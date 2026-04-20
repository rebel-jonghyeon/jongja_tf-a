/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <stdbool.h>
#include <driver.h>
#include "test_common.h"
#include "rebel_h_platform.h"

/*
 * CHIPID[63:0] = CHIP_ID_1 << 32 | CHIP_ID_0
 * CHIPID[41:34] YPOS
 * CHIPID[33:26] XPOS
 * CHIPID[25:21] WF_ID
 * CHIPID[20:0] LOT_ID
 */
#define MASK_LOT_ID (0x1FFFFF)
#define MASK_WF_ID (0x3E00000)
#define MASK_XPOS_ID_0 (0xFC000000)
#define MASK_XPOS_ID_1 (0x3)
#define MASK_YPOS_ID (0xFF)

#define BLEN_LOT (21)
#define BLEN_WF (5)
#define BLEN_XPOS (8)
#define BLEN_YPOS (8)

#define MAX_LOT_LEN 6
#define NUM_CHIPID_REG 2

static uint32_t chipid_reverse_value(uint32_t value, uint32_t bit_cnt)
{
	uint32_t temp, retvalue = 0;
	uint32_t i;

	for (i = 0; i < bit_cnt; i++) {
		temp = (value >> i) & 0x1;
		retvalue += temp << ((bit_cnt - 1) - i);
	}

	return retvalue;
}

static void chipid_dec_to_36(uint32_t in, char *p)
{
	uint32_t mod;
	uint32_t i;

	for (i = 4; i >= 1; i--) {
		mod = in % 36;
		in /= 36;
		p[i] = (mod < 10) ? (mod + '0') : (mod - 10 + 'A');
	}

	p[5] = 0;
}

uint8_t test_main_get_chipid(int argc, char *argv[])
{
	uint32_t chipid[NUM_CHIPID_REG] = {0x00,};
	char lotid[MAX_LOT_LEN] = {0};
	uint32_t lot = 0, wf = 0, xpos = 0, ypos = 0;

	chipid[0] = CHIP_ID_0;
	chipid[1] = CHIP_ID_1;

	lot = chipid_reverse_value(chipid[0] & MASK_LOT_ID, BLEN_LOT);
	chipid_dec_to_36(lot, lotid);
	lotid[0] = ((chipid[1] & 0xC00) == 0x800) ? 'A' : ((chipid[1] & 0xC00) == 0xC00) ? 'F' : ' ';

	wf = chipid_reverse_value(((chipid[0] & MASK_WF_ID) >> BLEN_LOT), BLEN_WF);
	xpos = chipid_reverse_value(((chipid[0] & MASK_XPOS_ID_0) >> (BLEN_LOT + BLEN_WF)) |
			((chipid[1] & MASK_XPOS_ID_1) << (32 - (BLEN_LOT + BLEN_WF))), BLEN_XPOS);
	ypos = chipid_reverse_value(((chipid[1] >> ((BLEN_LOT + BLEN_WF + BLEN_XPOS) - 32)) & MASK_YPOS_ID), BLEN_YPOS);

	printf("CHIPID: %s-W%d-%d-%d\n", lotid, wf, xpos, ypos);

	return true;
}

CLI_REGISTER(chipid, NULL, test_main_get_chipid, NULL);
