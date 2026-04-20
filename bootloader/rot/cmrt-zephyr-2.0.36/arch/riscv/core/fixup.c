/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <kernel_structs.h>
#include <zephyr/types.h>
#include <arch/cpu.h>
#include <string.h>
#include <cmrt_mpu.h>
#include <drivers/cmrt/sac.h>

#include "fixup.h"

static void fixup_load(void *addr, ulong_t *data_reg, ulong_t size, ulong_t extend)
{
	(void)memcpy(data_reg, addr, size);
	switch (extend) {
	case SIGN_EXT_16_32:
		if ((*data_reg & 0x8000u) != 0u) {
			*data_reg |= 0xffff0000;
			break;
		}
		/* fallthrough */
	case ZERO_EXT_16_32:
		*data_reg &= 0x0000ffff;
		break;
#ifdef CONFIG_CMRT_SAC_ACCESS_FIXUP
	case SIGN_EXT_8_32:
		if ((*data_reg & 0x80u) != 0u) {
			*data_reg |= 0xffffff00;
			break;
		}
		/* fallthrough */
	case ZERO_EXT_8_32:
		*data_reg &= 0x000000ff;
		break;
#endif
	default:
		break;
	}
}

static void fixup_store(void *addr, ulong_t *data_reg, ulong_t size)
{
	(void)memcpy(addr, data_reg, size);
}

static void *decode_inst(z_arch_esf_t *esf, ulong_t *data_reg, uint8_t *size,
			 uint8_t *mepc_adjust, uint8_t *flags)
{
	ulong_t *regs = (ulong_t *)esf;
	/* Copy previous instruction to inst. Whether or not it is a
	 * compressed instruction does not matter, since the opcode is
	 * always in the lowest 16 bits of the instruction word. */
	uint32_t inst, base_reg;
	int32_t offset;
	(void)memcpy(&inst, (void *)esf->mepc, sizeof(uint32_t));

	/* Decode it enough to see if, and how to, handle it. */
	*size = sizeof(uint32_t);
	*mepc_adjust = sizeof(uint32_t);
	*flags = 0;
	if ((inst & MASK_SW) == MATCH_SW) {
		/* store word, S-type format */
		*flags |= IS_WRITE;
		base_reg = BASE_REG_S(inst);
		offset = OFFSET_S(inst);
		*data_reg = DATA_REG_S(inst);
	} else if ((inst & MASK_SH) == MATCH_SH) {
		/* store half word, S-type format */
		*flags |= IS_WRITE;
		base_reg = BASE_REG_S(inst);
		offset = OFFSET_S(inst);
		*data_reg = DATA_REG_S(inst);
		*size = sizeof(uint16_t);
	} else if ((inst & MASK_LH) == MATCH_LH) {
		/* load half word with sign extension, I-type format */
		base_reg = BASE_REG_I(inst);
		offset = OFFSET_I(inst);
		*data_reg = DATA_REG_I(inst);
		*size = sizeof(uint16_t);
		*flags |= SIGN_EXT_16_32;
	} else if ((inst & MASK_LHU) == MATCH_LHU) {
		/* load half word with zero extension, I-type format */
		base_reg = BASE_REG_I(inst);
		offset = OFFSET_I(inst);
		*data_reg = DATA_REG_I(inst);
		*size = sizeof(uint16_t);
		*flags |= ZERO_EXT_16_32;
	} else if ((inst & MASK_LW) == MATCH_LW) {
		/* load word, I-type format */
		base_reg = BASE_REG_I(inst);
		offset = OFFSET_I(inst);
		*data_reg = DATA_REG_I(inst);
	} else if ((inst & MASK_C_SW) == MATCH_C_SW) {
		/* store word, compressed instruction, CS-type format */
		*flags |= IS_WRITE;
		base_reg = BASE_REG_CS(inst);
		offset = OFFSET_CS(inst);
		*data_reg = DATA_REG_CS(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else if ((inst & MASK_C_LW) == MATCH_C_LW) {
		/* load word, compressed instruction, CL-type format */
		base_reg = BASE_REG_CL(inst);
		offset = OFFSET_CL(inst);
		*data_reg = DATA_REG_CL(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else if ((inst & MASK_C_SWSP) == MATCH_C_SWSP) {
		/* store word stack relative, CSS-type format */
		*flags |= IS_WRITE;
		base_reg = BASE_REG_CSS(inst);
		offset = OFFSET_CSS(inst);
		*data_reg = DATA_REG_CSS(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else if ((inst & MASK_C_LWSP) == MATCH_C_LWSP) {
		/* load word stack relative, CI-type format */
		base_reg = BASE_REG_CI(inst);
		offset = OFFSET_CI(inst);
		*data_reg = DATA_REG_CI(inst);
		*mepc_adjust = sizeof(uint16_t);
	} else {
#ifdef CONFIG_CMRT_SAC_ACCESS_FIXUP
		/* Code below decodes byte access instructions. Byte access
		 * can't raise misaligned access exception, so these are needed
		 * only if SAC access fixup is enabled. */
		*size = 1;
		*mepc_adjust = sizeof(uint32_t);
		if ((inst & MASK_LB) == MATCH_LB) {
			/* load byte with sign extension, I-type format */
			*flags |= SIGN_EXT_8_32;
			base_reg = BASE_REG_I(inst);
			offset = OFFSET_I(inst);
			*data_reg = DATA_REG_I(inst);
		} else if ((inst & MASK_LBU) == MATCH_LBU) {
			/* load byte with zero extension, I-type format */
			*flags |= ZERO_EXT_8_32;
			base_reg = BASE_REG_I(inst);
			offset = OFFSET_I(inst);
			*data_reg = DATA_REG_I(inst);
		} else if ((inst & MASK_SB) == MATCH_SB) {
			/* store byte, S-type format */
			*flags |= IS_WRITE;
			base_reg = BASE_REG_S(inst);
			offset = OFFSET_S(inst);
			*data_reg = DATA_REG_S(inst);
		} else
#endif
		{
			/* No idea what to do with this. */
			return NULL;
		}
	}
	return (void *)(regs[base_reg] + offset);
}

bool cmrt_access_fixup(z_arch_esf_t *esf)
{
	/* Handle CPU traps for misaligned read/write and 64bit indirect
	 * SAC read/write to make SAC look like directly mapped memory. */
	ulong_t data_reg;
	uint8_t size, flags;
	uint8_t mepc_adjust = 0;
	void *addr = decode_inst(esf, &data_reg, &size, &mepc_adjust, &flags);
	if (addr == NULL || size > 4) {
		/* RV32 accesses at most a word at a time. */
		return false;
	}
	bool is_write = (flags & IS_WRITE) == IS_WRITE;
	ulong_t *regs = (ulong_t *)esf;
#ifdef CONFIG_CMRT_SAC_ACCESS_FIXUP
	uint32_t wdata[2];
	uintptr_t waddr = (uintptr_t)addr & ~3u;
#ifndef CONFIG_RISCV_MISALIGNED_FIXUP
	if (((uintptr_t)addr & (size - 1)) != 0)  {
		/* Misaligned SAC access not supported. */
		return false;
	}
#endif
#endif
	if (is_sac_ptr((uintptr_t)addr)) {
#ifdef CONFIG_CMRT_SAC_ACCESS_FIXUP
		uint64_t sac_addr = cmrt_sac_translate((mem_addr_t)addr);
		if (!cmrt_sac_has_access(_current, sac_addr, size, is_write)) {
			/* Permission error. */
			return false;
		}
		/* To support misaligned SAC access, copy two words. */
		wdata[0] = cmrt_sac_read32(waddr);
#ifdef CONFIG_RISCV_MISALIGNED_FIXUP
		wdata[1] = cmrt_sac_read32(waddr + 4u);
#endif
		/* And set address point to the copy. */
		addr = (void *)((uint8_t *)wdata + ((uintptr_t)addr & 3u));
#else
		/* SAC access fixup not supported. */
		return false;
#endif
	} else {
		/* Check MPU rules because HW does not do it. */
#ifdef CONFIG_SUPERVISOR_MODE
		uint32_t privilege = MPU_PRIVILEGE_S;
#else
		uint32_t privilege = MPU_PRIVILEGE_M;
#endif
#ifdef CONFIG_USERSPACE
		if ((_current->base.user_options & K_USER) == K_USER) {
			privilege = MPU_PRIVILEGE_U;
		}
#endif
		uint32_t bits = is_write ? MPU_MODE_WRITABLE : MPU_MODE_READABLE;
		if (!cmrt_mpu_has_access((uint32_t)(uintptr_t)addr, size, privilege, bits)) {
			/* No access to this memory. */
			return false;
		}
	}
	if (is_write) {
		fixup_store(addr, &regs[data_reg], size);
#ifdef CONFIG_CMRT_SAC_ACCESS_FIXUP
		if (is_sac_ptr((uintptr_t)waddr)) {
			/* Write back the two SAC words from the copy. */
			cmrt_sac_write32(wdata[0], waddr);
#ifdef CONFIG_RISCV_MISALIGNED_FIXUP
			cmrt_sac_write32(wdata[1], waddr + 4u);
#endif
		}
#endif
	} else {
		fixup_load(addr, &regs[data_reg], size, flags);
	}
	/* Set mepc to jump over handled instruction. */
	esf->mepc += mepc_adjust;
	return true;
}
