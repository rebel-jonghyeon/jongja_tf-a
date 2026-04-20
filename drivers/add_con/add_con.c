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

#include <rebel_h_platform.h>
#include <driver.h>
#include <interrupt.h>
#include "add_con.h"
#include "cmu.h"

#define D_MAX				(0xff)
#define WARN_ADD_CNT		(64)
#define START_UP_TIME		(16) /* us, longer than 15us */
#define EXT_LPF_ON_TIME		(11) /* us, longer than 10us */
#define SCREEND_FLAG_TIME	(2)  /* us, longer than 1us  */

uint32_t add_isr_cnt;

struct add_data {
	uint64_t *base;
	int int0_vol_drop;
	int int1_cal_fail;
};

static struct add_data add_list[] = {
	{(uint64_t *)ADD_CON_CP0_PRIVATE, ADD_CP0_VDROP_IRQ_NO, ADD_CP0_CAL_IRQ_NO},
	{(uint64_t *)ADD_CON_CP1_PRIVATE, ADD_CP1_VDROP_IRQ_NO, ADD_CP1_CAL_IRQ_NO},
};

static struct sysreg_cp *add_sysreg_cp0 = (struct sysreg_cp *)(SYSREG_CP0_PRIVATE + EN_ADD);
static struct sysreg_cp *add_sysreg_cp1 = (struct sysreg_cp *)(SYSREG_CP1_PRIVATE + EN_ADD);

static void add_sfr_clear(uint64_t *base)
{
	volatile struct add_con *con = (volatile struct add_con *)base;

	con->add_control.val = ADD_SFR_CLEAR;
	con->add_config0.val = ADD_SFR_CLEAR;
	con->add_config1.val = ADD_SFR_CLEAR;
	con->add_dac_cal_control.val = ADD_SFR_CLEAR;
	con->add_dac_cal_config.val = ADD_SFR_CLEAR;
	con->add_int_mask.val = ADD_SFR_CLEAR;
	con->add_int_clr.val = ADD_INT_CLEAR;
}

static uint32_t add_get_i_clk(void)
{
	uint64_t clk1;
	uint64_t clk2;
	uint32_t i_clk;

	CMU_BLK(cp, CMU_CP0_PRIVATE);

	clk1 = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp, &blk_cmu_cp->pll_con3_pll_cp);
	clk2 = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp_dvfs, &blk_cmu_cp->pll_con3_pll_cp_dvfs);
	clk1 = get_mux_freq(&blk_cmu_cp->clk_con_mux_mux_cp_pll_fout, clk1, clk2);
	i_clk = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div2_cp_aclk,
							 &blk_cmu_cp->clk_con_div_div4_hch_cp_aclk, clk1);

	return i_clk;
}

static uint32_t add_calc_cycle(uint32_t i_clk, uint32_t target_delay)
{
	if (target_delay == 0 || i_clk == 0) {
		return 0;
	}

	return i_clk * target_delay;
}

static int add_dac_cal(uint64_t *base)
{
	volatile struct add_con *con = (volatile struct add_con *)base;

	uint32_t i_clk = add_get_i_clk();
	uint32_t cycle = add_calc_cycle(i_clk, START_UP_TIME);

	if (cycle != 0) {
		con->add_config0.start_up_time = cycle;
	} else {
		return -1;
	}

	cycle = add_calc_cycle(i_clk, EXT_LPF_ON_TIME);
	if (cycle != 0) {
		con->add_config0.ext_lpf_on_time = cycle;
	} else {
		return -1;
	}

	cycle = add_calc_cycle(i_clk, SCREEND_FLAG_TIME);
	if (cycle != 0) {
		con->add_config1.screen_flag_time = cycle;
	} else {
		return -1;
	}

	con->add_dac_cal_control.dac_calibration_enable = ADD_DAC_CAL_ENABLE;

	con->add_dac_cal_config.d_diff = ADD_D_DIFF;
	con->add_dac_cal_config.d_start = ADD_D_START;
	con->add_dac_cal_config.dac_cal_interval = con->add_config1.screen_flag_time
											   + ADD_DAC_CAL_INTERVAL;

	con->add_control.mux_lpf = ADD_MANUAL_CTRL;
	con->add_control.div2_en = ADD_DIV2_EN;
	con->add_control.scal = ADD_SCAL_0P65_0P8;
	con->add_control.en = ADD_ENABLE;

	while (!con->add_dac_cal_debug.dac_calibration_done) {
		con->add_control.d++;
		if (con->add_control.d == D_MAX) {
			return -1;
		}
	}

	if (con->add_dac_cal_debug.dac_calibration_fail) {
		return -2;
	}

	con->add_control.d -= con->add_dac_cal_config.d_diff;

	return 0;
}

void add_adjust_d_diff_cp0(uint8_t v_diff)
{
	uint64_t *base = add_list[0].base;
	volatile struct add_con *con = (volatile struct add_con *)base;

	con->add_dac_cal_config.d_diff = v_diff;
}

void add_adjust_d_diff_cp1(uint8_t v_diff)
{
	uint64_t *base = add_list[1].base;
	volatile struct add_con *con = (volatile struct add_con *)base;

	con->add_dac_cal_config.d_diff = v_diff;
}

uint8_t add_get_adjusted_d_cp0(void)
{
	uint64_t *base = add_list[0].base;
	volatile struct add_con *con = (volatile struct add_con *)base;

	return con->add_control.d;
}

uint8_t add_get_adjusted_d_cp1(void)
{
	uint64_t *base = add_list[1].base;
	volatile struct add_con *con = (volatile struct add_con *)base;

	return con->add_control.d;
}

void add_enable_cp0_dfs(void)
{
	add_sysreg_cp0->en_add.en_add = SYSREG_CP0_ADD_ENABLE;
}

void add_enable_cp1_dfs(void)
{
	add_sysreg_cp1->en_add.en_add = SYSREG_CP1_ADD_ENABLE;
}

void add_disable_cp0_dfs(void)
{
	add_sysreg_cp0->en_add.en_add = SYSREG_CP0_ADD_DISABLE;
}

void add_disable_cp1_dfs(void)
{
	add_sysreg_cp1->en_add.en_add = SYSREG_CP1_ADD_DISABLE;
}

static void vol_drop_isr(void *base)
{
	add_isr_cnt++;

	if (add_isr_cnt >= WARN_ADD_CNT) {
		printf("[add] voltage drop had happened 0x%10p\n", base);
	}

	volatile struct add_con *con = (volatile struct add_con *)base;

	con->add_int_clr.int0_clr = ADD_INT0_CLEAR;
}

static void cal_fail_isr(void *base)
{
	printf("[add] cal fail happened 0x%10p\n", base);

	volatile struct add_con *con = (volatile struct add_con *)base;

	con->add_int_clr.int1_clr = ADD_INT1_CLEAR;
}

int add_con_init(void)
{
	uint32_t nr_add_con = sizeof(add_list) / sizeof(struct add_data);
	int res = 0;

	for (uint32_t i = 0; i < nr_add_con; ++i) {
		add_sfr_clear(add_list[i].base);

		res = add_dac_cal(add_list[i].base);
		if (res) {
			/* calibration fail */
			return res;
		}
		connect_interrupt_with_handler(add_list[i].int0_vol_drop, ADD_CP_VDROP_IRQ_PRIO,
									   IRQ_TYPE_EDGE, vol_drop_isr, add_list[i].base);
		connect_interrupt_with_handler(add_list[i].int1_cal_fail, ADD_CP_CAL_IRQ_PRIO,
									   IRQ_TYPE_EDGE, cal_fail_isr, add_list[i].base);
	}

	return res;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(7, add_con_init);
#endif
