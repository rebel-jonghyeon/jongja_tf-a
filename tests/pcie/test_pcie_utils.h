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

#include "FreeRTOS.h"
#include "task.h"

#include "bat.h"

#define PCIE_HOST_TC_ADDR (PCIE_HOST_BAT_BASE + 0x01000000)
#define PCIE_HOST_TC_RESULT_ADDR (PCIE_HOST_TC_ADDR + 0x4)

/* DOE */
#define PCIE_DOE_TEST_LENGTH (0x4)
#define PCIE_DOE_TEST_PAYLOAD_0 (0x12345678)
#define PCIE_DOE_TEST_PAYLOAD_1 (0x87654321)

/* MSIX */
#define PCIE_MSIX_TEST_HOST_ADDRESS (0x1000000000ULL)
#define PCIE_MSIX_TEST_HOST_ADDRESS_BAT_BASE (PCIE_HOST_BAT_BASE)
#define PCIE_MSIX_TEST_MSG_DATA (0x10000000)

/* PCIe Test case ID & Result Code*/
enum pcie_tc_id {
	TEST_ID_DOE = 0x1,
	TEST_ID_MSIX = 0x2,
};

enum pcie_tc_result {
	RESULT_NONE = 0x0,
	RESULT_PASS = 0x1,
	RESULT_FAIL = 0x2,
};

static inline int32_t check_pcie_test_result(void)
{
	while (1) {
		volatile int32_t res = rl_readl((uint32_t *)(PCIE_HOST_TC_RESULT_ADDR));

		if (res == RESULT_PASS || res == RESULT_FAIL) {
			/* Clear Result */
			rl_writel(RESULT_NONE, (uint32_t *)PCIE_HOST_TC_RESULT_ADDR);
			return res;
		}
		vTaskDelay(1);
	}

	return RESULT_FAIL;
}
