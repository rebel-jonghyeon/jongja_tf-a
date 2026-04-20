/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <device.h>
#include <cri/cmrt/sic.h>

#include <cri/cmrt/fmc.h>

#include "common.h"
#define DEBUG

#define BUFSIZE 256

typedef enum {
	FMC_CMD_FEATURE_SET = 0,
	FMC_CMD_FEATURE_GET = 1,
	FMC_CMD_FEATURE_SYS_OUT = 4,
} fmc_cmd_t;

typedef struct fmc_command {
	fmc_cmd_t cmd;
	u32_t offs;
	u32_t data;
	u32_t mask;
} fmc_args_t;

static int feature_set(u32_t addr, u32_t data, u32_t mask)
{
	info("feature_set_operations\n");
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		err("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_feature_write(fmc, addr, data, mask);
	if (rc)
		err("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

static int feature_get(u32_t addr, u32_t *data)
{
	info("feature_get_operations\n");
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		err("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_feature_read(fmc, addr, data);
	if (rc)
		err("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

static int fmc_run(void *input, u32_t in_used,
		     void *output, u32_t *out_used, u32_t out_size)
{

	info("fmc_run:\n");
	fmc_args_t *args = (fmc_args_t *)input;
	fmc_args_t *argsout = (fmc_args_t *)output;
	if (out_size < sizeof(*argsout)) {
		err("output buffer too small\n");
		return -ENOSPC;
	}
	u32_t fmc_addr;
	fmc_addr = args->offs * sizeof(u32_t);
	info("fmc_addr:0x%x\n", fmc_addr);
	int res = 0;
	info("FMC command: cmd = %d, offs = 0x%x, data = 0x%x, mask = 0x%x\n",
		args->cmd, args->offs, args->data, args->mask);
	*argsout = *args;
	switch (args->cmd) {
	case FMC_CMD_FEATURE_SET:
		res = feature_set(fmc_addr, args->data, args->mask);
		info("FMC_CMD_FEATURE_SET %d\n", res);
		break;
	case FMC_CMD_FEATURE_GET:
		res = feature_get(fmc_addr, &args->data);
		info("FMC_CMD_FEATURE_GET %d\n", res);
		break;
	case FMC_CMD_FEATURE_SYS_OUT:
		res = feature_set(fmc_addr, args->data, args->mask);
		info("FMC_CMD_FEATURE_SYS_OUT %d\n", res);
		break;
	default:
		err("**** Unknown command ****\n");
		return EINVAL;
		break;
	}
	if (res) {
		err("fmc operation failed: %d\n", res);
		snprintf((char *)output, BUFSIZE, "Failed. res %d\n", res);
	} else if (args->cmd == FMC_CMD_FEATURE_SYS_OUT) {
		info("SET_FPGA_TEST %d\n", res);
		*(fmc_args_t *)output = *args;
	} else {
		char arr_state[20];
		snprintf(arr_state, sizeof(arr_state), "%s %s %s %s",
			args->data & 8 ? "ON" : "OFF",
			args->data & 4 ? "ON" : "OFF",
			args->data & 2 ? "ON" : "OFF",
			args->data & 1 ? "ON" : "OFF");
		info("states: %s\n", arr_state);
		snprintf((char *)output, BUFSIZE, "OK. %s\n", arr_state);

	}
	info("FMC operation done\n");
	*out_used = BUFSIZE;
	return 0;
}

const cmd_t cmd_fmc = { CMDID_FMC, "FMC",
			  "Sample FMC API", fmc_run };
