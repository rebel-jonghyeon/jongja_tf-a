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

union cmu_dcl_pll_locktime_pll_dcl {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dcl_pll_locktime_pll_dcl_dvfs {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dcl_shortstop {
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

union cmu_dcl_pll_con0_pll_dcl {
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

union cmu_dcl_pll_con1_pll_dcl {
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

union cmu_dcl_pll_con2_pll_dcl {
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

union cmu_dcl_pll_con3_pll_dcl {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dcl_pll_con4_pll_dcl {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_pll_con0_pll_dcl_dvfs {
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

union cmu_dcl_pll_con1_pll_dcl_dvfs {
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

union cmu_dcl_pll_con2_pll_dcl_dvfs {
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

union cmu_dcl_pll_con3_pll_dcl_dvfs {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dcl_pll_con4_pll_dcl_dvfs {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_dcl_cmu_dcl_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clkout_con_blk_dcl_cmu_dcl_clkout {
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

union cmu_dcl_clk_con_mux_mux_dcl_pll_fout {
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

union cmu_dcl_clk_con_div_div4_hch_dcl_cmuref {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk0 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk1 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk2 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk3 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk4 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk5 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div8_hch_dcl_pclk {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div4_hch_dcl_add {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue0 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue1 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue2 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue3 {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_sglue {
	struct {
		uint32_t divratio:4; /* [3:0] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t therm_dfs:1; /* [16:16] */
		uint32_t reserved1:14; /* [30:17] */
		uint32_t enable:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_div_div_dcl_aclk0 {
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

union cmu_dcl_clk_con_div_div4_dcl_pclk {
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

union cmu_dcl_clk_con_div_div_dcl_aclk1 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk2 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk3 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk4 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk5 {
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

union cmu_dcl_clk_con_div_div2_dcl_cmuref {
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

union cmu_dcl_clk_con_div_div5_dcl_oscclk {
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

union cmu_dcl_clk_con_div_div2_dcl_add {
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

union cmu_dcl_clk_con_div_div9_dcl_pvt {
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

union cmu_dcl_clk_con_div_div_dcl_aclk_dglue0 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk_dglue1 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk_dglue2 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk_dglue3 {
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

union cmu_dcl_clk_con_div_div_dcl_aclk_sglue {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_cmu_dcl_ipclkport_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk5 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0_g {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1_g {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3_g {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4_g {
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

union cmu_dcl_clk_con_gat_shortstop_dcl {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_dcl_clk_con_gat_clkgate0 {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2_g {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_dst {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_etc {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_dst {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_etc {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_dst {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_etc {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_dst {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_etc {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_dst {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_etc {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclns_p_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_mp_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp0_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp1_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp2_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp3_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sp_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_r {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_w {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sc_si_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sc_mi_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp2_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp3_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd2_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd3_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd2_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd3_ipclkport_aclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_sysreg_dcl_ipclkport_pclk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0_dcl_ipclkport_ch_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1_dcl_ipclkport_ch_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2_dcl_ipclkport_ch_clk {
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

union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3_dcl_ipclkport_ch_clk {
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

union cmu_dcl_qch_con_dcl_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk0_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk1_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk2_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk3_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk4_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk5_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg0_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg1_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg2_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg3_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_aclk_sg_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_pvtclk_qch {
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

union cmu_dcl_qch_con_rstnsync_dcl_addclk_qch {
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

union cmu_dcl_qch_con_mglue_idle_sync_qch {
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

union cmu_dcl_qch_con_lh_dglue0_qch {
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

union cmu_dcl_qch_con_lh_dglue1_qch {
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

union cmu_dcl_qch_con_lh_dglue2_qch {
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

union cmu_dcl_qch_con_lh_dglue3_qch {
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

union cmu_dcl_qch_con_lh_sglue_qch {
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

union cmu_dcl_qch_con_axi_rs_dcls_dp2_qch {
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

union cmu_dcl_qch_con_axi_rs_dcls_dp3_qch {
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

union cmu_dcl_qch_con_axi_rs_dclm_dd2_qch {
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

union cmu_dcl_qch_con_axi_rs_dclm_dd3_qch {
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

union cmu_dcl_qch_con_axi_rs_dcls_dd2_qch {
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

union cmu_dcl_qch_con_axi_rs_dcls_dd3_qch {
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

union cmu_dcl_qch_con_axi2apb_dcl_qch {
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

union cmu_dcl_qch_con_pvt0ctrl_dcl_qch {
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

union cmu_dcl_qch_con_pvt1ctrl_dcl_qch {
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

union cmu_dcl_qch_con_add0_dcl_qch {
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

union cmu_dcl_qch_con_add1_dcl_qch {
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

union cmu_dcl_qch_con_add2_dcl_qch {
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

union cmu_dcl_qch_con_add3_dcl_qch {
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

union cmu_dcl_qch_con_lh_dclns_p_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_mp_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp0_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp1_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp2_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp3_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_sp_mi_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dclm_dd0_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd0_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd1_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd1_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd2_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd2_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd3_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd3_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd0_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd0_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd1_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd1_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd2_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd2_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd3_si_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd3_si_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd0_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd0_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd1_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd1_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd2_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd2_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd3_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd3_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd0_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd0_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd1_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd1_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd2_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd2_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd3_mi_pch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd3_mi_pch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sc_si_pch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_sc_mi_pch_s_lh {
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

union cmu_dcl_qch_con_dcl_cmu_dcl_qch {
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

union cmu_dcl_qch_con_lh_dclns_p_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_mp_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp0_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp1_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp2_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_dp3_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_sp_mi_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dclm_dd0_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd0_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd1_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd1_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd2_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd2_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_dd3_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_dd3_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd0_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd0_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd1_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd1_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd2_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd2_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sd3_si_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dclm_sd3_si_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd0_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd0_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd1_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd1_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd2_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd2_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_dd3_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_dd3_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd0_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd0_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd1_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd1_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd2_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd2_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dcls_sd3_mi_qch_s_lh_r {
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

union cmu_dcl_qch_con_lh_dcls_sd3_mi_qch_s_lh_w {
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

union cmu_dcl_qch_con_lh_dclm_sc_si_qch_s_lh {
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

union cmu_dcl_qch_con_lh_dcls_sc_mi_qch_s_lh {
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

union cmu_dcl_qch_con_add0ctrl_dcl_qch {
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

union cmu_dcl_qch_con_add1ctrl_dcl_qch {
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

union cmu_dcl_qch_con_add2ctrl_dcl_qch {
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

union cmu_dcl_qch_con_add3ctrl_dcl_qch {
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

union cmu_dcl_qch_con_sysreg_dcl_qch {
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

union cmu_dcl_qch_con_shortstop_qch {
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

struct cmu_dcl {
	union cmu_dcl_pll_locktime_pll_dcl pll_locktime_pll_dcl; /* offset : 0x0 */
	union cmu_dcl_pll_locktime_pll_dcl_dvfs pll_locktime_pll_dcl_dvfs; /* offset : 0x4 */
	uint32_t reserved_1[6];
	union cmu_dcl_shortstop shortstop; /* offset : 0x20 */
	uint32_t reserved_2[55];
	union cmu_dcl_pll_con0_pll_dcl pll_con0_pll_dcl; /* offset : 0x100 */
	union cmu_dcl_pll_con1_pll_dcl pll_con1_pll_dcl; /* offset : 0x104 */
	union cmu_dcl_pll_con2_pll_dcl pll_con2_pll_dcl; /* offset : 0x108 */
	union cmu_dcl_pll_con3_pll_dcl pll_con3_pll_dcl; /* offset : 0x10c */
	union cmu_dcl_pll_con4_pll_dcl pll_con4_pll_dcl; /* offset : 0x110 */
	union cmu_dcl_pll_con0_pll_dcl_dvfs pll_con0_pll_dcl_dvfs; /* offset : 0x114 */
	union cmu_dcl_pll_con1_pll_dcl_dvfs pll_con1_pll_dcl_dvfs; /* offset : 0x118 */
	union cmu_dcl_pll_con2_pll_dcl_dvfs pll_con2_pll_dcl_dvfs; /* offset : 0x11c */
	union cmu_dcl_pll_con3_pll_dcl_dvfs pll_con3_pll_dcl_dvfs; /* offset : 0x120 */
	union cmu_dcl_pll_con4_pll_dcl_dvfs pll_con4_pll_dcl_dvfs; /* offset : 0x124 */
	uint32_t reserved_3[438];
	union cmu_dcl_dcl_cmu_dcl_controller_option dcl_cmu_dcl_controller_option; /* offset : 0x800 */
	union cmu_dcl_clkout_con_blk_dcl_cmu_dcl_clkout
			clkout_con_blk_dcl_cmu_dcl_clkout; /* offset : 0x804 */
	uint32_t reserved_4[510];
	union cmu_dcl_clk_con_mux_mux_dcl_pll_fout clk_con_mux_mux_dcl_pll_fout; /* offset : 0x1000 */
	uint32_t reserved_5[447];
	union cmu_dcl_clk_con_div_div4_hch_dcl_cmuref
			clk_con_div_div4_hch_dcl_cmuref; /* offset : 0x1700 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk0
			clk_con_div_div2_hch_dcl_aclk0; /* offset : 0x1704 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk1
			clk_con_div_div2_hch_dcl_aclk1; /* offset : 0x1708 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk2
			clk_con_div_div2_hch_dcl_aclk2; /* offset : 0x170c */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk3
			clk_con_div_div2_hch_dcl_aclk3; /* offset : 0x1710 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk4
			clk_con_div_div2_hch_dcl_aclk4; /* offset : 0x1714 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk5
			clk_con_div_div2_hch_dcl_aclk5; /* offset : 0x1718 */
	union cmu_dcl_clk_con_div_div8_hch_dcl_pclk
			clk_con_div_div8_hch_dcl_pclk; /* offset : 0x171c */
	union cmu_dcl_clk_con_div_div4_hch_dcl_add clk_con_div_div4_hch_dcl_add; /* offset : 0x1720 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue0
			clk_con_div_div2_hch_dcl_aclk_dglue0; /* offset : 0x1724 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue1
			clk_con_div_div2_hch_dcl_aclk_dglue1; /* offset : 0x1728 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue2
			clk_con_div_div2_hch_dcl_aclk_dglue2; /* offset : 0x172c */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_dglue3
			clk_con_div_div2_hch_dcl_aclk_dglue3; /* offset : 0x1730 */
	union cmu_dcl_clk_con_div_div2_hch_dcl_aclk_sglue
			clk_con_div_div2_hch_dcl_aclk_sglue; /* offset : 0x1734 */
	uint32_t reserved_6[50];
	union cmu_dcl_clk_con_div_div_dcl_aclk0 clk_con_div_div_dcl_aclk0; /* offset : 0x1800 */
	union cmu_dcl_clk_con_div_div4_dcl_pclk clk_con_div_div4_dcl_pclk; /* offset : 0x1804 */
	union cmu_dcl_clk_con_div_div_dcl_aclk1 clk_con_div_div_dcl_aclk1; /* offset : 0x1808 */
	union cmu_dcl_clk_con_div_div_dcl_aclk2 clk_con_div_div_dcl_aclk2; /* offset : 0x180c */
	union cmu_dcl_clk_con_div_div_dcl_aclk3 clk_con_div_div_dcl_aclk3; /* offset : 0x1810 */
	union cmu_dcl_clk_con_div_div_dcl_aclk4 clk_con_div_div_dcl_aclk4; /* offset : 0x1814 */
	union cmu_dcl_clk_con_div_div_dcl_aclk5 clk_con_div_div_dcl_aclk5; /* offset : 0x1818 */
	union cmu_dcl_clk_con_div_div2_dcl_cmuref clk_con_div_div2_dcl_cmuref; /* offset : 0x181c */
	union cmu_dcl_clk_con_div_div5_dcl_oscclk clk_con_div_div5_dcl_oscclk; /* offset : 0x1820 */
	union cmu_dcl_clk_con_div_div2_dcl_add clk_con_div_div2_dcl_add; /* offset : 0x1824 */
	union cmu_dcl_clk_con_div_div9_dcl_pvt clk_con_div_div9_dcl_pvt; /* offset : 0x1828 */
	union cmu_dcl_clk_con_div_div_dcl_aclk_dglue0
			clk_con_div_div_dcl_aclk_dglue0; /* offset : 0x182c */
	union cmu_dcl_clk_con_div_div_dcl_aclk_dglue1
			clk_con_div_div_dcl_aclk_dglue1; /* offset : 0x1830 */
	union cmu_dcl_clk_con_div_div_dcl_aclk_dglue2
			clk_con_div_div_dcl_aclk_dglue2; /* offset : 0x1834 */
	union cmu_dcl_clk_con_div_div_dcl_aclk_dglue3
			clk_con_div_div_dcl_aclk_dglue3; /* offset : 0x1838 */
	union cmu_dcl_clk_con_div_div_dcl_aclk_sglue
			clk_con_div_div_dcl_aclk_sglue; /* offset : 0x183c */
	uint32_t reserved_7[496];
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_cmu_dcl_ipclkport_pclk
			clk_con_gat_clk_blk_dcl_uid_dcl_cmu_dcl_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0; /* offset : 0x2004 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1; /* offset : 0x2008 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2; /* offset : 0x200c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3; /* offset : 0x2010 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4; /* offset : 0x2014 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk5
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk5; /* offset : 0x2018 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0_g
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk0_g; /* offset : 0x201c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1_g
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk1_g; /* offset : 0x2020 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3_g
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk3_g; /* offset : 0x2024 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4_g
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk4_g; /* offset : 0x2028 */
	union cmu_dcl_clk_con_gat_shortstop_dcl clk_con_gat_shortstop_dcl; /* offset : 0x202c */
	union cmu_dcl_clk_con_gat_clkgate0 clk_con_gat_clkgate0; /* offset : 0x2030 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2_g
			clk_con_gat_clk_blk_dcl_uid_dcl_ipclkport_i_clk2_g; /* offset : 0x2034 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_dst; /* offset : 0x2038 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_dcl_uid_lh_dglue0_ipclkport_i_scan_clk_etc; /* offset : 0x203c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_dst; /* offset : 0x2040 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_dcl_uid_lh_dglue1_ipclkport_i_scan_clk_etc; /* offset : 0x2044 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_dst; /* offset : 0x2048 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_dcl_uid_lh_dglue2_ipclkport_i_scan_clk_etc; /* offset : 0x204c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_dst; /* offset : 0x2050 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_dcl_uid_lh_dglue3_ipclkport_i_scan_clk_etc; /* offset : 0x2054 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_dst; /* offset : 0x2058 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_dcl_uid_lh_sglue_ipclkport_i_scan_clk_etc; /* offset : 0x205c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclns_p_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dclns_p_mi_ipclkport_i_clk; /* offset : 0x2060 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_mp_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_mp_mi_ipclkport_i_clk; /* offset : 0x2064 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp0_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp0_mi_ipclkport_i_clk; /* offset : 0x2068 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp1_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp1_mi_ipclkport_i_clk; /* offset : 0x206c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp2_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp2_mi_ipclkport_i_clk; /* offset : 0x2070 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp3_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dp3_mi_ipclkport_i_clk; /* offset : 0x2074 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sp_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sp_mi_ipclkport_i_clk; /* offset : 0x2078 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_r; /* offset : 0x207c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd0_si_ipclkport_i_clk_w; /* offset : 0x2080 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_r; /* offset : 0x2084 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd1_si_ipclkport_i_clk_w; /* offset : 0x2088 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_r; /* offset : 0x208c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd2_si_ipclkport_i_clk_w; /* offset : 0x2090 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_r; /* offset : 0x2094 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_dd3_si_ipclkport_i_clk_w; /* offset : 0x2098 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_r; /* offset : 0x209c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd0_si_ipclkport_i_clk_w; /* offset : 0x20a0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_r; /* offset : 0x20a4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd1_si_ipclkport_i_clk_w; /* offset : 0x20a8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_r; /* offset : 0x20ac */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd2_si_ipclkport_i_clk_w; /* offset : 0x20b0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_r; /* offset : 0x20b4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sd3_si_ipclkport_i_clk_w; /* offset : 0x20b8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_r; /* offset : 0x20bc */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd0_mi_ipclkport_i_clk_w; /* offset : 0x20c0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_r; /* offset : 0x20c4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd1_mi_ipclkport_i_clk_w; /* offset : 0x20c8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_r; /* offset : 0x20cc */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd2_mi_ipclkport_i_clk_w; /* offset : 0x20d0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_r; /* offset : 0x20d4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_dd3_mi_ipclkport_i_clk_w; /* offset : 0x20d8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_r; /* offset : 0x20dc */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd0_mi_ipclkport_i_clk_w; /* offset : 0x20e0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_r; /* offset : 0x20e4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd1_mi_ipclkport_i_clk_w; /* offset : 0x20e8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_r; /* offset : 0x20ec */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd2_mi_ipclkport_i_clk_w; /* offset : 0x20f0 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_r
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_r; /* offset : 0x20f4 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_w
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sd3_mi_ipclkport_i_clk_w; /* offset : 0x20f8 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dclm_sc_si_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dclm_sc_si_ipclkport_i_clk; /* offset : 0x20fc */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_lh_dcls_sc_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_lh_dcls_sc_mi_ipclkport_i_clk; /* offset : 0x2100 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp2_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp2_ipclkport_aclk; /* offset : 0x2104 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp3_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dp3_ipclkport_aclk; /* offset : 0x2108 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd2_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd2_ipclkport_aclk; /* offset : 0x210c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd3_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dclm_dd3_ipclkport_aclk; /* offset : 0x2110 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd2_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd2_ipclkport_aclk; /* offset : 0x2114 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd3_ipclkport_aclk
			clk_con_gat_clk_blk_dcl_uid_axi_rs_dcls_dd3_ipclkport_aclk; /* offset : 0x2118 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_pclk
			clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_pclk; /* offset : 0x211c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_clk
			clk_con_gat_clk_blk_dcl_uid_pvt0ctrl_dcl_ipclkport_clk; /* offset : 0x2120 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_pclk
			clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_pclk; /* offset : 0x2124 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_clk
			clk_con_gat_clk_blk_dcl_uid_pvt1ctrl_dcl_ipclkport_clk; /* offset : 0x2128 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_pclk
			clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_pclk; /* offset : 0x212c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_add0ctrl_dcl_ipclkport_i_clk; /* offset : 0x2130 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_pclk
			clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_pclk; /* offset : 0x2134 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_add1ctrl_dcl_ipclkport_i_clk; /* offset : 0x2138 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_pclk
			clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_pclk; /* offset : 0x213c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_add2ctrl_dcl_ipclkport_i_clk; /* offset : 0x2140 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_pclk
			clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_pclk; /* offset : 0x2144 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_clk
			clk_con_gat_clk_blk_dcl_uid_add3ctrl_dcl_ipclkport_i_clk; /* offset : 0x2148 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_sysreg_dcl_ipclkport_pclk
			clk_con_gat_clk_blk_dcl_uid_sysreg_dcl_ipclkport_pclk; /* offset : 0x214c */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add0_dcl_ipclkport_ch_clk
			clk_con_gat_clk_blk_dcl_uid_add0_dcl_ipclkport_ch_clk; /* offset : 0x2150 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add1_dcl_ipclkport_ch_clk
			clk_con_gat_clk_blk_dcl_uid_add1_dcl_ipclkport_ch_clk; /* offset : 0x2154 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add2_dcl_ipclkport_ch_clk
			clk_con_gat_clk_blk_dcl_uid_add2_dcl_ipclkport_ch_clk; /* offset : 0x2158 */
	union cmu_dcl_clk_con_gat_clk_blk_dcl_uid_add3_dcl_ipclkport_ch_clk
			clk_con_gat_clk_blk_dcl_uid_add3_dcl_ipclkport_ch_clk; /* offset : 0x215c */
	uint32_t reserved_8[936];
	union cmu_dcl_qch_con_dcl_qch qch_con_dcl_qch; /* offset : 0x3000 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk0_qch
			qch_con_rstnsync_dcl_aclk0_qch; /* offset : 0x3004 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk1_qch
			qch_con_rstnsync_dcl_aclk1_qch; /* offset : 0x3008 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk2_qch
			qch_con_rstnsync_dcl_aclk2_qch; /* offset : 0x300c */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk3_qch
			qch_con_rstnsync_dcl_aclk3_qch; /* offset : 0x3010 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk4_qch
			qch_con_rstnsync_dcl_aclk4_qch; /* offset : 0x3014 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk5_qch
			qch_con_rstnsync_dcl_aclk5_qch; /* offset : 0x3018 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg0_qch
			qch_con_rstnsync_dcl_aclk_dg0_qch; /* offset : 0x301c */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg1_qch
			qch_con_rstnsync_dcl_aclk_dg1_qch; /* offset : 0x3020 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg2_qch
			qch_con_rstnsync_dcl_aclk_dg2_qch; /* offset : 0x3024 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk_dg3_qch
			qch_con_rstnsync_dcl_aclk_dg3_qch; /* offset : 0x3028 */
	union cmu_dcl_qch_con_rstnsync_dcl_aclk_sg_qch
			qch_con_rstnsync_dcl_aclk_sg_qch; /* offset : 0x302c */
	union cmu_dcl_qch_con_rstnsync_dcl_pvtclk_qch
			qch_con_rstnsync_dcl_pvtclk_qch; /* offset : 0x3030 */
	union cmu_dcl_qch_con_rstnsync_dcl_addclk_qch
			qch_con_rstnsync_dcl_addclk_qch; /* offset : 0x3034 */
	union cmu_dcl_qch_con_mglue_idle_sync_qch qch_con_mglue_idle_sync_qch; /* offset : 0x3038 */
	union cmu_dcl_qch_con_lh_dglue0_qch qch_con_lh_dglue0_qch; /* offset : 0x303c */
	union cmu_dcl_qch_con_lh_dglue1_qch qch_con_lh_dglue1_qch; /* offset : 0x3040 */
	union cmu_dcl_qch_con_lh_dglue2_qch qch_con_lh_dglue2_qch; /* offset : 0x3044 */
	union cmu_dcl_qch_con_lh_dglue3_qch qch_con_lh_dglue3_qch; /* offset : 0x3048 */
	union cmu_dcl_qch_con_lh_sglue_qch qch_con_lh_sglue_qch; /* offset : 0x304c */
	union cmu_dcl_qch_con_axi_rs_dcls_dp2_qch qch_con_axi_rs_dcls_dp2_qch; /* offset : 0x3050 */
	union cmu_dcl_qch_con_axi_rs_dcls_dp3_qch qch_con_axi_rs_dcls_dp3_qch; /* offset : 0x3054 */
	union cmu_dcl_qch_con_axi_rs_dclm_dd2_qch qch_con_axi_rs_dclm_dd2_qch; /* offset : 0x3058 */
	union cmu_dcl_qch_con_axi_rs_dclm_dd3_qch qch_con_axi_rs_dclm_dd3_qch; /* offset : 0x305c */
	union cmu_dcl_qch_con_axi_rs_dcls_dd2_qch qch_con_axi_rs_dcls_dd2_qch; /* offset : 0x3060 */
	union cmu_dcl_qch_con_axi_rs_dcls_dd3_qch qch_con_axi_rs_dcls_dd3_qch; /* offset : 0x3064 */
	union cmu_dcl_qch_con_axi2apb_dcl_qch qch_con_axi2apb_dcl_qch; /* offset : 0x3068 */
	union cmu_dcl_qch_con_pvt0ctrl_dcl_qch qch_con_pvt0ctrl_dcl_qch; /* offset : 0x306c */
	union cmu_dcl_qch_con_pvt1ctrl_dcl_qch qch_con_pvt1ctrl_dcl_qch; /* offset : 0x3070 */
	union cmu_dcl_qch_con_add0_dcl_qch qch_con_add0_dcl_qch; /* offset : 0x3074 */
	union cmu_dcl_qch_con_add1_dcl_qch qch_con_add1_dcl_qch; /* offset : 0x3078 */
	union cmu_dcl_qch_con_add2_dcl_qch qch_con_add2_dcl_qch; /* offset : 0x307c */
	union cmu_dcl_qch_con_add3_dcl_qch qch_con_add3_dcl_qch; /* offset : 0x3080 */
	union cmu_dcl_qch_con_lh_dclns_p_mi_pch_s_lh
			qch_con_lh_dclns_p_mi_pch_s_lh; /* offset : 0x3084 */
	union cmu_dcl_qch_con_lh_dcls_mp_mi_pch_s_lh
			qch_con_lh_dcls_mp_mi_pch_s_lh; /* offset : 0x3088 */
	union cmu_dcl_qch_con_lh_dcls_dp0_mi_pch_s_lh
			qch_con_lh_dcls_dp0_mi_pch_s_lh; /* offset : 0x308c */
	union cmu_dcl_qch_con_lh_dcls_dp1_mi_pch_s_lh
			qch_con_lh_dcls_dp1_mi_pch_s_lh; /* offset : 0x3090 */
	union cmu_dcl_qch_con_lh_dcls_dp2_mi_pch_s_lh
			qch_con_lh_dcls_dp2_mi_pch_s_lh; /* offset : 0x3094 */
	union cmu_dcl_qch_con_lh_dcls_dp3_mi_pch_s_lh
			qch_con_lh_dcls_dp3_mi_pch_s_lh; /* offset : 0x3098 */
	union cmu_dcl_qch_con_lh_dcls_sp_mi_pch_s_lh
			qch_con_lh_dcls_sp_mi_pch_s_lh; /* offset : 0x309c */
	union cmu_dcl_qch_con_lh_dclm_dd0_si_pch_s_lh_r
			qch_con_lh_dclm_dd0_si_pch_s_lh_r; /* offset : 0x30a0 */
	union cmu_dcl_qch_con_lh_dclm_dd0_si_pch_s_lh_w
			qch_con_lh_dclm_dd0_si_pch_s_lh_w; /* offset : 0x30a4 */
	union cmu_dcl_qch_con_lh_dclm_dd1_si_pch_s_lh_r
			qch_con_lh_dclm_dd1_si_pch_s_lh_r; /* offset : 0x30a8 */
	union cmu_dcl_qch_con_lh_dclm_dd1_si_pch_s_lh_w
			qch_con_lh_dclm_dd1_si_pch_s_lh_w; /* offset : 0x30ac */
	union cmu_dcl_qch_con_lh_dclm_dd2_si_pch_s_lh_r
			qch_con_lh_dclm_dd2_si_pch_s_lh_r; /* offset : 0x30b0 */
	union cmu_dcl_qch_con_lh_dclm_dd2_si_pch_s_lh_w
			qch_con_lh_dclm_dd2_si_pch_s_lh_w; /* offset : 0x30b4 */
	union cmu_dcl_qch_con_lh_dclm_dd3_si_pch_s_lh_r
			qch_con_lh_dclm_dd3_si_pch_s_lh_r; /* offset : 0x30b8 */
	union cmu_dcl_qch_con_lh_dclm_dd3_si_pch_s_lh_w
			qch_con_lh_dclm_dd3_si_pch_s_lh_w; /* offset : 0x30bc */
	union cmu_dcl_qch_con_lh_dclm_sd0_si_pch_s_lh_r
			qch_con_lh_dclm_sd0_si_pch_s_lh_r; /* offset : 0x30c0 */
	union cmu_dcl_qch_con_lh_dclm_sd0_si_pch_s_lh_w
			qch_con_lh_dclm_sd0_si_pch_s_lh_w; /* offset : 0x30c4 */
	union cmu_dcl_qch_con_lh_dclm_sd1_si_pch_s_lh_r
			qch_con_lh_dclm_sd1_si_pch_s_lh_r; /* offset : 0x30c8 */
	union cmu_dcl_qch_con_lh_dclm_sd1_si_pch_s_lh_w
			qch_con_lh_dclm_sd1_si_pch_s_lh_w; /* offset : 0x30cc */
	union cmu_dcl_qch_con_lh_dclm_sd2_si_pch_s_lh_r
			qch_con_lh_dclm_sd2_si_pch_s_lh_r; /* offset : 0x30d0 */
	union cmu_dcl_qch_con_lh_dclm_sd2_si_pch_s_lh_w
			qch_con_lh_dclm_sd2_si_pch_s_lh_w; /* offset : 0x30d4 */
	union cmu_dcl_qch_con_lh_dclm_sd3_si_pch_s_lh_r
			qch_con_lh_dclm_sd3_si_pch_s_lh_r; /* offset : 0x30d8 */
	union cmu_dcl_qch_con_lh_dclm_sd3_si_pch_s_lh_w
			qch_con_lh_dclm_sd3_si_pch_s_lh_w; /* offset : 0x30dc */
	union cmu_dcl_qch_con_lh_dcls_dd0_mi_pch_s_lh_r
			qch_con_lh_dcls_dd0_mi_pch_s_lh_r; /* offset : 0x30e0 */
	union cmu_dcl_qch_con_lh_dcls_dd0_mi_pch_s_lh_w
			qch_con_lh_dcls_dd0_mi_pch_s_lh_w; /* offset : 0x30e4 */
	union cmu_dcl_qch_con_lh_dcls_dd1_mi_pch_s_lh_r
			qch_con_lh_dcls_dd1_mi_pch_s_lh_r; /* offset : 0x30e8 */
	union cmu_dcl_qch_con_lh_dcls_dd1_mi_pch_s_lh_w
			qch_con_lh_dcls_dd1_mi_pch_s_lh_w; /* offset : 0x30ec */
	union cmu_dcl_qch_con_lh_dcls_dd2_mi_pch_s_lh_r
			qch_con_lh_dcls_dd2_mi_pch_s_lh_r; /* offset : 0x30f0 */
	union cmu_dcl_qch_con_lh_dcls_dd2_mi_pch_s_lh_w
			qch_con_lh_dcls_dd2_mi_pch_s_lh_w; /* offset : 0x30f4 */
	union cmu_dcl_qch_con_lh_dcls_dd3_mi_pch_s_lh_r
			qch_con_lh_dcls_dd3_mi_pch_s_lh_r; /* offset : 0x30f8 */
	union cmu_dcl_qch_con_lh_dcls_dd3_mi_pch_s_lh_w
			qch_con_lh_dcls_dd3_mi_pch_s_lh_w; /* offset : 0x30fc */
	union cmu_dcl_qch_con_lh_dcls_sd0_mi_pch_s_lh_r
			qch_con_lh_dcls_sd0_mi_pch_s_lh_r; /* offset : 0x3100 */
	union cmu_dcl_qch_con_lh_dcls_sd0_mi_pch_s_lh_w
			qch_con_lh_dcls_sd0_mi_pch_s_lh_w; /* offset : 0x3104 */
	union cmu_dcl_qch_con_lh_dcls_sd1_mi_pch_s_lh_r
			qch_con_lh_dcls_sd1_mi_pch_s_lh_r; /* offset : 0x3108 */
	union cmu_dcl_qch_con_lh_dcls_sd1_mi_pch_s_lh_w
			qch_con_lh_dcls_sd1_mi_pch_s_lh_w; /* offset : 0x310c */
	union cmu_dcl_qch_con_lh_dcls_sd2_mi_pch_s_lh_r
			qch_con_lh_dcls_sd2_mi_pch_s_lh_r; /* offset : 0x3110 */
	union cmu_dcl_qch_con_lh_dcls_sd2_mi_pch_s_lh_w
			qch_con_lh_dcls_sd2_mi_pch_s_lh_w; /* offset : 0x3114 */
	union cmu_dcl_qch_con_lh_dcls_sd3_mi_pch_s_lh_r
			qch_con_lh_dcls_sd3_mi_pch_s_lh_r; /* offset : 0x3118 */
	union cmu_dcl_qch_con_lh_dcls_sd3_mi_pch_s_lh_w
			qch_con_lh_dcls_sd3_mi_pch_s_lh_w; /* offset : 0x311c */
	union cmu_dcl_qch_con_lh_dclm_sc_si_pch_s_lh
			qch_con_lh_dclm_sc_si_pch_s_lh; /* offset : 0x3120 */
	union cmu_dcl_qch_con_lh_dcls_sc_mi_pch_s_lh
			qch_con_lh_dcls_sc_mi_pch_s_lh; /* offset : 0x3124 */
	union cmu_dcl_qch_con_dcl_cmu_dcl_qch qch_con_dcl_cmu_dcl_qch; /* offset : 0x3128 */
	union cmu_dcl_qch_con_lh_dclns_p_mi_qch_s_lh
			qch_con_lh_dclns_p_mi_qch_s_lh; /* offset : 0x312c */
	union cmu_dcl_qch_con_lh_dcls_mp_mi_qch_s_lh
			qch_con_lh_dcls_mp_mi_qch_s_lh; /* offset : 0x3130 */
	union cmu_dcl_qch_con_lh_dcls_dp0_mi_qch_s_lh
			qch_con_lh_dcls_dp0_mi_qch_s_lh; /* offset : 0x3134 */
	union cmu_dcl_qch_con_lh_dcls_dp1_mi_qch_s_lh
			qch_con_lh_dcls_dp1_mi_qch_s_lh; /* offset : 0x3138 */
	union cmu_dcl_qch_con_lh_dcls_dp2_mi_qch_s_lh
			qch_con_lh_dcls_dp2_mi_qch_s_lh; /* offset : 0x313c */
	union cmu_dcl_qch_con_lh_dcls_dp3_mi_qch_s_lh
			qch_con_lh_dcls_dp3_mi_qch_s_lh; /* offset : 0x3140 */
	union cmu_dcl_qch_con_lh_dcls_sp_mi_qch_s_lh
			qch_con_lh_dcls_sp_mi_qch_s_lh; /* offset : 0x3144 */
	union cmu_dcl_qch_con_lh_dclm_dd0_si_qch_s_lh_r
			qch_con_lh_dclm_dd0_si_qch_s_lh_r; /* offset : 0x3148 */
	union cmu_dcl_qch_con_lh_dclm_dd0_si_qch_s_lh_w
			qch_con_lh_dclm_dd0_si_qch_s_lh_w; /* offset : 0x314c */
	union cmu_dcl_qch_con_lh_dclm_dd1_si_qch_s_lh_r
			qch_con_lh_dclm_dd1_si_qch_s_lh_r; /* offset : 0x3150 */
	union cmu_dcl_qch_con_lh_dclm_dd1_si_qch_s_lh_w
			qch_con_lh_dclm_dd1_si_qch_s_lh_w; /* offset : 0x3154 */
	union cmu_dcl_qch_con_lh_dclm_dd2_si_qch_s_lh_r
			qch_con_lh_dclm_dd2_si_qch_s_lh_r; /* offset : 0x3158 */
	union cmu_dcl_qch_con_lh_dclm_dd2_si_qch_s_lh_w
			qch_con_lh_dclm_dd2_si_qch_s_lh_w; /* offset : 0x315c */
	union cmu_dcl_qch_con_lh_dclm_dd3_si_qch_s_lh_r
			qch_con_lh_dclm_dd3_si_qch_s_lh_r; /* offset : 0x3160 */
	union cmu_dcl_qch_con_lh_dclm_dd3_si_qch_s_lh_w
			qch_con_lh_dclm_dd3_si_qch_s_lh_w; /* offset : 0x3164 */
	union cmu_dcl_qch_con_lh_dclm_sd0_si_qch_s_lh_r
			qch_con_lh_dclm_sd0_si_qch_s_lh_r; /* offset : 0x3168 */
	union cmu_dcl_qch_con_lh_dclm_sd0_si_qch_s_lh_w
			qch_con_lh_dclm_sd0_si_qch_s_lh_w; /* offset : 0x316c */
	union cmu_dcl_qch_con_lh_dclm_sd1_si_qch_s_lh_r
			qch_con_lh_dclm_sd1_si_qch_s_lh_r; /* offset : 0x3170 */
	union cmu_dcl_qch_con_lh_dclm_sd1_si_qch_s_lh_w
			qch_con_lh_dclm_sd1_si_qch_s_lh_w; /* offset : 0x3174 */
	union cmu_dcl_qch_con_lh_dclm_sd2_si_qch_s_lh_r
			qch_con_lh_dclm_sd2_si_qch_s_lh_r; /* offset : 0x3178 */
	union cmu_dcl_qch_con_lh_dclm_sd2_si_qch_s_lh_w
			qch_con_lh_dclm_sd2_si_qch_s_lh_w; /* offset : 0x317c */
	union cmu_dcl_qch_con_lh_dclm_sd3_si_qch_s_lh_r
			qch_con_lh_dclm_sd3_si_qch_s_lh_r; /* offset : 0x3180 */
	union cmu_dcl_qch_con_lh_dclm_sd3_si_qch_s_lh_w
			qch_con_lh_dclm_sd3_si_qch_s_lh_w; /* offset : 0x3184 */
	union cmu_dcl_qch_con_lh_dcls_dd0_mi_qch_s_lh_r
			qch_con_lh_dcls_dd0_mi_qch_s_lh_r; /* offset : 0x3188 */
	union cmu_dcl_qch_con_lh_dcls_dd0_mi_qch_s_lh_w
			qch_con_lh_dcls_dd0_mi_qch_s_lh_w; /* offset : 0x318c */
	union cmu_dcl_qch_con_lh_dcls_dd1_mi_qch_s_lh_r
			qch_con_lh_dcls_dd1_mi_qch_s_lh_r; /* offset : 0x3190 */
	union cmu_dcl_qch_con_lh_dcls_dd1_mi_qch_s_lh_w
			qch_con_lh_dcls_dd1_mi_qch_s_lh_w; /* offset : 0x3194 */
	union cmu_dcl_qch_con_lh_dcls_dd2_mi_qch_s_lh_r
			qch_con_lh_dcls_dd2_mi_qch_s_lh_r; /* offset : 0x3198 */
	union cmu_dcl_qch_con_lh_dcls_dd2_mi_qch_s_lh_w
			qch_con_lh_dcls_dd2_mi_qch_s_lh_w; /* offset : 0x319c */
	union cmu_dcl_qch_con_lh_dcls_dd3_mi_qch_s_lh_r
			qch_con_lh_dcls_dd3_mi_qch_s_lh_r; /* offset : 0x31a0 */
	union cmu_dcl_qch_con_lh_dcls_dd3_mi_qch_s_lh_w
			qch_con_lh_dcls_dd3_mi_qch_s_lh_w; /* offset : 0x31a4 */
	union cmu_dcl_qch_con_lh_dcls_sd0_mi_qch_s_lh_r
			qch_con_lh_dcls_sd0_mi_qch_s_lh_r; /* offset : 0x31a8 */
	union cmu_dcl_qch_con_lh_dcls_sd0_mi_qch_s_lh_w
			qch_con_lh_dcls_sd0_mi_qch_s_lh_w; /* offset : 0x31ac */
	union cmu_dcl_qch_con_lh_dcls_sd1_mi_qch_s_lh_r
			qch_con_lh_dcls_sd1_mi_qch_s_lh_r; /* offset : 0x31b0 */
	union cmu_dcl_qch_con_lh_dcls_sd1_mi_qch_s_lh_w
			qch_con_lh_dcls_sd1_mi_qch_s_lh_w; /* offset : 0x31b4 */
	union cmu_dcl_qch_con_lh_dcls_sd2_mi_qch_s_lh_r
			qch_con_lh_dcls_sd2_mi_qch_s_lh_r; /* offset : 0x31b8 */
	union cmu_dcl_qch_con_lh_dcls_sd2_mi_qch_s_lh_w
			qch_con_lh_dcls_sd2_mi_qch_s_lh_w; /* offset : 0x31bc */
	union cmu_dcl_qch_con_lh_dcls_sd3_mi_qch_s_lh_r
			qch_con_lh_dcls_sd3_mi_qch_s_lh_r; /* offset : 0x31c0 */
	union cmu_dcl_qch_con_lh_dcls_sd3_mi_qch_s_lh_w
			qch_con_lh_dcls_sd3_mi_qch_s_lh_w; /* offset : 0x31c4 */
	union cmu_dcl_qch_con_lh_dclm_sc_si_qch_s_lh
			qch_con_lh_dclm_sc_si_qch_s_lh; /* offset : 0x31c8 */
	union cmu_dcl_qch_con_lh_dcls_sc_mi_qch_s_lh
			qch_con_lh_dcls_sc_mi_qch_s_lh; /* offset : 0x31cc */
	union cmu_dcl_qch_con_add0ctrl_dcl_qch qch_con_add0ctrl_dcl_qch; /* offset : 0x31d0 */
	union cmu_dcl_qch_con_add1ctrl_dcl_qch qch_con_add1ctrl_dcl_qch; /* offset : 0x31d4 */
	union cmu_dcl_qch_con_add2ctrl_dcl_qch qch_con_add2ctrl_dcl_qch; /* offset : 0x31d8 */
	union cmu_dcl_qch_con_add3ctrl_dcl_qch qch_con_add3ctrl_dcl_qch; /* offset : 0x31dc */
	union cmu_dcl_qch_con_sysreg_dcl_qch qch_con_sysreg_dcl_qch; /* offset : 0x31e0 */
	union cmu_dcl_qch_con_shortstop_qch qch_con_shortstop_qch; /* offset : 0x31e4 */
};

enum DCL_CLK_OUT {
	OSCCLK_DCL,
	PLL_DCL,
	PLL_DCL_DVFS,
	CLK_DCL_ACLK0,
	CLK_DCL_ACLK1,
	CLK_DCL_ACLK2,
	CLK_DCL_ACLK3,
	CLK_DCL_ACLK4,
	CLK_DCL_ACLK5,
	CLK_DCL_PCLK,
	CLK_DCL_CMUREF,
	CLK_DCL_OSCCLK,
	CLK_DCL_ADD,
	CLK_DCL_PVT,
	CLK_DCL_ACLK_DGLUE0,
	CLK_DCL_ACLK_DGLUE1,
	CLK_DCL_ACLK_DGLUE2,
	CLK_DCL_ACLK_DGLUE3,
	CLK_DCL_ACLK_SGLUE,
	DCL_CLK_LH_SCAN_DST,
	DCL_CLK_LH_SCAN_ETC,
};
