/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_plic

/**
 * @brief Platform Level Interrupt Controller (PLIC) driver for CMRT
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <init.h>
#include <soc.h>
#include <sw_isr_table.h>
#include <drivers/cmrt/plic_reg.h>

#define R_BASE DT_INST_REG_ADDR(0)

typedef struct {
    uint32_t interrupt;
    uint32_t machine_ie;
    uint32_t supervisor_ie;
    uint32_t machine_sw_int;
    uint32_t timer_ie;
} cmrt_plic_t;

#define PLIC (volatile cmrt_plic_t *)(R_BASE + R_PLIC_INTERRUPT)
#define PLIC_IRQS (CONFIG_3RD_LVL_ISR_TBL_OFFSET - CONFIG_2ND_LVL_ISR_TBL_OFFSET)

static int save_irq;

/**
 * @brief Enable a riscv PLIC-specific interrupt line
 *
 * This routine enables a RISCV PLIC-specific interrupt line.
 * riscv_plic_irq_enable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_enable function to enable external interrupts for
 * IRQS level == 2, whenever CONFIG_RISCV_HAS_PLIC variable is set.
 * @param irq IRQ number to enable
 *
 * @return N/A
 */
void riscv_plic_irq_enable(uint32_t irq)
{
#ifndef CONFIG_SUPERVISOR_MODE
	volatile cmrt_plic_t *const plic = PLIC;
	uint32_t key = irq_lock();
	plic->machine_ie |= (1UL << (irq & 31u));
	irq_unlock(key);
#else
	ARG_UNUSED(irq);
#endif
}

/**
 * @brief Disable a riscv PLIC-specific interrupt line
 *
 * This routine disables a RISCV PLIC-specific interrupt line.
 * riscv_plic_irq_disable is called by SOC_FAMILY_RISCV_PRIVILEGE
 * arch_irq_disable function to disable external interrupts, for
 * IRQS level == 2, whenever CONFIG_RISCV_HAS_PLIC variable is set.
 * @param irq IRQ number to disable
 *
 * @return N/A
 */
void riscv_plic_irq_disable(uint32_t irq)
{
#ifndef CONFIG_SUPERVISOR_MODE
	volatile cmrt_plic_t *const plic = PLIC;
	uint32_t key = irq_lock();
	plic->machine_ie &= ~(1UL << (irq & 31u));
	irq_unlock(key);
#else
	ARG_UNUSED(irq);
#endif
}

/**
 * @brief Check if a riscv PLIC-specific interrupt line is enabled
 *
 * This routine checks if a RISCV PLIC-specific interrupt line is enabled.
 * @param irq IRQ number to check
 *
 * @return 1 or 0
 */
int riscv_plic_irq_is_enabled(uint32_t irq)
{
	volatile cmrt_plic_t *const plic = PLIC;

#ifndef CONFIG_SUPERVISOR_MODE
	return (plic->machine_ie & (1UL << (irq & 31u))) != 0u ? 1 : 0;
#else
	return (plic->supervisor_ie & (1UL << (irq & 31u))) != 0u ? 1 : 0;
#endif
}

/**
 * @brief Set priority of a riscv PLIC-specific interrupt line
 *
 * CMRT doesn't support priorities in its PLIC, but arch code may call
 * this function if CONFIG_RISCV_HAS_PLIC is defined, so let's have a
 * no-op.
 */
void riscv_plic_set_priority(uint32_t irq, uint32_t priority)
{
	ARG_UNUSED(irq);
	ARG_UNUSED(priority);
}

/**
 * @brief Get riscv PLIC-specific interrupt line causing an interrupt
 *
 * This routine returns the RISCV PLIC-specific interrupt line causing an
 * interrupt.
 * @return last IRQ number
 */
int riscv_plic_get_irq(void)
{
	return save_irq;
}

static void cmrt_plic_irq_handler(const void *arg)
{
	ARG_UNUSED(arg);
	const struct _isr_table_entry *ite;
	volatile cmrt_plic_t *const plic = PLIC;

	/* Get the 'highest' interrupt bit number */
	uint32_t irq = find_msb_set(plic->interrupt);
	if (irq == 0u) {
		/*
		 * Very rarely there is a plic interrupt but no bits set.
		 * This is probably a HW bug, remove this code when fixed.
		 */
		return;
	}
	irq -= 1; /* bit number to index */
	/*
	 * Save IRQ in save_irq. To be used, if need be, by
	 * subsequent handlers registered in the _sw_isr_table table,
	 * as IRQ number held by the claim_complete register is
	 * cleared upon read.
	 */
	save_irq = (int)irq;

	/*
	 * If the IRQ is out of range, call z_irq_spurious.
	 * A call to z_irq_spurious will not return.
	 */
	if (irq >= PLIC_IRQS) {
		z_irq_spurious(NULL);
	}
	irq += CONFIG_2ND_LVL_ISR_TBL_OFFSET;

	/* Call the corresponding IRQ handler in _sw_isr_table */
	ite = (struct _isr_table_entry *)&_sw_isr_table[irq];
	ite->isr(ite->arg);
}

void cmrt_plic_init_early(void)
{
	volatile cmrt_plic_t *const plic = PLIC;
	/*
	 * Enable all interrupts. Supervisor does not have permissions
	 * to write this register. Device interrupts can be enabled
	 * using their CORE_INTERRUPT_MASK registers.
	 */
	plic->machine_ie = 0;
	plic->supervisor_ie = 0xFFFFFFFF;
	plic->timer_ie = PLIC_TIMER_STIE;
}

/**
 * @brief Initialize CMRT Platform Level Interrupt Controller
 */
static int cmrt_plic_init(const struct device *dev)
{
	ARG_UNUSED(dev);

#ifndef CONFIG_SUPERVISOR_MODE
	volatile cmrt_plic_t *const plic = PLIC;
#ifdef CONFIG_MULTITHREADING
	/* Enable all interrupts. */
	plic->machine_ie = 0xFFFFFFFF;
#else
	/* Enable only SIC interrupt for fboot. */
	plic->machine_ie = 1UL << PLIC_SIC_INTERRUPT;
#endif
#ifndef CONFIG_CMRT_FBOOT
	/* Enable machine timer interrupt for non-fboot. */
	plic->timer_ie = PLIC_TIMER_MTIE;
#endif
#endif
	/* Setup IRQ handler for PLIC driver */
	IRQ_CONNECT(RISCV_MACHINE_EXT_IRQ,
		    0,
		    cmrt_plic_irq_handler,
		    NULL,
		    0);

	/* Enable IRQ for PLIC driver */
	irq_enable(RISCV_MACHINE_EXT_IRQ);

	return 0;
}

SYS_INIT(cmrt_plic_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
