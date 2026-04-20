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

union cmu_sbus_u_pll_locktime_pll_sbus {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_sbus_u_pll_con0_pll_sbus {
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

union cmu_sbus_u_pll_con1_pll_sbus {
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

union cmu_sbus_u_pll_con2_pll_sbus {
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

union cmu_sbus_u_pll_con3_pll_sbus {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_sbus_u_pll_con4_pll_sbus {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_sbus_u_sbus_u_cmu_sbus_u_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_sbus_u_clkout_con_blk_sbus_u_cmu_sbus_u_clkout {
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

union cmu_sbus_u_clk_con_div_div1_sbus_u_aclk {
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

union cmu_sbus_u_clk_con_div_div3_sbus_u_pclk {
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

union cmu_sbus_u_clk_con_div_div4_rbc_v10 {
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

union cmu_sbus_u_clk_con_div_div4_rbc_v11 {
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

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sbus_u_cmu_sbus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_noc_c_sbus_u_ipclkport_clk_533_s_u {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_noc_d_sbus_u_r_ipclkport_clk_main_sfr_su {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sbus_u_noc_refclk_gen_ipclkport_i_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sysreg_sbus_u_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_buf_clk_rbc_v10 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_clk_con_buf_clk_rbc_v11 {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved1:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_noc_c_sbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_noc_d_sbus_u_r_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_sbus_u_noc_refclk_gen_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_axi2apb_dbg_sbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_axi2apb_sbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_rstnsync_sbus_u_aclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_rstnsync_sbus_u_pclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_rstnsync_sbus_u_oscclk_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_rbc_v10_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_rbc_v11_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_lh_dcl1s_mp_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_sbus_u_cmu_sbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_lh_dcl1s_mp_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_sysreg_sbus_u_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_sbus_u_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_sbus_u {
	union cmu_sbus_u_pll_locktime_pll_sbus pll_locktime_pll_sbus; /* offset : 0x0 */
	uint32_t reserved_1[63];
	union cmu_sbus_u_pll_con0_pll_sbus pll_con0_pll_sbus; /* offset : 0x100 */
	union cmu_sbus_u_pll_con1_pll_sbus pll_con1_pll_sbus; /* offset : 0x104 */
	union cmu_sbus_u_pll_con2_pll_sbus pll_con2_pll_sbus; /* offset : 0x108 */
	union cmu_sbus_u_pll_con3_pll_sbus pll_con3_pll_sbus; /* offset : 0x10c */
	union cmu_sbus_u_pll_con4_pll_sbus pll_con4_pll_sbus; /* offset : 0x110 */
	uint32_t reserved_2[443];
};

struct cmu_sbus_u_cont {
	union cmu_sbus_u_sbus_u_cmu_sbus_u_controller_option
		sbus_u_cmu_sbus_u_controller_option; /* offset : 0x800 */
	union cmu_sbus_u_clkout_con_blk_sbus_u_cmu_sbus_u_clkout
		clkout_con_blk_sbus_u_cmu_sbus_u_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
};

struct cmu_sbus_u_mux {
};

struct cmu_sbus_u_div {
	union cmu_sbus_u_clk_con_div_div1_sbus_u_aclk
		clk_con_div_div1_sbus_u_aclk; /* offset : 0x1800 */
	union cmu_sbus_u_clk_con_div_div3_sbus_u_pclk
		clk_con_div_div3_sbus_u_pclk; /* offset : 0x1804 */
	union cmu_sbus_u_clk_con_div_div4_rbc_v10 clk_con_div_div4_rbc_v10; /* offset : 0x1808 */
	union cmu_sbus_u_clk_con_div_div4_rbc_v11 clk_con_div_div4_rbc_v11; /* offset : 0x180c */
	uint32_t reserved_4[508];
};

struct cmu_sbus_u_gate {
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sbus_u_cmu_sbus_u_ipclkport_pclk
		clk_con_gat_clk_blk_sbus_u_uid_sbus_u_cmu_sbus_u_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_noc_c_sbus_u_ipclkport_clk_533_s_u
		clk_con_gat_clk_blk_sbus_u_uid_noc_c_sbus_u_ipclkport_clk_533_s_u; /* offset : 0x2004 */
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_noc_d_sbus_u_r_ipclkport_clk_main_sfr_su
		clk_con_gat_clk_blk_sbus_u_uid_noc_d_sbus_u_r_ipclkport_clk_main_sfr_su;
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sbus_u_noc_refclk_gen_ipclkport_i_osc_clk
		clk_con_gat_clk_blk_sbus_u_uid_sbus_u_noc_refclk_gen_ipclkport_i_osc_clk;
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_sysreg_sbus_u_ipclkport_pclk
		clk_con_gat_clk_blk_sbus_u_uid_sysreg_sbus_u_ipclkport_pclk; /* offset : 0x2010 */
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2014 */
	union cmu_sbus_u_clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_sbus_u_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2018 */
	uint32_t reserved_5[2];
	union cmu_sbus_u_clk_con_buf_clk_rbc_v10 clk_con_buf_clk_rbc_v10; /* offset : 0x2024 */
	union cmu_sbus_u_clk_con_buf_clk_rbc_v11 clk_con_buf_clk_rbc_v11; /* offset : 0x2028 */
	uint32_t reserved_6[1013];
};

struct cmu_sbus_u_qch {
	union cmu_sbus_u_qch_con_noc_c_sbus_u_qch qch_con_noc_c_sbus_u_qch; /* offset : 0x3000 */
	union cmu_sbus_u_qch_con_noc_d_sbus_u_r_qch qch_con_noc_d_sbus_u_r_qch; /* offset : 0x3004 */
	union cmu_sbus_u_qch_con_sbus_u_noc_refclk_gen_qch
		qch_con_sbus_u_noc_refclk_gen_qch; /* offset : 0x3008 */
	union cmu_sbus_u_qch_con_axi2apb_dbg_sbus_u_qch
		qch_con_axi2apb_dbg_sbus_u_qch; /* offset : 0x300c */
	union cmu_sbus_u_qch_con_axi2apb_sbus_u_qch qch_con_axi2apb_sbus_u_qch; /* offset : 0x3010 */
	union cmu_sbus_u_qch_con_rstnsync_sbus_u_aclk_qch
		qch_con_rstnsync_sbus_u_aclk_qch; /* offset : 0x3014 */
	union cmu_sbus_u_qch_con_rstnsync_sbus_u_pclk_qch
		qch_con_rstnsync_sbus_u_pclk_qch; /* offset : 0x3018 */
	union cmu_sbus_u_qch_con_rstnsync_sbus_u_oscclk_qch
		qch_con_rstnsync_sbus_u_oscclk_qch; /* offset : 0x301c */
	union cmu_sbus_u_qch_con_rbc_v10_qch qch_con_rbc_v10_qch; /* offset : 0x3020 */
	union cmu_sbus_u_qch_con_rbc_v11_qch qch_con_rbc_v11_qch; /* offset : 0x3024 */
	union cmu_sbus_u_qch_con_lh_dcl1s_mp_si_pch qch_con_lh_dcl1s_mp_si_pch; /* offset : 0x3028 */
	union cmu_sbus_u_qch_con_sbus_u_cmu_sbus_u_qch
		qch_con_sbus_u_cmu_sbus_u_qch; /* offset : 0x302c */
	union cmu_sbus_u_qch_con_lh_dcl1s_mp_si_qch qch_con_lh_dcl1s_mp_si_qch; /* offset : 0x3030 */
	union cmu_sbus_u_qch_con_sysreg_sbus_u_qch qch_con_sysreg_sbus_u_qch; /* offset : 0x3034 */
	union cmu_sbus_u_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3038 */
};
