/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys_command_line.h"
#include "printf.h"

#define TEST_CHANNEL		(31)
#define TEST_BUF			(63)
#define TEST_CMD_SIZE		(4)

enum {
	INTEGRATED_TEST,
	RBC_V00_INIT_TEST,
	RBC_LPI_ENTRY_TEST,
	RBC_SET_LP_MODE_L1_TEST,
	RBC_SET_LP_MODE_L2_TEST,
	RBC_LP_ENTRY_TEST,
	RBC_LP_EXIT_TEST,
	RBC_LPI_EXIT_TEST,
};

#ifdef __TARGET_PCIE
#include "../pcie/test_pcie.h"

static const char * const cm7_test_params[] = {
	"iatu",
};
#else
	/* TODO: Need to add parameters for secondary chiplet test cases */
#endif

void test_cb(int inst, int chan);
