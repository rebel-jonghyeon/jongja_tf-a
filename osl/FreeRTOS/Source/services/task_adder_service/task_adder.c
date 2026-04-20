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

#include "FreeRTOS.h"
#include "task.h"
 
#include "task_adder.h"
#include "queue.h"
#include <stdio.h>

#define TASK_ADDER_QUEUE_LEN	(128)

static QueueHandle_t task_adder_queue;
static TaskHandle_t task_adder_handle;

void task_adder_init(TaskHandle_t handle)
{
	task_adder_handle = handle;
	task_adder_queue = xQueueCreate(TASK_ADDER_QUEUE_LEN, sizeof(struct task_info));
	configASSERT(task_adder_queue != NULL);
}

void task_adder_task(void *arg)
{
	struct task_info info = {};
	BaseType_t ret = pdFAIL;

	while (1) {
		ret = xQueueReceive(task_adder_queue, &info, portMAX_DELAY);
		if (ret == pdPASS) {
#if configUSE_CORE_AFFINITY
			ret = xTaskCreateAffinitySet(info.func, info.task_name, info.stack_depth,
							  info.param, info.priority, info.affinity, info.handle);
#else
			ret = xTaskCreateAffinitySet(info.func, info.task_name, info.stack_depth,
							  info.param, info.priority, info.affinity, info.handle);
#endif
			configASSERT(ret == pdPASS);
		}
	}
}

void task_adder_enqueue(struct task_info *task_info)
{
	BaseType_t ret = pdFAIL;

	if (task_adder_queue) {
		if (!xPortIsInsideInterrupt()) {
			portENTER_CRITICAL();
			ret = xQueueSend(task_adder_queue, task_info, 0U);
			portEXIT_CRITICAL();
		} else {
			ret = xQueueSendFromISR(task_adder_queue, (void *)task_info, 0);
		}
		configASSERT(ret == pdPASS);
	}
}
