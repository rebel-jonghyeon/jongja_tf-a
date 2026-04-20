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

#include "cli_task.h"
#include "console_uart.h"
#include "uart.h"

#define RX_BUF_SIZE		(UART_BUFFER_SIZE)

struct console uart = {
	.name = "uart",
	.putc = console_uart_putc,
	.assert_putc = console_uart_putc,
	.rx_handler = NULL,
	.flush = NULL,
	.enabled = 0
};

char test_uart_ptr[RX_BUF_SIZE];
char saved_uart_ptr[RX_BUF_SIZE];

static void console_uart_rx_callback(void *ptr)
{
	// Handle UART RX and call uart.rx_handler to convey to CLI
	for (int i = 0; (i < RX_BUF_SIZE) && (test_uart_ptr[i] != 0); i++) {
		saved_uart_ptr[i] = test_uart_ptr[i];
		cli_enqueue((uint8_t *)(test_uart_ptr + i), 1);
	}
}

static void console_uart_tx_callback(void *ptr)
{
}

void console_uart_init(void)
{
	// Init UART HW and register the console
	uart_int_config();
	console_uart_enable();

	uart_register_rx_callback(console_uart_rx_callback, test_uart_ptr);
	uart_register_tx_callback(console_uart_tx_callback, saved_uart_ptr);

	console_dev_register(&uart);
}

void console_uart_enable(void)
{
	// Enable UART console
	uart.enabled = 1;
}

uint8_t console_uart_putc(int c)
{
	// Output to UART console
	uart_putc(c);
	return 0;
}

