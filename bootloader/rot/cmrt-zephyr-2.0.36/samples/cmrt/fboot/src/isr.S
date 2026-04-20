/*
 * Copyright (c) 2016 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2018 Foundries.io Ltd
 * Copyright (c) 2020 BayLibre, SAS
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain.h>
#include <linker/sections.h>
#include <offsets_short.h>
#include <arch/cpu.h>
#include <sys/util.h>
#include <kernel.h>
#include <syscall.h>
#include <arch/riscv/csr.h>
#ifdef CONFIG_CMRT_EAC
#include <drivers/cmrt/eac_reg.h>
#endif

/* imports */
GDATA(_sw_isr_table)
GTEXT(__soc_is_irq)
GTEXT(__soc_handle_irq)
GTEXT(z_interrupt_stacks)
GTEXT(_Fault)
#ifdef CONFIG_CMRT_SAC_CONSOLE
GTEXT(cmrt_sac_console_copy)
#endif

/* exports */
GTEXT(__irq_wrapper)

/* use ABI name of registers for the sake of simplicity */

/*
 * Generic architecture-level IRQ handling, along with callouts to
 * SoC-specific routines.
 *
 * Architecture level IRQ handling includes basic context save/restore
 * of standard registers and calling ISRs registered at Zephyr's driver
 * level.
 *
 * Since RISC-V does not completely prescribe IRQ handling behavior,
 * implementations vary (some implementations also deviate from
 * what standard behavior is defined). Hence, the arch level code expects
 * the following functions to be provided at the SOC level:
 *
 *     - __soc_is_irq: decide if we're handling an interrupt or an exception
 *     - __soc_handle_irq: handle SoC-specific details for a pending IRQ
 *       (e.g. clear a pending bit in a SoC-specific register)
 *
 * If CONFIG_RISCV_SOC_CONTEXT_SAVE=y, calls to SoC-level context save/restore
 * routines are also made here. For details, see the Kconfig help text.
 */

/*
 * Handler called upon each exception/interrupt/fault
 * In this architecture, system call (ECALL) is used to perform context
 * switching or IRQ offloading (when enabled).
 */
SECTION_FUNC(exception.entry, __irq_wrapper)
	/* Maybe switch to privileged stack. */
	csrw SOC_MSCRATCH_REG, t0
	csrr t0, SOC_MSTATUS_REG
	srli t0, t0, SOC_MSTATUS_PP_SHIFT
	andi t0, t0, SOC_MSTATUS_PP_MASK
	addi t0, t0, -SOC_CURR_PRIVILEGE
	beqz t0, is_privileged
	/* Use the main stack as the privileged stack. */
	la t0, z_main_stack
	/* Add as multiples of 2047 (the maximum immediate value supported
	 * by 'addi', plus the remainer) to go to the stack beginning. */
#if (CONFIG_MAIN_STACK_SIZE % 2047) > 0
	addi t0, t0, CONFIG_MAIN_STACK_SIZE % 2047
#endif
	.rept CONFIG_MAIN_STACK_SIZE / 2047
	addi t0, t0, 2047
	.endr

	j use_privileged
is_privileged:
	/* Use current stack, this is native fboot code. */
	mv t0, sp
use_privileged:
	/* Now using privileged stack. */
	addi t0, t0, -__z_arch_esf_t_SIZEOF
	/* Save supervisor stack pointer. */
	sw sp, __z_arch_esf_t_sp_OFFSET(t0)
	mv sp, t0
	csrr t0, SOC_MSCRATCH_REG
	/*
	 * Save all registers on current thread stack. It's not always
	 * required to save callee-saved registers here, but we do it to
	 * make a simpler bug free trap handler as a trade-off to speed.
	 * Note that we save also x0 for possible fault handler actions.
	 */
	sw zero, __z_arch_esf_t_zero_OFFSET(sp)
	sw ra, __z_arch_esf_t_ra_OFFSET(sp)
	/* sp was handled above */
	sw gp, __z_arch_esf_t_gp_OFFSET(sp)
	sw tp, __z_arch_esf_t_tp_OFFSET(sp)
	sw t0, __z_arch_esf_t_t0_OFFSET(sp)
	sw t1, __z_arch_esf_t_t1_OFFSET(sp)
	sw t2, __z_arch_esf_t_t2_OFFSET(sp)
	sw s0, __z_arch_esf_t_s0_OFFSET(sp)
	sw s1, __z_arch_esf_t_s1_OFFSET(sp)
	sw a0, __z_arch_esf_t_a0_OFFSET(sp)
	sw a1, __z_arch_esf_t_a1_OFFSET(sp)
	sw a2, __z_arch_esf_t_a2_OFFSET(sp)
	sw a3, __z_arch_esf_t_a3_OFFSET(sp)
	sw a4, __z_arch_esf_t_a4_OFFSET(sp)
	sw a5, __z_arch_esf_t_a5_OFFSET(sp)
	sw a6, __z_arch_esf_t_a6_OFFSET(sp)
	sw a7, __z_arch_esf_t_a7_OFFSET(sp)
	sw s2, __z_arch_esf_t_s2_OFFSET(sp)
	sw s3, __z_arch_esf_t_s3_OFFSET(sp)
	sw s4, __z_arch_esf_t_s4_OFFSET(sp)
	sw s5, __z_arch_esf_t_s5_OFFSET(sp)
	sw s6, __z_arch_esf_t_s6_OFFSET(sp)
	sw s7, __z_arch_esf_t_s7_OFFSET(sp)
	sw s8, __z_arch_esf_t_s8_OFFSET(sp)
	sw s9, __z_arch_esf_t_s9_OFFSET(sp)
	sw s10, __z_arch_esf_t_s10_OFFSET(sp)
	sw s11, __z_arch_esf_t_s11_OFFSET(sp)
	sw t3, __z_arch_esf_t_t3_OFFSET(sp)
	sw t4, __z_arch_esf_t_t4_OFFSET(sp)
	sw t5, __z_arch_esf_t_t5_OFFSET(sp)
	sw t6, __z_arch_esf_t_t6_OFFSET(sp)

	/* Save MEPC register */
	csrr t0, SOC_MEPC_REG
	sw t0, __z_arch_esf_t_mepc_OFFSET(sp)
#ifdef CONFIG_CMRT_EAC
	/* Save current PC and RA to EAC registers. */
	li t1, CMRT_EAC_BASE
	sw t0, R_SW_ERROR_INFO0(t1)
	sw ra, R_SW_ERROR_INFO1(t1)
#endif
	/* Save SOC-specific MSTATUS register */
	csrr t0, SOC_MSTATUS_REG
	sw t0, __z_arch_esf_t_mstatus_OFFSET(sp)

	/*
	 * Check if exception is the result of an interrupt or not.
	 * (SOC dependent). Following the RISC-V architecture spec, the MSB
	 * of the mcause register is used to indicate whether an exception
	 * is the result of an interrupt or an exception/fault. But for some
	 * SOCs (like pulpino or riscv-qemu), the MSB is never set to indicate
	 * interrupt. Hence, check for interrupt/exception via the __soc_is_irq
	 * function (that needs to be implemented by each SOC). The result is
	 * returned via register a0 (1: interrupt, 0 exception)
	 */
	jal ra, __soc_is_irq

	/* If a0 != 0, jump to is_interrupt */
	bnez a0, is_interrupt

	/*
	 * If the exception is the result of an ECALL, check whether to
	 * handle system call from the supervisor. Otherwise call _Fault
	 * to report the exception.
	 */
	csrr t0, SOC_MCAUSE_REG
	li t2, SOC_MCAUSE_EXP_MASK
	and t0, t0, t2
	li t1, SOC_MCAUSE_USER_ECALL_EXP
	beq t0, t1, is_kernel_syscall

	/*
	 * Call _Fault to handle exception.
	 * Stack pointer is pointing to a z_arch_esf_t structure, pass it
	 * to _Fault (via register a0).
	 * If _Fault shall return, set return address to
	 * no_reschedule to restore stack.
	 */
	mv a0, sp
	la ra, no_reschedule
	tail _Fault

is_kernel_syscall:
	/*
	 * A syscall is the result of an ecall instruction, in which case the
	 * MEPC will contain the address of the ecall instruction.
	 * Increment saved MEPC by 4 to prevent triggering the same ecall
	 * again upon exiting the ISR.
	 *
	 * It's safe to always increment by 4, even with compressed
	 * instructions, because the ecall instruction is always 4 bytes.
	 */
	lw t0, __z_arch_esf_t_mepc_OFFSET(sp)
	addi t0, t0, 4
	sw t0, __z_arch_esf_t_mepc_OFFSET(sp)

	/* Place a default system call result */
	li a0, -14 /* -EFAULT */

	/* Load syscall number */
	lw a7, __z_arch_esf_t_a7_OFFSET(sp)
	la t0, FBOOT_SYSCALL_TABLE_SIZE
	bgeu a7, t0, syscall_return

	/* Restore argument registers from user stack */
	lw a0, __z_arch_esf_t_a0_OFFSET(sp)
	lw a1, __z_arch_esf_t_a1_OFFSET(sp)
	lw a2, __z_arch_esf_t_a2_OFFSET(sp)
	lw a3, __z_arch_esf_t_a3_OFFSET(sp)
	lw a4, __z_arch_esf_t_a4_OFFSET(sp)
	lw a5, __z_arch_esf_t_a5_OFFSET(sp)

	/* Load syscall function. */
	la t0, fboot_syscall_table

	slli t1, a7, RV_REGSHIFT /* determine offset from indice value */
	add t0, t0, t1 /* Ttble addr + offset = function addr */
	lw t3, 0x00(t0) /* load function address */

	/*
	 * Execute syscall function. Note that interrupts are disabled,
	 * security monitor executes the syscall as an atomic operation.
	 */
	jalr t3

syscall_return:
	/* Update a0 (return value) */
	sw a0, __z_arch_esf_t_a0_OFFSET(sp)

#ifdef CONFIG_CMRT_SAC_CONSOLE
	/* Make sure we see security monitor logs. */
	call cmrt_sac_console_copy
#endif
	j no_reschedule

is_interrupt:
	/*
	 * Save current thread stack pointer and switch
	 * stack pointer to interrupt stack.
	 */

	/* Save thread stack pointer to temp register t0 */
	mv t0, sp

	/* Switch to interrupt stack */
	la t2, z_interrupt_stacks
	li t3, CONFIG_ISR_STACK_SIZE
	add sp, t2, t3

	/* Save thread stack pointer on interrupt stack */
	addi sp, sp, -ARCH_STACK_PTR_ALIGN
	sw t0, 0x00(sp)

on_irq_stack:
	/* Get IRQ causing interrupt */
	csrr a0, SOC_MCAUSE_REG
	li t0, SOC_MCAUSE_EXP_MASK
	and a0, a0, t0

	/*
	 * Clear pending IRQ generating the interrupt at SOC level
	 * Pass IRQ number to __soc_handle_irq via register a0
	 */
	jal ra, __soc_handle_irq

	/*
	 * Call corresponding registered function in _sw_isr_table.
	 * (table is 2-word wide, we should shift index accordingly)
	 */
	la t0, _sw_isr_table
	slli a0, a0, (RV_REGSHIFT + 1)
	add t0, t0, a0

	/* Load argument in a0 register */
	lw a0, 0x00(t0)

	/* Load ISR function address in register t1 */
	lw t1, RV_REGSIZE(t0)

	/* Call ISR function */
	jalr ra, t1

on_thread_stack:
	/* Restore thread stack pointer */
	lw t0, 0x00(sp)
	mv sp, t0

no_reschedule:
	/* Restore MEPC register */
	lw t0, __z_arch_esf_t_mepc_OFFSET(sp)
	csrw SOC_MEPC_REG, t0

	/* Restore SOC-specific MSTATUS register */
	lw t0, __z_arch_esf_t_mstatus_OFFSET(sp)
	csrw SOC_MSTATUS_REG, t0

	/* Restore all registers from thread stack */
	/* lw zero, __z_arch_esf_t_zero_OFFSET(sp) */
	lw ra, __z_arch_esf_t_ra_OFFSET(sp)
	/* sp is handled below */
	lw gp, __z_arch_esf_t_gp_OFFSET(sp)
	lw tp, __z_arch_esf_t_tp_OFFSET(sp)
	lw t0, __z_arch_esf_t_t0_OFFSET(sp)
	lw t1, __z_arch_esf_t_t1_OFFSET(sp)
	lw t2, __z_arch_esf_t_t2_OFFSET(sp)
	lw s0, __z_arch_esf_t_s0_OFFSET(sp)
	lw s1, __z_arch_esf_t_s1_OFFSET(sp)
	lw a0, __z_arch_esf_t_a0_OFFSET(sp)
	lw a1, __z_arch_esf_t_a1_OFFSET(sp)
	lw a2, __z_arch_esf_t_a2_OFFSET(sp)
	lw a3, __z_arch_esf_t_a3_OFFSET(sp)
	lw a4, __z_arch_esf_t_a4_OFFSET(sp)
	lw a5, __z_arch_esf_t_a5_OFFSET(sp)
	lw a6, __z_arch_esf_t_a6_OFFSET(sp)
	lw a7, __z_arch_esf_t_a7_OFFSET(sp)
	lw s2, __z_arch_esf_t_s2_OFFSET(sp)
	lw s3, __z_arch_esf_t_s3_OFFSET(sp)
	lw s4, __z_arch_esf_t_s4_OFFSET(sp)
	lw s5, __z_arch_esf_t_s5_OFFSET(sp)
	lw s6, __z_arch_esf_t_s6_OFFSET(sp)
	lw s7, __z_arch_esf_t_s7_OFFSET(sp)
	lw s8, __z_arch_esf_t_s8_OFFSET(sp)
	lw s9, __z_arch_esf_t_s9_OFFSET(sp)
	lw s10, __z_arch_esf_t_s10_OFFSET(sp)
	lw s11, __z_arch_esf_t_s11_OFFSET(sp)
	lw t3, __z_arch_esf_t_t3_OFFSET(sp)
	lw t4, __z_arch_esf_t_t4_OFFSET(sp)
	lw t5, __z_arch_esf_t_t5_OFFSET(sp)
	lw t6, __z_arch_esf_t_t6_OFFSET(sp)

	/* Return to caller stack. */
	lw sp, __z_arch_esf_t_sp_OFFSET(sp)

	/* Call SOC_ERET to exit ISR */
	SOC_ERET
