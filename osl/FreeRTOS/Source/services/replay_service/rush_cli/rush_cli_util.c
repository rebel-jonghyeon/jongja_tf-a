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

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "autogen/g_sys_addrmap.h"

#include "rush_cli_util.h"

#define SHM_SIZE	SIZE_MiB(64)
#define SPM_SIZE	SIZE_MiB(64)

int rush_cli_parse_size(const char *str, uint64_t *size)
{
	char *endptr;
	uint64_t val;

	errno = 0;
	val = (uint64_t)strtoull(str, &endptr, 0);
	if (errno || str == endptr)
		return -EINVAL;

	switch (*endptr) {
	case 'k':
	case 'K':
		val *= SIZE_KiB(1);
		break;
	case 'm':
	case 'M':
		val *= SIZE_MiB(1);
		break;
	case 'g':
	case 'G':
		val *= SIZE_GiB(1);
		break;
	default:
		break;
	};

	*size = val;

	return 0;
}

int rush_cli_split_to_fields(char *str, uint32_t len, int sep, char **fields, int num_fields)
{
	int i = 0;
	int ret = 0;
	char *end = str + len;

	while (str < end) {
		if (i >= num_fields)
			return -EINVAL;

		/* remove start spaces at input start */
		if (!*str) {
			str++;
			continue;
		}

		fields[i++] = str;
		while (str < end && *str && *str != sep)
			str++;
		if (str >= end || !*str)
			break;
		*str++ = 0;
	}
	ret = i;

	while (i < num_fields)
		fields[i++] = NULL;

	return ret;
}

enum memory_type rush_cli_chk_memory_type(uint64_t addr)
{
	addr = LOCAL_CL_ADDR(addr);
	if (rush_cli_chk_addr_in_range(addr, DCL0_SH_MEM_BASE, SHM_SIZE))
		return SHM;
	if (rush_cli_chk_addr_in_range(addr, DCL0_SP_MEM_BASE, SPM_SIZE))
		return SP;


	return DRAM;
}

int rush_cli_validate_addr_size(enum memory_type mem_type, uint64_t addr, uint32_t size)
{
	uint64_t local = LOCAL_CL_ADDR(addr);

	switch (mem_type) {
	case SHM:
		if (size > SHM_SIZE)
			return -EINVAL;
		if (local + size > DCL0_SH_MEM_BASE + SHM_SIZE)
			return -EINVAL;
		break;
	case SP:
		if (size > SPM_SIZE)
			return -EINVAL;
		if (local + size > DCL0_SP_MEM_BASE + SPM_SIZE)
			return -EINVAL;
		break;
	default:
		if (addr < DRAMUSERREGIONBASE || addr >= DRAMEXTENDEDBASE)
			return -EINVAL;
		if (addr + size > DRAMEXTENDEDBASE)
			return -EINVAL;
		break;
	}

	return 0;
}
