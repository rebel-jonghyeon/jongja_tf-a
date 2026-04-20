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

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_math.h>
#include "pke4_hash.h"
#include "pke_internal.h"
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"


int z_impl_cmrt_pke_ffdh_parmgen(cmrt_pke_t pke,
				 size_t pbits,
				 size_t qbits,
				 struct cmrt_ffdh_param *param)
{
	int ret = -EIO;

	if (!param) {
		return -EINVAL;
	}

	uint8_t *p = param->p;
	uint8_t *q = param->q;
	uint8_t *g = param->g;

	uint32_t length;

	if (!pke || !p || !q || !g) {
		return -EINVAL;
	}

	ret = cmrt_pke_clear_ram();
	if (ret != 0) {
		goto err;
	}

	ret = cmrt_pke_generate_prime(pke, qbits, ffdh_parmgen_q, DH_SETUP_REQUIRED);
	if (ret != 0) {
		goto err;
	}

	memcpy(q, pke_addr(ffdh_parmgen_q, NULL, qbits), qbits / 8);

	ret = cmrt_pke_clear_ram();
	if (ret != 0) {
		goto err;
	}

	ret = cmrt_pke_generate_dh_prime(pke, pbits, ffdh_parmgen_p,
					 qbits, q, DH_GENERATE_P);
	if (ret != 0) {
		goto err;
	}

	memcpy(p, pke_addr(ffdh_parmgen_p, NULL, pbits), pbits / 8);

#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (pbits / 8) / sizeof(uint32_t);
#else /* 64-bit */
	length = (pbits / 8) / sizeof(uint64_t);
#endif

	static const uint32_t setup[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_MAND, SLOT(modexp_n)),
		SLOT_CMD(COPY, SLOT(ffdh_parmgen_p)),
		SLOT_CMD(SET_MAND, SLOT(modexp_d0)),
		SLOT_CMD(COPY, SLOT(ffdh_parmgen_dh))
	};
	enum { nsetup = sizeof(setup) / sizeof(setup[0]) };
	ret = cmrt_pke_mau_command_sequence(setup, nsetup, length);
	if (ret != 0) {
		goto err;
	}

	do {
		ISSUE_MAU_COMMAND(LOAD, R_MAU_ADDR_RNG, length);
		ISSUE_MAU_COMMAND(COMPARE, SLOT(modexp_n), length);

		ret = cmrt_pke_wait();
		if (ret != 0) {
			goto err;
		}
	} while (MAU_GET_COMPARE_RESULT() != MAU_LT);

	ISSUE_MAU_COMMAND(STORE, SLOT(modexp_x), length);

	ret = cmrt_pke_wait();
	if (ret != 0) {
		goto err;
	}

	ret = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MONTGOMERY_MOD_EXP, 0, 0, length));
	if (ret != 0) {
		goto err;
	}

	static const uint32_t cmds[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_PARAMS, SLOT(modexp_n)),
		SLOT_CMD(SET_MAND, SLOT(out_modexp_xd)),
		SLOT_CMD(MONT_MUL, R_MAU_ONE),
		SLOT_CMD(CANON, 0),
		SLOT_CMD(STORE, SLOT(out_modexp_xd))
	};
	enum { ncmds = sizeof(cmds) / sizeof(cmds[0]) };
	ret = cmrt_pke_mau_command_sequence(cmds, ncmds, length);
	if (ret != 0) {
		goto err;
	}

	memcpy(g, pke_addr(out_modexp_xd, NULL, pbits), pbits / 8);

	param->mod_bits = pbits;
	param->grp_bits = qbits;
	param->mod_size = pbits / 8;
	param->grp_size = qbits / 8;
	param->gen_size = pbits / 8;

	ret = cmrt_pke_complete(pke);
err:
	return ret;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_ffdh_parmgen(cmrt_pke_t pke,
					       size_t pbits,
					       size_t qbits,
					       struct cmrt_ffdh_param *param)
{
	z_syscall_verify_pke_context(pke);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(param, sizeof(struct cmrt_ffdh_param)));

	return z_impl_cmrt_pke_ffdh_parmgen(pke, pbits, qbits, param);
}
#include <syscalls/cmrt_pke_ffdh_parmgen_mrsh.c>

#endif /* CONFIG_USERSPACE */
