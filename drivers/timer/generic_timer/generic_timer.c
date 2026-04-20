#include <util.h>

#ifndef BOOTLOADER
#include "FreeRTOS.h"
#define CPU_HZ configCPU_CLOCK_HZ
#define TICK_HZ configTICK_RATE_HZ
#else
#define CPU_HZ (500000000)
#define TICK_HZ (1000)
#endif
#include "sys_io.h"
#include "gic.h"
#include "generic_timer.h"


static volatile uint64_t last_cycle;
#define CYCLE_PER_TICK  (CPU_HZ / TICK_HZ)

static inline void arch_timer_set_irq_mask(int mask)
{
	uint64_t cntv_ctl;

	__asm__ volatile ("mrs %[r], cntv_ctl_el0" : [r] "=r" (cntv_ctl));

	if (mask) {
		cntv_ctl |= CNTV_CTL_IMASK_BIT;
	} else {
		cntv_ctl &= ~CNTV_CTL_IMASK_BIT;
	}

	__asm__ volatile ("msr cntv_ctl_el0, %[i]" :: [i] "r" (cntv_ctl));
}

static inline void arch_timer_enable(int enable)
{
	uint64_t cntv_ctl;

	__asm__ volatile ("mrs %[r], cntv_ctl_el0" : [r] "=r" (cntv_ctl));

	if (enable) {
		cntv_ctl |= CNTV_CTL_ENABLE_BIT;
	} else {
		cntv_ctl &= ~CNTV_CTL_ENABLE_BIT;
	}

	__asm__ volatile ("msr cntv_ctl_el0, %[i]" :: [i] "r" (cntv_ctl));
}

static inline void arch_timer_set_compare(uint64_t val)
{
	__asm__ volatile ("msr cntv_cval_el0, %[i]" :: [i] "r" (val));
}

static inline uint64_t arch_timer_count(void)
{
	uint64_t val;

	__asm__ volatile ("mrs %[r], cntvct_el0" : [r] "=r" (val));

	return val;
}

void arch_timer_update_compare(void)
{
	uint64_t current_cycle = arch_timer_count();
	uint32_t delta_ticks = (uint32_t)((current_cycle - last_cycle) / CYCLE_PER_TICK);

	/* TODO: clock tick count */
	last_cycle += (uint64_t)delta_ticks * (uint64_t)CYCLE_PER_TICK;

	uint64_t next_cycle = last_cycle + CYCLE_PER_TICK;

	arch_timer_set_compare(next_cycle);
	arch_timer_set_irq_mask(0);
}

int generic_timer_init(void)
{
	/* IRQ CONNECT */
	arch_timer_set_compare(arch_timer_count() + last_cycle + CYCLE_PER_TICK);

	arch_timer_enable(1);
	gic_irq_enable(27);
	arch_timer_set_irq_mask(0);

	return 0;
}
