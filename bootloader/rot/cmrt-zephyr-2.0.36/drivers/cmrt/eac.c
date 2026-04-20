/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_eac

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/dd.h>
#ifdef CONFIG_CMRT_SAC_CONSOLE
#include <drivers/cmrt/sac.h>
#endif
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_EAC_BASE); /* device tree must match headers */

void cmrt_eac_set_core_error(uint8_t core_id, uint8_t core_error)
{
	unsigned int key = irq_lock();
	uint32_t value = sys_read32((mm_reg_t)(CMRT_SIC_BASE+R_INTERNAL_SW_ERR_INFO));
	if ((value >> 24) == 0 || core_error != 0) {
		/* Update core id but do not overwrite errors. */
		value &= 0x0000FFFFu;
		value |= (core_error << 24) | (core_id << 16);
		/* Write error status to INTERNAL_SW_ERR_INFO for HLOS */
		sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_INTERNAL_SW_ERR_INFO));
	}
	irq_unlock(key);
}

void cmrt_eac_set_internal_error(int major, int minor)
{
	unsigned int key = irq_lock();
	uint32_t value = sys_read32((mm_reg_t)(CMRT_SIC_BASE+R_INTERNAL_SW_ERR_INFO)) & 0xFFFF0000u;
	value |= ((((uint32_t)-minor) & 0xffu) << 8) | (((uint32_t)-major) & 0xffu);
	/* Write error status to INTERNAL_SW_ERR_INFO for HLOS */
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_INTERNAL_SW_ERR_INFO));
	irq_unlock(key);
}

void cmrt_eac_set_boot_status(uint8_t mcause, uint8_t nmi)
{
	unsigned int key = irq_lock();
	uint32_t value = sys_read32((mm_reg_t)(CMRT_SIC_BASE+R_SW_BOOT_STATUS));
	value |= ((uint32_t)mcause << 24) | ((uint32_t)nmi << 16);
	/* Write error status to SW_BOOT_STATUS for HLOS */
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_SW_BOOT_STATUS));
	irq_unlock(key);
}

void cmrt_eac_halt(uint32_t core_id, int major, int minor)
{
	if (core_id == CORE_ID_CPU) {
		/* Update PC and RA values before halting. */
		uint32_t pc = (uint32_t)(uintptr_t)cmrt_eac_halt;
		sys_write32(pc, (mm_reg_t)(R_BASE+R_SW_ERROR_INFO0));
		/* coverity[UNINIT] */
		register uint32_t ra __asm__ ("ra");
		sys_write32(ra, (mm_reg_t)(R_BASE+R_SW_ERROR_INFO1));
	}
#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
	cmrt_eac_set_internal_error(major, minor);

	(void)irq_lock();
#ifdef CONFIG_CMRT_ASIL_B_MODE
	if (!(major == -EFAULT && minor == 0)) {
		/* Safety alarm except when supervisor exits without error. */
		sys_write32((uint32_t)SW_SAFETY_ALARM, (mm_reg_t)(R_BASE+R_SW_SAFETY_ERROR));
	}
#endif
	sys_write32((uint32_t)SW_HALT_DO, (mm_reg_t)(R_BASE+R_SW_HALT));

	while (true) {
		arch_wfi();
	}
}

void cmrt_eac_reboot(void)
{
	(void)irq_lock();

	sys_write32((uint32_t)ESW_RESET_DO, (mm_reg_t)(CMRT_SIC_BASE+R_ESW_RESET));

	while (true) {
		arch_wfi();
	}
}

void cmrt_eac_reset(void)
{
#if IS_ENABLED(CMRT_SIC_BOOT_CONTROL)
	cmrt_eac_reboot();
#else
	(void)irq_lock();

	sys_write32((uint32_t)MPU_RESET_DO, (mm_reg_t)(CMRT_SIC_BASE+R_ESW_RESET));

	while (true) {
		arch_wfi();
	}
#endif
}

void cmrt_eac_kat_error(uint32_t core_id, int major, int minor)
{
	(void)irq_lock();
#ifdef CONFIG_CMRT_ASIL_B_MODE
	sys_write32((uint32_t)SAFETY_DIAG_ESW_KAT_ERR, (mm_reg_t)(CMRT_SIC_BASE+R_SAFETY_DIAGNOSIS_0));
#endif
	cmrt_eac_halt(core_id, major, minor);
}

void _cmrt_eac_nmi_error(uint32_t mcause)
{
	/* Called from NMI handler, read and clear NMI error. */
	uint32_t value = sys_read32((mm_reg_t)(R_BASE+R_HW_ERROR_INFO0));
	cmrt_eac_set_boot_status(mcause, value);
	if (value != 0u) {
		/* Called because of NMI. */
		cmrt_eac_halt(0, -EPIPE, -EINTR);
	} else if (mcause != 0u) {
		/* Called because of M mode trap. */
		cmrt_eac_halt(0, -EIO, -EINTR);
	} else {
		/* Called without reason. */
		cmrt_eac_halt(0, -EIO, -EFAULT);
	}
}

void cmrt_eac_init_early(void)
{
#ifdef CONFIG_CMRT_EAC_ERROR_DEBUG
	/* Write errors to SIC CUSTOM registers. */
	uint32_t value = sys_read32((mm_reg_t)(R_BASE+R_HW_ERROR_INFO0));
	sys_write32(value, (mm_reg_t)(R_BASE+R_HW_ERROR_INFO0));
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_CUSTOM_0));

	value = sys_read32((mm_reg_t)(R_BASE+R_HW_ERROR_INFO1));
	sys_write32(value, (mm_reg_t)(R_BASE+R_HW_ERROR_INFO1));
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_CUSTOM_1));

	value = sys_read32((mm_reg_t)(R_BASE+R_SW_ERROR_INFO0));
	sys_write32(0, (mm_reg_t)(R_BASE+R_SW_ERROR_INFO0));
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_CUSTOM_2));

	value = sys_read32((mm_reg_t)(R_BASE+R_SW_ERROR_INFO1));
	sys_write32(0, (mm_reg_t)(R_BASE+R_SW_ERROR_INFO1));
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_CUSTOM_3));
#endif
}

static int cmrt_eac_init(const struct device *dev)
{
	ARG_UNUSED(dev);
#ifndef CONFIG_SUPERVISOR_MODE
	cmrt_eac_init_early();
#endif
	return 0;
}

SYS_INIT(cmrt_eac_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
