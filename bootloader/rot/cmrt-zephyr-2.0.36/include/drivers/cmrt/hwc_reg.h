/*
 * Abstraction of register declarations and operations in cmrt devices.
 *
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_HW_COMMON_REG_H
#define CMRT_HW_COMMON_REG_H

/* Core ids */
#define CORE_ID_MIN   0x01UL
#define CORE_ID_SIC   0x01UL
#define CORE_ID_FMC   0x02UL
#define CORE_ID_TMC   0x04UL
#define CORE_ID_EMC   0x05UL
#define CORE_ID_CC    0x08UL
#define CORE_ID_EAC   0x0BUL
#define CORE_ID_AES   0x10UL
#define CORE_ID_HC    0x20UL
#define CORE_ID_WHC   0x22UL
#define CORE_ID_CSHC  0x24UL
#define CORE_ID_HC2   0x26UL
#define CORE_ID_PKE   0x30UL
#define CORE_ID_OMC   0x40UL
#define CORE_ID_KDC   0x50UL
#define CORE_ID_KTC   0x52UL
#define CORE_ID_CPU   0x5AUL
#define CORE_ID_SAC   0x60UL
#define CORE_ID_DMAC  0x62UL
#define CORE_ID_MPU   0x70UL
#define CORE_ID_PLIC  0x72UL
#define CORE_ID_TIMER 0x74UL
#define CORE_ID_UART  0x75UL
#define CORE_ID_UFC   0x80UL
#define CORE_ID_CCP   0x90UL
#define CORE_ID_SM3   0xA0UL
#define CORE_ID_SM4   0xA2UL
#define CORE_ID_QSE   0xB0UL
#define CORE_ID_MAX   0xFFUL

/* Common register offsets */
#define R_HWC_ID               0x0000UL
#define R_HWC_INFO0            0x0004UL
#define R_HWC_INFO1            0x0008UL
#define R_HWC_KEY_CONTRIB      0x0010UL
#define R_HWC_CORE_ACCESS_CTRL 0x0020UL
#define R_HWC_CORE_PERM        0x0030UL
#define HWC_CORE_PERM_DISABLE  0x0UL
#define HWC_CORE_PERM_ENABLE   0x3UL
#define HWC_CORE_PERM_MASK     0x3UL
#define R_HWC_LOCK_MASTER      0x0100UL
#define R_CORE_INTERRUPT       0x0110UL
#define R_CORE_INTERRUPT_MASK  0x0114UL
#define R_CORE_STATUS          0x0120UL
#define R_CORE_CONTROL         0x0130UL
#define R_CORE_LAST_BLOCK      0x0140UL
#define R_CORE_KEY_CONTROL     0x0200UL
#define R_CORE_KEY             0x0210UL
#define R_CORE_INPUT           0x0250UL
#define R_CORE_LAST_INPUT      0x028CUL
#define R_CORE_OUTPUT          0x0290UL
#define R_CORE_LAST_OUTPUT     0x02CCUL
#define R_MAX                  0x1000UL

/* Viable privileges in lock master */
#define HWC_LOCK_MAST_PRV_S    (1UL << 1)
#define HWC_LOCK_MAST_PRV_M    (1UL << 2)

/* R_CORE_STATUS values */
#define HWC_STATUS_AVAILABLE       0x00UL
#define HWC_STATUS_IDLE_LOCKED     0x01UL
#define HWC_STATUS_BUSY            0x10UL
#define HWC_STATUS_UNAVAILABLE     0x11UL
#define HWC_STATUS_ERROR           0x80UL
#define HWC_STATUS_SUCCESS         0xF0UL

/* Filter out core specific error. 0x81, 0x82, etc. would return true. */
#define IS_HWC_ERROR(s) (((s) & 0xF0UL) == HWC_STATUS_ERROR)

#define HWC_STATUS_ERROR_SHIFT     8UL
#define HWC_STATUS_INWORDS_SHIFT   18UL
#define HWC_STATUS_OUTWORDS_SHIFT  26UL
#define HWC_STATUS_STATUS_MASK     0x000000FFUL
#define HWC_STATUS_ERROR_MASK      0x0000FF00UL
#define HWC_STATUS_INWORDS_ERROR   0x00030000UL
#define HWC_STATUS_INWORDS_MASK    0x00FC0000UL
#define HWC_STATUS_OUTWORDS_ERROR  0x03000000UL
#define HWC_STATUS_OUTWORDS_MASK   0xFC000000UL

/* R_CORE_CONTROL values */
#define HWC_CONTROL_NONE          0x00UL
#define HWC_CONTROL_FLUSH         0xFFUL
#define HWC_CONTROL_CMD_MASK      0x000000ffUL

#endif
