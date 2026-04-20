#pragma once

#include <stdint.h>

static inline uint32_t get_current_count(void)
{
	uint32_t current_count;

	current_count = *(uint32_t *)0xE000E018U;

	return current_count;
}

static inline uint32_t get_reload_count(void)
{
	uint32_t reload_count;

	reload_count = *(uint32_t *)0xE000E014U;

	return reload_count;
}

/* SysTick timer */
/* CM7 = Count-Down */
static inline void delay_count(uint64_t target_count)
{
	/* CM7 has to consider ticks between 'last_count' & 'current_count' */
	uint64_t tick_interval = get_reload_count();
	uint64_t elapsed_count = 0;
	uint64_t last_count;
	uint64_t current_count;

	last_count = get_current_count();

	do {
		current_count = get_current_count();

		/* Check if counter reset occurred */
		/* TODO: Identify how many ticks are triggered */
		if (last_count < current_count) {	/* Count-down */
			/* Timeline : [tick_0]|--MAX--(LAST--ZERO)--|--[tick_n]|--(MAX--CUR)--| */
			elapsed_count += last_count + (tick_interval - current_count);
		} else {
			/* Timeline : [single tick]|--(LAST--ticks--CUR)--| */
			elapsed_count += last_count - current_count;
		}

		/* Update 'last_count' */
		last_count = current_count;
	/* Check if time is delayed enough */
	} while (elapsed_count < target_count);
}
