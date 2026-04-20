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

#pragma once

#include <lib/libc/stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <platform_def.h>
#include <common/debug.h>
#include <drivers/hbm3/hbm3_init.h>
#include <drivers/delay_timer.h>

// Memory Test Analyzer
#define USE_MTA

#define _WAIT(a, b)            \
	while (((a) & (b)) != (b)) \
		asm("nop")

#define _WAIT2(a, b)            \
	while (((a) & (b)) != 0x1) \
		asm("nop");	\
	while (((a) & (b)) != 0x0) \
		asm("nop")

#define CH_SIZE 0x90000000

/*
 * Controller Memory Test Size
 */
enum mt_bits {
	MTBITS_512B = 3,
	MTBITS_1KB,
	MTBITS_2KB,		// 5
	MTBITS_4KB,
	MTBITS_8KB,
	MTBITS_16KB,
	MTBITS_32KB,
	MTBITS_64KB,	// 10
	MTBITS_128KB,
	MTBITS_256KB,
	MTBITS_512KB,
	MTBITS_1MB,
	MTBITS_2MB,		// 15
	MTBITS_4MB,
	MTBITS_8MB,
	MTBITS_16MB,
	MTBITS_32MB,
	MTBITS_64MB,	// 20
	MTBITS_128MB,
	MTBITS_256MB,
	MTBITS_512MB,
	MTBITS_1GB,
	MTBITS_2GB,	// 25
	MTBITS_MAX = MTBITS_2GB
};

/*
 * Controller Memory Test Pattern
 */
enum TEST_PATTERN {
	TP_COUNTING,		// 0x0 -- Counting pattern
	TP_WALKING1s,		// 0x1 -- Walking 1’s
	TP_REPSEUDO,		// 0x2 – Repeating Pseudo-random
	TP_NREPSEUDO,		// 0x3 – Non-Repeating Pseudo-random
	TP_ALTERN01,		// 0x4 -- Alternating 1’s and 0’s
	TP_ALTERN5A,		// 0x5 -- Alternating 5’s and A’s
	TP_USER,			// 0x6 –- User-specified
	TP_NREPSEUDO16b,	// 0x7 – Non-repeating Pseudo-random 16-bit
	TP_NREPSEUDO8b,		// 0x8 – Non-repeating Pseudo-random 8-bit
	TP_MAX
};

static struct _mt_saved_cfg {
	uint32_t _cfg_ecc_correction_en;
	uint32_t _init_ecc_scrub_en;
	uint32_t _cfg_ecc_scrub_init_rmw;
	uint32_t _init_idle_time_to_power_down;
	uint32_t _init_sbref_en;
	uint32_t _cfg_reorder_en;
	uint32_t _mt_addr_bits;
	uint32_t _cfg_force_bgpos0;
} mt_saved;

#define _SAVE(reg, val)            \
	mt_saved._##reg = (val)

void turn_off_phy_mastering(volatile struct ddr_csr *ctrl);

void turn_on_phy_mastering(volatile struct ddr_csr *ctrl);

void turn_off_auto_refresh(volatile struct ddr_csr *ctrl);

void turn_on_auto_refresh(volatile struct ddr_csr *ctrl);

void disable_reorder_sbref(volatile struct ddr_csr *ctrl);

void restore_reorder_sbref(volatile struct ddr_csr *ctrl, uint32_t reorder_en, uint32_t sbref_en);
