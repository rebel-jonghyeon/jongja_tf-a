/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <stdint.h>
#include <rebel_h_platform.h>
#include "test_common.h"
#include "mailbox.h"

#include "test_mailbox_main.h"
#include "test_cmu_main.h"
#include "test_gpio.h"
#include "test_dma_main.h"
#include "test_apb_qspi.h"

#define SEND_TO_ROT			IDX_MAILBOX_M0
#define SEND_TO_CM7			IDX_MAILBOX_CP0_M4
#define SEND_TO_SEC_CP0		IDX_MAILBOX_PERI0_M7_CPU0

static const char * const test_params[] = {
	"cp0",
	"pcie",
	"0",
	"1",
	"1",
};

uint8_t test_main(int argc, char *argv[])
{
	uint32_t dest_chiplet;

	dest_chiplet = 0;

	printf("========integrated test start=========\n");

	printf("test cmd SEND_TO_CM7\n");
	ipm_samsung_write(SEND_TO_CM7, dest_chiplet, INTEGRATED_TEST, TEST_CMD_SIZE, TEST_BUF);
	ipm_samsung_send(SEND_TO_CM7, dest_chiplet, TEST_CHANNEL, CPU1);

	printf("test cmd SEND_TO_ROT\n");
	ipm_samsung_write(SEND_TO_ROT, dest_chiplet, INTEGRATED_TEST, TEST_CMD_SIZE, TEST_BUF);
	ipm_samsung_send(SEND_TO_ROT, dest_chiplet, TEST_CHANNEL, CPU0);

	printf("test start CP0\n");
	/* Need to add test cases below*/
	test_main_apb_qspi(2, ((char **)test_params) + 2);
	test_main_cmu(1, (char **)test_params);
	test_gpio();
	test_main_mailbox(1, ((char **)test_params) + 1);
	test_main_dma(3, ((char **)test_params) + 2);

	printf("========integrated test done=========\n");
	printf("integrated test list:\n");
	printf("\t test_main_apb_qspi 0 1\n");
	printf("\t test_cmu cp0\n");
	printf("\t test_gpio\n");
	printf("\t test_mailbox pcie\n");
	printf("\t test_dma 0 1 1\n");

	return true;
}

static const char help_test_main[] =
	"[test <vector>]\r\n"
	" - [test all]\r\n"
	" - [test cp0]\r\n"
	" - [test cm7]\r\n"
	" - [test rot]\r\n"
	"\r\n";

CLI_REGISTER(test, NULL, test_main, help_test_main);
