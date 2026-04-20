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

union ddr_csr_mc_base1_cfg_temp_ctrl_ref_mode {
	struct {
		uint32_t cfg_temp_ctrl_ref_mode:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_read_dbi {
	struct {
		uint32_t cfg_read_dbi:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_write_dbi {
	struct {
		uint32_t cfg_write_dbi:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_data_mask {
	struct {
		uint32_t cfg_data_mask:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_ccd_s {
	struct {
		uint32_t cfg_ccd_s:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_rd_dq_parity_en {
	struct {
		uint32_t cfg_rd_dq_parity_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_wr_dq_parity_en {
	struct {
		uint32_t cfg_wr_dq_parity_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_ca_parity_en {
	struct {
		uint32_t cfg_ca_parity_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_bank_group_en {
	struct {
		uint32_t cfg_bank_group_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_hbm_cb_en {
	struct {
		uint32_t cfg_hbm_cb_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_tcr_enable {
	struct {
		uint32_t cfg_tcr_enable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_en_rrdp {
	struct {
		uint32_t cfg_en_rrdp:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_ccd_r {
	struct {
		uint32_t cfg_ccd_r:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_auto_mr_prog_en {
	struct {
		uint32_t cfg_auto_mr_prog_en:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_da28_lockout {
	struct {
		uint32_t cfg_da28_lockout:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_init_sbref_en {
	struct {
		uint32_t init_sbref_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_advance_activate_ready {
	struct {
		uint32_t cfg_advance_activate_ready:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_severity_en {
	struct {
		uint32_t cfg_severity_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_auto_ecs_on_ref {
	struct {
		uint32_t cfg_auto_ecs_on_ref:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_auto_ecs_on_sr {
	struct {
		uint32_t cfg_auto_ecs_on_sr:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_ecs_mberr_scrub_enable {
	struct {
		uint32_t cfg_ecs_mberr_scrub_enable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_ecs_reset {
	struct {
		uint32_t cfg_ecs_reset:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_strict_severity_decode {
	struct {
		uint32_t cfg_strict_severity_decode:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base1_cfg_phymstr_sr_loopback_en {
	struct {
		uint32_t cfg_phymstr_sr_loopback_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_ctrlr_soft_reset_n {
	struct {
		uint32_t ctrlr_soft_reset_n:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_autoinit_disable {
	struct {
		uint32_t init_autoinit_disable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_force_reset {
	struct {
		uint32_t init_force_reset:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_disable_cke {
	struct {
		uint32_t init_disable_cke:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_precharge_all {
	struct {
		uint32_t init_precharge_all:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_ctrlr_init_done {
	struct {
		uint32_t ctrlr_init_done:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_auto_ref_en {
	struct {
		uint32_t init_auto_ref_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_min_read_idle {
	struct {
		uint32_t cfg_min_read_idle:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_mem_rowbits {
	struct {
		uint32_t cfg_mem_rowbits:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_mem_bankbits {
	struct {
		uint32_t cfg_mem_bankbits:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_mr_w_req {
	struct {
		uint32_t init_mr_w_req:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_mr_addr {
	struct {
		uint32_t init_mr_addr:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_mr_wr_data {
	struct {
		uint32_t init_mr_wr_data:18; /* [17:0] */
		uint32_t reserved_31_18:14; /* [31:18] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_mr_wr_mask {
	struct {
		uint32_t init_mr_wr_mask:18; /* [17:0] */
		uint32_t reserved_31_18:14; /* [31:18] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_self_refresh {
	struct {
		uint32_t init_self_refresh:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_self_refresh_status {
	struct {
		uint32_t init_self_refresh_status:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_power_down {
	struct {
		uint32_t init_power_down:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_power_down_status {
	struct {
		uint32_t init_power_down_status:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_force_write_cs {
	struct {
		uint32_t init_force_write_cs:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_ctrlr_init_disable {
	struct {
		uint32_t cfg_ctrlr_init_disable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_ctrlr_ready {
	struct {
		uint32_t ctrlr_ready:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_memory_reset_mask {
	struct {
		uint32_t init_memory_reset_mask:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_cal_l_r_ack {
	struct {
		uint32_t init_cal_l_r_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_init_cal_l_read_complete {
	struct {
		uint32_t init_cal_l_read_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_ctrlupd_trig {
	struct {
		uint32_t cfg_ctrlupd_trig:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_ctrlupd_start_delay {
	struct {
		uint32_t cfg_ctrlupd_start_delay:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_dfi_t_ctrlupd_max {
	struct {
		uint32_t cfg_dfi_t_ctrlupd_max:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_phyupd_ack_delay {
	struct {
		uint32_t cfg_phyupd_ack_delay:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_dfi_t_ctrl_delay {
	struct {
		uint32_t cfg_dfi_t_ctrl_delay:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_dfi_t_dram_clk_enable {
	struct {
		uint32_t cfg_dfi_t_dram_clk_enable:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_bg_interleave {
	struct {
		uint32_t cfg_bg_interleave:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_dbi_byte_disable_source {
	struct {
		uint32_t cfg_dbi_byte_disable_source:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_dbi_byte_disable {
	struct {
		uint32_t cfg_dbi_byte_disable:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mc_base2_cfg_refresh_during_phy_training {
	struct {
		uint32_t cfg_refresh_during_phy_training:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_12hi {
	struct {
		uint32_t cfg_12hi:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_np2_rows {
	struct {
		uint32_t cfg_np2_rows:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_stat_interrupt_0 {
	struct {
		uint32_t stat_interrupt; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_interrupt_mask_0 {
	struct {
		uint32_t init_interrupt_mask; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_interrupt_gen_0 {
	struct {
		uint32_t init_interrupt_gen; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_ccd_throttle_cnt {
	struct {
		uint32_t init_ccd_throttle_cnt:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_disable_dfi_ctrlupd_req_in_sr {
	struct {
		uint32_t cfg_disable_dfi_ctrlupd_req_in_sr:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_amt_simultaneous_ram_write {
	struct {
		uint32_t amt_simultaneous_ram_write:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_en {
	struct {
		uint32_t init_rfm_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_raarfm {
	struct {
		uint32_t init_rfm_raarfm:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_raammt {
	struct {
		uint32_t init_rfm_raammt:11; /* [10:0] */
		uint32_t reserved_31_11:21; /* [31:11] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_raaref {
	struct {
		uint32_t init_rfm_raaref:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_rfm_raasrf {
	struct {
		uint32_t cfg_rfm_raasrf:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_axi_auto_pch {
	struct {
		uint32_t cfg_axi_auto_pch:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_axi_write_response_mport_order {
	struct {
		uint32_t cfg_axi_write_response_mport_order:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_axi_ready_disable {
	struct {
		uint32_t init_axi_ready_disable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_am_repeat_en {
	struct {
		uint32_t init_am_repeat_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_am_single_en {
	struct {
		uint32_t init_am_single_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_am_interval {
	struct {
		uint32_t init_am_interval; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_stat_am_complete {
	struct {
		uint32_t stat_am_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_arfu_value {
	struct {
		uint32_t cfg_arfu_value:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_hbm_le_32b_write_en {
	struct {
		uint32_t cfg_hbm_le_32b_write_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_dfi_phyupd_idle_sel {
	struct {
		uint32_t cfg_dfi_phyupd_idle_sel:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_aggressive_autopch {
	struct {
		uint32_t cfg_aggressive_autopch:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_idle_delay {
	struct {
		uint32_t cfg_idle_delay:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_force_bgpos0 {
	struct {
		uint32_t cfg_force_bgpos0:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_hold_sr_during_reset {
	struct {
		uint32_t init_hold_sr_during_reset:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_level_chg {
	struct {
		uint32_t init_rfm_level_chg:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_init_rfm_raaimt {
	struct {
		uint32_t init_rfm_raaimt:12; /* [11:0] */
		uint32_t reserved_31_12:20; /* [31:12] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_min_partial_issued_lifetime {
	struct {
		uint32_t cfg_min_partial_issued_lifetime:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_arfm_level {
	struct {
		uint32_t cfg_arfm_level:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_stat_poison_read_addr {
	struct {
		uint32_t stat_poison_read_addr:26; /* [25:0] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_stat_poison_read_rmw {
	struct {
		uint32_t stat_poison_read_rmw:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base3_cfg_2bit_bg_interleave {
	struct {
		uint32_t cfg_2bit_bg_interleave:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_init_ack {
	struct {
		uint32_t init_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_init_refresh {
	struct {
		uint32_t init_refresh:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_init_refresh_count {
	struct {
		uint32_t init_refresh_count:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_init_force_write {
	struct {
		uint32_t init_force_write:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_init_force_write_data_0 {
	struct {
		uint32_t init_force_write_data; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_mem_array_severity_code {
	struct {
		uint32_t stat_mem_array_severity_code; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_mem_array_mbit_corr_err {
	struct {
		uint32_t stat_mem_array_mbit_corr_err:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_ack_mr {
	struct {
		uint32_t stat_ack_mr:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_ack_refresh {
	struct {
		uint32_t stat_ack_refresh:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_ack_precharge_all {
	struct {
		uint32_t stat_ack_precharge_all:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_ack_nop {
	struct {
		uint32_t stat_ack_nop:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_idle {
	struct {
		uint32_t stat_idle:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mc_base4_stat_ack_rfm_level_chg {
	struct {
		uint32_t stat_ack_rfm_level_chg:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_t_rddata_en {
	struct {
		uint32_t cfg_dfi_t_rddata_en:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_t_phy_wrlat {
	struct {
		uint32_t cfg_dfi_t_phy_wrlat:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_phyupd_en {
	struct {
		uint32_t init_dfi_phyupd_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_lp_data_req {
	struct {
		uint32_t init_dfi_lp_data_req:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_lp_ctrl_req {
	struct {
		uint32_t init_dfi_lp_ctrl_req:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_dram_clk_disable {
	struct {
		uint32_t init_dfi_dram_clk_disable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_training_error {
	struct {
		uint32_t stat_dfi_training_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_error {
	struct {
		uint32_t stat_dfi_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_error_info {
	struct {
		uint32_t stat_dfi_error_info:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_data_byte_disable {
	struct {
		uint32_t cfg_dfi_data_byte_disable:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_init_complete {
	struct {
		uint32_t stat_dfi_init_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_training_complete {
	struct {
		uint32_t stat_dfi_training_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_lvl_sel {
	struct {
		uint32_t cfg_dfi_lvl_sel:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_lvl_periodic {
	struct {
		uint32_t cfg_dfi_lvl_periodic:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_lvl_pattern {
	struct {
		uint32_t cfg_dfi_lvl_pattern:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_tcr_temp {
	struct {
		uint32_t stat_dfi_tcr_temp:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_cattrip {
	struct {
		uint32_t stat_dfi_cattrip:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_phy_dfi_init_start {
	struct {
		uint32_t phy_dfi_init_start:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_training_complete {
	struct {
		uint32_t init_dfi_training_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_lp_mode_for_pd {
	struct {
		uint32_t cfg_lp_mode_for_pd:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_lp_ctrl_ack {
	struct {
		uint32_t stat_dfi_lp_ctrl_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_lp_ctrl_wakeup {
	struct {
		uint32_t init_dfi_lp_ctrl_wakeup:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_lp_data_ack {
	struct {
		uint32_t stat_dfi_lp_data_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_lp_data_wakeup {
	struct {
		uint32_t init_dfi_lp_data_wakeup:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_lp_data_wakeup_1 {
	struct {
		uint32_t cfg_lp_data_wakeup_1:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_lp_data_wakeup_2 {
	struct {
		uint32_t cfg_lp_data_wakeup_2:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_lp_dfi_state {
	struct {
		uint32_t stat_lp_dfi_state:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_dfi_init_dfi_phymstr_en {
	struct {
		uint32_t init_dfi_phymstr_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_stat_dfi_phymstr_ack {
	struct {
		uint32_t stat_dfi_phymstr_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_phy_ca_training_start {
	struct {
		uint32_t phy_ca_training_start:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_phy_ca_training_en {
	struct {
		uint32_t phy_ca_training_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_phy_ca_training_complete {
	struct {
		uint32_t phy_ca_training_complete:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_dfi_t_phy_wrdata {
	struct {
		uint32_t cfg_dfi_t_phy_wrdata:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_dfi_cfg_lp_data_wakeup_3 {
	struct {
		uint32_t cfg_lp_data_wakeup_3:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_mpfe_cfg_starve_timeout_p0 {
	struct {
		uint32_t cfg_starve_timeout_p0:12; /* [11:0] */
		uint32_t reserved_31_12:20; /* [31:12] */
	};
	uint32_t val;
};

union ddr_csr_mpfe_cfg_starve_timeout_p1 {
	struct {
		uint32_t cfg_starve_timeout_p1:12; /* [11:0] */
		uint32_t reserved_31_12:20; /* [31:12] */
	};
	uint32_t val;
};

union ddr_csr_mpfe_cfg_starve_timeout_p4 {
	struct {
		uint32_t cfg_starve_timeout_p4:12; /* [11:0] */
		uint32_t reserved_31_12:20; /* [31:12] */
	};
	uint32_t val;
};

union ddr_csr_mpfe_cfg_roundrobin_weight_p0 {
	struct {
		uint32_t cfg_roundrobin_weight_p0:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mpfe_cfg_roundrobin_weight_p1 {
	struct {
		uint32_t cfg_roundrobin_weight_p1:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_reorder_en {
	struct {
		uint32_t cfg_reorder_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_q_read_age_limit {
	struct {
		uint32_t cfg_q_read_age_limit:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_q_write_age_limit {
	struct {
		uint32_t cfg_q_write_age_limit:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_ro_write_limit {
	struct {
		uint32_t cfg_ro_write_limit:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_allow_write_act_thresh {
	struct {
		uint32_t cfg_allow_write_act_thresh:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_reorder_cfg_max_casreq {
	struct {
		uint32_t cfg_max_casreq:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_rmw_cfg_dm_en {
	struct {
		uint32_t cfg_dm_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_rmw_cfg_rmw_en {
	struct {
		uint32_t cfg_rmw_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_correction_en {
	struct {
		uint32_t cfg_ecc_correction_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_init_ecc_scrub_en {
	struct {
		uint32_t init_ecc_scrub_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_init_ecc_scrub_init_en {
	struct {
		uint32_t init_ecc_scrub_init_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_scrub_init_rmw {
	struct {
		uint32_t cfg_ecc_scrub_init_rmw:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_scrub_min_addr_0 {
	struct {
		uint32_t cfg_ecc_scrub_min_addr; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_scrub_max_addr_0 {
	struct {
		uint32_t cfg_ecc_scrub_max_addr; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_init_ecc_scrub_error_clr {
	struct {
		uint32_t init_ecc_scrub_error_clr:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_bypass {
	struct {
		uint32_t cfg_ecc_bypass:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_config_cfg_ecc_1bit_int_thresh {
	struct {
		uint32_t cfg_ecc_1bit_int_thresh:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_scrub_error_1bit_cnt {
	struct {
		uint32_t stat_ecc_scrub_error_1bit_cnt:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_scrub_error_2bit_cnt {
	struct {
		uint32_t stat_ecc_scrub_error_2bit_cnt:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_scrub_init_done {
	struct {
		uint32_t stat_ecc_scrub_init_done:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_init_write_data_1b_ecc_error_gen {
	struct {
		uint32_t init_write_data_1b_ecc_error_gen:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_init_write_data_2b_ecc_error_gen {
	struct {
		uint32_t init_write_data_2b_ecc_error_gen:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_int_ecc_1bit_thresh {
	struct {
		uint32_t stat_int_ecc_1bit_thresh:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_1bit_error_addr {
	struct {
		uint32_t stat_ecc_1bit_error_addr:26; /* [25:0] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_1bit_pos {
	struct {
		uint32_t stat_ecc_1bit_pos:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_1bit_rmw {
	struct {
		uint32_t stat_ecc_1bit_rmw:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_2bit_error_addr {
	struct {
		uint32_t stat_ecc_2bit_error_addr:26; /* [25:0] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union ddr_csr_ecc_stat_err_stat_ecc_2bit_rmw {
	struct {
		uint32_t stat_ecc_2bit_rmw:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_stat_di_write_data_parity_error {
	struct {
		uint32_t stat_di_write_data_parity_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_stat_write_data_parity_error {
	struct {
		uint32_t stat_write_data_parity_error:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_stat_read_data_parity_error {
	struct {
		uint32_t stat_read_data_parity_error:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_req {
	struct {
		uint32_t init_hbm_row_col_parity_error_gen_req:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_cmd {
	struct {
		uint32_t init_hbm_row_col_parity_error_gen_cmd:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_ack {
	struct {
		uint32_t init_hbm_row_col_parity_error_gen_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_data_parity_error_gen_req {
	struct {
		uint32_t init_hbm_data_parity_error_gen_req:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_data_parity_error_gen_sel {
	struct {
		uint32_t init_hbm_data_parity_error_gen_sel:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_data_parity_error_gen_ack {
	struct {
		uint32_t init_hbm_data_parity_error_gen_ack:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_write_data_perr_gen_pattern {
	struct {
		uint32_t init_hbm_write_data_perr_gen_pattern; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_init_hbm_read_data_perr_gen_pattern {
	struct {
		uint32_t init_hbm_read_data_perr_gen_pattern; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_parity_error_stat_ca_parity_error {
	struct {
		uint32_t stat_ca_parity_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_di_read_data_parity_odd_even_n {
	struct {
		uint32_t cfg_di_read_data_parity_odd_even_n:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_di_write_data_parity_odd_even_n {
	struct {
		uint32_t cfg_di_write_data_parity_odd_even_n:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_di_write_data_parity_enable {
	struct {
		uint32_t cfg_di_write_data_parity_enable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_di_read_force_parity_on_2b_ecc {
	struct {
		uint32_t cfg_di_read_force_parity_on_2b_ecc:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_data_int_init_di_read_data_parity_error_gen_0 {
	struct {
		uint32_t init_di_read_data_parity_error_gen_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_data_int_init_di_read_data_parity_error_gen_1 {
	struct {
		uint32_t init_di_read_data_parity_error_gen_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_axi_write_data_parity_enable {
	struct {
		uint32_t cfg_axi_write_data_parity_enable:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_data_int_cfg_csr_parity_error_mask {
	struct {
		uint32_t cfg_csr_parity_error_mask:28; /* [27:0] */
		uint32_t reserved_31_28:4; /* [31:28] */
	};
	uint32_t val;
};

union ddr_csr_data_int_stat_csr_parity_error {
	struct {
		uint32_t stat_csr_parity_error_addr_map:1; /* [0:0] */
		uint32_t stat_csr_parity_error_mc_base3:1; /* [1:1] */
		uint32_t stat_csr_parity_error_mc_base1:1; /* [2:2] */
		uint32_t stat_csr_parity_error_mc_base2:1; /* [3:3] */
		uint32_t stat_csr_parity_error_mem_test:1; /* [4:4] */
		uint32_t stat_csr_parity_error_mpfe:1; /* [5:5] */
		uint32_t stat_csr_parity_error_reorder:1; /* [6:6] */
		uint32_t stat_csr_parity_error_rmw:1; /* [7:7] */
		uint32_t stat_csr_parity_error_ecc_config:1; /* [8:8] */
		uint32_t stat_csr_parity_error_read_capt:1; /* [9:9] */
		uint32_t stat_csr_parity_error_adv_mem_test:1; /* [10:10] */
		uint32_t stat_csr_parity_error_mta:1; /* [11:11] */
		uint32_t stat_csr_parity_error_dyn_width_adj:1; /* [12:12] */
		uint32_t stat_csr_parity_error_ca_par_err:1; /* [13:13] */
		uint32_t stat_csr_parity_error_flush_rd:1; /* [14:14] */
		uint32_t stat_csr_parity_error_mr_reload:1; /* [15:15] */
		uint32_t stat_csr_parity_error_mb:1; /* [16:16] */
		uint32_t stat_csr_parity_error_reserved0:1; /* [17:17] */
		uint32_t stat_csr_parity_error_dfi:1; /* [18:18] */
		uint32_t stat_csr_parity_error_pream_cal:1; /* [19:19] */
		uint32_t stat_csr_parity_error_data_int:1; /* [20:20] */
		uint32_t stat_csr_parity_error_axi_if:1; /* [21:21] */
		uint32_t stat_csr_parity_error_act_mon:1; /* [22:22] */
		uint32_t stat_csr_parity_error_csr_custom:1; /* [23:23] */
		uint32_t stat_csr_parity_error_mc_base4:1; /* [24:24] */
		uint32_t stat_csr_parity_error_parity_error:1; /* [25:25] */
		uint32_t stat_csr_parity_error_ecc_stat_err:1; /* [26:26] */
		uint32_t stat_csr_parity_error_mc_base5:1; /* [27:27] */
		uint32_t reserved_31_28:4; /* [31:28] */
	};
	uint32_t val;
};

union ddr_csr_data_int_init_csr_parity_error_gen {
	struct {
		uint32_t init_csr_parity_error_gen:28; /* [27:0] */
		uint32_t reserved_31_28:4; /* [31:28] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_stat_axi_write_data_parity_error {
	struct {
		uint32_t stat_axi_write_data_parity_error:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_cfg_axi_start_address_axi1_0 {
	struct {
		uint32_t cfg_axi_start_address_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_cfg_axi_end_address_axi1_0 {
	struct {
		uint32_t cfg_axi_end_address_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_cfg_mem_start_address_axi1_0 {
	struct {
		uint32_t cfg_mem_start_address_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_cfg_axird_id_reorder_en {
	struct {
		uint32_t cfg_axird_id_reorder_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_cfg_axird_interleave_sel {
	struct {
		uint32_t cfg_axird_interleave_sel:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_axi_if_stat_axi_decerr {
	struct {
		uint32_t stat_axi_decerr:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_en {
	struct {
		uint32_t mt_en:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_en_single {
	struct {
		uint32_t mt_en_single:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_stop_on_error {
	struct {
		uint32_t mt_stop_on_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_rd_only {
	struct {
		uint32_t mt_rd_only:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wr_only {
	struct {
		uint32_t mt_wr_only:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_data_pattern {
	struct {
		uint32_t mt_data_pattern:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_addr_pattern {
	struct {
		uint32_t mt_addr_pattern:2; /* [1:0] */
		uint32_t reserved_31_2:30; /* [31:2] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_data_invert {
	struct {
		uint32_t mt_data_invert:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_addr_bits {
	struct {
		uint32_t mt_addr_bits:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_sts {
	struct {
		uint32_t mt_error_sts:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_done_ack {
	struct {
		uint32_t mt_done_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_max_wd {
	struct {
		uint32_t mt_max_wd:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_max_ex {
	struct {
		uint32_t mt_max_ex:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_max_ac {
	struct {
		uint32_t mt_max_ac:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_cycles {
	struct {
		uint32_t mt_cycles:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_arb_mem_addr {
	struct {
		uint32_t mt_arb_mem_addr:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_arb_ack {
	struct {
		uint32_t mt_arb_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_0 {
	struct {
		uint32_t mt_wd_wdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_1 {
	struct {
		uint32_t mt_wd_wdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_2 {
	struct {
		uint32_t mt_wd_wdata_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_3 {
	struct {
		uint32_t mt_wd_wdata_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_4 {
	struct {
		uint32_t mt_wd_wdata_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_5 {
	struct {
		uint32_t mt_wd_wdata_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_6 {
	struct {
		uint32_t mt_wd_wdata_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_7 {
	struct {
		uint32_t mt_wd_wdata_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_8 {
	struct {
		uint32_t mt_wd_wdata_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_9 {
	struct {
		uint32_t mt_wd_wdata_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_10 {
	struct {
		uint32_t mt_wd_wdata_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_11 {
	struct {
		uint32_t mt_wd_wdata_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_12 {
	struct {
		uint32_t mt_wd_wdata_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_13 {
	struct {
		uint32_t mt_wd_wdata_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_14 {
	struct {
		uint32_t mt_wd_wdata_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_15 {
	struct {
		uint32_t mt_wd_wdata_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_wdata_16 {
	struct {
		uint32_t mt_wd_wdata_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_0 {
	struct {
		uint32_t mt_ex_wdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_1 {
	struct {
		uint32_t mt_ex_wdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_2 {
	struct {
		uint32_t mt_ex_wdata_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_3 {
	struct {
		uint32_t mt_ex_wdata_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_4 {
	struct {
		uint32_t mt_ex_wdata_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_5 {
	struct {
		uint32_t mt_ex_wdata_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_6 {
	struct {
		uint32_t mt_ex_wdata_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_7 {
	struct {
		uint32_t mt_ex_wdata_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_8 {
	struct {
		uint32_t mt_ex_wdata_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_9 {
	struct {
		uint32_t mt_ex_wdata_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_10 {
	struct {
		uint32_t mt_ex_wdata_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_11 {
	struct {
		uint32_t mt_ex_wdata_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_12 {
	struct {
		uint32_t mt_ex_wdata_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_13 {
	struct {
		uint32_t mt_ex_wdata_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_14 {
	struct {
		uint32_t mt_ex_wdata_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_15 {
	struct {
		uint32_t mt_ex_wdata_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_wdata_16 {
	struct {
		uint32_t mt_ex_wdata_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ac_wdata_0 {
	struct {
		uint32_t mt_ac_wdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ac_wdata_1 {
	struct {
		uint32_t mt_ac_wdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_0 {
	struct {
		uint32_t mt_wd_rdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_1 {
	struct {
		uint32_t mt_wd_rdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_2 {
	struct {
		uint32_t mt_wd_rdata_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_3 {
	struct {
		uint32_t mt_wd_rdata_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_4 {
	struct {
		uint32_t mt_wd_rdata_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_5 {
	struct {
		uint32_t mt_wd_rdata_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_6 {
	struct {
		uint32_t mt_wd_rdata_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_7 {
	struct {
		uint32_t mt_wd_rdata_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_8 {
	struct {
		uint32_t mt_wd_rdata_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_9 {
	struct {
		uint32_t mt_wd_rdata_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_10 {
	struct {
		uint32_t mt_wd_rdata_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_11 {
	struct {
		uint32_t mt_wd_rdata_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_12 {
	struct {
		uint32_t mt_wd_rdata_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_13 {
	struct {
		uint32_t mt_wd_rdata_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_14 {
	struct {
		uint32_t mt_wd_rdata_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_15 {
	struct {
		uint32_t mt_wd_rdata_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_wd_rdata_16 {
	struct {
		uint32_t mt_wd_rdata_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_0 {
	struct {
		uint32_t mt_ex_rdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_1 {
	struct {
		uint32_t mt_ex_rdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_2 {
	struct {
		uint32_t mt_ex_rdata_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_3 {
	struct {
		uint32_t mt_ex_rdata_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_4 {
	struct {
		uint32_t mt_ex_rdata_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_5 {
	struct {
		uint32_t mt_ex_rdata_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_6 {
	struct {
		uint32_t mt_ex_rdata_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_7 {
	struct {
		uint32_t mt_ex_rdata_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_8 {
	struct {
		uint32_t mt_ex_rdata_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_9 {
	struct {
		uint32_t mt_ex_rdata_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_10 {
	struct {
		uint32_t mt_ex_rdata_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_11 {
	struct {
		uint32_t mt_ex_rdata_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_12 {
	struct {
		uint32_t mt_ex_rdata_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_13 {
	struct {
		uint32_t mt_ex_rdata_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_14 {
	struct {
		uint32_t mt_ex_rdata_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_15 {
	struct {
		uint32_t mt_ex_rdata_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ex_rdata_16 {
	struct {
		uint32_t mt_ex_rdata_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ac_rdata_0 {
	struct {
		uint32_t mt_ac_rdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_ac_rdata_1 {
	struct {
		uint32_t mt_ac_rdata_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_start_addr_0 {
	struct {
		uint32_t mt_start_addr:26; /* [25:0] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_0 {
	struct {
		uint32_t mt_error_mask_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_1 {
	struct {
		uint32_t mt_error_mask_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_2 {
	struct {
		uint32_t mt_error_mask_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_3 {
	struct {
		uint32_t mt_error_mask_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_4 {
	struct {
		uint32_t mt_error_mask_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_5 {
	struct {
		uint32_t mt_error_mask_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_6 {
	struct {
		uint32_t mt_error_mask_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_7 {
	struct {
		uint32_t mt_error_mask_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_8 {
	struct {
		uint32_t mt_error_mask_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_9 {
	struct {
		uint32_t mt_error_mask_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_10 {
	struct {
		uint32_t mt_error_mask_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_11 {
	struct {
		uint32_t mt_error_mask_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_12 {
	struct {
		uint32_t mt_error_mask_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_13 {
	struct {
		uint32_t mt_error_mask_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_14 {
	struct {
		uint32_t mt_error_mask_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_15 {
	struct {
		uint32_t mt_error_mask_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_error_mask_16 {
	struct {
		uint32_t mt_error_mask_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_user_data_pattern {
	struct {
		uint32_t mt_user_data_pattern:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_alg_auto_pch {
	struct {
		uint32_t mt_alg_auto_pch:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_0 {
	struct {
		uint32_t mt_output_mask_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_1 {
	struct {
		uint32_t mt_output_mask_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_2 {
	struct {
		uint32_t mt_output_mask_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_3 {
	struct {
		uint32_t mt_output_mask_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_4 {
	struct {
		uint32_t mt_output_mask_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_5 {
	struct {
		uint32_t mt_output_mask_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_6 {
	struct {
		uint32_t mt_output_mask_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_7 {
	struct {
		uint32_t mt_output_mask_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_8 {
	struct {
		uint32_t mt_output_mask_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_9 {
	struct {
		uint32_t mt_output_mask_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_10 {
	struct {
		uint32_t mt_output_mask_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_11 {
	struct {
		uint32_t mt_output_mask_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_12 {
	struct {
		uint32_t mt_output_mask_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_13 {
	struct {
		uint32_t mt_output_mask_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_14 {
	struct {
		uint32_t mt_output_mask_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_15 {
	struct {
		uint32_t mt_output_mask_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_mask_16 {
	struct {
		uint32_t mt_output_mask_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mem_test_mt_output_masked_value {
	struct {
		uint32_t mt_output_masked_value:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_waddr {
	struct {
		uint32_t amt_useq_iram_waddr:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_wdata_0 {
	struct {
		uint32_t amt_useq_iram_wdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_wdata_1 {
	struct {
		uint32_t amt_useq_iram_wdata_47_32:16; /* [15:0] */
		uint32_t reserved_63_48:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_rdata_0 {
	struct {
		uint32_t amt_useq_iram_rdata_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_rdata_1 {
	struct {
		uint32_t amt_useq_iram_rdata_47_32:16; /* [15:0] */
		uint32_t reserved_63_48:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_iram_ack {
	struct {
		uint32_t amt_useq_iram_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_rf_waddr {
	struct {
		uint32_t amt_useq_rf_waddr:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_rf_wdata_0 {
	struct {
		uint32_t amt_useq_rf_wdata; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_rf_rdata_0 {
	struct {
		uint32_t amt_useq_rf_rdata; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_rf_ack {
	struct {
		uint32_t amt_useq_rf_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_exceptions {
	struct {
		uint32_t amt_useq_exceptions; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_pc {
	struct {
		uint32_t amt_useq_pc:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_inst_counter_0 {
	struct {
		uint32_t amt_useq_inst_counter_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_inst_counter_1 {
	struct {
		uint32_t amt_useq_inst_counter_49_32:18; /* [17:0] */
		uint32_t reserved_63_50:14; /* [31:18] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_useq_mta_storage_sel {
	struct {
		uint32_t amt_useq_mta_storage_sel:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_adv_mem_test_amt_sequencer_enable {
	struct {
		uint32_t amt_sequencer_enable:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_error_group_sel {
	struct {
		uint32_t cfg_error_group_sel:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_data_sel {
	struct {
		uint32_t cfg_data_sel:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_mode {
	struct {
		uint32_t cfg_trig_mode:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_post_trig_cycs {
	struct {
		uint32_t cfg_post_trig_cycs:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_mask {
	struct {
		uint32_t cfg_trig_mask:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_en_mask {
	struct {
		uint32_t cfg_en_mask:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_addr {
	struct {
		uint32_t mtc_acq_addr:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_cycs_stored {
	struct {
		uint32_t mtc_acq_cycs_stored:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_trig_detect {
	struct {
		uint32_t mtc_acq_trig_detect:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_mem_trig_addr {
	struct {
		uint32_t mtc_acq_mem_trig_addr:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_mem_last_addr {
	struct {
		uint32_t mtc_acq_mem_last_addr:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_ack {
	struct {
		uint32_t mtc_ack:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_mt_addr_0 {
	struct {
		uint32_t cfg_trig_mt_addr:26; /* [25:0] */
		uint32_t reserved_31_26:6; /* [31:26] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_0 {
	struct {
		uint32_t cfg_trig_err_mask_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_1 {
	struct {
		uint32_t cfg_trig_err_mask_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_2 {
	struct {
		uint32_t cfg_trig_err_mask_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_3 {
	struct {
		uint32_t cfg_trig_err_mask_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_4 {
	struct {
		uint32_t cfg_trig_err_mask_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_5 {
	struct {
		uint32_t cfg_trig_err_mask_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_6 {
	struct {
		uint32_t cfg_trig_err_mask_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_7 {
	struct {
		uint32_t cfg_trig_err_mask_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_8 {
	struct {
		uint32_t cfg_trig_err_mask_287_256; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_9 {
	struct {
		uint32_t cfg_trig_err_mask_319_288; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_10 {
	struct {
		uint32_t cfg_trig_err_mask_351_320; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_11 {
	struct {
		uint32_t cfg_trig_err_mask_383_352; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_12 {
	struct {
		uint32_t cfg_trig_err_mask_415_384; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_13 {
	struct {
		uint32_t cfg_trig_err_mask_447_416; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_14 {
	struct {
		uint32_t cfg_trig_err_mask_479_448; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_15 {
	struct {
		uint32_t cfg_trig_err_mask_511_480; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_trig_err_mask_16 {
	struct {
		uint32_t cfg_trig_err_mask_543_512; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_0 {
	struct {
		uint32_t mtc_acq_wr_data_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_1 {
	struct {
		uint32_t mtc_acq_wr_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_2 {
	struct {
		uint32_t mtc_acq_wr_data_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_3 {
	struct {
		uint32_t mtc_acq_wr_data_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_4 {
	struct {
		uint32_t mtc_acq_wr_data_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_5 {
	struct {
		uint32_t mtc_acq_wr_data_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_6 {
	struct {
		uint32_t mtc_acq_wr_data_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_7 {
	struct {
		uint32_t mtc_acq_wr_data_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_wr_data_8 {
	struct {
		uint32_t mtc_acq_wr_data_272_256:17; /* [16:0] */
		uint32_t reserved_287_273:15; /* [31:17] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_0 {
	struct {
		uint32_t mtc_acq_rd_data_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_1 {
	struct {
		uint32_t mtc_acq_rd_data_63_32; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_2 {
	struct {
		uint32_t mtc_acq_rd_data_95_64; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_3 {
	struct {
		uint32_t mtc_acq_rd_data_127_96; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_4 {
	struct {
		uint32_t mtc_acq_rd_data_159_128; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_5 {
	struct {
		uint32_t mtc_acq_rd_data_191_160; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_6 {
	struct {
		uint32_t mtc_acq_rd_data_223_192; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_7 {
	struct {
		uint32_t mtc_acq_rd_data_255_224; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_rd_data_8 {
	struct {
		uint32_t mtc_acq_rd_data_272_256:17; /* [16:0] */
		uint32_t reserved_287_273:15; /* [31:17] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_pre_trig_cycs {
	struct {
		uint32_t cfg_pre_trig_cycs:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_error_cnt {
	struct {
		uint32_t mtc_acq_error_cnt:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_error_cnt_ovfl {
	struct {
		uint32_t mtc_acq_error_cnt_ovfl:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_cfg_data_sel_first_error {
	struct {
		uint32_t cfg_data_sel_first_error:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_mta_mtc_acq_data_sel {
	struct {
		uint32_t mtc_acq_data_sel:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_ccd_l {
	struct {
		uint32_t cfg_ccd_l:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_wtr_s {
	struct {
		uint32_t cfg_wtr_s:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_wtr_l {
	struct {
		uint32_t cfg_wtr_l:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rrefd {
	struct {
		uint32_t cfg_rrefd:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rcd_rd {
	struct {
		uint32_t cfg_rcd_rd:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rcd_wr {
	struct {
		uint32_t cfg_rcd_wr:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_ras {
	struct {
		uint32_t cfg_ras:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rrd_s {
	struct {
		uint32_t cfg_rrd_s:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rrd_l {
	struct {
		uint32_t cfg_rrd_l:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rp {
	struct {
		uint32_t cfg_rp:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rc {
	struct {
		uint32_t cfg_rc:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_faw {
	struct {
		uint32_t cfg_faw:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rfc {
	struct {
		uint32_t cfg_rfc:11; /* [10:0] */
		uint32_t reserved_31_11:21; /* [31:11] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rfcsb {
	struct {
		uint32_t cfg_rfcsb:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rtp {
	struct {
		uint32_t cfg_rtp:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_wr {
	struct {
		uint32_t cfg_wr:8; /* [7:0] */
		uint32_t reserved_31_8:24; /* [31:8] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_xp {
	struct {
		uint32_t cfg_xp:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_xpr {
	struct {
		uint32_t cfg_xpr:11; /* [10:0] */
		uint32_t reserved_31_11:21; /* [31:11] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_xs {
	struct {
		uint32_t cfg_xs:11; /* [10:0] */
		uint32_t reserved_31_11:21; /* [31:11] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_mod {
	struct {
		uint32_t cfg_mod:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_wl {
	struct {
		uint32_t cfg_wl:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_rl {
	struct {
		uint32_t cfg_rl:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_cksre {
	struct {
		uint32_t cfg_cksre:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_cksrx {
	struct {
		uint32_t cfg_cksrx:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_abref {
	struct {
		uint32_t init_abref:24; /* [23:0] */
		uint32_t reserved_31_24:8; /* [31:24] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_ref_per {
	struct {
		uint32_t init_ref_per:17; /* [16:0] */
		uint32_t reserved_31_17:15; /* [31:17] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_startup_delay {
	struct {
		uint32_t cfg_startup_delay:21; /* [20:0] */
		uint32_t reserved_31_21:11; /* [31:21] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_idle_time_to_self_refresh {
	struct {
		uint32_t cfg_idle_time_to_self_refresh; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_idle_time_to_power_down {
	struct {
		uint32_t init_idle_time_to_power_down; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_1 {
	struct {
		uint32_t init_idle_time_to_lp_data_wakeup_1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_2 {
	struct {
		uint32_t init_idle_time_to_lp_data_wakeup_2; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_sbref_issue_per {
	struct {
		uint32_t cfg_sbref_issue_per:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_ecc_scrub_period {
	struct {
		uint32_t cfg_ecc_scrub_period:13; /* [12:0] */
		uint32_t reserved_31_13:19; /* [31:13] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_read_to_write {
	struct {
		uint32_t cfg_read_to_write:5; /* [4:0] */
		uint32_t reserved_31_5:27; /* [31:5] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_ds {
	struct {
		uint32_t cfg_ds:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_hbm_parity_latency {
	struct {
		uint32_t cfg_hbm_parity_latency:3; /* [2:0] */
		uint32_t reserved_31_3:29; /* [31:3] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_int_vref {
	struct {
		uint32_t cfg_int_vref:16; /* [15:0] */
		uint32_t reserved_31_16:16; /* [31:16] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_lp_data_duration_1 {
	struct {
		uint32_t cfg_lp_data_duration_1:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_lp_data_duration_2 {
	struct {
		uint32_t cfg_lp_data_duration_2:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_vref_settle_time {
	struct {
		uint32_t cfg_vref_settle_time:14; /* [13:0] */
		uint32_t reserved_31_14:18; /* [31:14] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_3 {
	struct {
		uint32_t init_idle_time_to_lp_data_wakeup_3; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_mc_base5_cfg_lp_data_duration_3 {
	struct {
		uint32_t cfg_lp_data_duration_3:10; /* [9:0] */
		uint32_t reserved_31_10:22; /* [31:10] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wr_cmd {
	struct {
		uint32_t am_wr_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wr_ap_cmd {
	struct {
		uint32_t am_wr_ap_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rd_cmd {
	struct {
		uint32_t am_rd_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rd_ap_cmd {
	struct {
		uint32_t am_rd_ap_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_refresh_cmd {
	struct {
		uint32_t am_refresh_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_act_cmd {
	struct {
		uint32_t am_act_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_precharge_cmd {
	struct {
		uint32_t am_precharge_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_precharge_all_cmd {
	struct {
		uint32_t am_precharge_all_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_power_down {
	struct {
		uint32_t am_power_down; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_self_refresh {
	struct {
		uint32_t am_self_refresh; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rd_to_wr_switch {
	struct {
		uint32_t am_rd_to_wr_switch; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_ro_age_limit {
	struct {
		uint32_t am_ro_age_limit; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rmw_cycle {
	struct {
		uint32_t am_rmw_cycle; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_interval_count_axi1 {
	struct {
		uint32_t am_interval_count_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wac_active_axi1 {
	struct {
		uint32_t am_wac_active_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wac_stall_axi1 {
	struct {
		uint32_t am_wac_stall_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rac_active_axi1 {
	struct {
		uint32_t am_rac_active_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rac_stall_axi1 {
	struct {
		uint32_t am_rac_stall_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdc_active_axi1 {
	struct {
		uint32_t am_wdc_active_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdc_stall_axi1 {
	struct {
		uint32_t am_wdc_stall_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdc_active_axi1 {
	struct {
		uint32_t am_rdc_active_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdc_stall_axi1 {
	struct {
		uint32_t am_rdc_stall_axi1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_ctrlr_queue_sum_0 {
	struct {
		uint32_t am_ctrlr_queue_sum_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_ctrlr_queue_sum_1 {
	struct {
		uint32_t am_ctrlr_queue_sum_38_32:7; /* [6:0] */
		uint32_t reserved_63_39:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_ctrlr_queue_max_0 {
	struct {
		uint32_t am_ctrlr_queue_max:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_ctrlr_queue_min_0 {
	struct {
		uint32_t am_ctrlr_queue_min:7; /* [6:0] */
		uint32_t reserved_31_7:25; /* [31:7] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wcf_sum_axi1_0 {
	struct {
		uint32_t am_wcf_sum_axi1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wcf_sum_axi1_1 {
	struct {
		uint32_t am_wcf_sum_axi1_37_32:6; /* [5:0] */
		uint32_t reserved_63_38:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wcf_max_axi1_0 {
	struct {
		uint32_t am_wcf_max_axi1:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wcf_min_axi1_0 {
	struct {
		uint32_t am_wcf_min_axi1:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rcf_sum_axi1_0 {
	struct {
		uint32_t am_rcf_sum_axi1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rcf_sum_axi1_1 {
	struct {
		uint32_t am_rcf_sum_axi1_37_32:6; /* [5:0] */
		uint32_t reserved_63_38:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rcf_max_axi1_0 {
	struct {
		uint32_t am_rcf_max_axi1:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rcf_min_axi1_0 {
	struct {
		uint32_t am_rcf_min_axi1:6; /* [5:0] */
		uint32_t reserved_31_6:26; /* [31:6] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdf_sum_axi1_0 {
	struct {
		uint32_t am_wdf_sum_axi1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdf_sum_axi1_1 {
	struct {
		uint32_t am_wdf_sum_axi1_40_32:9; /* [8:0] */
		uint32_t reserved_63_41:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdf_max_axi1_0 {
	struct {
		uint32_t am_wdf_max_axi1:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_wdf_min_axi1_0 {
	struct {
		uint32_t am_wdf_min_axi1:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdf_sum_axi1_0 {
	struct {
		uint32_t am_rdf_sum_axi1_31_0; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdf_sum_axi1_1 {
	struct {
		uint32_t am_rdf_sum_axi1_40_32:9; /* [8:0] */
		uint32_t reserved_63_41:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdf_max_axi1_0 {
	struct {
		uint32_t am_rdf_max_axi1:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rdf_min_axi1_0 {
	struct {
		uint32_t am_rdf_min_axi1:9; /* [8:0] */
		uint32_t reserved_31_9:23; /* [31:9] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_rfm_cmd {
	struct {
		uint32_t am_rfm_cmd; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_cfg_am_rfm_threshold {
	struct {
		uint32_t cfg_am_rfm_threshold:20; /* [19:0] */
		uint32_t reserved_31_20:12; /* [31:20] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_power_down_transition_count {
	struct {
		uint32_t am_power_down_transition_count; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_1 {
	struct {
		uint32_t am_lp_data_1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_transition_count_1 {
	struct {
		uint32_t am_lp_data_transition_count_1; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_2 {
	struct {
		uint32_t am_lp_data_2; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_transition_count_2 {
	struct {
		uint32_t am_lp_data_transition_count_2; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_3 {
	struct {
		uint32_t am_lp_data_3; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_act_mon_am_lp_data_transition_count_3 {
	struct {
		uint32_t am_lp_data_transition_count_3; /* [31:0] */
	};
	uint32_t val;
};

union ddr_csr_csr_custom_phy_wck_toggle_dly {
	struct {
		uint32_t phy_wck_toggle_dly:1; /* [0:0] */
		uint32_t reserved_31_1:31; /* [31:1] */
	};
	uint32_t val;
};

union ddr_csr_csr_custom_phy_rddata_en_dly {
	struct {
		uint32_t phy_rddata_en_dly:4; /* [3:0] */
		uint32_t reserved_31_4:28; /* [31:4] */
	};
	uint32_t val;
};

struct ddr_csr {
	uint32_t reserved_1[4109];
	union ddr_csr_mc_base1_cfg_temp_ctrl_ref_mode mc_base1_cfg_temp_ctrl_ref_mode;
	/* offset : 0x4034 */
	uint32_t reserved_2[2];
	union ddr_csr_mc_base1_cfg_read_dbi mc_base1_cfg_read_dbi; /* offset : 0x4040 */
	union ddr_csr_mc_base1_cfg_write_dbi mc_base1_cfg_write_dbi; /* offset : 0x4044 */
	union ddr_csr_mc_base1_cfg_data_mask mc_base1_cfg_data_mask; /* offset : 0x4048 */
	uint32_t reserved_3[6];
	union ddr_csr_mc_base1_cfg_ccd_s mc_base1_cfg_ccd_s; /* offset : 0x4064 */
	uint32_t reserved_4[14];
	union ddr_csr_mc_base1_cfg_rd_dq_parity_en mc_base1_cfg_rd_dq_parity_en; /* offset : 0x40a0 */
	union ddr_csr_mc_base1_cfg_wr_dq_parity_en mc_base1_cfg_wr_dq_parity_en; /* offset : 0x40a4 */
	union ddr_csr_mc_base1_cfg_ca_parity_en mc_base1_cfg_ca_parity_en; /* offset : 0x40a8 */
	union ddr_csr_mc_base1_cfg_bank_group_en mc_base1_cfg_bank_group_en; /* offset : 0x40ac */
	union ddr_csr_mc_base1_cfg_hbm_cb_en mc_base1_cfg_hbm_cb_en; /* offset : 0x40b0 */
	uint32_t reserved_5;
	union ddr_csr_mc_base1_cfg_tcr_enable mc_base1_cfg_tcr_enable; /* offset : 0x40b8 */
	uint32_t reserved_6;
	union ddr_csr_mc_base1_cfg_en_rrdp mc_base1_cfg_en_rrdp; /* offset : 0x40c0 */
	uint32_t reserved_7;
	union ddr_csr_mc_base1_cfg_ccd_r mc_base1_cfg_ccd_r; /* offset : 0x40c8 */
	union ddr_csr_mc_base1_cfg_auto_mr_prog_en mc_base1_cfg_auto_mr_prog_en; /* offset : 0x40cc */
	uint32_t reserved_8;
	union ddr_csr_mc_base1_cfg_da28_lockout mc_base1_cfg_da28_lockout; /* offset : 0x40d4 */
	uint32_t reserved_9[102];
	union ddr_csr_mc_base1_init_sbref_en mc_base1_init_sbref_en; /* offset : 0x4270 */
	uint32_t reserved_10[3];
	union ddr_csr_mc_base1_cfg_advance_activate_ready mc_base1_cfg_advance_activate_ready;
	/* offset : 0x4280 */
	uint32_t reserved_11[7];
	union ddr_csr_mc_base1_cfg_severity_en mc_base1_cfg_severity_en; /* offset : 0x42a0 */
	union ddr_csr_mc_base1_cfg_auto_ecs_on_ref mc_base1_cfg_auto_ecs_on_ref; /* offset : 0x42a4 */
	union ddr_csr_mc_base1_cfg_auto_ecs_on_sr mc_base1_cfg_auto_ecs_on_sr; /* offset : 0x42a8 */
	union ddr_csr_mc_base1_cfg_ecs_mberr_scrub_enable mc_base1_cfg_ecs_mberr_scrub_enable;
	/* offset : 0x42ac */
	union ddr_csr_mc_base1_cfg_ecs_reset mc_base1_cfg_ecs_reset; /* offset : 0x42b0 */
	union ddr_csr_mc_base1_cfg_strict_severity_decode mc_base1_cfg_strict_severity_decode;
	/* offset : 0x42b4 */
	union ddr_csr_mc_base1_cfg_phymstr_sr_loopback_en mc_base1_cfg_phymstr_sr_loopback_en;
	/* offset : 0x42b8 */
	uint32_t reserved_12[81];
	union ddr_csr_mc_base2_ctrlr_soft_reset_n mc_base2_ctrlr_soft_reset_n; /* offset : 0x4400 */
	uint32_t reserved_13[2];
	union ddr_csr_mc_base2_init_autoinit_disable mc_base2_init_autoinit_disable;
	/* offset : 0x440c */
	union ddr_csr_mc_base2_init_force_reset mc_base2_init_force_reset; /* offset : 0x4410 */
	uint32_t reserved_14;
	union ddr_csr_mc_base2_init_disable_cke mc_base2_init_disable_cke; /* offset : 0x4418 */
	uint32_t reserved_15;
	union ddr_csr_mc_base2_init_precharge_all mc_base2_init_precharge_all; /* offset : 0x4420 */
	uint32_t reserved_16[2];
	union ddr_csr_mc_base2_ctrlr_init_done mc_base2_ctrlr_init_done; /* offset : 0x442c */
	union ddr_csr_mc_base2_init_auto_ref_en mc_base2_init_auto_ref_en; /* offset : 0x4430 */
	uint32_t reserved_17[24];
	union ddr_csr_mc_base2_cfg_min_read_idle mc_base2_cfg_min_read_idle; /* offset : 0x4494 */
	uint32_t reserved_18[11];
	union ddr_csr_mc_base2_cfg_mem_rowbits mc_base2_cfg_mem_rowbits; /* offset : 0x44c4 */
	union ddr_csr_mc_base2_cfg_mem_bankbits mc_base2_cfg_mem_bankbits; /* offset : 0x44c8 */
	uint32_t reserved_19[50];
	union ddr_csr_mc_base2_init_mr_w_req mc_base2_init_mr_w_req; /* offset : 0x4594 */
	union ddr_csr_mc_base2_init_mr_addr mc_base2_init_mr_addr; /* offset : 0x4598 */
	union ddr_csr_mc_base2_init_mr_wr_data mc_base2_init_mr_wr_data; /* offset : 0x459c */
	union ddr_csr_mc_base2_init_mr_wr_mask mc_base2_init_mr_wr_mask; /* offset : 0x45a0 */
	uint32_t reserved_20[11];
	union ddr_csr_mc_base2_init_self_refresh mc_base2_init_self_refresh; /* offset : 0x45d0 */
	union ddr_csr_mc_base2_init_self_refresh_status mc_base2_init_self_refresh_status;
	/* offset : 0x45d4 */
	union ddr_csr_mc_base2_init_power_down mc_base2_init_power_down; /* offset : 0x45d8 */
	union ddr_csr_mc_base2_init_power_down_status mc_base2_init_power_down_status;
	/* offset : 0x45dc */
	union ddr_csr_mc_base2_init_force_write_cs mc_base2_init_force_write_cs; /* offset : 0x45e0 */
	union ddr_csr_mc_base2_cfg_ctrlr_init_disable mc_base2_cfg_ctrlr_init_disable;
	/* offset : 0x45e4 */
	union ddr_csr_mc_base2_ctrlr_ready mc_base2_ctrlr_ready; /* offset : 0x45e8 */
	uint32_t reserved_21[5];
	union ddr_csr_mc_base2_init_memory_reset_mask mc_base2_init_memory_reset_mask;
	/* offset : 0x4600 */
	uint32_t reserved_22[10];
	union ddr_csr_mc_base2_init_cal_l_r_ack mc_base2_init_cal_l_r_ack; /* offset : 0x462c */
	union ddr_csr_mc_base2_init_cal_l_read_complete mc_base2_init_cal_l_read_complete;
	/* offset : 0x4630 */
	uint32_t reserved_23[8];
	union ddr_csr_mc_base2_cfg_ctrlupd_trig mc_base2_cfg_ctrlupd_trig; /* offset : 0x4654 */
	union ddr_csr_mc_base2_cfg_ctrlupd_start_delay mc_base2_cfg_ctrlupd_start_delay;
	/* offset : 0x4658 */
	union ddr_csr_mc_base2_cfg_dfi_t_ctrlupd_max mc_base2_cfg_dfi_t_ctrlupd_max;
	/* offset : 0x465c */
	uint32_t reserved_24[6];
	union ddr_csr_mc_base2_cfg_phyupd_ack_delay mc_base2_cfg_phyupd_ack_delay; /* offset : 0x4678 */
	uint32_t reserved_25[7];
	union ddr_csr_mc_base2_cfg_dfi_t_ctrl_delay mc_base2_cfg_dfi_t_ctrl_delay; /* offset : 0x4698 */
	union ddr_csr_mc_base2_cfg_dfi_t_dram_clk_enable mc_base2_cfg_dfi_t_dram_clk_enable;
	/* offset : 0x469c */
	uint32_t reserved_26[3];
	union ddr_csr_mc_base2_cfg_bg_interleave mc_base2_cfg_bg_interleave; /* offset : 0x46ac */
	union ddr_csr_mc_base2_cfg_dbi_byte_disable_source mc_base2_cfg_dbi_byte_disable_source;
	/* offset : 0x46b0 */
	union ddr_csr_mc_base2_cfg_dbi_byte_disable mc_base2_cfg_dbi_byte_disable; /* offset : 0x46b4 */
	union ddr_csr_mc_base2_cfg_refresh_during_phy_training mc_base2_cfg_refresh_during_phy_training;
	/* offset : 0x46b8 */
	uint32_t reserved_27[93];
	union ddr_csr_mc_base3_cfg_12hi mc_base3_cfg_12hi; /* offset : 0x4830 */
	union ddr_csr_mc_base3_cfg_np2_rows mc_base3_cfg_np2_rows; /* offset : 0x4834 */
	uint32_t reserved_28[63];
	union ddr_csr_mc_base3_stat_interrupt_0 mc_base3_stat_interrupt_0; /* offset : 0x4934 */
	union ddr_csr_mc_base3_init_interrupt_mask_0 mc_base3_init_interrupt_mask_0;
	/* offset : 0x4938 */
	union ddr_csr_mc_base3_init_interrupt_gen_0 mc_base3_init_interrupt_gen_0; /* offset : 0x493c */
	uint32_t reserved_29[6];
	union ddr_csr_mc_base3_init_ccd_throttle_cnt mc_base3_init_ccd_throttle_cnt;
	/* offset : 0x4958 */
	uint32_t reserved_30;
	union ddr_csr_mc_base3_cfg_disable_dfi_ctrlupd_req_in_sr
		mc_base3_cfg_disable_dfi_ctrlupd_req_in_sr; /* offset : 0x4960 */
	uint32_t reserved_31[4];
	union ddr_csr_mc_base3_amt_simultaneous_ram_write mc_base3_amt_simultaneous_ram_write;
	/* offset : 0x4974 */
	uint32_t reserved_32[18];
	union ddr_csr_mc_base3_init_rfm_en mc_base3_init_rfm_en; /* offset : 0x49c0 */
	union ddr_csr_mc_base3_init_rfm_raarfm mc_base3_init_rfm_raarfm; /* offset : 0x49c4 */
	union ddr_csr_mc_base3_init_rfm_raammt mc_base3_init_rfm_raammt; /* offset : 0x49c8 */
	union ddr_csr_mc_base3_init_rfm_raaref mc_base3_init_rfm_raaref; /* offset : 0x49cc */
	union ddr_csr_mc_base3_cfg_rfm_raasrf mc_base3_cfg_rfm_raasrf; /* offset : 0x49d0 */
	union ddr_csr_mc_base3_cfg_axi_auto_pch mc_base3_cfg_axi_auto_pch; /* offset : 0x49d4 */
	union ddr_csr_mc_base3_cfg_axi_write_response_mport_order
		mc_base3_cfg_axi_write_response_mport_order; /* offset : 0x49d8 */
	union ddr_csr_mc_base3_init_axi_ready_disable mc_base3_init_axi_ready_disable;
	/* offset : 0x49dc */
	union ddr_csr_mc_base3_init_am_repeat_en mc_base3_init_am_repeat_en; /* offset : 0x49e0 */
	union ddr_csr_mc_base3_init_am_single_en mc_base3_init_am_single_en; /* offset : 0x49e4 */
	union ddr_csr_mc_base3_init_am_interval mc_base3_init_am_interval; /* offset : 0x49e8 */
	union ddr_csr_mc_base3_stat_am_complete mc_base3_stat_am_complete; /* offset : 0x49ec */
	union ddr_csr_mc_base3_cfg_arfu_value mc_base3_cfg_arfu_value; /* offset : 0x49f0 */
	uint32_t reserved_33[30];
	union ddr_csr_mc_base3_cfg_hbm_le_32b_write_en mc_base3_cfg_hbm_le_32b_write_en;
	/* offset : 0x4a6c */
	union ddr_csr_mc_base3_cfg_dfi_phyupd_idle_sel mc_base3_cfg_dfi_phyupd_idle_sel;
	/* offset : 0x4a70 */
	uint32_t reserved_34[16];
	union ddr_csr_mc_base3_cfg_aggressive_autopch mc_base3_cfg_aggressive_autopch;
	/* offset : 0x4ab4 */
	union ddr_csr_mc_base3_cfg_idle_delay mc_base3_cfg_idle_delay; /* offset : 0x4ab8 */
	union ddr_csr_mc_base3_cfg_force_bgpos0 mc_base3_cfg_force_bgpos0; /* offset : 0x4abc */
	uint32_t reserved_35[5];
	union ddr_csr_mc_base3_init_hold_sr_during_reset mc_base3_init_hold_sr_during_reset;
	/* offset : 0x4ad4 */
	uint32_t reserved_36[4];
	union ddr_csr_mc_base3_init_rfm_level_chg mc_base3_init_rfm_level_chg; /* offset : 0x4ae8 */
	union ddr_csr_mc_base3_init_rfm_raaimt mc_base3_init_rfm_raaimt; /* offset : 0x4aec */
	union ddr_csr_mc_base3_cfg_min_partial_issued_lifetime mc_base3_cfg_min_partial_issued_lifetime;
	/* offset : 0x4af0 */
	uint32_t reserved_37[22];
	union ddr_csr_mc_base3_cfg_arfm_level mc_base3_cfg_arfm_level; /* offset : 0x4b4c */
	uint32_t reserved_38;
	union ddr_csr_mc_base3_stat_poison_read_addr mc_base3_stat_poison_read_addr;
	/* offset : 0x4b54 */
	union ddr_csr_mc_base3_stat_poison_read_rmw mc_base3_stat_poison_read_rmw; /* offset : 0x4b58 */
	uint32_t reserved_39[9];
	union ddr_csr_mc_base3_cfg_2bit_bg_interleave mc_base3_cfg_2bit_bg_interleave;
	/* offset : 0x4b80 */
	uint32_t reserved_40[31];
	union ddr_csr_mc_base4_init_ack mc_base4_init_ack; /* offset : 0x4c00 */
	union ddr_csr_mc_base4_init_refresh mc_base4_init_refresh; /* offset : 0x4c04 */
	union ddr_csr_mc_base4_init_refresh_count mc_base4_init_refresh_count; /* offset : 0x4c08 */
	union ddr_csr_mc_base4_init_force_write mc_base4_init_force_write; /* offset : 0x4c0c */
	union ddr_csr_mc_base4_init_force_write_data_0 mc_base4_init_force_write_data_0;
	/* offset : 0x4c10 */
	union ddr_csr_mc_base4_stat_mem_array_severity_code mc_base4_stat_mem_array_severity_code;
	/* offset : 0x4c14 */
	union ddr_csr_mc_base4_stat_mem_array_mbit_corr_err mc_base4_stat_mem_array_mbit_corr_err;
	/* offset : 0x4c18 */
	union ddr_csr_mc_base4_stat_ack_mr mc_base4_stat_ack_mr; /* offset : 0x4c1c */
	union ddr_csr_mc_base4_stat_ack_refresh mc_base4_stat_ack_refresh; /* offset : 0x4c20 */
	union ddr_csr_mc_base4_stat_ack_precharge_all mc_base4_stat_ack_precharge_all;
	/* offset : 0x4c24 */
	union ddr_csr_mc_base4_stat_ack_nop mc_base4_stat_ack_nop; /* offset : 0x4c28 */
	uint32_t reserved_41;
	union ddr_csr_mc_base4_stat_idle mc_base4_stat_idle; /* offset : 0x4c30 */
	uint32_t reserved_42;
	union ddr_csr_mc_base4_stat_ack_rfm_level_chg mc_base4_stat_ack_rfm_level_chg;
	/* offset : 0x4c38 */
	uint32_t reserved_43[241];
	union ddr_csr_dfi_cfg_dfi_t_rddata_en dfi_cfg_dfi_t_rddata_en; /* offset : 0x5000 */
	uint32_t reserved_44;
	union ddr_csr_dfi_cfg_dfi_t_phy_wrlat dfi_cfg_dfi_t_phy_wrlat; /* offset : 0x5008 */
	union ddr_csr_dfi_init_dfi_phyupd_en dfi_init_dfi_phyupd_en; /* offset : 0x500c */
	union ddr_csr_dfi_init_dfi_lp_data_req dfi_init_dfi_lp_data_req; /* offset : 0x5010 */
	union ddr_csr_dfi_init_dfi_lp_ctrl_req dfi_init_dfi_lp_ctrl_req; /* offset : 0x5014 */
	uint32_t reserved_45[2];
	union ddr_csr_dfi_init_dfi_dram_clk_disable dfi_init_dfi_dram_clk_disable; /* offset : 0x5020 */
	union ddr_csr_dfi_stat_dfi_training_error dfi_stat_dfi_training_error; /* offset : 0x5024 */
	union ddr_csr_dfi_stat_dfi_error dfi_stat_dfi_error; /* offset : 0x5028 */
	union ddr_csr_dfi_stat_dfi_error_info dfi_stat_dfi_error_info; /* offset : 0x502c */
	union ddr_csr_dfi_cfg_dfi_data_byte_disable dfi_cfg_dfi_data_byte_disable; /* offset : 0x5030 */
	union ddr_csr_dfi_stat_dfi_init_complete dfi_stat_dfi_init_complete; /* offset : 0x5034 */
	union ddr_csr_dfi_stat_dfi_training_complete dfi_stat_dfi_training_complete;
	/* offset : 0x5038 */
	union ddr_csr_dfi_cfg_dfi_lvl_sel dfi_cfg_dfi_lvl_sel; /* offset : 0x503c */
	union ddr_csr_dfi_cfg_dfi_lvl_periodic dfi_cfg_dfi_lvl_periodic; /* offset : 0x5040 */
	union ddr_csr_dfi_cfg_dfi_lvl_pattern dfi_cfg_dfi_lvl_pattern; /* offset : 0x5044 */
	union ddr_csr_dfi_stat_dfi_tcr_temp dfi_stat_dfi_tcr_temp; /* offset : 0x5048 */
	union ddr_csr_dfi_stat_dfi_cattrip dfi_stat_dfi_cattrip; /* offset : 0x504c */
	union ddr_csr_dfi_phy_dfi_init_start dfi_phy_dfi_init_start; /* offset : 0x5050 */
	uint32_t reserved_46;
	union ddr_csr_dfi_init_dfi_training_complete dfi_init_dfi_training_complete;
	/* offset : 0x5058 */
	union ddr_csr_dfi_cfg_lp_mode_for_pd dfi_cfg_lp_mode_for_pd; /* offset : 0x505c */
	union ddr_csr_dfi_stat_dfi_lp_ctrl_ack dfi_stat_dfi_lp_ctrl_ack; /* offset : 0x5060 */
	union ddr_csr_dfi_init_dfi_lp_ctrl_wakeup dfi_init_dfi_lp_ctrl_wakeup; /* offset : 0x5064 */
	union ddr_csr_dfi_stat_dfi_lp_data_ack dfi_stat_dfi_lp_data_ack; /* offset : 0x5068 */
	union ddr_csr_dfi_init_dfi_lp_data_wakeup dfi_init_dfi_lp_data_wakeup; /* offset : 0x506c */
	uint32_t reserved_47[2];
	union ddr_csr_dfi_cfg_lp_data_wakeup_1 dfi_cfg_lp_data_wakeup_1; /* offset : 0x5078 */
	union ddr_csr_dfi_cfg_lp_data_wakeup_2 dfi_cfg_lp_data_wakeup_2; /* offset : 0x507c */
	union ddr_csr_dfi_stat_lp_dfi_state dfi_stat_lp_dfi_state; /* offset : 0x5080 */
	union ddr_csr_dfi_init_dfi_phymstr_en dfi_init_dfi_phymstr_en; /* offset : 0x5084 */
	union ddr_csr_dfi_stat_dfi_phymstr_ack dfi_stat_dfi_phymstr_ack; /* offset : 0x5088 */
	union ddr_csr_dfi_phy_ca_training_start dfi_phy_ca_training_start; /* offset : 0x508c */
	union ddr_csr_dfi_phy_ca_training_en dfi_phy_ca_training_en; /* offset : 0x5090 */
	union ddr_csr_dfi_phy_ca_training_complete dfi_phy_ca_training_complete; /* offset : 0x5094 */
	uint32_t reserved_48[8];
	union ddr_csr_dfi_cfg_dfi_t_phy_wrdata dfi_cfg_dfi_t_phy_wrdata; /* offset : 0x50b8 */
	union ddr_csr_dfi_cfg_lp_data_wakeup_3 dfi_cfg_lp_data_wakeup_3; /* offset : 0x50bc */
	uint32_t reserved_49[464];
	union ddr_csr_mpfe_cfg_starve_timeout_p0 mpfe_cfg_starve_timeout_p0; /* offset : 0x5800 */
	union ddr_csr_mpfe_cfg_starve_timeout_p1 mpfe_cfg_starve_timeout_p1; /* offset : 0x5804 */
	uint32_t reserved_50[2];
	union ddr_csr_mpfe_cfg_starve_timeout_p4 mpfe_cfg_starve_timeout_p4; /* offset : 0x5810 */
	uint32_t reserved_51[6];
	union ddr_csr_mpfe_cfg_roundrobin_weight_p0 mpfe_cfg_roundrobin_weight_p0; /* offset : 0x582c */
	union ddr_csr_mpfe_cfg_roundrobin_weight_p1 mpfe_cfg_roundrobin_weight_p1; /* offset : 0x5830 */
	uint32_t reserved_52[243];
	union ddr_csr_reorder_cfg_reorder_en reorder_cfg_reorder_en; /* offset : 0x5c00 */
	uint32_t reserved_53[8];
	union ddr_csr_reorder_cfg_q_read_age_limit reorder_cfg_q_read_age_limit; /* offset : 0x5c24 */
	union ddr_csr_reorder_cfg_q_write_age_limit reorder_cfg_q_write_age_limit; /* offset : 0x5c28 */
	union ddr_csr_reorder_cfg_ro_write_limit reorder_cfg_ro_write_limit; /* offset : 0x5c2c */
	uint32_t reserved_54;
	union ddr_csr_reorder_cfg_allow_write_act_thresh reorder_cfg_allow_write_act_thresh;
	/* offset : 0x5c34 */
	union ddr_csr_reorder_cfg_max_casreq reorder_cfg_max_casreq; /* offset : 0x5c38 */
	uint32_t reserved_55[241];
	union ddr_csr_rmw_cfg_dm_en rmw_cfg_dm_en; /* offset : 0x6000 */
	union ddr_csr_rmw_cfg_rmw_en rmw_cfg_rmw_en; /* offset : 0x6004 */
	uint32_t reserved_56[254];
	union ddr_csr_ecc_config_cfg_ecc_correction_en ecc_config_cfg_ecc_correction_en;
	/* offset : 0x6400 */
	union ddr_csr_ecc_config_init_ecc_scrub_en ecc_config_init_ecc_scrub_en; /* offset : 0x6404 */
	union ddr_csr_ecc_config_init_ecc_scrub_init_en ecc_config_init_ecc_scrub_init_en;
	/* offset : 0x6408 */
	union ddr_csr_ecc_config_cfg_ecc_scrub_init_rmw ecc_config_cfg_ecc_scrub_init_rmw;
	/* offset : 0x640c */
	uint32_t reserved_57;
	union ddr_csr_ecc_config_cfg_ecc_scrub_min_addr_0 ecc_config_cfg_ecc_scrub_min_addr_0;
	/* offset : 0x6414 */
	union ddr_csr_ecc_config_cfg_ecc_scrub_max_addr_0 ecc_config_cfg_ecc_scrub_max_addr_0;
	/* offset : 0x6418 */
	union ddr_csr_ecc_config_init_ecc_scrub_error_clr ecc_config_init_ecc_scrub_error_clr;
	/* offset : 0x641c */
	union ddr_csr_ecc_config_cfg_ecc_bypass ecc_config_cfg_ecc_bypass; /* offset : 0x6420 */
	union ddr_csr_ecc_config_cfg_ecc_1bit_int_thresh ecc_config_cfg_ecc_1bit_int_thresh;
	/* offset : 0x6424 */
	uint32_t reserved_58[246];
	union ddr_csr_ecc_stat_err_stat_ecc_scrub_error_1bit_cnt
		ecc_stat_err_stat_ecc_scrub_error_1bit_cnt; /* offset : 0x6800 */
	union ddr_csr_ecc_stat_err_stat_ecc_scrub_error_2bit_cnt
		ecc_stat_err_stat_ecc_scrub_error_2bit_cnt; /* offset : 0x6804 */
	union ddr_csr_ecc_stat_err_stat_ecc_scrub_init_done ecc_stat_err_stat_ecc_scrub_init_done;
	/* offset : 0x6808 */
	union ddr_csr_ecc_stat_err_init_write_data_1b_ecc_error_gen
		ecc_stat_err_init_write_data_1b_ecc_error_gen; /* offset : 0x680c */
	union ddr_csr_ecc_stat_err_init_write_data_2b_ecc_error_gen
		ecc_stat_err_init_write_data_2b_ecc_error_gen; /* offset : 0x6810 */
	union ddr_csr_ecc_stat_err_stat_int_ecc_1bit_thresh ecc_stat_err_stat_int_ecc_1bit_thresh;
	/* offset : 0x6814 */
	union ddr_csr_ecc_stat_err_stat_ecc_1bit_error_addr ecc_stat_err_stat_ecc_1bit_error_addr;
	/* offset : 0x6818 */
	union ddr_csr_ecc_stat_err_stat_ecc_1bit_pos ecc_stat_err_stat_ecc_1bit_pos;
	/* offset : 0x681c */
	union ddr_csr_ecc_stat_err_stat_ecc_1bit_rmw ecc_stat_err_stat_ecc_1bit_rmw;
	/* offset : 0x6820 */
	union ddr_csr_ecc_stat_err_stat_ecc_2bit_error_addr ecc_stat_err_stat_ecc_2bit_error_addr;
	/* offset : 0x6824 */
	union ddr_csr_ecc_stat_err_stat_ecc_2bit_rmw ecc_stat_err_stat_ecc_2bit_rmw;
	/* offset : 0x6828 */
	uint32_t reserved_59[245];
	union ddr_csr_parity_error_stat_di_write_data_parity_error
		parity_error_stat_di_write_data_parity_error; /* offset : 0x6c00 */
	union ddr_csr_parity_error_stat_write_data_parity_error
		parity_error_stat_write_data_parity_error; /* offset : 0x6c04 */
	union ddr_csr_parity_error_stat_read_data_parity_error
		parity_error_stat_read_data_parity_error; /* offset : 0x6c08 */
	union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_req
		parity_error_init_hbm_row_col_parity_error_gen_req; /* offset : 0x6c0c */
	union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_cmd
		parity_error_init_hbm_row_col_parity_error_gen_cmd; /* offset : 0x6c10 */
	union ddr_csr_parity_error_init_hbm_row_col_parity_error_gen_ack
		parity_error_init_hbm_row_col_parity_error_gen_ack; /* offset : 0x6c14 */
	union ddr_csr_parity_error_init_hbm_data_parity_error_gen_req
		parity_error_init_hbm_data_parity_error_gen_req; /* offset : 0x6c18 */
	union ddr_csr_parity_error_init_hbm_data_parity_error_gen_sel
		parity_error_init_hbm_data_parity_error_gen_sel; /* offset : 0x6c1c */
	union ddr_csr_parity_error_init_hbm_data_parity_error_gen_ack
		parity_error_init_hbm_data_parity_error_gen_ack; /* offset : 0x6c20 */
	union ddr_csr_parity_error_init_hbm_write_data_perr_gen_pattern
		parity_error_init_hbm_write_data_perr_gen_pattern; /* offset : 0x6c24 */
	union ddr_csr_parity_error_init_hbm_read_data_perr_gen_pattern
		parity_error_init_hbm_read_data_perr_gen_pattern; /* offset : 0x6c28 */
	union ddr_csr_parity_error_stat_ca_parity_error parity_error_stat_ca_parity_error;
	/* offset : 0x6c2c */
	uint32_t reserved_60[500];
	union ddr_csr_data_int_cfg_di_read_data_parity_odd_even_n
		data_int_cfg_di_read_data_parity_odd_even_n; /* offset : 0x7400 */
	union ddr_csr_data_int_cfg_di_write_data_parity_odd_even_n
		data_int_cfg_di_write_data_parity_odd_even_n; /* offset : 0x7404 */
	union ddr_csr_data_int_cfg_di_write_data_parity_enable
		data_int_cfg_di_write_data_parity_enable; /* offset : 0x7408 */
	union ddr_csr_data_int_cfg_di_read_force_parity_on_2b_ecc
		data_int_cfg_di_read_force_parity_on_2b_ecc; /* offset : 0x740c */
	union ddr_csr_data_int_init_di_read_data_parity_error_gen_0
		data_int_init_di_read_data_parity_error_gen_0; /* offset : 0x7410 */
	union ddr_csr_data_int_init_di_read_data_parity_error_gen_1
		data_int_init_di_read_data_parity_error_gen_1; /* offset : 0x7414 */
	union ddr_csr_data_int_cfg_axi_write_data_parity_enable
		data_int_cfg_axi_write_data_parity_enable; /* offset : 0x7418 */
	union ddr_csr_data_int_cfg_csr_parity_error_mask data_int_cfg_csr_parity_error_mask;
	/* offset : 0x741c */
	union ddr_csr_data_int_stat_csr_parity_error data_int_stat_csr_parity_error;
	/* offset : 0x7420 */
	union ddr_csr_data_int_init_csr_parity_error_gen data_int_init_csr_parity_error_gen;
	/* offset : 0x7424 */
	uint32_t reserved_61[246];
	union ddr_csr_axi_if_stat_axi_write_data_parity_error axi_if_stat_axi_write_data_parity_error;
	/* offset : 0x7800 */
	uint32_t reserved_62;
	union ddr_csr_axi_if_cfg_axi_start_address_axi1_0 axi_if_cfg_axi_start_address_axi1_0;
	/* offset : 0x7808 */
	uint32_t reserved_63[4];
	union ddr_csr_axi_if_cfg_axi_end_address_axi1_0 axi_if_cfg_axi_end_address_axi1_0;
	/* offset : 0x781c */
	uint32_t reserved_64[4];
	union ddr_csr_axi_if_cfg_mem_start_address_axi1_0 axi_if_cfg_mem_start_address_axi1_0;
	/* offset : 0x7830 */
	uint32_t reserved_65[8];
	union ddr_csr_axi_if_cfg_axird_id_reorder_en axi_if_cfg_axird_id_reorder_en;
	/* offset : 0x7854 */
	union ddr_csr_axi_if_cfg_axird_interleave_sel axi_if_cfg_axird_interleave_sel;
	/* offset : 0x7858 */
	union ddr_csr_axi_if_stat_axi_decerr axi_if_stat_axi_decerr; /* offset : 0x785c */
	uint32_t reserved_66[488];
	union ddr_csr_mem_test_mt_en mem_test_mt_en; /* offset : 0x8000 */
	union ddr_csr_mem_test_mt_en_single mem_test_mt_en_single; /* offset : 0x8004 */
	union ddr_csr_mem_test_mt_stop_on_error mem_test_mt_stop_on_error; /* offset : 0x8008 */
	union ddr_csr_mem_test_mt_rd_only mem_test_mt_rd_only; /* offset : 0x800c */
	union ddr_csr_mem_test_mt_wr_only mem_test_mt_wr_only; /* offset : 0x8010 */
	union ddr_csr_mem_test_mt_data_pattern mem_test_mt_data_pattern; /* offset : 0x8014 */
	union ddr_csr_mem_test_mt_addr_pattern mem_test_mt_addr_pattern; /* offset : 0x8018 */
	union ddr_csr_mem_test_mt_data_invert mem_test_mt_data_invert; /* offset : 0x801c */
	union ddr_csr_mem_test_mt_addr_bits mem_test_mt_addr_bits; /* offset : 0x8020 */
	union ddr_csr_mem_test_mt_error_sts mem_test_mt_error_sts; /* offset : 0x8024 */
	union ddr_csr_mem_test_mt_done_ack mem_test_mt_done_ack; /* offset : 0x8028 */
	union ddr_csr_mem_test_mt_max_wd mem_test_mt_max_wd; /* offset : 0x802c */
	union ddr_csr_mem_test_mt_max_ex mem_test_mt_max_ex; /* offset : 0x8030 */
	union ddr_csr_mem_test_mt_max_ac mem_test_mt_max_ac; /* offset : 0x8034 */
	union ddr_csr_mem_test_mt_cycles mem_test_mt_cycles; /* offset : 0x8038 */
	union ddr_csr_mem_test_mt_arb_mem_addr mem_test_mt_arb_mem_addr; /* offset : 0x803c */
	union ddr_csr_mem_test_mt_arb_ack mem_test_mt_arb_ack; /* offset : 0x8040 */
	union ddr_csr_mem_test_mt_wd_wdata_0 mem_test_mt_wd_wdata_0; /* offset : 0x8044 */
	union ddr_csr_mem_test_mt_wd_wdata_1 mem_test_mt_wd_wdata_1; /* offset : 0x8048 */
	union ddr_csr_mem_test_mt_wd_wdata_2 mem_test_mt_wd_wdata_2; /* offset : 0x804c */
	union ddr_csr_mem_test_mt_wd_wdata_3 mem_test_mt_wd_wdata_3; /* offset : 0x8050 */
	union ddr_csr_mem_test_mt_wd_wdata_4 mem_test_mt_wd_wdata_4; /* offset : 0x8054 */
	union ddr_csr_mem_test_mt_wd_wdata_5 mem_test_mt_wd_wdata_5; /* offset : 0x8058 */
	union ddr_csr_mem_test_mt_wd_wdata_6 mem_test_mt_wd_wdata_6; /* offset : 0x805c */
	union ddr_csr_mem_test_mt_wd_wdata_7 mem_test_mt_wd_wdata_7; /* offset : 0x8060 */
	union ddr_csr_mem_test_mt_wd_wdata_8 mem_test_mt_wd_wdata_8; /* offset : 0x8064 */
	union ddr_csr_mem_test_mt_wd_wdata_9 mem_test_mt_wd_wdata_9; /* offset : 0x8068 */
	union ddr_csr_mem_test_mt_wd_wdata_10 mem_test_mt_wd_wdata_10; /* offset : 0x806c */
	union ddr_csr_mem_test_mt_wd_wdata_11 mem_test_mt_wd_wdata_11; /* offset : 0x8070 */
	union ddr_csr_mem_test_mt_wd_wdata_12 mem_test_mt_wd_wdata_12; /* offset : 0x8074 */
	union ddr_csr_mem_test_mt_wd_wdata_13 mem_test_mt_wd_wdata_13; /* offset : 0x8078 */
	union ddr_csr_mem_test_mt_wd_wdata_14 mem_test_mt_wd_wdata_14; /* offset : 0x807c */
	union ddr_csr_mem_test_mt_wd_wdata_15 mem_test_mt_wd_wdata_15; /* offset : 0x8080 */
	union ddr_csr_mem_test_mt_wd_wdata_16 mem_test_mt_wd_wdata_16; /* offset : 0x8084 */
	union ddr_csr_mem_test_mt_ex_wdata_0 mem_test_mt_ex_wdata_0; /* offset : 0x8088 */
	union ddr_csr_mem_test_mt_ex_wdata_1 mem_test_mt_ex_wdata_1; /* offset : 0x808c */
	union ddr_csr_mem_test_mt_ex_wdata_2 mem_test_mt_ex_wdata_2; /* offset : 0x8090 */
	union ddr_csr_mem_test_mt_ex_wdata_3 mem_test_mt_ex_wdata_3; /* offset : 0x8094 */
	union ddr_csr_mem_test_mt_ex_wdata_4 mem_test_mt_ex_wdata_4; /* offset : 0x8098 */
	union ddr_csr_mem_test_mt_ex_wdata_5 mem_test_mt_ex_wdata_5; /* offset : 0x809c */
	union ddr_csr_mem_test_mt_ex_wdata_6 mem_test_mt_ex_wdata_6; /* offset : 0x80a0 */
	union ddr_csr_mem_test_mt_ex_wdata_7 mem_test_mt_ex_wdata_7; /* offset : 0x80a4 */
	union ddr_csr_mem_test_mt_ex_wdata_8 mem_test_mt_ex_wdata_8; /* offset : 0x80a8 */
	union ddr_csr_mem_test_mt_ex_wdata_9 mem_test_mt_ex_wdata_9; /* offset : 0x80ac */
	union ddr_csr_mem_test_mt_ex_wdata_10 mem_test_mt_ex_wdata_10; /* offset : 0x80b0 */
	union ddr_csr_mem_test_mt_ex_wdata_11 mem_test_mt_ex_wdata_11; /* offset : 0x80b4 */
	union ddr_csr_mem_test_mt_ex_wdata_12 mem_test_mt_ex_wdata_12; /* offset : 0x80b8 */
	union ddr_csr_mem_test_mt_ex_wdata_13 mem_test_mt_ex_wdata_13; /* offset : 0x80bc */
	union ddr_csr_mem_test_mt_ex_wdata_14 mem_test_mt_ex_wdata_14; /* offset : 0x80c0 */
	union ddr_csr_mem_test_mt_ex_wdata_15 mem_test_mt_ex_wdata_15; /* offset : 0x80c4 */
	union ddr_csr_mem_test_mt_ex_wdata_16 mem_test_mt_ex_wdata_16; /* offset : 0x80c8 */
	union ddr_csr_mem_test_mt_ac_wdata_0 mem_test_mt_ac_wdata_0; /* offset : 0x80cc */
	union ddr_csr_mem_test_mt_ac_wdata_1 mem_test_mt_ac_wdata_1; /* offset : 0x80d0 */
	union ddr_csr_mem_test_mt_wd_rdata_0 mem_test_mt_wd_rdata_0; /* offset : 0x80d4 */
	union ddr_csr_mem_test_mt_wd_rdata_1 mem_test_mt_wd_rdata_1; /* offset : 0x80d8 */
	union ddr_csr_mem_test_mt_wd_rdata_2 mem_test_mt_wd_rdata_2; /* offset : 0x80dc */
	union ddr_csr_mem_test_mt_wd_rdata_3 mem_test_mt_wd_rdata_3; /* offset : 0x80e0 */
	union ddr_csr_mem_test_mt_wd_rdata_4 mem_test_mt_wd_rdata_4; /* offset : 0x80e4 */
	union ddr_csr_mem_test_mt_wd_rdata_5 mem_test_mt_wd_rdata_5; /* offset : 0x80e8 */
	union ddr_csr_mem_test_mt_wd_rdata_6 mem_test_mt_wd_rdata_6; /* offset : 0x80ec */
	union ddr_csr_mem_test_mt_wd_rdata_7 mem_test_mt_wd_rdata_7; /* offset : 0x80f0 */
	union ddr_csr_mem_test_mt_wd_rdata_8 mem_test_mt_wd_rdata_8; /* offset : 0x80f4 */
	union ddr_csr_mem_test_mt_wd_rdata_9 mem_test_mt_wd_rdata_9; /* offset : 0x80f8 */
	union ddr_csr_mem_test_mt_wd_rdata_10 mem_test_mt_wd_rdata_10; /* offset : 0x80fc */
	union ddr_csr_mem_test_mt_wd_rdata_11 mem_test_mt_wd_rdata_11; /* offset : 0x8100 */
	union ddr_csr_mem_test_mt_wd_rdata_12 mem_test_mt_wd_rdata_12; /* offset : 0x8104 */
	union ddr_csr_mem_test_mt_wd_rdata_13 mem_test_mt_wd_rdata_13; /* offset : 0x8108 */
	union ddr_csr_mem_test_mt_wd_rdata_14 mem_test_mt_wd_rdata_14; /* offset : 0x810c */
	union ddr_csr_mem_test_mt_wd_rdata_15 mem_test_mt_wd_rdata_15; /* offset : 0x8110 */
	union ddr_csr_mem_test_mt_wd_rdata_16 mem_test_mt_wd_rdata_16; /* offset : 0x8114 */
	union ddr_csr_mem_test_mt_ex_rdata_0 mem_test_mt_ex_rdata_0; /* offset : 0x8118 */
	union ddr_csr_mem_test_mt_ex_rdata_1 mem_test_mt_ex_rdata_1; /* offset : 0x811c */
	union ddr_csr_mem_test_mt_ex_rdata_2 mem_test_mt_ex_rdata_2; /* offset : 0x8120 */
	union ddr_csr_mem_test_mt_ex_rdata_3 mem_test_mt_ex_rdata_3; /* offset : 0x8124 */
	union ddr_csr_mem_test_mt_ex_rdata_4 mem_test_mt_ex_rdata_4; /* offset : 0x8128 */
	union ddr_csr_mem_test_mt_ex_rdata_5 mem_test_mt_ex_rdata_5; /* offset : 0x812c */
	union ddr_csr_mem_test_mt_ex_rdata_6 mem_test_mt_ex_rdata_6; /* offset : 0x8130 */
	union ddr_csr_mem_test_mt_ex_rdata_7 mem_test_mt_ex_rdata_7; /* offset : 0x8134 */
	union ddr_csr_mem_test_mt_ex_rdata_8 mem_test_mt_ex_rdata_8; /* offset : 0x8138 */
	union ddr_csr_mem_test_mt_ex_rdata_9 mem_test_mt_ex_rdata_9; /* offset : 0x813c */
	union ddr_csr_mem_test_mt_ex_rdata_10 mem_test_mt_ex_rdata_10; /* offset : 0x8140 */
	union ddr_csr_mem_test_mt_ex_rdata_11 mem_test_mt_ex_rdata_11; /* offset : 0x8144 */
	union ddr_csr_mem_test_mt_ex_rdata_12 mem_test_mt_ex_rdata_12; /* offset : 0x8148 */
	union ddr_csr_mem_test_mt_ex_rdata_13 mem_test_mt_ex_rdata_13; /* offset : 0x814c */
	union ddr_csr_mem_test_mt_ex_rdata_14 mem_test_mt_ex_rdata_14; /* offset : 0x8150 */
	union ddr_csr_mem_test_mt_ex_rdata_15 mem_test_mt_ex_rdata_15; /* offset : 0x8154 */
	union ddr_csr_mem_test_mt_ex_rdata_16 mem_test_mt_ex_rdata_16; /* offset : 0x8158 */
	union ddr_csr_mem_test_mt_ac_rdata_0 mem_test_mt_ac_rdata_0; /* offset : 0x815c */
	union ddr_csr_mem_test_mt_ac_rdata_1 mem_test_mt_ac_rdata_1; /* offset : 0x8160 */
	union ddr_csr_mem_test_mt_start_addr_0 mem_test_mt_start_addr_0; /* offset : 0x8164 */
	union ddr_csr_mem_test_mt_error_mask_0 mem_test_mt_error_mask_0; /* offset : 0x8168 */
	union ddr_csr_mem_test_mt_error_mask_1 mem_test_mt_error_mask_1; /* offset : 0x816c */
	union ddr_csr_mem_test_mt_error_mask_2 mem_test_mt_error_mask_2; /* offset : 0x8170 */
	union ddr_csr_mem_test_mt_error_mask_3 mem_test_mt_error_mask_3; /* offset : 0x8174 */
	union ddr_csr_mem_test_mt_error_mask_4 mem_test_mt_error_mask_4; /* offset : 0x8178 */
	union ddr_csr_mem_test_mt_error_mask_5 mem_test_mt_error_mask_5; /* offset : 0x817c */
	union ddr_csr_mem_test_mt_error_mask_6 mem_test_mt_error_mask_6; /* offset : 0x8180 */
	union ddr_csr_mem_test_mt_error_mask_7 mem_test_mt_error_mask_7; /* offset : 0x8184 */
	union ddr_csr_mem_test_mt_error_mask_8 mem_test_mt_error_mask_8; /* offset : 0x8188 */
	union ddr_csr_mem_test_mt_error_mask_9 mem_test_mt_error_mask_9; /* offset : 0x818c */
	union ddr_csr_mem_test_mt_error_mask_10 mem_test_mt_error_mask_10; /* offset : 0x8190 */
	union ddr_csr_mem_test_mt_error_mask_11 mem_test_mt_error_mask_11; /* offset : 0x8194 */
	union ddr_csr_mem_test_mt_error_mask_12 mem_test_mt_error_mask_12; /* offset : 0x8198 */
	union ddr_csr_mem_test_mt_error_mask_13 mem_test_mt_error_mask_13; /* offset : 0x819c */
	union ddr_csr_mem_test_mt_error_mask_14 mem_test_mt_error_mask_14; /* offset : 0x81a0 */
	union ddr_csr_mem_test_mt_error_mask_15 mem_test_mt_error_mask_15; /* offset : 0x81a4 */
	union ddr_csr_mem_test_mt_error_mask_16 mem_test_mt_error_mask_16; /* offset : 0x81a8 */
	union ddr_csr_mem_test_mt_user_data_pattern mem_test_mt_user_data_pattern; /* offset : 0x81ac */
	union ddr_csr_mem_test_mt_alg_auto_pch mem_test_mt_alg_auto_pch; /* offset : 0x81b0 */
	uint32_t reserved_67[11];
	union ddr_csr_mem_test_mt_output_mask_0 mem_test_mt_output_mask_0; /* offset : 0x81e0 */
	union ddr_csr_mem_test_mt_output_mask_1 mem_test_mt_output_mask_1; /* offset : 0x81e4 */
	union ddr_csr_mem_test_mt_output_mask_2 mem_test_mt_output_mask_2; /* offset : 0x81e8 */
	union ddr_csr_mem_test_mt_output_mask_3 mem_test_mt_output_mask_3; /* offset : 0x81ec */
	union ddr_csr_mem_test_mt_output_mask_4 mem_test_mt_output_mask_4; /* offset : 0x81f0 */
	union ddr_csr_mem_test_mt_output_mask_5 mem_test_mt_output_mask_5; /* offset : 0x81f4 */
	union ddr_csr_mem_test_mt_output_mask_6 mem_test_mt_output_mask_6; /* offset : 0x81f8 */
	union ddr_csr_mem_test_mt_output_mask_7 mem_test_mt_output_mask_7; /* offset : 0x81fc */
	union ddr_csr_mem_test_mt_output_mask_8 mem_test_mt_output_mask_8; /* offset : 0x8200 */
	union ddr_csr_mem_test_mt_output_mask_9 mem_test_mt_output_mask_9; /* offset : 0x8204 */
	union ddr_csr_mem_test_mt_output_mask_10 mem_test_mt_output_mask_10; /* offset : 0x8208 */
	union ddr_csr_mem_test_mt_output_mask_11 mem_test_mt_output_mask_11; /* offset : 0x820c */
	union ddr_csr_mem_test_mt_output_mask_12 mem_test_mt_output_mask_12; /* offset : 0x8210 */
	union ddr_csr_mem_test_mt_output_mask_13 mem_test_mt_output_mask_13; /* offset : 0x8214 */
	union ddr_csr_mem_test_mt_output_mask_14 mem_test_mt_output_mask_14; /* offset : 0x8218 */
	union ddr_csr_mem_test_mt_output_mask_15 mem_test_mt_output_mask_15; /* offset : 0x821c */
	union ddr_csr_mem_test_mt_output_mask_16 mem_test_mt_output_mask_16; /* offset : 0x8220 */
	union ddr_csr_mem_test_mt_output_masked_value mem_test_mt_output_masked_value;
	/* offset : 0x8224 */
	uint32_t reserved_68[374];
	union ddr_csr_adv_mem_test_amt_useq_iram_waddr adv_mem_test_amt_useq_iram_waddr;
	/* offset : 0x8800 */
	union ddr_csr_adv_mem_test_amt_useq_iram_wdata_0 adv_mem_test_amt_useq_iram_wdata_0;
	/* offset : 0x8804 */
	union ddr_csr_adv_mem_test_amt_useq_iram_wdata_1 adv_mem_test_amt_useq_iram_wdata_1;
	/* offset : 0x8808 */
	union ddr_csr_adv_mem_test_amt_useq_iram_rdata_0 adv_mem_test_amt_useq_iram_rdata_0;
	/* offset : 0x880c */
	union ddr_csr_adv_mem_test_amt_useq_iram_rdata_1 adv_mem_test_amt_useq_iram_rdata_1;
	/* offset : 0x8810 */
	union ddr_csr_adv_mem_test_amt_useq_iram_ack adv_mem_test_amt_useq_iram_ack;
	/* offset : 0x8814 */
	union ddr_csr_adv_mem_test_amt_useq_rf_waddr adv_mem_test_amt_useq_rf_waddr;
	/* offset : 0x8818 */
	union ddr_csr_adv_mem_test_amt_useq_rf_wdata_0 adv_mem_test_amt_useq_rf_wdata_0;
	/* offset : 0x881c */
	union ddr_csr_adv_mem_test_amt_useq_rf_rdata_0 adv_mem_test_amt_useq_rf_rdata_0;
	/* offset : 0x8820 */
	union ddr_csr_adv_mem_test_amt_useq_rf_ack adv_mem_test_amt_useq_rf_ack;
	/* offset : 0x8824 */
	union ddr_csr_adv_mem_test_amt_useq_exceptions adv_mem_test_amt_useq_exceptions;
	/* offset : 0x8828 */
	union ddr_csr_adv_mem_test_amt_useq_pc adv_mem_test_amt_useq_pc; /* offset : 0x882c */
	union ddr_csr_adv_mem_test_amt_useq_inst_counter_0 adv_mem_test_amt_useq_inst_counter_0;
	/* offset : 0x8830 */
	union ddr_csr_adv_mem_test_amt_useq_inst_counter_1 adv_mem_test_amt_useq_inst_counter_1;
	/* offset : 0x8834 */
	union ddr_csr_adv_mem_test_amt_useq_mta_storage_sel adv_mem_test_amt_useq_mta_storage_sel;
	/* offset : 0x8838 */
	uint32_t reserved_69;
	union ddr_csr_adv_mem_test_amt_sequencer_enable adv_mem_test_amt_sequencer_enable;
	/* offset : 0x8840 */
	uint32_t reserved_70[239];
	union ddr_csr_mta_cfg_error_group_sel mta_cfg_error_group_sel; /* offset : 0x8c00 */
	union ddr_csr_mta_cfg_data_sel mta_cfg_data_sel; /* offset : 0x8c04 */
	union ddr_csr_mta_cfg_trig_mode mta_cfg_trig_mode; /* offset : 0x8c08 */
	union ddr_csr_mta_cfg_post_trig_cycs mta_cfg_post_trig_cycs; /* offset : 0x8c0c */
	union ddr_csr_mta_cfg_trig_mask mta_cfg_trig_mask; /* offset : 0x8c10 */
	union ddr_csr_mta_cfg_en_mask mta_cfg_en_mask; /* offset : 0x8c14 */
	union ddr_csr_mta_mtc_acq_addr mta_mtc_acq_addr; /* offset : 0x8c18 */
	union ddr_csr_mta_mtc_acq_cycs_stored mta_mtc_acq_cycs_stored; /* offset : 0x8c1c */
	union ddr_csr_mta_mtc_acq_trig_detect mta_mtc_acq_trig_detect; /* offset : 0x8c20 */
	union ddr_csr_mta_mtc_acq_mem_trig_addr mta_mtc_acq_mem_trig_addr; /* offset : 0x8c24 */
	union ddr_csr_mta_mtc_acq_mem_last_addr mta_mtc_acq_mem_last_addr; /* offset : 0x8c28 */
	union ddr_csr_mta_mtc_ack mta_mtc_ack; /* offset : 0x8c2c */
	union ddr_csr_mta_cfg_trig_mt_addr_0 mta_cfg_trig_mt_addr_0; /* offset : 0x8c30 */
	union ddr_csr_mta_cfg_trig_err_mask_0 mta_cfg_trig_err_mask_0; /* offset : 0x8c34 */
	union ddr_csr_mta_cfg_trig_err_mask_1 mta_cfg_trig_err_mask_1; /* offset : 0x8c38 */
	union ddr_csr_mta_cfg_trig_err_mask_2 mta_cfg_trig_err_mask_2; /* offset : 0x8c3c */
	union ddr_csr_mta_cfg_trig_err_mask_3 mta_cfg_trig_err_mask_3; /* offset : 0x8c40 */
	union ddr_csr_mta_cfg_trig_err_mask_4 mta_cfg_trig_err_mask_4; /* offset : 0x8c44 */
	union ddr_csr_mta_cfg_trig_err_mask_5 mta_cfg_trig_err_mask_5; /* offset : 0x8c48 */
	union ddr_csr_mta_cfg_trig_err_mask_6 mta_cfg_trig_err_mask_6; /* offset : 0x8c4c */
	union ddr_csr_mta_cfg_trig_err_mask_7 mta_cfg_trig_err_mask_7; /* offset : 0x8c50 */
	union ddr_csr_mta_cfg_trig_err_mask_8 mta_cfg_trig_err_mask_8; /* offset : 0x8c54 */
	union ddr_csr_mta_cfg_trig_err_mask_9 mta_cfg_trig_err_mask_9; /* offset : 0x8c58 */
	union ddr_csr_mta_cfg_trig_err_mask_10 mta_cfg_trig_err_mask_10; /* offset : 0x8c5c */
	union ddr_csr_mta_cfg_trig_err_mask_11 mta_cfg_trig_err_mask_11; /* offset : 0x8c60 */
	union ddr_csr_mta_cfg_trig_err_mask_12 mta_cfg_trig_err_mask_12; /* offset : 0x8c64 */
	union ddr_csr_mta_cfg_trig_err_mask_13 mta_cfg_trig_err_mask_13; /* offset : 0x8c68 */
	union ddr_csr_mta_cfg_trig_err_mask_14 mta_cfg_trig_err_mask_14; /* offset : 0x8c6c */
	union ddr_csr_mta_cfg_trig_err_mask_15 mta_cfg_trig_err_mask_15; /* offset : 0x8c70 */
	union ddr_csr_mta_cfg_trig_err_mask_16 mta_cfg_trig_err_mask_16; /* offset : 0x8c74 */
	union ddr_csr_mta_mtc_acq_wr_data_0 mta_mtc_acq_wr_data_0; /* offset : 0x8c78 */
	union ddr_csr_mta_mtc_acq_wr_data_1 mta_mtc_acq_wr_data_1; /* offset : 0x8c7c */
	union ddr_csr_mta_mtc_acq_wr_data_2 mta_mtc_acq_wr_data_2; /* offset : 0x8c80 */
	union ddr_csr_mta_mtc_acq_wr_data_3 mta_mtc_acq_wr_data_3; /* offset : 0x8c84 */
	union ddr_csr_mta_mtc_acq_wr_data_4 mta_mtc_acq_wr_data_4; /* offset : 0x8c88 */
	union ddr_csr_mta_mtc_acq_wr_data_5 mta_mtc_acq_wr_data_5; /* offset : 0x8c8c */
	union ddr_csr_mta_mtc_acq_wr_data_6 mta_mtc_acq_wr_data_6; /* offset : 0x8c90 */
	union ddr_csr_mta_mtc_acq_wr_data_7 mta_mtc_acq_wr_data_7; /* offset : 0x8c94 */
	union ddr_csr_mta_mtc_acq_wr_data_8 mta_mtc_acq_wr_data_8; /* offset : 0x8c98 */
	union ddr_csr_mta_mtc_acq_rd_data_0 mta_mtc_acq_rd_data_0; /* offset : 0x8c9c */
	union ddr_csr_mta_mtc_acq_rd_data_1 mta_mtc_acq_rd_data_1; /* offset : 0x8ca0 */
	union ddr_csr_mta_mtc_acq_rd_data_2 mta_mtc_acq_rd_data_2; /* offset : 0x8ca4 */
	union ddr_csr_mta_mtc_acq_rd_data_3 mta_mtc_acq_rd_data_3; /* offset : 0x8ca8 */
	union ddr_csr_mta_mtc_acq_rd_data_4 mta_mtc_acq_rd_data_4; /* offset : 0x8cac */
	union ddr_csr_mta_mtc_acq_rd_data_5 mta_mtc_acq_rd_data_5; /* offset : 0x8cb0 */
	union ddr_csr_mta_mtc_acq_rd_data_6 mta_mtc_acq_rd_data_6; /* offset : 0x8cb4 */
	union ddr_csr_mta_mtc_acq_rd_data_7 mta_mtc_acq_rd_data_7; /* offset : 0x8cb8 */
	union ddr_csr_mta_mtc_acq_rd_data_8 mta_mtc_acq_rd_data_8; /* offset : 0x8cbc */
	union ddr_csr_mta_cfg_pre_trig_cycs mta_cfg_pre_trig_cycs; /* offset : 0x8cc0 */
	union ddr_csr_mta_mtc_acq_error_cnt mta_mtc_acq_error_cnt; /* offset : 0x8cc4 */
	union ddr_csr_mta_mtc_acq_error_cnt_ovfl mta_mtc_acq_error_cnt_ovfl; /* offset : 0x8cc8 */
	union ddr_csr_mta_cfg_data_sel_first_error mta_cfg_data_sel_first_error; /* offset : 0x8ccc */
	union ddr_csr_mta_mtc_acq_data_sel mta_mtc_acq_data_sel; /* offset : 0x8cd0 */
	uint32_t reserved_71[459];
	union ddr_csr_mc_base5_cfg_ccd_l mc_base5_cfg_ccd_l; /* offset : 0x9400 */
	uint32_t reserved_72;
	union ddr_csr_mc_base5_cfg_wtr_s mc_base5_cfg_wtr_s; /* offset : 0x9408 */
	union ddr_csr_mc_base5_cfg_wtr_l mc_base5_cfg_wtr_l; /* offset : 0x940c */
	union ddr_csr_mc_base5_cfg_rrefd mc_base5_cfg_rrefd; /* offset : 0x9410 */
	union ddr_csr_mc_base5_cfg_rcd_rd mc_base5_cfg_rcd_rd; /* offset : 0x9414 */
	union ddr_csr_mc_base5_cfg_rcd_wr mc_base5_cfg_rcd_wr; /* offset : 0x9418 */
	union ddr_csr_mc_base5_cfg_ras mc_base5_cfg_ras; /* offset : 0x941c */
	uint32_t reserved_73;
	union ddr_csr_mc_base5_cfg_rrd_s mc_base5_cfg_rrd_s; /* offset : 0x9424 */
	union ddr_csr_mc_base5_cfg_rrd_l mc_base5_cfg_rrd_l; /* offset : 0x9428 */
	union ddr_csr_mc_base5_cfg_rp mc_base5_cfg_rp; /* offset : 0x942c */
	union ddr_csr_mc_base5_cfg_rc mc_base5_cfg_rc; /* offset : 0x9430 */
	union ddr_csr_mc_base5_cfg_faw mc_base5_cfg_faw; /* offset : 0x9434 */
	union ddr_csr_mc_base5_cfg_rfc mc_base5_cfg_rfc; /* offset : 0x9438 */
	union ddr_csr_mc_base5_cfg_rfcsb mc_base5_cfg_rfcsb; /* offset : 0x943c */
	union ddr_csr_mc_base5_cfg_rtp mc_base5_cfg_rtp; /* offset : 0x9440 */
	union ddr_csr_mc_base5_cfg_wr mc_base5_cfg_wr; /* offset : 0x9444 */
	union ddr_csr_mc_base5_cfg_xp mc_base5_cfg_xp; /* offset : 0x9448 */
	union ddr_csr_mc_base5_cfg_xpr mc_base5_cfg_xpr; /* offset : 0x944c */
	union ddr_csr_mc_base5_cfg_xs mc_base5_cfg_xs; /* offset : 0x9450 */
	uint32_t reserved_74[3];
	union ddr_csr_mc_base5_cfg_mod mc_base5_cfg_mod; /* offset : 0x9460 */
	uint32_t reserved_75[5];
	union ddr_csr_mc_base5_cfg_wl mc_base5_cfg_wl; /* offset : 0x9478 */
	union ddr_csr_mc_base5_cfg_rl mc_base5_cfg_rl; /* offset : 0x947c */
	uint32_t reserved_76;
	union ddr_csr_mc_base5_cfg_cksre mc_base5_cfg_cksre; /* offset : 0x9484 */
	union ddr_csr_mc_base5_cfg_cksrx mc_base5_cfg_cksrx; /* offset : 0x9488 */
	uint32_t reserved_77[6];
	union ddr_csr_mc_base5_init_abref mc_base5_init_abref; /* offset : 0x94a4 */
	union ddr_csr_mc_base5_init_ref_per mc_base5_init_ref_per; /* offset : 0x94a8 */
	uint32_t reserved_78[7];
	union ddr_csr_mc_base5_cfg_startup_delay mc_base5_cfg_startup_delay; /* offset : 0x94c8 */
	union ddr_csr_mc_base5_cfg_idle_time_to_self_refresh mc_base5_cfg_idle_time_to_self_refresh;
	/* offset : 0x94cc */
	union ddr_csr_mc_base5_init_idle_time_to_power_down mc_base5_init_idle_time_to_power_down;
	/* offset : 0x94d0 */
	union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_1
		mc_base5_init_idle_time_to_lp_data_wakeup_1; /* offset : 0x94d4 */
	union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_2
		mc_base5_init_idle_time_to_lp_data_wakeup_2; /* offset : 0x94d8 */
	union ddr_csr_mc_base5_cfg_sbref_issue_per mc_base5_cfg_sbref_issue_per; /* offset : 0x94dc */
	union ddr_csr_mc_base5_cfg_ecc_scrub_period mc_base5_cfg_ecc_scrub_period; /* offset : 0x94e0 */
	union ddr_csr_mc_base5_cfg_read_to_write mc_base5_cfg_read_to_write; /* offset : 0x94e4 */
	uint32_t reserved_79[10];
	union ddr_csr_mc_base5_cfg_ds mc_base5_cfg_ds; /* offset : 0x9510 */
	uint32_t reserved_80[16];
	union ddr_csr_mc_base5_cfg_hbm_parity_latency mc_base5_cfg_hbm_parity_latency;
	/* offset : 0x9554 */
	union ddr_csr_mc_base5_cfg_int_vref mc_base5_cfg_int_vref; /* offset : 0x9558 */
	uint32_t reserved_81[30];
	union ddr_csr_mc_base5_cfg_lp_data_duration_1 mc_base5_cfg_lp_data_duration_1;
	/* offset : 0x95d4 */
	union ddr_csr_mc_base5_cfg_lp_data_duration_2 mc_base5_cfg_lp_data_duration_2;
	/* offset : 0x95d8 */
	uint32_t reserved_82[24];
	union ddr_csr_mc_base5_cfg_vref_settle_time mc_base5_cfg_vref_settle_time; /* offset : 0x963c */
	uint32_t reserved_83[21];
	union ddr_csr_mc_base5_init_idle_time_to_lp_data_wakeup_3
		mc_base5_init_idle_time_to_lp_data_wakeup_3; /* offset : 0x9694 */
	union ddr_csr_mc_base5_cfg_lp_data_duration_3 mc_base5_cfg_lp_data_duration_3;
	/* offset : 0x9698 */
	uint32_t reserved_84[1369];
	union ddr_csr_act_mon_am_wr_cmd act_mon_am_wr_cmd; /* offset : 0xac00 */
	union ddr_csr_act_mon_am_wr_ap_cmd act_mon_am_wr_ap_cmd; /* offset : 0xac04 */
	union ddr_csr_act_mon_am_rd_cmd act_mon_am_rd_cmd; /* offset : 0xac08 */
	union ddr_csr_act_mon_am_rd_ap_cmd act_mon_am_rd_ap_cmd; /* offset : 0xac0c */
	union ddr_csr_act_mon_am_refresh_cmd act_mon_am_refresh_cmd; /* offset : 0xac10 */
	union ddr_csr_act_mon_am_act_cmd act_mon_am_act_cmd; /* offset : 0xac14 */
	union ddr_csr_act_mon_am_precharge_cmd act_mon_am_precharge_cmd; /* offset : 0xac18 */
	union ddr_csr_act_mon_am_precharge_all_cmd act_mon_am_precharge_all_cmd; /* offset : 0xac1c */
	union ddr_csr_act_mon_am_power_down act_mon_am_power_down; /* offset : 0xac20 */
	union ddr_csr_act_mon_am_self_refresh act_mon_am_self_refresh; /* offset : 0xac24 */
	union ddr_csr_act_mon_am_rd_to_wr_switch act_mon_am_rd_to_wr_switch; /* offset : 0xac28 */
	union ddr_csr_act_mon_am_ro_age_limit act_mon_am_ro_age_limit; /* offset : 0xac2c */
	union ddr_csr_act_mon_am_rmw_cycle act_mon_am_rmw_cycle; /* offset : 0xac30 */
	union ddr_csr_act_mon_am_interval_count_axi1 act_mon_am_interval_count_axi1;
	/* offset : 0xac34 */
	union ddr_csr_act_mon_am_wac_active_axi1 act_mon_am_wac_active_axi1; /* offset : 0xac38 */
	union ddr_csr_act_mon_am_wac_stall_axi1 act_mon_am_wac_stall_axi1; /* offset : 0xac3c */
	union ddr_csr_act_mon_am_rac_active_axi1 act_mon_am_rac_active_axi1; /* offset : 0xac40 */
	union ddr_csr_act_mon_am_rac_stall_axi1 act_mon_am_rac_stall_axi1; /* offset : 0xac44 */
	union ddr_csr_act_mon_am_wdc_active_axi1 act_mon_am_wdc_active_axi1; /* offset : 0xac48 */
	union ddr_csr_act_mon_am_wdc_stall_axi1 act_mon_am_wdc_stall_axi1; /* offset : 0xac4c */
	union ddr_csr_act_mon_am_rdc_active_axi1 act_mon_am_rdc_active_axi1; /* offset : 0xac50 */
	union ddr_csr_act_mon_am_rdc_stall_axi1 act_mon_am_rdc_stall_axi1; /* offset : 0xac54 */
	union ddr_csr_act_mon_am_ctrlr_queue_sum_0 act_mon_am_ctrlr_queue_sum_0; /* offset : 0xac58 */
	union ddr_csr_act_mon_am_ctrlr_queue_sum_1 act_mon_am_ctrlr_queue_sum_1; /* offset : 0xac5c */
	union ddr_csr_act_mon_am_ctrlr_queue_max_0 act_mon_am_ctrlr_queue_max_0; /* offset : 0xac60 */
	union ddr_csr_act_mon_am_ctrlr_queue_min_0 act_mon_am_ctrlr_queue_min_0; /* offset : 0xac64 */
	uint32_t reserved_85[4];
	union ddr_csr_act_mon_am_wcf_sum_axi1_0 act_mon_am_wcf_sum_axi1_0; /* offset : 0xac78 */
	union ddr_csr_act_mon_am_wcf_sum_axi1_1 act_mon_am_wcf_sum_axi1_1; /* offset : 0xac7c */
	union ddr_csr_act_mon_am_wcf_max_axi1_0 act_mon_am_wcf_max_axi1_0; /* offset : 0xac80 */
	union ddr_csr_act_mon_am_wcf_min_axi1_0 act_mon_am_wcf_min_axi1_0; /* offset : 0xac84 */
	union ddr_csr_act_mon_am_rcf_sum_axi1_0 act_mon_am_rcf_sum_axi1_0; /* offset : 0xac88 */
	union ddr_csr_act_mon_am_rcf_sum_axi1_1 act_mon_am_rcf_sum_axi1_1; /* offset : 0xac8c */
	union ddr_csr_act_mon_am_rcf_max_axi1_0 act_mon_am_rcf_max_axi1_0; /* offset : 0xac90 */
	union ddr_csr_act_mon_am_rcf_min_axi1_0 act_mon_am_rcf_min_axi1_0; /* offset : 0xac94 */
	union ddr_csr_act_mon_am_wdf_sum_axi1_0 act_mon_am_wdf_sum_axi1_0; /* offset : 0xac98 */
	union ddr_csr_act_mon_am_wdf_sum_axi1_1 act_mon_am_wdf_sum_axi1_1; /* offset : 0xac9c */
	union ddr_csr_act_mon_am_wdf_max_axi1_0 act_mon_am_wdf_max_axi1_0; /* offset : 0xaca0 */
	union ddr_csr_act_mon_am_wdf_min_axi1_0 act_mon_am_wdf_min_axi1_0; /* offset : 0xaca4 */
	union ddr_csr_act_mon_am_rdf_sum_axi1_0 act_mon_am_rdf_sum_axi1_0; /* offset : 0xaca8 */
	union ddr_csr_act_mon_am_rdf_sum_axi1_1 act_mon_am_rdf_sum_axi1_1; /* offset : 0xacac */
	union ddr_csr_act_mon_am_rdf_max_axi1_0 act_mon_am_rdf_max_axi1_0; /* offset : 0xacb0 */
	union ddr_csr_act_mon_am_rdf_min_axi1_0 act_mon_am_rdf_min_axi1_0; /* offset : 0xacb4 */
	union ddr_csr_act_mon_am_rfm_cmd act_mon_am_rfm_cmd; /* offset : 0xacb8 */
	union ddr_csr_act_mon_cfg_am_rfm_threshold act_mon_cfg_am_rfm_threshold; /* offset : 0xacbc */
	union ddr_csr_act_mon_am_power_down_transition_count act_mon_am_power_down_transition_count;
	/* offset : 0xacc0 */
	union ddr_csr_act_mon_am_lp_data_1 act_mon_am_lp_data_1; /* offset : 0xacc4 */
	union ddr_csr_act_mon_am_lp_data_transition_count_1 act_mon_am_lp_data_transition_count_1;
	/* offset : 0xacc8 */
	union ddr_csr_act_mon_am_lp_data_2 act_mon_am_lp_data_2; /* offset : 0xaccc */
	union ddr_csr_act_mon_am_lp_data_transition_count_2 act_mon_am_lp_data_transition_count_2;
	/* offset : 0xacd0 */
	union ddr_csr_act_mon_am_lp_data_3 act_mon_am_lp_data_3; /* offset : 0xacd4 */
	union ddr_csr_act_mon_am_lp_data_transition_count_3 act_mon_am_lp_data_transition_count_3;
	/* offset : 0xacd8 */
	uint32_t reserved_86[3785];
	union ddr_csr_csr_custom_phy_wck_toggle_dly csr_custom_phy_wck_toggle_dly; /* offset : 0xe800 */
	union ddr_csr_csr_custom_phy_rddata_en_dly csr_custom_phy_rddata_en_dly; /* offset : 0xe804 */
	uint32_t reserved_87[50686];
};

