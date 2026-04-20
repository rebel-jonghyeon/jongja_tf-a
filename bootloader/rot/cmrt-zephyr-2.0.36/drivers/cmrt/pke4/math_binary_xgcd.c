/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include <stdio.h>

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

static void SHIFT_RIGHT(uint32_t *x,
			size_t len)
{
	size_t j;

	for (j = 0; j < (len)-1; j++) {
		x[j] = (x[j] >> 1) + (x[j + 1] << 31);
	}
	x[(len)-1] >>= 1;
}

static inline int modmath_compare_yx(uint32_t *y, uint32_t *x, size_t length, uint8_t *difference)
{
	int ret;

	ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(y), length);
	ISSUE_MAU_COMMAND(COMPARE, MAU_SRAM_ADDRESS(x), length);

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	*difference = MAU_GET_COMPARE_RESULT();
err:
	return ret;
}

int cmrt_pke_binary_xgcd(const uint8_t slot_x,
			const uint8_t slot_y,
			const uint8_t slot_c,
			const size_t len,
			uint8_t slot_a,
			uint8_t slot_b)
{
	int ret;

	uint32_t bit_length = len * 8;;

	uint32_t *x = pke_addr(binary_xgcd_x, NULL, bit_length);
	uint32_t *y = pke_addr(binary_xgcd_y, NULL, bit_length);
	uint32_t *k = NULL;

	uint32_t *u = pke_addr(binary_xgcd_u, NULL, bit_length);
	uint32_t *v = pke_addr(binary_xgcd_v, NULL, bit_length);
	uint32_t *s = pke_addr(binary_xgcd_s, NULL, bit_length);
	uint32_t *t = pke_addr(binary_xgcd_t, NULL, bit_length);

	uint32_t c;
	uint32_t g;

	uint8_t difference;

#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = len / sizeof(uint32_t);
	uint32_t swords = length;
#else /* 64-bit */
	uint32_t length = ((len - 1) / sizeof(uint64_t)) + 1;
	uint32_t swords = length * 2;
#endif

	static const uint32_t cmd_setup_xgcd[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(binary_xgcd_u)),
		SLOT_CMD(STORE,         SLOT(binary_xgcd_t)),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(binary_xgcd_v)),
		SLOT_CMD(STORE,         SLOT(binary_xgcd_s)),
	};

	ret = cmrt_pke_mau_command_sequence(cmd_setup_xgcd, sizeof(cmd_setup_xgcd)/sizeof(uint32_t), length);
	if (ret) {
		goto err;
	}

	ISSUE_MAU_COMMAND(SET_MAND, SLOT(binary_xgcd_x), length);
	ISSUE_MAU_COMMAND(COPY, SLOT(slot_x), length);
	ISSUE_MAU_COMMAND(SET_MAND, SLOT(binary_xgcd_y), length);
	ISSUE_MAU_COMMAND(COPY, SLOT(slot_y), length);
	ISSUE_MAU_COMMAND(SET_PARAMS, SLOT(slot_c), length);

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	g = 0;
	while (((x[0] & 1) == 0) && ((y[0] & 1) == 0)) {
		g++;
		SHIFT_RIGHT(x, swords);
		SHIFT_RIGHT(y, swords);
	}

	c = 0;
	while ((x[0] & 1) == 0) {
		SHIFT_RIGHT(x, swords);
		c = c + 1;
	}
	t[c / 32] = 1 << (c % 32);

	ret = modmath_compare_yx(y, x, length, &difference);
	if (ret) {
		goto err;
	}

	if (difference == MAU_COMP_ERROR) {
		goto err;
	}

	while (difference != MAU_EQ) {
		if ((y[0] & 1) == 0) {
			SHIFT_RIGHT(y, swords);

			ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(u), length);
			ISSUE_MAU_COMMAND(MOD_ADD, MAU_SRAM_ADDRESS(u), length);
			ISSUE_MAU_COMMAND(CANON, 0, length);
			ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(u), length);

			ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(v), length);
			ISSUE_MAU_COMMAND(MOD_ADD, MAU_SRAM_ADDRESS(v), length);
			ISSUE_MAU_COMMAND(CANON, 0, length);
			ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(v), length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}

			c = c + 1;
		} else {
			ret = modmath_compare_yx(y, x, length, &difference);
			if (ret) {
				goto err;
			}

			if (difference == MAU_COMP_ERROR) {
				goto err;
			}

			if (difference == MAU_LT) {
				k = x;
				x = y;
				y = k;
				k = u;
				u = s;
				s = k;
				k = v;
				v = t;
				t = k;
			} else {
				ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(y), length);
				ISSUE_MAU_COMMAND(INT_SUB, MAU_SRAM_ADDRESS(x), length);
				ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(y), length);

				ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(s), length);
				ISSUE_MAU_COMMAND(MOD_SUB, MAU_SRAM_ADDRESS(u), length);
				ISSUE_MAU_COMMAND(CANON, 0, length);
				ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(s), length);

				ISSUE_MAU_COMMAND(LOAD, MAU_SRAM_ADDRESS(t), length);
				ISSUE_MAU_COMMAND(MOD_SUB, MAU_SRAM_ADDRESS(v), length);
				ISSUE_MAU_COMMAND(CANON, 0, length);
				ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(t), length);

				ret = cmrt_pke_wait();
				if (ret) {
					goto err;
				}
			}
		}

		ret = modmath_compare_yx(y, x, length, &difference);
		if (ret) {
			goto err;
		}
	}

	ISSUE_MAU_COMMAND(LOAD, R_MAU_ZERO, length);
	ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(u), length);
	ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(v), length);
	ISSUE_MAU_COMMAND(SET_MAND, MAU_SRAM_ADDRESS(x), length);
	ISSUE_MAU_COMMAND(COMPARE, R_MAU_ONE, length);

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	u[(bit_length - (c/2))/32] = 1 << ((bit_length - (c/2)) % 32);
	v[(bit_length - ((c+1)/2))/32] = 1 << ((bit_length - ((c+1)/2)) % 32);

	ISSUE_MAU_COMMAND(SET_MAND, MAU_SRAM_ADDRESS(t), length);
	ISSUE_MAU_COMMAND(MONT_MUL, MAU_SRAM_ADDRESS(v), length);
	ISSUE_MAU_COMMAND(CANON, 0, length);
	ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(t), length);
	ISSUE_MAU_COMMAND(SET_MAND, MAU_SRAM_ADDRESS(t), length);
	ISSUE_MAU_COMMAND(MONT_MUL, MAU_SRAM_ADDRESS(u), length);
	ISSUE_MAU_COMMAND(CANON, 0, length);
	ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(t), length);

	ISSUE_MAU_COMMAND(SET_MAND, SLOT(slot_b), length);
	ISSUE_MAU_COMMAND(COPY, MAU_SRAM_ADDRESS(t), length);

	if (slot_a != 0) {
		ISSUE_MAU_COMMAND(SET_MAND, MAU_SRAM_ADDRESS(s), length);
		ISSUE_MAU_COMMAND(MONT_MUL, MAU_SRAM_ADDRESS(v), length);
		ISSUE_MAU_COMMAND(CANON, 0, length);
		ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(s), length);
		ISSUE_MAU_COMMAND(SET_MAND, MAU_SRAM_ADDRESS(s), length);
		ISSUE_MAU_COMMAND(MONT_MUL, MAU_SRAM_ADDRESS(u), length);
		ISSUE_MAU_COMMAND(CANON, 0, length);
		ISSUE_MAU_COMMAND(STORE, MAU_SRAM_ADDRESS(s), length);

		ISSUE_MAU_COMMAND(SET_MAND, SLOT(slot_a), length);
		ISSUE_MAU_COMMAND(COPY, MAU_SRAM_ADDRESS(s), length);
	}

	ret = cmrt_pke_wait();
err:
	return ret;
}
