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

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "common/debug.h"
#include "rbln/log.h"

void print_regs(const char *reg_name, uint64_t reg_base, uint32_t reg_cnt)
{
	uint32_t i, j, loop_cnt, remained;
	uint32_t reg[4];

	if (!reg_cnt) {
		RLOG_ERR("%s: reg_cnt is 0\r\n", __func__);
		printf("%s: reg_cnt is 0\r\n", __func__);
		return;
	}

	loop_cnt = reg_cnt / 4;
	remained = reg_cnt % 4;

	RLOG_ERR("%s\r\n", reg_name);
	printf("%s\r\n", reg_name);

	for (i = 0; i < loop_cnt; i++) {
		for (j = 0; j < 4; j++)
			reg[j] = rl_readl((void __iomem *)(reg_base + i * 0x10 + j * 0x4));

		RLOG_ERR("[%#lx] %#x %#x %#x %#x\r\n", reg_base + i * 0x10,
				 reg[0], reg[1], reg[2], reg[3]);
		printf("[%#lx] %#x %#x %#x %#x\r\n", reg_base + i * 0x10,
			   reg[0], reg[1], reg[2], reg[3]);
	}

	if (remained) {
		for (i = i * 4; i < reg_cnt; i++) {
			reg[0] = rl_readl((void __iomem *)(reg_base + i * 4));
			RLOG_ERR("[%#lx] %#x\r\n", reg_base + i * 4, reg[0]);
			printf("[%#lx] %#x\r\n", reg_base + i * 4, reg[0]);
		}
	}
}
