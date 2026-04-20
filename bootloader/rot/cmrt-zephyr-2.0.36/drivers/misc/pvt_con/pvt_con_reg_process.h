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
#include "common.h"
#include "pvt_con_config.h"

/* PVT process sensor registers */
/**
 * Pr_TRIMINFO	(r = 0, 1, ..., 15)	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : TRIMINFO_PS
 */
union pvt_p_triminfo_reg {
	struct {
		uint32_t triminfo_ps:PVT_PROCESS_N;
		uint32_t reserved:32 - PVT_PROCESS_N;

		/* bits[N-1:0] | R  | OTP information for process sensor Pr	| Reset Value = 0x000 */
		/* bits[31: N] | -  | Reserved								| Reset Value = 0x0_0000 */
	};
	uint32_t val;
};

/**
 * Pr_PROBE_EN_PS	(Reset Value = 0x0000_0001)
 * [31: 2] : RSVD	/ [    1] : HFDIV_PS
 * [    0] : PROBE_EN_PS
 */
union pvt_p_probe_en_ps {
	struct {
		uint32_t probe_en_ps:1;
		uint32_t hfdiv_ps:1;
		uint32_t reserved:30;

		/* bits[    0] | RW | PS PROBE Pr Enable/Disable			| Reset Value = 1'b1 */
		/* bits[    1] | RW | Process sensor output range selection	| Reset Value = 1'b0 */
		/* bits[31: 2] | -  | Reserved								| Reset Value = 0x0000_0000 */
	};
	uint32_t val;
};

/**
 * Pr_CURRENT_PROC	(Reset Value = 0x0000_0000)
 * [31: N] : RSVD	/ [N-1:0] : CurrProcess
 */
union pvt_p_current_proc_reg {
	struct {
		uint32_t currprocess:PVT_PROCESS_N;
		uint32_t reserved:32 - PVT_PROCESS_N;

		/* bits[N-1:0] | R  | Current process of probe Pr	| Reset Value = 0x000 */
		/* bits[31: N] | -  | Reserved						| Reset Value = 0x0_0000 */
	};
	uint32_t val;
};

/**
 * Pr_PS_STATUS		(Reset Value = 0x0000_0000)
 * [31: 1] : RSVD	/ [    0] : PS_VALID
 */
union pvt_ps_status_reg {
	struct {
		uint32_t ps_valid:1;
		uint32_t reserved:31;

		/* bits[    0] | R  | SW can read process of probe Pr	| Reset Value = 1'b0 */
		/* bits[31: 1] | -  | Reserved							| Reset Value = 0x0000_0000 */
	};
	uint32_t val;
};

/**
 * Pr_PAST_PROC	(Reset Value = 0x0000_0000)
 * [31:N+16] : RSVD	/ [N+15:16] : PastProc1
 * [15: N]   : RSVD	/ [N-1:0]   : PastProc0
 */
union pvt_past_proc_reg {
	struct {
		uint32_t pastproc0:PVT_PROCESS_N;
		uint32_t reserved0:16 - PVT_PROCESS_N;
		uint32_t pastproc1:PVT_PROCESS_N;
		uint32_t reserved1:16 - PVT_PROCESS_N;

		/* bits[N-1:0]   | R  | Past process 0	| Reset Value = 0x000 */
		/* bits[15: N]   | -  | Reserved		| Reset Value = 0x0 */
		/* bits[N+15:16] | R  | Past process 1	| Reset Value = 0x000 */
		/* bits[31:N+16] | -  | Reserved		| Reset Value = 0x0 */
	};
	uint32_t val;
};

/* Structure of all PVT process registers */
struct pvt_process_regs {
	union pvt_p_triminfo_reg		triminfo;
	union pvt_p_probe_en_ps			probe_en_ps;
	union pvt_p_current_proc_reg	current_proc;
	union pvt_ps_status_reg			ps_status;
	union pvt_past_proc_reg			past_proc[PVT_PROCESS_N_PAST / 2];
	uint32_t						reserved[4];

	/* Offset = 0x2800 + (0x40 * r) */
	/* Offset = 0x2804 + (0x40 * r) */
	/* Offset = 0x2808 + (0x40 * r) */
	/* Offset = 0x280C + (0x40 * r) */
	/* Offset = 0x2810-0x282C + (0x40 * r) */
	/* Offset = 0x2830-0x283C + (0x40 * r) */
};
