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

union aw_ucie_dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr {
	struct {
		uint32_t pcie_extnd_cap_hdr_cap_id:16; /* [15:0] */
		uint32_t pcie_extnd_cap_hdr_revision_id:4; /* [19:16] */
		uint32_t pcie_extnd_cap_hdr_next_cap_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr1 {
	struct {
		uint32_t hdr1_dvsec_vndr_id:16; /* [15:0] */
		uint32_t hdr1_dvsec_revision:4; /* [19:16] */
		uint32_t hdr1_len:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor {
	struct {
		uint32_t hdr2_dvsec_id:16; /* [15:0] */
		uint32_t cap_descriptor_no_of_reg_locators:3; /* [18:16] */
		uint32_t cap_descriptor_sb_mailbox_reg_present:1; /* [19:19] */
		uint32_t cap_descriptor_no_of_switch_dsps:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cap {
	struct {
		uint32_t lcap_raw_format:1; /* [0:0] */
		uint32_t lcap_max_link_width:3; /* [3:1] */
		uint32_t lcap_max_link_speed:4; /* [7:4] */
		uint32_t lcap_retimer:1; /* [8:8] */
		uint32_t lcap_multi_stack_capable:1; /* [9:9] */
		uint32_t lcap_adv_pkg:1; /* [10:10] */
		uint32_t lcap_68b_flit_fmt_strmng:1; /* [11:11] */
		uint32_t lcap_std_256b_end_hdr_flit_fmt_strmng:1; /* [12:12] */
		uint32_t lcap_std_256b_start_hdr_flit_fmt_strmng:1; /* [13:13] */
		uint32_t lcap_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng:1; /* [14:14] */
		uint32_t lcap_lat_opt_256b_flit_fmt_optnl_bytes_strmng:1; /* [15:15] */
		uint32_t lcap_enhanced_multi_protocol_cap:1; /* [16:16] */
		uint32_t lcap_std_start_hdr_flit_pcie:1; /* [17:17] */
		uint32_t lcap_lat_opt_flit_with_optnl_bytes_pcie:1; /* [18:18] */
		uint32_t lcap_runtime_link_test_parity_feat_err_signaling:1; /* [19:19] */
		uint32_t lcap_apmw:1; /* [20:20] */
		uint32_t lcap_width32_mode:1; /* [21:21] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl {
	struct {
		uint32_t lcntrl_raw_format_en:1; /* [0:0] */
		uint32_t lcntrl_multi_stack_en:1; /* [1:1] */
		uint32_t lcntrl_target_link_width:4; /* [5:2] */
		uint32_t lcntrl_target_link_speed:4; /* [9:6] */
		uint32_t lcntrl_start_ucie_link_training:1; /* [10:10] */
		uint32_t lcntrl_retrain_ucie_link:1; /* [11:11] */
		uint32_t lcntrl_phy_layer_clk_gating_en:1; /* [12:12] */
		uint32_t lcntrl_68b_flit_fmt_strmng:1; /* [13:13] */
		uint32_t lcntrl_std_256b_end_hdr_flit_fmt_strmng:1; /* [14:14] */
		uint32_t lcntrl_std_256b_start_hdr_flit_fmt_strmng:1; /* [15:15] */
		uint32_t lcntrl_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng:1; /* [16:16] */
		uint32_t lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng:1; /* [17:17] */
		uint32_t lcntrl_enhanced_multi_protocol_cap:1; /* [18:18] */
		uint32_t lcntrl_std_start_hdr_flit_pcie:1; /* [19:19] */
		uint32_t lcntrl_lat_opt_flit_optnl_bytes_pcie:1; /* [20:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status {
	struct {
		uint32_t lstatus_raw_format_en:1; /* [0:0] */
		uint32_t lstatus_multi_stack_en:1; /* [1:1] */
		uint32_t lstatus_enhanced_multi_protocol_en:1; /* [2:2] */
		uint32_t lstatus_adv_pkg_mod_size:1; /* [3:3] */
		uint32_t reserved_bit_0:3;
		uint32_t lstatus_link_width_en:4; /* [10:7] */
		uint32_t lstatus_link_speed_en:4; /* [14:11] */
		uint32_t lstatus_link_status:1; /* [15:15] */
		uint32_t lstatus_link_train_or_retrain:1; /* [16:16] */
		uint32_t lstatus_link_status_change:1; /* [17:17] */
		uint32_t lstatus_hw_autonomous_bw_change:1; /* [18:18] */
		uint32_t lstatus_ucie_link_corr_err:1; /* [19:19] */
		uint32_t lstatus_ucie_link_uncorr_non_fatal_err:1; /* [20:20] */
		uint32_t lstatus_ucie_link_uncorr_fatal_err:1; /* [21:21] */
		uint32_t lstatus_flit_format_status:4; /* [25:22] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl {
	struct {
		uint32_t link_status_change_ucie_link_event_intr_en:1; /* [0:0] */
		uint32_t hw_autonomous_bw_change_ucie_link_event_intr_en:1; /* [1:1] */
		uint32_t reserved_bit_0:9;
		uint32_t link_event_nf_intr_num:5; /* [15:11] */
		uint32_t err_nf_ctrl_corr_err_prtcl_layer_report_en:1; /* [16:16] */
		uint32_t err_nf_ctrl_corr_err_ucie_link_err_intr_en:1; /* [17:17] */
		uint32_t err_nf_ctrl_uncorr_non_fatal_err_ptcl_lyr_rpt_en:1; /* [18:18] */
		uint32_t err_nf_ctrl_uncorr_non_fatal_err_ucie_link_err_intr_en:1; /* [19:19] */
		uint32_t err_nf_ctrl_uncorr_fatal_err_ptcl_lyr_report_en:1; /* [20:20] */
		uint32_t err_nf_ctrl_uncorr_fatal_err_ucie_link_err_intr_en:1; /* [21:21] */
		uint32_t reserved_bit_1:5;
		uint32_t err_nf_cntrl_link_event_notif_intr_num:5; /* [31:27] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_low {
	struct {
		uint32_t reg_loc0_low_reg_bir:3; /* [2:0] */
		uint32_t reg_loc0_low_reg_blk_identifier:4; /* [6:3] */
		uint32_t reserved_bit_0:5;
		uint32_t reg_loc0_low_reg_blk_offset:20; /* [31:12] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_high {
	struct {
		uint32_t reg_loc0_high_reg_blk_offset; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_low {
	struct {
		uint32_t reg_loc1_low_reg_bir:3; /* [2:0] */
		uint32_t reg_loc1_low_reg_blk_identifier:4; /* [6:3] */
		uint32_t reserved_bit_0:5;
		uint32_t reg_loc1_low_reg_blk_offset:20; /* [31:12] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_high {
	struct {
		uint32_t reg_loc1_high_reg_blk_offset; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_low {
	struct {
		uint32_t reg_loc2_low_reg_bir:3; /* [2:0] */
		uint32_t reg_loc2_low_reg_blk_identifier:4; /* [6:3] */
		uint32_t reserved_bit_0:5;
		uint32_t reg_loc2_low_reg_blk_offset:20; /* [31:12] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_high {
	struct {
		uint32_t reg_loc2_high_reg_blk_offset; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_low {
	struct {
		uint32_t reg_loc3_low_reg_bir:3; /* [2:0] */
		uint32_t reg_loc3_low_reg_blk_identifier:4; /* [6:3] */
		uint32_t reserved_bit_0:5;
		uint32_t reg_loc3_low_reg_blk_offset:20; /* [31:12] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_high {
	struct {
		uint32_t reg_loc3_high_reg_blk_offset; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low {
	struct {
		uint32_t sb_mailbox_index_low_opcode:5; /* [4:0] */
		uint32_t sb_mailbox_index_low_be:8; /* [12:5] */
		uint32_t sb_mailbox_index_low_addr:19; /* [31:13] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high {
	struct {
		uint32_t sb_mailbox_index_high_addr:5; /* [4:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low {
	struct {
		uint32_t sb_mailbox_data_low_wr_or_rd_opcode; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high {
	struct {
		uint32_t sb_mailbox_data_high_wr_or_rd_opcode; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats {
	struct {
		uint32_t sb_mailbox_ctrl_wr_or_rd_trigger:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t sb_mailbox_stats_wr_or_rd_status:2; /* [9:8] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_req_id {
	struct {
		uint32_t req_id:24; /* [23:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec1_reg_reg_global_dvsec1_associated_port_num {
	struct {
		uint32_t assoc_port_num1:8; /* [7:0] */
		uint32_t assoc_port_num2:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_pcie_extnd_cap_hdr {
	struct {
		uint32_t pcie_extnd_cap_hdr_cap_id:16; /* [15:0] */
		uint32_t pcie_extnd_cap_hdr_rev_id:4; /* [19:16] */
		uint32_t pcie_extnd_cap_hdr_next_cap_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr1 {
	struct {
		uint32_t dvsec_hdr1_dvsec_vndr_id:16; /* [15:0] */
		uint32_t dvsec_hdr1_dvsec_revision:4; /* [19:16] */
		uint32_t dvsec_hdr1_len:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr2 {
	struct {
		uint32_t dvsec_hdr2_dvsec_id:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1 {
	struct {
		uint32_t uisrb_base_addr_reg1_bir:1; /* [0:0] */
		uint32_t reserved_bit_0:11;
		uint32_t uisrb_base_addr_reg1_blk_offset:20; /* [31:12] */
	};
	uint32_t val;
};

union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2 {
	struct {
		uint32_t uisrb_base_addr_reg2_blk_offset; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 {
	struct {
		uint32_t vndr_id:16; /* [15:0] */
		uint32_t vndr_id_reg_block:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 {
	struct {
		uint32_t vndr_reg_block_version:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 {
	struct {
		uint32_t vndr_reg_block_length; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg4 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat {
	struct {
		uint32_t adpt_timeout:1; /* [0:0] */
		uint32_t rcvr_overflow:1; /* [1:1] */
		uint32_t internal_err:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd:1; /* [4:4] */
		uint32_t invld_param_exchange:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask {
	struct {
		uint32_t adpt_timeout_mask:1; /* [0:0] */
		uint32_t rcvr_overflow_mask:1; /* [1:1] */
		uint32_t internal_err_mask:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd_mask:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd_mask:1; /* [4:4] */
		uint32_t invld_param_exchange_mask:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity {
	struct {
		uint32_t adpt_timeout_severity:1; /* [0:0] */
		uint32_t rcvr_overflow_severity:1; /* [1:1] */
		uint32_t internal_err_severity:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd_severity:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd_severity:1; /* [4:4] */
		uint32_t invld_param_exchange_severity:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat {
	struct {
		uint32_t crc_err_detected:1; /* [0:0] */
		uint32_t adpt_lsm_trans_retrain:1; /* [1:1] */
		uint32_t corr_internal_err:1; /* [2:2] */
		uint32_t sb_corr_err_msg_rcvd:1; /* [3:3] */
		uint32_t run_time_link_testing_parity_err:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask {
	struct {
		uint32_t crc_err_detected_mask:1; /* [0:0] */
		uint32_t adpt_lsm_trns_to_retrain_mask:1; /* [1:1] */
		uint32_t corr_internal_err_mask:1; /* [2:2] */
		uint32_t device_corr_err_msg_recv_mask:1; /* [3:3] */
		uint32_t runtime_link_tstng_parity_err_mask:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1 {
	struct {
		uint32_t hdr_log1_reg0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2 {
	struct {
		uint32_t hdr_log1_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 {
	struct {
		uint32_t adpt_timeout_encoding:4; /* [3:0] */
		uint32_t rcvr_ovf_encoding:3; /* [6:4] */
		uint32_t adpt_lsm_resp_type:3; /* [9:7] */
		uint32_t adpt_lsm_id:1; /* [10:10] */
		uint32_t reserved_bit_0:2;
		uint32_t param_exchange_successful:1; /* [13:13] */
		uint32_t flit_format:4; /* [17:14] */
		uint32_t first_fatal_err_indicator:5; /* [22:18] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl {
	struct {
		uint32_t remote_reg_access_th:4; /* [3:0] */
		uint32_t runtime_link_testing_tx_en:1; /* [4:4] */
		uint32_t runtime_link_testing_rx_en:1; /* [5:5] */
		uint32_t no_of_64b_inserts:3; /* [8:6] */
		uint32_t parity_feature_nak_rcvd:1; /* [9:9] */
		uint32_t reserved_bit_0:3;
		uint32_t crc_injection_en:2; /* [14:13] */
		uint32_t crc_injection_count:2; /* [16:15] */
		uint32_t crc_injection_busy:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1 {
	struct {
		uint32_t parity_log_reg1_mod0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2 {
	struct {
		uint32_t parity_log_reg2_mod0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1 {
	struct {
		uint32_t parity_log_reg1_mod1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2 {
	struct {
		uint32_t parity_log_reg2_mod1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1 {
	struct {
		uint32_t parity_log_reg1_mod2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2 {
	struct {
		uint32_t parity_log_reg2_mod2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1 {
	struct {
		uint32_t parity_log_reg1_mod3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2 {
	struct {
		uint32_t parity_log_reg2_mod3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 {
	struct {
		uint32_t raw_format:1; /* [0:0] */
		uint32_t _68b_flit_mode:1; /* [1:1] */
		uint32_t cxl_256b_flit_mode:1; /* [2:2] */
		uint32_t pcie_flit_mode:1; /* [3:3] */
		uint32_t streaming:1; /* [4:4] */
		uint32_t retry:1; /* [5:5] */
		uint32_t multi_protocol_enable:1; /* [6:6] */
		uint32_t stack0_enable:1; /* [7:7] */
		uint32_t stack1_enable:1; /* [8:8] */
		uint32_t cxl_latopt_fmt5:1; /* [9:9] */
		uint32_t cxl_latopt_fmt6:1; /* [10:10] */
		uint32_t retimer:1; /* [11:11] */
		uint32_t retimer_credits:1; /* [20:12] */
		uint32_t dp:1; /* [21:21] */
		uint32_t up:1; /* [22:22] */
		uint32_t _68b_flit_format:1; /* [23:23] */
		uint32_t std_256b_end_header_flit_format:1; /* [24:24] */
		uint32_t std_256b_start_header_flit_format:1; /* [25:25] */
		uint32_t latopt_256b_wo_opt_flit_format:1; /* [26:26] */
		uint32_t latopt_256b_w_opt_flit_format:1; /* [27:27] */
		uint32_t enhanced_multi_protocol_enable:1; /* [28:28] */
		uint32_t stack_0_max_bandwidth_limit:1; /* [29:29] */
		uint32_t stack_1_max_bandwidth_limit:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log2 {
	struct {
		uint32_t adv_adpt_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1 {
	struct {
		uint32_t raw_format:1; /* [0:0] */
		uint32_t _68b_flit_mode:1; /* [1:1] */
		uint32_t cxl_256b_flit_mode:1; /* [2:2] */
		uint32_t pcie_flit_mode:1; /* [3:3] */
		uint32_t streaming:1; /* [4:4] */
		uint32_t retry:1; /* [5:5] */
		uint32_t multi_protocol_enable:1; /* [6:6] */
		uint32_t stack0_enable:1; /* [7:7] */
		uint32_t stack1_enable:1; /* [8:8] */
		uint32_t cxl_latopt_fmt5:1; /* [9:9] */
		uint32_t cxl_latopt_fmt6:1; /* [10:10] */
		uint32_t retimer:1; /* [11:11] */
		uint32_t retimer_credits:1; /* [20:12] */
		uint32_t dp:1; /* [21:21] */
		uint32_t up:1; /* [22:22] */
		uint32_t _68b_flit_format:1; /* [23:23] */
		uint32_t std_256b_end_deader_flit_format:1; /* [24:24] */
		uint32_t std_256b_start_deader_flit_format:1; /* [25:25] */
		uint32_t latopt_256b_wo_opt_flit_format:1; /* [26:26] */
		uint32_t latopt_256b_w_opt_flit_format:1; /* [27:27] */
		uint32_t enhanced_multi_protocol_enable:1; /* [28:28] */
		uint32_t stack0_max_bandwidth_limit:1; /* [29:29] */
		uint32_t stack1_max_bandwidth_limit:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log2 {
	struct {
		uint32_t fin_adpt_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log1 {
	struct {
		uint32_t adv_cxl_cap_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log2 {
	struct {
		uint32_t adv_cxl_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log1 {
	struct {
		uint32_t fin_cxl_cap_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log2 {
	struct {
		uint32_t fin_cxl_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log1 {
	struct {
		uint32_t adv_multi_prtcl_cap_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log2 {
	struct {
		uint32_t adv_multi_prtcl_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log1 {
	struct {
		uint32_t fin_multi_prtcl_cap_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log2 {
	struct {
		uint32_t fin_multi_prtcl_cap_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1 {
	struct {
		uint32_t adv_cxl_cap_stack1_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2 {
	struct {
		uint32_t adv_cxl_cap_stack1_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1 {
	struct {
		uint32_t fin_cxl_cap_stack1_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2 {
	struct {
		uint32_t fin_cxl_cap_stack1_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cap {
	struct {
		uint32_t cap_mod_to_byte_map:3; /* [2:0] */
		uint32_t cap_terminated_link:1; /* [3:3] */
		uint32_t cap_tx_equalization:1; /* [4:4] */
		uint32_t cap_vswing_enc:6; /* [10:5] */
		uint32_t cap_prx_clk_mode:2; /* [12:11] */
		uint32_t cap_rx_clk_phase:2; /* [14:13] */
		uint32_t cap_pkg_type:1; /* [15:15] */
		uint32_t cap_tcm:1; /* [16:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl {
	struct {
		uint32_t cntrl_mod_to_byte_map:3; /* [2:0] */
		uint32_t cntrl_rx_terminated_cntrl:1; /* [3:3] */
		uint32_t cntrl_tx_eq_en:1; /* [4:4] */
		uint32_t cntrl_clk_mode_sel:1; /* [5:5] */
		uint32_t cntrl_clk_phase_sel:1; /* [6:6] */
		uint32_t cntrl_force_width_mode:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat {
	struct {
		uint32_t status_mod_to_byte_map:3; /* [2:0] */
		uint32_t status_rx_terminated_status:1; /* [3:3] */
		uint32_t status_tx_eq_status:1; /* [4:4] */
		uint32_t status_clk_mode_status:1; /* [5:5] */
		uint32_t status_clk_phase_status:1; /* [6:6] */
		uint32_t status_mod_lane_rev:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_init_debug {
	struct {
		uint32_t init_debug_init_cntrl:3; /* [2:0] */
		uint32_t reserved_bit_0:2;
		uint32_t init_debug_training_resume:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 {
	struct {
		uint32_t m0_data_pattern:3; /* [2:0] */
		uint32_t m0_valid_pattern:3; /* [5:3] */
		uint32_t m0_clk_phase_cntrl:4; /* [9:6] */
		uint32_t m0_train_mode:1; /* [10:10] */
		uint32_t m0_burst_cnt:16; /* [26:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup1 {
	struct {
		uint32_t m1_data_pattern:3; /* [2:0] */
		uint32_t m1_valid_pattern:3; /* [5:3] */
		uint32_t m1_clk_phase_cntrl:4; /* [9:6] */
		uint32_t m1_train_mode:1; /* [10:10] */
		uint32_t m1_burst_cnt:16; /* [26:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup1 {
	struct {
		uint32_t m2_data_pattern:3; /* [2:0] */
		uint32_t m2_valid_pattern:3; /* [5:3] */
		uint32_t m2_clk_phase_cntrl:4; /* [9:6] */
		uint32_t m2_train_mode:1; /* [10:10] */
		uint32_t m2_burst_cnt:16; /* [26:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup1 {
	struct {
		uint32_t m3_data_pattern:3; /* [2:0] */
		uint32_t m3_valid_pattern:3; /* [5:3] */
		uint32_t m3_clk_phase_cntrl:4; /* [9:6] */
		uint32_t m3_train_mode:1; /* [10:10] */
		uint32_t m3_burst_cnt:16; /* [26:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 {
	struct {
		uint32_t m0_idle_cnt:16; /* [15:0] */
		uint32_t m0_iterations:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup2 {
	struct {
		uint32_t m1_idle_cnt:16; /* [15:0] */
		uint32_t m1_iterations:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup2 {
	struct {
		uint32_t m2_idle_cnt:16; /* [15:0] */
		uint32_t m2_iterations:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup2 {
	struct {
		uint32_t m3_idle_cnt:16; /* [15:0] */
		uint32_t m3_iterations:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 {
	struct {
		uint32_t m0_reg1_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 {
	struct {
		uint32_t m0_reg2_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1 {
	struct {
		uint32_t m1_reg1_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2 {
	struct {
		uint32_t m1_reg2_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_1 {
	struct {
		uint32_t m2_reg1_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_2 {
	struct {
		uint32_t m2_reg2_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_1 {
	struct {
		uint32_t m3_reg1_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_2 {
	struct {
		uint32_t m3_reg2_lane_mask; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 {
	struct {
		uint32_t m0_repair_lane_mask:4; /* [3:0] */
		uint32_t m0_max_err_th_per_lane:12; /* [15:4] */
		uint32_t m0_max_err_th_aggregate:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup4 {
	struct {
		uint32_t m1_repair_lane_mask:4; /* [3:0] */
		uint32_t m1_max_err_th_per_lane:12; /* [15:4] */
		uint32_t m1_max_err_th_aggregate:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup4 {
	struct {
		uint32_t m2_repair_lane_mask:4; /* [3:0] */
		uint32_t m2_max_err_th_per_lane:12; /* [15:4] */
		uint32_t m2_max_err_th_aggregate:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup4 {
	struct {
		uint32_t m3_repair_lane_mask:4; /* [3:0] */
		uint32_t m3_max_err_th_per_lane:12; /* [15:4] */
		uint32_t m3_max_err_th_aggregate:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg1 {
	struct {
		uint32_t m0_rx_lane_map_reg1_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg2 {
	struct {
		uint32_t m0_rx_lane_map_reg2_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg1 {
	struct {
		uint32_t m1_rx_lane_map_reg1_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg2 {
	struct {
		uint32_t m1_rx_lane_map_reg2_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg1 {
	struct {
		uint32_t m2_rx_lane_map_reg1_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg2 {
	struct {
		uint32_t m2_rx_lane_map_reg2_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg1 {
	struct {
		uint32_t m3_rx_lane_map_reg1_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg2 {
	struct {
		uint32_t m3_rx_lane_map_reg2_clm; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log0 {
	struct {
		uint32_t m0_state_n:8; /* [7:0] */
		uint32_t m0_lane_rev:1; /* [8:8] */
		uint32_t m0_width_deg:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m0_state_n1:8; /* [23:16] */
		uint32_t m0_state_n2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log0 {
	struct {
		uint32_t m1_state_n:8; /* [7:0] */
		uint32_t m1_lane_rev:1; /* [8:8] */
		uint32_t m1_width_deg:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m1_state_n1:8; /* [23:16] */
		uint32_t m1_state_n2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log0 {
	struct {
		uint32_t m2_state_n:8; /* [7:0] */
		uint32_t m2_lane_rev:1; /* [8:8] */
		uint32_t m2_width_deg:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m2_state_n1:8; /* [23:16] */
		uint32_t m2_state_n2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log0 {
	struct {
		uint32_t m3_state_n:8; /* [7:0] */
		uint32_t m3_lane_rev:1; /* [8:8] */
		uint32_t m3_width_deg:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m3_state_n1:8; /* [23:16] */
		uint32_t m3_state_n2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log1 {
	struct {
		uint32_t m0_state_n3:8; /* [7:0] */
		uint32_t m0_state_time_out:1; /* [8:8] */
		uint32_t m0_sb_time_out:1; /* [9:9] */
		uint32_t m0_remote_link_err:1; /* [10:10] */
		uint32_t m0_internal_err:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log1 {
	struct {
		uint32_t m1_state_n3:8; /* [7:0] */
		uint32_t m1_state_time_out:1; /* [8:8] */
		uint32_t m1_sb_time_out:1; /* [9:9] */
		uint32_t m1_remote_link_err:1; /* [10:10] */
		uint32_t m1_internal_err:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log1 {
	struct {
		uint32_t m2_state_n3:8; /* [7:0] */
		uint32_t m2_state_time_out:1; /* [8:8] */
		uint32_t m2_sb_time_out:1; /* [9:9] */
		uint32_t m2_remote_link_err:1; /* [10:10] */
		uint32_t m2_internal_err:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log1 {
	struct {
		uint32_t m3_state_n3:8; /* [7:0] */
		uint32_t m3_state_time_out:1; /* [8:8] */
		uint32_t m3_sb_time_out:1; /* [9:9] */
		uint32_t m3_remote_link_err:1; /* [10:10] */
		uint32_t m3_internal_err:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1 {
	struct {
		uint32_t valid_repair:1; /* [0:0] */
		uint32_t clk_repair:1; /* [1:1] */
		uint32_t m0_lane_repair:1; /* [2:2] */
		uint32_t m1_lane_repair:1; /* [3:3] */
		uint32_t m2_lane_repair:1; /* [4:4] */
		uint32_t m3_lane_repair:1; /* [5:5] */
		uint32_t start:1; /* [6:6] */
		uint32_t inj_stuck_at_fault:1; /* [7:7] */
		uint32_t m0_lane_repair_id:7; /* [14:8] */
		uint32_t m1_lane_repair_id:7; /* [21:15] */
		uint32_t m2_lane_repair_id:7; /* [28:22] */
		uint32_t reg1_m3_lane_repair_id:3; /* [31:29] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg2 {
	struct {
		uint32_t reg2_m3_lane_repair_id:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2 {
	struct {
		uint32_t busy:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 {
	struct {
		uint32_t m0_repair_addr_trd_p0:8; /* [7:0] */
		uint32_t m0_repair_addr_trd_p1:8; /* [15:8] */
		uint32_t m0_repair_addr_trd_p2:8; /* [23:16] */
		uint32_t m0_repair_addr_trd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 {
	struct {
		uint32_t m0_repair_addr_rrd_p0:8; /* [7:0] */
		uint32_t m0_repair_addr_rrd_p1:8; /* [15:8] */
		uint32_t m0_repair_addr_rrd_p2:8; /* [23:16] */
		uint32_t m0_repair_addr_rrd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1 {
	struct {
		uint32_t m1_repair_addr_trd_p0:8; /* [7:0] */
		uint32_t m1_repair_addr_trd_p1:8; /* [15:8] */
		uint32_t m1_repair_addr_trd_p2:8; /* [23:16] */
		uint32_t m1_repair_addr_trd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2 {
	struct {
		uint32_t m1_repair_addr_rrd_p0:8; /* [7:0] */
		uint32_t m1_repair_addr_rrd_p1:8; /* [15:8] */
		uint32_t m1_repair_addr_rrd_p2:8; /* [23:16] */
		uint32_t m1_repair_addr_rrd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg1 {
	struct {
		uint32_t m2_repair_addr_trd_p0:8; /* [7:0] */
		uint32_t m2_repair_addr_trd_p1:8; /* [15:8] */
		uint32_t m2_repair_addr_trd_p2:8; /* [23:16] */
		uint32_t m2_repair_addr_trd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg2 {
	struct {
		uint32_t m2_repair_addr_rrd_p0:8; /* [7:0] */
		uint32_t m2_repair_addr_rrd_p1:8; /* [15:8] */
		uint32_t m2_repair_addr_rrd_p2:8; /* [23:16] */
		uint32_t m2_repair_addr_rrd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg1 {
	struct {
		uint32_t m3_repair_addr_trd_p0:8; /* [7:0] */
		uint32_t m3_repair_addr_trd_p1:8; /* [15:8] */
		uint32_t m3_repair_addr_trd_p2:8; /* [23:16] */
		uint32_t m3_repair_addr_trd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg2 {
	struct {
		uint32_t m3_repair_addr_rrd_p0:8; /* [7:0] */
		uint32_t m3_repair_addr_rrd_p1:8; /* [15:8] */
		uint32_t m3_repair_addr_rrd_p2:8; /* [23:16] */
		uint32_t m3_repair_addr_rrd_p3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair {
	struct {
		uint32_t m0_repair_addr_trdck_p:4; /* [3:0] */
		uint32_t m0_repair_addr_rrdck_p:4; /* [7:4] */
		uint32_t m0_repair_addr_trdvld_p:2; /* [9:8] */
		uint32_t m0_repair_addr_rrdvld_p:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m0_repair_addr_sb_tx:4; /* [19:16] */
		uint32_t m0_repair_addr_sb_rx:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair {
	struct {
		uint32_t m1_repair_addr_trdck_p:4; /* [3:0] */
		uint32_t m1_repair_addr_rrdck_p:4; /* [7:4] */
		uint32_t m1_repair_addr_trdvld_p:2; /* [9:8] */
		uint32_t m1_repair_addr_rrdvld_p:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m1_repair_addr_sb_tx:4; /* [19:16] */
		uint32_t m1_repair_addr_sb_rx:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair {
	struct {
		uint32_t m2_repair_addr_trdck_p:4; /* [3:0] */
		uint32_t m2_repair_addr_rrdck_p:4; /* [7:4] */
		uint32_t m2_repair_addr_trdvld_p:2; /* [9:8] */
		uint32_t m2_repair_addr_rrdvld_p:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m2_repair_addr_sb_tx:4; /* [19:16] */
		uint32_t m2_repair_addr_sb_rx:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair {
	struct {
		uint32_t m3_repair_addr_trdck_p:4; /* [3:0] */
		uint32_t m3_repair_addr_rrdck_p:4; /* [7:4] */
		uint32_t m3_repair_addr_trdvld_p:2; /* [9:8] */
		uint32_t m3_repair_addr_rrdvld_p:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m3_repair_addr_sb_tx:4; /* [19:16] */
		uint32_t m3_repair_addr_sb_rx:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr {
	struct {
		uint32_t extnd_cap_hdr_cap_id:16; /* [15:0] */
		uint32_t extnd_cap_hdr_revision_id:4; /* [19:16] */
		uint32_t extnd_cap_hdr_next_cap_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr1 {
	struct {
		uint32_t dvsec_hdr1_vendor_id:16; /* [15:0] */
		uint32_t dvsec_hdr1_revision:4; /* [19:16] */
		uint32_t dvsec_hdr1_length:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr2 {
	struct {
		uint32_t dvsec_hdr2_dvsec_id:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_uhm_status {
	struct {
		uint32_t reserved_bit_0:16;
		uint32_t step_cnt:8; /* [23:16] */
		uint32_t status_emv:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 {
	struct {
		uint32_t phy_eml_ln0_m0:8; /* [7:0] */
		uint32_t phy_emr_ln0_m0:8; /* [15:8] */
		uint32_t phy_eml_ln1_m0:8; /* [23:16] */
		uint32_t phy_emr_ln1_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0 {
	struct {
		uint32_t phy_eml_ln2_m0:8; /* [7:0] */
		uint32_t phy_emr_ln2_m0:8; /* [15:8] */
		uint32_t phy_eml_ln3_m0:8; /* [23:16] */
		uint32_t phy_emr_ln3_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0 {
	struct {
		uint32_t phy_eml_ln4_m0:8; /* [7:0] */
		uint32_t phy_emr_ln4_m0:8; /* [15:8] */
		uint32_t phy_eml_ln5_m0:8; /* [23:16] */
		uint32_t phy_emr_ln5_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0 {
	struct {
		uint32_t phy_eml_ln6_m0:8; /* [7:0] */
		uint32_t phy_emr_ln6_m0:8; /* [15:8] */
		uint32_t phy_eml_ln7_m0:8; /* [23:16] */
		uint32_t phy_emr_ln7_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0 {
	struct {
		uint32_t phy_eml_ln8_m0:8; /* [7:0] */
		uint32_t phy_emr_ln8_m0:8; /* [15:8] */
		uint32_t phy_eml_ln9_m0:8; /* [23:16] */
		uint32_t phy_emr_ln9_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0 {
	struct {
		uint32_t phy_eml_ln10_m0:8; /* [7:0] */
		uint32_t phy_emr_ln10_m0:8; /* [15:8] */
		uint32_t phy_eml_ln11_m0:8; /* [23:16] */
		uint32_t phy_emr_ln11_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0 {
	struct {
		uint32_t phy_eml_ln12_m0:8; /* [7:0] */
		uint32_t phy_emr_ln12_m0:8; /* [15:8] */
		uint32_t phy_eml_ln13_m0:8; /* [23:16] */
		uint32_t phy_emr_ln13_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0 {
	struct {
		uint32_t phy_eml_ln14_m0:8; /* [7:0] */
		uint32_t phy_emr_ln14_m0:8; /* [15:8] */
		uint32_t phy_eml_ln15_m0:8; /* [23:16] */
		uint32_t phy_emr_ln15_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0 {
	struct {
		uint32_t phy_eml_ln16_m0:8; /* [7:0] */
		uint32_t phy_emr_ln16_m0:8; /* [15:8] */
		uint32_t phy_eml_ln17_m0:8; /* [23:16] */
		uint32_t phy_emr_ln17_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0 {
	struct {
		uint32_t phy_eml_ln18_m0:8; /* [7:0] */
		uint32_t phy_emr_ln18_m0:8; /* [15:8] */
		uint32_t phy_eml_ln19_m0:8; /* [23:16] */
		uint32_t phy_emr_ln19_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0 {
	struct {
		uint32_t phy_eml_ln20_m0:8; /* [7:0] */
		uint32_t phy_emr_ln20_m0:8; /* [15:8] */
		uint32_t phy_eml_ln21_m0:8; /* [23:16] */
		uint32_t phy_emr_ln21_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0 {
	struct {
		uint32_t phy_eml_ln22_m0:8; /* [7:0] */
		uint32_t phy_emr_ln22_m0:8; /* [15:8] */
		uint32_t phy_eml_ln23_m0:8; /* [23:16] */
		uint32_t phy_emr_ln23_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0 {
	struct {
		uint32_t phy_eml_ln24_m0:8; /* [7:0] */
		uint32_t phy_emr_ln24_m0:8; /* [15:8] */
		uint32_t phy_eml_ln25_m0:8; /* [23:16] */
		uint32_t phy_emr_ln25_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0 {
	struct {
		uint32_t phy_eml_ln26_m0:8; /* [7:0] */
		uint32_t phy_emr_ln26_m0:8; /* [15:8] */
		uint32_t phy_eml_ln27_m0:8; /* [23:16] */
		uint32_t phy_emr_ln27_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0 {
	struct {
		uint32_t phy_eml_ln28_m0:8; /* [7:0] */
		uint32_t phy_emr_ln28_m0:8; /* [15:8] */
		uint32_t phy_eml_ln29_m0:8; /* [23:16] */
		uint32_t phy_emr_ln29_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0 {
	struct {
		uint32_t phy_eml_ln30_m0:8; /* [7:0] */
		uint32_t phy_emr_ln30_m0:8; /* [15:8] */
		uint32_t phy_eml_ln31_m0:8; /* [23:16] */
		uint32_t phy_emr_ln31_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0 {
	struct {
		uint32_t phy_eml_ln32_m0:8; /* [7:0] */
		uint32_t phy_emr_ln32_m0:8; /* [15:8] */
		uint32_t phy_eml_ln33_m0:8; /* [23:16] */
		uint32_t phy_emr_ln33_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0 {
	struct {
		uint32_t phy_eml_ln34_m0:8; /* [7:0] */
		uint32_t phy_emr_ln34_m0:8; /* [15:8] */
		uint32_t phy_eml_ln35_m0:8; /* [23:16] */
		uint32_t phy_emr_ln35_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0 {
	struct {
		uint32_t phy_eml_ln36_m0:8; /* [7:0] */
		uint32_t phy_emr_ln36_m0:8; /* [15:8] */
		uint32_t phy_eml_ln37_m0:8; /* [23:16] */
		uint32_t phy_emr_ln37_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0 {
	struct {
		uint32_t phy_eml_ln38_m0:8; /* [7:0] */
		uint32_t phy_emr_ln38_m0:8; /* [15:8] */
		uint32_t phy_eml_ln39_m0:8; /* [23:16] */
		uint32_t phy_emr_ln39_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0 {
	struct {
		uint32_t phy_eml_ln40_m0:8; /* [7:0] */
		uint32_t phy_emr_ln40_m0:8; /* [15:8] */
		uint32_t phy_eml_ln41_m0:8; /* [23:16] */
		uint32_t phy_emr_ln41_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0 {
	struct {
		uint32_t phy_eml_ln42_m0:8; /* [7:0] */
		uint32_t phy_emr_ln42_m0:8; /* [15:8] */
		uint32_t phy_eml_ln43_m0:8; /* [23:16] */
		uint32_t phy_emr_ln43_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0 {
	struct {
		uint32_t phy_eml_ln44_m0:8; /* [7:0] */
		uint32_t phy_emr_ln44_m0:8; /* [15:8] */
		uint32_t phy_eml_ln45_m0:8; /* [23:16] */
		uint32_t phy_emr_ln45_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0 {
	struct {
		uint32_t phy_eml_ln46_m0:8; /* [7:0] */
		uint32_t phy_emr_ln46_m0:8; /* [15:8] */
		uint32_t phy_eml_ln47_m0:8; /* [23:16] */
		uint32_t phy_emr_ln47_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0 {
	struct {
		uint32_t phy_eml_ln48_m0:8; /* [7:0] */
		uint32_t phy_emr_ln48_m0:8; /* [15:8] */
		uint32_t phy_eml_ln49_m0:8; /* [23:16] */
		uint32_t phy_emr_ln49_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0 {
	struct {
		uint32_t phy_eml_ln50_m0:8; /* [7:0] */
		uint32_t phy_emr_ln50_m0:8; /* [15:8] */
		uint32_t phy_eml_ln51_m0:8; /* [23:16] */
		uint32_t phy_emr_ln51_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0 {
	struct {
		uint32_t phy_eml_ln52_m0:8; /* [7:0] */
		uint32_t phy_emr_ln52_m0:8; /* [15:8] */
		uint32_t phy_eml_ln53_m0:8; /* [23:16] */
		uint32_t phy_emr_ln53_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0 {
	struct {
		uint32_t phy_eml_ln54_m0:8; /* [7:0] */
		uint32_t phy_emr_ln54_m0:8; /* [15:8] */
		uint32_t phy_eml_ln55_m0:8; /* [23:16] */
		uint32_t phy_emr_ln55_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0 {
	struct {
		uint32_t phy_eml_ln56_m0:8; /* [7:0] */
		uint32_t phy_emr_ln56_m0:8; /* [15:8] */
		uint32_t phy_eml_ln57_m0:8; /* [23:16] */
		uint32_t phy_emr_ln57_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0 {
	struct {
		uint32_t phy_eml_ln58_m0:8; /* [7:0] */
		uint32_t phy_emr_ln58_m0:8; /* [15:8] */
		uint32_t phy_eml_ln59_m0:8; /* [23:16] */
		uint32_t phy_emr_ln59_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0 {
	struct {
		uint32_t phy_eml_ln60_m0:8; /* [7:0] */
		uint32_t phy_emr_ln60_m0:8; /* [15:8] */
		uint32_t phy_eml_ln61_m0:8; /* [23:16] */
		uint32_t phy_emr_ln61_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0 {
	struct {
		uint32_t phy_eml_ln62_m0:8; /* [7:0] */
		uint32_t phy_emr_ln62_m0:8; /* [15:8] */
		uint32_t phy_eml_ln63_m0:8; /* [23:16] */
		uint32_t phy_emr_ln63_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0 {
	struct {
		uint32_t phy_eml_ln64_m0:8; /* [7:0] */
		uint32_t phy_emr_ln64_m0:8; /* [15:8] */
		uint32_t phy_eml_ln65_m0:8; /* [23:16] */
		uint32_t phy_emr_ln65_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0 {
	struct {
		uint32_t phy_eml_ln66_m0:8; /* [7:0] */
		uint32_t phy_emr_ln66_m0:8; /* [15:8] */
		uint32_t phy_eml_ln67_m0:8; /* [23:16] */
		uint32_t phy_emr_ln67_m0:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 {
	struct {
		uint32_t phy_eml_ln0_m1:8; /* [7:0] */
		uint32_t phy_emr_ln0_m1:8; /* [15:8] */
		uint32_t phy_eml_ln1_m1:8; /* [23:16] */
		uint32_t phy_emr_ln1_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1 {
	struct {
		uint32_t phy_eml_ln2_m1:8; /* [7:0] */
		uint32_t phy_emr_ln2_m1:8; /* [15:8] */
		uint32_t phy_eml_ln3_m1:8; /* [23:16] */
		uint32_t phy_emr_ln3_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1 {
	struct {
		uint32_t phy_eml_ln4_m1:8; /* [7:0] */
		uint32_t phy_emr_ln4_m1:8; /* [15:8] */
		uint32_t phy_eml_ln5_m1:8; /* [23:16] */
		uint32_t phy_emr_ln5_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1 {
	struct {
		uint32_t phy_eml_ln6_m1:8; /* [7:0] */
		uint32_t phy_emr_ln6_m1:8; /* [15:8] */
		uint32_t phy_eml_ln7_m1:8; /* [23:16] */
		uint32_t phy_emr_ln7_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1 {
	struct {
		uint32_t phy_eml_ln8_m1:8; /* [7:0] */
		uint32_t phy_emr_ln8_m1:8; /* [15:8] */
		uint32_t phy_eml_ln9_m1:8; /* [23:16] */
		uint32_t phy_emr_ln9_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1 {
	struct {
		uint32_t phy_eml_ln10_m1:8; /* [7:0] */
		uint32_t phy_emr_ln10_m1:8; /* [15:8] */
		uint32_t phy_eml_ln11_m1:8; /* [23:16] */
		uint32_t phy_emr_ln11_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1 {
	struct {
		uint32_t phy_eml_ln12_m1:8; /* [7:0] */
		uint32_t phy_emr_ln12_m1:8; /* [15:8] */
		uint32_t phy_eml_ln13_m1:8; /* [23:16] */
		uint32_t phy_emr_ln13_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1 {
	struct {
		uint32_t phy_eml_ln14_m1:8; /* [7:0] */
		uint32_t phy_emr_ln14_m1:8; /* [15:8] */
		uint32_t phy_eml_ln15_m1:8; /* [23:16] */
		uint32_t phy_emr_ln15_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1 {
	struct {
		uint32_t phy_eml_ln16_m1:8; /* [7:0] */
		uint32_t phy_emr_ln16_m1:8; /* [15:8] */
		uint32_t phy_eml_ln17_m1:8; /* [23:16] */
		uint32_t phy_emr_ln17_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1 {
	struct {
		uint32_t phy_eml_ln18_m1:8; /* [7:0] */
		uint32_t phy_emr_ln18_m1:8; /* [15:8] */
		uint32_t phy_eml_ln19_m1:8; /* [23:16] */
		uint32_t phy_emr_ln19_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1 {
	struct {
		uint32_t phy_eml_ln20_m1:8; /* [7:0] */
		uint32_t phy_emr_ln20_m1:8; /* [15:8] */
		uint32_t phy_eml_ln21_m1:8; /* [23:16] */
		uint32_t phy_emr_ln21_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1 {
	struct {
		uint32_t phy_eml_ln22_m1:8; /* [7:0] */
		uint32_t phy_emr_ln22_m1:8; /* [15:8] */
		uint32_t phy_eml_ln23_m1:8; /* [23:16] */
		uint32_t phy_emr_ln23_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1 {
	struct {
		uint32_t phy_eml_ln24_m1:8; /* [7:0] */
		uint32_t phy_emr_ln24_m1:8; /* [15:8] */
		uint32_t phy_eml_ln25_m1:8; /* [23:16] */
		uint32_t phy_emr_ln25_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1 {
	struct {
		uint32_t phy_eml_ln26_m1:8; /* [7:0] */
		uint32_t phy_emr_ln26_m1:8; /* [15:8] */
		uint32_t phy_eml_ln27_m1:8; /* [23:16] */
		uint32_t phy_emr_ln27_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1 {
	struct {
		uint32_t phy_eml_ln28_m1:8; /* [7:0] */
		uint32_t phy_emr_ln28_m1:8; /* [15:8] */
		uint32_t phy_eml_ln29_m1:8; /* [23:16] */
		uint32_t phy_emr_ln29_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1 {
	struct {
		uint32_t phy_eml_ln30_m1:8; /* [7:0] */
		uint32_t phy_emr_ln30_m1:8; /* [15:8] */
		uint32_t phy_eml_ln31_m1:8; /* [23:16] */
		uint32_t phy_emr_ln31_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1 {
	struct {
		uint32_t phy_eml_ln32_m1:8; /* [7:0] */
		uint32_t phy_emr_ln32_m1:8; /* [15:8] */
		uint32_t phy_eml_ln33_m1:8; /* [23:16] */
		uint32_t phy_emr_ln33_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1 {
	struct {
		uint32_t phy_eml_ln34_m1:8; /* [7:0] */
		uint32_t phy_emr_ln34_m1:8; /* [15:8] */
		uint32_t phy_eml_ln35_m1:8; /* [23:16] */
		uint32_t phy_emr_ln35_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1 {
	struct {
		uint32_t phy_eml_ln36_m1:8; /* [7:0] */
		uint32_t phy_emr_ln36_m1:8; /* [15:8] */
		uint32_t phy_eml_ln37_m1:8; /* [23:16] */
		uint32_t phy_emr_ln37_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1 {
	struct {
		uint32_t phy_eml_ln38_m1:8; /* [7:0] */
		uint32_t phy_emr_ln38_m1:8; /* [15:8] */
		uint32_t phy_eml_ln39_m1:8; /* [23:16] */
		uint32_t phy_emr_ln39_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1 {
	struct {
		uint32_t phy_eml_ln40_m1:8; /* [7:0] */
		uint32_t phy_emr_ln40_m1:8; /* [15:8] */
		uint32_t phy_eml_ln41_m1:8; /* [23:16] */
		uint32_t phy_emr_ln41_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1 {
	struct {
		uint32_t phy_eml_ln42_m1:8; /* [7:0] */
		uint32_t phy_emr_ln42_m1:8; /* [15:8] */
		uint32_t phy_eml_ln43_m1:8; /* [23:16] */
		uint32_t phy_emr_ln43_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1 {
	struct {
		uint32_t phy_eml_ln44_m1:8; /* [7:0] */
		uint32_t phy_emr_ln44_m1:8; /* [15:8] */
		uint32_t phy_eml_ln45_m1:8; /* [23:16] */
		uint32_t phy_emr_ln45_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1 {
	struct {
		uint32_t phy_eml_ln46_m1:8; /* [7:0] */
		uint32_t phy_emr_ln46_m1:8; /* [15:8] */
		uint32_t phy_eml_ln47_m1:8; /* [23:16] */
		uint32_t phy_emr_ln47_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1 {
	struct {
		uint32_t phy_eml_ln48_m1:8; /* [7:0] */
		uint32_t phy_emr_ln48_m1:8; /* [15:8] */
		uint32_t phy_eml_ln49_m1:8; /* [23:16] */
		uint32_t phy_emr_ln49_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1 {
	struct {
		uint32_t phy_eml_ln50_m1:8; /* [7:0] */
		uint32_t phy_emr_ln50_m1:8; /* [15:8] */
		uint32_t phy_eml_ln51_m1:8; /* [23:16] */
		uint32_t phy_emr_ln51_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1 {
	struct {
		uint32_t phy_eml_ln52_m1:8; /* [7:0] */
		uint32_t phy_emr_ln52_m1:8; /* [15:8] */
		uint32_t phy_eml_ln53_m1:8; /* [23:16] */
		uint32_t phy_emr_ln53_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1 {
	struct {
		uint32_t phy_eml_ln54_m1:8; /* [7:0] */
		uint32_t phy_emr_ln54_m1:8; /* [15:8] */
		uint32_t phy_eml_ln55_m1:8; /* [23:16] */
		uint32_t phy_emr_ln55_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1 {
	struct {
		uint32_t phy_eml_ln56_m1:8; /* [7:0] */
		uint32_t phy_emr_ln56_m1:8; /* [15:8] */
		uint32_t phy_eml_ln57_m1:8; /* [23:16] */
		uint32_t phy_emr_ln57_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1 {
	struct {
		uint32_t phy_eml_ln58_m1:8; /* [7:0] */
		uint32_t phy_emr_ln58_m1:8; /* [15:8] */
		uint32_t phy_eml_ln59_m1:8; /* [23:16] */
		uint32_t phy_emr_ln59_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1 {
	struct {
		uint32_t phy_eml_ln60_m1:8; /* [7:0] */
		uint32_t phy_emr_ln60_m1:8; /* [15:8] */
		uint32_t phy_eml_ln61_m1:8; /* [23:16] */
		uint32_t phy_emr_ln61_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1 {
	struct {
		uint32_t phy_eml_ln62_m1:8; /* [7:0] */
		uint32_t phy_emr_ln62_m1:8; /* [15:8] */
		uint32_t phy_eml_ln63_m1:8; /* [23:16] */
		uint32_t phy_emr_ln63_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1 {
	struct {
		uint32_t phy_eml_ln64_m1:8; /* [7:0] */
		uint32_t phy_emr_ln64_m1:8; /* [15:8] */
		uint32_t phy_eml_ln65_m1:8; /* [23:16] */
		uint32_t phy_emr_ln65_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1 {
	struct {
		uint32_t phy_eml_ln66_m1:8; /* [7:0] */
		uint32_t phy_emr_ln66_m1:8; /* [15:8] */
		uint32_t phy_eml_ln67_m1:8; /* [23:16] */
		uint32_t phy_emr_ln67_m1:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2 {
	struct {
		uint32_t phy_eml_ln0_m2:8; /* [7:0] */
		uint32_t phy_emr_ln0_m2:8; /* [15:8] */
		uint32_t phy_eml_ln1_m2:8; /* [23:16] */
		uint32_t phy_emr_ln1_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2 {
	struct {
		uint32_t phy_eml_ln2_m2:8; /* [7:0] */
		uint32_t phy_emr_ln2_m2:8; /* [15:8] */
		uint32_t phy_eml_ln3_m2:8; /* [23:16] */
		uint32_t phy_emr_ln3_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2 {
	struct {
		uint32_t phy_eml_ln4_m2:8; /* [7:0] */
		uint32_t phy_emr_ln4_m2:8; /* [15:8] */
		uint32_t phy_eml_ln5_m2:8; /* [23:16] */
		uint32_t phy_emr_ln5_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2 {
	struct {
		uint32_t phy_eml_ln6_m2:8; /* [7:0] */
		uint32_t phy_emr_ln6_m2:8; /* [15:8] */
		uint32_t phy_eml_ln7_m2:8; /* [23:16] */
		uint32_t phy_emr_ln7_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2 {
	struct {
		uint32_t phy_eml_ln8_m2:8; /* [7:0] */
		uint32_t phy_emr_ln8_m2:8; /* [15:8] */
		uint32_t phy_eml_ln9_m2:8; /* [23:16] */
		uint32_t phy_emr_ln9_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2 {
	struct {
		uint32_t phy_eml_ln10_m2:8; /* [7:0] */
		uint32_t phy_emr_ln10_m2:8; /* [15:8] */
		uint32_t phy_eml_ln11_m2:8; /* [23:16] */
		uint32_t phy_emr_ln11_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2 {
	struct {
		uint32_t phy_eml_ln12_m2:8; /* [7:0] */
		uint32_t phy_emr_ln12_m2:8; /* [15:8] */
		uint32_t phy_eml_ln13_m2:8; /* [23:16] */
		uint32_t phy_emr_ln13_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2 {
	struct {
		uint32_t phy_eml_ln14_m2:8; /* [7:0] */
		uint32_t phy_emr_ln14_m2:8; /* [15:8] */
		uint32_t phy_eml_ln15_m2:8; /* [23:16] */
		uint32_t phy_emr_ln15_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2 {
	struct {
		uint32_t phy_eml_ln16_m2:8; /* [7:0] */
		uint32_t phy_emr_ln16_m2:8; /* [15:8] */
		uint32_t phy_eml_ln17_m2:8; /* [23:16] */
		uint32_t phy_emr_ln17_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2 {
	struct {
		uint32_t phy_eml_ln18_m2:8; /* [7:0] */
		uint32_t phy_emr_ln18_m2:8; /* [15:8] */
		uint32_t phy_eml_ln19_m2:8; /* [23:16] */
		uint32_t phy_emr_ln19_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2 {
	struct {
		uint32_t phy_eml_ln20_m2:8; /* [7:0] */
		uint32_t phy_emr_ln20_m2:8; /* [15:8] */
		uint32_t phy_eml_ln21_m2:8; /* [23:16] */
		uint32_t phy_emr_ln21_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2 {
	struct {
		uint32_t phy_eml_ln22_m2:8; /* [7:0] */
		uint32_t phy_emr_ln22_m2:8; /* [15:8] */
		uint32_t phy_eml_ln23_m2:8; /* [23:16] */
		uint32_t phy_emr_ln23_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2 {
	struct {
		uint32_t phy_eml_ln24_m2:8; /* [7:0] */
		uint32_t phy_emr_ln24_m2:8; /* [15:8] */
		uint32_t phy_eml_ln25_m2:8; /* [23:16] */
		uint32_t phy_emr_ln25_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2 {
	struct {
		uint32_t phy_eml_ln26_m2:8; /* [7:0] */
		uint32_t phy_emr_ln26_m2:8; /* [15:8] */
		uint32_t phy_eml_ln27_m2:8; /* [23:16] */
		uint32_t phy_emr_ln27_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2 {
	struct {
		uint32_t phy_eml_ln28_m2:8; /* [7:0] */
		uint32_t phy_emr_ln28_m2:8; /* [15:8] */
		uint32_t phy_eml_ln29_m2:8; /* [23:16] */
		uint32_t phy_emr_ln29_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2 {
	struct {
		uint32_t phy_eml_ln30_m2:8; /* [7:0] */
		uint32_t phy_emr_ln30_m2:8; /* [15:8] */
		uint32_t phy_eml_ln31_m2:8; /* [23:16] */
		uint32_t phy_emr_ln31_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2 {
	struct {
		uint32_t phy_eml_ln32_m2:8; /* [7:0] */
		uint32_t phy_emr_ln32_m2:8; /* [15:8] */
		uint32_t phy_eml_ln33_m2:8; /* [23:16] */
		uint32_t phy_emr_ln33_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2 {
	struct {
		uint32_t phy_eml_ln34_m2:8; /* [7:0] */
		uint32_t phy_emr_ln34_m2:8; /* [15:8] */
		uint32_t phy_eml_ln35_m2:8; /* [23:16] */
		uint32_t phy_emr_ln35_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2 {
	struct {
		uint32_t phy_eml_ln36_m2:8; /* [7:0] */
		uint32_t phy_emr_ln36_m2:8; /* [15:8] */
		uint32_t phy_eml_ln37_m2:8; /* [23:16] */
		uint32_t phy_emr_ln37_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2 {
	struct {
		uint32_t phy_eml_ln38_m2:8; /* [7:0] */
		uint32_t phy_emr_ln38_m2:8; /* [15:8] */
		uint32_t phy_eml_ln39_m2:8; /* [23:16] */
		uint32_t phy_emr_ln39_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2 {
	struct {
		uint32_t phy_eml_ln40_m2:8; /* [7:0] */
		uint32_t phy_emr_ln40_m2:8; /* [15:8] */
		uint32_t phy_eml_ln41_m2:8; /* [23:16] */
		uint32_t phy_emr_ln41_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2 {
	struct {
		uint32_t phy_eml_ln42_m2:8; /* [7:0] */
		uint32_t phy_emr_ln42_m2:8; /* [15:8] */
		uint32_t phy_eml_ln43_m2:8; /* [23:16] */
		uint32_t phy_emr_ln43_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2 {
	struct {
		uint32_t phy_eml_ln44_m2:8; /* [7:0] */
		uint32_t phy_emr_ln44_m2:8; /* [15:8] */
		uint32_t phy_eml_ln45_m2:8; /* [23:16] */
		uint32_t phy_emr_ln45_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2 {
	struct {
		uint32_t phy_eml_ln46_m2:8; /* [7:0] */
		uint32_t phy_emr_ln46_m2:8; /* [15:8] */
		uint32_t phy_eml_ln47_m2:8; /* [23:16] */
		uint32_t phy_emr_ln47_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2 {
	struct {
		uint32_t phy_eml_ln48_m2:8; /* [7:0] */
		uint32_t phy_emr_ln48_m2:8; /* [15:8] */
		uint32_t phy_eml_ln49_m2:8; /* [23:16] */
		uint32_t phy_emr_ln49_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2 {
	struct {
		uint32_t phy_eml_ln50_m2:8; /* [7:0] */
		uint32_t phy_emr_ln50_m2:8; /* [15:8] */
		uint32_t phy_eml_ln51_m2:8; /* [23:16] */
		uint32_t phy_emr_ln51_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2 {
	struct {
		uint32_t phy_eml_ln52_m2:8; /* [7:0] */
		uint32_t phy_emr_ln52_m2:8; /* [15:8] */
		uint32_t phy_eml_ln53_m2:8; /* [23:16] */
		uint32_t phy_emr_ln53_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2 {
	struct {
		uint32_t phy_eml_ln54_m2:8; /* [7:0] */
		uint32_t phy_emr_ln54_m2:8; /* [15:8] */
		uint32_t phy_eml_ln55_m2:8; /* [23:16] */
		uint32_t phy_emr_ln55_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2 {
	struct {
		uint32_t phy_eml_ln56_m2:8; /* [7:0] */
		uint32_t phy_emr_ln56_m2:8; /* [15:8] */
		uint32_t phy_eml_ln57_m2:8; /* [23:16] */
		uint32_t phy_emr_ln57_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2 {
	struct {
		uint32_t phy_eml_ln58_m2:8; /* [7:0] */
		uint32_t phy_emr_ln58_m2:8; /* [15:8] */
		uint32_t phy_eml_ln59_m2:8; /* [23:16] */
		uint32_t phy_emr_ln59_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2 {
	struct {
		uint32_t phy_eml_ln60_m2:8; /* [7:0] */
		uint32_t phy_emr_ln60_m2:8; /* [15:8] */
		uint32_t phy_eml_ln61_m2:8; /* [23:16] */
		uint32_t phy_emr_ln61_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2 {
	struct {
		uint32_t phy_eml_ln62_m2:8; /* [7:0] */
		uint32_t phy_emr_ln62_m2:8; /* [15:8] */
		uint32_t phy_eml_ln63_m2:8; /* [23:16] */
		uint32_t phy_emr_ln63_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2 {
	struct {
		uint32_t phy_eml_ln64_m2:8; /* [7:0] */
		uint32_t phy_emr_ln64_m2:8; /* [15:8] */
		uint32_t phy_eml_ln65_m2:8; /* [23:16] */
		uint32_t phy_emr_ln65_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2 {
	struct {
		uint32_t phy_eml_ln66_m2:8; /* [7:0] */
		uint32_t phy_emr_ln66_m2:8; /* [15:8] */
		uint32_t phy_eml_ln67_m2:8; /* [23:16] */
		uint32_t phy_emr_ln67_m2:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3 {
	struct {
		uint32_t phy_eml_ln0_m3:8; /* [7:0] */
		uint32_t phy_emr_ln0_m3:8; /* [15:8] */
		uint32_t phy_eml_ln1_m3:8; /* [23:16] */
		uint32_t phy_emr_ln1_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3 {
	struct {
		uint32_t phy_eml_ln2_m3:8; /* [7:0] */
		uint32_t phy_emr_ln2_m3:8; /* [15:8] */
		uint32_t phy_eml_ln3_m3:8; /* [23:16] */
		uint32_t phy_emr_ln3_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3 {
	struct {
		uint32_t phy_eml_ln4_m3:8; /* [7:0] */
		uint32_t phy_emr_ln4_m3:8; /* [15:8] */
		uint32_t phy_eml_ln5_m3:8; /* [23:16] */
		uint32_t phy_emr_ln5_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3 {
	struct {
		uint32_t phy_eml_ln6_m3:8; /* [7:0] */
		uint32_t phy_emr_ln6_m3:8; /* [15:8] */
		uint32_t phy_eml_ln7_m3:8; /* [23:16] */
		uint32_t phy_emr_ln7_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3 {
	struct {
		uint32_t phy_eml_ln8_m3:8; /* [7:0] */
		uint32_t phy_emr_ln8_m3:8; /* [15:8] */
		uint32_t phy_eml_ln9_m3:8; /* [23:16] */
		uint32_t phy_emr_ln9_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3 {
	struct {
		uint32_t phy_eml_ln10_m3:8; /* [7:0] */
		uint32_t phy_emr_ln10_m3:8; /* [15:8] */
		uint32_t phy_eml_ln11_m3:8; /* [23:16] */
		uint32_t phy_emr_ln11_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3 {
	struct {
		uint32_t phy_eml_ln12_m3:8; /* [7:0] */
		uint32_t phy_emr_ln12_m3:8; /* [15:8] */
		uint32_t phy_eml_ln13_m3:8; /* [23:16] */
		uint32_t phy_emr_ln13_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3 {
	struct {
		uint32_t phy_eml_ln14_m3:8; /* [7:0] */
		uint32_t phy_emr_ln14_m3:8; /* [15:8] */
		uint32_t phy_eml_ln15_m3:8; /* [23:16] */
		uint32_t phy_emr_ln15_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3 {
	struct {
		uint32_t phy_eml_ln16_m3:8; /* [7:0] */
		uint32_t phy_emr_ln16_m3:8; /* [15:8] */
		uint32_t phy_eml_ln17_m3:8; /* [23:16] */
		uint32_t phy_emr_ln17_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3 {
	struct {
		uint32_t phy_eml_ln18_m3:8; /* [7:0] */
		uint32_t phy_emr_ln18_m3:8; /* [15:8] */
		uint32_t phy_eml_ln19_m3:8; /* [23:16] */
		uint32_t phy_emr_ln19_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3 {
	struct {
		uint32_t phy_eml_ln20_m3:8; /* [7:0] */
		uint32_t phy_emr_ln20_m3:8; /* [15:8] */
		uint32_t phy_eml_ln21_m3:8; /* [23:16] */
		uint32_t phy_emr_ln21_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3 {
	struct {
		uint32_t phy_eml_ln22_m3:8; /* [7:0] */
		uint32_t phy_emr_ln22_m3:8; /* [15:8] */
		uint32_t phy_eml_ln23_m3:8; /* [23:16] */
		uint32_t phy_emr_ln23_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3 {
	struct {
		uint32_t phy_eml_ln24_m3:8; /* [7:0] */
		uint32_t phy_emr_ln24_m3:8; /* [15:8] */
		uint32_t phy_eml_ln25_m3:8; /* [23:16] */
		uint32_t phy_emr_ln25_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3 {
	struct {
		uint32_t phy_eml_ln26_m3:8; /* [7:0] */
		uint32_t phy_emr_ln26_m3:8; /* [15:8] */
		uint32_t phy_eml_ln27_m3:8; /* [23:16] */
		uint32_t phy_emr_ln27_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3 {
	struct {
		uint32_t phy_eml_ln28_m3:8; /* [7:0] */
		uint32_t phy_emr_ln28_m3:8; /* [15:8] */
		uint32_t phy_eml_ln29_m3:8; /* [23:16] */
		uint32_t phy_emr_ln29_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3 {
	struct {
		uint32_t phy_eml_ln30_m3:8; /* [7:0] */
		uint32_t phy_emr_ln30_m3:8; /* [15:8] */
		uint32_t phy_eml_ln31_m3:8; /* [23:16] */
		uint32_t phy_emr_ln31_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3 {
	struct {
		uint32_t phy_eml_ln32_m3:8; /* [7:0] */
		uint32_t phy_emr_ln32_m3:8; /* [15:8] */
		uint32_t phy_eml_ln33_m3:8; /* [23:16] */
		uint32_t phy_emr_ln33_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3 {
	struct {
		uint32_t phy_eml_ln34_m3:8; /* [7:0] */
		uint32_t phy_emr_ln34_m3:8; /* [15:8] */
		uint32_t phy_eml_ln35_m3:8; /* [23:16] */
		uint32_t phy_emr_ln35_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3 {
	struct {
		uint32_t phy_eml_ln36_m3:8; /* [7:0] */
		uint32_t phy_emr_ln36_m3:8; /* [15:8] */
		uint32_t phy_eml_ln37_m3:8; /* [23:16] */
		uint32_t phy_emr_ln37_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3 {
	struct {
		uint32_t phy_eml_ln38_m3:8; /* [7:0] */
		uint32_t phy_emr_ln38_m3:8; /* [15:8] */
		uint32_t phy_eml_ln39_m3:8; /* [23:16] */
		uint32_t phy_emr_ln39_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3 {
	struct {
		uint32_t phy_eml_ln40_m3:8; /* [7:0] */
		uint32_t phy_emr_ln40_m3:8; /* [15:8] */
		uint32_t phy_eml_ln41_m3:8; /* [23:16] */
		uint32_t phy_emr_ln41_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3 {
	struct {
		uint32_t phy_eml_ln42_m3:8; /* [7:0] */
		uint32_t phy_emr_ln42_m3:8; /* [15:8] */
		uint32_t phy_eml_ln43_m3:8; /* [23:16] */
		uint32_t phy_emr_ln43_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3 {
	struct {
		uint32_t phy_eml_ln44_m3:8; /* [7:0] */
		uint32_t phy_emr_ln44_m3:8; /* [15:8] */
		uint32_t phy_eml_ln45_m3:8; /* [23:16] */
		uint32_t phy_emr_ln45_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3 {
	struct {
		uint32_t phy_eml_ln46_m3:8; /* [7:0] */
		uint32_t phy_emr_ln46_m3:8; /* [15:8] */
		uint32_t phy_eml_ln47_m3:8; /* [23:16] */
		uint32_t phy_emr_ln47_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3 {
	struct {
		uint32_t phy_eml_ln48_m3:8; /* [7:0] */
		uint32_t phy_emr_ln48_m3:8; /* [15:8] */
		uint32_t phy_eml_ln49_m3:8; /* [23:16] */
		uint32_t phy_emr_ln49_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3 {
	struct {
		uint32_t phy_eml_ln50_m3:8; /* [7:0] */
		uint32_t phy_emr_ln50_m3:8; /* [15:8] */
		uint32_t phy_eml_ln51_m3:8; /* [23:16] */
		uint32_t phy_emr_ln51_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3 {
	struct {
		uint32_t phy_eml_ln52_m3:8; /* [7:0] */
		uint32_t phy_emr_ln52_m3:8; /* [15:8] */
		uint32_t phy_eml_ln53_m3:8; /* [23:16] */
		uint32_t phy_emr_ln53_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3 {
	struct {
		uint32_t phy_eml_ln54_m3:8; /* [7:0] */
		uint32_t phy_emr_ln54_m3:8; /* [15:8] */
		uint32_t phy_eml_ln55_m3:8; /* [23:16] */
		uint32_t phy_emr_ln55_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3 {
	struct {
		uint32_t phy_eml_ln56_m3:8; /* [7:0] */
		uint32_t phy_emr_ln56_m3:8; /* [15:8] */
		uint32_t phy_eml_ln57_m3:8; /* [23:16] */
		uint32_t phy_emr_ln57_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3 {
	struct {
		uint32_t phy_eml_ln58_m3:8; /* [7:0] */
		uint32_t phy_emr_ln58_m3:8; /* [15:8] */
		uint32_t phy_eml_ln59_m3:8; /* [23:16] */
		uint32_t phy_emr_ln59_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3 {
	struct {
		uint32_t phy_eml_ln60_m3:8; /* [7:0] */
		uint32_t phy_emr_ln60_m3:8; /* [15:8] */
		uint32_t phy_eml_ln61_m3:8; /* [23:16] */
		uint32_t phy_emr_ln61_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3 {
	struct {
		uint32_t phy_eml_ln62_m3:8; /* [7:0] */
		uint32_t phy_emr_ln62_m3:8; /* [15:8] */
		uint32_t phy_eml_ln63_m3:8; /* [23:16] */
		uint32_t phy_emr_ln63_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3 {
	struct {
		uint32_t phy_eml_ln64_m3:8; /* [7:0] */
		uint32_t phy_emr_ln64_m3:8; /* [15:8] */
		uint32_t phy_eml_ln65_m3:8; /* [23:16] */
		uint32_t phy_emr_ln65_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3 {
	struct {
		uint32_t phy_eml_ln66_m3:8; /* [7:0] */
		uint32_t phy_emr_ln66_m3:8; /* [15:8] */
		uint32_t phy_eml_ln67_m3:8; /* [23:16] */
		uint32_t phy_emr_ln67_m3:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1 {
	struct {
		uint32_t blk_hdr1_vndr_id:16; /* [15:0] */
		uint32_t blk_hdr1_vndr_id_reg_blk:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2 {
	struct {
		uint32_t blk_hdr2_vndr_blk_version:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3 {
	struct {
		uint32_t blk_hdr3_vndr_blk_len; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr4 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset {
	struct {
		uint32_t d2d_adapter_testcompl_blk_offset:8; /* [7:0] */
		uint32_t d2d_adapter_testcompl_blk_len:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset {
	struct {
		uint32_t phy_testcompl_blk_offset:8; /* [7:0] */
		uint32_t phy_testcompl_blk_len:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl {
	struct {
		uint32_t compliance_mode:2; /* [1:0] */
		uint32_t compliance_force_link_reset:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 {
	struct {
		uint32_t flit_tx_inj_enable:1; /* [0:0] */
		uint32_t flit_type:3; /* [3:1] */
		uint32_t inj_mode:2; /* [5:4] */
		uint32_t flit_inj_number:8; /* [13:6] */
		uint32_t payload_type:4; /* [17:14] */
		uint32_t flit_byte_offset:8; /* [25:18] */
		uint32_t pattern_repetition:6; /* [31:26] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2 {
	struct {
		uint32_t payload_fixed_pattern; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts {
	struct {
		uint32_t compliance_sts:1; /* [0:0] */
		uint32_t flit_tx_inj_sts:2; /* [2:1] */
		uint32_t flit_rx_sts:2; /* [4:3] */
		uint32_t lstate_req_inj_sts_for_stack0:1; /* [5:5] */
		uint32_t lstate_resp_inj_sts_for_stack0:1; /* [6:6] */
		uint32_t lstate_reqt_inj_sts_for_stack1:1; /* [7:7] */
		uint32_t lstate_resp_inj_sts_for_stack1:1; /* [8:8] */
		uint32_t retry_inj_sts:2; /* [10:9] */
		uint32_t num_of_retries_exceeded_th:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 {
	struct {
		uint32_t stack0_req_or_resp_inj_en_at_tx:1; /* [0:0] */
		uint32_t stack0_inj_type:1; /* [1:1] */
		uint32_t stack0_link_req:4; /* [5:2] */
		uint32_t stack0_link_resp:4; /* [9:6] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack1 {
	struct {
		uint32_t stack1_req_or_resp_inj_en_at_tx:1; /* [0:0] */
		uint32_t stack1_inj_type:1; /* [1:1] */
		uint32_t stack1_link_req:4; /* [5:2] */
		uint32_t stack1_link_resp:4; /* [9:6] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1 {
	struct {
		uint32_t retry_inj_enable:1; /* [0:0] */
		uint32_t error_inj_type_on_txd_flits:2; /* [2:1] */
		uint32_t byte_offset:8; /* [10:3] */
		uint32_t num_of_errs_btwn_inj_errs:8; /* [18:11] */
		uint32_t num_of_errs_inj:8; /* [26:19] */
		uint32_t flit_type_for_err_inj:2; /* [28:27] */
	};
	uint32_t val;
};

union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2 {
	struct {
		uint32_t tx_retry_err_th:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1 {
	struct {
		uint32_t m0_compl_en:1; /* [0:0] */
		uint32_t m0_scram_disabled:1; /* [1:1] */
		uint32_t m0_operation_trigger:1; /* [2:2] */
		uint32_t m0_operation_type:3; /* [5:3] */
		uint32_t reserved_bit_0:2;
		uint32_t m0_rx_vref_offset_enable:2; /* [9:8] */
		uint32_t m0_rx_vref_offset:8; /* [17:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_2 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2 {
	struct {
		uint32_t m0_even_ui_compare_mask:1; /* [0:0] */
		uint32_t m0_odd_ui_compare_mask:1; /* [1:1] */
		uint32_t m0_track_enable:1; /* [2:2] */
		uint32_t m0_compare_setup:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1 {
	struct {
		uint32_t m0_mode:1; /* [0:0] */
		uint32_t m0_operation_status:1; /* [1:1] */
		uint32_t m0_rx_vref_offset_operation_status:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_1 {
	struct {
		uint32_t m0_aggregate_error_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_2 {
	struct {
		uint32_t m0_rx_vref_range_up:8; /* [7:0] */
		uint32_t m0_rx_vref_range_down:8; /* [15:8] */
		uint32_t m0_trained_value_rx_vref:8; /* [23:16] */
		uint32_t m0_vref_step_count_resolution:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_1 {
	struct {
		uint32_t m0_per_lane_comp_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_2 {
	struct {
		uint32_t m0_per_lane_comp_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1 {
	struct {
		uint32_t m1_compl_en:1; /* [0:0] */
		uint32_t m1_scram_disabled:1; /* [1:1] */
		uint32_t m1_operation_trigger:1; /* [2:2] */
		uint32_t m1_operation_type:3; /* [5:3] */
		uint32_t reserved_bit_0:2;
		uint32_t m1_rx_vref_offset_enable:2; /* [9:8] */
		uint32_t m1_rx_vref_offset:8; /* [17:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_2 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2 {
	struct {
		uint32_t m1_even_ui_compare_mask:1; /* [0:0] */
		uint32_t m1_odd_ui_compare_mask:1; /* [1:1] */
		uint32_t m1_track_enable:1; /* [2:2] */
		uint32_t m1_compare_setup:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1 {
	struct {
		uint32_t m1_mode:1; /* [0:0] */
		uint32_t m1_operation_status:1; /* [1:1] */
		uint32_t m1_rx_vref_offset_operation_status:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_1 {
	struct {
		uint32_t m1_aggregate_error_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_2 {
	struct {
		uint32_t m1_rx_vref_range_up:8; /* [7:0] */
		uint32_t m1_rx_vref_range_down:8; /* [15:8] */
		uint32_t m1_trained_value_rx_vref:8; /* [23:16] */
		uint32_t m1_vref_step_count_resolution:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_1 {
	struct {
		uint32_t m1_per_lane_comp_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_2 {
	struct {
		uint32_t m1_per_lane_comp_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_1 {
	struct {
		uint32_t m2_compl_en:1; /* [0:0] */
		uint32_t m2_scram_disabled:1; /* [1:1] */
		uint32_t m2_operation_trigger:1; /* [2:2] */
		uint32_t m2_operation_type:3; /* [5:3] */
		uint32_t reserved_bit_0:2;
		uint32_t m2_rx_vref_offset_enable:2; /* [9:8] */
		uint32_t m2_rx_vref_offset:8; /* [17:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_2 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl2 {
	struct {
		uint32_t m2_even_ui_compare_mask:1; /* [0:0] */
		uint32_t m2_odd_ui_compare_mask:1; /* [1:1] */
		uint32_t m2_track_enable:1; /* [2:2] */
		uint32_t m2_compare_setup:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat1 {
	struct {
		uint32_t m2_mode:1; /* [0:0] */
		uint32_t m2_operation_status:1; /* [1:1] */
		uint32_t m2_rx_vref_offset_operation_status:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_1 {
	struct {
		uint32_t m2_aggregate_error_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_2 {
	struct {
		uint32_t m2_rx_vref_range_up:8; /* [7:0] */
		uint32_t m2_rx_vref_range_down:8; /* [15:8] */
		uint32_t m2_trained_value_rx_vref:8; /* [23:16] */
		uint32_t m2_vref_step_count_resolution:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_1 {
	struct {
		uint32_t m2_per_lane_comp_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_2 {
	struct {
		uint32_t m2_per_lane_comp_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_1 {
	struct {
		uint32_t m3_compl_en:1; /* [0:0] */
		uint32_t m3_scram_disabled:1; /* [1:1] */
		uint32_t m3_operation_trigger:1; /* [2:2] */
		uint32_t m3_operation_type:3; /* [5:3] */
		uint32_t reserved_bit_0:2;
		uint32_t m3_rx_vref_offset_enable:2; /* [9:8] */
		uint32_t m3_rx_vref_offset:8; /* [17:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_2 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl2 {
	struct {
		uint32_t m3_even_ui_compare_mask:1; /* [0:0] */
		uint32_t m3_odd_ui_compare_mask:1; /* [1:1] */
		uint32_t m3_track_enable:1; /* [2:2] */
		uint32_t m3_compare_setup:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat1 {
	struct {
		uint32_t m3_mode:1; /* [0:0] */
		uint32_t m3_operation_status:1; /* [1:1] */
		uint32_t m3_rx_vref_offset_operation_status:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_1 {
	struct {
		uint32_t m3_aggregate_error_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_2 {
	struct {
		uint32_t m3_rx_vref_range_up:8; /* [7:0] */
		uint32_t m3_rx_vref_range_down:8; /* [15:8] */
		uint32_t m3_trained_value_rx_vref:8; /* [23:16] */
		uint32_t m3_vref_step_count_resolution:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_1 {
	struct {
		uint32_t m3_per_lane_comp_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_2 {
	struct {
		uint32_t m3_per_lane_comp_reg2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1 {
	struct {
		uint32_t vndr_id:16; /* [15:0] */
		uint32_t vndr_id_reg_block:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2 {
	struct {
		uint32_t vndr_reg_block_version:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3 {
	struct {
		uint32_t vndr_reg_block_length; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr4 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_config {
	struct {
		uint32_t adapter_config_hdr:4; /* [3:0] */
		uint32_t adapter_config_crc_en:1; /* [4:4] */
		uint32_t adapter_config_prbs_seed:23; /* [27:5] */
		uint32_t adapter_config_prbs_load:1; /* [28:28] */
		uint32_t adapter_config_prbs_en:1; /* [29:29] */
		uint32_t adapter_clk_gate_en:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_fifo_wm {
	struct {
		uint32_t txsb_afifo_cfg_wm_high:8; /* [7:0] */
		uint32_t txsb_afifo_cfg_wm_low:8; /* [15:8] */
		uint32_t rxsb_afifo_cfg_wm_high:8; /* [23:16] */
		uint32_t rxsb_afifo_cfg_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg1 {
	struct {
		uint32_t txsb_cfg1_opcode:5; /* [4:0] */
		uint32_t txsb_cfg1_ep:1; /* [5:5] */
		uint32_t txsb_cfg1_be:8; /* [13:6] */
		uint32_t txsb_cfg1_tag:5; /* [18:14] */
		uint32_t txsb_cfg1_srcid:3; /* [21:19] */
		uint32_t txsb_cfg1_type:3; /* [24:22] */
		uint32_t txsb_cfg1_status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg2 {
	struct {
		uint32_t txsb_cfg2_addr:24; /* [23:0] */
		uint32_t txsb_cfg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg3 {
	struct {
		uint32_t txsb_cfg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg4 {
	struct {
		uint32_t txsb_cfg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg5 {
	struct {
		uint32_t txsb_cfg5_msgsubcode:8; /* [7:0] */
		uint32_t txsb_cfg5_msginfo:16; /* [23:8] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg6 {
	struct {
		uint32_t txsb_cfg6_msgcode:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg7 {
	struct {
		uint32_t txsb_cfg7_execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_stall_rdreg1 {
	struct {
		uint32_t txsb_stall_rdreg1_accreq_wr_ok:1; /* [0:0] */
		uint32_t txsb_stall_rdreg1_acccom_wr_ok:1; /* [1:1] */
		uint32_t txsb_stall_rdreg1_msg_wr_ok:1; /* [2:2] */
		uint32_t txsb_stall_rdreg1_vmsg_wr_ok:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_cfg {
	struct {
		uint32_t rxsbacccom_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg1 {
	struct {
		uint32_t rxsbacccom_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbacccom_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbacccom_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbacccom_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbacccom_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbacccom_rdreg1_status:3; /* [24:22] */
		uint32_t rxsbacccom_rdreg1_dstid:3; /* [27:25] */
		uint32_t rxsbacccom_rdreg1_dp:1; /* [28:28] */
		uint32_t rxsbacccom_rdreg1_cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg2 {
	struct {
		uint32_t rxsbacccom_rdreg2_avail:1; /* [0:0] */
		uint32_t rxsbacccom_rdreg2_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg3 {
	struct {
		uint32_t rxsbacccom_rdreg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg4 {
	struct {
		uint32_t rxsbacccom_rdreg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_cfg {
	struct {
		uint32_t rxsbaccreq_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg1 {
	struct {
		uint32_t rxsbaccreq_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbaccreq_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbaccreq_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbaccreq_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbaccreq_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbaccreq_rdreg1_dp:1; /* [22:22] */
		uint32_t rxsbaccreq_rdreg1_cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg2 {
	struct {
		uint32_t rxsbaccreq_rdreg2_addr:24; /* [23:0] */
		uint32_t rxsbaccreq_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg3 {
	struct {
		uint32_t rxsbaccreq_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbaccreq_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg4 {
	struct {
		uint32_t rxsbaccreq_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg5 {
	struct {
		uint32_t rxsbaccreq_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_cfg {
	struct {
		uint32_t rxsbmsg_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg1 {
	struct {
		uint32_t rxsbmsg_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbmsg_rdreg1_msgcode:8; /* [12:5] */
		uint32_t rxsbmsg_rdreg1_srcid:3; /* [15:13] */
		uint32_t rxsbmsg_rdreg1_dp:1; /* [16:16] */
		uint32_t rxsbmsg_rdreg1_cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg2 {
	struct {
		uint32_t rxsbmsg_rdreg2_msgsubcode:8; /* [7:0] */
		uint32_t rxsbmsg_rdreg2_msginfo:16; /* [23:8] */
		uint32_t rxsbmsg_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg3 {
	struct {
		uint32_t rxsbmsg_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbmsg_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg4 {
	struct {
		uint32_t rxsbmsg_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg5 {
	struct {
		uint32_t rxsbmsg_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_cfg {
	struct {
		uint32_t rxsbvmsg_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg1 {
	struct {
		uint32_t rxsbvmsg_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbvmsg_rdreg1_msgcode:8; /* [12:5] */
		uint32_t rxsbvmsg_rdreg1_srcid:3; /* [15:13] */
		uint32_t rxsbvmsg_rdreg1_dp:1; /* [16:16] */
		uint32_t rxsbvmsg_rdreg1_cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg2 {
	struct {
		uint32_t rxsbvmsg_rdreg2_msgsubcode:8; /* [7:0] */
		uint32_t rxsbvmsg_rdreg2_msginfo:16; /* [23:8] */
		uint32_t rxsbvmsg_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg3 {
	struct {
		uint32_t rxsbvmsg_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbvmsg_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg4 {
	struct {
		uint32_t rxsbvmsg_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg5 {
	struct {
		uint32_t rxsbvmsg_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_lp_config {
	struct {
		uint32_t rdi_lp_state_req:4; /* [3:0] */
		uint32_t rdi_lp_linkerror:1; /* [4:4] */
		uint32_t rdi_lp_stallack:1; /* [5:5] */
		uint32_t rdi_lp_clk_ack:1; /* [6:6] */
		uint32_t rdi_lp_wake_req:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_rdreg6 {
	struct {
		uint32_t rdi_pl_state_sts:4; /* [3:0] */
		uint32_t rdi_pl_inband_pres:1; /* [4:4] */
		uint32_t rdi_pl_error:1; /* [5:5] */
		uint32_t rdi_pl_cerror:1; /* [6:6] */
		uint32_t rdi_pl_nferror:1; /* [7:7] */
		uint32_t rdi_pl_trainerror:1; /* [8:8] */
		uint32_t rdi_pl_phyinrecenter:1; /* [9:9] */
		uint32_t rdi_pl_stallreq:1; /* [10:10] */
		uint32_t rdi_pl_speedmode:3; /* [13:11] */
		uint32_t rdi_pl_lnk_cfg:3; /* [16:14] */
		uint32_t rdi_pl_clk_req:1; /* [17:17] */
		uint32_t rdi_pl_wake_ack:1; /* [18:18] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1 {
	struct {
		uint32_t rdi_pl_inband_pres_int1:1; /* [0:0] */
		uint32_t rdi_pl_error_int1:1; /* [1:1] */
		uint32_t rdi_pl_cerror_int1:1; /* [2:2] */
		uint32_t rdi_pl_nferror_int1:1; /* [3:3] */
		uint32_t rdi_pl_trainerror_int1:1; /* [4:4] */
		uint32_t rdi_pl_phyinrecenter_int1:1; /* [5:5] */
		uint32_t rdi_pl_stallreq_int1:1; /* [6:6] */
		uint32_t rdi_pl_clk_req_int1:1; /* [7:7] */
		uint32_t rdi_pl_wake_ack_int1:1; /* [8:8] */
		uint32_t rdi_lp_state_req_diff_int1:1; /* [9:9] */
		uint32_t rdi_pl_state_sts_diff_int1:1; /* [10:10] */
		uint32_t retry_exhaust_crc24_int1:1; /* [11:11] */
		uint32_t retry_exhaust_jump_not_det_int1:1; /* [12:12] */
		uint32_t retry_last_good_not_det_int1:1; /* [13:13] */
		uint32_t retry_replay_scheduled_nak_int1:1; /* [14:14] */
		uint32_t retry_replay_scheduled_timeout_int1:1; /* [15:15] */
		uint32_t retry_tx_int_corr_source_int1:1; /* [16:16] */
		uint32_t retry_tx_int_uncorr_source_int1:1; /* [17:17] */
		uint32_t retry_tx_int_max_unack_met_int1:1; /* [18:18] */
		uint32_t retry_tx_int_buf_ovrflow_int1:1; /* [19:19] */
		uint32_t parity_err_cnt_reached_threshold_int1:1; /* [20:20] */
		uint32_t crc_err_cnt_reached_threshold_int1:1; /* [21:21] */
		uint32_t timeout_cntr_triggered_8ms_int1:1; /* [22:22] */
		uint32_t mailbox_response_rcvd_int1:1; /* [23:23] */
		uint32_t retry_replay_done_int1:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1_mask {
	struct {
		uint32_t rdi_pl_inband_pres_int1_mask:1; /* [0:0] */
		uint32_t rdi_pl_error_int1_mask:1; /* [1:1] */
		uint32_t rdi_pl_cerror_int1_mask:1; /* [2:2] */
		uint32_t rdi_pl_nferror_int1_mask:1; /* [3:3] */
		uint32_t rdi_pl_trainerror_int1_mask:1; /* [4:4] */
		uint32_t rdi_pl_phyinrecenter_int1_mask:1; /* [5:5] */
		uint32_t rdi_pl_stallreq_int1_mask:1; /* [6:6] */
		uint32_t rdi_pl_clk_req_int1_mask:1; /* [7:7] */
		uint32_t rdi_pl_wake_ack_int1_mask:1; /* [8:8] */
		uint32_t rdi_lp_state_req_diff_int1_mask:1; /* [9:9] */
		uint32_t rdi_pl_state_sts_diff_int1_mask:1; /* [10:10] */
		uint32_t retry_exhaust_crc24_int1_mask:1; /* [11:11] */
		uint32_t retry_exhaust_jump_not_det_int1_mask:1; /* [12:12] */
		uint32_t retry_last_good_not_det_int1_mask:1; /* [13:13] */
		uint32_t retry_replay_scheduled_nak_int1_mask:1; /* [14:14] */
		uint32_t retry_replay_scheduled_timeout_int1_mask:1; /* [15:15] */
		uint32_t retry_tx_int_corr_source_int1_mask:1; /* [16:16] */
		uint32_t retry_tx_int_uncorr_source_int1_mask:1; /* [17:17] */
		uint32_t retry_tx_int_max_unack_met_int1_mask:1; /* [18:18] */
		uint32_t retry_tx_int_buf_ovrflow_int1_mask:1; /* [19:19] */
		uint32_t parity_err_cnt_reached_threshold_int1_mask:1; /* [20:20] */
		uint32_t crc_err_cnt_reached_threshold_int1_mask:1; /* [21:21] */
		uint32_t timeout_cntr_triggered_8ms_int1_mask:1; /* [22:22] */
		uint32_t mailbox_response_rcvd_int1_mask:1; /* [23:23] */
		uint32_t retry_replay_done_int1_mask:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2 {
	struct {
		uint32_t rdi_pl_inband_pres_int2:1; /* [0:0] */
		uint32_t rdi_pl_error_int2:1; /* [1:1] */
		uint32_t rdi_pl_cerror_int2:1; /* [2:2] */
		uint32_t rdi_pl_nferror_int2:1; /* [3:3] */
		uint32_t rdi_pl_trainerror_int2:1; /* [4:4] */
		uint32_t rdi_pl_phyinrecenter_int2:1; /* [5:5] */
		uint32_t rdi_pl_stallreq_int2:1; /* [6:6] */
		uint32_t rdi_pl_clk_req_int2:1; /* [7:7] */
		uint32_t rdi_pl_wake_ack_int2:1; /* [8:8] */
		uint32_t rdi_lp_state_req_diff_int2:1; /* [9:9] */
		uint32_t rdi_pl_state_sts_diff_int2:1; /* [10:10] */
		uint32_t retry_exhaust_crc24_int2:1; /* [11:11] */
		uint32_t retry_exhaust_jump_not_det_int2:1; /* [12:12] */
		uint32_t retry_last_good_not_det_int2:1; /* [13:13] */
		uint32_t retry_replay_scheduled_nak_int2:1; /* [14:14] */
		uint32_t retry_replay_scheduled_timeout_int2:1; /* [15:15] */
		uint32_t retry_tx_int_corr_source_int2:1; /* [16:16] */
		uint32_t retry_tx_int_uncorr_source_int2:1; /* [17:17] */
		uint32_t retry_tx_int_max_unack_met_int2:1; /* [18:18] */
		uint32_t retry_tx_int_buf_ovrflow_int2:1; /* [19:19] */
		uint32_t parity_err_cnt_reached_threshold_int2:1; /* [20:20] */
		uint32_t crc_err_cnt_reached_threshold_int2:1; /* [21:21] */
		uint32_t timeout_cntr_triggered_8ms_int2:1; /* [22:22] */
		uint32_t mailbox_response_rcvd_int2:1; /* [23:23] */
		uint32_t retry_replay_done_int2:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2_mask {
	struct {
		uint32_t rdi_pl_inband_pres_int2_mask:1; /* [0:0] */
		uint32_t rdi_pl_error_int2_mask:1; /* [1:1] */
		uint32_t rdi_pl_cerror_int2_mask:1; /* [2:2] */
		uint32_t rdi_pl_nferror_int2_mask:1; /* [3:3] */
		uint32_t rdi_pl_trainerror_int2_mask:1; /* [4:4] */
		uint32_t rdi_pl_phyinrecenter_int2_mask:1; /* [5:5] */
		uint32_t rdi_pl_stallreq_int2_mask:1; /* [6:6] */
		uint32_t rdi_pl_clk_req_int2_mask:1; /* [7:7] */
		uint32_t rdi_pl_wake_ack_int2_mask:1; /* [8:8] */
		uint32_t rdi_lp_state_req_diff_int2_mask:1; /* [9:9] */
		uint32_t rdi_pl_state_sts_diff_int2_mask:1; /* [10:10] */
		uint32_t retry_exhaust_crc24_int2_mask:1; /* [11:11] */
		uint32_t retry_exhaust_jump_not_det_int2_mask:1; /* [12:12] */
		uint32_t retry_last_good_not_det_int2_mask:1; /* [13:13] */
		uint32_t retry_replay_scheduled_nak_int2_mask:1; /* [14:14] */
		uint32_t retry_replay_scheduled_timeout_int2_mask:1; /* [15:15] */
		uint32_t retry_tx_int_corr_source_int2_mask:1; /* [16:16] */
		uint32_t retry_tx_int_uncorr_source_int2_mask:1; /* [17:17] */
		uint32_t retry_tx_int_max_unack_met_int2_mask:1; /* [18:18] */
		uint32_t retry_tx_int_buf_ovrflow_int2_mask:1; /* [19:19] */
		uint32_t parity_err_cnt_reached_threshold_int2_mask:1; /* [20:20] */
		uint32_t crc_err_cnt_reached_threshold_int2_mask:1; /* [21:21] */
		uint32_t timeout_cntr_triggered_8ms_int2_mask:1; /* [22:22] */
		uint32_t mailbox_response_rcvd_int2_mask:1; /* [23:23] */
		uint32_t retry_replay_done_int2_mask:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_int2 {
	struct {
		uint32_t adpt_timeout_int2:1; /* [0:0] */
		uint32_t rcvr_overflow_int2:1; /* [1:1] */
		uint32_t internal_err_int2:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd_int2:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd_int2:1; /* [4:4] */
		uint32_t invld_param_exchange_int2:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_int2_mask {
	struct {
		uint32_t adpt_timeout_int2_mask:1; /* [0:0] */
		uint32_t rcvr_overflow_int2_mask:1; /* [1:1] */
		uint32_t internal_err_int2_mask:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd_int2_mask:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd_int2_mask:1; /* [4:4] */
		uint32_t invld_param_exchange_int2_mask:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_stat_int2 {
	struct {
		uint32_t crc_err_detected_int2:1; /* [0:0] */
		uint32_t adpt_lsm_trans_retrain_int2:1; /* [1:1] */
		uint32_t corr_internal_err_int2:1; /* [2:2] */
		uint32_t sb_corr_err_msg_rcvd_int2:1; /* [3:3] */
		uint32_t run_time_link_testing_parity_err_int2:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_int2_mask {
	struct {
		uint32_t crc_err_detected_int2_mask:1; /* [0:0] */
		uint32_t adpt_lsm_trns_to_retrain_int2_mask:1; /* [1:1] */
		uint32_t corr_internal_err_int2_mask:1; /* [2:2] */
		uint32_t device_corr_err_msg_recv_int2_mask:1; /* [3:3] */
		uint32_t runtime_link_tstng_parity_err_int2_mask:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg1_w {
	struct {
		uint32_t vndr_id_w:16; /* [15:0] */
		uint32_t vndr_id_reg_block_w:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg2_w {
	struct {
		uint32_t vndr_reg_block_version_w:4; /* [3:0] */
		uint32_t adpt_timeout_encoding_w:4; /* [7:4] */
		uint32_t rcvr_ovf_encoding_w:3; /* [10:8] */
		uint32_t adpt_lsm_resp_type_w:3; /* [13:11] */
		uint32_t adpt_lsm_id_w:1; /* [14:14] */
		uint32_t param_exchange_successful_w:1; /* [15:15] */
		uint32_t flit_format_w:4; /* [19:16] */
		uint32_t first_fatal_err_indicator_w:5; /* [24:20] */
		uint32_t parity_feature_nak_rcvd_w:1; /* [25:25] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg3_w {
	struct {
		uint32_t vndr_reg_block_length_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_w {
	struct {
		uint32_t adpt_timeout_w:1; /* [0:0] */
		uint32_t rcvr_overflow_w:1; /* [1:1] */
		uint32_t internal_err_w:1; /* [2:2] */
		uint32_t sb_fatal_err_msg_rcvd_w:1; /* [3:3] */
		uint32_t sb_nonfatal_err_msg_rcvd_w:1; /* [4:4] */
		uint32_t invld_param_exchange_w:1; /* [5:5] */
		uint32_t crc_err_detected_w:1; /* [6:6] */
		uint32_t adpt_lsm_trans_retrain_w:1; /* [7:7] */
		uint32_t corr_internal_err_w:1; /* [8:8] */
		uint32_t sb_corr_err_msg_rcvd_w:1; /* [9:9] */
		uint32_t run_time_link_testing_parity_err_w:1; /* [10:10] */
		uint32_t compliance_sts_w:1; /* [11:11] */
		uint32_t lstate_req_inj_sts_for_stack0_w:1; /* [12:12] */
		uint32_t lstate_resp_inj_sts_for_stack0_w:1; /* [13:13] */
		uint32_t lstate_reqt_inj_sts_for_stack1_w:1; /* [14:14] */
		uint32_t lstate_resp_inj_sts_for_stack1_w:1; /* [15:15] */
		uint32_t retry_inj_sts_w:2; /* [17:16] */
		uint32_t num_of_retries_exceeded_th_w:1; /* [18:18] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_1_w {
	struct {
		uint32_t hdr_log1_reg0_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_2_w {
	struct {
		uint32_t hdr_log1_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1_w {
	struct {
		uint32_t parity_log_reg1_mod1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2_w {
	struct {
		uint32_t parity_log_reg2_mod1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1_w {
	struct {
		uint32_t parity_log_reg1_mod2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2_w {
	struct {
		uint32_t parity_log_reg2_mod2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1_w {
	struct {
		uint32_t parity_log_reg1_mod3_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2_w {
	struct {
		uint32_t parity_log_reg2_mod3_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log1_w {
	struct {
		uint32_t adv_adpt_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log2_w {
	struct {
		uint32_t adv_adpt_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log1_w {
	struct {
		uint32_t fin_adpt_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log2_w {
	struct {
		uint32_t fin_adpt_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log1_w {
	struct {
		uint32_t adv_cxl_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log2_w {
	struct {
		uint32_t adv_cxl_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log1_w {
	struct {
		uint32_t fin_cxl_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log2_w {
	struct {
		uint32_t fin_cxl_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log1_w {
	struct {
		uint32_t adv_multi_prtcl_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log2_w {
	struct {
		uint32_t adv_multi_prtcl_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log1_w {
	struct {
		uint32_t fin_multi_prtcl_cap_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log2_w {
	struct {
		uint32_t fin_multi_prtcl_cap_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1_w {
	struct {
		uint32_t adv_cxl_cap_stack1_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2_w {
	struct {
		uint32_t adv_cxl_cap_stack1_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1_w {
	struct {
		uint32_t fin_cxl_cap_stack1_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2_w {
	struct {
		uint32_t fin_cxl_cap_stack1_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg1 {
	struct {
		uint32_t tx_rt_enable:1; /* [0:0] */
		uint32_t tx_rt_nfe_rule:1; /* [1:1] */
		uint32_t tx_rt_buff_wm_high:7; /* [8:2] */
		uint32_t tx_rt_rtfc:9; /* [17:9] */
		uint32_t tx_rt_burst_seq_inr:6; /* [23:18] */
		uint32_t tx_user_seg_en:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg2 {
	struct {
		uint32_t tx_rt_burst_seq_num_bits:4; /* [3:0] */
		uint32_t tx_rt_enable_nop:1; /* [4:4] */
		uint32_t tx_rt_nop_spacing:3; /* [7:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg1 {
	struct {
		uint32_t rx_rt_enable:1; /* [0:0] */
		uint32_t rx_rt_burst_seq_inr:6; /* [6:1] */
		uint32_t rx_rt_burst_seq_num_bits:4; /* [10:7] */
		uint32_t rx_rt_ignore_crc24_delay:11; /* [21:11] */
		uint32_t rx_rt_max_unacknowledged_flits:10; /* [31:22] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg2 {
	struct {
		uint32_t rx_rt_jump_detect_timeout:16; /* [15:0] */
		uint32_t rx_user_seg_en:8; /* [23:16] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg3 {
	struct {
		uint32_t rx_rt_retry_count:2; /* [1:0] */
		uint32_t rx_rt_last_good_det_timeout:24; /* [25:2] */
		uint32_t rx_cfg_mult_ch:1; /* [26:26] */
		uint32_t sle_data_rate_is_32g_or_less:1; /* [27:27] */
		uint32_t sle_data_rate_is_64g:1; /* [28:28] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg4 {
	struct {
		uint32_t rx_rt_snh_timeout:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_static_counter_cfg {
	struct {
		uint32_t parity_sys_tick:1; /* [0:0] */
		uint32_t parity_counter_mode:1; /* [1:1] */
		uint32_t parity_force_clear:1; /* [2:2] */
		uint32_t parity_count_load:1; /* [3:3] */
		uint32_t crc_sys_tick:1; /* [4:4] */
		uint32_t crc_counter_mode:1; /* [5:5] */
		uint32_t crc_force_clear:1; /* [6:6] */
		uint32_t crc_count_load:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0 {
	struct {
		uint32_t crc_err_log_reg0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1 {
	struct {
		uint32_t crc_err_log_reg1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_parity_err_count_threshold_reg {
	struct {
		uint32_t parity_error_count_threshold; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_count_threshold_reg {
	struct {
		uint32_t crc_error_count_threshold; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config1_reg {
	struct {
		uint32_t timeout_cntr_en:1; /* [0:0] */
		uint32_t timeout_cntr_start:1; /* [1:1] */
		uint32_t timeout_cntr_stall:1; /* [2:2] */
		uint32_t timeout_cntr_stop:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config2_reg {
	struct {
		uint32_t timeout_cntr_no_cycles_for_8ms; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_rdi_reg_adapter_impsp_sts1_reg {
	struct {
		uint32_t crc_injection_done:1; /* [0:0] */
		uint32_t mailbox_tx_sb_tag:5; /* [5:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg1 {
	struct {
		uint32_t txsb_cfg1_opcode:5; /* [4:0] */
		uint32_t txsb_cfg1_ep:1; /* [5:5] */
		uint32_t txsb_cfg1_be:8; /* [13:6] */
		uint32_t txsb_cfg1_tag:5; /* [18:14] */
		uint32_t txsb_cfg1_srcid:3; /* [21:19] */
		uint32_t txsb_cfg1_type:3; /* [24:22] */
		uint32_t txsb_cfg1_status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg2 {
	struct {
		uint32_t txsb_cfg2_addr:24; /* [23:0] */
		uint32_t txsb_cfg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg3 {
	struct {
		uint32_t txsb_cfg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg4 {
	struct {
		uint32_t txsb_cfg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg5 {
	struct {
		uint32_t txsb_cfg7_execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_stall_rdreg1 {
	struct {
		uint32_t txsb_stall_rdreg1_accreq_wr_ok:1; /* [0:0] */
		uint32_t txsb_stall_rdreg1_acccom_wr_ok:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_cfg {
	struct {
		uint32_t rxsbacccom_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg1 {
	struct {
		uint32_t rxsbacccom_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbacccom_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbacccom_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbacccom_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbacccom_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbacccom_rdreg1_status:3; /* [24:22] */
		uint32_t rxsbacccom_rdreg1_dstid:3; /* [27:25] */
		uint32_t rxsbacccom_rdreg1_dp:1; /* [28:28] */
		uint32_t rxsbacccom_rdreg1_cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg2 {
	struct {
		uint32_t rxsbacccom_rdreg2_avail:1; /* [0:0] */
		uint32_t rxsbacccom_rdreg2_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg3 {
	struct {
		uint32_t rxsbacccom_rdreg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg4 {
	struct {
		uint32_t rxsbacccom_rdreg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_cfg {
	struct {
		uint32_t rxsbaccreq_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg1 {
	struct {
		uint32_t rxsbaccreq_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbaccreq_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbaccreq_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbaccreq_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbaccreq_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbaccreq_rdreg1_dp:1; /* [22:22] */
		uint32_t rxsbaccreq_rdreg1_cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg2 {
	struct {
		uint32_t rxsbaccreq_rdreg2_addr:24; /* [23:0] */
		uint32_t rxsbaccreq_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg3 {
	struct {
		uint32_t rxsbaccreq_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbaccreq_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg4 {
	struct {
		uint32_t rxsbaccreq_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg5 {
	struct {
		uint32_t rxsbaccreq_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1:1; /* [11:11] */
		uint32_t rxsb_accreq_avail_int1:1; /* [12:12] */
		uint32_t rxsb_accreq_rdready_int1:1; /* [13:13] */
		uint32_t rxsb_acccom_avail_int1:1; /* [14:14] */
		uint32_t rxsb_acccom_rdready_int1:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1_mask:1; /* [11:11] */
		uint32_t rxsb_accreq_avail_int1_mask:1; /* [12:12] */
		uint32_t rxsb_accreq_rdready_int1_mask:1; /* [13:13] */
		uint32_t rxsb_acccom_avail_int1_mask:1; /* [14:14] */
		uint32_t rxsb_acccom_rdready_int1_mask:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2:1; /* [11:11] */
		uint32_t rxsb_accreq_avail_int2:1; /* [12:12] */
		uint32_t rxsb_accreq_rdready_int2:1; /* [13:13] */
		uint32_t rxsb_acccom_avail_int2:1; /* [14:14] */
		uint32_t rxsb_acccom_rdready_int2:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2_mask:1; /* [11:11] */
		uint32_t rxsb_accreq_avail_int2_mask:1; /* [12:12] */
		uint32_t rxsb_accreq_rdready_int2_mask:1; /* [13:13] */
		uint32_t rxsb_acccom_avail_int2_mask:1; /* [14:14] */
		uint32_t rxsb_acccom_rdready_int2_mask:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg1 {
	struct {
		uint32_t fdi_pl_stream:8; /* [7:0] */
		uint32_t fdi_pl_state_sts:4; /* [11:8] */
		uint32_t fdi_pl_inband_pres:1; /* [12:12] */
		uint32_t fdi_pl_clk_req:1; /* [13:13] */
		uint32_t fdi_pl_wake_ack:1; /* [14:14] */
		uint32_t fdi_pl_protocol:3; /* [17:15] */
		uint32_t fdi_pl_protocol_flitfmt:4; /* [21:18] */
		uint32_t fdi_pl_protocol_vld:1; /* [22:22] */
		uint32_t fdi_pl_phyinrecenter:1; /* [23:23] */
		uint32_t fdi_pl_phyinl1:1; /* [24:24] */
		uint32_t fdi_pl_phyinl2:1; /* [25:25] */
		uint32_t fdi_pl_speedmode:3; /* [28:26] */
		uint32_t fdi_pl_lnk_cfg:3; /* [31:29] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg2 {
	struct {
		uint32_t fdi_pl_stallreq:1; /* [0:0] */
		uint32_t fdi_pl_error:1; /* [1:1] */
		uint32_t fdi_pl_cerror:1; /* [2:2] */
		uint32_t fdi_pl_nferror:1; /* [3:3] */
		uint32_t fdi_pl_trainerror:1; /* [4:4] */
		uint32_t fdi_pl_rx_active_req:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_rdreg {
	struct {
		uint32_t fdi_lp_stream:8; /* [7:0] */
		uint32_t fdi_lp_state_req:4; /* [11:8] */
		uint32_t fdi_lp_linkerror:1; /* [12:12] */
		uint32_t fdi_lp_rx_active_sts:1; /* [13:13] */
		uint32_t fdi_lp_stallack:1; /* [14:14] */
		uint32_t fdi_lp_clk_ack:1; /* [15:15] */
		uint32_t fdi_lp_wake_req:1; /* [16:16] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_reg {
	struct {
		uint32_t fdi_lp_linkerror_int1:1; /* [0:0] */
		uint32_t fdi_lp_rx_active_sts_int1:1; /* [1:1] */
		uint32_t fdi_lp_stallack_int1:1; /* [2:2] */
		uint32_t fdi_lp_clk_ack_int1:1; /* [3:3] */
		uint32_t fdi_lp_wake_req_int1:1; /* [4:4] */
		uint32_t fdi_lp_state_req_diff_int1:1; /* [5:5] */
		uint32_t fdi_pl_state_sts_diff_int1:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_mask_reg {
	struct {
		uint32_t fdi_lp_linkerror_int1_mask:1; /* [0:0] */
		uint32_t fdi_lp_rx_active_sts_int1_mask:1; /* [1:1] */
		uint32_t fdi_lp_stallack_int1_mask:1; /* [2:2] */
		uint32_t fdi_lp_clk_ack_int1_mask:1; /* [3:3] */
		uint32_t fdi_lp_wake_req_int1_mask:1; /* [4:4] */
		uint32_t fdi_lp_state_req_diff_int1_mask:1; /* [5:5] */
		uint32_t fdi_pl_state_sts_diff_int1_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_reg {
	struct {
		uint32_t fdi_lp_linkerror_int2:1; /* [0:0] */
		uint32_t fdi_lp_rx_active_sts_int2:1; /* [1:1] */
		uint32_t fdi_lp_stallack_int2:1; /* [2:2] */
		uint32_t fdi_lp_clk_ack_int2:1; /* [3:3] */
		uint32_t fdi_lp_wake_req_int2:1; /* [4:4] */
		uint32_t fdi_lp_state_req_diff_int2:1; /* [5:5] */
		uint32_t fdi_pl_state_sts_diff_int2:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_mask_reg {
	struct {
		uint32_t fdi_lp_linkerror_int2_mask:1; /* [0:0] */
		uint32_t fdi_lp_rx_active_sts_int2_mask:1; /* [1:1] */
		uint32_t fdi_lp_stallack_int2_mask:1; /* [2:2] */
		uint32_t fdi_lp_clk_ack_int2_mask:1; /* [3:3] */
		uint32_t fdi_lp_wake_req_int2_mask:1; /* [4:4] */
		uint32_t fdi_lp_state_req_diff_int2_mask:1; /* [5:5] */
		uint32_t fdi_pl_state_sts_diff_int2_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1 {
	struct {
		uint32_t vndr_id:16; /* [15:0] */
		uint32_t vndr_id_reg_blk:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2 {
	struct {
		uint32_t vndr_reg_blk_version:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3 {
	struct {
		uint32_t vndr_reg_blk_length; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4 {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg1 {
	struct {
		uint32_t txsb_cfg1_opcode:5; /* [4:0] */
		uint32_t txsb_cfg1_ep:1; /* [5:5] */
		uint32_t txsb_cfg1_be:8; /* [13:6] */
		uint32_t txsb_cfg1_tag:5; /* [18:14] */
		uint32_t txsb_cfg1_srcid:3; /* [21:19] */
		uint32_t txsb_cfg1_type:3; /* [24:22] */
		uint32_t txsb_cfg1_status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg2 {
	struct {
		uint32_t txsb_cfg2_addr:24; /* [23:0] */
		uint32_t txsb_cfg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg3 {
	struct {
		uint32_t txsb_cfg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg4 {
	struct {
		uint32_t txsb_cfg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg5 {
	struct {
		uint32_t txsb_cfg5_msgsubcode:8; /* [7:0] */
		uint32_t txsb_cfg5_msginfo:16; /* [23:8] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg6 {
	struct {
		uint32_t txsb_cfg6_msgcode:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg7 {
	struct {
		uint32_t txsb_cfg7_execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_stall_rdreg1 {
	struct {
		uint32_t txsb_stall_rdreg1_accreq_wr_ok:1; /* [0:0] */
		uint32_t txsb_stall_rdreg1_acccom_wr_ok:1; /* [1:1] */
		uint32_t txsb_stall_rdreg1_msg_wr_ok:1; /* [2:2] */
		uint32_t txsb_stall_rdreg1_vmsg_wr_ok:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_cfg {
	struct {
		uint32_t rxsbacccom_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg1 {
	struct {
		uint32_t rxsbacccom_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbacccom_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbacccom_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbacccom_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbacccom_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbacccom_rdreg1_status:3; /* [24:22] */
		uint32_t rxsbacccom_rdreg1_dstid:3; /* [27:25] */
		uint32_t rxsbacccom_rdreg1_dp:1; /* [28:28] */
		uint32_t rxsbacccom_rdreg1_cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg2 {
	struct {
		uint32_t rxsbacccom_rdreg2_avail:1; /* [0:0] */
		uint32_t rxsbacccom_rdreg2_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg3 {
	struct {
		uint32_t rxsbacccom_rdreg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg4 {
	struct {
		uint32_t rxsbacccom_rdreg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_cfg {
	struct {
		uint32_t rxsbaccreq_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg1 {
	struct {
		uint32_t rxsbaccreq_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbaccreq_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbaccreq_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbaccreq_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbaccreq_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbaccreq_rdreg1_dp:1; /* [22:22] */
		uint32_t rxsbaccreq_rdreg1_cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg2 {
	struct {
		uint32_t rxsbaccreq_rdreg2_addr:24; /* [23:0] */
		uint32_t rxsbaccreq_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg3 {
	struct {
		uint32_t rxsbaccreq_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbaccreq_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg4 {
	struct {
		uint32_t rxsbaccreq_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg5 {
	struct {
		uint32_t rxsbaccreq_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_cfg {
	struct {
		uint32_t rxsbmsg_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg1 {
	struct {
		uint32_t rxsbmsg_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbmsg_rdreg1_msgcode:8; /* [12:5] */
		uint32_t rxsbmsg_rdreg1_srcid:3; /* [15:13] */
		uint32_t rxsbmsg_rdreg1_dp:1; /* [16:16] */
		uint32_t rxsbmsg_rdreg1_cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg2 {
	struct {
		uint32_t rxsbmsg_rdreg2_msgsubcode:8; /* [7:0] */
		uint32_t rxsbmsg_rdreg2_msginfo:16; /* [23:8] */
		uint32_t rxsbmsg_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg3 {
	struct {
		uint32_t rxsbmsg_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbmsg_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg4 {
	struct {
		uint32_t rxsbmsg_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg5 {
	struct {
		uint32_t rxsbmsg_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_cfg {
	struct {
		uint32_t rxsbvmsg_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg1 {
	struct {
		uint32_t rxsbvmsg_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbvmsg_rdreg1_msgcode:8; /* [12:5] */
		uint32_t rxsbvmsg_rdreg1_srcid:3; /* [15:13] */
		uint32_t rxsbvmsg_rdreg1_dp:1; /* [16:16] */
		uint32_t rxsbvmsg_rdreg1_cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg2 {
	struct {
		uint32_t rxsbvmsg_rdreg2_msgsubcode:8; /* [7:0] */
		uint32_t rxsbvmsg_rdreg2_msginfo:16; /* [23:8] */
		uint32_t rxsbvmsg_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg3 {
	struct {
		uint32_t rxsbvmsg_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbvmsg_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg4 {
	struct {
		uint32_t rxsbvmsg_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg5 {
	struct {
		uint32_t rxsbvmsg_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_lp_rdreg {
	struct {
		uint32_t rdi_lp_state_req:4; /* [3:0] */
		uint32_t rdi_lp_linkerror:1; /* [4:4] */
		uint32_t rdi_lp_stallack:1; /* [5:5] */
		uint32_t rdi_lp_clk_ack:1; /* [6:6] */
		uint32_t rdi_lp_wake_req:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_phy_rdi_pl_cfg1 {
	struct {
		uint32_t rdi_pl_state_sts:4; /* [3:0] */
		uint32_t rdi_pl_inband_pres:1; /* [4:4] */
		uint32_t rdi_pl_clk_req:1; /* [5:5] */
		uint32_t rdi_pl_wake_ack:1; /* [6:6] */
		uint32_t rdi_pl_phyinrecenter:1; /* [7:7] */
		uint32_t rdi_pl_speedmode:3; /* [10:8] */
		uint32_t rdi_pl_lnk_cfg:3; /* [13:11] */
		uint32_t rdi_pl_stallreq:1; /* [14:14] */
		uint32_t rdi_pl_error:1; /* [15:15] */
		uint32_t rdi_pl_cerror:1; /* [16:16] */
		uint32_t rdi_pl_nferror:1; /* [17:17] */
		uint32_t rdi_pl_trainerror:1; /* [18:18] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log0_w {
	struct {
		uint32_t m0_state_n_w:8; /* [7:0] */
		uint32_t m0_lane_rev_w:1; /* [8:8] */
		uint32_t m0_width_deg_w:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m0_state_n1_w:8; /* [23:16] */
		uint32_t m0_state_n2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log0_w {
	struct {
		uint32_t m1_state_n_w:8; /* [7:0] */
		uint32_t m1_lane_rev_w:1; /* [8:8] */
		uint32_t m1_width_deg_w:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m1_state_n1_w:8; /* [23:16] */
		uint32_t m1_state_n2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log0_w {
	struct {
		uint32_t m2_state_n_w:8; /* [7:0] */
		uint32_t m2_lane_rev_w:1; /* [8:8] */
		uint32_t m2_width_deg_w:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m2_state_n1_w:8; /* [23:16] */
		uint32_t m2_state_n2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log0_w {
	struct {
		uint32_t m3_state_n_w:8; /* [7:0] */
		uint32_t m3_lane_rev_w:1; /* [8:8] */
		uint32_t m3_width_deg_w:1; /* [9:9] */
		uint32_t reserved_bit_0:6;
		uint32_t m3_state_n1_w:8; /* [23:16] */
		uint32_t m3_state_n2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log1_w {
	struct {
		uint32_t m0_state_n3_w:8; /* [7:0] */
		uint32_t m0_state_time_out_w:1; /* [8:8] */
		uint32_t m0_sb_time_out_w:1; /* [9:9] */
		uint32_t m0_remote_link_err_w:1; /* [10:10] */
		uint32_t m0_internal_err_w:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log1_w {
	struct {
		uint32_t m1_state_n3_w:8; /* [7:0] */
		uint32_t m1_state_time_out_w:1; /* [8:8] */
		uint32_t m1_sb_time_out_w:1; /* [9:9] */
		uint32_t m1_remote_link_err_w:1; /* [10:10] */
		uint32_t m1_internal_err_w:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log1_w {
	struct {
		uint32_t m2_state_n3_w:8; /* [7:0] */
		uint32_t m2_state_time_out_w:1; /* [8:8] */
		uint32_t m2_sb_time_out_w:1; /* [9:9] */
		uint32_t m2_remote_link_err_w:1; /* [10:10] */
		uint32_t m2_internal_err_w:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log1_w {
	struct {
		uint32_t m3_state_n3_w:8; /* [7:0] */
		uint32_t m3_state_time_out_w:1; /* [8:8] */
		uint32_t m3_sb_time_out_w:1; /* [9:9] */
		uint32_t m3_remote_link_err_w:1; /* [10:10] */
		uint32_t m3_internal_err_w:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1_w {
	struct {
		uint32_t busy_w:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg1_w {
	struct {
		uint32_t m0_repair_addr_trd_p0_w:8; /* [7:0] */
		uint32_t m0_repair_addr_trd_p1_w:8; /* [15:8] */
		uint32_t m0_repair_addr_trd_p2_w:8; /* [23:16] */
		uint32_t m0_repair_addr_trd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg2_w {
	struct {
		uint32_t m0_repair_addr_rrd_p0_w:8; /* [7:0] */
		uint32_t m0_repair_addr_rrd_p1_w:8; /* [15:8] */
		uint32_t m0_repair_addr_rrd_p2_w:8; /* [23:16] */
		uint32_t m0_repair_addr_rrd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg1_w {
	struct {
		uint32_t m1_repair_addr_trd_p0_w:8; /* [7:0] */
		uint32_t m1_repair_addr_trd_p1_w:8; /* [15:8] */
		uint32_t m1_repair_addr_trd_p2_w:8; /* [23:16] */
		uint32_t m1_repair_addr_trd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg2_w {
	struct {
		uint32_t m1_repair_addr_rrd_p0_w:8; /* [7:0] */
		uint32_t m1_repair_addr_rrd_p1_w:8; /* [15:8] */
		uint32_t m1_repair_addr_rrd_p2_w:8; /* [23:16] */
		uint32_t m1_repair_addr_rrd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg1_w {
	struct {
		uint32_t m2_repair_addr_trd_p0_w:8; /* [7:0] */
		uint32_t m2_repair_addr_trd_p1_w:8; /* [15:8] */
		uint32_t m2_repair_addr_trd_p2_w:8; /* [23:16] */
		uint32_t m2_repair_addr_trd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg2_w {
	struct {
		uint32_t m2_repair_addr_rrd_p0_w:8; /* [7:0] */
		uint32_t m2_repair_addr_rrd_p1_w:8; /* [15:8] */
		uint32_t m2_repair_addr_rrd_p2_w:8; /* [23:16] */
		uint32_t m2_repair_addr_rrd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg1_w {
	struct {
		uint32_t m3_repair_addr_trd_p0_w:8; /* [7:0] */
		uint32_t m3_repair_addr_trd_p1_w:8; /* [15:8] */
		uint32_t m3_repair_addr_trd_p2_w:8; /* [23:16] */
		uint32_t m3_repair_addr_trd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg2_w {
	struct {
		uint32_t m3_repair_addr_rrd_p0_w:8; /* [7:0] */
		uint32_t m3_repair_addr_rrd_p1_w:8; /* [15:8] */
		uint32_t m3_repair_addr_rrd_p2_w:8; /* [23:16] */
		uint32_t m3_repair_addr_rrd_p3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair_w {
	struct {
		uint32_t m0_repair_addr_trdck_p_w:4; /* [3:0] */
		uint32_t m0_repair_addr_rrdck_p_w:4; /* [7:4] */
		uint32_t m0_repair_addr_trdvld_p_w:2; /* [9:8] */
		uint32_t m0_repair_addr_rrdvld_p_w:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m0_repair_addr_sb_tx_w:4; /* [19:16] */
		uint32_t m0_repair_addr_sb_rx_w:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair_w {
	struct {
		uint32_t m1_repair_addr_trdck_p_w:4; /* [3:0] */
		uint32_t m1_repair_addr_rrdck_p_w:4; /* [7:4] */
		uint32_t m1_repair_addr_trdvld_p_w:2; /* [9:8] */
		uint32_t m1_repair_addr_rrdvld_p_w:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m1_repair_addr_sb_tx_w:4; /* [19:16] */
		uint32_t m1_repair_addr_sb_rx_w:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair_w {
	struct {
		uint32_t m2_repair_addr_trdck_p_w:4; /* [3:0] */
		uint32_t m2_repair_addr_rrdck_p_w:4; /* [7:4] */
		uint32_t m2_repair_addr_trdvld_p_w:2; /* [9:8] */
		uint32_t m2_repair_addr_rrdvld_p_w:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m2_repair_addr_sb_tx_w:4; /* [19:16] */
		uint32_t m2_repair_addr_sb_rx_w:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair_w {
	struct {
		uint32_t m3_repair_addr_trdck_p_w:4; /* [3:0] */
		uint32_t m3_repair_addr_rrdck_p_w:4; /* [7:4] */
		uint32_t m3_repair_addr_trdvld_p_w:2; /* [9:8] */
		uint32_t m3_repair_addr_rrdvld_p_w:2; /* [11:10] */
		uint32_t reserved_bit_0:4;
		uint32_t m3_repair_addr_sb_tx_w:4; /* [19:16] */
		uint32_t m3_repair_addr_sb_rx_w:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_pcie_extnd_cap_hdr_w {
	struct {
		uint32_t extnd_cap_hdr_cap_id_w:16; /* [15:0] */
		uint32_t extnd_cap_hdr_revision_id_w:4; /* [19:16] */
		uint32_t extnd_cap_hdr_next_cap_offset_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr1_w {
	struct {
		uint32_t dvsec_hdr1_vendor_id_w:16; /* [15:0] */
		uint32_t dvsec_hdr1_revision_w:4; /* [19:16] */
		uint32_t dvsec_hdr1_length_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr2_w {
	struct {
		uint32_t dvsec_hdr2_dvsec_id_w:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_uhm_status_w {
	struct {
		uint32_t reserved_bit_0:16;
		uint32_t step_cnt_w:8; /* [23:16] */
		uint32_t status_emv_w:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0_w {
	struct {
		uint32_t phy_eml_ln0_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln0_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln1_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln1_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0_w {
	struct {
		uint32_t phy_eml_ln2_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln2_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln3_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln3_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0_w {
	struct {
		uint32_t phy_eml_ln4_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln4_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln5_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln5_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0_w {
	struct {
		uint32_t phy_eml_ln6_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln6_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln7_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln7_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0_w {
	struct {
		uint32_t phy_eml_ln8_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln8_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln9_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln9_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0_w {
	struct {
		uint32_t phy_eml_ln10_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln10_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln11_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln11_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0_w {
	struct {
		uint32_t phy_eml_ln12_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln12_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln13_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln13_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0_w {
	struct {
		uint32_t phy_eml_ln14_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln14_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln15_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln15_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0_w {
	struct {
		uint32_t phy_eml_ln16_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln16_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln17_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln17_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0_w {
	struct {
		uint32_t phy_eml_ln18_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln18_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln19_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln19_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0_w {
	struct {
		uint32_t phy_eml_ln20_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln20_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln21_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln21_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0_w {
	struct {
		uint32_t phy_eml_ln22_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln22_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln23_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln23_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0_w {
	struct {
		uint32_t phy_eml_ln24_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln24_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln25_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln25_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0_w {
	struct {
		uint32_t phy_eml_ln26_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln26_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln27_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln27_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0_w {
	struct {
		uint32_t phy_eml_ln28_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln28_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln29_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln29_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0_w {
	struct {
		uint32_t phy_eml_ln30_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln30_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln31_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln31_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0_w {
	struct {
		uint32_t phy_eml_ln32_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln32_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln33_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln33_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0_w {
	struct {
		uint32_t phy_eml_ln34_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln34_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln35_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln35_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0_w {
	struct {
		uint32_t phy_eml_ln36_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln36_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln37_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln37_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0_w {
	struct {
		uint32_t phy_eml_ln38_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln38_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln39_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln39_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0_w {
	struct {
		uint32_t phy_eml_ln40_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln40_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln41_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln41_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0_w {
	struct {
		uint32_t phy_eml_ln42_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln42_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln43_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln43_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0_w {
	struct {
		uint32_t phy_eml_ln44_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln44_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln45_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln45_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0_w {
	struct {
		uint32_t phy_eml_ln46_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln46_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln47_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln47_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0_w {
	struct {
		uint32_t phy_eml_ln48_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln48_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln49_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln49_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0_w {
	struct {
		uint32_t phy_eml_ln50_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln50_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln51_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln51_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0_w {
	struct {
		uint32_t phy_eml_ln52_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln52_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln53_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln53_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0_w {
	struct {
		uint32_t phy_eml_ln54_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln54_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln55_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln55_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0_w {
	struct {
		uint32_t phy_eml_ln56_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln56_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln57_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln57_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0_w {
	struct {
		uint32_t phy_eml_ln58_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln58_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln59_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln59_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0_w {
	struct {
		uint32_t phy_eml_ln60_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln60_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln61_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln61_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0_w {
	struct {
		uint32_t phy_eml_ln62_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln62_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln63_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln63_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0_w {
	struct {
		uint32_t phy_eml_ln64_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln64_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln65_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln65_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0_w {
	struct {
		uint32_t phy_eml_ln66_m0_w:8; /* [7:0] */
		uint32_t phy_emr_ln66_m0_w:8; /* [15:8] */
		uint32_t phy_eml_ln67_m0_w:8; /* [23:16] */
		uint32_t phy_emr_ln67_m0_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1_w {
	struct {
		uint32_t phy_eml_ln0_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln0_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln1_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln1_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1_w {
	struct {
		uint32_t phy_eml_ln2_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln2_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln3_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln3_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1_w {
	struct {
		uint32_t phy_eml_ln4_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln4_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln5_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln5_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1_w {
	struct {
		uint32_t phy_eml_ln6_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln6_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln7_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln7_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1_w {
	struct {
		uint32_t phy_eml_ln8_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln8_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln9_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln9_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1_w {
	struct {
		uint32_t phy_eml_ln10_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln10_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln11_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln11_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1_w {
	struct {
		uint32_t phy_eml_ln12_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln12_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln13_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln13_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1_w {
	struct {
		uint32_t phy_eml_ln14_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln14_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln15_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln15_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1_w {
	struct {
		uint32_t phy_eml_ln16_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln16_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln17_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln17_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1_w {
	struct {
		uint32_t phy_eml_ln18_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln18_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln19_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln19_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1_w {
	struct {
		uint32_t phy_eml_ln20_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln20_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln21_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln21_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1_w {
	struct {
		uint32_t phy_eml_ln22_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln22_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln23_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln23_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1_w {
	struct {
		uint32_t phy_eml_ln24_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln24_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln25_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln25_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1_w {
	struct {
		uint32_t phy_eml_ln26_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln26_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln27_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln27_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1_w {
	struct {
		uint32_t phy_eml_ln28_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln28_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln29_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln29_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1_w {
	struct {
		uint32_t phy_eml_ln30_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln30_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln31_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln31_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1_w {
	struct {
		uint32_t phy_eml_ln32_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln32_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln33_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln33_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1_w {
	struct {
		uint32_t phy_eml_ln34_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln34_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln35_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln35_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1_w {
	struct {
		uint32_t phy_eml_ln36_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln36_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln37_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln37_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1_w {
	struct {
		uint32_t phy_eml_ln38_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln38_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln39_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln39_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1_w {
	struct {
		uint32_t phy_eml_ln40_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln40_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln41_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln41_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1_w {
	struct {
		uint32_t phy_eml_ln42_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln42_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln43_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln43_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1_w {
	struct {
		uint32_t phy_eml_ln44_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln44_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln45_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln45_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1_w {
	struct {
		uint32_t phy_eml_ln46_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln46_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln47_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln47_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1_w {
	struct {
		uint32_t phy_eml_ln48_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln48_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln49_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln49_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1_w {
	struct {
		uint32_t phy_eml_ln50_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln50_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln51_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln51_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1_w {
	struct {
		uint32_t phy_eml_ln52_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln52_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln53_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln53_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1_w {
	struct {
		uint32_t phy_eml_ln54_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln54_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln55_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln55_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1_w {
	struct {
		uint32_t phy_eml_ln56_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln56_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln57_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln57_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1_w {
	struct {
		uint32_t phy_eml_ln58_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln58_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln59_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln59_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1_w {
	struct {
		uint32_t phy_eml_ln60_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln60_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln61_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln61_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1_w {
	struct {
		uint32_t phy_eml_ln62_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln62_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln63_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln63_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1_w {
	struct {
		uint32_t phy_eml_ln64_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln64_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln65_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln65_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1_w {
	struct {
		uint32_t phy_eml_ln66_m1_w:8; /* [7:0] */
		uint32_t phy_emr_ln66_m1_w:8; /* [15:8] */
		uint32_t phy_eml_ln67_m1_w:8; /* [23:16] */
		uint32_t phy_emr_ln67_m1_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2_w {
	struct {
		uint32_t phy_eml_ln0_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln0_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln1_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln1_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2_w {
	struct {
		uint32_t phy_eml_ln2_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln2_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln3_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln3_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2_w {
	struct {
		uint32_t phy_eml_ln4_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln4_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln5_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln5_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2_w {
	struct {
		uint32_t phy_eml_ln6_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln6_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln7_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln7_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2_w {
	struct {
		uint32_t phy_eml_ln8_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln8_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln9_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln9_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2_w {
	struct {
		uint32_t phy_eml_ln10_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln10_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln11_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln11_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2_w {
	struct {
		uint32_t phy_eml_ln12_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln12_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln13_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln13_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2_w {
	struct {
		uint32_t phy_eml_ln14_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln14_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln15_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln15_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2_w {
	struct {
		uint32_t phy_eml_ln16_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln16_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln17_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln17_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2_w {
	struct {
		uint32_t phy_eml_ln18_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln18_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln19_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln19_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2_w {
	struct {
		uint32_t phy_eml_ln20_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln20_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln21_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln21_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2_w {
	struct {
		uint32_t phy_eml_ln22_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln22_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln23_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln23_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2_w {
	struct {
		uint32_t phy_eml_ln24_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln24_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln25_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln25_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2_w {
	struct {
		uint32_t phy_eml_ln26_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln26_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln27_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln27_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2_w {
	struct {
		uint32_t phy_eml_ln28_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln28_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln29_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln29_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2_w {
	struct {
		uint32_t phy_eml_ln30_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln30_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln31_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln31_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2_w {
	struct {
		uint32_t phy_eml_ln32_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln32_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln33_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln33_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2_w {
	struct {
		uint32_t phy_eml_ln34_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln34_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln35_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln35_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2_w {
	struct {
		uint32_t phy_eml_ln36_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln36_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln37_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln37_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2_w {
	struct {
		uint32_t phy_eml_ln38_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln38_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln39_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln39_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2_w {
	struct {
		uint32_t phy_eml_ln40_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln40_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln41_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln41_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2_w {
	struct {
		uint32_t phy_eml_ln42_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln42_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln43_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln43_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2_w {
	struct {
		uint32_t phy_eml_ln44_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln44_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln45_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln45_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2_w {
	struct {
		uint32_t phy_eml_ln46_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln46_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln47_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln47_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2_w {
	struct {
		uint32_t phy_eml_ln48_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln48_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln49_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln49_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2_w {
	struct {
		uint32_t phy_eml_ln50_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln50_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln51_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln51_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2_w {
	struct {
		uint32_t phy_eml_ln52_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln52_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln53_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln53_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2_w {
	struct {
		uint32_t phy_eml_ln54_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln54_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln55_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln55_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2_w {
	struct {
		uint32_t phy_eml_ln56_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln56_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln57_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln57_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2_w {
	struct {
		uint32_t phy_eml_ln58_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln58_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln59_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln59_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2_w {
	struct {
		uint32_t phy_eml_ln60_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln60_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln61_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln61_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2_w {
	struct {
		uint32_t phy_eml_ln62_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln62_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln63_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln63_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2_w {
	struct {
		uint32_t phy_eml_ln64_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln64_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln65_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln65_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2_w {
	struct {
		uint32_t phy_eml_ln66_m2_w:8; /* [7:0] */
		uint32_t phy_emr_ln66_m2_w:8; /* [15:8] */
		uint32_t phy_eml_ln67_m2_w:8; /* [23:16] */
		uint32_t phy_emr_ln67_m2_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3_w {
	struct {
		uint32_t phy_eml_ln0_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln0_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln1_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln1_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3_w {
	struct {
		uint32_t phy_eml_ln2_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln2_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln3_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln3_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3_w {
	struct {
		uint32_t phy_eml_ln4_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln4_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln5_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln5_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3_w {
	struct {
		uint32_t phy_eml_ln6_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln6_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln7_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln7_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3_w {
	struct {
		uint32_t phy_eml_ln8_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln8_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln9_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln9_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3_w {
	struct {
		uint32_t phy_eml_ln10_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln10_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln11_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln11_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3_w {
	struct {
		uint32_t phy_eml_ln12_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln12_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln13_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln13_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3_w {
	struct {
		uint32_t phy_eml_ln14_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln14_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln15_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln15_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3_w {
	struct {
		uint32_t phy_eml_ln16_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln16_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln17_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln17_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3_w {
	struct {
		uint32_t phy_eml_ln18_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln18_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln19_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln19_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3_w {
	struct {
		uint32_t phy_eml_ln20_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln20_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln21_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln21_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3_w {
	struct {
		uint32_t phy_eml_ln22_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln22_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln23_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln23_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3_w {
	struct {
		uint32_t phy_eml_ln24_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln24_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln25_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln25_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3_w {
	struct {
		uint32_t phy_eml_ln26_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln26_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln27_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln27_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3_w {
	struct {
		uint32_t phy_eml_ln28_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln28_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln29_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln29_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3_w {
	struct {
		uint32_t phy_eml_ln30_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln30_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln31_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln31_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3_w {
	struct {
		uint32_t phy_eml_ln32_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln32_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln33_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln33_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3_w {
	struct {
		uint32_t phy_eml_ln34_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln34_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln35_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln35_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3_w {
	struct {
		uint32_t phy_eml_ln36_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln36_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln37_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln37_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3_w {
	struct {
		uint32_t phy_eml_ln38_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln38_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln39_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln39_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3_w {
	struct {
		uint32_t phy_eml_ln40_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln40_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln41_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln41_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3_w {
	struct {
		uint32_t phy_eml_ln42_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln42_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln43_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln43_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3_w {
	struct {
		uint32_t phy_eml_ln44_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln44_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln45_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln45_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3_w {
	struct {
		uint32_t phy_eml_ln46_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln46_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln47_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln47_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3_w {
	struct {
		uint32_t phy_eml_ln48_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln48_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln49_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln49_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3_w {
	struct {
		uint32_t phy_eml_ln50_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln50_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln51_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln51_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3_w {
	struct {
		uint32_t phy_eml_ln52_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln52_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln53_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln53_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3_w {
	struct {
		uint32_t phy_eml_ln54_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln54_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln55_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln55_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3_w {
	struct {
		uint32_t phy_eml_ln56_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln56_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln57_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln57_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3_w {
	struct {
		uint32_t phy_eml_ln58_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln58_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln59_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln59_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3_w {
	struct {
		uint32_t phy_eml_ln60_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln60_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln61_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln61_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3_w {
	struct {
		uint32_t phy_eml_ln62_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln62_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln63_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln63_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3_w {
	struct {
		uint32_t phy_eml_ln64_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln64_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln65_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln65_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3_w {
	struct {
		uint32_t phy_eml_ln66_m3_w:8; /* [7:0] */
		uint32_t phy_emr_ln66_m3_w:8; /* [15:8] */
		uint32_t phy_eml_ln67_m3_w:8; /* [23:16] */
		uint32_t phy_emr_ln67_m3_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_status1_w {
	struct {
		uint32_t m0_mode_w:1; /* [0:0] */
		uint32_t m0_operation_status_w:1; /* [1:1] */
		uint32_t m0_rx_vref_offset_operation_status_w:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_1_w {
	struct {
		uint32_t m0_aggregate_error_count_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_2_w {
	struct {
		uint32_t m0_rx_vref_range_up_w:8; /* [7:0] */
		uint32_t m0_rx_vref_range_down_w:8; /* [15:8] */
		uint32_t m0_trained_value_rx_vref_w:8; /* [23:16] */
		uint32_t m0_vref_step_count_resolution_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_1_w {
	struct {
		uint32_t m0_per_lane_comp_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_2_w {
	struct {
		uint32_t m0_per_lane_comp_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat1_w {
	struct {
		uint32_t m1_mode_w:1; /* [0:0] */
		uint32_t m1_operation_status_w:1; /* [1:1] */
		uint32_t m1_rx_vref_offset_operation_status_w:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_1_w {
	struct {
		uint32_t m1_aggregate_error_count_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_2_w {
	struct {
		uint32_t m1_rx_vref_range_up_w:8; /* [7:0] */
		uint32_t m1_rx_vref_range_down_w:8; /* [15:8] */
		uint32_t m1_trained_value_rx_vref_w:8; /* [23:16] */
		uint32_t m1_vref_step_count_resolution_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_1_w {
	struct {
		uint32_t m1_per_lane_comp_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_2_w {
	struct {
		uint32_t m1_per_lane_comp_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat1_w {
	struct {
		uint32_t m2_mode_w:1; /* [0:0] */
		uint32_t m2_operation_status_w:1; /* [1:1] */
		uint32_t m2_rx_vref_offset_operation_status_w:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_1_w {
	struct {
		uint32_t m2_aggregate_error_count_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_2_w {
	struct {
		uint32_t m2_rx_vref_range_up_w:8; /* [7:0] */
		uint32_t m2_rx_vref_range_down_w:8; /* [15:8] */
		uint32_t m2_trained_value_rx_vref_w:8; /* [23:16] */
		uint32_t m2_vref_step_count_resolution_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_1_w {
	struct {
		uint32_t m2_per_lane_comp_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_2_w {
	struct {
		uint32_t m2_per_lane_comp_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat1_w {
	struct {
		uint32_t m3_mode_w:1; /* [0:0] */
		uint32_t m3_operation_status_w:1; /* [1:1] */
		uint32_t m3_rx_vref_offset_operation_status_w:2; /* [3:2] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_1_w {
	struct {
		uint32_t m3_aggregate_error_count_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_2_w {
	struct {
		uint32_t m3_rx_vref_range_up_w:8; /* [7:0] */
		uint32_t m3_rx_vref_range_down_w:8; /* [15:8] */
		uint32_t m3_trained_value_rx_vref_w:8; /* [23:16] */
		uint32_t m3_vref_step_count_resolution_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_1_w {
	struct {
		uint32_t m3_per_lane_comp_reg1_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_2_w {
	struct {
		uint32_t m3_per_lane_comp_reg2_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1_w {
	struct {
		uint32_t vndr_id_w:16; /* [15:0] */
		uint32_t vndr_id_reg_blk_w:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2_w {
	struct {
		uint32_t vndr_reg_blk_version_w:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3_w {
	struct {
		uint32_t vndr_reg_blk_length_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4_w {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_cap_w {
	struct {
		uint32_t cap_mod_to_byte_map_w:3; /* [2:0] */
		uint32_t cap_terminated_link_w:1; /* [3:3] */
		uint32_t cap_tx_equalization_w:1; /* [4:4] */
		uint32_t cap_vswing_enc_w:6; /* [10:5] */
		uint32_t cap_prx_clk_mode_w:2; /* [12:11] */
		uint32_t cap_rx_clk_phase_w:2; /* [14:13] */
		uint32_t cap_pkg_type_w:1; /* [15:15] */
		uint32_t cap_tcm_w:1; /* [16:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_stat_w {
	struct {
		uint32_t status_mod_to_byte_map_w:3; /* [2:0] */
		uint32_t status_rx_terminated_status_w:1; /* [3:3] */
		uint32_t status_tx_eq_status_w:1; /* [4:4] */
		uint32_t status_clk_mode_status_w:1; /* [5:5] */
		uint32_t status_clk_phase_status_w:1; /* [6:6] */
		uint32_t status_mod_lane_rev_w:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_ctrl1_2_w {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_ctrl1_2_w {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_ctrl1_2_w {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_ctrl1_2_w {
	struct {
		uint32_t full_rsvd; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_tx_mmpl_cfg {
	struct {
		uint32_t reg_phy_mmpl_cfg_tx_lane_map_m0:2; /* [1:0] */
		uint32_t reg_phy_mmpl_cfg_tx_lane_map_m1:2; /* [3:2] */
		uint32_t tx_derate_en:2; /* [5:4] */
		uint32_t reg_phy_mmpl_cfg_tx_lane_map_m3:2; /* [7:6] */
		uint32_t reg_phy_mmpl_cfg_tx_derate_en:1; /* [8:8] */
		uint32_t reg_phy_mmpl_cfg_tx_mod_en:4; /* [12:9] */
		uint32_t reg_phy_mmpl_cfg_tx_pw16_half_mode:1; /* [13:13] */
		uint32_t reg_phy_mmpl_cfg_tx_mod_map_m0:2; /* [15:14] */
		uint32_t reg_phy_mmpl_cfg_tx_mod_map_m1:2; /* [17:16] */
		uint32_t reg_phy_mmpl_cfg_tx_mod_map_m2:2; /* [19:18] */
		uint32_t reg_phy_mmpl_cfg_tx_mod_map_m3:2; /* [21:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rx_mmpl_cfg {
	struct {
		uint32_t reg_phy_mmpl_cfg_rx_lane_map_m0:2; /* [1:0] */
		uint32_t reg_phy_mmpl_cfg_rx_lane_map_m1:2; /* [3:2] */
		uint32_t reg_phy_mmpl_cfg_rx_lane_map_m2:2; /* [5:4] */
		uint32_t reg_phy_mmpl_cfg_rx_lane_map_m3:2; /* [7:6] */
		uint32_t reg_phy_mmpl_cfg_rx_derate_en:1; /* [8:8] */
		uint32_t reg_phy_mmpl_cfg_rx_mod_en:4; /* [12:9] */
		uint32_t reg_phy_mmpl_cfg_rx_pw16_half_mode:1; /* [13:13] */
		uint32_t reg_phy_mmpl_cfg_rx_mod_map_m0:2; /* [15:14] */
		uint32_t reg_phy_mmpl_cfg_rx_mod_map_m1:2; /* [17:16] */
		uint32_t reg_phy_mmpl_cfg_rx_mod_map_m2:2; /* [19:18] */
		uint32_t reg_phy_mmpl_cfg_rx_mod_map_m3:2; /* [21:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_mmpl_sts {
	struct {
		uint32_t mod_m0_id:2; /* [1:0] */
		uint32_t mod_m1_id:2; /* [3:2] */
		uint32_t mod_m2_id:2; /* [5:4] */
		uint32_t mod_m3_id:2; /* [7:6] */
		uint32_t rx_deskew_max_count:2; /* [9:8] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_rst_cfg {
	struct {
		uint32_t sync_rst:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1 {
	struct {
		uint32_t rdi_lp_linkerror_int1:1; /* [0:0] */
		uint32_t rdi_lp_stallack_int1:1; /* [1:1] */
		uint32_t rdi_lp_clk_ack_int1:1; /* [2:2] */
		uint32_t rdi_lp_wake_req_int1:1; /* [3:3] */
		uint32_t rdi_lp_state_req_int1:1; /* [4:4] */
		uint32_t rdi_pl_state_sts_int1:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1_mask {
	struct {
		uint32_t rdi_lp_linkerror_int1_mask:1; /* [0:0] */
		uint32_t rdi_lp_stallack_int1_mask:1; /* [1:1] */
		uint32_t rdi_lp_clk_ack_int1_mask:1; /* [2:2] */
		uint32_t rdi_lp_wake_req_int1_mask:1; /* [3:3] */
		uint32_t rdi_lp_state_req_int1_mask:1; /* [4:4] */
		uint32_t rdi_pl_state_sts_int1_mask:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2 {
	struct {
		uint32_t rdi_lp_linkerror_int2:1; /* [0:0] */
		uint32_t rdi_lp_stallack_int2:1; /* [1:1] */
		uint32_t rdi_lp_clk_ack_int2:1; /* [2:2] */
		uint32_t rdi_lp_wake_req_int2:1; /* [3:3] */
		uint32_t rdi_lp_state_req_int2:1; /* [4:4] */
		uint32_t rdi_pl_state_sts_int2:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2_mask {
	struct {
		uint32_t rdi_lp_linkerror_int2_mask:1; /* [0:0] */
		uint32_t rdi_lp_stallack_int2_mask:1; /* [1:1] */
		uint32_t rdi_lp_clk_ack_int2_mask:1; /* [2:2] */
		uint32_t rdi_lp_wake_req_int2_mask:1; /* [3:3] */
		uint32_t rdi_lp_state_req_int2_mask:1; /* [4:4] */
		uint32_t rdi_pl_state_sts_int2_mask:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_spare_in_ctrl {
	struct {
		uint32_t ictl_cmn_spare:4; /* [3:0] */
		uint32_t ictl_top_spare:4; /* [7:4] */
	};
	uint32_t val;
};

union aw_ucie_phy_imp_spec_reg_spare_out_ctrl {
	struct {
		uint32_t octl_cmn_spare_out:4; /* [3:0] */
		uint32_t octl_top_spare_out:4; /* [7:4] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_ctrl {
	struct {
		uint32_t reset_n_a:1; /* [0:0] */
		uint32_t clk_en_a:1; /* [1:1] */
		uint32_t fetch_en_a:1; /* [2:2] */
		uint32_t dble_fault_seen_clr_a:1; /* [3:3] */
		uint32_t time_out_threshold_nt:10; /* [13:4] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_hart_id {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_boot_addr {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_device_addr {
	struct {
		uint32_t base_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_dmem {
	struct {
		uint32_t alias_addr_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_irq_ctrl1 {
	struct {
		uint32_t edge_sel_nt:30; /* [29:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_irq_ctrl2 {
	struct {
		uint32_t det_type_nt:15; /* [14:0] */
		uint32_t clear_a:15; /* [29:15] */
		uint32_t software_irq_a:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_irq {
	struct {
		uint32_t flag:15; /* [14:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_crash_dump3 {
	struct {
		uint32_t curr_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_crash_dump2 {
	struct {
		uint32_t nxt_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_crash_dump1 {
	struct {
		uint32_t last_data_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_crash_dump0 {
	struct {
		uint32_t excep_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_stats {
	struct {
		uint32_t core_sleep:1; /* [0:0] */
		uint32_t dble_fault_seen:1; /* [1:1] */
		uint32_t dmactive:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_sram_cfg_rd_data {
	struct {
		uint32_t pipeline_stages_nt:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg1 {
	struct {
		uint32_t cmn_mcu_scratch1_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg2 {
	struct {
		uint32_t cmn_mcu_scratch2_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg3 {
	struct {
		uint32_t cmn_mcu_scratch3_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg4 {
	struct {
		uint32_t cmn_mcu_scratch4_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg5 {
	struct {
		uint32_t cmn_mcu_scratch5_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg6 {
	struct {
		uint32_t cmn_mcu_scratch6_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg7 {
	struct {
		uint32_t cmn_mcu_scratch7_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg8 {
	struct {
		uint32_t cmn_mcu_scratch8_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg9 {
	struct {
		uint32_t cmn_mcu_scratch9_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_cmn_mcu_scratch_reg10 {
	struct {
		uint32_t cmn_mcu_scratch10_reg; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_global_cmn_cfg1 {
	struct {
		uint32_t mb_sync_rst:1; /* [0:0] */
		uint32_t sb_sync_rst:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_global_intr1_summary {
	struct {
		uint32_t prot_bridge_mb_int1:1; /* [0:0] */
		uint32_t prot_bridge_sb_int1:1; /* [1:1] */
		uint32_t soc_bridge_int1:1; /* [2:2] */
		uint32_t adapter_d2d_ecc_int1:1; /* [3:3] */
		uint32_t adapter_fdi_mb_int1:1; /* [4:4] */
		uint32_t adapter_fdi_sb_int1:1; /* [5:5] */
		uint32_t adapter_rdi_mb_int1:1; /* [6:6] */
		uint32_t adapter_rdi_sb_int1:1; /* [7:7] */
		uint32_t lphy_m0_tx_int1:1; /* [8:8] */
		uint32_t lphy_m0_rx_int1:1; /* [9:9] */
		uint32_t lphy_m0_sb_int1:1; /* [10:10] */
		uint32_t lphy_m0_sb_afifo_int1:1; /* [11:11] */
		uint32_t lphy_m1_tx_int1:1; /* [12:12] */
		uint32_t lphy_m1_rx_int1:1; /* [13:13] */
		uint32_t lphy_m1_sb_int1:1; /* [14:14] */
		uint32_t lphy_m1_sb_afifo_int1:1; /* [15:15] */
		uint32_t lphy_m2_tx_int1:1; /* [16:16] */
		uint32_t lphy_m2_rx_int1:1; /* [17:17] */
		uint32_t lphy_m2_sb_int1:1; /* [18:18] */
		uint32_t lphy_m2_sb_afifo_int1:1; /* [19:19] */
		uint32_t lphy_m3_tx_int1:1; /* [20:20] */
		uint32_t lphy_m3_rx_int1:1; /* [21:21] */
		uint32_t lphy_m3_sb_int1:1; /* [22:22] */
		uint32_t lphy_m3_sb_afifo_int1:1; /* [23:23] */
		uint32_t lphy_rdi_sb_int1:1; /* [24:24] */
		uint32_t lphy_rdi_mb_int1:1; /* [25:25] */
		uint32_t cmn_top_int1:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_global_intr1_summary_mask {
	struct {
		uint32_t prot_bridge_mb_int1_mask:1; /* [0:0] */
		uint32_t prot_bridge_sb_int1_mask:1; /* [1:1] */
		uint32_t soc_bridge_int1_mask:1; /* [2:2] */
		uint32_t adapter_d2d_ecc_int1_mask:1; /* [3:3] */
		uint32_t adapter_fdi_mb_int1_mask:1; /* [4:4] */
		uint32_t adapter_fdi_sb_int1_mask:1; /* [5:5] */
		uint32_t adapter_rdi_mb_int1_mask:1; /* [6:6] */
		uint32_t adapter_rdi_sb_int1_mask:1; /* [7:7] */
		uint32_t lphy_m0_tx_int1_mask:1; /* [8:8] */
		uint32_t lphy_m0_rx_int1_mask:1; /* [9:9] */
		uint32_t lphy_m0_sb_int1_mask:1; /* [10:10] */
		uint32_t lphy_m0_sb_afifo_int1_mask:1; /* [11:11] */
		uint32_t lphy_m1_tx_int1_mask:1; /* [12:12] */
		uint32_t lphy_m1_rx_int1_mask:1; /* [13:13] */
		uint32_t lphy_m1_sb_int1_mask:1; /* [14:14] */
		uint32_t lphy_m1_sb_afifo_int1_mask:1; /* [15:15] */
		uint32_t lphy_m2_tx_int1_mask:1; /* [16:16] */
		uint32_t lphy_m2_rx_int1_mask:1; /* [17:17] */
		uint32_t lphy_m2_sb_int1_mask:1; /* [18:18] */
		uint32_t lphy_m2_sb_afifo_int1_mask:1; /* [19:19] */
		uint32_t lphy_m3_tx_int1_mask:1; /* [20:20] */
		uint32_t lphy_m3_rx_int1_mask:1; /* [21:21] */
		uint32_t lphy_m3_sb_int1_mask:1; /* [22:22] */
		uint32_t lphy_m3_sb_afifo_int1_mask:1; /* [23:23] */
		uint32_t lphy_rdi_sb_int1_mask:1; /* [24:24] */
		uint32_t lphy_rdi_mb_int1_mask:1; /* [25:25] */
		uint32_t cmn_top_int1_mask:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_global_intr2_summary {
	struct {
		uint32_t prot_bridge_mb_int2:1; /* [0:0] */
		uint32_t prot_bridge_sb_int2:1; /* [1:1] */
		uint32_t soc_bridge_int2:1; /* [2:2] */
		uint32_t adapter_d2d_ecc_int2:1; /* [3:3] */
		uint32_t adapter_fdi_mb_int2:1; /* [4:4] */
		uint32_t adapter_fdi_sb_int2:1; /* [5:5] */
		uint32_t adapter_rdi_mb_int2:1; /* [6:6] */
		uint32_t adapter_rdi_sb_int2:1; /* [7:7] */
		uint32_t lphy_m0_tx_int2:1; /* [8:8] */
		uint32_t lphy_m0_rx_int2:1; /* [9:9] */
		uint32_t lphy_m0_sb_int2:1; /* [10:10] */
		uint32_t lphy_m0_sb_afifo_int2:1; /* [11:11] */
		uint32_t lphy_m1_tx_int2:1; /* [12:12] */
		uint32_t lphy_m1_rx_int2:1; /* [13:13] */
		uint32_t lphy_m1_sb_int2:1; /* [14:14] */
		uint32_t lphy_m1_sb_afifo_int2:1; /* [15:15] */
		uint32_t lphy_m2_tx_int2:1; /* [16:16] */
		uint32_t lphy_m2_rx_int2:1; /* [17:17] */
		uint32_t lphy_m2_sb_int2:1; /* [18:18] */
		uint32_t lphy_m2_sb_afifo_int2:1; /* [19:19] */
		uint32_t lphy_m3_tx_int2:1; /* [20:20] */
		uint32_t lphy_m3_rx_int2:1; /* [21:21] */
		uint32_t lphy_m3_sb_int2:1; /* [22:22] */
		uint32_t lphy_m3_sb_afifo_int2:1; /* [23:23] */
		uint32_t lphy_rdi_sb_int2:1; /* [24:24] */
		uint32_t lphy_rdi_mb_int2:1; /* [25:25] */
		uint32_t cmn_top_int2:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_global_intr2_summary_mask {
	struct {
		uint32_t prot_bridge_mb_int2_mask:1; /* [0:0] */
		uint32_t prot_bridge_sb_int2_mask:1; /* [1:1] */
		uint32_t soc_bridge_int2_mask:1; /* [2:2] */
		uint32_t adapter_d2d_ecc_int2_mask:1; /* [3:3] */
		uint32_t adapter_fdi_mb_int2_mask:1; /* [4:4] */
		uint32_t adapter_fdi_sb_int2_mask:1; /* [5:5] */
		uint32_t adapter_rdi_mb_int2_mask:1; /* [6:6] */
		uint32_t adapter_rdi_sb_int2_mask:1; /* [7:7] */
		uint32_t lphy_m0_tx_int2_mask:1; /* [8:8] */
		uint32_t lphy_m0_rx_int2_mask:1; /* [9:9] */
		uint32_t lphy_m0_sb_int2_mask:1; /* [10:10] */
		uint32_t lphy_m0_sb_afifo_int2_mask:1; /* [11:11] */
		uint32_t lphy_m1_tx_int2_mask:1; /* [12:12] */
		uint32_t lphy_m1_rx_int2_mask:1; /* [13:13] */
		uint32_t lphy_m1_sb_int2_mask:1; /* [14:14] */
		uint32_t lphy_m1_sb_afifo_int2_mask:1; /* [15:15] */
		uint32_t lphy_m2_tx_int2_mask:1; /* [16:16] */
		uint32_t lphy_m2_rx_int2_mask:1; /* [17:17] */
		uint32_t lphy_m2_sb_int2_mask:1; /* [18:18] */
		uint32_t lphy_m2_sb_afifo_int2_mask:1; /* [19:19] */
		uint32_t lphy_m3_tx_int2_mask:1; /* [20:20] */
		uint32_t lphy_m3_rx_int2_mask:1; /* [21:21] */
		uint32_t lphy_m3_sb_int2_mask:1; /* [22:22] */
		uint32_t lphy_m3_sb_afifo_int2_mask:1; /* [23:23] */
		uint32_t lphy_rdi_sb_int2_mask:1; /* [24:24] */
		uint32_t lphy_rdi_mb_int2_mask:1; /* [25:25] */
		uint32_t cmn_top_int2_mask:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_pcie_extnd_cap_hdr_w {
	struct {
		uint32_t pcie_extnd_cap_hdr_cap_id_w:16; /* [15:0] */
		uint32_t pcie_extnd_cap_hdr_revision_id_w:4; /* [19:16] */
		uint32_t pcie_extnd_cap_hdr_next_cap_offset_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_hdr1_w {
	struct {
		uint32_t hdr1_dvsec_vndr_id_w:16; /* [15:0] */
		uint32_t hdr1_dvsec_revision_w:4; /* [19:16] */
		uint32_t hdr1_len_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_hdr2_and_cap_descriptor_w {
	struct {
		uint32_t hdr2_dvsec_id_w:16; /* [15:0] */
		uint32_t cap_descriptor_no_of_reg_locators_w:3; /* [18:16] */
		uint32_t cap_descriptor_sb_mailbox_reg_present_w:1; /* [19:19] */
		uint32_t cap_descriptor_no_of_switch_dsps_w:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_ucie_link_cap_and_status_w {
	struct {
		uint32_t lcap_raw_format_w:1; /* [0:0] */
		uint32_t lcap_retimer_w:1; /* [1:1] */
		uint32_t lcap_multi_stack_capable_w:1; /* [2:2] */
		uint32_t lcap_adv_pkg_w:1; /* [3:3] */
		uint32_t lcap_68b_flit_fmt_strmng_w:1; /* [4:4] */
		uint32_t lcap_std_256b_end_hdr_flit_fmt_strmng_w:1; /* [5:5] */
		uint32_t lcap_std_256b_start_hdr_flit_fmt_strmng_w:1; /* [6:6] */
		uint32_t lcap_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng_w:1; /* [7:7] */
		uint32_t lcap_lat_opt_256b_flit_fmt_optnl_bytes_strmng_w:1; /* [8:8] */
		uint32_t lcap_enhanced_multi_protocol_cap_w:1; /* [9:9] */
		uint32_t lcap_std_start_hdr_flit_pcie_w:1; /* [10:10] */
		uint32_t lcap_lat_opt_flit_with_optnl_bytes_pcie_w:1; /* [11:11] */
		uint32_t lcap_runtime_link_test_parity_feat_err_signaling_w:1; /* [12:12] */
		uint32_t lcap_width32_mode_w:1; /* [13:13] */
		uint32_t lstatus_raw_format_en_w:1; /* [14:14] */
		uint32_t lstatus_multi_stack_en_w:1; /* [15:15] */
		uint32_t lstatus_enhanced_multi_protocol_en_w:1; /* [16:16] */
		uint32_t lstatus_adv_pkg_mod_size_w:1; /* [17:17] */
		uint32_t lstatus_link_width_en_w:4; /* [21:18] */
		uint32_t lstatus_link_speed_en_w:4; /* [25:22] */
		uint32_t lstatus_link_status_w:1; /* [26:26] */
		uint32_t lstatus_link_train_or_retrain_w:1; /* [27:27] */
		uint32_t lstatus_link_status_change_w:1; /* [28:28] */
		uint32_t lstatus_hw_autonomous_bw_change_w:1; /* [29:29] */
		uint32_t lstatus_ucie_link_corr_err_w:1; /* [30:30] */
		uint32_t lstatus_ucie_link_uncorr_non_fatal_err_w:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_link_sts_evnt_err_nf_ctrl_loc0_w {
	struct {
		uint32_t lstatus_ucie_link_uncorr_fatal_err_w:1; /* [0:0] */
		uint32_t lstatus_flit_format_status_w:4; /* [4:1] */
		uint32_t link_event_nf_intr_num_w:5; /* [9:5] */
		uint32_t reg_loc0_low_reg_bir_w:3; /* [12:10] */
		uint32_t reg_loc0_low_reg_blk_identifier_w:4; /* [16:13] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_low_w {
	struct {
		uint32_t reg_loc0_low_reg_blk_offset_w:20; /* [19:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_high_w {
	struct {
		uint32_t reg_loc0_high_reg_blk_offset_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_low_w {
	struct {
		uint32_t reg_loc1_low_reg_bir_w:3; /* [2:0] */
		uint32_t reg_loc1_low_reg_blk_identifier_w:4; /* [6:3] */
		uint32_t reg_loc1_low_reg_blk_offset_w:20; /* [26:7] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_high_w {
	struct {
		uint32_t reg_loc1_high_reg_blk_offset_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_low_w {
	struct {
		uint32_t reg_loc2_low_reg_bir_w:3; /* [2:0] */
		uint32_t reg_loc2_low_reg_blk_identifier_w:4; /* [6:3] */
		uint32_t reg_loc2_low_reg_blk_offset_w:20; /* [26:7] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_high_w {
	struct {
		uint32_t reg_loc2_high_reg_blk_offset_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_low_w {
	struct {
		uint32_t reg_loc3_low_reg_bir_w:3; /* [2:0] */
		uint32_t reg_loc3_low_reg_blk_identifier_w:4; /* [6:3] */
		uint32_t reg_loc3_low_reg_blk_offset_w:20; /* [26:7] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_high_w {
	struct {
		uint32_t reg_loc3_high_reg_blk_offset_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec1_sb_mlbox_ctrl_stats_assoc_port_num_w {
	struct {
		uint32_t sb_mailbox_stats_wr_or_rd_status_w:2; /* [1:0] */
		uint32_t assoc_port_num1_w:8; /* [9:2] */
		uint32_t assoc_port_num2_w:8; /* [17:10] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1_w {
	struct {
		uint32_t uisrb_base_addr_reg1_bir_w:1; /* [0:0] */
		uint32_t uisrb_base_addr_reg1_blk_offset_w:20; /* [20:1] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2_w {
	struct {
		uint32_t uisrb_base_addr_reg2_blk_offset_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr1_w {
	struct {
		uint32_t blk_hdr1_vndr_id_w:16; /* [15:0] */
		uint32_t blk_hdr1_vndr_id_reg_blk_w:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr2_w {
	struct {
		uint32_t blk_hdr2_vndr_blk_version_w:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr3_w {
	struct {
		uint32_t blk_hdr3_vndr_blk_len_w; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_d2d_adapter_and_phy_testcompl_reg_blk_offset_w {
	struct {
		uint32_t d2d_adapter_testcompl_blk_offset_w:8; /* [7:0] */
		uint32_t d2d_adapter_testcompl_blk_len_w:8; /* [15:8] */
		uint32_t phy_testcompl_blk_offset_w:8; /* [23:16] */
		uint32_t phy_testcompl_blk_len_w:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_spare_out_ctrl {
	struct {
		uint32_t top_wrap_spare_out:4; /* [3:0] */
		uint32_t ucie_phy_wrap_spare_out:4; /* [7:4] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_spare_in_ctrl {
	struct {
		uint32_t top_wrap_spare:4; /* [3:0] */
		uint32_t ucie_phy_wrap_spare:4; /* [7:4] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_apb_response_timeout {
	struct {
		uint32_t apb_response_timeout:9; /* [8:0] */
		uint32_t apb_response_timeout_en:1; /* [9:9] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_cmn_top_int1 {
	struct {
		uint32_t cmn_top_sram_uncorr_err_int1:1; /* [0:0] */
		uint32_t cmn_top_sram_corr_err_int1:1; /* [1:1] */
		uint32_t cmn_top_ext_int1:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_cmn_top_int2 {
	struct {
		uint32_t cmn_top_sram_uncorr_err_int2:1; /* [0:0] */
		uint32_t cmn_top_sram_corr_err_int2:1; /* [1:1] */
		uint32_t cmn_top_ext_int2:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_cmn_top_int1_mask {
	struct {
		uint32_t cmn_top_sram_uncorr_err_int1_mask:1; /* [0:0] */
		uint32_t cmn_top_sram_corr_err_int1_mask:1; /* [1:1] */
		uint32_t cmn_top_ext_int1_mask:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_cmn_top_int2_mask {
	struct {
		uint32_t cmn_top_sram_uncorr_err_int2_mask:1; /* [0:0] */
		uint32_t cmn_top_sram_corr_err_int2_mask:1; /* [1:1] */
		uint32_t cmn_top_ext_int2_mask:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec2_pcie_extnd_cap_hdr_w {
	struct {
		uint32_t dvsec_pcie_extnd_cap_hdr_cap_id_w:16; /* [15:0] */
		uint32_t dvsec_pcie_extnd_cap_hdr_rev_id_w:4; /* [19:16] */
		uint32_t dvsec_pcie_extnd_cap_hdr_next_cap_offset_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec2_hdr1_w {
	struct {
		uint32_t dvsec_hdr1_dvsec_vndr_id_w:16; /* [15:0] */
		uint32_t dvsec_hdr1_dvsec_revision_w:4; /* [19:16] */
		uint32_t dvsec_hdr1_len_w:12; /* [31:20] */
	};
	uint32_t val;
};

union aw_ucie_global_reg_reg_glbl_dvsec2_hdr2_w {
	struct {
		uint32_t dvsec_hdr2_dvsec_id_w:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmn_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmn_ctrl {
	struct {
		uint32_t power:1; /* [0:0] */
		uint32_t instr_req:1; /* [1:1] */
		uint32_t instr_type:4; /* [5:2] */
		uint32_t reset_b:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmn_ctrl_rdreg {
	struct {
		uint32_t power_stat:1; /* [0:0] */
		uint32_t instr_ack:1; /* [1:1] */
		uint32_t state:4; /* [5:2] */
		uint32_t reset_done:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_clr {
	struct {
		uint32_t pi:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_piack_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_pictrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_pireq {
	struct {
		uint32_t req:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_pival {
	struct {
		uint32_t val:7; /* [6:0] */
		uint32_t dir:1; /* [7:7] */
	};
	uint32_t reg_val;
};

union aw_ucie_phy_cmn_reg_cmnafe_pival_rdreg {
	struct {
		uint32_t val:7; /* [6:0] */
	};
	uint32_t reg_val;
};

union aw_ucie_phy_cmn_reg_cmnafe_rdreg {
	struct {
		uint32_t bypass:2; /* [1:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_reg1 {
	struct {
		uint32_t bias_adj_nt:4; /* [3:0] */
		uint32_t bias_startup_force_nt:1; /* [4:4] */
		uint32_t bypass_ena_a:1; /* [5:5] */
		uint32_t clkgen_bias_adj_nt:2; /* [7:6] */
		uint32_t hsrefbuf_bias_adj_nt:2; /* [9:8] */
		uint32_t lsref_term_cal_a:3; /* [12:10] */
		uint32_t div24_sel_a:1; /* [13:13] */
		uint32_t lsrefbuf_bias_adj_nt:2; /* [15:14] */
		uint32_t lsrefbuf_heartbeat_ena_a:1; /* [16:16] */
		uint32_t lsrefbuf_term_mode_nt:2; /* [18:17] */
		uint32_t ref_ls_looptime_select_nt:1; /* [19:19] */
		uint32_t spare_nt:4; /* [23:20] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_reg2 {
	struct {
		uint32_t vref_hsref_select_nt:1; /* [0:0] */
		uint32_t vref_select_nt:1; /* [1:1] */
		uint32_t vreg_bleed_hsref_ena_a:1; /* [2:2] */
		uint32_t vreg_hsref_nt:4; /* [6:3] */
		uint32_t vreg_hsref_scbypass_nt:1; /* [7:7] */
		uint32_t bscan_rx_vbias_nt:3; /* [10:8] */
		uint32_t bscan_rx_vhyst_nt:2; /* [12:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_reg3 {
	struct {
		uint32_t sideband_clkdiv_nt:10; /* [9:0] */
		uint32_t pclk_clkdiv_nt:10; /* [19:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafe_reg4 {
	struct {
		uint32_t pi_cal_en_a:1; /* [0:0] */
		uint32_t pi_decoder_nt:7; /* [7:1] */
		uint32_t pi_ical_decoder_a:3; /* [10:8] */
		uint32_t pi_qcal_decoder_a:3; /* [13:11] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnafepd {
	struct {
		uint32_t atest_adc_ba:1; /* [0:0] */
		uint32_t atest_pmon_ba:1; /* [1:1] */
		uint32_t bias_ba:1; /* [2:2] */
		uint32_t bscan_ba:1; /* [3:3] */
		uint32_t div24_ba:1; /* [4:4] */
		uint32_t lsrefbuf_ba:1; /* [5:5] */
		uint32_t pi_cml2cmos_ba:1; /* [6:6] */
		uint32_t ref_ls_looptime_ba:1; /* [7:7] */
		uint32_t reg_hsref_ba:1; /* [8:8] */
		uint32_t zqcal_ba:1; /* [9:9] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnaferst {
	struct {
		uint32_t atest_adc_ba:1; /* [0:0] */
		uint32_t atest_pmon_ba:1; /* [1:1] */
		uint32_t div24_ba:1; /* [2:2] */
		uint32_t pclk_clkdiv_ba:1; /* [3:3] */
		uint32_t pi_ba:1; /* [4:4] */
		uint32_t pll_clkdiv_ba:1; /* [5:5] */
		uint32_t sideband_clkdiv_ba:1; /* [6:6] */
		uint32_t pll_offset_cal_ba:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnatest {
	struct {
		uint32_t addr_bin_nt:5; /* [4:0] */
		uint32_t bias_adj_nt:2; /* [6:5] */
		uint32_t capture_ena_a:1; /* [7:7] */
		uint32_t digsig_a:1; /* [8:8] */
		uint32_t div_nt:3; /* [11:9] */
		uint32_t meas_term_a:3; /* [14:12] */
		uint32_t pmonsel_a:4; /* [18:15] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnatest_rdreg {
	struct {
		uint32_t atest_adc_nt:12; /* [11:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnclkctrl {
	struct {
		uint32_t sram_fast_a:1; /* [0:0] */
		uint32_t soc_clk_en_a:1; /* [1:1] */
		uint32_t ref_clk_en_a:1; /* [2:2] */
		uint32_t vco_clk_en_a:1; /* [3:3] */
		uint32_t master_sel_a:4; /* [7:4] */
		uint32_t pworddiv_nt:2; /* [9:8] */
		uint32_t refdiv_nt:2; /* [11:10] */
		uint32_t vcodiv_nt:2; /* [13:12] */
		uint32_t pmon_sel_nt:1; /* [14:14] */
		uint32_t plldiv_clk_sel_nt:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_rdreg {
	struct {
		uint32_t lock:1; /* [0:0] */
		uint32_t offset_cal:12; /* [12:1] */
		uint32_t offset_cal_lock:1; /* [13:13] */
		uint32_t offset_cal_ovf:1; /* [14:14] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg1 {
	struct {
		uint32_t bypass_nt:1; /* [0:0] */
		uint32_t dacen_nt:1; /* [1:1] */
		uint32_t div_upd_edge_a:1; /* [2:2] */
		uint32_t dsmen_nt:1; /* [3:3] */
		uint32_t en_a:1; /* [4:4] */
		uint32_t fout4phaseen_a:1; /* [5:5] */
		uint32_t foutpostdiven_a:1; /* [6:6] */
		uint32_t foutvcoen_a:1; /* [7:7] */
		uint32_t postdiv1_nt:3; /* [10:8] */
		uint32_t postdiv2_nt:3; /* [13:11] */
		uint32_t refdiv_nt:6; /* [19:14] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg2 {
	struct {
		uint32_t fbdiv_nt:12; /* [11:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg3 {
	struct {
		uint32_t frac_nt:24; /* [23:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg4 {
	struct {
		uint32_t reserved_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg5 {
	struct {
		uint32_t offset_cal_bypass_a:1; /* [0:0] */
		uint32_t offset_cal_counter_a:3; /* [3:1] */
		uint32_t offset_cal_en_a:1; /* [4:4] */
		uint32_t offset_cal_in_a:12; /* [16:5] */
		uint32_t offset_fastcal_a:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg6 {
	struct {
		uint32_t ssc_en_a:1; /* [0:0] */
		uint32_t ssc_upd_a:1; /* [1:1] */
		uint32_t ssc_delay_nt:8; /* [9:2] */
		uint32_t ssc_flat_nt:4; /* [13:10] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg7 {
	struct {
		uint32_t ssc_min_nt:24; /* [23:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg8 {
	struct {
		uint32_t ssc_max_nt:24; /* [23:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpll_reg9 {
	struct {
		uint32_t ssc_step_nt:22; /* [21:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpmon {
	struct {
		uint32_t time_nt:16; /* [15:0] */
		uint32_t req_a:1; /* [16:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnpmon_rdreg {
	struct {
		uint32_t result:16; /* [15:0] */
		uint32_t ack:1; /* [16:16] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnrxtx_reg1 {
	struct {
		uint32_t cmn_info; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnrxtx_reg2 {
	struct {
		uint32_t dncal:8; /* [7:0] */
		uint32_t upcal:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnsoc_reg1 {
	struct {
		uint32_t ena_mux_sel_ovr_ena_a:1; /* [0:0] */
		uint32_t ena_ref_ls_ovr_ena_a:1; /* [1:1] */
		uint32_t l2r0_mux_sel_ovr_nt:2; /* [3:2] */
		uint32_t l2r1_mux_sel_ovr_nt:2; /* [5:4] */
		uint32_t ls_mux_sel_ovr_nt:3; /* [8:6] */
		uint32_t r2l0_mux_sel_ovr_nt:2; /* [10:9] */
		uint32_t r2l1_mux_sel_ovr_nt:2; /* [12:11] */
		uint32_t ref_ls_ena_ovr_a:1; /* [13:13] */
		uint32_t lsrefbuf_term_mode_ovr_ena_a:1; /* [14:14] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnzqcal_rdreg {
	struct {
		uint32_t error:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnzqcal_reg1 {
	struct {
		uint32_t atest_en_nt:1; /* [0:0] */
		uint32_t atest_nt:4; /* [4:1] */
		uint32_t dncal_a:8; /* [12:5] */
		uint32_t en_a:1; /* [13:13] */
		uint32_t flip_a:1; /* [14:14] */
		uint32_t phase_nt:4; /* [18:15] */
		uint32_t upcal_a:8; /* [26:19] */
		uint32_t vddqmode_nt:1; /* [27:27] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_cmnzqcal_reg2 {
	struct {
		uint32_t vref_ctrl_a:7; /* [6:0] */
		uint32_t vsel_a:1; /* [7:7] */
		uint32_t spare_a:10; /* [17:8] */
	};
	uint32_t val;
};

union aw_ucie_phy_cmn_reg_sram_cfg {
	struct {
		uint32_t rd_data_pipeline_stages_nt:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rx_ctrl {
	struct {
		uint32_t power:1; /* [0:0] */
		uint32_t instr_req:1; /* [1:1] */
		uint32_t instr_type:4; /* [5:2] */
		uint32_t loopback:2; /* [7:6] */
		uint32_t failed:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rx_ctrl_rdreg {
	struct {
		uint32_t power_stat:1; /* [0:0] */
		uint32_t instr_ack:1; /* [1:1] */
		uint32_t state:4; /* [5:2] */
		uint32_t reset_done:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxcalen {
	struct {
		uint32_t ndealign:1; /* [0:0] */
		uint32_t offset:1; /* [1:1] */
		uint32_t dcc:1; /* [2:2] */
		uint32_t qcc:1; /* [3:3] */
		uint32_t txsync:1; /* [4:4] */
		uint32_t retpi:1; /* [5:5] */
		uint32_t retvref:1; /* [6:6] */
		uint32_t retpbd:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxclkchk_rdreg {
	struct {
		uint32_t clkn_cnt:16; /* [15:0] */
		uint32_t clkp_cnt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxcmn_reg1 {
	struct {
		uint32_t cmn_info; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxcmn_reg2 {
	struct {
		uint32_t dncal:8; /* [7:0] */
		uint32_t upcal:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg0 {
	struct {
		uint32_t shift_right_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg1 {
	struct {
		uint32_t shift_right_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg2 {
	struct {
		uint32_t shift_right_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg3 {
	struct {
		uint32_t shift_left_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg4 {
	struct {
		uint32_t shift_left_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatapath_reg5 {
	struct {
		uint32_t shift_left_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatcap_rdreg1 {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatcap_rdreg2 {
	struct {
		uint32_t val; /* [31:0] */
	};
	uint32_t reg_val;
};

union aw_ucie_rx0_reg_rxdatcap_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t sel:6; /* [6:1] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg0 {
	struct {
		uint32_t vec_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg1 {
	struct {
		uint32_t vec_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg10 {
	struct {
		uint32_t vec_10; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg11 {
	struct {
		uint32_t vec_11; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg12 {
	struct {
		uint32_t vec_12; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg13 {
	struct {
		uint32_t vec_13; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg14 {
	struct {
		uint32_t vec_14; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg15 {
	struct {
		uint32_t vec_15; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg16 {
	struct {
		uint32_t vec_16; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg2 {
	struct {
		uint32_t vec_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg3 {
	struct {
		uint32_t vec_3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg4 {
	struct {
		uint32_t vec_4; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg5 {
	struct {
		uint32_t vec_5; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg6 {
	struct {
		uint32_t vec_6; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg7 {
	struct {
		uint32_t vec_7; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg8 {
	struct {
		uint32_t vec_8; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg9 {
	struct {
		uint32_t vec_9; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg1 {
	struct {
		uint32_t cnt:16; /* [15:0] */
		uint32_t lock:1; /* [16:16] */
		uint32_t running:1; /* [17:17] */
		uint32_t done:1; /* [18:18] */
		uint32_t complete_stat:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg10 {
	struct {
		uint32_t succ_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg11 {
	struct {
		uint32_t succ_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg12 {
	struct {
		uint32_t succ_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg2 {
	struct {
		uint32_t err_cnt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg3 {
	struct {
		uint32_t err_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg4 {
	struct {
		uint32_t err_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg5 {
	struct {
		uint32_t err_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg1 {
	struct {
		uint32_t cmn_seed_nt:1; /* [0:0] */
		uint32_t en:1; /* [1:1] */
		uint32_t mode_nt:1; /* [2:2] */
		uint32_t pat_sel_nt:4; /* [6:3] */
		uint32_t err_cnt_sel:7; /* [13:7] */
		uint32_t subset_nt:2; /* [15:14] */
		uint32_t trylock_num_nt:5; /* [20:16] */
		uint32_t position_nt:1; /* [21:21] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg13 {
	struct {
		uint32_t burst_mode_en:1; /* [0:0] */
		uint32_t force_last_check_en:1; /* [1:1] */
		uint32_t force_last_check:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg2 {
	struct {
		uint32_t err_thres_nt:16; /* [15:0] */
		uint32_t timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg3 {
	struct {
		uint32_t valtrain_vec_nt:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg4 {
	struct {
		uint32_t val_pat_en:1; /* [0:0] */
		uint32_t valrd_pat_en:1; /* [1:1] */
		uint32_t trk_pat_en:1; /* [2:2] */
		uint32_t perlaneid_pat_en:1; /* [3:3] */
		uint32_t clkp_pat_en:1; /* [4:4] */
		uint32_t clkn_pat_en:1; /* [5:5] */
		uint32_t clkrd_pat_en:1; /* [6:6] */
		uint32_t no_vld_present_mode:1; /* [7:7] */
		uint32_t dynamic_seed_en:1; /* [8:8] */
		uint32_t txio_lpbk_en:1; /* [9:9] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg5 {
	struct {
		uint32_t locktimer_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg6 {
	struct {
		uint32_t val_conpat_thres_nt:8; /* [7:0] */
		uint32_t id_conpat_thres_nt:8; /* [15:8] */
		uint32_t clk_conpat_thres_nt:11; /* [26:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg0 {
	struct {
		uint32_t io0_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg1 {
	struct {
		uint32_t io1_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg10 {
	struct {
		uint32_t io10_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg11 {
	struct {
		uint32_t io11_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg12 {
	struct {
		uint32_t io12_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg13 {
	struct {
		uint32_t io13_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg14 {
	struct {
		uint32_t io14_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg15 {
	struct {
		uint32_t io15_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg16 {
	struct {
		uint32_t io16_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg17 {
	struct {
		uint32_t io17_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg18 {
	struct {
		uint32_t io18_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg19 {
	struct {
		uint32_t io19_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg2 {
	struct {
		uint32_t io2_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg20 {
	struct {
		uint32_t io20_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg21 {
	struct {
		uint32_t io21_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg22 {
	struct {
		uint32_t io22_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg23 {
	struct {
		uint32_t io23_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg24 {
	struct {
		uint32_t io24_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg25 {
	struct {
		uint32_t io25_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg26 {
	struct {
		uint32_t io26_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg27 {
	struct {
		uint32_t io27_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg28 {
	struct {
		uint32_t io28_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg29 {
	struct {
		uint32_t io29_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg3 {
	struct {
		uint32_t io3_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg30 {
	struct {
		uint32_t io30_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg31 {
	struct {
		uint32_t io31_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg32 {
	struct {
		uint32_t io32_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg33 {
	struct {
		uint32_t io33_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg34 {
	struct {
		uint32_t io34_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg35 {
	struct {
		uint32_t io35_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg36 {
	struct {
		uint32_t io36_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg37 {
	struct {
		uint32_t io37_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg38 {
	struct {
		uint32_t io38_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg39 {
	struct {
		uint32_t io39_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg4 {
	struct {
		uint32_t io4_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg40 {
	struct {
		uint32_t io40_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg41 {
	struct {
		uint32_t io41_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg42 {
	struct {
		uint32_t io42_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg43 {
	struct {
		uint32_t io43_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg44 {
	struct {
		uint32_t io44_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg45 {
	struct {
		uint32_t io45_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg46 {
	struct {
		uint32_t io46_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg47 {
	struct {
		uint32_t io47_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg48 {
	struct {
		uint32_t io48_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg49 {
	struct {
		uint32_t io49_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg5 {
	struct {
		uint32_t io5_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg50 {
	struct {
		uint32_t io50_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg51 {
	struct {
		uint32_t io51_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg52 {
	struct {
		uint32_t io52_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg53 {
	struct {
		uint32_t io53_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg54 {
	struct {
		uint32_t io54_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg55 {
	struct {
		uint32_t io55_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg56 {
	struct {
		uint32_t io56_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg57 {
	struct {
		uint32_t io57_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg58 {
	struct {
		uint32_t io58_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg59 {
	struct {
		uint32_t io59_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg6 {
	struct {
		uint32_t io6_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg60 {
	struct {
		uint32_t io60_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg61 {
	struct {
		uint32_t io61_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg62 {
	struct {
		uint32_t io62_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg63 {
	struct {
		uint32_t io63_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg64 {
	struct {
		uint32_t io64_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg65 {
	struct {
		uint32_t io65_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg66 {
	struct {
		uint32_t io66_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg67 {
	struct {
		uint32_t io67_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg68 {
	struct {
		uint32_t io68_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg69 {
	struct {
		uint32_t io69_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg7 {
	struct {
		uint32_t io7_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg70 {
	struct {
		uint32_t io70_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg71 {
	struct {
		uint32_t io71_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg72 {
	struct {
		uint32_t io72_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg73 {
	struct {
		uint32_t io73_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg8 {
	struct {
		uint32_t io8_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg9 {
	struct {
		uint32_t io9_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_clr {
	struct {
		uint32_t pi:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_piack_rdreg {
	struct {
		uint32_t nde:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_pictrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_pireq {
	struct {
		uint32_t nde:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_pival {
	struct {
		uint32_t nde:7; /* [6:0] */
		uint32_t nde_dir:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_pival_rdreg {
	struct {
		uint32_t nde:7; /* [6:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhip_rdreg1 {
	struct {
		uint32_t rxcmn_cal_comp_out_a:1; /* [0:0] */
		uint32_t nde_cpt_sync_a:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipcmn_reg1 {
	struct {
		uint32_t bias_en_nt:1; /* [0:0] */
		uint32_t nde_cpt_en_a:1; /* [1:1] */
		uint32_t comp_polarity_a:1; /* [2:2] */
		uint32_t gearbox_nt:2; /* [4:3] */
		uint32_t ical_decoder_a:3; /* [7:5] */
		uint32_t pi_cal_en_nt:1; /* [8:8] */
		uint32_t qcal_decoder_a:3; /* [11:9] */
		uint32_t shp_sel_nt:8; /* [19:12] */
		uint32_t vref_sel_a:7; /* [26:20] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipcmnio_reg1 {
	struct {
		uint32_t cal_sel_a:3; /* [2:0] */
		uint32_t lpbken_a:2; /* [4:3] */
		uint32_t halfrate_prbs_en_a:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipcmnio_reg2 {
	struct {
		uint32_t gearbox_nt:2; /* [1:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipcmnio_reg3 {
	struct {
		uint32_t atest_sel_nt:7; /* [6:0] */
		uint32_t atest_nt:4; /* [10:7] */
		uint32_t samp_offset_cal_en_a:3; /* [13:11] */
		uint32_t rxhipcmnio_cmnmux_reg3_atest_sel_nt:7; /* [20:14] */
		uint32_t rxhipcmnio_cmnmux_reg3_atest_nt:4; /* [24:21] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipctrl_reg1 {
	struct {
		uint32_t pd_ba:1; /* [0:0] */
		uint32_t rst_ba:1; /* [1:1] */
		uint32_t clkgate_en_a:1; /* [2:2] */
		uint32_t rxio_en_a:1; /* [3:3] */
		uint32_t rst_clk2path_div2_ba:1; /* [4:4] */
		uint32_t rst_lpbk_prbs_ba:1; /* [5:5] */
		uint32_t rst_nde_cpt_ba:1; /* [6:6] */
		uint32_t rst_pclkgen_ba:1; /* [7:7] */
		uint32_t rst_pclkgen_nde_cpt_ba:1; /* [8:8] */
		uint32_t rst_s2p_ff_ba:1; /* [9:9] */
		uint32_t rst_vref_ba:1; /* [10:10] */
		uint32_t rst_fifo_ba:1; /* [11:11] */
		uint32_t rst_tia_delaycell_ba:1; /* [12:12] */
		uint32_t rst_clkdet_div4_ba:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipdqs_reg1 {
	struct {
		uint32_t atest_sel_nt:4; /* [3:0] */
		uint32_t clk2path_ctle_degenc_a:2; /* [5:4] */
		uint32_t clk2path_ctle_degenr_a:2; /* [7:6] */
		uint32_t clk2path_ctle_en_nt:1; /* [8:8] */
		uint32_t mux_gm_nmos_a:5; /* [13:9] */
		uint32_t mux_gm_pmos_a:5; /* [18:14] */
		uint32_t mux_mode_sel_a:3; /* [21:19] */
		uint32_t mux_res_a:3; /* [24:22] */
		uint32_t nde_cpt_en_a:1; /* [25:25] */
		uint32_t nde_sel_a:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipdqs_reg2 {
	struct {
		uint32_t pclkgen_en_a:1; /* [0:0] */
		uint32_t pclkgen_gearbox_nt:2; /* [2:1] */
		uint32_t pd_polarity_a:1; /* [3:3] */
		uint32_t rate_sel_nt:1; /* [4:4] */
		uint32_t clkdet_en_a:1; /* [5:5] */
		uint32_t fifo_ctrl_nt:2; /* [7:6] */
		uint32_t fifo_ctrl_gearbox_nt:2; /* [9:8] */
		uint32_t fifo_ctrl_rx_div2_en_nt:1; /* [10:10] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipio_reg1 {
	struct {
		uint32_t delaybuffer_nmos_slice_en_a:2; /* [1:0] */
		uint32_t delaybuffer_pmos_slice_en_a:2; /* [3:2] */
		uint32_t delaybuffer_res_a:2; /* [5:4] */
		uint32_t delaycell_nmos_slice_en_a:2; /* [7:6] */
		uint32_t delaycell_pmos_slice_en_a:2; /* [9:8] */
		uint32_t delaycell_res_a:2; /* [11:10] */
		uint32_t tia_nmos_en_a:5; /* [16:12] */
		uint32_t tia_pmos_en_a:5; /* [21:17] */
		uint32_t tia_res_a:3; /* [24:22] */
		uint32_t vref_ctrl_a:7; /* [31:25] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiondesync_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiondesync_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiondesync_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiosampler_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiosampler_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipiosampler_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg1 {
	struct {
		uint32_t tia_delaycell_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg10 {
	struct {
		uint32_t vref270_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg11 {
	struct {
		uint32_t vref270_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg12 {
	struct {
		uint32_t vref270_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg13 {
	struct {
		uint32_t vref90_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg14 {
	struct {
		uint32_t vref90_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg15 {
	struct {
		uint32_t vref90_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg2 {
	struct {
		uint32_t tia_delaycell_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg3 {
	struct {
		uint32_t tia_delaycell_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg4 {
	struct {
		uint32_t vref0_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg5 {
	struct {
		uint32_t vref0_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg6 {
	struct {
		uint32_t vref0_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg7 {
	struct {
		uint32_t vref180_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg8 {
	struct {
		uint32_t vref180_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipload_reg9 {
	struct {
		uint32_t vref180_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipspare_rdreg1 {
	struct {
		uint32_t cmn_in_a:3; /* [2:0] */
		uint32_t rdqs_in_a:4; /* [6:3] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipspare_reg1 {
	struct {
		uint32_t cmn_out_nt:3; /* [2:0] */
		uint32_t rxio_out_nt:4; /* [6:3] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxhipspare_reg2 {
	struct {
		uint32_t rdqs_out_nt:4; /* [3:0] */
		uint32_t rtrk_out_nt:4; /* [7:4] */
		uint32_t rvld_out_nt:4; /* [11:8] */
		uint32_t rrdvld__out_nt:4; /* [15:12] */
		uint32_t rxiord0_out_nt:4; /* [19:16] */
		uint32_t rxiord1_out_nt:4; /* [23:20] */
		uint32_t rxiord2_out_nt:4; /* [27:24] */
		uint32_t rxiord3_out_nt:4; /* [31:28] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioctrl_reg1 {
	struct {
		uint32_t nde_use_clk:1; /* [0:0] */
		uint32_t ndedat_polarity:1; /* [1:1] */
		uint32_t nde_delay:2; /* [3:2] */
		uint32_t dat_polarity:1; /* [4:4] */
		uint32_t lb_polarity:1; /* [5:5] */
		uint32_t flit_pat_chk_en:1; /* [6:6] */
		uint32_t shift_vld:1; /* [7:7] */
		uint32_t retimer_en:1; /* [8:8] */
		uint32_t valid_err_tol_value:2; /* [10:9] */
		uint32_t framing_err_chk_en:1; /* [11:11] */
		uint32_t bit_slip_en:1; /* [12:12] */
		uint32_t bit_slip_flop_stg_nt:2; /* [14:13] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioctrl_reg2 {
	struct {
		uint32_t framing_err:1; /* [0:0] */
		uint32_t bit_slip_detect:1; /* [1:1] */
		uint32_t bit_slip_data:16; /* [17:2] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_afe_ovr_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgate_en:1; /* [1:1] */
		uint32_t clkgate:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_afe_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_afe_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_afe_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_data_ovr_reg1 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_data_ovr_reg2 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_data_ovr_reg3 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_ovr_reg1 {
	struct {
		uint32_t datapath_en:1; /* [0:0] */
		uint32_t datchk_en:1; /* [1:1] */
		uint32_t ndealign_en:1; /* [2:2] */
		uint32_t ndesync_en:1; /* [3:3] */
		uint32_t ndechk_en:1; /* [4:4] */
		uint32_t retpi_en:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxioen_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndealign_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndealign_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t target_nt:1; /* [1:1] */
		uint32_t dir_nt:1; /* [2:2] */
		uint32_t meas_threshold_nt:6; /* [8:3] */
		uint32_t step_nt:7; /* [15:9] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndealign_reg2 {
	struct {
		uint32_t max_iter_nt:16; /* [15:0] */
		uint32_t meas_cnt_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_rdreg1 {
	struct {
		uint32_t err_cnt:16; /* [15:0] */
		uint32_t done:1; /* [16:16] */
		uint32_t running:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_rdreg2 {
	struct {
		uint32_t err_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_rdreg3 {
	struct {
		uint32_t err_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_rdreg4 {
	struct {
		uint32_t err_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t nde_sel_nt:4; /* [4:1] */
		uint32_t err_cnt_sel:7; /* [11:5] */
		uint32_t clk_sel_nt:1; /* [12:12] */
		uint32_t mode:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_reg2 {
	struct {
		uint32_t err_thres_nt:16; /* [15:0] */
		uint32_t timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndechk_reg3 {
	struct {
		uint32_t offset_err_thres_nt:16; /* [15:0] */
		uint32_t offset_timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndesync_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndesync_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndesync_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t meas_val:1; /* [2:2] */
		uint32_t running:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndesync_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:1; /* [1:1] */
		uint32_t final_val_en_nt:1; /* [2:2] */
		uint32_t final_val_nt:1; /* [3:3] */
		uint32_t meas_threshold_nt:6; /* [9:4] */
		uint32_t polarity_nt:1; /* [10:10] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxndesync_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxretpi_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t dir:1; /* [1:1] */
		uint32_t err:1; /* [2:2] */
		uint32_t meas_val:1; /* [3:3] */
		uint32_t running:1; /* [4:4] */
		uint32_t left_val:7; /* [11:5] */
		uint32_t right_val:7; /* [18:12] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxretpi_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:2; /* [2:1] */
		uint32_t bist_sel_nt:1; /* [3:3] */
		uint32_t final_val_en_nt:1; /* [4:4] */
		uint32_t final_val_nt:1; /* [5:5] */
		uint32_t max_distance_nt:6; /* [11:6] */
		uint32_t meas_threshold_nt:6; /* [17:12] */
		uint32_t shift_offset_nt:6; /* [23:18] */
		uint32_t measonly_nt:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxretpi_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxretpi_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxretpi_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxrst_reg1 {
	struct {
		uint32_t loopback_ba:1; /* [0:0] */
		uint32_t rx_ba:1; /* [1:1] */
		uint32_t ndechk_ba:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxsip_clr {
	struct {
		uint32_t retpi:1; /* [0:0] */
		uint32_t ndealign:1; /* [1:1] */
		uint32_t ndesync:1; /* [2:2] */
		uint32_t timer1:1; /* [3:3] */
		uint32_t timer2:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxsoc_rdreg {
	struct {
		uint32_t rxen:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxsoc_reg1 {
	struct {
		uint32_t rst_ovr_b:1; /* [0:0] */
		uint32_t rst_ovr_en:1; /* [1:1] */
		uint32_t rxen_ovr_a:1; /* [2:2] */
		uint32_t rxen_ovr_en_a:1; /* [3:3] */
		uint32_t valid_en_a:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer1_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer1_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer1_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer2_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer2_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxtimer2_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxclkchk_rdreg2 {
	struct {
		uint32_t clkn_detect_succ_stat:1; /* [0:0] */
		uint32_t clkp_detect_succ_stat:1; /* [1:1] */
		uint32_t clkrd_detect_succ_stat:1; /* [2:2] */
		uint32_t trk_detect_succ_stat:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxclkchk_config1 {
	struct {
		uint32_t rxclkchk_thres_nt:16; /* [15:0] */
		uint32_t rxclkchk_trkdet_en_a:1; /* [16:16] */
		uint32_t rxclkchk_clkn_en:1; /* [17:17] */
		uint32_t rxclkchk_clkp_en:1; /* [18:18] */
		uint32_t rxclkchk_clkrd_en:1; /* [19:19] */
		uint32_t rxclkchk_trk_en:1; /* [20:20] */
		uint32_t rxclkchk_clk_edge_detect_thres_nt:3; /* [23:21] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_int1 {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int1:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int1:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int1:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int1:1; /* [3:3] */
		uint32_t rxdatchk_complete_int1:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int1:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int1:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_int1_mask {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int1_mask:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int1_mask:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int1_mask:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int1_mask:1; /* [3:3] */
		uint32_t rxdatchk_complete_int1_mask:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int1_mask:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int1_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_int2 {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int2:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int2:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int2:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int2:1; /* [3:3] */
		uint32_t rxdatchk_complete_int2:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int2:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int2:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_int2_mask {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int2_mask:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int2_mask:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int2_mask:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int2_mask:1; /* [3:3] */
		uint32_t rxdatchk_complete_int2_mask:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int2_mask:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int2_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxclkchk_rdreg3 {
	struct {
		uint32_t clkrd_cnt:16; /* [15:0] */
		uint32_t trk_cnt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg13 {
	struct {
		uint32_t agg_err_cnt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_rdreg14 {
	struct {
		uint32_t agg_succ:1; /* [0:0] */
		uint32_t agg_err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx0_reg_rxdatchk_reg14 {
	struct {
		uint32_t agg_err_thres_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_tx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_tx_ctrl {
	struct {
		uint32_t power:1; /* [0:0] */
		uint32_t instr_req:1; /* [1:1] */
		uint32_t instr_type:4; /* [5:2] */
		uint32_t loopback:2; /* [7:6] */
		uint32_t failed:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_tx_ctrl_rdreg {
	struct {
		uint32_t power_stat:1; /* [0:0] */
		uint32_t instr_ack:1; /* [1:1] */
		uint32_t state:4; /* [5:2] */
		uint32_t reset_done:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txcalen {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t qcc:1; /* [1:1] */
		uint32_t txsync:1; /* [2:2] */
		uint32_t retpi:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txcmn_reg1 {
	struct {
		uint32_t cmn_info; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txcmn_reg2 {
	struct {
		uint32_t dncal:8; /* [7:0] */
		uint32_t upcal:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg0 {
	struct {
		uint32_t shift_right_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg1 {
	struct {
		uint32_t shift_right_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg2 {
	struct {
		uint32_t shift_left_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg3 {
	struct {
		uint32_t shift_left_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg4 {
	struct {
		uint32_t scrm_en_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatapath_reg5 {
	struct {
		uint32_t scrm_en_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg0 {
	struct {
		uint32_t vec_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg1 {
	struct {
		uint32_t vec_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg10 {
	struct {
		uint32_t vec_10; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg11 {
	struct {
		uint32_t vec_11; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg12 {
	struct {
		uint32_t vec_12; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg13 {
	struct {
		uint32_t vec_13; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg14 {
	struct {
		uint32_t vec_14; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg15 {
	struct {
		uint32_t vec_15; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg16 {
	struct {
		uint32_t vec_16; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg2 {
	struct {
		uint32_t vec_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg3 {
	struct {
		uint32_t vec_3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg4 {
	struct {
		uint32_t vec_4; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg5 {
	struct {
		uint32_t vec_5; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg6 {
	struct {
		uint32_t vec_6; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg7 {
	struct {
		uint32_t vec_7; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg8 {
	struct {
		uint32_t vec_8; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_perlaneid_reg9 {
	struct {
		uint32_t vec_9; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_rdreg {
	struct {
		uint32_t running:1; /* [0:0] */
		uint32_t clk_running:1; /* [1:1] */
		uint32_t clkpat_complete_stat:1; /* [2:2] */
		uint32_t datpat_complete_stat:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgen_en:1; /* [1:1] */
		uint32_t continuous_clk_mode:1; /* [2:2] */
		uint32_t out_en:1; /* [3:3] */
		uint32_t pat_sel_nt:4; /* [7:4] */
		uint32_t position_nt:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg10 {
	struct {
		uint32_t err_inject_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg11 {
	struct {
		uint32_t clkn_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg12 {
	struct {
		uint32_t clkn_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg13 {
	struct {
		uint32_t clkrd_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg14 {
	struct {
		uint32_t clkrd_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg15 {
	struct {
		uint32_t trk_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg16 {
	struct {
		uint32_t trk_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg17 {
	struct {
		uint32_t clk_iterations_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg18 {
	struct {
		uint32_t clkn_default:16; /* [15:0] */
		uint32_t clkp_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg19 {
	struct {
		uint32_t trk_default:16; /* [15:0] */
		uint32_t clkrd_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg2 {
	struct {
		uint32_t err_pattern_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg20 {
	struct {
		uint32_t burst_mode_pause_en:1; /* [0:0] */
		uint32_t burst_mode_pause_select:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg21 {
	struct {
		uint32_t burst_mode_pause_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg3 {
	struct {
		uint32_t valtrain_vec_nt:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg4 {
	struct {
		uint32_t clkp_pat_en:1; /* [0:0] */
		uint32_t clkn_pat_en:1; /* [1:1] */
		uint32_t clkrd_pat_en:1; /* [2:2] */
		uint32_t val_pat_en:1; /* [3:3] */
		uint32_t valrd_pat_en:1; /* [4:4] */
		uint32_t trk_pat_en:1; /* [5:5] */
		uint32_t perlaneid_pat_en:1; /* [6:6] */
		uint32_t iterat_for_val:1; /* [7:7] */
		uint32_t pat_sel_48b:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg5 {
	struct {
		uint32_t clkp_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg6 {
	struct {
		uint32_t clkp_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg7 {
	struct {
		uint32_t iterations_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg8 {
	struct {
		uint32_t err_inject_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_reg9 {
	struct {
		uint32_t err_inject_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg0 {
	struct {
		uint32_t io0_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg1 {
	struct {
		uint32_t io1_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg10 {
	struct {
		uint32_t io10_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg11 {
	struct {
		uint32_t io11_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg12 {
	struct {
		uint32_t io12_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg13 {
	struct {
		uint32_t io13_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg14 {
	struct {
		uint32_t io14_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg15 {
	struct {
		uint32_t io15_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg16 {
	struct {
		uint32_t io16_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg17 {
	struct {
		uint32_t io17_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg18 {
	struct {
		uint32_t io18_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg19 {
	struct {
		uint32_t io19_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg2 {
	struct {
		uint32_t io2_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg20 {
	struct {
		uint32_t io20_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg21 {
	struct {
		uint32_t io21_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg22 {
	struct {
		uint32_t io22_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg23 {
	struct {
		uint32_t io23_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg24 {
	struct {
		uint32_t io24_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg25 {
	struct {
		uint32_t io25_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg26 {
	struct {
		uint32_t io26_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg27 {
	struct {
		uint32_t io27_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg28 {
	struct {
		uint32_t io28_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg29 {
	struct {
		uint32_t io29_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg3 {
	struct {
		uint32_t io3_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg30 {
	struct {
		uint32_t io30_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg31 {
	struct {
		uint32_t io31_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg32 {
	struct {
		uint32_t io32_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg33 {
	struct {
		uint32_t io33_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg34 {
	struct {
		uint32_t io34_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg35 {
	struct {
		uint32_t io35_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg36 {
	struct {
		uint32_t io36_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg37 {
	struct {
		uint32_t io37_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg38 {
	struct {
		uint32_t io38_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg39 {
	struct {
		uint32_t io39_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg4 {
	struct {
		uint32_t io4_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg40 {
	struct {
		uint32_t io40_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg41 {
	struct {
		uint32_t io41_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg42 {
	struct {
		uint32_t io42_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg43 {
	struct {
		uint32_t io43_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg44 {
	struct {
		uint32_t io44_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg45 {
	struct {
		uint32_t io45_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg46 {
	struct {
		uint32_t io46_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg47 {
	struct {
		uint32_t io47_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg48 {
	struct {
		uint32_t io48_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg49 {
	struct {
		uint32_t io49_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg5 {
	struct {
		uint32_t io5_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg50 {
	struct {
		uint32_t io50_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg51 {
	struct {
		uint32_t io51_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg52 {
	struct {
		uint32_t io52_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg53 {
	struct {
		uint32_t io53_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg54 {
	struct {
		uint32_t io54_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg55 {
	struct {
		uint32_t io55_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg56 {
	struct {
		uint32_t io56_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg57 {
	struct {
		uint32_t io57_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg58 {
	struct {
		uint32_t io58_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg59 {
	struct {
		uint32_t io59_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg6 {
	struct {
		uint32_t io6_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg60 {
	struct {
		uint32_t io60_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg61 {
	struct {
		uint32_t io61_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg62 {
	struct {
		uint32_t io62_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg63 {
	struct {
		uint32_t io63_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg64 {
	struct {
		uint32_t io64_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg65 {
	struct {
		uint32_t io65_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg66 {
	struct {
		uint32_t io66_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg67 {
	struct {
		uint32_t io67_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg68 {
	struct {
		uint32_t io68_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg69 {
	struct {
		uint32_t io69_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg7 {
	struct {
		uint32_t io7_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg70 {
	struct {
		uint32_t io70_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg71 {
	struct {
		uint32_t io71_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg72 {
	struct {
		uint32_t io72_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg73 {
	struct {
		uint32_t io73_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg8 {
	struct {
		uint32_t io8_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_seed_udp_reg9 {
	struct {
		uint32_t io9_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_bg_reg1 {
	struct {
		uint32_t iter_nt:16; /* [15:0] */
		uint32_t mu_dir_nt:1; /* [16:16] */
		uint32_t mu_nt:5; /* [21:17] */
		uint32_t range_nt:3; /* [24:22] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:6; /* [5:0] */
		uint32_t mu_coarse_dir_nt:1; /* [6:6] */
		uint32_t mu_coarse_nt:5; /* [11:7] */
		uint32_t mu_fine_dir_nt:1; /* [12:12] */
		uint32_t mu_fine_nt:5; /* [17:13] */
		uint32_t stop_dirchng_cnt_nt:5; /* [22:18] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t running:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t bg_nt:1; /* [1:1] */
		uint32_t ctrl_sel_nt:3; /* [4:2] */
		uint32_t final_val_en_nt:1; /* [5:5] */
		uint32_t final_val_nt:1; /* [6:6] */
		uint32_t flip_en_nt:2; /* [8:7] */
		uint32_t polarity_nt:5; /* [13:9] */
		uint32_t min_nt:6; /* [19:14] */
		uint32_t max_nt:6; /* [25:20] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdcc_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_clr {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t pi:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_dccack_rdreg {
	struct {
		uint32_t ck4i:1; /* [0:0] */
		uint32_t ck4q:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_dccctrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
		uint32_t doublezero_nt:2; /* [17:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_dccreq {
	struct {
		uint32_t ck4i:1; /* [0:0] */
		uint32_t ck4q:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_dccval {
	struct {
		uint32_t ck4i:6; /* [5:0] */
		uint32_t ck4q:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_dccval_rdreg {
	struct {
		uint32_t ck4i:6; /* [5:0] */
		uint32_t ck4q:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_piack_rdreg {
	struct {
		uint32_t ck4_0:1; /* [0:0] */
		uint32_t ck4_0_nde_lpbk:1; /* [1:1] */
		uint32_t ck4_90:1; /* [2:2] */
		uint32_t ck4_90_nde_lpbk:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_pictrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
		uint32_t ck4_90_slave:1; /* [16:16] */
		uint32_t ck4_0_nde_lpbk_slave:1; /* [17:17] */
		uint32_t ck4_90_nde_lpbk_slave:1; /* [18:18] */
		uint32_t ck4_90_nde_lpbk_slave_sel:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_pireq {
	struct {
		uint32_t ck4_0:1; /* [0:0] */
		uint32_t ck4_0_nde_lpbk:1; /* [1:1] */
		uint32_t ck4_90:1; /* [2:2] */
		uint32_t ck4_90_nde_lpbk:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_pival {
	struct {
		uint32_t ck4_0:7; /* [6:0] */
		uint32_t ck4_0_dir:1; /* [7:7] */
		uint32_t ck4_0_nde_lpbk:7; /* [14:8] */
		uint32_t ck4_0_nde_lpbk_dir:1; /* [15:15] */
		uint32_t ck4_90:7; /* [22:16] */
		uint32_t ck4_90_dir:1; /* [23:23] */
		uint32_t ck4_90_nde_lpbk:7; /* [30:24] */
		uint32_t ck4_90_nde_lpbk_dir:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_pival_rdreg {
	struct {
		uint32_t ck4_0:7; /* [6:0] */
		uint32_t ck4_0_nde_lpbk:7; /* [13:7] */
		uint32_t ck4_90:7; /* [20:14] */
		uint32_t ck4_90_nde_lpbk:7; /* [27:21] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhip_rdreg1 {
	struct {
		uint32_t txcmn_cal_comp_out_a:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipcmn_reg1 {
	struct {
		uint32_t comp_flip_a:1; /* [0:0] */
		uint32_t vref_cntrl_a:8; /* [8:1] */
		uint32_t ical_decoder_nt:3; /* [11:9] */
		uint32_t qcal_decoder_nt:3; /* [14:12] */
		uint32_t pi_cal_en_nt:1; /* [15:15] */
		uint32_t pi_shp_sel_nt:8; /* [23:16] */
		uint32_t pi_cml2cmos_en_nt:2; /* [25:24] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipcmnio_reg1 {
	struct {
		uint32_t cal_sel_a:3; /* [2:0] */
		uint32_t eqen_a:1; /* [3:3] */
		uint32_t gearbox_nt:2; /* [5:4] */
		uint32_t load_cntrl_a:2; /* [7:6] */
		uint32_t lpbken_a:2; /* [9:8] */
		uint32_t stgen_nt:2; /* [11:10] */
		uint32_t vddqmode_nt:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipcmnio_reg2 {
	struct {
		uint32_t dncal_a:8; /* [7:0] */
		uint32_t upcal_a:8; /* [15:8] */
		uint32_t eqdncal_a:8; /* [23:16] */
		uint32_t equpcal_a:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipcmnio_reg3 {
	struct {
		uint32_t atest_sel_nt:7; /* [6:0] */
		uint32_t atest_nt:4; /* [10:7] */
		uint32_t loadpulse_retime_nt:2; /* [12:11] */
		uint32_t lpbkmode_nt:2; /* [14:13] */
		uint32_t txhipcmnio_cmnmux_reg3_atest_sel_nt:7; /* [21:15] */
		uint32_t txhipcmnio_cmnmux_reg3_atest_nt:4; /* [25:22] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipctrl_reg1 {
	struct {
		uint32_t pd_ba:1; /* [0:0] */
		uint32_t rst_ba:1; /* [1:1] */
		uint32_t rst_fifo_ba:1; /* [2:2] */
		uint32_t wdqs_en_a:1; /* [3:3] */
		uint32_t clkgate_en_a:1; /* [4:4] */
		uint32_t txio_en_a:1; /* [5:5] */
		uint32_t rst_div4_ba:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipio {
	struct {
		uint32_t dl_ph_sel_a:5; /* [4:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipiosync_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipiosync_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipiosync_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipload_reg1 {
	struct {
		uint32_t dl_ph_sel_load_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipload_reg2 {
	struct {
		uint32_t dl_ph_sel_load_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipload_reg3 {
	struct {
		uint32_t dl_ph_sel_load_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipspare_rdreg1 {
	struct {
		uint32_t cmn_in_a:3; /* [2:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipspare_reg1 {
	struct {
		uint32_t ttrk_out_nt:1; /* [0:0] */
		uint32_t tvld_out_nt:1; /* [1:1] */
		uint32_t cmn_out_nt:3; /* [4:2] */
		uint32_t wdqs_c_out_nt:1; /* [5:5] */
		uint32_t wdqs_t_out_nt:1; /* [6:6] */
		uint32_t txio_out_nt:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txhipspare_reg2 {
	struct {
		uint32_t trdck_out_nt:1; /* [0:0] */
		uint32_t trdvld_out_nt:1; /* [1:1] */
		uint32_t txiord0_out_nt:1; /* [2:2] */
		uint32_t txiord1_out_nt:1; /* [3:3] */
		uint32_t txiord2_out_nt:1; /* [4:4] */
		uint32_t txiord3_out_nt:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg1 {
	struct {
		uint32_t clk_polarity_nt:1; /* [0:0] */
		uint32_t clkgate_delay_nt:4; /* [4:1] */
		uint32_t dat_polarity:1; /* [5:5] */
		uint32_t lb_polarity:1; /* [6:6] */
		uint32_t lane_reverse:1; /* [7:7] */
		uint32_t normal_mode:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg10 {
	struct {
		uint32_t val_vec:16; /* [15:0] */
		uint32_t valrd_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg11 {
	struct {
		uint32_t hiz_pstm_vec:2; /* [1:0] */
		uint32_t hiz_fidle_vec:2; /* [3:2] */
		uint32_t hiz_lidle_vec:2; /* [5:4] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg12 {
	struct {
		uint32_t clkp_pat_en:1; /* [0:0] */
		uint32_t clkn_pat_en:1; /* [1:1] */
		uint32_t val_pat_en:1; /* [2:2] */
		uint32_t valrd_pat_en:1; /* [3:3] */
		uint32_t clkrd_pat_en:1; /* [4:4] */
		uint32_t trk_pat_en:1; /* [5:5] */
		uint32_t val_io_dis:1; /* [6:6] */
		uint32_t valrd_io_dis:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg13 {
	struct {
		uint32_t gen_clkp_default:16; /* [15:0] */
		uint32_t gen_clkn_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg14 {
	struct {
		uint32_t gen_trk_default:16; /* [15:0] */
		uint32_t gen_clkrd_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg15 {
	struct {
		uint32_t postamble_count_max:3; /* [2:0] */
		uint32_t clk_parking_level_toggle_en:1; /* [3:3] */
		uint32_t clkn_shift:1; /* [4:4] */
		uint32_t clkp_shift:1; /* [5:5] */
		uint32_t trk_shift:1; /* [6:6] */
		uint32_t tvld_shift:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg16 {
	struct {
		uint32_t clkp_pstm_last_vec:16; /* [15:0] */
		uint32_t clkn_pstm_last_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg17 {
	struct {
		uint32_t trk_pstm_last_vec:16; /* [15:0] */
		uint32_t clkrd_pstm_last_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg18 {
	struct {
		uint32_t hiz_pstm_last_vec:2; /* [1:0] */
		uint32_t hiz_dly_select:4; /* [5:2] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg2 {
	struct {
		uint32_t clkp_nor_vec:16; /* [15:0] */
		uint32_t clkp_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg3 {
	struct {
		uint32_t clkp_fidle_vec:16; /* [15:0] */
		uint32_t clkp_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg4 {
	struct {
		uint32_t clkn_nor_vec:16; /* [15:0] */
		uint32_t clkn_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg5 {
	struct {
		uint32_t clkn_fidle_vec:16; /* [15:0] */
		uint32_t clkn_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg6 {
	struct {
		uint32_t clkrd_nor_vec:16; /* [15:0] */
		uint32_t clkrd_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg7 {
	struct {
		uint32_t clkrd_fidle_vec:16; /* [15:0] */
		uint32_t clkrd_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg8 {
	struct {
		uint32_t trk_nor_vec:16; /* [15:0] */
		uint32_t trk_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioctrl_reg9 {
	struct {
		uint32_t trk_fidle_vec:16; /* [15:0] */
		uint32_t trk_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgate_en:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_data_ovr_reg1 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_data_ovr_reg2 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_data_ovr_reg3 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_ovr_reg1 {
	struct {
		uint32_t datapath_en:1; /* [0:0] */
		uint32_t txsync_en:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txqcc_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txqcc_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:1; /* [1:1] */
		uint32_t final_val_en_nt:1; /* [2:2] */
		uint32_t final_val_nt:1; /* [3:3] */
		uint32_t flip_en_nt:1; /* [4:4] */
		uint32_t polarity_nt:1; /* [5:5] */
		uint32_t max_distance_nt:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txqcc_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txqcc_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txqcc_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txretpi_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t dir:1; /* [1:1] */
		uint32_t err:1; /* [2:2] */
		uint32_t meas_val:1; /* [3:3] */
		uint32_t running:1; /* [4:4] */
		uint32_t left_val:7; /* [11:5] */
		uint32_t right_val:7; /* [18:12] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txretpi_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:2; /* [2:1] */
		uint32_t final_val_en_nt:1; /* [3:3] */
		uint32_t final_val_nt:1; /* [4:4] */
		uint32_t max_distance_nt:6; /* [10:5] */
		uint32_t meas_threshold_nt:6; /* [16:11] */
		uint32_t shift_offset_nt:6; /* [22:17] */
		uint32_t measonly_nt:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txretpi_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txretpi_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txretpi_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txrst_reg1 {
	struct {
		uint32_t loopback_ba:1; /* [0:0] */
		uint32_t tx_ba:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsip_clr {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t qcc:1; /* [1:1] */
		uint32_t retpi:1; /* [2:2] */
		uint32_t txsync:1; /* [3:3] */
		uint32_t timer1:1; /* [4:4] */
		uint32_t timer2:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsoc_rdreg {
	struct {
		uint32_t txen:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsoc_reg1 {
	struct {
		uint32_t ready_en_a:1; /* [0:0] */
		uint32_t rst_ovr_b:1; /* [1:1] */
		uint32_t rst_ovr_en:1; /* [2:2] */
		uint32_t txen_ovr_a:1; /* [3:3] */
		uint32_t txen_ovr_en_a:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_bg_reg1 {
	struct {
		uint32_t iter_nt:16; /* [15:0] */
		uint32_t mu_dir_nt:1; /* [16:16] */
		uint32_t mu_nt:5; /* [21:17] */
		uint32_t range_nt:3; /* [24:22] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t meas_val:1; /* [2:2] */
		uint32_t running:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t bg_nt:1; /* [1:1] */
		uint32_t ctrl_sel_nt:1; /* [2:2] */
		uint32_t final_val_en_nt:1; /* [3:3] */
		uint32_t final_val_nt:1; /* [4:4] */
		uint32_t meas_threshold_nt:6; /* [10:5] */
		uint32_t polarity_nt:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txsync_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer1_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer1_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer1_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer2_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer2_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txtimer2_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_int1 {
	struct {
		uint32_t txdatgen_clkpat_complete_int1:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int1:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_int1_mask {
	struct {
		uint32_t txdatgen_clkpat_complete_int1_mask:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int1_mask:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_int2 {
	struct {
		uint32_t txdatgen_clkpat_complete_int2:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int2:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txdatgen_int2_mask {
	struct {
		uint32_t txdatgen_clkpat_complete_int2_mask:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int2_mask:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg5 {
	struct {
		uint32_t clkgate_f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg6 {
	struct {
		uint32_t clkgate_f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx0_reg_txioen_afe_ovr_reg7 {
	struct {
		uint32_t clkgate_f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_reg_sb_afe_cfg1 {
	struct {
		uint32_t ictl_rxclksb_en:1; /* [0:0] */
		uint32_t ictl_rxdatasb_en:1; /* [1:1] */
		uint32_t ictl_txclksb_en:1; /* [2:2] */
		uint32_t ictl_txdatasb_en:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_reg_sb_afe_cfg2 {
	struct {
		uint32_t ictl_rxclksbrd_en:1; /* [0:0] */
		uint32_t ictl_rxdatasbrd_en:1; /* [1:1] */
		uint32_t ictl_txclksbrd_en:1; /* [2:2] */
		uint32_t ictl_txdatasbrd_en:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_reg_sb_cmn_reset_cfg {
	struct {
		uint32_t clk_state_rst:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rst_reg1 {
	struct {
		uint32_t sb_ba:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsb_afifo_cfg {
	struct {
		uint32_t wm_high:8; /* [7:0] */
		uint32_t wm_low:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsb_cfg {
	struct {
		uint32_t pat_en:1; /* [0:0] */
		uint32_t cpat_value:8; /* [8:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_sfifo_int1_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_sfifo_int1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsb_rdreg1 {
	struct {
		uint32_t pattern_lock:1; /* [0:0] */
		uint32_t result:4; /* [4:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbacccom_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbacccom_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t status:3; /* [24:22] */
		uint32_t dstid:3; /* [27:25] */
		uint32_t dp:1; /* [28:28] */
		uint32_t cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbacccom_rdreg2 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbacccom_rdreg3 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbacccom_rdreg4 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t dp:1; /* [22:22] */
		uint32_t cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_rdreg2 {
	struct {
		uint32_t addr:24; /* [23:0] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbaccreq_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t msgcode:8; /* [12:5] */
		uint32_t srcid:3; /* [15:13] */
		uint32_t dp:1; /* [16:16] */
		uint32_t cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_rdreg2 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbmsg_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t msgcode:8; /* [12:5] */
		uint32_t srcid:3; /* [15:13] */
		uint32_t dp:1; /* [16:16] */
		uint32_t cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_rdreg2 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_rxsbvmsg_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_soc_reg1 {
	struct {
		uint32_t clk_en_a:1; /* [0:0] */
		uint32_t sbclk_en_a:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_afifo_cfg {
	struct {
		uint32_t wm_high:8; /* [7:0] */
		uint32_t wm_low:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t txsb_type:3; /* [24:22] */
		uint32_t status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg10 {
	struct {
		uint32_t idle_value:20; /* [19:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg11 {
	struct {
		uint32_t remote_rx_result:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg2 {
	struct {
		uint32_t addr:24; /* [23:0] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg3 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg4 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg5 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg6 {
	struct {
		uint32_t msgcode:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg7 {
	struct {
		uint32_t execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg8 {
	struct {
		uint32_t pat_en:1; /* [0:0] */
		uint32_t cpat_value:8; /* [8:1] */
		uint32_t lpat_value:8; /* [16:9] */
		uint32_t more_value:4; /* [20:17] */
		uint32_t max_8ms_value:8; /* [28:21] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_cfg9 {
	struct {
		uint32_t to_1ms_value:20; /* [19:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_txsb_stall_rdreg1 {
	struct {
		uint32_t accreq_wr_ok:1; /* [0:0] */
		uint32_t acccom_wr_ok:1; /* [1:1] */
		uint32_t msg_wr_ok:1; /* [2:2] */
		uint32_t vmsg_wr_ok:1; /* [3:3] */
		uint32_t reserved_bit_0:8;
		uint32_t timeout_cntr_triggered_8ms_int1_mask:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_afifo_int1_mask {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int1_mask:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int1_mask:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int1_mask:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int1_mask:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_afifo_int1 {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int1:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int1:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int1:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int1:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int1:1; /* [11:11] */
		uint32_t timeout_cntr_triggered_8ms_int1:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_sfifo_int2_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_sfifo_int2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_afifo_int2_mask {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int2_mask:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int2_mask:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int2_mask:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int2_mask:1; /* [11:11] */
		uint32_t timeout_cntr_triggered_8ms_int2_mask:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_afifo_int2 {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int2:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int2:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int2:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int2:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int2:1; /* [11:11] */
		uint32_t timeout_cntr_triggered_8ms_int2:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_timeout_count_config1_reg {
	struct {
		uint32_t timeout_cntr_en:1; /* [0:0] */
		uint32_t timeout_cntr_start:1; /* [1:1] */
		uint32_t timeout_cntr_stall:1; /* [2:2] */
		uint32_t timeout_cntr_stop:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_timeout_count_config2_reg {
	struct {
		uint32_t timeout_cntr_no_cycles_for_8ms; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb0_reg_sb_rx_cntrl_config_reg {
	struct {
		uint32_t rxsb_ignore_bb_same_msg:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_clk_ctrl {
	struct {
		uint32_t isolate_en_a:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_dfx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_dfx_ctrl {
	struct {
		uint32_t test_en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_dfx_stat_rdreg {
	struct {
		uint32_t test_state:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_boot_addr {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_crash_dump0 {
	struct {
		uint32_t excep_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_crash_dump1 {
	struct {
		uint32_t last_data_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_crash_dump2 {
	struct {
		uint32_t nxt_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_crash_dump3 {
	struct {
		uint32_t curr_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_ctrl {
	struct {
		uint32_t reset_n_a:1; /* [0:0] */
		uint32_t clk_en_a:1; /* [1:1] */
		uint32_t fetch_en_a:1; /* [2:2] */
		uint32_t dble_fault_seen_clr_a:1; /* [3:3] */
		uint32_t time_out_threshold_nt:10; /* [13:4] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_device_addr {
	struct {
		uint32_t base_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_dmem {
	struct {
		uint32_t alias_addr_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_hart_id {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_irq {
	struct {
		uint32_t flag:15; /* [14:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl1 {
	struct {
		uint32_t edge_sel_nt:30; /* [29:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl2 {
	struct {
		uint32_t det_type_nt:15; /* [14:0] */
		uint32_t clear_a:15; /* [29:15] */
		uint32_t software_irq_a:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_dfx0_reg_lane_mcu_stats {
	struct {
		uint32_t core_sleep:1; /* [0:0] */
		uint32_t dble_fault_seen:1; /* [1:1] */
		uint32_t dmactive:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rx_ctrl {
	struct {
		uint32_t power:1; /* [0:0] */
		uint32_t instr_req:1; /* [1:1] */
		uint32_t instr_type:4; /* [5:2] */
		uint32_t loopback:2; /* [7:6] */
		uint32_t failed:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rx_ctrl_rdreg {
	struct {
		uint32_t power_stat:1; /* [0:0] */
		uint32_t instr_ack:1; /* [1:1] */
		uint32_t state:4; /* [5:2] */
		uint32_t reset_done:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxcalen {
	struct {
		uint32_t ndealign:1; /* [0:0] */
		uint32_t offset:1; /* [1:1] */
		uint32_t dcc:1; /* [2:2] */
		uint32_t qcc:1; /* [3:3] */
		uint32_t txsync:1; /* [4:4] */
		uint32_t retpi:1; /* [5:5] */
		uint32_t retvref:1; /* [6:6] */
		uint32_t retpbd:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxclkchk_rdreg {
	struct {
		uint32_t clkn_cnt:16; /* [15:0] */
		uint32_t clkp_cnt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxcmn_reg1 {
	struct {
		uint32_t cmn_info; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxcmn_reg2 {
	struct {
		uint32_t dncal:8; /* [7:0] */
		uint32_t upcal:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg0 {
	struct {
		uint32_t shift_right_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg1 {
	struct {
		uint32_t shift_right_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg2 {
	struct {
		uint32_t shift_right_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg3 {
	struct {
		uint32_t shift_left_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg4 {
	struct {
		uint32_t shift_left_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatapath_reg5 {
	struct {
		uint32_t shift_left_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatcap_rdreg1 {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatcap_rdreg2 {
	struct {
		uint32_t val; /* [31:0] */
	};
	uint32_t reg_val;
};

union aw_ucie_rx1_reg_rxdatcap_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t sel:6; /* [6:1] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg0 {
	struct {
		uint32_t vec_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg1 {
	struct {
		uint32_t vec_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg10 {
	struct {
		uint32_t vec_10; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg11 {
	struct {
		uint32_t vec_11; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg12 {
	struct {
		uint32_t vec_12; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg13 {
	struct {
		uint32_t vec_13; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg14 {
	struct {
		uint32_t vec_14; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg15 {
	struct {
		uint32_t vec_15; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg16 {
	struct {
		uint32_t vec_16; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg2 {
	struct {
		uint32_t vec_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg3 {
	struct {
		uint32_t vec_3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg4 {
	struct {
		uint32_t vec_4; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg5 {
	struct {
		uint32_t vec_5; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg6 {
	struct {
		uint32_t vec_6; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg7 {
	struct {
		uint32_t vec_7; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg8 {
	struct {
		uint32_t vec_8; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg9 {
	struct {
		uint32_t vec_9; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg1 {
	struct {
		uint32_t cnt:16; /* [15:0] */
		uint32_t lock:1; /* [16:16] */
		uint32_t running:1; /* [17:17] */
		uint32_t done:1; /* [18:18] */
		uint32_t complete_stat:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg10 {
	struct {
		uint32_t succ_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg11 {
	struct {
		uint32_t succ_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg12 {
	struct {
		uint32_t succ_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg2 {
	struct {
		uint32_t err_cnt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg3 {
	struct {
		uint32_t err_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg4 {
	struct {
		uint32_t err_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg5 {
	struct {
		uint32_t err_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg1 {
	struct {
		uint32_t cmn_seed_nt:1; /* [0:0] */
		uint32_t en:1; /* [1:1] */
		uint32_t mode_nt:1; /* [2:2] */
		uint32_t pat_sel_nt:4; /* [6:3] */
		uint32_t err_cnt_sel:7; /* [13:7] */
		uint32_t subset_nt:2; /* [15:14] */
		uint32_t trylock_num_nt:5; /* [20:16] */
		uint32_t position_nt:1; /* [21:21] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg13 {
	struct {
		uint32_t burst_mode_en:1; /* [0:0] */
		uint32_t force_last_check_en:1; /* [1:1] */
		uint32_t force_last_check:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg2 {
	struct {
		uint32_t err_thres_nt:16; /* [15:0] */
		uint32_t timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg3 {
	struct {
		uint32_t valtrain_vec_nt:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg4 {
	struct {
		uint32_t val_pat_en:1; /* [0:0] */
		uint32_t valrd_pat_en:1; /* [1:1] */
		uint32_t trk_pat_en:1; /* [2:2] */
		uint32_t perlaneid_pat_en:1; /* [3:3] */
		uint32_t clkp_pat_en:1; /* [4:4] */
		uint32_t clkn_pat_en:1; /* [5:5] */
		uint32_t clkrd_pat_en:1; /* [6:6] */
		uint32_t no_vld_present_mode:1; /* [7:7] */
		uint32_t dynamic_seed_en:1; /* [8:8] */
		uint32_t txio_lpbk_en:1; /* [9:9] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg5 {
	struct {
		uint32_t locktimer_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg6 {
	struct {
		uint32_t val_conpat_thres_nt:8; /* [7:0] */
		uint32_t id_conpat_thres_nt:8; /* [15:8] */
		uint32_t clk_conpat_thres_nt:11; /* [26:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg0 {
	struct {
		uint32_t io0_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg1 {
	struct {
		uint32_t io1_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg10 {
	struct {
		uint32_t io10_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg11 {
	struct {
		uint32_t io11_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg12 {
	struct {
		uint32_t io12_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg13 {
	struct {
		uint32_t io13_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg14 {
	struct {
		uint32_t io14_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg15 {
	struct {
		uint32_t io15_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg16 {
	struct {
		uint32_t io16_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg17 {
	struct {
		uint32_t io17_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg18 {
	struct {
		uint32_t io18_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg19 {
	struct {
		uint32_t io19_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg2 {
	struct {
		uint32_t io2_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg20 {
	struct {
		uint32_t io20_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg21 {
	struct {
		uint32_t io21_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg22 {
	struct {
		uint32_t io22_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg23 {
	struct {
		uint32_t io23_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg24 {
	struct {
		uint32_t io24_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg25 {
	struct {
		uint32_t io25_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg26 {
	struct {
		uint32_t io26_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg27 {
	struct {
		uint32_t io27_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg28 {
	struct {
		uint32_t io28_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg29 {
	struct {
		uint32_t io29_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg3 {
	struct {
		uint32_t io3_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg30 {
	struct {
		uint32_t io30_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg31 {
	struct {
		uint32_t io31_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg32 {
	struct {
		uint32_t io32_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg33 {
	struct {
		uint32_t io33_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg34 {
	struct {
		uint32_t io34_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg35 {
	struct {
		uint32_t io35_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg36 {
	struct {
		uint32_t io36_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg37 {
	struct {
		uint32_t io37_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg38 {
	struct {
		uint32_t io38_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg39 {
	struct {
		uint32_t io39_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg4 {
	struct {
		uint32_t io4_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg40 {
	struct {
		uint32_t io40_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg41 {
	struct {
		uint32_t io41_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg42 {
	struct {
		uint32_t io42_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg43 {
	struct {
		uint32_t io43_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg44 {
	struct {
		uint32_t io44_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg45 {
	struct {
		uint32_t io45_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg46 {
	struct {
		uint32_t io46_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg47 {
	struct {
		uint32_t io47_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg48 {
	struct {
		uint32_t io48_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg49 {
	struct {
		uint32_t io49_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg5 {
	struct {
		uint32_t io5_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg50 {
	struct {
		uint32_t io50_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg51 {
	struct {
		uint32_t io51_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg52 {
	struct {
		uint32_t io52_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg53 {
	struct {
		uint32_t io53_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg54 {
	struct {
		uint32_t io54_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg55 {
	struct {
		uint32_t io55_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg56 {
	struct {
		uint32_t io56_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg57 {
	struct {
		uint32_t io57_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg58 {
	struct {
		uint32_t io58_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg59 {
	struct {
		uint32_t io59_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg6 {
	struct {
		uint32_t io6_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg60 {
	struct {
		uint32_t io60_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg61 {
	struct {
		uint32_t io61_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg62 {
	struct {
		uint32_t io62_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg63 {
	struct {
		uint32_t io63_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg64 {
	struct {
		uint32_t io64_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg65 {
	struct {
		uint32_t io65_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg66 {
	struct {
		uint32_t io66_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg67 {
	struct {
		uint32_t io67_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg68 {
	struct {
		uint32_t io68_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg69 {
	struct {
		uint32_t io69_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg7 {
	struct {
		uint32_t io7_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg70 {
	struct {
		uint32_t io70_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg71 {
	struct {
		uint32_t io71_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg72 {
	struct {
		uint32_t io72_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg73 {
	struct {
		uint32_t io73_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg8 {
	struct {
		uint32_t io8_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg9 {
	struct {
		uint32_t io9_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_clr {
	struct {
		uint32_t pi:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_piack_rdreg {
	struct {
		uint32_t nde:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_pictrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_pireq {
	struct {
		uint32_t nde:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_pival {
	struct {
		uint32_t nde:7; /* [6:0] */
		uint32_t nde_dir:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_pival_rdreg {
	struct {
		uint32_t nde:7; /* [6:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhip_rdreg1 {
	struct {
		uint32_t rxcmn_cal_comp_out_a:1; /* [0:0] */
		uint32_t nde_cpt_sync_a:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipcmn_reg1 {
	struct {
		uint32_t bias_en_nt:1; /* [0:0] */
		uint32_t nde_cpt_en_a:1; /* [1:1] */
		uint32_t comp_polarity_a:1; /* [2:2] */
		uint32_t gearbox_nt:2; /* [4:3] */
		uint32_t ical_decoder_a:3; /* [7:5] */
		uint32_t pi_cal_en_nt:1; /* [8:8] */
		uint32_t qcal_decoder_a:3; /* [11:9] */
		uint32_t shp_sel_nt:8; /* [19:12] */
		uint32_t vref_sel_a:7; /* [26:20] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipcmnio_reg1 {
	struct {
		uint32_t cal_sel_a:3; /* [2:0] */
		uint32_t lpbken_a:2; /* [4:3] */
		uint32_t halfrate_prbs_en_a:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipcmnio_reg2 {
	struct {
		uint32_t gearbox_nt:2; /* [1:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipcmnio_reg3 {
	struct {
		uint32_t atest_sel_nt:7; /* [6:0] */
		uint32_t atest_nt:4; /* [10:7] */
		uint32_t samp_offset_cal_en_a:3; /* [13:11] */
		uint32_t rxhipcmnio_cmnmux_reg3_atest_sel_nt:7; /* [20:14] */
		uint32_t rxhipcmnio_cmnmux_reg3_atest_nt:4; /* [24:21] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipctrl_reg1 {
	struct {
		uint32_t pd_ba:1; /* [0:0] */
		uint32_t rst_ba:1; /* [1:1] */
		uint32_t clkgate_en_a:1; /* [2:2] */
		uint32_t rxio_en_a:1; /* [3:3] */
		uint32_t rst_clk2path_div2_ba:1; /* [4:4] */
		uint32_t rst_lpbk_prbs_ba:1; /* [5:5] */
		uint32_t rst_nde_cpt_ba:1; /* [6:6] */
		uint32_t rst_pclkgen_ba:1; /* [7:7] */
		uint32_t rst_pclkgen_nde_cpt_ba:1; /* [8:8] */
		uint32_t rst_s2p_ff_ba:1; /* [9:9] */
		uint32_t rst_vref_ba:1; /* [10:10] */
		uint32_t rst_fifo_ba:1; /* [11:11] */
		uint32_t rst_tia_delaycell_ba:1; /* [12:12] */
		uint32_t rst_clkdet_div4_ba:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipdqs_reg1 {
	struct {
		uint32_t atest_sel_nt:4; /* [3:0] */
		uint32_t clk2path_ctle_degenc_a:2; /* [5:4] */
		uint32_t clk2path_ctle_degenr_a:2; /* [7:6] */
		uint32_t clk2path_ctle_en_nt:1; /* [8:8] */
		uint32_t mux_gm_nmos_a:5; /* [13:9] */
		uint32_t mux_gm_pmos_a:5; /* [18:14] */
		uint32_t mux_mode_sel_a:3; /* [21:19] */
		uint32_t mux_res_a:3; /* [24:22] */
		uint32_t nde_cpt_en_a:1; /* [25:25] */
		uint32_t nde_sel_a:1; /* [26:26] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipdqs_reg2 {
	struct {
		uint32_t pclkgen_en_a:1; /* [0:0] */
		uint32_t pclkgen_gearbox_nt:2; /* [2:1] */
		uint32_t pd_polarity_a:1; /* [3:3] */
		uint32_t rate_sel_nt:1; /* [4:4] */
		uint32_t clkdet_en_a:1; /* [5:5] */
		uint32_t fifo_ctrl_nt:2; /* [7:6] */
		uint32_t fifo_ctrl_gearbox_nt:2; /* [9:8] */
		uint32_t fifo_ctrl_rx_div2_en_nt:1; /* [10:10] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipio_reg1 {
	struct {
		uint32_t delaybuffer_nmos_slice_en_a:2; /* [1:0] */
		uint32_t delaybuffer_pmos_slice_en_a:2; /* [3:2] */
		uint32_t delaybuffer_res_a:2; /* [5:4] */
		uint32_t delaycell_nmos_slice_en_a:2; /* [7:6] */
		uint32_t delaycell_pmos_slice_en_a:2; /* [9:8] */
		uint32_t delaycell_res_a:2; /* [11:10] */
		uint32_t tia_nmos_en_a:5; /* [16:12] */
		uint32_t tia_pmos_en_a:5; /* [21:17] */
		uint32_t tia_res_a:3; /* [24:22] */
		uint32_t vref_ctrl_a:7; /* [31:25] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiondesync_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiondesync_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiondesync_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiosampler_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiosampler_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipiosampler_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg1 {
	struct {
		uint32_t tia_delaycell_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg10 {
	struct {
		uint32_t vref270_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg11 {
	struct {
		uint32_t vref270_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg12 {
	struct {
		uint32_t vref270_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg13 {
	struct {
		uint32_t vref90_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg14 {
	struct {
		uint32_t vref90_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg15 {
	struct {
		uint32_t vref90_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg2 {
	struct {
		uint32_t tia_delaycell_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg3 {
	struct {
		uint32_t tia_delaycell_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg4 {
	struct {
		uint32_t vref0_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg5 {
	struct {
		uint32_t vref0_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg6 {
	struct {
		uint32_t vref0_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg7 {
	struct {
		uint32_t vref180_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg8 {
	struct {
		uint32_t vref180_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipload_reg9 {
	struct {
		uint32_t vref180_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipspare_rdreg1 {
	struct {
		uint32_t cmn_in_a:3; /* [2:0] */
		uint32_t rdqs_in_a:4; /* [6:3] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipspare_reg1 {
	struct {
		uint32_t cmn_out_nt:3; /* [2:0] */
		uint32_t rxio_out_nt:4; /* [6:3] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxhipspare_reg2 {
	struct {
		uint32_t rdqs_out_nt:4; /* [3:0] */
		uint32_t rtrk_out_nt:4; /* [7:4] */
		uint32_t rvld_out_nt:4; /* [11:8] */
		uint32_t rrdvld__out_nt:4; /* [15:12] */
		uint32_t rxiord0_out_nt:4; /* [19:16] */
		uint32_t rxiord1_out_nt:4; /* [23:20] */
		uint32_t rxiord2_out_nt:4; /* [27:24] */
		uint32_t rxiord3_out_nt:4; /* [31:28] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioctrl_reg1 {
	struct {
		uint32_t nde_use_clk:1; /* [0:0] */
		uint32_t ndedat_polarity:1; /* [1:1] */
		uint32_t nde_delay:2; /* [3:2] */
		uint32_t dat_polarity:1; /* [4:4] */
		uint32_t lb_polarity:1; /* [5:5] */
		uint32_t flit_pat_chk_en:1; /* [6:6] */
		uint32_t shift_vld:1; /* [7:7] */
		uint32_t retimer_en:1; /* [8:8] */
		uint32_t valid_err_tol_value:2; /* [10:9] */
		uint32_t framing_err_chk_en:1; /* [11:11] */
		uint32_t bit_slip_en:1; /* [12:12] */
		uint32_t bit_slip_flop_stg_nt:2; /* [14:13] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioctrl_reg2 {
	struct {
		uint32_t framing_err:1; /* [0:0] */
		uint32_t bit_slip_detect:1; /* [1:1] */
		uint32_t bit_slip_data:16; /* [17:2] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_afe_ovr_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgate_en:1; /* [1:1] */
		uint32_t clkgate:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_afe_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_afe_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_afe_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_data_ovr_reg1 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_data_ovr_reg2 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_data_ovr_reg3 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_ovr_reg1 {
	struct {
		uint32_t datapath_en:1; /* [0:0] */
		uint32_t datchk_en:1; /* [1:1] */
		uint32_t ndealign_en:1; /* [2:2] */
		uint32_t ndesync_en:1; /* [3:3] */
		uint32_t ndechk_en:1; /* [4:4] */
		uint32_t retpi_en:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxioen_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndealign_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndealign_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t target_nt:1; /* [1:1] */
		uint32_t dir_nt:1; /* [2:2] */
		uint32_t meas_threshold_nt:6; /* [8:3] */
		uint32_t step_nt:7; /* [15:9] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndealign_reg2 {
	struct {
		uint32_t max_iter_nt:16; /* [15:0] */
		uint32_t meas_cnt_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_rdreg1 {
	struct {
		uint32_t err_cnt:16; /* [15:0] */
		uint32_t done:1; /* [16:16] */
		uint32_t running:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_rdreg2 {
	struct {
		uint32_t err_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_rdreg3 {
	struct {
		uint32_t err_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_rdreg4 {
	struct {
		uint32_t err_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t nde_sel_nt:4; /* [4:1] */
		uint32_t err_cnt_sel:7; /* [11:5] */
		uint32_t clk_sel_nt:1; /* [12:12] */
		uint32_t mode:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_reg2 {
	struct {
		uint32_t err_thres_nt:16; /* [15:0] */
		uint32_t timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndechk_reg3 {
	struct {
		uint32_t offset_err_thres_nt:16; /* [15:0] */
		uint32_t offset_timer_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndesync_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndesync_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndesync_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t meas_val:1; /* [2:2] */
		uint32_t running:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndesync_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:1; /* [1:1] */
		uint32_t final_val_en_nt:1; /* [2:2] */
		uint32_t final_val_nt:1; /* [3:3] */
		uint32_t meas_threshold_nt:6; /* [9:4] */
		uint32_t polarity_nt:1; /* [10:10] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxndesync_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxretpi_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t dir:1; /* [1:1] */
		uint32_t err:1; /* [2:2] */
		uint32_t meas_val:1; /* [3:3] */
		uint32_t running:1; /* [4:4] */
		uint32_t left_val:7; /* [11:5] */
		uint32_t right_val:7; /* [18:12] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxretpi_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:2; /* [2:1] */
		uint32_t bist_sel_nt:1; /* [3:3] */
		uint32_t final_val_en_nt:1; /* [4:4] */
		uint32_t final_val_nt:1; /* [5:5] */
		uint32_t max_distance_nt:6; /* [11:6] */
		uint32_t meas_threshold_nt:6; /* [17:12] */
		uint32_t shift_offset_nt:6; /* [23:18] */
		uint32_t measonly_nt:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxretpi_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxretpi_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxretpi_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxrst_reg1 {
	struct {
		uint32_t loopback_ba:1; /* [0:0] */
		uint32_t rx_ba:1; /* [1:1] */
		uint32_t ndechk_ba:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxsip_clr {
	struct {
		uint32_t retpi:1; /* [0:0] */
		uint32_t ndealign:1; /* [1:1] */
		uint32_t ndesync:1; /* [2:2] */
		uint32_t timer1:1; /* [3:3] */
		uint32_t timer2:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxsoc_rdreg {
	struct {
		uint32_t rxen:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxsoc_reg1 {
	struct {
		uint32_t rst_ovr_b:1; /* [0:0] */
		uint32_t rst_ovr_en:1; /* [1:1] */
		uint32_t rxen_ovr_a:1; /* [2:2] */
		uint32_t rxen_ovr_en_a:1; /* [3:3] */
		uint32_t valid_en_a:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer1_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer1_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer1_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer2_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer2_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxtimer2_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxclkchk_rdreg2 {
	struct {
		uint32_t clkn_detect_succ_stat:1; /* [0:0] */
		uint32_t clkp_detect_succ_stat:1; /* [1:1] */
		uint32_t clkrd_detect_succ_stat:1; /* [2:2] */
		uint32_t trk_detect_succ_stat:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxclkchk_config1 {
	struct {
		uint32_t rxclkchk_thres_nt:16; /* [15:0] */
		uint32_t rxclkchk_trkdet_en_a:1; /* [16:16] */
		uint32_t rxclkchk_clkn_en:1; /* [17:17] */
		uint32_t rxclkchk_clkp_en:1; /* [18:18] */
		uint32_t rxclkchk_clkrd_en:1; /* [19:19] */
		uint32_t rxclkchk_trk_en:1; /* [20:20] */
		uint32_t rxclkchk_clk_edge_detect_thres_nt:3; /* [23:21] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_int1 {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int1:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int1:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int1:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int1:1; /* [3:3] */
		uint32_t rxdatchk_complete_int1:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int1:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int1:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_int1_mask {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int1_mask:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int1_mask:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int1_mask:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int1_mask:1; /* [3:3] */
		uint32_t rxdatchk_complete_int1_mask:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int1_mask:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int1_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_int2 {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int2:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int2:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int2:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int2:1; /* [3:3] */
		uint32_t rxdatchk_complete_int2:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int2:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int2:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_int2_mask {
	struct {
		uint32_t rxclkchk_clkn_detect_succ_int2_mask:1; /* [0:0] */
		uint32_t rxclkchk_clkp_detect_succ_int2_mask:1; /* [1:1] */
		uint32_t rxclkchk_clkrd_detect_succ_int2_mask:1; /* [2:2] */
		uint32_t rxclkchk_trk_detect_succ_int2_mask:1; /* [3:3] */
		uint32_t rxdatchk_complete_int2_mask:1; /* [4:4] */
		uint32_t rxdatchk_framing_err_int2_mask:1; /* [5:5] */
		uint32_t rxdatchk_bit_slip_err_int2_mask:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxclkchk_rdreg3 {
	struct {
		uint32_t clkrd_cnt:16; /* [15:0] */
		uint32_t trk_cnt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg13 {
	struct {
		uint32_t agg_err_cnt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_rdreg14 {
	struct {
		uint32_t agg_succ:1; /* [0:0] */
		uint32_t agg_err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_rx1_reg_rxdatchk_reg14 {
	struct {
		uint32_t agg_err_thres_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_tx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_tx_ctrl {
	struct {
		uint32_t power:1; /* [0:0] */
		uint32_t instr_req:1; /* [1:1] */
		uint32_t instr_type:4; /* [5:2] */
		uint32_t loopback:2; /* [7:6] */
		uint32_t failed:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_tx_ctrl_rdreg {
	struct {
		uint32_t power_stat:1; /* [0:0] */
		uint32_t instr_ack:1; /* [1:1] */
		uint32_t state:4; /* [5:2] */
		uint32_t reset_done:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txcalen {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t qcc:1; /* [1:1] */
		uint32_t txsync:1; /* [2:2] */
		uint32_t retpi:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txcmn_reg1 {
	struct {
		uint32_t cmn_info; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txcmn_reg2 {
	struct {
		uint32_t dncal:8; /* [7:0] */
		uint32_t upcal:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg0 {
	struct {
		uint32_t shift_right_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg1 {
	struct {
		uint32_t shift_right_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg2 {
	struct {
		uint32_t shift_left_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg3 {
	struct {
		uint32_t shift_left_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg4 {
	struct {
		uint32_t scrm_en_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatapath_reg5 {
	struct {
		uint32_t scrm_en_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg0 {
	struct {
		uint32_t vec_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg1 {
	struct {
		uint32_t vec_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg10 {
	struct {
		uint32_t vec_10; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg11 {
	struct {
		uint32_t vec_11; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg12 {
	struct {
		uint32_t vec_12; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg13 {
	struct {
		uint32_t vec_13; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg14 {
	struct {
		uint32_t vec_14; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg15 {
	struct {
		uint32_t vec_15; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg16 {
	struct {
		uint32_t vec_16; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg2 {
	struct {
		uint32_t vec_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg3 {
	struct {
		uint32_t vec_3; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg4 {
	struct {
		uint32_t vec_4; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg5 {
	struct {
		uint32_t vec_5; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg6 {
	struct {
		uint32_t vec_6; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg7 {
	struct {
		uint32_t vec_7; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg8 {
	struct {
		uint32_t vec_8; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_perlaneid_reg9 {
	struct {
		uint32_t vec_9; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_rdreg {
	struct {
		uint32_t running:1; /* [0:0] */
		uint32_t clk_running:1; /* [1:1] */
		uint32_t clkpat_complete_stat:1; /* [2:2] */
		uint32_t datpat_complete_stat:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgen_en:1; /* [1:1] */
		uint32_t continuous_clk_mode:1; /* [2:2] */
		uint32_t out_en:1; /* [3:3] */
		uint32_t pat_sel_nt:4; /* [7:4] */
		uint32_t position_nt:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg10 {
	struct {
		uint32_t err_inject_2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg11 {
	struct {
		uint32_t clkn_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg12 {
	struct {
		uint32_t clkn_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg13 {
	struct {
		uint32_t clkrd_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg14 {
	struct {
		uint32_t clkrd_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg15 {
	struct {
		uint32_t trk_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg16 {
	struct {
		uint32_t trk_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg17 {
	struct {
		uint32_t clk_iterations_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg18 {
	struct {
		uint32_t clkn_default:16; /* [15:0] */
		uint32_t clkp_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg19 {
	struct {
		uint32_t trk_default:16; /* [15:0] */
		uint32_t clkrd_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg2 {
	struct {
		uint32_t err_pattern_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg20 {
	struct {
		uint32_t burst_mode_pause_en:1; /* [0:0] */
		uint32_t burst_mode_pause_select:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg21 {
	struct {
		uint32_t burst_mode_pause_count; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg3 {
	struct {
		uint32_t valtrain_vec_nt:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg4 {
	struct {
		uint32_t clkp_pat_en:1; /* [0:0] */
		uint32_t clkn_pat_en:1; /* [1:1] */
		uint32_t clkrd_pat_en:1; /* [2:2] */
		uint32_t val_pat_en:1; /* [3:3] */
		uint32_t valrd_pat_en:1; /* [4:4] */
		uint32_t trk_pat_en:1; /* [5:5] */
		uint32_t perlaneid_pat_en:1; /* [6:6] */
		uint32_t iterat_for_val:1; /* [7:7] */
		uint32_t pat_sel_48b:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg5 {
	struct {
		uint32_t clkp_pat_vec_nt_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg6 {
	struct {
		uint32_t clkp_pat_vec_nt_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg7 {
	struct {
		uint32_t iterations_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg8 {
	struct {
		uint32_t err_inject_0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_reg9 {
	struct {
		uint32_t err_inject_1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg0 {
	struct {
		uint32_t io0_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg1 {
	struct {
		uint32_t io1_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg10 {
	struct {
		uint32_t io10_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg11 {
	struct {
		uint32_t io11_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg12 {
	struct {
		uint32_t io12_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg13 {
	struct {
		uint32_t io13_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg14 {
	struct {
		uint32_t io14_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg15 {
	struct {
		uint32_t io15_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg16 {
	struct {
		uint32_t io16_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg17 {
	struct {
		uint32_t io17_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg18 {
	struct {
		uint32_t io18_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg19 {
	struct {
		uint32_t io19_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg2 {
	struct {
		uint32_t io2_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg20 {
	struct {
		uint32_t io20_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg21 {
	struct {
		uint32_t io21_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg22 {
	struct {
		uint32_t io22_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg23 {
	struct {
		uint32_t io23_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg24 {
	struct {
		uint32_t io24_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg25 {
	struct {
		uint32_t io25_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg26 {
	struct {
		uint32_t io26_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg27 {
	struct {
		uint32_t io27_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg28 {
	struct {
		uint32_t io28_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg29 {
	struct {
		uint32_t io29_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg3 {
	struct {
		uint32_t io3_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg30 {
	struct {
		uint32_t io30_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg31 {
	struct {
		uint32_t io31_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg32 {
	struct {
		uint32_t io32_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg33 {
	struct {
		uint32_t io33_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg34 {
	struct {
		uint32_t io34_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg35 {
	struct {
		uint32_t io35_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg36 {
	struct {
		uint32_t io36_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg37 {
	struct {
		uint32_t io37_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg38 {
	struct {
		uint32_t io38_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg39 {
	struct {
		uint32_t io39_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg4 {
	struct {
		uint32_t io4_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg40 {
	struct {
		uint32_t io40_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg41 {
	struct {
		uint32_t io41_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg42 {
	struct {
		uint32_t io42_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg43 {
	struct {
		uint32_t io43_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg44 {
	struct {
		uint32_t io44_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg45 {
	struct {
		uint32_t io45_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg46 {
	struct {
		uint32_t io46_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg47 {
	struct {
		uint32_t io47_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg48 {
	struct {
		uint32_t io48_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg49 {
	struct {
		uint32_t io49_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg5 {
	struct {
		uint32_t io5_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg50 {
	struct {
		uint32_t io50_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg51 {
	struct {
		uint32_t io51_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg52 {
	struct {
		uint32_t io52_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg53 {
	struct {
		uint32_t io53_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg54 {
	struct {
		uint32_t io54_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg55 {
	struct {
		uint32_t io55_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg56 {
	struct {
		uint32_t io56_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg57 {
	struct {
		uint32_t io57_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg58 {
	struct {
		uint32_t io58_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg59 {
	struct {
		uint32_t io59_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg6 {
	struct {
		uint32_t io6_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg60 {
	struct {
		uint32_t io60_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg61 {
	struct {
		uint32_t io61_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg62 {
	struct {
		uint32_t io62_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg63 {
	struct {
		uint32_t io63_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg64 {
	struct {
		uint32_t io64_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg65 {
	struct {
		uint32_t io65_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg66 {
	struct {
		uint32_t io66_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg67 {
	struct {
		uint32_t io67_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg68 {
	struct {
		uint32_t io68_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg69 {
	struct {
		uint32_t io69_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg7 {
	struct {
		uint32_t io7_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg70 {
	struct {
		uint32_t io70_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg71 {
	struct {
		uint32_t io71_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg72 {
	struct {
		uint32_t io72_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg73 {
	struct {
		uint32_t io73_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg8 {
	struct {
		uint32_t io8_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_seed_udp_reg9 {
	struct {
		uint32_t io9_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_bg_reg1 {
	struct {
		uint32_t iter_nt:16; /* [15:0] */
		uint32_t mu_dir_nt:1; /* [16:16] */
		uint32_t mu_nt:5; /* [21:17] */
		uint32_t range_nt:3; /* [24:22] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:6; /* [5:0] */
		uint32_t mu_coarse_dir_nt:1; /* [6:6] */
		uint32_t mu_coarse_nt:5; /* [11:7] */
		uint32_t mu_fine_dir_nt:1; /* [12:12] */
		uint32_t mu_fine_nt:5; /* [17:13] */
		uint32_t stop_dirchng_cnt_nt:5; /* [22:18] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t running:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t bg_nt:1; /* [1:1] */
		uint32_t ctrl_sel_nt:3; /* [4:2] */
		uint32_t final_val_en_nt:1; /* [5:5] */
		uint32_t final_val_nt:1; /* [6:6] */
		uint32_t flip_en_nt:2; /* [8:7] */
		uint32_t polarity_nt:5; /* [13:9] */
		uint32_t min_nt:6; /* [19:14] */
		uint32_t max_nt:6; /* [25:20] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdcc_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_clr {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t pi:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_dccack_rdreg {
	struct {
		uint32_t ck4i:1; /* [0:0] */
		uint32_t ck4q:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_dccctrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
		uint32_t doublezero_nt:2; /* [17:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_dccreq {
	struct {
		uint32_t ck4i:1; /* [0:0] */
		uint32_t ck4q:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_dccval {
	struct {
		uint32_t ck4i:6; /* [5:0] */
		uint32_t ck4q:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_dccval_rdreg {
	struct {
		uint32_t ck4i:6; /* [5:0] */
		uint32_t ck4q:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_piack_rdreg {
	struct {
		uint32_t ck4_0:1; /* [0:0] */
		uint32_t ck4_0_nde_lpbk:1; /* [1:1] */
		uint32_t ck4_90:1; /* [2:2] */
		uint32_t ck4_90_nde_lpbk:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_pictrl {
	struct {
		uint32_t load_delay_post_nt:5; /* [4:0] */
		uint32_t load_delay_pre_nt:5; /* [9:5] */
		uint32_t load_width_nt:5; /* [14:10] */
		uint32_t load:1; /* [15:15] */
		uint32_t ck4_90_slave:1; /* [16:16] */
		uint32_t ck4_0_nde_lpbk_slave:1; /* [17:17] */
		uint32_t ck4_90_nde_lpbk_slave:1; /* [18:18] */
		uint32_t ck4_90_nde_lpbk_slave_sel:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_pireq {
	struct {
		uint32_t ck4_0:1; /* [0:0] */
		uint32_t ck4_0_nde_lpbk:1; /* [1:1] */
		uint32_t ck4_90:1; /* [2:2] */
		uint32_t ck4_90_nde_lpbk:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_pival {
	struct {
		uint32_t ck4_0:7; /* [6:0] */
		uint32_t ck4_0_dir:1; /* [7:7] */
		uint32_t ck4_0_nde_lpbk:7; /* [14:8] */
		uint32_t ck4_0_nde_lpbk_dir:1; /* [15:15] */
		uint32_t ck4_90:7; /* [22:16] */
		uint32_t ck4_90_dir:1; /* [23:23] */
		uint32_t ck4_90_nde_lpbk:7; /* [30:24] */
		uint32_t ck4_90_nde_lpbk_dir:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_pival_rdreg {
	struct {
		uint32_t ck4_0:7; /* [6:0] */
		uint32_t ck4_0_nde_lpbk:7; /* [13:7] */
		uint32_t ck4_90:7; /* [20:14] */
		uint32_t ck4_90_nde_lpbk:7; /* [27:21] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhip_rdreg1 {
	struct {
		uint32_t txcmn_cal_comp_out_a:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipcmn_reg1 {
	struct {
		uint32_t comp_flip_a:1; /* [0:0] */
		uint32_t vref_cntrl_a:8; /* [8:1] */
		uint32_t ical_decoder_nt:3; /* [11:9] */
		uint32_t qcal_decoder_nt:3; /* [14:12] */
		uint32_t pi_cal_en_nt:1; /* [15:15] */
		uint32_t pi_shp_sel_nt:8; /* [23:16] */
		uint32_t pi_cml2cmos_en_nt:2; /* [25:24] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipcmnio_reg1 {
	struct {
		uint32_t cal_sel_a:3; /* [2:0] */
		uint32_t eqen_a:1; /* [3:3] */
		uint32_t gearbox_nt:2; /* [5:4] */
		uint32_t load_cntrl_a:2; /* [7:6] */
		uint32_t lpbken_a:2; /* [9:8] */
		uint32_t stgen_nt:2; /* [11:10] */
		uint32_t vddqmode_nt:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipcmnio_reg2 {
	struct {
		uint32_t dncal_a:8; /* [7:0] */
		uint32_t upcal_a:8; /* [15:8] */
		uint32_t eqdncal_a:8; /* [23:16] */
		uint32_t equpcal_a:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipcmnio_reg3 {
	struct {
		uint32_t atest_sel_nt:7; /* [6:0] */
		uint32_t atest_nt:4; /* [10:7] */
		uint32_t loadpulse_retime_nt:2; /* [12:11] */
		uint32_t lpbkmode_nt:2; /* [14:13] */
		uint32_t txhipcmnio_cmnmux_reg3_atest_sel_nt:7; /* [21:15] */
		uint32_t txhipcmnio_cmnmux_reg3_atest_nt:4; /* [25:22] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipctrl_reg1 {
	struct {
		uint32_t pd_ba:1; /* [0:0] */
		uint32_t rst_ba:1; /* [1:1] */
		uint32_t rst_fifo_ba:1; /* [2:2] */
		uint32_t wdqs_en_a:1; /* [3:3] */
		uint32_t clkgate_en_a:1; /* [4:4] */
		uint32_t txio_en_a:1; /* [5:5] */
		uint32_t rst_div4_ba:1; /* [6:6] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipio {
	struct {
		uint32_t dl_ph_sel_a:5; /* [4:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipiosync_rdreg1 {
	struct {
		uint32_t f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipiosync_rdreg2 {
	struct {
		uint32_t f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipiosync_rdreg3 {
	struct {
		uint32_t f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipload_reg1 {
	struct {
		uint32_t dl_ph_sel_load_f0_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipload_reg2 {
	struct {
		uint32_t dl_ph_sel_load_f1_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipload_reg3 {
	struct {
		uint32_t dl_ph_sel_load_f2_a; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipspare_rdreg1 {
	struct {
		uint32_t cmn_in_a:3; /* [2:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipspare_reg1 {
	struct {
		uint32_t ttrk_out_nt:1; /* [0:0] */
		uint32_t tvld_out_nt:1; /* [1:1] */
		uint32_t cmn_out_nt:3; /* [4:2] */
		uint32_t wdqs_c_out_nt:1; /* [5:5] */
		uint32_t wdqs_t_out_nt:1; /* [6:6] */
		uint32_t txio_out_nt:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txhipspare_reg2 {
	struct {
		uint32_t trdck_out_nt:1; /* [0:0] */
		uint32_t trdvld_out_nt:1; /* [1:1] */
		uint32_t txiord0_out_nt:1; /* [2:2] */
		uint32_t txiord1_out_nt:1; /* [3:3] */
		uint32_t txiord2_out_nt:1; /* [4:4] */
		uint32_t txiord3_out_nt:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg1 {
	struct {
		uint32_t clk_polarity_nt:1; /* [0:0] */
		uint32_t clkgate_delay_nt:4; /* [4:1] */
		uint32_t dat_polarity:1; /* [5:5] */
		uint32_t lb_polarity:1; /* [6:6] */
		uint32_t lane_reverse:1; /* [7:7] */
		uint32_t normal_mode:1; /* [8:8] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg10 {
	struct {
		uint32_t val_vec:16; /* [15:0] */
		uint32_t valrd_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg11 {
	struct {
		uint32_t hiz_pstm_vec:2; /* [1:0] */
		uint32_t hiz_fidle_vec:2; /* [3:2] */
		uint32_t hiz_lidle_vec:2; /* [5:4] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg12 {
	struct {
		uint32_t clkp_pat_en:1; /* [0:0] */
		uint32_t clkn_pat_en:1; /* [1:1] */
		uint32_t val_pat_en:1; /* [2:2] */
		uint32_t valrd_pat_en:1; /* [3:3] */
		uint32_t clkrd_pat_en:1; /* [4:4] */
		uint32_t trk_pat_en:1; /* [5:5] */
		uint32_t val_io_dis:1; /* [6:6] */
		uint32_t valrd_io_dis:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg13 {
	struct {
		uint32_t gen_clkp_default:16; /* [15:0] */
		uint32_t gen_clkn_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg14 {
	struct {
		uint32_t gen_trk_default:16; /* [15:0] */
		uint32_t gen_clkrd_default:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg15 {
	struct {
		uint32_t postamble_count_max:3; /* [2:0] */
		uint32_t clk_parking_level_toggle_en:1; /* [3:3] */
		uint32_t clkn_shift:1; /* [4:4] */
		uint32_t clkp_shift:1; /* [5:5] */
		uint32_t trk_shift:1; /* [6:6] */
		uint32_t tvld_shift:1; /* [7:7] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg16 {
	struct {
		uint32_t clkp_pstm_last_vec:16; /* [15:0] */
		uint32_t clkn_pstm_last_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg17 {
	struct {
		uint32_t trk_pstm_last_vec:16; /* [15:0] */
		uint32_t clkrd_pstm_last_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg18 {
	struct {
		uint32_t hiz_pstm_last_vec:2; /* [1:0] */
		uint32_t hiz_dly_select:4; /* [5:2] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg2 {
	struct {
		uint32_t clkp_nor_vec:16; /* [15:0] */
		uint32_t clkp_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg3 {
	struct {
		uint32_t clkp_fidle_vec:16; /* [15:0] */
		uint32_t clkp_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg4 {
	struct {
		uint32_t clkn_nor_vec:16; /* [15:0] */
		uint32_t clkn_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg5 {
	struct {
		uint32_t clkn_fidle_vec:16; /* [15:0] */
		uint32_t clkn_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg6 {
	struct {
		uint32_t clkrd_nor_vec:16; /* [15:0] */
		uint32_t clkrd_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg7 {
	struct {
		uint32_t clkrd_fidle_vec:16; /* [15:0] */
		uint32_t clkrd_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg8 {
	struct {
		uint32_t trk_nor_vec:16; /* [15:0] */
		uint32_t trk_pstm_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioctrl_reg9 {
	struct {
		uint32_t trk_fidle_vec:16; /* [15:0] */
		uint32_t trk_lidle_vec:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t clkgate_en:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_data_ovr_reg1 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_data_ovr_reg2 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_data_ovr_reg3 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_ovr_reg1 {
	struct {
		uint32_t datapath_en:1; /* [0:0] */
		uint32_t txsync_en:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_ovr_reg2 {
	struct {
		uint32_t f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_ovr_reg3 {
	struct {
		uint32_t f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_ovr_reg4 {
	struct {
		uint32_t f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txqcc_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txqcc_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:1; /* [1:1] */
		uint32_t final_val_en_nt:1; /* [2:2] */
		uint32_t final_val_nt:1; /* [3:3] */
		uint32_t flip_en_nt:1; /* [4:4] */
		uint32_t polarity_nt:1; /* [5:5] */
		uint32_t max_distance_nt:6; /* [11:6] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txqcc_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txqcc_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txqcc_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txretpi_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t dir:1; /* [1:1] */
		uint32_t err:1; /* [2:2] */
		uint32_t meas_val:1; /* [3:3] */
		uint32_t running:1; /* [4:4] */
		uint32_t left_val:7; /* [11:5] */
		uint32_t right_val:7; /* [18:12] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txretpi_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t ctrl_sel_nt:2; /* [2:1] */
		uint32_t final_val_en_nt:1; /* [3:3] */
		uint32_t final_val_nt:1; /* [4:4] */
		uint32_t max_distance_nt:6; /* [10:5] */
		uint32_t meas_threshold_nt:6; /* [16:11] */
		uint32_t shift_offset_nt:6; /* [22:17] */
		uint32_t measonly_nt:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txretpi_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txretpi_reg3 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txretpi_reg4 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txrst_reg1 {
	struct {
		uint32_t loopback_ba:1; /* [0:0] */
		uint32_t tx_ba:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsip_clr {
	struct {
		uint32_t dcc:1; /* [0:0] */
		uint32_t qcc:1; /* [1:1] */
		uint32_t retpi:1; /* [2:2] */
		uint32_t txsync:1; /* [3:3] */
		uint32_t timer1:1; /* [4:4] */
		uint32_t timer2:1; /* [5:5] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsoc_rdreg {
	struct {
		uint32_t txen:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsoc_reg1 {
	struct {
		uint32_t ready_en_a:1; /* [0:0] */
		uint32_t rst_ovr_b:1; /* [1:1] */
		uint32_t rst_ovr_en:1; /* [2:2] */
		uint32_t txen_ovr_a:1; /* [3:3] */
		uint32_t txen_ovr_en_a:1; /* [4:4] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_bg_reg1 {
	struct {
		uint32_t iter_nt:16; /* [15:0] */
		uint32_t mu_dir_nt:1; /* [16:16] */
		uint32_t mu_nt:5; /* [21:17] */
		uint32_t range_nt:3; /* [24:22] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_fg_reg1 {
	struct {
		uint32_t coarse_step_nt:7; /* [6:0] */
		uint32_t mu_coarse_dir_nt:1; /* [7:7] */
		uint32_t mu_coarse_nt:5; /* [12:8] */
		uint32_t mu_fine_dir_nt:1; /* [13:13] */
		uint32_t mu_fine_nt:5; /* [18:14] */
		uint32_t stop_dirchng_cnt_nt:5; /* [23:19] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_fg_reg2 {
	struct {
		uint32_t coarse_iter_nt:16; /* [15:0] */
		uint32_t fine_iter_nt:16; /* [31:16] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_rdreg {
	struct {
		uint32_t ack:1; /* [0:0] */
		uint32_t err:1; /* [1:1] */
		uint32_t meas_val:1; /* [2:2] */
		uint32_t running:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_reg1 {
	struct {
		uint32_t req:1; /* [0:0] */
		uint32_t bg_nt:1; /* [1:1] */
		uint32_t ctrl_sel_nt:1; /* [2:2] */
		uint32_t final_val_en_nt:1; /* [3:3] */
		uint32_t final_val_nt:1; /* [4:4] */
		uint32_t meas_threshold_nt:6; /* [10:5] */
		uint32_t polarity_nt:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txsync_reg2 {
	struct {
		uint32_t meas_cnt_nt:16; /* [15:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer1_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer1_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer1_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer2_rdreg {
	struct {
		uint32_t done:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer2_reg1 {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txtimer2_reg2 {
	struct {
		uint32_t max; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_int1 {
	struct {
		uint32_t txdatgen_clkpat_complete_int1:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int1:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_int1_mask {
	struct {
		uint32_t txdatgen_clkpat_complete_int1_mask:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int1_mask:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_int2 {
	struct {
		uint32_t txdatgen_clkpat_complete_int2:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int2:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txdatgen_int2_mask {
	struct {
		uint32_t txdatgen_clkpat_complete_int2_mask:1; /* [0:0] */
		uint32_t txdatgen_datpat_complete_int2_mask:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg5 {
	struct {
		uint32_t clkgate_f0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg6 {
	struct {
		uint32_t clkgate_f1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_tx1_reg_txioen_afe_ovr_reg7 {
	struct {
		uint32_t clkgate_f2; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_reg_sb_afe_cfg1 {
	struct {
		uint32_t ictl_rxclksb_en:1; /* [0:0] */
		uint32_t ictl_rxdatasb_en:1; /* [1:1] */
		uint32_t ictl_txclksb_en:1; /* [2:2] */
		uint32_t ictl_txdatasb_en:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_reg_sb_afe_cfg2 {
	struct {
		uint32_t ictl_rxclksbrd_en:1; /* [0:0] */
		uint32_t ictl_rxdatasbrd_en:1; /* [1:1] */
		uint32_t ictl_txclksbrd_en:1; /* [2:2] */
		uint32_t ictl_txdatasbrd_en:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_reg_sb_cmn_reset_cfg {
	struct {
		uint32_t clk_state_rst:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rst_reg1 {
	struct {
		uint32_t sb_ba:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsb_afifo_cfg {
	struct {
		uint32_t wm_high:8; /* [7:0] */
		uint32_t wm_low:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsb_cfg {
	struct {
		uint32_t pat_en:1; /* [0:0] */
		uint32_t cpat_value:8; /* [8:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_sfifo_int1_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_sfifo_int1 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int1:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int1:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int1:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int1:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int1:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int1:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int1:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int1:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int1:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int1:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int1:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int1:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int1:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int1:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int1:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int1:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int1:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int1:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int1:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int1:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int1:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsb_rdreg1 {
	struct {
		uint32_t pattern_lock:1; /* [0:0] */
		uint32_t result:4; /* [4:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbacccom_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbacccom_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t status:3; /* [24:22] */
		uint32_t dstid:3; /* [27:25] */
		uint32_t dp:1; /* [28:28] */
		uint32_t cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbacccom_rdreg2 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbacccom_rdreg3 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbacccom_rdreg4 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t dp:1; /* [22:22] */
		uint32_t cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_rdreg2 {
	struct {
		uint32_t addr:24; /* [23:0] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbaccreq_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t msgcode:8; /* [12:5] */
		uint32_t srcid:3; /* [15:13] */
		uint32_t dp:1; /* [16:16] */
		uint32_t cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_rdreg2 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbmsg_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_cfg {
	struct {
		uint32_t rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_rdreg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t msgcode:8; /* [12:5] */
		uint32_t srcid:3; /* [15:13] */
		uint32_t dp:1; /* [16:16] */
		uint32_t cp:1; /* [17:17] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_rdreg2 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_rdreg3 {
	struct {
		uint32_t avail:1; /* [0:0] */
		uint32_t rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_rdreg4 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_rxsbvmsg_rdreg5 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_soc_reg1 {
	struct {
		uint32_t clk_en_a:1; /* [0:0] */
		uint32_t sbclk_en_a:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_afifo_cfg {
	struct {
		uint32_t wm_high:8; /* [7:0] */
		uint32_t wm_low:8; /* [15:8] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg1 {
	struct {
		uint32_t opcode:5; /* [4:0] */
		uint32_t ep:1; /* [5:5] */
		uint32_t be:8; /* [13:6] */
		uint32_t tag:5; /* [18:14] */
		uint32_t srcid:3; /* [21:19] */
		uint32_t txsb_type:3; /* [24:22] */
		uint32_t status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg10 {
	struct {
		uint32_t idle_value:20; /* [19:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg11 {
	struct {
		uint32_t remote_rx_result:4; /* [3:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg2 {
	struct {
		uint32_t addr:24; /* [23:0] */
		uint32_t dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg3 {
	struct {
		uint32_t data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg4 {
	struct {
		uint32_t data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg5 {
	struct {
		uint32_t msgsubcode:8; /* [7:0] */
		uint32_t msginfo:16; /* [23:8] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg6 {
	struct {
		uint32_t msgcode:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg7 {
	struct {
		uint32_t execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg8 {
	struct {
		uint32_t pat_en:1; /* [0:0] */
		uint32_t cpat_value:8; /* [8:1] */
		uint32_t lpat_value:8; /* [16:9] */
		uint32_t more_value:4; /* [20:17] */
		uint32_t max_8ms_value:8; /* [28:21] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_cfg9 {
	struct {
		uint32_t to_1ms_value:20; /* [19:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_txsb_stall_rdreg1 {
	struct {
		uint32_t accreq_wr_ok:1; /* [0:0] */
		uint32_t acccom_wr_ok:1; /* [1:1] */
		uint32_t msg_wr_ok:1; /* [2:2] */
		uint32_t vmsg_wr_ok:1; /* [3:3] */
		uint32_t reserved_bit_0:8;
		uint32_t timeout_cntr_triggered_8ms_int1_mask:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_afifo_int1_mask {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int1_mask:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int1_mask:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int1_mask:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int1_mask:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_afifo_int1 {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int1:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int1:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int1:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int1:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int1:1; /* [11:11] */
		uint32_t timeout_cntr_triggered_8ms_int1:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_sfifo_int2_mask {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2_mask:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2_mask:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2_mask:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2_mask:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2_mask:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2_mask:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2_mask:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2_mask:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2_mask:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2_mask:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2_mask:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2_mask:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2_mask:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2_mask:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2_mask:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2_mask:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2_mask:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2_mask:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2_mask:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2_mask:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_sfifo_int2 {
	struct {
		uint32_t txsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t txsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t txsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t txsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t txsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_accreq_sfifo_ovf_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_accreq_sfifo_unf_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_acccom_sfifo_ovf_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_acccom_sfifo_unf_err_int2:1; /* [11:11] */
		uint32_t rxsb_fifo_err_msg_sfifo_ovf_err_int2:1; /* [12:12] */
		uint32_t rxsb_fifo_err_msg_sfifo_unf_err_int2:1; /* [13:13] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_ovf_err_int2:1; /* [14:14] */
		uint32_t rxsb_fifo_err_vmsg_sfifo_unf_err_int2:1; /* [15:15] */
		uint32_t rxsb_fifo_err_stat_accreq_hdr_parity_err_int2:1; /* [16:16] */
		uint32_t rxsb_fifo_err_stat_accreq_dat_parity_err_int2:1; /* [17:17] */
		uint32_t rxsb_fifo_err_stat_acccom_hdr_parity_err_int2:1; /* [18:18] */
		uint32_t rxsb_fifo_err_stat_acccom_dat_parity_err_int2:1; /* [19:19] */
		uint32_t rxsb_fifo_err_stat_msg_hdr_parity_err_int2:1; /* [20:20] */
		uint32_t rxsb_fifo_err_stat_msg_dat_parity_err_int2:1; /* [21:21] */
		uint32_t rxsb_fifo_err_stat_vmsg_hdr_parity_err_int2:1; /* [22:22] */
		uint32_t rxsb_fifo_err_stat_vmsg_dat_parity_err_int2:1; /* [23:23] */
		uint32_t rxsb_accreq_avail_int2:1; /* [24:24] */
		uint32_t rxsb_accreq_rdready_int2:1; /* [25:25] */
		uint32_t rxsb_acccom_avail_int2:1; /* [26:26] */
		uint32_t rxsb_acccom_rdready_int2:1; /* [27:27] */
		uint32_t rxsb_msg_avail_int2:1; /* [28:28] */
		uint32_t rxsb_msg_rdready_int2:1; /* [29:29] */
		uint32_t rxsb_vmsg_avail_int2:1; /* [30:30] */
		uint32_t rxsb_vmsg_rdready_int2:1; /* [31:31] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_afifo_int2_mask {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int2_mask:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int2_mask:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int2_mask:1; /* [10:10] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_afifo_int2 {
	struct {
		uint32_t txsb_fifo_err_afifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_afifo_unf_err_int2:1; /* [1:1] */
		uint32_t rxsb_fifo_err_afifo_ovf_err_int2:4; /* [5:2] */
		uint32_t rxsb_fifo_err_afifo_unf_err_int2:4; /* [9:6] */
		uint32_t rxsb_rdreg1_pattern_lock_int2:1; /* [10:10] */
		uint32_t txsb_clock_pattern_done_int2:1; /* [11:11] */
		uint32_t timeout_cntr_triggered_8ms_int2:1; /* [12:12] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_timeout_count_config1_reg {
	struct {
		uint32_t timeout_cntr_en:1; /* [0:0] */
		uint32_t timeout_cntr_start:1; /* [1:1] */
		uint32_t timeout_cntr_stall:1; /* [2:2] */
		uint32_t timeout_cntr_stop:1; /* [3:3] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_timeout_count_config2_reg {
	struct {
		uint32_t timeout_cntr_no_cycles_for_8ms; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_sb1_reg_sb_rx_cntrl_config_reg {
	struct {
		uint32_t rxsb_ignore_bb_same_msg:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_clk_ctrl {
	struct {
		uint32_t isolate_en_a:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_dfx_csr_ctrl {
	struct {
		uint32_t ro_disable:1; /* [0:0] */
		uint32_t clkgate_ena:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_dfx_ctrl {
	struct {
		uint32_t test_en:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_dfx_stat_rdreg {
	struct {
		uint32_t test_state:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_boot_addr {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_crash_dump0 {
	struct {
		uint32_t excep_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_crash_dump1 {
	struct {
		uint32_t last_data_addr; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_crash_dump2 {
	struct {
		uint32_t nxt_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_crash_dump3 {
	struct {
		uint32_t curr_pc; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_ctrl {
	struct {
		uint32_t reset_n_a:1; /* [0:0] */
		uint32_t clk_en_a:1; /* [1:1] */
		uint32_t fetch_en_a:1; /* [2:2] */
		uint32_t dble_fault_seen_clr_a:1; /* [3:3] */
		uint32_t time_out_threshold_nt:10; /* [13:4] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_device_addr {
	struct {
		uint32_t base_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_dmem {
	struct {
		uint32_t alias_addr_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_hart_id {
	struct {
		uint32_t val_nt; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_irq {
	struct {
		uint32_t flag:15; /* [14:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl1 {
	struct {
		uint32_t edge_sel_nt:30; /* [29:0] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl2 {
	struct {
		uint32_t det_type_nt:15; /* [14:0] */
		uint32_t clear_a:15; /* [29:15] */
		uint32_t software_irq_a:1; /* [30:30] */
	};
	uint32_t val;
};

union aw_ucie_dfx1_reg_lane_mcu_stats {
	struct {
		uint32_t core_sleep:1; /* [0:0] */
		uint32_t dble_fault_seen:1; /* [1:1] */
		uint32_t dmactive:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_fifo_wm {
	struct {
		uint32_t tx_prot_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_prot_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_prot_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_prot_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1 {
	struct {
		uint32_t tx_prot_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_prot_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_prot_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_prot_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t rx_prot_fifo_corr_err_int1:1; /* [4:4] */
		uint32_t rx_prot_fifo_uncorr_err_int1:1; /* [5:5] */
		uint32_t rx_prot_fifo_ovf_err_int1:1; /* [6:6] */
		uint32_t rx_prot_fifo_unf_err_int1:1; /* [7:7] */
		uint32_t rx_prot_pl_clk_req_int1:1; /* [8:8] */
		uint32_t rx_prot_pl_wake_ack_int1:1; /* [9:9] */
		uint32_t rx_prot_pl_inband_pres_int1:1; /* [10:10] */
		uint32_t rx_prot_pl_phyinrecenter_int1:1; /* [11:11] */
		uint32_t rx_prot_pl_phyinl1_int1:1; /* [12:12] */
		uint32_t rx_prot_pl_phyinl2_int1:1; /* [13:13] */
		uint32_t rx_prot_pl_error_int1:1; /* [14:14] */
		uint32_t rx_prot_pl_cerror_int1:1; /* [15:15] */
		uint32_t rx_prot_pl_nferror_int1:1; /* [16:16] */
		uint32_t rx_prot_pl_trainerror_int1:1; /* [17:17] */
		uint32_t rx_prot_pl_link_cfg_int1:1; /* [18:18] */
		uint32_t rx_prot_pl_speedmode_int1:1; /* [19:19] */
		uint32_t rx_prot_pl_state_sts_int1:1; /* [20:20] */
		uint32_t rx_prot_pl_flitfmt_int1:1; /* [21:21] */
		uint32_t rx_prot_pl_protocol_int1:1; /* [22:22] */
		uint32_t rx_prot_pl_stream_int1:1; /* [23:23] */
		uint32_t rx_prot_pl_rx_act_req_int1:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1_mask {
	struct {
		uint32_t tx_prot_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_prot_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_prot_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_prot_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t rx_prot_fifo_corr_err_int1_mask:1; /* [4:4] */
		uint32_t rx_prot_fifo_uncorr_err_int1_mask:1; /* [5:5] */
		uint32_t rx_prot_fifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t rx_prot_fifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rx_prot_pl_clk_req_int1_mask:1; /* [8:8] */
		uint32_t rx_prot_pl_wake_ack_int1_mask:1; /* [9:9] */
		uint32_t rx_prot_pl_inband_pres_int1_mask:1; /* [10:10] */
		uint32_t rx_prot_pl_phyinrecenter_int1_mask:1; /* [11:11] */
		uint32_t rx_prot_pl_phyinl1_int1_mask:1; /* [12:12] */
		uint32_t rx_prot_pl_phyinl2_int1_mask:1; /* [13:13] */
		uint32_t rx_prot_pl_error_int1_mask:1; /* [14:14] */
		uint32_t rx_prot_pl_cerror_int1_mask:1; /* [15:15] */
		uint32_t rx_prot_pl_nferror_int1_mask:1; /* [16:16] */
		uint32_t rx_prot_pl_trainerror_int1_mask:1; /* [17:17] */
		uint32_t rx_prot_pl_link_cfg_int1_mask:1; /* [18:18] */
		uint32_t rx_prot_pl_speedmode_int1_mask:1; /* [19:19] */
		uint32_t rx_prot_pl_state_sts_int1_mask:1; /* [20:20] */
		uint32_t rx_prot_pl_flitfmt_int1_mask:1; /* [21:21] */
		uint32_t rx_prot_pl_protocol_int1_mask:1; /* [22:22] */
		uint32_t rx_prot_pl_stream_int1_mask:1; /* [23:23] */
		uint32_t rx_prot_pl_rx_act_req_int1_mask:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2 {
	struct {
		uint32_t tx_prot_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_prot_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_prot_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_prot_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t rx_prot_fifo_corr_err_int2:1; /* [4:4] */
		uint32_t rx_prot_fifo_uncorr_err_int2:1; /* [5:5] */
		uint32_t rx_prot_fifo_ovf_err_int2:1; /* [6:6] */
		uint32_t rx_prot_fifo_unf_err_int2:1; /* [7:7] */
		uint32_t rx_prot_pl_clk_req_int2:1; /* [8:8] */
		uint32_t rx_prot_pl_wake_ack_int2:1; /* [9:9] */
		uint32_t rx_prot_pl_inband_pres_int2:1; /* [10:10] */
		uint32_t rx_prot_pl_phyinrecenter_int2:1; /* [11:11] */
		uint32_t rx_prot_pl_phyinl1_int2:1; /* [12:12] */
		uint32_t rx_prot_pl_phyinl2_int2:1; /* [13:13] */
		uint32_t rx_prot_pl_error_int2:1; /* [14:14] */
		uint32_t rx_prot_pl_cerror_int2:1; /* [15:15] */
		uint32_t rx_prot_pl_nferror_int2:1; /* [16:16] */
		uint32_t rx_prot_pl_trainerror_int2:1; /* [17:17] */
		uint32_t rx_prot_pl_link_cfg_int2:1; /* [18:18] */
		uint32_t rx_prot_pl_speedmode_int2:1; /* [19:19] */
		uint32_t rx_prot_pl_state_sts_int2:1; /* [20:20] */
		uint32_t rx_prot_pl_flitfmt_int2:1; /* [21:21] */
		uint32_t rx_prot_pl_protocol_int2:1; /* [22:22] */
		uint32_t rx_prot_pl_stream_int2:1; /* [23:23] */
		uint32_t rx_prot_pl_rx_act_req_int2:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2_mask {
	struct {
		uint32_t tx_prot_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_prot_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_prot_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_prot_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t rx_prot_fifo_corr_err_int2_mask:1; /* [4:4] */
		uint32_t rx_prot_fifo_uncorr_err_int2_mask:1; /* [5:5] */
		uint32_t rx_prot_fifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t rx_prot_fifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rx_prot_pl_clk_req_int2_mask:1; /* [8:8] */
		uint32_t rx_prot_pl_wake_ack_int2_mask:1; /* [9:9] */
		uint32_t rx_prot_pl_inband_pres_int2_mask:1; /* [10:10] */
		uint32_t rx_prot_pl_phyinrecenter_int2_mask:1; /* [11:11] */
		uint32_t rx_prot_pl_phyinl1_int2_mask:1; /* [12:12] */
		uint32_t rx_prot_pl_phyinl2_int2_mask:1; /* [13:13] */
		uint32_t rx_prot_pl_error_int2_mask:1; /* [14:14] */
		uint32_t rx_prot_pl_cerror_int2_mask:1; /* [15:15] */
		uint32_t rx_prot_pl_nferror_int2_mask:1; /* [16:16] */
		uint32_t rx_prot_pl_trainerror_int2_mask:1; /* [17:17] */
		uint32_t rx_prot_pl_link_cfg_int2_mask:1; /* [18:18] */
		uint32_t rx_prot_pl_speedmode_int2_mask:1; /* [19:19] */
		uint32_t rx_prot_pl_state_sts_int2_mask:1; /* [20:20] */
		uint32_t rx_prot_pl_flitfmt_int2_mask:1; /* [21:21] */
		uint32_t rx_prot_pl_protocol_int2_mask:1; /* [22:22] */
		uint32_t rx_prot_pl_stream_int2_mask:1; /* [23:23] */
		uint32_t rx_prot_pl_rx_act_req_int2_mask:1; /* [24:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary {
	struct {
		uint32_t soc_bridge_ch0_int1:1; /* [0:0] */
		uint32_t soc_bridge_ch1_int1:1; /* [1:1] */
		uint32_t soc_bridge_ch2_int1:1; /* [2:2] */
		uint32_t soc_bridge_ch3_int1:1; /* [3:3] */
		uint32_t soc_bridge_ch4_int1:1; /* [4:4] */
		uint32_t soc_bridge_ch5_int1:1; /* [5:5] */
		uint32_t soc_bridge_ch6_int1:1; /* [6:6] */
		uint32_t soc_bridge_ch7_int1:1; /* [7:7] */
		uint32_t soc_bridge_ch8_int1:1; /* [8:8] */
		uint32_t soc_bridge_ch9_int1:1; /* [9:9] */
		uint32_t soc_bridge_ch10_int1:1; /* [10:10] */
		uint32_t soc_bridge_ch11_int1:1; /* [11:11] */
		uint32_t soc_bridge_ch12_int1:1; /* [12:12] */
		uint32_t soc_bridge_ch13_int1:1; /* [13:13] */
		uint32_t soc_bridge_ch14_int1:1; /* [14:14] */
		uint32_t soc_bridge_ch15_int1:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary_mask {
	struct {
		uint32_t soc_bridge_ch0_int1_mask:1; /* [0:0] */
		uint32_t soc_bridge_ch1_int1_mask:1; /* [1:1] */
		uint32_t soc_bridge_ch2_int1_mask:1; /* [2:2] */
		uint32_t soc_bridge_ch3_int1_mask:1; /* [3:3] */
		uint32_t soc_bridge_ch4_int1_mask:1; /* [4:4] */
		uint32_t soc_bridge_ch5_int1_mask:1; /* [5:5] */
		uint32_t soc_bridge_ch6_int1_mask:1; /* [6:6] */
		uint32_t soc_bridge_ch7_int1_mask:1; /* [7:7] */
		uint32_t soc_bridge_ch8_int1_mask:1; /* [8:8] */
		uint32_t soc_bridge_ch9_int1_mask:1; /* [9:9] */
		uint32_t soc_bridge_ch10_int1_mask:1; /* [10:10] */
		uint32_t soc_bridge_ch11_int1_mask:1; /* [11:11] */
		uint32_t soc_bridge_ch12_int1_mask:1; /* [12:12] */
		uint32_t soc_bridge_ch13_int1_mask:1; /* [13:13] */
		uint32_t soc_bridge_ch14_int1_mask:1; /* [14:14] */
		uint32_t soc_bridge_ch15_int1_mask:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary {
	struct {
		uint32_t soc_bridge_ch0_int2:1; /* [0:0] */
		uint32_t soc_bridge_ch1_int2:1; /* [1:1] */
		uint32_t soc_bridge_ch2_int2:1; /* [2:2] */
		uint32_t soc_bridge_ch3_int2:1; /* [3:3] */
		uint32_t soc_bridge_ch4_int2:1; /* [4:4] */
		uint32_t soc_bridge_ch5_int2:1; /* [5:5] */
		uint32_t soc_bridge_ch6_int2:1; /* [6:6] */
		uint32_t soc_bridge_ch7_int2:1; /* [7:7] */
		uint32_t soc_bridge_ch8_int2:1; /* [8:8] */
		uint32_t soc_bridge_ch9_int2:1; /* [9:9] */
		uint32_t soc_bridge_ch10_int2:1; /* [10:10] */
		uint32_t soc_bridge_ch11_int2:1; /* [11:11] */
		uint32_t soc_bridge_ch12_int2:1; /* [12:12] */
		uint32_t soc_bridge_ch13_int2:1; /* [13:13] */
		uint32_t soc_bridge_ch14_int2:1; /* [14:14] */
		uint32_t soc_bridge_ch15_int2:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary_mask {
	struct {
		uint32_t soc_bridge_ch0_int2_mask:1; /* [0:0] */
		uint32_t soc_bridge_ch1_int2_mask:1; /* [1:1] */
		uint32_t soc_bridge_ch2_int2_mask:1; /* [2:2] */
		uint32_t soc_bridge_ch3_int2_mask:1; /* [3:3] */
		uint32_t soc_bridge_ch4_int2_mask:1; /* [4:4] */
		uint32_t soc_bridge_ch5_int2_mask:1; /* [5:5] */
		uint32_t soc_bridge_ch6_int2_mask:1; /* [6:6] */
		uint32_t soc_bridge_ch7_int2_mask:1; /* [7:7] */
		uint32_t soc_bridge_ch8_int2_mask:1; /* [8:8] */
		uint32_t soc_bridge_ch9_int2_mask:1; /* [9:9] */
		uint32_t soc_bridge_ch10_int2_mask:1; /* [10:10] */
		uint32_t soc_bridge_ch11_int2_mask:1; /* [11:11] */
		uint32_t soc_bridge_ch12_int2_mask:1; /* [12:12] */
		uint32_t soc_bridge_ch13_int2_mask:1; /* [13:13] */
		uint32_t soc_bridge_ch14_int2_mask:1; /* [14:14] */
		uint32_t soc_bridge_ch15_int2_mask:1; /* [15:15] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_cfg {
	struct {
		uint32_t prot_bridge_rt_en:1; /* [0:0] */
		uint32_t prot_bridge_tx_flit_sop:1; /* [1:1] */
		uint32_t prot_bridge_lp_stream:8; /* [9:2] */
		uint32_t prot_bridge_lp_state_req:4; /* [13:10] */
		uint32_t prot_bridge_lp_rx_active_sts:1; /* [14:14] */
		uint32_t prot_bridge_lp_wake_req:1; /* [15:15] */
		uint32_t prot_bridge_lp_corrupt_crc:1; /* [16:16] */
		uint32_t prot_bridge_lp_clk_ack:1; /* [17:17] */
		uint32_t prot_bridge_clk_gate_en:1; /* [18:18] */
		uint32_t prot_bridge_lp_linkerror:1; /* [19:19] */
		uint32_t rx_remote_link_up:1; /* [20:20] */
		uint32_t prot_bridge_lp_stallack:1; /* [21:21] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status {
	struct {
		uint32_t prot_bridge_pl_stream:8; /* [7:0] */
		uint32_t prot_bridge_pl_protocol:3; /* [10:8] */
		uint32_t prot_bridge_pl_protocol_flitfmt:4; /* [14:11] */
		uint32_t prot_bridge_pl_state_sts:4; /* [18:15] */
		uint32_t prot_bridge_pl_rx_acive_req:1; /* [19:19] */
		uint32_t prot_bridge_pl_speedmode:3; /* [22:20] */
		uint32_t prot_bridge_pl_linkcfg:3; /* [25:23] */
		uint32_t prot_bridge_pl_clk_req:1; /* [26:26] */
		uint32_t prot_bridge_pl_inband_pres:1; /* [27:27] */
		uint32_t prot_bridge_pl_wake_ack:1; /* [28:28] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status2 {
	struct {
		uint32_t prot_bridge_pl_phyinrecenter:1; /* [0:0] */
		uint32_t prot_bridge_pl_phyinl1:1; /* [1:1] */
		uint32_t prot_bridge_pl_phyinl2:1; /* [2:2] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_cfg1 {
	struct {
		uint32_t txsb_cfg1_opcode:5; /* [4:0] */
		uint32_t txsb_cfg1_ep:1; /* [5:5] */
		uint32_t txsb_cfg1_be:8; /* [13:6] */
		uint32_t txsb_cfg1_tag:5; /* [18:14] */
		uint32_t txsb_cfg1_srcid:3; /* [21:19] */
		uint32_t txsb_cfg1_type:3; /* [24:22] */
		uint32_t txsb_cfg1_status:3; /* [27:25] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_cfg2 {
	struct {
		uint32_t txsb_cfg2_addr:24; /* [23:0] */
		uint32_t txsb_cfg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_cfg3 {
	struct {
		uint32_t txsb_cfg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_cfg4 {
	struct {
		uint32_t txsb_cfg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_cfg5 {
	struct {
		uint32_t txsb_cfg7_execute:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_txsb_stall_rdreg1 {
	struct {
		uint32_t txsb_stall_rdreg1_accreq_wr_ok:1; /* [0:0] */
		uint32_t txsb_stall_rdreg1_acccom_wr_ok:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbacccom_cfg {
	struct {
		uint32_t rxsbacccom_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg1 {
	struct {
		uint32_t rxsbacccom_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbacccom_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbacccom_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbacccom_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbacccom_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbacccom_rdreg1_status:3; /* [24:22] */
		uint32_t rxsbacccom_rdreg1_dstid:3; /* [27:25] */
		uint32_t rxsbacccom_rdreg1_dp:1; /* [28:28] */
		uint32_t rxsbacccom_rdreg1_cp:1; /* [29:29] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg2 {
	struct {
		uint32_t rxsbacccom_rdreg2_avail:1; /* [0:0] */
		uint32_t rxsbacccom_rdreg2_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg3 {
	struct {
		uint32_t rxsbacccom_rdreg3_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg4 {
	struct {
		uint32_t rxsbacccom_rdreg4_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_cfg {
	struct {
		uint32_t rxsbaccreq_cfg_rdreq:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg1 {
	struct {
		uint32_t rxsbaccreq_rdreg1_opcode:5; /* [4:0] */
		uint32_t rxsbaccreq_rdreg1_ep:1; /* [5:5] */
		uint32_t rxsbaccreq_rdreg1_be:8; /* [13:6] */
		uint32_t rxsbaccreq_rdreg1_tag:5; /* [18:14] */
		uint32_t rxsbaccreq_rdreg1_srcid:3; /* [21:19] */
		uint32_t rxsbaccreq_rdreg1_dp:1; /* [22:22] */
		uint32_t rxsbaccreq_rdreg1_cp:1; /* [23:23] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg2 {
	struct {
		uint32_t rxsbaccreq_rdreg2_addr:24; /* [23:0] */
		uint32_t rxsbaccreq_rdreg2_dstid:3; /* [26:24] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg3 {
	struct {
		uint32_t rxsbaccreq_rdreg3_avail:1; /* [0:0] */
		uint32_t rxsbaccreq_rdreg3_rdready:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg4 {
	struct {
		uint32_t rxsbaccreq_rdreg4_data0; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg5 {
	struct {
		uint32_t rxsbaccreq_rdreg5_data1; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg1 {
	struct {
		uint32_t txsb_fifo_err_rdreg1_accreq_sfifo_ovf_err_int1:1; /* [0:0] */
		uint32_t txsb_fifo_err_rdreg1_accreq_sfifo_unf_err_int1:1; /* [1:1] */
		uint32_t txsb_fifo_err_rdreg1_acccom_sfifo_ovf_err_int1:1; /* [2:2] */
		uint32_t txsb_fifo_err_rdreg1_acccom_sfifo_unf_err_int1:1; /* [3:3] */
		uint32_t rxsb_fifo_err_rdreg1_accreq_sfifo_ovf_err_int1:1; /* [4:4] */
		uint32_t rxsb_fifo_err_rdreg1_accreq_sfifo_unf_err_int1:1; /* [5:5] */
		uint32_t rxsb_fifo_err_rdreg1_acccom_sfifo_ovf_err_int1:1; /* [6:6] */
		uint32_t rxsb_fifo_err_rdreg1_acccom_sfifo_unf_err_int1:1; /* [7:7] */
		uint32_t rxsb_fifo_err_rdreg1_stat_accreq_hdr_parity_err_int1:1; /* [8:8] */
		uint32_t rxsb_fifo_err_rdreg1_stat_accreq_dat_parity_err_int1:1; /* [9:9] */
		uint32_t rxsb_fifo_err_rdreg1_stat_acccom_hdr_parity_err_int1:1; /* [10:10] */
		uint32_t rxsb_fifo_err_rdreg1_stat_acccom_dat_parity_err_int1:1; /* [11:11] */
		uint32_t rxsbacccom_avail_int1:1; /* [12:12] */
		uint32_t rxsbaccreq_avail_int1:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask {
	struct {
		uint32_t txsb_fifo_err_mask_accreq_sfifo_ovf_err_int1_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_mask_accreq_sfifo_unf_err_int1_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_mask_acccom_sfifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_mask_acccom_sfifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t rxsb_fifo_err_mask_accreq_sfifo_ovf_err_int1_mask:1; /* [4:4] */
		uint32_t rxsb_fifo_err_mask_accreq_sfifo_unf_err_int1_mask:1; /* [5:5] */
		uint32_t rxsb_fifo_err_mask_acccom_sfifo_ovf_err_int1_mask:1; /* [6:6] */
		uint32_t rxsb_fifo_err_mask_acccom_sfifo_unf_err_int1_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_mask_stat_accreq_hdr_parity_err_int1_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_mask_stat_accreq_dat_parity_err_int1_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_mask_stat_acccom_hdr_parity_err_int1_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_mask_stat_acccom_dat_parity_err_int1_mask:1; /* [11:11] */
		uint32_t rxsbacccom_avail_int1_mask:1; /* [12:12] */
		uint32_t rxsbaccreq_avail_int1_mask:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg2 {
	struct {
		uint32_t txsb_fifo_err_rdreg1_accreq_sfifo_ovf_err_int2:1; /* [0:0] */
		uint32_t txsb_fifo_err_rdreg1_accreq_sfifo_unf_err_int2:1; /* [1:1] */
		uint32_t txsb_fifo_err_rdreg1_acccom_sfifo_ovf_err_int2:1; /* [2:2] */
		uint32_t txsb_fifo_err_rdreg1_acccom_sfifo_unf_err_int2:1; /* [3:3] */
		uint32_t rxsb_fifo_err_rdreg1_accreq_sfifo_ovf_err_int2:1; /* [4:4] */
		uint32_t rxsb_fifo_err_rdreg1_accreq_sfifo_unf_err_int2:1; /* [5:5] */
		uint32_t rxsb_fifo_err_rdreg1_acccom_sfifo_ovf_err_int2:1; /* [6:6] */
		uint32_t rxsb_fifo_err_rdreg1_acccom_sfifo_unf_err_int2:1; /* [7:7] */
		uint32_t rxsb_fifo_err_rdreg1_stat_accreq_hdr_parity_err_int2:1; /* [8:8] */
		uint32_t rxsb_fifo_err_rdreg1_stat_accreq_dat_parity_err_int2:1; /* [9:9] */
		uint32_t rxsb_fifo_err_rdreg1_stat_acccom_hdr_parity_err_int2:1; /* [10:10] */
		uint32_t rxsb_fifo_err_rdreg1_stat_acccom_dat_parity_err_int2:1; /* [11:11] */
		uint32_t rxsbacccom_avail_int2:1; /* [12:12] */
		uint32_t rxsbaccreq_avail_int2:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask2 {
	struct {
		uint32_t txsb_fifo_err_mask_accreq_sfifo_ovf_err_int2_mask:1; /* [0:0] */
		uint32_t txsb_fifo_err_mask_accreq_sfifo_unf_err_int2_mask:1; /* [1:1] */
		uint32_t txsb_fifo_err_mask_acccom_sfifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t txsb_fifo_err_mask_acccom_sfifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t rxsb_fifo_err_mask_accreq_sfifo_ovf_err_int2_mask:1; /* [4:4] */
		uint32_t rxsb_fifo_err_mask_accreq_sfifo_unf_err_int2_mask:1; /* [5:5] */
		uint32_t rxsb_fifo_err_mask_acccom_sfifo_ovf_err_int2_mask:1; /* [6:6] */
		uint32_t rxsb_fifo_err_mask_acccom_sfifo_unf_err_int2_mask:1; /* [7:7] */
		uint32_t rxsb_fifo_err_mask_stat_accreq_hdr_parity_err_int2_mask:1; /* [8:8] */
		uint32_t rxsb_fifo_err_mask_stat_accreq_dat_parity_err_int2_mask:1; /* [9:9] */
		uint32_t rxsb_fifo_err_mask_stat_acccom_hdr_parity_err_int2_mask:1; /* [10:10] */
		uint32_t rxsb_fifo_err_mask_stat_acccom_dat_parity_err_int2_mask:1; /* [11:11] */
		uint32_t rxsbacccom_avail_int2_mask:1; /* [12:12] */
		uint32_t rxsbaccreq_avail_int2_mask:1; /* [13:13] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config {
	struct {
		uint32_t rx_cxs_deactivate_timer_enable:1; /* [0:0] */
		uint32_t rx_cxs_deactivate_timer_max_value:15; /* [15:1] */
		uint32_t tx_cxs_rc_link_deact_timer_enable:1; /* [16:16] */
		uint32_t tx_cxs_rc_link_deact_timer_max_value:15; /* [31:17] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_status {
	struct {
		uint32_t p0_tx_present_status:2; /* [1:0] */
		uint32_t p0_rx_present_status:2; /* [3:2] */
		uint32_t p1_tx_present_status:2; /* [5:4] */
		uint32_t p1_rx_present_status:2; /* [7:6] */
		uint32_t p2_tx_present_status:2; /* [9:8] */
		uint32_t p2_rx_present_status:2; /* [11:10] */
		uint32_t p3_tx_present_status:2; /* [13:12] */
		uint32_t p3_rx_present_status:2; /* [15:14] */
		uint32_t p4_tx_present_status:2; /* [17:16] */
		uint32_t p4_rx_present_status:2; /* [19:18] */
		uint32_t p5_tx_present_status:2; /* [21:20] */
		uint32_t p5_rx_present_status:2; /* [23:22] */
		uint32_t p6_tx_present_status:2; /* [25:24] */
		uint32_t p6_rx_present_status:2; /* [27:26] */
		uint32_t p7_tx_present_status:2; /* [29:28] */
		uint32_t p7_rx_present_status:2; /* [31:30] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config2 {
	struct {
		uint32_t bridge_select_mux:1; /* [0:0] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_periodic_timer_config {
	struct {
		uint32_t periodic_timer_en:1; /* [0:0] */
		uint32_t periodic_timer_value:16; /* [16:1] */
	};
	uint32_t val;
};

union aw_ucie_bridge_top_reg_reg_bridge_top_gb_force_read_value {
	struct {
		uint32_t gb_force_read_value:7; /* [6:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_fifo_wm {
	struct {
		uint32_t tx_chan_fifo_wm_high:8; /* [7:0] */
		uint32_t tx_chan_fifo_wm_low:8; /* [15:8] */
		uint32_t rx_chan_fifo_wm_high:8; /* [23:16] */
		uint32_t rx_chan_fifo_wm_low:8; /* [31:24] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_fc_control {
	struct {
		uint32_t rx_chan_fc_init_credit:8; /* [7:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_comm_count_control {
	struct {
		uint32_t sys_tick:1; /* [0:0] */
		uint32_t counter_mode:1; /* [1:1] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_count_control {
	struct {
		uint32_t tx_chan_trans_count_force_clear:1; /* [0:0] */
		uint32_t tx_chan_trans_count_load:1; /* [1:1] */
		uint32_t tx_chan_bytes_count_force_clear:1; /* [2:2] */
		uint32_t tx_chan_bytes_count_load:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t rx_chan_trans_count_force_clear:1; /* [8:8] */
		uint32_t rx_chan_trans_count_load:1; /* [9:9] */
		uint32_t rx_chan_bytes_count_force_clear:1; /* [10:10] */
		uint32_t rx_chan_bytes_count_load:1; /* [11:11] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi {
	struct {
		uint32_t tx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo {
	struct {
		uint32_t tx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi {
	struct {
		uint32_t tx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo {
	struct {
		uint32_t tx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi {
	struct {
		uint32_t rx_chan_trans_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo {
	struct {
		uint32_t rx_chan_trans_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi {
	struct {
		uint32_t rx_chan_bytes_count_hi; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo {
	struct {
		uint32_t rx_chan_bytes_count_lo; /* [31:0] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int1_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int1_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int1_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int1_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int1_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int1_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int1_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int1_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2 {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2_mask {
	struct {
		uint32_t tx_chan_fifo_corr_err_int2_mask:1; /* [0:0] */
		uint32_t tx_chan_fifo_uncorr_err_int2_mask:1; /* [1:1] */
		uint32_t tx_chan_fifo_ovf_err_int2_mask:1; /* [2:2] */
		uint32_t tx_chan_fifo_unf_err_int2_mask:1; /* [3:3] */
		uint32_t reserved_bit_0:12;
		uint32_t rx_chan_fifo_corr_err_int2_mask:1; /* [16:16] */
		uint32_t rx_chan_fifo_uncorr_err_int2_mask:1; /* [17:17] */
		uint32_t rx_chan_fifo_ovf_err_int2_mask:1; /* [18:18] */
		uint32_t rx_chan_fifo_unf_err_int2_mask:1; /* [19:19] */
	};
	uint32_t val;
};

union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_credit {
	struct {
		uint32_t max_credit_load:8; /* [7:0] */
	};
	uint32_t val;
};

#if EVT_VER == 0
	struct aw_ucie {
		uint32_t reserved_1[32768];
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr; /* offset : 0x20000 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr1 dvsec1_reg_reg_global_dvsec1_hdr1; /* offset : 0x20004 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor; /* offset : 0x20008 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cap dvsec1_reg_reg_global_dvsec1_ucie_link_cap; /* offset : 0x2000c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl; /* offset : 0x20010 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status dvsec1_reg_reg_global_dvsec1_ucie_link_status; /* offset : 0x20014 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl; /* offset : 0x20018 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_low dvsec1_reg_reg_global_dvsec1_reg_loc0_low; /* offset : 0x2001c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_high dvsec1_reg_reg_global_dvsec1_reg_loc0_high; /* offset : 0x20020 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_low dvsec1_reg_reg_global_dvsec1_reg_loc1_low; /* offset : 0x20024 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_high dvsec1_reg_reg_global_dvsec1_reg_loc1_high; /* offset : 0x20028 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_low dvsec1_reg_reg_global_dvsec1_reg_loc2_low; /* offset : 0x2002c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_high dvsec1_reg_reg_global_dvsec1_reg_loc2_high; /* offset : 0x20030 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_low dvsec1_reg_reg_global_dvsec1_reg_loc3_low; /* offset : 0x20034 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_high dvsec1_reg_reg_global_dvsec1_reg_loc3_high; /* offset : 0x20038 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low; /* offset : 0x2003c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high; /* offset : 0x20040 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low; /* offset : 0x20044 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high; /* offset : 0x20048 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats; /* offset : 0x2004c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_req_id dvsec1_reg_reg_global_dvsec1_req_id; /* offset : 0x20050 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_associated_port_num dvsec1_reg_reg_global_dvsec1_associated_port_num; /* offset : 0x20054 */
		uint32_t reserved_2[1002];
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_pcie_extnd_cap_hdr dvsec2_reg_reg_glbl_dvsec2_cap_pcie_extnd_cap_hdr; /* offset : 0x21000 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr1 dvsec2_reg_reg_glbl_dvsec2_cap_hdr1; /* offset : 0x21004 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr2 dvsec2_reg_reg_glbl_dvsec2_cap_hdr2; /* offset : 0x21008 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1 dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1; /* offset : 0x2100c */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2 dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2; /* offset : 0x21010 */
		uint32_t reserved_3[4091];
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1; /* offset : 0x25000 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2; /* offset : 0x25004 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3; /* offset : 0x25008 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg4 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg4; /* offset : 0x2500c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat; /* offset : 0x25010 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask; /* offset : 0x25014 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity; /* offset : 0x25018 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat adapter_d2d_reg_reg_adapter_d2d_corr_err_stat; /* offset : 0x2501c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask adapter_d2d_reg_reg_adapter_d2d_corr_err_mask; /* offset : 0x25020 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1 adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1; /* offset : 0x25024 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2 adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2; /* offset : 0x25028 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 adapter_d2d_reg_reg_adapter_d2d_hdr_log2; /* offset : 0x2502c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl; /* offset : 0x25030 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1; /* offset : 0x25034 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2; /* offset : 0x25038 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1; /* offset : 0x2503c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2; /* offset : 0x25040 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1; /* offset : 0x25044 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2; /* offset : 0x25048 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1; /* offset : 0x2504c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2; /* offset : 0x25050 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1; /* offset : 0x25054 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log2; /* offset : 0x25058 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1; /* offset : 0x2505c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log2; /* offset : 0x25060 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log1; /* offset : 0x25064 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log2; /* offset : 0x25068 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log1; /* offset : 0x2506c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log2; /* offset : 0x25070 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log1; /* offset : 0x25074 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log2; /* offset : 0x25078 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log1; /* offset : 0x2507c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log2; /* offset : 0x25080 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1; /* offset : 0x25084 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2; /* offset : 0x25088 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1; /* offset : 0x2508c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2; /* offset : 0x25090 */
		uint32_t reserved_4[987];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cap phy_d2d_reg_reg_phy_d2d_phy_cap; /* offset : 0x26000 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_d2d_reg_reg_phy_d2d_phy_cntrl; /* offset : 0x26004 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_d2d_reg_reg_phy_d2d_phy_stat; /* offset : 0x26008 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_init_debug phy_d2d_reg_reg_phy_d2d_phy_init_debug; /* offset : 0x2600c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 phy_d2d_reg_reg_phy_d2d_m0_train_setup1; /* offset : 0x26010 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup1 phy_d2d_reg_reg_phy_d2d_m1_train_setup1; /* offset : 0x26014 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup1 phy_d2d_reg_reg_phy_d2d_m2_train_setup1; /* offset : 0x26018 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup1 phy_d2d_reg_reg_phy_d2d_m3_train_setup1; /* offset : 0x2601c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 phy_d2d_reg_reg_phy_d2d_m0_train_setup2; /* offset : 0x26020 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup2 phy_d2d_reg_reg_phy_d2d_m1_train_setup2; /* offset : 0x26024 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup2 phy_d2d_reg_reg_phy_d2d_m2_train_setup2; /* offset : 0x26028 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup2 phy_d2d_reg_reg_phy_d2d_m3_train_setup2; /* offset : 0x2602c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1; /* offset : 0x26030 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2; /* offset : 0x26034 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1; /* offset : 0x26038 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2; /* offset : 0x2603c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m2_train_setup3_1; /* offset : 0x26040 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m2_train_setup3_2; /* offset : 0x26044 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m3_train_setup3_1; /* offset : 0x26048 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m3_train_setup3_2; /* offset : 0x2604c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 phy_d2d_reg_reg_phy_d2d_m0_train_setup4; /* offset : 0x26050 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup4 phy_d2d_reg_reg_phy_d2d_m1_train_setup4; /* offset : 0x26054 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup4 phy_d2d_reg_reg_phy_d2d_m2_train_setup4; /* offset : 0x26058 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup4 phy_d2d_reg_reg_phy_d2d_m3_train_setup4; /* offset : 0x2605c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg1; /* offset : 0x26060 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg2; /* offset : 0x26064 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg1; /* offset : 0x26068 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg2; /* offset : 0x2606c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg1; /* offset : 0x26070 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg2; /* offset : 0x26074 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg1; /* offset : 0x26078 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg2; /* offset : 0x2607c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log0 phy_d2d_reg_reg_phy_d2d_m0_err_log0; /* offset : 0x26080 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log0 phy_d2d_reg_reg_phy_d2d_m1_err_log0; /* offset : 0x26084 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log0 phy_d2d_reg_reg_phy_d2d_m2_err_log0; /* offset : 0x26088 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log0 phy_d2d_reg_reg_phy_d2d_m3_err_log0; /* offset : 0x2608c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log1 phy_d2d_reg_reg_phy_d2d_m0_err_log1; /* offset : 0x26090 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log1 phy_d2d_reg_reg_phy_d2d_m1_err_log1; /* offset : 0x26094 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log1 phy_d2d_reg_reg_phy_d2d_m2_err_log1; /* offset : 0x26098 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log1 phy_d2d_reg_reg_phy_d2d_m3_err_log1; /* offset : 0x2609c */
		uint32_t reserved_5[24];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1 phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1; /* offset : 0x26100 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg2 phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg2; /* offset : 0x26104 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2 phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2; /* offset : 0x26108 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1; /* offset : 0x2610c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2; /* offset : 0x26110 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1; /* offset : 0x26114 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2; /* offset : 0x26118 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg1; /* offset : 0x2611c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg2; /* offset : 0x26120 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg1; /* offset : 0x26124 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg2; /* offset : 0x26128 */
		uint32_t reserved_6[2];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair; /* offset : 0x26134 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair; /* offset : 0x26138 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair; /* offset : 0x2613c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair; /* offset : 0x26140 */
		uint32_t reserved_7[47];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr; /* offset : 0x26200 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr1 phy_d2d_reg_reg_phy_d2d_dvsec_hdr1; /* offset : 0x26204 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr2 phy_d2d_reg_reg_phy_d2d_dvsec_hdr2; /* offset : 0x26208 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_uhm_status phy_d2d_reg_reg_phy_d2d_uhm_status; /* offset : 0x2620c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0; /* offset : 0x26210 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0; /* offset : 0x26214 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0; /* offset : 0x26218 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0; /* offset : 0x2621c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0; /* offset : 0x26220 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0; /* offset : 0x26224 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0; /* offset : 0x26228 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0; /* offset : 0x2622c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0; /* offset : 0x26230 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0; /* offset : 0x26234 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0; /* offset : 0x26238 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0; /* offset : 0x2623c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0; /* offset : 0x26240 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0; /* offset : 0x26244 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0; /* offset : 0x26248 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0; /* offset : 0x2624c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0; /* offset : 0x26250 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0; /* offset : 0x26254 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0; /* offset : 0x26258 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0; /* offset : 0x2625c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0; /* offset : 0x26260 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0; /* offset : 0x26264 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0; /* offset : 0x26268 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0; /* offset : 0x2626c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0; /* offset : 0x26270 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0; /* offset : 0x26274 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0; /* offset : 0x26278 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0; /* offset : 0x2627c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0; /* offset : 0x26280 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0; /* offset : 0x26284 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0; /* offset : 0x26288 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0; /* offset : 0x2628c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0; /* offset : 0x26290 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0; /* offset : 0x26294 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1; /* offset : 0x26298 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1; /* offset : 0x2629c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1; /* offset : 0x262a0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1; /* offset : 0x262a4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1; /* offset : 0x262a8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1; /* offset : 0x262ac */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1; /* offset : 0x262b0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1; /* offset : 0x262b4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1; /* offset : 0x262b8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1; /* offset : 0x262bc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1; /* offset : 0x262c0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1; /* offset : 0x262c4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1; /* offset : 0x262c8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1; /* offset : 0x262cc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1; /* offset : 0x262d0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1; /* offset : 0x262d4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1; /* offset : 0x262d8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1; /* offset : 0x262dc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1; /* offset : 0x262e0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1; /* offset : 0x262e4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1; /* offset : 0x262e8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1; /* offset : 0x262ec */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1; /* offset : 0x262f0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1; /* offset : 0x262f4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1; /* offset : 0x262f8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1; /* offset : 0x262fc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1; /* offset : 0x26300 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1; /* offset : 0x26304 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1; /* offset : 0x26308 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1; /* offset : 0x2630c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1; /* offset : 0x26310 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1; /* offset : 0x26314 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1; /* offset : 0x26318 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1; /* offset : 0x2631c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2; /* offset : 0x26320 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2; /* offset : 0x26324 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2; /* offset : 0x26328 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2; /* offset : 0x2632c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2; /* offset : 0x26330 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2; /* offset : 0x26334 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2; /* offset : 0x26338 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2; /* offset : 0x2633c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2; /* offset : 0x26340 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2; /* offset : 0x26344 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2; /* offset : 0x26348 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2; /* offset : 0x2634c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2; /* offset : 0x26350 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2; /* offset : 0x26354 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2; /* offset : 0x26358 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2; /* offset : 0x2635c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2; /* offset : 0x26360 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2; /* offset : 0x26364 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2; /* offset : 0x26368 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2; /* offset : 0x2636c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2; /* offset : 0x26370 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2; /* offset : 0x26374 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2; /* offset : 0x26378 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2; /* offset : 0x2637c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2; /* offset : 0x26380 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2; /* offset : 0x26384 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2; /* offset : 0x26388 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2; /* offset : 0x2638c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2; /* offset : 0x26390 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2; /* offset : 0x26394 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2; /* offset : 0x26398 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2; /* offset : 0x2639c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2; /* offset : 0x263a0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2; /* offset : 0x263a4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3; /* offset : 0x263a8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3; /* offset : 0x263ac */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3; /* offset : 0x263b0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3; /* offset : 0x263b4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3; /* offset : 0x263b8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3; /* offset : 0x263bc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3; /* offset : 0x263c0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3; /* offset : 0x263c4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3; /* offset : 0x263c8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3; /* offset : 0x263cc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3; /* offset : 0x263d0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3; /* offset : 0x263d4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3; /* offset : 0x263d8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3; /* offset : 0x263dc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3; /* offset : 0x263e0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3; /* offset : 0x263e4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3; /* offset : 0x263e8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3; /* offset : 0x263ec */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3; /* offset : 0x263f0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3; /* offset : 0x263f4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3; /* offset : 0x263f8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3; /* offset : 0x263fc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3; /* offset : 0x26400 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3; /* offset : 0x26404 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3; /* offset : 0x26408 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3; /* offset : 0x2640c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3; /* offset : 0x26410 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3; /* offset : 0x26414 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3; /* offset : 0x26418 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3; /* offset : 0x2641c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3; /* offset : 0x26420 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3; /* offset : 0x26424 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3; /* offset : 0x26428 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3; /* offset : 0x2642c */
		uint32_t reserved_8[756];
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1; /* offset : 0x27000 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2; /* offset : 0x27004 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3; /* offset : 0x27008 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr4 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr4; /* offset : 0x2700c */
		union aw_ucie_test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset; /* offset : 0x27010 */
		union aw_ucie_test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset; /* offset : 0x27014 */
		uint32_t reserved_9[2];
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl; /* offset : 0x27020 */
		uint32_t reserved_10;
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1; /* offset : 0x27028 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2 adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2; /* offset : 0x2702c */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts adapter_test_comp_reg_reg_adapter_tstcmp_test_sts; /* offset : 0x27030 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0; /* offset : 0x27034 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack1 adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack1; /* offset : 0x27038 */
		uint32_t reserved_11;
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1 adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1; /* offset : 0x27040 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2 adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2; /* offset : 0x27044 */
		uint32_t reserved_12[1006];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1; /* offset : 0x28000 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_2; /* offset : 0x28004 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2; /* offset : 0x28008 */
		uint32_t reserved_13;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1; /* offset : 0x28010 */
		uint32_t reserved_14;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_1; /* offset : 0x28018 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_2; /* offset : 0x2801c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_1; /* offset : 0x28020 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_2; /* offset : 0x28024 */
		uint32_t reserved_15[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1; /* offset : 0x28400 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_2; /* offset : 0x28404 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2; /* offset : 0x28408 */
		uint32_t reserved_16;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1; /* offset : 0x28410 */
		uint32_t reserved_17;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_1; /* offset : 0x28418 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_2; /* offset : 0x2841c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_1; /* offset : 0x28420 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_2; /* offset : 0x28424 */
		uint32_t reserved_18[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_1; /* offset : 0x28800 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_2; /* offset : 0x28804 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl2; /* offset : 0x28808 */
		uint32_t reserved_19;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat1; /* offset : 0x28810 */
		uint32_t reserved_20;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_1; /* offset : 0x28818 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_2; /* offset : 0x2881c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_1; /* offset : 0x28820 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_2; /* offset : 0x28824 */
		uint32_t reserved_21[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_1; /* offset : 0x28c00 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_2; /* offset : 0x28c04 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl2; /* offset : 0x28c08 */
		uint32_t reserved_22;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat1; /* offset : 0x28c10 */
		uint32_t reserved_23;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_1; /* offset : 0x28c18 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_2; /* offset : 0x28c1c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_1; /* offset : 0x28c20 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_2; /* offset : 0x28c24 */
		uint32_t reserved_24[246];
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg1 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg1; /* offset : 0x29000 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg2 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg2; /* offset : 0x29004 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg3 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg3; /* offset : 0x29008 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg4 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg4; /* offset : 0x2900c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg5 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg5; /* offset : 0x29010 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_stall_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_stall_rdreg1; /* offset : 0x29014 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_cfg adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_cfg; /* offset : 0x29018 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg1; /* offset : 0x2901c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg2; /* offset : 0x29020 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg3 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg3; /* offset : 0x29024 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg4 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg4; /* offset : 0x29028 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_cfg adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_cfg; /* offset : 0x2902c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg1; /* offset : 0x29030 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg2; /* offset : 0x29034 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg3 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg3; /* offset : 0x29038 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg4 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg4; /* offset : 0x2903c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg5 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg5; /* offset : 0x29040 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg1; /* offset : 0x29044 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask; /* offset : 0x29048 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg2; /* offset : 0x2904c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask2 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask2; /* offset : 0x29050 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg1 adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg1; /* offset : 0x29054 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg2 adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg2; /* offset : 0x29058 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_rdreg adapter_imp_spec_fdi_reg_adapter_fdi_lp_rdreg; /* offset : 0x2905c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_reg; /* offset : 0x29060 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_mask_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_mask_reg; /* offset : 0x29064 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_reg; /* offset : 0x29068 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_mask_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_mask_reg; /* offset : 0x2906c */
		uint32_t reserved_25[484];
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1; /* offset : 0x29800 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2; /* offset : 0x29804 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3; /* offset : 0x29808 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr4 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr4; /* offset : 0x2980c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_config adapter_imp_spec_rdi_reg_reg_adapter_impsp_config; /* offset : 0x29810 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_fifo_wm adapter_imp_spec_rdi_reg_reg_adapter_fifo_wm; /* offset : 0x29814 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg1 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg1; /* offset : 0x29818 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg2 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg2; /* offset : 0x2981c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg3 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg3; /* offset : 0x29820 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg4 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg4; /* offset : 0x29824 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg5 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg5; /* offset : 0x29828 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg6 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg6; /* offset : 0x2982c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg7 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg7; /* offset : 0x29830 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_stall_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_stall_rdreg1; /* offset : 0x29834 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_cfg; /* offset : 0x29838 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg1; /* offset : 0x2983c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg2; /* offset : 0x29840 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg3; /* offset : 0x29844 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg4; /* offset : 0x29848 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_cfg; /* offset : 0x2984c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg1; /* offset : 0x29850 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg2; /* offset : 0x29854 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg3; /* offset : 0x29858 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg4; /* offset : 0x2985c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg5; /* offset : 0x29860 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_cfg; /* offset : 0x29864 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg1; /* offset : 0x29868 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg2; /* offset : 0x2986c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg3; /* offset : 0x29870 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg4; /* offset : 0x29874 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg5; /* offset : 0x29878 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_cfg; /* offset : 0x2987c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg1; /* offset : 0x29880 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg2; /* offset : 0x29884 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg3; /* offset : 0x29888 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg4; /* offset : 0x2988c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg5; /* offset : 0x29890 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg1; /* offset : 0x29894 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask; /* offset : 0x29898 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg2; /* offset : 0x2989c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask2 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask2; /* offset : 0x298a0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_lp_config adapter_imp_spec_rdi_reg_adapter_rdi_lp_config; /* offset : 0x298a4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_rdreg6 adapter_imp_spec_rdi_reg_adapter_rdi_pl_rdreg6; /* offset : 0x298a8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1 adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1; /* offset : 0x298ac */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1_mask adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1_mask; /* offset : 0x298b0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2 adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2; /* offset : 0x298b4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2_mask adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2_mask; /* offset : 0x298b8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_int2 adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_int2; /* offset : 0x298bc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_int2_mask adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_int2_mask; /* offset : 0x298c0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_stat_int2 adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_stat_int2; /* offset : 0x298c4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_int2_mask adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_int2_mask; /* offset : 0x298c8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg1_w; /* offset : 0x298cc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg2_w; /* offset : 0x298d0 */
		uint32_t reserved_26;
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg3_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg3_w; /* offset : 0x298d8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_w; /* offset : 0x298dc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_1_w; /* offset : 0x298e0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_2_w; /* offset : 0x298e4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1_w; /* offset : 0x298e8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2_w; /* offset : 0x298ec */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1_w; /* offset : 0x298f0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2_w; /* offset : 0x298f4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1_w; /* offset : 0x298f8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2_w; /* offset : 0x298fc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log1_w; /* offset : 0x29900 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log2_w; /* offset : 0x29904 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log1_w; /* offset : 0x29908 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log2_w; /* offset : 0x2990c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log1_w; /* offset : 0x29910 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log2_w; /* offset : 0x29914 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log1_w; /* offset : 0x29918 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log2_w; /* offset : 0x2991c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log1_w; /* offset : 0x29920 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log2_w; /* offset : 0x29924 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log1_w; /* offset : 0x29928 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log2_w; /* offset : 0x2992c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1_w; /* offset : 0x29930 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2_w; /* offset : 0x29934 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1_w; /* offset : 0x29938 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2_w; /* offset : 0x2993c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg1 adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg1; /* offset : 0x29940 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg2 adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg2; /* offset : 0x29944 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg1 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg1; /* offset : 0x29948 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg2 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg2; /* offset : 0x2994c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg3 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg3; /* offset : 0x29950 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg4 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg4; /* offset : 0x29954 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_static_counter_cfg adapter_imp_spec_rdi_reg_adapter_static_counter_cfg; /* offset : 0x29958 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0 adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0; /* offset : 0x2995c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1 adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1; /* offset : 0x29960 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_parity_err_count_threshold_reg adapter_imp_spec_rdi_reg_adapter_parity_err_count_threshold_reg; /* offset : 0x29964 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_count_threshold_reg adapter_imp_spec_rdi_reg_adapter_crc_err_count_threshold_reg; /* offset : 0x29968 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config1_reg adapter_imp_spec_rdi_reg_adapter_timeout_count_config1_reg; /* offset : 0x2996c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config2_reg adapter_imp_spec_rdi_reg_adapter_timeout_count_config2_reg; /* offset : 0x29970 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_impsp_sts1_reg adapter_imp_spec_rdi_reg_adapter_impsp_sts1_reg; /* offset : 0x29974 */
		uint32_t reserved_27[418];
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1; /* offset : 0x2a000 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2; /* offset : 0x2a004 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3; /* offset : 0x2a008 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4; /* offset : 0x2a00c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg1 phy_imp_spec_reg_phy_rdi_txsb_cfg1; /* offset : 0x2a010 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg2 phy_imp_spec_reg_phy_rdi_txsb_cfg2; /* offset : 0x2a014 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg3 phy_imp_spec_reg_phy_rdi_txsb_cfg3; /* offset : 0x2a018 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg4 phy_imp_spec_reg_phy_rdi_txsb_cfg4; /* offset : 0x2a01c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg5 phy_imp_spec_reg_phy_rdi_txsb_cfg5; /* offset : 0x2a020 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg6 phy_imp_spec_reg_phy_rdi_txsb_cfg6; /* offset : 0x2a024 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg7 phy_imp_spec_reg_phy_rdi_txsb_cfg7; /* offset : 0x2a028 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_stall_rdreg1 phy_imp_spec_reg_phy_rdi_txsb_stall_rdreg1; /* offset : 0x2a02c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_cfg phy_imp_spec_reg_phy_rdi_rxsbacccom_cfg; /* offset : 0x2a030 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg1; /* offset : 0x2a034 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg2; /* offset : 0x2a038 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg3; /* offset : 0x2a03c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg4; /* offset : 0x2a040 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_cfg phy_imp_spec_reg_phy_rdi_rxsbaccreq_cfg; /* offset : 0x2a044 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg1; /* offset : 0x2a048 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg2; /* offset : 0x2a04c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg3; /* offset : 0x2a050 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg4; /* offset : 0x2a054 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg5; /* offset : 0x2a058 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_cfg phy_imp_spec_reg_phy_rdi_rxsbmsg_cfg; /* offset : 0x2a05c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg1; /* offset : 0x2a060 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg2; /* offset : 0x2a064 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg3; /* offset : 0x2a068 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg4; /* offset : 0x2a06c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg5; /* offset : 0x2a070 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_cfg phy_imp_spec_reg_phy_rdi_rxsbvmsg_cfg; /* offset : 0x2a074 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg1; /* offset : 0x2a078 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg2; /* offset : 0x2a07c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg3; /* offset : 0x2a080 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg4; /* offset : 0x2a084 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg5; /* offset : 0x2a088 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1 phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1; /* offset : 0x2a08c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1_mask phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1_mask; /* offset : 0x2a090 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1 phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1; /* offset : 0x2a094 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1_mask phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1_mask; /* offset : 0x2a098 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_lp_rdreg phy_imp_spec_reg_phy_rdi_lp_rdreg; /* offset : 0x2a09c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_pl_cfg1 phy_imp_spec_reg_phy_rdi_pl_cfg1; /* offset : 0x2a0a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m0_err_log0_w; /* offset : 0x2a0a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m1_err_log0_w; /* offset : 0x2a0a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m2_err_log0_w; /* offset : 0x2a0ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m3_err_log0_w; /* offset : 0x2a0b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m0_err_log1_w; /* offset : 0x2a0b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m1_err_log1_w; /* offset : 0x2a0b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m2_err_log1_w; /* offset : 0x2a0bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m3_err_log1_w; /* offset : 0x2a0c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1_w phy_imp_spec_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1_w; /* offset : 0x2a0c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg1_w; /* offset : 0x2a0c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg2_w; /* offset : 0x2a0cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg1_w; /* offset : 0x2a0d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg2_w; /* offset : 0x2a0d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg1_w; /* offset : 0x2a0d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg2_w; /* offset : 0x2a0dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg1_w; /* offset : 0x2a0e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg2_w; /* offset : 0x2a0e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair_w; /* offset : 0x2a0e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair_w; /* offset : 0x2a0ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair_w; /* offset : 0x2a0f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair_w; /* offset : 0x2a0f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_pcie_extnd_cap_hdr_w phy_imp_spec_reg_reg_phy_d2d_pcie_extnd_cap_hdr_w; /* offset : 0x2a0f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr1_w phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr1_w; /* offset : 0x2a0fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr2_w phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr2_w; /* offset : 0x2a100 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_uhm_status_w phy_imp_spec_reg_reg_phy_d2d_uhm_status_w; /* offset : 0x2a104 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0_w; /* offset : 0x2a108 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0_w; /* offset : 0x2a10c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0_w; /* offset : 0x2a110 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0_w; /* offset : 0x2a114 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0_w; /* offset : 0x2a118 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0_w; /* offset : 0x2a11c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0_w; /* offset : 0x2a120 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0_w; /* offset : 0x2a124 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0_w; /* offset : 0x2a128 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0_w; /* offset : 0x2a12c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0_w; /* offset : 0x2a130 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0_w; /* offset : 0x2a134 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0_w; /* offset : 0x2a138 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0_w; /* offset : 0x2a13c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0_w; /* offset : 0x2a140 */
		uint32_t reserved_28[2];
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0_w; /* offset : 0x2a14c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0_w; /* offset : 0x2a150 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0_w; /* offset : 0x2a154 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0_w; /* offset : 0x2a158 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0_w; /* offset : 0x2a15c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0_w; /* offset : 0x2a160 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0_w; /* offset : 0x2a164 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0_w; /* offset : 0x2a168 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0_w; /* offset : 0x2a16c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0_w; /* offset : 0x2a170 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0_w; /* offset : 0x2a174 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0_w; /* offset : 0x2a178 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0_w; /* offset : 0x2a17c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0_w; /* offset : 0x2a180 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0_w; /* offset : 0x2a184 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0_w; /* offset : 0x2a188 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0_w; /* offset : 0x2a18c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0_w; /* offset : 0x2a190 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0_w; /* offset : 0x2a194 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1_w; /* offset : 0x2a198 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1_w; /* offset : 0x2a19c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1_w; /* offset : 0x2a1a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1_w; /* offset : 0x2a1a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1_w; /* offset : 0x2a1a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1_w; /* offset : 0x2a1ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1_w; /* offset : 0x2a1b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1_w; /* offset : 0x2a1b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1_w; /* offset : 0x2a1b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1_w; /* offset : 0x2a1bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1_w; /* offset : 0x2a1c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1_w; /* offset : 0x2a1c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1_w; /* offset : 0x2a1c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1_w; /* offset : 0x2a1cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1_w; /* offset : 0x2a1d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1_w; /* offset : 0x2a1d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1_w; /* offset : 0x2a1d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1_w; /* offset : 0x2a1dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1_w; /* offset : 0x2a1e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1_w; /* offset : 0x2a1e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1_w; /* offset : 0x2a1e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1_w; /* offset : 0x2a1ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1_w; /* offset : 0x2a1f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1_w; /* offset : 0x2a1f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1_w; /* offset : 0x2a1f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1_w; /* offset : 0x2a1fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1_w; /* offset : 0x2a200 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1_w; /* offset : 0x2a204 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1_w; /* offset : 0x2a208 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1_w; /* offset : 0x2a20c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1_w; /* offset : 0x2a210 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1_w; /* offset : 0x2a214 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1_w; /* offset : 0x2a218 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1_w; /* offset : 0x2a21c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2_w; /* offset : 0x2a220 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2_w; /* offset : 0x2a224 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2_w; /* offset : 0x2a228 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2_w; /* offset : 0x2a22c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2_w; /* offset : 0x2a230 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2_w; /* offset : 0x2a234 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2_w; /* offset : 0x2a238 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2_w; /* offset : 0x2a23c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2_w; /* offset : 0x2a240 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2_w; /* offset : 0x2a244 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2_w; /* offset : 0x2a248 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2_w; /* offset : 0x2a24c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2_w; /* offset : 0x2a250 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2_w; /* offset : 0x2a254 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2_w; /* offset : 0x2a258 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2_w; /* offset : 0x2a25c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2_w; /* offset : 0x2a260 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2_w; /* offset : 0x2a264 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2_w; /* offset : 0x2a268 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2_w; /* offset : 0x2a26c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2_w; /* offset : 0x2a270 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2_w; /* offset : 0x2a274 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2_w; /* offset : 0x2a278 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2_w; /* offset : 0x2a27c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2_w; /* offset : 0x2a280 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2_w; /* offset : 0x2a284 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2_w; /* offset : 0x2a288 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2_w; /* offset : 0x2a28c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2_w; /* offset : 0x2a290 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2_w; /* offset : 0x2a294 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2_w; /* offset : 0x2a298 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2_w; /* offset : 0x2a29c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2_w; /* offset : 0x2a2a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2_w; /* offset : 0x2a2a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3_w; /* offset : 0x2a2a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3_w; /* offset : 0x2a2ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3_w; /* offset : 0x2a2b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3_w; /* offset : 0x2a2b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3_w; /* offset : 0x2a2b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3_w; /* offset : 0x2a2bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3_w; /* offset : 0x2a2c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3_w; /* offset : 0x2a2c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3_w; /* offset : 0x2a2c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3_w; /* offset : 0x2a2cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3_w; /* offset : 0x2a2d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3_w; /* offset : 0x2a2d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3_w; /* offset : 0x2a2d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3_w; /* offset : 0x2a2dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3_w; /* offset : 0x2a2e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3_w; /* offset : 0x2a2e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3_w; /* offset : 0x2a2e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3_w; /* offset : 0x2a2ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3_w; /* offset : 0x2a2f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3_w; /* offset : 0x2a2f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3_w; /* offset : 0x2a2f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3_w; /* offset : 0x2a2fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3_w; /* offset : 0x2a300 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3_w; /* offset : 0x2a304 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3_w; /* offset : 0x2a308 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3_w; /* offset : 0x2a30c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3_w; /* offset : 0x2a310 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3_w; /* offset : 0x2a314 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3_w; /* offset : 0x2a318 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3_w; /* offset : 0x2a31c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3_w; /* offset : 0x2a320 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3_w; /* offset : 0x2a324 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3_w; /* offset : 0x2a328 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3_w; /* offset : 0x2a32c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_status1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_status1_w; /* offset : 0x2a330 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_1_w; /* offset : 0x2a334 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_2_w; /* offset : 0x2a338 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_1_w; /* offset : 0x2a33c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_2_w; /* offset : 0x2a340 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat1_w; /* offset : 0x2a344 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_1_w; /* offset : 0x2a348 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_2_w; /* offset : 0x2a34c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_1_w; /* offset : 0x2a350 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_2_w; /* offset : 0x2a354 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat1_w; /* offset : 0x2a358 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_1_w; /* offset : 0x2a35c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_2_w; /* offset : 0x2a360 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_1_w; /* offset : 0x2a364 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_2_w; /* offset : 0x2a368 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat1_w; /* offset : 0x2a36c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_1_w; /* offset : 0x2a370 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_2_w; /* offset : 0x2a374 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_1_w; /* offset : 0x2a378 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_2_w; /* offset : 0x2a37c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1_w; /* offset : 0x2a380 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2_w; /* offset : 0x2a384 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3_w; /* offset : 0x2a388 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4_w; /* offset : 0x2a38c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_cap_w phy_imp_spec_reg_reg_phy_d2d_phy_cap_w; /* offset : 0x2a390 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_stat_w phy_imp_spec_reg_reg_phy_d2d_phy_stat_w; /* offset : 0x2a394 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_ctrl1_2_w; /* offset : 0x2a398 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_ctrl1_2_w; /* offset : 0x2a39c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_ctrl1_2_w; /* offset : 0x2a3a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_ctrl1_2_w; /* offset : 0x2a3a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tx_mmpl_cfg phy_imp_spec_reg_reg_phy_tx_mmpl_cfg; /* offset : 0x2a3a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rx_mmpl_cfg phy_imp_spec_reg_reg_phy_rx_mmpl_cfg; /* offset : 0x2a3ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_mmpl_sts phy_imp_spec_reg_reg_phy_mmpl_sts; /* offset : 0x2a3b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_rst_cfg phy_imp_spec_reg_reg_phy_rdi_rst_cfg; /* offset : 0x2a3b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1 phy_imp_spec_reg_reg_phy_rdi_lp_int1; /* offset : 0x2a3b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1_mask phy_imp_spec_reg_reg_phy_rdi_lp_int1_mask; /* offset : 0x2a3bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2 phy_imp_spec_reg_reg_phy_rdi_lp_int2; /* offset : 0x2a3c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2_mask phy_imp_spec_reg_reg_phy_rdi_lp_int2_mask; /* offset : 0x2a3c4 */
		union aw_ucie_phy_imp_spec_reg_spare_in_ctrl phy_imp_spec_reg_spare_in_ctrl; /* offset : 0x2a3c8 */
		union aw_ucie_phy_imp_spec_reg_spare_out_ctrl phy_imp_spec_reg_spare_out_ctrl; /* offset : 0x2a3cc */
		uint32_t reserved_29[3852];
		union aw_ucie_global_reg_cmn_mcu_ctrl global_reg_cmn_mcu_ctrl; /* offset : 0x2e000 */
		union aw_ucie_global_reg_cmn_mcu_hart_id global_reg_cmn_mcu_hart_id; /* offset : 0x2e004 */
		union aw_ucie_global_reg_cmn_mcu_boot_addr global_reg_cmn_mcu_boot_addr; /* offset : 0x2e008 */
		union aw_ucie_global_reg_cmn_mcu_device_addr global_reg_cmn_mcu_device_addr; /* offset : 0x2e00c */
		union aw_ucie_global_reg_cmn_mcu_dmem global_reg_cmn_mcu_dmem; /* offset : 0x2e010 */
		union aw_ucie_global_reg_cmn_mcu_irq_ctrl1 global_reg_cmn_mcu_irq_ctrl1; /* offset : 0x2e014 */
		union aw_ucie_global_reg_cmn_mcu_irq_ctrl2 global_reg_cmn_mcu_irq_ctrl2; /* offset : 0x2e018 */
		union aw_ucie_global_reg_cmn_mcu_irq global_reg_cmn_mcu_irq; /* offset : 0x2e01c */
		union aw_ucie_global_reg_cmn_mcu_crash_dump3 global_reg_cmn_mcu_crash_dump3; /* offset : 0x2e020 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump2 global_reg_cmn_mcu_crash_dump2; /* offset : 0x2e024 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump1 global_reg_cmn_mcu_crash_dump1; /* offset : 0x2e028 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump0 global_reg_cmn_mcu_crash_dump0; /* offset : 0x2e02c */
		union aw_ucie_global_reg_cmn_mcu_stats global_reg_cmn_mcu_stats; /* offset : 0x2e030 */
		union aw_ucie_global_reg_sram_cfg_rd_data global_reg_sram_cfg_rd_data; /* offset : 0x2e034 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg1 global_reg_cmn_mcu_scratch_reg1; /* offset : 0x2e038 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg2 global_reg_cmn_mcu_scratch_reg2; /* offset : 0x2e03c */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg3 global_reg_cmn_mcu_scratch_reg3; /* offset : 0x2e040 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg4 global_reg_cmn_mcu_scratch_reg4; /* offset : 0x2e044 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg5 global_reg_cmn_mcu_scratch_reg5; /* offset : 0x2e048 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg6 global_reg_cmn_mcu_scratch_reg6; /* offset : 0x2e04c */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg7 global_reg_cmn_mcu_scratch_reg7; /* offset : 0x2e050 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg8 global_reg_cmn_mcu_scratch_reg8; /* offset : 0x2e054 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg9 global_reg_cmn_mcu_scratch_reg9; /* offset : 0x2e058 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg10 global_reg_cmn_mcu_scratch_reg10; /* offset : 0x2e05c */
		union aw_ucie_global_reg_reg_global_cmn_cfg1 global_reg_reg_global_cmn_cfg1; /* offset : 0x2e060 */
		union aw_ucie_global_reg_reg_global_intr1_summary global_reg_reg_global_intr1_summary; /* offset : 0x2e064 */
		union aw_ucie_global_reg_reg_global_intr1_summary_mask global_reg_reg_global_intr1_summary_mask; /* offset : 0x2e068 */
		union aw_ucie_global_reg_reg_global_intr2_summary global_reg_reg_global_intr2_summary; /* offset : 0x2e06c */
		union aw_ucie_global_reg_reg_global_intr2_summary_mask global_reg_reg_global_intr2_summary_mask; /* offset : 0x2e070 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_pcie_extnd_cap_hdr_w global_reg_reg_glbl_dvsec1_pcie_extnd_cap_hdr_w; /* offset : 0x2e074 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_hdr1_w global_reg_reg_glbl_dvsec1_hdr1_w; /* offset : 0x2e078 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_hdr2_and_cap_descriptor_w global_reg_reg_glbl_dvsec1_hdr2_and_cap_descriptor_w; /* offset : 0x2e07c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_ucie_link_cap_and_status_w global_reg_reg_glbl_dvsec1_ucie_link_cap_and_status_w; /* offset : 0x2e080 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_link_sts_evnt_err_nf_ctrl_loc0_w global_reg_reg_glbl_dvsec1_link_sts_evnt_err_nf_ctrl_loc0_w; /* offset : 0x2e084 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_low_w global_reg_reg_glbl_dvsec1_reg_loc0_low_w; /* offset : 0x2e088 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_high_w global_reg_reg_glbl_dvsec1_reg_loc0_high_w; /* offset : 0x2e08c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_low_w global_reg_reg_glbl_dvsec1_reg_loc1_low_w; /* offset : 0x2e090 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_high_w global_reg_reg_glbl_dvsec1_reg_loc1_high_w; /* offset : 0x2e094 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_low_w global_reg_reg_glbl_dvsec1_reg_loc2_low_w; /* offset : 0x2e098 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_high_w global_reg_reg_glbl_dvsec1_reg_loc2_high_w; /* offset : 0x2e09c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_low_w global_reg_reg_glbl_dvsec1_reg_loc3_low_w; /* offset : 0x2e0a0 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_high_w global_reg_reg_glbl_dvsec1_reg_loc3_high_w; /* offset : 0x2e0a4 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_sb_mlbox_ctrl_stats_assoc_port_num_w global_reg_reg_glbl_dvsec1_sb_mlbox_ctrl_stats_assoc_port_num_w; /* offset : 0x2e0a8 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1_w global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1_w; /* offset : 0x2e0ac */
		union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2_w global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2_w; /* offset : 0x2e0b0 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr1_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr1_w; /* offset : 0x2e0b4 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr2_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr2_w; /* offset : 0x2e0b8 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr3_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr3_w; /* offset : 0x2e0bc */
		union aw_ucie_global_reg_reg_glbl_d2d_adapter_and_phy_testcompl_reg_blk_offset_w global_reg_reg_glbl_d2d_adapter_and_phy_testcompl_reg_blk_offset_w; /* offset : 0x2e0c0 */
		union aw_ucie_global_reg_spare_out_ctrl global_reg_spare_out_ctrl; /* offset : 0x2e0c4 */
		union aw_ucie_global_reg_spare_in_ctrl global_reg_spare_in_ctrl; /* offset : 0x2e0c8 */
		union aw_ucie_global_reg_reg_glbl_apb_response_timeout global_reg_reg_glbl_apb_response_timeout; /* offset : 0x2e0cc */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int1 global_reg_reg_glbl_cmn_top_int1; /* offset : 0x2e0d0 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int2 global_reg_reg_glbl_cmn_top_int2; /* offset : 0x2e0d4 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int1_mask global_reg_reg_glbl_cmn_top_int1_mask; /* offset : 0x2e0d8 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int2_mask global_reg_reg_glbl_cmn_top_int2_mask; /* offset : 0x2e0dc */
		union aw_ucie_global_reg_reg_glbl_dvsec2_pcie_extnd_cap_hdr_w global_reg_reg_glbl_dvsec2_pcie_extnd_cap_hdr_w; /* offset : 0x2e0e0 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_hdr1_w global_reg_reg_glbl_dvsec2_hdr1_w; /* offset : 0x2e0e4 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_hdr2_w global_reg_reg_glbl_dvsec2_hdr2_w; /* offset : 0x2e0e8 */
		uint32_t reserved_30[965];
		union aw_ucie_phy_cmn_reg_cmn_csr_ctrl phy_cmn_reg_cmn_csr_ctrl; /* offset : 0x2f000 */
		union aw_ucie_phy_cmn_reg_cmn_ctrl phy_cmn_reg_cmn_ctrl; /* offset : 0x2f004 */
		union aw_ucie_phy_cmn_reg_cmn_ctrl_rdreg phy_cmn_reg_cmn_ctrl_rdreg; /* offset : 0x2f008 */
		union aw_ucie_phy_cmn_reg_cmnafe_clr phy_cmn_reg_cmnafe_clr; /* offset : 0x2f00c */
		union aw_ucie_phy_cmn_reg_cmnafe_piack_rdreg phy_cmn_reg_cmnafe_piack_rdreg; /* offset : 0x2f010 */
		union aw_ucie_phy_cmn_reg_cmnafe_pictrl phy_cmn_reg_cmnafe_pictrl; /* offset : 0x2f014 */
		union aw_ucie_phy_cmn_reg_cmnafe_pireq phy_cmn_reg_cmnafe_pireq; /* offset : 0x2f018 */
		union aw_ucie_phy_cmn_reg_cmnafe_pival phy_cmn_reg_cmnafe_pival; /* offset : 0x2f01c */
		union aw_ucie_phy_cmn_reg_cmnafe_pival_rdreg phy_cmn_reg_cmnafe_pival_rdreg; /* offset : 0x2f020 */
		union aw_ucie_phy_cmn_reg_cmnafe_rdreg phy_cmn_reg_cmnafe_rdreg; /* offset : 0x2f024 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg1 phy_cmn_reg_cmnafe_reg1; /* offset : 0x2f028 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg2 phy_cmn_reg_cmnafe_reg2; /* offset : 0x2f02c */
		union aw_ucie_phy_cmn_reg_cmnafe_reg3 phy_cmn_reg_cmnafe_reg3; /* offset : 0x2f030 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg4 phy_cmn_reg_cmnafe_reg4; /* offset : 0x2f034 */
		union aw_ucie_phy_cmn_reg_cmnafepd phy_cmn_reg_cmnafepd; /* offset : 0x2f038 */
		union aw_ucie_phy_cmn_reg_cmnaferst phy_cmn_reg_cmnaferst; /* offset : 0x2f03c */
		union aw_ucie_phy_cmn_reg_cmnatest phy_cmn_reg_cmnatest; /* offset : 0x2f040 */
		union aw_ucie_phy_cmn_reg_cmnatest_rdreg phy_cmn_reg_cmnatest_rdreg; /* offset : 0x2f044 */
		union aw_ucie_phy_cmn_reg_cmnclkctrl phy_cmn_reg_cmnclkctrl; /* offset : 0x2f048 */
		union aw_ucie_phy_cmn_reg_cmnpll_rdreg phy_cmn_reg_cmnpll_rdreg; /* offset : 0x2f04c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg1 phy_cmn_reg_cmnpll_reg1; /* offset : 0x2f050 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg2 phy_cmn_reg_cmnpll_reg2; /* offset : 0x2f054 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg3 phy_cmn_reg_cmnpll_reg3; /* offset : 0x2f058 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg4 phy_cmn_reg_cmnpll_reg4; /* offset : 0x2f05c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg5 phy_cmn_reg_cmnpll_reg5; /* offset : 0x2f060 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg6 phy_cmn_reg_cmnpll_reg6; /* offset : 0x2f064 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg7 phy_cmn_reg_cmnpll_reg7; /* offset : 0x2f068 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg8 phy_cmn_reg_cmnpll_reg8; /* offset : 0x2f06c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg9 phy_cmn_reg_cmnpll_reg9; /* offset : 0x2f070 */
		union aw_ucie_phy_cmn_reg_cmnpmon phy_cmn_reg_cmnpmon; /* offset : 0x2f074 */
		union aw_ucie_phy_cmn_reg_cmnpmon_rdreg phy_cmn_reg_cmnpmon_rdreg; /* offset : 0x2f078 */
		union aw_ucie_phy_cmn_reg_cmnrxtx_reg1 phy_cmn_reg_cmnrxtx_reg1; /* offset : 0x2f07c */
		union aw_ucie_phy_cmn_reg_cmnrxtx_reg2 phy_cmn_reg_cmnrxtx_reg2; /* offset : 0x2f080 */
		union aw_ucie_phy_cmn_reg_cmnsoc_reg1 phy_cmn_reg_cmnsoc_reg1; /* offset : 0x2f084 */
		union aw_ucie_phy_cmn_reg_cmnzqcal_rdreg phy_cmn_reg_cmnzqcal_rdreg; /* offset : 0x2f088 */
		union aw_ucie_phy_cmn_reg_cmnzqcal_reg1 phy_cmn_reg_cmnzqcal_reg1; /* offset : 0x2f08c */
		union aw_ucie_phy_cmn_reg_cmnzqcal_reg2 phy_cmn_reg_cmnzqcal_reg2; /* offset : 0x2f090 */
		union aw_ucie_phy_cmn_reg_sram_cfg phy_cmn_reg_sram_cfg; /* offset : 0x2f094 */
		uint32_t reserved_31[986];
		union aw_ucie_rx0_reg_rx_csr_ctrl rx0_reg_rx_csr_ctrl; /* offset : 0x30000 */
		union aw_ucie_rx0_reg_rx_ctrl rx0_reg_rx_ctrl; /* offset : 0x30004 */
		union aw_ucie_rx0_reg_rx_ctrl_rdreg rx0_reg_rx_ctrl_rdreg; /* offset : 0x30008 */
		union aw_ucie_rx0_reg_rxcalen rx0_reg_rxcalen; /* offset : 0x3000c */
		union aw_ucie_rx0_reg_rxclkchk_rdreg rx0_reg_rxclkchk_rdreg; /* offset : 0x30010 */
		union aw_ucie_rx0_reg_rxcmn_reg1 rx0_reg_rxcmn_reg1; /* offset : 0x30014 */
		union aw_ucie_rx0_reg_rxcmn_reg2 rx0_reg_rxcmn_reg2; /* offset : 0x30018 */
		union aw_ucie_rx0_reg_rxdatapath_reg0 rx0_reg_rxdatapath_reg0; /* offset : 0x3001c */
		union aw_ucie_rx0_reg_rxdatapath_reg1 rx0_reg_rxdatapath_reg1; /* offset : 0x30020 */
		union aw_ucie_rx0_reg_rxdatapath_reg2 rx0_reg_rxdatapath_reg2; /* offset : 0x30024 */
		union aw_ucie_rx0_reg_rxdatapath_reg3 rx0_reg_rxdatapath_reg3; /* offset : 0x30028 */
		union aw_ucie_rx0_reg_rxdatapath_reg4 rx0_reg_rxdatapath_reg4; /* offset : 0x3002c */
		union aw_ucie_rx0_reg_rxdatapath_reg5 rx0_reg_rxdatapath_reg5; /* offset : 0x30030 */
		union aw_ucie_rx0_reg_rxdatcap_rdreg1 rx0_reg_rxdatcap_rdreg1; /* offset : 0x30034 */
		union aw_ucie_rx0_reg_rxdatcap_rdreg2 rx0_reg_rxdatcap_rdreg2; /* offset : 0x30038 */
		union aw_ucie_rx0_reg_rxdatcap_reg1 rx0_reg_rxdatcap_reg1; /* offset : 0x3003c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg0 rx0_reg_rxdatchk_perlaneid_reg0; /* offset : 0x30040 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg1 rx0_reg_rxdatchk_perlaneid_reg1; /* offset : 0x30044 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg10 rx0_reg_rxdatchk_perlaneid_reg10; /* offset : 0x30048 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg11 rx0_reg_rxdatchk_perlaneid_reg11; /* offset : 0x3004c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg12 rx0_reg_rxdatchk_perlaneid_reg12; /* offset : 0x30050 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg13 rx0_reg_rxdatchk_perlaneid_reg13; /* offset : 0x30054 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg14 rx0_reg_rxdatchk_perlaneid_reg14; /* offset : 0x30058 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg15 rx0_reg_rxdatchk_perlaneid_reg15; /* offset : 0x3005c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg16 rx0_reg_rxdatchk_perlaneid_reg16; /* offset : 0x30060 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg2 rx0_reg_rxdatchk_perlaneid_reg2; /* offset : 0x30064 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg3 rx0_reg_rxdatchk_perlaneid_reg3; /* offset : 0x30068 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg4 rx0_reg_rxdatchk_perlaneid_reg4; /* offset : 0x3006c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg5 rx0_reg_rxdatchk_perlaneid_reg5; /* offset : 0x30070 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg6 rx0_reg_rxdatchk_perlaneid_reg6; /* offset : 0x30074 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg7 rx0_reg_rxdatchk_perlaneid_reg7; /* offset : 0x30078 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg8 rx0_reg_rxdatchk_perlaneid_reg8; /* offset : 0x3007c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg9 rx0_reg_rxdatchk_perlaneid_reg9; /* offset : 0x30080 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg1 rx0_reg_rxdatchk_rdreg1; /* offset : 0x30084 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg10 rx0_reg_rxdatchk_rdreg10; /* offset : 0x30088 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg11 rx0_reg_rxdatchk_rdreg11; /* offset : 0x3008c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg12 rx0_reg_rxdatchk_rdreg12; /* offset : 0x30090 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg2 rx0_reg_rxdatchk_rdreg2; /* offset : 0x30094 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg3 rx0_reg_rxdatchk_rdreg3; /* offset : 0x30098 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg4 rx0_reg_rxdatchk_rdreg4; /* offset : 0x3009c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg5 rx0_reg_rxdatchk_rdreg5; /* offset : 0x300a0 */
		union aw_ucie_rx0_reg_rxdatchk_reg1 rx0_reg_rxdatchk_reg1; /* offset : 0x300a4 */
		union aw_ucie_rx0_reg_rxdatchk_reg13 rx0_reg_rxdatchk_reg13; /* offset : 0x300a8 */
		union aw_ucie_rx0_reg_rxdatchk_reg2 rx0_reg_rxdatchk_reg2; /* offset : 0x300ac */
		union aw_ucie_rx0_reg_rxdatchk_reg3 rx0_reg_rxdatchk_reg3; /* offset : 0x300b0 */
		union aw_ucie_rx0_reg_rxdatchk_reg4 rx0_reg_rxdatchk_reg4; /* offset : 0x300b4 */
		union aw_ucie_rx0_reg_rxdatchk_reg5 rx0_reg_rxdatchk_reg5; /* offset : 0x300b8 */
		union aw_ucie_rx0_reg_rxdatchk_reg6 rx0_reg_rxdatchk_reg6; /* offset : 0x300bc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg0 rx0_reg_rxdatgen_seed_udp_reg0; /* offset : 0x300c0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg1 rx0_reg_rxdatgen_seed_udp_reg1; /* offset : 0x300c4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg10 rx0_reg_rxdatgen_seed_udp_reg10; /* offset : 0x300c8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg11 rx0_reg_rxdatgen_seed_udp_reg11; /* offset : 0x300cc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg12 rx0_reg_rxdatgen_seed_udp_reg12; /* offset : 0x300d0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg13 rx0_reg_rxdatgen_seed_udp_reg13; /* offset : 0x300d4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg14 rx0_reg_rxdatgen_seed_udp_reg14; /* offset : 0x300d8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg15 rx0_reg_rxdatgen_seed_udp_reg15; /* offset : 0x300dc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg16 rx0_reg_rxdatgen_seed_udp_reg16; /* offset : 0x300e0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg17 rx0_reg_rxdatgen_seed_udp_reg17; /* offset : 0x300e4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg18 rx0_reg_rxdatgen_seed_udp_reg18; /* offset : 0x300e8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg19 rx0_reg_rxdatgen_seed_udp_reg19; /* offset : 0x300ec */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg2 rx0_reg_rxdatgen_seed_udp_reg2; /* offset : 0x300f0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg20 rx0_reg_rxdatgen_seed_udp_reg20; /* offset : 0x300f4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg21 rx0_reg_rxdatgen_seed_udp_reg21; /* offset : 0x300f8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg22 rx0_reg_rxdatgen_seed_udp_reg22; /* offset : 0x300fc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg23 rx0_reg_rxdatgen_seed_udp_reg23; /* offset : 0x30100 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg24 rx0_reg_rxdatgen_seed_udp_reg24; /* offset : 0x30104 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg25 rx0_reg_rxdatgen_seed_udp_reg25; /* offset : 0x30108 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg26 rx0_reg_rxdatgen_seed_udp_reg26; /* offset : 0x3010c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg27 rx0_reg_rxdatgen_seed_udp_reg27; /* offset : 0x30110 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg28 rx0_reg_rxdatgen_seed_udp_reg28; /* offset : 0x30114 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg29 rx0_reg_rxdatgen_seed_udp_reg29; /* offset : 0x30118 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg3 rx0_reg_rxdatgen_seed_udp_reg3; /* offset : 0x3011c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg30 rx0_reg_rxdatgen_seed_udp_reg30; /* offset : 0x30120 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg31 rx0_reg_rxdatgen_seed_udp_reg31; /* offset : 0x30124 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg32 rx0_reg_rxdatgen_seed_udp_reg32; /* offset : 0x30128 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg33 rx0_reg_rxdatgen_seed_udp_reg33; /* offset : 0x3012c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg34 rx0_reg_rxdatgen_seed_udp_reg34; /* offset : 0x30130 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg35 rx0_reg_rxdatgen_seed_udp_reg35; /* offset : 0x30134 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg36 rx0_reg_rxdatgen_seed_udp_reg36; /* offset : 0x30138 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg37 rx0_reg_rxdatgen_seed_udp_reg37; /* offset : 0x3013c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg38 rx0_reg_rxdatgen_seed_udp_reg38; /* offset : 0x30140 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg39 rx0_reg_rxdatgen_seed_udp_reg39; /* offset : 0x30144 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg4 rx0_reg_rxdatgen_seed_udp_reg4; /* offset : 0x30148 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg40 rx0_reg_rxdatgen_seed_udp_reg40; /* offset : 0x3014c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg41 rx0_reg_rxdatgen_seed_udp_reg41; /* offset : 0x30150 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg42 rx0_reg_rxdatgen_seed_udp_reg42; /* offset : 0x30154 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg43 rx0_reg_rxdatgen_seed_udp_reg43; /* offset : 0x30158 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg44 rx0_reg_rxdatgen_seed_udp_reg44; /* offset : 0x3015c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg45 rx0_reg_rxdatgen_seed_udp_reg45; /* offset : 0x30160 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg46 rx0_reg_rxdatgen_seed_udp_reg46; /* offset : 0x30164 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg47 rx0_reg_rxdatgen_seed_udp_reg47; /* offset : 0x30168 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg48 rx0_reg_rxdatgen_seed_udp_reg48; /* offset : 0x3016c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg49 rx0_reg_rxdatgen_seed_udp_reg49; /* offset : 0x30170 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg5 rx0_reg_rxdatgen_seed_udp_reg5; /* offset : 0x30174 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg50 rx0_reg_rxdatgen_seed_udp_reg50; /* offset : 0x30178 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg51 rx0_reg_rxdatgen_seed_udp_reg51; /* offset : 0x3017c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg52 rx0_reg_rxdatgen_seed_udp_reg52; /* offset : 0x30180 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg53 rx0_reg_rxdatgen_seed_udp_reg53; /* offset : 0x30184 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg54 rx0_reg_rxdatgen_seed_udp_reg54; /* offset : 0x30188 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg55 rx0_reg_rxdatgen_seed_udp_reg55; /* offset : 0x3018c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg56 rx0_reg_rxdatgen_seed_udp_reg56; /* offset : 0x30190 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg57 rx0_reg_rxdatgen_seed_udp_reg57; /* offset : 0x30194 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg58 rx0_reg_rxdatgen_seed_udp_reg58; /* offset : 0x30198 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg59 rx0_reg_rxdatgen_seed_udp_reg59; /* offset : 0x3019c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg6 rx0_reg_rxdatgen_seed_udp_reg6; /* offset : 0x301a0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg60 rx0_reg_rxdatgen_seed_udp_reg60; /* offset : 0x301a4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg61 rx0_reg_rxdatgen_seed_udp_reg61; /* offset : 0x301a8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg62 rx0_reg_rxdatgen_seed_udp_reg62; /* offset : 0x301ac */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg63 rx0_reg_rxdatgen_seed_udp_reg63; /* offset : 0x301b0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg64 rx0_reg_rxdatgen_seed_udp_reg64; /* offset : 0x301b4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg65 rx0_reg_rxdatgen_seed_udp_reg65; /* offset : 0x301b8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg66 rx0_reg_rxdatgen_seed_udp_reg66; /* offset : 0x301bc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg67 rx0_reg_rxdatgen_seed_udp_reg67; /* offset : 0x301c0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg68 rx0_reg_rxdatgen_seed_udp_reg68; /* offset : 0x301c4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg69 rx0_reg_rxdatgen_seed_udp_reg69; /* offset : 0x301c8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg7 rx0_reg_rxdatgen_seed_udp_reg7; /* offset : 0x301cc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg70 rx0_reg_rxdatgen_seed_udp_reg70; /* offset : 0x301d0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg71 rx0_reg_rxdatgen_seed_udp_reg71; /* offset : 0x301d4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg72 rx0_reg_rxdatgen_seed_udp_reg72; /* offset : 0x301d8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg73 rx0_reg_rxdatgen_seed_udp_reg73; /* offset : 0x301dc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg8 rx0_reg_rxdatgen_seed_udp_reg8; /* offset : 0x301e0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg9 rx0_reg_rxdatgen_seed_udp_reg9; /* offset : 0x301e4 */
		union aw_ucie_rx0_reg_rxhip_clr rx0_reg_rxhip_clr; /* offset : 0x301e8 */
		union aw_ucie_rx0_reg_rxhip_piack_rdreg rx0_reg_rxhip_piack_rdreg; /* offset : 0x301ec */
		union aw_ucie_rx0_reg_rxhip_pictrl rx0_reg_rxhip_pictrl; /* offset : 0x301f0 */
		union aw_ucie_rx0_reg_rxhip_pireq rx0_reg_rxhip_pireq; /* offset : 0x301f4 */
		union aw_ucie_rx0_reg_rxhip_pival rx0_reg_rxhip_pival; /* offset : 0x301f8 */
		union aw_ucie_rx0_reg_rxhip_pival_rdreg rx0_reg_rxhip_pival_rdreg; /* offset : 0x301fc */
		union aw_ucie_rx0_reg_rxhip_rdreg1 rx0_reg_rxhip_rdreg1; /* offset : 0x30200 */
		union aw_ucie_rx0_reg_rxhipcmn_reg1 rx0_reg_rxhipcmn_reg1; /* offset : 0x30204 */
		union aw_ucie_rx0_reg_rxhipcmnio_reg1 rx0_reg_rxhipcmnio_reg1; /* offset : 0x30208 */
		union aw_ucie_rx0_reg_rxhipcmnio_reg2 rx0_reg_rxhipcmnio_reg2; /* offset : 0x3020c */
		union aw_ucie_rx0_reg_rxhipcmnio_reg3 rx0_reg_rxhipcmnio_reg3; /* offset : 0x30210 */
		union aw_ucie_rx0_reg_rxhipctrl_reg1 rx0_reg_rxhipctrl_reg1; /* offset : 0x30214 */
		union aw_ucie_rx0_reg_rxhipdqs_reg1 rx0_reg_rxhipdqs_reg1; /* offset : 0x30218 */
		union aw_ucie_rx0_reg_rxhipdqs_reg2 rx0_reg_rxhipdqs_reg2; /* offset : 0x3021c */
		union aw_ucie_rx0_reg_rxhipio_reg1 rx0_reg_rxhipio_reg1; /* offset : 0x30220 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg1 rx0_reg_rxhipiondesync_rdreg1; /* offset : 0x30224 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg2 rx0_reg_rxhipiondesync_rdreg2; /* offset : 0x30228 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg3 rx0_reg_rxhipiondesync_rdreg3; /* offset : 0x3022c */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg1 rx0_reg_rxhipiosampler_rdreg1; /* offset : 0x30230 */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg2 rx0_reg_rxhipiosampler_rdreg2; /* offset : 0x30234 */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg3 rx0_reg_rxhipiosampler_rdreg3; /* offset : 0x30238 */
		union aw_ucie_rx0_reg_rxhipload_reg1 rx0_reg_rxhipload_reg1; /* offset : 0x3023c */
		union aw_ucie_rx0_reg_rxhipload_reg10 rx0_reg_rxhipload_reg10; /* offset : 0x30240 */
		union aw_ucie_rx0_reg_rxhipload_reg11 rx0_reg_rxhipload_reg11; /* offset : 0x30244 */
		union aw_ucie_rx0_reg_rxhipload_reg12 rx0_reg_rxhipload_reg12; /* offset : 0x30248 */
		union aw_ucie_rx0_reg_rxhipload_reg13 rx0_reg_rxhipload_reg13; /* offset : 0x3024c */
		union aw_ucie_rx0_reg_rxhipload_reg14 rx0_reg_rxhipload_reg14; /* offset : 0x30250 */
		union aw_ucie_rx0_reg_rxhipload_reg15 rx0_reg_rxhipload_reg15; /* offset : 0x30254 */
		union aw_ucie_rx0_reg_rxhipload_reg2 rx0_reg_rxhipload_reg2; /* offset : 0x30258 */
		union aw_ucie_rx0_reg_rxhipload_reg3 rx0_reg_rxhipload_reg3; /* offset : 0x3025c */
		union aw_ucie_rx0_reg_rxhipload_reg4 rx0_reg_rxhipload_reg4; /* offset : 0x30260 */
		union aw_ucie_rx0_reg_rxhipload_reg5 rx0_reg_rxhipload_reg5; /* offset : 0x30264 */
		union aw_ucie_rx0_reg_rxhipload_reg6 rx0_reg_rxhipload_reg6; /* offset : 0x30268 */
		union aw_ucie_rx0_reg_rxhipload_reg7 rx0_reg_rxhipload_reg7; /* offset : 0x3026c */
		union aw_ucie_rx0_reg_rxhipload_reg8 rx0_reg_rxhipload_reg8; /* offset : 0x30270 */
		union aw_ucie_rx0_reg_rxhipload_reg9 rx0_reg_rxhipload_reg9; /* offset : 0x30274 */
		union aw_ucie_rx0_reg_rxhipspare_rdreg1 rx0_reg_rxhipspare_rdreg1; /* offset : 0x30278 */
		union aw_ucie_rx0_reg_rxhipspare_reg1 rx0_reg_rxhipspare_reg1; /* offset : 0x3027c */
		union aw_ucie_rx0_reg_rxhipspare_reg2 rx0_reg_rxhipspare_reg2; /* offset : 0x30280 */
		union aw_ucie_rx0_reg_rxioctrl_reg1 rx0_reg_rxioctrl_reg1; /* offset : 0x30284 */
		union aw_ucie_rx0_reg_rxioctrl_reg2 rx0_reg_rxioctrl_reg2; /* offset : 0x30288 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg1 rx0_reg_rxioen_afe_ovr_reg1; /* offset : 0x3028c */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg2 rx0_reg_rxioen_afe_ovr_reg2; /* offset : 0x30290 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg3 rx0_reg_rxioen_afe_ovr_reg3; /* offset : 0x30294 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg4 rx0_reg_rxioen_afe_ovr_reg4; /* offset : 0x30298 */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg1 rx0_reg_rxioen_data_ovr_reg1; /* offset : 0x3029c */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg2 rx0_reg_rxioen_data_ovr_reg2; /* offset : 0x302a0 */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg3 rx0_reg_rxioen_data_ovr_reg3; /* offset : 0x302a4 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg1 rx0_reg_rxioen_ovr_reg1; /* offset : 0x302a8 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg2 rx0_reg_rxioen_ovr_reg2; /* offset : 0x302ac */
		union aw_ucie_rx0_reg_rxioen_ovr_reg3 rx0_reg_rxioen_ovr_reg3; /* offset : 0x302b0 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg4 rx0_reg_rxioen_ovr_reg4; /* offset : 0x302b4 */
		union aw_ucie_rx0_reg_rxndealign_rdreg rx0_reg_rxndealign_rdreg; /* offset : 0x302b8 */
		union aw_ucie_rx0_reg_rxndealign_reg1 rx0_reg_rxndealign_reg1; /* offset : 0x302bc */
		union aw_ucie_rx0_reg_rxndealign_reg2 rx0_reg_rxndealign_reg2; /* offset : 0x302c0 */
		union aw_ucie_rx0_reg_rxndechk_rdreg1 rx0_reg_rxndechk_rdreg1; /* offset : 0x302c4 */
		union aw_ucie_rx0_reg_rxndechk_rdreg2 rx0_reg_rxndechk_rdreg2; /* offset : 0x302c8 */
		union aw_ucie_rx0_reg_rxndechk_rdreg3 rx0_reg_rxndechk_rdreg3; /* offset : 0x302cc */
		union aw_ucie_rx0_reg_rxndechk_rdreg4 rx0_reg_rxndechk_rdreg4; /* offset : 0x302d0 */
		union aw_ucie_rx0_reg_rxndechk_reg1 rx0_reg_rxndechk_reg1; /* offset : 0x302d4 */
		union aw_ucie_rx0_reg_rxndechk_reg2 rx0_reg_rxndechk_reg2; /* offset : 0x302d8 */
		union aw_ucie_rx0_reg_rxndechk_reg3 rx0_reg_rxndechk_reg3; /* offset : 0x302dc */
		union aw_ucie_rx0_reg_rxndesync_fg_reg1 rx0_reg_rxndesync_fg_reg1; /* offset : 0x302e0 */
		union aw_ucie_rx0_reg_rxndesync_fg_reg2 rx0_reg_rxndesync_fg_reg2; /* offset : 0x302e4 */
		union aw_ucie_rx0_reg_rxndesync_rdreg rx0_reg_rxndesync_rdreg; /* offset : 0x302e8 */
		union aw_ucie_rx0_reg_rxndesync_reg1 rx0_reg_rxndesync_reg1; /* offset : 0x302ec */
		union aw_ucie_rx0_reg_rxndesync_reg2 rx0_reg_rxndesync_reg2; /* offset : 0x302f0 */
		union aw_ucie_rx0_reg_rxretpi_rdreg rx0_reg_rxretpi_rdreg; /* offset : 0x302f4 */
		union aw_ucie_rx0_reg_rxretpi_reg1 rx0_reg_rxretpi_reg1; /* offset : 0x302f8 */
		union aw_ucie_rx0_reg_rxretpi_reg2 rx0_reg_rxretpi_reg2; /* offset : 0x302fc */
		union aw_ucie_rx0_reg_rxretpi_reg3 rx0_reg_rxretpi_reg3; /* offset : 0x30300 */
		union aw_ucie_rx0_reg_rxretpi_reg4 rx0_reg_rxretpi_reg4; /* offset : 0x30304 */
		union aw_ucie_rx0_reg_rxrst_reg1 rx0_reg_rxrst_reg1; /* offset : 0x30308 */
		union aw_ucie_rx0_reg_rxsip_clr rx0_reg_rxsip_clr; /* offset : 0x3030c */
		union aw_ucie_rx0_reg_rxsoc_rdreg rx0_reg_rxsoc_rdreg; /* offset : 0x30310 */
		union aw_ucie_rx0_reg_rxsoc_reg1 rx0_reg_rxsoc_reg1; /* offset : 0x30314 */
		union aw_ucie_rx0_reg_rxtimer1_rdreg rx0_reg_rxtimer1_rdreg; /* offset : 0x30318 */
		union aw_ucie_rx0_reg_rxtimer1_reg1 rx0_reg_rxtimer1_reg1; /* offset : 0x3031c */
		union aw_ucie_rx0_reg_rxtimer1_reg2 rx0_reg_rxtimer1_reg2; /* offset : 0x30320 */
		union aw_ucie_rx0_reg_rxtimer2_rdreg rx0_reg_rxtimer2_rdreg; /* offset : 0x30324 */
		union aw_ucie_rx0_reg_rxtimer2_reg1 rx0_reg_rxtimer2_reg1; /* offset : 0x30328 */
		union aw_ucie_rx0_reg_rxtimer2_reg2 rx0_reg_rxtimer2_reg2; /* offset : 0x3032c */
		union aw_ucie_rx0_reg_rxclkchk_rdreg2 rx0_reg_rxclkchk_rdreg2; /* offset : 0x30330 */
		union aw_ucie_rx0_reg_rxclkchk_config1 rx0_reg_rxclkchk_config1; /* offset : 0x30334 */
		union aw_ucie_rx0_reg_rxdatchk_int1 rx0_reg_rxdatchk_int1; /* offset : 0x30338 */
		union aw_ucie_rx0_reg_rxdatchk_int1_mask rx0_reg_rxdatchk_int1_mask; /* offset : 0x3033c */
		union aw_ucie_rx0_reg_rxdatchk_int2 rx0_reg_rxdatchk_int2; /* offset : 0x30340 */
		union aw_ucie_rx0_reg_rxdatchk_int2_mask rx0_reg_rxdatchk_int2_mask; /* offset : 0x30344 */
		union aw_ucie_rx0_reg_rxclkchk_rdreg3 rx0_reg_rxclkchk_rdreg3; /* offset : 0x30348 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg13 rx0_reg_rxdatchk_rdreg13; /* offset : 0x3034c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg14 rx0_reg_rxdatchk_rdreg14; /* offset : 0x30350 */
		union aw_ucie_rx0_reg_rxdatchk_reg14 rx0_reg_rxdatchk_reg14; /* offset : 0x30354 */
		uint32_t reserved_32[298];
		union aw_ucie_tx0_reg_tx_csr_ctrl tx0_reg_tx_csr_ctrl; /* offset : 0x30800 */
		union aw_ucie_tx0_reg_tx_ctrl tx0_reg_tx_ctrl; /* offset : 0x30804 */
		union aw_ucie_tx0_reg_tx_ctrl_rdreg tx0_reg_tx_ctrl_rdreg; /* offset : 0x30808 */
		union aw_ucie_tx0_reg_txcalen tx0_reg_txcalen; /* offset : 0x3080c */
		union aw_ucie_tx0_reg_txcmn_reg1 tx0_reg_txcmn_reg1; /* offset : 0x30810 */
		union aw_ucie_tx0_reg_txcmn_reg2 tx0_reg_txcmn_reg2; /* offset : 0x30814 */
		union aw_ucie_tx0_reg_txdatapath_reg0 tx0_reg_txdatapath_reg0; /* offset : 0x30818 */
		union aw_ucie_tx0_reg_txdatapath_reg1 tx0_reg_txdatapath_reg1; /* offset : 0x3081c */
		union aw_ucie_tx0_reg_txdatapath_reg2 tx0_reg_txdatapath_reg2; /* offset : 0x30820 */
		union aw_ucie_tx0_reg_txdatapath_reg3 tx0_reg_txdatapath_reg3; /* offset : 0x30824 */
		union aw_ucie_tx0_reg_txdatapath_reg4 tx0_reg_txdatapath_reg4; /* offset : 0x30828 */
		union aw_ucie_tx0_reg_txdatapath_reg5 tx0_reg_txdatapath_reg5; /* offset : 0x3082c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg0 tx0_reg_txdatgen_perlaneid_reg0; /* offset : 0x30830 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg1 tx0_reg_txdatgen_perlaneid_reg1; /* offset : 0x30834 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg10 tx0_reg_txdatgen_perlaneid_reg10; /* offset : 0x30838 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg11 tx0_reg_txdatgen_perlaneid_reg11; /* offset : 0x3083c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg12 tx0_reg_txdatgen_perlaneid_reg12; /* offset : 0x30840 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg13 tx0_reg_txdatgen_perlaneid_reg13; /* offset : 0x30844 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg14 tx0_reg_txdatgen_perlaneid_reg14; /* offset : 0x30848 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg15 tx0_reg_txdatgen_perlaneid_reg15; /* offset : 0x3084c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg16 tx0_reg_txdatgen_perlaneid_reg16; /* offset : 0x30850 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg2 tx0_reg_txdatgen_perlaneid_reg2; /* offset : 0x30854 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg3 tx0_reg_txdatgen_perlaneid_reg3; /* offset : 0x30858 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg4 tx0_reg_txdatgen_perlaneid_reg4; /* offset : 0x3085c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg5 tx0_reg_txdatgen_perlaneid_reg5; /* offset : 0x30860 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg6 tx0_reg_txdatgen_perlaneid_reg6; /* offset : 0x30864 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg7 tx0_reg_txdatgen_perlaneid_reg7; /* offset : 0x30868 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg8 tx0_reg_txdatgen_perlaneid_reg8; /* offset : 0x3086c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg9 tx0_reg_txdatgen_perlaneid_reg9; /* offset : 0x30870 */
		union aw_ucie_tx0_reg_txdatgen_rdreg tx0_reg_txdatgen_rdreg; /* offset : 0x30874 */
		union aw_ucie_tx0_reg_txdatgen_reg1 tx0_reg_txdatgen_reg1; /* offset : 0x30878 */
		union aw_ucie_tx0_reg_txdatgen_reg10 tx0_reg_txdatgen_reg10; /* offset : 0x3087c */
		union aw_ucie_tx0_reg_txdatgen_reg11 tx0_reg_txdatgen_reg11; /* offset : 0x30880 */
		union aw_ucie_tx0_reg_txdatgen_reg12 tx0_reg_txdatgen_reg12; /* offset : 0x30884 */
		union aw_ucie_tx0_reg_txdatgen_reg13 tx0_reg_txdatgen_reg13; /* offset : 0x30888 */
		union aw_ucie_tx0_reg_txdatgen_reg14 tx0_reg_txdatgen_reg14; /* offset : 0x3088c */
		union aw_ucie_tx0_reg_txdatgen_reg15 tx0_reg_txdatgen_reg15; /* offset : 0x30890 */
		union aw_ucie_tx0_reg_txdatgen_reg16 tx0_reg_txdatgen_reg16; /* offset : 0x30894 */
		union aw_ucie_tx0_reg_txdatgen_reg17 tx0_reg_txdatgen_reg17; /* offset : 0x30898 */
		union aw_ucie_tx0_reg_txdatgen_reg18 tx0_reg_txdatgen_reg18; /* offset : 0x3089c */
		union aw_ucie_tx0_reg_txdatgen_reg19 tx0_reg_txdatgen_reg19; /* offset : 0x308a0 */
		union aw_ucie_tx0_reg_txdatgen_reg2 tx0_reg_txdatgen_reg2; /* offset : 0x308a4 */
		union aw_ucie_tx0_reg_txdatgen_reg20 tx0_reg_txdatgen_reg20; /* offset : 0x308a8 */
		union aw_ucie_tx0_reg_txdatgen_reg21 tx0_reg_txdatgen_reg21; /* offset : 0x308ac */
		union aw_ucie_tx0_reg_txdatgen_reg3 tx0_reg_txdatgen_reg3; /* offset : 0x308b0 */
		union aw_ucie_tx0_reg_txdatgen_reg4 tx0_reg_txdatgen_reg4; /* offset : 0x308b4 */
		union aw_ucie_tx0_reg_txdatgen_reg5 tx0_reg_txdatgen_reg5; /* offset : 0x308b8 */
		union aw_ucie_tx0_reg_txdatgen_reg6 tx0_reg_txdatgen_reg6; /* offset : 0x308bc */
		union aw_ucie_tx0_reg_txdatgen_reg7 tx0_reg_txdatgen_reg7; /* offset : 0x308c0 */
		union aw_ucie_tx0_reg_txdatgen_reg8 tx0_reg_txdatgen_reg8; /* offset : 0x308c4 */
		union aw_ucie_tx0_reg_txdatgen_reg9 tx0_reg_txdatgen_reg9; /* offset : 0x308c8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg0 tx0_reg_txdatgen_seed_udp_reg0; /* offset : 0x308cc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg1 tx0_reg_txdatgen_seed_udp_reg1; /* offset : 0x308d0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg10 tx0_reg_txdatgen_seed_udp_reg10; /* offset : 0x308d4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg11 tx0_reg_txdatgen_seed_udp_reg11; /* offset : 0x308d8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg12 tx0_reg_txdatgen_seed_udp_reg12; /* offset : 0x308dc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg13 tx0_reg_txdatgen_seed_udp_reg13; /* offset : 0x308e0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg14 tx0_reg_txdatgen_seed_udp_reg14; /* offset : 0x308e4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg15 tx0_reg_txdatgen_seed_udp_reg15; /* offset : 0x308e8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg16 tx0_reg_txdatgen_seed_udp_reg16; /* offset : 0x308ec */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg17 tx0_reg_txdatgen_seed_udp_reg17; /* offset : 0x308f0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg18 tx0_reg_txdatgen_seed_udp_reg18; /* offset : 0x308f4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg19 tx0_reg_txdatgen_seed_udp_reg19; /* offset : 0x308f8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg2 tx0_reg_txdatgen_seed_udp_reg2; /* offset : 0x308fc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg20 tx0_reg_txdatgen_seed_udp_reg20; /* offset : 0x30900 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg21 tx0_reg_txdatgen_seed_udp_reg21; /* offset : 0x30904 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg22 tx0_reg_txdatgen_seed_udp_reg22; /* offset : 0x30908 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg23 tx0_reg_txdatgen_seed_udp_reg23; /* offset : 0x3090c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg24 tx0_reg_txdatgen_seed_udp_reg24; /* offset : 0x30910 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg25 tx0_reg_txdatgen_seed_udp_reg25; /* offset : 0x30914 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg26 tx0_reg_txdatgen_seed_udp_reg26; /* offset : 0x30918 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg27 tx0_reg_txdatgen_seed_udp_reg27; /* offset : 0x3091c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg28 tx0_reg_txdatgen_seed_udp_reg28; /* offset : 0x30920 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg29 tx0_reg_txdatgen_seed_udp_reg29; /* offset : 0x30924 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg3 tx0_reg_txdatgen_seed_udp_reg3; /* offset : 0x30928 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg30 tx0_reg_txdatgen_seed_udp_reg30; /* offset : 0x3092c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg31 tx0_reg_txdatgen_seed_udp_reg31; /* offset : 0x30930 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg32 tx0_reg_txdatgen_seed_udp_reg32; /* offset : 0x30934 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg33 tx0_reg_txdatgen_seed_udp_reg33; /* offset : 0x30938 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg34 tx0_reg_txdatgen_seed_udp_reg34; /* offset : 0x3093c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg35 tx0_reg_txdatgen_seed_udp_reg35; /* offset : 0x30940 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg36 tx0_reg_txdatgen_seed_udp_reg36; /* offset : 0x30944 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg37 tx0_reg_txdatgen_seed_udp_reg37; /* offset : 0x30948 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg38 tx0_reg_txdatgen_seed_udp_reg38; /* offset : 0x3094c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg39 tx0_reg_txdatgen_seed_udp_reg39; /* offset : 0x30950 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg4 tx0_reg_txdatgen_seed_udp_reg4; /* offset : 0x30954 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg40 tx0_reg_txdatgen_seed_udp_reg40; /* offset : 0x30958 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg41 tx0_reg_txdatgen_seed_udp_reg41; /* offset : 0x3095c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg42 tx0_reg_txdatgen_seed_udp_reg42; /* offset : 0x30960 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg43 tx0_reg_txdatgen_seed_udp_reg43; /* offset : 0x30964 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg44 tx0_reg_txdatgen_seed_udp_reg44; /* offset : 0x30968 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg45 tx0_reg_txdatgen_seed_udp_reg45; /* offset : 0x3096c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg46 tx0_reg_txdatgen_seed_udp_reg46; /* offset : 0x30970 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg47 tx0_reg_txdatgen_seed_udp_reg47; /* offset : 0x30974 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg48 tx0_reg_txdatgen_seed_udp_reg48; /* offset : 0x30978 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg49 tx0_reg_txdatgen_seed_udp_reg49; /* offset : 0x3097c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg5 tx0_reg_txdatgen_seed_udp_reg5; /* offset : 0x30980 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg50 tx0_reg_txdatgen_seed_udp_reg50; /* offset : 0x30984 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg51 tx0_reg_txdatgen_seed_udp_reg51; /* offset : 0x30988 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg52 tx0_reg_txdatgen_seed_udp_reg52; /* offset : 0x3098c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg53 tx0_reg_txdatgen_seed_udp_reg53; /* offset : 0x30990 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg54 tx0_reg_txdatgen_seed_udp_reg54; /* offset : 0x30994 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg55 tx0_reg_txdatgen_seed_udp_reg55; /* offset : 0x30998 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg56 tx0_reg_txdatgen_seed_udp_reg56; /* offset : 0x3099c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg57 tx0_reg_txdatgen_seed_udp_reg57; /* offset : 0x309a0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg58 tx0_reg_txdatgen_seed_udp_reg58; /* offset : 0x309a4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg59 tx0_reg_txdatgen_seed_udp_reg59; /* offset : 0x309a8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg6 tx0_reg_txdatgen_seed_udp_reg6; /* offset : 0x309ac */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg60 tx0_reg_txdatgen_seed_udp_reg60; /* offset : 0x309b0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg61 tx0_reg_txdatgen_seed_udp_reg61; /* offset : 0x309b4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg62 tx0_reg_txdatgen_seed_udp_reg62; /* offset : 0x309b8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg63 tx0_reg_txdatgen_seed_udp_reg63; /* offset : 0x309bc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg64 tx0_reg_txdatgen_seed_udp_reg64; /* offset : 0x309c0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg65 tx0_reg_txdatgen_seed_udp_reg65; /* offset : 0x309c4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg66 tx0_reg_txdatgen_seed_udp_reg66; /* offset : 0x309c8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg67 tx0_reg_txdatgen_seed_udp_reg67; /* offset : 0x309cc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg68 tx0_reg_txdatgen_seed_udp_reg68; /* offset : 0x309d0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg69 tx0_reg_txdatgen_seed_udp_reg69; /* offset : 0x309d4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg7 tx0_reg_txdatgen_seed_udp_reg7; /* offset : 0x309d8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg70 tx0_reg_txdatgen_seed_udp_reg70; /* offset : 0x309dc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg71 tx0_reg_txdatgen_seed_udp_reg71; /* offset : 0x309e0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg72 tx0_reg_txdatgen_seed_udp_reg72; /* offset : 0x309e4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg73 tx0_reg_txdatgen_seed_udp_reg73; /* offset : 0x309e8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg8 tx0_reg_txdatgen_seed_udp_reg8; /* offset : 0x309ec */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg9 tx0_reg_txdatgen_seed_udp_reg9; /* offset : 0x309f0 */
		union aw_ucie_tx0_reg_txdcc_bg_reg1 tx0_reg_txdcc_bg_reg1; /* offset : 0x309f4 */
		union aw_ucie_tx0_reg_txdcc_fg_reg1 tx0_reg_txdcc_fg_reg1; /* offset : 0x309f8 */
		union aw_ucie_tx0_reg_txdcc_fg_reg2 tx0_reg_txdcc_fg_reg2; /* offset : 0x309fc */
		union aw_ucie_tx0_reg_txdcc_rdreg tx0_reg_txdcc_rdreg; /* offset : 0x30a00 */
		union aw_ucie_tx0_reg_txdcc_reg1 tx0_reg_txdcc_reg1; /* offset : 0x30a04 */
		union aw_ucie_tx0_reg_txdcc_reg2 tx0_reg_txdcc_reg2; /* offset : 0x30a08 */
		union aw_ucie_tx0_reg_txhip_clr tx0_reg_txhip_clr; /* offset : 0x30a0c */
		union aw_ucie_tx0_reg_txhip_dccack_rdreg tx0_reg_txhip_dccack_rdreg; /* offset : 0x30a10 */
		union aw_ucie_tx0_reg_txhip_dccctrl tx0_reg_txhip_dccctrl; /* offset : 0x30a14 */
		union aw_ucie_tx0_reg_txhip_dccreq tx0_reg_txhip_dccreq; /* offset : 0x30a18 */
		union aw_ucie_tx0_reg_txhip_dccval tx0_reg_txhip_dccval; /* offset : 0x30a1c */
		union aw_ucie_tx0_reg_txhip_dccval_rdreg tx0_reg_txhip_dccval_rdreg; /* offset : 0x30a20 */
		union aw_ucie_tx0_reg_txhip_piack_rdreg tx0_reg_txhip_piack_rdreg; /* offset : 0x30a24 */
		union aw_ucie_tx0_reg_txhip_pictrl tx0_reg_txhip_pictrl; /* offset : 0x30a28 */
		union aw_ucie_tx0_reg_txhip_pireq tx0_reg_txhip_pireq; /* offset : 0x30a2c */
		union aw_ucie_tx0_reg_txhip_pival tx0_reg_txhip_pival; /* offset : 0x30a30 */
		union aw_ucie_tx0_reg_txhip_pival_rdreg tx0_reg_txhip_pival_rdreg; /* offset : 0x30a34 */
		union aw_ucie_tx0_reg_txhip_rdreg1 tx0_reg_txhip_rdreg1; /* offset : 0x30a38 */
		union aw_ucie_tx0_reg_txhipcmn_reg1 tx0_reg_txhipcmn_reg1; /* offset : 0x30a3c */
		union aw_ucie_tx0_reg_txhipcmnio_reg1 tx0_reg_txhipcmnio_reg1; /* offset : 0x30a40 */
		union aw_ucie_tx0_reg_txhipcmnio_reg2 tx0_reg_txhipcmnio_reg2; /* offset : 0x30a44 */
		union aw_ucie_tx0_reg_txhipcmnio_reg3 tx0_reg_txhipcmnio_reg3; /* offset : 0x30a48 */
		union aw_ucie_tx0_reg_txhipctrl_reg1 tx0_reg_txhipctrl_reg1; /* offset : 0x30a4c */
		union aw_ucie_tx0_reg_txhipio tx0_reg_txhipio; /* offset : 0x30a50 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg1 tx0_reg_txhipiosync_rdreg1; /* offset : 0x30a54 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg2 tx0_reg_txhipiosync_rdreg2; /* offset : 0x30a58 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg3 tx0_reg_txhipiosync_rdreg3; /* offset : 0x30a5c */
		union aw_ucie_tx0_reg_txhipload_reg1 tx0_reg_txhipload_reg1; /* offset : 0x30a60 */
		union aw_ucie_tx0_reg_txhipload_reg2 tx0_reg_txhipload_reg2; /* offset : 0x30a64 */
		union aw_ucie_tx0_reg_txhipload_reg3 tx0_reg_txhipload_reg3; /* offset : 0x30a68 */
		union aw_ucie_tx0_reg_txhipspare_rdreg1 tx0_reg_txhipspare_rdreg1; /* offset : 0x30a6c */
		union aw_ucie_tx0_reg_txhipspare_reg1 tx0_reg_txhipspare_reg1; /* offset : 0x30a70 */
		union aw_ucie_tx0_reg_txhipspare_reg2 tx0_reg_txhipspare_reg2; /* offset : 0x30a74 */
		union aw_ucie_tx0_reg_txioctrl_reg1 tx0_reg_txioctrl_reg1; /* offset : 0x30a78 */
		union aw_ucie_tx0_reg_txioctrl_reg10 tx0_reg_txioctrl_reg10; /* offset : 0x30a7c */
		union aw_ucie_tx0_reg_txioctrl_reg11 tx0_reg_txioctrl_reg11; /* offset : 0x30a80 */
		union aw_ucie_tx0_reg_txioctrl_reg12 tx0_reg_txioctrl_reg12; /* offset : 0x30a84 */
		union aw_ucie_tx0_reg_txioctrl_reg13 tx0_reg_txioctrl_reg13; /* offset : 0x30a88 */
		union aw_ucie_tx0_reg_txioctrl_reg14 tx0_reg_txioctrl_reg14; /* offset : 0x30a8c */
		union aw_ucie_tx0_reg_txioctrl_reg15 tx0_reg_txioctrl_reg15; /* offset : 0x30a90 */
		union aw_ucie_tx0_reg_txioctrl_reg16 tx0_reg_txioctrl_reg16; /* offset : 0x30a94 */
		union aw_ucie_tx0_reg_txioctrl_reg17 tx0_reg_txioctrl_reg17; /* offset : 0x30a98 */
		union aw_ucie_tx0_reg_txioctrl_reg18 tx0_reg_txioctrl_reg18; /* offset : 0x30a9c */
		union aw_ucie_tx0_reg_txioctrl_reg2 tx0_reg_txioctrl_reg2; /* offset : 0x30aa0 */
		union aw_ucie_tx0_reg_txioctrl_reg3 tx0_reg_txioctrl_reg3; /* offset : 0x30aa4 */
		union aw_ucie_tx0_reg_txioctrl_reg4 tx0_reg_txioctrl_reg4; /* offset : 0x30aa8 */
		union aw_ucie_tx0_reg_txioctrl_reg5 tx0_reg_txioctrl_reg5; /* offset : 0x30aac */
		union aw_ucie_tx0_reg_txioctrl_reg6 tx0_reg_txioctrl_reg6; /* offset : 0x30ab0 */
		union aw_ucie_tx0_reg_txioctrl_reg7 tx0_reg_txioctrl_reg7; /* offset : 0x30ab4 */
		union aw_ucie_tx0_reg_txioctrl_reg8 tx0_reg_txioctrl_reg8; /* offset : 0x30ab8 */
		union aw_ucie_tx0_reg_txioctrl_reg9 tx0_reg_txioctrl_reg9; /* offset : 0x30abc */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg1 tx0_reg_txioen_afe_ovr_reg1; /* offset : 0x30ac0 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg2 tx0_reg_txioen_afe_ovr_reg2; /* offset : 0x30ac4 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg3 tx0_reg_txioen_afe_ovr_reg3; /* offset : 0x30ac8 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg4 tx0_reg_txioen_afe_ovr_reg4; /* offset : 0x30acc */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg1 tx0_reg_txioen_data_ovr_reg1; /* offset : 0x30ad0 */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg2 tx0_reg_txioen_data_ovr_reg2; /* offset : 0x30ad4 */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg3 tx0_reg_txioen_data_ovr_reg3; /* offset : 0x30ad8 */
		union aw_ucie_tx0_reg_txioen_ovr_reg1 tx0_reg_txioen_ovr_reg1; /* offset : 0x30adc */
		union aw_ucie_tx0_reg_txioen_ovr_reg2 tx0_reg_txioen_ovr_reg2; /* offset : 0x30ae0 */
		union aw_ucie_tx0_reg_txioen_ovr_reg3 tx0_reg_txioen_ovr_reg3; /* offset : 0x30ae4 */
		union aw_ucie_tx0_reg_txioen_ovr_reg4 tx0_reg_txioen_ovr_reg4; /* offset : 0x30ae8 */
		union aw_ucie_tx0_reg_txqcc_rdreg tx0_reg_txqcc_rdreg; /* offset : 0x30aec */
		union aw_ucie_tx0_reg_txqcc_reg1 tx0_reg_txqcc_reg1; /* offset : 0x30af0 */
		union aw_ucie_tx0_reg_txqcc_reg2 tx0_reg_txqcc_reg2; /* offset : 0x30af4 */
		union aw_ucie_tx0_reg_txqcc_reg3 tx0_reg_txqcc_reg3; /* offset : 0x30af8 */
		union aw_ucie_tx0_reg_txqcc_reg4 tx0_reg_txqcc_reg4; /* offset : 0x30afc */
		union aw_ucie_tx0_reg_txretpi_rdreg tx0_reg_txretpi_rdreg; /* offset : 0x30b00 */
		union aw_ucie_tx0_reg_txretpi_reg1 tx0_reg_txretpi_reg1; /* offset : 0x30b04 */
		union aw_ucie_tx0_reg_txretpi_reg2 tx0_reg_txretpi_reg2; /* offset : 0x30b08 */
		union aw_ucie_tx0_reg_txretpi_reg3 tx0_reg_txretpi_reg3; /* offset : 0x30b0c */
		union aw_ucie_tx0_reg_txretpi_reg4 tx0_reg_txretpi_reg4; /* offset : 0x30b10 */
		union aw_ucie_tx0_reg_txrst_reg1 tx0_reg_txrst_reg1; /* offset : 0x30b14 */
		union aw_ucie_tx0_reg_txsip_clr tx0_reg_txsip_clr; /* offset : 0x30b18 */
		union aw_ucie_tx0_reg_txsoc_rdreg tx0_reg_txsoc_rdreg; /* offset : 0x30b1c */
		union aw_ucie_tx0_reg_txsoc_reg1 tx0_reg_txsoc_reg1; /* offset : 0x30b20 */
		union aw_ucie_tx0_reg_txsync_bg_reg1 tx0_reg_txsync_bg_reg1; /* offset : 0x30b24 */
		union aw_ucie_tx0_reg_txsync_fg_reg1 tx0_reg_txsync_fg_reg1; /* offset : 0x30b28 */
		union aw_ucie_tx0_reg_txsync_fg_reg2 tx0_reg_txsync_fg_reg2; /* offset : 0x30b2c */
		union aw_ucie_tx0_reg_txsync_rdreg tx0_reg_txsync_rdreg; /* offset : 0x30b30 */
		union aw_ucie_tx0_reg_txsync_reg1 tx0_reg_txsync_reg1; /* offset : 0x30b34 */
		union aw_ucie_tx0_reg_txsync_reg2 tx0_reg_txsync_reg2; /* offset : 0x30b38 */
		union aw_ucie_tx0_reg_txtimer1_rdreg tx0_reg_txtimer1_rdreg; /* offset : 0x30b3c */
		union aw_ucie_tx0_reg_txtimer1_reg1 tx0_reg_txtimer1_reg1; /* offset : 0x30b40 */
		union aw_ucie_tx0_reg_txtimer1_reg2 tx0_reg_txtimer1_reg2; /* offset : 0x30b44 */
		union aw_ucie_tx0_reg_txtimer2_rdreg tx0_reg_txtimer2_rdreg; /* offset : 0x30b48 */
		union aw_ucie_tx0_reg_txtimer2_reg1 tx0_reg_txtimer2_reg1; /* offset : 0x30b4c */
		union aw_ucie_tx0_reg_txtimer2_reg2 tx0_reg_txtimer2_reg2; /* offset : 0x30b50 */
		union aw_ucie_tx0_reg_txdatgen_int1 tx0_reg_txdatgen_int1; /* offset : 0x30b54 */
		union aw_ucie_tx0_reg_txdatgen_int1_mask tx0_reg_txdatgen_int1_mask; /* offset : 0x30b58 */
		union aw_ucie_tx0_reg_txdatgen_int2 tx0_reg_txdatgen_int2; /* offset : 0x30b5c */
		union aw_ucie_tx0_reg_txdatgen_int2_mask tx0_reg_txdatgen_int2_mask; /* offset : 0x30b60 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg5 tx0_reg_txioen_afe_ovr_reg5; /* offset : 0x30b64 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg6 tx0_reg_txioen_afe_ovr_reg6; /* offset : 0x30b68 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg7 tx0_reg_txioen_afe_ovr_reg7; /* offset : 0x30b6c */
		uint32_t reserved_33[292];
		union aw_ucie_sb0_reg_reg_sb_afe_cfg1 sb0_reg_reg_sb_afe_cfg1; /* offset : 0x31000 */
		union aw_ucie_sb0_reg_reg_sb_afe_cfg2 sb0_reg_reg_sb_afe_cfg2; /* offset : 0x31004 */
		union aw_ucie_sb0_reg_reg_sb_cmn_reset_cfg sb0_reg_reg_sb_cmn_reset_cfg; /* offset : 0x31008 */
		union aw_ucie_sb0_reg_rst_reg1 sb0_reg_rst_reg1; /* offset : 0x3100c */
		union aw_ucie_sb0_reg_rxsb_afifo_cfg sb0_reg_rxsb_afifo_cfg; /* offset : 0x31010 */
		union aw_ucie_sb0_reg_rxsb_cfg sb0_reg_rxsb_cfg; /* offset : 0x31014 */
		union aw_ucie_sb0_reg_sb_sfifo_int1_mask sb0_reg_sb_sfifo_int1_mask; /* offset : 0x31018 */
		union aw_ucie_sb0_reg_sb_sfifo_int1 sb0_reg_sb_sfifo_int1; /* offset : 0x3101c */
		uint32_t reserved_34;
		union aw_ucie_sb0_reg_rxsb_rdreg1 sb0_reg_rxsb_rdreg1; /* offset : 0x31024 */
		union aw_ucie_sb0_reg_rxsbacccom_cfg sb0_reg_rxsbacccom_cfg; /* offset : 0x31028 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg1 sb0_reg_rxsbacccom_rdreg1; /* offset : 0x3102c */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg2 sb0_reg_rxsbacccom_rdreg2; /* offset : 0x31030 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg3 sb0_reg_rxsbacccom_rdreg3; /* offset : 0x31034 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg4 sb0_reg_rxsbacccom_rdreg4; /* offset : 0x31038 */
		union aw_ucie_sb0_reg_rxsbaccreq_cfg sb0_reg_rxsbaccreq_cfg; /* offset : 0x3103c */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg1 sb0_reg_rxsbaccreq_rdreg1; /* offset : 0x31040 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg2 sb0_reg_rxsbaccreq_rdreg2; /* offset : 0x31044 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg3 sb0_reg_rxsbaccreq_rdreg3; /* offset : 0x31048 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg4 sb0_reg_rxsbaccreq_rdreg4; /* offset : 0x3104c */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg5 sb0_reg_rxsbaccreq_rdreg5; /* offset : 0x31050 */
		union aw_ucie_sb0_reg_rxsbmsg_cfg sb0_reg_rxsbmsg_cfg; /* offset : 0x31054 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg1 sb0_reg_rxsbmsg_rdreg1; /* offset : 0x31058 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg2 sb0_reg_rxsbmsg_rdreg2; /* offset : 0x3105c */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg3 sb0_reg_rxsbmsg_rdreg3; /* offset : 0x31060 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg4 sb0_reg_rxsbmsg_rdreg4; /* offset : 0x31064 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg5 sb0_reg_rxsbmsg_rdreg5; /* offset : 0x31068 */
		union aw_ucie_sb0_reg_rxsbvmsg_cfg sb0_reg_rxsbvmsg_cfg; /* offset : 0x3106c */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg1 sb0_reg_rxsbvmsg_rdreg1; /* offset : 0x31070 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg2 sb0_reg_rxsbvmsg_rdreg2; /* offset : 0x31074 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg3 sb0_reg_rxsbvmsg_rdreg3; /* offset : 0x31078 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg4 sb0_reg_rxsbvmsg_rdreg4; /* offset : 0x3107c */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg5 sb0_reg_rxsbvmsg_rdreg5; /* offset : 0x31080 */
		union aw_ucie_sb0_reg_sb_csr_ctrl sb0_reg_sb_csr_ctrl; /* offset : 0x31084 */
		union aw_ucie_sb0_reg_soc_reg1 sb0_reg_soc_reg1; /* offset : 0x31088 */
		union aw_ucie_sb0_reg_txsb_afifo_cfg sb0_reg_txsb_afifo_cfg; /* offset : 0x3108c */
		union aw_ucie_sb0_reg_txsb_cfg1 sb0_reg_txsb_cfg1; /* offset : 0x31090 */
		union aw_ucie_sb0_reg_txsb_cfg10 sb0_reg_txsb_cfg10; /* offset : 0x31094 */
		union aw_ucie_sb0_reg_txsb_cfg11 sb0_reg_txsb_cfg11; /* offset : 0x31098 */
		union aw_ucie_sb0_reg_txsb_cfg2 sb0_reg_txsb_cfg2; /* offset : 0x3109c */
		union aw_ucie_sb0_reg_txsb_cfg3 sb0_reg_txsb_cfg3; /* offset : 0x310a0 */
		union aw_ucie_sb0_reg_txsb_cfg4 sb0_reg_txsb_cfg4; /* offset : 0x310a4 */
		union aw_ucie_sb0_reg_txsb_cfg5 sb0_reg_txsb_cfg5; /* offset : 0x310a8 */
		union aw_ucie_sb0_reg_txsb_cfg6 sb0_reg_txsb_cfg6; /* offset : 0x310ac */
		union aw_ucie_sb0_reg_txsb_cfg7 sb0_reg_txsb_cfg7; /* offset : 0x310b0 */
		union aw_ucie_sb0_reg_txsb_cfg8 sb0_reg_txsb_cfg8; /* offset : 0x310b4 */
		union aw_ucie_sb0_reg_txsb_cfg9 sb0_reg_txsb_cfg9; /* offset : 0x310b8 */
		union aw_ucie_sb0_reg_txsb_stall_rdreg1 sb0_reg_txsb_stall_rdreg1; /* offset : 0x310bc */
		union aw_ucie_sb0_reg_sb_afifo_int1_mask sb0_reg_sb_afifo_int1_mask; /* offset : 0x310c0 */
		union aw_ucie_sb0_reg_sb_afifo_int1 sb0_reg_sb_afifo_int1; /* offset : 0x310c4 */
		union aw_ucie_sb0_reg_sb_sfifo_int2_mask sb0_reg_sb_sfifo_int2_mask; /* offset : 0x310c8 */
		union aw_ucie_sb0_reg_sb_sfifo_int2 sb0_reg_sb_sfifo_int2; /* offset : 0x310cc */
		union aw_ucie_sb0_reg_sb_afifo_int2_mask sb0_reg_sb_afifo_int2_mask; /* offset : 0x310d0 */
		union aw_ucie_sb0_reg_sb_afifo_int2 sb0_reg_sb_afifo_int2; /* offset : 0x310d4 */
		union aw_ucie_sb0_reg_sb_timeout_count_config1_reg sb0_reg_sb_timeout_count_config1_reg; /* offset : 0x310d8 */
		union aw_ucie_sb0_reg_sb_timeout_count_config2_reg sb0_reg_sb_timeout_count_config2_reg; /* offset : 0x310dc */
		union aw_ucie_sb0_reg_sb_rx_cntrl_config_reg sb0_reg_sb_rx_cntrl_config_reg; /* offset : 0x310e0 */
		uint32_t reserved_35[455];
		union aw_ucie_dfx0_reg_clk_ctrl dfx0_reg_clk_ctrl; /* offset : 0x31800 */
		union aw_ucie_dfx0_reg_dfx_csr_ctrl dfx0_reg_dfx_csr_ctrl; /* offset : 0x31804 */
		union aw_ucie_dfx0_reg_dfx_ctrl dfx0_reg_dfx_ctrl; /* offset : 0x31808 */
		union aw_ucie_dfx0_reg_dfx_stat_rdreg dfx0_reg_dfx_stat_rdreg; /* offset : 0x3180c */
		union aw_ucie_dfx0_reg_lane_mcu_boot_addr dfx0_reg_lane_mcu_boot_addr; /* offset : 0x31810 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump0 dfx0_reg_lane_mcu_crash_dump0; /* offset : 0x31814 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump1 dfx0_reg_lane_mcu_crash_dump1; /* offset : 0x31818 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump2 dfx0_reg_lane_mcu_crash_dump2; /* offset : 0x3181c */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump3 dfx0_reg_lane_mcu_crash_dump3; /* offset : 0x31820 */
		union aw_ucie_dfx0_reg_lane_mcu_ctrl dfx0_reg_lane_mcu_ctrl; /* offset : 0x31824 */
		union aw_ucie_dfx0_reg_lane_mcu_device_addr dfx0_reg_lane_mcu_device_addr; /* offset : 0x31828 */
		union aw_ucie_dfx0_reg_lane_mcu_dmem dfx0_reg_lane_mcu_dmem; /* offset : 0x3182c */
		union aw_ucie_dfx0_reg_lane_mcu_hart_id dfx0_reg_lane_mcu_hart_id; /* offset : 0x31830 */
		union aw_ucie_dfx0_reg_lane_mcu_irq dfx0_reg_lane_mcu_irq; /* offset : 0x31834 */
		union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl1 dfx0_reg_lane_mcu_irq_ctrl1; /* offset : 0x31838 */
		union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl2 dfx0_reg_lane_mcu_irq_ctrl2; /* offset : 0x3183c */
		union aw_ucie_dfx0_reg_lane_mcu_stats dfx0_reg_lane_mcu_stats; /* offset : 0x31840 */
		uint32_t reserved_36[495];
		union aw_ucie_rx1_reg_rx_csr_ctrl rx1_reg_rx_csr_ctrl; /* offset : 0x32000 */
		union aw_ucie_rx1_reg_rx_ctrl rx1_reg_rx_ctrl; /* offset : 0x32004 */
		union aw_ucie_rx1_reg_rx_ctrl_rdreg rx1_reg_rx_ctrl_rdreg; /* offset : 0x32008 */
		union aw_ucie_rx1_reg_rxcalen rx1_reg_rxcalen; /* offset : 0x3200c */
		union aw_ucie_rx1_reg_rxclkchk_rdreg rx1_reg_rxclkchk_rdreg; /* offset : 0x32010 */
		union aw_ucie_rx1_reg_rxcmn_reg1 rx1_reg_rxcmn_reg1; /* offset : 0x32014 */
		union aw_ucie_rx1_reg_rxcmn_reg2 rx1_reg_rxcmn_reg2; /* offset : 0x32018 */
		union aw_ucie_rx1_reg_rxdatapath_reg0 rx1_reg_rxdatapath_reg0; /* offset : 0x3201c */
		union aw_ucie_rx1_reg_rxdatapath_reg1 rx1_reg_rxdatapath_reg1; /* offset : 0x32020 */
		union aw_ucie_rx1_reg_rxdatapath_reg2 rx1_reg_rxdatapath_reg2; /* offset : 0x32024 */
		union aw_ucie_rx1_reg_rxdatapath_reg3 rx1_reg_rxdatapath_reg3; /* offset : 0x32028 */
		union aw_ucie_rx1_reg_rxdatapath_reg4 rx1_reg_rxdatapath_reg4; /* offset : 0x3202c */
		union aw_ucie_rx1_reg_rxdatapath_reg5 rx1_reg_rxdatapath_reg5; /* offset : 0x32030 */
		union aw_ucie_rx1_reg_rxdatcap_rdreg1 rx1_reg_rxdatcap_rdreg1; /* offset : 0x32034 */
		union aw_ucie_rx1_reg_rxdatcap_rdreg2 rx1_reg_rxdatcap_rdreg2; /* offset : 0x32038 */
		union aw_ucie_rx1_reg_rxdatcap_reg1 rx1_reg_rxdatcap_reg1; /* offset : 0x3203c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg0 rx1_reg_rxdatchk_perlaneid_reg0; /* offset : 0x32040 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg1 rx1_reg_rxdatchk_perlaneid_reg1; /* offset : 0x32044 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg10 rx1_reg_rxdatchk_perlaneid_reg10; /* offset : 0x32048 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg11 rx1_reg_rxdatchk_perlaneid_reg11; /* offset : 0x3204c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg12 rx1_reg_rxdatchk_perlaneid_reg12; /* offset : 0x32050 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg13 rx1_reg_rxdatchk_perlaneid_reg13; /* offset : 0x32054 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg14 rx1_reg_rxdatchk_perlaneid_reg14; /* offset : 0x32058 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg15 rx1_reg_rxdatchk_perlaneid_reg15; /* offset : 0x3205c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg16 rx1_reg_rxdatchk_perlaneid_reg16; /* offset : 0x32060 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg2 rx1_reg_rxdatchk_perlaneid_reg2; /* offset : 0x32064 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg3 rx1_reg_rxdatchk_perlaneid_reg3; /* offset : 0x32068 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg4 rx1_reg_rxdatchk_perlaneid_reg4; /* offset : 0x3206c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg5 rx1_reg_rxdatchk_perlaneid_reg5; /* offset : 0x32070 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg6 rx1_reg_rxdatchk_perlaneid_reg6; /* offset : 0x32074 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg7 rx1_reg_rxdatchk_perlaneid_reg7; /* offset : 0x32078 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg8 rx1_reg_rxdatchk_perlaneid_reg8; /* offset : 0x3207c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg9 rx1_reg_rxdatchk_perlaneid_reg9; /* offset : 0x32080 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg1 rx1_reg_rxdatchk_rdreg1; /* offset : 0x32084 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg10 rx1_reg_rxdatchk_rdreg10; /* offset : 0x32088 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg11 rx1_reg_rxdatchk_rdreg11; /* offset : 0x3208c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg12 rx1_reg_rxdatchk_rdreg12; /* offset : 0x32090 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg2 rx1_reg_rxdatchk_rdreg2; /* offset : 0x32094 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg3 rx1_reg_rxdatchk_rdreg3; /* offset : 0x32098 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg4 rx1_reg_rxdatchk_rdreg4; /* offset : 0x3209c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg5 rx1_reg_rxdatchk_rdreg5; /* offset : 0x320a0 */
		union aw_ucie_rx1_reg_rxdatchk_reg1 rx1_reg_rxdatchk_reg1; /* offset : 0x320a4 */
		union aw_ucie_rx1_reg_rxdatchk_reg13 rx1_reg_rxdatchk_reg13; /* offset : 0x320a8 */
		union aw_ucie_rx1_reg_rxdatchk_reg2 rx1_reg_rxdatchk_reg2; /* offset : 0x320ac */
		union aw_ucie_rx1_reg_rxdatchk_reg3 rx1_reg_rxdatchk_reg3; /* offset : 0x320b0 */
		union aw_ucie_rx1_reg_rxdatchk_reg4 rx1_reg_rxdatchk_reg4; /* offset : 0x320b4 */
		union aw_ucie_rx1_reg_rxdatchk_reg5 rx1_reg_rxdatchk_reg5; /* offset : 0x320b8 */
		union aw_ucie_rx1_reg_rxdatchk_reg6 rx1_reg_rxdatchk_reg6; /* offset : 0x320bc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg0 rx1_reg_rxdatgen_seed_udp_reg0; /* offset : 0x320c0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg1 rx1_reg_rxdatgen_seed_udp_reg1; /* offset : 0x320c4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg10 rx1_reg_rxdatgen_seed_udp_reg10; /* offset : 0x320c8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg11 rx1_reg_rxdatgen_seed_udp_reg11; /* offset : 0x320cc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg12 rx1_reg_rxdatgen_seed_udp_reg12; /* offset : 0x320d0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg13 rx1_reg_rxdatgen_seed_udp_reg13; /* offset : 0x320d4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg14 rx1_reg_rxdatgen_seed_udp_reg14; /* offset : 0x320d8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg15 rx1_reg_rxdatgen_seed_udp_reg15; /* offset : 0x320dc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg16 rx1_reg_rxdatgen_seed_udp_reg16; /* offset : 0x320e0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg17 rx1_reg_rxdatgen_seed_udp_reg17; /* offset : 0x320e4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg18 rx1_reg_rxdatgen_seed_udp_reg18; /* offset : 0x320e8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg19 rx1_reg_rxdatgen_seed_udp_reg19; /* offset : 0x320ec */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg2 rx1_reg_rxdatgen_seed_udp_reg2; /* offset : 0x320f0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg20 rx1_reg_rxdatgen_seed_udp_reg20; /* offset : 0x320f4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg21 rx1_reg_rxdatgen_seed_udp_reg21; /* offset : 0x320f8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg22 rx1_reg_rxdatgen_seed_udp_reg22; /* offset : 0x320fc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg23 rx1_reg_rxdatgen_seed_udp_reg23; /* offset : 0x32100 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg24 rx1_reg_rxdatgen_seed_udp_reg24; /* offset : 0x32104 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg25 rx1_reg_rxdatgen_seed_udp_reg25; /* offset : 0x32108 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg26 rx1_reg_rxdatgen_seed_udp_reg26; /* offset : 0x3210c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg27 rx1_reg_rxdatgen_seed_udp_reg27; /* offset : 0x32110 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg28 rx1_reg_rxdatgen_seed_udp_reg28; /* offset : 0x32114 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg29 rx1_reg_rxdatgen_seed_udp_reg29; /* offset : 0x32118 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg3 rx1_reg_rxdatgen_seed_udp_reg3; /* offset : 0x3211c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg30 rx1_reg_rxdatgen_seed_udp_reg30; /* offset : 0x32120 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg31 rx1_reg_rxdatgen_seed_udp_reg31; /* offset : 0x32124 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg32 rx1_reg_rxdatgen_seed_udp_reg32; /* offset : 0x32128 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg33 rx1_reg_rxdatgen_seed_udp_reg33; /* offset : 0x3212c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg34 rx1_reg_rxdatgen_seed_udp_reg34; /* offset : 0x32130 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg35 rx1_reg_rxdatgen_seed_udp_reg35; /* offset : 0x32134 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg36 rx1_reg_rxdatgen_seed_udp_reg36; /* offset : 0x32138 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg37 rx1_reg_rxdatgen_seed_udp_reg37; /* offset : 0x3213c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg38 rx1_reg_rxdatgen_seed_udp_reg38; /* offset : 0x32140 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg39 rx1_reg_rxdatgen_seed_udp_reg39; /* offset : 0x32144 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg4 rx1_reg_rxdatgen_seed_udp_reg4; /* offset : 0x32148 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg40 rx1_reg_rxdatgen_seed_udp_reg40; /* offset : 0x3214c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg41 rx1_reg_rxdatgen_seed_udp_reg41; /* offset : 0x32150 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg42 rx1_reg_rxdatgen_seed_udp_reg42; /* offset : 0x32154 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg43 rx1_reg_rxdatgen_seed_udp_reg43; /* offset : 0x32158 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg44 rx1_reg_rxdatgen_seed_udp_reg44; /* offset : 0x3215c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg45 rx1_reg_rxdatgen_seed_udp_reg45; /* offset : 0x32160 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg46 rx1_reg_rxdatgen_seed_udp_reg46; /* offset : 0x32164 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg47 rx1_reg_rxdatgen_seed_udp_reg47; /* offset : 0x32168 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg48 rx1_reg_rxdatgen_seed_udp_reg48; /* offset : 0x3216c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg49 rx1_reg_rxdatgen_seed_udp_reg49; /* offset : 0x32170 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg5 rx1_reg_rxdatgen_seed_udp_reg5; /* offset : 0x32174 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg50 rx1_reg_rxdatgen_seed_udp_reg50; /* offset : 0x32178 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg51 rx1_reg_rxdatgen_seed_udp_reg51; /* offset : 0x3217c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg52 rx1_reg_rxdatgen_seed_udp_reg52; /* offset : 0x32180 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg53 rx1_reg_rxdatgen_seed_udp_reg53; /* offset : 0x32184 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg54 rx1_reg_rxdatgen_seed_udp_reg54; /* offset : 0x32188 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg55 rx1_reg_rxdatgen_seed_udp_reg55; /* offset : 0x3218c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg56 rx1_reg_rxdatgen_seed_udp_reg56; /* offset : 0x32190 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg57 rx1_reg_rxdatgen_seed_udp_reg57; /* offset : 0x32194 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg58 rx1_reg_rxdatgen_seed_udp_reg58; /* offset : 0x32198 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg59 rx1_reg_rxdatgen_seed_udp_reg59; /* offset : 0x3219c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg6 rx1_reg_rxdatgen_seed_udp_reg6; /* offset : 0x321a0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg60 rx1_reg_rxdatgen_seed_udp_reg60; /* offset : 0x321a4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg61 rx1_reg_rxdatgen_seed_udp_reg61; /* offset : 0x321a8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg62 rx1_reg_rxdatgen_seed_udp_reg62; /* offset : 0x321ac */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg63 rx1_reg_rxdatgen_seed_udp_reg63; /* offset : 0x321b0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg64 rx1_reg_rxdatgen_seed_udp_reg64; /* offset : 0x321b4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg65 rx1_reg_rxdatgen_seed_udp_reg65; /* offset : 0x321b8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg66 rx1_reg_rxdatgen_seed_udp_reg66; /* offset : 0x321bc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg67 rx1_reg_rxdatgen_seed_udp_reg67; /* offset : 0x321c0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg68 rx1_reg_rxdatgen_seed_udp_reg68; /* offset : 0x321c4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg69 rx1_reg_rxdatgen_seed_udp_reg69; /* offset : 0x321c8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg7 rx1_reg_rxdatgen_seed_udp_reg7; /* offset : 0x321cc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg70 rx1_reg_rxdatgen_seed_udp_reg70; /* offset : 0x321d0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg71 rx1_reg_rxdatgen_seed_udp_reg71; /* offset : 0x321d4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg72 rx1_reg_rxdatgen_seed_udp_reg72; /* offset : 0x321d8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg73 rx1_reg_rxdatgen_seed_udp_reg73; /* offset : 0x321dc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg8 rx1_reg_rxdatgen_seed_udp_reg8; /* offset : 0x321e0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg9 rx1_reg_rxdatgen_seed_udp_reg9; /* offset : 0x321e4 */
		union aw_ucie_rx1_reg_rxhip_clr rx1_reg_rxhip_clr; /* offset : 0x321e8 */
		union aw_ucie_rx1_reg_rxhip_piack_rdreg rx1_reg_rxhip_piack_rdreg; /* offset : 0x321ec */
		union aw_ucie_rx1_reg_rxhip_pictrl rx1_reg_rxhip_pictrl; /* offset : 0x321f0 */
		union aw_ucie_rx1_reg_rxhip_pireq rx1_reg_rxhip_pireq; /* offset : 0x321f4 */
		union aw_ucie_rx1_reg_rxhip_pival rx1_reg_rxhip_pival; /* offset : 0x321f8 */
		union aw_ucie_rx1_reg_rxhip_pival_rdreg rx1_reg_rxhip_pival_rdreg; /* offset : 0x321fc */
		union aw_ucie_rx1_reg_rxhip_rdreg1 rx1_reg_rxhip_rdreg1; /* offset : 0x32200 */
		union aw_ucie_rx1_reg_rxhipcmn_reg1 rx1_reg_rxhipcmn_reg1; /* offset : 0x32204 */
		union aw_ucie_rx1_reg_rxhipcmnio_reg1 rx1_reg_rxhipcmnio_reg1; /* offset : 0x32208 */
		union aw_ucie_rx1_reg_rxhipcmnio_reg2 rx1_reg_rxhipcmnio_reg2; /* offset : 0x3220c */
		union aw_ucie_rx1_reg_rxhipcmnio_reg3 rx1_reg_rxhipcmnio_reg3; /* offset : 0x32210 */
		union aw_ucie_rx1_reg_rxhipctrl_reg1 rx1_reg_rxhipctrl_reg1; /* offset : 0x32214 */
		union aw_ucie_rx1_reg_rxhipdqs_reg1 rx1_reg_rxhipdqs_reg1; /* offset : 0x32218 */
		union aw_ucie_rx1_reg_rxhipdqs_reg2 rx1_reg_rxhipdqs_reg2; /* offset : 0x3221c */
		union aw_ucie_rx1_reg_rxhipio_reg1 rx1_reg_rxhipio_reg1; /* offset : 0x32220 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg1 rx1_reg_rxhipiondesync_rdreg1; /* offset : 0x32224 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg2 rx1_reg_rxhipiondesync_rdreg2; /* offset : 0x32228 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg3 rx1_reg_rxhipiondesync_rdreg3; /* offset : 0x3222c */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg1 rx1_reg_rxhipiosampler_rdreg1; /* offset : 0x32230 */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg2 rx1_reg_rxhipiosampler_rdreg2; /* offset : 0x32234 */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg3 rx1_reg_rxhipiosampler_rdreg3; /* offset : 0x32238 */
		union aw_ucie_rx1_reg_rxhipload_reg1 rx1_reg_rxhipload_reg1; /* offset : 0x3223c */
		union aw_ucie_rx1_reg_rxhipload_reg10 rx1_reg_rxhipload_reg10; /* offset : 0x32240 */
		union aw_ucie_rx1_reg_rxhipload_reg11 rx1_reg_rxhipload_reg11; /* offset : 0x32244 */
		union aw_ucie_rx1_reg_rxhipload_reg12 rx1_reg_rxhipload_reg12; /* offset : 0x32248 */
		union aw_ucie_rx1_reg_rxhipload_reg13 rx1_reg_rxhipload_reg13; /* offset : 0x3224c */
		union aw_ucie_rx1_reg_rxhipload_reg14 rx1_reg_rxhipload_reg14; /* offset : 0x32250 */
		union aw_ucie_rx1_reg_rxhipload_reg15 rx1_reg_rxhipload_reg15; /* offset : 0x32254 */
		union aw_ucie_rx1_reg_rxhipload_reg2 rx1_reg_rxhipload_reg2; /* offset : 0x32258 */
		union aw_ucie_rx1_reg_rxhipload_reg3 rx1_reg_rxhipload_reg3; /* offset : 0x3225c */
		union aw_ucie_rx1_reg_rxhipload_reg4 rx1_reg_rxhipload_reg4; /* offset : 0x32260 */
		union aw_ucie_rx1_reg_rxhipload_reg5 rx1_reg_rxhipload_reg5; /* offset : 0x32264 */
		union aw_ucie_rx1_reg_rxhipload_reg6 rx1_reg_rxhipload_reg6; /* offset : 0x32268 */
		union aw_ucie_rx1_reg_rxhipload_reg7 rx1_reg_rxhipload_reg7; /* offset : 0x3226c */
		union aw_ucie_rx1_reg_rxhipload_reg8 rx1_reg_rxhipload_reg8; /* offset : 0x32270 */
		union aw_ucie_rx1_reg_rxhipload_reg9 rx1_reg_rxhipload_reg9; /* offset : 0x32274 */
		union aw_ucie_rx1_reg_rxhipspare_rdreg1 rx1_reg_rxhipspare_rdreg1; /* offset : 0x32278 */
		union aw_ucie_rx1_reg_rxhipspare_reg1 rx1_reg_rxhipspare_reg1; /* offset : 0x3227c */
		union aw_ucie_rx1_reg_rxhipspare_reg2 rx1_reg_rxhipspare_reg2; /* offset : 0x32280 */
		union aw_ucie_rx1_reg_rxioctrl_reg1 rx1_reg_rxioctrl_reg1; /* offset : 0x32284 */
		union aw_ucie_rx1_reg_rxioctrl_reg2 rx1_reg_rxioctrl_reg2; /* offset : 0x32288 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg1 rx1_reg_rxioen_afe_ovr_reg1; /* offset : 0x3228c */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg2 rx1_reg_rxioen_afe_ovr_reg2; /* offset : 0x32290 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg3 rx1_reg_rxioen_afe_ovr_reg3; /* offset : 0x32294 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg4 rx1_reg_rxioen_afe_ovr_reg4; /* offset : 0x32298 */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg1 rx1_reg_rxioen_data_ovr_reg1; /* offset : 0x3229c */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg2 rx1_reg_rxioen_data_ovr_reg2; /* offset : 0x322a0 */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg3 rx1_reg_rxioen_data_ovr_reg3; /* offset : 0x322a4 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg1 rx1_reg_rxioen_ovr_reg1; /* offset : 0x322a8 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg2 rx1_reg_rxioen_ovr_reg2; /* offset : 0x322ac */
		union aw_ucie_rx1_reg_rxioen_ovr_reg3 rx1_reg_rxioen_ovr_reg3; /* offset : 0x322b0 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg4 rx1_reg_rxioen_ovr_reg4; /* offset : 0x322b4 */
		union aw_ucie_rx1_reg_rxndealign_rdreg rx1_reg_rxndealign_rdreg; /* offset : 0x322b8 */
		union aw_ucie_rx1_reg_rxndealign_reg1 rx1_reg_rxndealign_reg1; /* offset : 0x322bc */
		union aw_ucie_rx1_reg_rxndealign_reg2 rx1_reg_rxndealign_reg2; /* offset : 0x322c0 */
		union aw_ucie_rx1_reg_rxndechk_rdreg1 rx1_reg_rxndechk_rdreg1; /* offset : 0x322c4 */
		union aw_ucie_rx1_reg_rxndechk_rdreg2 rx1_reg_rxndechk_rdreg2; /* offset : 0x322c8 */
		union aw_ucie_rx1_reg_rxndechk_rdreg3 rx1_reg_rxndechk_rdreg3; /* offset : 0x322cc */
		union aw_ucie_rx1_reg_rxndechk_rdreg4 rx1_reg_rxndechk_rdreg4; /* offset : 0x322d0 */
		union aw_ucie_rx1_reg_rxndechk_reg1 rx1_reg_rxndechk_reg1; /* offset : 0x322d4 */
		union aw_ucie_rx1_reg_rxndechk_reg2 rx1_reg_rxndechk_reg2; /* offset : 0x322d8 */
		union aw_ucie_rx1_reg_rxndechk_reg3 rx1_reg_rxndechk_reg3; /* offset : 0x322dc */
		union aw_ucie_rx1_reg_rxndesync_fg_reg1 rx1_reg_rxndesync_fg_reg1; /* offset : 0x322e0 */
		union aw_ucie_rx1_reg_rxndesync_fg_reg2 rx1_reg_rxndesync_fg_reg2; /* offset : 0x322e4 */
		union aw_ucie_rx1_reg_rxndesync_rdreg rx1_reg_rxndesync_rdreg; /* offset : 0x322e8 */
		union aw_ucie_rx1_reg_rxndesync_reg1 rx1_reg_rxndesync_reg1; /* offset : 0x322ec */
		union aw_ucie_rx1_reg_rxndesync_reg2 rx1_reg_rxndesync_reg2; /* offset : 0x322f0 */
		union aw_ucie_rx1_reg_rxretpi_rdreg rx1_reg_rxretpi_rdreg; /* offset : 0x322f4 */
		union aw_ucie_rx1_reg_rxretpi_reg1 rx1_reg_rxretpi_reg1; /* offset : 0x322f8 */
		union aw_ucie_rx1_reg_rxretpi_reg2 rx1_reg_rxretpi_reg2; /* offset : 0x322fc */
		union aw_ucie_rx1_reg_rxretpi_reg3 rx1_reg_rxretpi_reg3; /* offset : 0x32300 */
		union aw_ucie_rx1_reg_rxretpi_reg4 rx1_reg_rxretpi_reg4; /* offset : 0x32304 */
		union aw_ucie_rx1_reg_rxrst_reg1 rx1_reg_rxrst_reg1; /* offset : 0x32308 */
		union aw_ucie_rx1_reg_rxsip_clr rx1_reg_rxsip_clr; /* offset : 0x3230c */
		union aw_ucie_rx1_reg_rxsoc_rdreg rx1_reg_rxsoc_rdreg; /* offset : 0x32310 */
		union aw_ucie_rx1_reg_rxsoc_reg1 rx1_reg_rxsoc_reg1; /* offset : 0x32314 */
		union aw_ucie_rx1_reg_rxtimer1_rdreg rx1_reg_rxtimer1_rdreg; /* offset : 0x32318 */
		union aw_ucie_rx1_reg_rxtimer1_reg1 rx1_reg_rxtimer1_reg1; /* offset : 0x3231c */
		union aw_ucie_rx1_reg_rxtimer1_reg2 rx1_reg_rxtimer1_reg2; /* offset : 0x32320 */
		union aw_ucie_rx1_reg_rxtimer2_rdreg rx1_reg_rxtimer2_rdreg; /* offset : 0x32324 */
		union aw_ucie_rx1_reg_rxtimer2_reg1 rx1_reg_rxtimer2_reg1; /* offset : 0x32328 */
		union aw_ucie_rx1_reg_rxtimer2_reg2 rx1_reg_rxtimer2_reg2; /* offset : 0x3232c */
		union aw_ucie_rx1_reg_rxclkchk_rdreg2 rx1_reg_rxclkchk_rdreg2; /* offset : 0x32330 */
		union aw_ucie_rx1_reg_rxclkchk_config1 rx1_reg_rxclkchk_config1; /* offset : 0x32334 */
		union aw_ucie_rx1_reg_rxdatchk_int1 rx1_reg_rxdatchk_int1; /* offset : 0x32338 */
		union aw_ucie_rx1_reg_rxdatchk_int1_mask rx1_reg_rxdatchk_int1_mask; /* offset : 0x3233c */
		union aw_ucie_rx1_reg_rxdatchk_int2 rx1_reg_rxdatchk_int2; /* offset : 0x32340 */
		union aw_ucie_rx1_reg_rxdatchk_int2_mask rx1_reg_rxdatchk_int2_mask; /* offset : 0x32344 */
		union aw_ucie_rx1_reg_rxclkchk_rdreg3 rx1_reg_rxclkchk_rdreg3; /* offset : 0x32348 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg13 rx1_reg_rxdatchk_rdreg13; /* offset : 0x3234c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg14 rx1_reg_rxdatchk_rdreg14; /* offset : 0x32350 */
		union aw_ucie_rx1_reg_rxdatchk_reg14 rx1_reg_rxdatchk_reg14; /* offset : 0x32354 */
		uint32_t reserved_37[298];
		union aw_ucie_tx1_reg_tx_csr_ctrl tx1_reg_tx_csr_ctrl; /* offset : 0x32800 */
		union aw_ucie_tx1_reg_tx_ctrl tx1_reg_tx_ctrl; /* offset : 0x32804 */
		union aw_ucie_tx1_reg_tx_ctrl_rdreg tx1_reg_tx_ctrl_rdreg; /* offset : 0x32808 */
		union aw_ucie_tx1_reg_txcalen tx1_reg_txcalen; /* offset : 0x3280c */
		union aw_ucie_tx1_reg_txcmn_reg1 tx1_reg_txcmn_reg1; /* offset : 0x32810 */
		union aw_ucie_tx1_reg_txcmn_reg2 tx1_reg_txcmn_reg2; /* offset : 0x32814 */
		union aw_ucie_tx1_reg_txdatapath_reg0 tx1_reg_txdatapath_reg0; /* offset : 0x32818 */
		union aw_ucie_tx1_reg_txdatapath_reg1 tx1_reg_txdatapath_reg1; /* offset : 0x3281c */
		union aw_ucie_tx1_reg_txdatapath_reg2 tx1_reg_txdatapath_reg2; /* offset : 0x32820 */
		union aw_ucie_tx1_reg_txdatapath_reg3 tx1_reg_txdatapath_reg3; /* offset : 0x32824 */
		union aw_ucie_tx1_reg_txdatapath_reg4 tx1_reg_txdatapath_reg4; /* offset : 0x32828 */
		union aw_ucie_tx1_reg_txdatapath_reg5 tx1_reg_txdatapath_reg5; /* offset : 0x3282c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg0 tx1_reg_txdatgen_perlaneid_reg0; /* offset : 0x32830 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg1 tx1_reg_txdatgen_perlaneid_reg1; /* offset : 0x32834 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg10 tx1_reg_txdatgen_perlaneid_reg10; /* offset : 0x32838 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg11 tx1_reg_txdatgen_perlaneid_reg11; /* offset : 0x3283c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg12 tx1_reg_txdatgen_perlaneid_reg12; /* offset : 0x32840 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg13 tx1_reg_txdatgen_perlaneid_reg13; /* offset : 0x32844 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg14 tx1_reg_txdatgen_perlaneid_reg14; /* offset : 0x32848 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg15 tx1_reg_txdatgen_perlaneid_reg15; /* offset : 0x3284c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg16 tx1_reg_txdatgen_perlaneid_reg16; /* offset : 0x32850 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg2 tx1_reg_txdatgen_perlaneid_reg2; /* offset : 0x32854 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg3 tx1_reg_txdatgen_perlaneid_reg3; /* offset : 0x32858 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg4 tx1_reg_txdatgen_perlaneid_reg4; /* offset : 0x3285c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg5 tx1_reg_txdatgen_perlaneid_reg5; /* offset : 0x32860 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg6 tx1_reg_txdatgen_perlaneid_reg6; /* offset : 0x32864 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg7 tx1_reg_txdatgen_perlaneid_reg7; /* offset : 0x32868 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg8 tx1_reg_txdatgen_perlaneid_reg8; /* offset : 0x3286c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg9 tx1_reg_txdatgen_perlaneid_reg9; /* offset : 0x32870 */
		union aw_ucie_tx1_reg_txdatgen_rdreg tx1_reg_txdatgen_rdreg; /* offset : 0x32874 */
		union aw_ucie_tx1_reg_txdatgen_reg1 tx1_reg_txdatgen_reg1; /* offset : 0x32878 */
		union aw_ucie_tx1_reg_txdatgen_reg10 tx1_reg_txdatgen_reg10; /* offset : 0x3287c */
		union aw_ucie_tx1_reg_txdatgen_reg11 tx1_reg_txdatgen_reg11; /* offset : 0x32880 */
		union aw_ucie_tx1_reg_txdatgen_reg12 tx1_reg_txdatgen_reg12; /* offset : 0x32884 */
		union aw_ucie_tx1_reg_txdatgen_reg13 tx1_reg_txdatgen_reg13; /* offset : 0x32888 */
		union aw_ucie_tx1_reg_txdatgen_reg14 tx1_reg_txdatgen_reg14; /* offset : 0x3288c */
		union aw_ucie_tx1_reg_txdatgen_reg15 tx1_reg_txdatgen_reg15; /* offset : 0x32890 */
		union aw_ucie_tx1_reg_txdatgen_reg16 tx1_reg_txdatgen_reg16; /* offset : 0x32894 */
		union aw_ucie_tx1_reg_txdatgen_reg17 tx1_reg_txdatgen_reg17; /* offset : 0x32898 */
		union aw_ucie_tx1_reg_txdatgen_reg18 tx1_reg_txdatgen_reg18; /* offset : 0x3289c */
		union aw_ucie_tx1_reg_txdatgen_reg19 tx1_reg_txdatgen_reg19; /* offset : 0x328a0 */
		union aw_ucie_tx1_reg_txdatgen_reg2 tx1_reg_txdatgen_reg2; /* offset : 0x328a4 */
		union aw_ucie_tx1_reg_txdatgen_reg20 tx1_reg_txdatgen_reg20; /* offset : 0x328a8 */
		union aw_ucie_tx1_reg_txdatgen_reg21 tx1_reg_txdatgen_reg21; /* offset : 0x328ac */
		union aw_ucie_tx1_reg_txdatgen_reg3 tx1_reg_txdatgen_reg3; /* offset : 0x328b0 */
		union aw_ucie_tx1_reg_txdatgen_reg4 tx1_reg_txdatgen_reg4; /* offset : 0x328b4 */
		union aw_ucie_tx1_reg_txdatgen_reg5 tx1_reg_txdatgen_reg5; /* offset : 0x328b8 */
		union aw_ucie_tx1_reg_txdatgen_reg6 tx1_reg_txdatgen_reg6; /* offset : 0x328bc */
		union aw_ucie_tx1_reg_txdatgen_reg7 tx1_reg_txdatgen_reg7; /* offset : 0x328c0 */
		union aw_ucie_tx1_reg_txdatgen_reg8 tx1_reg_txdatgen_reg8; /* offset : 0x328c4 */
		union aw_ucie_tx1_reg_txdatgen_reg9 tx1_reg_txdatgen_reg9; /* offset : 0x328c8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg0 tx1_reg_txdatgen_seed_udp_reg0; /* offset : 0x328cc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg1 tx1_reg_txdatgen_seed_udp_reg1; /* offset : 0x328d0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg10 tx1_reg_txdatgen_seed_udp_reg10; /* offset : 0x328d4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg11 tx1_reg_txdatgen_seed_udp_reg11; /* offset : 0x328d8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg12 tx1_reg_txdatgen_seed_udp_reg12; /* offset : 0x328dc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg13 tx1_reg_txdatgen_seed_udp_reg13; /* offset : 0x328e0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg14 tx1_reg_txdatgen_seed_udp_reg14; /* offset : 0x328e4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg15 tx1_reg_txdatgen_seed_udp_reg15; /* offset : 0x328e8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg16 tx1_reg_txdatgen_seed_udp_reg16; /* offset : 0x328ec */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg17 tx1_reg_txdatgen_seed_udp_reg17; /* offset : 0x328f0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg18 tx1_reg_txdatgen_seed_udp_reg18; /* offset : 0x328f4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg19 tx1_reg_txdatgen_seed_udp_reg19; /* offset : 0x328f8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg2 tx1_reg_txdatgen_seed_udp_reg2; /* offset : 0x328fc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg20 tx1_reg_txdatgen_seed_udp_reg20; /* offset : 0x32900 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg21 tx1_reg_txdatgen_seed_udp_reg21; /* offset : 0x32904 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg22 tx1_reg_txdatgen_seed_udp_reg22; /* offset : 0x32908 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg23 tx1_reg_txdatgen_seed_udp_reg23; /* offset : 0x3290c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg24 tx1_reg_txdatgen_seed_udp_reg24; /* offset : 0x32910 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg25 tx1_reg_txdatgen_seed_udp_reg25; /* offset : 0x32914 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg26 tx1_reg_txdatgen_seed_udp_reg26; /* offset : 0x32918 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg27 tx1_reg_txdatgen_seed_udp_reg27; /* offset : 0x3291c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg28 tx1_reg_txdatgen_seed_udp_reg28; /* offset : 0x32920 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg29 tx1_reg_txdatgen_seed_udp_reg29; /* offset : 0x32924 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg3 tx1_reg_txdatgen_seed_udp_reg3; /* offset : 0x32928 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg30 tx1_reg_txdatgen_seed_udp_reg30; /* offset : 0x3292c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg31 tx1_reg_txdatgen_seed_udp_reg31; /* offset : 0x32930 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg32 tx1_reg_txdatgen_seed_udp_reg32; /* offset : 0x32934 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg33 tx1_reg_txdatgen_seed_udp_reg33; /* offset : 0x32938 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg34 tx1_reg_txdatgen_seed_udp_reg34; /* offset : 0x3293c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg35 tx1_reg_txdatgen_seed_udp_reg35; /* offset : 0x32940 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg36 tx1_reg_txdatgen_seed_udp_reg36; /* offset : 0x32944 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg37 tx1_reg_txdatgen_seed_udp_reg37; /* offset : 0x32948 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg38 tx1_reg_txdatgen_seed_udp_reg38; /* offset : 0x3294c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg39 tx1_reg_txdatgen_seed_udp_reg39; /* offset : 0x32950 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg4 tx1_reg_txdatgen_seed_udp_reg4; /* offset : 0x32954 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg40 tx1_reg_txdatgen_seed_udp_reg40; /* offset : 0x32958 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg41 tx1_reg_txdatgen_seed_udp_reg41; /* offset : 0x3295c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg42 tx1_reg_txdatgen_seed_udp_reg42; /* offset : 0x32960 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg43 tx1_reg_txdatgen_seed_udp_reg43; /* offset : 0x32964 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg44 tx1_reg_txdatgen_seed_udp_reg44; /* offset : 0x32968 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg45 tx1_reg_txdatgen_seed_udp_reg45; /* offset : 0x3296c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg46 tx1_reg_txdatgen_seed_udp_reg46; /* offset : 0x32970 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg47 tx1_reg_txdatgen_seed_udp_reg47; /* offset : 0x32974 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg48 tx1_reg_txdatgen_seed_udp_reg48; /* offset : 0x32978 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg49 tx1_reg_txdatgen_seed_udp_reg49; /* offset : 0x3297c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg5 tx1_reg_txdatgen_seed_udp_reg5; /* offset : 0x32980 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg50 tx1_reg_txdatgen_seed_udp_reg50; /* offset : 0x32984 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg51 tx1_reg_txdatgen_seed_udp_reg51; /* offset : 0x32988 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg52 tx1_reg_txdatgen_seed_udp_reg52; /* offset : 0x3298c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg53 tx1_reg_txdatgen_seed_udp_reg53; /* offset : 0x32990 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg54 tx1_reg_txdatgen_seed_udp_reg54; /* offset : 0x32994 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg55 tx1_reg_txdatgen_seed_udp_reg55; /* offset : 0x32998 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg56 tx1_reg_txdatgen_seed_udp_reg56; /* offset : 0x3299c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg57 tx1_reg_txdatgen_seed_udp_reg57; /* offset : 0x329a0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg58 tx1_reg_txdatgen_seed_udp_reg58; /* offset : 0x329a4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg59 tx1_reg_txdatgen_seed_udp_reg59; /* offset : 0x329a8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg6 tx1_reg_txdatgen_seed_udp_reg6; /* offset : 0x329ac */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg60 tx1_reg_txdatgen_seed_udp_reg60; /* offset : 0x329b0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg61 tx1_reg_txdatgen_seed_udp_reg61; /* offset : 0x329b4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg62 tx1_reg_txdatgen_seed_udp_reg62; /* offset : 0x329b8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg63 tx1_reg_txdatgen_seed_udp_reg63; /* offset : 0x329bc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg64 tx1_reg_txdatgen_seed_udp_reg64; /* offset : 0x329c0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg65 tx1_reg_txdatgen_seed_udp_reg65; /* offset : 0x329c4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg66 tx1_reg_txdatgen_seed_udp_reg66; /* offset : 0x329c8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg67 tx1_reg_txdatgen_seed_udp_reg67; /* offset : 0x329cc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg68 tx1_reg_txdatgen_seed_udp_reg68; /* offset : 0x329d0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg69 tx1_reg_txdatgen_seed_udp_reg69; /* offset : 0x329d4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg7 tx1_reg_txdatgen_seed_udp_reg7; /* offset : 0x329d8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg70 tx1_reg_txdatgen_seed_udp_reg70; /* offset : 0x329dc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg71 tx1_reg_txdatgen_seed_udp_reg71; /* offset : 0x329e0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg72 tx1_reg_txdatgen_seed_udp_reg72; /* offset : 0x329e4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg73 tx1_reg_txdatgen_seed_udp_reg73; /* offset : 0x329e8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg8 tx1_reg_txdatgen_seed_udp_reg8; /* offset : 0x329ec */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg9 tx1_reg_txdatgen_seed_udp_reg9; /* offset : 0x329f0 */
		union aw_ucie_tx1_reg_txdcc_bg_reg1 tx1_reg_txdcc_bg_reg1; /* offset : 0x329f4 */
		union aw_ucie_tx1_reg_txdcc_fg_reg1 tx1_reg_txdcc_fg_reg1; /* offset : 0x329f8 */
		union aw_ucie_tx1_reg_txdcc_fg_reg2 tx1_reg_txdcc_fg_reg2; /* offset : 0x329fc */
		union aw_ucie_tx1_reg_txdcc_rdreg tx1_reg_txdcc_rdreg; /* offset : 0x32a00 */
		union aw_ucie_tx1_reg_txdcc_reg1 tx1_reg_txdcc_reg1; /* offset : 0x32a04 */
		union aw_ucie_tx1_reg_txdcc_reg2 tx1_reg_txdcc_reg2; /* offset : 0x32a08 */
		union aw_ucie_tx1_reg_txhip_clr tx1_reg_txhip_clr; /* offset : 0x32a0c */
		union aw_ucie_tx1_reg_txhip_dccack_rdreg tx1_reg_txhip_dccack_rdreg; /* offset : 0x32a10 */
		union aw_ucie_tx1_reg_txhip_dccctrl tx1_reg_txhip_dccctrl; /* offset : 0x32a14 */
		union aw_ucie_tx1_reg_txhip_dccreq tx1_reg_txhip_dccreq; /* offset : 0x32a18 */
		union aw_ucie_tx1_reg_txhip_dccval tx1_reg_txhip_dccval; /* offset : 0x32a1c */
		union aw_ucie_tx1_reg_txhip_dccval_rdreg tx1_reg_txhip_dccval_rdreg; /* offset : 0x32a20 */
		union aw_ucie_tx1_reg_txhip_piack_rdreg tx1_reg_txhip_piack_rdreg; /* offset : 0x32a24 */
		union aw_ucie_tx1_reg_txhip_pictrl tx1_reg_txhip_pictrl; /* offset : 0x32a28 */
		union aw_ucie_tx1_reg_txhip_pireq tx1_reg_txhip_pireq; /* offset : 0x32a2c */
		union aw_ucie_tx1_reg_txhip_pival tx1_reg_txhip_pival; /* offset : 0x32a30 */
		union aw_ucie_tx1_reg_txhip_pival_rdreg tx1_reg_txhip_pival_rdreg; /* offset : 0x32a34 */
		union aw_ucie_tx1_reg_txhip_rdreg1 tx1_reg_txhip_rdreg1; /* offset : 0x32a38 */
		union aw_ucie_tx1_reg_txhipcmn_reg1 tx1_reg_txhipcmn_reg1; /* offset : 0x32a3c */
		union aw_ucie_tx1_reg_txhipcmnio_reg1 tx1_reg_txhipcmnio_reg1; /* offset : 0x32a40 */
		union aw_ucie_tx1_reg_txhipcmnio_reg2 tx1_reg_txhipcmnio_reg2; /* offset : 0x32a44 */
		union aw_ucie_tx1_reg_txhipcmnio_reg3 tx1_reg_txhipcmnio_reg3; /* offset : 0x32a48 */
		union aw_ucie_tx1_reg_txhipctrl_reg1 tx1_reg_txhipctrl_reg1; /* offset : 0x32a4c */
		union aw_ucie_tx1_reg_txhipio tx1_reg_txhipio; /* offset : 0x32a50 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg1 tx1_reg_txhipiosync_rdreg1; /* offset : 0x32a54 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg2 tx1_reg_txhipiosync_rdreg2; /* offset : 0x32a58 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg3 tx1_reg_txhipiosync_rdreg3; /* offset : 0x32a5c */
		union aw_ucie_tx1_reg_txhipload_reg1 tx1_reg_txhipload_reg1; /* offset : 0x32a60 */
		union aw_ucie_tx1_reg_txhipload_reg2 tx1_reg_txhipload_reg2; /* offset : 0x32a64 */
		union aw_ucie_tx1_reg_txhipload_reg3 tx1_reg_txhipload_reg3; /* offset : 0x32a68 */
		union aw_ucie_tx1_reg_txhipspare_rdreg1 tx1_reg_txhipspare_rdreg1; /* offset : 0x32a6c */
		union aw_ucie_tx1_reg_txhipspare_reg1 tx1_reg_txhipspare_reg1; /* offset : 0x32a70 */
		union aw_ucie_tx1_reg_txhipspare_reg2 tx1_reg_txhipspare_reg2; /* offset : 0x32a74 */
		union aw_ucie_tx1_reg_txioctrl_reg1 tx1_reg_txioctrl_reg1; /* offset : 0x32a78 */
		union aw_ucie_tx1_reg_txioctrl_reg10 tx1_reg_txioctrl_reg10; /* offset : 0x32a7c */
		union aw_ucie_tx1_reg_txioctrl_reg11 tx1_reg_txioctrl_reg11; /* offset : 0x32a80 */
		union aw_ucie_tx1_reg_txioctrl_reg12 tx1_reg_txioctrl_reg12; /* offset : 0x32a84 */
		union aw_ucie_tx1_reg_txioctrl_reg13 tx1_reg_txioctrl_reg13; /* offset : 0x32a88 */
		union aw_ucie_tx1_reg_txioctrl_reg14 tx1_reg_txioctrl_reg14; /* offset : 0x32a8c */
		union aw_ucie_tx1_reg_txioctrl_reg15 tx1_reg_txioctrl_reg15; /* offset : 0x32a90 */
		union aw_ucie_tx1_reg_txioctrl_reg16 tx1_reg_txioctrl_reg16; /* offset : 0x32a94 */
		union aw_ucie_tx1_reg_txioctrl_reg17 tx1_reg_txioctrl_reg17; /* offset : 0x32a98 */
		union aw_ucie_tx1_reg_txioctrl_reg18 tx1_reg_txioctrl_reg18; /* offset : 0x32a9c */
		union aw_ucie_tx1_reg_txioctrl_reg2 tx1_reg_txioctrl_reg2; /* offset : 0x32aa0 */
		union aw_ucie_tx1_reg_txioctrl_reg3 tx1_reg_txioctrl_reg3; /* offset : 0x32aa4 */
		union aw_ucie_tx1_reg_txioctrl_reg4 tx1_reg_txioctrl_reg4; /* offset : 0x32aa8 */
		union aw_ucie_tx1_reg_txioctrl_reg5 tx1_reg_txioctrl_reg5; /* offset : 0x32aac */
		union aw_ucie_tx1_reg_txioctrl_reg6 tx1_reg_txioctrl_reg6; /* offset : 0x32ab0 */
		union aw_ucie_tx1_reg_txioctrl_reg7 tx1_reg_txioctrl_reg7; /* offset : 0x32ab4 */
		union aw_ucie_tx1_reg_txioctrl_reg8 tx1_reg_txioctrl_reg8; /* offset : 0x32ab8 */
		union aw_ucie_tx1_reg_txioctrl_reg9 tx1_reg_txioctrl_reg9; /* offset : 0x32abc */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg1 tx1_reg_txioen_afe_ovr_reg1; /* offset : 0x32ac0 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg2 tx1_reg_txioen_afe_ovr_reg2; /* offset : 0x32ac4 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg3 tx1_reg_txioen_afe_ovr_reg3; /* offset : 0x32ac8 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg4 tx1_reg_txioen_afe_ovr_reg4; /* offset : 0x32acc */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg1 tx1_reg_txioen_data_ovr_reg1; /* offset : 0x32ad0 */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg2 tx1_reg_txioen_data_ovr_reg2; /* offset : 0x32ad4 */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg3 tx1_reg_txioen_data_ovr_reg3; /* offset : 0x32ad8 */
		union aw_ucie_tx1_reg_txioen_ovr_reg1 tx1_reg_txioen_ovr_reg1; /* offset : 0x32adc */
		union aw_ucie_tx1_reg_txioen_ovr_reg2 tx1_reg_txioen_ovr_reg2; /* offset : 0x32ae0 */
		union aw_ucie_tx1_reg_txioen_ovr_reg3 tx1_reg_txioen_ovr_reg3; /* offset : 0x32ae4 */
		union aw_ucie_tx1_reg_txioen_ovr_reg4 tx1_reg_txioen_ovr_reg4; /* offset : 0x32ae8 */
		union aw_ucie_tx1_reg_txqcc_rdreg tx1_reg_txqcc_rdreg; /* offset : 0x32aec */
		union aw_ucie_tx1_reg_txqcc_reg1 tx1_reg_txqcc_reg1; /* offset : 0x32af0 */
		union aw_ucie_tx1_reg_txqcc_reg2 tx1_reg_txqcc_reg2; /* offset : 0x32af4 */
		union aw_ucie_tx1_reg_txqcc_reg3 tx1_reg_txqcc_reg3; /* offset : 0x32af8 */
		union aw_ucie_tx1_reg_txqcc_reg4 tx1_reg_txqcc_reg4; /* offset : 0x32afc */
		union aw_ucie_tx1_reg_txretpi_rdreg tx1_reg_txretpi_rdreg; /* offset : 0x32b00 */
		union aw_ucie_tx1_reg_txretpi_reg1 tx1_reg_txretpi_reg1; /* offset : 0x32b04 */
		union aw_ucie_tx1_reg_txretpi_reg2 tx1_reg_txretpi_reg2; /* offset : 0x32b08 */
		union aw_ucie_tx1_reg_txretpi_reg3 tx1_reg_txretpi_reg3; /* offset : 0x32b0c */
		union aw_ucie_tx1_reg_txretpi_reg4 tx1_reg_txretpi_reg4; /* offset : 0x32b10 */
		union aw_ucie_tx1_reg_txrst_reg1 tx1_reg_txrst_reg1; /* offset : 0x32b14 */
		union aw_ucie_tx1_reg_txsip_clr tx1_reg_txsip_clr; /* offset : 0x32b18 */
		union aw_ucie_tx1_reg_txsoc_rdreg tx1_reg_txsoc_rdreg; /* offset : 0x32b1c */
		union aw_ucie_tx1_reg_txsoc_reg1 tx1_reg_txsoc_reg1; /* offset : 0x32b20 */
		union aw_ucie_tx1_reg_txsync_bg_reg1 tx1_reg_txsync_bg_reg1; /* offset : 0x32b24 */
		union aw_ucie_tx1_reg_txsync_fg_reg1 tx1_reg_txsync_fg_reg1; /* offset : 0x32b28 */
		union aw_ucie_tx1_reg_txsync_fg_reg2 tx1_reg_txsync_fg_reg2; /* offset : 0x32b2c */
		union aw_ucie_tx1_reg_txsync_rdreg tx1_reg_txsync_rdreg; /* offset : 0x32b30 */
		union aw_ucie_tx1_reg_txsync_reg1 tx1_reg_txsync_reg1; /* offset : 0x32b34 */
		union aw_ucie_tx1_reg_txsync_reg2 tx1_reg_txsync_reg2; /* offset : 0x32b38 */
		union aw_ucie_tx1_reg_txtimer1_rdreg tx1_reg_txtimer1_rdreg; /* offset : 0x32b3c */
		union aw_ucie_tx1_reg_txtimer1_reg1 tx1_reg_txtimer1_reg1; /* offset : 0x32b40 */
		union aw_ucie_tx1_reg_txtimer1_reg2 tx1_reg_txtimer1_reg2; /* offset : 0x32b44 */
		union aw_ucie_tx1_reg_txtimer2_rdreg tx1_reg_txtimer2_rdreg; /* offset : 0x32b48 */
		union aw_ucie_tx1_reg_txtimer2_reg1 tx1_reg_txtimer2_reg1; /* offset : 0x32b4c */
		union aw_ucie_tx1_reg_txtimer2_reg2 tx1_reg_txtimer2_reg2; /* offset : 0x32b50 */
		union aw_ucie_tx1_reg_txdatgen_int1 tx1_reg_txdatgen_int1; /* offset : 0x32b54 */
		union aw_ucie_tx1_reg_txdatgen_int1_mask tx1_reg_txdatgen_int1_mask; /* offset : 0x32b58 */
		union aw_ucie_tx1_reg_txdatgen_int2 tx1_reg_txdatgen_int2; /* offset : 0x32b5c */
		union aw_ucie_tx1_reg_txdatgen_int2_mask tx1_reg_txdatgen_int2_mask; /* offset : 0x32b60 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg5 tx1_reg_txioen_afe_ovr_reg5; /* offset : 0x32b64 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg6 tx1_reg_txioen_afe_ovr_reg6; /* offset : 0x32b68 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg7 tx1_reg_txioen_afe_ovr_reg7; /* offset : 0x32b6c */
		uint32_t reserved_38[292];
		union aw_ucie_sb1_reg_reg_sb_afe_cfg1 sb1_reg_reg_sb_afe_cfg1; /* offset : 0x33000 */
		union aw_ucie_sb1_reg_reg_sb_afe_cfg2 sb1_reg_reg_sb_afe_cfg2; /* offset : 0x33004 */
		union aw_ucie_sb1_reg_reg_sb_cmn_reset_cfg sb1_reg_reg_sb_cmn_reset_cfg; /* offset : 0x33008 */
		union aw_ucie_sb1_reg_rst_reg1 sb1_reg_rst_reg1; /* offset : 0x3300c */
		union aw_ucie_sb1_reg_rxsb_afifo_cfg sb1_reg_rxsb_afifo_cfg; /* offset : 0x33010 */
		union aw_ucie_sb1_reg_rxsb_cfg sb1_reg_rxsb_cfg; /* offset : 0x33014 */
		union aw_ucie_sb1_reg_sb_sfifo_int1_mask sb1_reg_sb_sfifo_int1_mask; /* offset : 0x33018 */
		union aw_ucie_sb1_reg_sb_sfifo_int1 sb1_reg_sb_sfifo_int1; /* offset : 0x3301c */
		uint32_t reserved_39;
		union aw_ucie_sb1_reg_rxsb_rdreg1 sb1_reg_rxsb_rdreg1; /* offset : 0x33024 */
		union aw_ucie_sb1_reg_rxsbacccom_cfg sb1_reg_rxsbacccom_cfg; /* offset : 0x33028 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg1 sb1_reg_rxsbacccom_rdreg1; /* offset : 0x3302c */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg2 sb1_reg_rxsbacccom_rdreg2; /* offset : 0x33030 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg3 sb1_reg_rxsbacccom_rdreg3; /* offset : 0x33034 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg4 sb1_reg_rxsbacccom_rdreg4; /* offset : 0x33038 */
		union aw_ucie_sb1_reg_rxsbaccreq_cfg sb1_reg_rxsbaccreq_cfg; /* offset : 0x3303c */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg1 sb1_reg_rxsbaccreq_rdreg1; /* offset : 0x33040 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg2 sb1_reg_rxsbaccreq_rdreg2; /* offset : 0x33044 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg3 sb1_reg_rxsbaccreq_rdreg3; /* offset : 0x33048 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg4 sb1_reg_rxsbaccreq_rdreg4; /* offset : 0x3304c */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg5 sb1_reg_rxsbaccreq_rdreg5; /* offset : 0x33050 */
		union aw_ucie_sb1_reg_rxsbmsg_cfg sb1_reg_rxsbmsg_cfg; /* offset : 0x33054 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg1 sb1_reg_rxsbmsg_rdreg1; /* offset : 0x33058 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg2 sb1_reg_rxsbmsg_rdreg2; /* offset : 0x3305c */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg3 sb1_reg_rxsbmsg_rdreg3; /* offset : 0x33060 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg4 sb1_reg_rxsbmsg_rdreg4; /* offset : 0x33064 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg5 sb1_reg_rxsbmsg_rdreg5; /* offset : 0x33068 */
		union aw_ucie_sb1_reg_rxsbvmsg_cfg sb1_reg_rxsbvmsg_cfg; /* offset : 0x3306c */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg1 sb1_reg_rxsbvmsg_rdreg1; /* offset : 0x33070 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg2 sb1_reg_rxsbvmsg_rdreg2; /* offset : 0x33074 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg3 sb1_reg_rxsbvmsg_rdreg3; /* offset : 0x33078 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg4 sb1_reg_rxsbvmsg_rdreg4; /* offset : 0x3307c */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg5 sb1_reg_rxsbvmsg_rdreg5; /* offset : 0x33080 */
		union aw_ucie_sb1_reg_sb_csr_ctrl sb1_reg_sb_csr_ctrl; /* offset : 0x33084 */
		union aw_ucie_sb1_reg_soc_reg1 sb1_reg_soc_reg1; /* offset : 0x33088 */
		union aw_ucie_sb1_reg_txsb_afifo_cfg sb1_reg_txsb_afifo_cfg; /* offset : 0x3308c */
		union aw_ucie_sb1_reg_txsb_cfg1 sb1_reg_txsb_cfg1; /* offset : 0x33090 */
		union aw_ucie_sb1_reg_txsb_cfg10 sb1_reg_txsb_cfg10; /* offset : 0x33094 */
		union aw_ucie_sb1_reg_txsb_cfg11 sb1_reg_txsb_cfg11; /* offset : 0x33098 */
		union aw_ucie_sb1_reg_txsb_cfg2 sb1_reg_txsb_cfg2; /* offset : 0x3309c */
		union aw_ucie_sb1_reg_txsb_cfg3 sb1_reg_txsb_cfg3; /* offset : 0x330a0 */
		union aw_ucie_sb1_reg_txsb_cfg4 sb1_reg_txsb_cfg4; /* offset : 0x330a4 */
		union aw_ucie_sb1_reg_txsb_cfg5 sb1_reg_txsb_cfg5; /* offset : 0x330a8 */
		union aw_ucie_sb1_reg_txsb_cfg6 sb1_reg_txsb_cfg6; /* offset : 0x330ac */
		union aw_ucie_sb1_reg_txsb_cfg7 sb1_reg_txsb_cfg7; /* offset : 0x330b0 */
		union aw_ucie_sb1_reg_txsb_cfg8 sb1_reg_txsb_cfg8; /* offset : 0x330b4 */
		union aw_ucie_sb1_reg_txsb_cfg9 sb1_reg_txsb_cfg9; /* offset : 0x330b8 */
		union aw_ucie_sb1_reg_txsb_stall_rdreg1 sb1_reg_txsb_stall_rdreg1; /* offset : 0x330bc */
		union aw_ucie_sb1_reg_sb_afifo_int1_mask sb1_reg_sb_afifo_int1_mask; /* offset : 0x330c0 */
		union aw_ucie_sb1_reg_sb_afifo_int1 sb1_reg_sb_afifo_int1; /* offset : 0x330c4 */
		union aw_ucie_sb1_reg_sb_sfifo_int2_mask sb1_reg_sb_sfifo_int2_mask; /* offset : 0x330c8 */
		union aw_ucie_sb1_reg_sb_sfifo_int2 sb1_reg_sb_sfifo_int2; /* offset : 0x330cc */
		union aw_ucie_sb1_reg_sb_afifo_int2_mask sb1_reg_sb_afifo_int2_mask; /* offset : 0x330d0 */
		union aw_ucie_sb1_reg_sb_afifo_int2 sb1_reg_sb_afifo_int2; /* offset : 0x330d4 */
		union aw_ucie_sb1_reg_sb_timeout_count_config1_reg sb1_reg_sb_timeout_count_config1_reg; /* offset : 0x330d8 */
		union aw_ucie_sb1_reg_sb_timeout_count_config2_reg sb1_reg_sb_timeout_count_config2_reg; /* offset : 0x330dc */
		union aw_ucie_sb1_reg_sb_rx_cntrl_config_reg sb1_reg_sb_rx_cntrl_config_reg; /* offset : 0x330e0 */
		uint32_t reserved_40[455];
		union aw_ucie_dfx1_reg_clk_ctrl dfx1_reg_clk_ctrl; /* offset : 0x33800 */
		union aw_ucie_dfx1_reg_dfx_csr_ctrl dfx1_reg_dfx_csr_ctrl; /* offset : 0x33804 */
		union aw_ucie_dfx1_reg_dfx_ctrl dfx1_reg_dfx_ctrl; /* offset : 0x33808 */
		union aw_ucie_dfx1_reg_dfx_stat_rdreg dfx1_reg_dfx_stat_rdreg; /* offset : 0x3380c */
		union aw_ucie_dfx1_reg_lane_mcu_boot_addr dfx1_reg_lane_mcu_boot_addr; /* offset : 0x33810 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump0 dfx1_reg_lane_mcu_crash_dump0; /* offset : 0x33814 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump1 dfx1_reg_lane_mcu_crash_dump1; /* offset : 0x33818 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump2 dfx1_reg_lane_mcu_crash_dump2; /* offset : 0x3381c */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump3 dfx1_reg_lane_mcu_crash_dump3; /* offset : 0x33820 */
		union aw_ucie_dfx1_reg_lane_mcu_ctrl dfx1_reg_lane_mcu_ctrl; /* offset : 0x33824 */
		union aw_ucie_dfx1_reg_lane_mcu_device_addr dfx1_reg_lane_mcu_device_addr; /* offset : 0x33828 */
		union aw_ucie_dfx1_reg_lane_mcu_dmem dfx1_reg_lane_mcu_dmem; /* offset : 0x3382c */
		union aw_ucie_dfx1_reg_lane_mcu_hart_id dfx1_reg_lane_mcu_hart_id; /* offset : 0x33830 */
		union aw_ucie_dfx1_reg_lane_mcu_irq dfx1_reg_lane_mcu_irq; /* offset : 0x33834 */
		union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl1 dfx1_reg_lane_mcu_irq_ctrl1; /* offset : 0x33838 */
		union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl2 dfx1_reg_lane_mcu_irq_ctrl2; /* offset : 0x3383c */
		union aw_ucie_dfx1_reg_lane_mcu_stats dfx1_reg_lane_mcu_stats; /* offset : 0x33840 */
		uint32_t reserved_41[15855];
		union aw_ucie_bridge_top_reg_reg_bridge_top_fifo_wm bridge_top_reg_reg_bridge_top_fifo_wm; /* offset : 0x43000 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1 bridge_top_reg_reg_bridge_top_interrupt1; /* offset : 0x43004 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1_mask bridge_top_reg_reg_bridge_top_interrupt1_mask; /* offset : 0x43008 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2 bridge_top_reg_reg_bridge_top_interrupt2; /* offset : 0x4300c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2_mask bridge_top_reg_reg_bridge_top_interrupt2_mask; /* offset : 0x43010 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary bridge_top_reg_reg_bridge_top_intr1_summary; /* offset : 0x43014 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary_mask bridge_top_reg_reg_bridge_top_intr1_summary_mask; /* offset : 0x43018 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary bridge_top_reg_reg_bridge_top_intr2_summary; /* offset : 0x4301c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary_mask bridge_top_reg_reg_bridge_top_intr2_summary_mask; /* offset : 0x43020 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_cfg bridge_top_reg_reg_bridge_top_cmn_cfg; /* offset : 0x43024 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status bridge_top_reg_reg_bridge_top_cmn_status; /* offset : 0x43028 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status2 bridge_top_reg_reg_bridge_top_cmn_status2; /* offset : 0x4302c */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg1 bridge_top_reg_fdi_txsb_cfg1; /* offset : 0x43030 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg2 bridge_top_reg_fdi_txsb_cfg2; /* offset : 0x43034 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg3 bridge_top_reg_fdi_txsb_cfg3; /* offset : 0x43038 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg4 bridge_top_reg_fdi_txsb_cfg4; /* offset : 0x4303c */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg5 bridge_top_reg_fdi_txsb_cfg5; /* offset : 0x43040 */
		union aw_ucie_bridge_top_reg_fdi_txsb_stall_rdreg1 bridge_top_reg_fdi_txsb_stall_rdreg1; /* offset : 0x43044 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_cfg bridge_top_reg_fdi_rxsbacccom_cfg; /* offset : 0x43048 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg1 bridge_top_reg_fdi_rxsbacccom_rdreg1; /* offset : 0x4304c */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg2 bridge_top_reg_fdi_rxsbacccom_rdreg2; /* offset : 0x43050 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg3 bridge_top_reg_fdi_rxsbacccom_rdreg3; /* offset : 0x43054 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg4 bridge_top_reg_fdi_rxsbacccom_rdreg4; /* offset : 0x43058 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_cfg bridge_top_reg_fdi_rxsbaccreq_cfg; /* offset : 0x4305c */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg1 bridge_top_reg_fdi_rxsbaccreq_rdreg1; /* offset : 0x43060 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg2 bridge_top_reg_fdi_rxsbaccreq_rdreg2; /* offset : 0x43064 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg3 bridge_top_reg_fdi_rxsbaccreq_rdreg3; /* offset : 0x43068 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg4 bridge_top_reg_fdi_rxsbaccreq_rdreg4; /* offset : 0x4306c */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg5 bridge_top_reg_fdi_rxsbaccreq_rdreg5; /* offset : 0x43070 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg1 bridge_top_reg_fdi_sb_fifo_err_rdreg1; /* offset : 0x43074 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask bridge_top_reg_fdi_sb_fifo_err_mask; /* offset : 0x43078 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg2 bridge_top_reg_fdi_sb_fifo_err_rdreg2; /* offset : 0x4307c */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask2 bridge_top_reg_fdi_sb_fifo_err_mask2; /* offset : 0x43080 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config bridge_top_reg_reg_bridge_top_cxs_config; /* offset : 0x43084 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_status bridge_top_reg_reg_bridge_top_cxs_status; /* offset : 0x43088 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config2 bridge_top_reg_reg_bridge_top_cxs_config2; /* offset : 0x4308c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_periodic_timer_config bridge_top_reg_reg_bridge_top_periodic_timer_config; /* offset : 0x43090 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_gb_force_read_value bridge_top_reg_reg_bridge_top_gb_force_read_value; /* offset : 0x43094 */
		uint32_t reserved_42[26];
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_fifo_wm p0_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43100 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_fc_control p0_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43104 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_comm_count_control p0_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43108 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_count_control p0_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x4310c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43110 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43114 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43118 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4311c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43120 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43124 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43128 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4312c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1 p0_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43130 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1_mask p0_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43134 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2 p0_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43138 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2_mask p0_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4313c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_credit p0_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43140 */
		uint32_t reserved_43[47];
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_fifo_wm p0_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43200 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_fc_control p0_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43204 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_comm_count_control p0_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43208 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_count_control p0_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x4320c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43210 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43214 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43218 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4321c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43220 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43224 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43228 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4322c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1 p0_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43230 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1_mask p0_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43234 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2 p0_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43238 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2_mask p0_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4323c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_credit p0_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43240 */
		uint32_t reserved_44[47];
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_fifo_wm p0_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43300 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_fc_control p0_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43304 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_comm_count_control p0_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43308 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_count_control p0_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x4330c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43310 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43314 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43318 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4331c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43320 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43324 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43328 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4332c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1 p0_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43330 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1_mask p0_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43334 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2 p0_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43338 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2_mask p0_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4333c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_credit p0_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43340 */
		uint32_t reserved_45[47];
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_fifo_wm p0_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43400 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_fc_control p0_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43404 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_comm_count_control p0_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43408 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_count_control p0_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x4340c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43410 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43414 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43418 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4341c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43420 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43424 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43428 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4342c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1 p0_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43430 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1_mask p0_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43434 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2 p0_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43438 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2_mask p0_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4343c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_credit p0_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43440 */
		uint32_t reserved_46[47];
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_fifo_wm p0_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43500 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_fc_control p0_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43504 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_comm_count_control p0_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43508 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_count_control p0_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x4350c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43510 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43514 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43518 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4351c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43520 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43524 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43528 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4352c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1 p0_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43530 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1_mask p0_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43534 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2 p0_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43538 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2_mask p0_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4353c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_credit p0_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43540 */
		uint32_t reserved_47[47];
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_fifo_wm p1_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43600 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_fc_control p1_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43604 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_comm_count_control p1_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43608 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_count_control p1_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x4360c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43610 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43614 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43618 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4361c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43620 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43624 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43628 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4362c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1 p1_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43630 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1_mask p1_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43634 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2 p1_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43638 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2_mask p1_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4363c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_credit p1_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43640 */
		uint32_t reserved_48[47];
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_fifo_wm p1_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43700 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_fc_control p1_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43704 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_comm_count_control p1_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43708 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_count_control p1_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x4370c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43710 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43714 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43718 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4371c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43720 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43724 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43728 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4372c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1 p1_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43730 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1_mask p1_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43734 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2 p1_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43738 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2_mask p1_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4373c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_credit p1_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43740 */
		uint32_t reserved_49[47];
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_fifo_wm p1_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43800 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_fc_control p1_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43804 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_comm_count_control p1_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43808 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_count_control p1_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x4380c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43810 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43814 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43818 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4381c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43820 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43824 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43828 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4382c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1 p1_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43830 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1_mask p1_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43834 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2 p1_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43838 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2_mask p1_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4383c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_credit p1_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43840 */
		uint32_t reserved_50[47];
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_fifo_wm p1_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43900 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_fc_control p1_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43904 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_comm_count_control p1_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43908 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_count_control p1_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x4390c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43910 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43914 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43918 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4391c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43920 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43924 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43928 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4392c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1 p1_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43930 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1_mask p1_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43934 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2 p1_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43938 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2_mask p1_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4393c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_credit p1_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43940 */
		uint32_t reserved_51[47];
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_fifo_wm p1_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43a00 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_fc_control p1_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43a04 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_comm_count_control p1_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43a08 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_count_control p1_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x43a0c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43a10 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43a14 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43a18 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43a1c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43a20 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43a24 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43a28 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43a2c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1 p1_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43a30 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1_mask p1_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43a34 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2 p1_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43a38 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2_mask p1_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43a3c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_credit p1_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43a40 */
		uint32_t reserved_52[47];
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_fifo_wm p2_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43b00 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_fc_control p2_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43b04 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_comm_count_control p2_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43b08 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_count_control p2_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x43b0c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43b10 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43b14 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43b18 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43b1c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43b20 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43b24 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43b28 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43b2c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1 p2_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43b30 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1_mask p2_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43b34 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2 p2_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43b38 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2_mask p2_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43b3c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_credit p2_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43b40 */
		uint32_t reserved_53[47];
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_fifo_wm p2_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43c00 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_fc_control p2_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43c04 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_comm_count_control p2_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43c08 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_count_control p2_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x43c0c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43c10 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43c14 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43c18 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43c1c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43c20 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43c24 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43c28 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43c2c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1 p2_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43c30 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1_mask p2_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43c34 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2 p2_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43c38 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2_mask p2_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43c3c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_credit p2_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43c40 */
		uint32_t reserved_54[47];
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_fifo_wm p2_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43d00 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_fc_control p2_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43d04 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_comm_count_control p2_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43d08 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_count_control p2_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x43d0c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43d10 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43d14 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43d18 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43d1c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43d20 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43d24 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43d28 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43d2c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1 p2_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43d30 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1_mask p2_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43d34 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2 p2_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43d38 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2_mask p2_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43d3c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_credit p2_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43d40 */
		uint32_t reserved_55[47];
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_fifo_wm p2_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43e00 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_fc_control p2_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43e04 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_comm_count_control p2_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43e08 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_count_control p2_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x43e0c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43e10 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43e14 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43e18 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43e1c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43e20 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43e24 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43e28 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43e2c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1 p2_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43e30 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1_mask p2_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43e34 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2 p2_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43e38 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2_mask p2_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43e3c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_credit p2_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43e40 */
		uint32_t reserved_56[47];
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_fifo_wm p2_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43f00 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_fc_control p2_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43f04 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_comm_count_control p2_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43f08 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_count_control p2_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x43f0c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43f10 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43f14 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43f18 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43f1c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43f20 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43f24 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43f28 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43f2c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1 p2_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43f30 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1_mask p2_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43f34 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2 p2_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43f38 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2_mask p2_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43f3c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_credit p2_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43f40 */
	};
#else
	struct aw_ucie {
		uint32_t reserved_1[32768];
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr; /* offset : 0x20000 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr1 dvsec1_reg_reg_global_dvsec1_hdr1; /* offset : 0x20004 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor; /* offset : 0x20008 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cap dvsec1_reg_reg_global_dvsec1_ucie_link_cap; /* offset : 0x2000c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl; /* offset : 0x20010 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status dvsec1_reg_reg_global_dvsec1_ucie_link_status; /* offset : 0x20014 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl; /* offset : 0x20018 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_low dvsec1_reg_reg_global_dvsec1_reg_loc0_low; /* offset : 0x2001c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_high dvsec1_reg_reg_global_dvsec1_reg_loc0_high; /* offset : 0x20020 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_low dvsec1_reg_reg_global_dvsec1_reg_loc1_low; /* offset : 0x20024 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_high dvsec1_reg_reg_global_dvsec1_reg_loc1_high; /* offset : 0x20028 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_low dvsec1_reg_reg_global_dvsec1_reg_loc2_low; /* offset : 0x2002c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_high dvsec1_reg_reg_global_dvsec1_reg_loc2_high; /* offset : 0x20030 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_low dvsec1_reg_reg_global_dvsec1_reg_loc3_low; /* offset : 0x20034 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_high dvsec1_reg_reg_global_dvsec1_reg_loc3_high; /* offset : 0x20038 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low; /* offset : 0x2003c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high; /* offset : 0x20040 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low; /* offset : 0x20044 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high; /* offset : 0x20048 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats; /* offset : 0x2004c */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_req_id dvsec1_reg_reg_global_dvsec1_req_id; /* offset : 0x20050 */
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_associated_port_num dvsec1_reg_reg_global_dvsec1_associated_port_num; /* offset : 0x20054 */
		uint32_t reserved_2[1002];
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_pcie_extnd_cap_hdr dvsec2_reg_reg_glbl_dvsec2_cap_pcie_extnd_cap_hdr; /* offset : 0x21000 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr1 dvsec2_reg_reg_glbl_dvsec2_cap_hdr1; /* offset : 0x21004 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_hdr2 dvsec2_reg_reg_glbl_dvsec2_cap_hdr2; /* offset : 0x21008 */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1 dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1; /* offset : 0x2100c */
		union aw_ucie_dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2 dvsec2_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2; /* offset : 0x21010 */
		uint32_t reserved_3[4091];
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1; /* offset : 0x25000 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2; /* offset : 0x25004 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3; /* offset : 0x25008 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg4 adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg4; /* offset : 0x2500c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat; /* offset : 0x25010 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask; /* offset : 0x25014 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity; /* offset : 0x25018 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat adapter_d2d_reg_reg_adapter_d2d_corr_err_stat; /* offset : 0x2501c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask adapter_d2d_reg_reg_adapter_d2d_corr_err_mask; /* offset : 0x25020 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1 adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1; /* offset : 0x25024 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2 adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2; /* offset : 0x25028 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 adapter_d2d_reg_reg_adapter_d2d_hdr_log2; /* offset : 0x2502c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl; /* offset : 0x25030 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1; /* offset : 0x25034 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2; /* offset : 0x25038 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1; /* offset : 0x2503c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2; /* offset : 0x25040 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1; /* offset : 0x25044 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2; /* offset : 0x25048 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1; /* offset : 0x2504c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2 adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2; /* offset : 0x25050 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1; /* offset : 0x25054 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log2; /* offset : 0x25058 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1; /* offset : 0x2505c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log2; /* offset : 0x25060 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log1; /* offset : 0x25064 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log2; /* offset : 0x25068 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log1; /* offset : 0x2506c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log2; /* offset : 0x25070 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log1 adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log1; /* offset : 0x25074 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log2 adapter_d2d_reg_reg_adapter_d2d_adv_multi_prot_capability_log2; /* offset : 0x25078 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log1 adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log1; /* offset : 0x2507c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log2 adapter_d2d_reg_reg_adapter_d2d_fin_multi_prot_capability_log2; /* offset : 0x25080 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1; /* offset : 0x25084 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2 adapter_d2d_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2; /* offset : 0x25088 */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1; /* offset : 0x2508c */
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2 adapter_d2d_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2; /* offset : 0x25090 */
		uint32_t reserved_4[987];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cap phy_d2d_reg_reg_phy_d2d_phy_cap; /* offset : 0x26000 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_d2d_reg_reg_phy_d2d_phy_cntrl; /* offset : 0x26004 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_d2d_reg_reg_phy_d2d_phy_stat; /* offset : 0x26008 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_init_debug phy_d2d_reg_reg_phy_d2d_phy_init_debug; /* offset : 0x2600c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 phy_d2d_reg_reg_phy_d2d_m0_train_setup1; /* offset : 0x26010 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup1 phy_d2d_reg_reg_phy_d2d_m1_train_setup1; /* offset : 0x26014 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup1 phy_d2d_reg_reg_phy_d2d_m2_train_setup1; /* offset : 0x26018 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup1 phy_d2d_reg_reg_phy_d2d_m3_train_setup1; /* offset : 0x2601c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 phy_d2d_reg_reg_phy_d2d_m0_train_setup2; /* offset : 0x26020 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup2 phy_d2d_reg_reg_phy_d2d_m1_train_setup2; /* offset : 0x26024 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup2 phy_d2d_reg_reg_phy_d2d_m2_train_setup2; /* offset : 0x26028 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup2 phy_d2d_reg_reg_phy_d2d_m3_train_setup2; /* offset : 0x2602c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1; /* offset : 0x26030 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2; /* offset : 0x26034 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1; /* offset : 0x26038 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2; /* offset : 0x2603c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m2_train_setup3_1; /* offset : 0x26040 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m2_train_setup3_2; /* offset : 0x26044 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_1 phy_d2d_reg_reg_phy_d2d_m3_train_setup3_1; /* offset : 0x26048 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup3_2 phy_d2d_reg_reg_phy_d2d_m3_train_setup3_2; /* offset : 0x2604c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 phy_d2d_reg_reg_phy_d2d_m0_train_setup4; /* offset : 0x26050 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_train_setup4 phy_d2d_reg_reg_phy_d2d_m1_train_setup4; /* offset : 0x26054 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_train_setup4 phy_d2d_reg_reg_phy_d2d_m2_train_setup4; /* offset : 0x26058 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_train_setup4 phy_d2d_reg_reg_phy_d2d_m3_train_setup4; /* offset : 0x2605c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg1; /* offset : 0x26060 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m0_curr_lane_map_reg2; /* offset : 0x26064 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg1; /* offset : 0x26068 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m1_curr_lane_map_reg2; /* offset : 0x2606c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg1; /* offset : 0x26070 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m2_curr_lane_map_reg2; /* offset : 0x26074 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg1 phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg1; /* offset : 0x26078 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg2 phy_d2d_reg_reg_phy_d2d_m3_curr_lane_map_reg2; /* offset : 0x2607c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log0 phy_d2d_reg_reg_phy_d2d_m0_err_log0; /* offset : 0x26080 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log0 phy_d2d_reg_reg_phy_d2d_m1_err_log0; /* offset : 0x26084 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log0 phy_d2d_reg_reg_phy_d2d_m2_err_log0; /* offset : 0x26088 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log0 phy_d2d_reg_reg_phy_d2d_m3_err_log0; /* offset : 0x2608c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log1 phy_d2d_reg_reg_phy_d2d_m0_err_log1; /* offset : 0x26090 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log1 phy_d2d_reg_reg_phy_d2d_m1_err_log1; /* offset : 0x26094 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_err_log1 phy_d2d_reg_reg_phy_d2d_m2_err_log1; /* offset : 0x26098 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_err_log1 phy_d2d_reg_reg_phy_d2d_m3_err_log1; /* offset : 0x2609c */
		uint32_t reserved_5[24];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1 phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1; /* offset : 0x26100 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg2 phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg2; /* offset : 0x26104 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2 phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2; /* offset : 0x26108 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1; /* offset : 0x2610c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2; /* offset : 0x26110 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1; /* offset : 0x26114 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2; /* offset : 0x26118 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg1; /* offset : 0x2611c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m2_mb_data_repair_reg2; /* offset : 0x26120 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg1 phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg1; /* offset : 0x26124 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg2 phy_d2d_reg_reg_phy_d2d_m3_mb_data_repair_reg2; /* offset : 0x26128 */
		uint32_t reserved_6[2];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair; /* offset : 0x26134 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair; /* offset : 0x26138 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair; /* offset : 0x2613c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair phy_d2d_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair; /* offset : 0x26140 */
		uint32_t reserved_7[47];
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr; /* offset : 0x26200 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr1 phy_d2d_reg_reg_phy_d2d_dvsec_hdr1; /* offset : 0x26204 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr2 phy_d2d_reg_reg_phy_d2d_dvsec_hdr2; /* offset : 0x26208 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_uhm_status phy_d2d_reg_reg_phy_d2d_uhm_status; /* offset : 0x2620c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0; /* offset : 0x26210 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0; /* offset : 0x26214 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0; /* offset : 0x26218 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0; /* offset : 0x2621c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0; /* offset : 0x26220 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0; /* offset : 0x26224 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0; /* offset : 0x26228 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0; /* offset : 0x2622c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0; /* offset : 0x26230 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0; /* offset : 0x26234 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0; /* offset : 0x26238 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0; /* offset : 0x2623c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0; /* offset : 0x26240 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0; /* offset : 0x26244 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0; /* offset : 0x26248 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0; /* offset : 0x2624c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0; /* offset : 0x26250 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0; /* offset : 0x26254 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0; /* offset : 0x26258 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0; /* offset : 0x2625c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0; /* offset : 0x26260 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0; /* offset : 0x26264 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0; /* offset : 0x26268 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0; /* offset : 0x2626c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0; /* offset : 0x26270 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0; /* offset : 0x26274 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0; /* offset : 0x26278 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0; /* offset : 0x2627c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0; /* offset : 0x26280 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0; /* offset : 0x26284 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0; /* offset : 0x26288 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0; /* offset : 0x2628c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0; /* offset : 0x26290 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0; /* offset : 0x26294 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1; /* offset : 0x26298 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1; /* offset : 0x2629c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1; /* offset : 0x262a0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1; /* offset : 0x262a4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1; /* offset : 0x262a8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1; /* offset : 0x262ac */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1; /* offset : 0x262b0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1; /* offset : 0x262b4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1; /* offset : 0x262b8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1; /* offset : 0x262bc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1; /* offset : 0x262c0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1; /* offset : 0x262c4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1; /* offset : 0x262c8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1; /* offset : 0x262cc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1; /* offset : 0x262d0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1; /* offset : 0x262d4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1; /* offset : 0x262d8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1; /* offset : 0x262dc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1; /* offset : 0x262e0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1; /* offset : 0x262e4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1; /* offset : 0x262e8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1; /* offset : 0x262ec */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1; /* offset : 0x262f0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1; /* offset : 0x262f4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1; /* offset : 0x262f8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1; /* offset : 0x262fc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1; /* offset : 0x26300 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1; /* offset : 0x26304 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1; /* offset : 0x26308 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1; /* offset : 0x2630c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1; /* offset : 0x26310 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1; /* offset : 0x26314 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1; /* offset : 0x26318 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1; /* offset : 0x2631c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2; /* offset : 0x26320 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2; /* offset : 0x26324 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2; /* offset : 0x26328 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2; /* offset : 0x2632c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2; /* offset : 0x26330 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2; /* offset : 0x26334 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2; /* offset : 0x26338 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2; /* offset : 0x2633c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2; /* offset : 0x26340 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2; /* offset : 0x26344 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2; /* offset : 0x26348 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2; /* offset : 0x2634c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2; /* offset : 0x26350 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2; /* offset : 0x26354 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2; /* offset : 0x26358 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2; /* offset : 0x2635c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2; /* offset : 0x26360 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2; /* offset : 0x26364 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2; /* offset : 0x26368 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2; /* offset : 0x2636c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2; /* offset : 0x26370 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2; /* offset : 0x26374 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2; /* offset : 0x26378 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2; /* offset : 0x2637c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2; /* offset : 0x26380 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2; /* offset : 0x26384 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2; /* offset : 0x26388 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2; /* offset : 0x2638c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2; /* offset : 0x26390 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2; /* offset : 0x26394 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2; /* offset : 0x26398 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2; /* offset : 0x2639c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2; /* offset : 0x263a0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2; /* offset : 0x263a4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3; /* offset : 0x263a8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3; /* offset : 0x263ac */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3; /* offset : 0x263b0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3; /* offset : 0x263b4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3; /* offset : 0x263b8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3; /* offset : 0x263bc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3; /* offset : 0x263c0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3; /* offset : 0x263c4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3; /* offset : 0x263c8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3; /* offset : 0x263cc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3; /* offset : 0x263d0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3; /* offset : 0x263d4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3; /* offset : 0x263d8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3; /* offset : 0x263dc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3; /* offset : 0x263e0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3; /* offset : 0x263e4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3; /* offset : 0x263e8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3; /* offset : 0x263ec */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3; /* offset : 0x263f0 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3; /* offset : 0x263f4 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3; /* offset : 0x263f8 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3; /* offset : 0x263fc */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3; /* offset : 0x26400 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3; /* offset : 0x26404 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3; /* offset : 0x26408 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3; /* offset : 0x2640c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3; /* offset : 0x26410 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3; /* offset : 0x26414 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3; /* offset : 0x26418 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3; /* offset : 0x2641c */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3; /* offset : 0x26420 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3; /* offset : 0x26424 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3; /* offset : 0x26428 */
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3 phy_d2d_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3; /* offset : 0x2642c */
		uint32_t reserved_8[756];
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1; /* offset : 0x27000 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2; /* offset : 0x27004 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3; /* offset : 0x27008 */
		union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr4 test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr4; /* offset : 0x2700c */
		union aw_ucie_test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset; /* offset : 0x27010 */
		union aw_ucie_test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset; /* offset : 0x27014 */
		uint32_t reserved_9[2];
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl; /* offset : 0x27020 */
		uint32_t reserved_10;
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1; /* offset : 0x27028 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2 adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2; /* offset : 0x2702c */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts adapter_test_comp_reg_reg_adapter_tstcmp_test_sts; /* offset : 0x27030 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0; /* offset : 0x27034 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack1 adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack1; /* offset : 0x27038 */
		uint32_t reserved_11;
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1 adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1; /* offset : 0x27040 */
		union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2 adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2; /* offset : 0x27044 */
		uint32_t reserved_12[1006];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1; /* offset : 0x28000 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_2; /* offset : 0x28004 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2; /* offset : 0x28008 */
		uint32_t reserved_13;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1; /* offset : 0x28010 */
		uint32_t reserved_14;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_1; /* offset : 0x28018 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat2_2; /* offset : 0x2801c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_1; /* offset : 0x28020 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m0_compl_stat3_2; /* offset : 0x28024 */
		uint32_t reserved_15[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1; /* offset : 0x28400 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_2; /* offset : 0x28404 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2; /* offset : 0x28408 */
		uint32_t reserved_16;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1; /* offset : 0x28410 */
		uint32_t reserved_17;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_1; /* offset : 0x28418 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat2_2; /* offset : 0x2841c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_1; /* offset : 0x28420 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat3_2; /* offset : 0x28424 */
		uint32_t reserved_18[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_1; /* offset : 0x28800 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl1_2; /* offset : 0x28804 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_ctrl2; /* offset : 0x28808 */
		uint32_t reserved_19;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat1; /* offset : 0x28810 */
		uint32_t reserved_20;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_1; /* offset : 0x28818 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat2_2; /* offset : 0x2881c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_1; /* offset : 0x28820 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m2_compl_stat3_2; /* offset : 0x28824 */
		uint32_t reserved_21[246];
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_1; /* offset : 0x28c00 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl1_2; /* offset : 0x28c04 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_ctrl2; /* offset : 0x28c08 */
		uint32_t reserved_22;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat1; /* offset : 0x28c10 */
		uint32_t reserved_23;
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_1; /* offset : 0x28c18 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat2_2; /* offset : 0x28c1c */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_1 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_1; /* offset : 0x28c20 */
		union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_2 phy_test_comp_reg_reg_phy_tstcmp_m3_compl_stat3_2; /* offset : 0x28c24 */
		uint32_t reserved_24[246];
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1; /* offset : 0x29000 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2; /* offset : 0x29004 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3; /* offset : 0x29008 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr4 adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr4; /* offset : 0x2900c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_config adapter_imp_spec_rdi_reg_reg_adapter_impsp_config; /* offset : 0x29010 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_fifo_wm adapter_imp_spec_rdi_reg_reg_adapter_fifo_wm; /* offset : 0x29014 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg1 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg1; /* offset : 0x29018 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg2 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg2; /* offset : 0x2901c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg3 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg3; /* offset : 0x29020 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg4 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg4; /* offset : 0x29024 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg5 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg5; /* offset : 0x29028 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg6 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg6; /* offset : 0x2902c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg7 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_cfg7; /* offset : 0x29030 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_txsb_stall_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_txsb_stall_rdreg1; /* offset : 0x29034 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_cfg; /* offset : 0x29038 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg1; /* offset : 0x2903c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg2; /* offset : 0x29040 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg3; /* offset : 0x29044 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbacccom_rdreg4; /* offset : 0x29048 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_cfg; /* offset : 0x2904c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg1; /* offset : 0x29050 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg2; /* offset : 0x29054 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg3; /* offset : 0x29058 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg4; /* offset : 0x2905c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbaccreq_rdreg5; /* offset : 0x29060 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_cfg; /* offset : 0x29064 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg1; /* offset : 0x29068 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg2; /* offset : 0x2906c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg3; /* offset : 0x29070 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg4; /* offset : 0x29074 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbmsg_rdreg5; /* offset : 0x29078 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_cfg adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_cfg; /* offset : 0x2907c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg1; /* offset : 0x29080 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg2; /* offset : 0x29084 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg3 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg3; /* offset : 0x29088 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg4 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg4; /* offset : 0x2908c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg5 adapter_imp_spec_rdi_reg_adapter_rdi_rxsbvmsg_rdreg5; /* offset : 0x29090 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg1 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg1; /* offset : 0x29094 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask; /* offset : 0x29098 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg2 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_rdreg2; /* offset : 0x2909c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask2 adapter_imp_spec_rdi_reg_adapter_rdi_sb_fifo_err_mask2; /* offset : 0x290a0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_lp_config adapter_imp_spec_rdi_reg_adapter_rdi_lp_config; /* offset : 0x290a4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_rdreg6 adapter_imp_spec_rdi_reg_adapter_rdi_pl_rdreg6; /* offset : 0x290a8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1 adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1; /* offset : 0x290ac */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1_mask adapter_imp_spec_rdi_reg_adapter_rdi_pl_int1_mask; /* offset : 0x290b0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2 adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2; /* offset : 0x290b4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2_mask adapter_imp_spec_rdi_reg_adapter_rdi_pl_int2_mask; /* offset : 0x290b8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_int2 adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_int2; /* offset : 0x290bc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_int2_mask adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_int2_mask; /* offset : 0x290c0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_stat_int2 adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_stat_int2; /* offset : 0x290c4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_int2_mask adapter_imp_spec_rdi_reg_reg_adapter_d2d_corr_err_int2_mask; /* offset : 0x290c8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg1_w; /* offset : 0x290cc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg2_w; /* offset : 0x290d0 */
		uint32_t reserved_25;
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg3_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_ucie_blk_hdr_reg3_w; /* offset : 0x290d8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_uncorr_err_stat_w; /* offset : 0x290dc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_1_w; /* offset : 0x290e0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_hdr_log1_2_w; /* offset : 0x290e4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1_w; /* offset : 0x290e8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2_w; /* offset : 0x290ec */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1_w; /* offset : 0x290f0 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2_w; /* offset : 0x290f4 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1_w; /* offset : 0x290f8 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2_w; /* offset : 0x290fc */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log1_w; /* offset : 0x29100 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_adapter_capability_log2_w; /* offset : 0x29104 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log1_w; /* offset : 0x29108 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_adapter_capability_log2_w; /* offset : 0x2910c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log1_w; /* offset : 0x29110 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log2_w; /* offset : 0x29114 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log1_w; /* offset : 0x29118 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log2_w; /* offset : 0x2911c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log1_w; /* offset : 0x29120 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_multi_prot_capability_log2_w; /* offset : 0x29124 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log1_w; /* offset : 0x29128 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_multi_prot_capability_log2_w; /* offset : 0x2912c */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_1_w; /* offset : 0x29130 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_adv_cxl_capability_log_stack1_2_w; /* offset : 0x29134 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_1_w; /* offset : 0x29138 */
		union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2_w adapter_imp_spec_rdi_reg_reg_adapter_d2d_fin_cxl_capability_log_stack1_2_w; /* offset : 0x2913c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg1 adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg1; /* offset : 0x29140 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg2 adapter_imp_spec_rdi_reg_adapter_tx_retry_cfg2; /* offset : 0x29144 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg1 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg1; /* offset : 0x29148 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg2 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg2; /* offset : 0x2914c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg3 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg3; /* offset : 0x29150 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg4 adapter_imp_spec_rdi_reg_adapter_rx_retry_cfg4; /* offset : 0x29154 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_static_counter_cfg adapter_imp_spec_rdi_reg_adapter_static_counter_cfg; /* offset : 0x29158 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0 adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0; /* offset : 0x2915c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1 adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1; /* offset : 0x29160 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_parity_err_count_threshold_reg adapter_imp_spec_rdi_reg_adapter_parity_err_count_threshold_reg; /* offset : 0x29164 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_count_threshold_reg adapter_imp_spec_rdi_reg_adapter_crc_err_count_threshold_reg; /* offset : 0x29168 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config1_reg adapter_imp_spec_rdi_reg_adapter_timeout_count_config1_reg; /* offset : 0x2916c */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_timeout_count_config2_reg adapter_imp_spec_rdi_reg_adapter_timeout_count_config2_reg; /* offset : 0x29170 */
		union aw_ucie_adapter_imp_spec_rdi_reg_adapter_impsp_sts1_reg adapter_imp_spec_rdi_reg_adapter_impsp_sts1_reg; /* offset : 0x29174 */
		uint32_t reserved_26[418];
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg1 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg1; /* offset : 0x29800 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg2 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg2; /* offset : 0x29804 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg3 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg3; /* offset : 0x29808 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg4 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg4; /* offset : 0x2980c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg5 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_cfg5; /* offset : 0x29810 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_txsb_stall_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_txsb_stall_rdreg1; /* offset : 0x29814 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_cfg adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_cfg; /* offset : 0x29818 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg1; /* offset : 0x2981c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg2; /* offset : 0x29820 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg3 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg3; /* offset : 0x29824 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg4 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbacccom_rdreg4; /* offset : 0x29828 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_cfg adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_cfg; /* offset : 0x2982c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg1; /* offset : 0x29830 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg2; /* offset : 0x29834 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg3 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg3; /* offset : 0x29838 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg4 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg4; /* offset : 0x2983c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg5 adapter_imp_spec_fdi_reg_adapter_fdi_rxsbaccreq_rdreg5; /* offset : 0x29840 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg1 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg1; /* offset : 0x29844 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask; /* offset : 0x29848 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg2 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_rdreg2; /* offset : 0x2984c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask2 adapter_imp_spec_fdi_reg_adapter_fdi_sb_fifo_err_mask2; /* offset : 0x29850 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg1 adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg1; /* offset : 0x29854 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg2 adapter_imp_spec_fdi_reg_adapter_fdi_pl_cfg2; /* offset : 0x29858 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_rdreg adapter_imp_spec_fdi_reg_adapter_fdi_lp_rdreg; /* offset : 0x2985c */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_reg; /* offset : 0x29860 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_mask_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int1_mask_reg; /* offset : 0x29864 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_reg; /* offset : 0x29868 */
		union aw_ucie_adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_mask_reg adapter_imp_spec_fdi_reg_adapter_fdi_lp_int2_mask_reg; /* offset : 0x2986c */
		uint32_t reserved_27[484];
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1; /* offset : 0x2a000 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2; /* offset : 0x2a004 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3; /* offset : 0x2a008 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4 phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4; /* offset : 0x2a00c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg1 phy_imp_spec_reg_phy_rdi_txsb_cfg1; /* offset : 0x2a010 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg2 phy_imp_spec_reg_phy_rdi_txsb_cfg2; /* offset : 0x2a014 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg3 phy_imp_spec_reg_phy_rdi_txsb_cfg3; /* offset : 0x2a018 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg4 phy_imp_spec_reg_phy_rdi_txsb_cfg4; /* offset : 0x2a01c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg5 phy_imp_spec_reg_phy_rdi_txsb_cfg5; /* offset : 0x2a020 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg6 phy_imp_spec_reg_phy_rdi_txsb_cfg6; /* offset : 0x2a024 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_cfg7 phy_imp_spec_reg_phy_rdi_txsb_cfg7; /* offset : 0x2a028 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_txsb_stall_rdreg1 phy_imp_spec_reg_phy_rdi_txsb_stall_rdreg1; /* offset : 0x2a02c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_cfg phy_imp_spec_reg_phy_rdi_rxsbacccom_cfg; /* offset : 0x2a030 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg1; /* offset : 0x2a034 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg2; /* offset : 0x2a038 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg3; /* offset : 0x2a03c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbacccom_rdreg4; /* offset : 0x2a040 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_cfg phy_imp_spec_reg_phy_rdi_rxsbaccreq_cfg; /* offset : 0x2a044 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg1; /* offset : 0x2a048 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg2; /* offset : 0x2a04c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg3; /* offset : 0x2a050 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg4; /* offset : 0x2a054 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbaccreq_rdreg5; /* offset : 0x2a058 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_cfg phy_imp_spec_reg_phy_rdi_rxsbmsg_cfg; /* offset : 0x2a05c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg1; /* offset : 0x2a060 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg2; /* offset : 0x2a064 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg3; /* offset : 0x2a068 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg4; /* offset : 0x2a06c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbmsg_rdreg5; /* offset : 0x2a070 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_cfg phy_imp_spec_reg_phy_rdi_rxsbvmsg_cfg; /* offset : 0x2a074 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg1 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg1; /* offset : 0x2a078 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg2 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg2; /* offset : 0x2a07c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg3 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg3; /* offset : 0x2a080 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg4 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg4; /* offset : 0x2a084 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg5 phy_imp_spec_reg_phy_rdi_rxsbvmsg_rdreg5; /* offset : 0x2a088 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1 phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1; /* offset : 0x2a08c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1_mask phy_imp_spec_reg_phy_rdi_sb_int1_rdreg1_mask; /* offset : 0x2a090 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1 phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1; /* offset : 0x2a094 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1_mask phy_imp_spec_reg_phy_rdi_sb_int2_rdreg1_mask; /* offset : 0x2a098 */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_lp_rdreg phy_imp_spec_reg_phy_rdi_lp_rdreg; /* offset : 0x2a09c */
		union aw_ucie_phy_imp_spec_reg_phy_rdi_pl_cfg1 phy_imp_spec_reg_phy_rdi_pl_cfg1; /* offset : 0x2a0a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m0_err_log0_w; /* offset : 0x2a0a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m1_err_log0_w; /* offset : 0x2a0a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m2_err_log0_w; /* offset : 0x2a0ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log0_w phy_imp_spec_reg_reg_phy_d2d_m3_err_log0_w; /* offset : 0x2a0b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m0_err_log1_w; /* offset : 0x2a0b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m1_err_log1_w; /* offset : 0x2a0b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m2_err_log1_w; /* offset : 0x2a0bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_err_log1_w phy_imp_spec_reg_reg_phy_d2d_m3_err_log1_w; /* offset : 0x2a0c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1_w phy_imp_spec_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1_w; /* offset : 0x2a0c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg1_w; /* offset : 0x2a0c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m0_mb_data_repair_reg2_w; /* offset : 0x2a0cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg1_w; /* offset : 0x2a0d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m1_mb_data_repair_reg2_w; /* offset : 0x2a0d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg1_w; /* offset : 0x2a0d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m2_mb_data_repair_reg2_w; /* offset : 0x2a0dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg1_w phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg1_w; /* offset : 0x2a0e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg2_w phy_imp_spec_reg_reg_phy_d2d_m3_mb_data_repair_reg2_w; /* offset : 0x2a0e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m0_clk_trk_vld_sb_repair_w; /* offset : 0x2a0e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m1_clk_trk_vld_sb_repair_w; /* offset : 0x2a0ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m2_clk_trk_vld_sb_repair_w; /* offset : 0x2a0f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair_w phy_imp_spec_reg_reg_phy_d2d_m3_clk_trk_vld_sb_repair_w; /* offset : 0x2a0f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_pcie_extnd_cap_hdr_w phy_imp_spec_reg_reg_phy_d2d_pcie_extnd_cap_hdr_w; /* offset : 0x2a0f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr1_w phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr1_w; /* offset : 0x2a0fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr2_w phy_imp_spec_reg_reg_phy_d2d_dvsec_hdr2_w; /* offset : 0x2a100 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_uhm_status_w phy_imp_spec_reg_reg_phy_d2d_uhm_status_w; /* offset : 0x2a104 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0_w; /* offset : 0x2a108 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m0_w; /* offset : 0x2a10c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m0_w; /* offset : 0x2a110 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m0_w; /* offset : 0x2a114 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m0_w; /* offset : 0x2a118 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m0_w; /* offset : 0x2a11c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m0_w; /* offset : 0x2a120 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m0_w; /* offset : 0x2a124 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m0_w; /* offset : 0x2a128 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m0_w; /* offset : 0x2a12c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m0_w; /* offset : 0x2a130 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m0_w; /* offset : 0x2a134 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m0_w; /* offset : 0x2a138 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m0_w; /* offset : 0x2a13c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m0_w; /* offset : 0x2a140 */
		uint32_t reserved_28[2];
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m0_w; /* offset : 0x2a14c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m0_w; /* offset : 0x2a150 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m0_w; /* offset : 0x2a154 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m0_w; /* offset : 0x2a158 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m0_w; /* offset : 0x2a15c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m0_w; /* offset : 0x2a160 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m0_w; /* offset : 0x2a164 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m0_w; /* offset : 0x2a168 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m0_w; /* offset : 0x2a16c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m0_w; /* offset : 0x2a170 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m0_w; /* offset : 0x2a174 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m0_w; /* offset : 0x2a178 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m0_w; /* offset : 0x2a17c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m0_w; /* offset : 0x2a180 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m0_w; /* offset : 0x2a184 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m0_w; /* offset : 0x2a188 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m0_w; /* offset : 0x2a18c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m0_w; /* offset : 0x2a190 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m0_w; /* offset : 0x2a194 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1_w; /* offset : 0x2a198 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m1_w; /* offset : 0x2a19c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m1_w; /* offset : 0x2a1a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m1_w; /* offset : 0x2a1a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m1_w; /* offset : 0x2a1a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m1_w; /* offset : 0x2a1ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m1_w; /* offset : 0x2a1b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m1_w; /* offset : 0x2a1b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m1_w; /* offset : 0x2a1b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m1_w; /* offset : 0x2a1bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m1_w; /* offset : 0x2a1c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m1_w; /* offset : 0x2a1c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m1_w; /* offset : 0x2a1c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m1_w; /* offset : 0x2a1cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m1_w; /* offset : 0x2a1d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m1_w; /* offset : 0x2a1d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m1_w; /* offset : 0x2a1d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m1_w; /* offset : 0x2a1dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m1_w; /* offset : 0x2a1e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m1_w; /* offset : 0x2a1e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m1_w; /* offset : 0x2a1e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m1_w; /* offset : 0x2a1ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m1_w; /* offset : 0x2a1f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m1_w; /* offset : 0x2a1f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m1_w; /* offset : 0x2a1f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m1_w; /* offset : 0x2a1fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m1_w; /* offset : 0x2a200 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m1_w; /* offset : 0x2a204 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m1_w; /* offset : 0x2a208 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m1_w; /* offset : 0x2a20c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m1_w; /* offset : 0x2a210 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m1_w; /* offset : 0x2a214 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m1_w; /* offset : 0x2a218 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m1_w; /* offset : 0x2a21c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m2_w; /* offset : 0x2a220 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m2_w; /* offset : 0x2a224 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m2_w; /* offset : 0x2a228 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m2_w; /* offset : 0x2a22c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m2_w; /* offset : 0x2a230 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m2_w; /* offset : 0x2a234 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m2_w; /* offset : 0x2a238 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m2_w; /* offset : 0x2a23c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m2_w; /* offset : 0x2a240 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m2_w; /* offset : 0x2a244 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m2_w; /* offset : 0x2a248 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m2_w; /* offset : 0x2a24c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m2_w; /* offset : 0x2a250 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m2_w; /* offset : 0x2a254 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m2_w; /* offset : 0x2a258 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m2_w; /* offset : 0x2a25c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m2_w; /* offset : 0x2a260 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m2_w; /* offset : 0x2a264 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m2_w; /* offset : 0x2a268 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m2_w; /* offset : 0x2a26c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m2_w; /* offset : 0x2a270 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m2_w; /* offset : 0x2a274 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m2_w; /* offset : 0x2a278 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m2_w; /* offset : 0x2a27c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m2_w; /* offset : 0x2a280 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m2_w; /* offset : 0x2a284 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m2_w; /* offset : 0x2a288 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m2_w; /* offset : 0x2a28c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m2_w; /* offset : 0x2a290 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m2_w; /* offset : 0x2a294 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m2_w; /* offset : 0x2a298 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m2_w; /* offset : 0x2a29c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m2_w; /* offset : 0x2a2a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m2_w; /* offset : 0x2a2a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln0_ln1_m3_w; /* offset : 0x2a2a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln2_ln3_m3_w; /* offset : 0x2a2ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln4_ln5_m3_w; /* offset : 0x2a2b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln6_ln7_m3_w; /* offset : 0x2a2b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln8_ln9_m3_w; /* offset : 0x2a2b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln10_ln11_m3_w; /* offset : 0x2a2bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln12_ln13_m3_w; /* offset : 0x2a2c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln14_ln15_m3_w; /* offset : 0x2a2c4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln16_ln17_m3_w; /* offset : 0x2a2c8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln18_ln19_m3_w; /* offset : 0x2a2cc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln20_ln21_m3_w; /* offset : 0x2a2d0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln22_ln23_m3_w; /* offset : 0x2a2d4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln24_ln25_m3_w; /* offset : 0x2a2d8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln26_ln27_m3_w; /* offset : 0x2a2dc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln28_ln29_m3_w; /* offset : 0x2a2e0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln30_ln31_m3_w; /* offset : 0x2a2e4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln32_ln33_m3_w; /* offset : 0x2a2e8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln34_ln35_m3_w; /* offset : 0x2a2ec */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln36_ln37_m3_w; /* offset : 0x2a2f0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln38_ln39_m3_w; /* offset : 0x2a2f4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln40_ln41_m3_w; /* offset : 0x2a2f8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln42_ln43_m3_w; /* offset : 0x2a2fc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln44_ln45_m3_w; /* offset : 0x2a300 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln46_ln47_m3_w; /* offset : 0x2a304 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln48_ln49_m3_w; /* offset : 0x2a308 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln50_ln51_m3_w; /* offset : 0x2a30c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln52_ln53_m3_w; /* offset : 0x2a310 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln54_ln55_m3_w; /* offset : 0x2a314 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln56_ln57_m3_w; /* offset : 0x2a318 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln58_ln59_m3_w; /* offset : 0x2a31c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln60_ln61_m3_w; /* offset : 0x2a320 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln62_ln63_m3_w; /* offset : 0x2a324 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln64_ln65_m3_w; /* offset : 0x2a328 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3_w phy_imp_spec_reg_reg_phy_d2d_eml_emr_ln66_ln67_m3_w; /* offset : 0x2a32c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_status1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_status1_w; /* offset : 0x2a330 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_1_w; /* offset : 0x2a334 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat2_2_w; /* offset : 0x2a338 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_1_w; /* offset : 0x2a33c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_stat3_2_w; /* offset : 0x2a340 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat1_w; /* offset : 0x2a344 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_1_w; /* offset : 0x2a348 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat2_2_w; /* offset : 0x2a34c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_1_w; /* offset : 0x2a350 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_stat3_2_w; /* offset : 0x2a354 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat1_w; /* offset : 0x2a358 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_1_w; /* offset : 0x2a35c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat2_2_w; /* offset : 0x2a360 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_1_w; /* offset : 0x2a364 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_stat3_2_w; /* offset : 0x2a368 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat1_w; /* offset : 0x2a36c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_1_w; /* offset : 0x2a370 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat2_2_w; /* offset : 0x2a374 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_1_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_1_w; /* offset : 0x2a378 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_stat3_2_w; /* offset : 0x2a37c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1_w; /* offset : 0x2a380 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2_w; /* offset : 0x2a384 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3_w; /* offset : 0x2a388 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4_w phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr4_w; /* offset : 0x2a38c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_cap_w phy_imp_spec_reg_reg_phy_d2d_phy_cap_w; /* offset : 0x2a390 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_d2d_phy_stat_w phy_imp_spec_reg_reg_phy_d2d_phy_stat_w; /* offset : 0x2a394 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m0_compl_ctrl1_2_w; /* offset : 0x2a398 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m1_compl_ctrl1_2_w; /* offset : 0x2a39c */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m2_compl_ctrl1_2_w; /* offset : 0x2a3a0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_ctrl1_2_w phy_imp_spec_reg_reg_phy_tstcmp_m3_compl_ctrl1_2_w; /* offset : 0x2a3a4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_tx_mmpl_cfg phy_imp_spec_reg_reg_phy_tx_mmpl_cfg; /* offset : 0x2a3a8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rx_mmpl_cfg phy_imp_spec_reg_reg_phy_rx_mmpl_cfg; /* offset : 0x2a3ac */
		union aw_ucie_phy_imp_spec_reg_reg_phy_mmpl_sts phy_imp_spec_reg_reg_phy_mmpl_sts; /* offset : 0x2a3b0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_rst_cfg phy_imp_spec_reg_reg_phy_rdi_rst_cfg; /* offset : 0x2a3b4 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1 phy_imp_spec_reg_reg_phy_rdi_lp_int1; /* offset : 0x2a3b8 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int1_mask phy_imp_spec_reg_reg_phy_rdi_lp_int1_mask; /* offset : 0x2a3bc */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2 phy_imp_spec_reg_reg_phy_rdi_lp_int2; /* offset : 0x2a3c0 */
		union aw_ucie_phy_imp_spec_reg_reg_phy_rdi_lp_int2_mask phy_imp_spec_reg_reg_phy_rdi_lp_int2_mask; /* offset : 0x2a3c4 */
		union aw_ucie_phy_imp_spec_reg_spare_in_ctrl phy_imp_spec_reg_spare_in_ctrl; /* offset : 0x2a3c8 */
		union aw_ucie_phy_imp_spec_reg_spare_out_ctrl phy_imp_spec_reg_spare_out_ctrl; /* offset : 0x2a3cc */
		uint32_t reserved_29[3852];
		union aw_ucie_global_reg_cmn_mcu_ctrl global_reg_cmn_mcu_ctrl; /* offset : 0x2e000 */
		union aw_ucie_global_reg_cmn_mcu_hart_id global_reg_cmn_mcu_hart_id; /* offset : 0x2e004 */
		union aw_ucie_global_reg_cmn_mcu_boot_addr global_reg_cmn_mcu_boot_addr; /* offset : 0x2e008 */
		union aw_ucie_global_reg_cmn_mcu_device_addr global_reg_cmn_mcu_device_addr; /* offset : 0x2e00c */
		union aw_ucie_global_reg_cmn_mcu_dmem global_reg_cmn_mcu_dmem; /* offset : 0x2e010 */
		union aw_ucie_global_reg_cmn_mcu_irq_ctrl1 global_reg_cmn_mcu_irq_ctrl1; /* offset : 0x2e014 */
		union aw_ucie_global_reg_cmn_mcu_irq_ctrl2 global_reg_cmn_mcu_irq_ctrl2; /* offset : 0x2e018 */
		union aw_ucie_global_reg_cmn_mcu_irq global_reg_cmn_mcu_irq; /* offset : 0x2e01c */
		union aw_ucie_global_reg_cmn_mcu_crash_dump3 global_reg_cmn_mcu_crash_dump3; /* offset : 0x2e020 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump2 global_reg_cmn_mcu_crash_dump2; /* offset : 0x2e024 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump1 global_reg_cmn_mcu_crash_dump1; /* offset : 0x2e028 */
		union aw_ucie_global_reg_cmn_mcu_crash_dump0 global_reg_cmn_mcu_crash_dump0; /* offset : 0x2e02c */
		union aw_ucie_global_reg_cmn_mcu_stats global_reg_cmn_mcu_stats; /* offset : 0x2e030 */
		union aw_ucie_global_reg_sram_cfg_rd_data global_reg_sram_cfg_rd_data; /* offset : 0x2e034 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg1 global_reg_cmn_mcu_scratch_reg1; /* offset : 0x2e038 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg2 global_reg_cmn_mcu_scratch_reg2; /* offset : 0x2e03c */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg3 global_reg_cmn_mcu_scratch_reg3; /* offset : 0x2e040 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg4 global_reg_cmn_mcu_scratch_reg4; /* offset : 0x2e044 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg5 global_reg_cmn_mcu_scratch_reg5; /* offset : 0x2e048 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg6 global_reg_cmn_mcu_scratch_reg6; /* offset : 0x2e04c */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg7 global_reg_cmn_mcu_scratch_reg7; /* offset : 0x2e050 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg8 global_reg_cmn_mcu_scratch_reg8; /* offset : 0x2e054 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg9 global_reg_cmn_mcu_scratch_reg9; /* offset : 0x2e058 */
		union aw_ucie_global_reg_cmn_mcu_scratch_reg10 global_reg_cmn_mcu_scratch_reg10; /* offset : 0x2e05c */
		union aw_ucie_global_reg_reg_global_cmn_cfg1 global_reg_reg_global_cmn_cfg1; /* offset : 0x2e060 */
		union aw_ucie_global_reg_reg_global_intr1_summary global_reg_reg_global_intr1_summary; /* offset : 0x2e064 */
		union aw_ucie_global_reg_reg_global_intr1_summary_mask global_reg_reg_global_intr1_summary_mask; /* offset : 0x2e068 */
		union aw_ucie_global_reg_reg_global_intr2_summary global_reg_reg_global_intr2_summary; /* offset : 0x2e06c */
		union aw_ucie_global_reg_reg_global_intr2_summary_mask global_reg_reg_global_intr2_summary_mask; /* offset : 0x2e070 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_pcie_extnd_cap_hdr_w global_reg_reg_glbl_dvsec1_pcie_extnd_cap_hdr_w; /* offset : 0x2e074 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_hdr1_w global_reg_reg_glbl_dvsec1_hdr1_w; /* offset : 0x2e078 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_hdr2_and_cap_descriptor_w global_reg_reg_glbl_dvsec1_hdr2_and_cap_descriptor_w; /* offset : 0x2e07c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_ucie_link_cap_and_status_w global_reg_reg_glbl_dvsec1_ucie_link_cap_and_status_w; /* offset : 0x2e080 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_link_sts_evnt_err_nf_ctrl_loc0_w global_reg_reg_glbl_dvsec1_link_sts_evnt_err_nf_ctrl_loc0_w; /* offset : 0x2e084 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_low_w global_reg_reg_glbl_dvsec1_reg_loc0_low_w; /* offset : 0x2e088 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc0_high_w global_reg_reg_glbl_dvsec1_reg_loc0_high_w; /* offset : 0x2e08c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_low_w global_reg_reg_glbl_dvsec1_reg_loc1_low_w; /* offset : 0x2e090 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc1_high_w global_reg_reg_glbl_dvsec1_reg_loc1_high_w; /* offset : 0x2e094 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_low_w global_reg_reg_glbl_dvsec1_reg_loc2_low_w; /* offset : 0x2e098 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc2_high_w global_reg_reg_glbl_dvsec1_reg_loc2_high_w; /* offset : 0x2e09c */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_low_w global_reg_reg_glbl_dvsec1_reg_loc3_low_w; /* offset : 0x2e0a0 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_reg_loc3_high_w global_reg_reg_glbl_dvsec1_reg_loc3_high_w; /* offset : 0x2e0a4 */
		union aw_ucie_global_reg_reg_glbl_dvsec1_sb_mlbox_ctrl_stats_assoc_port_num_w global_reg_reg_glbl_dvsec1_sb_mlbox_ctrl_stats_assoc_port_num_w; /* offset : 0x2e0a8 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1_w global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr1_w; /* offset : 0x2e0ac */
		union aw_ucie_global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2_w global_reg_reg_glbl_dvsec2_cap_uisrb_base_addr2_w; /* offset : 0x2e0b0 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr1_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr1_w; /* offset : 0x2e0b4 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr2_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr2_w; /* offset : 0x2e0b8 */
		union aw_ucie_global_reg_reg_glbl_tstcmp_ucie_blk_hdr3_w global_reg_reg_glbl_tstcmp_ucie_blk_hdr3_w; /* offset : 0x2e0bc */
		union aw_ucie_global_reg_reg_glbl_d2d_adapter_and_phy_testcompl_reg_blk_offset_w global_reg_reg_glbl_d2d_adapter_and_phy_testcompl_reg_blk_offset_w; /* offset : 0x2e0c0 */
		union aw_ucie_global_reg_spare_out_ctrl global_reg_spare_out_ctrl; /* offset : 0x2e0c4 */
		union aw_ucie_global_reg_spare_in_ctrl global_reg_spare_in_ctrl; /* offset : 0x2e0c8 */
		union aw_ucie_global_reg_reg_glbl_apb_response_timeout global_reg_reg_glbl_apb_response_timeout; /* offset : 0x2e0cc */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int1 global_reg_reg_glbl_cmn_top_int1; /* offset : 0x2e0d0 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int2 global_reg_reg_glbl_cmn_top_int2; /* offset : 0x2e0d4 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int1_mask global_reg_reg_glbl_cmn_top_int1_mask; /* offset : 0x2e0d8 */
		union aw_ucie_global_reg_reg_glbl_cmn_top_int2_mask global_reg_reg_glbl_cmn_top_int2_mask; /* offset : 0x2e0dc */
		union aw_ucie_global_reg_reg_glbl_dvsec2_pcie_extnd_cap_hdr_w global_reg_reg_glbl_dvsec2_pcie_extnd_cap_hdr_w; /* offset : 0x2e0e0 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_hdr1_w global_reg_reg_glbl_dvsec2_hdr1_w; /* offset : 0x2e0e4 */
		union aw_ucie_global_reg_reg_glbl_dvsec2_hdr2_w global_reg_reg_glbl_dvsec2_hdr2_w; /* offset : 0x2e0e8 */
		uint32_t reserved_30[965];
		union aw_ucie_phy_cmn_reg_cmn_csr_ctrl phy_cmn_reg_cmn_csr_ctrl; /* offset : 0x2f000 */
		union aw_ucie_phy_cmn_reg_cmn_ctrl phy_cmn_reg_cmn_ctrl; /* offset : 0x2f004 */
		union aw_ucie_phy_cmn_reg_cmn_ctrl_rdreg phy_cmn_reg_cmn_ctrl_rdreg; /* offset : 0x2f008 */
		union aw_ucie_phy_cmn_reg_cmnafe_clr phy_cmn_reg_cmnafe_clr; /* offset : 0x2f00c */
		union aw_ucie_phy_cmn_reg_cmnafe_piack_rdreg phy_cmn_reg_cmnafe_piack_rdreg; /* offset : 0x2f010 */
		union aw_ucie_phy_cmn_reg_cmnafe_pictrl phy_cmn_reg_cmnafe_pictrl; /* offset : 0x2f014 */
		union aw_ucie_phy_cmn_reg_cmnafe_pireq phy_cmn_reg_cmnafe_pireq; /* offset : 0x2f018 */
		union aw_ucie_phy_cmn_reg_cmnafe_pival phy_cmn_reg_cmnafe_pival; /* offset : 0x2f01c */
		union aw_ucie_phy_cmn_reg_cmnafe_pival_rdreg phy_cmn_reg_cmnafe_pival_rdreg; /* offset : 0x2f020 */
		union aw_ucie_phy_cmn_reg_cmnafe_rdreg phy_cmn_reg_cmnafe_rdreg; /* offset : 0x2f024 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg1 phy_cmn_reg_cmnafe_reg1; /* offset : 0x2f028 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg2 phy_cmn_reg_cmnafe_reg2; /* offset : 0x2f02c */
		union aw_ucie_phy_cmn_reg_cmnafe_reg3 phy_cmn_reg_cmnafe_reg3; /* offset : 0x2f030 */
		union aw_ucie_phy_cmn_reg_cmnafe_reg4 phy_cmn_reg_cmnafe_reg4; /* offset : 0x2f034 */
		union aw_ucie_phy_cmn_reg_cmnafepd phy_cmn_reg_cmnafepd; /* offset : 0x2f038 */
		union aw_ucie_phy_cmn_reg_cmnaferst phy_cmn_reg_cmnaferst; /* offset : 0x2f03c */
		union aw_ucie_phy_cmn_reg_cmnatest phy_cmn_reg_cmnatest; /* offset : 0x2f040 */
		union aw_ucie_phy_cmn_reg_cmnatest_rdreg phy_cmn_reg_cmnatest_rdreg; /* offset : 0x2f044 */
		union aw_ucie_phy_cmn_reg_cmnclkctrl phy_cmn_reg_cmnclkctrl; /* offset : 0x2f048 */
		union aw_ucie_phy_cmn_reg_cmnpll_rdreg phy_cmn_reg_cmnpll_rdreg; /* offset : 0x2f04c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg1 phy_cmn_reg_cmnpll_reg1; /* offset : 0x2f050 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg2 phy_cmn_reg_cmnpll_reg2; /* offset : 0x2f054 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg3 phy_cmn_reg_cmnpll_reg3; /* offset : 0x2f058 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg4 phy_cmn_reg_cmnpll_reg4; /* offset : 0x2f05c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg5 phy_cmn_reg_cmnpll_reg5; /* offset : 0x2f060 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg6 phy_cmn_reg_cmnpll_reg6; /* offset : 0x2f064 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg7 phy_cmn_reg_cmnpll_reg7; /* offset : 0x2f068 */
		union aw_ucie_phy_cmn_reg_cmnpll_reg8 phy_cmn_reg_cmnpll_reg8; /* offset : 0x2f06c */
		union aw_ucie_phy_cmn_reg_cmnpll_reg9 phy_cmn_reg_cmnpll_reg9; /* offset : 0x2f070 */
		union aw_ucie_phy_cmn_reg_cmnpmon phy_cmn_reg_cmnpmon; /* offset : 0x2f074 */
		union aw_ucie_phy_cmn_reg_cmnpmon_rdreg phy_cmn_reg_cmnpmon_rdreg; /* offset : 0x2f078 */
		union aw_ucie_phy_cmn_reg_cmnrxtx_reg1 phy_cmn_reg_cmnrxtx_reg1; /* offset : 0x2f07c */
		union aw_ucie_phy_cmn_reg_cmnrxtx_reg2 phy_cmn_reg_cmnrxtx_reg2; /* offset : 0x2f080 */
		union aw_ucie_phy_cmn_reg_cmnsoc_reg1 phy_cmn_reg_cmnsoc_reg1; /* offset : 0x2f084 */
		union aw_ucie_phy_cmn_reg_cmnzqcal_rdreg phy_cmn_reg_cmnzqcal_rdreg; /* offset : 0x2f088 */
		union aw_ucie_phy_cmn_reg_cmnzqcal_reg1 phy_cmn_reg_cmnzqcal_reg1; /* offset : 0x2f08c */
		union aw_ucie_phy_cmn_reg_cmnzqcal_reg2 phy_cmn_reg_cmnzqcal_reg2; /* offset : 0x2f090 */
		union aw_ucie_phy_cmn_reg_sram_cfg phy_cmn_reg_sram_cfg; /* offset : 0x2f094 */
		uint32_t reserved_31[986];
		union aw_ucie_rx0_reg_rx_csr_ctrl rx0_reg_rx_csr_ctrl; /* offset : 0x30000 */
		union aw_ucie_rx0_reg_rx_ctrl rx0_reg_rx_ctrl; /* offset : 0x30004 */
		union aw_ucie_rx0_reg_rx_ctrl_rdreg rx0_reg_rx_ctrl_rdreg; /* offset : 0x30008 */
		union aw_ucie_rx0_reg_rxcalen rx0_reg_rxcalen; /* offset : 0x3000c */
		union aw_ucie_rx0_reg_rxclkchk_rdreg rx0_reg_rxclkchk_rdreg; /* offset : 0x30010 */
		union aw_ucie_rx0_reg_rxcmn_reg1 rx0_reg_rxcmn_reg1; /* offset : 0x30014 */
		union aw_ucie_rx0_reg_rxcmn_reg2 rx0_reg_rxcmn_reg2; /* offset : 0x30018 */
		union aw_ucie_rx0_reg_rxdatapath_reg0 rx0_reg_rxdatapath_reg0; /* offset : 0x3001c */
		union aw_ucie_rx0_reg_rxdatapath_reg1 rx0_reg_rxdatapath_reg1; /* offset : 0x30020 */
		union aw_ucie_rx0_reg_rxdatapath_reg2 rx0_reg_rxdatapath_reg2; /* offset : 0x30024 */
		union aw_ucie_rx0_reg_rxdatapath_reg3 rx0_reg_rxdatapath_reg3; /* offset : 0x30028 */
		union aw_ucie_rx0_reg_rxdatapath_reg4 rx0_reg_rxdatapath_reg4; /* offset : 0x3002c */
		union aw_ucie_rx0_reg_rxdatapath_reg5 rx0_reg_rxdatapath_reg5; /* offset : 0x30030 */
		union aw_ucie_rx0_reg_rxdatcap_rdreg1 rx0_reg_rxdatcap_rdreg1; /* offset : 0x30034 */
		union aw_ucie_rx0_reg_rxdatcap_rdreg2 rx0_reg_rxdatcap_rdreg2; /* offset : 0x30038 */
		union aw_ucie_rx0_reg_rxdatcap_reg1 rx0_reg_rxdatcap_reg1; /* offset : 0x3003c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg0 rx0_reg_rxdatchk_perlaneid_reg0; /* offset : 0x30040 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg1 rx0_reg_rxdatchk_perlaneid_reg1; /* offset : 0x30044 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg10 rx0_reg_rxdatchk_perlaneid_reg10; /* offset : 0x30048 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg11 rx0_reg_rxdatchk_perlaneid_reg11; /* offset : 0x3004c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg12 rx0_reg_rxdatchk_perlaneid_reg12; /* offset : 0x30050 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg13 rx0_reg_rxdatchk_perlaneid_reg13; /* offset : 0x30054 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg14 rx0_reg_rxdatchk_perlaneid_reg14; /* offset : 0x30058 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg15 rx0_reg_rxdatchk_perlaneid_reg15; /* offset : 0x3005c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg16 rx0_reg_rxdatchk_perlaneid_reg16; /* offset : 0x30060 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg2 rx0_reg_rxdatchk_perlaneid_reg2; /* offset : 0x30064 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg3 rx0_reg_rxdatchk_perlaneid_reg3; /* offset : 0x30068 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg4 rx0_reg_rxdatchk_perlaneid_reg4; /* offset : 0x3006c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg5 rx0_reg_rxdatchk_perlaneid_reg5; /* offset : 0x30070 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg6 rx0_reg_rxdatchk_perlaneid_reg6; /* offset : 0x30074 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg7 rx0_reg_rxdatchk_perlaneid_reg7; /* offset : 0x30078 */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg8 rx0_reg_rxdatchk_perlaneid_reg8; /* offset : 0x3007c */
		union aw_ucie_rx0_reg_rxdatchk_perlaneid_reg9 rx0_reg_rxdatchk_perlaneid_reg9; /* offset : 0x30080 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg1 rx0_reg_rxdatchk_rdreg1; /* offset : 0x30084 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg10 rx0_reg_rxdatchk_rdreg10; /* offset : 0x30088 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg11 rx0_reg_rxdatchk_rdreg11; /* offset : 0x3008c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg12 rx0_reg_rxdatchk_rdreg12; /* offset : 0x30090 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg2 rx0_reg_rxdatchk_rdreg2; /* offset : 0x30094 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg3 rx0_reg_rxdatchk_rdreg3; /* offset : 0x30098 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg4 rx0_reg_rxdatchk_rdreg4; /* offset : 0x3009c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg5 rx0_reg_rxdatchk_rdreg5; /* offset : 0x300a0 */
		union aw_ucie_rx0_reg_rxdatchk_reg1 rx0_reg_rxdatchk_reg1; /* offset : 0x300a4 */
		union aw_ucie_rx0_reg_rxdatchk_reg13 rx0_reg_rxdatchk_reg13; /* offset : 0x300a8 */
		union aw_ucie_rx0_reg_rxdatchk_reg2 rx0_reg_rxdatchk_reg2; /* offset : 0x300ac */
		union aw_ucie_rx0_reg_rxdatchk_reg3 rx0_reg_rxdatchk_reg3; /* offset : 0x300b0 */
		union aw_ucie_rx0_reg_rxdatchk_reg4 rx0_reg_rxdatchk_reg4; /* offset : 0x300b4 */
		union aw_ucie_rx0_reg_rxdatchk_reg5 rx0_reg_rxdatchk_reg5; /* offset : 0x300b8 */
		union aw_ucie_rx0_reg_rxdatchk_reg6 rx0_reg_rxdatchk_reg6; /* offset : 0x300bc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg0 rx0_reg_rxdatgen_seed_udp_reg0; /* offset : 0x300c0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg1 rx0_reg_rxdatgen_seed_udp_reg1; /* offset : 0x300c4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg10 rx0_reg_rxdatgen_seed_udp_reg10; /* offset : 0x300c8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg11 rx0_reg_rxdatgen_seed_udp_reg11; /* offset : 0x300cc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg12 rx0_reg_rxdatgen_seed_udp_reg12; /* offset : 0x300d0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg13 rx0_reg_rxdatgen_seed_udp_reg13; /* offset : 0x300d4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg14 rx0_reg_rxdatgen_seed_udp_reg14; /* offset : 0x300d8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg15 rx0_reg_rxdatgen_seed_udp_reg15; /* offset : 0x300dc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg16 rx0_reg_rxdatgen_seed_udp_reg16; /* offset : 0x300e0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg17 rx0_reg_rxdatgen_seed_udp_reg17; /* offset : 0x300e4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg18 rx0_reg_rxdatgen_seed_udp_reg18; /* offset : 0x300e8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg19 rx0_reg_rxdatgen_seed_udp_reg19; /* offset : 0x300ec */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg2 rx0_reg_rxdatgen_seed_udp_reg2; /* offset : 0x300f0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg20 rx0_reg_rxdatgen_seed_udp_reg20; /* offset : 0x300f4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg21 rx0_reg_rxdatgen_seed_udp_reg21; /* offset : 0x300f8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg22 rx0_reg_rxdatgen_seed_udp_reg22; /* offset : 0x300fc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg23 rx0_reg_rxdatgen_seed_udp_reg23; /* offset : 0x30100 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg24 rx0_reg_rxdatgen_seed_udp_reg24; /* offset : 0x30104 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg25 rx0_reg_rxdatgen_seed_udp_reg25; /* offset : 0x30108 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg26 rx0_reg_rxdatgen_seed_udp_reg26; /* offset : 0x3010c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg27 rx0_reg_rxdatgen_seed_udp_reg27; /* offset : 0x30110 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg28 rx0_reg_rxdatgen_seed_udp_reg28; /* offset : 0x30114 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg29 rx0_reg_rxdatgen_seed_udp_reg29; /* offset : 0x30118 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg3 rx0_reg_rxdatgen_seed_udp_reg3; /* offset : 0x3011c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg30 rx0_reg_rxdatgen_seed_udp_reg30; /* offset : 0x30120 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg31 rx0_reg_rxdatgen_seed_udp_reg31; /* offset : 0x30124 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg32 rx0_reg_rxdatgen_seed_udp_reg32; /* offset : 0x30128 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg33 rx0_reg_rxdatgen_seed_udp_reg33; /* offset : 0x3012c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg34 rx0_reg_rxdatgen_seed_udp_reg34; /* offset : 0x30130 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg35 rx0_reg_rxdatgen_seed_udp_reg35; /* offset : 0x30134 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg36 rx0_reg_rxdatgen_seed_udp_reg36; /* offset : 0x30138 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg37 rx0_reg_rxdatgen_seed_udp_reg37; /* offset : 0x3013c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg38 rx0_reg_rxdatgen_seed_udp_reg38; /* offset : 0x30140 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg39 rx0_reg_rxdatgen_seed_udp_reg39; /* offset : 0x30144 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg4 rx0_reg_rxdatgen_seed_udp_reg4; /* offset : 0x30148 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg40 rx0_reg_rxdatgen_seed_udp_reg40; /* offset : 0x3014c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg41 rx0_reg_rxdatgen_seed_udp_reg41; /* offset : 0x30150 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg42 rx0_reg_rxdatgen_seed_udp_reg42; /* offset : 0x30154 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg43 rx0_reg_rxdatgen_seed_udp_reg43; /* offset : 0x30158 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg44 rx0_reg_rxdatgen_seed_udp_reg44; /* offset : 0x3015c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg45 rx0_reg_rxdatgen_seed_udp_reg45; /* offset : 0x30160 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg46 rx0_reg_rxdatgen_seed_udp_reg46; /* offset : 0x30164 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg47 rx0_reg_rxdatgen_seed_udp_reg47; /* offset : 0x30168 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg48 rx0_reg_rxdatgen_seed_udp_reg48; /* offset : 0x3016c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg49 rx0_reg_rxdatgen_seed_udp_reg49; /* offset : 0x30170 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg5 rx0_reg_rxdatgen_seed_udp_reg5; /* offset : 0x30174 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg50 rx0_reg_rxdatgen_seed_udp_reg50; /* offset : 0x30178 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg51 rx0_reg_rxdatgen_seed_udp_reg51; /* offset : 0x3017c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg52 rx0_reg_rxdatgen_seed_udp_reg52; /* offset : 0x30180 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg53 rx0_reg_rxdatgen_seed_udp_reg53; /* offset : 0x30184 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg54 rx0_reg_rxdatgen_seed_udp_reg54; /* offset : 0x30188 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg55 rx0_reg_rxdatgen_seed_udp_reg55; /* offset : 0x3018c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg56 rx0_reg_rxdatgen_seed_udp_reg56; /* offset : 0x30190 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg57 rx0_reg_rxdatgen_seed_udp_reg57; /* offset : 0x30194 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg58 rx0_reg_rxdatgen_seed_udp_reg58; /* offset : 0x30198 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg59 rx0_reg_rxdatgen_seed_udp_reg59; /* offset : 0x3019c */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg6 rx0_reg_rxdatgen_seed_udp_reg6; /* offset : 0x301a0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg60 rx0_reg_rxdatgen_seed_udp_reg60; /* offset : 0x301a4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg61 rx0_reg_rxdatgen_seed_udp_reg61; /* offset : 0x301a8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg62 rx0_reg_rxdatgen_seed_udp_reg62; /* offset : 0x301ac */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg63 rx0_reg_rxdatgen_seed_udp_reg63; /* offset : 0x301b0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg64 rx0_reg_rxdatgen_seed_udp_reg64; /* offset : 0x301b4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg65 rx0_reg_rxdatgen_seed_udp_reg65; /* offset : 0x301b8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg66 rx0_reg_rxdatgen_seed_udp_reg66; /* offset : 0x301bc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg67 rx0_reg_rxdatgen_seed_udp_reg67; /* offset : 0x301c0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg68 rx0_reg_rxdatgen_seed_udp_reg68; /* offset : 0x301c4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg69 rx0_reg_rxdatgen_seed_udp_reg69; /* offset : 0x301c8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg7 rx0_reg_rxdatgen_seed_udp_reg7; /* offset : 0x301cc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg70 rx0_reg_rxdatgen_seed_udp_reg70; /* offset : 0x301d0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg71 rx0_reg_rxdatgen_seed_udp_reg71; /* offset : 0x301d4 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg72 rx0_reg_rxdatgen_seed_udp_reg72; /* offset : 0x301d8 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg73 rx0_reg_rxdatgen_seed_udp_reg73; /* offset : 0x301dc */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg8 rx0_reg_rxdatgen_seed_udp_reg8; /* offset : 0x301e0 */
		union aw_ucie_rx0_reg_rxdatgen_seed_udp_reg9 rx0_reg_rxdatgen_seed_udp_reg9; /* offset : 0x301e4 */
		union aw_ucie_rx0_reg_rxhip_clr rx0_reg_rxhip_clr; /* offset : 0x301e8 */
		union aw_ucie_rx0_reg_rxhip_piack_rdreg rx0_reg_rxhip_piack_rdreg; /* offset : 0x301ec */
		union aw_ucie_rx0_reg_rxhip_pictrl rx0_reg_rxhip_pictrl; /* offset : 0x301f0 */
		union aw_ucie_rx0_reg_rxhip_pireq rx0_reg_rxhip_pireq; /* offset : 0x301f4 */
		union aw_ucie_rx0_reg_rxhip_pival rx0_reg_rxhip_pival; /* offset : 0x301f8 */
		union aw_ucie_rx0_reg_rxhip_pival_rdreg rx0_reg_rxhip_pival_rdreg; /* offset : 0x301fc */
		union aw_ucie_rx0_reg_rxhip_rdreg1 rx0_reg_rxhip_rdreg1; /* offset : 0x30200 */
		union aw_ucie_rx0_reg_rxhipcmn_reg1 rx0_reg_rxhipcmn_reg1; /* offset : 0x30204 */
		union aw_ucie_rx0_reg_rxhipcmnio_reg1 rx0_reg_rxhipcmnio_reg1; /* offset : 0x30208 */
		union aw_ucie_rx0_reg_rxhipcmnio_reg2 rx0_reg_rxhipcmnio_reg2; /* offset : 0x3020c */
		union aw_ucie_rx0_reg_rxhipcmnio_reg3 rx0_reg_rxhipcmnio_reg3; /* offset : 0x30210 */
		union aw_ucie_rx0_reg_rxhipctrl_reg1 rx0_reg_rxhipctrl_reg1; /* offset : 0x30214 */
		union aw_ucie_rx0_reg_rxhipdqs_reg1 rx0_reg_rxhipdqs_reg1; /* offset : 0x30218 */
		union aw_ucie_rx0_reg_rxhipdqs_reg2 rx0_reg_rxhipdqs_reg2; /* offset : 0x3021c */
		union aw_ucie_rx0_reg_rxhipio_reg1 rx0_reg_rxhipio_reg1; /* offset : 0x30220 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg1 rx0_reg_rxhipiondesync_rdreg1; /* offset : 0x30224 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg2 rx0_reg_rxhipiondesync_rdreg2; /* offset : 0x30228 */
		union aw_ucie_rx0_reg_rxhipiondesync_rdreg3 rx0_reg_rxhipiondesync_rdreg3; /* offset : 0x3022c */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg1 rx0_reg_rxhipiosampler_rdreg1; /* offset : 0x30230 */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg2 rx0_reg_rxhipiosampler_rdreg2; /* offset : 0x30234 */
		union aw_ucie_rx0_reg_rxhipiosampler_rdreg3 rx0_reg_rxhipiosampler_rdreg3; /* offset : 0x30238 */
		union aw_ucie_rx0_reg_rxhipload_reg1 rx0_reg_rxhipload_reg1; /* offset : 0x3023c */
		union aw_ucie_rx0_reg_rxhipload_reg10 rx0_reg_rxhipload_reg10; /* offset : 0x30240 */
		union aw_ucie_rx0_reg_rxhipload_reg11 rx0_reg_rxhipload_reg11; /* offset : 0x30244 */
		union aw_ucie_rx0_reg_rxhipload_reg12 rx0_reg_rxhipload_reg12; /* offset : 0x30248 */
		union aw_ucie_rx0_reg_rxhipload_reg13 rx0_reg_rxhipload_reg13; /* offset : 0x3024c */
		union aw_ucie_rx0_reg_rxhipload_reg14 rx0_reg_rxhipload_reg14; /* offset : 0x30250 */
		union aw_ucie_rx0_reg_rxhipload_reg15 rx0_reg_rxhipload_reg15; /* offset : 0x30254 */
		union aw_ucie_rx0_reg_rxhipload_reg2 rx0_reg_rxhipload_reg2; /* offset : 0x30258 */
		union aw_ucie_rx0_reg_rxhipload_reg3 rx0_reg_rxhipload_reg3; /* offset : 0x3025c */
		union aw_ucie_rx0_reg_rxhipload_reg4 rx0_reg_rxhipload_reg4; /* offset : 0x30260 */
		union aw_ucie_rx0_reg_rxhipload_reg5 rx0_reg_rxhipload_reg5; /* offset : 0x30264 */
		union aw_ucie_rx0_reg_rxhipload_reg6 rx0_reg_rxhipload_reg6; /* offset : 0x30268 */
		union aw_ucie_rx0_reg_rxhipload_reg7 rx0_reg_rxhipload_reg7; /* offset : 0x3026c */
		union aw_ucie_rx0_reg_rxhipload_reg8 rx0_reg_rxhipload_reg8; /* offset : 0x30270 */
		union aw_ucie_rx0_reg_rxhipload_reg9 rx0_reg_rxhipload_reg9; /* offset : 0x30274 */
		union aw_ucie_rx0_reg_rxhipspare_rdreg1 rx0_reg_rxhipspare_rdreg1; /* offset : 0x30278 */
		union aw_ucie_rx0_reg_rxhipspare_reg1 rx0_reg_rxhipspare_reg1; /* offset : 0x3027c */
		union aw_ucie_rx0_reg_rxhipspare_reg2 rx0_reg_rxhipspare_reg2; /* offset : 0x30280 */
		union aw_ucie_rx0_reg_rxioctrl_reg1 rx0_reg_rxioctrl_reg1; /* offset : 0x30284 */
		union aw_ucie_rx0_reg_rxioctrl_reg2 rx0_reg_rxioctrl_reg2; /* offset : 0x30288 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg1 rx0_reg_rxioen_afe_ovr_reg1; /* offset : 0x3028c */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg2 rx0_reg_rxioen_afe_ovr_reg2; /* offset : 0x30290 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg3 rx0_reg_rxioen_afe_ovr_reg3; /* offset : 0x30294 */
		union aw_ucie_rx0_reg_rxioen_afe_ovr_reg4 rx0_reg_rxioen_afe_ovr_reg4; /* offset : 0x30298 */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg1 rx0_reg_rxioen_data_ovr_reg1; /* offset : 0x3029c */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg2 rx0_reg_rxioen_data_ovr_reg2; /* offset : 0x302a0 */
		union aw_ucie_rx0_reg_rxioen_data_ovr_reg3 rx0_reg_rxioen_data_ovr_reg3; /* offset : 0x302a4 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg1 rx0_reg_rxioen_ovr_reg1; /* offset : 0x302a8 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg2 rx0_reg_rxioen_ovr_reg2; /* offset : 0x302ac */
		union aw_ucie_rx0_reg_rxioen_ovr_reg3 rx0_reg_rxioen_ovr_reg3; /* offset : 0x302b0 */
		union aw_ucie_rx0_reg_rxioen_ovr_reg4 rx0_reg_rxioen_ovr_reg4; /* offset : 0x302b4 */
		union aw_ucie_rx0_reg_rxndealign_rdreg rx0_reg_rxndealign_rdreg; /* offset : 0x302b8 */
		union aw_ucie_rx0_reg_rxndealign_reg1 rx0_reg_rxndealign_reg1; /* offset : 0x302bc */
		union aw_ucie_rx0_reg_rxndealign_reg2 rx0_reg_rxndealign_reg2; /* offset : 0x302c0 */
		union aw_ucie_rx0_reg_rxndechk_rdreg1 rx0_reg_rxndechk_rdreg1; /* offset : 0x302c4 */
		union aw_ucie_rx0_reg_rxndechk_rdreg2 rx0_reg_rxndechk_rdreg2; /* offset : 0x302c8 */
		union aw_ucie_rx0_reg_rxndechk_rdreg3 rx0_reg_rxndechk_rdreg3; /* offset : 0x302cc */
		union aw_ucie_rx0_reg_rxndechk_rdreg4 rx0_reg_rxndechk_rdreg4; /* offset : 0x302d0 */
		union aw_ucie_rx0_reg_rxndechk_reg1 rx0_reg_rxndechk_reg1; /* offset : 0x302d4 */
		union aw_ucie_rx0_reg_rxndechk_reg2 rx0_reg_rxndechk_reg2; /* offset : 0x302d8 */
		union aw_ucie_rx0_reg_rxndechk_reg3 rx0_reg_rxndechk_reg3; /* offset : 0x302dc */
		union aw_ucie_rx0_reg_rxndesync_fg_reg1 rx0_reg_rxndesync_fg_reg1; /* offset : 0x302e0 */
		union aw_ucie_rx0_reg_rxndesync_fg_reg2 rx0_reg_rxndesync_fg_reg2; /* offset : 0x302e4 */
		union aw_ucie_rx0_reg_rxndesync_rdreg rx0_reg_rxndesync_rdreg; /* offset : 0x302e8 */
		union aw_ucie_rx0_reg_rxndesync_reg1 rx0_reg_rxndesync_reg1; /* offset : 0x302ec */
		union aw_ucie_rx0_reg_rxndesync_reg2 rx0_reg_rxndesync_reg2; /* offset : 0x302f0 */
		union aw_ucie_rx0_reg_rxretpi_rdreg rx0_reg_rxretpi_rdreg; /* offset : 0x302f4 */
		union aw_ucie_rx0_reg_rxretpi_reg1 rx0_reg_rxretpi_reg1; /* offset : 0x302f8 */
		union aw_ucie_rx0_reg_rxretpi_reg2 rx0_reg_rxretpi_reg2; /* offset : 0x302fc */
		union aw_ucie_rx0_reg_rxretpi_reg3 rx0_reg_rxretpi_reg3; /* offset : 0x30300 */
		union aw_ucie_rx0_reg_rxretpi_reg4 rx0_reg_rxretpi_reg4; /* offset : 0x30304 */
		union aw_ucie_rx0_reg_rxrst_reg1 rx0_reg_rxrst_reg1; /* offset : 0x30308 */
		union aw_ucie_rx0_reg_rxsip_clr rx0_reg_rxsip_clr; /* offset : 0x3030c */
		union aw_ucie_rx0_reg_rxsoc_rdreg rx0_reg_rxsoc_rdreg; /* offset : 0x30310 */
		union aw_ucie_rx0_reg_rxsoc_reg1 rx0_reg_rxsoc_reg1; /* offset : 0x30314 */
		union aw_ucie_rx0_reg_rxtimer1_rdreg rx0_reg_rxtimer1_rdreg; /* offset : 0x30318 */
		union aw_ucie_rx0_reg_rxtimer1_reg1 rx0_reg_rxtimer1_reg1; /* offset : 0x3031c */
		union aw_ucie_rx0_reg_rxtimer1_reg2 rx0_reg_rxtimer1_reg2; /* offset : 0x30320 */
		union aw_ucie_rx0_reg_rxtimer2_rdreg rx0_reg_rxtimer2_rdreg; /* offset : 0x30324 */
		union aw_ucie_rx0_reg_rxtimer2_reg1 rx0_reg_rxtimer2_reg1; /* offset : 0x30328 */
		union aw_ucie_rx0_reg_rxtimer2_reg2 rx0_reg_rxtimer2_reg2; /* offset : 0x3032c */
		union aw_ucie_rx0_reg_rxclkchk_rdreg2 rx0_reg_rxclkchk_rdreg2; /* offset : 0x30330 */
		union aw_ucie_rx0_reg_rxclkchk_config1 rx0_reg_rxclkchk_config1; /* offset : 0x30334 */
		union aw_ucie_rx0_reg_rxdatchk_int1 rx0_reg_rxdatchk_int1; /* offset : 0x30338 */
		union aw_ucie_rx0_reg_rxdatchk_int1_mask rx0_reg_rxdatchk_int1_mask; /* offset : 0x3033c */
		union aw_ucie_rx0_reg_rxdatchk_int2 rx0_reg_rxdatchk_int2; /* offset : 0x30340 */
		union aw_ucie_rx0_reg_rxdatchk_int2_mask rx0_reg_rxdatchk_int2_mask; /* offset : 0x30344 */
		union aw_ucie_rx0_reg_rxclkchk_rdreg3 rx0_reg_rxclkchk_rdreg3; /* offset : 0x30348 */
		union aw_ucie_rx0_reg_rxdatchk_rdreg13 rx0_reg_rxdatchk_rdreg13; /* offset : 0x3034c */
		union aw_ucie_rx0_reg_rxdatchk_rdreg14 rx0_reg_rxdatchk_rdreg14; /* offset : 0x30350 */
		union aw_ucie_rx0_reg_rxdatchk_reg14 rx0_reg_rxdatchk_reg14; /* offset : 0x30354 */
		uint32_t reserved_32[298];
		union aw_ucie_tx0_reg_tx_csr_ctrl tx0_reg_tx_csr_ctrl; /* offset : 0x30800 */
		union aw_ucie_tx0_reg_tx_ctrl tx0_reg_tx_ctrl; /* offset : 0x30804 */
		union aw_ucie_tx0_reg_tx_ctrl_rdreg tx0_reg_tx_ctrl_rdreg; /* offset : 0x30808 */
		union aw_ucie_tx0_reg_txcalen tx0_reg_txcalen; /* offset : 0x3080c */
		union aw_ucie_tx0_reg_txcmn_reg1 tx0_reg_txcmn_reg1; /* offset : 0x30810 */
		union aw_ucie_tx0_reg_txcmn_reg2 tx0_reg_txcmn_reg2; /* offset : 0x30814 */
		union aw_ucie_tx0_reg_txdatapath_reg0 tx0_reg_txdatapath_reg0; /* offset : 0x30818 */
		union aw_ucie_tx0_reg_txdatapath_reg1 tx0_reg_txdatapath_reg1; /* offset : 0x3081c */
		union aw_ucie_tx0_reg_txdatapath_reg2 tx0_reg_txdatapath_reg2; /* offset : 0x30820 */
		union aw_ucie_tx0_reg_txdatapath_reg3 tx0_reg_txdatapath_reg3; /* offset : 0x30824 */
		union aw_ucie_tx0_reg_txdatapath_reg4 tx0_reg_txdatapath_reg4; /* offset : 0x30828 */
		union aw_ucie_tx0_reg_txdatapath_reg5 tx0_reg_txdatapath_reg5; /* offset : 0x3082c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg0 tx0_reg_txdatgen_perlaneid_reg0; /* offset : 0x30830 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg1 tx0_reg_txdatgen_perlaneid_reg1; /* offset : 0x30834 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg10 tx0_reg_txdatgen_perlaneid_reg10; /* offset : 0x30838 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg11 tx0_reg_txdatgen_perlaneid_reg11; /* offset : 0x3083c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg12 tx0_reg_txdatgen_perlaneid_reg12; /* offset : 0x30840 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg13 tx0_reg_txdatgen_perlaneid_reg13; /* offset : 0x30844 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg14 tx0_reg_txdatgen_perlaneid_reg14; /* offset : 0x30848 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg15 tx0_reg_txdatgen_perlaneid_reg15; /* offset : 0x3084c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg16 tx0_reg_txdatgen_perlaneid_reg16; /* offset : 0x30850 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg2 tx0_reg_txdatgen_perlaneid_reg2; /* offset : 0x30854 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg3 tx0_reg_txdatgen_perlaneid_reg3; /* offset : 0x30858 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg4 tx0_reg_txdatgen_perlaneid_reg4; /* offset : 0x3085c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg5 tx0_reg_txdatgen_perlaneid_reg5; /* offset : 0x30860 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg6 tx0_reg_txdatgen_perlaneid_reg6; /* offset : 0x30864 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg7 tx0_reg_txdatgen_perlaneid_reg7; /* offset : 0x30868 */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg8 tx0_reg_txdatgen_perlaneid_reg8; /* offset : 0x3086c */
		union aw_ucie_tx0_reg_txdatgen_perlaneid_reg9 tx0_reg_txdatgen_perlaneid_reg9; /* offset : 0x30870 */
		union aw_ucie_tx0_reg_txdatgen_rdreg tx0_reg_txdatgen_rdreg; /* offset : 0x30874 */
		union aw_ucie_tx0_reg_txdatgen_reg1 tx0_reg_txdatgen_reg1; /* offset : 0x30878 */
		union aw_ucie_tx0_reg_txdatgen_reg10 tx0_reg_txdatgen_reg10; /* offset : 0x3087c */
		union aw_ucie_tx0_reg_txdatgen_reg11 tx0_reg_txdatgen_reg11; /* offset : 0x30880 */
		union aw_ucie_tx0_reg_txdatgen_reg12 tx0_reg_txdatgen_reg12; /* offset : 0x30884 */
		union aw_ucie_tx0_reg_txdatgen_reg13 tx0_reg_txdatgen_reg13; /* offset : 0x30888 */
		union aw_ucie_tx0_reg_txdatgen_reg14 tx0_reg_txdatgen_reg14; /* offset : 0x3088c */
		union aw_ucie_tx0_reg_txdatgen_reg15 tx0_reg_txdatgen_reg15; /* offset : 0x30890 */
		union aw_ucie_tx0_reg_txdatgen_reg16 tx0_reg_txdatgen_reg16; /* offset : 0x30894 */
		union aw_ucie_tx0_reg_txdatgen_reg17 tx0_reg_txdatgen_reg17; /* offset : 0x30898 */
		union aw_ucie_tx0_reg_txdatgen_reg18 tx0_reg_txdatgen_reg18; /* offset : 0x3089c */
		union aw_ucie_tx0_reg_txdatgen_reg19 tx0_reg_txdatgen_reg19; /* offset : 0x308a0 */
		union aw_ucie_tx0_reg_txdatgen_reg2 tx0_reg_txdatgen_reg2; /* offset : 0x308a4 */
		union aw_ucie_tx0_reg_txdatgen_reg20 tx0_reg_txdatgen_reg20; /* offset : 0x308a8 */
		union aw_ucie_tx0_reg_txdatgen_reg21 tx0_reg_txdatgen_reg21; /* offset : 0x308ac */
		union aw_ucie_tx0_reg_txdatgen_reg3 tx0_reg_txdatgen_reg3; /* offset : 0x308b0 */
		union aw_ucie_tx0_reg_txdatgen_reg4 tx0_reg_txdatgen_reg4; /* offset : 0x308b4 */
		union aw_ucie_tx0_reg_txdatgen_reg5 tx0_reg_txdatgen_reg5; /* offset : 0x308b8 */
		union aw_ucie_tx0_reg_txdatgen_reg6 tx0_reg_txdatgen_reg6; /* offset : 0x308bc */
		union aw_ucie_tx0_reg_txdatgen_reg7 tx0_reg_txdatgen_reg7; /* offset : 0x308c0 */
		union aw_ucie_tx0_reg_txdatgen_reg8 tx0_reg_txdatgen_reg8; /* offset : 0x308c4 */
		union aw_ucie_tx0_reg_txdatgen_reg9 tx0_reg_txdatgen_reg9; /* offset : 0x308c8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg0 tx0_reg_txdatgen_seed_udp_reg0; /* offset : 0x308cc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg1 tx0_reg_txdatgen_seed_udp_reg1; /* offset : 0x308d0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg10 tx0_reg_txdatgen_seed_udp_reg10; /* offset : 0x308d4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg11 tx0_reg_txdatgen_seed_udp_reg11; /* offset : 0x308d8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg12 tx0_reg_txdatgen_seed_udp_reg12; /* offset : 0x308dc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg13 tx0_reg_txdatgen_seed_udp_reg13; /* offset : 0x308e0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg14 tx0_reg_txdatgen_seed_udp_reg14; /* offset : 0x308e4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg15 tx0_reg_txdatgen_seed_udp_reg15; /* offset : 0x308e8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg16 tx0_reg_txdatgen_seed_udp_reg16; /* offset : 0x308ec */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg17 tx0_reg_txdatgen_seed_udp_reg17; /* offset : 0x308f0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg18 tx0_reg_txdatgen_seed_udp_reg18; /* offset : 0x308f4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg19 tx0_reg_txdatgen_seed_udp_reg19; /* offset : 0x308f8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg2 tx0_reg_txdatgen_seed_udp_reg2; /* offset : 0x308fc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg20 tx0_reg_txdatgen_seed_udp_reg20; /* offset : 0x30900 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg21 tx0_reg_txdatgen_seed_udp_reg21; /* offset : 0x30904 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg22 tx0_reg_txdatgen_seed_udp_reg22; /* offset : 0x30908 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg23 tx0_reg_txdatgen_seed_udp_reg23; /* offset : 0x3090c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg24 tx0_reg_txdatgen_seed_udp_reg24; /* offset : 0x30910 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg25 tx0_reg_txdatgen_seed_udp_reg25; /* offset : 0x30914 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg26 tx0_reg_txdatgen_seed_udp_reg26; /* offset : 0x30918 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg27 tx0_reg_txdatgen_seed_udp_reg27; /* offset : 0x3091c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg28 tx0_reg_txdatgen_seed_udp_reg28; /* offset : 0x30920 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg29 tx0_reg_txdatgen_seed_udp_reg29; /* offset : 0x30924 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg3 tx0_reg_txdatgen_seed_udp_reg3; /* offset : 0x30928 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg30 tx0_reg_txdatgen_seed_udp_reg30; /* offset : 0x3092c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg31 tx0_reg_txdatgen_seed_udp_reg31; /* offset : 0x30930 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg32 tx0_reg_txdatgen_seed_udp_reg32; /* offset : 0x30934 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg33 tx0_reg_txdatgen_seed_udp_reg33; /* offset : 0x30938 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg34 tx0_reg_txdatgen_seed_udp_reg34; /* offset : 0x3093c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg35 tx0_reg_txdatgen_seed_udp_reg35; /* offset : 0x30940 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg36 tx0_reg_txdatgen_seed_udp_reg36; /* offset : 0x30944 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg37 tx0_reg_txdatgen_seed_udp_reg37; /* offset : 0x30948 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg38 tx0_reg_txdatgen_seed_udp_reg38; /* offset : 0x3094c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg39 tx0_reg_txdatgen_seed_udp_reg39; /* offset : 0x30950 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg4 tx0_reg_txdatgen_seed_udp_reg4; /* offset : 0x30954 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg40 tx0_reg_txdatgen_seed_udp_reg40; /* offset : 0x30958 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg41 tx0_reg_txdatgen_seed_udp_reg41; /* offset : 0x3095c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg42 tx0_reg_txdatgen_seed_udp_reg42; /* offset : 0x30960 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg43 tx0_reg_txdatgen_seed_udp_reg43; /* offset : 0x30964 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg44 tx0_reg_txdatgen_seed_udp_reg44; /* offset : 0x30968 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg45 tx0_reg_txdatgen_seed_udp_reg45; /* offset : 0x3096c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg46 tx0_reg_txdatgen_seed_udp_reg46; /* offset : 0x30970 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg47 tx0_reg_txdatgen_seed_udp_reg47; /* offset : 0x30974 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg48 tx0_reg_txdatgen_seed_udp_reg48; /* offset : 0x30978 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg49 tx0_reg_txdatgen_seed_udp_reg49; /* offset : 0x3097c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg5 tx0_reg_txdatgen_seed_udp_reg5; /* offset : 0x30980 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg50 tx0_reg_txdatgen_seed_udp_reg50; /* offset : 0x30984 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg51 tx0_reg_txdatgen_seed_udp_reg51; /* offset : 0x30988 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg52 tx0_reg_txdatgen_seed_udp_reg52; /* offset : 0x3098c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg53 tx0_reg_txdatgen_seed_udp_reg53; /* offset : 0x30990 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg54 tx0_reg_txdatgen_seed_udp_reg54; /* offset : 0x30994 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg55 tx0_reg_txdatgen_seed_udp_reg55; /* offset : 0x30998 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg56 tx0_reg_txdatgen_seed_udp_reg56; /* offset : 0x3099c */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg57 tx0_reg_txdatgen_seed_udp_reg57; /* offset : 0x309a0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg58 tx0_reg_txdatgen_seed_udp_reg58; /* offset : 0x309a4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg59 tx0_reg_txdatgen_seed_udp_reg59; /* offset : 0x309a8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg6 tx0_reg_txdatgen_seed_udp_reg6; /* offset : 0x309ac */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg60 tx0_reg_txdatgen_seed_udp_reg60; /* offset : 0x309b0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg61 tx0_reg_txdatgen_seed_udp_reg61; /* offset : 0x309b4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg62 tx0_reg_txdatgen_seed_udp_reg62; /* offset : 0x309b8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg63 tx0_reg_txdatgen_seed_udp_reg63; /* offset : 0x309bc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg64 tx0_reg_txdatgen_seed_udp_reg64; /* offset : 0x309c0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg65 tx0_reg_txdatgen_seed_udp_reg65; /* offset : 0x309c4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg66 tx0_reg_txdatgen_seed_udp_reg66; /* offset : 0x309c8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg67 tx0_reg_txdatgen_seed_udp_reg67; /* offset : 0x309cc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg68 tx0_reg_txdatgen_seed_udp_reg68; /* offset : 0x309d0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg69 tx0_reg_txdatgen_seed_udp_reg69; /* offset : 0x309d4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg7 tx0_reg_txdatgen_seed_udp_reg7; /* offset : 0x309d8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg70 tx0_reg_txdatgen_seed_udp_reg70; /* offset : 0x309dc */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg71 tx0_reg_txdatgen_seed_udp_reg71; /* offset : 0x309e0 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg72 tx0_reg_txdatgen_seed_udp_reg72; /* offset : 0x309e4 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg73 tx0_reg_txdatgen_seed_udp_reg73; /* offset : 0x309e8 */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg8 tx0_reg_txdatgen_seed_udp_reg8; /* offset : 0x309ec */
		union aw_ucie_tx0_reg_txdatgen_seed_udp_reg9 tx0_reg_txdatgen_seed_udp_reg9; /* offset : 0x309f0 */
		union aw_ucie_tx0_reg_txdcc_bg_reg1 tx0_reg_txdcc_bg_reg1; /* offset : 0x309f4 */
		union aw_ucie_tx0_reg_txdcc_fg_reg1 tx0_reg_txdcc_fg_reg1; /* offset : 0x309f8 */
		union aw_ucie_tx0_reg_txdcc_fg_reg2 tx0_reg_txdcc_fg_reg2; /* offset : 0x309fc */
		union aw_ucie_tx0_reg_txdcc_rdreg tx0_reg_txdcc_rdreg; /* offset : 0x30a00 */
		union aw_ucie_tx0_reg_txdcc_reg1 tx0_reg_txdcc_reg1; /* offset : 0x30a04 */
		union aw_ucie_tx0_reg_txdcc_reg2 tx0_reg_txdcc_reg2; /* offset : 0x30a08 */
		union aw_ucie_tx0_reg_txhip_clr tx0_reg_txhip_clr; /* offset : 0x30a0c */
		union aw_ucie_tx0_reg_txhip_dccack_rdreg tx0_reg_txhip_dccack_rdreg; /* offset : 0x30a10 */
		union aw_ucie_tx0_reg_txhip_dccctrl tx0_reg_txhip_dccctrl; /* offset : 0x30a14 */
		union aw_ucie_tx0_reg_txhip_dccreq tx0_reg_txhip_dccreq; /* offset : 0x30a18 */
		union aw_ucie_tx0_reg_txhip_dccval tx0_reg_txhip_dccval; /* offset : 0x30a1c */
		union aw_ucie_tx0_reg_txhip_dccval_rdreg tx0_reg_txhip_dccval_rdreg; /* offset : 0x30a20 */
		union aw_ucie_tx0_reg_txhip_piack_rdreg tx0_reg_txhip_piack_rdreg; /* offset : 0x30a24 */
		union aw_ucie_tx0_reg_txhip_pictrl tx0_reg_txhip_pictrl; /* offset : 0x30a28 */
		union aw_ucie_tx0_reg_txhip_pireq tx0_reg_txhip_pireq; /* offset : 0x30a2c */
		union aw_ucie_tx0_reg_txhip_pival tx0_reg_txhip_pival; /* offset : 0x30a30 */
		union aw_ucie_tx0_reg_txhip_pival_rdreg tx0_reg_txhip_pival_rdreg; /* offset : 0x30a34 */
		union aw_ucie_tx0_reg_txhip_rdreg1 tx0_reg_txhip_rdreg1; /* offset : 0x30a38 */
		union aw_ucie_tx0_reg_txhipcmn_reg1 tx0_reg_txhipcmn_reg1; /* offset : 0x30a3c */
		union aw_ucie_tx0_reg_txhipcmnio_reg1 tx0_reg_txhipcmnio_reg1; /* offset : 0x30a40 */
		union aw_ucie_tx0_reg_txhipcmnio_reg2 tx0_reg_txhipcmnio_reg2; /* offset : 0x30a44 */
		union aw_ucie_tx0_reg_txhipcmnio_reg3 tx0_reg_txhipcmnio_reg3; /* offset : 0x30a48 */
		union aw_ucie_tx0_reg_txhipctrl_reg1 tx0_reg_txhipctrl_reg1; /* offset : 0x30a4c */
		union aw_ucie_tx0_reg_txhipio tx0_reg_txhipio; /* offset : 0x30a50 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg1 tx0_reg_txhipiosync_rdreg1; /* offset : 0x30a54 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg2 tx0_reg_txhipiosync_rdreg2; /* offset : 0x30a58 */
		union aw_ucie_tx0_reg_txhipiosync_rdreg3 tx0_reg_txhipiosync_rdreg3; /* offset : 0x30a5c */
		union aw_ucie_tx0_reg_txhipload_reg1 tx0_reg_txhipload_reg1; /* offset : 0x30a60 */
		union aw_ucie_tx0_reg_txhipload_reg2 tx0_reg_txhipload_reg2; /* offset : 0x30a64 */
		union aw_ucie_tx0_reg_txhipload_reg3 tx0_reg_txhipload_reg3; /* offset : 0x30a68 */
		union aw_ucie_tx0_reg_txhipspare_rdreg1 tx0_reg_txhipspare_rdreg1; /* offset : 0x30a6c */
		union aw_ucie_tx0_reg_txhipspare_reg1 tx0_reg_txhipspare_reg1; /* offset : 0x30a70 */
		union aw_ucie_tx0_reg_txhipspare_reg2 tx0_reg_txhipspare_reg2; /* offset : 0x30a74 */
		union aw_ucie_tx0_reg_txioctrl_reg1 tx0_reg_txioctrl_reg1; /* offset : 0x30a78 */
		union aw_ucie_tx0_reg_txioctrl_reg10 tx0_reg_txioctrl_reg10; /* offset : 0x30a7c */
		union aw_ucie_tx0_reg_txioctrl_reg11 tx0_reg_txioctrl_reg11; /* offset : 0x30a80 */
		union aw_ucie_tx0_reg_txioctrl_reg12 tx0_reg_txioctrl_reg12; /* offset : 0x30a84 */
		union aw_ucie_tx0_reg_txioctrl_reg13 tx0_reg_txioctrl_reg13; /* offset : 0x30a88 */
		union aw_ucie_tx0_reg_txioctrl_reg14 tx0_reg_txioctrl_reg14; /* offset : 0x30a8c */
		union aw_ucie_tx0_reg_txioctrl_reg15 tx0_reg_txioctrl_reg15; /* offset : 0x30a90 */
		union aw_ucie_tx0_reg_txioctrl_reg16 tx0_reg_txioctrl_reg16; /* offset : 0x30a94 */
		union aw_ucie_tx0_reg_txioctrl_reg17 tx0_reg_txioctrl_reg17; /* offset : 0x30a98 */
		union aw_ucie_tx0_reg_txioctrl_reg18 tx0_reg_txioctrl_reg18; /* offset : 0x30a9c */
		union aw_ucie_tx0_reg_txioctrl_reg2 tx0_reg_txioctrl_reg2; /* offset : 0x30aa0 */
		union aw_ucie_tx0_reg_txioctrl_reg3 tx0_reg_txioctrl_reg3; /* offset : 0x30aa4 */
		union aw_ucie_tx0_reg_txioctrl_reg4 tx0_reg_txioctrl_reg4; /* offset : 0x30aa8 */
		union aw_ucie_tx0_reg_txioctrl_reg5 tx0_reg_txioctrl_reg5; /* offset : 0x30aac */
		union aw_ucie_tx0_reg_txioctrl_reg6 tx0_reg_txioctrl_reg6; /* offset : 0x30ab0 */
		union aw_ucie_tx0_reg_txioctrl_reg7 tx0_reg_txioctrl_reg7; /* offset : 0x30ab4 */
		union aw_ucie_tx0_reg_txioctrl_reg8 tx0_reg_txioctrl_reg8; /* offset : 0x30ab8 */
		union aw_ucie_tx0_reg_txioctrl_reg9 tx0_reg_txioctrl_reg9; /* offset : 0x30abc */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg1 tx0_reg_txioen_afe_ovr_reg1; /* offset : 0x30ac0 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg2 tx0_reg_txioen_afe_ovr_reg2; /* offset : 0x30ac4 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg3 tx0_reg_txioen_afe_ovr_reg3; /* offset : 0x30ac8 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg4 tx0_reg_txioen_afe_ovr_reg4; /* offset : 0x30acc */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg1 tx0_reg_txioen_data_ovr_reg1; /* offset : 0x30ad0 */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg2 tx0_reg_txioen_data_ovr_reg2; /* offset : 0x30ad4 */
		union aw_ucie_tx0_reg_txioen_data_ovr_reg3 tx0_reg_txioen_data_ovr_reg3; /* offset : 0x30ad8 */
		union aw_ucie_tx0_reg_txioen_ovr_reg1 tx0_reg_txioen_ovr_reg1; /* offset : 0x30adc */
		union aw_ucie_tx0_reg_txioen_ovr_reg2 tx0_reg_txioen_ovr_reg2; /* offset : 0x30ae0 */
		union aw_ucie_tx0_reg_txioen_ovr_reg3 tx0_reg_txioen_ovr_reg3; /* offset : 0x30ae4 */
		union aw_ucie_tx0_reg_txioen_ovr_reg4 tx0_reg_txioen_ovr_reg4; /* offset : 0x30ae8 */
		union aw_ucie_tx0_reg_txqcc_rdreg tx0_reg_txqcc_rdreg; /* offset : 0x30aec */
		union aw_ucie_tx0_reg_txqcc_reg1 tx0_reg_txqcc_reg1; /* offset : 0x30af0 */
		union aw_ucie_tx0_reg_txqcc_reg2 tx0_reg_txqcc_reg2; /* offset : 0x30af4 */
		union aw_ucie_tx0_reg_txqcc_reg3 tx0_reg_txqcc_reg3; /* offset : 0x30af8 */
		union aw_ucie_tx0_reg_txqcc_reg4 tx0_reg_txqcc_reg4; /* offset : 0x30afc */
		union aw_ucie_tx0_reg_txretpi_rdreg tx0_reg_txretpi_rdreg; /* offset : 0x30b00 */
		union aw_ucie_tx0_reg_txretpi_reg1 tx0_reg_txretpi_reg1; /* offset : 0x30b04 */
		union aw_ucie_tx0_reg_txretpi_reg2 tx0_reg_txretpi_reg2; /* offset : 0x30b08 */
		union aw_ucie_tx0_reg_txretpi_reg3 tx0_reg_txretpi_reg3; /* offset : 0x30b0c */
		union aw_ucie_tx0_reg_txretpi_reg4 tx0_reg_txretpi_reg4; /* offset : 0x30b10 */
		union aw_ucie_tx0_reg_txrst_reg1 tx0_reg_txrst_reg1; /* offset : 0x30b14 */
		union aw_ucie_tx0_reg_txsip_clr tx0_reg_txsip_clr; /* offset : 0x30b18 */
		union aw_ucie_tx0_reg_txsoc_rdreg tx0_reg_txsoc_rdreg; /* offset : 0x30b1c */
		union aw_ucie_tx0_reg_txsoc_reg1 tx0_reg_txsoc_reg1; /* offset : 0x30b20 */
		union aw_ucie_tx0_reg_txsync_bg_reg1 tx0_reg_txsync_bg_reg1; /* offset : 0x30b24 */
		union aw_ucie_tx0_reg_txsync_fg_reg1 tx0_reg_txsync_fg_reg1; /* offset : 0x30b28 */
		union aw_ucie_tx0_reg_txsync_fg_reg2 tx0_reg_txsync_fg_reg2; /* offset : 0x30b2c */
		union aw_ucie_tx0_reg_txsync_rdreg tx0_reg_txsync_rdreg; /* offset : 0x30b30 */
		union aw_ucie_tx0_reg_txsync_reg1 tx0_reg_txsync_reg1; /* offset : 0x30b34 */
		union aw_ucie_tx0_reg_txsync_reg2 tx0_reg_txsync_reg2; /* offset : 0x30b38 */
		union aw_ucie_tx0_reg_txtimer1_rdreg tx0_reg_txtimer1_rdreg; /* offset : 0x30b3c */
		union aw_ucie_tx0_reg_txtimer1_reg1 tx0_reg_txtimer1_reg1; /* offset : 0x30b40 */
		union aw_ucie_tx0_reg_txtimer1_reg2 tx0_reg_txtimer1_reg2; /* offset : 0x30b44 */
		union aw_ucie_tx0_reg_txtimer2_rdreg tx0_reg_txtimer2_rdreg; /* offset : 0x30b48 */
		union aw_ucie_tx0_reg_txtimer2_reg1 tx0_reg_txtimer2_reg1; /* offset : 0x30b4c */
		union aw_ucie_tx0_reg_txtimer2_reg2 tx0_reg_txtimer2_reg2; /* offset : 0x30b50 */
		union aw_ucie_tx0_reg_txdatgen_int1 tx0_reg_txdatgen_int1; /* offset : 0x30b54 */
		union aw_ucie_tx0_reg_txdatgen_int1_mask tx0_reg_txdatgen_int1_mask; /* offset : 0x30b58 */
		union aw_ucie_tx0_reg_txdatgen_int2 tx0_reg_txdatgen_int2; /* offset : 0x30b5c */
		union aw_ucie_tx0_reg_txdatgen_int2_mask tx0_reg_txdatgen_int2_mask; /* offset : 0x30b60 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg5 tx0_reg_txioen_afe_ovr_reg5; /* offset : 0x30b64 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg6 tx0_reg_txioen_afe_ovr_reg6; /* offset : 0x30b68 */
		union aw_ucie_tx0_reg_txioen_afe_ovr_reg7 tx0_reg_txioen_afe_ovr_reg7; /* offset : 0x30b6c */
		uint32_t reserved_33[292];
		union aw_ucie_sb0_reg_reg_sb_afe_cfg1 sb0_reg_reg_sb_afe_cfg1; /* offset : 0x31000 */
		union aw_ucie_sb0_reg_reg_sb_afe_cfg2 sb0_reg_reg_sb_afe_cfg2; /* offset : 0x31004 */
		union aw_ucie_sb0_reg_reg_sb_cmn_reset_cfg sb0_reg_reg_sb_cmn_reset_cfg; /* offset : 0x31008 */
		union aw_ucie_sb0_reg_rst_reg1 sb0_reg_rst_reg1; /* offset : 0x3100c */
		union aw_ucie_sb0_reg_rxsb_afifo_cfg sb0_reg_rxsb_afifo_cfg; /* offset : 0x31010 */
		union aw_ucie_sb0_reg_rxsb_cfg sb0_reg_rxsb_cfg; /* offset : 0x31014 */
		union aw_ucie_sb0_reg_sb_sfifo_int1_mask sb0_reg_sb_sfifo_int1_mask; /* offset : 0x31018 */
		union aw_ucie_sb0_reg_sb_sfifo_int1 sb0_reg_sb_sfifo_int1; /* offset : 0x3101c */
		uint32_t reserved_34;
		union aw_ucie_sb0_reg_rxsb_rdreg1 sb0_reg_rxsb_rdreg1; /* offset : 0x31024 */
		union aw_ucie_sb0_reg_rxsbacccom_cfg sb0_reg_rxsbacccom_cfg; /* offset : 0x31028 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg1 sb0_reg_rxsbacccom_rdreg1; /* offset : 0x3102c */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg2 sb0_reg_rxsbacccom_rdreg2; /* offset : 0x31030 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg3 sb0_reg_rxsbacccom_rdreg3; /* offset : 0x31034 */
		union aw_ucie_sb0_reg_rxsbacccom_rdreg4 sb0_reg_rxsbacccom_rdreg4; /* offset : 0x31038 */
		union aw_ucie_sb0_reg_rxsbaccreq_cfg sb0_reg_rxsbaccreq_cfg; /* offset : 0x3103c */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg1 sb0_reg_rxsbaccreq_rdreg1; /* offset : 0x31040 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg2 sb0_reg_rxsbaccreq_rdreg2; /* offset : 0x31044 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg3 sb0_reg_rxsbaccreq_rdreg3; /* offset : 0x31048 */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg4 sb0_reg_rxsbaccreq_rdreg4; /* offset : 0x3104c */
		union aw_ucie_sb0_reg_rxsbaccreq_rdreg5 sb0_reg_rxsbaccreq_rdreg5; /* offset : 0x31050 */
		union aw_ucie_sb0_reg_rxsbmsg_cfg sb0_reg_rxsbmsg_cfg; /* offset : 0x31054 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg1 sb0_reg_rxsbmsg_rdreg1; /* offset : 0x31058 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg2 sb0_reg_rxsbmsg_rdreg2; /* offset : 0x3105c */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg3 sb0_reg_rxsbmsg_rdreg3; /* offset : 0x31060 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg4 sb0_reg_rxsbmsg_rdreg4; /* offset : 0x31064 */
		union aw_ucie_sb0_reg_rxsbmsg_rdreg5 sb0_reg_rxsbmsg_rdreg5; /* offset : 0x31068 */
		union aw_ucie_sb0_reg_rxsbvmsg_cfg sb0_reg_rxsbvmsg_cfg; /* offset : 0x3106c */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg1 sb0_reg_rxsbvmsg_rdreg1; /* offset : 0x31070 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg2 sb0_reg_rxsbvmsg_rdreg2; /* offset : 0x31074 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg3 sb0_reg_rxsbvmsg_rdreg3; /* offset : 0x31078 */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg4 sb0_reg_rxsbvmsg_rdreg4; /* offset : 0x3107c */
		union aw_ucie_sb0_reg_rxsbvmsg_rdreg5 sb0_reg_rxsbvmsg_rdreg5; /* offset : 0x31080 */
		union aw_ucie_sb0_reg_sb_csr_ctrl sb0_reg_sb_csr_ctrl; /* offset : 0x31084 */
		union aw_ucie_sb0_reg_soc_reg1 sb0_reg_soc_reg1; /* offset : 0x31088 */
		union aw_ucie_sb0_reg_txsb_afifo_cfg sb0_reg_txsb_afifo_cfg; /* offset : 0x3108c */
		union aw_ucie_sb0_reg_txsb_cfg1 sb0_reg_txsb_cfg1; /* offset : 0x31090 */
		union aw_ucie_sb0_reg_txsb_cfg10 sb0_reg_txsb_cfg10; /* offset : 0x31094 */
		union aw_ucie_sb0_reg_txsb_cfg11 sb0_reg_txsb_cfg11; /* offset : 0x31098 */
		union aw_ucie_sb0_reg_txsb_cfg2 sb0_reg_txsb_cfg2; /* offset : 0x3109c */
		union aw_ucie_sb0_reg_txsb_cfg3 sb0_reg_txsb_cfg3; /* offset : 0x310a0 */
		union aw_ucie_sb0_reg_txsb_cfg4 sb0_reg_txsb_cfg4; /* offset : 0x310a4 */
		union aw_ucie_sb0_reg_txsb_cfg5 sb0_reg_txsb_cfg5; /* offset : 0x310a8 */
		union aw_ucie_sb0_reg_txsb_cfg6 sb0_reg_txsb_cfg6; /* offset : 0x310ac */
		union aw_ucie_sb0_reg_txsb_cfg7 sb0_reg_txsb_cfg7; /* offset : 0x310b0 */
		union aw_ucie_sb0_reg_txsb_cfg8 sb0_reg_txsb_cfg8; /* offset : 0x310b4 */
		union aw_ucie_sb0_reg_txsb_cfg9 sb0_reg_txsb_cfg9; /* offset : 0x310b8 */
		union aw_ucie_sb0_reg_txsb_stall_rdreg1 sb0_reg_txsb_stall_rdreg1; /* offset : 0x310bc */
		union aw_ucie_sb0_reg_sb_afifo_int1_mask sb0_reg_sb_afifo_int1_mask; /* offset : 0x310c0 */
		union aw_ucie_sb0_reg_sb_afifo_int1 sb0_reg_sb_afifo_int1; /* offset : 0x310c4 */
		union aw_ucie_sb0_reg_sb_sfifo_int2_mask sb0_reg_sb_sfifo_int2_mask; /* offset : 0x310c8 */
		union aw_ucie_sb0_reg_sb_sfifo_int2 sb0_reg_sb_sfifo_int2; /* offset : 0x310cc */
		union aw_ucie_sb0_reg_sb_afifo_int2_mask sb0_reg_sb_afifo_int2_mask; /* offset : 0x310d0 */
		union aw_ucie_sb0_reg_sb_afifo_int2 sb0_reg_sb_afifo_int2; /* offset : 0x310d4 */
		union aw_ucie_sb0_reg_sb_timeout_count_config1_reg sb0_reg_sb_timeout_count_config1_reg; /* offset : 0x310d8 */
		union aw_ucie_sb0_reg_sb_timeout_count_config2_reg sb0_reg_sb_timeout_count_config2_reg; /* offset : 0x310dc */
		union aw_ucie_sb0_reg_sb_rx_cntrl_config_reg sb0_reg_sb_rx_cntrl_config_reg; /* offset : 0x310e0 */
		uint32_t reserved_35[455];
		union aw_ucie_dfx0_reg_clk_ctrl dfx0_reg_clk_ctrl; /* offset : 0x31800 */
		union aw_ucie_dfx0_reg_dfx_csr_ctrl dfx0_reg_dfx_csr_ctrl; /* offset : 0x31804 */
		union aw_ucie_dfx0_reg_dfx_ctrl dfx0_reg_dfx_ctrl; /* offset : 0x31808 */
		union aw_ucie_dfx0_reg_dfx_stat_rdreg dfx0_reg_dfx_stat_rdreg; /* offset : 0x3180c */
		union aw_ucie_dfx0_reg_lane_mcu_boot_addr dfx0_reg_lane_mcu_boot_addr; /* offset : 0x31810 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump0 dfx0_reg_lane_mcu_crash_dump0; /* offset : 0x31814 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump1 dfx0_reg_lane_mcu_crash_dump1; /* offset : 0x31818 */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump2 dfx0_reg_lane_mcu_crash_dump2; /* offset : 0x3181c */
		union aw_ucie_dfx0_reg_lane_mcu_crash_dump3 dfx0_reg_lane_mcu_crash_dump3; /* offset : 0x31820 */
		union aw_ucie_dfx0_reg_lane_mcu_ctrl dfx0_reg_lane_mcu_ctrl; /* offset : 0x31824 */
		union aw_ucie_dfx0_reg_lane_mcu_device_addr dfx0_reg_lane_mcu_device_addr; /* offset : 0x31828 */
		union aw_ucie_dfx0_reg_lane_mcu_dmem dfx0_reg_lane_mcu_dmem; /* offset : 0x3182c */
		union aw_ucie_dfx0_reg_lane_mcu_hart_id dfx0_reg_lane_mcu_hart_id; /* offset : 0x31830 */
		union aw_ucie_dfx0_reg_lane_mcu_irq dfx0_reg_lane_mcu_irq; /* offset : 0x31834 */
		union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl1 dfx0_reg_lane_mcu_irq_ctrl1; /* offset : 0x31838 */
		union aw_ucie_dfx0_reg_lane_mcu_irq_ctrl2 dfx0_reg_lane_mcu_irq_ctrl2; /* offset : 0x3183c */
		union aw_ucie_dfx0_reg_lane_mcu_stats dfx0_reg_lane_mcu_stats; /* offset : 0x31840 */
		uint32_t reserved_36[495];
		union aw_ucie_rx1_reg_rx_csr_ctrl rx1_reg_rx_csr_ctrl; /* offset : 0x32000 */
		union aw_ucie_rx1_reg_rx_ctrl rx1_reg_rx_ctrl; /* offset : 0x32004 */
		union aw_ucie_rx1_reg_rx_ctrl_rdreg rx1_reg_rx_ctrl_rdreg; /* offset : 0x32008 */
		union aw_ucie_rx1_reg_rxcalen rx1_reg_rxcalen; /* offset : 0x3200c */
		union aw_ucie_rx1_reg_rxclkchk_rdreg rx1_reg_rxclkchk_rdreg; /* offset : 0x32010 */
		union aw_ucie_rx1_reg_rxcmn_reg1 rx1_reg_rxcmn_reg1; /* offset : 0x32014 */
		union aw_ucie_rx1_reg_rxcmn_reg2 rx1_reg_rxcmn_reg2; /* offset : 0x32018 */
		union aw_ucie_rx1_reg_rxdatapath_reg0 rx1_reg_rxdatapath_reg0; /* offset : 0x3201c */
		union aw_ucie_rx1_reg_rxdatapath_reg1 rx1_reg_rxdatapath_reg1; /* offset : 0x32020 */
		union aw_ucie_rx1_reg_rxdatapath_reg2 rx1_reg_rxdatapath_reg2; /* offset : 0x32024 */
		union aw_ucie_rx1_reg_rxdatapath_reg3 rx1_reg_rxdatapath_reg3; /* offset : 0x32028 */
		union aw_ucie_rx1_reg_rxdatapath_reg4 rx1_reg_rxdatapath_reg4; /* offset : 0x3202c */
		union aw_ucie_rx1_reg_rxdatapath_reg5 rx1_reg_rxdatapath_reg5; /* offset : 0x32030 */
		union aw_ucie_rx1_reg_rxdatcap_rdreg1 rx1_reg_rxdatcap_rdreg1; /* offset : 0x32034 */
		union aw_ucie_rx1_reg_rxdatcap_rdreg2 rx1_reg_rxdatcap_rdreg2; /* offset : 0x32038 */
		union aw_ucie_rx1_reg_rxdatcap_reg1 rx1_reg_rxdatcap_reg1; /* offset : 0x3203c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg0 rx1_reg_rxdatchk_perlaneid_reg0; /* offset : 0x32040 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg1 rx1_reg_rxdatchk_perlaneid_reg1; /* offset : 0x32044 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg10 rx1_reg_rxdatchk_perlaneid_reg10; /* offset : 0x32048 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg11 rx1_reg_rxdatchk_perlaneid_reg11; /* offset : 0x3204c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg12 rx1_reg_rxdatchk_perlaneid_reg12; /* offset : 0x32050 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg13 rx1_reg_rxdatchk_perlaneid_reg13; /* offset : 0x32054 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg14 rx1_reg_rxdatchk_perlaneid_reg14; /* offset : 0x32058 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg15 rx1_reg_rxdatchk_perlaneid_reg15; /* offset : 0x3205c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg16 rx1_reg_rxdatchk_perlaneid_reg16; /* offset : 0x32060 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg2 rx1_reg_rxdatchk_perlaneid_reg2; /* offset : 0x32064 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg3 rx1_reg_rxdatchk_perlaneid_reg3; /* offset : 0x32068 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg4 rx1_reg_rxdatchk_perlaneid_reg4; /* offset : 0x3206c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg5 rx1_reg_rxdatchk_perlaneid_reg5; /* offset : 0x32070 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg6 rx1_reg_rxdatchk_perlaneid_reg6; /* offset : 0x32074 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg7 rx1_reg_rxdatchk_perlaneid_reg7; /* offset : 0x32078 */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg8 rx1_reg_rxdatchk_perlaneid_reg8; /* offset : 0x3207c */
		union aw_ucie_rx1_reg_rxdatchk_perlaneid_reg9 rx1_reg_rxdatchk_perlaneid_reg9; /* offset : 0x32080 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg1 rx1_reg_rxdatchk_rdreg1; /* offset : 0x32084 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg10 rx1_reg_rxdatchk_rdreg10; /* offset : 0x32088 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg11 rx1_reg_rxdatchk_rdreg11; /* offset : 0x3208c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg12 rx1_reg_rxdatchk_rdreg12; /* offset : 0x32090 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg2 rx1_reg_rxdatchk_rdreg2; /* offset : 0x32094 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg3 rx1_reg_rxdatchk_rdreg3; /* offset : 0x32098 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg4 rx1_reg_rxdatchk_rdreg4; /* offset : 0x3209c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg5 rx1_reg_rxdatchk_rdreg5; /* offset : 0x320a0 */
		union aw_ucie_rx1_reg_rxdatchk_reg1 rx1_reg_rxdatchk_reg1; /* offset : 0x320a4 */
		union aw_ucie_rx1_reg_rxdatchk_reg13 rx1_reg_rxdatchk_reg13; /* offset : 0x320a8 */
		union aw_ucie_rx1_reg_rxdatchk_reg2 rx1_reg_rxdatchk_reg2; /* offset : 0x320ac */
		union aw_ucie_rx1_reg_rxdatchk_reg3 rx1_reg_rxdatchk_reg3; /* offset : 0x320b0 */
		union aw_ucie_rx1_reg_rxdatchk_reg4 rx1_reg_rxdatchk_reg4; /* offset : 0x320b4 */
		union aw_ucie_rx1_reg_rxdatchk_reg5 rx1_reg_rxdatchk_reg5; /* offset : 0x320b8 */
		union aw_ucie_rx1_reg_rxdatchk_reg6 rx1_reg_rxdatchk_reg6; /* offset : 0x320bc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg0 rx1_reg_rxdatgen_seed_udp_reg0; /* offset : 0x320c0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg1 rx1_reg_rxdatgen_seed_udp_reg1; /* offset : 0x320c4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg10 rx1_reg_rxdatgen_seed_udp_reg10; /* offset : 0x320c8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg11 rx1_reg_rxdatgen_seed_udp_reg11; /* offset : 0x320cc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg12 rx1_reg_rxdatgen_seed_udp_reg12; /* offset : 0x320d0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg13 rx1_reg_rxdatgen_seed_udp_reg13; /* offset : 0x320d4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg14 rx1_reg_rxdatgen_seed_udp_reg14; /* offset : 0x320d8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg15 rx1_reg_rxdatgen_seed_udp_reg15; /* offset : 0x320dc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg16 rx1_reg_rxdatgen_seed_udp_reg16; /* offset : 0x320e0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg17 rx1_reg_rxdatgen_seed_udp_reg17; /* offset : 0x320e4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg18 rx1_reg_rxdatgen_seed_udp_reg18; /* offset : 0x320e8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg19 rx1_reg_rxdatgen_seed_udp_reg19; /* offset : 0x320ec */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg2 rx1_reg_rxdatgen_seed_udp_reg2; /* offset : 0x320f0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg20 rx1_reg_rxdatgen_seed_udp_reg20; /* offset : 0x320f4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg21 rx1_reg_rxdatgen_seed_udp_reg21; /* offset : 0x320f8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg22 rx1_reg_rxdatgen_seed_udp_reg22; /* offset : 0x320fc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg23 rx1_reg_rxdatgen_seed_udp_reg23; /* offset : 0x32100 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg24 rx1_reg_rxdatgen_seed_udp_reg24; /* offset : 0x32104 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg25 rx1_reg_rxdatgen_seed_udp_reg25; /* offset : 0x32108 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg26 rx1_reg_rxdatgen_seed_udp_reg26; /* offset : 0x3210c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg27 rx1_reg_rxdatgen_seed_udp_reg27; /* offset : 0x32110 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg28 rx1_reg_rxdatgen_seed_udp_reg28; /* offset : 0x32114 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg29 rx1_reg_rxdatgen_seed_udp_reg29; /* offset : 0x32118 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg3 rx1_reg_rxdatgen_seed_udp_reg3; /* offset : 0x3211c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg30 rx1_reg_rxdatgen_seed_udp_reg30; /* offset : 0x32120 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg31 rx1_reg_rxdatgen_seed_udp_reg31; /* offset : 0x32124 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg32 rx1_reg_rxdatgen_seed_udp_reg32; /* offset : 0x32128 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg33 rx1_reg_rxdatgen_seed_udp_reg33; /* offset : 0x3212c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg34 rx1_reg_rxdatgen_seed_udp_reg34; /* offset : 0x32130 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg35 rx1_reg_rxdatgen_seed_udp_reg35; /* offset : 0x32134 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg36 rx1_reg_rxdatgen_seed_udp_reg36; /* offset : 0x32138 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg37 rx1_reg_rxdatgen_seed_udp_reg37; /* offset : 0x3213c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg38 rx1_reg_rxdatgen_seed_udp_reg38; /* offset : 0x32140 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg39 rx1_reg_rxdatgen_seed_udp_reg39; /* offset : 0x32144 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg4 rx1_reg_rxdatgen_seed_udp_reg4; /* offset : 0x32148 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg40 rx1_reg_rxdatgen_seed_udp_reg40; /* offset : 0x3214c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg41 rx1_reg_rxdatgen_seed_udp_reg41; /* offset : 0x32150 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg42 rx1_reg_rxdatgen_seed_udp_reg42; /* offset : 0x32154 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg43 rx1_reg_rxdatgen_seed_udp_reg43; /* offset : 0x32158 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg44 rx1_reg_rxdatgen_seed_udp_reg44; /* offset : 0x3215c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg45 rx1_reg_rxdatgen_seed_udp_reg45; /* offset : 0x32160 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg46 rx1_reg_rxdatgen_seed_udp_reg46; /* offset : 0x32164 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg47 rx1_reg_rxdatgen_seed_udp_reg47; /* offset : 0x32168 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg48 rx1_reg_rxdatgen_seed_udp_reg48; /* offset : 0x3216c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg49 rx1_reg_rxdatgen_seed_udp_reg49; /* offset : 0x32170 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg5 rx1_reg_rxdatgen_seed_udp_reg5; /* offset : 0x32174 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg50 rx1_reg_rxdatgen_seed_udp_reg50; /* offset : 0x32178 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg51 rx1_reg_rxdatgen_seed_udp_reg51; /* offset : 0x3217c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg52 rx1_reg_rxdatgen_seed_udp_reg52; /* offset : 0x32180 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg53 rx1_reg_rxdatgen_seed_udp_reg53; /* offset : 0x32184 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg54 rx1_reg_rxdatgen_seed_udp_reg54; /* offset : 0x32188 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg55 rx1_reg_rxdatgen_seed_udp_reg55; /* offset : 0x3218c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg56 rx1_reg_rxdatgen_seed_udp_reg56; /* offset : 0x32190 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg57 rx1_reg_rxdatgen_seed_udp_reg57; /* offset : 0x32194 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg58 rx1_reg_rxdatgen_seed_udp_reg58; /* offset : 0x32198 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg59 rx1_reg_rxdatgen_seed_udp_reg59; /* offset : 0x3219c */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg6 rx1_reg_rxdatgen_seed_udp_reg6; /* offset : 0x321a0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg60 rx1_reg_rxdatgen_seed_udp_reg60; /* offset : 0x321a4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg61 rx1_reg_rxdatgen_seed_udp_reg61; /* offset : 0x321a8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg62 rx1_reg_rxdatgen_seed_udp_reg62; /* offset : 0x321ac */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg63 rx1_reg_rxdatgen_seed_udp_reg63; /* offset : 0x321b0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg64 rx1_reg_rxdatgen_seed_udp_reg64; /* offset : 0x321b4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg65 rx1_reg_rxdatgen_seed_udp_reg65; /* offset : 0x321b8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg66 rx1_reg_rxdatgen_seed_udp_reg66; /* offset : 0x321bc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg67 rx1_reg_rxdatgen_seed_udp_reg67; /* offset : 0x321c0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg68 rx1_reg_rxdatgen_seed_udp_reg68; /* offset : 0x321c4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg69 rx1_reg_rxdatgen_seed_udp_reg69; /* offset : 0x321c8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg7 rx1_reg_rxdatgen_seed_udp_reg7; /* offset : 0x321cc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg70 rx1_reg_rxdatgen_seed_udp_reg70; /* offset : 0x321d0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg71 rx1_reg_rxdatgen_seed_udp_reg71; /* offset : 0x321d4 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg72 rx1_reg_rxdatgen_seed_udp_reg72; /* offset : 0x321d8 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg73 rx1_reg_rxdatgen_seed_udp_reg73; /* offset : 0x321dc */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg8 rx1_reg_rxdatgen_seed_udp_reg8; /* offset : 0x321e0 */
		union aw_ucie_rx1_reg_rxdatgen_seed_udp_reg9 rx1_reg_rxdatgen_seed_udp_reg9; /* offset : 0x321e4 */
		union aw_ucie_rx1_reg_rxhip_clr rx1_reg_rxhip_clr; /* offset : 0x321e8 */
		union aw_ucie_rx1_reg_rxhip_piack_rdreg rx1_reg_rxhip_piack_rdreg; /* offset : 0x321ec */
		union aw_ucie_rx1_reg_rxhip_pictrl rx1_reg_rxhip_pictrl; /* offset : 0x321f0 */
		union aw_ucie_rx1_reg_rxhip_pireq rx1_reg_rxhip_pireq; /* offset : 0x321f4 */
		union aw_ucie_rx1_reg_rxhip_pival rx1_reg_rxhip_pival; /* offset : 0x321f8 */
		union aw_ucie_rx1_reg_rxhip_pival_rdreg rx1_reg_rxhip_pival_rdreg; /* offset : 0x321fc */
		union aw_ucie_rx1_reg_rxhip_rdreg1 rx1_reg_rxhip_rdreg1; /* offset : 0x32200 */
		union aw_ucie_rx1_reg_rxhipcmn_reg1 rx1_reg_rxhipcmn_reg1; /* offset : 0x32204 */
		union aw_ucie_rx1_reg_rxhipcmnio_reg1 rx1_reg_rxhipcmnio_reg1; /* offset : 0x32208 */
		union aw_ucie_rx1_reg_rxhipcmnio_reg2 rx1_reg_rxhipcmnio_reg2; /* offset : 0x3220c */
		union aw_ucie_rx1_reg_rxhipcmnio_reg3 rx1_reg_rxhipcmnio_reg3; /* offset : 0x32210 */
		union aw_ucie_rx1_reg_rxhipctrl_reg1 rx1_reg_rxhipctrl_reg1; /* offset : 0x32214 */
		union aw_ucie_rx1_reg_rxhipdqs_reg1 rx1_reg_rxhipdqs_reg1; /* offset : 0x32218 */
		union aw_ucie_rx1_reg_rxhipdqs_reg2 rx1_reg_rxhipdqs_reg2; /* offset : 0x3221c */
		union aw_ucie_rx1_reg_rxhipio_reg1 rx1_reg_rxhipio_reg1; /* offset : 0x32220 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg1 rx1_reg_rxhipiondesync_rdreg1; /* offset : 0x32224 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg2 rx1_reg_rxhipiondesync_rdreg2; /* offset : 0x32228 */
		union aw_ucie_rx1_reg_rxhipiondesync_rdreg3 rx1_reg_rxhipiondesync_rdreg3; /* offset : 0x3222c */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg1 rx1_reg_rxhipiosampler_rdreg1; /* offset : 0x32230 */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg2 rx1_reg_rxhipiosampler_rdreg2; /* offset : 0x32234 */
		union aw_ucie_rx1_reg_rxhipiosampler_rdreg3 rx1_reg_rxhipiosampler_rdreg3; /* offset : 0x32238 */
		union aw_ucie_rx1_reg_rxhipload_reg1 rx1_reg_rxhipload_reg1; /* offset : 0x3223c */
		union aw_ucie_rx1_reg_rxhipload_reg10 rx1_reg_rxhipload_reg10; /* offset : 0x32240 */
		union aw_ucie_rx1_reg_rxhipload_reg11 rx1_reg_rxhipload_reg11; /* offset : 0x32244 */
		union aw_ucie_rx1_reg_rxhipload_reg12 rx1_reg_rxhipload_reg12; /* offset : 0x32248 */
		union aw_ucie_rx1_reg_rxhipload_reg13 rx1_reg_rxhipload_reg13; /* offset : 0x3224c */
		union aw_ucie_rx1_reg_rxhipload_reg14 rx1_reg_rxhipload_reg14; /* offset : 0x32250 */
		union aw_ucie_rx1_reg_rxhipload_reg15 rx1_reg_rxhipload_reg15; /* offset : 0x32254 */
		union aw_ucie_rx1_reg_rxhipload_reg2 rx1_reg_rxhipload_reg2; /* offset : 0x32258 */
		union aw_ucie_rx1_reg_rxhipload_reg3 rx1_reg_rxhipload_reg3; /* offset : 0x3225c */
		union aw_ucie_rx1_reg_rxhipload_reg4 rx1_reg_rxhipload_reg4; /* offset : 0x32260 */
		union aw_ucie_rx1_reg_rxhipload_reg5 rx1_reg_rxhipload_reg5; /* offset : 0x32264 */
		union aw_ucie_rx1_reg_rxhipload_reg6 rx1_reg_rxhipload_reg6; /* offset : 0x32268 */
		union aw_ucie_rx1_reg_rxhipload_reg7 rx1_reg_rxhipload_reg7; /* offset : 0x3226c */
		union aw_ucie_rx1_reg_rxhipload_reg8 rx1_reg_rxhipload_reg8; /* offset : 0x32270 */
		union aw_ucie_rx1_reg_rxhipload_reg9 rx1_reg_rxhipload_reg9; /* offset : 0x32274 */
		union aw_ucie_rx1_reg_rxhipspare_rdreg1 rx1_reg_rxhipspare_rdreg1; /* offset : 0x32278 */
		union aw_ucie_rx1_reg_rxhipspare_reg1 rx1_reg_rxhipspare_reg1; /* offset : 0x3227c */
		union aw_ucie_rx1_reg_rxhipspare_reg2 rx1_reg_rxhipspare_reg2; /* offset : 0x32280 */
		union aw_ucie_rx1_reg_rxioctrl_reg1 rx1_reg_rxioctrl_reg1; /* offset : 0x32284 */
		union aw_ucie_rx1_reg_rxioctrl_reg2 rx1_reg_rxioctrl_reg2; /* offset : 0x32288 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg1 rx1_reg_rxioen_afe_ovr_reg1; /* offset : 0x3228c */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg2 rx1_reg_rxioen_afe_ovr_reg2; /* offset : 0x32290 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg3 rx1_reg_rxioen_afe_ovr_reg3; /* offset : 0x32294 */
		union aw_ucie_rx1_reg_rxioen_afe_ovr_reg4 rx1_reg_rxioen_afe_ovr_reg4; /* offset : 0x32298 */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg1 rx1_reg_rxioen_data_ovr_reg1; /* offset : 0x3229c */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg2 rx1_reg_rxioen_data_ovr_reg2; /* offset : 0x322a0 */
		union aw_ucie_rx1_reg_rxioen_data_ovr_reg3 rx1_reg_rxioen_data_ovr_reg3; /* offset : 0x322a4 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg1 rx1_reg_rxioen_ovr_reg1; /* offset : 0x322a8 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg2 rx1_reg_rxioen_ovr_reg2; /* offset : 0x322ac */
		union aw_ucie_rx1_reg_rxioen_ovr_reg3 rx1_reg_rxioen_ovr_reg3; /* offset : 0x322b0 */
		union aw_ucie_rx1_reg_rxioen_ovr_reg4 rx1_reg_rxioen_ovr_reg4; /* offset : 0x322b4 */
		union aw_ucie_rx1_reg_rxndealign_rdreg rx1_reg_rxndealign_rdreg; /* offset : 0x322b8 */
		union aw_ucie_rx1_reg_rxndealign_reg1 rx1_reg_rxndealign_reg1; /* offset : 0x322bc */
		union aw_ucie_rx1_reg_rxndealign_reg2 rx1_reg_rxndealign_reg2; /* offset : 0x322c0 */
		union aw_ucie_rx1_reg_rxndechk_rdreg1 rx1_reg_rxndechk_rdreg1; /* offset : 0x322c4 */
		union aw_ucie_rx1_reg_rxndechk_rdreg2 rx1_reg_rxndechk_rdreg2; /* offset : 0x322c8 */
		union aw_ucie_rx1_reg_rxndechk_rdreg3 rx1_reg_rxndechk_rdreg3; /* offset : 0x322cc */
		union aw_ucie_rx1_reg_rxndechk_rdreg4 rx1_reg_rxndechk_rdreg4; /* offset : 0x322d0 */
		union aw_ucie_rx1_reg_rxndechk_reg1 rx1_reg_rxndechk_reg1; /* offset : 0x322d4 */
		union aw_ucie_rx1_reg_rxndechk_reg2 rx1_reg_rxndechk_reg2; /* offset : 0x322d8 */
		union aw_ucie_rx1_reg_rxndechk_reg3 rx1_reg_rxndechk_reg3; /* offset : 0x322dc */
		union aw_ucie_rx1_reg_rxndesync_fg_reg1 rx1_reg_rxndesync_fg_reg1; /* offset : 0x322e0 */
		union aw_ucie_rx1_reg_rxndesync_fg_reg2 rx1_reg_rxndesync_fg_reg2; /* offset : 0x322e4 */
		union aw_ucie_rx1_reg_rxndesync_rdreg rx1_reg_rxndesync_rdreg; /* offset : 0x322e8 */
		union aw_ucie_rx1_reg_rxndesync_reg1 rx1_reg_rxndesync_reg1; /* offset : 0x322ec */
		union aw_ucie_rx1_reg_rxndesync_reg2 rx1_reg_rxndesync_reg2; /* offset : 0x322f0 */
		union aw_ucie_rx1_reg_rxretpi_rdreg rx1_reg_rxretpi_rdreg; /* offset : 0x322f4 */
		union aw_ucie_rx1_reg_rxretpi_reg1 rx1_reg_rxretpi_reg1; /* offset : 0x322f8 */
		union aw_ucie_rx1_reg_rxretpi_reg2 rx1_reg_rxretpi_reg2; /* offset : 0x322fc */
		union aw_ucie_rx1_reg_rxretpi_reg3 rx1_reg_rxretpi_reg3; /* offset : 0x32300 */
		union aw_ucie_rx1_reg_rxretpi_reg4 rx1_reg_rxretpi_reg4; /* offset : 0x32304 */
		union aw_ucie_rx1_reg_rxrst_reg1 rx1_reg_rxrst_reg1; /* offset : 0x32308 */
		union aw_ucie_rx1_reg_rxsip_clr rx1_reg_rxsip_clr; /* offset : 0x3230c */
		union aw_ucie_rx1_reg_rxsoc_rdreg rx1_reg_rxsoc_rdreg; /* offset : 0x32310 */
		union aw_ucie_rx1_reg_rxsoc_reg1 rx1_reg_rxsoc_reg1; /* offset : 0x32314 */
		union aw_ucie_rx1_reg_rxtimer1_rdreg rx1_reg_rxtimer1_rdreg; /* offset : 0x32318 */
		union aw_ucie_rx1_reg_rxtimer1_reg1 rx1_reg_rxtimer1_reg1; /* offset : 0x3231c */
		union aw_ucie_rx1_reg_rxtimer1_reg2 rx1_reg_rxtimer1_reg2; /* offset : 0x32320 */
		union aw_ucie_rx1_reg_rxtimer2_rdreg rx1_reg_rxtimer2_rdreg; /* offset : 0x32324 */
		union aw_ucie_rx1_reg_rxtimer2_reg1 rx1_reg_rxtimer2_reg1; /* offset : 0x32328 */
		union aw_ucie_rx1_reg_rxtimer2_reg2 rx1_reg_rxtimer2_reg2; /* offset : 0x3232c */
		union aw_ucie_rx1_reg_rxclkchk_rdreg2 rx1_reg_rxclkchk_rdreg2; /* offset : 0x32330 */
		union aw_ucie_rx1_reg_rxclkchk_config1 rx1_reg_rxclkchk_config1; /* offset : 0x32334 */
		union aw_ucie_rx1_reg_rxdatchk_int1 rx1_reg_rxdatchk_int1; /* offset : 0x32338 */
		union aw_ucie_rx1_reg_rxdatchk_int1_mask rx1_reg_rxdatchk_int1_mask; /* offset : 0x3233c */
		union aw_ucie_rx1_reg_rxdatchk_int2 rx1_reg_rxdatchk_int2; /* offset : 0x32340 */
		union aw_ucie_rx1_reg_rxdatchk_int2_mask rx1_reg_rxdatchk_int2_mask; /* offset : 0x32344 */
		union aw_ucie_rx1_reg_rxclkchk_rdreg3 rx1_reg_rxclkchk_rdreg3; /* offset : 0x32348 */
		union aw_ucie_rx1_reg_rxdatchk_rdreg13 rx1_reg_rxdatchk_rdreg13; /* offset : 0x3234c */
		union aw_ucie_rx1_reg_rxdatchk_rdreg14 rx1_reg_rxdatchk_rdreg14; /* offset : 0x32350 */
		union aw_ucie_rx1_reg_rxdatchk_reg14 rx1_reg_rxdatchk_reg14; /* offset : 0x32354 */
		uint32_t reserved_37[298];
		union aw_ucie_tx1_reg_tx_csr_ctrl tx1_reg_tx_csr_ctrl; /* offset : 0x32800 */
		union aw_ucie_tx1_reg_tx_ctrl tx1_reg_tx_ctrl; /* offset : 0x32804 */
		union aw_ucie_tx1_reg_tx_ctrl_rdreg tx1_reg_tx_ctrl_rdreg; /* offset : 0x32808 */
		union aw_ucie_tx1_reg_txcalen tx1_reg_txcalen; /* offset : 0x3280c */
		union aw_ucie_tx1_reg_txcmn_reg1 tx1_reg_txcmn_reg1; /* offset : 0x32810 */
		union aw_ucie_tx1_reg_txcmn_reg2 tx1_reg_txcmn_reg2; /* offset : 0x32814 */
		union aw_ucie_tx1_reg_txdatapath_reg0 tx1_reg_txdatapath_reg0; /* offset : 0x32818 */
		union aw_ucie_tx1_reg_txdatapath_reg1 tx1_reg_txdatapath_reg1; /* offset : 0x3281c */
		union aw_ucie_tx1_reg_txdatapath_reg2 tx1_reg_txdatapath_reg2; /* offset : 0x32820 */
		union aw_ucie_tx1_reg_txdatapath_reg3 tx1_reg_txdatapath_reg3; /* offset : 0x32824 */
		union aw_ucie_tx1_reg_txdatapath_reg4 tx1_reg_txdatapath_reg4; /* offset : 0x32828 */
		union aw_ucie_tx1_reg_txdatapath_reg5 tx1_reg_txdatapath_reg5; /* offset : 0x3282c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg0 tx1_reg_txdatgen_perlaneid_reg0; /* offset : 0x32830 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg1 tx1_reg_txdatgen_perlaneid_reg1; /* offset : 0x32834 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg10 tx1_reg_txdatgen_perlaneid_reg10; /* offset : 0x32838 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg11 tx1_reg_txdatgen_perlaneid_reg11; /* offset : 0x3283c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg12 tx1_reg_txdatgen_perlaneid_reg12; /* offset : 0x32840 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg13 tx1_reg_txdatgen_perlaneid_reg13; /* offset : 0x32844 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg14 tx1_reg_txdatgen_perlaneid_reg14; /* offset : 0x32848 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg15 tx1_reg_txdatgen_perlaneid_reg15; /* offset : 0x3284c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg16 tx1_reg_txdatgen_perlaneid_reg16; /* offset : 0x32850 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg2 tx1_reg_txdatgen_perlaneid_reg2; /* offset : 0x32854 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg3 tx1_reg_txdatgen_perlaneid_reg3; /* offset : 0x32858 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg4 tx1_reg_txdatgen_perlaneid_reg4; /* offset : 0x3285c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg5 tx1_reg_txdatgen_perlaneid_reg5; /* offset : 0x32860 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg6 tx1_reg_txdatgen_perlaneid_reg6; /* offset : 0x32864 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg7 tx1_reg_txdatgen_perlaneid_reg7; /* offset : 0x32868 */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg8 tx1_reg_txdatgen_perlaneid_reg8; /* offset : 0x3286c */
		union aw_ucie_tx1_reg_txdatgen_perlaneid_reg9 tx1_reg_txdatgen_perlaneid_reg9; /* offset : 0x32870 */
		union aw_ucie_tx1_reg_txdatgen_rdreg tx1_reg_txdatgen_rdreg; /* offset : 0x32874 */
		union aw_ucie_tx1_reg_txdatgen_reg1 tx1_reg_txdatgen_reg1; /* offset : 0x32878 */
		union aw_ucie_tx1_reg_txdatgen_reg10 tx1_reg_txdatgen_reg10; /* offset : 0x3287c */
		union aw_ucie_tx1_reg_txdatgen_reg11 tx1_reg_txdatgen_reg11; /* offset : 0x32880 */
		union aw_ucie_tx1_reg_txdatgen_reg12 tx1_reg_txdatgen_reg12; /* offset : 0x32884 */
		union aw_ucie_tx1_reg_txdatgen_reg13 tx1_reg_txdatgen_reg13; /* offset : 0x32888 */
		union aw_ucie_tx1_reg_txdatgen_reg14 tx1_reg_txdatgen_reg14; /* offset : 0x3288c */
		union aw_ucie_tx1_reg_txdatgen_reg15 tx1_reg_txdatgen_reg15; /* offset : 0x32890 */
		union aw_ucie_tx1_reg_txdatgen_reg16 tx1_reg_txdatgen_reg16; /* offset : 0x32894 */
		union aw_ucie_tx1_reg_txdatgen_reg17 tx1_reg_txdatgen_reg17; /* offset : 0x32898 */
		union aw_ucie_tx1_reg_txdatgen_reg18 tx1_reg_txdatgen_reg18; /* offset : 0x3289c */
		union aw_ucie_tx1_reg_txdatgen_reg19 tx1_reg_txdatgen_reg19; /* offset : 0x328a0 */
		union aw_ucie_tx1_reg_txdatgen_reg2 tx1_reg_txdatgen_reg2; /* offset : 0x328a4 */
		union aw_ucie_tx1_reg_txdatgen_reg20 tx1_reg_txdatgen_reg20; /* offset : 0x328a8 */
		union aw_ucie_tx1_reg_txdatgen_reg21 tx1_reg_txdatgen_reg21; /* offset : 0x328ac */
		union aw_ucie_tx1_reg_txdatgen_reg3 tx1_reg_txdatgen_reg3; /* offset : 0x328b0 */
		union aw_ucie_tx1_reg_txdatgen_reg4 tx1_reg_txdatgen_reg4; /* offset : 0x328b4 */
		union aw_ucie_tx1_reg_txdatgen_reg5 tx1_reg_txdatgen_reg5; /* offset : 0x328b8 */
		union aw_ucie_tx1_reg_txdatgen_reg6 tx1_reg_txdatgen_reg6; /* offset : 0x328bc */
		union aw_ucie_tx1_reg_txdatgen_reg7 tx1_reg_txdatgen_reg7; /* offset : 0x328c0 */
		union aw_ucie_tx1_reg_txdatgen_reg8 tx1_reg_txdatgen_reg8; /* offset : 0x328c4 */
		union aw_ucie_tx1_reg_txdatgen_reg9 tx1_reg_txdatgen_reg9; /* offset : 0x328c8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg0 tx1_reg_txdatgen_seed_udp_reg0; /* offset : 0x328cc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg1 tx1_reg_txdatgen_seed_udp_reg1; /* offset : 0x328d0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg10 tx1_reg_txdatgen_seed_udp_reg10; /* offset : 0x328d4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg11 tx1_reg_txdatgen_seed_udp_reg11; /* offset : 0x328d8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg12 tx1_reg_txdatgen_seed_udp_reg12; /* offset : 0x328dc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg13 tx1_reg_txdatgen_seed_udp_reg13; /* offset : 0x328e0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg14 tx1_reg_txdatgen_seed_udp_reg14; /* offset : 0x328e4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg15 tx1_reg_txdatgen_seed_udp_reg15; /* offset : 0x328e8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg16 tx1_reg_txdatgen_seed_udp_reg16; /* offset : 0x328ec */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg17 tx1_reg_txdatgen_seed_udp_reg17; /* offset : 0x328f0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg18 tx1_reg_txdatgen_seed_udp_reg18; /* offset : 0x328f4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg19 tx1_reg_txdatgen_seed_udp_reg19; /* offset : 0x328f8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg2 tx1_reg_txdatgen_seed_udp_reg2; /* offset : 0x328fc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg20 tx1_reg_txdatgen_seed_udp_reg20; /* offset : 0x32900 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg21 tx1_reg_txdatgen_seed_udp_reg21; /* offset : 0x32904 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg22 tx1_reg_txdatgen_seed_udp_reg22; /* offset : 0x32908 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg23 tx1_reg_txdatgen_seed_udp_reg23; /* offset : 0x3290c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg24 tx1_reg_txdatgen_seed_udp_reg24; /* offset : 0x32910 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg25 tx1_reg_txdatgen_seed_udp_reg25; /* offset : 0x32914 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg26 tx1_reg_txdatgen_seed_udp_reg26; /* offset : 0x32918 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg27 tx1_reg_txdatgen_seed_udp_reg27; /* offset : 0x3291c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg28 tx1_reg_txdatgen_seed_udp_reg28; /* offset : 0x32920 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg29 tx1_reg_txdatgen_seed_udp_reg29; /* offset : 0x32924 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg3 tx1_reg_txdatgen_seed_udp_reg3; /* offset : 0x32928 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg30 tx1_reg_txdatgen_seed_udp_reg30; /* offset : 0x3292c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg31 tx1_reg_txdatgen_seed_udp_reg31; /* offset : 0x32930 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg32 tx1_reg_txdatgen_seed_udp_reg32; /* offset : 0x32934 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg33 tx1_reg_txdatgen_seed_udp_reg33; /* offset : 0x32938 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg34 tx1_reg_txdatgen_seed_udp_reg34; /* offset : 0x3293c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg35 tx1_reg_txdatgen_seed_udp_reg35; /* offset : 0x32940 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg36 tx1_reg_txdatgen_seed_udp_reg36; /* offset : 0x32944 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg37 tx1_reg_txdatgen_seed_udp_reg37; /* offset : 0x32948 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg38 tx1_reg_txdatgen_seed_udp_reg38; /* offset : 0x3294c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg39 tx1_reg_txdatgen_seed_udp_reg39; /* offset : 0x32950 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg4 tx1_reg_txdatgen_seed_udp_reg4; /* offset : 0x32954 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg40 tx1_reg_txdatgen_seed_udp_reg40; /* offset : 0x32958 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg41 tx1_reg_txdatgen_seed_udp_reg41; /* offset : 0x3295c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg42 tx1_reg_txdatgen_seed_udp_reg42; /* offset : 0x32960 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg43 tx1_reg_txdatgen_seed_udp_reg43; /* offset : 0x32964 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg44 tx1_reg_txdatgen_seed_udp_reg44; /* offset : 0x32968 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg45 tx1_reg_txdatgen_seed_udp_reg45; /* offset : 0x3296c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg46 tx1_reg_txdatgen_seed_udp_reg46; /* offset : 0x32970 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg47 tx1_reg_txdatgen_seed_udp_reg47; /* offset : 0x32974 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg48 tx1_reg_txdatgen_seed_udp_reg48; /* offset : 0x32978 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg49 tx1_reg_txdatgen_seed_udp_reg49; /* offset : 0x3297c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg5 tx1_reg_txdatgen_seed_udp_reg5; /* offset : 0x32980 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg50 tx1_reg_txdatgen_seed_udp_reg50; /* offset : 0x32984 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg51 tx1_reg_txdatgen_seed_udp_reg51; /* offset : 0x32988 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg52 tx1_reg_txdatgen_seed_udp_reg52; /* offset : 0x3298c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg53 tx1_reg_txdatgen_seed_udp_reg53; /* offset : 0x32990 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg54 tx1_reg_txdatgen_seed_udp_reg54; /* offset : 0x32994 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg55 tx1_reg_txdatgen_seed_udp_reg55; /* offset : 0x32998 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg56 tx1_reg_txdatgen_seed_udp_reg56; /* offset : 0x3299c */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg57 tx1_reg_txdatgen_seed_udp_reg57; /* offset : 0x329a0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg58 tx1_reg_txdatgen_seed_udp_reg58; /* offset : 0x329a4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg59 tx1_reg_txdatgen_seed_udp_reg59; /* offset : 0x329a8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg6 tx1_reg_txdatgen_seed_udp_reg6; /* offset : 0x329ac */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg60 tx1_reg_txdatgen_seed_udp_reg60; /* offset : 0x329b0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg61 tx1_reg_txdatgen_seed_udp_reg61; /* offset : 0x329b4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg62 tx1_reg_txdatgen_seed_udp_reg62; /* offset : 0x329b8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg63 tx1_reg_txdatgen_seed_udp_reg63; /* offset : 0x329bc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg64 tx1_reg_txdatgen_seed_udp_reg64; /* offset : 0x329c0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg65 tx1_reg_txdatgen_seed_udp_reg65; /* offset : 0x329c4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg66 tx1_reg_txdatgen_seed_udp_reg66; /* offset : 0x329c8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg67 tx1_reg_txdatgen_seed_udp_reg67; /* offset : 0x329cc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg68 tx1_reg_txdatgen_seed_udp_reg68; /* offset : 0x329d0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg69 tx1_reg_txdatgen_seed_udp_reg69; /* offset : 0x329d4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg7 tx1_reg_txdatgen_seed_udp_reg7; /* offset : 0x329d8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg70 tx1_reg_txdatgen_seed_udp_reg70; /* offset : 0x329dc */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg71 tx1_reg_txdatgen_seed_udp_reg71; /* offset : 0x329e0 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg72 tx1_reg_txdatgen_seed_udp_reg72; /* offset : 0x329e4 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg73 tx1_reg_txdatgen_seed_udp_reg73; /* offset : 0x329e8 */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg8 tx1_reg_txdatgen_seed_udp_reg8; /* offset : 0x329ec */
		union aw_ucie_tx1_reg_txdatgen_seed_udp_reg9 tx1_reg_txdatgen_seed_udp_reg9; /* offset : 0x329f0 */
		union aw_ucie_tx1_reg_txdcc_bg_reg1 tx1_reg_txdcc_bg_reg1; /* offset : 0x329f4 */
		union aw_ucie_tx1_reg_txdcc_fg_reg1 tx1_reg_txdcc_fg_reg1; /* offset : 0x329f8 */
		union aw_ucie_tx1_reg_txdcc_fg_reg2 tx1_reg_txdcc_fg_reg2; /* offset : 0x329fc */
		union aw_ucie_tx1_reg_txdcc_rdreg tx1_reg_txdcc_rdreg; /* offset : 0x32a00 */
		union aw_ucie_tx1_reg_txdcc_reg1 tx1_reg_txdcc_reg1; /* offset : 0x32a04 */
		union aw_ucie_tx1_reg_txdcc_reg2 tx1_reg_txdcc_reg2; /* offset : 0x32a08 */
		union aw_ucie_tx1_reg_txhip_clr tx1_reg_txhip_clr; /* offset : 0x32a0c */
		union aw_ucie_tx1_reg_txhip_dccack_rdreg tx1_reg_txhip_dccack_rdreg; /* offset : 0x32a10 */
		union aw_ucie_tx1_reg_txhip_dccctrl tx1_reg_txhip_dccctrl; /* offset : 0x32a14 */
		union aw_ucie_tx1_reg_txhip_dccreq tx1_reg_txhip_dccreq; /* offset : 0x32a18 */
		union aw_ucie_tx1_reg_txhip_dccval tx1_reg_txhip_dccval; /* offset : 0x32a1c */
		union aw_ucie_tx1_reg_txhip_dccval_rdreg tx1_reg_txhip_dccval_rdreg; /* offset : 0x32a20 */
		union aw_ucie_tx1_reg_txhip_piack_rdreg tx1_reg_txhip_piack_rdreg; /* offset : 0x32a24 */
		union aw_ucie_tx1_reg_txhip_pictrl tx1_reg_txhip_pictrl; /* offset : 0x32a28 */
		union aw_ucie_tx1_reg_txhip_pireq tx1_reg_txhip_pireq; /* offset : 0x32a2c */
		union aw_ucie_tx1_reg_txhip_pival tx1_reg_txhip_pival; /* offset : 0x32a30 */
		union aw_ucie_tx1_reg_txhip_pival_rdreg tx1_reg_txhip_pival_rdreg; /* offset : 0x32a34 */
		union aw_ucie_tx1_reg_txhip_rdreg1 tx1_reg_txhip_rdreg1; /* offset : 0x32a38 */
		union aw_ucie_tx1_reg_txhipcmn_reg1 tx1_reg_txhipcmn_reg1; /* offset : 0x32a3c */
		union aw_ucie_tx1_reg_txhipcmnio_reg1 tx1_reg_txhipcmnio_reg1; /* offset : 0x32a40 */
		union aw_ucie_tx1_reg_txhipcmnio_reg2 tx1_reg_txhipcmnio_reg2; /* offset : 0x32a44 */
		union aw_ucie_tx1_reg_txhipcmnio_reg3 tx1_reg_txhipcmnio_reg3; /* offset : 0x32a48 */
		union aw_ucie_tx1_reg_txhipctrl_reg1 tx1_reg_txhipctrl_reg1; /* offset : 0x32a4c */
		union aw_ucie_tx1_reg_txhipio tx1_reg_txhipio; /* offset : 0x32a50 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg1 tx1_reg_txhipiosync_rdreg1; /* offset : 0x32a54 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg2 tx1_reg_txhipiosync_rdreg2; /* offset : 0x32a58 */
		union aw_ucie_tx1_reg_txhipiosync_rdreg3 tx1_reg_txhipiosync_rdreg3; /* offset : 0x32a5c */
		union aw_ucie_tx1_reg_txhipload_reg1 tx1_reg_txhipload_reg1; /* offset : 0x32a60 */
		union aw_ucie_tx1_reg_txhipload_reg2 tx1_reg_txhipload_reg2; /* offset : 0x32a64 */
		union aw_ucie_tx1_reg_txhipload_reg3 tx1_reg_txhipload_reg3; /* offset : 0x32a68 */
		union aw_ucie_tx1_reg_txhipspare_rdreg1 tx1_reg_txhipspare_rdreg1; /* offset : 0x32a6c */
		union aw_ucie_tx1_reg_txhipspare_reg1 tx1_reg_txhipspare_reg1; /* offset : 0x32a70 */
		union aw_ucie_tx1_reg_txhipspare_reg2 tx1_reg_txhipspare_reg2; /* offset : 0x32a74 */
		union aw_ucie_tx1_reg_txioctrl_reg1 tx1_reg_txioctrl_reg1; /* offset : 0x32a78 */
		union aw_ucie_tx1_reg_txioctrl_reg10 tx1_reg_txioctrl_reg10; /* offset : 0x32a7c */
		union aw_ucie_tx1_reg_txioctrl_reg11 tx1_reg_txioctrl_reg11; /* offset : 0x32a80 */
		union aw_ucie_tx1_reg_txioctrl_reg12 tx1_reg_txioctrl_reg12; /* offset : 0x32a84 */
		union aw_ucie_tx1_reg_txioctrl_reg13 tx1_reg_txioctrl_reg13; /* offset : 0x32a88 */
		union aw_ucie_tx1_reg_txioctrl_reg14 tx1_reg_txioctrl_reg14; /* offset : 0x32a8c */
		union aw_ucie_tx1_reg_txioctrl_reg15 tx1_reg_txioctrl_reg15; /* offset : 0x32a90 */
		union aw_ucie_tx1_reg_txioctrl_reg16 tx1_reg_txioctrl_reg16; /* offset : 0x32a94 */
		union aw_ucie_tx1_reg_txioctrl_reg17 tx1_reg_txioctrl_reg17; /* offset : 0x32a98 */
		union aw_ucie_tx1_reg_txioctrl_reg18 tx1_reg_txioctrl_reg18; /* offset : 0x32a9c */
		union aw_ucie_tx1_reg_txioctrl_reg2 tx1_reg_txioctrl_reg2; /* offset : 0x32aa0 */
		union aw_ucie_tx1_reg_txioctrl_reg3 tx1_reg_txioctrl_reg3; /* offset : 0x32aa4 */
		union aw_ucie_tx1_reg_txioctrl_reg4 tx1_reg_txioctrl_reg4; /* offset : 0x32aa8 */
		union aw_ucie_tx1_reg_txioctrl_reg5 tx1_reg_txioctrl_reg5; /* offset : 0x32aac */
		union aw_ucie_tx1_reg_txioctrl_reg6 tx1_reg_txioctrl_reg6; /* offset : 0x32ab0 */
		union aw_ucie_tx1_reg_txioctrl_reg7 tx1_reg_txioctrl_reg7; /* offset : 0x32ab4 */
		union aw_ucie_tx1_reg_txioctrl_reg8 tx1_reg_txioctrl_reg8; /* offset : 0x32ab8 */
		union aw_ucie_tx1_reg_txioctrl_reg9 tx1_reg_txioctrl_reg9; /* offset : 0x32abc */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg1 tx1_reg_txioen_afe_ovr_reg1; /* offset : 0x32ac0 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg2 tx1_reg_txioen_afe_ovr_reg2; /* offset : 0x32ac4 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg3 tx1_reg_txioen_afe_ovr_reg3; /* offset : 0x32ac8 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg4 tx1_reg_txioen_afe_ovr_reg4; /* offset : 0x32acc */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg1 tx1_reg_txioen_data_ovr_reg1; /* offset : 0x32ad0 */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg2 tx1_reg_txioen_data_ovr_reg2; /* offset : 0x32ad4 */
		union aw_ucie_tx1_reg_txioen_data_ovr_reg3 tx1_reg_txioen_data_ovr_reg3; /* offset : 0x32ad8 */
		union aw_ucie_tx1_reg_txioen_ovr_reg1 tx1_reg_txioen_ovr_reg1; /* offset : 0x32adc */
		union aw_ucie_tx1_reg_txioen_ovr_reg2 tx1_reg_txioen_ovr_reg2; /* offset : 0x32ae0 */
		union aw_ucie_tx1_reg_txioen_ovr_reg3 tx1_reg_txioen_ovr_reg3; /* offset : 0x32ae4 */
		union aw_ucie_tx1_reg_txioen_ovr_reg4 tx1_reg_txioen_ovr_reg4; /* offset : 0x32ae8 */
		union aw_ucie_tx1_reg_txqcc_rdreg tx1_reg_txqcc_rdreg; /* offset : 0x32aec */
		union aw_ucie_tx1_reg_txqcc_reg1 tx1_reg_txqcc_reg1; /* offset : 0x32af0 */
		union aw_ucie_tx1_reg_txqcc_reg2 tx1_reg_txqcc_reg2; /* offset : 0x32af4 */
		union aw_ucie_tx1_reg_txqcc_reg3 tx1_reg_txqcc_reg3; /* offset : 0x32af8 */
		union aw_ucie_tx1_reg_txqcc_reg4 tx1_reg_txqcc_reg4; /* offset : 0x32afc */
		union aw_ucie_tx1_reg_txretpi_rdreg tx1_reg_txretpi_rdreg; /* offset : 0x32b00 */
		union aw_ucie_tx1_reg_txretpi_reg1 tx1_reg_txretpi_reg1; /* offset : 0x32b04 */
		union aw_ucie_tx1_reg_txretpi_reg2 tx1_reg_txretpi_reg2; /* offset : 0x32b08 */
		union aw_ucie_tx1_reg_txretpi_reg3 tx1_reg_txretpi_reg3; /* offset : 0x32b0c */
		union aw_ucie_tx1_reg_txretpi_reg4 tx1_reg_txretpi_reg4; /* offset : 0x32b10 */
		union aw_ucie_tx1_reg_txrst_reg1 tx1_reg_txrst_reg1; /* offset : 0x32b14 */
		union aw_ucie_tx1_reg_txsip_clr tx1_reg_txsip_clr; /* offset : 0x32b18 */
		union aw_ucie_tx1_reg_txsoc_rdreg tx1_reg_txsoc_rdreg; /* offset : 0x32b1c */
		union aw_ucie_tx1_reg_txsoc_reg1 tx1_reg_txsoc_reg1; /* offset : 0x32b20 */
		union aw_ucie_tx1_reg_txsync_bg_reg1 tx1_reg_txsync_bg_reg1; /* offset : 0x32b24 */
		union aw_ucie_tx1_reg_txsync_fg_reg1 tx1_reg_txsync_fg_reg1; /* offset : 0x32b28 */
		union aw_ucie_tx1_reg_txsync_fg_reg2 tx1_reg_txsync_fg_reg2; /* offset : 0x32b2c */
		union aw_ucie_tx1_reg_txsync_rdreg tx1_reg_txsync_rdreg; /* offset : 0x32b30 */
		union aw_ucie_tx1_reg_txsync_reg1 tx1_reg_txsync_reg1; /* offset : 0x32b34 */
		union aw_ucie_tx1_reg_txsync_reg2 tx1_reg_txsync_reg2; /* offset : 0x32b38 */
		union aw_ucie_tx1_reg_txtimer1_rdreg tx1_reg_txtimer1_rdreg; /* offset : 0x32b3c */
		union aw_ucie_tx1_reg_txtimer1_reg1 tx1_reg_txtimer1_reg1; /* offset : 0x32b40 */
		union aw_ucie_tx1_reg_txtimer1_reg2 tx1_reg_txtimer1_reg2; /* offset : 0x32b44 */
		union aw_ucie_tx1_reg_txtimer2_rdreg tx1_reg_txtimer2_rdreg; /* offset : 0x32b48 */
		union aw_ucie_tx1_reg_txtimer2_reg1 tx1_reg_txtimer2_reg1; /* offset : 0x32b4c */
		union aw_ucie_tx1_reg_txtimer2_reg2 tx1_reg_txtimer2_reg2; /* offset : 0x32b50 */
		union aw_ucie_tx1_reg_txdatgen_int1 tx1_reg_txdatgen_int1; /* offset : 0x32b54 */
		union aw_ucie_tx1_reg_txdatgen_int1_mask tx1_reg_txdatgen_int1_mask; /* offset : 0x32b58 */
		union aw_ucie_tx1_reg_txdatgen_int2 tx1_reg_txdatgen_int2; /* offset : 0x32b5c */
		union aw_ucie_tx1_reg_txdatgen_int2_mask tx1_reg_txdatgen_int2_mask; /* offset : 0x32b60 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg5 tx1_reg_txioen_afe_ovr_reg5; /* offset : 0x32b64 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg6 tx1_reg_txioen_afe_ovr_reg6; /* offset : 0x32b68 */
		union aw_ucie_tx1_reg_txioen_afe_ovr_reg7 tx1_reg_txioen_afe_ovr_reg7; /* offset : 0x32b6c */
		uint32_t reserved_38[292];
		union aw_ucie_sb1_reg_reg_sb_afe_cfg1 sb1_reg_reg_sb_afe_cfg1; /* offset : 0x33000 */
		union aw_ucie_sb1_reg_reg_sb_afe_cfg2 sb1_reg_reg_sb_afe_cfg2; /* offset : 0x33004 */
		union aw_ucie_sb1_reg_reg_sb_cmn_reset_cfg sb1_reg_reg_sb_cmn_reset_cfg; /* offset : 0x33008 */
		union aw_ucie_sb1_reg_rst_reg1 sb1_reg_rst_reg1; /* offset : 0x3300c */
		union aw_ucie_sb1_reg_rxsb_afifo_cfg sb1_reg_rxsb_afifo_cfg; /* offset : 0x33010 */
		union aw_ucie_sb1_reg_rxsb_cfg sb1_reg_rxsb_cfg; /* offset : 0x33014 */
		union aw_ucie_sb1_reg_sb_sfifo_int1_mask sb1_reg_sb_sfifo_int1_mask; /* offset : 0x33018 */
		union aw_ucie_sb1_reg_sb_sfifo_int1 sb1_reg_sb_sfifo_int1; /* offset : 0x3301c */
		uint32_t reserved_39;
		union aw_ucie_sb1_reg_rxsb_rdreg1 sb1_reg_rxsb_rdreg1; /* offset : 0x33024 */
		union aw_ucie_sb1_reg_rxsbacccom_cfg sb1_reg_rxsbacccom_cfg; /* offset : 0x33028 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg1 sb1_reg_rxsbacccom_rdreg1; /* offset : 0x3302c */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg2 sb1_reg_rxsbacccom_rdreg2; /* offset : 0x33030 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg3 sb1_reg_rxsbacccom_rdreg3; /* offset : 0x33034 */
		union aw_ucie_sb1_reg_rxsbacccom_rdreg4 sb1_reg_rxsbacccom_rdreg4; /* offset : 0x33038 */
		union aw_ucie_sb1_reg_rxsbaccreq_cfg sb1_reg_rxsbaccreq_cfg; /* offset : 0x3303c */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg1 sb1_reg_rxsbaccreq_rdreg1; /* offset : 0x33040 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg2 sb1_reg_rxsbaccreq_rdreg2; /* offset : 0x33044 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg3 sb1_reg_rxsbaccreq_rdreg3; /* offset : 0x33048 */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg4 sb1_reg_rxsbaccreq_rdreg4; /* offset : 0x3304c */
		union aw_ucie_sb1_reg_rxsbaccreq_rdreg5 sb1_reg_rxsbaccreq_rdreg5; /* offset : 0x33050 */
		union aw_ucie_sb1_reg_rxsbmsg_cfg sb1_reg_rxsbmsg_cfg; /* offset : 0x33054 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg1 sb1_reg_rxsbmsg_rdreg1; /* offset : 0x33058 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg2 sb1_reg_rxsbmsg_rdreg2; /* offset : 0x3305c */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg3 sb1_reg_rxsbmsg_rdreg3; /* offset : 0x33060 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg4 sb1_reg_rxsbmsg_rdreg4; /* offset : 0x33064 */
		union aw_ucie_sb1_reg_rxsbmsg_rdreg5 sb1_reg_rxsbmsg_rdreg5; /* offset : 0x33068 */
		union aw_ucie_sb1_reg_rxsbvmsg_cfg sb1_reg_rxsbvmsg_cfg; /* offset : 0x3306c */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg1 sb1_reg_rxsbvmsg_rdreg1; /* offset : 0x33070 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg2 sb1_reg_rxsbvmsg_rdreg2; /* offset : 0x33074 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg3 sb1_reg_rxsbvmsg_rdreg3; /* offset : 0x33078 */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg4 sb1_reg_rxsbvmsg_rdreg4; /* offset : 0x3307c */
		union aw_ucie_sb1_reg_rxsbvmsg_rdreg5 sb1_reg_rxsbvmsg_rdreg5; /* offset : 0x33080 */
		union aw_ucie_sb1_reg_sb_csr_ctrl sb1_reg_sb_csr_ctrl; /* offset : 0x33084 */
		union aw_ucie_sb1_reg_soc_reg1 sb1_reg_soc_reg1; /* offset : 0x33088 */
		union aw_ucie_sb1_reg_txsb_afifo_cfg sb1_reg_txsb_afifo_cfg; /* offset : 0x3308c */
		union aw_ucie_sb1_reg_txsb_cfg1 sb1_reg_txsb_cfg1; /* offset : 0x33090 */
		union aw_ucie_sb1_reg_txsb_cfg10 sb1_reg_txsb_cfg10; /* offset : 0x33094 */
		union aw_ucie_sb1_reg_txsb_cfg11 sb1_reg_txsb_cfg11; /* offset : 0x33098 */
		union aw_ucie_sb1_reg_txsb_cfg2 sb1_reg_txsb_cfg2; /* offset : 0x3309c */
		union aw_ucie_sb1_reg_txsb_cfg3 sb1_reg_txsb_cfg3; /* offset : 0x330a0 */
		union aw_ucie_sb1_reg_txsb_cfg4 sb1_reg_txsb_cfg4; /* offset : 0x330a4 */
		union aw_ucie_sb1_reg_txsb_cfg5 sb1_reg_txsb_cfg5; /* offset : 0x330a8 */
		union aw_ucie_sb1_reg_txsb_cfg6 sb1_reg_txsb_cfg6; /* offset : 0x330ac */
		union aw_ucie_sb1_reg_txsb_cfg7 sb1_reg_txsb_cfg7; /* offset : 0x330b0 */
		union aw_ucie_sb1_reg_txsb_cfg8 sb1_reg_txsb_cfg8; /* offset : 0x330b4 */
		union aw_ucie_sb1_reg_txsb_cfg9 sb1_reg_txsb_cfg9; /* offset : 0x330b8 */
		union aw_ucie_sb1_reg_txsb_stall_rdreg1 sb1_reg_txsb_stall_rdreg1; /* offset : 0x330bc */
		union aw_ucie_sb1_reg_sb_afifo_int1_mask sb1_reg_sb_afifo_int1_mask; /* offset : 0x330c0 */
		union aw_ucie_sb1_reg_sb_afifo_int1 sb1_reg_sb_afifo_int1; /* offset : 0x330c4 */
		union aw_ucie_sb1_reg_sb_sfifo_int2_mask sb1_reg_sb_sfifo_int2_mask; /* offset : 0x330c8 */
		union aw_ucie_sb1_reg_sb_sfifo_int2 sb1_reg_sb_sfifo_int2; /* offset : 0x330cc */
		union aw_ucie_sb1_reg_sb_afifo_int2_mask sb1_reg_sb_afifo_int2_mask; /* offset : 0x330d0 */
		union aw_ucie_sb1_reg_sb_afifo_int2 sb1_reg_sb_afifo_int2; /* offset : 0x330d4 */
		union aw_ucie_sb1_reg_sb_timeout_count_config1_reg sb1_reg_sb_timeout_count_config1_reg; /* offset : 0x330d8 */
		union aw_ucie_sb1_reg_sb_timeout_count_config2_reg sb1_reg_sb_timeout_count_config2_reg; /* offset : 0x330dc */
		union aw_ucie_sb1_reg_sb_rx_cntrl_config_reg sb1_reg_sb_rx_cntrl_config_reg; /* offset : 0x330e0 */
		uint32_t reserved_40[455];
		union aw_ucie_dfx1_reg_clk_ctrl dfx1_reg_clk_ctrl; /* offset : 0x33800 */
		union aw_ucie_dfx1_reg_dfx_csr_ctrl dfx1_reg_dfx_csr_ctrl; /* offset : 0x33804 */
		union aw_ucie_dfx1_reg_dfx_ctrl dfx1_reg_dfx_ctrl; /* offset : 0x33808 */
		union aw_ucie_dfx1_reg_dfx_stat_rdreg dfx1_reg_dfx_stat_rdreg; /* offset : 0x3380c */
		union aw_ucie_dfx1_reg_lane_mcu_boot_addr dfx1_reg_lane_mcu_boot_addr; /* offset : 0x33810 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump0 dfx1_reg_lane_mcu_crash_dump0; /* offset : 0x33814 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump1 dfx1_reg_lane_mcu_crash_dump1; /* offset : 0x33818 */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump2 dfx1_reg_lane_mcu_crash_dump2; /* offset : 0x3381c */
		union aw_ucie_dfx1_reg_lane_mcu_crash_dump3 dfx1_reg_lane_mcu_crash_dump3; /* offset : 0x33820 */
		union aw_ucie_dfx1_reg_lane_mcu_ctrl dfx1_reg_lane_mcu_ctrl; /* offset : 0x33824 */
		union aw_ucie_dfx1_reg_lane_mcu_device_addr dfx1_reg_lane_mcu_device_addr; /* offset : 0x33828 */
		union aw_ucie_dfx1_reg_lane_mcu_dmem dfx1_reg_lane_mcu_dmem; /* offset : 0x3382c */
		union aw_ucie_dfx1_reg_lane_mcu_hart_id dfx1_reg_lane_mcu_hart_id; /* offset : 0x33830 */
		union aw_ucie_dfx1_reg_lane_mcu_irq dfx1_reg_lane_mcu_irq; /* offset : 0x33834 */
		union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl1 dfx1_reg_lane_mcu_irq_ctrl1; /* offset : 0x33838 */
		union aw_ucie_dfx1_reg_lane_mcu_irq_ctrl2 dfx1_reg_lane_mcu_irq_ctrl2; /* offset : 0x3383c */
		union aw_ucie_dfx1_reg_lane_mcu_stats dfx1_reg_lane_mcu_stats; /* offset : 0x33840 */
		uint32_t reserved_41[15855];
		union aw_ucie_bridge_top_reg_reg_bridge_top_fifo_wm bridge_top_reg_reg_bridge_top_fifo_wm; /* offset : 0x43000 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1 bridge_top_reg_reg_bridge_top_interrupt1; /* offset : 0x43004 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt1_mask bridge_top_reg_reg_bridge_top_interrupt1_mask; /* offset : 0x43008 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2 bridge_top_reg_reg_bridge_top_interrupt2; /* offset : 0x4300c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_interrupt2_mask bridge_top_reg_reg_bridge_top_interrupt2_mask; /* offset : 0x43010 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary bridge_top_reg_reg_bridge_top_intr1_summary; /* offset : 0x43014 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr1_summary_mask bridge_top_reg_reg_bridge_top_intr1_summary_mask; /* offset : 0x43018 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary bridge_top_reg_reg_bridge_top_intr2_summary; /* offset : 0x4301c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_intr2_summary_mask bridge_top_reg_reg_bridge_top_intr2_summary_mask; /* offset : 0x43020 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_cfg bridge_top_reg_reg_bridge_top_cmn_cfg; /* offset : 0x43024 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status bridge_top_reg_reg_bridge_top_cmn_status; /* offset : 0x43028 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cmn_status2 bridge_top_reg_reg_bridge_top_cmn_status2; /* offset : 0x4302c */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg1 bridge_top_reg_fdi_txsb_cfg1; /* offset : 0x43030 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg2 bridge_top_reg_fdi_txsb_cfg2; /* offset : 0x43034 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg3 bridge_top_reg_fdi_txsb_cfg3; /* offset : 0x43038 */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg4 bridge_top_reg_fdi_txsb_cfg4; /* offset : 0x4303c */
		union aw_ucie_bridge_top_reg_fdi_txsb_cfg5 bridge_top_reg_fdi_txsb_cfg5; /* offset : 0x43040 */
		union aw_ucie_bridge_top_reg_fdi_txsb_stall_rdreg1 bridge_top_reg_fdi_txsb_stall_rdreg1; /* offset : 0x43044 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_cfg bridge_top_reg_fdi_rxsbacccom_cfg; /* offset : 0x43048 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg1 bridge_top_reg_fdi_rxsbacccom_rdreg1; /* offset : 0x4304c */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg2 bridge_top_reg_fdi_rxsbacccom_rdreg2; /* offset : 0x43050 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg3 bridge_top_reg_fdi_rxsbacccom_rdreg3; /* offset : 0x43054 */
		union aw_ucie_bridge_top_reg_fdi_rxsbacccom_rdreg4 bridge_top_reg_fdi_rxsbacccom_rdreg4; /* offset : 0x43058 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_cfg bridge_top_reg_fdi_rxsbaccreq_cfg; /* offset : 0x4305c */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg1 bridge_top_reg_fdi_rxsbaccreq_rdreg1; /* offset : 0x43060 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg2 bridge_top_reg_fdi_rxsbaccreq_rdreg2; /* offset : 0x43064 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg3 bridge_top_reg_fdi_rxsbaccreq_rdreg3; /* offset : 0x43068 */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg4 bridge_top_reg_fdi_rxsbaccreq_rdreg4; /* offset : 0x4306c */
		union aw_ucie_bridge_top_reg_fdi_rxsbaccreq_rdreg5 bridge_top_reg_fdi_rxsbaccreq_rdreg5; /* offset : 0x43070 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg1 bridge_top_reg_fdi_sb_fifo_err_rdreg1; /* offset : 0x43074 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask bridge_top_reg_fdi_sb_fifo_err_mask; /* offset : 0x43078 */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_rdreg2 bridge_top_reg_fdi_sb_fifo_err_rdreg2; /* offset : 0x4307c */
		union aw_ucie_bridge_top_reg_fdi_sb_fifo_err_mask2 bridge_top_reg_fdi_sb_fifo_err_mask2; /* offset : 0x43080 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config bridge_top_reg_reg_bridge_top_cxs_config; /* offset : 0x43084 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_status bridge_top_reg_reg_bridge_top_cxs_status; /* offset : 0x43088 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_cxs_config2 bridge_top_reg_reg_bridge_top_cxs_config2; /* offset : 0x4308c */
		union aw_ucie_bridge_top_reg_reg_bridge_top_periodic_timer_config bridge_top_reg_reg_bridge_top_periodic_timer_config; /* offset : 0x43090 */
		union aw_ucie_bridge_top_reg_reg_bridge_top_gb_force_read_value bridge_top_reg_reg_bridge_top_gb_force_read_value; /* offset : 0x43094 */
		uint32_t reserved_42[26];
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_fifo_wm p0_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43100 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_fc_control p0_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43104 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_comm_count_control p0_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43108 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_count_control p0_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x4310c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43110 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43114 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43118 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4311c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43120 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43124 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43128 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4312c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1 p0_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43130 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt1_mask p0_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43134 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2 p0_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43138 */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_interrupt2_mask p0_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4313c */
		union aw_ucie_p0_axi4_aw_ch_reg_reg_brg_credit p0_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43140 */
		uint32_t reserved_43[47];
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_fifo_wm p0_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43200 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_fc_control p0_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43204 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_comm_count_control p0_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43208 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_count_control p0_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x4320c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43210 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43214 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43218 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4321c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43220 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43224 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43228 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4322c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1 p0_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43230 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt1_mask p0_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43234 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2 p0_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43238 */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_interrupt2_mask p0_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4323c */
		union aw_ucie_p0_axi4_wd_ch_reg_reg_brg_credit p0_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43240 */
		uint32_t reserved_44[47];
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_fifo_wm p0_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43300 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_fc_control p0_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43304 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_comm_count_control p0_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43308 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_count_control p0_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x4330c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43310 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43314 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43318 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4331c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43320 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43324 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43328 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4332c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1 p0_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43330 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt1_mask p0_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43334 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2 p0_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43338 */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_interrupt2_mask p0_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4333c */
		union aw_ucie_p0_axi4_wr_ch_reg_reg_brg_credit p0_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43340 */
		uint32_t reserved_45[47];
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_fifo_wm p0_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43400 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_fc_control p0_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43404 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_comm_count_control p0_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43408 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_count_control p0_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x4340c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43410 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43414 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43418 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4341c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43420 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43424 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43428 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4342c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1 p0_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43430 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt1_mask p0_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43434 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2 p0_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43438 */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_interrupt2_mask p0_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4343c */
		union aw_ucie_p0_axi4_ar_ch_reg_reg_brg_credit p0_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43440 */
		uint32_t reserved_46[47];
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_fifo_wm p0_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43500 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_fc_control p0_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43504 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_comm_count_control p0_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43508 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_count_control p0_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x4350c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43510 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p0_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43514 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43518 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p0_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4351c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43520 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p0_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43524 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43528 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p0_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4352c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1 p0_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43530 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt1_mask p0_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43534 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2 p0_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43538 */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_interrupt2_mask p0_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4353c */
		union aw_ucie_p0_axi4_rd_ch_reg_reg_brg_credit p0_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43540 */
		uint32_t reserved_47[47];
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_fifo_wm p1_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43600 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_fc_control p1_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43604 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_comm_count_control p1_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43608 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_count_control p1_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x4360c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43610 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43614 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43618 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4361c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43620 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43624 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43628 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4362c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1 p1_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43630 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt1_mask p1_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43634 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2 p1_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43638 */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_interrupt2_mask p1_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4363c */
		union aw_ucie_p1_axi4_aw_ch_reg_reg_brg_credit p1_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43640 */
		uint32_t reserved_48[47];
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_fifo_wm p1_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43700 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_fc_control p1_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43704 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_comm_count_control p1_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43708 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_count_control p1_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x4370c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43710 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43714 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43718 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4371c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43720 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43724 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43728 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4372c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1 p1_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43730 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt1_mask p1_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43734 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2 p1_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43738 */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_interrupt2_mask p1_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4373c */
		union aw_ucie_p1_axi4_wd_ch_reg_reg_brg_credit p1_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43740 */
		uint32_t reserved_49[47];
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_fifo_wm p1_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43800 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_fc_control p1_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43804 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_comm_count_control p1_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43808 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_count_control p1_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x4380c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43810 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43814 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43818 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4381c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43820 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43824 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43828 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4382c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1 p1_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43830 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt1_mask p1_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43834 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2 p1_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43838 */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_interrupt2_mask p1_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4383c */
		union aw_ucie_p1_axi4_wr_ch_reg_reg_brg_credit p1_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43840 */
		uint32_t reserved_50[47];
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_fifo_wm p1_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43900 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_fc_control p1_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43904 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_comm_count_control p1_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43908 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_count_control p1_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x4390c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43910 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43914 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43918 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x4391c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43920 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43924 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43928 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x4392c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1 p1_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43930 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt1_mask p1_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43934 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2 p1_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43938 */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_interrupt2_mask p1_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x4393c */
		union aw_ucie_p1_axi4_ar_ch_reg_reg_brg_credit p1_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43940 */
		uint32_t reserved_51[47];
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_fifo_wm p1_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43a00 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_fc_control p1_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43a04 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_comm_count_control p1_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43a08 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_count_control p1_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x43a0c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43a10 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p1_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43a14 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43a18 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p1_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43a1c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43a20 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p1_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43a24 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43a28 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p1_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43a2c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1 p1_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43a30 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt1_mask p1_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43a34 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2 p1_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43a38 */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_interrupt2_mask p1_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43a3c */
		union aw_ucie_p1_axi4_rd_ch_reg_reg_brg_credit p1_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43a40 */
		uint32_t reserved_52[47];
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_fifo_wm p2_axi4_aw_ch_reg_reg_brg_fifo_wm; /* offset : 0x43b00 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_fc_control p2_axi4_aw_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43b04 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_comm_count_control p2_axi4_aw_ch_reg_reg_brg_comm_count_control; /* offset : 0x43b08 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_count_control p2_axi4_aw_ch_reg_reg_brg_count_control; /* offset : 0x43b0c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43b10 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_aw_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43b14 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43b18 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_aw_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43b1c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43b20 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_aw_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43b24 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43b28 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_aw_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43b2c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1 p2_axi4_aw_ch_reg_reg_brg_interrupt1; /* offset : 0x43b30 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt1_mask p2_axi4_aw_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43b34 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2 p2_axi4_aw_ch_reg_reg_brg_interrupt2; /* offset : 0x43b38 */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_interrupt2_mask p2_axi4_aw_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43b3c */
		union aw_ucie_p2_axi4_aw_ch_reg_reg_brg_credit p2_axi4_aw_ch_reg_reg_brg_credit; /* offset : 0x43b40 */
		uint32_t reserved_53[47];
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_fifo_wm p2_axi4_wd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43c00 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_fc_control p2_axi4_wd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43c04 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_comm_count_control p2_axi4_wd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43c08 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_count_control p2_axi4_wd_ch_reg_reg_brg_count_control; /* offset : 0x43c0c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43c10 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_wd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43c14 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43c18 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_wd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43c1c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43c20 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_wd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43c24 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43c28 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_wd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43c2c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1 p2_axi4_wd_ch_reg_reg_brg_interrupt1; /* offset : 0x43c30 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt1_mask p2_axi4_wd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43c34 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2 p2_axi4_wd_ch_reg_reg_brg_interrupt2; /* offset : 0x43c38 */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_interrupt2_mask p2_axi4_wd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43c3c */
		union aw_ucie_p2_axi4_wd_ch_reg_reg_brg_credit p2_axi4_wd_ch_reg_reg_brg_credit; /* offset : 0x43c40 */
		uint32_t reserved_54[47];
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_fifo_wm p2_axi4_wr_ch_reg_reg_brg_fifo_wm; /* offset : 0x43d00 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_fc_control p2_axi4_wr_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43d04 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_comm_count_control p2_axi4_wr_ch_reg_reg_brg_comm_count_control; /* offset : 0x43d08 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_count_control p2_axi4_wr_ch_reg_reg_brg_count_control; /* offset : 0x43d0c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43d10 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_wr_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43d14 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43d18 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_wr_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43d1c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43d20 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_wr_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43d24 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43d28 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_wr_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43d2c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1 p2_axi4_wr_ch_reg_reg_brg_interrupt1; /* offset : 0x43d30 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt1_mask p2_axi4_wr_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43d34 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2 p2_axi4_wr_ch_reg_reg_brg_interrupt2; /* offset : 0x43d38 */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_interrupt2_mask p2_axi4_wr_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43d3c */
		union aw_ucie_p2_axi4_wr_ch_reg_reg_brg_credit p2_axi4_wr_ch_reg_reg_brg_credit; /* offset : 0x43d40 */
		uint32_t reserved_55[47];
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_fifo_wm p2_axi4_ar_ch_reg_reg_brg_fifo_wm; /* offset : 0x43e00 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_fc_control p2_axi4_ar_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43e04 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_comm_count_control p2_axi4_ar_ch_reg_reg_brg_comm_count_control; /* offset : 0x43e08 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_count_control p2_axi4_ar_ch_reg_reg_brg_count_control; /* offset : 0x43e0c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43e10 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_ar_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43e14 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43e18 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_ar_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43e1c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43e20 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_ar_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43e24 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43e28 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_ar_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43e2c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1 p2_axi4_ar_ch_reg_reg_brg_interrupt1; /* offset : 0x43e30 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt1_mask p2_axi4_ar_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43e34 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2 p2_axi4_ar_ch_reg_reg_brg_interrupt2; /* offset : 0x43e38 */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_interrupt2_mask p2_axi4_ar_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43e3c */
		union aw_ucie_p2_axi4_ar_ch_reg_reg_brg_credit p2_axi4_ar_ch_reg_reg_brg_credit; /* offset : 0x43e40 */
		uint32_t reserved_56[47];
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_fifo_wm p2_axi4_rd_ch_reg_reg_brg_fifo_wm; /* offset : 0x43f00 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_fc_control p2_axi4_rd_ch_reg_reg_brg_rx_fc_control; /* offset : 0x43f04 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_comm_count_control p2_axi4_rd_ch_reg_reg_brg_comm_count_control; /* offset : 0x43f08 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_count_control p2_axi4_rd_ch_reg_reg_brg_count_control; /* offset : 0x43f0c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_hi; /* offset : 0x43f10 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo p2_axi4_rd_ch_reg_reg_brg_tx_stat_trans_counter_lo; /* offset : 0x43f14 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_hi; /* offset : 0x43f18 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo p2_axi4_rd_ch_reg_reg_brg_tx_stat_byte_counter_lo; /* offset : 0x43f1c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_hi; /* offset : 0x43f20 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo p2_axi4_rd_ch_reg_reg_brg_rx_stat_trans_counter_lo; /* offset : 0x43f24 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_hi; /* offset : 0x43f28 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo p2_axi4_rd_ch_reg_reg_brg_rx_stat_byte_counter_lo; /* offset : 0x43f2c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1 p2_axi4_rd_ch_reg_reg_brg_interrupt1; /* offset : 0x43f30 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt1_mask p2_axi4_rd_ch_reg_reg_brg_interrupt1_mask; /* offset : 0x43f34 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2 p2_axi4_rd_ch_reg_reg_brg_interrupt2; /* offset : 0x43f38 */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_interrupt2_mask p2_axi4_rd_ch_reg_reg_brg_interrupt2_mask; /* offset : 0x43f3c */
		union aw_ucie_p2_axi4_rd_ch_reg_reg_brg_credit p2_axi4_rd_ch_reg_reg_brg_credit; /* offset : 0x43f40 */
	};
#endif