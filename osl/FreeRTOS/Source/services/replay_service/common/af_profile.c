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

#if defined(AF_PROFILE_ENABLED) && !defined(VDK)
#include <stdio.h>
#include <string.h>
#include "sys_command_line.h"
#include "terminal_task.h"
#include "hal/hw_spec.h"
#include "hal/dnc_if.h"
#include "hal/rbdma_if.h"
#include "hal/log_mgr.h"
#include "rbln/utils.h"
#include "cpu.h"
#include "rbln/log.h"
#include "common/cb_tcb.h"
#include "common/exec_id.h"
#include "common/af_profile.h"
#include "hal/command_descriptor.h"

static const char help_profile_show[] = "[af_profile_show]\r\n"
									  " * show profile result\r\n"
									  "\r\n";

static const char help_profile_clear[] = "[af_profile_clear]\r\n"
									   " * clear profile log\r\n"
									   "\r\n";

static const char help_profile_reset[] = "[af_profile_reset]\r\n"
									   " * reset profile clk\r\n"
									   "\r\n";

static const char * const profile_event_string[] = {
	"AF_CHECK_DEP",
	"AF_FETCH_TRIGGER",
	"AF_CHECK_HW_DONE",
	"AF_HANDLER",
	"PROFILE_EVENT_TYPE_NUM",
};

static int profile_log_idx[RL_CPU_CORE_NUM];
static uint64_t profile_event_start[RL_CPU_CORE_NUM][AF_PROFILE_EVENT_NUM];
struct af_profile_log profile_tasks[RL_CPU_CORE_NUM][AF_MAX_PROFILE_EVENT_NUM];

void af_profile_reset(void)
{
	DNC_PROFILE_RESET(0);
	RBDMA_LOGMGR_RESET();

	memset(profile_log_idx, 0, sizeof(profile_log_idx));
	cpu_raise_clksync_interrupt();
}

void af_profile_log_start(enum af_profile_event evt_type)
{
	int core_id = get_current_cpuid();

	profile_event_start[core_id][evt_type] = rl_cpu_read_cycle();
}

void af_profile_log(enum af_profile_event evt_type, uint16_t cmd_id, uint8_t cmd_type)
{
	uint64_t end_cycle = rl_cpu_read_cycle();
	int core_id = get_current_cpuid();
	int idx = profile_log_idx[core_id];
	uint64_t start_cycle = profile_event_start[core_id][evt_type];

	if (idx == AF_MAX_PROFILE_EVENT_NUM) {
		RLOG_ERR("profile buffer full\r\n");
		return;
	}

	profile_log_idx[core_id]++;

	struct af_profile_log *log = &profile_tasks[core_id][idx];

	log->cmd_id = cmd_id;
	log->task_id = 0;
	log->cmd_type = cmd_type;
	log->duration = end_cycle - start_cycle;
	log->start_time = start_cycle;
	log->evt_type = evt_type;
}

static void profile_show(int core_id)
{
	struct af_profile_log *log;
	int latest = profile_log_idx[core_id];

	RLOG_ERR("*** core %d result ***\r\n", core_id);
	for (int i = 0; i < latest; i++) {
		log = &profile_tasks[core_id][i];
		RLOG_ERR("evt %d %d %d %llu %llu %s\r\n", log->cmd_id, log->cmd_type, log->task_id,
				log->start_time, log->duration, profile_event_string[log->evt_type]);
	}
}

static void profile_show_hwcounter(void)
{
	uint64_t rbdma_exetime = log_mgr_sum_exectime_rbdma(RBDMA_LOGMGR_DUMP_PTR(),
														RBDMA_LOGMGR_GET_DUMP_CNT());
	uint64_t dnc_exetime = log_mgr_sum_exectime_dnc(0, DNC_PROFILE_PTR(0),
													DNC_PROFILE_GET_CNT(0));

	RLOG_ERR("rbdma: %lu comp0: %lu\r\n", rbdma_exetime, dnc_exetime);
}

static uint8_t cli_profile_show(int argc, char *argv[])
{
	RLOG_ERR("af_profile_show start\r\n");
	profile_show_hwcounter();
	RLOG_ERR("------------------------------------------------------------------------\r\n");

	for (int i = 0; i < RL_CPU_CORE_NUM; i++)
		profile_show(i);

	RLOG_ERR("------------------------------------------------------------------------\r\n");
	RLOG_ERR("af_profile_show end\r\n");

	return true;
}

static uint8_t cli_profile_show_index(int argc, char *argv[])
{
	uint64_t size;

	printf("\r\n");
	for (int i = 0; i < RL_CPU_CORE_NUM; i++) {
		size = (uint64_t)&profile_tasks[i][profile_log_idx[i]]
			   - (uint64_t)&profile_tasks[i][0];
		printf("core[%d]: %p size(%#lx)\r\n", i, profile_tasks[i], size);
	}

	return true;
}

static uint8_t cli_profile_clear(int argc, char *argv[])
{
	memset(profile_log_idx, 0, sizeof(profile_log_idx));
	memset(profile_tasks, 0, sizeof(profile_tasks));

	return true;
}

static uint8_t cli_profile_reset(int argc, char *argv[])
{
	af_profile_reset();

	return true;
}

CLI_REGISTER(af_profile_show, NULL, cli_profile_show, help_profile_show);
CLI_REGISTER(af_profile_clear, NULL, cli_profile_clear, help_profile_clear);
CLI_REGISTER(af_profile_reset, NULL, cli_profile_reset, help_profile_reset);
CLI_REGISTER(af_profile_show_index, NULL, cli_profile_show_index, "");

#endif /* AF_PROFILE_ENABLED && !VDK */
