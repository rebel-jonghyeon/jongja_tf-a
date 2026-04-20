/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate how to turn on debug mode.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <cri/cmrt.h>
#include "crisyscall-user.h"
#include <cri/cmrt/fmc.h>
#include "crilog-user.h"

int main(void)
{
	c_log("Sample (enable debug) container starting...\n");
	cri_fmc_t fmc = cri_fmc_open();

	if (!cri_is_valid(fmc)) {
		c_log("Can't open FMC\n");
		return 1;
	}
	int res = cri_fmc_set_debug_mode(fmc);
	cri_fmc_close(fmc);
	if (res == 0) {
		c_log("Entering debug mode\n");
	}

	return res;
}
