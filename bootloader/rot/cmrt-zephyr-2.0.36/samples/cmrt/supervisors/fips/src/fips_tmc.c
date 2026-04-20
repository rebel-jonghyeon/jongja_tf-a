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
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/tmc.h>

#include <cri/cmrt/sac.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_crypto.h"
#include "cri_utils.h"

static bool is_config_word_valid(uint32_t value)
{
	enum {
		EMPTY_VAL = 0,
		INVALID_VAL = 0xffffffff
	};
	return (value != EMPTY_VAL) && (value != INVALID_VAL);
}

int32_t init_tmc_with_otp_config(void)
{
	int res = 0;
	static bool initialized;
	if (!initialized) {
		cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
		if (!cmrt_is_valid(omc)) {
				dprintk("Failed to open OMC\n");
				return -ENODEV;
		}
		cmrt_tmc_init_params_t tmc_params = {
			.control = 0,
			.config = 0,
			.detune_limit = 8
		};
		res = cmrt_omc_read(omc, FIPS_OTP_TMC_PARAM_OFFSET,
				    &tmc_params.control, sizeof(uint32_t));
		if (res == 0) {
			res = cmrt_omc_read(omc, FIPS_OTP_TMC_PARAM_OFFSET + 4,
					    &tmc_params.config, sizeof(uint32_t));
		}
		cmrt_omc_close(omc);

		cmrt_tmc_init_params_t *p = NULL;
		if (is_config_word_valid(tmc_params.control) &&
		    is_config_word_valid(tmc_params.config)) {
			/* Set only if both are valid */
			p = &tmc_params;
			dprintk("TMC control:0x%x config:0x%x\n",
				tmc_params.control, tmc_params.config);
		}
		cmrt_tmc_t tmc = cmrt_tmc_open(CRI_O_SYNC, p);
		if (!cmrt_is_valid(tmc)) {
			dprintk("Failed to init TMC\n");
			res = -EIO;
		} else {
			cmrt_tmc_close(tmc);
		}
		initialized = true;
	}
	return res;
}

int32_t cri_get_randomness(uint8_t *buffer, size_t size)
{
	int status;
	status = 0;

	uint32_t q;
	uint32_t r;
	uint32_t i;

	q = size >> 4;
	r = size & 0xf;

	cmrt_tmc_t tmc = cmrt_tmc_open(CRI_O_SYNC, NULL);
	if (!cmrt_is_valid(tmc)) {
		status = -EIO;
		goto out;
	}

	for (i = 0; i < q; i++) {
		int res = cmrt_tmc_command(tmc, CMRT_TMC_GENERATE, buffer + (i * 16), 16);
		if (res) {
			dprintk("Failed to run cri_tmc_generate %d!\n", res);
			status = -EIO;
			goto out1;
		}
	}

	if (r != 0) {
		int res = cmrt_tmc_command(tmc, CMRT_TMC_GENERATE, buffer + (i * 16), r);
		if (res) {
			dprintk("Failed to run cri_tmc_generate %d!\n", res);
			status = -EIO;
			goto out1;
		}
	}

out1:
	cmrt_tmc_close(tmc);
out:
	return status;
}

int32_t fips_get_randomness(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status;

	status = 0;
	dprintk("FIPS_SERVICE_GET_TRNG\n");
	CHECK_COMMAND(FIPS_SERVICE_GET_TRNG);

	if (h->params[0].memref.size == 0) {
		status = -EINVAL;
		goto out;
	}

	status = cri_get_randomness((uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				    h->params[0].memref.size);
	if (status) {
		goto out;
	}

out:
	destroy_workcontext(sizeof(uint32_t));
	return status;
}
