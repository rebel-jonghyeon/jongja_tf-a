/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_CC_REG_H
#define CMRT_CC_REG_H

#include "hwc_reg.h"

#define CMRT_CC_BASE          0x00008000UL

#define R_DATA_MIX            0x300UL
#define R_CANARY_VALUE0       0x304UL
#define R_CANARY_VALUE1       0x308UL
#define R_ASSERT_VALUE0       0x30CUL
#define R_ASSERT_VALUE1       0x310UL

#define CC_CONTROL_MIX        0x01UL
#define CC_CONTROL_ASSERT     0x02UL

#endif
