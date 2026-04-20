/*
 * Copyright (c) 2017-2020, ARM Limited and Contributors. All rights reserved.
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <cpu_macros.S>
#include <platform_def.h>

	/* ------------------------------------------------------------------
	 *  uintptr_t plat_get_my_entrypoint(void)
	 * ------------------------------------------------------------------
	 *
	 * This function is called with the called with the MMU and caches
	 * disabled (SCTLR_EL3.M = 0 and SCTLR_EL3.C = 0). The function is
	 * responsible for distinguishing between a warm and cold reset for the
	 * current CPU using platform-specific means. If it's a warm reset,
	 * then it returns the warm reset entrypoint point provided to
	 * plat_setup_psci_ops() during BL31 initialization. If it's a cold
	 * reset then this function must return zero.
	 *
	 * This function does not follow the Procedure Call Standard used by
	 * the Application Binary Interface for the ARM 64-bit architecture.
	 * The caller should not assume that callee saved registers are
	 * preserved across a call to this function.
	 */
	.globl	plat_get_my_entrypoint
func plat_get_my_entrypoint

	/* Cold reset only */
	mov	x0, #0
	ret

endfunc plat_get_my_entrypoint

	/* ------------------------------------------------------------------
	 * unsigned int plat_my_core_pos(void)
	 * ------------------------------------------------------------------
	 *
	 * This function returns the index of the calling CPU which is used as a
	 * CPU-specific linear index into blocks of memory (for example while
	 * allocating per-CPU stacks). This function will be invoked very early
	 * in the initialization sequence which mandates that this function
	 * should be implemented in assembly and should not rely on the
	 * avalability of a C runtime environment. This function can clobber x0
	 * - x8 and must preserve x9 - x29.
	 *
	 * This function plays a crucial role in the power domain topology
	 * framework in PSCI and details of this can be found in Power Domain
	 * Topology Design.
	 */
	.globl plat_my_core_pos
func plat_my_core_pos
	mrs	x0, mpidr_el1
	b	plat_core_pos_by_mpidr
endfunc plat_my_core_pos

	.globl plat_arm_calc_core_pos
func plat_arm_calc_core_pos
	and	x0, x0, #MPIDR_CPU_MASK
	ret
endfunc plat_arm_calc_core_pos

	.global plat_is_my_cpu_primary
func plat_is_my_cpu_primary
	mrs	x0, mpidr_el1
	and	x0, x0, #MPIDR_CPU_MASK
	cmp	x0, #0x0
	cset	x0, eq
	ret
endfunc plat_is_my_cpu_primary

	.global plat_secondary_cold_boot_setup
func plat_secondary_cold_boot_setup
#ifdef ZEBU_POC
#if (IMAGE_BL1)
poll_mailbox:
	mov_imm	x0, PLAT_SEC_ENTRY
	ldr	x1, [x0]
	cbz	x0, poll_mailbox
poll_release:
	mov_imm	x2, PLAT_CPUID_RELEASE
	ldr	x3, [x2]
	mrs	x4, mpidr_el1
	and	x4, x4, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp	x3, x4
	bne	poll_release
	mov_imm	x1, BL31_BASE
	br	x1
#elif (IMAGE_BL31)
poll_release:
	mov_imm	x2, PLAT_CPUID_RELEASE
	ldr	x3, [x2]
	mrs	x4, mpidr_el1
	and	x4, x4, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp	x3, x4
	bne	poll_release
	b	bl31_warm_entrypoint
#else
	ret
#endif
#else
	ret
#endif
endfunc plat_secondary_cold_boot_setup

	.global platform_mem_init
func platform_mem_init
	/* TODO: Nothing to do here, yet */
	ret
endfunc platform_mem_init

	.global plat_get_image_source
func plat_get_image_source
	/* TODO: Optional */
endfunc plat_get_image_source

	/* --------------------------------------------------------------------
	 * This handler does the following:
	 * - Set the L2 Data RAM latency to 2 (i.e. 3 cycles) for Cortex-A72
	 * --------------------------------------------------------------------
	 */
	.globl plat_reset_handler
func plat_reset_handler
	/* TODO: Optional */
endfunc plat_reset_handler

	/* ---------------------------------------------
	 * int plat_crash_console_init(void)
	 * Function to initialize the crash console
	 * without a C Runtime to print crash report.
	 * Clobber list : x0 - x4
	 * ---------------------------------------------
	 */
	.globl plat_crash_console_init
func plat_crash_console_init
	mov_imm	x0, CRASH_CONSOLE_BASE
	mov_imm	x1, CRASH_CONSOLE_CLK
	mov_imm	x2, CRASH_CONSOLE_BAUD_RATE
	mov w3, #0x0
	b	console_16550_core_init
endfunc plat_crash_console_init

	/* ---------------------------------------------
	 * int plat_crash_console_putc(void)
	 * Function to print a character on the crash
	 * console without a C Runtime.
	 * Clobber list : x1, x2
	 * ---------------------------------------------
	 */
	.globl plat_crash_console_putc
func plat_crash_console_putc
	mov_imm	x1, CRASH_CONSOLE_BASE
	b	console_16550_core_putc
endfunc plat_crash_console_putc

	/* ---------------------------------------------
	 * void plat_crash_console_flush()
	 * Function to force a write of all buffered
	 * data that hasn't been output.
	 * Out : void.
	 * Clobber list : x0, x1
	 * ---------------------------------------------
	 */
	.globl plat_crash_console_flush
func plat_crash_console_flush
	mov_imm	x0, CRASH_CONSOLE_BASE
	b	console_16550_core_flush
endfunc plat_crash_console_flush
