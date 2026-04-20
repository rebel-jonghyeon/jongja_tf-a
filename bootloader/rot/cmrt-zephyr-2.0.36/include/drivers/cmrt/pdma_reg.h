/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_PDMA_REG_H
#define CMRT_PDMA_REG_H

#define CMRT_PDMA_NR_AT                2
/* Following are in bytes. */
#define CMRT_PDMA_DESC_BRAM_SIZE       4096
#define CMRT_PDMA_AT_SIZE              4096
#define CMRT_PDMA_AT_BRAM_SIZE         (CMRT_PDMA_NR_AT * CMRT_PDMA_AT_SIZE)
#define CMRT_PDMA_DATA_WIDTH           32
#define CMRT_PDMA_SIC_SOC_IRQ          0

/* Registers */
#define CMRT_PDMA_BASE                 (EXT_MEMORY_CMRT + 0x40000)
#define R_PDMA_INTERRUPT               0x110
#define R_PDMA_INTERRUPT_MASK          0x114
#define R_PDMA_STATUS                  0x120
#define R_PDMA_CONTROL                 0x130
#define R_PDMA_SP                      0x200
#define R_PDMA_EP                      0x210
#define R_PDMA_DESC_BRAM               0x1000
#define R_PDMA_DESC_BRAM_LAST          (R_PDMA_DESC_BRAM + CMRT_PDMA_DESC_BRAM_SIZE - 1)
/* AT BRAM is not accessible to SW. */
#define R_PDMA_AT_BRAM                 0x2000
#define R_PDMA_AT_BRAM_LAST            (R_PDMA_AT_BRAM + CMRT_PDMA_AT_BRAM_SIZE - 1)
#define R_PDMA_MAX                     0x10000

/* Status values */
#define PDMA_STATUS_IDLE               0x0
#define PDMA_STATUS_BUSY               0x10
#define PDMA_STATUS_STOPPED            0x30
#define PDMA_STATUS_ERROR              0x80
#define PDMA_STATUS_MASK               0xFF

/* Error codes */
#define PDMA_STATUS_ERR_CTRL           0x01
#define PDMA_STATUS_ERR_CTRL_ENCODING  0x02
#define PDMA_STATUS_ERR_DESC           0x03
#define PDMA_STATUS_ERR_AT             0x04
#define PDMA_STATUS_ERR_AXI            0x06
#define PDMA_STATUS_ERR_DCM            0x07
#define PDMA_STATUS_ERR_CBLOCK         0x08
#define PDMA_STATUS_ERR_DMA_TIMEOUT    0x09
#define PDMA_STATUS_ERR_GLITCH         0x0A

/* QEMU specific error codes */
#define PDMA_STATUS_ERR_EP             0x80

#define PDMA_STATUS_ERR_CODE_MASK      0xFF
#define PDMA_STATUS_ERR_CODE_SHIFT     8
#define PDMA_STATUS_ERR_CH_MASK        0xFF
#define PDMA_STATUS_ERR_CH_SHIFT       16

/* Control values */
#define PDMA_CONTROL_ABORT             0xAB
#define PDMA_CONTROL_FLUSH             0xFF
#define PDMA_CONTROL_MASK              0XFF

/* Interrupt values */
#define PDMA_INTERRUPT_DONE            1
#define PDMA_INTERRUPT_ERR             2
#define PDMA_INTERRUPT_MASK            3

/**
 * PDMA Address Table (AT) entry.
 *
 * Address Table is an array of AT entries. An AT entry specify source
 * and destination address for PDMA copy operation and meta data for AES-GCM
 * operation (for use by HSAES, see @ref cmrt_hs_aes_circular_desc_t).
 */
typedef struct cmrt_pdma_at {
	uint64_t in_src_addr;   /**< Source HLOS address. */
	uint64_t out_dst_addr;  /**< Destination HLOS address. */

	/**
	 * Field F1 is concatenation of following fields (LS to MS)
	 *
	 * size:17     Size of data in bytes.
	 * rsrvd:14
	 * ad_valid:1  True if Authentication only data is valid.
	 */
	uint32_t F1;

	uint32_t iv[CMRT_HSAES_IV_SIZE / 4];    /**< Initialization vector data. */
	uint32_t tag[CMRT_HSAES_TAG_SIZE / 4];  /**< Tag for AES-GCM operation. */
	uint32_t ad;                            /**< Authentic Only Data. */
} __attribute__((packed)) cmrt_pdma_at_t;

#define CMRT_PDMA_MAX_AT_ROWS (CMRT_PDMA_AT_SIZE / sizeof(cmrt_pdma_at_t))

/** PDMA descriptor. */
typedef struct cmrt_pdma_desc {
	uint64_t at_addr;       /**< Address of AT (in HLOS address space). */
	uint64_t in_dst_addr;   /**< Destination DDR buffer address to copy data (to) from HLOS. */
	uint64_t out_src_addr;  /**< Source DDR buffer address to copy data (from) to HLOS. */

	/**
	 * Field F2 is concatenation of following fields (LS to MS)
	 *
	 * at_rows:23    Number of AT entries.
	 * key_bank:1    For bidirectional HSAES mode, Key bank used for this AT.
	 * channel:6     AT channel.
	 * type:2        Descriptor type, see @ref PDMA_DESC_TYPE.
	 */
	uint32_t F2;
} __attribute__((packed)) cmrt_pdma_desc_t;

#define PDMA_AT_SIZE            F1, 17, 0
#define PDMA_AT_AD_VALID        F1, 1, 31

#define PDMA_DESC_AT_ROWS       F2, 23, 0
#define PDMA_DESC_KEY_BANK      F2, 1, 23
#define PDMA_DESC_CHANNEL       F2, 6, 24
#define PDMA_DESC_TYPE          F2, 2, 30

#define AT(op, field, ...) CMRT_FIELD(op, __VA_ARGS__, PDMA_AT_ ## field)
#define PDMA(op, field, ...) CMRT_FIELD(op, __VA_ARGS__, PDMA_DESC_ ## field)

/**
 * @anchor PDMA_DESC_TYPE
 * @name PDMA descriptor types.
 * @{
 */
#define PDMA_DESC_BIDI_AT 0
#define PDMA_DESC_BIDI    1
#define PDMA_DESC_IN      2
#define PDMA_DESC_OUT     3
/** @} */

#endif /* CMRT_PDMA_REG_H */
