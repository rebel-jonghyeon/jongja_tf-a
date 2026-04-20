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

#define HISTORY_REG_NUM 32

/* sfr_history_reg bit field */
#define G1_SMLH_LTSSM_STATE		(0x3F << 3)
#define G1_PM_CURRENT_DATA_RATE (0x7)
#define G2_SMLH_LINK_UP			(0x1 << 7)
#define G2_RDLH_LINK_UP			(0x1 << 6)
#define G2_CFG_NEG_LINK_WIDTH	(0x3F)
#define G3_PM_L1SUB_STATE		(0x7 << 3)
#define G3_PM_DSTATE			(0x7)
#define G4_PM_L0S_STATE			(0x7 << 4)
#define G4_PM_USP_PROT_STATE	(0xF)

#define HIST_GET_G1_SMLH_LTSSM_STATE(x)		(((x) & G1_SMLH_LTSSM_STATE) >> 3)
#define HIST_GET_G1_PM_CURRENT_DATA_RATE(x) ((x) & G1_PM_CURRENT_DATA_RATE)
#define HIST_GET_G2_SMLH_LINK_UP(x)			(((x) & G2_SMLH_LINK_UP) >> 7)
#define HIST_GET_G2_RDLH_LINK_UP(x)			(((x) & G2_RDLH_LINK_UP) >> 6)
#define HIST_GET_G2_CFG_NEG_LINK_WIDTH(x)	((x) & G2_CFG_NEG_LINK_WIDTH)
#define HIST_GET_G3_PM_L1SUB_STATE(x)		(((x) & G3_PM_L1SUB_STATE) >> 3)
#define HIST_GET_G3_PM_DSTATE(x)			((x) & G3_PM_DSTATE)
#define HIST_GET_G4_PM_L0S_STATE(x)			(((x) & G4_PM_L0S_STATE >> 4))
#define HIST_GET_G4_PM_USP_PROT_STATE(x)	((x) & G4_PM_USP_PROT_STATE)

#define HIST_SET_G1_SMLH_LTSSM_STATE(x)		(((x) & 0x3F) << 3)
#define HIST_SET_G1_PM_CURRENT_DATA_RATE(x)	(((x) & 0x7))
#define HIST_SET_G2_SMLH_LINK_UP(x)			(((x) & 0x1) << 7)
#define HIST_SET_G2_RDLH_LINK_UP(x)			(((x) & 0x1) << 6)
#define HIST_SET_G2_CFG_NEG_LINK_WIDTH(x)	((x) & 0x3F)
#define HIST_SET_G3_PM_L1SUB_STATE(x)		(((x) & 0x7) << 3)
#define HIST_SET_G3_PM_DSTATE(x)			((x) & 0x7)
#define HIST_SET_G4_PM_L0S_STATE(x)			(((x) & 0x7 << 4))
#define HIST_SET_G4_PM_USP_PROT_STATE(x)	((x) & 0xF)

/* sfr_history_reg */
#define HISTORY_LTSSM_STATE_L0 (0x11 << 3)
#define HISTORY_GEN1 0
#define HISTORY_GEN2 1
#define HISTORY_GEN3 2
#define HISTORY_GEN4 3
#define HISTORY_GEN5 4

#define HISTORY_PHY_LINK_UP (0x1 << 7)
#define HISTORY_DLLP_LINK_UP (0x1 << 6)
#define HISTORY_LINK_WIDTH_1 1
#define HISTORY_LINK_WIDTH_2 2
#define HISTORY_LINK_WIDTH_4 4
#define HISTORY_LINK_WIDTH_8 8
#define HISTORY_LINK_WIDTH_16 16

/* sfr_history_store_ctrl */
#define COMPARE_START_MODE	(0x1 << 2)
#define COMPARE_EXIT_MODE	(0x0 << 2)
#define HISTORY_CLEAR		(0x1 << 1)
#define BUFFER_EN			(0x1)

/* LTSSM STATE */
#define PCIE_LTSSM_STATE_MASK				0x3F
#define PCIE_LTSSM_STATE_DETECT_QUIET		0x0
#define PCIE_LTSSM_STATE_DETECT_ACT			0x1
#define PCIE_LTSSM_STATE_POLL_ACTIVE		0x2
#define PCIE_LTSSM_STATE_POLL_COMPLIANCE	0x3
#define PCIE_LTSSM_STATE_POLL_CONFIG		0x4
#define PCIE_LTSSM_STATE_PRE_DETECT_QUIET	0x5
#define PCIE_LTSSM_STATE_DETECT_WAIT		0x6
#define PCIE_LTSSM_STATE_CFG_LINKWD_START	0x7
#define PCIE_LTSSM_STATE_CFG_LINKWD_ACEPT	0x8
#define PCIE_LTSSM_STATE_CFG_LANENUM_WAIT	0x9
#define PCIE_LTSSM_STATE_CFG_LANENUM_ACEPT	0xA
#define PCIE_LTSSM_STATE_CFG_COMPLETE		0xB
#define PCIE_LTSSM_STATE_CFG_IDLE			0xC
#define PCIE_LTSSM_STATE_RCVRY_LOCK			0xD
#define PCIE_LTSSM_STATE_RCVRY_SPEED		0xE
#define PCIE_LTSSM_STATE_RCVRY_RCVRYCFG		0xF
#define PCIE_LTSSM_STATE_RCVRY_IDLE			0x10
#define PCIE_LTSSM_STATE_L0					0x11
#define PCIE_LTSSM_STATE_L0S				0x12
#define PCIE_LTSSM_STATE_L123_SEND_EIDLE	0x13
#define PCIE_LTSSM_STATE_L1_IDLE			0x14
#define PCIE_LTSSM_STATE_L2_IDLE			0x15
#define PCIE_LTSSM_STATE_L2_WAKE			0x16
#define PCIE_LTSSM_STATE_DISABLED_ENTRY		0x17
#define PCIE_LTSSM_STATE_DISABLED_IDLE		0x18
#define PCIE_LTSSM_STATE_DISABLED			0x19
#define PCIE_LTSSM_STATE_LPBK_ENTRY			0x1A
#define PCIE_LTSSM_STATE_LPBK_ACTIVE		0x1B
#define PCIE_LTSSM_STATE_LPBK_EXIT			0x1C
#define PCIE_LTSSM_STATE_LPBK_EXIT_TIMEOUT	0x1D
#define PCIE_LTSSM_STATE_HOT_RESET_ENTRY	0x1E
#define PCIE_LTSSM_STATE_HOT_RESET			0x1F
#define PCIE_LTSSM_STATE_RCVRY_EQ0			0x20
#define PCIE_LTSSM_STATE_RCVRY_EQ1			0x21
#define PCIE_LTSSM_STATE_RCVRY_EQ2			0x22
#define PCIE_LTSSM_STATE_RCVRY_EQ3			0x23

/* Negotiated link width */
#define NEGO_LINK_WIDTH_1 0x1
#define NEGO_LINK_WIDTH_2 0x2
#define NEGO_LINK_WIDTH_4 0x4
#define NEGO_LINK_WIDTH_8 0x8
#define NEGO_LINK_WIDTH_16 0x10

/* pm_l1sub_state */
#define PM_L1SUB_S_L1_U					0x0
#define PM_L1SUB_S_L1_0					0x1
#define PM_L1SUB_S_L1_0_WAIT4_ACK		0x2
#define PM_L1SUB_S_L1_0_WAIT4_CLKREQ	0x3
#define PM_L1SUB_S_L1_N_ENTRY			0x4
#define PM_L1SUB_S_L1_N					0x5
#define PM_L1SUB_S_L1_N_EXIT			0x6
#define PM_L1SUB_S_L1_N_ABORT			0x7

/* D-state */
#define PM_DSTATE_D0 0x0
#define PM_DSTATE_D1 0x1
#define PM_DSTATE_D2 0x2
#define PM_DSTATE_D3 0x3
#define PM_DSTATE_UNINITIALIZED 0x4

/* pm_l0s_state */
#define L0S_IDLE		0x0
#define L0S_BLOCK_TLP	0x1
#define L0S_ENTER_L0S	0x2
#define L0S_L0S			0x3
#define L0S_EXIT		0x4

/* pm_usp_prot_state */
#define USP_PROT_RST					0x0
#define USP_PROT_RECOVERY				0x1
#define USP_PROT_ACTIVE					0x2
#define USP_PROT_ENTER_L0S				0x3
#define USP_PROT_ENTER_L1				0x4
#define USP_PROT_L1_BLOCK_TLP			0x5
#define USP_PROT_L1_WAIT_LAST_TLP_ACK	0x6
#define USP_PROT_L1_WAIT_PMDLLP_ACK		0x7
#define USP_PROT_ENTER_L23				0x8
#define USP_PROT_L23_BLOCK_TLP			0x9
#define USP_PROT_L23_WAIT_LAST_TLP_ACK	0xA
#define USP_PROT_L23_WAIT_PMDLLP_ACK	0xB
#define USP_PROT_WAIT_PMCSR_CPL_SENT	0xC
#define USP_PROT_WAIT_LAST_PMDLLP		0xD
#define USP_PROT_WAIT_CXS_IDLE			0xE

/* The time is recorded using 500 MHz from always-on counter in CSSYS.
 * Thus, the unit of the time stamp stored in sfr_ts_msb/lsb_history_reg* is 2ns.
 * This will be converted to 1ns unit for convenience.
 */
#define CONV_2NS_TO_1NS(x) ((x) / 2)

enum history_group {
	GROUP1 = 0x0,
	GROUP1_SUBGRP1 = 0x1,
	GROUP1_SUBGRP2 = 0x2,
	GROUP1_SUBGRP3 = 0x3,
	GROUP1_SUBGRP4 = 0x4,
	GROUP2 = 0x5,
	GROUP3 = 0x6,
	GROUP4 = 0x7
};

int32_t pcie_find_bit_shift(uint32_t field);
void pcie_subctrl_history_store_config(struct pcie_epc *dw_pcie_epc, uint32_t group,
									   uint32_t field, uint32_t user_setting);
void pcie_subctrl_history_store_start(struct pcie_epc *dw_pcie_epc, uint32_t group,
									  uint32_t buf_cond_sel);
void pcie_subctrl_history_select_group(struct pcie_epc *dw_pcie_epc, uint32_t group);
void pcie_subctrl_history_buf_clear(struct pcie_epc *dw_pcie_epc, uint32_t group);
void pcie_subctrl_history_reg_clear(struct pcie_epc *dw_pcie_epc);
void pcie_subctrl_show_history(struct pcie_epc *dw_pcie_epc, uint32_t group);
void pcie_ltssm_enable(const struct dw_pcie_config *cfg, bool en);
void pcie_crs_enable(const struct dw_pcie_config *cfg, bool en);
int16_t pcie_get_ltssm_state(const struct dw_pcie_config *cfg);
