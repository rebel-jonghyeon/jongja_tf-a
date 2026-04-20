/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_EMC_REG_H
#define CMRT_EMC_REG_H

#include "hwc_reg.h"

#define CMRT_EMC_BASE             0x00005000UL

#define EMC_STATUS_AVAILABLE       0x00UL
#define EMC_STATUS_DATA_AVAILABLE  0x01UL

#define R_EMC_TRNG_DATA           0x290UL

#define EMC_OUTPUT_REGS        16UL
#define EMC_OUTPUT_SIZE        (EMC_OUTPUT_REGS * sizeof(uint32_t))

#endif
