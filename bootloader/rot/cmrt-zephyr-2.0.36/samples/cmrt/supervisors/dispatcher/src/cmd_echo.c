/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include "common.h"

/* Simple command to echo back input data. */

static int echo_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
	info("Echo command: input data size %u output buffer size %u\n",
	     in_used, out_size);

	if (in_used > out_size) {
		err("Output buffer is too small %u vs %u\n",
		    in_used, *out_used);
		return -ENOSPC;
	}

	memcpy(output, input, ROUND_UP(in_used, 4));
	*out_used = in_used;
	return 0;
}

const cmd_t cmd_echo = { CMDID_ECHO, "Echo",
			 "Simply return input data", echo_run };
