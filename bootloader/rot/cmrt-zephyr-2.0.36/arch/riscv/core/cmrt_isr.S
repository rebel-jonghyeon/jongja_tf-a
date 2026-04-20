/*
 * Copyright (c) 2016 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2018 Foundries.io Ltd
 * Copyright (c) 2020 BayLibre, SAS
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
#ifdef CONFIG_CMRT_PMU
#include <drivers/cmrt/sic_reg.h>
#endif
#ifdef CONFIG_CMRT_SAC2
#include <drivers/cmrt/sac_reg.h>
#endif
#include <errno.h>

/* imports */
GDATA(_sw_isr_table)
GTEXT(__soc_is_irq)
GTEXT(__soc_handle_irq)
GTEXT(_Fault)
#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
GTEXT(__soc_save_context)
GTEXT(__soc_restore_context)
#endif

GTEXT(_k_neg_eagain)
GTEXT(_is_next_thread_current)
GTEXT(z_get_next_ready_thread)

#ifdef CONFIG_INSTRUMENT_THREAD_SWITCHING
GTEXT(z_thread_mark_switched_in)
GTEXT(z_thread_mark_switched_out)
#ifdef CONFIG_TRACING
GTEXT(sys_trace_isr_enter)
#endif
#endif

#ifdef CONFIG_IRQ_OFFLOAD
GTEXT(_offload_routine)
#endif

#ifdef CONFIG_USERSPACE
GTEXT(z_riscv_do_syscall)
GTEXT(z_riscv_configure_user_allowed_stack)
GTEXT(z_interrupt_stacks)
GTEXT(z_riscv_do_syscall_start)
GTEXT(z_riscv_do_syscall_end)
#endif

/* exports */
GTEXT(__irq_wrapper)
#ifdef CONFIG_CMRT_PMU
GTEXT(reschedule)
#endif

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
	csrw SOC_MSCRATCH_REG, t0
#ifdef CONFIG_USERSPACE
	/* Maybe switch to privileged stack. */
	csrr t0, SOC_MSTATUS_REG
	srli t0, t0, SOC_MSTATUS_PP_SHIFT
	andi t0, t0, SOC_MSTATUS_PP_MASK
	addi t0, t0, -SOC_CURR_PRIVILEGE
	beqz t0, is_privileged
	/* User mode, switch to privileged stack. */
	la t0, _kernel
	lw t0, _kernel_offset_to_current(t0)
	lw t0, _thread_offset_to_priv_stack_start(t0)
	/* Add as multiples of 2047 (the maximum immediate value supported
	 * by 'addi', plus the remainer) to go to the stack beginning. */
#if (CONFIG_PRIVILEGED_STACK_SIZE % 2047) > 0
	addi t0, t0, CONFIG_PRIVILEGED_STACK_SIZE % 2047
#endif
	.rept CONFIG_PRIVILEGED_STACK_SIZE / 2047
	addi t0, t0, 2047
	.endr

	j use_privileged
#endif
is_privileged:
	/* Use current stack otherwise. */
	mv t0, sp
use_privileged:
	/* Now using privileged stack. */
	addi t0, t0, -__z_arch_esf_t_SIZEOF
	/* Save stack pointer before the trap. */
	sw sp, __z_arch_esf_t_sp_OFFSET(t0)
	/* Switch to the new stack. */
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

#if defined(CONFIG_RISCV_GP)
	/* Set global pointer to privileged value. */
	.option push
	.option norelax
	la gp, __global_pointer$
	.option pop
#endif
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

#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
	/* Handle context saving at SOC level. */
	addi a0, sp, __z_arch_esf_t_soc_context_OFFSET
	jal ra, __soc_save_context
#endif

#ifdef CONFIG_USERSPACE
	/* Clear user mode variable, we are in higher privilege now. */
	la t0, is_user_mode
	sb zero, 0x00(t0)
#endif
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
	 * perform a context-switch or an IRQ offload. Otherwise call _Fault
	 * to report the exception.
	 */
	csrr t0, SOC_MCAUSE_REG
	li t2, SOC_MCAUSE_EXP_MASK
	and t0, t0, t2
	li t1, SOC_MCAUSE_ECALL_EXP
	/*
	 * If mcause == SOC_MCAUSE_ECALL_EXP, handle system call from
	 * kernel thread.
	 */
	beq t0, t1, is_kernel_syscall

#ifdef CONFIG_USERSPACE
	li t1, SOC_MCAUSE_USER_ECALL_EXP
	/*
	 * If mcause == SOC_MCAUSE_USER_ECALL_EXP, handle system call from
	 * user thread, otherwise handle fault.
	 */
	beq t0, t1, is_user_syscall
#endif
	/*
	 * Call _Fault to handle exception.
	 * Stack pointer is pointing to a z_arch_esf_t structure, pass it
	 * to _Fault (via register a0). If _Fault shall return, set return
	 * address to no_reschedule to restore stack.
	 */
	mv a0, sp
	la ra, no_reschedule
	tail _Fault

is_kernel_syscall:
#ifdef CONFIG_USERSPACE
	/* Check if it is a return from user syscall */
	csrr t0, SOC_MEPC_REG
	la t1, z_riscv_do_syscall_start
	bltu t0, t1, not_user_syscall
	la t1, z_riscv_do_syscall_end
	bleu t0, t1, return_from_syscall
not_user_syscall:
#endif
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

#ifdef CONFIG_IRQ_OFFLOAD
	/*
	 * Determine if the system call is the result of an IRQ offloading.
	 * Done by checking if _offload_routine is not pointing to NULL.
	 * If NULL, jump to reschedule to perform a context-switch, otherwise,
	 * jump to is_interrupt to handle the IRQ offload.
	 */
	la t0, _offload_routine
	lw t1, 0x00(t0)
	bnez t1, is_interrupt
#endif
#ifdef CONFIG_USERSPACE
	/*
	 * Check for forced syscall,
	 * otherwise go to reschedule to handle context-switch
	 */
	li t0, FORCE_SYSCALL_ID
	bne a7, t0, reschedule

	lw a0, __z_arch_esf_t_a0_OFFSET(sp)

	/* Check for user_mode_enter function */
	la t0, arch_user_mode_enter
	bne t0, a0, reschedule

	lw a0, __z_arch_esf_t_a1_OFFSET(sp)
	lw a1, __z_arch_esf_t_a2_OFFSET(sp)
	lw a2, __z_arch_esf_t_a3_OFFSET(sp)
	lw a3, __z_arch_esf_t_a4_OFFSET(sp)
	/*
	 * MRET will be done in the following function because
	 * restore caller-saved registers is not need anymore
	 * due to user mode jump (new stack/context).
	 */
	j z_riscv_user_mode_enter_syscall
#endif
	/*
	 * Go to reschedule to handle context-switch
	 */
	j reschedule

#ifdef CONFIG_USERSPACE
is_user_syscall:
	/*
	 * A syscall is the result of an ecall instruction, in which case the
	 * MEPC will contain the address of the ecall instruction.
	 * Increment saved MEPC by 4 to prevent triggering the same ecall
	 * again upon exiting the ISR.
	 *
	 * It is safe to always increment by 4, even with compressed
	 * instructions, because the ecall instruction is always 4 bytes.
	 */
	lw t1, __z_arch_esf_t_mepc_OFFSET(sp)
	addi t1, t1, 4
	sw t1, __z_arch_esf_t_mepc_OFFSET(sp)

	/* Restore argument registers from user stack */
	lw a0, __z_arch_esf_t_a0_OFFSET(sp)
	lw a1, __z_arch_esf_t_a1_OFFSET(sp)
	lw a2, __z_arch_esf_t_a2_OFFSET(sp)
	lw a3, __z_arch_esf_t_a3_OFFSET(sp)
	lw a4, __z_arch_esf_t_a4_OFFSET(sp)
	lw a5, __z_arch_esf_t_a5_OFFSET(sp)
	mv a6, sp
	lw a7, __z_arch_esf_t_a7_OFFSET(sp)

#ifdef CONFIG_CMRT_USERSPACE_SYSCALLS
	la t2, _k_syscall_table /* default syscall table */
#else
#ifdef CONFIG_CMRT_CONTAINER_SYSCALLS
	la t2, _c_syscall_table /* container syscall table */
#else
#error "No user mode system calls defined in configuration!"
#endif
#endif
	la t0, _kernel
	lw t1, _kernel_offset_to_current(t0)
	lw t0, _thread_offset_to_user_options(t1)
	andi t0, t0, K_CONTAINER
	beqz t0, not_user_container
	/* Validate syscall limit for user container */
	li t0, C_SYSCALL_BASE
	bltu a7, t0, bad_syscall_id
	li t0, C_SYSCALL_BASE + C_SYSCALL_LIMIT
	bgeu a7, t0, bad_syscall_id
	/* Use container syscall table for z_riscv_do_syscall */
	addi a7, a7, -C_SYSCALL_BASE
#ifdef CONFIG_CMRT_USERSPACE_SYSCALLS
	la t2, _c_syscall_table /* container syscall table */
#endif
	j valid_syscall_id

not_user_container:
#ifdef CONFIG_CMRT_USERSPACE_SYSCALLS
	/* validate syscall limit */
	li t0, K_SYSCALL_LIMIT
	bltu a7, t0, valid_syscall_id
#endif
bad_syscall_id:
	/* Bad syscall id, set arg1 to bad id and set call_id to SYSCALL_BAD */
	mv a0, a7
#ifdef CONFIG_CMRT_USERSPACE_SYSCALLS
	li a7, K_SYSCALL_BAD
#else
	li a7, C_SYSCALL_BAD
#endif
valid_syscall_id:
	/* Prepare to jump into do_syscall function */
	la t0, z_riscv_do_syscall
	csrw SOC_MEPC_REG, t0

	/* Force kernel mode for syscall execution */
	li t0, MSTATUS_MPP_M
	csrs SOC_MSTATUS_REG, t0

#ifdef CONFIG_CMRT_CFI
	/* Initialize shadow stack frame pointer. */
	csrw SOC_THREADSP_REG, sp
#endif
	SOC_ERET

return_from_syscall:
	/* Retrieve a0 (return value) from current stack frame */
	lw a0, __z_arch_esf_t_a0_OFFSET(sp)
	/* Go back to the original frame in privileged stack */
	addi sp, sp, __z_arch_esf_t_SIZEOF
	/* Update a0 (return value) in the original frame */
	sw a0, __z_arch_esf_t_a0_OFFSET(sp)

	j no_reschedule
#endif

is_interrupt:
#ifdef CONFIG_CMRT_PMU
	/* Clear power down allowed after the idle thread. */
	li t0, 0
	li t2, CMRT_SIC_BASE
	sw t0, R_POWER_DOWN_ALLOWED(t2)
#endif
	/* Save thread stack pointer to temp register t0 */
	mv t0, sp

	/* Switch to interrupt stack */
	la t2, _kernel
	lw sp, _kernel_offset_to_irq_stack(t2)
	/*
	 * Save thread stack pointer on interrupt stack
	 * In RISC-V, stack pointer needs to be 16-byte aligned
	 */
	addi sp, sp, -ARCH_STACK_PTR_ALIGN
	sw t0, 0x00(sp)

on_irq_stack:
	/* Increment _kernel.cpus[0].nested variable */
	lw t3, _kernel_offset_to_nested(t2)
	addi t3, t3, 1
	sw t3, _kernel_offset_to_nested(t2)

#ifdef CONFIG_IRQ_OFFLOAD
	/*
	 * If we are here due to a system call, t1 register should != 0.
	 * In this case, perform IRQ offloading, otherwise jump to call_irq
	 */
	beqz t1, call_irq
	/*
	 * Call z_irq_do_offload to handle IRQ offloading.
	 * Set return address to on_thread_stack in order to jump there
	 * upon returning from z_irq_do_offload
	 */
	la ra, on_thread_stack
	tail z_irq_do_offload
call_irq:
#endif
#ifdef CONFIG_TRACING_ISR
	call sys_trace_isr_enter
#endif
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
	/* Get reference to _kernel */
	la t1, _kernel

	/* Decrement _kernel.cpus[0].nested variable */
	lw t2, _kernel_offset_to_nested(t1)
	addi t2, t2, -1
	sw t2, _kernel_offset_to_nested(t1)

	/* Restore thread stack pointer */
	lw t0, 0x00(sp)
	mv sp, t0

#ifdef CONFIG_STACK_SENTINEL
	call z_check_stack_sentinel
	la t1, _kernel
#endif

#ifndef CONFIG_PREEMPT_ENABLED
	/* Only preempt config can reschedule. */
	j no_reschedule
#endif

reschedule:
	/*
	 * Check if the current thread is the same as the thread on the ready Q.
	 * If so, do not reschedule.
	 * Note:
	 *   Sometimes this code is executed back-to-back before the target
	 *   thread has a chance to run. If this happens, the current thread
	 *   and the target thread will be the same.
	 */
	la t0, _kernel
	lw t1, _kernel_offset_to_current(t0)
	lw t2, _kernel_offset_to_ready_q_cache(t0)
	beq t1, t2, no_reschedule

#if CONFIG_INSTRUMENT_THREAD_SWITCHING
	call z_thread_mark_switched_out
	la t0, _kernel
	lw t1, _kernel_offset_to_current(t0)
#endif
	/*
	 * Save stack pointer of current thread and set the default return value
	 * of z_swap to -EAGAIN for the thread.
	 */
	sw sp, _thread_offset_to_sp(t1)
	li t3, -EAGAIN
	sw t3, _thread_offset_to_swap_return_value(t1)

	/* Get next thread to schedule. */
	lw t1, _kernel_offset_to_ready_q_cache(t0)

	/* Set _kernel.current to new thread loaded in t1 */
	sw t1, _kernel_offset_to_current(t0)

	/* Switch to new thread privileged stack */
	lw sp, _thread_offset_to_sp(t1)

#ifdef CONFIG_CMRT_SAC2
	/* Switch to new thread SAC base */
	li t3, CMRT_SAC_BASE
	lw t2, _thread_offset_to_sac_cpu_base_hi(t1)
	sw t2, R_CPU_ADDR_HI(t3)
	lw t2, _thread_offset_to_sac_cpu_base_lo(t1)
	sw t2, R_CPU_ADDR_LO(t3)
#endif
#ifdef CONFIG_USERSPACE
	/* Check if this is user mode thread */
	lw t0, _thread_offset_to_user_options(t1)
	andi t0, t0, K_USER
	beqz t0, not_user_mode
	mv a0, t1
	/* Set MPU rules for the user mode thread */
	jal ra, z_riscv_configure_user_allowed_stack
not_user_mode:
#endif
#if CONFIG_INSTRUMENT_THREAD_SWITCHING
	call z_thread_mark_switched_in
#endif

no_reschedule:
#ifdef CONFIG_USERSPACE
	/* Check if we are going into user mode */
	lw t0, __z_arch_esf_t_mstatus_OFFSET(sp)
	srli t0, t0, SOC_MSTATUS_PP_SHIFT
	andi t0, t0, SOC_MSTATUS_PP_MASK
	addi t0, t0, -SOC_CURR_PRIVILEGE
	beqz t0, kernel_thread

	li t0, MSTATUS_MPRV
	csrc SOC_MSTATUS_REG, t0

	/* Set user mode variable */
	li t1, 0x1
	la t0, is_user_mode
	sb t1, 0x00(t0)
kernel_thread:
#endif
#ifdef CONFIG_RISCV_SOC_CONTEXT_SAVE
	/* Restore context at SOC level */
	addi a0, sp, __z_arch_esf_t_soc_context_OFFSET
	jal ra, __soc_restore_context
#endif
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

	/* Finally, restore stack pointer before the trap */
	lw sp, __z_arch_esf_t_sp_OFFSET(sp)

	/* Call SOC_ERET to exit ISR */
	SOC_ERET
