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

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "hbm3.h"
#include "icon.h"
#include "hbm3ephy.h"

#define WDR_SFR_MAX 19
#define TX_LANE_MAX 7

lane_map tx_lane[WDR_SFR_MAX][TX_LANE_MAX] = {
	{
		{0, "DBI7", 9, DWORD1_BYTE3},
		{5, "DBI6", 9, DWORD1_BYTE2},
		{10, "DQ63", 8, DWORD1_BYTE3},
		{15, "DQ55", 8, DWORD1_BYTE2},
		{20, "DQ62", 7, DWORD1_BYTE3},
		{25, "DQ54", 7, DWORD1_BYTE2},
		{30, "DQ61", 6, DWORD1_BYTE3}
	}, // RD_WDR[0]
	{
		{35, "DQ53", 6, DWORD1_BYTE2},
		{40, "DQ60", 5, DWORD1_BYTE3},
		{45, "DQ52", 5, DWORD1_BYTE2},
		{50, "RD3", 0xF, REDUNDANT},
		{55, "RDQS1", 0xF, UNREPAIRABLE},
		{62, "DPAR1", 0xF, UNREPAIRABLE},
		{0xff, "dummy", 0xff, NA}
	}, // RD_WDR[1]
	{
		{67, "DQ59", 4, DWORD1_BYTE3},
		{72, "DQ51", 4, DWORD1_BYTE2},
		{77, "DQ58", 3, DWORD1_BYTE3},
		{82, "DQ50", 3, DWORD1_BYTE2},
		{87, "DQ57", 2, DWORD1_BYTE3},
		{92, "DQ49", 2, DWORD1_BYTE2},
		{0xff, "dummy", 0xff, NA}
	}, // RD_WDR[2]
	{
		{97, "DQ56", 1, DWORD1_BYTE3},
		{102, "DQ48", 1, DWORD1_BYTE2},
		{107, "SEV3", 0, DWORD1_BYTE3},
		{112, "SEV2", 0, DWORD1_BYTE2},
		{117, "ECC3", 0, DWORD1_BYTE1},
		{122, "ECC2", 0, DWORD1_BYTE0},
		{127, "DQ40", 1, DWORD1_BYTE1}
	}, // RD_WDR[3]
	{
		{132, "DQ32", 1, DWORD1_BYTE0},
		{137, "DQ41", 2, DWORD1_BYTE1},
		{142, "DQ33", 2, DWORD1_BYTE0},
		{147, "DQ42", 3, DWORD1_BYTE1},
		{152, "DQ34", 3, DWORD1_BYTE0},
		{157, "DQ43", 4, DWORD1_BYTE1},
		{0xff, "dummy", 0xff, NA}
	}, // RD_WDR[4]
	{
		{162, "DQ35", 4, DWORD1_BYTE0},
		{167, "DERR1", 0xF, UNREPAIRABLE},
		{172, "WDQS1", 0xF, UNREPAIRABLE},
		{179, "RD2", 0xF, REDUNDANT},
		{184, "DQ44", 5, DWORD1_BYTE1},
		{189, "DQ36", 5, DWORD1_BYTE0},
		{0xff, "dummy", 0xff, NA}
	}, // RD_WDR[5]
	{
		{194, "DQ45", 6, DWORD1_BYTE1},
		{199, "DQ37", 6, DWORD1_BYTE0},
		{204, "DQ46", 7, DWORD1_BYTE1},
		{209, "DQ38", 7, DWORD1_BYTE0},
		{214, "DQ47", 8, DWORD1_BYTE1},
		{219, "DQ39", 8, DWORD1_BYTE0},
		{0xff, "dummy", 0xff, NA}
	}, // RD_WDR[6]
	{
		{224, "DBI5", 9, DWORD1_BYTE1},
		{229, "DBI4", 9, DWORD1_BYTE0},
		{234, "R1", 1, AWORD_RA},
		{239, "C0", 0, AWORD_CA},
		{244, "R2", 2, AWORD_RA},
		{249, "C1", 1, AWORD_CA},
		{254, "R3", 3, AWORD_RA}
	},  // RD_WDR[7]
	{
		{259, "C2", 2, AWORD_CA},
		{264, "R0", 0, AWORD_RA},
		{269, "C3", 3, AWORD_CA},
		{274, "R4", 4, AWORD_RA},
		{279, "C4", 4, AWORD_CA},
		{284, "R5", 5, AWORD_RA},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[8]
	{
		{289, "CK_t", 0xF, UNREPAIRABLE},
		{296, "C5", 5, AWORD_CA},
		{301, "R6", 6, AWORD_RA},
		{306, "C6", 6, AWORD_CA},
		{311, "R7", 7, AWORD_RA},
		{316, "C7", 7, AWORD_CA},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[9]
	{
		{321, "R8", 8, AWORD_RA},
		{326, "APAR", 8, AWORD_CA},
		{331, "R9", 9, AWORD_RA},
		{336, "ARFU", 9, AWORD_CA},
		{341, "AERR", 0xF, UNREPAIRABLE},
		{346, "RA", 0xF, REDUNDANT},
		{351, "DBI3", 9, DWORD0_BYTE3}
	},  // RD_WDR[10]
	{
		{356, "DBI2", 9, DWORD0_BYTE2},
		{361, "DQ31", 8, DWORD0_BYTE3},
		{366, "DQ23", 8, DWORD0_BYTE2},
		{371, "DQ30", 7, DWORD0_BYTE3},
		{376, "DQ22", 7, DWORD0_BYTE2},
		{381, "DQ29", 6, DWORD0_BYTE3},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[11]
	{
		{386, "DQ21", 6, DWORD0_BYTE2},
		{391, "DQ28", 5, DWORD0_BYTE3},
		{396, "DQ20", 5, DWORD0_BYTE2},
		{401, "RD1", 0xF, REDUNDANT},
		{406, "RDQS0", 0xF, UNREPAIRABLE},
		{413, "DPAR0", 0xF, UNREPAIRABLE},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[12]
	{
		{418, "DQ27", 4, DWORD0_BYTE3},
		{423, "DQ19", 4, DWORD0_BYTE2},
		{428, "DQ26", 3, DWORD0_BYTE3},
		{433, "DQ18", 3, DWORD0_BYTE2},
		{438, "DQ25", 2, DWORD0_BYTE3},
		{443, "DQ17", 2, DWORD0_BYTE2},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[13]
	{
		{448, "DQ24", 1, DWORD0_BYTE3},
		{453, "DQ16", 1, DWORD0_BYTE2},
		{458, "SEV1", 0, DWORD0_BYTE3},
		{463, "SEV0", 0, DWORD0_BYTE2},
		{468, "ECC1", 0, DWORD0_BYTE1},
		{473, "ECC0", 0, DWORD0_BYTE0},
		{478, "DQ8", 1, DWORD0_BYTE1}
	},  // RD_WDR[14]
	{
		{483, "DQ0", 1, DWORD0_BYTE0},
		{488, "DQ9", 2, DWORD0_BYTE1},
		{493, "DQ1", 2, DWORD0_BYTE0},
		{498, "DQ10", 3, DWORD0_BYTE1},
		{503, "DQ2", 3, DWORD0_BYTE0},
		{508, "DQ11", 4, DWORD0_BYTE1},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[15]
	{
		{513, "DQ3", 4, DWORD0_BYTE0},
		{518, "DERR0", 0xF, UNREPAIRABLE},
		{523, "WDQS0", 0xF, UNREPAIRABLE},
		{530, "RD0", 0xF, REDUNDANT},
		{535, "DQ12", 5, DWORD0_BYTE1},
		{540, "DQ4", 5, DWORD0_BYTE0},
		{0xff, "dummy", 0xff, NA}
	},  // RD_WDR[16]
	{
		{545, "DQ13", 6, DWORD0_BYTE1},
		{550, "DQ5", 6, DWORD0_BYTE0},
		{555, "DQ14", 7, DWORD0_BYTE1},
		{560, "DQ6", 7, DWORD0_BYTE0},
		{565, "DQ15", 8, DWORD0_BYTE1},
		{570, "DQ7", 8, DWORD0_BYTE0},
		{575, "DBI1", 9, DWORD0_BYTE1}
	},  // RD_WDR[17]
	{
		{580, "DBI0", 9, DWORD0_BYTE0},
		{0xff, "dummy", 0xff, NA},
		{0xff, "dummy", 0xff, NA},
		{0xff, "dummy", 0xff, NA},
		{0xff, "dummy", 0xff, NA},
		{0xff, "dummy", 0xff, NA},
		{0xff, "dummy", 0xff, NA}
	}  // RD_WDR[18]
};

lane_map rx_lane[4][32] = {
	{
		{0, "ECC0", 0, DWORD0_BYTE0},
		{1, "DQ0", 1, DWORD0_BYTE0},
		{2, "DQ1", 2, DWORD0_BYTE0},
		{3, "DQ2", 3, DWORD0_BYTE0},
		{4, "DQ3", 4, DWORD0_BYTE0},
		{5, "DPAR0", 0xf, UNREPAIRABLE},
		{6, "RD0", 0xf, REDUNDANT},
		{7, "DQ4", 5, DWORD0_BYTE0},
		{8, "DQ5", 6, DWORD0_BYTE0},
		{9, "DQ6", 7, DWORD0_BYTE0},
		{10, "DQ7", 8, DWORD0_BYTE0},
		{11, "DBI0", 9, DWORD0_BYTE0},
		{12, "ECC1", 0, DWORD0_BYTE1},
		{13, "DQ8", 1, DWORD0_BYTE1},
		{14, "DQ9", 2, DWORD0_BYTE1},
		{15, "DQ10", 3, DWORD0_BYTE1},
		{16, "DQ11", 4, DWORD0_BYTE1},
		{17, "WDQS0_t", 0xf, UNREPAIRABLE},
		{18, "WDQS0_c", 0xf, UNREPAIRABLE},
		{19, "DQ12", 5, DWORD0_BYTE1},
		{20, "DQ13", 6, DWORD0_BYTE1},
		{21, "DQ14", 7, DWORD0_BYTE1},
		{22, "DQ15", 8, DWORD0_BYTE1},
		{23, "DBI1", 9, DWORD0_BYTE1},
		{24, "SEV0", 0, DWORD0_BYTE2},
		{25, "DQ16", 1, DWORD0_BYTE2},
		{26, "DQ17", 2, DWORD0_BYTE2},
		{27, "DQ18", 3, DWORD0_BYTE2},
		{28, "DQ19", 4, DWORD0_BYTE2},
		{29, "RDQS0_t", 0xf, UNREPAIRABLE},
		{30, "RDQS0_c", 0xf, UNREPAIRABLE},
		{31, "DQ20", 5, DWORD0_BYTE2}
	}, // RD_WDR[0]
	{
		{32, "DQ21", 6, DWORD0_BYTE2},
		{33, "DQ22", 7, DWORD0_BYTE2},
		{34, "DQ23", 8, DWORD0_BYTE2},
		{35, "DBI2", 9, DWORD0_BYTE2},
		{36, "SEV1", 0, DWORD0_BYTE3},
		{37, "DQ24", 1, DWORD0_BYTE3},
		{38, "DQ25", 2, DWORD0_BYTE3},
		{39, "DQ26", 3, DWORD0_BYTE3},
		{40, "DQ27", 4, DWORD0_BYTE3},
		{41, "DERR0", 0xf, UNREPAIRABLE},
		{42, "RD1", 0xf, REDUNDANT},
		{43, "DQ28", 5, DWORD0_BYTE3},
		{44, "DQ29", 6, DWORD0_BYTE3},
		{45, "DQ30", 7, DWORD0_BYTE3},
		{46, "DQ31", 8, DWORD0_BYTE3},
		{47, "DBI3", 9, DWORD0_BYTE3},
		{48, "C0", 0, AWORD_CA},
		{49, "C1", 1, AWORD_CA},
		{50, "C2", 2, AWORD_CA},
		{51, "C3", 3, AWORD_CA},
		{52, "C4", 4, AWORD_CA},
		{53, "CK_t", 0xf, UNREPAIRABLE},
		{54, "C5", 5, AWORD_CA},
		{55, "C6", 6, AWORD_CA},
		{56, "C7", 7, AWORD_CA},
		{57, "APAR", 8, AWORD_CA},
		{58, "ARFU", 9, AWORD_CA},
		{59, "RA", 0xf, REDUNDANT},
		{60, "R1", 1, AWORD_RA},
		{61, "R2", 2, AWORD_RA},
		{62, "R3", 3, AWORD_RA},
		{63, "R0", 0, AWORD_RA}
	}, // RD_WDR[1]
	{
		{64, "R4", 4, AWORD_RA},
		{65, "R5", 5, AWORD_RA},
		{66,	"CK_c",	0xf, UNREPAIRABLE},
		{67, "R6", 6, AWORD_RA},
		{68, "R7", 7, AWORD_RA},
		{69, "R8", 8, AWORD_RA},
		{70, "R9", 9, AWORD_RA},
		{71, "AERR", 0xf, UNREPAIRABLE},
		{72, "ECC2", 0, DWORD1_BYTE0},
		{73, "DQ32", 1, DWORD1_BYTE0},
		{74, "DQ33", 2, DWORD1_BYTE0},
		{75, "DQ34", 3, DWORD1_BYTE0},
		{76, "DQ35", 4, DWORD1_BYTE0},
		{77, "DPAR1", 0xf, UNREPAIRABLE},
		{78, "RD2", 0xf, REDUNDANT},
		{79, "DQ36", 5, DWORD1_BYTE0},
		{80, "DQ37", 6, DWORD1_BYTE0},
		{81, "DQ38", 7, DWORD1_BYTE0},
		{82, "DQ39", 8, DWORD1_BYTE0},
		{83, "DBI4", 9, DWORD1_BYTE0},
		{84, "ECC3", 0, DWORD1_BYTE1},
		{85, "DQ40", 1, DWORD1_BYTE1},
		{86, "DQ41", 2, DWORD1_BYTE1},
		{87, "DQ42", 3, DWORD1_BYTE1},
		{88, "DQ43", 4, DWORD1_BYTE1},
		{89, "WDQS1_t", 0xf, UNREPAIRABLE},
		{90, "WDQS1_c", 0xf,	UNREPAIRABLE},
		{91, "DQ44", 5, DWORD1_BYTE1},
		{92, "DQ45", 6, DWORD1_BYTE1},
		{93, "DQ46", 7, DWORD1_BYTE1},
		{94, "DQ47", 8, DWORD1_BYTE1},
		{95, "DBI5", 9, DWORD1_BYTE1}
	}, // RD_WDR[2]
	{
		{96, "SEV2", 0, DWORD1_BYTE2},
		{97, "DQ48", 1, DWORD1_BYTE2},
		{98, "DQ49", 2, DWORD1_BYTE2},
		{99, "DQ50", 3, DWORD1_BYTE2},
		{100, "DQ51", 4, DWORD1_BYTE2},
		{101, "RDQS1_t", 0xf, UNREPAIRABLE},
		{102, "RDQS1_c", 0xf, UNREPAIRABLE},
		{103, "DQ52", 5, DWORD1_BYTE2},
		{104, "DQ53", 6, DWORD1_BYTE2},
		{105, "DQ54", 7, DWORD1_BYTE2},
		{106, "DQ55", 8, DWORD1_BYTE2},
		{107, "DBI6", 9, DWORD1_BYTE2},
		{108, "SEV3", 0, DWORD1_BYTE3},
		{109, "DQ56", 1, DWORD1_BYTE3},
		{110, "DQ57", 2, DWORD1_BYTE3},
		{111, "DQ58", 3, DWORD1_BYTE3},
		{112, "DQ59", 4, DWORD1_BYTE3},
		{113, "DERR1", 0xf, UNREPAIRABLE},
		{114, "RD3", 0xf, REDUNDANT},
		{115, "DQ60", 5, DWORD1_BYTE3},
		{116, "DQ61", 6, DWORD1_BYTE3},
		{117, "DQ62", 7, DWORD1_BYTE3},
		{118, "DQ63", 8, DWORD1_BYTE3},
		{119, "DBI7", 9, DWORD1_BYTE3},
		{120, "dummy", 0xf, NA},
		{121, "dummy", 0xf, NA},
		{122, "dummy", 0xf, NA},
		{123, "dummy", 0xf, NA},
		{124, "dummy", 0xf, NA},
		{125, "dummy", 0xf, NA},
		{126, "dummy", 0xf, NA},
		{127, "dummy", 0xf, NA}
	} // RD_WDR[3]
};

void wait_for_test_instruction_req_done(struct hbm3_config *cfg)
{
	uint32_t rdata;

	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);
}

void wait_for_test_instruction_req_done_clear(struct hbm3_config *cfg)
{
	uint32_t rdata;

	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x0);
}

uint32_t icon_test_instruction_req(struct hbm3_config *cfg, uint8_t ch,
								   enum ICON_INSTRUCTION_REQ_BIT req_bit)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	udelay(1);

	cfg->icon_base->test_instruction_req1.ch_select = ch;

	cfg->icon_base->test_instruction_req0.val |= (1 << req_bit);
	udelay(1);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.val &= ~(1 << req_bit);
	udelay(1);
	wait_for_test_instruction_req_done_clear(cfg);

	return 0;
}

uint32_t icon_sw_instruction_req(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	return 0;
}

uint32_t icon_hbm_reset(struct hbm3_config *cfg)
{
	uint32_t rdata;

	/* Initiate the reset */
	cfg->icon_base->wr_wdr0.wr_wdr0 = 1;

	cfg->icon_base->test_instruction_req0.hbm_reset_req = 1;
	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);
	cfg->icon_base->test_instruction_req0.hbm_reset_req = 0;
	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x0);

	/* Finish the reset */
	cfg->icon_base->wr_wdr0.wr_wdr0 = 0;

		cfg->icon_base->test_instruction_req0.hbm_reset_req = 1;
	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);
	cfg->icon_base->test_instruction_req0.hbm_reset_req = 0;
	do {
		rdata = cfg->icon_base->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x0);

	return 0;
}

uint32_t icon_lane_repair(struct hbm3_config *cfg, uint8_t ch, uint8_t inst, uint8_t idx, uint32_t rep_lane)
{
	uint32_t wdr0_val = 0xffffffff;
	uint8_t wdr1_val = 0xff;
	uint8_t repair_inst;

	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	cfg->icon_base->io_ctrl0.ctrl_io_en_apb = 0x1;

	cfg->icon_base->test_instruction_req1.ch_select = ch;

	if (inst == HARD_LANE_REPAIR)
		repair_inst = ICON_INSTRUCTION_REQ_HARD_LANE_REPAIR_WRITE;
	else
		repair_inst = ICON_INSTRUCTION_REQ_SOFT_LANE_REPAIR_WRITE;

	if (idx < DWORD1_BYTE2) {
		wdr0_val = 0xffffffff;
		wdr0_val &= ~(0xffu << (idx * 4));
		wdr0_val |= (rep_lane & 0xffu) << (idx * 4);
		wdr1_val = 0xff;
	} else { // DWORD1_BYTE2, DWORD1_BYTE3
		wdr0_val = 0xffffffff;
		wdr1_val = 0xff;
		wdr1_val &= ~(0xffu << 0);
		wdr1_val = (rep_lane & 0xff);
	}
	cfg->icon_base->wr_wdr0.wr_wdr0 = wdr0_val;
	cfg->icon_base->wr_wdr1.wr_wdr1 = wdr1_val;

	icon_test_instruction_req(cfg, ch, repair_inst);

	udelay(1 * 10);

	return 0;
}

int32_t icon_rx_lane_search(struct hbm3_config *cfg, uint8_t ch, uint32_t idx,
							uint32_t compare_result, uint8_t *lane_result)
{
	uint8_t bit_base = 0, err_bit_pos = 0, shift_cnt, group_idx = 0;
	uint32_t ret = 0;

	bit_base = (idx * 32);
	for (shift_cnt = 0; shift_cnt < 32; shift_cnt++) {
		if (((compare_result >> shift_cnt) & 0x1) == 0x1) {
			err_bit_pos = bit_base + shift_cnt;
			if (err_bit_pos == rx_lane[idx][shift_cnt].bit_pos) {
				printf("CH[%d] bit pos = %d, lane = %s, repair_pos = %d, group = %d\n",
					   ch, rx_lane[idx][shift_cnt].bit_pos, rx_lane[idx][shift_cnt].lane,
					   rx_lane[idx][shift_cnt].repair_pos, rx_lane[idx][shift_cnt].dword_group);

				if (rx_lane[idx][shift_cnt].dword_group == UNREPAIRABLE) {
					printf("rx lane is UNREPAIRABLE\n");
					return HBM_UNREPAIRABLE;
				} else if (rx_lane[idx][shift_cnt].dword_group == NA) {
					printf("NA, Don't care\n");
				} else if (rx_lane[idx][shift_cnt].dword_group == REDUNDANT) {
					printf("REDUNDANT, Don't care\n");
				} else {
					group_idx = rx_lane[idx][shift_cnt].dword_group;
					if (lane_result[group_idx] != 0xF &&
						lane_result[group_idx] != rx_lane[idx][shift_cnt].repair_pos) {
						printf("Only 1 pin can repair for each dword group\n");
						return HBM_UNREPAIRABLE;
					} else {
						lane_result[group_idx] = (rx_lane[idx][shift_cnt].repair_pos & 0xf);
						ret++;
					}
				}
			}
		}
	}
	return ret;
}

int32_t icon_rx_extest(struct hbm3_config *cfg, uint8_t ch, uint8_t mode, uint8_t *lane_result)
{
	uint64_t icon_addr = (uint64_t)cfg->icon_base;
	uint32_t rdata, idx, sfr_idx = 0, compare_result = 0;
	int32_t search_result = 0, ret = 0;

	uint32_t extest_rx_io_direct[WDR_SFR_MAX] = {
		0x84210842, 0x81084210, 0x21084210, 0x08421084,
		0x42108421, 0x42102108, 0x10842108, 0x84210842,
		0x21084210, 0x21084204, 0x08421084, 0x42108421,
		0x40842108, 0x10842108, 0x84210842, 0x21084210,
		0x21081084, 0x08421084, 0x00000021
	};

	uint32_t extest_rx0_pattern[4] = {
		0x40040000, 0x00000000, 0x04000004, 0x00000040
	};
	uint32_t extest_rx1_pattern[4] = {
		0xbffbffff, 0xffffffff, 0xfbfffffb, 0x00ffffbf
	};

	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x1;
	cfg->phy_base[ch]->ctrl_io_con0.ctrl_ieee_sel_apb = 0x1;
	cfg->phy_base[ch]->ctrl_io_con0.ieee_phy_ctrl_apb = 0x1;
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	for (sfr_idx = 0; sfr_idx < WDR_SFR_MAX; sfr_idx++) {
		if (mode == RX0_EXTEST) {
			WR_WDR_IDX(icon_addr, sfr_idx, 0x0);
		} else { // RX1_EXTEST
			WR_WDR_IDX(icon_addr, sfr_idx, extest_rx_io_direct[sfr_idx]);
		}
	}

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con1.wir_width = 0x2;
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = 0x249;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR_WR_WDR; // 0x1
	cfg->icon_base->icon_ctrl_con0.sw_wir = ICON_WIR_HBM_RESET; // 0x5

	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x1;
	wait_for_test_instruction_req_done(cfg);
	cfg->phy_base[ch]->ctrl_io_con0.mode_mux_apb = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;
	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x0;
	cfg->icon_base->icon_ctrl_con1.wir_width = 0xC;
	cfg->icon_base->test_instruction_req0.extest_rx_req = 0x1;
	udelay(1 * 10);
	wait_for_test_instruction_req_done(cfg);
	cfg->icon_base->test_instruction_req0.extest_rx_req = 0x0;
	udelay(1 * 10);
	wait_for_test_instruction_req_done_clear(cfg);

	for (idx = 0; idx < 4; idx++) {
		compare_result = 0;

		rdata = RD_WDR_CH(icon_addr, idx, ch);
		udelay(1 * 10);
		if (mode == RX0_EXTEST) {
			compare_result = (rdata ^ extest_rx0_pattern[idx]);
		} else { // RX1_TXTEST
			compare_result = (rdata ^ extest_rx1_pattern[idx]);
		}

		if (compare_result != 0x00000000) {
			search_result = icon_rx_lane_search(cfg, ch, idx, compare_result, lane_result);

			if (search_result == HBM_UNREPAIRABLE) {
				printf("CH[%d] Detect UNREPAIRABLE lane\n", ch);
				return HBM_UNREPAIRABLE;
			}
			ret += search_result;
		}
	}

	cfg->phy_base[ch]->ctrl_io_con0.ieee_phy_ctrl_apb = 0x0;
	cfg->phy_base[ch]->ctrl_io_con0.ctrl_ieee_sel_apb = 0x0;
	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x0;
	cfg->phy_base[ch]->ctrl_io_con0.mode_mux_apb = 0x0;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	if (ret)
		printf("RX%d EXTEST return = %d\n", mode - RX0_EXTEST, ret);

	return ret;
}

int32_t icon_tx_lane_search(struct hbm3_config *cfg, uint8_t ch, uint32_t idx,
							uint32_t compare_result, uint8_t *lane_result)
{
	uint8_t bit_base = 0, err_bit_pos = 0, shift_cnt, tx_array, group_idx = 0;
	uint32_t ret = 0;

	bit_base = (idx * 32);
	for (shift_cnt = 0; shift_cnt < 32; shift_cnt++) {
		if (((compare_result >> shift_cnt) & 0x1) == 0x1) {
			err_bit_pos = bit_base + shift_cnt;
			for (tx_array = 0; tx_array < TX_LANE_MAX; tx_array++) {
				if (err_bit_pos == tx_lane[idx][tx_array].bit_pos) {
					printf("CH[%d] bit pos = %d, lane = %s, repair_pos = %d, group = %d\n",
						   ch, tx_lane[idx][tx_array].bit_pos, tx_lane[idx][tx_array].lane,
						   tx_lane[idx][tx_array].repair_pos, tx_lane[idx][tx_array].dword_group);

					if (tx_lane[idx][tx_array].dword_group == UNREPAIRABLE) {
						printf("tx lane is UNREPAIRABLE\n");
						return HBM_UNREPAIRABLE;
					} else if (tx_lane[idx][tx_array].dword_group == NA) {
						printf("NA, Don't care\n");
					} else if (tx_lane[idx][tx_array].dword_group == REDUNDANT) {
						printf("REDUNDANT lane, Don't care\n");
					} else {
						group_idx = (tx_lane[idx][tx_array].dword_group);
						if (lane_result[group_idx] != 0xF &&
							lane_result[group_idx] != tx_lane[idx][tx_array].repair_pos) {
							printf("Only 1 pin can repair for each dword group\n");
							return HBM_UNREPAIRABLE;
						} else {
							lane_result[group_idx] = (tx_lane[idx][tx_array].repair_pos & 0xf);
							ret++;
						}
					}
				}
			}
		}
	}
	return ret;
}

int32_t icon_tx_extest(struct hbm3_config *cfg, uint8_t ch, uint8_t mode, uint8_t *lane_result)
{
	uint64_t icon_addr = (uint64_t)cfg->icon_base;
	uint32_t rdata, idx, sfr_idx = 0, compare_result = 0;
	int32_t search_result = 0, ret = 0;

	uint32_t extest_tx_io_direct[WDR_SFR_MAX] = {
		0x08421084, 0x02108421, 0x42108421, 0x10842108,
		0x84210842, 0x84204210, 0x21084210, 0x08421084,
		0x42108421, 0x42108408, 0x10842108, 0x84210842,
		0x81084210, 0x21084210, 0x08421084, 0x42108421,
		0x42102108, 0x10842108, 0x00000042
	};
	uint32_t extest_tx1_expected[WDR_SFR_MAX] = {
		0x42108421, 0x40842108, 0x10842108, 0x84210842,
		0x21084210, 0x21081084, 0x08421084, 0x42108421,
		0x10842108, 0x10842102, 0x84210842, 0x21084210,
		0x20421084, 0x08421084, 0x42108421, 0x10842108,
		0x10840842, 0x84210842, 0x00000010,
	};
	uint32_t extest_tx0_pattern[4] = {
		0x40040000, 0x00000000, 0x04000004, 0x00000040
	};
	uint32_t extest_tx1_pattern[4] = {
		0xbffbffff, 0xffffffff, 0xfbfffffb, 0x03ffffbf
	};

	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x1;
	cfg->phy_base[ch]->ctrl_io_con0.ctrl_ieee_sel_apb = 0x1;
	cfg->phy_base[ch]->ctrl_io_con0.ieee_phy_ctrl_apb = 0x1;
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	for (sfr_idx = 0; sfr_idx < WDR_SFR_MAX; sfr_idx++) {
		WR_WDR_IDX(icon_addr, sfr_idx, extest_tx_io_direct[sfr_idx]);
	}

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con1.wir_width = 0x2;
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = 0x249;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR_WR_WDR; // 0x1
	cfg->icon_base->icon_ctrl_con0.sw_wir = ICON_WIR_HBM_RESET; // 0x5

	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x1;
	wait_for_test_instruction_req_done(cfg);

	cfg->phy_base[ch]->ctrl_io_con0.mode_mux_apb = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	cfg->icon_base->icon_ctrl_con0.sw_mode_req = 0x0;
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x0;
	cfg->icon_base->icon_ctrl_con1.wir_width = 0xC;

	if (mode == TX0_EXTEST) {
		cfg->icon_base->wr_wdr0.wr_wdr0 = extest_tx0_pattern[0];
		cfg->icon_base->wr_wdr1.wr_wdr1 = extest_tx0_pattern[1];
		cfg->icon_base->wr_wdr2.wr_wdr2 = extest_tx0_pattern[2];
		cfg->icon_base->wr_wdr3.wr_wdr3 = extest_tx0_pattern[3];
	} else { // TX1_TXTEST
		cfg->icon_base->wr_wdr0.wr_wdr0 = extest_tx1_pattern[0];
		cfg->icon_base->wr_wdr1.wr_wdr1 = extest_tx1_pattern[1];
		cfg->icon_base->wr_wdr2.wr_wdr2 = extest_tx1_pattern[2];
		cfg->icon_base->wr_wdr3.wr_wdr3 = extest_tx1_pattern[3];
	}

	cfg->icon_base->test_instruction_req0.extest_tx_req = 0x1;
	udelay(1 * 10);
	wait_for_test_instruction_req_done(cfg);

	cfg->icon_base->test_instruction_req0.extest_tx_req = 0x0;
	udelay(1 * 10);
	wait_for_test_instruction_req_done_clear(cfg);

	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x1;
	cfg->icon_base->icon_ctrl_con1.wir_width = 0x2;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = RD_WDR; // 0x4
	udelay(1 * 10);
	icon_sw_instruction_req(cfg);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	for (idx = 0; idx < WDR_SFR_MAX; idx++) {
		compare_result = 0;

		rdata = RD_WDR_CH(icon_addr, idx, ch);
		udelay(1 * 10);

		if (mode == TX0_EXTEST) {
			compare_result = (rdata ^ 0x00000000);
		} else { // TX1_EXTEST
			compare_result = (rdata ^ extest_tx1_expected[idx]);
		}

		if (compare_result != 0x00000000) {
			search_result = icon_tx_lane_search(cfg, ch,  idx, compare_result, lane_result);

			if (search_result == HBM_UNREPAIRABLE) {
				printf("CH[%d] Detect UNREPAIRABLE lane\n", ch);
				return HBM_UNREPAIRABLE;
			}
			ret += search_result;
		}
	}

	cfg->icon_base->icon_ctrl_con1.wir_width = 0xC;
	cfg->phy_base[ch]->ctrl_io_con0.ieee_phy_ctrl_apb = 0x0;
	cfg->phy_base[ch]->ctrl_io_con0.ctrl_ieee_sel_apb = 0x0;
	cfg->icon_base->icon_ctrl_con0.phy_ctrl_mode = 0x0;
	cfg->phy_base[ch]->ctrl_io_con0.mode_mux_apb = 0x0;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	if (ret)
		printf("TX%d EXTEST return = %d\n", mode - TX0_EXTEST, ret);

	return ret;
}

int32_t hbm3_lane_repair(struct hbm3_config *cfg, uint8_t ch, uint8_t rep_lane[REDUNDANT])
{
	uint8_t idx, lane_wdr;

	for (idx = 0; idx < 10; idx += 2) {
		lane_wdr = 0;
		if (rep_lane[idx] != 0xf && rep_lane[idx + 1] != 0xf) {
			printf("ch[%d] Unrepairable\n", ch);
			return HBM_UNREPAIRABLE;
		} else if (rep_lane[idx] != 0xf || rep_lane[idx + 1] != 0xf) {
			printf("rep_lane[%d][%d] = 0x%x, rep_lane[%d][%d] = 0x%x\n",
				   ch, idx, rep_lane[idx], ch, idx + 1, rep_lane[idx + 1]);
			printf("CH[%d] Repairable\n", ch);
			lane_wdr = (((rep_lane[idx + 1] & 0xf) << 4)  | ((rep_lane[idx] & 0xf) << 0));
			icon_lane_repair(cfg, ch, SOFT_LANE_REPAIR, idx, lane_wdr);
		}
	}

	cfg->phy_base[ch]->remap_con1.dword0_remap_byte0 = rep_lane[DWORD0_BYTE0] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword0_remap_byte1 = rep_lane[DWORD0_BYTE1] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword0_remap_byte2 = rep_lane[DWORD0_BYTE2] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword0_remap_byte3 = rep_lane[DWORD0_BYTE3] & 0xf;
	cfg->phy_base[ch]->remap_con0.aword_col_remap = rep_lane[AWORD_CA] & 0xf;
	cfg->phy_base[ch]->remap_con0.aword_row_remap = rep_lane[AWORD_RA] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword1_remap_byte0 = rep_lane[DWORD1_BYTE0] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword1_remap_byte1 = rep_lane[DWORD1_BYTE1] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword1_remap_byte2 = rep_lane[DWORD1_BYTE2] & 0xf;
	cfg->phy_base[ch]->remap_con1.dword1_remap_byte3 = rep_lane[DWORD1_BYTE3] & 0xf;

	mdelay(1);

	/* Updata AWORD/DWORD deskewcode */
	cfg->phy_base[ch]->offsetd_con0.ctrl_resync = 0x1;
	udelay(1);
	cfg->phy_base[ch]->offsetd_con0.ctrl_resync = 0x0;

	return HBM_OK;
}

int32_t icon_extest(struct hbm3_config *cfg, uint8_t ch, uint8_t rep_lane[REDUNDANT])
{
	int8_t tx0_ret, tx1_ret;
	int8_t rx0_ret, rx1_ret;
	int8_t ret = 0;

	tx0_ret = icon_tx_extest(cfg, ch, TX0_EXTEST, rep_lane);
	if (tx0_ret == HBM_UNREPAIRABLE)
		return HBM_UNREPAIRABLE;
	ret += tx0_ret;

	icon_hbm_reset(cfg);

	udelay(1 * 10);
	tx1_ret = icon_tx_extest(cfg, ch, TX1_EXTEST, rep_lane);
	if (tx1_ret == HBM_UNREPAIRABLE)
		return HBM_UNREPAIRABLE;
	ret += tx1_ret;

	icon_hbm_reset(cfg);

	udelay(1 * 10);
	rx0_ret = icon_rx_extest(cfg, ch, RX0_EXTEST, rep_lane);
	if (rx0_ret == HBM_UNREPAIRABLE)
		return HBM_UNREPAIRABLE;
	ret += rx0_ret;

	icon_hbm_reset(cfg);

	udelay(1 * 10);
	rx1_ret = icon_rx_extest(cfg, ch, RX1_EXTEST,  rep_lane);
	if (rx1_ret == HBM_UNREPAIRABLE)
		return HBM_UNREPAIRABLE;
	ret += rx1_ret;

	return ret;
}

uint32_t icon_cdc_result(struct hbm3_config *cfg)
{
	uint32_t ch, rdata;
	uint32_t *icon_addr = (uint32_t *)cfg->icon_base;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = RD_WDR; /* 3'd4 : Read WDR */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = 21;
	/* WIR[12:0] = 0x1fd0 : CHIPPING_DET */
	cfg->icon_base->icon_ctrl_con0.sw_wir = ICON_SET_WIR(ICON_WIR_CH_ALL, ICON_WIR_CDC);

	icon_sw_instruction_req(cfg);

	udelay(1 * 10);

	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		rdata = RD_WDR_CH(icon_addr, 0, ch);
		printf("\nCH[%d] CDC Result = 0x%08x", ch, rdata);
	}
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t icon_cdc_wdr(struct hbm3_config *cfg, uint32_t cdc_wdr)
{
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = WR_WDR; /* 3'd3 : Write WDR */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = 21;

	cfg->icon_base->wr_wdr0.wr_wdr0 = cdc_wdr;

	icon_sw_instruction_req(cfg);

	return 0;
}

uint32_t icon_cdc_wir(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR; /* 3'd0 : Set WIR */

	/* WIR[12:0] = 0x1fd0 : CHIPPING_DET */
	cfg->icon_base->icon_ctrl_con0.sw_wir = ICON_SET_WIR(ICON_WIR_CH_ALL, ICON_WIR_CDC);

	icon_sw_instruction_req(cfg);

	return 0;
}

uint32_t icon_hbm_chipping_detection(struct hbm3_config *cfg)
{
	icon_cdc_wir(cfg);
	udelay(1 * 10);

	icon_cdc_wdr(cfg, B_DIE_UPPER);
	udelay(1 * 10);
	printf("B_DIE_UPPER Result\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, B_DIE_MIDDLE);
	udelay(1 * 10);
	printf("B_DIE_MIDDLE Result\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, B_DIE_LOWER);
	udelay(1 * 10);
	printf("B_DIE_LOWER Result\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID0_UPPER);
	udelay(1 * 10);
	printf("\nC_DIE_SID0_UPPER\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID0_MIDDLE);
	udelay(1 * 10);
	printf("C_DIE_SID0_MIDDLE\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID0_LOWER);
	udelay(1 * 10);
	printf("C_DIE_SID0_LOWER\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID1_UPPER);
	udelay(1 * 10);
	printf("\nC_DIE_SID1_UPPER\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID1_MIDDLE);
	udelay(1 * 10);
	printf("C_DIE_SID1_MIDDLE\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID1_LOWER);
	udelay(1 * 10);
	printf("C_DIE_SID1_LOWER\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID2_UPPER);
	udelay(1 * 10);
	printf("\nC_DIE_SID2_UPPER\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID2_MIDDLE);
	udelay(1 * 10);
	printf("C_DIE_SID2_MIDDLE\n");
	icon_cdc_result(cfg);

	icon_cdc_wdr(cfg, C_DIE_SID2_LOWER);
	udelay(1 * 10);
	printf("C_DIE_SID2_LOWER\n");
	icon_cdc_result(cfg);

	return 0;
}

uint32_t icon_mbist_wdr(struct hbm3_config *cfg, uint32_t *mbist_wdr)
{
	uint64_t icon_addr = (uint64_t)cfg->icon_base;

	uint32_t wdr_idx = 0, wdr_sfr_idx = 0;
	uint32_t loop_cnt = 4, loop_cnt_idx = 0;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = WR_WDR; /* 3'd3 : Write WDR */

	/* WR_WDR0 ~ WR_WDR14 = 480bit * 4 = 1920 bit */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = ((0x1 << 10) | 480);

	for (loop_cnt_idx = 0; loop_cnt_idx < loop_cnt; loop_cnt_idx++) {
		wdr_sfr_idx = 0;
		for (wdr_idx = (loop_cnt_idx * 15); wdr_idx < ((loop_cnt_idx + 1) * 15); wdr_idx++) {
			WR_WDR_IDX(icon_addr, wdr_sfr_idx, mbist_wdr[wdr_idx]);
			wdr_sfr_idx++;
		}
		icon_sw_instruction_req(cfg);

	}
	/* 2272 - 1920 = 352 */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = ((0x0 << 10) | 352);
	wdr_sfr_idx = 0;

	for (wdr_idx = (loop_cnt_idx * 15); wdr_idx < ICON_MBIST_WDR_IDX; wdr_idx++) {
		WR_WDR_IDX(icon_addr, wdr_sfr_idx, mbist_wdr[wdr_idx]);
		wdr_sfr_idx++;
	}
	icon_sw_instruction_req(cfg);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

uint32_t icon_mbist_result(struct hbm3_config *cfg)
{
	uint8_t idx, idx_max, ch, fail_ra_cnt = 0x11, rdqs_fail = 0, is_reparable = 1;
	uint32_t rdata;
	uint32_t mbist_result[HBM3_NUM_CH] = {0x0, };
	uint64_t icon_addr = (uint64_t)cfg->icon_base;

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = RD_WDR;

	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = 416;

	icon_sw_instruction_req(cfg);

	/* RD_WDR0 ~ RD_WDR12 [415:0] */
	idx_max = 1; /* idx_max : 1 = MBIST result only / 13 : all result */
	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		/* rd_wdr0_ch_# ~ rd_wdr12_ch_# */
		for (idx = 0; idx < idx_max; idx++) {
			rdata = RD_WDR_CH(icon_addr, idx, ch);
			printf("CH[%d][%d] MBIST result = 0x%08x\n", ch, idx, rdata >> 2);

			mbist_result[ch] = rdata;
		}
	}

	/* check self repair */
	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		rdata = (mbist_result[ch] >> 2);
		fail_ra_cnt = (rdata >> 6) & 0x1f;
		rdqs_fail = (rdata >> 11) & 0x1;
		is_reparable = (rdata >> 12) & 0x1;

		if (is_reparable != 0 && (rdqs_fail != 0 || fail_ra_cnt != 0x0)) {
			idx_max = 13;
			/* TODO : Add self repair logic */
			printf("\nCH[%d] need Self Repair", ch);
			for (idx = 0; idx < idx_max; idx++) {
				rdata = RD_WDR_CH(icon_addr, idx, ch);
			}
		}
	}
	return 0;
}

uint32_t icon_mbist_wir(struct hbm3_config *cfg)
{
	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x1;

	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR; /* 3'd0 : Set WIR */
	cfg->icon_base->icon_ctrl_con0.sw_wir = ICON_SET_WIR(ICON_WIR_CH_ALL, ICON_WIR_MBIST); /* MBIST WIR */

	icon_sw_instruction_req(cfg);

	cfg->icon_base->icon_ctrl_con0.sw_mode = 0x0;

	return 0;
}

union icon_device_id_t icon_get_device_id(struct hbm3_config *cfg)
{
	union icon_device_id_t device_id;

	icon_test_instruction_req(cfg, 0, ICON_INSTRUCTION_REQ_DEVICE_ID);

	for (int i = 0; i < ARRAY_SIZE(device_id.val); i++)
		device_id.val[i] = RD_WDR_CH(cfg->icon_base, i, 0);

	return device_id;
}

union icon_dram_temp_t icon_get_dram_temperature(struct hbm3_config *cfg)
{
	union icon_dram_temp_t dram_temp;

	icon_test_instruction_req(cfg, 0, ICON_INSTRUCTION_REQ_TEMPERATURE);

	for (int i = 0; i < ARRAY_SIZE(dram_temp.val); i++)
		dram_temp.val[i] = RD_WDR_CH(cfg->icon_base, i, 0);

	return dram_temp;
}

union icon_channel_temp_t icon_get_channel_temperature(struct hbm3_config *cfg)
{
	union icon_channel_temp_t channel_temp;

	icon_test_instruction_req(cfg, 0, ICON_INSTRUCTION_REQ_CHANNEL_TEMP);

	for (int i = 0; i < ARRAY_SIZE(channel_temp.val); i++)
		channel_temp.val[i] = RD_WDR_CH(cfg->icon_base, i, 0);

	return channel_temp;
}

union icon_ecs_error_log_t icon_get_ecs_error_log(struct hbm3_config *cfg, uint8_t ch)
{
	union icon_ecs_error_log_t ecs_error_log;

	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_ECS_ERROR_LOG);

	for (int i = 0; i < ARRAY_SIZE(ecs_error_log.val); i++)
		ecs_error_log.val[i] = RD_WDR_CH(cfg->icon_base, i, ch);

	return ecs_error_log;
}

void icon_print_device_id(union icon_device_id_t device_id)
{
	printf("\nDEVICE_ID[159:0] :");
	PRINT_INFO_VAL(device_id.model_part_number);
	PRINT_INFO_VAL(device_id.channel_available);
	PRINT_INFO_VAL(device_id.density);
	PRINT_INFO_VAL(device_id.manufacture_id);
	PRINT_INFO_VAL(device_id.serial_no_lower);
	PRINT_INFO_VAL(device_id.serial_no_upper);
	PRINT_INFO_VAL(device_id.manufacturing_week);
	PRINT_INFO_VAL(device_id.manufacturing_year);
	PRINT_INFO_VAL(device_id.rfm);
	PRINT_INFO_VAL(device_id.arfm);
	PRINT_INFO_VAL(device_id.raaimt);
	PRINT_INFO_VAL(device_id.raammt);
	PRINT_INFO_VAL(device_id.raadec);
	PRINT_INFO_VAL(device_id.raaimt_a);
	PRINT_INFO_VAL(device_id.raammt_a);
	PRINT_INFO_VAL(device_id.raadec_a);
	PRINT_INFO_VAL(device_id.raaimt_b);
	PRINT_INFO_VAL(device_id.raammt_b);
	PRINT_INFO_VAL(device_id.raadec_b);
	PRINT_INFO_VAL(device_id.raaimt_c);
	PRINT_INFO_VAL(device_id.raammt_c);
	PRINT_INFO_VAL(device_id.raadec_c);
	PRINT_INFO_VAL(device_id.ppr_ra);
	PRINT_INFO_VAL(device_id.ppr_rsvd);
	PRINT_INFO_VAL(device_id.shared_rep_res);
	PRINT_INFO_VAL(device_id.opt_feature);
}

void icon_print_dram_temperature(union icon_dram_temp_t dram_temp)
{
	printf("\nTemperature[8:0] :");
	PRINT_INFO_VAL(dram_temp.valid);
	PRINT_INFO_VAL(dram_temp.temp);

	if (dram_temp.valid)
		printf("\ntemp: %d 'C", ICON_HBM3_TEMP(dram_temp.temp));
}

void icon_print_channel_temperature(union icon_channel_temp_t channel_temp)
{
	printf("\nChannel-temperature[35:0] :");
	PRINT_INFO_VAL(channel_temp.sid0_valid);
	PRINT_INFO_VAL(channel_temp.sid0_temp);
	PRINT_INFO_VAL(channel_temp.sid1_valid);
	PRINT_INFO_VAL(channel_temp.sid1_temp);
	PRINT_INFO_VAL(channel_temp.sid2_valid);
	PRINT_INFO_VAL(channel_temp.sid2_temp);

	if (channel_temp.sid0_valid)
		printf("\nSID0_temp: %d 'C", ICON_HBM3_TEMP(channel_temp.sid0_temp));

	if (channel_temp.sid1_valid)
		printf("\nSID1_temp: %d 'C", ICON_HBM3_TEMP(channel_temp.sid1_temp));

	if (channel_temp.sid2_valid)
		printf("\nSID2_temp: %d 'C", ICON_HBM3_TEMP(channel_temp.sid2_temp));
}

void icon_print_ecs_error_log(union icon_ecs_error_log_t ecs_error_log)
{
	printf("\nECS_ERROR_LOG[215:0] :");
	PRINT_INFO_VAL(ecs_error_log.sid0_pc0_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc0_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc0_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc0_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc0_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc1_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc1_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc1_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc1_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid0_pc1_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc0_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc0_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc0_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc0_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc0_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc1_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc1_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc1_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc1_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid1_pc1_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc0_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc0_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc0_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc0_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc0_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc1_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc1_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc1_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc1_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid2_pc1_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc0_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc0_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc0_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc0_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc0_ecs_bank_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc1_ecs_valid);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc1_ecs_error_type);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc1_ecs_column_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc1_ecs_row_address);
	PRINT_INFO_VAL(ecs_error_log.sid3_pc1_ecs_bank_address);
}

uint32_t icon_mrw_idx(struct hbm3_config *cfg, uint8_t ch, enum wdr_mr_pos wdr_idx, uint32_t mr_data)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	printf("\nwdr_idx = %d, mr_data = 0x%08x", wdr_idx, mr_data);

	switch (wdr_idx) {
	case MR0_3: /* mr 0 ~ 3 */
		cfg->icon_base->wr_wdr0.wr_wdr0 = mr_data;
		break;
	case MR4_7: /* mr 4 ~ 7 */
		cfg->icon_base->wr_wdr1.wr_wdr1 = mr_data;
		break;
	case MR8_11: /* mr 8 ~ 11 */
		cfg->icon_base->wr_wdr2.wr_wdr2 = mr_data;
		break;
	case MR12_15: /* mr 12 ~ 15 */
		cfg->icon_base->wr_wdr3.wr_wdr3 = mr_data;
		break;
	default:
		printf("\ninvalid wdr idx");
		return -1;
	}

	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_MR_DUMP_SET_WRITE);

	return 0;
}

uint32_t icon_mrs_ch(struct hbm3_config *cfg, uint8_t ch, uint32_t *mr_data)
{
	cfg->icon_base->icon_ctrl_con0.ctrl_wrck_en = 0x1;

	cfg->icon_base->wr_wdr0.wr_wdr0 = mr_data[0];
	cfg->icon_base->wr_wdr1.wr_wdr1 = mr_data[1];
	cfg->icon_base->wr_wdr2.wr_wdr2 = mr_data[2];
	cfg->icon_base->wr_wdr3.wr_wdr3 = mr_data[3];

	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_MR_DUMP_SET_WRITE);

	return 0;
}

uint32_t icon_mrr(struct hbm3_config *cfg, uint8_t ch)
{
	union {
		uint32_t val[4];
		struct __attribute__((packed)) {
			uint8_t mr0;
			uint8_t mr1;
			uint8_t mr2;
			uint8_t mr3;
			uint8_t mr4;
			uint8_t mr5;
			uint8_t mr6;
			uint8_t mr7;
			uint8_t mr9;
			uint8_t mr10;
			uint8_t mr11;
			uint8_t mr12;
			uint8_t mr13;
			uint8_t mr14;
			uint8_t mr15;
		};
	} mr_dump;

	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_MR_DUMP_SET_READ);

	//rdata = icon_addr[(0xa4 + (0x4c * ch) - (i * 4)) / 4]; /* rd_wdr0_ch_# ~ rd_wdr3_ch_# */
	for (uint32_t i = 0; i < ARRAY_SIZE(mr_dump.val); i++)
		mr_dump.val[i] = RD_WDR_CH(cfg->icon_base, i, ch);

	printf("\nMODE_REGISTER_DUMP :");
	PRINT_INFO_VAL(mr_dump.mr0);
	PRINT_INFO_VAL(mr_dump.mr1);
	PRINT_INFO_VAL(mr_dump.mr2);
	PRINT_INFO_VAL(mr_dump.mr3);
	PRINT_INFO_VAL(mr_dump.mr4);
	PRINT_INFO_VAL(mr_dump.mr5);
	PRINT_INFO_VAL(mr_dump.mr6);
	PRINT_INFO_VAL(mr_dump.mr7);
	PRINT_INFO_VAL(mr_dump.mr9);
	PRINT_INFO_VAL(mr_dump.mr10);
	PRINT_INFO_VAL(mr_dump.mr11);
	PRINT_INFO_VAL(mr_dump.mr12);
	PRINT_INFO_VAL(mr_dump.mr13);
	PRINT_INFO_VAL(mr_dump.mr14);
	PRINT_INFO_VAL(mr_dump.mr15);

	return 0;
}

uint32_t icon_rd_feedback(struct hbm3_config *cfg, uint8_t ch,
						  uint32_t *rd_data0, uint32_t *rd_data1)
{
	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_AWORD_MISR_MODE);
	icon_test_instruction_req(cfg, ch, ICON_INSTRUCTION_REQ_AWORD_MISR_READ);

	*rd_data0 = RD_WDR_CH(cfg->icon_base, 0, ch);
	*rd_data1 = RD_WDR_CH(cfg->icon_base, 1, ch);

	return 0;
}
