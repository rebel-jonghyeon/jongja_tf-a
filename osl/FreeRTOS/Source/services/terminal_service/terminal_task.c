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

#include "terminal_task.h"
#include "cli_task.h"
#include "stream_buffer.h"
// #include "rl_errors.h"
// #include "rl_utils.h"
#include "assert.h"

#include "event_groups.h"
#include "console.h"
#include "printf.h"
#include <stdarg.h>

#define RLOG_ERR printf

#define TX_EVENT  (1 << 0)

#define BUF_SIZE   (16 * 1024)

static TaskHandle_t task_handle;
static StreamBufferHandle_t tx_buf;
static EventGroupHandle_t event_handle;
static uint8_t initialized;

void terminal_rx_handler(uint8_t *buf, uint32_t cnt)
{
	cli_enqueue(buf, cnt);
}

void terminal_init(TaskHandle_t handle)
{
	task_handle = handle;

	tx_buf = xStreamBufferCreate(BUF_SIZE, 1);
	event_handle = xEventGroupCreate();

	console_register_rx_handler(terminal_rx_handler);

	initialized = true;
}

void terminal_task(void *param)
{
	EventBits_t events;
	char data;

	if (!initialized)
		return;

	while (1) {
		events = xEventGroupWaitBits(event_handle, TX_EVENT, pdTRUE, pdFALSE,
			portMAX_DELAY);

		if ((events & TX_EVENT) != 0) {
			while (xStreamBufferReceive(tx_buf, &data, 1, 0) == 1) {
				console_putc(data);
			}
			console_flush();
		} else {
			// printf("--events=%x\n", (unsigned int)events);
		}
	}
}

int terminal_tx_bytes(char *buf, size_t dest_str_length)
{
	size_t ret;

	if (tx_buf == NULL) {
		console_assert_print(buf, dest_str_length);
		return dest_str_length;
	}

	if (xStreamBufferSpacesAvailable(tx_buf) < dest_str_length) {
		return 0;
	}

	if (xPortIsInsideInterrupt())
		ret = xStreamBufferSendFromISR(tx_buf, (void *)buf, dest_str_length, NULL);
	else {
		portENTER_CRITICAL();
		ret = xStreamBufferSend(tx_buf, (void *)buf, dest_str_length, 0);
		portEXIT_CRITICAL();
	}

	if (ret != dest_str_length)
		return 0;

	if (xPortIsInsideInterrupt()) {
		configASSERT(xEventGroupSetBitsFromISR(event_handle, TX_EVENT, NULL) == pdTRUE);
	} else
		xEventGroupSetBits(event_handle, TX_EVENT);

	return dest_str_length;
}

int terminal_tx_byte(int c)
{
	size_t ret;

	if (xPortIsInsideInterrupt())
		ret = xStreamBufferSendFromISR(tx_buf, (void *)&c, 1, NULL);
	else {
		portENTER_CRITICAL();
		ret = xStreamBufferSend(tx_buf, (void *)&c, 1, 0);
		portEXIT_CRITICAL();
	}
	if (ret != 1)
		return 0;

	if (xPortIsInsideInterrupt()) {
		configASSERT(xEventGroupSetBitsFromISR(event_handle, TX_EVENT, NULL) == pdTRUE);
	} else
		xEventGroupSetBits(event_handle, TX_EVENT);

	return 1;
}

int terminal_printf(const char *format, ...)
{
	va_list args;
	size_t len;

	char buf[PRINTF_MAX_SIZE] = {
	    0,
	};

	va_start(args, format);
	len = vsnprintf(buf, PRINTF_MAX_SIZE, format, args);
	va_end(args);

	while (!terminal_tx_bytes(buf, len+1)) {
		// tx_buf full
		if (!xPortIsInsideInterrupt()) {
			// Wait for tx_buf to be dequeued
			vTaskDelay(pdMS_TO_TICKS(1));
		} else {
			// no way to handle the buffer full in ISR
			// RLOG_ERR("%s: tx_buf full in isr, dropping the output.\r\n", __func__);
			break;
		}
	}

	return 0;
}

int terminal_print_buf(const uint8_t *buf, size_t len)
{
	while (!terminal_tx_bytes((char *)buf, len)) {
		// tx_buf full
		if (!xPortIsInsideInterrupt()) {
			// Wait for tx_buf to be dequeued
			vTaskDelay(pdMS_TO_TICKS(1));
		} else {
			// no way to handle the buffer full in ISR
			// RLOG_ERR("%s: tx_buf full in isr, dropping the output.\r\n", __func__);
			break;
		}
	}

	return 0;
}
