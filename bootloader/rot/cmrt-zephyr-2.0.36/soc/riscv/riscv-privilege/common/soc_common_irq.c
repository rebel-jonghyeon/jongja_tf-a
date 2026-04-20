/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief interrupt management code for riscv SOCs supporting the riscv
	  privileged architecture specification
 */
#include <irq.h>

void arch_irq_enable(unsigned int irq)
{
	uint32_t mie;

#if defined(CONFIG_RISCV_HAS_PLIC)
	unsigned int level = irq_get_level(irq);

	if (level == 2) {
		irq = irq_from_level_2(irq);
		riscv_plic_irq_enable(irq);
		return;
	}
#if defined(CONFIG_RISCV_HAS_SLIC)
	else if (level == 3) {
		irq = irq_from_level_3(irq);
		riscv_slic_irq_enable(irq);
		return;
	}
#if defined(CONFIG_RISCV_HAS_AXI)
	else if (level == 4) {
		irq = irq_from_level_4(irq);
		riscv_axi_irq_enable(irq);
		return;
	}
#endif
#endif
#endif

	/*
	 * CSR mie register is updated using atomic instruction csrrs
	 * (atomic read and set bits in CSR register)
	 */
#ifndef CONFIG_SUPERVISOR_MODE
	mie = csr_read_set(mie, 1UL << irq);
#else
	mie = csr_read_set(sie, 1UL << irq);
#endif
}

void arch_irq_disable(unsigned int irq)
{
	uint32_t mie;

#if defined(CONFIG_RISCV_HAS_PLIC)
	unsigned int level = irq_get_level(irq);

	if (level == 2) {
		irq = irq_from_level_2(irq);
		riscv_plic_irq_disable(irq);
		return;
	}
#if defined(CONFIG_RISCV_HAS_SLIC)
	else if (level == 3) {
		irq = irq_from_level_3(irq);
		riscv_slic_irq_disable(irq);
		return;
	}
#if defined(CONFIG_RISCV_HAS_AXI)
	else if (level == 4) {
		irq = irq_from_level_4(irq);
		riscv_axi_irq_disable(irq);
		return;
	}
#endif
#endif
#endif

	/*
	 * Use atomic instruction csrrc to disable device interrupt in mie CSR.
	 * (atomic read and clear bits in CSR register)
	 */
#ifndef CONFIG_SUPERVISOR_MODE
	mie = csr_read_clear(mie, 1UL << irq);
#else
	mie = csr_read_clear(sie, 1UL << irq);
#endif
};

void arch_irq_priority_set(unsigned int irq, unsigned int prio)
{
#if defined(CONFIG_RISCV_HAS_PLIC)
	unsigned int level = irq_get_level(irq);

	if (level == 2) {
		irq = irq_from_level_2(irq);
		riscv_plic_set_priority(irq, prio);
	}
#if defined(CONFIG_RISCV_HAS_SLIC)
	else if (level == 3) {
		irq = irq_from_level_3(irq);
		riscv_slic_set_priority(irq, prio);
	}
#if defined(CONFIG_RISCV_HAS_AXI)
	else if (level == 4) {
		irq = irq_from_level_4(irq);
		riscv_axi_set_priority(irq, prio);
	}
#endif
#endif
#endif

	return ;
}

int arch_irq_is_enabled(unsigned int irq)
{
	uint32_t mie;

#if defined(CONFIG_RISCV_HAS_PLIC)
	unsigned int level = irq_get_level(irq);

	if (level == 2) {
		irq = irq_from_level_2(irq);
		return riscv_plic_irq_is_enabled(irq);
	}
#if defined(CONFIG_RISCV_HAS_SLIC)
	else if (level == 3) {
		irq = irq_from_level_3(irq);
		return riscv_slic_irq_is_enabled(irq);
	}
#if defined(CONFIG_RISCV_HAS_AXI)
	else if (level == 4) {
		irq = irq_from_level_4(irq);
		return riscv_axi_irq_is_enabled(irq);
	}
#endif
#endif
#endif

#ifndef CONFIG_SUPERVISOR_MODE
	mie = csr_read(mie);
#else
	mie = csr_read(sie);
#endif
	return !!(mie & (1UL << irq));
}

#if defined(CONFIG_RISCV_SOC_INTERRUPT_INIT)
__weak void soc_interrupt_init(void)
{
	/* ensure that all interrupts are disabled */
	(void)irq_lock();

#ifndef CONFIG_SUPERVISOR_MODE
	csr_write(mie, 0);
	csr_write(mip, 0);
	csr_write(mideleg, 0);
	csr_write(medeleg, 0);
#else
	csr_write(sie, 0);
	csr_write(sip, 0);
#endif
}
#endif
