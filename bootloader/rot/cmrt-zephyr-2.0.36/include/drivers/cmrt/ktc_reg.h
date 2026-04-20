/*
 * Copyright (c) 2019-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_KTC_REG_H
#define CMRT_KTC_REG_H

#include "hwc_reg.h"

#define CMRT_KTC_BASE             0x00052000UL

#define R_KTC_BLOCK_TOTAL_NUM     0x140UL
#define R_KTC_KEY_METADATA0       0x200UL
#define R_KTC_KEY_METADATA1       0x204UL
#define R_KTC_KEY_DESTINATION     0x208UL
#define R_KTC_BLOCK_ID            0x20CUL
#define R_KTC_KEY_DATA0           0x210UL
#define R_KTC_KEY_DATA1           0x214UL
#define R_KTC_KEY_DATA2           0x218UL
#define R_KTC_KEY_DATA3           0x21CUL
#define R_KTC_ALLOWED_DESTINATONS 0x220UL

/* KTC specific R_CORE_CONTROL values */
#define KTC_CONTROL_UPDATE        0x01UL
#define KTC_CONTROL_ABORT         0x02UL

/* KTC specific R_CORE_STATUS values */
#define KTC_STATUS_READY_FOR_NEXT 0x20UL
#define KTC_STATUS_WAIT_ACK       0x21UL

#define KTC_KEY_DATA_WORDS        4UL
#define KTC_KEY_METADATA_WORDS    2UL

#define KTC_MAX_KEY_SIZE          (16 * 255)

#define KEYBUS_FILE_NAME_FMT "keybus-dest-%d.txt"

#endif
