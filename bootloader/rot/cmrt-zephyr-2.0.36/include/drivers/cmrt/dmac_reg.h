/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_DMAC_REG_H
#define CMRT_DMAC_REG_H

#include "hwc_reg.h"

#define CMRT_DMAC_BASE        0x00062000UL

#define R_VCQ_BAR0            0x300UL
#define R_VCQ_HEAD0           0x304UL
#define R_VCQ_TAIL0           0x308UL
#define R_VCQ_LENGTH0         0x30CUL

#define SUCCESS_INTERRUPT0 (1UL << 0)
#define ERROR_INTERRUPT0   (1UL << 1)
#define DMAC_INTERRUPT_MASK (SUCCESS_INTERRUPT0 | ERROR_INTERRUPT0)

#define VCQ_ERROR          0x0100UL
#define COMMAND_READ_ERROR 0x0200UL
#define COMMAND_ERROR      0x0400UL
#define PRIVILEGE_ERROR    0x0800UL
#define EXT_MEM_ERROR      0x1000UL
#define INT_MEM_ERROR      0x2000UL
#define DEVICE_ERROR       0x4000UL
#define ERROR_MASK         0xFF00UL

#define DMAC_CONTROL_START 0x55UL
#define DMAC_CONTROL_ABORT 0xABUL

#define DESC_MODE_CSR        0x01UL
#define DESC_MODE_DATA       0x02UL
#define DESC_MODE_CRYPTO     0x04UL
#define DESC_MODE_FILL       0x08UL
#define DESC_MODE_LOCK       0x10UL
#define DESC_MODE_MASK       0xFFUL

#define DESC_PRIV_USER       0x000UL
#define DESC_PRIV_SUPERVISOR 0x100UL
#define DESC_PRIV_MACHINE    0x300UL
#define DESC_PRIV_MASK       0x300UL
#define DESC_PRIV_SHIFT      8UL

#define DESC_DECSRCADDR_BIT   (1UL << 10)
#define DESC_DECDSTADDR_BIT   (1UL << 11)
#define DESC_SWPSRCBYTES_BIT  (1UL << 12)
#define DESC_SWPDSTBYTES_BIT  (1UL << 13)
#define DESC_VALIDCSR1_BIT    (1UL << 14)
#define DESC_CFI_BIT          (1UL << 15)
#define DESC_STOP_BIT         (1UL << 16)
#define DESC_INTERRUPT_BIT    (1UL << 17)
#define DESC_EXTSRC_BIT       (1UL << 18)
#define DESC_EXTDST_BIT       (1UL << 19)

/*
 * DMAC descriptor structures.
 */
typedef struct cmrt_dmac_data_desc {
	uint32_t rsrvd1;
	uint32_t dst_size;
	uint32_t dst_addr;
	uint32_t src_addr;
} cmrt_dmac_data_desc_t;

#define DMAC_DATA_DST_SIZE_MASK 0x0000FFFFUL

typedef struct cmrt_dmac_crypto_desc {
	uint32_t device_addr;
	uint32_t srcdst_size;
	uint32_t dst_addr;
	uint32_t src_addr;
} cmrt_dmac_crypto_desc_t;

#define DMAC_CRYPTO_SRC_SIZE_MASK 0xFFFF0000UL
#define DMAC_CRYPTO_DST_SIZE_MASK 0x0000FFFFUL

typedef struct cmrt_dmac_csr_desc {
	uint32_t csr_addr0;
	uint32_t csr_data0;
	uint32_t csr_addr1;
	uint32_t csr_data1;
} cmrt_dmac_csr_desc_t;

typedef struct cmrt_dmac_fill_desc {
	uint32_t rsrvd1;
	uint32_t dst_size;
	uint32_t dst_addr;
	uint32_t fill_data;
} cmrt_dmac_fill_desc_t;

#define DMAC_FILL_DST_SIZE_MASK 0x0000FFFFUL

typedef struct cmrt_dmac_lock_desc {
	uint32_t device_addr;
	uint32_t retry_interval;
	uint32_t rsrvd2;
	uint32_t rsrvd3;
} cmrt_dmac_lock_desc_t;

#define DMAC_LOCK_RETRY_INTERVAL_MASK 0x0000FFFFUL

typedef struct cmrt_dmac_desc_t {
	uint32_t header;
	union {
		cmrt_dmac_data_desc_t data;
		cmrt_dmac_crypto_desc_t crypto;
		cmrt_dmac_csr_desc_t csr;
		cmrt_dmac_fill_desc_t fill;
		cmrt_dmac_lock_desc_t lock;
	} u;
} cmrt_dmac_desc_t;

#endif
