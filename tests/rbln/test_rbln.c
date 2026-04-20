/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
#include "FreeRTOS.h"
#include "test_common.h"

#include "task.h"
#include "task_adder.h"
#include "replay.h"

static TaskHandle_t replay_handle;

uint8_t rbln_test_main(int argc, char *argv[])
{
	uint8_t ret = true;

	static struct task_info t_info = {
		.func = replay_task,
		.task_name = "replay",
		.stack_depth = configMINIMAL_STACK_SIZE,
		.param = NULL,
		.priority = 1,
		.affinity = 0x1,
		.handle = &replay_handle,
	};

	task_adder_enqueue(&t_info);

	while (!replay_handle) {
		vTaskDelay(1);
	}

	replay_task_init(replay_handle);

	return ret;
}

//CLI_REGISTER(test_rbln, NULL, rbln_test_main, NULL);
