/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <test_common.h>
#include "test_sic.h"
#include <sic.h>
#include <rebel_h_sic.h>

uint8_t test_sic(int argc, char **argv)
{
	uint32_t res;

	if (argc == 0) {
		printf("need command input\n");
		return false;
	}

	if (strcmp(argv[0], "bootdone") == 0) {
		res = request_to_cmrt(CMRT_MW_BOOTDONE_CHECK);
		if (res == RESPONSE_PASS)
			printf("responsed bootdone pass returned\n");
		else
			printf("responsed bootdone fail returned\n");
	} else if (strcmp(argv[0], "imgupdate") == 0) {
		res = request_to_cmrt(CMRT_MW_LOAD_IMG_FROM_HBM);
		if (res == RESPONSE_PASS)
			printf("responsed image update pass returned\n");
		else
			printf("responsed image update fail returned\n");
	} else
		printf("param error\n");

	return 1;
}

static const char help_sic[] =
	"[sic [command]]\n"
	"- [sic bootdone]\n"
	"- [sic imgupdate]\n"
	"for bootdone check and img update\n"
	"\n";

CLI_REGISTER(sic, NULL, test_sic, help_sic);
