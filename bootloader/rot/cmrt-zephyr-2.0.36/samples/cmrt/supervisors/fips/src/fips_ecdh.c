/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/pke.h>

#include <cri/cmrt/sac.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"

int32_t cri_ecdh(cmrt_ecc_curve_t curve,
		 const uint8_t *priv_key,
		 const uint8_t *public_key,
		 uint8_t *secret)
{
	int32_t status = 0;
	int32_t res = 0;

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	res = cmrt_pke_ecdh(pke, curve, priv_key, public_key, secret);
	if (res) {
		dprintk("Failed to run cri_pke_ecdh %d!\n", res);
		status = -EIO;
	}

	cri_pke_close(pke);
out:
	return status;
}

int32_t fips_ecdh(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;
	int32_t res = -EACCES;

	uint32_t asset_length = 0;
	uint32_t secret_length = 0;
	uint32_t total_length = 0;
	uint32_t max_element_length;
	uint32_t input_size;

	uint8_t *asset = workcontext+4;
	uint8_t *public_key_asset;
	uint8_t *secret_asset;
	uint8_t *private_key;
	uint8_t *public_key;
	uint8_t *secret;

	cmrt_ecc_curve_t curve = NULL;

	status = 0;
	dprintk("FIPS_SERVICE_ECDH\n");
	CHECK_COMMAND(FIPS_SERVICE_ECDH);

	/* get maximum asset length */
	curve = cri_pke_get_curve(CMRT_ECC_CURVE_NIST_P521);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EIO;
		goto out;
	}

	asset_length = GET_ECDH_KEYPAIR_ASSET_SIZE(curve);
	max_element_length = cmrt_pke_get_curve_length(curve);

	res = fips_read_asset_from_teefs(state,
			(fips_asset_identifier *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
			h->params[0].memref.size, asset, &asset_length);
	if (res) {
		dprintk("Teefs read not successful\n");
		goto out;
	}

	dhexdump("asset", asset, asset_length);

	if (GET_ASSET_INTERNAL_FLAG_FROM_ASSET(asset) != FIPS_INTERNAL_ASSET) {
		dprintk("Key not internally generated\n");
		state->approved_mode = 0;
	}

	if ((GET_ASSET_TYPE_FROM_ASSET(asset) != FIPS_TYPE_ECDH_KEYPAIR) &&
			(GET_ASSET_TYPE_FROM_ASSET(asset) != FIPS_TYPE_ECDSA_KEYPAIR)) {
		dprintk("Key type not set to FIPS_TYPE_ECDH_KEYPAIR\n");
		status = -EPERM;
		goto out;
	}
	total_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);

	curve = cri_pke_get_fips_curve_from_asset((fips_asset *) asset);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EPERM;
		goto out;
	}

	if (GET_ASSET_TYPE_FROM_ASSET(asset) == FIPS_TYPE_ECDH_KEYPAIR) {
		dprintk("ECDH asset\n");
		private_key = GET_ECDH_PRIVATE_KEY_FROM_ASSET(asset, curve);
		SET_ASSET_TYPE_OWNER(asset, state->user, FIPS_TYPE_ECDH_PUBLIC_KEY);
		asset_length = GET_ECDH_PUBLIC_KEY_ASSET_SIZE(curve);
	} else if (GET_ASSET_TYPE_FROM_ASSET(asset) == FIPS_TYPE_ECDSA_KEYPAIR) {
		dprintk("ECDSA asset\n");
		private_key = GET_ECDSA_PRIVATE_KEY_FROM_ASSET(asset, curve);
		SET_ASSET_TYPE_OWNER(asset, state->user, FIPS_TYPE_ECDSA_PUBLIC_KEY);
		asset_length = GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve);
	} else {
		dprintk("Key type not set to FIPS_TYPE_ECDH_KEYPAIR\n");
		status = -EPERM;
		goto out;
	}

	dhexdump("private key", private_key, cri_pke_get_curve_length(curve));

	public_key_asset = (uint8_t *)ALIGN_32_BIT_POINTER(asset + GET_ECDSA_KEYPAIR_ASSET_SIZE(curve));

	input_size = GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve);
	res = fips_read_from_shared_memory(h, 1, public_key_asset, &input_size);
	if (res) {
		dprintk("Read from shared memory failed\n");
		status = -EIO;
		goto out;
	}
	dhexdump("public key", public_key_asset, input_size);
	total_length += GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve);

	if (GET_EC_CURVE_TYPE(public_key_asset) != GET_EC_ASSET_CURVE_TYPE(asset)) {
		dprintk("Curve types not compatible\n");
		status = -EPERM;
		goto out;
	}

	public_key = ((uint8_t *)public_key_asset) + 4;
	dhexdump("public key", public_key, cri_pke_get_curve_length(curve));

	secret_asset = (uint8_t *)ALIGN_32_BIT_POINTER(public_key_asset + GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve));
	SET_FIPS_HEADER(secret_asset, state->user, FIPS_TYPE_SHARED_SECRET);
	SET_SHARED_SECRET_LENGTH(secret_asset, CURVE_LENGTH(curve));
	secret = GET_SHARED_SECRET_FROM_ASSET(secret_asset);
	secret_length = GET_SHARED_SECRET_ASSET_SIZE(CURVE_LENGTH(curve));
	total_length += secret_length;

	status = cri_ecdh(curve, private_key, public_key, secret);
	if (status) {
		goto out;
	}

	SET_ASSET_INTERNAL_FLAG_IN_ASSET(secret_asset, state->approved_mode);
	dhexdump("secret", secret, cri_pke_get_curve_length(curve));

	status = fips_write_asset_to_teefs(state,
			(fips_asset_identifier *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, secret_asset, secret_length);
	if (status) {
		goto out;
	}

	memset(private_key, 0x00, cri_pke_get_curve_length(curve));

	status = fips_write_to_shared_memory(asset + GET_HEADER_SIZE(), asset_length - GET_HEADER_SIZE(), h, 3);

out:
	dprintk("Zero size: %i\n", total_length + 12 + sizeof(uint32_t));
	destroy_workcontext(total_length + 12 + sizeof(uint32_t));
	return status;
}
