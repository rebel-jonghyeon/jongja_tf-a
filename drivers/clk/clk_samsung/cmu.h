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
#include <platform_def.h>
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

enum F0434_FREQ {
	_2_3GHZ,
	_2_0GHZ,
	_1_8GHZ,
	_1_7GHZ,
	_1_6GHZ,
	_1_5GHZ,
	_1_4GHZ,
	_1_2GHZ,
	_1_0GHZ,
	_0_8GHZ,
	NOT_SUPPORT_F0434,
};

enum F0435_FREQ {
	_9_6GHZ,
	_9_2GHZ,
	_8_0GHZ,
	_6_4GHZ,
	_4_8GHZ,
	NOT_SUPPORT_F0435,
};

/**
 * @fn		void cmu_init_bl1(void)
 * @brief	Initialize the blocks clock tree to its default settings.
 */
void cmu_init_bl1(const uint32_t bootmode);

/**
 * @fn		void cmu_init_bl2(uint64_t chiplet_offset)
 * @brief	Initialize the block's clock tree to its default settings.
 * @param   chiplet_offset: The base address of each chiplet in the cmu block.
 */
void cmu_init_bl2(uintptr_t chiplet_offset);

/**
 * @fn		cmu_init_rbc(const uint32_t chiplet_id, const uintptr_t base_addr)
 * @brief	Initialize the blk_rbc's clock tree of each die to its default settings.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of each chiplet in the cmu block.
 */
void cmu_init_rbc(const uint32_t chiplet_id, const uintptr_t base_addr);
void cmu_blk_dram_init_evt0(uintptr_t base, uint32_t lvl);
void cmu_blk_dram_init_evt1(uintptr_t base, uint32_t lvl);
void cmu_blk_dram_init_evt0_by_freq(uintptr_t base, uint32_t target_freq);
void cmu_blk_dram_init_evt1_by_freq(uintptr_t base, uint32_t target_freq);
