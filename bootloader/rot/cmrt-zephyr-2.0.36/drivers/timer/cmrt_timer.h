/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_TIMER_H
#define CMRT_TIMER_H

#include <drivers/cmrt/timer_reg.h>

#define R_BASE DT_REG_ADDR(DT_NODELABEL(clint))

typedef struct {
	uint32_t core_interrupt;
	uint32_t core_interrupt_mask;
	uint32_t unused[6];
	uint32_t watchdog_control;
	uint32_t watchdog_count;
	uint32_t watchdog_compare;
	uint32_t watchdog_compare_add;
	uint32_t watchdog_key;
	uint32_t watchdog_feed;
} wdt_cmrt_t;

#define WDT (volatile wdt_cmrt_t *)(R_BASE + R_CORE_INTERRUPT)

typedef struct {
	wdt_cmrt_t wdt;
	uint32_t unused;
	uint32_t gtime_count_low;
	uint32_t gtime_count_high;
	uint32_t gtime_compare_low;
	uint32_t gtime_compare_high;
} tmr_cmrt_t;

#define TMR (volatile tmr_cmrt_t *)(R_BASE + R_CORE_INTERRUPT)

typedef struct {
	tmr_cmrt_t tmr;
	uint32_t safety_wd_control;
	uint32_t safety_wd_count;
	uint32_t safety_wd_compare;
	uint32_t safety_wd_feed;
} wdt_safety_cmrt_t;

#define SAFETY_WDT (volatile wdt_safety_cmrt_t *)(R_BASE + R_CORE_INTERRUPT)

#endif
