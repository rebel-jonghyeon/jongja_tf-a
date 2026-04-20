#include <rebel_h.h>
#include <sac.h>
#include "sac_custom.h"
#include "dma_reg.h"
#include "dma.h"
#include <string.h>

#define DMA_ROT_BASE				(0x1ff02c0000)
#define CSR0						(0x100)
#define SAC_DMA_DBG_BASE			(0x1ff02c0800)
#define SYSREG_SYSREMAP_BASE		(0x1ff0220000)

#define OVRD_HIGH_ADDR		(0x1F)
#define ENABLE				(1)

#define DMA_CH_0			(0)

const struct dma_pl330_config pl330_config = {
	.dma = (struct pl330 *)0x60800,
	.control = (struct sysreg_sysremap_regs *)0x60800,
	.mcode_base = 0x1ff803fe00, /* FreeRTOS_CM7.ld pl330_reserved */
	.sac_dma = (struct sac_pl330_dbg *)0x60800,
};

struct dma_pl330_dev_data pl330_data;

#define BYTE_WIDTH(burst_size) (1 << (burst_size))

int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t size);
void dma_pl330_get_counter(struct dma_pl330_ch_internal *ch_handle,
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

uint32_t dma_pl330_ch_ccr(struct dma_pl330_ch_internal *ch_handle)
{
	uint32_t ccr;
	int secure = ch_handle->nonsec_mode ? SRC_PRI_NONSEC_VALUE :
		SRC_PRI_SEC_VALUE;

	ccr = ((ch_handle->dst_cache_ctrl & CC_SRCCCTRL_MASK) << CC_DSTCCTRL_SHIFT) +
		((ch_handle->nonsec_mode) << CC_DSTNS_SHIFT) +
		(ch_handle->dst_burst_len << CC_DSTBRSTLEN_SHIFT) +
		(ch_handle->dst_burst_sz << CC_DSTBRSTSIZE_SHIFT) +
		(ch_handle->dst_inc << CC_DSTINC_SHIFT) +
		((ch_handle->src_cache_ctrl & CC_SRCCCTRL_MASK) << CC_SRCCCTRL_SHIFT) +
		(secure << CC_SRCPRI_SHIFT) +
		(ch_handle->src_burst_len << CC_SRCBRSTLEN_SHIFT) +
		(ch_handle->src_burst_sz << CC_SRCBRSTSIZE_SHIFT) +
		(ch_handle->src_inc << CC_SRCINC_SHIFT);

	return ccr;
}

void dma_pl330_calc_burstsz_len(struct dma_pl330_ch_internal *ch_handle,
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

void dma_pl330_cfg_dmac_add_control(void)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(SYSREG_SYSREMAP_BASE));
	struct sysreg_sysremap_regs *control = pl330_config.control;

	control->m3_prot_ovrd_value.val = 0x0;

	control->m3_user_ovrd_value.awuser_sfr = OVRD_HIGH_ADDR;
	control->m3_user_ovrd_value.aruser_sfr = OVRD_HIGH_ADDR;

	control->m3_prot_ovrd_sel.awprot1_ovrd_sel = ENABLE;
	control->m3_prot_ovrd_sel.arprot1_ovrd_sel = ENABLE;

	control->m3_user_ovrd_sel.awuser_ovrd_sel = ENABLE;
	control->m3_user_ovrd_sel.aruser_ovrd_sel = ENABLE;

	control->m3_secsid_ovrd_value.awsecsid_sfr = ENABLE;
	control->m3_secsid_ovrd_value.arsecsid_sfr = ENABLE;

	control->m3_secsid_ovrd_sel.awsecsid_ovrd_sel = ENABLE;
	control->m3_secsid_ovrd_sel.arsecsid_ovrd_sel = ENABLE;
}

void dma_pl330_config_channel(struct dma_pl330_ch_config *ch_cfg,
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

uint32_t dma_pl330_gen_mov(uint64_t buf, enum dmamov_type type, uint32_t val)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(buf));

	sboot_sac_write8(OP_DMA_MOV, GET_SAC_OFFSET(buf));
	sboot_sac_write8(type, GET_SAC_OFFSET(buf + 1));
	sboot_sac_write8(val, GET_SAC_OFFSET(buf + 2));
	sboot_sac_write8(val >> 8,  GET_SAC_OFFSET(buf + 3));
	sboot_sac_write8(val >> 16, GET_SAC_OFFSET(buf + 4));
	sboot_sac_write8(val >> 24, GET_SAC_OFFSET(buf + 5));

	return SZ_CMD_DMAMOV;
}

void dma_pl330_gen_op(uint8_t opcode, uint64_t addr, uint32_t val)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(addr));

	sboot_sac_write8(opcode, GET_SAC_OFFSET(addr));
	sboot_sac_write8(val, GET_SAC_OFFSET(addr + 1));
}

int dma_pl330_setup_ch(struct dma_pl330_ch_internal *ch_dat)
{
	uint64_t dma_exec_addr;
	uint32_t offset = 0, ccr;
	uint32_t lp0_start, lp1_start;
	uint32_t loop_counter0 = 0, loop_counter1 = 0;
	uint32_t srcbytewidth, dstbytewidth;
	uint32_t loop_counter, residue;
	struct dma_pl330_ch_config *channel_cfg;
	int secure = ch_dat->nonsec_mode ? SRC_PRI_NONSEC_VALUE : SRC_PRI_SEC_VALUE;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	dma_exec_addr = channel_cfg->dma_exec_addr;

	offset += dma_pl330_gen_mov(dma_exec_addr, SAR, ch_dat->src_addr);

	offset += dma_pl330_gen_mov(dma_exec_addr + offset, DAR, ch_dat->dst_addr);

	ccr = dma_pl330_ch_ccr(ch_dat);

	offset += dma_pl330_gen_mov(dma_exec_addr + offset, CCR, ccr);

	dma_pl330_get_counter(ch_dat, &srcbytewidth, &dstbytewidth, &loop_counter, &residue);

	if (loop_counter >= PL330_LOOP_COUNTER0_MAX) {
		loop_counter0 = PL330_LOOP_COUNTER0_MAX - 1;
		loop_counter1 = loop_counter / PL330_LOOP_COUNTER0_MAX - 1;
		dma_pl330_gen_op(OP_DMA_LOOP_COUNT1, dma_exec_addr + offset,
						 loop_counter1 & BYTE_MASK);
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, loop_counter0 & BYTE_MASK);
		offset = offset + 2;
		lp1_start = offset;
		lp0_start = offset;

		cmrt_sac_set_base(NULL, GET_SAC_BASE(dma_exec_addr));
		sboot_sac_write8(OP_DMA_LD, GET_SAC_OFFSET(dma_exec_addr + offset));
		sboot_sac_write8(OP_DMA_ST, GET_SAC_OFFSET(dma_exec_addr + offset + 1));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
						 ((offset - lp0_start) & BYTE_MASK));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, (loop_counter0 & BYTE_MASK));
		offset = offset + 2;
		loop_counter1--;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP2, dma_exec_addr + offset,
						 ((offset - lp1_start) & BYTE_MASK));
		offset = offset + 2;
	}

	if ((loop_counter % PL330_LOOP_COUNTER0_MAX) != 0) {
		loop_counter0 = (loop_counter % PL330_LOOP_COUNTER0_MAX) - 1;
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, (loop_counter0 & BYTE_MASK));
		offset = offset + 2;
		loop_counter1--;
		lp0_start = offset;
		cmrt_sac_set_base(NULL, GET_SAC_BASE(dma_exec_addr));
		sboot_sac_write8(OP_DMA_LD, GET_SAC_OFFSET(dma_exec_addr + offset));
		sboot_sac_write8(OP_DMA_ST, GET_SAC_OFFSET(dma_exec_addr + offset + 1));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
						 ((offset - lp0_start) & BYTE_MASK));
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
		dma_pl330_gen_op(OP_DMA_LOOP, dma_exec_addr + offset, ((residue - 1) & BYTE_MASK));
		offset = offset + 2;
		lp0_start = offset;
		cmrt_sac_set_base(NULL, GET_SAC_BASE(dma_exec_addr));
		sboot_sac_write8(OP_DMA_LD, GET_SAC_OFFSET(dma_exec_addr + offset));
		sboot_sac_write8(OP_DMA_ST, GET_SAC_OFFSET(dma_exec_addr + offset + 1));
		offset = offset + 2;
		dma_pl330_gen_op(OP_DMA_LP_BK_JMP1, dma_exec_addr + offset,
						 ((offset - lp0_start) & BYTE_MASK));
		offset = offset + 2;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(dma_exec_addr));
	sboot_sac_write8(OP_DMA_END, GET_SAC_OFFSET(dma_exec_addr + offset));
	sboot_sac_write8(OP_DMA_END, GET_SAC_OFFSET(dma_exec_addr + offset + 1));
	sboot_sac_write8(OP_DMA_END, GET_SAC_OFFSET(dma_exec_addr + offset + 2));
	sboot_sac_write8(OP_DMA_END, GET_SAC_OFFSET(dma_exec_addr + offset + 3));

	return 0;
}

int dma_pl330_start_dma_ch(int secure)
{
	struct dma_pl330_ch_config *channel_cfg;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(SAC_DMA_DBG_BASE));
	struct sac_pl330_dbg *dma = pl330_config.sac_dma;
	uint32_t count = 0U;
	uint32_t data;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	do {
		data = dma->dbgstatus;
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((data & DATA_MASK) != 0);

	dma->dbginst0 = ((DMA_CH_0 << DMA_INTSR1_SHIFT) +
			(DMA_INTSR0 << DMA_INTSR0_SHIFT) +
			(secure << DMA_SECURE_SHIFT) + (DMA_CH_0 << DMA_CH_SHIFT));

	dma->dbginst1 = channel_cfg->dma_exec_addr;
	dma->dbgcmd = 0x0;

	count = 0U;
	do {
		data = dma->dbgcmd;
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((data & DATA_MASK) != 0);

	return 0;
}

int dma_pl330_wait(void)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(DMA_ROT_BASE));
	struct pl330 *dma = pl330_config.dma;
	int count = 0U;

	do {
		if (++count > DMA_TIMEOUT_US) {
			return -ETIMEDOUT;
		}
	} while ((dma->ch_stat[DMA_CH_0].csr & CH_STATUS_MASK) != 0);
	return 0;
}

int dma_pl330_xfer(uint64_t dst, uint64_t src, uint32_t size,
				   uint32_t *xfer_size)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;
	int ret;
	uint32_t max_size;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	ch_handle = &channel_cfg->internal;
	dma_pl330_calc_burstsz_len(ch_handle, dst, src, size);

	max_size = GET_MAX_DMA_SIZE((1 << ch_handle->src_burst_sz),
								ch_handle->src_burst_len);

	if (size > max_size) {
		size = max_size;
	}

	dma_pl330_config_channel(channel_cfg, dst, src, size);
	/*
	 * Pl330 supports only 4GB boundary, but boundary region can be
	 * configured.
	 * TODO : add logic to support 40bit address
	 */
	dma_pl330_cfg_dmac_add_control();

	ret = dma_pl330_setup_ch(ch_handle);
	if (ret) {
		goto err;
	}

	ret = dma_pl330_start_dma_ch(ch_handle->nonsec_mode);
	if (ret) {
		goto err;
	}

	ret = dma_pl330_wait();
	if (ret) {
		goto err;
	}

	*xfer_size = size;
err:
	return ret;
}

int dma_pl330_handle_boundary(uint64_t dst, uint64_t src, uint32_t size)
{
	uint32_t dst_low = (uint32_t)dst;
	uint32_t src_low = (uint32_t)src;
	uint32_t transfer_size;
	int ret;

	if (size > (PL330_MAX_OFFSET - dst_low)) {
		transfer_size = PL330_MAX_OFFSET - dst_low;
		ret = dma_pl330_submit(dst, src, transfer_size);
		if (ret < 0) {
			return ret;
		}

		dst += transfer_size;
		src += transfer_size;
		size -= transfer_size;
		return dma_pl330_submit(dst, src, size);
	}

	if (size > (PL330_MAX_OFFSET - src_low)) {
		transfer_size = PL330_MAX_OFFSET - src_low;
		ret = dma_pl330_submit(dst, src, transfer_size);
		if (ret < 0) {
			return ret;
		}

		src += transfer_size;
		dst += transfer_size;
		size -= transfer_size;
		return dma_pl330_submit(dst, src, size);
	}

	return 0;
}

int dma_pl330_submit(uint64_t dst, uint64_t src, uint32_t size)
{
	int ret = 0;
	uint32_t xfer_size;

	/*
	 * Pl330 has only 32bit registers and supports 4GB memory.
	 * 4GB memory window can be configured using DMAC_AXI_ADD_CONTROL
	 * registers. 32bit boundary (0xffffffff) should be check.
	 * DMA on boundary condition is taken care in below function.
	 */

	if ((size > (PL330_MAX_OFFSET - (uint32_t)dst)) ||
		(size > (PL330_MAX_OFFSET - (uint32_t)src))) {
		return dma_pl330_handle_boundary(dst, src, size);
	}

	while (size) {
		xfer_size = 0;
		ret = dma_pl330_xfer(dst, src, size, &xfer_size);
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

int sboot_dma_configure(struct dma_config *cfg)
{
	struct dma_pl330_ch_config *channel_cfg;
	struct dma_pl330_ch_internal *ch_handle;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	if (channel_cfg->channel_active) {
		return -EBUSY;
	}
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

int sboot_dma_start(void)
{
	struct dma_pl330_ch_config *channel_cfg;
	int ret;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	ret = dma_pl330_submit(channel_cfg->dst_addr, channel_cfg->src_addr,
						   channel_cfg->trans_size);

	channel_cfg->channel_active = 0;

	return ret;
}

int sboot_dma_init(void)
{
	struct dma_pl330_ch_config *channel_cfg;

	channel_cfg = &pl330_data.channels[DMA_CH_0];
	channel_cfg->dma_exec_addr = pl330_config.mcode_base;

	return 0;
}

void sboot_dma_config(struct dma_block_config *dma_block_cfg)
{
	struct dma_config dma_cfg = {0};

	dma_cfg.channel_direction = MEMORY_TO_MEMORY;
	dma_cfg.source_data_size = 128U;
	dma_cfg.dest_data_size = 128U;
	dma_cfg.source_burst_length = 128U;
	dma_cfg.dest_burst_length = 128U;
	dma_cfg.block_count = 1U;
	dma_cfg.head_block = dma_block_cfg;

	sboot_dma_configure(&dma_cfg);
}

#define CHANNEL_OFFSET				(8)
#define CHANNEL_STATUS_MASK			(0xF)

void sboot_dma_xfer_done(void)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(DMA_ROT_BASE));
	while (1) {
		if ((sys_read32(GET_SAC_R_CPU_DATA(CSR0)) &
			CHANNEL_STATUS_MASK) == 0)
			break;
	}
}
