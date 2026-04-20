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

union ieee1500_icon_icon_ctrl_con0 {
	struct {
		uint32_t ctrl_wrck_en:1; /* [0:0] */
		uint32_t sw_mode:1; /* [1:1] */
		uint32_t sw_fsm_mode:3; /* [4:2] */
		uint32_t sw_wir:13; /* [17:5] */
		uint32_t sw_shiftwr_wdr_dur:11; /* [28:18] */
		uint32_t sw_mode_req:1; /* [29:29] */
		uint32_t phy_ctrl_mode:1; /* [30:30] */
		uint32_t wrst_n:1; /* [31:31] */
	};
	uint32_t val;
};

union ieee1500_icon_icon_ctrl_con1 {
	struct {
		uint32_t wir_width:4; /* [3:0] */
		uint32_t icon_wrstn_mode:1; /* [4:4] */
		uint32_t reserved0:27; /* [31:5] */
	};
	uint32_t val;
};

union ieee1500_icon_test_instruction_req0 {
	struct {
		uint32_t bypass_req:1; /* [0:0] */
		uint32_t extest_rx_req:1; /* [1:1] */
		uint32_t extest_tx_req:1; /* [2:2] */
		uint32_t hbm_reset_req:1; /* [3:3] */
		uint32_t mbist_req:1; /* [4:4] */
		uint32_t soft_repair_req:1; /* [5:5] */
		uint32_t hard_repair_req:1; /* [6:6] */
		uint32_t dword_misr_mode_req:1; /* [7:7] */
		uint32_t dword_misr_read_req:1; /* [8:8] */
		uint32_t dword_misr_write_req:1; /* [9:9] */
		uint32_t aword_misr_mode_req:1; /* [10:10] */
		uint32_t aword_misr_read_req:1; /* [11:11] */
		uint32_t channel_id_req:1; /* [12:12] */
		uint32_t aword_misr_config_req:1; /* [13:13] */
		uint32_t device_id_req:1; /* [14:14] */
		uint32_t temperature_req:1; /* [15:15] */
		uint32_t mr_dump_set_read_req:1; /* [16:16] */
		uint32_t mr_dump_set_write_req:1; /* [17:17] */
		uint32_t read_lfsr_cmp_sticky_req:1; /* [18:18] */
		uint32_t soft_lane_repair_read_req:1; /* [19:19] */
		uint32_t soft_lane_repair_write_req:1; /* [20:20] */
		uint32_t hard_lane_repair_read_req:1; /* [21:21] */
		uint32_t hard_lane_repair_write_req:1; /* [22:22] */
		uint32_t channel_disable_req:1; /* [23:23] */
		uint32_t channel_temp_req:1; /* [24:24] */
		uint32_t wosc_run_req:1; /* [25:25] */
		uint32_t wosc_count_req:1; /* [26:26] */
		uint32_t ecs_error_log_req:1; /* [27:27] */
		uint32_t hs_rep_cap_req:1; /* [28:28] */
		uint32_t self_rep_read_req:1; /* [29:29] */
		uint32_t self_rep_write_req:1; /* [30:30] */
		uint32_t self_rep_results_req:1; /* [31:31] */
	};
	uint32_t val;
};

union ieee1500_icon_test_instruction_req1 {
	struct {
		uint32_t ch_select:5; /* [4:0] */
		uint32_t test_done:1; /* [5:5] */
		uint32_t reserved0:26; /* [31:6] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr18 {
	struct {
		uint32_t wr_wdr18; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr17 {
	struct {
		uint32_t wr_wdr17; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr16 {
	struct {
		uint32_t wr_wdr16; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr15 {
	struct {
		uint32_t wr_wdr15; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr14 {
	struct {
		uint32_t wr_wdr14; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr13 {
	struct {
		uint32_t wr_wdr13; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr12 {
	struct {
		uint32_t wr_wdr12; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr11 {
	struct {
		uint32_t wr_wdr11; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr10 {
	struct {
		uint32_t wr_wdr10; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr9 {
	struct {
		uint32_t wr_wdr9; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr8 {
	struct {
		uint32_t wr_wdr8; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr7 {
	struct {
		uint32_t wr_wdr7; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr6 {
	struct {
		uint32_t wr_wdr6; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr5 {
	struct {
		uint32_t wr_wdr5; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr4 {
	struct {
		uint32_t wr_wdr4; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr3 {
	struct {
		uint32_t wr_wdr3; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr2 {
	struct {
		uint32_t wr_wdr2; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr1 {
	struct {
		uint32_t wr_wdr1; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_wr_wdr0 {
	struct {
		uint32_t wr_wdr0; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_a {
	struct {
		uint32_t rd_wdr18_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_a {
	struct {
		uint32_t rd_wdr17_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_a {
	struct {
		uint32_t rd_wdr16_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_a {
	struct {
		uint32_t rd_wdr15_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_a {
	struct {
		uint32_t rd_wdr14_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_a {
	struct {
		uint32_t rd_wdr13_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_a {
	struct {
		uint32_t rd_wdr12_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_a {
	struct {
		uint32_t rd_wdr11_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_a {
	struct {
		uint32_t rd_wdr10_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_a {
	struct {
		uint32_t rd_wdr9_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_a {
	struct {
		uint32_t rd_wdr8_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_a {
	struct {
		uint32_t rd_wdr7_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_a {
	struct {
		uint32_t rd_wdr6_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_a {
	struct {
		uint32_t rd_wdr5_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_a {
	struct {
		uint32_t rd_wdr4_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_a {
	struct {
		uint32_t rd_wdr3_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_a {
	struct {
		uint32_t rd_wdr2_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_a {
	struct {
		uint32_t rd_wdr1_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_a {
	struct {
		uint32_t rd_wdr0_ch_a; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_b {
	struct {
		uint32_t rd_wdr18_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_b {
	struct {
		uint32_t rd_wdr17_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_b {
	struct {
		uint32_t rd_wdr16_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_b {
	struct {
		uint32_t rd_wdr15_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_b {
	struct {
		uint32_t rd_wdr14_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_b {
	struct {
		uint32_t rd_wdr13_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_b {
	struct {
		uint32_t rd_wdr12_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_b {
	struct {
		uint32_t rd_wdr11_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_b {
	struct {
		uint32_t rd_wdr10_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_b {
	struct {
		uint32_t rd_wdr9_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_b {
	struct {
		uint32_t rd_wdr8_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_b {
	struct {
		uint32_t rd_wdr7_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_b {
	struct {
		uint32_t rd_wdr6_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_b {
	struct {
		uint32_t rd_wdr5_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_b {
	struct {
		uint32_t rd_wdr4_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_b {
	struct {
		uint32_t rd_wdr3_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_b {
	struct {
		uint32_t rd_wdr2_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_b {
	struct {
		uint32_t rd_wdr1_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_b {
	struct {
		uint32_t rd_wdr0_ch_b; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_c {
	struct {
		uint32_t rd_wdr18_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_c {
	struct {
		uint32_t rd_wdr17_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_c {
	struct {
		uint32_t rd_wdr16_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_c {
	struct {
		uint32_t rd_wdr15_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_c {
	struct {
		uint32_t rd_wdr14_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_c {
	struct {
		uint32_t rd_wdr13_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_c {
	struct {
		uint32_t rd_wdr12_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_c {
	struct {
		uint32_t rd_wdr11_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_c {
	struct {
		uint32_t rd_wdr10_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_c {
	struct {
		uint32_t rd_wdr9_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_c {
	struct {
		uint32_t rd_wdr8_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_c {
	struct {
		uint32_t rd_wdr7_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_c {
	struct {
		uint32_t rd_wdr6_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_c {
	struct {
		uint32_t rd_wdr5_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_c {
	struct {
		uint32_t rd_wdr4_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_c {
	struct {
		uint32_t rd_wdr3_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_c {
	struct {
		uint32_t rd_wdr2_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_c {
	struct {
		uint32_t rd_wdr1_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_c {
	struct {
		uint32_t rd_wdr0_ch_c; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_d {
	struct {
		uint32_t rd_wdr18_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_d {
	struct {
		uint32_t rd_wdr17_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_d {
	struct {
		uint32_t rd_wdr16_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_d {
	struct {
		uint32_t rd_wdr15_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_d {
	struct {
		uint32_t rd_wdr14_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_d {
	struct {
		uint32_t rd_wdr13_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_d {
	struct {
		uint32_t rd_wdr12_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_d {
	struct {
		uint32_t rd_wdr11_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_d {
	struct {
		uint32_t rd_wdr10_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_d {
	struct {
		uint32_t rd_wdr9_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_d {
	struct {
		uint32_t rd_wdr8_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_d {
	struct {
		uint32_t rd_wdr7_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_d {
	struct {
		uint32_t rd_wdr6_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_d {
	struct {
		uint32_t rd_wdr5_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_d {
	struct {
		uint32_t rd_wdr4_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_d {
	struct {
		uint32_t rd_wdr3_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_d {
	struct {
		uint32_t rd_wdr2_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_d {
	struct {
		uint32_t rd_wdr1_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_d {
	struct {
		uint32_t rd_wdr0_ch_d; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_e {
	struct {
		uint32_t rd_wdr18_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_e {
	struct {
		uint32_t rd_wdr17_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_e {
	struct {
		uint32_t rd_wdr16_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_e {
	struct {
		uint32_t rd_wdr15_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_e {
	struct {
		uint32_t rd_wdr14_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_e {
	struct {
		uint32_t rd_wdr13_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_e {
	struct {
		uint32_t rd_wdr12_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_e {
	struct {
		uint32_t rd_wdr11_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_e {
	struct {
		uint32_t rd_wdr10_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_e {
	struct {
		uint32_t rd_wdr9_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_e {
	struct {
		uint32_t rd_wdr8_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_e {
	struct {
		uint32_t rd_wdr7_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_e {
	struct {
		uint32_t rd_wdr6_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_e {
	struct {
		uint32_t rd_wdr5_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_e {
	struct {
		uint32_t rd_wdr4_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_e {
	struct {
		uint32_t rd_wdr3_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_e {
	struct {
		uint32_t rd_wdr2_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_e {
	struct {
		uint32_t rd_wdr1_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_e {
	struct {
		uint32_t rd_wdr0_ch_e; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_f {
	struct {
		uint32_t rd_wdr18_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_f {
	struct {
		uint32_t rd_wdr17_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_f {
	struct {
		uint32_t rd_wdr16_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_f {
	struct {
		uint32_t rd_wdr15_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_f {
	struct {
		uint32_t rd_wdr14_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_f {
	struct {
		uint32_t rd_wdr13_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_f {
	struct {
		uint32_t rd_wdr12_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_f {
	struct {
		uint32_t rd_wdr11_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_f {
	struct {
		uint32_t rd_wdr10_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_f {
	struct {
		uint32_t rd_wdr9_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_f {
	struct {
		uint32_t rd_wdr8_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_f {
	struct {
		uint32_t rd_wdr7_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_f {
	struct {
		uint32_t rd_wdr6_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_f {
	struct {
		uint32_t rd_wdr5_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_f {
	struct {
		uint32_t rd_wdr4_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_f {
	struct {
		uint32_t rd_wdr3_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_f {
	struct {
		uint32_t rd_wdr2_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_f {
	struct {
		uint32_t rd_wdr1_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_f {
	struct {
		uint32_t rd_wdr0_ch_f; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_g {
	struct {
		uint32_t rd_wdr18_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_g {
	struct {
		uint32_t rd_wdr17_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_g {
	struct {
		uint32_t rd_wdr16_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_g {
	struct {
		uint32_t rd_wdr15_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_g {
	struct {
		uint32_t rd_wdr14_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_g {
	struct {
		uint32_t rd_wdr13_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_g {
	struct {
		uint32_t rd_wdr12_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_g {
	struct {
		uint32_t rd_wdr11_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_g {
	struct {
		uint32_t rd_wdr10_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_g {
	struct {
		uint32_t rd_wdr9_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_g {
	struct {
		uint32_t rd_wdr8_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_g {
	struct {
		uint32_t rd_wdr7_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_g {
	struct {
		uint32_t rd_wdr6_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_g {
	struct {
		uint32_t rd_wdr5_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_g {
	struct {
		uint32_t rd_wdr4_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_g {
	struct {
		uint32_t rd_wdr3_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_g {
	struct {
		uint32_t rd_wdr2_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_g {
	struct {
		uint32_t rd_wdr1_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_g {
	struct {
		uint32_t rd_wdr0_ch_g; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_h {
	struct {
		uint32_t rd_wdr18_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_h {
	struct {
		uint32_t rd_wdr17_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_h {
	struct {
		uint32_t rd_wdr16_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_h {
	struct {
		uint32_t rd_wdr15_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_h {
	struct {
		uint32_t rd_wdr14_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_h {
	struct {
		uint32_t rd_wdr13_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_h {
	struct {
		uint32_t rd_wdr12_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_h {
	struct {
		uint32_t rd_wdr11_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_h {
	struct {
		uint32_t rd_wdr10_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_h {
	struct {
		uint32_t rd_wdr9_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_h {
	struct {
		uint32_t rd_wdr8_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_h {
	struct {
		uint32_t rd_wdr7_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_h {
	struct {
		uint32_t rd_wdr6_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_h {
	struct {
		uint32_t rd_wdr5_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_h {
	struct {
		uint32_t rd_wdr4_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_h {
	struct {
		uint32_t rd_wdr3_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_h {
	struct {
		uint32_t rd_wdr2_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_h {
	struct {
		uint32_t rd_wdr1_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_h {
	struct {
		uint32_t rd_wdr0_ch_h; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_i {
	struct {
		uint32_t rd_wdr18_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_i {
	struct {
		uint32_t rd_wdr17_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_i {
	struct {
		uint32_t rd_wdr16_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_i {
	struct {
		uint32_t rd_wdr15_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_i {
	struct {
		uint32_t rd_wdr14_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_i {
	struct {
		uint32_t rd_wdr13_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_i {
	struct {
		uint32_t rd_wdr12_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_i {
	struct {
		uint32_t rd_wdr11_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_i {
	struct {
		uint32_t rd_wdr10_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_i {
	struct {
		uint32_t rd_wdr9_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_i {
	struct {
		uint32_t rd_wdr8_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_i {
	struct {
		uint32_t rd_wdr7_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_i {
	struct {
		uint32_t rd_wdr6_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_i {
	struct {
		uint32_t rd_wdr5_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_i {
	struct {
		uint32_t rd_wdr4_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_i {
	struct {
		uint32_t rd_wdr3_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_i {
	struct {
		uint32_t rd_wdr2_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_i {
	struct {
		uint32_t rd_wdr1_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_i {
	struct {
		uint32_t rd_wdr0_ch_i; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_j {
	struct {
		uint32_t rd_wdr18_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_j {
	struct {
		uint32_t rd_wdr17_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_j {
	struct {
		uint32_t rd_wdr16_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_j {
	struct {
		uint32_t rd_wdr15_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_j {
	struct {
		uint32_t rd_wdr14_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_j {
	struct {
		uint32_t rd_wdr13_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_j {
	struct {
		uint32_t rd_wdr12_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_j {
	struct {
		uint32_t rd_wdr11_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_j {
	struct {
		uint32_t rd_wdr10_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_j {
	struct {
		uint32_t rd_wdr9_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_j {
	struct {
		uint32_t rd_wdr8_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_j {
	struct {
		uint32_t rd_wdr7_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_j {
	struct {
		uint32_t rd_wdr6_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_j {
	struct {
		uint32_t rd_wdr5_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_j {
	struct {
		uint32_t rd_wdr4_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_j {
	struct {
		uint32_t rd_wdr3_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_j {
	struct {
		uint32_t rd_wdr2_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_j {
	struct {
		uint32_t rd_wdr1_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_j {
	struct {
		uint32_t rd_wdr0_ch_j; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_k {
	struct {
		uint32_t rd_wdr18_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_k {
	struct {
		uint32_t rd_wdr17_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_k {
	struct {
		uint32_t rd_wdr16_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_k {
	struct {
		uint32_t rd_wdr15_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_k {
	struct {
		uint32_t rd_wdr14_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_k {
	struct {
		uint32_t rd_wdr13_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_k {
	struct {
		uint32_t rd_wdr12_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_k {
	struct {
		uint32_t rd_wdr11_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_k {
	struct {
		uint32_t rd_wdr10_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_k {
	struct {
		uint32_t rd_wdr9_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_k {
	struct {
		uint32_t rd_wdr8_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_k {
	struct {
		uint32_t rd_wdr7_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_k {
	struct {
		uint32_t rd_wdr6_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_k {
	struct {
		uint32_t rd_wdr5_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_k {
	struct {
		uint32_t rd_wdr4_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_k {
	struct {
		uint32_t rd_wdr3_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_k {
	struct {
		uint32_t rd_wdr2_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_k {
	struct {
		uint32_t rd_wdr1_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_k {
	struct {
		uint32_t rd_wdr0_ch_k; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_l {
	struct {
		uint32_t rd_wdr18_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_l {
	struct {
		uint32_t rd_wdr17_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_l {
	struct {
		uint32_t rd_wdr16_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_l {
	struct {
		uint32_t rd_wdr15_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_l {
	struct {
		uint32_t rd_wdr14_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_l {
	struct {
		uint32_t rd_wdr13_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_l {
	struct {
		uint32_t rd_wdr12_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_l {
	struct {
		uint32_t rd_wdr11_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_l {
	struct {
		uint32_t rd_wdr10_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_l {
	struct {
		uint32_t rd_wdr9_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_l {
	struct {
		uint32_t rd_wdr8_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_l {
	struct {
		uint32_t rd_wdr7_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_l {
	struct {
		uint32_t rd_wdr6_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_l {
	struct {
		uint32_t rd_wdr5_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_l {
	struct {
		uint32_t rd_wdr4_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_l {
	struct {
		uint32_t rd_wdr3_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_l {
	struct {
		uint32_t rd_wdr2_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_l {
	struct {
		uint32_t rd_wdr1_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_l {
	struct {
		uint32_t rd_wdr0_ch_l; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_m {
	struct {
		uint32_t rd_wdr18_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_m {
	struct {
		uint32_t rd_wdr17_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_m {
	struct {
		uint32_t rd_wdr16_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_m {
	struct {
		uint32_t rd_wdr15_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_m {
	struct {
		uint32_t rd_wdr14_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_m {
	struct {
		uint32_t rd_wdr13_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_m {
	struct {
		uint32_t rd_wdr12_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_m {
	struct {
		uint32_t rd_wdr11_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_m {
	struct {
		uint32_t rd_wdr10_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_m {
	struct {
		uint32_t rd_wdr9_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_m {
	struct {
		uint32_t rd_wdr8_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_m {
	struct {
		uint32_t rd_wdr7_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_m {
	struct {
		uint32_t rd_wdr6_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_m {
	struct {
		uint32_t rd_wdr5_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_m {
	struct {
		uint32_t rd_wdr4_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_m {
	struct {
		uint32_t rd_wdr3_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_m {
	struct {
		uint32_t rd_wdr2_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_m {
	struct {
		uint32_t rd_wdr1_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_m {
	struct {
		uint32_t rd_wdr0_ch_m; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_n {
	struct {
		uint32_t rd_wdr18_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_n {
	struct {
		uint32_t rd_wdr17_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_n {
	struct {
		uint32_t rd_wdr16_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_n {
	struct {
		uint32_t rd_wdr15_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_n {
	struct {
		uint32_t rd_wdr14_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_n {
	struct {
		uint32_t rd_wdr13_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_n {
	struct {
		uint32_t rd_wdr12_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_n {
	struct {
		uint32_t rd_wdr11_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_n {
	struct {
		uint32_t rd_wdr10_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_n {
	struct {
		uint32_t rd_wdr9_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_n {
	struct {
		uint32_t rd_wdr8_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_n {
	struct {
		uint32_t rd_wdr7_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_n {
	struct {
		uint32_t rd_wdr6_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_n {
	struct {
		uint32_t rd_wdr5_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_n {
	struct {
		uint32_t rd_wdr4_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_n {
	struct {
		uint32_t rd_wdr3_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_n {
	struct {
		uint32_t rd_wdr2_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_n {
	struct {
		uint32_t rd_wdr1_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_n {
	struct {
		uint32_t rd_wdr0_ch_n; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_o {
	struct {
		uint32_t rd_wdr18_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_o {
	struct {
		uint32_t rd_wdr17_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_o {
	struct {
		uint32_t rd_wdr16_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_o {
	struct {
		uint32_t rd_wdr15_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_o {
	struct {
		uint32_t rd_wdr14_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_o {
	struct {
		uint32_t rd_wdr13_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_o {
	struct {
		uint32_t rd_wdr12_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_o {
	struct {
		uint32_t rd_wdr11_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_o {
	struct {
		uint32_t rd_wdr10_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_o {
	struct {
		uint32_t rd_wdr9_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_o {
	struct {
		uint32_t rd_wdr8_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_o {
	struct {
		uint32_t rd_wdr7_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_o {
	struct {
		uint32_t rd_wdr6_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_o {
	struct {
		uint32_t rd_wdr5_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_o {
	struct {
		uint32_t rd_wdr4_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_o {
	struct {
		uint32_t rd_wdr3_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_o {
	struct {
		uint32_t rd_wdr2_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_o {
	struct {
		uint32_t rd_wdr1_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_o {
	struct {
		uint32_t rd_wdr0_ch_o; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr18_ch_p {
	struct {
		uint32_t rd_wdr18_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr17_ch_p {
	struct {
		uint32_t rd_wdr17_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr16_ch_p {
	struct {
		uint32_t rd_wdr16_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr15_ch_p {
	struct {
		uint32_t rd_wdr15_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr14_ch_p {
	struct {
		uint32_t rd_wdr14_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr13_ch_p {
	struct {
		uint32_t rd_wdr13_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr12_ch_p {
	struct {
		uint32_t rd_wdr12_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr11_ch_p {
	struct {
		uint32_t rd_wdr11_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr10_ch_p {
	struct {
		uint32_t rd_wdr10_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr9_ch_p {
	struct {
		uint32_t rd_wdr9_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr8_ch_p {
	struct {
		uint32_t rd_wdr8_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr7_ch_p {
	struct {
		uint32_t rd_wdr7_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr6_ch_p {
	struct {
		uint32_t rd_wdr6_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr5_ch_p {
	struct {
		uint32_t rd_wdr5_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr4_ch_p {
	struct {
		uint32_t rd_wdr4_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr3_ch_p {
	struct {
		uint32_t rd_wdr3_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr2_ch_p {
	struct {
		uint32_t rd_wdr2_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr1_ch_p {
	struct {
		uint32_t rd_wdr1_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_rd_wdr0_ch_p {
	struct {
		uint32_t rd_wdr0_ch_p; /* [31:0] */
	};
	uint32_t val;
};

union ieee1500_icon_fsm_debug {
	struct {
		uint32_t fsm_mode:3; /* [2:0] */
		uint32_t wait_cnt:11; /* [13:3] */
		uint32_t cs_state:5; /* [18:14] */
		uint32_t reserved0:13; /* [31:19] */
	};
	uint32_t val;
};

union ieee1500_icon_io_ctrl0 {
	struct {
		uint32_t ctrl_io_pde_apb:1; /* [0:0] */
		uint32_t ctrl_io_pue_apb:1; /* [1:1] */
		uint32_t ctrl_io_pd_apb:1; /* [2:2] */
		uint32_t ctrl_io_en_apb:1; /* [3:3] */
		uint32_t ctrl_apb:1; /* [4:4] */
		uint32_t ctrl_testihbm3_apb:1; /* [5:5] */
		uint32_t io_zq_dds_apb:2; /* [7:6] */
		uint32_t reserved0:24; /* [31:8] */
	};
	uint32_t val;
};

union ieee1500_icon_zq_con0 {
	struct {
		uint32_t i_zq_force_impn_apb:3; /* [2:0] */
		uint32_t i_zq_force_impp_apb:3; /* [5:3] */
		uint32_t i_zq_udt_dly_apb:8; /* [13:6] */
		uint32_t i_zq_manual_mode_apb:2; /* [15:14] */
		uint32_t i_zq_manual_str_apb:1; /* [16:16] */
		uint32_t i_phy_clk_en_apb:1; /* [17:17] */
		uint32_t ctrl_zqswmode_apb:1; /* [18:18] */
		uint32_t zq_comp_resp_time_apb:5; /* [23:19] */
		uint32_t ctrl_int_resync_apb:1; /* [24:24] */
		uint32_t reserved0:7; /* [31:25] */
	};
	uint32_t val;
};

union ieee1500_icon_zq_mon0 {
	struct {
		uint32_t o_zq_error:1; /* [0:0] */
		uint32_t o_zq_done:1; /* [1:1] */
		uint32_t o_zq_cal_fsm:4; /* [5:2] */
		uint32_t o_zq_zctrl_nmon:3; /* [8:6] */
		uint32_t o_zq_zctrl_pmon:3; /* [11:9] */
		uint32_t reserved0:20; /* [31:12] */
	};
	uint32_t val;
};

union ieee1500_icon_icon_spec {
	struct {
		uint32_t hbm_spec_selection_apb:1; /* [0:0] */
		uint32_t reserved0:31; /* [31:1] */
	};
	uint32_t val;
};

struct ieee1500_icon {
	union ieee1500_icon_icon_ctrl_con0 icon_ctrl_con0; /* offset : 0x0 */
	union ieee1500_icon_icon_ctrl_con1 icon_ctrl_con1; /* offset : 0x4 */
	union ieee1500_icon_test_instruction_req0 test_instruction_req0; /* offset : 0x8 */
	union ieee1500_icon_test_instruction_req1 test_instruction_req1; /* offset : 0xc */
	union ieee1500_icon_wr_wdr18 wr_wdr18; /* offset : 0x10 */
	union ieee1500_icon_wr_wdr17 wr_wdr17; /* offset : 0x14 */
	union ieee1500_icon_wr_wdr16 wr_wdr16; /* offset : 0x18 */
	union ieee1500_icon_wr_wdr15 wr_wdr15; /* offset : 0x1c */
	union ieee1500_icon_wr_wdr14 wr_wdr14; /* offset : 0x20 */
	union ieee1500_icon_wr_wdr13 wr_wdr13; /* offset : 0x24 */
	union ieee1500_icon_wr_wdr12 wr_wdr12; /* offset : 0x28 */
	union ieee1500_icon_wr_wdr11 wr_wdr11; /* offset : 0x2c */
	union ieee1500_icon_wr_wdr10 wr_wdr10; /* offset : 0x30 */
	union ieee1500_icon_wr_wdr9 wr_wdr9; /* offset : 0x34 */
	union ieee1500_icon_wr_wdr8 wr_wdr8; /* offset : 0x38 */
	union ieee1500_icon_wr_wdr7 wr_wdr7; /* offset : 0x3c */
	union ieee1500_icon_wr_wdr6 wr_wdr6; /* offset : 0x40 */
	union ieee1500_icon_wr_wdr5 wr_wdr5; /* offset : 0x44 */
	union ieee1500_icon_wr_wdr4 wr_wdr4; /* offset : 0x48 */
	union ieee1500_icon_wr_wdr3 wr_wdr3; /* offset : 0x4c */
	union ieee1500_icon_wr_wdr2 wr_wdr2; /* offset : 0x50 */
	union ieee1500_icon_wr_wdr1 wr_wdr1; /* offset : 0x54 */
	union ieee1500_icon_wr_wdr0 wr_wdr0; /* offset : 0x58 */
	union ieee1500_icon_rd_wdr18_ch_a rd_wdr18_ch_a; /* offset : 0x5c */
	union ieee1500_icon_rd_wdr17_ch_a rd_wdr17_ch_a; /* offset : 0x60 */
	union ieee1500_icon_rd_wdr16_ch_a rd_wdr16_ch_a; /* offset : 0x64 */
	union ieee1500_icon_rd_wdr15_ch_a rd_wdr15_ch_a; /* offset : 0x68 */
	union ieee1500_icon_rd_wdr14_ch_a rd_wdr14_ch_a; /* offset : 0x6c */
	union ieee1500_icon_rd_wdr13_ch_a rd_wdr13_ch_a; /* offset : 0x70 */
	union ieee1500_icon_rd_wdr12_ch_a rd_wdr12_ch_a; /* offset : 0x74 */
	union ieee1500_icon_rd_wdr11_ch_a rd_wdr11_ch_a; /* offset : 0x78 */
	union ieee1500_icon_rd_wdr10_ch_a rd_wdr10_ch_a; /* offset : 0x7c */
	union ieee1500_icon_rd_wdr9_ch_a rd_wdr9_ch_a; /* offset : 0x80 */
	union ieee1500_icon_rd_wdr8_ch_a rd_wdr8_ch_a; /* offset : 0x84 */
	union ieee1500_icon_rd_wdr7_ch_a rd_wdr7_ch_a; /* offset : 0x88 */
	union ieee1500_icon_rd_wdr6_ch_a rd_wdr6_ch_a; /* offset : 0x8c */
	union ieee1500_icon_rd_wdr5_ch_a rd_wdr5_ch_a; /* offset : 0x90 */
	union ieee1500_icon_rd_wdr4_ch_a rd_wdr4_ch_a; /* offset : 0x94 */
	union ieee1500_icon_rd_wdr3_ch_a rd_wdr3_ch_a; /* offset : 0x98 */
	union ieee1500_icon_rd_wdr2_ch_a rd_wdr2_ch_a; /* offset : 0x9c */
	union ieee1500_icon_rd_wdr1_ch_a rd_wdr1_ch_a; /* offset : 0xa0 */
	union ieee1500_icon_rd_wdr0_ch_a rd_wdr0_ch_a; /* offset : 0xa4 */
	union ieee1500_icon_rd_wdr18_ch_b rd_wdr18_ch_b; /* offset : 0xa8 */
	union ieee1500_icon_rd_wdr17_ch_b rd_wdr17_ch_b; /* offset : 0xac */
	union ieee1500_icon_rd_wdr16_ch_b rd_wdr16_ch_b; /* offset : 0xb0 */
	union ieee1500_icon_rd_wdr15_ch_b rd_wdr15_ch_b; /* offset : 0xb4 */
	union ieee1500_icon_rd_wdr14_ch_b rd_wdr14_ch_b; /* offset : 0xb8 */
	union ieee1500_icon_rd_wdr13_ch_b rd_wdr13_ch_b; /* offset : 0xbc */
	union ieee1500_icon_rd_wdr12_ch_b rd_wdr12_ch_b; /* offset : 0xc0 */
	union ieee1500_icon_rd_wdr11_ch_b rd_wdr11_ch_b; /* offset : 0xc4 */
	union ieee1500_icon_rd_wdr10_ch_b rd_wdr10_ch_b; /* offset : 0xc8 */
	union ieee1500_icon_rd_wdr9_ch_b rd_wdr9_ch_b; /* offset : 0xcc */
	union ieee1500_icon_rd_wdr8_ch_b rd_wdr8_ch_b; /* offset : 0xd0 */
	union ieee1500_icon_rd_wdr7_ch_b rd_wdr7_ch_b; /* offset : 0xd4 */
	union ieee1500_icon_rd_wdr6_ch_b rd_wdr6_ch_b; /* offset : 0xd8 */
	union ieee1500_icon_rd_wdr5_ch_b rd_wdr5_ch_b; /* offset : 0xdc */
	union ieee1500_icon_rd_wdr4_ch_b rd_wdr4_ch_b; /* offset : 0xe0 */
	union ieee1500_icon_rd_wdr3_ch_b rd_wdr3_ch_b; /* offset : 0xe4 */
	union ieee1500_icon_rd_wdr2_ch_b rd_wdr2_ch_b; /* offset : 0xe8 */
	union ieee1500_icon_rd_wdr1_ch_b rd_wdr1_ch_b; /* offset : 0xec */
	union ieee1500_icon_rd_wdr0_ch_b rd_wdr0_ch_b; /* offset : 0xf0 */
	union ieee1500_icon_rd_wdr18_ch_c rd_wdr18_ch_c; /* offset : 0xf4 */
	union ieee1500_icon_rd_wdr17_ch_c rd_wdr17_ch_c; /* offset : 0xf8 */
	union ieee1500_icon_rd_wdr16_ch_c rd_wdr16_ch_c; /* offset : 0xfc */
	union ieee1500_icon_rd_wdr15_ch_c rd_wdr15_ch_c; /* offset : 0x100 */
	union ieee1500_icon_rd_wdr14_ch_c rd_wdr14_ch_c; /* offset : 0x104 */
	union ieee1500_icon_rd_wdr13_ch_c rd_wdr13_ch_c; /* offset : 0x108 */
	union ieee1500_icon_rd_wdr12_ch_c rd_wdr12_ch_c; /* offset : 0x10c */
	union ieee1500_icon_rd_wdr11_ch_c rd_wdr11_ch_c; /* offset : 0x110 */
	union ieee1500_icon_rd_wdr10_ch_c rd_wdr10_ch_c; /* offset : 0x114 */
	union ieee1500_icon_rd_wdr9_ch_c rd_wdr9_ch_c; /* offset : 0x118 */
	union ieee1500_icon_rd_wdr8_ch_c rd_wdr8_ch_c; /* offset : 0x11c */
	union ieee1500_icon_rd_wdr7_ch_c rd_wdr7_ch_c; /* offset : 0x120 */
	union ieee1500_icon_rd_wdr6_ch_c rd_wdr6_ch_c; /* offset : 0x124 */
	union ieee1500_icon_rd_wdr5_ch_c rd_wdr5_ch_c; /* offset : 0x128 */
	union ieee1500_icon_rd_wdr4_ch_c rd_wdr4_ch_c; /* offset : 0x12c */
	union ieee1500_icon_rd_wdr3_ch_c rd_wdr3_ch_c; /* offset : 0x130 */
	union ieee1500_icon_rd_wdr2_ch_c rd_wdr2_ch_c; /* offset : 0x134 */
	union ieee1500_icon_rd_wdr1_ch_c rd_wdr1_ch_c; /* offset : 0x138 */
	union ieee1500_icon_rd_wdr0_ch_c rd_wdr0_ch_c; /* offset : 0x13c */
	union ieee1500_icon_rd_wdr18_ch_d rd_wdr18_ch_d; /* offset : 0x140 */
	union ieee1500_icon_rd_wdr17_ch_d rd_wdr17_ch_d; /* offset : 0x144 */
	union ieee1500_icon_rd_wdr16_ch_d rd_wdr16_ch_d; /* offset : 0x148 */
	union ieee1500_icon_rd_wdr15_ch_d rd_wdr15_ch_d; /* offset : 0x14c */
	union ieee1500_icon_rd_wdr14_ch_d rd_wdr14_ch_d; /* offset : 0x150 */
	union ieee1500_icon_rd_wdr13_ch_d rd_wdr13_ch_d; /* offset : 0x154 */
	union ieee1500_icon_rd_wdr12_ch_d rd_wdr12_ch_d; /* offset : 0x158 */
	union ieee1500_icon_rd_wdr11_ch_d rd_wdr11_ch_d; /* offset : 0x15c */
	union ieee1500_icon_rd_wdr10_ch_d rd_wdr10_ch_d; /* offset : 0x160 */
	union ieee1500_icon_rd_wdr9_ch_d rd_wdr9_ch_d; /* offset : 0x164 */
	union ieee1500_icon_rd_wdr8_ch_d rd_wdr8_ch_d; /* offset : 0x168 */
	union ieee1500_icon_rd_wdr7_ch_d rd_wdr7_ch_d; /* offset : 0x16c */
	union ieee1500_icon_rd_wdr6_ch_d rd_wdr6_ch_d; /* offset : 0x170 */
	union ieee1500_icon_rd_wdr5_ch_d rd_wdr5_ch_d; /* offset : 0x174 */
	union ieee1500_icon_rd_wdr4_ch_d rd_wdr4_ch_d; /* offset : 0x178 */
	union ieee1500_icon_rd_wdr3_ch_d rd_wdr3_ch_d; /* offset : 0x17c */
	union ieee1500_icon_rd_wdr2_ch_d rd_wdr2_ch_d; /* offset : 0x180 */
	union ieee1500_icon_rd_wdr1_ch_d rd_wdr1_ch_d; /* offset : 0x184 */
	union ieee1500_icon_rd_wdr0_ch_d rd_wdr0_ch_d; /* offset : 0x188 */
	union ieee1500_icon_rd_wdr18_ch_e rd_wdr18_ch_e; /* offset : 0x18c */
	union ieee1500_icon_rd_wdr17_ch_e rd_wdr17_ch_e; /* offset : 0x190 */
	union ieee1500_icon_rd_wdr16_ch_e rd_wdr16_ch_e; /* offset : 0x194 */
	union ieee1500_icon_rd_wdr15_ch_e rd_wdr15_ch_e; /* offset : 0x198 */
	union ieee1500_icon_rd_wdr14_ch_e rd_wdr14_ch_e; /* offset : 0x19c */
	union ieee1500_icon_rd_wdr13_ch_e rd_wdr13_ch_e; /* offset : 0x1a0 */
	union ieee1500_icon_rd_wdr12_ch_e rd_wdr12_ch_e; /* offset : 0x1a4 */
	union ieee1500_icon_rd_wdr11_ch_e rd_wdr11_ch_e; /* offset : 0x1a8 */
	union ieee1500_icon_rd_wdr10_ch_e rd_wdr10_ch_e; /* offset : 0x1ac */
	union ieee1500_icon_rd_wdr9_ch_e rd_wdr9_ch_e; /* offset : 0x1b0 */
	union ieee1500_icon_rd_wdr8_ch_e rd_wdr8_ch_e; /* offset : 0x1b4 */
	union ieee1500_icon_rd_wdr7_ch_e rd_wdr7_ch_e; /* offset : 0x1b8 */
	union ieee1500_icon_rd_wdr6_ch_e rd_wdr6_ch_e; /* offset : 0x1bc */
	union ieee1500_icon_rd_wdr5_ch_e rd_wdr5_ch_e; /* offset : 0x1c0 */
	union ieee1500_icon_rd_wdr4_ch_e rd_wdr4_ch_e; /* offset : 0x1c4 */
	union ieee1500_icon_rd_wdr3_ch_e rd_wdr3_ch_e; /* offset : 0x1c8 */
	union ieee1500_icon_rd_wdr2_ch_e rd_wdr2_ch_e; /* offset : 0x1cc */
	union ieee1500_icon_rd_wdr1_ch_e rd_wdr1_ch_e; /* offset : 0x1d0 */
	union ieee1500_icon_rd_wdr0_ch_e rd_wdr0_ch_e; /* offset : 0x1d4 */
	union ieee1500_icon_rd_wdr18_ch_f rd_wdr18_ch_f; /* offset : 0x1d8 */
	union ieee1500_icon_rd_wdr17_ch_f rd_wdr17_ch_f; /* offset : 0x1dc */
	union ieee1500_icon_rd_wdr16_ch_f rd_wdr16_ch_f; /* offset : 0x1e0 */
	union ieee1500_icon_rd_wdr15_ch_f rd_wdr15_ch_f; /* offset : 0x1e4 */
	union ieee1500_icon_rd_wdr14_ch_f rd_wdr14_ch_f; /* offset : 0x1e8 */
	union ieee1500_icon_rd_wdr13_ch_f rd_wdr13_ch_f; /* offset : 0x1ec */
	union ieee1500_icon_rd_wdr12_ch_f rd_wdr12_ch_f; /* offset : 0x1f0 */
	union ieee1500_icon_rd_wdr11_ch_f rd_wdr11_ch_f; /* offset : 0x1f4 */
	union ieee1500_icon_rd_wdr10_ch_f rd_wdr10_ch_f; /* offset : 0x1f8 */
	union ieee1500_icon_rd_wdr9_ch_f rd_wdr9_ch_f; /* offset : 0x1fc */
	union ieee1500_icon_rd_wdr8_ch_f rd_wdr8_ch_f; /* offset : 0x200 */
	union ieee1500_icon_rd_wdr7_ch_f rd_wdr7_ch_f; /* offset : 0x204 */
	union ieee1500_icon_rd_wdr6_ch_f rd_wdr6_ch_f; /* offset : 0x208 */
	union ieee1500_icon_rd_wdr5_ch_f rd_wdr5_ch_f; /* offset : 0x20c */
	union ieee1500_icon_rd_wdr4_ch_f rd_wdr4_ch_f; /* offset : 0x210 */
	union ieee1500_icon_rd_wdr3_ch_f rd_wdr3_ch_f; /* offset : 0x214 */
	union ieee1500_icon_rd_wdr2_ch_f rd_wdr2_ch_f; /* offset : 0x218 */
	union ieee1500_icon_rd_wdr1_ch_f rd_wdr1_ch_f; /* offset : 0x21c */
	union ieee1500_icon_rd_wdr0_ch_f rd_wdr0_ch_f; /* offset : 0x220 */
	union ieee1500_icon_rd_wdr18_ch_g rd_wdr18_ch_g; /* offset : 0x224 */
	union ieee1500_icon_rd_wdr17_ch_g rd_wdr17_ch_g; /* offset : 0x228 */
	union ieee1500_icon_rd_wdr16_ch_g rd_wdr16_ch_g; /* offset : 0x22c */
	union ieee1500_icon_rd_wdr15_ch_g rd_wdr15_ch_g; /* offset : 0x230 */
	union ieee1500_icon_rd_wdr14_ch_g rd_wdr14_ch_g; /* offset : 0x234 */
	union ieee1500_icon_rd_wdr13_ch_g rd_wdr13_ch_g; /* offset : 0x238 */
	union ieee1500_icon_rd_wdr12_ch_g rd_wdr12_ch_g; /* offset : 0x23c */
	union ieee1500_icon_rd_wdr11_ch_g rd_wdr11_ch_g; /* offset : 0x240 */
	union ieee1500_icon_rd_wdr10_ch_g rd_wdr10_ch_g; /* offset : 0x244 */
	union ieee1500_icon_rd_wdr9_ch_g rd_wdr9_ch_g; /* offset : 0x248 */
	union ieee1500_icon_rd_wdr8_ch_g rd_wdr8_ch_g; /* offset : 0x24c */
	union ieee1500_icon_rd_wdr7_ch_g rd_wdr7_ch_g; /* offset : 0x250 */
	union ieee1500_icon_rd_wdr6_ch_g rd_wdr6_ch_g; /* offset : 0x254 */
	union ieee1500_icon_rd_wdr5_ch_g rd_wdr5_ch_g; /* offset : 0x258 */
	union ieee1500_icon_rd_wdr4_ch_g rd_wdr4_ch_g; /* offset : 0x25c */
	union ieee1500_icon_rd_wdr3_ch_g rd_wdr3_ch_g; /* offset : 0x260 */
	union ieee1500_icon_rd_wdr2_ch_g rd_wdr2_ch_g; /* offset : 0x264 */
	union ieee1500_icon_rd_wdr1_ch_g rd_wdr1_ch_g; /* offset : 0x268 */
	union ieee1500_icon_rd_wdr0_ch_g rd_wdr0_ch_g; /* offset : 0x26c */
	union ieee1500_icon_rd_wdr18_ch_h rd_wdr18_ch_h; /* offset : 0x270 */
	union ieee1500_icon_rd_wdr17_ch_h rd_wdr17_ch_h; /* offset : 0x274 */
	union ieee1500_icon_rd_wdr16_ch_h rd_wdr16_ch_h; /* offset : 0x278 */
	union ieee1500_icon_rd_wdr15_ch_h rd_wdr15_ch_h; /* offset : 0x27c */
	union ieee1500_icon_rd_wdr14_ch_h rd_wdr14_ch_h; /* offset : 0x280 */
	union ieee1500_icon_rd_wdr13_ch_h rd_wdr13_ch_h; /* offset : 0x284 */
	union ieee1500_icon_rd_wdr12_ch_h rd_wdr12_ch_h; /* offset : 0x288 */
	union ieee1500_icon_rd_wdr11_ch_h rd_wdr11_ch_h; /* offset : 0x28c */
	union ieee1500_icon_rd_wdr10_ch_h rd_wdr10_ch_h; /* offset : 0x290 */
	union ieee1500_icon_rd_wdr9_ch_h rd_wdr9_ch_h; /* offset : 0x294 */
	union ieee1500_icon_rd_wdr8_ch_h rd_wdr8_ch_h; /* offset : 0x298 */
	union ieee1500_icon_rd_wdr7_ch_h rd_wdr7_ch_h; /* offset : 0x29c */
	union ieee1500_icon_rd_wdr6_ch_h rd_wdr6_ch_h; /* offset : 0x2a0 */
	union ieee1500_icon_rd_wdr5_ch_h rd_wdr5_ch_h; /* offset : 0x2a4 */
	union ieee1500_icon_rd_wdr4_ch_h rd_wdr4_ch_h; /* offset : 0x2a8 */
	union ieee1500_icon_rd_wdr3_ch_h rd_wdr3_ch_h; /* offset : 0x2ac */
	union ieee1500_icon_rd_wdr2_ch_h rd_wdr2_ch_h; /* offset : 0x2b0 */
	union ieee1500_icon_rd_wdr1_ch_h rd_wdr1_ch_h; /* offset : 0x2b4 */
	union ieee1500_icon_rd_wdr0_ch_h rd_wdr0_ch_h; /* offset : 0x2b8 */
	union ieee1500_icon_rd_wdr18_ch_i rd_wdr18_ch_i; /* offset : 0x2bc */
	union ieee1500_icon_rd_wdr17_ch_i rd_wdr17_ch_i; /* offset : 0x2c0 */
	union ieee1500_icon_rd_wdr16_ch_i rd_wdr16_ch_i; /* offset : 0x2c4 */
	union ieee1500_icon_rd_wdr15_ch_i rd_wdr15_ch_i; /* offset : 0x2c8 */
	union ieee1500_icon_rd_wdr14_ch_i rd_wdr14_ch_i; /* offset : 0x2cc */
	union ieee1500_icon_rd_wdr13_ch_i rd_wdr13_ch_i; /* offset : 0x2d0 */
	union ieee1500_icon_rd_wdr12_ch_i rd_wdr12_ch_i; /* offset : 0x2d4 */
	union ieee1500_icon_rd_wdr11_ch_i rd_wdr11_ch_i; /* offset : 0x2d8 */
	union ieee1500_icon_rd_wdr10_ch_i rd_wdr10_ch_i; /* offset : 0x2dc */
	union ieee1500_icon_rd_wdr9_ch_i rd_wdr9_ch_i; /* offset : 0x2e0 */
	union ieee1500_icon_rd_wdr8_ch_i rd_wdr8_ch_i; /* offset : 0x2e4 */
	union ieee1500_icon_rd_wdr7_ch_i rd_wdr7_ch_i; /* offset : 0x2e8 */
	union ieee1500_icon_rd_wdr6_ch_i rd_wdr6_ch_i; /* offset : 0x2ec */
	union ieee1500_icon_rd_wdr5_ch_i rd_wdr5_ch_i; /* offset : 0x2f0 */
	union ieee1500_icon_rd_wdr4_ch_i rd_wdr4_ch_i; /* offset : 0x2f4 */
	union ieee1500_icon_rd_wdr3_ch_i rd_wdr3_ch_i; /* offset : 0x2f8 */
	union ieee1500_icon_rd_wdr2_ch_i rd_wdr2_ch_i; /* offset : 0x2fc */
	union ieee1500_icon_rd_wdr1_ch_i rd_wdr1_ch_i; /* offset : 0x300 */
	union ieee1500_icon_rd_wdr0_ch_i rd_wdr0_ch_i; /* offset : 0x304 */
	union ieee1500_icon_rd_wdr18_ch_j rd_wdr18_ch_j; /* offset : 0x308 */
	union ieee1500_icon_rd_wdr17_ch_j rd_wdr17_ch_j; /* offset : 0x30c */
	union ieee1500_icon_rd_wdr16_ch_j rd_wdr16_ch_j; /* offset : 0x310 */
	union ieee1500_icon_rd_wdr15_ch_j rd_wdr15_ch_j; /* offset : 0x314 */
	union ieee1500_icon_rd_wdr14_ch_j rd_wdr14_ch_j; /* offset : 0x318 */
	union ieee1500_icon_rd_wdr13_ch_j rd_wdr13_ch_j; /* offset : 0x31c */
	union ieee1500_icon_rd_wdr12_ch_j rd_wdr12_ch_j; /* offset : 0x320 */
	union ieee1500_icon_rd_wdr11_ch_j rd_wdr11_ch_j; /* offset : 0x324 */
	union ieee1500_icon_rd_wdr10_ch_j rd_wdr10_ch_j; /* offset : 0x328 */
	union ieee1500_icon_rd_wdr9_ch_j rd_wdr9_ch_j; /* offset : 0x32c */
	union ieee1500_icon_rd_wdr8_ch_j rd_wdr8_ch_j; /* offset : 0x330 */
	union ieee1500_icon_rd_wdr7_ch_j rd_wdr7_ch_j; /* offset : 0x334 */
	union ieee1500_icon_rd_wdr6_ch_j rd_wdr6_ch_j; /* offset : 0x338 */
	union ieee1500_icon_rd_wdr5_ch_j rd_wdr5_ch_j; /* offset : 0x33c */
	union ieee1500_icon_rd_wdr4_ch_j rd_wdr4_ch_j; /* offset : 0x340 */
	union ieee1500_icon_rd_wdr3_ch_j rd_wdr3_ch_j; /* offset : 0x344 */
	union ieee1500_icon_rd_wdr2_ch_j rd_wdr2_ch_j; /* offset : 0x348 */
	union ieee1500_icon_rd_wdr1_ch_j rd_wdr1_ch_j; /* offset : 0x34c */
	union ieee1500_icon_rd_wdr0_ch_j rd_wdr0_ch_j; /* offset : 0x350 */
	union ieee1500_icon_rd_wdr18_ch_k rd_wdr18_ch_k; /* offset : 0x354 */
	union ieee1500_icon_rd_wdr17_ch_k rd_wdr17_ch_k; /* offset : 0x358 */
	union ieee1500_icon_rd_wdr16_ch_k rd_wdr16_ch_k; /* offset : 0x35c */
	union ieee1500_icon_rd_wdr15_ch_k rd_wdr15_ch_k; /* offset : 0x360 */
	union ieee1500_icon_rd_wdr14_ch_k rd_wdr14_ch_k; /* offset : 0x364 */
	union ieee1500_icon_rd_wdr13_ch_k rd_wdr13_ch_k; /* offset : 0x368 */
	union ieee1500_icon_rd_wdr12_ch_k rd_wdr12_ch_k; /* offset : 0x36c */
	union ieee1500_icon_rd_wdr11_ch_k rd_wdr11_ch_k; /* offset : 0x370 */
	union ieee1500_icon_rd_wdr10_ch_k rd_wdr10_ch_k; /* offset : 0x374 */
	union ieee1500_icon_rd_wdr9_ch_k rd_wdr9_ch_k; /* offset : 0x378 */
	union ieee1500_icon_rd_wdr8_ch_k rd_wdr8_ch_k; /* offset : 0x37c */
	union ieee1500_icon_rd_wdr7_ch_k rd_wdr7_ch_k; /* offset : 0x380 */
	union ieee1500_icon_rd_wdr6_ch_k rd_wdr6_ch_k; /* offset : 0x384 */
	union ieee1500_icon_rd_wdr5_ch_k rd_wdr5_ch_k; /* offset : 0x388 */
	union ieee1500_icon_rd_wdr4_ch_k rd_wdr4_ch_k; /* offset : 0x38c */
	union ieee1500_icon_rd_wdr3_ch_k rd_wdr3_ch_k; /* offset : 0x390 */
	union ieee1500_icon_rd_wdr2_ch_k rd_wdr2_ch_k; /* offset : 0x394 */
	union ieee1500_icon_rd_wdr1_ch_k rd_wdr1_ch_k; /* offset : 0x398 */
	union ieee1500_icon_rd_wdr0_ch_k rd_wdr0_ch_k; /* offset : 0x39c */
	union ieee1500_icon_rd_wdr18_ch_l rd_wdr18_ch_l; /* offset : 0x3a0 */
	union ieee1500_icon_rd_wdr17_ch_l rd_wdr17_ch_l; /* offset : 0x3a4 */
	union ieee1500_icon_rd_wdr16_ch_l rd_wdr16_ch_l; /* offset : 0x3a8 */
	union ieee1500_icon_rd_wdr15_ch_l rd_wdr15_ch_l; /* offset : 0x3ac */
	union ieee1500_icon_rd_wdr14_ch_l rd_wdr14_ch_l; /* offset : 0x3b0 */
	union ieee1500_icon_rd_wdr13_ch_l rd_wdr13_ch_l; /* offset : 0x3b4 */
	union ieee1500_icon_rd_wdr12_ch_l rd_wdr12_ch_l; /* offset : 0x3b8 */
	union ieee1500_icon_rd_wdr11_ch_l rd_wdr11_ch_l; /* offset : 0x3bc */
	union ieee1500_icon_rd_wdr10_ch_l rd_wdr10_ch_l; /* offset : 0x3c0 */
	union ieee1500_icon_rd_wdr9_ch_l rd_wdr9_ch_l; /* offset : 0x3c4 */
	union ieee1500_icon_rd_wdr8_ch_l rd_wdr8_ch_l; /* offset : 0x3c8 */
	union ieee1500_icon_rd_wdr7_ch_l rd_wdr7_ch_l; /* offset : 0x3cc */
	union ieee1500_icon_rd_wdr6_ch_l rd_wdr6_ch_l; /* offset : 0x3d0 */
	union ieee1500_icon_rd_wdr5_ch_l rd_wdr5_ch_l; /* offset : 0x3d4 */
	union ieee1500_icon_rd_wdr4_ch_l rd_wdr4_ch_l; /* offset : 0x3d8 */
	union ieee1500_icon_rd_wdr3_ch_l rd_wdr3_ch_l; /* offset : 0x3dc */
	union ieee1500_icon_rd_wdr2_ch_l rd_wdr2_ch_l; /* offset : 0x3e0 */
	union ieee1500_icon_rd_wdr1_ch_l rd_wdr1_ch_l; /* offset : 0x3e4 */
	union ieee1500_icon_rd_wdr0_ch_l rd_wdr0_ch_l; /* offset : 0x3e8 */
	union ieee1500_icon_rd_wdr18_ch_m rd_wdr18_ch_m; /* offset : 0x3ec */
	union ieee1500_icon_rd_wdr17_ch_m rd_wdr17_ch_m; /* offset : 0x3f0 */
	union ieee1500_icon_rd_wdr16_ch_m rd_wdr16_ch_m; /* offset : 0x3f4 */
	union ieee1500_icon_rd_wdr15_ch_m rd_wdr15_ch_m; /* offset : 0x3f8 */
	union ieee1500_icon_rd_wdr14_ch_m rd_wdr14_ch_m; /* offset : 0x3fc */
	union ieee1500_icon_rd_wdr13_ch_m rd_wdr13_ch_m; /* offset : 0x400 */
	union ieee1500_icon_rd_wdr12_ch_m rd_wdr12_ch_m; /* offset : 0x404 */
	union ieee1500_icon_rd_wdr11_ch_m rd_wdr11_ch_m; /* offset : 0x408 */
	union ieee1500_icon_rd_wdr10_ch_m rd_wdr10_ch_m; /* offset : 0x40c */
	union ieee1500_icon_rd_wdr9_ch_m rd_wdr9_ch_m; /* offset : 0x410 */
	union ieee1500_icon_rd_wdr8_ch_m rd_wdr8_ch_m; /* offset : 0x414 */
	union ieee1500_icon_rd_wdr7_ch_m rd_wdr7_ch_m; /* offset : 0x418 */
	union ieee1500_icon_rd_wdr6_ch_m rd_wdr6_ch_m; /* offset : 0x41c */
	union ieee1500_icon_rd_wdr5_ch_m rd_wdr5_ch_m; /* offset : 0x420 */
	union ieee1500_icon_rd_wdr4_ch_m rd_wdr4_ch_m; /* offset : 0x424 */
	union ieee1500_icon_rd_wdr3_ch_m rd_wdr3_ch_m; /* offset : 0x428 */
	union ieee1500_icon_rd_wdr2_ch_m rd_wdr2_ch_m; /* offset : 0x42c */
	union ieee1500_icon_rd_wdr1_ch_m rd_wdr1_ch_m; /* offset : 0x430 */
	union ieee1500_icon_rd_wdr0_ch_m rd_wdr0_ch_m; /* offset : 0x434 */
	union ieee1500_icon_rd_wdr18_ch_n rd_wdr18_ch_n; /* offset : 0x438 */
	union ieee1500_icon_rd_wdr17_ch_n rd_wdr17_ch_n; /* offset : 0x43c */
	union ieee1500_icon_rd_wdr16_ch_n rd_wdr16_ch_n; /* offset : 0x440 */
	union ieee1500_icon_rd_wdr15_ch_n rd_wdr15_ch_n; /* offset : 0x444 */
	union ieee1500_icon_rd_wdr14_ch_n rd_wdr14_ch_n; /* offset : 0x448 */
	union ieee1500_icon_rd_wdr13_ch_n rd_wdr13_ch_n; /* offset : 0x44c */
	union ieee1500_icon_rd_wdr12_ch_n rd_wdr12_ch_n; /* offset : 0x450 */
	union ieee1500_icon_rd_wdr11_ch_n rd_wdr11_ch_n; /* offset : 0x454 */
	union ieee1500_icon_rd_wdr10_ch_n rd_wdr10_ch_n; /* offset : 0x458 */
	union ieee1500_icon_rd_wdr9_ch_n rd_wdr9_ch_n; /* offset : 0x45c */
	union ieee1500_icon_rd_wdr8_ch_n rd_wdr8_ch_n; /* offset : 0x460 */
	union ieee1500_icon_rd_wdr7_ch_n rd_wdr7_ch_n; /* offset : 0x464 */
	union ieee1500_icon_rd_wdr6_ch_n rd_wdr6_ch_n; /* offset : 0x468 */
	union ieee1500_icon_rd_wdr5_ch_n rd_wdr5_ch_n; /* offset : 0x46c */
	union ieee1500_icon_rd_wdr4_ch_n rd_wdr4_ch_n; /* offset : 0x470 */
	union ieee1500_icon_rd_wdr3_ch_n rd_wdr3_ch_n; /* offset : 0x474 */
	union ieee1500_icon_rd_wdr2_ch_n rd_wdr2_ch_n; /* offset : 0x478 */
	union ieee1500_icon_rd_wdr1_ch_n rd_wdr1_ch_n; /* offset : 0x47c */
	union ieee1500_icon_rd_wdr0_ch_n rd_wdr0_ch_n; /* offset : 0x480 */
	union ieee1500_icon_rd_wdr18_ch_o rd_wdr18_ch_o; /* offset : 0x484 */
	union ieee1500_icon_rd_wdr17_ch_o rd_wdr17_ch_o; /* offset : 0x488 */
	union ieee1500_icon_rd_wdr16_ch_o rd_wdr16_ch_o; /* offset : 0x48c */
	union ieee1500_icon_rd_wdr15_ch_o rd_wdr15_ch_o; /* offset : 0x490 */
	union ieee1500_icon_rd_wdr14_ch_o rd_wdr14_ch_o; /* offset : 0x494 */
	union ieee1500_icon_rd_wdr13_ch_o rd_wdr13_ch_o; /* offset : 0x498 */
	union ieee1500_icon_rd_wdr12_ch_o rd_wdr12_ch_o; /* offset : 0x49c */
	union ieee1500_icon_rd_wdr11_ch_o rd_wdr11_ch_o; /* offset : 0x4a0 */
	union ieee1500_icon_rd_wdr10_ch_o rd_wdr10_ch_o; /* offset : 0x4a4 */
	union ieee1500_icon_rd_wdr9_ch_o rd_wdr9_ch_o; /* offset : 0x4a8 */
	union ieee1500_icon_rd_wdr8_ch_o rd_wdr8_ch_o; /* offset : 0x4ac */
	union ieee1500_icon_rd_wdr7_ch_o rd_wdr7_ch_o; /* offset : 0x4b0 */
	union ieee1500_icon_rd_wdr6_ch_o rd_wdr6_ch_o; /* offset : 0x4b4 */
	union ieee1500_icon_rd_wdr5_ch_o rd_wdr5_ch_o; /* offset : 0x4b8 */
	union ieee1500_icon_rd_wdr4_ch_o rd_wdr4_ch_o; /* offset : 0x4bc */
	union ieee1500_icon_rd_wdr3_ch_o rd_wdr3_ch_o; /* offset : 0x4c0 */
	union ieee1500_icon_rd_wdr2_ch_o rd_wdr2_ch_o; /* offset : 0x4c4 */
	union ieee1500_icon_rd_wdr1_ch_o rd_wdr1_ch_o; /* offset : 0x4c8 */
	union ieee1500_icon_rd_wdr0_ch_o rd_wdr0_ch_o; /* offset : 0x4cc */
	union ieee1500_icon_rd_wdr18_ch_p rd_wdr18_ch_p; /* offset : 0x4d0 */
	union ieee1500_icon_rd_wdr17_ch_p rd_wdr17_ch_p; /* offset : 0x4d4 */
	union ieee1500_icon_rd_wdr16_ch_p rd_wdr16_ch_p; /* offset : 0x4d8 */
	union ieee1500_icon_rd_wdr15_ch_p rd_wdr15_ch_p; /* offset : 0x4dc */
	union ieee1500_icon_rd_wdr14_ch_p rd_wdr14_ch_p; /* offset : 0x4e0 */
	union ieee1500_icon_rd_wdr13_ch_p rd_wdr13_ch_p; /* offset : 0x4e4 */
	union ieee1500_icon_rd_wdr12_ch_p rd_wdr12_ch_p; /* offset : 0x4e8 */
	union ieee1500_icon_rd_wdr11_ch_p rd_wdr11_ch_p; /* offset : 0x4ec */
	union ieee1500_icon_rd_wdr10_ch_p rd_wdr10_ch_p; /* offset : 0x4f0 */
	union ieee1500_icon_rd_wdr9_ch_p rd_wdr9_ch_p; /* offset : 0x4f4 */
	union ieee1500_icon_rd_wdr8_ch_p rd_wdr8_ch_p; /* offset : 0x4f8 */
	union ieee1500_icon_rd_wdr7_ch_p rd_wdr7_ch_p; /* offset : 0x4fc */
	union ieee1500_icon_rd_wdr6_ch_p rd_wdr6_ch_p; /* offset : 0x500 */
	union ieee1500_icon_rd_wdr5_ch_p rd_wdr5_ch_p; /* offset : 0x504 */
	union ieee1500_icon_rd_wdr4_ch_p rd_wdr4_ch_p; /* offset : 0x508 */
	union ieee1500_icon_rd_wdr3_ch_p rd_wdr3_ch_p; /* offset : 0x50c */
	union ieee1500_icon_rd_wdr2_ch_p rd_wdr2_ch_p; /* offset : 0x510 */
	union ieee1500_icon_rd_wdr1_ch_p rd_wdr1_ch_p; /* offset : 0x514 */
	union ieee1500_icon_rd_wdr0_ch_p rd_wdr0_ch_p; /* offset : 0x518 */
	union ieee1500_icon_fsm_debug fsm_debug; /* offset : 0x51c */
	union ieee1500_icon_io_ctrl0 io_ctrl0; /* offset : 0x520 */
	union ieee1500_icon_zq_con0 evt1_zq_con0; /* offset : 0x524 */
	union ieee1500_icon_zq_mon0 evt1_zq_mon0; /* offset : 0x528 */
	uint32_t reserved_1[8];
	union ieee1500_icon_icon_spec icon_spec; /* offset : 0x54c */
};

