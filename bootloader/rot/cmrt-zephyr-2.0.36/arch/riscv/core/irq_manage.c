/*
 * Copyright (c) 2016 Jean-Paul Etienne <fractalclone@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <kernel_internal.h>
#include <logging/log.h>
LOG_MODULE_DECLARE(os, CONFIG_KERNEL_LOG_LEVEL);

FUNC_NORETURN void z_irq_spurious(const void *unused)
{
	ulong_t mcause;

	ARG_UNUSED(unused);

#ifndef CONFIG_SUPERVISOR_MODE
	mcause = csr_read(mcause);
#else
	mcause = csr_read(scause);
#endif
	mcause &= SOC_MCAUSE_EXP_MASK;

	LOG_ERR("Spurious interrupt detected! IRQ: %ld", mcause);
#if defined(CONFIG_RISCV_HAS_PLIC)
	if (mcause == RISCV_MACHINE_EXT_IRQ) {
		LOG_ERR("PLIC interrupt line causing the IRQ: %d",
			riscv_plic_get_irq());
	}
#endif
	z_riscv_fatal_error(K_ERR_SPURIOUS_IRQ, NULL);
}

#ifdef CONFIG_DYNAMIC_INTERRUPTS
int arch_irq_connect_dynamic(unsigned int irq, unsigned int priority,
			     void (*routine)(const void *parameter),
			     const void *parameter, uint32_t flags)
{
	ARG_UNUSED(flags);

	z_isr_install(irq, routine, parameter);

#if defined(CONFIG_RISCV_HAS_PLIC)
	if (irq_get_level(irq) == 2) {
		irq = irq_from_level_2(irq);

		riscv_plic_set_priority(irq, priority);
	}
#if defined(CONFIG_RISCV_HAS_SLIC)
	else if (irq_get_level(irq) == 3) {
		irq = irq_from_level_3(irq);

		riscv_slic_set_priority(irq, priority);
	}
#endif
#if defined(CONFIG_RISCV_HAS_AXI)
	else if (irq_get_level(irq) == 4) {
		irq = irq_from_level_4(irq);

		riscv_axi_set_priority(irq, priority);
	}
#endif
#else
	ARG_UNUSED(priority);
#endif
	return irq;
}
#endif /* CONFIG_DYNAMIC_INTERRUPTS */
