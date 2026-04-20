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

union pcie_ctrl_pf0_type0_hdr_device_id_vendor_id_reg {
	struct {
		uint32_t pci_type0_vendor_id:16; /* [15:0] */
		uint32_t pci_type0_device_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_status_command_reg {
	struct {
		uint32_t pci_type0_io_en:1; /* [0:0] */
		uint32_t pci_type0_mem_space_en:1; /* [1:1] */
		uint32_t pci_type0_bus_master_en:1; /* [2:2] */
		uint32_t pci_type0_special_cycle_operation:1; /* [3:3] */
		uint32_t pci_type_mwi_enable:1; /* [4:4] */
		uint32_t pci_type_vga_palette_snoop:1; /* [5:5] */
		uint32_t pci_type0_parity_err_en:1; /* [6:6] */
		uint32_t pci_type_idsel_stepping:1; /* [7:7] */
		uint32_t pci_type0_serren:1; /* [8:8] */
		uint32_t rsvdp_9:1; /* [9:9] */
		uint32_t pci_type0_int_en:1; /* [10:10] */
		uint32_t pci_type_reserv:5; /* [15:11] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_17:2; /* [18:17] */
		uint32_t int_status:1; /* [19:19] */
		uint32_t cap_list:1; /* [20:20] */
		uint32_t fast_66mhz_cap:1; /* [21:21] */
		uint32_t rsvdp_22:1; /* [22:22] */
		uint32_t fast_b2b_cap:1; /* [23:23] */
		uint32_t master_dpe:1; /* [24:24] */
		uint32_t dev_sel_timing:2; /* [26:25] */
		uint32_t signaled_target_abort:1; /* [27:27] */
		uint32_t rcvd_target_abort:1; /* [28:28] */
		uint32_t rcvd_master_abort:1; /* [29:29] */
		uint32_t signaled_sys_err:1; /* [30:30] */
		uint32_t detected_parity_err:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_class_code_revision_id {
	struct {
		uint32_t revision_id:8; /* [7:0] */
		uint32_t program_interface:8; /* [15:8] */
		uint32_t subclass_code:8; /* [23:16] */
		uint32_t base_class_code:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bist_header_type_latency_cache_line_size_reg {
	struct {
		uint32_t cache_line_size:8; /* [7:0] */
		uint32_t latency_master_timer:8; /* [15:8] */
		uint32_t header_type:7; /* [22:16] */
		uint32_t multi_func:1; /* [23:23] */
		uint32_t bist:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar0_reg {
	struct {
		uint32_t bar0_mem_io:1; /* [0:0] */
		uint32_t bar0_type:2; /* [2:1] */
		uint32_t bar0_prefetch:1; /* [3:3] */
		uint32_t bar0_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar1_reg {
	struct {
		uint32_t bar1_mem_io:1; /* [0:0] */
		uint32_t bar1_type:2; /* [2:1] */
		uint32_t bar1_prefetch:1; /* [3:3] */
		uint32_t bar1_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar2_reg {
	struct {
		uint32_t bar2_mem_io:1; /* [0:0] */
		uint32_t bar2_type:2; /* [2:1] */
		uint32_t bar2_prefetch:1; /* [3:3] */
		uint32_t bar2_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar3_reg {
	struct {
		uint32_t bar3_mem_io:1; /* [0:0] */
		uint32_t bar3_type:2; /* [2:1] */
		uint32_t bar3_prefetch:1; /* [3:3] */
		uint32_t bar3_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar4_reg {
	struct {
		uint32_t bar4_mem_io:1; /* [0:0] */
		uint32_t bar4_type:2; /* [2:1] */
		uint32_t bar4_prefetch:1; /* [3:3] */
		uint32_t bar4_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_bar5_reg {
	struct {
		uint32_t bar5_mem_io:1; /* [0:0] */
		uint32_t bar5_type:2; /* [2:1] */
		uint32_t bar5_prefetch:1; /* [3:3] */
		uint32_t bar5_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_cardbus_cis_ptr_reg {
	struct {
		uint32_t cardbus_cis_pointer; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_subsystem_id_subsystem_vendor_id_reg {
	struct {
		uint32_t subsys_vendor_id:16; /* [15:0] */
		uint32_t subsys_dev_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_exp_rom_base_addr_reg {
	struct {
		uint32_t rom_bar_enable:1; /* [0:0] */
		uint32_t rom_bar_validation_status:3; /* [3:1] */
		uint32_t rom_bar_validation_details:4; /* [7:4] */
		uint32_t rsvdp_8:3; /* [10:8] */
		uint32_t exp_rom_base_address:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_pci_cap_ptr_reg {
	struct {
		uint32_t cap_pointer:8; /* [7:0] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_max_latency_min_grant_interrupt_pin_interrupt_line_reg {
	struct {
		uint32_t int_line:8; /* [7:0] */
		uint32_t int_pin:8; /* [15:8] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pm_cap_cap_id_nxt_ptr_reg {
	struct {
		uint32_t pm_cap_id:8; /* [7:0] */
		uint32_t pm_next_pointer:8; /* [15:8] */
		uint32_t pm_spec_ver:3; /* [18:16] */
		uint32_t pme_clk:1; /* [19:19] */
		uint32_t reserved_bit_0:1;
		uint32_t dsi:1; /* [21:21] */
		uint32_t aux_curr:3; /* [24:22] */
		uint32_t d1_support:1; /* [25:25] */
		uint32_t d2_support:1; /* [26:26] */
		uint32_t pme_support:5; /* [31:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pm_cap_con_status_reg {
	struct {
		uint32_t power_state:2; /* [1:0] */
		uint32_t rsvdp_2:1; /* [2:2] */
		uint32_t no_soft_rst:1; /* [3:3] */
		uint32_t rsvdp_4:4; /* [7:4] */
		uint32_t pme_enable:1; /* [8:8] */
		uint32_t data_select:4; /* [12:9] */
		uint32_t data_scale:2; /* [14:13] */
		uint32_t pme_status:1; /* [15:15] */
		uint32_t rsvdp_16:6; /* [21:16] */
		uint32_t b2_b3_support:1; /* [22:22] */
		uint32_t bus_pwr_clk_con_en:1; /* [23:23] */
		uint32_t data_reg_add_info:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg {
	struct {
		uint32_t pcie_cap_id:8; /* [7:0] */
		uint32_t pcie_cap_next_ptr:8; /* [15:8] */
		uint32_t pcie_cap_reg:4; /* [19:16] */
		uint32_t pcie_dev_port_type:4; /* [23:20] */
		uint32_t pcie_slot_imp:1; /* [24:24] */
		uint32_t pcie_int_msg_num:5; /* [29:25] */
		uint32_t rsvd:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_device_capabilities_reg {
	struct {
		uint32_t pcie_cap_max_payload_size:3; /* [2:0] */
		uint32_t pcie_cap_phantom_func_support:2; /* [4:3] */
		uint32_t pcie_cap_ext_tag_supp:1; /* [5:5] */
		uint32_t pcie_cap_ep_l0s_accpt_latency:3; /* [8:6] */
		uint32_t pcie_cap_ep_l1_accpt_latency:3; /* [11:9] */
		uint32_t rsvdp_12:3; /* [14:12] */
		uint32_t pcie_cap_role_based_err_report:1; /* [15:15] */
		uint32_t rsvdp_16:1; /* [16:16] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_cap_cap_slot_pwr_lmt_value:8; /* [25:18] */
		uint32_t pcie_cap_cap_slot_pwr_lmt_scale:2; /* [27:26] */
		uint32_t pcie_cap_flr_cap:1; /* [28:28] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_cap_tee_io_supported:1; /* [30:30] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_device_control_device_status {
	struct {
		uint32_t pcie_cap_corr_err_report_en:1; /* [0:0] */
		uint32_t pcie_cap_non_fatal_err_report_en:1; /* [1:1] */
		uint32_t pcie_cap_fatal_err_report_en:1; /* [2:2] */
		uint32_t pcie_cap_unsupport_req_rep_en:1; /* [3:3] */
		uint32_t pcie_cap_en_rel_order:1; /* [4:4] */
		uint32_t pcie_cap_max_payload_size_cs:3; /* [7:5] */
		uint32_t pcie_cap_ext_tag_en:1; /* [8:8] */
		uint32_t pcie_cap_phantom_func_en:1; /* [9:9] */
		uint32_t pcie_cap_aux_power_pm_en:1; /* [10:10] */
		uint32_t pcie_cap_en_no_snoop:1; /* [11:11] */
		uint32_t pcie_cap_max_read_req_size:3; /* [14:12] */
		uint32_t pcie_cap_initiate_flr:1; /* [15:15] */
		uint32_t pcie_cap_corr_err_detected:1; /* [16:16] */
		uint32_t pcie_cap_non_fatal_err_detected:1; /* [17:17] */
		uint32_t pcie_cap_fatal_err_detected:1; /* [18:18] */
		uint32_t pcie_cap_unsupported_req_detected:1; /* [19:19] */
		uint32_t pcie_cap_aux_power_detected:1; /* [20:20] */
		uint32_t pcie_cap_trans_pending:1; /* [21:21] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_link_capabilities_reg {
	struct {
		uint32_t pcie_cap_max_link_speed:4; /* [3:0] */
		uint32_t pcie_cap_max_link_width:6; /* [9:4] */
		uint32_t pcie_cap_active_state_link_pm_support:2; /* [11:10] */
		uint32_t pcie_cap_l0s_exit_latency:3; /* [14:12] */
		uint32_t pcie_cap_l1_exit_latency:3; /* [17:15] */
		uint32_t pcie_cap_clock_power_man:1; /* [18:18] */
		uint32_t pcie_cap_surprise_down_err_rep_cap:1; /* [19:19] */
		uint32_t pcie_cap_dll_active_rep_cap:1; /* [20:20] */
		uint32_t pcie_cap_link_bw_not_cap:1; /* [21:21] */
		uint32_t pcie_cap_aspm_opt_compliance:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t pcie_cap_port_num:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_link_control_link_status_reg {
	struct {
		uint32_t pcie_cap_active_state_link_pm_control:2; /* [1:0] */
		uint32_t rsvdp_2:1; /* [2:2] */
		uint32_t pcie_cap_rcb:1; /* [3:3] */
		uint32_t pcie_cap_link_disable:1; /* [4:4] */
		uint32_t pcie_cap_retrain_link:1; /* [5:5] */
		uint32_t pcie_cap_common_clk_config:1; /* [6:6] */
		uint32_t pcie_cap_extended_synch:1; /* [7:7] */
		uint32_t pcie_cap_en_clk_power_man:1; /* [8:8] */
		uint32_t pcie_cap_hw_auto_width_disable:1; /* [9:9] */
		uint32_t pcie_cap_link_bw_man_int_en:1; /* [10:10] */
		uint32_t pcie_cap_link_auto_bw_int_en:1; /* [11:11] */
		uint32_t reserved_bit_0:2;
		uint32_t pcie_cap_drs_signaling_control:2; /* [15:14] */
		uint32_t pcie_cap_link_speed:4; /* [19:16] */
		uint32_t pcie_cap_nego_link_width:6; /* [25:20] */
		uint32_t rsvdp_26:1; /* [26:26] */
		uint32_t pcie_cap_link_training:1; /* [27:27] */
		uint32_t pcie_cap_slot_clk_config:1; /* [28:28] */
		uint32_t pcie_cap_dll_active:1; /* [29:29] */
		uint32_t pcie_cap_link_bw_man_status:1; /* [30:30] */
		uint32_t pcie_cap_link_auto_bw_status:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_device_capabilities2_reg {
	struct {
		uint32_t pcie_cap_cpl_timeout_range:4; /* [3:0] */
		uint32_t pcie_cap_cpl_timeout_disable_support:1; /* [4:4] */
		uint32_t pcie_cap_ari_forward_support:1; /* [5:5] */
		uint32_t pcie_cap_atomic_routing_supp:1; /* [6:6] */
		uint32_t pcie_cap_32_atomic_cpl_supp:1; /* [7:7] */
		uint32_t pcie_cap_64_atomic_cpl_supp:1; /* [8:8] */
		uint32_t pcie_cap_128_cas_cpl_supp:1; /* [9:9] */
		uint32_t pcie_cap_no_ro_en_pr2pr_par:1; /* [10:10] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_cap_tph_cmplt_support_0:1; /* [12:12] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_cap2_ln_sys_cls:2; /* [15:14] */
		uint32_t pcie_cap2_10_bit_tag_comp_support:1; /* [16:16] */
		uint32_t pcie_cap2_10_bit_tag_req_support:1; /* [17:17] */
		uint32_t reserved_bit_2:2;
		uint32_t pcie_cap2_cfg_extnd_fmt_support:1; /* [20:20] */
		uint32_t pcie_cap2_cfg_end2end_tlp_prfx_support:1; /* [21:21] */
		uint32_t pcie_cap2_cfg_max_end2end_tlp_prfxs:2; /* [23:22] */
		uint32_t reserved_bit_3:3;
		uint32_t rsvdp_27:1; /* [27:27] */
		uint32_t pcie_cap_dmwr_cpl_supp:1; /* [28:28] */
		uint32_t pcie_cap_dmwr_len_supp:2; /* [30:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_device_control2_device_status2_reg {
	struct {
		uint32_t pcie_cap_cpl_timeout_value:4; /* [3:0] */
		uint32_t pcie_cap_cpl_timeout_disable:1; /* [4:4] */
		uint32_t pcie_cap_ari_forward_support_cs:1; /* [5:5] */
		uint32_t reserved_bit_0:2;
		uint32_t pcie_cap_ido_req_en:1; /* [8:8] */
		uint32_t pcie_cap_ido_cpl_en:1; /* [9:9] */
		uint32_t reserved_bit_1:5;
		uint32_t pcie_ctrl2_cfg_end2end_tlp_pfx_blck:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_link_capabilities2_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t pcie_cap_support_link_speed_vector:7; /* [7:1] */
		uint32_t pcie_cap_cross_link_support:1; /* [8:8] */
		uint32_t pcie_cap_lwr_skp_os_gen_sup:7; /* [15:9] */
		uint32_t pcie_cap_lwr_skp_os_rcv_sup:7; /* [22:16] */
		uint32_t pcie_cap_retimer_pre_det_support:1; /* [23:23] */
		uint32_t pcie_cap_two_retimers_pre_det_support:1; /* [24:24] */
		uint32_t rsvdp_25:6; /* [30:25] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_link_control2_link_status2_reg {
	struct {
		uint32_t pcie_cap_target_link_speed:4; /* [3:0] */
		uint32_t pcie_cap_enter_compliance:1; /* [4:4] */
		uint32_t pcie_cap_hw_auto_speed_disable:1; /* [5:5] */
		uint32_t pcie_cap_sel_deemphasis:1; /* [6:6] */
		uint32_t pcie_cap_tx_margin:3; /* [9:7] */
		uint32_t pcie_cap_enter_modified_compliance:1; /* [10:10] */
		uint32_t pcie_cap_compliance_sos:1; /* [11:11] */
		uint32_t pcie_cap_compliance_preset:4; /* [15:12] */
		uint32_t pcie_cap_curr_deemphasis:1; /* [16:16] */
		uint32_t pcie_cap_eq_cpl:1; /* [17:17] */
		uint32_t pcie_cap_eq_cpl_p1:1; /* [18:18] */
		uint32_t pcie_cap_eq_cpl_p2:1; /* [19:19] */
		uint32_t pcie_cap_eq_cpl_p3:1; /* [20:20] */
		uint32_t pcie_cap_link_eq_req:1; /* [21:21] */
		uint32_t pcie_cap_retimer_pre_det:1; /* [22:22] */
		uint32_t pcie_cap_two_retimers_pre_det:1; /* [23:23] */
		uint32_t pcie_cap_crosslink_resolution:2; /* [25:24] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_27:1; /* [27:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_pci_msix_cap_id_next_ctrl_reg {
	struct {
		uint32_t pci_msix_cap_id:8; /* [7:0] */
		uint32_t pci_msix_cap_next_offset:8; /* [15:8] */
		uint32_t pci_msix_table_size:11; /* [26:16] */
		uint32_t rsvdp_27:3; /* [29:27] */
		uint32_t pci_msix_function_mask:1; /* [30:30] */
		uint32_t pci_msix_enable:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_msix_table_offset_reg {
	struct {
		uint32_t pci_msix_bir:3; /* [2:0] */
		uint32_t pci_msix_table_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_msix_pba_offset_reg {
	struct {
		uint32_t pci_msix_pba_bir:3; /* [2:0] */
		uint32_t pci_msix_pba_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_aer_ext_cap_hdr_off {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_uncorr_err_status_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_status:1; /* [4:4] */
		uint32_t surprise_down_err_status:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_status:1; /* [12:12] */
		uint32_t fc_protocol_err_status:1; /* [13:13] */
		uint32_t cmplt_timeout_err_status:1; /* [14:14] */
		uint32_t cmplt_abort_err_status:1; /* [15:15] */
		uint32_t unexp_cmplt_err_status:1; /* [16:16] */
		uint32_t rec_overflow_err_status:1; /* [17:17] */
		uint32_t malf_tlp_err_status:1; /* [18:18] */
		uint32_t ecrc_err_status:1; /* [19:19] */
		uint32_t unsupported_req_err_status:1; /* [20:20] */
		uint32_t acs_violation_status:1; /* [21:21] */
		uint32_t internal_err_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t reserved_bit_0:1;
		uint32_t tlp_prfx_blocked_err_status:1; /* [25:25] */
		uint32_t reserved_bit_1:2;
		uint32_t ide_check_failed_status:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_status:1; /* [29:29] */
		uint32_t pcrc_check_failed_status:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_uncorr_err_mask_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_mask:1; /* [4:4] */
		uint32_t surprise_down_err_mask:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_mask:1; /* [12:12] */
		uint32_t fc_protocol_err_mask:1; /* [13:13] */
		uint32_t cmplt_timeout_err_mask:1; /* [14:14] */
		uint32_t cmplt_abort_err_mask:1; /* [15:15] */
		uint32_t unexp_cmplt_err_mask:1; /* [16:16] */
		uint32_t rec_overflow_err_mask:1; /* [17:17] */
		uint32_t malf_tlp_err_mask:1; /* [18:18] */
		uint32_t ecrc_err_mask:1; /* [19:19] */
		uint32_t unsupported_req_err_mask:1; /* [20:20] */
		uint32_t acs_violation_mask:1; /* [21:21] */
		uint32_t internal_err_mask:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t atomic_egress_blocked_err_mask:1; /* [24:24] */
		uint32_t tlp_prfx_blocked_err_mask:1; /* [25:25] */
		uint32_t rsvdp_26:1; /* [26:26] */
		uint32_t dmwr_egress_blocked_err_mask:1; /* [27:27] */
		uint32_t ide_check_failed_mask:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_mask:1; /* [29:29] */
		uint32_t pcrc_check_failed_mask:1; /* [30:30] */
		uint32_t tlp_translation_egress_blocked_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_uncorr_err_sev_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_severity:1; /* [4:4] */
		uint32_t surprise_down_err_svrity:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_severity:1; /* [12:12] */
		uint32_t fc_protocol_err_severity:1; /* [13:13] */
		uint32_t cmplt_timeout_err_severity:1; /* [14:14] */
		uint32_t cmplt_abort_err_severity:1; /* [15:15] */
		uint32_t unexp_cmplt_err_severity:1; /* [16:16] */
		uint32_t rec_overflow_err_severity:1; /* [17:17] */
		uint32_t malf_tlp_err_severity:1; /* [18:18] */
		uint32_t ecrc_err_severity:1; /* [19:19] */
		uint32_t unsupported_req_err_severity:1; /* [20:20] */
		uint32_t acs_violation_severity:1; /* [21:21] */
		uint32_t internal_err_severity:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t reserved_bit_0:1;
		uint32_t tlp_prfx_blocked_err_severity:1; /* [25:25] */
		uint32_t reserved_bit_1:1;
		uint32_t dmwr_egress_blocked_err_severity:1; /* [27:27] */
		uint32_t ide_check_failed_sev:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_sev:1; /* [29:29] */
		uint32_t pcrc_check_failed_sev:1; /* [30:30] */
		uint32_t tlp_translation_egress_blocked_sev:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_corr_err_status_off {
	struct {
		uint32_t rx_err_status:1; /* [0:0] */
		uint32_t rsvdp_1:5; /* [5:1] */
		uint32_t bad_tlp_status:1; /* [6:6] */
		uint32_t bad_dllp_status:1; /* [7:7] */
		uint32_t replay_no_roleover_status:1; /* [8:8] */
		uint32_t rsvdp_9:3; /* [11:9] */
		uint32_t rpl_timer_timeout_status:1; /* [12:12] */
		uint32_t advisory_non_fatal_err_status:1; /* [13:13] */
		uint32_t corrected_int_err_status:1; /* [14:14] */
		uint32_t header_log_overflow_status:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_corr_err_mask_off {
	struct {
		uint32_t rx_err_mask:1; /* [0:0] */
		uint32_t rsvdp_1:5; /* [5:1] */
		uint32_t bad_tlp_mask:1; /* [6:6] */
		uint32_t bad_dllp_mask:1; /* [7:7] */
		uint32_t replay_no_roleover_mask:1; /* [8:8] */
		uint32_t rsvdp_9:3; /* [11:9] */
		uint32_t rpl_timer_timeout_mask:1; /* [12:12] */
		uint32_t advisory_non_fatal_err_mask:1; /* [13:13] */
		uint32_t corrected_int_err_mask:1; /* [14:14] */
		uint32_t header_log_overflow_mask:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_adv_err_cap_ctrl_off {
	struct {
		uint32_t first_err_pointer:5; /* [4:0] */
		uint32_t ecrc_gen_cap:1; /* [5:5] */
		uint32_t ecrc_gen_en:1; /* [6:6] */
		uint32_t ecrc_check_cap:1; /* [7:7] */
		uint32_t ecrc_check_en:1; /* [8:8] */
		uint32_t multiple_header_cap:1; /* [9:9] */
		uint32_t multiple_header_en:1; /* [10:10] */
		uint32_t tlp_prfx_log_present:1; /* [11:11] */
		uint32_t cto_prfx_hdr_log_cap:1; /* [12:12] */
		uint32_t reserved_bit_0:11;
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_hdr_log_0_off {
	struct {
		uint32_t first_dword_first_byte:8; /* [7:0] */
		uint32_t first_dword_second_byte:8; /* [15:8] */
		uint32_t first_dword_third_byte:8; /* [23:16] */
		uint32_t first_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_hdr_log_1_off {
	struct {
		uint32_t second_dword_first_byte:8; /* [7:0] */
		uint32_t second_dword_second_byte:8; /* [15:8] */
		uint32_t second_dword_third_byte:8; /* [23:16] */
		uint32_t second_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_hdr_log_2_off {
	struct {
		uint32_t third_dword_first_byte:8; /* [7:0] */
		uint32_t third_dword_second_byte:8; /* [15:8] */
		uint32_t third_dword_third_byte:8; /* [23:16] */
		uint32_t third_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_hdr_log_3_off {
	struct {
		uint32_t fourth_dword_first_byte:8; /* [7:0] */
		uint32_t fourth_dword_second_byte:8; /* [15:8] */
		uint32_t fourth_dword_third_byte:8; /* [23:16] */
		uint32_t fourth_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_1_off {
	struct {
		uint32_t cfg_tlp_pfx_log_1_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_1_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_1_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_1_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_2_off {
	struct {
		uint32_t cfg_tlp_pfx_log_2_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_2_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_2_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_2_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_3_off {
	struct {
		uint32_t cfg_tlp_pfx_log_3_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_3_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_3_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_3_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_4_off {
	struct {
		uint32_t cfg_tlp_pfx_log_4_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_4_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_4_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_4_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ari_cap_ari_base {
	struct {
		uint32_t ari_pcie_extended_cap_id:16; /* [15:0] */
		uint32_t ari_cap_version:4; /* [19:16] */
		uint32_t ari_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ari_cap_cap_reg {
	struct {
		uint32_t ari_mfvc_fun_grp_cap:1; /* [0:0] */
		uint32_t ari_acs_fun_grp_cap:1; /* [1:1] */
		uint32_t rsvdp_2:6; /* [7:2] */
		uint32_t ari_next_fun_num:8; /* [15:8] */
		uint32_t ari_mfvc_fun_grp_en:1; /* [16:16] */
		uint32_t ari_acs_fun_grp_en:1; /* [17:17] */
		uint32_t rsvdp_18:2; /* [19:18] */
		uint32_t ari_fun_grp:3; /* [22:20] */
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_header_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_link_control3_reg {
	struct {
		uint32_t perform_eq:1; /* [0:0] */
		uint32_t eq_req_int_en:1; /* [1:1] */
		uint32_t rsvdp_2:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_lane_err_status_reg {
	struct {
		uint32_t lane_err_status:16; /* [15:0] */
		uint32_t rsvdp_lane_err_status:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_0ch_reg {
	struct {
		uint32_t dsp_tx_preset0:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint0:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset0:4; /* [11:8] */
		uint32_t usp_rx_preset_hint0:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset1:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint1:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset1:4; /* [27:24] */
		uint32_t usp_rx_preset_hint1:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_10h_reg {
	struct {
		uint32_t dsp_tx_preset2:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint2:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset2:4; /* [11:8] */
		uint32_t usp_rx_preset_hint2:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset3:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint3:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset3:4; /* [27:24] */
		uint32_t usp_rx_preset_hint3:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_14h_reg {
	struct {
		uint32_t dsp_tx_preset4:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint4:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset4:4; /* [11:8] */
		uint32_t usp_rx_preset_hint4:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset5:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint5:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset5:4; /* [27:24] */
		uint32_t usp_rx_preset_hint5:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_18h_reg {
	struct {
		uint32_t dsp_tx_preset6:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint6:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset6:4; /* [11:8] */
		uint32_t usp_rx_preset_hint6:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset7:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint7:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset7:4; /* [27:24] */
		uint32_t usp_rx_preset_hint7:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_1ch_reg {
	struct {
		uint32_t dsp_tx_preset8:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint8:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset8:4; /* [11:8] */
		uint32_t usp_rx_preset_hint8:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset9:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint9:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset9:4; /* [27:24] */
		uint32_t usp_rx_preset_hint9:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_20h_reg {
	struct {
		uint32_t dsp_tx_preset10:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint10:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset10:4; /* [11:8] */
		uint32_t usp_rx_preset_hint10:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset11:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint11:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset11:4; /* [27:24] */
		uint32_t usp_rx_preset_hint11:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_24h_reg {
	struct {
		uint32_t dsp_tx_preset12:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint12:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset12:4; /* [11:8] */
		uint32_t usp_rx_preset_hint12:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset13:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint13:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset13:4; /* [27:24] */
		uint32_t usp_rx_preset_hint13:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_28h_reg {
	struct {
		uint32_t dsp_tx_preset14:4; /* [3:0] */
		uint32_t dsp_rx_preset_hint14:3; /* [6:4] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t usp_tx_preset14:4; /* [11:8] */
		uint32_t usp_rx_preset_hint14:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t dsp_tx_preset15:4; /* [19:16] */
		uint32_t dsp_rx_preset_hint15:3; /* [22:20] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t usp_tx_preset15:4; /* [27:24] */
		uint32_t usp_rx_preset_hint15:3; /* [30:28] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_ext_cap_hdr_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_capability_reg {
	struct {
		uint32_t rsvdp_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_control_reg {
	struct {
		uint32_t rsvdp_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_status_reg {
	struct {
		uint32_t eq_16g_cpl:1; /* [0:0] */
		uint32_t eq_16g_cpl_p1:1; /* [1:1] */
		uint32_t eq_16g_cpl_p2:1; /* [2:2] */
		uint32_t eq_16g_cpl_p3:1; /* [3:3] */
		uint32_t link_eq_16g_req:1; /* [4:4] */
		uint32_t rsvdp_5:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_lc_dpar_status_reg {
	struct {
		uint32_t lc_dpar_status:16; /* [15:0] */
		uint32_t rsvdp_lc_dpar_status:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_first_retimer_dpar_status_reg {
	struct {
		uint32_t first_retimer_dpar_status:16; /* [15:0] */
		uint32_t rsvdp_first_retimer_dpar_status:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_second_retimer_dpar_status_reg {
	struct {
		uint32_t second_retimer_dpar_status:16; /* [15:0] */
		uint32_t rsvdp_second_retimer_dpar_status:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_20h_reg {
	struct {
		uint32_t dsp_16g_tx_preset0:4; /* [3:0] */
		uint32_t usp_16g_tx_preset0:4; /* [7:4] */
		uint32_t dsp_16g_tx_preset1:4; /* [11:8] */
		uint32_t usp_16g_tx_preset1:4; /* [15:12] */
		uint32_t dsp_16g_tx_preset2:4; /* [19:16] */
		uint32_t usp_16g_tx_preset2:4; /* [23:20] */
		uint32_t dsp_16g_tx_preset3:4; /* [27:24] */
		uint32_t usp_16g_tx_preset3:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_24h_reg {
	struct {
		uint32_t dsp_16g_tx_preset4:4; /* [3:0] */
		uint32_t usp_16g_tx_preset4:4; /* [7:4] */
		uint32_t dsp_16g_tx_preset5:4; /* [11:8] */
		uint32_t usp_16g_tx_preset5:4; /* [15:12] */
		uint32_t dsp_16g_tx_preset6:4; /* [19:16] */
		uint32_t usp_16g_tx_preset6:4; /* [23:20] */
		uint32_t dsp_16g_tx_preset7:4; /* [27:24] */
		uint32_t usp_16g_tx_preset7:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_28h_reg {
	struct {
		uint32_t dsp_16g_tx_preset8:4; /* [3:0] */
		uint32_t usp_16g_tx_preset8:4; /* [7:4] */
		uint32_t dsp_16g_tx_preset9:4; /* [11:8] */
		uint32_t usp_16g_tx_preset9:4; /* [15:12] */
		uint32_t dsp_16g_tx_preset10:4; /* [19:16] */
		uint32_t usp_16g_tx_preset10:4; /* [23:20] */
		uint32_t dsp_16g_tx_preset11:4; /* [27:24] */
		uint32_t usp_16g_tx_preset11:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_2ch_reg {
	struct {
		uint32_t dsp_16g_tx_preset12:4; /* [3:0] */
		uint32_t usp_16g_tx_preset12:4; /* [7:4] */
		uint32_t dsp_16g_tx_preset13:4; /* [11:8] */
		uint32_t usp_16g_tx_preset13:4; /* [15:12] */
		uint32_t dsp_16g_tx_preset14:4; /* [19:16] */
		uint32_t usp_16g_tx_preset14:4; /* [23:20] */
		uint32_t dsp_16g_tx_preset15:4; /* [27:24] */
		uint32_t usp_16g_tx_preset15:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_ext_cap_hdr_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_port_capabilities_status_reg {
	struct {
		uint32_t margining_uses_driver_software:1; /* [0:0] */
		uint32_t rsvdp_1:15; /* [15:1] */
		uint32_t margining_ready:1; /* [16:16] */
		uint32_t margining_software_ready:1; /* [17:17] */
		uint32_t rsvdp_18:14; /* [31:18] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status0_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status1_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status2_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status3_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status4_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status5_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status6_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status7_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status8_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status9_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status10_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status11_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status12_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status13_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status14_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status15_reg {
	struct {
		uint32_t receiver_number:3; /* [2:0] */
		uint32_t margin_type:3; /* [5:3] */
		uint32_t usage_model:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t margin_payload:8; /* [15:8] */
		uint32_t receiver_number_status:3; /* [18:16] */
		uint32_t margin_type_status:3; /* [21:19] */
		uint32_t usage_model_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t margin_payload_status:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_ext_cap_hdr_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_capability_reg {
	struct {
		uint32_t eq_bypass_highest_rate_support:1; /* [0:0] */
		uint32_t no_eq_needed_support:1; /* [1:1] */
		uint32_t rsvdp_2:6; /* [7:2] */
		uint32_t mod_ts_pcie_support:1; /* [8:8] */
		uint32_t mod_ts_traing_set_msg_support:1; /* [9:9] */
		uint32_t reserved_bit_0:1;
		uint32_t mod_ts_rsvd_usage_mode:5; /* [15:11] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_control_reg {
	struct {
		uint32_t eq_bypass_highest_rate_disable:1; /* [0:0] */
		uint32_t no_eq_needed_disable:1; /* [1:1] */
		uint32_t rsvdp_2:6; /* [7:2] */
		uint32_t mod_ts_usage_mode_select:3; /* [10:8] */
		uint32_t rsvdp_11:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_status_reg {
	struct {
		uint32_t eq_32g_cpl:1; /* [0:0] */
		uint32_t eq_32g_cpl_p1:1; /* [1:1] */
		uint32_t eq_32g_cpl_p2:1; /* [2:2] */
		uint32_t eq_32g_cpl_p3:1; /* [3:3] */
		uint32_t link_eq_32g_req:1; /* [4:4] */
		uint32_t mod_ts_rcvd:1; /* [5:5] */
		uint32_t rx_enh_link_behavior_ctrl:2; /* [7:6] */
		uint32_t tx_precoding_on:1; /* [8:8] */
		uint32_t tx_precode_req:1; /* [9:9] */
		uint32_t no_eq_needed_rcvd:1; /* [10:10] */
		uint32_t rsvdp_11:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_rcvd_mod_ts_data1_reg {
	struct {
		uint32_t rcvd_mod_ts_usage_mode:3; /* [2:0] */
		uint32_t rcvd_mod_ts_info1:13; /* [15:3] */
		uint32_t rcvd_mod_ts_vender_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_rcvd_mod_ts_data2_reg {
	struct {
		uint32_t rcvd_mod_ts_info2:24; /* [23:0] */
		uint32_t rcvd_alt_protocol_nego_status:2; /* [25:24] */
		uint32_t rsvdp_26:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_tx_mod_ts_data1_reg {
	struct {
		uint32_t tx_mod_ts_usage_mode:3; /* [2:0] */
		uint32_t tx_mod_ts_info1:13; /* [15:3] */
		uint32_t tx_mod_ts_vender_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_tx_mod_ts_data2_reg {
	struct {
		uint32_t tx_mod_ts_info2:24; /* [23:0] */
		uint32_t tx_alt_protocol_nego_status:2; /* [25:24] */
		uint32_t rsvdp_26:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_20h_reg {
	struct {
		uint32_t dsp_32g_tx_preset0:4; /* [3:0] */
		uint32_t usp_32g_tx_preset0:4; /* [7:4] */
		uint32_t dsp_32g_tx_preset1:4; /* [11:8] */
		uint32_t usp_32g_tx_preset1:4; /* [15:12] */
		uint32_t dsp_32g_tx_preset2:4; /* [19:16] */
		uint32_t usp_32g_tx_preset2:4; /* [23:20] */
		uint32_t dsp_32g_tx_preset3:4; /* [27:24] */
		uint32_t usp_32g_tx_preset3:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_24h_reg {
	struct {
		uint32_t dsp_32g_tx_preset4:4; /* [3:0] */
		uint32_t usp_32g_tx_preset4:4; /* [7:4] */
		uint32_t dsp_32g_tx_preset5:4; /* [11:8] */
		uint32_t usp_32g_tx_preset5:4; /* [15:12] */
		uint32_t dsp_32g_tx_preset6:4; /* [19:16] */
		uint32_t usp_32g_tx_preset6:4; /* [23:20] */
		uint32_t dsp_32g_tx_preset7:4; /* [27:24] */
		uint32_t usp_32g_tx_preset7:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_28h_reg {
	struct {
		uint32_t dsp_32g_tx_preset8:4; /* [3:0] */
		uint32_t usp_32g_tx_preset8:4; /* [7:4] */
		uint32_t dsp_32g_tx_preset9:4; /* [11:8] */
		uint32_t usp_32g_tx_preset9:4; /* [15:12] */
		uint32_t dsp_32g_tx_preset10:4; /* [19:16] */
		uint32_t usp_32g_tx_preset10:4; /* [23:20] */
		uint32_t dsp_32g_tx_preset11:4; /* [27:24] */
		uint32_t usp_32g_tx_preset11:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_2ch_reg {
	struct {
		uint32_t dsp_32g_tx_preset12:4; /* [3:0] */
		uint32_t usp_32g_tx_preset12:4; /* [7:4] */
		uint32_t dsp_32g_tx_preset13:4; /* [11:8] */
		uint32_t usp_32g_tx_preset13:4; /* [15:12] */
		uint32_t dsp_32g_tx_preset14:4; /* [19:16] */
		uint32_t usp_32g_tx_preset14:4; /* [23:20] */
		uint32_t dsp_32g_tx_preset15:4; /* [27:24] */
		uint32_t usp_32g_tx_preset15:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_base_reg {
	struct {
		uint32_t sriov_pcie_extended_cap_id:16; /* [15:0] */
		uint32_t sriov_cap_version:4; /* [19:16] */
		uint32_t sriov_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_capabilities_reg {
	struct {
		uint32_t sriov_vf_migration_cap:1; /* [0:0] */
		uint32_t sriov_ari_cap_hier_preserved:1; /* [1:1] */
		uint32_t sriov_vf_10bit_tag_req_cap:1; /* [2:2] */
		uint32_t rsvdp_3:18; /* [20:3] */
		uint32_t sriov_vf_migration_int_msg_num:10; /* [30:21] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_status_control_reg {
	struct {
		uint32_t sriov_vf_enable:1; /* [0:0] */
		uint32_t sriov_vf_migration_enable:1; /* [1:1] */
		uint32_t sriov_vf_migration_int_enable:1; /* [2:2] */
		uint32_t sriov_vf_mse:1; /* [3:3] */
		uint32_t sriov_ari_capable_hier:1; /* [4:4] */
		uint32_t sriov_vf_10bit_tag_req_enable:1; /* [5:5] */
		uint32_t rsvdp_6:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_total_vfs_initial_vfs_reg {
	struct {
		uint32_t sriov_initial_vfs:16; /* [15:0] */
		uint32_t sriov_total_vfs:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_num_vfs {
	struct {
		uint32_t sriov_num_vfs:16; /* [15:0] */
		uint32_t sriov_fdl:8; /* [23:16] */
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_vf_offset_position {
	struct {
		uint32_t sriov_vf_offset:16; /* [15:0] */
		uint32_t sriov_vf_stride:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_vf_device_id_reg {
	struct {
		uint32_t rsvdp_0:16; /* [15:0] */
		uint32_t sriov_vf_device_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sup_page_sizes_reg {
	struct {
		uint32_t sriov_sup_page_size; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_system_page_size_reg {
	struct {
		uint32_t system_page_size; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar0_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t sriov_vf_bar0_type:2; /* [2:1] */
		uint32_t sriov_vf_bar0_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar0_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar1_reg {
	struct {
		uint32_t rsvdp_sriov_vf_bar1:1; /* [0:0] */
		uint32_t sriov_vf_bar1_type:2; /* [2:1] */
		uint32_t sriov_vf_bar1_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar1_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar2_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t sriov_vf_bar2_type:2; /* [2:1] */
		uint32_t sriov_vf_bar2_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar2_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar3_reg {
	struct {
		uint32_t rsvdp_sriov_vf_bar3:1; /* [0:0] */
		uint32_t sriov_vf_bar3_type:2; /* [2:1] */
		uint32_t sriov_vf_bar3_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar3_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar4_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t sriov_vf_bar4_type:2; /* [2:1] */
		uint32_t sriov_vf_bar4_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar4_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_sriov_bar5_reg {
	struct {
		uint32_t rsvdp_sriov_vf_bar5:1; /* [0:0] */
		uint32_t sriov_vf_bar5_type:2; /* [2:1] */
		uint32_t sriov_vf_bar5_prefetch:1; /* [3:3] */
		uint32_t sriov_vf_bar5_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_vf_migration_state_array_reg {
	struct {
		uint32_t sriov_vf_migration_state_bir:3; /* [2:0] */
		uint32_t sriov_vf_migration_state_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_tph_cap_tph_ext_cap_hdr_reg {
	struct {
		uint32_t pcie_ext_cap_id:16; /* [15:0] */
		uint32_t tph_req_cap_ver:4; /* [19:16] */
		uint32_t tph_req_next_ptr:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_tph_cap_tph_req_cap_reg_reg {
	struct {
		uint32_t tph_req_no_st_mode:1; /* [0:0] */
		uint32_t tph_req_cap_int_vec:1; /* [1:1] */
		uint32_t tph_req_device_spec:1; /* [2:2] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t tph_req_extended_tph:1; /* [8:8] */
		uint32_t tph_req_cap_st_table_loc_0:1; /* [9:9] */
		uint32_t tph_req_cap_st_table_loc_1:1; /* [10:10] */
		uint32_t rsvdp_11:5; /* [15:11] */
		uint32_t tph_req_cap_st_table_size:11; /* [26:16] */
		uint32_t rsvdp_27:5; /* [31:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_tph_cap_tph_req_control_reg_reg {
	struct {
		uint32_t tph_req_st_mode_select:3; /* [2:0] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t tph_req_ctrl_req_en:2; /* [9:8] */
		uint32_t rsvdp_10:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ats_cap_ats_cap_hdr_reg {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ats_cap_ats_capabilities_ctrl_reg {
	struct {
		uint32_t invalidate_q_depth:5; /* [4:0] */
		uint32_t page_aligned_req:1; /* [5:5] */
		uint32_t global_inval_spprtd:1; /* [6:6] */
		uint32_t rsvdp_7:9; /* [15:7] */
		uint32_t stu:5; /* [20:16] */
		uint32_t rsvdp_21:10; /* [30:21] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_acs_cap_acs_cap_hdr_reg {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_acs_cap_acs_capabilities_ctrl_reg {
	struct {
		uint32_t acs_src_valid:1; /* [0:0] */
		uint32_t acs_at_block:1; /* [1:1] */
		uint32_t acs_p2p_req_redirect:1; /* [2:2] */
		uint32_t acs_p2p_cpl_redirect:1; /* [3:3] */
		uint32_t acs_usp_forwarding:1; /* [4:4] */
		uint32_t acs_p2p_egress_control:1; /* [5:5] */
		uint32_t acs_direct_translated_p2p:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t acs_egress_ctrl_size:8; /* [15:8] */
		uint32_t acs_src_valid_en:1; /* [16:16] */
		uint32_t acs_at_block_en:1; /* [17:17] */
		uint32_t acs_p2p_req_redirect_en:1; /* [18:18] */
		uint32_t acs_p2p_cpl_redirect_en:1; /* [19:19] */
		uint32_t acs_usp_forwarding_en:1; /* [20:20] */
		uint32_t acs_p2p_egress_control_en:1; /* [21:21] */
		uint32_t acs_direct_translated_p2p_en:1; /* [22:22] */
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_acs_cap_acs_egress_ctrl_vector_reg0 {
	struct {
		uint32_t acs_egress_ctrl_vector_reg0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_prs_ext_cap_prs_ext_cap_hdr_reg {
	struct {
		uint32_t prs_cap_id:16; /* [15:0] */
		uint32_t prs_cap_version:4; /* [19:16] */
		uint32_t prs_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_prs_ext_cap_prs_control_status_reg {
	struct {
		uint32_t prs_enable:1; /* [0:0] */
		uint32_t prs_reset:1; /* [1:1] */
		uint32_t rsvdp_2:14; /* [15:2] */
		uint32_t prs_resp_failure:1; /* [16:16] */
		uint32_t prs_uprgi:1; /* [17:17] */
		uint32_t rsvdp_18:6; /* [23:18] */
		uint32_t prs_stopped:1; /* [24:24] */
		uint32_t rsvdp_25:6; /* [30:25] */
		uint32_t prs_pasid:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_prs_ext_cap_prs_req_capacity_reg {
	struct {
		uint32_t prs_outstanding_capacity; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_prs_ext_cap_prs_req_allocation_reg {
	struct {
		uint32_t prs_outstanding_allocation; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_l1sub_cap_l1sub_cap_header_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_l1sub_cap_l1sub_capability_reg {
	struct {
		uint32_t l1_2_pcipm_support:1; /* [0:0] */
		uint32_t l1_1_pcipm_support:1; /* [1:1] */
		uint32_t l1_2_aspm_support:1; /* [2:2] */
		uint32_t l1_1_aspm_support:1; /* [3:3] */
		uint32_t l1_pmsub_support:1; /* [4:4] */
		uint32_t rsvdp_5:3; /* [7:5] */
		uint32_t comm_mode_support:8; /* [15:8] */
		uint32_t pwr_on_scale_support:2; /* [17:16] */
		uint32_t rsvdp_18:1; /* [18:18] */
		uint32_t pwr_on_value_support:5; /* [23:19] */
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_l1sub_cap_l1sub_control1_reg {
	struct {
		uint32_t l1_2_pcipm_en:1; /* [0:0] */
		uint32_t l1_1_pcipm_en:1; /* [1:1] */
		uint32_t l1_2_aspm_en:1; /* [2:2] */
		uint32_t l1_1_aspm_en:1; /* [3:3] */
		uint32_t rsvdp_4:4; /* [7:4] */
		uint32_t t_common_mode:8; /* [15:8] */
		uint32_t l1_2_th_val:10; /* [25:16] */
		uint32_t rsvdp_26:3; /* [28:26] */
		uint32_t l1_2_th_sca:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_l1sub_cap_l1sub_control2_reg {
	struct {
		uint32_t t_power_on_scale:2; /* [1:0] */
		uint32_t rsvdp_2:1; /* [2:2] */
		uint32_t t_power_on_value:5; /* [7:3] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pasid_cap_pasid_ext_cap_hdr_reg {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pasid_cap_pasid_cap_cntrl_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t execute_permission_supported:1; /* [1:1] */
		uint32_t privileged_mode_supported:1; /* [2:2] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t max_pasid_width:5; /* [12:8] */
		uint32_t rsvdp_13:3; /* [15:13] */
		uint32_t en:1; /* [16:16] */
		uint32_t execute_permission_en:1; /* [17:17] */
		uint32_t privileged_mode_en:1; /* [18:18] */
		uint32_t rsvdp_19:13; /* [31:19] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_ras_des_cap_header_reg {
	struct {
		uint32_t extended_cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_vendor_specific_header_reg {
	struct {
		uint32_t vsec_id:16; /* [15:0] */
		uint32_t vsec_rev:4; /* [19:16] */
		uint32_t vsec_length:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_event_counter_control_reg {
	struct {
		uint32_t event_counter_clear:2; /* [1:0] */
		uint32_t event_counter_enable:3; /* [4:2] */
		uint32_t rsvdp_5:2; /* [6:5] */
		uint32_t event_counter_status:1; /* [7:7] */
		uint32_t event_counter_lane_select:4; /* [11:8] */
		uint32_t rsvdp_12:4; /* [15:12] */
		uint32_t event_counter_event_select:12; /* [27:16] */
		uint32_t rsvdp_28:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_event_counter_data_reg {
	struct {
		uint32_t event_counter_data; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_control_reg {
	struct {
		uint32_t timer_start:1; /* [0:0] */
		uint32_t rsvdp_1:7; /* [7:1] */
		uint32_t time_based_duration_select:8; /* [15:8] */
		uint32_t rsvdp_16:8; /* [23:16] */
		uint32_t time_based_report_select:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_data_reg {
	struct {
		uint32_t time_based_analysis_data; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_data_63_32_reg {
	struct {
		uint32_t time_based_analysis_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj_enable_reg {
	struct {
		uint32_t error_injection0_enable:1; /* [0:0] */
		uint32_t error_injection1_enable:1; /* [1:1] */
		uint32_t error_injection2_enable:1; /* [2:2] */
		uint32_t error_injection3_enable:1; /* [3:3] */
		uint32_t error_injection4_enable:1; /* [4:4] */
		uint32_t error_injection5_enable:1; /* [5:5] */
		uint32_t error_injection6_enable:1; /* [6:6] */
		uint32_t rsvdp_7:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj0_crc_reg {
	struct {
		uint32_t einj0_count:8; /* [7:0] */
		uint32_t einj0_crc_type:4; /* [11:8] */
		uint32_t rsvdp_12:4; /* [15:12] */
		uint32_t reserved_bit_0:3;
		uint32_t rsvdp_19:1; /* [19:19] */
		uint32_t reserved_bit_1:2;
		uint32_t rsvdp_22:2; /* [23:22] */
		uint32_t reserved_bit_2:1;
		uint32_t rsvdp_25:7; /* [31:25] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj1_seqnum_reg {
	struct {
		uint32_t einj1_count:8; /* [7:0] */
		uint32_t einj1_seqnum_type:1; /* [8:8] */
		uint32_t rsvdp_9:7; /* [15:9] */
		uint32_t einj1_bad_seqnum:13; /* [28:16] */
		uint32_t rsvdp_29:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj2_dllp_reg {
	struct {
		uint32_t einj2_count:8; /* [7:0] */
		uint32_t einj2_dllp_type:2; /* [9:8] */
		uint32_t rsvdp_10:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj3_symbol_reg {
	struct {
		uint32_t einj3_count:8; /* [7:0] */
		uint32_t einj3_symbol_type:3; /* [10:8] */
		uint32_t rsvdp_11:21; /* [31:11] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj4_fc_reg {
	struct {
		uint32_t einj4_count:8; /* [7:0] */
		uint32_t einj4_updfc_type:3; /* [10:8] */
		uint32_t rsvdp_11:1; /* [11:11] */
		uint32_t einj4_vc_number:3; /* [14:12] */
		uint32_t rsvdp_15:1; /* [15:15] */
		uint32_t einj4_bad_updfc_value:13; /* [28:16] */
		uint32_t rsvdp_29:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj5_sp_tlp_reg {
	struct {
		uint32_t einj5_count:8; /* [7:0] */
		uint32_t einj5_specified_tlp:1; /* [8:8] */
		uint32_t rsvdp_9:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h0_reg {
	struct {
		uint32_t einj6_compare_point_h0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h1_reg {
	struct {
		uint32_t einj6_compare_point_h1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h2_reg {
	struct {
		uint32_t einj6_compare_point_h2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h3_reg {
	struct {
		uint32_t einj6_compare_point_h3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h0_reg {
	struct {
		uint32_t einj6_compare_value_h0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h1_reg {
	struct {
		uint32_t einj6_compare_value_h1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h2_reg {
	struct {
		uint32_t einj6_compare_value_h2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h3_reg {
	struct {
		uint32_t einj6_compare_value_h3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h0_reg {
	struct {
		uint32_t einj6_change_point_h0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h1_reg {
	struct {
		uint32_t einj6_change_point_h1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h2_reg {
	struct {
		uint32_t einj6_change_point_h2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h3_reg {
	struct {
		uint32_t einj6_change_point_h3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h0_reg {
	struct {
		uint32_t einj6_change_value_h0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h1_reg {
	struct {
		uint32_t einj6_change_value_h1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h2_reg {
	struct {
		uint32_t einj6_change_value_h2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h3_reg {
	struct {
		uint32_t einj6_change_value_h3; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_einj6_tlp_reg {
	struct {
		uint32_t einj6_count:8; /* [7:0] */
		uint32_t einj6_inverted_control:1; /* [8:8] */
		uint32_t einj6_packet_type:3; /* [11:9] */
		uint32_t rsvdp_12:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_control1_reg {
	struct {
		uint32_t force_detect_lane:16; /* [15:0] */
		uint32_t force_detect_lane_en:1; /* [16:16] */
		uint32_t rsvdp_17:3; /* [19:17] */
		uint32_t tx_eios_num:2; /* [21:20] */
		uint32_t low_power_interval:2; /* [23:22] */
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_control2_reg {
	struct {
		uint32_t hold_ltssm:1; /* [0:0] */
		uint32_t recovery_request:1; /* [1:1] */
		uint32_t noack_force_linkdown:1; /* [2:2] */
		uint32_t rsvdp_3:1; /* [3:3] */
		uint32_t reserved_bit_0:4;
		uint32_t direct_recidle_to_config:1; /* [8:8] */
		uint32_t direct_polcomp_to_detect:1; /* [9:9] */
		uint32_t direct_lpbkslv_to_exit:1; /* [10:10] */
		uint32_t reserved_bit_1:2;
		uint32_t rsvdp_13:3; /* [15:13] */
		uint32_t framing_err_recovery_disable:1; /* [16:16] */
		uint32_t rsvdp_17:15; /* [31:17] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_l1lane_reg {
	struct {
		uint32_t lane_select:4; /* [3:0] */
		uint32_t rsvdp_4:12; /* [15:4] */
		uint32_t pipe_rxpolarity:1; /* [16:16] */
		uint32_t pipe_detect_lane:1; /* [17:17] */
		uint32_t pipe_rxvalid:1; /* [18:18] */
		uint32_t pipe_rxelecidle:1; /* [19:19] */
		uint32_t pipe_txelecidle:1; /* [20:20] */
		uint32_t rsvdp_21:3; /* [23:21] */
		uint32_t deskew_pointer:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_l1ltssm_reg {
	struct {
		uint32_t framing_err_ptr:7; /* [6:0] */
		uint32_t framing_err:1; /* [7:7] */
		uint32_t pipe_power_down:3; /* [10:8] */
		uint32_t rsvdp_11:4; /* [14:11] */
		uint32_t lane_reversal:1; /* [15:15] */
		uint32_t ltssm_variable:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_pm_reg {
	struct {
		uint32_t pm_dsp_link_state:4; /* [3:0] */
		uint32_t pm_dsp_prot_state:4; /* [7:4] */
		uint32_t pm_usp_link_state:4; /* [11:8] */
		uint32_t pme_resend_flag:1; /* [12:12] */
		uint32_t l1sub_state:3; /* [15:13] */
		uint32_t latched_nfts:8; /* [23:16] */
		uint32_t pm_l0s_state:3; /* [26:24] */
		uint32_t pm_usp_prot_state:4; /* [30:27] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_l2_reg {
	struct {
		uint32_t tx_tlp_seq_no:12; /* [11:0] */
		uint32_t rx_ack_seq_no:12; /* [23:12] */
		uint32_t dlcmsm:2; /* [25:24] */
		uint32_t fc_init1:1; /* [26:26] */
		uint32_t fc_init2:1; /* [27:27] */
		uint32_t rsvdp_28:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_l3fc_reg {
	struct {
		uint32_t credit_sel_vc:3; /* [2:0] */
		uint32_t credit_sel_credit_type:1; /* [3:3] */
		uint32_t credit_sel_tlp_type:2; /* [5:4] */
		uint32_t credit_sel_hd:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t credit_data0:12; /* [19:8] */
		uint32_t credit_data1:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_status_l3_reg {
	struct {
		uint32_t mftlp_pointer:7; /* [6:0] */
		uint32_t mftlp_status:1; /* [7:7] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_control1_reg {
	struct {
		uint32_t eq_lane_sel:4; /* [3:0] */
		uint32_t eq_rate_sel:2; /* [5:4] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t ext_eq_timeout:2; /* [9:8] */
		uint32_t rsvdp_10:6; /* [15:10] */
		uint32_t eval_interval_time:2; /* [17:16] */
		uint32_t rsvdp_18:5; /* [22:18] */
		uint32_t fom_target_enable:1; /* [23:23] */
		uint32_t fom_target:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_control2_reg {
	struct {
		uint32_t force_local_tx_pre_cursor:6; /* [5:0] */
		uint32_t force_local_tx_cursor:6; /* [11:6] */
		uint32_t force_local_tx_post_cursor:6; /* [17:12] */
		uint32_t force_local_rx_hint_or_force_local_tx_2nd_pre_cursor:6; /* [23:18] */
		uint32_t force_local_tx_preset:4; /* [27:24] */
		uint32_t force_local_tx_coef_enable:1; /* [28:28] */
		uint32_t force_local_rx_hint_enable:1; /* [29:29] */
		uint32_t force_local_tx_preset_enable:1; /* [30:30] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_control3_reg {
	struct {
		uint32_t force_remote_tx_pre_cursor:6; /* [5:0] */
		uint32_t force_remote_tx_cursor:6; /* [11:6] */
		uint32_t force_remote_tx_post_cursor:6; /* [17:12] */
		uint32_t force_remote_tx_2nd_pre_cursor:6; /* [23:18] */
		uint32_t rsvdp_24:4; /* [27:24] */
		uint32_t force_remote_tx_coef_enable:1; /* [28:28] */
		uint32_t rsvdp_29:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_status1_reg {
	struct {
		uint32_t eq_sequence:1; /* [0:0] */
		uint32_t eq_convergence_info:2; /* [2:1] */
		uint32_t eq_ruled_violation:1; /* [3:3] */
		uint32_t eq_rulea_violation:1; /* [4:4] */
		uint32_t eq_ruleb_violation:1; /* [5:5] */
		uint32_t eq_rulec_violation:1; /* [6:6] */
		uint32_t eq_reject_event:1; /* [7:7] */
		uint32_t rsvdp_8:18; /* [25:8] */
		uint32_t eq_remote_2nd_pre_cursor:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_status2_reg {
	struct {
		uint32_t eq_local_pre_cursor:6; /* [5:0] */
		uint32_t eq_local_cursor:6; /* [11:6] */
		uint32_t eq_local_post_cursor:6; /* [17:12] */
		uint32_t eq_local_rx_hint_or_eq_local_2nd_pre_cursor:6; /* [23:18] */
		uint32_t eq_local_fom_value:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_ras_des_cap_sd_eq_status3_reg {
	struct {
		uint32_t eq_remote_pre_cursor:6; /* [5:0] */
		uint32_t eq_remote_cursor:6; /* [11:6] */
		uint32_t eq_remote_post_cursor:6; /* [17:12] */
		uint32_t eq_remote_lf:6; /* [23:18] */
		uint32_t eq_remote_fs:6; /* [29:24] */
		uint32_t rsvdp_30:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_ext_cap_hdr_off {
	struct {
		uint32_t id:16; /* [15:0] */
		uint32_t cap:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_vendor_specific_hdr_off {
	struct {
		uint32_t vsec_id:16; /* [15:0] */
		uint32_t vsec_rev:4; /* [19:16] */
		uint32_t vsec_length:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_error_prot_ctrl_off {
	struct {
		uint32_t error_prot_disable_tx:1; /* [0:0] */
		uint32_t error_prot_disable_axi_bridge_master:1; /* [1:1] */
		uint32_t error_prot_disable_axi_bridge_outbound:1; /* [2:2] */
		uint32_t error_prot_disable_dma_write:1; /* [3:3] */
		uint32_t error_prot_disable_layer2_tx:1; /* [4:4] */
		uint32_t error_prot_disable_layer3_tx:1; /* [5:5] */
		uint32_t error_prot_disable_adm_tx:1; /* [6:6] */
		uint32_t error_prot_disable_cxs_tx:1; /* [7:7] */
		uint32_t error_prot_disable_dtim_tx:1; /* [8:8] */
		uint32_t error_prot_disable_cxl_tx:1; /* [9:9] */
		uint32_t rsvdp_10:6; /* [15:10] */
		uint32_t error_prot_disable_rx:1; /* [16:16] */
		uint32_t error_prot_disable_axi_bridge_inbound_completion:1; /* [17:17] */
		uint32_t error_prot_disable_axi_bridge_inbound_request:1; /* [18:18] */
		uint32_t error_prot_disable_dma_read:1; /* [19:19] */
		uint32_t error_prot_disable_layer2_rx:1; /* [20:20] */
		uint32_t error_prot_disable_layer3_rx:1; /* [21:21] */
		uint32_t error_prot_disable_adm_rx:1; /* [22:22] */
		uint32_t error_prot_disable_cxs_rx:1; /* [23:23] */
		uint32_t error_prot_disable_ltim:1; /* [24:24] */
		uint32_t rsvdp_25:7; /* [31:25] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_counter_ctrl_off {
	struct {
		uint32_t corr_clear_counters:1; /* [0:0] */
		uint32_t rsvdp_1:3; /* [3:1] */
		uint32_t corr_en_counters:1; /* [4:4] */
		uint32_t rsvdp_5:15; /* [19:5] */
		uint32_t corr_counter_selection_region:4; /* [23:20] */
		uint32_t corr_counter_selection:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_count_report_off {
	struct {
		uint32_t corr_counter:8; /* [7:0] */
		uint32_t rsvdp_8:12; /* [19:8] */
		uint32_t corr_counter_selected_region:4; /* [23:20] */
		uint32_t corr_counter_selected:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off {
	struct {
		uint32_t uncorr_clear_counters:1; /* [0:0] */
		uint32_t rsvdp_1:3; /* [3:1] */
		uint32_t uncorr_en_counters:1; /* [4:4] */
		uint32_t rsvdp_5:15; /* [19:5] */
		uint32_t uncorr_counter_selection_region:4; /* [23:20] */
		uint32_t uncorr_counter_selection:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_count_report_off {
	struct {
		uint32_t uncorr_counter:8; /* [7:0] */
		uint32_t rsvdp_8:12; /* [19:8] */
		uint32_t uncorr_counter_selected_region:4; /* [23:20] */
		uint32_t uncorr_counter_selected:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_error_inj_ctrl_off {
	struct {
		uint32_t error_inj_en:1; /* [0:0] */
		uint32_t rsvdp_1:3; /* [3:1] */
		uint32_t error_inj_type:2; /* [5:4] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t error_inj_count:8; /* [15:8] */
		uint32_t error_inj_loc:8; /* [23:16] */
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_error_location_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t reg_first_corr_error:4; /* [7:4] */
		uint32_t loc_first_corr_error:8; /* [15:8] */
		uint32_t rsvdp_16:4; /* [19:16] */
		uint32_t reg_last_corr_error:4; /* [23:20] */
		uint32_t loc_last_corr_error:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_error_location_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t reg_first_uncorr_error:4; /* [7:4] */
		uint32_t loc_first_uncorr_error:8; /* [15:8] */
		uint32_t rsvdp_16:4; /* [19:16] */
		uint32_t reg_last_uncorr_error:4; /* [23:20] */
		uint32_t loc_last_uncorr_error:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_error_mode_en_off {
	struct {
		uint32_t error_mode_en:1; /* [0:0] */
		uint32_t auto_link_down_en:1; /* [1:1] */
		uint32_t rsvdp_2:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_error_mode_clear_off {
	struct {
		uint32_t error_mode_clear:1; /* [0:0] */
		uint32_t rsvdp_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_ram_addr_corr_error_off {
	struct {
		uint32_t ram_addr_corr_error:27; /* [26:0] */
		uint32_t rsvdp_27:1; /* [27:27] */
		uint32_t ram_index_corr_error:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecras_cap_rasdp_ram_addr_uncorr_error_off {
	struct {
		uint32_t ram_addr_uncorr_error:27; /* [26:0] */
		uint32_t rsvdp_27:1; /* [27:27] */
		uint32_t ram_index_uncorr_error:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dlink_cap_data_link_feature_ext_hdr_off {
	struct {
		uint32_t dlink_ext_cap_id:16; /* [15:0] */
		uint32_t dlink_cap_version:4; /* [19:16] */
		uint32_t dlink_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dlink_cap_data_link_feature_cap_off {
	struct {
		uint32_t scaled_flow_cntl_supported:1; /* [0:0] */
		uint32_t lcl_immediate_readiness:1; /* [1:1] */
		uint32_t lcl_extended_vc_cnt:3; /* [4:2] */
		uint32_t lcl_l0p_exit_ltncy:3; /* [7:5] */
		uint32_t future_feature_supported:15; /* [22:8] */
		uint32_t rsvdp_23:8; /* [30:23] */
		uint32_t dl_feature_exchange_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dlink_cap_data_link_feature_status_off {
	struct {
		uint32_t remote_scaled_flow_cntl_supported:1; /* [0:0] */
		uint32_t remote_immediate_readiness:1; /* [1:1] */
		uint32_t remote_extended_vc_cnt:3; /* [4:2] */
		uint32_t remote_l0p_exit_ltncy:3; /* [7:5] */
		uint32_t remote_reserved:15; /* [22:8] */
		uint32_t rsvdp_23:8; /* [30:23] */
		uint32_t data_link_feature_status_valid:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_ext_cap_hdr_off {
	struct {
		uint32_t id:16; /* [15:0] */
		uint32_t cap:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_vendor_specific_hdr_off {
	struct {
		uint32_t vsec_id:16; /* [15:0] */
		uint32_t vsec_rev:4; /* [19:16] */
		uint32_t vsec_length:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_device_information_off {
	struct {
		uint32_t map_format:3; /* [2:0] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t barn:3; /* [10:8] */
		uint32_t pfn:5; /* [15:11] */
		uint32_t channel_separation:3; /* [18:16] */
		uint32_t axi:1; /* [19:19] */
		uint32_t master_bus_width:3; /* [22:20] */
		uint32_t master_burst_length:3; /* [25:23] */
		uint32_t master_page_boundary_pointer_width:4; /* [29:26] */
		uint32_t rsvdp_30:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_num_chan_off {
	struct {
		uint32_t num_dma_wr_chan:10; /* [9:0] */
		uint32_t rsvdp_10:6; /* [15:10] */
		uint32_t num_dma_rd_chan:10; /* [25:16] */
		uint32_t rsvdp_26:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_unroll_addr_offset_low_off {
	struct {
		uint32_t unroll_addr_offset_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vsecdma_cap_vsecdma_unroll_addr_offset_high_off {
	struct {
		uint32_t unroll_addr_offset_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dev3_ext_cap_dev3_ext_cap_hdr_reg {
	struct {
		uint32_t dev3_cap_id:16; /* [15:0] */
		uint32_t dev3_cap_version:4; /* [19:16] */
		uint32_t dev3_cap_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dev3_ext_cap_device_capabilities3_reg {
	struct {
		uint32_t dev3_cap_dmwr_routing_supp:1; /* [0:0] */
		uint32_t dev3_cap_14b_tag_complet_supp:1; /* [1:1] */
		uint32_t reserved_bit_0:8;
		uint32_t rsvdp_10:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dev3_ext_cap_device_control3_reg {
	struct {
		uint32_t reserved_bit_0:1;
		uint32_t dev3_cap_dmwr_egress_blk:1; /* [1:1] */
		uint32_t reserved_bit_1:5;
		uint32_t rsvdp_7:25; /* [31:7] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_dev3_ext_cap_device_status3_reg {
	struct {
		uint32_t dev3_init_link_width:3; /* [2:0] */
		uint32_t dev3_cap_segment_captured:1; /* [3:3] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_5:27; /* [31:5] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_ext_cap_hdr {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_ver:4; /* [19:16] */
		uint32_t next_cap_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_cap {
	struct {
		uint32_t link_ide_stream_supported:1; /* [0:0] */
		uint32_t slct_ide_stream_supported:1; /* [1:1] */
		uint32_t flowthrough_ide_stream_supported:1; /* [2:2] */
		uint32_t ide_partial_header_encryption_supported:1; /* [3:3] */
		uint32_t aggregation_supported:1; /* [4:4] */
		uint32_t pcrc_supported:1; /* [5:5] */
		uint32_t ide_km_protocol_supported:1; /* [6:6] */
		uint32_t slct_ide_conf_req_supported:1; /* [7:7] */
		uint32_t supported_algorithm:5; /* [12:8] */
		uint32_t num_tc_supported_for_link_ide:3; /* [15:13] */
		uint32_t num_slct_ide_streams_supported:8; /* [23:16] */
		uint32_t tee_limited_stream_supported:1; /* [24:24] */
		uint32_t reserved_31_25:7; /* [31:25] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_ctrl {
	struct {
		uint32_t reserved_1_0:2; /* [1:0] */
		uint32_t flowthrough_ide_stream_enabled:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_link_stream_ctrl_0 {
	struct {
		uint32_t link_ide_stream_enabled:1; /* [0:0] */
		uint32_t reserved_1:1; /* [1:1] */
		uint32_t reserved_7_2:6; /* [7:2] */
		uint32_t pcrc_enable:1; /* [8:8] */
		uint32_t reserved_9:1; /* [9:9] */
		uint32_t reserved_bit_0:4;
		uint32_t selected_algorithm:5; /* [18:14] */
		uint32_t tc:3; /* [21:19] */
		uint32_t reserved_23_22:2; /* [23:22] */
		uint32_t stream_id:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_link_status_0 {
	struct {
		uint32_t link_ide_stream_state:4; /* [3:0] */
		uint32_t reserved_30_4:27; /* [30:4] */
		uint32_t received_integrity_check_fail_msg:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_slct_ide_stream_cap_0 {
	struct {
		uint32_t num_addr_assos_reg_blocks:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_slct_ide_stream_ctrl_0 {
	struct {
		uint32_t slct_ide_stream_enabled:1; /* [0:0] */
		uint32_t reserved_1:1; /* [1:1] */
		uint32_t reserved_7_2:6; /* [7:2] */
		uint32_t pcrc_enable:1; /* [8:8] */
		uint32_t slcr_ide_cfg_req_enable:1; /* [9:9] */
		uint32_t reserved_bit_0:4;
		uint32_t selected_algorithm:5; /* [18:14] */
		uint32_t tc:3; /* [21:19] */
		uint32_t default_stream:1; /* [22:22] */
		uint32_t tee_limited_stream:1; /* [23:23] */
		uint32_t stream_id:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_slct_ide_stream_status_0 {
	struct {
		uint32_t slct_ide_stream_state:4; /* [3:0] */
		uint32_t reserved_31_4:27; /* [30:4] */
		uint32_t received_integrity_check_fail_msg:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_rid_assos_reg1_0 {
	struct {
		uint32_t reserved_7_0:8; /* [7:0] */
		uint32_t rid_limit:16; /* [23:8] */
		uint32_t reserved_31_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_rid_assos_reg2_0 {
	struct {
		uint32_t rid_valid:1; /* [0:0] */
		uint32_t reserved_7_1:7; /* [7:1] */
		uint32_t rid_base:16; /* [23:8] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg1_0_0 {
	struct {
		uint32_t valid:1; /* [0:0] */
		uint32_t reserved_7_1:7; /* [7:1] */
		uint32_t mem_base_lower:12; /* [19:8] */
		uint32_t mem_limit_lower:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg2_0_0 {
	struct {
		uint32_t mem_limit_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg3_0_0 {
	struct {
		uint32_t mem_base_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg1_0_1 {
	struct {
		uint32_t valid:1; /* [0:0] */
		uint32_t reserved_7_1:7; /* [7:1] */
		uint32_t mem_base_lower:12; /* [19:8] */
		uint32_t mem_limit_lower:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg2_0_1 {
	struct {
		uint32_t mem_limit_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg3_0_1 {
	struct {
		uint32_t mem_base_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg1_0_2 {
	struct {
		uint32_t valid:1; /* [0:0] */
		uint32_t reserved_7_1:7; /* [7:1] */
		uint32_t mem_base_lower:12; /* [19:8] */
		uint32_t mem_limit_lower:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg2_0_2 {
	struct {
		uint32_t mem_limit_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_wire_ide_addr_assos_reg3_0_2 {
	struct {
		uint32_t mem_base_upper; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_resbar_cap_resbar_cap_hdr_reg {
	struct {
		uint32_t resbar_ext_cap_id:16; /* [15:0] */
		uint32_t resbar_cap_version:4; /* [19:16] */
		uint32_t resbar_cap_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_resbar_cap_resbar_cap_reg_0_reg {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t resbar_cap_reg_0_1mb:1; /* [4:4] */
		uint32_t resbar_cap_reg_0_2mb:1; /* [5:5] */
		uint32_t resbar_cap_reg_0_4mb:1; /* [6:6] */
		uint32_t resbar_cap_reg_0_8mb:1; /* [7:7] */
		uint32_t resbar_cap_reg_0_16mb:1; /* [8:8] */
		uint32_t resbar_cap_reg_0_32mb:1; /* [9:9] */
		uint32_t resbar_cap_reg_0_64mb:1; /* [10:10] */
		uint32_t resbar_cap_reg_0_128mb:1; /* [11:11] */
		uint32_t resbar_cap_reg_0_256mb:1; /* [12:12] */
		uint32_t resbar_cap_reg_0_512mb:1; /* [13:13] */
		uint32_t resbar_cap_reg_0_1gb:1; /* [14:14] */
		uint32_t resbar_cap_reg_0_2gb:1; /* [15:15] */
		uint32_t resbar_cap_reg_0_4gb:1; /* [16:16] */
		uint32_t resbar_cap_reg_0_8gb:1; /* [17:17] */
		uint32_t resbar_cap_reg_0_16gb:1; /* [18:18] */
		uint32_t resbar_cap_reg_0_32gb:1; /* [19:19] */
		uint32_t resbar_cap_reg_0_64gb:1; /* [20:20] */
		uint32_t resbar_cap_reg_0_128gb:1; /* [21:21] */
		uint32_t resbar_cap_reg_0_256gb:1; /* [22:22] */
		uint32_t resbar_cap_reg_0_512gb:1; /* [23:23] */
		uint32_t resbar_cap_reg_0_1tb:1; /* [24:24] */
		uint32_t resbar_cap_reg_0_2tb:1; /* [25:25] */
		uint32_t resbar_cap_reg_0_4tb:1; /* [26:26] */
		uint32_t resbar_cap_reg_0_8tb:1; /* [27:27] */
		uint32_t resbar_cap_reg_0_16tb:1; /* [28:28] */
		uint32_t resbar_cap_reg_0_32tb:1; /* [29:29] */
		uint32_t resbar_cap_reg_0_64tb:1; /* [30:30] */
		uint32_t resbar_cap_reg_0_128tb:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_resbar_cap_resbar_ctrl_reg_0_reg {
	struct {
		uint32_t resbar_ctrl_reg_idx_0:3; /* [2:0] */
		uint32_t rsvdp_3:2; /* [4:3] */
		uint32_t resbar_ctrl_reg_num_bars:3; /* [7:5] */
		uint32_t resbar_ctrl_reg_bar_size:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t resbar_ctrl_reg_0_256tb:1; /* [16:16] */
		uint32_t resbar_ctrl_reg_0_512tb:1; /* [17:17] */
		uint32_t resbar_ctrl_reg_0_1pb:1; /* [18:18] */
		uint32_t resbar_ctrl_reg_0_2pb:1; /* [19:19] */
		uint32_t resbar_ctrl_reg_0_4pb:1; /* [20:20] */
		uint32_t resbar_ctrl_reg_0_8pb:1; /* [21:21] */
		uint32_t resbar_ctrl_reg_0_16pb:1; /* [22:22] */
		uint32_t resbar_ctrl_reg_0_32pb:1; /* [23:23] */
		uint32_t resbar_ctrl_reg_0_64pb:1; /* [24:24] */
		uint32_t resbar_ctrl_reg_0_128pb:1; /* [25:25] */
		uint32_t resbar_ctrl_reg_0_256pb:1; /* [26:26] */
		uint32_t resbar_ctrl_reg_0_512pb:1; /* [27:27] */
		uint32_t resbar_ctrl_reg_0_1eb:1; /* [28:28] */
		uint32_t resbar_ctrl_reg_0_2eb:1; /* [29:29] */
		uint32_t resbar_ctrl_reg_0_4eb:1; /* [30:30] */
		uint32_t resbar_ctrl_reg_0_8eb:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_cap_hdr_reg {
	struct {
		uint32_t vf_resbar_ext_cap_id:16; /* [15:0] */
		uint32_t vf_resbar_cap_version:4; /* [19:16] */
		uint32_t vf_resbar_cap_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_cap_reg_0_reg {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t vf_resbar_cap_reg_0_1mb:1; /* [4:4] */
		uint32_t vf_resbar_cap_reg_0_2mb:1; /* [5:5] */
		uint32_t vf_resbar_cap_reg_0_4mb:1; /* [6:6] */
		uint32_t vf_resbar_cap_reg_0_8mb:1; /* [7:7] */
		uint32_t vf_resbar_cap_reg_0_16mb:1; /* [8:8] */
		uint32_t vf_resbar_cap_reg_0_32mb:1; /* [9:9] */
		uint32_t vf_resbar_cap_reg_0_64mb:1; /* [10:10] */
		uint32_t vf_resbar_cap_reg_0_128mb:1; /* [11:11] */
		uint32_t vf_resbar_cap_reg_0_256mb:1; /* [12:12] */
		uint32_t vf_resbar_cap_reg_0_512mb:1; /* [13:13] */
		uint32_t vf_resbar_cap_reg_0_1gb:1; /* [14:14] */
		uint32_t vf_resbar_cap_reg_0_2gb:1; /* [15:15] */
		uint32_t vf_resbar_cap_reg_0_4gb:1; /* [16:16] */
		uint32_t vf_resbar_cap_reg_0_8gb:1; /* [17:17] */
		uint32_t vf_resbar_cap_reg_0_16gb:1; /* [18:18] */
		uint32_t vf_resbar_cap_reg_0_32gb:1; /* [19:19] */
		uint32_t vf_resbar_cap_reg_0_64gb:1; /* [20:20] */
		uint32_t vf_resbar_cap_reg_0_128gb:1; /* [21:21] */
		uint32_t vf_resbar_cap_reg_0_256gb:1; /* [22:22] */
		uint32_t vf_resbar_cap_reg_0_512gb:1; /* [23:23] */
		uint32_t vf_resbar_cap_reg_0_1tb:1; /* [24:24] */
		uint32_t vf_resbar_cap_reg_0_2tb:1; /* [25:25] */
		uint32_t vf_resbar_cap_reg_0_4tb:1; /* [26:26] */
		uint32_t vf_resbar_cap_reg_0_8tb:1; /* [27:27] */
		uint32_t vf_resbar_cap_reg_0_16tb:1; /* [28:28] */
		uint32_t vf_resbar_cap_reg_0_32tb:1; /* [29:29] */
		uint32_t vf_resbar_cap_reg_0_64tb:1; /* [30:30] */
		uint32_t vf_resbar_cap_reg_0_128tb:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_ctrl_reg_0_reg {
	struct {
		uint32_t vf_resbar_ctrl_reg_idx_0:3; /* [2:0] */
		uint32_t rsvdp_3:2; /* [4:3] */
		uint32_t vf_resbar_ctrl_reg_num_bars:3; /* [7:5] */
		uint32_t vf_resbar_ctrl_reg_bar_size:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t vf_resbar_ctrl_reg_0_256tb:1; /* [16:16] */
		uint32_t vf_resbar_ctrl_reg_0_512tb:1; /* [17:17] */
		uint32_t vf_resbar_ctrl_reg_0_1pb:1; /* [18:18] */
		uint32_t vf_resbar_ctrl_reg_0_2pb:1; /* [19:19] */
		uint32_t vf_resbar_ctrl_reg_0_4pb:1; /* [20:20] */
		uint32_t vf_resbar_ctrl_reg_0_8pb:1; /* [21:21] */
		uint32_t vf_resbar_ctrl_reg_0_16pb:1; /* [22:22] */
		uint32_t vf_resbar_ctrl_reg_0_32pb:1; /* [23:23] */
		uint32_t vf_resbar_ctrl_reg_0_64pb:1; /* [24:24] */
		uint32_t vf_resbar_ctrl_reg_0_128pb:1; /* [25:25] */
		uint32_t vf_resbar_ctrl_reg_0_256pb:1; /* [26:26] */
		uint32_t vf_resbar_ctrl_reg_0_512pb:1; /* [27:27] */
		uint32_t vf_resbar_ctrl_reg_0_1eb:1; /* [28:28] */
		uint32_t vf_resbar_ctrl_reg_0_2eb:1; /* [29:29] */
		uint32_t vf_resbar_ctrl_reg_0_4eb:1; /* [30:30] */
		uint32_t vf_resbar_ctrl_reg_0_8eb:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_device_id_vendor_id_reg {
	struct {
		uint32_t pci_type0_vendor_id:16; /* [15:0] */
		uint32_t pci_type0_device_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_status_command_reg {
	struct {
		uint32_t pci_type0_io_en:1; /* [0:0] */
		uint32_t pci_type0_mem_space_en:1; /* [1:1] */
		uint32_t pci_type0_bus_master_en:1; /* [2:2] */
		uint32_t pci_type0_special_cycle_operation:1; /* [3:3] */
		uint32_t pci_type_mwi_enable:1; /* [4:4] */
		uint32_t pci_type_vga_palette_snoop:1; /* [5:5] */
		uint32_t pci_type0_parity_err_en:1; /* [6:6] */
		uint32_t pci_type_idsel_stepping:1; /* [7:7] */
		uint32_t pci_type0_serren:1; /* [8:8] */
		uint32_t rsvdp_9:1; /* [9:9] */
		uint32_t pci_type0_int_en:1; /* [10:10] */
		uint32_t pci_type_reserv:5; /* [15:11] */
		uint32_t imm_readiness:1; /* [16:16] */
		uint32_t rsvdp_17:2; /* [18:17] */
		uint32_t int_status:1; /* [19:19] */
		uint32_t cap_list:1; /* [20:20] */
		uint32_t fast_66mhz_cap:1; /* [21:21] */
		uint32_t rsvdp_22:1; /* [22:22] */
		uint32_t fast_b2b_cap:1; /* [23:23] */
		uint32_t master_dpe:1; /* [24:24] */
		uint32_t dev_sel_timing:2; /* [26:25] */
		uint32_t signaled_target_abort:1; /* [27:27] */
		uint32_t rcvd_target_abort:1; /* [28:28] */
		uint32_t rcvd_master_abort:1; /* [29:29] */
		uint32_t signaled_sys_err:1; /* [30:30] */
		uint32_t detected_parity_err:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_class_code_revision_id {
	struct {
		uint32_t revision_id:8; /* [7:0] */
		uint32_t program_interface:8; /* [15:8] */
		uint32_t subclass_code:8; /* [23:16] */
		uint32_t base_class_code:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bist_header_type_latency_cache_line_size_reg {
	struct {
		uint32_t cache_line_size:8; /* [7:0] */
		uint32_t latency_master_timer:8; /* [15:8] */
		uint32_t header_type:7; /* [22:16] */
		uint32_t multi_func:1; /* [23:23] */
		uint32_t bist:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar0_reg {
	struct {
		uint32_t bar0_mem_io:1; /* [0:0] */
		uint32_t bar0_type:2; /* [2:1] */
		uint32_t bar0_prefetch:1; /* [3:3] */
		uint32_t bar0_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar1_reg {
	struct {
		uint32_t bar1_mem_io:1; /* [0:0] */
		uint32_t bar1_type:2; /* [2:1] */
		uint32_t bar1_prefetch:1; /* [3:3] */
		uint32_t bar1_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar2_reg {
	struct {
		uint32_t bar2_mem_io:1; /* [0:0] */
		uint32_t bar2_type:2; /* [2:1] */
		uint32_t bar2_prefetch:1; /* [3:3] */
		uint32_t bar2_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar3_reg {
	struct {
		uint32_t bar3_mem_io:1; /* [0:0] */
		uint32_t bar3_type:2; /* [2:1] */
		uint32_t bar3_prefetch:1; /* [3:3] */
		uint32_t bar3_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar4_reg {
	struct {
		uint32_t bar4_mem_io:1; /* [0:0] */
		uint32_t bar4_type:2; /* [2:1] */
		uint32_t bar4_prefetch:1; /* [3:3] */
		uint32_t bar4_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_bar5_reg {
	struct {
		uint32_t bar5_mem_io:1; /* [0:0] */
		uint32_t bar5_type:2; /* [2:1] */
		uint32_t bar5_prefetch:1; /* [3:3] */
		uint32_t bar5_start:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_cardbus_cis_ptr_reg {
	struct {
		uint32_t cardbus_cis_pointer; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_subsystem_id_subsystem_vendor_id_reg {
	struct {
		uint32_t subsys_vendor_id:16; /* [15:0] */
		uint32_t subsys_dev_id:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_pci_cap_ptr_reg {
	struct {
		uint32_t cap_pointer:8; /* [7:0] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_type0_hdr_vf_max_latency_min_grant_interrupt_pin_interrupt_line_reg {
	struct {
		uint32_t int_line:8; /* [7:0] */
		uint32_t int_pin:8; /* [15:8] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg {
	struct {
		uint32_t pcie_cap_id:8; /* [7:0] */
		uint32_t pcie_cap_next_ptr:8; /* [15:8] */
		uint32_t pcie_cap_reg:4; /* [19:16] */
		uint32_t pcie_dev_port_type:4; /* [23:20] */
		uint32_t pcie_slot_imp:1; /* [24:24] */
		uint32_t pcie_int_msg_num:5; /* [29:25] */
		uint32_t rsvd:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_device_capabilities_reg {
	struct {
		uint32_t pcie_cap_max_payload_size:3; /* [2:0] */
		uint32_t pcie_cap_phantom_func_support:2; /* [4:3] */
		uint32_t pcie_cap_ext_tag_supp:1; /* [5:5] */
		uint32_t pcie_cap_ep_l0s_accpt_latency:3; /* [8:6] */
		uint32_t pcie_cap_ep_l1_accpt_latency:3; /* [11:9] */
		uint32_t rsvdp_12:3; /* [14:12] */
		uint32_t pcie_cap_role_based_err_report:1; /* [15:15] */
		uint32_t rsvdp_16:1; /* [16:16] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_cap_cap_slot_pwr_lmt_value:8; /* [25:18] */
		uint32_t pcie_cap_cap_slot_pwr_lmt_scale:2; /* [27:26] */
		uint32_t pcie_cap_flr_cap:1; /* [28:28] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_cap_tee_io_supported:1; /* [30:30] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_device_control_device_status {
	struct {
		uint32_t pcie_cap_corr_err_report_en:1; /* [0:0] */
		uint32_t pcie_cap_non_fatal_err_report_en:1; /* [1:1] */
		uint32_t pcie_cap_fatal_err_report_en:1; /* [2:2] */
		uint32_t pcie_cap_unsupport_req_rep_en:1; /* [3:3] */
		uint32_t pcie_cap_en_rel_order:1; /* [4:4] */
		uint32_t pcie_cap_max_payload_size_cs:3; /* [7:5] */
		uint32_t pcie_cap_ext_tag_en:1; /* [8:8] */
		uint32_t pcie_cap_phantom_func_en:1; /* [9:9] */
		uint32_t pcie_cap_aux_power_pm_en:1; /* [10:10] */
		uint32_t pcie_cap_en_no_snoop:1; /* [11:11] */
		uint32_t pcie_cap_max_read_req_size:3; /* [14:12] */
		uint32_t pcie_cap_initiate_flr:1; /* [15:15] */
		uint32_t pcie_cap_corr_err_detected:1; /* [16:16] */
		uint32_t pcie_cap_non_fatal_err_detected:1; /* [17:17] */
		uint32_t pcie_cap_fatal_err_detected:1; /* [18:18] */
		uint32_t pcie_cap_unsupported_req_detected:1; /* [19:19] */
		uint32_t pcie_cap_aux_power_detected:1; /* [20:20] */
		uint32_t pcie_cap_trans_pending:1; /* [21:21] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_link_capabilities_reg {
	struct {
		uint32_t pcie_cap_max_link_speed:4; /* [3:0] */
		uint32_t pcie_cap_max_link_width:6; /* [9:4] */
		uint32_t pcie_cap_active_state_link_pm_support:2; /* [11:10] */
		uint32_t pcie_cap_l0s_exit_latency:3; /* [14:12] */
		uint32_t pcie_cap_l1_exit_latency:3; /* [17:15] */
		uint32_t pcie_cap_clock_power_man:1; /* [18:18] */
		uint32_t pcie_cap_surprise_down_err_rep_cap:1; /* [19:19] */
		uint32_t pcie_cap_dll_active_rep_cap:1; /* [20:20] */
		uint32_t pcie_cap_link_bw_not_cap:1; /* [21:21] */
		uint32_t pcie_cap_aspm_opt_compliance:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t pcie_cap_port_num:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_link_control_link_status_reg {
	struct {
		uint32_t pcie_cap_active_state_link_pm_control:2; /* [1:0] */
		uint32_t rsvdp_2:1; /* [2:2] */
		uint32_t pcie_cap_rcb:1; /* [3:3] */
		uint32_t pcie_cap_link_disable:1; /* [4:4] */
		uint32_t pcie_cap_retrain_link:1; /* [5:5] */
		uint32_t pcie_cap_common_clk_config:1; /* [6:6] */
		uint32_t pcie_cap_extended_synch:1; /* [7:7] */
		uint32_t pcie_cap_en_clk_power_man:1; /* [8:8] */
		uint32_t pcie_cap_hw_auto_width_disable:1; /* [9:9] */
		uint32_t pcie_cap_link_bw_man_int_en:1; /* [10:10] */
		uint32_t pcie_cap_link_auto_bw_int_en:1; /* [11:11] */
		uint32_t reserved_bit_0:2;
		uint32_t pcie_cap_drs_signaling_control:2; /* [15:14] */
		uint32_t pcie_cap_link_speed:4; /* [19:16] */
		uint32_t pcie_cap_nego_link_width:6; /* [25:20] */
		uint32_t rsvdp_26:1; /* [26:26] */
		uint32_t pcie_cap_link_training:1; /* [27:27] */
		uint32_t pcie_cap_slot_clk_config:1; /* [28:28] */
		uint32_t pcie_cap_dll_active:1; /* [29:29] */
		uint32_t pcie_cap_link_bw_man_status:1; /* [30:30] */
		uint32_t pcie_cap_link_auto_bw_status:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_device_capabilities2_reg {
	struct {
		uint32_t pcie_cap_cpl_timeout_range:4; /* [3:0] */
		uint32_t pcie_cap_cpl_timeout_disable_support:1; /* [4:4] */
		uint32_t pcie_cap_ari_forward_support:1; /* [5:5] */
		uint32_t pcie_cap_atomic_routing_supp:1; /* [6:6] */
		uint32_t pcie_cap_32_atomic_cpl_supp:1; /* [7:7] */
		uint32_t pcie_cap_64_atomic_cpl_supp:1; /* [8:8] */
		uint32_t pcie_cap_128_cas_cpl_supp:1; /* [9:9] */
		uint32_t pcie_cap_no_ro_en_pr2pr_par:1; /* [10:10] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_cap_tph_cmplt_support_0:1; /* [12:12] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_cap2_ln_sys_cls:2; /* [15:14] */
		uint32_t pcie_cap2_10_bit_tag_comp_support:1; /* [16:16] */
		uint32_t pcie_cap2_10_bit_tag_req_support:1; /* [17:17] */
		uint32_t reserved_bit_2:2;
		uint32_t pcie_cap2_cfg_extnd_fmt_support:1; /* [20:20] */
		uint32_t pcie_cap2_cfg_end2end_tlp_prfx_support:1; /* [21:21] */
		uint32_t pcie_cap2_cfg_max_end2end_tlp_prfxs:2; /* [23:22] */
		uint32_t reserved_bit_3:3;
		uint32_t rsvdp_27:1; /* [27:27] */
		uint32_t pcie_cap_dmwr_cpl_supp:1; /* [28:28] */
		uint32_t pcie_cap_dmwr_len_supp:2; /* [30:29] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_device_control2_device_status2_reg {
	struct {
		uint32_t pcie_cap_cpl_timeout_value:4; /* [3:0] */
		uint32_t pcie_cap_cpl_timeout_disable:1; /* [4:4] */
		uint32_t pcie_cap_ari_forward_support_cs:1; /* [5:5] */
		uint32_t reserved_bit_0:2;
		uint32_t pcie_cap_ido_req_en:1; /* [8:8] */
		uint32_t pcie_cap_ido_cpl_en:1; /* [9:9] */
		uint32_t reserved_bit_1:5;
		uint32_t pcie_ctrl2_cfg_end2end_tlp_pfx_blck:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_link_capabilities2_reg {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t pcie_cap_support_link_speed_vector:7; /* [7:1] */
		uint32_t pcie_cap_cross_link_support:1; /* [8:8] */
		uint32_t pcie_cap_lwr_skp_os_gen_sup:7; /* [15:9] */
		uint32_t pcie_cap_lwr_skp_os_rcv_sup:7; /* [22:16] */
		uint32_t pcie_cap_retimer_pre_det_support:1; /* [23:23] */
		uint32_t pcie_cap_two_retimers_pre_det_support:1; /* [24:24] */
		uint32_t rsvdp_25:6; /* [30:25] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_pcie_cap_vf_link_control2_link_status2_reg {
	struct {
		uint32_t pcie_cap_target_link_speed:4; /* [3:0] */
		uint32_t pcie_cap_enter_compliance:1; /* [4:4] */
		uint32_t pcie_cap_hw_auto_speed_disable:1; /* [5:5] */
		uint32_t pcie_cap_sel_deemphasis:1; /* [6:6] */
		uint32_t pcie_cap_tx_margin:3; /* [9:7] */
		uint32_t pcie_cap_enter_modified_compliance:1; /* [10:10] */
		uint32_t pcie_cap_compliance_sos:1; /* [11:11] */
		uint32_t pcie_cap_compliance_preset:4; /* [15:12] */
		uint32_t pcie_cap_curr_deemphasis:1; /* [16:16] */
		uint32_t pcie_cap_eq_cpl:1; /* [17:17] */
		uint32_t pcie_cap_eq_cpl_p1:1; /* [18:18] */
		uint32_t pcie_cap_eq_cpl_p2:1; /* [19:19] */
		uint32_t pcie_cap_eq_cpl_p3:1; /* [20:20] */
		uint32_t pcie_cap_link_eq_req:1; /* [21:21] */
		uint32_t pcie_cap_retimer_pre_det:1; /* [22:22] */
		uint32_t pcie_cap_two_retimers_pre_det:1; /* [23:23] */
		uint32_t pcie_cap_crosslink_resolution:2; /* [25:24] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_27:1; /* [27:27] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_msix_cap_vf_pci_msix_cap_id_next_ctrl_reg {
	struct {
		uint32_t pci_msix_cap_id:8; /* [7:0] */
		uint32_t pci_msix_cap_next_offset:8; /* [15:8] */
		uint32_t pci_msix_table_size:11; /* [26:16] */
		uint32_t rsvdp_27:3; /* [29:27] */
		uint32_t pci_msix_function_mask:1; /* [30:30] */
		uint32_t pci_msix_enable:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_msix_cap_vf_msix_table_offset_reg {
	struct {
		uint32_t pci_msix_bir:3; /* [2:0] */
		uint32_t pci_msix_table_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_msix_cap_vf_msix_pba_offset_reg {
	struct {
		uint32_t pci_msix_pba_bir:3; /* [2:0] */
		uint32_t pci_msix_pba_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_aer_ext_cap_hdr_off {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_status_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_status:1; /* [4:4] */
		uint32_t surprise_down_err_status:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_status:1; /* [12:12] */
		uint32_t fc_protocol_err_status:1; /* [13:13] */
		uint32_t cmplt_timeout_err_status:1; /* [14:14] */
		uint32_t cmplt_abort_err_status:1; /* [15:15] */
		uint32_t unexp_cmplt_err_status:1; /* [16:16] */
		uint32_t rec_overflow_err_status:1; /* [17:17] */
		uint32_t malf_tlp_err_status:1; /* [18:18] */
		uint32_t ecrc_err_status:1; /* [19:19] */
		uint32_t unsupported_req_err_status:1; /* [20:20] */
		uint32_t acs_violation_status:1; /* [21:21] */
		uint32_t internal_err_status:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t reserved_bit_0:1;
		uint32_t tlp_prfx_blocked_err_status:1; /* [25:25] */
		uint32_t reserved_bit_1:2;
		uint32_t ide_check_failed_status:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_status:1; /* [29:29] */
		uint32_t pcrc_check_failed_status:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_mask_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_mask:1; /* [4:4] */
		uint32_t surprise_down_err_mask:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_mask:1; /* [12:12] */
		uint32_t fc_protocol_err_mask:1; /* [13:13] */
		uint32_t cmplt_timeout_err_mask:1; /* [14:14] */
		uint32_t cmplt_abort_err_mask:1; /* [15:15] */
		uint32_t unexp_cmplt_err_mask:1; /* [16:16] */
		uint32_t rec_overflow_err_mask:1; /* [17:17] */
		uint32_t malf_tlp_err_mask:1; /* [18:18] */
		uint32_t ecrc_err_mask:1; /* [19:19] */
		uint32_t unsupported_req_err_mask:1; /* [20:20] */
		uint32_t acs_violation_mask:1; /* [21:21] */
		uint32_t internal_err_mask:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t atomic_egress_blocked_err_mask:1; /* [24:24] */
		uint32_t tlp_prfx_blocked_err_mask:1; /* [25:25] */
		uint32_t rsvdp_26:1; /* [26:26] */
		uint32_t dmwr_egress_blocked_err_mask:1; /* [27:27] */
		uint32_t ide_check_failed_mask:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_mask:1; /* [29:29] */
		uint32_t pcrc_check_failed_mask:1; /* [30:30] */
		uint32_t tlp_translation_egress_blocked_mask:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_sev_off {
	struct {
		uint32_t rsvdp_0:4; /* [3:0] */
		uint32_t dl_protocol_err_severity:1; /* [4:4] */
		uint32_t surprise_down_err_svrity:1; /* [5:5] */
		uint32_t rsvdp_6:6; /* [11:6] */
		uint32_t pois_tlp_err_severity:1; /* [12:12] */
		uint32_t fc_protocol_err_severity:1; /* [13:13] */
		uint32_t cmplt_timeout_err_severity:1; /* [14:14] */
		uint32_t cmplt_abort_err_severity:1; /* [15:15] */
		uint32_t unexp_cmplt_err_severity:1; /* [16:16] */
		uint32_t rec_overflow_err_severity:1; /* [17:17] */
		uint32_t malf_tlp_err_severity:1; /* [18:18] */
		uint32_t ecrc_err_severity:1; /* [19:19] */
		uint32_t unsupported_req_err_severity:1; /* [20:20] */
		uint32_t acs_violation_severity:1; /* [21:21] */
		uint32_t internal_err_severity:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t reserved_bit_0:1;
		uint32_t tlp_prfx_blocked_err_severity:1; /* [25:25] */
		uint32_t reserved_bit_1:1;
		uint32_t dmwr_egress_blocked_err_severity:1; /* [27:27] */
		uint32_t ide_check_failed_sev:1; /* [28:28] */
		uint32_t misrouted_ide_tlp_sev:1; /* [29:29] */
		uint32_t pcrc_check_failed_sev:1; /* [30:30] */
		uint32_t tlp_translation_egress_blocked_sev:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_corr_err_status_off {
	struct {
		uint32_t rx_err_status:1; /* [0:0] */
		uint32_t rsvdp_1:5; /* [5:1] */
		uint32_t bad_tlp_status:1; /* [6:6] */
		uint32_t bad_dllp_status:1; /* [7:7] */
		uint32_t replay_no_roleover_status:1; /* [8:8] */
		uint32_t rsvdp_9:3; /* [11:9] */
		uint32_t rpl_timer_timeout_status:1; /* [12:12] */
		uint32_t advisory_non_fatal_err_status:1; /* [13:13] */
		uint32_t corrected_int_err_status:1; /* [14:14] */
		uint32_t header_log_overflow_status:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_corr_err_mask_off {
	struct {
		uint32_t rx_err_mask:1; /* [0:0] */
		uint32_t rsvdp_1:5; /* [5:1] */
		uint32_t bad_tlp_mask:1; /* [6:6] */
		uint32_t bad_dllp_mask:1; /* [7:7] */
		uint32_t replay_no_roleover_mask:1; /* [8:8] */
		uint32_t rsvdp_9:3; /* [11:9] */
		uint32_t rpl_timer_timeout_mask:1; /* [12:12] */
		uint32_t advisory_non_fatal_err_mask:1; /* [13:13] */
		uint32_t corrected_int_err_mask:1; /* [14:14] */
		uint32_t header_log_overflow_mask:1; /* [15:15] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_adv_err_cap_ctrl_off {
	struct {
		uint32_t first_err_pointer:5; /* [4:0] */
		uint32_t ecrc_gen_cap:1; /* [5:5] */
		uint32_t ecrc_gen_en:1; /* [6:6] */
		uint32_t ecrc_check_cap:1; /* [7:7] */
		uint32_t ecrc_check_en:1; /* [8:8] */
		uint32_t multiple_header_cap:1; /* [9:9] */
		uint32_t multiple_header_en:1; /* [10:10] */
		uint32_t tlp_prfx_log_present:1; /* [11:11] */
		uint32_t cto_prfx_hdr_log_cap:1; /* [12:12] */
		uint32_t reserved_bit_0:11;
		uint32_t rsvdp_24:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_0_off {
	struct {
		uint32_t first_dword_first_byte:8; /* [7:0] */
		uint32_t first_dword_second_byte:8; /* [15:8] */
		uint32_t first_dword_third_byte:8; /* [23:16] */
		uint32_t first_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_1_off {
	struct {
		uint32_t second_dword_first_byte:8; /* [7:0] */
		uint32_t second_dword_second_byte:8; /* [15:8] */
		uint32_t second_dword_third_byte:8; /* [23:16] */
		uint32_t second_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_2_off {
	struct {
		uint32_t third_dword_first_byte:8; /* [7:0] */
		uint32_t third_dword_second_byte:8; /* [15:8] */
		uint32_t third_dword_third_byte:8; /* [23:16] */
		uint32_t third_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_3_off {
	struct {
		uint32_t fourth_dword_first_byte:8; /* [7:0] */
		uint32_t fourth_dword_second_byte:8; /* [15:8] */
		uint32_t fourth_dword_third_byte:8; /* [23:16] */
		uint32_t fourth_dword_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_1_off {
	struct {
		uint32_t cfg_tlp_pfx_log_1_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_1_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_1_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_1_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_2_off {
	struct {
		uint32_t cfg_tlp_pfx_log_2_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_2_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_2_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_2_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_3_off {
	struct {
		uint32_t cfg_tlp_pfx_log_3_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_3_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_3_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_3_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_4_off {
	struct {
		uint32_t cfg_tlp_pfx_log_4_first_byte:8; /* [7:0] */
		uint32_t cfg_tlp_pfx_log_4_second_byte:8; /* [15:8] */
		uint32_t cfg_tlp_pfx_log_4_third_byte:8; /* [23:16] */
		uint32_t cfg_tlp_pfx_log_4_fourth_byte:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_ari_cap_vf_ari_base {
	struct {
		uint32_t ari_pcie_extended_cap_id:16; /* [15:0] */
		uint32_t ari_cap_version:4; /* [19:16] */
		uint32_t ari_next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_ari_cap_vf_cap_reg {
	struct {
		uint32_t ari_mfvc_fun_grp_cap:1; /* [0:0] */
		uint32_t ari_acs_fun_grp_cap:1; /* [1:1] */
		uint32_t rsvdp_2:6; /* [7:2] */
		uint32_t ari_next_fun_num:8; /* [15:8] */
		uint32_t ari_mfvc_fun_grp_en:1; /* [16:16] */
		uint32_t ari_acs_fun_grp_en:1; /* [17:17] */
		uint32_t rsvdp_18:2; /* [19:18] */
		uint32_t ari_fun_grp:3; /* [22:20] */
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_tph_cap_vf_tph_ext_cap_hdr_reg {
	struct {
		uint32_t pcie_ext_cap_id:16; /* [15:0] */
		uint32_t tph_req_cap_ver:4; /* [19:16] */
		uint32_t tph_req_next_ptr:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_tph_cap_vf_tph_req_cap_reg_reg {
	struct {
		uint32_t tph_req_no_st_mode:1; /* [0:0] */
		uint32_t tph_req_cap_int_vec:1; /* [1:1] */
		uint32_t tph_req_device_spec:1; /* [2:2] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t tph_req_extended_tph:1; /* [8:8] */
		uint32_t tph_req_cap_st_table_loc_0:1; /* [9:9] */
		uint32_t tph_req_cap_st_table_loc_1:1; /* [10:10] */
		uint32_t rsvdp_11:5; /* [15:11] */
		uint32_t tph_req_cap_st_table_size:11; /* [26:16] */
		uint32_t rsvdp_27:5; /* [31:27] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_tph_cap_vf_tph_req_control_reg_reg {
	struct {
		uint32_t tph_req_st_mode_select:3; /* [2:0] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t tph_req_ctrl_req_en:2; /* [9:8] */
		uint32_t rsvdp_10:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_ats_cap_vf_ats_cap_hdr_reg {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_ats_cap_vf_ats_capabilities_ctrl_reg {
	struct {
		uint32_t invalidate_q_depth:5; /* [4:0] */
		uint32_t page_aligned_req:1; /* [5:5] */
		uint32_t global_inval_spprtd:1; /* [6:6] */
		uint32_t rsvdp_7:9; /* [15:7] */
		uint32_t stu:5; /* [20:16] */
		uint32_t rsvdp_21:10; /* [30:21] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_acs_cap_vf_acs_cap_hdr_reg {
	struct {
		uint32_t cap_id:16; /* [15:0] */
		uint32_t cap_version:4; /* [19:16] */
		uint32_t next_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_acs_cap_vf_acs_capabilities_ctrl_reg {
	struct {
		uint32_t acs_src_valid:1; /* [0:0] */
		uint32_t acs_at_block:1; /* [1:1] */
		uint32_t acs_p2p_req_redirect:1; /* [2:2] */
		uint32_t acs_p2p_cpl_redirect:1; /* [3:3] */
		uint32_t acs_usp_forwarding:1; /* [4:4] */
		uint32_t acs_p2p_egress_control:1; /* [5:5] */
		uint32_t acs_direct_translated_p2p:1; /* [6:6] */
		uint32_t rsvdp_7:1; /* [7:7] */
		uint32_t acs_egress_ctrl_size:8; /* [15:8] */
		uint32_t acs_src_valid_en:1; /* [16:16] */
		uint32_t acs_at_block_en:1; /* [17:17] */
		uint32_t acs_p2p_req_redirect_en:1; /* [18:18] */
		uint32_t acs_p2p_cpl_redirect_en:1; /* [19:19] */
		uint32_t acs_usp_forwarding_en:1; /* [20:20] */
		uint32_t acs_p2p_egress_control_en:1; /* [21:21] */
		uint32_t acs_direct_translated_p2p_en:1; /* [22:22] */
		uint32_t rsvdp_23:9; /* [31:23] */
	};
	uint32_t val;
};

union pcie_ctrl_vf_pf0_acs_cap_vf_acs_egress_ctrl_vector_reg0 {
	struct {
		uint32_t acs_egress_ctrl_vector_reg0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar0_mask_reg {
	struct {
		uint32_t pci_type0_bar0_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar0_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar1_mask_reg {
	struct {
		uint32_t pci_type0_bar1_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar1_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar2_mask_reg {
	struct {
		uint32_t pci_type0_bar2_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar2_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar3_mask_reg {
	struct {
		uint32_t pci_type0_bar3_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar3_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar4_mask_reg {
	struct {
		uint32_t pci_type0_bar4_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar4_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_bar5_mask_reg {
	struct {
		uint32_t pci_type0_bar5_enabled:1; /* [0:0] */
		uint32_t pci_type0_bar5_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_type0_hdr_dbi2_exp_rom_bar_mask_reg {
	struct {
		uint32_t rom_bar_enabled:1; /* [0:0] */
		uint32_t rom_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_pcie_cap_dbi2_shadow_link_capabilities_reg {
	struct {
		uint32_t pcie_cap_max_link_speed:4; /* [3:0] */
		uint32_t pcie_cap_max_link_width:6; /* [9:4] */
		uint32_t pcie_cap_active_state_link_pm_support:2; /* [11:10] */
		uint32_t shadow_pcie_cap_l0s_exit_latency:3; /* [14:12] */
		uint32_t shadow_pcie_cap_l1_exit_latency:3; /* [17:15] */
		uint32_t pcie_cap_clock_power_man:1; /* [18:18] */
		uint32_t pcie_cap_surprise_down_err_rep_cap:1; /* [19:19] */
		uint32_t pcie_cap_dll_active_rep_cap:1; /* [20:20] */
		uint32_t pcie_cap_link_bw_not_cap:1; /* [21:21] */
		uint32_t pcie_cap_aspm_opt_compliance:1; /* [22:22] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t pcie_cap_port_num:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_dbi2_shadow_pci_msix_cap_id_next_ctrl_reg {
	struct {
		uint32_t pci_msix_reserved0:16; /* [15:0] */
		uint32_t pci_msix_table_size:11; /* [26:16] */
		uint32_t pci_msix_reserved1:5; /* [31:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_dbi2_shadow_msix_table_offset_reg {
	struct {
		uint32_t pci_msix_bir:3; /* [2:0] */
		uint32_t pci_msix_table_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_msix_cap_dbi2_shadow_msix_pba_offset_reg {
	struct {
		uint32_t pci_msix_pba_bir:3; /* [2:0] */
		uint32_t pci_msix_pba_offset:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_dbi2_shadow_sriov_vf_offset_position {
	struct {
		uint32_t shadow_sriov_vf_offset:16; /* [15:0] */
		uint32_t shadow_sriov_vf_stride:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar2_mask_reg {
	struct {
		uint32_t pci_sriov_bar2_enabled:1; /* [0:0] */
		uint32_t pci_sriov_bar2_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar3_mask_reg {
	struct {
		uint32_t pci_sriov_bar3_enabled:1; /* [0:0] */
		uint32_t pci_sriov_bar3_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar4_mask_reg {
	struct {
		uint32_t pci_sriov_bar4_enabled:1; /* [0:0] */
		uint32_t pci_sriov_bar4_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar5_mask_reg {
	struct {
		uint32_t pci_sriov_bar5_enabled:1; /* [0:0] */
		uint32_t pci_sriov_bar5_mask:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_tph_cap_dbi2_shadow_tph_req_cap_reg_reg {
	struct {
		uint32_t tph_req_no_st_mode:1; /* [0:0] */
		uint32_t tph_req_cap_int_vec:1; /* [1:1] */
		uint32_t tph_req_device_spec:1; /* [2:2] */
		uint32_t rsvdp_3:5; /* [7:3] */
		uint32_t tph_req_extended_tph:1; /* [8:8] */
		uint32_t tph_req_cap_st_table_loc_0:1; /* [9:9] */
		uint32_t tph_req_cap_st_table_loc_1:1; /* [10:10] */
		uint32_t rsvdp_11:5; /* [15:11] */
		uint32_t tph_req_cap_st_table_size:11; /* [26:16] */
		uint32_t rsvdp_27:5; /* [31:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_1_off_outbound {
	struct {
		uint32_t type_:5; /* [4:0] */
		uint32_t tc:3; /* [7:5] */
		uint32_t td:1; /* [8:8] */
		uint32_t attr:2; /* [10:9] */
		uint32_t ido:1; /* [11:11] */
		uint32_t th:1; /* [12:12] */
		uint32_t increase_region_size:1; /* [13:13] */
		uint32_t reserved_bit_0:2;
		uint32_t at:2; /* [17:16] */
		uint32_t ph:2; /* [19:18] */
		uint32_t ctrl_1_func_num:1; /* [20:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_2_off_outbound {
	struct {
		uint32_t msg_code:8; /* [7:0] */
		uint32_t tag:8; /* [15:8] */
		uint32_t tag_substitute_en:1; /* [16:16] */
		uint32_t msb2bits_tag:2; /* [18:17] */
		uint32_t func_bypass:1; /* [19:19] */
		uint32_t snp:1; /* [20:20] */
		uint32_t tlp_header_fields_bypass:1; /* [21:21] */
		uint32_t inhibit_payload:1; /* [22:22] */
		uint32_t header_substitute_en:1; /* [23:23] */
		uint32_t reserved_bit_0:3;
		uint32_t dma_bypass:1; /* [27:27] */
		uint32_t cfg_shift_mode:1; /* [28:28] */
		uint32_t invert_mode:1; /* [29:29] */
		uint32_t reserved_bit_1:1;
		uint32_t region_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_lwr_base_addr_off_outbound {
	struct {
		uint32_t lwr_base_hw:12; /* [11:0] */
		uint32_t lwr_base_rw:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_upper_base_addr_off_outbound {
	struct {
		uint32_t upper_base_rw; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_limit_addr_off_outbound {
	struct {
		uint32_t cbuf_incr:4; /* [3:0] */
		uint32_t limit_addr_hw:8; /* [11:4] */
		uint32_t limit_addr_rw:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_lwr_target_addr_off_outbound {
	struct {
		uint32_t lwr_target_rw_outbound; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_upper_target_addr_off_outbound {
	struct {
		uint32_t upper_target_rw; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_3_off_outbound {
	struct {
		uint32_t vf_number:4; /* [3:0] */
		uint32_t rsvdp_vf_number:27; /* [30:4] */
		uint32_t vf_active:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_uppr_limit_addr_off_outbound {
	struct {
		uint32_t uppr_limit_addr_rw:8; /* [7:0] */
		uint32_t uppr_limit_addr_hw:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_1_off_inbound {
	struct {
		uint32_t type_:5; /* [4:0] */
		uint32_t tc:3; /* [7:5] */
		uint32_t td:1; /* [8:8] */
		uint32_t attr:2; /* [10:9] */
		uint32_t ido:1; /* [11:11] */
		uint32_t th:1; /* [12:12] */
		uint32_t increase_region_size:1; /* [13:13] */
		uint32_t reserved_bit_0:2;
		uint32_t at:2; /* [17:16] */
		uint32_t ph:2; /* [19:18] */
		uint32_t ctrl_1_func_num:1; /* [20:20] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_2_off_inbound {
	struct {
		uint32_t msg_code:8; /* [7:0] */
		uint32_t bar_num:3; /* [10:8] */
		uint32_t reserved_bit_0:2;
		uint32_t msg_type_match_mode:1; /* [13:13] */
		uint32_t tc_match_en:1; /* [14:14] */
		uint32_t td_match_en:1; /* [15:15] */
		uint32_t attr_match_en:1; /* [16:16] */
		uint32_t th_match_en:1; /* [17:17] */
		uint32_t at_match_en:1; /* [18:18] */
		uint32_t func_num_match_en:1; /* [19:19] */
		uint32_t vf_match_en:1; /* [20:20] */
		uint32_t msg_code_match_en:1; /* [21:21] */
		uint32_t ph_match_en:1; /* [22:22] */
		uint32_t single_addr_loc_trans_en:1; /* [23:23] */
		uint32_t response_code:2; /* [25:24] */
		uint32_t vfbar_match_mode_en:1; /* [26:26] */
		uint32_t fuzzy_type_match_code:1; /* [27:27] */
		uint32_t cfg_shift_mode:1; /* [28:28] */
		uint32_t invert_mode:1; /* [29:29] */
		uint32_t match_mode:1; /* [30:30] */
		uint32_t region_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_lwr_base_addr_off_inbound {
	struct {
		uint32_t lwr_base_hw:12; /* [11:0] */
		uint32_t lwr_base_rw:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_upper_base_addr_off_inbound {
	struct {
		uint32_t upper_base_rw; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_limit_addr_off_inbound {
	struct {
		uint32_t cbuf_incr:4; /* [3:0] */
		uint32_t limit_addr_hw:8; /* [11:4] */
		uint32_t limit_addr_rw:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_lwr_target_addr_off_inbound {
	struct {
		uint32_t lwr_target_hw:12; /* [11:0] */
		uint32_t lwr_target_rw:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_upper_target_addr_off_inbound {
	struct {
		uint32_t upper_target_rw; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_3_off_inbound {
	struct {
		uint32_t vf_number:4; /* [3:0] */
		uint32_t rsvdp_vf_number:27; /* [30:4] */
		uint32_t vf_active:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_atu_cap_iatu_uppr_limit_addr_off_inbound {
	struct {
		uint32_t uppr_limit_addr_rw:8; /* [7:0] */
		uint32_t uppr_limit_addr_hw:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_en_off_wrch {
	struct {
		uint32_t enable:1; /* [0:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_doorbell_off_wrch {
	struct {
		uint32_t db_start:1; /* [0:0] */
		uint32_t db_stop:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_elem_pf_off_wrch {
	struct {
		uint32_t element_prefetch:7; /* [6:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_llp_low_off_wrch {
	struct {
		uint32_t element_list_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_llp_high_off_wrch {
	struct {
		uint32_t element_list_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_cycle_off_wrch {
	struct {
		uint32_t cycle_bit:1; /* [0:0] */
		uint32_t cycle_state:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_xfersize_off_wrch {
	struct {
		uint32_t xfersize; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_sar_low_off_wrch {
	struct {
		uint32_t sar_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_sar_high_off_wrch {
	struct {
		uint32_t sar_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_dar_low_off_wrch {
	struct {
		uint32_t dar_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_dar_high_off_wrch {
	struct {
		uint32_t dar_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_watermark_en_off_wrch {
	struct {
		uint32_t rwie:1; /* [0:0] */
		uint32_t lwie:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_control1_off_wrch {
	struct {
		uint32_t llen:1; /* [0:0] */
		uint32_t mem_type:1; /* [1:1] */
		uint32_t src_snoop:1; /* [2:2] */
		uint32_t dst_snoop:1; /* [3:3] */
		uint32_t ro:1; /* [4:4] */
		uint32_t at:2; /* [6:5] */
		uint32_t t_bit:1; /* [7:7] */
		uint32_t t_bit_src:1; /* [8:8] */
		uint32_t reserved_bit_0:7;
		uint32_t th:1; /* [16:16] */
		uint32_t ph:2; /* [18:17] */
		uint32_t st:8; /* [26:19] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_func_num_off_wrch {
	struct {
		uint32_t pf:8; /* [7:0] */
		uint32_t reserved_bit_0:8;
		uint32_t vf_en:1; /* [16:16] */
		uint32_t vf:8; /* [24:17] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_qos_off_wrch {
	struct {
		uint32_t tc:3; /* [2:0] */
		uint32_t weight:5; /* [7:3] */
		uint32_t reserved_bit_0:8;
		uint32_t pf_depth:10; /* [25:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_status_off_wrch {
	struct {
		uint32_t status:2; /* [1:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_status_off_wrch {
	struct {
		uint32_t stop:1; /* [0:0] */
		uint32_t watermark:1; /* [1:1] */
		uint32_t abort:1; /* [2:2] */
		uint32_t error:4; /* [6:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_setup_off_wrch {
	struct {
		uint32_t stop_mask:1; /* [0:0] */
		uint32_t watermark_mask:1; /* [1:1] */
		uint32_t abort_mask:1; /* [2:2] */
		uint32_t rsie:1; /* [3:3] */
		uint32_t lsie:1; /* [4:4] */
		uint32_t raie:1; /* [5:5] */
		uint32_t laie:1; /* [6:6] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_clear_off_wrch {
	struct {
		uint32_t stop_clear:1; /* [0:0] */
		uint32_t watermark_clear:1; /* [1:1] */
		uint32_t abort_clear:1; /* [2:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_low_off_wrch {
	struct {
		uint32_t msi_stop_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_high_off_wrch {
	struct {
		uint32_t msi_stop_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_low_off_wrch {
	struct {
		uint32_t msi_watermark_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_high_off_wrch {
	struct {
		uint32_t msi_watermark_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_low_off_wrch {
	struct {
		uint32_t msi_abort_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_high_off_wrch {
	struct {
		uint32_t msi_abort_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_msgd_off_wrch {
	struct {
		uint32_t msi_message:16; /* [15:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_en_off_rdch {
	struct {
		uint32_t enable:1; /* [0:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_doorbell_off_rdch {
	struct {
		uint32_t db_start:1; /* [0:0] */
		uint32_t db_stop:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_elem_pf_off_rdch {
	struct {
		uint32_t element_prefetch:7; /* [6:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_llp_low_off_rdch {
	struct {
		uint32_t element_list_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_llp_high_off_rdch {
	struct {
		uint32_t element_list_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_cycle_off_rdch {
	struct {
		uint32_t cycle_bit:1; /* [0:0] */
		uint32_t cycle_state:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_xfersize_off_rdch {
	struct {
		uint32_t xfersize; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_sar_low_off_rdch {
	struct {
		uint32_t sar_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_sar_high_off_rdch {
	struct {
		uint32_t sar_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_dar_low_off_rdch {
	struct {
		uint32_t dar_ptr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_dar_high_off_rdch {
	struct {
		uint32_t dar_ptr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_watermark_en_off_rdch {
	struct {
		uint32_t rwie:1; /* [0:0] */
		uint32_t lwie:1; /* [1:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_control1_off_rdch {
	struct {
		uint32_t llen:1; /* [0:0] */
		uint32_t mem_type:1; /* [1:1] */
		uint32_t src_snoop:1; /* [2:2] */
		uint32_t dst_snoop:1; /* [3:3] */
		uint32_t ro:1; /* [4:4] */
		uint32_t at:2; /* [6:5] */
		uint32_t t_bit:1; /* [7:7] */
		uint32_t t_bit_src:1; /* [8:8] */
		uint32_t reserved_bit_0:7;
		uint32_t th:1; /* [16:16] */
		uint32_t ph:2; /* [18:17] */
		uint32_t st:8; /* [26:19] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_func_num_off_rdch {
	struct {
		uint32_t pf:8; /* [7:0] */
		uint32_t reserved_bit_0:8;
		uint32_t vf_en:1; /* [16:16] */
		uint32_t vf:8; /* [24:17] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_qos_off_rdch {
	struct {
		uint32_t tc:3; /* [2:0] */
		uint32_t weight:5; /* [7:3] */
		uint32_t reserved_bit_0:8;
		uint32_t pf_depth:10; /* [25:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_status_off_rdch {
	struct {
		uint32_t status:2; /* [1:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_status_off_rdch {
	struct {
		uint32_t stop:1; /* [0:0] */
		uint32_t watermark:1; /* [1:1] */
		uint32_t abort:1; /* [2:2] */
		uint32_t error:4; /* [6:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_setup_off_rdch {
	struct {
		uint32_t stop_mask:1; /* [0:0] */
		uint32_t watermark_mask:1; /* [1:1] */
		uint32_t abort_mask:1; /* [2:2] */
		uint32_t rsie:1; /* [3:3] */
		uint32_t lsie:1; /* [4:4] */
		uint32_t raie:1; /* [5:5] */
		uint32_t laie:1; /* [6:6] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_int_clear_off_rdch {
	struct {
		uint32_t stop_clear:1; /* [0:0] */
		uint32_t watermark_clear:1; /* [1:1] */
		uint32_t abort_clear:1; /* [2:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_low_off_rdch {
	struct {
		uint32_t msi_stop_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_high_off_rdch {
	struct {
		uint32_t msi_stop_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_low_off_rdch {
	struct {
		uint32_t msi_watermark_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_high_off_rdch {
	struct {
		uint32_t msi_watermark_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_low_off_rdch {
	struct {
		uint32_t msi_abort_addr_low; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_high_off_rdch {
	struct {
		uint32_t msi_abort_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_hdma_cap_hdma_msi_msgd_off_rdch {
	struct {
		uint32_t msi_message:16; /* [15:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_ack_latency_timer_off {
	struct {
		uint32_t round_trip_latency_time_limit:16; /* [15:0] */
		uint32_t replay_time_limit:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vendor_spec_dllp_off {
	struct {
		uint32_t vendor_spec_dllp; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_port_force_off {
	struct {
		uint32_t link_num:8; /* [7:0] */
		uint32_t forced_ltssm:4; /* [11:8] */
		uint32_t rsvdp_12:3; /* [14:12] */
		uint32_t force_en:1; /* [15:15] */
		uint32_t link_state:6; /* [21:16] */
		uint32_t support_part_lanes_rxei_exit:1; /* [22:22] */
		uint32_t do_deskew_for_sris:1; /* [23:23] */
		uint32_t reserved_bit_0:4;
		uint32_t rsvdp_28:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_ack_f_aspm_ctrl_off {
	struct {
		uint32_t ack_freq:8; /* [7:0] */
		uint32_t ack_n_fts:8; /* [15:8] */
		uint32_t common_clk_n_fts:8; /* [23:16] */
		uint32_t l0s_entrance_latency:3; /* [26:24] */
		uint32_t l1_entrance_latency:3; /* [29:27] */
		uint32_t enter_aspm:1; /* [30:30] */
		uint32_t aspm_l1_timer_enable:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_port_link_ctrl_off {
	struct {
		uint32_t vendor_specific_dllp_req:1; /* [0:0] */
		uint32_t scramble_disable:1; /* [1:1] */
		uint32_t loopback_enable:1; /* [2:2] */
		uint32_t reset_assert:1; /* [3:3] */
		uint32_t rsvdp_4:1; /* [4:4] */
		uint32_t dll_link_en:1; /* [5:5] */
		uint32_t link_disable:1; /* [6:6] */
		uint32_t fast_link_mode:1; /* [7:7] */
		uint32_t link_rate:4; /* [11:8] */
		uint32_t rsvdp_12:4; /* [15:12] */
		uint32_t link_capable:6; /* [21:16] */
		uint32_t reserved_bit_0:2;
		uint32_t beacon_enable:1; /* [24:24] */
		uint32_t corrupt_lcrc_enable:1; /* [25:25] */
		uint32_t extended_synch:1; /* [26:26] */
		uint32_t transmit_lane_reversale_enable:1; /* [27:27] */
		uint32_t rsvdp_28:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_lane_skew_off {
	struct {
		uint32_t insert_lane_skew:23; /* [22:0] */
		uint32_t drift_buffer_deskew_enable:1; /* [23:23] */
		uint32_t flow_ctrl_disable:1; /* [24:24] */
		uint32_t ack_nak_disable:1; /* [25:25] */
		uint32_t elastic_buffer_mode:1; /* [26:26] */
		uint32_t implement_num_lanes:4; /* [30:27] */
		uint32_t disable_lane_to_lane_deskew:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_timer_ctrl_max_func_num_off {
	struct {
		uint32_t max_func_num:8; /* [7:0] */
		uint32_t rsvdp_8:6; /* [13:8] */
		uint32_t timer_mod_replay_timer:5; /* [18:14] */
		uint32_t timer_mod_ack_nak:5; /* [23:19] */
		uint32_t update_freq_timer:5; /* [28:24] */
		uint32_t fast_link_scaling_factor:2; /* [30:29] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_symbol_timer_filter_1_off {
	struct {
		uint32_t skp_int_val:11; /* [10:0] */
		uint32_t eidle_timer:4; /* [14:11] */
		uint32_t disable_fc_wd_timer:1; /* [15:15] */
		uint32_t mask_radm_1:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_filter_mask_2_off {
	struct {
		uint32_t mask_radm_2; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pl_debug0_off {
	struct {
		uint32_t deb_reg_0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pl_debug1_off {
	struct {
		uint32_t deb_reg_1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_tx_p_fc_credit_status_off {
	struct {
		uint32_t tx_p_data_fc_credit:16; /* [15:0] */
		uint32_t tx_p_header_fc_credit:12; /* [27:16] */
		uint32_t rsvdp_tx_p_fc_credit_status:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_tx_np_fc_credit_status_off {
	struct {
		uint32_t tx_np_data_fc_credit:16; /* [15:0] */
		uint32_t tx_np_header_fc_credit:12; /* [27:16] */
		uint32_t rsvdp_tx_np_fc_credit_status:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_tx_cpl_fc_credit_status_off {
	struct {
		uint32_t tx_cpl_data_fc_credit:16; /* [15:0] */
		uint32_t tx_cpl_header_fc_credit:12; /* [27:16] */
		uint32_t rsvdp_tx_cpl_fc_credit_status:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_queue_status_off {
	struct {
		uint32_t rx_tlp_fc_credit_non_return:1; /* [0:0] */
		uint32_t tx_retry_buffer_ne:1; /* [1:1] */
		uint32_t rx_queue_non_empty:1; /* [2:2] */
		uint32_t rx_queue_overflow:1; /* [3:3] */
		uint32_t rsvdp_4:9; /* [12:4] */
		uint32_t rx_serialization_q_non_empty:1; /* [13:13] */
		uint32_t rx_serialization_q_write_err:1; /* [14:14] */
		uint32_t rx_serialization_q_read_err:1; /* [15:15] */
		uint32_t timer_mod_flow_control:13; /* [28:16] */
		uint32_t rsvdp_29:2; /* [30:29] */
		uint32_t timer_mod_flow_control_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vc_tx_arbi_1_off {
	struct {
		uint32_t wrr_weight_vc_0:8; /* [7:0] */
		uint32_t wrr_weight_vc_1:8; /* [15:8] */
		uint32_t wrr_weight_vc_2:8; /* [23:16] */
		uint32_t wrr_weight_vc_3:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vc_tx_arbi_2_off {
	struct {
		uint32_t wrr_weight_vc_4:8; /* [7:0] */
		uint32_t wrr_weight_vc_5:8; /* [15:8] */
		uint32_t wrr_weight_vc_6:8; /* [23:16] */
		uint32_t wrr_weight_vc_7:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vc0_p_rx_q_ctrl_off {
	struct {
		uint32_t vc0_p_data_credit:12; /* [11:0] */
		uint32_t vc0_p_header_credit:8; /* [19:12] */
		uint32_t reserved4:1; /* [20:20] */
		uint32_t vc0_p_tlp_q_mode:3; /* [23:21] */
		uint32_t vc0_p_hdr_scale:2; /* [25:24] */
		uint32_t vc0_p_data_scale:2; /* [27:26] */
		uint32_t reserved5:2; /* [29:28] */
		uint32_t tlp_type_ordering_vc0:1; /* [30:30] */
		uint32_t vc_ordering_rx_q:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vc0_np_rx_q_ctrl_off {
	struct {
		uint32_t vc0_np_data_credit:12; /* [11:0] */
		uint32_t vc0_np_header_credit:8; /* [19:12] */
		uint32_t reserved6:1; /* [20:20] */
		uint32_t vc0_np_tlp_q_mode:3; /* [23:21] */
		uint32_t vc0_np_hdr_scale:2; /* [25:24] */
		uint32_t vc0_np_data_scale:2; /* [27:26] */
		uint32_t reserved7:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_vc0_cpl_rx_q_ctrl_off {
	struct {
		uint32_t vc0_cpl_data_credit:12; /* [11:0] */
		uint32_t vc0_cpl_header_credit:8; /* [19:12] */
		uint32_t reserved8:1; /* [20:20] */
		uint32_t vc0_cpl_tlp_q_mode:3; /* [23:21] */
		uint32_t vc0_cpl_hdr_scale:2; /* [25:24] */
		uint32_t vc0_cpl_data_scale:2; /* [27:26] */
		uint32_t reserved9:4; /* [31:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen2_ctrl_off {
	struct {
		uint32_t fast_training_seq:8; /* [7:0] */
		uint32_t num_of_lanes:5; /* [12:8] */
		uint32_t pre_det_lane:3; /* [15:13] */
		uint32_t auto_lane_flip_ctrl_en:1; /* [16:16] */
		uint32_t direct_speed_change:1; /* [17:17] */
		uint32_t config_phy_tx_change:1; /* [18:18] */
		uint32_t config_tx_comp_rx:1; /* [19:19] */
		uint32_t sel_deemphasis:1; /* [20:20] */
		uint32_t gen1_ei_inference:1; /* [21:21] */
		uint32_t select_deemph_var_mux:1; /* [22:22] */
		uint32_t selectable_deemph_bit_mux:1; /* [23:23] */
		uint32_t lane_under_test:4; /* [27:24] */
		uint32_t eq_for_loopback:1; /* [28:28] */
		uint32_t tx_mod_cmpl_pattern_for_loopback:1; /* [29:29] */
		uint32_t force_lane_flip:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_phy_status_off {
	struct {
		uint32_t phy_status; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_phy_control_off {
	struct {
		uint32_t phy_control; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_trgt_map_ctrl_off {
	struct {
		uint32_t target_map_pf:6; /* [5:0] */
		uint32_t target_map_rom:1; /* [6:6] */
		uint32_t target_map_vf:6; /* [12:7] */
		uint32_t target_map_reserved_13_15:3; /* [15:13] */
		uint32_t target_map_index:5; /* [20:16] */
		uint32_t target_map_reserved_21_31:11; /* [31:21] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_clock_gating_ctrl_off {
	struct {
		uint32_t radm_clk_gating_en:1; /* [0:0] */
		uint32_t axi_clk_gating_en:1; /* [1:1] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_related_off {
	struct {
		uint32_t gen3_zrxdc_noncompl:1; /* [0:0] */
		uint32_t no_seed_value_change:1; /* [1:1] */
		uint32_t rsvdp_2:6; /* [7:2] */
		uint32_t disable_scrambler_gen_3:1; /* [8:8] */
		uint32_t eq_phase_2_3:1; /* [9:9] */
		uint32_t eq_eieos_cnt:1; /* [10:10] */
		uint32_t eq_redo:1; /* [11:11] */
		uint32_t rxeq_ph01_en:1; /* [12:12] */
		uint32_t rxeq_rgrdless_rxts:1; /* [13:13] */
		uint32_t rsvdp_14:1; /* [14:14] */
		uint32_t gen3_eq_pset_coef_map_mode_prog:1; /* [15:15] */
		uint32_t gen3_equalization_disable:1; /* [16:16] */
		uint32_t gen3_dllp_xmt_delay_disable:1; /* [17:17] */
		uint32_t gen3_dc_balance_disable:1; /* [18:18] */
		uint32_t rsvdp_19:2; /* [20:19] */
		uint32_t auto_eq_disable:1; /* [21:21] */
		uint32_t usp_send_8gt_eq_ts2_disable:1; /* [22:22] */
		uint32_t gen3_eq_invreq_eval_diff_disable:1; /* [23:23] */
		uint32_t rate_shadow_sel:2; /* [25:24] */
		uint32_t rsvdp_26:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_local_fs_lf_off {
	struct {
		uint32_t gen3_eq_local_lf:6; /* [5:0] */
		uint32_t gen3_eq_local_fs:6; /* [11:6] */
		uint32_t rsvdp_12:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_pset_coef_map__0 {
	struct {
		uint32_t gen3_eq_pre_cursor_pset:6; /* [5:0] */
		uint32_t gen3_eq_cursor_pset:6; /* [11:6] */
		uint32_t gen3_eq_post_cursor_pset:6; /* [17:12] */
		uint32_t reserved_bit_0:3;
		uint32_t rsvdp_21:11; /* [31:21] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_pset_index_off {
	struct {
		uint32_t gen3_eq_pset_index:4; /* [3:0] */
		uint32_t rsvdp_4:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_coeff_legality_status_off {
	struct {
		uint32_t gen3_eq_violate_coef_rules:1; /* [0:0] */
		uint32_t rsvdp_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_control_off {
	struct {
		uint32_t gen3_eq_fb_mode:4; /* [3:0] */
		uint32_t gen3_eq_phase23_exit_mode:1; /* [4:4] */
		uint32_t gen3_eq_eval_2ms_disable:1; /* [5:5] */
		uint32_t gen3_lower_rate_eq_redo_enable:1; /* [6:6] */
		uint32_t gen3_eq_eval_2ms_extend:1; /* [7:7] */
		uint32_t gen3_eq_pset_req_vec:16; /* [23:8] */
		uint32_t gen3_eq_fom_inc_initial_eval:1; /* [24:24] */
		uint32_t gen3_eq_pset_req_as_coef:1; /* [25:25] */
		uint32_t gen3_req_send_consec_eieos_for_pset_map:1; /* [26:26] */
		uint32_t gen3_eq_req_num:3; /* [29:27] */
		uint32_t gen3_support_finite_eq_request:1; /* [30:30] */
		uint32_t rsvdp_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen3_eq_fb_mode_dir_change_off {
	struct {
		uint32_t gen3_eq_fmdc_t_min_phase23:5; /* [4:0] */
		uint32_t gen3_eq_fmdc_n_evals:5; /* [9:5] */
		uint32_t gen3_eq_fmdc_max_pre_cusror_delta:4; /* [13:10] */
		uint32_t gen3_eq_fmdc_max_post_cusror_delta:4; /* [17:14] */
		uint32_t reserved_bit_0:4;
		uint32_t rsvdp_22:10; /* [31:22] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_order_rule_ctrl_off {
	struct {
		uint32_t np_pass_p:8; /* [7:0] */
		uint32_t cpl_pass_p:8; /* [15:8] */
		uint32_t rsvdp_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pipe_loopback_control_off {
	struct {
		uint32_t lpbk_rxvalid:16; /* [15:0] */
		uint32_t rxstatus_lane:6; /* [21:16] */
		uint32_t rsvdp_22:2; /* [23:22] */
		uint32_t rxstatus_value:3; /* [26:24] */
		uint32_t rsvdp_27:4; /* [30:27] */
		uint32_t pipe_loopback:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_misc_control_1_off {
	struct {
		uint32_t dbi_ro_wr_en:1; /* [0:0] */
		uint32_t default_target:1; /* [1:1] */
		uint32_t ur_ca_mask_4_trgt1:1; /* [2:2] */
		uint32_t simplified_replay_timer:1; /* [3:3] */
		uint32_t reserved_bit_0:1;
		uint32_t ari_device_number:1; /* [5:5] */
		uint32_t cplq_mng_en:1; /* [6:6] */
		uint32_t cfg_tlp_bypass_en_reg:1; /* [7:7] */
		uint32_t config_limit_reg:10; /* [17:8] */
		uint32_t target_above_config_limit_reg:2; /* [19:18] */
		uint32_t p2p_track_cpl_to_reg:1; /* [20:20] */
		uint32_t p2p_err_rpt_ctrl:1; /* [21:21] */
		uint32_t port_logic_wr_disable:1; /* [22:22] */
		uint32_t ras_reg_pf0_only:1; /* [23:23] */
		uint32_t rasdes_reg_pf0_only:1; /* [24:24] */
		uint32_t err_inj_wr_disable:1; /* [25:25] */
		uint32_t reserved_bit_1:4;
		uint32_t rsvdp_30:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_multi_lane_control_off {
	struct {
		uint32_t target_link_width:6; /* [5:0] */
		uint32_t direct_link_width_change:1; /* [6:6] */
		uint32_t upconfigure_support:1; /* [7:7] */
		uint32_t reliability_link_width_change_enable:1; /* [8:8] */
		uint32_t rsvdp_9:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_phy_interop_ctrl_off {
	struct {
		uint32_t rxstandby_control:8; /* [7:0] */
		uint32_t l1sub_exit_mode:1; /* [8:8] */
		uint32_t l1_nowait_p1:1; /* [9:9] */
		uint32_t l1_clk_sel:1; /* [10:10] */
		uint32_t p2nobeacon_enable:1; /* [11:11] */
		uint32_t phy_rst_timer:18; /* [29:12] */
		uint32_t phy_perst_on_warm_reset:1; /* [30:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_trgt_cpl_lut_delete_entry_off {
	struct {
		uint32_t look_up_id:31; /* [30:0] */
		uint32_t delete_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_link_flush_control_off {
	struct {
		uint32_t auto_flush_en:1; /* [0:0] */
		uint32_t rsvdp_1:23; /* [23:1] */
		uint32_t auto_flush_timeout:8; /* [31:24] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_amba_error_response_default_off {
	struct {
		uint32_t amba_error_response_global:1; /* [0:0] */
		uint32_t rsvdp_1:1; /* [1:1] */
		uint32_t amba_error_response_vendorid:1; /* [2:2] */
		uint32_t amba_error_response_crs:2; /* [4:3] */
		uint32_t rsvdp_5:5; /* [9:5] */
		uint32_t amba_error_response_map:6; /* [15:10] */
		uint32_t reserved_bit_0:12;
		uint32_t rsvdp_28:2; /* [29:28] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_amba_link_timeout_off {
	struct {
		uint32_t link_timeout_period_default:8; /* [7:0] */
		uint32_t link_timeout_enable_default:1; /* [8:8] */
		uint32_t rsvdp_9:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_amba_ordering_ctrl_off {
	struct {
		uint32_t rsvdp_0:1; /* [0:0] */
		uint32_t ax_snp_en:1; /* [1:1] */
		uint32_t rsvdp_2:1; /* [2:2] */
		uint32_t ax_mstr_ordr_p_event_sel:2; /* [4:3] */
		uint32_t rsvdp_5:2; /* [6:5] */
		uint32_t ax_mstr_zerolread_fw:1; /* [7:7] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_coherency_control_1_off {
	struct {
		uint32_t cfg_memtype_value:1; /* [0:0] */
		uint32_t rsvdp_1:1; /* [1:1] */
		uint32_t cfg_memtype_boundary_low_addr:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_coherency_control_2_off {
	struct {
		uint32_t cfg_memtype_boundary_high_addr; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_coherency_control_3_off {
	struct {
		uint32_t reserved_bit_0:3;
		uint32_t cfg_mstr_arcache_mode:4; /* [6:3] */
		uint32_t reserved_bit_1:4;
		uint32_t cfg_mstr_awcache_mode:4; /* [14:11] */
		uint32_t reserved_bit_2:4;
		uint32_t cfg_mstr_arcache_value:4; /* [22:19] */
		uint32_t reserved_bit_3:4;
		uint32_t cfg_mstr_awcache_value:4; /* [30:27] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_axi_mstr_msg_addr_low_off {
	struct {
		uint32_t cfg_aximstr_msg_addr_low_reserved:12; /* [11:0] */
		uint32_t cfg_aximstr_msg_addr_low:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_axi_mstr_msg_addr_high_off {
	struct {
		uint32_t cfg_aximstr_msg_addr_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pcie_version_number_off {
	struct {
		uint32_t version_number; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pcie_version_type_off {
	struct {
		uint32_t version_type; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_msix_address_match_low_off {
	struct {
		uint32_t msix_address_match_en:1; /* [0:0] */
		uint32_t msix_address_match_reserved_1:1; /* [1:1] */
		uint32_t msix_address_match_low:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_msix_address_match_high_off {
	struct {
		uint32_t msix_address_match_high; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_msix_doorbell_off {
	struct {
		uint32_t msix_doorbell_vector:11; /* [10:0] */
		uint32_t msix_doorbell_reserved_11:1; /* [11:11] */
		uint32_t msix_doorbell_tc:3; /* [14:12] */
		uint32_t msix_doorbell_vf_active:1; /* [15:15] */
		uint32_t msix_doorbell_vf:8; /* [23:16] */
		uint32_t msix_doorbell_pf:5; /* [28:24] */
		uint32_t msix_doorbell_reserved_29_31:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_msix_ram_ctrl_off {
	struct {
		uint32_t msix_ram_ctrl_table_ds:1; /* [0:0] */
		uint32_t msix_ram_ctrl_table_sd:1; /* [1:1] */
		uint32_t msix_ram_ctrl_reserved_2_7:6; /* [7:2] */
		uint32_t msix_ram_ctrl_pba_ds:1; /* [8:8] */
		uint32_t msix_ram_ctrl_pba_sd:1; /* [9:9] */
		uint32_t msix_ram_ctrl_reserved_10_15:6; /* [15:10] */
		uint32_t msix_ram_ctrl_bypass:1; /* [16:16] */
		uint32_t msix_ram_ctrl_reserved_17_23:7; /* [23:17] */
		uint32_t msix_ram_ctrl_dbg_table:1; /* [24:24] */
		uint32_t msix_ram_ctrl_dbg_pba:1; /* [25:25] */
		uint32_t msix_ram_ctrl_reserved_26_31:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pcipm_traffic_ctrl_off {
	struct {
		uint32_t pcipm_vdm_traffic_blocked:1; /* [0:0] */
		uint32_t pcipm_new_tlp_client0_blocked:1; /* [1:1] */
		uint32_t pcipm_new_tlp_client1_blocked:1; /* [2:2] */
		uint32_t pcipm_new_tlp_client2_blocked:1; /* [3:3] */
		uint32_t pcipm_reserved_4_7:4; /* [7:4] */
		uint32_t rsvdp_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_aux_clk_freq_off {
	struct {
		uint32_t aux_clk_freq:10; /* [9:0] */
		uint32_t rsvdp_10:22; /* [31:10] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_l1_substates_off {
	struct {
		uint32_t l1sub_t_power_off:2; /* [1:0] */
		uint32_t l1sub_t_l1_2:4; /* [5:2] */
		uint32_t l1sub_t_pclkack_low:2; /* [7:6] */
		uint32_t l1sub_low_power_clock_switch_mode:1; /* [8:8] */
		uint32_t l1sub_t_pclkack_high:5; /* [13:9] */
		uint32_t rsvdp_14:18; /* [31:14] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_powerdown_ctrl_status_off {
	struct {
		uint32_t powerdown_force:1; /* [0:0] */
		uint32_t powerdown_vmain_ack:1; /* [1:1] */
		uint32_t rsvdp_2:2; /* [3:2] */
		uint32_t powerdown_mac_powerdown:4; /* [7:4] */
		uint32_t powerdown_phy_powerdown:4; /* [11:8] */
		uint32_t rsvdp_12:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_phy_interop_ctrl_2_off {
	struct {
		uint32_t pma_pipe_rst_delay_timer:6; /* [5:0] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t dsp_pcipm_l1_enter_delay:4; /* [11:8] */
		uint32_t rsvdp_12:20; /* [31:12] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen4_lane_margining_1_off {
	struct {
		uint32_t gen4_margining_num_timing_steps:6; /* [5:0] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t gen4_margining_max_timing_offset:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t gen4_margining_num_voltage_steps:7; /* [22:16] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t gen4_margining_max_voltage_offset:6; /* [29:24] */
		uint32_t rsvdp_30:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen4_lane_margining_2_off {
	struct {
		uint32_t gen4_margining_sample_rate_voltage:6; /* [5:0] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t gen4_margining_sample_rate_timing:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t gen4_margining_maxlanes:5; /* [20:16] */
		uint32_t rsvdp_21:3; /* [23:21] */
		uint32_t gen4_margining_voltage_supported:1; /* [24:24] */
		uint32_t gen4_margining_ind_up_down_voltage:1; /* [25:25] */
		uint32_t gen4_margining_ind_left_right_timing:1; /* [26:26] */
		uint32_t gen4_margining_sample_reporting_method:1; /* [27:27] */
		uint32_t gen4_margining_ind_error_sampler:1; /* [28:28] */
		uint32_t rsvdp_29:2; /* [30:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen5_lane_margining_1_off {
	struct {
		uint32_t gen5_margining_num_timing_steps:6; /* [5:0] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t gen5_margining_max_timing_offset:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t gen5_margining_num_voltage_steps:7; /* [22:16] */
		uint32_t rsvdp_23:1; /* [23:23] */
		uint32_t gen5_margining_max_voltage_offset:6; /* [29:24] */
		uint32_t rsvdp_30:2; /* [31:30] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_gen5_lane_margining_2_off {
	struct {
		uint32_t gen5_margining_sample_rate_voltage:6; /* [5:0] */
		uint32_t rsvdp_6:2; /* [7:6] */
		uint32_t gen5_margining_sample_rate_timing:6; /* [13:8] */
		uint32_t rsvdp_14:2; /* [15:14] */
		uint32_t gen5_margining_maxlanes:5; /* [20:16] */
		uint32_t rsvdp_21:3; /* [23:21] */
		uint32_t gen5_margining_voltage_supported:1; /* [24:24] */
		uint32_t gen5_margining_ind_up_down_voltage:1; /* [25:25] */
		uint32_t gen5_margining_ind_left_right_timing:1; /* [26:26] */
		uint32_t gen5_margining_sample_reporting_method:1; /* [27:27] */
		uint32_t gen5_margining_ind_error_sampler:1; /* [28:28] */
		uint32_t rsvdp_29:3; /* [31:29] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pipe_related_off {
	struct {
		uint32_t rx_message_bus_write_buffer_depth:4; /* [3:0] */
		uint32_t tx_message_bus_min_write_buffer_depth:4; /* [7:4] */
		uint32_t pipe_garbage_data_mode:1; /* [8:8] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_rx_serialization_q_ctrl_off {
	struct {
		uint32_t almost_full_threshold:16; /* [15:0] */
		uint32_t almost_full_threshold_adj_val:12; /* [27:16] */
		uint32_t rsvdp_28:2; /* [29:28] */
		uint32_t almost_full_threshold_adj_sign:1; /* [30:30] */
		uint32_t rx_serialization_ovflw_prvntn_en:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_dbi_function_bank_ctrl_reg_off {
	struct {
		uint32_t dbi_function_bank_ctrl_reg:1; /* [0:0] */
		uint32_t dbi_function_bank_ctrl_reg_rsvd:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_utility_off {
	struct {
		uint32_t utility; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_pm_utility_off {
	struct {
		uint32_t pm_utility; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_ide_ctrl_off {
	struct {
		uint32_t ide_ctrl_disable:1; /* [0:0] */
		uint32_t early_tdisp_timeout_disable:1; /* [1:1] */
		uint32_t reserved_bit_0:1;
		uint32_t rsvdp_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ctrl_pf0_port_logic_prbs_loopback_test_reg_off {
	struct {
		uint32_t prbs_loopback_test_enable:1; /* [0:0] */
		uint32_t prbs_loopback_test_done:1; /* [1:1] */
		uint32_t prbs_loopback_test_failed:1; /* [2:2] */
		uint32_t prbs_loopback_test_lane_select:4; /* [6:3] */
		uint32_t prbs_loopback_test_started_lanex:1; /* [7:7] */
		uint32_t prbs_loopback_test_error_counter_lanex:8; /* [15:8] */
		uint32_t prbs_loopback_test_unexpected_fail_lanex:1; /* [16:16] */
		uint32_t rsvdp_17:15; /* [31:17] */
	};
	uint32_t val;
};

struct pcie_ctrl_register {
	union pcie_ctrl_pf0_type0_hdr_device_id_vendor_id_reg pf0_type0_hdr_device_id_vendor_id_reg; /* offset : 0x0 */
	union pcie_ctrl_pf0_type0_hdr_status_command_reg pf0_type0_hdr_status_command_reg; /* offset : 0x4 */
	union pcie_ctrl_pf0_type0_hdr_class_code_revision_id pf0_type0_hdr_class_code_revision_id; /* offset : 0x8 */
	union pcie_ctrl_pf0_type0_hdr_bist_header_type_latency_cache_line_size_reg pf0_type0_hdr_bist_header_type_latency_cache_line_size_reg; /* offset : 0xc */
	union pcie_ctrl_pf0_type0_hdr_bar0_reg pf0_type0_hdr_bar0_reg; /* offset : 0x10 */
	union pcie_ctrl_pf0_type0_hdr_bar1_reg pf0_type0_hdr_bar1_reg; /* offset : 0x14 */
	union pcie_ctrl_pf0_type0_hdr_bar2_reg pf0_type0_hdr_bar2_reg; /* offset : 0x18 */
	union pcie_ctrl_pf0_type0_hdr_bar3_reg pf0_type0_hdr_bar3_reg; /* offset : 0x1c */
	union pcie_ctrl_pf0_type0_hdr_bar4_reg pf0_type0_hdr_bar4_reg; /* offset : 0x20 */
	union pcie_ctrl_pf0_type0_hdr_bar5_reg pf0_type0_hdr_bar5_reg; /* offset : 0x24 */
	union pcie_ctrl_pf0_type0_hdr_cardbus_cis_ptr_reg pf0_type0_hdr_cardbus_cis_ptr_reg; /* offset : 0x28 */
	union pcie_ctrl_pf0_type0_hdr_subsystem_id_subsystem_vendor_id_reg pf0_type0_hdr_subsystem_id_subsystem_vendor_id_reg; /* offset : 0x2c */
	union pcie_ctrl_pf0_type0_hdr_exp_rom_base_addr_reg pf0_type0_hdr_exp_rom_base_addr_reg; /* offset : 0x30 */
	union pcie_ctrl_pf0_type0_hdr_pci_cap_ptr_reg pf0_type0_hdr_pci_cap_ptr_reg; /* offset : 0x34 */
	uint32_t reserved_1;
	union pcie_ctrl_pf0_type0_hdr_max_latency_min_grant_interrupt_pin_interrupt_line_reg pf0_type0_hdr_max_latency_min_grant_interrupt_pin_interrupt_line_reg; /* offset : 0x3c */
	union pcie_ctrl_pf0_pm_cap_cap_id_nxt_ptr_reg pf0_pm_cap_cap_id_nxt_ptr_reg; /* offset : 0x40 */
	union pcie_ctrl_pf0_pm_cap_con_status_reg pf0_pm_cap_con_status_reg; /* offset : 0x44 */
	uint32_t reserved_2[10];
	union pcie_ctrl_pf0_pcie_cap_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg pf0_pcie_cap_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg; /* offset : 0x70 */
	union pcie_ctrl_pf0_pcie_cap_device_capabilities_reg pf0_pcie_cap_device_capabilities_reg; /* offset : 0x74 */
	union pcie_ctrl_pf0_pcie_cap_device_control_device_status pf0_pcie_cap_device_control_device_status; /* offset : 0x78 */
	union pcie_ctrl_pf0_pcie_cap_link_capabilities_reg pf0_pcie_cap_link_capabilities_reg; /* offset : 0x7c */
	union pcie_ctrl_pf0_pcie_cap_link_control_link_status_reg pf0_pcie_cap_link_control_link_status_reg; /* offset : 0x80 */
	uint32_t reserved_3[4];
	union pcie_ctrl_pf0_pcie_cap_device_capabilities2_reg pf0_pcie_cap_device_capabilities2_reg; /* offset : 0x94 */
	union pcie_ctrl_pf0_pcie_cap_device_control2_device_status2_reg pf0_pcie_cap_device_control2_device_status2_reg; /* offset : 0x98 */
	union pcie_ctrl_pf0_pcie_cap_link_capabilities2_reg pf0_pcie_cap_link_capabilities2_reg; /* offset : 0x9c */
	union pcie_ctrl_pf0_pcie_cap_link_control2_link_status2_reg pf0_pcie_cap_link_control2_link_status2_reg; /* offset : 0xa0 */
	uint32_t reserved_4[3];
	union pcie_ctrl_pf0_msix_cap_pci_msix_cap_id_next_ctrl_reg pf0_msix_cap_pci_msix_cap_id_next_ctrl_reg; /* offset : 0xb0 */
	union pcie_ctrl_pf0_msix_cap_msix_table_offset_reg pf0_msix_cap_msix_table_offset_reg; /* offset : 0xb4 */
	union pcie_ctrl_pf0_msix_cap_msix_pba_offset_reg pf0_msix_cap_msix_pba_offset_reg; /* offset : 0xb8 */
	uint32_t reserved_5[17];
	union pcie_ctrl_pf0_aer_cap_aer_ext_cap_hdr_off pf0_aer_cap_aer_ext_cap_hdr_off; /* offset : 0x100 */
	union pcie_ctrl_pf0_aer_cap_uncorr_err_status_off pf0_aer_cap_uncorr_err_status_off; /* offset : 0x104 */
	union pcie_ctrl_pf0_aer_cap_uncorr_err_mask_off pf0_aer_cap_uncorr_err_mask_off; /* offset : 0x108 */
	union pcie_ctrl_pf0_aer_cap_uncorr_err_sev_off pf0_aer_cap_uncorr_err_sev_off; /* offset : 0x10c */
	union pcie_ctrl_pf0_aer_cap_corr_err_status_off pf0_aer_cap_corr_err_status_off; /* offset : 0x110 */
	union pcie_ctrl_pf0_aer_cap_corr_err_mask_off pf0_aer_cap_corr_err_mask_off; /* offset : 0x114 */
	union pcie_ctrl_pf0_aer_cap_adv_err_cap_ctrl_off pf0_aer_cap_adv_err_cap_ctrl_off; /* offset : 0x118 */
	union pcie_ctrl_pf0_aer_cap_hdr_log_0_off pf0_aer_cap_hdr_log_0_off; /* offset : 0x11c */
	union pcie_ctrl_pf0_aer_cap_hdr_log_1_off pf0_aer_cap_hdr_log_1_off; /* offset : 0x120 */
	union pcie_ctrl_pf0_aer_cap_hdr_log_2_off pf0_aer_cap_hdr_log_2_off; /* offset : 0x124 */
	union pcie_ctrl_pf0_aer_cap_hdr_log_3_off pf0_aer_cap_hdr_log_3_off; /* offset : 0x128 */
	uint32_t reserved_6[3];
	union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_1_off pf0_aer_cap_tlp_prefix_log_1_off; /* offset : 0x138 */
	union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_2_off pf0_aer_cap_tlp_prefix_log_2_off; /* offset : 0x13c */
	union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_3_off pf0_aer_cap_tlp_prefix_log_3_off; /* offset : 0x140 */
	union pcie_ctrl_pf0_aer_cap_tlp_prefix_log_4_off pf0_aer_cap_tlp_prefix_log_4_off; /* offset : 0x144 */
	union pcie_ctrl_pf0_ari_cap_ari_base pf0_ari_cap_ari_base; /* offset : 0x148 */
	union pcie_ctrl_pf0_ari_cap_cap_reg pf0_ari_cap_cap_reg; /* offset : 0x14c */
	uint32_t reserved_7[2];
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_header_reg pf0_spcie_cap_spcie_cap_header_reg; /* offset : 0x158 */
	union pcie_ctrl_pf0_spcie_cap_link_control3_reg pf0_spcie_cap_link_control3_reg; /* offset : 0x15c */
	union pcie_ctrl_pf0_spcie_cap_lane_err_status_reg pf0_spcie_cap_lane_err_status_reg; /* offset : 0x160 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_0ch_reg pf0_spcie_cap_spcie_cap_off_0ch_reg; /* offset : 0x164 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_10h_reg pf0_spcie_cap_spcie_cap_off_10h_reg; /* offset : 0x168 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_14h_reg pf0_spcie_cap_spcie_cap_off_14h_reg; /* offset : 0x16c */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_18h_reg pf0_spcie_cap_spcie_cap_off_18h_reg; /* offset : 0x170 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_1ch_reg pf0_spcie_cap_spcie_cap_off_1ch_reg; /* offset : 0x174 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_20h_reg pf0_spcie_cap_spcie_cap_off_20h_reg; /* offset : 0x178 */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_24h_reg pf0_spcie_cap_spcie_cap_off_24h_reg; /* offset : 0x17c */
	union pcie_ctrl_pf0_spcie_cap_spcie_cap_off_28h_reg pf0_spcie_cap_spcie_cap_off_28h_reg; /* offset : 0x180 */
	uint32_t reserved_8;
	union pcie_ctrl_pf0_pl16g_cap_pl16g_ext_cap_hdr_reg pf0_pl16g_cap_pl16g_ext_cap_hdr_reg; /* offset : 0x188 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_capability_reg pf0_pl16g_cap_pl16g_capability_reg; /* offset : 0x18c */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_control_reg pf0_pl16g_cap_pl16g_control_reg; /* offset : 0x190 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_status_reg pf0_pl16g_cap_pl16g_status_reg; /* offset : 0x194 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_lc_dpar_status_reg pf0_pl16g_cap_pl16g_lc_dpar_status_reg; /* offset : 0x198 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_first_retimer_dpar_status_reg pf0_pl16g_cap_pl16g_first_retimer_dpar_status_reg; /* offset : 0x19c */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_second_retimer_dpar_status_reg pf0_pl16g_cap_pl16g_second_retimer_dpar_status_reg; /* offset : 0x1a0 */
	uint32_t reserved_9;
	union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_20h_reg pf0_pl16g_cap_pl16g_cap_off_20h_reg; /* offset : 0x1a8 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_24h_reg pf0_pl16g_cap_pl16g_cap_off_24h_reg; /* offset : 0x1ac */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_28h_reg pf0_pl16g_cap_pl16g_cap_off_28h_reg; /* offset : 0x1b0 */
	union pcie_ctrl_pf0_pl16g_cap_pl16g_cap_off_2ch_reg pf0_pl16g_cap_pl16g_cap_off_2ch_reg; /* offset : 0x1b4 */
	union pcie_ctrl_pf0_margin_cap_margin_ext_cap_hdr_reg pf0_margin_cap_margin_ext_cap_hdr_reg; /* offset : 0x1b8 */
	union pcie_ctrl_pf0_margin_cap_margin_port_capabilities_status_reg pf0_margin_cap_margin_port_capabilities_status_reg; /* offset : 0x1bc */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status0_reg pf0_margin_cap_margin_lane_cntrl_status0_reg; /* offset : 0x1c0 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status1_reg pf0_margin_cap_margin_lane_cntrl_status1_reg; /* offset : 0x1c4 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status2_reg pf0_margin_cap_margin_lane_cntrl_status2_reg; /* offset : 0x1c8 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status3_reg pf0_margin_cap_margin_lane_cntrl_status3_reg; /* offset : 0x1cc */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status4_reg pf0_margin_cap_margin_lane_cntrl_status4_reg; /* offset : 0x1d0 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status5_reg pf0_margin_cap_margin_lane_cntrl_status5_reg; /* offset : 0x1d4 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status6_reg pf0_margin_cap_margin_lane_cntrl_status6_reg; /* offset : 0x1d8 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status7_reg pf0_margin_cap_margin_lane_cntrl_status7_reg; /* offset : 0x1dc */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status8_reg pf0_margin_cap_margin_lane_cntrl_status8_reg; /* offset : 0x1e0 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status9_reg pf0_margin_cap_margin_lane_cntrl_status9_reg; /* offset : 0x1e4 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status10_reg pf0_margin_cap_margin_lane_cntrl_status10_reg; /* offset : 0x1e8 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status11_reg pf0_margin_cap_margin_lane_cntrl_status11_reg; /* offset : 0x1ec */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status12_reg pf0_margin_cap_margin_lane_cntrl_status12_reg; /* offset : 0x1f0 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status13_reg pf0_margin_cap_margin_lane_cntrl_status13_reg; /* offset : 0x1f4 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status14_reg pf0_margin_cap_margin_lane_cntrl_status14_reg; /* offset : 0x1f8 */
	union pcie_ctrl_pf0_margin_cap_margin_lane_cntrl_status15_reg pf0_margin_cap_margin_lane_cntrl_status15_reg; /* offset : 0x1fc */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_ext_cap_hdr_reg pf0_pl32g_cap_pl32g_ext_cap_hdr_reg; /* offset : 0x200 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_capability_reg pf0_pl32g_cap_pl32g_capability_reg; /* offset : 0x204 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_control_reg pf0_pl32g_cap_pl32g_control_reg; /* offset : 0x208 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_status_reg pf0_pl32g_cap_pl32g_status_reg; /* offset : 0x20c */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_rcvd_mod_ts_data1_reg pf0_pl32g_cap_pl32g_rcvd_mod_ts_data1_reg; /* offset : 0x210 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_rcvd_mod_ts_data2_reg pf0_pl32g_cap_pl32g_rcvd_mod_ts_data2_reg; /* offset : 0x214 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_tx_mod_ts_data1_reg pf0_pl32g_cap_pl32g_tx_mod_ts_data1_reg; /* offset : 0x218 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_tx_mod_ts_data2_reg pf0_pl32g_cap_pl32g_tx_mod_ts_data2_reg; /* offset : 0x21c */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_20h_reg pf0_pl32g_cap_pl32g_cap_off_20h_reg; /* offset : 0x220 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_24h_reg pf0_pl32g_cap_pl32g_cap_off_24h_reg; /* offset : 0x224 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_28h_reg pf0_pl32g_cap_pl32g_cap_off_28h_reg; /* offset : 0x228 */
	union pcie_ctrl_pf0_pl32g_cap_pl32g_cap_off_2ch_reg pf0_pl32g_cap_pl32g_cap_off_2ch_reg; /* offset : 0x22c */
	union pcie_ctrl_pf0_sriov_cap_sriov_base_reg pf0_sriov_cap_sriov_base_reg; /* offset : 0x230 */
	union pcie_ctrl_pf0_sriov_cap_capabilities_reg pf0_sriov_cap_capabilities_reg; /* offset : 0x234 */
	union pcie_ctrl_pf0_sriov_cap_status_control_reg pf0_sriov_cap_status_control_reg; /* offset : 0x238 */
	union pcie_ctrl_pf0_sriov_cap_total_vfs_initial_vfs_reg pf0_sriov_cap_total_vfs_initial_vfs_reg; /* offset : 0x23c */
	union pcie_ctrl_pf0_sriov_cap_sriov_num_vfs pf0_sriov_cap_sriov_num_vfs; /* offset : 0x240 */
	union pcie_ctrl_pf0_sriov_cap_sriov_vf_offset_position pf0_sriov_cap_sriov_vf_offset_position; /* offset : 0x244 */
	union pcie_ctrl_pf0_sriov_cap_vf_device_id_reg pf0_sriov_cap_vf_device_id_reg; /* offset : 0x248 */
	union pcie_ctrl_pf0_sriov_cap_sup_page_sizes_reg pf0_sriov_cap_sup_page_sizes_reg; /* offset : 0x24c */
	union pcie_ctrl_pf0_sriov_cap_system_page_size_reg pf0_sriov_cap_system_page_size_reg; /* offset : 0x250 */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar0_reg pf0_sriov_cap_sriov_bar0_reg; /* offset : 0x254 */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar1_reg pf0_sriov_cap_sriov_bar1_reg; /* offset : 0x258 */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar2_reg pf0_sriov_cap_sriov_bar2_reg; /* offset : 0x25c */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar3_reg pf0_sriov_cap_sriov_bar3_reg; /* offset : 0x260 */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar4_reg pf0_sriov_cap_sriov_bar4_reg; /* offset : 0x264 */
	union pcie_ctrl_pf0_sriov_cap_sriov_bar5_reg pf0_sriov_cap_sriov_bar5_reg; /* offset : 0x268 */
	union pcie_ctrl_pf0_sriov_cap_vf_migration_state_array_reg pf0_sriov_cap_vf_migration_state_array_reg; /* offset : 0x26c */
	union pcie_ctrl_pf0_tph_cap_tph_ext_cap_hdr_reg pf0_tph_cap_tph_ext_cap_hdr_reg; /* offset : 0x270 */
	union pcie_ctrl_pf0_tph_cap_tph_req_cap_reg_reg pf0_tph_cap_tph_req_cap_reg_reg; /* offset : 0x274 */
	union pcie_ctrl_pf0_tph_cap_tph_req_control_reg_reg pf0_tph_cap_tph_req_control_reg_reg; /* offset : 0x278 */
	union pcie_ctrl_pf0_ats_cap_ats_cap_hdr_reg pf0_ats_cap_ats_cap_hdr_reg; /* offset : 0x27c */
	union pcie_ctrl_pf0_ats_cap_ats_capabilities_ctrl_reg pf0_ats_cap_ats_capabilities_ctrl_reg; /* offset : 0x280 */
	uint32_t reserved_10[2];
	union pcie_ctrl_pf0_acs_cap_acs_cap_hdr_reg pf0_acs_cap_acs_cap_hdr_reg; /* offset : 0x28c */
	union pcie_ctrl_pf0_acs_cap_acs_capabilities_ctrl_reg pf0_acs_cap_acs_capabilities_ctrl_reg; /* offset : 0x290 */
	union pcie_ctrl_pf0_acs_cap_acs_egress_ctrl_vector_reg0 pf0_acs_cap_acs_egress_ctrl_vector_reg0; /* offset : 0x294 */
	union pcie_ctrl_pf0_prs_ext_cap_prs_ext_cap_hdr_reg pf0_prs_ext_cap_prs_ext_cap_hdr_reg; /* offset : 0x298 */
	union pcie_ctrl_pf0_prs_ext_cap_prs_control_status_reg pf0_prs_ext_cap_prs_control_status_reg; /* offset : 0x29c */
	union pcie_ctrl_pf0_prs_ext_cap_prs_req_capacity_reg pf0_prs_ext_cap_prs_req_capacity_reg; /* offset : 0x2a0 */
	union pcie_ctrl_pf0_prs_ext_cap_prs_req_allocation_reg pf0_prs_ext_cap_prs_req_allocation_reg; /* offset : 0x2a4 */
	union pcie_ctrl_pf0_l1sub_cap_l1sub_cap_header_reg pf0_l1sub_cap_l1sub_cap_header_reg; /* offset : 0x2a8 */
	union pcie_ctrl_pf0_l1sub_cap_l1sub_capability_reg pf0_l1sub_cap_l1sub_capability_reg; /* offset : 0x2ac */
	union pcie_ctrl_pf0_l1sub_cap_l1sub_control1_reg pf0_l1sub_cap_l1sub_control1_reg; /* offset : 0x2b0 */
	union pcie_ctrl_pf0_l1sub_cap_l1sub_control2_reg pf0_l1sub_cap_l1sub_control2_reg; /* offset : 0x2b4 */
	union pcie_ctrl_pf0_pasid_cap_pasid_ext_cap_hdr_reg pf0_pasid_cap_pasid_ext_cap_hdr_reg; /* offset : 0x2b8 */
	union pcie_ctrl_pf0_pasid_cap_pasid_cap_cntrl_reg pf0_pasid_cap_pasid_cap_cntrl_reg; /* offset : 0x2bc */
	union pcie_ctrl_pf0_ras_des_cap_ras_des_cap_header_reg pf0_ras_des_cap_ras_des_cap_header_reg; /* offset : 0x2c0 */
	union pcie_ctrl_pf0_ras_des_cap_vendor_specific_header_reg pf0_ras_des_cap_vendor_specific_header_reg; /* offset : 0x2c4 */
	union pcie_ctrl_pf0_ras_des_cap_event_counter_control_reg pf0_ras_des_cap_event_counter_control_reg; /* offset : 0x2c8 */
	union pcie_ctrl_pf0_ras_des_cap_event_counter_data_reg pf0_ras_des_cap_event_counter_data_reg; /* offset : 0x2cc */
	union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_control_reg pf0_ras_des_cap_time_based_analysis_control_reg; /* offset : 0x2d0 */
	union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_data_reg pf0_ras_des_cap_time_based_analysis_data_reg; /* offset : 0x2d4 */
	union pcie_ctrl_pf0_ras_des_cap_time_based_analysis_data_63_32_reg pf0_ras_des_cap_time_based_analysis_data_63_32_reg; /* offset : 0x2d8 */
	uint32_t reserved_11[5];
	union pcie_ctrl_pf0_ras_des_cap_einj_enable_reg pf0_ras_des_cap_einj_enable_reg; /* offset : 0x2f0 */
	union pcie_ctrl_pf0_ras_des_cap_einj0_crc_reg pf0_ras_des_cap_einj0_crc_reg; /* offset : 0x2f4 */
	union pcie_ctrl_pf0_ras_des_cap_einj1_seqnum_reg pf0_ras_des_cap_einj1_seqnum_reg; /* offset : 0x2f8 */
	union pcie_ctrl_pf0_ras_des_cap_einj2_dllp_reg pf0_ras_des_cap_einj2_dllp_reg; /* offset : 0x2fc */
	union pcie_ctrl_pf0_ras_des_cap_einj3_symbol_reg pf0_ras_des_cap_einj3_symbol_reg; /* offset : 0x300 */
	union pcie_ctrl_pf0_ras_des_cap_einj4_fc_reg pf0_ras_des_cap_einj4_fc_reg; /* offset : 0x304 */
	union pcie_ctrl_pf0_ras_des_cap_einj5_sp_tlp_reg pf0_ras_des_cap_einj5_sp_tlp_reg; /* offset : 0x308 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h0_reg pf0_ras_des_cap_einj6_compare_point_h0_reg; /* offset : 0x30c */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h1_reg pf0_ras_des_cap_einj6_compare_point_h1_reg; /* offset : 0x310 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h2_reg pf0_ras_des_cap_einj6_compare_point_h2_reg; /* offset : 0x314 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_point_h3_reg pf0_ras_des_cap_einj6_compare_point_h3_reg; /* offset : 0x318 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h0_reg pf0_ras_des_cap_einj6_compare_value_h0_reg; /* offset : 0x31c */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h1_reg pf0_ras_des_cap_einj6_compare_value_h1_reg; /* offset : 0x320 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h2_reg pf0_ras_des_cap_einj6_compare_value_h2_reg; /* offset : 0x324 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_compare_value_h3_reg pf0_ras_des_cap_einj6_compare_value_h3_reg; /* offset : 0x328 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h0_reg pf0_ras_des_cap_einj6_change_point_h0_reg; /* offset : 0x32c */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h1_reg pf0_ras_des_cap_einj6_change_point_h1_reg; /* offset : 0x330 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h2_reg pf0_ras_des_cap_einj6_change_point_h2_reg; /* offset : 0x334 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_point_h3_reg pf0_ras_des_cap_einj6_change_point_h3_reg; /* offset : 0x338 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h0_reg pf0_ras_des_cap_einj6_change_value_h0_reg; /* offset : 0x33c */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h1_reg pf0_ras_des_cap_einj6_change_value_h1_reg; /* offset : 0x340 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h2_reg pf0_ras_des_cap_einj6_change_value_h2_reg; /* offset : 0x344 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_change_value_h3_reg pf0_ras_des_cap_einj6_change_value_h3_reg; /* offset : 0x348 */
	union pcie_ctrl_pf0_ras_des_cap_einj6_tlp_reg pf0_ras_des_cap_einj6_tlp_reg; /* offset : 0x34c */
	uint32_t reserved_12[4];
	union pcie_ctrl_pf0_ras_des_cap_sd_control1_reg pf0_ras_des_cap_sd_control1_reg; /* offset : 0x360 */
	union pcie_ctrl_pf0_ras_des_cap_sd_control2_reg pf0_ras_des_cap_sd_control2_reg; /* offset : 0x364 */
	uint32_t reserved_13[2];
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l1lane_reg pf0_ras_des_cap_sd_status_l1lane_reg; /* offset : 0x370 */
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l1ltssm_reg pf0_ras_des_cap_sd_status_l1ltssm_reg; /* offset : 0x374 */
	union pcie_ctrl_pf0_ras_des_cap_sd_status_pm_reg pf0_ras_des_cap_sd_status_pm_reg; /* offset : 0x378 */
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l2_reg pf0_ras_des_cap_sd_status_l2_reg; /* offset : 0x37c */
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l3fc_reg pf0_ras_des_cap_sd_status_l3fc_reg; /* offset : 0x380 */
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l3_reg pf0_ras_des_cap_sd_status_l3_reg; /* offset : 0x384 */
	uint32_t reserved_14[2];
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_control1_reg pf0_ras_des_cap_sd_eq_control1_reg; /* offset : 0x390 */
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_control2_reg pf0_ras_des_cap_sd_eq_control2_reg; /* offset : 0x394 */
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_control3_reg pf0_ras_des_cap_sd_eq_control3_reg; /* offset : 0x398 */
	uint32_t reserved_15;
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status1_reg pf0_ras_des_cap_sd_eq_status1_reg; /* offset : 0x3a0 */
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status2_reg pf0_ras_des_cap_sd_eq_status2_reg; /* offset : 0x3a4 */
	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status3_reg pf0_ras_des_cap_sd_eq_status3_reg; /* offset : 0x3a8 */
	uint32_t reserved_16[5];
	union pcie_ctrl_pf0_vsecras_cap_rasdp_ext_cap_hdr_off pf0_vsecras_cap_rasdp_ext_cap_hdr_off; /* offset : 0x3c0 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_vendor_specific_hdr_off pf0_vsecras_cap_rasdp_vendor_specific_hdr_off; /* offset : 0x3c4 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_error_prot_ctrl_off pf0_vsecras_cap_rasdp_error_prot_ctrl_off; /* offset : 0x3c8 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_counter_ctrl_off pf0_vsecras_cap_rasdp_corr_counter_ctrl_off; /* offset : 0x3cc */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_count_report_off pf0_vsecras_cap_rasdp_corr_count_report_off; /* offset : 0x3d0 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off pf0_vsecras_cap_rasdp_uncorr_counter_ctrl_off; /* offset : 0x3d4 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_count_report_off pf0_vsecras_cap_rasdp_uncorr_count_report_off; /* offset : 0x3d8 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_error_inj_ctrl_off pf0_vsecras_cap_rasdp_error_inj_ctrl_off; /* offset : 0x3dc */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_corr_error_location_off pf0_vsecras_cap_rasdp_corr_error_location_off; /* offset : 0x3e0 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_uncorr_error_location_off pf0_vsecras_cap_rasdp_uncorr_error_location_off; /* offset : 0x3e4 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_error_mode_en_off pf0_vsecras_cap_rasdp_error_mode_en_off; /* offset : 0x3e8 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_error_mode_clear_off pf0_vsecras_cap_rasdp_error_mode_clear_off; /* offset : 0x3ec */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_ram_addr_corr_error_off pf0_vsecras_cap_rasdp_ram_addr_corr_error_off; /* offset : 0x3f0 */
	union pcie_ctrl_pf0_vsecras_cap_rasdp_ram_addr_uncorr_error_off pf0_vsecras_cap_rasdp_ram_addr_uncorr_error_off; /* offset : 0x3f4 */
	union pcie_ctrl_pf0_dlink_cap_data_link_feature_ext_hdr_off pf0_dlink_cap_data_link_feature_ext_hdr_off; /* offset : 0x3f8 */
	union pcie_ctrl_pf0_dlink_cap_data_link_feature_cap_off pf0_dlink_cap_data_link_feature_cap_off; /* offset : 0x3fc */
	union pcie_ctrl_pf0_dlink_cap_data_link_feature_status_off pf0_dlink_cap_data_link_feature_status_off; /* offset : 0x400 */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_ext_cap_hdr_off pf0_vsecdma_cap_vsecdma_ext_cap_hdr_off; /* offset : 0x404 */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_vendor_specific_hdr_off pf0_vsecdma_cap_vsecdma_vendor_specific_hdr_off; /* offset : 0x408 */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_device_information_off pf0_vsecdma_cap_vsecdma_device_information_off; /* offset : 0x40c */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_num_chan_off pf0_vsecdma_cap_vsecdma_num_chan_off; /* offset : 0x410 */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_unroll_addr_offset_low_off pf0_vsecdma_cap_vsecdma_unroll_addr_offset_low_off; /* offset : 0x414 */
	union pcie_ctrl_pf0_vsecdma_cap_vsecdma_unroll_addr_offset_high_off pf0_vsecdma_cap_vsecdma_unroll_addr_offset_high_off; /* offset : 0x418 */
	union pcie_ctrl_pf0_dev3_ext_cap_dev3_ext_cap_hdr_reg pf0_dev3_ext_cap_dev3_ext_cap_hdr_reg; /* offset : 0x41c */
	union pcie_ctrl_pf0_dev3_ext_cap_device_capabilities3_reg pf0_dev3_ext_cap_device_capabilities3_reg; /* offset : 0x420 */
	union pcie_ctrl_pf0_dev3_ext_cap_device_control3_reg pf0_dev3_ext_cap_device_control3_reg; /* offset : 0x424 */
	union pcie_ctrl_pf0_dev3_ext_cap_device_status3_reg pf0_dev3_ext_cap_device_status3_reg; /* offset : 0x428 */
	union pcie_ctrl_wire_ide_ext_cap_hdr wire_ide_ext_cap_hdr; /* offset : 0x42c */
	union pcie_ctrl_wire_ide_cap wire_ide_cap; /* offset : 0x430 */
	union pcie_ctrl_wire_ide_ctrl wire_ide_ctrl; /* offset : 0x434 */
	union pcie_ctrl_wire_ide_link_stream_ctrl_0 wire_ide_link_stream_ctrl_0; /* offset : 0x438 */
	union pcie_ctrl_wire_ide_link_status_0 wire_ide_link_status_0; /* offset : 0x43c */
	union pcie_ctrl_wire_ide_slct_ide_stream_cap_0 wire_ide_slct_ide_stream_cap_0; /* offset : 0x440 */
	union pcie_ctrl_wire_ide_slct_ide_stream_ctrl_0 wire_ide_slct_ide_stream_ctrl_0; /* offset : 0x444 */
	union pcie_ctrl_wire_ide_slct_ide_stream_status_0 wire_ide_slct_ide_stream_status_0; /* offset : 0x448 */
	union pcie_ctrl_wire_ide_rid_assos_reg1_0 wire_ide_rid_assos_reg1_0; /* offset : 0x44c */
	union pcie_ctrl_wire_ide_rid_assos_reg2_0 wire_ide_rid_assos_reg2_0; /* offset : 0x450 */
	union pcie_ctrl_wire_ide_addr_assos_reg1_0_0 wire_ide_addr_assos_reg1_0_0; /* offset : 0x454 */
	union pcie_ctrl_wire_ide_addr_assos_reg2_0_0 wire_ide_addr_assos_reg2_0_0; /* offset : 0x458 */
	union pcie_ctrl_wire_ide_addr_assos_reg3_0_0 wire_ide_addr_assos_reg3_0_0; /* offset : 0x45c */
	union pcie_ctrl_wire_ide_addr_assos_reg1_0_1 wire_ide_addr_assos_reg1_0_1; /* offset : 0x460 */
	union pcie_ctrl_wire_ide_addr_assos_reg2_0_1 wire_ide_addr_assos_reg2_0_1; /* offset : 0x464 */
	union pcie_ctrl_wire_ide_addr_assos_reg3_0_1 wire_ide_addr_assos_reg3_0_1; /* offset : 0x468 */
	union pcie_ctrl_wire_ide_addr_assos_reg1_0_2 wire_ide_addr_assos_reg1_0_2; /* offset : 0x46c */
	union pcie_ctrl_wire_ide_addr_assos_reg2_0_2 wire_ide_addr_assos_reg2_0_2; /* offset : 0x470 */
	union pcie_ctrl_wire_ide_addr_assos_reg3_0_2 wire_ide_addr_assos_reg3_0_2; /* offset : 0x474 */
	union pcie_ctrl_pf0_resbar_cap_resbar_cap_hdr_reg pf0_resbar_cap_resbar_cap_hdr_reg; /* offset : 0x478 */
	union pcie_ctrl_pf0_resbar_cap_resbar_cap_reg_0_reg pf0_resbar_cap_resbar_cap_reg_0_reg; /* offset : 0x47c */
	union pcie_ctrl_pf0_resbar_cap_resbar_ctrl_reg_0_reg pf0_resbar_cap_resbar_ctrl_reg_0_reg; /* offset : 0x480 */
	uint32_t reserved_17[13];
	union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_cap_hdr_reg pf0_vf_resbar_cap_vf_resbar_cap_hdr_reg; /* offset : 0x4b8 */
	union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_cap_reg_0_reg pf0_vf_resbar_cap_vf_resbar_cap_reg_0_reg; /* offset : 0x4bc */
	union pcie_ctrl_pf0_vf_resbar_cap_vf_resbar_ctrl_reg_0_reg pf0_vf_resbar_cap_vf_resbar_ctrl_reg_0_reg; /* offset : 0x4c0 */
};

struct pcie_ctrl_dbi2_register {
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar0_mask_reg pf0_type0_hdr_dbi2_bar0_mask_reg; /* offset : 0x80000010 */
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar1_mask_reg pf0_type0_hdr_dbi2_bar1_mask_reg; /* offset : 0x80000014 */
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar2_mask_reg pf0_type0_hdr_dbi2_bar2_mask_reg; /* offset : 0x80000018 */
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar3_mask_reg pf0_type0_hdr_dbi2_bar3_mask_reg; /* offset : 0x8000001c */
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar4_mask_reg pf0_type0_hdr_dbi2_bar4_mask_reg; /* offset : 0x80000020 */
	union pcie_ctrl_pf0_type0_hdr_dbi2_bar5_mask_reg pf0_type0_hdr_dbi2_bar5_mask_reg; /* offset : 0x80000024 */
	uint32_t reserved_1[2];
	union pcie_ctrl_pf0_type0_hdr_dbi2_exp_rom_bar_mask_reg pf0_type0_hdr_dbi2_exp_rom_bar_mask_reg; /* offset : 0x80000030 */
	uint32_t reserved_2[18];
	union pcie_ctrl_pf0_pcie_cap_dbi2_shadow_link_capabilities_reg pf0_pcie_cap_dbi2_shadow_link_capabilities_reg; /* offset : 0x8000007c */
	uint32_t reserved_3[12];
	union pcie_ctrl_pf0_msix_cap_dbi2_shadow_pci_msix_cap_id_next_ctrl_reg pf0_msix_cap_dbi2_shadow_pci_msix_cap_id_next_ctrl_reg; /* offset : 0x800000b0 */
	union pcie_ctrl_pf0_msix_cap_dbi2_shadow_msix_table_offset_reg pf0_msix_cap_dbi2_shadow_msix_table_offset_reg; /* offset : 0x800000b4 */
	union pcie_ctrl_pf0_msix_cap_dbi2_shadow_msix_pba_offset_reg pf0_msix_cap_dbi2_shadow_msix_pba_offset_reg; /* offset : 0x800000b8 */
	uint32_t reserved_4[98];
	union pcie_ctrl_pf0_sriov_cap_dbi2_shadow_sriov_vf_offset_position pf0_sriov_cap_dbi2_shadow_sriov_vf_offset_position; /* offset : 0x80000244 */
	uint32_t reserved_5[5];
	union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar2_mask_reg pf0_sriov_cap_dbi2_sriov_bar2_mask_reg; /* offset : 0x8000025c */
	union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar3_mask_reg pf0_sriov_cap_dbi2_sriov_bar3_mask_reg; /* offset : 0x80000260 */
	union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar4_mask_reg pf0_sriov_cap_dbi2_sriov_bar4_mask_reg; /* offset : 0x80000264 */
	union pcie_ctrl_pf0_sriov_cap_dbi2_sriov_bar5_mask_reg pf0_sriov_cap_dbi2_sriov_bar5_mask_reg; /* offset : 0x80000268 */
	uint32_t reserved_6[2];
	union pcie_ctrl_pf0_tph_cap_dbi2_shadow_tph_req_cap_reg_reg pf0_tph_cap_dbi2_shadow_tph_req_cap_reg_reg; /* offset : 0x80000274 */
};

struct pcie_ctrl_port_register {
	union pcie_ctrl_pf0_port_logic_ack_latency_timer_off pf0_port_logic_ack_latency_timer_off; /* offset : 0x180b00000 */
	union pcie_ctrl_pf0_port_logic_vendor_spec_dllp_off pf0_port_logic_vendor_spec_dllp_off; /* offset : 0x180b00004 */
	union pcie_ctrl_pf0_port_logic_port_force_off pf0_port_logic_port_force_off; /* offset : 0x180b00008 */
	union pcie_ctrl_pf0_port_logic_ack_f_aspm_ctrl_off pf0_port_logic_ack_f_aspm_ctrl_off; /* offset : 0x180b0000c */
	union pcie_ctrl_pf0_port_logic_port_link_ctrl_off pf0_port_logic_port_link_ctrl_off; /* offset : 0x180b00010 */
	union pcie_ctrl_pf0_port_logic_lane_skew_off pf0_port_logic_lane_skew_off; /* offset : 0x180b00014 */
	union pcie_ctrl_pf0_port_logic_timer_ctrl_max_func_num_off pf0_port_logic_timer_ctrl_max_func_num_off; /* offset : 0x180b00018 */
	union pcie_ctrl_pf0_port_logic_symbol_timer_filter_1_off pf0_port_logic_symbol_timer_filter_1_off; /* offset : 0x180b0001c */
	union pcie_ctrl_pf0_port_logic_filter_mask_2_off pf0_port_logic_filter_mask_2_off; /* offset : 0x180b00020 */
	uint32_t reserved_1;
	union pcie_ctrl_pf0_port_logic_pl_debug0_off pf0_port_logic_pl_debug0_off; /* offset : 0x180b00028 */
	union pcie_ctrl_pf0_port_logic_pl_debug1_off pf0_port_logic_pl_debug1_off; /* offset : 0x180b0002c */
	union pcie_ctrl_pf0_port_logic_tx_p_fc_credit_status_off pf0_port_logic_tx_p_fc_credit_status_off; /* offset : 0x180b00030 */
	union pcie_ctrl_pf0_port_logic_tx_np_fc_credit_status_off pf0_port_logic_tx_np_fc_credit_status_off; /* offset : 0x180b00034 */
	union pcie_ctrl_pf0_port_logic_tx_cpl_fc_credit_status_off pf0_port_logic_tx_cpl_fc_credit_status_off; /* offset : 0x180b00038 */
	union pcie_ctrl_pf0_port_logic_queue_status_off pf0_port_logic_queue_status_off; /* offset : 0x180b0003c */
	union pcie_ctrl_pf0_port_logic_vc_tx_arbi_1_off pf0_port_logic_vc_tx_arbi_1_off; /* offset : 0x180b00040 */
	union pcie_ctrl_pf0_port_logic_vc_tx_arbi_2_off pf0_port_logic_vc_tx_arbi_2_off; /* offset : 0x180b00044 */
	union pcie_ctrl_pf0_port_logic_vc0_p_rx_q_ctrl_off pf0_port_logic_vc0_p_rx_q_ctrl_off; /* offset : 0x180b00048 */
	union pcie_ctrl_pf0_port_logic_vc0_np_rx_q_ctrl_off pf0_port_logic_vc0_np_rx_q_ctrl_off; /* offset : 0x180b0004c */
	union pcie_ctrl_pf0_port_logic_vc0_cpl_rx_q_ctrl_off pf0_port_logic_vc0_cpl_rx_q_ctrl_off; /* offset : 0x180b00050 */
	uint32_t reserved_2[46];
	union pcie_ctrl_pf0_port_logic_gen2_ctrl_off pf0_port_logic_gen2_ctrl_off; /* offset : 0x180b0010c */
	union pcie_ctrl_pf0_port_logic_phy_status_off pf0_port_logic_phy_status_off; /* offset : 0x180b00110 */
	union pcie_ctrl_pf0_port_logic_phy_control_off pf0_port_logic_phy_control_off; /* offset : 0x180b00114 */
	uint32_t reserved_3;
	union pcie_ctrl_pf0_port_logic_trgt_map_ctrl_off pf0_port_logic_trgt_map_ctrl_off; /* offset : 0x180b0011c */
	uint32_t reserved_4[27];
	union pcie_ctrl_pf0_port_logic_clock_gating_ctrl_off pf0_port_logic_clock_gating_ctrl_off; /* offset : 0x180b0018c */
	union pcie_ctrl_pf0_port_logic_gen3_related_off pf0_port_logic_gen3_related_off; /* offset : 0x180b00190 */
	union pcie_ctrl_pf0_port_logic_gen3_eq_local_fs_lf_off pf0_port_logic_gen3_eq_local_fs_lf_off; /* offset : 0x180b00194 */
	union pcie_ctrl_pf0_port_logic_gen3_eq_pset_coef_map__0 pf0_port_logic_gen3_eq_pset_coef_map__0; /* offset : 0x180b00198 */
	union pcie_ctrl_pf0_port_logic_gen3_eq_pset_index_off pf0_port_logic_gen3_eq_pset_index_off; /* offset : 0x180b0019c */
	uint32_t reserved_5;
	union pcie_ctrl_pf0_port_logic_gen3_eq_coeff_legality_status_off pf0_port_logic_gen3_eq_coeff_legality_status_off; /* offset : 0x180b001a4 */
	union pcie_ctrl_pf0_port_logic_gen3_eq_control_off pf0_port_logic_gen3_eq_control_off; /* offset : 0x180b001a8 */
	union pcie_ctrl_pf0_port_logic_gen3_eq_fb_mode_dir_change_off pf0_port_logic_gen3_eq_fb_mode_dir_change_off; /* offset : 0x180b001ac */
	uint32_t reserved_6;
	union pcie_ctrl_pf0_port_logic_order_rule_ctrl_off pf0_port_logic_order_rule_ctrl_off; /* offset : 0x180b001b4 */
	union pcie_ctrl_pf0_port_logic_pipe_loopback_control_off pf0_port_logic_pipe_loopback_control_off; /* offset : 0x180b001b8 */
	union pcie_ctrl_pf0_port_logic_misc_control_1_off pf0_port_logic_misc_control_1_off; /* offset : 0x180b001bc */
	union pcie_ctrl_pf0_port_logic_multi_lane_control_off pf0_port_logic_multi_lane_control_off; /* offset : 0x180b001c0 */
	union pcie_ctrl_pf0_port_logic_phy_interop_ctrl_off pf0_port_logic_phy_interop_ctrl_off; /* offset : 0x180b001c4 */
	union pcie_ctrl_pf0_port_logic_trgt_cpl_lut_delete_entry_off pf0_port_logic_trgt_cpl_lut_delete_entry_off; /* offset : 0x180b001c8 */
	union pcie_ctrl_pf0_port_logic_link_flush_control_off pf0_port_logic_link_flush_control_off; /* offset : 0x180b001cc */
	union pcie_ctrl_pf0_port_logic_amba_error_response_default_off pf0_port_logic_amba_error_response_default_off; /* offset : 0x180b001d0 */
	union pcie_ctrl_pf0_port_logic_amba_link_timeout_off pf0_port_logic_amba_link_timeout_off; /* offset : 0x180b001d4 */
	union pcie_ctrl_pf0_port_logic_amba_ordering_ctrl_off pf0_port_logic_amba_ordering_ctrl_off; /* offset : 0x180b001d8 */
	uint32_t reserved_7;
	union pcie_ctrl_pf0_port_logic_coherency_control_1_off pf0_port_logic_coherency_control_1_off; /* offset : 0x180b001e0 */
	union pcie_ctrl_pf0_port_logic_coherency_control_2_off pf0_port_logic_coherency_control_2_off; /* offset : 0x180b001e4 */
	union pcie_ctrl_pf0_port_logic_coherency_control_3_off pf0_port_logic_coherency_control_3_off; /* offset : 0x180b001e8 */
	uint32_t reserved_8;
	union pcie_ctrl_pf0_port_logic_axi_mstr_msg_addr_low_off pf0_port_logic_axi_mstr_msg_addr_low_off; /* offset : 0x180b001f0 */
	union pcie_ctrl_pf0_port_logic_axi_mstr_msg_addr_high_off pf0_port_logic_axi_mstr_msg_addr_high_off; /* offset : 0x180b001f4 */
	union pcie_ctrl_pf0_port_logic_pcie_version_number_off pf0_port_logic_pcie_version_number_off; /* offset : 0x180b001f8 */
	union pcie_ctrl_pf0_port_logic_pcie_version_type_off pf0_port_logic_pcie_version_type_off; /* offset : 0x180b001fc */
	uint32_t reserved_9[16];
	union pcie_ctrl_pf0_port_logic_msix_address_match_low_off pf0_port_logic_msix_address_match_low_off; /* offset : 0x180b00240 */
	union pcie_ctrl_pf0_port_logic_msix_address_match_high_off pf0_port_logic_msix_address_match_high_off; /* offset : 0x180b00244 */
	union pcie_ctrl_pf0_port_logic_msix_doorbell_off pf0_port_logic_msix_doorbell_off; /* offset : 0x180b00248 */
	union pcie_ctrl_pf0_port_logic_msix_ram_ctrl_off pf0_port_logic_msix_ram_ctrl_off; /* offset : 0x180b0024c */
	uint32_t reserved_10[115];
	union pcie_ctrl_pf0_port_logic_pcipm_traffic_ctrl_off pf0_port_logic_pcipm_traffic_ctrl_off; /* offset : 0x180b0041c */
	uint32_t reserved_11[8];
	union pcie_ctrl_pf0_port_logic_aux_clk_freq_off pf0_port_logic_aux_clk_freq_off; /* offset : 0x180b00440 */
	union pcie_ctrl_pf0_port_logic_l1_substates_off pf0_port_logic_l1_substates_off; /* offset : 0x180b00444 */
	union pcie_ctrl_pf0_port_logic_powerdown_ctrl_status_off pf0_port_logic_powerdown_ctrl_status_off; /* offset : 0x180b00448 */
	union pcie_ctrl_pf0_port_logic_phy_interop_ctrl_2_off pf0_port_logic_phy_interop_ctrl_2_off; /* offset : 0x180b0044c */
	uint32_t reserved_12[12];
	union pcie_ctrl_pf0_port_logic_gen4_lane_margining_1_off pf0_port_logic_gen4_lane_margining_1_off; /* offset : 0x180b00480 */
	union pcie_ctrl_pf0_port_logic_gen4_lane_margining_2_off pf0_port_logic_gen4_lane_margining_2_off; /* offset : 0x180b00484 */
	union pcie_ctrl_pf0_port_logic_gen5_lane_margining_1_off pf0_port_logic_gen5_lane_margining_1_off; /* offset : 0x180b00488 */
	union pcie_ctrl_pf0_port_logic_gen5_lane_margining_2_off pf0_port_logic_gen5_lane_margining_2_off; /* offset : 0x180b0048c */
	union pcie_ctrl_pf0_port_logic_pipe_related_off pf0_port_logic_pipe_related_off; /* offset : 0x180b00490 */
	uint32_t reserved_13[27];
	union pcie_ctrl_pf0_port_logic_rx_serialization_q_ctrl_off pf0_port_logic_rx_serialization_q_ctrl_off; /* offset : 0x180b00500 */
	uint32_t reserved_14[30];
	union pcie_ctrl_pf0_port_logic_dbi_function_bank_ctrl_reg_off pf0_port_logic_dbi_function_bank_ctrl_reg_off; /* offset : 0x180b0057c */
	union pcie_ctrl_pf0_port_logic_utility_off pf0_port_logic_utility_off; /* offset : 0x180b00580 */
	uint32_t reserved_15;
	union pcie_ctrl_pf0_port_logic_pm_utility_off pf0_port_logic_pm_utility_off; /* offset : 0x180b00588 */
	union pcie_ctrl_pf0_port_logic_ide_ctrl_off pf0_port_logic_ide_ctrl_off; /* offset : 0x180b0058c */
	uint32_t reserved_16[7];
	union pcie_ctrl_pf0_port_logic_prbs_loopback_test_reg_off pf0_port_logic_prbs_loopback_test_reg_off; /* offset : 0x180b005ac */
};

/* offset: 0x200000, 0x600000, 0xa00000 .... 0x3e00000 */
struct pcie_ctrl_vf_pf0_register {
	union pcie_ctrl_vf_pf0_type0_hdr_vf_device_id_vendor_id_reg
		vf_pf0_type0_hdr_vf_device_id_vendor_id_reg; /* offset : 0x200000 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_status_command_reg
		vf_pf0_type0_hdr_vf_status_command_reg; /* offset : 0x200004 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_class_code_revision_id
		vf_pf0_type0_hdr_vf_class_code_revision_id; /* offset : 0x200008 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bist_header_type_latency_cache_line_size_reg
		vf_pf0_type0_hdr_vf_bist_header_type_latency_cache_line_size_reg; /* offset : 0x20000c */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar0_reg vf_pf0_type0_hdr_vf_bar0_reg; /* offset:0x200010 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar1_reg vf_pf0_type0_hdr_vf_bar1_reg; /* offset:0x200014 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar2_reg vf_pf0_type0_hdr_vf_bar2_reg; /* offset:0x200018 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar3_reg vf_pf0_type0_hdr_vf_bar3_reg; /* offset:0x20001c */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar4_reg vf_pf0_type0_hdr_vf_bar4_reg; /* offset:0x200020 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_bar5_reg vf_pf0_type0_hdr_vf_bar5_reg; /* offset:0x200024 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_cardbus_cis_ptr_reg
		vf_pf0_type0_hdr_vf_cardbus_cis_ptr_reg; /* offset : 0x200028 */
	union pcie_ctrl_vf_pf0_type0_hdr_vf_subsystem_id_subsystem_vendor_id_reg
		vf_pf0_type0_hdr_vf_subsystem_id_subsystem_vendor_id_reg; /* offset : 0x20002c */
	uint32_t reserved_1;
	union pcie_ctrl_vf_pf0_type0_hdr_vf_pci_cap_ptr_reg
		vf_pf0_type0_hdr_vf_pci_cap_ptr_reg; /* offset : 0x200034 */
	uint32_t reserved_2;
	union pcie_ctrl_vf_pf0_type0_hdr_vf_max_latency_min_grant_interrupt_pin_interrupt_line_reg
		vf_pf0_type0_hdr_vf_max_latency_min_grant_interrupt_pin_interrupt_line_reg;
															/* offset : 0x20003c */
	uint32_t reserved_3[12];
	union pcie_ctrl_vf_pf0_pcie_cap_vf_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg
		vf_pf0_pcie_cap_vf_pcie_cap_id_pcie_next_cap_ptr_pcie_cap_reg; /* offset : 0x200070 */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_device_capabilities_reg
		vf_pf0_pcie_cap_vf_device_capabilities_reg; /* offset : 0x200074 */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_device_control_device_status
		vf_pf0_pcie_cap_vf_device_control_device_status; /* offset : 0x200078 */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_link_capabilities_reg
		vf_pf0_pcie_cap_vf_link_capabilities_reg; /* offset : 0x20007c */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_link_control_link_status_reg
		vf_pf0_pcie_cap_vf_link_control_link_status_reg; /* offset : 0x200080 */
	uint32_t reserved_4[4];
	union pcie_ctrl_vf_pf0_pcie_cap_vf_device_capabilities2_reg
		vf_pf0_pcie_cap_vf_device_capabilities2_reg; /* offset : 0x200094 */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_device_control2_device_status2_reg
		vf_pf0_pcie_cap_vf_device_control2_device_status2_reg; /* offset : 0x200098 */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_link_capabilities2_reg
		vf_pf0_pcie_cap_vf_link_capabilities2_reg; /* offset : 0x20009c */
	union pcie_ctrl_vf_pf0_pcie_cap_vf_link_control2_link_status2_reg
		vf_pf0_pcie_cap_vf_link_control2_link_status2_reg; /* offset : 0x2000a0 */
	uint32_t reserved_5[3];
	union pcie_ctrl_vf_pf0_msix_cap_vf_pci_msix_cap_id_next_ctrl_reg
		vf_pf0_msix_cap_vf_pci_msix_cap_id_next_ctrl_reg; /* offset : 0x2000b0 */
	union pcie_ctrl_vf_pf0_msix_cap_vf_msix_table_offset_reg
		vf_pf0_msix_cap_vf_msix_table_offset_reg; /* offset : 0x2000b4 */
	union pcie_ctrl_vf_pf0_msix_cap_vf_msix_pba_offset_reg
		vf_pf0_msix_cap_vf_msix_pba_offset_reg; /* offset : 0x2000b8 */
	uint32_t reserved_6[17];
	union pcie_ctrl_vf_pf0_aer_cap_vf_aer_ext_cap_hdr_off vf_pf0_aer_cap_vf_aer_ext_cap_hdr_off;
																		/* offset : 0x200100 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_status_off vf_pf0_aer_cap_vf_uncorr_err_status_off;
																			/* offset : 0x200104 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_mask_off vf_pf0_aer_cap_vf_uncorr_err_mask_off;
																			/* offset : 0x200108 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_uncorr_err_sev_off vf_pf0_aer_cap_vf_uncorr_err_sev_off;
																	/* offset : 0x20010c */
	union pcie_ctrl_vf_pf0_aer_cap_vf_corr_err_status_off vf_pf0_aer_cap_vf_corr_err_status_off;
																		/* offset : 0x200110 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_corr_err_mask_off vf_pf0_aer_cap_vf_corr_err_mask_off;
																	/* offset : 0x200114 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_adv_err_cap_ctrl_off vf_pf0_aer_cap_vf_adv_err_cap_ctrl_off;
																			/* offset : 0x200118 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_0_off vf_pf0_aer_cap_vf_hdr_log_0_off;
															/* offset : 0x20011c */
	union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_1_off vf_pf0_aer_cap_vf_hdr_log_1_off;
															/* offset : 0x200120 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_2_off vf_pf0_aer_cap_vf_hdr_log_2_off;
															/* offset : 0x200124 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_hdr_log_3_off vf_pf0_aer_cap_vf_hdr_log_3_off;
															/* offset : 0x200128 */
	uint32_t reserved_7[3];
	union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_1_off vf_pf0_aer_cap_vf_tlp_prefix_log_1_off;
																		/* offset : 0x200138 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_2_off vf_pf0_aer_cap_vf_tlp_prefix_log_2_off;
																		/* offset : 0x20013c */
	union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_3_off vf_pf0_aer_cap_vf_tlp_prefix_log_3_off;
																		/* offset : 0x200140 */
	union pcie_ctrl_vf_pf0_aer_cap_vf_tlp_prefix_log_4_off vf_pf0_aer_cap_vf_tlp_prefix_log_4_off;
																		/* offset : 0x200144 */
	union pcie_ctrl_vf_pf0_ari_cap_vf_ari_base vf_pf0_ari_cap_vf_ari_base; /* offset : 0x200148 */
	union pcie_ctrl_vf_pf0_ari_cap_vf_cap_reg vf_pf0_ari_cap_vf_cap_reg; /* offset : 0x20014c */
	uint32_t reserved_8[2];
	union pcie_ctrl_vf_pf0_tph_cap_vf_tph_ext_cap_hdr_reg vf_pf0_tph_cap_vf_tph_ext_cap_hdr_reg;
																		/* offset : 0x200158 */
	union pcie_ctrl_vf_pf0_tph_cap_vf_tph_req_cap_reg_reg vf_pf0_tph_cap_vf_tph_req_cap_reg_reg;
																		/* offset : 0x20015c */
	union pcie_ctrl_vf_pf0_tph_cap_vf_tph_req_control_reg_reg
		vf_pf0_tph_cap_vf_tph_req_control_reg_reg; /* offset : 0x200160 */
	union pcie_ctrl_vf_pf0_ats_cap_vf_ats_cap_hdr_reg vf_pf0_ats_cap_vf_ats_cap_hdr_reg;
																/* offset : 0x200164 */
	union pcie_ctrl_vf_pf0_ats_cap_vf_ats_capabilities_ctrl_reg
		vf_pf0_ats_cap_vf_ats_capabilities_ctrl_reg; /* offset : 0x200168 */
	uint32_t reserved_9[2];
	union pcie_ctrl_vf_pf0_acs_cap_vf_acs_cap_hdr_reg vf_pf0_acs_cap_vf_acs_cap_hdr_reg;
																/* offset : 0x200174 */
	union pcie_ctrl_vf_pf0_acs_cap_vf_acs_capabilities_ctrl_reg
		vf_pf0_acs_cap_vf_acs_capabilities_ctrl_reg; /* offset : 0x200178 */
	union pcie_ctrl_vf_pf0_acs_cap_vf_acs_egress_ctrl_vector_reg0
		vf_pf0_acs_cap_vf_acs_egress_ctrl_vector_reg0; /* offset : 0x20017c */
	uint32_t reserved_10[1048480];
};

/* offset: 0x180300000, 0x180300200, ..., 0x180307e00 */
struct pcie_ctrl_pf0_atu_cap_iatu_register {
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_1_off_outbound pf0_atu_cap_iatu_region_ctrl_1_off_outbound; /* offset : 0x180300000 */
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_2_off_outbound pf0_atu_cap_iatu_region_ctrl_2_off_outbound; /* offset : 0x180300004 */
	union pcie_ctrl_pf0_atu_cap_iatu_lwr_base_addr_off_outbound pf0_atu_cap_iatu_lwr_base_addr_off_outbound; /* offset : 0x180300008 */
	union pcie_ctrl_pf0_atu_cap_iatu_upper_base_addr_off_outbound pf0_atu_cap_iatu_upper_base_addr_off_outbound; /* offset : 0x18030000c */
	union pcie_ctrl_pf0_atu_cap_iatu_limit_addr_off_outbound pf0_atu_cap_iatu_limit_addr_off_outbound; /* offset : 0x180300010 */
	union pcie_ctrl_pf0_atu_cap_iatu_lwr_target_addr_off_outbound pf0_atu_cap_iatu_lwr_target_addr_off_outbound; /* offset : 0x180300014 */
	union pcie_ctrl_pf0_atu_cap_iatu_upper_target_addr_off_outbound pf0_atu_cap_iatu_upper_target_addr_off_outbound; /* offset : 0x180300018 */
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_3_off_outbound pf0_atu_cap_iatu_region_ctrl_3_off_outbound; /* offset : 0x18030001c */
	union pcie_ctrl_pf0_atu_cap_iatu_uppr_limit_addr_off_outbound pf0_atu_cap_iatu_uppr_limit_addr_off_outbound; /* offset : 0x180300020 */
	uint32_t reserved_1[55];
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_1_off_inbound pf0_atu_cap_iatu_region_ctrl_1_off_inbound; /* offset : 0x180300100 */
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_2_off_inbound pf0_atu_cap_iatu_region_ctrl_2_off_inbound; /* offset : 0x180300104 */
	union pcie_ctrl_pf0_atu_cap_iatu_lwr_base_addr_off_inbound pf0_atu_cap_iatu_lwr_base_addr_off_inbound; /* offset : 0x180300108 */
	union pcie_ctrl_pf0_atu_cap_iatu_upper_base_addr_off_inbound pf0_atu_cap_iatu_upper_base_addr_off_inbound; /* offset : 0x18030010c */
	union pcie_ctrl_pf0_atu_cap_iatu_limit_addr_off_inbound pf0_atu_cap_iatu_limit_addr_off_inbound; /* offset : 0x180300110 */
	union pcie_ctrl_pf0_atu_cap_iatu_lwr_target_addr_off_inbound pf0_atu_cap_iatu_lwr_target_addr_off_inbound; /* offset : 0x180300114 */
	union pcie_ctrl_pf0_atu_cap_iatu_upper_target_addr_off_inbound pf0_atu_cap_iatu_upper_target_addr_off_inbound; /* offset : 0x180300118 */
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_3_off_inbound pf0_atu_cap_iatu_region_ctrl_3_off_inbound; /* offset : 0x18030011c */
	union pcie_ctrl_pf0_atu_cap_iatu_uppr_limit_addr_off_inbound pf0_atu_cap_iatu_uppr_limit_addr_off_inbound; /* offset : 0x180300120 */
	uint32_t reserved_2[55];
};

/* offset: 0x180380000(0x180380080), 0x180381000(0x180381800), ... 0x18038f000(0x18038f800) */
struct pcie_ctrl_pf0_hdma_cap_hdma_register {
	union pcie_ctrl_pf0_hdma_cap_hdma_en_off_wrch pf0_hdma_cap_hdma_en_off_wrch; /* offset : 0x180380000 */
	union pcie_ctrl_pf0_hdma_cap_hdma_doorbell_off_wrch pf0_hdma_cap_hdma_doorbell_off_wrch; /* offset : 0x180380004 */
	union pcie_ctrl_pf0_hdma_cap_hdma_elem_pf_off_wrch pf0_hdma_cap_hdma_elem_pf_off_wrch; /* offset : 0x180380008 */
	uint32_t reserved_1;
	union pcie_ctrl_pf0_hdma_cap_hdma_llp_low_off_wrch pf0_hdma_cap_hdma_llp_low_off_wrch; /* offset : 0x180380010 */
	union pcie_ctrl_pf0_hdma_cap_hdma_llp_high_off_wrch pf0_hdma_cap_hdma_llp_high_off_wrch; /* offset : 0x180380014 */
	union pcie_ctrl_pf0_hdma_cap_hdma_cycle_off_wrch pf0_hdma_cap_hdma_cycle_off_wrch; /* offset : 0x180380018 */
	union pcie_ctrl_pf0_hdma_cap_hdma_xfersize_off_wrch pf0_hdma_cap_hdma_xfersize_off_wrch; /* offset : 0x18038001c */
	union pcie_ctrl_pf0_hdma_cap_hdma_sar_low_off_wrch pf0_hdma_cap_hdma_sar_low_off_wrch; /* offset : 0x180380020 */
	union pcie_ctrl_pf0_hdma_cap_hdma_sar_high_off_wrch pf0_hdma_cap_hdma_sar_high_off_wrch; /* offset : 0x180380024 */
	union pcie_ctrl_pf0_hdma_cap_hdma_dar_low_off_wrch pf0_hdma_cap_hdma_dar_low_off_wrch; /* offset : 0x180380028 */
	union pcie_ctrl_pf0_hdma_cap_hdma_dar_high_off_wrch pf0_hdma_cap_hdma_dar_high_off_wrch; /* offset : 0x18038002c */
	union pcie_ctrl_pf0_hdma_cap_hdma_watermark_en_off_wrch pf0_hdma_cap_hdma_watermark_en_off_wrch; /* offset : 0x180380030 */
	union pcie_ctrl_pf0_hdma_cap_hdma_control1_off_wrch pf0_hdma_cap_hdma_control1_off_wrch; /* offset : 0x180380034 */
	union pcie_ctrl_pf0_hdma_cap_hdma_func_num_off_wrch pf0_hdma_cap_hdma_func_num_off_wrch; /* offset : 0x180380038 */
	union pcie_ctrl_pf0_hdma_cap_hdma_qos_off_wrch pf0_hdma_cap_hdma_qos_off_wrch; /* offset : 0x18038003c */
	uint32_t reserved_2[16];
	union pcie_ctrl_pf0_hdma_cap_hdma_status_off_wrch pf0_hdma_cap_hdma_status_off_wrch; /* offset : 0x180380080 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_status_off_wrch pf0_hdma_cap_hdma_int_status_off_wrch; /* offset : 0x180380084 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_setup_off_wrch pf0_hdma_cap_hdma_int_setup_off_wrch; /* offset : 0x180380088 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_clear_off_wrch pf0_hdma_cap_hdma_int_clear_off_wrch; /* offset : 0x18038008c */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_low_off_wrch pf0_hdma_cap_hdma_msi_stop_low_off_wrch; /* offset : 0x180380090 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_high_off_wrch pf0_hdma_cap_hdma_msi_stop_high_off_wrch; /* offset : 0x180380094 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_low_off_wrch pf0_hdma_cap_hdma_msi_watermark_low_off_wrch; /* offset : 0x180380098 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_high_off_wrch pf0_hdma_cap_hdma_msi_watermark_high_off_wrch; /* offset : 0x18038009c */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_low_off_wrch pf0_hdma_cap_hdma_msi_abort_low_off_wrch; /* offset : 0x1803800a0 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_high_off_wrch pf0_hdma_cap_hdma_msi_abort_high_off_wrch; /* offset : 0x1803800a4 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_msgd_off_wrch pf0_hdma_cap_hdma_msi_msgd_off_wrch; /* offset : 0x1803800a8 */
	uint32_t reserved_3[469];
	union pcie_ctrl_pf0_hdma_cap_hdma_en_off_rdch pf0_hdma_cap_hdma_en_off_rdch; /* offset : 0x180380800 */
	union pcie_ctrl_pf0_hdma_cap_hdma_doorbell_off_rdch pf0_hdma_cap_hdma_doorbell_off_rdch; /* offset : 0x180380804 */
	union pcie_ctrl_pf0_hdma_cap_hdma_elem_pf_off_rdch pf0_hdma_cap_hdma_elem_pf_off_rdch; /* offset : 0x180380808 */
	uint32_t reserved_4;
	union pcie_ctrl_pf0_hdma_cap_hdma_llp_low_off_rdch pf0_hdma_cap_hdma_llp_low_off_rdch; /* offset : 0x180380810 */
	union pcie_ctrl_pf0_hdma_cap_hdma_llp_high_off_rdch pf0_hdma_cap_hdma_llp_high_off_rdch; /* offset : 0x180380814 */
	union pcie_ctrl_pf0_hdma_cap_hdma_cycle_off_rdch pf0_hdma_cap_hdma_cycle_off_rdch; /* offset : 0x180380818 */
	union pcie_ctrl_pf0_hdma_cap_hdma_xfersize_off_rdch pf0_hdma_cap_hdma_xfersize_off_rdch; /* offset : 0x18038081c */
	union pcie_ctrl_pf0_hdma_cap_hdma_sar_low_off_rdch pf0_hdma_cap_hdma_sar_low_off_rdch; /* offset : 0x180380820 */
	union pcie_ctrl_pf0_hdma_cap_hdma_sar_high_off_rdch pf0_hdma_cap_hdma_sar_high_off_rdch; /* offset : 0x180380824 */
	union pcie_ctrl_pf0_hdma_cap_hdma_dar_low_off_rdch pf0_hdma_cap_hdma_dar_low_off_rdch; /* offset : 0x180380828 */
	union pcie_ctrl_pf0_hdma_cap_hdma_dar_high_off_rdch pf0_hdma_cap_hdma_dar_high_off_rdch; /* offset : 0x18038082c */
	union pcie_ctrl_pf0_hdma_cap_hdma_watermark_en_off_rdch pf0_hdma_cap_hdma_watermark_en_off_rdch; /* offset : 0x180380830 */
	union pcie_ctrl_pf0_hdma_cap_hdma_control1_off_rdch pf0_hdma_cap_hdma_control1_off_rdch; /* offset : 0x180380834 */
	union pcie_ctrl_pf0_hdma_cap_hdma_func_num_off_rdch pf0_hdma_cap_hdma_func_num_off_rdch; /* offset : 0x180380838 */
	union pcie_ctrl_pf0_hdma_cap_hdma_qos_off_rdch pf0_hdma_cap_hdma_qos_off_rdch; /* offset : 0x18038083c */
	uint32_t reserved_5[16];
	union pcie_ctrl_pf0_hdma_cap_hdma_status_off_rdch pf0_hdma_cap_hdma_status_off_rdch; /* offset : 0x180380880 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_status_off_rdch pf0_hdma_cap_hdma_int_status_off_rdch; /* offset : 0x180380884 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_setup_off_rdch pf0_hdma_cap_hdma_int_setup_off_rdch; /* offset : 0x180380888 */
	union pcie_ctrl_pf0_hdma_cap_hdma_int_clear_off_rdch pf0_hdma_cap_hdma_int_clear_off_rdch; /* offset : 0x18038088c */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_low_off_rdch pf0_hdma_cap_hdma_msi_stop_low_off_rdch; /* offset : 0x180380890 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_stop_high_off_rdch pf0_hdma_cap_hdma_msi_stop_high_off_rdch; /* offset : 0x180380894 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_low_off_rdch pf0_hdma_cap_hdma_msi_watermark_low_off_rdch; /* offset : 0x180380898 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_watermark_high_off_rdch pf0_hdma_cap_hdma_msi_watermark_high_off_rdch; /* offset : 0x18038089c */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_low_off_rdch pf0_hdma_cap_hdma_msi_abort_low_off_rdch; /* offset : 0x1803808a0 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_abort_high_off_rdch pf0_hdma_cap_hdma_msi_abort_high_off_rdch; /* offset : 0x1803808a4 */
	union pcie_ctrl_pf0_hdma_cap_hdma_msi_msgd_off_rdch pf0_hdma_cap_hdma_msi_msgd_off_rdch; /* offset : 0x1803808a8 */
	uint32_t reserved_6[469];
};
