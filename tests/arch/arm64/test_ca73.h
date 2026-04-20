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

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <uart.h>
#include <printf.h>

/* UART for SMP */
#if defined(ZEBU)
#define TARGET_BAUD_RATE	(7812500)
#else
#define TARGET_BAUD_RATE	(115200)
#endif

#define TEST_CA73_MAX_STRING	(100)
#define TEST_CA73_MAX_PRINTF	(30)
#define TEST_CA73_MAX_TASK		(8)

struct test_ca73_data {
	void *data0;
	void *data1;
	char msg[TEST_CA73_MAX_STRING];
};

struct test_ca73_task_config {
	void					(*task)(void *param);
	char					name[TEST_CA73_MAX_STRING];
	struct test_ca73_data	data;
};

static void test_ca73_printf(char *s);

static inline void test_ca73_create_tasks(TaskHandle_t handle[],
										  struct test_ca73_task_config config[])
{
	for (uint32_t i = 0; i < TEST_CA73_MAX_TASK; ++i) {
		xTaskCreate(config[i].task, config[i].name, configMINIMAL_STACK_SIZE,
					&config[i].data, 1, &handle[i]);
	}
}

static inline void test_ca73_set_affinity(TaskHandle_t handle[])
{
	for (uint32_t i = 0; i < TEST_CA73_MAX_TASK; ++i) {
		vTaskCoreAffinitySet(handle[i], 1U << (i & 0b11));
	}
}

static inline void test_ca73_create_queue(QueueHandle_t test_ca73_queue[], uint32_t queue_num)
{
	for (uint32_t i = 0; i < queue_num; ++i) {
		test_ca73_queue[i] = xQueueCreate(1, sizeof(int));
	}
}

static inline void test_ca73_suspend_tasks(TaskHandle_t handle[])
{
	for (uint32_t i = 0; i < TEST_CA73_MAX_TASK; ++i) {
		vTaskSuspend(handle[i]);
	}
}

static inline void test_ca73_delete_tasks(TaskHandle_t handle[])
{
	for (uint32_t i = 0; i < TEST_CA73_MAX_TASK; ++i) {
		vTaskDelete(handle[i]);
	}
}
