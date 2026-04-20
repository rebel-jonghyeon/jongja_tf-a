#pragma once
#include <drivers/dma.h>
#include <sysreg_sysremap.h>

/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

/*
 * Max burst length and max burst size for 32bit system with
 * 128bit bus width for memory to memory data transfer
 *
 * Burst length is encoded in following format for pl330
 * b0000 = 1 data transfer
 * b0001 = 2 data transfers
 * b0010 = 3 data transfers
 * .
 * .
 * b1111 = 16 data transfers
 *
 * Burst size is encoded in following format for pl330
 * b000 = 1 byte
 * b001 = 2 bytes
 * b010 = 4 bytes
 * b011 = 8 bytes
 * b100 = 16 bytes
 * b101 = 32 bytes
 * b110 = 64 bytes
 * b111 = 128 bytes.
 */

#include "errno.h"

#define MAX_BURST_LEN		(0xf) /* 16byte data */
#define MAX_BURST_SIZE_LOG2	(4)

#define DMA_INTID_START     (40)
#define DMA_INTID_END       (71)
#define DMA_ABORT_INTID     (72)

struct pl330 {
	struct {
		volatile uint32_t dsr;
		volatile uint32_t dpc;
		volatile uint32_t rsvd0[6];
		volatile uint32_t inten;
		volatile uint32_t int_event_ris;
		volatile uint32_t intmis;
		volatile uint32_t intclr;
		volatile uint32_t fsrd;
		volatile uint32_t fsrc;
		volatile uint32_t ftrd;
		volatile uint32_t rsvd1;
		volatile uint32_t ftr[8];
	} ctrl;
	volatile uint32_t rsvd0[40];
	struct {
		volatile uint32_t csr;
		volatile uint32_t cpc;
	} ch_stat[8];
	volatile uint32_t rsvd1[176];
	struct {
		volatile uint32_t sar;
		volatile uint32_t dar;
		volatile uint32_t ccr;
		volatile uint32_t lc0;
		volatile uint32_t lc1;
		volatile uint32_t rsvd[3];
	} lp_cnt_stat[8];
	volatile uint32_t rsvd2[512];
	struct {
		volatile uint32_t dbgstatus;
		volatile uint32_t dbgcmd;
		volatile uint32_t dbginst0;
		volatile uint32_t dbginst1;
	} dbg;
	volatile uint32_t rsvd3[60];
	struct {
		volatile uint32_t cr[5];
		volatile uint32_t crd;
		volatile uint32_t rsvd[26];
		volatile uint32_t wd;
	} config;
	volatile uint32_t rsvd4[87];
	struct {
		volatile uint32_t periph[4];
		volatile uint32_t pcell[4];
	} component_id;
};

struct sac_pl330_dbg {
	volatile uint32_t rsvd[320];
	volatile uint32_t dbgstatus;
	volatile uint32_t dbgcmd;
	volatile uint32_t dbginst0;
	volatile uint32_t dbginst1;
};

/*
 * PL330 works only on 4GB boundary.
 * PL330 has 32bit registers for source and destination addresses
 */
#define PL330_MAX_OFFSET	(0x100000000)

/* PL330 supports max 16MB dma based on AXI bus size */
#define PL330_MAX_DMA_SIZE	(0x1000000)

/* Maximum possible values for PL330 ucode loop counters */
#define PL330_LOOP_COUNTER0_MAX	(0x100)
#define PL330_LOOP_COUNTER1_MAX	(0x100)

#define MAX_DMA_CHANNELS	(1)

#define DMAC_PL330_NONSEC_MODE	(1)

#define DMAC_PL330_INTEN		(0x20)
#define DMAC_PL330_INTCLR		(0x2c)
#define DMAC_PL330_CS0			(0x100)
#define DMAC_PL330_DBGSTATUS	(0xd00)
#define DMAC_PL330_DBGCMD		(0xd04)
#define DMAC_PL330_DBGINST0		(0xd08)
#define DMAC_PL330_DBGINST1		(0xd0c)

/*
 * TIMEOUT value of 100000us is kept to cover all possible data
 * transfer sizes, with lesser time out value(10us) DMA channel
 * appears to be busy on FPGA/Emul environment. Ideally 100000us
 * timeout value should never hit.
 */
#define DMA_TIMEOUT_US		(100000)

#define CH_STATUS_MASK		(0xf)
#define DATA_MASK			(0xf)

#define DMA_INTSR1_SHIFT	(24)
#define DMA_INTSR0_SHIFT	(16)
#define DMA_INTSR0			(0xa0)
#define DMA_SECURE_SHIFT	(17)
#define DMA_CH_SHIFT		(8)

#define CONTROL_OFFSET		(0x4)
#define HIGHER_32_ADDR_MASK	(0x0f)
#define DST_ADDR_SHIFT		(0x4)

#define MICROCODE_SIZE_MAX	(0x400)
#define GET_MAX_DMA_SIZE(byte_width, burst_len) \
		(PL330_LOOP_COUNTER0_MAX * PL330_LOOP_COUNTER1_MAX * \
		(byte_width) * ((burst_len) + 1))

#define CC_SRCINC_SHIFT			(0)
#define CC_DSTINC_SHIFT			(14)
#define CC_SRCPRI_SHIFT			(8)
#define CC_DSTPRI_SHIFT			(22)
#define CC_DSTNS_SHIFT			(23)
#define CC_SRCBRSTLEN_SHIFT		(4)
#define CC_DSTBRSTLEN_SHIFT		(18)
#define CC_SRCBRSTSIZE_SHIFT	(1)
#define CC_DSTBRSTSIZE_SHIFT	(15)
#define CC_SRCCCTRL_SHIFT		(11)
#define CC_SRCCCTRL_MASK		(0x7)
#define CC_DSTCCTRL_SHIFT		(25)
#define CC_DRCCCTRL_MASK		(0x7)
#define CC_SWAP_SHIFT			(28)
#define SRC_PRI_NONSEC_VALUE	(0x2)
#define SRC_PRI_SEC_VALUE		(0x0)

#define OP_DMA_MOV			(0xbc)
#define OP_DMA_LOOP_COUNT1	(0x22)
#define OP_DMA_LOOP			(0x20)
#define OP_DMA_LD			(0x4)
#define OP_DMA_ST			(0x8)
#define OP_DMA_SEV			(0x34)
#define OP_DMA_END			(0x00)
#define OP_DMA_LP_BK_JMP1	(0x38)
#define OP_DMA_LP_BK_JMP2	(0x3c)
#define SZ_CMD_DMAMOV		(0x6)

/**
 * @brief DMA attributes
 */
enum dma_attribute_type {
	DMA_ATTR_BUFFER_ADDRESS_ALIGNMENT,
	DMA_ATTR_BUFFER_SIZE_ALIGNMENT,
	DMA_ATTR_COPY_ALIGNMENT,
	DMA_ATTR_MAX_BLOCK_COUNT,
};

/** The DMA callback event has occurred at the completion of a transfer list */
#define DMA_STATUS_COMPLETE	(0)
/** The DMA callback has occurred at the completion of a single transfer block in a transfer list */
#define DMA_STATUS_BLOCK	(1)

enum dmamov_type {
	/* Source Address Register */
	SAR = 0,
	/* Channel Control Register */
	CCR,
	/* Destination Address Register */
	DAR,
};

/* Channel specific private data */
struct dma_pl330_ch_internal {
	uint64_t src_addr;
	uint64_t dst_addr;
	int src_burst_sz;
	uint32_t src_burst_len;
	int dst_burst_sz;
	uint32_t dst_burst_len;
	uint32_t trans_size;
	uint32_t dst_id;
	uint32_t src_id;
	uint32_t perip_type;
	uint32_t breq_only;
	uint32_t src_cache_ctrl;
	uint32_t dst_cache_ctrl;
	uint32_t dst_inc;
	uint32_t src_inc;
	int nonsec_mode;
};

struct dma_pl330_ch_config {
	/* Channel configuration details */
	uint64_t src_addr;
	enum dma_addr_adj src_addr_adj;
	uint64_t dst_addr;
	enum dma_addr_adj dst_addr_adj;
	enum dma_channel_direction direction;
	uint32_t trans_size;
	void *user_data;
	dma_callback_t dma_callback;
	uint64_t dma_exec_addr;
	//SemaphoreHandle_t ch_mutex;
	int channel_active;

	/* Channel specific private data */
	struct dma_pl330_ch_internal internal;
};

struct dma_pl330_config {
	struct pl330 *dma;
	struct sysreg_sysremap_regs *control;
	uint64_t mcode_base;
	struct sac_pl330_dbg *sac_dma;
};

struct dma_pl330_dev_data {
	struct dma_pl330_ch_config channels[MAX_DMA_CHANNELS];
};
