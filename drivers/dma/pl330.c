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

#include <util.h>
#include <rebel_h_platform.h>
#include <driver.h>
#include "pl330.h"
#include "interrupt.h"
#include <string.h>

extern const char dma_mcode_start[];

static struct dma_pl330_config pl330_config = {
	.dma = (struct pl330 *)DMA_ROT,
	.control = (struct sysreg_sysremap_regs *)SYSREG_SYSREMAP,
	.mcode_base = (mem_addr_t)dma_mcode_start,
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

	loop_counter = ch_handle->trans_size /
			   (srcbytewidth * (ch_handle->src_burst_len + 1));

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
		   (ch_handle->src_burst_len << CC_SRCBRSTLEN_SHIFT)  +
		   (ch_handle->src_burst_sz << CC_SRCBRSTSIZE_SHIFT)  +
		   (ch_handle->src_inc << CC_SRCINC_SHIFT);

	return ccr;
}

static void dma_pl330_calc_burstsz_len(struct dma_pl330_ch_internal *ch_handle,
					   uint64_t dst, uint64_t src,
					   uint32_t size)
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

static void dma_pl330_cfg_dmac_add_control(uint64_t dst, uint64_t src)
{
	struct sysreg_sysremap_regs *control = pl330_config.control;

	control->m3_user_ovrd_value.awuser_sfr = (dst & REBEL_40BIT_HIGH_ADDR_MASK) >> 32;
	control->m3_user_ovrd_value.aruser_sfr = (src & REBEL_40BIT_HIGH_ADDR_MASK) >> 32;
}

void dma_set_amba_ovrd(uint32_t sid, uint32_t ssid, uint32_t sec)
{
	volatile struct sysreg_sysremap_regs *control = pl330_config.control;

	control->m3_sid_ovrd_value.arsid_sfr = sid;
	control->m3_sid_ovrd_value.awsid_sfr = sid;

	control->m3_ssid_ovrd_value.arssid_sfr = ssid;
	control->m3_ssid_ovrd_value.awssid_sfr = ssid;

	control->m3_ssidv_ovrd_value.arssidv_sfr = SELECT;
	control->m3_ssidv_ovrd_value.awssidv_sfr = SELECT;

	control->m3_secsid_ovrd_value.arsecsid_sfr = sec;
	control->m3_secsid_ovrd_value.awsecsid_sfr = sec;

	control->m3_sid_ovrd_sel.arsid_ovrd_sel = SELECT;
	control->m3_sid_ovrd_sel.awsid_ovrd_sel = SELECT;

	control->m3_ssid_ovrd_sel.arssid_ovrd_sel = SELECT;
	control->m3_ssid_ovrd_sel.awssid_ovrd_sel = SELECT;

	control->m3_ssidv_ovrd_sel.arssidv_ovrd_sel = SELECT;
	control->m3_ssidv_ovrd_sel.awssidv_ovrd_sel = SELECT;

	control->m3_secsid_ovrd_sel.arsecsid_ovrd_sel = SELECT;
	control->m3_secsid_ovrd_sel.awsecsid_ovrd_sel = SELECT;
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

static inline uint32_t dma_pl330_gen_mov(mem_addr_t buf, enum dmamov_type type, uint32_t val)
{
	sys_write8(OP_DMA_MOV, buf);
	sys_write8(type, buf + 1);
	sys_write8(val, buf + 2);
	sys_write8(val >> 8, buf + 3);
	sys_write8(val >> 16, buf + 4);
	sys_write8(val >> 24, buf + 5);

	return SZ_CMD_DMAMOV;
}

static inline void dma_pl330_gen_op(uint8_t opcode, uint32_t addr, uint32_t val)
{
	sys_write8(opcode, addr);
	sys_write8(val, addr + 1);
}

static int dma_pl330_setup_ch(struct dma_pl330_ch_internal *ch_dat, int channel)
{
	mem_addr_t dma_exec_addr;
	uint32_t offset = 0, ccr;
	uint32_t lp0_start, lp1_start;
	uint32_t loop_counter0 = 0, loop_counter1 = 0;
	uint32_t srcbytewidth, dstbytewidth;
	uint32_t loop_counter, residue;
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_dev_data *data = &pl330_data;
	int secure = ch_dat->nonsec_mode ? SRC_PRI_NONSEC_VALUE : SRC_PRI_SEC_VALUE;

	channel_cfg = &(pl330_data.channels[channel]);
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
		offset += dma_pl330_gen_mov(dma_exec_addr + offset,
						CCR, ccr);
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset,
				 ((residue - 1) & 0xff));
		offset = offset + 2;
		lp0_start = offset;
		sys_write8(OP_DMA_LD, dma_exec_addr + offset);
		sys_write8(OP_DMA_ST, dma_exec_addr + offset + 1);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
				 ((offset - lp0_start) & 0xff));
		offset = offset + 2;
	}

	if (data->channels[channel].dma_callback != NULL) {
		sys_write8(OP_DMA_SEV, dma_exec_addr + offset);
		sys_write8(channel << 3, dma_exec_addr + offset + 1);
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

	channel_cfg = &(pl330_data.channels[channel]);
	do {
		data = dma->dbg.dbgstatus;
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((data & DATA_MASK) != 0);

	dma->dbg.dbginst0 = ((channel << DMA_INTSR1_SHIFT) +
			(DMA_INTSR0 << DMA_INTSR0_SHIFT) +
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

static int dma_pl330_xfer(uint64_t dst, uint64_t src, uint32_t size, uint32_t channel,
		uint32_t *xfer_size)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;
	int ret;
	uint32_t max_size;

	channel_cfg = &(pl330_data.channels[channel]);
	ch_handle = &channel_cfg->internal;
	dma_pl330_calc_burstsz_len(ch_handle, dst, src, size);

	max_size = GET_MAX_DMA_SIZE((1 << ch_handle->src_burst_sz),
					ch_handle->src_burst_len);

	if (size > max_size) {
		size = max_size;
	}

	dma_pl330_config_channel(channel_cfg, dst, src, size);

	dma_pl330_cfg_dmac_add_control(dst, src);

	ret = dma_pl330_setup_ch(ch_handle, channel);
	if (ret) {
		printf("Failed to setup channel for DMA PL330\n");
		goto err;
	}

	ret = dma_pl330_start_dma_ch(channel, ch_handle->nonsec_mode);
	if (ret) {
		printf("Failed to start DMA PL330\n");
		goto err;
	}

	ret = dma_pl330_wait(channel);
	if (ret) {
		printf("Failed waiting to finish DMA PL330\n");
		goto err;
	}

	*xfer_size = size;
err:
	return ret;

}
static int dma_pl330_handle_boundary(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size)
{
	uint32_t dst_low = (uint32_t)dst;
	uint32_t src_low = (uint32_t)src;
	uint32_t transfer_size;
	int ret;

	if (size > (PL330_MAX_OFFSET - dst_low)) {
		transfer_size = PL330_MAX_OFFSET - dst_low;
		ret = dma_pl330_submit(dst, src, channel, transfer_size);
		if (ret < 0) {
			return ret;
		}

		dst += transfer_size;
		src += transfer_size;
		size -= transfer_size;
		return dma_pl330_submit(dst, src, channel, size);
	}

	if (size > (PL330_MAX_OFFSET - src_low)) {
		transfer_size = PL330_MAX_OFFSET - src_low;
		ret = dma_pl330_submit(dst, src, channel, transfer_size);
		if (ret < 0) {
			return ret;
		}

		src += transfer_size;
		dst += transfer_size;
		size -= transfer_size;
		return dma_pl330_submit(dst, src, channel, size);
	}

	return 0;
}

static int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t channel, uint32_t size)
{
	int ret;
	uint32_t xfer_size;

	/*
	 * Pl330 has only 32bit registers and supports 4GB memory.
	 * 4GB memory window can be configured using DMAC_AXI_ADD_CONTROL
	 * registers. 32bit boundary (0xffffffff) should be check.
	 * DMA on boundary condition is taken care in below function.
	 */

	if ((size > (PL330_MAX_OFFSET - (uint32_t)dst)) ||
		(size > (PL330_MAX_OFFSET - (uint32_t)src))) {
		return dma_pl330_handle_boundary(dst, src, channel, size);
	}

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

static inline void dma_clear_interrupt(uint32_t channel)
{
	struct pl330 *dma = pl330_config.dma;
	uint32_t val = dma->ctrl.intclr;

	dma->ctrl.intclr = val | (1 << channel);
}

int dma_configure(uint32_t channel, struct dma_config *cfg)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;

	if (channel >= MAX_DMA_CHANNELS) {
		return -EINVAL;
	}

	channel_cfg = &(pl330_data.channels[channel]);
	xSemaphoreTake(channel_cfg->ch_mutex, portMAX_DELAY);
	if (channel_cfg->channel_active) {
		xSemaphoreGive(channel_cfg->ch_mutex);
		return -EBUSY;
	}
	channel_cfg->channel_active = 1;
	xSemaphoreGive(channel_cfg->ch_mutex);

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

	channel_cfg = &(pl330_data.channels[channel]);
	ret = dma_pl330_submit(channel_cfg->dst_addr, channel_cfg->src_addr,
			channel, channel_cfg->trans_size);

	xSemaphoreTake(channel_cfg->ch_mutex, portMAX_DELAY);
	channel_cfg->channel_active = 0;

	xSemaphoreGive(channel_cfg->ch_mutex);

	return ret;
}

void dma_isr(void)
{
	volatile struct pl330 *dma = pl330_config.dma;
	struct dma_pl330_dev_data *data = &pl330_data;
	uint32_t val, ch;

	val = dma->ctrl.intmis;

	for (ch = 0; ch < MAX_DMA_CHANNELS; ch++) {
		if ((val & (1 << ch)) && (data->channels[ch].dma_callback)) {
			/* clear interrupt status */
			dma_clear_interrupt(ch);
			/* call callback function each channel */
			data->channels[ch].dma_callback(data->channels[ch].user_data, ch, 0);
		}
	}
}

void dma_fault_isr(void)
{
	volatile struct pl330 *dma = pl330_config.dma;
	uint32_t val, ch;

	val = dma->ctrl.fsrc;

	for (ch = 0; ch < MAX_DMA_CHANNELS; ch++) {
		if ((val & (1 << ch))) {
			printf("DMA Fault!! channel->%d\r\n", ch);
			dma->dbg.dbginst0 = (OP_DMA_KILL << DMA_INTSR0_SHIFT) | (ch  << DMA_CH_SHIFT) | (0x1);
			dma->dbg.dbgcmd = DMA_EXEC;
		}
	}
}

int dma_init(void)
{
	struct dma_pl330_ch_config *channel_cfg;

	for (int channel = 0; channel < MAX_DMA_CHANNELS; channel++) {
		channel_cfg = &(pl330_data.channels[channel]);
		channel_cfg->dma_exec_addr = pl330_config.mcode_base + (channel * MICROCODE_SIZE_MAX);
		channel_cfg->ch_mutex = xSemaphoreCreateMutex();
	}

	for (uint32_t i = DMA_INTID_START; i <= DMA_INTID_END; i++) {
		connect_interrupt_with_handler(i, 0, IRQ_TYPE_LEVEL, dma_isr, NULL);
	}

	connect_interrupt_with_handler(DMA_ABORT_INTID, 0, IRQ_TYPE_LEVEL, dma_fault_isr, NULL);

	return 0;
}


#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(4, dma_init);
#endif
