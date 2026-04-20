/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_EAC_REG_H
#define CMRT_EAC_REG_H

#include "hwc_reg.h"

#define CMRT_EAC_BASE      0x0000B000UL

#define R_HW_ERROR_INFO0   0x120UL
#define R_HW_ERROR_INFO1   0x124UL
#define R_SW_ERROR_INFO0   0x128UL
#define R_SW_ERROR_INFO1   0x12CUL
#define R_SW_HALT          0x130UL
#define SW_HALT_DO          (1UL << 0)
#define R_SW_SAFETY_ERROR  0x148UL
#define SW_SAFETY_NO_ALARM  (1UL << 0)
#define SW_SAFETY_ALARM     (1UL << 1)
#define SW_SAFETY_ALARM_MASK (SW_SAFETY_ALARM | SW_SAFETY_NO_ALARM)

/* NMI errors map to interrupt lines in EAC.*/
#define EAC_NMI_MPU_UPDATE        0UL
#define EAC_NMI_OMC_ESW_PERM      1UL
#define EAC_NMI_OMC_SLOT_PERM     2UL
#define EAC_NMI_KTC_PERM          3UL
#define EAC_NMI_FMC_PERM          4UL
#define EAC_NMI_WD_TIMER          5UL
#define EAC_NMI_KDC_PERM          6UL
#define EAC_NMI_CC_S_ASSERT       7UL
#define EAC_NMI_ERRORS (EAC_NMI_CC_S_ASSERT + 1)

/* Fatal errors map to interrupt lines in EAC. */
#define EAC_FATAL_SRAM_ERROR      0UL
#define EAC_FATAL_MPU_PRIVILEGE   1UL
#define EAC_FATAL_OMC_LC_SHADOW   2UL
#define EAC_FATAL_OMC_LC_UPDATE   3UL
#define EAC_FATAL_OMC_SLOT_PERM   4UL
#define EAC_FATAL_OMC_ESW_PERM    5UL
#define EAC_FATAL_ROM_BOOT_CHECK  6UL
#define EAC_FATAL_SRAM_BOOT_CHECK 7UL
#define EAC_FATAL_OMC_FMC_PERM    8UL
#define EAC_FATAL_CC_HW_PANIC     9UL
#define EAC_FATAL_CC_M_ASSERT     10UL
#define EAC_FATAL_RESERVED        11UL
#define EAC_FATAL_WD_TIMER        12UL
#define EAC_FATAL_KDC_PERM        13UL
#define EAC_FATAL_PRIVILEGE       14UL
#define EAC_FATAL_KTC_PERM        15UL
#define EAC_FATAL_DRBG_ERROR      16UL
#define EAC_FATAL_KDC_DISABLED    17UL
#define EAC_FATAL_EMC_ERROR       18UL
#define EAC_FATAL_PKE_HW_PANIC    19UL
#define EAC_FATAL_ERRORS (EAC_FATAL_PKE_HW_PANIC + 1)

#endif
