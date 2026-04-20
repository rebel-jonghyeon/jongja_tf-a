/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/pmu.h>
#include <drivers/cmrt/timer_reg.h>
#include <string.h>
#include <errno.h>
#ifdef CONFIG_SUPERVISOR_MODE
#include <drivers/cmrt/fboot.h>
#endif

#ifdef CONFIG_CMRT_FBOOT
__noinit static uint32_t csr_sie;
__noinit static uint32_t csr_stvec;
__noinit static uint32_t sic_sw_boot_status;
__noinit static uint32_t sic_interrupt_mask;
__noinit static uint32_t sic_kernel_version;
__noinit static uint32_t sic_sdk_version;
__noinit static uint32_t sic_scratch;
__noinit static uint32_t sic_custom[CMRT_SIC_NUM_CUSTOM];
__noinit static uint32_t timer_interrupt_mask;

void cmrt_pmu_save_os(void)
{
	/* Save state in case we go to low power. */
	csr_sie = csr_read(sie);
	csr_stvec = csr_read(stvec);
	sic_sw_boot_status = cmrt_read_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS);
	sic_interrupt_mask = cmrt_read_reg(CMRT_SIC_BASE, R_CORE_INTERRUPT_MASK);
	sic_kernel_version = cmrt_read_reg(CMRT_SIC_BASE, R_KERNEL_VERSION);
	sic_sdk_version = cmrt_read_reg(CMRT_SIC_BASE, R_SDK_VERSION);
	sic_scratch = cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0);
	for (int i = 0; i < CMRT_SIC_NUM_CUSTOM; i++) {
		sic_custom[i] = cmrt_read_reg(CMRT_SIC_BASE, R_CUSTOM_0 + i * 4);
	}
	timer_interrupt_mask = cmrt_read_reg(CMRT_TIMER_BASE, R_CORE_INTERRUPT_MASK);
}

void cmrt_pmu_restore_os(void)
{
	csr_write(sie, csr_sie);
	csr_write(stvec, csr_stvec);
	cmrt_write_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS, sic_sw_boot_status);
	cmrt_write_reg(CMRT_SIC_BASE, R_CORE_INTERRUPT_MASK, sic_interrupt_mask);
	cmrt_write_reg(CMRT_SIC_BASE, R_KERNEL_VERSION, sic_kernel_version);
	cmrt_write_reg(CMRT_SIC_BASE, R_SDK_VERSION, sic_sdk_version);
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, sic_scratch);
	for (int i = 0; i < CMRT_SIC_NUM_CUSTOM; i++) {
		cmrt_write_reg(CMRT_SIC_BASE, R_CUSTOM_0 + i * 4, sic_custom[i]);
	}
	cmrt_write_reg(CMRT_TIMER_BASE, R_CORE_INTERRUPT_MASK, timer_interrupt_mask);
	/* Update the number of low power events in security monitor. */
	extern int cmrt_pmu_events;
	cmrt_pmu_events++;
}
#endif

#ifdef CONFIG_SUPERVISOR_MODE
static volatile bool can_enter_low_power_mode;

int z_impl_cmrt_pmu_low_power(bool allowed)
{
	can_enter_low_power_mode = allowed;
	return 0;
}

extern struct __esf *idle_stack_init;
extern void reschedule(void);

void cmrt_pmu_to_idle(void)
{
	if (can_enter_low_power_mode && cmrt_sic_is_idle()) {
		/* This is for normal supervisor that can make syscalls. */
		(void)fboot_prepare_boot_bypass(idle_stack_init, &reschedule);

		/* Allow HLOS to enter low power mode command. */
		cmrt_write_reg(CMRT_SIC_BASE, R_POWER_DOWN_ALLOWED, POWER_DOWN_ALLOWED);
		can_enter_low_power_mode = false;
		/* The idle thread still needs to execute WFI. */
	}
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

int z_vrfy_cmrt_pmu_low_power(bool allowed)
{
	return z_impl_cmrt_pmu_low_power(allowed);
}
#include <syscalls/cmrt_pmu_low_power_mrsh.c>
#endif
