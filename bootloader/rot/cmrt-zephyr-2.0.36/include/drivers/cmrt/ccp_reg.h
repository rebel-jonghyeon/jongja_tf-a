/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_CCP_REG_H
#define CMRT_CCP_REG_H

#include "hwc_reg.h"
#include "cipher_reg.h"

#define CMRT_CCP_BASE          0x00090000

enum ccp_key_size {
	CCP_KEY_SIZE_128 = 0,
	CCP_KEY_SIZE_256 = 2,
};

/* tag length in bits */
enum ccp_tag_len {
	CCP_TAG_LEN_128 = 0,
};

enum ccp_cnt_nonce {
	/* Counter length is 64bits, nonce length is 64bits */
	CCP_COUNTER_LEN_64 = 0,
	/* Counter length is 32bits, nonce length is 96bits */
	CCP_COUNTER_LEN_32,
};

enum ccp_mode_op {
	CCP_MODE_RESERVED = 0,
	CCP_MODE_CHACHA,
	CCP_MODE_POLY,
	CCP_MODE_CHACHA_POLY_AEAD,
};

#define CHACHA_BLOCK_BYTES           64
#define CHACHA_BLOCK_WORDS           (CHACHA_BLOCK_BYTES / 4)
#define POLY_BLOCK_BYTES             16
#define POLY_BLOCK_WORDS             (POLY_BLOCK_BYTES / 4)
#define POLY_TAG_LENGTH_BYTES        16

#define CCP_LAST_BLOCK_BYTES_MASK    0x7f

#define CCP_IV_LEN                   16

/* CCP_DATA_RATE register is currently a part of the wrapper. */
#define R_CCP_DATA_RATE_0            0x104
#define R_CCP_DATA_RATE_1            0x108

/* CCP_CONTROL register values */
#define CCP_CMD_GENERATE_POLY_KEY    0x07

struct ccp_ctrl {
	/* CIPHER_CMD_XXX */
	unsigned int cmd : 8;
	/* CIPHER_OP_XXX */
	unsigned int cipher_op : 1;
	enum ccp_key_size key_size : 3;
	/* fixed value CCP_MODE_1 */
#define CCP_MODE_1 0x0f
	unsigned int mode_1 : 4;
	enum ccp_tag_len tag_len : 3;
	enum ccp_cnt_nonce cnt_len : 1;
	enum ccp_mode_op mode_2 : 7;
	unsigned int reserved : 5;
};

typedef union {
	struct ccp_ctrl ctl;
	uint32_t val;
} ccp_ctrl_t;

#endif
