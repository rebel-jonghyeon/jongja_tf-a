/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @brief SoC Level Interrupt Controller (SLIC) driver for CMRT
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <init.h>
#include <soc.h>
#include <sw_isr_table.h>
#include <drivers/cmrt/sic.h>

#define R_BASE CMRT_SIC_BASE

static int save_irq;

static bool valid_soc_irq(uint32_t irq)
{
	return irq < (uint32_t)CONFIG_SOC_NUM_IRQS;
}

/**
 * @brief Enable a riscv SLIC-specific interrupt line
 *
 * This routine enables a RISCV SLIC-specific interrupt line.
 * riscv_slic_irq_enable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_enable function to enable external interrupts for
 * IRQS level == 3, whenever CONFIG_RISCV_HAS_SLIC variable is set.
 * @param irq IRQ number to enable
 *
 * @return N/A
 */
void riscv_slic_irq_enable(uint32_t irq)
{
	if (!valid_soc_irq(irq)) {
		return;
	}
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
	mask |= ((1UL << irq) & CMRT_SOC_INTERRUPT_IN_MASK);
	sys_write32(mask, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
}

/**
 * @brief Disable a riscv SLIC-specific interrupt line
 *
 * This routine disables a RISCV SLIC-specific interrupt line.
 * riscv_slic_irq_disable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_disable function to disable external interrupts, for
 * IRQS level == 3, whenever CONFIG_RISCV_HAS_SLIC variable is set.
 * @param irq IRQ number to disable
 *
 * @return N/A
 */
void riscv_slic_irq_disable(uint32_t irq)
{
	if (!valid_soc_irq(irq)) {
		return;
	}
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
	mask &= ~((1UL << irq) & CMRT_SOC_INTERRUPT_IN_MASK);
	sys_write32(mask, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
}

/**
 * @brief Check if a riscv SLIC-specific interrupt line is enabled
 *
 * This routine checks if a RISCV SLIC-specific interrupt line is enabled.
 * @param irq IRQ number to check
 *
 * @return 1 or 0
 */
int riscv_slic_irq_is_enabled(uint32_t irq)
{
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
	return (mask & ((1UL << irq) & CMRT_SOC_INTERRUPT_IN_MASK)) != 0u ? 1 : 0;
}

/**
 * @brief Set priority of a riscv SLIC-specific interrupt line
 *
 * CMRT doesn't support priorities in its SLIC, but arch code may call
 * this function if CONFIG_RISCV_HAS_SLIC variable is defined, so let's have a
 * no-op.
 */
void riscv_slic_set_priority(uint32_t irq, uint32_t priority)
{
	ARG_UNUSED(irq);
	ARG_UNUSED(priority);
}

/**
 * @brief Get riscv SLIC-specific interrupt line causing an interrupt
 *
 * This routine returns the RISCV SLIC-specific interrupt line causing an
 * interrupt.
 * @return last IRQ number
 */
int riscv_slic_get_irq(void)
{
	return save_irq;
}

uint32_t cmrt_slic_irq_handler(uint32_t irqs)
{
	uint32_t pending = irqs;
	/* Handle irqs that have a valid handler. */
	while (pending != 0u) {
		uint32_t bit = find_msb_set(pending) - 1u;
		save_irq = (int)bit;
		if (!valid_soc_irq(bit)) {
			z_irq_spurious(NULL);
		}
		uint32_t irq = bit + CONFIG_3RD_LVL_ISR_TBL_OFFSET;

		/* Call the corresponding IRQ handler in _sw_isr_table */
		const struct _isr_table_entry *ite;
		ite = (struct _isr_table_entry *)&_sw_isr_table[irq];
		if (ite->isr != NULL && ite->isr != z_irq_spurious) {
			/* There is a valid handler for this line. */
			ite->isr(ite->arg);
			irqs &= ~(1u << bit); /* mark it handled */
			sys_write32((1u << bit), (mm_reg_t)(R_BASE + R_CORE_INTERRUPT));
		}
		pending &= ~(1u << bit);
	}
	return irqs; /* return unhandled back to the caller */
}

/**
 * @brief Initialize CMRT SoC Level Interrupt Controller
 */
static int cmrt_slic_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	return 0;
}

SYS_INIT(cmrt_slic_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
