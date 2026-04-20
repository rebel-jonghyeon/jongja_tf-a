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

#include <stdio.h>
#include <string.h>
#include "sys_command_line.h"
#include "terminal_task.h"
#include "hal/hw_spec.h"
//#include "rbln/utils.h"
#include "rl_utils.h"
#include "cpu.h"
#include "common/profile.h"
#include "rbln/log.h"
//#include "common/cb_tcb.h"
//#include "cmd_mgr/command.h"
#include "common/exec_id.h"
//#include "hal/command_descriptor.h"
//#include "common/ici.h"
#include "system_api.h"
#include "chiplet.h"


static const char help_profile_show[] = "[profile_show]\r\n"
									  " * show profile result\r\n"
									  "\r\n";

static int hwcounter_log_idx[HW_SPEC_DNC_COUNT + HW_SPEC_DDMA_COUNT];
static int profile_log_idx;
uint64_t rl_profile_event_start[PROFILE_EVENT_TYPE_NUM];
struct profile_log rl_profile_tasks[RL_MAX_PROFILE_EVENT_NUM];
struct hwcounter_log rl_hwcounter[HW_SPEC_DNC_COUNT + HW_SPEC_DDMA_COUNT]
								 [RL_MAX_HWCOUNTER_EVENT_NUM];
uint16_t profile_sg_id[1024];

void rl_profile_init(void)
{
    profile_log_idx = 0;
	memset(hwcounter_log_idx, 0, sizeof(hwcounter_log_idx));
}

#ifndef PROFILE_DISABLE_L1
void rl_profile_sg_cid(uint16_t cid, uint8_t subtask_type)
{
	profile_sg_id[subtask_type] = cid;
}

void rl_profile_log_start(profile_event evt_type)
{
	rl_profile_event_start[evt_type] = get_current_count();
}

void rl_profile_log(profile_event evt_type, uint16_t cmd_id, uint8_t cmd_type)
{
	uint64_t end_cycle = get_current_count();
	int idx = profile_log_idx;
	uint64_t start_cycle = rl_profile_event_start[evt_type];

	if (idx == RL_MAX_PROFILE_EVENT_NUM) {
	//	RLOG_ERR("profile buffer full\r\n");
		return;
	} else {
		profile_log_idx++;
	}

	struct profile_log *log = &rl_profile_tasks[idx];

	/* logging */
	if (cmd_id >= UDMA_SUBTASK_ID_MIN) {
		uint32_t subtask_type = (cmd_type < COMMON_CMD_TYPE_DDMA) ?
								SUBTASK_TYPE_UDMA : SUBTASK_TYPE_DDMA;

		log->cmd_id = profile_sg_id[subtask_type];
	} else {
		log->cmd_id = cmd_id;
	}
	/* ToDo: get task id information for profiler */
	log->task_id = 0;
	log->cmd_type = cmd_type;
	log->duration = end_cycle - start_cycle;
	log->start_time = start_cycle;
	log->evt_type = evt_type;
}


void rl_profile_hwcounter(hwcounter_event evt_type, uint64_t val, uint32_t id_info, uint32_t dnc_id,
						  uint8_t cmd_type)
{
	int idx;
	union exec_id id;
	struct hwcounter_log *log;

	id.bits = id_info;
	if (cmd_type < COMMON_CMD_TYPE_DDMA) {
		idx = hwcounter_log_idx[dnc_id];
		log = &rl_hwcounter[dnc_id][idx];
	} else {
		idx = hwcounter_log_idx[HW_SPEC_DNC_COUNT];
		log = &rl_hwcounter[HW_SPEC_DNC_COUNT][idx];
	}

	if (idx == RL_MAX_HWCOUNTER_EVENT_NUM) {
	//	RLOG_ERR("profile buffer full\r\n");
		return;
	} else {
		hwcounter_log_idx[dnc_id]++;
	}

	/* logging */
	log->cmd_id = id.cmd_id;
	/* ToDo: get task id information for profiler */
	log->task_id = dnc_id;
	log->cmd_type = cmd_type;
	log->cnt = val;
	log->evt_type = evt_type;
}
#endif

static void profile_show(int core_id)
{
	struct profile_log *log;
	int latest = profile_log_idx;

	RLOG_ERR("*** core %d result ***\r\n", core_id);
	for (int i = 0; i < latest; i++) {
		log = &rl_profile_tasks[i];
		RLOG_ERR("evt %d %d %d %llu %llu %s\r\n", log->cmd_id, log->cmd_type, log->task_id,
				log->start_time, log->duration, profile_event_string[log->evt_type]);
	}
}

static void profile_show_hwcounter(int task_id)
{
	struct hwcounter_log *log;
	int latest = hwcounter_log_idx[task_id];

	RLOG_ERR("*** hwcounter result dev %d start ***\r\n", task_id);
	for (int i = 0; i < latest; i++) {
		log = &rl_hwcounter[task_id][i];
		RLOG_ERR("evt %d %d %d %llu %s\r\n", log->cmd_id, log->cmd_type, log->task_id,
				log->cnt, profile_event_hwcounter_string[log->evt_type]);
	}
	RLOG_ERR("*** hwcounter result dev %d end ***\r\n", task_id);
}

//static void profile_show_l2(int core_id)
//{
//	struct profile_log_l2 *log;
//	int latest = profile_log_idx_l2;
//
//	RLOG_ERR("*** core %d result ***\r\n", core_id);
//	for (int i = 0; i < latest; i++) {
//		log = &rl_profile_tasks_l2[i];
//		RLOG_ERR("evt %d %d %08lx %d %llu %llu %s\r\n",
//				log->func_id, log->ctx_id, log->cbtcb, log->ci,
//				log->start_time, log->duration,
//				profile_event_l2_string[log->evt_type]);
//	}
//}


static uint8_t rl_profile_show(int argc, char *argv[])
{
	int level = 1;

	if (argc == 1) {
		level = atoi(argv[0]);
		if (level > 2)
			return false;
	}

	RLOG_ERR("profile_show_start\r\n");
	RLOG_ERR("------------------------------------------------------------------------\r\n");

    profile_show(0);

	if (level == 1) {
		for (int i = 0; i < HW_SPEC_DNC_COUNT + HW_SPEC_DDMA_COUNT; i++)
			profile_show_hwcounter(i);
	}
	RLOG_ERR("------------------------------------------------------------------------\r\n");
	RLOG_ERR("profile_show_end\r\n");

	return true;
}

uint8_t rl_profile_show_index()
{
	uint64_t size;

	printf("\r\n");
	size = (uint64_t)&rl_profile_tasks[profile_log_idx]
		   - (uint64_t)&rl_profile_tasks[0];
	printf("core[0]: %p size(%#lx)\r\n", rl_profile_tasks, size);

	for (int i = 0; i < HW_SPEC_DNC_COUNT + HW_SPEC_DDMA_COUNT; i++) {
		size = (uint64_t)&rl_hwcounter[i][hwcounter_log_idx[i]] - (uint64_t)&rl_hwcounter[i][0];
		printf("hwcnt[%d]: %p size(%#lx)\r\n", i, rl_hwcounter[i], size);
	}

	return true;
}

CLI_REGISTER(profile_show, NULL, rl_profile_show, help_profile_show);
CLI_REGISTER(profile_show_index, NULL, rl_profile_show_index, "");

