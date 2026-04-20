/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file configuration macros for riscv SOCs supporting the riscv
 *       privileged architecture specification
 */

#ifndef __SOC_COMMON_H_
#define __SOC_COMMON_H_

/* IRQ numbers */
#define RISCV_MACHINE_SOFT_IRQ       3UL  /* Machine Software Interrupt */
#ifndef CONFIG_SUPERVISOR_MODE
#define RISCV_MACHINE_TIMER_IRQ      7UL  /* Machine Timer Interrupt */
#define RISCV_MACHINE_EXT_IRQ        11UL /* Machine External Interrupt */
/* ECALL Exception numbers */
#define SOC_MCAUSE_ECALL_EXP         11UL /* Machine ECALL instruction */
#ifdef CONFIG_SOC_SERIES_RISCV_CMRT
#define SOC_MCAUSE_USER_ECALL_EXP    9UL  /* Supervisor ECALL instruction */
#else
#define SOC_MCAUSE_USER_ECALL_EXP    8UL  /* User ECALL instruction */
#endif
#else /* CONFIG_SUPERVISOR_MODE */
#define RISCV_MACHINE_TIMER_IRQ      5UL  /* Supervisor Timer Interrupt */
#define RISCV_MACHINE_EXT_IRQ        9UL  /* Supervisor External Interrupt */
/* ECALL Exception numbers */
#define SOC_MCAUSE_ECALL_EXP         9UL  /* Supervisor ECALL instruction */
#define SOC_MCAUSE_USER_ECALL_EXP    8UL  /* User ECALL instruction */
#endif
#define RISCV_LOAD_MISALIGNED_EXP    4UL  /* Load address misaligned */
#define RISCV_LOAD_ACCESS_EXP        5UL  /* Load access fault */
#define RISCV_STORE_MISALIGNED_EXP   6UL  /* Store/AMO address misaligned */
#define RISCV_STORE_ACCESS_EXP       7UL  /* Store/AMO access fault */

/* SOC-specific MSTATUS related info */
#ifndef CONFIG_SUPERVISOR_MODE
#define SOC_MSTATUS_REG              mstatus
#define SOC_MCAUSE_REG               mcause
#define SOC_MEPC_REG                 mepc
#define SOC_MIE_REG                  mie
#define SOC_MIP_REG                  mip
#define SOC_MSCRATCH_REG             mscratch
#define SOC_MTVEC_REG                mtvec
#else /* CONFIG_SUPERVISOR_MODE */
#define SOC_MSTATUS_REG              sstatus
#define SOC_MCAUSE_REG               scause
#define SOC_MEPC_REG                 sepc
#define SOC_MIE_REG                  sie
#define SOC_MIP_REG                  sip
#define SOC_MSCRATCH_REG             sscratch
#define SOC_MTVEC_REG                stvec
#endif

/* SOC-specific MCAUSE bitfields */
#ifdef CONFIG_64BIT
/* Interrupt Mask */
#define SOC_MCAUSE_IRQ_MASK          (1UL << 63)
/* Exception code Mask */
#define SOC_MCAUSE_EXP_MASK          0x7FFFFFFFFFFFFFFFUL
#else
/* Interrupt Mask */
#define SOC_MCAUSE_IRQ_MASK          (1UL << 31)
/* Exception code Mask */
#define SOC_MCAUSE_EXP_MASK          0x7FFFFFFFUL
#endif

/* SOC-Specific EXIT ISR command */
#ifndef CONFIG_SUPERVISOR_MODE
#define SOC_ERET                     mret
#else
#define SOC_ERET                     sret
#endif

/* SOC-Specific MSTATUS values. */
#ifndef CONFIG_SUPERVISOR_MODE
#define SOC_MSTATUS_PP_SHIFT         11
#define SOC_MSTATUS_PP_MASK          3UL
#define SOC_CURR_PRIVILEGE           3UL
#else
#define SOC_MSTATUS_PP_SHIFT         8
#define SOC_MSTATUS_PP_MASK          1UL
#define SOC_CURR_PRIVILEGE           1UL
#endif

/* CFI specific CSRs */
#ifndef CONFIG_SUPERVISOR_MODE
#define SOC_THREADSP_REG             0x7c2
#else
#define SOC_THREADSP_REG             0x9c2
#endif

#ifndef _ASMLANGUAGE

#if defined(CONFIG_RISCV_SOC_INTERRUPT_INIT)
void soc_interrupt_init(void);
#endif

#if defined(CONFIG_RISCV_HAS_PLIC)
void riscv_plic_irq_enable(uint32_t irq);
void riscv_plic_irq_disable(uint32_t irq);
int riscv_plic_irq_is_enabled(uint32_t irq);
void riscv_plic_set_priority(uint32_t irq, uint32_t priority);
int riscv_plic_get_irq(void);
#endif

#if defined(CONFIG_RISCV_HAS_SLIC)
void riscv_slic_irq_enable(uint32_t irq);
void riscv_slic_irq_disable(uint32_t irq);
int riscv_slic_irq_is_enabled(uint32_t irq);
void riscv_slic_set_priority(uint32_t irq, uint32_t priority);
int riscv_slic_get_irq(void);
#if defined(CONFIG_SOC_SERIES_RISCV_CMRT)
uint32_t cmrt_slic_irq_handler(uint32_t irqs);
#endif
#endif

#if defined(CONFIG_RISCV_HAS_AXI)
void riscv_axi_irq_enable(uint32_t irq);
void riscv_axi_irq_disable(uint32_t irq);
int riscv_axi_irq_is_enabled(uint32_t irq);
void riscv_axi_set_priority(uint32_t irq, uint32_t priority);
int riscv_axi_get_irq(void);
#endif

#endif /* !_ASMLANGUAGE */

#endif /* __SOC_COMMON_H_ */
