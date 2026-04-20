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
#include "test_cm7.h"
#include "printf.h"

/* NVIC */
static void test_cm7_nvic(void)
{
	/* TODO */
}

/* Tick interrupt */
static void test_cm7_tick_irq(void)
{
	/* TODO */
}

/* MPU */
static void test_cm7_mpu(void)
{
	/* TODO */
}

/* FPU */
static void test_cm7_fpu(void)
{
	/* Is enabled */
	/* TODO */
}

/* Context switching */
static void test_cm7_context_switching(void)
{
	/* TODO */
}

/* TODO: Add more tests */

static void (*test_cm7_sequence[])(void) = {
	test_cm7_nvic,
	test_cm7_tick_irq,
	test_cm7_mpu,
	test_cm7_fpu,
	test_cm7_context_switching,
};

uint8_t test_cm7_cli(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart CM7 architecture test\n");

	for (uint32_t i = 0; i < sizeof(test_cm7_sequence) / sizeof(void (*)(void)); ++i) {
		test_cm7_sequence[i]();
	}

	return ret;
}

static const char help_cm7[] = "[cm7]\n * Test for CM7 architecture code\n\r\n";

CLI_REGISTER(cm7, NULL, test_cm7_cli, help_cm7);
