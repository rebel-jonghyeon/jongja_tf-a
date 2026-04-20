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
#include "stdint.h"

#define ADD_SFR_CLEAR		0x0
#define ADD_INT_CLEAR		0x3

#define ADD_CP0_VDROP_IRQ_NO	150
#define ADD_CP0_CAL_IRQ_NO		151
#define ADD_CP1_VDROP_IRQ_NO	160
#define ADD_CP1_CAL_IRQ_NO		161
#define ADD_CP_VDROP_IRQ_PRIO	160
#define ADD_CP_CAL_IRQ_PRIO		160

/* ADD_CONTROL */
#define ADD_AUTO_CTRL		0x0
#define ADD_MANUAL_CTRL		0x1
#define ADD_DIV2_EN			0x0
#define ADD_SCAL_0P5V		0x0
#define ADD_SCAL_0P5_0P65	0x1
#define ADD_SCAL_0P65_0P8	0x2
#define ADD_SCAL_0P8_0P9	0x3
#define ADD_ENABLE			0x1
#define ADD_DISABLE			0x0

/* ADD_CONFIG0 */
/* ADD_CONFIG1 */
/* ADD_DAC_CAL_CONTROL */
#define ADD_DAC_CAL_ENABLE	0x1
#define ADD_DAC_CAL_DISABLE	0x0
/* ADD_DAC_CAL_CONFIG */
#define ADD_D_START				0xA
#define ADD_D_DIFF				0x14
#define ADD_DAC_CAL_INTERVAL	0x5
/* ADD_DAC_CAL_DEBUG */
/* ADD_INT_MASK */
#define ADD_INT0_MASK		0x1
#define ADD_INT1_MASK		0x1

/* ADD_INT_CLR */
#define ADD_INT0_CLEAR		0x1
#define ADD_INT1_CLEAR		0x1

/* SYSREG_CP0 : to control interrupt enable */
#define EN_ADD					0x378
#define SYSREG_CP0_ADD_ENABLE	0x1
#define SYSREG_CP0_ADD_DISABLE	0x0
#define SYSREG_CP1_ADD_ENABLE	0x1
#define SYSREG_CP1_ADD_DISABLE	0x0

union add_con_add_control {
	struct {
		uint32_t en:1; /* [0:0] */
		uint32_t reserved0:3; /* [3:1] */
		uint32_t d:8; /* [11:4] */
		uint32_t scal:2; /* [13:12] */
		uint32_t div2_en:1; /* [14:14] */
		uint32_t mux_lpf:1; /* [15:15] */
		uint32_t reserved1:12; /* [27:16] */
		uint32_t add_controller_version:4; /* [31:28] */
	};
	uint32_t val;
};

union add_con_add_config0 {
	struct {
		uint32_t ext_lpf_on_time:16; /* [15:0] */
		uint32_t start_up_time:16; /* [31:16] */
	};
	uint32_t val;
};

union add_con_add_config1 {
	struct {
		uint32_t screen_flag_time:16; /* [15:0] */
		uint32_t reserved0:16; /* [31:16] */
	};
	uint32_t val;
};

union add_con_add_dac_cal_control {
	struct {
		uint32_t dac_calibration_enable:1; /* [0:0] */
		uint32_t reserved0:31; /* [31:1] */
	};
	uint32_t val;
};

union add_con_add_dac_cal_config {
	struct {
		uint32_t dac_cal_interval:16; /* [15:0] */
		uint32_t d_start:8; /* [23:16] */
		uint32_t d_diff:8; /* [31:24] */
	};
	uint32_t val;
};

union add_con_add_dac_cal_debug {
	struct {
		uint32_t dac_calibration_done:1; /* [0:0] */
		uint32_t dac_calibration_fail:1; /* [1:1] */
		uint32_t reserved0:2; /* [3:2] */
		uint32_t fsm_debug:4; /* [7:4] */
		uint32_t reserved1:8; /* [15:8] */
		uint32_t d_debug:8; /* [23:16] */
		uint32_t d_ref:8; /* [31:24] */
	};
	uint32_t val;
};

union add_con_add_int_mask {
	struct {
		uint32_t int0_mask:1; /* [0:0] */
		uint32_t int1_mask:1; /* [1:1] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

union add_con_add_int_clr {
	struct {
		uint32_t int0_clr:1; /* [0:0] */
		uint32_t int1_clr:1; /* [1:1] */
		uint32_t reserved0:30; /* [31:2] */
	};
	uint32_t val;
};

struct add_con {
	union add_con_add_control add_control; /* offset : 0x0 */
	union add_con_add_config0 add_config0; /* offset : 0x4 */
	union add_con_add_config1 add_config1; /* offset : 0x8 */
	union add_con_add_dac_cal_control add_dac_cal_control; /* offset : 0xc */
	union add_con_add_dac_cal_config add_dac_cal_config; /* offset : 0x10 */
	union add_con_add_dac_cal_debug add_dac_cal_debug; /* offset : 0x14 */
	union add_con_add_int_mask add_int_mask; /* offset : 0x18 */
	union add_con_add_int_clr add_int_clr; /* offset : 0x1c */
};

union sysreg_cp_en_add {
	struct {
		uint32_t en_add:1;
		uint32_t reserved:31;
	};
};

struct sysreg_cp {
	union sysreg_cp_en_add en_add;
};

void add_enable_cp0_dfs(void);
void add_enable_cp1_dfs(void);
void add_disable_cp0_dfs(void);
void add_disable_cp1_dfs(void);
void add_adjust_d_diff_cp0(uint8_t v_diff);
void add_adjust_d_diff_cp1(uint8_t v_diff);
uint8_t add_get_adjusted_d_cp0(void);
uint8_t add_get_adjusted_d_cp1(void);
