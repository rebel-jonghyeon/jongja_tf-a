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

union cmu_dram_pll_locktime_pll_hbm3_phy0 {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_locktime_pll_hbm3_phy1 {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_locktime_pll_hbm3_phy2 {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_locktime_pll_hbm3_phy3 {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_con0_pll_hbm3_phy0 {
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

union cmu_dram_pll_con1_pll_hbm3_phy0 {
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

union cmu_dram_pll_con2_pll_hbm3_phy0 {
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

union cmu_dram_pll_con3_pll_hbm3_phy0 {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_con4_pll_hbm3_phy0 {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dram_pll_con0_pll_hbm3_phy1 {
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

union cmu_dram_pll_con1_pll_hbm3_phy1 {
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

union cmu_dram_pll_con2_pll_hbm3_phy1 {
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

union cmu_dram_pll_con3_pll_hbm3_phy1 {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_con4_pll_hbm3_phy1 {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dram_pll_con0_pll_hbm3_phy2 {
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

union cmu_dram_pll_con1_pll_hbm3_phy2 {
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

union cmu_dram_pll_con2_pll_hbm3_phy2 {
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

union cmu_dram_pll_con3_pll_hbm3_phy2 {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_con4_pll_hbm3_phy2 {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dram_pll_con0_pll_hbm3_phy3 {
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

union cmu_dram_pll_con1_pll_hbm3_phy3 {
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

union cmu_dram_pll_con2_pll_hbm3_phy3 {
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

union cmu_dram_pll_con3_pll_hbm3_phy3 {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_dram_pll_con4_pll_hbm3_phy3 {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dram_dram_cmu_dram_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_dram_clkout_con_blk_dram_cmu_dram_clkout {
	struct {
		uint32_t div_ratio:6; /* [5:0] */
		uint32_t reserved0:2; /* [7:6] */
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

union cmu_dram_clk_con_div_div2_dram_aclk0 {
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

union cmu_dram_clk_con_div_div8_dram_pclk0 {
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

union cmu_dram_clk_con_div_div2_dram_aclk1 {
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

union cmu_dram_clk_con_div_div8_dram_pclk1 {
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

union cmu_dram_clk_con_div_div2_dram_aclk2 {
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

union cmu_dram_clk_con_div_div8_dram_pclk2 {
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

union cmu_dram_clk_con_div_div2_dram_aclk3 {
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

union cmu_dram_clk_con_div_div8_dram_pclk3 {
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

union cmu_dram_clk_con_div_div5_dram_wrck_icon {
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

union cmu_dram_clk_con_custom_gfclkmux {
	struct {
		uint32_t use_custom_gfclkmux_sel:1; /* [0:0] */
		uint32_t sfr_custom_gfclkmux_sel_0:1; /* [1:1] */
		uint32_t sfr_custom_gfclkmux_sel_1:1; /* [2:2] */
		uint32_t sfr_custom_gfclkmux_sel_2:1; /* [3:3] */
		uint32_t sfr_custom_gfclkmux_sel_3:1; /* [4:4] */
		uint32_t reserved0:27; /* [31:5] */
	};
	uint32_t val;
};

union cmu_dram_clk_con_gat_clk_blk_dram_uid_dram_cmu_dram_ipclkport_pclk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_icon_pclk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_wrck_icon {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c0 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c0 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c1 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c1 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c2 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c2 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c3 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c3 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c4 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c4 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c5 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c5 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c6 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c6 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c7 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c7 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c8 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c8 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c9 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c9 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c10 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c10 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c11 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c11 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c12 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c12 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c13 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c13 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c14 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c14 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c15 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c15 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c0 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c0 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c1 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c1 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c2 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c2 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c3 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c3 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c4 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c4 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c5 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c5 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c6 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c6 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c7 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c7 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c8 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c8 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c9 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c9 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c10 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c10 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c11 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c11 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c12 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c12 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c13 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c13 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c14 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c14 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c15 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c15 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_dst {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_etc {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_0 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_1 {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_da_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_db_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dc_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dd_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_de_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_df_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dg_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dh_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_di_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dj_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dk_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dl_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dm_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dn_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_do_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dp_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_p_mi_ipclkport_i_clk {
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

union cmu_dram_clk_con_gat_clk_blk_dram_uid_sysreg_dram_ipclkport_pclk {
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

union cmu_dram_qch_con_axi2apb_bridge_dram_qch {
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

union cmu_dram_qch_con_rstnsync_dram_pclk_qch {
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

union cmu_dram_qch_con_rstnsync_dram_aclk0_qch {
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

union cmu_dram_qch_con_rstnsync_dram_aclk1_qch {
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

union cmu_dram_qch_con_rstnsync_dram_aclk2_qch {
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

union cmu_dram_qch_con_rstnsync_dram_aclk3_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n0_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n1_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n2_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n3_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n4_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n5_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n6_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n7_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n8_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n9_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n10_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n11_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n12_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n13_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n14_qch {
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

union cmu_dram_qch_con_rstnsync_dram_rst_n15_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n0_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n1_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n2_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n3_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n4_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n5_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n6_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n7_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n8_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n9_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n10_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n11_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n12_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n13_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n14_qch {
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

union cmu_dram_qch_con_rstnsync_dram_div_rst_n15_qch {
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

union cmu_dram_qch_con_rstnsync_dram_csr_qch {
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

union cmu_dram_qch_con_rstnsync_dram_phy_pclk_qch {
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

union cmu_dram_qch_con_hbm_ss_qch {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c0 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c1 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c2 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c3 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c4 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c5 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c6 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c7 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c8 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c9 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c10 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c11 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c12 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c13 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c14 {
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

union cmu_dram_qch_con_hbm_ss_qch_clk4x_c15 {
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

union cmu_dram_qch_con_lh_qch {
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

union cmu_dram_qch_con_lh_rs_qch {
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

union cmu_dram_qch_con_lh_drams_da_mi_pch {
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

union cmu_dram_qch_con_lh_drams_db_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dc_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dd_mi_pch {
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

union cmu_dram_qch_con_lh_drams_de_mi_pch {
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

union cmu_dram_qch_con_lh_drams_df_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dg_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dh_mi_pch {
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

union cmu_dram_qch_con_lh_drams_di_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dj_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dk_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dl_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dm_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dn_mi_pch {
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

union cmu_dram_qch_con_lh_drams_do_mi_pch {
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

union cmu_dram_qch_con_lh_drams_dp_mi_pch {
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

union cmu_dram_qch_con_lh_drams_p_mi_pch {
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

union cmu_dram_qch_con_dram_cmu_dram_qch {
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

union cmu_dram_qch_con_lh_drams_da_mi_qch {
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

union cmu_dram_qch_con_lh_drams_db_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dc_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dd_mi_qch {
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

union cmu_dram_qch_con_lh_drams_de_mi_qch {
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

union cmu_dram_qch_con_lh_drams_df_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dg_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dh_mi_qch {
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

union cmu_dram_qch_con_lh_drams_di_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dj_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dk_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dl_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dm_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dn_mi_qch {
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

union cmu_dram_qch_con_lh_drams_do_mi_qch {
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

union cmu_dram_qch_con_lh_drams_dp_mi_qch {
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

union cmu_dram_qch_con_lh_drams_p_mi_qch {
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

union cmu_dram_qch_con_sysreg_dram_qch {
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

struct cmu_dram {
	union cmu_dram_pll_locktime_pll_hbm3_phy0 pll_locktime_pll_hbm3_phy0; /* offset : 0x0 */
	union cmu_dram_pll_locktime_pll_hbm3_phy1 pll_locktime_pll_hbm3_phy1; /* offset : 0x4 */
	union cmu_dram_pll_locktime_pll_hbm3_phy2 pll_locktime_pll_hbm3_phy2; /* offset : 0x8 */
	union cmu_dram_pll_locktime_pll_hbm3_phy3 pll_locktime_pll_hbm3_phy3; /* offset : 0xc */
	uint32_t reserved_1[60];
	union cmu_dram_pll_con0_pll_hbm3_phy0 pll_con0_pll_hbm3_phy0; /* offset : 0x100 */
	union cmu_dram_pll_con1_pll_hbm3_phy0 pll_con1_pll_hbm3_phy0; /* offset : 0x104 */
	union cmu_dram_pll_con2_pll_hbm3_phy0 pll_con2_pll_hbm3_phy0; /* offset : 0x108 */
	union cmu_dram_pll_con3_pll_hbm3_phy0 pll_con3_pll_hbm3_phy0; /* offset : 0x10c */
	union cmu_dram_pll_con4_pll_hbm3_phy0 pll_con4_pll_hbm3_phy0; /* offset : 0x110 */
	union cmu_dram_pll_con0_pll_hbm3_phy1 pll_con0_pll_hbm3_phy1; /* offset : 0x114 */
	union cmu_dram_pll_con1_pll_hbm3_phy1 pll_con1_pll_hbm3_phy1; /* offset : 0x118 */
	union cmu_dram_pll_con2_pll_hbm3_phy1 pll_con2_pll_hbm3_phy1; /* offset : 0x11c */
	union cmu_dram_pll_con3_pll_hbm3_phy1 pll_con3_pll_hbm3_phy1; /* offset : 0x120 */
	union cmu_dram_pll_con4_pll_hbm3_phy1 pll_con4_pll_hbm3_phy1; /* offset : 0x124 */
	union cmu_dram_pll_con0_pll_hbm3_phy2 pll_con0_pll_hbm3_phy2; /* offset : 0x128 */
	union cmu_dram_pll_con1_pll_hbm3_phy2 pll_con1_pll_hbm3_phy2; /* offset : 0x12c */
	union cmu_dram_pll_con2_pll_hbm3_phy2 pll_con2_pll_hbm3_phy2; /* offset : 0x130 */
	union cmu_dram_pll_con3_pll_hbm3_phy2 pll_con3_pll_hbm3_phy2; /* offset : 0x134 */
	union cmu_dram_pll_con4_pll_hbm3_phy2 pll_con4_pll_hbm3_phy2; /* offset : 0x138 */
	union cmu_dram_pll_con0_pll_hbm3_phy3 pll_con0_pll_hbm3_phy3; /* offset : 0x13c */
	union cmu_dram_pll_con1_pll_hbm3_phy3 pll_con1_pll_hbm3_phy3; /* offset : 0x140 */
	union cmu_dram_pll_con2_pll_hbm3_phy3 pll_con2_pll_hbm3_phy3; /* offset : 0x144 */
	union cmu_dram_pll_con3_pll_hbm3_phy3 pll_con3_pll_hbm3_phy3; /* offset : 0x148 */
	union cmu_dram_pll_con4_pll_hbm3_phy3 pll_con4_pll_hbm3_phy3; /* offset : 0x14c */
	uint32_t reserved_2[428];
	union cmu_dram_dram_cmu_dram_controller_option
		dram_cmu_dram_controller_option; /* offset : 0x800 */
	union cmu_dram_clkout_con_blk_dram_cmu_dram_clkout
		clkout_con_blk_dram_cmu_dram_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
	union cmu_dram_clk_con_div_div2_dram_aclk0 clk_con_div_div2_dram_aclk0; /* offset : 0x1800 */
	union cmu_dram_clk_con_div_div8_dram_pclk0 clk_con_div_div8_dram_pclk0; /* offset : 0x1804 */
	union cmu_dram_clk_con_div_div2_dram_aclk1 clk_con_div_div2_dram_aclk1; /* offset : 0x1808 */
	union cmu_dram_clk_con_div_div8_dram_pclk1 clk_con_div_div8_dram_pclk1; /* offset : 0x180c */
	union cmu_dram_clk_con_div_div2_dram_aclk2 clk_con_div_div2_dram_aclk2; /* offset : 0x1810 */
	union cmu_dram_clk_con_div_div8_dram_pclk2 clk_con_div_div8_dram_pclk2; /* offset : 0x1814 */
	union cmu_dram_clk_con_div_div2_dram_aclk3 clk_con_div_div2_dram_aclk3; /* offset : 0x1818 */
	union cmu_dram_clk_con_div_div8_dram_pclk3 clk_con_div_div8_dram_pclk3; /* offset : 0x181c */
	uint32_t reserved_4[16];
	union cmu_dram_clk_con_div_div5_dram_wrck_icon
		clk_con_div_div5_dram_wrck_icon; /* offset : 0x1860 */
	union cmu_dram_clk_con_custom_gfclkmux clk_con_custom_gfclkmux; /* offset : 0x1864 */
	uint32_t reserved_5[486];
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_dram_cmu_dram_ipclkport_pclk
		clk_con_gat_clk_blk_dram_uid_dram_cmu_dram_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_icon_pclk
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_icon_pclk; /* offset : 0x2004 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_wrck_icon
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_wrck_icon; /* offset : 0x2008 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c0
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c0; /* offset : 0x200c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c0
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c0; /* offset : 0x2010 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c1
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c1; /* offset : 0x2014 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c1
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c1; /* offset : 0x2018 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c2
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c2; /* offset : 0x201c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c2
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c2; /* offset : 0x2020 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c3
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c3; /* offset : 0x2024 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c3
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c3; /* offset : 0x2028 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c4
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c4; /* offset : 0x202c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c4
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c4; /* offset : 0x2030 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c5
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c5; /* offset : 0x2034 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c5
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c5; /* offset : 0x2038 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c6
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c6; /* offset : 0x203c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c6
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c6; /* offset : 0x2040 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c7
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c7; /* offset : 0x2044 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c7
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c7; /* offset : 0x2048 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c8
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c8; /* offset : 0x204c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c8
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c8; /* offset : 0x2050 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c9
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c9; /* offset : 0x2054 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c9
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c9; /* offset : 0x2058 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c10
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c10; /* offset : 0x205c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c10
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c10; /* offset : 0x2060 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c11
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c11; /* offset : 0x2064 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c11
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c11; /* offset : 0x2068 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c12
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c12; /* offset : 0x206c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c12
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c12; /* offset : 0x2070 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c13
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c13; /* offset : 0x2074 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c13
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c13; /* offset : 0x2078 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c14
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c14; /* offset : 0x207c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c14
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c14; /* offset : 0x2080 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c15
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_axi1_aclk_c15; /* offset : 0x2084 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c15
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_csr_clk_c15; /* offset : 0x2088 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c0
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c0; /* offset : 0x208c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c0
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c0; /* offset : 0x2090 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c1
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c1; /* offset : 0x2094 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c1
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c1; /* offset : 0x2098 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c2
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c2; /* offset : 0x209c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c2
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c2; /* offset : 0x20a0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c3
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c3; /* offset : 0x20a4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c3
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c3; /* offset : 0x20a8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c4
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c4; /* offset : 0x20ac */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c4
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c4; /* offset : 0x20b0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c5
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c5; /* offset : 0x20b4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c5
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c5; /* offset : 0x20b8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c6
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c6; /* offset : 0x20bc */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c6
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c6; /* offset : 0x20c0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c7
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c7; /* offset : 0x20c4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c7
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c7; /* offset : 0x20c8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c8
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c8; /* offset : 0x20cc */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c8
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c8; /* offset : 0x20d0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c9
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c9; /* offset : 0x20d4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c9
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c9; /* offset : 0x20d8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c10
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c10; /* offset : 0x20dc */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c10
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c10; /* offset : 0x20e0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c11
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c11; /* offset : 0x20e4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c11
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c11; /* offset : 0x20e8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c12
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c12; /* offset : 0x20ec */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c12
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c12; /* offset : 0x20f0 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c13
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c13; /* offset : 0x20f4 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c13
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c13; /* offset : 0x20f8 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c14
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c14; /* offset : 0x20fc */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c14
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c14; /* offset : 0x2100 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c15
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_osc_clk_c15; /* offset : 0x2104 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c15
		clk_con_gat_clk_blk_dram_uid_hbm_ss_ipclkport_phy_pclk_c15; /* offset : 0x2108 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x210c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_dram_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2110 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_0
		clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_0; /* offset : 0x2114 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_1
		clk_con_gat_clk_blk_dram_uid_lh_rs_ipclkport_i_scan_clk_rt_1; /* offset : 0x2118 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_da_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_da_mi_ipclkport_i_clk; /* offset : 0x211c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_db_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_db_mi_ipclkport_i_clk; /* offset : 0x2120 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dc_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dc_mi_ipclkport_i_clk; /* offset : 0x2124 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dd_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dd_mi_ipclkport_i_clk; /* offset : 0x2128 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_de_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_de_mi_ipclkport_i_clk; /* offset : 0x212c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_df_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_df_mi_ipclkport_i_clk; /* offset : 0x2130 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dg_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dg_mi_ipclkport_i_clk; /* offset : 0x2134 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dh_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dh_mi_ipclkport_i_clk; /* offset : 0x2138 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_di_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_di_mi_ipclkport_i_clk; /* offset : 0x213c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dj_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dj_mi_ipclkport_i_clk; /* offset : 0x2140 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dk_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dk_mi_ipclkport_i_clk; /* offset : 0x2144 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dl_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dl_mi_ipclkport_i_clk; /* offset : 0x2148 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dm_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dm_mi_ipclkport_i_clk; /* offset : 0x214c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dn_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dn_mi_ipclkport_i_clk; /* offset : 0x2150 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_do_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_do_mi_ipclkport_i_clk; /* offset : 0x2154 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_dp_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_dp_mi_ipclkport_i_clk; /* offset : 0x2158 */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_lh_drams_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_dram_uid_lh_drams_p_mi_ipclkport_i_clk; /* offset : 0x215c */
	union cmu_dram_clk_con_gat_clk_blk_dram_uid_sysreg_dram_ipclkport_pclk
		clk_con_gat_clk_blk_dram_uid_sysreg_dram_ipclkport_pclk; /* offset : 0x2160 */
	uint32_t reserved_6[935];
	union cmu_dram_qch_con_axi2apb_bridge_dram_qch
		qch_con_axi2apb_bridge_dram_qch; /* offset : 0x3000 */
	union cmu_dram_qch_con_rstnsync_dram_pclk_qch
		qch_con_rstnsync_dram_pclk_qch; /* offset : 0x3004 */
	union cmu_dram_qch_con_rstnsync_dram_aclk0_qch
		qch_con_rstnsync_dram_aclk0_qch; /* offset : 0x3008 */
	union cmu_dram_qch_con_rstnsync_dram_aclk1_qch
		qch_con_rstnsync_dram_aclk1_qch; /* offset : 0x300c */
	union cmu_dram_qch_con_rstnsync_dram_aclk2_qch
		qch_con_rstnsync_dram_aclk2_qch; /* offset : 0x3010 */
	union cmu_dram_qch_con_rstnsync_dram_aclk3_qch
		qch_con_rstnsync_dram_aclk3_qch; /* offset : 0x3014 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n0_qch
		qch_con_rstnsync_dram_rst_n0_qch; /* offset : 0x3018 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n1_qch
		qch_con_rstnsync_dram_rst_n1_qch; /* offset : 0x301c */
	union cmu_dram_qch_con_rstnsync_dram_rst_n2_qch
		qch_con_rstnsync_dram_rst_n2_qch; /* offset : 0x3020 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n3_qch
		qch_con_rstnsync_dram_rst_n3_qch; /* offset : 0x3024 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n4_qch
		qch_con_rstnsync_dram_rst_n4_qch; /* offset : 0x3028 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n5_qch
		qch_con_rstnsync_dram_rst_n5_qch; /* offset : 0x302c */
	union cmu_dram_qch_con_rstnsync_dram_rst_n6_qch
		qch_con_rstnsync_dram_rst_n6_qch; /* offset : 0x3030 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n7_qch
		qch_con_rstnsync_dram_rst_n7_qch; /* offset : 0x3034 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n8_qch
		qch_con_rstnsync_dram_rst_n8_qch; /* offset : 0x3038 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n9_qch
		qch_con_rstnsync_dram_rst_n9_qch; /* offset : 0x303c */
	union cmu_dram_qch_con_rstnsync_dram_rst_n10_qch
		qch_con_rstnsync_dram_rst_n10_qch; /* offset : 0x3040 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n11_qch
		qch_con_rstnsync_dram_rst_n11_qch; /* offset : 0x3044 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n12_qch
		qch_con_rstnsync_dram_rst_n12_qch; /* offset : 0x3048 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n13_qch
		qch_con_rstnsync_dram_rst_n13_qch; /* offset : 0x304c */
	union cmu_dram_qch_con_rstnsync_dram_rst_n14_qch
		qch_con_rstnsync_dram_rst_n14_qch; /* offset : 0x3050 */
	union cmu_dram_qch_con_rstnsync_dram_rst_n15_qch
		qch_con_rstnsync_dram_rst_n15_qch; /* offset : 0x3054 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n0_qch
		qch_con_rstnsync_dram_div_rst_n0_qch; /* offset : 0x3058 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n1_qch
		qch_con_rstnsync_dram_div_rst_n1_qch; /* offset : 0x305c */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n2_qch
		qch_con_rstnsync_dram_div_rst_n2_qch; /* offset : 0x3060 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n3_qch
		qch_con_rstnsync_dram_div_rst_n3_qch; /* offset : 0x3064 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n4_qch
		qch_con_rstnsync_dram_div_rst_n4_qch; /* offset : 0x3068 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n5_qch
		qch_con_rstnsync_dram_div_rst_n5_qch; /* offset : 0x306c */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n6_qch
		qch_con_rstnsync_dram_div_rst_n6_qch; /* offset : 0x3070 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n7_qch
		qch_con_rstnsync_dram_div_rst_n7_qch; /* offset : 0x3074 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n8_qch
		qch_con_rstnsync_dram_div_rst_n8_qch; /* offset : 0x3078 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n9_qch
		qch_con_rstnsync_dram_div_rst_n9_qch; /* offset : 0x307c */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n10_qch
		qch_con_rstnsync_dram_div_rst_n10_qch; /* offset : 0x3080 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n11_qch
		qch_con_rstnsync_dram_div_rst_n11_qch; /* offset : 0x3084 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n12_qch
		qch_con_rstnsync_dram_div_rst_n12_qch; /* offset : 0x3088 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n13_qch
		qch_con_rstnsync_dram_div_rst_n13_qch; /* offset : 0x308c */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n14_qch
		qch_con_rstnsync_dram_div_rst_n14_qch; /* offset : 0x3090 */
	union cmu_dram_qch_con_rstnsync_dram_div_rst_n15_qch
		qch_con_rstnsync_dram_div_rst_n15_qch; /* offset : 0x3094 */
	union cmu_dram_qch_con_rstnsync_dram_csr_qch
		qch_con_rstnsync_dram_csr_qch; /* offset : 0x3098 */
	union cmu_dram_qch_con_rstnsync_dram_phy_pclk_qch
		qch_con_rstnsync_dram_phy_pclk_qch; /* offset : 0x309c */
	union cmu_dram_qch_con_hbm_ss_qch qch_con_hbm_ss_qch; /* offset : 0x30a0 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c0 qch_con_hbm_ss_qch_clk4x_c0; /* offset : 0x30a4 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c1 qch_con_hbm_ss_qch_clk4x_c1; /* offset : 0x30a8 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c2 qch_con_hbm_ss_qch_clk4x_c2; /* offset : 0x30ac */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c3 qch_con_hbm_ss_qch_clk4x_c3; /* offset : 0x30b0 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c4 qch_con_hbm_ss_qch_clk4x_c4; /* offset : 0x30b4 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c5 qch_con_hbm_ss_qch_clk4x_c5; /* offset : 0x30b8 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c6 qch_con_hbm_ss_qch_clk4x_c6; /* offset : 0x30bc */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c7 qch_con_hbm_ss_qch_clk4x_c7; /* offset : 0x30c0 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c8 qch_con_hbm_ss_qch_clk4x_c8; /* offset : 0x30c4 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c9 qch_con_hbm_ss_qch_clk4x_c9; /* offset : 0x30c8 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c10 qch_con_hbm_ss_qch_clk4x_c10; /* offset : 0x30cc */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c11 qch_con_hbm_ss_qch_clk4x_c11; /* offset : 0x30d0 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c12 qch_con_hbm_ss_qch_clk4x_c12; /* offset : 0x30d4 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c13 qch_con_hbm_ss_qch_clk4x_c13; /* offset : 0x30d8 */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c14 qch_con_hbm_ss_qch_clk4x_c14; /* offset : 0x30dc */
	union cmu_dram_qch_con_hbm_ss_qch_clk4x_c15 qch_con_hbm_ss_qch_clk4x_c15; /* offset : 0x30e0 */
	union cmu_dram_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x30e4 */
	union cmu_dram_qch_con_lh_rs_qch qch_con_lh_rs_qch; /* offset : 0x30e8 */
	union cmu_dram_qch_con_lh_drams_da_mi_pch qch_con_lh_drams_da_mi_pch; /* offset : 0x30ec */
	union cmu_dram_qch_con_lh_drams_db_mi_pch qch_con_lh_drams_db_mi_pch; /* offset : 0x30f0 */
	union cmu_dram_qch_con_lh_drams_dc_mi_pch qch_con_lh_drams_dc_mi_pch; /* offset : 0x30f4 */
	union cmu_dram_qch_con_lh_drams_dd_mi_pch qch_con_lh_drams_dd_mi_pch; /* offset : 0x30f8 */
	union cmu_dram_qch_con_lh_drams_de_mi_pch qch_con_lh_drams_de_mi_pch; /* offset : 0x30fc */
	union cmu_dram_qch_con_lh_drams_df_mi_pch qch_con_lh_drams_df_mi_pch; /* offset : 0x3100 */
	union cmu_dram_qch_con_lh_drams_dg_mi_pch qch_con_lh_drams_dg_mi_pch; /* offset : 0x3104 */
	union cmu_dram_qch_con_lh_drams_dh_mi_pch qch_con_lh_drams_dh_mi_pch; /* offset : 0x3108 */
	union cmu_dram_qch_con_lh_drams_di_mi_pch qch_con_lh_drams_di_mi_pch; /* offset : 0x310c */
	union cmu_dram_qch_con_lh_drams_dj_mi_pch qch_con_lh_drams_dj_mi_pch; /* offset : 0x3110 */
	union cmu_dram_qch_con_lh_drams_dk_mi_pch qch_con_lh_drams_dk_mi_pch; /* offset : 0x3114 */
	union cmu_dram_qch_con_lh_drams_dl_mi_pch qch_con_lh_drams_dl_mi_pch; /* offset : 0x3118 */
	union cmu_dram_qch_con_lh_drams_dm_mi_pch qch_con_lh_drams_dm_mi_pch; /* offset : 0x311c */
	union cmu_dram_qch_con_lh_drams_dn_mi_pch qch_con_lh_drams_dn_mi_pch; /* offset : 0x3120 */
	union cmu_dram_qch_con_lh_drams_do_mi_pch qch_con_lh_drams_do_mi_pch; /* offset : 0x3124 */
	union cmu_dram_qch_con_lh_drams_dp_mi_pch qch_con_lh_drams_dp_mi_pch; /* offset : 0x3128 */
	union cmu_dram_qch_con_lh_drams_p_mi_pch qch_con_lh_drams_p_mi_pch; /* offset : 0x312c */
	union cmu_dram_qch_con_dram_cmu_dram_qch qch_con_dram_cmu_dram_qch; /* offset : 0x3130 */
	union cmu_dram_qch_con_lh_drams_da_mi_qch qch_con_lh_drams_da_mi_qch; /* offset : 0x3134 */
	union cmu_dram_qch_con_lh_drams_db_mi_qch qch_con_lh_drams_db_mi_qch; /* offset : 0x3138 */
	union cmu_dram_qch_con_lh_drams_dc_mi_qch qch_con_lh_drams_dc_mi_qch; /* offset : 0x313c */
	union cmu_dram_qch_con_lh_drams_dd_mi_qch qch_con_lh_drams_dd_mi_qch; /* offset : 0x3140 */
	union cmu_dram_qch_con_lh_drams_de_mi_qch qch_con_lh_drams_de_mi_qch; /* offset : 0x3144 */
	union cmu_dram_qch_con_lh_drams_df_mi_qch qch_con_lh_drams_df_mi_qch; /* offset : 0x3148 */
	union cmu_dram_qch_con_lh_drams_dg_mi_qch qch_con_lh_drams_dg_mi_qch; /* offset : 0x314c */
	union cmu_dram_qch_con_lh_drams_dh_mi_qch qch_con_lh_drams_dh_mi_qch; /* offset : 0x3150 */
	union cmu_dram_qch_con_lh_drams_di_mi_qch qch_con_lh_drams_di_mi_qch; /* offset : 0x3154 */
	union cmu_dram_qch_con_lh_drams_dj_mi_qch qch_con_lh_drams_dj_mi_qch; /* offset : 0x3158 */
	union cmu_dram_qch_con_lh_drams_dk_mi_qch qch_con_lh_drams_dk_mi_qch; /* offset : 0x315c */
	union cmu_dram_qch_con_lh_drams_dl_mi_qch qch_con_lh_drams_dl_mi_qch; /* offset : 0x3160 */
	union cmu_dram_qch_con_lh_drams_dm_mi_qch qch_con_lh_drams_dm_mi_qch; /* offset : 0x3164 */
	union cmu_dram_qch_con_lh_drams_dn_mi_qch qch_con_lh_drams_dn_mi_qch; /* offset : 0x3168 */
	union cmu_dram_qch_con_lh_drams_do_mi_qch qch_con_lh_drams_do_mi_qch; /* offset : 0x316c */
	union cmu_dram_qch_con_lh_drams_dp_mi_qch qch_con_lh_drams_dp_mi_qch; /* offset : 0x3170 */
	union cmu_dram_qch_con_lh_drams_p_mi_qch qch_con_lh_drams_p_mi_qch; /* offset : 0x3174 */
	union cmu_dram_qch_con_sysreg_dram_qch qch_con_sysreg_dram_qch; /* offset : 0x3178 */
};

enum DRAM_CLK_OUT {
	OSCCLK_DRAM,
	PLL_HBM3_PHY0_OUT_0,
	PLL_HBM3_PHY1_OUT_0,
	PLL_HBM3_PHY2_OUT_0,
	PLL_HBM3_PHY3_OUT_0,
	PLL_HBM3P_PHY0_GFMUX_OUT_0,
	PLL_HBM3P_PHY1_GFMUX_OUT_0,
	PLL_HBM3P_PHY2_GFMUX_OUT_0,
	PLL_HBM3P_PHY3_GFMUX_OUT_0,
	CLK_DRAM_ACLK0,
	CLK_DRAM_ACLK1,
	CLK_DRAM_ACLK2,
	CLK_DRAM_ACLK3,
	CLK_DRAM_PCLK0,
	CLK_DRAM_PCLK1,
	CLK_DRAM_PCLK2,
	CLK_DRAM_PCLK3,
	CLK_DRAM_WRCK_ICON,
	CLK_DRAM_PHY_OSC,
	DRAM_CLK_LH_SCAN_DST,
	DRAM_CLK_LH_SCAN_ETC,
};
