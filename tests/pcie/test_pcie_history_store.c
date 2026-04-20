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

#include "test_common.h"
#include "rl_errors.h"

#include "pcie_dw.h"
#include "pcie_subctrl.h"

static const char help_pcie_history[] =
	"[pcie hist g1 <mode> <LTSSM state> <Speed>]\r\n"
	"- <mode> : 0 - exit mode, 1 - start mode\r\n"
	"- <LTSSM state> : 0x0(Detect.Quiet) ~ 0x23(Rcvry.Eq3), other - off\r\n"
	"- <Speed> : 1(Gen1) ~ 5(Gen5), other - off\r\n"
	"[pcie hist g2 <mode> <PHY Linkup> <DLLP Linkup> <Link width>]"
	"- <mode> : 0 - exit mode, 1 - start mode\r\n"
	"- <PHY Linkup> : 1 - smlh_link_up, other - off\r\n"
	"- <DLLP Linkup> : 1 - rdlh_link_up, other - off\r\n"
	"- <Link width> : 1 - x1, 2 - x2, 4 - x4, 8 - x8, 16 - x16, other - off\r\n"
	"[pcie hist g3 <mode> <L1 substate> <PHY Power State>]\r\n"
	"- <mode> : 0 - exit mode, 1 - start mode\r\n"
	"- <L1 substate> : 0(L1_U) ~ 7(L1_N_ABORT), other - off\r\n"
	"- <PHY Power State> : 0(D0) ~ 4(Uninitialized), other - off\r\n"
	"[pcie hist g4 <mode> <Internal PM L0S state> <Internal PM USP Prot state>]\r\n"
	"- <mode> : 0 - exit mode, 1 - start mode\r\n"
	"- <Internal PM L0S state> : 0(L0S_IDLE) ~ 4(L0S_EXIT), other - off\r\n"
	"- <Internal PM USP Prot state> : 0x0(USP_PROT_RST) ~ 0xe(USP_PROT_WAIT_CXS_IDLE), other - off\r\n"
	"[pcie show_hist <group>]\r\n"
	"[pcie clear_hist <group>]\r\n"
	"\r\n";

static int32_t test_pcie_group1_history(uint8_t mode, int8_t state, int8_t speed)
{
	struct pcie_epc *epc;
	uint32_t mask = 0, user_setting = 0;

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	if (state >= PCIE_LTSSM_STATE_DETECT_QUIET && state <= PCIE_LTSSM_STATE_RCVRY_EQ3) {
		mask |= G1_SMLH_LTSSM_STATE;
		user_setting |= HIST_SET_G1_SMLH_LTSSM_STATE(state);
	}

	if (speed >= GEN1 && speed <= GEN5) {
		mask |= G1_PM_CURRENT_DATA_RATE;
		/* pm_current_data_rate - 0:GEN1, 1:GEN2 2:GEN3 3:GEN4 4:GEN5 */
		user_setting |= HIST_SET_G1_PM_CURRENT_DATA_RATE(speed - 1);
	}

	if (!mask) {
		printf("Check the input values: state(%d), speed(%d)\n", state, speed);
		return RL_ERROR;
	}

	pcie_subctrl_history_store_config(epc, GROUP1_SUBGRP1, mask, user_setting);

	if (mode == 0) {
		pcie_subctrl_history_store_start(epc, GROUP1_SUBGRP1, COMPARE_EXIT_MODE);
	} else if (mode == 1) {
		pcie_subctrl_history_store_start(epc, GROUP1_SUBGRP1, COMPARE_START_MODE);
	} else {
		printf("%s: Enter proper mode\n", __func__);
	}

	return 0;
}

static int32_t test_pcie_group2_history(uint8_t mode, int8_t phy_linkup, int8_t dllp_linkup, int8_t width)
{
	struct pcie_epc *epc;
	uint32_t mask = 0, user_setting = 0;

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	if (phy_linkup == 1) {
		mask |= G2_SMLH_LINK_UP;
		user_setting |= HISTORY_PHY_LINK_UP;
	}

	if (dllp_linkup == 1) {
		mask |= G2_RDLH_LINK_UP;
		user_setting |= HISTORY_DLLP_LINK_UP;
	}

	if (width == 1 || width == 2 || width == 4 || width == 8 || width == 16) {
		mask |= G2_CFG_NEG_LINK_WIDTH;
		user_setting |= HIST_SET_G2_CFG_NEG_LINK_WIDTH(width);
	}

	if (!mask) {
		printf("Check the input values: phy_linkup(%d), dllp_linkup(%d), width(%d)\n",
			   phy_linkup, dllp_linkup, width);
		return RL_ERROR;
	}

	pcie_subctrl_history_store_config(epc, GROUP2, mask, user_setting);

	if (mode == 0) {
		pcie_subctrl_history_store_start(epc, GROUP2, COMPARE_EXIT_MODE);
	} else if (mode == 1) {
		pcie_subctrl_history_store_start(epc, GROUP2, COMPARE_START_MODE);
	} else {
		printf("%s: Enter proper mode\n", __func__);
	}

	return 0;
}

static int32_t test_pcie_group3_history(uint8_t mode, int8_t pm_l1sub, int8_t pm_dstate)
{
	struct pcie_epc *epc;
	uint32_t mask = 0;
	uint32_t user_setting = 0;

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	if (pm_l1sub >= PM_L1SUB_S_L1_U && pm_l1sub <= PM_L1SUB_S_L1_N_ABORT) {
		mask |= G3_PM_L1SUB_STATE;
		user_setting |= HIST_GET_G3_PM_L1SUB_STATE(pm_l1sub);
	}

	if (pm_dstate >= PM_DSTATE_D0 && pm_dstate <= PM_DSTATE_UNINITIALIZED) {
		mask |= G3_PM_DSTATE;
		user_setting |= HIST_SET_G3_PM_DSTATE(pm_dstate);
	}

	if (!mask) {
		printf("Check the input values: pm_l1sub_state(0x%x), pm_dstate(0x%x)\n",
			   pm_l1sub, pm_dstate);
		return RL_ERROR;
	}

	pcie_subctrl_history_store_config(epc, GROUP3, mask, user_setting);

	if (mode == 0) {
		pcie_subctrl_history_store_start(epc, GROUP3, COMPARE_EXIT_MODE);
	} else if (mode == 1) {
		pcie_subctrl_history_store_start(epc, GROUP3, COMPARE_START_MODE);
	} else {
		printf("%s: Enter proper mode\n", __func__);
	}

	return RL_OK;
}

static int32_t test_pcie_group4_history(uint8_t mode, int8_t pm_l0s, int8_t pm_usp_prot)
{
	struct pcie_epc *epc;
	uint32_t mask = 0;
	uint32_t user_setting = 0;

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	if (pm_l0s >= L0S_IDLE && pm_l0s <= L0S_EXIT) {
		mask |= G4_PM_L0S_STATE;
		user_setting |= HIST_SET_G4_PM_L0S_STATE(pm_l0s);
	}

	if (pm_usp_prot >= USP_PROT_RST && pm_usp_prot <= USP_PROT_WAIT_CXS_IDLE) {
		mask |= G4_PM_USP_PROT_STATE;
		user_setting |= HIST_SET_G4_PM_USP_PROT_STATE(pm_usp_prot);
	}

	if (!mask) {
		printf("Check the input values: pm_l0s_state(0x%x), pm_usp_prot_state(0x%x)\n",
			   pm_l0s, pm_usp_prot);
		return RL_ERROR;
	}

	pcie_subctrl_history_store_config(epc, GROUP4, mask, user_setting);

	if (mode == 0) {
		pcie_subctrl_history_store_start(epc, GROUP4, COMPARE_EXIT_MODE);
	} else if (mode == 1) {
		pcie_subctrl_history_store_start(epc, GROUP4, COMPARE_START_MODE);
	} else {
		printf("%s: Enter proper mode\n", __func__);
	}

	return RL_OK;
}

void test_pcie_show_history(int argc, char *argv[])
{
	char *group;
	uint32_t i;
	struct pcie_epc *epc;

	if (argc != 2) {
		printf("Check command\n%s", help_pcie_history);
		return;
	}
	group = argv[1];

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	if (!strcmp(group, "GROUP1") || !strcmp(group, "group1") || !strcmp(group, "1")) {
		for (i = GROUP1_SUBGRP4; i >= GROUP1_SUBGRP1; i--)
			pcie_subctrl_show_history(epc, i);
	} else if (!strcmp(group, "GROUP2") || !strcmp(group, "group2") || !strcmp(group, "2"))
		pcie_subctrl_show_history(epc, GROUP2);
	else if (!strcmp(group, "GROUP3") || !strcmp(group, "group3") || !strcmp(group, "3"))
		pcie_subctrl_show_history(epc, GROUP3);
	else if (!strcmp(group, "GROUP4") || !strcmp(group, "group4") || !strcmp(group, "4"))
		pcie_subctrl_show_history(epc, GROUP4);
	else
		printf("%s: Fail to show history\n", __func__);
}

void test_pcie_clear_buffer(int argc, char *argv[])
{
	char *group;
	struct pcie_epc *epc;

	if (argc != 2) {
		printf("Check command\n%s", help_pcie_history);
		return;
	}
	group = argv[1];

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	if (!strcmp(group, "GROUP1") || !strcmp(group, "group1") || !strcmp(group, "1"))
		pcie_subctrl_history_buf_clear(epc, GROUP1);
	else if (!strcmp(group, "GROUP2") || !strcmp(group, "group2") || !strcmp(group, "2"))
		pcie_subctrl_history_buf_clear(epc, GROUP2);
	else if (!strcmp(group, "GROUP3") || !strcmp(group, "group3") || !strcmp(group, "3"))
		pcie_subctrl_history_buf_clear(epc, GROUP3);
	else if (!strcmp(group, "GROUP4") || !strcmp(group, "group4") || !strcmp(group, "4"))
		pcie_subctrl_history_buf_clear(epc, GROUP4);
}

int32_t test_pcie_history_store(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Check command\n%s", help_pcie_history);
		return RL_BADARG;
	}

	if (strcmp(argv[1], "g1") == 0 || strcmp(argv[1], "GROUP1") == 0 ||
		strcmp(argv[1], "group1") == 0 || strcmp(argv[1], "1") == 0) {

		if (argc != 5) {
			printf("Check command\n%s", help_pcie_history);
			return RL_BADARG;
		}
		uint8_t mode = strtol(argv[2], NULL, 0);
		int8_t state = strtol(argv[3], NULL, 0);
		int8_t speed = strtol(argv[4], NULL, 0);

		test_pcie_group1_history(mode, state, speed);
	} else if (strcmp(argv[1], "g2") == 0 || strcmp(argv[1], "GROUP2") == 0 ||
			   strcmp(argv[1], "group2") == 0 || strcmp(argv[1], "2") == 0) {
		if (argc != 6) {
			printf("Check command\n%s", help_pcie_history);
			return RL_BADARG;
		}

		uint8_t mode = strtol(argv[2], NULL, 0);
		int8_t phy_linkup = strtol(argv[3], NULL, 0);
		int8_t dllp_linkup = strtol(argv[4], NULL, 0);
		int8_t width = strtol(argv[5], NULL, 0);

		test_pcie_group2_history(mode, phy_linkup, dllp_linkup, width);
	} else if (strcmp(argv[1], "g3") == 0 || strcmp(argv[1], "GROUP3") == 0 ||
			   strcmp(argv[1], "group3") == 0 || strcmp(argv[1], "3") == 0) {
		if (argc != 5) {
			printf("Check command\n%s", help_pcie_history);
			return RL_BADARG;
		}
		uint8_t mode = strtol(argv[2], NULL, 0);
		int8_t l1sub = strtol(argv[3], NULL, 0);
		int8_t dstate = strtol(argv[4], NULL, 0);

		test_pcie_group3_history(mode, l1sub, dstate);
	} else if (strcmp(argv[1], "g4") == 0 || strcmp(argv[1], "GROUP4") == 0 ||
			   strcmp(argv[1], "group4") == 0 || strcmp(argv[1], "4") == 0) {
		if (argc != 5) {
			printf("Check command\n%s", help_pcie_history);
			return RL_BADARG;
		}
		uint8_t mode = strtol(argv[2], NULL, 0);
		int8_t l0s = strtol(argv[3], NULL, 0);
		int8_t usp_prot = strtol(argv[4], NULL, 0);

		test_pcie_group4_history(mode, l0s, usp_prot);
	} else {
		printf("ERR: Enter proper signal to store history\n");
		return RL_ERROR;
	}

	return RL_OK;
}
