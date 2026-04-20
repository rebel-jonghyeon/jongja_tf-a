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

union sysreg_buscsr_cp_m1_user_ovrd_value {
	struct {
		uint32_t aruser_sfr:6; /* [0:0] */
		uint32_t reserved_bit_0:2;
		uint32_t awuser_sfr:6; /* [8:8] */
		uint32_t reserved_bit_1:2;
		uint32_t aruser_sfr_en:6; /* [16:16] */
		uint32_t reserved_bit_2:2;
		uint32_t awuser_sfr_en:6; /* [24:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_cp_m1_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

struct sysreg_buscsr_cp_register {
	uint32_t reserved_1[67];
	union sysreg_buscsr_cp_m1_user_ovrd_value m1_user_ovrd_value; /* offset : 0x10c */
	uint32_t reserved_5[31];
	union sysreg_buscsr_cp_m1_user_ovrd_sel m1_user_ovrd_sel; /* offset : 0x18c */
};
