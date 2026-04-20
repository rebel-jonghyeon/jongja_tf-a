#include "FreeRTOS.h"
#include "generic_timer.h"
#include "gic.h"
#include "cpu.h"
#include "task.h"
#include "smp.h"
#include "interrupt.h"

extern _isr_table isr_table[];

uint32_t isr_flag[configNUMBER_OF_CORES] = {0};

void vSetupTickInterrupt(void)
{
	/* TODO: SoC-600 timer must be enabled here at real h/w */

	if (portGET_CORE_ID() == 0) {
#if (__TARGET_CP == 1)
		connect_interrupt_with_handler(SGI_IPI + 1, 1, IRQ_TYPE_LEVEL, FreeRTOS_Tick_Handler, NULL);
#else
		generic_timer_init();
		connect_interrupt_with_handler(CNTVIRQ, 1, IRQ_TYPE_LEVEL, FreeRTOS_Tick_Handler, NULL);
#endif
	}

	connect_interrupt_with_handler(SGI_IPI, 1, IRQ_TYPE_LEVEL, ipi_handler, NULL);
}

void vClearTickInterrupt(void)
{
	arch_timer_update_compare();
}

void vApplicationIRQHandler(uint32_t icc_iar)
{
	uint32_t intid;

	intid = icc_iar & 0x3ff;

	if (intid < GIC_INT_NUM) {
		int core_id = portGET_CORE_ID();

		isr_flag[core_id]++;

		if (isr_table[intid].isr != NULL) {
			isr_table[intid].isr(isr_table[intid].cb_ref);
		}

		isr_flag[core_id]--;
	}
}
