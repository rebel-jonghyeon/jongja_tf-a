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

union cmu_pcie_pll_locktime_pll_pcie {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_pcie_pll_con0_pll_pcie {
	struct {
		uint32_t div_s:3; /* [2:0] */
		uint32_t pll_lock:1; /* [3:3] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved0:2; /* [6:5] */
		uint32_t mux_busy:1; /* [7:7] */
		uint32_t div_p:6; /* [13:8] */
		uint32_t reserved1:2; /* [15:14] */
		uint32_t div_m:10; /* [25:16] */
		uint32_t lock_en:1; /* [26:26] */
		uint32_t lock_fail:1; /* [27:27] */
		uint32_t use_hw_lock_det:1; /* [28:28] */
		uint32_t stable:1; /* [29:29] */
		uint32_t use_lock_fail:1; /* [30:30] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_pll_con1_pll_pcie {
	struct {
		uint32_t ext_afc:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t icp:2; /* [7:6] */
		uint32_t lock_con_dly:2; /* [9:8] */
		uint32_t disable_sdiv_clock_stop:1; /* [10:10] */
		uint32_t disable_all_clock_stop:1; /* [11:11] */
		uint32_t lock_con_in:2; /* [13:12] */
		uint32_t lock_con_out:2; /* [15:14] */
		uint32_t sscgen:1; /* [16:16] */
		uint32_t reserved0:3; /* [19:17] */
		uint32_t afc_enb:1; /* [20:20] */
		uint32_t reserved1:1; /* [21:21] */
		uint32_t bypass:1; /* [22:22] */
		uint32_t reserved2:2; /* [24:23] */
		uint32_t fout_mask:1; /* [25:25] */
		uint32_t reserved3:2; /* [27:26] */
		uint32_t rsel:4; /* [31:28] */
	};
	uint32_t val;
};

union cmu_pcie_pll_con2_pll_pcie {
	struct {
		uint32_t auto_pll_ctrl:1; /* [0:0] */
		uint32_t manual_pll_ctrl:1; /* [1:1] */
		uint32_t reserved0:6; /* [7:2] */
		uint32_t rsel:16; /* [23:8] */
		uint32_t reserved1:4; /* [27:24] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_automatic_bypass:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_pll_con3_pll_pcie {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_pcie_pll_con4_pll_pcie {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_pcie_cmu_pcie_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clkout_con_blk_pcie_cmu_pcie_clkout {
	struct {
		uint32_t div_ratio:5; /* [4:0] */
		uint32_t reserved0:3; /* [7:5] */
		uint32_t select:5; /* [12:8] */
		uint32_t reserved1:3; /* [15:13] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved2:3; /* [19:17] */
		uint32_t validate_clk_req:1; /* [20:20] */
		uint32_t reserved3:7; /* [27:21] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable:1; /* [29:29] */
		uint32_t reserved4:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_mux_mux_pcie_auxclk {
	struct {
		uint32_t select:1; /* [0:0] */
		uint32_t reserved0:15; /* [15:1] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_mux_mux_pcie_tsclk {
	struct {
		uint32_t select:1; /* [0:0] */
		uint32_t reserved0:15; /* [15:1] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div2_pcie_aclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div20_pcie_refclk_p {
	struct {
		uint32_t divratio:5; /* [4:0] */
		uint32_t reserved0:11; /* [15:5] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div4_pcie_pclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div2_pcie_scan_macpclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div16_pcie_crparaclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div_pcie_auxclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div2_pcie_scan_rxclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div2_pcie_scan_ropllclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div1_pcie_scan_wordclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div16_pcie_scan_refclk {
	struct {
		uint32_t divratio:5; /* [4:0] */
		uint32_t reserved0:11; /* [15:5] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div16_pcie_scan_crclk {
	struct {
		uint32_t divratio:5; /* [4:0] */
		uint32_t reserved0:11; /* [15:5] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div2_pcie_scan_dwordclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div16_pcie_phy_scan_clk {
	struct {
		uint32_t divratio:5; /* [4:0] */
		uint32_t reserved0:11; /* [15:5] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_div_div1_pcie_tsclk {
	struct {
		uint32_t divratio:6; /* [5:0] */
		uint32_t reserved0:10; /* [15:6] */
		uint32_t busy:1; /* [16:16] */
		uint32_t reserved1:11; /* [27:17] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved3:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_cmu_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_d_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_d_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_ast_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_ast_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_p_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_apb_pcies_g_mi_ipclkport_clk_m {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_apb_pcies_g1_mi_ipclkport_clk_m {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_t_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_slv_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_mstr_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_dbi_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_auxclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_ref_alt0_clk_p {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_apb_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcie_cr_para_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_max_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_pipe_rx_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_ropll_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_cr_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union
cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_dword_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_word_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_ref_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_cr_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union
cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_dword_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_word_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_ref_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_cr_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union
cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_dword_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_word_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_ref_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_cr_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union
cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_dword_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_word_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_ref_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_apbcfg_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_phy_cr_para_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_apbcfg_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_phy_cr_para_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_apbcfg_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_phy_cr_para_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_apbcfg_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_phy_cr_para_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_sysreg_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk1000 {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk500 {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_tbu_pcie_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cm7_ipclkport_clkin {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_mstr_aclk_soc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_slv_aclk_soc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_i_driver_apb_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_mailbox_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_uart_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_wdt_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_axi_rs_pciem_d_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_iat_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_pclkdbg {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_tsclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_sysreg_buscsr_pcie_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_iat_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_m_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_s_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_cm7_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pe_wrapper_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_intmem_pcie_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_axi2apb_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_axi2apb_pcie_phy_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_pcie_iip_device_inst_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_phy0_apb2cr_para_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_phy1_apb2cr_para_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_phy2_apb2cr_para_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_phy3_apb2cr_para_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_noc_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_cm7_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_gpio_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_pcie_sub_ctrl_inst_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_uart_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_wdt_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_axi_rs_pciem_d_dmyqch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_iat_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_vdm_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_apb_async_iat_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_cssys_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_amba_ovrd_iat_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_amba_ovrd_pciec_m_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_amba_ovrd_pciec_s_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_amba_ovrd_cm7_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_pe_wrapper_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_pe_wrapper_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_d_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_d_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_p_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_t_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_pcie_cmu_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_d_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_d_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pcies_p_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_apb_pcies_g_mi_qch_clk_m {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_apb_pcies_g1_mi_qch_clk_m {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_lh_pciem_t_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_sysreg_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_tbu_pcie_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_tbu_pcie_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_gpio_pcie_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_mailbox_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_cssys_pcie_qch_s_ahbap_cssys {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_sysreg_buscsr_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_pcie_qch_con_intmem_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_pcie {
	union cmu_pcie_pll_locktime_pll_pcie pll_locktime_pll_pcie; /* offset : 0x0 */
	uint32_t reserved_1[63];
	union cmu_pcie_pll_con0_pll_pcie pll_con0_pll_pcie; /* offset : 0x100 */
	union cmu_pcie_pll_con1_pll_pcie pll_con1_pll_pcie; /* offset : 0x104 */
	union cmu_pcie_pll_con2_pll_pcie pll_con2_pll_pcie; /* offset : 0x108 */
	union cmu_pcie_pll_con3_pll_pcie pll_con3_pll_pcie; /* offset : 0x10c */
	union cmu_pcie_pll_con4_pll_pcie pll_con4_pll_pcie; /* offset : 0x110 */
	uint32_t reserved_2[443];
	union cmu_pcie_pcie_cmu_pcie_controller_option
		pcie_cmu_pcie_controller_option; /* offset : 0x800 */
	union cmu_pcie_clkout_con_blk_pcie_cmu_pcie_clkout
		clkout_con_blk_pcie_cmu_pcie_clkout; /* offset : 0x804 */
	uint32_t reserved_3[510];
	union cmu_pcie_clk_con_mux_mux_pcie_auxclk clk_con_mux_mux_pcie_auxclk; /* offset : 0x1000 */
	union cmu_pcie_clk_con_mux_mux_pcie_tsclk clk_con_mux_mux_pcie_tsclk; /* offset : 0x1004 */
	uint32_t reserved_4[510];
	union cmu_pcie_clk_con_div_div2_pcie_aclk clk_con_div_div2_pcie_aclk; /* offset : 0x1800 */
	union cmu_pcie_clk_con_div_div20_pcie_refclk_p
		clk_con_div_div20_pcie_refclk_p; /* offset : 0x1804 */
	union cmu_pcie_clk_con_div_div4_pcie_pclk clk_con_div_div4_pcie_pclk; /* offset : 0x1808 */
	union cmu_pcie_clk_con_div_div2_pcie_scan_macpclk
		clk_con_div_div2_pcie_scan_macpclk; /* offset : 0x180c */
	union cmu_pcie_clk_con_div_div16_pcie_crparaclk
		clk_con_div_div16_pcie_crparaclk; /* offset : 0x1810 */
	union cmu_pcie_clk_con_div_div_pcie_auxclk clk_con_div_div_pcie_auxclk; /* offset : 0x1814 */
	union cmu_pcie_clk_con_div_div2_pcie_scan_rxclk
		clk_con_div_div2_pcie_scan_rxclk; /* offset : 0x1818 */
	union cmu_pcie_clk_con_div_div2_pcie_scan_ropllclk
		clk_con_div_div2_pcie_scan_ropllclk; /* offset : 0x181c */
	uint32_t reserved_5;
	union cmu_pcie_clk_con_div_div1_pcie_scan_wordclk
		clk_con_div_div1_pcie_scan_wordclk; /* offset : 0x1824 */
	union cmu_pcie_clk_con_div_div16_pcie_scan_refclk
		clk_con_div_div16_pcie_scan_refclk; /* offset : 0x1828 */
	union cmu_pcie_clk_con_div_div16_pcie_scan_crclk
		clk_con_div_div16_pcie_scan_crclk; /* offset : 0x182c */
	union cmu_pcie_clk_con_div_div2_pcie_scan_dwordclk
		clk_con_div_div2_pcie_scan_dwordclk; /* offset : 0x1830 */
	union cmu_pcie_clk_con_div_div16_pcie_phy_scan_clk
		clk_con_div_div16_pcie_phy_scan_clk; /* offset : 0x1834 */
	union cmu_pcie_clk_con_div_div1_pcie_tsclk clk_con_div_div1_pcie_tsclk; /* offset : 0x1838 */
	uint32_t reserved_6[497];
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_cmu_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_pcie_cmu_pcie_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2004 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_pcie_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2008 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_d_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pcies_d_mi_ipclkport_i_clk; /* offset : 0x200c */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_d_si_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pciem_d_si_ipclkport_i_clk; /* offset : 0x2010 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_ast_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pcies_ast_mi_ipclkport_i_clk; /* offset : 0x2014 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_ast_si_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pciem_ast_si_ipclkport_i_clk; /* offset : 0x2018 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pcies_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pcies_p_mi_ipclkport_i_clk; /* offset : 0x201c */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_apb_pcies_g_mi_ipclkport_clk_m
		clk_con_gat_clk_blk_pcie_uid_apb_pcies_g_mi_ipclkport_clk_m; /* offset : 0x2020 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_apb_pcies_g1_mi_ipclkport_clk_m
		clk_con_gat_clk_blk_pcie_uid_apb_pcies_g1_mi_ipclkport_clk_m; /* offset : 0x2024 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_lh_pciem_t_si_ipclkport_i_clk
		clk_con_gat_clk_blk_pcie_uid_lh_pciem_t_si_ipclkport_i_clk; /* offset : 0x2028 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_slv_aclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_slv_aclk; /*offset:0x202c*/
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_mstr_aclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_mstr_aclk; /*offset:0x2030*/
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_dbi_aclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_dbi_aclk; /*offset:0x2034*/
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_auxclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_auxclk; /*offset:0x2038*/
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_ref_alt0_clk_p
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_ref_alt0_clk_p;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_apb_pclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_apb_pclk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcie_cr_para_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcie_cr_para_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_max_pclk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_max_pclk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_pipe_rx_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_pipe_rx_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_ropll_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_pcs_scan_ropll_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_cr_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_cr_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_dword_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_dword_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_word_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_mpll_word_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_ref_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_ref_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy0_scan_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_cr_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_cr_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_dword_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_dword_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_word_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_mpll_word_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_ref_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_ref_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy1_scan_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_cr_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_cr_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_dword_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_dword_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_word_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_mpll_word_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_ref_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_ref_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy2_scan_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_cr_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_cr_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_dword_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_dword_clk;
	union
	cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_word_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_mpll_word_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_ref_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_ref_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_iip_device_inst_ipclkport_phy3_scan_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_apbcfg_pclk
		clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_apbcfg_pclk; /* offset : 0x20a4 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_phy_cr_para_clk
		clk_con_gat_clk_blk_pcie_uid_phy0_apb2cr_para_ipclkport_phy_cr_para_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_apbcfg_pclk
		clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_apbcfg_pclk; /* offset : 0x20ac */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_phy_cr_para_clk
		clk_con_gat_clk_blk_pcie_uid_phy1_apb2cr_para_ipclkport_phy_cr_para_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_apbcfg_pclk
		clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_apbcfg_pclk; /* offset : 0x20b4 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_phy_cr_para_clk
		clk_con_gat_clk_blk_pcie_uid_phy2_apb2cr_para_ipclkport_phy_cr_para_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_apbcfg_pclk
		clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_apbcfg_pclk; /* offset : 0x20bc */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_phy_cr_para_clk
		clk_con_gat_clk_blk_pcie_uid_phy3_apb2cr_para_ipclkport_phy_cr_para_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_sysreg_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_sysreg_pcie_ipclkport_pclk; /* offset : 0x20c4 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk1000
		clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk1000; /* offset : 0x20c8 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk500
		clk_con_gat_clk_blk_pcie_uid_noc_pcie_ipclkport_clk500; /* offset : 0x20cc */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_tbu_pcie_ipclkport_aclk
		clk_con_gat_clk_blk_pcie_uid_tbu_pcie_ipclkport_aclk; /* offset : 0x20d0 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cm7_ipclkport_clkin
		clk_con_gat_clk_blk_pcie_uid_cm7_ipclkport_clkin; /* offset : 0x20d4 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_oscclk
		clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_oscclk; /* offset : 0x20d8 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_gpio_pcie_ipclkport_pclk; /* offset : 0x20dc */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_mstr_aclk_soc
		clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_mstr_aclk_soc;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_slv_aclk_soc
		clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_slv_aclk_soc;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_i_driver_apb_clk
		clk_con_gat_clk_blk_pcie_uid_pcie_sub_ctrl_inst_ipclkport_i_driver_apb_clk;
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_mailbox_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_mailbox_ipclkport_pclk; /* offset : 0x20ec */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_uart_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_uart_pcie_ipclkport_pclk; /* offset : 0x20f0 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_wdt_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_wdt_pcie_ipclkport_pclk; /* offset : 0x20f4 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_axi_rs_pciem_d_ipclkport_aclk
		clk_con_gat_clk_blk_pcie_uid_axi_rs_pciem_d_ipclkport_aclk; /* offset : 0x20f8 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_iat_ipclkport_aclk
		clk_con_gat_clk_blk_pcie_uid_iat_ipclkport_aclk; /* offset : 0x20fc */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_pclk; /* offset : 0x2100 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_aclk
		clk_con_gat_clk_blk_pcie_uid_vdm_ipclkport_aclk; /* offset : 0x2104 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_pclkdbg
		clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_pclkdbg; /* offset : 0x2108 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_tsclk
		clk_con_gat_clk_blk_pcie_uid_cssys_pcie_ipclkport_tsclk; /* offset : 0x210c */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_sysreg_buscsr_pcie_ipclkport_pclk
		clk_con_gat_clk_blk_pcie_uid_sysreg_buscsr_pcie_ipclkport_pclk; /* offset : 0x2110 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_iat_ipclkport_i_aclk
		clk_con_gat_clk_blk_pcie_uid_amba_ovrd_iat_ipclkport_i_aclk; /* offset : 0x2114 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_m_ipclkport_i_aclk
		clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_m_ipclkport_i_aclk; /* offset : 0x2118 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_s_ipclkport_i_aclk
		clk_con_gat_clk_blk_pcie_uid_amba_ovrd_pciec_s_ipclkport_i_aclk; /* offset : 0x211c */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_amba_ovrd_cm7_ipclkport_i_aclk
		clk_con_gat_clk_blk_pcie_uid_amba_ovrd_cm7_ipclkport_i_aclk; /* offset : 0x2120 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_pe_wrapper_ipclkport_clk_s
		clk_con_gat_clk_blk_pcie_uid_pe_wrapper_ipclkport_clk_s; /* offset : 0x2124 */
	union cmu_pcie_clk_con_gat_clk_blk_pcie_uid_intmem_pcie_ipclkport_aclk
		clk_con_gat_clk_blk_pcie_uid_intmem_pcie_ipclkport_aclk; /* offset : 0x2128 */
	uint32_t reserved_7[949];
	union cmu_pcie_qch_con_axi2apb_pcie_qch qch_con_axi2apb_pcie_qch; /* offset : 0x3000 */
	union cmu_pcie_qch_con_axi2apb_pcie_phy_qch qch_con_axi2apb_pcie_phy_qch; /* offset : 0x3004 */
	union cmu_pcie_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3008 */
	union cmu_pcie_qch_con_pcie_iip_device_inst_qch
		qch_con_pcie_iip_device_inst_qch; /* offset : 0x300c */
	union cmu_pcie_qch_con_phy0_apb2cr_para_qch qch_con_phy0_apb2cr_para_qch; /* offset : 0x3010 */
	union cmu_pcie_qch_con_phy1_apb2cr_para_qch qch_con_phy1_apb2cr_para_qch; /* offset : 0x3014 */
	union cmu_pcie_qch_con_phy2_apb2cr_para_qch qch_con_phy2_apb2cr_para_qch; /* offset : 0x3018 */
	union cmu_pcie_qch_con_phy3_apb2cr_para_qch qch_con_phy3_apb2cr_para_qch; /* offset : 0x301c */
	union cmu_pcie_qch_con_noc_pcie_qch qch_con_noc_pcie_qch; /* offset : 0x3020 */
	union cmu_pcie_qch_con_cm7_qch qch_con_cm7_qch; /* offset : 0x3024 */
	union cmu_pcie_qch_con_gpio_pcie_qch qch_con_gpio_pcie_qch; /* offset : 0x3028 */
	union cmu_pcie_qch_con_pcie_sub_ctrl_inst_qch
		qch_con_pcie_sub_ctrl_inst_qch; /* offset : 0x302c */
	union cmu_pcie_qch_con_uart_pcie_qch qch_con_uart_pcie_qch; /* offset : 0x3030 */
	union cmu_pcie_qch_con_wdt_pcie_qch qch_con_wdt_pcie_qch; /* offset : 0x3034 */
	union cmu_pcie_qch_con_axi_rs_pciem_d_dmyqch
		qch_con_axi_rs_pciem_d_dmyqch; /* offset : 0x3038 */
	union cmu_pcie_qch_con_iat_qch qch_con_iat_qch; /* offset : 0x303c */
	union cmu_pcie_qch_con_vdm_qch qch_con_vdm_qch; /* offset : 0x3040 */
	union cmu_pcie_qch_con_apb_async_iat_qch qch_con_apb_async_iat_qch; /* offset : 0x3044 */
	union cmu_pcie_qch_con_cssys_pcie_qch qch_con_cssys_pcie_qch; /* offset : 0x3048 */
	union cmu_pcie_qch_con_amba_ovrd_iat_qch qch_con_amba_ovrd_iat_qch; /* offset : 0x304c */
	union cmu_pcie_qch_con_amba_ovrd_pciec_m_qch
		qch_con_amba_ovrd_pciec_m_qch; /* offset : 0x3050 */
	union cmu_pcie_qch_con_amba_ovrd_pciec_s_qch
		qch_con_amba_ovrd_pciec_s_qch; /* offset : 0x3054 */
	union cmu_pcie_qch_con_amba_ovrd_cm7_qch qch_con_amba_ovrd_cm7_qch; /* offset : 0x3058 */
	union cmu_pcie_qch_con_pe_wrapper_qch_s qch_con_pe_wrapper_qch_s; /* offset : 0x305c */
	union cmu_pcie_qch_con_pe_wrapper_qch_d qch_con_pe_wrapper_qch_d; /* offset : 0x3060 */
	union cmu_pcie_qch_con_lh_pcies_d_mi_pch qch_con_lh_pcies_d_mi_pch; /* offset : 0x3064 */
	union cmu_pcie_qch_con_lh_pciem_d_si_pch qch_con_lh_pciem_d_si_pch; /* offset : 0x3068 */
	union cmu_pcie_qch_con_lh_pcies_ast_mi_pch qch_con_lh_pcies_ast_mi_pch; /* offset : 0x306c */
	union cmu_pcie_qch_con_lh_pciem_ast_si_pch qch_con_lh_pciem_ast_si_pch; /* offset : 0x3070 */
	union cmu_pcie_qch_con_lh_pcies_p_mi_pch qch_con_lh_pcies_p_mi_pch; /* offset : 0x3074 */
	union cmu_pcie_qch_con_lh_pciem_t_si_pch qch_con_lh_pciem_t_si_pch; /* offset : 0x3078 */
	union cmu_pcie_qch_con_pcie_cmu_pcie_qch qch_con_pcie_cmu_pcie_qch; /* offset : 0x307c */
	union cmu_pcie_qch_con_lh_pcies_d_mi_qch qch_con_lh_pcies_d_mi_qch; /* offset : 0x3080 */
	union cmu_pcie_qch_con_lh_pciem_d_si_qch qch_con_lh_pciem_d_si_qch; /* offset : 0x3084 */
	union cmu_pcie_qch_con_lh_pcies_ast_mi_qch qch_con_lh_pcies_ast_mi_qch; /* offset : 0x3088 */
	union cmu_pcie_qch_con_lh_pciem_ast_si_qch qch_con_lh_pciem_ast_si_qch; /* offset : 0x308c */
	union cmu_pcie_qch_con_lh_pcies_p_mi_qch qch_con_lh_pcies_p_mi_qch; /* offset : 0x3090 */
	union cmu_pcie_qch_con_apb_pcies_g_mi_qch_clk_m
		qch_con_apb_pcies_g_mi_qch_clk_m; /* offset : 0x3094 */
	union cmu_pcie_qch_con_apb_pcies_g1_mi_qch_clk_m
		qch_con_apb_pcies_g1_mi_qch_clk_m; /* offset : 0x3098 */
	union cmu_pcie_qch_con_lh_pciem_t_si_qch qch_con_lh_pciem_t_si_qch; /* offset : 0x309c */
	union cmu_pcie_qch_con_sysreg_pcie_qch qch_con_sysreg_pcie_qch; /* offset : 0x30a0 */
	union cmu_pcie_qch_con_tbu_pcie_qch_cg qch_con_tbu_pcie_qch_cg; /* offset : 0x30a4 */
	union cmu_pcie_qch_con_tbu_pcie_qch_pd qch_con_tbu_pcie_qch_pd; /* offset : 0x30a8 */
	union cmu_pcie_qch_con_gpio_pcie_qch_s qch_con_gpio_pcie_qch_s; /* offset : 0x30ac */
	union cmu_pcie_qch_con_mailbox_qch qch_con_mailbox_qch; /* offset : 0x30b0 */
	union cmu_pcie_qch_con_cssys_pcie_qch_s_ahbap_cssys
		qch_con_cssys_pcie_qch_s_ahbap_cssys; /* offset : 0x30b4 */
	union cmu_pcie_qch_con_sysreg_buscsr_pcie_qch
		qch_con_sysreg_buscsr_pcie_qch; /* offset : 0x30b8 */
	union cmu_pcie_qch_con_intmem_pcie_qch qch_con_intmem_pcie_qch; /* offset : 0x30bc */
};

enum PCIE_CLK_OUT {
	OSCCLK_PCIE,
	PLL_PCIE,
	CLK_PCIE_ACLK,
	CLK_PCIE_PCLK,
	CLK_PCIE_CRPARACLK,
	CLK_PCIE_REFCLK_P,
	CLK_PCIE_AUXCLK,
	PCIE_CLK_LH_SCAN_DST,
	PCIE_CLK_LH_SCAN_ETC,
	CLK_PCIE_OSCCLK,
	CLK_PCIE_SCAN_MAXPCLK,
	CLK_PCIE_SCAN_RXCLK,
	CLK_PCIE_SCAN_ROPLLCLK,
	CLK_PCIE_SCAN_CRCLK,
	CLK_PCIE_SCAN_DWORDCLK,
	CLK_PCIE_SCAN_WORDCLK,
	CLK_PCIE_TSCLK,
	CLK_PCIE_SCAN_REFCLK,
	CLK_PCIE_PHY_SCAN_CLK,
};
