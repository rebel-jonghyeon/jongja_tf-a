#include <interrupt.h>

#if ENABLE_DEVICE_INTERRUPT_DRIVEN
void set_dev_interrupt_priority(uint32_t irq_num, uint32_t irq_prio)
{
#if defined(__TARGET_PCIE)
	NVIC_SetPriority((enum IRQn)irq_num, irq_prio);
#endif

#if defined(__TARGET_CP)
	/* TODO: Add GIC sequence */
	/* might be "gic_irq_set_priority()" */
#endif
}

void enable_dev_interrupt(uint32_t irq_num)
{
#if defined(__TARGET_PCIE)
	NVIC_EnableIRQ((enum IRQn)irq_num);
#endif

#if defined(__TARGET_CP)
	/* TODO: Add GIC sequence */
	/* might be "gic_irq_enable()" */
#endif
}

void enable_all_interrupts(void)
{
	portENABLE_INTERRUPTS();
}

void disable_all_interrupts(void)
{
	portDISABLE_INTERRUPTS();
}

#if defined(__TARGET_PCIE)
void connect_interrupt_with_handler(uint32_t irq_num, uint32_t irq_prio,
		uint32_t irq_type, void *handler, void *__attribute__((unused)) cb_ref)
{
	NVIC_SetVector((IRQn_Type)irq_num, (uint32_t)handler);
	NVIC_SetPriority(irq_num, irq_prio);
	NVIC_ClearPendingIRQ(irq_num);
	NVIC_EnableIRQ(irq_num);
	__DSB();
	__ISB();
	SCB_InvalidateICache();
}
#endif

#if defined(__TARGET_CP)
void connect_interrupt_with_handler(uint32_t irq_num, uint32_t irq_prio,
		uint32_t irq_type, void *handler, void *cb_ref)
{
	gic_irq_connect(irq_num, (isr_handler)handler, cb_ref);
	gic_irq_set_priority(irq_num, irq_prio, irq_type);	/* 'irq_type = IRQ_TYPE_LEVEL or IRQ_TYPE_EDGE */
	gic_irq_enable(irq_num);
}

void connect_interrupt_with_core_handler(uint32_t irq_num, uint32_t irq_prio,
										 uint32_t irq_type, uint32_t core_id, void *handler, void *cb_ref)
{
	gic_irq_connect(irq_num, (isr_handler)handler, cb_ref);
	gic_irq_route_dedicated_core(core_id, irq_num);
	gic_irq_set_priority(irq_num, irq_prio, irq_type);	/* 'irq_type = IRQ_TYPE_LEVEL or IRQ_TYPE_EDGE */
	gic_irq_enable(irq_num);
}
#endif

#endif /* ENABLE_DEVICE_INTERRUPT_DRIVEN */
