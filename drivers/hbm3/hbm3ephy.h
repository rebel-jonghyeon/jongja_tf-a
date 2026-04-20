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

union hbm3ephy_gnr_con0 {
	struct {
		uint32_t ctrl_rdlat:7; /* [6:0] */
		uint32_t ctrl_twpre:2; /* [8:7] */
		uint32_t ctrl_fnc_fb:3; /* [11:9] */
		uint32_t ctrl_dfrdqs:1; /* [12:12] */
		uint32_t ctrl_dfwdqs:1; /* [13:13] */
		uint32_t init_resync_mode:1; /* [14:14] */
		uint32_t ctrl_upd_time:2; /* [16:15] */
		uint32_t phy2x_bypass:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con0 {
	struct {
		uint32_t wrlvl_mode:1; /* [0:0] */
		uint32_t ca_cal_mode:1; /* [1:1] */
		uint32_t rd_cal_mode:1; /* [2:2] */
		uint32_t wr_cal_mode:1; /* [3:3] */
		uint32_t rdlvl_dqs_edge_en:2; /* [5:4] */
		uint32_t wrtrn_dqs_edge_en:2; /* [7:6] */
		uint32_t ctrl_upd_interval:2; /* [9:8] */
		uint32_t cal_vtc_en:1; /* [10:10] */
		uint32_t freq_offset_en:1; /* [11:11] */
		uint32_t dfs_wr_train_en:1; /* [12:12] */
		uint32_t reserved1:4; /* [16:13] */
		uint32_t wrlvl_start:1; /* [17:17] */
		uint32_t wrlvl_resp:1; /* [18:18] */
		uint32_t dfi_dram_clk_disable_apb:1; /* [19:19] */
		uint32_t rdtrn_pattern_change_en_apb:1; /* [20:20] */
		uint32_t rdtrn_lfsr_mode_en:1; /* [21:21] */
		uint32_t wrtrn_lfsr_mode_en:1; /* [22:22] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con1 {
	struct {
		uint32_t rdlvl_periodic_incr_adj:7; /* [6:0] */
		uint32_t rdtrn_ecc_cal_en:1; /* [7:7] */
		uint32_t wrtrn_ecc_cal_en:1; /* [8:8] */
		uint32_t wrtrn_wr_par_cal_en:1; /* [9:9] */
		uint32_t wrtrn_dbi_cal_en:1; /* [10:10] */
		uint32_t rdtrn_dbi_cal_en:1; /* [11:11] */
		uint32_t rdlvl_pass_adj:4; /* [15:12] */
		uint32_t rdlvl_incr_adj:7; /* [22:16] */
		uint32_t rdlvl_start_adj:4; /* [26:23] */
		uint32_t wrtrn_pass_adj:4; /* [30:27] */
		uint32_t rdlvl_rank_offset_update:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con2 {
	struct {
		uint32_t ctrl_read_width:1; /* [0:0] */
		uint32_t reserved2:1; /* [1:1] */
		uint32_t ctrl_wrlat_bbfifo:4; /* [5:2] */
		uint32_t reserved1:1; /* [6:6] */
		uint32_t wrtrn_lfsr_sev_cal_en:1; /* [7:7] */
		uint32_t wrtrn_lfsr_ecc_cal_en:1; /* [8:8] */
		uint32_t wrtrn_lfsr_dbi_cal_en:1; /* [9:9] */
		uint32_t ctrl_readadj:7; /* [16:10] */
		uint32_t ctrl_readduradj:7; /* [23:17] */
		uint32_t lock_avg_cnt_number:6; /* [29:24] */
		uint32_t rdlvl_rank_par_offset_update:1; /* [30:30] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con3 {
	struct {
		uint32_t pcfg_mode:3; /* [2:0] */
		uint32_t min_locktime_adj:2; /* [4:3] */
		uint32_t prbs_sw_mode:1; /* [5:5] */
		uint32_t wrlvl_sw_mode:1; /* [6:6] */
		uint32_t rd_sw_mode:1; /* [7:7] */
		uint32_t wr_sw_mode:1; /* [8:8] */
		uint32_t num_repeat:5; /* [13:9] */
		uint32_t wrtrn_cyc_en:1; /* [14:14] */
		uint32_t wrtrn_cyc_mode:1; /* [15:15] */
		uint32_t wrtrn_cyc_th:8; /* [23:16] */
		uint32_t rdtrn_sev_cal_en:1; /* [24:24] */
		uint32_t wrtrn_sev_cal_en:1; /* [25:25] */
		uint32_t periodic_rdtrn_fast_mode:1; /* [26:26] */
		uint32_t periodic_wrtrn_fast_mode:1; /* [27:27] */
		uint32_t rdtrn_restore:1; /* [28:28] */
		uint32_t rdtrn_lfsr_sev_cal_en:1; /* [29:29] */
		uint32_t rdtrn_lfsr_ecc_cal_en:1; /* [30:30] */
		uint32_t rdtrn_lfsr_dbi_cal_en:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con4 {
	struct {
		uint32_t phy_train_en:1; /* [0:0] */
		uint32_t phy_wrlvl_en:1; /* [1:1] */
		uint32_t phy_rdtrn_en:1; /* [2:2] */
		uint32_t phy_wrtrn_en:1; /* [3:3] */
		uint32_t phy_prbs_rdtrn_en:1; /* [4:4] */
		uint32_t phy_prbs_wrtrn_en:1; /* [5:5] */
		uint32_t phy_rdtrn_par_en:1; /* [6:6] */
		uint32_t phy_train_done:1; /* [7:7] */
		uint32_t periodic_wrtrn_en:1; /* [8:8] */
		uint32_t periodic_rdtrn_en:1; /* [9:9] */
		uint32_t polling_rdtrn_en:1; /* [10:10] */
		uint32_t reserved1:1; /* [11:11] */
		uint32_t phy_mstr_bypass:1; /* [12:12] */
		uint32_t periodic_train_force:1; /* [13:13] */
		uint32_t phy_mstr_cnt_en:1; /* [14:14] */
		uint32_t ctrl_readadj_dqs:7; /* [21:15] */
		uint32_t ctrl_readduradj_dqs:7; /* [28:22] */
		uint32_t phy_mstr_state_sel:1; /* [29:29] */
		uint32_t periodic_train_mode:1; /* [30:30] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_cal_con5 {
	struct {
		uint32_t periodic_time:31; /* [30:0] */
		uint32_t periodic_en:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_lock_check_con {
	struct {
		uint32_t lock_check_avg_en:1; /* [0:0] */
		uint32_t lock_check_avg_n_sel:2; /* [2:1] */
		uint32_t lock_average_en:1; /* [3:3] */
		uint32_t get_avg_lock_extend:2; /* [5:4] */
		uint32_t lock_ratio_threshold:5; /* [10:6] */
		uint32_t lock_diff_threshold:11; /* [21:11] */
		uint32_t lock_sample_condition:2; /* [23:22] */
		uint32_t lock_check_diff_en:1; /* [24:24] */
		uint32_t avg_window_size:2; /* [26:25] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_lp_con0 {
	struct {
		uint32_t ctrl_pulld_dq:1; /* [0:0] */
		uint32_t mdll_dcg_en:1; /* [1:1] */
		uint32_t pcl_pd:1; /* [2:2] */
		uint32_t tlp_ctrl_wakeup:3; /* [5:3] */
		uint32_t tlp_ctrl_resp:3; /* [8:6] */
		uint32_t tlp_data_wakeup:3; /* [11:9] */
		uint32_t tlp_data_resp:3; /* [14:12] */
		uint32_t ds_io_pd:1; /* [15:15] */
		uint32_t reserved1:1; /* [16:16] */
		uint32_t dqs_enable:1; /* [17:17] */
		uint32_t ctrl_dqs_drv_off:1; /* [18:18] */
		uint32_t ctrl_scheduler_en:1; /* [19:19] */
		uint32_t scheduler_hw_clock_gating_disable:1; /* [20:20] */
		uint32_t phy_cg_en_dword:2; /* [22:21] */
		uint32_t phy_cg_en_aword:1; /* [23:23] */
		uint32_t clkhg_always_on_apb:2; /* [25:24] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_offsetr_con0 {
	struct {
		uint32_t ctrl_offsetr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t ctrl_offsetr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_offsetw_con0 {
	struct {
		uint32_t ctrl_offsetw0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t ctrl_offsetw1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_offset_dq_con0 {
	struct {
		uint32_t ctrl_offset_dq:7; /* [6:0] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_offsetd_con0 {
	struct {
		uint32_t ctrl_offsetd:9; /* [8:0] */
		uint32_t ctrl_resync:1; /* [9:9] */
		uint32_t upd_mode:1; /* [10:10] */
		uint32_t cmd_falling_mode:1; /* [11:11] */
		uint32_t reserved0:20; /* [31:12] */
	};
	uint32_t val;
};

union hbm3ephy_dfs_con0 {
	struct {
		uint32_t freq_train:12; /* [11:0] */
		uint32_t reserved1:4; /* [15:12] */
		uint32_t freq_change:12; /* [27:16] */
		uint32_t per_dfs_train_disable:1; /* [28:28] */
		uint32_t reserved0:3; /* [31:29] */
	};
	uint32_t val;
};

union hbm3ephy_dfs_con1 {
	struct {
		uint32_t dvfs_freq_apb:12; /* [11:0] */
		uint32_t reserved0:20; /* [31:12] */
	};
	uint32_t val;
};

union hbm3ephy_par_con {
	struct {
		uint32_t cmd_par_en:1; /* [0:0] */
		uint32_t wr_par_en:1; /* [1:1] */
		uint32_t rd_par_en:1; /* [2:2] */
		uint32_t reserved1:2; /* [4:3] */
		uint32_t cmd_par_err_rst_n:1; /* [5:5] */
		uint32_t wr_par_err_rst_n:1; /* [6:6] */
		uint32_t pl:3; /* [9:7] */
		uint32_t reserved0:22; /* [31:10] */
	};
	uint32_t val;
};

union hbm3ephy_aword_glitch_con {
	struct {
		uint32_t ra_glitch_remove_en:10; /* [9:0] */
		uint32_t wdqs_glitch_remove_en:2; /* [11:10] */
		uint32_t ca_glitch_remove_en:8; /* [19:12] */
		uint32_t rrc_glitch_remove_en:1; /* [20:20] */
		uint32_t arfu_glitch_remove_en:1; /* [21:21] */
		uint32_t apar_glitch_remove_en:1; /* [22:22] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_wr_lvl_con0 {
	struct {
		uint32_t reserved1:8; /* [7:0] */
		uint32_t tdqsl:6; /* [13:8] */
		uint32_t twdqs2pd:6; /* [19:14] */
		uint32_t reserved0:12; /* [31:20] */
	};
	uint32_t val;
};

union hbm3ephy_wr_lvl_con1 {
	struct {
		uint32_t ctrl_wrlvl_resync:2; /* [1:0] */
		uint32_t reserved2:1; /* [2:2] */
		uint32_t ctrl_wrlvl_clear:2; /* [4:3] */
		uint32_t reserved1:3; /* [7:5] */
		uint32_t wrlvl_wait:5; /* [12:8] */
		uint32_t reserved0:19; /* [31:13] */
	};
	uint32_t val;
};

union hbm3ephy_wr_lvl_cs0_code0 {
	struct {
		uint32_t ctrl_wrlvl_ds0_rank0:9; /* [8:0] */
		uint32_t reserved1:1; /* [9:9] */
		uint32_t ctrl_wrlvl_ds1_rank0:9; /* [18:10] */
		uint32_t reserved0:13; /* [31:19] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code0 {
	struct {
		uint32_t ca0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code1 {
	struct {
		uint32_t ca2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code2 {
	struct {
		uint32_t ca4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code3 {
	struct {
		uint32_t ca6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code4 {
	struct {
		uint32_t rrcdeskewcode:9; /* [8:0] */
		uint32_t reserved0:23; /* [31:9] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code5 {
	struct {
		uint32_t ra0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code6 {
	struct {
		uint32_t ra2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code7 {
	struct {
		uint32_t ra4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code8 {
	struct {
		uint32_t ra6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code9 {
	struct {
		uint32_t ra8deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra9deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_cmd_deskewc_code10 {
	struct {
		uint32_t arfudeskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t apardeskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code0 {
	struct {
		uint32_t sw_ca0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ca1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code1 {
	struct {
		uint32_t sw_ca2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ca3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code2 {
	struct {
		uint32_t sw_ca4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ca5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code3 {
	struct {
		uint32_t sw_ca6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ca7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code4 {
	struct {
		uint32_t sw_rrcdeskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ckdeskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code5 {
	struct {
		uint32_t sw_ra0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ra1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code6 {
	struct {
		uint32_t sw_ra2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ra3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code7 {
	struct {
		uint32_t sw_ra4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ra5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code8 {
	struct {
		uint32_t sw_ra6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ra7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code9 {
	struct {
		uint32_t sw_ra8deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_ra9deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_cmd_deskewc_code10 {
	struct {
		uint32_t sw_arfudeskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_apardeskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_mdll_con0 {
	struct {
		uint32_t ctrl_half:1; /* [0:0] */
		uint32_t ctrl_ref:4; /* [4:1] */
		uint32_t ctrl_dll_on:1; /* [5:5] */
		uint32_t ctrl_start:1; /* [6:6] */
		uint32_t lock_value_init_override:1; /* [7:7] */
		uint32_t ctrl_force:10; /* [17:8] */
		uint32_t clkm_cg_en_sw:1; /* [18:18] */
		uint32_t ctrl_start_point:7; /* [25:19] */
		uint32_t sfr_dll_fine_track:1; /* [26:26] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_mdll_con1 {
	struct {
		uint32_t ctrl_lock_value:10; /* [9:0] */
		uint32_t ctrl_locked:1; /* [10:10] */
		uint32_t ctrl_flock:1; /* [11:11] */
		uint32_t ctrl_clock:1; /* [12:12] */
		uint32_t ctrl_lock_value_init:11; /* [23:13] */
		uint32_t evt1_ctrl_lock_start:1; /* [24:24] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_dll_update_con0 {
	struct {
		uint32_t ctrl_upd_range:2; /* [1:0] */
		uint32_t upd_range_ext:2; /* [3:2] */
		uint32_t upd_req_timeout_en:1; /* [4:4] */
		uint32_t upd_ack_cycle:8; /* [12:5] */
		uint32_t dvfs_mcupd_req_cycle:6; /* [18:13] */
		uint32_t dfs_wait_cycle:4; /* [22:19] */
		uint32_t dvfs_phyupd_req_cycle:6; /* [28:23] */
		uint32_t reserved0:3; /* [31:29] */
	};
	uint32_t val;
};

union hbm3ephy_dll_update_con1 {
	struct {
		uint32_t vt_mcupd_req_cycle:6; /* [5:0] */
		uint32_t vt_phyupd_req_cycle:6; /* [11:6] */
		uint32_t tphyupd_resp_apb:11; /* [22:12] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_remap_con0 {
	struct {
		uint32_t aword_col_remap:4; /* [3:0] */
		uint32_t aword_row_remap:4; /* [7:4] */
		uint32_t reserved0:24; /* [31:8] */
	};
	uint32_t val;
};

union hbm3ephy_remap_con1 {
	struct {
		uint32_t dword0_remap_byte0:4; /* [3:0] */
		uint32_t dword0_remap_byte1:4; /* [7:4] */
		uint32_t dword0_remap_byte2:4; /* [11:8] */
		uint32_t dword0_remap_byte3:4; /* [15:12] */
		uint32_t dword1_remap_byte0:4; /* [19:16] */
		uint32_t dword1_remap_byte1:4; /* [23:20] */
		uint32_t dword1_remap_byte2:4; /* [27:24] */
		uint32_t dword1_remap_byte3:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dqs_vwmc_code0 {
	struct {
		uint32_t rddqsvwmc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddqsvwmc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq0_deskewc_code0 {
	struct {
		uint32_t rddq0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq1_deskewc_code0 {
	struct {
		uint32_t rddq1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq2_deskewc_code0 {
	struct {
		uint32_t rddq2deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq2deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq3_deskewc_code0 {
	struct {
		uint32_t rddq3deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq3deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq4_deskewc_code0 {
	struct {
		uint32_t rddq4deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq4deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq5_deskewc_code0 {
	struct {
		uint32_t rddq5deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq5deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq6_deskewc_code0 {
	struct {
		uint32_t rddq6deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq6deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq7_deskewc_code0 {
	struct {
		uint32_t rddq7deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq7deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq8_deskewc_code0 {
	struct {
		uint32_t rddq8deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq8deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq9_deskewc_code0 {
	struct {
		uint32_t rddq9deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq9deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq10_deskewc_code0 {
	struct {
		uint32_t rddq10deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq10deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq11_deskewc_code0 {
	struct {
		uint32_t rddq11deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq11deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq12_deskewc_code0 {
	struct {
		uint32_t rddq12deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq12deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq13_deskewc_code0 {
	struct {
		uint32_t rddq13deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq13deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq14_deskewc_code0 {
	struct {
		uint32_t rddq14deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq14deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq15_deskewc_code0 {
	struct {
		uint32_t rddq15deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq15deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq16_deskewc_code0 {
	struct {
		uint32_t rddq16deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq16deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq17_deskewc_code0 {
	struct {
		uint32_t rddq17deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq17deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq18_deskewc_code0 {
	struct {
		uint32_t rddq18deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq18deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq19_deskewc_code0 {
	struct {
		uint32_t rddq19deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq19deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq20_deskewc_code0 {
	struct {
		uint32_t rddq20deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq20deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq21_deskewc_code0 {
	struct {
		uint32_t rddq21deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq21deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq22_deskewc_code0 {
	struct {
		uint32_t rddq22deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq22deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq23_deskewc_code0 {
	struct {
		uint32_t rddq23deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq23deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq24_deskewc_code0 {
	struct {
		uint32_t rddq24deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq24deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq25_deskewc_code0 {
	struct {
		uint32_t rddq25deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq25deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq26_deskewc_code0 {
	struct {
		uint32_t rddq26deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq26deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq27_deskewc_code0 {
	struct {
		uint32_t rddq27deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq27deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq28_deskewc_code0 {
	struct {
		uint32_t rddq28deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq28deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq29_deskewc_code0 {
	struct {
		uint32_t rddq29deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq29deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq30_deskewc_code0 {
	struct {
		uint32_t rddq30deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq30deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq31_deskewc_code0 {
	struct {
		uint32_t rddq31deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq31deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_ecc0_deskewc_code0 {
	struct {
		uint32_t rdecc0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdecc0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_ecc1_deskewc_code0 {
	struct {
		uint32_t rdecc1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdecc1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_sev0_deskewc_code0 {
	struct {
		uint32_t rdsev0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdsev0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_sev1_deskewc_code0 {
	struct {
		uint32_t rdsev1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdsev1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi0_deskewc_code0 {
	struct {
		uint32_t rddbi0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi1_deskewc_code0 {
	struct {
		uint32_t rddbi1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi2_deskewc_code0 {
	struct {
		uint32_t rddbi2deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi2deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi3_deskewc_code0 {
	struct {
		uint32_t rddbi3deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi3deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_par_deskewc_code0 {
	struct {
		uint32_t rdpardeskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdpardeskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dqs_vwmc_code0 {
	struct {
		uint32_t sw_rddqsvwmc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_rddqsvwmc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq0_deskewc_code0 {
	struct {
		uint32_t sw_rddq0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq1_deskewc_code0 {
	struct {
		uint32_t sw_rddq1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq2_deskewc_code0 {
	struct {
		uint32_t sw_rddq2deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq2deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq3_deskewc_code0 {
	struct {
		uint32_t sw_rddq3deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq3deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq4_deskewc_code0 {
	struct {
		uint32_t sw_rddq4deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq4deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq5_deskewc_code0 {
	struct {
		uint32_t sw_rddq5deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq5deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq6_deskewc_code0 {
	struct {
		uint32_t sw_rddq6deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq6deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq7_deskewc_code0 {
	struct {
		uint32_t sw_rddq7deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq7deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq8_deskewc_code0 {
	struct {
		uint32_t sw_rddq8deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq8deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq9_deskewc_code0 {
	struct {
		uint32_t sw_rddq9deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq9deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq10_deskewc_code0 {
	struct {
		uint32_t sw_rddq10deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq10deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq11_deskewc_code0 {
	struct {
		uint32_t sw_rddq11deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq11deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq12_deskewc_code0 {
	struct {
		uint32_t sw_rddq12deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq12deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq13_deskewc_code0 {
	struct {
		uint32_t sw_rddq13deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq13deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq14_deskewc_code0 {
	struct {
		uint32_t sw_rddq14deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq14deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq15_deskewc_code0 {
	struct {
		uint32_t sw_rddq15deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq15deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq16_deskewc_code0 {
	struct {
		uint32_t sw_rddq16deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq16deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq17_deskewc_code0 {
	struct {
		uint32_t sw_rddq17deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq17deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq18_deskewc_code0 {
	struct {
		uint32_t sw_rddq18deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq18deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq19_deskewc_code0 {
	struct {
		uint32_t sw_rddq19deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq19deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq20_deskewc_code0 {
	struct {
		uint32_t sw_rddq20deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq20deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq21_deskewc_code0 {
	struct {
		uint32_t sw_rddq21deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq21deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq22_deskewc_code0 {
	struct {
		uint32_t sw_rddq22deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq22deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq23_deskewc_code0 {
	struct {
		uint32_t sw_rddq23deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq23deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq24_deskewc_code0 {
	struct {
		uint32_t sw_rddq24deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq24deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq25_deskewc_code0 {
	struct {
		uint32_t sw_rddq25deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq25deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq26_deskewc_code0 {
	struct {
		uint32_t sw_rddq26deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq26deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq27_deskewc_code0 {
	struct {
		uint32_t sw_rddq27deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq27deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq28_deskewc_code0 {
	struct {
		uint32_t sw_rddq28deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq28deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq29_deskewc_code0 {
	struct {
		uint32_t sw_rddq29deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq29deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq30_deskewc_code0 {
	struct {
		uint32_t sw_rddq30deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq30deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq31_deskewc_code0 {
	struct {
		uint32_t sw_rddq31deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq31deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_ecc0_deskewc_code0 {
	struct {
		uint32_t sw_rdecc0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdecc0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_ecc1_deskewc_code0 {
	struct {
		uint32_t sw_rdecc1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdecc1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_sev0_deskewc_code0 {
	struct {
		uint32_t sw_rdsev0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdsev0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_sev1_deskewc_code0 {
	struct {
		uint32_t sw_rdsev1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdsev1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi0_deskewc_code0 {
	struct {
		uint32_t sw_rddbi0deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi0deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi1_deskewc_code0 {
	struct {
		uint32_t sw_rddbi1deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi1deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi2_deskewc_code0 {
	struct {
		uint32_t sw_rddbi2deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi2deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi3_deskewc_code0 {
	struct {
		uint32_t sw_rddbi3deskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi3deskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_par_deskewc_code0 {
	struct {
		uint32_t sw_rdpardeskewc0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdpardeskewc1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq0_deskewc_code0 {
	struct {
		uint32_t wrdq0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq1_deskewc_code0 {
	struct {
		uint32_t wrdq1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq2_deskewc_code0 {
	struct {
		uint32_t wrdq2deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq2deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq3_deskewc_code0 {
	struct {
		uint32_t wrdq3deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq3deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq4_deskewc_code0 {
	struct {
		uint32_t wrdq4deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq4deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq5_deskewc_code0 {
	struct {
		uint32_t wrdq5deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq5deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq6_deskewc_code0 {
	struct {
		uint32_t wrdq6deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq6deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq7_deskewc_code0 {
	struct {
		uint32_t wrdq7deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq7deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq8_deskewc_code0 {
	struct {
		uint32_t wrdq8deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq8deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq9_deskewc_code0 {
	struct {
		uint32_t wrdq9deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq9deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq10_deskewc_code0 {
	struct {
		uint32_t wrdq10deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq10deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq11_deskewc_code0 {
	struct {
		uint32_t wrdq11deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq11deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq12_deskewc_code0 {
	struct {
		uint32_t wrdq12deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq12deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq13_deskewc_code0 {
	struct {
		uint32_t wrdq13deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq13deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq14_deskewc_code0 {
	struct {
		uint32_t wrdq14deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq14deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq15_deskewc_code0 {
	struct {
		uint32_t wrdq15deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq15deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq16_deskewc_code0 {
	struct {
		uint32_t wrdq16deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq16deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq17_deskewc_code0 {
	struct {
		uint32_t wrdq17deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq17deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq18_deskewc_code0 {
	struct {
		uint32_t wrdq18deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq18deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq19_deskewc_code0 {
	struct {
		uint32_t wrdq19deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq19deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq20_deskewc_code0 {
	struct {
		uint32_t wrdq20deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq20deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq21_deskewc_code0 {
	struct {
		uint32_t wrdq21deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq21deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq22_deskewc_code0 {
	struct {
		uint32_t wrdq22deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq22deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq23_deskewc_code0 {
	struct {
		uint32_t wrdq23deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq23deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq24_deskewc_code0 {
	struct {
		uint32_t wrdq24deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq24deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq25_deskewc_code0 {
	struct {
		uint32_t wrdq25deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq25deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq26_deskewc_code0 {
	struct {
		uint32_t wrdq26deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq26deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq27_deskewc_code0 {
	struct {
		uint32_t wrdq27deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq27deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq28_deskewc_code0 {
	struct {
		uint32_t wrdq28deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq28deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq29_deskewc_code0 {
	struct {
		uint32_t wrdq29deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq29deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq30_deskewc_code0 {
	struct {
		uint32_t wrdq30deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq30deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq31_deskewc_code0 {
	struct {
		uint32_t wrdq31deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq31deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_ecc0_deskewc_code0 {
	struct {
		uint32_t wrecc0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_ecc1_deskewc_code0 {
	struct {
		uint32_t wrecc1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_sev0_deskewc_code0 {
	struct {
		uint32_t wrsev0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_sev1_deskewc_code0 {
	struct {
		uint32_t wrsev1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi0_deskewc_code0 {
	struct {
		uint32_t wrdbi0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi1_deskewc_code0 {
	struct {
		uint32_t wrdbi1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi2_deskewc_code0 {
	struct {
		uint32_t wrdbi2deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi2deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi3_deskewc_code0 {
	struct {
		uint32_t wrdbi3deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi3deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_par_deskewc_code0 {
	struct {
		uint32_t wrpardeskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrpardeskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq0_deskewc_code0 {
	struct {
		uint32_t sw_wrdq0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq1_deskewc_code0 {
	struct {
		uint32_t sw_wrdq1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq2_deskewc_code0 {
	struct {
		uint32_t sw_wrdq2deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq2deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq3_deskewc_code0 {
	struct {
		uint32_t sw_wrdq3deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq3deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq4_deskewc_code0 {
	struct {
		uint32_t sw_wrdq4deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq4deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq5_deskewc_code0 {
	struct {
		uint32_t sw_wrdq5deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq5deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq6_deskewc_code0 {
	struct {
		uint32_t sw_wrdq6deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq6deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq7_deskewc_code0 {
	struct {
		uint32_t sw_wrdq7deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq7deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq8_deskewc_code0 {
	struct {
		uint32_t sw_wrdq8deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq8deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq9_deskewc_code0 {
	struct {
		uint32_t sw_wrdq9deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq9deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq10_deskewc_code0 {
	struct {
		uint32_t sw_wrdq10deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq10deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq11_deskewc_code0 {
	struct {
		uint32_t sw_wrdq11deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq11deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq12_deskewc_code0 {
	struct {
		uint32_t sw_wrdq12deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq12deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq13_deskewc_code0 {
	struct {
		uint32_t sw_wrdq13deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq13deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq14_deskewc_code0 {
	struct {
		uint32_t sw_wrdq14deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq14deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq15_deskewc_code0 {
	struct {
		uint32_t sw_wrdq15deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq15deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq16_deskewc_code0 {
	struct {
		uint32_t sw_wrdq16deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq16deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq17_deskewc_code0 {
	struct {
		uint32_t sw_wrdq17deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq17deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq18_deskewc_code0 {
	struct {
		uint32_t sw_wrdq18deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq18deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq19_deskewc_code0 {
	struct {
		uint32_t sw_wrdq19deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq19deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq20_deskewc_code0 {
	struct {
		uint32_t sw_wrdq20deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq20deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq21_deskewc_code0 {
	struct {
		uint32_t sw_wrdq21deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq21deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq22_deskewc_code0 {
	struct {
		uint32_t sw_wrdq22deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq22deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq23_deskewc_code0 {
	struct {
		uint32_t sw_wrdq23deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq23deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq24_deskewc_code0 {
	struct {
		uint32_t sw_wrdq24deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq24deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq25_deskewc_code0 {
	struct {
		uint32_t sw_wrdq25deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq25deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq26_deskewc_code0 {
	struct {
		uint32_t sw_wrdq26deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq26deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq27_deskewc_code0 {
	struct {
		uint32_t sw_wrdq27deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq27deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq28_deskewc_code0 {
	struct {
		uint32_t sw_wrdq28deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq28deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq29_deskewc_code0 {
	struct {
		uint32_t sw_wrdq29deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq29deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq30_deskewc_code0 {
	struct {
		uint32_t sw_wrdq30deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq30deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq31_deskewc_code0 {
	struct {
		uint32_t sw_wrdq31deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq31deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_ecc0_deskewc_code0 {
	struct {
		uint32_t sw_wrecc0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrecc0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_ecc1_deskewc_code0 {
	struct {
		uint32_t sw_wrecc1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrecc1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_sev0_deskewc_code0 {
	struct {
		uint32_t sw_wrsev0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrsev0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_sev1_deskewc_code0 {
	struct {
		uint32_t sw_wrsev1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrsev1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi0_deskewc_code0 {
	struct {
		uint32_t sw_wrdbi0deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi0deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi1_deskewc_code0 {
	struct {
		uint32_t sw_wrdbi1deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi1deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi2_deskewc_code0 {
	struct {
		uint32_t sw_wrdbi2deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi2deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi3_deskewc_code0 {
	struct {
		uint32_t sw_wrdbi3deskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi3deskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_par_deskewc_code0 {
	struct {
		uint32_t sw_wrpardeskewc0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrpardeskewc1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_dword_select {
	struct {
		uint32_t bsel:2; /* [1:0] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_version_info_stat0 {
	struct {
		uint32_t version_info; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_auto_dqs_stat0 {
	struct {
		uint32_t fifo_rd_fail:2; /* [1:0] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_cacal_con {
	struct {
		uint32_t cbt_sw_mode:1; /* [0:0] */
		uint32_t ca_cal_start:1; /* [1:1] */
		uint32_t ca_cal_ck_sel:2; /* [3:2] */
		uint32_t reserved0:28; /* [31:4] */
	};
	uint32_t val;
};

union hbm3ephy_freq_offset_con {
	struct {
		uint32_t freq_offset:23; /* [22:0] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_con0 {
	struct {
		uint32_t prbs_done:1; /* [0:0] */
		uint32_t reserved1:2; /* [2:1] */
		uint32_t prbs_write_cyc_en:1; /* [3:3] */
		uint32_t prbs_write_done:1; /* [4:4] */
		uint32_t prbs_read_done:1; /* [5:5] */
		uint32_t prbs_pattern:16; /* [21:6] */
		uint32_t evt1_prbs_noise_gen:1; /* [22:22] */
		uint32_t evt1_prbs_noise_gen_done:1; /* [23:23] */
		uint32_t evt1_prbs_noise_gen_resp:1; /* [24:24] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_con1 {
	struct {
		uint32_t prbs_start_offset:9; /* [8:0] */
		uint32_t prbs_fail:9; /* [17:9] */
		uint32_t prbs_par_en:1; /* [18:18] */
		uint32_t prbs_dbi_en:1; /* [19:19] */
		uint32_t prbs_ecc_en:1; /* [20:20] */
		uint32_t prbs_per_bit_mode:1; /* [21:21] */
		uint32_t evt1_seamless_prbs_cnt:9; /* [30:22] */
		uint32_t evt1_seamless_prbs_en:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_margin0 {
	struct {
		uint32_t reserved3:10; /* [9:0] */
		uint32_t reserved2:6; /* [15:10] */
		uint32_t reserved1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_fail_read_d0 {
	struct {
		uint32_t prbs_fail_read_dq_ds0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_fail_read_d1 {
	struct {
		uint32_t prbs_fail_read_dq_ds1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_fail_etc {
	struct {
		uint32_t prbs_fail_read_dbi_ds0:4; /* [3:0] */
		uint32_t prbs_fail_read_dbi_ds1:4; /* [7:4] */
		uint32_t prbs_fail_read_par_ds0:1; /* [8:8] */
		uint32_t prbs_fail_read_par_ds1:1; /* [9:9] */
		uint32_t prbs_fail_read_ecc_ds0:2; /* [11:10] */
		uint32_t prbs_fail_read_ecc_ds1:2; /* [13:12] */
		uint32_t prbs_fail_write_dbi_ds0:4; /* [17:14] */
		uint32_t prbs_fail_write_dbi_ds1:4; /* [21:18] */
		uint32_t prbs_fail_write_par_ds0:1; /* [22:22] */
		uint32_t prbs_fail_write_par_ds1:1; /* [23:23] */
		uint32_t prbs_fail_write_ecc_ds0:2; /* [25:24] */
		uint32_t prbs_fail_write_ecc_ds1:2; /* [27:26] */
		uint32_t reserved0:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_mon_con0 {
	struct {
		uint32_t dfi_disconnect:1; /* [0:0] */
		uint32_t ignore_phy_cg_en:1; /* [1:1] */
		uint32_t rddata_en_phase_err:2; /* [3:2] */
		uint32_t dfi_dram_clk_disable_status:1; /* [4:4] */
		uint32_t ignore_clkgate_dfi_ctrl:1; /* [5:5] */
		uint32_t ignore_clkgate_prbs:1; /* [6:6] */
		uint32_t ignore_clkgate_vtc:1; /* [7:7] */
		uint32_t wrdata_dur:4; /* [11:8] */
		uint32_t write_dur_err:2; /* [13:12] */
		uint32_t mdll_monitor_en:1; /* [14:14] */
		uint32_t read_dur_err:2; /* [16:15] */
		uint32_t ctrl_phy_cg_en_status:1; /* [17:17] */
		uint32_t write_drive_en:1; /* [18:18] */
		uint32_t cs_phyupd:2; /* [20:19] */
		uint32_t cs_phydfs:3; /* [23:21] */
		uint32_t dfi_init_complete_status:1; /* [24:24] */
		uint32_t dfi_init_start_status:1; /* [25:25] */
		uint32_t debug_mode_en:1; /* [26:26] */
		uint32_t rddata_dur:4; /* [30:27] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_fail_write_d0 {
	struct {
		uint32_t prbs_fail_write_dq_ds0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_fail_write_d1 {
	struct {
		uint32_t prbs_fail_write_dq_ds1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_debug0 {
	struct {
		uint32_t trden2resp:6; /* [5:0] */
		uint32_t tcal_prea:11; /* [16:6] */
		uint32_t tcal_en:6; /* [22:17] */
		uint32_t err_mask_disable:1; /* [23:23] */
		uint32_t rnop_mrs_disable:1; /* [24:24] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_trn_mon0 {
	struct {
		uint32_t rdtrn_fsm_dword0:2; /* [1:0] */
		uint32_t rdtrn_fsm_dword1:2; /* [3:2] */
		uint32_t rdtrn_par_fsm_dword0:2; /* [5:4] */
		uint32_t rdtrn_par_fsm_dword1:2; /* [7:6] */
		uint32_t wrtrn_fsm_dword0:4; /* [11:8] */
		uint32_t wrtrn_fsm_dword1:4; /* [15:12] */
		uint32_t prbs_fsm_dword0:3; /* [18:16] */
		uint32_t prbs_fsm_dword1:3; /* [21:19] */
		uint32_t sw_trn_fsm_status:5; /* [26:22] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_lock_mon0 {
	struct {
		uint32_t relock_value:10; /* [9:0] */
		uint32_t harmonic_err:1; /* [10:10] */
		uint32_t locked_release:1; /* [11:11] */
		uint32_t reserved0:20; /* [31:12] */
	};
	uint32_t val;
};

union hbm3ephy_lock_mon1 {
	struct {
		uint32_t lock_value_min:10; /* [9:0] */
		uint32_t lock_value_max:10; /* [19:10] */
		uint32_t reserved0:12; /* [31:20] */
	};
	uint32_t val;
};

union hbm3ephy_fifo_stat0 {
	struct {
		uint32_t reserved2:8; /* [7:0] */
		uint32_t read_command_counter:8; /* [15:8] */
		uint32_t rptr:4; /* [19:16] */
		uint32_t reserved1:4; /* [23:20] */
		uint32_t wptr:4; /* [27:24] */
		uint32_t fifo_err:1; /* [28:28] */
		uint32_t reserved0:3; /* [31:29] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con0 {
	struct {
		uint32_t wrtrn_rddata_adj0_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con1 {
	struct {
		uint32_t wrtrn_rddata_adj0_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con2 {
	struct {
		uint32_t wrtrn_rddata_adj1_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con3 {
	struct {
		uint32_t wrtrn_rddata_adj1_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con4 {
	struct {
		uint32_t wrtrn_rddata_adj2_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con5 {
	struct {
		uint32_t wrtrn_rddata_adj2_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con6 {
	struct {
		uint32_t wrtrn_rddata_adj3_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con7 {
	struct {
		uint32_t wrtrn_rddata_adj3_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con8 {
	struct {
		uint32_t wrtrn_rddata_adj4_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con9 {
	struct {
		uint32_t wrtrn_rddata_adj4_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con10 {
	struct {
		uint32_t wrtrn_rddata_adj5_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con11 {
	struct {
		uint32_t wrtrn_rddata_adj5_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con12 {
	struct {
		uint32_t wrtrn_rddata_adj6_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con13 {
	struct {
		uint32_t wrtrn_rddata_adj6_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con14 {
	struct {
		uint32_t wrtrn_rddata_adj7_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con15 {
	struct {
		uint32_t wrtrn_rddata_adj7_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con16 {
	struct {
		uint32_t wrtrn_rddata_ecc_adj0_apb:4; /* [3:0] */
		uint32_t wrtrn_rddata_ecc_adj1_apb:4; /* [7:4] */
		uint32_t wrtrn_rddata_ecc_adj2_apb:4; /* [11:8] */
		uint32_t wrtrn_rddata_ecc_adj3_apb:4; /* [15:12] */
		uint32_t wrtrn_rddata_ecc_adj4_apb:4; /* [19:16] */
		uint32_t wrtrn_rddata_ecc_adj5_apb:4; /* [23:20] */
		uint32_t wrtrn_rddata_ecc_adj6_apb:4; /* [27:24] */
		uint32_t wrtrn_rddata_ecc_adj7_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con17 {
	struct {
		uint32_t wrtrn_rddata_sev_adj0_apb:4; /* [3:0] */
		uint32_t wrtrn_rddata_sev_adj1_apb:4; /* [7:4] */
		uint32_t wrtrn_rddata_sev_adj2_apb:4; /* [11:8] */
		uint32_t wrtrn_rddata_sev_adj3_apb:4; /* [15:12] */
		uint32_t wrtrn_rddata_sev_adj4_apb:4; /* [19:16] */
		uint32_t wrtrn_rddata_sev_adj5_apb:4; /* [23:20] */
		uint32_t wrtrn_rddata_sev_adj6_apb:4; /* [27:24] */
		uint32_t wrtrn_rddata_sev_adj7_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con18 {
	struct {
		uint32_t wrtrn_rddata_dbi_adj0_apb:8; /* [7:0] */
		uint32_t wrtrn_rddata_dbi_adj1_apb:8; /* [15:8] */
		uint32_t wrtrn_rddata_dbi_adj2_apb:8; /* [23:16] */
		uint32_t wrtrn_rddata_dbi_adj3_apb:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con19 {
	struct {
		uint32_t wrtrn_rddata_dbi_adj4_apb:8; /* [7:0] */
		uint32_t wrtrn_rddata_dbi_adj5_apb:8; /* [15:8] */
		uint32_t wrtrn_rddata_dbi_adj6_apb:8; /* [23:16] */
		uint32_t wrtrn_rddata_dbi_adj7_apb:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_cal_wr_pattern_con20 {
	struct {
		uint32_t wrtrn_rddata_par_adj0_apb:2; /* [1:0] */
		uint32_t wrtrn_rddata_par_adj1_apb:2; /* [3:2] */
		uint32_t wrtrn_rddata_par_adj2_apb:2; /* [5:4] */
		uint32_t wrtrn_rddata_par_adj3_apb:2; /* [7:6] */
		uint32_t wrtrn_rddata_par_adj4_apb:2; /* [9:8] */
		uint32_t wrtrn_rddata_par_adj5_apb:2; /* [11:10] */
		uint32_t wrtrn_rddata_par_adj6_apb:2; /* [13:12] */
		uint32_t wrtrn_rddata_par_adj7_apb:2; /* [15:14] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_mode {
	struct {
		uint32_t scheduler_sw_mode:1; /* [0:0] */
		uint32_t scheduler_cg_en_disable:1; /* [1:1] */
		uint32_t periodic_fail_status_clear:1; /* [2:2] */
		uint32_t dvfs_fail_status_clear:1; /* [3:3] */
		uint32_t timeout_fail_status_clear:1; /* [4:4] */
		uint32_t sw_cmd_start:1; /* [5:5] */
		uint32_t schd_fsm_clear:1; /* [6:6] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_direct_cmd_con_0 {
	struct {
		uint32_t cmd_cnop_req:1; /* [0:0] */
		uint32_t cmd_rnop_req:1; /* [1:1] */
		uint32_t cmd_act_req:1; /* [2:2] */
		uint32_t cmd_pre_req:1; /* [3:3] */
		uint32_t cmd_prea_req:1; /* [4:4] */
		uint32_t cmd_refpb_req:1; /* [5:5] */
		uint32_t cmd_refab_req:1; /* [6:6] */
		uint32_t cmd_rfmpb_req:1; /* [7:7] */
		uint32_t cmd_rfmab_req:1; /* [8:8] */
		uint32_t cmd_pde_req:1; /* [9:9] */
		uint32_t cmd_sre_req:1; /* [10:10] */
		uint32_t cmd_pdx_srx_req:1; /* [11:11] */
		uint32_t cmd_read_req:1; /* [12:12] */
		uint32_t cmd_read_wap_req:1; /* [13:13] */
		uint32_t cmd_write_req:1; /* [14:14] */
		uint32_t cmd_write_wap_req:1; /* [15:15] */
		uint32_t cmd_mrs_req:1; /* [16:16] */
		uint32_t cmd_read_seamless_req:1; /* [17:17] */
		uint32_t cmd_write_seamless_req:1; /* [18:18] */
		uint32_t cmd_cacal_req:1; /* [19:19] */
		uint32_t direct_cmd_req:1; /* [20:20] */
		uint32_t direct_cmd_seamless_req:1; /* [21:21] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_direct_cmd_con_1 {
	struct {
		uint32_t direct_cmd_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_direct_cmd_con_2 {
	struct {
		uint32_t direct_cmd_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_direct_cmd_con_3 {
	struct {
		uint32_t direct_cmd_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_direct_cmd_con_4 {
	struct {
		uint32_t direct_cmd_4; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con0 {
	struct {
		uint32_t wl:6; /* [5:0] */
		uint32_t tppd:4; /* [9:6] */
		uint32_t tmod:8; /* [17:10] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con1 {
	struct {
		uint32_t tccd:8; /* [7:0] */
		uint32_t trtp:6; /* [13:8] */
		uint32_t twtr:6; /* [19:14] */
		uint32_t tnop:4; /* [23:20] */
		uint32_t reserved0:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con2 {
	struct {
		uint32_t tmrd:7; /* [6:0] */
		uint32_t tdes:4; /* [10:7] */
		uint32_t txs_extra:10; /* [20:11] */
		uint32_t reserved0:11; /* [31:21] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con3 {
	struct {
		uint32_t evt0_additional_wl:2; /* [1:0] */
		uint32_t evt0_txp:5; /* [6:2] */
		uint32_t evt0_tra_rfc:10; /* [16:7] */
		uint32_t evt0_ma_code_apb:5; /* [21:17] */
		uint32_t evt0_phy_t_rddata_en:8; /* [29:22] */
		uint32_t reserved0:2; /* [31:30] */
	};
	struct {
		uint32_t evt1_additional_wl:2; /* [1:0] */
		uint32_t evt1_txp:6; /* [7:2] */
		uint32_t evt1_tra_rfc:11; /* [18:8] */
		uint32_t evt1_ma_code_apb:5; /* [23:19] */
		uint32_t evt1_phy_t_rddata_en:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con4 {
	struct {
		uint32_t ba_code_apb:4; /* [3:0] */
		uint32_t ra_code_apb:15; /* [18:4] */
		uint32_t ca_code_apb:5; /* [23:19] */
		uint32_t reserved1:1; /* [24:24] */
		uint32_t ch_apb:1; /* [25:25] */
		uint32_t sid0_apb:1; /* [26:26] */
		uint32_t sid1_apb:1; /* [27:27] */
		uint32_t reserved0:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_con5 {
	struct {
		uint32_t tra_act_apb:8; /* [7:0] */
		uint32_t tra_sre_apb:8; /* [15:8] */
		uint32_t tca_write_bl16_apb:8; /* [23:16] */
		uint32_t op_code_apb:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_scheduler_state {
	struct {
		uint32_t schd_train_fsm:4; /* [3:0] */
		uint32_t schd_fifo_empty_status:1; /* [4:4] */
		uint32_t schd_periodic_trn_fsm:5; /* [9:5] */
		uint32_t schd_periodic_fsm:4; /* [13:10] */
		uint32_t periodic_fail_status:1; /* [14:14] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_io_duty_ctrl {
	struct {
		uint32_t duty_aword_io_cntp:2; /* [1:0] */
		uint32_t duty_aword_io_cntn:2; /* [3:2] */
		uint32_t duty_aword_io_en:1; /* [4:4] */
		uint32_t duty_dword_io_cntp:4; /* [8:5] */
		uint32_t duty_dword_io_cntn:4; /* [12:9] */
		uint32_t duty_dword_io_en:2; /* [14:13] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_dtb {
	struct {
		uint32_t dtb_select:4; /* [3:0] */
		uint32_t reserved0:28; /* [31:4] */
	};
	uint32_t val;
};

union hbm3ephy_cg_off {
	struct {
		uint32_t rd_train_cg_off:1; /* [0:0] */
		uint32_t wr_train_cg_off:1; /* [1:1] */
		uint32_t wrlvl_cg_off:1; /* [2:2] */
		uint32_t cbt_cg_off:1; /* [3:3] */
		uint32_t reserved0:28; /* [31:4] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq0_stat {
	struct {
		uint32_t dq0_vwmc:10; /* [9:0] */
		uint32_t dq0_vwml:10; /* [19:10] */
		uint32_t dq0_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq1_stat {
	struct {
		uint32_t dq1_vwmc:10; /* [9:0] */
		uint32_t dq1_vwml:10; /* [19:10] */
		uint32_t dq1_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq2_stat {
	struct {
		uint32_t dq2_vwmc:10; /* [9:0] */
		uint32_t dq2_vwml:10; /* [19:10] */
		uint32_t dq2_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq3_stat {
	struct {
		uint32_t dq3_vwmc:10; /* [9:0] */
		uint32_t dq3_vwml:10; /* [19:10] */
		uint32_t dq3_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq4_stat {
	struct {
		uint32_t dq4_vwmc:10; /* [9:0] */
		uint32_t dq4_vwml:10; /* [19:10] */
		uint32_t dq4_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq5_stat {
	struct {
		uint32_t dq5_vwmc:10; /* [9:0] */
		uint32_t dq5_vwml:10; /* [19:10] */
		uint32_t dq5_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq6_stat {
	struct {
		uint32_t dq6_vwmc:10; /* [9:0] */
		uint32_t dq6_vwml:10; /* [19:10] */
		uint32_t dq6_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq7_stat {
	struct {
		uint32_t dq7_vwmc:10; /* [9:0] */
		uint32_t dq7_vwml:10; /* [19:10] */
		uint32_t dq7_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq8_stat {
	struct {
		uint32_t dq8_vwmc:10; /* [9:0] */
		uint32_t dq8_vwml:10; /* [19:10] */
		uint32_t dq8_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq9_stat {
	struct {
		uint32_t dq9_vwmc:10; /* [9:0] */
		uint32_t dq9_vwml:10; /* [19:10] */
		uint32_t dq9_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq10_stat {
	struct {
		uint32_t dq10_vwmc:10; /* [9:0] */
		uint32_t dq10_vwml:10; /* [19:10] */
		uint32_t dq10_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq11_stat {
	struct {
		uint32_t dq11_vwmc:10; /* [9:0] */
		uint32_t dq11_vwml:10; /* [19:10] */
		uint32_t dq11_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq12_stat {
	struct {
		uint32_t dq12_vwmc:10; /* [9:0] */
		uint32_t dq12_vwml:10; /* [19:10] */
		uint32_t dq12_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq13_stat {
	struct {
		uint32_t dq13_vwmc:10; /* [9:0] */
		uint32_t dq13_vwml:10; /* [19:10] */
		uint32_t dq13_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq14_stat {
	struct {
		uint32_t dq14_vwmc:10; /* [9:0] */
		uint32_t dq14_vwml:10; /* [19:10] */
		uint32_t dq14_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq15_stat {
	struct {
		uint32_t dq15_vwmc:10; /* [9:0] */
		uint32_t dq15_vwml:10; /* [19:10] */
		uint32_t dq15_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq16_stat {
	struct {
		uint32_t dq16_vwmc:10; /* [9:0] */
		uint32_t dq16_vwml:10; /* [19:10] */
		uint32_t dq16_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq17_stat {
	struct {
		uint32_t dq17_vwmc:10; /* [9:0] */
		uint32_t dq17_vwml:10; /* [19:10] */
		uint32_t dq17_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq18_stat {
	struct {
		uint32_t dq18_vwmc:10; /* [9:0] */
		uint32_t dq18_vwml:10; /* [19:10] */
		uint32_t dq18_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq19_stat {
	struct {
		uint32_t dq19_vwmc:10; /* [9:0] */
		uint32_t dq19_vwml:10; /* [19:10] */
		uint32_t dq19_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq20_stat {
	struct {
		uint32_t dq20_vwmc:10; /* [9:0] */
		uint32_t dq20_vwml:10; /* [19:10] */
		uint32_t dq20_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq21_stat {
	struct {
		uint32_t dq21_vwmc:10; /* [9:0] */
		uint32_t dq21_vwml:10; /* [19:10] */
		uint32_t dq21_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq22_stat {
	struct {
		uint32_t dq22_vwmc:10; /* [9:0] */
		uint32_t dq22_vwml:10; /* [19:10] */
		uint32_t dq22_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq23_stat {
	struct {
		uint32_t dq23_vwmc:10; /* [9:0] */
		uint32_t dq23_vwml:10; /* [19:10] */
		uint32_t dq23_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq24_stat {
	struct {
		uint32_t dq24_vwmc:10; /* [9:0] */
		uint32_t dq24_vwml:10; /* [19:10] */
		uint32_t dq24_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq25_stat {
	struct {
		uint32_t dq25_vwmc:10; /* [9:0] */
		uint32_t dq25_vwml:10; /* [19:10] */
		uint32_t dq25_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq26_stat {
	struct {
		uint32_t dq26_vwmc:10; /* [9:0] */
		uint32_t dq26_vwml:10; /* [19:10] */
		uint32_t dq26_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq27_stat {
	struct {
		uint32_t dq27_vwmc:10; /* [9:0] */
		uint32_t dq27_vwml:10; /* [19:10] */
		uint32_t dq27_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq28_stat {
	struct {
		uint32_t dq28_vwmc:10; /* [9:0] */
		uint32_t dq28_vwml:10; /* [19:10] */
		uint32_t dq28_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq29_stat {
	struct {
		uint32_t dq29_vwmc:10; /* [9:0] */
		uint32_t dq29_vwml:10; /* [19:10] */
		uint32_t dq29_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq30_stat {
	struct {
		uint32_t dq30_vwmc:10; /* [9:0] */
		uint32_t dq30_vwml:10; /* [19:10] */
		uint32_t dq30_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dq31_stat {
	struct {
		uint32_t dq31_vwmc:10; /* [9:0] */
		uint32_t dq31_vwml:10; /* [19:10] */
		uint32_t dq31_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_ecc0_stat {
	struct {
		uint32_t ecc0_vwmc:10; /* [9:0] */
		uint32_t ecc0_vwml:10; /* [19:10] */
		uint32_t ecc0_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_ecc1_stat {
	struct {
		uint32_t ecc1_vwmc:10; /* [9:0] */
		uint32_t ecc1_vwml:10; /* [19:10] */
		uint32_t ecc1_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_sev0_stat {
	struct {
		uint32_t sev0_vwmc:10; /* [9:0] */
		uint32_t sev0_vwml:10; /* [19:10] */
		uint32_t sev0_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_sev1_stat {
	struct {
		uint32_t sev1_vwmc:10; /* [9:0] */
		uint32_t sev1_vwml:10; /* [19:10] */
		uint32_t sev1_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dbi0_stat {
	struct {
		uint32_t dbi0_vwmc:10; /* [9:0] */
		uint32_t dbi0_vwml:10; /* [19:10] */
		uint32_t dbi0_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dbi1_stat {
	struct {
		uint32_t dbi1_vwmc:10; /* [9:0] */
		uint32_t dbi1_vwml:10; /* [19:10] */
		uint32_t dbi1_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dbi2_stat {
	struct {
		uint32_t dbi2_vwmc:10; /* [9:0] */
		uint32_t dbi2_vwml:10; /* [19:10] */
		uint32_t dbi2_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_dbi3_stat {
	struct {
		uint32_t dbi3_vwmc:10; /* [9:0] */
		uint32_t dbi3_vwml:10; /* [19:10] */
		uint32_t dbi3_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_par_stat {
	struct {
		uint32_t par_vwmc:10; /* [9:0] */
		uint32_t par_vwml:10; /* [19:10] */
		uint32_t par_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_rd0_stat {
	struct {
		uint32_t rd0_vwmc:10; /* [9:0] */
		uint32_t rd0_vwml:10; /* [19:10] */
		uint32_t rd0_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_vwm_rd1_stat {
	struct {
		uint32_t rd1_vwmc:10; /* [9:0] */
		uint32_t rd1_vwml:10; /* [19:10] */
		uint32_t rd1_vwmr:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_lvl_cs0_code0 {
	struct {
		uint32_t sw_wrlvl0_code_rank0:9; /* [8:0] */
		uint32_t reserved1:1; /* [9:9] */
		uint32_t sw_wrlvl1_code_rank0:9; /* [18:10] */
		uint32_t reserved0:13; /* [31:19] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata0_0 {
	struct {
		uint32_t dfi_rddata0_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata0_1 {
	struct {
		uint32_t dfi_rddata0_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata0_2 {
	struct {
		uint32_t dfi_rddata0_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata0_3 {
	struct {
		uint32_t dfi_rddata0_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata2_0 {
	struct {
		uint32_t dfi_rddata2_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata2_1 {
	struct {
		uint32_t dfi_rddata2_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata2_2 {
	struct {
		uint32_t dfi_rddata2_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata2_3 {
	struct {
		uint32_t dfi_rddata2_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata4_0 {
	struct {
		uint32_t dfi_rddata4_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata4_1 {
	struct {
		uint32_t dfi_rddata4_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata4_2 {
	struct {
		uint32_t dfi_rddata4_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata4_3 {
	struct {
		uint32_t dfi_rddata4_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata6_0 {
	struct {
		uint32_t dfi_rddata6_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata6_1 {
	struct {
		uint32_t dfi_rddata6_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata6_2 {
	struct {
		uint32_t dfi_rddata6_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata6_3 {
	struct {
		uint32_t dfi_rddata6_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata8_0 {
	struct {
		uint32_t dfi_rddata8_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata8_1 {
	struct {
		uint32_t dfi_rddata8_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata8_2 {
	struct {
		uint32_t dfi_rddata8_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata8_3 {
	struct {
		uint32_t dfi_rddata8_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata10_0 {
	struct {
		uint32_t dfi_rddata10_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata10_1 {
	struct {
		uint32_t dfi_rddata10_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata10_2 {
	struct {
		uint32_t dfi_rddata10_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata10_3 {
	struct {
		uint32_t dfi_rddata10_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata12_0 {
	struct {
		uint32_t dfi_rddata12_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata12_1 {
	struct {
		uint32_t dfi_rddata12_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata12_2 {
	struct {
		uint32_t dfi_rddata12_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata12_3 {
	struct {
		uint32_t dfi_rddata12_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata14_0 {
	struct {
		uint32_t dfi_rddata14_0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata14_1 {
	struct {
		uint32_t dfi_rddata14_1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata14_2 {
	struct {
		uint32_t dfi_rddata14_2; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata14_3 {
	struct {
		uint32_t dfi_rddata14_3; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_ecc_0 {
	struct {
		uint32_t dfi_rddata_ecc0_0:4; /* [3:0] */
		uint32_t dfi_rddata_ecc0_1:4; /* [7:4] */
		uint32_t dfi_rddata_ecc1_0:4; /* [11:8] */
		uint32_t dfi_rddata_ecc1_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_ecc_1 {
	struct {
		uint32_t dfi_rddata_ecc2_0:4; /* [3:0] */
		uint32_t dfi_rddata_ecc2_1:4; /* [7:4] */
		uint32_t dfi_rddata_ecc3_0:4; /* [11:8] */
		uint32_t dfi_rddata_ecc3_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_ecc_2 {
	struct {
		uint32_t dfi_rddata_ecc4_0:4; /* [3:0] */
		uint32_t dfi_rddata_ecc4_1:4; /* [7:4] */
		uint32_t dfi_rddata_ecc5_0:4; /* [11:8] */
		uint32_t dfi_rddata_ecc5_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_ecc_3 {
	struct {
		uint32_t dfi_rddata_ecc6_0:4; /* [3:0] */
		uint32_t dfi_rddata_ecc6_1:4; /* [7:4] */
		uint32_t dfi_rddata_ecc7_0:4; /* [11:8] */
		uint32_t dfi_rddata_ecc7_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_sev_0 {
	struct {
		uint32_t dfi_rddata_sev0_0:4; /* [3:0] */
		uint32_t dfi_rddata_sev0_1:4; /* [7:4] */
		uint32_t dfi_rddata_sev1_0:4; /* [11:8] */
		uint32_t dfi_rddata_sev1_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_sev_1 {
	struct {
		uint32_t dfi_rddata_sev2_0:4; /* [3:0] */
		uint32_t dfi_rddata_sev2_1:4; /* [7:4] */
		uint32_t dfi_rddata_sev3_0:4; /* [11:8] */
		uint32_t dfi_rddata_sev3_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_sev_2 {
	struct {
		uint32_t dfi_rddata_sev4_0:4; /* [3:0] */
		uint32_t dfi_rddata_sev4_1:4; /* [7:4] */
		uint32_t dfi_rddata_sev5_0:4; /* [11:8] */
		uint32_t dfi_rddata_sev5_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_sev_3 {
	struct {
		uint32_t dfi_rddata_sev6_0:4; /* [3:0] */
		uint32_t dfi_rddata_sev6_1:4; /* [7:4] */
		uint32_t dfi_rddata_sev7_0:4; /* [11:8] */
		uint32_t dfi_rddata_sev7_1:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_0 {
	struct {
		uint32_t dfi_rddata_dbi0_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi0_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_1 {
	struct {
		uint32_t dfi_rddata_dbi1_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi1_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_2 {
	struct {
		uint32_t dfi_rddata_dbi2_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi2_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_3 {
	struct {
		uint32_t dfi_rddata_dbi3_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi3_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_4 {
	struct {
		uint32_t dfi_rddata_dbi4_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi4_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_5 {
	struct {
		uint32_t dfi_rddata_dbi5_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi5_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_6 {
	struct {
		uint32_t dfi_rddata_dbi6_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi6_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_dbi_7 {
	struct {
		uint32_t dfi_rddata_dbi7_0:8; /* [7:0] */
		uint32_t dfi_rddata_dbi7_1:8; /* [15:8] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_dfi_rddata_par_0 {
	struct {
		uint32_t dfi_rddata_par0_0:2; /* [1:0] */
		uint32_t dfi_rddata_par0_1:2; /* [3:2] */
		uint32_t dfi_rddata_par1_0:2; /* [5:4] */
		uint32_t dfi_rddata_par1_1:2; /* [7:6] */
		uint32_t dfi_rddata_par2_0:2; /* [9:8] */
		uint32_t dfi_rddata_par2_1:2; /* [11:10] */
		uint32_t dfi_rddata_par3_0:2; /* [13:12] */
		uint32_t dfi_rddata_par3_1:2; /* [15:14] */
		uint32_t dfi_rddata_par4_0:2; /* [17:16] */
		uint32_t dfi_rddata_par4_1:2; /* [19:18] */
		uint32_t dfi_rddata_par5_0:2; /* [21:20] */
		uint32_t dfi_rddata_par5_1:2; /* [23:22] */
		uint32_t dfi_rddata_par6_0:2; /* [25:24] */
		uint32_t dfi_rddata_par6_1:2; /* [27:26] */
		uint32_t dfi_rddata_par7_0:2; /* [29:28] */
		uint32_t dfi_rddata_par7_1:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat0 {
	struct {
		uint32_t test_oky_dq_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat1 {
	struct {
		uint32_t test_oky_dq_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat2 {
	struct {
		uint32_t test_err_dq_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat3 {
	struct {
		uint32_t test_err_dq_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat4 {
	struct {
		uint32_t test_err_sev_dword0:2; /* [1:0] */
		uint32_t test_oky_sev_dword0:2; /* [3:2] */
		uint32_t test_err_sev_dword1:2; /* [5:4] */
		uint32_t test_oky_sev_dword1:2; /* [7:6] */
		uint32_t test_err_ecc_dword0:2; /* [9:8] */
		uint32_t test_oky_ecc_dword0:2; /* [11:10] */
		uint32_t test_err_ecc_dword1:2; /* [13:12] */
		uint32_t test_oky_ecc_dword1:2; /* [15:14] */
		uint32_t test_err_dbi_dword0:4; /* [19:16] */
		uint32_t test_oky_dbi_dword0:4; /* [23:20] */
		uint32_t test_err_dbi_dword1:4; /* [27:24] */
		uint32_t test_oky_dbi_dword1:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_dword_stat5 {
	struct {
		uint32_t test_err_dpar_dword0:1; /* [0:0] */
		uint32_t test_oky_dpar_dword0:1; /* [1:1] */
		uint32_t test_err_dpar_dword1:1; /* [2:2] */
		uint32_t test_oky_dpar_dword1:1; /* [3:3] */
		uint32_t test_err_rd_dword0:2; /* [5:4] */
		uint32_t test_oky_rd_dword0:2; /* [7:6] */
		uint32_t test_err_rd_dword1:2; /* [9:8] */
		uint32_t test_oky_rd_dword1:2; /* [11:10] */
		uint32_t reserved0:20; /* [31:12] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con0 {
	struct {
		uint32_t rdtrn_rddata_adj0_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con1 {
	struct {
		uint32_t rdtrn_rddata_adj0_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con2 {
	struct {
		uint32_t rdtrn_rddata_adj1_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con3 {
	struct {
		uint32_t rdtrn_rddata_adj1_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con4 {
	struct {
		uint32_t rdtrn_rddata_adj2_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con5 {
	struct {
		uint32_t rdtrn_rddata_adj2_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con6 {
	struct {
		uint32_t rdtrn_rddata_adj3_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con7 {
	struct {
		uint32_t rdtrn_rddata_adj3_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con8 {
	struct {
		uint32_t rdtrn_rddata_adj4_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con9 {
	struct {
		uint32_t rdtrn_rddata_adj4_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con10 {
	struct {
		uint32_t rdtrn_rddata_adj5_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con11 {
	struct {
		uint32_t rdtrn_rddata_adj5_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con12 {
	struct {
		uint32_t rdtrn_rddata_adj6_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con13 {
	struct {
		uint32_t rdtrn_rddata_adj6_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con14 {
	struct {
		uint32_t rdtrn_rddata_adj7_0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con15 {
	struct {
		uint32_t rdtrn_rddata_adj7_1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con16 {
	struct {
		uint32_t rdtrn_rddata_ecc_adj0_apb:4; /* [3:0] */
		uint32_t rdtrn_rddata_ecc_adj1_apb:4; /* [7:4] */
		uint32_t rdtrn_rddata_ecc_adj2_apb:4; /* [11:8] */
		uint32_t rdtrn_rddata_ecc_adj3_apb:4; /* [15:12] */
		uint32_t rdtrn_rddata_ecc_adj4_apb:4; /* [19:16] */
		uint32_t rdtrn_rddata_ecc_adj5_apb:4; /* [23:20] */
		uint32_t rdtrn_rddata_ecc_adj6_apb:4; /* [27:24] */
		uint32_t rdtrn_rddata_ecc_adj7_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con17 {
	struct {
		uint32_t rdtrn_rddata_sev_adj0_apb:4; /* [3:0] */
		uint32_t rdtrn_rddata_sev_adj1_apb:4; /* [7:4] */
		uint32_t rdtrn_rddata_sev_adj2_apb:4; /* [11:8] */
		uint32_t rdtrn_rddata_sev_adj3_apb:4; /* [15:12] */
		uint32_t rdtrn_rddata_sev_adj4_apb:4; /* [19:16] */
		uint32_t rdtrn_rddata_sev_adj5_apb:4; /* [23:20] */
		uint32_t rdtrn_rddata_sev_adj6_apb:4; /* [27:24] */
		uint32_t rdtrn_rddata_sev_adj7_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con18 {
	struct {
		uint32_t rdtrn_rddata_dbi_adj0_apb:8; /* [7:0] */
		uint32_t rdtrn_rddata_dbi_adj1_apb:8; /* [15:8] */
		uint32_t rdtrn_rddata_dbi_adj2_apb:8; /* [23:16] */
		uint32_t rdtrn_rddata_dbi_adj3_apb:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con19 {
	struct {
		uint32_t rdtrn_rddata_dbi_adj4_apb:8; /* [7:0] */
		uint32_t rdtrn_rddata_dbi_adj5_apb:8; /* [15:8] */
		uint32_t rdtrn_rddata_dbi_adj6_apb:8; /* [23:16] */
		uint32_t rdtrn_rddata_dbi_adj7_apb:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con20 {
	struct {
		uint32_t rdtrn_rddata_par_adj0_apb:2; /* [1:0] */
		uint32_t rdtrn_rddata_par_adj1_apb:2; /* [3:2] */
		uint32_t rdtrn_rddata_par_adj2_apb:2; /* [5:4] */
		uint32_t rdtrn_rddata_par_adj3_apb:2; /* [7:6] */
		uint32_t rdtrn_rddata_par_adj4_apb:2; /* [9:8] */
		uint32_t rdtrn_rddata_par_adj5_apb:2; /* [11:10] */
		uint32_t rdtrn_rddata_par_adj6_apb:2; /* [13:12] */
		uint32_t rdtrn_rddata_par_adj7_apb:2; /* [15:14] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_cal_rd_pattern_con21 {
	struct {
		uint32_t rdtrn_rddata_rd_adj0_apb:4; /* [3:0] */
		uint32_t rdtrn_rddata_rd_adj1_apb:4; /* [7:4] */
		uint32_t rdtrn_rddata_rd_adj2_apb:4; /* [11:8] */
		uint32_t rdtrn_rddata_rd_adj3_apb:4; /* [15:12] */
		uint32_t rdtrn_rddata_rd_adj4_apb:4; /* [19:16] */
		uint32_t rdtrn_rddata_rd_adj5_apb:4; /* [23:20] */
		uint32_t rdtrn_rddata_rd_adj6_apb:4; /* [27:24] */
		uint32_t rdtrn_rddata_rd_adj7_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_fail_stat0 {
	struct {
		uint32_t read_dq_fail_status0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_fail_stat1 {
	struct {
		uint32_t read_dq_fail_status1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_fail_stat2 {
	struct {
		uint32_t read_sev_fail_status0:2; /* [1:0] */
		uint32_t read_sev_fail_status1:2; /* [3:2] */
		uint32_t read_ecc_fail_status0:2; /* [5:4] */
		uint32_t read_ecc_fail_status1:2; /* [7:6] */
		uint32_t read_dbi_fail_status0:4; /* [11:8] */
		uint32_t read_dbi_fail_status1:4; /* [15:12] */
		uint32_t read_par_fail_status0:1; /* [16:16] */
		uint32_t read_par_fail_status1:1; /* [17:17] */
		uint32_t read_rd_fail_status0:2; /* [19:18] */
		uint32_t read_rd_fail_status1:2; /* [21:20] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl0_dword0 {
	struct {
		uint32_t rddq0offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq1offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq2offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq3offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl1_dword0 {
	struct {
		uint32_t rddq4offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq5offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq6offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq7offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl2_dword0 {
	struct {
		uint32_t rddq8offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq9offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq10offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq11offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl3_dword0 {
	struct {
		uint32_t rddq12offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq13offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq14offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq15offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl4_dword0 {
	struct {
		uint32_t rddq16offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq17offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq18offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq19offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl5_dword0 {
	struct {
		uint32_t rddq20offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq21offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq22offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq23offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl6_dword0 {
	struct {
		uint32_t rddq24offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq25offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq26offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq27offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl7_dword0 {
	struct {
		uint32_t rddq28offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq29offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq30offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq31offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_ecc_offset_ctrl0_dword0 {
	struct {
		uint32_t rdecc0offset_dword0:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdecc1offset_dword0:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_read_sev_offset_ctrl0_dword0 {
	struct {
		uint32_t rdsev0offset_dword0:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdsev1offset_dword0:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_read_dbi_offset_ctrl0_dword0 {
	struct {
		uint32_t rddbi0offset_dword0:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddbi1offset_dword0:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddbi2offset_dword0:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddbi3offset_dword0:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_par_offset_ctrl0_dword0 {
	struct {
		uint32_t rdpar0offset_dword0:7; /* [6:0] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_read_rd_offset_ctrl0_dword0 {
	struct {
		uint32_t rdrd0offset_dword0:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdrd1offset_dword0:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl0_dword1 {
	struct {
		uint32_t rddq0offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq1offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq2offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq3offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl1_dword1 {
	struct {
		uint32_t rddq4offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq5offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq6offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq7offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl2_dword1 {
	struct {
		uint32_t rddq8offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq9offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq10offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq11offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl3_dword1 {
	struct {
		uint32_t rddq12offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq13offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq14offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq15offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl4_dword1 {
	struct {
		uint32_t rddq16offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq17offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq18offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq19offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl5_dword1 {
	struct {
		uint32_t rddq20offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq21offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq22offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq23offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl6_dword1 {
	struct {
		uint32_t rddq24offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq25offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq26offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq27offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_dq_offset_ctrl7_dword1 {
	struct {
		uint32_t rddq28offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddq29offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddq30offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddq31offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_ecc_offset_ctrl0_dword1 {
	struct {
		uint32_t rdecc0offset_dword1:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdecc1offset_dword1:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_read_sev_offset_ctrl0_dword1 {
	struct {
		uint32_t rdsev0offset_dword1:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdsev1offset_dword1:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_read_dbi_offset_ctrl0_dword1 {
	struct {
		uint32_t rddbi0offset_dword1:7; /* [6:0] */
		uint32_t reserved3:1; /* [7:7] */
		uint32_t rddbi1offset_dword1:7; /* [14:8] */
		uint32_t reserved2:1; /* [15:15] */
		uint32_t rddbi2offset_dword1:7; /* [22:16] */
		uint32_t reserved1:1; /* [23:23] */
		uint32_t rddbi3offset_dword1:7; /* [30:24] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_read_par_offset_ctrl0_dword1 {
	struct {
		uint32_t rdpar0offset_dword1:7; /* [6:0] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_read_rd_offset_ctrl0_dword1 {
	struct {
		uint32_t rdrd0offset_dword1:7; /* [6:0] */
		uint32_t reserved1:1; /* [7:7] */
		uint32_t rdrd1offset_dword1:7; /* [14:8] */
		uint32_t reserved0:17; /* [31:15] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_io_con0 {
	struct {
		uint32_t mode_mux_apb:1; /* [0:0] */
		uint32_t ctrl_ieee_sel_apb:1; /* [1:1] */
		uint32_t ieee_ctrl_en_apb:1; /* [2:2] */
		uint32_t ieee_phy_ctrl_apb:1; /* [3:3] */
		uint32_t reserved0:28; /* [31:4] */
	};
	uint32_t val;
};

union hbm3ephy_debug_mon {
	struct {
		uint32_t debug_tphyupd_rst:1; /* [0:0] */
		uint32_t debug_tphyupd_resp_timeout:1; /* [1:1] */
		uint32_t debug_tphyupd_resp_timeout_cnt:10; /* [11:2] */
		uint32_t debug_tphyupd_cancel_cnt:10; /* [21:12] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_schd_cmd_gating0 {
	struct {
		uint32_t gating_cmd_direct_req_apb:1; /* [0:0] */
		uint32_t gating_cmd_mrs_req_apb:1; /* [1:1] */
		uint32_t gating_cmd_write_seamless_req_apb:1; /* [2:2] */
		uint32_t gating_cmd_write_wap_req_apb:1; /* [3:3] */
		uint32_t gating_cmd_write_req_apb:1; /* [4:4] */
		uint32_t gating_cmd_read_seamless_req_apb:1; /* [5:5] */
		uint32_t gating_cmd_read_wap_req_apb:1; /* [6:6] */
		uint32_t gating_cmd_read_req_apb:1; /* [7:7] */
		uint32_t gating_cmd_pdx_srx_req_apb:1; /* [8:8] */
		uint32_t gating_cmd_sre_req_apb:1; /* [9:9] */
		uint32_t gating_cmd_pde_req_apb:1; /* [10:10] */
		uint32_t gating_cmd_refab_req_apb:1; /* [11:11] */
		uint32_t gating_cmd_refpb_req_apb:1; /* [12:12] */
		uint32_t gating_cmd_rfmab_req_apb:1; /* [13:13] */
		uint32_t gating_cmd_rfmpb_req_apb:1; /* [14:14] */
		uint32_t gating_cmd_prea_req_apb:1; /* [15:15] */
		uint32_t gating_cmd_pre_req_apb:1; /* [16:16] */
		uint32_t gating_cmd_act_req_apb:1; /* [17:17] */
		uint32_t gating_cmd_rnop_req_apb:1; /* [18:18] */
		uint32_t gating_cmd_cnop_req_apb:1; /* [19:19] */
		uint32_t reserved0:12; /* [31:20] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift0 {
	struct {
		uint32_t ctrl_shift_dq_0_dword0_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift1 {
	struct {
		uint32_t ctrl_shift_dq_1_dword0_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift2 {
	struct {
		uint32_t ctrl_shift_dq_2_dword0_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift3 {
	struct {
		uint32_t evt0_ctrl_shift_dbi_dowrd0_apb:12; /* [11:0] */
		uint32_t evt0_ctrl_shift_ecc_dowrd0_apb:6; /* [17:12] */
		uint32_t evt0_ctrl_shift_sev_dowrd0_apb:6; /* [23:18] */
		uint32_t evt0_ctrl_shift_par_dowrd0_apb:3; /* [26:24] */
		uint32_t evt0_reserved0:5; /* [31:27] */
	};
	struct {
		uint32_t evt1_ctrl_shift_dq_3_dword0_apb:6; /* [5:0] */
		uint32_t evt1_reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_per_bit_en0 {
	struct {
		uint32_t prbs_per_bit_en_ecc_dw0:2; /* [1:0] */
		uint32_t prbs_per_bit_en_par_dw0:1; /* [2:2] */
		uint32_t prbs_per_bit_en_dbi_dw0:4; /* [6:3] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t prbs_per_bit_en_ecc_dw1:2; /* [17:16] */
		uint32_t prbs_per_bit_en_par_dw1:1; /* [18:18] */
		uint32_t prbs_per_bit_en_dbi_dw1:4; /* [22:19] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_per_bit_en1 {
	struct {
		uint32_t prbs_per_bit_en_dq_dw0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_per_bit_en2 {
	struct {
		uint32_t prbs_per_bit_en_dq_dw1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon0 {
	struct {
		uint32_t ctrl_out_cycle_dq_0:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon1 {
	struct {
		uint32_t ctrl_out_cycle_dq_1:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon2 {
	struct {
		uint32_t ctrl_out_cycle_dq_2:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon3 {
	struct {
		uint32_t ctrl_out_cycle_dq_3:6; /* [5:0] */
		uint32_t reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon4 {
	struct {
		uint32_t ctrl_out_cycle_dq_4:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon5 {
	struct {
		uint32_t ctrl_out_cycle_dq_5:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon6 {
	struct {
		uint32_t ctrl_out_cycle_dq_6:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon7 {
	struct {
		uint32_t ctrl_out_cycle_dq_7:6; /* [5:0] */
		uint32_t reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon8 {
	struct {
		uint32_t ctrl_out_cycle_dbi_0:12; /* [11:0] */
		uint32_t ctrl_out_cycle_ecc_0:6; /* [17:12] */
		uint32_t ctrl_out_cycle_sev_0:6; /* [23:18] */
		uint32_t ctrl_out_cycle_par_0:3; /* [26:24] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_cyc_mon9 {
	struct {
		uint32_t ctrl_out_cycle_dbi_1:12; /* [11:0] */
		uint32_t ctrl_out_cycle_ecc_1:6; /* [17:12] */
		uint32_t ctrl_out_cycle_sev_1:6; /* [23:18] */
		uint32_t ctrl_out_cycle_par_1:3; /* [26:24] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift4 {
	struct {
		uint32_t ctrl_shift_dq_0_dword1_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift5 {
	struct {
		uint32_t ctrl_shift_dq_1_dword1_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift6 {
	struct {
		uint32_t ctrl_shift_dq_2_dword1_apb:30; /* [29:0] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift7 {
	struct {
		uint32_t evt0_ctrl_shift_dbi_dword1_apb:12; /* [11:0] */
		uint32_t evt0_ctrl_shift_ecc_dword1_apb:6; /* [17:12] */
		uint32_t evt0_ctrl_shift_sev_dword1_apb:6; /* [23:18] */
		uint32_t evt0_ctrl_shift_par_dword1_apb:3; /* [26:24] */
		uint32_t evt0_reserved0:5; /* [31:27] */
	};
	struct {
		uint32_t evt1_ctrl_shift_dq_3_dword1_apb:6; /* [5:0] */
		uint32_t evt1_reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl0 {
	struct {
		uint32_t io_rduty_dq0:4; /* [3:0] */
		uint32_t io_rduty_dq1:4; /* [7:4] */
		uint32_t io_rduty_dq2:4; /* [11:8] */
		uint32_t io_rduty_dq3:4; /* [15:12] */
		uint32_t io_rduty_dq4:4; /* [19:16] */
		uint32_t io_rduty_dq5:4; /* [23:20] */
		uint32_t io_rduty_dq6:4; /* [27:24] */
		uint32_t io_rduty_dq7:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl1 {
	struct {
		uint32_t io_rduty_dq8:4; /* [3:0] */
		uint32_t io_rduty_dq9:4; /* [7:4] */
		uint32_t io_rduty_dq10:4; /* [11:8] */
		uint32_t io_rduty_dq11:4; /* [15:12] */
		uint32_t io_rduty_dq12:4; /* [19:16] */
		uint32_t io_rduty_dq13:4; /* [23:20] */
		uint32_t io_rduty_dq14:4; /* [27:24] */
		uint32_t io_rduty_dq15:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl2 {
	struct {
		uint32_t io_rduty_dq16:4; /* [3:0] */
		uint32_t io_rduty_dq17:4; /* [7:4] */
		uint32_t io_rduty_dq18:4; /* [11:8] */
		uint32_t io_rduty_dq19:4; /* [15:12] */
		uint32_t io_rduty_dq20:4; /* [19:16] */
		uint32_t io_rduty_dq21:4; /* [23:20] */
		uint32_t io_rduty_dq22:4; /* [27:24] */
		uint32_t io_rduty_dq23:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl3 {
	struct {
		uint32_t io_rduty_dq24:4; /* [3:0] */
		uint32_t io_rduty_dq25:4; /* [7:4] */
		uint32_t io_rduty_dq26:4; /* [11:8] */
		uint32_t io_rduty_dq27:4; /* [15:12] */
		uint32_t io_rduty_dq28:4; /* [19:16] */
		uint32_t io_rduty_dq29:4; /* [23:20] */
		uint32_t io_rduty_dq30:4; /* [27:24] */
		uint32_t io_rduty_dq31:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl4 {
	struct {
		uint32_t io_rduty_ecc0:4; /* [3:0] */
		uint32_t io_rduty_ecc1:4; /* [7:4] */
		uint32_t io_rduty_sev0:4; /* [11:8] */
		uint32_t io_rduty_sev1:4; /* [15:12] */
		uint32_t io_rduty_dbi0:4; /* [19:16] */
		uint32_t io_rduty_dbi1:4; /* [23:20] */
		uint32_t io_rduty_dbi2:4; /* [27:24] */
		uint32_t io_rduty_dbi3:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_rduty_ctrl5 {
	struct {
		uint32_t io_rduty_rd0:4; /* [3:0] */
		uint32_t io_rduty_rd1:4; /* [7:4] */
		uint32_t io_rduty_par:4; /* [11:8] */
		uint32_t io_rduty_rdqs:4; /* [15:12] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift8 {
	struct {
		uint32_t ctrl_shift_dbi_dword0_apb:12; /* [11:0] */
		uint32_t ctrl_shift_ecc_dword0_apb:6; /* [17:12] */
		uint32_t ctrl_shift_sev_dword0_apb:6; /* [23:18] */
		uint32_t ctrl_shift_par_dword0_apb:3; /* [26:24] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_ctrl_shift9 {
	struct {
		uint32_t ctrl_shift_dbi_dword1_apb:12; /* [11:0] */
		uint32_t ctrl_shift_ecc_dword1_apb:6; /* [17:12] */
		uint32_t ctrl_shift_sev_dword1_apb:6; /* [23:18] */
		uint32_t ctrl_shift_par_dword1_apb:3; /* [26:24] */
		uint32_t reserved0:5; /* [31:27] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl_en {
	struct {
		uint32_t duty_ctrl_start_en:1; /* [0:0] */
		uint32_t duty_ctrl_dword_sel:2; /* [2:1] */
		uint32_t reserved0:28; /* [30:3] */
		uint32_t duty_ctrl_set_state_busy:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl0 {
	struct {
		uint32_t io_offset_cal_dq0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl1 {
	struct {
		uint32_t io_offset_cal_dq2:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq3:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl2 {
	struct {
		uint32_t io_offset_cal_dq4:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq5:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl3 {
	struct {
		uint32_t io_offset_cal_dq6:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq7:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl4 {
	struct {
		uint32_t io_offset_cal_dq8:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq9:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl5 {
	struct {
		uint32_t io_offset_cal_dq10:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq11:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl6 {
	struct {
		uint32_t io_offset_cal_dq12:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq13:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl7 {
	struct {
		uint32_t io_offset_cal_dq14:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq15:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl8 {
	struct {
		uint32_t io_offset_cal_dq16:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq17:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl9 {
	struct {
		uint32_t io_offset_cal_dq18:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq19:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl10 {
	struct {
		uint32_t io_offset_cal_dq20:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq21:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl11 {
	struct {
		uint32_t io_offset_cal_dq22:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq23:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl12 {
	struct {
		uint32_t io_offset_cal_dq24:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq25:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl13 {
	struct {
		uint32_t io_offset_cal_dq26:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq27:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl14 {
	struct {
		uint32_t io_offset_cal_dq28:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq29:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl15 {
	struct {
		uint32_t io_offset_cal_dq30:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dq31:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl16 {
	struct {
		uint32_t io_offset_cal_ecc0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_ecc1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl17 {
	struct {
		uint32_t io_offset_cal_sev0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_sev1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl18 {
	struct {
		uint32_t io_offset_cal_dbi0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dbi1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl19 {
	struct {
		uint32_t io_offset_cal_dbi2:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_dbi3:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl20 {
	struct {
		uint32_t io_offset_cal_rd0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t io_offset_cal_rd1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl21 {
	struct {
		uint32_t io_offset_cal_par:7; /* [6:0] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_duty_ctrl22 {
	struct {
		uint32_t io_offset_cal_rdqs:7; /* [6:0] */
		uint32_t reserved0:25; /* [31:7] */
	};
	uint32_t val;
};

union hbm3ephy_wr_lvl_fail_stat0 {
	struct {
		uint32_t wrlvl_fail_status:2; /* [1:0] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_wr_lvl_overflow_stat0 {
	struct {
		uint32_t wdqs_overflow:2; /* [1:0] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_fail_stat0 {
	struct {
		uint32_t write_dq_fail_status0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_fail_stat1 {
	struct {
		uint32_t write_dq_fail_status1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_fail_stat2 {
	struct {
		uint32_t write_sev_fail_status0:2; /* [1:0] */
		uint32_t write_sev_fail_status1:2; /* [3:2] */
		uint32_t write_ecc_fail_status0:2; /* [5:4] */
		uint32_t write_ecc_fail_status1:2; /* [7:6] */
		uint32_t write_dbi_fail_status0:4; /* [11:8] */
		uint32_t write_dbi_fail_status1:4; /* [15:12] */
		uint32_t write_par_fail_status0:1; /* [16:16] */
		uint32_t write_par_fail_status1:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow0 {
	struct {
		uint32_t read_dq_overflow0:1; /* [0:0] */
		uint32_t read_dq_overflow1:1; /* [1:1] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow1 {
	struct {
		uint32_t rddeskewcode_overflow0_dq; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow2 {
	struct {
		uint32_t rddeskewcode_overflow1_dq; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow3 {
	struct {
		uint32_t rddeskewcode_overflow0_sev:2; /* [1:0] */
		uint32_t rddeskewcode_overflow1_sev:2; /* [3:2] */
		uint32_t rddeskewcode_overflow0_ecc:2; /* [5:4] */
		uint32_t rddeskewcode_overflow1_ecc:2; /* [7:6] */
		uint32_t rddeskewcode_overflow0_dbi:4; /* [11:8] */
		uint32_t rddeskewcode_overflow1_dbi:4; /* [15:12] */
		uint32_t rddeskewcode_overflow0_par:1; /* [16:16] */
		uint32_t rddeskewcode_overflow1_par:1; /* [17:17] */
		uint32_t rddeskewcode_overflow0_rd:2; /* [19:18] */
		uint32_t rddeskewcode_overflow1_rd:2; /* [21:20] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow4 {
	struct {
		uint32_t rddqsdeskewcode_overflow0_dq; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow5 {
	struct {
		uint32_t rddqsdeskewcode_overflow1_dq; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_rd_cal_overflow6 {
	struct {
		uint32_t rddqsdeskewcode_overflow0_sev:2; /* [1:0] */
		uint32_t rddqsdeskewcode_overflow1_sev:2; /* [3:2] */
		uint32_t rddqsdeskewcode_overflow0_ecc:2; /* [5:4] */
		uint32_t rddqsdeskewcode_overflow1_ecc:2; /* [7:6] */
		uint32_t rddqsdeskewcode_overflow0_dbi:4; /* [11:8] */
		uint32_t rddqsdeskewcode_overflow1_dbi:4; /* [15:12] */
		uint32_t rddqsdeskewcode_overflow0_par:1; /* [16:16] */
		uint32_t rddqsdeskewcode_overflow1_par:1; /* [17:17] */
		uint32_t rddqsdeskewcode_overflow0_rd:2; /* [19:18] */
		uint32_t rddqsdeskewcode_overflow1_rd:2; /* [21:20] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_overflow0 {
	struct {
		uint32_t wdq_overflow0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_overflow1 {
	struct {
		uint32_t wdq_overflow1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_wr_cal_overflow2 {
	struct {
		uint32_t wecc_overflow0:2; /* [1:0] */
		uint32_t wecc_overflow1:2; /* [3:2] */
		uint32_t wsev_overflow0:2; /* [5:4] */
		uint32_t wsev_overflow1:2; /* [7:6] */
		uint32_t wdbi_overflow0:4; /* [11:8] */
		uint32_t wdbi_overflow1:4; /* [15:12] */
		uint32_t wpar_overflow0:1; /* [16:16] */
		uint32_t wpar_overflow1:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_io_vref_con0 {
	struct {
		uint32_t zq_aword_pmon:3; /* [2:0] */
		uint32_t zq_aword_nmon:3; /* [5:3] */
		uint32_t zq_aword_dds:2; /* [7:6] */
		uint32_t zq_aword_vref_pd:1; /* [8:8] */
		uint32_t zq_aword_vref:6; /* [14:9] */
		uint32_t zq_aword_vref_fsbst:1; /* [15:15] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union hbm3ephy_io_vref_con1 {
	struct {
		uint32_t zq_dword0_pmon:6; /* [5:0] */
		uint32_t zq_dword0_nmon:6; /* [11:6] */
		uint32_t zq_dword0_dds:4; /* [15:12] */
		uint32_t zq_dword0_vref_pd:2; /* [17:16] */
		uint32_t zq_dword0_vref:12; /* [29:18] */
		uint32_t zq_dword0_vref_fsbst:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_io_vref_con2 {
	struct {
		uint32_t zq_dword1_pmon:6; /* [5:0] */
		uint32_t zq_dword1_nmon:6; /* [11:6] */
		uint32_t zq_dword1_dds:4; /* [15:12] */
		uint32_t zq_dword1_vref_pd:2; /* [17:16] */
		uint32_t zq_dword1_vref:12; /* [29:18] */
		uint32_t zq_dword1_vref_fsbst:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_io_ctrl_con0 {
	struct {
		uint32_t ctrl_ibias_rcv_en_dword0:1; /* [0:0] */
		uint32_t ctrl_ibias_rcv_dword0:2; /* [2:1] */
		uint32_t ctrl_ibias_rcv_en_dword1:1; /* [3:3] */
		uint32_t ctrl_ibias_rcv_dword1:2; /* [5:4] */
		uint32_t reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union hbm3ephy_io_ctrl_con1 {
	struct {
		uint32_t testihbm3_dword:20; /* [19:0] */
		uint32_t testihbm3_aword:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_zq_test_con0 {
	struct {
		uint32_t zq_test:2; /* [1:0] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_aword_stat0 {
	struct {
		uint32_t test_err_ra:10; /* [9:0] */
		uint32_t test_oky_ra:10; /* [19:10] */
		uint32_t reserved0:12; /* [31:20] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_aword_stat1 {
	struct {
		uint32_t test_err_ca:8; /* [7:0] */
		uint32_t test_oky_ca:8; /* [15:8] */
		uint32_t test_err_rrc:1; /* [16:16] */
		uint32_t test_oky_rrc:1; /* [17:17] */
		uint32_t test_err_apar:1; /* [18:18] */
		uint32_t test_oky_apar:1; /* [19:19] */
		uint32_t test_err_arfu:1; /* [20:20] */
		uint32_t test_oky_arfu:1; /* [21:21] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_stat0 {
	struct {
		uint32_t test_ext_clock:1; /* [0:0] */
		uint32_t test_ext_flock:1; /* [1:1] */
		uint32_t test_ext_locked:1; /* [2:2] */
		uint32_t test_ext_lock_value:10; /* [12:3] */
		uint32_t reserved0:19; /* [31:13] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_stat1 {
	struct {
		uint32_t test_ext_init_complete:1; /* [0:0] */
		uint32_t test_ext_rdlvl_vwmc:20; /* [20:1] */
		uint32_t dll_test_done:2; /* [22:21] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con0 {
	struct {
		uint32_t ptc_mode_dword0:1; /* [0:0] */
		uint32_t ptc_mode_dword1:1; /* [1:1] */
		uint32_t ptc_test_start:3; /* [4:2] */
		uint32_t test_compare:1; /* [5:5] */
		uint32_t test_end:1; /* [6:6] */
		uint32_t mode_phy:1; /* [7:7] */
		uint32_t mode_scan:1; /* [8:8] */
		uint32_t reserved1:1; /* [9:9] */
		uint32_t mode_run:3; /* [12:10] */
		uint32_t ptc_test_ext_dfwdqs:1; /* [13:13] */
		uint32_t ptc_test_ext_dfrdqs:1; /* [14:14] */
		uint32_t ptc_test_ext_half:1; /* [15:15] */
		uint32_t ptc_test_ext_mode:4; /* [19:16] */
		uint32_t ptc_test_ext_lvl_en:1; /* [20:20] */
		uint32_t ptc_test_ext_dll_test:1; /* [21:21] */
		uint32_t ptc_test_ext_auto_dqs_en:1; /* [22:22] */
		uint32_t ptc_test_ext_debug:8; /* [30:23] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con1 {
	struct {
		uint32_t ptc_test_ext_offsetd:9; /* [8:0] */
		uint32_t ptc_test_ext_offsetr:10; /* [18:9] */
		uint32_t reserved1:1; /* [19:19] */
		uint32_t ptc_test_ext_offsetw:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con2 {
	struct {
		uint32_t fb_bl_sel:1; /* [0:0] */
		uint32_t fb_data_pattern:2; /* [2:1] */
		uint32_t reserved1:5; /* [7:3] */
		uint32_t fb_rdlat:2; /* [9:8] */
		uint32_t fb_wrlat:2; /* [11:10] */
		uint32_t fb_lfsr_en:1; /* [12:12] */
		uint32_t reserved0:19; /* [31:13] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con3 {
	struct {
		uint32_t fb_bit_pattern_dq0:2; /* [1:0] */
		uint32_t fb_bit_pattern_dq1:2; /* [3:2] */
		uint32_t fb_bit_pattern_dq2:2; /* [5:4] */
		uint32_t fb_bit_pattern_dq3:2; /* [7:6] */
		uint32_t fb_bit_pattern_dq4:2; /* [9:8] */
		uint32_t fb_bit_pattern_dq5:2; /* [11:10] */
		uint32_t fb_bit_pattern_dq6:2; /* [13:12] */
		uint32_t fb_bit_pattern_dq7:2; /* [15:14] */
		uint32_t fb_bit_pattern_dq8:2; /* [17:16] */
		uint32_t fb_bit_pattern_dq9:2; /* [19:18] */
		uint32_t fb_bit_pattern_dq10:2; /* [21:20] */
		uint32_t fb_bit_pattern_dq11:2; /* [23:22] */
		uint32_t fb_bit_pattern_dq12:2; /* [25:24] */
		uint32_t fb_bit_pattern_dq13:2; /* [27:26] */
		uint32_t fb_bit_pattern_dq14:2; /* [29:28] */
		uint32_t fb_bit_pattern_dq15:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con4 {
	struct {
		uint32_t fb_bit_pattern_dq16:2; /* [1:0] */
		uint32_t fb_bit_pattern_dq17:2; /* [3:2] */
		uint32_t fb_bit_pattern_dq18:2; /* [5:4] */
		uint32_t fb_bit_pattern_dq19:2; /* [7:6] */
		uint32_t fb_bit_pattern_dq20:2; /* [9:8] */
		uint32_t fb_bit_pattern_dq21:2; /* [11:10] */
		uint32_t fb_bit_pattern_dq22:2; /* [13:12] */
		uint32_t fb_bit_pattern_dq23:2; /* [15:14] */
		uint32_t fb_bit_pattern_dq24:2; /* [17:16] */
		uint32_t fb_bit_pattern_dq25:2; /* [19:18] */
		uint32_t fb_bit_pattern_dq26:2; /* [21:20] */
		uint32_t fb_bit_pattern_dq27:2; /* [23:22] */
		uint32_t fb_bit_pattern_dq28:2; /* [25:24] */
		uint32_t fb_bit_pattern_dq29:2; /* [27:26] */
		uint32_t fb_bit_pattern_dq30:2; /* [29:28] */
		uint32_t fb_bit_pattern_dq31:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_ptc_con5 {
	struct {
		uint32_t fb_bit_pattern_dbi0:2; /* [1:0] */
		uint32_t fb_bit_pattern_dbi1:2; /* [3:2] */
		uint32_t fb_bit_pattern_dbi2:2; /* [5:4] */
		uint32_t fb_bit_pattern_dbi3:2; /* [7:6] */
		uint32_t fb_bit_pattern_ecc0:2; /* [9:8] */
		uint32_t fb_bit_pattern_ecc1:2; /* [11:10] */
		uint32_t fb_bit_pattern_sev0:2; /* [13:12] */
		uint32_t fb_bit_pattern_sev1:2; /* [15:14] */
		uint32_t fb_bit_pattern_dpar0:2; /* [17:16] */
		uint32_t fb_bit_pattern_rd0:2; /* [19:18] */
		uint32_t fb_bit_pattern_rd1:2; /* [21:20] */
		uint32_t reserved0:10; /* [31:22] */
	};
	uint32_t val;
};

union hbm3ephy_apar_stat1 {
	struct {
		uint32_t apar_fbdata:1; /* [0:0] */
		uint32_t reserved0:31; /* [31:1] */
	};
	uint32_t val;
};

union hbm3ephy_polling_read_trn_con0 {
	struct {
		uint32_t polling_read_trn_range_dword0:2; /* [1:0] */
		uint32_t polling_read_trn_range_dword1:2; /* [3:2] */
		uint32_t polling_read_trn_dq_mask_dword0:1; /* [4:4] */
		uint32_t polling_read_trn_dq_mask_dword1:1; /* [5:5] */
		uint32_t polling_read_trn_ecc_mask_dword0:1; /* [6:6] */
		uint32_t polling_read_trn_ecc_mask_dword1:1; /* [7:7] */
		uint32_t polling_read_trn_sev_mask_dword0:1; /* [8:8] */
		uint32_t polling_read_trn_sev_mask_dword1:1; /* [9:9] */
		uint32_t polling_read_trn_dbi_mask_dword0:1; /* [10:10] */
		uint32_t polling_read_trn_dbi_mask_dword1:1; /* [11:11] */
		uint32_t polling_read_trn_dpar_mask_dword0:1; /* [12:12] */
		uint32_t polling_read_trn_dpar_mask_dword1:1; /* [13:13] */
		uint32_t polling_read_trn_rd_mask_dword0:1; /* [14:14] */
		uint32_t polling_read_trn_rd_mask_dword1:1; /* [15:15] */
		uint32_t mrg_reg_rst_n:1; /* [16:16] */
		uint32_t reserved0:15; /* [31:17] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat0 {
	struct {
		uint32_t dq_rise_left_mrg_fail_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat1 {
	struct {
		uint32_t dq_rise_left_mrg_fail_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat2 {
	struct {
		uint32_t dq_rise_right_mrg_fail_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat3 {
	struct {
		uint32_t dq_rise_right_mrg_fail_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat4 {
	struct {
		uint32_t dq_fall_left_mrg_fail_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat5 {
	struct {
		uint32_t dq_fall_left_mrg_fail_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat6 {
	struct {
		uint32_t dq_fall_right_mrg_fail_dword1; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat7 {
	struct {
		uint32_t dq_fall_right_mrg_fail_dword0; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat8 {
	struct {
		uint32_t dbi_fall_right_mrg_fail_dword0:4; /* [3:0] */
		uint32_t dbi_fall_right_mrg_fail_dword1:4; /* [7:4] */
		uint32_t dbi_fall_left_mrg_fail_dword0:4; /* [11:8] */
		uint32_t dbi_fall_left_mrg_fail_dword1:4; /* [15:12] */
		uint32_t dbi_rise_right_mrg_fail_dword0:4; /* [19:16] */
		uint32_t dbi_rise_right_mrg_fail_dword1:4; /* [23:20] */
		uint32_t dbi_rise_left_mrg_fail_dword0:4; /* [27:24] */
		uint32_t dbi_rise_left_mrg_fail_dword1:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat9 {
	struct {
		uint32_t sev_fall_right_mrg_fail_dword0:2; /* [1:0] */
		uint32_t sev_fall_right_mrg_fail_dword1:2; /* [3:2] */
		uint32_t sev_fall_left_mrg_fail_dword0:2; /* [5:4] */
		uint32_t sev_fall_left_mrg_fail_dword1:2; /* [7:6] */
		uint32_t sev_rise_right_mrg_fail_dword0:2; /* [9:8] */
		uint32_t sev_rise_right_mrg_fail_dword1:2; /* [11:10] */
		uint32_t sev_rise_left_mrg_fail_dword0:2; /* [13:12] */
		uint32_t sev_rise_left_mrg_fail_dword1:2; /* [15:14] */
		uint32_t ecc_fall_right_mrg_fail_dword0:2; /* [17:16] */
		uint32_t ecc_fall_right_mrg_fail_dword1:2; /* [19:18] */
		uint32_t ecc_fall_left_mrg_fail_dword0:2; /* [21:20] */
		uint32_t ecc_fall_left_mrg_fail_dword1:2; /* [23:22] */
		uint32_t ecc_rise_right_mrg_fail_dword0:2; /* [25:24] */
		uint32_t ecc_rise_right_mrg_fail_dword1:2; /* [27:26] */
		uint32_t ecc_rise_left_mrg_fail_dword0:2; /* [29:28] */
		uint32_t ecc_rise_left_mrg_fail_dword1:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_mrg_stat10 {
	struct {
		uint32_t dpar_fall_right_mrg_fail_dword0:1; /* [0:0] */
		uint32_t dpar_fall_right_mrg_fail_dword1:1; /* [1:1] */
		uint32_t dpar_fall_left_mrg_fail_dword0:1; /* [2:2] */
		uint32_t dpar_fall_left_mrg_fail_dword1:1; /* [3:3] */
		uint32_t dpar_rise_right_mrg_fail_dword0:1; /* [4:4] */
		uint32_t dpar_rise_right_mrg_fail_dword1:1; /* [5:5] */
		uint32_t dpar_rise_left_mrg_fail_dword0:1; /* [6:6] */
		uint32_t dpar_rise_left_mrg_fail_dword1:1; /* [7:7] */
		uint32_t rd_fall_right_mrg_fail_dword0:2; /* [9:8] */
		uint32_t rd_fall_right_mrg_fail_dword1:2; /* [11:10] */
		uint32_t rd_fall_left_mrg_fail_dword0:2; /* [13:12] */
		uint32_t rd_fall_left_mrg_fail_dword1:2; /* [15:14] */
		uint32_t rd_rise_right_mrg_fail_dword0:2; /* [17:16] */
		uint32_t rd_rise_right_mrg_fail_dword1:2; /* [19:18] */
		uint32_t rd_rise_left_mrg_fail_dword0:2; /* [21:20] */
		uint32_t rd_rise_left_mrg_fail_dword1:2; /* [23:22] */
		uint32_t reserved0:8; /* [31:24] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_con0 {
	struct {
		uint32_t sw_trn_en:1; /* [0:0] */
		uint32_t sw_trn_mode:7; /* [7:1] */
		uint32_t reserved0:24; /* [31:8] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_con1 {
	struct {
		uint32_t sw_trn_ready_command_num:6; /* [5:0] */
		uint32_t sw_trn_loop_command_num:6; /* [11:6] */
		uint32_t sw_trn_finish_command_num:6; /* [17:12] */
		uint32_t sw_trn_loop_cnt_apb:10; /* [27:18] */
		uint32_t sw_trn_wrpar_wait_cnt_apb:4; /* [31:28] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_con2 {
	struct {
		uint32_t sw_trn_wait0_cnt_apb:11; /* [10:0] */
		uint32_t sw_trn_wait1_cnt_apb:10; /* [20:11] */
		uint32_t sw_trn_done_cnt_apb:11; /* [31:21] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd0_0 {
	struct {
		uint32_t sw_trn_cmd0_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd0_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd0_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd0_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd0_1 {
	struct {
		uint32_t sw_trn_cmd0_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd0_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd0_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd0_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd0_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd0_all:1; /* [16:16] */
		uint32_t sw_trn_cmd0_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd1_0 {
	struct {
		uint32_t sw_trn_cmd1_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd1_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd1_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd1_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd1_1 {
	struct {
		uint32_t sw_trn_cmd1_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd1_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd1_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd1_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd1_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd1_all:1; /* [16:16] */
		uint32_t sw_trn_cmd1_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd2_0 {
	struct {
		uint32_t sw_trn_cmd2_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd2_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd2_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd2_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd2_1 {
	struct {
		uint32_t sw_trn_cmd2_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd2_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd2_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd2_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd2_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd2_all:1; /* [16:16] */
		uint32_t sw_trn_cmd2_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd3_0 {
	struct {
		uint32_t sw_trn_cmd3_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd3_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd3_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd3_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd3_1 {
	struct {
		uint32_t sw_trn_cmd3_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd3_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd3_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd3_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd3_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd3_all:1; /* [16:16] */
		uint32_t sw_trn_cmd3_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd4_0 {
	struct {
		uint32_t sw_trn_cmd4_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd4_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd4_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd4_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd4_1 {
	struct {
		uint32_t sw_trn_cmd4_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd4_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd4_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd4_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd4_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd4_all:1; /* [16:16] */
		uint32_t sw_trn_cmd4_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd5_0 {
	struct {
		uint32_t sw_trn_cmd5_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd5_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd5_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd5_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd5_1 {
	struct {
		uint32_t sw_trn_cmd5_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd5_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd5_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd5_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd5_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd5_all:1; /* [16:16] */
		uint32_t sw_trn_cmd5_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd6_0 {
	struct {
		uint32_t sw_trn_cmd6_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd6_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd6_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd6_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd6_1 {
	struct {
		uint32_t sw_trn_cmd6_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd6_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd6_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd6_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd6_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd6_all:1; /* [16:16] */
		uint32_t sw_trn_cmd6_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd7_0 {
	struct {
		uint32_t sw_trn_cmd7_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd7_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd7_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd7_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd7_1 {
	struct {
		uint32_t sw_trn_cmd7_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd7_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd7_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd7_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd7_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd7_all:1; /* [16:16] */
		uint32_t sw_trn_cmd7_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd8_0 {
	struct {
		uint32_t sw_trn_cmd8_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd8_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd8_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd8_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd8_1 {
	struct {
		uint32_t sw_trn_cmd8_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd8_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd8_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd8_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd8_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd8_all:1; /* [16:16] */
		uint32_t sw_trn_cmd8_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd9_0 {
	struct {
		uint32_t sw_trn_cmd9_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd9_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd9_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd9_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd9_1 {
	struct {
		uint32_t sw_trn_cmd9_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd9_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd9_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd9_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd9_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd9_all:1; /* [16:16] */
		uint32_t sw_trn_cmd9_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd10_0 {
	struct {
		uint32_t sw_trn_cmd10_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd10_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd10_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd10_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd10_1 {
	struct {
		uint32_t sw_trn_cmd10_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd10_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd10_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd10_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd10_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd10_all:1; /* [16:16] */
		uint32_t sw_trn_cmd10_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd11_0 {
	struct {
		uint32_t sw_trn_cmd11_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd11_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd11_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd11_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd11_1 {
	struct {
		uint32_t sw_trn_cmd11_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd11_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd11_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd11_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd11_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd11_all:1; /* [16:16] */
		uint32_t sw_trn_cmd11_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd12_0 {
	struct {
		uint32_t sw_trn_cmd12_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd12_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd12_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd12_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd12_1 {
	struct {
		uint32_t sw_trn_cmd12_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd12_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd12_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd12_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd12_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd12_all:1; /* [16:16] */
		uint32_t sw_trn_cmd12_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd13_0 {
	struct {
		uint32_t sw_trn_cmd13_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd13_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd13_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd13_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd13_1 {
	struct {
		uint32_t sw_trn_cmd13_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd13_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd13_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd13_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd13_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd13_all:1; /* [16:16] */
		uint32_t sw_trn_cmd13_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd14_0 {
	struct {
		uint32_t sw_trn_cmd14_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd14_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd14_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd14_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd14_1 {
	struct {
		uint32_t sw_trn_cmd14_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd14_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd14_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd14_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd14_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd14_all:1; /* [16:16] */
		uint32_t sw_trn_cmd14_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd15_0 {
	struct {
		uint32_t sw_trn_cmd15_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd15_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd15_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd15_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd15_1 {
	struct {
		uint32_t sw_trn_cmd15_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd15_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd15_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd15_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd15_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd15_all:1; /* [16:16] */
		uint32_t sw_trn_cmd15_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd16_0 {
	struct {
		uint32_t sw_trn_cmd16_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd16_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd16_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd16_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd16_1 {
	struct {
		uint32_t sw_trn_cmd16_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd16_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd16_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd16_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd16_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd16_all:1; /* [16:16] */
		uint32_t sw_trn_cmd16_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd17_0 {
	struct {
		uint32_t sw_trn_cmd17_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd17_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd17_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd17_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd17_1 {
	struct {
		uint32_t sw_trn_cmd17_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd17_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd17_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd17_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd17_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd17_all:1; /* [16:16] */
		uint32_t sw_trn_cmd17_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd18_0 {
	struct {
		uint32_t sw_trn_cmd18_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd18_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd18_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd18_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd18_1 {
	struct {
		uint32_t sw_trn_cmd18_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd18_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd18_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd18_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd18_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd18_all:1; /* [16:16] */
		uint32_t sw_trn_cmd18_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd19_0 {
	struct {
		uint32_t sw_trn_cmd19_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd19_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd19_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd19_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd19_1 {
	struct {
		uint32_t sw_trn_cmd19_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd19_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd19_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd19_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd19_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd19_all:1; /* [16:16] */
		uint32_t sw_trn_cmd19_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd20_0 {
	struct {
		uint32_t sw_trn_cmd20_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd20_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd20_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd20_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd20_1 {
	struct {
		uint32_t sw_trn_cmd20_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd20_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd20_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd20_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd20_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd20_all:1; /* [16:16] */
		uint32_t sw_trn_cmd20_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd21_0 {
	struct {
		uint32_t sw_trn_cmd21_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd21_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd21_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd21_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd21_1 {
	struct {
		uint32_t sw_trn_cmd21_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd21_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd21_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd21_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd21_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd21_all:1; /* [16:16] */
		uint32_t sw_trn_cmd21_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd22_0 {
	struct {
		uint32_t sw_trn_cmd22_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd22_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd22_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd22_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd22_1 {
	struct {
		uint32_t sw_trn_cmd22_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd22_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd22_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd22_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd22_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd22_all:1; /* [16:16] */
		uint32_t sw_trn_cmd22_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd23_0 {
	struct {
		uint32_t sw_trn_cmd23_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd23_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd23_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd23_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd23_1 {
	struct {
		uint32_t sw_trn_cmd23_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd23_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd23_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd23_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd23_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd23_all:1; /* [16:16] */
		uint32_t sw_trn_cmd23_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd24_0 {
	struct {
		uint32_t sw_trn_cmd24_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd24_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd24_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd24_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd24_1 {
	struct {
		uint32_t sw_trn_cmd24_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd24_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd24_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd24_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd24_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd24_all:1; /* [16:16] */
		uint32_t sw_trn_cmd24_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd25_0 {
	struct {
		uint32_t sw_trn_cmd25_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd25_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd25_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd25_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd25_1 {
	struct {
		uint32_t sw_trn_cmd25_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd25_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd25_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd25_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd25_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd25_all:1; /* [16:16] */
		uint32_t sw_trn_cmd25_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd26_0 {
	struct {
		uint32_t sw_trn_cmd26_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd26_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd26_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd26_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd26_1 {
	struct {
		uint32_t sw_trn_cmd26_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd26_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd26_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd26_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd26_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd26_all:1; /* [16:16] */
		uint32_t sw_trn_cmd26_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd27_0 {
	struct {
		uint32_t sw_trn_cmd27_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd27_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd27_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd27_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd27_1 {
	struct {
		uint32_t sw_trn_cmd27_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd27_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd27_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd27_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd27_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd27_all:1; /* [16:16] */
		uint32_t sw_trn_cmd27_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd28_0 {
	struct {
		uint32_t sw_trn_cmd28_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd28_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd28_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd28_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd28_1 {
	struct {
		uint32_t sw_trn_cmd28_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd28_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd28_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd28_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd28_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd28_all:1; /* [16:16] */
		uint32_t sw_trn_cmd28_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd29_0 {
	struct {
		uint32_t sw_trn_cmd29_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd29_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd29_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd29_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd29_1 {
	struct {
		uint32_t sw_trn_cmd29_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd29_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd29_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd29_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd29_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd29_all:1; /* [16:16] */
		uint32_t sw_trn_cmd29_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd30_0 {
	struct {
		uint32_t sw_trn_cmd30_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd30_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd30_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd30_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd30_1 {
	struct {
		uint32_t sw_trn_cmd30_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd30_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd30_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd30_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd30_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd30_all:1; /* [16:16] */
		uint32_t sw_trn_cmd30_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd31_0 {
	struct {
		uint32_t sw_trn_cmd31_sel:7; /* [6:0] */
		uint32_t sw_trn_cmd31_ba_code:4; /* [10:7] */
		uint32_t sw_trn_cmd31_ra_code:15; /* [25:11] */
		uint32_t sw_trn_cmd31_ma_code:5; /* [30:26] */
		uint32_t reserved0:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_sw_trn_cmd31_1 {
	struct {
		uint32_t sw_trn_cmd31_ca_code:5; /* [4:0] */
		uint32_t sw_trn_cmd31_op_code:8; /* [12:5] */
		uint32_t sw_trn_cmd31_sid0:1; /* [13:13] */
		uint32_t sw_trn_cmd31_sid1:1; /* [14:14] */
		uint32_t sw_trn_cmd31_ch:1; /* [15:15] */
		uint32_t sw_trn_cmd31_all:1; /* [16:16] */
		uint32_t sw_trn_cmd31_rfm:1; /* [17:17] */
		uint32_t reserved0:14; /* [31:18] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode0 {
	struct {
		uint32_t ca0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode1 {
	struct {
		uint32_t ca2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode2 {
	struct {
		uint32_t ca4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode3 {
	struct {
		uint32_t ca6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ca7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode4 {
	struct {
		uint32_t ra0deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra1deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode5 {
	struct {
		uint32_t ra2deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra3deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode6 {
	struct {
		uint32_t ra4deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra5deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode7 {
	struct {
		uint32_t ra6deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra7deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode8 {
	struct {
		uint32_t ra8deskewcode:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t ra9deskewcode:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode9 {
	struct {
		uint32_t wdqsdeskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wdqsdeskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode10 {
	struct {
		uint32_t rdqsdeskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t rdqsdeskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode11 {
	struct {
		uint32_t rddq0deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq0deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode12 {
	struct {
		uint32_t rddq1deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq1deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode13 {
	struct {
		uint32_t rddq2deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq2deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode14 {
	struct {
		uint32_t rddq3deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq3deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode15 {
	struct {
		uint32_t rddq4deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq4deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode16 {
	struct {
		uint32_t rddq5deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq5deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode17 {
	struct {
		uint32_t rddq6deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq6deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode18 {
	struct {
		uint32_t rddq7deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq7deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode19 {
	struct {
		uint32_t rddq8deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq8deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode20 {
	struct {
		uint32_t rddq9deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq9deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode21 {
	struct {
		uint32_t rddq10deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq10deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode22 {
	struct {
		uint32_t rddq11deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq11deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode23 {
	struct {
		uint32_t rddq12deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq12deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode24 {
	struct {
		uint32_t rddq13deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq13deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode25 {
	struct {
		uint32_t rddq14deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq14deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode26 {
	struct {
		uint32_t rddq15deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq15deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode27 {
	struct {
		uint32_t rddq16deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq16deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode28 {
	struct {
		uint32_t rddq17deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq17deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode29 {
	struct {
		uint32_t rddq18deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq18deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode30 {
	struct {
		uint32_t rddq19deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq19deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode31 {
	struct {
		uint32_t rddq20deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq20deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode32 {
	struct {
		uint32_t rddq21deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq21deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode33 {
	struct {
		uint32_t rddq22deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq22deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode34 {
	struct {
		uint32_t rddq23deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq23deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode35 {
	struct {
		uint32_t rddq24deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq24deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode36 {
	struct {
		uint32_t rddq25deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq25deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode37 {
	struct {
		uint32_t rddq26deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq26deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode38 {
	struct {
		uint32_t rddq27deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq27deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode39 {
	struct {
		uint32_t rddq28deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq28deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode40 {
	struct {
		uint32_t rddq29deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq29deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode41 {
	struct {
		uint32_t rddq30deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq30deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode42 {
	struct {
		uint32_t rddq31deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq31deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode43 {
	struct {
		uint32_t rdecc0deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdecc0deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode44 {
	struct {
		uint32_t rdecc1deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdecc1deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode45 {
	struct {
		uint32_t rdsev0deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdsev0deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode46 {
	struct {
		uint32_t rdsev1deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdsev1deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode47 {
	struct {
		uint32_t rddbi0deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi0deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode48 {
	struct {
		uint32_t rddbi1deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi1deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode49 {
	struct {
		uint32_t rddbi2deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi2deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode50 {
	struct {
		uint32_t rddbi3deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi3deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode51 {
	struct {
		uint32_t rdpardeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdpardeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode52 {
	struct {
		uint32_t rdrd0deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdrd0deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode53 {
	struct {
		uint32_t rdrd1deskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdrd1deskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode54 {
	struct {
		uint32_t rddq0dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq0dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode55 {
	struct {
		uint32_t rddq1dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq1dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode56 {
	struct {
		uint32_t rddq2dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq2dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode57 {
	struct {
		uint32_t rddq3dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq3dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode58 {
	struct {
		uint32_t rddq4dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq4dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode59 {
	struct {
		uint32_t rddq5dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq5dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode60 {
	struct {
		uint32_t rddq6dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq6dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode61 {
	struct {
		uint32_t rddq7dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq7dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode62 {
	struct {
		uint32_t rddq8dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq8dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode63 {
	struct {
		uint32_t rddq9dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq9dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode64 {
	struct {
		uint32_t rddq10dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq10dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode65 {
	struct {
		uint32_t rddq11dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq11dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode66 {
	struct {
		uint32_t rddq12dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq12dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode67 {
	struct {
		uint32_t rddq13dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq13dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode68 {
	struct {
		uint32_t rddq14dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq14dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode69 {
	struct {
		uint32_t rddq15dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq15dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode70 {
	struct {
		uint32_t rddq16dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq16dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode71 {
	struct {
		uint32_t rddq17dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq17dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode72 {
	struct {
		uint32_t rddq18dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq18dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode73 {
	struct {
		uint32_t rddq19dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq19dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode74 {
	struct {
		uint32_t rddq20dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq20dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode75 {
	struct {
		uint32_t rddq21dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq21dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode76 {
	struct {
		uint32_t rddq22dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq22dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode77 {
	struct {
		uint32_t rddq23dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq23dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode78 {
	struct {
		uint32_t rddq24dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq24dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode79 {
	struct {
		uint32_t rddq25dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq25dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode80 {
	struct {
		uint32_t rddq26dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq26dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode81 {
	struct {
		uint32_t rddq27dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq27dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode82 {
	struct {
		uint32_t rddq28dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq28dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode83 {
	struct {
		uint32_t rddq29dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq29dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode84 {
	struct {
		uint32_t rddq30dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq30dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode85 {
	struct {
		uint32_t rddq31dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddq31dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode86 {
	struct {
		uint32_t rdecc0dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdecc0dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode87 {
	struct {
		uint32_t rdecc1dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdecc1dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode88 {
	struct {
		uint32_t rdsev0dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdsev0dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode89 {
	struct {
		uint32_t rdsev1dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdsev1dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode90 {
	struct {
		uint32_t rddbi0dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi0dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode91 {
	struct {
		uint32_t rddbi1dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi1dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode92 {
	struct {
		uint32_t rddbi2dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi2dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode93 {
	struct {
		uint32_t rddbi3dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rddbi3dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode94 {
	struct {
		uint32_t rdpardqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdpardqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode95 {
	struct {
		uint32_t rdrd0dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdrd0dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode96 {
	struct {
		uint32_t rdrd1dqsdeskewcode0:7; /* [6:0] */
		uint32_t reserved1:9; /* [15:7] */
		uint32_t rdrd1dqsdeskewcode1:7; /* [22:16] */
		uint32_t reserved0:9; /* [31:23] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode97 {
	struct {
		uint32_t wrdq0deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq0deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode98 {
	struct {
		uint32_t wrdq1deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq1deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode99 {
	struct {
		uint32_t wrdq2deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq2deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode100 {
	struct {
		uint32_t wrdq3deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq3deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode101 {
	struct {
		uint32_t wrdq4deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq4deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode102 {
	struct {
		uint32_t wrdq5deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq5deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode103 {
	struct {
		uint32_t wrdq6deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq6deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode104 {
	struct {
		uint32_t wrdq7deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq7deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode105 {
	struct {
		uint32_t wrdq8deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq8deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode106 {
	struct {
		uint32_t wrdq9deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq9deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode107 {
	struct {
		uint32_t wrdq10deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq10deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode108 {
	struct {
		uint32_t wrdq11deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq11deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode109 {
	struct {
		uint32_t wrdq12deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq12deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode110 {
	struct {
		uint32_t wrdq13deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq13deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode111 {
	struct {
		uint32_t wrdq14deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq14deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode112 {
	struct {
		uint32_t wrdq15deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq15deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode113 {
	struct {
		uint32_t wrdq16deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq16deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode114 {
	struct {
		uint32_t wrdq17deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq17deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode115 {
	struct {
		uint32_t wrdq18deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq18deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode116 {
	struct {
		uint32_t wrdq19deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq19deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode117 {
	struct {
		uint32_t wrdq20deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq20deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode118 {
	struct {
		uint32_t wrdq21deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq21deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode119 {
	struct {
		uint32_t wrdq22deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq22deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode120 {
	struct {
		uint32_t wrdq23deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq23deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode121 {
	struct {
		uint32_t wrdq24deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq24deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode122 {
	struct {
		uint32_t wrdq25deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq25deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode123 {
	struct {
		uint32_t wrdq26deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq26deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode124 {
	struct {
		uint32_t wrdq27deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq27deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode125 {
	struct {
		uint32_t wrdq28deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq28deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode126 {
	struct {
		uint32_t wrdq29deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq29deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode127 {
	struct {
		uint32_t wrdq30deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq30deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode128 {
	struct {
		uint32_t wrdq31deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq31deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode129 {
	struct {
		uint32_t wrecc0deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc0deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode130 {
	struct {
		uint32_t wrecc1deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc1deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode131 {
	struct {
		uint32_t wrsev0deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev0deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode132 {
	struct {
		uint32_t wrsev1deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev1deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode133 {
	struct {
		uint32_t wrdbi0deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi0deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode134 {
	struct {
		uint32_t wrdbi1deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi1deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode135 {
	struct {
		uint32_t wrdbi2deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi2deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode136 {
	struct {
		uint32_t wrdbi3deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi3deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode137 {
	struct {
		uint32_t wrpardeskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrpardeskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode138 {
	struct {
		uint32_t wrrd0deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrrd0deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_final_deskewcode139 {
	struct {
		uint32_t wrrd1deskewcode0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrrd1deskewcode1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr0 {
	struct {
		uint32_t prbs_offsetr_par_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_ecc1_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr1 {
	struct {
		uint32_t prbs_offsetr_dbi2_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dbi1_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr2 {
	struct {
		uint32_t prbs_offsetr_dq1_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq0_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr3 {
	struct {
		uint32_t prbs_offsetr_dq4_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq3_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr4 {
	struct {
		uint32_t prbs_offsetr_dq7_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq6_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr5 {
	struct {
		uint32_t prbs_offsetr_dq10_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq9_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr6 {
	struct {
		uint32_t prbs_offsetr_dq13_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq12_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr7 {
	struct {
		uint32_t prbs_offsetr_dq16_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq15_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr8 {
	struct {
		uint32_t prbs_offsetr_dq19_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq18_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr9 {
	struct {
		uint32_t prbs_offsetr_dq22_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq21_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr10 {
	struct {
		uint32_t prbs_offsetr_dq25_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq24_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr11 {
	struct {
		uint32_t prbs_offsetr_dq28_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq27_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr12 {
	struct {
		uint32_t prbs_offsetr_dq31_dword0:10; /* [9:0] */
		uint32_t prbs_offsetr_dq30_dword0:10; /* [19:10] */
		uint32_t prbs_offsetr_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr13 {
	struct {
		uint32_t prbs_offsetr_par_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_ecc1_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr14 {
	struct {
		uint32_t prbs_offsetr_dbi2_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dbi1_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr15 {
	struct {
		uint32_t prbs_offsetr_dq1_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq0_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr16 {
	struct {
		uint32_t prbs_offsetr_dq4_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq3_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr17 {
	struct {
		uint32_t prbs_offsetr_dq7_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq6_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr18 {
	struct {
		uint32_t prbs_offsetr_dq10_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq9_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr19 {
	struct {
		uint32_t prbs_offsetr_dq13_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq12_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr20 {
	struct {
		uint32_t prbs_offsetr_dq16_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq15_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr21 {
	struct {
		uint32_t prbs_offsetr_dq19_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq18_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr22 {
	struct {
		uint32_t prbs_offsetr_dq22_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq21_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr23 {
	struct {
		uint32_t prbs_offsetr_dq25_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq24_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr24 {
	struct {
		uint32_t prbs_offsetr_dq28_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq27_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetr25 {
	struct {
		uint32_t prbs_offsetr_dq31_dword1:10; /* [9:0] */
		uint32_t prbs_offsetr_dq30_dword1:10; /* [19:10] */
		uint32_t prbs_offsetr_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw0 {
	struct {
		uint32_t prbs_offsetw_par_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_ecc1_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw1 {
	struct {
		uint32_t prbs_offsetw_dbi2_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dbi1_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw2 {
	struct {
		uint32_t prbs_offsetw_dq1_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq0_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw3 {
	struct {
		uint32_t prbs_offsetw_dq4_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq3_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw4 {
	struct {
		uint32_t prbs_offsetw_dq7_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq6_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw5 {
	struct {
		uint32_t prbs_offsetw_dq10_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq9_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw6 {
	struct {
		uint32_t prbs_offsetw_dq13_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq12_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw7 {
	struct {
		uint32_t prbs_offsetw_dq16_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq15_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw8 {
	struct {
		uint32_t prbs_offsetw_dq19_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq18_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw9 {
	struct {
		uint32_t prbs_offsetw_dq22_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq21_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw10 {
	struct {
		uint32_t prbs_offsetw_dq25_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq24_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw11 {
	struct {
		uint32_t prbs_offsetw_dq28_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq27_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw12 {
	struct {
		uint32_t prbs_offsetw_dq31_dword0:10; /* [9:0] */
		uint32_t prbs_offsetw_dq30_dword0:10; /* [19:10] */
		uint32_t prbs_offsetw_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw13 {
	struct {
		uint32_t prbs_offsetw_par_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_ecc1_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw14 {
	struct {
		uint32_t prbs_offsetw_dbi2_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dbi1_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw15 {
	struct {
		uint32_t prbs_offsetw_dq1_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq0_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw16 {
	struct {
		uint32_t prbs_offsetw_dq4_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq3_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw17 {
	struct {
		uint32_t prbs_offsetw_dq7_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq6_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw18 {
	struct {
		uint32_t prbs_offsetw_dq10_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq9_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw19 {
	struct {
		uint32_t prbs_offsetw_dq13_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq12_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw20 {
	struct {
		uint32_t prbs_offsetw_dq16_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq15_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw21 {
	struct {
		uint32_t prbs_offsetw_dq19_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq18_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw22 {
	struct {
		uint32_t prbs_offsetw_dq22_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq21_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw23 {
	struct {
		uint32_t prbs_offsetw_dq25_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq24_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw24 {
	struct {
		uint32_t prbs_offsetw_dq28_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq27_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_offsetw25 {
	struct {
		uint32_t prbs_offsetw_dq31_dword1:10; /* [9:0] */
		uint32_t prbs_offsetw_dq30_dword1:10; /* [19:10] */
		uint32_t prbs_offsetw_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr0 {
	struct {
		uint32_t sw_prbs_offsetr_par_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_ecc1_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr1 {
	struct {
		uint32_t sw_prbs_offsetr_dbi2_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dbi1_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr2 {
	struct {
		uint32_t sw_prbs_offsetr_dq1_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq0_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr3 {
	struct {
		uint32_t sw_prbs_offsetr_dq4_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq3_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr4 {
	struct {
		uint32_t sw_prbs_offsetr_dq7_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq6_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr5 {
	struct {
		uint32_t sw_prbs_offsetr_dq10_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq9_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr6 {
	struct {
		uint32_t sw_prbs_offsetr_dq13_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq12_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr7 {
	struct {
		uint32_t sw_prbs_offsetr_dq16_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq15_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr8 {
	struct {
		uint32_t sw_prbs_offsetr_dq19_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq18_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr9 {
	struct {
		uint32_t sw_prbs_offsetr_dq22_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq21_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr10 {
	struct {
		uint32_t sw_prbs_offsetr_dq25_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq24_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr11 {
	struct {
		uint32_t sw_prbs_offsetr_dq28_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq27_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr12 {
	struct {
		uint32_t sw_prbs_offsetr_dq31_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq30_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr13 {
	struct {
		uint32_t sw_prbs_offsetr_par_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_ecc1_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr14 {
	struct {
		uint32_t sw_prbs_offsetr_dbi2_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dbi1_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr15 {
	struct {
		uint32_t sw_prbs_offsetr_dq1_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq0_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr16 {
	struct {
		uint32_t sw_prbs_offsetr_dq4_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq3_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr17 {
	struct {
		uint32_t sw_prbs_offsetr_dq7_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq6_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr18 {
	struct {
		uint32_t sw_prbs_offsetr_dq10_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq9_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr19 {
	struct {
		uint32_t sw_prbs_offsetr_dq13_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq12_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr20 {
	struct {
		uint32_t sw_prbs_offsetr_dq16_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq15_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr21 {
	struct {
		uint32_t sw_prbs_offsetr_dq19_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq18_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr22 {
	struct {
		uint32_t sw_prbs_offsetr_dq22_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq21_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr23 {
	struct {
		uint32_t sw_prbs_offsetr_dq25_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq24_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr24 {
	struct {
		uint32_t sw_prbs_offsetr_dq28_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq27_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetr25 {
	struct {
		uint32_t sw_prbs_offsetr_dq31_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetr_dq30_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetr_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw0 {
	struct {
		uint32_t sw_prbs_offsetw_par_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_ecc1_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw1 {
	struct {
		uint32_t sw_prbs_offsetw_dbi2_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dbi1_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw2 {
	struct {
		uint32_t sw_prbs_offsetw_dq1_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq0_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw3 {
	struct {
		uint32_t sw_prbs_offsetw_dq4_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq3_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw4 {
	struct {
		uint32_t sw_prbs_offsetw_dq7_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq6_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw5 {
	struct {
		uint32_t sw_prbs_offsetw_dq10_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq9_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw6 {
	struct {
		uint32_t sw_prbs_offsetw_dq13_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq12_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw7 {
	struct {
		uint32_t sw_prbs_offsetw_dq16_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq15_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw8 {
	struct {
		uint32_t sw_prbs_offsetw_dq19_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq18_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw9 {
	struct {
		uint32_t sw_prbs_offsetw_dq22_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq21_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw10 {
	struct {
		uint32_t sw_prbs_offsetw_dq25_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq24_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw11 {
	struct {
		uint32_t sw_prbs_offsetw_dq28_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq27_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw12 {
	struct {
		uint32_t sw_prbs_offsetw_dq31_dword0:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq30_dword0:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw13 {
	struct {
		uint32_t sw_prbs_offsetw_par_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_ecc1_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw14 {
	struct {
		uint32_t sw_prbs_offsetw_dbi2_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dbi1_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw15 {
	struct {
		uint32_t sw_prbs_offsetw_dq1_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq0_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw16 {
	struct {
		uint32_t sw_prbs_offsetw_dq4_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq3_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw17 {
	struct {
		uint32_t sw_prbs_offsetw_dq7_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq6_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw18 {
	struct {
		uint32_t sw_prbs_offsetw_dq10_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq9_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw19 {
	struct {
		uint32_t sw_prbs_offsetw_dq13_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq12_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw20 {
	struct {
		uint32_t sw_prbs_offsetw_dq16_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq15_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw21 {
	struct {
		uint32_t sw_prbs_offsetw_dq19_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq18_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw22 {
	struct {
		uint32_t sw_prbs_offsetw_dq22_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq21_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw23 {
	struct {
		uint32_t sw_prbs_offsetw_dq25_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq24_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw24 {
	struct {
		uint32_t sw_prbs_offsetw_dq28_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq27_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_sw_prbs_offsetw25 {
	struct {
		uint32_t sw_prbs_offsetw_dq31_dword1:10; /* [9:0] */
		uint32_t sw_prbs_offsetw_dq30_dword1:10; /* [19:10] */
		uint32_t sw_prbs_offsetw_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin0 {
	struct {
		uint32_t prbs_offset_left_par_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_ecc1_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin1 {
	struct {
		uint32_t prbs_offset_left_dbi2_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dbi1_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin2 {
	struct {
		uint32_t prbs_offset_left_dq1_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq0_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin3 {
	struct {
		uint32_t prbs_offset_left_dq4_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq3_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin4 {
	struct {
		uint32_t prbs_offset_left_dq7_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq6_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin5 {
	struct {
		uint32_t prbs_offset_left_dq10_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq9_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin6 {
	struct {
		uint32_t prbs_offset_left_dq13_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq12_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin7 {
	struct {
		uint32_t prbs_offset_left_dq16_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq15_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin8 {
	struct {
		uint32_t prbs_offset_left_dq19_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq18_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin9 {
	struct {
		uint32_t prbs_offset_left_dq22_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq21_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin10 {
	struct {
		uint32_t prbs_offset_left_dq25_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq24_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin11 {
	struct {
		uint32_t prbs_offset_left_dq28_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq27_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin12 {
	struct {
		uint32_t prbs_offset_left_dq31_dword0:10; /* [9:0] */
		uint32_t prbs_offset_left_dq30_dword0:10; /* [19:10] */
		uint32_t prbs_offset_left_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin13 {
	struct {
		uint32_t prbs_offset_left_par_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_ecc1_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin14 {
	struct {
		uint32_t prbs_offset_left_dbi2_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dbi1_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin15 {
	struct {
		uint32_t prbs_offset_left_dq1_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq0_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin16 {
	struct {
		uint32_t prbs_offset_left_dq4_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq3_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin17 {
	struct {
		uint32_t prbs_offset_left_dq7_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq6_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin18 {
	struct {
		uint32_t prbs_offset_left_dq10_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq9_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin19 {
	struct {
		uint32_t prbs_offset_left_dq13_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq12_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin20 {
	struct {
		uint32_t prbs_offset_left_dq16_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq15_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin21 {
	struct {
		uint32_t prbs_offset_left_dq19_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq18_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin22 {
	struct {
		uint32_t prbs_offset_left_dq22_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq21_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin23 {
	struct {
		uint32_t prbs_offset_left_dq25_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq24_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin24 {
	struct {
		uint32_t prbs_offset_left_dq28_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq27_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_left_margin25 {
	struct {
		uint32_t prbs_offset_left_dq31_dword1:10; /* [9:0] */
		uint32_t prbs_offset_left_dq30_dword1:10; /* [19:10] */
		uint32_t prbs_offset_left_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin0 {
	struct {
		uint32_t prbs_offset_right_par_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_ecc1_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_ecc0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin1 {
	struct {
		uint32_t prbs_offset_right_dbi2_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dbi1_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dbi0_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin2 {
	struct {
		uint32_t prbs_offset_right_dq1_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq0_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dbi3_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin3 {
	struct {
		uint32_t prbs_offset_right_dq4_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq3_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq2_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin4 {
	struct {
		uint32_t prbs_offset_right_dq7_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq6_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq5_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin5 {
	struct {
		uint32_t prbs_offset_right_dq10_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq9_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq8_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin6 {
	struct {
		uint32_t prbs_offset_right_dq13_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq12_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq11_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin7 {
	struct {
		uint32_t prbs_offset_right_dq16_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq15_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq14_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin8 {
	struct {
		uint32_t prbs_offset_right_dq19_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq18_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq17_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin9 {
	struct {
		uint32_t prbs_offset_right_dq22_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq21_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq20_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin10 {
	struct {
		uint32_t prbs_offset_right_dq25_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq24_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq23_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin11 {
	struct {
		uint32_t prbs_offset_right_dq28_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq27_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq26_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin12 {
	struct {
		uint32_t prbs_offset_right_dq31_dword0:10; /* [9:0] */
		uint32_t prbs_offset_right_dq30_dword0:10; /* [19:10] */
		uint32_t prbs_offset_right_dq29_dword0:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin13 {
	struct {
		uint32_t prbs_offset_right_par_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_ecc1_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_ecc0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin14 {
	struct {
		uint32_t prbs_offset_right_dbi2_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dbi1_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dbi0_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin15 {
	struct {
		uint32_t prbs_offset_right_dq1_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq0_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dbi3_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin16 {
	struct {
		uint32_t prbs_offset_right_dq4_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq3_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq2_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin17 {
	struct {
		uint32_t prbs_offset_right_dq7_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq6_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq5_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin18 {
	struct {
		uint32_t prbs_offset_right_dq10_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq9_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq8_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin19 {
	struct {
		uint32_t prbs_offset_right_dq13_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq12_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq11_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin20 {
	struct {
		uint32_t prbs_offset_right_dq16_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq15_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq14_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin21 {
	struct {
		uint32_t prbs_offset_right_dq19_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq18_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq17_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin22 {
	struct {
		uint32_t prbs_offset_right_dq22_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq21_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq20_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin23 {
	struct {
		uint32_t prbs_offset_right_dq25_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq24_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq23_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin24 {
	struct {
		uint32_t prbs_offset_right_dq28_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq27_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq26_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_prbs_right_margin25 {
	struct {
		uint32_t prbs_offset_right_dq31_dword1:10; /* [9:0] */
		uint32_t prbs_offset_right_dq30_dword1:10; /* [19:10] */
		uint32_t prbs_offset_right_dq29_dword1:10; /* [29:20] */
		uint32_t reserved0:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con0 {
	struct {
		uint32_t seed0_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con1 {
	struct {
		uint32_t seed1_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con2 {
	struct {
		uint32_t seed2_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con3 {
	struct {
		uint32_t seed3_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con4 {
	struct {
		uint32_t seed4_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con5 {
	struct {
		uint32_t seed5_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con6 {
	struct {
		uint32_t seed6_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con7 {
	struct {
		uint32_t seed7_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con8 {
	struct {
		uint32_t seed8_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_cal_seed_con9 {
	struct {
		uint32_t seed9_apb; /* [31:0] */
	};
	uint32_t val;
};

union hbm3ephy_dcm_con0 {
	struct {
		uint32_t dca_code_pc0:4; /* [3:0] */
		uint32_t dca_code_pc1:4; /* [7:4] */
		uint32_t dcm_fail_pc0:1; /* [8:8] */
		uint32_t dcm_fail_pc1:1; /* [9:9] */
		uint32_t dcm_fsm_status:4; /* [13:10] */
		uint32_t dcm_cg_off:1; /* [14:14] */
		uint32_t dcm_direction:1; /* [15:15] */
		uint32_t tdcmm_offset:11; /* [26:16] */
		uint32_t twait_offset:3; /* [29:27] */
		uint32_t dcm_start:1; /* [30:30] */
		uint32_t phy_dcm_en:1; /* [31:31] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq0_deskewl_code0 {
	struct {
		uint32_t wrdq0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq1_deskewl_code0 {
	struct {
		uint32_t wrdq1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq2_deskewl_code0 {
	struct {
		uint32_t wrdq2deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq2deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq3_deskewl_code0 {
	struct {
		uint32_t wrdq3deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq3deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq4_deskewl_code0 {
	struct {
		uint32_t wrdq4deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq4deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq5_deskewl_code0 {
	struct {
		uint32_t wrdq5deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq5deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq6_deskewl_code0 {
	struct {
		uint32_t wrdq6deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq6deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq7_deskewl_code0 {
	struct {
		uint32_t wrdq7deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq7deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq8_deskewl_code0 {
	struct {
		uint32_t wrdq8deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq8deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq9_deskewl_code0 {
	struct {
		uint32_t wrdq9deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq9deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq10_deskewl_code0 {
	struct {
		uint32_t wrdq10deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq10deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq11_deskewl_code0 {
	struct {
		uint32_t wrdq11deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq11deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq12_deskewl_code0 {
	struct {
		uint32_t wrdq12deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq12deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq13_deskewl_code0 {
	struct {
		uint32_t wrdq13deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq13deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq14_deskewl_code0 {
	struct {
		uint32_t wrdq14deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq14deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq15_deskewl_code0 {
	struct {
		uint32_t wrdq15deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq15deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq16_deskewl_code0 {
	struct {
		uint32_t wrdq16deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq16deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq17_deskewl_code0 {
	struct {
		uint32_t wrdq17deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq17deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq18_deskewl_code0 {
	struct {
		uint32_t wrdq18deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq18deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq19_deskewl_code0 {
	struct {
		uint32_t wrdq19deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq19deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq20_deskewl_code0 {
	struct {
		uint32_t wrdq20deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq20deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq21_deskewl_code0 {
	struct {
		uint32_t wrdq21deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq21deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq22_deskewl_code0 {
	struct {
		uint32_t wrdq22deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq22deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq23_deskewl_code0 {
	struct {
		uint32_t wrdq23deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq23deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq24_deskewl_code0 {
	struct {
		uint32_t wrdq24deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq24deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq25_deskewl_code0 {
	struct {
		uint32_t wrdq25deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq25deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq26_deskewl_code0 {
	struct {
		uint32_t wrdq26deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq26deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq27_deskewl_code0 {
	struct {
		uint32_t wrdq27deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq27deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq28_deskewl_code0 {
	struct {
		uint32_t wrdq28deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq28deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq29_deskewl_code0 {
	struct {
		uint32_t wrdq29deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq29deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq30_deskewl_code0 {
	struct {
		uint32_t wrdq30deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq30deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dq31_deskewl_code0 {
	struct {
		uint32_t wrdq31deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdq31deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_ecc0_deskewl_code0 {
	struct {
		uint32_t wrecc0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_ecc1_deskewl_code0 {
	struct {
		uint32_t wrecc1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrecc1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_sev0_deskewl_code0 {
	struct {
		uint32_t wrsev0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_sev1_deskewl_code0 {
	struct {
		uint32_t wrsev1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrsev1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi0_deskewl_code0 {
	struct {
		uint32_t wrdbi0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi1_deskewl_code0 {
	struct {
		uint32_t wrdbi1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi2_deskewl_code0 {
	struct {
		uint32_t wrdbi2deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi2deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_dbi3_deskewl_code0 {
	struct {
		uint32_t wrdbi3deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrdbi3deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_wr_par_deskewl_code0 {
	struct {
		uint32_t wrpardeskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t wrpardeskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq0_deskewl_code0 {
	struct {
		uint32_t sw_wrdq0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq1_deskewl_code0 {
	struct {
		uint32_t sw_wrdq1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq2_deskewl_code0 {
	struct {
		uint32_t sw_wrdq2deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq2deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq3_deskewl_code0 {
	struct {
		uint32_t sw_wrdq3deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq3deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq4_deskewl_code0 {
	struct {
		uint32_t sw_wrdq4deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq4deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq5_deskewl_code0 {
	struct {
		uint32_t sw_wrdq5deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq5deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq6_deskewl_code0 {
	struct {
		uint32_t sw_wrdq6deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq6deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq7_deskewl_code0 {
	struct {
		uint32_t sw_wrdq7deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq7deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq8_deskewl_code0 {
	struct {
		uint32_t sw_wrdq8deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq8deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq9_deskewl_code0 {
	struct {
		uint32_t sw_wrdq9deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq9deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq10_deskewl_code0 {
	struct {
		uint32_t sw_wrdq10deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq10deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq11_deskewl_code0 {
	struct {
		uint32_t sw_wrdq11deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq11deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq12_deskewl_code0 {
	struct {
		uint32_t sw_wrdq12deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq12deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq13_deskewl_code0 {
	struct {
		uint32_t sw_wrdq13deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq13deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq14_deskewl_code0 {
	struct {
		uint32_t sw_wrdq14deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq14deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq15_deskewl_code0 {
	struct {
		uint32_t sw_wrdq15deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq15deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq16_deskewl_code0 {
	struct {
		uint32_t sw_wrdq16deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq16deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq17_deskewl_code0 {
	struct {
		uint32_t sw_wrdq17deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq17deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq18_deskewl_code0 {
	struct {
		uint32_t sw_wrdq18deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq18deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq19_deskewl_code0 {
	struct {
		uint32_t sw_wrdq19deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq19deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq20_deskewl_code0 {
	struct {
		uint32_t sw_wrdq20deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq20deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq21_deskewl_code0 {
	struct {
		uint32_t sw_wrdq21deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq21deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq22_deskewl_code0 {
	struct {
		uint32_t sw_wrdq22deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq22deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq23_deskewl_code0 {
	struct {
		uint32_t sw_wrdq23deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq23deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq24_deskewl_code0 {
	struct {
		uint32_t sw_wrdq24deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq24deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq25_deskewl_code0 {
	struct {
		uint32_t sw_wrdq25deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq25deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq26_deskewl_code0 {
	struct {
		uint32_t sw_wrdq26deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq26deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq27_deskewl_code0 {
	struct {
		uint32_t sw_wrdq27deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq27deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq28_deskewl_code0 {
	struct {
		uint32_t sw_wrdq28deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq28deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq29_deskewl_code0 {
	struct {
		uint32_t sw_wrdq29deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq29deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq30_deskewl_code0 {
	struct {
		uint32_t sw_wrdq30deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq30deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dq31_deskewl_code0 {
	struct {
		uint32_t sw_wrdq31deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdq31deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_ecc0_deskewl_code0 {
	struct {
		uint32_t sw_wrecc0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrecc0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_ecc1_deskewl_code0 {
	struct {
		uint32_t sw_wrecc1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrecc1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_sev0_deskewl_code0 {
	struct {
		uint32_t sw_wrsev0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrsev0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_sev1_deskewl_code0 {
	struct {
		uint32_t sw_wrsev1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrsev1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi0_deskewl_code0 {
	struct {
		uint32_t sw_wrdbi0deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi0deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi1_deskewl_code0 {
	struct {
		uint32_t sw_wrdbi1deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi1deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi2_deskewl_code0 {
	struct {
		uint32_t sw_wrdbi2deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi2deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_dbi3_deskewl_code0 {
	struct {
		uint32_t sw_wrdbi3deskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrdbi3deskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_wr_par_deskewl_code0 {
	struct {
		uint32_t sw_wrpardeskewl0:9; /* [8:0] */
		uint32_t reserved1:7; /* [15:9] */
		uint32_t sw_wrpardeskewl1:9; /* [24:16] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union hbm3ephy_sw_dcm_con0 {
	struct {
		uint32_t derr_mon:2; /* [1:0] */
		uint32_t reserved0:26; /* [27:2] */
		uint32_t bypass_derr_in:2; /* [29:28] */
		uint32_t wdqs_gen:2; /* [31:30] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq0_deskewr_code0 {
	struct {
		uint32_t rddq0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq1_deskewr_code0 {
	struct {
		uint32_t rddq1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq2_deskewr_code0 {
	struct {
		uint32_t rddq2deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq2deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq3_deskewr_code0 {
	struct {
		uint32_t rddq3deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq3deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq4_deskewr_code0 {
	struct {
		uint32_t rddq4deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq4deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq5_deskewr_code0 {
	struct {
		uint32_t rddq5deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq5deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq6_deskewr_code0 {
	struct {
		uint32_t rddq6deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq6deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq7_deskewr_code0 {
	struct {
		uint32_t rddq7deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq7deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq8_deskewr_code0 {
	struct {
		uint32_t rddq8deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq8deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq9_deskewr_code0 {
	struct {
		uint32_t rddq9deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq9deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq10_deskewr_code0 {
	struct {
		uint32_t rddq10deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq10deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq11_deskewr_code0 {
	struct {
		uint32_t rddq11deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq11deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq12_deskewr_code0 {
	struct {
		uint32_t rddq12deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq12deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq13_deskewr_code0 {
	struct {
		uint32_t rddq13deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq13deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq14_deskewr_code0 {
	struct {
		uint32_t rddq14deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq14deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq15_deskewr_code0 {
	struct {
		uint32_t rddq15deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq15deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq16_deskewr_code0 {
	struct {
		uint32_t rddq16deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq16deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq17_deskewr_code0 {
	struct {
		uint32_t rddq17deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq17deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq18_deskewr_code0 {
	struct {
		uint32_t rddq18deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq18deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq19_deskewr_code0 {
	struct {
		uint32_t rddq19deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq19deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq20_deskewr_code0 {
	struct {
		uint32_t rddq20deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq20deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq21_deskewr_code0 {
	struct {
		uint32_t rddq21deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq21deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq22_deskewr_code0 {
	struct {
		uint32_t rddq22deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq22deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq23_deskewr_code0 {
	struct {
		uint32_t rddq23deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq23deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq24_deskewr_code0 {
	struct {
		uint32_t rddq24deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq24deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq25_deskewr_code0 {
	struct {
		uint32_t rddq25deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq25deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq26_deskewr_code0 {
	struct {
		uint32_t rddq26deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq26deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq27_deskewr_code0 {
	struct {
		uint32_t rddq27deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq27deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq28_deskewr_code0 {
	struct {
		uint32_t rddq28deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq28deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq29_deskewr_code0 {
	struct {
		uint32_t rddq29deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq29deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq30_deskewr_code0 {
	struct {
		uint32_t rddq30deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq30deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dq31_deskewr_code0 {
	struct {
		uint32_t rddq31deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddq31deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_ecc0_deskewr_code0 {
	struct {
		uint32_t rdecc0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdecc0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_ecc1_deskewr_code0 {
	struct {
		uint32_t rdecc1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdecc1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_sev0_deskewr_code0 {
	struct {
		uint32_t rdsev0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdsev0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_sev1_deskewr_code0 {
	struct {
		uint32_t rdsev1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdsev1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi0_deskewr_code0 {
	struct {
		uint32_t rddbi0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi1_deskewr_code0 {
	struct {
		uint32_t rddbi1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi2_deskewr_code0 {
	struct {
		uint32_t rddbi2deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi2deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_dbi3_deskewr_code0 {
	struct {
		uint32_t rddbi3deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rddbi3deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_rd_par_deskewr_code0 {
	struct {
		uint32_t rdpardeskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t rdpardeskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq0_deskewr_code0 {
	struct {
		uint32_t sw_rddq0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq1_deskewr_code0 {
	struct {
		uint32_t sw_rddq1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq2_deskewr_code0 {
	struct {
		uint32_t sw_rddq2deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq2deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq3_deskewr_code0 {
	struct {
		uint32_t sw_rddq3deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq3deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq4_deskewr_code0 {
	struct {
		uint32_t sw_rddq4deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq4deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq5_deskewr_code0 {
	struct {
		uint32_t sw_rddq5deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq5deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq6_deskewr_code0 {
	struct {
		uint32_t sw_rddq6deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq6deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq7_deskewr_code0 {
	struct {
		uint32_t sw_rddq7deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq7deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq8_deskewr_code0 {
	struct {
		uint32_t sw_rddq8deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq8deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq9_deskewr_code0 {
	struct {
		uint32_t sw_rddq9deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq9deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq10_deskewr_code0 {
	struct {
		uint32_t sw_rddq10deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq10deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq11_deskewr_code0 {
	struct {
		uint32_t sw_rddq11deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq11deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq12_deskewr_code0 {
	struct {
		uint32_t sw_rddq12deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq12deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq13_deskewr_code0 {
	struct {
		uint32_t sw_rddq13deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq13deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq14_deskewr_code0 {
	struct {
		uint32_t sw_rddq14deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq14deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq15_deskewr_code0 {
	struct {
		uint32_t sw_rddq15deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq15deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq16_deskewr_code0 {
	struct {
		uint32_t sw_rddq16deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq16deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq17_deskewr_code0 {
	struct {
		uint32_t sw_rddq17deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq17deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq18_deskewr_code0 {
	struct {
		uint32_t sw_rddq18deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq18deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq19_deskewr_code0 {
	struct {
		uint32_t sw_rddq19deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq19deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq20_deskewr_code0 {
	struct {
		uint32_t sw_rddq20deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq20deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq21_deskewr_code0 {
	struct {
		uint32_t sw_rddq21deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq21deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq22_deskewr_code0 {
	struct {
		uint32_t sw_rddq22deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq22deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq23_deskewr_code0 {
	struct {
		uint32_t sw_rddq23deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq23deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq24_deskewr_code0 {
	struct {
		uint32_t sw_rddq24deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq24deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq25_deskewr_code0 {
	struct {
		uint32_t sw_rddq25deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq25deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq26_deskewr_code0 {
	struct {
		uint32_t sw_rddq26deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq26deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq27_deskewr_code0 {
	struct {
		uint32_t sw_rddq27deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq27deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq28_deskewr_code0 {
	struct {
		uint32_t sw_rddq28deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq28deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq29_deskewr_code0 {
	struct {
		uint32_t sw_rddq29deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq29deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq30_deskewr_code0 {
	struct {
		uint32_t sw_rddq30deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq30deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dq31_deskewr_code0 {
	struct {
		uint32_t sw_rddq31deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddq31deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_ecc0_deskewr_code0 {
	struct {
		uint32_t sw_rdecc0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdecc0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_ecc1_deskewr_code0 {
	struct {
		uint32_t sw_rdecc1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdecc1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_sev0_deskewr_code0 {
	struct {
		uint32_t sw_rdsev0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdsev0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_sev1_deskewr_code0 {
	struct {
		uint32_t sw_rdsev1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdsev1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi0_deskewr_code0 {
	struct {
		uint32_t sw_rddbi0deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi0deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi1_deskewr_code0 {
	struct {
		uint32_t sw_rddbi1deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi1deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi2_deskewr_code0 {
	struct {
		uint32_t sw_rddbi2deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi2deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_dbi3_deskewr_code0 {
	struct {
		uint32_t sw_rddbi3deskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rddbi3deskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

union hbm3ephy_sw_rd_par_deskewr_code0 {
	struct {
		uint32_t sw_rdpardeskewr0:10; /* [9:0] */
		uint32_t reserved1:6; /* [15:10] */
		uint32_t sw_rdpardeskewr1:10; /* [25:16] */
		uint32_t reserved0:6; /* [31:26] */
	};
	uint32_t val;
};

struct hbm3ephy {
	union hbm3ephy_gnr_con0 gnr_con0; /* offset : 0x0 */
	union hbm3ephy_cal_con0 cal_con0; /* offset : 0x4 */
	union hbm3ephy_cal_con1 cal_con1; /* offset : 0x8 */
	union hbm3ephy_cal_con2 cal_con2; /* offset : 0xc */
	union hbm3ephy_cal_con3 cal_con3; /* offset : 0x10 */
	union hbm3ephy_cal_con4 cal_con4; /* offset : 0x14 */
	union hbm3ephy_cal_con5 cal_con5; /* offset : 0x18 */
	union hbm3ephy_lock_check_con lock_check_con; /* offset : 0x1c */
	union hbm3ephy_lp_con0 lp_con0; /* offset : 0x20 */
	union hbm3ephy_offsetr_con0 offsetr_con0; /* offset : 0x24 */
	union hbm3ephy_offsetw_con0 offsetw_con0; /* offset : 0x28 */
	union hbm3ephy_offset_dq_con0 offset_dq_con0; /* offset : 0x2c */
	union hbm3ephy_offsetd_con0 offsetd_con0; /* offset : 0x30 */
	union hbm3ephy_dfs_con0 dfs_con0; /* offset : 0x34 */
	union hbm3ephy_dfs_con1 dfs_con1; /* offset : 0x38 */
	union hbm3ephy_par_con par_con; /* offset : 0x3c */
	union hbm3ephy_aword_glitch_con aword_glitch_con; /* offset : 0x40 */
	union hbm3ephy_wr_lvl_con0 wr_lvl_con0; /* offset : 0x44 */
	uint32_t reserved_1;
	union hbm3ephy_wr_lvl_con1 wr_lvl_con1; /* offset : 0x4c */
	union hbm3ephy_wr_lvl_cs0_code0 wr_lvl_cs0_code0; /* offset : 0x50 */
	union hbm3ephy_cmd_deskewc_code0 cmd_deskewc_code0; /* offset : 0x54 */
	union hbm3ephy_cmd_deskewc_code1 cmd_deskewc_code1; /* offset : 0x58 */
	union hbm3ephy_cmd_deskewc_code2 cmd_deskewc_code2; /* offset : 0x5c */
	union hbm3ephy_cmd_deskewc_code3 cmd_deskewc_code3; /* offset : 0x60 */
	union hbm3ephy_cmd_deskewc_code4 cmd_deskewc_code4; /* offset : 0x64 */
	union hbm3ephy_cmd_deskewc_code5 cmd_deskewc_code5; /* offset : 0x68 */
	union hbm3ephy_cmd_deskewc_code6 cmd_deskewc_code6; /* offset : 0x6c */
	union hbm3ephy_cmd_deskewc_code7 cmd_deskewc_code7; /* offset : 0x70 */
	union hbm3ephy_cmd_deskewc_code8 cmd_deskewc_code8; /* offset : 0x74 */
	union hbm3ephy_cmd_deskewc_code9 cmd_deskewc_code9; /* offset : 0x78 */
	union hbm3ephy_cmd_deskewc_code10 cmd_deskewc_code10; /* offset : 0x7c */
	union hbm3ephy_sw_cmd_deskewc_code0 sw_cmd_deskewc_code0; /* offset : 0x80 */
	union hbm3ephy_sw_cmd_deskewc_code1 sw_cmd_deskewc_code1; /* offset : 0x84 */
	union hbm3ephy_sw_cmd_deskewc_code2 sw_cmd_deskewc_code2; /* offset : 0x88 */
	union hbm3ephy_sw_cmd_deskewc_code3 sw_cmd_deskewc_code3; /* offset : 0x8c */
	union hbm3ephy_sw_cmd_deskewc_code4 sw_cmd_deskewc_code4; /* offset : 0x90 */
	union hbm3ephy_sw_cmd_deskewc_code5 sw_cmd_deskewc_code5; /* offset : 0x94 */
	union hbm3ephy_sw_cmd_deskewc_code6 sw_cmd_deskewc_code6; /* offset : 0x98 */
	union hbm3ephy_sw_cmd_deskewc_code7 sw_cmd_deskewc_code7; /* offset : 0x9c */
	union hbm3ephy_sw_cmd_deskewc_code8 sw_cmd_deskewc_code8; /* offset : 0xa0 */
	union hbm3ephy_sw_cmd_deskewc_code9 sw_cmd_deskewc_code9; /* offset : 0xa4 */
	union hbm3ephy_sw_cmd_deskewc_code10 sw_cmd_deskewc_code10; /* offset : 0xa8 */
	union hbm3ephy_mdll_con0 mdll_con0; /* offset : 0xac */
	union hbm3ephy_mdll_con1 mdll_con1; /* offset : 0xb0 */
	union hbm3ephy_dll_update_con0 dll_update_con0; /* offset : 0xb4 */
	union hbm3ephy_dll_update_con1 dll_update_con1; /* offset : 0xb8 */
	uint32_t reserved_2[6];
	union hbm3ephy_remap_con0 remap_con0; /* offset : 0xd4 */
	union hbm3ephy_remap_con1 remap_con1; /* offset : 0xd8 */
	union hbm3ephy_rd_dqs_vwmc_code0 rd_dqs_vwmc_code0; /* offset : 0xdc */
	union hbm3ephy_rd_dq0_deskewc_code0 rd_dq0_deskewc_code0; /* offset : 0xe0 */
	union hbm3ephy_rd_dq1_deskewc_code0 rd_dq1_deskewc_code0; /* offset : 0xe4 */
	union hbm3ephy_rd_dq2_deskewc_code0 rd_dq2_deskewc_code0; /* offset : 0xe8 */
	union hbm3ephy_rd_dq3_deskewc_code0 rd_dq3_deskewc_code0; /* offset : 0xec */
	union hbm3ephy_rd_dq4_deskewc_code0 rd_dq4_deskewc_code0; /* offset : 0xf0 */
	union hbm3ephy_rd_dq5_deskewc_code0 rd_dq5_deskewc_code0; /* offset : 0xf4 */
	union hbm3ephy_rd_dq6_deskewc_code0 rd_dq6_deskewc_code0; /* offset : 0xf8 */
	union hbm3ephy_rd_dq7_deskewc_code0 rd_dq7_deskewc_code0; /* offset : 0xfc */
	union hbm3ephy_rd_dq8_deskewc_code0 rd_dq8_deskewc_code0; /* offset : 0x100 */
	union hbm3ephy_rd_dq9_deskewc_code0 rd_dq9_deskewc_code0; /* offset : 0x104 */
	union hbm3ephy_rd_dq10_deskewc_code0 rd_dq10_deskewc_code0; /* offset : 0x108 */
	union hbm3ephy_rd_dq11_deskewc_code0 rd_dq11_deskewc_code0; /* offset : 0x10c */
	union hbm3ephy_rd_dq12_deskewc_code0 rd_dq12_deskewc_code0; /* offset : 0x110 */
	union hbm3ephy_rd_dq13_deskewc_code0 rd_dq13_deskewc_code0; /* offset : 0x114 */
	union hbm3ephy_rd_dq14_deskewc_code0 rd_dq14_deskewc_code0; /* offset : 0x118 */
	union hbm3ephy_rd_dq15_deskewc_code0 rd_dq15_deskewc_code0; /* offset : 0x11c */
	union hbm3ephy_rd_dq16_deskewc_code0 rd_dq16_deskewc_code0; /* offset : 0x120 */
	union hbm3ephy_rd_dq17_deskewc_code0 rd_dq17_deskewc_code0; /* offset : 0x124 */
	union hbm3ephy_rd_dq18_deskewc_code0 rd_dq18_deskewc_code0; /* offset : 0x128 */
	union hbm3ephy_rd_dq19_deskewc_code0 rd_dq19_deskewc_code0; /* offset : 0x12c */
	union hbm3ephy_rd_dq20_deskewc_code0 rd_dq20_deskewc_code0; /* offset : 0x130 */
	union hbm3ephy_rd_dq21_deskewc_code0 rd_dq21_deskewc_code0; /* offset : 0x134 */
	union hbm3ephy_rd_dq22_deskewc_code0 rd_dq22_deskewc_code0; /* offset : 0x138 */
	union hbm3ephy_rd_dq23_deskewc_code0 rd_dq23_deskewc_code0; /* offset : 0x13c */
	union hbm3ephy_rd_dq24_deskewc_code0 rd_dq24_deskewc_code0; /* offset : 0x140 */
	union hbm3ephy_rd_dq25_deskewc_code0 rd_dq25_deskewc_code0; /* offset : 0x144 */
	union hbm3ephy_rd_dq26_deskewc_code0 rd_dq26_deskewc_code0; /* offset : 0x148 */
	union hbm3ephy_rd_dq27_deskewc_code0 rd_dq27_deskewc_code0; /* offset : 0x14c */
	union hbm3ephy_rd_dq28_deskewc_code0 rd_dq28_deskewc_code0; /* offset : 0x150 */
	union hbm3ephy_rd_dq29_deskewc_code0 rd_dq29_deskewc_code0; /* offset : 0x154 */
	union hbm3ephy_rd_dq30_deskewc_code0 rd_dq30_deskewc_code0; /* offset : 0x158 */
	union hbm3ephy_rd_dq31_deskewc_code0 rd_dq31_deskewc_code0; /* offset : 0x15c */
	union hbm3ephy_rd_ecc0_deskewc_code0 rd_ecc0_deskewc_code0; /* offset : 0x160 */
	union hbm3ephy_rd_ecc1_deskewc_code0 rd_ecc1_deskewc_code0; /* offset : 0x164 */
	union hbm3ephy_rd_sev0_deskewc_code0 rd_sev0_deskewc_code0; /* offset : 0x168 */
	union hbm3ephy_rd_sev1_deskewc_code0 rd_sev1_deskewc_code0; /* offset : 0x16c */
	union hbm3ephy_rd_dbi0_deskewc_code0 rd_dbi0_deskewc_code0; /* offset : 0x170 */
	union hbm3ephy_rd_dbi1_deskewc_code0 rd_dbi1_deskewc_code0; /* offset : 0x174 */
	union hbm3ephy_rd_dbi2_deskewc_code0 rd_dbi2_deskewc_code0; /* offset : 0x178 */
	union hbm3ephy_rd_dbi3_deskewc_code0 rd_dbi3_deskewc_code0; /* offset : 0x17c */
	union hbm3ephy_rd_par_deskewc_code0 rd_par_deskewc_code0; /* offset : 0x180 */
	union hbm3ephy_sw_rd_dqs_vwmc_code0 sw_rd_dqs_vwmc_code0; /* offset : 0x184 */
	union hbm3ephy_sw_rd_dq0_deskewc_code0 sw_rd_dq0_deskewc_code0; /* offset : 0x188 */
	union hbm3ephy_sw_rd_dq1_deskewc_code0 sw_rd_dq1_deskewc_code0; /* offset : 0x18c */
	union hbm3ephy_sw_rd_dq2_deskewc_code0 sw_rd_dq2_deskewc_code0; /* offset : 0x190 */
	union hbm3ephy_sw_rd_dq3_deskewc_code0 sw_rd_dq3_deskewc_code0; /* offset : 0x194 */
	union hbm3ephy_sw_rd_dq4_deskewc_code0 sw_rd_dq4_deskewc_code0; /* offset : 0x198 */
	union hbm3ephy_sw_rd_dq5_deskewc_code0 sw_rd_dq5_deskewc_code0; /* offset : 0x19c */
	union hbm3ephy_sw_rd_dq6_deskewc_code0 sw_rd_dq6_deskewc_code0; /* offset : 0x1a0 */
	union hbm3ephy_sw_rd_dq7_deskewc_code0 sw_rd_dq7_deskewc_code0; /* offset : 0x1a4 */
	union hbm3ephy_sw_rd_dq8_deskewc_code0 sw_rd_dq8_deskewc_code0; /* offset : 0x1a8 */
	union hbm3ephy_sw_rd_dq9_deskewc_code0 sw_rd_dq9_deskewc_code0; /* offset : 0x1ac */
	union hbm3ephy_sw_rd_dq10_deskewc_code0 sw_rd_dq10_deskewc_code0; /* offset : 0x1b0 */
	union hbm3ephy_sw_rd_dq11_deskewc_code0 sw_rd_dq11_deskewc_code0; /* offset : 0x1b4 */
	union hbm3ephy_sw_rd_dq12_deskewc_code0 sw_rd_dq12_deskewc_code0; /* offset : 0x1b8 */
	union hbm3ephy_sw_rd_dq13_deskewc_code0 sw_rd_dq13_deskewc_code0; /* offset : 0x1bc */
	union hbm3ephy_sw_rd_dq14_deskewc_code0 sw_rd_dq14_deskewc_code0; /* offset : 0x1c0 */
	union hbm3ephy_sw_rd_dq15_deskewc_code0 sw_rd_dq15_deskewc_code0; /* offset : 0x1c4 */
	union hbm3ephy_sw_rd_dq16_deskewc_code0 sw_rd_dq16_deskewc_code0; /* offset : 0x1c8 */
	union hbm3ephy_sw_rd_dq17_deskewc_code0 sw_rd_dq17_deskewc_code0; /* offset : 0x1cc */
	union hbm3ephy_sw_rd_dq18_deskewc_code0 sw_rd_dq18_deskewc_code0; /* offset : 0x1d0 */
	union hbm3ephy_sw_rd_dq19_deskewc_code0 sw_rd_dq19_deskewc_code0; /* offset : 0x1d4 */
	union hbm3ephy_sw_rd_dq20_deskewc_code0 sw_rd_dq20_deskewc_code0; /* offset : 0x1d8 */
	union hbm3ephy_sw_rd_dq21_deskewc_code0 sw_rd_dq21_deskewc_code0; /* offset : 0x1dc */
	union hbm3ephy_sw_rd_dq22_deskewc_code0 sw_rd_dq22_deskewc_code0; /* offset : 0x1e0 */
	union hbm3ephy_sw_rd_dq23_deskewc_code0 sw_rd_dq23_deskewc_code0; /* offset : 0x1e4 */
	union hbm3ephy_sw_rd_dq24_deskewc_code0 sw_rd_dq24_deskewc_code0; /* offset : 0x1e8 */
	union hbm3ephy_sw_rd_dq25_deskewc_code0 sw_rd_dq25_deskewc_code0; /* offset : 0x1ec */
	union hbm3ephy_sw_rd_dq26_deskewc_code0 sw_rd_dq26_deskewc_code0; /* offset : 0x1f0 */
	union hbm3ephy_sw_rd_dq27_deskewc_code0 sw_rd_dq27_deskewc_code0; /* offset : 0x1f4 */
	union hbm3ephy_sw_rd_dq28_deskewc_code0 sw_rd_dq28_deskewc_code0; /* offset : 0x1f8 */
	union hbm3ephy_sw_rd_dq29_deskewc_code0 sw_rd_dq29_deskewc_code0; /* offset : 0x1fc */
	union hbm3ephy_sw_rd_dq30_deskewc_code0 sw_rd_dq30_deskewc_code0; /* offset : 0x200 */
	union hbm3ephy_sw_rd_dq31_deskewc_code0 sw_rd_dq31_deskewc_code0; /* offset : 0x204 */
	union hbm3ephy_sw_rd_ecc0_deskewc_code0 sw_rd_ecc0_deskewc_code0; /* offset : 0x208 */
	union hbm3ephy_sw_rd_ecc1_deskewc_code0 sw_rd_ecc1_deskewc_code0; /* offset : 0x20c */
	union hbm3ephy_sw_rd_sev0_deskewc_code0 sw_rd_sev0_deskewc_code0; /* offset : 0x210 */
	union hbm3ephy_sw_rd_sev1_deskewc_code0 sw_rd_sev1_deskewc_code0; /* offset : 0x214 */
	union hbm3ephy_sw_rd_dbi0_deskewc_code0 sw_rd_dbi0_deskewc_code0; /* offset : 0x218 */
	union hbm3ephy_sw_rd_dbi1_deskewc_code0 sw_rd_dbi1_deskewc_code0; /* offset : 0x21c */
	union hbm3ephy_sw_rd_dbi2_deskewc_code0 sw_rd_dbi2_deskewc_code0; /* offset : 0x220 */
	union hbm3ephy_sw_rd_dbi3_deskewc_code0 sw_rd_dbi3_deskewc_code0; /* offset : 0x224 */
	union hbm3ephy_sw_rd_par_deskewc_code0 sw_rd_par_deskewc_code0; /* offset : 0x228 */
	union hbm3ephy_wr_dq0_deskewc_code0 wr_dq0_deskewc_code0; /* offset : 0x22c */
	union hbm3ephy_wr_dq1_deskewc_code0 wr_dq1_deskewc_code0; /* offset : 0x230 */
	union hbm3ephy_wr_dq2_deskewc_code0 wr_dq2_deskewc_code0; /* offset : 0x234 */
	union hbm3ephy_wr_dq3_deskewc_code0 wr_dq3_deskewc_code0; /* offset : 0x238 */
	union hbm3ephy_wr_dq4_deskewc_code0 wr_dq4_deskewc_code0; /* offset : 0x23c */
	union hbm3ephy_wr_dq5_deskewc_code0 wr_dq5_deskewc_code0; /* offset : 0x240 */
	union hbm3ephy_wr_dq6_deskewc_code0 wr_dq6_deskewc_code0; /* offset : 0x244 */
	union hbm3ephy_wr_dq7_deskewc_code0 wr_dq7_deskewc_code0; /* offset : 0x248 */
	union hbm3ephy_wr_dq8_deskewc_code0 wr_dq8_deskewc_code0; /* offset : 0x24c */
	union hbm3ephy_wr_dq9_deskewc_code0 wr_dq9_deskewc_code0; /* offset : 0x250 */
	union hbm3ephy_wr_dq10_deskewc_code0 wr_dq10_deskewc_code0; /* offset : 0x254 */
	union hbm3ephy_wr_dq11_deskewc_code0 wr_dq11_deskewc_code0; /* offset : 0x258 */
	union hbm3ephy_wr_dq12_deskewc_code0 wr_dq12_deskewc_code0; /* offset : 0x25c */
	union hbm3ephy_wr_dq13_deskewc_code0 wr_dq13_deskewc_code0; /* offset : 0x260 */
	union hbm3ephy_wr_dq14_deskewc_code0 wr_dq14_deskewc_code0; /* offset : 0x264 */
	union hbm3ephy_wr_dq15_deskewc_code0 wr_dq15_deskewc_code0; /* offset : 0x268 */
	union hbm3ephy_wr_dq16_deskewc_code0 wr_dq16_deskewc_code0; /* offset : 0x26c */
	union hbm3ephy_wr_dq17_deskewc_code0 wr_dq17_deskewc_code0; /* offset : 0x270 */
	union hbm3ephy_wr_dq18_deskewc_code0 wr_dq18_deskewc_code0; /* offset : 0x274 */
	union hbm3ephy_wr_dq19_deskewc_code0 wr_dq19_deskewc_code0; /* offset : 0x278 */
	union hbm3ephy_wr_dq20_deskewc_code0 wr_dq20_deskewc_code0; /* offset : 0x27c */
	union hbm3ephy_wr_dq21_deskewc_code0 wr_dq21_deskewc_code0; /* offset : 0x280 */
	union hbm3ephy_wr_dq22_deskewc_code0 wr_dq22_deskewc_code0; /* offset : 0x284 */
	union hbm3ephy_wr_dq23_deskewc_code0 wr_dq23_deskewc_code0; /* offset : 0x288 */
	union hbm3ephy_wr_dq24_deskewc_code0 wr_dq24_deskewc_code0; /* offset : 0x28c */
	union hbm3ephy_wr_dq25_deskewc_code0 wr_dq25_deskewc_code0; /* offset : 0x290 */
	union hbm3ephy_wr_dq26_deskewc_code0 wr_dq26_deskewc_code0; /* offset : 0x294 */
	union hbm3ephy_wr_dq27_deskewc_code0 wr_dq27_deskewc_code0; /* offset : 0x298 */
	union hbm3ephy_wr_dq28_deskewc_code0 wr_dq28_deskewc_code0; /* offset : 0x29c */
	union hbm3ephy_wr_dq29_deskewc_code0 wr_dq29_deskewc_code0; /* offset : 0x2a0 */
	union hbm3ephy_wr_dq30_deskewc_code0 wr_dq30_deskewc_code0; /* offset : 0x2a4 */
	union hbm3ephy_wr_dq31_deskewc_code0 wr_dq31_deskewc_code0; /* offset : 0x2a8 */
	union hbm3ephy_wr_ecc0_deskewc_code0 wr_ecc0_deskewc_code0; /* offset : 0x2ac */
	union hbm3ephy_wr_ecc1_deskewc_code0 wr_ecc1_deskewc_code0; /* offset : 0x2b0 */
	union hbm3ephy_wr_sev0_deskewc_code0 wr_sev0_deskewc_code0; /* offset : 0x2b4 */
	union hbm3ephy_wr_sev1_deskewc_code0 wr_sev1_deskewc_code0; /* offset : 0x2b8 */
	union hbm3ephy_wr_dbi0_deskewc_code0 wr_dbi0_deskewc_code0; /* offset : 0x2bc */
	union hbm3ephy_wr_dbi1_deskewc_code0 wr_dbi1_deskewc_code0; /* offset : 0x2c0 */
	union hbm3ephy_wr_dbi2_deskewc_code0 wr_dbi2_deskewc_code0; /* offset : 0x2c4 */
	union hbm3ephy_wr_dbi3_deskewc_code0 wr_dbi3_deskewc_code0; /* offset : 0x2c8 */
	union hbm3ephy_wr_par_deskewc_code0 wr_par_deskewc_code0; /* offset : 0x2cc */
	union hbm3ephy_sw_wr_dq0_deskewc_code0 sw_wr_dq0_deskewc_code0; /* offset : 0x2d0 */
	union hbm3ephy_sw_wr_dq1_deskewc_code0 sw_wr_dq1_deskewc_code0; /* offset : 0x2d4 */
	union hbm3ephy_sw_wr_dq2_deskewc_code0 sw_wr_dq2_deskewc_code0; /* offset : 0x2d8 */
	union hbm3ephy_sw_wr_dq3_deskewc_code0 sw_wr_dq3_deskewc_code0; /* offset : 0x2dc */
	union hbm3ephy_sw_wr_dq4_deskewc_code0 sw_wr_dq4_deskewc_code0; /* offset : 0x2e0 */
	union hbm3ephy_sw_wr_dq5_deskewc_code0 sw_wr_dq5_deskewc_code0; /* offset : 0x2e4 */
	union hbm3ephy_sw_wr_dq6_deskewc_code0 sw_wr_dq6_deskewc_code0; /* offset : 0x2e8 */
	union hbm3ephy_sw_wr_dq7_deskewc_code0 sw_wr_dq7_deskewc_code0; /* offset : 0x2ec */
	union hbm3ephy_sw_wr_dq8_deskewc_code0 sw_wr_dq8_deskewc_code0; /* offset : 0x2f0 */
	union hbm3ephy_sw_wr_dq9_deskewc_code0 sw_wr_dq9_deskewc_code0; /* offset : 0x2f4 */
	union hbm3ephy_sw_wr_dq10_deskewc_code0 sw_wr_dq10_deskewc_code0; /* offset : 0x2f8 */
	union hbm3ephy_sw_wr_dq11_deskewc_code0 sw_wr_dq11_deskewc_code0; /* offset : 0x2fc */
	union hbm3ephy_sw_wr_dq12_deskewc_code0 sw_wr_dq12_deskewc_code0; /* offset : 0x300 */
	union hbm3ephy_sw_wr_dq13_deskewc_code0 sw_wr_dq13_deskewc_code0; /* offset : 0x304 */
	union hbm3ephy_sw_wr_dq14_deskewc_code0 sw_wr_dq14_deskewc_code0; /* offset : 0x308 */
	union hbm3ephy_sw_wr_dq15_deskewc_code0 sw_wr_dq15_deskewc_code0; /* offset : 0x30c */
	union hbm3ephy_sw_wr_dq16_deskewc_code0 sw_wr_dq16_deskewc_code0; /* offset : 0x310 */
	union hbm3ephy_sw_wr_dq17_deskewc_code0 sw_wr_dq17_deskewc_code0; /* offset : 0x314 */
	union hbm3ephy_sw_wr_dq18_deskewc_code0 sw_wr_dq18_deskewc_code0; /* offset : 0x318 */
	union hbm3ephy_sw_wr_dq19_deskewc_code0 sw_wr_dq19_deskewc_code0; /* offset : 0x31c */
	union hbm3ephy_sw_wr_dq20_deskewc_code0 sw_wr_dq20_deskewc_code0; /* offset : 0x320 */
	union hbm3ephy_sw_wr_dq21_deskewc_code0 sw_wr_dq21_deskewc_code0; /* offset : 0x324 */
	union hbm3ephy_sw_wr_dq22_deskewc_code0 sw_wr_dq22_deskewc_code0; /* offset : 0x328 */
	union hbm3ephy_sw_wr_dq23_deskewc_code0 sw_wr_dq23_deskewc_code0; /* offset : 0x32c */
	union hbm3ephy_sw_wr_dq24_deskewc_code0 sw_wr_dq24_deskewc_code0; /* offset : 0x330 */
	union hbm3ephy_sw_wr_dq25_deskewc_code0 sw_wr_dq25_deskewc_code0; /* offset : 0x334 */
	union hbm3ephy_sw_wr_dq26_deskewc_code0 sw_wr_dq26_deskewc_code0; /* offset : 0x338 */
	union hbm3ephy_sw_wr_dq27_deskewc_code0 sw_wr_dq27_deskewc_code0; /* offset : 0x33c */
	union hbm3ephy_sw_wr_dq28_deskewc_code0 sw_wr_dq28_deskewc_code0; /* offset : 0x340 */
	union hbm3ephy_sw_wr_dq29_deskewc_code0 sw_wr_dq29_deskewc_code0; /* offset : 0x344 */
	union hbm3ephy_sw_wr_dq30_deskewc_code0 sw_wr_dq30_deskewc_code0; /* offset : 0x348 */
	union hbm3ephy_sw_wr_dq31_deskewc_code0 sw_wr_dq31_deskewc_code0; /* offset : 0x34c */
	union hbm3ephy_sw_wr_ecc0_deskewc_code0 sw_wr_ecc0_deskewc_code0; /* offset : 0x350 */
	union hbm3ephy_sw_wr_ecc1_deskewc_code0 sw_wr_ecc1_deskewc_code0; /* offset : 0x354 */
	union hbm3ephy_sw_wr_sev0_deskewc_code0 sw_wr_sev0_deskewc_code0; /* offset : 0x358 */
	union hbm3ephy_sw_wr_sev1_deskewc_code0 sw_wr_sev1_deskewc_code0; /* offset : 0x35c */
	union hbm3ephy_sw_wr_dbi0_deskewc_code0 sw_wr_dbi0_deskewc_code0; /* offset : 0x360 */
	union hbm3ephy_sw_wr_dbi1_deskewc_code0 sw_wr_dbi1_deskewc_code0; /* offset : 0x364 */
	union hbm3ephy_sw_wr_dbi2_deskewc_code0 sw_wr_dbi2_deskewc_code0; /* offset : 0x368 */
	union hbm3ephy_sw_wr_dbi3_deskewc_code0 sw_wr_dbi3_deskewc_code0; /* offset : 0x36c */
	union hbm3ephy_sw_wr_par_deskewc_code0 sw_wr_par_deskewc_code0; /* offset : 0x370 */
	union hbm3ephy_dword_select dword_select; /* offset : 0x374 */
	union hbm3ephy_version_info_stat0 version_info_stat0; /* offset : 0x378 */
	uint32_t reserved_3[2];
	union hbm3ephy_auto_dqs_stat0 auto_dqs_stat0; /* offset : 0x384 */
	union hbm3ephy_cacal_con cacal_con; /* offset : 0x388 */
	union hbm3ephy_freq_offset_con freq_offset_con; /* offset : 0x38c */
	union hbm3ephy_prbs_con0 prbs_con0; /* offset : 0x390 */
	union hbm3ephy_prbs_con1 prbs_con1; /* offset : 0x394 */
	union hbm3ephy_prbs_margin0 prbs_margin0; /* offset : 0x398 */
	union hbm3ephy_prbs_fail_read_d0 prbs_fail_read_d0; /* offset : 0x39c */
	union hbm3ephy_prbs_fail_read_d1 prbs_fail_read_d1; /* offset : 0x3a0 */
	union hbm3ephy_prbs_fail_etc prbs_fail_etc; /* offset : 0x3a4 */
	union hbm3ephy_mon_con0 mon_con0; /* offset : 0x3a8 */
	union hbm3ephy_prbs_fail_write_d0 prbs_fail_write_d0; /* offset : 0x3ac */
	union hbm3ephy_prbs_fail_write_d1 prbs_fail_write_d1; /* offset : 0x3b0 */
	union hbm3ephy_cal_debug0 cal_debug0; /* offset : 0x3b4 */
	union hbm3ephy_trn_mon0 trn_mon0; /* offset : 0x3b8 */
	union hbm3ephy_lock_mon0 lock_mon0; /* offset : 0x3bc */
	union hbm3ephy_lock_mon1 lock_mon1; /* offset : 0x3c0 */
	union hbm3ephy_fifo_stat0 fifo_stat0; /* offset : 0x3c4 */
	union hbm3ephy_cal_wr_pattern_con0 cal_wr_pattern_con0; /* offset : 0x3c8 */
	union hbm3ephy_cal_wr_pattern_con1 cal_wr_pattern_con1; /* offset : 0x3cc */
	union hbm3ephy_cal_wr_pattern_con2 cal_wr_pattern_con2; /* offset : 0x3d0 */
	union hbm3ephy_cal_wr_pattern_con3 cal_wr_pattern_con3; /* offset : 0x3d4 */
	union hbm3ephy_cal_wr_pattern_con4 cal_wr_pattern_con4; /* offset : 0x3d8 */
	union hbm3ephy_cal_wr_pattern_con5 cal_wr_pattern_con5; /* offset : 0x3dc */
	union hbm3ephy_cal_wr_pattern_con6 cal_wr_pattern_con6; /* offset : 0x3e0 */
	union hbm3ephy_cal_wr_pattern_con7 cal_wr_pattern_con7; /* offset : 0x3e4 */
	union hbm3ephy_cal_wr_pattern_con8 cal_wr_pattern_con8; /* offset : 0x3e8 */
	union hbm3ephy_cal_wr_pattern_con9 cal_wr_pattern_con9; /* offset : 0x3ec */
	union hbm3ephy_cal_wr_pattern_con10 cal_wr_pattern_con10; /* offset : 0x3f0 */
	union hbm3ephy_cal_wr_pattern_con11 cal_wr_pattern_con11; /* offset : 0x3f4 */
	union hbm3ephy_cal_wr_pattern_con12 cal_wr_pattern_con12; /* offset : 0x3f8 */
	union hbm3ephy_cal_wr_pattern_con13 cal_wr_pattern_con13; /* offset : 0x3fc */
	union hbm3ephy_cal_wr_pattern_con14 cal_wr_pattern_con14; /* offset : 0x400 */
	union hbm3ephy_cal_wr_pattern_con15 cal_wr_pattern_con15; /* offset : 0x404 */
	union hbm3ephy_cal_wr_pattern_con16 cal_wr_pattern_con16; /* offset : 0x408 */
	union hbm3ephy_cal_wr_pattern_con17 cal_wr_pattern_con17; /* offset : 0x40c */
	union hbm3ephy_cal_wr_pattern_con18 cal_wr_pattern_con18; /* offset : 0x410 */
	union hbm3ephy_cal_wr_pattern_con19 cal_wr_pattern_con19; /* offset : 0x414 */
	union hbm3ephy_cal_wr_pattern_con20 cal_wr_pattern_con20; /* offset : 0x418 */
	union hbm3ephy_scheduler_mode scheduler_mode; /* offset : 0x41c */
	union hbm3ephy_direct_cmd_con_0 direct_cmd_con_0; /* offset : 0x420 */
	union hbm3ephy_direct_cmd_con_1 direct_cmd_con_1; /* offset : 0x424 */
	union hbm3ephy_direct_cmd_con_2 direct_cmd_con_2; /* offset : 0x428 */
	union hbm3ephy_direct_cmd_con_3 direct_cmd_con_3; /* offset : 0x42c */
	union hbm3ephy_direct_cmd_con_4 direct_cmd_con_4; /* offset : 0x430 */
	union hbm3ephy_scheduler_con0 scheduler_con0; /* offset : 0x434 */
	union hbm3ephy_scheduler_con1 scheduler_con1; /* offset : 0x438 */
	union hbm3ephy_scheduler_con2 scheduler_con2; /* offset : 0x43c */
	union hbm3ephy_scheduler_con3 scheduler_con3; /* offset : 0x440 */
	union hbm3ephy_scheduler_con4 scheduler_con4; /* offset : 0x444 */
	union hbm3ephy_scheduler_con5 scheduler_con5; /* offset : 0x448 */
	union hbm3ephy_scheduler_state scheduler_state; /* offset : 0x44c */
	union hbm3ephy_io_duty_ctrl io_duty_ctrl; /* offset : 0x450 */
	union hbm3ephy_dtb dtb; /* offset : 0x454 */
	union hbm3ephy_cg_off cg_off; /* offset : 0x458 */
	union hbm3ephy_vwm_dq0_stat vwm_dq0_stat; /* offset : 0x45c */
	union hbm3ephy_vwm_dq1_stat vwm_dq1_stat; /* offset : 0x460 */
	union hbm3ephy_vwm_dq2_stat vwm_dq2_stat; /* offset : 0x464 */
	union hbm3ephy_vwm_dq3_stat vwm_dq3_stat; /* offset : 0x468 */
	union hbm3ephy_vwm_dq4_stat vwm_dq4_stat; /* offset : 0x46c */
	union hbm3ephy_vwm_dq5_stat vwm_dq5_stat; /* offset : 0x470 */
	union hbm3ephy_vwm_dq6_stat vwm_dq6_stat; /* offset : 0x474 */
	union hbm3ephy_vwm_dq7_stat vwm_dq7_stat; /* offset : 0x478 */
	union hbm3ephy_vwm_dq8_stat vwm_dq8_stat; /* offset : 0x47c */
	union hbm3ephy_vwm_dq9_stat vwm_dq9_stat; /* offset : 0x480 */
	union hbm3ephy_vwm_dq10_stat vwm_dq10_stat; /* offset : 0x484 */
	union hbm3ephy_vwm_dq11_stat vwm_dq11_stat; /* offset : 0x488 */
	union hbm3ephy_vwm_dq12_stat vwm_dq12_stat; /* offset : 0x48c */
	union hbm3ephy_vwm_dq13_stat vwm_dq13_stat; /* offset : 0x490 */
	union hbm3ephy_vwm_dq14_stat vwm_dq14_stat; /* offset : 0x494 */
	union hbm3ephy_vwm_dq15_stat vwm_dq15_stat; /* offset : 0x498 */
	union hbm3ephy_vwm_dq16_stat vwm_dq16_stat; /* offset : 0x49c */
	union hbm3ephy_vwm_dq17_stat vwm_dq17_stat; /* offset : 0x4a0 */
	union hbm3ephy_vwm_dq18_stat vwm_dq18_stat; /* offset : 0x4a4 */
	union hbm3ephy_vwm_dq19_stat vwm_dq19_stat; /* offset : 0x4a8 */
	union hbm3ephy_vwm_dq20_stat vwm_dq20_stat; /* offset : 0x4ac */
	union hbm3ephy_vwm_dq21_stat vwm_dq21_stat; /* offset : 0x4b0 */
	union hbm3ephy_vwm_dq22_stat vwm_dq22_stat; /* offset : 0x4b4 */
	union hbm3ephy_vwm_dq23_stat vwm_dq23_stat; /* offset : 0x4b8 */
	union hbm3ephy_vwm_dq24_stat vwm_dq24_stat; /* offset : 0x4bc */
	union hbm3ephy_vwm_dq25_stat vwm_dq25_stat; /* offset : 0x4c0 */
	union hbm3ephy_vwm_dq26_stat vwm_dq26_stat; /* offset : 0x4c4 */
	union hbm3ephy_vwm_dq27_stat vwm_dq27_stat; /* offset : 0x4c8 */
	union hbm3ephy_vwm_dq28_stat vwm_dq28_stat; /* offset : 0x4cc */
	union hbm3ephy_vwm_dq29_stat vwm_dq29_stat; /* offset : 0x4d0 */
	union hbm3ephy_vwm_dq30_stat vwm_dq30_stat; /* offset : 0x4d4 */
	union hbm3ephy_vwm_dq31_stat vwm_dq31_stat; /* offset : 0x4d8 */
	union hbm3ephy_vwm_ecc0_stat vwm_ecc0_stat; /* offset : 0x4dc */
	union hbm3ephy_vwm_ecc1_stat vwm_ecc1_stat; /* offset : 0x4e0 */
	union hbm3ephy_vwm_sev0_stat vwm_sev0_stat; /* offset : 0x4e4 */
	union hbm3ephy_vwm_sev1_stat vwm_sev1_stat; /* offset : 0x4e8 */
	union hbm3ephy_vwm_dbi0_stat vwm_dbi0_stat; /* offset : 0x4ec */
	union hbm3ephy_vwm_dbi1_stat vwm_dbi1_stat; /* offset : 0x4f0 */
	union hbm3ephy_vwm_dbi2_stat vwm_dbi2_stat; /* offset : 0x4f4 */
	union hbm3ephy_vwm_dbi3_stat vwm_dbi3_stat; /* offset : 0x4f8 */
	union hbm3ephy_vwm_par_stat vwm_par_stat; /* offset : 0x4fc */
	union hbm3ephy_vwm_rd0_stat vwm_rd0_stat; /* offset : 0x500 */
	union hbm3ephy_vwm_rd1_stat vwm_rd1_stat; /* offset : 0x504 */
	union hbm3ephy_sw_wr_lvl_cs0_code0 sw_wr_lvl_cs0_code0; /* offset : 0x508 */
	uint32_t reserved_4[4];
	union hbm3ephy_dfi_rddata0_0 dfi_rddata0_0; /* offset : 0x51c */
	union hbm3ephy_dfi_rddata0_1 dfi_rddata0_1; /* offset : 0x520 */
	union hbm3ephy_dfi_rddata0_2 dfi_rddata0_2; /* offset : 0x524 */
	union hbm3ephy_dfi_rddata0_3 dfi_rddata0_3; /* offset : 0x528 */
	union hbm3ephy_dfi_rddata2_0 dfi_rddata2_0; /* offset : 0x52c */
	union hbm3ephy_dfi_rddata2_1 dfi_rddata2_1; /* offset : 0x530 */
	union hbm3ephy_dfi_rddata2_2 dfi_rddata2_2; /* offset : 0x534 */
	union hbm3ephy_dfi_rddata2_3 dfi_rddata2_3; /* offset : 0x538 */
	union hbm3ephy_dfi_rddata4_0 dfi_rddata4_0; /* offset : 0x53c */
	union hbm3ephy_dfi_rddata4_1 dfi_rddata4_1; /* offset : 0x540 */
	union hbm3ephy_dfi_rddata4_2 dfi_rddata4_2; /* offset : 0x544 */
	union hbm3ephy_dfi_rddata4_3 dfi_rddata4_3; /* offset : 0x548 */
	union hbm3ephy_dfi_rddata6_0 dfi_rddata6_0; /* offset : 0x54c */
	union hbm3ephy_dfi_rddata6_1 dfi_rddata6_1; /* offset : 0x550 */
	union hbm3ephy_dfi_rddata6_2 dfi_rddata6_2; /* offset : 0x554 */
	union hbm3ephy_dfi_rddata6_3 dfi_rddata6_3; /* offset : 0x558 */
	union hbm3ephy_dfi_rddata8_0 dfi_rddata8_0; /* offset : 0x55c */
	union hbm3ephy_dfi_rddata8_1 dfi_rddata8_1; /* offset : 0x560 */
	union hbm3ephy_dfi_rddata8_2 dfi_rddata8_2; /* offset : 0x564 */
	union hbm3ephy_dfi_rddata8_3 dfi_rddata8_3; /* offset : 0x568 */
	union hbm3ephy_dfi_rddata10_0 dfi_rddata10_0; /* offset : 0x56c */
	union hbm3ephy_dfi_rddata10_1 dfi_rddata10_1; /* offset : 0x570 */
	union hbm3ephy_dfi_rddata10_2 dfi_rddata10_2; /* offset : 0x574 */
	union hbm3ephy_dfi_rddata10_3 dfi_rddata10_3; /* offset : 0x578 */
	union hbm3ephy_dfi_rddata12_0 dfi_rddata12_0; /* offset : 0x57c */
	union hbm3ephy_dfi_rddata12_1 dfi_rddata12_1; /* offset : 0x580 */
	union hbm3ephy_dfi_rddata12_2 dfi_rddata12_2; /* offset : 0x584 */
	union hbm3ephy_dfi_rddata12_3 dfi_rddata12_3; /* offset : 0x588 */
	union hbm3ephy_dfi_rddata14_0 dfi_rddata14_0; /* offset : 0x58c */
	union hbm3ephy_dfi_rddata14_1 dfi_rddata14_1; /* offset : 0x590 */
	union hbm3ephy_dfi_rddata14_2 dfi_rddata14_2; /* offset : 0x594 */
	union hbm3ephy_dfi_rddata14_3 dfi_rddata14_3; /* offset : 0x598 */
	union hbm3ephy_dfi_rddata_ecc_0 dfi_rddata_ecc_0; /* offset : 0x59c */
	union hbm3ephy_dfi_rddata_ecc_1 dfi_rddata_ecc_1; /* offset : 0x5a0 */
	union hbm3ephy_dfi_rddata_ecc_2 dfi_rddata_ecc_2; /* offset : 0x5a4 */
	union hbm3ephy_dfi_rddata_ecc_3 dfi_rddata_ecc_3; /* offset : 0x5a8 */
	union hbm3ephy_dfi_rddata_sev_0 dfi_rddata_sev_0; /* offset : 0x5ac */
	union hbm3ephy_dfi_rddata_sev_1 dfi_rddata_sev_1; /* offset : 0x5b0 */
	union hbm3ephy_dfi_rddata_sev_2 dfi_rddata_sev_2; /* offset : 0x5b4 */
	union hbm3ephy_dfi_rddata_sev_3 dfi_rddata_sev_3; /* offset : 0x5b8 */
	union hbm3ephy_dfi_rddata_dbi_0 dfi_rddata_dbi_0; /* offset : 0x5bc */
	union hbm3ephy_dfi_rddata_dbi_1 dfi_rddata_dbi_1; /* offset : 0x5c0 */
	union hbm3ephy_dfi_rddata_dbi_2 dfi_rddata_dbi_2; /* offset : 0x5c4 */
	union hbm3ephy_dfi_rddata_dbi_3 dfi_rddata_dbi_3; /* offset : 0x5c8 */
	union hbm3ephy_dfi_rddata_dbi_4 dfi_rddata_dbi_4; /* offset : 0x5cc */
	union hbm3ephy_dfi_rddata_dbi_5 dfi_rddata_dbi_5; /* offset : 0x5d0 */
	union hbm3ephy_dfi_rddata_dbi_6 dfi_rddata_dbi_6; /* offset : 0x5d4 */
	union hbm3ephy_dfi_rddata_dbi_7 dfi_rddata_dbi_7; /* offset : 0x5d8 */
	union hbm3ephy_dfi_rddata_par_0 dfi_rddata_par_0; /* offset : 0x5dc */
	union hbm3ephy_ptc_dword_stat0 ptc_dword_stat0; /* offset : 0x5e0 */
	union hbm3ephy_ptc_dword_stat1 ptc_dword_stat1; /* offset : 0x5e4 */
	union hbm3ephy_ptc_dword_stat2 ptc_dword_stat2; /* offset : 0x5e8 */
	union hbm3ephy_ptc_dword_stat3 ptc_dword_stat3; /* offset : 0x5ec */
	union hbm3ephy_ptc_dword_stat4 ptc_dword_stat4; /* offset : 0x5f0 */
	union hbm3ephy_ptc_dword_stat5 ptc_dword_stat5; /* offset : 0x5f4 */
	union hbm3ephy_cal_rd_pattern_con0 cal_rd_pattern_con0; /* offset : 0x5f8 */
	union hbm3ephy_cal_rd_pattern_con1 cal_rd_pattern_con1; /* offset : 0x5fc */
	union hbm3ephy_cal_rd_pattern_con2 cal_rd_pattern_con2; /* offset : 0x600 */
	union hbm3ephy_cal_rd_pattern_con3 cal_rd_pattern_con3; /* offset : 0x604 */
	union hbm3ephy_cal_rd_pattern_con4 cal_rd_pattern_con4; /* offset : 0x608 */
	union hbm3ephy_cal_rd_pattern_con5 cal_rd_pattern_con5; /* offset : 0x60c */
	union hbm3ephy_cal_rd_pattern_con6 cal_rd_pattern_con6; /* offset : 0x610 */
	union hbm3ephy_cal_rd_pattern_con7 cal_rd_pattern_con7; /* offset : 0x614 */
	union hbm3ephy_cal_rd_pattern_con8 cal_rd_pattern_con8; /* offset : 0x618 */
	union hbm3ephy_cal_rd_pattern_con9 cal_rd_pattern_con9; /* offset : 0x61c */
	union hbm3ephy_cal_rd_pattern_con10 cal_rd_pattern_con10; /* offset : 0x620 */
	union hbm3ephy_cal_rd_pattern_con11 cal_rd_pattern_con11; /* offset : 0x624 */
	union hbm3ephy_cal_rd_pattern_con12 cal_rd_pattern_con12; /* offset : 0x628 */
	union hbm3ephy_cal_rd_pattern_con13 cal_rd_pattern_con13; /* offset : 0x62c */
	union hbm3ephy_cal_rd_pattern_con14 cal_rd_pattern_con14; /* offset : 0x630 */
	union hbm3ephy_cal_rd_pattern_con15 cal_rd_pattern_con15; /* offset : 0x634 */
	union hbm3ephy_cal_rd_pattern_con16 cal_rd_pattern_con16; /* offset : 0x638 */
	union hbm3ephy_cal_rd_pattern_con17 cal_rd_pattern_con17; /* offset : 0x63c */
	union hbm3ephy_cal_rd_pattern_con18 cal_rd_pattern_con18; /* offset : 0x640 */
	union hbm3ephy_cal_rd_pattern_con19 cal_rd_pattern_con19; /* offset : 0x644 */
	union hbm3ephy_cal_rd_pattern_con20 cal_rd_pattern_con20; /* offset : 0x648 */
	union hbm3ephy_cal_rd_pattern_con21 cal_rd_pattern_con21; /* offset : 0x64c */
	union hbm3ephy_rd_cal_fail_stat0 rd_cal_fail_stat0; /* offset : 0x650 */
	union hbm3ephy_rd_cal_fail_stat1 rd_cal_fail_stat1; /* offset : 0x654 */
	union hbm3ephy_rd_cal_fail_stat2 rd_cal_fail_stat2; /* offset : 0x658 */
	union hbm3ephy_read_dq_offset_ctrl0_dword0 read_dq_offset_ctrl0_dword0; /* offset : 0x65c */
	union hbm3ephy_read_dq_offset_ctrl1_dword0 read_dq_offset_ctrl1_dword0; /* offset : 0x660 */
	union hbm3ephy_read_dq_offset_ctrl2_dword0 read_dq_offset_ctrl2_dword0; /* offset : 0x664 */
	union hbm3ephy_read_dq_offset_ctrl3_dword0 read_dq_offset_ctrl3_dword0; /* offset : 0x668 */
	union hbm3ephy_read_dq_offset_ctrl4_dword0 read_dq_offset_ctrl4_dword0; /* offset : 0x66c */
	union hbm3ephy_read_dq_offset_ctrl5_dword0 read_dq_offset_ctrl5_dword0; /* offset : 0x670 */
	union hbm3ephy_read_dq_offset_ctrl6_dword0 read_dq_offset_ctrl6_dword0; /* offset : 0x674 */
	union hbm3ephy_read_dq_offset_ctrl7_dword0 read_dq_offset_ctrl7_dword0; /* offset : 0x678 */
	union hbm3ephy_read_ecc_offset_ctrl0_dword0 read_ecc_offset_ctrl0_dword0; /* offset : 0x67c */
	union hbm3ephy_read_sev_offset_ctrl0_dword0 read_sev_offset_ctrl0_dword0; /* offset : 0x680 */
	union hbm3ephy_read_dbi_offset_ctrl0_dword0 read_dbi_offset_ctrl0_dword0; /* offset : 0x684 */
	union hbm3ephy_read_par_offset_ctrl0_dword0 read_par_offset_ctrl0_dword0; /* offset : 0x688 */
	union hbm3ephy_read_rd_offset_ctrl0_dword0 read_rd_offset_ctrl0_dword0; /* offset : 0x68c */
	union hbm3ephy_read_dq_offset_ctrl0_dword1 read_dq_offset_ctrl0_dword1; /* offset : 0x690 */
	union hbm3ephy_read_dq_offset_ctrl1_dword1 read_dq_offset_ctrl1_dword1; /* offset : 0x694 */
	union hbm3ephy_read_dq_offset_ctrl2_dword1 read_dq_offset_ctrl2_dword1; /* offset : 0x698 */
	union hbm3ephy_read_dq_offset_ctrl3_dword1 read_dq_offset_ctrl3_dword1; /* offset : 0x69c */
	union hbm3ephy_read_dq_offset_ctrl4_dword1 read_dq_offset_ctrl4_dword1; /* offset : 0x6a0 */
	union hbm3ephy_read_dq_offset_ctrl5_dword1 read_dq_offset_ctrl5_dword1; /* offset : 0x6a4 */
	union hbm3ephy_read_dq_offset_ctrl6_dword1 read_dq_offset_ctrl6_dword1; /* offset : 0x6a8 */
	union hbm3ephy_read_dq_offset_ctrl7_dword1 read_dq_offset_ctrl7_dword1; /* offset : 0x6ac */
	union hbm3ephy_read_ecc_offset_ctrl0_dword1 read_ecc_offset_ctrl0_dword1; /* offset : 0x6b0 */
	union hbm3ephy_read_sev_offset_ctrl0_dword1 read_sev_offset_ctrl0_dword1; /* offset : 0x6b4 */
	union hbm3ephy_read_dbi_offset_ctrl0_dword1 read_dbi_offset_ctrl0_dword1; /* offset : 0x6b8 */
	union hbm3ephy_read_par_offset_ctrl0_dword1 read_par_offset_ctrl0_dword1; /* offset : 0x6bc */
	union hbm3ephy_read_rd_offset_ctrl0_dword1 read_rd_offset_ctrl0_dword1; /* offset : 0x6c0 */
	union hbm3ephy_ctrl_io_con0 ctrl_io_con0; /* offset : 0x6c4 */
	uint32_t reserved_5[6];
	union hbm3ephy_debug_mon debug_mon; /* offset : 0x6e0 */
	uint32_t reserved_6[14];
	union hbm3ephy_schd_cmd_gating0 schd_cmd_gating0; /* offset : 0x71c */
	union hbm3ephy_ctrl_shift0 ctrl_shift0; /* offset : 0x720 */
	union hbm3ephy_ctrl_shift1 ctrl_shift1; /* offset : 0x724 */
	union hbm3ephy_ctrl_shift2 ctrl_shift2; /* offset : 0x728 */
	union hbm3ephy_ctrl_shift3 ctrl_shift3; /* offset : 0x72c */
	union hbm3ephy_prbs_per_bit_en0 prbs_per_bit_en0; /* offset : 0x730 */
	union hbm3ephy_prbs_per_bit_en1 prbs_per_bit_en1; /* offset : 0x734 */
	union hbm3ephy_prbs_per_bit_en2 prbs_per_bit_en2; /* offset : 0x738 */
	union hbm3ephy_cyc_mon0 cyc_mon0; /* offset : 0x73c */
	union hbm3ephy_cyc_mon1 cyc_mon1; /* offset : 0x740 */
	union hbm3ephy_cyc_mon2 cyc_mon2; /* offset : 0x744 */
	union hbm3ephy_cyc_mon3 cyc_mon3; /* offset : 0x748 */
	union hbm3ephy_cyc_mon4 cyc_mon4; /* offset : 0x74c */
	union hbm3ephy_cyc_mon5 cyc_mon5; /* offset : 0x750 */
	union hbm3ephy_cyc_mon6 cyc_mon6; /* offset : 0x754 */
	union hbm3ephy_cyc_mon7 cyc_mon7; /* offset : 0x758 */
	union hbm3ephy_cyc_mon8 cyc_mon8; /* offset : 0x75c */
	union hbm3ephy_cyc_mon9 cyc_mon9; /* offset : 0x760 */
	uint32_t reserved_7[7];
	union hbm3ephy_ctrl_shift4 ctrl_shift4; /* offset : 0x780 */
	union hbm3ephy_ctrl_shift5 ctrl_shift5; /* offset : 0x784 */
	union hbm3ephy_ctrl_shift6 ctrl_shift6; /* offset : 0x788 */
	union hbm3ephy_ctrl_shift7 ctrl_shift7; /* offset : 0x78c */
	union hbm3ephy_rduty_ctrl0 evt1_rduty_ctrl0; /* offset : 0x790 */ /* EVT1 only */
	union hbm3ephy_rduty_ctrl1 evt1_rduty_ctrl1; /* offset : 0x794 */ /* EVT1 only */
	union hbm3ephy_rduty_ctrl2 evt1_rduty_ctrl2; /* offset : 0x798 */ /* EVT1 only */
	union hbm3ephy_rduty_ctrl3 evt1_rduty_ctrl3; /* offset : 0x79c */ /* EVT1 only */
	union hbm3ephy_rduty_ctrl4 evt1_rduty_ctrl4; /* offset : 0x7a0 */ /* EVT1 only */
	union hbm3ephy_rduty_ctrl5 evt1_rduty_ctrl5; /* offset : 0x7a4 */ /* EVT1 only */
	union hbm3ephy_ctrl_shift8 evt1_ctrl_shift8; /* offset : 0x7a8 */ /* EVT1 only */
	union hbm3ephy_ctrl_shift9 evt1_ctrl_shift9; /* offset : 0x7ac */ /* EVT1 only */
	uint32_t reserved_8[8];
	union hbm3ephy_duty_ctrl_en duty_ctrl_en; /* offset : 0x7d0 */
	union hbm3ephy_duty_ctrl0 duty_ctrl0; /* offset : 0x7d4 */
	union hbm3ephy_duty_ctrl1 duty_ctrl1; /* offset : 0x7d8 */
	union hbm3ephy_duty_ctrl2 duty_ctrl2; /* offset : 0x7dc */
	union hbm3ephy_duty_ctrl3 duty_ctrl3; /* offset : 0x7e0 */
	union hbm3ephy_duty_ctrl4 duty_ctrl4; /* offset : 0x7e4 */
	union hbm3ephy_duty_ctrl5 duty_ctrl5; /* offset : 0x7e8 */
	union hbm3ephy_duty_ctrl6 duty_ctrl6; /* offset : 0x7ec */
	union hbm3ephy_duty_ctrl7 duty_ctrl7; /* offset : 0x7f0 */
	union hbm3ephy_duty_ctrl8 duty_ctrl8; /* offset : 0x7f4 */
	union hbm3ephy_duty_ctrl9 duty_ctrl9; /* offset : 0x7f8 */
	union hbm3ephy_duty_ctrl10 duty_ctrl10; /* offset : 0x7fc */
	union hbm3ephy_duty_ctrl11 duty_ctrl11; /* offset : 0x800 */
	union hbm3ephy_duty_ctrl12 duty_ctrl12; /* offset : 0x804 */
	union hbm3ephy_duty_ctrl13 duty_ctrl13; /* offset : 0x808 */
	union hbm3ephy_duty_ctrl14 duty_ctrl14; /* offset : 0x80c */
	union hbm3ephy_duty_ctrl15 duty_ctrl15; /* offset : 0x810 */
	union hbm3ephy_duty_ctrl16 duty_ctrl16; /* offset : 0x814 */
	union hbm3ephy_duty_ctrl17 duty_ctrl17; /* offset : 0x818 */
	union hbm3ephy_duty_ctrl18 duty_ctrl18; /* offset : 0x81c */
	union hbm3ephy_duty_ctrl19 duty_ctrl19; /* offset : 0x820 */
	union hbm3ephy_duty_ctrl20 duty_ctrl20; /* offset : 0x824 */
	union hbm3ephy_duty_ctrl21 duty_ctrl21; /* offset : 0x828 */
	union hbm3ephy_duty_ctrl22 duty_ctrl22; /* offset : 0x82c */
	uint32_t reserved_9[5];
	union hbm3ephy_wr_lvl_fail_stat0 wr_lvl_fail_stat0; /* offset : 0x844 */
	union hbm3ephy_wr_lvl_overflow_stat0 wr_lvl_overflow_stat0; /* offset : 0x848 */
	union hbm3ephy_wr_cal_fail_stat0 wr_cal_fail_stat0; /* offset : 0x84c */
	union hbm3ephy_wr_cal_fail_stat1 wr_cal_fail_stat1; /* offset : 0x850 */
	union hbm3ephy_wr_cal_fail_stat2 wr_cal_fail_stat2; /* offset : 0x854 */
	union hbm3ephy_rd_cal_overflow0 rd_cal_overflow0; /* offset : 0x858 */
	union hbm3ephy_rd_cal_overflow1 rd_cal_overflow1; /* offset : 0x85c */
	union hbm3ephy_rd_cal_overflow2 rd_cal_overflow2; /* offset : 0x860 */
	union hbm3ephy_rd_cal_overflow3 rd_cal_overflow3; /* offset : 0x864 */
	union hbm3ephy_rd_cal_overflow4 rd_cal_overflow4; /* offset : 0x868 */
	union hbm3ephy_rd_cal_overflow5 rd_cal_overflow5; /* offset : 0x86c */
	union hbm3ephy_rd_cal_overflow6 rd_cal_overflow6; /* offset : 0x870 */
	union hbm3ephy_wr_cal_overflow0 wr_cal_overflow0; /* offset : 0x874 */
	union hbm3ephy_wr_cal_overflow1 wr_cal_overflow1; /* offset : 0x878 */
	union hbm3ephy_wr_cal_overflow2 wr_cal_overflow2; /* offset : 0x87c */
	union hbm3ephy_io_vref_con0 io_vref_con0; /* offset : 0x880 */
	union hbm3ephy_io_vref_con1 io_vref_con1; /* offset : 0x884 */
	union hbm3ephy_io_vref_con2 io_vref_con2; /* offset : 0x888 */
	union hbm3ephy_io_ctrl_con0 io_ctrl_con0; /* offset : 0x88c */
	union hbm3ephy_io_ctrl_con1 io_ctrl_con1; /* offset : 0x890 */
	union hbm3ephy_zq_test_con0 evt0_zq_test_con0; /* offset : 0x894 */ /* EVT0 only */
	union hbm3ephy_ptc_aword_stat0 ptc_aword_stat0; /* offset : 0x898 */
	union hbm3ephy_ptc_aword_stat1 ptc_aword_stat1; /* offset : 0x89c */
	union hbm3ephy_ptc_stat0 ptc_stat0; /* offset : 0x8a0 */
	union hbm3ephy_ptc_stat1 ptc_stat1; /* offset : 0x8a4 */
	union hbm3ephy_ptc_con0 ptc_con0; /* offset : 0x8a8 */
	union hbm3ephy_ptc_con1 ptc_con1; /* offset : 0x8ac */
	union hbm3ephy_ptc_con2 ptc_con2; /* offset : 0x8b0 */
	union hbm3ephy_ptc_con3 ptc_con3; /* offset : 0x8b4 */
	union hbm3ephy_ptc_con4 ptc_con4; /* offset : 0x8b8 */
	union hbm3ephy_ptc_con5 ptc_con5; /* offset : 0x8bc */
	union hbm3ephy_apar_stat1 apar_stat1; /* offset : 0x8c0 */
	uint32_t reserved_10[9];
	union hbm3ephy_polling_read_trn_con0 polling_read_trn_con0; /* offset : 0x8e8 */
	uint32_t reserved_11;
	union hbm3ephy_mrg_stat0 mrg_stat0; /* offset : 0x8f0 */
	union hbm3ephy_mrg_stat1 mrg_stat1; /* offset : 0x8f4 */
	union hbm3ephy_mrg_stat2 mrg_stat2; /* offset : 0x8f8 */
	union hbm3ephy_mrg_stat3 mrg_stat3; /* offset : 0x8fc */
	union hbm3ephy_mrg_stat4 mrg_stat4; /* offset : 0x900 */
	union hbm3ephy_mrg_stat5 mrg_stat5; /* offset : 0x904 */
	union hbm3ephy_mrg_stat6 mrg_stat6; /* offset : 0x908 */
	union hbm3ephy_mrg_stat7 mrg_stat7; /* offset : 0x90c */
	union hbm3ephy_mrg_stat8 mrg_stat8; /* offset : 0x910 */
	union hbm3ephy_mrg_stat9 mrg_stat9; /* offset : 0x914 */
	union hbm3ephy_mrg_stat10 mrg_stat10; /* offset : 0x918 */
	uint32_t reserved_12[16];
	union hbm3ephy_sw_trn_con0 sw_trn_con0; /* offset : 0x95c */
	union hbm3ephy_sw_trn_con1 sw_trn_con1; /* offset : 0x960 */
	union hbm3ephy_sw_trn_con2 sw_trn_con2; /* offset : 0x964 */
	union hbm3ephy_sw_trn_cmd0_0 sw_trn_cmd0_0; /* offset : 0x968 */
	union hbm3ephy_sw_trn_cmd0_1 sw_trn_cmd0_1; /* offset : 0x96c */
	union hbm3ephy_sw_trn_cmd1_0 sw_trn_cmd1_0; /* offset : 0x970 */
	union hbm3ephy_sw_trn_cmd1_1 sw_trn_cmd1_1; /* offset : 0x974 */
	union hbm3ephy_sw_trn_cmd2_0 sw_trn_cmd2_0; /* offset : 0x978 */
	union hbm3ephy_sw_trn_cmd2_1 sw_trn_cmd2_1; /* offset : 0x97c */
	union hbm3ephy_sw_trn_cmd3_0 sw_trn_cmd3_0; /* offset : 0x980 */
	union hbm3ephy_sw_trn_cmd3_1 sw_trn_cmd3_1; /* offset : 0x984 */
	union hbm3ephy_sw_trn_cmd4_0 sw_trn_cmd4_0; /* offset : 0x988 */
	union hbm3ephy_sw_trn_cmd4_1 sw_trn_cmd4_1; /* offset : 0x98c */
	union hbm3ephy_sw_trn_cmd5_0 sw_trn_cmd5_0; /* offset : 0x990 */
	union hbm3ephy_sw_trn_cmd5_1 sw_trn_cmd5_1; /* offset : 0x994 */
	union hbm3ephy_sw_trn_cmd6_0 sw_trn_cmd6_0; /* offset : 0x998 */
	union hbm3ephy_sw_trn_cmd6_1 sw_trn_cmd6_1; /* offset : 0x99c */
	union hbm3ephy_sw_trn_cmd7_0 sw_trn_cmd7_0; /* offset : 0x9a0 */
	union hbm3ephy_sw_trn_cmd7_1 sw_trn_cmd7_1; /* offset : 0x9a4 */
	union hbm3ephy_sw_trn_cmd8_0 sw_trn_cmd8_0; /* offset : 0x9a8 */
	union hbm3ephy_sw_trn_cmd8_1 sw_trn_cmd8_1; /* offset : 0x9ac */
	union hbm3ephy_sw_trn_cmd9_0 sw_trn_cmd9_0; /* offset : 0x9b0 */
	union hbm3ephy_sw_trn_cmd9_1 sw_trn_cmd9_1; /* offset : 0x9b4 */
	union hbm3ephy_sw_trn_cmd10_0 sw_trn_cmd10_0; /* offset : 0x9b8 */
	union hbm3ephy_sw_trn_cmd10_1 sw_trn_cmd10_1; /* offset : 0x9bc */
	union hbm3ephy_sw_trn_cmd11_0 sw_trn_cmd11_0; /* offset : 0x9c0 */
	union hbm3ephy_sw_trn_cmd11_1 sw_trn_cmd11_1; /* offset : 0x9c4 */
	union hbm3ephy_sw_trn_cmd12_0 sw_trn_cmd12_0; /* offset : 0x9c8 */
	union hbm3ephy_sw_trn_cmd12_1 sw_trn_cmd12_1; /* offset : 0x9cc */
	union hbm3ephy_sw_trn_cmd13_0 sw_trn_cmd13_0; /* offset : 0x9d0 */
	union hbm3ephy_sw_trn_cmd13_1 sw_trn_cmd13_1; /* offset : 0x9d4 */
	union hbm3ephy_sw_trn_cmd14_0 sw_trn_cmd14_0; /* offset : 0x9d8 */
	union hbm3ephy_sw_trn_cmd14_1 sw_trn_cmd14_1; /* offset : 0x9dc */
	union hbm3ephy_sw_trn_cmd15_0 sw_trn_cmd15_0; /* offset : 0x9e0 */
	union hbm3ephy_sw_trn_cmd15_1 sw_trn_cmd15_1; /* offset : 0x9e4 */
	union hbm3ephy_sw_trn_cmd16_0 sw_trn_cmd16_0; /* offset : 0x9e8 */
	union hbm3ephy_sw_trn_cmd16_1 sw_trn_cmd16_1; /* offset : 0x9ec */
	union hbm3ephy_sw_trn_cmd17_0 sw_trn_cmd17_0; /* offset : 0x9f0 */
	union hbm3ephy_sw_trn_cmd17_1 sw_trn_cmd17_1; /* offset : 0x9f4 */
	union hbm3ephy_sw_trn_cmd18_0 sw_trn_cmd18_0; /* offset : 0x9f8 */
	union hbm3ephy_sw_trn_cmd18_1 sw_trn_cmd18_1; /* offset : 0x9fc */
	union hbm3ephy_sw_trn_cmd19_0 sw_trn_cmd19_0; /* offset : 0xa00 */
	union hbm3ephy_sw_trn_cmd19_1 sw_trn_cmd19_1; /* offset : 0xa04 */
	union hbm3ephy_sw_trn_cmd20_0 sw_trn_cmd20_0; /* offset : 0xa08 */
	union hbm3ephy_sw_trn_cmd20_1 sw_trn_cmd20_1; /* offset : 0xa0c */
	union hbm3ephy_sw_trn_cmd21_0 sw_trn_cmd21_0; /* offset : 0xa10 */
	union hbm3ephy_sw_trn_cmd21_1 sw_trn_cmd21_1; /* offset : 0xa14 */
	union hbm3ephy_sw_trn_cmd22_0 sw_trn_cmd22_0; /* offset : 0xa18 */
	union hbm3ephy_sw_trn_cmd22_1 sw_trn_cmd22_1; /* offset : 0xa1c */
	union hbm3ephy_sw_trn_cmd23_0 sw_trn_cmd23_0; /* offset : 0xa20 */
	union hbm3ephy_sw_trn_cmd23_1 sw_trn_cmd23_1; /* offset : 0xa24 */
	union hbm3ephy_sw_trn_cmd24_0 sw_trn_cmd24_0; /* offset : 0xa28 */
	union hbm3ephy_sw_trn_cmd24_1 sw_trn_cmd24_1; /* offset : 0xa2c */
	union hbm3ephy_sw_trn_cmd25_0 sw_trn_cmd25_0; /* offset : 0xa30 */
	union hbm3ephy_sw_trn_cmd25_1 sw_trn_cmd25_1; /* offset : 0xa34 */
	union hbm3ephy_sw_trn_cmd26_0 sw_trn_cmd26_0; /* offset : 0xa38 */
	union hbm3ephy_sw_trn_cmd26_1 sw_trn_cmd26_1; /* offset : 0xa3c */
	union hbm3ephy_sw_trn_cmd27_0 sw_trn_cmd27_0; /* offset : 0xa40 */
	union hbm3ephy_sw_trn_cmd27_1 sw_trn_cmd27_1; /* offset : 0xa44 */
	union hbm3ephy_sw_trn_cmd28_0 sw_trn_cmd28_0; /* offset : 0xa48 */
	union hbm3ephy_sw_trn_cmd28_1 sw_trn_cmd28_1; /* offset : 0xa4c */
	union hbm3ephy_sw_trn_cmd29_0 sw_trn_cmd29_0; /* offset : 0xa50 */
	union hbm3ephy_sw_trn_cmd29_1 sw_trn_cmd29_1; /* offset : 0xa54 */
	union hbm3ephy_sw_trn_cmd30_0 sw_trn_cmd30_0; /* offset : 0xa58 */
	union hbm3ephy_sw_trn_cmd30_1 sw_trn_cmd30_1; /* offset : 0xa5c */
	union hbm3ephy_sw_trn_cmd31_0 sw_trn_cmd31_0; /* offset : 0xa60 */
	union hbm3ephy_sw_trn_cmd31_1 sw_trn_cmd31_1; /* offset : 0xa64 */
	uint32_t reserved_13[38];
	union hbm3ephy_final_deskewcode0 final_deskewcode0; /* offset : 0xb00 */
	union hbm3ephy_final_deskewcode1 final_deskewcode1; /* offset : 0xb04 */
	union hbm3ephy_final_deskewcode2 final_deskewcode2; /* offset : 0xb08 */
	union hbm3ephy_final_deskewcode3 final_deskewcode3; /* offset : 0xb0c */
	union hbm3ephy_final_deskewcode4 final_deskewcode4; /* offset : 0xb10 */
	union hbm3ephy_final_deskewcode5 final_deskewcode5; /* offset : 0xb14 */
	union hbm3ephy_final_deskewcode6 final_deskewcode6; /* offset : 0xb18 */
	union hbm3ephy_final_deskewcode7 final_deskewcode7; /* offset : 0xb1c */
	union hbm3ephy_final_deskewcode8 final_deskewcode8; /* offset : 0xb20 */
	union hbm3ephy_final_deskewcode9 final_deskewcode9; /* offset : 0xb24 */
	union hbm3ephy_final_deskewcode10 final_deskewcode10; /* offset : 0xb28 */
	union hbm3ephy_final_deskewcode11 final_deskewcode11; /* offset : 0xb2c */
	union hbm3ephy_final_deskewcode12 final_deskewcode12; /* offset : 0xb30 */
	union hbm3ephy_final_deskewcode13 final_deskewcode13; /* offset : 0xb34 */
	union hbm3ephy_final_deskewcode14 final_deskewcode14; /* offset : 0xb38 */
	union hbm3ephy_final_deskewcode15 final_deskewcode15; /* offset : 0xb3c */
	union hbm3ephy_final_deskewcode16 final_deskewcode16; /* offset : 0xb40 */
	union hbm3ephy_final_deskewcode17 final_deskewcode17; /* offset : 0xb44 */
	union hbm3ephy_final_deskewcode18 final_deskewcode18; /* offset : 0xb48 */
	union hbm3ephy_final_deskewcode19 final_deskewcode19; /* offset : 0xb4c */
	union hbm3ephy_final_deskewcode20 final_deskewcode20; /* offset : 0xb50 */
	union hbm3ephy_final_deskewcode21 final_deskewcode21; /* offset : 0xb54 */
	union hbm3ephy_final_deskewcode22 final_deskewcode22; /* offset : 0xb58 */
	union hbm3ephy_final_deskewcode23 final_deskewcode23; /* offset : 0xb5c */
	union hbm3ephy_final_deskewcode24 final_deskewcode24; /* offset : 0xb60 */
	union hbm3ephy_final_deskewcode25 final_deskewcode25; /* offset : 0xb64 */
	union hbm3ephy_final_deskewcode26 final_deskewcode26; /* offset : 0xb68 */
	union hbm3ephy_final_deskewcode27 final_deskewcode27; /* offset : 0xb6c */
	union hbm3ephy_final_deskewcode28 final_deskewcode28; /* offset : 0xb70 */
	union hbm3ephy_final_deskewcode29 final_deskewcode29; /* offset : 0xb74 */
	union hbm3ephy_final_deskewcode30 final_deskewcode30; /* offset : 0xb78 */
	union hbm3ephy_final_deskewcode31 final_deskewcode31; /* offset : 0xb7c */
	union hbm3ephy_final_deskewcode32 final_deskewcode32; /* offset : 0xb80 */
	union hbm3ephy_final_deskewcode33 final_deskewcode33; /* offset : 0xb84 */
	union hbm3ephy_final_deskewcode34 final_deskewcode34; /* offset : 0xb88 */
	union hbm3ephy_final_deskewcode35 final_deskewcode35; /* offset : 0xb8c */
	union hbm3ephy_final_deskewcode36 final_deskewcode36; /* offset : 0xb90 */
	union hbm3ephy_final_deskewcode37 final_deskewcode37; /* offset : 0xb94 */
	union hbm3ephy_final_deskewcode38 final_deskewcode38; /* offset : 0xb98 */
	union hbm3ephy_final_deskewcode39 final_deskewcode39; /* offset : 0xb9c */
	union hbm3ephy_final_deskewcode40 final_deskewcode40; /* offset : 0xba0 */
	union hbm3ephy_final_deskewcode41 final_deskewcode41; /* offset : 0xba4 */
	union hbm3ephy_final_deskewcode42 final_deskewcode42; /* offset : 0xba8 */
	union hbm3ephy_final_deskewcode43 final_deskewcode43; /* offset : 0xbac */
	union hbm3ephy_final_deskewcode44 final_deskewcode44; /* offset : 0xbb0 */
	union hbm3ephy_final_deskewcode45 final_deskewcode45; /* offset : 0xbb4 */
	union hbm3ephy_final_deskewcode46 final_deskewcode46; /* offset : 0xbb8 */
	union hbm3ephy_final_deskewcode47 final_deskewcode47; /* offset : 0xbbc */
	union hbm3ephy_final_deskewcode48 final_deskewcode48; /* offset : 0xbc0 */
	union hbm3ephy_final_deskewcode49 final_deskewcode49; /* offset : 0xbc4 */
	union hbm3ephy_final_deskewcode50 final_deskewcode50; /* offset : 0xbc8 */
	union hbm3ephy_final_deskewcode51 final_deskewcode51; /* offset : 0xbcc */
	union hbm3ephy_final_deskewcode52 final_deskewcode52; /* offset : 0xbd0 */
	union hbm3ephy_final_deskewcode53 final_deskewcode53; /* offset : 0xbd4 */
	union hbm3ephy_final_deskewcode54 final_deskewcode54; /* offset : 0xbd8 */
	union hbm3ephy_final_deskewcode55 final_deskewcode55; /* offset : 0xbdc */
	union hbm3ephy_final_deskewcode56 final_deskewcode56; /* offset : 0xbe0 */
	union hbm3ephy_final_deskewcode57 final_deskewcode57; /* offset : 0xbe4 */
	union hbm3ephy_final_deskewcode58 final_deskewcode58; /* offset : 0xbe8 */
	union hbm3ephy_final_deskewcode59 final_deskewcode59; /* offset : 0xbec */
	union hbm3ephy_final_deskewcode60 final_deskewcode60; /* offset : 0xbf0 */
	union hbm3ephy_final_deskewcode61 final_deskewcode61; /* offset : 0xbf4 */
	union hbm3ephy_final_deskewcode62 final_deskewcode62; /* offset : 0xbf8 */
	union hbm3ephy_final_deskewcode63 final_deskewcode63; /* offset : 0xbfc */
	union hbm3ephy_final_deskewcode64 final_deskewcode64; /* offset : 0xc00 */
	union hbm3ephy_final_deskewcode65 final_deskewcode65; /* offset : 0xc04 */
	union hbm3ephy_final_deskewcode66 final_deskewcode66; /* offset : 0xc08 */
	union hbm3ephy_final_deskewcode67 final_deskewcode67; /* offset : 0xc0c */
	union hbm3ephy_final_deskewcode68 final_deskewcode68; /* offset : 0xc10 */
	union hbm3ephy_final_deskewcode69 final_deskewcode69; /* offset : 0xc14 */
	union hbm3ephy_final_deskewcode70 final_deskewcode70; /* offset : 0xc18 */
	union hbm3ephy_final_deskewcode71 final_deskewcode71; /* offset : 0xc1c */
	union hbm3ephy_final_deskewcode72 final_deskewcode72; /* offset : 0xc20 */
	union hbm3ephy_final_deskewcode73 final_deskewcode73; /* offset : 0xc24 */
	union hbm3ephy_final_deskewcode74 final_deskewcode74; /* offset : 0xc28 */
	union hbm3ephy_final_deskewcode75 final_deskewcode75; /* offset : 0xc2c */
	union hbm3ephy_final_deskewcode76 final_deskewcode76; /* offset : 0xc30 */
	union hbm3ephy_final_deskewcode77 final_deskewcode77; /* offset : 0xc34 */
	union hbm3ephy_final_deskewcode78 final_deskewcode78; /* offset : 0xc38 */
	union hbm3ephy_final_deskewcode79 final_deskewcode79; /* offset : 0xc3c */
	union hbm3ephy_final_deskewcode80 final_deskewcode80; /* offset : 0xc40 */
	union hbm3ephy_final_deskewcode81 final_deskewcode81; /* offset : 0xc44 */
	union hbm3ephy_final_deskewcode82 final_deskewcode82; /* offset : 0xc48 */
	union hbm3ephy_final_deskewcode83 final_deskewcode83; /* offset : 0xc4c */
	union hbm3ephy_final_deskewcode84 final_deskewcode84; /* offset : 0xc50 */
	union hbm3ephy_final_deskewcode85 final_deskewcode85; /* offset : 0xc54 */
	union hbm3ephy_final_deskewcode86 final_deskewcode86; /* offset : 0xc58 */
	union hbm3ephy_final_deskewcode87 final_deskewcode87; /* offset : 0xc5c */
	union hbm3ephy_final_deskewcode88 final_deskewcode88; /* offset : 0xc60 */
	union hbm3ephy_final_deskewcode89 final_deskewcode89; /* offset : 0xc64 */
	union hbm3ephy_final_deskewcode90 final_deskewcode90; /* offset : 0xc68 */
	union hbm3ephy_final_deskewcode91 final_deskewcode91; /* offset : 0xc6c */
	union hbm3ephy_final_deskewcode92 final_deskewcode92; /* offset : 0xc70 */
	union hbm3ephy_final_deskewcode93 final_deskewcode93; /* offset : 0xc74 */
	union hbm3ephy_final_deskewcode94 final_deskewcode94; /* offset : 0xc78 */
	union hbm3ephy_final_deskewcode95 final_deskewcode95; /* offset : 0xc7c */
	union hbm3ephy_final_deskewcode96 final_deskewcode96; /* offset : 0xc80 */
	union hbm3ephy_final_deskewcode97 final_deskewcode97; /* offset : 0xc84 */
	union hbm3ephy_final_deskewcode98 final_deskewcode98; /* offset : 0xc88 */
	union hbm3ephy_final_deskewcode99 final_deskewcode99; /* offset : 0xc8c */
	union hbm3ephy_final_deskewcode100 final_deskewcode100; /* offset : 0xc90 */
	union hbm3ephy_final_deskewcode101 final_deskewcode101; /* offset : 0xc94 */
	union hbm3ephy_final_deskewcode102 final_deskewcode102; /* offset : 0xc98 */
	union hbm3ephy_final_deskewcode103 final_deskewcode103; /* offset : 0xc9c */
	union hbm3ephy_final_deskewcode104 final_deskewcode104; /* offset : 0xca0 */
	union hbm3ephy_final_deskewcode105 final_deskewcode105; /* offset : 0xca4 */
	union hbm3ephy_final_deskewcode106 final_deskewcode106; /* offset : 0xca8 */
	union hbm3ephy_final_deskewcode107 final_deskewcode107; /* offset : 0xcac */
	union hbm3ephy_final_deskewcode108 final_deskewcode108; /* offset : 0xcb0 */
	union hbm3ephy_final_deskewcode109 final_deskewcode109; /* offset : 0xcb4 */
	union hbm3ephy_final_deskewcode110 final_deskewcode110; /* offset : 0xcb8 */
	union hbm3ephy_final_deskewcode111 final_deskewcode111; /* offset : 0xcbc */
	union hbm3ephy_final_deskewcode112 final_deskewcode112; /* offset : 0xcc0 */
	union hbm3ephy_final_deskewcode113 final_deskewcode113; /* offset : 0xcc4 */
	union hbm3ephy_final_deskewcode114 final_deskewcode114; /* offset : 0xcc8 */
	union hbm3ephy_final_deskewcode115 final_deskewcode115; /* offset : 0xccc */
	union hbm3ephy_final_deskewcode116 final_deskewcode116; /* offset : 0xcd0 */
	union hbm3ephy_final_deskewcode117 final_deskewcode117; /* offset : 0xcd4 */
	union hbm3ephy_final_deskewcode118 final_deskewcode118; /* offset : 0xcd8 */
	union hbm3ephy_final_deskewcode119 final_deskewcode119; /* offset : 0xcdc */
	union hbm3ephy_final_deskewcode120 final_deskewcode120; /* offset : 0xce0 */
	union hbm3ephy_final_deskewcode121 final_deskewcode121; /* offset : 0xce4 */
	union hbm3ephy_final_deskewcode122 final_deskewcode122; /* offset : 0xce8 */
	union hbm3ephy_final_deskewcode123 final_deskewcode123; /* offset : 0xcec */
	union hbm3ephy_final_deskewcode124 final_deskewcode124; /* offset : 0xcf0 */
	union hbm3ephy_final_deskewcode125 final_deskewcode125; /* offset : 0xcf4 */
	union hbm3ephy_final_deskewcode126 final_deskewcode126; /* offset : 0xcf8 */
	union hbm3ephy_final_deskewcode127 final_deskewcode127; /* offset : 0xcfc */
	union hbm3ephy_final_deskewcode128 final_deskewcode128; /* offset : 0xd00 */
	union hbm3ephy_final_deskewcode129 final_deskewcode129; /* offset : 0xd04 */
	union hbm3ephy_final_deskewcode130 final_deskewcode130; /* offset : 0xd08 */
	union hbm3ephy_final_deskewcode131 final_deskewcode131; /* offset : 0xd0c */
	union hbm3ephy_final_deskewcode132 final_deskewcode132; /* offset : 0xd10 */
	union hbm3ephy_final_deskewcode133 final_deskewcode133; /* offset : 0xd14 */
	union hbm3ephy_final_deskewcode134 final_deskewcode134; /* offset : 0xd18 */
	union hbm3ephy_final_deskewcode135 final_deskewcode135; /* offset : 0xd1c */
	union hbm3ephy_final_deskewcode136 final_deskewcode136; /* offset : 0xd20 */
	union hbm3ephy_final_deskewcode137 final_deskewcode137; /* offset : 0xd24 */
	union hbm3ephy_final_deskewcode138 final_deskewcode138; /* offset : 0xd28 */
	union hbm3ephy_final_deskewcode139 final_deskewcode139; /* offset : 0xd2c */
	union hbm3ephy_prbs_offsetr0 prbs_offsetr0; /* offset : 0xd30 */
	union hbm3ephy_prbs_offsetr1 prbs_offsetr1; /* offset : 0xd34 */
	union hbm3ephy_prbs_offsetr2 prbs_offsetr2; /* offset : 0xd38 */
	union hbm3ephy_prbs_offsetr3 prbs_offsetr3; /* offset : 0xd3c */
	union hbm3ephy_prbs_offsetr4 prbs_offsetr4; /* offset : 0xd40 */
	union hbm3ephy_prbs_offsetr5 prbs_offsetr5; /* offset : 0xd44 */
	union hbm3ephy_prbs_offsetr6 prbs_offsetr6; /* offset : 0xd48 */
	union hbm3ephy_prbs_offsetr7 prbs_offsetr7; /* offset : 0xd4c */
	union hbm3ephy_prbs_offsetr8 prbs_offsetr8; /* offset : 0xd50 */
	union hbm3ephy_prbs_offsetr9 prbs_offsetr9; /* offset : 0xd54 */
	union hbm3ephy_prbs_offsetr10 prbs_offsetr10; /* offset : 0xd58 */
	union hbm3ephy_prbs_offsetr11 prbs_offsetr11; /* offset : 0xd5c */
	union hbm3ephy_prbs_offsetr12 prbs_offsetr12; /* offset : 0xd60 */
	union hbm3ephy_prbs_offsetr13 prbs_offsetr13; /* offset : 0xd64 */
	union hbm3ephy_prbs_offsetr14 prbs_offsetr14; /* offset : 0xd68 */
	union hbm3ephy_prbs_offsetr15 prbs_offsetr15; /* offset : 0xd6c */
	union hbm3ephy_prbs_offsetr16 prbs_offsetr16; /* offset : 0xd70 */
	union hbm3ephy_prbs_offsetr17 prbs_offsetr17; /* offset : 0xd74 */
	union hbm3ephy_prbs_offsetr18 prbs_offsetr18; /* offset : 0xd78 */
	union hbm3ephy_prbs_offsetr19 prbs_offsetr19; /* offset : 0xd7c */
	union hbm3ephy_prbs_offsetr20 prbs_offsetr20; /* offset : 0xd80 */
	union hbm3ephy_prbs_offsetr21 prbs_offsetr21; /* offset : 0xd84 */
	union hbm3ephy_prbs_offsetr22 prbs_offsetr22; /* offset : 0xd88 */
	union hbm3ephy_prbs_offsetr23 prbs_offsetr23; /* offset : 0xd8c */
	union hbm3ephy_prbs_offsetr24 prbs_offsetr24; /* offset : 0xd90 */
	union hbm3ephy_prbs_offsetr25 prbs_offsetr25; /* offset : 0xd94 */
	union hbm3ephy_prbs_offsetw0 prbs_offsetw0; /* offset : 0xd98 */
	union hbm3ephy_prbs_offsetw1 prbs_offsetw1; /* offset : 0xd9c */
	union hbm3ephy_prbs_offsetw2 prbs_offsetw2; /* offset : 0xda0 */
	union hbm3ephy_prbs_offsetw3 prbs_offsetw3; /* offset : 0xda4 */
	union hbm3ephy_prbs_offsetw4 prbs_offsetw4; /* offset : 0xda8 */
	union hbm3ephy_prbs_offsetw5 prbs_offsetw5; /* offset : 0xdac */
	union hbm3ephy_prbs_offsetw6 prbs_offsetw6; /* offset : 0xdb0 */
	union hbm3ephy_prbs_offsetw7 prbs_offsetw7; /* offset : 0xdb4 */
	union hbm3ephy_prbs_offsetw8 prbs_offsetw8; /* offset : 0xdb8 */
	union hbm3ephy_prbs_offsetw9 prbs_offsetw9; /* offset : 0xdbc */
	union hbm3ephy_prbs_offsetw10 prbs_offsetw10; /* offset : 0xdc0 */
	union hbm3ephy_prbs_offsetw11 prbs_offsetw11; /* offset : 0xdc4 */
	union hbm3ephy_prbs_offsetw12 prbs_offsetw12; /* offset : 0xdc8 */
	union hbm3ephy_prbs_offsetw13 prbs_offsetw13; /* offset : 0xdcc */
	union hbm3ephy_prbs_offsetw14 prbs_offsetw14; /* offset : 0xdd0 */
	union hbm3ephy_prbs_offsetw15 prbs_offsetw15; /* offset : 0xdd4 */
	union hbm3ephy_prbs_offsetw16 prbs_offsetw16; /* offset : 0xdd8 */
	union hbm3ephy_prbs_offsetw17 prbs_offsetw17; /* offset : 0xddc */
	union hbm3ephy_prbs_offsetw18 prbs_offsetw18; /* offset : 0xde0 */
	union hbm3ephy_prbs_offsetw19 prbs_offsetw19; /* offset : 0xde4 */
	union hbm3ephy_prbs_offsetw20 prbs_offsetw20; /* offset : 0xde8 */
	union hbm3ephy_prbs_offsetw21 prbs_offsetw21; /* offset : 0xdec */
	union hbm3ephy_prbs_offsetw22 prbs_offsetw22; /* offset : 0xdf0 */
	union hbm3ephy_prbs_offsetw23 prbs_offsetw23; /* offset : 0xdf4 */
	union hbm3ephy_prbs_offsetw24 prbs_offsetw24; /* offset : 0xdf8 */
	union hbm3ephy_prbs_offsetw25 prbs_offsetw25; /* offset : 0xdfc */
	union hbm3ephy_sw_prbs_offsetr0 sw_prbs_offsetr0; /* offset : 0xe00 */
	union hbm3ephy_sw_prbs_offsetr1 sw_prbs_offsetr1; /* offset : 0xe04 */
	union hbm3ephy_sw_prbs_offsetr2 sw_prbs_offsetr2; /* offset : 0xe08 */
	union hbm3ephy_sw_prbs_offsetr3 sw_prbs_offsetr3; /* offset : 0xe0c */
	union hbm3ephy_sw_prbs_offsetr4 sw_prbs_offsetr4; /* offset : 0xe10 */
	union hbm3ephy_sw_prbs_offsetr5 sw_prbs_offsetr5; /* offset : 0xe14 */
	union hbm3ephy_sw_prbs_offsetr6 sw_prbs_offsetr6; /* offset : 0xe18 */
	union hbm3ephy_sw_prbs_offsetr7 sw_prbs_offsetr7; /* offset : 0xe1c */
	union hbm3ephy_sw_prbs_offsetr8 sw_prbs_offsetr8; /* offset : 0xe20 */
	union hbm3ephy_sw_prbs_offsetr9 sw_prbs_offsetr9; /* offset : 0xe24 */
	union hbm3ephy_sw_prbs_offsetr10 sw_prbs_offsetr10; /* offset : 0xe28 */
	union hbm3ephy_sw_prbs_offsetr11 sw_prbs_offsetr11; /* offset : 0xe2c */
	union hbm3ephy_sw_prbs_offsetr12 sw_prbs_offsetr12; /* offset : 0xe30 */
	union hbm3ephy_sw_prbs_offsetr13 sw_prbs_offsetr13; /* offset : 0xe34 */
	union hbm3ephy_sw_prbs_offsetr14 sw_prbs_offsetr14; /* offset : 0xe38 */
	union hbm3ephy_sw_prbs_offsetr15 sw_prbs_offsetr15; /* offset : 0xe3c */
	union hbm3ephy_sw_prbs_offsetr16 sw_prbs_offsetr16; /* offset : 0xe40 */
	union hbm3ephy_sw_prbs_offsetr17 sw_prbs_offsetr17; /* offset : 0xe44 */
	union hbm3ephy_sw_prbs_offsetr18 sw_prbs_offsetr18; /* offset : 0xe48 */
	union hbm3ephy_sw_prbs_offsetr19 sw_prbs_offsetr19; /* offset : 0xe4c */
	union hbm3ephy_sw_prbs_offsetr20 sw_prbs_offsetr20; /* offset : 0xe50 */
	union hbm3ephy_sw_prbs_offsetr21 sw_prbs_offsetr21; /* offset : 0xe54 */
	union hbm3ephy_sw_prbs_offsetr22 sw_prbs_offsetr22; /* offset : 0xe58 */
	union hbm3ephy_sw_prbs_offsetr23 sw_prbs_offsetr23; /* offset : 0xe5c */
	union hbm3ephy_sw_prbs_offsetr24 sw_prbs_offsetr24; /* offset : 0xe60 */
	union hbm3ephy_sw_prbs_offsetr25 sw_prbs_offsetr25; /* offset : 0xe64 */
	union hbm3ephy_sw_prbs_offsetw0 sw_prbs_offsetw0; /* offset : 0xe68 */
	union hbm3ephy_sw_prbs_offsetw1 sw_prbs_offsetw1; /* offset : 0xe6c */
	union hbm3ephy_sw_prbs_offsetw2 sw_prbs_offsetw2; /* offset : 0xe70 */
	union hbm3ephy_sw_prbs_offsetw3 sw_prbs_offsetw3; /* offset : 0xe74 */
	union hbm3ephy_sw_prbs_offsetw4 sw_prbs_offsetw4; /* offset : 0xe78 */
	union hbm3ephy_sw_prbs_offsetw5 sw_prbs_offsetw5; /* offset : 0xe7c */
	union hbm3ephy_sw_prbs_offsetw6 sw_prbs_offsetw6; /* offset : 0xe80 */
	union hbm3ephy_sw_prbs_offsetw7 sw_prbs_offsetw7; /* offset : 0xe84 */
	union hbm3ephy_sw_prbs_offsetw8 sw_prbs_offsetw8; /* offset : 0xe88 */
	union hbm3ephy_sw_prbs_offsetw9 sw_prbs_offsetw9; /* offset : 0xe8c */
	union hbm3ephy_sw_prbs_offsetw10 sw_prbs_offsetw10; /* offset : 0xe90 */
	union hbm3ephy_sw_prbs_offsetw11 sw_prbs_offsetw11; /* offset : 0xe94 */
	union hbm3ephy_sw_prbs_offsetw12 sw_prbs_offsetw12; /* offset : 0xe98 */
	union hbm3ephy_sw_prbs_offsetw13 sw_prbs_offsetw13; /* offset : 0xe9c */
	union hbm3ephy_sw_prbs_offsetw14 sw_prbs_offsetw14; /* offset : 0xea0 */
	union hbm3ephy_sw_prbs_offsetw15 sw_prbs_offsetw15; /* offset : 0xea4 */
	union hbm3ephy_sw_prbs_offsetw16 sw_prbs_offsetw16; /* offset : 0xea8 */
	union hbm3ephy_sw_prbs_offsetw17 sw_prbs_offsetw17; /* offset : 0xeac */
	union hbm3ephy_sw_prbs_offsetw18 sw_prbs_offsetw18; /* offset : 0xeb0 */
	union hbm3ephy_sw_prbs_offsetw19 sw_prbs_offsetw19; /* offset : 0xeb4 */
	union hbm3ephy_sw_prbs_offsetw20 sw_prbs_offsetw20; /* offset : 0xeb8 */
	union hbm3ephy_sw_prbs_offsetw21 sw_prbs_offsetw21; /* offset : 0xebc */
	union hbm3ephy_sw_prbs_offsetw22 sw_prbs_offsetw22; /* offset : 0xec0 */
	union hbm3ephy_sw_prbs_offsetw23 sw_prbs_offsetw23; /* offset : 0xec4 */
	union hbm3ephy_sw_prbs_offsetw24 sw_prbs_offsetw24; /* offset : 0xec8 */
	union hbm3ephy_sw_prbs_offsetw25 sw_prbs_offsetw25; /* offset : 0xecc */
	union hbm3ephy_prbs_left_margin0 prbs_left_margin0; /* offset : 0xed0 */
	union hbm3ephy_prbs_left_margin1 prbs_left_margin1; /* offset : 0xed4 */
	union hbm3ephy_prbs_left_margin2 prbs_left_margin2; /* offset : 0xed8 */
	union hbm3ephy_prbs_left_margin3 prbs_left_margin3; /* offset : 0xedc */
	union hbm3ephy_prbs_left_margin4 prbs_left_margin4; /* offset : 0xee0 */
	union hbm3ephy_prbs_left_margin5 prbs_left_margin5; /* offset : 0xee4 */
	union hbm3ephy_prbs_left_margin6 prbs_left_margin6; /* offset : 0xee8 */
	union hbm3ephy_prbs_left_margin7 prbs_left_margin7; /* offset : 0xeec */
	union hbm3ephy_prbs_left_margin8 prbs_left_margin8; /* offset : 0xef0 */
	union hbm3ephy_prbs_left_margin9 prbs_left_margin9; /* offset : 0xef4 */
	union hbm3ephy_prbs_left_margin10 prbs_left_margin10; /* offset : 0xef8 */
	union hbm3ephy_prbs_left_margin11 prbs_left_margin11; /* offset : 0xefc */
	union hbm3ephy_prbs_left_margin12 prbs_left_margin12; /* offset : 0xf00 */
	union hbm3ephy_prbs_left_margin13 prbs_left_margin13; /* offset : 0xf04 */
	union hbm3ephy_prbs_left_margin14 prbs_left_margin14; /* offset : 0xf08 */
	union hbm3ephy_prbs_left_margin15 prbs_left_margin15; /* offset : 0xf0c */
	union hbm3ephy_prbs_left_margin16 prbs_left_margin16; /* offset : 0xf10 */
	union hbm3ephy_prbs_left_margin17 prbs_left_margin17; /* offset : 0xf14 */
	union hbm3ephy_prbs_left_margin18 prbs_left_margin18; /* offset : 0xf18 */
	union hbm3ephy_prbs_left_margin19 prbs_left_margin19; /* offset : 0xf1c */
	union hbm3ephy_prbs_left_margin20 prbs_left_margin20; /* offset : 0xf20 */
	union hbm3ephy_prbs_left_margin21 prbs_left_margin21; /* offset : 0xf24 */
	union hbm3ephy_prbs_left_margin22 prbs_left_margin22; /* offset : 0xf28 */
	union hbm3ephy_prbs_left_margin23 prbs_left_margin23; /* offset : 0xf2c */
	union hbm3ephy_prbs_left_margin24 prbs_left_margin24; /* offset : 0xf30 */
	union hbm3ephy_prbs_left_margin25 prbs_left_margin25; /* offset : 0xf34 */
	union hbm3ephy_prbs_right_margin0 prbs_right_margin0; /* offset : 0xf38 */
	union hbm3ephy_prbs_right_margin1 prbs_right_margin1; /* offset : 0xf3c */
	union hbm3ephy_prbs_right_margin2 prbs_right_margin2; /* offset : 0xf40 */
	union hbm3ephy_prbs_right_margin3 prbs_right_margin3; /* offset : 0xf44 */
	union hbm3ephy_prbs_right_margin4 prbs_right_margin4; /* offset : 0xf48 */
	union hbm3ephy_prbs_right_margin5 prbs_right_margin5; /* offset : 0xf4c */
	union hbm3ephy_prbs_right_margin6 prbs_right_margin6; /* offset : 0xf50 */
	union hbm3ephy_prbs_right_margin7 prbs_right_margin7; /* offset : 0xf54 */
	union hbm3ephy_prbs_right_margin8 prbs_right_margin8; /* offset : 0xf58 */
	union hbm3ephy_prbs_right_margin9 prbs_right_margin9; /* offset : 0xf5c */
	union hbm3ephy_prbs_right_margin10 prbs_right_margin10; /* offset : 0xf60 */
	union hbm3ephy_prbs_right_margin11 prbs_right_margin11; /* offset : 0xf64 */
	union hbm3ephy_prbs_right_margin12 prbs_right_margin12; /* offset : 0xf68 */
	union hbm3ephy_prbs_right_margin13 prbs_right_margin13; /* offset : 0xf6c */
	union hbm3ephy_prbs_right_margin14 prbs_right_margin14; /* offset : 0xf70 */
	union hbm3ephy_prbs_right_margin15 prbs_right_margin15; /* offset : 0xf74 */
	union hbm3ephy_prbs_right_margin16 prbs_right_margin16; /* offset : 0xf78 */
	union hbm3ephy_prbs_right_margin17 prbs_right_margin17; /* offset : 0xf7c */
	union hbm3ephy_prbs_right_margin18 prbs_right_margin18; /* offset : 0xf80 */
	union hbm3ephy_prbs_right_margin19 prbs_right_margin19; /* offset : 0xf84 */
	union hbm3ephy_prbs_right_margin20 prbs_right_margin20; /* offset : 0xf88 */
	union hbm3ephy_prbs_right_margin21 prbs_right_margin21; /* offset : 0xf8c */
	union hbm3ephy_prbs_right_margin22 prbs_right_margin22; /* offset : 0xf90 */
	union hbm3ephy_prbs_right_margin23 prbs_right_margin23; /* offset : 0xf94 */
	union hbm3ephy_prbs_right_margin24 prbs_right_margin24; /* offset : 0xf98 */
	union hbm3ephy_prbs_right_margin25 prbs_right_margin25; /* offset : 0xf9c */
	union hbm3ephy_cal_seed_con0 cal_seed_con0; /* offset : 0xfa0 */
	union hbm3ephy_cal_seed_con1 cal_seed_con1; /* offset : 0xfa4 */
	union hbm3ephy_cal_seed_con2 cal_seed_con2; /* offset : 0xfa8 */
	union hbm3ephy_cal_seed_con3 cal_seed_con3; /* offset : 0xfac */
	union hbm3ephy_cal_seed_con4 cal_seed_con4; /* offset : 0xfb0 */
	union hbm3ephy_cal_seed_con5 cal_seed_con5; /* offset : 0xfb4 */
	union hbm3ephy_cal_seed_con6 cal_seed_con6; /* offset : 0xfb8 */
	union hbm3ephy_cal_seed_con7 cal_seed_con7; /* offset : 0xfbc */
	union hbm3ephy_cal_seed_con8 cal_seed_con8; /* offset : 0xfc0 */
	union hbm3ephy_cal_seed_con9 cal_seed_con9; /* offset : 0xfc4 */
	union hbm3ephy_dcm_con0 evt1_dcm_con0; /* offset : 0xfc8 */ /* EVT1 only */
	union hbm3ephy_wr_dq0_deskewl_code0 evt1_wr_dq0_deskewl_code0; /* offset : 0xfcc */ /* EVT1 only */
	union hbm3ephy_wr_dq1_deskewl_code0 evt1_wr_dq1_deskewl_code0; /* offset : 0xfd0 */ /* EVT1 only */
	union hbm3ephy_wr_dq2_deskewl_code0 evt1_wr_dq2_deskewl_code0; /* offset : 0xfd4 */ /* EVT1 only */
	union hbm3ephy_wr_dq3_deskewl_code0 evt1_wr_dq3_deskewl_code0; /* offset : 0xfd8 */ /* EVT1 only */
	union hbm3ephy_wr_dq4_deskewl_code0 evt1_wr_dq4_deskewl_code0; /* offset : 0xfdc */ /* EVT1 only */
	union hbm3ephy_wr_dq5_deskewl_code0 evt1_wr_dq5_deskewl_code0; /* offset : 0xfe0 */ /* EVT1 only */
	union hbm3ephy_wr_dq6_deskewl_code0 evt1_wr_dq6_deskewl_code0; /* offset : 0xfe4 */ /* EVT1 only */
	union hbm3ephy_wr_dq7_deskewl_code0 evt1_wr_dq7_deskewl_code0; /* offset : 0xfe8 */ /* EVT1 only */
	union hbm3ephy_wr_dq8_deskewl_code0 evt1_wr_dq8_deskewl_code0; /* offset : 0xfec */ /* EVT1 only */
	union hbm3ephy_wr_dq9_deskewl_code0 evt1_wr_dq9_deskewl_code0; /* offset : 0xff0 */ /* EVT1 only */
	union hbm3ephy_wr_dq10_deskewl_code0 evt1_wr_dq10_deskewl_code0; /* offset : 0xff4 */ /* EVT1 only */
	union hbm3ephy_wr_dq11_deskewl_code0 evt1_wr_dq11_deskewl_code0; /* offset : 0xff8 */ /* EVT1 only */
	union hbm3ephy_wr_dq12_deskewl_code0 evt1_wr_dq12_deskewl_code0; /* offset : 0xffc */ /* EVT1 only */
	union hbm3ephy_wr_dq13_deskewl_code0 evt1_wr_dq13_deskewl_code0; /* offset : 0x1000 */ /* EVT1 only */
	union hbm3ephy_wr_dq14_deskewl_code0 evt1_wr_dq14_deskewl_code0; /* offset : 0x1004 */ /* EVT1 only */
	union hbm3ephy_wr_dq15_deskewl_code0 evt1_wr_dq15_deskewl_code0; /* offset : 0x1008 */ /* EVT1 only */
	union hbm3ephy_wr_dq16_deskewl_code0 evt1_wr_dq16_deskewl_code0; /* offset : 0x100c */ /* EVT1 only */
	union hbm3ephy_wr_dq17_deskewl_code0 evt1_wr_dq17_deskewl_code0; /* offset : 0x1010 */ /* EVT1 only */
	union hbm3ephy_wr_dq18_deskewl_code0 evt1_wr_dq18_deskewl_code0; /* offset : 0x1014 */ /* EVT1 only */
	union hbm3ephy_wr_dq19_deskewl_code0 evt1_wr_dq19_deskewl_code0; /* offset : 0x1018 */ /* EVT1 only */
	union hbm3ephy_wr_dq20_deskewl_code0 evt1_wr_dq20_deskewl_code0; /* offset : 0x101c */ /* EVT1 only */
	union hbm3ephy_wr_dq21_deskewl_code0 evt1_wr_dq21_deskewl_code0; /* offset : 0x1020 */ /* EVT1 only */
	union hbm3ephy_wr_dq22_deskewl_code0 evt1_wr_dq22_deskewl_code0; /* offset : 0x1024 */ /* EVT1 only */
	union hbm3ephy_wr_dq23_deskewl_code0 evt1_wr_dq23_deskewl_code0; /* offset : 0x1028 */ /* EVT1 only */
	union hbm3ephy_wr_dq24_deskewl_code0 evt1_wr_dq24_deskewl_code0; /* offset : 0x102c */ /* EVT1 only */
	union hbm3ephy_wr_dq25_deskewl_code0 evt1_wr_dq25_deskewl_code0; /* offset : 0x1030 */ /* EVT1 only */
	union hbm3ephy_wr_dq26_deskewl_code0 evt1_wr_dq26_deskewl_code0; /* offset : 0x1034 */ /* EVT1 only */
	union hbm3ephy_wr_dq27_deskewl_code0 evt1_wr_dq27_deskewl_code0; /* offset : 0x1038 */ /* EVT1 only */
	union hbm3ephy_wr_dq28_deskewl_code0 evt1_wr_dq28_deskewl_code0; /* offset : 0x103c */ /* EVT1 only */
	union hbm3ephy_wr_dq29_deskewl_code0 evt1_wr_dq29_deskewl_code0; /* offset : 0x1040 */ /* EVT1 only */
	union hbm3ephy_wr_dq30_deskewl_code0 evt1_wr_dq30_deskewl_code0; /* offset : 0x1044 */ /* EVT1 only */
	union hbm3ephy_wr_dq31_deskewl_code0 evt1_wr_dq31_deskewl_code0; /* offset : 0x1048 */ /* EVT1 only */
	union hbm3ephy_wr_ecc0_deskewl_code0 evt1_wr_ecc0_deskewl_code0; /* offset : 0x104c */ /* EVT1 only */
	union hbm3ephy_wr_ecc1_deskewl_code0 evt1_wr_ecc1_deskewl_code0; /* offset : 0x1050 */ /* EVT1 only */
	union hbm3ephy_wr_sev0_deskewl_code0 evt1_wr_sev0_deskewl_code0; /* offset : 0x1054 */ /* EVT1 only */
	union hbm3ephy_wr_sev1_deskewl_code0 evt1_wr_sev1_deskewl_code0; /* offset : 0x1058 */ /* EVT1 only */
	union hbm3ephy_wr_dbi0_deskewl_code0 evt1_wr_dbi0_deskewl_code0; /* offset : 0x105c */ /* EVT1 only */
	union hbm3ephy_wr_dbi1_deskewl_code0 evt1_wr_dbi1_deskewl_code0; /* offset : 0x1060 */ /* EVT1 only */
	union hbm3ephy_wr_dbi2_deskewl_code0 evt1_wr_dbi2_deskewl_code0; /* offset : 0x1064 */ /* EVT1 only */
	union hbm3ephy_wr_dbi3_deskewl_code0 evt1_wr_dbi3_deskewl_code0; /* offset : 0x1068 */ /* EVT1 only */
	union hbm3ephy_wr_par_deskewl_code0 evt1_wr_par_deskewl_code0; /* offset : 0x106c */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq0_deskewl_code0 evt1_sw_wr_dq0_deskewl_code0; /* offset : 0x1070 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq1_deskewl_code0 evt1_sw_wr_dq1_deskewl_code0; /* offset : 0x1074 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq2_deskewl_code0 evt1_sw_wr_dq2_deskewl_code0; /* offset : 0x1078 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq3_deskewl_code0 evt1_sw_wr_dq3_deskewl_code0; /* offset : 0x107c */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq4_deskewl_code0 evt1_sw_wr_dq4_deskewl_code0; /* offset : 0x1080 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq5_deskewl_code0 evt1_sw_wr_dq5_deskewl_code0; /* offset : 0x1084 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq6_deskewl_code0 evt1_sw_wr_dq6_deskewl_code0; /* offset : 0x1088 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq7_deskewl_code0 evt1_sw_wr_dq7_deskewl_code0; /* offset : 0x108c */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq8_deskewl_code0 evt1_sw_wr_dq8_deskewl_code0; /* offset : 0x1090 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq9_deskewl_code0 evt1_sw_wr_dq9_deskewl_code0; /* offset : 0x1094 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq10_deskewl_code0 evt1_sw_wr_dq10_deskewl_code0; /* offset : 0x1098 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq11_deskewl_code0 evt1_sw_wr_dq11_deskewl_code0; /* offset : 0x109c */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq12_deskewl_code0 evt1_sw_wr_dq12_deskewl_code0; /* offset : 0x10a0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq13_deskewl_code0 evt1_sw_wr_dq13_deskewl_code0; /* offset : 0x10a4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq14_deskewl_code0 evt1_sw_wr_dq14_deskewl_code0; /* offset : 0x10a8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq15_deskewl_code0 evt1_sw_wr_dq15_deskewl_code0; /* offset : 0x10ac */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq16_deskewl_code0 evt1_sw_wr_dq16_deskewl_code0; /* offset : 0x10b0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq17_deskewl_code0 evt1_sw_wr_dq17_deskewl_code0; /* offset : 0x10b4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq18_deskewl_code0 evt1_sw_wr_dq18_deskewl_code0; /* offset : 0x10b8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq19_deskewl_code0 evt1_sw_wr_dq19_deskewl_code0; /* offset : 0x10bc */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq20_deskewl_code0 evt1_sw_wr_dq20_deskewl_code0; /* offset : 0x10c0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq21_deskewl_code0 evt1_sw_wr_dq21_deskewl_code0; /* offset : 0x10c4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq22_deskewl_code0 evt1_sw_wr_dq22_deskewl_code0; /* offset : 0x10c8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq23_deskewl_code0 evt1_sw_wr_dq23_deskewl_code0; /* offset : 0x10cc */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq24_deskewl_code0 evt1_sw_wr_dq24_deskewl_code0; /* offset : 0x10d0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq25_deskewl_code0 evt1_sw_wr_dq25_deskewl_code0; /* offset : 0x10d4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq26_deskewl_code0 evt1_sw_wr_dq26_deskewl_code0; /* offset : 0x10d8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq27_deskewl_code0 evt1_sw_wr_dq27_deskewl_code0; /* offset : 0x10dc */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq28_deskewl_code0 evt1_sw_wr_dq28_deskewl_code0; /* offset : 0x10e0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq29_deskewl_code0 evt1_sw_wr_dq29_deskewl_code0; /* offset : 0x10e4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq30_deskewl_code0 evt1_sw_wr_dq30_deskewl_code0; /* offset : 0x10e8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dq31_deskewl_code0 evt1_sw_wr_dq31_deskewl_code0; /* offset : 0x10ec */ /* EVT1 only */
	union hbm3ephy_sw_wr_ecc0_deskewl_code0 evt1_sw_wr_ecc0_deskewl_code0; /* offset : 0x10f0 */ /* EVT1 only */
	union hbm3ephy_sw_wr_ecc1_deskewl_code0 evt1_sw_wr_ecc1_deskewl_code0; /* offset : 0x10f4 */ /* EVT1 only */
	union hbm3ephy_sw_wr_sev0_deskewl_code0 evt1_sw_wr_sev0_deskewl_code0; /* offset : 0x10f8 */ /* EVT1 only */
	union hbm3ephy_sw_wr_sev1_deskewl_code0 evt1_sw_wr_sev1_deskewl_code0; /* offset : 0x10fc */ /* EVT1 only */
	union hbm3ephy_sw_wr_dbi0_deskewl_code0 evt1_sw_wr_dbi0_deskewl_code0; /* offset : 0x1100 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dbi1_deskewl_code0 evt1_sw_wr_dbi1_deskewl_code0; /* offset : 0x1104 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dbi2_deskewl_code0 evt1_sw_wr_dbi2_deskewl_code0; /* offset : 0x1108 */ /* EVT1 only */
	union hbm3ephy_sw_wr_dbi3_deskewl_code0 evt1_sw_wr_dbi3_deskewl_code0; /* offset : 0x110c */ /* EVT1 only */
	union hbm3ephy_sw_wr_par_deskewl_code0 evt1_sw_wr_par_deskewl_code0; /* offset : 0x1110 */ /* EVT1 only */
	union hbm3ephy_sw_dcm_con0 evt1_sw_dcm_con0; /* offset : 0x1114 */ /* EVT1 only */
	union hbm3ephy_rd_dq0_deskewr_code0 evt1_rd_dq0_deskewr_code0; /* offset : 0x1118 */ /* EVT1 only */
	union hbm3ephy_rd_dq1_deskewr_code0 evt1_rd_dq1_deskewr_code0; /* offset : 0x111c */ /* EVT1 only */
	union hbm3ephy_rd_dq2_deskewr_code0 evt1_rd_dq2_deskewr_code0; /* offset : 0x1120 */ /* EVT1 only */
	union hbm3ephy_rd_dq3_deskewr_code0 evt1_rd_dq3_deskewr_code0; /* offset : 0x1124 */ /* EVT1 only */
	union hbm3ephy_rd_dq4_deskewr_code0 evt1_rd_dq4_deskewr_code0; /* offset : 0x1128 */ /* EVT1 only */
	union hbm3ephy_rd_dq5_deskewr_code0 evt1_rd_dq5_deskewr_code0; /* offset : 0x112c */ /* EVT1 only */
	union hbm3ephy_rd_dq6_deskewr_code0 evt1_rd_dq6_deskewr_code0; /* offset : 0x1130 */ /* EVT1 only */
	union hbm3ephy_rd_dq7_deskewr_code0 evt1_rd_dq7_deskewr_code0; /* offset : 0x1134 */ /* EVT1 only */
	union hbm3ephy_rd_dq8_deskewr_code0 evt1_rd_dq8_deskewr_code0; /* offset : 0x1138 */ /* EVT1 only */
	union hbm3ephy_rd_dq9_deskewr_code0 evt1_rd_dq9_deskewr_code0; /* offset : 0x113c */ /* EVT1 only */
	union hbm3ephy_rd_dq10_deskewr_code0 evt1_rd_dq10_deskewr_code0; /* offset : 0x1140 */ /* EVT1 only */
	union hbm3ephy_rd_dq11_deskewr_code0 evt1_rd_dq11_deskewr_code0; /* offset : 0x1144 */ /* EVT1 only */
	union hbm3ephy_rd_dq12_deskewr_code0 evt1_rd_dq12_deskewr_code0; /* offset : 0x1148 */ /* EVT1 only */
	union hbm3ephy_rd_dq13_deskewr_code0 evt1_rd_dq13_deskewr_code0; /* offset : 0x114c */ /* EVT1 only */
	union hbm3ephy_rd_dq14_deskewr_code0 evt1_rd_dq14_deskewr_code0; /* offset : 0x1150 */ /* EVT1 only */
	union hbm3ephy_rd_dq15_deskewr_code0 evt1_rd_dq15_deskewr_code0; /* offset : 0x1154 */ /* EVT1 only */
	union hbm3ephy_rd_dq16_deskewr_code0 evt1_rd_dq16_deskewr_code0; /* offset : 0x1158 */ /* EVT1 only */
	union hbm3ephy_rd_dq17_deskewr_code0 evt1_rd_dq17_deskewr_code0; /* offset : 0x115c */ /* EVT1 only */
	union hbm3ephy_rd_dq18_deskewr_code0 evt1_rd_dq18_deskewr_code0; /* offset : 0x1160 */ /* EVT1 only */
	union hbm3ephy_rd_dq19_deskewr_code0 evt1_rd_dq19_deskewr_code0; /* offset : 0x1164 */ /* EVT1 only */
	union hbm3ephy_rd_dq20_deskewr_code0 evt1_rd_dq20_deskewr_code0; /* offset : 0x1168 */ /* EVT1 only */
	union hbm3ephy_rd_dq21_deskewr_code0 evt1_rd_dq21_deskewr_code0; /* offset : 0x116c */ /* EVT1 only */
	union hbm3ephy_rd_dq22_deskewr_code0 evt1_rd_dq22_deskewr_code0; /* offset : 0x1170 */ /* EVT1 only */
	union hbm3ephy_rd_dq23_deskewr_code0 evt1_rd_dq23_deskewr_code0; /* offset : 0x1174 */ /* EVT1 only */
	union hbm3ephy_rd_dq24_deskewr_code0 evt1_rd_dq24_deskewr_code0; /* offset : 0x1178 */ /* EVT1 only */
	union hbm3ephy_rd_dq25_deskewr_code0 evt1_rd_dq25_deskewr_code0; /* offset : 0x117c */ /* EVT1 only */
	union hbm3ephy_rd_dq26_deskewr_code0 evt1_rd_dq26_deskewr_code0; /* offset : 0x1180 */ /* EVT1 only */
	union hbm3ephy_rd_dq27_deskewr_code0 evt1_rd_dq27_deskewr_code0; /* offset : 0x1184 */ /* EVT1 only */
	union hbm3ephy_rd_dq28_deskewr_code0 evt1_rd_dq28_deskewr_code0; /* offset : 0x1188 */ /* EVT1 only */
	union hbm3ephy_rd_dq29_deskewr_code0 evt1_rd_dq29_deskewr_code0; /* offset : 0x118c */ /* EVT1 only */
	union hbm3ephy_rd_dq30_deskewr_code0 evt1_rd_dq30_deskewr_code0; /* offset : 0x1190 */ /* EVT1 only */
	union hbm3ephy_rd_dq31_deskewr_code0 evt1_rd_dq31_deskewr_code0; /* offset : 0x1194 */ /* EVT1 only */
	union hbm3ephy_rd_ecc0_deskewr_code0 evt1_rd_ecc0_deskewr_code0; /* offset : 0x1198 */ /* EVT1 only */
	union hbm3ephy_rd_ecc1_deskewr_code0 evt1_rd_ecc1_deskewr_code0; /* offset : 0x119c */ /* EVT1 only */
	union hbm3ephy_rd_sev0_deskewr_code0 evt1_rd_sev0_deskewr_code0; /* offset : 0x11a0 */ /* EVT1 only */
	union hbm3ephy_rd_sev1_deskewr_code0 evt1_rd_sev1_deskewr_code0; /* offset : 0x11a4 */ /* EVT1 only */
	union hbm3ephy_rd_dbi0_deskewr_code0 evt1_rd_dbi0_deskewr_code0; /* offset : 0x11a8 */ /* EVT1 only */
	union hbm3ephy_rd_dbi1_deskewr_code0 evt1_rd_dbi1_deskewr_code0; /* offset : 0x11ac */ /* EVT1 only */
	union hbm3ephy_rd_dbi2_deskewr_code0 evt1_rd_dbi2_deskewr_code0; /* offset : 0x11b0 */ /* EVT1 only */
	union hbm3ephy_rd_dbi3_deskewr_code0 evt1_rd_dbi3_deskewr_code0; /* offset : 0x11b4 */ /* EVT1 only */
	union hbm3ephy_rd_par_deskewr_code0 evt1_rd_par_deskewr_code0; /* offset : 0x11b8 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq0_deskewr_code0 evt1_sw_rd_dq0_deskewr_code0; /* offset : 0x11bc */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq1_deskewr_code0 evt1_sw_rd_dq1_deskewr_code0; /* offset : 0x11c0 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq2_deskewr_code0 evt1_sw_rd_dq2_deskewr_code0; /* offset : 0x11c4 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq3_deskewr_code0 evt1_sw_rd_dq3_deskewr_code0; /* offset : 0x11c8 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq4_deskewr_code0 evt1_sw_rd_dq4_deskewr_code0; /* offset : 0x11cc */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq5_deskewr_code0 evt1_sw_rd_dq5_deskewr_code0; /* offset : 0x11d0 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq6_deskewr_code0 evt1_sw_rd_dq6_deskewr_code0; /* offset : 0x11d4 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq7_deskewr_code0 evt1_sw_rd_dq7_deskewr_code0; /* offset : 0x11d8 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq8_deskewr_code0 evt1_sw_rd_dq8_deskewr_code0; /* offset : 0x11dc */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq9_deskewr_code0 evt1_sw_rd_dq9_deskewr_code0; /* offset : 0x11e0 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq10_deskewr_code0 evt1_sw_rd_dq10_deskewr_code0; /* offset : 0x11e4 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq11_deskewr_code0 evt1_sw_rd_dq11_deskewr_code0; /* offset : 0x11e8 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq12_deskewr_code0 evt1_sw_rd_dq12_deskewr_code0; /* offset : 0x11ec */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq13_deskewr_code0 evt1_sw_rd_dq13_deskewr_code0; /* offset : 0x11f0 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq14_deskewr_code0 evt1_sw_rd_dq14_deskewr_code0; /* offset : 0x11f4 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq15_deskewr_code0 evt1_sw_rd_dq15_deskewr_code0; /* offset : 0x11f8 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq16_deskewr_code0 evt1_sw_rd_dq16_deskewr_code0; /* offset : 0x11fc */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq17_deskewr_code0 evt1_sw_rd_dq17_deskewr_code0; /* offset : 0x1200 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq18_deskewr_code0 evt1_sw_rd_dq18_deskewr_code0; /* offset : 0x1204 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq19_deskewr_code0 evt1_sw_rd_dq19_deskewr_code0; /* offset : 0x1208 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq20_deskewr_code0 evt1_sw_rd_dq20_deskewr_code0; /* offset : 0x120c */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq21_deskewr_code0 evt1_sw_rd_dq21_deskewr_code0; /* offset : 0x1210 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq22_deskewr_code0 evt1_sw_rd_dq22_deskewr_code0; /* offset : 0x1214 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq23_deskewr_code0 evt1_sw_rd_dq23_deskewr_code0; /* offset : 0x1218 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq24_deskewr_code0 evt1_sw_rd_dq24_deskewr_code0; /* offset : 0x121c */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq25_deskewr_code0 evt1_sw_rd_dq25_deskewr_code0; /* offset : 0x1220 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq26_deskewr_code0 evt1_sw_rd_dq26_deskewr_code0; /* offset : 0x1224 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq27_deskewr_code0 evt1_sw_rd_dq27_deskewr_code0; /* offset : 0x1228 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq28_deskewr_code0 evt1_sw_rd_dq28_deskewr_code0; /* offset : 0x122c */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq29_deskewr_code0 evt1_sw_rd_dq29_deskewr_code0; /* offset : 0x1230 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq30_deskewr_code0 evt1_sw_rd_dq30_deskewr_code0; /* offset : 0x1234 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dq31_deskewr_code0 evt1_sw_rd_dq31_deskewr_code0; /* offset : 0x1238 */ /* EVT1 only */
	union hbm3ephy_sw_rd_ecc0_deskewr_code0 evt1_sw_rd_ecc0_deskewr_code0; /* offset : 0x123c */ /* EVT1 only */
	union hbm3ephy_sw_rd_ecc1_deskewr_code0 evt1_sw_rd_ecc1_deskewr_code0; /* offset : 0x1240 */ /* EVT1 only */
	union hbm3ephy_sw_rd_sev0_deskewr_code0 evt1_sw_rd_sev0_deskewr_code0; /* offset : 0x1244 */ /* EVT1 only */
	union hbm3ephy_sw_rd_sev1_deskewr_code0 evt1_sw_rd_sev1_deskewr_code0; /* offset : 0x1248 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dbi0_deskewr_code0 evt1_sw_rd_dbi0_deskewr_code0; /* offset : 0x124c */ /* EVT1 only */
	union hbm3ephy_sw_rd_dbi1_deskewr_code0 evt1_sw_rd_dbi1_deskewr_code0; /* offset : 0x1250 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dbi2_deskewr_code0 evt1_sw_rd_dbi2_deskewr_code0; /* offset : 0x1254 */ /* EVT1 only */
	union hbm3ephy_sw_rd_dbi3_deskewr_code0 evt1_sw_rd_dbi3_deskewr_code0; /* offset : 0x1258 */ /* EVT1 only */
	union hbm3ephy_sw_rd_par_deskewr_code0 evt1_sw_rd_par_deskewr_code0; /* offset : 0x125c */ /* EVT1 only */
};

