/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_math.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"

static void SHIFT_LEFT(uint32_t *x,
		       size_t len)
{
	int32_t j;

	for (j = (len)-1; j > 0; j--) {
		x[j] = (x[j] << 1) + (x[j - 1] >> 31);
	}
	x[0] <<= 1;
}

static void SHIFT_RIGHT(uint32_t *x,
			size_t len)
{
	size_t j;

	for (j = 0; j < (len)-1; j++) {
		x[j] = (x[j] >> 1) + (x[j + 1] << 31);
	}
	x[(len)-1] >>= 1;
}

int cmrt_pke_gcd(uint32_t *addrA,
		uint32_t *addrB,
		size_t length,
		uint32_t **gcd)
{
	int ret = 0;

	uint32_t *x;
	uint32_t *y;
	uint32_t *t = NULL;

	uint32_t g;
	uint32_t i;

	uint8_t difference;
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t cmd_length = length;
#else /* 64-bit */
	uint32_t cmd_length = ((length - 1) / 2) + 1;
#endif

	x = addrA;
	y = addrB;
	g = 0;
	while (((x[0] & 1) == 0) && ((y[0] & 1) == 0)) {
		g++;
		SHIFT_RIGHT(x, length);
		SHIFT_RIGHT(y, length);
	}

	do {
		while ((x[0] & 1) == 0) {
			SHIFT_RIGHT(x, length);
		}

		while ((y[0] & 1) == 0) {
			SHIFT_RIGHT(y, length);
		}

		ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(x), cmd_length);
		ISSUE_MAU_COMMAND(COMPARE, MAU_SRAM_ADDRESS(y), cmd_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		difference = MAU_GET_COMPARE_RESULT();
		if (difference == MAU_COMP_ERROR) {
			ret = -EIO;
			goto err;
		}

		if (difference == MAU_LT) {
			t = x;
			x = y;
			y = t;
		}

		ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(x), cmd_length);
		ISSUE_MAU_COMMAND(INT_SUB, MAU_SRAM_ADDRESS(y), cmd_length);
		ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(x), cmd_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		SHIFT_RIGHT(x, length);

		ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(x), cmd_length);
		ISSUE_MAU_COMMAND(COMPARE, R_MAU_ZERO, cmd_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		difference = MAU_GET_COMPARE_RESULT();
		if (difference == MAU_COMP_ERROR) {
			ret = -EIO;
			goto err;
		}
	} while (difference != 0);

	for (i = 0; i < g; i++) {
		SHIFT_LEFT(y, length);
	}
	*gcd = y;

err:
	return ret;
}
