/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2026 [Rebellions Inc.], All Rights Reserved.
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "rbln/memory.h"
#include "terminal_task.h"

#include "rush_cli_msg_buf.h"

#define LOG_SHELL terminal_printf

int rush_cli_msg_buf_init(struct rush_cli_msg_buf *msg_buf, const size_t size)
{
	msg_buf->data = rl_malloc(size);
	if (msg_buf->data == NULL)
		return -ENOMEM;

	msg_buf->size = size - 1;
	msg_buf->data[size - 1] = '\0';
	msg_buf->pos = 0;

	msg_buf->is_full = false;

	return 0;
}

void rush_cli_msg_buf_deinit(struct rush_cli_msg_buf *msg_buf)
{
	if (msg_buf == NULL)
		return;

	if (msg_buf->data) {
		rl_free(msg_buf->data);
		msg_buf->data = NULL;
		msg_buf->size = 0;
		msg_buf->pos = 0;
	}
}

int rush_cli_msg_buf_sprintf(struct rush_cli_msg_buf *msg_buf, const char *format, ...)
{
	int n;
	size_t remaining;
	va_list args;

	if (msg_buf == NULL)
		return -ENOENT;

	if (msg_buf->pos >= msg_buf->size)
		return -ENOMEM;

	if (msg_buf->is_full)
		return -ENOBUFS;

	remaining = msg_buf->size - msg_buf->pos;
	va_start(args, format);
	n = vsnprintf(msg_buf->data + msg_buf->pos, remaining, format, args);
	va_end(args);

	if (n < 0) {
		LOG_SHELL("rush cli msg_buf vsnprintf error: %d\r\n", n);
		return n;
	}

	if ((size_t)n >= remaining) {
		sprintf(msg_buf->data, "rush cli msg_buf overflow, required: %d, remaining: %zu\r\n",
				n, remaining);
		msg_buf->is_full = true;
		return -ENOBUFS;
	}

	msg_buf->pos += n;

	return 0;
}

void rush_cli_msg_buf_flush(struct rush_cli_msg_buf *msg_buf)
{
	if (msg_buf == NULL)
		return;

	if (msg_buf->pos) {
		msg_buf->data[msg_buf->pos] = '\0';

		terminal_print_buf((const uint8_t *)msg_buf->data, msg_buf->pos);
	}
}
