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

#include <errno.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/ktc.h>
#include <cri/cmrt/sac.h>

#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"

static int ok_to_transport_with_ktc(uint8_t metadata)
{
	switch (metadata) {
	case FIPS_TYPE_AES:
	case FIPS_TYPE_HMAC_SHA224:
	case FIPS_TYPE_HMAC_SHA256:
	case FIPS_TYPE_HMAC_SHA384:
	case FIPS_TYPE_HMAC_SHA512:
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_TYPE_HMAC_SHA3_224:
	case FIPS_TYPE_HMAC_SHA3_256:
	case FIPS_TYPE_HMAC_SHA3_384:
	case FIPS_TYPE_HMAC_SHA3_512:
#endif
	case FIPS_TYPE_AES_GCM_ENCRYPT:
	case FIPS_TYPE_AES_GCM_DECRYPT:
	case FIPS_TYPE_SECRET:
		return 1;
	default:
		return 0;
	}
}

int32_t fips_service_export_ktc(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{
	int status;
	teefs_command_t cmd;

	fips_asset_identifier *toexport;

	dprintk("FIPS_SERVICE_EXPORT_KEY_KTC\n");
	CHECK_COMMAND(FIPS_SERVICE_EXPORT_KEY_KTC);

	if ((h->params[0].value.a > 15) || (h->params[0].value.b != 0)) {
		status = -EINVAL;
		goto out;
	}

	toexport = (fips_asset_identifier *) (h->params[2].memref.offset + SAC_MEMORY_BASE);

	if (toexport->location == FIPS_ASSET_DYNAMIC) {
		cmd = READ_FILE_RAM;
	} else if (toexport->location == FIPS_ASSET_STATIC) {
		cmd = READ_FILE_OTP;
	} else {
		status = -ENOENT;
		goto out;
	}

	status = process_teefs_request(cmd, toexport->asset_name_length,
				       toexport->asset_name, g_inout_buffer,
				       &g_inout_buffer_len);
	if (status) {
		dprintk("Asset read status: %d\n", status);
		goto out;
	}

	/* Due to the limited types of assets which can be exported over the ktc, this works */
	fips_asset *asset_toexport = (fips_asset *) g_inout_buffer;

	if (!ok_to_transport_with_ktc(GET_ASSET_TYPE_FROM_ASSET(asset_toexport))) {
		dprintk("Wrong type for exporting over the ktc\n");
		status = -EINVAL;
		goto out;
	}

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(asset_toexport->metadata)) == 0) {
		dprintk("The currently logged in user cannot use the asset just opened\n");
		status = -EACCES;
		goto out;
	}

	dprintk("Opening ktc\n");
	cri_ktc_t ktc = cri_ktc_open();
	if (!cri_is_valid(ktc)) {
		printk("Cannot open %s\n", CONFIG_CRI_KTC_NAME);
		status = -EIO;
		goto out;
	}

	uint32_t *assetdata = (uint32_t *) (g_inout_buffer + 12);

	ktc_cmd_t ktc_cmd;
	ktc_cmd.destination = h->params[0].value.a;
	ktc_cmd.metadata[0] = h->params[1].value.a;
	ktc_cmd.metadata[1] = h->params[1].value.b;
	ktc_cmd.key_size = assetdata[0];
	ktc_cmd.key = &assetdata[1];

	status = cri_ktc_export_key(ktc, &ktc_cmd);
	if (status) {
		status = -EIO;
		printk("Key export failed %d\n", status);
	} else {
		printk("Key transfer success\n");
	}

	dprintk("Closing ktc\n");
	cri_ktc_close(ktc);

out:
	destroy_workcontext(0);
	return status;
}
