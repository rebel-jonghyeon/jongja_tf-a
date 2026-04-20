/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "rl_errors.h"

#include "pcie_dw.h"
#include "pcie_dw_iatu.h"
#include "pcie_dw_hdma.h"
#include "pcie_rebelh.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

#define CHAN_DATA(ch_num, prio, md, en, dir, max_tr)		\
	.chan_data[ch_num] = {									\
		.priority =	prio,									\
		.mode	  = md,										\
		.enable   =	en,										\
		.direction = dir,									\
		.max_transfers = max_tr,							\
	}

static struct pcie_ep_hdma_controller g_dw_ep_hdmac = {
	/* Write Channels */
	CHAN_DATA(0, 0, NON_LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(1, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(2, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(3, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(4, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(5, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(6, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(7, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(8, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(9, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(10, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(11, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(12, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(13, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(14, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),
	CHAN_DATA(15, 0, LINKED_LIST_MODE, 1, DW_PCIE_WRITE_HDMA, 128),

	/* Read Channels */
	CHAN_DATA(16, 0, NON_LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(17, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(18, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(19, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(20, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(21, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(22, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(23, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(24, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(25, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(26, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(27, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(28, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(29, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(30, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
	CHAN_DATA(31, 0, LINKED_LIST_MODE, 1, DW_PCIE_READ_HDMA, 128),
};

static enum dw_hdma_chan_attr pcie_hdma_get_channel_attribute(struct pcie_ep_hdma_controller *hdmac,
															  uint32_t channel)
{
	struct chan_plat_data *chan_data = &hdmac->chan_data[channel];

	if (chan_data->enable && chan_data->direction == DW_PCIE_WRITE_HDMA) {
		if (chan_data->mode == LINKED_LIST_MODE) {
			pcie_dbg_log("%s: Channel[%d] for DMA write with LL mode\n", __func__, channel);
			return LINKED_LIST_HDMA_WRITE;
		} else {
			pcie_dbg_log("%s: Channel[%d] for DMA write with non-LL mode\n", __func__, channel);
			return NON_LINKED_LIST_HDMA_WRITE;
		}
	} else if (chan_data->enable && chan_data->direction == DW_PCIE_READ_HDMA) {
		if (chan_data->mode == LINKED_LIST_MODE) {
			pcie_dbg_log("%s: Channel[%d] for DMA read with LL mode\n", __func__, channel);
			return LINKED_LIST_HDMA_READ;
		} else {
			pcie_dbg_log("%s: Channel[%d] for DMA read with non-LL mode\n", __func__, channel);
			return NON_LINKED_LIST_HDMA_READ;
		}
	} else
		return INVALID_CHANNEL;
}

struct pcie_ep_hdma_controller *pcie_hdmac_create(struct pcie_epc *epc)
{
	const struct dw_pcie_config *cfg = epc->cfg;

	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	struct pcie_ep_hdma_controller *pcie_hdmac_ptr = NULL;
	uint32_t i = 0;

	pcie_hdmac_ptr = &g_dw_ep_hdmac;

	if (pcie_hdmac_ptr->is_created)
		return pcie_hdmac_ptr;

	pcie_hdmac_ptr->epc = epc;
	pcie_hdmac_ptr->num_channels = PCIE_MAX_HDMA_CHANNELS;

	for (i = 0; i < PCIE_MAX_HDMA_CHANNELS / 2; i++) {
		hdma_reg = cfg->hdma_base[i];
		/* Write Channel */
		hdma_reg->pf0_hdma_cap_hdma_en_off_wrch.enable = 0;

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.stop_mask = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.watermark_mask = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.abort_mask = 1;

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.lsie = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.laie = 1;

		hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.mem_type = 1;
		hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.llen = 0;

		/* Read Channel */
		hdma_reg->pf0_hdma_cap_hdma_en_off_rdch.enable = 0;

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.stop_mask = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.watermark_mask = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.abort_mask = 1;

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.lsie = 1;
		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.laie = 1;

		hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.mem_type = 1;
		hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.llen = 0;
	}

	pcie_hdmac_ptr->is_created = true;

	return pcie_hdmac_ptr;
}

static enum pcie_hdmac_chan_status pcie_hdmac_get_state(struct pcie_ep_hdma_controller *hdmac,
														enum pcie_hdma_type type, uint8_t channel)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;

	if (type == PCIE_HDMA_READ) {
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];
		return hdma_reg->pf0_hdma_cap_hdma_status_off_rdch.status;
	} else if (type == PCIE_HDMA_WRITE) {
		hdma_reg = cfg->hdma_base[channel];
		return hdma_reg->pf0_hdma_cap_hdma_status_off_wrch.status;
	} else {
		return CHAN_STAT_RESERVED;
	}
}

static int32_t pcie_hdmac_enable_ll_mode(struct pcie_ep_hdma_controller *hdmac,
										 enum pcie_hdma_type type, uint8_t channel, bool enable)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t val;

	val = enable ? 1 : 0;

	if (type == PCIE_HDMA_WRITE) {
		hdma_reg = cfg->hdma_base[channel];
		hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.llen = val;
	} else if (type == PCIE_HDMA_READ) {
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];
		hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.llen = val;
	} else {
		pcie_dbg_log("%s: Fail to enable linked list mode\n", __func__);
		return RL_ERROR;
	}

	return RL_OK;
}

static void pcie_hdma_unmask_interrupt(struct pcie_ep_hdma_controller *hdmac,
									   enum pcie_hdma_type type, uint8_t channel)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	struct chan_plat_data *chan_data = &hdmac->chan_data[channel];

	switch (type) {
	case PCIE_HDMA_WRITE:
		hdma_reg = cfg->hdma_base[channel];

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.stop_mask = 0;

		if (chan_data->mode == NON_LINKED_LIST_MODE) {
			hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.abort_mask = 0;
		} else {
			hdma_reg->pf0_hdma_cap_hdma_int_setup_off_wrch.watermark_mask = 0;
		}
		break;
	case PCIE_HDMA_READ:
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];

		hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.stop_mask = 0;

		if (chan_data->mode == NON_LINKED_LIST_MODE) {
			hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.abort_mask = 0;
		} else {
			hdma_reg->pf0_hdma_cap_hdma_int_setup_off_rdch.watermark_mask = 0;
		}
		break;
	default:
		break;
	}
}

static int32_t pcie_hdma_non_ll_write_config(struct pcie_ep_hdma_controller *hdmac, uint8_t channel,
											 struct pcie_hdma_block_config *cfg_blk)
{
	if (!cfg_blk) {
		pcie_dbg_log("%s: There is no block_config\n", __func__);
		return RL_ERROR;
	}

	if (channel > HDMA_WRITE_CH15) {
		pcie_dbg_log("%s: Invalid channel number for DMA write\n", __func__);
		return RL_ERROR;
	}

	pcie_hdma_unmask_interrupt(hdmac, PCIE_HDMA_WRITE, channel);

	pcie_hdmac_enable_ll_mode(hdmac, PCIE_HDMA_WRITE, channel, false);

	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;

	hdma_reg = cfg->hdma_base[channel];

	hdma_reg->pf0_hdma_cap_hdma_en_off_wrch.enable = 1;

	hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.mem_type = 1;

	hdma_reg->pf0_hdma_cap_hdma_xfersize_off_wrch.xfersize = cfg_blk->block_size;

	hdma_reg->pf0_hdma_cap_hdma_sar_low_off_wrch.sar_ptr_low =
		LOWER_32_BITS(cfg_blk->source_address);
	hdma_reg->pf0_hdma_cap_hdma_sar_high_off_wrch.sar_ptr_high =
		UPPER_32_BITS(cfg_blk->source_address);

	hdma_reg->pf0_hdma_cap_hdma_dar_low_off_wrch.dar_ptr_low =
		LOWER_32_BITS(cfg_blk->dest_address);
	hdma_reg->pf0_hdma_cap_hdma_dar_high_off_wrch.dar_ptr_high =
		UPPER_32_BITS(cfg_blk->dest_address);

	return RL_OK;
}

static int32_t pcie_hdma_ll_write_config(struct pcie_ep_hdma_controller *hdmac, uint8_t channel,
										 struct pcie_hdma_block_config *cfg_blk)
{
	if (!cfg_blk) {
		pcie_dbg_log("%s: There is no block_config\n", __func__);
		return RL_ERROR;
	}

	if (channel > HDMA_WRITE_CH15) {
		pcie_dbg_log("%s: Invalid channel number for DMA write\n", __func__);
		return RL_ERROR;
	}

	pcie_hdma_unmask_interrupt(hdmac, PCIE_HDMA_WRITE, channel);

	pcie_hdmac_enable_ll_mode(hdmac, PCIE_HDMA_WRITE, channel, true);

	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;

	hdma_reg = cfg->hdma_base[channel];

	hdma_reg->pf0_hdma_cap_hdma_en_off_wrch.enable = 1;

	hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.mem_type = 1;

	/* Customer Cycle State (CCS)
	 * If CB != CCS, that is, end of the transfer list, stop interrupt will be generated.
	 */
	hdma_reg->pf0_hdma_cap_hdma_cycle_off_wrch.cycle_state = 1;

	hdma_reg->pf0_hdma_cap_hdma_llp_low_off_wrch.element_list_ptr_low =
		LOWER_32_BITS(cfg_blk->load_link_pointer);
	hdma_reg->pf0_hdma_cap_hdma_llp_high_off_wrch.element_list_ptr_high =
		UPPER_32_BITS(cfg_blk->load_link_pointer);

	return RL_OK;
}

static int32_t pcie_hdma_non_ll_read_config(struct pcie_ep_hdma_controller *hdmac, uint8_t channel,
											struct pcie_hdma_block_config *cfg_blk)
{
	if (!cfg_blk) {
		pcie_dbg_log("%s: There is no block_config\n", __func__);
		return RL_ERROR;
	}

	if (channel < HDMA_READ_CH0 || channel > HDMA_READ_CH15) {
		pcie_dbg_log("%s: Invalid channel number for DMA read\n", __func__);
		return RL_ERROR;
	}

	pcie_hdma_unmask_interrupt(hdmac, PCIE_HDMA_READ, channel);

	pcie_hdmac_enable_ll_mode(hdmac, PCIE_HDMA_READ, channel, false);

	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;

	hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];

	hdma_reg->pf0_hdma_cap_hdma_en_off_rdch.enable = 1;

	hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.mem_type = 1;

	hdma_reg->pf0_hdma_cap_hdma_xfersize_off_rdch.xfersize = cfg_blk->block_size;

	hdma_reg->pf0_hdma_cap_hdma_sar_low_off_rdch.sar_ptr_low =
		LOWER_32_BITS(cfg_blk->source_address);
	hdma_reg->pf0_hdma_cap_hdma_sar_high_off_rdch.sar_ptr_high =
		UPPER_32_BITS(cfg_blk->source_address);

	hdma_reg->pf0_hdma_cap_hdma_dar_low_off_rdch.dar_ptr_low =
		LOWER_32_BITS(cfg_blk->dest_address);
	hdma_reg->pf0_hdma_cap_hdma_dar_high_off_rdch.dar_ptr_high =
		UPPER_32_BITS(cfg_blk->dest_address);

	return RL_OK;
}

static int32_t pcie_hdma_ll_read_config(struct pcie_ep_hdma_controller *hdmac, uint8_t channel,
										struct pcie_hdma_block_config *cfg_blk)
{
	if (!cfg_blk) {
		pcie_dbg_log("%s: There is no block_config\n", __func__);
		return RL_ERROR;
	}

	if (channel < HDMA_READ_CH0 || channel > HDMA_READ_CH15) {
		pcie_dbg_log("%s: Invalid channel number for DMA read\n", __func__);
		return RL_ERROR;
	}

	pcie_hdma_unmask_interrupt(hdmac, PCIE_HDMA_READ, channel);

	pcie_hdmac_enable_ll_mode(hdmac, PCIE_HDMA_READ, channel, true);

	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;

	hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];

	hdma_reg->pf0_hdma_cap_hdma_en_off_rdch.enable = 1;

	hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.mem_type = 1;

	/* Customer Cycle State (CCS)
	 * If CB != CCS, that is, end of the transfer list, stop interrupt will be generated.
	 */
	hdma_reg->pf0_hdma_cap_hdma_cycle_off_rdch.cycle_state = 1;

	hdma_reg->pf0_hdma_cap_hdma_llp_low_off_rdch.element_list_ptr_low =
		LOWER_32_BITS(cfg_blk->load_link_pointer);
	hdma_reg->pf0_hdma_cap_hdma_llp_high_off_rdch.element_list_ptr_high =
		UPPER_32_BITS(cfg_blk->load_link_pointer);

	return RL_OK;
}

static uint32_t pcie_hdma_get_type(uint32_t channel)
{
	return (channel > HDMA_WRITE_CH15) ? DW_PCIE_READ_HDMA : DW_PCIE_WRITE_HDMA;
}

int32_t pcie_hdma_transfer_start(struct pcie_ep_hdma_controller *hdmac, uint8_t channel)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t direction;

	direction = pcie_hdma_get_type(channel);

	if (pcie_hdmac_get_state(hdmac, direction, channel) == CHAN_STAT_RUNNING) {
		pcie_dbg_log("%s: Channel[%d] has been already running\n", __func__, channel);
		return RL_ERROR;
	}

	switch (direction) {
	case DW_PCIE_WRITE_HDMA:
		if (channel > HDMA_WRITE_CH15)
			return RL_ERROR;

		hdma_reg = cfg->hdma_base[channel];
		hdma_reg->pf0_hdma_cap_hdma_doorbell_off_wrch.db_start = 1;
		break;
	case DW_PCIE_READ_HDMA:
		if (channel < HDMA_READ_CH0 || channel > HDMA_READ_CH15)
			return RL_ERROR;

		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];
		hdma_reg->pf0_hdma_cap_hdma_doorbell_off_rdch.db_start = 1;
		break;
	default:
		pcie_dbg_log("%s: Invalid HDMA direction on start\n", __func__);
		break;
	}

	return RL_OK;
}

int32_t pcie_hdma_transfer_stop(struct pcie_ep_hdma_controller *hdmac, uint8_t channel)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t direction;

	direction = pcie_hdma_get_type(channel);

	if (pcie_hdmac_get_state(hdmac, direction, channel) != CHAN_STAT_RUNNING) {
		pcie_dbg_log("%s: Channel[%d] is not running\n", __func__, channel);
		return RL_ERROR;
	}

	switch (direction) {
	case DW_PCIE_WRITE_HDMA:
		hdma_reg = cfg->hdma_base[channel];
		hdma_reg->pf0_hdma_cap_hdma_doorbell_off_wrch.db_stop = 1;
		break;
	case DW_PCIE_READ_HDMA:
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];
		hdma_reg->pf0_hdma_cap_hdma_doorbell_off_rdch.db_stop = 1;
		break;
	default:
		pcie_dbg_log("%s: Invalid HDMA direction on stop\n", __func__);
		break;
	}

	return RL_OK;
}

int32_t pcie_hdma_select_function(struct pcie_ep_hdma_controller *hdmac, uint32_t channel,
								  bool vf_active, uint32_t func_num)
{
	const struct dw_pcie_config *cfg = hdmac->epc->cfg;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t direction;

	direction = pcie_hdma_get_type(channel);

	switch (direction) {
	case DW_PCIE_WRITE_HDMA:
		hdma_reg = cfg->hdma_base[channel];

		if (vf_active) {
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_wrch.vf_en = 1;
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_wrch.vf = func_num;
		} else {
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_wrch.vf_en = 0;
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_wrch.pf = 0;
		}

		break;
	case DW_PCIE_READ_HDMA:
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];

		if (vf_active) {
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_rdch.vf_en = 1;
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_rdch.vf = func_num;
		} else {
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_rdch.vf_en = 0;
			hdma_reg->pf0_hdma_cap_hdma_func_num_off_rdch.pf = 0;
		}

		break;
	default:
		pcie_dbg_log("%s: Invalid HDMA direction\n", __func__);
		break;
	}

	return RL_OK;
}

int32_t dw_hdma_config(struct pcie_ep_hdma_controller *hdmac, uint32_t channel,
					   struct pcie_hdma_config *hdma_cfg)
{
	enum dw_hdma_chan_attr chan_attr;
	int32_t ret = RL_ERROR;

	hdmac->hdma_cfg = hdma_cfg;

	chan_attr = pcie_hdma_get_channel_attribute(hdmac, channel);

	switch (chan_attr) {
	case NON_LINKED_LIST_HDMA_WRITE:
		ret = pcie_hdma_non_ll_write_config(hdmac, channel, hdma_cfg->head_block);
		break;
	case NON_LINKED_LIST_HDMA_READ:
		ret = pcie_hdma_non_ll_read_config(hdmac, channel, hdma_cfg->head_block);
		break;
	case LINKED_LIST_HDMA_WRITE:
		ret = pcie_hdma_ll_write_config(hdmac, channel, hdma_cfg->head_block);
		break;
	case LINKED_LIST_HDMA_READ:
		ret = pcie_hdma_ll_read_config(hdmac, channel, hdma_cfg->head_block);
		break;
	default:
		pcie_dbg_log("%s: Fail to config due to invalid channel attribute\n", __func__);
		break;
	}

	return ret;
}
