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

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rbln/spinlock.h"
#include "sys_command_line.h"
#include "cpu.h"
#include "rbln/cache.h"
#include "rbln_cmn_ioctl.h"
#include "terminal_task.h"
#include "rbln/log.h"
#include "rbln/rebel.h"

#define LOG_SHELL terminal_printf
#define LOGPRINT_PERIOD_MS 1000u

/* DRAM 0x0 ~ 0x80000 (512KB) is reserved for FW Image(DDR_RO)
 * .logbuf section is adjusted in linker scripts in FW region(DDR_RW)
 * FW region DRAM END(0x10000000) - LOGBUF RESERVE(0x400000(4MB)) : 0xfc00000
 * FW will use 4MB logbuf at 0xfc00000 ~ 0x10000000
 */
struct rl_log _log[RL_LOG_ENTRY_CNT] __attribute__((section(".logbuf")));
static int log_idx = -1;
static uint32_t log_idx_mask = RL_LOG_ENTRY_CNT - 1;
static spinlock_t log_idx_lock = { 0, };

//#ifdef __TARGET_DEBUG__
#if 0
static const char help_log_show[] = "[log_show]\r\n"
									" * show log buffer\r\n"
									"\r\n";

static const char help_log_clear[] = "[log_clear]\r\n"
									 " * clear log buffer\r\n"
									 "\r\n";

static const char help_log_level[] = "[log_level]\r\n"
									   " * set log level: 0(err), 1(info), 2(dbg), 3(verbose)\r\n"
									   "\r\n";

static const char log_type_name[][RBLN_LOGTYPE_NAME_LEN] = {
	"ERR", "INFO", "DBG", "VERBOSE",
};
#endif /* __TARGET_DEBUG__ */

/* default log level from Makefile */
static int rlog_level = LOG_LEVEL_DEFAULT;

static void rl_log_save_entry(int idx, uint8_t type, uint8_t func_id, const char *log_str)
{
	struct rl_log *log;

	log = &_log[idx];
	log->tick = xTaskGetTickCount();
	log->type = type;
	log->cpu = get_current_cpuid();
	log->func_id = func_id;

	memcpy(log->logstr, log_str, RBLN_LOG_STR_LEN);

	clean_dcache_range((uintptr_t)log, sizeof(struct rl_log));
}

static inline void _rl_log_msg(uint8_t type, uint8_t func_id, const char *format, va_list va)
{
	if (type <= rlog_level) {
		char log_str[RBLN_LOG_STR_LEN];
		int idx;
		unsigned long flags;

		memset(log_str, 0, RBLN_LOG_STR_LEN);
		vsnprintf(log_str, RBLN_LOG_STR_LEN, format, va);

		flags = spin_lock_irqsave(&log_idx_lock);
		idx = ++log_idx & log_idx_mask;
		spin_unlock_irqrestore(&log_idx_lock, flags);

		rl_log_save_entry(idx, type, func_id, log_str);
	}
}

void rl_log_msg(uint8_t type, uint8_t func_id, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	_rl_log_msg(type, func_id, format, args);
	va_end(args);
}

static uint8_t rl_log_show(int argc, char *argv[])
{
	int idx, latest;
	struct rl_log *log;
	unsigned long flags;

	flags = spin_lock_irqsave(&log_idx_lock);
	idx = log_idx;
	spin_unlock_irqrestore(&log_idx_lock, flags);

	if (idx == -1)
		return true;

	latest = idx & log_idx_mask;
	idx = (idx < RL_LOG_ENTRY_CNT) ? -1 : latest;

//	LOG_SHELL("*--------------------------------------------------------------------------\r\n");
//	LOG_SHELL("%20s %8s %4s %5s %18s\r\n", "Tick", "LogType", "CPU", "Message");
//	LOG_SHELL("--------------------------------------------------------------------------\r\n");

	do {
		if (++idx >= RL_LOG_ENTRY_CNT)
			idx = 0;

		log = &_log[idx];

	//	LOG_SHELL("[%18llu] %8s %4d %5s %s", log->tick, log_type_name[log->type],
	//			  log->cpu, log->logstr);

	} while (latest != idx);

//	LOG_SHELL("--------------------------------------------------------------------------\r\n");

	return true;
}

static void rl_log_clear_region(void)
{
	unsigned long flags;

	flags = spin_lock_irqsave(&log_idx_lock);
	log_idx = -1;
	memset(_log, 0, sizeof(struct rl_log) * RL_LOG_ENTRY_CNT);
	clean_dcache_range((uintptr_t)_log, sizeof(struct rl_log) * RL_LOG_ENTRY_CNT);
	spin_unlock_irqrestore(&log_idx_lock, flags);
}

static uint8_t rl_log_clear(int argc, char *argv[])
{
	rl_log_clear_region();
	return true;
}

enum rbln_log_level rl_log_get_level(void)
{
	return rlog_level;
}

static bool rl_log_set_level(uint32_t level)
{
	if (level < RBLN_LOG_ERR || level > RBLN_LOG_VERBOSE)
		return false;

	rlog_level = level;

	return true;
}

#if 0
static uint8_t rl_log_level(int argc, char *argv[])
{
	int level = -1;

	/* show current val */
	if (argc == 0) {
		LOG_SHELL("%d\r\n", rlog_level);
		return true;
	}

	if (argc != 1)
		return false;

	level = atoi(argv[0]);

	if (!rl_log_set_level(level))
		LOG_SHELL("Invalid val %d\r\n", level);

	return true;
}
#endif

#if 0
CLI_REGISTER(log_show, NULL, rl_log_show, help_log_show);
CLI_REGISTER(log_clear, NULL, rl_log_clear, help_log_clear);
CLI_REGISTER(log_level, NULL, rl_log_level, help_log_level);
#endif