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

#include <stdlib.h>
#include "rl_utils.h"
#include "rl_errors.h"

#include "pcie_dw.h"

#define GEN3_BASE_VAL (3)

static const char help_pcie_sd[] =
	"[pcie sd] : Print RAS-DES Silicon Debug Status\r\n"
	"\r\n";

static const char help_pcie_sd_eq[] =
	"[pcie sd_eq <all/lane_sel> <all/rate_sel> : Print RAS-DES Silicon Debug EQ Status ]\r\n"
	"\r\n";

static const char help_pcie_tba[] =
	"[pcie tba sel] : Print selected report & duration information\r\n"
	"[pcie tba 1 <report> <duration>] : Select Report and Duration & Enable Timer\r\n"
	"[pcie tba 0] : Disable Time-based Analysis\r\n"
	"[pcie tba dump] : Print Time-based Analysis Data\r\n"
	"\r\n";

static const char help_pcie_ecnt[] =
	"[pcie ecnt <all or group:0,1,2,3,5,7>] : Print Event count data\r\n"
	"[pcie ecnt_clr <all or group:0,1,2,3,5,7>] : Clear Event count data\r\n"
	"\r\n";

struct index_str {
	int8_t index;
	char *str;
};

struct event_group_info {
	int8_t index;
	char *str;
	int32_t max_event;
	const struct index_str *event;
};

static const struct index_str sd_ltssm_var[] = {
	{0x0, "DIR_SPEED_CHANGE"},
	{0x1, "CHANGED_SPEED_RCVRY"},
	{0x2, "SUCCESSFUL_SPEED_NEGO"},
	{0x3, "UPCFG_CAPABLE"},
	{0x4, "SEL_DE_EMPHASIS"},
	{0x5, "START_EQ_W_PRESET"},
	{0x6, "EQ_DONE_8GT"},
	{0x7, "EQ_DONE_16GT"},
	{0xFF, "idle_to_rlock_transitioned"}
};

static const struct index_str tba_report_info[] = {
	{0x0, "TBA_ONE_CYCLE"},
	{0x1, "TBA_TX_L0S"},
	{0x2, "TBA_RX_L0S"},
	{0x3, "TBA_L0"},
	{0x4, "TBA_L1"},
	{0x5, "TBA_L1_1"},
	{0x6, "TBA_L1_2"},
	{0x7, "TBA_CFG_RCVRY"},
	{0x8, "TBA_TX_RX_L0S_OR_L0P"},
	{0x9, "TBA_L1_AUX"},
	{0xA, "NULL"}, {0xB, "NULL"}, {0xC, "NULL"},
	{0xD, "NULL"}, {0xE, "NULL"}, {0xF, "NULL"},
	{0x10, "TBA_1_CYCLE"},
	{0x11, "TBA_TX_L0S_"},
	{0x12, "TBA_RX_L0S_"},
	{0x13, "TBA_L0_"},
	{0x14, "TBA_L1_"},
	{0x17, "TBA_CFG_RCVRY_"},
	{0x18, "TBA_TX_RX_L0S_"},
	{0x19, "NULL"}, {0x1A, "NULL"}, {0x1B, "NULL"},
	{0x1C, "NULL"}, {0x1D, "NULL"}, {0x1E, "NULL"}, {0x1F, "NULL"},
	{0x20, "TBA_TX_PCIE_TLP"},
	{0x21, "TBA_RX_PCIE_TLP"},
	{0x22, "TBA_TX_CCIX_TLP"},
	{0x23, "TBA_RX_CCIX_TLP"}
};

static const struct index_str tba_duration_info[] =  {
	{0x0, "TBA_MANUAL"},
	{0x1, "TBA_1_MS"},
	{0x2, "TBA_2_MS"},
	{0x3, "TBA_100_MS"},
	{0x4, "TBA_1_S"},
	{0x5, "TBA_2_S"},
	{0x6, "TBA_4_S"},
	{0xFF, "TBA_4_US"}
};

static const struct index_str event_g0[] = {
	{0x0, "EBUF Overflow"},
	{0x1, "EBUF Under-run"},
	{0x2, "Decode Error"},
	{0x3, "Running Disparity Error"},
	{0x4, "SKP OS Parity Error"},
	{0x5, "SYNC Header Error"},
	{0x6, "RX Valid de-assertion"},
	{0x7, "CTL SKP OS Parity Error"},
	{0x8, "1st Retimer Parity Error"},
	{0x9, "2nd Retimer Parity Error"},
	{0xA, "Margin CRC and Parity Error"}
};

static const struct index_str event_g1[] = {
	{0x0, "Reserved"}, {0x1, "Reserved"}, {0x2, "Reserved"},
	{0x3, "Reserved"}, {0x4, "Reserved"},
	{0x5, "Detect EI Infer"},
	{0x6, "Receiver Error"},
	{0x7, "RX Recovery Request"},
	{0x8, "N_FTS Timeout"},
	{0x9, "Framing Error"},
	{0xA, "Deskew Error"},
	{0xB, "Received EIOS when L0s is not supported and not directed L1 or L2"},
	{0xC, "Framing Error in L0 State"},
	{0xD, "Deskew Uncompleted Error"}
};

static const struct index_str event_g2[] = {
	{0x0, "BAD TLP"},
	{0x1, "LCRC Error"},
	{0x2, "BAD DLLP"},
	{0x3, "Replay Number Rollover"},
	{0x4, "Replay Timeout"},
	{0x5, "RX Nak DLLP"},
	{0x6, "TX Nak DLLP"},
	{0x7, "Retry TLP"}
};

static const struct index_str event_g3[] = {
	{0x0, "FC Timeout"},
	{0x1, "Poisoned TLP"},
	{0x2, "ECRC Error"},
	{0x3, "Unsupported Request"},
	{0x4, "Completer Abort"},
	{0x5, "Completion Timeout"}
};

static const struct index_str event_g4[] = {
	{0x0, "EBUF SKP Add"},
	{0x1, "EBUF SKP Del"}
};

static const struct index_str event_g5[] = {
	{0x0, "L0 to Recovery Entry"},
	{0x1, "L1 to Recovery Entry"},
	{0x2, "TX L0s Entry"},
	{0x3, "RX L0s Entry"},
	{0x4, "ASPM L1 reject"},
	{0x5, "L1 Entry"},
	{0x6, "L1 CPM"},
	{0x7, "L1.1 Entry"},
	{0x8, "L1.2 Entry"},
	{0x9, "L1 short duration"},
	{0xA, "L1.2 abort"},
	{0xB, "L2 Entry"},
	{0xC, "Speed Change"},
	{0xD, "Link width Change"},
	{0xE, "Reserved"}
};

static const struct index_str event_g6[] = {
	{0x0, "TX Ack DLLP"},
	{0x1, "TX Update FC DLLP"},
	{0x2, "RX Ack DLLP"},
	{0x3, "RX Update FC DLLP"},
	{0x4, "RX Nullified TLP"},
	{0x5, "TX Nullified TLP"},
	{0x6, "RX Duplicate TLP"},
};

static const struct index_str event_g7[] = {
	{0x0, "TX Memory Write"},
	{0x1, "TX Memory Read"},
	{0x2, "Reserved"},
	{0x3, "Reserved"},
	{0x4, "TX IO Write"},
	{0x5, "TX IO Read"},
	{0x6, "TX Completion without data"},
	{0x7, "TX Completion w data"},
	{0x8, "TX Message TLP"},
	{0x9, "TX Atomic"},
	{0xA, "TX TLP with Prefix"},
	{0xB, "RX Memory Write"},
	{0xC, "RX Memory Read"},
	{0xD, "RX Configuration Write"},
	{0xE, "RX Configuration Read"},
	{0xF, "RX IO Write"},
	{0x10, "RX IO Read"},
	{0x11, "RX Completion without data"},
	{0x12, "RX Completion w data"},
	{0x13, "RX Message TLP"},
	{0x14, "RX Atomic"},
	{0x15, "RX TLP with Prefix"},
	{0x16, "TX CCIX TLP"},
	{0x17, "RX CCIX TLP"},
	{0x18, "TX Deferrable Memory Write TLP"},
	{0x19, "RX Deferrable Memory Write TLP"}
};

static const struct event_group_info event_group[] = {
	{0x0, "Layer1 Error Counter Per-Lane", sizeof(event_g0) / sizeof(struct index_str), event_g0},
	{0x1, "Layer1 Error Counter Common-Lane", sizeof(event_g1) / sizeof(struct index_str), event_g1},
	{0x2, "Layer2 Error Counter Common-Lane", sizeof(event_g2) / sizeof(struct index_str), event_g2},
	{0x3, "Layer3 Error Counter Common-Lane", sizeof(event_g3) / sizeof(struct index_str), event_g3},
	{0x4, "Layer1 Non-Error Counter Per-Lane", sizeof(event_g4) / sizeof(struct index_str), event_g4},
	{0x5, "Layer1 Non-Error Counter [RAM] Common Lane", sizeof(event_g5) / sizeof(struct index_str), event_g5},
	{0x6, "Layer2 Non-Error Counter [RAM]", sizeof(event_g6) / sizeof(struct index_str), event_g6},
	{0x7, "Layer3 Non-Error Counter [RAM]", sizeof(event_g7) / sizeof(struct index_str), event_g7}
};

static int32_t print_tba_selection(struct pcie_epc *epc)
{
	uint8_t report = 0, duration = 0;

	if (pcie_rasdes_get_tba_info(epc, &report, &duration) != RL_OK)
		return false;

	printf("Selected Report Type: %s Duration: %s",
		   tba_report_info[report].str,
		   duration == tba_duration_info[7].index ? tba_duration_info[7].str : tba_duration_info[duration].str);

	return RL_OK;
}

static int32_t print_tba_data(struct pcie_epc *epc)
{
	printf("TBA Data: %lld", pcie_rasdes_get_tba_data(epc));

	return RL_OK;
}

int32_t test_pcie_rasdes_tba(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Check command again\n%s", help_pcie_tba);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();
	int32_t ret = RL_OK;

	if (!epc)
		return RL_ERROR;

	if (strcmp(argv[1], "sel") == 0) {
		ret = print_tba_selection(epc);

	} else if (strcmp(argv[1], "1") == 0) {
		if (argc != 4) {
			printf("Check command again\n%s", help_pcie_tba);
			return RL_BADARG;
		}
		uint8_t report = strtol(argv[2], NULL, 0);
		uint8_t duration = strtol(argv[3], NULL, 0);

		if (pcie_rasdes_start_tba(epc, report, duration) != RL_OK)
			return RL_ERROR;

	} else if (strcmp(argv[1], "0") == 0) {
		if (pcie_rasdes_stop_tba(epc) != RL_OK)
			return RL_ERROR;

	} else if (strcmp(argv[1], "dump") == 0) {
		ret = print_tba_data(epc);

	} else {
		printf("Check command again\n%s", help_pcie_tba);
		return RL_BADARG;
	}

	return ret;
}

static void print_ecnt_group_data(struct pcie_epc *epc, uint8_t group)
{
	uint32_t data = 0;
	uint8_t event, lane;

	printf("========================================\n");
	printf("Group%d: %s\n", group, event_group[group].str);
	printf("========================================\n");
	for (event = 0; event < event_group[group].max_event; event++) {
		if (strcmp(event_group[group].event[event].str, "Reserved") == 0)
			continue;
		printf("Event 0x%x: %s\n", event, event_group[group].event[event].str);
		printf("----------------------------------------\n");
		printf("lane_num|    Data    |\n");
		for (lane = 0; lane < PCIE_TARGET_NUM_LANES; lane++) {
			pcie_rasdes_select_ecnt(epc, group, event, lane);
			pcie_rasdes_get_ecnt_data(epc, &data);
			printf("   %2d   | 0x%08x |\n", lane, data);
		}
		printf("----------------------------------------\n");
	}
}

static void clear_ecnt_group_data(struct pcie_epc *epc, uint8_t group)
{
	uint8_t event, lane;

	for (event = 0; event < event_group[group].max_event; event++) {
		if (strcmp(event_group[group].event[event].str, "Reserved") == 0)
			continue;

		for (lane = 0; lane < PCIE_TARGET_NUM_LANES; lane++) {
			pcie_rasdes_select_ecnt(epc, group, event, lane);
			pcie_rasdes_clear_ecnt(epc, false);
		}
	}
}

int32_t test_pcie_rasdes_ecnt(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command again\n%s", help_pcie_ecnt);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	if (strcmp(argv[0], "ecnt") == 0) {
		if (strcmp(argv[1], "en") == 0) {
			pcie_rasdes_enable_ecnt(epc, ECNT_ALL_ON);
		} else if (strcmp(argv[1], "dis") == 0) {
			pcie_rasdes_enable_ecnt(epc, ECNT_ALL_OFF);
		} else if (strcmp(argv[1], "all") == 0) {
			int32_t i;

			for (i = 0; i < sizeof(event_group) / sizeof(struct event_group_info); i++) {
				print_ecnt_group_data(epc, event_group[i].index);
			}
		} else {
			uint8_t gp = strtol(argv[1], NULL, 0);

			print_ecnt_group_data(epc, gp);
		}
	} else if (strcmp(argv[0], "ecnt_clr") == 0) {
		if (strcmp(argv[1], "all") == 0) {
			pcie_rasdes_clear_ecnt(epc, true);
		} else {
			uint8_t gp = strtol(argv[1], NULL, 0);

			clear_ecnt_group_data(epc, gp);
		}
	} else {
		printf("Check command again\n%s", help_pcie_ecnt);
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t test_pcie_rasdes_sd(int argc, char *argv[])
{
	if (argc != 1) {
		printf("Check the command's arguments\n", help_pcie_sd);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	int32_t i;
	union pcie_ctrl_pf0_ras_des_cap_sd_status_l1lane_reg l1_lane;

	printf("\nSilicon Debug Status (Layer1 Per-lane)\n");
	printf("--------------------------------------------------------------------"
		   "--------------------------------------------------\n");
	printf(" DESKEW_POINTER | PIPE_TXELECIDLE | PIPE_RXELECIDLE | PIPE_RXVALID | "
		   "PIPE_DETECT_LANE | PIPE_RXPOLARITY | LANE_SELECT\n");
	printf("--------------------------------------------------------------------"
		   "--------------------------------------------------\n");
	for (i = 0; i < PCIE_TARGET_NUM_LANES; i++) {
		pcie_rasdes_sd_l1_lane_sel(epc, i);
		pcie_rasdes_get_sd_status(epc, SD_L1_PER_LANE, (uint32_t *)&l1_lane);
		printf("      0x%02x      |        %d        |        %d        |      %d       |"
			   "         %d        |        %d        |      %2d\n",
			   l1_lane.deskew_pointer, l1_lane.pipe_txelecidle,
			   l1_lane.pipe_rxelecidle, l1_lane.pipe_rxvalid,
			   l1_lane.pipe_detect_lane, l1_lane.pipe_rxpolarity,
			   l1_lane.lane_select);
	}

	union pcie_ctrl_pf0_ras_des_cap_sd_status_l1ltssm_reg l1_ltssm;

	pcie_rasdes_get_sd_status(epc, SD_L1_LTSSM, (uint32_t *)&l1_ltssm);
	printf("\nSilicon Debug Status (Layer1 LTSSM)\n");

	if (l1_ltssm.ltssm_variable >= DIR_SPEED_CHANGE && l1_ltssm.ltssm_variable <= EQ_DONE_16GT) {
		printf("LTSSM_VARIABLE  : %s\n", sd_ltssm_var[l1_ltssm.ltssm_variable].str);
	} else {
		printf("idle_to_rlock_transitioned : %d\n", l1_ltssm.ltssm_variable);
	}

	printf("  LANE_REVERSAL : %s\n", l1_ltssm.lane_reversal ? "O" : "X");
	printf("PIPE_POWER_DOWN : 0x%x\n", l1_ltssm.pipe_power_down);
	printf("    FRAMING_ERR : %s\n", l1_ltssm.framing_err ? "O" : "X");

	if (l1_ltssm.framing_err) {
		printf("FRAMING_ERR_PTR : 0x%x\n", l1_ltssm.framing_err_ptr);
	}

	union pcie_ctrl_pf0_ras_des_cap_sd_status_pm_reg pm;

	pcie_rasdes_get_sd_status(epc, SD_L1_LTSSM, (uint32_t *)&pm);
	printf("\nSilicon Debug Status (PM)\n");
	printf("PM_USP_PROT_STATE : 0x%x\n", pm.pm_usp_prot_state);
	printf("     PM_L0S_STATE : 0x%x\n", pm.pm_l0s_state);
	printf("     LATCHED_NFTS : 0x%x\n", pm.latched_nfts);
	printf("      L1SUB_STATE : 0x%x\n", pm.l1sub_state);
	printf("  PME_RESEND_FLAG : 0x%x\n", pm.pme_resend_flag);
	printf("PM_USP_LINK_STATE : 0x%x\n", pm.pm_usp_link_state);
	printf("PM_DSP_PROT_STATE : 0x%x\n", pm.pm_dsp_prot_state);
	printf("PM_DSP_LINK_STATE : 0x%x\n", pm.pm_dsp_link_state);

	union pcie_ctrl_pf0_ras_des_cap_sd_status_l2_reg l2;

	pcie_rasdes_get_sd_status(epc, SD_L2, (uint32_t *)&l2);
	printf("\nSilicon Debug Status (Layer2)\n");
	printf("     FC_INIT2 : 0x%x\n", l2.fc_init2);
	printf("     FC_INIT2 : 0x%x\n", l2.fc_init1);
	printf("       DLCMSM : 0x%x\n", l2.dlcmsm);
	printf("RX_ACK_SEQ_NO : 0x%x\n", l2.rx_ack_seq_no);
	printf("TX_TLP_SEQ_NO : 0x%x\n", l2.tx_tlp_seq_no);

	union pcie_ctrl_pf0_ras_des_cap_sd_status_l3fc_reg l3fc;

	pcie_rasdes_get_sd_status(epc, SD_L3_FC, (uint32_t *)&l3fc);
	printf("\nSilicon Debug Status (Layer3 FC)\n");
	printf("          CREDIT_DATA1 : 0x%x\n", l3fc.credit_data1);
	printf("          CREDIT_DATA0 : 0x%x\n", l3fc.credit_data0);
	printf("         CREDIT_SEL_HD : 0x%x\n", l3fc.credit_sel_hd);
	printf("   CREDIT_SEL_TLP_TYPE : 0x%x\n", l3fc.credit_sel_tlp_type);
	printf("CREDIT_SEL_CREDIT_TYPE : 0x%x\n", l3fc.credit_sel_credit_type);
	printf("         CREDIT_SEL_VC : 0x%x\n", l3fc.credit_sel_vc);

	union pcie_ctrl_pf0_ras_des_cap_sd_status_l3_reg l3;

	pcie_rasdes_get_sd_status(epc, SD_L3, (uint32_t *)&l3);
	printf("\nSilicon Debug Status (Layer3)\n");
	printf(" MFTLP_STATUS : 0x%x\n", l3.mftlp_status);
	printf("MFTLP_POINTER : 0x%x\n", l3.mftlp_pointer);

	return RL_OK;
}

static void print_sd_eq_status(struct pcie_epc *epc, uint32_t lane_sel, uint32_t rate_sel)
{
	pcie_rasdes_sd_eq_lane_sel(epc, lane_sel);
	pcie_rasdes_sd_eq_rate_sel(epc, rate_sel);

	printf("\n============================\n");
	printf(" Lane number: %d, Rate: Gen%d\n", lane_sel, GEN3_BASE_VAL + rate_sel);
	printf("============================\n");

	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status1_reg eq_status1;

	pcie_rasdes_get_sd_eq_status(epc, SD_EQ_STATUS1, (uint32_t *)&eq_status1);

	printf("\nSD EQ Status1\n");
	printf("Prefix: eq_\n");
	printf("------------------------------------------------------------------------------------\n");
	printf(" reject_event | rulec_viol | ruleb_viol | rulea_viol | ruled_viol | conv_info | seq\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("       %d      |      %d     |      %d     |      %d     |      %d     |     %2d    |  %d\n",
		   eq_status1.eq_reject_event,
		   eq_status1.eq_rulec_violation,
		   eq_status1.eq_ruleb_violation,
		   eq_status1.eq_rulea_violation,
		   eq_status1.eq_ruled_violation,
		   eq_status1.eq_convergence_info,
		   eq_status1.eq_sequence);

	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status2_reg eq_status2;

	pcie_rasdes_get_sd_eq_status(epc, SD_EQ_STATUS2, (uint32_t *)&eq_status2);

	printf("\nSD EQ Status2\n");
	printf("Prefix: eq_local_\n");
	printf("------------------------------------------------------\n");
	printf("   fom  | rx_hint | post_cursor | cursor | pre_cursor\n");
	printf("------------------------------------------------------\n");
	printf(" %6d | %6d  |    %6d   | %6d |   %6d\n",
		   eq_status2.eq_local_fom_value,
		   eq_status2.eq_local_rx_hint_or_eq_local_2nd_pre_cursor,
		   eq_status2.eq_local_post_cursor,
		   eq_status2.eq_local_cursor,
		   eq_status2.eq_local_pre_cursor);

	union pcie_ctrl_pf0_ras_des_cap_sd_eq_status3_reg eq_status3;

	pcie_rasdes_get_sd_eq_status(epc, SD_EQ_STATUS3, (uint32_t *)&eq_status3);

	printf("\nSD EQ Status3\n");
	printf("Prefix: eq_remote_\n");
	printf("-----------------------------------------------------\n");
	printf("   fs   |   lf   | post_cursor | cursor | pre_cursor\n");
	printf("-----------------------------------------------------\n");
	printf(" %6d | %6d |    %6d   | %6d |   %6d\n",
		   eq_status3.eq_remote_fs,
		   eq_status3.eq_remote_lf,
		   eq_status3.eq_remote_post_cursor,
		   eq_status3.eq_remote_cursor,
		   eq_status3.eq_remote_pre_cursor);
}

int32_t test_pcie_rasdes_sd_eq(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Check the number of arguments\n%s", help_pcie_sd_eq);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	uint32_t lane_sel, rate_sel;
	int i, j;

	if (strcmp(argv[1], "all") == 0) {
		if (strcmp(argv[2], "all") == 0) {
			for (i = 0; i < PCIE_TARGET_NUM_LANES; i++) {
				for (j = SD_EQ_RATE_GEN3; j <= SD_EQ_RATE_GEN5; j++) {
					print_sd_eq_status(epc, i, j);
				}
			}
		} else {
			rate_sel = strtol(argv[2], NULL, 0);

			for (i = 0; i < PCIE_TARGET_NUM_LANES; i++) {
				print_sd_eq_status(epc, i, rate_sel);
			}
		}
	} else {
		if (strcmp(argv[2], "all") == 0) {
			lane_sel = strtol(argv[1], NULL, 0);

			for (i = SD_EQ_RATE_GEN3; i <= SD_EQ_RATE_GEN5; i++) {
				print_sd_eq_status(epc, lane_sel, i);
			}
		} else {
			lane_sel = strtol(argv[1], NULL, 0);
			rate_sel = strtol(argv[2], NULL, 0);

			if (lane_sel >= PCIE_TARGET_NUM_LANES || rate_sel > SD_EQ_RATE_GEN5) {
				printf("%s: check the arguments\n", __func__);
				return RL_BADARG;
			}

			print_sd_eq_status(epc, lane_sel, rate_sel);
		}
	}

	return RL_OK;
}
