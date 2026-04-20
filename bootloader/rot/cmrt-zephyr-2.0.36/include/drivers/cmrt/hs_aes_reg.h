/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_HS_AES_REG_H
#define CMRT_HS_AES_REG_H

#include "cmrt_field.h"
#include "sac_reg.h"

#define CMRT_HSAES_BASE                 (EXT_MEMORY_CMRT + 0x20000)
#define CMRT_HSAES_NR_CHANNELS          64
#define CMRT_HSAES_NR_KEY_BANKS         2

/* Following are in bytes. */
#define CMRT_HSAES_DESC_BRAM_SIZE       4096
#define CMRT_HSAES_BLOCK_SIZE           16
#define CMRT_HSAES_IV_SIZE              12
#define CMRT_HSAES_TAG_SIZE             16
#define CMRT_HSAES_TAG_OFFSET           16
#define CMRT_HSAES_KEY_SIZE             32
#define CMRT_HSAES_HKEY_SIZE            16
#define CMRT_HSAES_LIN_DESC_MAX_SIZE    0x800000
#define CMRT_HSAES_SIC_SOC_IRQ          1

/* Registers */
#define R_HSAES_INTERRUPT               0x110
#define R_HSAES_INTERRUPT_MASK          0x114
#define R_HSAES_STATUS                  0x120
#define R_HSAES_CONTROL                 0x130
#define R_HSAES_SP                      0x200
#define R_HSAES_EP                      0x210
#define R_HSAES_MODE                    0x240
#define R_HSAES_DESC_BRAM               0x1000
#define R_HSAES_DESC_BRAM_LAST          (R_HSAES_DESC_BRAM + CMRT_HSAES_DESC_BRAM_SIZE - 1)
#define R_HSAES_MAX                     0x10000

/* Status values */
#define HSAES_STATUS_IDLE               0x0
#define HSAES_STATUS_BUSY               0x10
#define HSAES_STATUS_STOPPED            0x30
#define HSAES_STATUS_ERROR              0x80
#define HSAES_STATUS_MASK               0xFF

/* Error codes */
#define HSAES_STATUS_ERR_MODE_MISMATCH  0x01
#define HSAES_STATUS_ERR_CH_KB_MISMATCH 0x02
#define HSAES_STATUS_ERR_AUTH           0x04
#define HSAES_STATUS_ERR_AXI            0x08
#define HSAES_STATUS_ERR_EIP            0x10
#define HSAES_STATUS_ERR_DCM            0x20

/* QEMU specific error codes */
#define HSAES_STATUS_ERR_CTRL_ENCODING  0x80
#define HSAES_STATUS_ERR_SSL            0x81
#define HSAES_STATUS_ERR_DESC           0x82
#define HSAES_STATUS_ERR_EP             0x84

#define HSAES_STATUS_ERR_CODE_MASK      0xFF
#define HSAES_STATUS_ERR_CODE_SHIFT     8
#define HSAES_STATUS_ERR_CH_MASK        0xFF
#define HSAES_STATUS_ERR_CH_SHIFT       16

/* Control values */
#define HSAES_CONTROL_ABORT             0xAB
#define HSAES_CONTROL_FLUSH             0xFF
#define HSAES_CONTROL_MASK              0XFF

/* Mode values */
#define HSAES_MODE_CIRCULAR_DESC        0
#define HSAES_MODE_LINEAR_DESC          1
#define HSAES_MODE_MASK                 1

/* Interrupt values */
#define HSAES_INTERRUPT_DONE            1
#define HSAES_INTERRUPT_ERR             2
#define HSAES_INTERRUPT_MASK            3

/**
 * HSAES linear descriptor.
 *
 * A sequence of linear descriptor forms a "packet" (full AES-GCM operation).
 * Packet begins with descriptor that has flag @p sop and ends with one that has flag @p
 * eop. As such a single descriptor can have both flags, thus would compose an entire packet.
 */
typedef struct cmrt_hs_aes_linear_desc {
	uint64_t in_addr;       /**< Address of input data (in DDR). */
	uint64_t out_addr;      /**< Address of output data (in DDR). */

	/**
	 * Field F1 is concatenation of following fields (LS to MS)
	 *
	 * size:23      Size of data (bytes)
	 * key_bank:1
	 * channel:6
	 * decyrpt:1    Operation: 0:encryption 1:decryption
	 * linear:1     Mode: 0:bidirectional 1:linear, should be 1
	 */
	uint32_t F1;

	/**
	 * Field F2 is concatenation of following fields (LS to MS)
	 *
	 * ad_size:23   Size of Authentication Only Data (bytes)
	 * sop:1        Start of packet flag
	 * eop:1        End of packet flag
	 * swap:1       Swap bytes in a word
	 */
	uint32_t F2;

	uint64_t meta_addr;     /**< Address of meta data (iv .. tag) (in DDR). */
	uint64_t ad_addr;       /**< Address of Authentication Only data (in DDR). */
} __attribute__((packed)) cmrt_hs_aes_linear_desc_t;

typedef struct cmrt_hs_aes_desc_metadata {
	uint32_t iv[CMRT_HSAES_IV_SIZE / 4];
	uint32_t padding[(CMRT_HSAES_TAG_OFFSET - CMRT_HSAES_IV_SIZE) / 4];
	uint32_t tag[CMRT_HSAES_TAG_SIZE / 4];
} __attribute__((packed)) cmrt_hs_aes_desc_metadata_t;

typedef struct cmrt_hs_aes_circular_desc {
	uint64_t in_addr;       /**< Address of first input (DDR) buffer. */
	uint64_t out_addr;      /**< Address of first output (DRR) buffer. */

	/**
	 * Field F1 is concatenation of following fields (LS to MS)
	 *
	 * size:23      Number of entries in AT
	 * key_bank:1
	 * channel:6
	 * decrypt:1    Operation: 0:encryption 1:decryption
	 * linear:1     Mode: 0:bidirectional 1:linear, should be 0
	 */
	uint32_t F1;
} __attribute__((packed)) cmrt_hs_aes_circular_desc_t;

typedef struct cmrt_hs_aes_keybus_metadata0 {
	/**
	 * Field KB0 is concatenation of following fields (LS to MS)
	 *
	 * key_bank:1
	 * channel:6
	 * hkey:1
	 * key_256_bit:1
	 * padding:7
	 */
	uint32_t KB0;
} __attribute__((packed)) cmrt_hs_aes_keybus_metadata0_t;

#define HSAES_DESC_SIZE           F1, 23, 0
#define HSAES_DESC_KEY_BANK       F1, 1, 23
#define HSAES_DESC_CHANNEL        F1, 6, 24
#define HSAES_DESC_DECRYPT        F1, 1, 30
#define HSAES_DESC_LINEAR         F1, 1, 31

#define HSAES_DESC_AD_SIZE        F2, 23, 0
#define HSAES_DESC_SOP            F2, 1, 23
#define HSAES_DESC_EOP            F2, 1, 24
#define HSAES_DESC_SWAP           F2, 1, 25

/* Keybus metadata0 */
#define HSAES_KB0_KEY_BANK        KB0, 1, 0
#define HSAES_KB0_CHANNEL         KB0, 6, 1
#define HSAES_KB0_HKEY            KB0, 1, 7
#define HSAES_KB0_KEY_256_BIT     KB0, 1, 8

#define HSAES(op, field, ...) CMRT_FIELD(op, __VA_ARGS__, HSAES_DESC_ ## field)
#define HSAES_KB(op, field, ...) CMRT_FIELD(op, __VA_ARGS__, HSAES_KB0_ ## field)
#endif /* CMRT_HS_AES_REG_H */
