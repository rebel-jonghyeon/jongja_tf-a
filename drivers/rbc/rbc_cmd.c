/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#include <stdint.h>
#include <string.h>
#include <printf.h>
#include <rebel_h_platform.h>
#include "rbc_cmd.h"

const uint64_t crc_err_count_base[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_CRC_LOG, BLK_RBC_V11_CRC_LOG,
		BLK_RBC_H00_CRC_LOG, BLK_RBC_H01_CRC_LOG
	},
	{
		BLK_RBC_V01_CRC_LOG + CHIPLET_OFFSET * 1, BLK_RBC_V00_CRC_LOG + CHIPLET_OFFSET * 1,
		BLK_RBC_H00_CRC_LOG + CHIPLET_OFFSET * 1, BLK_RBC_H01_CRC_LOG + CHIPLET_OFFSET * 1
	},
	{
		BLK_RBC_V00_CRC_LOG + CHIPLET_OFFSET * 2, BLK_RBC_V01_CRC_LOG + CHIPLET_OFFSET * 2,
		BLK_RBC_H00_CRC_LOG + CHIPLET_OFFSET * 2, BLK_RBC_H01_CRC_LOG + CHIPLET_OFFSET * 2
	},
	{
		BLK_RBC_V11_CRC_LOG + CHIPLET_OFFSET * 3, BLK_RBC_V10_CRC_LOG + CHIPLET_OFFSET * 3,
		BLK_RBC_H00_CRC_LOG + CHIPLET_OFFSET * 3, BLK_RBC_H01_CRC_LOG + CHIPLET_OFFSET * 3
	}
};

const uint64_t link_stat_base_addr[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_LINK_STAT, BLK_RBC_V11_LINK_STAT,
		BLK_RBC_H00_LINK_STAT, BLK_RBC_H01_LINK_STAT
	},
	{
		BLK_RBC_V01_LINK_STAT + CHIPLET_OFFSET * 1, BLK_RBC_V00_LINK_STAT + CHIPLET_OFFSET * 1,
		BLK_RBC_H00_LINK_STAT + CHIPLET_OFFSET * 1, BLK_RBC_H01_LINK_STAT + CHIPLET_OFFSET * 1
	},
	{
		BLK_RBC_V00_LINK_STAT + CHIPLET_OFFSET * 2, BLK_RBC_V01_LINK_STAT + CHIPLET_OFFSET * 2,
		BLK_RBC_H00_LINK_STAT + CHIPLET_OFFSET * 2, BLK_RBC_H01_LINK_STAT + CHIPLET_OFFSET * 2
	},
	{
		BLK_RBC_V11_LINK_STAT + CHIPLET_OFFSET * 3, BLK_RBC_V10_LINK_STAT + CHIPLET_OFFSET * 3,
		BLK_RBC_H00_LINK_STAT + CHIPLET_OFFSET * 3, BLK_RBC_H01_LINK_STAT + CHIPLET_OFFSET * 3
	}
};

const uint64_t link_cap_base_addr[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_LINK_CAP, BLK_RBC_V11_LINK_CAP,
		BLK_RBC_H00_LINK_CAP, BLK_RBC_H01_LINK_CAP
	},
	{
		BLK_RBC_V01_LINK_CAP + CHIPLET_OFFSET * 1, BLK_RBC_V00_LINK_CAP + CHIPLET_OFFSET * 1,
		BLK_RBC_H00_LINK_CAP + CHIPLET_OFFSET * 1, BLK_RBC_H01_LINK_CAP + CHIPLET_OFFSET * 1
	},
	{
		BLK_RBC_V00_LINK_CAP + CHIPLET_OFFSET * 2, BLK_RBC_V01_LINK_CAP + CHIPLET_OFFSET * 2,
		BLK_RBC_H00_LINK_CAP + CHIPLET_OFFSET * 2, BLK_RBC_H01_LINK_CAP + CHIPLET_OFFSET * 2
	},
	{
		BLK_RBC_V11_LINK_CAP + CHIPLET_OFFSET * 3, BLK_RBC_V10_LINK_CAP + CHIPLET_OFFSET * 3,
		BLK_RBC_H00_LINK_CAP + CHIPLET_OFFSET * 3, BLK_RBC_H01_LINK_CAP + CHIPLET_OFFSET * 3
	}
};

const uint64_t scratch_reg3_base_addr[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_SCRATCH3, BLK_RBC_V11_SCRATCH3,
		BLK_RBC_H00_SCRATCH3, BLK_RBC_H01_SCRATCH3
	},
	{
		BLK_RBC_V01_SCRATCH3 + CHIPLET_OFFSET * 1, BLK_RBC_V00_SCRATCH3 + CHIPLET_OFFSET * 1,
		BLK_RBC_H00_SCRATCH3 + CHIPLET_OFFSET * 1, BLK_RBC_H01_SCRATCH3 + CHIPLET_OFFSET * 1
	},
	{
		BLK_RBC_V00_SCRATCH3 + CHIPLET_OFFSET * 2, BLK_RBC_V01_SCRATCH3 + CHIPLET_OFFSET * 2,
		BLK_RBC_H00_SCRATCH3 + CHIPLET_OFFSET * 2, BLK_RBC_H01_SCRATCH3 + CHIPLET_OFFSET * 2
	},
	{
		BLK_RBC_V11_SCRATCH3 + CHIPLET_OFFSET * 3, BLK_RBC_V10_SCRATCH3 + CHIPLET_OFFSET * 3,
		BLK_RBC_H00_SCRATCH3 + CHIPLET_OFFSET * 3, BLK_RBC_H01_SCRATCH3 + CHIPLET_OFFSET * 3
	}
};

void _check_ucie_link_speed(void)
{
	uint32_t fail_flag = 0;
	const char * const SPEED_STR[] = {
				"4GT", "8GT", "12GT", "16GT", "24GT", "32GT",
			};
	for (uint32_t chiplet_id = 0; chiplet_id < NUM_OF_CHIPS; chiplet_id++) {
		for (uint32_t rbc_idx = 0; rbc_idx < NUM_OF_ACTIVE_RBC; rbc_idx++) {
			uint64_t base = link_stat_base_addr[chiplet_id][rbc_idx] & (~0xffff);
			uint32_t link_stat_speed =
			(*(volatile uint32_t *)link_stat_base_addr[chiplet_id][rbc_idx] & (0xf << 11)) >> 11;
			uint32_t link_cap_speed =
			(*(volatile uint32_t *)link_cap_base_addr[chiplet_id][rbc_idx] & (0xf << 4)) >> 4;

			if (link_stat_speed != link_cap_speed) {
				printf("ch%d(0x%lx) : cap-%s but stat-%s\n", chiplet_id, base, SPEED_STR[link_cap_speed],
					   SPEED_STR[link_stat_speed]);
				fail_flag = 1;
			}
		}
	}
	if (fail_flag) {
		while (1)
			;
	} else {
		printf("UCIe Link Speed(%s) checking done\n",
			   SPEED_STR[(*(volatile uint32_t *)link_stat_base_addr[CHIPLET_ID][0] & (0xf << 11)) >> 11]);
	}
}

uint64_t get_crc_err_cnt(uint64_t (*crc_err_cnt_count)[4])
{
	int total_cnt = 0;

	for (uint32_t chiplet_id = 0; chiplet_id < NUM_OF_CHIPS; chiplet_id++) {
		for (uint32_t rbc_idx = 0; rbc_idx < NUM_OF_ACTIVE_RBC; rbc_idx++) {
			uint32_t low  = *(volatile uint32_t *)crc_err_count_base[chiplet_id][rbc_idx];
			uint32_t high = *(volatile uint32_t *)(crc_err_count_base[chiplet_id][rbc_idx] + 4);
			uint64_t count = ((uint64_t)high << 32) | low;

			crc_err_cnt_count[chiplet_id][rbc_idx] = count;
			if (count)
				total_cnt += count;
		}
	}

	return total_cnt;
}

uint32_t get_retrain_cnt(uint32_t (*retrain_count)[4])
{
	int total_cnt = 0;

	for (uint32_t chiplet_id = 0; chiplet_id < NUM_OF_CHIPS; chiplet_id++) {
		for (uint32_t rbc_idx = 0; rbc_idx < NUM_OF_ACTIVE_RBC; rbc_idx++) {
			uint32_t reg_value  = *(volatile uint32_t *)scratch_reg3_base_addr[chiplet_id][rbc_idx];
			uint32_t count = (reg_value >> 1) & 0x1f;

			retrain_count[chiplet_id][rbc_idx] = count;
			if (count)
				total_cnt += count;
		}
	}

	return total_cnt;
}

void show_crc_err_count(void)
{
	uint64_t crc_err_cnt_count[4][4];
	uint32_t retrain_count[4][4];

	get_crc_err_cnt(crc_err_cnt_count);
	get_retrain_cnt(retrain_count);

	for (uint32_t chiplet_id = 0; chiplet_id < NUM_OF_CHIPS; chiplet_id++) {
		for (uint32_t rbc_idx = 0; rbc_idx < NUM_OF_ACTIVE_RBC; rbc_idx++) {
			uint64_t base = crc_err_count_base[chiplet_id][rbc_idx];

			if (crc_err_cnt_count[chiplet_id][rbc_idx] > 0) {
				printf("ch%d(0x%lx) - crc err count %d", chiplet_id, base, crc_err_cnt_count[chiplet_id][rbc_idx]);
			} else {
				printf("ch%d(0x%lx) - none crc err", chiplet_id, base);
			}

			printf(" retrain count - %d", retrain_count[chiplet_id][rbc_idx]);
			printf("\n");
		}
	}
}
