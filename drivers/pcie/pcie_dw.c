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
#include "rl_sizes.h"

#include "pcie_dw.h"
#include "pcie_subctrl.h"
#include "pcie_rebelh.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

void pcie_dbi_ro_wr_enable(const struct dw_pcie_config *cfg, bool en)
{
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	if (en) {
		/* app_dbi_ro_wr_disable = 0 means
		 * MISC_CONTROL_1_OFF.DBI_RO_WR_EN register field is read-write
		 */
		subctrl_base->sfr_app_ctrl_signals.app_dbi_ro_wr_disable = 0;
		__DSB();
		port_base->pf0_port_logic_misc_control_1_off.dbi_ro_wr_en = 1;
	} else {
		/* app_dbi_ro_wr_disable = 1 means
		 * MISC_CONTROL_1_OFF.DBI_RO_WR_EN register field is forced to 0
		 * and is read-only
		 */
		subctrl_base->sfr_app_ctrl_signals.app_dbi_ro_wr_disable = 1;
	}
}

int32_t pcie_link_setup(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;
	uint32_t num_lanes = cfg->num_lanes;
	uint32_t link_cap;

	switch (num_lanes) {
	case 1:
		link_cap = LINK_CAPABLE_X1;
		break;
	case 2:
		link_cap = LINK_CAPABLE_X2;
		break;
	case 4:
		link_cap = LINK_CAPABLE_X4;
		break;
	case 8:
		link_cap = LINK_CAPABLE_X8;
		break;
	case 16:
		link_cap = LINK_CAPABLE_X16;
		break;
	case 32:
		link_cap = LINK_CAPABLE_X32;
		break;
	default:
		pcie_err_log("ERR: Invalid number of lanes\n");
		return RL_ERROR;
	}

	port_base->pf0_port_logic_port_link_ctrl_off.link_capable = link_cap;
	port_base->pf0_port_logic_port_link_ctrl_off.dll_link_en = 1;
#if defined(ZEBU)
	port_base->pf0_port_logic_port_link_ctrl_off.fast_link_mode = 1;
#else
	port_base->pf0_port_logic_port_link_ctrl_off.fast_link_mode = 0;
#endif

	port_base->pf0_port_logic_gen2_ctrl_off.num_of_lanes = num_lanes;

	port_base->pf0_port_logic_gen2_ctrl_off.auto_lane_flip_ctrl_en = 1;
	port_base->pf0_port_logic_gen2_ctrl_off.pre_det_lane = 0;

	return RL_OK;
}

int32_t pcie_set_width(struct pcie_epc *dw_pcie_epc, uint8_t width)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;

	/* Check L0 LTSSM state */
	if (pcie_get_ltssm_state(cfg) != PCIE_LTSSM_STATE_L0) {
		pcie_err_log("Ensure the link is the L0 LTSSM state before set width\n");
		return RL_ERROR;
	}

	/* Change lane width */
	switch (width) {
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
		port_base->pf0_port_logic_multi_lane_control_off.target_link_width = width;
		port_base->pf0_port_logic_multi_lane_control_off.reliability_link_width_change_enable = 0;
		port_base->pf0_port_logic_multi_lane_control_off.direct_link_width_change = 1;
		break;
	case 32: /* REBEL-H support up to 16 lanes */
	default:
		pcie_err_log("lane width %d: invalid value\n", width);
		return RL_ERROR;
	}

	return RL_OK;
}

int32_t pcie_get_width(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	return dbi_base->pf0_pcie_cap_link_control_link_status_reg.pcie_cap_nego_link_width;
}

int32_t pcie_set_speed(struct pcie_epc *dw_pcie_epc, uint8_t speed)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;

	if (speed < GEN1 || speed > GEN5) {
		pcie_err_log("speed %d: not supported\n", speed);
		return RL_ERROR;
	}

	/* TODO: need enable dbi_ro_wr if want to change cap after pcie_ep_init */
	dbi_base->pf0_pcie_cap_link_capabilities_reg.pcie_cap_max_link_speed = speed;

	dbi_base->pf0_pcie_cap_link_control2_link_status2_reg.pcie_cap_target_link_speed = speed;
	port_base->pf0_port_logic_gen2_ctrl_off.direct_speed_change = 0;
	__DSB();
	port_base->pf0_port_logic_gen2_ctrl_off.direct_speed_change = 1;

	return RL_OK;
}

int32_t pcie_get_speed(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	return dbi_base->pf0_pcie_cap_link_control_link_status_reg.pcie_cap_link_speed;
}

void pcie_eq_setup(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;

	port_base->pf0_port_logic_gen3_related_off.gen3_equalization_disable = 0;

#ifndef ZEBU
	/* for Gen3 */
	port_base->pf0_port_logic_gen3_related_off.rxeq_ph01_en = 1;
	port_base->pf0_port_logic_gen3_related_off.rxeq_rgrdless_rxts = 1;
	port_base->pf0_port_logic_gen3_related_off.usp_send_8gt_eq_ts2_disable = 1;

	/* for Gen4 */
	/* RATE_SHADOW_SEL
	 * 00b: RXEQ_RGRDLESS_RXTS is for Gen3, USP_SEND_8GT_EQ_TS2_DISABLE is reserved
	 * 01b: RXEQ_RGRDLESS_RXTS is for Gen4, USP_SEND_8GT_EQ_TS2_DISABLE is for Gen4
	 * 10b: RXEQ_RGRDLESS_RXTS is for Gen5, USP_SEND_8GT_EQ_TS2_DISABLE is for Gen5
	 * 11b: RXEQ_RGRDLESS_RXTS is for Gen6, USP_SEND_8GT_EQ_TS2_DISABLE is for Gen6
	 */
	port_base->pf0_port_logic_gen3_related_off.rate_shadow_sel = 1;
	port_base->pf0_port_logic_gen3_related_off.rxeq_ph01_en = 1;
	port_base->pf0_port_logic_gen3_related_off.rxeq_rgrdless_rxts = 1;
	port_base->pf0_port_logic_gen3_related_off.usp_send_8gt_eq_ts2_disable = 1;

	/* for Gen5 */
	port_base->pf0_port_logic_gen3_related_off.rate_shadow_sel = 2;
	port_base->pf0_port_logic_gen3_related_off.rxeq_ph01_en = 1;
	port_base->pf0_port_logic_gen3_related_off.rxeq_rgrdless_rxts = 1;
	port_base->pf0_port_logic_gen3_related_off.usp_send_8gt_eq_ts2_disable = 1;
#endif /* ZEBU */
}

void pcie_cap_setup(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;

	port_base->pf0_port_logic_aux_clk_freq_off.aux_clk_freq = AUX_CLK_50M;

	/* Set Vendor ID & Device ID */
	dbi_base->pf0_type0_hdr_device_id_vendor_id_reg.pci_type0_vendor_id = REBELH_VENDOR_ID;
	dbi_base->pf0_type0_hdr_device_id_vendor_id_reg.pci_type0_device_id = REBELH_DEVICE_ID;

	/* Set Max Payload Size */
	dbi_base->pf0_pcie_cap_device_control_device_status.pcie_cap_max_payload_size_cs =
		MAX_512B_SIZE;
}

int32_t pcie_find_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t *reg_ptr = (uint32_t *)cfg->dbi_base;
	uint32_t reg = cfg->dbi_base->pf0_type0_hdr_pci_cap_ptr_reg.val;
	uint32_t cap_ptr = PCI_CAP_POINTER(reg);
	uint32_t cap_id;

	while (1) {
		reg = reg_ptr[cap_ptr / SZ_4];
		cap_id = PCI_CAP_ID(reg);

		if (cap_id == cap)
			return cap_ptr;

		cap_ptr = PCI_CAP_NEXT(reg);

		if (cap_ptr == 0) {
			break;
		}
	}

	return 0;
}

bool pcie_disable_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t *reg_ptr = (uint32_t *)cfg->dbi_base;
	uint32_t reg = cfg->dbi_base->pf0_type0_hdr_pci_cap_ptr_reg.val;
	uint32_t cap_ptr, cap_id;
	uint32_t next_cap_ptr  = PCI_CAP_POINTER(reg);
	uint32_t next_reg;

	next_reg = reg_ptr[next_cap_ptr / SZ_4];
	cap_id = PCI_CAP_ID(next_reg);

	if (cap_id == cap) {
		pcie_dbi_ro_wr_enable(cfg, true);
		cfg->dbi_base->pf0_type0_hdr_pci_cap_ptr_reg.cap_pointer = PCI_CAP_NEXT(next_reg);
		pcie_dbi_ro_wr_enable(cfg, false);
		return true;
	}

	while (1) {
		reg = next_reg;
		cap_ptr = next_cap_ptr;

		next_cap_ptr = PCI_CAP_NEXT(reg);
		if (next_cap_ptr == 0) {
			break;
		}

		next_reg = reg_ptr[next_cap_ptr / SZ_4];
		cap_id = PCI_CAP_ID(next_reg);

		if (cap_id == cap) {
			pcie_dbi_ro_wr_enable(cfg, true);
			reg_ptr[cap_ptr / SZ_4] &= ~PCI_CAP_NEXT_MASK;
			reg_ptr[cap_ptr / SZ_4] |= (next_reg & PCI_CAP_NEXT_MASK);
			pcie_dbi_ro_wr_enable(cfg, false);
			return true;
		}
	}

	return false;
}

int32_t pcie_find_ext_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t *reg_ptr = (uint32_t *)cfg->dbi_base;

	uint32_t reg = reg_ptr[PCI_CFG_SPACE_SIZE / SZ_4];
	uint32_t cap_id, cap_ptr = 0;

	while (1) {
		cap_id = PCI_EXT_CAP_ID(reg);
		if (cap_id == cap)
			return cap_ptr;

		cap_ptr = PCI_EXT_CAP_NEXT(reg);
		if (cap_ptr == 0) {
			break;
		}

		reg = reg_ptr[cap_ptr / SZ_4];
	}

	return 0;
}

bool pcie_disable_ext_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t *reg_ptr = (uint32_t *)cfg->dbi_base;

	uint32_t cap_ptr = PCI_CFG_SPACE_SIZE;
	uint32_t reg = reg_ptr[cap_ptr / SZ_4];
	uint32_t cap_id = PCI_EXT_CAP_ID(reg);
	uint32_t next_cap_ptr, next_reg;

	/* Limitation: Cannot disable first extended capability */
	if (cap_id == cap)
		return false;

	while (1) {
		next_cap_ptr = PCI_EXT_CAP_NEXT(reg);
		if (next_cap_ptr == 0) {
			break;
		}

		next_reg = reg_ptr[next_cap_ptr / SZ_4];
		cap_id = PCI_EXT_CAP_ID(next_reg);
		if (cap_id == cap) {
			pcie_dbi_ro_wr_enable(cfg, true);
			reg_ptr[cap_ptr / SZ_4] &= ~PCI_EXT_CAP_NEXT_MASK;
			reg_ptr[cap_ptr / SZ_4] |= (next_reg & PCI_EXT_CAP_NEXT_MASK);
			pcie_dbi_ro_wr_enable(cfg, false);
			return true;
		}

		reg = next_reg;
		cap_ptr = next_cap_ptr;
	}

	return false;
}

int32_t pcie_rasdp_enable_error_mode(struct pcie_epc *dw_pcie_epc, bool en)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (en) {
		dbi_base->pf0_vsecras_cap_rasdp_error_mode_en_off.error_mode_en = 1;
	} else {
		dbi_base->pf0_vsecras_cap_rasdp_error_mode_en_off.error_mode_en = 0;
	}

	return RL_OK;
}

int32_t pcie_rasdp_clear_error_mode(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_vsecras_cap_rasdp_error_mode_clear_off.error_mode_clear = 1;

	return RL_OK;
}

int32_t pcie_rasdp_enable_error_injection(struct pcie_epc *dw_pcie_epc, bool en, uint8_t loc,
										  uint8_t count, uint8_t type)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (en) {
		dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_en = 1;
		dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_type = type;
		dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_count = count;
		dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_loc = loc;

		pcie_dbg_log("Enable Error Injection\n");
		pcie_dbg_log("ERROR_INJ_LOC: %d\n", dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_loc);
		if (dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_count) {
			pcie_dbg_log("ERROR_INJ_COUNT: %d\n", dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_count);
		} else {
			pcie_dbg_log("Errors are inserted in very TLP until clear ERROR_INJ_EN\n");
		}
		pcie_dbg_log("ERROR_INJ_TYPE: %d-bit\n", dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_type);
	} else {
		dbi_base->pf0_vsecras_cap_rasdp_error_inj_ctrl_off.error_inj_en = 0;

		pcie_dbg_log("Disable Error Injection\n");
	}

	return RL_OK;
}

int32_t pcie_rasdp_get_count(struct pcie_epc *dw_pcie_epc, bool corr, uint8_t sel)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	int cnt = 0;

	if (corr) {
		dbi_base->pf0_vsecras_cap_rasdp_corr_counter_ctrl_off.corr_counter_selection = sel;
		cnt = dbi_base->pf0_vsecras_cap_rasdp_corr_count_report_off.corr_counter;
	} else {
		dbi_base->pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off.uncorr_counter_selection = sel;
		cnt = dbi_base->pf0_vsecras_cap_rasdp_uncorr_count_report_off.uncorr_counter;
	}

	return cnt;
}

uint8_t pcie_rasdp_get_region(struct pcie_epc *dw_pcie_epc, bool corr)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	uint8_t region;

	if (corr)
		region = dbi_base->pf0_vsecras_cap_rasdp_corr_count_report_off.corr_counter_selected_region;
	else
		region = dbi_base->pf0_vsecras_cap_rasdp_uncorr_count_report_off.uncorr_counter_selected_region;

	return region;
}

int32_t pcie_rasdp_select_region(struct pcie_epc *dw_pcie_epc, bool corr, uint8_t region)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (corr) {
		dbi_base->pf0_vsecras_cap_rasdp_corr_counter_ctrl_off.corr_counter_selection_region = region;
		pcie_dbg_log("Set Corrected error counter selection region: %d\n",
					 dbi_base->pf0_vsecras_cap_rasdp_corr_counter_ctrl_off.corr_counter_selection_region);
	} else {
		dbi_base->pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off.uncorr_counter_selection_region = region;
		pcie_dbg_log("Set Uncorrected error counter selection region: %d\n",
					 dbi_base->pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off.uncorr_counter_selection_region);
	}

	return RL_OK;
}

int32_t pcie_rasdp_clear_count(struct pcie_epc *dw_pcie_epc, bool corr)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (corr)
		dbi_base->pf0_vsecras_cap_rasdp_corr_counter_ctrl_off.corr_clear_counters = 1;
	else
		dbi_base->pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off.uncorr_clear_counters = 1;

	return 0;
}

int32_t pcie_rasdes_get_tba_info(struct pcie_epc *dw_pcie_epc, uint8_t *report, uint8_t *duration)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	*report = dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_report_select;
	*duration = dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_duration_select;

	return RL_OK;
}

int32_t pcie_rasdes_start_tba(struct pcie_epc *dw_pcie_epc, uint8_t report, uint8_t duration)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_report_select = report;
	dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_duration_select = duration;
	dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.timer_start = 1;

	pcie_dbg_log("Start Time Based Analysis - report type: 0x%x duration type:0x%x\n",
				 dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_report_select,
				 dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.time_based_duration_select);

	return RL_OK;
}

int32_t pcie_rasdes_stop_tba(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_time_based_analysis_control_reg.timer_start = 0;

	pcie_dbg_log("Stop Time Based Analysis");

	return RL_OK;
}

uint64_t pcie_rasdes_get_tba_data(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	uint64_t data =
		((uint64_t)dbi_base->pf0_ras_des_cap_time_based_analysis_data_63_32_reg.time_based_analysis_data_63_32 << 32)
		+ dbi_base->pf0_ras_des_cap_time_based_analysis_data_reg.time_based_analysis_data;

	return data;
}

int32_t pcie_rasdes_select_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t group, uint8_t event, uint8_t lane)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	uint16_t val = ((uint16_t)group << 8) | event;

	dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_event_select = val;
	dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_lane_select = lane;

	return RL_OK;
}

int32_t pcie_rasdes_get_selected_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t *group, uint8_t *event, uint8_t *lane)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	*group = RASDES_ECNT_GROUP(dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_event_select);
	*event = RASDES_ECNT_EVENT(dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_event_select);
	*lane = dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_lane_select;

	return RL_OK;
}

int32_t pcie_rasdes_get_ecnt_data(struct pcie_epc *dw_pcie_epc, uint32_t *data)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	*data = dbi_base->pf0_ras_des_cap_event_counter_data_reg.event_counter_data;

	return RL_OK;
}

int32_t pcie_rasdes_enable_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t en)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_enable = en;

	return RL_OK;
}

int32_t pcie_rasdes_clear_ecnt(struct pcie_epc *dw_pcie_epc, bool all)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (all)
		dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_clear = ECNT_ALL_CLEAR;
	else
		dbi_base->pf0_ras_des_cap_event_counter_control_reg.event_counter_clear = ECNT_PER_CLEAR;

	return RL_OK;
}

int32_t pcie_rasdes_sd_l1_lane_sel(struct pcie_epc *dw_pcie_epc, int8_t lane_num)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_sd_status_l1lane_reg.lane_select = lane_num;

	return RL_OK;
}

int32_t pcie_rasdes_get_sd_status(struct pcie_epc *dw_pcie_epc, int32_t sel, uint32_t *data)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	switch (sel) {
	case SD_L1_PER_LANE:
		*data = dbi_base->pf0_ras_des_cap_sd_status_l1lane_reg.val;
		break;
	case SD_L1_LTSSM:
		*data = dbi_base->pf0_ras_des_cap_sd_status_l1ltssm_reg.val;
		break;
	case SD_PM:
		*data = dbi_base->pf0_ras_des_cap_sd_status_pm_reg.val;
		break;
	case SD_L2:
		*data = dbi_base->pf0_ras_des_cap_sd_status_l2_reg.val;
		break;
	case SD_L3_FC:
		*data = dbi_base->pf0_ras_des_cap_sd_status_l3fc_reg.val;
		break;
	case SD_L3:
		*data = dbi_base->pf0_ras_des_cap_sd_status_l3_reg.val;
		break;
	default:
		return RL_ERROR;
	}

	return RL_OK;
}

int32_t pcie_rasdes_sd_eq_rate_sel(struct pcie_epc *dw_pcie_epc, int8_t eq_rate_sel)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_sd_eq_control1_reg.eq_rate_sel = eq_rate_sel;

	return RL_OK;
}

int32_t pcie_rasdes_sd_eq_lane_sel(struct pcie_epc *dw_pcie_epc, int8_t eq_lane_sel)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_ras_des_cap_sd_eq_control1_reg.eq_lane_sel = eq_lane_sel;

	return RL_OK;
}

int32_t pcie_rasdes_get_sd_eq_status(struct pcie_epc *dw_pcie_epc, int32_t sel, uint32_t *data)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	switch (sel) {
	case SD_EQ_STATUS1:
		*data = dbi_base->pf0_ras_des_cap_sd_eq_status1_reg.val;
		break;
	case SD_EQ_STATUS2:
		*data = dbi_base->pf0_ras_des_cap_sd_eq_status2_reg.val;
		break;
	case SD_EQ_STATUS3:
		*data = dbi_base->pf0_ras_des_cap_sd_eq_status3_reg.val;
		break;
	default:
		return RL_ERROR;
	}

	return RL_OK;
}

void pcie_lane_margin_setup(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	port_base->pf0_port_logic_gen4_lane_margining_1_off.gen4_margining_num_timing_steps =
		PCIE_GEN4_MARGINING_NUM_TIMING_STEPS;
	port_base->pf0_port_logic_gen4_lane_margining_1_off.gen4_margining_num_voltage_steps =
		PCIE_GEN4_MARGINING_NUM_VOLTAGE_STEPS;
	port_base->pf0_port_logic_gen4_lane_margining_1_off.gen4_margining_max_timing_offset =
		PCIE_GEN4_MARGINING_MAX_TIMING_OFFSET;
	port_base->pf0_port_logic_gen4_lane_margining_1_off.gen4_margining_max_voltage_offset =
		PCIE_GEN4_MARGINING_MAX_VOLTAGE_OFFSET;
	port_base->pf0_port_logic_gen5_lane_margining_1_off.gen5_margining_num_timing_steps =
		PCIE_GEN5_MARGINING_NUM_TIMING_STEPS;
	port_base->pf0_port_logic_gen5_lane_margining_1_off.gen5_margining_num_voltage_steps =
		PCIE_GEN5_MARGINING_NUM_VOLTAGE_STEPS;
	port_base->pf0_port_logic_gen5_lane_margining_1_off.gen5_margining_max_timing_offset =
		PCIE_GEN5_MARGINING_MAX_TIMING_OFFSET;
	port_base->pf0_port_logic_gen5_lane_margining_1_off.gen5_margining_max_voltage_offset =
		PCIE_GEN5_MARGINING_MAX_VOLTAGE_OFFSET;

	subctrl_base->sfr_app_margining_ready.app_margining_ready = 1;
}
