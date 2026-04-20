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

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "hbm3.h"
#include "tmrs.h"
#include "icon.h"
#include "sysreg_dram.h"

uint32_t tmrs_write(struct hbm3_config *cfg, uint32_t tmrs_code)
{
	uint32_t wdr_len;

	cfg->icon_base->wr_wdr0.wr_wdr0 = tmrs_code;

	wdr_len = 30;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = WR_WDR; /* 0x3 : Write WDR */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = wdr_len;
	icon_sw_instruction_req(cfg);

	udelay(10);

	return 0;
}

uint32_t tmrs_gen_inst(struct hbm3_config *cfg)
{
	uint32_t sw_wir = ICON_SET_WIR(ICON_WIR_CH_ALL, 0xB0); // TMRS_GEN Instruction set: WIR = 13’b0_0000_1011_0000

	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR; // 3'd0 : Set WIR
	cfg->icon_base->icon_ctrl_con0.sw_wir = sw_wir;

	icon_sw_instruction_req(cfg);
	udelay(10);

	return 0;
}

uint32_t tmrs_bypass(struct hbm3_config *cfg)
{
	uint32_t sw_wir, wdr_len;

	sw_wir = ICON_SET_WIR(ICON_WIR_CH_ALL, ICON_WIR_BYPASS); //  BYPASS WIR : 13'b1_1111_0000_0000;
	wdr_len = 1;

	cfg->icon_base->wr_wdr0.wr_wdr0 = 0x1;
	cfg->icon_base->icon_ctrl_con0.sw_fsm_mode = SET_WIR_WR_WDR; /* 3'd1 : Set WIR + Write WDR */
	cfg->icon_base->icon_ctrl_con0.sw_shiftwr_wdr_dur = wdr_len;
	cfg->icon_base->icon_ctrl_con0.sw_wir = sw_wir;
	icon_sw_instruction_req(cfg);

	udelay(10);

	return 0;
}
