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

#ifndef _RUSH_CLI_UTIL_H
#define _RUSH_CLI_UTIL_H

#include "sys_command_line.h"
#include "terminal_task.h"
#include "common_test.h"

#define LOG_SHELL terminal_printf

#define SIZE_KiB(x)			((size_t)(x) << 10)
#define SIZE_MiB(x)			(SIZE_KiB(x) << 10)
#define SIZE_GiB(x)			(SIZE_MiB(x) << 10)

#define LOCAL_CL_ADDR(addr)	((uint64_t)(addr) & 0x1FFFFFFFFFUL)

int rush_cli_parse_size(const char *str, uint64_t *size);
int rush_cli_split_to_fields(char *str, uint32_t len, int sep, char **fields, int num_fields);

static inline bool rush_cli_chk_addr_in_range(uint64_t addr, uint64_t base, uint64_t size)
{
	return (addr >= base) && (addr < (base + size));
}

static inline uint32_t rush_cli_get_cl_from_addr(uint64_t addr)
{
	return addr >> 37;
}

enum memory_type rush_cli_chk_memory_type(uint64_t addr);
int rush_cli_validate_addr_size(enum memory_type mem_type, uint64_t addr, uint32_t size);

#endif /* _RUSH_CLI_UTIL_H */
