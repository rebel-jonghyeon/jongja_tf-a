/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <lib/libc/stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <platform_def.h>
#include <common/debug.h>
#include <drivers/hbm3/hbm3_init.h>
#include <drivers/hbm3/hbm3_timing.h>
#include <drivers/delay_timer.h>
#include <cmu.h>
#include <rebel_h_pmu.h>

#define RUN_EXTEST 1
#define RUN_MBIST 0
#if RUN_MBIST
#define RUN_CDC 1
#endif

#define SAMSUNG_PHY_CTRL_READDURADJ(ck_freq) ((NS_TO_CYCLES(2.275, ck_freq) - 3.5) + 1)
#define SAMSUNG_PHY_CTRL_READDURADJ_DQS(ck_freq) ((NS_TO_CYCLES(2.275, ck_freq) - 1.5) + 1)

/* global variable */
union phy_vwm vwm_buf;
union phy_vwm max_vwm_buf;
union phy_offset max_offset_buf;
int8_t rep_status[HBM3_NUM_CH];
uint8_t ch_rep_lane[HBM3_NUM_CH][REDUNDANT];

extern uint32_t hbm_target_lvl;

lane_map dq_lane[] = {
	{0, "DQ0", 0x1, DWORD0_BYTE0},
	{1, "DQ1", 0x2, DWORD0_BYTE0},
	{2, "DQ2", 0x3, DWORD0_BYTE0},
	{3, "DQ3", 0x4, DWORD0_BYTE0},
	{4, "DQ4", 0x5, DWORD0_BYTE0},
	{5, "DQ5", 0x6, DWORD0_BYTE0},
	{6, "DQ6", 0x7, DWORD0_BYTE0},
	{7, "DQ7", 0x8, DWORD0_BYTE0},
	{8, "DQ8", 0x1, DWORD0_BYTE1},
	{9, "DQ9", 0x2, DWORD0_BYTE1},
	{10, "DQ10", 0x3, DWORD0_BYTE1},
	{11, "DQ11", 0x4, DWORD0_BYTE1},
	{12, "DQ12", 0x5, DWORD0_BYTE1},
	{13, "DQ13", 0x6, DWORD0_BYTE1},
	{14, "DQ14", 0x7, DWORD0_BYTE1},
	{15, "DQ15", 0x8, DWORD0_BYTE1},
	{16, "DQ16", 0x1, DWORD0_BYTE2},
	{17, "DQ17", 0x2, DWORD0_BYTE2},
	{18, "DQ18", 0x3, DWORD0_BYTE2},
	{19, "DQ19", 0x4, DWORD0_BYTE2},
	{20, "DQ20", 0x5, DWORD0_BYTE2},
	{21, "DQ21", 0x6, DWORD0_BYTE2},
	{22, "DQ22", 0x7, DWORD0_BYTE2},
	{23, "DQ23", 0x8, DWORD0_BYTE2},
	{24, "DQ24", 0x1, DWORD0_BYTE3},
	{25, "DQ25", 0x2, DWORD0_BYTE3},
	{26, "DQ26", 0x3, DWORD0_BYTE3},
	{27, "DQ27", 0x4, DWORD0_BYTE3},
	{28, "DQ28", 0x5, DWORD0_BYTE3},
	{29, "DQ29", 0x6, DWORD0_BYTE3},
	{30, "DQ30", 0x7, DWORD0_BYTE3},
	{31, "DQ31", 0x8, DWORD0_BYTE3}
};

lane_map ecc_lane[] = {
	{0, "ECC0", 0x0, DWORD0_BYTE0},
	{1, "ECC1", 0x0, DWORD0_BYTE1}
};

lane_map sev_lane[] = {
	{0, "SEV0", 0x0, DWORD0_BYTE2},
	{1, "SEV1", 0x0, DWORD0_BYTE3}
};

lane_map dbi_lane[] = {
	{0, "DBI0", 0x9, DWORD0_BYTE0},
	{1, "DBI1", 0x9, DWORD0_BYTE1},
	{2, "DBI2", 0x9, DWORD0_BYTE2},
	{3, "DBI3", 0x9, DWORD0_BYTE3},
};

/* global configuration */
static struct system_config_t system_config = {
#if HBM_DATA_RATE == 9600
	.op_datarate = hbm3_datarate_9600mbps,
#elif HBM_DATA_RATE == 9200
	.op_datarate = hbm3_datarate_9200mbps,
#elif HBM_DATA_RATE == 8000
	.op_datarate = hbm3_datarate_8000mbps,
#elif HBM_DATA_RATE == 6400
	.op_datarate = hbm3_datarate_6400mbps,
#else
	.op_datarate = hbm3_datarate_4800mbps,
#endif
	.cfg_dbi_off = false,
	.cfg_bg_interleave_on = true,
	.cfg_ecs_on = false,
	.cfg_all_bank_ref = false,
	.cfg_parity_dis = true,
#if ZEBU
	.cfg_dis_ecc = true,
	.cfg_ecc_bypass  = true,
	.cfg_dis_on_die_ecc = true,
	.cfg_auto_self_ref_en = false,
	.cfg_auto_power_down_en = false,
#else
	.cfg_dis_ecc = false,
	.cfg_ecc_bypass = false,
	.cfg_dis_on_die_ecc = false,
	.cfg_auto_self_ref_en = false,
	.cfg_auto_power_down_en = false,
#endif
	.cfg_en_rfm = false, // Samsung HBM3E not Supprt RFM. use Internal logic for RH
	.cfg_periodic_tr_en = false,
};

void enable_hashing(struct hbm3_config *cfg, bool enable)
{
	if (enable && GET_REVISION == REVISION_EVT0) {
		cfg->sysreg_base->cfg_custom_hash_bitmask_0.value = 0x108421;
		cfg->sysreg_base->cfg_custom_hash_bitmask_1.value = 0x210842;
		cfg->sysreg_base->cfg_custom_hash_bitmask_2.value = 0x021084;
		cfg->sysreg_base->cfg_custom_hash_bitmask_3.value = 0x042108;
		cfg->sysreg_base->cfg_custom_hash_bitmask_4.value = 0x084210;
		cfg->sysreg_base->cfg_custom_hash_ctrl.enable = 0x1; // 0x1 : enable, 0x0 : disable
	} else if (enable && GET_REVISION == REVISION_EVT1) {
		cfg->sysreg_base->cfg_custom_hash_bitmask_0.value = 0x108421;
		cfg->sysreg_base->cfg_custom_hash_bitmask_1.value = 0x210842;
		cfg->sysreg_base->cfg_custom_hash_bitmask_2.value = 0x021084;
		cfg->sysreg_base->cfg_custom_hash_bitmask_3.value = 0x042108;
		cfg->sysreg_base->cfg_custom_hash_bitmask_4.value = 0x084210;
		cfg->sysreg_base->user_reg3.val = 0x40000;
		cfg->sysreg_base->user_reg4.val = 0x80000;
		cfg->sysreg_base->cfg_custom_hash_ctrl.enable = 0x1; // 0x1 : enable, 0x0 : disable
	}

	INFO("Hashing Enable Done: %d\n", enable);

	udelay(1 * 10);
}

static uint32_t get_clock_frequency(uint8_t datarate)
{
	switch (datarate) {
	case hbm3_datarate_4800mbps:
		return CK_1200MHZ;
	case hbm3_datarate_6400mbps:
		return CK_1600MHZ;
	case hbm3_datarate_8000mbps:
		return CK_2000MHZ;
	case hbm3_datarate_9200mbps:
		return CK_2300MHZ;
	case hbm3_datarate_9600mbps:
		return CK_2400MHZ;
	default:
		return 0;
	}
}

static void set_ctrl_timing(struct hbm3_config *cfg, uint8_t ch, uint32_t ck_freq)
{
	/* Set Timing Parameter S */
	/* Samsung 24Gb 12H HBM3E SE specific timing configuration */
	cfg->csr_base[ch]->mc_base5_cfg_cksrx.cfg_cksrx = SAMSUNG_24G_12H_HBM3E_SE_tCKSRX(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rtp.cfg_rtp = SAMSUNG_24G_12H_HBM3E_SE_tRTP(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rfcsb.cfg_rfcsb = SAMSUNG_24G_12H_HBM3E_SE_tRFCpb(ck_freq);

	/* Latency settings */
	cfg->csr_base[ch]->mc_base5_cfg_rl.cfg_rl = SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_wl.cfg_wl = SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_wr.cfg_wr = SAMSUNG_24G_12H_HBM3E_SE_tWR(ck_freq);

	/* Row access timing */
	cfg->csr_base[ch]->mc_base5_cfg_rc.cfg_rc = SAMSUNG_24G_12H_HBM3E_SE_tRC(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_ras.cfg_ras = SAMSUNG_24G_12H_HBM3E_SE_tRAS(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rcd_rd.cfg_rcd_rd = SAMSUNG_24G_12H_HBM3E_SE_tRCDRD(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rcd_wr.cfg_rcd_wr = SAMSUNG_24G_12H_HBM3E_SE_tRCDWR(ck_freq);

	/* Row-to-row delay timing */
	cfg->csr_base[ch]->mc_base5_cfg_rrd_l.cfg_rrd_l = SAMSUNG_24G_12H_HBM3E_SE_tRRDL(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rrd_s.cfg_rrd_s = SAMSUNG_24G_12H_HBM3E_SE_tRRDS(ck_freq);

	/* Four bank activation and precharge timing */
	cfg->csr_base[ch]->mc_base5_cfg_faw.cfg_faw = SAMSUNG_24G_12H_HBM3E_SE_tFAW(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rp.cfg_rp = SAMSUNG_24G_12H_HBM3E_SE_tRP(ck_freq);

	/* Write-to-read delay timing */
	cfg->csr_base[ch]->mc_base5_cfg_wtr_l.cfg_wtr_l = SAMSUNG_24G_12H_HBM3E_SE_tWTRL(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_wtr_s.cfg_wtr_s = SAMSUNG_24G_12H_HBM3E_SE_tWTRS(ck_freq);

	/* Self-refresh and power-down timing */
	cfg->csr_base[ch]->mc_base5_cfg_cksre.cfg_cksre = SAMSUNG_24G_12H_HBM3E_SE_tCKSRE(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_xs.cfg_xs = SAMSUNG_24G_12H_HBM3E_SE_tXS(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_xp.cfg_xp = SAMSUNG_24G_12H_HBM3E_SE_tXP(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_xpr.cfg_xpr = SAMSUNG_24G_12H_HBM3E_SE_tXPR(ck_freq);

	/* Refresh timing */
	cfg->csr_base[ch]->mc_base5_cfg_rfc.cfg_rfc = SAMSUNG_24G_12H_HBM3E_SE_tRFCab(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_rrefd.cfg_rrefd = SAMSUNG_24G_12H_HBM3E_SE_tRREFD(ck_freq);
	cfg->csr_base[ch]->mc_base5_init_ref_per.init_ref_per = SAMSUNG_24G_12H_HBM3E_SE_tREFI(ck_freq);

	/* Column command delay timing */
	cfg->csr_base[ch]->mc_base1_cfg_ccd_s.cfg_ccd_s = SAMSUNG_24G_12H_HBM3E_SE_tCCDS(ck_freq);
	cfg->csr_base[ch]->mc_base1_cfg_ccd_r.cfg_ccd_r = SAMSUNG_24G_12H_HBM3E_SE_tCCDR(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_ccd_l.cfg_ccd_l = SAMSUNG_24G_12H_HBM3E_SE_tCCDL(ck_freq);

	/* Mode register and parity timing */
	cfg->csr_base[ch]->mc_base5_cfg_mod.cfg_mod = SAMSUNG_24G_12H_HBM3E_SE_tMOD(ck_freq);
	cfg->csr_base[ch]->mc_base5_cfg_hbm_parity_latency.cfg_hbm_parity_latency =
		SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq);
}

static void set_ctrl_config(struct hbm3_config *cfg, unsigned int ch)
{
	/* controller initial setting S */
	//cfg->sysreg_base->hbmc_paddr_select_all.en = 0x1;
#if !ZEBU
	cfg->csr_base[ch]->dfi_phy_ca_training_en.phy_ca_training_en = 1;
#else
	cfg->csr_base[ch]->dfi_phy_ca_training_en.phy_ca_training_en = 0;
#endif

	/* axi addr range */
	cfg->csr_base[ch]->axi_if_cfg_axi_start_address_axi1_0.cfg_axi_start_address_axi1 = 0;
	cfg->csr_base[ch]->axi_if_cfg_axi_end_address_axi1_0.cfg_axi_end_address_axi1 = 0xFFFFFFFF;

	/* Common parameter */
#if ZEBU
	cfg->csr_base[ch]->mc_base5_cfg_startup_delay.cfg_startup_delay = 0x7d0;
#endif

	/* Non-timing controller configuration */
	cfg->csr_base[ch]->mc_base5_cfg_sbref_issue_per.cfg_sbref_issue_per = 0x8c;
	cfg->csr_base[ch]->mc_base5_cfg_read_to_write.cfg_read_to_write = 0xf;

	/* Density */
	cfg->csr_base[ch]->mc_base2_cfg_mem_rowbits.cfg_mem_rowbits = 0xf;
	cfg->csr_base[ch]->mc_base2_cfg_mem_bankbits.cfg_mem_bankbits = 0x6;
	cfg->csr_base[ch]->mc_base3_cfg_np2_rows.cfg_np2_rows = 0x1;
	cfg->csr_base[ch]->mc_base3_cfg_12hi.cfg_12hi = 0x1;
}

static void set_ctrl_feature(struct hbm3_config *cfg, unsigned int ch)
{
	/* Set Timing Parameter E */
	/* Configure DBI settings */
	if (system_config.cfg_dbi_off) {
		cfg->csr_base[ch]->mc_base1_cfg_read_dbi.cfg_read_dbi = 0x0;
		cfg->csr_base[ch]->mc_base1_cfg_write_dbi.cfg_write_dbi = 0x0;
	}

	/* Configure bank group interleave */
	if (!system_config.cfg_bg_interleave_on) {
		cfg->csr_base[ch]->mc_base2_cfg_bg_interleave.cfg_bg_interleave = 0x0;
	}

	/* Configure ECS settings */
	if (system_config.cfg_ecs_on) {
		/* Need to check : can enable ECS in SS HBM3 Memory */
		cfg->csr_base[ch]->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0x1;
		cfg->csr_base[ch]->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw = 0x1;
		cfg->csr_base[ch]->mc_base5_cfg_ecc_scrub_period.cfg_ecc_scrub_period = 0x1;
		cfg->csr_base[ch]->ecc_config_cfg_ecc_scrub_min_addr_0.cfg_ecc_scrub_min_addr = 0x0;
		cfg->csr_base[ch]->ecc_config_cfg_ecc_scrub_max_addr_0.cfg_ecc_scrub_max_addr = 0x400;
	} else {
		cfg->csr_base[ch]->mc_base1_cfg_auto_ecs_on_ref.cfg_auto_ecs_on_ref = 0x0;
		cfg->csr_base[ch]->mc_base1_cfg_auto_ecs_on_sr.cfg_auto_ecs_on_sr = 0x0;
		cfg->csr_base[ch]->mc_base1_cfg_ecs_mberr_scrub_enable.cfg_ecs_mberr_scrub_enable = 0x0;
		cfg->csr_base[ch]->mc_base1_cfg_ecs_reset.cfg_ecs_reset = 0x0;
	}
	cfg->csr_base[ch]->ecc_config_cfg_ecc_scrub_max_addr_0.cfg_ecc_scrub_max_addr = 0x8fffffc0;
	cfg->csr_base[ch]->mc_base3_cfg_dfi_phyupd_idle_sel.cfg_dfi_phyupd_idle_sel = 1;

	/* Configure RFM settings */
	if (system_config.cfg_en_rfm) {
		/* Need to check : SS HBM memory not recommand RFM.  */
		cfg->csr_base[ch]->mc_base3_init_rfm_en.init_rfm_en = 0x1;
	}

	/* Configure ECC settings */
	if (system_config.cfg_dis_ecc) {
		cfg->csr_base[ch]->ecc_config_cfg_ecc_correction_en.cfg_ecc_correction_en = ECC_DISABLE;
	} else {
		cfg->csr_base[ch]->ecc_config_cfg_ecc_correction_en.cfg_ecc_correction_en = ECC_ENABLE;
	}

	if (system_config.cfg_ecc_bypass) {
		cfg->csr_base[ch]->ecc_config_cfg_ecc_bypass.cfg_ecc_bypass = ECC_BYPASS_ENABLE;
	}

	/* Configure parity settings */
	if (system_config.cfg_parity_dis) {
		cfg->csr_base[ch]->mc_base1_cfg_rd_dq_parity_en.cfg_rd_dq_parity_en = PARITY_DISABLE;
		cfg->csr_base[ch]->mc_base1_cfg_wr_dq_parity_en.cfg_wr_dq_parity_en = PARITY_DISABLE;
		cfg->csr_base[ch]->mc_base1_cfg_ca_parity_en.cfg_ca_parity_en = PARITY_DISABLE;
	}

	/* Configure all bank refresh settings */
	if (system_config.cfg_all_bank_ref) {
		cfg->csr_base[ch]->mc_base1_init_sbref_en.init_sbref_en = 0x0;
	}

	/* Configure on-die ECC settings */
	if (system_config.cfg_dis_on_die_ecc) {
		cfg->csr_base[ch]->mc_base1_cfg_severity_en.cfg_severity_en = 0x0;
	}

	/* Configure power management settings */
	if (system_config.cfg_auto_self_ref_en) {
		/* A value of 0 disables. the automatic self-refresh entry feature. */
		/* A value less than tXS/tXSR in memory clocks is prohibited */
		cfg->csr_base[ch]->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh =
			cfg->csr_base[ch]->mc_base5_cfg_xs.cfg_xs + 5; /* Need to check */
	}

	if (system_config.cfg_auto_power_down_en) {
		/* During normal operation, user should write 0 first, before writing a new value. */
		/* This function and automatic self-refresh are mutually exclusive, */
		cfg->csr_base[ch]->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh =
			0x0;
		/* Need to Check : tPD + tXP */
		cfg->csr_base[ch]->mc_base5_init_idle_time_to_power_down.init_idle_time_to_power_down = 36;
	}

	/* controller initial setting E */
	// rdata = cfg->csr_base[ch]->mc_base1_cfg_auto_mr_prog_en.val;
	// printf("Check auto MRS bit = 0x%x\n", rdata);

	/* Reset Value : 0xc37f = 2'b 0011 0011 0111 1111 */
	/* MR 0,1,2,3,4,5,6,8,9,12,13 */

	/* Set Vref & Driver Strength */
	/* HBM3 is a 16 bit value : the lower 8 bits are used when MR14 is */
	/* written and bits 6:1 define the value of VREFCA */
	/* The upper 8-bits are used when MR15 is written */
	/* and bits 14:9 define the value of VREFD. */
	/* 0x4040  = 0100 0000 0100 0000 = VREFCA  VREFD = 0.5 x VDDQL */
	cfg->csr_base[ch]->mc_base5_cfg_int_vref.cfg_int_vref = HBM3_INIT_VREF;

	/* Bit 2:0 used for HBM3 Pulldown Driver Strength and Bit 5:3 used */
	/* for HBM3 Pullup Driver Stength */
	/* 0x1b : PUDS : 12mA / PDDS : 12mA */
	/* Hidden value : 0x2d : PUDS/PDDS > 14mA */
	cfg->csr_base[ch]->mc_base5_cfg_ds.cfg_ds = HBM3_INIT_DS;

	/*  Wait for tINIT1(200us) */
	udelay(2 * 100);
}

#if !ZEBU
void set_zq_calibration(struct hbm3_config *cfg, uint8_t ch)
{
	uint8_t zq_pmon = 0, zq_nmon = 0;

	/* Set ZQ cal value */
	if (GET_REVISION == REVISION_EVT0) {
		zq_pmon = (cfg->sysreg_base->evt0_zq_icon_reg0.o_zctrl_pmon & 0x7);
		zq_nmon = (cfg->sysreg_base->evt0_zq_icon_reg0.o_zctrl_nmon & 0x7);
	} else {
		zq_pmon = cfg->icon_base->evt1_zq_mon0.o_zq_zctrl_pmon & 0x7;
		zq_nmon = cfg->icon_base->evt1_zq_mon0.o_zq_zctrl_nmon & 0x7;
	}

	cfg->phy_base[ch]->io_vref_con0.zq_aword_pmon = zq_pmon;
	cfg->phy_base[ch]->io_vref_con0.zq_aword_nmon = zq_nmon;

	cfg->phy_base[ch]->io_vref_con1.zq_dword0_pmon = ((zq_pmon << 3) | zq_pmon);
	cfg->phy_base[ch]->io_vref_con1.zq_dword0_nmon = ((zq_nmon << 3) | zq_nmon);

	cfg->phy_base[ch]->io_vref_con2.zq_dword1_pmon = ((zq_pmon << 3) | zq_pmon);
	cfg->phy_base[ch]->io_vref_con2.zq_dword1_nmon = ((zq_nmon << 3) | zq_nmon);
}
#endif

static void set_phy_config(struct hbm3_config *cfg, uint8_t ch, uint32_t ck_freq)
{
	/* phy initial setting S */
	/* Initialization of HBM3_PHY */
	cfg->phy_base[ch]->cal_con0.dfi_dram_clk_disable_apb = 0x0;

	// PHY team confirm that EVT1 value is correct.
	cfg->phy_base[ch]->cal_con2.ctrl_readadj = 2;
	cfg->phy_base[ch]->cal_con2.ctrl_readduradj = 1;
	cfg->phy_base[ch]->cal_con4.ctrl_readadj_dqs = SAMSUNG_PHY_CTRL_READDURADJ(ck_freq);
	cfg->phy_base[ch]->cal_con4.ctrl_readduradj_dqs = SAMSUNG_PHY_CTRL_READDURADJ_DQS(ck_freq);

	cfg->csr_base[ch]->csr_custom_phy_rddata_en_dly.phy_rddata_en_dly = 0x8;

#if !ZEBU
	// use default zq cal to imporve write margin
	// set_zq_calibration(cfg, ch);
#endif

	cfg->phy_base[ch]->gnr_con0.init_resync_mode = 0x1;
	udelay(1);

	cfg->csr_base[ch]->mc_base2_ctrlr_soft_reset_n.ctrlr_soft_reset_n = 0x1;

	/* for coverage only */
	// cfg->csr_base[ch]->mc_base2_init_force_reset.init_force_reset = 0x1;
	udelay(1);
	//cfg->csr_base[ch]->mc_base2_init_force_reset.init_force_reset = 0x0;
}

void hbm3_dfi_init(struct hbm3_config *cfg, unsigned int ch, uint32_t *retry)
{
	uint32_t rdata;

	/* DFI Initialization */
	cfg->csr_base[ch]->dfi_phy_dfi_init_start.phy_dfi_init_start = 0x1;
	udelay(5);

	do {
		rdata = cfg->csr_base[ch]->dfi_stat_dfi_init_complete.val;
		if (*retry > 1000) {
			ERROR("CH[%d] dfi_init fail..\n", ch);
			return;
		}
		(*retry)++;
	} while ((rdata & 0x1) != 0x1);

	cfg->csr_base[ch]->dfi_phy_dfi_init_start.phy_dfi_init_start = 0x0;

	cfg->sysreg_base->icon_wrstn.rst_ctrl = 0x1;

	cfg->phy_base[ch]->gnr_con0.init_resync_mode = 0x0;

	INFO("CH[%d] dfi_init_complete..\n", ch);
}

uint32_t icon_mrs(struct hbm3_config *cfg, enum ch_select ch)
{
	uint8_t rd_lat, wr_lat, par_lat;
	uint8_t ca_vref, dq_vref;

	rd_lat = get_read_latency(system_config.op_datarate);
	wr_lat = get_write_latency(system_config.op_datarate);
	par_lat = cfg->csr_base[0]->mc_base5_cfg_hbm_parity_latency.cfg_hbm_parity_latency;

	ca_vref = (cfg->csr_base[0]->mc_base5_cfg_int_vref.cfg_int_vref) & 0xFF;
	dq_vref = ((cfg->csr_base[0]->mc_base5_cfg_int_vref.cfg_int_vref) >> 8) & 0xFF;

	union hbm3_mr_t mr = {
		.mr0 = {
			.read_dbi = 1,
			.write_dbi = 1,
			.tcsr = 1, //2025-1127 try this config, but not effectivetcsr disable -> 0
			.rsvd0 = 0,
			.read_parity = 0,
			.write_parity = 0,
			.ca_parity = 0,
			.test_mdoe = 0,
		},
		.mr1 = {
			.write_latency = wr_lat,
			.parity_latency = par_lat,
		},
		.mr2 = {
			.read_latency = rd_lat,
		},
		.mr3 = {
			.write_recovery_for_auto_precharge =
				cfg->csr_base[0]->mc_base5_cfg_wr.cfg_wr,
		},
		.mr4 = {
			.activate_to_precharge =
				cfg->csr_base[0]->mc_base5_cfg_ras.cfg_ras,
		},
		.mr5 = {
			.read_to_auto_precharge =
				cfg->csr_base[0]->mc_base5_cfg_rtp.cfg_rtp,
			.rsvd0 = 0,
		},
		.mr6 = {
			.pull_down_driver_strength =
				cfg->csr_base[0]->mc_base5_cfg_ds.cfg_ds & 0x7,
			.pull_up_driver_strength =
				(cfg->csr_base[0]->mc_base5_cfg_ds.cfg_ds >> 3) & 0x7,
			.rsvd0 = 0,
		},
		.mr7 = {
			.dword_loopback = 0,
			.dword_read_mux_control = 0,
			.rsvd0 = 0,
			.dword_misr_control = 0,
			.rsvd1 = 0,
			.cattrip = 0,
		},
		.mr8 = {
			.da_port_lockout = 1,
			.duty_cycle_monitor = 0,
			.ecs_error_log_auto_reset = 0,
			.wdqs_to_ck_training = 0,
			.rfm_levels = 0,
			.rsvd0 = 0,
		},
		.mr9 = {
			.meta_data = 0,
			.severity_reporting = 0,
			.error_vector_input_mode = 0,
			.error_vector_pattern = 0,
			.auto_ecs_via_refab = 0,
			.auto_ecs_during_self_refresh = 0,
			.ecs_multi_bit_error_correction = 0,
			.ecs_error_type_address_reset = 0,
		},
		.mr10 = {
			.rsvd0 = 0,
		},
		.mr11 = {
			.dca_code_wdqs0 = 0,
			.dca_code_wdqs1 = 0,
		},
		.mr12 = {
			.rsvd0 = 0,
		},
		.mr13 = {
			.rsvd0 = 0,
		},
		.mr14 = {
			.rsvd0 = 0,
			.ref_volt_aword = ca_vref >> 1, /* VREFCA : 50% - default */
			.rsvd1 = 0,
		},
		.mr15 = {
			.rsvd0 = 0,
			.ref_volt_dword = dq_vref >> 1, /* VREFDQ : 50% - default */
			.rsvd1 = 0,
		},
	};

	/* MR0/1 */
	if (system_config.cfg_parity_dis) {
		mr.mr1.parity_latency = 0;
	} else {
		mr.mr0.read_parity = 1;
		mr.mr0.write_parity = 1;
		mr.mr0.ca_parity = 1;
	}

	/* MR8 */
	if (system_config.cfg_en_rfm)
		mr.mr8.rfm_levels = 1;

	/* MR9 */
	if (system_config.cfg_ecs_on) {
		mr.mr9.meta_data = 1;
		mr.mr9.auto_ecs_via_refab = 1;
		mr.mr9.auto_ecs_during_self_refresh = 1;
		mr.mr9.ecs_multi_bit_error_correction = 1;
		mr.mr9.ecs_error_type_address_reset = 1;
	} else if (!system_config.cfg_dis_ecc) {
		mr.mr9.meta_data = 1;
	}

	if (!system_config.cfg_dis_on_die_ecc)
		mr.mr9.severity_reporting = 1;

	icon_mrs_ch(cfg, CH_ALL, mr.mrs);

	return 0;
}

uint32_t set_mbist_tmrs(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* MBIST TMRS code for HBM3E */
	tmrs_write(cfg, 0x3E001000); // 1 : Safety
	tmrs_write(cfg, 0x20000B50); // 2 : B-die TMRS lock
	tmrs_write(cfg, 0x20000160); // 3
	tmrs_write(cfg, 0x20000240); // 4
	tmrs_write(cfg, 0x20000500); // 5
	tmrs_write(cfg, 0x1E000B43); // 6
	tmrs_write(cfg, 0x1E000848); // 7
	tmrs_write(cfg, 0x20000021); // 8
	tmrs_write(cfg, 0x2000023B); // 9
	tmrs_write(cfg, 0x20000031); // 10
	tmrs_write(cfg, 0x20000000); // 11

	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t icon_hbm_mbist(struct hbm3_config *cfg)
{
	uint32_t i = 0;

	// March sid all
	uint32_t march_vector[ICON_MBIST_WDR_IDX] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00001008, 0x1F0FBA46, 0x00017FFC,
		0x00000000, 0x00000190, 0x20384000, 0x80E4C070,
		0x00000002, 0x00000190, 0x00000000, 0x00001000,
		0x1F0FBA46, 0x00017FFC, 0x00000000, 0x00000190,
		0x00000000, 0x85980000, 0x00000002, 0x00000190,
		0x60386000, 0x80E4C070, 0x00000002, 0x00000190,
		0x00000000, 0x7B918000, 0xDF36A000, 0x7C91BE6D,
		0x1F090000, 0x7C243E12, 0x00000000, 0x800B8000,
		0x00000000, 0x800D0000, 0xA0046000, 0x800A4008,
		0x00000000, 0x80900000, 0x20F44000, 0x83CBC1E7,
		0x00001000, 0x00000000, 0x00000002, 0x00000190,
		0x00001C06, 0x00230000, 0x4F052400, 0x00502732,
		0x5A08C32A, 0x38A94990, 0x00000002, 0x00000000,
		0x00000000, 0x500C0500, 0x8C0300C0, 0x6318C631,
		0x0102200C, 0x40208C04, 0xD011885B
		// SID0, SID1, SID2, SID ALL
		// 0xC011885B, 0xC411885B, 0xC811885B, 0xD011885B
	};
	// SCAN sid all
	uint32_t scan_vector[ICON_MBIST_WDR_IDX] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000688, 0x1F0FBA46, 0x00017FFC,
		0x00000000, 0x00000190, 0x20384000, 0x80E4C070,
		0x00000002, 0x00000190, 0x00000000, 0x00000680,
		0x1F0FBA46, 0x00017FFC, 0x00000000, 0x00000190,
		0x00000000, 0x85980000, 0x00000002, 0x00000190,
		0x60386000, 0x80E4C070, 0x00000002, 0x00000190,
		0x00000000, 0x7B918000, 0xDF36A000, 0x7C91BE6D,
		0x1F090000, 0x7C243E12, 0x00000000, 0x800B8000,
		0x00000000, 0x800D0000, 0xA0046000, 0x800A4008,
		0x00000000, 0x80900000, 0x20F44000, 0x83CBC1E7,
		0x00001000, 0x00000000, 0x00000002, 0x00000190,
		0x00001C06, 0x00230000, 0x4F052400, 0x00502732,
		0x5A08C32A, 0x38A94990, 0x00000002, 0x00000000,
		0x00000000, 0x600C0600, 0x8C0300C0, 0x6318C631,
		0x0102200C, 0x40208C04, 0xD011885B
		// SID0, SID1, SID2, SID ALL
		// 0xC011885B, 0xC411885B, 0xC811885B, 0xD011885B
	};

	set_mbist_tmrs(cfg);

	icon_mbist_wir(cfg);

	icon_mbist_wdr(cfg, march_vector);

	for (i = 0; i < 7; i++) {
		mdelay(5 * 1000);
		NOTICE("waiting result = %d sec\n", (i + 1) * 5);
	}

	NOTICE("MBIST March Result\n");
	icon_mbist_result(cfg);

	icon_mbist_wdr(cfg, scan_vector);

	for (i = 0; i < 7; i++) {
		mdelay(5 * 1000);
		NOTICE("waiting result = %d sec\n", (i + 1) * 5);
	}

	NOTICE("MBIST Scan Result\n");
	icon_mbist_result(cfg);

	return 1; /* MBIST for debugging, not normal operation */
}

uint8_t get_read_latency(uint8_t datarate)
{
	uint32_t ck_freq = get_clock_frequency(datarate);

	if (ck_freq == 0) {
		ERROR("Invalid datarate\n");
		return 0;
	}

	return SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq);
}

uint8_t get_write_latency(uint8_t datarate)
{
	uint32_t ck_freq = get_clock_frequency(datarate);

	if (ck_freq == 0) {
		ERROR("Invalid datarate\n");
		return 0;
	}

	return SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq);
}

void enable_memory_dbi(struct hbm3_config *cfg, uint8_t ch, bool en)
{
	union hbm3_mr0_t mr0;

	mr0.val = 0;

	if (en) {
		mr0.read_dbi = 1;
		mr0.write_dbi = 1;
	} else {
		mr0.read_dbi = 0;
		mr0.write_dbi = 0;
	}

	mr0.tcsr = 1;

	if (!system_config.cfg_parity_dis) {
		mr0.read_parity = 1;
		mr0.write_parity = 1;
		mr0.ca_parity = 1;
	}

	mrw_phy_direct_cmd(cfg, ch, MR0, mr0.val);
}

uint32_t tmrs_c_die_kill_code(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* TODO : add TMRS code for HBM3E */
	INFO("tmrs c die_kill\n");
	tmrs_write(cfg, 0x3E001000); // Safety Code

	/* Kill Code */
	tmrs_write(cfg, 0x1E000322); // TMRS_PSDR_PRE
	tmrs_write(cfg, 0x1E000006); // TMRS_ADD_TSV_OFF_CDIE

	tmrs_write(cfg, 0x20000B50); // B die TMRS lock
	tmrs_write(cfg, 0x1E000B43); // C die TMRS lock

	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t tmrs_b_die_kill_code(struct hbm3_config *cfg)
{

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* TODO : add TMRS code for HBM3E */
	INFO("tmrs b die_kill\n");
	tmrs_write(cfg, 0x3E001000); // Safety Code

	tmrs_write(cfg, 0x20000210); // TMRS_ADD_TSV_OFF
	tmrs_write(cfg, 0x20000322); // TMRS_PSDR_TSV

	tmrs_write(cfg, 0x20000B50); // B die TMRS lock
	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t tmrs_rev0_errata_wa(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* TODO : add TMRS code for HBM3E */
	tmrs_write(cfg, 0x3E001000); // Safety Code
	tmrs_write(cfg, 0x20000B50); // B die TMRS lock
	tmrs_write(cfg, 0x1E000B43); // C die TMRS lock

	tmrs_write(cfg, 0x20000C50); // Read C2C

	// DCM output Low
	tmrs_write(cfg, 0x20000021);
	tmrs_write(cfg, 0x20000C44);
	tmrs_write(cfg, 0x20000000);

	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;

	return 0;
}

uint32_t tmrs_default_set(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* TODO : add TMRS code for HBM3E */
	tmrs_write(cfg, 0x3E001000); // Safety Code

	tmrs_write(cfg, 0x20000B50); // B die TMRS lock
	tmrs_write(cfg, 0x1E000B43); // C die TMRS lock
	tmrs_write(cfg, 0x20000528); // LDO
	tmrs_write(cfg, 0x1E000870); // C die read local sensing margin
	tmrs_write(cfg, 0x1E000A70); // C die read local sensing margin
	tmrs_write(cfg, 0x20000190); // AW CMD centering

	// FRP LVDD margin improvement
	tmrs_write(cfg, 0x1E00056A);
	tmrs_write(cfg, 0x1E0005CB);
	tmrs_write(cfg, 0x1E00066A);
	tmrs_write(cfg, 0x1E0006CB);
	if ((HBM_DATA_RATE == 9600 || HBM_DATA_RATE == 9200) && GET_REVISION == REVISION_EVT1) {
		printf("Applied TMRS for 9.2 Gbps and 9.6 Gbps\n");
		tmrs_write(cfg, 0x1E000227);
		tmrs_write(cfg, 0x1E000327);
		tmrs_write(cfg, 0x1E000427);
		tmrs_write(cfg, 0x1E000007);
	}

	// IOSA 4g, FRPF +4g, FRP +8g
	tmrs_write(cfg, 0x1E000256);
	tmrs_write(cfg, 0x1E000456);
	tmrs_write(cfg, 0x1E000717);
	tmrs_write(cfg, 0x1E00041A);
	tmrs_write(cfg, 0x1E00061A);

	tmrs_write(cfg, 0x1E000419); // REFOSCpb period up
	tmrs_write(cfg, 0x08000506); // SID2 * CRCK delay dn

	// PDL (-4g)
	tmrs_write(cfg, 0x1E000666);
	tmrs_write(cfg, 0x1E000766);
	tmrs_write(cfg, 0x1E000A66);
	tmrs_write(cfg, 0x1E000B66);

	// Replica aligner +4g
	tmrs_write(cfg, 0x1E000C4A);
	tmrs_write(cfg, 0x1E000C5A);

	// tmrs_b_die_kill_code(cfg);
	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t set_tmrs(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	udelay(1 * 10);
	cfg->sysreg_base->icon_wrstn.rst_ctrl = 0x1;
	udelay(1 * 10);

	tmrs_default_set(cfg);

	udelay(1 * 10);

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;

	return 0;
}

static union phy_vwm *phy_acquire_vwm_buf(void)
{
	memset(&vwm_buf, 0, sizeof(vwm_buf));
	return &vwm_buf;
}

#if !ZEBU
static union phy_vwm *phy_acquire_max_vwm_buf(void)
{
	memset(&max_vwm_buf, 0, sizeof(max_vwm_buf));
	return &max_vwm_buf;
}

static union phy_offset *phy_acquire_max_offset_buf(void)
{
	memset(&max_offset_buf, 0, sizeof(max_offset_buf));
	return &max_offset_buf;
}
#endif /* !ZEBU */

#if !ZEBU
static int32_t phy_find_read_training_fail_bit(struct hbm3_config *cfg, uint32_t chiplet_id, uint8_t ch)
{
	int32_t count = 0;
	uint32_t val;

	val = cfg->phy_base[ch]->rd_cal_fail_stat0.read_dq_fail_status0;
	if (val) {
		for (int i = 0; i < 32; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dq_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][dq_lane[i].dword_group] != dq_lane[i].repair_pos) {
					if (val == 0xFFFFFFFF)
						ERROR("Unrepairable HBM%d_CH_%d_DWORD0_ALL (fail_status: 0x%x)\n", chiplet_id, ch, val);
					else
						ERROR("Unrepairable HBM%d_CH_%d_DQ%d (fail_status: 0x%x repair_pos: 0x%x)\n",
							  chiplet_id, ch, i, val, ch_rep_lane[ch][dq_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dq_lane[i].dword_group] = dq_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_dbi_fail_status0;
	if (val) {
		for (int i = 0; i < 4; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dbi_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][dbi_lane[i].dword_group] != dbi_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_DBI%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][dbi_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dbi_lane[i].dword_group] = dbi_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_ecc_fail_status0;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][ecc_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][ecc_lane[i].dword_group] != ecc_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_ECC%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][ecc_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][ecc_lane[i].dword_group] = ecc_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_sev_fail_status0;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][sev_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][sev_lane[i].dword_group] != sev_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_SEV%d\n (fail_status: 0x%x repair_pos: 0x%x)",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][sev_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][sev_lane[i].dword_group] = sev_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat1.read_dq_fail_status1;
	if (val) {
		for (int i = 0; i < 32; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] != dq_lane[i].repair_pos) {
					if (val == 0xFFFFFFFF)
						ERROR("Unrepairable HBM%d_CH_%d_DWORD1_ALL (fail_status: 0x%x)\n", chiplet_id, ch, val);
					else
						ERROR("Unrepairable HBM%d_CH_%d_DQ%d (fail_status: 0x%x repair_pos: 0x%x)\n",
							  chiplet_id, ch, i + 32, val, ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] = dq_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_dbi_fail_status1;
	if (val) {
		for (int i = 0; i < 4; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] != dbi_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_DBI%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch,  + 4, val, ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] = dbi_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_ecc_fail_status1;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] != ecc_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_ECC%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i + 2, val, ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] = ecc_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->rd_cal_fail_stat2.read_sev_fail_status1;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] != sev_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_SEV%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i + 2, val, ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] = sev_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	if (count) {
		rep_status[ch] += count;
		return HBM_NEED_REPAIR;
	}

	return HBM_OK;
}

static int32_t phy_find_write_training_fail_bit(struct hbm3_config *cfg, uint32_t chiplet_id, uint8_t ch)
{
	int32_t count = 0;
	uint32_t val;

	val = cfg->phy_base[ch]->wr_cal_fail_stat0.write_dq_fail_status0;
	if (val) {
		for (int i = 0; i < 32; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dq_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][dq_lane[i].dword_group] != dq_lane[i].repair_pos) {
					if (val == 0xFFFFFFFF)
						ERROR("Unrepairable HBM%d_CH_%d_DWORD0_ALL (fail_status: 0x%x)\n", chiplet_id, ch, val);
					else
						ERROR("Unrepairable HBM%d_CH_%d_DQ%d (fail_status: 0x%x repair_pos: 0x%x)\n",
							  chiplet_id, ch, i, val, ch_rep_lane[ch][dq_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dq_lane[i].dword_group] = dq_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_dbi_fail_status0;
	if (val) {
		for (int i = 0; i < 4; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dbi_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][dbi_lane[i].dword_group] != dbi_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_DBI%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][dbi_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dbi_lane[i].dword_group] = dbi_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_ecc_fail_status0;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][ecc_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][ecc_lane[i].dword_group] != ecc_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_ECC%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][ecc_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][ecc_lane[i].dword_group] = ecc_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_sev_fail_status0;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][sev_lane[i].dword_group] != 0xF &&
					ch_rep_lane[ch][sev_lane[i].dword_group] != sev_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_SEV%d\n (fail_status: 0x%x repair_pos: 0x%x)",
						  chiplet_id, ch, i, val, ch_rep_lane[ch][sev_lane[i].dword_group]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][sev_lane[i].dword_group] = sev_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat1.write_dq_fail_status1;
	if (val) {
		for (int i = 0; i < 32; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] != dq_lane[i].repair_pos) {
					if (val == 0xFFFFFFFF)
						ERROR("Unrepairable HBM%d_CH_%d_DWORD1_ALL (fail_status: 0x%x)\n", chiplet_id, i, val);
					else
						ERROR("Unrepairable HBM%d_CH_%d_DQ%d (fail_status: 0x%x repair_pos: 0x%x)\n",
							  chiplet_id, ch, i + 32, val, ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dq_lane[i].dword_group + DWORD1_BYTE0] = dq_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_dbi_fail_status1;
	if (val) {
		for (int i = 0; i < 4; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] != dbi_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_DBI%d  (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i + 4, val, ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][dbi_lane[i].dword_group + DWORD1_BYTE0] = dbi_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_ecc_fail_status1;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] != ecc_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_ECC%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i + 2, val, ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][ecc_lane[i].dword_group + DWORD1_BYTE0] = ecc_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	val = cfg->phy_base[ch]->wr_cal_fail_stat2.write_sev_fail_status1;
	if (val) {
		for (int i = 0; i < 2; i++) {
			uint32_t fail_bit = (val >> i) & 0x1;

			if (fail_bit) {
				if (ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] != 0xF &&
					ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] != sev_lane[i].repair_pos) {
					ERROR("Unrepairable HBM%d_CH_%d_SEV%d (fail_status: 0x%x repair_pos: 0x%x)\n",
						  chiplet_id, ch, i + 2, val, ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0]);
					return HBM_UNREPAIRABLE;
				} else {
					ch_rep_lane[ch][sev_lane[i].dword_group + DWORD1_BYTE0] = sev_lane[i].repair_pos;
					count++;
				}
			}
		}
	}

	if (count) {
		rep_status[ch] += count;
		return HBM_NEED_REPAIR;
	}

	return HBM_OK;
}
#endif /* !ZEBU */

uint32_t phy_read_training_fail_check(struct hbm3_config *cfg, uint8_t ch,
									  uint32_t *fail_stat_dword0, uint32_t *fail_stat_dword1)
{
	*fail_stat_dword0 = 0;
	*fail_stat_dword1 = 0;

	if (cfg->phy_base[ch]->rd_cal_fail_stat0.read_dq_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 0;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_dbi_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 1;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_ecc_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 2;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_sev_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 3;

	if (cfg->phy_base[ch]->rd_cal_fail_stat1.read_dq_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 0;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_dbi_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 1;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_ecc_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 2;
	if (cfg->phy_base[ch]->rd_cal_fail_stat2.read_sev_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 3;

	return 0;
}

uint32_t phy_write_training_fail_check(struct hbm3_config *cfg, uint8_t ch,
									   uint32_t *fail_stat_dword0, uint32_t *fail_stat_dword1)
{
	*fail_stat_dword0 = 0;
	*fail_stat_dword1 = 0;

	if (cfg->phy_base[ch]->wr_cal_fail_stat0.write_dq_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 0;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_dbi_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 1;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_ecc_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 2;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_sev_fail_status0 != 0)
		*fail_stat_dword0 |= 1 << 3;

	if (cfg->phy_base[ch]->wr_cal_fail_stat1.write_dq_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 0;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_dbi_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 1;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_ecc_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 2;
	if (cfg->phy_base[ch]->wr_cal_fail_stat2.write_sev_fail_status1 != 0)
		*fail_stat_dword1 |= 1 << 3;

	return 0;
}

uint32_t phy_find_min_result(struct hbm3_config *cfg, uint8_t ch, union phy_vwm *vwm,
							 uint16_t *min_dword0, uint16_t *min_dword1)
{
	uint32_t dword, i;
	uint16_t min_dword;

	for (dword = 0; dword < DWORD_NUM; dword++) {
		min_dword = 0xFFFF;

		if (dword == 0 && !min_dword0) {
			continue;
		}

		if (dword == 1 && !min_dword1) {
			continue;
		}

		for (i = 0; i < PCH_DQ_WIDTH; i++) {
			if (min_dword > vwm->dq[dword * PCH_DQ_WIDTH + i]) {
				min_dword = vwm->dq[dword * PCH_DQ_WIDTH + i];
			}
		}
		if (!system_config.cfg_dis_ecc) {
			for (i = 0; i < PCH_ECC_WIDTH; i++) {
				if (min_dword > vwm->ecc[dword * PCH_ECC_WIDTH + i]) {
					min_dword = vwm->ecc[dword * PCH_ECC_WIDTH + i];
				}
			}
		}
		if (!system_config.cfg_dis_on_die_ecc) {
			for (i = 0; i < PCH_SEV_WIDTH; i++) {
				if (min_dword > vwm->sev[dword * PCH_SEV_WIDTH + i]) {
					min_dword = vwm->sev[dword * PCH_SEV_WIDTH + i];
				}
			}
		}
		for (i = 0; i < PCH_DBI_WIDTH; i++) {
			if (min_dword > vwm->dbi[dword * PCH_DBI_WIDTH + i]) {
				min_dword = vwm->dbi[dword * PCH_DBI_WIDTH + i];
			}
		}

		if (dword == 0) {
			*min_dword0 = min_dword;
		} else {
			*min_dword1 = min_dword;
		}
	}

	return 0;
}

uint32_t phy_get_training_result(struct hbm3_config *cfg, uint8_t ch, union phy_vwm *vwm)
{
	union hbm3ephy_vwm_dq0_stat vwm_dq_stat;
	union hbm3ephy_vwm_ecc0_stat vwm_ecc_stat;
	union hbm3ephy_vwm_sev0_stat vwm_sev_stat;
	union hbm3ephy_vwm_dbi0_stat vwm_dbi_stat;
	uint32_t dword, pch_width;
	uint64_t phy_addr = (uint64_t)cfg->phy_base[ch];

	for (dword = 0; dword < DWORD_NUM; dword++) {
		cfg->phy_base[ch]->dword_select.bsel = dword;

		for (pch_width = 0; pch_width < PCH_DQ_WIDTH; pch_width++) {
			vwm_dq_stat.val = RD_VWM_DQ_STAT(phy_addr, pch_width);
			vwm->dq[dword * PCH_DQ_WIDTH + pch_width] =
				vwm_dq_stat.dq0_vwmr - vwm_dq_stat.dq0_vwmc;
		}

		if (!system_config.cfg_dis_ecc) {
			for (pch_width = 0; pch_width < PCH_ECC_WIDTH; pch_width++) {
				vwm_ecc_stat.val = RD_VWM_ECC_STAT(phy_addr, pch_width);
				vwm->ecc[dword * PCH_ECC_WIDTH + pch_width] =
					vwm_ecc_stat.ecc0_vwmr - vwm_ecc_stat.ecc0_vwmc;
			}
		} else {
			for (pch_width = 0; pch_width < PCH_ECC_WIDTH; pch_width++) {
				vwm->ecc[dword * PCH_ECC_WIDTH + pch_width] = 0xffff;
			}
		}
		if (!system_config.cfg_dis_on_die_ecc) {
			for (pch_width = 0; pch_width < PCH_SEV_WIDTH; pch_width++) {
				vwm_sev_stat.val = RD_VWM_SEV_STAT(phy_addr, pch_width);
				vwm->sev[dword * PCH_SEV_WIDTH + pch_width] =
					vwm_sev_stat.sev0_vwmr - vwm_sev_stat.sev0_vwmc;
			}
		} else {
			for (pch_width = 0; pch_width < PCH_SEV_WIDTH; pch_width++) {
				vwm->sev[dword * PCH_SEV_WIDTH + pch_width] = 0xffff;
			}
		}
		if (!system_config.cfg_dbi_off) {
			for (pch_width = 0; pch_width < PCH_DBI_WIDTH; pch_width++) {
				vwm_dbi_stat.val = RD_VWM_DBI_STAT(phy_addr, pch_width);
				vwm->dbi[dword * PCH_DBI_WIDTH + pch_width] =
					vwm_dbi_stat.dbi0_vwmr - vwm_dbi_stat.dbi0_vwmc;
			}
		} else {
			for (pch_width = 0; pch_width < PCH_DBI_WIDTH; pch_width++) {
				vwm->dbi[dword * PCH_DBI_WIDTH + pch_width] = 0xffff;
			}
		}
	}

	return 0;
}

void phy_update_ca_ra_deskew(struct hbm3_config *cfg, uint8_t ch, uint32_t *ca_deskew,
							 uint32_t *ra_deskew, uint32_t arfu_deskew)
{
	cfg->phy_base[ch]->sw_cmd_deskewc_code0.sw_ca0deskewcode = ca_deskew[0];
	cfg->phy_base[ch]->sw_cmd_deskewc_code0.sw_ca1deskewcode = ca_deskew[1];

	cfg->phy_base[ch]->sw_cmd_deskewc_code1.sw_ca2deskewcode = ca_deskew[2];
	cfg->phy_base[ch]->sw_cmd_deskewc_code1.sw_ca3deskewcode = ca_deskew[3];

	cfg->phy_base[ch]->sw_cmd_deskewc_code2.sw_ca4deskewcode = ca_deskew[4];
	cfg->phy_base[ch]->sw_cmd_deskewc_code2.sw_ca5deskewcode = ca_deskew[5];

	cfg->phy_base[ch]->sw_cmd_deskewc_code3.sw_ca6deskewcode = ca_deskew[6];
	cfg->phy_base[ch]->sw_cmd_deskewc_code3.sw_ca7deskewcode = ca_deskew[7];

	cfg->phy_base[ch]->sw_cmd_deskewc_code5.sw_ra0deskewcode = ra_deskew[0];
	cfg->phy_base[ch]->sw_cmd_deskewc_code5.sw_ra1deskewcode = ra_deskew[1];

	cfg->phy_base[ch]->sw_cmd_deskewc_code6.sw_ra2deskewcode = ra_deskew[2];
	cfg->phy_base[ch]->sw_cmd_deskewc_code6.sw_ra3deskewcode = ra_deskew[3];

	cfg->phy_base[ch]->sw_cmd_deskewc_code7.sw_ra4deskewcode = ra_deskew[4];
	cfg->phy_base[ch]->sw_cmd_deskewc_code7.sw_ra5deskewcode = ra_deskew[5];

	cfg->phy_base[ch]->sw_cmd_deskewc_code8.sw_ra6deskewcode = ra_deskew[6];
	cfg->phy_base[ch]->sw_cmd_deskewc_code8.sw_ra7deskewcode = ra_deskew[7];

	cfg->phy_base[ch]->sw_cmd_deskewc_code9.sw_ra8deskewcode = ra_deskew[8];
	cfg->phy_base[ch]->sw_cmd_deskewc_code9.sw_ra9deskewcode = ra_deskew[9];

	cfg->phy_base[ch]->sw_cmd_deskewc_code10.sw_arfudeskewcode = arfu_deskew;
}

void phy_search_ca_ra_deskew(struct hbm3_config *cfg, uint8_t ch, uint32_t code)
{
	cfg->phy_base[ch]->sw_cmd_deskewc_code0.sw_ca0deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code0.sw_ca1deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code1.sw_ca2deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code1.sw_ca3deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code2.sw_ca4deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code2.sw_ca5deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code3.sw_ca6deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code3.sw_ca7deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code5.sw_ra0deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code5.sw_ra1deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code6.sw_ra2deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code6.sw_ra3deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code7.sw_ra4deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code7.sw_ra5deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code8.sw_ra6deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code8.sw_ra7deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code9.sw_ra8deskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code9.sw_ra9deskewcode = code;

	cfg->phy_base[ch]->sw_cmd_deskewc_code10.sw_apardeskewcode = code;
	cfg->phy_base[ch]->sw_cmd_deskewc_code10.sw_arfudeskewcode = code;
}

int32_t phy_read_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t fail_stat_dword0, fail_stat_dword1;

	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

	cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = HBM3_INIT_OFFSET_DQ;
	phy_do_training(cfg, ch);
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

	phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);

	if ((fail_stat_dword0 != 0 || fail_stat_dword1 != 0)) {
		ERROR("CH[%d] Read Training Fail, %s%s\n",
			  ch, fail_stat_dword0 ? "DWORD0 " : "", fail_stat_dword1 ? "DWORD1 " : "");
		return HBM_READ_TRAIN_FAIL;
	}

	return 0;
}

int32_t phy_write_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t fail_stat_dword0, fail_stat_dword1;

	// sev for read-only
	cfg->phy_base[ch]->cal_con3.wrtrn_sev_cal_en = 0x0;

	cfg->phy_base[ch]->cal_con3.num_repeat = 0x1;
	cfg->phy_base[ch]->cal_con3.wrtrn_cyc_en = 0x1;
	cfg->phy_base[ch]->cal_con3.wrtrn_cyc_th = 0x1F;

	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x1;
	phy_do_training(cfg, ch);
	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x0;

	phy_write_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);

	if ((fail_stat_dword0 != 0 || fail_stat_dword1 != 0)) {
		ERROR("CH[%d] Write Training Fail, %s%s\n",
			  ch, fail_stat_dword0 ? "DWORD0 " : "", fail_stat_dword1 ? "DWORD1 " : "");
		return HBM_WRITE_TRAIN_FAIL;
	}

	return 0;
}

uint32_t phy_read_parity_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t fail_stat_dword0, fail_stat_dword1;

	cfg->phy_base[ch]->cal_con4.phy_rdtrn_par_en = 0x1;
	phy_do_training(cfg, ch);
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_par_en = 0x0;

	fail_stat_dword0 = cfg->phy_base[ch]->rd_cal_fail_stat2.read_par_fail_status0;
	fail_stat_dword1 = cfg->phy_base[ch]->rd_cal_fail_stat2.read_par_fail_status1;

	if (fail_stat_dword0 | fail_stat_dword1) {
		ERROR("CH[%d] Read Parity Training Fail, DWORD0 = 0x%08x, DWORD1 = 0x%08x\n",
			  ch, fail_stat_dword0, fail_stat_dword1);
		return 1;
	}

	return 0;
}

void phy_read_training_LFSR_seed(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t wdr = 0xAAAAAAAA;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	// Set WR_WDR0~9 to intended seeds for training
	cfg->icon_base->wr_wdr0.wr_wdr0 = wdr;
	cfg->icon_base->wr_wdr1.wr_wdr1 = wdr;
	cfg->icon_base->wr_wdr2.wr_wdr2 = wdr;
	cfg->icon_base->wr_wdr3.wr_wdr3 = wdr;
	cfg->icon_base->wr_wdr4.wr_wdr4 = wdr;
	cfg->icon_base->wr_wdr5.wr_wdr5 = wdr;
	cfg->icon_base->wr_wdr6.wr_wdr6 = wdr;
	cfg->icon_base->wr_wdr7.wr_wdr7 = wdr;
	cfg->icon_base->wr_wdr8.wr_wdr8 = wdr;
	cfg->icon_base->wr_wdr9.wr_wdr9 = wdr;

	cfg->icon_base->test_instruction_req0.dword_misr_mode_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_mode_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_write_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_write_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	// Set CAL_SEED_CON*
	cfg->phy_base[ch]->cal_seed_con0.seed0_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con1.seed1_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con2.seed2_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con3.seed3_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con4.seed4_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con5.seed5_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con6.seed6_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con7.seed7_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con8.seed8_apb = wdr;
	cfg->phy_base[ch]->cal_seed_con9.seed9_apb = wdr;

	cfg->phy_base[ch]->cal_con0.rdtrn_lfsr_mode_en = 0x1;
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
}

int32_t phy_read_training_LFSR(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t fail_stat_dword0, fail_stat_dword1;

	phy_read_training_LFSR_seed(cfg, ch);

	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;
	cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = HBM3_INIT_OFFSET_DQ;
	cfg->phy_base[ch]->cal_con3.num_repeat = 0x6;

	phy_do_training(cfg, ch);
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

	phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);

	cfg->phy_base[ch]->cal_con0.rdtrn_lfsr_mode_en = 0x0;

	if ((fail_stat_dword0 != 0 || fail_stat_dword1 != 0)) {
		ERROR("CH[%d] Read Training LFSR Fail, DWORD0 = 0x%08x, DWORD1 = 0x%08x\n",
			  ch, fail_stat_dword0, fail_stat_dword1);
		return HBM_READ_TRAIN_FAIL;
	}

	return 0;
}

void phy_write_training_LFSR_seed(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t wdr = 0xAAAAAAAA;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	// Set WR_WDR0~9 to intended seeds for training
	cfg->icon_base->wr_wdr0.wr_wdr0 = wdr;
	cfg->icon_base->wr_wdr1.wr_wdr1 = wdr;
	cfg->icon_base->wr_wdr2.wr_wdr2 = wdr;
	cfg->icon_base->wr_wdr3.wr_wdr3 = wdr;
	cfg->icon_base->wr_wdr4.wr_wdr4 = wdr;
	cfg->icon_base->wr_wdr5.wr_wdr5 = wdr;
	cfg->icon_base->wr_wdr6.wr_wdr6 = wdr;
	cfg->icon_base->wr_wdr7.wr_wdr7 = wdr;
	cfg->icon_base->wr_wdr8.wr_wdr8 = wdr;
	cfg->icon_base->wr_wdr9.wr_wdr9 = wdr;

	cfg->icon_base->test_instruction_req0.dword_misr_mode_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_mode_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_write_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.dword_misr_write_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	// Set CAL_WR_PATTERN_CON*
	cfg->phy_base[ch]->cal_wr_pattern_con0.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con1.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con2.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con3.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con4.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con5.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con6.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con7.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con8.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con9.val = 0x08080808;
	cfg->phy_base[ch]->cal_wr_pattern_con10.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con11.val = 0x10101010;
	cfg->phy_base[ch]->cal_wr_pattern_con12.val = 0x08080808;
	cfg->phy_base[ch]->cal_wr_pattern_con13.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con14.val = 0x08080808;
	cfg->phy_base[ch]->cal_wr_pattern_con15.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con16.val = 0xCC33CC33;
	cfg->phy_base[ch]->cal_wr_pattern_con17.val = 0xCC33CC33;
	cfg->phy_base[ch]->cal_wr_pattern_con18.val = 0xF0F00F0F;
	cfg->phy_base[ch]->cal_wr_pattern_con19.val = 0x00F0000F;

	cfg->phy_base[ch]->cal_con0.wrtrn_lfsr_mode_en = 0x1;
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;
}

int32_t phy_write_training_LFSR(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t fail_stat_dword0, fail_stat_dword1;

	// sev for read-only
	cfg->phy_base[ch]->cal_con3.wrtrn_sev_cal_en = 0x0;

	cfg->phy_base[ch]->cal_con3.num_repeat = 0x1;
	cfg->phy_base[ch]->cal_con3.wrtrn_cyc_en = 0x1;
	cfg->phy_base[ch]->cal_con3.wrtrn_cyc_th = 0x1F;	// 31

	phy_write_training_LFSR_seed(cfg, ch);

	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x1;
	phy_do_training(cfg, ch);
	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x0;

	cfg->phy_base[ch]->cal_con0.wrtrn_lfsr_mode_en = 0x0;

	phy_write_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);

	if ((fail_stat_dword0 != 0 || fail_stat_dword1 != 0)) {
		WARN("CH[%d] Write Training LFSR Fail, DWORD0 = 0x%08x, DWORD1 = 0x%08x\n",
			 ch, fail_stat_dword0, fail_stat_dword1);
		return HBM_WRITE_TRAIN_FAIL;
	}

	/* Restore the pattern to its reset value for normal write training */
	cfg->phy_base[ch]->cal_wr_pattern_con0.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con1.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con2.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con3.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con4.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con5.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con6.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con7.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con8.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con9.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con10.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con11.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con12.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con13.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con14.val = 0xFFFFFFFF;
	cfg->phy_base[ch]->cal_wr_pattern_con15.val = 0x0;
	cfg->phy_base[ch]->cal_wr_pattern_con16.val = 0x33333333;
	cfg->phy_base[ch]->cal_wr_pattern_con17.val = 0x33333333;
	cfg->phy_base[ch]->cal_wr_pattern_con18.val = 0x0F0F0F0F;
	cfg->phy_base[ch]->cal_wr_pattern_con19.val = 0x0F0F0F0F;

	return 0;
}

#define VREF_STEP 1
#define VREF_FROM 0

uint32_t phy_vwm_sum_margin(uint32_t *vwm)
{
	int vwm_idx;
	uint32_t output = 0;

	for (vwm_idx = 0; vwm_idx < VREF_REF_NUM; vwm_idx++)
		output += vwm[vwm_idx];

	return output;
}

void phy_vwm_shitf_window(uint32_t *vwm)
{
	uint32_t vwm_idx;

	for (vwm_idx = 1; vwm_idx < VREF_REF_NUM; vwm_idx++)
		vwm[vwm_idx - 1] = vwm[vwm_idx];
}

int32_t phy_write_vref_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t vref;
	uint32_t fail_stat_dword0 = 0, fail_stat_dword1 = 0;
	uint16_t optimal_vref_dword0 = 0, optimal_vref_dword1 = 0;
	uint32_t vref_dword0_max_sum = 0;
	uint32_t vref_dword1_max_sum = 0;
	uint16_t optimal_vref = 0;
	uint32_t vwm_vref_dword0[VREF_REF_NUM] = {0, };
	uint32_t vwm_vref_dword1[VREF_REF_NUM] = {0, };
	uint16_t dword0_min_result = 0;
	uint16_t dword1_min_result = 0;
	uint16_t vwm_vref_dword_idx = 0;
	uint16_t vwm_sum_vref_dword0 = 0, vwm_sum_vref_dword1 = 0;
	uint16_t max_vwm_sum_vref_dword0 = 0, max_vwm_sum_vref_dword1 = 0;
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x1;

	for (vref = VREF_FROM; vref < VREF_MAX; vref += VREF_STEP) {
		fail_stat_dword0 = 0;
		fail_stat_dword1 = 0;

		phy_set_write_vref(cfg, ch, vref);

		udelay(5);

		phy_do_training(cfg, ch);

		phy_write_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);
		phy_get_training_result(cfg, ch, vwm);

		if (fail_stat_dword0 == 0 || fail_stat_dword1 == 0)
			phy_find_min_result(cfg, ch, vwm, &dword0_min_result, &dword1_min_result);

		if (fail_stat_dword0 == 0)
			vwm_vref_dword0[vwm_vref_dword_idx] = dword0_min_result;
		else
			vwm_vref_dword0[vwm_vref_dword_idx] = 0;

		if (fail_stat_dword1 == 0)
			vwm_vref_dword1[vwm_vref_dword_idx] = dword1_min_result;
		else
			vwm_vref_dword1[vwm_vref_dword_idx] = 0;

		if (vwm_vref_dword_idx < VREF_REF_NUM - 1) {
			vwm_vref_dword_idx++;
		} else {
			vwm_sum_vref_dword0  = phy_vwm_sum_margin(vwm_vref_dword0);
			vwm_sum_vref_dword1  = phy_vwm_sum_margin(vwm_vref_dword1);

			if (max_vwm_sum_vref_dword0 < vwm_sum_vref_dword0) {
				max_vwm_sum_vref_dword0 = vwm_sum_vref_dword0;
				vref_dword0_max_sum = vref;
			}

			if (max_vwm_sum_vref_dword1 < vwm_sum_vref_dword1) {
				max_vwm_sum_vref_dword1 = vwm_sum_vref_dword1;
				vref_dword1_max_sum = vref;
			}

			phy_vwm_shitf_window(vwm_vref_dword0);
			phy_vwm_shitf_window(vwm_vref_dword1);
		}
	}

	optimal_vref_dword0 = vref_dword0_max_sum - (VREF_REF_NUM / 2);
	optimal_vref_dword1 = vref_dword1_max_sum - (VREF_REF_NUM / 2);
	optimal_vref = (optimal_vref_dword0 + optimal_vref_dword1) / 2;
	cfg->phy_base[ch]->cal_con4.phy_wrtrn_en = 0x0;

	phy_set_write_vref(cfg, ch, optimal_vref);
	INFO("CH[%d] write optimal vref dword = 0x%x\n", ch, optimal_vref);

	return 0;
}

#define MIN_OFFSET_MARGIN			0
#define GROUND_BOUNCE_OFFSET		5
#define GROUND_BOUNCE_THRESHOLD		16
int32_t phy_read_vref_training_LFSR_vertical(struct hbm3_config *cfg, uint8_t ch)
{
	const uint16_t SENTINEL_VALUE = 0xff;
	uint32_t vref;
	uint32_t dword0_fail_status = 0;
	uint32_t dword1_fail_status = 0;
	uint16_t final_vref_dword0 = 0;
	uint16_t final_vref_dword1 = 0;
	uint16_t dword0_min_result = 0;
	uint16_t dword1_min_result = 0;
	uint32_t dword0_min_margin[VREF_MAX + 1] = {0, };
	uint32_t dword1_min_margin[VREF_MAX + 1] = {0, };
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	uint16_t min_valid_voltage[2] = {SENTINEL_VALUE, SENTINEL_VALUE};
	uint16_t max_valid_voltage[2] = {0x0, 0x0};
	uint16_t final_offset[2] = {0, };

	for (vref = VREF_FROM; vref < VREF_MAX; vref += VREF_STEP) {
		dword0_fail_status = 0;
		dword1_fail_status = 0;

		phy_set_read_vref(cfg, ch, vref, vref);
		udelay(5);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;
		phy_do_training(cfg, ch);
		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

		phy_read_training_LFSR_seed(cfg, ch);
		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;
		cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = 0x34;
		cfg->phy_base[ch]->cal_con3.num_repeat = 0x6;
		phy_do_training(cfg, ch);
		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;
		cfg->phy_base[ch]->cal_con0.rdtrn_lfsr_mode_en = 0x0;

		phy_read_training_fail_check(cfg, ch, &dword0_fail_status, &dword1_fail_status);
		phy_get_training_result(cfg, ch, vwm);

		if (dword0_fail_status == 0 || dword1_fail_status == 0) {
			phy_find_min_result(cfg, ch, vwm, &dword0_min_result, &dword1_min_result);
		}

		if (dword0_fail_status == 0 && dword0_min_result > MIN_OFFSET_MARGIN) {
			if (min_valid_voltage[0] == 0xff) {
				min_valid_voltage[0] = vref;
			}
			max_valid_voltage[0] = vref;
			dword0_min_margin[vref] = dword0_min_result;
		}

		if (dword1_fail_status == 0 && dword1_min_result > MIN_OFFSET_MARGIN) {
			if (min_valid_voltage[1] == 0xff) {
				min_valid_voltage[1] = vref;
			}
			max_valid_voltage[1] = vref;
			dword1_min_margin[vref] = dword1_min_result;
		}
	}

	if (min_valid_voltage[0] == SENTINEL_VALUE || min_valid_voltage[1] == SENTINEL_VALUE) {
		printf("CH[%d] read optimal vref (vert) FAILED. No valid window found.\n", ch);

		uint16_t default_vref = (VREF_FROM + VREF_MAX) / 2;

		phy_set_read_vref(cfg, ch, default_vref, default_vref);

		return 1;
	}

	// if (min_valid_voltage[0] > GROUND_BOUNCE_THRESHOLD)
	// final_offset[0] = GROUND_BOUNCE_OFFSET;
	// if (min_valid_voltage[1] > GROUND_BOUNCE_THRESHOLD)
	// final_offset[1] = GROUND_BOUNCE_OFFSET;

	if (min_valid_voltage[0] > 0x14)
		final_offset[0] = 4;
	else if (min_valid_voltage[0] > 0x10)
		final_offset[0] = 3;
	else if (min_valid_voltage[0] > 0xA)
		final_offset[0] = 2;
	else if (min_valid_voltage[0] <= 0xA)
		final_offset[0] = 1;

	if (min_valid_voltage[1] > 0x14)
		final_offset[1] = 4;
	else if (min_valid_voltage[1] > 0x10)
		final_offset[1] = 3;
	else if (min_valid_voltage[1] > 0xA)
		final_offset[1] = 2;
	else if (min_valid_voltage[1] <= 0xA)
		final_offset[1] = 1;

	final_vref_dword0 = (min_valid_voltage[0] + max_valid_voltage[0]) / 2 + final_offset[0];
	final_vref_dword1 = (min_valid_voltage[1] + max_valid_voltage[1]) / 2 + final_offset[1];

	if (final_vref_dword0 > VREF_MAX) {
		printf("CH[%d] dword0 Vref CLAMPED! (Calculated: 0x%x -> Set: 0x%x)\n",
			   ch,
			   final_vref_dword0,
			   VREF_MAX);
		final_vref_dword0 = VREF_MAX;
	}

	if (final_vref_dword1 > VREF_MAX) {
		printf("CH[%d] dword1 Vref CLAMPED! (Calculated: 0x%x -> Set: 0x%x)\n",
			   ch,
			   final_vref_dword1,
			   VREF_MAX);
		final_vref_dword1 = VREF_MAX;
	}

	uint32_t lock_value, ewidth0, ewidth1;

	lock_value = get_phy_lock_value(cfg, ch);
	printf("lock value: %d\n", lock_value);
	// ((vwmr - vwmc) * 2) / (lock_value / 4)
	ewidth0 = (dword0_min_margin[final_vref_dword0] * 2 * 4 * 100) / lock_value;
	ewidth1 = (dword1_min_margin[final_vref_dword1] * 2 * 4 * 100) / lock_value;

	printf("CH[%d] dword0 rx voltage margin 0x%x, 0x%x (%d) (offset %d)\n",
		   ch,
		   min_valid_voltage[0],
		   max_valid_voltage[0],
		   max_valid_voltage[0] - min_valid_voltage[0],
		   final_offset[0]);
	printf("CH[%d] dword1 rx voltage margin 0x%x, 0x%x (%d) (offset %d)\n",
		   ch,
		   min_valid_voltage[1],
		   max_valid_voltage[1],
		   max_valid_voltage[1] - min_valid_voltage[1],
		   final_offset[1]);
	printf("CH[%d] read optimal vref dword0 = 0x%x (0.%d UI), dword1 = 0x%x (0.%d UI)\n",
		   ch,
		   final_vref_dword0, ewidth0,
		   final_vref_dword1, ewidth1);

	phy_set_read_vref(cfg, ch, final_vref_dword0, final_vref_dword1);

	return 0;
}

int32_t phy_read_vref_training_LFSR_avg(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t vref;
	uint32_t fail_stat_dword0 = 0, fail_stat_dword1 = 0;
	uint16_t optimal_vref_dword0 = 0, optimal_vref_dword1 = 0;
	uint16_t dword0_min_result = 0;
	uint16_t dword1_min_result = 0;
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	uint32_t dword0_sum_margin = 0, dword1_sum_margin = 0;
	uint32_t dword0_min_margin[VREF_MAX + 1] = {0, };
	uint32_t dword1_min_margin[VREF_MAX + 1] = {0, };
	uint32_t dword0_margin_avg = 0, dword1_margin_avg = 0;
	uint32_t dword0_pass_cnt = 0, dword1_pass_cnt = 0;
	uint16_t min_valid_voltage[2] = {0x0, 0x0};
	uint16_t max_valid_voltage[2] = {0x0, 0x0};

	for (vref = VREF_FROM; vref < VREF_MAX; vref += VREF_STEP) {
		fail_stat_dword0 = 0;
		fail_stat_dword1 = 0;

		phy_set_read_vref(cfg, ch, vref, vref);

		udelay(5);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

		phy_do_training(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

		phy_read_training_LFSR_seed(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;
		cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = 0x34;
		cfg->phy_base[ch]->cal_con3.num_repeat = 0x6;

		phy_do_training(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;
		cfg->phy_base[ch]->cal_con0.rdtrn_lfsr_mode_en = 0x0;

		phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);
		phy_get_training_result(cfg, ch, vwm);

		if (fail_stat_dword0 == 0 || fail_stat_dword1 == 0)
			phy_find_min_result(cfg, ch, vwm, &dword0_min_result, &dword1_min_result);

		if (fail_stat_dword0 == 0) {
			dword0_min_margin[vref] = dword0_min_result;
			dword0_sum_margin += dword0_min_result;
			dword0_pass_cnt += 1;
		}

		if (fail_stat_dword1 == 0) {
			dword1_min_margin[vref] = dword1_min_result;
			dword1_sum_margin += dword1_min_result;
			dword1_pass_cnt += 1;
		}
	}

	if (dword0_sum_margin == 0 || dword1_sum_margin == 0) {
		ERROR("CH[%d] %s%sRead Vref training: FAIL on all Vref levels\n",
				ch, fail_stat_dword0 ? "DWORD0 " : "", fail_stat_dword1 ? "DWORD1 " : "");
		return HBM_READ_TRAIN_FAIL;
	}

	dword0_margin_avg = dword0_sum_margin / dword0_pass_cnt;
	dword1_margin_avg = dword1_sum_margin / dword1_pass_cnt;

	for (vref = VREF_FROM; vref <= VREF_MAX; vref += VREF_STEP) {
		if (dword0_min_margin[vref] <= dword0_margin_avg && max_valid_voltage[0] == 0) {
			min_valid_voltage[0] = vref;
		} else if (dword0_min_margin[vref] > dword0_margin_avg) {
			max_valid_voltage[0] = vref;
		}
		if (dword1_min_margin[vref] <= dword1_margin_avg && max_valid_voltage[1] == 0) {
			min_valid_voltage[1] = vref;
		} else if (dword1_min_margin[vref] > dword1_margin_avg) {
			max_valid_voltage[1] = vref;
		}
	}

	max_valid_voltage[0] += 1;
	max_valid_voltage[1] += 1;

	optimal_vref_dword0 = (min_valid_voltage[0] + max_valid_voltage[0]) / 2;
	optimal_vref_dword1 = (min_valid_voltage[1] + max_valid_voltage[1]) / 2;

	uint32_t lock_value, ewidth0, ewidth1;

	lock_value = get_phy_lock_value(cfg, ch);
	printf("lock value: %d\n", lock_value);
	// ((vwmr - vwmc) * 2) / (lock_value / 4)
	ewidth0 = (dword0_min_margin[optimal_vref_dword0] * 2 * 4 * 100) / lock_value;
	ewidth1 = (dword1_min_margin[optimal_vref_dword1] * 2 * 4 * 100) / lock_value;

	printf("CH[%d] AVG read optimal vref "
			"dword0 = 0x%x (0x%x, 0x%x, %d, 0.%d UI), "
			"dword1 = 0x%x (0x%x, 0x%x, %d, 0.%d UI)\n",
			ch,
			optimal_vref_dword0, min_valid_voltage[0], max_valid_voltage[0], dword0_margin_avg, ewidth0,
			optimal_vref_dword1, min_valid_voltage[1], max_valid_voltage[1], dword1_margin_avg, ewidth1);

	phy_set_read_vref(cfg, ch, optimal_vref_dword0, optimal_vref_dword1);

	return 0;
}

int32_t phy_read_vref_training_LFSR(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t vref;
	uint32_t fail_stat_dword0 = 0, fail_stat_dword1 = 0;
	uint16_t optimal_vref_dword0 = 0, optimal_vref_dword1 = 0;
	uint32_t vref_dword0_max_sum = 0;
	uint32_t vref_dword1_max_sum = 0;
	uint32_t vwm_vref_dword0[VREF_REF_NUM] = {0, };
	uint32_t vwm_vref_dword1[VREF_REF_NUM] = {0, };
	uint16_t dword0_min_result = 0;
	uint16_t dword1_min_result = 0;
	uint16_t vwm_vref_dword_idx = 0;
	uint16_t vwm_sum_vref_dword0 = 0, vwm_sum_vref_dword1 = 0;
	uint16_t max_vwm_sum_vref_dword0 = 0, max_vwm_sum_vref_dword1 = 0;
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	for (vref = VREF_FROM; vref < VREF_MAX; vref += VREF_STEP) {
		fail_stat_dword0 = 0;
		fail_stat_dword1 = 0;

		phy_set_read_vref(cfg, ch, vref, vref);

		udelay(5);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

		phy_do_training(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

		phy_read_training_LFSR_seed(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;
		cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = 0x34;
		cfg->phy_base[ch]->cal_con3.num_repeat = 0x6;

		phy_do_training(cfg, ch);

		cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;
		cfg->phy_base[ch]->cal_con0.rdtrn_lfsr_mode_en = 0x0;

		phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);
		phy_get_training_result(cfg, ch, vwm);

		if (fail_stat_dword0 == 0 || fail_stat_dword1 == 0)
			phy_find_min_result(cfg, ch, vwm, &dword0_min_result, &dword1_min_result);

		if (fail_stat_dword0 == 0) {
			vwm_vref_dword0[vwm_vref_dword_idx] = dword0_min_result;
		} else {
			vwm_vref_dword0[vwm_vref_dword_idx] = 0;
		}

		if (fail_stat_dword1 == 0) {
			vwm_vref_dword1[vwm_vref_dword_idx] = dword1_min_result;
		} else {
			vwm_vref_dword1[vwm_vref_dword_idx] = 0;
		}

		if (vwm_vref_dword_idx < VREF_REF_NUM - 1) {
			vwm_vref_dword_idx++;
		} else {
			vwm_sum_vref_dword0  = phy_vwm_sum_margin(vwm_vref_dword0);
			vwm_sum_vref_dword1  = phy_vwm_sum_margin(vwm_vref_dword1);

			if (max_vwm_sum_vref_dword0 < vwm_sum_vref_dword0) {
				max_vwm_sum_vref_dword0 = vwm_sum_vref_dword0;
				vref_dword0_max_sum = vref;
			}

			if (max_vwm_sum_vref_dword1 < vwm_sum_vref_dword1) {
				max_vwm_sum_vref_dword1 = vwm_sum_vref_dword1;
				vref_dword1_max_sum = vref;
			}

			phy_vwm_shitf_window(vwm_vref_dword0);
			phy_vwm_shitf_window(vwm_vref_dword1);
		}
	}

	optimal_vref_dword0 = vref_dword0_max_sum - (VREF_REF_NUM / 2);
	optimal_vref_dword1 = vref_dword1_max_sum - (VREF_REF_NUM / 2);

	printf("CH[%d] read optimal vref dword0 = 0x%x, dword1 = 0x%x\n", ch, optimal_vref_dword0, optimal_vref_dword1);

	phy_set_read_vref(cfg, ch, optimal_vref_dword0, optimal_vref_dword1);

	return 0;
}

int32_t phy_read_vref_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t vref;
	uint32_t fail_stat_dword0 = 0, fail_stat_dword1 = 0;
	uint16_t optimal_vref_dword0 = 0, optimal_vref_dword1 = 0;
	uint32_t vref_dword0_max_sum = 0;
	uint32_t vref_dword1_max_sum = 0;
	uint32_t vwm_vref_dword0[VREF_REF_NUM] = {0, };
	uint32_t vwm_vref_dword1[VREF_REF_NUM] = {0, };
	uint16_t dword0_min_result = 0;
	uint16_t dword1_min_result = 0;
	uint16_t vwm_vref_dword_idx = 0;
	uint16_t vwm_sum_vref_dword0 = 0, vwm_sum_vref_dword1 = 0;
	uint16_t max_vwm_sum_vref_dword0 = 0, max_vwm_sum_vref_dword1 = 0;
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

	for (vref = VREF_FROM; vref < VREF_MAX; vref += VREF_STEP) {
		fail_stat_dword0 = 0;
		fail_stat_dword1 = 0;

		phy_set_read_vref(cfg, ch, vref, vref);

		udelay(5);

		phy_do_training(cfg, ch);

		phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);
		phy_get_training_result(cfg, ch, vwm);

		if (fail_stat_dword0 == 0 || fail_stat_dword1 == 0)
			phy_find_min_result(cfg, ch, vwm, &dword0_min_result, &dword1_min_result);

		if (fail_stat_dword0 == 0)
			vwm_vref_dword0[vwm_vref_dword_idx] = dword0_min_result;
		else
			vwm_vref_dword0[vwm_vref_dword_idx] = 0;

		if (fail_stat_dword1 == 0)
			vwm_vref_dword1[vwm_vref_dword_idx] = dword1_min_result;
		else
			vwm_vref_dword1[vwm_vref_dword_idx] = 0;

		if (vwm_vref_dword_idx < VREF_REF_NUM - 1) {
			vwm_vref_dword_idx++;
		} else {
			vwm_sum_vref_dword0  = phy_vwm_sum_margin(vwm_vref_dword0);
			vwm_sum_vref_dword1  = phy_vwm_sum_margin(vwm_vref_dword1);

			if (max_vwm_sum_vref_dword0 < vwm_sum_vref_dword0) {
				max_vwm_sum_vref_dword0 = vwm_sum_vref_dword0;
				vref_dword0_max_sum = vref;
			}

			if (max_vwm_sum_vref_dword1 < vwm_sum_vref_dword1) {
				max_vwm_sum_vref_dword1 = vwm_sum_vref_dword1;
				vref_dword1_max_sum = vref;
			}

			phy_vwm_shitf_window(vwm_vref_dword0);
			phy_vwm_shitf_window(vwm_vref_dword1);
		}
	}

	optimal_vref_dword0 = vref_dword0_max_sum - (VREF_REF_NUM / 2);
	optimal_vref_dword1 = vref_dword1_max_sum - (VREF_REF_NUM / 2);
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

	phy_set_read_vref(cfg, ch, optimal_vref_dword0, optimal_vref_dword1);
	INFO("CH[%d] read optimal vref dword0 = 0x%x, dword1 = 0x%x\n", ch, optimal_vref_dword0, optimal_vref_dword1);

	return 0;
}

uint32_t phy_prbs_read_training_fail_check(struct hbm3_config *cfg, uint8_t ch,
										   uint32_t *fail_stat_dword0,
										   uint32_t *fail_stat_dword1,
										   uint32_t *fail_stat_dword2)
{
	*fail_stat_dword0 = cfg->phy_base[ch]->prbs_fail_read_d0.prbs_fail_read_dq_ds0;
	*fail_stat_dword1 = cfg->phy_base[ch]->prbs_fail_read_d1.prbs_fail_read_dq_ds1;
	*fail_stat_dword2 = cfg->phy_base[ch]->prbs_fail_etc.val;

	return 0;
}

uint32_t phy_prbs_write_training_fail_check(struct hbm3_config *cfg, uint8_t ch,
											uint32_t *fail_stat_dword0,
											uint32_t *fail_stat_dword1,
											uint32_t *fail_stat_dword2)
{
	*fail_stat_dword0 = cfg->phy_base[ch]->prbs_fail_write_d0.prbs_fail_write_dq_ds0;
	*fail_stat_dword1 = cfg->phy_base[ch]->prbs_fail_write_d1.prbs_fail_write_dq_ds1;
	*fail_stat_dword2 = cfg->phy_base[ch]->prbs_fail_etc.val;

	return 0;
}

uint32_t phy_prbs_read_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	cfg->phy_base[ch]->prbs_con1.prbs_per_bit_mode = 0x1;

	if (system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_con0.prbs_pattern = 0x7;
	} else {
		cfg->phy_base[ch]->prbs_con0.prbs_pattern = 0x10;
	}

	cfg->phy_base[ch]->cal_con4.phy_prbs_rdtrn_en = 0x1;

	// PRBS read DQ and ECC training
	cfg->phy_base[ch]->prbs_per_bit_en1.prbs_per_bit_en_dq_dw0 = 0xFFFFFFFF;
	cfg->phy_base[ch]->prbs_per_bit_en2.prbs_per_bit_en_dq_dw1 = 0xFFFFFFFF;
	if (!system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0xF;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0xF;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x1;
	} else {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0x0;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x0;
	}

	if (!system_config.cfg_dis_ecc) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw0 = 0x3;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw1 = 0x3;
	}
	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x1;

	do {
		rdata = cfg->phy_base[ch]->prbs_con0.prbs_read_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	do {
		rdata = cfg->phy_base[ch]->cal_con4.phy_train_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x0;

	cfg->phy_base[ch]->prbs_per_bit_en1.prbs_per_bit_en_dq_dw0 = 0x0;
	cfg->phy_base[ch]->prbs_per_bit_en2.prbs_per_bit_en_dq_dw1 = 0x0;
	if (!system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0x0;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x0;
	}

	if (!system_config.cfg_dis_ecc) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw1 = 0x0;
	}

	/* read parity prbs */
	if (!system_config.cfg_parity_dis) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw0 = 0x1;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw1 = 0x1;

		cfg->phy_base[ch]->cal_con4.phy_train_en = 0x1;

		do {
			rdata = cfg->phy_base[ch]->prbs_con0.prbs_read_done;
			udelay(1);
		} while ((rdata & 0x1) != 0x1);

		do {
			rdata = cfg->phy_base[ch]->cal_con4.phy_train_done;
			udelay(1);
		} while ((rdata & 0x1) != 0x1);

		cfg->phy_base[ch]->cal_con4.phy_train_en = 0x0;
	}

	cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw0 = 0x0;
	cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw1 = 0x0;

	cfg->phy_base[ch]->cal_con4.phy_prbs_rdtrn_en = 0x0;

	cfg->phy_base[ch]->prbs_con1.prbs_per_bit_mode = 0x0;

	return 0;
}

uint32_t phy_prbs_write_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	cfg->phy_base[ch]->prbs_con1.prbs_per_bit_mode = 0x1;

	if (system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_con0.prbs_pattern = 0x7;
	} else {
		cfg->phy_base[ch]->prbs_con0.prbs_pattern = 0x10;
	}

	cfg->phy_base[ch]->cal_con4.phy_prbs_wrtrn_en = 0x1;

	// PRBS write DQ and ECC training
	cfg->phy_base[ch]->prbs_per_bit_en1.prbs_per_bit_en_dq_dw0 = 0xFFFFFFFF;
	cfg->phy_base[ch]->prbs_per_bit_en2.prbs_per_bit_en_dq_dw1 = 0xFFFFFFFF;
	if (!system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0xF;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0xF;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x1;
	} else {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0x0;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x0;
	}

	if (!system_config.cfg_dis_ecc) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw0 = 0x3;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw1 = 0x3;
	}

	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x1;

	do {
		rdata = cfg->phy_base[ch]->prbs_con0.prbs_write_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	do {
		rdata = cfg->phy_base[ch]->cal_con4.phy_train_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x0;

	cfg->phy_base[ch]->prbs_per_bit_en1.prbs_per_bit_en_dq_dw0 = 0x0;
	cfg->phy_base[ch]->prbs_per_bit_en2.prbs_per_bit_en_dq_dw1 = 0x0;
	if (!system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_dbi_dw1 = 0x0;
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x0;
	}

	if (!system_config.cfg_dis_ecc) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw0 = 0x0;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_ecc_dw1 = 0x0;
	}

	// PRBS write Parity training
	if (!system_config.cfg_parity_dis) {
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw0 = 0x1;
		cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw1 = 0x1;

		cfg->phy_base[ch]->cal_con4.phy_train_en = 0x1;

		do {
			rdata = cfg->phy_base[ch]->prbs_con0.prbs_write_done;
			udelay(1);
		} while ((rdata & 0x1) != 0x1);

		do {
			rdata = cfg->phy_base[ch]->cal_con4.phy_train_done;
			udelay(1);
		} while ((rdata & 0x1) != 0x1);

		cfg->phy_base[ch]->cal_con4.phy_train_en = 0x0;
	}

	cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw0 = 0x0;
	cfg->phy_base[ch]->prbs_per_bit_en0.prbs_per_bit_en_par_dw1 = 0x0;

	cfg->phy_base[ch]->cal_con4.phy_prbs_wrtrn_en = 0x0;

	cfg->phy_base[ch]->prbs_con1.prbs_per_bit_mode = 0x0;

	return 0;
}

uint32_t phy_wdqs2ck_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t ret = 0;

	cfg->phy_base[ch]->cal_con4.phy_wrlvl_en = 0x1;
	cfg->phy_base[ch]->cal_con0.wrlvl_start = 0x1;

	phy_do_training(cfg, ch);

	cfg->phy_base[ch]->cal_con4.phy_wrlvl_en = 0x0;
	cfg->phy_base[ch]->cal_con0.wrlvl_start = 0x0;

	if (cfg->phy_base[ch]->wr_lvl_fail_stat0.wrlvl_fail_status != 0) {
		ERROR("Write Leveling Fail\n");
		ret = 1;
	}

	if (cfg->phy_base[ch]->wr_lvl_overflow_stat0.wdqs_overflow != 0) {
		ERROR("Write Leveling Overflow\n");
		ret = 1;
	}

	udelay(1 * 10);

	return ret;
}

uint32_t phy_prbs_training(struct hbm3_config *cfg, uint8_t ch, bool per_bit)
{
	uint32_t ret = 0;
	uint32_t fail_stat_dword0, fail_stat_dword1, fail_stat_dword2;

	/* PRBS per-bit Training*/
	/* PRBS Read Training */
	phy_prbs_read_training(cfg, ch);
	phy_prbs_read_training_fail_check(cfg, ch, &fail_stat_dword0,
									  &fail_stat_dword1, &fail_stat_dword2);

	if (fail_stat_dword0 != 0 || fail_stat_dword1 != 0 || fail_stat_dword2 != 0) {
		WARN("CH[%d] PRBS Per-Bit Read Training Fail, DWORD0 = 0x%08x, DWORD1 = 0x%08x, DWORD2 = 0x%08x\n",
			 ch, fail_stat_dword0, fail_stat_dword1, fail_stat_dword2);
		ret = 1;
	}

	/* PRBS Write Training */
	phy_prbs_write_training(cfg, ch);
	phy_prbs_write_training_fail_check(cfg, ch, &fail_stat_dword0,
									   &fail_stat_dword1, &fail_stat_dword2);

	if (fail_stat_dword0 != 0 || fail_stat_dword1 != 0 || fail_stat_dword2 != 0) {
		WARN("CH[%d] PRBS Per-Bit Write Training Fail, DWORD0 = 0x%08x, DWORD1 = 0x%08x, DWORD2 = 0x%08x\n",
			 ch, fail_stat_dword0, fail_stat_dword1, fail_stat_dword2);
		ret = 1;
	}

	INFO("CH[%d] Read/Write PRBS Training Done\n", ch);

	return ret;
}

static inline uint32_t encode_offset_data(uint16_t p, uint16_t n)
{
	return ((p & 0x7) | ((n & 0x7) << 0x3));
}

static void update_vwm_results(union phy_vwm *vwm, union phy_vwm *max_vwm,
							   union phy_offset *max_offset, uint16_t p, uint16_t n)
{
	// Update DQ results (DQ[63:0])
	for (uint32_t i = 0; i < DQ_WIDTH; i++) {
		if (max_vwm->dq[i] < vwm->dq[i]) {
			max_vwm->dq[i] = vwm->dq[i];
			max_offset->p_dq[i] = p;
			max_offset->n_dq[i] = n;
		}
	}

	// Update ECC results (ECC[4:0])
	for (uint32_t i = 0; i < ECC_WIDTH; i++) {
		if (max_vwm->ecc[i] < vwm->ecc[i]) {
			max_vwm->ecc[i] = vwm->ecc[i];
			max_offset->p_ecc[i] = p;
			max_offset->n_ecc[i] = n;
		}
	}

	// Update SEV results (SEV[4:0])
	for (uint32_t i = 0; i < SEV_WIDTH; i++) {
		if (max_vwm->sev[i] < vwm->sev[i]) {
			max_vwm->sev[i] = vwm->sev[i];
			max_offset->p_sev[i] = p;
			max_offset->n_sev[i] = n;
		}
	}

	// Update DBI results (only if DBI is enabled) (DBI[7:0])
	if (!system_config.cfg_dbi_off) {
		for (uint32_t i = 0; i < DBI_WIDTH; i++) {
			if (max_vwm->dbi[i] < vwm->dbi[i]) {
				max_vwm->dbi[i] = vwm->dbi[i];
				max_offset->p_dbi[i] = p;
				max_offset->n_dbi[i] = n;
			}
		}
	}
}

static void apply_duty_ctrl_settings(struct hbm3_config *cfg, uint8_t ch, union phy_offset *max_offset)
{
	uint32_t data;
	uint16_t p, n;

	for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
		cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (1 << sel);

		// Apply DQ settings
		for (uint32_t i = 0; i < PCH_DQ_WIDTH; i += 2) {
			uint32_t duty_ctrl_idx = i / 2;

			p = max_offset->p_dq[sel * PCH_DQ_WIDTH + i];
			n = max_offset->n_dq[sel * PCH_DQ_WIDTH + i];
			data = encode_offset_data(p, n);
			PHY_SET_DUTY_CTRL_0(duty_ctrl_idx, (data << 1) | 1);

			p = max_offset->p_dq[sel * PCH_DQ_WIDTH + i + 1];
			n = max_offset->n_dq[sel * PCH_DQ_WIDTH + i + 1];
			data = encode_offset_data(p, n);
			PHY_SET_DUTY_CTRL_1(duty_ctrl_idx, (data << 1) | 1);
		}

		// Apply ECC settings
		p = max_offset->p_ecc[sel * PCH_ECC_WIDTH + 0];
		n = max_offset->n_ecc[sel * PCH_ECC_WIDTH + 0];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_0(16, (data << 1) | 1);

		p = max_offset->p_ecc[sel * PCH_ECC_WIDTH + 1];
		n = max_offset->n_ecc[sel * PCH_ECC_WIDTH + 1];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_1(16, (data << 1) | 1);

		// Apply SEV settings
		p = max_offset->p_sev[sel * PCH_SEV_WIDTH + 0];
		n = max_offset->n_sev[sel * PCH_SEV_WIDTH + 0];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_0(17, (data << 1) | 1);

		p = max_offset->p_sev[sel * PCH_SEV_WIDTH + 1];
		n = max_offset->n_sev[sel * PCH_SEV_WIDTH + 1];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_1(17, (data << 1) | 1);

		// Apply DBI settings
		p = max_offset->p_dbi[sel * PCH_DBI_WIDTH + 0];
		n = max_offset->n_dbi[sel * PCH_DBI_WIDTH + 0];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_0(18, (data << 1) | 1);

		p = max_offset->p_dbi[sel * PCH_DBI_WIDTH + 1];
		n = max_offset->n_dbi[sel * PCH_DBI_WIDTH + 1];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_1(18, (data << 1) | 1);

		p = max_offset->p_dbi[sel * PCH_DBI_WIDTH + 2];
		n = max_offset->n_dbi[sel * PCH_DBI_WIDTH + 2];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_0(19, (data << 1) | 1);

		p = max_offset->p_dbi[sel * PCH_DBI_WIDTH + 3];
		n = max_offset->n_dbi[sel * PCH_DBI_WIDTH + 3];
		data = encode_offset_data(p, n);
		PHY_SET_DUTY_CTRL_1(19, (data << 1) | 1);
	}
}

uint32_t phy_recv_offset_calibration(struct hbm3_config *cfg, uint8_t ch, union phy_vwm *vwm,
									 union phy_vwm *max_vwm, union phy_offset *max_offset)
{
	uint16_t p, n;

	// Enable read training mode
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

	cfg->phy_base[ch]->offset_dq_con0.ctrl_offset_dq = HBM3_INIT_OFFSET_DQ;

	// 1. DQ/ECC/SEV/DBI Receiver offset Calibration
	for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
		cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (0x1 << sel); // select dw0 or dw1

		// Enable offset calibration
		// 0 ~ 15 for DQ[31:0],
		// 16 for ECC[1:0], 17 for SEV[1:0]
		// 18 ~ 19 for DBI[3:0]
		for (int i = 0 ; i < 20 ; i++) {
			PHY_SET_DUTY_CTRL_0(i, 0x1);
			PHY_SET_DUTY_CTRL_1(i, 0x1);
		}
	}
	// Calibration sweep: N=0/P=0(default), N=1~7/P=0, N=0/P=1~7
	// This covers N=7/P=0(min) and N=0/P=7(max) range
	uint8_t n_range;

	for (p = 0; p < 8; p++) {
		n_range = (p == 0) ? 8 : 1;

		for (n = 0; n < n_range; n++) {
			// Apply offset control settings for all DWORDs
			for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
				cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (0x1 << sel); // select dw0 or dw1
				phy_dq_offset_control(cfg, ch, p, n);  // DQ[63:0]
				phy_ecc_offset_control(cfg, ch, p, n); // ECC[3:0]
				phy_sev_offset_control(cfg, ch, p, n); // SEV[3:0]
				phy_dbi_offset_control(cfg, ch, p, n); // DBI[7:0]
				phy_offset_update(cfg, ch);
			}

			phy_do_training(cfg, ch);
			phy_get_training_result(cfg, ch, vwm);
			update_vwm_results(vwm, max_vwm, max_offset, p, n);
		}
	}

	apply_duty_ctrl_settings(cfg, ch, max_offset);
	phy_offset_update(cfg, ch);
	phy_do_training(cfg, ch);

	// 2. DQS Receiver offset calibration
	uint16_t min_vwm_dword[DWORD_NUM] = {0xFFFF, 0xFFFF};
	uint16_t max_vwm_dword[DWORD_NUM] = {0, 0};

	// Enable DQS offset calibration for all DWORDs
	for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
		cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (0x1 << sel);	// select dw0 or dw1
		cfg->phy_base[ch]->duty_ctrl22.io_offset_cal_rdqs = 0x1;			// DQS0 offset calibration enable
	}

	// DQS calibration sweep
	for (p = 0; p < 8; p++) {
		n_range = (p == 0) ? 8 : 1;

		for (n = 0; n < n_range; n++) {
			// Apply RDQS offset control for all DWORDs
			for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
				cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (0x1 << sel);	// select dw0 or dw1
				phy_rdqs_offset_control(cfg, ch, p, n);
				phy_offset_update(cfg, ch);
			}

			phy_do_training(cfg, ch);
			phy_get_training_result(cfg, ch, vwm);	 // VWM_DQ/ECC/SEV/DBI
			phy_find_min_result(cfg, ch, vwm, &min_vwm_dword[0], &min_vwm_dword[1]);

			// Update best RDQS offset values
			for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
				if (max_vwm_dword[sel] < min_vwm_dword[sel]) {
					max_vwm_dword[sel] = min_vwm_dword[sel];
					max_offset->p_rdqs[sel] = p;
					max_offset->n_rdqs[sel] = n;
				}
			}
		}
	}

	// Apply best RDQS offset settings
	for (uint32_t sel = 0; sel < DWORD_NUM; sel++) {
		cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = (0x1 << sel); // select dw0 or dw1
		phy_rdqs_offset_control(cfg, ch, max_offset->p_rdqs[sel], max_offset->n_rdqs[sel]);
		phy_offset_update(cfg, ch);
	}

	// Final training with optimal settings
	phy_do_training(cfg, ch);

	// 3. Exit Receiver offset calibration
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;

	return 0;
}

uint32_t phy_command_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;
	uint32_t ca_pattern = 0x0; // ca_pattern[7:0]
	uint32_t ra_pattern = 0x5; // ra_pattern[9:0]
	uint32_t arfu_pattern = 0x0;
	uint32_t neg_ca_pattern = ~(ca_pattern) & 0xff;
	uint32_t neg_ra_pattern = ~(ra_pattern) & 0x3ff;
	uint32_t neg_arfu_pattern = ~(arfu_pattern) & 0x1;
	uint32_t i, search;
	uint32_t rd_data0 = 0, rd_data1 = 0;
	uint32_t ca_data = 0, ca_rdata = 0, ca_fdata = 0;
	uint32_t ra_data = 0, ra_rdata = 0, ra_fdata = 0;
	uint32_t arfu_data = 0, arfu_rdata = 0, arfu_fdata = 0;
	uint32_t ca_vwmr[CA_BW] = {0, }, ca_vwml[CA_BW] = {0, }, ca_vwmc[CA_BW] = {0, };
	uint32_t ra_vwmr[RA_BW] = {0, }, ra_vwml[RA_BW] = {0, }, ra_vwmc[RA_BW] = {0, };
	uint32_t arfu_vwmr = 0, arfu_vwml = 0, arfu_vwmc = 0;
	uint32_t ca = 0, ca_done = 0, ca_vwmr_done = 0, ca_vwml_done = 0;
	uint32_t ra = 0, ra_done = 0, ra_vwmr_done = 0, ra_vwml_done = 0;
	uint32_t arfu_done = 0, arfu_vwmr_done = 0, arfu_vwml_done = 0;
	uint32_t apar_vwmr = 0, apar_vwml = 0, apar_vwmc = 0;
	uint32_t apar_fb_data = 0, apar_done = 0, apar_vwmr_done = 0, apar_vwml_done = 0;
	uint8_t parity_status;
	uint8_t rd_lat = get_read_latency(system_config.op_datarate);
	uint8_t wr_lat = get_write_latency(system_config.op_datarate);

#if !ZEBU
	do {
		rdata = cfg->csr_base[ch]->dfi_phy_ca_training_start.phy_ca_training_start;
	} while ((rdata & 0x1) != 1);
#endif

	/* configuere APAR enable */
	if (system_config.cfg_parity_dis) {
		parity_status = 0x3;
	} else {
		parity_status = 0x73;
	}

	rdata = ((cfg->csr_base[ch]->mc_base5_cfg_wr.cfg_wr << 24) | (rd_lat << 16) |
			(wr_lat << 8) | (parity_status << 0));
	cfg->icon_base->wr_wdr0.wr_wdr0 = rdata;

	rdata = ((0x0 << 24) | (cfg->csr_base[ch]->mc_base5_cfg_ds.cfg_ds << 16) |
			(cfg->csr_base[ch]->mc_base5_cfg_rtp.cfg_rtp << 8) |
			(cfg->csr_base[ch]->mc_base5_cfg_ras.cfg_ras << 0));
	cfg->icon_base->wr_wdr1.wr_wdr1 = rdata;

	cfg->icon_base->test_instruction_req1.ch_select = ch;

	cfg->icon_base->test_instruction_req0.mr_dump_set_write_req = 0x1;
	udelay(1);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.mr_dump_set_write_req = 0x0;
	udelay(1);
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->phy_base[ch]->par_con.cmd_par_en = PARITY_ENABLE;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	udelay(1 * 10);

	cfg->phy_base[ch]->scheduler_mode.sw_cmd_start = 0x1;

	cfg->phy_base[ch]->scheduler_mode.scheduler_sw_mode = 0x1;

	cfg->phy_base[ch]->direct_cmd_con_0.cmd_sre_req = 0x1;
	udelay(1 * 10);
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_sre_req = 0x0;
	udelay(1 * 10);
	cfg->phy_base[ch]->cacal_con.ca_cal_start = 0x1;
	cfg->phy_base[ch]->cal_con0.ca_cal_mode = 0x1;

	/* AWORD_MISR with IEEE1500 Controller interface */
	cfg->icon_base->wr_wdr0.wr_wdr0 = 0x4; /* AWORD_MISR_CONFIG : Preset */

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x1;
	udelay(1);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x0;
	udelay(1);
	wait_for_test_instruction_req_done_clear(cfg);

	/* Set AWOR_MISR_CONFIG as AWORD Register mode */
	cfg->icon_base->wr_wdr0.wr_wdr0 = 0x6; /* AWORD_MISR_CONFIG : AWORD Register mode */

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x1;
	udelay(1);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x0;
	udelay(1);
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->phy_base[ch]->cacal_con.ca_cal_ck_sel = 0x2;

	rdata = get_phy_lock_value(cfg, ch);
	// tFS = tCK / ctrl_lock_value
	// RU((tCK/5)/1tFS) = RU((tCK/5)/(tCK/lock value))
	cfg->phy_base[ch]->sw_cmd_deskewc_code4.sw_ckdeskewcode = RU(rdata / 5);
	// printf("ckdeskew = 0x%x\n", cfg->phy_base[ch]->sw_cmd_deskewc_code4.sw_ckdeskewcode);

	cfg->phy_base[ch]->cacal_con.cbt_sw_mode = 0x1;

	phy_update_dll_code(cfg, ch);

	/* CA/RA training */
	/* Set CA[7:0], RA[9:0] pattern */
	cfg->phy_base[ch]->direct_cmd_con_1.direct_cmd_1 = (arfu_pattern << 18) |
		(ca_pattern << 10) | (ra_pattern << 0);
	cfg->phy_base[ch]->direct_cmd_con_2.direct_cmd_2 = (neg_arfu_pattern << 18) |
		(neg_ca_pattern << 10) | (neg_ra_pattern << 0);
	cfg->phy_base[ch]->direct_cmd_con_3.direct_cmd_3 = (arfu_pattern << 18) |
		(ca_pattern << 10) | (ra_pattern << 0);
	cfg->phy_base[ch]->direct_cmd_con_4.direct_cmd_4 = (neg_arfu_pattern << 18) |
		(neg_ca_pattern << 10) | (neg_ra_pattern << 0);

	for (search = 0; search <= MAX_CODE_OF_CA; search++) {
		ra_data = 0;
		ca_data = 0;
		arfu_data = 0;
		ca_fdata = 0;
		ca_rdata = 0;
		ra_fdata = 0;
		ra_rdata = 0;
		arfu_rdata = 0;
		arfu_fdata = 0;
		rd_data0 = 0;
		rd_data1 = 0;

		phy_search_ca_ra_deskew(cfg, ch, search);
		phy_update_dll_code(cfg, ch);
		phy_gen_pattern(cfg, ch);

		rdata = icon_rd_feedback(cfg, ch, &rd_data0, &rd_data1);

		ca_data = (rd_data0 & 0xffff);
		// ra_data = (((rd_data1 & 0x3f) << 14) | ((rd_data0 >> 18) & 0x3fff));
		ra_data = ((((rd_data0 >> 18) & 0x3) << 18) |
				(((rd_data0 >> 20) & 0x3) << 16) |
				(((rd_data0 >> 22) & 0x3) << 14) |
				(((rd_data0 >> 24) & 0x3) << 12) |
				(((rd_data0 >> 26) & 0x3) << 10) |
				(((rd_data0 >> 28) & 0x3) << 8) |
				(((rd_data1 >> 0) & 0x3) << 6) |
				(((rd_data1 >> 2) & 0x3) << 4) |
				(((rd_data1 >> 4) & 0x3) << 2) |
				(((rd_data0 >> 30) & 0x3) << 0));

		arfu_data = ((rd_data0 >> 16) & 0x3);

		for (i = 0; i < CA_BW; i++) {
			ca_rdata |= (((ca_data >> (i * 2 + 1)) & 0x1) << (i));
			ca_fdata |= (((ca_data >> (i * 2)) & 0x1) << (i));
		}
		for (i = 0; i < RA_BW; i++) {
			ra_rdata |= (((ra_data >> (i * 2 + 1)) & 0x1) << (i));
			ra_fdata |= (((ra_data >> (i * 2)) & 0x1) << (i));
		}

		arfu_fdata = (arfu_data & 0x1);
		arfu_rdata = ((arfu_data >> 1) & 0x1);

		for (ca = 0; ca < CA_BW; ca++) {
			if (((ca_done >> ca) & 0x1) == 0x0) {
				/* Right edge searching */
				if (((ca_vwmr_done >> ca) & 0x1) == 0x0) {
					if (((ca_rdata >> ca) & 0x1) == ((ca_pattern >> ca) & 0x1) &&
						((ca_fdata >> ca) & 0x1) == ((neg_ca_pattern >> ca) & 0x1)) {
						ca_vwmr[ca] = search;
						ca_vwmr_done |= (0x1 << ca);
					}
				} else if (((ca_vwml_done >> ca) & 0x1) == 0x0) {
					/* Left edge searching */
					if (((ca_rdata >> ca) & 0x1) == ((neg_ca_pattern >> ca) & 0x1) &&
						((ca_fdata >> ca) & 0x1) == ((ca_pattern >> ca) & 0x1)) {
						ca_vwml[ca] = search;
						ca_vwml_done |= (0x1 << ca);
					}
				} else if (((ca_vwmr_done >> ca) & 0x1) & ((ca_vwml_done >> ca) & 0x1)) {
					ca_done |= (0x1 << ca);
				}
			}
		}

		for (ra = 0; ra < RA_BW; ra++) {
			if (((ra_done >> ra) & 0x1) == 0x0) {
				/* Right edge searching */
				if (((ra_vwmr_done >> ra) & 0x1) == 0x0) {
					if (((ra_rdata >> ra) & 0x1) == ((ra_pattern >> ra) & 0x1) &&
						((ra_fdata >> ra) & 0x1) == ((neg_ra_pattern >> ra) & 0x1)) {
						ra_vwmr[ra] = search;
						ra_vwmr_done |= (0x1 << ra);
					}
				} else if (((ra_vwml_done >> ra) & 0x1) == 0x0) {
					/* Left edge searching */
					if (((ra_rdata >> ra) & 0x1) == ((neg_ra_pattern >> ra) & 0x1) &&
						((ra_fdata >> ra) & 0x1) == ((ra_pattern >> ra) & 0x1)) {
						ra_vwml[ra] = search;
						ra_vwml_done |= (0x1 << ra);
					}
				} else if (((ra_vwmr_done >> ra) & 0x1) & ((ra_vwml_done >> ra) & 0x1)) {
					ra_done |= (0x1 << ra);
				}
			}
		}
		if ((arfu_done & 0x1) == 0x0) {
			/* Right edge searching */
			if ((arfu_vwmr_done & 0x1) == 0x0) {
				if ((arfu_rdata & 0x1) == (arfu_pattern & 0x1) &&
					(arfu_fdata & 0x1) == (neg_arfu_pattern & 0x1)) {
					arfu_vwmr = search;
					arfu_vwmr_done = 0x1;
				}
			} else if ((arfu_vwml_done & 0x1) == 0x0) {
				/* Left edge searching */
				if ((arfu_rdata & 0x1) == (neg_arfu_pattern & 0x1) &&
					(arfu_fdata & 0x1) == (arfu_pattern & 0x1)) {
					arfu_vwml = search;
					arfu_vwml_done = 0x1;
				}
			} else if ((arfu_vwmr_done & 0x1) & (arfu_vwml_done & 0x1)) {
				arfu_done = 0x1;
			}
		}
		if ((ca_done == ((0x1 << CA_BW) - 1)) && (ra_done == ((0x1 << RA_BW) - 1)) &&
			arfu_done == 0x1) {
			break;
		}
	}

	for (ca = 0; ca < CA_BW; ca++) {
		ca_vwmc[ca] = (ca_vwmr[ca] + ca_vwml[ca]) / 2;
	}
	for (ra = 0; ra < RA_BW; ra++) {
		ra_vwmc[ra] = (ra_vwmr[ra] + ra_vwml[ra]) / 2;
	}
	arfu_vwmc = (arfu_vwmr + arfu_vwml) / 2;

	phy_update_ca_ra_deskew(cfg, ch, ca_vwmc, ra_vwmc, arfu_vwmc);

	phy_update_dll_code(cfg, ch);

	/* Searching APAR Edge */
	cfg->phy_base[ch]->direct_cmd_con_1.direct_cmd_1 = 0;
	cfg->phy_base[ch]->direct_cmd_con_2.direct_cmd_2 = 0;
	cfg->phy_base[ch]->direct_cmd_con_3.direct_cmd_3 = 0;
	cfg->phy_base[ch]->direct_cmd_con_4.direct_cmd_4 = 0;

	if (!system_config.cfg_parity_dis) {
		for (search = 0; search < MAX_CODE_OF_CA; search++) {
			phy_clear_feedback_data(cfg, ch);
			cfg->phy_base[ch]->sw_cmd_deskewc_code10.sw_apardeskewcode = search;
			phy_update_dll_code(cfg, ch);

			phy_gen_pattern(cfg, ch);
			phy_clear_feedback_data(cfg, ch);
			phy_gen_pattern(cfg, ch);

			udelay(1);
			apar_fb_data = cfg->phy_base[ch]->apar_stat1.apar_fbdata;

			if ((apar_done & 0x1) == 0) {
				if ((apar_vwmr_done & 0x1) == 0) {
					if (apar_fb_data == 0x0) {
						// Right edge search done
						apar_vwmr = search;
						apar_vwmr_done = 1;
						search = search + 3;
					}
				}
				// Left edge searching
				if ((apar_vwmr_done & 0x1) == 1 && (apar_vwml_done & 0x1) == 0) {
					if (apar_fb_data != 0x0) {
						apar_vwml = search;
						apar_vwml_done = 1;
					}
				} else if (apar_vwmr_done & apar_vwml_done)
					apar_done = 1;
			}
			if (apar_done) {
				// printf("APAR Done\n");
				break;
			}
		}
	}

	apar_vwmc = (apar_vwmr + apar_vwml) / 2;
	cfg->phy_base[ch]->sw_cmd_deskewc_code10.sw_apardeskewcode = apar_vwmc;
	phy_update_dll_code(cfg, ch);

	cfg->phy_base[ch]->cacal_con.cbt_sw_mode = 0x0;

	cfg->icon_base->wr_wdr0.wr_wdr0 = 0x0;

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x1;
	udelay(1);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.aword_misr_config_req = 0x0;
	udelay(1);
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;

	cfg->phy_base[ch]->cacal_con.ca_cal_start = 0x0;
	cfg->phy_base[ch]->scheduler_mode.scheduler_sw_mode = 0x1;
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_pdx_srx_req = 0x1;
	udelay(1);
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_pdx_srx_req = 0x0;
	cfg->phy_base[ch]->scheduler_mode.scheduler_sw_mode = 0x0;

	do {
		rdata = cfg->phy_base[ch]->scheduler_state.schd_fifo_empty_status;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	cfg->csr_base[ch]->dfi_phy_ca_training_complete.phy_ca_training_complete = 0x1;

	INFO("CH[%d] CBT Done\n", ch);
	return 0;
}

uint8_t phy_rx_io_setting(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	/* Beta gm increase */
	rdata = (0x2 << 0) | (0x2 << 3);
	cfg->phy_base[ch]->io_ctrl_con0.val = rdata;

	/* CTLE enable + CTLE strong */
	rdata = (0x3 << 2) | (0x3 << 12);
	cfg->phy_base[ch]->io_ctrl_con1.val = rdata;

	if (GET_REVISION == REVISION_EVT1) {
		// Enable CK side duty control
		cfg->phy_base[ch]->io_duty_ctrl.duty_aword_io_en = 0x1;

		cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_en = 0x3;
		// // case1: WDQS duty +1.5%
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x1 << 2 | 0x1;
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x0;
		// case2: WDQS duty +3.0%
		cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x2 << 2 | 0x2;
		cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x0;

		// // case3: WDQS duty +4.5%
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x3 << 2 | 0x3;
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x0;
		// // case4: WDQS duty -1.5%
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x0;
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x1 << 2 | 0x1;
		// // case5: WDQS duty -3.0%
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x0;
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x2 << 2 | 0x2;
		// // case6: WDQS duty -4.5%
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntp = 0x0;
		// cfg->phy_base[ch]->io_duty_ctrl.duty_dword_io_cntn = 0x3 << 2 | 0x3;

		// /* RDQS duty setting */
		// uint32_t rdata, rduty_ctrlp, rduty_ctrln;

		// rduty_ctrlp = 1; // 1: +1.7%, 2: +3.4%, 3: +5% @rduty_ctrln = 0
		// rduty_ctrln = 0; // 1: -1.7%, 2: -3.4%, 3: -5% @rduty_ctrlp = 0
		// rdata = cfg->phy_base[ch]->io_ctrl_con1.val;
		// cfg->phy_base[ch]->io_ctrl_con1.val = rdata | (1 << 17) | (1 << 7);
		// cfg->phy_base[ch]->evt1_rduty_ctrl5.io_rduty_rdqs = (rduty_ctrln << 2) | (rduty_ctrlp);
		// cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_dword_sel = 0x3;
		// cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_start_en = 0x1;
		// do {
		// rdata = cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_set_state_busy;
		// } while (rdata != 0);
		// cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_start_en = 0x0;
		// printf("state busy - %d (wanted 0)\n", rdata);
	}

	return 0;
}

uint8_t phy_dca_training(struct hbm3_config *cfg, uint8_t ch)
{
	union hbm3_mr11_t mr11;
	int8_t dca_step;
	uint8_t dword0_dca = 0, dword1_dca = 0;

	uint32_t fail_stat_dword0 = 0, fail_stat_dword1 = 0;
	uint16_t *dword0_ptr = NULL;
	uint16_t *dword1_ptr = NULL;
	uint16_t vwm_dca_dword0[16] = {0, }; // number of DCA steps
	uint16_t vwm_dca_dword1[16] = {0, }; // number of DCA steps
	uint16_t max_vwm_dca_dword0 = 0, max_vwm_dca_dword1 = 0;
	union phy_vwm *vwm = phy_acquire_vwm_buf();

	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x1;

	for (dca_step = 15; dca_step >= 0; dca_step--) {
		if (dca_step == 8)
			continue;

		mr11.dca_code_wdqs0 = (dca_step & 0xf);
		mr11.dca_code_wdqs1 = (dca_step & 0xf);
		mrw_phy_direct_cmd(cfg, ch, MR11, mr11.val);

		phy_do_training(cfg, ch);

		phy_read_training_fail_check(cfg, ch, &fail_stat_dword0, &fail_stat_dword1);

		phy_get_training_result(cfg, ch, vwm);

		if (fail_stat_dword0 == 0)
			dword0_ptr = &vwm_dca_dword0[dca_step];

		if (fail_stat_dword1 == 0)
			dword1_ptr = &vwm_dca_dword1[dca_step];

		phy_find_min_result(cfg, ch, vwm, dword0_ptr, dword1_ptr);

		if (max_vwm_dca_dword0 <= vwm_dca_dword0[dca_step]) {
			max_vwm_dca_dword0 = vwm_dca_dword0[dca_step];
			dword0_dca = dca_step;
		}

		if (max_vwm_dca_dword1 <= vwm_dca_dword1[dca_step]) {
			max_vwm_dca_dword1 = vwm_dca_dword1[dca_step];
			dword1_dca = dca_step;
		}
	} // dca step end
	cfg->phy_base[ch]->cal_con4.phy_rdtrn_en = 0x0;
	mr11.dca_code_wdqs0 = (dword0_dca & 0xf);
	mr11.dca_code_wdqs1 = (dword1_dca & 0xf);

	udelay(1 * 10);

	return mr11.val;
}

/* Use this function only for EVT1 */
int32_t phy_dcm_init(struct hbm3_config *cfg, uint8_t ch)
{
	uint8_t fail_pc0, fail_pc1;
	uint8_t dca_code0[2] = {0,};
	uint8_t dca_code1[2] = {0,};
	int8_t sum_dca_code0 = 0, sum_dca_code1 = 0;
	bool sign = false;
	bool is_failed = false;

	for (int direction = 0; direction <= 1; direction++) {
		cfg->phy_base[ch]->evt1_dcm_con0.dcm_direction = direction;
		cfg->phy_base[ch]->evt1_dcm_con0.phy_dcm_en = 0x1;
		cfg->phy_base[ch]->evt1_dcm_con0.dcm_start = 0x1;

		phy_do_training(cfg, ch);

		fail_pc0 = cfg->phy_base[ch]->evt1_dcm_con0.dcm_fail_pc0;
		fail_pc1 = cfg->phy_base[ch]->evt1_dcm_con0.dcm_fail_pc1;

		printf("Direction%d DCM Result: ", direction);

		if (fail_pc0) {
			printf("PC0: FAIL, ");
			is_failed = true;
		} else {
			dca_code0[direction] = cfg->phy_base[ch]->evt1_dcm_con0.dca_code_pc0;

			if (dca_code0[direction] >= 0x8) {
				sign = true;
				sum_dca_code0 += (dca_code0[direction] - 8);
			} else {
				sign = false;
				sum_dca_code0 += (-1 * dca_code0[direction]);
			}

			if (dca_code0[direction] == 0x8)
				printf("PC0: reserved value, ");
			else
				printf("PC0: %s%d, ", dca_code0[direction] == 0 ? "" : (sign ? "+" : "-"),
					   sign ? dca_code0[direction] - 0x8 : dca_code0[direction]);
		}

		if (fail_pc1) {
			printf("PC1: FAIL\n");
			is_failed = true;
		} else {
			dca_code1[direction] = cfg->phy_base[ch]->evt1_dcm_con0.dca_code_pc1;

			if (dca_code1[direction] >= 0x8) {
				sign = true;
				sum_dca_code1 += (dca_code1[direction] - 8);
			} else {
				sign = false;
				sum_dca_code1 += (-1 * dca_code1[direction]);
			}

			if (dca_code1[direction] == 0x8)
				printf("PC1: reserved value\n");
			else
				printf("PC1: %s%d\n", dca_code1[direction] == 0 ? "" : (sign ? "+" : "-"),
					   sign ? dca_code1[direction] - 0x8 : dca_code1[direction]);
		}

		cfg->phy_base[ch]->evt1_dcm_con0.dcm_start = 0x0;
		cfg->phy_base[ch]->evt1_dcm_con0.phy_dcm_en = 0x0;
	}

	if (!is_failed) {
		union hbm3_mr11_t mr11;

		sum_dca_code0 = sum_dca_code0 / 2;
		sum_dca_code1 = sum_dca_code1 / 2;

		if (sum_dca_code0 > 0)
			mr11.dca_code_wdqs0 = (sum_dca_code0 + 0x8) & 0xF;
		else
			mr11.dca_code_wdqs0 = (sum_dca_code0 * -1) & 0xF;

		if (sum_dca_code1 > 0)
			mr11.dca_code_wdqs1 = (sum_dca_code1 + 0x8) & 0xF;
		else
			mr11.dca_code_wdqs1 = (sum_dca_code1 * -1) & 0xF;

		mrw_phy_direct_cmd(cfg, ch, MR11, mr11.val);
	}

	return 0;
}

static void phy_pre_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint8_t rd_lat = get_read_latency(system_config.op_datarate);
	uint8_t wr_lat = get_write_latency(system_config.op_datarate);
	uint8_t par_lat = cfg->csr_base[ch]->mc_base5_cfg_hbm_parity_latency.cfg_hbm_parity_latency;
	uint32_t ctrl_wrlat_bbfifo_temp;

	/* Set PHY before training  */
	if (GET_REVISION == REVISION_EVT0)
		cfg->phy_base[ch]->scheduler_con3.evt0_phy_t_rddata_en = 0x1a;
	else
		cfg->phy_base[ch]->scheduler_con3.evt1_phy_t_rddata_en = 0x1a;


	cfg->phy_base[ch]->scheduler_con1.twtr =
		((cfg->csr_base[ch]->mc_base5_cfg_wtr_l.cfg_wtr_l) + wr_lat + 2);

	cfg->phy_base[ch]->gnr_con0.ctrl_rdlat = rd_lat;
	cfg->phy_base[ch]->scheduler_con0.wl = wr_lat;

	ctrl_wrlat_bbfifo_temp = (((rd_lat) >> 1) - 8 + 1 + 1);
	if (ctrl_wrlat_bbfifo_temp < 0)
		cfg->phy_base[ch]->cal_con2.ctrl_wrlat_bbfifo = 0x0;
	else if  (ctrl_wrlat_bbfifo_temp > 0xf)
		cfg->phy_base[ch]->cal_con2.ctrl_wrlat_bbfifo = 0xf;
	else
		cfg->phy_base[ch]->cal_con2.ctrl_wrlat_bbfifo = ctrl_wrlat_bbfifo_temp;

	cfg->phy_base[ch]->dll_update_con0.ctrl_upd_range = 0x2;
	/* 2025-12-01, just try
	 * cfg->phy_base[ch]->dll_update_con0.ctrl_upd_range = 0x3; // this is for EVB board condition.
	 * if this value is 0x2, we got different result(BW) as chiplet condition.
	 */
	cfg->phy_base[ch]->lock_check_con.lock_average_en = 0x1;
	/* phy initial setting E */

	if (!system_config.cfg_parity_dis) {
		cfg->phy_base[ch]->par_con.rd_par_en = PARITY_ENABLE;
		cfg->phy_base[ch]->par_con.wr_par_en = PARITY_ENABLE;
		/* Write to memory MR0 to disable CA parity because PHY does not support it */
		/* during DRAM interface training. */
		cfg->phy_base[ch]->par_con.cmd_par_en = PARITY_ENABLE;
		/* parity latency */
		cfg->phy_base[ch]->par_con.pl = par_lat;
		/* Write & Write LFSR */
		cfg->phy_base[ch]->cal_con1.wrtrn_wr_par_cal_en = 0x1;
		cfg->phy_base[ch]->par_con.wr_par_err_rst_n = 0x1;
		/* PRBS */
		cfg->phy_base[ch]->prbs_con1.prbs_par_en = 0x1;
	} else {
		/* Write & Write LFSR */
		cfg->phy_base[ch]->cal_con1.wrtrn_wr_par_cal_en = 0x0;
		cfg->phy_base[ch]->par_con.wr_par_err_rst_n = 0x0;
		/* PRBS */
		cfg->phy_base[ch]->prbs_con1.prbs_par_en = 0x0;
	}
	udelay(1);

	/* Setting before training */
	cfg->phy_base[ch]->offsetd_con0.upd_mode = 0x0;
	cfg->phy_base[ch]->mdll_con0.clkm_cg_en_sw = 0x1;
	cfg->phy_base[ch]->scheduler_con0.wl = wr_lat;

	if (GET_REVISION == REVISION_EVT0)
		cfg->phy_base[ch]->scheduler_con3.evt0_tra_rfc = (cfg->csr_base[ch]->mc_base5_cfg_rfc.cfg_rfc) + 1;
	else
		cfg->phy_base[ch]->scheduler_con3.evt1_tra_rfc = (cfg->csr_base[ch]->mc_base5_cfg_rfc.cfg_rfc) + 1;

	if (cfg->csr_base[ch]->mc_base5_cfg_xs.cfg_xs > 511) {
		cfg->phy_base[ch]->scheduler_con2.txs_extra = 0x1ff;
	} else {
		cfg->phy_base[ch]->scheduler_con2.txs_extra = cfg->csr_base[ch]->mc_base5_cfg_xs.cfg_xs;
	}

	if (system_config.cfg_dbi_off) {
		cfg->phy_base[ch]->cal_con1.wrtrn_dbi_cal_en = 0x0;
		cfg->phy_base[ch]->cal_con1.rdtrn_dbi_cal_en = 0x0;
		/* PRBS */
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x0;
	} else {
		cfg->phy_base[ch]->prbs_con1.prbs_dbi_en = 0x1;
	}

	if (system_config.cfg_dis_ecc) {
		cfg->phy_base[ch]->cal_con1.rdtrn_ecc_cal_en = 0x0;
		cfg->phy_base[ch]->cal_con1.wrtrn_ecc_cal_en = 0x0;
		/* PRBS */
		cfg->phy_base[ch]->prbs_con1.prbs_ecc_en = 0x0;
	} else {
		cfg->phy_base[ch]->cal_con1.rdtrn_ecc_cal_en = 0x1;
		cfg->phy_base[ch]->cal_con1.wrtrn_ecc_cal_en = 0x1;
		cfg->phy_base[ch]->prbs_con1.prbs_ecc_en = 0x1;
	}

	if (system_config.cfg_dis_on_die_ecc) {
		cfg->phy_base[ch]->cal_con3.rdtrn_sev_cal_en = 0x0;
		cfg->phy_base[ch]->cal_con3.wrtrn_sev_cal_en = 0x0;
	}
}

static void phy_post_training(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	cfg->phy_base[ch]->prbs_con1.prbs_per_bit_mode = 0x1;

	cfg->phy_base[ch]->mdll_con0.clkm_cg_en_sw = 0x0;
	cfg->phy_base[ch]->cal_con0.cal_vtc_en = 0x1;

	cfg->csr_base[ch]->dfi_init_dfi_training_complete.init_dfi_training_complete = 0x1;

	cfg->csr_base[ch]->mc_base2_ctrlr_soft_reset_n.ctrlr_soft_reset_n = 0x1;

	do {
		rdata = cfg->csr_base[ch]->mc_base2_ctrlr_init_done.val;
	} while ((rdata & 0x1) != 1);

	if (system_config.cfg_periodic_tr_en) {
		cfg->phy_base[ch]->cal_con4.periodic_wrtrn_en = 0x1;
		cfg->phy_base[ch]->cal_con4.periodic_rdtrn_en = 0x1; // need to check on silicon
		cfg->phy_base[ch]->cal_con5.periodic_time = 500;
		cfg->phy_base[ch]->cal_con5.periodic_en = 0x1;
	}
}

int32_t phy_training_all(struct hbm3_config *cfg, uint8_t ch)
{
	int32_t ret = HBM_OK;

	// phy_read_vref_training(cfg, ch);
	// phy_read_vref_training_LFSR(cfg, ch);
	phy_read_vref_training_LFSR_vertical(cfg, ch);
	// phy_read_vref_training_LFSR_avg(cfg, ch);
	ret = phy_read_training(cfg, ch);
	if (ret)
		return ret;
	ret = phy_read_training_LFSR(cfg, ch);
	if (ret)
		return ret;

	phy_write_vref_training(cfg, ch);
	ret = phy_write_training(cfg, ch);
	if (ret)
		return ret;
	ret = phy_write_training_LFSR(cfg, ch);
	if (ret)
		return ret;

	phy_prbs_training(cfg, ch, true);

	return ret;
}

int32_t hbm3_phy_training_step2(struct hbm3_config *cfg, uint32_t chiplet_id, uint8_t ch)
{
	INFO("CH[%d] hbm3_phy_training_step2 start\n", ch);

#if !ZEBU
	union phy_vwm *vwm = phy_acquire_vwm_buf();
	union phy_vwm *max_vwm = phy_acquire_max_vwm_buf();
	union phy_offset *max_offset = phy_acquire_max_offset_buf();

	union hbm3_mr0_t mr0 = {.val = 0};
	union hbm3_mr8_t mr8 = {.val = 0};

	mr8.duty_cycle_monitor = 1;
	mrw_phy_direct_cmd(cfg, ch, MR8, mr8.val); // Set DCM - MR8[1] to 1

	mr0.read_dbi = 1;
	mr0.write_dbi = 1;
	mr0.tcsr = 1;
	mrw_phy_direct_cmd(cfg, ch, MR0, mr0.val); // Set Disable Parity - MR0[5] to 0

	phy_rx_io_setting(cfg, ch);
	phy_recv_offset_calibration(cfg, ch, vwm, max_vwm, max_offset);
	udelay(1);

	phy_training_all(cfg, ch);

	uint8_t optimal_dca = phy_dca_training(cfg, ch);

	mrw_phy_direct_cmd(cfg, ch, MR11, optimal_dca);

	mr8.duty_cycle_monitor = 0;
	mrw_phy_direct_cmd(cfg, ch, MR8, mr8.val); // Set DCM - MR8[2] to 0

	phy_wdqs2ck_training(cfg, ch);

	mr8.duty_cycle_monitor = 1;
	mrw_phy_direct_cmd(cfg, ch, MR8, mr8.val); // Set DCM - MR8[2] to 1

	int32_t ret;

	ret = phy_training_all(cfg, ch);
	if (ret == HBM_READ_TRAIN_FAIL) {
		return phy_find_read_training_fail_bit(cfg, chiplet_id, ch);
	} else if (ret == HBM_WRITE_TRAIN_FAIL) {
		return phy_find_write_training_fail_bit(cfg, chiplet_id, ch);
	}

	udelay(1);
#endif
	INFO("CH[%d] HBM3E Errata Training Complete\n", ch);

	phy_post_training(cfg, ch);

	return HBM_OK;
}

void hbm3_phy_training_step1(struct hbm3_config *cfg, uint8_t ch)
{
	INFO("CH[%d] hbm3_phy_training_step1 start\n", ch);

	phy_pre_training(cfg, ch);
#if !ZEBU
	union hbm3_mr15_t mr15 = {.val = 0};

	phy_command_training(cfg, ch);

	//mrw_phy_direct_cmd(cfg, ch, MR11, 0x0); // Set DCA - MR11 to 0
	mr15.ref_volt_dword = 0x1b; // Vref for DQ/DQS - MR15[5:0] to 0x1b
	mrw_phy_direct_cmd(cfg, ch, MR15, mr15.val);

	phy_wdqs2ck_training(cfg, ch);
#endif
}

int32_t hbm3_phy_training_evt0(struct hbm3_config *cfg, uint32_t chiplet_id, uint8_t ch)
{
	int32_t ret = 0;

	phy_pre_training(cfg, ch);
#if !ZEBU
	union phy_vwm *vwm = phy_acquire_vwm_buf();
	union phy_vwm *max_vwm = phy_acquire_max_vwm_buf();
	union phy_offset *max_offset = phy_acquire_max_offset_buf();

	phy_command_training(cfg, ch);
	udelay(1 * 10);
	phy_wdqs2ck_training(cfg, ch);
	udelay(1 * 10);
	phy_rx_io_setting(cfg, ch);
	phy_recv_offset_calibration(cfg, ch, vwm, max_vwm, max_offset);
	udelay(1);

	phy_training_all(cfg, ch);

	uint8_t optimal_dca = phy_dca_training(cfg, ch);

	mrw_phy_direct_cmd(cfg, ch, MR11, optimal_dca);
	phy_wdqs2ck_training(cfg, ch);

	ret = phy_training_all(cfg, ch);
	if (ret == HBM_READ_TRAIN_FAIL) {
		return phy_find_read_training_fail_bit(cfg, chiplet_id, ch);
	} else if (ret == HBM_WRITE_TRAIN_FAIL) {
		return phy_find_write_training_fail_bit(cfg, chiplet_id, ch);
	}

	INFO("CH[%d] HBM Training Complete\n", ch);
#endif
	phy_post_training(cfg, ch);

	return ret;
}

int32_t hbm3_phy_training_evt1(struct hbm3_config *cfg, uint32_t chiplet_id, uint8_t ch)
{
	phy_pre_training(cfg, ch);
#if !ZEBU
	union phy_vwm *vwm = phy_acquire_vwm_buf();
	union phy_vwm *max_vwm = phy_acquire_max_vwm_buf();
	union phy_offset *max_offset = phy_acquire_max_offset_buf();

	phy_rx_io_setting(cfg, ch);
	phy_recv_offset_calibration(cfg, ch, vwm, max_vwm, max_offset);
	udelay(1 * 10);
	phy_command_training(cfg, ch);
	udelay(1 * 10);
	phy_dcm_init(cfg, ch);
	udelay(1 * 10);
	phy_wdqs2ck_training(cfg, ch);
	udelay(1 * 10);

	int32_t ret = phy_training_all(cfg, ch);

	if (ret == HBM_READ_TRAIN_FAIL) {
		return phy_find_read_training_fail_bit(cfg, chiplet_id, ch);
	} else if (ret == HBM_WRITE_TRAIN_FAIL) {
		return phy_find_write_training_fail_bit(cfg, chiplet_id, ch);
	}

	INFO("CH[%d] HBM Training Complete\n", ch);
#endif
	phy_post_training(cfg, ch);

	return 0;
}

#if !ZEBU
void hbm3_icon_zq_cal_evt0(struct hbm3_config *cfg)
{
	uint32_t rdata, retry = 0;

	cfg->sysreg_base->evt0_zq_icon_reg1.i_reset = 0x1;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	/* for EVT0. ZQ sequence */
	cfg->sysreg_base->evt0_zq_icon_reg1.i_zctrl_req_long = 0x1;

	do {
		rdata = cfg->sysreg_base->evt0_zq_icon_reg0.o_zctrl_ack;
		if (retry > 1000) {
			ERROR("zq ack Fail\n");
			return;
		}
		retry++;
	} while ((rdata & 0x1) != 0x1);

	cfg->sysreg_base->evt0_zq_icon_reg1.i_zctrl_req_long = 0x0;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;
}

int32_t hbm3_icon_zq_cal_evt1(struct hbm3_config *cfg)
{
	uint32_t rdata = 0;

	cfg->sysreg_base->evt1_i_reset.i_reset = 0x1;
	cfg->icon_base->evt1_zq_con0.i_zq_manual_mode_apb = 0x1;
	cfg->icon_base->evt1_zq_con0.i_zq_manual_str_apb = 0x1;

	do {
		rdata = cfg->icon_base->evt1_zq_mon0.o_zq_done;
	} while ((rdata & 0x1) != 0x1);

	cfg->icon_base->evt1_zq_con0.i_zq_manual_str_apb = 0x0;

	if (cfg->icon_base->evt1_zq_mon0.o_zq_error) {
		ERROR("ZQ calibration failed\n");
		return -1;
	}

	return 0;
}
#endif

uint32_t set_errata_tmrs(struct hbm3_config *cfg)
{
	NOTICE("Apply ERRATA TMRS\n");
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	udelay(1);
	cfg->sysreg_base->icon_wrstn.rst_ctrl = 0x1;
	udelay(1);
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	tmrs_gen_inst(cfg);

	/* TODO : add TMRS code for HBM3E */
	tmrs_write(cfg, 0x3E001000); // Safety Code
	tmrs_write(cfg, 0x20000B50); // B die TMRS lock
	tmrs_write(cfg, 0x1E000B43); // C die TMRS lock
	tmrs_write(cfg, 0x20000C50); // Read C2C

	// DCM output Low
	tmrs_write(cfg, 0x20000021);
	tmrs_write(cfg, 0x20000C44);
	tmrs_write(cfg, 0x20000000);

	// tmrs_b_die_kill_code(cfg); // for test

	tmrs_bypass(cfg);
	icon_mrs(cfg, CH_ALL);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x0;

	return 0;
}

static void hbm3_clear_repair_lane(void)
{
	for (int ch = 0; ch < HBM3_NUM_CH; ch++) {
		rep_status[ch] = 0;
		for (int repair_group = 0; repair_group < REDUNDANT; repair_group++) {
			ch_rep_lane[ch][repair_group] = 0xF;
		}
	}
}

#if !ZEBU
static void print_repair_info(uint32_t chiplet_id)
{
	char lane[8];

	for (int ch = 0; ch < 16; ch++) {
		for (int group = DWORD0_BYTE0; group <= DWORD1_BYTE3; group++) {
			uint16_t val = ch_rep_lane[ch][group];

			if (val == 0xF)
				continue;

			switch (group) {
			case DWORD0_BYTE0:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "ECC%d", 0);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 0);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val - 1);
				}
				break;
			case DWORD0_BYTE1:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "ECC%d", 1);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 1);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 7);
				}
				break;
			case DWORD0_BYTE2:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "SEV%d", 0);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 2);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 15);
				}
				break;
			case DWORD0_BYTE3:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "SEV%d", 1);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 3);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 23);
				}
				break;
			case DWORD1_BYTE0:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "ECC%d", 2);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 4);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 31);
				}
				break;
			case DWORD1_BYTE1:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "ECC%d", 3);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 5);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 39);
				}
				break;
			case DWORD1_BYTE2:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "SEV%d", 2);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 6);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 47);
				}
				break;
			case DWORD1_BYTE3:
				if (val == 0) {
					snprintf(lane, sizeof(lane), "SEV%d", 3);
				} else if (val == 9) {
					snprintf(lane, sizeof(lane), "DBI%d", 7);
				} else {
					snprintf(lane, sizeof(lane), "DQ%d", val + 55);
				}
				break;
			case AWORD_CA:
				if (val == 8) {
					snprintf(lane, sizeof(lane), "APAR");
				} else  if (val == 9) {
					snprintf(lane, sizeof(lane), "APFU");
				} else {
					snprintf(lane, sizeof(lane), "C%d", val);
				}
				break;
			case AWORD_RA:
				snprintf(lane, sizeof(lane), "R%d", val);
				break;
			default:
				continue;
			}

			printf("HBM%d_CH_%d_%s\n", chiplet_id, ch, lane);

		}
	}
}

static int32_t hbm3_all_ch_lane_repair(struct hbm3_config *cfg, uint32_t chiplet_id)
{
	print_repair_info(chiplet_id);
	printf("================================\n");

	for (int32_t ch = 0; ch < HBM3_NUM_CH; ch++) {
		if (rep_status[ch] == HBM_UNREPAIRABLE) {
			ERROR("CH[%d] Unrepairable PKG\n", ch);
			return HBM_UNREPAIRABLE;
		}

		if (rep_status[ch] != 0) {
			if (hbm3_lane_repair(cfg, ch, ch_rep_lane[ch])) {
				ERROR("CH[%d] Unrepairable PKG\n", ch);
				return HBM_UNREPAIRABLE;
			}
		}
	}

	return HBM_OK;
}

#if RUN_EXTEST
static void hbm3_run_extest(struct hbm3_config *cfg)
{
	uint32_t ch;

	for (ch = 0; ch < HBM3_NUM_CH; ch++)
		rep_status[ch] = icon_extest(cfg, ch, ch_rep_lane[ch]);
}
#endif
#endif /* !ZEBU */

void hbm3_ctrl_phy_init(struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t ck_freq = get_clock_frequency(system_config.op_datarate);
	uint32_t retry = 0;

	if (ch == 0) {
		if (system_config.op_datarate == hbm3_datarate_4800mbps) {
			NOTICE("HBM3 4800Mbps\n");
		} else if (system_config.op_datarate == hbm3_datarate_6400mbps) {
			NOTICE("HBM3 6400Mbps\n");
		} else if (system_config.op_datarate == hbm3_datarate_8000mbps) {
			NOTICE("HBM3 8000Mbps\n");
		} else if (system_config.op_datarate == hbm3_datarate_9200mbps) {
			NOTICE("HBM3 9200Mbps\n");
		} else if (system_config.op_datarate == hbm3_datarate_9600mbps) {
			NOTICE("HBM3 9600Mbps\n");
		} else {
			ERROR("Unsupported HBM3 datarate: %d Mbps\n", system_config.op_datarate);
			return;
		}
	}

	/* set memory controller basic configs */
	set_ctrl_config(cfg, ch);

	/* Set memory controller timing parameters */
	set_ctrl_timing(cfg, ch, ck_freq);

	/* Set memory controller features */
	set_ctrl_feature(cfg, ch);

	/* Set PHY config */
	set_phy_config(cfg, ch, ck_freq);

	/* DFI Initialization */
	hbm3_dfi_init(cfg, ch, &retry);
}

void hbm_ecc_scrub_init(uint32_t chiplet_id)
{
	struct hbm3_config *cfg = get_hbm_cfg(chiplet_id);
	uint32_t ch, rdata;

	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		cfg->csr_base[ch]->ecc_config_init_ecc_scrub_init_en.init_ecc_scrub_init_en = 0x1;
		do {
			rdata = cfg->csr_base[ch]->ecc_stat_err_stat_ecc_scrub_init_done.stat_ecc_scrub_init_done;
		} while ((rdata & 0x1) != 1);

		INFO("CH[%d] ECC init done\n", ch);
	}
}

int32_t hbm3_run_phy_training(struct hbm3_config *cfg, uint32_t chiplet_id)
{
	uint8_t rev_info = get_lotid_for_hbm();
	uint32_t ch;
	int32_t ch_result, ret = 0;

	if (rev_info != HBM3_VER_NEW) {
		for (ch = 0; ch < HBM3_NUM_CH; ch++)
			hbm3_phy_training_step1(cfg, ch);

		set_errata_tmrs(cfg);

		for (ch = 0; ch < HBM3_NUM_CH; ch++) {
			ch_result = hbm3_phy_training_step2(cfg, chiplet_id, ch);

			if (ch_result == HBM_UNREPAIRABLE) {
				ret = HBM_UNREPAIRABLE;
			} else if (ch_result == HBM_NEED_REPAIR && ret != HBM_UNREPAIRABLE) {
				ret = HBM_NEED_REPAIR;
			}
		}

	} else {
		for (ch = 0; ch < HBM3_NUM_CH; ch++) {
			if (GET_REVISION == REVISION_EVT0)
				ch_result = hbm3_phy_training_evt0(cfg, chiplet_id, ch);
			else
				ch_result = hbm3_phy_training_evt1(cfg, chiplet_id, ch);

			if (ch_result == HBM_UNREPAIRABLE) {
				ret = HBM_UNREPAIRABLE;
			} else if (ch_result == HBM_NEED_REPAIR && ret != HBM_UNREPAIRABLE) {
				ret = HBM_NEED_REPAIR;
			}
		}
	}

	return ret;
}

int32_t hbm3_init(uint32_t chiplet_id)
{
	struct hbm3_config *cfg = get_hbm_cfg(chiplet_id);
	uint32_t ch;
	uint32_t blk_dram_reset_done = 0;
	int32_t ret = 0;

	printf("Chiplet ID[%d] HBM3 init start\n", chiplet_id);
	hbm3_clear_repair_lane();
	hbm3_config_init();

hbm_reinit:
#if !ZEBU
	/* use default zq cal to imporve write margin
	 * if (GET_REVISION == REVISION_EVT0)
	 *	hbm3_icon_zq_cal_evt0(cfg);
	 * else
	 *	hbm3_icon_zq_cal_evt1(cfg);
	 */
#endif

	for (ch = 0; ch < HBM3_NUM_CH; ch++)
		hbm3_ctrl_phy_init(cfg, ch);

#if !ZEBU
#if RUN_EXTEST
	if (!blk_dram_reset_done) {
		hbm3_run_extest(cfg);
		printf("========   EXTEST DONE  ========\n");
	}
#endif /* RUN_EXTEST */
	if (blk_dram_reset_done)
		printf("======== RUNTIME REPAIR ========\n");

	if (hbm3_all_ch_lane_repair(cfg, chiplet_id) == HBM_UNREPAIRABLE)
		return HBM_UNREPAIRABLE;
#endif /* !ZEBU */

#if RUN_MBIST
	mdelay(10);
	/* MBIST is debugging feature. don't run for normal operation */
	icon_hbm_mbist(cfg);
#if RUN_CDC
	mdelay(10);
	/* CDC is debugging feature. don't run for normal operation */
	icon_hbm_chipping_detection(cfg);
#endif /* RUN_CDC */
	asm("b .");
#endif /* RUN_MBIST */

	/* for Samsung HBM3E Memory. TMRS is mandatory for High speed operation */
	set_tmrs(cfg);
	/* Controller execute MRS automatically, but send MRS through icon for confirm the MRS value  */
	icon_mrs(cfg, CH_ALL);

	ret = hbm3_run_phy_training(cfg, chiplet_id);
	if (ret == HBM_NEED_REPAIR) {
		if (blk_dram_reset_done <= 0) {
			/* BLK_DRAM partial reset for HBM lane repair */
			pmu_reset_blk_dram(chiplet_id);
			if (GET_REVISION == REVISION_EVT0)
				cmu_blk_dram_init_evt0_by_freq(CHIPLET_OFFSET * chiplet_id + CMU_DRAM, HBM_DATA_RATE);
			else
				cmu_blk_dram_init_evt1_by_freq(CHIPLET_OFFSET * chiplet_id + CMU_DRAM, HBM_DATA_RATE);
			blk_dram_reset_done++;
			goto hbm_reinit;
		} else {
			ERROR("Already Reset for HBM Repair %d times\n", blk_dram_reset_done);
			ERROR("Chiplet ID[%d] HBM Training FAIL\n", chiplet_id);
			return ret;
		}
	} else if (ret < 0) {
		ERROR("Chiplet ID[%d] HBM Training FAIL\n", chiplet_id);
		return ret;
	}

	printf("Chiplet ID[%d] HBM3 init done\n", chiplet_id);

	/* Inhibit DLL re-locking */
	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		/**
		 * Once ctrl_locked and dfi_init_complete
		 * are asserted, those won’t be deasserted
		 * until rst_n is asserted or DLL is relocked.
		 */
		cfg->phy_base[ch]->mdll_con0.ctrl_ref = 0b1111;
	}

	/* hashing enable */
	cfg->icon_base->io_ctrl0.ctrl_io_en_apb = 0x1;
	cfg->icon_base->io_ctrl0.ctrl_io_pde_apb = 0x1;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
#if (HBM3_NUM_CH == 16)
	enable_hashing(cfg, true);
#endif

	return HBM_OK;
}
