/*
 * Copyright (c) 2020-2024y Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <cri/cmrt/sac.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt/crypto/rsa_common.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include <drivers/cmrt/cmrt.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"


static int pke_rsa_pub(cmrt_pke_t pke, const struct cmrt_rsa_key *key,
		       const char *signature, char *message)
{
	return cmrt_pke_rsa_public_key_primitive(pke, key->bits,
						 key->n, key->e,
						 signature,
						 message);
}


int32_t rsa_pairwise_consistency_check(const uint32_t *n,
		const uint32_t *d,
		uint32_t bit_length,
		uint32_t *work_buffer)
{
	int32_t status;

	uint32_t byte_length;

	uint32_t *m;

	struct cmrt_rsa_ctx *r_ctx = NULL;

	byte_length = bit_length / 8;

	if (work_buffer == NULL) {
		m = (uint32_t *) workcontext;
	} else {
		m = work_buffer;
	}

	r_ctx = (struct cmrt_rsa_ctx *)((uint8_t *)m + byte_length);

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_rsa_ctx_init(r_ctx, bit_length,
			(uint32_t *)((uint8_t *)r_ctx + sizeof(struct cmrt_rsa_ctx)));
	if (status) goto out;

	memset(m, 0x00, byte_length);
	status = cri_get_randomness((uint8_t *) m, 16 * sizeof(uint8_t));
	if (status) goto out;

	dhexdump("m", m, byte_length);

	memcpy(r_ctx->key.d, d, byte_length);
	memcpy(r_ctx->key.n, n, byte_length);
	memcpy(r_ctx->signature, m, byte_length);

	dhexdump("e", r_ctx->key.e, r_ctx->key.elength);
	dhexdump("d", r_ctx->key.d, r_ctx->key.elength);
	dhexdump("n", r_ctx->key.n, byte_length);
	dhexdump("s", r_ctx->signature, byte_length);

	status = pke_rsa_pub(pke, &r_ctx->key, r_ctx->signature, r_ctx->message);
	if (status) goto out;

	memset(r_ctx->signature, 0x00, byte_length);

	status = cmrt_pke_rsa_sign(pke, r_ctx);
	if (status) goto out;

	if (memcmp(r_ctx->signature, m, byte_length) != 0) {
		status = -EINVAL;
		goto out;
	}

out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}
	return status;
}

int32_t cri_rsa_crt_key_generation(struct cmrt_rsa_ctx *ctx,
		uint32_t *work_buffer,
		uint8_t fips_rsa_key_type)
{
	int32_t status = 0;
	int32_t res = -EIO;

	uint8_t rsa_type = 0;
	uint8_t fips_rsa_type = 0;
	cmrt_pke_t pke = CMRT_INVALID_HANDLE;

	fips_get_rsa_type(fips_rsa_key_type, &rsa_type, &fips_rsa_type);

	switch (rsa_type) {
	case FIPS_RSA:
		res = cmrt_pke_rsa_ctx_init(ctx, GET_RSA_BIT_LENGTH(fips_rsa_type), work_buffer);
		dprintk("Starting PKE: %d-bit RSA\n", GET_RSA_BIT_LENGTH(fips_rsa_key_type));
		break;
	case FIPS_RSA_PF:
		res = cmrt_pke_rsa_ctx_init(ctx, GET_RSA_PF_BIT_LENGTH(fips_rsa_type), work_buffer);
		dprintk("Starting PKE: %d-bit RSA\n", GET_RSA_PF_BIT_LENGTH(fips_rsa_key_type));
		break;
	case FIPS_RSA_CRT:
		res = cmrt_pke_rsa_ctx_init(ctx, GET_RSA_CRT_BIT_LENGTH(fips_rsa_type), work_buffer);
		dprintk("Starting PKE: %d-bit RSA\n", GET_RSA_CRT_BIT_LENGTH(fips_rsa_key_type));
		break;
	default:
		status = -EPERM;
		goto out;
	}

	if (res) {
		dprintk("Failed RSA init %d\n", res);
		status = -EIO;
		goto out;
	}

	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	res = cmrt_pke_rsa_crt_key_gen(pke, &(ctx->key));
	if (res) {
		dprintk("Failed to generate RSA key %d\n", res);
		status = -EIO;
		goto out;
	}

out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}
	return status;
}

int32_t fips_rsa_generate_keypair(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	uint8_t rsa_key_type;
	uint8_t fips_rsa_key_type;

	uint32_t asset_length = 0;
	uint32_t pk_asset_length = 0;
	uint32_t byte_length = 0;

	uint32_t *pct_n;
	uint32_t *pct_d;

	fips_rsa_public_key_components *public_key = (fips_rsa_public_key_components *) (workcontext + 4);
	fips_rsa_private_key_components *key = (fips_rsa_private_key_components *)
			((uint8_t *) public_key + sizeof(fips_rsa_public_key_components));
	fips_rsa_pf_private_key_components *key_pf = (fips_rsa_pf_private_key_components *)
			((uint8_t *) key + sizeof(fips_rsa_private_key_components));
	fips_rsa_crt_private_key_components *crt_key = (fips_rsa_crt_private_key_components *)
			((uint8_t *) key_pf + sizeof(fips_rsa_pf_private_key_components));
	struct cmrt_rsa_ctx *ctx = (struct cmrt_rsa_ctx *) ((uint8_t *) crt_key +
			sizeof(fips_rsa_crt_private_key_components));

	uint8_t *asset = (uint8_t *) ctx + sizeof(struct cmrt_rsa_ctx);
	uint8_t *work_buffer = NULL;
	cmrt_pke_t pke = CMRT_INVALID_HANDLE;

	dprintk("FIPS_SERVICE_GEN_RSA_KEYPAIR\n");
	CHECK_COMMAND(FIPS_SERVICE_GEN_RSA_KEYPAIR);

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(h->params[0].value.b)) == 0) {
		dprintk("The currently logged in user cannot own this key\n");
		status = -EACCES;
		goto out;
	}

	public_key->e = GET_RSA_PUBLIC_EXPONENT_FROM_ASSET(asset);
	public_key->n = GET_RSA_PUBLIC_MODULUS_FROM_ASSET(asset);

	dprintk("Making RSA key\n");
	fips_get_rsa_type(h->params[0].value.a, &rsa_key_type, &fips_rsa_key_type);
	switch (rsa_key_type) {
	case FIPS_RSA:
		if (GET_ASSET_TYPE(h->params[0].value.b) != FIPS_TYPE_RSA_KEYPAIR) {
			dprintk("Wrong asset type requested");
			status = -EPERM;
			goto out;
		}

		SET_FIPS_RSA_HEADER(asset, GET_ASSET_OWNER(h->params[0].value.b),
				FIPS_TYPE_RSA_KEYPAIR, fips_rsa_key_type);

		key->d = GET_RSA_PRIVATE_EXPONENT_FROM_ASSET(asset, fips_rsa_key_type);

		byte_length = GET_RSA_KEY_LENGTH(fips_rsa_key_type);
		asset_length = GET_RSA_ASSET_SIZE(fips_rsa_key_type);
		pk_asset_length = GET_RSA_PUBLIC_KEY_ASSET_SIZE(fips_rsa_key_type);

		pct_n = (uint32_t *) (asset + GET_RSA_ASSET_SIZE(fips_rsa_key_type));
		pct_d = (uint32_t *) ((uint8_t *) pct_n + byte_length);
		work_buffer = (uint8_t *) pct_d + byte_length;
		break;

	case FIPS_RSA_PF:
		if (GET_ASSET_TYPE(h->params[0].value.b) != FIPS_TYPE_RSA_PF_KEYPAIR) {
			dprintk("Wrong asset type requested");
			status = -EPERM;
			goto out;
		}

		SET_FIPS_RSA_HEADER(asset, GET_ASSET_OWNER(h->params[0].value.b),
				FIPS_TYPE_RSA_PF_KEYPAIR, fips_rsa_key_type);

		key_pf->d = GET_RSA_PF_PRIVATE_EXPONENT_FROM_ASSET(asset, fips_rsa_key_type);
		key_pf->p = GET_RSA_PF_PRIVATE_P_FROM_ASSET(asset, fips_rsa_key_type);
		key_pf->q = GET_RSA_PF_PRIVATE_Q_FROM_ASSET(asset, fips_rsa_key_type);

		byte_length = GET_RSA_PF_KEY_LENGTH(fips_rsa_key_type);
		asset_length = GET_RSA_PF_ASSET_SIZE(fips_rsa_key_type);
		pk_asset_length = GET_RSA_PF_PUBLIC_KEY_ASSET_SIZE(fips_rsa_key_type);

		pct_n = (uint32_t *) (asset + GET_RSA_PF_ASSET_SIZE(fips_rsa_key_type));
		pct_d = (uint32_t *) ((uint8_t *) pct_n + byte_length);
		work_buffer = (uint8_t *) pct_d + byte_length;

		ctx->key.p = (uint8_t *)key_pf->p;
		ctx->key.q = (uint8_t *)key_pf->q;
		break;

	case FIPS_RSA_CRT:
		if (GET_ASSET_TYPE(h->params[0].value.b) != FIPS_TYPE_RSA_CRT_KEYPAIR) {
			dprintk("Wrong asset type requested");
			status = -EPERM;
			goto out;
		}

		SET_FIPS_RSA_HEADER(asset, GET_ASSET_OWNER(h->params[0].value.b),
				FIPS_TYPE_RSA_CRT_KEYPAIR, fips_rsa_key_type);

		crt_key->p = GET_RSA_CRT_PRIVATE_P_FROM_ASSET(asset, fips_rsa_key_type);
		crt_key->q = GET_RSA_CRT_PRIVATE_Q_FROM_ASSET(asset, fips_rsa_key_type);
		crt_key->dp = GET_RSA_CRT_PRIVATE_DP_FROM_ASSET(asset, fips_rsa_key_type);
		crt_key->dq = GET_RSA_CRT_PRIVATE_DQ_FROM_ASSET(asset, fips_rsa_key_type);
		crt_key->iq = GET_RSA_CRT_PRIVATE_IQ_FROM_ASSET(asset, fips_rsa_key_type);

		byte_length = 2 * GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type);
		asset_length = GET_RSA_CRT_ASSET_SIZE(fips_rsa_key_type);
		pk_asset_length = GET_RSA_CRT_PUBLIC_KEY_ASSET_SIZE(fips_rsa_key_type);

		pct_n = (uint32_t *) (asset + GET_RSA_CRT_ASSET_SIZE(fips_rsa_key_type));
		pct_d = (uint32_t *) ((uint8_t *) pct_n + byte_length);
		work_buffer = (uint8_t *) pct_d + byte_length;

		ctx->key.p = (uint8_t *)crt_key->p;
		ctx->key.q = (uint8_t *)crt_key->q;
		ctx->key.dp = (uint8_t *)crt_key->dp;
		ctx->key.dq = (uint8_t *)crt_key->dq;
		ctx->key.iq = (uint8_t *)crt_key->iq;
		break;

	default:
		status = -EPERM;
		goto out;
	}

	static const uint32_t E = 0x00010001;
	ctx->key.bits = byte_length * 8;
	ctx->key.e = (uint8_t *)&E;
	ctx->key.elength = 4;
	ctx->key.flags = 0;
	ctx->key.n = (uint8_t *)pct_n;
	ctx->key.d = (uint8_t *)pct_d;
	ctx->key.mask = work_buffer + byte_length;
	work_buffer = (uint8_t *) work_buffer + sizeof(uint32_t);

	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_rsa_crt_key_gen(pke, &(ctx->key));
	if (status) {
		status = -EIO;
		dprintk("RSA key generation failed: %d", status);
		goto out;
	}
	cmrt_pke_close(pke);

	memcpy(pct_n, ctx->key.n, byte_length);
	memcpy(pct_d, ctx->key.d, byte_length);

	switch (rsa_key_type) {
	case FIPS_RSA:
		reverse_words(ctx->key.n, byte_length / sizeof(uint32_t), public_key->n);
		reverse_words(ctx->key.d, byte_length / sizeof(uint32_t), key->d);
		break;

	case FIPS_RSA_PF:
		reverse_words(ctx->key.n, byte_length / sizeof(uint32_t), public_key->n);
		reverse_words(ctx->key.d, byte_length / sizeof(uint32_t), key_pf->d);
		reverse_words(ctx->key.p, (byte_length / 2) / sizeof(uint32_t), key_pf->p);
		reverse_words(ctx->key.q, (byte_length / 2) / sizeof(uint32_t), key_pf->q);
		break;

	case FIPS_RSA_CRT:
		reverse_words(ctx->key.n, byte_length / sizeof(uint32_t), public_key->n);
		reverse_words(ctx->key.p, (byte_length / 2) / sizeof(uint32_t), crt_key->p);
		reverse_words(ctx->key.q, (byte_length / 2) / sizeof(uint32_t), crt_key->q);
		reverse_words(ctx->key.dp, (byte_length / 2) / sizeof(uint32_t), crt_key->dp);
		reverse_words(ctx->key.dq, (byte_length / 2) / sizeof(uint32_t), crt_key->dq);
		reverse_words(ctx->key.iq, (byte_length / 2) / sizeof(uint32_t), crt_key->iq);
		break;

	default:
		status = -EPERM;
		goto out;
	}

	status = fips_write_asset_to_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, asset_length);
	if (status) {
		goto out;
	}

	status = rsa_pairwise_consistency_check(pct_n, pct_d, byte_length * 8, (uint32_t *)work_buffer);
	if (status) {
		dprintk("PCT fail\n");
		destroy_workcontext_and_halt(status);
	}

	SET_ASSET_TYPE_IN_ASSET(asset, FIPS_TYPE_RSA_PUBLIC_KEY);
	status = fips_write_to_shared_memory(asset + GET_RSA_HEADER_SIZE(), pk_asset_length - GET_RSA_HEADER_SIZE(), h, 2);


out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}
	destroy_workcontext(status);
	return status;
}
