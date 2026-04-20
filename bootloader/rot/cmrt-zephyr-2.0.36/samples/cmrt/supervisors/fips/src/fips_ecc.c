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

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/pke.h>

#include <cri/cmrt/dd.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

const uint8_t curve_order_p224[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x16, 0xa2,
	0xe0, 0xb8, 0xf0, 0x3e, 0x13, 0xdd, 0x29, 0x45,
	0x5c, 0x5c, 0x2a, 0x3d
};

const uint8_t curve_order_p256[] = {
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84,
	0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51
};

const uint8_t curve_order_p384[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xc7, 0x63, 0x4d, 0x81, 0xf4, 0x37, 0x2d, 0xdf,
	0x58, 0x1a, 0x0d, 0xb2, 0x48, 0xb0, 0xa7, 0x7a,
	0xec, 0xec, 0x19, 0x6a, 0xcc, 0xc5, 0x29, 0x73
};

const uint8_t curve_order_p521[] = {
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfa, 0x51, 0x86, 0x87, 0x83, 0xbf, 0x2f,
	0x96, 0x6b, 0x7f, 0xcc, 0x01, 0x48, 0xf7, 0x09,
	0xa5, 0xd0, 0x3b, 0xb5, 0xc9, 0xb8, 0x89, 0x9c,
	0x47, 0xae, 0xbb, 0x6f, 0xb7, 0x1e, 0x91, 0x38,
	0x64, 0x09
};

int32_t cri_full_ecdsa_public_key_validation(cri_ecc_curve_t curve,
					     uint8_t *public_key_x,
					     uint8_t *public_key_y)
{
	int32_t status = 0;
	uint32_t dummy[17];
	const uint8_t *curve_order;

	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		dprintk("Failed to open pke\n");
		status = -EIO;
		goto out;
	}

	switch (cri_pke_get_curve_length(curve)) {
	case sizeof(curve_order_p224):
		curve_order = curve_order_p224;
		break;
	case sizeof(curve_order_p256):
		curve_order = curve_order_p256;
		break;
	case sizeof(curve_order_p384):
		curve_order = curve_order_p384;
		break;
	case sizeof(curve_order_p521):
		curve_order = curve_order_p521;
		break;
	default:
		status = -EPERM;
		goto out;
	}

	dhexdump("order", curve_order, cri_pke_get_curve_length(curve));

	dprintk("Check point is on the curve and in [0, p)\n");
	status = cri_pke_validate_ecc_xy_key(pke, curve, public_key_x, public_key_y);
	if (status >= 0) {
		status = cri_pke_sync(pke);
	}
	if (status) {
		dprintk("Failed to validate_ecc_xy_key pke %d\n", status);
		status = -EIO;
		goto out;
	}

	dprintk("   On curve, not the point-at-infinity\n");

	dprintk("Check order of the curve\n");
	if (cri_pke_ecdh(pke, curve, curve_order, public_key_x, dummy) >= 0) {
		status = cri_pke_sync(pke);
	} else {
		status = 0;
	}

	if (status) {
		dprintk("   Found point-at-infinity\n");
		status = 0;
	} else {
		dprintk("   Test failed\n");
		status = -EIO;
	}

out:
	cri_pke_close(pke);
	return status;
}

static int32_t ecdsa_keygen(cmrt_ecc_curve_t curve,
			    uint8_t *priv_key, uint8_t *pub_x, uint8_t *pub_y)
{
	int32_t status;

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open pke\n");
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_ecdsa_keygen(pke, curve, priv_key, pub_x, pub_y);

out:
	cmrt_pke_close(pke);
	return status;
}

static int32_t ecdh_keygen(cri_ecc_curve_t curve,
		uint8_t *priv_key, uint8_t *pub_x)
{
	int32_t status;

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open pke\n");
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_ecdh_keygen(pke, curve, priv_key, pub_x);

out:
	cmrt_pke_close(pke);
	return status;
}

static void increment(const size_t length, uint8_t *a)
{
	int32_t i;

	uint8_t tmp;
	uint8_t cry;

	cry = ((((int32_t)a[length - 1]) + 1) >> 8) & 1;
	a[length - 1] += 1;

	i = length - 2;
	while ((cry == 1) && (i >= 0)) {
		tmp = a[i] + cry;
		cry = ((((int32_t)a[i]) + cry) >> 8) & 1;
		a[i] = tmp;
		i--;
	}
}

/* This is the behavior seen and it is hard to say if it was supposed
 * to be a non short-circuiting test.  Now it could be replaced by
 * memcmp().
 */
static int32_t compare_big_numbers(const uint8_t *a,
				   const uint8_t *b,
				   const size_t length)
{
	int32_t greater = 0;
	int32_t less = 0;

	for (uint32_t i = 0; (i < length) && (greater == less); ++i) {
		greater = (a[i] > b[i]);
		less = (a[i] < b[i]);
	}

	return (greater - less);
}

static int32_t generate_ec_private_key(cri_ecc_curve_t curve,
				       uint8_t *private_key)
{
	int32_t status = 0;
	int32_t res;

	const uint8_t *curve_order;

	switch (cri_pke_get_curve_length(curve)) {
	case sizeof(curve_order_p224):
		curve_order = curve_order_p224;
		break;
	case sizeof(curve_order_p256):
		curve_order = curve_order_p256;
		break;
	case sizeof(curve_order_p384):
		curve_order = curve_order_p384;
		break;
	case sizeof(curve_order_p521):
		curve_order = curve_order_p521;
		break;
	default:
		status = -EPERM;
		goto out;
	}

	do {
		status = cri_get_randomness(private_key, cri_pke_get_curve_length(curve));
		if (status) goto out;

		if (cri_pke_get_curve_length(curve) == 66) {
			private_key[0] &= 0x01;
		}

		dhexdump("key candidate", private_key, cri_pke_get_curve_length(curve));

		res = compare_big_numbers(curve_order, private_key, cri_pke_get_curve_length(curve));
		dprintk("compare: %d\n", res);
	} while (res != 1);

	increment(cri_pke_get_curve_length(curve), private_key);

	dhexdump("key", private_key, cri_pke_get_curve_length(curve));

out:
	return status;
}

int32_t fips_ec_generate_key(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	uint32_t asset_length = 0;

	uint8_t *private_key;
	uint8_t *public_key_x;
	uint8_t *public_key_y;
	uint8_t *asset = workcontext+4;

	cri_ecc_curve_t curve;

	status = 0;
	dprintk("FIPS_SERVICE_GEN_EC_KEYPAIR\n");
	CHECK_COMMAND(FIPS_SERVICE_GEN_EC_KEYPAIR)

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(h->params[0].value.b)) == 0) {
		dprintk("The currently logged in user cannot own this key\n");
		status = -EACCES;
		goto out;
	}

	curve = cri_pke_get_fips_curve(h->params[0].value.a);
	if (curve == NULL) {
		status = -EPERM;
		goto out;
	}

	/* fips asset */
	SET_FIPS_EC_HEADER(asset,
			GET_ASSET_OWNER(h->params[0].value.b),
			GET_ASSET_TYPE(h->params[0].value.b),
			h->params[0].value.a);

	/* Internally generated key asset */
	SET_ASSET_INTERNAL_FLAG_IN_ASSET(asset, FIPS_INTERNAL_ASSET);

	switch (GET_ASSET_TYPE(h->params[0].value.b)) {
	case FIPS_TYPE_ECDSA_KEYPAIR:
		dprintk("Generating ECDSA key\n");

		public_key_x = &(asset[4 * sizeof(uint32_t)]);
		public_key_y = public_key_x + cri_pke_get_curve_length(curve);
		private_key = public_key_y + cri_pke_get_curve_length(curve);
		asset_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);

		status = generate_ec_private_key(curve, private_key);
		if (status) goto out;

		dhexdump("private key", private_key, cri_pke_get_curve_length(curve));

		status = ecdsa_keygen(curve, private_key, public_key_x, public_key_y);
		if (status) goto out;

		dhexdump("ECDSA public key: x", public_key_x, cri_pke_get_curve_length(curve));
		dhexdump("ECDSA public key: y", public_key_y, cri_pke_get_curve_length(curve));

		status = cri_pke_ecc_pairwise_consistency_check(curve,
				FIPS_TYPE_ECDSA_KEYPAIR, private_key,
				public_key_x, public_key_y);

		if (status) {
			destroy_workcontext_and_halt(status);
		}

		status = cri_full_ecdsa_public_key_validation(curve, public_key_x, public_key_y);
		if (status) {
			destroy_workcontext_and_halt(status);
		}

		status = fips_write_asset_to_teefs(state,
				(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
				h->params[1].memref.size, asset, asset_length);
		if (status) goto out;

		memset(private_key, 0x00, cri_pke_get_curve_length(curve));
		SET_ASSET_INTERNAL_FLAG_IN_ASSET(asset, FIPS_EXTERNAL_ASSET);
		SET_ASSET_TYPE_IN_ASSET(asset, FIPS_TYPE_ECDSA_PUBLIC_KEY);
		asset_length = GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve);

		break;

	case FIPS_TYPE_ECDH_KEYPAIR:
		dprintk("Generating ECDH key\n");

		public_key_x = GET_ECDH_PUBLIC_KEY_FROM_ASSET(asset);
		private_key = GET_ECDH_PRIVATE_KEY_FROM_ASSET(asset, curve);

		status = generate_ec_private_key(curve, private_key);
		if (status) goto out;

		dhexdump("private key", private_key, cri_pke_get_curve_length(curve));

		status = ecdh_keygen(curve, private_key, public_key_x);
		if (status) goto out;

		dhexdump("ECDH public key", public_key_x, cri_pke_get_curve_length(curve));


		status = cri_pke_ecc_pairwise_consistency_check(curve,
				FIPS_TYPE_ECDH_KEYPAIR, private_key,
				public_key_x, NULL);

		if (status) {
			destroy_workcontext_and_halt(status);
		}

		asset_length = GET_ECDH_KEYPAIR_ASSET_SIZE(curve);
		status = fips_write_asset_to_teefs(state,
				(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
				h->params[1].memref.size, asset, asset_length);
		if (status) goto out;

		memset(private_key, 0x00, cri_pke_get_curve_length(curve));
		SET_ASSET_INTERNAL_FLAG_IN_ASSET(asset, FIPS_EXTERNAL_ASSET);
		SET_ASSET_TYPE_IN_ASSET(asset, FIPS_TYPE_ECDH_PUBLIC_KEY);
		asset_length = GET_ECDH_PUBLIC_KEY_ASSET_SIZE(curve);

		break;

	default:
		dprintk("Algorithm type not known\n");
		status = -EPERM;
		goto out;
	}

	status = fips_write_to_shared_memory(asset + GET_HEADER_SIZE() + sizeof(uint32_t),
			asset_length - GET_HEADER_SIZE() - sizeof(uint32_t), h, 2);

out:
	destroy_workcontext(status);
	return status;
}
