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

#ifndef RL_PROFILE_H
#define RL_PROFILE_H

struct rl_cb_tcb;

#define RL_MAX_HWCOUNTER_EVENT_NUM 8192
#define RL_MAX_PROFILE_EVENT_NUM 131072
#define RL_MAX_PROFILE_EVENT_L2_NUM 8192

#define MAX_CMD_ID 0xF7FF

#define MAX_SUBTASK_TYPE_NUM 2
#define SUBTASK_TYPE_UDMA 0
#define SUBTASK_TYPE_DDMA 1

#define MAX_SUBTASK_NUM 1024

#define DDMA_SUBTASK_ID_MASK 0x03FF
#define DDMA_SUBTASK_ID_MIN 0xFC00
#define DDMA_SUBTASK_ID_MAX 0xFFFF

#define UDMA_SUBTASK_ID_MASK 0x03FF
#define UDMA_SUBTASK_ID_MIN 0xF800
#define UDMA_SUBTASK_ID_MAX 0xFBFF

//// code from common/exec_id.h
//union exec_id {
//	struct __attribute__((packed, aligned(4))) {
//		uint32_t	func_id		: BIT_WIDTH_ID_INFO_FUNC_ID;
//		uint32_t	ctx_id		: BIT_WIDTH_ID_INFO_CTX_ID;
//		uint32_t	proc_id		: BIT_WIDTH_ID_INFO_PROC_ID;
//		uint32_t	cmd_id		: BIT_WIDTH_ID_INFO_CMD_ID;
//	};
//	uint32_t bits;
//};
//


typedef enum _profile_event {
	CM_LOAD_GETCMD,
	CM_LOAD_ALLOCDS,
	CM_LOAD_ALLOCSB,
	CM_LOAD_GENTLB,
	CM_LOAD_ENQUEUE,
	CM_FETCH_LOAD,
	CM_FETCH_SYNCCHECK,
	CM_FETCH_SYNCEXTCHECK,
	CM_FETCH_DEPCHECK,
	CM_FETCH_CMGRALLOC,
	CM_FETCH_ENQUEUE,
	TM_FETCH,
	HW_RUN,
	HANDLER,
	SM_PROC,
	PROFILE_EVENT_TYPE_NUM,
} profile_event;

typedef enum _profile_event_l2 {
	DOORBELL_HDLR,
	HQ_MGR,
	CB_MGR,
	HDMA_MGR,
	HDMA_HDLR,
	DNC_E2E,
	PROFILE_EVENT_L2_TYPE_NUM,
} profile_event_l2;

typedef enum _hwcounter_event {
	RBDMA_QUEUE_IN,
	RBDMA_QUEUE_OUT,
	RBDMA_TASK_START,
	RBDMA_TASK_DONE,
	DNC_QUEUE_TIME,
	DNC_PRE_TIME,
	DNC_RUN_TIME,
	PROFILE_EVENT_HWCOUNTER_TYPE_NUM,
} hwcounter_event;

static const char * const profile_event_string[] = {
	"CM_LOAD_GETCMD",
	"CM_LOAD_ALLOCDS",
	"CM_LOAD_ALLOCSB",
	"CM_LOAD_GENTLB",
	"CM_LOAD_ENQUEUE",
	"CM_FETCH_LOAD",
	"CM_FETCH_SYNCCHECK",
	"CM_FETCH_SYNCEXTCHECK",
	"CM_FETCH_DEPCHECK",
	"CM_FETCH_CMGRALLOC",
	"CM_FETCH_ENQUEUE",
	"TM_FETCH",
	"HW_RUN",
	"HANDLER",
	"SM_PROC",
	"PROFILE_EVENT_TYPE_NUM",
};

static const char * const profile_event_l2_string[] = {
	"DOORBELL_HDLR",
	"HQ_MGR",
	"CB_MGR",
	"HDMA_MGR",
	"HDMA_HDLR",
	"DNC_E2E",
	"PROFILE_EVENT_L2_TYPE_NUM",
};

static const char * const profile_event_hwcounter_string[] = {
	"RBDMA_QUEUE_IN",
	"RBDMA_QUEUE_OUT",
	"RBDMA_TASK_START",
	"RBDMA_TASK_DONE",
	"DNC_QUEUE_TIME",
	"DNC_PRE_TIME",
	"DNC_RUN_TIME",
	"PROFILE_EVENT_HWCOUNTER_TYPE_NUM",
};

struct hwcounter_log {
	uint64_t cnt;
	uint16_t cmd_id;
	uint32_t task_id;
	uint8_t cmd_type;
	hwcounter_event evt_type;
};

struct profile_log {
	uint64_t start_time;
	uint64_t duration;
	uint16_t cmd_id;
	uint32_t task_id;
	uint8_t cmd_type;
	profile_event evt_type;
};

struct profile_log_l2 {
	uint64_t start_time;
	uint64_t duration;
	uint32_t func_id;
	uint32_t ctx_id;
	uint64_t cbtcb;
	uint32_t ci;
	profile_event_l2 evt_type;
};

void rl_profile_init(void);
void rl_profile_log(profile_event evt_type, uint16_t cmd_id, uint8_t cmd_type);
void rl_profile_log_add(profile_event evt_type, uint64_t start_time, uint64_t duration,
						uint16_t cmd_id, uint8_t cmd_type);
void rl_profile_log_start(profile_event evt_type);
void rl_profile_sg_cid(uint16_t cid, uint8_t subtask_type);
void rl_profile_hwcounter(hwcounter_event evt_type, uint64_t val, uint32_t id_info, uint32_t dnc_id,
						  uint8_t cmd_type);

static inline void rl_profile_log_start_l2(profile_event_l2 evt_type) {}
static inline void rl_profile_log_l2(profile_event_l2 evt_type, struct rl_cb_tcb *cbtcb) {}
uint8_t rl_profile_show_index();

// from cp_service/include/autogen/g_cmd_descr_common_rebel.h
enum common_cmd_type {
	COMMON_CMD_TYPE_COMPUTE = 0,
	COMMON_CMD_TYPE_UDMA,
	COMMON_CMD_TYPE_UDMA_LP,
	COMMON_CMD_TYPE_UDMA_ST,
	COMMON_CMD_TYPE_DDMA,
	COMMON_CMD_TYPE_DDMA_HIGHP,
	COMMON_CMD_TYPE_RESERVED,
	COMMON_CMD_TYPE_EXTENSION,
};

// from include/hal/log_mgr.h
#define LOG_MGR_EVT_CODE_NONE   0
#define LOG_MGR_EVT_CODE_ENTRY  1
#define LOG_MGR_EVT_CODE_FETCH  2
#define LOG_MGR_EVT_CODE_RUN    4
#define LOG_MGR_EVT_CODE_DONE   8
struct __attribute__ ((packed)) log_mgr_entry {
    uint32_t exec_id;
    uint32_t evt_code:4;
    uint32_t cycle_cnt:28;
};
struct __attribute__ ((packed)) dnc_profile_entry {
    uint64_t exec_id: 32;
    uint64_t queueing_time: 16;
    uint64_t pre_time: 36;
    uint64_t run_time: 44;
};

#endif /* RL_PROFILE_H */
