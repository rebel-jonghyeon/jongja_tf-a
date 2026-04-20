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

union cmu_ebus_u_pll_locktime_pll_ebus {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_ebus_u_pll_con0_pll_ebus {
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

union cmu_ebus_u_pll_con1_pll_ebus {
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

union cmu_ebus_u_pll_con2_pll_ebus {
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

union cmu_ebus_u_pll_con3_pll_ebus {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_ebus_u_pll_con4_pll_ebus {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_ebus_u_pll_con0_pll_ctrl_ebus_u {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_ebus_u_pll_con1_pll_ctrl_ebus_u {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_ebus_u_pll_con2_pll_ctrl_ebus_u {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_ebus_u_ebus_u_cmu_ebus_u_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_ebus_u_clkout_con_blk_ebus_u_cmu_ebus_u_clkout {
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

union cmu_ebus_u_clk_con_div_div_rbc_h0 {
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

union cmu_ebus_u_clk_con_div_div1_ebus_u_aclk {
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

union cmu_ebus_u_clk_con_div_div_rbc_h1 {
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

union cmu_ebus_u_clk_con_div_div3_ebus_u_pclk {
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

union cmu_ebus_u_clk_con_div_div1_ebus_u_sh_low_clk {
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

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_ebus_u_cmu_ebus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_sysreg_ebus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_sysreg_buscsr_ebus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_ebus_u_noc_refclk_gen_ipclkport_i_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_c_ebus_u_ipclkport_clk_533_e_u {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_d_ebus_u_r_ipclkport_clk_main_sfr_eu {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_shbus_eu_r_ipclkport_clk_shm_sfr_u {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_buf_clk_rbc_h0 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_clk_con_buf_clk_rbc_h1 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi2apb_ebus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi2apb_dbg_ebus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rstnsync_ebus_u_oscclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rstnsync_ebus_u_aclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rstnsync_ebus_u_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rstnsync_ebus_u_sh_low_clk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_ebus_u_noc_refclk_gen_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_noc_c_ebus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_noc_d_ebus_u_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_noc_shbus_eu_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_dti_sw_ebus_u_2x1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_pe_wrapper_cl0_ch2_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_pe_wrapper_cl0_ch2_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_refclk_div_0_sync_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_refclk_div_1_sync_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_refclk_div_2_sync_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_amba_ovrd_cl0_ch2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_dti_rs_cl0_ch2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_dti_rs_cl0_ch3_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_dti_rs_wbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi_rs_dcl0s_dd2_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd2_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd3_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rbc_h0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_rbc_h1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sc_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sc_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sp_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dp2_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_um_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_us_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_rs_ast0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_rm_ast0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_ebus_u_cmu_ebus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_sysreg_ebus_u_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_sysreg_buscsr_ebus_u_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_tbu_dglue_cl0_ch2_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_tbu_dglue_cl0_ch2_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sc_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sc_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sp_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_dcl0s_dp2_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_um_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_us_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_rs_ast0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_ebus_u_qch_con_lh_ebus_rm_ast0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_ebus_u {
	union cmu_ebus_u_pll_locktime_pll_ebus pll_locktime_pll_ebus; /* offset : 0x0 */
	uint32_t reserved_1[63];
	union cmu_ebus_u_pll_con0_pll_ebus pll_con0_pll_ebus; /* offset : 0x100 */
	union cmu_ebus_u_pll_con1_pll_ebus pll_con1_pll_ebus; /* offset : 0x104 */
	union cmu_ebus_u_pll_con2_pll_ebus pll_con2_pll_ebus; /* offset : 0x108 */
	union cmu_ebus_u_pll_con3_pll_ebus pll_con3_pll_ebus; /* offset : 0x10c */
	union cmu_ebus_u_pll_con4_pll_ebus pll_con4_pll_ebus; /* offset : 0x110 */
	union cmu_ebus_u_pll_con0_pll_ctrl_ebus_u pll_con0_pll_ctrl_ebus_u; /* offset : 0x114 */
	union cmu_ebus_u_pll_con1_pll_ctrl_ebus_u pll_con1_pll_ctrl_ebus_u; /* offset : 0x118 */
	union cmu_ebus_u_pll_con2_pll_ctrl_ebus_u pll_con2_pll_ctrl_ebus_u; /* offset : 0x11c */
	uint32_t reserved_2[440];
	union cmu_ebus_u_ebus_u_cmu_ebus_u_controller_option
		ebus_u_cmu_ebus_u_controller_option; /* offset : 0x800 */
	union cmu_ebus_u_clkout_con_blk_ebus_u_cmu_ebus_u_clkout
		clkout_con_blk_ebus_u_cmu_ebus_u_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
	union cmu_ebus_u_clk_con_div_div_rbc_h0 clk_con_div_div_rbc_h0; /* offset : 0x1800 */
	union cmu_ebus_u_clk_con_div_div1_ebus_u_aclk clk_con_div_div1_ebus_u_aclk; /*offset:0x1804*/
	union cmu_ebus_u_clk_con_div_div_rbc_h1 clk_con_div_div_rbc_h1; /* offset : 0x1808 */
	uint32_t reserved_4;
	union cmu_ebus_u_clk_con_div_div3_ebus_u_pclk clk_con_div_div3_ebus_u_pclk; /*offset:0x1810*/
	union cmu_ebus_u_clk_con_div_div1_ebus_u_sh_low_clk
		clk_con_div_div1_ebus_u_sh_low_clk; /* offset : 0x1814 */
	uint32_t reserved_5[506];
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_ebus_u_cmu_ebus_u_ipclkport_pclk
		clk_con_gat_clk_blk_ebus_u_uid_ebus_u_cmu_ebus_u_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2004 */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_ebus_u_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2008 */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_sysreg_ebus_u_ipclkport_pclk
		clk_con_gat_clk_blk_ebus_u_uid_sysreg_ebus_u_ipclkport_pclk; /* offset : 0x200c */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_sysreg_buscsr_ebus_u_ipclkport_pclk
		clk_con_gat_clk_blk_ebus_u_uid_sysreg_buscsr_ebus_u_ipclkport_pclk; /* offset : 0x2010 */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_ebus_u_noc_refclk_gen_ipclkport_i_osc_clk
		clk_con_gat_clk_blk_ebus_u_uid_ebus_u_noc_refclk_gen_ipclkport_i_osc_clk; /*offset:0x2014*/
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_c_ebus_u_ipclkport_clk_533_e_u
		clk_con_gat_clk_blk_ebus_u_uid_noc_c_ebus_u_ipclkport_clk_533_e_u; /* offset : 0x2018 */
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_d_ebus_u_r_ipclkport_clk_main_sfr_eu
		clk_con_gat_clk_blk_ebus_u_uid_noc_d_ebus_u_r_ipclkport_clk_main_sfr_eu; /*offset:0x201c*/
	union cmu_ebus_u_clk_con_gat_clk_blk_ebus_u_uid_noc_shbus_eu_r_ipclkport_clk_shm_sfr_u
		clk_con_gat_clk_blk_ebus_u_uid_noc_shbus_eu_r_ipclkport_clk_shm_sfr_u; /*offset:0x2020*/
	uint32_t reserved_6[13];
	union cmu_ebus_u_clk_con_buf_clk_rbc_h0 clk_con_buf_clk_rbc_h0; /* offset : 0x2058 */
	union cmu_ebus_u_clk_con_buf_clk_rbc_h1 clk_con_buf_clk_rbc_h1; /* offset : 0x205c */
	uint32_t reserved_7[1000];
	union cmu_ebus_u_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3000 */
	union cmu_ebus_u_qch_con_axi2apb_ebus_u_qch qch_con_axi2apb_ebus_u_qch; /* offset : 0x3004 */
	union cmu_ebus_u_qch_con_axi2apb_dbg_ebus_u_qch
		qch_con_axi2apb_dbg_ebus_u_qch; /* offset : 0x3008 */
	union cmu_ebus_u_qch_con_rstnsync_ebus_u_oscclk_qch
		qch_con_rstnsync_ebus_u_oscclk_qch; /* offset : 0x300c */
	union cmu_ebus_u_qch_con_rstnsync_ebus_u_aclk_qch
		qch_con_rstnsync_ebus_u_aclk_qch; /* offset : 0x3010 */
	union cmu_ebus_u_qch_con_rstnsync_ebus_u_pclk_qch
		qch_con_rstnsync_ebus_u_pclk_qch; /* offset : 0x3014 */
	union cmu_ebus_u_qch_con_rstnsync_ebus_u_sh_low_clk_qch
		qch_con_rstnsync_ebus_u_sh_low_clk_qch; /* offset : 0x3018 */
	union cmu_ebus_u_qch_con_ebus_u_noc_refclk_gen_qch
		qch_con_ebus_u_noc_refclk_gen_qch; /* offset : 0x301c */
	union cmu_ebus_u_qch_con_noc_c_ebus_u_qch
		qch_con_noc_c_ebus_u_qch; /* offset : 0x3020 */
	union cmu_ebus_u_qch_con_noc_d_ebus_u_r_qch
		qch_con_noc_d_ebus_u_r_qch; /* offset : 0x3024 */
	union cmu_ebus_u_qch_con_noc_shbus_eu_r_qch
		qch_con_noc_shbus_eu_r_qch; /* offset : 0x3028 */
	union cmu_ebus_u_qch_con_dti_sw_ebus_u_2x1_qch
		qch_con_dti_sw_ebus_u_2x1_qch; /* offset : 0x302c */
	union cmu_ebus_u_qch_con_pe_wrapper_cl0_ch2_qch_s
		qch_con_pe_wrapper_cl0_ch2_qch_s; /* offset : 0x3030 */
	union cmu_ebus_u_qch_con_pe_wrapper_cl0_ch2_qch_d
		qch_con_pe_wrapper_cl0_ch2_qch_d; /* offset : 0x3034 */
	union cmu_ebus_u_qch_con_refclk_div_0_sync_qch_d
		qch_con_refclk_div_0_sync_qch_d; /* offset : 0x3038 */
	union cmu_ebus_u_qch_con_refclk_div_1_sync_qch_d
		qch_con_refclk_div_1_sync_qch_d; /* offset : 0x303c */
	union cmu_ebus_u_qch_con_refclk_div_2_sync_qch_d
		qch_con_refclk_div_2_sync_qch_d; /* offset : 0x3040 */
	union cmu_ebus_u_qch_con_amba_ovrd_cl0_ch2_qch
		qch_con_amba_ovrd_cl0_ch2_qch; /* offset : 0x3044 */
	union cmu_ebus_u_qch_con_dti_rs_cl0_ch2_qch
		qch_con_dti_rs_cl0_ch2_qch; /* offset : 0x3048 */
	union cmu_ebus_u_qch_con_dti_rs_cl0_ch3_qch
		qch_con_dti_rs_cl0_ch3_qch; /* offset : 0x304c */
	union cmu_ebus_u_qch_con_dti_rs_wbus_u_qch
		qch_con_dti_rs_wbus_u_qch; /* offset : 0x3050 */
	union cmu_ebus_u_qch_con_axi_rs_dcl0s_dd2_si_qch
		qch_con_axi_rs_dcl0s_dd2_si_qch; /* offset : 0x3054 */
	union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd0_si_qch
		qch_con_axi_rs_dcl0s_sd0_si_qch; /* offset : 0x3058 */
	union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd1_si_qch
		qch_con_axi_rs_dcl0s_sd1_si_qch; /* offset : 0x305c */
	union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd2_si_qch
		qch_con_axi_rs_dcl0s_sd2_si_qch; /* offset : 0x3060 */
	union cmu_ebus_u_qch_con_axi_rs_dcl0s_sd3_si_qch
		qch_con_axi_rs_dcl0s_sd3_si_qch; /* offset : 0x3064 */
	union cmu_ebus_u_qch_con_rbc_h0_qch qch_con_rbc_h0_qch; /* offset : 0x3068 */
	union cmu_ebus_u_qch_con_rbc_h1_qch qch_con_rbc_h1_qch; /* offset : 0x306c */
	union cmu_ebus_u_qch_con_lh_dcl0m_sc_mi_pch qch_con_lh_dcl0m_sc_mi_pch; /* offset : 0x3070 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sc_si_pch qch_con_lh_dcl0s_sc_si_pch; /* offset : 0x3074 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sp_si_pch qch_con_lh_dcl0s_sp_si_pch; /* offset : 0x3078 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_pch_r
		qch_con_lh_dcl0s_sd0_si_pch_r; /* offset : 0x307c */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_pch_w
		qch_con_lh_dcl0s_sd0_si_pch_w; /* offset : 0x3080 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_pch_r
		qch_con_lh_dcl0s_sd1_si_pch_r; /* offset : 0x3084 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_pch_w
		qch_con_lh_dcl0s_sd1_si_pch_w; /* offset : 0x3088 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_pch_r
		qch_con_lh_dcl0s_sd2_si_pch_r; /* offset : 0x308c */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_pch_w
		qch_con_lh_dcl0s_sd2_si_pch_w; /* offset : 0x3090 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_pch_r
		qch_con_lh_dcl0s_sd3_si_pch_r; /* offset : 0x3094 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_pch_w
		qch_con_lh_dcl0s_sd3_si_pch_w; /* offset : 0x3098 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_pch_r
		qch_con_lh_dcl0m_sd0_mi_pch_r; /* offset : 0x309c */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_pch_w
		qch_con_lh_dcl0m_sd0_mi_pch_w; /* offset : 0x30a0 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_pch_r
		qch_con_lh_dcl0m_sd1_mi_pch_r; /* offset : 0x30a4 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_pch_w
		qch_con_lh_dcl0m_sd1_mi_pch_w; /* offset : 0x30a8 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_pch_r
		qch_con_lh_dcl0m_sd2_mi_pch_r; /* offset : 0x30ac */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_pch_w
		qch_con_lh_dcl0m_sd2_mi_pch_w; /* offset : 0x30b0 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_pch_r
		qch_con_lh_dcl0m_sd3_mi_pch_r; /* offset : 0x30b4 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_pch_w
		qch_con_lh_dcl0m_sd3_mi_pch_w; /* offset : 0x30b8 */
	union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_pch_r
		qch_con_lh_dcl0m_dd2_mi_pch_r; /* offset : 0x30bc */
	union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_pch_w
		qch_con_lh_dcl0m_dd2_mi_pch_w; /* offset : 0x30c0 */
	union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_pch_r
		qch_con_lh_dcl0s_dd2_si_pch_r; /* offset : 0x30c4 */
	union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_pch_w
		qch_con_lh_dcl0s_dd2_si_pch_w; /* offset : 0x30c8 */
	union cmu_ebus_u_qch_con_lh_dcl0s_dp2_si_pch
		qch_con_lh_dcl0s_dp2_si_pch; /* offset : 0x30cc */
	union cmu_ebus_u_qch_con_lh_ebus_um_ast_si_pch
		qch_con_lh_ebus_um_ast_si_pch; /* offset : 0x30d0 */
	union cmu_ebus_u_qch_con_lh_ebus_us_ast_mi_pch
		qch_con_lh_ebus_us_ast_mi_pch; /* offset : 0x30d4 */
	union cmu_ebus_u_qch_con_lh_ebus_rs_ast0_si_pch
		qch_con_lh_ebus_rs_ast0_si_pch; /* offset : 0x30d8 */
	union cmu_ebus_u_qch_con_lh_ebus_rm_ast0_mi_pch
		qch_con_lh_ebus_rm_ast0_mi_pch; /* offset : 0x30dc */
	union cmu_ebus_u_qch_con_ebus_u_cmu_ebus_u_qch
		qch_con_ebus_u_cmu_ebus_u_qch; /* offset : 0x30e0 */
	union cmu_ebus_u_qch_con_sysreg_ebus_u_qch_s
		qch_con_sysreg_ebus_u_qch_s; /* offset : 0x30e4 */
	union cmu_ebus_u_qch_con_sysreg_buscsr_ebus_u_qch_s
		qch_con_sysreg_buscsr_ebus_u_qch_s; /* offset : 0x30e8 */
	union cmu_ebus_u_qch_con_tbu_dglue_cl0_ch2_qch_cg
		qch_con_tbu_dglue_cl0_ch2_qch_cg; /* offset : 0x30ec */
	union cmu_ebus_u_qch_con_tbu_dglue_cl0_ch2_qch_pd
		qch_con_tbu_dglue_cl0_ch2_qch_pd; /* offset : 0x30f0 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sc_mi_qch
		qch_con_lh_dcl0m_sc_mi_qch; /* offset : 0x30f4 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sc_si_qch
		qch_con_lh_dcl0s_sc_si_qch; /* offset : 0x30f8 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sp_si_qch
		qch_con_lh_dcl0s_sp_si_qch; /* offset : 0x30fc */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_qch_r
		qch_con_lh_dcl0s_sd0_si_qch_r; /* offset : 0x3100 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd0_si_qch_w
		qch_con_lh_dcl0s_sd0_si_qch_w; /* offset : 0x3104 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_qch_r
		qch_con_lh_dcl0s_sd1_si_qch_r; /* offset : 0x3108 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd1_si_qch_w
		qch_con_lh_dcl0s_sd1_si_qch_w; /* offset : 0x310c */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_qch_r
		qch_con_lh_dcl0s_sd2_si_qch_r; /* offset : 0x3110 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd2_si_qch_w
		qch_con_lh_dcl0s_sd2_si_qch_w; /* offset : 0x3114 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_qch_r
		qch_con_lh_dcl0s_sd3_si_qch_r; /* offset : 0x3118 */
	union cmu_ebus_u_qch_con_lh_dcl0s_sd3_si_qch_w
		qch_con_lh_dcl0s_sd3_si_qch_w; /* offset : 0x311c */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_qch_r
		qch_con_lh_dcl0m_sd0_mi_qch_r; /* offset : 0x3120 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd0_mi_qch_w
		qch_con_lh_dcl0m_sd0_mi_qch_w; /* offset : 0x3124 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_qch_r
		qch_con_lh_dcl0m_sd1_mi_qch_r; /* offset : 0x3128 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd1_mi_qch_w
		qch_con_lh_dcl0m_sd1_mi_qch_w; /* offset : 0x312c */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_qch_r
		qch_con_lh_dcl0m_sd2_mi_qch_r; /* offset : 0x3130 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd2_mi_qch_w
		qch_con_lh_dcl0m_sd2_mi_qch_w; /* offset : 0x3134 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_qch_r
		qch_con_lh_dcl0m_sd3_mi_qch_r; /* offset : 0x3138 */
	union cmu_ebus_u_qch_con_lh_dcl0m_sd3_mi_qch_w
		qch_con_lh_dcl0m_sd3_mi_qch_w; /* offset : 0x313c */
	union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_qch_r
		qch_con_lh_dcl0m_dd2_mi_qch_r; /* offset : 0x3140 */
	union cmu_ebus_u_qch_con_lh_dcl0m_dd2_mi_qch_w
		qch_con_lh_dcl0m_dd2_mi_qch_w; /* offset : 0x3144 */
	union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_qch_r
		qch_con_lh_dcl0s_dd2_si_qch_r; /* offset : 0x3148 */
	union cmu_ebus_u_qch_con_lh_dcl0s_dd2_si_qch_w
		qch_con_lh_dcl0s_dd2_si_qch_w; /* offset : 0x314c */
	union cmu_ebus_u_qch_con_lh_dcl0s_dp2_si_qch
		qch_con_lh_dcl0s_dp2_si_qch; /* offset : 0x3150 */
	union cmu_ebus_u_qch_con_lh_ebus_um_ast_si_qch
		qch_con_lh_ebus_um_ast_si_qch; /* offset : 0x3154 */
	union cmu_ebus_u_qch_con_lh_ebus_us_ast_mi_qch
		qch_con_lh_ebus_us_ast_mi_qch; /* offset : 0x3158 */
	union cmu_ebus_u_qch_con_lh_ebus_rs_ast0_si_qch
		qch_con_lh_ebus_rs_ast0_si_qch; /* offset : 0x315c */
	union cmu_ebus_u_qch_con_lh_ebus_rm_ast0_mi_qch
		qch_con_lh_ebus_rm_ast0_mi_qch; /* offset : 0x3160 */
};

enum EBUS_U_CLK_OUT {
	OSCCLK_EBUS_U,
	PLL_EBUS,
	CLK_EBUS_U_ACLK,
	CLK_EBUS_U_PCLK,
	CLK_RBC_H0,
	CLK_RBC_H1,
	CLK_EBUS_U_SH_LOW_CLK,
	CLK_EBUS_U_OSCCLK,
	EBUS_U_CLK_LH_SCAN_DST,
	EBUS_U_CLK_LH_SCAN_ETC,
};
