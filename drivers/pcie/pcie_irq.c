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

#include <interrupt.h>

#include "pcie_dw.h"
#include "pcie_dw_hdma.h"
#include "pcie_dw_bar.h"
#include "pcie_doe.h"
#include "pcie_rebelh.h"
#include "pcie_subctrl.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

extern struct pcie_epc dw_pcie_epc;

static void pcie_perstn_fall_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;

	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("perstn_irq_fall_handler called\n");

	if (subctrl_base->irq_pad_perst_n.irq_pad_perst_n_fall) {
		/* TODO: Add work */

		subctrl_base->irq_pad_perst_n.irq_pad_perst_n_fall = 1;
		while (subctrl_base->irq_pad_perst_n.irq_pad_perst_n_fall)
			;
	}
}

static void pcie_perstn_rise_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;

	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("perstn_rise_irq_handler called\n");

	if (subctrl_base->irq_pad_perst_n.irq_pad_perst_n_rise) {
		/* TODO: Add work */

		subctrl_base->irq_pad_perst_n.irq_pad_perst_n_rise = 1;
		while (subctrl_base->irq_pad_perst_n.irq_pad_perst_n_rise)
			;

		pcie_crs_enable(cfg, false);
		pcie_ltssm_enable(cfg, true);
	}
}

static void pcie_irq_link_down_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_link_down_handler called\n");

	if (subctrl_base->irq_reset.irq_smlh_req_rst_not) {
		/* TODO: Add work */

		subctrl_base->irq_reset.irq_smlh_req_rst_not = 1;
		while (subctrl_base->irq_reset.irq_smlh_req_rst_not)
			;
	}
}

static void pcie_irq_flush_done_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_flush_done_handler called\n");

	if (subctrl_base->irq_reset.irq_link_req_rst_not) {
		/* TODO: Add work */

		subctrl_base->irq_reset.irq_link_req_rst_not = 1;
		while (subctrl_base->irq_reset.irq_link_req_rst_not)
			;
	}
}

static void pcie_irq_flr_pf_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_flr_pf_handler called\n");

	if (subctrl_base->irq_reset.irq_flr_pf) {
		/* TODO: Add work */

		subctrl_base->irq_reset.irq_flr_pf = 1;
		while (subctrl_base->irq_reset.irq_flr_pf)
			;
	}
}

static void pcie_irq_flr_vf_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_flr_vf_handler called\n");

	if (subctrl_base->irq_reset.irq_flr_vf) {
		/* TODO: Add work */

		subctrl_base->irq_reset.irq_flr_vf = subctrl_base->irq_reset.irq_flr_vf;
		while (subctrl_base->irq_reset.irq_flr_vf)
			;
	}
}

static void pcie_irq_core_rst_n_assert_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	const struct dw_pcie_drv *data = dw_pcie_epc.drv;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_core_rst_n_assert called\n");

	if (subctrl_base->irq_reset.irq_core_rst_n_assert) {
		/* TODO: Add work */

		subctrl_base->irq_reset.irq_core_rst_n_assert = 1;
		while (subctrl_base->irq_reset.irq_core_rst_n_assert)
			;
	}

	pcie_dbi_ro_wr_enable(cfg, true);

	/* Recovery non-stickty resizable BAR register configuration */
	pcie_set_resizable_bar_size(cfg, BAR0, data->bar_info[BAR0].size);
	pcie_set_resizable_bar_size(cfg, VF_BAR0, data->bar_info[VF_BAR0].size);

	pcie_dbi_ro_wr_enable(cfg, false);

	pcie_crs_enable(cfg, false);
	pcie_ltssm_enable(cfg, true);
}

static void pcie_bw_changed_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_bw_changed\n");

	if (subctrl_base->irq_bw_changed.irq_pm_current_data_rate_changed) {
		pcie_dbg_log("- data rate changed\n");
		/* TODO: Add work */

		subctrl_base->irq_bw_changed.irq_pm_current_data_rate_changed = 1;
		while (subctrl_base->irq_bw_changed.irq_pm_current_data_rate_changed)
			;
	}

	if (subctrl_base->irq_bw_changed.irq_cfg_neg_link_width_changed) {
		pcie_dbg_log("- link width changed\n");
		/* TODO: Add work */

		subctrl_base->irq_bw_changed.irq_cfg_neg_link_width_changed = 1;
		while (subctrl_base->irq_bw_changed.irq_cfg_neg_link_width_changed)
			;
	}
}

static void pcie_rbar_changed_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_rbar_changed\n");

	if (subctrl_base->irq_rbar_changed.rbar_ctrl_update) {
		/* TODO: Add work */

		subctrl_base->irq_rbar_changed.rbar_ctrl_update = 1;
		while (subctrl_base->irq_rbar_changed.rbar_ctrl_update)
			;
	}
}

static void pcie_vf_rbar_changed_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_vf_rbar_changed\n");
	if (subctrl_base->irq_vf_rbar_changed.vf_rbar_ctrl_update) {
		/* TODO: Add work */

		subctrl_base->irq_vf_rbar_changed.vf_rbar_ctrl_update = 1;
		while (subctrl_base->irq_vf_rbar_changed.vf_rbar_ctrl_update)
			;
	}
}

static void pcie_irq_parity_err_handler(void)
{
	pcie_dbg_log("irq_parity_err called\n");

	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	if (subctrl_base->irq_app_parity_err.app_parity_err) {
		pcie_dbg_log("- app_parity_err 0x%x\n", subctrl_base->irq_app_parity_err.app_parity_err);
		/* TODO: Add work */

		subctrl_base->irq_app_parity_err.app_parity_err = subctrl_base->irq_app_parity_err.app_parity_err;
		while (subctrl_base->irq_app_parity_err.app_parity_err)
			;
	}

	if (subctrl_base->irq_ram_parity_err_0.val) {
		pcie_dbg_log("- ram_parity_err_0 0x%x\n", subctrl_base->irq_ram_parity_err_0.val);
		/* TODO: Add work */

		subctrl_base->irq_ram_parity_err_0.val = subctrl_base->irq_ram_parity_err_0.val;
		while (subctrl_base->irq_ram_parity_err_0.val)
			;
	}

	if (subctrl_base->irq_ram_parity_err_1.val) {
		pcie_dbg_log("- ram_parity_err_1 0x%x\n", subctrl_base->irq_ram_parity_err_1.val);
		/* TODO: Add work */

		subctrl_base->irq_ram_parity_err_1.val = subctrl_base->irq_ram_parity_err_1.val;
		while (subctrl_base->irq_ram_parity_err_1.val)
			;
	}

	if (subctrl_base->irq_axi_parity_err.val) {
		pcie_dbg_log("- axi_parity_err\n");
		/* TODO: Add work */

		subctrl_base->irq_axi_parity_err.val = subctrl_base->irq_axi_parity_err.val;
		while (subctrl_base->irq_axi_parity_err.val)
			;
	}
}

static void pcie_irq_internal_err_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_internal_err called\n");

	if (subctrl_base->irq_1.val) {
		/* TODO: Add work */
		pcie_dbg_log("irq_1: 0x%x\n", subctrl_base->irq_1.val);

		subctrl_base->irq_1.val = subctrl_base->irq_1.val;
		while (subctrl_base->irq_1.val)
			;
	} else if (subctrl_base->irq_0_mstr_aclk.mstr_rasdp_err_mode) {
		pcie_dbg_log("mstr_rasdp_err_mode: 0x%x\n", subctrl_base->irq_0_mstr_aclk.mstr_rasdp_err_mode);
		subctrl_base->irq_0_mstr_aclk.mstr_rasdp_err_mode = 1;
		while (subctrl_base->irq_0_mstr_aclk.mstr_rasdp_err_mode)
			;
	} else if (subctrl_base->irq_0_slv_aclk.slv_rasdp_err_mode) {
		pcie_dbg_log("slv_rasdp_err_mode: 0x%x\n", subctrl_base->irq_0_slv_aclk.slv_rasdp_err_mode);
		subctrl_base->irq_0_slv_aclk.slv_rasdp_err_mode = 1;
		while (subctrl_base->irq_0_slv_aclk.slv_rasdp_err_mode)
			;
	}
}

static void pcie_irq_cbuf_err_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	pcie_dbg_log("irq_cbuf_err called\n");

	if (subctrl_base->irq_cbuf_err.cbuf_err) {
		/* TODO: Add work */

		subctrl_base->irq_cbuf_err.cbuf_err = 1;
		while (subctrl_base->irq_cbuf_err.cbuf_err)
			;
	}
}

static void pcie_hdma_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;
	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t val, stat, err;
	uint32_t llp_lo, llp_hi;
	uint32_t chan_num = 0;

	pcie_dbg_log("hdma_irq_handler called\n");

	val = subctrl_base->sfr_edma_int_cm7.edma_int_cm7;
	if (!val) {
		pcie_dbg_log("Nothing to handle for hdma\n", __func__);
		return;
	}
	pcie_dbg_log("%s: edma_int_cm7: 0x%08lx\n", __func__, val);

	int i;

	for (i = 0; i < PCIE_MAX_HDMA_CHANNELS; i++) {
		if ((val & (1 << i))) {
			chan_num = i;
			break;
		}
	}

	if (chan_num < HDMA_READ_CH0) {
		hdma_reg = cfg->hdma_base[chan_num];
		stat = hdma_reg->pf0_hdma_cap_hdma_int_status_off_wrch.val;

		if (stat & HDMA_INT_STATUS_ABORT) {
			err = hdma_reg->pf0_hdma_cap_hdma_int_status_off_wrch.error;
			pcie_dbg_log("%s: Abort - error 0x%lx\n", __func__, err);

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_wrch.abort_clear = 1;
			pcie_dbg_log("%s: Clear abort interrupt\n", __func__);
		}

		if (stat & HDMA_INT_STATUS_WATERMARK) {
			llp_lo = hdma_reg->pf0_hdma_cap_hdma_llp_low_off_wrch.val;
			llp_hi = hdma_reg->pf0_hdma_cap_hdma_llp_high_off_wrch.val;
			pcie_dbg_log("%s: Watermark - LLP: 0x%10llx\n", __func__,
						 (((uint64_t)llp_hi << 32) | llp_lo));

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_wrch.watermark_clear = 1;
			pcie_dbg_log("%s: Clear watermark interrupt\n", __func__);
		}

		if (stat & HDMA_INT_STATUS_STOP) {
			if (hdma_reg->pf0_hdma_cap_hdma_xfersize_off_wrch.xfersize == 0) {
				pcie_dbg_log("%s: Stop - HDMA transfer done\n", __func__);

				if (hdma_reg->pf0_hdma_cap_hdma_control1_off_wrch.llen &&
					hdma_reg->pf0_hdma_cap_hdma_cycle_off_wrch.cycle_state == 1 &&
					hdma_reg->pf0_hdma_cap_hdma_cycle_off_wrch.cycle_bit == 1) {
					pcie_dbg_log("%s: Jump to another list done\n", __func__);
				}
			} else {
				pcie_dbg_log("%s: Stop - SW stop is triggered\n", __func__);
			}

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_wrch.stop_clear = 1;
			pcie_dbg_log("%s: Clear stop interrupt\n", __func__);
		}
	} else {
		chan_num = chan_num - HDMA_READ_CH0;
		hdma_reg = cfg->hdma_base[chan_num];

		stat = hdma_reg->pf0_hdma_cap_hdma_int_status_off_rdch.val;

		if (stat & HDMA_INT_STATUS_ABORT) {
			err = hdma_reg->pf0_hdma_cap_hdma_int_status_off_rdch.error;
			pcie_dbg_log("%s: Abort - error 0x%lx\n", __func__, err);

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_rdch.abort_clear = 1;
			pcie_dbg_log("%s: Clear abort interrupt\n", __func__);
		}

		if (stat & HDMA_INT_STATUS_WATERMARK) {
			llp_lo = hdma_reg->pf0_hdma_cap_hdma_llp_low_off_rdch.val;
			llp_hi = hdma_reg->pf0_hdma_cap_hdma_llp_high_off_rdch.val;
			pcie_dbg_log("%s: Watermark - LLP: 0x%10llx\n", __func__,
						 (((uint64_t)llp_hi << 32) | llp_lo));

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_rdch.watermark_clear = 1;
			pcie_dbg_log("%s: Clear watermark interrupt\n", __func__);
		}

		if (stat & HDMA_INT_STATUS_STOP) {
			if (hdma_reg->pf0_hdma_cap_hdma_xfersize_off_rdch.xfersize == 0) {
				pcie_dbg_log("%s: Stop - HDMA transfer done\n", __func__);

				if (hdma_reg->pf0_hdma_cap_hdma_control1_off_rdch.llen &&
					hdma_reg->pf0_hdma_cap_hdma_cycle_off_rdch.cycle_state == 1 &&
					hdma_reg->pf0_hdma_cap_hdma_cycle_off_rdch.cycle_bit == 1) {
					pcie_dbg_log("%s: Jump to another list done\n", __func__);
				}
			} else {
				pcie_dbg_log("%s: Stop - SW stop is triggered\n", __func__);
			}

			hdma_reg->pf0_hdma_cap_hdma_int_clear_off_rdch.stop_clear = 1;
			pcie_dbg_log("%s: Clear stop interrupt\n", __func__);
		}
	}
}

static void pcie_irq_elbi_rst_handler(void)
{
	pcie_dbg_log("irq_elbi_rst_handler called\n");
}

static void pcie_irq_handler(void)
{
	pcie_dbg_log("irq_handler called\n");
}

static int32_t pcie_doe_error_check(union pcie_doe_error_flag err)
{
	int32_t ret = DOE_ERROR_ABORT;

	if (err.wbox_dw_mismatch) {
		pcie_err_log("DOE WBOX mismatched Error!!!\n");
	} else if (err.rbox_dw_mismatch) {
		pcie_err_log("DOE RBOX mismatched Error!!!\n");
	} else if (err.wbox_fifo_full) {
		pcie_err_log("DOE WBOX FIFO full Error!!!\n");
	} else if (err.rbox_fifo_full) {
		pcie_err_log("DOE RBOX FIFO full Error!!!\n");
	} else if (err.wbox_fifo_empty) {
		pcie_err_log("DOE WBOX FIFO empty Error!!!\n");
	} else if (err.rbox_fifo_empty) {
		pcie_err_log("DOE RBOX FIFO empty Error!!!\n");
	} else if (err.poisoned_error) {
		pcie_err_log("DOE poisoned error occurred!!!\n");
	} else {
		pcie_dbg_log("No DOE errors\n");
		ret = DOE_NO_ERROR;
	}

	return ret;
}

static void pcie_doe_error_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_doe_register *doe_base = cfg->doe_base;
	int32_t err;

	pcie_dbg_log("pcie_doe_error_irq_handler called\n");

	err = pcie_doe_error_check(doe_base->doe_error_flag);
	if (err != DOE_NO_ERROR) {
		pcie_err_log("Clear DOE FIFO & Errors\n");
		doe_base->doe_control.doe_abort = 1;
		while (doe_base->doe_control.doe_abort)
			;
	}
}

static void pcie_doe_go_irq_handler(void)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	volatile struct pcie_doe_register *doe_base = cfg->doe_base;

	pcie_dbg_log("pcie_doe_go_irq_handler called\n");

	pcie_doe_read_wmb(cfg, dw_pcie_epc.drv);

	doe_base->doe_error_flag.irq_clear = 1;
	while (doe_base->doe_error_flag.irq_clear)
		;
}

void pcie_ep_request_irq(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	connect_interrupt_with_handler(PCIE_PAD_PERST_N_FALL_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_perstn_fall_irq_handler, NULL);
	subctrl_base->irq_en_pad_perst_n.irq_en_pad_perst_n_fall = 1;
	connect_interrupt_with_handler(PCIE_PAD_PERST_N_RISE_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_perstn_rise_irq_handler, NULL);
	subctrl_base->irq_en_pad_perst_n.irq_en_pad_perst_n_rise = 1;

	connect_interrupt_with_handler(PCIE_LINK_DOWN_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_link_down_handler, NULL);
	subctrl_base->irq_reset_en.irq_en_smlh_req_rst_not = 1;
	connect_interrupt_with_handler(PCIE_FLUSH_DONE_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_flush_done_handler, NULL);
	subctrl_base->irq_reset_en.irq_en_link_req_rst_not = 1;
	connect_interrupt_with_handler(PCIE_FLR_PF_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_irq_flr_pf_handler, NULL);
	subctrl_base->irq_reset_en.irq_en_flr_pf = 1;
	connect_interrupt_with_handler(PCIE_FLR_VF_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_irq_flr_vf_handler, NULL);
	subctrl_base->irq_reset_en.irq_en_flr_vf = 0xFFFF;
	connect_interrupt_with_handler(PCIE_CORE_RST_N_ASSERT_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_irq_core_rst_n_assert_handler, NULL);
	subctrl_base->irq_reset_en.irq_en_core_rst_n_assert = 1;

	connect_interrupt_with_handler(PCIE_BW_CHANGED_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_bw_changed_irq_handler, NULL);
	subctrl_base->irq_en_bw_changed.irq_en_cfg_neg_link_width_changed = 1;
	subctrl_base->irq_en_bw_changed.irq_en_pm_current_data_rate_changed = 1;
	connect_interrupt_with_handler(PCIE_RBAR_CHANGED_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_rbar_changed_irq_handler, NULL);
	subctrl_base->irq_en_rbar_changed.irq_en_rbar_ctrl_update = 1;
	connect_interrupt_with_handler(PCIE_VF_RBAR_CHANGED_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_EDGE,
								   pcie_vf_rbar_changed_irq_handler, NULL);
	subctrl_base->irq_en_vf_rbar_changed.irq_en_vf_rbar_ctrl_update = 1;

	connect_interrupt_with_handler(PCIE_PARITY_ERRS_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_parity_err_handler, NULL);
	subctrl_base->irq_en_app_parity_err.irq_en_app_parity_err = 0x7;
	subctrl_base->irq_en_ram_parity_err_0.val = 0xFFF6A2D7;
	subctrl_base->irq_en_ram_parity_err_1.val = 0x3FF;
	subctrl_base->irq_en_axi_parity_err.val = 0;
	connect_interrupt_with_handler(PCIE_INTERNAL_ERR_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_internal_err_handler, NULL);
	subctrl_base->irq_1_en.val = 0x7FFF;
	connect_interrupt_with_handler(PCIE_CBUF_ERR_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_cbuf_err_handler, NULL);
	subctrl_base->irq_en_cbuf_err.irq_en_cbuf_err = 1;

	connect_interrupt_with_handler(PCIE_EDMA_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_hdma_irq_handler, NULL);
	subctrl_base->sfr_edma_int_cm7_mask.edma_int_cm7_mask = 0;

	connect_interrupt_with_handler(PCIE_ELBI_RST_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_elbi_rst_handler, NULL);
	subctrl_base->irq_en_elbi_rst.irq_en_elbi_rst = 1;

	subctrl_base->sfr_phy_cfg_29_reg.phy0_sram_init_done_rise_int_en = 0;
	connect_interrupt_with_handler(PCIE_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_irq_handler, NULL);
	subctrl_base->irq_0_en_slv_aclk.irq_en_slv_rasdp_err_mode = 1;
	subctrl_base->irq_0_en_mstr_aclk.irq_en_mstr_rasdp_err_mode = 1;

	connect_interrupt_with_handler(PCIE_DOE_ERROR_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_doe_error_irq_handler, NULL);
	connect_interrupt_with_handler(PCIE_DOE_GO_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pcie_doe_go_irq_handler, NULL);
	/* EP does not need ready IRQ
	 * connect_interrupt_with_handler(PCIE_DOE_READY_IRQ_NUM, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
									pcie_doe_ready_irq_handler, NULL);
	*/

	/*
	 * connect_interrupt_with_handler(PCIE_VDM_INV_RECEIVED, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL,
										NULL, NULL);
	 * connect_interrupt_with_handler(PCIE_VDM_RECEIVED, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL, NULL, NULL);
	 * connect_interrupt_with_handler(PCIE_VDI_STATUS, PCIE_IRQ_PRIO, IRQ_TYPE_LEVEL, NULL, NULL);
	 */
}
