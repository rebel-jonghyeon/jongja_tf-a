/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common_test.h"

#include "rl_utils.h"
#include "argparse.h"

#include "rush_cli_util.h"
#include "rush_cli_msg_buf.h"
#include "rush_cli.h"

#define MEM_CLI_READ_COUNT_MAX	128
#define MEM_CLI_DUMP_SIZE_MAX	SIZE_KiB(4)

static int mem_cli_rd(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int ret;
	uint32_t i;
	uint64_t addr = UINT64_MAX;
	uint32_t count = 1;
	struct argparse argparse;
	static const char *const usage[] = {
		"rd [args]",
		" - read memory/register, 32-bit words",
		"  $ rd --addr <address> --count <count>",
		NULL
	};
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_LONG('a', "addr", &addr, "address to read"),
		OPT_INTEGER('c', "count", &count, "read count number, max = 128"),
		OPT_END(),
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	ret = argparse_parse(&argparse, argc, argv);
	if (ret < 0)
		return 0;

	if (addr == UINT64_MAX || count > MEM_CLI_READ_COUNT_MAX) {
		RUSH_CLI_MSG(msg_buf, "invalid argument\r\n");
		return -EINVAL;
	}

	uint32_t *p = (uint32_t *)(uintptr_t)addr;

	for (i = 0; i < count; i++) {
		if (i % 4 == 0)
			RUSH_CLI_MSG(msg_buf, "0x%016lx: ", (uintptr_t)&p[i]);
		RUSH_CLI_MSG(msg_buf, "%08x ", rl_readl_relaxed((void __iomem *)&p[i]));
		if ((i + 1) % 4 == 0 || i + 1 == count)
			RUSH_CLI_MSG(msg_buf, "\r\n");
	}

	return 0;
}

static int mem_cli_wr(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int ret;
	uint64_t addr = UINT64_MAX;
	uint32_t value = 0;
	struct argparse argparse;
	static const char *const usage[] = {
		"wr [args]",
		" - write memory/register, 32-bit words",
		"  $ wr --addr <address> --val <value>",
		NULL
	};
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_LONG('a', "addr", &addr, "address to write"),
		OPT_INTEGER('v', "val", &value, "value"),
		OPT_END(),
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	ret = argparse_parse(&argparse, argc, argv);
	if (ret < 0)
		return 0;

	if (addr == UINT64_MAX) {
		RUSH_CLI_MSG(msg_buf, "invalid argument\r\n");
		return -EINVAL;
	}

	rl_writel(value, (void * __iomem)addr);

	return 0;
}

static int mem_cli_dump_size_cb_func(struct argparse *self, const struct argparse_option *option,
									 void *ctx, int flags)
{
	int ret;
	char *buf;
	uint64_t val;

	buf = *(char **)option->value;
	ret = rush_cli_parse_size(buf, &val);
	if (ret) {
		RUSH_CLI_MSG(self->msg_buf, "failed to parse size\r\n");
		return -EINVAL;
	}

	*(uint32_t *)ctx = (uint32_t)val;

	return 0;
}

static void mem_cli_dump_print_hex(struct rush_cli_msg_buf *msg_buf,
								   const void *ptr, uint32_t size)
{
	size_t i, j;
	char ascii[17];

	ascii[16] = '\0';
	for (i = 0; i < size; i++) {
		RUSH_CLI_MSG(msg_buf, "%02X ", ((const unsigned char *)ptr)[i]);
		if (((const unsigned char *)ptr)[i] >= ' ' &&
				((const unsigned char *)ptr)[i] <= '~')
			ascii[i % 16] = ((const unsigned char *)ptr)[i];
		else
			ascii[i % 16] = '.';

		if (((i + 1) % 8) == 0 || ((i + 1) == size)) {
			RUSH_CLI_MSG(msg_buf, " ");
			if (((i + 1) % 16) == 0) {
				RUSH_CLI_MSG(msg_buf, "|  %s\r\n", ascii);
			} else if (i + 1 == size) {
				ascii[(i + 1) % 16] = '\0';
				if (((i + 1) % 16) <= 8)
					RUSH_CLI_MSG(msg_buf, " ");

				for (j = (i + 1) % 16; j < 16; j++)
					RUSH_CLI_MSG(msg_buf, "   ");

				RUSH_CLI_MSG(msg_buf, "|  %s\r\n", ascii);
			}
		}
	}
}

static int mem_cli_dump(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int ret;
	uint64_t addr = UINT64_MAX;
	uint32_t size = 0;
	struct argparse argparse;
	const char *arg_str;
	static const char *const usage[] = {
		"dump [args]",
		" - dump memory/register",
		"  $ dump --addr <address> --size <size>",
		NULL
	};
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_LONG('a', "addr", &addr, "address to dump"),
		OPT_STRING('s', "size", &arg_str, "dump size (size - num[k/K], e.g, 1K, Max: 4K)",
				   mem_cli_dump_size_cb_func, &size),
		OPT_END(),
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	ret = argparse_parse(&argparse, argc, argv);
	if (ret < 0)
		return 0;

	if (addr == UINT64_MAX || size == 0 || size > MEM_CLI_DUMP_SIZE_MAX) {
		RUSH_CLI_MSG(msg_buf, "invalid argument\r\n");
		return -EINVAL;
	}

	mem_cli_dump_print_hex(msg_buf, (void __iomem *)addr, size);

	return 0;
}

static struct rush_cli_sub_cmd mem_cmd_tbl[] = {
	{"rd", "read memory/register", mem_cli_rd},
	{"wr", "write memory/register", mem_cli_wr},
	{"dump", "dump memory", mem_cli_dump},
};

int mem_cli(int argc, const char **argv, const size_t msg_buf_size)
{
	int ret;
	struct rush_cli_msg_buf msg_buf;
	static const char *const usage[] = {
		"mem {command} [args]",
		NULL,
	};

	if (msg_buf_size) {
		ret = rush_cli_msg_buf_init(&msg_buf, msg_buf_size);
		if (ret < 0)
			return ret;
	}

	ret = rush_cli_cmd_proc(argc, argv, "Memory/Register Operation", usage,
							mem_cmd_tbl, ARRAY_SIZE(mem_cmd_tbl),
							msg_buf_size ? &msg_buf : NULL);

	if (msg_buf_size) {
		if (msg_buf.pos)
			rush_cli_msg_buf_flush(&msg_buf);
		rush_cli_msg_buf_deinit(&msg_buf);
	}

	return ret;
}

int mem_cli_init(void)
{
	return 0;
}
