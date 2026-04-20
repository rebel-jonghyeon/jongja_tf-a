#pragma once

union cmu_rot_pll_locktime_pll_rot {
	struct {
		uint32_t pll_lock_time:20; /* [19:0] */
		uint32_t reserved0:4; /* [23:20] */
		uint32_t reset_req_time:6; /* [29:24] */
		uint32_t reserved1:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_rot_pll_con0_pll_rot {
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

union cmu_rot_pll_con1_pll_rot {
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

union cmu_rot_pll_con2_pll_rot {
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

union cmu_rot_pll_con3_pll_rot {
	struct {
		uint32_t div_k:16; /* [15:0] */
		uint32_t mfr:8; /* [23:16] */
		uint32_t mrr:6; /* [29:24] */
		uint32_t sel_pf:2; /* [31:30] */
	};
	uint32_t val;
};

union cmu_rot_pll_con4_pll_rot {
	struct {
		uint32_t filter_cnt_expire_value:8; /* [7:0] */
		uint32_t ctrl:16; /* [23:8] */
		uint32_t reserved0:7; /* [30:24] */
		uint32_t enable_filter_automatic_clkgating:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_rot_rot_cmu_rot_controller_option {
	struct {
		uint32_t reserved0:28; /* [27:0] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t enable_power_management:1; /* [29:29] */
		uint32_t enable_layer2_ctrl:1; /* [30:30] */
		uint32_t enable_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union cmu_rot_clkout_con_blk_rot_cmu_rot_clkout {
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

union cmu_rot_clk_con_mux_mux_rot_tsclk {
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

union cmu_rot_clk_con_div_div2_rot_aclk {
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

union cmu_rot_clk_con_div_div3_rot_pclk {
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

union cmu_rot_clk_con_div_div7_rot_pvt {
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

union cmu_rot_clk_con_div_div4_rot_otp {
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

union cmu_rot_clk_con_div_div1_rot_tsclk {
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

union cmu_rot_clk_con_div_div3_rot_cntclk {
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

union cmu_rot_clk_con_div_div3_rot_rtck {
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

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rot_cmu_rot_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_top_ipclkport_sys_cm_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram0_ipclkport_ck {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram1_ipclkport_ck {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram2_ipclkport_ck {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram3_ipclkport_ck {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_dma_rot_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_m {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_tbu_rot_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_pe_wrapper_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_test_scan_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_mem_wrapper_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_noc_rot_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk_r {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk_r {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_dst {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_etc {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_d0_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rots_p_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_d1_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t0_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t1_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t2_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t3_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t4_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rots_ast_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_ast_si_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t0_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t1_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t2_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t3_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t4_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_pciem_t_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t0_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t1_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t2_mi_ipclkport_i_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp0s_g0_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp0s_g1_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp1s_g0_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp1s_g1_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_pcies_g0_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_pcies_g1_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_nbuss_g_si_ipclkport_clk_s {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_trace_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_debug_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_rt630_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_dma330_ipclkport_i_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_sysreg_sysremap_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_hclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_ssi_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_intmem_rot_ipclkport_aclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_tsclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_cntclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_pclkdbg {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_sysreg_rot_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m0_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m1_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m2_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_ecc_bridge_top_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_sec_ap_sfr_apbif_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_mem_wrapper_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_test_scan_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_mem_wrapper_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_test_scan_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_mem_wrapper_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_test_scan_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_mem_wrapper_ipclkport_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_oscclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_pclk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_test_scan_osc_clk {
	struct {
		uint32_t reserved0:20; /* [19:0] */
		uint32_t manual:1; /* [20:20] */
		uint32_t cg_val:1; /* [21:21] */
		uint32_t reserved1:6; /* [27:22] */
		uint32_t enable_automatic_clkgating:1; /* [28:28] */
		uint32_t reserved2:3; /* [31:29] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rt_top_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rt_sram0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rt_sram1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rt_sram2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rt_sram3_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_dma_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_pe_wrapper_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_pe_wrapper_qch_d {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_soc_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_soc_mem_wrapper_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_noc_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_nic_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_amba_ovrd_cs_trace_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_amba_ovrd_cs_debug_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_amba_ovrd_rt630_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_amba_ovrd_dma330_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_qspi_boot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_intmem_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_cssys_top_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_axi2apb_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_ecc_bridge_top_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_gpio_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_pvt_rot_controller_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_cpu_mem_wrapper_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_cpu_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s0_mem_wrapper_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s1_mem_wrapper_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s2_mem_wrapper_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_d0_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rots_p_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_d1_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t2_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t3_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t4_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rots_ast_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_ast_si_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t2_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t3_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t4_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_pciem_t_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t0_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t1_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t2_mi_pch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_rot_cmu_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_async_dma_clk_m {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_async_dma_clk_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_async_dma_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_tbu_rot_qch_cg {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_tbu_rot_qch_pd {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_soc_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_d0_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rots_p_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_d1_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t2_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t3_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp0m_t4_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rots_ast_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_rotm_ast_si_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t2_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t3_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_cp1m_t4_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_pciem_t_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t0_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t1_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_lh_nbusm_t2_mi_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp0s_g0_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp0s_g0_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp0s_g1_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp0s_g1_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp1s_g0_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp1s_g0_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp1s_g1_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_cp1s_g1_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_pcies_g0_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_pcies_g0_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_pcies_g1_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_pcies_g1_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_nbuss_g_si_qch_clk {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_apb_nbuss_g_si_qch_pwr {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_sysreg_sysremap_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_cssys_top_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_sysreg_rot_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_mailbox_m0_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_mailbox_m1_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_mailbox_m2_qch {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_sec_ap_sfr_apbif_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_gpio_rot_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_cpu_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s0_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s1_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

union cmu_rot_qch_con_otp_con_top_s2_qch_s {
	struct {
		uint32_t enable:1; /* [0:0] */
		uint32_t clock_req:1; /* [1:1] */
		uint32_t ignore_force_pm_en:1; /* [2:2] */
		uint32_t mask_qactive:1; /* [3:3] */
		uint32_t reserved0:12; /* [15:4] */
		uint32_t expire_val:10; /* [25:16] */
		uint32_t reserved1:6; /* [31:26] */
	};
	uint32_t val;
};

struct cmu_rot {
	union cmu_rot_pll_locktime_pll_rot pll_locktime_pll_rot; /* offset : 0x0 */
	uint32_t reserved_1[63];
	union cmu_rot_pll_con0_pll_rot pll_con0_pll_rot; /* offset : 0x100 */
	union cmu_rot_pll_con1_pll_rot pll_con1_pll_rot; /* offset : 0x104 */
	union cmu_rot_pll_con2_pll_rot pll_con2_pll_rot; /* offset : 0x108 */
	union cmu_rot_pll_con3_pll_rot pll_con3_pll_rot; /* offset : 0x10c */
	union cmu_rot_pll_con4_pll_rot pll_con4_pll_rot; /* offset : 0x110 */
	uint32_t reserved_2[443];
	union cmu_rot_rot_cmu_rot_controller_option rot_cmu_rot_controller_option; /* offset : 0x800 */
	union cmu_rot_clkout_con_blk_rot_cmu_rot_clkout
		clkout_con_blk_rot_cmu_rot_clkout; /* offset : 0x804 */
	uint32_t reserved_3[510];
	union cmu_rot_clk_con_mux_mux_rot_tsclk clk_con_mux_mux_rot_tsclk; /* offset : 0x1000 */
	uint32_t reserved_4[511];
	union cmu_rot_clk_con_div_div2_rot_aclk clk_con_div_div2_rot_aclk; /* offset : 0x1800 */
	union cmu_rot_clk_con_div_div3_rot_pclk clk_con_div_div3_rot_pclk; /* offset : 0x1804 */
	union cmu_rot_clk_con_div_div7_rot_pvt clk_con_div_div7_rot_pvt; /* offset : 0x1808 */
	union cmu_rot_clk_con_div_div4_rot_otp clk_con_div_div4_rot_otp; /* offset : 0x180c */
	union cmu_rot_clk_con_div_div1_rot_tsclk clk_con_div_div1_rot_tsclk; /* offset : 0x1810 */
	union cmu_rot_clk_con_div_div3_rot_cntclk clk_con_div_div3_rot_cntclk; /* offset : 0x1814 */
	union cmu_rot_clk_con_div_div3_rot_rtck clk_con_div_div3_rot_rtck; /* offset : 0x1818 */
	uint32_t reserved_5[505];
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rot_cmu_rot_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_rot_cmu_rot_ipclkport_pclk; /* offset : 0x2000 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_top_ipclkport_sys_cm_clk
		clk_con_gat_clk_blk_rot_uid_rt_top_ipclkport_sys_cm_clk; /* offset : 0x2004 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram0_ipclkport_ck
		clk_con_gat_clk_blk_rot_uid_rt_sram0_ipclkport_ck; /* offset : 0x2008 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram1_ipclkport_ck
		clk_con_gat_clk_blk_rot_uid_rt_sram1_ipclkport_ck; /* offset : 0x200c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram2_ipclkport_ck
		clk_con_gat_clk_blk_rot_uid_rt_sram2_ipclkport_ck; /* offset : 0x2010 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_rt_sram3_ipclkport_ck
		clk_con_gat_clk_blk_rot_uid_rt_sram3_ipclkport_ck; /* offset : 0x2014 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_dma_rot_ipclkport_aclk
		clk_con_gat_clk_blk_rot_uid_dma_rot_ipclkport_aclk; /* offset : 0x2018 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_m
		clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_m; /* offset : 0x201c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_async_dma_ipclkport_clk_s; /* offset : 0x2020 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_tbu_rot_ipclkport_aclk
		clk_con_gat_clk_blk_rot_uid_tbu_rot_ipclkport_aclk; /* offset : 0x2024 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_pe_wrapper_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_pe_wrapper_ipclkport_clk_s; /* offset : 0x2028 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_oscclk
		clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_oscclk; /* offset : 0x202c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_test_scan_osc_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_i_test_scan_osc_clk; /* offset : 0x2030 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_otp_con_soc_ipclkport_pclk; /* offset : 0x2034 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_soc_mem_wrapper_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_soc_mem_wrapper_ipclkport_clk; /* offset : 0x2038 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_noc_rot_ipclkport_aclk
		clk_con_gat_clk_blk_rot_uid_noc_rot_ipclkport_aclk; /* offset : 0x203c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk
		clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk; /* offset : 0x2040 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk_r
		clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_ackclk_r; /* offset : 0x2044 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk
		clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk; /* offset : 0x2048 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk_r
		clk_con_gat_clk_blk_rot_uid_nic_rot_ipclkport_pckclk_r; /* offset : 0x204c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_dst
		clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_dst; /* offset : 0x2050 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_etc
		clk_con_gat_clk_blk_rot_uid_lh_ipclkport_i_scan_clk_etc; /* offset : 0x2054 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_d0_si_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_rotm_d0_si_ipclkport_i_clk; /* offset : 0x2058 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rots_p_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_rots_p_mi_ipclkport_i_clk; /* offset : 0x205c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_d1_si_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_rotm_d1_si_ipclkport_i_clk; /* offset : 0x2060 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t0_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp0m_t0_mi_ipclkport_i_clk; /* offset : 0x2064 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t1_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp0m_t1_mi_ipclkport_i_clk; /* offset : 0x2068 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t2_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp0m_t2_mi_ipclkport_i_clk; /* offset : 0x206c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t3_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp0m_t3_mi_ipclkport_i_clk; /* offset : 0x2070 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp0m_t4_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp0m_t4_mi_ipclkport_i_clk; /* offset : 0x2074 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rots_ast_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_rots_ast_mi_ipclkport_i_clk; /* offset : 0x2078 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_rotm_ast_si_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_rotm_ast_si_ipclkport_i_clk; /* offset : 0x207c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t0_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp1m_t0_mi_ipclkport_i_clk; /* offset : 0x2080 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t1_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp1m_t1_mi_ipclkport_i_clk; /* offset : 0x2084 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t2_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp1m_t2_mi_ipclkport_i_clk; /* offset : 0x2088 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t3_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp1m_t3_mi_ipclkport_i_clk; /* offset : 0x208c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_cp1m_t4_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_cp1m_t4_mi_ipclkport_i_clk; /* offset : 0x2090 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_pciem_t_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_pciem_t_mi_ipclkport_i_clk; /* offset : 0x2094 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t0_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_nbusm_t0_mi_ipclkport_i_clk; /* offset : 0x2098 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t1_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_nbusm_t1_mi_ipclkport_i_clk; /* offset : 0x209c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_lh_nbusm_t2_mi_ipclkport_i_clk
		clk_con_gat_clk_blk_rot_uid_lh_nbusm_t2_mi_ipclkport_i_clk; /* offset : 0x20a0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp0s_g0_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_cp0s_g0_si_ipclkport_clk_s; /* offset : 0x20a4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp0s_g1_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_cp0s_g1_si_ipclkport_clk_s; /* offset : 0x20a8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp1s_g0_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_cp1s_g0_si_ipclkport_clk_s; /* offset : 0x20ac */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_cp1s_g1_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_cp1s_g1_si_ipclkport_clk_s; /* offset : 0x20b0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_pcies_g0_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_pcies_g0_si_ipclkport_clk_s; /* offset : 0x20b4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_pcies_g1_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_pcies_g1_si_ipclkport_clk_s; /* offset : 0x20b8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_apb_nbuss_g_si_ipclkport_clk_s
		clk_con_gat_clk_blk_rot_uid_apb_nbuss_g_si_ipclkport_clk_s; /* offset : 0x20bc */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_trace_ipclkport_i_aclk
		clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_trace_ipclkport_i_aclk; /* offset : 0x20c0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_debug_ipclkport_i_aclk
		clk_con_gat_clk_blk_rot_uid_amba_ovrd_cs_debug_ipclkport_i_aclk; /* offset : 0x20c4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_rt630_ipclkport_i_aclk
		clk_con_gat_clk_blk_rot_uid_amba_ovrd_rt630_ipclkport_i_aclk; /* offset : 0x20c8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_amba_ovrd_dma330_ipclkport_i_aclk
		clk_con_gat_clk_blk_rot_uid_amba_ovrd_dma330_ipclkport_i_aclk; /* offset : 0x20cc */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_sysreg_sysremap_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_sysreg_sysremap_ipclkport_pclk; /* offset : 0x20d0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_hclk
		clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_hclk; /* offset : 0x20d4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_ssi_clk
		clk_con_gat_clk_blk_rot_uid_qspi_boot_ipclkport_ssi_clk; /* offset : 0x20d8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_intmem_rot_ipclkport_aclk
		clk_con_gat_clk_blk_rot_uid_intmem_rot_ipclkport_aclk; /* offset : 0x20dc */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_tsclk
		clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_tsclk; /* offset : 0x20e0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_cntclk
		clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_cntclk; /* offset : 0x20e4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_pclkdbg
		clk_con_gat_clk_blk_rot_uid_cssys_top_ipclkport_pclkdbg; /* offset : 0x20e8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_sysreg_rot_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_sysreg_rot_ipclkport_pclk; /* offset : 0x20ec */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m0_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_mailbox_m0_ipclkport_pclk; /* offset : 0x20f0 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m1_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_mailbox_m1_ipclkport_pclk; /* offset : 0x20f4 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_mailbox_m2_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_mailbox_m2_ipclkport_pclk; /* offset : 0x20f8 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_ecc_bridge_top_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_ecc_bridge_top_ipclkport_clk; /* offset : 0x20fc */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_sec_ap_sfr_apbif_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_sec_ap_sfr_apbif_ipclkport_pclk; /* offset : 0x2100 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_oscclk
		clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_oscclk; /* offset : 0x2104 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_gpio_rot_ipclkport_pclk; /* offset : 0x2108 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_clk; /* offset : 0x210c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_pvt_rot_controller_ipclkport_pclk; /* offset : 0x2110 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_mem_wrapper_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_cpu_mem_wrapper_ipclkport_clk; /* offset : 0x2114 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_oscclk
		clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_oscclk; /* offset : 0x2118 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_pclk; /* offset : 0x211c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_test_scan_osc_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_cpu_ipclkport_i_test_scan_osc_clk; /* offset : 0x2120 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_mem_wrapper_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_mem_wrapper_ipclkport_clk; /* offset : 0x2124 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_oscclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_oscclk; /* offset : 0x2128 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_pclk; /* offset : 0x212c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_test_scan_osc_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s0_ipclkport_i_test_scan_osc_clk;
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_mem_wrapper_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_mem_wrapper_ipclkport_clk; /* offset : 0x2134 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_oscclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_oscclk; /* offset : 0x2138 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_pclk; /* offset : 0x213c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_test_scan_osc_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s1_ipclkport_i_test_scan_osc_clk;
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_mem_wrapper_ipclkport_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_mem_wrapper_ipclkport_clk; /* offset : 0x2144 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_oscclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_oscclk; /* offset : 0x2148 */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_pclk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_pclk; /* offset : 0x214c */
	union cmu_rot_clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_test_scan_osc_clk
		clk_con_gat_clk_blk_rot_uid_otp_con_top_s2_ipclkport_i_test_scan_osc_clk;
	uint32_t reserved_6[939];
	union cmu_rot_qch_con_rt_top_qch qch_con_rt_top_qch; /* offset : 0x3000 */
	union cmu_rot_qch_con_rt_sram0_qch qch_con_rt_sram0_qch; /* offset : 0x3004 */
	union cmu_rot_qch_con_rt_sram1_qch qch_con_rt_sram1_qch; /* offset : 0x3008 */
	union cmu_rot_qch_con_rt_sram2_qch qch_con_rt_sram2_qch; /* offset : 0x300c */
	union cmu_rot_qch_con_rt_sram3_qch qch_con_rt_sram3_qch; /* offset : 0x3010 */
	union cmu_rot_qch_con_dma_rot_qch qch_con_dma_rot_qch; /* offset : 0x3014 */
	union cmu_rot_qch_con_pe_wrapper_qch_s qch_con_pe_wrapper_qch_s; /* offset : 0x3018 */
	union cmu_rot_qch_con_pe_wrapper_qch_d qch_con_pe_wrapper_qch_d; /* offset : 0x301c */
	union cmu_rot_qch_con_otp_con_soc_qch qch_con_otp_con_soc_qch; /* offset : 0x3020 */
	union cmu_rot_qch_con_otp_con_soc_mem_wrapper_qch
		qch_con_otp_con_soc_mem_wrapper_qch; /* offset : 0x3024 */
	union cmu_rot_qch_con_noc_rot_qch qch_con_noc_rot_qch; /* offset : 0x3028 */
	union cmu_rot_qch_con_nic_rot_qch qch_con_nic_rot_qch; /* offset : 0x302c */
	union cmu_rot_qch_con_lh_qch qch_con_lh_qch; /* offset : 0x3030 */
	union cmu_rot_qch_con_amba_ovrd_cs_trace_qch
		qch_con_amba_ovrd_cs_trace_qch; /* offset : 0x3034 */
	union cmu_rot_qch_con_amba_ovrd_cs_debug_qch
		qch_con_amba_ovrd_cs_debug_qch; /* offset : 0x3038 */
	union cmu_rot_qch_con_amba_ovrd_rt630_qch qch_con_amba_ovrd_rt630_qch; /* offset : 0x303c */
	union cmu_rot_qch_con_amba_ovrd_dma330_qch qch_con_amba_ovrd_dma330_qch; /* offset : 0x3040 */
	union cmu_rot_qch_con_qspi_boot_qch qch_con_qspi_boot_qch; /* offset : 0x3044 */
	union cmu_rot_qch_con_intmem_rot_qch qch_con_intmem_rot_qch; /* offset : 0x3048 */
	union cmu_rot_qch_con_cssys_top_qch qch_con_cssys_top_qch; /* offset : 0x304c */
	union cmu_rot_qch_con_axi2apb_rot_qch qch_con_axi2apb_rot_qch; /* offset : 0x3050 */
	union cmu_rot_qch_con_ecc_bridge_top_qch qch_con_ecc_bridge_top_qch; /* offset : 0x3054 */
	union cmu_rot_qch_con_gpio_rot_qch qch_con_gpio_rot_qch; /* offset : 0x3058 */
	union cmu_rot_qch_con_pvt_rot_controller_qch
		qch_con_pvt_rot_controller_qch; /* offset : 0x305c */
	union cmu_rot_qch_con_otp_con_cpu_mem_wrapper_qch
		qch_con_otp_con_cpu_mem_wrapper_qch; /* offset : 0x3060 */
	union cmu_rot_qch_con_otp_con_cpu_qch qch_con_otp_con_cpu_qch; /* offset : 0x3064 */
	union cmu_rot_qch_con_otp_con_top_s0_mem_wrapper_qch
		qch_con_otp_con_top_s0_mem_wrapper_qch; /* offset : 0x3068 */
	union cmu_rot_qch_con_otp_con_top_s0_qch qch_con_otp_con_top_s0_qch; /* offset : 0x306c */
	union cmu_rot_qch_con_otp_con_top_s1_mem_wrapper_qch
		qch_con_otp_con_top_s1_mem_wrapper_qch; /* offset : 0x3070 */
	union cmu_rot_qch_con_otp_con_top_s1_qch qch_con_otp_con_top_s1_qch; /* offset : 0x3074 */
	union cmu_rot_qch_con_otp_con_top_s2_mem_wrapper_qch
		qch_con_otp_con_top_s2_mem_wrapper_qch; /* offset : 0x3078 */
	union cmu_rot_qch_con_otp_con_top_s2_qch qch_con_otp_con_top_s2_qch; /* offset : 0x307c */
	union cmu_rot_qch_con_lh_rotm_d0_si_pch qch_con_lh_rotm_d0_si_pch; /* offset : 0x3080 */
	union cmu_rot_qch_con_lh_rots_p_mi_pch qch_con_lh_rots_p_mi_pch; /* offset : 0x3084 */
	union cmu_rot_qch_con_lh_rotm_d1_si_pch qch_con_lh_rotm_d1_si_pch; /* offset : 0x3088 */
	union cmu_rot_qch_con_lh_cp0m_t0_mi_pch qch_con_lh_cp0m_t0_mi_pch; /* offset : 0x308c */
	union cmu_rot_qch_con_lh_cp0m_t1_mi_pch qch_con_lh_cp0m_t1_mi_pch; /* offset : 0x3090 */
	union cmu_rot_qch_con_lh_cp0m_t2_mi_pch qch_con_lh_cp0m_t2_mi_pch; /* offset : 0x3094 */
	union cmu_rot_qch_con_lh_cp0m_t3_mi_pch qch_con_lh_cp0m_t3_mi_pch; /* offset : 0x3098 */
	union cmu_rot_qch_con_lh_cp0m_t4_mi_pch qch_con_lh_cp0m_t4_mi_pch; /* offset : 0x309c */
	union cmu_rot_qch_con_lh_rots_ast_mi_pch qch_con_lh_rots_ast_mi_pch; /* offset : 0x30a0 */
	union cmu_rot_qch_con_lh_rotm_ast_si_pch qch_con_lh_rotm_ast_si_pch; /* offset : 0x30a4 */
	union cmu_rot_qch_con_lh_cp1m_t0_mi_pch qch_con_lh_cp1m_t0_mi_pch; /* offset : 0x30a8 */
	union cmu_rot_qch_con_lh_cp1m_t1_mi_pch qch_con_lh_cp1m_t1_mi_pch; /* offset : 0x30ac */
	union cmu_rot_qch_con_lh_cp1m_t2_mi_pch qch_con_lh_cp1m_t2_mi_pch; /* offset : 0x30b0 */
	union cmu_rot_qch_con_lh_cp1m_t3_mi_pch qch_con_lh_cp1m_t3_mi_pch; /* offset : 0x30b4 */
	union cmu_rot_qch_con_lh_cp1m_t4_mi_pch qch_con_lh_cp1m_t4_mi_pch; /* offset : 0x30b8 */
	union cmu_rot_qch_con_lh_pciem_t_mi_pch qch_con_lh_pciem_t_mi_pch; /* offset : 0x30bc */
	union cmu_rot_qch_con_lh_nbusm_t0_mi_pch qch_con_lh_nbusm_t0_mi_pch; /* offset : 0x30c0 */
	union cmu_rot_qch_con_lh_nbusm_t1_mi_pch qch_con_lh_nbusm_t1_mi_pch; /* offset : 0x30c4 */
	union cmu_rot_qch_con_lh_nbusm_t2_mi_pch qch_con_lh_nbusm_t2_mi_pch; /* offset : 0x30c8 */
	union cmu_rot_qch_con_rot_cmu_rot_qch qch_con_rot_cmu_rot_qch; /* offset : 0x30cc */
	union cmu_rot_qch_con_apb_async_dma_clk_m qch_con_apb_async_dma_clk_m; /* offset : 0x30d0 */
	union cmu_rot_qch_con_apb_async_dma_clk_s qch_con_apb_async_dma_clk_s; /* offset : 0x30d4 */
	union cmu_rot_qch_con_apb_async_dma_pwr qch_con_apb_async_dma_pwr; /* offset : 0x30d8 */
	union cmu_rot_qch_con_tbu_rot_qch_cg qch_con_tbu_rot_qch_cg; /* offset : 0x30dc */
	union cmu_rot_qch_con_tbu_rot_qch_pd qch_con_tbu_rot_qch_pd; /* offset : 0x30e0 */
	union cmu_rot_qch_con_otp_con_soc_qch_s qch_con_otp_con_soc_qch_s; /* offset : 0x30e4 */
	union cmu_rot_qch_con_lh_rotm_d0_si_qch qch_con_lh_rotm_d0_si_qch; /* offset : 0x30e8 */
	union cmu_rot_qch_con_lh_rots_p_mi_qch qch_con_lh_rots_p_mi_qch; /* offset : 0x30ec */
	union cmu_rot_qch_con_lh_rotm_d1_si_qch qch_con_lh_rotm_d1_si_qch; /* offset : 0x30f0 */
	union cmu_rot_qch_con_lh_cp0m_t0_mi_qch qch_con_lh_cp0m_t0_mi_qch; /* offset : 0x30f4 */
	union cmu_rot_qch_con_lh_cp0m_t1_mi_qch qch_con_lh_cp0m_t1_mi_qch; /* offset : 0x30f8 */
	union cmu_rot_qch_con_lh_cp0m_t2_mi_qch qch_con_lh_cp0m_t2_mi_qch; /* offset : 0x30fc */
	union cmu_rot_qch_con_lh_cp0m_t3_mi_qch qch_con_lh_cp0m_t3_mi_qch; /* offset : 0x3100 */
	union cmu_rot_qch_con_lh_cp0m_t4_mi_qch qch_con_lh_cp0m_t4_mi_qch; /* offset : 0x3104 */
	union cmu_rot_qch_con_lh_rots_ast_mi_qch qch_con_lh_rots_ast_mi_qch; /* offset : 0x3108 */
	union cmu_rot_qch_con_lh_rotm_ast_si_qch qch_con_lh_rotm_ast_si_qch; /* offset : 0x310c */
	union cmu_rot_qch_con_lh_cp1m_t0_mi_qch qch_con_lh_cp1m_t0_mi_qch; /* offset : 0x3110 */
	union cmu_rot_qch_con_lh_cp1m_t1_mi_qch qch_con_lh_cp1m_t1_mi_qch; /* offset : 0x3114 */
	union cmu_rot_qch_con_lh_cp1m_t2_mi_qch qch_con_lh_cp1m_t2_mi_qch; /* offset : 0x3118 */
	union cmu_rot_qch_con_lh_cp1m_t3_mi_qch qch_con_lh_cp1m_t3_mi_qch; /* offset : 0x311c */
	union cmu_rot_qch_con_lh_cp1m_t4_mi_qch qch_con_lh_cp1m_t4_mi_qch; /* offset : 0x3120 */
	union cmu_rot_qch_con_lh_pciem_t_mi_qch qch_con_lh_pciem_t_mi_qch; /* offset : 0x3124 */
	union cmu_rot_qch_con_lh_nbusm_t0_mi_qch qch_con_lh_nbusm_t0_mi_qch; /* offset : 0x3128 */
	union cmu_rot_qch_con_lh_nbusm_t1_mi_qch qch_con_lh_nbusm_t1_mi_qch; /* offset : 0x312c */
	union cmu_rot_qch_con_lh_nbusm_t2_mi_qch qch_con_lh_nbusm_t2_mi_qch; /* offset : 0x3130 */
	union cmu_rot_qch_con_apb_cp0s_g0_si_qch_clk
		qch_con_apb_cp0s_g0_si_qch_clk; /* offset : 0x3134 */
	union cmu_rot_qch_con_apb_cp0s_g0_si_qch_pwr
		qch_con_apb_cp0s_g0_si_qch_pwr; /* offset : 0x3138 */
	union cmu_rot_qch_con_apb_cp0s_g1_si_qch_clk
		qch_con_apb_cp0s_g1_si_qch_clk; /* offset : 0x313c */
	union cmu_rot_qch_con_apb_cp0s_g1_si_qch_pwr
		qch_con_apb_cp0s_g1_si_qch_pwr; /* offset : 0x3140 */
	union cmu_rot_qch_con_apb_cp1s_g0_si_qch_clk
		qch_con_apb_cp1s_g0_si_qch_clk; /* offset : 0x3144 */
	union cmu_rot_qch_con_apb_cp1s_g0_si_qch_pwr
		qch_con_apb_cp1s_g0_si_qch_pwr; /* offset : 0x3148 */
	union cmu_rot_qch_con_apb_cp1s_g1_si_qch_clk
		qch_con_apb_cp1s_g1_si_qch_clk; /* offset : 0x314c */
	union cmu_rot_qch_con_apb_cp1s_g1_si_qch_pwr
		qch_con_apb_cp1s_g1_si_qch_pwr; /* offset : 0x3150 */
	union cmu_rot_qch_con_apb_pcies_g0_si_qch_clk
		qch_con_apb_pcies_g0_si_qch_clk; /* offset : 0x3154 */
	union cmu_rot_qch_con_apb_pcies_g0_si_qch_pwr
		qch_con_apb_pcies_g0_si_qch_pwr; /* offset : 0x3158 */
	union cmu_rot_qch_con_apb_pcies_g1_si_qch_clk
		qch_con_apb_pcies_g1_si_qch_clk; /* offset : 0x315c */
	union cmu_rot_qch_con_apb_pcies_g1_si_qch_pwr
		qch_con_apb_pcies_g1_si_qch_pwr; /* offset : 0x3160 */
	union cmu_rot_qch_con_apb_nbuss_g_si_qch_clk
		qch_con_apb_nbuss_g_si_qch_clk; /* offset : 0x3164 */
	union cmu_rot_qch_con_apb_nbuss_g_si_qch_pwr
		qch_con_apb_nbuss_g_si_qch_pwr; /* offset : 0x3168 */
	union cmu_rot_qch_con_sysreg_sysremap_qch qch_con_sysreg_sysremap_qch; /* offset : 0x316c */
	union cmu_rot_qch_con_cssys_top_qch_s qch_con_cssys_top_qch_s; /* offset : 0x3170 */
	union cmu_rot_qch_con_sysreg_rot_qch qch_con_sysreg_rot_qch; /* offset : 0x3174 */
	union cmu_rot_qch_con_mailbox_m0_qch qch_con_mailbox_m0_qch; /* offset : 0x3178 */
	union cmu_rot_qch_con_mailbox_m1_qch qch_con_mailbox_m1_qch; /* offset : 0x317c */
	union cmu_rot_qch_con_mailbox_m2_qch qch_con_mailbox_m2_qch; /* offset : 0x3180 */
	union cmu_rot_qch_con_sec_ap_sfr_apbif_qch_s
		qch_con_sec_ap_sfr_apbif_qch_s; /* offset : 0x3184 */
	union cmu_rot_qch_con_gpio_rot_qch_s qch_con_gpio_rot_qch_s; /* offset : 0x3188 */
	union cmu_rot_qch_con_otp_con_cpu_qch_s qch_con_otp_con_cpu_qch_s; /* offset : 0x318c */
	union cmu_rot_qch_con_otp_con_top_s0_qch_s qch_con_otp_con_top_s0_qch_s; /* offset : 0x3190 */
	union cmu_rot_qch_con_otp_con_top_s1_qch_s qch_con_otp_con_top_s1_qch_s; /* offset : 0x3194 */
	union cmu_rot_qch_con_otp_con_top_s2_qch_s qch_con_otp_con_top_s2_qch_s; /* offset : 0x3198 */
};

enum ROT_CLK_OUT {
	OSCCLK_ROT,
	PLL_ROT,
	CLK_ROT_ACLK,
	CLK_ROT_PCLK,
	CLK_ROT_PVT_mainCLK,
	CLK_ROT_DFT,
	CLK_ROT_OSCCLK,
	CLK_ROT_OTPCLK,
	CM_SYS_TST_FRO_CLK_OUT,
	CLK_ROT_CNTCLK,
	CLK_ROT_TSCLK,
	CLK_ROT_RTCK,
	ROT_CLK_LH_SCAN_DST,
	ROT_CLK_LH_SCAN_ETC,
};
