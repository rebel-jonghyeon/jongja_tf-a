/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @brief AXI Level Interrupt Controller (AXI) driver for CMRT
 */

#define DT_DRV_COMPAT xlnx_axi_intc

#include <kernel.h>
#include <arch/cpu.h>
#include <init.h>
#include <soc.h>
#include <sw_isr_table.h>
#include <drivers/cmrt/plic_reg.h>
#include <drivers/cmrt/sic_reg.h>

#define R_BASE DT_INST_REG_ADDR(0)
#define AXI_INTC_IRQ DT_INST_IRQN(0)

/* Registers from AXI Intc v4.1 Product Guide. */
typedef struct {
	uint32_t isr; /* interrupt status register */
	uint32_t ipr; /* interrupt pending register (optional) */
	uint32_t ier; /* interrupt enable register */
	uint32_t iar; /* interrupt acknowledge register */
	uint32_t sie; /* set interrupt enables (optional) */
	uint32_t cie; /* clear interrupt enables (optional) */
	uint32_t ivr; /* interrupt vector register */
	uint32_t mer; /* master enable register */
	uint32_t imr; /* interrupt mode register (optional) */
	uint32_t ilr; /* interrupt level register */
} cmrt_axi_t;

#define MER_ME  (1u << 0) /* hardware interrupt enable */
#define MER_HIE (1u << 1) /* master irq enable */

static volatile cmrt_axi_t *axi = (cmrt_axi_t *)(R_BASE);

static int save_irq;

static bool valid_axi_irq(uint32_t irq)
{
	return irq < (uint32_t)CONFIG_AXI_NUM_IRQS;
}

/**
 * @brief Enable a riscv AXI-specific interrupt line
 *
 * This routine enables a RISCV AXI-specific interrupt line.
 * riscv_axi_irq_enable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_enable function to enable external interrupts for
 * IRQS level == 4, whenever CONFIG_RISCV_HAS_AXI variable is set.
 * @param irq IRQ number to enable
 *
 * @return N/A
 */
void riscv_axi_irq_enable(uint32_t irq)
{
	if (!valid_axi_irq(irq)) {
		return;
	}
	axi->ier |= (1 << irq);
}

/**
 * @brief Disable a riscv AXI-specific interrupt line
 *
 * This routine disables a RISCV AXI-specific interrupt line.
 * riscv_axi_irq_disable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_disable function to disable external interrupts, for
 * IRQS level == 4, whenever CONFIG_RISCV_HAS_AXI variable is set.
 * @param irq IRQ number to disable
 *
 * @return N/A
 */
void riscv_axi_irq_disable(uint32_t irq)
{
	if (!valid_axi_irq(irq)) {
		return;
	}
	axi->ier &= ~(1 << irq);
}

/**
 * @brief Check if a riscv AXI-specific interrupt line is enabled
 *
 * This routine checks if a RISCV AXI-specific interrupt line is enabled.
 * @param irq IRQ number to check
 *
 * @return 1 or 0
 */
int riscv_axi_irq_is_enabled(uint32_t irq)
{
	return !!(axi->ier & (1 << (irq & (CONFIG_AXI_NUM_IRQS - 1))));
}

/**
 * @brief Set priority of a riscv AXI-specific interrupt line
 *
 * CMRT doesn't support priorities in its AXI, but arch code may call
 * this function if CONFIG_RISCV_HAS_AXI is defined, so let's have a
 * no-op.
 */
void riscv_axi_set_priority(uint32_t irq, uint32_t priority)
{
	ARG_UNUSED(irq);
	ARG_UNUSED(priority);
}

/**
 * @brief Get riscv AXI-specific interrupt line causing an interrupt
 *
 * This routine returns the RISCV AXI-specific interrupt line causing an
 * interrupt.
 * @return last IRQ number
 */
int riscv_axi_get_irq(void)
{
	return save_irq;
}

static void cmrt_axi_irq_handler(const void *arg)
{
	uint32_t irqs = axi->ipr;
	uint32_t pending = irqs;
	/* Handle irqs that have a valid handler. */
	while (pending != 0u) {
		uint32_t bit = find_msb_set(pending) - 1u;
		save_irq = (int)bit;
		if (!valid_axi_irq(bit)) {
			z_irq_spurious(NULL);
		}
		uint32_t irq = bit + CONFIG_4TH_LVL_ISR_TBL_OFFSET;

		/* Call the corresponding IRQ handler in _sw_isr_table */
		const struct _isr_table_entry *ite;
		ite = (struct _isr_table_entry *)&_sw_isr_table[irq];
		if (ite->isr != NULL && ite->isr != z_irq_spurious) {
			/* There is a valid handler for this line. */
			ite->isr(ite->arg);
		}
		pending &= ~(1u << bit);
	}
	/* Device interrupt handler lowered the irq reason and we need
	 * to acknowledge the irqs here. Acknowledge all in one call. */
	axi->iar = irqs;
}

/**
 * @brief Initialize CMRT AXI Level Interrupt Controller
 */
static int cmrt_axi_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	/* Setup IRQ handler for AXI driver */
	IRQ_CONNECT(AXI_INTC_IRQ, 0, cmrt_axi_irq_handler, NULL, 0);

	/* Reset INTC to a known state. */
	axi->ier = 0u;
	axi->iar = BIT_MASK(31);

	/* Allow AXI HW to raise interrupts. */
	axi->mer |= MER_ME | MER_HIE;

	/* Enable IRQ for AXI driver */
	irq_enable(AXI_INTC_IRQ);

	return 0;
}

SYS_INIT(cmrt_axi_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
