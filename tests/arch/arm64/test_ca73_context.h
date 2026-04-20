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

#pragma once

#include "test_ca73.h"

static void test_ca73_fpu_context(void *param)
{
	struct test_ca73_data *data = (struct test_ca73_data *)param;
	double *fpu_context0 = (double *)data->data0;
	double *fpu_context1 = (double *)data->data1;
	double temp;
	char buffer[TEST_CA73_MAX_STRING];

	for (;;) {
		temp = *fpu_context1;
		*fpu_context1 += *fpu_context0;
		*fpu_context0 = temp;
		snprintf(buffer, -1, data->msg, get_current_cpuid(), *fpu_context0, *fpu_context1);

		test_ca73_printf(buffer);

		vTaskDelay(1U);
	}
}

double test_ca73_fpu_data[TEST_CA73_MAX_TASK * 2] = {
	0.1, 0.1,
	0.2, 0.3,
	0.3, 0.5,
	0.5, 0.8,
	0.8, 1.3,
	1.3, 2.1,
	2.1, 3.4,
	3.4, 5.5,
};

static struct test_ca73_task_config test_ca73_task_config_fpu_context[TEST_CA73_MAX_TASK] = {
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context0",
		{&test_ca73_fpu_data[0], &test_ca73_fpu_data[1], "[%ld] %lf %lf task0\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context1",
		{&test_ca73_fpu_data[2], &test_ca73_fpu_data[3], "[%ld] %lf %lf task1\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context2",
		{&test_ca73_fpu_data[4], &test_ca73_fpu_data[5], "[%ld] %lf %lf task2\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context3",
		{&test_ca73_fpu_data[6], &test_ca73_fpu_data[7], "[%ld] %lf %lf task3\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context4",
		{&test_ca73_fpu_data[8], &test_ca73_fpu_data[9], "[%ld] %lf %lf task4\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context5",
		{&test_ca73_fpu_data[10], &test_ca73_fpu_data[11], "[%ld] %lf %lf task5\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context6",
		{&test_ca73_fpu_data[12], &test_ca73_fpu_data[13], "[%ld] %lf %lf task6\n"},
	},
	{
		test_ca73_fpu_context,
		"test_ca73_fpu_context7",
		{&test_ca73_fpu_data[14], &test_ca73_fpu_data[15], "[%ld] %lf %lf task7\n"},
	},
};
