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

#include "argparse.h"

#include "rl_utils.h"
#include "rush_cli_util.h"
#include "rush_cli.h"

static int rush_cli_list(int argc, const char **argv, const size_t msg_buf_size);

static struct rush_cli_cmd rush_cmd_tbl[] = {
	{"list", "List all rush commands", rush_cli_list, SIZE_KiB(4)},
	{"tpg", "Test Pattern Generation", tpg_cli, SIZE_KiB(4)},
	{"rbdma", "RBDMA Test commands", rbdma_cli, SIZE_KiB(4)},
	{"mem", "Read/Write Memory/Register commands", mem_cli, SIZE_KiB(8)},
};

static void rush_cli_print_cmd(struct rush_cli_cmd *cmd, uint32_t num,
							   struct rush_cli_msg_buf *msg_buf)
{
	uint32_t i;

	for (i = 0; i < num; i++)
		RUSH_CLI_MSG(msg_buf, "%10s: %s\r\n", cmd[i].name, cmd[i].desc);
}

static void rush_cli_print_sub_cmd(struct rush_cli_sub_cmd *cmd, uint32_t num,
								   struct rush_cli_msg_buf *msg_buf)
{
	uint32_t i;

	for (i = 0; i < num; i++)
		RUSH_CLI_MSG(msg_buf, "%10s: %s\r\n", cmd[i].name, cmd[i].desc);
}

static int rush_cli_list(int argc, const char **argv, const size_t msg_buf_size)
{
	struct rush_cli_msg_buf msg_buf;

	if (msg_buf_size)
		rush_cli_msg_buf_init(&msg_buf, msg_buf_size);

	rush_cli_print_cmd(rush_cmd_tbl, ARRAY_SIZE(rush_cmd_tbl), msg_buf_size ? &msg_buf : NULL);

	if (msg_buf_size) {
		if (msg_buf.pos)
			rush_cli_msg_buf_flush(&msg_buf);
		rush_cli_msg_buf_deinit(&msg_buf);
	}

	return 0;
}

static const char help_rush_cli[] = "[rush]\r\n"
" * RUSH cli command\r\n"
" *  rush {list|command name} [options]\r\n"
" *   use list to know rush command \r\n"
" *   $ rush list\r\n"
"\r\n";

static uint8_t rush_cli(int argc, char *argv[])
{
	uint32_t i;

	if (!argc)
		return false;

	for (i = 0; i < ARRAY_SIZE(rush_cmd_tbl); i++) {
		if (!strcmp(rush_cmd_tbl[i].name, argv[0])) {
			rush_cmd_tbl[i].func(argc, (const char **)argv, rush_cmd_tbl[i].buf_size);
			break;
		}
	}

	if (i >= ARRAY_SIZE(rush_cmd_tbl))
		return false;

	return true;
}

int rush_cli_cmd_proc(int argc, const char **argv,
					  const char *description, const char *const *usage,
					  struct rush_cli_sub_cmd *cmd_tbl, uint32_t total_cmd_num,
					  struct rush_cli_msg_buf *msg_buf)
{
	uint32_t i;
	struct argparse argparse;
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_END()
	};
	struct rush_cli_sub_cmd *cmd = NULL;

	argparse_init(&argparse, options, usage, ARGPARSE_STOP_AT_NON_OPTION, msg_buf);
	argparse_describe(&argparse, description, NULL);
	argc = argparse_parse(&argparse, argc, argv);
	if (argc < 1) {
		rush_cli_print_sub_cmd(cmd_tbl, total_cmd_num, msg_buf);
		return -EINVAL;
	}

	for (i = 0; i < total_cmd_num; i++) {
		if (!strcmp(cmd_tbl[i].name, argv[0])) {
			cmd = &cmd_tbl[i];
			break;
		}
	}

	if (cmd == NULL)
		return -ENOTSUP;

	return cmd->func(argc, argv, msg_buf);
}

/*
 * This function is intended to be called from the replay service
 * initialization path so that all rush_cli components are properly
 * initialized and retained by the linker.
 */
int rush_cli_init(void)
{
	tpg_cli_init();
	rbdma_cli_init();
	mem_cli_init();

	return 0;
}

CLI_REGISTER(rush, NULL, rush_cli, help_rush_cli);
