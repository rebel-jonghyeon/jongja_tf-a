/*
 * Copyright (c) 2018-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_SAC_REG_H
#define CMRT_SAC_REG_H

#include "hwc_reg.h"

#define CMRT_SAC_BASE 0x00060000UL

/* 32bit SAC registers */
#define R_SEGMENT_ACCESS_CONFIG_0		(0x300UL)
#define R_SEGMENT_CONFIG_0				(0x304UL)
#define R_SEGMENT_ACCESS_CONFIG_1		(0x308UL)
#define R_SEGMENT_CONFIG_1				(0x30CUL)
#define R_SEGMENT_ACCESS_CONFIG_2		(0x310UL)
#define R_SEGMENT_CONFIG_2				(0x314UL)
#define R_SEGMENT_ACCESS_CONFIG_3		(0x318UL)
#define R_SEGMENT_CONFIG_3				(0x31CUL)

/* 64bit SAC registers */
#define R_CPU_ACCESS_CONFIG				(0x300UL)
#define R_CPU_ADDR_LO					(0x304UL)
#define CPU_ADDR_LO_MASK				(0xFFFFF800)
#define CPU_ADDR_MASK					((0x7fULL << 32) | CPU_ADDR_LO_MASK)
#define R_CPU_ADDR_HI					(0x308UL)
#define R_DMA_ACCESS_CONFIG				(0x30CUL)
#define R_DMA_ADDR_IN_HI				(0x310UL)
#define R_DMA_ADDR_OUT_HI				(0x314UL)
#define R_SAC_EXT_ADDR_WIDTH_HI			(0x318UL)
#define R_CPU_DATA						(0x800UL)
#define R_CPU_DATA_LAST					(0xFFCUL)

#define EXT_MEMORY_CMRT					(0x40000000U)
#define EXT_MEMORY_HLOS					(0x80000000U)
#define EXT_MEMORY_MASK					(0x80000000U)

#define FOUR_BYTE_ALIGN_MASK			(0x3)
#define BYTE_MASK						(0xFF)
#endif
