#include "fake_gic.h"

#ifdef USE_DILIGENT_PTR
_isr_table isr_table[GIC_INT_NUM];
void gic_irq_connect(uint32_t intid, isr_handler isr_func, void *cb_ref)
{
	isr_table[intid].isr = isr_func;
	isr_table[intid].cb_ref = cb_ref;
}

void gic_irq_enable(unsigned int intid)
{
}
#else
extern _isr_table isr_table[GIC_INT_NUM];
#endif // not USE_DILIGENT_PTR

void call_interrupt_handler(uint32_t intid)
{
	_isr_table *vector = &isr_table[intid];

	vector->isr(vector->cb_ref);
}
