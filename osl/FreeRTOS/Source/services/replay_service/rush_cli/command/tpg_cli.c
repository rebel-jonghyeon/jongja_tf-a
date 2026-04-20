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

#define TPG_SIZE_MAX				UINT32_MAX	/* 4GB */
#define TPG_BURST_DATA_ACCESS_SIZE	128			/* Depend on SHM bus size */
#define TPG_MAX_REPEAT_LEN			1024

struct tpg_cli_fill_opt {
	uint64_t addr;
	uint32_t size;

	uint32_t p[2];
	uint32_t p_cnt;
	uint32_t repeat_len;
};

static int tpg_cli_size_cb_func(struct argparse *self, const struct argparse_option *option,
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

	if (val > TPG_SIZE_MAX) {
		RUSH_CLI_MSG(self->msg_buf, "Max supported size is 4GB\r\n");
		return -EINVAL;
	}

	*(uint32_t *)ctx = val;

	return 0;
}

static int tpg_cli_fill_rand_cmd(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int ret;
	uint64_t addr = 0;
	uint32_t size = 0;
	const char *arg_str;
	enum memory_type mem_type;
	struct argparse argparse;
	static const char *const usage[] = {
		"rand [args]",
		NULL
	};
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_LONG('a', "addr", &addr, "start address to make random pattern data"),
		OPT_STRING('s', "size", &arg_str, "total size of random pattern data "
				   "(size - num[k/K/m/M/g/G], e.g, 64M, Max: 4G)",
				   tpg_cli_size_cb_func, &size),
		OPT_END(),
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	argc = argparse_parse(&argparse, argc, argv);
	if (argc < 0)
		return 0;

	if (!addr || !size)
		return -EINVAL;

	mem_type = rush_cli_chk_memory_type(addr);
	ret = rush_cli_validate_addr_size(mem_type, addr, size);
	if (ret < 0) {
		RUSH_CLI_MSG(msg_buf, "invalid addr or size\r\n");
		return ret;
	}

	rand_fill((void *)addr, size);

	return 0;
}

static int tpg_cli_fill_value_cb_func(struct argparse *self, const struct argparse_option *option,
									  void *ctx, int flags)
{
	uint32_t val;
	char *buf = *(char **)option->value;
	struct tpg_cli_fill_opt *opt = ctx;
	char *endptr;

	errno = 0;
	val = strtoul(buf, &endptr, 16);
	if (errno || endptr == buf || val > 0xFF) {
		RUSH_CLI_MSG(self->msg_buf, "invalid fill pattern value\n");
		return -EINVAL;
	}

	opt->p[opt->p_cnt] = val;
	opt->p_cnt++;

	return 0;
}

static void tpg_cli_fill_chunk_data(void *addr, uint32_t size,
									uint32_t burst_size, uint8_t data)
{
	uint32_t len;
	uint32_t written = 0;
	uint8_t *ptr = (uint8_t *)addr;

	while (written < size) {
		len = ((size - written) > burst_size) ? burst_size : size - written;
		memset(ptr + written, data, len);

		written += len;
	}
}

static int tpg_cli_fill_pattern_cmd(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int ret;
	uint8_t val;
	uint32_t i;
	struct tpg_cli_fill_opt opt = {0, };
	enum memory_type mem_type;
	const char *arg_str;
	struct argparse argparse;
	static const char *const usage[] = {
		"fill [args]",
		" - fill same value into whole data chunk",
		"  $ fill --addr <address> --size <size> --p1 <value>",
		" - fill two different values with length into data chunk",
		"  $ fill --addr <address> --size <size> --p1 <value> --p2 <value> --repeat <length>",
		NULL
	};
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_LONG('a', "addr", &opt.addr, "start address to make pattern data"),
		OPT_STRING('s', "size", &arg_str, "total size of pattern data "
				   "(size: num[k/K/m/M/g/G], e.g, 64M, Max: 4G)",
				   tpg_cli_size_cb_func, &opt.size),
		OPT_STRING('\0', "p1", &arg_str, "fill pattern with value, 0x00~0xFF",
				   tpg_cli_fill_value_cb_func, &opt),
		OPT_STRING('\0', "p2", &arg_str, "fill pattern with value, 0x00~0xFF",
				   tpg_cli_fill_value_cb_func, &opt),
		OPT_INTEGER('r', "repeat", &opt.repeat_len, "repeat length of p1 and p2 (max: 1024)"),
		OPT_END(),
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	ret = argparse_parse(&argparse, argc, argv);
	if (ret < 0)
		return 0;

	if (!opt.addr || !opt.size || !opt.p_cnt)
		return -EINVAL;

	mem_type = rush_cli_chk_memory_type(opt.addr);

	ret = rush_cli_validate_addr_size(mem_type, opt.addr, opt.size);
	if (ret < 0) {
		RUSH_CLI_MSG(msg_buf, "invalid addr or size\r\n");
		return ret;
	}

	switch (opt.p_cnt) {
	case 1:
		if (mem_type == DRAM)
			memset((void *)opt.addr, opt.p[0], opt.size);
		else
			tpg_cli_fill_chunk_data((void *)opt.addr, opt.size,
									TPG_BURST_DATA_ACCESS_SIZE, opt.p[0]);
		break;
	case 2:
		if (opt.repeat_len == 0) {
			RUSH_CLI_MSG(msg_buf, "repeat length is required!\r\n");
			return -EINVAL;
		}

		if (opt.repeat_len > TPG_MAX_REPEAT_LEN || opt.repeat_len > opt.size) {
			RUSH_CLI_MSG(msg_buf, "invalid repeat length!\r\n");
			return -EINVAL;
		}

		uint32_t chunk_num = opt.size / opt.repeat_len;
		uint32_t remainder = opt.size % opt.repeat_len;

		for (i = 0; i < chunk_num; i++) {
			val = i & 0x01 ? opt.p[1] : opt.p[0];
			if (mem_type == DRAM)
				memset((void *)opt.addr + i * opt.repeat_len, val, opt.repeat_len);
			else
				tpg_cli_fill_chunk_data((void *)opt.addr + i * opt.repeat_len, opt.repeat_len,
										TPG_BURST_DATA_ACCESS_SIZE, val);
		}

		if (remainder) {
			val = i & 0x01 ? opt.p[1] : opt.p[0];
			if (mem_type == DRAM)
				memset((void *)opt.addr + i * opt.repeat_len, val, remainder);
			else
				tpg_cli_fill_chunk_data((void *)opt.addr + i * opt.repeat_len, remainder,
										TPG_BURST_DATA_ACCESS_SIZE, val);
		}

		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static struct rush_cli_sub_cmd tpg_cmd_tbl[] = {
	{"fill", "fill pattern data with values", tpg_cli_fill_pattern_cmd},
	{"rand", "fill random data", tpg_cli_fill_rand_cmd},
};

int tpg_cli(int argc, const char **argv, const size_t msg_buf_size)
{
	int ret;
	struct rush_cli_msg_buf msg_buf;
	static const char *const usage[] = {
		"tpg {command} [args]",
		NULL,
	};

	if (msg_buf_size) {
		ret = rush_cli_msg_buf_init(&msg_buf, msg_buf_size);
		if (ret < 0)
			return ret;
	}

	ret = rush_cli_cmd_proc(argc, argv, "Traffic Pattern Generator(TPG) Operation", usage,
							tpg_cmd_tbl, ARRAY_SIZE(tpg_cmd_tbl),
							msg_buf_size ? &msg_buf : NULL);

	if (msg_buf_size) {
		if (msg_buf.pos)
			rush_cli_msg_buf_flush(&msg_buf);
		rush_cli_msg_buf_deinit(&msg_buf);
	}

	return ret;
}

int tpg_cli_init(void)
{
	return 0;
}
