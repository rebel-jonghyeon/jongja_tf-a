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

static void test_ca73_uart_task(void *param)
{
	struct test_ca73_data *data = (struct test_ca73_data *)param;
	char buffer[TEST_CA73_MAX_STRING];

	for (;;) {
		snprintf(buffer, -1, data->msg, get_current_cpuid());

		test_ca73_printf(buffer);

		vTaskDelay(1U);
	}
}

static void test_ca73_access_task(void *param)
{
	struct test_ca73_data *data = (struct test_ca73_data *)param;
	char buffer[TEST_CA73_MAX_STRING];

	for (;;) {
		(*(uint32_t *)data->data0)++;

		snprintf(buffer, -1, data->msg, get_current_cpuid(), *((uint32_t *)data->data0));

		test_ca73_printf(buffer);

		vTaskDelay(1U);
	}
}

static void test_ca73_data_transfer(void *param)
{
	struct test_ca73_data *data = (struct test_ca73_data *)param;
	QueueHandle_t recv_queue = *(QueueHandle_t *)data->data0;
	QueueHandle_t send_queue = *(QueueHandle_t *)data->data1;
	char buffer[TEST_CA73_MAX_STRING];
	int recv;

	for (;;) {
		if (xQueueReceive(recv_queue, &recv, -1)) {
			snprintf(buffer, -1, data->msg, get_current_cpuid(), recv);
			test_ca73_printf(buffer);
			recv++;
			xQueueSend(send_queue, &recv, -1);
			if (recv > TEST_CA73_MAX_STRING) {
				vTaskSuspend(NULL);
			}
		}
	}
}

static struct test_ca73_task_config test_ca73_task_config_affinity_x[TEST_CA73_MAX_TASK] = {
	{test_ca73_uart_task, "test_ca73_uart_task0", {NULL, NULL, "[%ld] Affinity X task0\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task1", {NULL, NULL, "[%ld] Affinity X task1\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task2", {NULL, NULL, "[%ld] Affinity X task2\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task3", {NULL, NULL, "[%ld] Affinity X task3\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task4", {NULL, NULL, "[%ld] Affinity X task4\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task5", {NULL, NULL, "[%ld] Affinity X task5\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task6", {NULL, NULL, "[%ld] Affinity X task6\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task7", {NULL, NULL, "[%ld] Affinity X task7\n"},},
};

static struct test_ca73_task_config test_ca73_task_config_affinity_o[TEST_CA73_MAX_TASK] = {
	{test_ca73_uart_task, "test_ca73_uart_task0", {NULL, NULL, "[%ld] Affinity O task0\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task1", {NULL, NULL, "[%ld] Affinity O task1\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task2", {NULL, NULL, "[%ld] Affinity O task2\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task3", {NULL, NULL, "[%ld] Affinity O task3\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task4", {NULL, NULL, "[%ld] Affinity O task4\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task5", {NULL, NULL, "[%ld] Affinity O task5\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task6", {NULL, NULL, "[%ld] Affinity O task6\n"},},
	{test_ca73_uart_task, "test_ca73_uart_task7", {NULL, NULL, "[%ld] Affinity O task7\n"},},
};

static uint32_t test_ca73_shared_data;

static struct test_ca73_task_config test_ca73_task_config_access[TEST_CA73_MAX_TASK] = {
	{
		test_ca73_access_task,
		"test_ca73_access_task0",
		{&test_ca73_shared_data, NULL, "[%ld] %d task0\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task1",
		{&test_ca73_shared_data, NULL, "[%ld] %d task1\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task2",
		{&test_ca73_shared_data, NULL, "[%ld] %d task2\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task3",
		{&test_ca73_shared_data, NULL, "[%ld] %d task3\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task4",
		{&test_ca73_shared_data, NULL, "[%ld] %d task4\n"}
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task5",
		{&test_ca73_shared_data, NULL, "[%ld] %d task5\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task6",
		{&test_ca73_shared_data, NULL, "[%ld] %d task6\n"},
	},
	{
		test_ca73_access_task,
		"test_ca73_access_task7",
		{&test_ca73_shared_data, NULL, "[%ld] %d task7\n"},
	},
};

static QueueHandle_t test_ca73_queue[TEST_CA73_MAX_TASK];

static struct test_ca73_task_config __attribute__((unused))
test_ca73_task_config_transfer[TEST_CA73_MAX_TASK] = {
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer0",
		{&test_ca73_queue[0], &test_ca73_queue[1], "[%ld] %d Received task0\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer1",
		{&test_ca73_queue[1], &test_ca73_queue[2], "[%ld] %d Received task1\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer2",
		{&test_ca73_queue[2], &test_ca73_queue[3], "[%ld] %d Received task2\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer3",
		{&test_ca73_queue[3], &test_ca73_queue[4], "[%ld] %d Received task3\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer4",
		{&test_ca73_queue[4], &test_ca73_queue[5], "[%ld] %d Received task4\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer5",
		{&test_ca73_queue[5], &test_ca73_queue[6], "[%ld] %d Received task5\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer6",
		{&test_ca73_queue[6], &test_ca73_queue[7], "[%ld] %d Received task6\n"},
	},
	{
		test_ca73_data_transfer,
		"test_ca73_data_transfer7",
		{&test_ca73_queue[7], &test_ca73_queue[0], "[%ld] %d Received task7\n"},
	},
};
