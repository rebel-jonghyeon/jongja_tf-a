/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <toolchain.h>
#include <kernel_structs.h>
#ifdef CONFIG_CMRT_CFI
#include <arch/cpu.h>
#endif

/* Exports, define as weak for security monitor to roll its own. */
WTEXT(start_supervisor)

/*
 * Security monitor code for starting supervisor mode OS.
 *
 * Code here will be placed into ROM if CONFIG_SUPERVISOR_MODE is on.
 * This makes it possible to run and debug any supervisor project stand alone.
 * However, when security monitor loads and starts a supervisor image,
 * It will use its own version of start_supervisor.
 */
SECTION_FUNC(vectors, start_supervisor)
	/* Disable machine interrupts. */
	csrwi mie, 0

	/* Jump to given reset at mret. */
	csrw mepc, a0

	/* Delegate everything but machine syscalls. */
	li t0, 0xBBFF
	csrw medeleg, t0
	li t0, 0x333
	csrw mideleg, t0

	/* Go to supervisor mode after mret with interrupts disabled. */
	li t0, 0x800
	csrs mstatus, t0

	/*
	 * Configure timer and watchdog here in machine mode.
	 * Supervisor can only rearm both timer and watchdog, it cannot
	 * change configuration. Code below is for running supervisor
	 * Zephyr stand-alone here, normally all this code would be
	 * executed in fboot in normal device driver init functions.
	 */
	la sp, z_interrupt_stacks
	li t0, CONFIG_ISR_STACK_SIZE
	add sp, sp, t0
#ifdef CONFIG_CMRT_PLIC
	call cmrt_plic_init_early
#endif
#ifdef CONFIG_CMRT_EAC
	call cmrt_eac_init_early
#endif
#ifdef CONFIG_CMRT_SAC
	call cmrt_sac_init_early
#endif
#ifdef CONFIG_CMRT_MPU
	call cmrt_mpu_init_early
#endif
#ifdef CONFIG_CMRT_CFI
	/* Initialize shadow stack frame pointer. */
	addi sp, sp, -ARCH_STACK_PTR_ALIGN
	csrw 0x7c2, sp
#endif
	/* Jump to __reset, mepc was set above */
	mret
