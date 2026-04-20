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

int32_t fips_ecdsa_pk_test(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	uint32_t key_length = 0;
	uint32_t total_length = 0;

	uint8_t *key;
	uint8_t *public_key_x;
	uint8_t *public_key_y;

	cri_ecc_curve_t curve = NULL;

	dprintk("FIPS_SERVICE_ECDSA_PK_TEST\n");
	CHECK_COMMAND(FIPS_SERVICE_ECDSA_PK_TEST);

	key = workcontext + sizeof(uint32_t);

	/* get maximum asset length */
	curve = cri_pke_get_curve(CRI_ECC_CURVE_NIST_P521);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EIO;
		goto out;
	}
	key_length = GET_ECDSA_KEYPAIR_ASSET_SIZE(curve);

	status = fips_read_from_shared_memory(h, 0, key, &key_length);
	if (status) goto out;

	curve = cri_pke_get_fips_curve(((uint32_t *) key)[0]);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EINVAL;
		goto out;
	}

	public_key_x = key + sizeof(uint32_t);
	public_key_y = public_key_x + cri_pke_get_curve_length(curve);

	status = cri_full_ecdsa_public_key_validation(curve, public_key_x, public_key_y);

out:
	total_length = GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve);
	destroy_workcontext(total_length + sizeof(uint32_t));
	return status;
}
