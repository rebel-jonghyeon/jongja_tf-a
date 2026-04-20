/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <ctype.h>
#include <smcalls.h>
#include <sac.h>

#include <cri/cmrt/omc.h>
#include <cri/cmrt/omc_reg.h>
#include <cri/cmrt/fmc.h>

#include <tee_client_api.h>
#include <tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"

int32_t fips_create_user(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	dprintk("FIPS_SERVICE_CREATE_USER\n");
	CHECK_COMMAND(FIPS_SERVICE_CREATE_USER);

	cmrt_omc_root_t omc_root = {
		.id.hash = {
			0x85, 0x5f, 0x8d, 0x89, 0x1f, 0x53, 0xf5, 0x63,
			0x6f, 0xd1, 0x0e, 0x22, 0xde, 0x11, 0xd5, 0xd4,
			0x6f, 0xcd, 0x7e, 0xf4, 0xb7, 0xad, 0x6a, 0xee,
			0x01, 0x61, 0xb4, 0x62, 0x38, 0x7a, 0xb3, 0x22
		},
		.perm.slot_perm.val = 0xFFFFFF1F,
		.perm.key_perm.val = 0xFFFFFE07,
		.perm.feature_perm.val = 0x7FFFFFFF,
		.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
		.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
		.perm.software_perm.val = 0xFFFFFFFF,
	};

	if ((h->params[0].value.b != 0) ||
		(h->params[0].value.a == FIPS_OWNER_CRYPTO_OFFICER) ||
		(h->params[0].value.a == FIPS_OWNER_ANONYMOUS) ||
		(h->params[0].value.a >= CONFIG_CRI_OMC_ROOTS_NUM) ||
		(h->params[1].memref.size != 32)) {
		status = -EINVAL;
		goto out;
	}

	dprintk("call cri_mcall_create_root(index %d)\n", h->params[0].value.a);

	memcpy(omc_root.id.hash, (uint8_t *) (h->params[1].memref.offset+SAC_MEMORY_BASE), h->params[1].memref.size);
	status = cri_mcall_create_root(h->params[0].value.a, &omc_root);
	if (status)	{
		goto out;
	}

out:
	destroy_workcontext(sizeof(uint32_t));
	return status;
}

int32_t fips_delete_user(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	dprintk("FIPS_SERVICE_DELETE_USER\n");
	CHECK_COMMAND(FIPS_SERVICE_DELETE_USER);

	if ((h->params[0].value.b != 0) ||
		(h->params[0].value.a == FIPS_OWNER_CRYPTO_OFFICER) ||
		(h->params[0].value.a == FIPS_OWNER_ANONYMOUS) ||
		(h->params[0].value.a >= CONFIG_CRI_OMC_ROOTS_NUM)) {
		status = -EINVAL;
		goto out;
	}

	status = cri_mcall_obliterate_root(h->params[0].value.a);

out:
	destroy_workcontext(0);
	return status;
}

/*
int32_t test_otp(void)
{
	int res;

	dprintk("Testing OTP\n");
	cmrt_omc_root_t rootje;

	cri_otp_t omc = cri_otp_open(0);
	if (!cri_is_valid(omc)) {
		dprintk("Failed to open omc\n");
		return -EIO;
	}

	int i;

	for (i = 0; i < 8; i++) {
		res = cri_otp_read_root(omc, i, &rootje);
		dprintk("Root reading results of root %d: %d\n", i, res);
		hexdump(rootje.id.hash, 32);
		dprintk("Slot permissions root %d:\n", i);
		hexdump(&(rootje.perm.slot_perm), 8);
		dprintk("Feature permissions root %d:\n", i);
		hexdump(&(rootje.perm.feature_perm), 4);
		dprintk("Key permissions root %d:\n", i);
		hexdump(&(rootje.perm.key_perm), 8);
		dprintk("Software permissions root %d:\n", i);
		hexdump(&(rootje.perm.software_perm), 4);
		dprintk("SW OTP permissions 0 root %d:\n", i);
		hexdump(&(rootje.perm.sw_otp_perm[0]), 4);
		dprintk("Region 0: high:%04x\n", (rootje.perm.sw_otp_perm[0].s.upper_and_write)&0x3fff);
		dprintk("Region 0: low:%04x\n", (rootje.perm.sw_otp_perm[0].s.lower_and_read)&0x3fff);
		dprintk("Region 0: read bit:%d\n", ((rootje.perm.sw_otp_perm[0].s.lower_and_read)&0x8000)>>15);
		dprintk("Region 0: write bit:%d\n", ((rootje.perm.sw_otp_perm[0].s.upper_and_write)&0x8000)>>15);
		dprintk("Region 1: high:%04x\n", (rootje.perm.sw_otp_perm[1].s.upper_and_write)&0x3fff);
		dprintk("Region 1: low:%04x\n", (rootje.perm.sw_otp_perm[1].s.lower_and_read)&0x3fff);
		dprintk("Region 1: read bit:%d\n", ((rootje.perm.sw_otp_perm[1].s.lower_and_read)&0x8000)>>15);
		dprintk("Region 1: write bit:%d\n", ((rootje.perm.sw_otp_perm[1].s.upper_and_write)&0x8000)>>15);
		dprintk("SW OTP permissions 1 root %d:\n", i);
		hexdump(&(rootje.perm.sw_otp_perm[0]), 4);
	}

	cri_otp_close(omc);

	dprintk("Testing OTP done\n");

	return 0;
}
*/
