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

union cmu_wbus_d_pll_con0_pll_wbus_d {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_wbus_d_pll_con1_pll_wbus_d {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_wbus_d_pll_con2_pll_wbus_d {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_wbus_d_wbus_d_cmu_wbus_d_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_wbus_d_clkout_con_blk_wbus_d_cmu_wbus_d_clkout {
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

union cmu_wbus_d_clk_con_div_div1_wbus_d_aclk {
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

union cmu_wbus_d_clk_con_div_div3_wbus_d_pclk {
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

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_wbus_d_cmu_wbus_d_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_r_ipclkport_clk_main_sfr_wd {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_w_ipclkport_clk_main_sfr_wd {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_c_wbus_d_ipclkport_clk_533_w_d {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_wbus_noc_refclk_gen_ipclkport_i_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_sysreg_wbus_d_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_sysreg_buscsr_wbus_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_noc_d_wbus_d_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_noc_d_wbus_d_w_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_noc_c_wbus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_wbus_noc_refclk_gen_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_axi_rs_dcl1s_dd0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_axi_rs_dcl1s_dd1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_dti_sw_wbus_d_3x1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_dti_rs_lh_ebus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_dti_rs_lh_wbus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_dti_rs_tbu_dglue_cl1_ch0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_dti_rs_tbu_dglue_cl1_ch1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_axi2apb_wbus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_amba_ovrd_cl1_ch0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_amba_ovrd_cl1_ch1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_rstnsync_wbus_oscclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_rstnsync_wbus_aclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_wbus_dm_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_wbus_ds_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_ebus_dm_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_ebus_ds_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_pch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_pch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dp0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dp1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_wbus_d_cmu_wbus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_wbus_dm_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_wbus_ds_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_ebus_dm_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_ebus_ds_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_qch_r {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_qch_w {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dp0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_lh_dcl1s_dp1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch0_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch0_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch1_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch1_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_sysreg_wbus_d_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_sysreg_buscsr_wbus_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_wbus_d_qch_con_rstnsync_wbus_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_wbus_d {
	uint32_t reserved_1[64];
	union cmu_wbus_d_pll_con0_pll_wbus_d pll_con0_pll_wbus_d; /* offset : 0x100 */
	union cmu_wbus_d_pll_con1_pll_wbus_d pll_con1_pll_wbus_d; /* offset : 0x104 */
	union cmu_wbus_d_pll_con2_pll_wbus_d pll_con2_pll_wbus_d; /* offset : 0x108 */
	uint32_t reserved_2[445];
};

struct cmu_wbus_d_cont {
	union cmu_wbus_d_wbus_d_cmu_wbus_d_controller_option
		wbus_d_cmu_wbus_d_controller_option; /* offset : 0x800 */
	union cmu_wbus_d_clkout_con_blk_wbus_d_cmu_wbus_d_clkout
		clkout_con_blk_wbus_d_cmu_wbus_d_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
};

struct cmu_wbus_d_mux {
};

struct cmu_wbus_d_div {
	union cmu_wbus_d_clk_con_div_div1_wbus_d_aclk
		clk_con_div_div1_wbus_d_aclk; /* offset : 0x1800 */
	union cmu_wbus_d_clk_con_div_div3_wbus_d_pclk
		clk_con_div_div3_wbus_d_pclk; /* offset : 0x1804 */
	uint32_t reserved_4[510];
};

struct cmu_wbus_d_gate {
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_wbus_d_cmu_wbus_d_ipclkport_pclk
		clk_con_gat_clk_blk_wbus_d_uid_wbus_d_cmu_wbus_d_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_r_ipclkport_clk_main_sfr_wd
		clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_r_ipclkport_clk_main_sfr_wd;
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_w_ipclkport_clk_main_sfr_wd
		clk_con_gat_clk_blk_wbus_d_uid_noc_d_wbus_d_w_ipclkport_clk_main_sfr_wd;
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_noc_c_wbus_d_ipclkport_clk_533_w_d
		clk_con_gat_clk_blk_wbus_d_uid_noc_c_wbus_d_ipclkport_clk_533_w_d; /* offset : 0x200c */
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2010 */
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_wbus_d_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2014 */
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_wbus_noc_refclk_gen_ipclkport_i_osc_clk
		clk_con_gat_clk_blk_wbus_d_uid_wbus_noc_refclk_gen_ipclkport_i_osc_clk;
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_sysreg_wbus_d_ipclkport_pclk
		clk_con_gat_clk_blk_wbus_d_uid_sysreg_wbus_d_ipclkport_pclk; /* offset : 0x201c */
	union cmu_wbus_d_clk_con_gat_clk_blk_wbus_d_uid_sysreg_buscsr_wbus_ipclkport_pclk
		clk_con_gat_clk_blk_wbus_d_uid_sysreg_buscsr_wbus_ipclkport_pclk; /* offset : 0x2020 */
	uint32_t reserved_5[1015];
};

struct cmu_wbus_d_qch {
	union cmu_wbus_d_qch_con_noc_d_wbus_d_r_qch qch_con_noc_d_wbus_d_r_qch; /* offset : 0x3000 */
	union cmu_wbus_d_qch_con_noc_d_wbus_d_w_qch qch_con_noc_d_wbus_d_w_qch; /* offset : 0x3004 */
	union cmu_wbus_d_qch_con_noc_c_wbus_d_qch qch_con_noc_c_wbus_d_qch; /* offset : 0x3008 */
	union cmu_wbus_d_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x300c */
	union cmu_wbus_d_qch_con_wbus_noc_refclk_gen_qch
		qch_con_wbus_noc_refclk_gen_qch; /* offset : 0x3010 */
	union cmu_wbus_d_qch_con_axi_rs_dcl1s_dd0_qch
		qch_con_axi_rs_dcl1s_dd0_qch; /* offset : 0x3014 */
	union cmu_wbus_d_qch_con_axi_rs_dcl1s_dd1_qch
		qch_con_axi_rs_dcl1s_dd1_qch; /* offset : 0x3018 */
	union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_s
		qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_s; /* offset : 0x301c */
	union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_d
		qch_con_pe_wrapper_tbu_dglue_cl1_ch0_qch_d; /* offset : 0x3020 */
	union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_s
		qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_s; /* offset : 0x3024 */
	union cmu_wbus_d_qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_d
		qch_con_pe_wrapper_tbu_dglue_cl1_ch1_qch_d; /* offset : 0x3028 */
	union cmu_wbus_d_qch_con_dti_sw_wbus_d_3x1_qch
		qch_con_dti_sw_wbus_d_3x1_qch; /* offset : 0x302c */
	union cmu_wbus_d_qch_con_dti_rs_lh_ebus_d_qch
		qch_con_dti_rs_lh_ebus_d_qch; /* offset : 0x3030 */
	union cmu_wbus_d_qch_con_dti_rs_lh_wbus_d_qch
		qch_con_dti_rs_lh_wbus_d_qch; /* offset : 0x3034 */
	union cmu_wbus_d_qch_con_dti_rs_tbu_dglue_cl1_ch0_qch
		qch_con_dti_rs_tbu_dglue_cl1_ch0_qch; /* offset : 0x3038 */
	union cmu_wbus_d_qch_con_dti_rs_tbu_dglue_cl1_ch1_qch
		qch_con_dti_rs_tbu_dglue_cl1_ch1_qch; /* offset : 0x303c */
	union cmu_wbus_d_qch_con_axi2apb_wbus_d_qch qch_con_axi2apb_wbus_d_qch; /* offset : 0x3040 */
	union cmu_wbus_d_qch_con_amba_ovrd_cl1_ch0_qch
		qch_con_amba_ovrd_cl1_ch0_qch; /* offset : 0x3044 */
	union cmu_wbus_d_qch_con_amba_ovrd_cl1_ch1_qch
		qch_con_amba_ovrd_cl1_ch1_qch; /* offset : 0x3048 */
	union cmu_wbus_d_qch_con_rstnsync_wbus_oscclk_qch
		qch_con_rstnsync_wbus_oscclk_qch; /* offset : 0x304c */
	union cmu_wbus_d_qch_con_rstnsync_wbus_aclk_qch
		qch_con_rstnsync_wbus_aclk_qch; /* offset : 0x3050 */
	union cmu_wbus_d_qch_con_lh_wbus_dm_ast_si_pch
		qch_con_lh_wbus_dm_ast_si_pch; /* offset : 0x3054 */
	union cmu_wbus_d_qch_con_lh_wbus_ds_ast_mi_pch
		qch_con_lh_wbus_ds_ast_mi_pch; /* offset : 0x3058 */
	union cmu_wbus_d_qch_con_lh_ebus_dm_ast_mi_pch
		qch_con_lh_ebus_dm_ast_mi_pch; /* offset : 0x305c */
	union cmu_wbus_d_qch_con_lh_ebus_ds_ast_si_pch
		qch_con_lh_ebus_ds_ast_si_pch; /* offset : 0x3060 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_pch_r
		qch_con_lh_dcl1m_dd0_mi_pch_r; /* offset : 0x3064 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_pch_w
		qch_con_lh_dcl1m_dd0_mi_pch_w; /* offset : 0x3068 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_pch_r
		qch_con_lh_dcl1m_dd1_mi_pch_r; /* offset : 0x306c */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_pch_w
		qch_con_lh_dcl1m_dd1_mi_pch_w; /* offset : 0x3070 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_pch_r
		qch_con_lh_dcl1s_dd0_si_pch_r; /* offset : 0x3074 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_pch_w
		qch_con_lh_dcl1s_dd0_si_pch_w; /* offset : 0x3078 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_pch_r
		qch_con_lh_dcl1s_dd1_si_pch_r; /* offset : 0x307c */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_pch_w
		qch_con_lh_dcl1s_dd1_si_pch_w; /* offset : 0x3080 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dp0_si_pch qch_con_lh_dcl1s_dp0_si_pch; /* offset : 0x3084 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dp1_si_pch qch_con_lh_dcl1s_dp1_si_pch; /* offset : 0x3088 */
	union cmu_wbus_d_qch_con_wbus_d_cmu_wbus_d_qch
		qch_con_wbus_d_cmu_wbus_d_qch; /* offset : 0x308c */
	union cmu_wbus_d_qch_con_lh_wbus_dm_ast_si_qch
		qch_con_lh_wbus_dm_ast_si_qch; /* offset : 0x3090 */
	union cmu_wbus_d_qch_con_lh_wbus_ds_ast_mi_qch
		qch_con_lh_wbus_ds_ast_mi_qch; /* offset : 0x3094 */
	union cmu_wbus_d_qch_con_lh_ebus_dm_ast_mi_qch
		qch_con_lh_ebus_dm_ast_mi_qch; /* offset : 0x3098 */
	union cmu_wbus_d_qch_con_lh_ebus_ds_ast_si_qch
		qch_con_lh_ebus_ds_ast_si_qch; /* offset : 0x309c */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_qch_r
		qch_con_lh_dcl1m_dd0_mi_qch_r; /* offset : 0x30a0 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd0_mi_qch_w
		qch_con_lh_dcl1m_dd0_mi_qch_w; /* offset : 0x30a4 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_qch_r
		qch_con_lh_dcl1m_dd1_mi_qch_r; /* offset : 0x30a8 */
	union cmu_wbus_d_qch_con_lh_dcl1m_dd1_mi_qch_w
		qch_con_lh_dcl1m_dd1_mi_qch_w; /* offset : 0x30ac */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_qch_r
		qch_con_lh_dcl1s_dd0_si_qch_r; /* offset : 0x30b0 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd0_si_qch_w
		qch_con_lh_dcl1s_dd0_si_qch_w; /* offset : 0x30b4 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_qch_r
		qch_con_lh_dcl1s_dd1_si_qch_r; /* offset : 0x30b8 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dd1_si_qch_w
		qch_con_lh_dcl1s_dd1_si_qch_w; /* offset : 0x30bc */
	union cmu_wbus_d_qch_con_lh_dcl1s_dp0_si_qch qch_con_lh_dcl1s_dp0_si_qch; /* offset : 0x30c0 */
	union cmu_wbus_d_qch_con_lh_dcl1s_dp1_si_qch qch_con_lh_dcl1s_dp1_si_qch; /* offset : 0x30c4 */
	union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch0_qch_cg
		qch_con_tbu_dglue_cl1_ch0_qch_cg; /* offset : 0x30c8 */
	union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch0_qch_pd
		qch_con_tbu_dglue_cl1_ch0_qch_pd; /* offset : 0x30cc */
	union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch1_qch_cg
		qch_con_tbu_dglue_cl1_ch1_qch_cg; /* offset : 0x30d0 */
	union cmu_wbus_d_qch_con_tbu_dglue_cl1_ch1_qch_pd
		qch_con_tbu_dglue_cl1_ch1_qch_pd; /* offset : 0x30d4 */
	union cmu_wbus_d_qch_con_sysreg_wbus_d_qch qch_con_sysreg_wbus_d_qch; /* offset : 0x30d8 */
	union cmu_wbus_d_qch_con_sysreg_buscsr_wbus_qch
		qch_con_sysreg_buscsr_wbus_qch; /* offset : 0x30dc */
	union cmu_wbus_d_qch_con_rstnsync_wbus_pclk_qch
		qch_con_rstnsync_wbus_pclk_qch; /* offset : 0x30e0 */
};
