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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#if defined(__RUN_RTOS)
#include <arch/system_api.h>
#include <rl_utils.h>
#include <rebel_h_platform.h>
#else
#include <drivers/delay_timer.h>
#include <lib/utils_def.h>
#include <platform_def.h>
#endif

#define PRINT_INFO_VAL(x) \
	printf("\n>> %s: 0x%08x", #x, x)

#ifndef HBM3_NUM_CH
#define HBM3_NUM_CH 16
#endif
#define HBM3_NUM_INST 1

#define HBM3_INST_OFFSET 0x2000000000
#define HBM3_CON_BASE_OFFSET 0x40000
#define HBM3_PHY_BASE_OFFSET 0x10000

#if defined(__RUN_RTOS)
#define HBM3_ICON_BASE      HBM_ICON

#define HBM3_CON_0_BASE     HBMC0
#define HBM3_CON_1_BASE     HBMC1
#define HBM3_CON_2_BASE     HBMC2
#define HBM3_CON_3_BASE     HBMC3
#define HBM3_CON_4_BASE     HBMC4
#define HBM3_CON_5_BASE     HBMC5
#define HBM3_CON_6_BASE     HBMC6
#define HBM3_CON_7_BASE     HBMC7
#define HBM3_CON_8_BASE     HBMC8
#define HBM3_CON_9_BASE     HBMC9
#define HBM3_CON_10_BASE    HBMC10
#define HBM3_CON_11_BASE    HBMC11
#define HBM3_CON_12_BASE    HBMC12
#define HBM3_CON_13_BASE    HBMC13
#define HBM3_CON_14_BASE    HBMC14
#define HBM3_CON_15_BASE    HBMC15

#define HBM3_PHY_0_BASE     HBM_PHY_0
#define HBM3_PHY_1_BASE     HBM_PHY_1
#define HBM3_PHY_2_BASE     HBM_PHY_2
#define HBM3_PHY_3_BASE     HBM_PHY_3
#define HBM3_PHY_4_BASE     HBM_PHY_4
#define HBM3_PHY_5_BASE     HBM_PHY_5
#define HBM3_PHY_6_BASE     HBM_PHY_6
#define HBM3_PHY_7_BASE     HBM_PHY_7
#define HBM3_PHY_8_BASE     HBM_PHY_8
#define HBM3_PHY_9_BASE     HBM_PHY_9
#define HBM3_PHY_10_BASE    HBM_PHY_10
#define HBM3_PHY_11_BASE    HBM_PHY_11
#define HBM3_PHY_12_BASE    HBM_PHY_12
#define HBM3_PHY_13_BASE    HBM_PHY_13
#define HBM3_PHY_14_BASE    HBM_PHY_14
#define HBM3_PHY_15_BASE    HBM_PHY_15
#else
#define HBM3_ICON_BASE      0x1FF79F0000

#define HBM3_CON_0_BASE     0x1FF7400000
#define HBM3_CON_1_BASE     0x1FF7440000
#define HBM3_CON_2_BASE     0x1FF7480000
#define HBM3_CON_3_BASE     0x1FF74c0000
#define HBM3_CON_4_BASE     0x1FF7500000
#define HBM3_CON_5_BASE     0x1FF7540000
#define HBM3_CON_6_BASE     0x1FF7580000
#define HBM3_CON_7_BASE     0x1FF75c0000
#define HBM3_CON_8_BASE     0x1FF7600000
#define HBM3_CON_9_BASE     0x1FF7640000
#define HBM3_CON_10_BASE    0x1FF7680000
#define HBM3_CON_11_BASE    0x1FF76c0000
#define HBM3_CON_12_BASE    0x1FF7700000
#define HBM3_CON_13_BASE    0x1FF7740000
#define HBM3_CON_14_BASE    0x1FF7780000
#define HBM3_CON_15_BASE    0x1FF77c0000

#define HBM3_PHY_0_BASE     0x1FF7800000
#define HBM3_PHY_1_BASE     0x1FF7810000
#define HBM3_PHY_2_BASE     0x1FF7820000
#define HBM3_PHY_3_BASE     0x1FF7830000
#define HBM3_PHY_4_BASE     0x1FF7840000
#define HBM3_PHY_5_BASE     0x1FF7850000
#define HBM3_PHY_6_BASE     0x1FF7860000
#define HBM3_PHY_7_BASE     0x1FF7870000
#define HBM3_PHY_8_BASE     0x1FF7880000
#define HBM3_PHY_9_BASE     0x1FF7890000
#define HBM3_PHY_10_BASE    0x1FF78A0000
#define HBM3_PHY_11_BASE    0x1FF78B0000
#define HBM3_PHY_12_BASE    0x1FF78C0000
#define HBM3_PHY_13_BASE    0x1FF78D0000
#define HBM3_PHY_14_BASE    0x1FF78E0000
#define HBM3_PHY_15_BASE    0x1FF78F0000
#endif

#define SBREF_ISSUE_PER 10
#define BL8_SHIFT 6
#define MT_ADDR_MASK 0x3FFFFFF
#define MT_ADDR_BIT_MASK 0x3F
#define MAX_ADDR_RANGE 0x2400000

// PRBS_LEFT_MARGIN 3 ~ 12
#define PRBS_LEFT_MARGIN_3(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0xedc + (0x4 * (idx)))))))

// PRBS_RIGHT_MARGIN 3~12
#define PRBS_RIGHT_MARGIN_3(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0xf44 + (0x4 * (idx)))))))

// PRBS_LEFT_MARGIN 16 ~ 25
#define PRBS_LEFT_MARGIN_16(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0xf10 + (0x4 * (idx)))))))

// PRBS_RIGHT_MARGIN 16 ~ 25
#define PRBS_RIGHT_MARGIN_16(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0xf78 + (0x4 * (idx)))))))

// SW_PRBS_OFFSETRW_CLEAR 0xE00 ~ 0xECC
#define SW_PRBS_OFFSETRW_CLEAR(idx) \
		*((volatile unsigned int *)((unsigned long long)&cfg->phy_base[ch]->sw_prbs_offsetr0 + 0x4 * (idx))) = \
		(0x0)

#define WR_WDR_IDX(addr, idx, v) \
	((*((volatile unsigned int *)(((unsigned long long)(addr) + (0x58) - ((idx) * 4))))) = v)

#define RD_WDR_CH(addr, idx, ch) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0xa4 + (0x4c * (ch)) - ((idx) * 4))))))

#define RD_VWM_DQ_STAT(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0x45c + (0x4 * (idx)))))))

#define RD_VWM_ECC_STAT(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0x4dc + (0x4 * (idx)))))))

#define RD_VWM_SEV_STAT(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0x4e4 + (0x4 * (idx)))))))

#define RD_VWM_DBI_STAT(addr, idx) \
	(*((volatile unsigned int *)(((unsigned long long)(addr) + (0x4ec + (0x4 * (idx)))))))

#define PHY_SET_DUTY_CTRL_0(idx, v) \
		*((volatile unsigned int *)((unsigned long long)&cfg->phy_base[ch]->duty_ctrl0 + 0x4 * (idx))) = \
		((*((volatile unsigned int *)((unsigned long long)&cfg->phy_base[ch]->duty_ctrl0 + 0x4 * (idx)))) \
		& (~0x7F)) | ((v) & 0x7F)

#define PHY_SET_DUTY_CTRL_1(idx, v) \
		*((volatile unsigned int *)((unsigned long long)&cfg->phy_base[ch]->duty_ctrl0 + 0x4 * (idx))) = \
		((*((volatile unsigned int *)((unsigned long long)&cfg->phy_base[ch]->duty_ctrl0 + 0x4 * (idx)))) \
		& (~0x7F0000)) | (((v) << 16) & 0x7F0000)

#define MAX_CODE_OF_CA 0x1ef /* 0x1ff - 0x10  */
#define CA_BW 8
#define RA_BW 10

#define VREF_MAX 0x3f
#define VREF_REF_NUM 5
#define DQ_WIDTH 64
#define ECC_WIDTH 4
#define SEV_WIDTH 4
#define DBI_WIDTH 8
#define DWORD_NUM 2

#define PCH_DQ_WIDTH (DQ_WIDTH / DWORD_NUM)
#define PCH_ECC_WIDTH (ECC_WIDTH / DWORD_NUM)
#define PCH_SEV_WIDTH (SEV_WIDTH / DWORD_NUM)
#define PCH_DBI_WIDTH (DBI_WIDTH / DWORD_NUM)

#define CTL_LOCK_VALUE_MASK 0x3FF
#define MRW_MASK 0x3FF00
#define HBM3_SET_VREF(x) (((x) & 0x3f) << 6 | ((x) & 0x3f) << 0)
#define HBM3_GET_VREF(x) ((x) & 0x3f)

/* Return Code */
#define HBM_OK					0		/* Success */
#define HBM_ERROR				-1		/* Error generic */
#define HBM_NEED_REPAIR			2		/* Need HBM Repair */
#define HBM_UNREPAIRABLE		-2		/* HBM Unrepairable */
#define HBM_READ_TRAIN_FAIL		-3
#define HBM_WRITE_TRAIN_FAIL	-4

enum ecc_status {
	ECC_DISABLE = 0,
	ECC_ENABLE = 1,
};

enum ecc_bypass {
	ECC_BYPASS_DISABLE = 0,
	ECC_BYPASS_ENABLE = 1,
};

enum parity_status {
	PARITY_DISABLE = 0,
	PARITY_ENABLE = 1,
};

enum hbm3_datarate {
	hbm3_datarate_4800mbps = 0,
	hbm3_datarate_6400mbps = 1,
	hbm3_datarate_8000mbps = 2,
	hbm3_datarate_9200mbps = 3,
	hbm3_datarate_9600mbps = 4,
};

enum train_rw {
	TRAIN_CA = 0,
	TRAIN_READ = 1,
	TRAIN_WRITE = 2,
};

enum wdr_mr_pos {
	MR0_3 = 0,
	MR4_7 = 1,
	MR8_11 = 2,
	MR12_15 = 3,
};

enum ch_select {
	CH_A = 0,
	CH_B = 1,
	CH_C = 2,
	CH_D = 3,
	CH_E = 4,
	CH_F = 5,
	CH_G = 6,
	CH_H = 7,
	CH_I = 8,
	CH_J = 9,
	CH_K = 10,
	CH_L = 11,
	CH_M = 12,
	CH_N = 13,
	CH_O = 14,
	CH_P = 15,
	CH_ALL = 31,
};

enum sw_fsm_mode {
	SET_WIR = 0,
	SET_WIR_WR_WDR = 1,
	SET_WIR_RD_WDR = 2,
	WR_WDR = 3,
	RD_WDR = 4,
	SET_WIR_SHIFT_WDR = 5,
};

enum HBM3_MODE_REGISTER {
	MR0,
	MR1,
	MR2,
	MR3,
	MR4,
	MR5,
	MR6,
	MR7,
	MR8,
	MR9,
	MR10,
	MR11,
	MR12,
	MR13,
	MR14,
	MR15
};

struct hbm3_config {
	volatile struct hbm3ephy *phy_base[HBM3_NUM_CH];
	volatile struct ddr_csr *csr_base[HBM3_NUM_CH];
	volatile struct ieee1500_icon *icon_base;
	volatile struct sysreg_dram *sysreg_base;
};

struct system_config_t {
	uint8_t op_datarate;
	bool cfg_dbi_off;
	bool cfg_bg_interleave_on;
	bool cfg_ecs_on;
	bool cfg_all_bank_ref;
	bool cfg_parity_dis;
	bool cfg_dis_ecc;
	bool cfg_ecc_bypass;
	bool cfg_dis_on_die_ecc;
	bool cfg_auto_self_ref_en;
	bool cfg_auto_power_down_en;
	bool cfg_en_rfm;
	bool cfg_periodic_tr_en;
};

/* Common */
struct hbm3_config *get_hbm_cfg(uint32_t chiplet_id);
int32_t hbm3_config_init(void);
uint16_t get_phy_lock_value(volatile struct hbm3_config *cfg, uint8_t ch);
void phy_do_training(volatile struct hbm3_config *cfg, uint8_t ch);
void phy_gen_pattern(volatile struct hbm3_config *cfg, uint8_t ch);
void phy_update_dll_code(volatile struct hbm3_config *cfg, uint8_t ch);
void phy_clear_feedback_data(volatile struct hbm3_config *cfg, uint8_t ch);
void mrw_mask(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t mr_addr, uint32_t mr_data, uint32_t mask);
void mrw(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t mr_addr, uint32_t mr_data);
void mrw_phy_direct_cmd(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t ma, uint8_t op);
void phy_set_read_vref(volatile struct hbm3_config *cfg, uint8_t ch,  uint16_t dword0_vref, uint16_t dword1_vref);
void phy_set_write_vref(volatile struct hbm3_config *cfg, uint8_t ch,  uint16_t dram_vref);
void phy_dq_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n);
void phy_ecc_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n);
void phy_sev_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n);
void phy_dbi_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n);
void phy_rdqs_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n);
void phy_offset_update(volatile struct hbm3_config *cfg, uint8_t ch);
