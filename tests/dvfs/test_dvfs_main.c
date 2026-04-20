/* Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "test_common.h"
#include "rl_errors.h"
#include "dvfs.h"

uint8_t test_main_dvfs(int argc, char *argv[])
{
	uint32_t level;
	uint32_t ret;

	printf("\nStart dvfs test\n");

	if (argc && (strcmp(argv[0], "set_dvfs") == 0)) {
		if (argc < 3) {
			return RL_ERROR;
		}

		level = (uint32_t)strtol(argv[2], NULL, 0);

		if (strcmp(argv[1], "cp") == 0) {
			printf("Test set_dvfs CP level %d\n", level);
			printf("set vout:%d\n", cp_dvfs_table[level].vout_mv);
			printf("set freq:%d\n", cp_dvfs_table[level].freq_numeric);

			ret = set_dvfs_lvl(DVFS_DOMAIN_CP, level);
			if (ret) {
				printf("Error: value is invalid\n");
				return RL_ERROR;
			}

		} else if (strcmp(argv[1], "dnc") == 0) {
			printf("Test set_dvfs DNC level %d\n", level);
			printf("set vout:%d\n", dnc_dvfs_table[level].vout_mv);
			printf("set freq:%d\n", dnc_dvfs_table[level].freq_numeric);

			ret = set_dvfs_lvl(DVFS_DOMAIN_DNC, level);
			if (ret) {
				printf("Error: value is invalid\n");
				return RL_ERROR;
			}
		}
	} else if (argc && (strcmp(argv[0], "get_dvfs") == 0)) {
		if (argc < 2) {
			return RL_ERROR;
		}

		struct dvfs_info info = {0};

		if (strcmp(argv[1], "cp") == 0) {
			printf("Test get_dvfs CP\n");

			ret = get_dvfs_lvl(DVFS_DOMAIN_CP, &info);
			if (ret)
				return RL_ERROR;

			printf("VDD_CP_C02: %d, VDD_CP_C13: %d\n", info.vout[0], info.vout[1]);

			for (int i = 0; i < 2; i++) {
				printf("get cp%d freq : ", i);
				for (int j = 0; j < 4; j++)
					printf("%lu ", info.freq[i][j]);
				printf("\n");
			}
		} else if (strcmp(argv[1], "dnc") == 0) {
			printf("Test get_dvfs DNC\n");

			ret = get_dvfs_lvl(DVFS_DOMAIN_DNC, &info);
			if (ret)
				return RL_ERROR;

			printf("VDD_DCL: %d, VDD_DCL_ODD: %d\n", info.vout[0], info.vout[1]);

			for (int i = 0; i < 2; i++) {
				printf("get dnc%d freq : ", i);
				for (int j = 0; j < 4; j++)
					printf("%lu ", info.freq[i][j]);
				printf("\n");
			}
		}
	}

	return 1;
}

static const char help_dvfs[] =
	"[test_dvfs]\r\n"
	"domain: cp (level: 0~16)\r\n"
	"domain: dnc (level: 0~6)\r\n"
	" - [test_dvfs set_dvfs <domain> <level>]\r\n"
	" - [test_dvfs get_dvfs <domain>]\r\n"
	"\r\n";

CLI_REGISTER(test_dvfs, NULL, test_main_dvfs, help_dvfs);
