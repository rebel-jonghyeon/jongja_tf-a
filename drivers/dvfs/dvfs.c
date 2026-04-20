/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include <stdlib.h>
#include <string.h>
#include <driver.h>
#include <rebel_h_platform.h>
#include "dvfs.h"
#include "ltc1427cs8.h"
#include "mp29816a.h"
#include "mpq8785.h"
#include "cmu.h"
#include "rl_errors.h"
#include "rl_utils.h"

struct dvfs_entry cp_dvfs_table[] = {
	{_2_5GHz, 950, 2500},
	{_2_4GHz, 950, 2400},
	{_2_3GHz, 850, 2300},
	{_2_2GHz, 850, 2200},
	{_2_1GHz, 850, 2100},
	{_2_GHz, 750, 2000},
	{_1_9GHz, 750, 1900},
	{_1_8GHz, 750, 1800},
	{_1_7GHz, 750, 1700},
	{_1_6GHz, 750, 1600},
	{_1_5GHz, 750, 1500},
	{_1_3GHz, 750, 1300},
	{_1_2GHz, 750, 1200},
	{_1_0GHz, 750, 1000},
	{_0_8GHz, 750, 800},
	{_0_6GHz, 750, 600},
	{_0_4GHz, 750, 400},
};

struct dvfs_entry dnc_dvfs_table[] = {
	{_1_2GHz, 650, 1200},	//UD level=0
	{_1_8GHz, 750, 1800},	//NM,level=1
	{_2_GHz, 850, 2000},	//OD,level=2
	{_1_6GHz, 750, 1600},	//ND,level=3
	{_1_4GHz, 750, 1400},	//ND,level=4
	{_1_2GHz, 750, 1200},	//ND,level=5
	{_1_0GHz, 750, 1000},	//ND,level=6
};

static struct get_pll_info get_pll_freq_cp(uintptr_t base)
{
	struct get_pll_info info = {0};
	uint32_t chiplet_cnt = CHIPLET_CNT;

	for (int i = 0; i <= chiplet_cnt; i++) {
		base = (base + (i * CHIPLET_BASE_OFFSET)) & ADDR_MASK;

		CMU_BLK(cp, base);
		info.vals[i] = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp,
										  &blk_cmu_cp->pll_con3_pll_cp);
	}
	return info;
}

static struct get_pll_info get_pll_freq_dcl(uintptr_t base)
{
	struct get_pll_info info = {0};
	uint32_t chiplet_cnt = CHIPLET_CNT;

	for (int i = 0; i <= chiplet_cnt; i++) {
		base = (base + (i * CHIPLET_BASE_OFFSET)) & ADDR_MASK;

		CMU_BLK(dcl, base);
		info.vals[i] = get_pll_freq_f0434(&blk_cmu_dcl->pll_con0_pll_dcl,
										  &blk_cmu_dcl->pll_con3_pll_dcl);
	}

	return info;
}

static void set_pll_freq_cp(uintptr_t base, uint32_t freq)
{
	uint32_t chiplet_cnt = CHIPLET_CNT;

	for (int i = 0; i <= chiplet_cnt; i++) {
		base = (base + (i * CHIPLET_BASE_OFFSET)) & ADDR_MASK;

		CMU_BLK(cp, base);
		set_pll_freq_f0434(&blk_cmu_cp->pll_locktime_pll_cp,
						   &blk_cmu_cp->pll_con0_pll_cp,
						   &blk_cmu_cp->pll_con3_pll_cp, freq);
	}
}

static void set_pll_freq_dcl(uintptr_t base, uint32_t freq)
{
	uint32_t chiplet_cnt = CHIPLET_CNT;

	for (int i = 0; i <= chiplet_cnt; i++) {
		base = (base + (i * CHIPLET_BASE_OFFSET)) & ADDR_MASK;

		CMU_BLK(dcl, base);
		set_pll_freq_f0434(&blk_cmu_dcl->pll_locktime_pll_dcl,
						   &blk_cmu_dcl->pll_con0_pll_dcl,
						   &blk_cmu_dcl->pll_con3_pll_dcl, freq);
	}
}

int set_dvfs_lvl(uint32_t domain, uint32_t lvl)
{
	uint32_t freq = 0, vout = 0;

	switch (domain) {
	case DVFS_DOMAIN_CP:
		if (lvl > ARRAY_SIZE(cp_dvfs_table))
			return RL_ERROR;

		freq = cp_dvfs_table[lvl].freq_mhz;
		vout = cp_dvfs_table[lvl].vout_mv;
		mpq8785_set_vout(VDD_CP_CHIPLET02, vout);
		mpq8785_set_vout(VDD_CP_CHIPLET13, vout);
		set_pll_freq_cp(CMU_CP0, freq);
		set_pll_freq_cp(CMU_CP1, freq);
		break;

	case DVFS_DOMAIN_DNC:
		if (lvl > ARRAY_SIZE(dnc_dvfs_table))
			return RL_ERROR;

		freq = dnc_dvfs_table[lvl].freq_mhz;
		vout = dnc_dvfs_table[lvl].vout_mv;
		/* FIXME : Temporary comment out before fix PMBUS configuration */
//		mp29816a_set_vout(VDD_DCL, vout);
//		mp29816a_set_vout(VDD_DCL_ODD, vout);
		set_pll_freq_dcl(CMU_DCL0, freq);
		set_pll_freq_dcl(CMU_DCL1, freq);
		break;

	default:
		printf("Error: Unknown case value %d\n", domain);
		return RL_ERROR;
	}

	return RL_OK;
}

int get_dvfs_lvl(uint32_t domain, struct dvfs_info *info)
{
	if (!info)
		return RL_ERROR;

	switch (domain) {
	case DVFS_DOMAIN_CP:
		info->vout[0] = mpq8785_get_vout(VDD_CP_CHIPLET02);
		info->vout[1] = mpq8785_get_vout(VDD_CP_CHIPLET13);
		memcpy(info->freq[0], get_pll_freq_cp(CMU_CP0).vals, sizeof(uint64_t) * 4);
		memcpy(info->freq[1], get_pll_freq_cp(CMU_CP1).vals, sizeof(uint64_t) * 4);
		break;

	case DVFS_DOMAIN_DNC:
		/* FIXME : Temporary comment out before fix PMBUS configuration */
//		info->vout[0] = mp29816a_get_vout(VDD_DCL);
//		info->vout[1] = mp29816a_get_vout(VDD_DCL_ODD);
		memcpy(info->freq[0], get_pll_freq_dcl(CMU_DCL0).vals, sizeof(uint64_t) * 4);
		memcpy(info->freq[1], get_pll_freq_dcl(CMU_DCL1).vals, sizeof(uint64_t) * 4);
		break;

	default:
		printf("Error: Unknown case value %d\n", domain);
		return RL_ERROR;
	}

	return RL_OK;
}
