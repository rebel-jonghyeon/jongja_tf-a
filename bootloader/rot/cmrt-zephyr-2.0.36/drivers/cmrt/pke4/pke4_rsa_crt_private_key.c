/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>
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
#include "pke_internal.h"

int z_impl_cmrt_pke_rsa_crt_sign(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	int status;

	uint32_t i;
	uint32_t length = 0;
	uint32_t blength;
	uint32_t slot_bit_length;

	uint32_t *L[15];

	uint32_t full_width;
	uint32_t width;
	uint32_t copy_width;

	cmrt_pke_response_t *const resp = &pke->response;
	memset(resp, 0x00, sizeof(cmrt_pke_response_t));

	if (!pke || !ctx) {
		status = -EINVAL;
		goto err;
	}

	struct cmrt_rsa_key *key = &ctx->key;

	blength = (key->bits / 8) / sizeof(uint8_t);
#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (key->bits / 8) / sizeof(uint32_t);
	width = ((key->bits / 16) / sizeof(uint32_t)) + 1;
	full_width = (key->bits / 8) / sizeof(uint32_t);
	slot_bit_length = (key->bits / 2) + 32;
#else /* 64-bit */
	length = (key->bits / 8) / sizeof(uint64_t);
	width = ((key->bits / 16) / sizeof(uint64_t)) + 1;
	full_width = (key->bits / 8) / sizeof(uint64_t);
	slot_bit_length = (key->bits / 2) + 64;
#endif
	copy_width = (key->bits / 16) + sizeof(uint32_t);

	status = cmrt_pke_clear_ram();
	if (status) {
		goto err;
	}

	for (i = 0; i < 15; i++) {
		L[i] = pke_addr(i, NULL, slot_bit_length);
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * Test for invalid input
	 * ----------------------------------------------------------------------------------------------------------------*/
	memcpy(pke_addr(0, NULL, key->bits), ctx->message, blength);

	static const uint32_t cmd_zero_test[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(COMPARE,       SLOT(0)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_zero_test, sizeof(cmd_zero_test)/sizeof(uint32_t), length);
	if (status) {
		goto err;
	}

	if (MAU_GET_COMPARE_RESULT() == MAU_EQ) {
		status = -EINVAL;
		goto err;
	}

	status = cmrt_pke_clear_ram();
	if (status) {
		goto err;
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * Start PRNG and reblind key
	 * ----------------------------------------------------------------------------------------------------------------*/
	status = cmrt_pke_blind_rsa_crt_key_internal(pke, key, 0); /* leaves blinded key in PKE RAM */
	if (status) {
		goto err;
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * We have slots:
	 * 0: p    1: q    2: dp   3: dq   5: mask
	 * we change to
	 * 0: mask 2: p    8: q    9: dp   10: dq
	 * and zero the rest
	 * ----------------------------------------------------------------------------------------------------------------*/
	static const uint32_t cmd_move_key[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(14)),
		SLOT_CMD(STORE,         SLOT(13)),
		SLOT_CMD(STORE,         SLOT(12)),
		SLOT_CMD(STORE,         SLOT(11)),
		SLOT_CMD(SET_MAND,      SLOT(10)),
		SLOT_CMD(COPY,          SLOT(3)),
		SLOT_CMD(SET_MAND,      SLOT(9)),
		SLOT_CMD(COPY,          SLOT(2)),
		SLOT_CMD(SET_MAND,      SLOT(8)),
		SLOT_CMD(COPY,          SLOT(1)),
		SLOT_CMD(STORE,         SLOT(7)),
		SLOT_CMD(STORE,         SLOT(6)),
		SLOT_CMD(SET_MAND,      SLOT(2)),
		SLOT_CMD(COPY,          SLOT(0)),
		SLOT_CMD(SET_MAND,      SLOT(0)),
		SLOT_CMD(COPY,          SLOT(5)),
		SLOT_CMD(STORE,         SLOT(6)),
		SLOT_CMD(STORE,         SLOT(5)),
		SLOT_CMD(STORE,         SLOT(4)),
		SLOT_CMD(STORE,         SLOT(3)),
		SLOT_CMD(STORE,         SLOT(1)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_move_key,
					      sizeof(cmd_move_key)/sizeof(uint32_t),
					      width);
	if (status) {
		goto err;
	}

	memcpy(pke_addr(5, NULL, slot_bit_length), key->e, key->elength);

	static const uint32_t cmd_decrement_exponents[] = {
		SLOT_CMD(LOAD,          SLOT(5)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(5)),
		SLOT_CMD(LOAD,          SLOT(9)),
		SLOT_CMD(INT_SUB,       R_MAU_TWO),
		SLOT_CMD(STORE,         SLOT(9)),
		SLOT_CMD(LOAD,          SLOT(10)),
		SLOT_CMD(INT_SUB,       R_MAU_TWO),
		SLOT_CMD(STORE,         SLOT(10)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_decrement_exponents,
					      sizeof(cmd_decrement_exponents)/sizeof(uint32_t),
					      width);
	if (status) {
		goto err;
	}

	memcpy(pke_addr(13, NULL, slot_bit_length), key->n, (key->bits / 8));
	memcpy(pke_addr(11, NULL, slot_bit_length), ctx->message, (key->bits / 8));

	status = cmrt_pke_get_pseudo_random(NULL, copy_width, 6, width);
	if (status) {
		goto err;
	}

	/* XOR dp and dq with public key */
	for (i = 0; i < width; i++) {
		L[9][i] ^= L[5][i];
		L[10][i] ^= L[5][i];
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * RSA CRT
	 * NB: in comments x is Montgomery multiplication
	 * ----------------------------------------------------------------------------------------------------------------*/
#ifdef CONFIG_CMRT_PKE_32_BIT
	L[1][6] = 1;
#else
	L[1][12] = 1;
#endif
	static const uint32_t cmd_1[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),

		SLOT_CMD(SET_MAND,	SLOT(3)),
		SLOT_CMD(COPY,          R_MAU_ADDR_RNG_ODD),
		SLOT_CMD(SET_PARAMS,    SLOT(3)),
		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(COPY,          R_MAU_ADDR_RNG_ODD),
		SLOT_CMD(SET_MAND,      SLOT(0)),
		SLOT_CMD(MONT_MUL,      SLOT(0)), /* dummy multiplication */
		SLOT_CMD(STORE,         SLOT(0)),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(3)),

		SLOT_CMD(SET_PARAMS,    SLOT(2)),
		SLOT_CMD(SET_MAND,      SLOT(6)),
		SLOT_CMD(MONT_MUL,      SLOT(8)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: rq = r * q' mod p' */
		SLOT_CMD(SET_MAND,      SLOT(0)),
		SLOT_CMD(MONT_MUL,      R_MAU_ONE),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: rq = 1 x rq mod p' */
		SLOT_CMD(MONT_MUL,      R_MAU_ONE),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: rq = 1 x rq mod p' */
		SLOT_CMD(MONT_MUL,      SLOT(1)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(7)), /* L[7]: rq = 2^192 x rq mod p' */
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(1)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_1, sizeof(cmd_1)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	L[1][2] = 1;
#else
	L[1][4] = 1;
#endif
	static const uint32_t cmd_2[] = {
		SLOT_CMD(SET_MAND,      SLOT(7)),
		SLOT_CMD(MONT_MUL,      SLOT(1)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: rqw = 2^64 x rq mod p' */
		SLOT_CMD(SET_MAND,      SLOT(0)),
		SLOT_CMD(MONT_MUL,      R_MAU_ONE),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: rqw = 1 x rqw mod p' */
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(3)),
		SLOT_CMD(STORE,         SLOT(4)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_2, sizeof(cmd_2)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

	ISSUE_MCG_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, width); /* L[0]: rqw = rqw^(e-1) mod p' */

	status = cmrt_pke_wait();
	if (status) {
		goto err;
	}

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, width);
	ISSUE_MAU_COMMAND(SET_MAND, SLOT(3), width);
	ISSUE_MAU_COMMAND(COPY, R_MAU_ZERO, width);
	static const uint32_t cmd_3[] = {
		SLOT_CMD(SET_PARAMS,	SLOT(2)),
		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(MONT_MUL,	SLOT(11)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0-1]: ap = m x rqw mod p' */
	};

	status = cmrt_pke_mau_command_sequence(cmd_3, sizeof(cmd_3)/sizeof(uint32_t), full_width);
	if (status) {
		goto err;
	}

	static const uint32_t cmd_4[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_PARAMS,	SLOT(2)),
		SLOT_CMD(SET_MAND,	SLOT(3)),
		SLOT_CMD(COPY,          SLOT(0)),
		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(MONT_MUL,	SLOT(7)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)), /* L[0]: brp = rq x ap mod p' */
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(7)),
		SLOT_CMD(SET_MAND,	SLOT(7)),
		SLOT_CMD(COPY,          SLOT(3)),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(3)),
		SLOT_CMD(SET_MAND,	SLOT(4)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_4, sizeof(cmd_4)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

	ISSUE_MAU_COMMAND(COPY, SLOT(9), width);

	status = cmrt_pke_wait();
	if (status) {
		goto err;
	}

	status = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, width));
	if (status) {
		goto err;
	}

	static const uint32_t cmd_5[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_PARAMS,	SLOT(2)),
		SLOT_CMD(LOAD,		R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(9)),
		SLOT_CMD(SET_MAND,      SLOT(7)),
		SLOT_CMD(MONT_MUL,      SLOT(0)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(9)), /* L[9]: bp = ap x bp mod p' */
		SLOT_CMD(LOAD,		R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),
		SLOT_CMD(MONT_MUL,      SLOT(9)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(SET_MAND,      SLOT(9)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(9)), /* L[9]: cp = ap x bp mod p' */
		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(COPY,          R_MAU_ADDR_RNG),

		SLOT_CMD(LOAD,		R_MAU_ZERO), /* swap p and q */
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(SET_MAND,      SLOT(1)),
		SLOT_CMD(COPY,          SLOT(8)),
		SLOT_CMD(STORE,         SLOT(8)),
		SLOT_CMD(SET_MAND,      SLOT(8)),
		SLOT_CMD(COPY,          SLOT(2)),
		SLOT_CMD(STORE,         SLOT(2)),
		SLOT_CMD(SET_MAND,      SLOT(2)),
		SLOT_CMD(COPY,          SLOT(1)),
		SLOT_CMD(STORE,         SLOT(1)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_5, sizeof(cmd_5)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	L[1][6] = 1;
#else
	L[1][12] = 1;
#endif
	status = cmrt_pke_mau_command_sequence(cmd_1, sizeof(cmd_1)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	L[1][2] = 1;
#else
	L[1][4] = 1;
#endif

	status = cmrt_pke_mau_command_sequence(cmd_2, sizeof(cmd_2)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

	ISSUE_MCG_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, width); /* L[0]: rpw = rpw^(e-1) mod q' */

	status = cmrt_pke_wait();
	if (status) {
		goto err;
	}

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, width);
	ISSUE_MAU_COMMAND(SET_MAND, SLOT(3), width);
	ISSUE_MAU_COMMAND(COPY, R_MAU_ZERO, width);

	status = cmrt_pke_mau_command_sequence(cmd_3, sizeof(cmd_3)/sizeof(uint32_t), full_width);
	if (status) {
		goto err;
	}

	status = cmrt_pke_mau_command_sequence(cmd_4, sizeof(cmd_4)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

	ISSUE_MAU_COMMAND(COPY, SLOT(10), width);
	/* the copy needs a wait before starting modexp, coz the copy may
	 * not finish in time.
	 */
	status = cmrt_pke_wait();
	if (status) {
		goto err;
	}

	ISSUE_MCG_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, width);

	status = cmrt_pke_wait(); /* L[0]: bq = brq^dq' mod q' */
	if (status) {
		goto err;
	}

	static const uint32_t cmd_6[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_PARAMS,	SLOT(2)),
		SLOT_CMD(LOAD,		R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(10)),
		SLOT_CMD(SET_MAND,      SLOT(7)),
		SLOT_CMD(MONT_MUL,      SLOT(0)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(10)), /* L[10]: bq = aq x bq mod q' */
		SLOT_CMD(LOAD,		R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),
		SLOT_CMD(MONT_MUL,      SLOT(10)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(SET_MAND,      SLOT(10)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(10)), /* L[10]: cq = aq x bq mod q' */
		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(COPY,          R_MAU_ONE),
		SLOT_CMD(SET_MAND,	SLOT(1)),
		SLOT_CMD(COPY,          R_MAU_ONE),
		SLOT_CMD(SET_MAND,      SLOT(1)),
		SLOT_CMD(MONT_MUL,      SLOT(0)), /* dummy multiplication */
		SLOT_CMD(LOAD,		R_MAU_ZERO),
		SLOT_CMD(SET_MAND,      SLOT(0)), /* L[0-1] = cq */
		SLOT_CMD(COPY,          SLOT(10)),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(3)), /* L[2-3] = q' */
		SLOT_CMD(SET_MAND,      SLOT(10)),
		SLOT_CMD(COPY,          SLOT(9)), /* L[10-11] = cp */
		SLOT_CMD(STORE,         SLOT(11)),
		SLOT_CMD(STORE,         SLOT(9)), /* L[8-9] = p' */
		SLOT_CMD(STORE,         SLOT(7)), /* L[6-7] = r */
	};

	status = cmrt_pke_mau_command_sequence(cmd_6, sizeof(cmd_6)/sizeof(uint32_t), width);
	if (status) {
		goto err;
	}

	static const uint32_t cmd_7[] = {
		SLOT_CMD(SET_PARAMS,    SLOT(13)),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(4)),

		SLOT_CMD(SET_MAND,	SLOT(0)),
		SLOT_CMD(MONT_MUL,      SLOT(8)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(4)), /* L[4-5]: s1 = cq x p' mod n */

		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),

		SLOT_CMD(SET_MAND,	SLOT(2)),
		SLOT_CMD(MONT_MUL,      SLOT(10)), /* L[0-1]: s2 = cp x q' mod n */
		SLOT_CMD(MOD_ADD,       SLOT(4)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(2)), /* L[2-3]: s' = s1 + s2 mod n */

		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),

		SLOT_CMD(SET_MAND,	SLOT(2)),
		SLOT_CMD(MONT_MUL,      SLOT(6)),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(0)),
	};

	status = cmrt_pke_mau_command_sequence(cmd_7, sizeof(cmd_7)/sizeof(uint32_t), full_width);
	if (status) {
		goto err;
	}

	/* this value could be copied as part of a command response value
	 * in the sync routine only, but that won't currently buy anything
	 * as the sequence is already executed fully synchronously.
	 */
	memcpy(ctx->signature, pke_addr(0, NULL, key->bits), key->bits / 8);

	status = cmrt_pke_complete(pke);
err:
	return status;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_rsa_crt_sign(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	z_syscall_verify_pke_context(pke);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(ctx, sizeof(struct cmrt_rsa_ctx)));

	return z_impl_cmrt_pke_rsa_crt_sign(pke, ctx);
}
#include <syscalls/cmrt_pke_rsa_crt_sign_mrsh.c>

#endif /* CONFIG_USERSPACE  */
