/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

union dw_apb_wdt_wdt_cr {
	struct {
		uint32_t wdt_en:1; /* [0:0] */
		uint32_t rmod:1; /* [1:1] */
		uint32_t rpl:3; /* [4:2] */
		uint32_t no_name:1; /* [5:5] */
		uint32_t rsvd_wdt_cr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_torr {
	struct {
		uint32_t top:4; /* [3:0] */
		uint32_t rsvd_top_init:4; /* [7:4] */
		uint32_t rsvd_wdt_torr:24; /* [31:8] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_ccvr {
	struct {
		uint32_t wdt_ccvr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_crr {
	struct {
		uint32_t wdt_crr:8; /* [7:0] */
		uint32_t rsvd_wdt_crr:24; /* [31:8] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_stat {
	struct {
		uint32_t wdt_stat:1; /* [0:0] */
		uint32_t rsvd_wdt_stat:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_eoi {
	struct {
		uint32_t wdt_eoi:1; /* [0:0] */
		uint32_t rsvd_wdt_eoi:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_prot_level {
	struct {
		uint32_t wdt_prot_level:3; /* [2:0] */
		uint32_t rsvd_wdt_prot_level:29; /* [31:3] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_param_5 {
	struct {
		uint32_t cp_wdt_user_top_max; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_param_4 {
	struct {
		uint32_t cp_wdt_user_top_init_max; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_param_3 {
	struct {
		uint32_t cd_wdt_top_rst; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_param_2 {
	struct {
		uint32_t cp_wdt_cnt_rst; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_param_1 {
	struct {
		uint32_t wdt_always_en:1; /* [0:0] */
		uint32_t wdt_dflt_rmod:1; /* [1:1] */
		uint32_t wdt_dual_top:1; /* [2:2] */
		uint32_t wdt_hc_rmod:1; /* [3:3] */
		uint32_t wdt_hc_rpl:1; /* [4:4] */
		uint32_t wdt_hc_top:1; /* [5:5] */
		uint32_t wdt_use_fix_top:1; /* [6:6] */
		uint32_t wdt_pause:1; /* [7:7] */
		uint32_t apb_data_width:2; /* [9:8] */
		uint32_t wdt_dflt_rpl:3; /* [12:10] */
		uint32_t rsvd_15_13:3; /* [15:13] */
		uint32_t wdt_dflt_top:4; /* [19:16] */
		uint32_t wdt_dflt_top_init:4; /* [23:20] */
		uint32_t wdt_cnt_width:5; /* [28:24] */
		uint32_t rsvd_31_29:3; /* [31:29] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_version {
	struct {
		uint32_t wdt_comp_version; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_wdt_wdt_comp_type {
	struct {
		uint32_t wdt_comp_type; /* [31:0] */
	};
	uint32_t val;
};

struct dw_apb_wdt {
	union dw_apb_wdt_wdt_cr wdt_cr; /* offset : 0x0 */
	union dw_apb_wdt_wdt_torr wdt_torr; /* offset : 0x4 */
	union dw_apb_wdt_wdt_ccvr wdt_ccvr; /* offset : 0x8 */
	union dw_apb_wdt_wdt_crr wdt_crr; /* offset : 0xc */
	union dw_apb_wdt_wdt_stat wdt_stat; /* offset : 0x10 */
	union dw_apb_wdt_wdt_eoi wdt_eoi; /* offset : 0x14 */
	uint32_t reserved_1;
	union dw_apb_wdt_wdt_prot_level wdt_prot_level; /* offset : 0x1c */
	uint32_t reserved_2[49];
	union dw_apb_wdt_wdt_comp_param_5 wdt_comp_param_5; /* offset : 0xe4 */
	union dw_apb_wdt_wdt_comp_param_4 wdt_comp_param_4; /* offset : 0xe8 */
	union dw_apb_wdt_wdt_comp_param_3 wdt_comp_param_3; /* offset : 0xec */
	union dw_apb_wdt_wdt_comp_param_2 wdt_comp_param_2; /* offset : 0xf0 */
	union dw_apb_wdt_wdt_comp_param_1 wdt_comp_param_1; /* offset : 0xf4 */
	union dw_apb_wdt_wdt_comp_version wdt_comp_version; /* offset : 0xf8 */
	union dw_apb_wdt_wdt_comp_type wdt_comp_type; /* offset : 0xfc */
};
