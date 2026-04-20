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

union cmu_rbc_pll_con0_pll_ctrl_rbc0 {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_rbc_pll_con1_pll_ctrl_rbc0 {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_rbc_pll_con2_pll_ctrl_rbc0 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_rbc_pll_con0_pll_ctrl_rbc2 {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_rbc_pll_con1_pll_ctrl_rbc2 {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_rbc_pll_con2_pll_ctrl_rbc2 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_rbc_rbc_cmu_rbc_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_rbc_clkout_con_blk_rbc_cmu_rbc_clkout {
	struct {
		uint32_t div_ratio:4; /* [3:0] */
		uint32_t reserved0:4; /* [7:4] */
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

union cmu_rbc_clk_con_div_div1_rbc_aclk0 {
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

union cmu_rbc_clk_con_div_div1_rbc_pclk {
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

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_axi2apb_rbc_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_rstnsync_clk_rbc_aclk0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_rstnsync_clk_rbc_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_ucie_ss0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_d0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_d0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_d1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_d1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_p0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_p0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_p_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_rbc_cmu_rbc_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_d0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_d0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_d1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_d1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_p0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcm_p0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_lh_rbcs_p_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_sysreg_rbc_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_apb_async_rbc_m0_qch_clks {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_apb_async_rbc_m0_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_apb_async_rbc_m0_qch_clkm {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_qch_con_rbc_m0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rbc_queue_ctrl_reg_blk_rbc_cmu_rbc {
	struct {
		uint32_t reserved0:12; /* [11:0] */
		uint32_t queue_wait_count:4; /* [15:12] */
		uint32_t reserved1:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_pll_ctrl_rbc0 {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_pll_ctrl_rbc2 {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_blk_rbc_cmu_rbc_clkout {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_div1_rbc_aclk0 {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_div1_rbc_pclk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_rbc_cmu_rbc_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_axi2apb_rbc_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_rstnsync_clk_rbc_aclk0_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_rstnsync_clk_rbc_pclk_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d0_mi_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d0_mi_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d0_si_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d0_si_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d1_mi_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d1_mi_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d1_si_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d1_si_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p0_mi_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p0_mi_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_p0_si_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_p0_si_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p_mi_pch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p_mi_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_sysreg_rbc_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_clks {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_pwr {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_clkm {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_ucie_ss0_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union cmu_rbc_dbg_nfo_qch_con_rbc_m0_qch {
	struct {
		uint32_t debug_info:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

struct cmu_rbc {
	uint32_t reserved_1[64];
	union cmu_rbc_pll_con0_pll_ctrl_rbc0 pll_con0_pll_ctrl_rbc0; /* offset : 0x100 */
	union cmu_rbc_pll_con1_pll_ctrl_rbc0 pll_con1_pll_ctrl_rbc0; /* offset : 0x104 */
	union cmu_rbc_pll_con2_pll_ctrl_rbc0 pll_con2_pll_ctrl_rbc0; /* offset : 0x108 */
	uint32_t reserved_2[3];
	union cmu_rbc_pll_con0_pll_ctrl_rbc2 pll_con0_pll_ctrl_rbc2; /* offset : 0x118 */
	union cmu_rbc_pll_con1_pll_ctrl_rbc2 pll_con1_pll_ctrl_rbc2; /* offset : 0x11c */
	union cmu_rbc_pll_con2_pll_ctrl_rbc2 pll_con2_pll_ctrl_rbc2; /* offset : 0x120 */
	uint32_t reserved_3[439];
	union cmu_rbc_rbc_cmu_rbc_controller_option rbc_cmu_rbc_controller_option; /* offset : 0x800 */
	union cmu_rbc_clkout_con_blk_rbc_cmu_rbc_clkout clkout_con_blk_rbc_cmu_rbc_clkout; /* offset : 0x804 */
	uint32_t reserved_4[1022];
	union cmu_rbc_clk_con_div_div1_rbc_aclk0 clk_con_div_div1_rbc_aclk0; /* offset : 0x1800 */
	union cmu_rbc_clk_con_div_div1_rbc_pclk clk_con_div_div1_rbc_pclk; /* offset : 0x1804 */
	uint32_t reserved_5[510];
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk clk_con_gat_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2004 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2008 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk; /* offset : 0x200c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk; /* offset : 0x2010 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk; /* offset : 0x2014 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk; /* offset : 0x2018 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk; /* offset : 0x201c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk; /* offset : 0x2020 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk; /* offset : 0x2024 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk clk_con_gat_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk; /* offset : 0x2028 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s; /* offset : 0x202c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m clk_con_gat_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m; /* offset : 0x2030 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk; /* offset : 0x2034 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk clk_con_gat_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk; /* offset : 0x2038 */
	uint32_t reserved_6[1009];
	union cmu_rbc_qch_con_axi2apb_rbc_qch qch_con_axi2apb_rbc_qch; /* offset : 0x3000 */
	union cmu_rbc_qch_con_rstnsync_clk_rbc_aclk0_qch qch_con_rstnsync_clk_rbc_aclk0_qch; /* offset : 0x3004 */
	union cmu_rbc_qch_con_rstnsync_clk_rbc_pclk_qch qch_con_rstnsync_clk_rbc_pclk_qch; /* offset : 0x3008 */
	union cmu_rbc_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x300c */
	union cmu_rbc_qch_con_ucie_ss0_qch qch_con_ucie_ss0_qch; /* offset : 0x3010 */
	union cmu_rbc_qch_con_lh_rbcs_d0_mi_pch qch_con_lh_rbcs_d0_mi_pch; /* offset : 0x3014 */
	union cmu_rbc_qch_con_lh_rbcm_d0_si_pch qch_con_lh_rbcm_d0_si_pch; /* offset : 0x3018 */
	union cmu_rbc_qch_con_lh_rbcs_d1_mi_pch qch_con_lh_rbcs_d1_mi_pch; /* offset : 0x301c */
	union cmu_rbc_qch_con_lh_rbcm_d1_si_pch qch_con_lh_rbcm_d1_si_pch; /* offset : 0x3020 */
	union cmu_rbc_qch_con_lh_rbcs_p0_mi_pch qch_con_lh_rbcs_p0_mi_pch; /* offset : 0x3024 */
	union cmu_rbc_qch_con_lh_rbcm_p0_si_pch qch_con_lh_rbcm_p0_si_pch; /* offset : 0x3028 */
	union cmu_rbc_qch_con_lh_rbcs_p_mi_pch qch_con_lh_rbcs_p_mi_pch; /* offset : 0x302c */
	union cmu_rbc_qch_con_rbc_cmu_rbc_qch qch_con_rbc_cmu_rbc_qch; /* offset : 0x3030 */
	union cmu_rbc_qch_con_lh_rbcs_d0_mi_qch qch_con_lh_rbcs_d0_mi_qch; /* offset : 0x3034 */
	union cmu_rbc_qch_con_lh_rbcm_d0_si_qch qch_con_lh_rbcm_d0_si_qch; /* offset : 0x3038 */
	union cmu_rbc_qch_con_lh_rbcs_d1_mi_qch qch_con_lh_rbcs_d1_mi_qch; /* offset : 0x303c */
	union cmu_rbc_qch_con_lh_rbcm_d1_si_qch qch_con_lh_rbcm_d1_si_qch; /* offset : 0x3040 */
	union cmu_rbc_qch_con_lh_rbcs_p0_mi_qch qch_con_lh_rbcs_p0_mi_qch; /* offset : 0x3044 */
	union cmu_rbc_qch_con_lh_rbcm_p0_si_qch qch_con_lh_rbcm_p0_si_qch; /* offset : 0x3048 */
	union cmu_rbc_qch_con_lh_rbcs_p_mi_qch qch_con_lh_rbcs_p_mi_qch; /* offset : 0x304c */
	union cmu_rbc_qch_con_sysreg_rbc_qch qch_con_sysreg_rbc_qch; /* offset : 0x3050 */
	union cmu_rbc_qch_con_apb_async_rbc_m0_qch_clks qch_con_apb_async_rbc_m0_qch_clks; /* offset : 0x3054 */
	union cmu_rbc_qch_con_apb_async_rbc_m0_qch_pwr qch_con_apb_async_rbc_m0_qch_pwr; /* offset : 0x3058 */
	union cmu_rbc_qch_con_apb_async_rbc_m0_qch_clkm qch_con_apb_async_rbc_m0_qch_clkm; /* offset : 0x305c */
	union cmu_rbc_qch_con_rbc_m0_qch qch_con_rbc_m0_qch; /* offset : 0x3060 */
	uint32_t reserved_7[743];
	union cmu_rbc_queue_ctrl_reg_blk_rbc_cmu_rbc queue_ctrl_reg_blk_rbc_cmu_rbc; /* offset : 0x3c00 */
	uint32_t reserved_8[319];
	union cmu_rbc_dbg_nfo_pll_ctrl_rbc0 dbg_nfo_pll_ctrl_rbc0; /* offset : 0x4100 */
	uint32_t reserved_9;
	union cmu_rbc_dbg_nfo_pll_ctrl_rbc2 dbg_nfo_pll_ctrl_rbc2; /* offset : 0x4108 */
	uint32_t reserved_10[449];
	union cmu_rbc_dbg_nfo_blk_rbc_cmu_rbc_clkout dbg_nfo_blk_rbc_cmu_rbc_clkout; /* offset : 0x4810 */
	uint32_t reserved_11[1019];
	union cmu_rbc_dbg_nfo_div1_rbc_aclk0 dbg_nfo_div1_rbc_aclk0; /* offset : 0x5800 */
	union cmu_rbc_dbg_nfo_div1_rbc_pclk dbg_nfo_div1_rbc_pclk; /* offset : 0x5804 */
	uint32_t reserved_12[510];
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk dbg_nfo_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk; /* offset : 0x6000 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x6004 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc dbg_nfo_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x6008 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk; /* offset : 0x600c */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk; /* offset : 0x6010 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk; /* offset : 0x6014 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk; /* offset : 0x6018 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk; /* offset : 0x601c */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk; /* offset : 0x6020 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk dbg_nfo_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk; /* offset : 0x6024 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk dbg_nfo_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk; /* offset : 0x6028 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_s; /* offset : 0x602c */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m dbg_nfo_clk_blk_rbc_uid_apb_async_rbc_m0_ipclkport_clk_m; /* offset : 0x6030 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk dbg_nfo_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk; /* offset : 0x6034 */
	union cmu_rbc_dbg_nfo_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk dbg_nfo_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk; /* offset : 0x6038 */
	uint32_t reserved_13[1009];
	union cmu_rbc_dbg_nfo_qch_con_rbc_cmu_rbc_qch dbg_nfo_qch_con_rbc_cmu_rbc_qch; /* offset : 0x7000 */
	union cmu_rbc_dbg_nfo_qch_con_axi2apb_rbc_qch dbg_nfo_qch_con_axi2apb_rbc_qch; /* offset : 0x7004 */
	union cmu_rbc_dbg_nfo_qch_con_rstnsync_clk_rbc_aclk0_qch dbg_nfo_qch_con_rstnsync_clk_rbc_aclk0_qch; /* offset : 0x7008 */
	union cmu_rbc_dbg_nfo_qch_con_rstnsync_clk_rbc_pclk_qch dbg_nfo_qch_con_rstnsync_clk_rbc_pclk_qch; /* offset : 0x700c */
	union cmu_rbc_dbg_nfo_qch_con_lh_qch dbg_nfo_qch_con_lh_qch; /* offset : 0x7010 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d0_mi_pch dbg_nfo_qch_con_lh_rbcs_d0_mi_pch; /* offset : 0x7014 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d0_mi_qch dbg_nfo_qch_con_lh_rbcs_d0_mi_qch; /* offset : 0x7018 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d0_si_pch dbg_nfo_qch_con_lh_rbcm_d0_si_pch; /* offset : 0x701c */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d0_si_qch dbg_nfo_qch_con_lh_rbcm_d0_si_qch; /* offset : 0x7020 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d1_mi_pch dbg_nfo_qch_con_lh_rbcs_d1_mi_pch; /* offset : 0x7024 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_d1_mi_qch dbg_nfo_qch_con_lh_rbcs_d1_mi_qch; /* offset : 0x7028 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d1_si_pch dbg_nfo_qch_con_lh_rbcm_d1_si_pch; /* offset : 0x702c */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_d1_si_qch dbg_nfo_qch_con_lh_rbcm_d1_si_qch; /* offset : 0x7030 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p0_mi_pch dbg_nfo_qch_con_lh_rbcs_p0_mi_pch; /* offset : 0x7034 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p0_mi_qch dbg_nfo_qch_con_lh_rbcs_p0_mi_qch; /* offset : 0x7038 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_p0_si_pch dbg_nfo_qch_con_lh_rbcm_p0_si_pch; /* offset : 0x703c */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcm_p0_si_qch dbg_nfo_qch_con_lh_rbcm_p0_si_qch; /* offset : 0x7040 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p_mi_pch dbg_nfo_qch_con_lh_rbcs_p_mi_pch; /* offset : 0x7044 */
	union cmu_rbc_dbg_nfo_qch_con_lh_rbcs_p_mi_qch dbg_nfo_qch_con_lh_rbcs_p_mi_qch; /* offset : 0x7048 */
	union cmu_rbc_dbg_nfo_qch_con_sysreg_rbc_qch dbg_nfo_qch_con_sysreg_rbc_qch; /* offset : 0x704c */
	union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_clks dbg_nfo_qch_con_apb_async_rbc_m0_qch_clks; /* offset : 0x7050 */
	union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_pwr dbg_nfo_qch_con_apb_async_rbc_m0_qch_pwr; /* offset : 0x7054 */
	union cmu_rbc_dbg_nfo_qch_con_apb_async_rbc_m0_qch_clkm dbg_nfo_qch_con_apb_async_rbc_m0_qch_clkm; /* offset : 0x7058 */
	union cmu_rbc_dbg_nfo_qch_con_ucie_ss0_qch dbg_nfo_qch_con_ucie_ss0_qch; /* offset : 0x705c */
	union cmu_rbc_dbg_nfo_qch_con_rbc_m0_qch dbg_nfo_qch_con_rbc_m0_qch; /* offset : 0x7060 */
};
