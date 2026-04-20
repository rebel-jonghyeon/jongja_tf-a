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

#pragma once
#include <stdint.h>

#include "cmu_cp.h"
#include "cmu_dram.h"
#include "cmu_dcl.h"
#include "cmu_ebus_d.h"
#include "cmu_ebus_r.h"
#include "cmu_ebus_u.h"
#include "cmu_nbus_d.h"
#include "cmu_nbus_l.h"
#include "cmu_nbus_u.h"
#include "cmu_pcie.h"
#include "cmu_peri.h"
#include "cmu_rbc.h"
#include "cmu_rot.h"
#include "cmu_sbus_d.h"
#include "cmu_sbus_l.h"
#include "cmu_sbus_u.h"
#include "cmu_wbus_d.h"
#include "cmu_wbus_u.h"

#define CLK_ENABLE              1
#define CLK_DISABLE             0

#define CMU_BLK(block, base_addr)			\
	volatile struct cmu_##block *const blk_cmu_##block = \
		(struct cmu_##block *)(uintptr_t)(base_addr)

enum F0434_FREQ {
	_2_5GHz,
	_2_4GHz,
	_2_3GHz,
	_2_2GHz,
	_2_1GHz,
	_2_GHz,
	_1_9GHz,
	_1_8GHz,
	_1_7GHz,
	_1_6GHz,
	_1_5GHz,
	_1_4GHz,
	_1_3GHz,
	_1_2GHz,
	_1_0GHz,
	_0_8GHz,
	_0_6GHz,
	_0_4GHz,
	NOT_SUPPORT_F0434,
};

enum F0435_FREQ {
	_9_6GHz,
	_9_2GHz,
	_8_0GHz,
	_6_4GHz, /* for test */
	NOT_SUPPORT_F0435,
};

enum CPMU_CLKOUT_BLK {
	CLKOUT_CMU_CP0 = 4,
	CLKOUT_CMU_CP1, /* 5 */

	CLKOUT_CMU_PCIE,
	CLKOUT_CMU_DRAM,
	CLKOUT_CMU_DCL0,
	CLKOUT_CMU_DCL1,
	CLKOUT_CMU_RBCH00, /* 10 */

	CLKOUT_CMU_RBCH01,
	CLKOUT_CMU_RBCV00,
	CLKOUT_CMU_RBCV01,
	CLKOUT_CMU_RBCV10,
	CLKOUT_CMU_RBCV11, /* 15 */

	CLKOUT_CMU_ROT,
	CLKOUT_CMU_PERI0,
	CLKOUT_CMU_PERI1,
	CLKOUT_CMU_SBUS_U,
	CLKOUT_CMU_SBUS_D, /* 20*/

	CLKOUT_CMU_SBUS_L,
	CLKOUT_CMU_NBUS_U,
	CLKOUT_CMU_NBUS_D,
	CLKOUT_CMU_NBUS_L,
	CLKOUT_CMU_WBUS_U, /* 25 */

	CLKOUT_CMU_WBUS_D,
	CLKOUT_CMU_EBUS_U,
	CLKOUT_CMU_EBUS_D,
	CLKOUT_CMU_EBUS_R,
};

/**
 * @fn		uint32_t set_clk_out(uint64_t cmu_base, uint32_t blk_id, uint32_t clk_id);
 * @brief   set clock monitoring for dedicated clock
 * @param   cmu_base: The SFR base address of blk_cmu
 * @param   blk_id: The enum value of the block you want to clock out.
 * @param   clk_id: The enum value of the clock you want to clock out, each item refers to
 *              the corresponding *_CLK_OUT enum value in the herder file.
 * @return  The value of the set clock out register
 */
uint32_t set_clk_out(uint64_t cmu_base, uint32_t blk_id, uint32_t clk_id);

/**
 * @fn	    uint64_t get_pll_freq_f0434(void *con0, void *con3)
 * @brief	Get the output clock of PLL F0434
 *			The formula to calculate the frequency of pll_0434 is as follows:
 *			((m + k / 65536) * 40) / (p * (2 ^ s))
 * @param   con0: The address of the pll_con0 register for the pll
 * @param   con3: The address of the pll_con3 register for the pll
 * @return  The output clock of the currently set PLL
 */
uint64_t get_pll_freq_f0434(volatile void *con0, volatile void *con3);

/**
 * @fn	    uint64_t get_pll_freq_f0435(void *con0, void *con3)
 * @brief	Get the output clock of PLL F0435
 *			The formula to calculate the frequency of pll_0434 is as follows:
 *			((m + k / 65536) * 2 * 40) / (p * (2 ^ s))
 * @param   con0: The address of the pll_con0 register for the pll
 * @param   con3: The address of the pll_con3 register for the pll
 * @return  The output clock of the currently set PLL
 */
uint64_t get_pll_freq_f0435(volatile void *con0, volatile void *con3);

/**
 * @fn	    void set_pll_freq_f0434(void *lock_time, void *con0, void *con3, uint32_t freq)
 * @brief	Set the output clock of PLL F0434
 * @param   lock_time: The address of the pll_locktime register for the pll
 * @param   con0: The address of the pll_con0 register for the pll
 * @param   con3: The address of the pll_con3 register for the pll
 * @param   freq: The desired pll output frequency to be set
 */
void set_pll_freq_f0434(volatile void *lock_time, volatile void *con0, volatile void *con3,
						uint32_t freq);

/**
 * @fn	    void set_pll_freq_f0435(void *lock_time, void *con0, void *con3, uint32_t freq)
 * @brief	Set the output clock of PLL F0435
 * @param   lock_time: The address of the pll_locktime register for the pll
 * @param   con0: The address of the pll_con0 register for the pll
 * @param   con3: The address of the pll_con3 register for the pll
 * @param   freq: The desired pll output frequency to be set
 */
void set_pll_freq_f0435(volatile void *lock_time, volatile void *con0, volatile void *con3,
						uint32_t freq);

/**
 * @fn		void set_div_ratio(void *div, uint32_t ratio)
 * @brief	changing the settings of a clock divider
 * @param   div: The SFR address of the clock divider
 * @param   ratio: The value to set for the clock's divider
 */
void set_div_ratio(volatile void *div, uint32_t ratio);

/**
 * @fn		void set_hch_div_ratio(void *div, void *hch_div, uint32_t ratio)
 * @brief	changing the settings of a clock divider
 * @param   div: The SFR address of the clock divider
 * @param   hch_div_addr: The SFR address of the clock divider for h-channel
 *              for dividers that do not support hch(h-channel), enter this address as NULL.
 * @param   ratio: The value to set for the clock's divider
 * @return  The set divider value
 * @note
 */
void set_hch_div_ratio(volatile void *div, volatile void *hch_div, uint32_t ratio);

/**
 * @fn		uint32_t get_hch_div_ratio(void *div, void *hch_div)
 * @brief	get the divider ratio of a clock divider or h-channel divider
 * @param   div: The SFR address of the clock divider
 * @param   hch_div_addr: The SFR address of the clock divider for h-channel
 *              for dividers that do not support hch(h-channel), enter this address as NULL.
 * @return  The current divider value
 */
uint32_t get_hch_div_ratio(volatile void *div, volatile void *hch_div);

/**
 * @fn		uint32_t get_div_ratio(void *div)
 * @brief	get the divider ratio of a clock divider
 * @param   div: The SFR address of the clock divider
 * @return  The current divider value
 */
uint32_t get_div_ratio(volatile void *div);

/**
 * @fn		static inline void set_user_mux_sel(void *user_mux, uint32_t sel)
 * @brief	changing the settings of a user_mux
 * @param   user_mux: The SFR address of the user_mux
 * @param   sel: The value to set for the parents of user_mux
 */
void set_user_mux_sel(volatile void *user_mux, uint32_t sel);

/**
 * @fn		static inline void set_mux_sel(void *mux, uint32_t sel)
 * @brief	changing the settings of a clock mux
 * @param   mux: The SFR address of the clock mux
 * @param   sel: The value to set for the parents of mux
 */
void set_mux_sel(volatile void *mux, uint32_t sel);

/**
 * @fn		uint32_t get_user_mux_sel(void *user_mux)
 * @brief	get the settings of a user_mux
 * @param   user_mux: The SFR address of the user_mux
 * @return  The current user_mux seletion
 */
uint32_t get_user_mux_sel(volatile void *user_mux);

/**
 * @fn		uint32_t get_mux_sel(void *mux)
 * @brief	get the settings of a clock mux
 * @param   mux: The SFR address of the clock mux
 * @return  The current mux seletion
 */
uint32_t get_mux_sel(volatile void *mux);

/**
 * @fn		uint32_t is_clk_gated(void *gate)
 * @brief	get clock status
 * @param   gate: The SFR address of the clock gate
 * @return	current clock status: CLK_ENABLE(1), CLK_DISABLE(0)
 */
uint32_t is_clk_gated(volatile void *gate);

/**
 * @fn		void clk_gating(void *gate, uint32_t val)
 * @brief	enable or disable clock
 * @param   gate: The SFR address of the clock gate
 * @param   val: CLK_ENABLE(1), CLK_DISABLE(0)
 */
void clk_gating(volatile void *gate, uint32_t val);

/**
 * @fn	    uint64_t get_user_mux_freq(void *user_mux, uint64_t in1, uint64_t in2)
 * @brief	Get the output clock frequency of user_mux
 * @param   user_mux: The SFR address of the user_mux
 * @param   in1: The input clock from first parent
 * @param   in2: The input clock from second parent
 * @return  The output clock of the currently set user_mux
 */
uint64_t get_user_mux_freq(volatile void *user_mux, uint64_t in1, uint64_t in2);

/**
 * @fn	    uint64_t get_mux_freq(void *mux, uint64_t in1, uint64_t in2)
 * @brief	Get the output clock frequency of mux
 * @param   mux: The SFR address of the clock mux
 * @param   in1: The input clock from first parent
 * @param   in2: The input clock from second parent
 * @return  The output clock of the currently set mux
 */
uint64_t get_mux_freq(volatile void *mux, uint64_t in1, uint64_t in2);

/**
 * @fn	    uint64_t get_div_freq(void *div, uint64_t in)
 * @brief	Get the output clock frequency of divider
 * @param   div: The SFR address of the clock divider
 * @param   in: The input clock from parent
 * @return  The output clock of the currently set divider
 */
uint64_t get_div_freq(volatile void *div, uint64_t in);

/**
 * @fn	    uint64_t get_hch_div_freq(void *div, void *hch_div, uint64_t in)
 * @brief	get the output clock frequency of a clock divider or h-channel divider
 * @param   div: The SFR address of the clock divider
 * @param   hch_div_addr: The SFR address of the clock divider for h-channel
 *              for dividers that do not support hch(h-channel), enter this address as NULL.
 * @return  The output clock of the currently set divider
 */
uint64_t get_hch_div_freq(volatile void *div, volatile void *hch_div, uint64_t in);

/**
 * @fn		void cmu_blk_xx_init(uintptr_t base)
 * @brief   set the block cmu to an initial value
 * @param   base: The base address of the blk_cmu
 */
void cmu_blk_cp_init(uintptr_t base);
void cmu_blk_pcie_init(uintptr_t base);
void cmu_blk_rot_init(uintptr_t base);
void cmu_blk_peri_init(uintptr_t base);
void cmu_blk_ebus_d_init(uintptr_t base);
void cmu_blk_ebus_r_init(uintptr_t base);
void cmu_blk_ebus_u_init(uintptr_t base);
void cmu_blk_nbus_d_init(uintptr_t base);
void cmu_blk_nbus_l_init(uintptr_t base);
void cmu_blk_nbus_u_init(uintptr_t base);
void cmu_blk_sbus_d_init(uintptr_t base);
void cmu_blk_sbus_l_init(uintptr_t base);
void cmu_blk_sbus_u_init(uintptr_t base);
void cmu_blk_wbus_d_init(uintptr_t base);
void cmu_blk_wbus_u_init(uintptr_t base);
void cmu_blk_dram_init_evt0(uintptr_t base);
void cmu_blk_dram_init_evt1(uintptr_t base);

/*
 * FIXME: This code is only valid in an environment where a dcl block exists.
 *  Please remove the comments and use it if necessary.
 */
/*
 *void cmu_blk_dcl_init(uintptr_t base);
 */
