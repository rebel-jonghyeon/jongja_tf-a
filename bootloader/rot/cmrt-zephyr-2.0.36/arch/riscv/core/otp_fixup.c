/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <kernel_structs.h>
#include <zephyr/types.h>
#include <arch/cpu.h>
#include <string.h>
#include <drivers/cmrt/omc.h>

#include "fixup.h"

static void *decode_inst(z_arch_esf_t *esf, ulong_t *data_reg, uint8_t *mepc_adjust)
{
	ulong_t *regs = (ulong_t *)esf;
	/* Copy previous instruction to inst. Whether or not it is a
	 * compressed instruction does not matter, since the opcode is
	 * always in the lowest 16 bits of the instruction word. */
	uint32_t inst, base_reg;
	int32_t offset;
	(void)memcpy(&inst, (void *)esf->mepc, sizeof(uint32_t));

	/* Decode it enough to see if, and how to, handle it. */
	if ((inst & MASK_LW) == MATCH_LW) {
		/* load word, I-type format */
		base_reg = BASE_REG_I(inst);
		offset = OFFSET_I(inst);
		*data_reg = DATA_REG_I(inst);
		*mepc_adjust = sizeof(uint32_t);
	} else if ((inst & MASK_C_LW) == MATCH_C_LW) {
		/* load word, compressed instruction, CL-type format */
		base_reg = BASE_REG_CL(inst);
		offset = OFFSET_CL(inst);
		*data_reg = DATA_REG_CL(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else if ((inst & MASK_C_LWSP) == MATCH_C_LWSP) {
		/* load word stack relative, CI-type format */
		base_reg = BASE_REG_CI(inst);
		offset = OFFSET_CI(inst);
		*data_reg = DATA_REG_CI(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else {
		/* No idea what to do with this. */
		return NULL;
	}
	return (void *)(regs[base_reg] + offset);
}

bool otp_access_fixup(z_arch_esf_t *esf)
{
	/* Handle CPU traps for OTP reads that had uncorrectable ECC errors.
	 * Return fixed value 0xffffffff for all such words. Note that OTP
	 * permission failures cause NMIs which are not handled here. */
	ulong_t data_reg;
	uint8_t mepc_adjust = 0;
	void *addr = decode_inst(esf, &data_reg, &mepc_adjust);
	if (addr == NULL || ((uintptr_t)addr & 0x3) != 0) {
		/* Misaligned OTP access not supported. */
		return false;
	}
	if ((uintptr_t)addr < CMRT_OTP_BASE ||
	    (uintptr_t)addr >= CMRT_OTP_BASE + CMRT_OTP_SIZE) {
		/* Not in the OTP memory region. */
		return false;
	}
#if defined(CONFIG_SUPERVISOR_MODE) && defined(CONFIG_USERSPACE)
	if ((_current->base.user_options & K_USER) == K_USER) {
		/* User thread must be in a syscall. Code in valid_syscall_id
		 * in cmrt_isr.S sets the previous privilege to S in sstatus. */
		ulong_t sstatus = csr_read(sstatus);
		if ((sstatus & MSTATUS_SPP) == 0) {
			/* Not allowed, it's direct reference from user. */
			return false;
		}
	}
#endif
	/* Write all ones for reads with ECC error. For the reader this
	 * looks like valid data. However, the OMC driver will return an
	 * error from cmrt_omc_read. */
	ulong_t *regs = (ulong_t *)esf;
	regs[data_reg] = 0xffffffff;

	/* Set mepc to jump over handled instruction. */
	esf->mepc += mepc_adjust;
	return true;
}
