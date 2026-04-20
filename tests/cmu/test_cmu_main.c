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

#include <stdint.h>
#include <rebel_h_platform.h>
#include "rl_utils.h"
#include "test_common.h"
#include "cmu.h"

#define OSC_MHz								(40)

/* This table values delived from pll_table_f0434 in cmu.c */
uint32_t table_f0434[] = {
	2500, 2400, 2300, 2200, 2100, 2000, 1900, 1800, 1700, 1600, 1500,
	1300, 1200, 1000, 800, 600, 400
};

/* This table values delived from pll_table_f0435 in cmu.c */
uint32_t table_f0435[] = {
	8000, 6400
};

void set_pll_freq_f0434_test(char *name, volatile void *locktime, volatile void *con0,
							 volatile void *con3, uint64_t freq)
{
	printf(" - step0. %s freq: %luMHz\n", name, get_pll_freq_f0434(con0, con3));
	printf(" - step1. set as %uMHz\n", table_f0434[freq]);
	set_pll_freq_f0434(locktime, con0, con3, freq);
	printf(" - step2. %s freq: %luMHz\n\n", name, get_pll_freq_f0434(con0, con3));
}

void set_pll_freq_f0435_test(char *name, volatile void *locktime, volatile void *con0,
							 volatile void *con3, uint64_t freq)
{
	printf(" - step0. %s freq: %luMHz\n", name, get_pll_freq_f0435(con0, con3));
	printf(" - step1. set as %uMHz\n", table_f0435[freq]);
	set_pll_freq_f0435(locktime, con0, con3, freq);
	printf(" - step2. %s freq: %luMHz\n\n", name, get_pll_freq_f0435(con0, con3));
}

void set_hch_div_ratio_test(char *name, volatile void *div, volatile void *hch_div, uint32_t ratio)
{
	printf(" - step0. %s ratio: %u\n", name, get_hch_div_ratio(div, hch_div));
	printf(" - step1. set as %u\n", ratio);
	set_hch_div_ratio(div, hch_div, ratio);
	printf(" - step2. %s ratio: %u\n\n", name, get_hch_div_ratio(div, hch_div));
}

void set_div_ratio_test(char *name, volatile void *div, uint32_t ratio)
{
	printf(" - step0. %s ratio: %u\n", name, get_div_ratio(div));
	printf(" - step1. set as %u\n", ratio);
	set_div_ratio(div, ratio);
	printf(" - step2. %s ratio: %u\n\n", name, get_div_ratio(div));
}

void set_mux_sel_test(char *name, volatile void *mux, uint32_t sel)
{
	printf(" - step0. %s select: %u\n", name, get_mux_sel(mux));
	printf(" - step1. set as %u\n", sel);
	set_mux_sel(mux, sel);
	printf(" - step2. %s select: %u\n\n", name, get_mux_sel(mux));
}

void clk_gating_test(char *name, volatile void *gate, uint32_t val)
{
	printf(" - step0. %s status: %sABLE\n", name, is_clk_gated(gate) ? "EN" : "DIS");
	printf(" - step1. set as %sABLE\n", val ? "EN" : "DIS");
	clk_gating(gate, val);
	printf(" - step2. %s status: %sABLE\n\n", name, is_clk_gated(gate) ? "EN" : "DIS");
}

void set_clkout_test(uint64_t base, uint32_t blk_id, uint32_t clk_id)
{
	printf(" - clkout: 0x%x\n", set_clk_out(base, blk_id, clk_id));
}

void test_cmu_cp(uintptr_t base)
{
	CMU_BLK(cp, base);

	printf("---------------------------\n");
	printf("test_cmu_cp 0x%lx\n", base);

	printf("PLL test\n");
	set_pll_freq_f0434_test("pll_cp", &blk_cmu_cp->pll_locktime_pll_cp,
							&blk_cmu_cp->pll_con0_pll_cp,
							&blk_cmu_cp->pll_con3_pll_cp, _1_8GHz);
	set_pll_freq_f0434_test("pll_cp_dvfs", &blk_cmu_cp->pll_locktime_pll_cp_dvfs,
							&blk_cmu_cp->pll_con0_pll_cp_dvfs,
							&blk_cmu_cp->pll_con3_pll_cp_dvfs, _1_2GHz);

	printf("DIV test\n");
	set_hch_div_ratio_test("div2_cp_cmuref", &blk_cmu_cp->clk_con_div_div2_cp_cmuref,
						   &blk_cmu_cp->clk_con_div_div4_hch_cp_cmuref, 1);
	set_hch_div_ratio_test("div1_cp_coreclk", &blk_cmu_cp->clk_con_div_div1_cp_coreclk,
						   &blk_cmu_cp->clk_con_div_div2_hch_cp_coreclk, 1);
	set_hch_div_ratio_test("div2_cp_aclk", &blk_cmu_cp->clk_con_div_div2_cp_aclk,
						   &blk_cmu_cp->clk_con_div_div4_hch_cp_aclk, 1);
	set_hch_div_ratio_test("div4_cp_stm", &blk_cmu_cp->clk_con_div_div4_cp_stm,
						   &blk_cmu_cp->clk_con_div_div8_hch_cp_stm, 2);
	set_hch_div_ratio_test("div4_cp_pclk", &blk_cmu_cp->clk_con_div_div4_cp_pclk,
						   &blk_cmu_cp->clk_con_div_div8_hch_cp_pclk, 2);
	set_div_ratio_test("div1_cp_tsclk", &blk_cmu_cp->clk_con_div_div1_cp_tsclk, 2);
	set_div_ratio_test("div5_cp_add", &blk_cmu_cp->clk_con_div_div5_cp_add, 10);

	printf("MUX test\n");
	set_mux_sel_test("mux_cp_tsclk", &blk_cmu_cp->clk_con_mux_mux_cp_tsclk, 1);
	set_mux_sel_test("mux_cp_pll_fout", &blk_cmu_cp->clk_con_mux_mux_cp_pll_fout, 1);

	printf("CLKOUT test - After setting each clkout, measure using an oscilloscope.\n");

	uint32_t blk_id = base == CMU_CP0_PRIVATE ? CLKOUT_CMU_CP0 : CLKOUT_CMU_CP1;

	set_clkout_test(base, blk_id, OSCCLK_CP);
	set_clkout_test(base, blk_id, PLL_CP);
	set_clkout_test(base, blk_id, PLL_CP_DVFS);
	set_clkout_test(base, blk_id, CLK_CP_CORECLK);
	set_clkout_test(base, blk_id, CLK_CP_ACLK);
	set_clkout_test(base, blk_id, CLK_CP_PCLK);
	set_clkout_test(base, blk_id, CLK_CP_ADD);
	set_clkout_test(base, blk_id, CLK_CP_STM);
	set_clkout_test(base, blk_id, CLK_CP_TSCLK);
	set_clkout_test(base, blk_id, CLK_CP_CMUREF);
	set_clkout_test(base, blk_id, CP_CLK_LH_SCAN_DST);
	set_clkout_test(base, blk_id, CP_CLK_LH_SCAN_ETC);

	printf("---------------------------\n");
	printf("test_cmu_cp teardown\n\n");
	cmu_blk_cp_init(base);
}

void test_cmu_pcie(uintptr_t base)
{
	CMU_BLK(pcie, base);

	printf("---------------------------\n");
	printf("test_cmu_pcie 0x%lx\n", base);

	printf("PLL test\n");
	set_pll_freq_f0434_test("pll_pcie", &blk_cmu_pcie->pll_locktime_pll_pcie,
							&blk_cmu_pcie->pll_con0_pll_pcie,
							&blk_cmu_pcie->pll_con3_pll_pcie, _1_0GHz);

	printf("DIV test\n");
	set_div_ratio_test("div20_pcie_refclk_p", &blk_cmu_pcie->clk_con_div_div20_pcie_refclk_p, 10);
	set_div_ratio_test("div2_pcie_aclk", &blk_cmu_pcie->clk_con_div_div2_pcie_aclk, 4);
	set_div_ratio_test("div4_pcie_pclk", &blk_cmu_pcie->clk_con_div_div4_pcie_pclk, 8);
	set_div_ratio_test("div1_pcie_tsclk", &blk_cmu_pcie->clk_con_div_div1_pcie_tsclk, 2);
	set_div_ratio_test("div16_pcie_crparaclk", &blk_cmu_pcie->clk_con_div_div16_pcie_crparaclk, 8);
	set_div_ratio_test("div_pcie_auxclk", &blk_cmu_pcie->clk_con_div_div_pcie_auxclk, 5);

	printf("MUX test\n");
	set_mux_sel_test("mux_pcie_auxclk", &blk_cmu_pcie->clk_con_mux_mux_pcie_auxclk, 0);
	set_mux_sel_test("mux_pcie_tsclk", &blk_cmu_pcie->clk_con_mux_mux_pcie_tsclk, 1);

	printf("GATE test\n");
	clk_gating_test("cm7_qch", &blk_cmu_pcie->qch_con_cm7_qch, CLK_DISABLE);
	clk_gating_test("cm7_qch", &blk_cmu_pcie->qch_con_cm7_qch, CLK_ENABLE);

	printf("CLKOUT test - After setting each clkout, measure using an oscilloscope.\n");

	uint32_t blk_id = CLKOUT_CMU_PCIE;

	set_clkout_test(base, blk_id, OSCCLK_PCIE);
	set_clkout_test(base, blk_id, PLL_PCIE);
	set_clkout_test(base, blk_id, CLK_PCIE_ACLK);
	set_clkout_test(base, blk_id, CLK_PCIE_PCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_CRPARACLK);
	set_clkout_test(base, blk_id, CLK_PCIE_REFCLK_P);
	set_clkout_test(base, blk_id, CLK_PCIE_AUXCLK);
	set_clkout_test(base, blk_id, PCIE_CLK_LH_SCAN_DST);
	set_clkout_test(base, blk_id, PCIE_CLK_LH_SCAN_ETC);
	set_clkout_test(base, blk_id, CLK_PCIE_OSCCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_MAXPCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_RXCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_ROPLLCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_CRCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_DWORDCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_WORDCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_TSCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_SCAN_REFCLK);
	set_clkout_test(base, blk_id, CLK_PCIE_PHY_SCAN_CLK);

	printf("---------------------------\n");
	printf("test_cmu_pcie teardown\n\n");
	cmu_blk_pcie_init(base);
}

void test_cmu_rot(uintptr_t base)
{
	CMU_BLK(rot, base);

	printf("---------------------------\n");
	printf("test_cmu_rot 0x%lx\n", base);

	printf("PLL test\n");
	set_pll_freq_f0434_test("pll_rot", &blk_cmu_rot->pll_locktime_pll_rot,
							&blk_cmu_rot->pll_con0_pll_rot,
							&blk_cmu_rot->pll_con3_pll_rot, _1_0GHz);

	printf("DIV test\n");
	set_div_ratio_test("div4_rot_otp", &blk_cmu_rot->clk_con_div_div4_rot_otp, 8);
	set_div_ratio_test("div2_rot_aclk", &blk_cmu_rot->clk_con_div_div2_rot_aclk, 4);
	set_div_ratio_test("div7_rot_pvt", &blk_cmu_rot->clk_con_div_div7_rot_pvt, 14);
	set_div_ratio_test("div3_rot_pclk", &blk_cmu_rot->clk_con_div_div3_rot_pclk, 6);
	set_div_ratio_test("div1_rot_tsclk", &blk_cmu_rot->clk_con_div_div1_rot_tsclk, 2);
	set_div_ratio_test("div3_rot_cntclk", &blk_cmu_rot->clk_con_div_div3_rot_cntclk, 6);
	set_div_ratio_test("div3_rot_trck", &blk_cmu_rot->clk_con_div_div3_rot_rtck, 6);

	printf("MUX test\n");
	set_mux_sel_test("mux_rot_tsclk", &blk_cmu_rot->clk_con_mux_mux_rot_tsclk, 1);

	printf("CLKOUT test - After setting each clkout, measure using an oscilloscope.\n");

	uint32_t blk_id = CLKOUT_CMU_ROT;

	set_clkout_test(base, blk_id, OSCCLK_ROT);
	set_clkout_test(base, blk_id, PLL_ROT);
	set_clkout_test(base, blk_id, CLK_ROT_ACLK);
	set_clkout_test(base, blk_id, CLK_ROT_PCLK);
	set_clkout_test(base, blk_id, CLK_ROT_PVT_mainCLK);
	set_clkout_test(base, blk_id, CLK_ROT_DFT);
	set_clkout_test(base, blk_id, CLK_ROT_OSCCLK);
	set_clkout_test(base, blk_id, CLK_ROT_OTPCLK);
	set_clkout_test(base, blk_id, CM_SYS_TST_FRO_CLK_OUT);
	set_clkout_test(base, blk_id, CLK_ROT_CNTCLK);
	set_clkout_test(base, blk_id, CLK_ROT_TSCLK);
	set_clkout_test(base, blk_id, CLK_ROT_RTCK);
	set_clkout_test(base, blk_id, ROT_CLK_LH_SCAN_DST);
	set_clkout_test(base, blk_id, ROT_CLK_LH_SCAN_ETC);

	printf("---------------------------\n");
	printf("test_cmu_rot teardown\n\n");
	cmu_blk_rot_init(base);
}

void test_cmu_peri(uintptr_t base)
{
	CMU_BLK(peri, base);

	printf("---------------------------\n");
	printf("test_cmu_peri 0x%lx\n", base);

	printf("PLL test\n");
	set_pll_freq_f0434_test("pll_peri", &blk_cmu_peri->pll_locktime_pll_peri,
							&blk_cmu_peri->pll_con0_pll_peri,
							&blk_cmu_peri->pll_con3_pll_peri, _1_2GHz);

	printf("DIV test\n");
	set_div_ratio_test("div2_peri_pclk", &blk_cmu_peri->clk_con_div_div2_peri_pclk, 3);

	printf("GATE test\n");
	clk_gating_test("uart1", &blk_cmu_peri->qch_con_uart1_peri_qch, CLK_DISABLE);
	clk_gating_test("uart1", &blk_cmu_peri->qch_con_uart1_peri_qch, CLK_ENABLE);
	clk_gating_test("i2c0", &blk_cmu_peri->qch_con_i2c0_peri_qch, CLK_DISABLE);
	clk_gating_test("i2c0", &blk_cmu_peri->qch_con_i2c0_peri_qch, CLK_ENABLE);
	clk_gating_test("i2c1", &blk_cmu_peri->qch_con_i2c1_peri_qch, CLK_DISABLE);
	clk_gating_test("i2c1", &blk_cmu_peri->qch_con_i2c1_peri_qch, CLK_ENABLE);
	clk_gating_test("qspi0", &blk_cmu_peri->qch_con_qspi0_peri_qch, CLK_DISABLE);
	clk_gating_test("qspi0", &blk_cmu_peri->qch_con_qspi0_peri_qch, CLK_ENABLE);
	clk_gating_test("qspi1", &blk_cmu_peri->qch_con_qspi1_peri_qch, CLK_DISABLE);
	clk_gating_test("qspi1", &blk_cmu_peri->qch_con_qspi1_peri_qch, CLK_ENABLE);
	clk_gating_test("qspi2", &blk_cmu_peri->qch_con_qspi2_peri_qch, CLK_DISABLE);
	clk_gating_test("qspi2", &blk_cmu_peri->qch_con_qspi2_peri_qch, CLK_ENABLE);
	clk_gating_test("qspi3", &blk_cmu_peri->qch_con_qspi3_peri_qch, CLK_DISABLE);
	clk_gating_test("qspi3", &blk_cmu_peri->qch_con_qspi3_peri_qch, CLK_ENABLE);
	clk_gating_test("wdt0", &blk_cmu_peri->qch_con_wdt0_peri_qch, CLK_DISABLE);
	clk_gating_test("wdt0", &blk_cmu_peri->qch_con_wdt0_peri_qch, CLK_ENABLE);
	clk_gating_test("wdt1", &blk_cmu_peri->qch_con_wdt1_peri_qch, CLK_DISABLE);
	clk_gating_test("wdt1", &blk_cmu_peri->qch_con_wdt1_peri_qch, CLK_ENABLE);
	clk_gating_test("pwm", &blk_cmu_peri->qch_con_pwm_peri_qch, CLK_DISABLE);
	clk_gating_test("pwm", &blk_cmu_peri->qch_con_pwm_peri_qch, CLK_ENABLE);
	clk_gating_test("gpio_peri", &blk_cmu_peri->qch_con_gpio_peri_qch, CLK_DISABLE);
	clk_gating_test("gpio_peri", &blk_cmu_peri->qch_con_gpio_peri_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m5", &blk_cmu_peri->qch_con_mailbox_m5_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m5", &blk_cmu_peri->qch_con_mailbox_m5_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m6", &blk_cmu_peri->qch_con_mailbox_m6_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m6", &blk_cmu_peri->qch_con_mailbox_m6_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m7", &blk_cmu_peri->qch_con_mailbox_m7_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m7", &blk_cmu_peri->qch_con_mailbox_m7_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m8", &blk_cmu_peri->qch_con_mailbox_m8_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m8", &blk_cmu_peri->qch_con_mailbox_m8_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m9", &blk_cmu_peri->qch_con_mailbox_m9_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m9", &blk_cmu_peri->qch_con_mailbox_m9_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m10", &blk_cmu_peri->qch_con_mailbox_m10_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m10", &blk_cmu_peri->qch_con_mailbox_m10_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m11", &blk_cmu_peri->qch_con_mailbox_m11_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m11", &blk_cmu_peri->qch_con_mailbox_m11_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m12", &blk_cmu_peri->qch_con_mailbox_m12_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m12", &blk_cmu_peri->qch_con_mailbox_m12_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m13", &blk_cmu_peri->qch_con_mailbox_m13_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m13", &blk_cmu_peri->qch_con_mailbox_m13_qch, CLK_ENABLE);
	clk_gating_test("mailbox_m14", &blk_cmu_peri->qch_con_mailbox_m14_qch, CLK_DISABLE);
	clk_gating_test("mailbox_m14", &blk_cmu_peri->qch_con_mailbox_m14_qch, CLK_ENABLE);

	printf("CLKOUT test - After setting each clkout, measure using an oscilloscope.\n");

	uint32_t blk_id = (base == CMU_PERI0) ? CLKOUT_CMU_PERI0 : CLKOUT_CMU_PERI1;

	set_clkout_test(base, blk_id, OSCCLK_PERI);
	set_clkout_test(base, blk_id, CLK_PERI_PCLK);
	set_clkout_test(base, blk_id, CLK_PERI_OSCCLK);
	set_clkout_test(base, blk_id, CLK_PERI_IC_CLK);
	set_clkout_test(base, blk_id, PERI_CLK_LH_SCAN_DST);
	set_clkout_test(base, blk_id, PERI_CLK_LH_SCAN_ETC);

	printf("---------------------------\n");
	printf("test_cmu_peri teardown\n\n");
	cmu_blk_peri_init(base);
}

void test_cmu_dram(uintptr_t base)
{
	CMU_BLK(dram, base);

	printf("---------------------------\n");
	printf("test_cmu_dram 0x%lx\n", base);

	printf("PLL test\n");
	set_pll_freq_f0435_test("pll_hbm3_phy0", &blk_cmu_dram->pll_locktime_pll_hbm3_phy0,
							&blk_cmu_dram->pll_con0_pll_hbm3_phy0,
							&blk_cmu_dram->pll_con3_pll_hbm3_phy0, _6_4GHz);
	set_pll_freq_f0435_test("pll_hbm3_phy1", &blk_cmu_dram->pll_locktime_pll_hbm3_phy1,
							&blk_cmu_dram->pll_con0_pll_hbm3_phy1,
							&blk_cmu_dram->pll_con3_pll_hbm3_phy1, _6_4GHz);
	set_pll_freq_f0435_test("pll_hbm3_phy2", &blk_cmu_dram->pll_locktime_pll_hbm3_phy1,
							&blk_cmu_dram->pll_con0_pll_hbm3_phy2,
							&blk_cmu_dram->pll_con3_pll_hbm3_phy2, _6_4GHz);
	set_pll_freq_f0435_test("pll_hbm3_phy3", &blk_cmu_dram->pll_locktime_pll_hbm3_phy3,
							&blk_cmu_dram->pll_con0_pll_hbm3_phy3,
							&blk_cmu_dram->pll_con3_pll_hbm3_phy3, _6_4GHz);

	printf("DIV test\n");
	set_div_ratio_test("div2_dram_aclk0", &blk_cmu_dram->clk_con_div_div2_dram_aclk0, 4);
	set_div_ratio_test("div8_dram_pclk0", &blk_cmu_dram->clk_con_div_div8_dram_pclk0, 16);
	set_div_ratio_test("div2_dram_aclk1", &blk_cmu_dram->clk_con_div_div2_dram_aclk1, 4);
	set_div_ratio_test("div8_dram_pclk1", &blk_cmu_dram->clk_con_div_div8_dram_pclk1, 16);
	set_div_ratio_test("div2_dram_aclk2", &blk_cmu_dram->clk_con_div_div2_dram_aclk2, 4);
	set_div_ratio_test("div8_dram_pclk2", &blk_cmu_dram->clk_con_div_div8_dram_pclk2, 16);
	set_div_ratio_test("div2_dram_aclk3", &blk_cmu_dram->clk_con_div_div2_dram_aclk3, 4);
	set_div_ratio_test("div8_dram_pclk3", &blk_cmu_dram->clk_con_div_div8_dram_pclk3, 16);

	printf("CLKOUT test - After setting each clkout, measure using an oscilloscope.\n");

	uint32_t blk_id = CLKOUT_CMU_DRAM;

	set_clkout_test(base, blk_id, OSCCLK_DRAM);
	set_clkout_test(base, blk_id, PLL_HBM3_PHY0_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3_PHY1_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3_PHY2_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3_PHY3_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3P_PHY0_GFMUX_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3P_PHY1_GFMUX_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3P_PHY2_GFMUX_OUT_0);
	set_clkout_test(base, blk_id, PLL_HBM3P_PHY3_GFMUX_OUT_0);
	set_clkout_test(base, blk_id, CLK_DRAM_ACLK0);
	set_clkout_test(base, blk_id, CLK_DRAM_ACLK1);
	set_clkout_test(base, blk_id, CLK_DRAM_ACLK2);
	set_clkout_test(base, blk_id, CLK_DRAM_ACLK3);
	set_clkout_test(base, blk_id, CLK_DRAM_PCLK0);
	set_clkout_test(base, blk_id, CLK_DRAM_PCLK1);
	set_clkout_test(base, blk_id, CLK_DRAM_PCLK2);
	set_clkout_test(base, blk_id, CLK_DRAM_PCLK3);
	set_clkout_test(base, blk_id, CLK_DRAM_WRCK_ICON);
	set_clkout_test(base, blk_id, CLK_DRAM_PHY_OSC);
	set_clkout_test(base, blk_id, DRAM_CLK_LH_SCAN_DST);
	set_clkout_test(base, blk_id, DRAM_CLK_LH_SCAN_ETC);

	printf("---------------------------\n");
	printf("test_cmu_dram teardown\n\n");

	if (GET_REVISION == REVISION_EVT0) {
		cmu_blk_dram_init_evt0(base);
	} else {
		cmu_blk_dram_init_evt1(base);
	}
}

void freq_cmu_cp(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(cp, base);

	printf("------------------------ BLK_CP start ------------------------\n");
	clk1 = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp, &blk_cmu_cp->pll_con3_pll_cp);
	clk2 = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp_dvfs, &blk_cmu_cp->pll_con3_pll_cp_dvfs);

	printf("PLL_CP:			%luMHz\n", clk1);
	printf("PLL_CP_DVFS:		%luMHz\n", clk2);

	clk1 = get_mux_freq(&blk_cmu_cp->clk_con_mux_mux_cp_pll_fout, clk1, clk2);
	printf("\tMUX_CP_PLL_FOUT		%luMHz\n", clk1);

	clk2 = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div2_cp_cmuref,
							&blk_cmu_cp->clk_con_div_div4_hch_cp_cmuref, clk1);
	printf("\t\tDIV2_CP_CMUREF		%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_CMUREF		%luMHz\n", clk2);
	clk2 = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div1_cp_coreclk,
							&blk_cmu_cp->clk_con_div_div2_hch_cp_coreclk, clk1);
	printf("\t\tDIV2_CP_CORECLK		%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_CORECLK	%luMHz\n", clk2);
	clk2 = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div2_cp_aclk,
							&blk_cmu_cp->clk_con_div_div4_hch_cp_aclk, clk1);
	printf("\t\tDIV2_CP_ACLK		%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_ACLK		%luMHz\n", clk2);
	clk2 = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div4_cp_stm,
							&blk_cmu_cp->clk_con_div_div8_hch_cp_stm, clk1);
	printf("\t\tDIV4_CP_STM			%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_STM		%luMHz\n", clk2);
	clk2 = get_hch_div_freq(&blk_cmu_cp->clk_con_div_div4_cp_pclk,
							&blk_cmu_cp->clk_con_div_div8_hch_cp_pclk, clk1);
	printf("\t\tDIV4_CP_PCLK		%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_PCLK		%luMHz\n", clk2);

	clk1 = get_mux_freq(&blk_cmu_cp->clk_con_mux_mux_cp_tsclk, clk2, OSC_MHz);
	printf("\tMUX_CP_TSCLK			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_cp->clk_con_div_div1_cp_tsclk, clk1);
	printf("\t\tDIV1_CP_TSCLK		%luMHz\n", clk2);
	printf("\t\t\tCLK_CP_TSCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_cp->clk_con_div_div5_cp_add, OSC_MHz);
	printf("DIV5_CP_ADD			%luMHz\n", clk2);
	printf("\tCLK_CP_ADD		%luMHz\n", clk2);

	printf("------------------------ BLK_CP end ------------------------\n\n");
}

void set_freq_cp(uintptr_t base, const char *target, uint32_t freq_mhz)
{
	uint32_t freq_idx;
	uint32_t is_matched = 0;

	for (freq_idx = 0; freq_idx < ARRAY_SIZE(table_f0434); freq_idx++) {

		if (table_f0434[freq_idx] == freq_mhz) {
			is_matched = 1;
			break;
		}
	}

	if (!is_matched) {
		printf("%s : not supported freq.: %uMHz\n", target, freq_mhz);

		printf(" idx / freq.(MHz)\n");
		for (freq_idx = 0; freq_idx < ARRAY_SIZE(table_f0434); freq_idx++)
			printf("  %d / %u\n", freq_idx, table_f0434[freq_idx]);
		return;
	}

	CMU_BLK(cp, base);

	uint32_t prev, curr;

	prev = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp, &blk_cmu_cp->pll_con3_pll_cp);

	if (prev == freq_mhz) {
		printf("%s : The current running freq. is requested. %uMHz\n", target, freq_mhz);
		return;
	}

	set_pll_freq_f0434(&blk_cmu_cp->pll_locktime_pll_cp,
					   &blk_cmu_cp->pll_con0_pll_cp,
					   &blk_cmu_cp->pll_con3_pll_cp, freq_idx);

	curr = get_pll_freq_f0434(&blk_cmu_cp->pll_con0_pll_cp, &blk_cmu_cp->pll_con3_pll_cp);

	printf("%s : freq. changed: prev %uMHz -> curr %uMHz\n", target, prev, curr);
}

void freq_cmu_pcie(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;
	uint64_t clk3;

	CMU_BLK(pcie, base);

	printf("------------------------ BLK_PCIE start ------------------------\n");
	clk1 = get_pll_freq_f0434(&blk_cmu_pcie->pll_con0_pll_pcie, &blk_cmu_pcie->pll_con3_pll_pcie);
	printf("PLL_PCIE:		%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_pcie->clk_con_div_div20_pcie_refclk_p, clk1);
	printf("\tDIV20_PCIE_REFCLK_P	%luMHz\n", clk2);
	printf("\t\tCLK_PCIE_REFCLK_P	%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_pcie->clk_con_div_div2_pcie_aclk, clk1);
	printf("\tDIV2_PCIE_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_PCIE_ACLK		%luMHz\n", clk2);

	clk3 = get_div_freq(&blk_cmu_pcie->clk_con_div_div4_pcie_pclk, clk1);
	printf("\tDIV1_PCIE_TSCLK		%luMHz\n", clk3);
	printf("\t\tCLK_PCIE_TSCLK	%luMHz\n", clk3);

	clk2 = get_mux_freq(&blk_cmu_pcie->clk_con_mux_mux_pcie_tsclk, clk3, OSC_MHz);
	printf("\t\tMUX_PCIE_TSCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_pcie->clk_con_div_div1_pcie_tsclk, clk2);
	printf("\t\t\tDIV1_PCIE_TSCLK	%luMHz\n", clk2);
	printf("\t\t\t\tCLK_PCIE_TSCLK	%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_pcie->clk_con_div_div16_pcie_crparaclk, clk1);
	printf("\t\tDIV16_PCIE_CRPARACLK %luMHz\n", clk2);
	printf("\t\t\tCLK_PCIE_CRPARACLK %luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_pcie->clk_con_div_div_pcie_auxclk, clk3);
	printf("\t\tDIV_PCIE_AUXCLK		%luMHz\n", clk2);

	clk2 = get_mux_freq(&blk_cmu_pcie->clk_con_mux_mux_pcie_auxclk, OSC_MHz, clk2);
	printf("\t\t\tMUX_PCIE_AUXCLK		%luMHz\n", clk2);
	printf("\t\t\t\tCLK_PCIE_AUXCLK		%luMHz\n", clk2);

	printf("------------------------ BLK_PCIE end ------------------------\n\n");
}

void freq_cmu_rot(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(rot, base);

	printf("------------------------ BLK_ROT start ------------------------\n");
	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div4_rot_otp, OSC_MHz);
	printf("\tDIV4_ROT_OTP			%luMHz\n", clk2);
	printf("\t\tCLK_ROT_OTPCLK		%luMHz\n", clk2);

	clk1 = get_pll_freq_f0434(&blk_cmu_rot->pll_con0_pll_rot, &blk_cmu_rot->pll_con3_pll_rot);
	printf("PLL_ROT:		%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div2_rot_aclk, clk1);
	printf("\tDIV2_ROT_ACLK			%luMHz\n", clk2);
	printf("\t\tCLK_ROT_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div7_rot_pvt, clk1);
	printf("\tDIV7_ROT_PVT			%luMHz\n", clk2);
	printf("\t\tCLK_ROT_PVT_mainCLK	%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div3_rot_pclk, clk1);
	printf("\tDIV3_ROT_PCLK			%luMHz\n", clk2);
	printf("\t\tCLK_ROT_PCLK		%luMHz\n", clk2);

	clk2 = get_mux_freq(&blk_cmu_rot->clk_con_mux_mux_rot_tsclk, clk2, OSC_MHz);
	printf("\tMUX_ROT_TSCLK			%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div1_rot_tsclk, clk2);
	printf("\tDIV1_ROT_TSCLK		%luMHz\n", clk2);
	printf("\t\tCLK_ROT_TSCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div3_rot_cntclk, clk1);
	printf("\tDIV3_ROT_CNTCLK		%luMHz\n", clk2);
	printf("\t\tCLK_ROT_CNTCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_rot->clk_con_div_div3_rot_rtck, clk1);
	printf("\tDIV3_ROT_RTCLK		%luMHz\n", clk2);
	printf("\t\tCLK_ROT_RTCK		%luMHz\n", clk2);

	printf("------------------------ BLK_ROT end ------------------------\n\n");
}

void freq_cmu_peri(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(peri, base);

	printf("------------------------ BLK_PERI start ------------------------\n");
	clk1 = get_pll_freq_f0434(&blk_cmu_peri->pll_con0_pll_peri, &blk_cmu_peri->pll_con3_pll_peri);
	printf("PLL_PERI:		%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_peri->clk_con_div_div2_peri_pclk, clk1);
	printf("\tDIV2_PERI_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_PERI_PCLK		%luMHz\n", clk2);

	printf("------------------------ BLK_PERI end ------------------------\n\n");
}

void freq_cmu_wbus(void)
{
	uint64_t clk_pll_wbus_d_1600;
	uint64_t clk_pll_wbus_u_1600;
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(wbus_u, CMU_WBUS_U);
	CMU_BLK(wbus_d, CMU_WBUS_D);

	clk_pll_wbus_u_1600 = get_pll_freq_f0434(&blk_cmu_wbus_u->pll_con0_pll_wbus,
											 &blk_cmu_wbus_u->pll_con3_pll_wbus);
	clk_pll_wbus_d_1600 = clk_pll_wbus_u_1600;

	printf("------------------------ BLK_WBUS_U start ------------------------\n");
	printf("PLL_WBUS:		%luMHz\n", clk_pll_wbus_u_1600);

	clk2 = get_div_freq(&blk_cmu_wbus_u->clk_con_div_div1_wbus_u_aclk, clk_pll_wbus_u_1600);
	printf("\tDIV1_WBUS_U_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_WBUS_U_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_wbus_u->clk_con_div_div3_wbus_u_pclk, clk_pll_wbus_u_1600);
	printf("\tDIV3_WBUS_U_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_WBUS_U_PCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_WBUS_U end ------------------------\n\n");

	printf("------------------------ BLK_WBUS_D start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_wbus_d->pll_con0_pll_wbus_d, OSC_MHz, clk_pll_wbus_d_1600);
	printf("PLL_CTRL_WBUS_D			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_wbus_d->clk_con_div_div1_wbus_d_aclk, clk1);
	printf("\tDIV1_WBUS_D_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_WBUS_D_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_wbus_d->clk_con_div_div3_wbus_d_pclk, clk1);
	printf("\tDIV3_WBUS_D_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_WBUS_D_PCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_WBUS_D end ------------------------\n\n");
}

void freq_cmu_sbus(void)
{
	uint64_t clk_pll_sbus_d_1600;
	uint64_t clk_pll_sbus_u_1600;
	uint64_t clk_pll_sbus_l_1600;
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(sbus_u, CMU_SBUS_U);
	CMU_BLK(sbus_d, CMU_SBUS_D);
	CMU_BLK(sbus_l, CMU_SBUS_L);

	clk_pll_sbus_u_1600 = get_pll_freq_f0434(&blk_cmu_sbus_u->pll_con0_pll_sbus,
											 &blk_cmu_sbus_u->pll_con3_pll_sbus);
	clk_pll_sbus_d_1600 = clk_pll_sbus_u_1600;
	clk_pll_sbus_l_1600 = clk_pll_sbus_u_1600;

	printf("------------------------ BLK_SBUS_U start ------------------------\n");
	printf("PLL_SBUS:		%luMHz\n", clk_pll_sbus_u_1600);

	clk2 = get_div_freq(&blk_cmu_sbus_u->clk_con_div_div1_sbus_u_aclk, clk_pll_sbus_u_1600);
	printf("\tDIV1_SBUS_U_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_U_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_sbus_u->clk_con_div_div3_sbus_u_pclk, clk_pll_sbus_u_1600);
	printf("\tDIV3_SBUS_U_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_U_PCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_sbus_u->clk_con_div_div4_rbc_v10, clk_pll_sbus_u_1600);
	printf("\tDIV4_RBC_V10			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_V10			%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_sbus_u->clk_con_div_div4_rbc_v11, clk_pll_sbus_u_1600);
	printf("\tDIV4_RBC_V11			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_V11			%luMHz\n", clk2);
	printf("------------------------ BLK_SBUS_U end ------------------------\n\n");

	printf("------------------------ BLK_SBUS_D start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_sbus_d->pll_con0_pll_sbus_d, OSC_MHz, clk_pll_sbus_d_1600);
	printf("PLL_CTRL_SBUS_D			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_sbus_d->clk_con_div_div1_sbus_d_aclk, clk1);
	printf("\tDIV1_SBUS_D_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_D_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_sbus_d->clk_con_div_div3_sbus_d_pclk, clk1);
	printf("\tDIV3_SBUS_D_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_D_PCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_SBUS_D end ------------------------\n\n");

	printf("------------------------ BLK_SBUS_L start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_sbus_l->pll_con0_pll_sbus_l, OSC_MHz, clk_pll_sbus_l_1600);
	printf("PLL_CTRL_SBUS_L			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_sbus_l->clk_con_div_div1_sbus_l_aclk, clk1);
	printf("\tDIV1_SBUS_L_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_L_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_sbus_l->clk_con_div_div3_sbus_l_pclk, clk1);
	printf("\tDIV3_SBUS_L_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_SBUS_L_PCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_SBUS_L end ------------------------\n\n");
}

void freq_cmu_nbus(void)
{
	uint64_t clk_pll_nbus_d_1600;
	uint64_t clk_pll_nbus_u_1600;
	uint64_t clk_pll_nbus_l_1600;
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(nbus_u, CMU_NBUS_U);
	CMU_BLK(nbus_d, CMU_NBUS_D);
	CMU_BLK(nbus_l, CMU_NBUS_L);

	clk_pll_nbus_d_1600 = get_pll_freq_f0434(&blk_cmu_nbus_d->pll_con0_pll_nbus,
											 &blk_cmu_nbus_d->pll_con3_pll_nbus);
	clk_pll_nbus_u_1600 = clk_pll_nbus_d_1600;
	clk_pll_nbus_l_1600 = clk_pll_nbus_d_1600;

	printf("------------------------ BLK_NBUS_D start ------------------------\n");
	printf("PLL_NBUS:		%luMHz\n", clk_pll_nbus_d_1600);

	clk2 = get_div_freq(&blk_cmu_nbus_d->clk_con_div_div1_nbus_d_aclk, clk_pll_nbus_d_1600);
	printf("\tDIV1_NBUS_D_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_D_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_d->clk_con_div_div3_nbus_d_pclk, clk_pll_nbus_d_1600);
	printf("\tDIV3_NBUS_D_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_D_PCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_d->clk_con_div_div4_rbc_v0, clk_pll_nbus_d_1600);
	printf("\tDIV4_RBC_V0			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_V0			%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_d->clk_con_div_div4_rbc_v1, clk_pll_nbus_d_1600);
	printf("\tDIV4_RBC_V1			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_V1			%luMHz\n", clk2);
	printf("------------------------ BLK_NBUS_D end ------------------------\n\n");

	printf("------------------------ BLK_NBUS_L start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_nbus_l->pll_con0_pll_nbus_l, OSC_MHz, clk_pll_nbus_l_1600);
	printf("PLL_CTRL_NBUS_L			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_nbus_l->clk_con_div_div1_nbus_l_aclk, clk1);
	printf("\tDIV1_NBUS_L_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_L_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_l->clk_con_div_div3_nbus_l_pclk, clk1);
	printf("\tDIV3_NBUS_L_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_L_PCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_l->clk_con_div_div2_nbus_l_gclk, clk1);
	printf("\tDIV2_NBUS_L_GCLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_L_GCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_NBUS_L end ------------------------\n\n");

	printf("------------------------ BLK_NBUS_U start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_nbus_u->pll_con0_pll_nbus_u, OSC_MHz, clk_pll_nbus_u_1600);
	printf("PLL_CTRL_NBUS_U			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_nbus_u->clk_con_div_div1_nbus_u_aclk, clk1);
	printf("\tDIV1_NBUS_U_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_U_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_nbus_u->clk_con_div_div3_nbus_u_pclk, clk1);
	printf("\tDIV3_NBUS_U_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_U_PCLK		%luMHz\n", clk2);

	clk1 = get_mux_freq(&blk_cmu_nbus_u->clk_con_mux_mux_nbus_u_tclk, clk2, OSC_MHz);
	printf("MUX_NBUS_U_TCLK			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_nbus_u->clk_con_div_div1_nbus_u_tclk, clk1);
	printf("\tDIV1_NBUS_U_TCLK		%luMHz\n", clk2);
	printf("\t\tCLK_NBUS_U_TCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_NBUS_U end ------------------------\n\n");
}

void freq_cmu_ebus(void)
{
	uint64_t clk_pll_ebus_d_1600;
	uint64_t clk_pll_ebus_d_1200;
	uint64_t clk_pll_ebus_r_1600;
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(ebus_u, CMU_EBUS_U);
	CMU_BLK(ebus_d, CMU_EBUS_D);
	CMU_BLK(ebus_r, CMU_EBUS_R);

	clk_pll_ebus_d_1600 = get_pll_freq_f0434(&blk_cmu_ebus_u->pll_con0_pll_ebus,
											 &blk_cmu_ebus_u->pll_con3_pll_ebus);
	clk_pll_ebus_r_1600 = clk_pll_ebus_d_1600;
	clk_pll_ebus_d_1200 = get_pll_freq_f0434(&blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200,
											 &blk_cmu_ebus_d->pll_con3_pll_ebus_d_1200);

	printf("------------------------ BLK_EBUS_U start ------------------------\n");
	printf("PLL_EBUS:		%luMHz\n", clk_pll_ebus_d_1600);

	clk2 = get_div_freq(&blk_cmu_ebus_u->clk_con_div_div1_ebus_u_aclk, clk_pll_ebus_d_1600);
	printf("\tDIV1_EBUS_U_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_U_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_ebus_u->clk_con_div_div3_ebus_u_pclk, clk_pll_ebus_d_1600);
	printf("\tDIV3_EBUS_U_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_U_PCLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_ebus_u->clk_con_div_div_rbc_h0, clk_pll_ebus_d_1600);
	printf("\tDIV_RBC_H0			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_H0			%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_ebus_u->clk_con_div_div_rbc_h1, clk_pll_ebus_d_1600);
	printf("\tDIV_RBC_H1			%luMHz\n", clk2);
	printf("\t\tCLK_RBC_H1			%luMHz\n", clk2);

	clk1 = get_user_mux_freq(&blk_cmu_ebus_u->pll_con0_pll_ctrl_ebus_u, OSC_MHz,
							 clk_pll_ebus_d_1200);
	printf("PLL_CTRL_EBUS_U			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_ebus_u->clk_con_div_div1_ebus_u_sh_low_clk, clk1);
	printf("\tDIV1_EBUS_U_SH_LOW_CLK	%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_U_SH_LOW_CLK	%luMHz\n", clk2);
	printf("------------------------ BLK_EBUS_U end ------------------------\n\n");

	printf("------------------------ BLK_EBUS_D start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_ebus_d->pll_con0_pll_ebus_d_1600, OSC_MHz,
							 clk_pll_ebus_d_1600);
	printf("PLL_CTRL_EBUS_D			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_ebus_d->clk_con_div_div1_ebus_d_aclk, clk1);
	printf("\tDIV1_EBUS_D_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_D_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_ebus_d->clk_con_div_div3_ebus_d_pclk, clk1);
	printf("\tDIV3_EBUS_D_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_D_PCLK		%luMHz\n", clk2);

	printf("PLL_EBUS_D:		%luMHz\n", clk_pll_ebus_d_1200);

	clk2 = get_div_freq(&blk_cmu_ebus_d->clk_con_div_div_ebus_d_sh_low_clk, clk_pll_ebus_d_1200);
	printf("\tDIV_EBUS_D_SH_LOW_CLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_D_SH_LOW_CLK	%luMHz\n", clk2);
	printf("------------------------ BLK_EBUS_D end ------------------------\n\n");

	printf("------------------------ BLK_EBUS_R start ------------------------\n");
	clk1 = get_user_mux_freq(&blk_cmu_ebus_r->pll_con0_pll_ebus_r, OSC_MHz, clk_pll_ebus_r_1600);
	printf("PLL_CTRL_EBUS_R			%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_ebus_r->clk_con_div_div1_ebus_r_aclk, clk1);
	printf("\tDIV1_EBUS_R_ACLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_R_ACLK		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_ebus_r->clk_con_div_div3_ebus_r_pclk, clk1);
	printf("\tDIV3_EBUS_R_PCLK		%luMHz\n", clk2);
	printf("\t\tCLK_EBUS_R_PCLK		%luMHz\n", clk2);
	printf("------------------------ BLK_EBUS_R end ------------------------\n\n");
}

void freq_cmu_dram(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(dram, base);

	printf("------------------------ BLK_DRAM start ------------------------\n");
	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div5_dram_wrck_icon, OSC_MHz);
	printf("\tDIV5_DRAM_WRCK_ICON	%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_WRCK_ICON	%luMHz\n", clk2);

	clk1 = get_pll_freq_f0435(&blk_cmu_dram->pll_con0_pll_hbm3_phy0,
							  &blk_cmu_dram->pll_con3_pll_hbm3_phy0);
	printf("PLL_HBM3_PHY0:		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY0_OUT_0		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY0_GFMUX_OUT_0	%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div2_dram_aclk0, clk1);
	printf("\tDIV2_DRAM_ACLK0		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_ACLK0		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div8_dram_pclk0, clk1);
	printf("\tDIV8_DRAM_PCLK0		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_PCLK0		%luMHz\n", clk2);

	clk1 = get_pll_freq_f0435(&blk_cmu_dram->pll_con0_pll_hbm3_phy1,
							  &blk_cmu_dram->pll_con3_pll_hbm3_phy1);
	printf("PLL_HBM3_PHY1:		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY1_OUT_0		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY1_GFMUX_OUT_0	%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div2_dram_aclk1, clk1);
	printf("\tDIV2_DRAM_ACLK1		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_ACLK1		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div8_dram_pclk1, clk1);
	printf("\tDIV8_DRAM_PCLK1		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_PCLK1		%luMHz\n", clk2);

	clk1 = get_pll_freq_f0435(&blk_cmu_dram->pll_con0_pll_hbm3_phy2,
							  &blk_cmu_dram->pll_con3_pll_hbm3_phy2);
	printf("PLL_HBM3_PHY2:		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY2_OUT_0		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY2_GFMUX_OUT_0	%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div2_dram_aclk2, clk1);
	printf("\tDIV2_DRAM_ACLK2		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_ACLK2		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div8_dram_pclk2, clk1);
	printf("\tDIV8_DRAM_PCLK2		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_PCLK2		%luMHz\n", clk2);

	clk1 = get_pll_freq_f0435(&blk_cmu_dram->pll_con0_pll_hbm3_phy3,
							  &blk_cmu_dram->pll_con3_pll_hbm3_phy3);
	printf("PLL_HBM3_PHY3:		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY3_OUT_0		%luMHz\n", clk1);
	printf("\tPLL_HBM3_PHY3_GFMUX_OUT_0	%luMHz\n", clk1);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div2_dram_aclk3, clk1);
	printf("\tDIV2_DRAM_ACLK3		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_ACLK3		%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_dram->clk_con_div_div8_dram_pclk3, clk1);
	printf("\tDIV8_DRAM_PCLK3		%luMHz\n", clk2);
	printf("\t\tCLK_DRAM_PCLK3		%luMHz\n", clk2);

	printf("------------------------ BLK_DRAM end ------------------------\n\n");
}

void freq_cmu_dcl(uintptr_t base)
{
	uint64_t clk1;
	uint64_t clk2;

	CMU_BLK(dcl, base);

	printf("------------------------ BLK_DCL start ------------------------\n");
	clk2 = get_div_freq(&blk_cmu_dcl->clk_con_div_div5_dcl_oscclk, OSC_MHz);
	printf("\tDIV5_DCL_OSCCLK		%luMHz\n", clk2);

	clk1 = get_pll_freq_f0434(&blk_cmu_dcl->pll_con0_pll_dcl, &blk_cmu_dcl->pll_con3_pll_dcl);
	printf("PLL_DCL:				%luMHz\n", clk1);
	clk2 = get_pll_freq_f0434(&blk_cmu_dcl->pll_con0_pll_dcl_dvfs,
							  &blk_cmu_dcl->pll_con3_pll_dcl_dvfs);
	printf("PLL_DCL_DVFS:			%luMHz\n", clk1);

	clk1 = get_mux_freq(&blk_cmu_dcl->clk_con_mux_mux_dcl_pll_fout, clk1, clk2);
	printf("\tMUX_DCL_PLL_FOUT		%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div2_dcl_cmuref,
							&blk_cmu_dcl->clk_con_div_div4_hch_dcl_cmuref, clk1);
	printf("\t\tDIV2_DCL_CMUREF		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_CMUREF		%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk0,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk0, clk1);
	printf("\t\tDIV_DCL_ACLK0			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK0			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk1,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk1, clk1);
	printf("\t\tDIV_DCL_ACLK1			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK1			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk2,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk2, clk1);
	printf("\t\tDIV_DCL_ACLK2			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK2			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk3,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk3, clk1);
	printf("\t\tDIV_DCL_ACLK3			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK3			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk4,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk4, clk1);
	printf("\t\tDIV_DCL_ACLK4			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK4			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk5,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk5, clk1);
	printf("\t\tDIV_DCL_ACLK5			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK5			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue0,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue0, clk1);
	printf("\t\tDIV_DCL_ACLK_DGLUE0		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK_DGLUE0	%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue1,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue1, clk1);
	printf("\t\tDIV_DCL_ACLK_DGLUE1		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK_DGLUE1	%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue2,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue2, clk1);
	printf("\t\tDIV_DCL_ACLK_DGLUE2		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK_DGLUE2	%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk_dglue3,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_dglue3, clk1);
	printf("\t\tDIV_DCL_ACLK_DGLUE3		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK_DGLUE3	%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div_dcl_aclk_sglue,
							&blk_cmu_dcl->clk_con_div_div2_hch_dcl_aclk_sglue, clk1);
	printf("\t\tDIV_DCL_ACLK_SGLUE		%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ACLK_SGLUE	%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div4_dcl_pclk,
							&blk_cmu_dcl->clk_con_div_div8_hch_dcl_pclk, clk1);
	printf("\t\tDIV_4_DCL_PCLK			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_PCLK			%luMHz\n", clk2);

	clk2 = get_hch_div_freq(&blk_cmu_dcl->clk_con_div_div2_dcl_add,
							&blk_cmu_dcl->clk_con_div_div4_hch_dcl_add, clk1);
	printf("\t\tDIV2_DCL_ADD			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_ADD			%luMHz\n", clk2);

	clk2 = get_div_freq(&blk_cmu_dcl->clk_con_div_div9_dcl_pvt, clk1);
	printf("\t\tDIV9_DCL_PVT			%luMHz\n", clk2);
	printf("\t\t\tCLK_DCL_PVT			%luMHz\n", clk2);

	printf("------------------------ BLK_DCL end ------------------------\n\n");
}

uint8_t test_main_cmu(int argc, char *argv[])
{
	printf("\nStart cmu test\n");

	if (argc) {
		if (strcmp(argv[0], "cp0") == 0) {
			test_cmu_cp(CMU_CP0_PRIVATE);
		} else if (strcmp(argv[0], "cp1") == 0) {
			test_cmu_cp(CMU_CP1_PRIVATE);
		} else if (strcmp(argv[0], "pcie") == 0) {
			if (!CHIPLET_ID) {
				test_cmu_pcie(CMU_PCIE_PRIVATE);
			}
		} else if (strcmp(argv[0], "rot") == 0) {
			test_cmu_rot(CMU_ROT_PRIVATE);
		} else if (strcmp(argv[0], "peri0") == 0) {
			test_cmu_peri(CMU_PERI0);
		} else if (strcmp(argv[0], "peri1") == 0) {
			test_cmu_peri(CMU_PERI1);
		} else if (strcmp(argv[0], "dram") == 0) {
			test_cmu_dram(CMU_DRAM);
		}
	} else {
		test_cmu_cp(CMU_CP0_PRIVATE);
		test_cmu_cp(CMU_CP1_PRIVATE);
		if (!CHIPLET_ID) {
			test_cmu_pcie(CMU_PCIE_PRIVATE);
		}
		test_cmu_rot(CMU_ROT_PRIVATE);
		test_cmu_peri(CMU_PERI0);
		test_cmu_peri(CMU_PERI1);
		test_cmu_dram(CMU_DRAM);
	}

	return true;
}

uint8_t cmu_freq_main(int argc, char *argv[])
{
	printf("\nFrequences for blk_cmus\n");

	if (argc) {
		if (strcmp(argv[0], "cp0") == 0) {
			freq_cmu_cp(CMU_CP0_PRIVATE);
		} else if (strcmp(argv[0], "cp1") == 0) {
			freq_cmu_cp(CMU_CP1_PRIVATE);
		} else if (strcmp(argv[0], "pcie") == 0) {
			freq_cmu_pcie(CMU_PCIE_PRIVATE);
		} else if (strcmp(argv[0], "rot") == 0) {
			freq_cmu_rot(CMU_ROT_PRIVATE);
		} else if (strcmp(argv[0], "peri0") == 0) {
			if (!CHIPLET_ID) {
				freq_cmu_peri(CMU_PERI0);
			}
		} else if (strcmp(argv[0], "peri1") == 0) {
			freq_cmu_peri(CMU_PERI1);
		} else if (strcmp(argv[0], "dram") == 0) {
			freq_cmu_dram(CMU_DRAM);
		} else if (strcmp(argv[0], "ebus") == 0) {
			freq_cmu_ebus();
		} else if (strcmp(argv[0], "nbus") == 0) {
			freq_cmu_nbus();
		} else if (strcmp(argv[0], "sbus") == 0) {
			freq_cmu_sbus();
		} else if (strcmp(argv[0], "wbus") == 0) {
			freq_cmu_wbus();
		} else if (strcmp(argv[0], "dcl0") == 0) {
			freq_cmu_dcl(CMU_DCL0);
		} else if (strcmp(argv[0], "dcl1") == 0) {
			freq_cmu_dcl(CMU_DCL1);
		}
	} else {
		freq_cmu_cp(CMU_CP0_PRIVATE);
		freq_cmu_cp(CMU_CP1_PRIVATE);
		if (!CHIPLET_ID) {
			freq_cmu_pcie(CMU_PCIE_PRIVATE);
		}
		freq_cmu_rot(CMU_ROT_PRIVATE);
		freq_cmu_peri(CMU_PERI0);
		freq_cmu_peri(CMU_PERI1);
		freq_cmu_dram(CMU_DRAM);
		freq_cmu_ebus();
		freq_cmu_nbus();
		freq_cmu_sbus();
		freq_cmu_wbus();
		freq_cmu_dcl(CMU_DCL0);
		freq_cmu_dcl(CMU_DCL1);
	}

	return true;
}

uint8_t cmu_set_freq(int argc, char *argv[])
{
	if (argc == 2) {
		if (strcmp(argv[0], "cp0") == 0) {
			set_freq_cp(CMU_CP0_PRIVATE, argv[0], atoi(argv[1]));
		} else if (strcmp(argv[0], "cp1") == 0) {
			set_freq_cp(CMU_CP1_PRIVATE, argv[0], atoi(argv[1]));
		} else {
			printf("Invalid target: %s\n", argv[0]);
		}
	} else {
		printf("Invalid request. Please check a help description\n");

		return false;
	}

	return true;
}

static const char help_cmu[] =
	"[test_cmu [block]] - test minimal items for block each\r\n"
	" - [test_cmu cp0]\r\n"
	" - [test_cmu cp1]\r\n"
	" - [test_cmu rot]\r\n"
	" - [test_cmu pcie] - Primary chiplet only\r\n"
	" - [test_cmu peri0]\r\n"
	" - [test_cmu peri1]\r\n"
	" - [test_cmu dram]\r\n"
	"[cmu_freq [block]] - check pll/mux/div status\r\n"
	" - [cmu_freq cp0]\r\n"
	" - [cmu_freq cp1]\r\n"
	" - [cmu_freq rot]\r\n"
	" - [cmu_freq pcie] - Primary chiplet only\r\n"
	" - [cmu_freq peri0]\r\n"
	" - [cmu_freq peri1]\r\n"
	" - [cmu_freq dram]\r\n"
	" - [cmu_freq ebus]\r\n"
	" - [cmu_freq nbus]\r\n"
	" - [cmu_freq sbus]\r\n"
	" - [cmu_freq wbus]\r\n"
	" - [cmu_freq dcl0]\r\n"
	" - [cmu_freq dcl1]\r\n"
	"\r\n";

static const char help_cmu_set[] =
	"[cmu_set [target] [freq. in MHz]] - set cp0/1 freq.\r\n"
	" - target: cp0, cp1\r\n"
	" - freq: 400 ~ 2500\r\n"
	"\r\n";

CLI_REGISTER(test_cmu, NULL, test_main_cmu, help_cmu);
CLI_REGISTER(cmu_freq, NULL, cmu_freq_main, help_cmu);
CLI_REGISTER(cmu_set,  NULL, cmu_set_freq,  help_cmu_set);
