/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_MPU_REG_H
#define CMRT_MPU_REG_H

#include "hwc_reg.h"

#define CMRT_MPU_BASE       0x00070000UL

#define R_MPRR0             0x300UL

#define NR_OF_MPRRS 32UL
#define R_MPRRN (R_MPRR0 + (NR_OF_MPRRS << 2))

#define MPU_ADDRESS_MASK    0x00FFFFFFUL
#define MPU_PRIVILEGE_MASK  0x03000000UL
#define MPU_PRIVILEGE_SHIFT 24
#define MPU_PRIVILEGE_U     (0x0UL << MPU_PRIVILEGE_SHIFT)
#define MPU_PRIVILEGE_S     (0x1UL << MPU_PRIVILEGE_SHIFT)
#define MPU_PRIVILEGE_M     (0x3UL << MPU_PRIVILEGE_SHIFT)
#define MPU_BITS_MASK       0xFC000000UL
#define MPU_MODE_WRITABLE   (1UL << 26)
#define MPU_MODE_READABLE   (1UL << 27)
#define MPU_MODE_EXECUTABLE (1UL << 28)
#define MPU_MODE_MASK       (MPU_MODE_WRITABLE | MPU_MODE_READABLE | \
			     MPU_MODE_EXECUTABLE)
#define MPU_START_OF_RANGE  (1UL << 29)
#define MPU_RESERVED        (1UL << 30)
#define MPU_LOCKED          (1UL << 31)

#endif
