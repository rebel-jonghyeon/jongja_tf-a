/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_OEC_REG_H
#define CMRT_OEC_REG_H

#include "hwc_reg.h"

#define CMRT_OEC_BASE       0x00304000u

#define R_OEC_ADDRESS       0x000u
#define OEC_ADDRESS_KEY_EFUSE     0x01u
#define OEC_ADDRESS_VERSION_EFUSE 0x02u
#define OEC_ADDRESS_AES_IV        0x04u

#define R_OEC_CONTROL       0x004u
#define OEC_CONTROL_READ   0x01u
#define OEC_CONTROL_WRITE  0x02u
#define OEC_CONTROL_COMMIT 0x04u
#define OEC_CONTROL_TRANSFER_KEY0 0x08u
#define OEC_CONTROL_TRANSFER_KEY1 0x10u

#define R_OEC_STATUS       0x008u
#define R_OEC_INPUT        0x010u
#define R_OEC_LAST_INPUT   0x02Cu
#define R_OEC_OUTPUT       0x040u
#define R_OEC_LAST_OUTPUT  0x05Cu
#define R_OEC_EFUSE_STATUS 0x070u
#define R_OEC_IV_OUTPUT    0x080u
#define R_OEC_MAX          0x10000u

#define OEC_MAX_DATA_BITS 256u
#define OEC_MAX_DATA_BYTES (OEC_MAX_DATA_BITS / 8u)
#define OEC_MAX_DATA_WORDS (OEC_MAX_DATA_BYTES / 4u)

#define OEC_MEMORY_FILE "oecmem.bin"

#endif
