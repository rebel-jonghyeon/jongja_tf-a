#pragma once

#include <sys_io.h>
#include <stdio.h>
#include "printf.h"

#if defined(__TARGET_PCIE)
#include <ARMCM7_SP.h>
#endif

#if defined(__TARGET_CP)
//TODO: Add headers for CP
#endif

#if defined(__RUN_RTOS)
#include <projdefs.h>
#endif

/////////////////////////////////////////////////////////////////////
//                   Utilities for driver                          //
/////////////////////////////////////////////////////////////////////
#ifndef BIT
/** @brief Unsigned integer with bit position @p n set */
#define BIT(n)  (1UL << (n))
#endif

#ifndef BIT64
/** @brief 64-bit unsigned integer with bit position @p _n set. */
#define BIT64(_n) (1ULL << (_n))
#endif

#define BIT_MASK(n) (BIT(n) - 1UL)

#ifndef KHZ
#define KHZ	(1000)
#endif

#ifndef MHZ
#define MHZ	(1000000)
#endif

#ifndef GHZ
#define GHZ	(1000000000)
#endif

struct init_entry {
	/** Initialization function for the init entry */
	int (*init)(void);
};

#define DRIVER_INIT_ENTRY_DEFINE(_priority, _init_fn)                                   \
	static const struct init_entry _init_##_priority                                    \
	__attribute__((used)) __attribute__((__section__(".init_func_" #_priority))) = {	\
		.init = (_init_fn),										                        \
	}

void init_drivers_by_calling_init_entry(void);
