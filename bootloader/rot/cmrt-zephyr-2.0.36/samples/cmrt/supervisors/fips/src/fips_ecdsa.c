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

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

int32_t cri_ecdsa_verify(cri_ecc_curve_t curve,
		uint8_t *r,
		uint8_t *s,
		uint8_t *public_key_x,
		uint8_t *public_key_y,
		uint8_t *digest,
		uint32_t digest_len,
		uint8_t *rp)
{
	int32_t status = 0;
	int32_t res = 0;

	dprintk("Starting PKE.\n");
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	dprintk("Verify generated signature.\n");
	res = cri_pke_ecdsa_verify_hash(pke, curve, public_key_x, public_key_y, digest, digest_len, r, s, rp);
	if (res) {
		printk("Failed to run cri_pke_ecdsa_verify %d!\n", res);
		status = -EPERM;
		goto out1;
	}

	res = cri_pke_sync(pke);
	if (res) {
		dprintk("Failed to sync pke %d\n", res);
		status = -EIO;
		goto out1;
	}

out1:
	cri_pke_close(pke);
out:
	return status;
}

static int32_t ecdsa_sign(cri_ecc_curve_t curve,
		uint8_t *priv_key,
		uint8_t *digest,
		uint32_t digest_len,
		uint8_t *r,
		uint8_t *s)
{
	int32_t status = 0;
	int32_t res = 0;

	printk("Starting PKE.\n");
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	status = cri_pke_ecdsa_sign_hash(pke, curve, priv_key, digest, digest_len, r, s);
	if (res) {
		printk("Failed to run cri_pke_ecdsa_verify %d!\n", res);
		status = -EIO;
		goto out1;
	}

	res = cri_pke_sync(pke);
	if (res) {
		dprintk("Failed to sync pke %d\n", res);
		status = -EIO;
		goto out1;
	}

out1:
	cri_pke_close(pke);
out:
	return status;
}

int32_t fips_ecdsa_sign(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	uint32_t asset_length = 0;
	uint32_t total_length = 0;
	uint32_t max_element_length = 0;
	uint32_t hash_length;
	uint32_t offset;

	uint8_t *asset;
	uint8_t *r;
	uint8_t *s;
	uint8_t *digest;
	uint8_t *private_key;
	uint8_t *hash;
	uint8_t hash_core;

	hash_work_struct sha;

	cri_ecc_curve_t curve = NULL;

	status = 0;
	dprintk("FIPS_SERVICE_ECDSA_SIGN\n");
	CHECK_COMMAND(FIPS_SERVICE_ECDSA_SIGN);

	if (h->params[0].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	/* get maximum asset length */
	curve = cri_pke_get_curve(CRI_ECC_CURVE_NIST_P521);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EIO;
		goto out;
	}
	asset_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);

	digest = workcontext + 4;
	asset = (uint8_t *)ALIGN_32_BIT_POINTER(digest + cri_pke_get_curve_length(curve));

	status = fips_read_asset_of_type_from_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, &asset_length, FIPS_TYPE_ECDSA_KEYPAIR);
	if (status) goto out;

	dhexdump("asset", asset, asset_length);

	curve = cri_pke_get_fips_curve_from_asset((fips_asset *) asset);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EPERM;
		goto out;
	}

	r = asset + GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);
	s = r + cri_pke_get_curve_length(curve);
	hash = s + cri_pke_get_curve_length(curve);
	total_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve) + 3 * cri_pke_get_curve_length(curve);

	hash_core = h->params[0].value.a >> 16;
	if ((hash_core != FIPS_HC_1)
#ifdef CONFIG_CMRT_HC2
	    && (hash_core != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out;
	}

	sha.hashtype = h->params[0].value.a & 0xFFFF;
	switch (sha.hashtype) {
	case FIPS_HASH_SHA224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		sha.hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		sha.hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		sha.hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out;
	}

	offset = 0;
	if (sha.hashlen < cri_pke_get_curve_length(curve)) {
		hash_length = sha.hashlen;
	} else {
		hash_length = cri_pke_get_curve_length(curve);
	}

	max_element_length = sha.hashlen;
	status = cri_hash(&sha, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, digest, max_element_length, hash_core);
	if (status) {
		status = -EIO;
		goto out;
	}

	memcpy(hash + offset, digest, hash_length);

	dhexdump("digest", hash, cri_pke_get_curve_length(curve));

	private_key = GET_ECDSA_PRIVATE_KEY_FROM_ASSET(asset, curve);
	dhexdump("private key", private_key, cri_pke_get_curve_length(curve));

	status = ecdsa_sign(curve, private_key, hash, hash_length, r, s);
	if (status) goto out;

	dhexdump("r", r, cri_pke_get_curve_length(curve));
	dhexdump("s", s, cri_pke_get_curve_length(curve));

	status = fips_write_to_shared_memory(r, 2 * cri_pke_get_curve_length(curve), h, 3);
	if (status) goto out;

out:
	dprintk("Zero length: %i\n", total_length + 68 + sizeof(uint32_t));
	destroy_workcontext(total_length + 68 + sizeof(uint32_t));
	return status;
}

int32_t fips_ecdsa_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	uint32_t asset_length = 0;
	uint32_t total_length = 0;
	uint32_t max_element_length = 0;
	uint32_t input_size;
	uint32_t hash_length;
	uint32_t offset;

	uint8_t *asset;
	uint8_t *r;
	uint8_t *rp;
	uint8_t *s;
	uint8_t *digest;
	uint8_t *public_key_x;
	uint8_t *public_key_y;
	uint8_t *hash;
	uint8_t hash_core;

	hash_work_struct sha;

	cri_ecc_curve_t curve = NULL;

	status = 0;
	dprintk("FIPS_SERVICE_ECDSA_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_ECDSA_VERIFY);

	asset = workcontext + sizeof(uint32_t);

	if (h->params[0].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	/* get maximum asset length */
	curve = cri_pke_get_curve(CRI_ECC_CURVE_NIST_P521);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EIO;
		goto out;
	}
	asset_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);
	total_length = asset_length;
	max_element_length = 64;

	digest = workcontext + sizeof(uint32_t);
	asset = (uint8_t *)ALIGN_32_BIT_POINTER(digest + max_element_length);

	status = fips_read_asset_from_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, &asset_length);
	if (status) goto out;

	dhexdump("asset", asset, asset_length);

	if ((GET_ASSET_TYPE_FROM_ASSET(asset) != FIPS_TYPE_ECDSA_KEYPAIR) &&
	    (GET_ASSET_TYPE_FROM_ASSET(asset) != FIPS_TYPE_ECDSA_PUBLIC_KEY)) {
		dprintk("Key type not set to FIPS_TYPE_ECDSA_KEYPAIR or FIPS_TYPE_ECDSA_PUBLIC_KEY\n");
		status = -EPERM;
		goto out;
	}

	curve = cri_pke_get_fips_curve_from_asset((fips_asset *) asset);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EPERM;
		goto out;
	}

	r = asset + GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);
	s = r + cri_pke_get_curve_length(curve);
	rp = s + cri_pke_get_curve_length(curve);
	hash = rp + cri_pke_get_curve_length(curve);
	total_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve) + 4 * cri_pke_get_curve_length(curve);

	hash_core = h->params[0].value.a >> 16;
	if ((hash_core != FIPS_HC_1)
#ifdef CONFIG_CMRT_HC2
	    && (hash_core != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out;
	}

	sha.hashtype = h->params[0].value.a & 0xFFFF;
	switch (sha.hashtype) {
	case FIPS_HASH_SHA224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		sha.hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		sha.hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		sha.hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out;
	}
	dprintk("Hashlen:%d\n", sha.hashlen);

	offset = 0;
	if (sha.hashlen < cri_pke_get_curve_length(curve)) {
		hash_length = sha.hashlen;
	} else {
		hash_length = cri_pke_get_curve_length(curve);
	}

	max_element_length = sha.hashlen;
	status = cri_hash(&sha, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, digest, max_element_length, hash_core);
	if (status) {
		status = -EIO;
		goto out;
	}

	memcpy(hash + offset, digest, hash_length);

	dhexdump("digest", hash, cri_pke_get_curve_length(curve));

	input_size = 2 * cri_pke_get_curve_length(curve);
	status = fips_read_from_shared_memory(h, 3, r, &input_size);
	if (status) goto out;

	dhexdump("r", r, cri_pke_get_curve_length(curve));
	dhexdump("s", s, cri_pke_get_curve_length(curve));

	public_key_x = GET_ECDSA_PUBLIC_KEY_X_FROM_ASSET(asset);
	public_key_y = GET_ECDSA_PUBLIC_KEY_Y_FROM_ASSET(asset, curve);
	dhexdump("public key x", public_key_x, cri_pke_get_curve_length(curve));
	dhexdump("public key y", public_key_y, cri_pke_get_curve_length(curve));

	status = cri_ecdsa_verify(curve, r, s, public_key_x, public_key_y, hash, hash_length, rp);
	if (status) {
		status = -EIO;
		goto out;
	}

	if (memcmp(r, rp, cri_pke_get_curve_length(curve)) != 0) {
		dprintk("Verify failed\n");
		status = -EPERM;
	}

	dhexdump("r out", rp, cri_pke_get_curve_length(curve));

out:
	dprintk("Zero length: %i\n", total_length + 68 + sizeof(uint32_t));
	destroy_workcontext(total_length + 68 + sizeof(uint32_t));
	return status;
}
