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

union cmu_cp_pll_locktime_pll_cp {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_cp_pll_locktime_pll_cp_dvfs {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_cp_shortstop {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t reserved0:3; /* [3:1] */
		uint32_t pre_count:4; /* [7:4] */
		uint32_t post_count:4; /* [11:8] */
		uint32_t keepparentreq_count:4; /* [15:12] */
		uint32_t debug_info:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_cp_pll_con0_pll_cp {
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

union cmu_cp_pll_con1_pll_cp {
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

union cmu_cp_pll_con2_pll_cp {
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

union cmu_cp_pll_con3_pll_cp {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_cp_pll_con4_pll_cp {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_pll_con0_pll_cp_dvfs {
	struct {
		uint32_t div_s:3; /* [2:0] */
		uint32_t pll_lock:1; /* [3:3] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t mux_busy:1; /* [7:7] */
		uint32_t div_p:6; /* [13:8] */
		uint32_t reserved2:2; /* [15:14] */
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

union cmu_cp_pll_con1_pll_cp_dvfs {
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

union cmu_cp_pll_con2_pll_cp_dvfs {
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

union cmu_cp_pll_con3_pll_cp_dvfs {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_cp_pll_con4_pll_cp_dvfs {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_cp_cmu_cp_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clkout_con_blk_cp_cmu_cp_clkout {
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

union cmu_cp_clk_con_mux_mux_cp_pll_fout {
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

union cmu_cp_clk_con_mux_mux_cp_tsclk {
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

union cmu_cp_clk_con_div_div4_hch_cp_cmuref {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_div_div2_hch_cp_coreclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_div_div4_hch_cp_aclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_div_div8_hch_cp_pclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_div_div8_hch_cp_stm {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_div_div2_cp_cmuref {
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

union cmu_cp_clk_con_div_div1_cp_coreclk {
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

union cmu_cp_clk_con_div_div2_cp_aclk {
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

union cmu_cp_clk_con_div_div4_cp_pclk {
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

union cmu_cp_clk_con_div_div5_cp_add {
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

union cmu_cp_clk_con_div_div4_cp_stm {
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

union cmu_cp_clk_con_div_div1_cp_tsclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_cp_cmu_cp_ipclkport_pclk {
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

union cmu_cp_clk_con_gat_shortstop_cp {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_cp_clk_con_gat_gate_cp {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_dst {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_etc {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_d_mi_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_d_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_p_mi_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t0_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t1_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t2_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t3_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t4_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_si_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_mi_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_apb_cps_g0_mi_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_apb_cps_g1_mi_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sysreg_cp_ipclkport_pclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk_r {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_stmckclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk_r {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_bisr_ctrlr_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_cntvalue_g2b_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_mailbox_m3_ipclkport_pclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_mailbox_m4_ipclkport_pclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_mst_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_replicator_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_dec0_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_dec1_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_cti_async_mst_stm_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_cti_async_slv_stm_ipclkport_clk_s {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_stm_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_ch_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk_tm {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_pclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_dbgen_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_niden_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_spiden_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_spniden_ipclkport_clk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_sysreg_buscsr_cp_ipclkport_pclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_amba_ovrd_ace_ipclkport_i_aclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_amba_ovrd_acp_ipclkport_i_aclk {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_s {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_m {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_s {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_si {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_mi {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_mi {
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

union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_si {
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

union cmu_cp_qch_con_lh_qch {
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

union cmu_cp_qch_con_axi2apb_cp_qch {
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

union cmu_cp_qch_con_nic_cp_dmyqch {
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

union cmu_cp_qch_con_artemis4_dmyqch {
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

union cmu_cp_qch_con_artemis4_qch {
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

union cmu_cp_qch_con_cntvalue_g2b_dmyqch {
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

union cmu_cp_qch_con_ts_replicator_dmyqch {
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

union cmu_cp_qch_con_cti_async_slv_stm_dmyqch {
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

union cmu_cp_qch_con_stm_dmyqch {
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

union cmu_cp_qch_con_add_cp_dmyqch {
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

union cmu_cp_qch_con_add_con_cp_dmyqch {
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

union cmu_cp_qch_con_sync_dbgen_dmyqch {
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

union cmu_cp_qch_con_sync_niden_dmyqch {
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

union cmu_cp_qch_con_sync_spiden_dmyqch {
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

union cmu_cp_qch_con_sync_spniden_dmyqch {
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

union cmu_cp_qch_con_rstnsync_coreclk_dmyqch {
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

union cmu_cp_qch_con_rstnsync_aclk_dmyqch {
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

union cmu_cp_qch_con_rstnsync_pclk_dmyqch {
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

union cmu_cp_qch_con_rstnsync_stm_dmyqch {
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

union cmu_cp_qch_con_rstnsync_tsclk_dmyqch {
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

union cmu_cp_qch_con_amba_ovrd_ace_dmyqch {
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

union cmu_cp_qch_con_amba_ovrd_acp_dmyqch {
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

union cmu_cp_qch_con_lh_cps_d_mi_pch {
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

union cmu_cp_qch_con_lh_cpm_d_si_pch {
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

union cmu_cp_qch_con_lh_cps_p_mi_pch {
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

union cmu_cp_qch_con_lh_cpm_t0_si_pch {
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

union cmu_cp_qch_con_lh_cpm_t1_si_pch {
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

union cmu_cp_qch_con_lh_cpm_t2_si_pch {
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

union cmu_cp_qch_con_lh_cpm_t3_si_pch {
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

union cmu_cp_qch_con_lh_cpm_t4_si_pch {
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

union cmu_cp_qch_con_lh_cpm_ast_si_pch {
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

union cmu_cp_qch_con_lh_cps_ast_mi_pch {
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

union cmu_cp_qch_con_lh_cpm_ast_top_pch_si {
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

union cmu_cp_qch_con_lh_cpm_ast_top_pch_mi {
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

union cmu_cp_qch_con_lh_cps_ast_top_pch_si {
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

union cmu_cp_qch_con_lh_cps_ast_top_pch_mi {
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

union cmu_cp_qch_con_cp_cmu_cp_qch {
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

union cmu_cp_qch_con_lh_cps_d_mi_qch {
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

union cmu_cp_qch_con_lh_cpm_d_si_qch {
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

union cmu_cp_qch_con_lh_cps_p_mi_qch {
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

union cmu_cp_qch_con_lh_cpm_t0_si_qch {
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

union cmu_cp_qch_con_lh_cpm_t1_si_qch {
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

union cmu_cp_qch_con_lh_cpm_t2_si_qch {
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

union cmu_cp_qch_con_lh_cpm_t3_si_qch {
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

union cmu_cp_qch_con_lh_cpm_t4_si_qch {
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

union cmu_cp_qch_con_lh_cpm_ast_si_qch {
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

union cmu_cp_qch_con_lh_cps_ast_mi_qch {
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

union cmu_cp_qch_con_apb_cps_g0_mi_qch {
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

union cmu_cp_qch_con_apb_cps_g1_mi_qch {
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

union cmu_cp_qch_con_sysreg_cp_qch {
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

union cmu_cp_qch_con_mailbox_m3_qch {
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

union cmu_cp_qch_con_mailbox_m4_qch {
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

union cmu_cp_qch_con_nts_async_mst_qch {
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

union cmu_cp_qch_con_ts_dec0_qch {
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

union cmu_cp_qch_con_ts_dec1_qch {
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

union cmu_cp_qch_con_cti_async_mst_stm_qch {
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

union cmu_cp_qch_con_add_con_cp_qch {
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

union cmu_cp_qch_con_sysreg_buscsr_cp_qch {
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

union cmu_cp_qch_con_nts_async_ca73_qch_m {
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

union cmu_cp_qch_con_nts_async_ca73_qch_s {
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

union cmu_cp_qch_con_nts_async_stm_qch_m {
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

union cmu_cp_qch_con_nts_async_stm_qch_s {
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

union cmu_cp_qch_con_lh_cpm_ast_top_qch_si {
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

union cmu_cp_qch_con_lh_cpm_ast_top_qch_mi {
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

union cmu_cp_qch_con_lh_cps_ast_top_qch_si {
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

union cmu_cp_qch_con_lh_cps_ast_top_qch_mi {
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

union cmu_cp_qch_con_shortstop_dmyqch {
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

struct cmu_cp {
	union cmu_cp_pll_locktime_pll_cp pll_locktime_pll_cp; /* offset : 0x0 */
	union cmu_cp_pll_locktime_pll_cp_dvfs pll_locktime_pll_cp_dvfs; /* offset : 0x4 */
	uint32_t reserved_1[6];
	union cmu_cp_shortstop shortstop; /* offset : 0x20 */
	uint32_t reserved_2[55];
	union cmu_cp_pll_con0_pll_cp pll_con0_pll_cp; /* offset : 0x100 */
	union cmu_cp_pll_con1_pll_cp pll_con1_pll_cp; /* offset : 0x104 */
	union cmu_cp_pll_con2_pll_cp pll_con2_pll_cp; /* offset : 0x108 */
	union cmu_cp_pll_con3_pll_cp pll_con3_pll_cp; /* offset : 0x10c */
	union cmu_cp_pll_con4_pll_cp pll_con4_pll_cp; /* offset : 0x110 */
	union cmu_cp_pll_con0_pll_cp_dvfs pll_con0_pll_cp_dvfs; /* offset : 0x114 */
	union cmu_cp_pll_con1_pll_cp_dvfs pll_con1_pll_cp_dvfs; /* offset : 0x118 */
	union cmu_cp_pll_con2_pll_cp_dvfs pll_con2_pll_cp_dvfs; /* offset : 0x11c */
	union cmu_cp_pll_con3_pll_cp_dvfs pll_con3_pll_cp_dvfs; /* offset : 0x120 */
	union cmu_cp_pll_con4_pll_cp_dvfs pll_con4_pll_cp_dvfs; /* offset : 0x124 */
	uint32_t reserved_3[438];
	union cmu_cp_cp_cmu_cp_controller_option cp_cmu_cp_controller_option; /* offset : 0x800 */
	union cmu_cp_clkout_con_blk_cp_cmu_cp_clkout
		clkout_con_blk_cp_cmu_cp_clkout; /* offset : 0x804 */
	uint32_t reserved_4[510];
	union cmu_cp_clk_con_mux_mux_cp_pll_fout clk_con_mux_mux_cp_pll_fout; /* offset : 0x1000 */
	union cmu_cp_clk_con_mux_mux_cp_tsclk clk_con_mux_mux_cp_tsclk; /* offset : 0x1004 */
	uint32_t reserved_5[446];
	union cmu_cp_clk_con_div_div4_hch_cp_cmuref
		clk_con_div_div4_hch_cp_cmuref; /* offset : 0x1700 */
	union cmu_cp_clk_con_div_div2_hch_cp_coreclk
		clk_con_div_div2_hch_cp_coreclk; /* offset : 0x1704 */
	union cmu_cp_clk_con_div_div4_hch_cp_aclk clk_con_div_div4_hch_cp_aclk; /* offset : 0x1708 */
	union cmu_cp_clk_con_div_div8_hch_cp_pclk clk_con_div_div8_hch_cp_pclk; /* offset : 0x170c */
	union cmu_cp_clk_con_div_div8_hch_cp_stm clk_con_div_div8_hch_cp_stm; /* offset : 0x1710 */
	uint32_t reserved_6[59];
	union cmu_cp_clk_con_div_div2_cp_cmuref clk_con_div_div2_cp_cmuref; /* offset : 0x1800 */
	union cmu_cp_clk_con_div_div1_cp_coreclk clk_con_div_div1_cp_coreclk; /* offset : 0x1804 */
	union cmu_cp_clk_con_div_div2_cp_aclk clk_con_div_div2_cp_aclk; /* offset : 0x1808 */
	union cmu_cp_clk_con_div_div4_cp_pclk clk_con_div_div4_cp_pclk; /* offset : 0x180c */
	union cmu_cp_clk_con_div_div5_cp_add clk_con_div_div5_cp_add; /* offset : 0x1810 */
	union cmu_cp_clk_con_div_div4_cp_stm clk_con_div_div4_cp_stm; /* offset : 0x1814 */
	union cmu_cp_clk_con_div_div1_cp_tsclk clk_con_div_div1_cp_tsclk; /* offset : 0x1818 */
	uint32_t reserved_7[505];
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_cp_cmu_cp_ipclkport_pclk
		clk_con_gat_clk_blk_cp_uid_cp_cmu_cp_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_cp_clk_con_gat_shortstop_cp clk_con_gat_shortstop_cp; /* offset : 0x2004 */
	union cmu_cp_clk_con_gat_gate_cp clk_con_gat_gate_cp; /* offset : 0x2008 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x200c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_cp_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2010 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_d_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cps_d_mi_ipclkport_i_clk; /* offset : 0x2014 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_d_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_d_si_ipclkport_i_clk; /* offset : 0x2018 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cps_p_mi_ipclkport_i_clk; /* offset : 0x201c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t0_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_t0_si_ipclkport_i_clk; /* offset : 0x2020 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t1_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_t1_si_ipclkport_i_clk; /* offset : 0x2024 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t2_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_t2_si_ipclkport_i_clk; /* offset : 0x2028 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t3_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_t3_si_ipclkport_i_clk; /* offset : 0x202c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_t4_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_t4_si_ipclkport_i_clk; /* offset : 0x2030 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_si_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_si_ipclkport_i_clk; /* offset : 0x2034 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_lh_cps_ast_mi_ipclkport_i_clk; /* offset : 0x2038 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_apb_cps_g0_mi_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_apb_cps_g0_mi_ipclkport_clk_m; /* offset : 0x203c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_apb_cps_g1_mi_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_apb_cps_g1_mi_ipclkport_clk_m; /* offset : 0x2040 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sysreg_cp_ipclkport_pclk
		clk_con_gat_clk_blk_cp_uid_sysreg_cp_ipclkport_pclk; /* offset : 0x2044 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk
		clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk; /* offset : 0x2048 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk_r
		clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_ackclk_r; /* offset : 0x204c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_stmckclk
		clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_stmckclk; /* offset : 0x2050 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk
		clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk; /* offset : 0x2054 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk_r
		clk_con_gat_clk_blk_cp_uid_nic_cp_ipclkport_pckclk_r; /* offset : 0x2058 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_bisr_ctrlr_clk
		clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_bisr_ctrlr_clk; /* offset : 0x205c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_artemis4_ipclkport_clk; /* offset : 0x2060 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_cntvalue_g2b_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_cntvalue_g2b_ipclkport_clk; /* offset : 0x2064 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_mailbox_m3_ipclkport_pclk
		clk_con_gat_clk_blk_cp_uid_mailbox_m3_ipclkport_pclk; /* offset : 0x2068 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_mailbox_m4_ipclkport_pclk
		clk_con_gat_clk_blk_cp_uid_mailbox_m4_ipclkport_pclk; /* offset : 0x206c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_mst_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_nts_async_mst_ipclkport_clk_m; /* offset : 0x2070 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_replicator_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_ts_replicator_ipclkport_clk; /* offset : 0x2074 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_dec0_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_ts_dec0_ipclkport_clk; /* offset : 0x2078 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_ts_dec1_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_ts_dec1_ipclkport_clk; /* offset : 0x207c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_cti_async_mst_stm_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_cti_async_mst_stm_ipclkport_clk_m; /* offset : 0x2080 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_cti_async_slv_stm_ipclkport_clk_s
		clk_con_gat_clk_blk_cp_uid_cti_async_slv_stm_ipclkport_clk_s; /* offset : 0x2084 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_stm_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_stm_ipclkport_clk; /* offset : 0x2088 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_ch_clk
		clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_ch_clk; /* offset : 0x208c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk_tm
		clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk_tm; /* offset : 0x2090 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_add_cp_ipclkport_clk; /* offset : 0x2094 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_pclk
		clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_pclk; /* offset : 0x2098 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_clk
		clk_con_gat_clk_blk_cp_uid_add_con_cp_ipclkport_i_clk; /* offset : 0x209c */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_dbgen_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_sync_dbgen_ipclkport_clk; /* offset : 0x20a0 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_niden_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_sync_niden_ipclkport_clk; /* offset : 0x20a4 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_spiden_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_sync_spiden_ipclkport_clk; /* offset : 0x20a8 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sync_spniden_ipclkport_clk
		clk_con_gat_clk_blk_cp_uid_sync_spniden_ipclkport_clk; /* offset : 0x20ac */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_sysreg_buscsr_cp_ipclkport_pclk
		clk_con_gat_clk_blk_cp_uid_sysreg_buscsr_cp_ipclkport_pclk; /* offset : 0x20b0 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_amba_ovrd_ace_ipclkport_i_aclk
		clk_con_gat_clk_blk_cp_uid_amba_ovrd_ace_ipclkport_i_aclk; /* offset : 0x20b4 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_amba_ovrd_acp_ipclkport_i_aclk
		clk_con_gat_clk_blk_cp_uid_amba_ovrd_acp_ipclkport_i_aclk; /* offset : 0x20b8 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_m; /* offset : 0x20bc */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_s
		clk_con_gat_clk_blk_cp_uid_nts_async_ca73_ipclkport_clk_s; /* offset : 0x20c0 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_m
		clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_m; /* offset : 0x20c4 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_s
		clk_con_gat_clk_blk_cp_uid_nts_async_stm_ipclkport_clk_s; /* offset : 0x20c8 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_si
		clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_si; /* offset : 0x20cc */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_mi
		clk_con_gat_clk_blk_cp_uid_lh_cpm_ast_top_ipclkport_i_clk_mi; /* offset : 0x20d0 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_mi
		clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_mi; /* offset : 0x20d4 */
	union cmu_cp_clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_si
		clk_con_gat_clk_blk_cp_uid_lh_cps_ast_top_ipclkport_i_clk_si; /* offset : 0x20d8 */
	uint32_t reserved_8[969];
	union cmu_cp_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3000 */
	union cmu_cp_qch_con_axi2apb_cp_qch qch_con_axi2apb_cp_qch; /* offset : 0x3004 */
	union cmu_cp_qch_con_nic_cp_dmyqch qch_con_nic_cp_dmyqch; /* offset : 0x3008 */
	union cmu_cp_qch_con_artemis4_dmyqch qch_con_artemis4_dmyqch; /* offset : 0x300c */
	union cmu_cp_qch_con_artemis4_qch qch_con_artemis4_qch; /* offset : 0x3010 */
	union cmu_cp_qch_con_cntvalue_g2b_dmyqch qch_con_cntvalue_g2b_dmyqch; /* offset : 0x3014 */
	union cmu_cp_qch_con_ts_replicator_dmyqch qch_con_ts_replicator_dmyqch; /* offset : 0x3018 */
	union cmu_cp_qch_con_cti_async_slv_stm_dmyqch
		qch_con_cti_async_slv_stm_dmyqch; /* offset : 0x301c */
	union cmu_cp_qch_con_stm_dmyqch qch_con_stm_dmyqch; /* offset : 0x3020 */
	union cmu_cp_qch_con_add_cp_dmyqch qch_con_add_cp_dmyqch; /* offset : 0x3024 */
	union cmu_cp_qch_con_add_con_cp_dmyqch qch_con_add_con_cp_dmyqch; /* offset : 0x3028 */
	union cmu_cp_qch_con_sync_dbgen_dmyqch qch_con_sync_dbgen_dmyqch; /* offset : 0x302c */
	union cmu_cp_qch_con_sync_niden_dmyqch qch_con_sync_niden_dmyqch; /* offset : 0x3030 */
	union cmu_cp_qch_con_sync_spiden_dmyqch qch_con_sync_spiden_dmyqch; /* offset : 0x3034 */
	union cmu_cp_qch_con_sync_spniden_dmyqch qch_con_sync_spniden_dmyqch; /* offset : 0x3038 */
	union cmu_cp_qch_con_rstnsync_coreclk_dmyqch
		qch_con_rstnsync_coreclk_dmyqch; /* offset : 0x303c */
	union cmu_cp_qch_con_rstnsync_aclk_dmyqch qch_con_rstnsync_aclk_dmyqch; /* offset : 0x3040 */
	union cmu_cp_qch_con_rstnsync_pclk_dmyqch qch_con_rstnsync_pclk_dmyqch; /* offset : 0x3044 */
	union cmu_cp_qch_con_rstnsync_stm_dmyqch qch_con_rstnsync_stm_dmyqch; /* offset : 0x3048 */
	union cmu_cp_qch_con_rstnsync_tsclk_dmyqch qch_con_rstnsync_tsclk_dmyqch; /* offset : 0x304c */
	union cmu_cp_qch_con_amba_ovrd_ace_dmyqch qch_con_amba_ovrd_ace_dmyqch; /* offset : 0x3050 */
	union cmu_cp_qch_con_amba_ovrd_acp_dmyqch qch_con_amba_ovrd_acp_dmyqch; /* offset : 0x3054 */
	union cmu_cp_qch_con_lh_cps_d_mi_pch qch_con_lh_cps_d_mi_pch; /* offset : 0x3058 */
	union cmu_cp_qch_con_lh_cpm_d_si_pch qch_con_lh_cpm_d_si_pch; /* offset : 0x305c */
	union cmu_cp_qch_con_lh_cps_p_mi_pch qch_con_lh_cps_p_mi_pch; /* offset : 0x3060 */
	union cmu_cp_qch_con_lh_cpm_t0_si_pch qch_con_lh_cpm_t0_si_pch; /* offset : 0x3064 */
	union cmu_cp_qch_con_lh_cpm_t1_si_pch qch_con_lh_cpm_t1_si_pch; /* offset : 0x3068 */
	union cmu_cp_qch_con_lh_cpm_t2_si_pch qch_con_lh_cpm_t2_si_pch; /* offset : 0x306c */
	union cmu_cp_qch_con_lh_cpm_t3_si_pch qch_con_lh_cpm_t3_si_pch; /* offset : 0x3070 */
	union cmu_cp_qch_con_lh_cpm_t4_si_pch qch_con_lh_cpm_t4_si_pch; /* offset : 0x3074 */
	union cmu_cp_qch_con_lh_cpm_ast_si_pch qch_con_lh_cpm_ast_si_pch; /* offset : 0x3078 */
	union cmu_cp_qch_con_lh_cps_ast_mi_pch qch_con_lh_cps_ast_mi_pch; /* offset : 0x307c */
	union cmu_cp_qch_con_lh_cpm_ast_top_pch_si qch_con_lh_cpm_ast_top_pch_si; /* offset : 0x3080 */
	union cmu_cp_qch_con_lh_cpm_ast_top_pch_mi qch_con_lh_cpm_ast_top_pch_mi; /* offset : 0x3084 */
	union cmu_cp_qch_con_lh_cps_ast_top_pch_si qch_con_lh_cps_ast_top_pch_si; /* offset : 0x3088 */
	union cmu_cp_qch_con_lh_cps_ast_top_pch_mi qch_con_lh_cps_ast_top_pch_mi; /* offset : 0x308c */
	union cmu_cp_qch_con_cp_cmu_cp_qch qch_con_cp_cmu_cp_qch; /* offset : 0x3090 */
	union cmu_cp_qch_con_lh_cps_d_mi_qch qch_con_lh_cps_d_mi_qch; /* offset : 0x3094 */
	union cmu_cp_qch_con_lh_cpm_d_si_qch qch_con_lh_cpm_d_si_qch; /* offset : 0x3098 */
	union cmu_cp_qch_con_lh_cps_p_mi_qch qch_con_lh_cps_p_mi_qch; /* offset : 0x309c */
	union cmu_cp_qch_con_lh_cpm_t0_si_qch qch_con_lh_cpm_t0_si_qch; /* offset : 0x30a0 */
	union cmu_cp_qch_con_lh_cpm_t1_si_qch qch_con_lh_cpm_t1_si_qch; /* offset : 0x30a4 */
	union cmu_cp_qch_con_lh_cpm_t2_si_qch qch_con_lh_cpm_t2_si_qch; /* offset : 0x30a8 */
	union cmu_cp_qch_con_lh_cpm_t3_si_qch qch_con_lh_cpm_t3_si_qch; /* offset : 0x30ac */
	union cmu_cp_qch_con_lh_cpm_t4_si_qch qch_con_lh_cpm_t4_si_qch; /* offset : 0x30b0 */
	union cmu_cp_qch_con_lh_cpm_ast_si_qch qch_con_lh_cpm_ast_si_qch; /* offset : 0x30b4 */
	union cmu_cp_qch_con_lh_cps_ast_mi_qch qch_con_lh_cps_ast_mi_qch; /* offset : 0x30b8 */
	union cmu_cp_qch_con_apb_cps_g0_mi_qch qch_con_apb_cps_g0_mi_qch; /* offset : 0x30bc */
	union cmu_cp_qch_con_apb_cps_g1_mi_qch qch_con_apb_cps_g1_mi_qch; /* offset : 0x30c0 */
	union cmu_cp_qch_con_sysreg_cp_qch qch_con_sysreg_cp_qch; /* offset : 0x30c4 */
	union cmu_cp_qch_con_mailbox_m3_qch qch_con_mailbox_m3_qch; /* offset : 0x30c8 */
	union cmu_cp_qch_con_mailbox_m4_qch qch_con_mailbox_m4_qch; /* offset : 0x30cc */
	union cmu_cp_qch_con_nts_async_mst_qch qch_con_nts_async_mst_qch; /* offset : 0x30d0 */
	union cmu_cp_qch_con_ts_dec0_qch qch_con_ts_dec0_qch; /* offset : 0x30d4 */
	union cmu_cp_qch_con_ts_dec1_qch qch_con_ts_dec1_qch; /* offset : 0x30d8 */
	union cmu_cp_qch_con_cti_async_mst_stm_qch qch_con_cti_async_mst_stm_qch; /* offset : 0x30dc */
	union cmu_cp_qch_con_add_con_cp_qch qch_con_add_con_cp_qch; /* offset : 0x30e0 */
	union cmu_cp_qch_con_sysreg_buscsr_cp_qch qch_con_sysreg_buscsr_cp_qch; /* offset : 0x30e4 */
	union cmu_cp_qch_con_nts_async_ca73_qch_m qch_con_nts_async_ca73_qch_m; /* offset : 0x30e8 */
	union cmu_cp_qch_con_nts_async_ca73_qch_s qch_con_nts_async_ca73_qch_s; /* offset : 0x30ec */
	union cmu_cp_qch_con_nts_async_stm_qch_m qch_con_nts_async_stm_qch_m; /* offset : 0x30f0 */
	union cmu_cp_qch_con_nts_async_stm_qch_s qch_con_nts_async_stm_qch_s; /* offset : 0x30f4 */
	union cmu_cp_qch_con_lh_cpm_ast_top_qch_si qch_con_lh_cpm_ast_top_qch_si; /* offset : 0x30f8 */
	union cmu_cp_qch_con_lh_cpm_ast_top_qch_mi qch_con_lh_cpm_ast_top_qch_mi; /* offset : 0x30fc */
	union cmu_cp_qch_con_lh_cps_ast_top_qch_si qch_con_lh_cps_ast_top_qch_si; /* offset : 0x3100 */
	union cmu_cp_qch_con_lh_cps_ast_top_qch_mi qch_con_lh_cps_ast_top_qch_mi; /* offset : 0x3104 */
	union cmu_cp_qch_con_shortstop_dmyqch qch_con_shortstop_dmyqch; /* offset : 0x3108 */
};

enum CP_CLK_OUT {
	OSCCLK_CP,
	PLL_CP,
	PLL_CP_DVFS,
	CLK_CP_CORECLK,
	CLK_CP_ACLK,
	CLK_CP_PCLK,
	CLK_CP_ADD,
	CLK_CP_STM,
	CLK_CP_TSCLK,
	CLK_CP_CMUREF,
	CP_CLK_LH_SCAN_DST,
	CP_CLK_LH_SCAN_ETC,
};
