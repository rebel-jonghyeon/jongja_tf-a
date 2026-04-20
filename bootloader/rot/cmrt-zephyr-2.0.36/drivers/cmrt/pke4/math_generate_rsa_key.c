/*
 * Copyright (c) 2019-2024 Cryptography Research, Inc. (CRI).
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

#ifdef CONFIG_CMRT_FIPS140_MODE
static void SHIFT_RIGHT(uint32_t *x,
			size_t len)
{
	size_t j;

	for (j = 0; j < (len)-1; j++) {
		x[j] = (x[j] >> 1) + (x[j + 1] << 31);
	}
	x[(len)-1] >>= 1;
}
#endif

static int zero_pke_ram(uint32_t length)
{
	static const uint32_t cmds_zero[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(2)),
		SLOT_CMD(STORE,         SLOT(3)),
		SLOT_CMD(STORE,         SLOT(4)),
		SLOT_CMD(STORE,         SLOT(5)),
		SLOT_CMD(STORE,         SLOT(6)),
	};

	return cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), length);
}

static int cmrt_pke_inverse_mod_e(uint32_t bits)
{
	int ret;

	uint32_t length;
	uint32_t given_e = 0x010001;
	uint32_t phi_mod_e;
	uint32_t prime_e;
	uint32_t acc;
	uint32_t b;

	uint32_t *public_key = pke_addr(keygen_pk, NULL, bits);
	uint32_t *reduced_phi = pke_addr(keygen_redphi, NULL, bits);

#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (bits / 8) / sizeof(uint32_t);
#else /* 64-bit */
	length = (bits / 8) / sizeof(uint64_t);
#endif

	public_key[0] = given_e;
	/* phi(n) mod e */
	static const uint32_t cmds_reduce_phi[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(keygen_n)),
		SLOT_CMD(SET_PARAMS,    SLOT(keygen_pk)),
		SLOT_CMD(SET_MAND,      SLOT(keygen_phi)),
		SLOT_CMD(MONT_MUL,      R_MAU_ONE),
		SLOT_CMD(CANON,         0),
		SLOT_CMD(STORE,         SLOT(keygen_redphi)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_reduce_phi, sizeof(cmds_reduce_phi)/sizeof(uint32_t), length);
	if (ret) {
		goto err;
	}

	/* -phi(n)^-1 mod e */
	phi_mod_e = reduced_phi[0];
	prime_e = given_e;
	acc = 1;
	for (int i = 31; i >= 0; i--) {
		b = ((prime_e - 2) >> i) & 1;
		acc = (acc * acc) % prime_e;
		if (b == 1) {
			acc = (acc * phi_mod_e) % prime_e;
		}
	}
	phi_mod_e = prime_e - acc;
	reduced_phi[0] = phi_mod_e;

	/* (((-phi(n)^-1 mod e) * phi(n)) + 1) */
	static const uint32_t cmds_make_d[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_MAND,      SLOT(primegen_d_low)),
		SLOT_CMD(COPY,          SLOT(primegen_phi_low)),
		SLOT_CMD(INT_MUL,       SLOT(primegen_redphi)),
		SLOT_CMD(STORE,         SLOT(primegen_d_high)),

		SLOT_CMD(LOAD,          SLOT(primegen_d_low)),
		SLOT_CMD(INT_ADD,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(primegen_d_low)),

		SLOT_CMD(SET_MAND,      SLOT(primegen_n_low)),
		SLOT_CMD(COPY,          SLOT(primegen_phi_high)),
		SLOT_CMD(INT_MUL,       SLOT(primegen_redphi)),
		SLOT_CMD(STORE,         SLOT(primegen_n_high)),

		SLOT_CMD(LOAD,          SLOT(primegen_n_low)),
		SLOT_CMD(INT_ADD,       SLOT(primegen_d_high)),
		SLOT_CMD(STORE,         SLOT(primegen_d_high)),

		SLOT_CMD(SET_MAND,      SLOT(primegen_n_low)),
		SLOT_CMD(COPY,          SLOT(primegen_n_high)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_make_d, sizeof(cmds_make_d)/sizeof(uint32_t), length / 2);
	if (ret) {
		goto err;
	}

	/* (((-phi(n)^-1 mod e) * phi(n)) + 1) / e */
	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);
	ISSUE_MAU_COMMAND(SET_MAND, SLOT(keygen_d), length + 1);
	ISSUE_MAU_COMMAND(INT_DIV_SMALL_EXACT, SLOT(keygen_pk), length + 1);

	ret = cmrt_pke_wait();
err:
	return ret;
}

int cmrt_pke_generate_rsa_keys(cmrt_pke_t pke,
			       cmrt_rsa_key_t ctx)
{
	int ret;

	uint32_t length;
	uint32_t blength;

	blength = (ctx->bits / 8) / sizeof(uint8_t);
#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (ctx->bits / 8) / sizeof(uint32_t);
#else /* 64-bit */
	length = (ctx->bits / 8) / sizeof(uint64_t);
#endif

	static const uint32_t cmds_make_n[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(primegen_n_high)),
		SLOT_CMD(STORE,         SLOT(primegen_phi_high)),
		SLOT_CMD(SET_MAND,      SLOT(primegen_n_low)),
		SLOT_CMD(COPY,          SLOT(primegen_p)),
		SLOT_CMD(INT_MUL,       SLOT(primegen_q)),
		SLOT_CMD(STORE,         SLOT(primegen_n_high)),
		SLOT_CMD(LOAD,          SLOT(primegen_p)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(primegen_p)),
		SLOT_CMD(LOAD,          SLOT(primegen_q)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(primegen_q)),
		SLOT_CMD(SET_MAND,      SLOT(primegen_phi_low)),
		SLOT_CMD(COPY,          SLOT(primegen_p)),
		SLOT_CMD(INT_MUL,       SLOT(primegen_q)),
		SLOT_CMD(STORE,         SLOT(primegen_phi_high)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_make_n, sizeof(cmds_make_n)/sizeof(uint32_t), length / 2);
	if (ret) {
		goto err;
	}

	if (ctx->n != NULL) {
		memcpy(ctx->n, pke_addr(keygen_n, NULL, ctx->bits), blength);
	}

	if (ctx->d != NULL) {
#ifdef CONFIG_CMRT_FIPS140_MODE
		uint32_t *gcd;
		uint32_t gcd_bit_length = 0;
		uint32_t word_length;

#ifdef CONFIG_CMRT_PKE_32_BIT
		word_length = length;
#else /* 64-bit */
		word_length = 2 * length;
#endif

		static const uint32_t cmds_make_carmichael_d[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(LOAD,          SLOT(primegen_p)),
			SLOT_CMD(STORE,         SLOT(primegen_pm1)),
			SLOT_CMD(LOAD,          SLOT(primegen_q)),
			SLOT_CMD(STORE,         SLOT(primegen_qm1))
		};

		ret = cmrt_pke_mau_command_sequence(cmds_make_carmichael_d, sizeof(cmds_make_carmichael_d)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_gcd(pke_addr(primegen_pm1, NULL, ctx->bits / 2), pke_addr(primegen_qm1, NULL, ctx->bits / 2), word_length / 2, &gcd);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_get_bit_length(gcd, length / 2, &gcd_bit_length);
		if (gcd_bit_length >= 32) {
			ret = -EIO;
		}
		if (ret) {
			goto err;
		}

		while ((gcd[0] & 1) == 0) {
			gcd[0] /= 2;
			SHIFT_RIGHT(pke_addr(primegen_phi_low, NULL, ctx->bits / 2), word_length);
		}

		if (gcd[0] > 1) {
			ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);
			ISSUE_MAU_COMMAND(SET_MAND, SLOT(keygen_phi), length);
			ISSUE_MAU_COMMAND(INT_DIV_SMALL_EXACT, MAU_SRAM_ADDRESS(gcd), length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}
		}
#endif
		ret = cmrt_pke_inverse_mod_e(ctx->bits);
		if (ret) {
			goto err;
		}

		memcpy(ctx->d, pke_addr(keygen_d, NULL, ctx->bits), blength);
	}

	ret = zero_pke_ram(length);
	if (ret) {
		goto err;
	}

	if (ctx->dp != NULL) {
		static const uint32_t cmds_copy_p[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(SET_MAND,      SLOT(keygen_phi)),
			SLOT_CMD(COPY,          SLOT(primegen_p))
		};

		ret = cmrt_pke_mau_command_sequence(cmds_copy_p, sizeof(cmds_copy_p)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_inverse_mod_e(ctx->bits / 2);
		if (ret) {
			goto err;
		}

		memcpy(ctx->dp, pke_addr(keygen_d, NULL, ctx->bits / 2), blength / 2);

		ret = zero_pke_ram(length);
		if (ret) {
			goto err;
		}
	}

	if (ctx->dq != NULL) {
		static const uint32_t cmds_copy_q[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(SET_MAND,      SLOT(keygen_phi)),
			SLOT_CMD(COPY,          SLOT(primegen_q))
		};

		ret = cmrt_pke_mau_command_sequence(cmds_copy_q, sizeof(cmds_copy_q)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_inverse_mod_e(ctx->bits / 2);
		if (ret) {
			goto err;
		}

		memcpy(ctx->dq, pke_addr(keygen_d, NULL, ctx->bits / 2), blength / 2);

		ret = zero_pke_ram(length);
		if (ret) {
			goto err;
		}
	}

	if (ctx->iq != NULL) {
		static const uint32_t cmds_inv_q[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(LOAD,          SLOT(primegen_p)),
			SLOT_CMD(INT_ADD,       R_MAU_ONE),
			SLOT_CMD(STORE,         SLOT(modexp_n)),
			SLOT_CMD(INT_SUB,       R_MAU_TWO),
			SLOT_CMD(STORE,         SLOT(modexp_d0)),
			SLOT_CMD(SET_PARAMS,    SLOT(modexp_n)),
			SLOT_CMD(LOAD,          SLOT(primegen_q)),
			SLOT_CMD(MOD_ADD,       R_MAU_ONE),
			SLOT_CMD(CANON,         0),
			SLOT_CMD(STORE,         SLOT(modexp_x)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_inv_q, sizeof(cmds_inv_q)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MOD_EXP, 0, 0, length / 2));
		if (ret) {
			goto err;
		}

		memcpy(ctx->iq, pke_addr(modexp_x, NULL, ctx->bits / 2), blength / 2);
	}

	(void)cmrt_pke_clear_ram();
err:
	return ret;
}
