/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Contributors: 2018 Antmicro <www.antmicro.com>
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain.h>
#include <drivers/cmrt/cc_reg.h>
#include <drivers/cmrt/fmc_reg.h>
#include <drivers/cmrt/sic_reg.h>
#include <drivers/cmrt/timer_reg.h>
#ifdef CONFIG_CMRT_EAC
#include <drivers/cmrt/eac_reg.h>
#endif

/* exports */
GTEXT(__start)
GTEXT(do_nmi_wrapper)

/* imports */
GTEXT(__initialize)
GTEXT(__irq_wrapper)
#ifdef CONFIG_SUPERVISOR_MODE
GTEXT(start_supervisor)
#endif
#ifdef CONFIG_CMRT_EAC
GTEXT(_cmrt_eac_nmi_error)
#endif
GTEXT(z_interrupt_stacks)

/*
 * 0x00001000: reset
 * 0x00001008: non-maskable interrupt (nmi) vector
 * 0x00001010: machine trap (mt) vector
 */
SECTION_FUNC(vectors, __start)
	.option norvc

	/* Call do_reset for reset vector */
	j do_reset
	.word 0
	/* Call do_nmi_wrapper for nmi vector */
nmivec: j do_nmi_wrapper
	.word 0
	/* Call do_nmi_wrapper for mt vector until kernel is initialized */
mtvec:	j do_nmi_wrapper

SECTION_FUNC(vectors, do_reset)
	csrwi mstatus, 0 /* disables all interrupts */
	la t0, mtvec
	csrw mtvec, t0
	csrwi stvec, 0 /* no supervisor running yet */

#ifdef CONFIG_WDT_DISABLE_AT_BOOT
	/* Disable watchdog. */
	li t0, CMRT_TIMER_BASE
	li t1, WATCHDOG_KEY_VALUE
	sw t1, R_WATCHDOG_KEY(t0)
	lw t1, R_WATCHDOG_CONTROL(t0)
	li t2, ~WATCHDOG_CONTROL_WDEN
	and t1, t1, t2
	sw t1, R_WATCHDOG_CONTROL(t0)
#endif
#ifdef CONFIG_JTAG_BEFORE_BOOT
	li t0, CMRT_SIC_BASE
	lw t1, R_DEVICE_LIFECYCLE(t0)
	li t2, CONFIG_LIFECYCLE_BEFORE_BOOT
	blt t1, t2, jtag_continue_boot
#ifdef CONFIG_BOOTBYPASS_BEFORE_BOOT
	lw t1, R_BOOT_BYPASS_STATUS(t0)
	beqz t1, jtag_continue_boot
#endif
	/*
	 * In order to have debugger support we need to mix and assert
	 * canary once. Values are taken from verification sample.
	 */
	li t0, CMRT_CC_BASE
	li t1, 0x5A04 /* lock for CPU in M mode */
	sw t1, R_HWC_LOCK_MASTER(t0)
	li t1, 0x4466CA57
	sw t1, R_ASSERT_VALUE0(t0)
	li t1, 0x20D8C722
	sw t1, R_ASSERT_VALUE1(t0)
	li t1, 0xABCDEF12
	sw t1, R_DATA_MIX(t0)
	li t1, CC_CONTROL_MIX
	sw t1, R_CORE_CONTROL(t0)
	li t2, HWC_STATUS_IDLE_LOCKED
cc_busy_loop:
	lw t1, R_CORE_STATUS(t0)
	bne t2, t1, cc_busy_loop
	li t1, CC_CONTROL_ASSERT
	sw t1, R_CORE_CONTROL(t0)
	li t1, HWC_CONTROL_FLUSH
	sw t1, R_CORE_CONTROL(t0)
	/*
	 * Now we can set permissions and TDV value to get debugger support.
	 */
	li t0, CMRT_FMC_BASE
	li t1, 0x5A04 /* lock for CPU in M mode */
	sw t1, R_HWC_LOCK_MASTER(t0)
	li t1, 1 << FMC_FEATURE_INT_MIN | 1 << FMC_FEATURE_EXT_MIN
	sw t1, R_OTP_FEATURE_W(t0)
	li t1, 0
	sw t1, R_FEATURE_ADDRESS(t0)
	li t1, 0x1
	sw t1, R_FEATURE_DATA(t0)
	sw t1, R_FEATURE_DATA_MASK(t0)
	li t1, FMC_CONTROL_FEATURE_WRITE
	sw t1, R_CORE_CONTROL(t0)
	li t2, HWC_STATUS_BUSY
fmc_busy_loop:
	lw t1, R_CORE_STATUS(t0)
	beq t2, t1, fmc_busy_loop
	li t1, HWC_CONTROL_FLUSH
	sw t1, R_CORE_CONTROL(t0)
	/*
	 * Execute CCC to clear permissions, note that TDV is not cleared.
	 */
	li t0, CMRT_SIC_BASE
	li t1, HWC_CCC_DO
	sw t1, R_HWC_CCC(t0)
ccc_busy_loop:
	lw t2, R_HWC_CCC_DONE(t0)
	bne t2, t1, ccc_busy_loop
	sw t2, R_HWC_CCC_DONE(t0)
	sw x0, R_HWC_CCC(t0)
jtag_continue_boot:
#endif
#ifdef CONFIG_CMRT_EAC_ERROR_DEBUG
	/* Read errors to be visible already here. */
	li t0, CMRT_EAC_BASE
	li t1, CMRT_SIC_BASE
	lw t2, R_HW_ERROR_INFO0(t0)
	sw t2, R_CUSTOM_0(t1)
	lw t2, R_HW_ERROR_INFO1(t0)
	sw t2, R_CUSTOM_1(t1)
	lw t2, R_SW_ERROR_INFO0(t0)
	sw t2, R_CUSTOM_2(t1)
	lw t2, R_SW_ERROR_INFO1(t0)
	sw t2, R_CUSTOM_3(t1)
#endif
#ifdef CONFIG_WAIT_BEFORE_BOOT
	li t0, CMRT_SIC_BASE
	lw t1, R_DEVICE_LIFECYCLE(t0)
	li t2, CONFIG_LIFECYCLE_BEFORE_BOOT
	blt t1, t2, fpga_continue_boot
#ifdef CONFIG_BOOTBYPASS_BEFORE_BOOT
	lw t1, R_BOOT_BYPASS_STATUS(t0)
	beqz t1, fpga_continue_boot
#endif
	/*
	 * Read SIC scratch register in a loop until it has a non zero value:
	 * 1. Value 0xFFFFFFFF means boot can continue.
	 * 2. Any other value is an address to jump to.
	 */
fpga_wait_loop:
#ifdef CONFIG_WDT_CMRT
	/* Feed watchdog. */
	li t0, CMRT_TIMER_BASE
	li t1, WATCHDOG_KEY_VALUE
	sw t1, R_WATCHDOG_KEY(t0)
	li t1, WATCHDOG_FEED_VALUE
	sw t1, R_WATCHDOG_FEED(t0)
#endif
	li t0, CMRT_SIC_BASE
	lw t1, R_SCRATCH_0(t0)
	beq t1, x0, fpga_wait_loop
	li t2, 0xFFFFFFFF
	beq t2, t1, fpga_continue_boot
	sw t2, R_SCRATCH_0(t0) /* to continue if we are debugging ourselves */
	jr t1
fpga_continue_boot:
#endif
#ifndef CONFIG_SUPERVISOR_MODE
	/* Jump to __reset */
	tail __reset
#else
	/* Jump to go into supervisor mode. */
	la a0, __reset
	tail start_supervisor
#endif

do_nmi_wrapper:
	/*
	 * NMI is always a fatal condition and we cannot do anything
	 * more than save the error and reboot. FPGA does not have any
	 * shadow CSRs (like mepc for example), which means there is
	 * no way to reliable return from NMI. Just setup stack to
	 * interrupt stack and call EAC to do its business.
	 */
	csrci mstatus, 0xF /* no interrupts any more */
#ifdef CONFIG_CMRT_EAC
	la sp, z_interrupt_stacks
	li t0, CONFIG_ISR_STACK_SIZE
	add sp, sp, t0
	/* Save current PC and RA to EAC registers. */
	csrr t0, mepc
	li t1, CMRT_EAC_BASE
	sw t0, R_SW_ERROR_INFO0(t1)
	sw ra, R_SW_ERROR_INFO1(t1)
	csrr a0, mcause /* pass mcause as argument */
	tail _cmrt_eac_nmi_error
#endif
wfi_loop:
	wfi /* stay here forever */
	j wfi_loop
