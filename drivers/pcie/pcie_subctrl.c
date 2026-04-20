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

#include "rl_errors.h"

#include "pcie_dw.h"
#include "pcie_subctrl.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

void pcie_subctrl_history_store_config(struct pcie_epc *dw_pcie_epc, uint32_t group,
									   uint32_t field, uint32_t user_setting)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;

	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	if (user_setting == 0)
		field |= BIT(31);

	switch (group) {
	case GROUP1_SUBGRP1:
	case GROUP1_SUBGRP2:
	case GROUP1_SUBGRP3:
	case GROUP1_SUBGRP4:
		subctrl_base->sfr_power_state_history_m_g1.val = field;
		subctrl_base->sfr_power_state_history_s_g1.val = user_setting;
		break;
	case GROUP2:
		subctrl_base->sfr_power_state_history_m_g2.val = field;
		subctrl_base->sfr_power_state_history_s_g2.val = user_setting;
		break;
	case GROUP3:
		subctrl_base->sfr_power_state_history_m_g3.val = field;
		subctrl_base->sfr_power_state_history_s_g3.val = user_setting;
		break;
	case GROUP4:
		subctrl_base->sfr_power_state_history_m_g4.val = field;
		subctrl_base->sfr_power_state_history_s_g4.val = user_setting;
		break;
	default:
		pcie_err_log("%s: History store config fail - wrong group\n", __func__);
		break;
	}
}

void pcie_subctrl_history_store_start(struct pcie_epc *dw_pcie_epc, uint32_t group,
									  uint32_t buf_cond_sel)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	switch (group) {
	case GROUP1_SUBGRP1:
	case GROUP1_SUBGRP2:
	case GROUP1_SUBGRP3:
	case GROUP1_SUBGRP4:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g1 = buf_cond_sel | BUFFER_EN;
		break;
	case GROUP2:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g2 = buf_cond_sel | BUFFER_EN;
		break;
	case GROUP3:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g3 = buf_cond_sel | BUFFER_EN;
		break;
	case GROUP4:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g4 = buf_cond_sel | BUFFER_EN;
		break;
	default:
		pcie_err_log("%s: History store start fail - wrong group\n", __func__);
		return;
	}
}

void pcie_subctrl_history_select_group(struct pcie_epc *dw_pcie_epc, uint32_t group)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	subctrl_base->sfr_history_sel.history_sel = group;
}

void pcie_subctrl_history_buf_clear(struct pcie_epc *dw_pcie_epc, uint32_t group)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	switch (group) {
	case GROUP1:
	case GROUP1_SUBGRP1:
	case GROUP1_SUBGRP2:
	case GROUP1_SUBGRP3:
	case GROUP1_SUBGRP4:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g1 = HISTORY_CLEAR;
		break;
	case GROUP2:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g2 = HISTORY_CLEAR;
		break;
	case GROUP3:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g3 = HISTORY_CLEAR;
		break;
	case GROUP4:
		subctrl_base->sfr_history_store_ctrl.history_store_ctrl_g4 = HISTORY_CLEAR;
		break;
	default:
		pcie_err_log("%s: History store clear fail - wrong group\n", __func__);
		break;
	}
}

static char *pcie_subctrl_decode_smlh_ltssm_state(uint32_t value)
{
	char *decode = NULL;

	switch (value) {
	case PCIE_LTSSM_STATE_DETECT_QUIET:
		decode = "Detect.Quiet";
		break;
	case PCIE_LTSSM_STATE_DETECT_ACT:
		decode = "Detect.Active";
		break;
	case PCIE_LTSSM_STATE_POLL_ACTIVE:
		decode = "Polling.Active";
		break;
	case PCIE_LTSSM_STATE_POLL_COMPLIANCE:
		decode = "Polling.Compliance";
		break;
	case PCIE_LTSSM_STATE_POLL_CONFIG:
		decode = "Polling.Config";
		break;
	case PCIE_LTSSM_STATE_PRE_DETECT_QUIET:
		decode = "Predetect.Quiet";
		break;
	case PCIE_LTSSM_STATE_CFG_LINKWD_START:
		decode = "Cfg.LinkwdStart";
		break;
	case PCIE_LTSSM_STATE_CFG_LINKWD_ACEPT:
		decode = "Cfg.LinkwdAcept";
		break;
	case PCIE_LTSSM_STATE_CFG_LANENUM_WAIT:
		decode = "Cfg.LanenumWait";
		break;
	case PCIE_LTSSM_STATE_CFG_LANENUM_ACEPT:
		decode = "Cfg.LanenumAcept";
		break;
	case PCIE_LTSSM_STATE_CFG_COMPLETE:
		decode = "Cfg.Complete";
		break;
	case PCIE_LTSSM_STATE_CFG_IDLE:
		decode = "Cfg.Idle";
		break;
	case PCIE_LTSSM_STATE_RCVRY_LOCK:
		decode = "Rcvry.Lock";
		break;
	case PCIE_LTSSM_STATE_RCVRY_SPEED:
		decode = "Rcvry.Speed";
		break;
	case PCIE_LTSSM_STATE_RCVRY_RCVRYCFG:
		decode = "Rcvry.Rcvrycfg";
		break;
	case PCIE_LTSSM_STATE_RCVRY_IDLE:
		decode = "Rcvry.Idle";
		break;
	case PCIE_LTSSM_STATE_L0:
		decode = "L0";
		break;
	case PCIE_LTSSM_STATE_L0S:
		decode = "L0s";
		break;
	case PCIE_LTSSM_STATE_L123_SEND_EIDLE:
		decode = "L123.SendEidle";
		break;
	case PCIE_LTSSM_STATE_L1_IDLE:
		decode = "L1.Idle";
		break;
	case PCIE_LTSSM_STATE_L2_IDLE:
		decode = "L2.Idle";
		break;
	case PCIE_LTSSM_STATE_L2_WAKE:
		decode = "L2.Wake";
		break;
	case PCIE_LTSSM_STATE_DISABLED_ENTRY:
		decode = "Disabled.Entry";
		break;
	case PCIE_LTSSM_STATE_DISABLED_IDLE:
		decode = "Disabled.Idle";
		break;
	case PCIE_LTSSM_STATE_DISABLED:
		decode = "Disabled";
		break;
	case PCIE_LTSSM_STATE_LPBK_ENTRY:
		decode = "Loopback.Entry";
		break;
	case PCIE_LTSSM_STATE_LPBK_ACTIVE:
		decode = "Loopback.Active";
		break;
	case PCIE_LTSSM_STATE_LPBK_EXIT:
		decode = "Loopback.Exit";
		break;
	case PCIE_LTSSM_STATE_LPBK_EXIT_TIMEOUT:
		decode = "Loopback.Exittimeout";
		break;
	case PCIE_LTSSM_STATE_HOT_RESET_ENTRY:
		decode = "Hotreset.Entry";
		break;
	case PCIE_LTSSM_STATE_HOT_RESET:
		decode = "Hotreset";
		break;
	case PCIE_LTSSM_STATE_RCVRY_EQ0:
		decode = "Rcvry.Eq0";
		break;
	case PCIE_LTSSM_STATE_RCVRY_EQ1:
		decode = "Rcvry.Eq1";
		break;
	case PCIE_LTSSM_STATE_RCVRY_EQ2:
		decode = "Rcvry.Eq2";
		break;
	case PCIE_LTSSM_STATE_RCVRY_EQ3:
		decode = "Rcvry.Eq3";
		break;
	default:
		pcie_err_log("There is no case to decode the value of smlh_ltssm_state\n");
		pcie_err_log("Please check %s\n", __func__);
		break;
	}

	return decode;
}

static char *pcie_subctrl_decode_pm_l1sub_state(uint32_t value)
{
	char *decode = NULL;

	switch (value) {
	case PM_L1SUB_S_L1_U:
		decode = "S_L1_U";
		break;
	case PM_L1SUB_S_L1_0:
		decode = "S_L1_0";
		break;
	case PM_L1SUB_S_L1_0_WAIT4_ACK:
		decode = "S_L1_0_WAIT4_ACK";
		break;
	case PM_L1SUB_S_L1_0_WAIT4_CLKREQ:
		decode = "S_L1_0_WAIT4_CLKREQ";
		break;
	case PM_L1SUB_S_L1_N_ENTRY:
		decode = "S_L1_N_ENTRY";
		break;
	case PM_L1SUB_S_L1_N:
		decode = "S_L1_N";
		break;
	case PM_L1SUB_S_L1_N_EXIT:
		decode = "S_L1_N_EXIT";
		break;
	case PM_L1SUB_S_L1_N_ABORT:
		decode = "S_L1_N_ABORT";
		break;
	default:
		pcie_err_log("There is no case to decode the value of pm_l1sub_state\n");
		pcie_err_log("Please check %s\n", __func__);
		break;
	}

	return decode;
}

static char *pcie_subctrl_decode_pm_dstate(uint32_t value)
{
	char *decode = NULL;

	switch (value) {
	case PM_DSTATE_D0:
		decode = "D0";
		break;
	case PM_DSTATE_D1:
		decode = "D1";
		break;
	case PM_DSTATE_D2:
		decode = "D2";
		break;
	case PM_DSTATE_D3:
		decode = "D3";
		break;
	case PM_DSTATE_UNINITIALIZED:
		decode = "Uninitialized";
		break;
	default:
		pcie_err_log("There is no case to decode the value of pm_dstate\n");
		pcie_err_log("Please check %s\n", __func__);
		break;
	}

	return decode;
}

static char *pcie_subctrl_decode_pm_l0s_state(uint32_t value)
{
	char *decode = NULL;

	switch (value) {
	case L0S_IDLE:
		decode = "L0S_IDLE";
		break;
	case L0S_BLOCK_TLP:
		decode = "L0S_BLOCK_TLP";
		break;
	case L0S_ENTER_L0S:
		decode = "L0S_ENTER_L0S";
		break;
	case L0S_L0S:
		decode = "L0S_L0S";
		break;
	case L0S_EXIT:
		decode = "L0S_EXIT";
		break;
	case 0x5:
	case 0x6:
	case 0x7:
		decode = "Reserved";
		break;
	default:
		pcie_err_log("There is no case to decode the value of pm_l0s_state - 0x%x\n", value);
		pcie_err_log("Please check %s\n", __func__);
		break;
	}

	return decode;
}

static char *pcie_subctrl_decode_pm_usp_prot_state(uint32_t value)
{
	char *decode = NULL;

	switch (value) {
	case USP_PROT_RST:
		decode = "RST";
		break;
	case USP_PROT_RECOVERY:
		decode = "RECOVERY";
		break;
	case USP_PROT_ACTIVE:
		decode = "ACTIVE";
		break;
	case USP_PROT_ENTER_L0S:
		decode = "ENTER_L0S";
		break;
	case USP_PROT_ENTER_L1:
		decode = "ENTER_L1";
		break;
	case USP_PROT_L1_BLOCK_TLP:
		decode = "L1_BLOCK_TLP";
		break;
	case USP_PROT_L1_WAIT_LAST_TLP_ACK:
		decode = "L1_WAIT_LAST_TLP_ACK";
		break;
	case USP_PROT_L1_WAIT_PMDLLP_ACK:
		decode = "L1_WAIT_PMDLLP_ACK";
		break;
	case USP_PROT_ENTER_L23:
		decode = "ENTER_L23";
		break;
	case USP_PROT_L23_BLOCK_TLP:
		decode = "USP_PROT_L23_BLOCK_TLP";
		break;
	case USP_PROT_L23_WAIT_LAST_TLP_ACK:
		decode = "USP_PROT_L23_WAIT_LAST_TLP_ACK";
		break;
	case USP_PROT_L23_WAIT_PMDLLP_ACK:
		decode = "USP_PROT_L23_WAIT_PMDLLP_ACK";
		break;
	case USP_PROT_WAIT_PMCSR_CPL_SENT:
		decode = "USP_PROT_WAIT_PMCSR_CPL_SENT";
		break;
	case USP_PROT_WAIT_LAST_PMDLLP:
		decode = "USP_PROT_WAIT_LAST_PMDLLP";
		break;
	case USP_PROT_WAIT_CXS_IDLE:
		decode = "USP_PROT_WAIT_CXS_IDLE";
		break;
	default:
		pcie_err_log("There is no case to decode the value of pm_usp_prot_state - 0x%x\n", value);
		pcie_err_log("Please check %s\n", __func__);
		break;
	}

	return decode;
}

void pcie_subctrl_show_history(struct pcie_epc *dw_pcie_epc, uint32_t group)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;
	volatile uint32_t *history_reg = (volatile uint32_t *)&subctrl_base->sfr_history_reg0;
	volatile uint32_t *ts_msb_reg = (volatile uint32_t *)&subctrl_base->sfr_ts_msb_history_reg0;
	volatile uint32_t *ts_lsb_reg = (volatile uint32_t *)&subctrl_base->sfr_ts_lsb_history_reg0;
	int32_t i;
	uint32_t field1, field2, field3;
	uint64_t ts;
	char *state1, *state2;

	switch (group) {
	case GROUP1_SUBGRP1:
	case GROUP1_SUBGRP2:
	case GROUP1_SUBGRP3:
	case GROUP1_SUBGRP4:
		pcie_subctrl_history_select_group(dw_pcie_epc, group);

		if (!HIST_GET_G1_SMLH_LTSSM_STATE(history_reg[0]) &&
			!HIST_GET_G1_PM_CURRENT_DATA_RATE(history_reg[0]) &&
			!ts_msb_reg[0] && !ts_lsb_reg[0]) {
			printf("No data are stored in the history buffer for GROUP1_SUBGRP%ld.\n", group);
			break;
		}

		printf("-------------------------------------------------------------\n");
		printf(" Index |       LTSSM state      |  Speed  |  Time stamp (ns)\n");
		printf("-------------------------------------------------------------\n");

		for (i = HISTORY_REG_NUM - 1; i >= 0; i--) {
			field1 = HIST_GET_G1_SMLH_LTSSM_STATE(history_reg[i]);
			field2 = HIST_GET_G1_PM_CURRENT_DATA_RATE(history_reg[i]);
			ts = (((uint64_t)ts_msb_reg[i] << 32) | ts_lsb_reg[i]);

			if (field1 || field2 || ts) {
				state1 = pcie_subctrl_decode_smlh_ltssm_state(field1);

				printf("   %2ld  | %20s   |   Gen%1ld  |      %lld\n", i, state1, field2 + 1,
					   CONV_2NS_TO_1NS(ts));
			}

			if (!i)
				printf("-------------------------------------------------------------\n");
		}

		break;
	case GROUP2:
		pcie_subctrl_history_select_group(dw_pcie_epc, group);

		if (!HIST_GET_G2_SMLH_LINK_UP(history_reg[0]) &&
			!HIST_GET_G2_RDLH_LINK_UP(history_reg[0]) &&
			!HIST_GET_G2_CFG_NEG_LINK_WIDTH(history_reg[0]) &&
			!ts_msb_reg[0] && !ts_lsb_reg[0]) {
			printf("No data are stored in the history buffer for GROUP2.\n");
			break;
		}

		printf("------------------------------------------------------------------------\n");
		printf(" Index | smlh_link_up | rdlh_link_up | neg_link_width | Time stamp (ns)\n");
		printf("------------------------------------------------------------------------\n");

		for (i = HISTORY_REG_NUM - 1; i >= 0; i--) {
			field1 = HIST_GET_G2_SMLH_LINK_UP(history_reg[i]);
			field2 = HIST_GET_G2_RDLH_LINK_UP(history_reg[i]);
			field3 = HIST_GET_G2_CFG_NEG_LINK_WIDTH(history_reg[i]);
			ts = (((uint64_t)ts_msb_reg[i] << 32) | ts_lsb_reg[i]) / 2;

			if (field1 || field2 || field3 || ts) {
				printf("   %2ld  |       %1ld      |       %1ld      |       %2ld       |      %lld\n",
					   i, field1, field2, field3, CONV_2NS_TO_1NS(ts));
			}

			if (!i)
				printf("------------------------------------------------------------------------\n");
		}

		break;
	case GROUP3:
		pcie_subctrl_history_select_group(dw_pcie_epc, group);

		if (!HIST_GET_G3_PM_L1SUB_STATE(history_reg[0]) &&
			!HIST_GET_G3_PM_DSTATE(history_reg[0]) &&
			!ts_msb_reg[0] && !ts_lsb_reg[0]) {
			printf("No data are stored in the history buffer for GROUP3.\n");
			break;
		}

		printf("---------------------------------------------------------------\n");
		printf(" Index |    pm_l1sub_state    |   pm_dstate   | Time stamp (ns)\n");
		printf("---------------------------------------------------------------\n");

		for (i = HISTORY_REG_NUM - 1; i >= 0; i--) {
			field1 = HIST_GET_G3_PM_L1SUB_STATE(history_reg[i]);
			field2 = HIST_GET_G3_PM_DSTATE(history_reg[i]);
			ts = (((uint64_t)ts_msb_reg[i] << 32) | ts_lsb_reg[i]) / 2;

			if (field1 || field2 || ts) {
				state1 = pcie_subctrl_decode_pm_l1sub_state(field1);
				state2 = pcie_subctrl_decode_pm_dstate(field2);
				printf("   %2ld  | %19ld  | %13s |      %lld\n",
					   i, field1, state2, CONV_2NS_TO_1NS(ts));
			}

			if (!i)
				printf("---------------------------------------------------------------\n");
		}

		break;
	case GROUP4:
		pcie_subctrl_history_select_group(dw_pcie_epc, group);

		if (!HIST_GET_G4_PM_L0S_STATE(history_reg[0]) &&
			!HIST_GET_G4_PM_USP_PROT_STATE(history_reg[0]) &&
			!ts_msb_reg[0] && !ts_lsb_reg[0]) {
			printf("No data are stored in the history buffer for GROUP4.\n");
			break;
		}

		printf("----------------------------------------------------------------------------\n");
		printf(" Index |  pm_l0s_state  |        pm_usp_prot_state        | Time stamp (ns)\n");
		printf("----------------------------------------------------------------------------\n");

		for (i = HISTORY_REG_NUM - 1; i >= 0; i--) {
			field1 = HIST_GET_G4_PM_L0S_STATE(history_reg[i]);
			field2 = HIST_GET_G4_PM_USP_PROT_STATE(history_reg[i]);
			ts = (((uint64_t)ts_msb_reg[i] << 32) | ts_lsb_reg[i]) / 2;

			if (field1 || field2 || ts) {
				state1 = pcie_subctrl_decode_pm_l0s_state(field1);
				state2 = pcie_subctrl_decode_pm_usp_prot_state(field2);
				printf("   %2ld  | %14s | %31s |      %lld\n",
					   i, state1, state2, CONV_2NS_TO_1NS(ts));
			}

			if (!i)
				printf("----------------------------------------------------------------------------\n");
		}

		break;
	default:
		pcie_err_log("%s: Enter proper encoded history group number\n", __func__);
		break;
	}
}

void pcie_ltssm_enable(const struct dw_pcie_config *cfg, bool en)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	subctrl_base->sfr_app_ltssm_enable.app_ltssm_enable = en;
}

void pcie_crs_enable(const struct dw_pcie_config *cfg, bool en)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	subctrl_base->sfr_app_req_retry_en.app_req_retry_en = en;
	subctrl_base->sfr_app_pf_req_retry_en.app_pf_req_retry_en = en;
	if (en)
		subctrl_base->sfr_app_vf_req_retry_en.app_vf_req_retry_en = 0xFFFF;
	else
		subctrl_base->sfr_app_vf_req_retry_en.app_vf_req_retry_en = 0;
}

int16_t pcie_get_ltssm_state(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	return (subctrl_base->sfr_cxpl_debug_info_31_0.val & PCIE_LTSSM_STATE_MASK);
}
