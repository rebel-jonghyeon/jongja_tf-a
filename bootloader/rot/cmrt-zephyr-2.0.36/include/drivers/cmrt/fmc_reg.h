/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_FMC_REG_H
#define CMRT_FMC_REG_H

#include "hwc_reg.h"

#define CMRT_FMC_BASE                0x00002000UL

/*
 * Limits of internal feature space. Copied from Cmrt HW repository.
 * TDV is mapped here, but not functional in QEMU.
 */
#define FMC_FEATURE_INT_MIN          0
#define FMC_FEATURE_INT_MAX          0

#define FMC_FEATURE_REGION_BITS      11
#define FMC_FEATURE_REGION_SIZE      (1UL << FMC_FEATURE_REGION_BITS)

/*
 * Limits of external feature space. An example for QEMU. This area has no
 * functionality.
 */
#define FMC_FEATURE_EXT_MIN          3
#define FMC_FEATURE_EXT_MAX          4

/*
 * Limits of GPIO space. An example for QEMU. This area has no functionality.
 */
#define FMC_GPIO_MIN                 6UL
#define FMC_GPIO_MAX                 6UL

#define R_FEATURE_ADDRESS            0x300UL
#define R_FEATURE_DATA               0x304UL
#define R_FEATURE_DATA_MASK          0x308UL
#define R_OTP_FEATURE_W              0x400UL

#define FMC_CONTROL_CMD_MASK         0x000000ffUL
#define FMC_CONTROL_FEATURE_WRITE    0x05UL
#define FMC_CONTROL_FEATURE_READ     0x04UL
#define FMC_CONTROL_GPIO_WRITE       0x07UL
#define FMC_CONTROL_GPIO_READ        0x06UL
#define FMC_CONTROL_FLUSH            0xffUL

#define FMC_FEATURE_ADDRESS_RW_MASK  0x0000fffcUL

#define FMC_STATUS_ERROR_DATA        0x81UL
#define FMC_STATUS_MASK              0xffUL
#define FMC_STATUS_ERROR_SHIFT       8UL

#define FMC_TDV_OFFSET               0UL
#define FMC_TEST_MODE_BIT            (1UL << 0)

#endif
