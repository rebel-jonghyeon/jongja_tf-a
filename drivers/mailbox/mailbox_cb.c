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

#include <stdio.h>
#include "mailbox.h"

#ifdef __TARGET_PCIE
#ifdef USE_PCIE
#include "../../../../../drivers/pcie/pcie_mailbox_callback.h"
#endif /* USE_PCIE */
#endif /* __TARGET_PCIE */

#ifdef __TEST
#include "../../tests/common/test_common.h"
#ifdef __TARGET_CP
#include "../../tests/system_test/system_test.h"
#include "../../drivers/sic/sic.h"
#endif /* __TARGET_CP */
#endif /* __TEST */

static mailbox_rbln_callback_t user_cb;

void mailbox_register_callback(mailbox_rbln_callback_t cb)
{
    user_cb = cb;
}

void default_cb(const int inst, const int channel)
{
	switch (channel) {
#ifdef __TARGET_PCIE
#ifdef USE_PCIE
	case DRAM_INIT_DONE_CHANNEL:
		dram_init_done_cb();
		break;
#endif /* USE_PCIE */
#endif /* __TARGET_PCIE */
#ifdef __TEST
#ifdef __TARGET_PCIE
#ifdef USE_PCIE
	case PCIE_IDE_FROM_ROT_CHANNEL:
		pcie_ide_cb();
		break;
#endif /* USE_PCIE */
#else /* __TARGET_PCIE */
	case SYSTEM_TEST_CHANNEL:
		system_test_cb();
		break;
	case IMG_UPDATE_CHANNEL:
		uint32_t res;

		res = request_to_cmrt(CMRT_MW_LOAD_IMG_FROM_HBM);
		*(volatile uint32_t *)(0x1000000000) = res;
		*(volatile uint32_t *)(0x1BFFFFFFFC) = 0;
		break;
#endif /* __TARGET_CP */
	case TEST_CHANNEL:
		test_cb(inst, channel);
		break;
#endif /* __TEST */
	case RBLN_CHANNEL:
		printf("** %s inst: %d, channeld: %d\n", __func__, inst, channel);
		if(user_cb == NULL){
			printf("user_cb is null");
		}
		else{
			user_cb(inst, channel);
		}
		break;
	default:
		char data[SIZEOF_M_DATA] = {0};

		ipm_samsung_receive(inst, data, SIZEOF_M_DATA, DEFAULT_M_INDEX);

		printf("%s inst: %d, channeld: %d\n", __func__, inst, channel);
		for (int i = 0; i < SIZEOF_M_DATA; i++) {
			printf("%c", data[i]);
		}
		printf("\n");

		break;
	}
}
