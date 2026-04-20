/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
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

static void shift_right_small(uint32_t *x, size_t len, uint32_t bits)
{
	if (bits > 31)
		return;
	for (size_t j = 0; j < (len)-1; j++)
		x[j] = (x[j] >> bits) + (x[j + 1] << (32 - bits));
	x[(len)-1] >>= bits;
}

static void shift_right(uint32_t *x, size_t len, uint32_t bits)
{
	while (bits > 31) {
		shift_right_small(x, len, bits);
		bits -= 31;
	}
	shift_right_small(x, len, bits);
}

static int32_t get_number_mr_tests(uint32_t bit_length)
{
	uint32_t mr_tests = 7;

	if (bit_length >= 1536) {
		mr_tests = 3;
	} else if (bit_length >= 1024) {
		mr_tests = 4;
	}

	return(mr_tests);
}

static const uint32_t cmds_zero[] = {
	SLOT_CMD(LOAD,          R_MAU_ZERO),
	SLOT_CMD(STORE,         SLOT(0)),
	SLOT_CMD(STORE,         SLOT(1)),
	SLOT_CMD(STORE,         SLOT(2)),
	SLOT_CMD(STORE,         SLOT(3)),
	SLOT_CMD(STORE,         SLOT(4)),
	SLOT_CMD(STORE,         SLOT(5)),
	SLOT_CMD(STORE,         SLOT(6)),
	SLOT_CMD(STORE,         SLOT(7)),
	SLOT_CMD(STORE,         SLOT(8)),
};

int cmrt_pke_miller_rabin_test(cmrt_pke_t pke,
			       uint32_t bits,
			       uint8_t slot_number,
			       uint8_t nr_tests,
			       uint32_t *prime)
{
	int ret;

	uint32_t *test_input = pke_addr(modexp_x, NULL, bits);
	uint32_t *shifted_prime = pke_addr(modexp_d0, NULL, bits);
	uint32_t length;
	uint32_t bit_length;
	uint32_t bit_mask;
	uint32_t min_length;
	uint32_t *prime_ptr;

	*prime = 0;

#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (bits / 8) / sizeof(uint32_t);
#else /* 64-bit */
	length = (bits / 8) / sizeof(uint64_t);
#endif

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);
	ISSUE_MAU_COMMAND(LOAD, SLOT(slot_number), length);

	static const uint32_t cmds_mr_setup[] = {
		SLOT_CMD(STORE,         SLOT(modexp_n)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(modexp_d0)),
		SLOT_CMD(STORE,         SLOT(primegen_pm1)),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(modexp_d1)),
		SLOT_CMD(STORE,         SLOT(modexp_x)),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(3)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_mr_setup, sizeof(cmds_mr_setup)/sizeof(uint32_t), length);
	if (ret) {
		goto err;
	}

	uint32_t w = shifted_prime[0];
	int r = 0;
	while ((w & 1) == 0) {
		++r;
		w >>= 1;
	}
	shift_right(shifted_prime, (bits / 8) / sizeof(uint32_t), r);

	prime_ptr = pke_addr(slot_number, NULL, bits);
	ret = cmrt_pke_get_bit_length(prime_ptr, (bits / 8) / sizeof(uint32_t), &bit_length);
	if (bit_length == 0) {
		ret = -1;
		goto err;
	}
	bit_mask = (1 << ((bit_length - 1) & 0x1F)) - 1;
	bit_length = (((bit_length - 1) / 32) + 1) * 32;

	for (int i = 0; i < nr_tests; ++i) {
		ret = cmrt_pke_get_pseudo_random(NULL, (bit_length / 8) / sizeof(uint8_t), modexp_x, 1);
		if (ret) {
			goto err;
		}

		test_input[(bit_length / 32) - 1] &= bit_mask;
		if (((((bit_length - 1) / 32) + 1) & 1) != 0) {
			test_input[bit_length / 32] = 0;
		}

		min_length = MAU_READ_REG(R_MAU_MIN_LEN);
		for (uint32_t j = (bit_length / 32); j < min_length; j++) {
			test_input[j] = 0;
		}

		ret = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, length));
		if (ret) {
			goto err;
		}

		static const uint32_t cmds_test_one[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(LOAD,          R_MAU_ZERO),
			SLOT_CMD(STORE,         SLOT(modexp_d1)),
			SLOT_CMD(STORE,         SLOT(1)),
			SLOT_CMD(STORE,         SLOT(3)),
			SLOT_CMD(SET_PARAMS,    SLOT(modexp_n)),
			SLOT_CMD(SET_MAND,      SLOT(modexp_x)),
			SLOT_CMD(MONT_MUL,      R_MAU_ONE),
			SLOT_CMD(CANON,         0),
			SLOT_CMD(STORE,         SLOT(primegen_mr)),
			SLOT_CMD(COMPARE,       R_MAU_ONE),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_test_one, sizeof(cmds_test_one)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

		if (MAU_GET_COMPARE_RESULT() == MAU_EQ) {
			continue;
		}

		ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_mr), length);
		ISSUE_MAU_COMMAND(COMPARE, SLOT(primegen_pm1), length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		if (MAU_GET_COMPARE_RESULT() == MAU_EQ) {
			continue;
		}

		int wit = 0;
		for (int j = 0; j < r - 1; ++j) {
			static const uint32_t cmds_witness[] = {
				SLOT_CMD(MONT_SQR,      SLOT(modexp_x)),
				SLOT_CMD(CANON,         0),
				SLOT_CMD(STORE,         SLOT(modexp_x)),
				SLOT_CMD(MONT_MUL,      R_MAU_ONE),
				SLOT_CMD(CANON,         0),
				SLOT_CMD(STORE,         SLOT(primegen_mr)),
				SLOT_CMD(COMPARE,       SLOT(primegen_pm1)),
			};

			ret = cmrt_pke_mau_command_sequence(cmds_witness, sizeof(cmds_witness)/sizeof(uint32_t), length);
			if (ret) {
				goto err;
			}

			wit |= (MAU_GET_COMPARE_RESULT() == MAU_EQ);
		}

		if (!wit) {
			goto err;
		}
	}

	*prime = 1;
err:
	(void)cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), length);

	return ret;
}

int cmrt_pke_is_probable_prime(cmrt_pke_t pke,
			       uint32_t bits,
			       uint8_t slot_number,
			       uint32_t *prime)
{
	uint8_t nr_tests = get_number_mr_tests(bits);

	return cmrt_pke_miller_rabin_test(pke, bits, slot_number, nr_tests, prime);
}
