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

union cmu_nbus_u_pll_con0_pll_nbus_u {
	struct {
		uint32_t reserved0:4; /* [3:0] */
		uint32_t mux_sel:1; /* [4:4] */
		uint32_t reserved1:2; /* [6:5] */
		uint32_t busy:1; /* [7:7] */
		uint32_t reserved2:24; /* [31:8] */
	};
	uint32_t val;
};

union cmu_nbus_u_pll_con1_pll_nbus_u {
	struct {
		uint32_t reserved0:5; /* [4:0] */
		uint32_t ignore_req_sysclk:1; /* [5:5] */
		uint32_t reserved1:26; /* [31:6] */
	};
	uint32_t val;
};

union cmu_nbus_u_pll_con2_pll_nbus_u {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:1; /* [29:29] */
		uint32_t override_by_hch:1; /* [30:30] */
		uint32_t reserved2:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_nbus_u_nbus_u_cmu_nbus_u_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_nbus_u_clkout_con_blk_nbus_u_cmu_nbus_u_clkout {
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

union cmu_nbus_u_clk_con_mux_mux_nbus_u_tclk {
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

union cmu_nbus_u_clk_con_div_div1_nbus_u_aclk {
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

union cmu_nbus_u_clk_con_div_div1_nbus_u_tclk {
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

union cmu_nbus_u_clk_con_div_div2_nbus_u_cmgr_bist {
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

union cmu_nbus_u_clk_con_div_div3_nbus_u_pclk {
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

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_nbus_u_cmu_nbus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_noc_d_nbus_u_r_ipclkport_clk_main_sfr_nu {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_noc_c_nbus_u_ipclkport_clk_533_n_u {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_nbus_u_noc_refclk_gen_ipclkport_i_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_peri0m_p_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_peri0s_p_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_apb_nbuss_g_mi_ipclkport_clk_m {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t0_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t1_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t2_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_pclkdbg {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_tsclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_sysreg_buscsr_nbus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_sysreg_nbus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_noc_d_nbus_u_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_noc_c_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_rstnsync_nbus_u_oscclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_nbus_u_noc_refclk_gen_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_refclk_div_0_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_refclk_div_1_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_refclk_div_2_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_rstnsync_nbus_u_aclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_rstnsync_nbus_u_cssys_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_rstnsync_nbus_u_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_rstnsync_nbus_u_tsclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_amba_ovrd_cmgr_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_cmgr_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_cmgr_bist_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_cssys_nbus_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_noc_rbc_v0_r_sw_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_dti_sw_nbus_u_2x1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_dti_rs_pcie_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_dti_rs_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_dti_rs_nd_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi_rs_rbc_v00s_d0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi_rs_rbc_v00s_d1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi_rs_rbc_v01s_d0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi_rs_rbc_v01s_d1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_detour_ch0_en_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_detour_ch1_en_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_detour_ch2_en_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_detour_ch3_en_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_detour_en_sync_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi2apb_dbg_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_axi2apb_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_peri0m_p_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_peri0s_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_d_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pciem_d_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rots_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_d0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_d1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_p0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_p0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_d0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_d1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_d0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_d1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_p0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_p0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_d0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_d1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_d0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_d1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t2_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbus_um_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbus_us_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rots_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pciem_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_nbus_u_cmu_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_peri0m_p_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_peri0s_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_d_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pciem_d_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rots_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_d0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_d1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_p0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_p0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_d0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00m_d1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_d0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v00s_d1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_p0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_p0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_d0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01m_d1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_d0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rbc_v01s_d1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_apb_nbuss_g_mi_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbusm_t2_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbus_um_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_nbus_us_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rots_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_rotm_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pcies_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_lh_pciem_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_sysreg_buscsr_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_nbus_u_qch_con_sysreg_nbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_nbus_u {
	uint32_t reserved_1[64];
	union cmu_nbus_u_pll_con0_pll_nbus_u pll_con0_pll_nbus_u; /* offset : 0x100 */
	union cmu_nbus_u_pll_con1_pll_nbus_u pll_con1_pll_nbus_u; /* offset : 0x104 */
	union cmu_nbus_u_pll_con2_pll_nbus_u pll_con2_pll_nbus_u; /* offset : 0x108 */
	uint32_t reserved_2[445];
	union cmu_nbus_u_nbus_u_cmu_nbus_u_controller_option
		nbus_u_cmu_nbus_u_controller_option; /* offset : 0x800 */
	union cmu_nbus_u_clkout_con_blk_nbus_u_cmu_nbus_u_clkout
		clkout_con_blk_nbus_u_cmu_nbus_u_clkout; /* offset : 0x804 */
	uint32_t reserved_3[510];
	union cmu_nbus_u_clk_con_mux_mux_nbus_u_tclk clk_con_mux_mux_nbus_u_tclk; /* offset : 0x1000 */
	uint32_t reserved_4[511];
	union cmu_nbus_u_clk_con_div_div1_nbus_u_aclk clk_con_div_div1_nbus_u_aclk;
	union cmu_nbus_u_clk_con_div_div1_nbus_u_tclk clk_con_div_div1_nbus_u_tclk;
	union cmu_nbus_u_clk_con_div_div2_nbus_u_cmgr_bist
		clk_con_div_div2_nbus_u_cmgr_bist; /* offset : 0x1808 */
	union cmu_nbus_u_clk_con_div_div3_nbus_u_pclk clk_con_div_div3_nbus_u_pclk;
	uint32_t reserved_5[508];
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_nbus_u_cmu_nbus_u_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_u_uid_nbus_u_cmu_nbus_u_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_noc_d_nbus_u_r_ipclkport_clk_main_sfr_nu
		clk_con_gat_clk_blk_nbus_u_uid_noc_d_nbus_u_r_ipclkport_clk_main_sfr_nu; /*offset:0x2004*/
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_noc_c_nbus_u_ipclkport_clk_533_n_u
		clk_con_gat_clk_blk_nbus_u_uid_noc_c_nbus_u_ipclkport_clk_533_n_u; /* offset : 0x2008 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x200c */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_nbus_u_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2010 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_nbus_u_noc_refclk_gen_ipclkport_i_osc_clk
		clk_con_gat_clk_blk_nbus_u_uid_nbus_u_noc_refclk_gen_ipclkport_i_osc_clk; /*offset:0x2014*/
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_peri0m_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_u_uid_lh_peri0m_p_mi_ipclkport_i_clk; /* offset : 0x2018 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_peri0s_p_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_u_uid_lh_peri0s_p_si_ipclkport_i_clk; /* offset : 0x201c */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_apb_nbuss_g_mi_ipclkport_clk_m
		clk_con_gat_clk_blk_nbus_u_uid_apb_nbuss_g_mi_ipclkport_clk_m; /* offset : 0x2020 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t0_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t0_si_ipclkport_i_clk; /* offset : 0x2024 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t1_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t1_si_ipclkport_i_clk; /* offset : 0x2028 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t2_si_ipclkport_i_clk
		clk_con_gat_clk_blk_nbus_u_uid_lh_nbusm_t2_si_ipclkport_i_clk; /* offset : 0x202c */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_pclkdbg
		clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_pclkdbg; /* offset : 0x2030 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_tsclk
		clk_con_gat_clk_blk_nbus_u_uid_cssys_nbus_ipclkport_tsclk; /* offset : 0x2034 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_sysreg_buscsr_nbus_u_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_u_uid_sysreg_buscsr_nbus_u_ipclkport_pclk; /* offset : 0x2038 */
	union cmu_nbus_u_clk_con_gat_clk_blk_nbus_u_uid_sysreg_nbus_u_ipclkport_pclk
		clk_con_gat_clk_blk_nbus_u_uid_sysreg_nbus_u_ipclkport_pclk; /* offset : 0x203c */
	uint32_t reserved_6[1008];
	union cmu_nbus_u_qch_con_noc_d_nbus_u_r_qch qch_con_noc_d_nbus_u_r_qch; /* offset : 0x3000 */
	union cmu_nbus_u_qch_con_noc_c_nbus_u_qch qch_con_noc_c_nbus_u_qch; /* offset : 0x3004 */
	union cmu_nbus_u_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3008 */
	union cmu_nbus_u_qch_con_rstnsync_nbus_u_oscclk_qch
		qch_con_rstnsync_nbus_u_oscclk_qch; /* offset : 0x300c */
	union cmu_nbus_u_qch_con_nbus_u_noc_refclk_gen_qch
		qch_con_nbus_u_noc_refclk_gen_qch; /* offset : 0x3010 */
	union cmu_nbus_u_qch_con_refclk_div_0_sync_qch
		qch_con_refclk_div_0_sync_qch; /* offset : 0x3014 */
	union cmu_nbus_u_qch_con_refclk_div_1_sync_qch
		qch_con_refclk_div_1_sync_qch; /* offset : 0x3018 */
	union cmu_nbus_u_qch_con_refclk_div_2_sync_qch
		qch_con_refclk_div_2_sync_qch; /* offset : 0x301c */
	union cmu_nbus_u_qch_con_rstnsync_nbus_u_aclk_qch
		qch_con_rstnsync_nbus_u_aclk_qch; /* offset : 0x3020 */
	union cmu_nbus_u_qch_con_rstnsync_nbus_u_cssys_qch
		qch_con_rstnsync_nbus_u_cssys_qch; /* offset : 0x3024 */
	union cmu_nbus_u_qch_con_rstnsync_nbus_u_pclk_qch
		qch_con_rstnsync_nbus_u_pclk_qch; /* offset : 0x3028 */
	union cmu_nbus_u_qch_con_rstnsync_nbus_u_tsclk_qch
		qch_con_rstnsync_nbus_u_tsclk_qch; /* offset : 0x302c */
	union cmu_nbus_u_qch_con_amba_ovrd_cmgr_qch qch_con_amba_ovrd_cmgr_qch; /* offset : 0x3030 */
	union cmu_nbus_u_qch_con_cmgr_qch qch_con_cmgr_qch; /* offset : 0x3034 */
	union cmu_nbus_u_qch_con_cmgr_bist_qch qch_con_cmgr_bist_qch; /* offset : 0x3038 */
	union cmu_nbus_u_qch_con_cssys_nbus_qch qch_con_cssys_nbus_qch; /* offset : 0x303c */
	union cmu_nbus_u_qch_con_noc_rbc_v0_r_sw_qch qch_con_noc_rbc_v0_r_sw_qch; /* offset : 0x3040 */
	union cmu_nbus_u_qch_con_dti_sw_nbus_u_2x1_qch
		qch_con_dti_sw_nbus_u_2x1_qch; /* offset : 0x3044 */
	union cmu_nbus_u_qch_con_dti_rs_pcie_qch qch_con_dti_rs_pcie_qch; /* offset : 0x3048 */
	union cmu_nbus_u_qch_con_dti_rs_rot_qch qch_con_dti_rs_rot_qch; /* offset : 0x304c */
	union cmu_nbus_u_qch_con_dti_rs_nd_qch qch_con_dti_rs_nd_qch; /* offset : 0x3050 */
	union cmu_nbus_u_qch_con_axi_rs_rbc_v00s_d0_qch
		qch_con_axi_rs_rbc_v00s_d0_qch; /* offset : 0x3054 */
	union cmu_nbus_u_qch_con_axi_rs_rbc_v00s_d1_qch
		qch_con_axi_rs_rbc_v00s_d1_qch; /* offset : 0x3058 */
	union cmu_nbus_u_qch_con_axi_rs_rbc_v01s_d0_qch
		qch_con_axi_rs_rbc_v01s_d0_qch; /* offset : 0x305c */
	union cmu_nbus_u_qch_con_axi_rs_rbc_v01s_d1_qch
		qch_con_axi_rs_rbc_v01s_d1_qch; /* offset : 0x3060 */
	union cmu_nbus_u_qch_con_detour_ch0_en_sync_qch
		qch_con_detour_ch0_en_sync_qch; /* offset : 0x3064 */
	union cmu_nbus_u_qch_con_detour_ch1_en_sync_qch
		qch_con_detour_ch1_en_sync_qch; /* offset : 0x3068 */
	union cmu_nbus_u_qch_con_detour_ch2_en_sync_qch
		qch_con_detour_ch2_en_sync_qch; /* offset : 0x306c */
	union cmu_nbus_u_qch_con_detour_ch3_en_sync_qch
		qch_con_detour_ch3_en_sync_qch; /* offset : 0x3070 */
	union cmu_nbus_u_qch_con_detour_en_sync_qch qch_con_detour_en_sync_qch; /* offset : 0x3074 */
	union cmu_nbus_u_qch_con_axi2apb_dbg_nbus_u_qch
		qch_con_axi2apb_dbg_nbus_u_qch; /* offset : 0x3078 */
	union cmu_nbus_u_qch_con_axi2apb_nbus_u_qch qch_con_axi2apb_nbus_u_qch; /* offset : 0x307c */
	union cmu_nbus_u_qch_con_lh_peri0m_p_mi_pch qch_con_lh_peri0m_p_mi_pch; /* offset : 0x3080 */
	union cmu_nbus_u_qch_con_lh_peri0s_p_si_pch qch_con_lh_peri0s_p_si_pch; /* offset : 0x3084 */
	union cmu_nbus_u_qch_con_lh_pcies_p_si_pch qch_con_lh_pcies_p_si_pch; /* offset : 0x3088 */
	union cmu_nbus_u_qch_con_lh_pcies_d_si_pch qch_con_lh_pcies_d_si_pch; /* offset : 0x308c */
	union cmu_nbus_u_qch_con_lh_pciem_d_mi_pch qch_con_lh_pciem_d_mi_pch; /* offset : 0x3090 */
	union cmu_nbus_u_qch_con_lh_rots_p_si_pch qch_con_lh_rots_p_si_pch; /* offset : 0x3094 */
	union cmu_nbus_u_qch_con_lh_rotm_d0_mi_pch qch_con_lh_rotm_d0_mi_pch; /* offset : 0x3098 */
	union cmu_nbus_u_qch_con_lh_rotm_d1_mi_pch qch_con_lh_rotm_d1_mi_pch; /* offset : 0x309c */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_p_si_pch
		qch_con_lh_rbc_v00s_p_si_pch; /* offset : 0x30a0 */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_p0_mi_pch
		qch_con_lh_rbc_v00m_p0_mi_pch; /* offset : 0x30a4 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_p0_si_pch
		qch_con_lh_rbc_v00s_p0_si_pch; /* offset : 0x30a8 */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_d0_mi_pch
		qch_con_lh_rbc_v00m_d0_mi_pch; /* offset : 0x30ac */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_d1_mi_pch
		qch_con_lh_rbc_v00m_d1_mi_pch; /* offset : 0x30b0 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_d0_si_pch
		qch_con_lh_rbc_v00s_d0_si_pch; /* offset : 0x30b4 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_d1_si_pch
		qch_con_lh_rbc_v00s_d1_si_pch; /* offset : 0x30b8 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_p_si_pch
		qch_con_lh_rbc_v01s_p_si_pch; /* offset : 0x30bc */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_p0_mi_pch
		qch_con_lh_rbc_v01m_p0_mi_pch; /* offset : 0x30c0 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_p0_si_pch
		qch_con_lh_rbc_v01s_p0_si_pch; /* offset : 0x30c4 */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_d0_mi_pch
		qch_con_lh_rbc_v01m_d0_mi_pch; /* offset : 0x30c8 */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_d1_mi_pch
		qch_con_lh_rbc_v01m_d1_mi_pch; /* offset : 0x30cc */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_d0_si_pch
		qch_con_lh_rbc_v01s_d0_si_pch; /* offset : 0x30d0 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_d1_si_pch
		qch_con_lh_rbc_v01s_d1_si_pch; /* offset : 0x30d4 */
	union cmu_nbus_u_qch_con_lh_nbusm_t0_si_pch qch_con_lh_nbusm_t0_si_pch; /* offset : 0x30d8 */
	union cmu_nbus_u_qch_con_lh_nbusm_t1_si_pch qch_con_lh_nbusm_t1_si_pch; /* offset : 0x30dc */
	union cmu_nbus_u_qch_con_lh_nbusm_t2_si_pch qch_con_lh_nbusm_t2_si_pch; /* offset : 0x30e0 */
	union cmu_nbus_u_qch_con_lh_nbus_um_ast_si_pch
		qch_con_lh_nbus_um_ast_si_pch; /* offset : 0x30e4 */
	union cmu_nbus_u_qch_con_lh_nbus_us_ast_mi_pch
		qch_con_lh_nbus_us_ast_mi_pch; /* offset : 0x30e8 */
	union cmu_nbus_u_qch_con_lh_rots_ast_si_pch qch_con_lh_rots_ast_si_pch; /* offset : 0x30ec */
	union cmu_nbus_u_qch_con_lh_rotm_ast_mi_pch qch_con_lh_rotm_ast_mi_pch; /* offset : 0x30f0 */
	union cmu_nbus_u_qch_con_lh_pcies_ast_si_pch qch_con_lh_pcies_ast_si_pch; /* offset : 0x30f4 */
	union cmu_nbus_u_qch_con_lh_pciem_ast_mi_pch qch_con_lh_pciem_ast_mi_pch; /* offset : 0x30f8 */
	union cmu_nbus_u_qch_con_nbus_u_cmu_nbus_u_qch
		qch_con_nbus_u_cmu_nbus_u_qch; /* offset : 0x30fc */
	union cmu_nbus_u_qch_con_lh_peri0m_p_mi_qch qch_con_lh_peri0m_p_mi_qch; /* offset : 0x3100 */
	union cmu_nbus_u_qch_con_lh_peri0s_p_si_qch qch_con_lh_peri0s_p_si_qch; /* offset : 0x3104 */
	union cmu_nbus_u_qch_con_lh_pcies_p_si_qch qch_con_lh_pcies_p_si_qch; /* offset : 0x3108 */
	union cmu_nbus_u_qch_con_lh_pcies_d_si_qch qch_con_lh_pcies_d_si_qch; /* offset : 0x310c */
	union cmu_nbus_u_qch_con_lh_pciem_d_mi_qch qch_con_lh_pciem_d_mi_qch; /* offset : 0x3110 */
	union cmu_nbus_u_qch_con_lh_rots_p_si_qch qch_con_lh_rots_p_si_qch; /* offset : 0x3114 */
	union cmu_nbus_u_qch_con_lh_rotm_d0_mi_qch qch_con_lh_rotm_d0_mi_qch; /* offset : 0x3118 */
	union cmu_nbus_u_qch_con_lh_rotm_d1_mi_qch qch_con_lh_rotm_d1_mi_qch; /* offset : 0x311c */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_p_si_qch
		qch_con_lh_rbc_v00s_p_si_qch; /* offset : 0x3120 */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_p0_mi_qch
		qch_con_lh_rbc_v00m_p0_mi_qch; /* offset : 0x3124 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_p0_si_qch
		qch_con_lh_rbc_v00s_p0_si_qch; /* offset : 0x3128 */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_d0_mi_qch
		qch_con_lh_rbc_v00m_d0_mi_qch; /* offset : 0x312c */
	union cmu_nbus_u_qch_con_lh_rbc_v00m_d1_mi_qch
		qch_con_lh_rbc_v00m_d1_mi_qch; /* offset : 0x3130 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_d0_si_qch
		qch_con_lh_rbc_v00s_d0_si_qch; /* offset : 0x3134 */
	union cmu_nbus_u_qch_con_lh_rbc_v00s_d1_si_qch
		qch_con_lh_rbc_v00s_d1_si_qch; /* offset : 0x3138 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_p_si_qch
		qch_con_lh_rbc_v01s_p_si_qch; /* offset : 0x313c */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_p0_mi_qch
		qch_con_lh_rbc_v01m_p0_mi_qch; /* offset : 0x3140 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_p0_si_qch
		qch_con_lh_rbc_v01s_p0_si_qch; /* offset : 0x3144 */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_d0_mi_qch
		qch_con_lh_rbc_v01m_d0_mi_qch; /* offset : 0x3148 */
	union cmu_nbus_u_qch_con_lh_rbc_v01m_d1_mi_qch
		qch_con_lh_rbc_v01m_d1_mi_qch; /* offset : 0x314c */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_d0_si_qch
		qch_con_lh_rbc_v01s_d0_si_qch; /* offset : 0x3150 */
	union cmu_nbus_u_qch_con_lh_rbc_v01s_d1_si_qch
		qch_con_lh_rbc_v01s_d1_si_qch; /* offset : 0x3154 */
	union cmu_nbus_u_qch_con_apb_nbuss_g_mi_qch_clk
		qch_con_apb_nbuss_g_mi_qch_clk; /* offset : 0x3158 */
	union cmu_nbus_u_qch_con_lh_nbusm_t0_si_qch qch_con_lh_nbusm_t0_si_qch; /* offset : 0x315c */
	union cmu_nbus_u_qch_con_lh_nbusm_t1_si_qch qch_con_lh_nbusm_t1_si_qch; /* offset : 0x3160 */
	union cmu_nbus_u_qch_con_lh_nbusm_t2_si_qch qch_con_lh_nbusm_t2_si_qch; /* offset : 0x3164 */
	union cmu_nbus_u_qch_con_lh_nbus_um_ast_si_qch
		qch_con_lh_nbus_um_ast_si_qch; /* offset : 0x3168 */
	union cmu_nbus_u_qch_con_lh_nbus_us_ast_mi_qch
		qch_con_lh_nbus_us_ast_mi_qch; /* offset : 0x316c */
	union cmu_nbus_u_qch_con_lh_rots_ast_si_qch qch_con_lh_rots_ast_si_qch; /* offset : 0x3170 */
	union cmu_nbus_u_qch_con_lh_rotm_ast_mi_qch qch_con_lh_rotm_ast_mi_qch; /* offset : 0x3174 */
	union cmu_nbus_u_qch_con_lh_pcies_ast_si_qch qch_con_lh_pcies_ast_si_qch; /* offset : 0x3178 */
	union cmu_nbus_u_qch_con_lh_pciem_ast_mi_qch qch_con_lh_pciem_ast_mi_qch; /* offset : 0x317c */
	union cmu_nbus_u_qch_con_sysreg_buscsr_nbus_u_qch
		qch_con_sysreg_buscsr_nbus_u_qch; /* offset : 0x3180 */
	union cmu_nbus_u_qch_con_sysreg_nbus_u_qch qch_con_sysreg_nbus_u_qch; /* offset : 0x3184 */
};

enum NBUS_U_CLK_OUT {
	OSCCLK_NBUS_U,
	PLL_NBUS_U,
	CLK_NBUS_U_ACLK,
	CLK_NBUS_U_TCLK,
	CLK_NBUS_U_PCLK,
	CLK_NBUS_U_OSCCLK,
	NBUS_U_CLK_LH_SCAN_DST,
	NBUS_U_CLK_LH_SCAN_ETC,
};
