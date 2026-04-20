/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include <cri/cmrt/fmc.h>
#include <cri/cmrt/fmc_reg.h>
#include "common.h"

enum {
	DISABLE_DEBUG = 0,
	ENABLE_DEBUG = 1
};

typedef struct {
	u32_t mode;
} debug_args_t;


static int set_debug_mode(int on)
{
	info("feature_set_debug_operations\n");
	cri_fmc_t fmc = cri_fmc_open();

	if (!cri_is_valid(fmc)) {
		err("Can't open FMC\n");
		return -ENODEV;
	}
	/* can also use cri_fmc_set_debug_mode(fmc) */
	int rc = cri_fmc_feature_write(fmc,
				       FMC_TDV_OFFSET,
				       !!on,
				       0xffffffff);
	if (rc)
		err("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}


static int enable_debug_mode(void *input, u32_t in_used,
			     void *output, u32_t *out_used, u32_t out_size)
{
	debug_args_t *dbg = (debug_args_t *)input;
	debug_args_t *argsout = (debug_args_t *)output;
	info("Enable Debug Mode: %d\n", dbg->mode);

	info("input data size %u, output buffer size %u\n", in_used, out_size);

	if (in_used > out_size) {
		err("Output buffer is too small %u vs %u\n",
		    in_used, *out_used);
		return -ENOSPC;
	}

	switch (dbg->mode) {
	case ENABLE_DEBUG:
	case DISABLE_DEBUG:
		break;
	default:
		err("Unknown command: %d\n", dbg->mode);
		return -ENOTSUP;
	}
	int res;
	if (dbg->mode == ENABLE_DEBUG) {
		info("Enable DEBUG\n");
		res = set_debug_mode(1);
	} else {
		info("Disable DEBUG\n");
		res = set_debug_mode(0);
	}
	if (res) {
		err("Set debug mode %d failed: %d\n", dbg->mode, res);
	}
	info("FMC debug set operation done\n");

	argsout->mode = res;
	*(debug_args_t *)output = *argsout;
	*out_used = sizeof(*argsout);
	return res;
}

const cmd_t cmd_enable_debug = { CMDID_SET_DEBUG, "Debug",
				"Enable/Disable Debug mode", enable_debug_mode
};
