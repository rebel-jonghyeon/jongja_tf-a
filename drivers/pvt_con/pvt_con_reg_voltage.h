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
#include <common.h>
#include "pvt_con_config.h"

/* PVT voltage sensor registers */
/**
 * Vr_TRIMINFO (r = 0, 1, ..., V-1)	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : TRIMINFO_VS
 */
union pvt_v_triminfo_reg {
	struct {
		RO uint32_t triminfo_vs:PVT_VOLTAGE_N_BIT;
		RO uint32_t reserved:32 - PVT_VOLTAGE_N_BIT;

		/* bits[N-1:0] | R  | OTP information for error calibration	| Reset Value = 0x000 */
		/* bits[31: N] | -  | Reserved								| Reset Value = 0x0_0000 */
	};
	RO uint32_t val;
};

/**
 * Vr_PROBE_EN_VS	(Reset Value = 0x0000_0001)
 * [31: 2] : RSVD	/ [    1] : VOL_RANGE_TS
 * [    0] : PROBE_EN_VS
 */
union pvt_v_probe_en_vs_reg {
	struct {
		RW uint32_t probe_en_vs:1;
		RW uint32_t vol_range_ts:1;
		RO uint32_t reserved:30;

		/* bits[    0] | RW | VS PROBE Vr Enable/Disable	| Reset Value = 1'b1 */
		/* bits[    1] | RW | Voltage sensor input range	| Reset Value = 1'b0 */
		/* bits[31: 2] | -  | Reserved						| Reset Value = 0x0000_0000 */
	};
	RW uint32_t val;
};

/**
 * Vr_CURRENT_VOL	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : CurrVoltage
 */
union pvt_v_current_vol_reg {
	struct {
		RO uint32_t currvoltage:PVT_VOLTAGE_N_BIT;
		RO uint32_t reserved:32 - PVT_VOLTAGE_N_BIT;

		/* bits[N-1:0] | R  | Current voltage of probe Vr	| Reset Value = 0x0 */
		/* bits[31: N] | -  | Reserved						| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * Vr_VS_STATUS		(Reset Value = 0x0000_0000)
 * [31: 1] : RSVD	/ [    0] : VS_VALID
 */
union pvt_v_vs_status_reg {
	struct {
		RO uint32_t vs_valid:1;
		RO uint32_t reserved:31;

		/* bits[    0] | R  | SW can read voltage of probe Vr	| Reset Value = 0x0 */
		/* bits[31: 1] | -  | Reserved							| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * Vr_PAST_VOL	(Reset Value = 0x0000_0000)
 * [31:N+16] : RSVD	/ [N+15:16] : PastVOL1
 * [15: N] : RSVD	/ [N-1:0] : PastVOL0
 */
union pvt_v_past_vol_reg {
	struct {
		RO uint32_t pastvol0:PVT_VOLTAGE_N_BIT;
		RO uint32_t reserved0:16 - PVT_VOLTAGE_N_BIT;
		RO uint32_t pastvol1:PVT_VOLTAGE_N_BIT;
		RO uint32_t reserved1:16 - PVT_VOLTAGE_N_BIT;

		/* bits[N-1:0]   | R  | Past voltage 0	| Reset Value = 0x0 */
		/* bits[15:N]    | -  | Reserved		| Reset Value = 0x0 */
		/* bits[N+15:16] | R  | Past voltage 1	| Reset Value = 0x0 */
		/* bits[31:N+16] | -  | Reserved		| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/* Structure of all PVT voltage registers */
struct pvt_voltage_regs {
	RO union pvt_v_triminfo_reg		triminfo;
	RW union pvt_v_probe_en_vs_reg	probe_en_vs;
	RO union pvt_v_current_vol_reg	current_vol;
	RO union pvt_v_vs_status_reg	vs_status;
	RO union pvt_v_past_vol_reg		past_vol[PVT_VOLTAGE_N_PAST / 2];
	RO uint32_t						reserved[4];

	/* Offset = 0x400 + (r * 0x40) */
	/* Offset = 0x404 + (r * 0x40) */
	/* Offset = 0x408 + (r * 0x40) */
	/* Offset = 0x40C + (r * 0x40) */
	/* Offset = 0x410-0x42C + (4 * 0x40) */
	/* Offset = 0x430-0x43C + (4 * 0x40) */
};
