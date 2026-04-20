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

#pragma once

union pcie_subctrl_irq_0 {
	struct {
		uint32_t trgt_cpl_timeout:1; /* [0:0] */
		uint32_t ven_msg_grant:1; /* [1:1] */
		uint32_t ven_msi_grant:1; /* [2:2] */
		uint32_t cfg_aer_rc_err_msi:1; /* [3:3] */
		uint32_t cfg_bw_mgt_msi:1; /* [4:4] */
		uint32_t cfg_link_auto_bw_msi:1; /* [5:5] */
		uint32_t cfg_pme_msi:1; /* [6:6] */
		uint32_t cfg_sys_err_rc:1; /* [7:7] */
		uint32_t rsvd0:1; /* [8:8] */
		uint32_t rx_beacon_int:1; /* [9:9] */
		uint32_t hp_msi:1; /* [10:10] */
		uint32_t hp_pme:1; /* [11:11] */
		uint32_t radm_correctable_err:1; /* [12:12] */
		uint32_t radm_fatal_err:1; /* [13:13] */
		uint32_t radm_inta_asserted:1; /* [14:14] */
		uint32_t radm_inta_deasserted:1; /* [15:15] */
		uint32_t radm_intb_asserted:1; /* [16:16] */
		uint32_t radm_intb_deasserted:1; /* [17:17] */
		uint32_t radm_intc_asserted:1; /* [18:18] */
		uint32_t radm_intc_deasserted:1; /* [19:19] */
		uint32_t radm_intd_asserted:1; /* [20:20] */
		uint32_t radm_intd_deasserted:1; /* [21:21] */
		uint32_t radm_qoverflow:1; /* [22:22] */
		uint32_t rsvd3:1; /* [23:23] */
		uint32_t radm_msg_ltr:1; /* [24:24] */
		uint32_t rsvd2:1; /* [25:25] */
		uint32_t radm_msg_unlock:1; /* [26:26] */
		uint32_t radm_nonfatal_err:1; /* [27:27] */
		uint32_t radm_pm_pme:1; /* [28:28] */
		uint32_t radm_pm_to_ack:1; /* [29:29] */
		uint32_t radm_pm_turnoff:1; /* [30:30] */
		uint32_t radm_vendor_msg:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_1 {
	struct {
		uint32_t cfg_bad_dllp_err_sts:1; /* [0:0] */
		uint32_t cfg_bad_tlp_err_sts:1; /* [1:1] */
		uint32_t cfg_corrected_internal_err_sts:1; /* [2:2] */
		uint32_t cfg_dl_protocol_err_sts:1; /* [3:3] */
		uint32_t cfg_ecrc_err_sts:1; /* [4:4] */
		uint32_t cfg_fc_protocol_err_sts:1; /* [5:5] */
		uint32_t cfg_mlf_tlp_err_sts:1; /* [6:6] */
		uint32_t cfg_rcvr_err_sts:1; /* [7:7] */
		uint32_t cfg_rcvr_overflow_err_sts:1; /* [8:8] */
		uint32_t cfg_replay_number_rollover_err_sts:1; /* [9:9] */
		uint32_t cfg_replay_timer_timeout_err_sts:1; /* [10:10] */
		uint32_t cfg_surprise_down_er_sts:1; /* [11:11] */
		uint32_t cfg_uncor_internal_err_sts:1; /* [12:12] */
		uint32_t cfg_advisory_nf_sts:1; /* [13:13] */
		uint32_t cfg_hdr_log_overflow_sts:1; /* [14:14] */
		uint32_t rsvd0:17; /* [31:15] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_2 {
	struct {
		uint32_t wake:1; /* [0:0] */
		uint32_t perst_n_rise:1; /* [1:1] */
		uint32_t cfg_aer_rc_err_int:1; /* [2:2] */
		uint32_t cfg_bus_master_en:1; /* [3:3] */
		uint32_t cfg_link_eq_req_int:1; /* [4:4] */
		uint32_t cfg_pme_int:1; /* [5:5] */
		uint32_t rtlh_rfc_upd_0:1; /* [6:6] */
		uint32_t rtlh_rfc_upd_1:1; /* [7:7] */
		uint32_t rtlh_rfc_upd_2:1; /* [8:8] */
		uint32_t rtlh_rfc_upd_3:1; /* [9:9] */
		uint32_t rtlh_rfc_upd_4:1; /* [10:10] */
		uint32_t rtlh_rfc_upd_5:1; /* [11:11] */
		uint32_t rtlh_rfc_upd_6:1; /* [12:12] */
		uint32_t rtlh_rfc_upd_7:1; /* [13:13] */
		uint32_t cfg_bw_mgt_int:1; /* [14:14] */
		uint32_t cfg_link_auto_bw_int:1; /* [15:15] */
		uint32_t hp_int:1; /* [16:16] */
		uint32_t rsvd2:1; /* [17:17] */
		uint32_t pm_linkst_in_l0s:1; /* [18:18] */
		uint32_t pm_linkst_in_l1:1; /* [19:19] */
		uint32_t pm_linkst_in_l1sub_0:1; /* [20:20] */
		uint32_t pm_linkst_in_l2:1; /* [21:21] */
		uint32_t pm_linkst_l2_exit:1; /* [22:22] */
		uint32_t pm_xtlh_block_tlp:1; /* [23:23] */
		uint32_t radm_cpl_timeout:1; /* [24:24] */
		uint32_t radm_q_not_empty:1; /* [25:25] */
		uint32_t rdlh_link_up_0:1; /* [26:26] */
		uint32_t smlh_link_up:1; /* [27:27] */
		uint32_t compare_end_checker_g1:1; /* [28:28] */
		uint32_t compare_end_checker_g2:1; /* [29:29] */
		uint32_t compare_end_checker_g3:1; /* [30:30] */
		uint32_t compare_end_checker_g4:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_3 {
	struct {
		uint32_t perst_n_fall:1; /* [0:0] */
		uint32_t pm_linkst_in_l1sub_1:1; /* [1:1] */
		uint32_t rdlh_link_up_1:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_en {
	struct {
		uint32_t irq_en_trgt_cpl_timeout:1; /* [0:0] */
		uint32_t irq_en_ven_msg_grant:1; /* [1:1] */
		uint32_t irq_en_ven_msi_grant:1; /* [2:2] */
		uint32_t irq_en_cfg_aer_rc_err_msi:1; /* [3:3] */
		uint32_t irq_en_cfg_bw_mgt_msi:1; /* [4:4] */
		uint32_t irq_en_cfg_link_auto_bw_msi:1; /* [5:5] */
		uint32_t irq_en_cfg_pme_msi:1; /* [6:6] */
		uint32_t irq_en_cfg_sys_err_rc:1; /* [7:7] */
		uint32_t rsvd0:1; /* [8:8] */
		uint32_t irq_en_rx_beacon_int:1; /* [9:9] */
		uint32_t irq_en_hp_msi:1; /* [10:10] */
		uint32_t irq_en_hp_pme:1; /* [11:11] */
		uint32_t irq_en_radm_correctable_err:1; /* [12:12] */
		uint32_t irq_en_radm_fatal_err:1; /* [13:13] */
		uint32_t irq_en_radm_inta_asserted:1; /* [14:14] */
		uint32_t irq_en_radm_inta_deasserted:1; /* [15:15] */
		uint32_t irq_en_radm_intb_asserted:1; /* [16:16] */
		uint32_t irq_en_radm_intb_deasserted:1; /* [17:17] */
		uint32_t irq_en_radm_intc_asserted:1; /* [18:18] */
		uint32_t irq_en_radm_intc_deasserted:1; /* [19:19] */
		uint32_t irq_en_radm_intd_asserted:1; /* [20:20] */
		uint32_t irq_en_radm_intd_deasserted:1; /* [21:21] */
		uint32_t irq_en_radm_qoverflow:1; /* [22:22] */
		uint32_t rsvd3:1; /* [23:23] */
		uint32_t irq_en_radm_msg_ltr:1; /* [24:24] */
		uint32_t rsvd2:1; /* [25:25] */
		uint32_t irq_en_radm_msg_unlock:1; /* [26:26] */
		uint32_t irq_en_radm_nonfatal_err:1; /* [27:27] */
		uint32_t irq_en_radm_pm_pme:1; /* [28:28] */
		uint32_t irq_en_radm_pm_to_ack:1; /* [29:29] */
		uint32_t irq_en_radm_pm_turnoff:1; /* [30:30] */
		uint32_t irq_en_radm_vendor_msg:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_1_en {
	struct {
		uint32_t irq_en_cfg_bad_dllp_err_sts:1; /* [0:0] */
		uint32_t irq_en_cfg_bad_tlp_err_sts:1; /* [1:1] */
		uint32_t irq_en_cfg_corrected_internal_err_sts:1; /* [2:2] */
		uint32_t irq_en_cfg_dl_protocol_err_sts:1; /* [3:3] */
		uint32_t irq_en_cfg_ecrc_err_sts:1; /* [4:4] */
		uint32_t irq_en_cfg_fc_protocol_err_sts:1; /* [5:5] */
		uint32_t irq_en_cfg_mlf_tlp_err_sts:1; /* [6:6] */
		uint32_t irq_en_cfg_rcvr_err_sts:1; /* [7:7] */
		uint32_t irq_en_cfg_rcvr_overflow_err_sts:1; /* [8:8] */
		uint32_t irq_en_cfg_replay_number_rollover_err_sts:1; /* [9:9] */
		uint32_t irq_en_cfg_replay_timer_timeout_err_sts:1; /* [10:10] */
		uint32_t irq_en_cfg_surprise_down_er_sts:1; /* [11:11] */
		uint32_t irq_en_cfg_uncor_internal_err_sts:1; /* [12:12] */
		uint32_t irq_en_cfg_advisory_nf_sts:1; /* [13:13] */
		uint32_t irq_en_cfg_hdr_log_overflow_sts:1; /* [14:14] */
		uint32_t rsvd0:17; /* [31:15] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_2_en {
	struct {
		uint32_t irq_en_wake:1; /* [0:0] */
		uint32_t irq_en_perst_n_rise:1; /* [1:1] */
		uint32_t irq_en_cfg_aer_rc_err_int:1; /* [2:2] */
		uint32_t irq_en_cfg_bus_master_en:1; /* [3:3] */
		uint32_t irq_en_cfg_link_eq_req_int:1; /* [4:4] */
		uint32_t irq_en_cfg_pme_int:1; /* [5:5] */
		uint32_t irq_en_rtlh_rfc_upd_0:1; /* [6:6] */
		uint32_t irq_en_rtlh_rfc_upd_1:1; /* [7:7] */
		uint32_t irq_en_rtlh_rfc_upd_2:1; /* [8:8] */
		uint32_t irq_en_rtlh_rfc_upd_3:1; /* [9:9] */
		uint32_t irq_en_rtlh_rfc_upd_4:1; /* [10:10] */
		uint32_t irq_en_rtlh_rfc_upd_5:1; /* [11:11] */
		uint32_t irq_en_rtlh_rfc_upd_6:1; /* [12:12] */
		uint32_t irq_en_rtlh_rfc_upd_7:1; /* [13:13] */
		uint32_t irq_en_cfg_bw_mgt_int:1; /* [14:14] */
		uint32_t irq_en_cfg_link_auto_bw_int:1; /* [15:15] */
		uint32_t irq_en_hp_int:1; /* [16:16] */
		uint32_t rsvd2:1; /* [17:17] */
		uint32_t irq_en_pm_linkst_in_l0s:1; /* [18:18] */
		uint32_t irq_en_pm_linkst_in_l1:1; /* [19:19] */
		uint32_t irq_en_pm_linkst_in_l1sub_0:1; /* [20:20] */
		uint32_t irq_en_pm_linkst_in_l2:1; /* [21:21] */
		uint32_t irq_en_pm_linkst_l2_exit:1; /* [22:22] */
		uint32_t irq_en_pm_xtlh_block_tlp:1; /* [23:23] */
		uint32_t irq_en_radm_cpl_timeout:1; /* [24:24] */
		uint32_t irq_en_radm_q_not_empty:1; /* [25:25] */
		uint32_t irq_en_rdlh_link_up_0:1; /* [26:26] */
		uint32_t irq_en_smlh_link_up:1; /* [27:27] */
		uint32_t irq_en_compare_end_checker_g1:1; /* [28:28] */
		uint32_t irq_en_compare_end_checker_g2:1; /* [29:29] */
		uint32_t irq_en_compare_end_checker_g3:1; /* [30:30] */
		uint32_t irq_en_compare_end_checker_g4:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_3_en {
	struct {
		uint32_t irq_en_perst_n_fall:1; /* [0:0] */
		uint32_t irq_en_pm_linkst_in_l1sub_1:1; /* [1:1] */
		uint32_t irq_en_rdlh_link_up_1:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_clk_pm_en {
	struct {
		uint32_t app_clk_pm_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_clk_req_n {
	struct {
		uint32_t app_clk_req_n:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_err_advisory {
	struct {
		uint32_t app_err_advisory:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_err_bus {
	struct {
		uint32_t app_err_bus:15; /* [14:0] */
		uint32_t rsvd0:17; /* [31:15] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_err_func_num {
	struct {
		uint32_t app_err_func_num:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_hdr_log_31_0 {
	struct {
		uint32_t app_hdr_log_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_hdr_log_63_32 {
	struct {
		uint32_t app_hdr_log_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_hdr_log_95_64 {
	struct {
		uint32_t app_hdr_log_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_hdr_log_127_96 {
	struct {
		uint32_t app_hdr_log_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_hdr_valid {
	struct {
		uint32_t app_hdr_valid:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_usp_eq_redo_executed_int {
	struct {
		uint32_t usp_eq_redo_executed_int:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_l12_mem_pwr_shutoff_ovrd {
	struct {
		uint32_t l12_mem_pwr_shutoff_ovrd_sel:1; /* [0:0] */
		uint32_t l12_mem_pwr_shutoff_ovrd_val:1; /* [1:1] */
		uint32_t aggressive_l1_2_mode:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ltssm_enable {
	struct {
		uint32_t app_ltssm_enable:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_obff_cpu_active_msg_req {
	struct {
		uint32_t app_obff_cpu_active_msg_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_obff_idle_msg_req {
	struct {
		uint32_t app_obff_idle_msg_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_obff_obff_msg_req {
	struct {
		uint32_t app_obff_obff_msg_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ras_des_sd_hold_ltssm {
	struct {
		uint32_t app_ras_des_sd_hold_ltssm:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ready_entr_l23 {
	struct {
		uint32_t app_ready_entr_l23:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_req_exit_l1 {
	struct {
		uint32_t app_req_exit_l1:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_axi_s_araddr_sel {
	struct {
		uint32_t cfg_axi_s_araddr_sel; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_xfer_pending {
	struct {
		uint32_t app_xfer_pending:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_eml_control {
	struct {
		uint32_t cfg_eml_control:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pcs_ext_pclk_req {
	struct {
		uint32_t pcs_ext_pclk_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_reset_ovrd {
	struct {
		uint32_t phy_reset_ovrd:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_diag_ctrl_bus {
	struct {
		uint32_t diag_ctrl_bus:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_axi_s_araddr {
	struct {
		uint32_t cfg_axi_s_araddr; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_axi_s_awaddr {
	struct {
		uint32_t cfg_axi_s_awaddr; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_atten_button_pressed {
	struct {
		uint32_t sys_atten_button_pressed:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_aux_pwr_det {
	struct {
		uint32_t sys_aux_pwr_det:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_cmd_cpled_int {
	struct {
		uint32_t sys_cmd_cpled_int:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_eml_interlock_engaged {
	struct {
		uint32_t sys_eml_interlock_engaged:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_int {
	struct {
		uint32_t sys_int:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_mrl_sensor_chged {
	struct {
		uint32_t sys_mrl_sensor_chged:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_mrl_sensor_state {
	struct {
		uint32_t sys_mrl_sensor_state:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_vfunc_num {
	struct {
		uint32_t ven_msg_vfunc_num:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_vfunc_active {
	struct {
		uint32_t ven_msg_vfunc_active:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sys_pwr_fault_det {
	struct {
		uint32_t sys_pwr_fault_det:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_attr {
	struct {
		uint32_t ven_msg_attr:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_code {
	struct {
		uint32_t ven_msg_code:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_data_31_0 {
	struct {
		uint32_t ven_msg_data_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_data_63_32 {
	struct {
		uint32_t ven_msg_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_ep {
	struct {
		uint32_t ven_msg_ep:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_fmt {
	struct {
		uint32_t ven_msg_fmt:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_func_num {
	struct {
		uint32_t ven_msg_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_len {
	struct {
		uint32_t ven_msg_len:10; /* [9:0] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_req {
	struct {
		uint32_t ven_msg_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_tag {
	struct {
		uint32_t ven_msg_tag:10; /* [9:0] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_tc {
	struct {
		uint32_t ven_msg_tc:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_td {
	struct {
		uint32_t ven_msg_td:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msg_type {
	struct {
		uint32_t ven_msg_type:5; /* [4:0] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_axi_s_awaddr_sel {
	struct {
		uint32_t cfg_axi_s_awaddr_sel; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ven_msi_reg {
	struct {
		uint32_t ven_msi_func_num:1; /* [0:0] */
		uint32_t ven_msi_tc:3; /* [3:1] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_rtune_sts {
	struct {
		uint32_t phy_rtune_sts:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_rtune_req {
	struct {
		uint32_t phy_rtune_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_up_rst_n_ovrd {
	struct {
		uint32_t power_up_rst_n_ovrd:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_init_rst {
	struct {
		uint32_t app_init_rst:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ras_des_tba_ctrl {
	struct {
		uint32_t app_ras_des_tba_ctrl:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_req_entr_l1 {
	struct {
		uint32_t app_req_entr_l1:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_unlock_msg {
	struct {
		uint32_t app_unlock_msg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_apps_pm_xmt_pme {
	struct {
		uint32_t apps_pm_xmt_pme:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_apps_pm_xmt_turnoff {
	struct {
		uint32_t apps_pm_xmt_turnoff:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_outband_pwrup_cmd {
	struct {
		uint32_t outband_pwrup_cmd:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ltr_latency {
	struct {
		uint32_t app_ltr_latency; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_aux_pm_en {
	struct {
		uint32_t aux_pm_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_brdg_dbi_xfer_pending {
	struct {
		uint32_t brdg_dbi_xfer_pending:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_brdg_slv_xfer_pending {
	struct {
		uint32_t brdg_slv_xfer_pending:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ltr_msg_func_num {
	struct {
		uint32_t app_ltr_msg_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ltr_msg_latency {
	struct {
		uint32_t app_ltr_msg_latency; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ltr_msg_req {
	struct {
		uint32_t app_ltr_msg_req:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_ltr_max_latency {
	struct {
		uint32_t cfg_ltr_max_latency; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_disable_ltr_clr_msg {
	struct {
		uint32_t cfg_disable_ltr_clr_msg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_tx_lane_flip_en {
	struct {
		uint32_t tx_lane_flip_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rx_lane_flip_en {
	struct {
		uint32_t rx_lane_flip_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_margining_ready {
	struct {
		uint32_t app_margining_ready:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_margining_software_ready {
	struct {
		uint32_t app_margining_software_ready:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_sris_mode {
	struct {
		uint32_t app_sris_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_req_retry_en {
	struct {
		uint32_t app_req_retry_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_pf_req_retry_en {
	struct {
		uint32_t app_pf_req_retry_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_vf_req_retry_en {
	struct {
		uint32_t app_vf_req_retry_en:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbg_sel_group {
	struct {
		uint32_t app_dbg_sel_group:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbg_sel_dword {
	struct {
		uint32_t app_dbg_sel_dword:6; /* [5:0] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_2nd_reset {
	struct {
		uint32_t cfg_2nd_reset:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_2ndbus_num {
	struct {
		uint32_t cfg_2ndbus_num:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_aer_int_msg_num {
	struct {
		uint32_t cfg_aer_int_msg_num:5; /* [4:0] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_atten_button_pressed_en {
	struct {
		uint32_t cfg_atten_button_pressed_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_atten_ind {
	struct {
		uint32_t cfg_atten_ind:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar0_limit_31_0 {
	struct {
		uint32_t cfg_bar0_limit_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar0_limit_63_32 {
	struct {
		uint32_t cfg_bar0_limit_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar0_start_31_0 {
	struct {
		uint32_t cfg_bar0_start_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar0_start_63_32 {
	struct {
		uint32_t cfg_bar0_start_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar1_limit {
	struct {
		uint32_t cfg_bar1_limit; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar1_start {
	struct {
		uint32_t cfg_bar1_start; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar2_limit_31_0 {
	struct {
		uint32_t cfg_bar2_limit_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar2_limit_63_32 {
	struct {
		uint32_t cfg_bar2_limit_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar2_start_31_0 {
	struct {
		uint32_t cfg_bar2_start_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar2_start_63_32 {
	struct {
		uint32_t cfg_bar2_start_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar3_limit {
	struct {
		uint32_t cfg_bar3_limit; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar3_start {
	struct {
		uint32_t cfg_bar3_start; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar4_limit_31_0 {
	struct {
		uint32_t cfg_bar4_limit_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar4_limit_63_32 {
	struct {
		uint32_t cfg_bar4_limit_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar4_start_31_0 {
	struct {
		uint32_t cfg_bar4_start_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar4_start_63_32 {
	struct {
		uint32_t cfg_bar4_start_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar5_limit {
	struct {
		uint32_t cfg_bar5_limit; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_bar5_start {
	struct {
		uint32_t cfg_bar5_start; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_br_ctrl_serren {
	struct {
		uint32_t cfg_br_ctrl_serren:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_cmd_cpled_int_en {
	struct {
		uint32_t cfg_cmd_cpled_int_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_crs_sw_vis_en {
	struct {
		uint32_t cfg_crs_sw_vis_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_dll_state_chged_en {
	struct {
		uint32_t cfg_dll_state_chged_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_exp_rom_limit {
	struct {
		uint32_t cfg_exp_rom_limit; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_exp_rom_start {
	struct {
		uint32_t cfg_exp_rom_start; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_hp_int_en {
	struct {
		uint32_t cfg_hp_int_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_hp_slot_ctrl_access {
	struct {
		uint32_t cfg_hp_slot_ctrl_access:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_hw_auto_sp_dis {
	struct {
		uint32_t cfg_hw_auto_sp_dis:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_int_disable {
	struct {
		uint32_t cfg_int_disable:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_l1sub_en {
	struct {
		uint32_t cfg_l1sub_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_ltr_m_en {
	struct {
		uint32_t cfg_ltr_m_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_max_payload_size {
	struct {
		uint32_t cfg_max_payload_size:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_max_rd_req_size {
	struct {
		uint32_t cfg_max_rd_req_size:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_mem_spac {
	struct {
		uint32_t cfg_mem_spac:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_mrl_sensor_chged_en {
	struct {
		uint32_t cfg_mrl_sensor_chged_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_no_snoop_en {
	struct {
		uint32_t cfg_no_snoop_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_obff_en {
	struct {
		uint32_t cfg_obff_en:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pbus_dev_num {
	struct {
		uint32_t cfg_pbus_dev_num:5; /* [4:0] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pbus_num {
	struct {
		uint32_t cfg_pbus_num:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pcie_cap_int_msg_num {
	struct {
		uint32_t cfg_pcie_cap_int_msg_num:5; /* [4:0] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_phy_control {
	struct {
		uint32_t cfg_phy_control; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pm_no_soft_rst {
	struct {
		uint32_t cfg_pm_no_soft_rst:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pre_det_chged_en {
	struct {
		uint32_t cfg_pre_det_chged_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pwr_ctrler_ctrl {
	struct {
		uint32_t cfg_pwr_ctrler_ctrl:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pwr_fault_det_en {
	struct {
		uint32_t cfg_pwr_fault_det_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pwr_ind {
	struct {
		uint32_t cfg_pwr_ind:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_rcb {
	struct {
		uint32_t cfg_rcb:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_relax_order_en {
	struct {
		uint32_t cfg_relax_order_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_send_cor_err {
	struct {
		uint32_t cfg_send_cor_err:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_send_f_err {
	struct {
		uint32_t cfg_send_f_err:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_send_nf_err {
	struct {
		uint32_t cfg_send_nf_err:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_subbus_num {
	struct {
		uint32_t cfg_subbus_num:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cxpl_debug_info_31_0 {
	struct {
		uint32_t cxpl_debug_info_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cxpl_debug_info_63_32 {
	struct {
		uint32_t cxpl_debug_info_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cxpl_debug_info_ei {
	struct {
		uint32_t cxpl_debug_info_ei:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_xfer_pending {
	struct {
		uint32_t edma_xfer_pending:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msi_ctrl_int_vec {
	struct {
		uint32_t msi_ctrl_int_vec:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msi_ctrl_io {
	struct {
		uint32_t msi_ctrl_io; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_curnt_state {
	struct {
		uint32_t pm_curnt_state:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_dstate {
	struct {
		uint32_t pm_dstate:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_pme_en {
	struct {
		uint32_t pm_pme_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_status {
	struct {
		uint32_t pm_status:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_idle {
	struct {
		uint32_t radm_idle:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_xfer_pending {
	struct {
		uint32_t radm_xfer_pending:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_smlh_ltssm_state {
	struct {
		uint32_t smlh_ltssm_state:6; /* [5:0] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_smlh_ltssm_state_rcvry_eq {
	struct {
		uint32_t smlh_ltssm_state_rcvry_eq:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_lookup_empty {
	struct {
		uint32_t trgt_lookup_empty:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_lookup_id {
	struct {
		uint32_t trgt_lookup_id:10; /* [9:0] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_msg_code {
	struct {
		uint32_t radm_msg_code:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_msg_payload_31_0 {
	struct {
		uint32_t radm_msg_payload_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_msg_payload_63_32 {
	struct {
		uint32_t radm_msg_payload_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_msg_req_id {
	struct {
		uint32_t radm_msg_req_id:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_cpl_attr {
	struct {
		uint32_t radm_timeout_cpl_attr:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_cpl_len {
	struct {
		uint32_t radm_timeout_cpl_len:12; /* [11:0] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_cpl_tag {
	struct {
		uint32_t radm_timeout_cpl_tag:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_cpl_tc {
	struct {
		uint32_t radm_timeout_cpl_tc:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_func_num {
	struct {
		uint32_t radm_timeout_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_vfunc_num {
	struct {
		uint32_t radm_timeout_vfunc_num:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_timeout_vfunc_active {
	struct {
		uint32_t radm_timeout_vfunc_active:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_attr {
	struct {
		uint32_t trgt_timeout_cpl_attr:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_func_num {
	struct {
		uint32_t trgt_timeout_cpl_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_len {
	struct {
		uint32_t trgt_timeout_cpl_len:12; /* [11:0] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_tc {
	struct {
		uint32_t trgt_timeout_cpl_tc:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_lookup_id {
	struct {
		uint32_t trgt_timeout_lookup_id:10; /* [9:0] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_cp_en {
	struct {
		uint32_t irq_cp_en_trgt_cpl_timeout:1; /* [0:0] */
		uint32_t irq_cp_en_ven_msg_grant:1; /* [1:1] */
		uint32_t irq_cp_en_ven_msi_grant:1; /* [2:2] */
		uint32_t irq_cp_en_cfg_aer_rc_err_msi:1; /* [3:3] */
		uint32_t irq_cp_en_cfg_bw_mgt_msi:1; /* [4:4] */
		uint32_t irq_cp_en_cfg_link_auto_bw_msi:1; /* [5:5] */
		uint32_t irq_cp_en_cfg_pme_msi:1; /* [6:6] */
		uint32_t irq_cp_en_cfg_sys_err_rc:1; /* [7:7] */
		uint32_t rsvd0:1; /* [8:8] */
		uint32_t irq_cp_en_rx_beacon_int:1; /* [9:9] */
		uint32_t irq_cp_en_hp_msi:1; /* [10:10] */
		uint32_t irq_cp_en_hp_pme:1; /* [11:11] */
		uint32_t irq_cp_en_radm_correctable_err:1; /* [12:12] */
		uint32_t irq_cp_en_radm_fatal_err:1; /* [13:13] */
		uint32_t irq_cp_en_radm_inta_asserted:1; /* [14:14] */
		uint32_t irq_cp_en_radm_inta_deasserted:1; /* [15:15] */
		uint32_t irq_cp_en_radm_intb_asserted:1; /* [16:16] */
		uint32_t irq_cp_en_radm_intb_deasserted:1; /* [17:17] */
		uint32_t irq_cp_en_radm_intc_asserted:1; /* [18:18] */
		uint32_t irq_cp_en_radm_intc_deasserted:1; /* [19:19] */
		uint32_t irq_cp_en_radm_intd_asserted:1; /* [20:20] */
		uint32_t irq_cp_en_radm_intd_deasserted:1; /* [21:21] */
		uint32_t irq_cp_en_radm_qoverflow:1; /* [22:22] */
		uint32_t rsvd3:1; /* [23:23] */
		uint32_t irq_cp_en_radm_msg_ltr:1; /* [24:24] */
		uint32_t rsvd2:1; /* [25:25] */
		uint32_t irq_cp_en_radm_msg_unlock:1; /* [26:26] */
		uint32_t irq_cp_en_radm_nonfatal_err:1; /* [27:27] */
		uint32_t irq_cp_en_radm_pm_pme:1; /* [28:28] */
		uint32_t irq_cp_en_radm_pm_to_ack:1; /* [29:29] */
		uint32_t irq_cp_en_radm_pm_turnoff:1; /* [30:30] */
		uint32_t irq_cp_en_radm_vendor_msg:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_vfunc_num {
	struct {
		uint32_t trgt_timeout_cpl_vfunc_num:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_trgt_timeout_cpl_vfunc_active {
	struct {
		uint32_t trgt_timeout_cpl_vfunc_active:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_1_cp_en {
	struct {
		uint32_t irq_cp_en_cfg_bad_dllp_err_sts:1; /* [0:0] */
		uint32_t irq_cp_en_cfg_bad_tlp_err_sts:1; /* [1:1] */
		uint32_t irq_cp_en_cfg_corrected_internal_err_sts:1; /* [2:2] */
		uint32_t irq_cp_en_cfg_dl_protocol_err_sts:1; /* [3:3] */
		uint32_t irq_cp_en_cfg_ecrc_err_sts:1; /* [4:4] */
		uint32_t irq_cp_en_cfg_fc_protocol_err_sts:1; /* [5:5] */
		uint32_t irq_cp_en_cfg_mlf_tlp_err_sts:1; /* [6:6] */
		uint32_t irq_cp_en_cfg_rcvr_err_sts:1; /* [7:7] */
		uint32_t irq_cp_en_cfg_rcvr_overflow_err_sts:1; /* [8:8] */
		uint32_t irq_cp_en_cfg_replay_number_rollover_err_sts:1; /* [9:9] */
		uint32_t irq_cp_en_cfg_replay_timer_timeout_err_sts:1; /* [10:10] */
		uint32_t irq_cp_en_cfg_surprise_down_er_sts:1; /* [11:11] */
		uint32_t irq_cp_en_cfg_uncor_internal_err_sts:1; /* [12:12] */
		uint32_t rsvd0:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_2_cp_en {
	struct {
		uint32_t irq_cp_en_wake:1; /* [0:0] */
		uint32_t rsvd1:1; /* [1:1] */
		uint32_t irq_cp_en_cfg_aer_rc_err_int:1; /* [2:2] */
		uint32_t irq_cp_en_cfg_bus_master_en:1; /* [3:3] */
		uint32_t irq_cp_en_cfg_link_eq_req_int:1; /* [4:4] */
		uint32_t irq_cp_en_cfg_pme_int:1; /* [5:5] */
		uint32_t irq_cp_en_rtlh_rfc_upd_0:1; /* [6:6] */
		uint32_t irq_cp_en_rtlh_rfc_upd_1:1; /* [7:7] */
		uint32_t irq_cp_en_rtlh_rfc_upd_2:1; /* [8:8] */
		uint32_t irq_cp_en_rtlh_rfc_upd_3:1; /* [9:9] */
		uint32_t irq_cp_en_rtlh_rfc_upd_4:1; /* [10:10] */
		uint32_t irq_cp_en_rtlh_rfc_upd_5:1; /* [11:11] */
		uint32_t irq_cp_en_rtlh_rfc_upd_6:1; /* [12:12] */
		uint32_t irq_cp_en_rtlh_rfc_upd_7:1; /* [13:13] */
		uint32_t irq_cp_en_cfg_bw_mgt_int:1; /* [14:14] */
		uint32_t irq_cp_en_cfg_link_auto_bw_int:1; /* [15:15] */
		uint32_t irq_cp_en_hp_int:1; /* [16:16] */
		uint32_t rsvd2:1; /* [17:17] */
		uint32_t irq_cp_en_pm_linkst_in_l0s:1; /* [18:18] */
		uint32_t irq_cp_en_pm_linkst_in_l1:1; /* [19:19] */
		uint32_t irq_cp_en_pm_linkst_in_l1sub_0:1; /* [20:20] */
		uint32_t irq_cp_en_pm_linkst_in_l2:1; /* [21:21] */
		uint32_t irq_cp_en_pm_linkst_l2_exit:1; /* [22:22] */
		uint32_t irq_cp_en_pm_xtlh_block_tlp:1; /* [23:23] */
		uint32_t irq_cp_en_radm_cpl_timeout:1; /* [24:24] */
		uint32_t irq_cp_en_radm_q_not_empty:1; /* [25:25] */
		uint32_t irq_cp_en_rdlh_link_up_0:1; /* [26:26] */
		uint32_t irq_cp_en_smlh_link_up:1; /* [27:27] */
		uint32_t irq_cp_en_compare_end_checker_g1:1; /* [28:28] */
		uint32_t irq_cp_en_compare_end_checker_g2:1; /* [29:29] */
		uint32_t irq_cp_en_compare_end_checker_g3:1; /* [30:30] */
		uint32_t irq_cp_en_compare_end_checker_g4:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_3_cp_en {
	struct {
		uint32_t rsvd0:1; /* [0:0] */
		uint32_t irq_cp_en_pm_linkst_in_l1sub_1:1; /* [1:1] */
		uint32_t irq_cp_en_rdlh_link_up_1:1; /* [2:2] */
		uint32_t rsvd1:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_bus_dev_num {
	struct {
		uint32_t app_bus_num:8; /* [7:0] */
		uint32_t app_dev_num:5; /* [12:8] */
		uint32_t rsvd0:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_ctrl_signals {
	struct {
		uint32_t app_dbi_ro_wr_disable:1; /* [0:0] */
		uint32_t app_hold_phy_rst:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_acs_capabilities_ctrl_reg {
	struct {
		uint32_t cfg_acs_at_blocking_en:1; /* [0:0] */
		uint32_t cfg_acs_egress_ctrl_vec:8; /* [8:1] */
		uint32_t cfg_acs_p2p_compl_redirect_en:1; /* [9:9] */
		uint32_t cfg_acs_p2p_direct_transl_en:1; /* [10:10] */
		uint32_t cfg_acs_p2p_egress_ctrl_en:1; /* [11:11] */
		uint32_t cfg_acs_p2p_req_redirect_en:1; /* [12:12] */
		uint32_t cfg_acs_up_forward_en:1; /* [13:13] */
		uint32_t cfg_acs_validation_en:1; /* [14:14] */
		uint32_t cfg_drs_msi:1; /* [15:15] */
		uint32_t cfg_up_drs_to_frs:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_exp_rom_bar_validation_details {
	struct {
		uint32_t exp_rom_validation_status:3; /* [2:0] */
		uint32_t exp_rom_validation_status_strobe:1; /* [3:3] */
		uint32_t exp_rom_validation_details:4; /* [7:4] */
		uint32_t exp_rom_validation_details_strobe:1; /* [8:8] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_frsq_massaging_signals {
	struct {
		uint32_t frsq_int_msg_num:1; /* [0:0] */
		uint32_t frsq_msi:5; /* [5:1] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_local_ref_clk_req_n {
	struct {
		uint32_t local_ref_clk_req_n:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_ctrl_signals {
	struct {
		uint32_t ptm_context_valid:1; /* [0:0] */
		uint32_t ptm_responder_rdy_to_validate:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_external_master_time_31_0 {
	struct {
		uint32_t ptm_external_master_time_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_external_master_time_63_32 {
	struct {
		uint32_t ptm_external_master_time_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_local_clock_31_0 {
	struct {
		uint32_t ptm_local_clock_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_local_clock_63_32 {
	struct {
		uint32_t ptm_local_clock_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptm_external_master_strobe {
	struct {
		uint32_t ptm_external_master_strobe:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_register {
	struct {
		uint32_t mac_phy_pclk_rate:3; /* [2:0] */
		uint32_t mac_phy_width:2; /* [4:3] */
		uint32_t mac_phy_dirchange:16; /* [20:5] */
		uint32_t rsvd0:11; /* [31:21] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_clkreq_in_n {
	struct {
		uint32_t clkreq_h2l:1; /* [0:0] */
		uint32_t phy_ref_clk_req_n_to_ctrlr:1; /* [1:1] */
		uint32_t phy_ref_clk_req_n:1; /* [2:2] */
		uint32_t clkreq_l2h:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_mac_localfs {
	struct {
		uint32_t phy_mac_localfs:6; /* [5:0] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_current_data_rate {
	struct {
		uint32_t pm_current_data_rate:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_owre {
	struct {
		uint32_t app_owre_idle:1; /* [0:0] */
		uint32_t app_owre_obff:1; /* [1:1] */
		uint32_t app_owre_cpu_act:1; /* [2:2] */
		uint32_t owre_wake:1; /* [3:3] */
		uint32_t owre_grant:1; /* [4:4] */
		uint32_t owre_cur_state:4; /* [8:5] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_wk_min_max {
	struct {
		uint32_t cfg_wk_min_pls_wdt:8; /* [7:0] */
		uint32_t cfg_wk_max_pls_wdt:8; /* [15:8] */
		uint32_t cfg_wk_min_f2f_wdt:8; /* [23:16] */
		uint32_t cfg_wk_max_f2f_wdt:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_shared_dbi_bus_access {
	struct {
		uint32_t iatu_access_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ela_fifo_ctrl {
	struct {
		uint32_t ela_fifo_ctrl:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_mstr_aclk {
	struct {
		uint32_t mstr_rasdp_err_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_en_mstr_aclk {
	struct {
		uint32_t irq_en_mstr_rasdp_err_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_bmisc_info_cpl_stat {
	struct {
		uint32_t mstr_bmisc_info_cpl_stat:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_rmisc_info {
	struct {
		uint32_t mstr_rmisc_info:13; /* [12:0] */
		uint32_t rsvd0:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_rmisc_info_cpl_stat {
	struct {
		uint32_t mstr_rmisc_info_cpl_stat:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_zeroread {
	struct {
		uint32_t mstr_armisc_info_zeroread:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_31_0 {
	struct {
		uint32_t mstr_armisc_info_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_49_32 {
	struct {
		uint32_t mstr_armisc_info_49_32:18; /* [17:0] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_dma {
	struct {
		uint32_t mstr_armisc_info_dma:7; /* [6:0] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_last_dcmp_tlp {
	struct {
		uint32_t mstr_armisc_info_last_dcmp_tlp:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_31_0 {
	struct {
		uint32_t mstr_awmisc_info_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_49_32 {
	struct {
		uint32_t mstr_awmisc_info_49_32:18; /* [17:0] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_dma {
	struct {
		uint32_t mstr_awmisc_info_dma:7; /* [6:0] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_hdr_34dw_31_0 {
	struct {
		uint32_t mstr_awmisc_info_hdr_34dw_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_hdr_34dw_63_32 {
	struct {
		uint32_t mstr_awmisc_info_hdr_34dw_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_last_dcmp_tlp {
	struct {
		uint32_t mstr_awmisc_info_last_dcmp_tlp:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_ep {
	struct {
		uint32_t mstr_awmisc_info_ep:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_wtran_cnt {
	struct {
		uint32_t mstr_wtran_cnt:22; /* [21:0] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_rtran_cnt {
	struct {
		uint32_t mstr_rtran_cnt:22; /* [21:0] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_ch_status {
	struct {
		uint32_t mstr_ch_status:10; /* [9:0] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_func_num {
	struct {
		uint32_t mstr_armisc_info_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_vfunc_num {
	struct {
		uint32_t mstr_armisc_info_vfunc_num:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_vfunc_active {
	struct {
		uint32_t mstr_armisc_info_vfunc_active:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_ar_user {
	struct {
		uint32_t mstr_ar_user:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_func_num {
	struct {
		uint32_t mstr_awmisc_info_func_num:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_vfunc_num {
	struct {
		uint32_t mstr_awmisc_info_vfunc_num:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_vfunc_active {
	struct {
		uint32_t mstr_awmisc_info_vfunc_active:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_aw_user {
	struct {
		uint32_t mstr_aw_user:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_slv_aclk {
	struct {
		uint32_t slv_rasdp_err_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_0_en_slv_aclk {
	struct {
		uint32_t irq_en_slv_rasdp_err_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_armisc_info {
	struct {
		uint32_t slv_armisc_info:22; /* [21:0] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_armisc_info_atu_bypass {
	struct {
		uint32_t slv_armisc_info_atu_bypass:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_awmisc_info {
	struct {
		uint32_t slv_awmisc_info:22; /* [21:0] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_awmisc_info_atu_bypass {
	struct {
		uint32_t slv_awmisc_info_atu_bypass:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_awmisc_info_hdr_34dw_31_0 {
	struct {
		uint32_t slv_awmisc_info_hdr_34dw_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_awmisc_info_hdr_34dw_63_32 {
	struct {
		uint32_t slv_awmisc_info_hdr_34dw_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_awmisc_info_p_tag {
	struct {
		uint32_t slv_awmisc_info_p_tag:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_bmisc_info {
	struct {
		uint32_t slv_bmisc_info:11; /* [10:0] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_rmisc_info {
	struct {
		uint32_t slv_rmisc_info:11; /* [10:0] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_wmisc_info_ep {
	struct {
		uint32_t slv_wmisc_info_ep:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_wmisc_info_silentdrop {
	struct {
		uint32_t slv_wmisc_info_silentdrop:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_store_ctrl {
	struct {
		uint32_t history_store_ctrl_g1:3; /* [2:0] */
		uint32_t history_store_ctrl_g2:3; /* [5:3] */
		uint32_t history_store_ctrl_g3:3; /* [8:6] */
		uint32_t history_store_ctrl_g4:3; /* [11:9] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_s_g1 {
	struct {
		uint32_t power_state_history_s_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_m_g1 {
	struct {
		uint32_t power_state_history_m_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_s_g2 {
	struct {
		uint32_t power_state_history_s_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_m_g2 {
	struct {
		uint32_t power_state_history_m_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_s_g3 {
	struct {
		uint32_t power_state_history_s_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_m_g3 {
	struct {
		uint32_t power_state_history_m_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_s_g4 {
	struct {
		uint32_t power_state_history_s_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_power_state_history_m_g4 {
	struct {
		uint32_t power_state_history_m_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_sel {
	struct {
		uint32_t history_sel:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_mon_control {
	struct {
		uint32_t leq_mon_control:5; /* [4:0] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_0 {
	struct {
		uint32_t leq_status_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_1 {
	struct {
		uint32_t leq_status_1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_2 {
	struct {
		uint32_t leq_status_2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_3 {
	struct {
		uint32_t leq_status_3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_4 {
	struct {
		uint32_t leq_status_4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_5 {
	struct {
		uint32_t leq_status_5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_6 {
	struct {
		uint32_t leq_status_6; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_7 {
	struct {
		uint32_t leq_status_7; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_8 {
	struct {
		uint32_t leq_status_8; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_9 {
	struct {
		uint32_t leq_status_9; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_10 {
	struct {
		uint32_t leq_status_10; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_11 {
	struct {
		uint32_t leq_status_11; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_12 {
	struct {
		uint32_t leq_status_12; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_13 {
	struct {
		uint32_t leq_status_13; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_14 {
	struct {
		uint32_t leq_status_14; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_15 {
	struct {
		uint32_t leq_status_15; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_16 {
	struct {
		uint32_t leq_status_16; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_17 {
	struct {
		uint32_t leq_status_17; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_18 {
	struct {
		uint32_t leq_status_18; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_19 {
	struct {
		uint32_t leq_status_19; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_20 {
	struct {
		uint32_t leq_status_20; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_21 {
	struct {
		uint32_t leq_status_21; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_22 {
	struct {
		uint32_t leq_status_22; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_23 {
	struct {
		uint32_t leq_status_23; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_24 {
	struct {
		uint32_t leq_status_24; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_25 {
	struct {
		uint32_t leq_status_25; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_26 {
	struct {
		uint32_t leq_status_26; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_27 {
	struct {
		uint32_t leq_status_27; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_28 {
	struct {
		uint32_t leq_status_28; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_29 {
	struct {
		uint32_t leq_status_29; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_30 {
	struct {
		uint32_t leq_status_30; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_status_31 {
	struct {
		uint32_t leq_status_31; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_leq_counter {
	struct {
		uint32_t leq_counter; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg0 {
	struct {
		uint32_t history_reg0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg1 {
	struct {
		uint32_t history_reg1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg2 {
	struct {
		uint32_t history_reg2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg3 {
	struct {
		uint32_t history_reg3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg4 {
	struct {
		uint32_t history_reg4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg5 {
	struct {
		uint32_t history_reg5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg6 {
	struct {
		uint32_t history_reg6; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg7 {
	struct {
		uint32_t history_reg7; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg8 {
	struct {
		uint32_t history_reg8; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg9 {
	struct {
		uint32_t history_reg9; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg10 {
	struct {
		uint32_t history_reg10; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg11 {
	struct {
		uint32_t history_reg11; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg12 {
	struct {
		uint32_t history_reg12; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg13 {
	struct {
		uint32_t history_reg13; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg14 {
	struct {
		uint32_t history_reg14; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg15 {
	struct {
		uint32_t history_reg15; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg16 {
	struct {
		uint32_t history_reg16; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg17 {
	struct {
		uint32_t history_reg17; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg18 {
	struct {
		uint32_t history_reg18; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg19 {
	struct {
		uint32_t history_reg19; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg20 {
	struct {
		uint32_t history_reg20; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg21 {
	struct {
		uint32_t history_reg21; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg22 {
	struct {
		uint32_t history_reg22; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg23 {
	struct {
		uint32_t history_reg23; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg24 {
	struct {
		uint32_t history_reg24; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg25 {
	struct {
		uint32_t history_reg25; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg26 {
	struct {
		uint32_t history_reg26; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg27 {
	struct {
		uint32_t history_reg27; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg28 {
	struct {
		uint32_t history_reg28; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg29 {
	struct {
		uint32_t history_reg29; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg30 {
	struct {
		uint32_t history_reg30; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_history_reg31 {
	struct {
		uint32_t history_reg31; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg0 {
	struct {
		uint32_t ts_history_reg0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg1 {
	struct {
		uint32_t ts_history_reg1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg2 {
	struct {
		uint32_t ts_history_reg2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg3 {
	struct {
		uint32_t ts_history_reg3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg4 {
	struct {
		uint32_t ts_history_reg4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg5 {
	struct {
		uint32_t ts_history_reg5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg6 {
	struct {
		uint32_t ts_history_reg6; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg7 {
	struct {
		uint32_t ts_history_reg7; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg8 {
	struct {
		uint32_t ts_history_reg8; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg9 {
	struct {
		uint32_t ts_history_reg9; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg10 {
	struct {
		uint32_t ts_history_reg10; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg11 {
	struct {
		uint32_t ts_history_reg11; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg12 {
	struct {
		uint32_t ts_history_reg12; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg13 {
	struct {
		uint32_t ts_history_reg13; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg14 {
	struct {
		uint32_t ts_history_reg14; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg15 {
	struct {
		uint32_t ts_history_reg15; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg16 {
	struct {
		uint32_t ts_history_reg16; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg17 {
	struct {
		uint32_t ts_history_reg17; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg18 {
	struct {
		uint32_t ts_history_reg18; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg19 {
	struct {
		uint32_t ts_history_reg19; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg20 {
	struct {
		uint32_t ts_history_reg20; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg21 {
	struct {
		uint32_t ts_history_reg21; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg22 {
	struct {
		uint32_t ts_history_reg22; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg23 {
	struct {
		uint32_t ts_history_reg23; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg24 {
	struct {
		uint32_t ts_history_reg24; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg25 {
	struct {
		uint32_t ts_history_reg25; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg26 {
	struct {
		uint32_t ts_history_reg26; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg27 {
	struct {
		uint32_t ts_history_reg27; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg28 {
	struct {
		uint32_t ts_history_reg28; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg29 {
	struct {
		uint32_t ts_history_reg29; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg30 {
	struct {
		uint32_t ts_history_reg30; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_lsb_history_reg31 {
	struct {
		uint32_t ts_history_reg31; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg0 {
	struct {
		uint32_t ts_history_reg0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg1 {
	struct {
		uint32_t ts_history_reg1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg2 {
	struct {
		uint32_t ts_history_reg2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg3 {
	struct {
		uint32_t ts_history_reg3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg4 {
	struct {
		uint32_t ts_history_reg4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg5 {
	struct {
		uint32_t ts_history_reg5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg6 {
	struct {
		uint32_t ts_history_reg6; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg7 {
	struct {
		uint32_t ts_history_reg7; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg8 {
	struct {
		uint32_t ts_history_reg8; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg9 {
	struct {
		uint32_t ts_history_reg9; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg10 {
	struct {
		uint32_t ts_history_reg10; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg11 {
	struct {
		uint32_t ts_history_reg11; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg12 {
	struct {
		uint32_t ts_history_reg12; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg13 {
	struct {
		uint32_t ts_history_reg13; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg14 {
	struct {
		uint32_t ts_history_reg14; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg15 {
	struct {
		uint32_t ts_history_reg15; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg16 {
	struct {
		uint32_t ts_history_reg16; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg17 {
	struct {
		uint32_t ts_history_reg17; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg18 {
	struct {
		uint32_t ts_history_reg18; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg19 {
	struct {
		uint32_t ts_history_reg19; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg20 {
	struct {
		uint32_t ts_history_reg20; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg21 {
	struct {
		uint32_t ts_history_reg21; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg22 {
	struct {
		uint32_t ts_history_reg22; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg23 {
	struct {
		uint32_t ts_history_reg23; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg24 {
	struct {
		uint32_t ts_history_reg24; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg25 {
	struct {
		uint32_t ts_history_reg25; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg26 {
	struct {
		uint32_t ts_history_reg26; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg27 {
	struct {
		uint32_t ts_history_reg27; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg28 {
	struct {
		uint32_t ts_history_reg28; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg29 {
	struct {
		uint32_t ts_history_reg29; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg30 {
	struct {
		uint32_t ts_history_reg30; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ts_msb_history_reg31 {
	struct {
		uint32_t ts_history_reg31; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pad_perst_n {
	struct {
		uint32_t pad_perst_n_sync:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_mac_rxstatus_31_0 {
	struct {
		uint32_t phy_mac_rxstatus_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_mac_rxstatus_47_32 {
	struct {
		uint32_t phy_mac_rxstatus_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_messagebus_31_0 {
	struct {
		uint32_t mac_phy_messagebus_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_messagebus_63_32 {
	struct {
		uint32_t mac_phy_messagebus_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_messagebus_95_64 {
	struct {
		uint32_t mac_phy_messagebus_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_messagebus_127_96 {
	struct {
		uint32_t mac_phy_messagebus_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_30_reg {
	struct {
		uint32_t protocol0_ext_rx_vco_ld_val_g4:13; /* [12:0] */
		uint32_t protocol0_ext_rx_vco_ld_val_g5:13; /* [25:13] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_31_reg {
	struct {
		uint32_t protocol0_ext_rx_ref_ld_val_g4:7; /* [6:0] */
		uint32_t protocol0_ext_rx_ref_ld_val_g5:7; /* [13:7] */
		uint32_t rsvd0:18; /* [31:14] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_32_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_33_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_34_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_35_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_36_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_37_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g2_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_38_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_39_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_40_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g3_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_41_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_42_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_43_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g4_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_44_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_45_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_46_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_boost_g5_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_47_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_48_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_49_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_50_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_53_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_54_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_55_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_56_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_57_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_58_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_59_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_60_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_61_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_main_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_62_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_ovrd_g1:16; /* [15:0] */
		uint32_t protocol0_ext_tx_eq_ovrd_g2:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_63_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_ovrd_g3:16; /* [15:0] */
		uint32_t protocol0_ext_tx_eq_ovrd_g4:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_64_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_ovrd_g5:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_65_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_66_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_67_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_68_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_69_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_70_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g2_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_71_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_72_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_73_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g3_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_74_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_75_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_76_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g4_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_77_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_78_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_79_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_post_g5_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_80_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_81_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_82_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_83_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_84_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_85_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g2_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_86_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_87_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_88_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g3_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_89_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_90_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_91_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g4_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_92_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_93_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_94_reg {
	struct {
		uint32_t protocol0_ext_tx_eq_pre_g5_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_95_reg {
	struct {
		uint32_t phy0_ref_repeat_clk_en:1; /* [0:0] */
		uint32_t phy0_ref_repeat_clk_sel:2; /* [2:1] */
		uint32_t phy0_refa_clk_sel:2; /* [4:3] */
		uint32_t phy0_refb_clk_sel:2; /* [6:5] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_96_reg {
	struct {
		uint32_t phy1_ref_repeat_clk_en:1; /* [0:0] */
		uint32_t phy1_ref_repeat_clk_sel:2; /* [2:1] */
		uint32_t phy1_refa_clk_sel:2; /* [4:3] */
		uint32_t phy1_refb_clk_sel:2; /* [6:5] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_97_reg {
	struct {
		uint32_t phy2_ref_repeat_clk_en:1; /* [0:0] */
		uint32_t phy2_ref_repeat_clk_sel:2; /* [2:1] */
		uint32_t phy2_refa_clk_sel:2; /* [4:3] */
		uint32_t phy2_refb_clk_sel:2; /* [6:5] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_98_reg {
	struct {
		uint32_t phy3_ref_repeat_clk_en:1; /* [0:0] */
		uint32_t phy3_ref_repeat_clk_sel:2; /* [2:1] */
		uint32_t phy3_refa_clk_sel:2; /* [4:3] */
		uint32_t phy3_refb_clk_sel:2; /* [6:5] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_99_reg {
	struct {
		uint32_t phy1_sram_init_done:1; /* [0:0] */
		uint32_t rsvd0:1; /* [1:1] */
		uint32_t phy1_pma_pwr_en:1; /* [2:2] */
		uint32_t phy1_pcs_pwr_en:1; /* [3:3] */
		uint32_t phy1_mpllb_force_ack:1; /* [4:4] */
		uint32_t phy1_mplla_force_ack:1; /* [5:5] */
		uint32_t rsvd1:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_100_reg {
	struct {
		uint32_t phy2_sram_init_done:1; /* [0:0] */
		uint32_t rsvd0:1; /* [1:1] */
		uint32_t phy2_pma_pwr_en:1; /* [2:2] */
		uint32_t phy2_pcs_pwr_en:1; /* [3:3] */
		uint32_t phy2_mpllb_force_ack:1; /* [4:4] */
		uint32_t phy2_mplla_force_ack:1; /* [5:5] */
		uint32_t rsvd1:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_101_reg {
	struct {
		uint32_t phy3_sram_init_done:1; /* [0:0] */
		uint32_t rsvd0:1; /* [1:1] */
		uint32_t phy3_pma_pwr_en:1; /* [2:2] */
		uint32_t phy3_pcs_pwr_en:1; /* [3:3] */
		uint32_t phy3_mpllb_force_ack:1; /* [4:4] */
		uint32_t phy3_mplla_force_ack:1; /* [5:5] */
		uint32_t rsvd1:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_102_reg {
	struct {
		uint32_t phy1_mplla_force_en:1; /* [0:0] */
		uint32_t phy1_mplla_ssc_en:1; /* [1:1] */
		uint32_t phy1_mpllb_force_en:1; /* [2:2] */
		uint32_t phy1_mpllb_ssc_en:1; /* [3:3] */
		uint32_t phy1_sram_bypass:1; /* [4:4] */
		uint32_t phy1_sram_ext_ld_done:1; /* [5:5] */
		uint32_t phy1_sram_bootload_bypass:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_103_reg {
	struct {
		uint32_t phy2_mplla_force_en:1; /* [0:0] */
		uint32_t phy2_mplla_ssc_en:1; /* [1:1] */
		uint32_t phy2_mpllb_force_en:1; /* [2:2] */
		uint32_t phy2_mpllb_ssc_en:1; /* [3:3] */
		uint32_t phy2_sram_bypass:1; /* [4:4] */
		uint32_t phy2_sram_ext_ld_done:1; /* [5:5] */
		uint32_t phy2_sram_bootload_bypass:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_104_reg {
	struct {
		uint32_t phy3_mplla_force_en:1; /* [0:0] */
		uint32_t phy3_mplla_ssc_en:1; /* [1:1] */
		uint32_t phy3_mpllb_force_en:1; /* [2:2] */
		uint32_t phy3_mpllb_ssc_en:1; /* [3:3] */
		uint32_t phy3_sram_bypass:1; /* [4:4] */
		uint32_t phy3_sram_ext_ld_done:1; /* [5:5] */
		uint32_t phy3_sram_bootload_bypass:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_105_reg {
	struct {
		uint32_t phy_rx1_term_acdc:1; /* [0:0] */
		uint32_t phy_lane1_power_present:1; /* [1:1] */
		uint32_t phy_lane1_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_106_reg {
	struct {
		uint32_t phy_rx2_term_acdc:1; /* [0:0] */
		uint32_t phy_lane2_power_present:1; /* [1:1] */
		uint32_t phy_lane2_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_107_reg {
	struct {
		uint32_t phy_rx3_term_acdc:1; /* [0:0] */
		uint32_t phy_lane3_power_present:1; /* [1:1] */
		uint32_t phy_lane3_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_108_reg {
	struct {
		uint32_t phy_rx4_term_acdc:1; /* [0:0] */
		uint32_t phy_lane4_power_present:1; /* [1:1] */
		uint32_t phy_lane4_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_109_reg {
	struct {
		uint32_t phy_rx5_term_acdc:1; /* [0:0] */
		uint32_t phy_lane5_power_present:1; /* [1:1] */
		uint32_t phy_lane5_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_110_reg {
	struct {
		uint32_t phy_rx6_term_acdc:1; /* [0:0] */
		uint32_t phy_lane6_power_present:1; /* [1:1] */
		uint32_t phy_lane6_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_111_reg {
	struct {
		uint32_t phy_rx7_term_acdc:1; /* [0:0] */
		uint32_t phy_lane7_power_present:1; /* [1:1] */
		uint32_t phy_lane7_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_112_reg {
	struct {
		uint32_t phy_rx8_term_acdc:1; /* [0:0] */
		uint32_t phy_lane8_power_present:1; /* [1:1] */
		uint32_t phy_lane8_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_113_reg {
	struct {
		uint32_t phy_rx9_term_acdc:1; /* [0:0] */
		uint32_t phy_lane9_power_present:1; /* [1:1] */
		uint32_t phy_lane9_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_114_reg {
	struct {
		uint32_t phy_rx10_term_acdc:1; /* [0:0] */
		uint32_t phy_lane10_power_present:1; /* [1:1] */
		uint32_t phy_lane10_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_115_reg {
	struct {
		uint32_t phy_rx11_term_acdc:1; /* [0:0] */
		uint32_t phy_lane11_power_present:1; /* [1:1] */
		uint32_t phy_lane11_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_116_reg {
	struct {
		uint32_t phy_rx12_term_acdc:1; /* [0:0] */
		uint32_t phy_lane12_power_present:1; /* [1:1] */
		uint32_t phy_lane12_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_117_reg {
	struct {
		uint32_t phy_rx13_term_acdc:1; /* [0:0] */
		uint32_t phy_lane13_power_present:1; /* [1:1] */
		uint32_t phy_lane13_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_118_reg {
	struct {
		uint32_t phy_rx14_term_acdc:1; /* [0:0] */
		uint32_t phy_lane14_power_present:1; /* [1:1] */
		uint32_t phy_lane14_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_119_reg {
	struct {
		uint32_t phy_rx15_term_acdc:1; /* [0:0] */
		uint32_t phy_lane15_power_present:1; /* [1:1] */
		uint32_t phy_lane15_rx2tx_par_lb_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_217_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_adapt_mode_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_218_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_adapt_mode_r0_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_219_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_adapt_mode_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_220_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_adapt_mode_r1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_221_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_222_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_223_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r0_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_224_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_225_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_226_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_ppm_max_r1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_227_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_228_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_229_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_230_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_231_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_232_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r0_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_233_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_234_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_235_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_236_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_237_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_238_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_cdr_vco_config_r1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_239_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_delta_iq_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_240_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_delta_iq_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_241_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_delta_iq_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_242_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_delta_iq_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_243_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_dfe_bypass_r0:16; /* [15:0] */
		uint32_t protocol0_esm_ext_rx_dfe_bypass_r1:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_244_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_245_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_246_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_247_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_248_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_249_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r0_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_250_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_251_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_252_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_253_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_254_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_255_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_config_r1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_256_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_rate_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_257_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_rate_r0_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_258_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_rate_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_259_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_afe_rate_r1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_260_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_att_lvl_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_261_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_att_lvl_r0_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_262_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_att_lvl_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_263_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_att_lvl_r1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_264_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_265_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_266_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r0_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_267_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_268_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_269_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_boost_r1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_270_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_pole_r0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_271_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_ctle_pole_r1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_272_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_float_en_r0:16; /* [15:0] */
		uint32_t protocol0_esm_ext_rx_eq_dfe_float_en_r1:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_273_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_274_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_275_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_276_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r0_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_277_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r0_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_278_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_279_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_280_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_281_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_282_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap1_r1_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_283_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap2_r0:8; /* [7:0] */
		uint32_t protocol0_esm_ext_rx_eq_dfe_tap2_r1:8; /* [15:8] */
		uint32_t protocol0_esm_ext_rx_eq_vga_gain_r0:5; /* [20:16] */
		uint32_t protocol0_esm_ext_rx_eq_vga_gain_r1:5; /* [25:21] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_284_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_285_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_286_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_287_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_288_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_289_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_290_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_291_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_292_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_ref_ld_val_r0:7; /* [6:0] */
		uint32_t protocol0_esm_ext_rx_ref_ld_val_r1:7; /* [13:7] */
		uint32_t protocol0_esm_ext_rx_sigdet_lf_threshold_r0:3; /* [16:14] */
		uint32_t protocol0_esm_ext_rx_sigdet_lf_threshold_r1:3; /* [19:17] */
		uint32_t protocol0_esm_ext_rx_sigdet_lfps_filter_en_r0:1; /* [20:20] */
		uint32_t protocol0_esm_ext_rx_sigdet_lfps_filter_en_r1:1; /* [21:21] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_293_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_vco_ld_val_r0:13; /* [12:0] */
		uint32_t protocol0_esm_ext_rx_vco_ld_val_r1:13; /* [25:13] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_294_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_dcc_ctrl_cm_range_r0:4; /* [3:0] */
		uint32_t protocol0_esm_ext_rx_dcc_ctrl_cm_range_r1:4; /* [7:4] */
		uint32_t protocol0_esm_ext_rx_dcc_ctrl_diff_range_r0:4; /* [11:8] */
		uint32_t protocol0_esm_ext_rx_dcc_ctrl_diff_range_r1:4; /* [15:12] */
		uint32_t protocol0_esm_ext_rx_term_ctrl_r0:4; /* [19:16] */
		uint32_t protocol0_esm_ext_rx_term_ctrl_r1:4; /* [23:20] */
		uint32_t protocol0_esm_ext_tx_fastedge_en_r0:1; /* [24:24] */
		uint32_t protocol0_esm_ext_tx_fastedge_en_r1:1; /* [25:25] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_295_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_ovrd_r0:16; /* [15:0] */
		uint32_t protocol0_esm_ext_tx_eq_ovrd_r1:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_296_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_297_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_298_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r0_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_299_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_300_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_301_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_post_r1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_302_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_303_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_304_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r0_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_305_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_306_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_307_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_pre_r1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_308_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_309_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_310_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_311_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_312_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_313_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_314_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_315_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_316_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_317_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_318_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_319_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r0_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_320_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_321_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_322_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_323_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_intg_r1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_324_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_325_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_326_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_327_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r0_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_328_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_329_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_330_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_331_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_cp_ctl_prop_r1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_332_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_333_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_334_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_335_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r0_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_336_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_337_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_338_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_339_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_fbdiv_r1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_340_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_postdiv_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_341_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_postdiv_r0_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_342_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_postdiv_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_343_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_postdiv_r1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_344_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_rc_filter_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_345_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_rc_filter_r0_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_346_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_rc_filter_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_347_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_rc_filter_r1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_348_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refdiv_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_349_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refdiv_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_350_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refdiv_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_351_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refdiv_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_352_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refsel_r0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_353_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_refsel_r1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_354_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_v2i_mode_r0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_355_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_v2i_mode_r1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_356_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_vco_low_freq_r0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_357_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_vco_low_freq_r1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_358_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_word_clk_div_sel_r0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_359_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_ropll_word_clk_div_sel_r1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_360_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_dcc_ctrl_cm_range_r0:4; /* [3:0] */
		uint32_t protocol0_esm_ext_tx_dcc_ctrl_cm_range_r1:4; /* [7:4] */
		uint32_t protocol0_esm_ext_tx_dcc_ctrl_diff_range_r0:4; /* [11:8] */
		uint32_t protocol0_esm_ext_tx_dcc_ctrl_diff_range_r1:4; /* [15:12] */
		uint32_t protocol0_esm_ext_tx_term_ctrl_r0:4; /* [19:16] */
		uint32_t protocol0_esm_ext_tx_term_ctrl_r1:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_363_reg {
	struct {
		uint32_t protocol0_ext_mplla_word_clk_div:2; /* [1:0] */
		uint32_t protocol0_ext_mplla_fb_clk_div4_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_367_reg {
	struct {
		uint32_t protocol0_ext_mpllb_word_clk_div:2; /* [1:0] */
		uint32_t protocol0_ext_mpllb_fb_clk_div4_en:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_369_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_370_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_371_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_372_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g2_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_373_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_374_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g3_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_375_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_376_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g4_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_377_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_378_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_mode_g5_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_379_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_sel_piperate0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_380_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_sel_piperate1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_381_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_sel_piperate2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_382_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_sel_piperate3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_cor_err_rpt_en {
	struct {
		uint32_t cfg_cor_err_rpt_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_f_err_rpt_en {
	struct {
		uint32_t cfg_f_err_rpt_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_nf_err_rpt_en {
	struct {
		uint32_t cfg_nf_err_rpt_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_reg_serren {
	struct {
		uint32_t cfg_reg_serren:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_en_core_clk {
	struct {
		uint32_t pm_en_core_clk:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_l1_entry_started {
	struct {
		uint32_t pm_l1_entry_started:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_trgt1_vc {
	struct {
		uint32_t radm_trgt1_vc:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_rxelecidle_disable {
	struct {
		uint32_t mac_phy_rxelecidle_disable:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mac_phy_txcommonmode_disable {
	struct {
		uint32_t mac_phy_txcommonmode_disable:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_assert_inta_grt {
	struct {
		uint32_t assert_inta_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_assert_intb_grt {
	struct {
		uint32_t assert_intb_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_assert_intc_grt {
	struct {
		uint32_t assert_intc_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_assert_intd_grt {
	struct {
		uint32_t assert_intd_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_deassert_inta_grt {
	struct {
		uint32_t deassert_inta_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_deassert_intb_grt {
	struct {
		uint32_t deassert_intb_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_deassert_intc_grt {
	struct {
		uint32_t deassert_intc_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_deassert_intd_grt {
	struct {
		uint32_t deassert_intd_grt:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptrc_event_foundry_sig_31_0 {
	struct {
		uint32_t ptrc_event_foundry_sig_0_31; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ptrc_event_foundry_sig_63_32 {
	struct {
		uint32_t ptrc_event_foundry_sig_32_63; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_l1sub_disable {
	struct {
		uint32_t app_l1sub_disable:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_0_reg {
	struct {
		uint32_t phy0_mplla_force_en:1; /* [0:0] */
		uint32_t phy0_mplla_ssc_en:1; /* [1:1] */
		uint32_t phy0_mpllb_force_en:1; /* [2:2] */
		uint32_t phy0_mpllb_ssc_en:1; /* [3:3] */
		uint32_t phy0_sram_bypass:1; /* [4:4] */
		uint32_t phy0_sram_ext_ld_done:1; /* [5:5] */
		uint32_t phy0_sram_bootload_bypass:1; /* [6:6] */
		uint32_t phy0_sup_pre_hp:1; /* [7:7] */
		uint32_t phy0_ref_use_pad:1; /* [8:8] */
		uint32_t phy0_ana_pwr_en:1; /* [9:9] */
		uint32_t phy0_pcs_pwr_stable:1; /* [10:10] */
		uint32_t phy0_pma_pwr_stable:1; /* [11:11] */
		uint32_t phy_lane0_power_present:1; /* [12:12] */
		uint32_t phy_lane0_rx2tx_par_lb_en:1; /* [13:13] */
		uint32_t phy_rx0_term_acdc:1; /* [14:14] */
		uint32_t pipe_rx_cdr_legacy_en:1; /* [15:15] */
		uint32_t pipe_rx_recal_cont_en:1; /* [16:16] */
		uint32_t phy_tx0_bypass_eq_calc:1; /* [17:17] */
		uint32_t phy_tx0_vregdrv_byp:1; /* [18:18] */
		uint32_t rsvd0:13; /* [31:19] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_1_reg {
	struct {
		uint32_t protocol0_ext_mplla_cp_int:7; /* [6:0] */
		uint32_t protocol0_ext_mplla_cp_int_gs:7; /* [13:7] */
		uint32_t protocol0_ext_mplla_cp_prop:7; /* [20:14] */
		uint32_t protocol0_ext_mplla_cp_prop_gs:7; /* [27:21] */
		uint32_t protocol0_ext_mplla_div5_clk_en:1; /* [28:28] */
		uint32_t protocol0_ext_mplla_div_clk_en:1; /* [29:29] */
		uint32_t protocol0_ext_mplla_ssc_up_spread:1; /* [30:30] */
		uint32_t protocol0_ext_mplla_word_div2_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_2_reg {
	struct {
		uint32_t protocol0_ext_mplla_frac_den:16; /* [15:0] */
		uint32_t protocol0_ext_mplla_frac_quot:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_3_reg {
	struct {
		uint32_t protocol0_ext_mplla_frac_rem:16; /* [15:0] */
		uint32_t protocol0_ext_mplla_div_multiplier:8; /* [23:16] */
		uint32_t protocol0_ext_mplla_freq_vco:2; /* [25:24] */
		uint32_t protocol0_ext_mplla_tx_clk_div:3; /* [28:26] */
		uint32_t protocol0_ext_mplla_v2i:2; /* [30:29] */
		uint32_t protocol0_ext_mpllb_frac_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_4_reg {
	struct {
		uint32_t protocol0_ext_mplla_multiplier:12; /* [11:0] */
		uint32_t protocol0_ext_mplla_ssc_peak:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5_reg {
	struct {
		uint32_t protocol0_ext_mplla_ssc_step_size:21; /* [20:0] */
		uint32_t protocol0_ext_mpllb_cp_int:7; /* [27:21] */
		uint32_t protocol0_ext_mpllb_freq_vco:2; /* [29:28] */
		uint32_t protocol0_ext_mpllb_v2i:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_6_reg {
	struct {
		uint32_t protocol0_ext_mpllb_cp_int_gs:7; /* [6:0] */
		uint32_t protocol0_ext_mpllb_cp_prop:7; /* [13:7] */
		uint32_t protocol0_ext_mpllb_cp_prop_gs:7; /* [20:14] */
		uint32_t protocol0_ext_mpllb_div_multiplier:8; /* [28:21] */
		uint32_t protocol0_ext_mpllb_tx_clk_div:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_7_reg {
	struct {
		uint32_t protocol0_ext_mpllb_frac_den:16; /* [15:0] */
		uint32_t protocol0_ext_mpllb_frac_quot:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_8_reg {
	struct {
		uint32_t protocol0_ext_mpllb_frac_rem:16; /* [15:0] */
		uint32_t protocol0_ext_mpllb_multiplier:12; /* [27:16] */
		uint32_t protocol0_ext_mpllb_word_div2_en:1; /* [28:28] */
		uint32_t protocol0_ext_ref_clk_mplla_div:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_9_reg {
	struct {
		uint32_t protocol0_ext_mpllb_ssc_peak:20; /* [19:0] */
		uint32_t protocol0_ext_rx_adapt_afe_en_g1:1; /* [20:20] */
		uint32_t protocol0_ext_rx_adapt_afe_en_g2:1; /* [21:21] */
		uint32_t protocol0_ext_rx_adapt_afe_en_g3:1; /* [22:22] */
		uint32_t protocol0_ext_rx_adapt_dfe_en_g1:1; /* [23:23] */
		uint32_t protocol0_ext_rx_adapt_dfe_en_g2:1; /* [24:24] */
		uint32_t protocol0_ext_rx_adapt_dfe_en_g3:1; /* [25:25] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_10_reg {
	struct {
		uint32_t protocol0_ext_mpllb_ssc_step_size:21; /* [20:0] */
		uint32_t protocol0_ext_ref_range:5; /* [25:21] */
		uint32_t protocol0_ext_mpllb_div5_clk_en:1; /* [26:26] */
		uint32_t protocol0_ext_mpllb_div_clk_en:1; /* [27:27] */
		uint32_t protocol0_ext_mpllb_ssc_up_spread:1; /* [28:28] */
		uint32_t protocol0_ext_ref_clk_mpllb_div:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_11_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_gain_g1:4; /* [3:0] */
		uint32_t protocol0_ext_rx_eq_afe_gain_g2:4; /* [7:4] */
		uint32_t protocol0_ext_rx_eq_afe_gain_g3:4; /* [11:8] */
		uint32_t protocol0_ext_rx_cdr_vco_lowfreq_g1:1; /* [12:12] */
		uint32_t protocol0_ext_rx_cdr_vco_lowfreq_g2:1; /* [13:13] */
		uint32_t protocol0_ext_rx_cdr_vco_lowfreq_g3:1; /* [14:14] */
		uint32_t rsvd0:17; /* [31:15] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_12_reg {
	struct {
		uint32_t protocol0_ext_rx_term_ctrl:3; /* [2:0] */
		uint32_t protocol0_ext_rx_sigdet_hf_en:1; /* [3:3] */
		uint32_t protocol0_ext_rx_sigdet_hf_en_g1:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_13_reg {
	struct {
		uint32_t protocol0_ext_rx_sigdet_hf_filt_dis:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_14_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_delta_iq_g1:4; /* [3:0] */
		uint32_t protocol0_ext_rx_eq_delta_iq_g2:4; /* [7:4] */
		uint32_t protocol0_ext_rx_eq_delta_iq_g3:4; /* [11:8] */
		uint32_t protocol0_ext_sup_rx_vco_vref_sel:3; /* [14:12] */
		uint32_t protocol0_ext_rx_sigdet_lf_en:1; /* [15:15] */
		uint32_t protocol0_ext_rx_sigdet_lf_filter_en:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_17_reg {
	struct {
		uint32_t protocol0_ext_rx_ref_ld_val_g1:7; /* [6:0] */
		uint32_t protocol0_ext_rx_ref_ld_val_g2:7; /* [13:7] */
		uint32_t protocol0_ext_rx_ref_ld_val_g3:7; /* [20:14] */
		uint32_t pg_mode_en:1; /* [21:21] */
		uint32_t pcs_pwr_stable:1; /* [22:22] */
		uint32_t phy_ext_ctrl_sel:1; /* [23:23] */
		uint32_t phy0_ref_alt_clk_lp_sel:1; /* [24:24] */
		uint32_t phy0_cr_para_sel:1; /* [25:25] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_18_reg {
	struct {
		uint32_t protocol0_ext_rx_sigdet_hf_threshold_g1:3; /* [2:0] */
		uint32_t protocol0_ext_rx_sigdet_hf_threshold_g2:3; /* [5:3] */
		uint32_t protocol0_ext_rx_sigdet_hf_threshold_g3:3; /* [8:6] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_19_reg {
	struct {
		uint32_t protocol0_ext_rx_vco_ld_val_g1:13; /* [12:0] */
		uint32_t protocol0_ext_rx_vco_ld_val_g2:13; /* [25:13] */
		uint32_t rsvd0:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_20_reg {
	struct {
		uint32_t protocol0_ext_rx_vco_ld_val_g3:13; /* [12:0] */
		uint32_t rsvd0:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_21_reg {
	struct {
		uint32_t protocol0_ext_rx_sigdet_lf_threshold_g1:3; /* [2:0] */
		uint32_t protocol0_ext_rx_sigdet_lf_threshold_g2:3; /* [5:3] */
		uint32_t protocol0_ext_rx_sigdet_lf_threshold_g3:3; /* [8:6] */
		uint32_t protocol0_ext_rx_sigdet_lf_threshold_g4:3; /* [11:9] */
		uint32_t protocol0_ext_rx_sigdet_lf_threshold_g5:3; /* [14:12] */
		uint32_t rsvd0:17; /* [31:15] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_22_reg {
	struct {
		uint32_t protocol0_ext_bs_rx_bigswing:1; /* [0:0] */
		uint32_t protocol0_ext_bs_rx_level:3; /* [3:1] */
		uint32_t protocol0_ext_bs_tx_lowswing:1; /* [4:4] */
		uint32_t protocol0_ext_dco_finetune:6; /* [10:5] */
		uint32_t protocol0_ext_dco_range:2; /* [12:11] */
		uint32_t protocol0_ext_mplla_frac_en:1; /* [13:13] */
		uint32_t rsvd0:18; /* [31:14] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_23_reg {
	struct {
		uint32_t phy_ana_pwr_stable:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_27_reg {
	struct {
		uint32_t protocol0_ext_tx_term_ctrl:3; /* [2:0] */
		uint32_t protocol0_ext_tx_vboost_lvl:3; /* [5:3] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_28_reg {
	struct {
		uint32_t phy0_sram_init_done:1; /* [0:0] */
		uint32_t rsvd0:1; /* [1:1] */
		uint32_t phy0_pma_pwr_en:1; /* [2:2] */
		uint32_t phy0_pcs_pwr_en:1; /* [3:3] */
		uint32_t phy0_mpllb_force_ack:1; /* [4:4] */
		uint32_t phy0_mplla_force_ack:1; /* [5:5] */
		uint32_t phy_upcs_pwr_en:1; /* [6:6] */
		uint32_t rsvd1:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_29_reg {
	struct {
		uint32_t phy0_sram_init_done_rise_int_en:1; /* [0:0] */
		uint32_t usp_eq_redo_executed_rise_int_en:1; /* [1:1] */
		uint32_t cfg_send_cor_err_rise_int_en:1; /* [2:2] */
		uint32_t cfg_send_nf_err_rise_int_en:1; /* [3:3] */
		uint32_t cfg_send_f_err_rise_int_en:1; /* [4:4] */
		uint32_t cfg_send_cor_err_rise_int_clr:1; /* [5:5] */
		uint32_t cfg_send_nf_err_rise_int_clr:1; /* [6:6] */
		uint32_t cfg_send_f_err_rise_int_clr:1; /* [7:7] */
		uint32_t usp_eq_redo_executed_rise_int_clr:1; /* [8:8] */
		uint32_t phy0_sram_init_done_rise_int_clr:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_ext_tag_en {
	struct {
		uint32_t cfg_ext_tag_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_msi_64 {
	struct {
		uint32_t cfg_msi_64:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_msi_addr_31_0 {
	struct {
		uint32_t cfg_msi_addr_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_msi_addr_63_32 {
	struct {
		uint32_t cfg_msi_addr_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_msi_data {
	struct {
		uint32_t cfg_msi_data; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_msi_ext_data_en {
	struct {
		uint32_t cfg_msi_ext_data_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_num_vf {
	struct {
		uint32_t cfg_num_vf:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_start_vfi {
	struct {
		uint32_t cfg_start_vfi:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_en {
	struct {
		uint32_t cfg_vf_msix_en:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_func_mask {
	struct {
		uint32_t cfg_vf_msix_func_mask:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_pba_bir {
	struct {
		uint32_t cfg_vf_msix_pba_bir:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_pba_offset {
	struct {
		uint32_t cfg_vf_msix_pba_offset:29; /* [28:0] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_table_bir {
	struct {
		uint32_t cfg_vf_msix_table_bir:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_table_offset {
	struct {
		uint32_t cfg_vf_msix_table_offset:29; /* [28:0] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msix_table_size {
	struct {
		uint32_t cfg_vf_msix_table_size:11; /* [10:0] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_pba_data_in_31_0 {
	struct {
		uint32_t msix_pba_data_in_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_pba_data_in_63_32 {
	struct {
		uint32_t msix_pba_data_in_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_table_data_in_31_0 {
	struct {
		uint32_t msix_table_data_in_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_table_data_in_63_32 {
	struct {
		uint32_t msix_table_data_in_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_table_data_in_95_64 {
	struct {
		uint32_t msix_table_data_in_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_table_data_in_127_96 {
	struct {
		uint32_t msix_table_data_in_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msix_table_data_in_130_128 {
	struct {
		uint32_t msix_table_data_in_130_128:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_cactive {
	struct {
		uint32_t mstr_cactive:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_csysack {
	struct {
		uint32_t mstr_csysack:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_aspm_l1_enter_ready {
	struct {
		uint32_t pm_aspm_l1_enter_ready:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_slot_pwr_limit {
	struct {
		uint32_t radm_slot_pwr_limit:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_slot_pwr_payload {
	struct {
		uint32_t radm_slot_pwr_payload; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_cactive {
	struct {
		uint32_t slv_cactive:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_csysack {
	struct {
		uint32_t slv_csysack:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_training_rst_n {
	struct {
		uint32_t training_rst_n:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_device_type_ovrd {
	struct {
		uint32_t device_type_ovrd:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_device_type {
	struct {
		uint32_t device_type:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbg_sel_phy_lane {
	struct {
		uint32_t dbg_sel_phy_lane:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_rbar_size_31_0 {
	struct {
		uint32_t cfg_rbar_size_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_rbar_size_35_32 {
	struct {
		uint32_t cfg_rbar_size_35_32:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_msi_int {
	struct {
		uint32_t msi_int; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_vf_cfg_msi_64 {
	struct {
		uint32_t cfg_vf_msi_64:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_31_0 {
	struct {
		uint32_t cfg_vf_msi_addr_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_63_32 {
	struct {
		uint32_t cfg_vf_msi_addr_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_95_64 {
	struct {
		uint32_t cfg_vf_msi_addr_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_127_96 {
	struct {
		uint32_t cfg_vf_msi_addr_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_159_128 {
	struct {
		uint32_t cfg_vf_msi_addr_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_191_160 {
	struct {
		uint32_t cfg_vf_msi_addr_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_223_192 {
	struct {
		uint32_t cfg_vf_msi_addr_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_addr_255_224 {
	struct {
		uint32_t cfg_vf_msi_addr_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_data_31_0 {
	struct {
		uint32_t cfg_vf_msi_data_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_data_63_32 {
	struct {
		uint32_t cfg_vf_msi_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_data_95_64 {
	struct {
		uint32_t cfg_vf_msi_data_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_data_127_96 {
	struct {
		uint32_t cfg_vf_msi_data_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_msi_ext_data_en {
	struct {
		uint32_t cfg_vf_msi_ext_data_en:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_383_reg {
	struct {
		uint32_t protocol0_ext_rx_adapt_sel_piperate4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_384_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_385_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_386_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g1_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_387_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_388_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_389_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g2_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_390_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_391_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_392_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g3_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_393_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_394_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_395_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g4_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_396_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_397_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_398_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_ppm_max_g5_79_64:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_399_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_400_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_401_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_402_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_403_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_404_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_405_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_406_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_407_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_408_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_409_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_410_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g2_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_411_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_412_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_413_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_414_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_415_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_416_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g3_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_417_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_418_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_419_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_420_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_421_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_422_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g4_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_423_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_424_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_425_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_426_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_427_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_428_reg {
	struct {
		uint32_t protocol0_ext_rx_cdr_vco_config_g5_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_429_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_430_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_431_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_432_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_433_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_434_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_435_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_436_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_437_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_438_reg {
	struct {
		uint32_t protocol0_ext_rx_delta_iq_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_439_reg {
	struct {
		uint32_t protocol0_ext_rx_dfe_bypass_g1:16; /* [15:0] */
		uint32_t protocol0_ext_rx_dfe_bypass_g2:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_440_reg {
	struct {
		uint32_t protocol0_ext_rx_dfe_bypass_g3:16; /* [15:0] */
		uint32_t protocol0_ext_rx_dfe_bypass_g4:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_441_reg {
	struct {
		uint32_t protocol0_ext_rx_dfe_bypass_g5:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_442_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_443_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_444_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_445_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_446_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_447_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_448_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_449_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_450_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_451_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_452_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_453_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g2_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_454_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_455_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_456_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_457_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_458_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_459_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g3_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_460_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_461_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_462_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_463_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_464_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_465_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g4_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_466_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_467_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_468_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_469_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_470_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_471_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_config_g5_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_472_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_473_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_474_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_475_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g2_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_476_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_477_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g3_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_478_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_479_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g4_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_480_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_481_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_afe_rate_g5_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_482_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_483_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_484_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_485_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g2_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_486_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_487_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g3_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_488_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_489_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g4_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_490_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_491_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_att_lvl_g5_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_492_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_pole_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_493_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_pole_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_494_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_pole_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_495_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_pole_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_496_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_ctle_pole_g5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_497_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_float_en_g1:16; /* [15:0] */
		uint32_t protocol0_ext_rx_eq_dfe_float_en_g2:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_498_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_float_en_g3:16; /* [15:0] */
		uint32_t protocol0_ext_rx_eq_dfe_float_en_g4:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_499_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_float_en_g5:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_500_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_501_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_502_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_503_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_504_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g1_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_505_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_506_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_507_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_508_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g2_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_509_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g2_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_510_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_511_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_512_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_513_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g3_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_514_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g3_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_515_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_516_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_517_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_518_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g4_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_519_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g4_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_520_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_521_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_522_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_523_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g5_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_524_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap1_g5_143_128:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_525_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_vga_gain_g1:5; /* [4:0] */
		uint32_t protocol0_ext_rx_eq_vga_gain_g2:5; /* [9:5] */
		uint32_t protocol0_ext_rx_eq_vga_gain_g3:5; /* [14:10] */
		uint32_t protocol0_ext_rx_eq_vga_gain_g4:5; /* [19:15] */
		uint32_t protocol0_ext_rx_eq_vga_gain_g5:5; /* [24:20] */
		uint32_t rsvd0:7; /* [31:25] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_526_reg {
	struct {
		uint32_t protocol0_ext_rx_los_pwr_up_cnt:11; /* [10:0] */
		uint32_t protocol0_ext_rx_vref_ctrl:5; /* [15:11] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_527_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_528_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_529_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_530_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_531_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_532_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_533_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_534_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_535_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_536_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_537_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_538_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_539_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_540_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_541_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_542_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_543_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_544_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_545_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_546_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_547_reg {
	struct {
		uint32_t protocol0_ext_rx_sigdet_lfps_filter_en_g1:1; /* [0:0] */
		uint32_t protocol0_ext_rx_sigdet_lfps_filter_en_g2:1; /* [1:1] */
		uint32_t protocol0_ext_rx_sigdet_lfps_filter_en_g3:1; /* [2:2] */
		uint32_t protocol0_ext_rx_sigdet_lfps_filter_en_g4:1; /* [3:3] */
		uint32_t protocol0_ext_rx_sigdet_lfps_filter_en_g5:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_548_reg {
	struct {
		uint32_t protocol0_ext_rx_dcc_ctrl_cm_range_g1:4; /* [3:0] */
		uint32_t protocol0_ext_rx_dcc_ctrl_cm_range_g2:4; /* [7:4] */
		uint32_t protocol0_ext_rx_dcc_ctrl_cm_range_g3:4; /* [11:8] */
		uint32_t protocol0_ext_rx_dcc_ctrl_cm_range_g4:4; /* [15:12] */
		uint32_t protocol0_ext_rx_dcc_ctrl_cm_range_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_549_reg {
	struct {
		uint32_t protocol0_ext_rx_dcc_ctrl_diff_range_g1:4; /* [3:0] */
		uint32_t protocol0_ext_rx_dcc_ctrl_diff_range_g2:4; /* [7:4] */
		uint32_t protocol0_ext_rx_dcc_ctrl_diff_range_g3:4; /* [11:8] */
		uint32_t protocol0_ext_rx_dcc_ctrl_diff_range_g4:4; /* [15:12] */
		uint32_t protocol0_ext_rx_dcc_ctrl_diff_range_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_550_reg {
	struct {
		uint32_t protocol0_ext_rx_term_ctrl_g1:4; /* [3:0] */
		uint32_t protocol0_ext_rx_term_ctrl_g2:4; /* [7:4] */
		uint32_t protocol0_ext_rx_term_ctrl_g3:4; /* [11:8] */
		uint32_t protocol0_ext_rx_term_ctrl_g4:4; /* [15:12] */
		uint32_t protocol0_ext_rx_term_ctrl_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_551_reg {
	struct {
		uint32_t protocol0_ext_tx_fastedge_en_g1:1; /* [0:0] */
		uint32_t protocol0_ext_tx_fastedge_en_g2:1; /* [1:1] */
		uint32_t protocol0_ext_tx_fastedge_en_g3:1; /* [2:2] */
		uint32_t protocol0_ext_tx_fastedge_en_g4:1; /* [3:3] */
		uint32_t protocol0_ext_tx_fastedge_en_g5:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_552_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_553_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_554_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_555_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_556_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_557_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_558_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_559_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_560_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_561_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_562_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_563_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_564_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_565_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_566_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_567_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_568_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_569_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_570_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_571_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_572_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_573_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_574_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_575_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_576_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_577_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_578_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_579_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g2_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_580_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_581_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_582_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_583_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g3_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_584_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_585_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_586_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_587_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g4_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_588_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_589_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_590_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_591_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_intg_g5_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_592_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_593_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_594_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_595_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_596_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_597_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_598_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_599_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g2_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_600_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_601_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_602_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_603_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g3_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_604_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_605_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_606_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_607_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g4_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_608_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_609_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_610_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_611_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_cp_ctl_prop_g5_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_612_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_613_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_614_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_615_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g1_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_616_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_617_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_618_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g2_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_619_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g2_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_620_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_621_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_622_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g3_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_623_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g3_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_624_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_625_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_626_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g4_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_627_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g4_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_628_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_629_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_630_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g5_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_631_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_fbdiv_g5_111_96:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_632_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_633_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_634_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_635_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g2_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_636_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_637_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g3_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_638_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_639_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g4_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_640_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_641_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_postdiv_g5_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_642_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_643_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g1_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_644_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_645_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g2_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_646_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_647_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g3_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_648_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_649_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g4_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_650_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_651_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_rc_filter_g5_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_652_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_653_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_654_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g2_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_655_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g2_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_656_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g3_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_657_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g3_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_658_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g4_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_659_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g4_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_660_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g5_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_661_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refdiv_g5_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_662_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refsel_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_663_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refsel_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_664_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refsel_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_665_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refsel_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_666_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_refsel_g5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_667_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_v2i_mode_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_668_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_v2i_mode_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_669_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_v2i_mode_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_670_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_v2i_mode_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_671_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_v2i_mode_g5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_672_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_vco_low_freq_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_673_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_vco_low_freq_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_674_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_vco_low_freq_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_675_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_vco_low_freq_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_676_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_vco_low_freq_g5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_677_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_word_clk_div_sel_g1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_678_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_word_clk_div_sel_g2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_679_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_word_clk_div_sel_g3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_680_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_word_clk_div_sel_g4; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_681_reg {
	struct {
		uint32_t protocol0_ext_tx_ropll_word_clk_div_sel_g5; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_682_reg {
	struct {
		uint32_t protocol0_ext_tx_dcc_ctrl_cm_range_g1:4; /* [3:0] */
		uint32_t protocol0_ext_tx_dcc_ctrl_cm_range_g2:4; /* [7:4] */
		uint32_t protocol0_ext_tx_dcc_ctrl_cm_range_g3:4; /* [11:8] */
		uint32_t protocol0_ext_tx_dcc_ctrl_cm_range_g4:4; /* [15:12] */
		uint32_t protocol0_ext_tx_dcc_ctrl_cm_range_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_683_reg {
	struct {
		uint32_t protocol0_ext_tx_dcc_ctrl_diff_range_g1:4; /* [3:0] */
		uint32_t protocol0_ext_tx_dcc_ctrl_diff_range_g2:4; /* [7:4] */
		uint32_t protocol0_ext_tx_dcc_ctrl_diff_range_g3:4; /* [11:8] */
		uint32_t protocol0_ext_tx_dcc_ctrl_diff_range_g4:4; /* [15:12] */
		uint32_t protocol0_ext_tx_dcc_ctrl_diff_range_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_684_reg {
	struct {
		uint32_t protocol0_ext_tx_term_ctrl_g1:4; /* [3:0] */
		uint32_t protocol0_ext_tx_term_ctrl_g2:4; /* [7:4] */
		uint32_t protocol0_ext_tx_term_ctrl_g3:4; /* [11:8] */
		uint32_t protocol0_ext_tx_term_ctrl_g4:4; /* [15:12] */
		uint32_t protocol0_ext_tx_term_ctrl_g5:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_31_0 {
	struct {
		uint32_t rtlh_rfc_data_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_63_32 {
	struct {
		uint32_t rtlh_rfc_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_95_64 {
	struct {
		uint32_t rtlh_rfc_data_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_127_96 {
	struct {
		uint32_t rtlh_rfc_data_127_96; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_159_128 {
	struct {
		uint32_t rtlh_rfc_data_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_191_160 {
	struct {
		uint32_t rtlh_rfc_data_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_223_192 {
	struct {
		uint32_t rtlh_rfc_data_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_rtlh_rfc_data_255_224 {
	struct {
		uint32_t rtlh_rfc_data_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_685_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r0_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_686_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r0_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_687_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r0_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_688_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_689_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r1_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_690_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_eq_main_r1_95_64; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_691_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap2_g1:8; /* [7:0] */
		uint32_t protocol0_ext_rx_eq_dfe_tap2_g2:8; /* [15:8] */
		uint32_t protocol0_ext_rx_eq_dfe_tap2_g3:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_692_reg {
	struct {
		uint32_t protocol0_ext_rx_eq_dfe_tap2_g4:8; /* [7:0] */
		uint32_t protocol0_ext_rx_eq_dfe_tap2_g5:8; /* [15:8] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_120_reg {
	struct {
		uint32_t phy_lane0_cntx_en:1; /* [0:0] */
		uint32_t phy_lane1_cntx_en:1; /* [1:1] */
		uint32_t phy_lane2_cntx_en:1; /* [2:2] */
		uint32_t phy_lane3_cntx_en:1; /* [3:3] */
		uint32_t phy_lane4_cntx_en:1; /* [4:4] */
		uint32_t phy_lane5_cntx_en:1; /* [5:5] */
		uint32_t phy_lane6_cntx_en:1; /* [6:6] */
		uint32_t phy_lane7_cntx_en:1; /* [7:7] */
		uint32_t phy_lane8_cntx_en:1; /* [8:8] */
		uint32_t phy_lane9_cntx_en:1; /* [9:9] */
		uint32_t phy_lane10_cntx_en:1; /* [10:10] */
		uint32_t phy_lane11_cntx_en:1; /* [11:11] */
		uint32_t phy_lane12_cntx_en:1; /* [12:12] */
		uint32_t phy_lane13_cntx_en:1; /* [13:13] */
		uint32_t phy_lane14_cntx_en:1; /* [14:14] */
		uint32_t phy_lane15_cntx_en:1; /* [15:15] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_121_reg {
	struct {
		uint32_t phy_rx0_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx0_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx0_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx0_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_122_reg {
	struct {
		uint32_t phy_rx0_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx0_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx0_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_123_reg {
	struct {
		uint32_t phy_rx1_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx1_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx1_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx1_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_124_reg {
	struct {
		uint32_t phy_rx1_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx1_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx1_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_125_reg {
	struct {
		uint32_t phy_rx2_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx2_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx2_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx2_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_126_reg {
	struct {
		uint32_t phy_rx2_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx2_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx2_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_127_reg {
	struct {
		uint32_t phy_rx3_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx3_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx3_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx3_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_128_reg {
	struct {
		uint32_t phy_rx3_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx3_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx3_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_129_reg {
	struct {
		uint32_t phy_rx4_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx4_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx4_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx4_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_130_reg {
	struct {
		uint32_t phy_rx4_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx4_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx4_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_131_reg {
	struct {
		uint32_t phy_rx5_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx5_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx5_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx5_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_132_reg {
	struct {
		uint32_t phy_rx5_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx5_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx5_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_133_reg {
	struct {
		uint32_t phy_rx6_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx6_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx6_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx6_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_134_reg {
	struct {
		uint32_t phy_rx6_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx6_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx6_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_135_reg {
	struct {
		uint32_t phy_rx7_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx7_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx7_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx7_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_136_reg {
	struct {
		uint32_t phy_rx7_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx7_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx7_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_137_reg {
	struct {
		uint32_t phy_rx8_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx8_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx8_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx8_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_138_reg {
	struct {
		uint32_t phy_rx8_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx8_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx8_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_139_reg {
	struct {
		uint32_t phy_rx9_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx9_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx9_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx9_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_140_reg {
	struct {
		uint32_t phy_rx9_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx9_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx9_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_141_reg {
	struct {
		uint32_t phy_rx10_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx10_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx10_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx10_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_142_reg {
	struct {
		uint32_t phy_rx10_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx10_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx10_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_143_reg {
	struct {
		uint32_t phy_rx11_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx11_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx11_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx11_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_144_reg {
	struct {
		uint32_t phy_rx11_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx11_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx11_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_145_reg {
	struct {
		uint32_t phy_rx12_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx12_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx12_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx12_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_146_reg {
	struct {
		uint32_t phy_rx12_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx12_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx12_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_147_reg {
	struct {
		uint32_t phy_rx13_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx13_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx13_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx13_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_148_reg {
	struct {
		uint32_t phy_rx13_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx13_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx13_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_149_reg {
	struct {
		uint32_t phy_rx14_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx14_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx14_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx14_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_150_reg {
	struct {
		uint32_t phy_rx14_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx14_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx14_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_151_reg {
	struct {
		uint32_t phy_rx15_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_rx15_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_rx15_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_rx15_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_152_reg {
	struct {
		uint32_t phy_rx15_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_rx15_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_rx15_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_153_reg {
	struct {
		uint32_t phy_tx_cmn0_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn0_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn0_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn0_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_154_reg {
	struct {
		uint32_t phy_tx_cmn0_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn0_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn0_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_155_reg {
	struct {
		uint32_t phy_tx0_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx0_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx0_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx0_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_156_reg {
	struct {
		uint32_t phy_tx0_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx0_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx0_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_157_reg {
	struct {
		uint32_t phy_tx_cmn1_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn1_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn1_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn1_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_158_reg {
	struct {
		uint32_t phy_tx_cmn1_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn1_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn1_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_159_reg {
	struct {
		uint32_t phy_tx1_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx1_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx1_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx1_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_160_reg {
	struct {
		uint32_t phy_tx1_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx1_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx1_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_161_reg {
	struct {
		uint32_t phy_tx_cmn2_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn2_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn2_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn2_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_162_reg {
	struct {
		uint32_t phy_tx_cmn2_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn2_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn2_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_163_reg {
	struct {
		uint32_t phy_tx2_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx2_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx2_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx2_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_164_reg {
	struct {
		uint32_t phy_tx2_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx2_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx2_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_165_reg {
	struct {
		uint32_t phy_tx_cmn3_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn3_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn3_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn3_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_166_reg {
	struct {
		uint32_t phy_tx_cmn3_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn3_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn3_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_167_reg {
	struct {
		uint32_t phy_tx3_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx3_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx3_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx3_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_168_reg {
	struct {
		uint32_t phy_tx3_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx3_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx3_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_169_reg {
	struct {
		uint32_t phy_tx_cmn4_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn4_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn4_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn4_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_170_reg {
	struct {
		uint32_t phy_tx_cmn4_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn4_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn4_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_171_reg {
	struct {
		uint32_t phy_tx4_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx4_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx4_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx4_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_172_reg {
	struct {
		uint32_t phy_tx4_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx4_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx4_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_173_reg {
	struct {
		uint32_t phy_tx_cmn5_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn5_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn5_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn5_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_174_reg {
	struct {
		uint32_t phy_tx_cmn5_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn5_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn5_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_175_reg {
	struct {
		uint32_t phy_tx5_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx5_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx5_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx5_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_176_reg {
	struct {
		uint32_t phy_tx5_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx5_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx5_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_177_reg {
	struct {
		uint32_t phy_tx_cmn6_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn6_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn6_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn6_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_178_reg {
	struct {
		uint32_t phy_tx_cmn6_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn6_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn6_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_179_reg {
	struct {
		uint32_t phy_tx6_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx6_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx6_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx6_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_180_reg {
	struct {
		uint32_t phy_tx6_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx6_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx6_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_181_reg {
	struct {
		uint32_t phy_tx_cmn7_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn7_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn7_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn7_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_182_reg {
	struct {
		uint32_t phy_tx_cmn7_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn7_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn7_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_183_reg {
	struct {
		uint32_t phy_tx7_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx7_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx7_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx7_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_184_reg {
	struct {
		uint32_t phy_tx7_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx7_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx7_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_185_reg {
	struct {
		uint32_t phy_tx_cmn8_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn8_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn8_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn8_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_186_reg {
	struct {
		uint32_t phy_tx_cmn8_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn8_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn8_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_187_reg {
	struct {
		uint32_t phy_tx8_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx8_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx8_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx8_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_188_reg {
	struct {
		uint32_t phy_tx8_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx8_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx8_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_189_reg {
	struct {
		uint32_t phy_tx_cmn9_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn9_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn9_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn9_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_190_reg {
	struct {
		uint32_t phy_tx_cmn9_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn9_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn9_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_191_reg {
	struct {
		uint32_t phy_tx9_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx9_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx9_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx9_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_192_reg {
	struct {
		uint32_t phy_tx9_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx9_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx9_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_193_reg {
	struct {
		uint32_t phy_tx_cmn10_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn10_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn10_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn10_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_194_reg {
	struct {
		uint32_t phy_tx_cmn10_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn10_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn10_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_195_reg {
	struct {
		uint32_t phy_tx10_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx10_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx10_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx10_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_196_reg {
	struct {
		uint32_t phy_tx10_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx10_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx10_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_197_reg {
	struct {
		uint32_t phy_tx_cmn11_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn11_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn11_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn11_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_198_reg {
	struct {
		uint32_t phy_tx_cmn11_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn11_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn11_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_199_reg {
	struct {
		uint32_t phy_tx11_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx11_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx11_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx11_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_200_reg {
	struct {
		uint32_t phy_tx11_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx11_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx11_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_201_reg {
	struct {
		uint32_t phy_tx_cmn12_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn12_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn12_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn12_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_202_reg {
	struct {
		uint32_t phy_tx_cmn12_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn12_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn12_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_203_reg {
	struct {
		uint32_t phy_tx12_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx12_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx12_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx12_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_204_reg {
	struct {
		uint32_t phy_tx12_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx12_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx12_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_205_reg {
	struct {
		uint32_t phy_tx_cmn13_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn13_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn13_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn13_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_206_reg {
	struct {
		uint32_t phy_tx_cmn13_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn13_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn13_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_207_reg {
	struct {
		uint32_t phy_tx13_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx13_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx13_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx13_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_208_reg {
	struct {
		uint32_t phy_tx13_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx13_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx13_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_209_reg {
	struct {
		uint32_t phy_tx_cmn14_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn14_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn14_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn14_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_210_reg {
	struct {
		uint32_t phy_tx_cmn14_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn14_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn14_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_211_reg {
	struct {
		uint32_t phy_tx14_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx14_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx14_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx14_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_212_reg {
	struct {
		uint32_t phy_tx14_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx14_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx14_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_213_reg {
	struct {
		uint32_t phy_tx_cmn15_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx_cmn15_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx_cmn15_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx_cmn15_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_214_reg {
	struct {
		uint32_t phy_tx_cmn15_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx_cmn15_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx_cmn15_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_215_reg {
	struct {
		uint32_t phy_tx15_cntx_sel_g1:8; /* [7:0] */
		uint32_t phy_tx15_cntx_sel_g2:8; /* [15:8] */
		uint32_t phy_tx15_cntx_sel_g3:8; /* [23:16] */
		uint32_t phy_tx15_cntx_sel_g4:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_216_reg {
	struct {
		uint32_t phy_tx15_cntx_sel_g5:8; /* [7:0] */
		uint32_t phy_tx15_cntx_sel_esm20:8; /* [15:8] */
		uint32_t phy_tx15_cntx_sel_esm25:8; /* [23:16] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_693_reg {
	struct {
		uint32_t phy0_mplla_short_lock_en:1; /* [0:0] */
		uint32_t phy0_mplla_word_clk_en:1; /* [1:1] */
		uint32_t phy0_mpllb_short_lock_en:1; /* [2:2] */
		uint32_t phy0_mpllb_word_clk_en:1; /* [3:3] */
		uint32_t phy0_refa_lane_clk_en:1; /* [4:4] */
		uint32_t phy0_refb_lane_clk_en:1; /* [5:5] */
		uint32_t phy0_refa_clkdet_en:1; /* [6:6] */
		uint32_t phy0_refb_clkdet_en:1; /* [7:7] */
		uint32_t phy0_sram_ecc_en:1; /* [8:8] */
		uint32_t phy0_refa_clk_div2_en:1; /* [9:9] */
		uint32_t phy0_refa_range:4; /* [13:10] */
		uint32_t phy0_refa_raw_clk_div2_en:1; /* [14:14] */
		uint32_t phy0_refb_clk_div2_en:1; /* [15:15] */
		uint32_t phy0_refb_range:4; /* [19:16] */
		uint32_t phy0_refb_raw_clk_div2_en:1; /* [20:20] */
		uint32_t phy0_sup_misc:8; /* [28:21] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_694_reg {
	struct {
		uint32_t phy0_rx_term_offset:5; /* [4:0] */
		uint32_t phy0_txdn_term_offset:9; /* [13:5] */
		uint32_t phy0_txup_term_offset:9; /* [22:14] */
		uint32_t rsvd0:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_695_reg {
	struct {
		uint32_t phy1_mplla_short_lock_en:1; /* [0:0] */
		uint32_t phy1_mplla_word_clk_en:1; /* [1:1] */
		uint32_t phy1_mpllb_short_lock_en:1; /* [2:2] */
		uint32_t phy1_mpllb_word_clk_en:1; /* [3:3] */
		uint32_t phy1_refa_lane_clk_en:1; /* [4:4] */
		uint32_t phy1_refb_lane_clk_en:1; /* [5:5] */
		uint32_t phy1_refa_clkdet_en:1; /* [6:6] */
		uint32_t phy1_refb_clkdet_en:1; /* [7:7] */
		uint32_t phy1_sram_ecc_en:1; /* [8:8] */
		uint32_t phy1_refa_clk_div2_en:1; /* [9:9] */
		uint32_t phy1_refa_range:4; /* [13:10] */
		uint32_t phy1_refa_raw_clk_div2_en:1; /* [14:14] */
		uint32_t phy1_refb_clk_div2_en:1; /* [15:15] */
		uint32_t phy1_refb_range:4; /* [19:16] */
		uint32_t phy1_refb_raw_clk_div2_en:1; /* [20:20] */
		uint32_t phy1_sup_misc:8; /* [28:21] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_696_reg {
	struct {
		uint32_t phy1_rx_term_offset:5; /* [4:0] */
		uint32_t phy1_txdn_term_offset:9; /* [13:5] */
		uint32_t phy1_txup_term_offset:9; /* [22:14] */
		uint32_t rsvd0:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_697_reg {
	struct {
		uint32_t phy2_mplla_short_lock_en:1; /* [0:0] */
		uint32_t phy2_mplla_word_clk_en:1; /* [1:1] */
		uint32_t phy2_mpllb_short_lock_en:1; /* [2:2] */
		uint32_t phy2_mpllb_word_clk_en:1; /* [3:3] */
		uint32_t phy2_refa_lane_clk_en:1; /* [4:4] */
		uint32_t phy2_refb_lane_clk_en:1; /* [5:5] */
		uint32_t phy2_refa_clkdet_en:1; /* [6:6] */
		uint32_t phy2_refb_clkdet_en:1; /* [7:7] */
		uint32_t phy2_sram_ecc_en:1; /* [8:8] */
		uint32_t phy2_refa_clk_div2_en:1; /* [9:9] */
		uint32_t phy2_refa_range:4; /* [13:10] */
		uint32_t phy2_refa_raw_clk_div2_en:1; /* [14:14] */
		uint32_t phy2_refb_clk_div2_en:1; /* [15:15] */
		uint32_t phy2_refb_range:4; /* [19:16] */
		uint32_t phy2_refb_raw_clk_div2_en:1; /* [20:20] */
		uint32_t phy2_sup_misc:8; /* [28:21] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_698_reg {
	struct {
		uint32_t phy2_rx_term_offset:5; /* [4:0] */
		uint32_t phy2_txdn_term_offset:9; /* [13:5] */
		uint32_t phy2_txup_term_offset:9; /* [22:14] */
		uint32_t rsvd0:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_699_reg {
	struct {
		uint32_t phy3_mplla_short_lock_en:1; /* [0:0] */
		uint32_t phy3_mplla_word_clk_en:1; /* [1:1] */
		uint32_t phy3_mpllb_short_lock_en:1; /* [2:2] */
		uint32_t phy3_mpllb_word_clk_en:1; /* [3:3] */
		uint32_t phy3_refa_lane_clk_en:1; /* [4:4] */
		uint32_t phy3_refb_lane_clk_en:1; /* [5:5] */
		uint32_t phy3_refa_clkdet_en:1; /* [6:6] */
		uint32_t phy3_refb_clkdet_en:1; /* [7:7] */
		uint32_t phy3_sram_ecc_en:1; /* [8:8] */
		uint32_t phy3_refa_clk_div2_en:1; /* [9:9] */
		uint32_t phy3_refa_range:4; /* [13:10] */
		uint32_t phy3_refa_raw_clk_div2_en:1; /* [14:14] */
		uint32_t phy3_refb_clk_div2_en:1; /* [15:15] */
		uint32_t phy3_refb_range:4; /* [19:16] */
		uint32_t phy3_refb_raw_clk_div2_en:1; /* [20:20] */
		uint32_t phy3_sup_misc:8; /* [28:21] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_700_reg {
	struct {
		uint32_t phy3_rx_term_offset:5; /* [4:0] */
		uint32_t phy3_txdn_term_offset:9; /* [13:5] */
		uint32_t phy3_txup_term_offset:9; /* [22:14] */
		uint32_t rsvd0:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_701_reg {
	struct {
		uint32_t phy_lane0_ref_sel:1; /* [0:0] */
		uint32_t phy_lane0_refa_clk_en:1; /* [1:1] */
		uint32_t phy_lane0_refb_clk_en:1; /* [2:2] */
		uint32_t phy_lane1_ref_sel:1; /* [3:3] */
		uint32_t phy_lane1_refa_clk_en:1; /* [4:4] */
		uint32_t phy_lane1_refb_clk_en:1; /* [5:5] */
		uint32_t phy_lane2_ref_sel:1; /* [6:6] */
		uint32_t phy_lane2_refa_clk_en:1; /* [7:7] */
		uint32_t phy_lane2_refb_clk_en:1; /* [8:8] */
		uint32_t phy_lane3_ref_sel:1; /* [9:9] */
		uint32_t phy_lane3_refa_clk_en:1; /* [10:10] */
		uint32_t phy_lane3_refb_clk_en:1; /* [11:11] */
		uint32_t phy_lane4_ref_sel:1; /* [12:12] */
		uint32_t phy_lane4_refa_clk_en:1; /* [13:13] */
		uint32_t phy_lane4_refb_clk_en:1; /* [14:14] */
		uint32_t phy_lane5_ref_sel:1; /* [15:15] */
		uint32_t phy_lane5_refa_clk_en:1; /* [16:16] */
		uint32_t phy_lane5_refb_clk_en:1; /* [17:17] */
		uint32_t phy_lane6_ref_sel:1; /* [18:18] */
		uint32_t phy_lane6_refa_clk_en:1; /* [19:19] */
		uint32_t phy_lane6_refb_clk_en:1; /* [20:20] */
		uint32_t phy_lane7_ref_sel:1; /* [21:21] */
		uint32_t phy_lane7_refa_clk_en:1; /* [22:22] */
		uint32_t phy_lane7_refb_clk_en:1; /* [23:23] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_702_reg {
	struct {
		uint32_t phy_lane8_ref_sel:1; /* [0:0] */
		uint32_t phy_lane8_refa_clk_en:1; /* [1:1] */
		uint32_t phy_lane8_refb_clk_en:1; /* [2:2] */
		uint32_t phy_lane9_ref_sel:1; /* [3:3] */
		uint32_t phy_lane9_refa_clk_en:1; /* [4:4] */
		uint32_t phy_lane9_refb_clk_en:1; /* [5:5] */
		uint32_t phy_lane10_ref_sel:1; /* [6:6] */
		uint32_t phy_lane10_refa_clk_en:1; /* [7:7] */
		uint32_t phy_lane10_refb_clk_en:1; /* [8:8] */
		uint32_t phy_lane11_ref_sel:1; /* [9:9] */
		uint32_t phy_lane11_refa_clk_en:1; /* [10:10] */
		uint32_t phy_lane11_refb_clk_en:1; /* [11:11] */
		uint32_t phy_lane12_ref_sel:1; /* [12:12] */
		uint32_t phy_lane12_refa_clk_en:1; /* [13:13] */
		uint32_t phy_lane12_refb_clk_en:1; /* [14:14] */
		uint32_t phy_lane13_ref_sel:1; /* [15:15] */
		uint32_t phy_lane13_refa_clk_en:1; /* [16:16] */
		uint32_t phy_lane13_refb_clk_en:1; /* [17:17] */
		uint32_t phy_lane14_ref_sel:1; /* [18:18] */
		uint32_t phy_lane14_refa_clk_en:1; /* [19:19] */
		uint32_t phy_lane14_refb_clk_en:1; /* [20:20] */
		uint32_t phy_lane15_ref_sel:1; /* [21:21] */
		uint32_t phy_lane15_refa_clk_en:1; /* [22:22] */
		uint32_t phy_lane15_refb_clk_en:1; /* [23:23] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_703_reg {
	struct {
		uint32_t protocol_ext_mplla_recal_bank_sel:2; /* [1:0] */
		uint32_t protocol_ext_mplla_recal_bank_sel_ovrd_en:1; /* [2:2] */
		uint32_t protocol_ext_mpllb_recal_bank_sel:2; /* [4:3] */
		uint32_t protocol_ext_mpllb_recal_bank_sel_ovrd_en:1; /* [5:5] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_704_reg {
	struct {
		uint32_t protocol_ext_phy0_mplla_tx_clk_div:4; /* [3:0] */
		uint32_t protocol_ext_phy0_mplla_tx_clk_div_ovrd_en:1; /* [4:4] */
		uint32_t protocol_ext_phy0_mpllb_tx_clk_div:4; /* [8:5] */
		uint32_t protocol_ext_phy0_mpllb_tx_clk_div_ovrd_en:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_705_reg {
	struct {
		uint32_t protocol_ext_phy0_mplla_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy0_mplla_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_706_reg {
	struct {
		uint32_t protocol_ext_phy0_mpllb_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy0_mpllb_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_707_reg {
	struct {
		uint32_t protocol_ext_phy0_mplla_bw_threshold:8; /* [7:0] */
		uint32_t protocol_ext_phy0_mpllb_bw_threshold:8; /* [15:8] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_708_reg {
	struct {
		uint32_t protocol_ext_phy1_mplla_tx_clk_div:4; /* [3:0] */
		uint32_t protocol_ext_phy1_mplla_tx_clk_div_ovrd_en:1; /* [4:4] */
		uint32_t protocol_ext_phy1_mpllb_tx_clk_div:4; /* [8:5] */
		uint32_t protocol_ext_phy1_mpllb_tx_clk_div_ovrd_en:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_709_reg {
	struct {
		uint32_t protocol_ext_phy1_mplla_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy1_mplla_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_710_reg {
	struct {
		uint32_t protocol_ext_phy1_mpllb_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy1_mpllb_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_711_reg {
	struct {
		uint32_t protocol_ext_phy1_mplla_bw_threshold:8; /* [7:0] */
		uint32_t protocol_ext_phy1_mpllb_bw_threshold:8; /* [15:8] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_712_reg {
	struct {
		uint32_t protocol_ext_phy2_mplla_tx_clk_div:4; /* [3:0] */
		uint32_t protocol_ext_phy2_mplla_tx_clk_div_ovrd_en:1; /* [4:4] */
		uint32_t protocol_ext_phy2_mpllb_tx_clk_div:4; /* [8:5] */
		uint32_t protocol_ext_phy2_mpllb_tx_clk_div_ovrd_en:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_713_reg {
	struct {
		uint32_t protocol_ext_phy2_mplla_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy2_mplla_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_714_reg {
	struct {
		uint32_t protocol_ext_phy2_mpllb_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy2_mpllb_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_715_reg {
	struct {
		uint32_t protocol_ext_phy2_mplla_bw_threshold:8; /* [7:0] */
		uint32_t protocol_ext_phy2_mpllb_bw_threshold:8; /* [15:8] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_716_reg {
	struct {
		uint32_t protocol_ext_phy3_mplla_tx_clk_div:4; /* [3:0] */
		uint32_t protocol_ext_phy3_mplla_tx_clk_div_ovrd_en:1; /* [4:4] */
		uint32_t protocol_ext_phy3_mpllb_tx_clk_div:4; /* [8:5] */
		uint32_t protocol_ext_phy3_mpllb_tx_clk_div_ovrd_en:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_717_reg {
	struct {
		uint32_t protocol_ext_phy3_mplla_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy3_mplla_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_718_reg {
	struct {
		uint32_t protocol_ext_phy3_mpllb_bw_high:16; /* [15:0] */
		uint32_t protocol_ext_phy3_mpllb_bw_low:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_719_reg {
	struct {
		uint32_t protocol_ext_phy3_mplla_bw_threshold:8; /* [7:0] */
		uint32_t protocol_ext_phy3_mpllb_bw_threshold:8; /* [15:8] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_720_reg {
	struct {
		uint32_t protocol_ext_tx_ropll_postdiv_ovrd_en:16; /* [15:0] */
		uint32_t protocol_ext_tx_ropll_refdiv_ovrd_en:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_721_reg {
	struct {
		uint32_t protocol_ext_tx_ropll_word_clk_div_sel_ovrd_en:8; /* [7:0] */
		uint32_t protocol_ext_rx_eq_afe_ovrd_en:1; /* [8:8] */
		uint32_t protocol_ext_rx_misc_ovrd_en:1; /* [9:9] */
		uint32_t protocol_ext_tx_ropll_ovrd_en:1; /* [10:10] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_722_reg {
	struct {
		uint32_t pipe_lane0_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane0_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane0_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane0_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane0_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_723_reg {
	struct {
		uint32_t pipe_lane1_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane1_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane1_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane1_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane1_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_724_reg {
	struct {
		uint32_t pipe_lane2_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane2_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane2_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane2_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane2_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_725_reg {
	struct {
		uint32_t pipe_lane3_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane3_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane3_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane3_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane3_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_726_reg {
	struct {
		uint32_t pipe_lane4_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane4_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane4_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane4_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane4_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_727_reg {
	struct {
		uint32_t pipe_lane5_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane5_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane5_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane5_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane5_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_728_reg {
	struct {
		uint32_t pipe_lane6_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane6_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane6_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane6_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane6_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_729_reg {
	struct {
		uint32_t pipe_lane7_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane7_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane7_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane7_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane7_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_730_reg {
	struct {
		uint32_t pipe_lane8_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane8_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane8_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane8_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane8_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_731_reg {
	struct {
		uint32_t pipe_lane9_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane9_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane9_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane9_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane9_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_732_reg {
	struct {
		uint32_t pipe_lane10_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane10_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane10_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane10_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane10_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_733_reg {
	struct {
		uint32_t pipe_lane11_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane11_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane11_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane11_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane11_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_734_reg {
	struct {
		uint32_t pipe_lane12_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane12_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane12_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane12_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane12_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_735_reg {
	struct {
		uint32_t pipe_lane13_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane13_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane13_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane13_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane13_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_736_reg {
	struct {
		uint32_t pipe_lane14_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane14_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane14_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane14_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane14_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_737_reg {
	struct {
		uint32_t pipe_lane15_tx2rx_loopbk:1; /* [0:0] */
		uint32_t pipe_lane15_cascaded_mpllb_sel:1; /* [1:1] */
		uint32_t pipe_lane15_lanepll_bypass_mode:5; /* [6:2] */
		uint32_t pipe_lane15_lanepll_src_sel:4; /* [10:7] */
		uint32_t pipe_lane15_destruct_rxmargin_mode:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_738_reg {
	struct {
		uint32_t phy0_refa_clkdet_result:1; /* [0:0] */
		uint32_t phy0_refb_clkdet_result:1; /* [1:1] */
		uint32_t phy0_dtb_out:2; /* [3:2] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_739_reg {
	struct {
		uint32_t phy1_refa_clkdet_result:1; /* [0:0] */
		uint32_t phy1_refb_clkdet_result:1; /* [1:1] */
		uint32_t phy1_dtb_out:2; /* [3:2] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_740_reg {
	struct {
		uint32_t phy2_refa_clkdet_result:1; /* [0:0] */
		uint32_t phy2_refb_clkdet_result:1; /* [1:1] */
		uint32_t phy2_dtb_out:2; /* [3:2] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_741_reg {
	struct {
		uint32_t phy3_refa_clkdet_result:1; /* [0:0] */
		uint32_t phy3_refb_clkdet_result:1; /* [1:1] */
		uint32_t phy3_dtb_out:2; /* [3:2] */
		uint32_t phy_res_ack_out:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_742_reg {
	struct {
		uint32_t cfg_neg_link_width:6; /* [5:0] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_flr_pf_done {
	struct {
		uint32_t app_flr_pf_done:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_flr_vf_done {
	struct {
		uint32_t app_flr_vf_done:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbg_pba {
	struct {
		uint32_t dbg_pba:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbg_table {
	struct {
		uint32_t dbg_table:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_pad_perst_n {
	struct {
		uint32_t irq_pad_perst_n_rise:1; /* [0:0] */
		uint32_t irq_pad_perst_n_fall:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_pad_perst_n {
	struct {
		uint32_t irq_en_pad_perst_n_rise:1; /* [0:0] */
		uint32_t irq_en_pad_perst_n_fall:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_reset {
	struct {
		uint32_t irq_smlh_req_rst_not:1; /* [0:0] */
		uint32_t irq_link_req_rst_not:1; /* [1:1] */
		uint32_t irq_flr_pf:1; /* [2:2] */
		uint32_t irq_flr_vf:16; /* [18:3] */
		uint32_t irq_core_rst_n_assert:1; /* [19:19] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_reset_en {
	struct {
		uint32_t irq_en_smlh_req_rst_not:1; /* [0:0] */
		uint32_t irq_en_link_req_rst_not:1; /* [1:1] */
		uint32_t irq_en_flr_pf:1; /* [2:2] */
		uint32_t irq_en_flr_vf:16; /* [18:3] */
		uint32_t irq_en_core_rst_n_assert:1; /* [19:19] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_int_cm7 {
	struct {
		uint32_t edma_int_cm7; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_int_ca73 {
	struct {
		uint32_t edma_int_ca73; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_bw_changed {
	struct {
		uint32_t irq_cfg_neg_link_width_changed:1; /* [0:0] */
		uint32_t irq_pm_current_data_rate_changed:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_bw_changed {
	struct {
		uint32_t irq_en_cfg_neg_link_width_changed:1; /* [0:0] */
		uint32_t irq_en_pm_current_data_rate_changed:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_rbar_changed {
	struct {
		uint32_t rbar_ctrl_update:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_rbar_changed {
	struct {
		uint32_t irq_en_rbar_ctrl_update:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_vf_rbar_changed {
	struct {
		uint32_t vf_rbar_ctrl_update:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_vf_rbar_changed {
	struct {
		uint32_t irq_en_vf_rbar_ctrl_update:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_app_parity_err {
	struct {
		uint32_t app_parity_err:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_app_parity_err {
	struct {
		uint32_t irq_en_app_parity_err:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_ram_parity_err_0 {
	struct {
		uint32_t err_multpl_ib_rreq_ordr_ram_addra:1; /* [0:0] */
		uint32_t err_multpl_ib_rreq_ordr_ram_addrb:1; /* [1:1] */
		uint32_t err_multpl_ib_rreq_c2a_cdc_ram_addra:1; /* [2:2] */
		uint32_t err_multpl_ib_rreq_c2a_cdc_ram_addrb:1; /* [3:3] */
		uint32_t err_multpl_ib_wreq_c2a_cdc_ram_addra:1; /* [4:4] */
		uint32_t err_multpl_ib_wreq_c2a_cdc_ram_addrb:1; /* [5:5] */
		uint32_t err_multpl_ib_mcpl_sb_ram_addra:1; /* [6:6] */
		uint32_t err_multpl_ib_mcpl_sb_ram_addrb:1; /* [7:7] */
		uint32_t err_multpl_ib_mcpl_a2c_cdc_ram_addra:1; /* [8:8] */
		uint32_t err_multpl_ib_mcpl_a2c_cdc_ram_addrb:1; /* [9:9] */
		uint32_t err_multpl_slv_npw_sab_ram_addra:1; /* [10:10] */
		uint32_t err_multpl_slv_npw_sab_ram_addrb:1; /* [11:11] */
		uint32_t err_multpl_ob_npdcmp_ram_addra:1; /* [12:12] */
		uint32_t err_multpl_ob_npdcmp_ram_addrb:1; /* [13:13] */
		uint32_t err_multpl_ob_pdcmp_hdr_ram_addra:1; /* [14:14] */
		uint32_t err_multpl_ob_pdcmp_hdr_ram_addrb:1; /* [15:15] */
		uint32_t err_multpl_ob_pdcmp_data_ram_addra:1; /* [16:16] */
		uint32_t err_multpl_ob_pdcmp_data_ram_addrb:1; /* [17:17] */
		uint32_t err_multpl_ob_ccmp_data_ram_addra:1; /* [18:18] */
		uint32_t err_multpl_ob_ccmp_data_ram_addrb:1; /* [19:19] */
		uint32_t err_multpl_edmarbuff2ram_addra:1; /* [20:20] */
		uint32_t err_multpl_edmarbuff2ram_addrb:1; /* [21:21] */
		uint32_t err_multpl_edma_rd_eng_ll_addra_ram:1; /* [22:22] */
		uint32_t err_multpl_edma_rd_eng_ll_addrb_ram:1; /* [23:23] */
		uint32_t err_multpl_edma_rd_eng_ovrl_addra_ram:1; /* [24:24] */
		uint32_t err_multpl_edma_rd_eng_ovrl_addrb_ram:1; /* [25:25] */
		uint32_t err_multpl_edma_rd_eng_c2w_lut_addra_ram:1; /* [26:26] */
		uint32_t err_multpl_edma_rd_eng_c2w_lut_addrb_ram:1; /* [27:27] */
		uint32_t err_multpl_edma_rd_eng_stsh_lut_addra_ram:1; /* [28:28] */
		uint32_t err_multpl_edma_rd_eng_stsh_lut_addrb_ram:1; /* [29:29] */
		uint32_t err_multpl_edma_rd_eng_msi_addra_ram:1; /* [30:30] */
		uint32_t err_multpl_edma_rd_eng_msi_addrb_ram:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_ram_parity_err_1 {
	struct {
		uint32_t err_multpl_edma_wr_eng_ll_addra_ram:1; /* [0:0] */
		uint32_t err_multpl_edma_wr_eng_ll_addrb_ram:1; /* [1:1] */
		uint32_t err_multpl_edma_wr_eng_ovrl_addra_ram:1; /* [2:2] */
		uint32_t err_multpl_edma_wr_eng_ovrl_addrb_ram:1; /* [3:3] */
		uint32_t err_multpl_edma_wr_eng_c2w_lut_addra_ram:1; /* [4:4] */
		uint32_t err_multpl_edma_wr_eng_c2w_lut_addrb_ram:1; /* [5:5] */
		uint32_t err_multpl_edma_wr_eng_stsh_lut_addra_ram:1; /* [6:6] */
		uint32_t err_multpl_edma_wr_eng_stsh_lut_addrb_ram:1; /* [7:7] */
		uint32_t err_multpl_edma_wr_eng_msi_addra_ram:1; /* [8:8] */
		uint32_t err_multpl_edma_wr_eng_msi_addrb_ram:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_ram_parity_err_0 {
	struct {
		uint32_t irq_en_err_multpl_ib_rreq_ordr_ram_addra:1; /* [0:0] */
		uint32_t irq_en_err_multpl_ib_rreq_ordr_ram_addrb:1; /* [1:1] */
		uint32_t irq_en_err_multpl_ib_rreq_c2a_cdc_ram_addra:1; /* [2:2] */
		uint32_t irq_en_err_multpl_ib_rreq_c2a_cdc_ram_addrb:1; /* [3:3] */
		uint32_t irq_en_err_multpl_ib_wreq_c2a_cdc_ram_addra:1; /* [4:4] */
		uint32_t irq_en_err_multpl_ib_wreq_c2a_cdc_ram_addrb:1; /* [5:5] */
		uint32_t irq_en_err_multpl_ib_mcpl_sb_ram_addra:1; /* [6:6] */
		uint32_t irq_en_err_multpl_ib_mcpl_sb_ram_addrb:1; /* [7:7] */
		uint32_t irq_en_err_multpl_ib_mcpl_a2c_cdc_ram_addra:1; /* [8:8] */
		uint32_t irq_en_err_multpl_ib_mcpl_a2c_cdc_ram_addrb:1; /* [9:9] */
		uint32_t irq_en_err_multpl_slv_npw_sab_ram_addra:1; /* [10:10] */
		uint32_t irq_en_err_multpl_slv_npw_sab_ram_addrb:1; /* [11:11] */
		uint32_t irq_en_err_multpl_ob_npdcmp_ram_addra:1; /* [12:12] */
		uint32_t irq_en_err_multpl_ob_npdcmp_ram_addrb:1; /* [13:13] */
		uint32_t irq_en_err_multpl_ob_pdcmp_hdr_ram_addra:1; /* [14:14] */
		uint32_t irq_en_err_multpl_ob_pdcmp_hdr_ram_addrb:1; /* [15:15] */
		uint32_t irq_en_err_multpl_ob_pdcmp_data_ram_addra:1; /* [16:16] */
		uint32_t irq_en_err_multpl_ob_pdcmp_data_ram_addrb:1; /* [17:17] */
		uint32_t irq_en_err_multpl_ob_ccmp_data_ram_addra:1; /* [18:18] */
		uint32_t irq_en_err_multpl_ob_ccmp_data_ram_addrb:1; /* [19:19] */
		uint32_t irq_en_err_multpl_edmarbuff2ram_addra:1; /* [20:20] */
		uint32_t irq_en_err_multpl_edmarbuff2ram_addrb:1; /* [21:21] */
		uint32_t irq_en_err_multpl_edma_rd_eng_ll_addra_ram:1; /* [22:22] */
		uint32_t irq_en_err_multpl_edma_rd_eng_ll_addrb_ram:1; /* [23:23] */
		uint32_t irq_en_err_multpl_edma_rd_eng_ovrl_addra_ram:1; /* [24:24] */
		uint32_t irq_en_err_multpl_edma_rd_eng_ovrl_addrb_ram:1; /* [25:25] */
		uint32_t irq_en_err_multpl_edma_rd_eng_c2w_lut_addra_ram:1; /* [26:26] */
		uint32_t irq_en_err_multpl_edma_rd_eng_c2w_lut_addrb_ram:1; /* [27:27] */
		uint32_t irq_en_err_multpl_edma_rd_eng_stsh_lut_addra_ram:1; /* [28:28] */
		uint32_t irq_en_err_multpl_edma_rd_eng_stsh_lut_addrb_ram:1; /* [29:29] */
		uint32_t irq_en_err_multpl_edma_rd_eng_msi_addra_ram:1; /* [30:30] */
		uint32_t irq_en_err_multpl_edma_rd_eng_msi_addrb_ram:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_ram_parity_err_1 {
	struct {
		uint32_t irq_en_err_multpl_edma_wr_eng_ll_addra_ram:1; /* [0:0] */
		uint32_t irq_en_err_multpl_edma_wr_eng_ll_addrb_ram:1; /* [1:1] */
		uint32_t irq_en_err_multpl_edma_wr_eng_ovrl_addra_ram:1; /* [2:2] */
		uint32_t irq_en_err_multpl_edma_wr_eng_ovrl_addrb_ram:1; /* [3:3] */
		uint32_t irq_en_err_multpl_edma_wr_eng_c2w_lut_addra_ram:1; /* [4:4] */
		uint32_t irq_en_err_multpl_edma_wr_eng_c2w_lut_addrb_ram:1; /* [5:5] */
		uint32_t irq_en_err_multpl_edma_wr_eng_stsh_lut_addra_ram:1; /* [6:6] */
		uint32_t irq_en_err_multpl_edma_wr_eng_stsh_lut_addrb_ram:1; /* [7:7] */
		uint32_t irq_en_err_multpl_edma_wr_eng_msi_addra_ram:1; /* [8:8] */
		uint32_t irq_en_err_multpl_edma_wr_eng_msi_addrb_ram:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_axi_parity_err {
	struct {
		uint32_t err_multpl_mstr_awaddr:1; /* [0:0] */
		uint32_t err_multpl_mstr_wdata:1; /* [1:1] */
		uint32_t err_multpl_mstr_araddr:1; /* [2:2] */
		uint32_t err_multpl_mstr_awmisc_info_tlpprfx:1; /* [3:3] */
		uint32_t err_multpl_mstr_armisc_info_tlpprfx:1; /* [4:4] */
		uint32_t err_multpl_slv_rdata:1; /* [5:5] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_axi_parity_err {
	struct {
		uint32_t irq_en_err_multpl_mstr_awaddr:1; /* [0:0] */
		uint32_t irq_en_err_multpl_mstr_wdata:1; /* [1:1] */
		uint32_t irq_en_err_multpl_mstr_araddr:1; /* [2:2] */
		uint32_t irq_en_err_multpl_mstr_awmisc_info_tlpprfx:1; /* [3:3] */
		uint32_t irq_en_err_multpl_mstr_armisc_info_tlpprfx:1; /* [4:4] */
		uint32_t irq_en_err_multpl_slv_rdata:1; /* [5:5] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_trgt1_atu_cbuf_err_31_0 {
	struct {
		uint32_t radm_trgt1_atu_cbuf_err_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_trgt1_atu_cbuf_err_63_32 {
	struct {
		uint32_t radm_trgt1_atu_cbuf_err_64_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_cbuf_err {
	struct {
		uint32_t cbuf_err:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_cbuf_err {
	struct {
		uint32_t irq_en_cbuf_err:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_elbi_rst {
	struct {
		uint32_t elbi_rst:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_irq_en_elbi_rst {
	struct {
		uint32_t irq_en_elbi_rst:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_perstn_control {
	struct {
		uint32_t pad_perstn_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_hotreset_control {
	struct {
		uint32_t hotreset_global_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_hotreset {
	struct {
		uint32_t global_hotreset:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mask_control {
	struct {
		uint32_t req_rst_not_ltssm_enable_mask:1; /* [0:0] */
		uint32_t core_rst_n_ltssm_enable_mask:1; /* [1:1] */
		uint32_t req_rst_not_retry_en_mask:1; /* [2:2] */
		uint32_t flr_pf_active_pf_retry_en_mask:1; /* [3:3] */
		uint32_t flr_pf_active_vf_retry_en_mask:16; /* [19:4] */
		uint32_t perst_n_ltssm_enable_mask:1; /* [20:20] */
		uint32_t perst_n_retry_en_mask:1; /* [21:21] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_prs {
	struct {
		uint32_t prs_stopped:1; /* [0:0] */
		uint32_t prs_res_failure:1; /* [1:1] */
		uint32_t prs_uprgi:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_poisoned_type {
	struct {
		uint32_t radm_rcvd_cfg0wr_poisoned:1; /* [0:0] */
		uint32_t radm_rcvd_cfg1wr_poisoned:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_poisoned_detect {
	struct {
		uint32_t radm_rcvd_cfgwr_poisoned_ext_reg_num:4; /* [3:0] */
		uint32_t radm_rcvd_cfgwr_poisoned_reg_num:6; /* [9:4] */
		uint32_t radm_rcvd_cfgwr_poisoned_func_num:1; /* [10:10] */
		uint32_t radm_rcvd_cfgwr_poisoned_is_vf:1; /* [11:11] */
		uint32_t radm_rcvd_cfgwr_poisoned_vfunc_num:4; /* [15:12] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pcie_ras_des_sd_dbg_signal {
	struct {
		uint32_t pcie_ras_des_sd_dbg_signal; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ras_des_sel {
	struct {
		uint32_t ras_des_sd_selection:5; /* [4:0] */
		uint32_t ras_des_sd_data_sel:3; /* [7:5] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pcie_dbg_signal {
	struct {
		uint32_t pcie_dbg_signal; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_tdi_state_pf {
	struct {
		uint32_t app_tdi_state_pf:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_tdi_state_vf_31_0 {
	struct {
		uint32_t app_tdi_state_vf_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_tdi_state_vf_47_32 {
	struct {
		uint32_t app_tdi_state_vf_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_misc_info_t_bit {
	struct {
		uint32_t mstr_awmisc_info_t_bit:1; /* [0:0] */
		uint32_t mstr_armisc_info_t_bit:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_pm_sel_aux_clk_ovrd {
	struct {
		uint32_t pm_sel_aux_clk_ovrd:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_nw {
	struct {
		uint32_t mstr_armisc_info_nw:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_ats {
	struct {
		uint32_t mstr_armisc_info_ats:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_tph {
	struct {
		uint32_t mstr_armisc_info_tph:11; /* [10:0] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_31_0 {
	struct {
		uint32_t mstr_armisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_63_32 {
	struct {
		uint32_t mstr_armisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_71_64 {
	struct {
		uint32_t mstr_armisc_info_tlpprfx_71_64:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_armisc_info_ido {
	struct {
		uint32_t mstr_armisc_info_ido:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_nw {
	struct {
		uint32_t mstr_awmisc_info_nw:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_ats {
	struct {
		uint32_t mstr_awmisc_info_ats:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_tph {
	struct {
		uint32_t mstr_awmisc_info_tph:11; /* [10:0] */
		uint32_t rsvd0:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_31_0 {
	struct {
		uint32_t mstr_awmisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_63_32 {
	struct {
		uint32_t mstr_awmisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_71_64 {
	struct {
		uint32_t mstr_awmisc_info_tlpprfx_71_64:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mstr_awmisc_info_ido {
	struct {
		uint32_t mstr_awmisc_info_ido:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_misc_info_t_bit {
	struct {
		uint32_t slv_awmisc_info_t_bit:1; /* [0:0] */
		uint32_t slv_armisc_info_t_bit:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_dbi_misc_info_t_bit {
	struct {
		uint32_t dbi_awmisc_info_t_bit:1; /* [0:0] */
		uint32_t dbi_armisc_info_t_bit:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_0 {
	struct {
		uint32_t slv_bmisc_info_tlpprfx_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_1 {
	struct {
		uint32_t slv_bmisc_info_tlpprfx_1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_2 {
	struct {
		uint32_t slv_bmisc_info_tlpprfx_2:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_0 {
	struct {
		uint32_t slv_rmisc_info_tlpprfx_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_1 {
	struct {
		uint32_t slv_rmisc_info_tlpprfx_1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_2 {
	struct {
		uint32_t slv_rmisc_info_tlpprfx_2:8; /* [7:0] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_app_send_stream_to_insecure {
	struct {
		uint32_t app_send_stream_to_insecure:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_wr_eng_hard_stop {
	struct {
		uint32_t edma_wr_eng_hard_stop_req:1; /* [0:0] */
		uint32_t edma_wr_eng_hard_stop_channel:4; /* [4:1] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_rd_eng_hard_stop {
	struct {
		uint32_t edma_rd_eng_hard_stop_req:1; /* [0:0] */
		uint32_t edma_rd_eng_hard_stop_channel:4; /* [4:1] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_irq_out {
	struct {
		uint32_t ide_glb_irq_out:1; /* [0:0] */
		uint32_t ide_aes_hcfg_irq_out:3; /* [3:1] */
		uint32_t detected_write_access_out:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_radm_rcvd {
	struct {
		uint32_t radm_rcvd_ats_translation_cpl_tbit_clear_pf:1; /* [0:0] */
		uint32_t radm_rcvd_ats_translation_cpl_tbit_clear_vf:1; /* [1:1] */
		uint32_t radm_rcvd_cpl_ca_pf:1; /* [2:2] */
		uint32_t radm_rcvd_cpl_ca_vf:1; /* [3:3] */
		uint32_t radm_rcvd_cpl_not_in_run_pf:1; /* [4:4] */
		uint32_t radm_rcvd_cpl_not_in_run_vf:1; /* [5:5] */
		uint32_t radm_rcvd_cpl_poisoned_pf:1; /* [6:6] */
		uint32_t radm_rcvd_cpl_poisoned_vf:1; /* [7:7] */
		uint32_t radm_rcvd_cpl_ur_pf:1; /* [8:8] */
		uint32_t radm_rcvd_cpl_ur_vf:1; /* [9:9] */
		uint32_t radm_rcvd_wreq_poisoned_pf:1; /* [10:10] */
		uint32_t radm_rcvd_wreq_poisoned_vf:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_en_radm_rcvd {
	struct {
		uint32_t radm_rcvd_ats_translation_cpl_tbit_clear_pf:1; /* [0:0] */
		uint32_t radm_rcvd_ats_translation_cpl_tbit_clear_vf:1; /* [1:1] */
		uint32_t radm_rcvd_cpl_ca_pf:1; /* [2:2] */
		uint32_t radm_rcvd_cpl_ca_vf:1; /* [3:3] */
		uint32_t radm_rcvd_cpl_not_in_run_pf:1; /* [4:4] */
		uint32_t radm_rcvd_cpl_not_in_run_vf:1; /* [5:5] */
		uint32_t radm_rcvd_cpl_poisoned_pf:1; /* [6:6] */
		uint32_t radm_rcvd_cpl_poisoned_vf:1; /* [7:7] */
		uint32_t radm_rcvd_cpl_ur_pf:1; /* [8:8] */
		uint32_t radm_rcvd_cpl_ur_vf:1; /* [9:9] */
		uint32_t radm_rcvd_wreq_poisoned_pf:1; /* [10:10] */
		uint32_t radm_rcvd_wreq_poisoned_vf:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_rcvd_num {
	struct {
		uint32_t radm_rcvd_err_func_num:1; /* [0:0] */
		uint32_t radm_rcvd_err_vfunc_num:4; /* [4:1] */
		uint32_t radm_rcvd_err_vfindex:4; /* [8:5] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_radm_vendor_msg_type {
	struct {
		uint32_t radm_vendor_msg_type:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sw_rst_n {
	struct {
		uint32_t sw_phy_rst_n:1; /* [0:0] */
		uint32_t sw_core_rst_n:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_radm_trgt1_atu_sloc_match_31_0 {
	struct {
		uint32_t radm_trgt1_atu_sloc_match_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_radm_trgt1_atu_sloc_match_63_32 {
	struct {
		uint32_t radm_trgt1_atu_sloc_match_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_en_radm_trgt1_atu_sloc_match_31_0 {
	struct {
		uint32_t irq_en_radm_trgt1_atu_sloc_match_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_irq_en_radm_trgt1_atu_sloc_match_63_32 {
	struct {
		uint32_t irq_en_radm_trgt1_atu_sloc_match_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_0 {
	struct {
		uint32_t _cbuf_error_cnt_0_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_1 {
	struct {
		uint32_t _cbuf_error_cnt_1_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_2 {
	struct {
		uint32_t _cbuf_error_cnt_2_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_3 {
	struct {
		uint32_t _cbuf_error_cnt_3_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_4 {
	struct {
		uint32_t _cbuf_error_cnt_4_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_5 {
	struct {
		uint32_t _cbuf_error_cnt_5_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_6 {
	struct {
		uint32_t _cbuf_error_cnt_6_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_7 {
	struct {
		uint32_t _cbuf_error_cnt_7_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_8 {
	struct {
		uint32_t _cbuf_error_cnt_8_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_9 {
	struct {
		uint32_t _cbuf_error_cnt_9_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_10 {
	struct {
		uint32_t _cbuf_error_cnt_10_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_11 {
	struct {
		uint32_t _cbuf_error_cnt_11_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_12 {
	struct {
		uint32_t _cbuf_error_cnt_12_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_13 {
	struct {
		uint32_t _cbuf_error_cnt_13_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_14 {
	struct {
		uint32_t _cbuf_error_cnt_14_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_15 {
	struct {
		uint32_t _cbuf_error_cnt_15_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_16 {
	struct {
		uint32_t _cbuf_error_cnt_16_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_17 {
	struct {
		uint32_t _cbuf_error_cnt_17_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_18 {
	struct {
		uint32_t _cbuf_error_cnt_18_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_19 {
	struct {
		uint32_t _cbuf_error_cnt_19_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_20 {
	struct {
		uint32_t _cbuf_error_cnt_20_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_21 {
	struct {
		uint32_t _cbuf_error_cnt_21_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_22 {
	struct {
		uint32_t _cbuf_error_cnt_22_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_23 {
	struct {
		uint32_t _cbuf_error_cnt_23_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_24 {
	struct {
		uint32_t _cbuf_error_cnt_24_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_25 {
	struct {
		uint32_t _cbuf_error_cnt_25_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_26 {
	struct {
		uint32_t _cbuf_error_cnt_26_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_27 {
	struct {
		uint32_t _cbuf_error_cnt_27_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_28 {
	struct {
		uint32_t _cbuf_error_cnt_28_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_29 {
	struct {
		uint32_t _cbuf_error_cnt_29_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_30 {
	struct {
		uint32_t _cbuf_error_cnt_30_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_31 {
	struct {
		uint32_t _cbuf_error_cnt_31_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_32 {
	struct {
		uint32_t _cbuf_error_cnt_32_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_33 {
	struct {
		uint32_t _cbuf_error_cnt_33_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_34 {
	struct {
		uint32_t _cbuf_error_cnt_34_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_35 {
	struct {
		uint32_t _cbuf_error_cnt_35_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_36 {
	struct {
		uint32_t _cbuf_error_cnt_36_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_37 {
	struct {
		uint32_t _cbuf_error_cnt_37_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_38 {
	struct {
		uint32_t _cbuf_error_cnt_38_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_39 {
	struct {
		uint32_t _cbuf_error_cnt_39_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_40 {
	struct {
		uint32_t _cbuf_error_cnt_40_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_41 {
	struct {
		uint32_t _cbuf_error_cnt_41_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_42 {
	struct {
		uint32_t _cbuf_error_cnt_42_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_43 {
	struct {
		uint32_t _cbuf_error_cnt_43_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_44 {
	struct {
		uint32_t _cbuf_error_cnt_44_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_45 {
	struct {
		uint32_t _cbuf_error_cnt_45_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_46 {
	struct {
		uint32_t _cbuf_error_cnt_46_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_47 {
	struct {
		uint32_t _cbuf_error_cnt_47_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_48 {
	struct {
		uint32_t _cbuf_error_cnt_48_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_49 {
	struct {
		uint32_t _cbuf_error_cnt_49_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_50 {
	struct {
		uint32_t _cbuf_error_cnt_50_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_51 {
	struct {
		uint32_t _cbuf_error_cnt_51_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_52 {
	struct {
		uint32_t _cbuf_error_cnt_52_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_53 {
	struct {
		uint32_t _cbuf_error_cnt_53_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_54 {
	struct {
		uint32_t _cbuf_error_cnt_54_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_55 {
	struct {
		uint32_t _cbuf_error_cnt_55_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_56 {
	struct {
		uint32_t _cbuf_error_cnt_56_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_57 {
	struct {
		uint32_t _cbuf_error_cnt_57_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_58 {
	struct {
		uint32_t _cbuf_error_cnt_58_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_59 {
	struct {
		uint32_t _cbuf_error_cnt_59_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_60 {
	struct {
		uint32_t _cbuf_error_cnt_60_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_61 {
	struct {
		uint32_t _cbuf_error_cnt_61_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_62 {
	struct {
		uint32_t _cbuf_error_cnt_62_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cbuf_error_cnt_63 {
	struct {
		uint32_t _cbuf_error_cnt_63_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_training_rst_n_fall {
	struct {
		uint32_t training_rst_n_fall:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_smlh_link_disable_rise {
	struct {
		uint32_t smlh_link_disable_rise:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy0_sup_misc {
	struct {
		uint32_t phy0_sup_misc:24; /* [23:0] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy1_sup_misc {
	struct {
		uint32_t phy1_sup_misc:24; /* [23:0] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy2_sup_misc {
	struct {
		uint32_t phy2_sup_misc:24; /* [23:0] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy3_sup_misc {
	struct {
		uint32_t phy3_sup_misc:24; /* [23:0] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_514c_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5150_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5154_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5158_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_515c_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5160_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5164_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5168_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r0_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_516c_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5170_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5174_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5178_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_517c_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5180_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5184_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5188_reg {
	struct {
		uint32_t protocol0_esm_ext_rx_misc_r1_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_518c_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5190_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5194_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5198_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_519c_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51a0_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51a4_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51a8_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r0_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51ac_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51b0_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51b4_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51b8_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51bc_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51c0_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51c4_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51c8_reg {
	struct {
		uint32_t protocol0_esm_ext_tx_misc_r1_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51cc_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51d0_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51d4_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51d8_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51dc_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51e0_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51e4_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51e8_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g1_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51ec_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51f0_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51f4_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51f8_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_51fc_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5200_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5204_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5208_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g2_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_520c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5210_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5214_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5218_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_521c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5220_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5224_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5228_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g3_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_522c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5230_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5234_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5238_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_523c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5240_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5244_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5248_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g4_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_524c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5250_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5254_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5258_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_525c_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5260_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5264_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5268_reg {
	struct {
		uint32_t protocol0_ext_rx_misc_g5_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_526c_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5270_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5274_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5278_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_527c_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5280_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5284_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5288_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g1_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_528c_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5290_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5294_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5298_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_529c_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52a0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52a4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52a8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g2_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52ac_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52b0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52b4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52b8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52bc_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52c0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52c4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52c8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g3_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52cc_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52d0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52d4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52d8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52dc_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52e0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52e4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52e8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g4_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52ec_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_159_128; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52f0_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_191_160; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52f4_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_223_192; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52f8_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_255_224; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_52fc_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_287_256; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5300_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_319_288; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5304_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_351_320; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_cfg_5308_reg {
	struct {
		uint32_t protocol0_ext_tx_misc_g5_383_352; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_upcs_mpll_ssc_sync_mode {
	struct {
		uint32_t upcs_mpll_ssc_sync_mode:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_phy_sram_ded_sec_sticky_status {
	struct {
		uint32_t phy0_sram_ded_sticky_status:1; /* [0:0] */
		uint32_t phy0_sram_sec_sticky_status:1; /* [1:1] */
		uint32_t phy1_sram_ded_sticky_status:1; /* [2:2] */
		uint32_t phy1_sram_sec_sticky_status:1; /* [3:3] */
		uint32_t phy2_sram_ded_sticky_status:1; /* [4:4] */
		uint32_t phy2_sram_sec_sticky_status:1; /* [5:5] */
		uint32_t phy3_sram_ded_sticky_status:1; /* [6:6] */
		uint32_t phy3_sram_sec_sticky_status:1; /* [7:7] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_ido_req_cpl_en {
	struct {
		uint32_t cfg_ido_req_en:1; /* [0:0] */
		uint32_t cfg_ido_cpl_en:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_pf_tph_st_mode {
	struct {
		uint32_t cfg_pf_tph_st_mode:3; /* [2:0] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_tph_st_mode_31_0 {
	struct {
		uint32_t cfg_vf_tph_st_mode_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_cfg_vf_tph_st_mode_47_32 {
	struct {
		uint32_t cfg_vf_tph_st_mode_47_32:16; /* [15:0] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_mpll_status {
	struct {
		uint32_t phy0_mplla_state:1; /* [0:0] */
		uint32_t phy0_mpllb_state:1; /* [1:1] */
		uint32_t phy1_mplla_state:1; /* [2:2] */
		uint32_t phy1_mpllb_state:1; /* [3:3] */
		uint32_t phy2_mplla_state:1; /* [4:4] */
		uint32_t phy2_mpllb_state:1; /* [5:5] */
		uint32_t phy3_mplla_state:1; /* [6:6] */
		uint32_t phy3_mpllb_state:1; /* [7:7] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_aes_mem_zero_init_in {
	struct {
		uint32_t ide_aes_mem_zero_init_in:1; /* [0:0] */
		uint32_t ide_mem_zero_clkmux_sel:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_aes_mem_zero_done_out {
	struct {
		uint32_t ide_aes_tx_mem_zero_done_out:1; /* [0:0] */
		uint32_t ide_aes_rx_mem_zero_done_out:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sw_button_rst_n {
	struct {
		uint32_t sw_button_rst_n:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_int_cm7_mask {
	struct {
		uint32_t edma_int_cm7_mask; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_edma_int_ca73_mask {
	struct {
		uint32_t edma_int_ca73_mask; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_perstn_sel {
	struct {
		uint32_t perstn_sel:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_lock_in {
	struct {
		uint32_t ide_aes_hcfg_key_lock_in:1; /* [0:0] */
		uint32_t ide_hcfg_config_lock_in:1; /* [1:1] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_test_control {
	struct {
		uint32_t ide_test_enable:1; /* [0:0] */
		uint32_t ide_bist_start_in_ide:1; /* [1:1] */
		uint32_t ide_bist_start_in_clkmux:1; /* [2:2] */
		uint32_t ide_bist_test_mode_in:4; /* [6:3] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_done_out {
	struct {
		uint32_t ide_bist_done_out:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_err {
	struct {
		uint32_t ide_bist_fail_out:1; /* [0:0] */
		uint32_t ide_bist_err_test_type_tx_out:3; /* [3:1] */
		uint32_t ide_bist_err_test_type_rx1_out:3; /* [6:4] */
		uint32_t ide_bist_err_core_out:2; /* [8:7] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_err_timestamp_tx_out_31_0 {
	struct {
		uint32_t ide_bist_err_timestamp_tx_out_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_err_timestamp_tx_out_63_32 {
	struct {
		uint32_t ide_bist_err_timestamp_tx_out_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_err_timestamp_rx1_out_31_0 {
	struct {
		uint32_t ide_bist_err_timestamp_rx1_out_31_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_err_timestamp_rx1_out_63_32 {
	struct {
		uint32_t ide_bist_err_timestamp_rx1_out_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_sw_ide_rst {
	struct {
		uint32_t sw_ide_rst_core:1; /* [0:0] */
		uint32_t sw_ide_cfg_caps_flr_rst:1; /* [1:1] */
		uint32_t sw_ide_cfg_caps_sticky_rst:1; /* [2:2] */
		uint32_t sw_ide_cfg_caps_non_sticky_rst:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_apb_bist_clk_en {
	struct {
		uint32_t ide_apb_bist_clk_en:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_ide_bist_done_out_clear {
	struct {
		uint32_t ide_bist_done_out_clear:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_0 {
	struct {
		uint32_t _atu_sloc_match_cnt_0_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_1 {
	struct {
		uint32_t _atu_sloc_match_cnt_1_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_2 {
	struct {
		uint32_t _atu_sloc_match_cnt_2_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_3 {
	struct {
		uint32_t _atu_sloc_match_cnt_3_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_4 {
	struct {
		uint32_t _atu_sloc_match_cnt_4_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_5 {
	struct {
		uint32_t _atu_sloc_match_cnt_5_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_6 {
	struct {
		uint32_t _atu_sloc_match_cnt_6_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_7 {
	struct {
		uint32_t _atu_sloc_match_cnt_7_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_8 {
	struct {
		uint32_t _atu_sloc_match_cnt_8_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_9 {
	struct {
		uint32_t _atu_sloc_match_cnt_9_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_10 {
	struct {
		uint32_t _atu_sloc_match_cnt_10_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_11 {
	struct {
		uint32_t _atu_sloc_match_cnt_11_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_12 {
	struct {
		uint32_t _atu_sloc_match_cnt_12_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_13 {
	struct {
		uint32_t _atu_sloc_match_cnt_13_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_14 {
	struct {
		uint32_t _atu_sloc_match_cnt_14_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_15 {
	struct {
		uint32_t _atu_sloc_match_cnt_15_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_16 {
	struct {
		uint32_t _atu_sloc_match_cnt_16_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_17 {
	struct {
		uint32_t _atu_sloc_match_cnt_17_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_18 {
	struct {
		uint32_t _atu_sloc_match_cnt_18_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_19 {
	struct {
		uint32_t _atu_sloc_match_cnt_19_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_20 {
	struct {
		uint32_t _atu_sloc_match_cnt_20_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_21 {
	struct {
		uint32_t _atu_sloc_match_cnt_21_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_22 {
	struct {
		uint32_t _atu_sloc_match_cnt_22_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_23 {
	struct {
		uint32_t _atu_sloc_match_cnt_23_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_24 {
	struct {
		uint32_t _atu_sloc_match_cnt_24_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_25 {
	struct {
		uint32_t _atu_sloc_match_cnt_25_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_26 {
	struct {
		uint32_t _atu_sloc_match_cnt_26_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_27 {
	struct {
		uint32_t _atu_sloc_match_cnt_27_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_28 {
	struct {
		uint32_t _atu_sloc_match_cnt_28_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_29 {
	struct {
		uint32_t _atu_sloc_match_cnt_29_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_30 {
	struct {
		uint32_t _atu_sloc_match_cnt_30_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_31 {
	struct {
		uint32_t _atu_sloc_match_cnt_31_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_32 {
	struct {
		uint32_t _atu_sloc_match_cnt_32_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_33 {
	struct {
		uint32_t _atu_sloc_match_cnt_33_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_34 {
	struct {
		uint32_t _atu_sloc_match_cnt_34_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_35 {
	struct {
		uint32_t _atu_sloc_match_cnt_35_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_36 {
	struct {
		uint32_t _atu_sloc_match_cnt_36_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_37 {
	struct {
		uint32_t _atu_sloc_match_cnt_37_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_38 {
	struct {
		uint32_t _atu_sloc_match_cnt_38_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_39 {
	struct {
		uint32_t _atu_sloc_match_cnt_39_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_40 {
	struct {
		uint32_t _atu_sloc_match_cnt_40_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_41 {
	struct {
		uint32_t _atu_sloc_match_cnt_41_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_42 {
	struct {
		uint32_t _atu_sloc_match_cnt_42_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_43 {
	struct {
		uint32_t _atu_sloc_match_cnt_43_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_44 {
	struct {
		uint32_t _atu_sloc_match_cnt_44_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_45 {
	struct {
		uint32_t _atu_sloc_match_cnt_45_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_46 {
	struct {
		uint32_t _atu_sloc_match_cnt_46_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_47 {
	struct {
		uint32_t _atu_sloc_match_cnt_47_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_48 {
	struct {
		uint32_t _atu_sloc_match_cnt_48_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_49 {
	struct {
		uint32_t _atu_sloc_match_cnt_49_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_50 {
	struct {
		uint32_t _atu_sloc_match_cnt_50_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_51 {
	struct {
		uint32_t _atu_sloc_match_cnt_51_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_52 {
	struct {
		uint32_t _atu_sloc_match_cnt_52_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_53 {
	struct {
		uint32_t _atu_sloc_match_cnt_53_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_54 {
	struct {
		uint32_t _atu_sloc_match_cnt_54_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_55 {
	struct {
		uint32_t _atu_sloc_match_cnt_55_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_56 {
	struct {
		uint32_t _atu_sloc_match_cnt_56_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_57 {
	struct {
		uint32_t _atu_sloc_match_cnt_57_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_58 {
	struct {
		uint32_t _atu_sloc_match_cnt_58_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_59 {
	struct {
		uint32_t _atu_sloc_match_cnt_59_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_60 {
	struct {
		uint32_t _atu_sloc_match_cnt_60_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_61 {
	struct {
		uint32_t _atu_sloc_match_cnt_61_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_62 {
	struct {
		uint32_t _atu_sloc_match_cnt_62_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_subctrl_sfr_atu_sloc_match_cnt_63 {
	struct {
		uint32_t _atu_sloc_match_cnt_63_:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

struct pcie_subctrl_register {
	union pcie_subctrl_irq_0 irq_0; /* offset : 0x0 */
	union pcie_subctrl_irq_1 irq_1; /* offset : 0x4 */
	union pcie_subctrl_irq_2 irq_2; /* offset : 0x8 */
	union pcie_subctrl_irq_3 irq_3; /* offset : 0xc */
	union pcie_subctrl_irq_0_en irq_0_en; /* offset : 0x10 */
	union pcie_subctrl_irq_1_en irq_1_en; /* offset : 0x14 */
	union pcie_subctrl_irq_2_en irq_2_en; /* offset : 0x18 */
	union pcie_subctrl_irq_3_en irq_3_en; /* offset : 0x1c */
	union pcie_subctrl_sfr_app_clk_pm_en sfr_app_clk_pm_en; /* offset : 0x20 */
	union pcie_subctrl_sfr_app_clk_req_n sfr_app_clk_req_n; /* offset : 0x24 */
	union pcie_subctrl_sfr_app_err_advisory sfr_app_err_advisory; /* offset : 0x28 */
	union pcie_subctrl_sfr_app_err_bus sfr_app_err_bus; /* offset : 0x2c */
	union pcie_subctrl_sfr_app_err_func_num sfr_app_err_func_num; /* offset : 0x30 */
	union pcie_subctrl_sfr_app_hdr_log_31_0 sfr_app_hdr_log_31_0; /* offset : 0x34 */
	union pcie_subctrl_sfr_app_hdr_log_63_32 sfr_app_hdr_log_63_32; /* offset : 0x38 */
	union pcie_subctrl_sfr_app_hdr_log_95_64 sfr_app_hdr_log_95_64; /* offset : 0x3c */
	union pcie_subctrl_sfr_app_hdr_log_127_96 sfr_app_hdr_log_127_96; /* offset : 0x40 */
	union pcie_subctrl_sfr_app_hdr_valid sfr_app_hdr_valid; /* offset : 0x44 */
	union pcie_subctrl_sfr_usp_eq_redo_executed_int sfr_usp_eq_redo_executed_int; /* offset : 0x48 */
	uint32_t reserved_1;
	union pcie_subctrl_sfr_l12_mem_pwr_shutoff_ovrd sfr_l12_mem_pwr_shutoff_ovrd; /* offset : 0x50 */
	union pcie_subctrl_sfr_app_ltssm_enable sfr_app_ltssm_enable; /* offset : 0x54 */
	union pcie_subctrl_sfr_app_obff_cpu_active_msg_req sfr_app_obff_cpu_active_msg_req; /* offset : 0x58 */
	union pcie_subctrl_sfr_app_obff_idle_msg_req sfr_app_obff_idle_msg_req; /* offset : 0x5c */
	union pcie_subctrl_sfr_app_obff_obff_msg_req sfr_app_obff_obff_msg_req; /* offset : 0x60 */
	union pcie_subctrl_sfr_app_ras_des_sd_hold_ltssm sfr_app_ras_des_sd_hold_ltssm; /* offset : 0x64 */
	union pcie_subctrl_sfr_app_ready_entr_l23 sfr_app_ready_entr_l23; /* offset : 0x68 */
	union pcie_subctrl_sfr_app_req_exit_l1 sfr_app_req_exit_l1; /* offset : 0x6c */
	union pcie_subctrl_sfr_cfg_axi_s_araddr_sel sfr_cfg_axi_s_araddr_sel; /* offset : 0x70 */
	union pcie_subctrl_sfr_app_xfer_pending sfr_app_xfer_pending; /* offset : 0x74 */
	union pcie_subctrl_sfr_cfg_eml_control sfr_cfg_eml_control; /* offset : 0x78 */
	union pcie_subctrl_sfr_pcs_ext_pclk_req sfr_pcs_ext_pclk_req; /* offset : 0x7c */
	union pcie_subctrl_sfr_phy_reset_ovrd sfr_phy_reset_ovrd; /* offset : 0x80 */
	union pcie_subctrl_sfr_diag_ctrl_bus sfr_diag_ctrl_bus; /* offset : 0x84 */
	union pcie_subctrl_sfr_cfg_axi_s_araddr sfr_cfg_axi_s_araddr; /* offset : 0x88 */
	union pcie_subctrl_sfr_cfg_axi_s_awaddr sfr_cfg_axi_s_awaddr; /* offset : 0x8c */
	union pcie_subctrl_sfr_sys_atten_button_pressed sfr_sys_atten_button_pressed; /* offset : 0x90 */
	union pcie_subctrl_sfr_sys_aux_pwr_det sfr_sys_aux_pwr_det; /* offset : 0x94 */
	union pcie_subctrl_sfr_sys_cmd_cpled_int sfr_sys_cmd_cpled_int; /* offset : 0x98 */
	union pcie_subctrl_sfr_sys_eml_interlock_engaged sfr_sys_eml_interlock_engaged; /* offset : 0x9c */
	union pcie_subctrl_sfr_sys_int sfr_sys_int; /* offset : 0xa0 */
	union pcie_subctrl_sfr_sys_mrl_sensor_chged sfr_sys_mrl_sensor_chged; /* offset : 0xa4 */
	union pcie_subctrl_sfr_sys_mrl_sensor_state sfr_sys_mrl_sensor_state; /* offset : 0xa8 */
	union pcie_subctrl_sfr_ven_msg_vfunc_num sfr_ven_msg_vfunc_num; /* offset : 0xac */
	union pcie_subctrl_sfr_ven_msg_vfunc_active sfr_ven_msg_vfunc_active; /* offset : 0xb0 */
	union pcie_subctrl_sfr_sys_pwr_fault_det sfr_sys_pwr_fault_det; /* offset : 0xb4 */
	union pcie_subctrl_sfr_ven_msg_attr sfr_ven_msg_attr; /* offset : 0xb8 */
	union pcie_subctrl_sfr_ven_msg_code sfr_ven_msg_code; /* offset : 0xbc */
	union pcie_subctrl_sfr_ven_msg_data_31_0 sfr_ven_msg_data_31_0; /* offset : 0xc0 */
	union pcie_subctrl_sfr_ven_msg_data_63_32 sfr_ven_msg_data_63_32; /* offset : 0xc4 */
	union pcie_subctrl_sfr_ven_msg_ep sfr_ven_msg_ep; /* offset : 0xc8 */
	union pcie_subctrl_sfr_ven_msg_fmt sfr_ven_msg_fmt; /* offset : 0xcc */
	union pcie_subctrl_sfr_ven_msg_func_num sfr_ven_msg_func_num; /* offset : 0xd0 */
	union pcie_subctrl_sfr_ven_msg_len sfr_ven_msg_len; /* offset : 0xd4 */
	union pcie_subctrl_sfr_ven_msg_req sfr_ven_msg_req; /* offset : 0xd8 */
	union pcie_subctrl_sfr_ven_msg_tag sfr_ven_msg_tag; /* offset : 0xdc */
	union pcie_subctrl_sfr_ven_msg_tc sfr_ven_msg_tc; /* offset : 0xe0 */
	union pcie_subctrl_sfr_ven_msg_td sfr_ven_msg_td; /* offset : 0xe4 */
	union pcie_subctrl_sfr_ven_msg_type sfr_ven_msg_type; /* offset : 0xe8 */
	union pcie_subctrl_sfr_cfg_axi_s_awaddr_sel sfr_cfg_axi_s_awaddr_sel; /* offset : 0xec */
	union pcie_subctrl_sfr_ven_msi_reg sfr_ven_msi_reg; /* offset : 0xf0 */
	union pcie_subctrl_sfr_phy_rtune_sts sfr_phy_rtune_sts; /* offset : 0xf4 */
	union pcie_subctrl_sfr_phy_rtune_req sfr_phy_rtune_req; /* offset : 0xf8 */
	union pcie_subctrl_sfr_power_up_rst_n_ovrd sfr_power_up_rst_n_ovrd; /* offset : 0xfc */
	union pcie_subctrl_sfr_app_init_rst sfr_app_init_rst; /* offset : 0x100 */
	union pcie_subctrl_sfr_app_ras_des_tba_ctrl sfr_app_ras_des_tba_ctrl; /* offset : 0x104 */
	union pcie_subctrl_sfr_app_req_entr_l1 sfr_app_req_entr_l1; /* offset : 0x108 */
	uint32_t reserved_2;
	union pcie_subctrl_sfr_app_unlock_msg sfr_app_unlock_msg; /* offset : 0x110 */
	union pcie_subctrl_sfr_apps_pm_xmt_pme sfr_apps_pm_xmt_pme; /* offset : 0x114 */
	union pcie_subctrl_sfr_apps_pm_xmt_turnoff sfr_apps_pm_xmt_turnoff; /* offset : 0x118 */
	union pcie_subctrl_sfr_outband_pwrup_cmd sfr_outband_pwrup_cmd; /* offset : 0x11c */
	union pcie_subctrl_sfr_app_ltr_latency sfr_app_ltr_latency; /* offset : 0x120 */
	union pcie_subctrl_sfr_aux_pm_en sfr_aux_pm_en; /* offset : 0x124 */
	union pcie_subctrl_sfr_brdg_dbi_xfer_pending sfr_brdg_dbi_xfer_pending; /* offset : 0x128 */
	union pcie_subctrl_sfr_brdg_slv_xfer_pending sfr_brdg_slv_xfer_pending; /* offset : 0x12c */
	union pcie_subctrl_sfr_app_ltr_msg_func_num sfr_app_ltr_msg_func_num; /* offset : 0x130 */
	union pcie_subctrl_sfr_app_ltr_msg_latency sfr_app_ltr_msg_latency; /* offset : 0x134 */
	union pcie_subctrl_sfr_app_ltr_msg_req sfr_app_ltr_msg_req; /* offset : 0x138 */
	union pcie_subctrl_sfr_cfg_ltr_max_latency sfr_cfg_ltr_max_latency; /* offset : 0x13c */
	union pcie_subctrl_sfr_cfg_disable_ltr_clr_msg sfr_cfg_disable_ltr_clr_msg; /* offset : 0x140 */
	union pcie_subctrl_sfr_tx_lane_flip_en sfr_tx_lane_flip_en; /* offset : 0x144 */
	union pcie_subctrl_sfr_rx_lane_flip_en sfr_rx_lane_flip_en; /* offset : 0x148 */
	union pcie_subctrl_sfr_app_margining_ready sfr_app_margining_ready; /* offset : 0x14c */
	union pcie_subctrl_sfr_app_margining_software_ready sfr_app_margining_software_ready; /* offset : 0x150 */
	union pcie_subctrl_sfr_app_sris_mode sfr_app_sris_mode; /* offset : 0x154 */
	union pcie_subctrl_sfr_app_req_retry_en sfr_app_req_retry_en; /* offset : 0x158 */
	union pcie_subctrl_sfr_app_pf_req_retry_en sfr_app_pf_req_retry_en; /* offset : 0x15c */
	union pcie_subctrl_sfr_app_vf_req_retry_en sfr_app_vf_req_retry_en; /* offset : 0x160 */
	union pcie_subctrl_sfr_dbg_sel_group sfr_dbg_sel_group; /* offset : 0x164 */
	union pcie_subctrl_sfr_dbg_sel_dword sfr_dbg_sel_dword; /* offset : 0x168 */
	uint32_t reserved_3[35];
	union pcie_subctrl_sfr_cfg_2nd_reset sfr_cfg_2nd_reset; /* offset : 0x1f8 */
	union pcie_subctrl_sfr_cfg_2ndbus_num sfr_cfg_2ndbus_num; /* offset : 0x1fc */
	union pcie_subctrl_sfr_cfg_aer_int_msg_num sfr_cfg_aer_int_msg_num; /* offset : 0x200 */
	union pcie_subctrl_sfr_cfg_atten_button_pressed_en sfr_cfg_atten_button_pressed_en; /* offset : 0x204 */
	union pcie_subctrl_sfr_cfg_atten_ind sfr_cfg_atten_ind; /* offset : 0x208 */
	union pcie_subctrl_sfr_cfg_bar0_limit_31_0 sfr_cfg_bar0_limit_31_0; /* offset : 0x20c */
	union pcie_subctrl_sfr_cfg_bar0_limit_63_32 sfr_cfg_bar0_limit_63_32; /* offset : 0x210 */
	union pcie_subctrl_sfr_cfg_bar0_start_31_0 sfr_cfg_bar0_start_31_0; /* offset : 0x214 */
	union pcie_subctrl_sfr_cfg_bar0_start_63_32 sfr_cfg_bar0_start_63_32; /* offset : 0x218 */
	union pcie_subctrl_sfr_cfg_bar1_limit sfr_cfg_bar1_limit; /* offset : 0x21c */
	union pcie_subctrl_sfr_cfg_bar1_start sfr_cfg_bar1_start; /* offset : 0x220 */
	union pcie_subctrl_sfr_cfg_bar2_limit_31_0 sfr_cfg_bar2_limit_31_0; /* offset : 0x224 */
	union pcie_subctrl_sfr_cfg_bar2_limit_63_32 sfr_cfg_bar2_limit_63_32; /* offset : 0x228 */
	union pcie_subctrl_sfr_cfg_bar2_start_31_0 sfr_cfg_bar2_start_31_0; /* offset : 0x22c */
	union pcie_subctrl_sfr_cfg_bar2_start_63_32 sfr_cfg_bar2_start_63_32; /* offset : 0x230 */
	union pcie_subctrl_sfr_cfg_bar3_limit sfr_cfg_bar3_limit; /* offset : 0x234 */
	union pcie_subctrl_sfr_cfg_bar3_start sfr_cfg_bar3_start; /* offset : 0x238 */
	union pcie_subctrl_sfr_cfg_bar4_limit_31_0 sfr_cfg_bar4_limit_31_0; /* offset : 0x23c */
	union pcie_subctrl_sfr_cfg_bar4_limit_63_32 sfr_cfg_bar4_limit_63_32; /* offset : 0x240 */
	union pcie_subctrl_sfr_cfg_bar4_start_31_0 sfr_cfg_bar4_start_31_0; /* offset : 0x244 */
	union pcie_subctrl_sfr_cfg_bar4_start_63_32 sfr_cfg_bar4_start_63_32; /* offset : 0x248 */
	union pcie_subctrl_sfr_cfg_bar5_limit sfr_cfg_bar5_limit; /* offset : 0x24c */
	union pcie_subctrl_sfr_cfg_bar5_start sfr_cfg_bar5_start; /* offset : 0x250 */
	union pcie_subctrl_sfr_cfg_br_ctrl_serren sfr_cfg_br_ctrl_serren; /* offset : 0x254 */
	union pcie_subctrl_sfr_cfg_cmd_cpled_int_en sfr_cfg_cmd_cpled_int_en; /* offset : 0x258 */
	union pcie_subctrl_sfr_cfg_crs_sw_vis_en sfr_cfg_crs_sw_vis_en; /* offset : 0x25c */
	union pcie_subctrl_sfr_cfg_dll_state_chged_en sfr_cfg_dll_state_chged_en; /* offset : 0x260 */
	union pcie_subctrl_sfr_cfg_exp_rom_limit sfr_cfg_exp_rom_limit; /* offset : 0x264 */
	union pcie_subctrl_sfr_cfg_exp_rom_start sfr_cfg_exp_rom_start; /* offset : 0x268 */
	union pcie_subctrl_sfr_cfg_hp_int_en sfr_cfg_hp_int_en; /* offset : 0x26c */
	union pcie_subctrl_sfr_cfg_hp_slot_ctrl_access sfr_cfg_hp_slot_ctrl_access; /* offset : 0x270 */
	union pcie_subctrl_sfr_cfg_hw_auto_sp_dis sfr_cfg_hw_auto_sp_dis; /* offset : 0x274 */
	union pcie_subctrl_sfr_cfg_int_disable sfr_cfg_int_disable; /* offset : 0x278 */
	union pcie_subctrl_sfr_cfg_l1sub_en sfr_cfg_l1sub_en; /* offset : 0x27c */
	union pcie_subctrl_sfr_cfg_ltr_m_en sfr_cfg_ltr_m_en; /* offset : 0x280 */
	uint32_t reserved_4;
	union pcie_subctrl_sfr_cfg_max_payload_size sfr_cfg_max_payload_size; /* offset : 0x288 */
	union pcie_subctrl_sfr_cfg_max_rd_req_size sfr_cfg_max_rd_req_size; /* offset : 0x28c */
	union pcie_subctrl_sfr_cfg_mem_spac sfr_cfg_mem_spac; /* offset : 0x290 */
	union pcie_subctrl_sfr_cfg_mrl_sensor_chged_en sfr_cfg_mrl_sensor_chged_en; /* offset : 0x294 */
	uint32_t reserved_5[2];
	union pcie_subctrl_sfr_cfg_no_snoop_en sfr_cfg_no_snoop_en; /* offset : 0x2a0 */
	union pcie_subctrl_sfr_cfg_obff_en sfr_cfg_obff_en; /* offset : 0x2a4 */
	union pcie_subctrl_sfr_cfg_pbus_dev_num sfr_cfg_pbus_dev_num; /* offset : 0x2a8 */
	union pcie_subctrl_sfr_cfg_pbus_num sfr_cfg_pbus_num; /* offset : 0x2ac */
	union pcie_subctrl_sfr_cfg_pcie_cap_int_msg_num sfr_cfg_pcie_cap_int_msg_num; /* offset : 0x2b0 */
	union pcie_subctrl_sfr_cfg_phy_control sfr_cfg_phy_control; /* offset : 0x2b4 */
	union pcie_subctrl_sfr_cfg_pm_no_soft_rst sfr_cfg_pm_no_soft_rst; /* offset : 0x2b8 */
	union pcie_subctrl_sfr_cfg_pre_det_chged_en sfr_cfg_pre_det_chged_en; /* offset : 0x2bc */
	union pcie_subctrl_sfr_cfg_pwr_ctrler_ctrl sfr_cfg_pwr_ctrler_ctrl; /* offset : 0x2c0 */
	union pcie_subctrl_sfr_cfg_pwr_fault_det_en sfr_cfg_pwr_fault_det_en; /* offset : 0x2c4 */
	union pcie_subctrl_sfr_cfg_pwr_ind sfr_cfg_pwr_ind; /* offset : 0x2c8 */
	union pcie_subctrl_sfr_cfg_rcb sfr_cfg_rcb; /* offset : 0x2cc */
	union pcie_subctrl_sfr_cfg_relax_order_en sfr_cfg_relax_order_en; /* offset : 0x2d0 */
	union pcie_subctrl_sfr_cfg_send_cor_err sfr_cfg_send_cor_err; /* offset : 0x2d4 */
	union pcie_subctrl_sfr_cfg_send_f_err sfr_cfg_send_f_err; /* offset : 0x2d8 */
	union pcie_subctrl_sfr_cfg_send_nf_err sfr_cfg_send_nf_err; /* offset : 0x2dc */
	union pcie_subctrl_sfr_cfg_subbus_num sfr_cfg_subbus_num; /* offset : 0x2e0 */
	uint32_t reserved_6;
	union pcie_subctrl_sfr_cxpl_debug_info_31_0 sfr_cxpl_debug_info_31_0; /* offset : 0x2e8 */
	union pcie_subctrl_sfr_cxpl_debug_info_63_32 sfr_cxpl_debug_info_63_32; /* offset : 0x2ec */
	union pcie_subctrl_sfr_cxpl_debug_info_ei sfr_cxpl_debug_info_ei; /* offset : 0x2f0 */
	union pcie_subctrl_sfr_edma_xfer_pending sfr_edma_xfer_pending; /* offset : 0x2f4 */
	uint32_t reserved_7;
	union pcie_subctrl_sfr_msi_ctrl_int_vec sfr_msi_ctrl_int_vec; /* offset : 0x2fc */
	union pcie_subctrl_sfr_msi_ctrl_io sfr_msi_ctrl_io; /* offset : 0x300 */
	union pcie_subctrl_sfr_pm_curnt_state sfr_pm_curnt_state; /* offset : 0x304 */
	union pcie_subctrl_sfr_pm_dstate sfr_pm_dstate; /* offset : 0x308 */
	union pcie_subctrl_sfr_pm_pme_en sfr_pm_pme_en; /* offset : 0x30c */
	union pcie_subctrl_sfr_pm_status sfr_pm_status; /* offset : 0x310 */
	union pcie_subctrl_sfr_radm_idle sfr_radm_idle; /* offset : 0x314 */
	uint32_t reserved_8;
	union pcie_subctrl_sfr_radm_xfer_pending sfr_radm_xfer_pending; /* offset : 0x31c */
	union pcie_subctrl_sfr_smlh_ltssm_state sfr_smlh_ltssm_state; /* offset : 0x320 */
	union pcie_subctrl_sfr_smlh_ltssm_state_rcvry_eq sfr_smlh_ltssm_state_rcvry_eq; /* offset : 0x324 */
	union pcie_subctrl_sfr_trgt_lookup_empty sfr_trgt_lookup_empty; /* offset : 0x328 */
	union pcie_subctrl_sfr_trgt_lookup_id sfr_trgt_lookup_id; /* offset : 0x32c */
	union pcie_subctrl_sfr_radm_msg_code sfr_radm_msg_code; /* offset : 0x330 */
	uint32_t reserved_9[5];
	union pcie_subctrl_sfr_radm_msg_payload_31_0 sfr_radm_msg_payload_31_0; /* offset : 0x348 */
	union pcie_subctrl_sfr_radm_msg_payload_63_32 sfr_radm_msg_payload_63_32; /* offset : 0x34c */
	union pcie_subctrl_sfr_radm_msg_req_id sfr_radm_msg_req_id; /* offset : 0x350 */
	union pcie_subctrl_sfr_radm_timeout_cpl_attr sfr_radm_timeout_cpl_attr; /* offset : 0x354 */
	union pcie_subctrl_sfr_radm_timeout_cpl_len sfr_radm_timeout_cpl_len; /* offset : 0x358 */
	union pcie_subctrl_sfr_radm_timeout_cpl_tag sfr_radm_timeout_cpl_tag; /* offset : 0x35c */
	union pcie_subctrl_sfr_radm_timeout_cpl_tc sfr_radm_timeout_cpl_tc; /* offset : 0x360 */
	union pcie_subctrl_sfr_radm_timeout_func_num sfr_radm_timeout_func_num; /* offset : 0x364 */
	union pcie_subctrl_sfr_radm_timeout_vfunc_num sfr_radm_timeout_vfunc_num; /* offset : 0x368 */
	union pcie_subctrl_sfr_radm_timeout_vfunc_active sfr_radm_timeout_vfunc_active; /* offset : 0x36c */
	union pcie_subctrl_sfr_trgt_timeout_cpl_attr sfr_trgt_timeout_cpl_attr; /* offset : 0x370 */
	union pcie_subctrl_sfr_trgt_timeout_cpl_func_num sfr_trgt_timeout_cpl_func_num; /* offset : 0x374 */
	union pcie_subctrl_sfr_trgt_timeout_cpl_len sfr_trgt_timeout_cpl_len; /* offset : 0x378 */
	union pcie_subctrl_sfr_trgt_timeout_cpl_tc sfr_trgt_timeout_cpl_tc; /* offset : 0x37c */
	union pcie_subctrl_sfr_trgt_timeout_lookup_id sfr_trgt_timeout_lookup_id; /* offset : 0x380 */
	union pcie_subctrl_irq_0_cp_en irq_0_cp_en; /* offset : 0x384 */
	union pcie_subctrl_sfr_trgt_timeout_cpl_vfunc_num sfr_trgt_timeout_cpl_vfunc_num; /* offset : 0x388 */
	union pcie_subctrl_sfr_trgt_timeout_cpl_vfunc_active sfr_trgt_timeout_cpl_vfunc_active; /* offset : 0x38c */
	uint32_t reserved_10;
	union pcie_subctrl_irq_1_cp_en irq_1_cp_en; /* offset : 0x394 */
	union pcie_subctrl_irq_2_cp_en irq_2_cp_en; /* offset : 0x398 */
	union pcie_subctrl_irq_3_cp_en irq_3_cp_en; /* offset : 0x39c */
	union pcie_subctrl_sfr_app_bus_dev_num sfr_app_bus_dev_num; /* offset : 0x3a0 */
	union pcie_subctrl_sfr_app_ctrl_signals sfr_app_ctrl_signals; /* offset : 0x3a4 */
	union pcie_subctrl_sfr_cfg_acs_capabilities_ctrl_reg sfr_cfg_acs_capabilities_ctrl_reg; /* offset : 0x3a8 */
	union pcie_subctrl_sfr_exp_rom_bar_validation_details sfr_exp_rom_bar_validation_details; /* offset : 0x3ac */
	union pcie_subctrl_sfr_frsq_massaging_signals sfr_frsq_massaging_signals; /* offset : 0x3b0 */
	union pcie_subctrl_sfr_local_ref_clk_req_n sfr_local_ref_clk_req_n; /* offset : 0x3b4 */
	union pcie_subctrl_sfr_ptm_ctrl_signals sfr_ptm_ctrl_signals; /* offset : 0x3b8 */
	union pcie_subctrl_sfr_ptm_external_master_time_31_0 sfr_ptm_external_master_time_31_0; /* offset : 0x3bc */
	union pcie_subctrl_sfr_ptm_external_master_time_63_32 sfr_ptm_external_master_time_63_32; /* offset : 0x3c0 */
	union pcie_subctrl_sfr_ptm_local_clock_31_0 sfr_ptm_local_clock_31_0; /* offset : 0x3c4 */
	union pcie_subctrl_sfr_ptm_local_clock_63_32 sfr_ptm_local_clock_63_32; /* offset : 0x3c8 */
	union pcie_subctrl_sfr_ptm_external_master_strobe sfr_ptm_external_master_strobe; /* offset : 0x3cc */
	uint32_t reserved_11;
	union pcie_subctrl_sfr_mac_phy_register sfr_mac_phy_register; /* offset : 0x3d4 */
	union pcie_subctrl_sfr_clkreq_in_n sfr_clkreq_in_n; /* offset : 0x3d8 */
	union pcie_subctrl_sfr_phy_mac_localfs sfr_phy_mac_localfs; /* offset : 0x3dc */
	union pcie_subctrl_sfr_pm_current_data_rate sfr_pm_current_data_rate; /* offset : 0x3e0 */
	uint32_t reserved_12;
	union pcie_subctrl_sfr_app_owre sfr_app_owre; /* offset : 0x3e8 */
	union pcie_subctrl_sfr_cfg_wk_min_max sfr_cfg_wk_min_max; /* offset : 0x3ec */
	union pcie_subctrl_sfr_shared_dbi_bus_access sfr_shared_dbi_bus_access; /* offset : 0x3f0 */
	union pcie_subctrl_sfr_ela_fifo_ctrl sfr_ela_fifo_ctrl; /* offset : 0x3f4 */
	uint32_t reserved_13[4];
	union pcie_subctrl_irq_0_mstr_aclk irq_0_mstr_aclk; /* offset : 0x408 */
	uint32_t reserved_14[3];
	union pcie_subctrl_irq_0_en_mstr_aclk irq_0_en_mstr_aclk; /* offset : 0x418 */
	uint32_t reserved_15;
	union pcie_subctrl_sfr_mstr_bmisc_info_cpl_stat sfr_mstr_bmisc_info_cpl_stat; /* offset : 0x420 */
	union pcie_subctrl_sfr_mstr_rmisc_info sfr_mstr_rmisc_info; /* offset : 0x424 */
	union pcie_subctrl_sfr_mstr_rmisc_info_cpl_stat sfr_mstr_rmisc_info_cpl_stat; /* offset : 0x428 */
	union pcie_subctrl_sfr_mstr_armisc_info_zeroread sfr_mstr_armisc_info_zeroread; /* offset : 0x42c */
	union pcie_subctrl_sfr_mstr_armisc_info_31_0 sfr_mstr_armisc_info_31_0; /* offset : 0x430 */
	union pcie_subctrl_sfr_mstr_armisc_info_49_32 sfr_mstr_armisc_info_49_32; /* offset : 0x434 */
	union pcie_subctrl_sfr_mstr_armisc_info_dma sfr_mstr_armisc_info_dma; /* offset : 0x438 */
	union pcie_subctrl_sfr_mstr_armisc_info_last_dcmp_tlp sfr_mstr_armisc_info_last_dcmp_tlp; /* offset : 0x43c */
	union pcie_subctrl_sfr_mstr_awmisc_info_31_0 sfr_mstr_awmisc_info_31_0; /* offset : 0x440 */
	union pcie_subctrl_sfr_mstr_awmisc_info_49_32 sfr_mstr_awmisc_info_49_32; /* offset : 0x444 */
	union pcie_subctrl_sfr_mstr_awmisc_info_dma sfr_mstr_awmisc_info_dma; /* offset : 0x448 */
	union pcie_subctrl_sfr_mstr_awmisc_info_hdr_34dw_31_0 sfr_mstr_awmisc_info_hdr_34dw_31_0; /* offset : 0x44c */
	union pcie_subctrl_sfr_mstr_awmisc_info_hdr_34dw_63_32 sfr_mstr_awmisc_info_hdr_34dw_63_32; /* offset : 0x450 */
	union pcie_subctrl_sfr_mstr_awmisc_info_last_dcmp_tlp sfr_mstr_awmisc_info_last_dcmp_tlp; /* offset : 0x454 */
	union pcie_subctrl_sfr_mstr_awmisc_info_ep sfr_mstr_awmisc_info_ep; /* offset : 0x458 */
	uint32_t reserved_16;
	union pcie_subctrl_sfr_mstr_wtran_cnt sfr_mstr_wtran_cnt; /* offset : 0x460 */
	union pcie_subctrl_sfr_mstr_rtran_cnt sfr_mstr_rtran_cnt; /* offset : 0x464 */
	union pcie_subctrl_sfr_mstr_ch_status sfr_mstr_ch_status; /* offset : 0x468 */
	union pcie_subctrl_sfr_mstr_armisc_info_func_num sfr_mstr_armisc_info_func_num; /* offset : 0x46c */
	union pcie_subctrl_sfr_mstr_armisc_info_vfunc_num sfr_mstr_armisc_info_vfunc_num; /* offset : 0x470 */
	union pcie_subctrl_sfr_mstr_armisc_info_vfunc_active sfr_mstr_armisc_info_vfunc_active; /* offset : 0x474 */
	union pcie_subctrl_sfr_mstr_ar_user sfr_mstr_ar_user; /* offset : 0x478 */
	union pcie_subctrl_sfr_mstr_awmisc_info_func_num sfr_mstr_awmisc_info_func_num; /* offset : 0x47c */
	union pcie_subctrl_sfr_mstr_awmisc_info_vfunc_num sfr_mstr_awmisc_info_vfunc_num; /* offset : 0x480 */
	union pcie_subctrl_sfr_mstr_awmisc_info_vfunc_active sfr_mstr_awmisc_info_vfunc_active; /* offset : 0x484 */
	union pcie_subctrl_sfr_mstr_aw_user sfr_mstr_aw_user; /* offset : 0x488 */
	uint32_t reserved_17[223];
	union pcie_subctrl_irq_0_slv_aclk irq_0_slv_aclk; /* offset : 0x808 */
	uint32_t reserved_18[3];
	union pcie_subctrl_irq_0_en_slv_aclk irq_0_en_slv_aclk; /* offset : 0x818 */
	uint32_t reserved_19;
	union pcie_subctrl_sfr_slv_armisc_info sfr_slv_armisc_info; /* offset : 0x820 */
	union pcie_subctrl_sfr_slv_armisc_info_atu_bypass sfr_slv_armisc_info_atu_bypass; /* offset : 0x824 */
	union pcie_subctrl_sfr_slv_awmisc_info sfr_slv_awmisc_info; /* offset : 0x828 */
	union pcie_subctrl_sfr_slv_awmisc_info_atu_bypass sfr_slv_awmisc_info_atu_bypass; /* offset : 0x82c */
	union pcie_subctrl_sfr_slv_awmisc_info_hdr_34dw_31_0 sfr_slv_awmisc_info_hdr_34dw_31_0; /* offset : 0x830 */
	union pcie_subctrl_sfr_slv_awmisc_info_hdr_34dw_63_32 sfr_slv_awmisc_info_hdr_34dw_63_32; /* offset : 0x834 */
	union pcie_subctrl_sfr_slv_awmisc_info_p_tag sfr_slv_awmisc_info_p_tag; /* offset : 0x838 */
	uint32_t reserved_20;
	union pcie_subctrl_sfr_slv_bmisc_info sfr_slv_bmisc_info; /* offset : 0x840 */
	union pcie_subctrl_sfr_slv_rmisc_info sfr_slv_rmisc_info; /* offset : 0x844 */
	union pcie_subctrl_sfr_slv_wmisc_info_ep sfr_slv_wmisc_info_ep; /* offset : 0x848 */
	union pcie_subctrl_sfr_slv_wmisc_info_silentdrop sfr_slv_wmisc_info_silentdrop; /* offset : 0x84c */
	uint32_t reserved_21[236];
	union pcie_subctrl_sfr_history_store_ctrl sfr_history_store_ctrl; /* offset : 0xc00 */
	union pcie_subctrl_sfr_power_state_history_s_g1 sfr_power_state_history_s_g1; /* offset : 0xc04 */
	union pcie_subctrl_sfr_power_state_history_m_g1 sfr_power_state_history_m_g1; /* offset : 0xc08 */
	union pcie_subctrl_sfr_power_state_history_s_g2 sfr_power_state_history_s_g2; /* offset : 0xc0c */
	union pcie_subctrl_sfr_power_state_history_m_g2 sfr_power_state_history_m_g2; /* offset : 0xc10 */
	union pcie_subctrl_sfr_power_state_history_s_g3 sfr_power_state_history_s_g3; /* offset : 0xc14 */
	union pcie_subctrl_sfr_power_state_history_m_g3 sfr_power_state_history_m_g3; /* offset : 0xc18 */
	union pcie_subctrl_sfr_power_state_history_s_g4 sfr_power_state_history_s_g4; /* offset : 0xc1c */
	union pcie_subctrl_sfr_power_state_history_m_g4 sfr_power_state_history_m_g4; /* offset : 0xc20 */
	union pcie_subctrl_sfr_history_sel sfr_history_sel; /* offset : 0xc24 */
	uint32_t reserved_22[26];
	union pcie_subctrl_sfr_leq_mon_control sfr_leq_mon_control; /* offset : 0xc90 */
	union pcie_subctrl_sfr_leq_status_0 sfr_leq_status_0; /* offset : 0xc94 */
	union pcie_subctrl_sfr_leq_status_1 sfr_leq_status_1; /* offset : 0xc98 */
	union pcie_subctrl_sfr_leq_status_2 sfr_leq_status_2; /* offset : 0xc9c */
	union pcie_subctrl_sfr_leq_status_3 sfr_leq_status_3; /* offset : 0xca0 */
	union pcie_subctrl_sfr_leq_status_4 sfr_leq_status_4; /* offset : 0xca4 */
	union pcie_subctrl_sfr_leq_status_5 sfr_leq_status_5; /* offset : 0xca8 */
	union pcie_subctrl_sfr_leq_status_6 sfr_leq_status_6; /* offset : 0xcac */
	union pcie_subctrl_sfr_leq_status_7 sfr_leq_status_7; /* offset : 0xcb0 */
	union pcie_subctrl_sfr_leq_status_8 sfr_leq_status_8; /* offset : 0xcb4 */
	union pcie_subctrl_sfr_leq_status_9 sfr_leq_status_9; /* offset : 0xcb8 */
	union pcie_subctrl_sfr_leq_status_10 sfr_leq_status_10; /* offset : 0xcbc */
	union pcie_subctrl_sfr_leq_status_11 sfr_leq_status_11; /* offset : 0xcc0 */
	union pcie_subctrl_sfr_leq_status_12 sfr_leq_status_12; /* offset : 0xcc4 */
	union pcie_subctrl_sfr_leq_status_13 sfr_leq_status_13; /* offset : 0xcc8 */
	union pcie_subctrl_sfr_leq_status_14 sfr_leq_status_14; /* offset : 0xccc */
	union pcie_subctrl_sfr_leq_status_15 sfr_leq_status_15; /* offset : 0xcd0 */
	union pcie_subctrl_sfr_leq_status_16 sfr_leq_status_16; /* offset : 0xcd4 */
	union pcie_subctrl_sfr_leq_status_17 sfr_leq_status_17; /* offset : 0xcd8 */
	union pcie_subctrl_sfr_leq_status_18 sfr_leq_status_18; /* offset : 0xcdc */
	union pcie_subctrl_sfr_leq_status_19 sfr_leq_status_19; /* offset : 0xce0 */
	union pcie_subctrl_sfr_leq_status_20 sfr_leq_status_20; /* offset : 0xce4 */
	union pcie_subctrl_sfr_leq_status_21 sfr_leq_status_21; /* offset : 0xce8 */
	union pcie_subctrl_sfr_leq_status_22 sfr_leq_status_22; /* offset : 0xcec */
	union pcie_subctrl_sfr_leq_status_23 sfr_leq_status_23; /* offset : 0xcf0 */
	union pcie_subctrl_sfr_leq_status_24 sfr_leq_status_24; /* offset : 0xcf4 */
	union pcie_subctrl_sfr_leq_status_25 sfr_leq_status_25; /* offset : 0xcf8 */
	union pcie_subctrl_sfr_leq_status_26 sfr_leq_status_26; /* offset : 0xcfc */
	union pcie_subctrl_sfr_leq_status_27 sfr_leq_status_27; /* offset : 0xd00 */
	union pcie_subctrl_sfr_leq_status_28 sfr_leq_status_28; /* offset : 0xd04 */
	union pcie_subctrl_sfr_leq_status_29 sfr_leq_status_29; /* offset : 0xd08 */
	union pcie_subctrl_sfr_leq_status_30 sfr_leq_status_30; /* offset : 0xd0c */
	union pcie_subctrl_sfr_leq_status_31 sfr_leq_status_31; /* offset : 0xd10 */
	union pcie_subctrl_sfr_leq_counter sfr_leq_counter; /* offset : 0xd14 */
	union pcie_subctrl_sfr_history_reg0 sfr_history_reg0; /* offset : 0xd18 */
	union pcie_subctrl_sfr_history_reg1 sfr_history_reg1; /* offset : 0xd1c */
	union pcie_subctrl_sfr_history_reg2 sfr_history_reg2; /* offset : 0xd20 */
	union pcie_subctrl_sfr_history_reg3 sfr_history_reg3; /* offset : 0xd24 */
	union pcie_subctrl_sfr_history_reg4 sfr_history_reg4; /* offset : 0xd28 */
	union pcie_subctrl_sfr_history_reg5 sfr_history_reg5; /* offset : 0xd2c */
	union pcie_subctrl_sfr_history_reg6 sfr_history_reg6; /* offset : 0xd30 */
	union pcie_subctrl_sfr_history_reg7 sfr_history_reg7; /* offset : 0xd34 */
	union pcie_subctrl_sfr_history_reg8 sfr_history_reg8; /* offset : 0xd38 */
	union pcie_subctrl_sfr_history_reg9 sfr_history_reg9; /* offset : 0xd3c */
	union pcie_subctrl_sfr_history_reg10 sfr_history_reg10; /* offset : 0xd40 */
	union pcie_subctrl_sfr_history_reg11 sfr_history_reg11; /* offset : 0xd44 */
	union pcie_subctrl_sfr_history_reg12 sfr_history_reg12; /* offset : 0xd48 */
	union pcie_subctrl_sfr_history_reg13 sfr_history_reg13; /* offset : 0xd4c */
	union pcie_subctrl_sfr_history_reg14 sfr_history_reg14; /* offset : 0xd50 */
	union pcie_subctrl_sfr_history_reg15 sfr_history_reg15; /* offset : 0xd54 */
	union pcie_subctrl_sfr_history_reg16 sfr_history_reg16; /* offset : 0xd58 */
	union pcie_subctrl_sfr_history_reg17 sfr_history_reg17; /* offset : 0xd5c */
	union pcie_subctrl_sfr_history_reg18 sfr_history_reg18; /* offset : 0xd60 */
	union pcie_subctrl_sfr_history_reg19 sfr_history_reg19; /* offset : 0xd64 */
	union pcie_subctrl_sfr_history_reg20 sfr_history_reg20; /* offset : 0xd68 */
	union pcie_subctrl_sfr_history_reg21 sfr_history_reg21; /* offset : 0xd6c */
	union pcie_subctrl_sfr_history_reg22 sfr_history_reg22; /* offset : 0xd70 */
	union pcie_subctrl_sfr_history_reg23 sfr_history_reg23; /* offset : 0xd74 */
	union pcie_subctrl_sfr_history_reg24 sfr_history_reg24; /* offset : 0xd78 */
	union pcie_subctrl_sfr_history_reg25 sfr_history_reg25; /* offset : 0xd7c */
	union pcie_subctrl_sfr_history_reg26 sfr_history_reg26; /* offset : 0xd80 */
	union pcie_subctrl_sfr_history_reg27 sfr_history_reg27; /* offset : 0xd84 */
	union pcie_subctrl_sfr_history_reg28 sfr_history_reg28; /* offset : 0xd88 */
	union pcie_subctrl_sfr_history_reg29 sfr_history_reg29; /* offset : 0xd8c */
	union pcie_subctrl_sfr_history_reg30 sfr_history_reg30; /* offset : 0xd90 */
	union pcie_subctrl_sfr_history_reg31 sfr_history_reg31; /* offset : 0xd94 */
	union pcie_subctrl_sfr_ts_lsb_history_reg0 sfr_ts_lsb_history_reg0; /* offset : 0xd98 */
	union pcie_subctrl_sfr_ts_lsb_history_reg1 sfr_ts_lsb_history_reg1; /* offset : 0xd9c */
	union pcie_subctrl_sfr_ts_lsb_history_reg2 sfr_ts_lsb_history_reg2; /* offset : 0xda0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg3 sfr_ts_lsb_history_reg3; /* offset : 0xda4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg4 sfr_ts_lsb_history_reg4; /* offset : 0xda8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg5 sfr_ts_lsb_history_reg5; /* offset : 0xdac */
	union pcie_subctrl_sfr_ts_lsb_history_reg6 sfr_ts_lsb_history_reg6; /* offset : 0xdb0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg7 sfr_ts_lsb_history_reg7; /* offset : 0xdb4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg8 sfr_ts_lsb_history_reg8; /* offset : 0xdb8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg9 sfr_ts_lsb_history_reg9; /* offset : 0xdbc */
	union pcie_subctrl_sfr_ts_lsb_history_reg10 sfr_ts_lsb_history_reg10; /* offset : 0xdc0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg11 sfr_ts_lsb_history_reg11; /* offset : 0xdc4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg12 sfr_ts_lsb_history_reg12; /* offset : 0xdc8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg13 sfr_ts_lsb_history_reg13; /* offset : 0xdcc */
	union pcie_subctrl_sfr_ts_lsb_history_reg14 sfr_ts_lsb_history_reg14; /* offset : 0xdd0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg15 sfr_ts_lsb_history_reg15; /* offset : 0xdd4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg16 sfr_ts_lsb_history_reg16; /* offset : 0xdd8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg17 sfr_ts_lsb_history_reg17; /* offset : 0xddc */
	union pcie_subctrl_sfr_ts_lsb_history_reg18 sfr_ts_lsb_history_reg18; /* offset : 0xde0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg19 sfr_ts_lsb_history_reg19; /* offset : 0xde4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg20 sfr_ts_lsb_history_reg20; /* offset : 0xde8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg21 sfr_ts_lsb_history_reg21; /* offset : 0xdec */
	union pcie_subctrl_sfr_ts_lsb_history_reg22 sfr_ts_lsb_history_reg22; /* offset : 0xdf0 */
	union pcie_subctrl_sfr_ts_lsb_history_reg23 sfr_ts_lsb_history_reg23; /* offset : 0xdf4 */
	union pcie_subctrl_sfr_ts_lsb_history_reg24 sfr_ts_lsb_history_reg24; /* offset : 0xdf8 */
	union pcie_subctrl_sfr_ts_lsb_history_reg25 sfr_ts_lsb_history_reg25; /* offset : 0xdfc */
	union pcie_subctrl_sfr_ts_lsb_history_reg26 sfr_ts_lsb_history_reg26; /* offset : 0xe00 */
	union pcie_subctrl_sfr_ts_lsb_history_reg27 sfr_ts_lsb_history_reg27; /* offset : 0xe04 */
	union pcie_subctrl_sfr_ts_lsb_history_reg28 sfr_ts_lsb_history_reg28; /* offset : 0xe08 */
	union pcie_subctrl_sfr_ts_lsb_history_reg29 sfr_ts_lsb_history_reg29; /* offset : 0xe0c */
	union pcie_subctrl_sfr_ts_lsb_history_reg30 sfr_ts_lsb_history_reg30; /* offset : 0xe10 */
	union pcie_subctrl_sfr_ts_lsb_history_reg31 sfr_ts_lsb_history_reg31; /* offset : 0xe14 */
	union pcie_subctrl_sfr_ts_msb_history_reg0 sfr_ts_msb_history_reg0; /* offset : 0xe18 */
	union pcie_subctrl_sfr_ts_msb_history_reg1 sfr_ts_msb_history_reg1; /* offset : 0xe1c */
	union pcie_subctrl_sfr_ts_msb_history_reg2 sfr_ts_msb_history_reg2; /* offset : 0xe20 */
	union pcie_subctrl_sfr_ts_msb_history_reg3 sfr_ts_msb_history_reg3; /* offset : 0xe24 */
	union pcie_subctrl_sfr_ts_msb_history_reg4 sfr_ts_msb_history_reg4; /* offset : 0xe28 */
	union pcie_subctrl_sfr_ts_msb_history_reg5 sfr_ts_msb_history_reg5; /* offset : 0xe2c */
	union pcie_subctrl_sfr_ts_msb_history_reg6 sfr_ts_msb_history_reg6; /* offset : 0xe30 */
	union pcie_subctrl_sfr_ts_msb_history_reg7 sfr_ts_msb_history_reg7; /* offset : 0xe34 */
	union pcie_subctrl_sfr_ts_msb_history_reg8 sfr_ts_msb_history_reg8; /* offset : 0xe38 */
	union pcie_subctrl_sfr_ts_msb_history_reg9 sfr_ts_msb_history_reg9; /* offset : 0xe3c */
	union pcie_subctrl_sfr_ts_msb_history_reg10 sfr_ts_msb_history_reg10; /* offset : 0xe40 */
	union pcie_subctrl_sfr_ts_msb_history_reg11 sfr_ts_msb_history_reg11; /* offset : 0xe44 */
	union pcie_subctrl_sfr_ts_msb_history_reg12 sfr_ts_msb_history_reg12; /* offset : 0xe48 */
	union pcie_subctrl_sfr_ts_msb_history_reg13 sfr_ts_msb_history_reg13; /* offset : 0xe4c */
	union pcie_subctrl_sfr_ts_msb_history_reg14 sfr_ts_msb_history_reg14; /* offset : 0xe50 */
	union pcie_subctrl_sfr_ts_msb_history_reg15 sfr_ts_msb_history_reg15; /* offset : 0xe54 */
	union pcie_subctrl_sfr_ts_msb_history_reg16 sfr_ts_msb_history_reg16; /* offset : 0xe58 */
	union pcie_subctrl_sfr_ts_msb_history_reg17 sfr_ts_msb_history_reg17; /* offset : 0xe5c */
	union pcie_subctrl_sfr_ts_msb_history_reg18 sfr_ts_msb_history_reg18; /* offset : 0xe60 */
	union pcie_subctrl_sfr_ts_msb_history_reg19 sfr_ts_msb_history_reg19; /* offset : 0xe64 */
	union pcie_subctrl_sfr_ts_msb_history_reg20 sfr_ts_msb_history_reg20; /* offset : 0xe68 */
	union pcie_subctrl_sfr_ts_msb_history_reg21 sfr_ts_msb_history_reg21; /* offset : 0xe6c */
	union pcie_subctrl_sfr_ts_msb_history_reg22 sfr_ts_msb_history_reg22; /* offset : 0xe70 */
	union pcie_subctrl_sfr_ts_msb_history_reg23 sfr_ts_msb_history_reg23; /* offset : 0xe74 */
	union pcie_subctrl_sfr_ts_msb_history_reg24 sfr_ts_msb_history_reg24; /* offset : 0xe78 */
	union pcie_subctrl_sfr_ts_msb_history_reg25 sfr_ts_msb_history_reg25; /* offset : 0xe7c */
	union pcie_subctrl_sfr_ts_msb_history_reg26 sfr_ts_msb_history_reg26; /* offset : 0xe80 */
	union pcie_subctrl_sfr_ts_msb_history_reg27 sfr_ts_msb_history_reg27; /* offset : 0xe84 */
	union pcie_subctrl_sfr_ts_msb_history_reg28 sfr_ts_msb_history_reg28; /* offset : 0xe88 */
	union pcie_subctrl_sfr_ts_msb_history_reg29 sfr_ts_msb_history_reg29; /* offset : 0xe8c */
	union pcie_subctrl_sfr_ts_msb_history_reg30 sfr_ts_msb_history_reg30; /* offset : 0xe90 */
	union pcie_subctrl_sfr_ts_msb_history_reg31 sfr_ts_msb_history_reg31; /* offset : 0xe94 */
	union pcie_subctrl_sfr_pad_perst_n sfr_pad_perst_n; /* offset : 0xe98 */
	uint32_t reserved_23[89];
	union pcie_subctrl_sfr_phy_mac_rxstatus_31_0 sfr_phy_mac_rxstatus_31_0; /* offset : 0x1000 */
	union pcie_subctrl_sfr_phy_mac_rxstatus_47_32 sfr_phy_mac_rxstatus_47_32; /* offset : 0x1004 */
	union pcie_subctrl_sfr_mac_phy_messagebus_31_0 sfr_mac_phy_messagebus_31_0; /* offset : 0x1008 */
	union pcie_subctrl_sfr_mac_phy_messagebus_63_32 sfr_mac_phy_messagebus_63_32; /* offset : 0x100c */
	union pcie_subctrl_sfr_mac_phy_messagebus_95_64 sfr_mac_phy_messagebus_95_64; /* offset : 0x1010 */
	union pcie_subctrl_sfr_mac_phy_messagebus_127_96 sfr_mac_phy_messagebus_127_96; /* offset : 0x1014 */
	union pcie_subctrl_sfr_phy_cfg_30_reg sfr_phy_cfg_30_reg; /* offset : 0x1018 */
	union pcie_subctrl_sfr_phy_cfg_31_reg sfr_phy_cfg_31_reg; /* offset : 0x101c */
	union pcie_subctrl_sfr_phy_cfg_32_reg sfr_phy_cfg_32_reg; /* offset : 0x1020 */
	union pcie_subctrl_sfr_phy_cfg_33_reg sfr_phy_cfg_33_reg; /* offset : 0x1024 */
	union pcie_subctrl_sfr_phy_cfg_34_reg sfr_phy_cfg_34_reg; /* offset : 0x1028 */
	union pcie_subctrl_sfr_phy_cfg_35_reg sfr_phy_cfg_35_reg; /* offset : 0x102c */
	union pcie_subctrl_sfr_phy_cfg_36_reg sfr_phy_cfg_36_reg; /* offset : 0x1030 */
	union pcie_subctrl_sfr_phy_cfg_37_reg sfr_phy_cfg_37_reg; /* offset : 0x1034 */
	union pcie_subctrl_sfr_phy_cfg_38_reg sfr_phy_cfg_38_reg; /* offset : 0x1038 */
	union pcie_subctrl_sfr_phy_cfg_39_reg sfr_phy_cfg_39_reg; /* offset : 0x103c */
	union pcie_subctrl_sfr_phy_cfg_40_reg sfr_phy_cfg_40_reg; /* offset : 0x1040 */
	union pcie_subctrl_sfr_phy_cfg_41_reg sfr_phy_cfg_41_reg; /* offset : 0x1044 */
	union pcie_subctrl_sfr_phy_cfg_42_reg sfr_phy_cfg_42_reg; /* offset : 0x1048 */
	union pcie_subctrl_sfr_phy_cfg_43_reg sfr_phy_cfg_43_reg; /* offset : 0x104c */
	union pcie_subctrl_sfr_phy_cfg_44_reg sfr_phy_cfg_44_reg; /* offset : 0x1050 */
	union pcie_subctrl_sfr_phy_cfg_45_reg sfr_phy_cfg_45_reg; /* offset : 0x1054 */
	union pcie_subctrl_sfr_phy_cfg_46_reg sfr_phy_cfg_46_reg; /* offset : 0x1058 */
	union pcie_subctrl_sfr_phy_cfg_47_reg sfr_phy_cfg_47_reg; /* offset : 0x105c */
	union pcie_subctrl_sfr_phy_cfg_48_reg sfr_phy_cfg_48_reg; /* offset : 0x1060 */
	union pcie_subctrl_sfr_phy_cfg_49_reg sfr_phy_cfg_49_reg; /* offset : 0x1064 */
	union pcie_subctrl_sfr_phy_cfg_50_reg sfr_phy_cfg_50_reg; /* offset : 0x1068 */
	union pcie_subctrl_sfr_phy_cfg_51_reg sfr_phy_cfg_51_reg; /* offset : 0x106c */
	union pcie_subctrl_sfr_phy_cfg_52_reg sfr_phy_cfg_52_reg; /* offset : 0x1070 */
	union pcie_subctrl_sfr_phy_cfg_53_reg sfr_phy_cfg_53_reg; /* offset : 0x1074 */
	union pcie_subctrl_sfr_phy_cfg_54_reg sfr_phy_cfg_54_reg; /* offset : 0x1078 */
	union pcie_subctrl_sfr_phy_cfg_55_reg sfr_phy_cfg_55_reg; /* offset : 0x107c */
	union pcie_subctrl_sfr_phy_cfg_56_reg sfr_phy_cfg_56_reg; /* offset : 0x1080 */
	union pcie_subctrl_sfr_phy_cfg_57_reg sfr_phy_cfg_57_reg; /* offset : 0x1084 */
	union pcie_subctrl_sfr_phy_cfg_58_reg sfr_phy_cfg_58_reg; /* offset : 0x1088 */
	union pcie_subctrl_sfr_phy_cfg_59_reg sfr_phy_cfg_59_reg; /* offset : 0x108c */
	union pcie_subctrl_sfr_phy_cfg_60_reg sfr_phy_cfg_60_reg; /* offset : 0x1090 */
	union pcie_subctrl_sfr_phy_cfg_61_reg sfr_phy_cfg_61_reg; /* offset : 0x1094 */
	union pcie_subctrl_sfr_phy_cfg_62_reg sfr_phy_cfg_62_reg; /* offset : 0x1098 */
	union pcie_subctrl_sfr_phy_cfg_63_reg sfr_phy_cfg_63_reg; /* offset : 0x109c */
	union pcie_subctrl_sfr_phy_cfg_64_reg sfr_phy_cfg_64_reg; /* offset : 0x10a0 */
	union pcie_subctrl_sfr_phy_cfg_65_reg sfr_phy_cfg_65_reg; /* offset : 0x10a4 */
	union pcie_subctrl_sfr_phy_cfg_66_reg sfr_phy_cfg_66_reg; /* offset : 0x10a8 */
	union pcie_subctrl_sfr_phy_cfg_67_reg sfr_phy_cfg_67_reg; /* offset : 0x10ac */
	union pcie_subctrl_sfr_phy_cfg_68_reg sfr_phy_cfg_68_reg; /* offset : 0x10b0 */
	union pcie_subctrl_sfr_phy_cfg_69_reg sfr_phy_cfg_69_reg; /* offset : 0x10b4 */
	union pcie_subctrl_sfr_phy_cfg_70_reg sfr_phy_cfg_70_reg; /* offset : 0x10b8 */
	union pcie_subctrl_sfr_phy_cfg_71_reg sfr_phy_cfg_71_reg; /* offset : 0x10bc */
	union pcie_subctrl_sfr_phy_cfg_72_reg sfr_phy_cfg_72_reg; /* offset : 0x10c0 */
	union pcie_subctrl_sfr_phy_cfg_73_reg sfr_phy_cfg_73_reg; /* offset : 0x10c4 */
	union pcie_subctrl_sfr_phy_cfg_74_reg sfr_phy_cfg_74_reg; /* offset : 0x10c8 */
	union pcie_subctrl_sfr_phy_cfg_75_reg sfr_phy_cfg_75_reg; /* offset : 0x10cc */
	union pcie_subctrl_sfr_phy_cfg_76_reg sfr_phy_cfg_76_reg; /* offset : 0x10d0 */
	union pcie_subctrl_sfr_phy_cfg_77_reg sfr_phy_cfg_77_reg; /* offset : 0x10d4 */
	union pcie_subctrl_sfr_phy_cfg_78_reg sfr_phy_cfg_78_reg; /* offset : 0x10d8 */
	union pcie_subctrl_sfr_phy_cfg_79_reg sfr_phy_cfg_79_reg; /* offset : 0x10dc */
	union pcie_subctrl_sfr_phy_cfg_80_reg sfr_phy_cfg_80_reg; /* offset : 0x10e0 */
	union pcie_subctrl_sfr_phy_cfg_81_reg sfr_phy_cfg_81_reg; /* offset : 0x10e4 */
	union pcie_subctrl_sfr_phy_cfg_82_reg sfr_phy_cfg_82_reg; /* offset : 0x10e8 */
	union pcie_subctrl_sfr_phy_cfg_83_reg sfr_phy_cfg_83_reg; /* offset : 0x10ec */
	union pcie_subctrl_sfr_phy_cfg_84_reg sfr_phy_cfg_84_reg; /* offset : 0x10f0 */
	union pcie_subctrl_sfr_phy_cfg_85_reg sfr_phy_cfg_85_reg; /* offset : 0x10f4 */
	union pcie_subctrl_sfr_phy_cfg_86_reg sfr_phy_cfg_86_reg; /* offset : 0x10f8 */
	union pcie_subctrl_sfr_phy_cfg_87_reg sfr_phy_cfg_87_reg; /* offset : 0x10fc */
	union pcie_subctrl_sfr_phy_cfg_88_reg sfr_phy_cfg_88_reg; /* offset : 0x1100 */
	union pcie_subctrl_sfr_phy_cfg_89_reg sfr_phy_cfg_89_reg; /* offset : 0x1104 */
	union pcie_subctrl_sfr_phy_cfg_90_reg sfr_phy_cfg_90_reg; /* offset : 0x1108 */
	union pcie_subctrl_sfr_phy_cfg_91_reg sfr_phy_cfg_91_reg; /* offset : 0x110c */
	union pcie_subctrl_sfr_phy_cfg_92_reg sfr_phy_cfg_92_reg; /* offset : 0x1110 */
	union pcie_subctrl_sfr_phy_cfg_93_reg sfr_phy_cfg_93_reg; /* offset : 0x1114 */
	union pcie_subctrl_sfr_phy_cfg_94_reg sfr_phy_cfg_94_reg; /* offset : 0x1118 */
	union pcie_subctrl_sfr_phy_cfg_95_reg sfr_phy_cfg_95_reg; /* offset : 0x111c */
	union pcie_subctrl_sfr_phy_cfg_96_reg sfr_phy_cfg_96_reg; /* offset : 0x1120 */
	union pcie_subctrl_sfr_phy_cfg_97_reg sfr_phy_cfg_97_reg; /* offset : 0x1124 */
	union pcie_subctrl_sfr_phy_cfg_98_reg sfr_phy_cfg_98_reg; /* offset : 0x1128 */
	union pcie_subctrl_sfr_phy_cfg_99_reg sfr_phy_cfg_99_reg; /* offset : 0x112c */
	union pcie_subctrl_sfr_phy_cfg_100_reg sfr_phy_cfg_100_reg; /* offset : 0x1130 */
	union pcie_subctrl_sfr_phy_cfg_101_reg sfr_phy_cfg_101_reg; /* offset : 0x1134 */
	union pcie_subctrl_sfr_phy_cfg_102_reg sfr_phy_cfg_102_reg; /* offset : 0x1138 */
	union pcie_subctrl_sfr_phy_cfg_103_reg sfr_phy_cfg_103_reg; /* offset : 0x113c */
	union pcie_subctrl_sfr_phy_cfg_104_reg sfr_phy_cfg_104_reg; /* offset : 0x1140 */
	union pcie_subctrl_sfr_phy_cfg_105_reg sfr_phy_cfg_105_reg; /* offset : 0x1144 */
	union pcie_subctrl_sfr_phy_cfg_106_reg sfr_phy_cfg_106_reg; /* offset : 0x1148 */
	union pcie_subctrl_sfr_phy_cfg_107_reg sfr_phy_cfg_107_reg; /* offset : 0x114c */
	union pcie_subctrl_sfr_phy_cfg_108_reg sfr_phy_cfg_108_reg; /* offset : 0x1150 */
	union pcie_subctrl_sfr_phy_cfg_109_reg sfr_phy_cfg_109_reg; /* offset : 0x1154 */
	union pcie_subctrl_sfr_phy_cfg_110_reg sfr_phy_cfg_110_reg; /* offset : 0x1158 */
	union pcie_subctrl_sfr_phy_cfg_111_reg sfr_phy_cfg_111_reg; /* offset : 0x115c */
	union pcie_subctrl_sfr_phy_cfg_112_reg sfr_phy_cfg_112_reg; /* offset : 0x1160 */
	union pcie_subctrl_sfr_phy_cfg_113_reg sfr_phy_cfg_113_reg; /* offset : 0x1164 */
	union pcie_subctrl_sfr_phy_cfg_114_reg sfr_phy_cfg_114_reg; /* offset : 0x1168 */
	union pcie_subctrl_sfr_phy_cfg_115_reg sfr_phy_cfg_115_reg; /* offset : 0x116c */
	union pcie_subctrl_sfr_phy_cfg_116_reg sfr_phy_cfg_116_reg; /* offset : 0x1170 */
	union pcie_subctrl_sfr_phy_cfg_117_reg sfr_phy_cfg_117_reg; /* offset : 0x1174 */
	union pcie_subctrl_sfr_phy_cfg_118_reg sfr_phy_cfg_118_reg; /* offset : 0x1178 */
	union pcie_subctrl_sfr_phy_cfg_119_reg sfr_phy_cfg_119_reg; /* offset : 0x117c */
	union pcie_subctrl_sfr_phy_cfg_217_reg sfr_phy_cfg_217_reg; /* offset : 0x1180 */
	union pcie_subctrl_sfr_phy_cfg_218_reg sfr_phy_cfg_218_reg; /* offset : 0x1184 */
	union pcie_subctrl_sfr_phy_cfg_219_reg sfr_phy_cfg_219_reg; /* offset : 0x1188 */
	union pcie_subctrl_sfr_phy_cfg_220_reg sfr_phy_cfg_220_reg; /* offset : 0x118c */
	union pcie_subctrl_sfr_phy_cfg_221_reg sfr_phy_cfg_221_reg; /* offset : 0x1190 */
	union pcie_subctrl_sfr_phy_cfg_222_reg sfr_phy_cfg_222_reg; /* offset : 0x1194 */
	union pcie_subctrl_sfr_phy_cfg_223_reg sfr_phy_cfg_223_reg; /* offset : 0x1198 */
	union pcie_subctrl_sfr_phy_cfg_224_reg sfr_phy_cfg_224_reg; /* offset : 0x119c */
	union pcie_subctrl_sfr_phy_cfg_225_reg sfr_phy_cfg_225_reg; /* offset : 0x11a0 */
	union pcie_subctrl_sfr_phy_cfg_226_reg sfr_phy_cfg_226_reg; /* offset : 0x11a4 */
	union pcie_subctrl_sfr_phy_cfg_227_reg sfr_phy_cfg_227_reg; /* offset : 0x11a8 */
	union pcie_subctrl_sfr_phy_cfg_228_reg sfr_phy_cfg_228_reg; /* offset : 0x11ac */
	union pcie_subctrl_sfr_phy_cfg_229_reg sfr_phy_cfg_229_reg; /* offset : 0x11b0 */
	union pcie_subctrl_sfr_phy_cfg_230_reg sfr_phy_cfg_230_reg; /* offset : 0x11b4 */
	union pcie_subctrl_sfr_phy_cfg_231_reg sfr_phy_cfg_231_reg; /* offset : 0x11b8 */
	union pcie_subctrl_sfr_phy_cfg_232_reg sfr_phy_cfg_232_reg; /* offset : 0x11bc */
	union pcie_subctrl_sfr_phy_cfg_233_reg sfr_phy_cfg_233_reg; /* offset : 0x11c0 */
	union pcie_subctrl_sfr_phy_cfg_234_reg sfr_phy_cfg_234_reg; /* offset : 0x11c4 */
	union pcie_subctrl_sfr_phy_cfg_235_reg sfr_phy_cfg_235_reg; /* offset : 0x11c8 */
	union pcie_subctrl_sfr_phy_cfg_236_reg sfr_phy_cfg_236_reg; /* offset : 0x11cc */
	union pcie_subctrl_sfr_phy_cfg_237_reg sfr_phy_cfg_237_reg; /* offset : 0x11d0 */
	union pcie_subctrl_sfr_phy_cfg_238_reg sfr_phy_cfg_238_reg; /* offset : 0x11d4 */
	union pcie_subctrl_sfr_phy_cfg_239_reg sfr_phy_cfg_239_reg; /* offset : 0x11d8 */
	union pcie_subctrl_sfr_phy_cfg_240_reg sfr_phy_cfg_240_reg; /* offset : 0x11dc */
	union pcie_subctrl_sfr_phy_cfg_241_reg sfr_phy_cfg_241_reg; /* offset : 0x11e0 */
	union pcie_subctrl_sfr_phy_cfg_242_reg sfr_phy_cfg_242_reg; /* offset : 0x11e4 */
	union pcie_subctrl_sfr_phy_cfg_243_reg sfr_phy_cfg_243_reg; /* offset : 0x11e8 */
	union pcie_subctrl_sfr_phy_cfg_244_reg sfr_phy_cfg_244_reg; /* offset : 0x11ec */
	union pcie_subctrl_sfr_phy_cfg_245_reg sfr_phy_cfg_245_reg; /* offset : 0x11f0 */
	union pcie_subctrl_sfr_phy_cfg_246_reg sfr_phy_cfg_246_reg; /* offset : 0x11f4 */
	union pcie_subctrl_sfr_phy_cfg_247_reg sfr_phy_cfg_247_reg; /* offset : 0x11f8 */
	union pcie_subctrl_sfr_phy_cfg_248_reg sfr_phy_cfg_248_reg; /* offset : 0x11fc */
	union pcie_subctrl_sfr_phy_cfg_249_reg sfr_phy_cfg_249_reg; /* offset : 0x1200 */
	union pcie_subctrl_sfr_phy_cfg_250_reg sfr_phy_cfg_250_reg; /* offset : 0x1204 */
	union pcie_subctrl_sfr_phy_cfg_251_reg sfr_phy_cfg_251_reg; /* offset : 0x1208 */
	union pcie_subctrl_sfr_phy_cfg_252_reg sfr_phy_cfg_252_reg; /* offset : 0x120c */
	union pcie_subctrl_sfr_phy_cfg_253_reg sfr_phy_cfg_253_reg; /* offset : 0x1210 */
	union pcie_subctrl_sfr_phy_cfg_254_reg sfr_phy_cfg_254_reg; /* offset : 0x1214 */
	union pcie_subctrl_sfr_phy_cfg_255_reg sfr_phy_cfg_255_reg; /* offset : 0x1218 */
	union pcie_subctrl_sfr_phy_cfg_256_reg sfr_phy_cfg_256_reg; /* offset : 0x121c */
	union pcie_subctrl_sfr_phy_cfg_257_reg sfr_phy_cfg_257_reg; /* offset : 0x1220 */
	union pcie_subctrl_sfr_phy_cfg_258_reg sfr_phy_cfg_258_reg; /* offset : 0x1224 */
	union pcie_subctrl_sfr_phy_cfg_259_reg sfr_phy_cfg_259_reg; /* offset : 0x1228 */
	union pcie_subctrl_sfr_phy_cfg_260_reg sfr_phy_cfg_260_reg; /* offset : 0x122c */
	union pcie_subctrl_sfr_phy_cfg_261_reg sfr_phy_cfg_261_reg; /* offset : 0x1230 */
	union pcie_subctrl_sfr_phy_cfg_262_reg sfr_phy_cfg_262_reg; /* offset : 0x1234 */
	union pcie_subctrl_sfr_phy_cfg_263_reg sfr_phy_cfg_263_reg; /* offset : 0x1238 */
	union pcie_subctrl_sfr_phy_cfg_264_reg sfr_phy_cfg_264_reg; /* offset : 0x123c */
	union pcie_subctrl_sfr_phy_cfg_265_reg sfr_phy_cfg_265_reg; /* offset : 0x1240 */
	union pcie_subctrl_sfr_phy_cfg_266_reg sfr_phy_cfg_266_reg; /* offset : 0x1244 */
	union pcie_subctrl_sfr_phy_cfg_267_reg sfr_phy_cfg_267_reg; /* offset : 0x1248 */
	union pcie_subctrl_sfr_phy_cfg_268_reg sfr_phy_cfg_268_reg; /* offset : 0x124c */
	union pcie_subctrl_sfr_phy_cfg_269_reg sfr_phy_cfg_269_reg; /* offset : 0x1250 */
	union pcie_subctrl_sfr_phy_cfg_270_reg sfr_phy_cfg_270_reg; /* offset : 0x1254 */
	union pcie_subctrl_sfr_phy_cfg_271_reg sfr_phy_cfg_271_reg; /* offset : 0x1258 */
	union pcie_subctrl_sfr_phy_cfg_272_reg sfr_phy_cfg_272_reg; /* offset : 0x125c */
	union pcie_subctrl_sfr_phy_cfg_273_reg sfr_phy_cfg_273_reg; /* offset : 0x1260 */
	union pcie_subctrl_sfr_phy_cfg_274_reg sfr_phy_cfg_274_reg; /* offset : 0x1264 */
	union pcie_subctrl_sfr_phy_cfg_275_reg sfr_phy_cfg_275_reg; /* offset : 0x1268 */
	union pcie_subctrl_sfr_phy_cfg_276_reg sfr_phy_cfg_276_reg; /* offset : 0x126c */
	union pcie_subctrl_sfr_phy_cfg_277_reg sfr_phy_cfg_277_reg; /* offset : 0x1270 */
	union pcie_subctrl_sfr_phy_cfg_278_reg sfr_phy_cfg_278_reg; /* offset : 0x1274 */
	union pcie_subctrl_sfr_phy_cfg_279_reg sfr_phy_cfg_279_reg; /* offset : 0x1278 */
	union pcie_subctrl_sfr_phy_cfg_280_reg sfr_phy_cfg_280_reg; /* offset : 0x127c */
	union pcie_subctrl_sfr_phy_cfg_281_reg sfr_phy_cfg_281_reg; /* offset : 0x1280 */
	union pcie_subctrl_sfr_phy_cfg_282_reg sfr_phy_cfg_282_reg; /* offset : 0x1284 */
	union pcie_subctrl_sfr_phy_cfg_283_reg sfr_phy_cfg_283_reg; /* offset : 0x1288 */
	union pcie_subctrl_sfr_phy_cfg_284_reg sfr_phy_cfg_284_reg; /* offset : 0x128c */
	union pcie_subctrl_sfr_phy_cfg_285_reg sfr_phy_cfg_285_reg; /* offset : 0x1290 */
	union pcie_subctrl_sfr_phy_cfg_286_reg sfr_phy_cfg_286_reg; /* offset : 0x1294 */
	union pcie_subctrl_sfr_phy_cfg_287_reg sfr_phy_cfg_287_reg; /* offset : 0x1298 */
	union pcie_subctrl_sfr_phy_cfg_288_reg sfr_phy_cfg_288_reg; /* offset : 0x129c */
	union pcie_subctrl_sfr_phy_cfg_289_reg sfr_phy_cfg_289_reg; /* offset : 0x12a0 */
	union pcie_subctrl_sfr_phy_cfg_290_reg sfr_phy_cfg_290_reg; /* offset : 0x12a4 */
	union pcie_subctrl_sfr_phy_cfg_291_reg sfr_phy_cfg_291_reg; /* offset : 0x12a8 */
	union pcie_subctrl_sfr_phy_cfg_292_reg sfr_phy_cfg_292_reg; /* offset : 0x12ac */
	union pcie_subctrl_sfr_phy_cfg_293_reg sfr_phy_cfg_293_reg; /* offset : 0x12b0 */
	union pcie_subctrl_sfr_phy_cfg_294_reg sfr_phy_cfg_294_reg; /* offset : 0x12b4 */
	union pcie_subctrl_sfr_phy_cfg_295_reg sfr_phy_cfg_295_reg; /* offset : 0x12b8 */
	union pcie_subctrl_sfr_phy_cfg_296_reg sfr_phy_cfg_296_reg; /* offset : 0x12bc */
	union pcie_subctrl_sfr_phy_cfg_297_reg sfr_phy_cfg_297_reg; /* offset : 0x12c0 */
	union pcie_subctrl_sfr_phy_cfg_298_reg sfr_phy_cfg_298_reg; /* offset : 0x12c4 */
	union pcie_subctrl_sfr_phy_cfg_299_reg sfr_phy_cfg_299_reg; /* offset : 0x12c8 */
	union pcie_subctrl_sfr_phy_cfg_300_reg sfr_phy_cfg_300_reg; /* offset : 0x12cc */
	union pcie_subctrl_sfr_phy_cfg_301_reg sfr_phy_cfg_301_reg; /* offset : 0x12d0 */
	union pcie_subctrl_sfr_phy_cfg_302_reg sfr_phy_cfg_302_reg; /* offset : 0x12d4 */
	union pcie_subctrl_sfr_phy_cfg_303_reg sfr_phy_cfg_303_reg; /* offset : 0x12d8 */
	union pcie_subctrl_sfr_phy_cfg_304_reg sfr_phy_cfg_304_reg; /* offset : 0x12dc */
	union pcie_subctrl_sfr_phy_cfg_305_reg sfr_phy_cfg_305_reg; /* offset : 0x12e0 */
	union pcie_subctrl_sfr_phy_cfg_306_reg sfr_phy_cfg_306_reg; /* offset : 0x12e4 */
	union pcie_subctrl_sfr_phy_cfg_307_reg sfr_phy_cfg_307_reg; /* offset : 0x12e8 */
	union pcie_subctrl_sfr_phy_cfg_308_reg sfr_phy_cfg_308_reg; /* offset : 0x12ec */
	union pcie_subctrl_sfr_phy_cfg_309_reg sfr_phy_cfg_309_reg; /* offset : 0x12f0 */
	union pcie_subctrl_sfr_phy_cfg_310_reg sfr_phy_cfg_310_reg; /* offset : 0x12f4 */
	union pcie_subctrl_sfr_phy_cfg_311_reg sfr_phy_cfg_311_reg; /* offset : 0x12f8 */
	union pcie_subctrl_sfr_phy_cfg_312_reg sfr_phy_cfg_312_reg; /* offset : 0x12fc */
	union pcie_subctrl_sfr_phy_cfg_313_reg sfr_phy_cfg_313_reg; /* offset : 0x1300 */
	union pcie_subctrl_sfr_phy_cfg_314_reg sfr_phy_cfg_314_reg; /* offset : 0x1304 */
	union pcie_subctrl_sfr_phy_cfg_315_reg sfr_phy_cfg_315_reg; /* offset : 0x1308 */
	union pcie_subctrl_sfr_phy_cfg_316_reg sfr_phy_cfg_316_reg; /* offset : 0x130c */
	union pcie_subctrl_sfr_phy_cfg_317_reg sfr_phy_cfg_317_reg; /* offset : 0x1310 */
	union pcie_subctrl_sfr_phy_cfg_318_reg sfr_phy_cfg_318_reg; /* offset : 0x1314 */
	union pcie_subctrl_sfr_phy_cfg_319_reg sfr_phy_cfg_319_reg; /* offset : 0x1318 */
	union pcie_subctrl_sfr_phy_cfg_320_reg sfr_phy_cfg_320_reg; /* offset : 0x131c */
	union pcie_subctrl_sfr_phy_cfg_321_reg sfr_phy_cfg_321_reg; /* offset : 0x1320 */
	union pcie_subctrl_sfr_phy_cfg_322_reg sfr_phy_cfg_322_reg; /* offset : 0x1324 */
	union pcie_subctrl_sfr_phy_cfg_323_reg sfr_phy_cfg_323_reg; /* offset : 0x1328 */
	union pcie_subctrl_sfr_phy_cfg_324_reg sfr_phy_cfg_324_reg; /* offset : 0x132c */
	union pcie_subctrl_sfr_phy_cfg_325_reg sfr_phy_cfg_325_reg; /* offset : 0x1330 */
	union pcie_subctrl_sfr_phy_cfg_326_reg sfr_phy_cfg_326_reg; /* offset : 0x1334 */
	union pcie_subctrl_sfr_phy_cfg_327_reg sfr_phy_cfg_327_reg; /* offset : 0x1338 */
	union pcie_subctrl_sfr_phy_cfg_328_reg sfr_phy_cfg_328_reg; /* offset : 0x133c */
	union pcie_subctrl_sfr_phy_cfg_329_reg sfr_phy_cfg_329_reg; /* offset : 0x1340 */
	union pcie_subctrl_sfr_phy_cfg_330_reg sfr_phy_cfg_330_reg; /* offset : 0x1344 */
	union pcie_subctrl_sfr_phy_cfg_331_reg sfr_phy_cfg_331_reg; /* offset : 0x1348 */
	union pcie_subctrl_sfr_phy_cfg_332_reg sfr_phy_cfg_332_reg; /* offset : 0x134c */
	union pcie_subctrl_sfr_phy_cfg_333_reg sfr_phy_cfg_333_reg; /* offset : 0x1350 */
	union pcie_subctrl_sfr_phy_cfg_334_reg sfr_phy_cfg_334_reg; /* offset : 0x1354 */
	union pcie_subctrl_sfr_phy_cfg_335_reg sfr_phy_cfg_335_reg; /* offset : 0x1358 */
	union pcie_subctrl_sfr_phy_cfg_336_reg sfr_phy_cfg_336_reg; /* offset : 0x135c */
	union pcie_subctrl_sfr_phy_cfg_337_reg sfr_phy_cfg_337_reg; /* offset : 0x1360 */
	union pcie_subctrl_sfr_phy_cfg_338_reg sfr_phy_cfg_338_reg; /* offset : 0x1364 */
	union pcie_subctrl_sfr_phy_cfg_339_reg sfr_phy_cfg_339_reg; /* offset : 0x1368 */
	union pcie_subctrl_sfr_phy_cfg_340_reg sfr_phy_cfg_340_reg; /* offset : 0x136c */
	union pcie_subctrl_sfr_phy_cfg_341_reg sfr_phy_cfg_341_reg; /* offset : 0x1370 */
	union pcie_subctrl_sfr_phy_cfg_342_reg sfr_phy_cfg_342_reg; /* offset : 0x1374 */
	union pcie_subctrl_sfr_phy_cfg_343_reg sfr_phy_cfg_343_reg; /* offset : 0x1378 */
	union pcie_subctrl_sfr_phy_cfg_344_reg sfr_phy_cfg_344_reg; /* offset : 0x137c */
	union pcie_subctrl_sfr_phy_cfg_345_reg sfr_phy_cfg_345_reg; /* offset : 0x1380 */
	union pcie_subctrl_sfr_phy_cfg_346_reg sfr_phy_cfg_346_reg; /* offset : 0x1384 */
	union pcie_subctrl_sfr_phy_cfg_347_reg sfr_phy_cfg_347_reg; /* offset : 0x1388 */
	union pcie_subctrl_sfr_phy_cfg_348_reg sfr_phy_cfg_348_reg; /* offset : 0x138c */
	union pcie_subctrl_sfr_phy_cfg_349_reg sfr_phy_cfg_349_reg; /* offset : 0x1390 */
	union pcie_subctrl_sfr_phy_cfg_350_reg sfr_phy_cfg_350_reg; /* offset : 0x1394 */
	union pcie_subctrl_sfr_phy_cfg_351_reg sfr_phy_cfg_351_reg; /* offset : 0x1398 */
	union pcie_subctrl_sfr_phy_cfg_352_reg sfr_phy_cfg_352_reg; /* offset : 0x139c */
	union pcie_subctrl_sfr_phy_cfg_353_reg sfr_phy_cfg_353_reg; /* offset : 0x13a0 */
	union pcie_subctrl_sfr_phy_cfg_354_reg sfr_phy_cfg_354_reg; /* offset : 0x13a4 */
	union pcie_subctrl_sfr_phy_cfg_355_reg sfr_phy_cfg_355_reg; /* offset : 0x13a8 */
	union pcie_subctrl_sfr_phy_cfg_356_reg sfr_phy_cfg_356_reg; /* offset : 0x13ac */
	union pcie_subctrl_sfr_phy_cfg_357_reg sfr_phy_cfg_357_reg; /* offset : 0x13b0 */
	union pcie_subctrl_sfr_phy_cfg_358_reg sfr_phy_cfg_358_reg; /* offset : 0x13b4 */
	union pcie_subctrl_sfr_phy_cfg_359_reg sfr_phy_cfg_359_reg; /* offset : 0x13b8 */
	union pcie_subctrl_sfr_phy_cfg_360_reg sfr_phy_cfg_360_reg; /* offset : 0x13bc */
	union pcie_subctrl_sfr_phy_cfg_363_reg sfr_phy_cfg_363_reg; /* offset : 0x13c0 */
	union pcie_subctrl_sfr_phy_cfg_367_reg sfr_phy_cfg_367_reg; /* offset : 0x13c4 */
	union pcie_subctrl_sfr_phy_cfg_369_reg sfr_phy_cfg_369_reg; /* offset : 0x13c8 */
	union pcie_subctrl_sfr_phy_cfg_370_reg sfr_phy_cfg_370_reg; /* offset : 0x13cc */
	union pcie_subctrl_sfr_phy_cfg_371_reg sfr_phy_cfg_371_reg; /* offset : 0x13d0 */
	union pcie_subctrl_sfr_phy_cfg_372_reg sfr_phy_cfg_372_reg; /* offset : 0x13d4 */
	union pcie_subctrl_sfr_phy_cfg_373_reg sfr_phy_cfg_373_reg; /* offset : 0x13d8 */
	union pcie_subctrl_sfr_phy_cfg_374_reg sfr_phy_cfg_374_reg; /* offset : 0x13dc */
	union pcie_subctrl_sfr_phy_cfg_375_reg sfr_phy_cfg_375_reg; /* offset : 0x13e0 */
	union pcie_subctrl_sfr_phy_cfg_376_reg sfr_phy_cfg_376_reg; /* offset : 0x13e4 */
	union pcie_subctrl_sfr_phy_cfg_377_reg sfr_phy_cfg_377_reg; /* offset : 0x13e8 */
	union pcie_subctrl_sfr_phy_cfg_378_reg sfr_phy_cfg_378_reg; /* offset : 0x13ec */
	union pcie_subctrl_sfr_phy_cfg_379_reg sfr_phy_cfg_379_reg; /* offset : 0x13f0 */
	union pcie_subctrl_sfr_phy_cfg_380_reg sfr_phy_cfg_380_reg; /* offset : 0x13f4 */
	union pcie_subctrl_sfr_phy_cfg_381_reg sfr_phy_cfg_381_reg; /* offset : 0x13f8 */
	union pcie_subctrl_sfr_phy_cfg_382_reg sfr_phy_cfg_382_reg; /* offset : 0x13fc */
	uint32_t reserved_24[770];
	union pcie_subctrl_sfr_cfg_cor_err_rpt_en sfr_cfg_cor_err_rpt_en; /* offset : 0x2008 */
	uint32_t reserved_25[3];
	union pcie_subctrl_sfr_cfg_f_err_rpt_en sfr_cfg_f_err_rpt_en; /* offset : 0x2018 */
	uint32_t reserved_26[2];
	union pcie_subctrl_sfr_cfg_nf_err_rpt_en sfr_cfg_nf_err_rpt_en; /* offset : 0x2024 */
	uint32_t reserved_27[2];
	union pcie_subctrl_sfr_cfg_reg_serren sfr_cfg_reg_serren; /* offset : 0x2030 */
	uint32_t reserved_28[5];
	union pcie_subctrl_sfr_pm_en_core_clk sfr_pm_en_core_clk; /* offset : 0x2048 */
	union pcie_subctrl_sfr_pm_l1_entry_started sfr_pm_l1_entry_started; /* offset : 0x204c */
	union pcie_subctrl_sfr_radm_trgt1_vc sfr_radm_trgt1_vc; /* offset : 0x2050 */
	union pcie_subctrl_sfr_mac_phy_rxelecidle_disable sfr_mac_phy_rxelecidle_disable; /* offset : 0x2054 */
	union pcie_subctrl_sfr_mac_phy_txcommonmode_disable sfr_mac_phy_txcommonmode_disable; /* offset : 0x2058 */
	union pcie_subctrl_sfr_assert_inta_grt sfr_assert_inta_grt; /* offset : 0x205c */
	union pcie_subctrl_sfr_assert_intb_grt sfr_assert_intb_grt; /* offset : 0x2060 */
	union pcie_subctrl_sfr_assert_intc_grt sfr_assert_intc_grt; /* offset : 0x2064 */
	union pcie_subctrl_sfr_assert_intd_grt sfr_assert_intd_grt; /* offset : 0x2068 */
	uint32_t reserved_29[7];
	union pcie_subctrl_sfr_deassert_inta_grt sfr_deassert_inta_grt; /* offset : 0x2088 */
	union pcie_subctrl_sfr_deassert_intb_grt sfr_deassert_intb_grt; /* offset : 0x208c */
	union pcie_subctrl_sfr_deassert_intc_grt sfr_deassert_intc_grt; /* offset : 0x2090 */
	union pcie_subctrl_sfr_deassert_intd_grt sfr_deassert_intd_grt; /* offset : 0x2094 */
	uint32_t reserved_30[12];
	union pcie_subctrl_sfr_ptrc_event_foundry_sig_31_0 sfr_ptrc_event_foundry_sig_31_0; /* offset : 0x20c8 */
	union pcie_subctrl_sfr_ptrc_event_foundry_sig_63_32 sfr_ptrc_event_foundry_sig_63_32; /* offset : 0x20cc */
	uint32_t reserved_31[6];
	union pcie_subctrl_sfr_app_l1sub_disable sfr_app_l1sub_disable; /* offset : 0x20e8 */
	union pcie_subctrl_sfr_phy_cfg_0_reg sfr_phy_cfg_0_reg; /* offset : 0x20ec */
	union pcie_subctrl_sfr_phy_cfg_1_reg sfr_phy_cfg_1_reg; /* offset : 0x20f0 */
	union pcie_subctrl_sfr_phy_cfg_2_reg sfr_phy_cfg_2_reg; /* offset : 0x20f4 */
	union pcie_subctrl_sfr_phy_cfg_3_reg sfr_phy_cfg_3_reg; /* offset : 0x20f8 */
	union pcie_subctrl_sfr_phy_cfg_4_reg sfr_phy_cfg_4_reg; /* offset : 0x20fc */
	union pcie_subctrl_sfr_phy_cfg_5_reg sfr_phy_cfg_5_reg; /* offset : 0x2100 */
	union pcie_subctrl_sfr_phy_cfg_6_reg sfr_phy_cfg_6_reg; /* offset : 0x2104 */
	union pcie_subctrl_sfr_phy_cfg_7_reg sfr_phy_cfg_7_reg; /* offset : 0x2108 */
	union pcie_subctrl_sfr_phy_cfg_8_reg sfr_phy_cfg_8_reg; /* offset : 0x210c */
	union pcie_subctrl_sfr_phy_cfg_9_reg sfr_phy_cfg_9_reg; /* offset : 0x2110 */
	union pcie_subctrl_sfr_phy_cfg_10_reg sfr_phy_cfg_10_reg; /* offset : 0x2114 */
	union pcie_subctrl_sfr_phy_cfg_11_reg sfr_phy_cfg_11_reg; /* offset : 0x2118 */
	union pcie_subctrl_sfr_phy_cfg_12_reg sfr_phy_cfg_12_reg; /* offset : 0x211c */
	union pcie_subctrl_sfr_phy_cfg_13_reg sfr_phy_cfg_13_reg; /* offset : 0x2120 */
	union pcie_subctrl_sfr_phy_cfg_14_reg sfr_phy_cfg_14_reg; /* offset : 0x2124 */
	uint32_t reserved_32[2];
	union pcie_subctrl_sfr_phy_cfg_17_reg sfr_phy_cfg_17_reg; /* offset : 0x2130 */
	union pcie_subctrl_sfr_phy_cfg_18_reg sfr_phy_cfg_18_reg; /* offset : 0x2134 */
	union pcie_subctrl_sfr_phy_cfg_19_reg sfr_phy_cfg_19_reg; /* offset : 0x2138 */
	union pcie_subctrl_sfr_phy_cfg_20_reg sfr_phy_cfg_20_reg; /* offset : 0x213c */
	union pcie_subctrl_sfr_phy_cfg_21_reg sfr_phy_cfg_21_reg; /* offset : 0x2140 */
	union pcie_subctrl_sfr_phy_cfg_22_reg sfr_phy_cfg_22_reg; /* offset : 0x2144 */
	union pcie_subctrl_sfr_phy_cfg_23_reg sfr_phy_cfg_23_reg; /* offset : 0x2148 */
	uint32_t reserved_33[3];
	union pcie_subctrl_sfr_phy_cfg_27_reg sfr_phy_cfg_27_reg; /* offset : 0x2158 */
	union pcie_subctrl_sfr_phy_cfg_28_reg sfr_phy_cfg_28_reg; /* offset : 0x215c */
	union pcie_subctrl_sfr_phy_cfg_29_reg sfr_phy_cfg_29_reg; /* offset : 0x2160 */
	union pcie_subctrl_sfr_cfg_ext_tag_en sfr_cfg_ext_tag_en; /* offset : 0x2164 */
	union pcie_subctrl_sfr_cfg_msi_64 sfr_cfg_msi_64; /* offset : 0x2168 */
	union pcie_subctrl_sfr_cfg_msi_addr_31_0 sfr_cfg_msi_addr_31_0; /* offset : 0x216c */
	union pcie_subctrl_sfr_cfg_msi_addr_63_32 sfr_cfg_msi_addr_63_32; /* offset : 0x2170 */
	union pcie_subctrl_sfr_cfg_msi_data sfr_cfg_msi_data; /* offset : 0x2174 */
	union pcie_subctrl_sfr_cfg_msi_ext_data_en sfr_cfg_msi_ext_data_en; /* offset : 0x2178 */
	union pcie_subctrl_sfr_cfg_num_vf sfr_cfg_num_vf; /* offset : 0x217c */
	union pcie_subctrl_sfr_cfg_start_vfi sfr_cfg_start_vfi; /* offset : 0x2180 */
	union pcie_subctrl_sfr_cfg_vf_msix_en sfr_cfg_vf_msix_en; /* offset : 0x2184 */
	union pcie_subctrl_sfr_cfg_vf_msix_func_mask sfr_cfg_vf_msix_func_mask; /* offset : 0x2188 */
	union pcie_subctrl_sfr_cfg_vf_msix_pba_bir sfr_cfg_vf_msix_pba_bir; /* offset : 0x218c */
	union pcie_subctrl_sfr_cfg_vf_msix_pba_offset sfr_cfg_vf_msix_pba_offset; /* offset : 0x2190 */
	union pcie_subctrl_sfr_cfg_vf_msix_table_bir sfr_cfg_vf_msix_table_bir; /* offset : 0x2194 */
	union pcie_subctrl_sfr_cfg_vf_msix_table_offset sfr_cfg_vf_msix_table_offset; /* offset : 0x2198 */
	union pcie_subctrl_sfr_cfg_vf_msix_table_size sfr_cfg_vf_msix_table_size; /* offset : 0x219c */
	union pcie_subctrl_sfr_msix_pba_data_in_31_0 sfr_msix_pba_data_in_31_0; /* offset : 0x21a0 */
	union pcie_subctrl_sfr_msix_pba_data_in_63_32 sfr_msix_pba_data_in_63_32; /* offset : 0x21a4 */
	union pcie_subctrl_sfr_msix_table_data_in_31_0 sfr_msix_table_data_in_31_0; /* offset : 0x21a8 */
	union pcie_subctrl_sfr_msix_table_data_in_63_32 sfr_msix_table_data_in_63_32; /* offset : 0x21ac */
	union pcie_subctrl_sfr_msix_table_data_in_95_64 sfr_msix_table_data_in_95_64; /* offset : 0x21b0 */
	union pcie_subctrl_sfr_msix_table_data_in_127_96 sfr_msix_table_data_in_127_96; /* offset : 0x21b4 */
	union pcie_subctrl_sfr_msix_table_data_in_130_128 sfr_msix_table_data_in_130_128; /* offset : 0x21b8 */
	union pcie_subctrl_sfr_mstr_cactive sfr_mstr_cactive; /* offset : 0x21bc */
	union pcie_subctrl_sfr_mstr_csysack sfr_mstr_csysack; /* offset : 0x21c0 */
	union pcie_subctrl_sfr_pm_aspm_l1_enter_ready sfr_pm_aspm_l1_enter_ready; /* offset : 0x21c4 */
	union pcie_subctrl_sfr_radm_slot_pwr_limit sfr_radm_slot_pwr_limit; /* offset : 0x21c8 */
	union pcie_subctrl_sfr_radm_slot_pwr_payload sfr_radm_slot_pwr_payload; /* offset : 0x21cc */
	union pcie_subctrl_sfr_slv_cactive sfr_slv_cactive; /* offset : 0x21d0 */
	union pcie_subctrl_sfr_slv_csysack sfr_slv_csysack; /* offset : 0x21d4 */
	union pcie_subctrl_sfr_training_rst_n sfr_training_rst_n; /* offset : 0x21d8 */
	union pcie_subctrl_sfr_device_type_ovrd sfr_device_type_ovrd; /* offset : 0x21dc */
	union pcie_subctrl_sfr_device_type sfr_device_type; /* offset : 0x21e0 */
	union pcie_subctrl_sfr_dbg_sel_phy_lane sfr_dbg_sel_phy_lane; /* offset : 0x21e4 */
	uint32_t reserved_34;
	union pcie_subctrl_sfr_cfg_rbar_size_31_0 sfr_cfg_rbar_size_31_0; /* offset : 0x21ec */
	union pcie_subctrl_sfr_cfg_rbar_size_35_32 sfr_cfg_rbar_size_35_32; /* offset : 0x21f0 */
	union pcie_subctrl_sfr_msi_int sfr_msi_int; /* offset : 0x21f4 */
	union pcie_subctrl_sfr_vf_cfg_msi_64 sfr_vf_cfg_msi_64; /* offset : 0x21f8 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_31_0 sfr_cfg_vf_msi_addr_31_0; /* offset : 0x21fc */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_63_32 sfr_cfg_vf_msi_addr_63_32; /* offset : 0x2200 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_95_64 sfr_cfg_vf_msi_addr_95_64; /* offset : 0x2204 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_127_96 sfr_cfg_vf_msi_addr_127_96; /* offset : 0x2208 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_159_128 sfr_cfg_vf_msi_addr_159_128; /* offset : 0x220c */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_191_160 sfr_cfg_vf_msi_addr_191_160; /* offset : 0x2210 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_223_192 sfr_cfg_vf_msi_addr_223_192; /* offset : 0x2214 */
	union pcie_subctrl_sfr_cfg_vf_msi_addr_255_224 sfr_cfg_vf_msi_addr_255_224; /* offset : 0x2218 */
	union pcie_subctrl_sfr_cfg_vf_msi_data_31_0 sfr_cfg_vf_msi_data_31_0; /* offset : 0x221c */
	union pcie_subctrl_sfr_cfg_vf_msi_data_63_32 sfr_cfg_vf_msi_data_63_32; /* offset : 0x2220 */
	union pcie_subctrl_sfr_cfg_vf_msi_data_95_64 sfr_cfg_vf_msi_data_95_64; /* offset : 0x2224 */
	union pcie_subctrl_sfr_cfg_vf_msi_data_127_96 sfr_cfg_vf_msi_data_127_96; /* offset : 0x2228 */
	union pcie_subctrl_sfr_cfg_vf_msi_ext_data_en sfr_cfg_vf_msi_ext_data_en; /* offset : 0x222c */
	uint32_t reserved_35[884];
	union pcie_subctrl_sfr_phy_cfg_383_reg sfr_phy_cfg_383_reg; /* offset : 0x3000 */
	union pcie_subctrl_sfr_phy_cfg_384_reg sfr_phy_cfg_384_reg; /* offset : 0x3004 */
	union pcie_subctrl_sfr_phy_cfg_385_reg sfr_phy_cfg_385_reg; /* offset : 0x3008 */
	union pcie_subctrl_sfr_phy_cfg_386_reg sfr_phy_cfg_386_reg; /* offset : 0x300c */
	union pcie_subctrl_sfr_phy_cfg_387_reg sfr_phy_cfg_387_reg; /* offset : 0x3010 */
	union pcie_subctrl_sfr_phy_cfg_388_reg sfr_phy_cfg_388_reg; /* offset : 0x3014 */
	union pcie_subctrl_sfr_phy_cfg_389_reg sfr_phy_cfg_389_reg; /* offset : 0x3018 */
	union pcie_subctrl_sfr_phy_cfg_390_reg sfr_phy_cfg_390_reg; /* offset : 0x301c */
	union pcie_subctrl_sfr_phy_cfg_391_reg sfr_phy_cfg_391_reg; /* offset : 0x3020 */
	union pcie_subctrl_sfr_phy_cfg_392_reg sfr_phy_cfg_392_reg; /* offset : 0x3024 */
	union pcie_subctrl_sfr_phy_cfg_393_reg sfr_phy_cfg_393_reg; /* offset : 0x3028 */
	union pcie_subctrl_sfr_phy_cfg_394_reg sfr_phy_cfg_394_reg; /* offset : 0x302c */
	union pcie_subctrl_sfr_phy_cfg_395_reg sfr_phy_cfg_395_reg; /* offset : 0x3030 */
	union pcie_subctrl_sfr_phy_cfg_396_reg sfr_phy_cfg_396_reg; /* offset : 0x3034 */
	union pcie_subctrl_sfr_phy_cfg_397_reg sfr_phy_cfg_397_reg; /* offset : 0x3038 */
	union pcie_subctrl_sfr_phy_cfg_398_reg sfr_phy_cfg_398_reg; /* offset : 0x303c */
	union pcie_subctrl_sfr_phy_cfg_399_reg sfr_phy_cfg_399_reg; /* offset : 0x3040 */
	union pcie_subctrl_sfr_phy_cfg_400_reg sfr_phy_cfg_400_reg; /* offset : 0x3044 */
	union pcie_subctrl_sfr_phy_cfg_401_reg sfr_phy_cfg_401_reg; /* offset : 0x3048 */
	union pcie_subctrl_sfr_phy_cfg_402_reg sfr_phy_cfg_402_reg; /* offset : 0x304c */
	union pcie_subctrl_sfr_phy_cfg_403_reg sfr_phy_cfg_403_reg; /* offset : 0x3050 */
	union pcie_subctrl_sfr_phy_cfg_404_reg sfr_phy_cfg_404_reg; /* offset : 0x3054 */
	union pcie_subctrl_sfr_phy_cfg_405_reg sfr_phy_cfg_405_reg; /* offset : 0x3058 */
	union pcie_subctrl_sfr_phy_cfg_406_reg sfr_phy_cfg_406_reg; /* offset : 0x305c */
	union pcie_subctrl_sfr_phy_cfg_407_reg sfr_phy_cfg_407_reg; /* offset : 0x3060 */
	union pcie_subctrl_sfr_phy_cfg_408_reg sfr_phy_cfg_408_reg; /* offset : 0x3064 */
	union pcie_subctrl_sfr_phy_cfg_409_reg sfr_phy_cfg_409_reg; /* offset : 0x3068 */
	union pcie_subctrl_sfr_phy_cfg_410_reg sfr_phy_cfg_410_reg; /* offset : 0x306c */
	union pcie_subctrl_sfr_phy_cfg_411_reg sfr_phy_cfg_411_reg; /* offset : 0x3070 */
	union pcie_subctrl_sfr_phy_cfg_412_reg sfr_phy_cfg_412_reg; /* offset : 0x3074 */
	union pcie_subctrl_sfr_phy_cfg_413_reg sfr_phy_cfg_413_reg; /* offset : 0x3078 */
	union pcie_subctrl_sfr_phy_cfg_414_reg sfr_phy_cfg_414_reg; /* offset : 0x307c */
	union pcie_subctrl_sfr_phy_cfg_415_reg sfr_phy_cfg_415_reg; /* offset : 0x3080 */
	union pcie_subctrl_sfr_phy_cfg_416_reg sfr_phy_cfg_416_reg; /* offset : 0x3084 */
	union pcie_subctrl_sfr_phy_cfg_417_reg sfr_phy_cfg_417_reg; /* offset : 0x3088 */
	union pcie_subctrl_sfr_phy_cfg_418_reg sfr_phy_cfg_418_reg; /* offset : 0x308c */
	union pcie_subctrl_sfr_phy_cfg_419_reg sfr_phy_cfg_419_reg; /* offset : 0x3090 */
	union pcie_subctrl_sfr_phy_cfg_420_reg sfr_phy_cfg_420_reg; /* offset : 0x3094 */
	union pcie_subctrl_sfr_phy_cfg_421_reg sfr_phy_cfg_421_reg; /* offset : 0x3098 */
	union pcie_subctrl_sfr_phy_cfg_422_reg sfr_phy_cfg_422_reg; /* offset : 0x309c */
	union pcie_subctrl_sfr_phy_cfg_423_reg sfr_phy_cfg_423_reg; /* offset : 0x30a0 */
	union pcie_subctrl_sfr_phy_cfg_424_reg sfr_phy_cfg_424_reg; /* offset : 0x30a4 */
	union pcie_subctrl_sfr_phy_cfg_425_reg sfr_phy_cfg_425_reg; /* offset : 0x30a8 */
	union pcie_subctrl_sfr_phy_cfg_426_reg sfr_phy_cfg_426_reg; /* offset : 0x30ac */
	union pcie_subctrl_sfr_phy_cfg_427_reg sfr_phy_cfg_427_reg; /* offset : 0x30b0 */
	union pcie_subctrl_sfr_phy_cfg_428_reg sfr_phy_cfg_428_reg; /* offset : 0x30b4 */
	union pcie_subctrl_sfr_phy_cfg_429_reg sfr_phy_cfg_429_reg; /* offset : 0x30b8 */
	union pcie_subctrl_sfr_phy_cfg_430_reg sfr_phy_cfg_430_reg; /* offset : 0x30bc */
	union pcie_subctrl_sfr_phy_cfg_431_reg sfr_phy_cfg_431_reg; /* offset : 0x30c0 */
	union pcie_subctrl_sfr_phy_cfg_432_reg sfr_phy_cfg_432_reg; /* offset : 0x30c4 */
	union pcie_subctrl_sfr_phy_cfg_433_reg sfr_phy_cfg_433_reg; /* offset : 0x30c8 */
	union pcie_subctrl_sfr_phy_cfg_434_reg sfr_phy_cfg_434_reg; /* offset : 0x30cc */
	union pcie_subctrl_sfr_phy_cfg_435_reg sfr_phy_cfg_435_reg; /* offset : 0x30d0 */
	union pcie_subctrl_sfr_phy_cfg_436_reg sfr_phy_cfg_436_reg; /* offset : 0x30d4 */
	union pcie_subctrl_sfr_phy_cfg_437_reg sfr_phy_cfg_437_reg; /* offset : 0x30d8 */
	union pcie_subctrl_sfr_phy_cfg_438_reg sfr_phy_cfg_438_reg; /* offset : 0x30dc */
	union pcie_subctrl_sfr_phy_cfg_439_reg sfr_phy_cfg_439_reg; /* offset : 0x30e0 */
	union pcie_subctrl_sfr_phy_cfg_440_reg sfr_phy_cfg_440_reg; /* offset : 0x30e4 */
	union pcie_subctrl_sfr_phy_cfg_441_reg sfr_phy_cfg_441_reg; /* offset : 0x30e8 */
	union pcie_subctrl_sfr_phy_cfg_442_reg sfr_phy_cfg_442_reg; /* offset : 0x30ec */
	union pcie_subctrl_sfr_phy_cfg_443_reg sfr_phy_cfg_443_reg; /* offset : 0x30f0 */
	union pcie_subctrl_sfr_phy_cfg_444_reg sfr_phy_cfg_444_reg; /* offset : 0x30f4 */
	union pcie_subctrl_sfr_phy_cfg_445_reg sfr_phy_cfg_445_reg; /* offset : 0x30f8 */
	union pcie_subctrl_sfr_phy_cfg_446_reg sfr_phy_cfg_446_reg; /* offset : 0x30fc */
	union pcie_subctrl_sfr_phy_cfg_447_reg sfr_phy_cfg_447_reg; /* offset : 0x3100 */
	union pcie_subctrl_sfr_phy_cfg_448_reg sfr_phy_cfg_448_reg; /* offset : 0x3104 */
	union pcie_subctrl_sfr_phy_cfg_449_reg sfr_phy_cfg_449_reg; /* offset : 0x3108 */
	union pcie_subctrl_sfr_phy_cfg_450_reg sfr_phy_cfg_450_reg; /* offset : 0x310c */
	union pcie_subctrl_sfr_phy_cfg_451_reg sfr_phy_cfg_451_reg; /* offset : 0x3110 */
	union pcie_subctrl_sfr_phy_cfg_452_reg sfr_phy_cfg_452_reg; /* offset : 0x3114 */
	union pcie_subctrl_sfr_phy_cfg_453_reg sfr_phy_cfg_453_reg; /* offset : 0x3118 */
	union pcie_subctrl_sfr_phy_cfg_454_reg sfr_phy_cfg_454_reg; /* offset : 0x311c */
	union pcie_subctrl_sfr_phy_cfg_455_reg sfr_phy_cfg_455_reg; /* offset : 0x3120 */
	union pcie_subctrl_sfr_phy_cfg_456_reg sfr_phy_cfg_456_reg; /* offset : 0x3124 */
	union pcie_subctrl_sfr_phy_cfg_457_reg sfr_phy_cfg_457_reg; /* offset : 0x3128 */
	union pcie_subctrl_sfr_phy_cfg_458_reg sfr_phy_cfg_458_reg; /* offset : 0x312c */
	union pcie_subctrl_sfr_phy_cfg_459_reg sfr_phy_cfg_459_reg; /* offset : 0x3130 */
	union pcie_subctrl_sfr_phy_cfg_460_reg sfr_phy_cfg_460_reg; /* offset : 0x3134 */
	union pcie_subctrl_sfr_phy_cfg_461_reg sfr_phy_cfg_461_reg; /* offset : 0x3138 */
	union pcie_subctrl_sfr_phy_cfg_462_reg sfr_phy_cfg_462_reg; /* offset : 0x313c */
	union pcie_subctrl_sfr_phy_cfg_463_reg sfr_phy_cfg_463_reg; /* offset : 0x3140 */
	union pcie_subctrl_sfr_phy_cfg_464_reg sfr_phy_cfg_464_reg; /* offset : 0x3144 */
	union pcie_subctrl_sfr_phy_cfg_465_reg sfr_phy_cfg_465_reg; /* offset : 0x3148 */
	union pcie_subctrl_sfr_phy_cfg_466_reg sfr_phy_cfg_466_reg; /* offset : 0x314c */
	union pcie_subctrl_sfr_phy_cfg_467_reg sfr_phy_cfg_467_reg; /* offset : 0x3150 */
	union pcie_subctrl_sfr_phy_cfg_468_reg sfr_phy_cfg_468_reg; /* offset : 0x3154 */
	union pcie_subctrl_sfr_phy_cfg_469_reg sfr_phy_cfg_469_reg; /* offset : 0x3158 */
	union pcie_subctrl_sfr_phy_cfg_470_reg sfr_phy_cfg_470_reg; /* offset : 0x315c */
	union pcie_subctrl_sfr_phy_cfg_471_reg sfr_phy_cfg_471_reg; /* offset : 0x3160 */
	union pcie_subctrl_sfr_phy_cfg_472_reg sfr_phy_cfg_472_reg; /* offset : 0x3164 */
	union pcie_subctrl_sfr_phy_cfg_473_reg sfr_phy_cfg_473_reg; /* offset : 0x3168 */
	union pcie_subctrl_sfr_phy_cfg_474_reg sfr_phy_cfg_474_reg; /* offset : 0x316c */
	union pcie_subctrl_sfr_phy_cfg_475_reg sfr_phy_cfg_475_reg; /* offset : 0x3170 */
	union pcie_subctrl_sfr_phy_cfg_476_reg sfr_phy_cfg_476_reg; /* offset : 0x3174 */
	union pcie_subctrl_sfr_phy_cfg_477_reg sfr_phy_cfg_477_reg; /* offset : 0x3178 */
	union pcie_subctrl_sfr_phy_cfg_478_reg sfr_phy_cfg_478_reg; /* offset : 0x317c */
	union pcie_subctrl_sfr_phy_cfg_479_reg sfr_phy_cfg_479_reg; /* offset : 0x3180 */
	union pcie_subctrl_sfr_phy_cfg_480_reg sfr_phy_cfg_480_reg; /* offset : 0x3184 */
	union pcie_subctrl_sfr_phy_cfg_481_reg sfr_phy_cfg_481_reg; /* offset : 0x3188 */
	union pcie_subctrl_sfr_phy_cfg_482_reg sfr_phy_cfg_482_reg; /* offset : 0x318c */
	union pcie_subctrl_sfr_phy_cfg_483_reg sfr_phy_cfg_483_reg; /* offset : 0x3190 */
	union pcie_subctrl_sfr_phy_cfg_484_reg sfr_phy_cfg_484_reg; /* offset : 0x3194 */
	union pcie_subctrl_sfr_phy_cfg_485_reg sfr_phy_cfg_485_reg; /* offset : 0x3198 */
	union pcie_subctrl_sfr_phy_cfg_486_reg sfr_phy_cfg_486_reg; /* offset : 0x319c */
	union pcie_subctrl_sfr_phy_cfg_487_reg sfr_phy_cfg_487_reg; /* offset : 0x31a0 */
	union pcie_subctrl_sfr_phy_cfg_488_reg sfr_phy_cfg_488_reg; /* offset : 0x31a4 */
	union pcie_subctrl_sfr_phy_cfg_489_reg sfr_phy_cfg_489_reg; /* offset : 0x31a8 */
	union pcie_subctrl_sfr_phy_cfg_490_reg sfr_phy_cfg_490_reg; /* offset : 0x31ac */
	union pcie_subctrl_sfr_phy_cfg_491_reg sfr_phy_cfg_491_reg; /* offset : 0x31b0 */
	union pcie_subctrl_sfr_phy_cfg_492_reg sfr_phy_cfg_492_reg; /* offset : 0x31b4 */
	union pcie_subctrl_sfr_phy_cfg_493_reg sfr_phy_cfg_493_reg; /* offset : 0x31b8 */
	union pcie_subctrl_sfr_phy_cfg_494_reg sfr_phy_cfg_494_reg; /* offset : 0x31bc */
	union pcie_subctrl_sfr_phy_cfg_495_reg sfr_phy_cfg_495_reg; /* offset : 0x31c0 */
	union pcie_subctrl_sfr_phy_cfg_496_reg sfr_phy_cfg_496_reg; /* offset : 0x31c4 */
	union pcie_subctrl_sfr_phy_cfg_497_reg sfr_phy_cfg_497_reg; /* offset : 0x31c8 */
	union pcie_subctrl_sfr_phy_cfg_498_reg sfr_phy_cfg_498_reg; /* offset : 0x31cc */
	union pcie_subctrl_sfr_phy_cfg_499_reg sfr_phy_cfg_499_reg; /* offset : 0x31d0 */
	union pcie_subctrl_sfr_phy_cfg_500_reg sfr_phy_cfg_500_reg; /* offset : 0x31d4 */
	union pcie_subctrl_sfr_phy_cfg_501_reg sfr_phy_cfg_501_reg; /* offset : 0x31d8 */
	union pcie_subctrl_sfr_phy_cfg_502_reg sfr_phy_cfg_502_reg; /* offset : 0x31dc */
	union pcie_subctrl_sfr_phy_cfg_503_reg sfr_phy_cfg_503_reg; /* offset : 0x31e0 */
	union pcie_subctrl_sfr_phy_cfg_504_reg sfr_phy_cfg_504_reg; /* offset : 0x31e4 */
	union pcie_subctrl_sfr_phy_cfg_505_reg sfr_phy_cfg_505_reg; /* offset : 0x31e8 */
	union pcie_subctrl_sfr_phy_cfg_506_reg sfr_phy_cfg_506_reg; /* offset : 0x31ec */
	union pcie_subctrl_sfr_phy_cfg_507_reg sfr_phy_cfg_507_reg; /* offset : 0x31f0 */
	union pcie_subctrl_sfr_phy_cfg_508_reg sfr_phy_cfg_508_reg; /* offset : 0x31f4 */
	union pcie_subctrl_sfr_phy_cfg_509_reg sfr_phy_cfg_509_reg; /* offset : 0x31f8 */
	union pcie_subctrl_sfr_phy_cfg_510_reg sfr_phy_cfg_510_reg; /* offset : 0x31fc */
	union pcie_subctrl_sfr_phy_cfg_511_reg sfr_phy_cfg_511_reg; /* offset : 0x3200 */
	union pcie_subctrl_sfr_phy_cfg_512_reg sfr_phy_cfg_512_reg; /* offset : 0x3204 */
	union pcie_subctrl_sfr_phy_cfg_513_reg sfr_phy_cfg_513_reg; /* offset : 0x3208 */
	union pcie_subctrl_sfr_phy_cfg_514_reg sfr_phy_cfg_514_reg; /* offset : 0x320c */
	union pcie_subctrl_sfr_phy_cfg_515_reg sfr_phy_cfg_515_reg; /* offset : 0x3210 */
	union pcie_subctrl_sfr_phy_cfg_516_reg sfr_phy_cfg_516_reg; /* offset : 0x3214 */
	union pcie_subctrl_sfr_phy_cfg_517_reg sfr_phy_cfg_517_reg; /* offset : 0x3218 */
	union pcie_subctrl_sfr_phy_cfg_518_reg sfr_phy_cfg_518_reg; /* offset : 0x321c */
	union pcie_subctrl_sfr_phy_cfg_519_reg sfr_phy_cfg_519_reg; /* offset : 0x3220 */
	union pcie_subctrl_sfr_phy_cfg_520_reg sfr_phy_cfg_520_reg; /* offset : 0x3224 */
	union pcie_subctrl_sfr_phy_cfg_521_reg sfr_phy_cfg_521_reg; /* offset : 0x3228 */
	union pcie_subctrl_sfr_phy_cfg_522_reg sfr_phy_cfg_522_reg; /* offset : 0x322c */
	union pcie_subctrl_sfr_phy_cfg_523_reg sfr_phy_cfg_523_reg; /* offset : 0x3230 */
	union pcie_subctrl_sfr_phy_cfg_524_reg sfr_phy_cfg_524_reg; /* offset : 0x3234 */
	union pcie_subctrl_sfr_phy_cfg_525_reg sfr_phy_cfg_525_reg; /* offset : 0x3238 */
	union pcie_subctrl_sfr_phy_cfg_526_reg sfr_phy_cfg_526_reg; /* offset : 0x323c */
	union pcie_subctrl_sfr_phy_cfg_527_reg sfr_phy_cfg_527_reg; /* offset : 0x3240 */
	union pcie_subctrl_sfr_phy_cfg_528_reg sfr_phy_cfg_528_reg; /* offset : 0x3244 */
	union pcie_subctrl_sfr_phy_cfg_529_reg sfr_phy_cfg_529_reg; /* offset : 0x3248 */
	union pcie_subctrl_sfr_phy_cfg_530_reg sfr_phy_cfg_530_reg; /* offset : 0x324c */
	union pcie_subctrl_sfr_phy_cfg_531_reg sfr_phy_cfg_531_reg; /* offset : 0x3250 */
	union pcie_subctrl_sfr_phy_cfg_532_reg sfr_phy_cfg_532_reg; /* offset : 0x3254 */
	union pcie_subctrl_sfr_phy_cfg_533_reg sfr_phy_cfg_533_reg; /* offset : 0x3258 */
	union pcie_subctrl_sfr_phy_cfg_534_reg sfr_phy_cfg_534_reg; /* offset : 0x325c */
	union pcie_subctrl_sfr_phy_cfg_535_reg sfr_phy_cfg_535_reg; /* offset : 0x3260 */
	union pcie_subctrl_sfr_phy_cfg_536_reg sfr_phy_cfg_536_reg; /* offset : 0x3264 */
	union pcie_subctrl_sfr_phy_cfg_537_reg sfr_phy_cfg_537_reg; /* offset : 0x3268 */
	union pcie_subctrl_sfr_phy_cfg_538_reg sfr_phy_cfg_538_reg; /* offset : 0x326c */
	union pcie_subctrl_sfr_phy_cfg_539_reg sfr_phy_cfg_539_reg; /* offset : 0x3270 */
	union pcie_subctrl_sfr_phy_cfg_540_reg sfr_phy_cfg_540_reg; /* offset : 0x3274 */
	union pcie_subctrl_sfr_phy_cfg_541_reg sfr_phy_cfg_541_reg; /* offset : 0x3278 */
	union pcie_subctrl_sfr_phy_cfg_542_reg sfr_phy_cfg_542_reg; /* offset : 0x327c */
	union pcie_subctrl_sfr_phy_cfg_543_reg sfr_phy_cfg_543_reg; /* offset : 0x3280 */
	union pcie_subctrl_sfr_phy_cfg_544_reg sfr_phy_cfg_544_reg; /* offset : 0x3284 */
	union pcie_subctrl_sfr_phy_cfg_545_reg sfr_phy_cfg_545_reg; /* offset : 0x3288 */
	union pcie_subctrl_sfr_phy_cfg_546_reg sfr_phy_cfg_546_reg; /* offset : 0x328c */
	union pcie_subctrl_sfr_phy_cfg_547_reg sfr_phy_cfg_547_reg; /* offset : 0x3290 */
	union pcie_subctrl_sfr_phy_cfg_548_reg sfr_phy_cfg_548_reg; /* offset : 0x3294 */
	union pcie_subctrl_sfr_phy_cfg_549_reg sfr_phy_cfg_549_reg; /* offset : 0x3298 */
	union pcie_subctrl_sfr_phy_cfg_550_reg sfr_phy_cfg_550_reg; /* offset : 0x329c */
	union pcie_subctrl_sfr_phy_cfg_551_reg sfr_phy_cfg_551_reg; /* offset : 0x32a0 */
	union pcie_subctrl_sfr_phy_cfg_552_reg sfr_phy_cfg_552_reg; /* offset : 0x32a4 */
	union pcie_subctrl_sfr_phy_cfg_553_reg sfr_phy_cfg_553_reg; /* offset : 0x32a8 */
	union pcie_subctrl_sfr_phy_cfg_554_reg sfr_phy_cfg_554_reg; /* offset : 0x32ac */
	union pcie_subctrl_sfr_phy_cfg_555_reg sfr_phy_cfg_555_reg; /* offset : 0x32b0 */
	union pcie_subctrl_sfr_phy_cfg_556_reg sfr_phy_cfg_556_reg; /* offset : 0x32b4 */
	union pcie_subctrl_sfr_phy_cfg_557_reg sfr_phy_cfg_557_reg; /* offset : 0x32b8 */
	union pcie_subctrl_sfr_phy_cfg_558_reg sfr_phy_cfg_558_reg; /* offset : 0x32bc */
	union pcie_subctrl_sfr_phy_cfg_559_reg sfr_phy_cfg_559_reg; /* offset : 0x32c0 */
	union pcie_subctrl_sfr_phy_cfg_560_reg sfr_phy_cfg_560_reg; /* offset : 0x32c4 */
	union pcie_subctrl_sfr_phy_cfg_561_reg sfr_phy_cfg_561_reg; /* offset : 0x32c8 */
	union pcie_subctrl_sfr_phy_cfg_562_reg sfr_phy_cfg_562_reg; /* offset : 0x32cc */
	union pcie_subctrl_sfr_phy_cfg_563_reg sfr_phy_cfg_563_reg; /* offset : 0x32d0 */
	union pcie_subctrl_sfr_phy_cfg_564_reg sfr_phy_cfg_564_reg; /* offset : 0x32d4 */
	union pcie_subctrl_sfr_phy_cfg_565_reg sfr_phy_cfg_565_reg; /* offset : 0x32d8 */
	union pcie_subctrl_sfr_phy_cfg_566_reg sfr_phy_cfg_566_reg; /* offset : 0x32dc */
	union pcie_subctrl_sfr_phy_cfg_567_reg sfr_phy_cfg_567_reg; /* offset : 0x32e0 */
	union pcie_subctrl_sfr_phy_cfg_568_reg sfr_phy_cfg_568_reg; /* offset : 0x32e4 */
	union pcie_subctrl_sfr_phy_cfg_569_reg sfr_phy_cfg_569_reg; /* offset : 0x32e8 */
	union pcie_subctrl_sfr_phy_cfg_570_reg sfr_phy_cfg_570_reg; /* offset : 0x32ec */
	union pcie_subctrl_sfr_phy_cfg_571_reg sfr_phy_cfg_571_reg; /* offset : 0x32f0 */
	union pcie_subctrl_sfr_phy_cfg_572_reg sfr_phy_cfg_572_reg; /* offset : 0x32f4 */
	union pcie_subctrl_sfr_phy_cfg_573_reg sfr_phy_cfg_573_reg; /* offset : 0x32f8 */
	union pcie_subctrl_sfr_phy_cfg_574_reg sfr_phy_cfg_574_reg; /* offset : 0x32fc */
	union pcie_subctrl_sfr_phy_cfg_575_reg sfr_phy_cfg_575_reg; /* offset : 0x3300 */
	union pcie_subctrl_sfr_phy_cfg_576_reg sfr_phy_cfg_576_reg; /* offset : 0x3304 */
	union pcie_subctrl_sfr_phy_cfg_577_reg sfr_phy_cfg_577_reg; /* offset : 0x3308 */
	union pcie_subctrl_sfr_phy_cfg_578_reg sfr_phy_cfg_578_reg; /* offset : 0x330c */
	union pcie_subctrl_sfr_phy_cfg_579_reg sfr_phy_cfg_579_reg; /* offset : 0x3310 */
	union pcie_subctrl_sfr_phy_cfg_580_reg sfr_phy_cfg_580_reg; /* offset : 0x3314 */
	union pcie_subctrl_sfr_phy_cfg_581_reg sfr_phy_cfg_581_reg; /* offset : 0x3318 */
	union pcie_subctrl_sfr_phy_cfg_582_reg sfr_phy_cfg_582_reg; /* offset : 0x331c */
	union pcie_subctrl_sfr_phy_cfg_583_reg sfr_phy_cfg_583_reg; /* offset : 0x3320 */
	union pcie_subctrl_sfr_phy_cfg_584_reg sfr_phy_cfg_584_reg; /* offset : 0x3324 */
	union pcie_subctrl_sfr_phy_cfg_585_reg sfr_phy_cfg_585_reg; /* offset : 0x3328 */
	union pcie_subctrl_sfr_phy_cfg_586_reg sfr_phy_cfg_586_reg; /* offset : 0x332c */
	union pcie_subctrl_sfr_phy_cfg_587_reg sfr_phy_cfg_587_reg; /* offset : 0x3330 */
	union pcie_subctrl_sfr_phy_cfg_588_reg sfr_phy_cfg_588_reg; /* offset : 0x3334 */
	union pcie_subctrl_sfr_phy_cfg_589_reg sfr_phy_cfg_589_reg; /* offset : 0x3338 */
	union pcie_subctrl_sfr_phy_cfg_590_reg sfr_phy_cfg_590_reg; /* offset : 0x333c */
	union pcie_subctrl_sfr_phy_cfg_591_reg sfr_phy_cfg_591_reg; /* offset : 0x3340 */
	union pcie_subctrl_sfr_phy_cfg_592_reg sfr_phy_cfg_592_reg; /* offset : 0x3344 */
	union pcie_subctrl_sfr_phy_cfg_593_reg sfr_phy_cfg_593_reg; /* offset : 0x3348 */
	union pcie_subctrl_sfr_phy_cfg_594_reg sfr_phy_cfg_594_reg; /* offset : 0x334c */
	union pcie_subctrl_sfr_phy_cfg_595_reg sfr_phy_cfg_595_reg; /* offset : 0x3350 */
	union pcie_subctrl_sfr_phy_cfg_596_reg sfr_phy_cfg_596_reg; /* offset : 0x3354 */
	union pcie_subctrl_sfr_phy_cfg_597_reg sfr_phy_cfg_597_reg; /* offset : 0x3358 */
	union pcie_subctrl_sfr_phy_cfg_598_reg sfr_phy_cfg_598_reg; /* offset : 0x335c */
	union pcie_subctrl_sfr_phy_cfg_599_reg sfr_phy_cfg_599_reg; /* offset : 0x3360 */
	union pcie_subctrl_sfr_phy_cfg_600_reg sfr_phy_cfg_600_reg; /* offset : 0x3364 */
	union pcie_subctrl_sfr_phy_cfg_601_reg sfr_phy_cfg_601_reg; /* offset : 0x3368 */
	union pcie_subctrl_sfr_phy_cfg_602_reg sfr_phy_cfg_602_reg; /* offset : 0x336c */
	union pcie_subctrl_sfr_phy_cfg_603_reg sfr_phy_cfg_603_reg; /* offset : 0x3370 */
	union pcie_subctrl_sfr_phy_cfg_604_reg sfr_phy_cfg_604_reg; /* offset : 0x3374 */
	union pcie_subctrl_sfr_phy_cfg_605_reg sfr_phy_cfg_605_reg; /* offset : 0x3378 */
	union pcie_subctrl_sfr_phy_cfg_606_reg sfr_phy_cfg_606_reg; /* offset : 0x337c */
	union pcie_subctrl_sfr_phy_cfg_607_reg sfr_phy_cfg_607_reg; /* offset : 0x3380 */
	union pcie_subctrl_sfr_phy_cfg_608_reg sfr_phy_cfg_608_reg; /* offset : 0x3384 */
	union pcie_subctrl_sfr_phy_cfg_609_reg sfr_phy_cfg_609_reg; /* offset : 0x3388 */
	union pcie_subctrl_sfr_phy_cfg_610_reg sfr_phy_cfg_610_reg; /* offset : 0x338c */
	union pcie_subctrl_sfr_phy_cfg_611_reg sfr_phy_cfg_611_reg; /* offset : 0x3390 */
	union pcie_subctrl_sfr_phy_cfg_612_reg sfr_phy_cfg_612_reg; /* offset : 0x3394 */
	union pcie_subctrl_sfr_phy_cfg_613_reg sfr_phy_cfg_613_reg; /* offset : 0x3398 */
	union pcie_subctrl_sfr_phy_cfg_614_reg sfr_phy_cfg_614_reg; /* offset : 0x339c */
	union pcie_subctrl_sfr_phy_cfg_615_reg sfr_phy_cfg_615_reg; /* offset : 0x33a0 */
	union pcie_subctrl_sfr_phy_cfg_616_reg sfr_phy_cfg_616_reg; /* offset : 0x33a4 */
	union pcie_subctrl_sfr_phy_cfg_617_reg sfr_phy_cfg_617_reg; /* offset : 0x33a8 */
	union pcie_subctrl_sfr_phy_cfg_618_reg sfr_phy_cfg_618_reg; /* offset : 0x33ac */
	union pcie_subctrl_sfr_phy_cfg_619_reg sfr_phy_cfg_619_reg; /* offset : 0x33b0 */
	union pcie_subctrl_sfr_phy_cfg_620_reg sfr_phy_cfg_620_reg; /* offset : 0x33b4 */
	union pcie_subctrl_sfr_phy_cfg_621_reg sfr_phy_cfg_621_reg; /* offset : 0x33b8 */
	union pcie_subctrl_sfr_phy_cfg_622_reg sfr_phy_cfg_622_reg; /* offset : 0x33bc */
	union pcie_subctrl_sfr_phy_cfg_623_reg sfr_phy_cfg_623_reg; /* offset : 0x33c0 */
	union pcie_subctrl_sfr_phy_cfg_624_reg sfr_phy_cfg_624_reg; /* offset : 0x33c4 */
	union pcie_subctrl_sfr_phy_cfg_625_reg sfr_phy_cfg_625_reg; /* offset : 0x33c8 */
	union pcie_subctrl_sfr_phy_cfg_626_reg sfr_phy_cfg_626_reg; /* offset : 0x33cc */
	union pcie_subctrl_sfr_phy_cfg_627_reg sfr_phy_cfg_627_reg; /* offset : 0x33d0 */
	union pcie_subctrl_sfr_phy_cfg_628_reg sfr_phy_cfg_628_reg; /* offset : 0x33d4 */
	union pcie_subctrl_sfr_phy_cfg_629_reg sfr_phy_cfg_629_reg; /* offset : 0x33d8 */
	union pcie_subctrl_sfr_phy_cfg_630_reg sfr_phy_cfg_630_reg; /* offset : 0x33dc */
	union pcie_subctrl_sfr_phy_cfg_631_reg sfr_phy_cfg_631_reg; /* offset : 0x33e0 */
	union pcie_subctrl_sfr_phy_cfg_632_reg sfr_phy_cfg_632_reg; /* offset : 0x33e4 */
	union pcie_subctrl_sfr_phy_cfg_633_reg sfr_phy_cfg_633_reg; /* offset : 0x33e8 */
	union pcie_subctrl_sfr_phy_cfg_634_reg sfr_phy_cfg_634_reg; /* offset : 0x33ec */
	union pcie_subctrl_sfr_phy_cfg_635_reg sfr_phy_cfg_635_reg; /* offset : 0x33f0 */
	union pcie_subctrl_sfr_phy_cfg_636_reg sfr_phy_cfg_636_reg; /* offset : 0x33f4 */
	union pcie_subctrl_sfr_phy_cfg_637_reg sfr_phy_cfg_637_reg; /* offset : 0x33f8 */
	union pcie_subctrl_sfr_phy_cfg_638_reg sfr_phy_cfg_638_reg; /* offset : 0x33fc */
	uint32_t reserved_36[768];
	union pcie_subctrl_sfr_phy_cfg_639_reg sfr_phy_cfg_639_reg; /* offset : 0x4000 */
	union pcie_subctrl_sfr_phy_cfg_640_reg sfr_phy_cfg_640_reg; /* offset : 0x4004 */
	union pcie_subctrl_sfr_phy_cfg_641_reg sfr_phy_cfg_641_reg; /* offset : 0x4008 */
	union pcie_subctrl_sfr_phy_cfg_642_reg sfr_phy_cfg_642_reg; /* offset : 0x400c */
	union pcie_subctrl_sfr_phy_cfg_643_reg sfr_phy_cfg_643_reg; /* offset : 0x4010 */
	union pcie_subctrl_sfr_phy_cfg_644_reg sfr_phy_cfg_644_reg; /* offset : 0x4014 */
	union pcie_subctrl_sfr_phy_cfg_645_reg sfr_phy_cfg_645_reg; /* offset : 0x4018 */
	union pcie_subctrl_sfr_phy_cfg_646_reg sfr_phy_cfg_646_reg; /* offset : 0x401c */
	union pcie_subctrl_sfr_phy_cfg_647_reg sfr_phy_cfg_647_reg; /* offset : 0x4020 */
	union pcie_subctrl_sfr_phy_cfg_648_reg sfr_phy_cfg_648_reg; /* offset : 0x4024 */
	union pcie_subctrl_sfr_phy_cfg_649_reg sfr_phy_cfg_649_reg; /* offset : 0x4028 */
	union pcie_subctrl_sfr_phy_cfg_650_reg sfr_phy_cfg_650_reg; /* offset : 0x402c */
	union pcie_subctrl_sfr_phy_cfg_651_reg sfr_phy_cfg_651_reg; /* offset : 0x4030 */
	union pcie_subctrl_sfr_phy_cfg_652_reg sfr_phy_cfg_652_reg; /* offset : 0x4034 */
	union pcie_subctrl_sfr_phy_cfg_653_reg sfr_phy_cfg_653_reg; /* offset : 0x4038 */
	union pcie_subctrl_sfr_phy_cfg_654_reg sfr_phy_cfg_654_reg; /* offset : 0x403c */
	union pcie_subctrl_sfr_phy_cfg_655_reg sfr_phy_cfg_655_reg; /* offset : 0x4040 */
	union pcie_subctrl_sfr_phy_cfg_656_reg sfr_phy_cfg_656_reg; /* offset : 0x4044 */
	union pcie_subctrl_sfr_phy_cfg_657_reg sfr_phy_cfg_657_reg; /* offset : 0x4048 */
	union pcie_subctrl_sfr_phy_cfg_658_reg sfr_phy_cfg_658_reg; /* offset : 0x404c */
	union pcie_subctrl_sfr_phy_cfg_659_reg sfr_phy_cfg_659_reg; /* offset : 0x4050 */
	union pcie_subctrl_sfr_phy_cfg_660_reg sfr_phy_cfg_660_reg; /* offset : 0x4054 */
	union pcie_subctrl_sfr_phy_cfg_661_reg sfr_phy_cfg_661_reg; /* offset : 0x4058 */
	union pcie_subctrl_sfr_phy_cfg_662_reg sfr_phy_cfg_662_reg; /* offset : 0x405c */
	union pcie_subctrl_sfr_phy_cfg_663_reg sfr_phy_cfg_663_reg; /* offset : 0x4060 */
	union pcie_subctrl_sfr_phy_cfg_664_reg sfr_phy_cfg_664_reg; /* offset : 0x4064 */
	union pcie_subctrl_sfr_phy_cfg_665_reg sfr_phy_cfg_665_reg; /* offset : 0x4068 */
	union pcie_subctrl_sfr_phy_cfg_666_reg sfr_phy_cfg_666_reg; /* offset : 0x406c */
	union pcie_subctrl_sfr_phy_cfg_667_reg sfr_phy_cfg_667_reg; /* offset : 0x4070 */
	union pcie_subctrl_sfr_phy_cfg_668_reg sfr_phy_cfg_668_reg; /* offset : 0x4074 */
	union pcie_subctrl_sfr_phy_cfg_669_reg sfr_phy_cfg_669_reg; /* offset : 0x4078 */
	union pcie_subctrl_sfr_phy_cfg_670_reg sfr_phy_cfg_670_reg; /* offset : 0x407c */
	union pcie_subctrl_sfr_phy_cfg_671_reg sfr_phy_cfg_671_reg; /* offset : 0x4080 */
	union pcie_subctrl_sfr_phy_cfg_672_reg sfr_phy_cfg_672_reg; /* offset : 0x4084 */
	union pcie_subctrl_sfr_phy_cfg_673_reg sfr_phy_cfg_673_reg; /* offset : 0x4088 */
	union pcie_subctrl_sfr_phy_cfg_674_reg sfr_phy_cfg_674_reg; /* offset : 0x408c */
	union pcie_subctrl_sfr_phy_cfg_675_reg sfr_phy_cfg_675_reg; /* offset : 0x4090 */
	union pcie_subctrl_sfr_phy_cfg_676_reg sfr_phy_cfg_676_reg; /* offset : 0x4094 */
	union pcie_subctrl_sfr_phy_cfg_677_reg sfr_phy_cfg_677_reg; /* offset : 0x4098 */
	union pcie_subctrl_sfr_phy_cfg_678_reg sfr_phy_cfg_678_reg; /* offset : 0x409c */
	union pcie_subctrl_sfr_phy_cfg_679_reg sfr_phy_cfg_679_reg; /* offset : 0x40a0 */
	union pcie_subctrl_sfr_phy_cfg_680_reg sfr_phy_cfg_680_reg; /* offset : 0x40a4 */
	union pcie_subctrl_sfr_phy_cfg_681_reg sfr_phy_cfg_681_reg; /* offset : 0x40a8 */
	union pcie_subctrl_sfr_phy_cfg_682_reg sfr_phy_cfg_682_reg; /* offset : 0x40ac */
	union pcie_subctrl_sfr_phy_cfg_683_reg sfr_phy_cfg_683_reg; /* offset : 0x40b0 */
	union pcie_subctrl_sfr_phy_cfg_684_reg sfr_phy_cfg_684_reg; /* offset : 0x40b4 */
	union pcie_subctrl_sfr_rtlh_rfc_data_31_0 sfr_rtlh_rfc_data_31_0; /* offset : 0x40b8 */
	union pcie_subctrl_sfr_rtlh_rfc_data_63_32 sfr_rtlh_rfc_data_63_32; /* offset : 0x40bc */
	union pcie_subctrl_sfr_rtlh_rfc_data_95_64 sfr_rtlh_rfc_data_95_64; /* offset : 0x40c0 */
	union pcie_subctrl_sfr_rtlh_rfc_data_127_96 sfr_rtlh_rfc_data_127_96; /* offset : 0x40c4 */
	union pcie_subctrl_sfr_rtlh_rfc_data_159_128 sfr_rtlh_rfc_data_159_128; /* offset : 0x40c8 */
	union pcie_subctrl_sfr_rtlh_rfc_data_191_160 sfr_rtlh_rfc_data_191_160; /* offset : 0x40cc */
	union pcie_subctrl_sfr_rtlh_rfc_data_223_192 sfr_rtlh_rfc_data_223_192; /* offset : 0x40d0 */
	union pcie_subctrl_sfr_rtlh_rfc_data_255_224 sfr_rtlh_rfc_data_255_224; /* offset : 0x40d4 */
	union pcie_subctrl_sfr_phy_cfg_685_reg sfr_phy_cfg_685_reg; /* offset : 0x40d8 */
	union pcie_subctrl_sfr_phy_cfg_686_reg sfr_phy_cfg_686_reg; /* offset : 0x40dc */
	union pcie_subctrl_sfr_phy_cfg_687_reg sfr_phy_cfg_687_reg; /* offset : 0x40e0 */
	union pcie_subctrl_sfr_phy_cfg_688_reg sfr_phy_cfg_688_reg; /* offset : 0x40e4 */
	union pcie_subctrl_sfr_phy_cfg_689_reg sfr_phy_cfg_689_reg; /* offset : 0x40e8 */
	union pcie_subctrl_sfr_phy_cfg_690_reg sfr_phy_cfg_690_reg; /* offset : 0x40ec */
	union pcie_subctrl_sfr_phy_cfg_691_reg sfr_phy_cfg_691_reg; /* offset : 0x40f0 */
	union pcie_subctrl_sfr_phy_cfg_692_reg sfr_phy_cfg_692_reg; /* offset : 0x40f4 */
	union pcie_subctrl_sfr_phy_cfg_120_reg sfr_phy_cfg_120_reg; /* offset : 0x40f8 */
	union pcie_subctrl_sfr_phy_cfg_121_reg sfr_phy_cfg_121_reg; /* offset : 0x40fc */
	union pcie_subctrl_sfr_phy_cfg_122_reg sfr_phy_cfg_122_reg; /* offset : 0x4100 */
	union pcie_subctrl_sfr_phy_cfg_123_reg sfr_phy_cfg_123_reg; /* offset : 0x4104 */
	union pcie_subctrl_sfr_phy_cfg_124_reg sfr_phy_cfg_124_reg; /* offset : 0x4108 */
	union pcie_subctrl_sfr_phy_cfg_125_reg sfr_phy_cfg_125_reg; /* offset : 0x410c */
	union pcie_subctrl_sfr_phy_cfg_126_reg sfr_phy_cfg_126_reg; /* offset : 0x4110 */
	union pcie_subctrl_sfr_phy_cfg_127_reg sfr_phy_cfg_127_reg; /* offset : 0x4114 */
	union pcie_subctrl_sfr_phy_cfg_128_reg sfr_phy_cfg_128_reg; /* offset : 0x4118 */
	union pcie_subctrl_sfr_phy_cfg_129_reg sfr_phy_cfg_129_reg; /* offset : 0x411c */
	union pcie_subctrl_sfr_phy_cfg_130_reg sfr_phy_cfg_130_reg; /* offset : 0x4120 */
	union pcie_subctrl_sfr_phy_cfg_131_reg sfr_phy_cfg_131_reg; /* offset : 0x4124 */
	union pcie_subctrl_sfr_phy_cfg_132_reg sfr_phy_cfg_132_reg; /* offset : 0x4128 */
	union pcie_subctrl_sfr_phy_cfg_133_reg sfr_phy_cfg_133_reg; /* offset : 0x412c */
	union pcie_subctrl_sfr_phy_cfg_134_reg sfr_phy_cfg_134_reg; /* offset : 0x4130 */
	union pcie_subctrl_sfr_phy_cfg_135_reg sfr_phy_cfg_135_reg; /* offset : 0x4134 */
	union pcie_subctrl_sfr_phy_cfg_136_reg sfr_phy_cfg_136_reg; /* offset : 0x4138 */
	union pcie_subctrl_sfr_phy_cfg_137_reg sfr_phy_cfg_137_reg; /* offset : 0x413c */
	union pcie_subctrl_sfr_phy_cfg_138_reg sfr_phy_cfg_138_reg; /* offset : 0x4140 */
	union pcie_subctrl_sfr_phy_cfg_139_reg sfr_phy_cfg_139_reg; /* offset : 0x4144 */
	union pcie_subctrl_sfr_phy_cfg_140_reg sfr_phy_cfg_140_reg; /* offset : 0x4148 */
	union pcie_subctrl_sfr_phy_cfg_141_reg sfr_phy_cfg_141_reg; /* offset : 0x414c */
	union pcie_subctrl_sfr_phy_cfg_142_reg sfr_phy_cfg_142_reg; /* offset : 0x4150 */
	union pcie_subctrl_sfr_phy_cfg_143_reg sfr_phy_cfg_143_reg; /* offset : 0x4154 */
	union pcie_subctrl_sfr_phy_cfg_144_reg sfr_phy_cfg_144_reg; /* offset : 0x4158 */
	union pcie_subctrl_sfr_phy_cfg_145_reg sfr_phy_cfg_145_reg; /* offset : 0x415c */
	union pcie_subctrl_sfr_phy_cfg_146_reg sfr_phy_cfg_146_reg; /* offset : 0x4160 */
	union pcie_subctrl_sfr_phy_cfg_147_reg sfr_phy_cfg_147_reg; /* offset : 0x4164 */
	union pcie_subctrl_sfr_phy_cfg_148_reg sfr_phy_cfg_148_reg; /* offset : 0x4168 */
	union pcie_subctrl_sfr_phy_cfg_149_reg sfr_phy_cfg_149_reg; /* offset : 0x416c */
	union pcie_subctrl_sfr_phy_cfg_150_reg sfr_phy_cfg_150_reg; /* offset : 0x4170 */
	union pcie_subctrl_sfr_phy_cfg_151_reg sfr_phy_cfg_151_reg; /* offset : 0x4174 */
	union pcie_subctrl_sfr_phy_cfg_152_reg sfr_phy_cfg_152_reg; /* offset : 0x4178 */
	union pcie_subctrl_sfr_phy_cfg_153_reg sfr_phy_cfg_153_reg; /* offset : 0x417c */
	union pcie_subctrl_sfr_phy_cfg_154_reg sfr_phy_cfg_154_reg; /* offset : 0x4180 */
	union pcie_subctrl_sfr_phy_cfg_155_reg sfr_phy_cfg_155_reg; /* offset : 0x4184 */
	union pcie_subctrl_sfr_phy_cfg_156_reg sfr_phy_cfg_156_reg; /* offset : 0x4188 */
	union pcie_subctrl_sfr_phy_cfg_157_reg sfr_phy_cfg_157_reg; /* offset : 0x418c */
	union pcie_subctrl_sfr_phy_cfg_158_reg sfr_phy_cfg_158_reg; /* offset : 0x4190 */
	union pcie_subctrl_sfr_phy_cfg_159_reg sfr_phy_cfg_159_reg; /* offset : 0x4194 */
	union pcie_subctrl_sfr_phy_cfg_160_reg sfr_phy_cfg_160_reg; /* offset : 0x4198 */
	union pcie_subctrl_sfr_phy_cfg_161_reg sfr_phy_cfg_161_reg; /* offset : 0x419c */
	union pcie_subctrl_sfr_phy_cfg_162_reg sfr_phy_cfg_162_reg; /* offset : 0x41a0 */
	union pcie_subctrl_sfr_phy_cfg_163_reg sfr_phy_cfg_163_reg; /* offset : 0x41a4 */
	union pcie_subctrl_sfr_phy_cfg_164_reg sfr_phy_cfg_164_reg; /* offset : 0x41a8 */
	union pcie_subctrl_sfr_phy_cfg_165_reg sfr_phy_cfg_165_reg; /* offset : 0x41ac */
	union pcie_subctrl_sfr_phy_cfg_166_reg sfr_phy_cfg_166_reg; /* offset : 0x41b0 */
	union pcie_subctrl_sfr_phy_cfg_167_reg sfr_phy_cfg_167_reg; /* offset : 0x41b4 */
	union pcie_subctrl_sfr_phy_cfg_168_reg sfr_phy_cfg_168_reg; /* offset : 0x41b8 */
	union pcie_subctrl_sfr_phy_cfg_169_reg sfr_phy_cfg_169_reg; /* offset : 0x41bc */
	union pcie_subctrl_sfr_phy_cfg_170_reg sfr_phy_cfg_170_reg; /* offset : 0x41c0 */
	union pcie_subctrl_sfr_phy_cfg_171_reg sfr_phy_cfg_171_reg; /* offset : 0x41c4 */
	union pcie_subctrl_sfr_phy_cfg_172_reg sfr_phy_cfg_172_reg; /* offset : 0x41c8 */
	union pcie_subctrl_sfr_phy_cfg_173_reg sfr_phy_cfg_173_reg; /* offset : 0x41cc */
	union pcie_subctrl_sfr_phy_cfg_174_reg sfr_phy_cfg_174_reg; /* offset : 0x41d0 */
	union pcie_subctrl_sfr_phy_cfg_175_reg sfr_phy_cfg_175_reg; /* offset : 0x41d4 */
	union pcie_subctrl_sfr_phy_cfg_176_reg sfr_phy_cfg_176_reg; /* offset : 0x41d8 */
	union pcie_subctrl_sfr_phy_cfg_177_reg sfr_phy_cfg_177_reg; /* offset : 0x41dc */
	union pcie_subctrl_sfr_phy_cfg_178_reg sfr_phy_cfg_178_reg; /* offset : 0x41e0 */
	union pcie_subctrl_sfr_phy_cfg_179_reg sfr_phy_cfg_179_reg; /* offset : 0x41e4 */
	union pcie_subctrl_sfr_phy_cfg_180_reg sfr_phy_cfg_180_reg; /* offset : 0x41e8 */
	union pcie_subctrl_sfr_phy_cfg_181_reg sfr_phy_cfg_181_reg; /* offset : 0x41ec */
	union pcie_subctrl_sfr_phy_cfg_182_reg sfr_phy_cfg_182_reg; /* offset : 0x41f0 */
	union pcie_subctrl_sfr_phy_cfg_183_reg sfr_phy_cfg_183_reg; /* offset : 0x41f4 */
	union pcie_subctrl_sfr_phy_cfg_184_reg sfr_phy_cfg_184_reg; /* offset : 0x41f8 */
	union pcie_subctrl_sfr_phy_cfg_185_reg sfr_phy_cfg_185_reg; /* offset : 0x41fc */
	union pcie_subctrl_sfr_phy_cfg_186_reg sfr_phy_cfg_186_reg; /* offset : 0x4200 */
	union pcie_subctrl_sfr_phy_cfg_187_reg sfr_phy_cfg_187_reg; /* offset : 0x4204 */
	union pcie_subctrl_sfr_phy_cfg_188_reg sfr_phy_cfg_188_reg; /* offset : 0x4208 */
	union pcie_subctrl_sfr_phy_cfg_189_reg sfr_phy_cfg_189_reg; /* offset : 0x420c */
	union pcie_subctrl_sfr_phy_cfg_190_reg sfr_phy_cfg_190_reg; /* offset : 0x4210 */
	union pcie_subctrl_sfr_phy_cfg_191_reg sfr_phy_cfg_191_reg; /* offset : 0x4214 */
	union pcie_subctrl_sfr_phy_cfg_192_reg sfr_phy_cfg_192_reg; /* offset : 0x4218 */
	union pcie_subctrl_sfr_phy_cfg_193_reg sfr_phy_cfg_193_reg; /* offset : 0x421c */
	union pcie_subctrl_sfr_phy_cfg_194_reg sfr_phy_cfg_194_reg; /* offset : 0x4220 */
	union pcie_subctrl_sfr_phy_cfg_195_reg sfr_phy_cfg_195_reg; /* offset : 0x4224 */
	union pcie_subctrl_sfr_phy_cfg_196_reg sfr_phy_cfg_196_reg; /* offset : 0x4228 */
	union pcie_subctrl_sfr_phy_cfg_197_reg sfr_phy_cfg_197_reg; /* offset : 0x422c */
	union pcie_subctrl_sfr_phy_cfg_198_reg sfr_phy_cfg_198_reg; /* offset : 0x4230 */
	union pcie_subctrl_sfr_phy_cfg_199_reg sfr_phy_cfg_199_reg; /* offset : 0x4234 */
	union pcie_subctrl_sfr_phy_cfg_200_reg sfr_phy_cfg_200_reg; /* offset : 0x4238 */
	union pcie_subctrl_sfr_phy_cfg_201_reg sfr_phy_cfg_201_reg; /* offset : 0x423c */
	union pcie_subctrl_sfr_phy_cfg_202_reg sfr_phy_cfg_202_reg; /* offset : 0x4240 */
	union pcie_subctrl_sfr_phy_cfg_203_reg sfr_phy_cfg_203_reg; /* offset : 0x4244 */
	union pcie_subctrl_sfr_phy_cfg_204_reg sfr_phy_cfg_204_reg; /* offset : 0x4248 */
	union pcie_subctrl_sfr_phy_cfg_205_reg sfr_phy_cfg_205_reg; /* offset : 0x424c */
	union pcie_subctrl_sfr_phy_cfg_206_reg sfr_phy_cfg_206_reg; /* offset : 0x4250 */
	union pcie_subctrl_sfr_phy_cfg_207_reg sfr_phy_cfg_207_reg; /* offset : 0x4254 */
	union pcie_subctrl_sfr_phy_cfg_208_reg sfr_phy_cfg_208_reg; /* offset : 0x4258 */
	union pcie_subctrl_sfr_phy_cfg_209_reg sfr_phy_cfg_209_reg; /* offset : 0x425c */
	union pcie_subctrl_sfr_phy_cfg_210_reg sfr_phy_cfg_210_reg; /* offset : 0x4260 */
	union pcie_subctrl_sfr_phy_cfg_211_reg sfr_phy_cfg_211_reg; /* offset : 0x4264 */
	union pcie_subctrl_sfr_phy_cfg_212_reg sfr_phy_cfg_212_reg; /* offset : 0x4268 */
	union pcie_subctrl_sfr_phy_cfg_213_reg sfr_phy_cfg_213_reg; /* offset : 0x426c */
	union pcie_subctrl_sfr_phy_cfg_214_reg sfr_phy_cfg_214_reg; /* offset : 0x4270 */
	union pcie_subctrl_sfr_phy_cfg_215_reg sfr_phy_cfg_215_reg; /* offset : 0x4274 */
	union pcie_subctrl_sfr_phy_cfg_216_reg sfr_phy_cfg_216_reg; /* offset : 0x4278 */
	union pcie_subctrl_sfr_phy_cfg_693_reg sfr_phy_cfg_693_reg; /* offset : 0x427c */
	union pcie_subctrl_sfr_phy_cfg_694_reg sfr_phy_cfg_694_reg; /* offset : 0x4280 */
	union pcie_subctrl_sfr_phy_cfg_695_reg sfr_phy_cfg_695_reg; /* offset : 0x4284 */
	union pcie_subctrl_sfr_phy_cfg_696_reg sfr_phy_cfg_696_reg; /* offset : 0x4288 */
	union pcie_subctrl_sfr_phy_cfg_697_reg sfr_phy_cfg_697_reg; /* offset : 0x428c */
	union pcie_subctrl_sfr_phy_cfg_698_reg sfr_phy_cfg_698_reg; /* offset : 0x4290 */
	union pcie_subctrl_sfr_phy_cfg_699_reg sfr_phy_cfg_699_reg; /* offset : 0x4294 */
	union pcie_subctrl_sfr_phy_cfg_700_reg sfr_phy_cfg_700_reg; /* offset : 0x4298 */
	union pcie_subctrl_sfr_phy_cfg_701_reg sfr_phy_cfg_701_reg; /* offset : 0x429c */
	union pcie_subctrl_sfr_phy_cfg_702_reg sfr_phy_cfg_702_reg; /* offset : 0x42a0 */
	union pcie_subctrl_sfr_phy_cfg_703_reg sfr_phy_cfg_703_reg; /* offset : 0x42a4 */
	union pcie_subctrl_sfr_phy_cfg_704_reg sfr_phy_cfg_704_reg; /* offset : 0x42a8 */
	union pcie_subctrl_sfr_phy_cfg_705_reg sfr_phy_cfg_705_reg; /* offset : 0x42ac */
	union pcie_subctrl_sfr_phy_cfg_706_reg sfr_phy_cfg_706_reg; /* offset : 0x42b0 */
	union pcie_subctrl_sfr_phy_cfg_707_reg sfr_phy_cfg_707_reg; /* offset : 0x42b4 */
	union pcie_subctrl_sfr_phy_cfg_708_reg sfr_phy_cfg_708_reg; /* offset : 0x42b8 */
	union pcie_subctrl_sfr_phy_cfg_709_reg sfr_phy_cfg_709_reg; /* offset : 0x42bc */
	union pcie_subctrl_sfr_phy_cfg_710_reg sfr_phy_cfg_710_reg; /* offset : 0x42c0 */
	union pcie_subctrl_sfr_phy_cfg_711_reg sfr_phy_cfg_711_reg; /* offset : 0x42c4 */
	union pcie_subctrl_sfr_phy_cfg_712_reg sfr_phy_cfg_712_reg; /* offset : 0x42c8 */
	union pcie_subctrl_sfr_phy_cfg_713_reg sfr_phy_cfg_713_reg; /* offset : 0x42cc */
	union pcie_subctrl_sfr_phy_cfg_714_reg sfr_phy_cfg_714_reg; /* offset : 0x42d0 */
	union pcie_subctrl_sfr_phy_cfg_715_reg sfr_phy_cfg_715_reg; /* offset : 0x42d4 */
	union pcie_subctrl_sfr_phy_cfg_716_reg sfr_phy_cfg_716_reg; /* offset : 0x42d8 */
	union pcie_subctrl_sfr_phy_cfg_717_reg sfr_phy_cfg_717_reg; /* offset : 0x42dc */
	union pcie_subctrl_sfr_phy_cfg_718_reg sfr_phy_cfg_718_reg; /* offset : 0x42e0 */
	union pcie_subctrl_sfr_phy_cfg_719_reg sfr_phy_cfg_719_reg; /* offset : 0x42e4 */
	union pcie_subctrl_sfr_phy_cfg_720_reg sfr_phy_cfg_720_reg; /* offset : 0x42e8 */
	union pcie_subctrl_sfr_phy_cfg_721_reg sfr_phy_cfg_721_reg; /* offset : 0x42ec */
	union pcie_subctrl_sfr_phy_cfg_722_reg sfr_phy_cfg_722_reg; /* offset : 0x42f0 */
	union pcie_subctrl_sfr_phy_cfg_723_reg sfr_phy_cfg_723_reg; /* offset : 0x42f4 */
	union pcie_subctrl_sfr_phy_cfg_724_reg sfr_phy_cfg_724_reg; /* offset : 0x42f8 */
	union pcie_subctrl_sfr_phy_cfg_725_reg sfr_phy_cfg_725_reg; /* offset : 0x42fc */
	union pcie_subctrl_sfr_phy_cfg_726_reg sfr_phy_cfg_726_reg; /* offset : 0x4300 */
	union pcie_subctrl_sfr_phy_cfg_727_reg sfr_phy_cfg_727_reg; /* offset : 0x4304 */
	union pcie_subctrl_sfr_phy_cfg_728_reg sfr_phy_cfg_728_reg; /* offset : 0x4308 */
	union pcie_subctrl_sfr_phy_cfg_729_reg sfr_phy_cfg_729_reg; /* offset : 0x430c */
	union pcie_subctrl_sfr_phy_cfg_730_reg sfr_phy_cfg_730_reg; /* offset : 0x4310 */
	union pcie_subctrl_sfr_phy_cfg_731_reg sfr_phy_cfg_731_reg; /* offset : 0x4314 */
	union pcie_subctrl_sfr_phy_cfg_732_reg sfr_phy_cfg_732_reg; /* offset : 0x4318 */
	union pcie_subctrl_sfr_phy_cfg_733_reg sfr_phy_cfg_733_reg; /* offset : 0x431c */
	union pcie_subctrl_sfr_phy_cfg_734_reg sfr_phy_cfg_734_reg; /* offset : 0x4320 */
	union pcie_subctrl_sfr_phy_cfg_735_reg sfr_phy_cfg_735_reg; /* offset : 0x4324 */
	union pcie_subctrl_sfr_phy_cfg_736_reg sfr_phy_cfg_736_reg; /* offset : 0x4328 */
	union pcie_subctrl_sfr_phy_cfg_737_reg sfr_phy_cfg_737_reg; /* offset : 0x432c */
	union pcie_subctrl_sfr_phy_cfg_738_reg sfr_phy_cfg_738_reg; /* offset : 0x4330 */
	union pcie_subctrl_sfr_phy_cfg_739_reg sfr_phy_cfg_739_reg; /* offset : 0x4334 */
	union pcie_subctrl_sfr_phy_cfg_740_reg sfr_phy_cfg_740_reg; /* offset : 0x4338 */
	union pcie_subctrl_sfr_phy_cfg_741_reg sfr_phy_cfg_741_reg; /* offset : 0x433c */
	union pcie_subctrl_sfr_phy_cfg_742_reg sfr_phy_cfg_742_reg; /* offset : 0x4340 */
	union pcie_subctrl_sfr_app_flr_pf_done sfr_app_flr_pf_done; /* offset : 0x4344 */
	union pcie_subctrl_sfr_app_flr_vf_done sfr_app_flr_vf_done; /* offset : 0x4348 */
	union pcie_subctrl_sfr_dbg_pba sfr_dbg_pba; /* offset : 0x434c */
	union pcie_subctrl_sfr_dbg_table sfr_dbg_table; /* offset : 0x4350 */
	union pcie_subctrl_irq_pad_perst_n irq_pad_perst_n; /* offset : 0x4354 */
	union pcie_subctrl_irq_en_pad_perst_n irq_en_pad_perst_n; /* offset : 0x4358 */
	union pcie_subctrl_irq_reset irq_reset; /* offset : 0x435c */
	union pcie_subctrl_irq_reset_en irq_reset_en; /* offset : 0x4360 */
	union pcie_subctrl_sfr_edma_int_cm7 sfr_edma_int_cm7; /* offset : 0x4364 */
	union pcie_subctrl_sfr_edma_int_ca73 sfr_edma_int_ca73; /* offset : 0x4368 */
	union pcie_subctrl_irq_bw_changed irq_bw_changed; /* offset : 0x436c */
	union pcie_subctrl_irq_en_bw_changed irq_en_bw_changed; /* offset : 0x4370 */
	union pcie_subctrl_irq_rbar_changed irq_rbar_changed; /* offset : 0x4374 */
	union pcie_subctrl_irq_en_rbar_changed irq_en_rbar_changed; /* offset : 0x4378 */
	union pcie_subctrl_irq_vf_rbar_changed irq_vf_rbar_changed; /* offset : 0x437c */
	union pcie_subctrl_irq_en_vf_rbar_changed irq_en_vf_rbar_changed; /* offset : 0x4380 */
	union pcie_subctrl_irq_app_parity_err irq_app_parity_err; /* offset : 0x4384 */
	union pcie_subctrl_irq_en_app_parity_err irq_en_app_parity_err; /* offset : 0x4388 */
	union pcie_subctrl_irq_ram_parity_err_0 irq_ram_parity_err_0; /* offset : 0x438c */
	union pcie_subctrl_irq_ram_parity_err_1 irq_ram_parity_err_1; /* offset : 0x4390 */
	union pcie_subctrl_irq_en_ram_parity_err_0 irq_en_ram_parity_err_0; /* offset : 0x4394 */
	union pcie_subctrl_irq_en_ram_parity_err_1 irq_en_ram_parity_err_1; /* offset : 0x4398 */
	union pcie_subctrl_irq_axi_parity_err irq_axi_parity_err; /* offset : 0x439c */
	union pcie_subctrl_irq_en_axi_parity_err irq_en_axi_parity_err; /* offset : 0x43a0 */
	union pcie_subctrl_sfr_radm_trgt1_atu_cbuf_err_31_0 sfr_radm_trgt1_atu_cbuf_err_31_0; /* offset : 0x43a4 */
	union pcie_subctrl_sfr_radm_trgt1_atu_cbuf_err_63_32 sfr_radm_trgt1_atu_cbuf_err_63_32; /* offset : 0x43a8 */
	uint32_t reserved_37[2];
	union pcie_subctrl_irq_cbuf_err irq_cbuf_err; /* offset : 0x43b4 */
	union pcie_subctrl_irq_en_cbuf_err irq_en_cbuf_err; /* offset : 0x43b8 */
	union pcie_subctrl_irq_elbi_rst irq_elbi_rst; /* offset : 0x43bc */
	union pcie_subctrl_irq_en_elbi_rst irq_en_elbi_rst; /* offset : 0x43c0 */
	union pcie_subctrl_sfr_perstn_control sfr_perstn_control; /* offset : 0x43c4 */
	union pcie_subctrl_sfr_hotreset_control sfr_hotreset_control; /* offset : 0x43c8 */
	union pcie_subctrl_sfr_hotreset sfr_hotreset; /* offset : 0x43cc */
	uint32_t reserved_38;
	union pcie_subctrl_sfr_mask_control sfr_mask_control; /* offset : 0x43d4 */
	uint32_t reserved_39;
	union pcie_subctrl_sfr_prs sfr_prs; /* offset : 0x43dc */
	union pcie_subctrl_sfr_radm_poisoned_type sfr_radm_poisoned_type; /* offset : 0x43e0 */
	union pcie_subctrl_sfr_radm_poisoned_detect sfr_radm_poisoned_detect; /* offset : 0x43e4 */
	union pcie_subctrl_sfr_pcie_ras_des_sd_dbg_signal sfr_pcie_ras_des_sd_dbg_signal; /* offset : 0x43e8 */
	union pcie_subctrl_sfr_ras_des_sel sfr_ras_des_sel; /* offset : 0x43ec */
	union pcie_subctrl_sfr_pcie_dbg_signal sfr_pcie_dbg_signal; /* offset : 0x43f0 */
	union pcie_subctrl_sfr_app_tdi_state_pf sfr_app_tdi_state_pf; /* offset : 0x43f4 */
	union pcie_subctrl_sfr_app_tdi_state_vf_31_0 sfr_app_tdi_state_vf_31_0; /* offset : 0x43f8 */
	union pcie_subctrl_sfr_app_tdi_state_vf_47_32 sfr_app_tdi_state_vf_47_32; /* offset : 0x43fc */
	union pcie_subctrl_sfr_mstr_misc_info_t_bit sfr_mstr_misc_info_t_bit; /* offset : 0x4400 */
	union pcie_subctrl_sfr_pm_sel_aux_clk_ovrd sfr_pm_sel_aux_clk_ovrd; /* offset : 0x4404 */
	union pcie_subctrl_sfr_mstr_armisc_info_nw sfr_mstr_armisc_info_nw; /* offset : 0x4408 */
	union pcie_subctrl_sfr_mstr_armisc_info_ats sfr_mstr_armisc_info_ats; /* offset : 0x440c */
	union pcie_subctrl_sfr_mstr_armisc_info_tph sfr_mstr_armisc_info_tph; /* offset : 0x4410 */
	union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_31_0 sfr_mstr_armisc_info_tlpprfx_31_0; /* offset : 0x4414 */
	union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_63_32 sfr_mstr_armisc_info_tlpprfx_63_32; /* offset : 0x4418 */
	union pcie_subctrl_sfr_mstr_armisc_info_tlpprfx_71_64 sfr_mstr_armisc_info_tlpprfx_71_64; /* offset : 0x441c */
	union pcie_subctrl_sfr_mstr_armisc_info_ido sfr_mstr_armisc_info_ido; /* offset : 0x4420 */
	union pcie_subctrl_sfr_mstr_awmisc_info_nw sfr_mstr_awmisc_info_nw; /* offset : 0x4424 */
	union pcie_subctrl_sfr_mstr_awmisc_info_ats sfr_mstr_awmisc_info_ats; /* offset : 0x4428 */
	union pcie_subctrl_sfr_mstr_awmisc_info_tph sfr_mstr_awmisc_info_tph; /* offset : 0x442c */
	union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_31_0 sfr_mstr_awmisc_info_tlpprfx_31_0; /* offset : 0x4430 */
	union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_63_32 sfr_mstr_awmisc_info_tlpprfx_63_32; /* offset : 0x4434 */
	union pcie_subctrl_sfr_mstr_awmisc_info_tlpprfx_71_64 sfr_mstr_awmisc_info_tlpprfx_71_64; /* offset : 0x4438 */
	union pcie_subctrl_sfr_mstr_awmisc_info_ido sfr_mstr_awmisc_info_ido; /* offset : 0x443c */
	uint32_t reserved_40[240];
	union pcie_subctrl_sfr_slv_misc_info_t_bit sfr_slv_misc_info_t_bit; /* offset : 0x4800 */
	union pcie_subctrl_sfr_dbi_misc_info_t_bit sfr_dbi_misc_info_t_bit; /* offset : 0x4804 */
	union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_0 sfr_slv_bmisc_info_tlpprfx_0; /* offset : 0x4808 */
	union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_1 sfr_slv_bmisc_info_tlpprfx_1; /* offset : 0x480c */
	union pcie_subctrl_sfr_slv_bmisc_info_tlpprfx_2 sfr_slv_bmisc_info_tlpprfx_2; /* offset : 0x4810 */
	union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_0 sfr_slv_rmisc_info_tlpprfx_0; /* offset : 0x4814 */
	union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_1 sfr_slv_rmisc_info_tlpprfx_1; /* offset : 0x4818 */
	union pcie_subctrl_sfr_slv_rmisc_info_tlpprfx_2 sfr_slv_rmisc_info_tlpprfx_2; /* offset : 0x481c */
	uint32_t reserved_41[504];
	union pcie_subctrl_sfr_app_send_stream_to_insecure sfr_app_send_stream_to_insecure; /* offset : 0x5000 */
	union pcie_subctrl_sfr_edma_wr_eng_hard_stop sfr_edma_wr_eng_hard_stop; /* offset : 0x5004 */
	union pcie_subctrl_sfr_edma_rd_eng_hard_stop sfr_edma_rd_eng_hard_stop; /* offset : 0x5008 */
	union pcie_subctrl_sfr_ide_irq_out sfr_ide_irq_out; /* offset : 0x500c */
	union pcie_subctrl_sfr_irq_radm_rcvd sfr_irq_radm_rcvd; /* offset : 0x5010 */
	union pcie_subctrl_sfr_irq_en_radm_rcvd sfr_irq_en_radm_rcvd; /* offset : 0x5014 */
	union pcie_subctrl_sfr_radm_rcvd_num sfr_radm_rcvd_num; /* offset : 0x5018 */
	union pcie_subctrl_sfr_radm_vendor_msg_type sfr_radm_vendor_msg_type; /* offset : 0x501c */
	union pcie_subctrl_sfr_sw_rst_n sfr_sw_rst_n; /* offset : 0x5020 */
	union pcie_subctrl_sfr_irq_radm_trgt1_atu_sloc_match_31_0 sfr_irq_radm_trgt1_atu_sloc_match_31_0; /* offset : 0x5024 */
	union pcie_subctrl_sfr_irq_radm_trgt1_atu_sloc_match_63_32 sfr_irq_radm_trgt1_atu_sloc_match_63_32; /* offset : 0x5028 */
	union pcie_subctrl_sfr_irq_en_radm_trgt1_atu_sloc_match_31_0 sfr_irq_en_radm_trgt1_atu_sloc_match_31_0; /* offset : 0x502c */
	union pcie_subctrl_sfr_irq_en_radm_trgt1_atu_sloc_match_63_32 sfr_irq_en_radm_trgt1_atu_sloc_match_63_32; /* offset : 0x5030 */
	union pcie_subctrl_sfr_cbuf_error_cnt_0 sfr_cbuf_error_cnt_0; /* offset : 0x5034 */
	union pcie_subctrl_sfr_cbuf_error_cnt_1 sfr_cbuf_error_cnt_1; /* offset : 0x5038 */
	union pcie_subctrl_sfr_cbuf_error_cnt_2 sfr_cbuf_error_cnt_2; /* offset : 0x503c */
	union pcie_subctrl_sfr_cbuf_error_cnt_3 sfr_cbuf_error_cnt_3; /* offset : 0x5040 */
	union pcie_subctrl_sfr_cbuf_error_cnt_4 sfr_cbuf_error_cnt_4; /* offset : 0x5044 */
	union pcie_subctrl_sfr_cbuf_error_cnt_5 sfr_cbuf_error_cnt_5; /* offset : 0x5048 */
	union pcie_subctrl_sfr_cbuf_error_cnt_6 sfr_cbuf_error_cnt_6; /* offset : 0x504c */
	union pcie_subctrl_sfr_cbuf_error_cnt_7 sfr_cbuf_error_cnt_7; /* offset : 0x5050 */
	union pcie_subctrl_sfr_cbuf_error_cnt_8 sfr_cbuf_error_cnt_8; /* offset : 0x5054 */
	union pcie_subctrl_sfr_cbuf_error_cnt_9 sfr_cbuf_error_cnt_9; /* offset : 0x5058 */
	union pcie_subctrl_sfr_cbuf_error_cnt_10 sfr_cbuf_error_cnt_10; /* offset : 0x505c */
	union pcie_subctrl_sfr_cbuf_error_cnt_11 sfr_cbuf_error_cnt_11; /* offset : 0x5060 */
	union pcie_subctrl_sfr_cbuf_error_cnt_12 sfr_cbuf_error_cnt_12; /* offset : 0x5064 */
	union pcie_subctrl_sfr_cbuf_error_cnt_13 sfr_cbuf_error_cnt_13; /* offset : 0x5068 */
	union pcie_subctrl_sfr_cbuf_error_cnt_14 sfr_cbuf_error_cnt_14; /* offset : 0x506c */
	union pcie_subctrl_sfr_cbuf_error_cnt_15 sfr_cbuf_error_cnt_15; /* offset : 0x5070 */
	union pcie_subctrl_sfr_cbuf_error_cnt_16 sfr_cbuf_error_cnt_16; /* offset : 0x5074 */
	union pcie_subctrl_sfr_cbuf_error_cnt_17 sfr_cbuf_error_cnt_17; /* offset : 0x5078 */
	union pcie_subctrl_sfr_cbuf_error_cnt_18 sfr_cbuf_error_cnt_18; /* offset : 0x507c */
	union pcie_subctrl_sfr_cbuf_error_cnt_19 sfr_cbuf_error_cnt_19; /* offset : 0x5080 */
	union pcie_subctrl_sfr_cbuf_error_cnt_20 sfr_cbuf_error_cnt_20; /* offset : 0x5084 */
	union pcie_subctrl_sfr_cbuf_error_cnt_21 sfr_cbuf_error_cnt_21; /* offset : 0x5088 */
	union pcie_subctrl_sfr_cbuf_error_cnt_22 sfr_cbuf_error_cnt_22; /* offset : 0x508c */
	union pcie_subctrl_sfr_cbuf_error_cnt_23 sfr_cbuf_error_cnt_23; /* offset : 0x5090 */
	union pcie_subctrl_sfr_cbuf_error_cnt_24 sfr_cbuf_error_cnt_24; /* offset : 0x5094 */
	union pcie_subctrl_sfr_cbuf_error_cnt_25 sfr_cbuf_error_cnt_25; /* offset : 0x5098 */
	union pcie_subctrl_sfr_cbuf_error_cnt_26 sfr_cbuf_error_cnt_26; /* offset : 0x509c */
	union pcie_subctrl_sfr_cbuf_error_cnt_27 sfr_cbuf_error_cnt_27; /* offset : 0x50a0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_28 sfr_cbuf_error_cnt_28; /* offset : 0x50a4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_29 sfr_cbuf_error_cnt_29; /* offset : 0x50a8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_30 sfr_cbuf_error_cnt_30; /* offset : 0x50ac */
	union pcie_subctrl_sfr_cbuf_error_cnt_31 sfr_cbuf_error_cnt_31; /* offset : 0x50b0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_32 sfr_cbuf_error_cnt_32; /* offset : 0x50b4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_33 sfr_cbuf_error_cnt_33; /* offset : 0x50b8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_34 sfr_cbuf_error_cnt_34; /* offset : 0x50bc */
	union pcie_subctrl_sfr_cbuf_error_cnt_35 sfr_cbuf_error_cnt_35; /* offset : 0x50c0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_36 sfr_cbuf_error_cnt_36; /* offset : 0x50c4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_37 sfr_cbuf_error_cnt_37; /* offset : 0x50c8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_38 sfr_cbuf_error_cnt_38; /* offset : 0x50cc */
	union pcie_subctrl_sfr_cbuf_error_cnt_39 sfr_cbuf_error_cnt_39; /* offset : 0x50d0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_40 sfr_cbuf_error_cnt_40; /* offset : 0x50d4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_41 sfr_cbuf_error_cnt_41; /* offset : 0x50d8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_42 sfr_cbuf_error_cnt_42; /* offset : 0x50dc */
	union pcie_subctrl_sfr_cbuf_error_cnt_43 sfr_cbuf_error_cnt_43; /* offset : 0x50e0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_44 sfr_cbuf_error_cnt_44; /* offset : 0x50e4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_45 sfr_cbuf_error_cnt_45; /* offset : 0x50e8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_46 sfr_cbuf_error_cnt_46; /* offset : 0x50ec */
	union pcie_subctrl_sfr_cbuf_error_cnt_47 sfr_cbuf_error_cnt_47; /* offset : 0x50f0 */
	union pcie_subctrl_sfr_cbuf_error_cnt_48 sfr_cbuf_error_cnt_48; /* offset : 0x50f4 */
	union pcie_subctrl_sfr_cbuf_error_cnt_49 sfr_cbuf_error_cnt_49; /* offset : 0x50f8 */
	union pcie_subctrl_sfr_cbuf_error_cnt_50 sfr_cbuf_error_cnt_50; /* offset : 0x50fc */
	union pcie_subctrl_sfr_cbuf_error_cnt_51 sfr_cbuf_error_cnt_51; /* offset : 0x5100 */
	union pcie_subctrl_sfr_cbuf_error_cnt_52 sfr_cbuf_error_cnt_52; /* offset : 0x5104 */
	union pcie_subctrl_sfr_cbuf_error_cnt_53 sfr_cbuf_error_cnt_53; /* offset : 0x5108 */
	union pcie_subctrl_sfr_cbuf_error_cnt_54 sfr_cbuf_error_cnt_54; /* offset : 0x510c */
	union pcie_subctrl_sfr_cbuf_error_cnt_55 sfr_cbuf_error_cnt_55; /* offset : 0x5110 */
	union pcie_subctrl_sfr_cbuf_error_cnt_56 sfr_cbuf_error_cnt_56; /* offset : 0x5114 */
	union pcie_subctrl_sfr_cbuf_error_cnt_57 sfr_cbuf_error_cnt_57; /* offset : 0x5118 */
	union pcie_subctrl_sfr_cbuf_error_cnt_58 sfr_cbuf_error_cnt_58; /* offset : 0x511c */
	union pcie_subctrl_sfr_cbuf_error_cnt_59 sfr_cbuf_error_cnt_59; /* offset : 0x5120 */
	union pcie_subctrl_sfr_cbuf_error_cnt_60 sfr_cbuf_error_cnt_60; /* offset : 0x5124 */
	union pcie_subctrl_sfr_cbuf_error_cnt_61 sfr_cbuf_error_cnt_61; /* offset : 0x5128 */
	union pcie_subctrl_sfr_cbuf_error_cnt_62 sfr_cbuf_error_cnt_62; /* offset : 0x512c */
	union pcie_subctrl_sfr_cbuf_error_cnt_63 sfr_cbuf_error_cnt_63; /* offset : 0x5130 */
	union pcie_subctrl_sfr_training_rst_n_fall sfr_training_rst_n_fall; /* offset : 0x5134 */
	union pcie_subctrl_sfr_smlh_link_disable_rise sfr_smlh_link_disable_rise; /* offset : 0x5138 */
	union pcie_subctrl_sfr_phy0_sup_misc sfr_phy0_sup_misc; /* offset : 0x513c */
	union pcie_subctrl_sfr_phy1_sup_misc sfr_phy1_sup_misc; /* offset : 0x5140 */
	union pcie_subctrl_sfr_phy2_sup_misc sfr_phy2_sup_misc; /* offset : 0x5144 */
	union pcie_subctrl_sfr_phy3_sup_misc sfr_phy3_sup_misc; /* offset : 0x5148 */
	union pcie_subctrl_sfr_phy_cfg_514c_reg sfr_phy_cfg_514c_reg; /* offset : 0x514c */
	union pcie_subctrl_sfr_phy_cfg_5150_reg sfr_phy_cfg_5150_reg; /* offset : 0x5150 */
	union pcie_subctrl_sfr_phy_cfg_5154_reg sfr_phy_cfg_5154_reg; /* offset : 0x5154 */
	union pcie_subctrl_sfr_phy_cfg_5158_reg sfr_phy_cfg_5158_reg; /* offset : 0x5158 */
	union pcie_subctrl_sfr_phy_cfg_515c_reg sfr_phy_cfg_515c_reg; /* offset : 0x515c */
	union pcie_subctrl_sfr_phy_cfg_5160_reg sfr_phy_cfg_5160_reg; /* offset : 0x5160 */
	union pcie_subctrl_sfr_phy_cfg_5164_reg sfr_phy_cfg_5164_reg; /* offset : 0x5164 */
	union pcie_subctrl_sfr_phy_cfg_5168_reg sfr_phy_cfg_5168_reg; /* offset : 0x5168 */
	union pcie_subctrl_sfr_phy_cfg_516c_reg sfr_phy_cfg_516c_reg; /* offset : 0x516c */
	union pcie_subctrl_sfr_phy_cfg_5170_reg sfr_phy_cfg_5170_reg; /* offset : 0x5170 */
	union pcie_subctrl_sfr_phy_cfg_5174_reg sfr_phy_cfg_5174_reg; /* offset : 0x5174 */
	union pcie_subctrl_sfr_phy_cfg_5178_reg sfr_phy_cfg_5178_reg; /* offset : 0x5178 */
	union pcie_subctrl_sfr_phy_cfg_517c_reg sfr_phy_cfg_517c_reg; /* offset : 0x517c */
	union pcie_subctrl_sfr_phy_cfg_5180_reg sfr_phy_cfg_5180_reg; /* offset : 0x5180 */
	union pcie_subctrl_sfr_phy_cfg_5184_reg sfr_phy_cfg_5184_reg; /* offset : 0x5184 */
	union pcie_subctrl_sfr_phy_cfg_5188_reg sfr_phy_cfg_5188_reg; /* offset : 0x5188 */
	union pcie_subctrl_sfr_phy_cfg_518c_reg sfr_phy_cfg_518c_reg; /* offset : 0x518c */
	union pcie_subctrl_sfr_phy_cfg_5190_reg sfr_phy_cfg_5190_reg; /* offset : 0x5190 */
	union pcie_subctrl_sfr_phy_cfg_5194_reg sfr_phy_cfg_5194_reg; /* offset : 0x5194 */
	union pcie_subctrl_sfr_phy_cfg_5198_reg sfr_phy_cfg_5198_reg; /* offset : 0x5198 */
	union pcie_subctrl_sfr_phy_cfg_519c_reg sfr_phy_cfg_519c_reg; /* offset : 0x519c */
	union pcie_subctrl_sfr_phy_cfg_51a0_reg sfr_phy_cfg_51a0_reg; /* offset : 0x51a0 */
	union pcie_subctrl_sfr_phy_cfg_51a4_reg sfr_phy_cfg_51a4_reg; /* offset : 0x51a4 */
	union pcie_subctrl_sfr_phy_cfg_51a8_reg sfr_phy_cfg_51a8_reg; /* offset : 0x51a8 */
	union pcie_subctrl_sfr_phy_cfg_51ac_reg sfr_phy_cfg_51ac_reg; /* offset : 0x51ac */
	union pcie_subctrl_sfr_phy_cfg_51b0_reg sfr_phy_cfg_51b0_reg; /* offset : 0x51b0 */
	union pcie_subctrl_sfr_phy_cfg_51b4_reg sfr_phy_cfg_51b4_reg; /* offset : 0x51b4 */
	union pcie_subctrl_sfr_phy_cfg_51b8_reg sfr_phy_cfg_51b8_reg; /* offset : 0x51b8 */
	union pcie_subctrl_sfr_phy_cfg_51bc_reg sfr_phy_cfg_51bc_reg; /* offset : 0x51bc */
	union pcie_subctrl_sfr_phy_cfg_51c0_reg sfr_phy_cfg_51c0_reg; /* offset : 0x51c0 */
	union pcie_subctrl_sfr_phy_cfg_51c4_reg sfr_phy_cfg_51c4_reg; /* offset : 0x51c4 */
	union pcie_subctrl_sfr_phy_cfg_51c8_reg sfr_phy_cfg_51c8_reg; /* offset : 0x51c8 */
	union pcie_subctrl_sfr_phy_cfg_51cc_reg sfr_phy_cfg_51cc_reg; /* offset : 0x51cc */
	union pcie_subctrl_sfr_phy_cfg_51d0_reg sfr_phy_cfg_51d0_reg; /* offset : 0x51d0 */
	union pcie_subctrl_sfr_phy_cfg_51d4_reg sfr_phy_cfg_51d4_reg; /* offset : 0x51d4 */
	union pcie_subctrl_sfr_phy_cfg_51d8_reg sfr_phy_cfg_51d8_reg; /* offset : 0x51d8 */
	union pcie_subctrl_sfr_phy_cfg_51dc_reg sfr_phy_cfg_51dc_reg; /* offset : 0x51dc */
	union pcie_subctrl_sfr_phy_cfg_51e0_reg sfr_phy_cfg_51e0_reg; /* offset : 0x51e0 */
	union pcie_subctrl_sfr_phy_cfg_51e4_reg sfr_phy_cfg_51e4_reg; /* offset : 0x51e4 */
	union pcie_subctrl_sfr_phy_cfg_51e8_reg sfr_phy_cfg_51e8_reg; /* offset : 0x51e8 */
	union pcie_subctrl_sfr_phy_cfg_51ec_reg sfr_phy_cfg_51ec_reg; /* offset : 0x51ec */
	union pcie_subctrl_sfr_phy_cfg_51f0_reg sfr_phy_cfg_51f0_reg; /* offset : 0x51f0 */
	union pcie_subctrl_sfr_phy_cfg_51f4_reg sfr_phy_cfg_51f4_reg; /* offset : 0x51f4 */
	union pcie_subctrl_sfr_phy_cfg_51f8_reg sfr_phy_cfg_51f8_reg; /* offset : 0x51f8 */
	union pcie_subctrl_sfr_phy_cfg_51fc_reg sfr_phy_cfg_51fc_reg; /* offset : 0x51fc */
	union pcie_subctrl_sfr_phy_cfg_5200_reg sfr_phy_cfg_5200_reg; /* offset : 0x5200 */
	union pcie_subctrl_sfr_phy_cfg_5204_reg sfr_phy_cfg_5204_reg; /* offset : 0x5204 */
	union pcie_subctrl_sfr_phy_cfg_5208_reg sfr_phy_cfg_5208_reg; /* offset : 0x5208 */
	union pcie_subctrl_sfr_phy_cfg_520c_reg sfr_phy_cfg_520c_reg; /* offset : 0x520c */
	union pcie_subctrl_sfr_phy_cfg_5210_reg sfr_phy_cfg_5210_reg; /* offset : 0x5210 */
	union pcie_subctrl_sfr_phy_cfg_5214_reg sfr_phy_cfg_5214_reg; /* offset : 0x5214 */
	union pcie_subctrl_sfr_phy_cfg_5218_reg sfr_phy_cfg_5218_reg; /* offset : 0x5218 */
	union pcie_subctrl_sfr_phy_cfg_521c_reg sfr_phy_cfg_521c_reg; /* offset : 0x521c */
	union pcie_subctrl_sfr_phy_cfg_5220_reg sfr_phy_cfg_5220_reg; /* offset : 0x5220 */
	union pcie_subctrl_sfr_phy_cfg_5224_reg sfr_phy_cfg_5224_reg; /* offset : 0x5224 */
	union pcie_subctrl_sfr_phy_cfg_5228_reg sfr_phy_cfg_5228_reg; /* offset : 0x5228 */
	union pcie_subctrl_sfr_phy_cfg_522c_reg sfr_phy_cfg_522c_reg; /* offset : 0x522c */
	union pcie_subctrl_sfr_phy_cfg_5230_reg sfr_phy_cfg_5230_reg; /* offset : 0x5230 */
	union pcie_subctrl_sfr_phy_cfg_5234_reg sfr_phy_cfg_5234_reg; /* offset : 0x5234 */
	union pcie_subctrl_sfr_phy_cfg_5238_reg sfr_phy_cfg_5238_reg; /* offset : 0x5238 */
	union pcie_subctrl_sfr_phy_cfg_523c_reg sfr_phy_cfg_523c_reg; /* offset : 0x523c */
	union pcie_subctrl_sfr_phy_cfg_5240_reg sfr_phy_cfg_5240_reg; /* offset : 0x5240 */
	union pcie_subctrl_sfr_phy_cfg_5244_reg sfr_phy_cfg_5244_reg; /* offset : 0x5244 */
	union pcie_subctrl_sfr_phy_cfg_5248_reg sfr_phy_cfg_5248_reg; /* offset : 0x5248 */
	union pcie_subctrl_sfr_phy_cfg_524c_reg sfr_phy_cfg_524c_reg; /* offset : 0x524c */
	union pcie_subctrl_sfr_phy_cfg_5250_reg sfr_phy_cfg_5250_reg; /* offset : 0x5250 */
	union pcie_subctrl_sfr_phy_cfg_5254_reg sfr_phy_cfg_5254_reg; /* offset : 0x5254 */
	union pcie_subctrl_sfr_phy_cfg_5258_reg sfr_phy_cfg_5258_reg; /* offset : 0x5258 */
	union pcie_subctrl_sfr_phy_cfg_525c_reg sfr_phy_cfg_525c_reg; /* offset : 0x525c */
	union pcie_subctrl_sfr_phy_cfg_5260_reg sfr_phy_cfg_5260_reg; /* offset : 0x5260 */
	union pcie_subctrl_sfr_phy_cfg_5264_reg sfr_phy_cfg_5264_reg; /* offset : 0x5264 */
	union pcie_subctrl_sfr_phy_cfg_5268_reg sfr_phy_cfg_5268_reg; /* offset : 0x5268 */
	union pcie_subctrl_sfr_phy_cfg_526c_reg sfr_phy_cfg_526c_reg; /* offset : 0x526c */
	union pcie_subctrl_sfr_phy_cfg_5270_reg sfr_phy_cfg_5270_reg; /* offset : 0x5270 */
	union pcie_subctrl_sfr_phy_cfg_5274_reg sfr_phy_cfg_5274_reg; /* offset : 0x5274 */
	union pcie_subctrl_sfr_phy_cfg_5278_reg sfr_phy_cfg_5278_reg; /* offset : 0x5278 */
	union pcie_subctrl_sfr_phy_cfg_527c_reg sfr_phy_cfg_527c_reg; /* offset : 0x527c */
	union pcie_subctrl_sfr_phy_cfg_5280_reg sfr_phy_cfg_5280_reg; /* offset : 0x5280 */
	union pcie_subctrl_sfr_phy_cfg_5284_reg sfr_phy_cfg_5284_reg; /* offset : 0x5284 */
	union pcie_subctrl_sfr_phy_cfg_5288_reg sfr_phy_cfg_5288_reg; /* offset : 0x5288 */
	union pcie_subctrl_sfr_phy_cfg_528c_reg sfr_phy_cfg_528c_reg; /* offset : 0x528c */
	union pcie_subctrl_sfr_phy_cfg_5290_reg sfr_phy_cfg_5290_reg; /* offset : 0x5290 */
	union pcie_subctrl_sfr_phy_cfg_5294_reg sfr_phy_cfg_5294_reg; /* offset : 0x5294 */
	union pcie_subctrl_sfr_phy_cfg_5298_reg sfr_phy_cfg_5298_reg; /* offset : 0x5298 */
	union pcie_subctrl_sfr_phy_cfg_529c_reg sfr_phy_cfg_529c_reg; /* offset : 0x529c */
	union pcie_subctrl_sfr_phy_cfg_52a0_reg sfr_phy_cfg_52a0_reg; /* offset : 0x52a0 */
	union pcie_subctrl_sfr_phy_cfg_52a4_reg sfr_phy_cfg_52a4_reg; /* offset : 0x52a4 */
	union pcie_subctrl_sfr_phy_cfg_52a8_reg sfr_phy_cfg_52a8_reg; /* offset : 0x52a8 */
	union pcie_subctrl_sfr_phy_cfg_52ac_reg sfr_phy_cfg_52ac_reg; /* offset : 0x52ac */
	union pcie_subctrl_sfr_phy_cfg_52b0_reg sfr_phy_cfg_52b0_reg; /* offset : 0x52b0 */
	union pcie_subctrl_sfr_phy_cfg_52b4_reg sfr_phy_cfg_52b4_reg; /* offset : 0x52b4 */
	union pcie_subctrl_sfr_phy_cfg_52b8_reg sfr_phy_cfg_52b8_reg; /* offset : 0x52b8 */
	union pcie_subctrl_sfr_phy_cfg_52bc_reg sfr_phy_cfg_52bc_reg; /* offset : 0x52bc */
	union pcie_subctrl_sfr_phy_cfg_52c0_reg sfr_phy_cfg_52c0_reg; /* offset : 0x52c0 */
	union pcie_subctrl_sfr_phy_cfg_52c4_reg sfr_phy_cfg_52c4_reg; /* offset : 0x52c4 */
	union pcie_subctrl_sfr_phy_cfg_52c8_reg sfr_phy_cfg_52c8_reg; /* offset : 0x52c8 */
	union pcie_subctrl_sfr_phy_cfg_52cc_reg sfr_phy_cfg_52cc_reg; /* offset : 0x52cc */
	union pcie_subctrl_sfr_phy_cfg_52d0_reg sfr_phy_cfg_52d0_reg; /* offset : 0x52d0 */
	union pcie_subctrl_sfr_phy_cfg_52d4_reg sfr_phy_cfg_52d4_reg; /* offset : 0x52d4 */
	union pcie_subctrl_sfr_phy_cfg_52d8_reg sfr_phy_cfg_52d8_reg; /* offset : 0x52d8 */
	union pcie_subctrl_sfr_phy_cfg_52dc_reg sfr_phy_cfg_52dc_reg; /* offset : 0x52dc */
	union pcie_subctrl_sfr_phy_cfg_52e0_reg sfr_phy_cfg_52e0_reg; /* offset : 0x52e0 */
	union pcie_subctrl_sfr_phy_cfg_52e4_reg sfr_phy_cfg_52e4_reg; /* offset : 0x52e4 */
	union pcie_subctrl_sfr_phy_cfg_52e8_reg sfr_phy_cfg_52e8_reg; /* offset : 0x52e8 */
	union pcie_subctrl_sfr_phy_cfg_52ec_reg sfr_phy_cfg_52ec_reg; /* offset : 0x52ec */
	union pcie_subctrl_sfr_phy_cfg_52f0_reg sfr_phy_cfg_52f0_reg; /* offset : 0x52f0 */
	union pcie_subctrl_sfr_phy_cfg_52f4_reg sfr_phy_cfg_52f4_reg; /* offset : 0x52f4 */
	union pcie_subctrl_sfr_phy_cfg_52f8_reg sfr_phy_cfg_52f8_reg; /* offset : 0x52f8 */
	union pcie_subctrl_sfr_phy_cfg_52fc_reg sfr_phy_cfg_52fc_reg; /* offset : 0x52fc */
	union pcie_subctrl_sfr_phy_cfg_5300_reg sfr_phy_cfg_5300_reg; /* offset : 0x5300 */
	union pcie_subctrl_sfr_phy_cfg_5304_reg sfr_phy_cfg_5304_reg; /* offset : 0x5304 */
	union pcie_subctrl_sfr_phy_cfg_5308_reg sfr_phy_cfg_5308_reg; /* offset : 0x5308 */
	union pcie_subctrl_sfr_upcs_mpll_ssc_sync_mode sfr_upcs_mpll_ssc_sync_mode; /* offset : 0x530c */
	union pcie_subctrl_sfr_phy_sram_ded_sec_sticky_status sfr_phy_sram_ded_sec_sticky_status; /* offset : 0x5310 */
	union pcie_subctrl_sfr_cfg_ido_req_cpl_en sfr_cfg_ido_req_cpl_en; /* offset : 0x5314 */
	union pcie_subctrl_sfr_cfg_pf_tph_st_mode sfr_cfg_pf_tph_st_mode; /* offset : 0x5318 */
	union pcie_subctrl_sfr_cfg_vf_tph_st_mode_31_0 sfr_cfg_vf_tph_st_mode_31_0; /* offset : 0x531c */
	union pcie_subctrl_sfr_cfg_vf_tph_st_mode_47_32 sfr_cfg_vf_tph_st_mode_47_32; /* offset : 0x5320 */
	union pcie_subctrl_sfr_mpll_status sfr_mpll_status; /* offset : 0x5324 */
	uint32_t reserved_42[2];
	union pcie_subctrl_sfr_ide_aes_mem_zero_init_in sfr_ide_aes_mem_zero_init_in; /* offset : 0x5330 */
	union pcie_subctrl_sfr_ide_aes_mem_zero_done_out sfr_ide_aes_mem_zero_done_out; /* offset : 0x5334 */
	union pcie_subctrl_sfr_sw_button_rst_n sfr_sw_button_rst_n; /* offset : 0x5338 */
	union pcie_subctrl_sfr_edma_int_cm7_mask sfr_edma_int_cm7_mask; /* offset : 0x533c */
	union pcie_subctrl_sfr_edma_int_ca73_mask sfr_edma_int_ca73_mask; /* offset : 0x5340 */
	union pcie_subctrl_sfr_perstn_sel sfr_perstn_sel; /* offset : 0x5344 */
	union pcie_subctrl_sfr_ide_lock_in sfr_ide_lock_in; /* offset : 0x5348 */
	union pcie_subctrl_sfr_ide_test_control sfr_ide_test_control; /* offset : 0x534c */
	union pcie_subctrl_sfr_ide_bist_done_out sfr_ide_bist_done_out; /* offset : 0x5350 */
	union pcie_subctrl_sfr_ide_bist_err sfr_ide_bist_err; /* offset : 0x5354 */
	union pcie_subctrl_sfr_ide_bist_err_timestamp_tx_out_31_0 sfr_ide_bist_err_timestamp_tx_out_31_0;
	union pcie_subctrl_sfr_ide_bist_err_timestamp_tx_out_63_32 sfr_ide_bist_err_timestamp_tx_out_63_32;
	union pcie_subctrl_sfr_ide_bist_err_timestamp_rx1_out_31_0 sfr_ide_bist_err_timestamp_rx1_out_31_0;
	union pcie_subctrl_sfr_ide_bist_err_timestamp_rx1_out_63_32 sfr_ide_bist_err_timestamp_rx1_out_63_32;
	union pcie_subctrl_sfr_sw_ide_rst sfr_sw_ide_rst; /* offset : 0x5368 */
	union pcie_subctrl_sfr_ide_apb_bist_clk_en sfr_ide_apb_bist_clk_en; /* offset : 0x536c */
	union pcie_subctrl_sfr_ide_bist_done_out_clear sfr_ide_bist_done_out_clear; /* offset : 0x5370 */
	uint32_t reserved_43[803];
	union pcie_subctrl_sfr_atu_sloc_match_cnt_0 sfr_atu_sloc_match_cnt_0; /* offset : 0x6000 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_1 sfr_atu_sloc_match_cnt_1; /* offset : 0x6004 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_2 sfr_atu_sloc_match_cnt_2; /* offset : 0x6008 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_3 sfr_atu_sloc_match_cnt_3; /* offset : 0x600c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_4 sfr_atu_sloc_match_cnt_4; /* offset : 0x6010 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_5 sfr_atu_sloc_match_cnt_5; /* offset : 0x6014 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_6 sfr_atu_sloc_match_cnt_6; /* offset : 0x6018 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_7 sfr_atu_sloc_match_cnt_7; /* offset : 0x601c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_8 sfr_atu_sloc_match_cnt_8; /* offset : 0x6020 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_9 sfr_atu_sloc_match_cnt_9; /* offset : 0x6024 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_10 sfr_atu_sloc_match_cnt_10; /* offset : 0x6028 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_11 sfr_atu_sloc_match_cnt_11; /* offset : 0x602c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_12 sfr_atu_sloc_match_cnt_12; /* offset : 0x6030 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_13 sfr_atu_sloc_match_cnt_13; /* offset : 0x6034 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_14 sfr_atu_sloc_match_cnt_14; /* offset : 0x6038 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_15 sfr_atu_sloc_match_cnt_15; /* offset : 0x603c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_16 sfr_atu_sloc_match_cnt_16; /* offset : 0x6040 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_17 sfr_atu_sloc_match_cnt_17; /* offset : 0x6044 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_18 sfr_atu_sloc_match_cnt_18; /* offset : 0x6048 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_19 sfr_atu_sloc_match_cnt_19; /* offset : 0x604c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_20 sfr_atu_sloc_match_cnt_20; /* offset : 0x6050 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_21 sfr_atu_sloc_match_cnt_21; /* offset : 0x6054 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_22 sfr_atu_sloc_match_cnt_22; /* offset : 0x6058 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_23 sfr_atu_sloc_match_cnt_23; /* offset : 0x605c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_24 sfr_atu_sloc_match_cnt_24; /* offset : 0x6060 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_25 sfr_atu_sloc_match_cnt_25; /* offset : 0x6064 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_26 sfr_atu_sloc_match_cnt_26; /* offset : 0x6068 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_27 sfr_atu_sloc_match_cnt_27; /* offset : 0x606c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_28 sfr_atu_sloc_match_cnt_28; /* offset : 0x6070 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_29 sfr_atu_sloc_match_cnt_29; /* offset : 0x6074 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_30 sfr_atu_sloc_match_cnt_30; /* offset : 0x6078 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_31 sfr_atu_sloc_match_cnt_31; /* offset : 0x607c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_32 sfr_atu_sloc_match_cnt_32; /* offset : 0x6080 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_33 sfr_atu_sloc_match_cnt_33; /* offset : 0x6084 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_34 sfr_atu_sloc_match_cnt_34; /* offset : 0x6088 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_35 sfr_atu_sloc_match_cnt_35; /* offset : 0x608c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_36 sfr_atu_sloc_match_cnt_36; /* offset : 0x6090 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_37 sfr_atu_sloc_match_cnt_37; /* offset : 0x6094 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_38 sfr_atu_sloc_match_cnt_38; /* offset : 0x6098 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_39 sfr_atu_sloc_match_cnt_39; /* offset : 0x609c */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_40 sfr_atu_sloc_match_cnt_40; /* offset : 0x60a0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_41 sfr_atu_sloc_match_cnt_41; /* offset : 0x60a4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_42 sfr_atu_sloc_match_cnt_42; /* offset : 0x60a8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_43 sfr_atu_sloc_match_cnt_43; /* offset : 0x60ac */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_44 sfr_atu_sloc_match_cnt_44; /* offset : 0x60b0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_45 sfr_atu_sloc_match_cnt_45; /* offset : 0x60b4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_46 sfr_atu_sloc_match_cnt_46; /* offset : 0x60b8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_47 sfr_atu_sloc_match_cnt_47; /* offset : 0x60bc */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_48 sfr_atu_sloc_match_cnt_48; /* offset : 0x60c0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_49 sfr_atu_sloc_match_cnt_49; /* offset : 0x60c4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_50 sfr_atu_sloc_match_cnt_50; /* offset : 0x60c8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_51 sfr_atu_sloc_match_cnt_51; /* offset : 0x60cc */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_52 sfr_atu_sloc_match_cnt_52; /* offset : 0x60d0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_53 sfr_atu_sloc_match_cnt_53; /* offset : 0x60d4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_54 sfr_atu_sloc_match_cnt_54; /* offset : 0x60d8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_55 sfr_atu_sloc_match_cnt_55; /* offset : 0x60dc */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_56 sfr_atu_sloc_match_cnt_56; /* offset : 0x60e0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_57 sfr_atu_sloc_match_cnt_57; /* offset : 0x60e4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_58 sfr_atu_sloc_match_cnt_58; /* offset : 0x60e8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_59 sfr_atu_sloc_match_cnt_59; /* offset : 0x60ec */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_60 sfr_atu_sloc_match_cnt_60; /* offset : 0x60f0 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_61 sfr_atu_sloc_match_cnt_61; /* offset : 0x60f4 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_62 sfr_atu_sloc_match_cnt_62; /* offset : 0x60f8 */
	union pcie_subctrl_sfr_atu_sloc_match_cnt_63 sfr_atu_sloc_match_cnt_63; /* offset : 0x60fc */
};
