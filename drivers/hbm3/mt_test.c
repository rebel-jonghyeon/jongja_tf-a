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
#include <lib/libc/stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <platform_def.h>
#include <common/debug.h>
#include <drivers/hbm3/hbm3_init.h>
#include <drivers/delay_timer.h>
#include "memtest.h"

void run_memtest(uint32_t chiplet_id)
{
	uint32_t ch;

	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		printf("mt_alg test\n");
		mt_alg_test(chiplet_id, ch);

		printf("mt_arb test\n");
		mt_arb_test(chiplet_id, ch);

		printf("mt_amt test\n");
		mt_amt_test(chiplet_id, ch);

		//printf("ch[%d] memtest\n", ch);
		// do_memtest(0x0 + (ch * 0x1000), 0x800000);
	}
}
