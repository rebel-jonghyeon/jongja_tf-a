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

union cmu_peri_pll_locktime_pll_peri {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_peri_pll_con0_pll_peri {
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

union cmu_peri_pll_con1_pll_peri {
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

union cmu_peri_pll_con2_pll_peri {
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

union cmu_peri_pll_con3_pll_peri {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_peri_pll_con4_pll_peri {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_peri_peri_cmu_peri_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_peri_clkout_con_blk_peri_cmu_peri_clkout {
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

union cmu_peri_clk_con_div_div2_peri_pclk {
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

union cmu_peri_clk_con_gat_clk_blk_peri_uid_peri_cmu_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk_r {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_peris_p_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_perim_p_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_sysreg_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_uart0_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_uart1_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_ic_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_ic_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_ssi_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_ssi_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_hclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_ssi_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_hclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_ssi_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_mhclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_wdt0_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_wdt1_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_1_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_2_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_3_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_4_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m5_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m6_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m7_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m8_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m9_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m10_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m11_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m12_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m13_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m14_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_nic_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_axi2apb_peri0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_axi2apb_peri1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_uart0_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_uart1_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_i2c0_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_i2c1_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_qspi0_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_qspi1_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_qspi2_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_qspi3_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_wdt0_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_wdt1_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_pwm_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_gpio_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_lh_peris_p_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_lh_perim_p_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_peri_cmu_peri_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_lh_peris_p_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_lh_perim_p_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_sysreg_peri_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m5_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m6_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m7_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m8_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m9_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m10_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m11_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m12_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m13_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_mailbox_m14_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_peri_qch_con_gpio_peri_qch_s_gpio_peri {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_peri {
	union cmu_peri_pll_locktime_pll_peri pll_locktime_pll_peri; /* offset : 0x0 */
	uint32_t reserved_1[63];
	union cmu_peri_pll_con0_pll_peri pll_con0_pll_peri; /* offset : 0x100 */
	union cmu_peri_pll_con1_pll_peri pll_con1_pll_peri; /* offset : 0x104 */
	union cmu_peri_pll_con2_pll_peri pll_con2_pll_peri; /* offset : 0x108 */
	union cmu_peri_pll_con3_pll_peri pll_con3_pll_peri; /* offset : 0x10c */
	union cmu_peri_pll_con4_pll_peri pll_con4_pll_peri; /* offset : 0x110 */
	uint32_t reserved_2[443];
	union cmu_peri_peri_cmu_peri_controller_option
		peri_cmu_peri_controller_option; /* offset : 0x800 */
	union cmu_peri_clkout_con_blk_peri_cmu_peri_clkout
		clkout_con_blk_peri_cmu_peri_clkout; /* offset : 0x804 */
	uint32_t reserved_3[1022];
	union cmu_peri_clk_con_div_div2_peri_pclk clk_con_div_div2_peri_pclk; /* offset : 0x1800 */
	uint32_t reserved_4[511];
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_peri_cmu_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_peri_cmu_peri_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk
		clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk; /* offset : 0x2004 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk_r
		clk_con_gat_clk_blk_peri_uid_nic_peri_ipclkport_pckclk_r; /* offset : 0x2008 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_peris_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_peri_uid_lh_peris_p_mi_ipclkport_i_clk; /* offset : 0x200c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_perim_p_si_ipclkport_i_clk
		clk_con_gat_clk_blk_peri_uid_lh_perim_p_si_ipclkport_i_clk; /* offset : 0x2010 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_sysreg_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_sysreg_peri_ipclkport_pclk; /* offset : 0x2014 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_uart0_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_uart0_peri_ipclkport_pclk; /* offset : 0x2018 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_uart1_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_uart1_peri_ipclkport_pclk; /* offset : 0x201c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_pclk; /* offset : 0x2020 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_ic_clk
		clk_con_gat_clk_blk_peri_uid_i2c0_peri_ipclkport_ic_clk; /* offset : 0x2024 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_pclk; /* offset : 0x2028 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_ic_clk
		clk_con_gat_clk_blk_peri_uid_i2c1_peri_ipclkport_ic_clk; /* offset : 0x202c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_pclk; /* offset : 0x2030 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_ssi_clk
		clk_con_gat_clk_blk_peri_uid_qspi0_peri_ipclkport_ssi_clk; /* offset : 0x2034 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_pclk; /* offset : 0x2038 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_ssi_clk
		clk_con_gat_clk_blk_peri_uid_qspi1_peri_ipclkport_ssi_clk; /* offset : 0x203c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_hclk
		clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_hclk; /* offset : 0x2040 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_ssi_clk
		clk_con_gat_clk_blk_peri_uid_qspi2_peri_ipclkport_ssi_clk; /* offset : 0x2044 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_hclk
		clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_hclk; /* offset : 0x2048 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_ssi_clk
		clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_ssi_clk; /* offset : 0x204c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_mhclk
		clk_con_gat_clk_blk_peri_uid_qspi3_peri_ipclkport_mhclk; /* offset : 0x2050 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_wdt0_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_wdt0_peri_ipclkport_pclk; /* offset : 0x2054 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_wdt1_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_wdt1_peri_ipclkport_pclk; /* offset : 0x2058 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_pclk; /* offset : 0x205c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_1_clk
		clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_1_clk; /* offset : 0x2060 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_2_clk
		clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_2_clk; /* offset : 0x2064 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_3_clk
		clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_3_clk; /* offset : 0x2068 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_4_clk
		clk_con_gat_clk_blk_peri_uid_pwm_peri_ipclkport_timer_4_clk; /* offset : 0x206c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2070 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_peri_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2074 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m5_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m5_ipclkport_pclk; /* offset : 0x2078 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m6_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m6_ipclkport_pclk; /* offset : 0x207c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m7_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m7_ipclkport_pclk; /* offset : 0x2080 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m8_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m8_ipclkport_pclk; /* offset : 0x2084 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m9_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m9_ipclkport_pclk; /* offset : 0x2088 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m10_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m10_ipclkport_pclk; /* offset : 0x208c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m11_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m11_ipclkport_pclk; /* offset : 0x2090 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m12_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m12_ipclkport_pclk; /* offset : 0x2094 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m13_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m13_ipclkport_pclk; /* offset : 0x2098 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_mailbox_m14_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_mailbox_m14_ipclkport_pclk; /* offset : 0x209c */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_oscclk
		clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_oscclk; /* offset : 0x20a0 */
	union cmu_peri_clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_pclk
		clk_con_gat_clk_blk_peri_uid_gpio_peri_ipclkport_pclk; /* offset : 0x20a4 */
	uint32_t reserved_5[982];
	union cmu_peri_qch_con_nic_peri_qch qch_con_nic_peri_qch; /* offset : 0x3000 */
	union cmu_peri_qch_con_axi2apb_peri0_qch qch_con_axi2apb_peri0_qch; /* offset : 0x3004 */
	union cmu_peri_qch_con_axi2apb_peri1_qch qch_con_axi2apb_peri1_qch; /* offset : 0x3008 */
	union cmu_peri_qch_con_uart0_peri_qch qch_con_uart0_peri_qch; /* offset : 0x300c */
	union cmu_peri_qch_con_uart1_peri_qch qch_con_uart1_peri_qch; /* offset : 0x3010 */
	union cmu_peri_qch_con_i2c0_peri_qch qch_con_i2c0_peri_qch; /* offset : 0x3014 */
	union cmu_peri_qch_con_i2c1_peri_qch qch_con_i2c1_peri_qch; /* offset : 0x3018 */
	union cmu_peri_qch_con_qspi0_peri_qch qch_con_qspi0_peri_qch; /* offset : 0x301c */
	union cmu_peri_qch_con_qspi1_peri_qch qch_con_qspi1_peri_qch; /* offset : 0x3020 */
	union cmu_peri_qch_con_qspi2_peri_qch qch_con_qspi2_peri_qch; /* offset : 0x3024 */
	union cmu_peri_qch_con_qspi3_peri_qch qch_con_qspi3_peri_qch; /* offset : 0x3028 */
	union cmu_peri_qch_con_wdt0_peri_qch qch_con_wdt0_peri_qch; /* offset : 0x302c */
	union cmu_peri_qch_con_wdt1_peri_qch qch_con_wdt1_peri_qch; /* offset : 0x3030 */
	union cmu_peri_qch_con_pwm_peri_qch qch_con_pwm_peri_qch; /* offset : 0x3034 */
	union cmu_peri_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3038 */
	union cmu_peri_qch_con_gpio_peri_qch qch_con_gpio_peri_qch; /* offset : 0x303c */
	union cmu_peri_qch_con_lh_peris_p_mi_pch qch_con_lh_peris_p_mi_pch; /* offset : 0x3040 */
	union cmu_peri_qch_con_lh_perim_p_si_pch qch_con_lh_perim_p_si_pch; /* offset : 0x3044 */
	union cmu_peri_qch_con_peri_cmu_peri_qch qch_con_peri_cmu_peri_qch; /* offset : 0x3048 */
	union cmu_peri_qch_con_lh_peris_p_mi_qch qch_con_lh_peris_p_mi_qch; /* offset : 0x304c */
	union cmu_peri_qch_con_lh_perim_p_si_qch qch_con_lh_perim_p_si_qch; /* offset : 0x3050 */
	union cmu_peri_qch_con_sysreg_peri_qch_s qch_con_sysreg_peri_qch_s; /* offset : 0x3054 */
	union cmu_peri_qch_con_mailbox_m5_qch qch_con_mailbox_m5_qch; /* offset : 0x3058 */
	union cmu_peri_qch_con_mailbox_m6_qch qch_con_mailbox_m6_qch; /* offset : 0x305c */
	union cmu_peri_qch_con_mailbox_m7_qch qch_con_mailbox_m7_qch; /* offset : 0x3060 */
	union cmu_peri_qch_con_mailbox_m8_qch qch_con_mailbox_m8_qch; /* offset : 0x3064 */
	union cmu_peri_qch_con_mailbox_m9_qch qch_con_mailbox_m9_qch; /* offset : 0x3068 */
	union cmu_peri_qch_con_mailbox_m10_qch qch_con_mailbox_m10_qch; /* offset : 0x306c */
	union cmu_peri_qch_con_mailbox_m11_qch qch_con_mailbox_m11_qch; /* offset : 0x3070 */
	union cmu_peri_qch_con_mailbox_m12_qch qch_con_mailbox_m12_qch; /* offset : 0x3074 */
	union cmu_peri_qch_con_mailbox_m13_qch qch_con_mailbox_m13_qch; /* offset : 0x3078 */
	union cmu_peri_qch_con_mailbox_m14_qch qch_con_mailbox_m14_qch; /* offset : 0x307c */
	union cmu_peri_qch_con_gpio_peri_qch_s_gpio_peri
		qch_con_gpio_peri_qch_s_gpio_peri; /* offset : 0x3080 */
};

enum PERI_CLK_OUT {
	OSCCLK_PERI,
	CLK_PERI_PCLK,
	CLK_PERI_OSCCLK,
	CLK_PERI_IC_CLK,
	PERI_CLK_LH_SCAN_DST,
	PERI_CLK_LH_SCAN_ETC,
};
