/*
 * Copyright (c) 2019-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>

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
#include "errno.h"

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"
#include "pke_internal.h"

int __cmrt_pke_rsa_key_generator(cmrt_pke_t pke,
				 struct cmrt_rsa_key *ctx)
{
	int ret;

	uint8_t diff1;
	uint8_t diff2;

	uint32_t length;
	uint32_t blength;
	uint32_t given_e;

	if (!pke || !ctx) {
		ret = -EINVAL;
		goto err;
	}

	if (ctx->elength != 4) {
		ret = -EINVAL;
		printk("wrong public key length\n");
		goto err;
	}

	/* Coverity Check CID: 106697 => Dereference before null check.
	 * Perform checks for pke and ctx before its use.
	 */
	uint32_t *maxdiff = pke_addr(primegen_maxdiff, NULL, ctx->bits / 2);
	uint32_t *public_key = pke_addr(primegen_pk, NULL, ctx->bits / 2);
	uint32_t *reduced_prime = pke_addr(primegen_redp, NULL, ctx->bits / 2);

	cmrt_pke_response_t *const resp = &pke->response;
	memset(resp, 0x00, sizeof(cmrt_pke_response_t));

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	memcpy(&given_e, ctx->e, ctx->elength);

	if (given_e != 0x10001) {
		ret = -EINVAL;
		printk("wrong public key, given 0x%x\n", given_e);
		goto err;
	}

	blength = (ctx->bits / 8) / sizeof(uint8_t);
#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (ctx->bits / 8) / sizeof(uint32_t);
#else /* 64-bit */
	length = (ctx->bits / 8) / sizeof(uint64_t);
#endif

	do {
		do {
#ifndef CONFIG_CMRT_FIPS140_MODE
			ret = cmrt_pke_generate_prime(pke, ctx->bits / 2, primegen_p, SETUP_REQUIRED);
#else

			ret = cmrt_pke_generate_prime(pke, ctx->bits / 2, primegen_p);
#endif
		} while (ret == -ERANGE);

		if (ret) {
			goto err;
		}

		/* Test that GCD(p-1, e) = 1
		 * Note that 0x10001 is prime so we test that p-1 is not a multiple of e
		 * using Montgomery reduction
		 */
		public_key[0] = given_e;
		static const uint32_t cmds_reduce_p[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(SET_PARAMS,    SLOT(primegen_pk)),
			SLOT_CMD(LOAD,          SLOT(primegen_p)),
			SLOT_CMD(INT_SUB,       R_MAU_ONE),
			SLOT_CMD(STORE,         SLOT(primegen_redp)),
			SLOT_CMD(SET_MAND,      SLOT(primegen_redp)),
			SLOT_CMD(MONT_MUL,      R_MAU_ONE),
			SLOT_CMD(CANON,         0),
			SLOT_CMD(STORE,         SLOT(primegen_redp)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_reduce_p, sizeof(cmds_reduce_p)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

	} while (reduced_prime[0] == 0);

	if (ctx->p != NULL) {
		memcpy(ctx->p, pke_addr(primegen_p, NULL, ctx->bits / 2), blength / 2);
	}

	do {
		do {
			do {
#ifndef CONFIG_CMRT_FIPS140_MODE
				ret = cmrt_pke_generate_prime(pke, ctx->bits / 2, primegen_q, SETUP_DONE);
#else
				ret = cmrt_pke_generate_prime(pke, ctx->bits / 2, primegen_q);
#endif
			} while (ret == -ERANGE);

			if (ret) {
				goto err;
			}

			/* Test that GCD(q-1, e) = 1
			 */
			public_key[0] = given_e;
			static const uint32_t cmds_reduce_q[] = {
				SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
				SLOT_CMD(SET_PARAMS,    SLOT(primegen_pk)),
				SLOT_CMD(LOAD,          SLOT(primegen_q)),
				SLOT_CMD(INT_SUB,       R_MAU_ONE),
				SLOT_CMD(STORE,         SLOT(primegen_redp)),
				SLOT_CMD(SET_MAND,      SLOT(primegen_redp)),
				SLOT_CMD(MONT_MUL,      R_MAU_ONE),
				SLOT_CMD(CANON,         0),
				SLOT_CMD(STORE,         SLOT(primegen_redp)),
			};

			ret = cmrt_pke_mau_command_sequence(cmds_reduce_q, sizeof(cmds_reduce_q)/sizeof(uint32_t), length / 2);
			if (ret) {
				goto err;
			}

		}  while (reduced_prime[0] == 0);

		/* Test that 100 most-significant bits are not the same */
		static const uint32_t cmds_difference[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(SET_PARAMS,    SLOT(primegen_p)),
			SLOT_CMD(LOAD,          SLOT(primegen_q)),
			SLOT_CMD(MOD_ADD,       R_MAU_ZERO),
			SLOT_CMD(STORE,		SLOT(primegen_pdiff)),
			SLOT_CMD(SET_PARAMS,    SLOT(primegen_q)),
			SLOT_CMD(LOAD,          SLOT(primegen_p)),
			SLOT_CMD(MOD_ADD,       R_MAU_ZERO),
			SLOT_CMD(STORE,		SLOT(primegen_qdiff)),
			SLOT_CMD(LOAD,          R_MAU_ZERO),
			SLOT_CMD(STORE,		SLOT(primegen_maxdiff)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_difference, sizeof(cmds_difference)/sizeof(uint32_t), length / 2);
		if (ret) {
			goto err;
		}

		maxdiff[(ctx->bits / 64) - 4] = 0x10000000;

		ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_pdiff), length / 2);
		ISSUE_MAU_COMMAND(COMPARE, SLOT(primegen_maxdiff), length / 2);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		diff1 = MAU_GET_COMPARE_RESULT();

		ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_qdiff), length / 2);
		ISSUE_MAU_COMMAND(COMPARE, SLOT(primegen_maxdiff), length / 2);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		diff2 = MAU_GET_COMPARE_RESULT();

	} while ((diff1 != MAU_GT) && (diff2 != MAU_GT));

	static const uint32_t cmds_zero[] = {
		SLOT_CMD(LOAD,  R_MAU_ZERO),
		SLOT_CMD(STORE, SLOT(0)),
		SLOT_CMD(STORE,	SLOT(1)),
		SLOT_CMD(STORE,	SLOT(2)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), length / 2);
	if (ret) {
		goto err;
	}

	if (ctx->q != NULL) {
		memcpy(ctx->q, pke_addr(primegen_q, NULL, ctx->bits / 2), blength / 2);
	}

	ret = cmrt_pke_generate_rsa_keys(pke, ctx);

	if (ctx->mask != NULL) {
		memset(ctx->mask, 0x00, 4 * sizeof(uint8_t));
	}

	if (ret >= 0) {
		ret = cmrt_pke_complete(pke);
	}
err:
	return ret;
}

int z_impl_cmrt_pke_rsa_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key)
{
	return __cmrt_pke_rsa_key_generator(context, key);
}

#ifdef CONFIG_CMRT_RSA_CRT
int z_impl_cmrt_pke_rsa_crt_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key)
{
	return __cmrt_pke_rsa_key_generator(context, key);
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_rsa_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key)
{
	z_syscall_verify_pke_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(key, sizeof(struct cmrt_rsa_key)));

	return z_impl_cmrt_pke_rsa_key_gen(context, key);
}
#include <syscalls/cmrt_pke_rsa_key_gen_mrsh.c>

#ifdef CONFIG_CMRT_RSA_CRT
static inline int z_vrfy_cmrt_pke_rsa_crt_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key)
{
	z_syscall_verify_pke_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(key, sizeof(struct cmrt_rsa_key)));

	return z_impl_cmrt_pke_rsa_crt_key_gen(context, key);
}
#include <syscalls/cmrt_pke_rsa_crt_key_gen_mrsh.c>
#endif /* CONFIG_CMRT_RSA_CRT  */

#endif /* CONFIG_USERSPACE  */
