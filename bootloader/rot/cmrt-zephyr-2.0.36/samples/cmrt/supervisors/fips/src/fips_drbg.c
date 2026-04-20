/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/tmc.h>

#include <cri/cmrt/fips/fips_types.h>

#include "fips.h"
#include "cri_utils.h"

#define TMC_READ_OUTPUT 0xFF
#define TMC_CLOSE 0xFE

static cmrt_tmc_t tmc_drbg = CMRT_INVALID_HANDLE;

int32_t fips_drbg(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	uint32_t buffer[TMC_OUTPUT_REGS] = {0};
	uint32_t length = 0;

	uint8_t bytes_buffer[TMC_OUTPUT_REGS * sizeof(uint32_t)] = {0};

	dprintk("FIPS_SERVICE_DRBG\n");

	if (h->params[0].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	switch (h->params[0].value.a) {
	case 0:
		tmc_drbg = cmrt_tmc_open(0, NULL);
		if (!cmrt_is_valid(tmc_drbg)) {
			status = -EIO;
		}
		break;

	case TMC_READ_OUTPUT:
		length = h->params[1].memref.size;

		status = cmrt_tmc_sync(tmc_drbg);
		if (status) { goto out; }

		reverse_words(buffer, length / sizeof(uint32_t), bytes_buffer);

		status = fips_write_to_shared_memory(bytes_buffer, length, h, 1);
		break;

	case TMC_CLOSE:
		cmrt_tmc_close(tmc_drbg);
		break;

	case TMC_CONTROL_INSTANTIATE:
	case TMC_CONTROL_UNINSTANTIATE:
		status = cmrt_tmc_command(tmc_drbg, h->params[0].value.a,
					  NULL, 0);
		break;
	case TMC_CONTROL_GENERATE:
	case TMC_CONTROL_RESEED_GENERATE:
		length = h->params[1].memref.size;
		status = cmrt_tmc_command(tmc_drbg, h->params[0].value.a,
					  buffer, length);
		break;

	default:
		status = -EINVAL;
	}

out:
	return status;
}
