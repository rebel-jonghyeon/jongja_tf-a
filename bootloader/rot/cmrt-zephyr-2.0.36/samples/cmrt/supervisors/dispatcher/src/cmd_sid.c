/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <cri/cmrt/sid.h>
#include <cri/cmrt/sic.h>
#include "common.h"

/* Commands to exercise SID and demonstrate how it can be used to
 * watch interrupts. */

static cri_sid_t sid;
static uint32_t irqs;

typedef struct {
	u32_t subcmd;
	u32_t irqs;
} sid_args_t;

static int do_sid_watch(sid_args_t *args)
{
	if (!cri_is_valid(sid)) {
		sid = cri_sid_open(0, SOC_INTERRUPT_IN_MASK);
		if (!cri_is_valid(sid)) {
			err("cri_sid_open() failed\n");
			return -EIO;
		}
	}
	info("sid watch irqs 0x%08x\n", args->irqs);
	int res = cri_sid_watch(sid, args->irqs, SOC_INTERRUPT_IN_MASK, &irqs);
	if (res < 0) {
		err("cri_sid_watch(0x%08x, 0x%08x) failed: %d\n",
		    args->irqs, SOC_INTERRUPT_IN_MASK, res);
		return res;
	}
	return 0;
}

static int do_sid_get_irqs(sid_args_t *args)
{
	if (!cri_is_valid(sid)) {
		err("sid not opened\n");
		return -EIO;
	}
	args->irqs = 0;
	cri_handle_t handles = sid;
	int res = cri_wait(1, &handles, 1000);
	if (res > 0) {
		res = cri_sid_sync(sid);
		if (res < 0) {
			err("cri_sid_sync() failed: %d\n", res);
			return res;
		}
		args->irqs = irqs;
	}
	return 0;
}

static int sid_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
	sid_args_t *args;

	printk("sid run %u %u\n", in_used, out_size);
	if (in_used < sizeof(*args)) {
		return -EINVAL;
	}
	if (out_size < sizeof(*args)) {
		return -ENOSPC;
	}

	args = (sid_args_t *)input;
	int res;
	printk("sid run subcmd: %d\n", args->subcmd);
	switch (args->subcmd) {
	case 1:
		res = do_sid_watch(args);
		break;
	case 2:
		res = do_sid_get_irqs(args);
		break;
	default:
		res = -EINVAL;
		break;
	}
	*(sid_args_t *)output = *args;
	*out_used = sizeof(*args);
	return res;
}

const cmd_t cmd_sid = { CMDID_SID, "SID", "SID commands", sid_run };
