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

int32_t fips_generate_symmetric_key(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status;

	uint8_t *asset = workcontext+4;
	uint8_t *key;

	uint32_t asset_length = 0;
	uint32_t total_length = 4;
	uint32_t asset_type;

	size_t length = 0;

	status = 0;
	dprintk("FIPS_SERVICE_GEN_SYMM_KEY\n");
	CHECK_COMMAND(FIPS_SERVICE_GEN_SYMM_KEY);

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(h->params[0].value.b)) == 0) {
		dprintk("The currently logged in user cannot own this key\n");
		status = -EACCES;
		goto out;
	}

	asset_type = GET_ASSET_TYPE(h->params[0].value.b);
	SET_FIPS_HEADER(asset,
			GET_ASSET_OWNER(h->params[0].value.b),
			asset_type);

	key = asset + GET_HEADER_SIZE();
	asset_length = GET_HEADER_SIZE();

	length = h->params[0].value.a / 8;

	((uint32_t *) key)[0] = length;
	asset_length += length + sizeof(uint32_t);
	total_length += asset_length;

	/* Other asset types are checked in fips_check_valid_key_length below */
	if (asset_type == FIPS_TYPE_SECRET) {
		status = -EINVAL;
		goto out;
	}

	status = fips_check_valid_key_length(asset_type, length);
	if (status) {
		goto out;
	}

	status = cri_get_randomness(key + sizeof(uint32_t), length);
	if (status) {
		status = -EIO;
		goto out;
	}

	status = fips_write_asset_to_teefs(state,
			(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, asset, asset_length);
	if (status) {
		goto out;
	}

out:
	dprintk("Zero size: %i\n", total_length + sizeof(uint32_t));
	destroy_workcontext(total_length);
	return status;
}
