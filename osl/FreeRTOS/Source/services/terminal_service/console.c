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

#include "console.h"
// #include "dbglog.h"
#include <string.h>
#include <sys_command_line.h>
#include <terminal_task.h>
#include <assert.h>

#define LOG_SHELL terminal_printf

#define MAX_CONSOLE_DEVICES 5

static struct console *consoles[MAX_CONSOLE_DEVICES];
static uint32_t num_consoles;

void console_dev_register(struct console *console)
{
	configASSERT(num_consoles < MAX_CONSOLE_DEVICES);

	consoles[num_consoles++] = console;
}

void console_putc(int data)
{
	uint32_t i;
	struct console *ptr;

	for (i = 0; i < num_consoles; i++) {
		ptr = consoles[i];
		if (ptr->enabled)
			ptr->putc(data);
	}
}

void console_flush(void)
{
	uint32_t i;
	struct console *ptr;

	for (i = 0; i < num_consoles; i++) {
		ptr = consoles[i];
		if (ptr->flush && ptr->enabled)
			ptr->flush();
	}
}

static void console_assert_putc(int data)
{
	uint32_t i;
	struct console *ptr;

	for (i = 0; i < num_consoles; i++) {
		ptr = consoles[i];
		if (ptr->assert_putc && ptr->enabled)
			ptr->assert_putc(data);
	}
}

void console_assert_print(char *buf, size_t dest_str_length)
{
	uint8_t buf_idx = 0;

	for (buf_idx = 0; buf_idx < dest_str_length; buf_idx++)
		console_assert_putc(buf[buf_idx]);
}

void console_register_rx_handler(void (*rx_handler)(uint8_t *buf, uint32_t cnt))
{
	uint32_t i;
	struct console *ptr;

	for (i = 0; i < num_consoles; i++) {
		ptr = consoles[i];
		ptr->rx_handler = rx_handler;
	}
}

static const char help_console[] =
	"[console list]\r\n"
	" * list console devices\r\n"
	"\r\n"
	"[console {device name} on|off]\r\n"
	" * Turn on/off the console\r\n"
	"\r\n";

static uint8_t control_console(int argc, char *argv[])
{
	uint8_t ret = false;
	// uint32_t i;
	unsigned int i;
	struct console *ptr;

	if (argc == 0) {
		;
	} else if (argc == 1) {
		if (strcmp(argv[0], "list") == 0) {
			LOG_SHELL("   %10s %10s\r\n", "[console]", "[on|off]");
			for (i = 0; i < num_consoles; i++) {
				ptr = consoles[i];
				LOG_SHELL("%2u %10s %10s\r\n", i, ptr->name, ptr->enabled ? "on" : "off");
			}
			ret = true;
		}
	} else if (argc == 2) {
		for (i = 0; i < num_consoles; i++) {
			ptr = consoles[i];
			if (strcmp(argv[0], ptr->name) == 0) {
				if (strcmp(argv[1], "on") == 0) {
					LOG_SHELL("%s console enabled\r\n", ptr->name);
					ptr->enabled = 1;
					ret = true;
				} else if (strcmp(argv[1], "off") == 0) {
					LOG_SHELL("%s console disabled\r\n", ptr->name);
					ptr->enabled = 0;
					ret = true;
				}
			}
		}
		if (!ret)
			LOG_SHELL("arguemnt is not correct:%s\r\n", argv[0]);
	} else {
		ret = false;
	}

	LOG_SHELL("\r\n");

	return ret;
}

CLI_REGISTER(console, NULL, control_console, help_console);
