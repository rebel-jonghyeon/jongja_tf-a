/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>
#include <cri/cmrt/tmc.h>

#include "common.h"

typedef struct {
	u32_t size;
} random_args_t;

/* Command to respond back with random data of requested size. */

static int get_random(void *input, u32_t in_used,
		      void *output, u32_t *out_used, u32_t out_size)
{
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;

	plog_reset();
#endif
	random_args_t *args;
	info("Random run %u %u\n", in_used, out_size);

	if (in_used < sizeof(*args)) return -EINVAL;
	if (out_size < sizeof(*args)) return -ENOSPC;

	args = (random_args_t *)input;

	info("Requested data size is %d\n", args->size);

	int status = 0;

	u32_t q, r;

	q = args->size >> 4;
	r = args->size & 0xf;
#ifdef CONFIG_SV_PERF_MEAS
	plog_set_ref();
#endif
	cri_tmc_t tmc = cri_tmc_open(CRI_O_SYNC);
#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("TMC_cri_tmc_open,%d,%u", args->size, cycles);
#endif
	if (!cri_is_valid(tmc)) {
		status = -EIO;
		goto out;
	}

	u32_t i;

	for (i = 0; i < q; i++) {
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		int res = cri_tmc_generate(tmc, output + (i * 16), 16);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("TMC_cri_tmc_generate,%d,%u", args->size, cycles);
#endif
		if (res) {
			err("Failed to run cri_tmc_generate %d!\n", res);
			status = -EIO;
			goto out1;
		}
	}

	if (r != 0) {
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		int res = cri_tmc_generate(tmc, output + (i * 16), r);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("TMC_cri_tmc_generate,%d,%u", args->size, cycles);
#endif
		if (res) {
			err("Failed to run cri_tmc_generate %d!\n", res);
			status = -EIO;
			goto out1;
		}
	}

out1:
#ifdef CONFIG_SV_PERF_MEAS
	plog_set_ref();
#endif
	cri_tmc_close(tmc);
#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("TMC_cri_tmc_close,%d,%u", args->size, cycles);
#endif
out:
	if (status) {
		info("TMC Random data generation failed for size %u\n", args->size);
	} else {
		info("TMC Random data generation done for size %u\n", args->size);
		*out_used = args->size;
	}
	return status;
}


const cmd_t cmd_random = { CMDID_RANDOM, "Random",
			   "Generate Random data", get_random };
