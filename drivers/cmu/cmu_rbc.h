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

union cmu_rbc_clk_con_div_div3_rbc_scan_500 {
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

union cmu_rbc_clk_con_div_div2_rbc_scan_750 {
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

union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_ick_afe_ref_ls_soc {
	struct {
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

union cmu_rbc_clk_con_gat_oscclk_rbc_cg {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rbc_clk_con_custom_clkmux {
	struct {
		uint32_t sel:1; /* [0:0] */
		uint32_t reserved0:31; /* [31:1] */
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

union cmu_rbc_qch_con_apb_async_rbc_m0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
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
	union cmu_rbc_clkout_con_blk_rbc_cmu_rbc_clkout
			clkout_con_blk_rbc_cmu_rbc_clkout; /* offset : 0x804 */
	uint32_t reserved_4[1022];
	union cmu_rbc_clk_con_div_div1_rbc_aclk0 clk_con_div_div1_rbc_aclk0; /* offset : 0x1800 */
	union cmu_rbc_clk_con_div_div1_rbc_pclk clk_con_div_div1_rbc_pclk; /* offset : 0x1804 */
	union cmu_rbc_clk_con_div_div3_rbc_scan_500 clk_con_div_div3_rbc_scan_500; /* offset : 0x1808 */
	union cmu_rbc_clk_con_div_div2_rbc_scan_750 clk_con_div_div2_rbc_scan_750; /* offset : 0x180c */
	uint32_t reserved_5[508];
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk
			clk_con_gat_clk_blk_rbc_uid_rbc_cmu_rbc_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst
			clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2004 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc
			clk_con_gat_clk_blk_rbc_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2008 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d0_mi_ipclkport_i_clk; /* offset : 0x200c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d0_si_ipclkport_i_clk; /* offset : 0x2010 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcs_d1_mi_ipclkport_i_clk; /* offset : 0x2014 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcm_d1_si_ipclkport_i_clk; /* offset : 0x2018 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p0_mi_ipclkport_i_clk; /* offset : 0x201c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcm_p0_si_ipclkport_i_clk; /* offset : 0x2020 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk
			clk_con_gat_clk_blk_rbc_uid_lh_rbcs_p_mi_ipclkport_i_clk; /* offset : 0x2024 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk
			clk_con_gat_clk_blk_rbc_uid_sysreg_rbc_ipclkport_pclk; /* offset : 0x2028 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk
			clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_i_apb_pclk; /* offset : 0x202c */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_ick_afe_ref_ls_soc
			clk_con_gat_clk_blk_rbc_uid_ucie_ss0_ipclkport_ick_afe_ref_ls_soc; /* offset : 0x2030 */
	union cmu_rbc_clk_con_gat_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk
			clk_con_gat_clk_blk_rbc_uid_rbc_m0_ipclkport_sclk; /* offset : 0x2034 */
	union cmu_rbc_clk_con_gat_oscclk_rbc_cg clk_con_gat_oscclk_rbc_cg; /* offset : 0x2038 */
	uint32_t reserved_6[49];
	union cmu_rbc_clk_con_custom_clkmux clk_con_custom_clkmux; /* offset : 0x2100 */
	uint32_t reserved_7[959];
	union cmu_rbc_qch_con_axi2apb_rbc_qch qch_con_axi2apb_rbc_qch; /* offset : 0x3000 */
	union cmu_rbc_qch_con_rstnsync_clk_rbc_aclk0_qch
			qch_con_rstnsync_clk_rbc_aclk0_qch; /* offset : 0x3004 */
	union cmu_rbc_qch_con_rstnsync_clk_rbc_pclk_qch
			qch_con_rstnsync_clk_rbc_pclk_qch; /* offset : 0x3008 */
	union cmu_rbc_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x300c */
	union cmu_rbc_qch_con_apb_async_rbc_m0_qch qch_con_apb_async_rbc_m0_qch; /* offset : 0x3010 */
	union cmu_rbc_qch_con_ucie_ss0_qch qch_con_ucie_ss0_qch; /* offset : 0x3014 */
	union cmu_rbc_qch_con_lh_rbcs_d0_mi_pch qch_con_lh_rbcs_d0_mi_pch; /* offset : 0x3018 */
	union cmu_rbc_qch_con_lh_rbcm_d0_si_pch qch_con_lh_rbcm_d0_si_pch; /* offset : 0x301c */
	union cmu_rbc_qch_con_lh_rbcs_d1_mi_pch qch_con_lh_rbcs_d1_mi_pch; /* offset : 0x3020 */
	union cmu_rbc_qch_con_lh_rbcm_d1_si_pch qch_con_lh_rbcm_d1_si_pch; /* offset : 0x3024 */
	union cmu_rbc_qch_con_lh_rbcs_p0_mi_pch qch_con_lh_rbcs_p0_mi_pch; /* offset : 0x3028 */
	union cmu_rbc_qch_con_lh_rbcm_p0_si_pch qch_con_lh_rbcm_p0_si_pch; /* offset : 0x302c */
	union cmu_rbc_qch_con_lh_rbcs_p_mi_pch qch_con_lh_rbcs_p_mi_pch; /* offset : 0x3030 */
	union cmu_rbc_qch_con_rbc_cmu_rbc_qch qch_con_rbc_cmu_rbc_qch; /* offset : 0x3034 */
	union cmu_rbc_qch_con_lh_rbcs_d0_mi_qch qch_con_lh_rbcs_d0_mi_qch; /* offset : 0x3038 */
	union cmu_rbc_qch_con_lh_rbcm_d0_si_qch qch_con_lh_rbcm_d0_si_qch; /* offset : 0x303c */
	union cmu_rbc_qch_con_lh_rbcs_d1_mi_qch qch_con_lh_rbcs_d1_mi_qch; /* offset : 0x3040 */
	union cmu_rbc_qch_con_lh_rbcm_d1_si_qch qch_con_lh_rbcm_d1_si_qch; /* offset : 0x3044 */
	union cmu_rbc_qch_con_lh_rbcs_p0_mi_qch qch_con_lh_rbcs_p0_mi_qch; /* offset : 0x3048 */
	union cmu_rbc_qch_con_lh_rbcm_p0_si_qch qch_con_lh_rbcm_p0_si_qch; /* offset : 0x304c */
	union cmu_rbc_qch_con_lh_rbcs_p_mi_qch qch_con_lh_rbcs_p_mi_qch; /* offset : 0x3050 */
	union cmu_rbc_qch_con_sysreg_rbc_qch qch_con_sysreg_rbc_qch; /* offset : 0x3054 */
	union cmu_rbc_qch_con_rbc_m0_qch qch_con_rbc_m0_qch; /* offset : 0x3058 */
};

enum RBC_CLK_OUT {
	OSCCLK_RBC,
	CLK_RBC_ACLK0,
	CLK_RBC_PCLK,
	RBC_CLK_LH_SCAN_DST,
	RBC_CLK_LH_SCAN_ETC,
};
