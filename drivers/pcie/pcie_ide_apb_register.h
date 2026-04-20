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

union pcie_ide_apb_ide_core_ver_num {
	struct {
		uint32_t version_num:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_core_ver_type {
	struct {
		uint32_t type_num:8; /* [7:0] */
		uint32_t pkg_num:4; /* [11:8] */
		uint32_t type_enum:4; /* [15:12] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_glbl_cfg {
	struct {
		uint32_t ide_tx_bypass_en:1; /* [0:0] */
		uint32_t reserved_1:1; /* [1:1] */
		uint32_t ide_rx_bypass_en:1; /* [2:2] */
		uint32_t reserved_3:1; /* [3:3] */
		uint32_t ide_sram_ecc_en:1; /* [4:4] */
		uint32_t reserved_5:1; /* [5:5] */
		uint32_t ide_tbit_src_sel:1; /* [6:6] */
		uint32_t ide_tbit_if_src_sel:1; /* [7:7] */
		uint32_t ide_datapath_prot_en:1; /* [8:8] */
		uint32_t reserved_9:1; /* [9:9] */
		uint32_t reserved_bit_0:2;
		uint32_t reserved_12:1; /* [12:12] */
		uint32_t reserved_31_13:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_sync_msg_cfg {
	struct {
		uint32_t ide_sync_msg_req_threshold:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_link_tbit_cfg {
	struct {
		uint32_t tbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t tbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t tbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_slt_tbit1_cfg {
	struct {
		uint32_t tbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t tbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t tbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_lnk_kbit_cfg {
	struct {
		uint32_t kbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t kbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t kbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_slt_kbit1_cfg {
	struct {
		uint32_t kbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t kbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t kbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_lnk_kbit_cfg {
	struct {
		uint32_t rx_kbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t rx_kbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t rx_kbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_slt_kbit1_cfg {
	struct {
		uint32_t rx_kbit_cfg_s0_pr:1; /* [0:0] */
		uint32_t rx_kbit_cfg_s0_npr:1; /* [1:1] */
		uint32_t rx_kbit_cfg_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_key_thresh_en {
	struct {
		uint32_t tx_key_thresh_en:1; /* [0:0] */
		uint32_t rx_key_thresh_en:1; /* [1:1] */
		uint32_t tx_key_counter_autoclear_en:1; /* [2:2] */
		uint32_t rx_key_counter_autoclear_en:1; /* [3:3] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union pcie_ide_apb_rekey_req_stat {
	struct {
		uint32_t tx_rekey_req_status_s0:1; /* [0:0] */
		uint32_t tx_rekey_req_status_s1:1; /* [1:1] */
		uint32_t reserved_15_2:14; /* [15:2] */
		uint32_t rx_rekey_req_status_s0:1; /* [16:16] */
		uint32_t rx_rekey_req_status_s1:1; /* [17:17] */
		uint32_t reserved_31_18:14; /* [31:18] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_threshold_low_s0 {
	struct {
		uint32_t tx_key_threshold_low_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_threshold_high_s0 {
	struct {
		uint32_t tx_key_threshold_high_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_threshold_low_s0 {
	struct {
		uint32_t rx_key_threshold_low_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_threshold_high_s0 {
	struct {
		uint32_t rx_key_threshold_high_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_threshold_low_s1 {
	struct {
		uint32_t tx_key_threshold_low_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_threshold_high_s1 {
	struct {
		uint32_t tx_key_threshold_high_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_threshold_low_s1 {
	struct {
		uint32_t rx_key_threshold_low_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_threshold_high_s1 {
	struct {
		uint32_t rx_key_threshold_high_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_sram_ecc_status {
	struct {
		uint32_t tx_cipher_key_mem_ecc_stat:2; /* [1:0] */
		uint32_t tx_hash_key_mem_ecc_stat:2; /* [3:2] */
		uint32_t reserved_5_4:2; /* [5:4] */
		uint32_t rx_cipher_key_mem_ecc_stat:2; /* [7:6] */
		uint32_t rx_hash_key_mem_ecc_stat:2; /* [9:8] */
		uint32_t reserved_11_10:2; /* [11:10] */
		uint32_t reserved_13_12:2; /* [13:12] */
		uint32_t reserved_15_14:2; /* [15:14] */
		uint32_t reserved_17_16:2; /* [17:16] */
		uint32_t reserved_31_18:14; /* [31:18] */
	};
	uint32_t val;
};

union pcie_ide_apb_key_security_status_s0 {
	struct {
		uint32_t tx_key_swap_stat_s0_pr:1; /* [0:0] */
		uint32_t tx_key_swap_stat_s0_npr:1; /* [1:1] */
		uint32_t tx_key_swap_stat_s0_cpl:1; /* [2:2] */
		uint32_t rx_key_swap_stat_s0_pr:1; /* [3:3] */
		uint32_t rx_key_swap_stat_s0_npr:1; /* [4:4] */
		uint32_t rx_key_swap_stat_s0_cpl:1; /* [5:5] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_ide_apb_key_security_status_s1 {
	struct {
		uint32_t tx_key_swap_stat_s1_pr:1; /* [0:0] */
		uint32_t tx_key_swap_stat_s1_npr:1; /* [1:1] */
		uint32_t tx_key_swap_stat_s1_cpl:1; /* [2:2] */
		uint32_t rx_key_swap_stat_s1_pr:1; /* [3:3] */
		uint32_t rx_key_swap_stat_s1_npr:1; /* [4:4] */
		uint32_t rx_key_swap_stat_s1_cpl:1; /* [5:5] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_counter_overflow {
	struct {
		uint32_t overflow_status:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_irq_en {
	struct {
		uint32_t sram_ecc_irq_en_glbl:1; /* [0:0] */
		uint32_t key_security_irq_en_glb:1; /* [1:1] */
		uint32_t ide_cnt_ovf_irq_en_glb:1; /* [2:2] */
		uint32_t rx_misrouted_irq_en_glbl:1; /* [3:3] */
		uint32_t rx_check_failed_irq_en_glbl:1; /* [4:4] */
		uint32_t reserved_5:1; /* [5:5] */
		uint32_t rx_pcrc_err_irq_en_glbl:1; /* [6:6] */
		uint32_t tx_kbit_toggled_irq_en_glbl:1; /* [7:7] */
		uint32_t rx_kbit_toggled_irq_en_glbl:1; /* [8:8] */
		uint32_t tx_rekey_req_irq_en_glbl:1; /* [9:9] */
		uint32_t rx_rekey_req_irq_en_glbl:1; /* [10:10] */
		uint32_t datapath_prot_irq_en_glbl:1; /* [11:11] */
		uint32_t insec_stream_irq_en_glbl:1; /* [12:12] */
		uint32_t reserved_30_13:18; /* [30:13] */
		uint32_t irq_en_glbl:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_sram_ecc_irq_en {
	struct {
		uint32_t tx_cipher_key_mem_ecc_en:1; /* [0:0] */
		uint32_t tx_hash_key_mem_ecc_en:1; /* [1:1] */
		uint32_t reserved_2:1; /* [2:2] */
		uint32_t rx_cipher_key_mem_ecc_en:1; /* [3:3] */
		uint32_t rx_hash_key_mem_ecc_en:1; /* [4:4] */
		uint32_t reserved_5:1; /* [5:5] */
		uint32_t reserved_6:1; /* [6:6] */
		uint32_t reserved_7:1; /* [7:7] */
		uint32_t reserved_8:1; /* [8:8] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union pcie_ide_apb_key_security_irq_en {
	struct {
		uint32_t key_security_s0_irq_en:1; /* [0:0] */
		uint32_t key_security_s1_irq_en:1; /* [1:1] */
		uint32_t reserved_2:1; /* [2:2] */
		uint32_t reserved_3:1; /* [3:3] */
		uint32_t reserved_4:1; /* [4:4] */
		uint32_t reserved_5:1; /* [5:5] */
		uint32_t reserved_6:1; /* [6:6] */
		uint32_t reserved_7:1; /* [7:7] */
		uint32_t reserved_8:1; /* [8:8] */
		uint32_t reserved_9:1; /* [9:9] */
		uint32_t reserved_10:1; /* [10:10] */
		uint32_t reserved_11:1; /* [11:11] */
		uint32_t reserved_12:1; /* [12:12] */
		uint32_t reserved_13:1; /* [13:13] */
		uint32_t reserved_14:1; /* [14:14] */
		uint32_t reserved_15:1; /* [15:15] */
		uint32_t reserved_16:1; /* [16:16] */
		uint32_t reserved_17:1; /* [17:17] */
		uint32_t reserved_18:1; /* [18:18] */
		uint32_t reserved_19:1; /* [19:19] */
		uint32_t reserved_20:1; /* [20:20] */
		uint32_t reserved_21:1; /* [21:21] */
		uint32_t reserved_22:1; /* [22:22] */
		uint32_t reserved_23:1; /* [23:23] */
		uint32_t reserved_24:1; /* [24:24] */
		uint32_t reserved_25:1; /* [25:25] */
		uint32_t reserved_26:1; /* [26:26] */
		uint32_t reserved_27:1; /* [27:27] */
		uint32_t reserved_28:1; /* [28:28] */
		uint32_t reserved_29:1; /* [29:29] */
		uint32_t reserved_30:1; /* [30:30] */
		uint32_t reserved_31:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_io_irq_status {
	struct {
		uint32_t rx_misrouted_irq_glbl:1; /* [0:0] */
		uint32_t reserved_1:1; /* [1:1] */
		uint32_t rx_check_failed_irq_glbl:1; /* [2:2] */
		uint32_t reserved_3:1; /* [3:3] */
		uint32_t reserved_4:1; /* [4:4] */
		uint32_t rx_pcrc_err_irq_glbl:1; /* [5:5] */
		uint32_t reserved_6:1; /* [6:6] */
		uint32_t tx_kbit_toggled_irq_glbl:1; /* [7:7] */
		uint32_t rx_kbit_toggled_irq_glbl:1; /* [8:8] */
		uint32_t reserved_9:1; /* [9:9] */
		uint32_t tx_rekey_req_irq_glbl:1; /* [10:10] */
		uint32_t rx_rekey_req_irq_glbl:1; /* [11:11] */
		uint32_t insec_stream_irq_glbl:1; /* [12:12] */
		uint32_t reserved_31_13:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_ide_apb_lnk_snd_stream_insecure {
	struct {
		uint32_t lnk_snd_stream_0_insecure:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ide_apb_slt_snd_stream_insecure {
	struct {
		uint32_t slt_snd_stream_0_insecure:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_ecc_error_inj {
	struct {
		uint32_t ide_ecc_error_inj; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_ecc_error_inj_ctrl {
	struct {
		uint32_t ide_ecc_error_inj_offset:6; /* [5:0] */
		uint32_t reserved_15_6:10; /* [15:6] */
		uint32_t ide_tx_ecc_error_inj_ckey:1; /* [16:16] */
		uint32_t ide_tx_ecc_error_inj_hkey:1; /* [17:17] */
		uint32_t reserved_bit_0:1;
		uint32_t ide_rx_ecc_error_inj_ckey:1; /* [19:19] */
		uint32_t ide_rx_ecc_error_inj_hkey:1; /* [20:20] */
		uint32_t reserved_bit_1:4;
		uint32_t reserved_31_25:7; /* [31:25] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_ecc_error_inj_stat {
	struct {
		uint32_t ide_tx_ecc_error_inj_stat:1; /* [0:0] */
		uint32_t ide_rx_ecc_error_inj_stat:1; /* [1:1] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_lnk_kbit_toggled {
	struct {
		uint32_t tx_lnk_kbit_toggled_s0_pr:1; /* [0:0] */
		uint32_t tx_lnk_kbit_toggled_s0_npr:1; /* [1:1] */
		uint32_t tx_lnk_kbit_toggled_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_lnk_kbit_toggled {
	struct {
		uint32_t rx_lnk_kbit_toggled_s0_pr:1; /* [0:0] */
		uint32_t rx_lnk_kbit_toggled_s0_npr:1; /* [1:1] */
		uint32_t rx_lnk_kbit_toggled_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_lnk_kbit_current {
	struct {
		uint32_t rx_lnk_kbit_current_s0_pr:1; /* [0:0] */
		uint32_t rx_lnk_kbit_current_s0_npr:1; /* [1:1] */
		uint32_t rx_lnk_kbit_current_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_slt_kbit_toggled {
	struct {
		uint32_t tx_slt_kbit_toggled_s0_pr:1; /* [0:0] */
		uint32_t tx_slt_kbit_toggled_s0_npr:1; /* [1:1] */
		uint32_t tx_slt_kbit_toggled_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_slt_kbit_toggled {
	struct {
		uint32_t rx_slt_kbit_toggled_s0_pr:1; /* [0:0] */
		uint32_t rx_slt_kbit_toggled_s0_npr:1; /* [1:1] */
		uint32_t rx_slt_kbit_toggled_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_slt_kbit_current {
	struct {
		uint32_t rx_slt_kbit_current_s0_pr:1; /* [0:0] */
		uint32_t rx_slt_kbit_current_s0_npr:1; /* [1:1] */
		uint32_t rx_slt_kbit_current_s0_cpl:1; /* [2:2] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union pcie_ide_apb_datapath_prot_irq_en {
	struct {
		uint32_t datapath_prot_tx_prefix_irq_en:1; /* [0:0] */
		uint32_t datapath_prot_tx_hdr_irq_en:1; /* [1:1] */
		uint32_t datapath_prot_tx_data_irq_en:1; /* [2:2] */
		uint32_t datapath_prot_tx_mac_irq_en:1; /* [3:3] */
		uint32_t datapath_prot_tx_pcrc_irq_en:1; /* [4:4] */
		uint32_t datapath_prot_rx_prefix_irq_en:1; /* [5:5] */
		uint32_t datapath_prot_rx_hdr_irq_en:1; /* [6:6] */
		uint32_t datapath_prot_rx_data_irq_en:1; /* [7:7] */
		uint32_t datapath_prot_rx_pcrc_mac_bus_irq_en:1; /* [8:8] */
		uint32_t reserved_12_9:4; /* [12:9] */
		uint32_t reserved_31_13:19; /* [31:13] */
	};
	uint32_t val;
};

union pcie_ide_apb_datapath_prot_irq_stat {
	struct {
		uint32_t datapath_prot_tx_prefix_irq_status:2; /* [1:0] */
		uint32_t datapath_prot_tx_hdr_irq_status:2; /* [3:2] */
		uint32_t datapath_prot_tx_data_irq_status:2; /* [5:4] */
		uint32_t datapath_prot_tx_mac_irq_status:2; /* [7:6] */
		uint32_t datapath_prot_tx_pcrc_irq_status:2; /* [9:8] */
		uint32_t datapath_prot_rx_prefix_irq_status:2; /* [11:10] */
		uint32_t datapath_prot_rx_hdr_irq_status:2; /* [13:12] */
		uint32_t datapath_prot_rx_data_irq_status:2; /* [15:14] */
		uint32_t datapath_prot_rx_pcrc_mac_bus_irq_status:2; /* [17:16] */
		uint32_t reserved_25_18:8; /* [25:18] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union pcie_ide_apb_datapath_prot_error_inj_ctrl {
	struct {
		uint32_t datapath_prot_error_inj_en:1; /* [0:0] */
		uint32_t datapath_prot_error_inj_type:2; /* [2:1] */
		uint32_t datapath_prot_error_inj_count:8; /* [10:3] */
		uint32_t datapath_prot_error_inj_loc:5; /* [15:11] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_usage_counter_low_s0 {
	struct {
		uint32_t tx_key_usage_counter_low_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_usage_counter_high_s0 {
	struct {
		uint32_t tx_key_usage_counter_high_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_usage_counter_low_s0 {
	struct {
		uint32_t rx_key_usage_counter_low_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_usage_counter_high_s0 {
	struct {
		uint32_t rx_key_usage_counter_high_s0; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_usage_counter_low_s1 {
	struct {
		uint32_t tx_key_usage_counter_low_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_tx_key_usage_counter_high_s1 {
	struct {
		uint32_t tx_key_usage_counter_high_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_usage_counter_low_s1 {
	struct {
		uint32_t rx_key_usage_counter_low_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_rx_key_usage_counter_high_s1 {
	struct {
		uint32_t rx_key_usage_counter_high_s1; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_tx_pcrc_err_mask {
	struct {
		uint32_t tx_pcrc_error_mask; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_tx_pcrc_err_cnt {
	struct {
		uint32_t tx_pcrc_error_cnt:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_rx_pcrc_err_mask {
	struct {
		uint32_t rx_pcrc_error_mask; /* [31:0] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_rx_pcrc_err_cnt {
	struct {
		uint32_t rx_pcrc_error_cnt:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_tdisp_on {
	struct {
		uint32_t link_0_tdisp_on:1; /* [0:0] */
		uint32_t reserved_15_1:15; /* [15:1] */
		uint32_t slct_0_tdisp_on:1; /* [16:16] */
		uint32_t reserved_31_17:15; /* [31:17] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_discard_override {
	struct {
		uint32_t discard_override:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union pcie_ide_apb_ide_msg_on_selective_en {
	struct {
		uint32_t ide_msg_on_selective_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

struct pcie_ide_apb_register {
	union pcie_ide_apb_ide_core_ver_num ide_core_ver_num; /* offset : 0x0 */
	union pcie_ide_apb_ide_core_ver_type ide_core_ver_type; /* offset : 0x4 */
	union pcie_ide_apb_ide_glbl_cfg ide_glbl_cfg; /* offset : 0x8 */
	union pcie_ide_apb_ide_sync_msg_cfg ide_sync_msg_cfg; /* offset : 0xc */
	union pcie_ide_apb_tx_link_tbit_cfg tx_link_tbit_cfg; /* offset : 0x10 */
	union pcie_ide_apb_tx_slt_tbit1_cfg tx_slt_tbit1_cfg; /* offset : 0x14 */
	uint32_t reserved_1;
	union pcie_ide_apb_tx_lnk_kbit_cfg tx_lnk_kbit_cfg; /* offset : 0x1c */
	union pcie_ide_apb_tx_slt_kbit1_cfg tx_slt_kbit1_cfg; /* offset : 0x20 */
	union pcie_ide_apb_rx_lnk_kbit_cfg rx_lnk_kbit_cfg; /* offset : 0x24 */
	union pcie_ide_apb_rx_slt_kbit1_cfg rx_slt_kbit1_cfg; /* offset : 0x28 */
	union pcie_ide_apb_key_thresh_en key_thresh_en; /* offset : 0x2c */
	union pcie_ide_apb_rekey_req_stat rekey_req_stat; /* offset : 0x30 */
	uint32_t reserved_2[3];
	union pcie_ide_apb_tx_key_threshold_low_s0 tx_key_threshold_low_s0; /* offset : 0x40 */
	union pcie_ide_apb_tx_key_threshold_high_s0 tx_key_threshold_high_s0; /* offset : 0x44 */
	union pcie_ide_apb_rx_key_threshold_low_s0 rx_key_threshold_low_s0; /* offset : 0x48 */
	union pcie_ide_apb_rx_key_threshold_high_s0 rx_key_threshold_high_s0; /* offset : 0x4c */
	union pcie_ide_apb_tx_key_threshold_low_s1 tx_key_threshold_low_s1; /* offset : 0x50 */
	union pcie_ide_apb_tx_key_threshold_high_s1 tx_key_threshold_high_s1; /* offset : 0x54 */
	union pcie_ide_apb_rx_key_threshold_low_s1 rx_key_threshold_low_s1; /* offset : 0x58 */
	union pcie_ide_apb_rx_key_threshold_high_s1 rx_key_threshold_high_s1; /* offset : 0x5c */
	uint32_t reserved_3[123];
	union pcie_ide_apb_sram_ecc_status sram_ecc_status; /* offset : 0x24c */
	union pcie_ide_apb_key_security_status_s0 key_security_status_s0; /* offset : 0x250 */
	union pcie_ide_apb_key_security_status_s1 key_security_status_s1; /* offset : 0x254 */
	uint32_t reserved_4[31];
	union pcie_ide_apb_ide_counter_overflow ide_counter_overflow; /* offset : 0x2d4 */
	union pcie_ide_apb_ide_irq_en ide_irq_en; /* offset : 0x2d8 */
	union pcie_ide_apb_ide_sram_ecc_irq_en ide_sram_ecc_irq_en; /* offset : 0x2dc */
	union pcie_ide_apb_key_security_irq_en key_security_irq_en; /* offset : 0x2e0 */
	union pcie_ide_apb_ide_io_irq_status ide_io_irq_status; /* offset : 0x2e4 */
	union pcie_ide_apb_lnk_snd_stream_insecure lnk_snd_stream_insecure; /* offset : 0x2e8 */
	union pcie_ide_apb_slt_snd_stream_insecure slt_snd_stream_insecure; /* offset : 0x2ec */
	uint32_t reserved_5[3];
	union pcie_ide_apb_ide_ecc_error_inj ide_ecc_error_inj; /* offset : 0x2fc */
	union pcie_ide_apb_ide_ecc_error_inj_ctrl ide_ecc_error_inj_ctrl; /* offset : 0x300 */
	union pcie_ide_apb_ide_ecc_error_inj_stat ide_ecc_error_inj_stat; /* offset : 0x304 */
	union pcie_ide_apb_tx_lnk_kbit_toggled tx_lnk_kbit_toggled; /* offset : 0x308 */
	union pcie_ide_apb_rx_lnk_kbit_toggled rx_lnk_kbit_toggled; /* offset : 0x30c */
	union pcie_ide_apb_rx_lnk_kbit_current rx_lnk_kbit_current; /* offset : 0x310 */
	union pcie_ide_apb_tx_slt_kbit_toggled tx_slt_kbit_toggled; /* offset : 0x314 */
	union pcie_ide_apb_rx_slt_kbit_toggled rx_slt_kbit_toggled; /* offset : 0x318 */
	union pcie_ide_apb_rx_slt_kbit_current rx_slt_kbit_current; /* offset : 0x31c */
	union pcie_ide_apb_datapath_prot_irq_en datapath_prot_irq_en; /* offset : 0x320 */
	union pcie_ide_apb_datapath_prot_irq_stat datapath_prot_irq_stat; /* offset : 0x324 */
	union pcie_ide_apb_datapath_prot_error_inj_ctrl datapath_prot_error_inj_ctrl; /* offset : 0x328 */
	union pcie_ide_apb_tx_key_usage_counter_low_s0 tx_key_usage_counter_low_s0; /* offset : 0x32c */
	union pcie_ide_apb_tx_key_usage_counter_high_s0 tx_key_usage_counter_high_s0; /* offset : 0x330 */
	union pcie_ide_apb_rx_key_usage_counter_low_s0 rx_key_usage_counter_low_s0; /* offset : 0x334 */
	union pcie_ide_apb_rx_key_usage_counter_high_s0 rx_key_usage_counter_high_s0; /* offset : 0x338 */
	union pcie_ide_apb_tx_key_usage_counter_low_s1 tx_key_usage_counter_low_s1; /* offset : 0x33c */
	union pcie_ide_apb_tx_key_usage_counter_high_s1 tx_key_usage_counter_high_s1; /* offset : 0x340 */
	union pcie_ide_apb_rx_key_usage_counter_low_s1 rx_key_usage_counter_low_s1; /* offset : 0x344 */
	union pcie_ide_apb_rx_key_usage_counter_high_s1 rx_key_usage_counter_high_s1; /* offset : 0x348 */
	uint32_t reserved_6[56];
	union pcie_ide_apb_ide_tx_pcrc_err_mask ide_tx_pcrc_err_mask; /* offset : 0x42c */
	union pcie_ide_apb_ide_tx_pcrc_err_cnt ide_tx_pcrc_err_cnt; /* offset : 0x430 */
	union pcie_ide_apb_ide_rx_pcrc_err_mask ide_rx_pcrc_err_mask; /* offset : 0x434 */
	union pcie_ide_apb_ide_rx_pcrc_err_cnt ide_rx_pcrc_err_cnt; /* offset : 0x438 */
	uint32_t reserved_7[3];
	union pcie_ide_apb_ide_tdisp_on ide_tdisp_on; /* offset : 0x448 */
	union pcie_ide_apb_ide_discard_override ide_discard_override; /* offset : 0x44c */
	uint32_t reserved_8[44];
	union pcie_ide_apb_ide_msg_on_selective_en ide_msg_on_selective_en; /* offset : 0x500 */
};
