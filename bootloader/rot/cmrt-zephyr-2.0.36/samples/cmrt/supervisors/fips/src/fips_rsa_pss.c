/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
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
#include <cri/cmrt.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/hc.h>
#include "crypto/rsa_common.h"
#include <cmrt/ucu/endianness.h>
#include <cmrt/ucu/rsa_pad.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

int32_t cri_rsa_verify(uint8_t *asset,
		uint32_t byte_length,
		uint8_t *work_buffer,
		uint8_t *signature,
		uint8_t *pss_message)
{
	int32_t status = 0;

	uint8_t *n = NULL;

	struct cmrt_rsa_ctx ctx;

	dprintk("Starting PKE: %d-bit RSA ", byte_length * 8);
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_rsa_ctx_init(&ctx, byte_length * 8, (uint32_t *)work_buffer);
	if (status) goto out;

	n = GET_RSA_PUBLIC_MODULUS_FROM_ASSET(asset);

	reverse_words(n, byte_length / sizeof(uint32_t), ctx.key.n);
	reverse_words(signature, byte_length / sizeof(uint32_t), ctx.signature);

	/* cri_util.c  */
	status = cri_rsa_pub(pke, &ctx);
	if (status) goto out;

	reverse_words(ctx.message, byte_length / sizeof(uint32_t), pss_message);

out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}
	return status;
}

int32_t _cri_rsa_sign(uint8_t *asset,
			     uint32_t rsa_key_type,
			     uint32_t fips_rsa_key_type,
			     uint8_t *work_buffer,
			     uint8_t *pss_message,
			     uint8_t *signature)
{
	int32_t status = 0;
	int32_t res = -EACCES;

	uint32_t byte_length = 0;
	uint32_t bit_length = 0;

	uint8_t *kptr = NULL;

	struct cmrt_rsa_ctx *r_ctx = NULL;
	struct cmrt_rsa_ctx *c_ctx = NULL;
	cmrt_pke_t pke = CMRT_INVALID_HANDLE;

	switch (rsa_key_type) {
	case FIPS_RSA_PF:
		rsa_key_type = FIPS_RSA;
		fips_rsa_key_type = fips_rsa_key_type - FIPS_RSA_PF_2K + FIPS_RSA_2K;
		/* fall through */
	case FIPS_RSA:
		byte_length = GET_RSA_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_BIT_LENGTH(fips_rsa_key_type);
		break;
	case FIPS_RSA_CRT:
		byte_length = 2 * GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_CRT_BIT_LENGTH(fips_rsa_key_type);
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	dprintk("Starting PKE: %d-bit RSA ", bit_length);
	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	switch (rsa_key_type) {
	case FIPS_RSA:
		r_ctx = (struct cmrt_rsa_ctx *)work_buffer;

		res = cmrt_pke_rsa_ctx_init(r_ctx, bit_length,
				       (uint32_t *)(work_buffer + sizeof(struct cmrt_rsa_ctx)));
		if (res) {
			dprintk("Failed RSA init %d\n", res);
			status = -EIO;
			goto out;
		}

		kptr = GET_RSA_PUBLIC_MODULUS_FROM_ASSET(asset);
		reverse_words(kptr, GET_RSA_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), r_ctx->key.n);
		kptr = GET_RSA_PRIVATE_EXPONENT_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), r_ctx->key.d);
		reverse_words(pss_message, GET_RSA_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), r_ctx->message);

		status = cmrt_pke_rsa_sign(pke, r_ctx);
		if (status) {
			goto out;
		}

		reverse_words(r_ctx->signature, GET_RSA_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), signature);
		break;

	case FIPS_RSA_CRT:
		c_ctx = (struct cmrt_rsa_ctx *)work_buffer;

		res = cmrt_pke_rsa_ctx_init(c_ctx, GET_RSA_CRT_BIT_LENGTH(fips_rsa_key_type),
				(uint32_t *)(work_buffer + sizeof(struct cmrt_rsa_ctx)));
		if (res) {
			dprintk("Failed RSA init %d\n", res);
			status = -EIO;
			goto out;
		}

		kptr = GET_RSA_PUBLIC_MODULUS_FROM_ASSET(asset);
		reverse_words(kptr, byte_length / sizeof(uint32_t), c_ctx->key.n);
		kptr = GET_RSA_CRT_PRIVATE_P_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), c_ctx->key.p);
		kptr = GET_RSA_CRT_PRIVATE_Q_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), c_ctx->key.q);
		kptr = GET_RSA_CRT_PRIVATE_DP_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), c_ctx->key.dp);
		kptr = GET_RSA_CRT_PRIVATE_DQ_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), c_ctx->key.dq);
		kptr = GET_RSA_CRT_PRIVATE_IQ_FROM_ASSET(asset, fips_rsa_key_type);
		reverse_words(kptr, GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type) / sizeof(uint32_t), c_ctx->key.iq);
		reverse_words(pss_message, byte_length / sizeof(uint32_t), c_ctx->message);

		dprintk("do signature\n");
		status = cmrt_pke_rsa_crt_sign(pke, c_ctx);
		if (status) {
			dprintk("status: %d\n", status);
			goto out;
		}

		dhexdump("c_ctx->signature", c_ctx->signature, byte_length);

		reverse_words(c_ctx->signature, byte_length / sizeof(uint32_t), signature);
		break;

	default:
		status = -EINVAL;
		goto out;
	}

out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}

	return status;
}

int32_t fips_rsa_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;
	int32_t res = -EACCES;

	uint32_t asset_length = 0;
	uint32_t total_length = 0;
	uint32_t hashlen;
	uint32_t hashtype;
	uint32_t length;
	uint32_t byte_length = 0;
	uint32_t bit_length = 0;

	uint8_t rsa_key_type;
	uint8_t fips_rsa_key_type;

	uint8_t *asset = workcontext+4;
	uint8_t *pss_message;
	uint8_t *signature;
	uint8_t *work_buffer;
	uint8_t *e;
	uint8_t hash_core;

	struct cmrt_pss_params *pss;

	status = 0;
	dprintk("FIPS_SERVICE_RSA_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_RSA_VERIFY);

	/* get maximum asset length */
	asset_length = GET_RSA_CRT_ASSET_SIZE(FIPS_RSA_CRT_4K);
	total_length = asset_length;

	res = fips_read_asset_from_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, &asset_length);
	if (res) {
		dprintk("Teefs read not successful\n");
		status = -ENOENT;
		goto out;
	}

	total_length = asset_length;

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(((uint32_t *) asset)[2])) == 0) {
		dprintk("The currently logged in user cannot own this key\n");
		status = -EACCES;
		goto out;
	}

	if ((GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_KEYPAIR) &&
			(GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_CRT_KEYPAIR) &&
			(GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_PF_KEYPAIR) &&
			(GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_PUBLIC_KEY)) {
		dprintk("Key type not set to RSA keypair\n");
		status = -EPERM;
		goto out;
	}

	e = GET_RSA_PUBLIC_EXPONENT_FROM_ASSET(asset);
	/* NB 0x01000100 is the little-endian representation of 2^16+1 */
	if (((uint32_t *)e)[0] != 0x01000100) {
		dprintk("Only e = 2^16 + 1 is supported: %08x given\n", ((uint32_t *)e)[0]);
		status = -EINVAL;
		goto out;
	}

	GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_key_type, fips_rsa_key_type);
	if (rsa_key_type == FIPS_INVALID) {
		status = -EINVAL;
		goto out;
	}

	hash_core = h->params[0].value.a >> 16;
	if ((hash_core != FIPS_HC_1)
#ifdef CONFIG_CMRT_HC2
	    && (hash_core != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out;
	}

	switch (h->params[0].value.a & 0xFFFF) {
	case FIPS_HASH_SHA224:
		hashtype = HC_HASH_ALGO_SHA_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		hashtype = HC_HASH_ALGO_SHA_256;
		hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		hashtype = HC_HASH_ALGO_SHA_384;
		hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		hashtype = HC_HASH_ALGO_SHA_512;
		hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		hashtype = HC_HASH_ALGO_SHA_512_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		hashtype = HC_HASH_ALGO_SHA_512_256;
		hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		hashtype = HC_HASH_ALGO_SHA3_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		hashtype = HC_HASH_ALGO_SHA3_256;
		hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		hashtype = HC_HASH_ALGO_SHA3_384;
		hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		hashtype = HC_HASH_ALGO_SHA3_512;
		hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out;
	}

	if (h->params[0].value.b > 64) {
		status = -EINVAL;
		goto out;
	}

	switch (rsa_key_type) {
	case FIPS_RSA_PF:
		rsa_key_type = FIPS_RSA;
		fips_rsa_key_type = fips_rsa_key_type - FIPS_RSA_PF_2K + FIPS_RSA_2K;
		/* fall through */
	case FIPS_RSA:
		byte_length = GET_RSA_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_BIT_LENGTH(fips_rsa_key_type);
		break;
	case FIPS_RSA_CRT:
		byte_length = 2 * GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_CRT_BIT_LENGTH(fips_rsa_key_type);
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	pss = (struct cmrt_pss_params *)(asset + asset_length);
	pss_message = ((uint8_t *)pss) + sizeof(struct cmrt_pss_params);

	pss->bits = bit_length;
	pss->hlen = hashlen;
	pss->flags = 0;
	pss->halgo = hashtype;
	pss->slen = h->params[0].value.b;

	signature = pss_message + byte_length;
	work_buffer = signature + byte_length;

	length = byte_length;
	status = fips_read_from_shared_memory(h, 3, signature, &length);
	if (status) {
		goto out;
	}

	if (length != byte_length) {
		dprintk("Signature appears to be the wrong length");
		status = -EIO;
		goto out;
	}

	status = cri_rsa_verify(asset, byte_length, work_buffer, signature, pss_message);
	if (status) {
		goto out;
	}

	dhexdump("RSA output:", pss_message, byte_length);

	/* Generate Hash Core Handle for cmrt_pss_verify. */
	const char *hc_name = DT_LABEL(DT_NODELABEL(hc0));
	if (hash_core == FIPS_HC_2) {
		hc_name = DT_LABEL(DT_NODELABEL(hc3));
	}
	cmrt_hc_t hc = cmrt_hc_open(hc_name, CMRT_O_SYNC);
	if (cmrt_is_valid(hc)) {
		status = cmrt_pss_verify(hc, pss, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, pss_message);
		cmrt_hc_close(hc);
	} else {
		dprintk("HC opening failed\n");
		status = -EBUSY;
		goto out;
	}

	if (status) {
		dprintk("PSS verify failed\n");
		status = -EPERM;
		goto out;
	}

out:
	destroy_workcontext(status);
	return status;
}

int32_t fips_rsa_sign(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;
	int32_t res = -EACCES;

	uint32_t asset_length = 0;
	uint32_t total_length = 0;
	uint32_t hashlen;
	uint32_t hashtype;
	uint32_t byte_length;
	uint32_t bit_length;

	uint8_t rsa_key_type;
	uint8_t fips_rsa_key_type;

	uint8_t *asset = workcontext+4;
	uint8_t *pss_message;
	uint8_t *signature;
	uint8_t *work_buffer;
	uint8_t *e;
	uint8_t hash_core;

	struct cmrt_pss_params *pss;

	status = 0;
	dprintk("FIPS_SERVICE_RSA_SIGN\n");
	CHECK_COMMAND(FIPS_SERVICE_RSA_SIGN);

	/* get maximum asset length */
	asset_length = GET_RSA_CRT_ASSET_SIZE(FIPS_RSA_CRT_4K);
	total_length = asset_length;

	res = fips_read_asset_from_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, &asset_length);
	if (res) {
		dprintk("Teefs read not successful\n");
		status = -ENOENT;
		goto out;
	}

	total_length = asset_length;

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(((uint32_t *) asset)[2])) == 0) {
		dprintk("The currently logged in user cannot own this key\n");
		status = -EACCES;
		goto out;
	}

	if ((GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_KEYPAIR) &&
			(GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_PF_KEYPAIR) &&
			(GET_ASSET_TYPE(((uint32_t *) asset)[2]) != FIPS_TYPE_RSA_CRT_KEYPAIR)) {
		dprintk("Key type not set to RSA keypair\n");
		status = -EPERM;
		goto out;
	}

	e = GET_RSA_PUBLIC_EXPONENT_FROM_ASSET(asset);
	/* NB 0x01000100 is the little-endian representation of 2^16+1 */
	if (((uint32_t *)e)[0] != 0x01000100) {
		dprintk("Only e = 2^16 + 1 is supported: %08x given\n", ((uint32_t *)e)[0]);
		status = -EINVAL;
		goto out;
	}

	GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_key_type, fips_rsa_key_type);
	if (rsa_key_type == FIPS_INVALID) {
		status = -EINVAL;
		goto out;
	}

	hash_core = h->params[0].value.a >> 16;
	if ((hash_core != FIPS_HC_1)
#ifdef CONFIG_CMRT_HC2
	    && (hash_core != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out;
	}

	switch (h->params[0].value.a & 0xFFFF) {
	case FIPS_HASH_SHA224:
		hashtype = HC_HASH_ALGO_SHA_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		hashtype = HC_HASH_ALGO_SHA_256;
		hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		hashtype = HC_HASH_ALGO_SHA_384;
		hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		hashtype = HC_HASH_ALGO_SHA_512;
		hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		hashtype = HC_HASH_ALGO_SHA_512_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		hashtype = HC_HASH_ALGO_SHA_512_256;
		hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		hashtype = HC_HASH_ALGO_SHA3_224;
		hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		hashtype = HC_HASH_ALGO_SHA3_256;
		hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		hashtype = HC_HASH_ALGO_SHA3_384;
		hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		hashtype = HC_HASH_ALGO_SHA3_512;
		hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out;
	}

	if (h->params[0].value.b > 64) {
		status = -EINVAL;
		goto out;
	}

	switch (rsa_key_type) {
	case FIPS_RSA_PF:
		rsa_key_type = FIPS_RSA;
		fips_rsa_key_type = fips_rsa_key_type - FIPS_RSA_PF_2K + FIPS_RSA_2K;
		/* fall through */
	case FIPS_RSA:
		byte_length = GET_RSA_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_BIT_LENGTH(fips_rsa_key_type);
		break;
	case FIPS_RSA_CRT:
		byte_length = 2 * GET_RSA_CRT_KEY_LENGTH(fips_rsa_key_type);
		bit_length = GET_RSA_CRT_BIT_LENGTH(fips_rsa_key_type);
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	pss = (struct cmrt_pss_params *)(asset + asset_length);
	pss_message = ((uint8_t *)pss) + sizeof(struct cmrt_pss_params);

	pss->bits = bit_length;
	pss->hlen = hashlen;
	pss->flags = 0;
	pss->halgo = hashtype;
	pss->slen = h->params[0].value.b;

	const char *hc_name = DT_LABEL(DT_NODELABEL(hc0));
	if (hash_core == FIPS_HC_2) {
		hc_name = DT_LABEL(DT_NODELABEL(hc3));
	}
	cmrt_hc_t hc = cmrt_hc_open(hc_name, CMRT_O_SYNC);
	if (cmrt_is_valid(hc)) {
		status = cmrt_pss_enc(hc, pss, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, pss_message);
		cmrt_hc_close(hc);
	} else {
		dprintk("HC opening failed\n");
		status = -EBUSY;
		goto out;
	}
	if (status) {
		status = -EINVAL;
		goto out;
	}

	dhexdump("pss", pss_message, byte_length);

	signature = pss_message + byte_length;
	work_buffer = signature + byte_length;

	status = _cri_rsa_sign(asset, rsa_key_type, fips_rsa_key_type,
			       work_buffer, pss_message, signature);
	if (status) {
		goto out;
	}

	dhexdump("signature", signature, byte_length);

	res = fips_write_to_shared_memory(signature, byte_length, h, 3);
	if (res) {
		dprintk("Write to shared memory failed\n");
		status = -EIO;
		goto out;
	}

out:
	destroy_workcontext(status);
	return status;
}
