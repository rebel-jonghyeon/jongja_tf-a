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

#ifndef _RUSH_CLI_MSG_BUF_H
#define _RUSH_CLI_MSG_BUF_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct rush_cli_msg_buf {
	size_t size;

	char *data;
	uint32_t pos;

	bool is_full;
};

int rush_cli_msg_buf_init(struct rush_cli_msg_buf *msg_buf, const size_t size);
void rush_cli_msg_buf_deinit(struct rush_cli_msg_buf *msg_buf);

int rush_cli_msg_buf_sprintf(struct rush_cli_msg_buf *msg_buf, const char *format, ...);
void rush_cli_msg_buf_flush(struct rush_cli_msg_buf *mst_buf);

#define RUSH_CLI_MSG(msg_buf, format, args...)	\
	rush_cli_msg_buf_sprintf(msg_buf, format, ##args)

#endif /* _RUSH_CLI_MSG_BUF_H */
