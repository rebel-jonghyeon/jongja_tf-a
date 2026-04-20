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

#include <sac_reg.h>
#include <fboot.h>
#include <rebel_h.h>

#include "cmu.h"

#define CMU_PCIE							(0x1FF8100000ULL)
#define CMU_ROT								(0x1FF0200000ULL)
#define CMU_NBUS_U							(0x1FF3000000ULL)
#define CMU_NBUS_D							(0x1FF3300000ULL)
#define CMU_NBUS_L							(0x1FF3500000ULL)
#define CMU_SBUS_U							(0x1FF3A00000ULL)
#define CMU_SBUS_D							(0X1FF3C00000ULL)
#define CMU_SBUS_L							(0x1FF3E00000ULL)
#define CMU_WBUS_U							(0x1FF4000000ULL)
#define CMU_WBUS_D							(0x1FF4600000ULL)
#define CMU_EBUS_U							(0x1FF4800000ULL)
#define CMU_EBUS_D							(0x1FF4A00000ULL)
#define CMU_EBUS_R							(0x1FF4C00000ULL)
#define CMU_PERI0							(0X1FF9000000ULL)

#define CMRT_SAC_DATA						(CMRT_SAC_BASE + R_CPU_DATA)

#define PLL_LOCKCYCLE						(500)
#define PLL_ENABLE							(1)

#define MHz	(1000000)

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
	volatile struct cmu_##block *const blk_cmu_##block = (struct cmu_##block *)(base_addr)

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

enum F0434_FREQ {
	_2_0GHZ,
	_1_6GHZ,
	_1_5GHZ,
	_1_2GHZ,
	_1_0GHZ,
};

struct pll_table {
	uint32_t target_freq;
	uint32_t p;
	uint32_t m;
	uint32_t s;
	uint32_t k;
};

static struct pll_table const pll_table_f0434[] = {
	{2000, 2, 100, 0, 0},
	{1600, 1, 80, 1, 0},
	{1500, 1, 75, 1, 0},
	{1200, 2, 120, 1, 0},
	{1000, 2, 50, 0, 0},
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

struct div_sfr {
	uint32_t divratio : 16;					 /* [15:0] */
	uint32_t busy : 1;						 /* [16:16] */
	uint32_t reserved1 : 11;				 /* [27:17] */
	uint32_t enable_automatic_clkgating : 1; /* [28:28] */
	uint32_t reserved2 : 1;					 /* [29:29] */
	uint32_t override_by_hch : 1;			 /* [30:30] */
	uint32_t reserved3 : 1;					 /* [31:31] */
};

static uint32_t clk_pow(int32_t base, uint32_t exp)
{
	int ret = 1;

	while (exp--) {
		ret *= base;
	}

	return ret;
}

uint64_t get_pll_freq_f0434(volatile void *con0, volatile void *con3)
{
	volatile struct pll_con0 *con0_addr = con0;
	volatile struct pll_con3 *con3_addr = con3;

	if (con0_addr->mux_sel == 0) {
		return (CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC / MHz);
	}

	return ((con0_addr->div_m + con3_addr->div_k / 65536) *
			(CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC / MHz)) /
			(con0_addr->div_p * clk_pow(2, con0_addr->div_s));
}

uint32_t get_div_ratio(volatile void *div)
{
	return ((volatile struct div_sfr *)div)->divratio + 1;
}

static inline void cmu_blk_ebus_d_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(ebus_d, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_ebus_d->pll_locktime_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	SET_CON3_VAL(blk_cmu_ebus_d->pll_con3_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	SET_CON0_VAL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, pll_table_f0434[_1_2GHZ]);
	IS_PLL_LOCKED(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(ebus_d, base));
	CMU_BLK(ebus_d_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_ebus_d_div->clk_con_div_div1_ebus_d_aclk, 1);
	SET_DIV(blk_cmu_ebus_d_div->clk_con_div_div3_ebus_d_pclk, 3);
	SET_DIV(blk_cmu_ebus_d_div->clk_con_div_div_ebus_d_sh_low_clk, 1);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1600, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_d->pll_con0_pll_ebus_d_1200, 1);
}

static inline void cmu_blk_ebus_r_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(ebus_r, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(ebus_r, base));
	CMU_BLK(ebus_r_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_ebus_r_div->clk_con_div_div1_ebus_r_aclk, 1);
	SET_DIV(blk_cmu_ebus_r_div->clk_con_div_div3_ebus_r_pclk, 3);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_ebus_r->pll_con0_pll_ebus_r, 1);
}

static inline void cmu_blk_ebus_u_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(ebus_u, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_ebus_u->pll_locktime_pll_ebus, pll_table_f0434[_1_6GHZ]);
	SET_CON3_VAL(blk_cmu_ebus_u->pll_con3_pll_ebus, pll_table_f0434[_1_6GHZ]);
	SET_CON0_VAL(blk_cmu_ebus_u->pll_con0_pll_ebus, pll_table_f0434[_1_6GHZ]);
	IS_PLL_LOCKED(blk_cmu_ebus_u->pll_con0_pll_ebus);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(ebus_u, base));
	CMU_BLK(ebus_u_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_ebus_u_div->clk_con_div_div1_ebus_u_aclk, 1);
	SET_DIV(blk_cmu_ebus_u_div->clk_con_div_div3_ebus_u_pclk, 3);
	SET_DIV(blk_cmu_ebus_u_div->clk_con_div_div_rbc_h0, 8);
	SET_DIV(blk_cmu_ebus_u_div->clk_con_div_div_rbc_h1, 8);
	SET_DIV(blk_cmu_ebus_u_div->clk_con_div_div1_ebus_u_sh_low_clk, 1);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_ebus_u->pll_con0_pll_ctrl_ebus_u, 1);
	SET_CON0_MUX_SEL(blk_cmu_ebus_u->pll_con0_pll_ebus, 1);
}

static inline void cmu_blk_nbus_d_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(nbus_d, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_nbus_d->pll_locktime_pll_nbus, pll_table_f0434[_1_6GHZ]);
	SET_CON3_VAL(blk_cmu_nbus_d->pll_con3_pll_nbus, pll_table_f0434[_1_6GHZ]);
	SET_CON0_VAL(blk_cmu_nbus_d->pll_con0_pll_nbus, pll_table_f0434[_1_6GHZ]);
	IS_PLL_LOCKED(blk_cmu_nbus_d->pll_con0_pll_nbus);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(nbus_d, base));
	CMU_BLK(nbus_d_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_nbus_d_div->clk_con_div_div1_nbus_d_aclk, 1);
	SET_DIV(blk_cmu_nbus_d_div->clk_con_div_div3_nbus_d_pclk, 3);
	SET_DIV(blk_cmu_nbus_d_div->clk_con_div_div4_rbc_v0, 8);
	SET_DIV(blk_cmu_nbus_d_div->clk_con_div_div4_rbc_v1, 8);

	cmrt_sac_set_base(NULL, base);
	SET_CON0_MUX_SEL(blk_cmu_nbus_d->pll_con0_pll_nbus, 1);
}

static inline void cmu_blk_nbus_l_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(nbus_l, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(nbus_l, base));
	CMU_BLK(nbus_l_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_nbus_l_div->clk_con_div_div1_nbus_l_aclk, 1);
	SET_DIV(blk_cmu_nbus_l_div->clk_con_div_div3_nbus_l_pclk, 3);
	SET_DIV(blk_cmu_nbus_l_div->clk_con_div_div2_nbus_l_gclk, 2);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_nbus_l->pll_con0_pll_nbus_l, 1);
}

static inline void cmu_blk_nbus_u_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(nbus_u, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(nbus_u, base));
	CMU_BLK(nbus_u_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_nbus_u_div->clk_con_div_div1_nbus_u_aclk, 1);
	SET_DIV(blk_cmu_nbus_u_div->clk_con_div_div3_nbus_u_pclk, 3);
	SET_DIV(blk_cmu_nbus_u_div->clk_con_div_div1_nbus_u_tclk, 1);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_nbus_u->pll_con0_pll_nbus_u, 1);
}

static inline void cmu_blk_pcie_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(pcie, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_pcie->pll_locktime_pll_pcie, pll_table_f0434[_2_0GHZ]);
	SET_CON3_VAL(blk_cmu_pcie->pll_con3_pll_pcie, pll_table_f0434[_2_0GHZ]);
	SET_CON0_VAL(blk_cmu_pcie->pll_con0_pll_pcie, pll_table_f0434[_2_0GHZ]);
	IS_PLL_LOCKED(blk_cmu_pcie->pll_con0_pll_pcie);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(pcie, base));
	CMU_BLK(pcie_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_pcie_div->clk_con_div_div20_pcie_refclk_p, 20);
	SET_DIV(blk_cmu_pcie_div->clk_con_div_div2_pcie_aclk, 2);
	SET_DIV(blk_cmu_pcie_div->clk_con_div_div4_pcie_pclk, 4);
	SET_DIV(blk_cmu_pcie_div->clk_con_div_div1_pcie_tsclk, 1);
	SET_DIV(blk_cmu_pcie_div->clk_con_div_div16_pcie_crparaclk, 16);
	SET_DIV(blk_cmu_pcie_div->clk_con_div_div_pcie_auxclk, 10);

	cmrt_sac_set_base(NULL, CMU_MUX_BASE(pcie, base));
	CMU_BLK(pcie_mux, CMRT_SAC_DATA);

	SET_MUX(blk_cmu_pcie_mux->clk_con_mux_mux_pcie_tsclk, 0);
	SET_MUX(blk_cmu_pcie_mux->clk_con_mux_mux_pcie_auxclk, 1);

	cmrt_sac_set_base(NULL, base);

	SET_CON0_MUX_SEL(blk_cmu_pcie->pll_con0_pll_pcie, 1);
}

static inline void cmu_blk_peri_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(peri, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_peri->pll_locktime_pll_peri, pll_table_f0434[_1_0GHZ]);
	SET_CON3_VAL(blk_cmu_peri->pll_con3_pll_peri, pll_table_f0434[_1_0GHZ]);
	SET_CON0_VAL(blk_cmu_peri->pll_con0_pll_peri, pll_table_f0434[_1_0GHZ]);
	IS_PLL_LOCKED(blk_cmu_peri->pll_con0_pll_peri);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(peri, base));
	CMU_BLK(peri_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_peri_div->clk_con_div_div2_peri_pclk, 4);

	cmrt_sac_set_base(NULL, base);
	SET_CON0_MUX_SEL(blk_cmu_peri->pll_con0_pll_peri, 1);
}

static inline void cmu_blk_rot_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(rot, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_rot->pll_locktime_pll_rot, pll_table_f0434[_1_5GHZ]);
	SET_CON3_VAL(blk_cmu_rot->pll_con3_pll_rot, pll_table_f0434[_1_5GHZ]);
	SET_CON0_VAL(blk_cmu_rot->pll_con0_pll_rot, pll_table_f0434[_1_5GHZ]);
	IS_PLL_LOCKED(blk_cmu_rot->pll_con0_pll_rot);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(rot, base));
	CMU_BLK(rot_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_rot_div->clk_con_div_div4_rot_otp, 4);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div2_rot_aclk, 2);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div7_rot_pvt, 7);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div3_rot_pclk, 3);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div1_rot_tsclk, 1);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div3_rot_cntclk, 3);
	SET_DIV(blk_cmu_rot_div->clk_con_div_div3_rot_rtck, 3);

	cmrt_sac_set_base(NULL, base);
	SET_CON0_MUX_SEL(blk_cmu_rot->pll_con0_pll_rot, 1);
}

static inline void cmu_blk_sbus_d_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(sbus_d, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(sbus_d, base));
	CMU_BLK(sbus_d_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_sbus_d_div->clk_con_div_div1_sbus_d_aclk, 1);
	SET_DIV(blk_cmu_sbus_d_div->clk_con_div_div3_sbus_d_pclk, 3);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_sbus_d->pll_con0_pll_sbus_d, 1);
}

static inline void cmu_blk_sbus_l_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(sbus_l, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(sbus_l, base));
	CMU_BLK(sbus_l_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_sbus_l_div->clk_con_div_div1_sbus_l_aclk, 1);
	SET_DIV(blk_cmu_sbus_l_div->clk_con_div_div3_sbus_l_pclk, 3);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_sbus_l->pll_con0_pll_sbus_l, 1);
}

static inline void cmu_blk_sbus_u_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(sbus_u, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_sbus_u->pll_locktime_pll_sbus, pll_table_f0434[_1_6GHZ]);
	SET_CON3_VAL(blk_cmu_sbus_u->pll_con3_pll_sbus, pll_table_f0434[_1_6GHZ]);
	SET_CON0_VAL(blk_cmu_sbus_u->pll_con0_pll_sbus, pll_table_f0434[_1_6GHZ]);
	IS_PLL_LOCKED(blk_cmu_sbus_u->pll_con0_pll_sbus);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(sbus_u, base));
	CMU_BLK(sbus_u_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_sbus_u_div->clk_con_div_div1_sbus_u_aclk, 1);
	SET_DIV(blk_cmu_sbus_u_div->clk_con_div_div3_sbus_u_pclk, 3);
	SET_DIV(blk_cmu_sbus_u_div->clk_con_div_div4_rbc_v10, 8);
	SET_DIV(blk_cmu_sbus_u_div->clk_con_div_div4_rbc_v11, 8);

	cmrt_sac_set_base(NULL, base);
	SET_CON0_MUX_SEL(blk_cmu_sbus_u->pll_con0_pll_sbus, 1);
}

static inline void cmu_blk_wbus_d_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(wbus_d, CMRT_SAC_DATA);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(wbus_d, base));
	CMU_BLK(wbus_d_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_wbus_d_div->clk_con_div_div1_wbus_d_aclk, 1);
	SET_DIV(blk_cmu_wbus_d_div->clk_con_div_div3_wbus_d_pclk, 3);

	cmrt_sac_set_base(NULL, base);
	SET_USER_MUX(blk_cmu_wbus_d->pll_con0_pll_wbus_d, 1);
}

static inline void cmu_blk_wbus_u_init(uint64_t base)
{
	cmrt_sac_set_base(NULL, base);
	CMU_BLK(wbus_u, CMRT_SAC_DATA);

	SET_LOCKTIME(blk_cmu_wbus_u->pll_locktime_pll_wbus, pll_table_f0434[_1_6GHZ]);
	SET_CON3_VAL(blk_cmu_wbus_u->pll_con3_pll_wbus, pll_table_f0434[_1_6GHZ]);
	SET_CON0_VAL(blk_cmu_wbus_u->pll_con0_pll_wbus, pll_table_f0434[_1_6GHZ]);
	IS_PLL_LOCKED(blk_cmu_wbus_u->pll_con0_pll_wbus);

	cmrt_sac_set_base(NULL, CMU_DIV_BASE(wbus_u, base));
	CMU_BLK(wbus_u_div, CMRT_SAC_DATA);

	SET_DIV(blk_cmu_wbus_u_div->clk_con_div_div1_wbus_u_aclk, 1);
	SET_DIV(blk_cmu_wbus_u_div->clk_con_div_div3_wbus_u_pclk, 3);

	cmrt_sac_set_base(NULL, base);
	SET_CON0_MUX_SEL(blk_cmu_wbus_u->pll_con0_pll_wbus, 1);
}

void cmu_init(uint32_t chiplet_id)
{
	uint64_t chiplet_offset = chiplet_id * CHIPLET_BASE_OFFSET;

	cmu_blk_ebus_d_init(chiplet_offset + CMU_EBUS_D);
	cmu_blk_ebus_r_init(chiplet_offset + CMU_EBUS_R);
	cmu_blk_ebus_u_init(chiplet_offset + CMU_EBUS_U);
	cmu_blk_nbus_d_init(chiplet_offset + CMU_NBUS_D);
	cmu_blk_nbus_l_init(chiplet_offset + CMU_NBUS_L);
	cmu_blk_nbus_u_init(chiplet_offset + CMU_NBUS_U);
	if (chiplet_id == 0) {
		cmu_blk_pcie_init(chiplet_offset + CMU_PCIE);
	} else if (chiplet_id == 3 && (get_revision() == REVISION_EVT1)) {
		cmu_blk_pcie_init(chiplet_offset + CMU_PCIE);
	}
	cmu_blk_peri_init(chiplet_offset + CMU_PERI0);
	cmu_blk_rot_init(chiplet_offset + CMU_ROT);
	cmu_blk_sbus_d_init(chiplet_offset + CMU_SBUS_D);
	cmu_blk_sbus_l_init(chiplet_offset + CMU_SBUS_L);
	cmu_blk_sbus_u_init(chiplet_offset + CMU_SBUS_U);
	cmu_blk_wbus_d_init(chiplet_offset + CMU_WBUS_D);
	cmu_blk_wbus_u_init(chiplet_offset + CMU_WBUS_U);
}
