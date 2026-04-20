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

union cmu_nbus_l_pll_con0_pll_nbus_l {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_nbus_l_pll_con1_pll_nbus_l {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_nbus_l_pll_con2_pll_nbus_l {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_nbus_l_nbus_l_cmu_nbus_l_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_nbus_l_clkout_con_blk_nbus_l_cmu_nbus_l_clkout {
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

union cmu_nbus_l_clk_con_div_div1_nbus_l_aclk {
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

union cmu_nbus_l_clk_con_div_div3_nbus_l_pclk {
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

union cmu_nbus_l_clk_con_div_div2_nbus_l_gclk {
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

union cmu_nbus_l_clk_con_div_div2_nbus_l_rbdma_bist {
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

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_nbus_l_cmu_nbus_l_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_d_nbus_l_r_ipclkport_clk_main_sfr_nl {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_800_gic {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_533_n_l {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_nbus_l_noc_refclk_gen_ipclkport_i_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gic600_ipclkport_gicclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp0s_ast_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp0m_ast_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp1s_ast_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp1m_ast_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_sysreg_buscsr_nbus_l_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_sysreg_nbus_l_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_noc_d_nbus_l_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_noc_c_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rstnsync_nbus_oscclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rstnsync_nbus_aclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rstnsync_nbus_gclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rstnsync_nbus_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_nbus_l_noc_refclk_gen_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_dti_sw_nbus_l_4x1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rbdma_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_rbdma_bist_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_noc_acp_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_dti_rs_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_amba_ovrd_rbdma0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_amba_ovrd_rbdma1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_amba_ovrd_rbdma2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_amba_ovrd_rbdma3_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_gic600_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_gpio_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_axi2apb_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d2_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d3_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_ls_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0m_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1s_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1m_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0m_d_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_d_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1m_d_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1s_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_nbus_l_cmu_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_0_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_0_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_1_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_1_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_2_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_2_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_3_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_tbu_rbdma_3_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d2_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_d3_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_lm_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_nbus_ls_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0m_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1s_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1m_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0m_d_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_d_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp0s_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1m_d_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_lh_cp1s_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_sysreg_buscsr_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_gpio_nbus_l_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_l_qch_con_sysreg_nbus_l_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_nbus_l {
	uint32_t reserved_1[64];
	union cmu_nbus_l_pll_con0_pll_nbus_l pll_con0_pll_nbus_l; /* offset : 0x100 */
	union cmu_nbus_l_pll_con1_pll_nbus_l pll_con1_pll_nbus_l; /* offset : 0x104 */
	union cmu_nbus_l_pll_con2_pll_nbus_l pll_con2_pll_nbus_l; /* offset : 0x108 */
	uint32_t reserved_2[445];
};

struct cmu_nbus_l_cont {
	union cmu_nbus_l_nbus_l_cmu_nbus_l_controller_option
		nbus_l_cmu_nbus_l_controller_option; /* offset : 0x800 */
	union cmu_nbus_l_clkout_con_blk_nbus_l_cmu_nbus_l_clkout
		clkout_con_blk_nbus_l_cmu_nbus_l_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
};

struct cmu_nbus_l_mux {
};

struct cmu_nbus_l_div {
	union cmu_nbus_l_clk_con_div_div1_nbus_l_aclk
		clk_con_div_div1_nbus_l_aclk; /* offset : 0x1800 */
	union cmu_nbus_l_clk_con_div_div3_nbus_l_pclk
		clk_con_div_div3_nbus_l_pclk; /* offset : 0x1804 */
	union cmu_nbus_l_clk_con_div_div2_nbus_l_gclk
		clk_con_div_div2_nbus_l_gclk; /* offset : 0x1808 */
	uint32_t reserved_4;
	union cmu_nbus_l_clk_con_div_div2_nbus_l_rbdma_bist
		clk_con_div_div2_nbus_l_rbdma_bist; /* offset : 0x1810 */
	uint32_t reserved_5[507];
};

struct cmu_nbus_l_gate {
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_nbus_l_cmu_nbus_l_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_l_uid_nbus_l_cmu_nbus_l_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_d_nbus_l_r_ipclkport_clk_main_sfr_nl
		clk_con_gat_clk_blk_nbus_l_uid_noc_d_nbus_l_r_ipclkport_clk_main_sfr_nl; /*offset:0x2004*/
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_800_gic
		clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_800_gic; /* offset : 0x2008 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_533_n_l
		clk_con_gat_clk_blk_nbus_l_uid_noc_c_nbus_l_ipclkport_clk_533_n_l; /* offset : 0x200c */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2010 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_nbus_l_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2014 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_nbus_l_noc_refclk_gen_ipclkport_i_osc_clk
		clk_con_gat_clk_blk_nbus_l_uid_nbus_l_noc_refclk_gen_ipclkport_i_osc_clk; /*offset:0x2018*/
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gic600_ipclkport_gicclk
		clk_con_gat_clk_blk_nbus_l_uid_gic600_ipclkport_gicclk; /* offset : 0x201c */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp0s_ast_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_l_uid_lh_cp0s_ast_si_ipclkport_i_clk; /* offset : 0x2020 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp0m_ast_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_l_uid_lh_cp0m_ast_mi_ipclkport_i_clk; /* offset : 0x2024 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp1s_ast_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_l_uid_lh_cp1s_ast_si_ipclkport_i_clk; /* offset : 0x2028 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_lh_cp1m_ast_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_l_uid_lh_cp1m_ast_mi_ipclkport_i_clk; /* offset : 0x202c */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_sysreg_buscsr_nbus_l_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_l_uid_sysreg_buscsr_nbus_l_ipclkport_pclk; /* offset : 0x2030 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_oscclk
		clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_oscclk; /* offset : 0x2034 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_l_uid_gpio_nbus_l_ipclkport_pclk; /* offset : 0x2038 */
	union cmu_nbus_l_clk_con_gat_clk_blk_nbus_l_uid_sysreg_nbus_l_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_l_uid_sysreg_nbus_l_ipclkport_pclk; /* offset : 0x203c */
	uint32_t reserved_6[1008];
};

struct cmu_nbus_l_qch {
	union cmu_nbus_l_qch_con_noc_d_nbus_l_r_qch qch_con_noc_d_nbus_l_r_qch; /* offset : 0x3000 */
	union cmu_nbus_l_qch_con_noc_c_nbus_l_qch qch_con_noc_c_nbus_l_qch; /* offset : 0x3004 */
	union cmu_nbus_l_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3008 */
	union cmu_nbus_l_qch_con_rstnsync_nbus_oscclk_qch
		qch_con_rstnsync_nbus_oscclk_qch; /* offset : 0x300c */
	union cmu_nbus_l_qch_con_rstnsync_nbus_aclk_qch
		qch_con_rstnsync_nbus_aclk_qch; /* offset : 0x3010 */
	union cmu_nbus_l_qch_con_rstnsync_nbus_gclk_qch
		qch_con_rstnsync_nbus_gclk_qch; /* offset : 0x3014 */
	union cmu_nbus_l_qch_con_rstnsync_nbus_pclk_qch
		qch_con_rstnsync_nbus_pclk_qch; /* offset : 0x3018 */
	union cmu_nbus_l_qch_con_nbus_l_noc_refclk_gen_qch
		qch_con_nbus_l_noc_refclk_gen_qch; /* offset : 0x301c */
	union cmu_nbus_l_qch_con_dti_sw_nbus_l_4x1_qch
		qch_con_dti_sw_nbus_l_4x1_qch; /* offset : 0x3020 */
	union cmu_nbus_l_qch_con_rbdma_qch qch_con_rbdma_qch; /* offset : 0x3024 */
	union cmu_nbus_l_qch_con_rbdma_bist_qch qch_con_rbdma_bist_qch; /* offset : 0x3028 */
	union cmu_nbus_l_qch_con_noc_acp_qch qch_con_noc_acp_qch; /* offset : 0x302c */
	union cmu_nbus_l_qch_con_dti_rs_qch qch_con_dti_rs_qch; /* offset : 0x3030 */
	union cmu_nbus_l_qch_con_amba_ovrd_rbdma0_qch
		qch_con_amba_ovrd_rbdma0_qch; /* offset : 0x3034 */
	union cmu_nbus_l_qch_con_amba_ovrd_rbdma1_qch
		qch_con_amba_ovrd_rbdma1_qch; /* offset : 0x3038 */
	union cmu_nbus_l_qch_con_amba_ovrd_rbdma2_qch
		qch_con_amba_ovrd_rbdma2_qch; /* offset : 0x303c */
	union cmu_nbus_l_qch_con_amba_ovrd_rbdma3_qch
		qch_con_amba_ovrd_rbdma3_qch; /* offset : 0x3040 */
	union cmu_nbus_l_qch_con_gic600_qch qch_con_gic600_qch; /* offset : 0x3044 */
	union cmu_nbus_l_qch_con_gpio_nbus_l_qch qch_con_gpio_nbus_l_qch; /* offset : 0x3048 */
	union cmu_nbus_l_qch_con_axi2apb_nbus_l_qch qch_con_axi2apb_nbus_l_qch; /* offset : 0x304c */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d0_si_pch
		qch_con_lh_nbus_lm_d0_si_pch; /* offset : 0x3050 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d1_si_pch
		qch_con_lh_nbus_lm_d1_si_pch; /* offset : 0x3054 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d2_si_pch
		qch_con_lh_nbus_lm_d2_si_pch; /* offset : 0x3058 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d3_si_pch
		qch_con_lh_nbus_lm_d3_si_pch; /* offset : 0x305c */
	union cmu_nbus_l_qch_con_lh_nbus_lm_ast_si_pch
		qch_con_lh_nbus_lm_ast_si_pch; /* offset : 0x3060 */
	union cmu_nbus_l_qch_con_lh_nbus_ls_ast_mi_pch
		qch_con_lh_nbus_ls_ast_mi_pch; /* offset : 0x3064 */
	union cmu_nbus_l_qch_con_lh_cp0s_ast_si_pch qch_con_lh_cp0s_ast_si_pch; /* offset : 0x3068 */
	union cmu_nbus_l_qch_con_lh_cp0m_ast_mi_pch qch_con_lh_cp0m_ast_mi_pch; /* offset : 0x306c */
	union cmu_nbus_l_qch_con_lh_cp1s_ast_si_pch qch_con_lh_cp1s_ast_si_pch; /* offset : 0x3070 */
	union cmu_nbus_l_qch_con_lh_cp1m_ast_mi_pch qch_con_lh_cp1m_ast_mi_pch; /* offset : 0x3074 */
	union cmu_nbus_l_qch_con_lh_cp0m_d_mi_pch qch_con_lh_cp0m_d_mi_pch; /* offset : 0x3078 */
	union cmu_nbus_l_qch_con_lh_cp0s_d_si_pch qch_con_lh_cp0s_d_si_pch; /* offset : 0x307c */
	union cmu_nbus_l_qch_con_lh_cp0s_p_si_pch qch_con_lh_cp0s_p_si_pch; /* offset : 0x3080 */
	union cmu_nbus_l_qch_con_lh_cp1m_d_mi_pch qch_con_lh_cp1m_d_mi_pch; /* offset : 0x3084 */
	union cmu_nbus_l_qch_con_lh_cp1s_p_si_pch qch_con_lh_cp1s_p_si_pch; /* offset : 0x3088 */
	union cmu_nbus_l_qch_con_nbus_l_cmu_nbus_l_qch
		qch_con_nbus_l_cmu_nbus_l_qch; /* offset : 0x308c */
	union cmu_nbus_l_qch_con_tbu_rbdma_0_qch_cg qch_con_tbu_rbdma_0_qch_cg; /* offset : 0x3090 */
	union cmu_nbus_l_qch_con_tbu_rbdma_0_qch_pd qch_con_tbu_rbdma_0_qch_pd; /* offset : 0x3094 */
	union cmu_nbus_l_qch_con_tbu_rbdma_1_qch_cg qch_con_tbu_rbdma_1_qch_cg; /* offset : 0x3098 */
	union cmu_nbus_l_qch_con_tbu_rbdma_1_qch_pd qch_con_tbu_rbdma_1_qch_pd; /* offset : 0x309c */
	union cmu_nbus_l_qch_con_tbu_rbdma_2_qch_cg qch_con_tbu_rbdma_2_qch_cg; /* offset : 0x30a0 */
	union cmu_nbus_l_qch_con_tbu_rbdma_2_qch_pd qch_con_tbu_rbdma_2_qch_pd; /* offset : 0x30a4 */
	union cmu_nbus_l_qch_con_tbu_rbdma_3_qch_cg qch_con_tbu_rbdma_3_qch_cg; /* offset : 0x30a8 */
	union cmu_nbus_l_qch_con_tbu_rbdma_3_qch_pd qch_con_tbu_rbdma_3_qch_pd; /* offset : 0x30ac */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d0_si_qch
		qch_con_lh_nbus_lm_d0_si_qch; /* offset : 0x30b0 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d1_si_qch
		qch_con_lh_nbus_lm_d1_si_qch; /* offset : 0x30b4 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d2_si_qch
		qch_con_lh_nbus_lm_d2_si_qch; /* offset : 0x30b8 */
	union cmu_nbus_l_qch_con_lh_nbus_lm_d3_si_qch
		qch_con_lh_nbus_lm_d3_si_qch; /* offset : 0x30bc */
	union cmu_nbus_l_qch_con_lh_nbus_lm_ast_si_qch
		qch_con_lh_nbus_lm_ast_si_qch; /* offset : 0x30c0 */
	union cmu_nbus_l_qch_con_lh_nbus_ls_ast_mi_qch
		qch_con_lh_nbus_ls_ast_mi_qch; /* offset : 0x30c4 */
	union cmu_nbus_l_qch_con_lh_cp0s_ast_si_qch qch_con_lh_cp0s_ast_si_qch; /* offset : 0x30c8 */
	union cmu_nbus_l_qch_con_lh_cp0m_ast_mi_qch qch_con_lh_cp0m_ast_mi_qch; /* offset : 0x30cc */
	union cmu_nbus_l_qch_con_lh_cp1s_ast_si_qch qch_con_lh_cp1s_ast_si_qch; /* offset : 0x30d0 */
	union cmu_nbus_l_qch_con_lh_cp1m_ast_mi_qch qch_con_lh_cp1m_ast_mi_qch; /* offset : 0x30d4 */
	union cmu_nbus_l_qch_con_lh_cp0m_d_mi_qch qch_con_lh_cp0m_d_mi_qch; /* offset : 0x30d8 */
	union cmu_nbus_l_qch_con_lh_cp0s_d_si_qch qch_con_lh_cp0s_d_si_qch; /* offset : 0x30dc */
	union cmu_nbus_l_qch_con_lh_cp0s_p_si_qch qch_con_lh_cp0s_p_si_qch; /* offset : 0x30e0 */
	union cmu_nbus_l_qch_con_lh_cp1m_d_mi_qch qch_con_lh_cp1m_d_mi_qch; /* offset : 0x30e4 */
	union cmu_nbus_l_qch_con_lh_cp1s_p_si_qch qch_con_lh_cp1s_p_si_qch; /* offset : 0x30e8 */
	union cmu_nbus_l_qch_con_sysreg_buscsr_nbus_l_qch
		qch_con_sysreg_buscsr_nbus_l_qch; /* offset : 0x30ec */
	union cmu_nbus_l_qch_con_gpio_nbus_l_qch_s qch_con_gpio_nbus_l_qch_s; /* offset : 0x30f0 */
	union cmu_nbus_l_qch_con_sysreg_nbus_l_qch qch_con_sysreg_nbus_l_qch; /* offset : 0x30f4 */
};
