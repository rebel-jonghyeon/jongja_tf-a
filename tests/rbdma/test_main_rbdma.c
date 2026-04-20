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

#include "rbdma_tsync_test.h"
#include "test_common.h"

uint8_t hbm_rbdma_test(int argc, char *argv[])
{
	uint32_t iter, rx, i;
	int result = 0;

	if (argc < 2) {
		return false;
	} else {
		rx = (uint32_t)strtoul(argv[0], NULL, 10);
		iter = (uint32_t)strtoul(argv[1], NULL, 10);
	}

	printf("**********************************\n");

	for (i = 0; i < iter; i++) {
		if (rx == 1) {
			result = rbdma_test_dram_2_shm();
		} else if (rx == 2) {
			result = rbdma_test_shm_2_dram();
		} else if (rx == 3) {
			result = rbdma_test_dram_2_dram();
		}
		if (result) {
			printf("[%03d] __FAIL__\n", i);
			return 1;
		} else {
			printf("[%03d] __PASS__\n", i);
		}
	}

	return 1;
}

CLI_REGISTER(rbdma, NULL, hbm_rbdma_test, "rbdma <tx=0/rx=1> <iter>");
