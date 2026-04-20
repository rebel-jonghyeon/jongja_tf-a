/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_AES_REG_H
#define CMRT_AES_REG_H

#include "hwc_reg.h"
#include "cipher_reg.h"

#define CMRT_AES_BASE          0x00010000UL

#define R_AES_ENTROPY          0x300UL

/* AES_STATUS register values */
#define AES_ERR_PRNG_NOT_SEEDED    0x0dUL


/* AES_CONTROL control register values */

#define AES_CMD_LOAD_J         0x07UL
#define AES_CMD_SEED_RNG       0x08UL

#define AES_ENCRYPT                CIPHER_OP_ENCRYPT
#define AES_DECRYPT                CIPHER_OP_DECRYPT
#define AES_OPERATION_SHIFT        CIPHER_OPERATION_SHIFT
#define AES_OPERATION_MASK         CIPHER_OPERATION_MASK
#define AES_OPERATION_ENCRYPT      CIPHER_OPERATION_ENCRYPT
#define AES_OPERATION_DECRYPT      CIPHER_OPERATION_DECRYPT

#define AES_KEY_SIZE_SHIFT         9UL
#define AES_KEY_SIZE_MASK          (0x3UL << AES_KEY_SIZE_SHIFT)
#define AES_KEY_SIZE_128           (0x0UL << AES_KEY_SIZE_SHIFT)
#define AES_KEY_SIZE_192           (0x1UL << AES_KEY_SIZE_SHIFT)
#define AES_KEY_SIZE_256           (0x2UL << AES_KEY_SIZE_SHIFT)

#define AES_ECB              (0x0UL)
#define AES_CBC              (0x1UL)
#define AES_CFB              (0x2UL)
#define AES_CTR              (0x3UL)
#define AES_GCM              (0x4UL)
#define AES_CCM              (0x5UL)
#define AES_XTS              (0x6UL)
#define AES_CMAC             (0x7UL)

#define AES_MODE_SHIFT            12UL
#define AES_MODE_MASK             (0xfUL << AES_MODE_SHIFT)
#define AES_MODE_ECB              (AES_ECB << AES_MODE_SHIFT)
#define AES_MODE_CBC              (AES_CBC << AES_MODE_SHIFT)
#define AES_MODE_CFB              (AES_CFB << AES_MODE_SHIFT)
#define AES_MODE_CTR              (AES_CTR << AES_MODE_SHIFT)
#define AES_MODE_GCM              (AES_GCM << AES_MODE_SHIFT)
#define AES_MODE_CCM              (AES_CCM << AES_MODE_SHIFT)
#define AES_MODE_XTS              (AES_XTS << AES_MODE_SHIFT)
#define AES_MODE_CMAC             (AES_CMAC << AES_MODE_SHIFT)

#define AES_TAG_LENGTH_SHIFT         16UL
#define AES_TAG_LENGTH_MASK          (0x7UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_128           (0x0UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_120           (0x1UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_112           (0x2UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_104           (0x3UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_96            (0x4UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_64            (0x5UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_48            (0x6UL << AES_TAG_LENGTH_SHIFT)
#define AES_TAG_LENGTH_32            (0x7UL << AES_TAG_LENGTH_SHIFT)

#define AES_CONTROL_MASK         (AES_OPERATION_MASK | \
				  AES_KEY_SIZE_MASK  | \
				  AES_MODE_MASK      | \
				  AES_TAG_LENGTH_MASK)

#define AES_BLOCK_WORDS 4UL
#define AES_BLOCK_BYTES (AES_BLOCK_WORDS << 2)

#define AES_LAST_BLOCK_BYTE_SELECT_MASK   0x0000ffffUL

#define AES_XTS_MAX_J ((1UL << 20) - 1UL)

#endif
