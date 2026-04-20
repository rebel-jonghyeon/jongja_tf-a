#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/timer_reg.h>

uint64_t get_timer_value(void)
{
	uint32_t ref_high = sys_read32(CMRT_TIMER_BASE + R_GTIME_COUNT_HIGH);
	uint32_t ref_high2 = sys_read32(CMRT_TIMER_BASE + R_GTIME_COUNT_HIGH);
	uint32_t ref_low = sys_read32(CMRT_TIMER_BASE + R_GTIME_COUNT_LOW);

	if (ref_high != ref_high2) {
		ref_high = ref_high2;
	}

	return ((uint64_t)ref_high << 32) | (uint64_t)ref_low;
}

uint64_t get_uptime_ms(void)
{
	extern int z_clock_hw_cycles_per_sec;

	return get_timer_value() * 1000 / z_clock_hw_cycles_per_sec;
}
