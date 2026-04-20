/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2023 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include "sys_command_line.h"
#include "cli_task.h"
#include "queue.h"
#include "terminal_task.h"

#define CLI_QUEUE_LEN 1024

static QueueHandle_t cli_queue;

void cli_task_init(TaskHandle_t handle)
{
	cli_init(terminal_printf, terminal_tx_byte);

	cli_queue = xQueueCreate(CLI_QUEUE_LEN, sizeof(char));
	configASSERT(cli_queue != NULL);

	if (cli_queue == NULL)
		return;
}

void cli_task(void *pvParameters)
{
	(void)pvParameters;
	char data;
	BaseType_t ret = pdFAIL;

	while (1) {
		do {
			ret = xQueueReceive(cli_queue, &data, portMAX_DELAY);
			if (ret == pdPASS)
				cli_run(data);
		} while (ret == pdPASS);
	}
}

static void cli_enqueue_char(char c)
{
	BaseType_t ret;

	if (cli_queue) {
		if (!xPortIsInsideInterrupt()) {
			portENTER_CRITICAL();
			ret = xQueueSend(cli_queue, &c, 0U);
			portEXIT_CRITICAL();
		} else {
			ret = xQueueSendFromISR(cli_queue, (void *)&c, 0);
		}
		configASSERT(ret == pdPASS);
	}
}

void cli_enqueue(uint8_t *buf, uint32_t cnt)
{
	uint32_t i;

	for (i = 0; i < cnt; i++) {
		cli_enqueue_char(buf[i]);
	}
}
