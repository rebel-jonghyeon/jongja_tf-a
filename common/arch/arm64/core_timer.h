#pragma once

#include <stdint.h>

static inline uint64_t get_current_count(void)
{
	uint64_t current_count;

	__asm__ volatile ("mrs %[r], cntpct_el0" : [r] "=r" (current_count));

	return current_count;
}

/* Generic Timer */
/* CA73 = Count-Up + Accumulated */
/* TODO: Find a way to test counter reset case */
#define MAX_COUNT	(0xFFFFFFFFFFFFFFFFULL)
static inline void delay_count(uint64_t target_count)
{
	/* CA73 doesn't have to consider ticks between 'last_count' & 'current_count' */
	uint64_t elapsed_count = 0;
	uint64_t last_count;
	uint64_t current_count;

	last_count = get_current_count();

	do {
		current_count = get_current_count();

		/* Check if counter reset occurred */
		if (current_count < last_count) {	/* Count-up */
			/* Timeline : |--(ZERO--CUR)--[ticks]--(LAST--MAX)--| */
			elapsed_count += current_count + (MAX_COUNT - last_count);
		} else {
			/* Timeline : |---ZERO--(LAST--[ticks]--CUR)--MAX---| */
			elapsed_count += (current_count - last_count);
		}

		/* Update 'last_count' */
		last_count = current_count;
	/* Check if time is delayed enough */
	} while (elapsed_count < target_count);
}
