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

#ifndef _RUSH_CLI_H
#define _RUSH_CLI_H

#include "rush_cli_msg_buf.h"

typedef int (*rush_cli_func_t)(int argc, const char **argv, const size_t msg_buf_size);

struct rush_cli_cmd {
	const char *name;
	const char *desc;

	rush_cli_func_t func;
	size_t buf_size;
};

typedef int (*rush_cli_sub_func_t)(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf);

struct rush_cli_sub_cmd {
	const char *name;
	const char *desc;

	rush_cli_sub_func_t func;
};

int rush_cli_init(void);

/* RUSH cli command */
int rush_cli_cmd_proc(int argc, const char **argv,
					  const char *description, const char *const *usage,
					  struct rush_cli_sub_cmd *cmd_tbl, uint32_t cmd_tbl_num,
					  struct rush_cli_msg_buf *msg_buf);

int tpg_cli_init(void);
int rbdma_cli_init(void);
int mem_cli_init(void);

int tpg_cli(int argc, const char **argv, const size_t buf_size);
int rbdma_cli(int argc, const char **argv, const size_t buf_size);
int mem_cli(int argc, const char **argv, const size_t buf_size);

#endif /* _RUSH_CLI_H */
