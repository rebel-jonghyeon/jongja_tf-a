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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys_io.h>
#include <string.h>
#include "dma_reg.h"
#include "dma.h"

#define DMA_ROT_BASE				(0X1FF02C0000)
#define SYSREG_SYSREMAP_BASE		(0X1FF0220000)
#define MCODE_BASE					(0X1FF0020000)
#define MAX_MCODE_SIZE				(16 * 4)

#define BYTE_WIDTH(burst_size) (1 << (burst_size))

struct dma_pl330_dev_data pl330_data;

const struct dma_pl330_config pl330_config = {
	.dma = (struct pl330 *)DMA_ROT_BASE,
	.control = (struct sysreg_sysremap *)SYSREG_SYSREMAP_BASE,
	.mcode_base = MCODE_BASE,
};

int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size);

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

	loop_counter = ch_handle->trans_size /
		(srcbytewidth * (ch_handle->src_burst_len + 1));

	residue = ch_handle->trans_size - loop_counter *
		(srcbytewidth * (ch_handle->src_burst_len + 1));

	/* Add one more counter to allow an aligned size transfer */
	if (residue != 0) {
		loop_counter++;
		residue = 0;
	}

	*psrc_byte_width = srcbytewidth;
	*pdst_byte_width = dstbytewidth;
	*ploop_counter = loop_counter;
	*presidue = residue;
}

static uint32_t dma_pl330_ch_ccr(struct dma_pl330_ch_internal *ch_handle)
{
	uint32_t ccr;
	int secure = ch_handle->nonsec_mode ? SRC_PRI_NONSEC_VALUE :
		SRC_PRI_SEC_VALUE;

	ccr = ((ch_handle->dst_cache_ctrl & CC_SRCCCTRL_MASK) <<
			CC_DSTCCTRL_SHIFT) +
		((ch_handle->nonsec_mode) << CC_DSTNS_SHIFT) +
		(ch_handle->dst_burst_len << CC_DSTBRSTLEN_SHIFT) +
		(ch_handle->dst_burst_sz << CC_DSTBRSTSIZE_SHIFT) +
		(ch_handle->dst_inc << CC_DSTINC_SHIFT) +
		((ch_handle->src_cache_ctrl & CC_SRCCCTRL_MASK) <<
		 CC_SRCCCTRL_SHIFT) +
		(secure << CC_SRCPRI_SHIFT) +
		(ch_handle->src_burst_len << CC_SRCBRSTLEN_SHIFT) +
		(ch_handle->src_burst_sz << CC_SRCBRSTSIZE_SHIFT) +
		(ch_handle->src_inc << CC_SRCINC_SHIFT);

	return ccr;
}

static void dma_pl330_calc_burstsz_len(struct dma_pl330_ch_internal *ch_handle,
									   uint64_t dst, uint64_t src, uint32_t size)
{
	uint32_t burst_sz, burst_len;

	burst_sz = MAX_BURST_SIZE_LOG2;
	burst_len = MAX_BURST_LEN;

	ch_handle->src_burst_len = burst_len;
	ch_handle->src_burst_sz = burst_sz;
	ch_handle->dst_burst_len = burst_len;
	ch_handle->dst_burst_sz = burst_sz;
}

static void dma_pl330_sysreg_control(void)
{
	sys_write32(0x000000, 0x1FF0220308);
	sys_write32(0x1F001F, 0x1FF022031C);
	sys_write32(0x000101, 0x1FF022032c);
	sys_write32(0x010001, 0x1FF0220388);
	sys_write32(0x010001, 0x1FF022038C);
	sys_write32(0x010001, 0x1FF022039C);
}

static void dma_pl330_config_channel(struct dma_pl330_ch_config *ch_cfg,
									 uint64_t dst, uint64_t src, uint32_t size)
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

static uint32_t dma_pl330_gen_mov(uint64_t buf, enum dmamov_type type, uint32_t val)
{
	sys_write8(OP_DMA_MOV, buf);
	sys_write8(type, buf + 1);
	sys_write8(val, buf + 2);
	sys_write8(val >> 8, buf + 3);
	sys_write8(val >> 16, buf + 4);
	sys_write8(val >> 24, buf + 5);

	return SZ_CMD_DMAMOV;
}

void dma_pl330_gen_op(uint8_t opcode, uint64_t addr, uint32_t val)
{
	sys_write8(opcode, addr);
	sys_write8(val, addr + 1);
}

int dma_pl330_setup_ch(struct dma_pl330_ch_internal *ch_dat, int channel)
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
		dma_pl330_gen_op(OP_DMA_LOOP_COUNT1, dma_exec_addr + offset,
						 loop_counter1 & 0xff);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset,
						 loop_counter0 & 0xff);
		offset = offset + 2;
		lp1_start = offset;
		lp0_start = offset;
		sys_write8(OP_DMA_LD, dma_exec_addr + offset);
		sys_write8(OP_DMA_ST, dma_exec_addr + offset + 1);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
						 ((offset - lp0_start) & 0xff));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset,
						 (loop_counter0 & 0xff));
		offset = offset + 2;
		loop_counter1--;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP2, dma_exec_addr + offset,
						 ((offset - lp1_start) & 0xff));
		offset = offset + 2;
	}

	if ((loop_counter % PL330_LOOP_COUNTER0_MAX) != 0) {
		loop_counter0 = (loop_counter % PL330_LOOP_COUNTER0_MAX) - 1;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset,
						 (loop_counter0 & 0xff));
		offset = offset + 2;
		loop_counter1--;
		lp0_start = offset;
		sys_write8(OP_DMA_LD, dma_exec_addr + offset);
		sys_write8(OP_DMA_ST, dma_exec_addr + offset + 1);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
						 ((offset - lp0_start) & 0xff));
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
		sys_write8(OP_DMA_LD, dma_exec_addr + offset);
		sys_write8(OP_DMA_ST, dma_exec_addr + offset + 1);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset, ((offset - lp0_start) & 0xff));
		offset = offset + 2;
	}

	sys_write8(OP_DMA_END, dma_exec_addr + offset);
	sys_write8(OP_DMA_END, dma_exec_addr + offset + 1);
	sys_write8(OP_DMA_END, dma_exec_addr + offset + 2);
	sys_write8(OP_DMA_END, dma_exec_addr + offset + 3);

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

	dma->dbg.dbginst0 = ((channel << DMA_INTSR1_SHIFT) +
						 (DMA_INTSR0 << DMA_INTSR0_SHIFT) +
						 (secure << DMA_SECURE_SHIFT) + (channel << DMA_CH_SHIFT));

	dma->dbg.dbginst1 = (uint32_t)channel_cfg->dma_exec_addr;
	dma->dbg.dbgcmd = 0x0;

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

int dma_pl330_xfer(uint64_t dst, uint64_t src, uint32_t size, uint32_t channel,
				   uint32_t *xfer_size)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;
	int ret;
	uint32_t max_size;

	channel_cfg = &pl330_data.channels[channel];
	ch_handle = &channel_cfg->internal;

	dma_pl330_config_channel(channel_cfg, dst, src, size);

	dma_pl330_calc_burstsz_len(ch_handle, dst, src, size);

	max_size = GET_MAX_DMA_SIZE((1 << ch_handle->src_burst_sz),
								ch_handle->src_burst_len);

	if (size > max_size) {
		size = max_size;
	}

	/* System level control
	 * Override upper 8 bit addr of 40bit & control on system level via SYSREG
	 */
	dma_pl330_sysreg_control();

	ret = dma_pl330_setup_ch(ch_handle, channel);
	if (ret) {
		goto err;
	}

	ret = dma_pl330_start_dma_ch(channel, ch_handle->nonsec_mode);
	if (ret) {
		goto err;
	}

	ret = dma_pl330_wait(channel);
	if (ret) {
		goto err;
	}

	*xfer_size = size;
err:
	return ret;

}

int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size)
{
	int ret = 0;
	uint32_t xfer_size;

	while (size) {
		xfer_size = 0;
		ret = dma_pl330_xfer(dst, src, size, channel, &xfer_size);
		if (ret) {
			return ret;
		}
		if (xfer_size > size) {
			return -EFAULT;
		}
		size -= xfer_size;
		dst += xfer_size;
		src += xfer_size;
	}

	return ret;
}

int dma_load(uint64_t src, uint64_t dst, uint32_t size)
{
	struct dma_pl330_ch_config *channel_cfg;
	int ret;

	uint32_t channel = 0;

	/*
	 * NOTE: Initialize SRAM region with 0x00 before using it to avoid X-value propagation.
	 * JIRA: REBELH-829
	 */
	memset((void *)MCODE_BASE, 0x00, MAX_MCODE_SIZE);

	channel_cfg = &pl330_data.channels[channel];
	channel_cfg->dst_addr = dst;
	channel_cfg->src_addr = src;
	channel_cfg->trans_size = size;
	channel_cfg->dma_exec_addr = pl330_config.mcode_base;
	channel_cfg->src_addr_adj = DMA_ADDR_ADJ_INCREMENT;
	channel_cfg->dst_addr_adj = DMA_ADDR_ADJ_INCREMENT;

	ret = dma_pl330_submit(channel_cfg->dst_addr, channel_cfg->src_addr,
						   channel, channel_cfg->trans_size);

	channel_cfg->channel_active = 0;

	return ret;
}
