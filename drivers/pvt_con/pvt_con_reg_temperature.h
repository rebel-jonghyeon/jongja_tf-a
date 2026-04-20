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

/* PVT temperature sensor registers */
/**
 * Tr_TRIMINFO1 (r = 0, 1, ..., R)	(Reset Value = 0x0000_0000)
 * [31:16+N] : RSVD	/ [15+N:16] : TRIMINFO_85
 * [15: N] : RSVD	/ [N-1:0] : TRIMINFO_25
 */
union pvt_t_triminfo1_reg {
	struct {
		RO uint32_t triminfo_25:PVT_TEMPERATURE_N;
		RO uint32_t reserved0:16 - PVT_TEMPERATURE_N;
		RO uint32_t triminfo_85:PVT_TEMPERATURE_N;
		RO uint32_t reserved1:16 - PVT_TEMPERATURE_N;

		/* bits[N-1:0]   | R  | OTP information for 25	| Reset Value = 0x000 */
		/* bits[15: N]   | -  | Reserved				| Reset Value = 0x0 */
		/* bits[15+N:16] | R  | OTP information for 85	| Reset Value = 0x000 */
		/* bits[31:16+N] | -  | Reserved				| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * Tr_TRIMINFO2	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : TRIMINFO_M40
 */
union pvt_t_triminfo2_reg {
	struct {
		RO uint32_t triminfo_m40:PVT_TEMPERATURE_N;
		RO uint32_t reserved:32 - PVT_TEMPERATURE_N;

		/* bits[N-1:0] | R  | OTP information for -40	| Reset Value = 0x000 */
		/* bits[31: N] | -  | Reserved					| Reset Value = 0x0_0000 */
	};
	RO uint32_t val;
};

/**
 * Tr_PROBE_EN_TS	(Reset Value = 0x0000_0003)
 * [31: 2] : RSVD	/ [    1] : EN_CYCLE
 * [    0] : PROBE_EN_TS
 */
union pvt_t_probe_en_ts_reg {
	struct {
		RW uint32_t probe_en_ts:1;
		RW uint32_t en_cycle:1;
		RO uint32_t reserved:30;

		/* bits[    0] | RW | TS PROBE Tr Enable/Disable	| Reset Value = 1'b1 */
		/* bits[    1] | RW | Fast conversion mode enable	| Reset Value = 1'b1 */
		/* bits[31: 2] | -  | Reserved						| Reset Value = 0x0000_0000 */
	};
	RW uint32_t val;
};

/**
 * Tr_INTEN		(Reset Value = 0x0000_0000)
 * [31:24] : RSVD	/ [23:16] : IntEn_Fall[7:0]
 * [15: 9] : RSVD	/ [ 8: 0] : IntEn_Rise[8:0]
 */
union pvt_t_inten_reg {
	struct {
		RW uint32_t inten_rise0:1;
		RW uint32_t inten_rise1:1;
		RW uint32_t inten_rise2:1;
		RW uint32_t inten_rise3:1;
		RW uint32_t inten_rise4:1;
		RW uint32_t inten_rise5:1;
		RW uint32_t inten_rise6:1;
		RW uint32_t inten_rise7:1;
		RW uint32_t inten_rise8:1;
		RO uint32_t reserved0:7;
		RW uint32_t inten_fall0:1;
		RW uint32_t inten_fall1:1;
		RW uint32_t inten_fall2:1;
		RW uint32_t inten_fall3:1;
		RW uint32_t inten_fall4:1;
		RW uint32_t inten_fall5:1;
		RW uint32_t inten_fall6:1;
		RW uint32_t inten_fall7:1;
		RO uint32_t reserved1:8;

		/* bits[    0] | RW | INTREQ_RISE[0] enable					| Reset Value = 0x0 */
		/* bits[    1] | RW | INTREQ_RISE[1] enable					| Reset Value = 0x0 */
		/* bits[    2] | RW | INTREQ_RISE[2] enable					| Reset Value = 0x0 */
		/* bits[    3] | RW | INTREQ_RISE[3] enable					| Reset Value = 0x0 */
		/* bits[    4] | RW | INTREQ_RISE[4] enable					| Reset Value = 0x0 */
		/* bits[    5] | RW | INTREQ_RISE[5] enable					| Reset Value = 0x0 */
		/* bits[    6] | RW | INTREQ_RISE[6] enable					| Reset Value = 0x0 */
		/* bits[    7] | RW | INTREQ_RISE[7] enable (tripping mode)	| Reset Value = 0x0 */
		/* bits[    8] | RW | INTREQ_RISE[8] enable (DFS mode)		| Reset Value = 0x0 */
		/* bits[15: 9] | -  | Reserved								| Reset Value = 0x0 */
		/* bits[   16] | RW | INTREQ_FALL[0] enable					| Reset Value = 0x0 */
		/* bits[   17] | RW | INTREQ_FALL[1] enable					| Reset Value = 0x0 */
		/* bits[   18] | RW | INTREQ_FALL[2] enable					| Reset Value = 0x0 */
		/* bits[   19] | RW | INTREQ_FALL[3] enable					| Reset Value = 0x0 */
		/* bits[   20] | RW | INTREQ_FALL[4] enable					| Reset Value = 0x0 */
		/* bits[   21] | RW | INTREQ_FALL[5] enable					| Reset Value = 0x0 */
		/* bits[   22] | RW | INTREQ_FALL[6] enable					| Reset Value = 0x0 */
		/* bits[   23] | RW | INTREQ_FALL[7] enable					| Reset Value = 0x0 */
		/* bits[31:24] | -  | Reserved								| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * Tr_INTPEND	(Reset Value = 0x0000_0000)
 * [31:24] : RSVD	/ [23:16] : IntPend_Fall[7:0]
 * [15: 9] : RSVD	/ [ 8: 0] : IntPend_Rise[8:0]
 */
union pvt_t_intpend_reg {
	struct {
		RW uint32_t intpend_rise0:1;
		RW uint32_t intpend_rise1:1;
		RW uint32_t intpend_rise2:1;
		RW uint32_t intpend_rise3:1;
		RW uint32_t intpend_rise4:1;
		RW uint32_t intpend_rise5:1;
		RW uint32_t intpend_rise6:1;
		RW uint32_t intpend_rise7:1;
		RW uint32_t intpend_rise8:1;
		RO uint32_t reserved0:7;
		RW uint32_t intpend_fall0:1;
		RW uint32_t intpend_fall1:1;
		RW uint32_t intpend_fall2:1;
		RW uint32_t intpend_fall3:1;
		RW uint32_t intpend_fall4:1;
		RW uint32_t intpend_fall5:1;
		RW uint32_t intpend_fall6:1;
		RW uint32_t intpend_fall7:1;
		RO uint32_t reserved1:8;

		/* bits[    0] | RW | INTREQ_RISE[0] pending and clear	| Reset Value = 0x0 */
		/* bits[    1] | RW | INTREQ_RISE[1] pending and clear	| Reset Value = 0x0 */
		/* bits[    2] | RW | INTREQ_RISE[2] pending and clear	| Reset Value = 0x0 */
		/* bits[    3] | RW | INTREQ_RISE[3] pending and clear	| Reset Value = 0x0 */
		/* bits[    4] | RW | INTREQ_RISE[4] pending and clear	| Reset Value = 0x0 */
		/* bits[    5] | RW | INTREQ_RISE[5] pending and clear	| Reset Value = 0x0 */
		/* bits[    6] | RW | INTREQ_RISE[6] pending and clear	| Reset Value = 0x0 */
		/* bits[    7] | RW | INTREQ_RISE[7] pending and clear	| Reset Value = 0x0 */
		/* bits[    8] | RW | INTREQ_RISE[8] pending and clear	| Reset Value = 0x0 */
		/* bits[15: 9] | -  | Reserved							| Reset Value = 0x0 */
		/* bits[   16] | RW | INTREQ_[0] pending and clear		| Reset Value = 0x0 */
		/* bits[   17] | RW | INTREQ_[1] pending and clear		| Reset Value = 0x0 */
		/* bits[   18] | RW | INTREQ_[2] pending and clear		| Reset Value = 0x0 */
		/* bits[   19] | RW | INTREQ_[3] pending and clear		| Reset Value = 0x0 */
		/* bits[   20] | RW | INTREQ_[4] pending and clear		| Reset Value = 0x0 */
		/* bits[   21] | RW | INTREQ_[5] pending and clear		| Reset Value = 0x0 */
		/* bits[   22] | RW | INTREQ_[6] pending and clear		| Reset Value = 0x0 */
		/* bits[   23] | RW | INTREQ_[7] pending and clear		| Reset Value = 0x0 */
		/* bits[31:24] | -  | Reserved							| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * Tr_INTSTAT	(Reset Value = 0x0000_0000)
 * [31:24] : RSVD	/ [23:16] : IntState_Fall[7:0]
 * [15: 9] : RSVD	/ [ 8: 0] : IntState_Rise[8:0]
 */
union pvt_t_intstat_reg {
	struct {
		RO uint32_t intstate_rise0:1;
		RO uint32_t intstate_rise1:1;
		RO uint32_t intstate_rise2:1;
		RO uint32_t intstate_rise3:1;
		RO uint32_t intstate_rise4:1;
		RO uint32_t intstate_rise5:1;
		RO uint32_t intstate_rise6:1;
		RO uint32_t intstate_rise7:1;
		RO uint32_t intstate_rise8:1;
		RO uint32_t reserved0:7;
		RO uint32_t intstate_fall0:1;
		RO uint32_t intstate_fall1:1;
		RO uint32_t intstate_fall2:1;
		RO uint32_t intstate_fall3:1;
		RO uint32_t intstate_fall4:1;
		RO uint32_t intstate_fall5:1;
		RO uint32_t intstate_fall6:1;
		RO uint32_t intstate_fall7:1;
		RO uint32_t reserved1:8;

		/* bits[    0] | R  | INTREQ_RISE[0] status	| Reset Value = 0x0 */
		/* bits[    1] | R  | INTREQ_RISE[1] status	| Reset Value = 0x0 */
		/* bits[    2] | R  | INTREQ_RISE[2] status	| Reset Value = 0x0 */
		/* bits[    3] | R  | INTREQ_RISE[3] status	| Reset Value = 0x0 */
		/* bits[    4] | R  | INTREQ_RISE[4] status	| Reset Value = 0x0 */
		/* bits[    5] | R  | INTREQ_RISE[5] status	| Reset Value = 0x0 */
		/* bits[    6] | R  | INTREQ_RISE[6] status	| Reset Value = 0x0 */
		/* bits[    7] | R  | INTREQ_RISE[7] status	| Reset Value = 0x0 */
		/* bits[    8] | R  | INTREQ_RISE[8] status	| Reset Value = 0x0 */
		/* bits[15: 9] | -  | Reserved				| Reset Value = 0x0 */
		/* bits[   16] | R  | INTREQ_FALL[0] status	| Reset Value = 0x0 */
		/* bits[   17] | R  | INTREQ_FALL[1] status	| Reset Value = 0x0 */
		/* bits[   18] | R  | INTREQ_FALL[2] status	| Reset Value = 0x0 */
		/* bits[   19] | R  | INTREQ_FALL[3] status	| Reset Value = 0x0 */
		/* bits[   20] | R  | INTREQ_FALL[4] status	| Reset Value = 0x0 */
		/* bits[   21] | R  | INTREQ_FALL[5] status	| Reset Value = 0x0 */
		/* bits[   22] | R  | INTREQ_FALL[6] status	| Reset Value = 0x0 */
		/* bits[   23] | R  | INTREQ_FALL[7] status	| Reset Value = 0x0 */
		/* bits[31:24] | -  | Reserved				| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * Tr_THRESHOLD_TEMP_RISE	(Reset Value = 0x0???_0???)
 * [31:N+16] : RSVD	/ [N+15:16] : ThresholdLevel_Rise1
 * [15: N]   : RSVD	/ [N-1:0]   : ThresholdLevel_Rise0
 */
union pvt_t_threshold_temp_rise_reg {
	struct {
		RW uint32_t thresholdlevel_rise0:PVT_TEMPERATURE_N;
		RO uint32_t reserved0:16 - PVT_TEMPERATURE_N;
		RW uint32_t thresholdlevel_rise1:PVT_TEMPERATURE_N;
		RO uint32_t reserved1:16 - PVT_TEMPERATURE_N;

		/* bits[N-1:0]   | RW | Threshold level 0 to INTREQ_TS_RISE0	| Reset Value = 0x??? */
		/* bits[15: N]   | -  | Reserved								| Reset Value = 0x0 */
		/* bits[N+15:16] | RW | Threshold level 1 to INTREQ_TS_RISE1	| Reset Value = 0x??? */
		/* bits[31:N+16] | -  | Reserved								| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * Tr_THRESHOLD_TEMP_FALL	(Reset Value = 0x0???_0???)
 * [31:N+16] : RSVD	/ [N+15:16] : ThresholdLevel_Fall1
 * [15: N]   : RSVD	/ [N-1:0]   : ThresholdLevel_Fall0
 */
union pvt_t_threshold_temp_fall_reg {
	struct {
		RW uint32_t thresholdlevel_fall0:PVT_TEMPERATURE_N;
		RO uint32_t reserved0:16 - PVT_TEMPERATURE_N;
		RW uint32_t thresholdlevel_fall1:PVT_TEMPERATURE_N;
		RO uint32_t reserved1:16 - PVT_TEMPERATURE_N;

		/* bits[N-1:0]   | RW | Threshold level 0 to INTREQ_TS_FALL0	| Reset Value = 0x??? */
		/* bits[15: N]   | -  | Reserved								| Reset Value = 0x0 */
		/* bits[N+15:16] | RW | Threshold level 1 to INTREQ_TS_FALL1	| Reset Value = 0x??? */
		/* bits[31:N+16] | -  | Reserved								| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * Tr_CURRENT_TEMP	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : CurrentTemp
 */
union pvt_t_current_temp_reg {
	struct {
		RO uint32_t currenttemp:PVT_TEMPERATURE_N;
		RO uint32_t reserved:32 - PVT_TEMPERATURE_N;

		/* bits[N-1:0] | R  | Current temperature of probe Tr	| Reset Value = 0x0 */
		/* bits[31: N] | -  | Reserved							| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * Tr_TS_STATUS		(Reset Value = 0x0000_0000)
 * [31: 3] : RSVD				/ [    2] : THERM_DFS_STATUS
 * [    1] : THERM_TRIP_STATUS	/ [    0] : TS_VALID
 */
union pvt_t_ts_status_reg {
	struct {
		uint32_t ts_valid:1;
		uint32_t therm_trip_status:1;
		uint32_t therm_dfs_status:1;
		uint32_t reserved:29;

		/* bits[    0] | R  | SW can read temperature of Probe Tr		| Reset Value = 0x0 */
		/* bits[    1] | R  | Thermal trip status of Probe Tr			| Reset Value = 0x0 */
		/* bits[    2] | R  | Thermal dynamic frequency scaling status	| Reset Value = 0x0 */
		/* bits[31: 3] | -  | Reserved									| Reset Value = 0x0 */
	};
	uint32_t val;
};

/**
 * Tr_PAST_TEMP		(Reset Value = 0x0000_0000)
 * [31:N+16] : RSVD	/ [N+15:16] : PastTemp1
 * [15: N] : RSVD	/ [N-1:0] : PastTemp0
 */
union pvt_t_past_temp_reg {
	struct {
		uint32_t pasttemp0:PVT_TEMPERATURE_N;
		uint32_t reserved0:16 - PVT_TEMPERATURE_N;
		uint32_t pasttemp1:PVT_TEMPERATURE_N;
		uint32_t reserved1:16 - PVT_TEMPERATURE_N;

		/* bits[N-1:0]   | R  | Past temperature 0	| Reset Value = 0x0 */
		/* bits[15: N]   | -  | Reserved			| Reset Value = 0x0 */
		/* bits[N+15:16] | R  | Past temperature 1	| Reset Value = 0x0 */
		/* bits[31:N+16] | -  | Reserved			| Reset Value = 0x0 */
	};
	uint32_t val;
};

/* Structure of all Temperature PVT registers */
struct pvt_temperature_regs {
	RO union pvt_t_triminfo1_reg			triminfo1;
	RO union pvt_t_triminfo2_reg			triminfo2;
	RW union pvt_t_probe_en_ts_reg			probe_en_ts;
	RW union pvt_t_inten_reg				inten;
	RW union pvt_t_intpend_reg				intpend;
	RO union pvt_t_intstat_reg				intstat;
	RW union pvt_t_threshold_temp_rise_reg	threshold_temp_rise[PVT_TEMPERATURE_N_RISE / 2];
	RW union pvt_t_threshold_temp_fall_reg	threshold_temp_fall[PVT_TEMPERATURE_N_FALL / 2];
	RO union pvt_t_current_temp_reg			current_temp;
	union pvt_t_ts_status_reg				ts_status;
	union pvt_t_past_temp_reg				past_temp[PVT_TEMPERATURE_N_PAST / 2];
	uint32_t								reserved[8];

	/* Offset = 0x800 + (0x80 * r) */
	/* Offset = 0x804 + (0x80 * r) */
	/* Offset = 0x808 + (0x80 * r) */
	/* Offset = 0x80C + (0x80 * r) */
	/* Offset = 0x810 + (0x80 * r) */
	/* Offset = 0x814 + (0x80 * r) */
	/* Offset = 0x818-0x824 + (0x80 * r) */
	/* Offset = 0x828-0x834 + (0x80 * r) */
	/* Offset = 0x838 + (0x80 * r) */
	/* Offset = 0x83C + (0x80 * r) */
	/* Offset = 0x840-0x85C + (0x80 * r) */
	/* Offset = 0x860-0x87C + (0x80 * r) */
};
