/*
 * Copyright (c) 2018-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <toolchain.h>
#include <kernel_structs.h>
#ifdef CONFIG_CMRT_PMU
#include <drivers/cmrt/sic_reg.h>
#endif

/* exports */
GTEXT(start_supervisor)
GTEXT(do_irq_wrapper)

/* imports */
GTEXT(tboot_irq_wrapper)
GTEXT(do_nmi_wrapper)
GTEXT(cmrt_plic_init_early)
GTEXT(cmrt_sic_init_early)
#ifdef CONFIG_CMRT_SAC_CONSOLE
GTEXT(cmrt_sac_console_copy)
#endif
#ifdef CONFIG_CMRT_PMU
GTEXT(cmrt_pmu_restore_os)
#endif

/*
 * Security monitor code for starting supervisor mode OS.
 */
SECTION_FUNC(exception.other, start_supervisor)
	/* Disable machine interrupts. */
	csrwi mie, 0

	/* Set address to jump to. */
	csrw mepc, a0 /* address to __reset is given as parameter */

	/* Set mtvec to process syscalls from supervisor mode. */
	la a0, tboot_irq_wrapper
	lw a0, 0(a0)
	bne a0, x0, set_mtvec
	la a0, do_irq_wrapper /* default if tboot_irq_wrapper is not set */
set_mtvec:
	csrw mtvec, a0

	/* Delegate everything but machine and supervisor syscalls. */
	li a0, 0xB1FF
	csrw medeleg, a0
	li a0, 0x333
	csrw mideleg, a0

	/* Go to supervisor mode after mret with interrupts disabled. */
	li a0, 0x800
	csrs mstatus, a0

	/* Configure all PLIC interrupts to supervisor. */
	call cmrt_plic_init_early

	/* Reset SIC state and interrupt mask. */
	call cmrt_sic_init_early

#ifdef CONFIG_CMRT_SAC_CONSOLE
	call cmrt_sac_console_copy
#endif
#ifdef CONFIG_CMRT_PMU
	/* Are we on a boot bypass? */
	li t0, CMRT_SIC_BASE
	lw t1, R_BOOT_BYPASS_STATUS(t0)
	li t0, BOOT_BYPASS_ALLOWED | IN_MPU_RESET
	beq t1, t0, no_boot_bypass /* no bypass for soft reset */
	beq t1, x0, no_boot_bypass /* no bypass, status is empty */
	/* Yes, mret to reschedule in supervisor isr.S. */
	call cmrt_pmu_restore_os
	li t0, CMRT_SIC_BASE
	lw t1, R_BOOT_BYPASS_STATUS(t0)
	li t0, ~(BOOT_BYPASS_ALLOWED | IN_MPU_RESET)
	and t1, t1, t0 /* filter out command bits */
	mv sp, t1 /* initial idle thread stack frame */
no_boot_bypass:
#endif
#ifdef CONFIG_CMRT_CFI
	/* Make a clean trap stack frame for the mret. */
	csrw 0x7c2, sp
#endif
	/* Jump to mepc which was set above. */
	mret

SECTION_FUNC(exception.other, do_irq_wrapper)
	/* Machine mode handler for supervisor syscalls. */
	csrw mscratch, t0
	/*
	 * Make sure we are only here for ecalls. Anything else is
	 * misconfiguration and takes us to the nmi wrapper.
	 */
	csrr t0, mcause
	xori t0, t0, 0x9 /* ecall from S */
	bnez t0, to_nmi_wrapper

	/* We have supervisor if stvec has been set. */
	csrr t0, stvec
	beqz t0, to_nmi_wrapper

	/*
	 * If it is a swap or force, let supervisor handle it.
	 * Syscall number -2 is dedicated for swap and -1 for force.
	*/
	li t0, -2
	beq t0, a7, to_supervisor
	li t0, -1
	beq t0, a7, to_supervisor

	/* It is a syscall to machine mode. */
	csrr t0, mscratch
	jal x0, __irq_wrapper

to_supervisor:
	/*
	 * This ecall is for supervisor to handle. Just copy mepc, mcause
	 * and mstatus bits to respective supervisor registers.
	 */
	csrr t0, mepc
	csrw sepc, t0
	csrr t0, mcause
	csrw scause, t0
	/*
	 * Set sstatus to go into supervisor mode also after sret and
	 * preserve supervisor mode interrupt bit.
	 */
	csrr t0, mstatus
	andi t0, t0, (1UL << 1) /* read SIE */
	csrc sstatus, t0 /* clear it if enabled */
	slli t0, t0, 4 /* set it to SPIE */
	ori t0, t0, (1UL << 8) /* set SPP */
	csrs sstatus, t0
	/*
	 * Finally set mepc to stvec, but clear bit 0 (which can be
	 * set for a vectored handler.)  Restore original t0,
	 * and mret to supervisor trap handler.
	 */
	csrr t0, stvec
	andi t0, t0, -4
	csrw mepc, t0
	csrr t0, mscratch
	mret

to_nmi_wrapper:
	tail do_nmi_wrapper
