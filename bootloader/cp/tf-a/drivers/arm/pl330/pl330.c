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

#include <assert.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <drivers/arm/pl330.h>
#include <stdlib.h>
#include <lib/mmio.h>
#include <common/debug.h>
#include <platform_def.h>

#define DMA_BASE		0x1ff02c0000U

char mcode[1024] __attribute__((aligned(16)));

static struct dma_pl330_config pl330_config = {
	.dma = (struct pl330 *)DMA_BASE,
};

static struct dma_pl330_dev_data pl330_data;

#define BYTE_WIDTH(burst_size) (1 << (burst_size))

static int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size);
static void dma_pl330_get_counter(struct dma_pl330_ch_internal *ch_handle,
								  uint32_t *psrc_byte_width,
								  uint32_t *pdst_byte_width,
								  uint32_t *ploop_counter,
								  uint32_t *presidue)
{
	uint32_t srcbytewidth, dstbytewidth;
	uint32_t loop_counter, residue;

	srcbytewidth = BYTE_WIDTH(ch_handle->src_burst_sz);
	dstbytewidth = BYTE_WIDTH(ch_handle->dst_burst_sz);

	loop_counter = ch_handle->trans_size / (srcbytewidth * (ch_handle->src_burst_len + 1));

	residue = ch_handle->trans_size - loop_counter *
		      (srcbytewidth * (ch_handle->src_burst_len + 1));

	*psrc_byte_width = srcbytewidth;
	*pdst_byte_width = dstbytewidth;
	*ploop_counter = loop_counter;
	*presidue = residue;
}

static uint32_t dma_pl330_ch_ccr(struct dma_pl330_ch_internal *ch_handle)
{
	uint32_t ccr;
	int secure = ch_handle->nonsec_mode ? SRC_PRI_NONSEC_VALUE : SRC_PRI_SEC_VALUE;

	ccr = ((ch_handle->dst_cache_ctrl & CC_SRCCCTRL_MASK) << CC_DSTCCTRL_SHIFT) +
		   ((ch_handle->nonsec_mode) << CC_DSTNS_SHIFT) +
		   (ch_handle->dst_burst_len << CC_DSTBRSTLEN_SHIFT) +
		   (ch_handle->dst_burst_sz << CC_DSTBRSTSIZE_SHIFT) +
		   (ch_handle->dst_inc << CC_DSTINC_SHIFT) +
		   ((ch_handle->src_cache_ctrl & CC_SRCCCTRL_MASK) << CC_SRCCCTRL_SHIFT) +
		   (secure << CC_SRCPRI_SHIFT) +
		   (ch_handle->src_burst_len << CC_SRCBRSTLEN_SHIFT)  +
		   (ch_handle->src_burst_sz << CC_SRCBRSTSIZE_SHIFT)  +
		   (ch_handle->src_inc << CC_SRCINC_SHIFT);

	return ccr;
}

static void dma_pl330_calc_burstsz_len(struct dma_pl330_ch_internal *ch_handle, uint64_t dst,
									   uint64_t src, uint32_t size)
{
	uint32_t byte_width, burst_sz, burst_len;

	burst_sz = MAX_BURST_SIZE_LOG2;
	while ((src | dst | size) & ((BYTE_WIDTH(burst_sz)) - 1)) {
		burst_sz--;
	}

	byte_width = BYTE_WIDTH(burst_sz);

	burst_len = MAX_BURST_LEN;
	while (burst_len) {
		if (!(size % ((burst_len + 1) << byte_width))) {
			break;
		}

		burst_len--;
	}

	ch_handle->src_burst_len = burst_len;
	ch_handle->src_burst_sz = burst_sz;
	ch_handle->dst_burst_len = burst_len;
	ch_handle->dst_burst_sz = burst_sz;
}

static void dma_pl330_config_channel(struct dma_pl330_ch_config *ch_cfg, uint64_t dst,
									 uint64_t src, uint32_t size)
{
	struct dma_pl330_ch_internal *ch_handle = &ch_cfg->internal;

	ch_handle->src_addr = src;
	ch_handle->dst_addr = dst;
	ch_handle->trans_size = size;
	ch_handle->nonsec_mode = DMAC_PL330_NONSEC_MODE;

	if (ch_cfg->src_addr_adj == DMA_ADDR_ADJ_INCREMENT) {
		ch_handle->src_inc = 1;
	}

	if (ch_cfg->dst_addr_adj == DMA_ADDR_ADJ_INCREMENT) {
		ch_handle->dst_inc = 1;
	}
}

static inline uint32_t dma_pl330_gen_mov(uint64_t buf, enum dmamov_type type, uint32_t val)
{
	mmio_write_8(buf, OP_DMA_MOV);
	mmio_write_8(buf + 1, type);
	mmio_write_8(buf + 2, val);
	mmio_write_8(buf + 3, val >> 8);
	mmio_write_8(buf + 4, val >> 16);
	mmio_write_8(buf + 5, val >> 24);

	return SZ_CMD_DMAMOV;
}

static inline void dma_pl330_gen_op(uint8_t opcode, uint64_t addr, uint32_t val)
{
	mmio_write_8(addr, opcode);
	mmio_write_8(addr + 1, val);
}

static int dma_pl330_setup_ch(struct dma_pl330_ch_internal *ch_dat, int channel)
{
	uint64_t dma_exec_addr;
	uint32_t offset = 0, ccr;
	uint32_t lp0_start, lp1_start;
	uint32_t loop_counter0 = 0, loop_counter1 = 0;
	uint32_t srcbytewidth, dstbytewidth;
	uint32_t loop_counter, residue;
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_dev_data *data = &pl330_data;
	int secure = ch_dat->nonsec_mode ? SRC_PRI_NONSEC_VALUE : SRC_PRI_SEC_VALUE;

	channel_cfg = &pl330_data.channels[channel];
	dma_exec_addr = channel_cfg->dma_exec_addr;

	offset  += dma_pl330_gen_mov(dma_exec_addr, SAR, ch_dat->src_addr);

	offset  += dma_pl330_gen_mov(dma_exec_addr + offset, DAR, ch_dat->dst_addr);

	ccr = dma_pl330_ch_ccr(ch_dat);

	offset  += dma_pl330_gen_mov(dma_exec_addr + offset, CCR, ccr);

	dma_pl330_get_counter(ch_dat, &srcbytewidth, &dstbytewidth, &loop_counter, &residue);

	if (loop_counter >= PL330_LOOP_COUNTER0_MAX) {
		loop_counter0 = PL330_LOOP_COUNTER0_MAX - 1;
		loop_counter1 = loop_counter / PL330_LOOP_COUNTER0_MAX - 1;
		dma_pl330_gen_op(OP_DMA_LOOP_COUNT1, dma_exec_addr + offset, loop_counter1 & 0xff);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, loop_counter0 & 0xff);
		offset = offset + 2;
		lp1_start = offset;
		lp0_start = offset;
		mmio_write_8(dma_exec_addr + offset, OP_DMA_LD);
		mmio_write_8(dma_exec_addr + offset + 1, OP_DMA_ST);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset, ((offset - lp0_start) & 0xff));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, (loop_counter0 & 0xff));
		offset = offset + 2;
		loop_counter1--;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP2, dma_exec_addr + offset, ((offset - lp1_start) & 0xff));
		offset = offset + 2;
	}

	if ((loop_counter % PL330_LOOP_COUNTER0_MAX) != 0) {
		loop_counter0 = (loop_counter % PL330_LOOP_COUNTER0_MAX) - 1;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, (loop_counter0 & 0xff));
		offset = offset + 2;
		loop_counter1--;
		lp0_start = offset;
		mmio_write_8(dma_exec_addr + offset, OP_DMA_LD);
		mmio_write_8(dma_exec_addr + offset + 1, OP_DMA_ST);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset, ((offset - lp0_start) & 0xff));
		offset = offset + 2;
	}

	if (residue != 0) {
		ccr = ((ch_dat->nonsec_mode) << CC_DSTNS_SHIFT) +
			   (0x0 << CC_DSTBRSTLEN_SHIFT) +
			   (0x0 << CC_DSTBRSTSIZE_SHIFT) +
			   (ch_dat->dst_inc << CC_DSTINC_SHIFT) +
			   (secure << CC_SRCPRI_SHIFT) +
			   (0x0 << CC_SRCBRSTLEN_SHIFT) +
			   (0x0 << CC_SRCBRSTSIZE_SHIFT) +
			   ch_dat->src_inc;
		offset += dma_pl330_gen_mov(dma_exec_addr + offset, CCR, ccr);
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, ((residue - 1) & 0xff));
		offset = offset + 2;
		lp0_start = offset;
		mmio_write_8(dma_exec_addr + offset, OP_DMA_LD);
		mmio_write_8(dma_exec_addr + offset + 1, OP_DMA_ST);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset, ((offset - lp0_start) & 0xff));
		offset = offset + 2;
	}

	if (data->channels[channel].dma_callback) {
		mmio_write_8(dma_exec_addr + offset, OP_DMA_SEV);
		mmio_write_8(dma_exec_addr + offset + 1, channel << 3);
		offset = offset + 2;
	}

	mmio_write_8(dma_exec_addr + offset, OP_DMA_END);
	mmio_write_8(dma_exec_addr + offset + 1, OP_DMA_END);
	mmio_write_8(dma_exec_addr + offset + 2, OP_DMA_END);
	mmio_write_8(dma_exec_addr + offset + 3, OP_DMA_END);

	return 0;
}

static int dma_pl330_start_dma_ch(int channel, int secure)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct pl330 *dma = pl330_config.dma;
	uint32_t count = 0U;
	uint32_t data;

	channel_cfg = &pl330_data.channels[channel];
	do {
		data = dma->dbg.dbgstatus;
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((data & DATA_MASK) != 0);

	dma->dbg.dbginst0 = ((channel << DMA_INTSR1_SHIFT) + (DMA_INTSR0 << DMA_INTSR0_SHIFT) +
						 (secure << DMA_SECURE_SHIFT) + (channel << DMA_CH_SHIFT));

	dma->dbg.dbginst1 = channel_cfg->dma_exec_addr;
	dma->dbg.dbgcmd = DMA_EXEC;

	count = 0U;
	do {
		data = dma->dbg.dbgcmd;
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((data & DATA_MASK) != 0);

	return 0;
}

static int dma_pl330_wait(int ch)
{
	struct pl330 *dma = pl330_config.dma;
	int count = 0U;

	do {
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((dma->ch_stat[ch].csr & CH_STATUS_MASK) != 0);
	return 0;
}

static int dma_pl330_xfer(uint64_t dst, uint64_t src, uint32_t size, uint32_t channel)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;
	int ret;
	uint32_t max_size;

	channel_cfg = &pl330_data.channels[channel];
	ch_handle = &channel_cfg->internal;
	dma_pl330_calc_burstsz_len(ch_handle, dst, src, size);

	max_size = GET_MAX_DMA_SIZE((1 << ch_handle->src_burst_sz), ch_handle->src_burst_len);

	if (size > max_size) {
		size = max_size;
	}

	dma_pl330_config_channel(channel_cfg, dst, src, size);

	ret = dma_pl330_setup_ch(ch_handle, channel);
	if (ret) {
		goto err;
	}

	ret = dma_pl330_start_dma_ch(channel, ch_handle->nonsec_mode);
	if (ret) {
		NOTICE("%s: Failed to start dma channel\n", __func__);
		goto err;
	}

	ret = dma_pl330_wait(channel);
	if (ret) {
		NOTICE("%s: Failed to wait dma channel\n", __func__);
		goto err;
	}

err:
	return ret;

}

static void dma_pl330_handle_boundary(uint64_t dst, uint64_t src)
{
	uint32_t temp_ovrd;

	temp_ovrd = (uint32_t)((dst & 0xff00000000) >> 16);
	temp_ovrd |= (uint32_t)((src & 0xff00000000) >> 32);

	mmio_write_32(0x1ff022031c, temp_ovrd);
	mmio_write_32(0x1ff022038c, 0x10001);
	mmio_write_32(0x1ff0220308, 0x0);
	mmio_write_32(0x1ff0220388, 0x10001);
	mmio_write_32(0x1ff022032c, 0x101);
	mmio_write_32(0x1ff022039c, 0x10001);
}

static int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size)
{
	int ret;

	dma_pl330_handle_boundary(dst, src);

	ret = dma_pl330_xfer(dst, src, size, channel);

	return ret;
}

void dma_wait_xfer_done(uint32_t channel)
{
	struct pl330 *dma = pl330_config.dma;

	volatile uint32_t val = dma->ch_stat[channel].csr;

	while (1) {
		if ((val & 0xf) == 0)
			break;
	}
}

static inline void dma_enable_interrupt(uint32_t channel)
{
	struct pl330 *dma = pl330_config.dma;
	uint32_t val = dma->ctrl.inten;

	dma->ctrl.inten = val | (1 << channel);
}

static inline void dma_disable_interrupt(uint32_t channel)
{
	struct pl330 *dma = pl330_config.dma;
	uint32_t val = dma->ctrl.inten;

	dma->ctrl.inten = val & ~(1 << channel);
}

int dma_configure(uint32_t channel, struct dma_config *cfg)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;

	if (channel >= MAX_DMA_CHANNELS) {
		return -EINVAL;
	}

	channel_cfg = &pl330_data.channels[channel];
	channel_cfg->channel_active = 1;

	if (cfg->channel_direction != MEMORY_TO_MEMORY) {
		return -ENOTSUP;
	}

	ch_handle = &channel_cfg->internal;
	memset(ch_handle, 0, sizeof(*ch_handle));

	channel_cfg->direction = cfg->channel_direction;
	channel_cfg->dst_addr_adj = cfg->head_block->dest_addr_adj;

	channel_cfg->src_addr = cfg->head_block->source_address;
	channel_cfg->dst_addr = cfg->head_block->dest_address;
	channel_cfg->trans_size = cfg->head_block->block_size;

	channel_cfg->dma_callback = cfg->dma_callback;
	channel_cfg->user_data = cfg->user_data;

	if (cfg->head_block->source_addr_adj == DMA_ADDR_ADJ_INCREMENT ||
		cfg->head_block->source_addr_adj == DMA_ADDR_ADJ_NO_CHANGE) {
		channel_cfg->src_addr_adj = cfg->head_block->source_addr_adj;
	} else {
		return -ENOTSUP;
	}

	if (cfg->head_block->dest_addr_adj == DMA_ADDR_ADJ_INCREMENT ||
		cfg->head_block->dest_addr_adj == DMA_ADDR_ADJ_NO_CHANGE) {
		channel_cfg->dst_addr_adj = cfg->head_block->dest_addr_adj;
	} else {
		return -ENOTSUP;
	}

	return 0;
}

int dma_start(uint32_t channel)
{
	struct dma_pl330_ch_config *channel_cfg;
	int ret;

	if (channel >= MAX_DMA_CHANNELS) {
		return -EINVAL;
	}

	dma_enable_interrupt(channel);

	channel_cfg = &pl330_data.channels[channel];
	ret = dma_pl330_submit(channel_cfg->dst_addr, channel_cfg->src_addr, channel,
						   channel_cfg->trans_size);

	channel_cfg->channel_active = 0;

	return ret;
}

int dma_init(uint64_t src_addr)
{
	struct dma_pl330_ch_config *channel_cfg;
	uint64_t mcode_base = ((uint64_t)mcode & 0xFFFFFFF) | (0x1FFULL << 28);
	uint64_t masked_src_addr = src_addr & 0xFF00000000ULL;

	if (masked_src_addr != 0x1E00000000 && masked_src_addr != 0x1F00000000) {
		mcode_base = (src_addr & 0xFF00000000ULL) | 0x60000000;
	}

	for (int channel = 0; channel < MAX_DMA_CHANNELS; channel++) {
		channel_cfg = &pl330_data.channels[channel];
		channel_cfg->dma_exec_addr = mcode_base;
	}

	return 0;
}

void dma_load_image(uint64_t dst_addr, uint64_t src_addr, uint32_t size)
{
	struct dma_config dma_cfg = {0};
	struct dma_block_config dma_block_cfg = {0};
	uint64_t before_tick = 0, after_tick = 0;

	VERBOSE("\ndma 0x%lx -> 0x%lx, size : 0x%x start ", src_addr, dst_addr, size);
	before_tick = read_cntpct_el0();
	dma_init(src_addr);

	dma_cfg.channel_direction = MEMORY_TO_MEMORY;
	dma_cfg.source_data_size = 8U;
	dma_cfg.dest_data_size = 8U;
	dma_cfg.source_burst_length = 16U;
	dma_cfg.dest_burst_length = 16U;
	dma_cfg.dma_callback = NULL;
	dma_cfg.block_count = 1U;
	dma_cfg.head_block = &dma_block_cfg;

	/* TODO : need to check image size from header */
	uint32_t image_size = size;
	uint64_t temp_src_addr = src_addr, temp_dst_addr = dst_addr;
	int ret = 0;

	while (image_size > 0) {
		if (image_size >= DMA_MAX_SIZE_LIMIT) {
			dma_block_cfg.block_size = DMA_MAX_SIZE_LIMIT;
			image_size -= DMA_MAX_SIZE_LIMIT;
		} else {
			dma_block_cfg.block_size = image_size;
			image_size = 0;
		}

		dma_block_cfg.source_address = (uint64_t)temp_src_addr;
		dma_block_cfg.dest_address = (uint64_t)temp_dst_addr;

		dma_configure(0, &dma_cfg);
		ret = dma_start(0);
		if (ret) {
			ERROR("BL2: Failed to dma load image(%d): dma 0x%lx -> 0x%lx, size : 0x%x\n",
			      ret, src_addr, dst_addr, size);
			assert(0);
		}

		temp_src_addr += DMA_MAX_SIZE_LIMIT;
		temp_dst_addr += DMA_MAX_SIZE_LIMIT;
	}
	after_tick = read_cntpct_el0();

	VERBOSE("end\n");
	VERBOSE("before tick : 0x%lx, after tick 0x%lx\n", before_tick, after_tick);
	VERBOSE("diff = 0x%lx\n", after_tick - before_tick);
}
