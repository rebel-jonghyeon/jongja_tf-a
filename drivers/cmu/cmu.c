/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include <rebel_h_platform.h>
#include "cmu.h"

struct pll_locktime {
	uint32_t pll_lock_time:20; /* [19:0] */
	uint32_t reserved0:4; /* [23:20] */
	uint32_t reset_req_time:6; /* [29:24] */
	uint32_t reserved1:2; /* [31:30] */
};

struct pll_con0 {
	uint32_t div_s : 3;			  /* [2:0] */
	uint32_t pll_lock : 1;		  /* [3:3] */
	uint32_t mux_sel : 1;		  /* [4:4] */
	uint32_t reserved0 : 2;		  /* [6:5] */
	uint32_t mux_busy : 1;		  /* [7:7] */
	uint32_t div_p : 6;			  /* [13:8] */
	uint32_t reserved1 : 2;		  /* [15:14] */
	uint32_t div_m : 10;		  /* [25:16] */
	uint32_t lock_en : 1;		  /* [26:26] */
	uint32_t lock_fail : 1;		  /* [27:27] */
	uint32_t use_hw_lock_det : 1; /* [28:28] */
	uint32_t stable : 1;		  /* [29:29] */
	uint32_t use_lock_fail : 1;	  /* [30:30] */
	uint32_t enable : 1;		  /* [31:31] */
};

struct pll_con3 {
	uint32_t div_k:16; /* [15:0] */
	uint32_t mfr:8; /* [23:16] */
	uint32_t mrr:6; /* [29:24] */
	uint32_t sel_pf:2; /* [31:30] */
};

struct hch_div_sfr {
	uint32_t divratio : 4;	 /* [3:0] */
	uint32_t reserved0 : 12; /* [15:4] */
	uint32_t therm_dfs : 1;	 /* [16:16] */
	uint32_t reserved1 : 14; /* [30:17] */
	uint32_t enable : 1;	 /* [31:31] */
};

struct div_sfr {
	uint32_t divratio : 16;					 /* [15:0] */
	uint32_t busy : 1;						 /* [16:16] */
	uint32_t reserved1 : 11;				 /* [27:17] */
	uint32_t enable_automatic_clkgating : 1; /* [28:28] */
	uint32_t reserved2 : 1;					 /* [29:29] */
	uint32_t override_by_hch : 1;			 /* [30:30] */
	uint32_t reserved3 : 1;					 /* [31:31] */
};

struct mux_sfr {
	uint32_t select : 1;					 /* [0:0] */
	uint32_t reserved0 : 15;				 /* [15:1] */
	uint32_t busy : 1;						 /* [16:16] */
	uint32_t reserved1 : 11;				 /* [27:17] */
	uint32_t enable_automatic_clkgating : 1; /* [28:28] */
	uint32_t reserved2 : 1;					 /* [29:29] */
	uint32_t override_by_hch : 1;			 /* [30:30] */
	uint32_t reserved3 : 1;					 /* [31:31] */
};

struct user_mux_sfr {
	uint32_t reserved0 : 4;	 /* [3:0] */
	uint32_t mux_sel : 1;	 /* [4:4] */
	uint32_t reserved1 : 2;	 /* [6:5] */
	uint32_t busy : 1;		 /* [7:7] */
	uint32_t reserved2 : 24; /* [31:8] */
};

struct gate_sfr {
	uint32_t enable : 1;			 /* [0:0] */
	uint32_t clock_req : 1;			 /* [1:1] */
	uint32_t ignore_force_pm_en : 1; /* [2:2] */
	uint32_t mask_qactive : 1;		 /* [3:3] */
	uint32_t reserved0 : 12;		 /* [15:4] */
	uint32_t expire_val : 10;		 /* [25:16] */
	uint32_t reserved1 : 6;			 /* [31:26] */
};

struct clk_out_sfr {
	uint32_t div_ratio : 5;                  /* [4:0] */
	uint32_t reserved0 : 3;                  /* [7:5] */
	uint32_t select : 5;                     /* [12:8] */
	uint32_t reserved1 : 3;                  /* [15:13] */
	uint32_t busy : 1;                       /* [16:16] */
	uint32_t reserved2 : 3;                  /* [19:17] */
	uint32_t validate_clk_req : 1;           /* [20:20] */
	uint32_t reserved3 : 7;                  /* [27:21] */
	uint32_t enable_automatic_clkgating : 1; /* [28:28] */
	uint32_t enable : 1;                     /* [29:29] */
	uint32_t reserved4 : 2;                  /* [31:30] */
};

struct cpmu_pmu_debug {
	uint32_t clkout0_enable:1; /* [0:0] */
	uint32_t rsvd3:5; /* [5:1] */
	uint32_t clkout0_invert:1; /* [6:6] */
	uint32_t rsvd2:1; /* [7:7] */
	uint32_t clkout0_sel:6; /* [13:8] */
	uint32_t rsvd1:1; /* [14:14] */
	uint32_t dbg_sel:5; /* [19:15] */
	uint32_t select_serial_debug_output_port:5; /* [24:20] */
	uint32_t rsvd0:1; /* [25:25] */
	uint32_t select_power_down_state_output_port:5; /* [30:26] */
	uint32_t enable_serial_debug:1; /* [31:31] */
};

struct pll_table {
	uint32_t target_freq;
	uint32_t p;
	uint32_t m;
	uint32_t s;
	uint32_t k;
};

static struct pll_table pll_table_f0434[] = {
	{2500, 2, 125, 0, 0},
	{2400, 2, 120, 0, 0},
	{2300, 2, 115, 0, 0},
	{2200, 2, 110, 0, 0},
	{2100, 2, 105, 0, 0},
	{2000, 2, 100, 0, 0},
	{1900, 1,  95, 1, 0},
	{1800, 1,  90, 1, 0},
	{1700, 1,  85, 1, 0},
	{1600, 1,  80, 1, 0},
	{1500, 1,  75, 1, 0},
	{1400, 2, 140, 1, 0},	//added
	{1300, 1,  65, 1, 0},
	{1200, 2, 120, 1, 0},
	{1000, 1, 100, 2, 0},
	{800,  1,  80, 2, 0},
	{600,  2, 120, 2, 0},
	{400,  1,  80, 3, 0},
};

static struct pll_table pll_table_f0435[] = {
	{9600, 1, 120, 0, 0},
	{9200, 1, 115, 0, 0},
	{8000, 1, 100, 0, 0},
	{6400, 1, 160, 1, 0},
};

#define OSC_MHz								(40)
#define _1MHz								(1000000ULL)
#define PLL_LOCKCYCLE						(500)
#define PLL_ENABLE							(1)
#define PLL_DISABLE							(0)

#define DISABLE_PLL(sfr)					\
	(sfr).enable = PLL_DISABLE
#define SET_LOCKTIME(sfr, table)			\
	(sfr).pll_lock_time = (table).p * PLL_LOCKCYCLE
#define SET_CON0_VAL(sfr, table)			\
	(sfr).div_p = (table).p;				\
	(sfr).div_m = (table).m;				\
	(sfr).div_s = (table).s;				\
	(sfr).enable = PLL_ENABLE
#define SET_CON3_VAL(sfr, table)			(sfr).div_k = (table).k
#define IS_PLL_LOCKED(sfr)					\
	do { ;									\
	} while (!(sfr).stable)

#define WAIT_PLL_BUSY(sfr)					\
	do { ;									\
	} while ((sfr).mux_busy)
#define SET_CON0_MUX_SEL(sfr, val)			\
	(sfr).mux_sel = (val);					\
	WAIT_PLL_BUSY(sfr)

#define SET_DIV(sfr, val)					(sfr).divratio = (val) ? ((val) - 1) : (0)

#define WAIT_MUX_BUSY(sfr)					\
	do { ;									\
	} while ((sfr).busy)
#define SET_MUX(sfr, val)					\
	(sfr).select = (val);					\
	WAIT_MUX_BUSY(sfr)

#define WAIT_USER_MUX(sfr)					WAIT_MUX_BUSY(sfr)
#define SET_USER_MUX(sfr, val)				\
	(sfr).mux_sel = (val);					\
	WAIT_USER_MUX(sfr)

static uint32_t clk_pow(int32_t base, uint32_t exp)
{
	int ret = 1;

	while (exp--) {
		ret *= base;
	}

	return ret;
}

uint32_t set_clk_out(volatile uint64_t cmu_base, uint32_t blk_id, uint32_t clk_id)
{
	volatile struct clk_out_sfr *clk_out = (struct clk_out_sfr *)(cmu_base + 0x804);
	volatile struct cpmu_pmu_debug *pmu_debug = (struct cpmu_pmu_debug *)(CPMU_PRIVATE + 0xA00);

	clk_out->div_ratio = 9;
	clk_out->select = clk_id;

	pmu_debug->dbg_sel = blk_id;

	return *(uint32_t *)clk_out;
}

void set_pll_freq_f0434(volatile void *lock_time, volatile void *con0, volatile void *con3,
						uint32_t freq)
{
	volatile struct pll_locktime *lock_addr = lock_time;
	volatile struct pll_con0 *con0_addr = con0;
	volatile struct pll_con3 *con3_addr = con3;
	volatile struct pll_table *table = &pll_table_f0434[freq];

	con0_addr->mux_sel = 0;
	while (con0_addr->mux_busy)
		;
	con0_addr->enable = PLL_DISABLE;

	lock_addr->pll_lock_time = table->p * PLL_LOCKCYCLE;

	con0_addr->div_p = table->p;
	con0_addr->div_m = table->m;
	con0_addr->div_s = table->s;
	con3_addr->div_k = table->k;
	con0_addr->enable = PLL_ENABLE;

	con0_addr->mux_sel = 1;
	while (!con0_addr->stable)
		;
}

void set_pll_freq_f0435(volatile void *lock_time, volatile void *con0, volatile void *con3,
						uint32_t freq)
{
	volatile struct pll_locktime *lock_addr = lock_time;
	volatile struct pll_con0 *con0_addr = con0;
	volatile struct pll_con3 *con3_addr = con3;
	volatile struct pll_table *table = &pll_table_f0435[freq];

	con0_addr->mux_sel = 0;
	while (con0_addr->mux_busy)
		;
	con0_addr->enable = PLL_DISABLE;

	lock_addr->pll_lock_time = table->p * PLL_LOCKCYCLE;

	con0_addr->div_p = table->p;
	con0_addr->div_m = table->m;
	con0_addr->div_s = table->s;
	con3_addr->div_k = table->k;
	con0_addr->enable = PLL_ENABLE;

	con0_addr->mux_sel = 1;
	while (!con0_addr->stable)
		;
}

uint64_t get_pll_freq_f0434(volatile void *con0, volatile void *con3)
{
	volatile struct pll_con0 *con0_addr = con0;
	volatile struct pll_con3 *con3_addr = con3;

	if (con0_addr->mux_sel == 0) {
		return OSC_MHz;
	}

	return ((con0_addr->div_m + con3_addr->div_k / 65536) * OSC_MHz) /
		(con0_addr->div_p * clk_pow(2, con0_addr->div_s));
}

uint64_t get_pll_freq_f0435(volatile void *con0, volatile void *con3)
{
	uint64_t freq = get_pll_freq_f0434(con0, con3);

	return freq == OSC_MHz ? OSC_MHz : freq * 2;
}

void set_div_ratio(volatile void *div, uint32_t ratio)
{
	volatile struct div_sfr *div_addr = div;

	if (ratio != 0) {
		ratio--;
	}
	div_addr->divratio = ratio;
}

void set_hch_div_ratio(volatile void *div, volatile void *hch_div, uint32_t ratio)
{
	volatile struct hch_div_sfr *hch_div_addr = hch_div;
	uint32_t hch_ratio;

	if (ratio != 0) {
		hch_ratio = (ratio - 1) * 2 + 1;
	} else {
		hch_ratio = 1;
	}

	set_div_ratio(div, ratio);
	if (hch_div_addr) {
		hch_div_addr->divratio = hch_ratio;
	}
}

uint32_t get_div_ratio(volatile void *div)
{
	return ((struct div_sfr *)div)->divratio + 1;
}

uint32_t get_hch_div_ratio(volatile void *div, volatile void *hch_div)
{
	if (hch_div != 0 && ((struct hch_div_sfr *)hch_div)->therm_dfs) {
		return ((struct hch_div_sfr *)hch_div)->divratio + 1;
	}

	return ((struct div_sfr *)div)->divratio + 1;
}

void set_user_mux_sel(volatile void *user_mux, uint32_t sel)
{
	volatile struct user_mux_sfr *user_mux_addr = user_mux;

	user_mux_addr->mux_sel = sel;
	while (user_mux_addr->busy)
		;
}

void set_mux_sel(volatile void *mux, uint32_t sel)
{
	volatile struct mux_sfr *mux_addr = mux;

	mux_addr->select = sel;
	while (mux_addr->busy)
		;
}

uint32_t get_user_mux_sel(volatile void *user_mux)
{
	return ((struct user_mux_sfr *)user_mux)->mux_sel;
}

uint32_t get_mux_sel(volatile void *mux)
{
	return ((struct mux_sfr *)mux)->select;
}

uint32_t is_clk_gated(volatile void *gate)
{
	return ((struct gate_sfr *)gate)->clock_req;
}

void clk_gating(volatile void *gate, uint32_t val)
{
	volatile struct gate_sfr *gate_addr = gate;

	gate_addr->ignore_force_pm_en = 1;
	gate_addr->clock_req = val;
}

uint64_t get_user_mux_freq(volatile void *user_mux, uint64_t in1, uint64_t in2)
{
	return get_user_mux_sel(user_mux) ? in2 : in1;
}

uint64_t get_mux_freq(volatile void *mux, uint64_t in1, uint64_t in2)
{
	return get_mux_sel(mux) ? in2 : in1;
}

uint64_t get_hch_div_freq(volatile void *div, volatile void *hch_div, uint64_t in)
{
	return in / get_hch_div_ratio(div, hch_div);
}

uint64_t get_div_freq(volatile void *div, uint64_t in)
{
	return in / get_div_ratio(div);
}

void cmu_blk_cp_init(uintptr_t base)
{
	CMU_BLK(cp, base);

	SET_LOCKTIME(blk_cmu_cp->pll_locktime_pll_cp, pll_table_f0434[_2_GHz]);
	SET_CON0_VAL(blk_cmu_cp->pll_con0_pll_cp, pll_table_f0434[_2_GHz]);
	SET_CON3_VAL(blk_cmu_cp->pll_con3_pll_cp, pll_table_f0434[_2_GHz]);
	IS_PLL_LOCKED(blk_cmu_cp->pll_con0_pll_cp);

	SET_LOCKTIME(blk_cmu_cp->pll_locktime_pll_cp_dvfs, pll_table_f0434[_2_GHz]);
	SET_CON0_VAL(blk_cmu_cp->pll_con0_pll_cp_dvfs, pll_table_f0434[_2_GHz]);
	SET_CON3_VAL(blk_cmu_cp->pll_con3_pll_cp_dvfs, pll_table_f0434[_2_GHz]);
	IS_PLL_LOCKED(blk_cmu_cp->pll_con0_pll_cp_dvfs);

	SET_DIV(blk_cmu_cp->clk_con_div_div2_cp_cmuref, 2);
	SET_DIV(blk_cmu_cp->clk_con_div_div4_hch_cp_cmuref, 4);
	SET_DIV(blk_cmu_cp->clk_con_div_div1_cp_coreclk, 1);
	SET_DIV(blk_cmu_cp->clk_con_div_div2_hch_cp_coreclk, 2);
	SET_DIV(blk_cmu_cp->clk_con_div_div2_cp_aclk, 2);
	SET_DIV(blk_cmu_cp->clk_con_div_div4_hch_cp_aclk, 4);
	SET_DIV(blk_cmu_cp->clk_con_div_div4_cp_stm, 4);
	SET_DIV(blk_cmu_cp->clk_con_div_div8_hch_cp_stm, 8);
	SET_DIV(blk_cmu_cp->clk_con_div_div4_cp_pclk, 4);
	SET_DIV(blk_cmu_cp->clk_con_div_div8_hch_cp_pclk, 8);

	SET_DIV(blk_cmu_cp->clk_con_div_div1_cp_tsclk, 1);
	SET_DIV(blk_cmu_cp->clk_con_div_div5_cp_add, 5);

	SET_MUX(blk_cmu_cp->clk_con_mux_mux_cp_pll_fout, 0);
	SET_MUX(blk_cmu_cp->clk_con_mux_mux_cp_tsclk, 0);

	SET_CON0_MUX_SEL(blk_cmu_cp->pll_con0_pll_cp, 1);
	SET_CON0_MUX_SEL(blk_cmu_cp->pll_con0_pll_cp_dvfs, 1);
}

void cmu_blk_pcie_init(uintptr_t base)
{
	CMU_BLK(pcie, base);

	SET_LOCKTIME(blk_cmu_pcie->pll_locktime_pll_pcie, pll_table_f0434[_2_GHz]);
	SET_CON0_VAL(blk_cmu_pcie->pll_con0_pll_pcie, pll_table_f0434[_2_GHz]);
	SET_CON3_VAL(blk_cmu_pcie->pll_con3_pll_pcie, pll_table_f0434[_2_GHz]);
	IS_PLL_LOCKED(blk_cmu_pcie->pll_con0_pll_pcie);

	SET_DIV(blk_cmu_pcie->clk_con_div_div20_pcie_refclk_p, 20);
	SET_DIV(blk_cmu_pcie->clk_con_div_div2_pcie_aclk, 2);
	SET_DIV(blk_cmu_pcie->clk_con_div_div4_pcie_pclk, 4);
	SET_DIV(blk_cmu_pcie->clk_con_div_div1_pcie_tsclk, 1);
	SET_DIV(blk_cmu_pcie->clk_con_div_div16_pcie_crparaclk, 16);
	SET_DIV(blk_cmu_pcie->clk_con_div_div_pcie_auxclk, 10);

	SET_MUX(blk_cmu_pcie->clk_con_mux_mux_pcie_tsclk, 0);
	SET_MUX(blk_cmu_pcie->clk_con_mux_mux_pcie_auxclk, 1);

	SET_CON0_MUX_SEL(blk_cmu_pcie->pll_con0_pll_pcie, 1);
}

void cmu_blk_rot_init(uintptr_t base)
{
	CMU_BLK(rot, base);

	SET_LOCKTIME(blk_cmu_rot->pll_locktime_pll_rot, pll_table_f0434[_1_5GHz]);
	SET_CON0_VAL(blk_cmu_rot->pll_con0_pll_rot, pll_table_f0434[_1_5GHz]);
	SET_CON3_VAL(blk_cmu_rot->pll_con3_pll_rot, pll_table_f0434[_1_5GHz]);
	IS_PLL_LOCKED(blk_cmu_rot->pll_con0_pll_rot);

	SET_DIV(blk_cmu_rot->clk_con_div_div4_rot_otp, 4);
	SET_DIV(blk_cmu_rot->clk_con_div_div2_rot_aclk, 2);
	SET_DIV(blk_cmu_rot->clk_con_div_div7_rot_pvt, 7);
	SET_DIV(blk_cmu_rot->clk_con_div_div3_rot_pclk, 3);
	SET_DIV(blk_cmu_rot->clk_con_div_div1_rot_tsclk, 1);
	SET_DIV(blk_cmu_rot->clk_con_div_div3_rot_cntclk, 3);
	SET_DIV(blk_cmu_rot->clk_con_div_div3_rot_rtck, 3);

	SET_CON0_MUX_SEL(blk_cmu_rot->pll_con0_pll_rot, 1);
}

void cmu_blk_peri_init(uintptr_t base)
{
	CMU_BLK(peri, base);

	SET_LOCKTIME(blk_cmu_peri->pll_locktime_pll_peri, pll_table_f0434[_1_0GHz]);
	SET_CON0_VAL(blk_cmu_peri->pll_con0_pll_peri, pll_table_f0434[_1_0GHz]);
	SET_CON3_VAL(blk_cmu_peri->pll_con3_pll_peri, pll_table_f0434[_1_0GHz]);
	IS_PLL_LOCKED(blk_cmu_peri->pll_con0_pll_peri);

	SET_DIV(blk_cmu_peri->clk_con_div_div2_peri_pclk, 4);

	SET_CON0_MUX_SEL(blk_cmu_peri->pll_con0_pll_peri, 1);
}

void cmu_blk_ebus_d_init(uintptr_t base)
{
	CMU_BLK(ebus_d, base);

	SET_LOCKTIME(blk_cmu_ebus_d->pll_locktime_pll_ebus_d_1200, pll_table_f0434[_1_2GHz]);
	SET_CON0_VAL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, pll_table_f0434[_1_2GHz]);
	SET_CON3_VAL(blk_cmu_ebus_d->pll_con3_pll_ebus_d_1200, pll_table_f0434[_1_2GHz]);
	IS_PLL_LOCKED(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200);

	SET_DIV(blk_cmu_ebus_d->clk_con_div_div1_ebus_d_aclk, 1);
	SET_DIV(blk_cmu_ebus_d->clk_con_div_div3_ebus_d_pclk, 3);
	SET_DIV(blk_cmu_ebus_d->clk_con_div_div_ebus_d_sh_low_clk, 1);

	SET_USER_MUX(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1600, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, 1);
}

void cmu_blk_ebus_r_init(uintptr_t base)
{
	CMU_BLK(ebus_r, base);

	SET_DIV(blk_cmu_ebus_r->clk_con_div_div1_ebus_r_aclk, 1);
	SET_DIV(blk_cmu_ebus_r->clk_con_div_div3_ebus_r_pclk, 3);

	SET_USER_MUX(blk_cmu_ebus_r->pll_con0_pll_ebus_r, 1);
}

void cmu_blk_ebus_u_init(uintptr_t base)
{
	CMU_BLK(ebus_u, base);

	SET_LOCKTIME(blk_cmu_ebus_u->pll_locktime_pll_ebus, pll_table_f0434[_1_6GHz]);
	SET_CON0_VAL(blk_cmu_ebus_u->pll_con0_pll_ebus, pll_table_f0434[_1_6GHz]);
	SET_CON3_VAL(blk_cmu_ebus_u->pll_con3_pll_ebus, pll_table_f0434[_1_6GHz]);
	IS_PLL_LOCKED(blk_cmu_ebus_u->pll_con0_pll_ebus);

	SET_DIV(blk_cmu_ebus_u->clk_con_div_div1_ebus_u_aclk, 1);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div3_ebus_u_pclk, 3);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div_rbc_h0, 8);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div_rbc_h1, 8);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div1_ebus_u_sh_low_clk, 1);

	SET_USER_MUX(blk_cmu_ebus_u->pll_con0_pll_ctrl_ebus_u, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_u->pll_con0_pll_ebus, 1);
}

void cmu_blk_nbus_d_init(uintptr_t base)
{
	CMU_BLK(nbus_d, base);

	SET_LOCKTIME(blk_cmu_nbus_d->pll_locktime_pll_nbus, pll_table_f0434[_1_6GHz]);
	SET_CON0_VAL(blk_cmu_nbus_d->pll_con0_pll_nbus, pll_table_f0434[_1_6GHz]);
	SET_CON3_VAL(blk_cmu_nbus_d->pll_con3_pll_nbus, pll_table_f0434[_1_6GHz]);
	IS_PLL_LOCKED(blk_cmu_nbus_d->pll_con0_pll_nbus);

	SET_DIV(blk_cmu_nbus_d->clk_con_div_div1_nbus_d_aclk, 1);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div3_nbus_d_pclk, 3);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div4_rbc_v0, 8);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div4_rbc_v1, 8);

	SET_CON0_MUX_SEL(blk_cmu_nbus_d->pll_con0_pll_nbus, 1);
}

void cmu_blk_nbus_l_init(uintptr_t base)
{
	CMU_BLK(nbus_l, base);

	SET_DIV(blk_cmu_nbus_l->clk_con_div_div1_nbus_l_aclk, 1);
	SET_DIV(blk_cmu_nbus_l->clk_con_div_div3_nbus_l_pclk, 3);
	SET_DIV(blk_cmu_nbus_l->clk_con_div_div2_nbus_l_gclk, 2);

	SET_USER_MUX(blk_cmu_nbus_l->pll_con0_pll_nbus_l, 1);
}

void cmu_blk_nbus_u_init(uintptr_t base)
{
	CMU_BLK(nbus_u, base);

	SET_DIV(blk_cmu_nbus_u->clk_con_div_div1_nbus_u_aclk, 1);
	SET_DIV(blk_cmu_nbus_u->clk_con_div_div3_nbus_u_pclk, 3);
	SET_DIV(blk_cmu_nbus_u->clk_con_div_div1_nbus_u_tclk, 1);

	SET_USER_MUX(blk_cmu_nbus_u->pll_con0_pll_nbus_u, 1);
}

void cmu_blk_sbus_d_init(uintptr_t base)
{
	CMU_BLK(sbus_d, base);

	SET_DIV(blk_cmu_sbus_d->clk_con_div_div1_sbus_d_aclk, 1);
	SET_DIV(blk_cmu_sbus_d->clk_con_div_div3_sbus_d_pclk, 3);

	SET_USER_MUX(blk_cmu_sbus_d->pll_con0_pll_sbus_d, 1);
}

void cmu_blk_sbus_l_init(uintptr_t base)
{
	CMU_BLK(sbus_l, base);

	SET_DIV(blk_cmu_sbus_l->clk_con_div_div1_sbus_l_aclk, 1);
	SET_DIV(blk_cmu_sbus_l->clk_con_div_div3_sbus_l_pclk, 3);

	SET_USER_MUX(blk_cmu_sbus_l->pll_con0_pll_sbus_l, 1);
}

void cmu_blk_sbus_u_init(uintptr_t base)
{
	CMU_BLK(sbus_u, base);

	SET_LOCKTIME(blk_cmu_sbus_u->pll_locktime_pll_sbus, pll_table_f0434[_1_6GHz]);
	SET_CON0_VAL(blk_cmu_sbus_u->pll_con0_pll_sbus, pll_table_f0434[_1_6GHz]);
	SET_CON3_VAL(blk_cmu_sbus_u->pll_con3_pll_sbus, pll_table_f0434[_1_6GHz]);
	IS_PLL_LOCKED(blk_cmu_sbus_u->pll_con0_pll_sbus);

	SET_DIV(blk_cmu_sbus_u->clk_con_div_div1_sbus_u_aclk, 1);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div3_sbus_u_pclk, 3);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div4_rbc_v10, 8);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div4_rbc_v11, 8);

	SET_CON0_MUX_SEL(blk_cmu_sbus_u->pll_con0_pll_sbus, 1);
}

void cmu_blk_wbus_d_init(uintptr_t base)
{
	CMU_BLK(wbus_d, base);

	SET_DIV(blk_cmu_wbus_d->clk_con_div_div1_wbus_d_aclk, 1);
	SET_DIV(blk_cmu_wbus_d->clk_con_div_div3_wbus_d_pclk, 3);

	SET_USER_MUX(blk_cmu_wbus_d->pll_con0_pll_wbus_d, 1);
}

void cmu_blk_wbus_u_init(uintptr_t base)
{
	CMU_BLK(wbus_u, base);

	SET_LOCKTIME(blk_cmu_wbus_u->pll_locktime_pll_wbus, pll_table_f0434[_1_6GHz]);
	SET_CON0_VAL(blk_cmu_wbus_u->pll_con0_pll_wbus, pll_table_f0434[_1_6GHz]);
	SET_CON3_VAL(blk_cmu_wbus_u->pll_con3_pll_wbus, pll_table_f0434[_1_6GHz]);
	IS_PLL_LOCKED(blk_cmu_wbus_u->pll_con0_pll_wbus);

	SET_DIV(blk_cmu_wbus_u->clk_con_div_div1_wbus_u_aclk, 1);
	SET_DIV(blk_cmu_wbus_u->clk_con_div_div3_wbus_u_pclk, 3);

	SET_CON0_MUX_SEL(blk_cmu_wbus_u->pll_con0_pll_wbus, 1);
}

void cmu_blk_dram_init_evt0(uintptr_t base)
{
	CMU_BLK(dram, base);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy0);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy1);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy2);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy3);

	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk0, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk1, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk2, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk3, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div5_dram_wrck_icon, 5);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk0, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk1, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk2, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk3, 8);

	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, 1);
}

void cmu_blk_dram_init_evt1(uintptr_t base)
{
	CMU_BLK(dram, base);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy0, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy0);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy1, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy1);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy2, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy2);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy3, pll_table_f0435[_8_0GHz]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy3);

	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk0, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk1, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk2, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk3, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div5_dram_wrck_icon, 5);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk0, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk1, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk2, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk3, 4);

	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, 1);
}

/*
 * FIXME: This code is only valid in an environment where a dcl block exists.
 *  Please remove the comments and use it if necessary.
 */
/*
 *void cmu_blk_dcl_init(uintptr_t base)
 *{
 *	CMU_BLK(dcl, base);
 *
 *	SET_LOCKTIME(blk_cmu_dcl->pll_locktime_pll_dcl, pll_table_f0434[_1_8GHz]);
 *	SET_CON0_VAL(blk_cmu_dcl->pll_con0_pll_dcl, pll_table_f0434[_1_8GHz]);
 *	SET_CON3_VAL(blk_cmu_dcl->pll_con3_pll_dcl, pll_table_f0434[_1_8GHz]);
 *	IS_PLL_LOCKED(blk_cmu_dcl->pll_con0_pll_dcl);
 *
 *	SET_LOCKTIME(blk_cmu_dcl->pll_locktime_pll_dcl_dvfs, pll_table_f0434[_1_8GHz]);
 *	SET_CON0_VAL(blk_cmu_dcl->pll_con0_pll_dcl_dvfs, pll_table_f0434[_1_8GHz]);
 *	SET_CON3_VAL(blk_cmu_dcl->pll_con3_pll_dcl_dvfs, pll_table_f0434[_1_8GHz]);
 *	IS_PLL_LOCKED(blk_cmu_dcl->pll_con0_pll_dcl_dvfs);
 *
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_dcl_cmuref, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div4_hch_dcl_cmuref, 4);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk0, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk0, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk1, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk1, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk2, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk2, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk3, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk3, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk4, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk4, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk5, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk5, 2);
 *
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue0, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue0, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue1, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue1, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue2, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue2, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue3, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue3, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_sglue, 1);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_sglue, 2);
 *
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div4_dcl_pclk, 4);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div8_hch_dcl_pclk, 8);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div2_dcl_add, 2);
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div4_hch_dcl_add, 4);
 *
 *	SET_DIV(blk_cmu_dcl->clk_con_div_div5_dcl_oscclk, 5);
 *
 *	SET_MUX(blk_cmu_dcl->clk_con_mux_mux_dcl_pll_fout, 0);
 *
 *	SET_CON0_MUX_SEL(blk_cmu_dcl->pll_con0_pll_dcl, 1);
 *	SET_CON0_MUX_SEL(blk_cmu_dcl->pll_con0_pll_dcl_dvfs, 1);
 *}
 */
