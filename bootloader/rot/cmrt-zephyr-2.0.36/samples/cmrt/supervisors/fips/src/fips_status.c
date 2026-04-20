/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <smcalls.h>

#include <cri/cmrt/dd.h>
#include <cri/cmrt/omc.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/sic_reg.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt/sic_reg.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cri_utils.h"

const char version_info[] Z_GENERIC_SECTION("version.1") =
	SUPERVISOR_VERSION_INFO;

extern cri_sic_t sic;


int32_t fips_show_status(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	char *str = workcontext+4;

	dprintk("FIPS_SERVICE_SHOW_STATUS\n");
	CHECK_COMMAND(FIPS_SERVICE_SHOW_STATUS);

	if (h->params[3].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	/* BUILDER_VERSION */
	uint32_t builder_version = cri_read_reg(CMRT_SIC_BASE, R_BUILDER_VERSION);
	dprintk("BUILDER_VERSION = 0x%08x\n", builder_version);
	sprintf(str, "%08x", builder_version);
	status = fips_write_to_shared_memory(str, strlen(str), h, 0);

	/* sboot version */
	char sboot_version[64];
	size_t sboot_verlen = sizeof(sboot_version);
	status = cri_mcall_get_img_version(CMRT_SBOOT_VERSION,
					   &sboot_version, &sboot_verlen);
	if (status != 0) {
		goto out;
	}
	if (sboot_verlen <= 0 || sboot_verlen > sizeof(sboot_version)) {
		status = -EINVAL;
		goto out;
	}

	dprintk("Sboot version: %s\n", sboot_version);
	status = fips_write_to_shared_memory(sboot_version, sboot_verlen, h, 1);
	if (status != 0) {
		goto out;
	}
	/* supervisor version */
	dprintk("Supervisor version: %s\n", version_info);
	status = fips_write_to_shared_memory(version_info, sizeof(version_info), h, 2);
	if (status != 0) {
		goto out;
	}
	/* FIPS_MODE */
	h->params[3].value.a = cri_read_reg(CMRT_SIC_BASE, R_FIPS_MODE);
	dprintk("FIPS register: %i\n", h->params[3].value.a);

out:
	destroy_workcontext(9 + sizeof(uint32_t));
	return status;
}
