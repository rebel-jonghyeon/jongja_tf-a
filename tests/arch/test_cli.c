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

#include "test_common.h"
#include "test_cli.h"
#include "FreeRTOS.h"
#include "printf.h"

/* CLI must not be called from any IRQ */
static inline void test_cli_is_inside_interrupt(void)
{
	if (xPortIsInsideInterrupt()) {
		#ifdef __TARGET_CP
		printf("[#%ld] Error CLI is inside IRQ\n", get_current_cpuid());
		#else
		printf("Error CLI is inside IRQ\n");
		#endif
	}
}

/* TODO: Add more tests */

uint8_t test_cli(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart CLI runtime service test\n");

	test_cli_is_inside_interrupt();

	return ret;
}

static const char help_cli[] = "[cli]\n * Test for CLI runtime service\n\r\n";

CLI_REGISTER(cli, NULL, test_cli, help_cli);
