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

#ifndef _RL_LOG_H
#define _RL_LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "rbln/fwlog_if.h"
#include "rbln_cmn_ioctl.h"

#ifndef dev_fmt
#define dev_fmt(fmt)	fmt
#endif

#define BASE_ADDR_PA_DRAM_LOGBUF	0xFC00000u
#define LOGBUF_SIZE			0x0200000u

// 128B for a plain log entry
// This makes log parsing easier and 100B for a log line seems to be long enough.
struct rl_log {
	uint64_t tick;
	uint8_t type;
	uint8_t cpu;
	uint8_t func_id;
	uint8_t rsvd;
	char task[RBLN_TASK_NAME_LEN];
	char logstr[RBLN_LOG_STR_LEN];
} __attribute__((packed, aligned(4)));

/* LOG Entry should be power of 2 since we are using Mask of (Entry - 1) */
#define RL_LOG_ENTRY_CNT		((int)(LOGBUF_SIZE / sizeof(struct rl_log) >> 1 << 1))

void rl_log_msg(uint8_t type, uint8_t func_id, const char *format, ...);
void rl_log_msg_lim(uint8_t type, uint8_t func_id, uint64_t *jiffies, const char *format, ...);

#define RLOG_ERR(fmt, args...)		rl_log_msg((uint8_t)RBLN_LOG_ERR, 0xff, dev_fmt(fmt), ##args)
#define FLOG_ERR(f, fmt, args...)	rl_log_msg((uint8_t)RBLN_LOG_ERR, f, dev_fmt(fmt), ##args)

#if defined(__TARGET_PROFILE__)
#define RLOG_INFO(fmt, args...)
#define RLOG_DBG(fmt, args...)
#define RLOG_DBG_LIM(fmt, args...)
#define RLOG_VER(fmt, args...)
#define FLOG_INFO(f, fmt, args...)
#define FLOG_DBG(f, fmt, args...)
#define FLOG_DBG_LIM(f, fmt, args...)
#define FLOG_VER(f, fmt, args...)
#elif defined(__TARGET_RELEASE__)
#define RLOG_INFO(fmt, args...)		rl_log_msg((uint8_t)RBLN_LOG_INFO, 0xff, dev_fmt(fmt), ##args)
#define RLOG_DBG(fmt, args...)
#define RLOG_DBG_LIM(fmt, args...)
#define RLOG_VER(fmt, args...)
#define FLOG_INFO(f, fmt, args...)	rl_log_msg((uint8_t)RBLN_LOG_INFO, f, dev_fmt(fmt), ##args)
#define FLOG_DBG(f, fmt, args...)
#define FLOG_DBG_LIM(f, fmt, args...)
#define FLOG_VER(f, fmt, args...)
#else
#define RLOG_INFO(fmt, args...)		rl_log_msg((uint8_t)RBLN_LOG_INFO, 0xff, dev_fmt(fmt), ##args)
#define RLOG_DBG(fmt, args...)		rl_log_msg((uint8_t)RBLN_LOG_DBG, 0xff, dev_fmt(fmt), ##args)
#define RLOG_DBG_LIM(fmt, args...)												\
	do {																		\
		static uint64_t j;														\
		rl_log_msg_lim((uint8_t)RBLN_LOG_DBG, 0xff, &j, dev_fmt(fmt), ##args);	\
	} while (0)
#define RLOG_VER(fmt, args...)													\
	rl_log_msg((uint8_t)RBLN_LOG_VERBOSE, 0xff, dev_fmt(fmt), ##args)
#define FLOG_INFO(f, fmt, args...)	rl_log_msg((uint8_t)RBLN_LOG_INFO, f, dev_fmt(fmt), ##args)
#define FLOG_DBG(f, fmt, args...)	rl_log_msg((uint8_t)RBLN_LOG_DBG, f, dev_fmt(fmt), ##args)
#define FLOG_DBG_LIM(f, fmt, args...)											\
	do {																		\
		static uint64_t j;														\
		rl_log_msg_lim((uint8_t)RBLN_LOG_DBG, f, &j, dev_fmt(fmt), ##args);		\
	} while (0)
#define FLOG_VER(f, fmt, args...)	rl_log_msg((uint8_t)RBLN_LOG_VERBOSE, f, dev_fmt(fmt), ##args)
#endif

enum rbln_log_level rl_log_get_level(void);
#endif /* _RL_LOG_H */
