/*
 * Copyright 2024-2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include "cmu.h"
#include <lib/mmio.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <rebel_h_pmu.h>
#include <errno.h>
#include <assert.h>

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

#define CMU_BLK(block, base_addr)			\
	volatile struct cmu_##block *const blk_cmu_##block = \
		(struct cmu_##block *)(uintptr_t)(base_addr)

#define CMU_CONT_BASE(block, base_addr)		\
	(base_addr) + sizeof(struct cmu_##block)
#define CMU_MUX_BASE(block, base_addr)		\
	CMU_CONT_BASE(block, base_addr) +	\
	sizeof(struct cmu_##block##_cont)
#define CMU_DIV_BASE(block, base_addr)		\
	CMU_MUX_BASE(block, base_addr) +	\
	sizeof(struct cmu_##block##_mux)
#define CMU_GATE_BASE(block, base_addr)		\
	CMU_DIV_BASE(block, base_addr) +	\
	sizeof(struct cmu_##block##_div)
#define CMU_QCH_BASE(block, base_addr)		\
	CMU_GATE_BASE(block, base_addr) +	\
	sizeof(struct cmu_##block##_gate)

struct pll_table {
	uint32_t target_freq;
	uint32_t p;
	uint32_t m;
	uint32_t s;
	uint32_t k;
};

static struct pll_table const pll_table_f0434[] = {
	{2300, 2, 115, 0, 0},
	{2000, 1, 100, 1, 0},
	{1800, 1, 90,  1, 0},
	{1700, 1, 85,  1, 0},
	{1600, 1, 80,  1, 0},
	{1500, 1, 75,  1, 0},
	{1400, 1, 70,  1, 0},
	{1200, 2, 120, 1, 0},
	{1000, 1, 100, 2, 0},
	{800,  2, 160, 2, 0},
};

static struct pll_table const pll_table_f0435[] = {
	{9600, 1, 120, 0, 0},
	{9200, 1, 115, 0, 0},
	{8000, 1, 100, 0, 0},
	{6400, 1, 80, 0, 0},
	{4800, 1, 60, 0, 0},
};

static int cmu_find_pll_lvl(const struct pll_table *table, const uint32_t target_freq)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pll_table_f0434); i++) {
		if (table[i].target_freq == target_freq)
			return i;
	}

	return -ENOTSUP;
}

static void cmu_blk_cp_init(uintptr_t base)
{
	CMU_BLK(cp, base);

	SET_LOCKTIME(blk_cmu_cp->pll_locktime_pll_cp, pll_table_f0434[_2_0GHZ]);
	SET_CON3_VAL(blk_cmu_cp->pll_con3_pll_cp, pll_table_f0434[_2_0GHZ]);
	SET_CON0_VAL(blk_cmu_cp->pll_con0_pll_cp, pll_table_f0434[_2_0GHZ]);
	IS_PLL_LOCKED(blk_cmu_cp->pll_con0_pll_cp);

	SET_LOCKTIME(blk_cmu_cp->pll_locktime_pll_cp_dvfs, pll_table_f0434[_2_3GHZ]);
	SET_CON3_VAL(blk_cmu_cp->pll_con3_pll_cp_dvfs, pll_table_f0434[_2_3GHZ]);
	SET_CON0_VAL(blk_cmu_cp->pll_con0_pll_cp_dvfs, pll_table_f0434[_2_3GHZ]);
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

static void cmu_blk_pcie_init(uintptr_t base)
{
	CMU_BLK(pcie, base);

	SET_LOCKTIME(blk_cmu_pcie->pll_locktime_pll_pcie, pll_table_f0434[_2_0GHZ]);
	SET_CON3_VAL(blk_cmu_pcie->pll_con3_pll_pcie, pll_table_f0434[_2_0GHZ]);
	SET_CON0_VAL(blk_cmu_pcie->pll_con0_pll_pcie, pll_table_f0434[_2_0GHZ]);
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

static void cmu_blk_rot_init(uintptr_t base)
{
	CMU_BLK(rot, base);

	SET_LOCKTIME(blk_cmu_rot->pll_locktime_pll_rot, pll_table_f0434[_1_5GHZ]);
	SET_CON3_VAL(blk_cmu_rot->pll_con3_pll_rot, pll_table_f0434[_1_5GHZ]);
	SET_CON0_VAL(blk_cmu_rot->pll_con0_pll_rot, pll_table_f0434[_1_5GHZ]);
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

static void cmu_blk_peri_init(uintptr_t base)
{
	CMU_BLK(peri, base);

	SET_LOCKTIME(blk_cmu_peri->pll_locktime_pll_peri, pll_table_f0434[_1_0GHZ]);
	SET_CON3_VAL(blk_cmu_peri->pll_con3_pll_peri, pll_table_f0434[_1_0GHZ]);
	SET_CON0_VAL(blk_cmu_peri->pll_con0_pll_peri, pll_table_f0434[_1_0GHZ]);
	IS_PLL_LOCKED(blk_cmu_peri->pll_con0_pll_peri);

	SET_DIV(blk_cmu_peri->clk_con_div_div2_peri_pclk, 4);

	SET_CON0_MUX_SEL(blk_cmu_peri->pll_con0_pll_peri, 1);
}

static void cmu_blk_ebus_d_init(uintptr_t base)
{
	CMU_BLK(ebus_d, base);

	SET_LOCKTIME(blk_cmu_ebus_d->pll_locktime_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	SET_CON3_VAL(blk_cmu_ebus_d->pll_con3_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	SET_CON0_VAL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	IS_PLL_LOCKED(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200);

	SET_DIV(blk_cmu_ebus_d->clk_con_div_div1_ebus_d_aclk, 1);
	SET_DIV(blk_cmu_ebus_d->clk_con_div_div3_ebus_d_pclk, 3);
	SET_DIV(blk_cmu_ebus_d->clk_con_div_div_ebus_d_sh_low_clk, 1);

	SET_USER_MUX(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1600, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, 1);
}

static void cmu_blk_ebus_r_init(uintptr_t base)
{
	CMU_BLK(ebus_r, base);

	SET_DIV(blk_cmu_ebus_r->clk_con_div_div1_ebus_r_aclk, 1);
	SET_DIV(blk_cmu_ebus_r->clk_con_div_div3_ebus_r_pclk, 3);

	SET_USER_MUX(blk_cmu_ebus_r->pll_con0_pll_ebus_r, 1);
}

static void cmu_blk_ebus_u_init(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(ebus_u, base);

	SET_LOCKTIME(blk_cmu_ebus_u->pll_locktime_pll_ebus, pll_table_f0434[lvl]);
	SET_CON3_VAL(blk_cmu_ebus_u->pll_con3_pll_ebus, pll_table_f0434[lvl]);
	SET_CON0_VAL(blk_cmu_ebus_u->pll_con0_pll_ebus, pll_table_f0434[lvl]);
	IS_PLL_LOCKED(blk_cmu_ebus_u->pll_con0_pll_ebus);

	SET_DIV(blk_cmu_ebus_u->clk_con_div_div1_ebus_u_aclk, 1);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div3_ebus_u_pclk, 3);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div_rbc_h0, 8);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div_rbc_h1, 8);
	SET_DIV(blk_cmu_ebus_u->clk_con_div_div1_ebus_u_sh_low_clk, 1);

	SET_USER_MUX(blk_cmu_ebus_u->pll_con0_pll_ctrl_ebus_u, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_u->pll_con0_pll_ebus, 1);
}

static void cmu_blk_nbus_d_init(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(nbus_d, base);

	SET_LOCKTIME(blk_cmu_nbus_d->pll_locktime_pll_nbus, pll_table_f0434[lvl]);
	SET_CON3_VAL(blk_cmu_nbus_d->pll_con3_pll_nbus, pll_table_f0434[lvl]);
	SET_CON0_VAL(blk_cmu_nbus_d->pll_con0_pll_nbus, pll_table_f0434[lvl]);
	IS_PLL_LOCKED(blk_cmu_nbus_d->pll_con0_pll_nbus);

	SET_DIV(blk_cmu_nbus_d->clk_con_div_div1_nbus_d_aclk, 1);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div3_nbus_d_pclk, 3);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div4_rbc_v0, 8);
	SET_DIV(blk_cmu_nbus_d->clk_con_div_div4_rbc_v1, 8);

	SET_CON0_MUX_SEL(blk_cmu_nbus_d->pll_con0_pll_nbus, 1);
}

static void cmu_blk_nbus_l_init(uintptr_t base)
{
	CMU_BLK(nbus_l, base);

	SET_DIV(blk_cmu_nbus_l->clk_con_div_div1_nbus_l_aclk, 1);
	SET_DIV(blk_cmu_nbus_l->clk_con_div_div3_nbus_l_pclk, 3);
	SET_DIV(blk_cmu_nbus_l->clk_con_div_div2_nbus_l_gclk, 2);

	SET_USER_MUX(blk_cmu_nbus_l->pll_con0_pll_nbus_l, 1);
}

static void cmu_blk_nbus_u_init(uintptr_t base)
{
	CMU_BLK(nbus_u, base);

	SET_DIV(blk_cmu_nbus_u->clk_con_div_div1_nbus_u_aclk, 1);
	SET_DIV(blk_cmu_nbus_u->clk_con_div_div3_nbus_u_pclk, 3);
	SET_DIV(blk_cmu_nbus_u->clk_con_div_div1_nbus_u_tclk, 1);

	SET_USER_MUX(blk_cmu_nbus_u->pll_con0_pll_nbus_u, 1);
}

static void cmu_blk_sbus_d_init(uintptr_t base)
{
	CMU_BLK(sbus_d, base);

	SET_DIV(blk_cmu_sbus_d->clk_con_div_div1_sbus_d_aclk, 1);
	SET_DIV(blk_cmu_sbus_d->clk_con_div_div3_sbus_d_pclk, 3);

	SET_USER_MUX(blk_cmu_sbus_d->pll_con0_pll_sbus_d, 1);
}

static void cmu_blk_sbus_l_init(uintptr_t base)
{
	CMU_BLK(sbus_l, base);

	SET_DIV(blk_cmu_sbus_l->clk_con_div_div1_sbus_l_aclk, 1);
	SET_DIV(blk_cmu_sbus_l->clk_con_div_div3_sbus_l_pclk, 3);

	SET_USER_MUX(blk_cmu_sbus_l->pll_con0_pll_sbus_l, 1);
}

static void cmu_blk_sbus_u_init(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(sbus_u, base);

	SET_LOCKTIME(blk_cmu_sbus_u->pll_locktime_pll_sbus, pll_table_f0434[lvl]);
	SET_CON3_VAL(blk_cmu_sbus_u->pll_con3_pll_sbus, pll_table_f0434[lvl]);
	SET_CON0_VAL(blk_cmu_sbus_u->pll_con0_pll_sbus, pll_table_f0434[lvl]);
	IS_PLL_LOCKED(blk_cmu_sbus_u->pll_con0_pll_sbus);

	SET_DIV(blk_cmu_sbus_u->clk_con_div_div1_sbus_u_aclk, 1);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div3_sbus_u_pclk, 3);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div4_rbc_v10, 8);
	SET_DIV(blk_cmu_sbus_u->clk_con_div_div4_rbc_v11, 8);

	SET_CON0_MUX_SEL(blk_cmu_sbus_u->pll_con0_pll_sbus, 1);
}

static void cmu_blk_wbus_d_init(uintptr_t base)
{
	CMU_BLK(wbus_d, base);

	SET_DIV(blk_cmu_wbus_d->clk_con_div_div1_wbus_d_aclk, 1);
	SET_DIV(blk_cmu_wbus_d->clk_con_div_div3_wbus_d_pclk, 3);

	SET_USER_MUX(blk_cmu_wbus_d->pll_con0_pll_wbus_d, 1);
}

static void cmu_blk_wbus_u_init(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(wbus_u, base);

	SET_LOCKTIME(blk_cmu_wbus_u->pll_locktime_pll_wbus, pll_table_f0434[lvl]);
	SET_CON3_VAL(blk_cmu_wbus_u->pll_con3_pll_wbus, pll_table_f0434[lvl]);
	SET_CON0_VAL(blk_cmu_wbus_u->pll_con0_pll_wbus, pll_table_f0434[lvl]);
	IS_PLL_LOCKED(blk_cmu_wbus_u->pll_con0_pll_wbus);

	SET_DIV(blk_cmu_wbus_u->clk_con_div_div1_wbus_u_aclk, 1);
	SET_DIV(blk_cmu_wbus_u->clk_con_div_div3_wbus_u_pclk, 3);

	SET_CON0_MUX_SEL(blk_cmu_wbus_u->pll_con0_pll_wbus, 1);
}

void cmu_blk_dram_init_evt0(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(dram, base);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy0, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy0, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy0);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy1, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy1, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy1);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy2, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy2, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy2);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy3, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy3, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy3);

	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk0, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk1, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk2, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk3, 2);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk0, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk1, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk2, 8);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk3, 8);

	/* Note: This WRCK is coming from OSC:40MHz, DIV=2 so, it goes to 20MHz */
	SET_DIV(blk_cmu_dram->clk_con_div_div5_dram_wrck_icon, 2);

	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, 1);
}

void cmu_blk_dram_init_evt1(uintptr_t base, uint32_t lvl)
{
	CMU_BLK(dram, base);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy0, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy0, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy0);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy1, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy1, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy1);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy2, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy2, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy2);

	SET_LOCKTIME(blk_cmu_dram->pll_locktime_pll_hbm3_phy3, pll_table_f0435[lvl]);
	SET_CON3_VAL(blk_cmu_dram->pll_con3_pll_hbm3_phy3, pll_table_f0435[lvl]);
	SET_CON0_VAL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, pll_table_f0435[lvl]);
	IS_PLL_LOCKED(blk_cmu_dram->pll_con0_pll_hbm3_phy3);

	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk0, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk1, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk2, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div2_dram_aclk3, 1);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk0, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk1, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk2, 4);
	SET_DIV(blk_cmu_dram->clk_con_div_div8_dram_pclk3, 4);

	/* Note: This WRCK is coming from OSC:40MHz, DIV=2 so, it goes to 20MHz */
	SET_DIV(blk_cmu_dram->clk_con_div_div5_dram_wrck_icon, 2);

	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy0, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy1, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy2, 1);
	SET_CON0_MUX_SEL(blk_cmu_dram->pll_con0_pll_hbm3_phy3, 1);
}

void cmu_blk_dram_init_evt0_by_freq(uintptr_t base, uint32_t target_freq)
{
	int pll_lvl;

	pll_lvl = cmu_find_pll_lvl(pll_table_f0435, target_freq);
	if (pll_lvl < 0)
		assert(0);

	cmu_blk_dram_init_evt0(base, pll_lvl);
}

void cmu_blk_dram_init_evt1_by_freq(uintptr_t base, uint32_t target_freq)
{
	int pll_lvl;

	pll_lvl = cmu_find_pll_lvl(pll_table_f0435, target_freq);
	if (pll_lvl < 0)
		assert(0);

	cmu_blk_dram_init_evt1(base, pll_lvl);
}

static void local_cmu_blk_rbc_init_evt0(const uintptr_t base)
{
	CMU_BLK(rbc_evt0, base);

	blk_cmu_rbc_evt0->rbc_cmu_rbc_controller_option.enable_power_management = 1;
	SET_DIV(blk_cmu_rbc_evt0->clk_con_div_div1_rbc_aclk0, 1);
	SET_DIV(blk_cmu_rbc_evt0->clk_con_div_div1_rbc_pclk, 1);
	SET_DIV(blk_cmu_rbc_evt0->clk_con_div_div2_rbc_scan_750, 2);
	SET_DIV(blk_cmu_rbc_evt0->clk_con_div_div3_rbc_scan_500, 3);

	blk_cmu_rbc_evt0->pll_con0_pll_ctrl_rbc0.mux_sel = 1;
	blk_cmu_rbc_evt0->pll_con0_pll_ctrl_rbc2.mux_sel = 1;
}

static void local_cmu_blk_rbc_init_evt1(const uintptr_t base)
{
	CMU_BLK(rbc_evt1, base);

	blk_cmu_rbc_evt1->rbc_cmu_rbc_controller_option.enable_power_management = 1;
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div1_rbc_aclk0, 1);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div1_rbc_pclk, 5);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc0, 1);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc1, 1);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc2, 5);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc3, 2);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc4, 4);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc5, 2);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_rbc_dft_1000, 1);
	SET_DIV(blk_cmu_rbc_evt1->clk_con_div_div_rbc_dft_500, 2);

	blk_cmu_rbc_evt1->pll_con0_pll_ctrl_rbc0.mux_sel = 1;
	blk_cmu_rbc_evt1->pll_con0_pll_ctrl_rbc2.mux_sel = 1;
}

static void remote_cmu_blk_rbc_init_evt0(const uintptr_t base, const uint32_t chiplet_id)
{
	const uint32_t qspi_channel = 2;

	CMU_BLK(rbc_evt0, base);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->rbc_cmu_rbc_controller_option,
							0x20000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->clk_con_div_div1_rbc_aclk0,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->clk_con_div_div1_rbc_pclk,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->clk_con_div_div2_rbc_scan_750,
							0x00000001, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->clk_con_div_div3_rbc_scan_500,
							0x00000002, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->pll_con0_pll_ctrl_rbc0, 0x00000010, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt0->pll_con0_pll_ctrl_rbc2, 0x00000010, chiplet_id);
}

static void remote_cmu_blk_rbc_init_evt1(const uintptr_t base, const uint32_t chiplet_id)
{
	const uint32_t qspi_channel = 2;

	CMU_BLK(rbc_evt1, base);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->rbc_cmu_rbc_controller_option,
							0x20000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div1_rbc_aclk0,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div1_rbc_pclk,
							0x00000004, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc0,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc1,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc2,
							0x00000004, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc3,
							0x00000001, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc4,
							0x00000003, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_ucie_extocc5,
							0x00000001, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_rbc_dft_1000,
							0x00000000, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->clk_con_div_div_rbc_dft_500,
							0x00000001, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->pll_con0_pll_ctrl_rbc0, 0x00000010, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&blk_cmu_rbc_evt1->pll_con0_pll_ctrl_rbc2, 0x00000010, chiplet_id);
}

#if DCL_CNT >= 1
static void cmu_blk_dcl_init(uintptr_t base)
{
	int pll_lvl;
	uint32_t rev = GET_REVISION;
	uint32_t target_freq = DCL_FREQ;

	CMU_BLK(dcl, base);

	/* EVT1 DCL Max freq is changed to 1700 MHz */
	if (rev == REVISION_EVT1 && target_freq == 1800)
		target_freq = 1700;

	pll_lvl = cmu_find_pll_lvl(pll_table_f0434, DCL_FREQ);
	if (pll_lvl < 0)
		assert(0);

	SET_LOCKTIME(blk_cmu_dcl->pll_locktime_pll_dcl, pll_table_f0434[pll_lvl]);
	SET_CON3_VAL(blk_cmu_dcl->pll_con3_pll_dcl, pll_table_f0434[pll_lvl]);
	SET_CON0_VAL(blk_cmu_dcl->pll_con0_pll_dcl, pll_table_f0434[pll_lvl]);
	IS_PLL_LOCKED(blk_cmu_dcl->pll_con0_pll_dcl);

	SET_LOCKTIME(blk_cmu_dcl->pll_locktime_pll_dcl_dvfs, pll_table_f0434[pll_lvl]);
	SET_CON3_VAL(blk_cmu_dcl->pll_con3_pll_dcl_dvfs, pll_table_f0434[pll_lvl]);
	SET_CON0_VAL(blk_cmu_dcl->pll_con0_pll_dcl_dvfs, pll_table_f0434[pll_lvl]);
	IS_PLL_LOCKED(blk_cmu_dcl->pll_con0_pll_dcl_dvfs);

	SET_DIV(blk_cmu_dcl->clk_con_div_div2_dcl_cmuref, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div4_hch_dcl_cmuref, 4);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk0, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk0, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk1, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk1, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk2, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk2, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk3, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk3, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk4, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk4, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk5, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk5, 2);

	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue0, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue0, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue1, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue1, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue2, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue2, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue3, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue3, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div_dcl_aclk_sglue, 1);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_sglue, 2);

	SET_DIV(blk_cmu_dcl->clk_con_div_div4_dcl_pclk, 4);
	SET_DIV(blk_cmu_dcl->clk_con_div_div8_hch_dcl_pclk, 8);
	SET_DIV(blk_cmu_dcl->clk_con_div_div2_dcl_add, 2);
	SET_DIV(blk_cmu_dcl->clk_con_div_div4_hch_dcl_add, 4);
	SET_DIV(blk_cmu_dcl->clk_con_div_div9_dcl_pvt, 9);

	SET_DIV(blk_cmu_dcl->clk_con_div_div5_dcl_oscclk, 5);

	SET_MUX(blk_cmu_dcl->clk_con_mux_mux_dcl_pll_fout, 0);

	SET_CON0_MUX_SEL(blk_cmu_dcl->pll_con0_pll_dcl, 1);
	SET_CON0_MUX_SEL(blk_cmu_dcl->pll_con0_pll_dcl_dvfs, 1);
}
#endif /* DCL_CNT */

static void cmu_top_bus(uintptr_t chiplet_offset, uint32_t lvl)
{
	cmu_blk_ebus_d_init(chiplet_offset + CMU_EBUS_D);
	cmu_blk_ebus_r_init(chiplet_offset + CMU_EBUS_R);
	cmu_blk_ebus_u_init(chiplet_offset + CMU_EBUS_U, lvl);
	cmu_blk_nbus_d_init(chiplet_offset + CMU_NBUS_D, lvl);
	cmu_blk_nbus_l_init(chiplet_offset + CMU_NBUS_L);
	cmu_blk_nbus_u_init(chiplet_offset + CMU_NBUS_U);
	cmu_blk_sbus_d_init(chiplet_offset + CMU_SBUS_D);
	cmu_blk_sbus_l_init(chiplet_offset + CMU_SBUS_L);
	cmu_blk_sbus_u_init(chiplet_offset + CMU_SBUS_U, lvl);
	cmu_blk_wbus_d_init(chiplet_offset + CMU_WBUS_D);
	cmu_blk_wbus_u_init(chiplet_offset + CMU_WBUS_U, lvl);
}

void cmu_init_bl1(const uint32_t bootmode)
{
	int pll_lvl;

	cmu_blk_cp_init(CMU_CP0);
	cmu_blk_peri_init(CMU_PERI1);

	if (bootmode != SECURE_OTP_BOOT && bootmode != SECURE_XIP_BOOT) {
		cmu_blk_pcie_init(CMU_PCIE);
		cmu_blk_rot_init(CMU_ROT);
		cmu_blk_peri_init(CMU_PERI0);

		pll_lvl = cmu_find_pll_lvl(pll_table_f0434, BUS_FREQ);
		if (pll_lvl < 0)
			assert(0);

		cmu_top_bus(0, pll_lvl);
	}
}

void cmu_init_bl2(uintptr_t chiplet_offset)
{
	int pll_lvl;

	if (chiplet_offset) {
		cmu_blk_cp_init(chiplet_offset + CMU_CP0);
		cmu_blk_rot_init(chiplet_offset + CMU_ROT);
		cmu_blk_peri_init(chiplet_offset + CMU_PERI0);

		pll_lvl = cmu_find_pll_lvl(pll_table_f0434, BUS_FREQ);
		if (pll_lvl < 0)
			assert(0);
		cmu_top_bus(chiplet_offset, pll_lvl);

		/* Chiplet3.PCIe is used on EVT1 only */
		if (GET_REVISION == REVISION_EVT1 && (CHIPLET_OFFSET * CHIPLET_ID3 == chiplet_offset))
			cmu_blk_pcie_init(chiplet_offset + CMU_PCIE);
	}

	pll_lvl = cmu_find_pll_lvl(pll_table_f0435, HBM_DATA_RATE);
	if (pll_lvl < 0)
		assert(0);

	cmu_blk_cp_init(chiplet_offset + CMU_CP1);
	cmu_blk_peri_init(chiplet_offset + CMU_PERI1);
	if (GET_REVISION == REVISION_EVT0) {
		cmu_blk_dram_init_evt0(chiplet_offset + CMU_DRAM, pll_lvl);
	} else {
		cmu_blk_dram_init_evt1(chiplet_offset + CMU_DRAM, pll_lvl);
	}

#if (DCL_CNT >= 1)
	cmu_blk_dcl_init(chiplet_offset + CMU_DCL0);
	cmu_blk_dcl_init(chiplet_offset + CMU_DCL1);
#endif /* DCL_CNT */
}

void cmu_init_rbc(const uint32_t chiplet_id, const uintptr_t base_addr)
{
	if (GET_REVISION == REVISION_EVT0) {
		if (chiplet_id == CHIPLET_ID) {
			local_cmu_blk_rbc_init_evt0(base_addr);
		} else {
			remote_cmu_blk_rbc_init_evt0(base_addr, chiplet_id);
		}
	} else {
		if (chiplet_id == CHIPLET_ID) {
			local_cmu_blk_rbc_init_evt1(base_addr);
		} else {
			remote_cmu_blk_rbc_init_evt1(base_addr, chiplet_id);
		}
	}
}
