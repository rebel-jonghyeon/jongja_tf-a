/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_PLIC_REG_H
#define CMRT_PLIC_REG_H

#include "hwc_reg.h"

#define CMRT_PLIC_BASE        0x00072000UL

#define R_PLIC_INTERRUPT      0x310UL
#define PLIC_DMAC_INTERRUPT   1UL
#define PLIC_PKE_INTERRUPT    2UL
#define PLIC_KDC_INTERRUPT    3UL
#define PLIC_SIC_INTERRUPT    4UL
#define PLIC_OMC_INTERRUPT    5UL
#define PLIC_TMC_INTERRUPT    6UL
#define PLIC_UFC_INTERRUPT    16UL
#define PLIC_INTERRUPT_MASK   (1UL << PLIC_DMAC_INTERRUPT | \
			       1UL << PLIC_PKE_INTERRUPT |  \
			       1UL << PLIC_KDC_INTERRUPT |  \
			       1UL << PLIC_SIC_INTERRUPT |  \
			       1UL << PLIC_OMC_INTERRUPT |  \
			       1UL << PLIC_UFC_INTERRUPT)
#define PLIC_INTERRUPT_LINES  32UL
#define R_PLIC_MACHINE_IE     0x314UL
#define R_PLIC_SUPERVISOR_IE  0x318UL
#define R_PLIC_MACHINE_SW_INT 0x31CUL
#define PLIC_M_SW_INT         (1UL << 0)
#define R_PLIC_TIMER_IE       0x320UL
#define PLIC_TIMER_MTIE       (1UL << 0)
#define PLIC_TIMER_STIE       (1UL << 1)
#endif
