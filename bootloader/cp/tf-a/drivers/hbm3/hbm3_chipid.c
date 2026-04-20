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
#include <drivers/delay_timer.h>

#define MASK_LOT_ID (0x1FFFFF)
#define BLEN_LOT (21)

#define MAX_LOT_LEN 6
#define NUM_CHIPID_REG 2


static const char * const old_lotid[] = {"FZ8XT", "FZ8Y3", "FZ8Y4"};

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
	uint32_t quotient;

	for (i = 4; i >= 1; i--) {
		quotient = 0;

		while (in >= 36) {
			in -= 36;
			quotient += 1;
		}

		mod = in;
		in = quotient;
		p[i] = (mod < 10) ? (mod + '0') : (mod - 10 + 'A');
	}
	p[5] = 0;
}

uint8_t get_lotid_for_hbm(void)
{
	char read_lotid[MAX_LOT_LEN] = {0};
	uint32_t chipid[NUM_CHIPID_REG];
	uint32_t i, lot;

	chipid[0] = GET_CHIP_ID(0);
	chipid[1] = GET_CHIP_ID(1);

	lot = chipid_reverse_value(chipid[0] & MASK_LOT_ID, BLEN_LOT);
	chipid_dec_to_36(lot, read_lotid);
	read_lotid[0] = ((chipid[1] & 0xC00) == 0x800) ? 'A' : ((chipid[1] & 0xC00) == 0xC00) ? 'F' : ' ';

	printf("Lot_ID: %s\n", read_lotid);

	for (i = 0; i < ARRAY_SIZE(old_lotid); i++) {
		if (strncmp(read_lotid, old_lotid[i], strlen(old_lotid[i])) == 0) {
			return HBM3_VER_OLD;
		}
	}

	return HBM3_VER_NEW;
}
