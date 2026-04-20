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

#ifndef _G_CMGR_CMD_EVENT_COMMON_H_
#define _G_CMGR_CMD_EVENT_COMMON_H_

#define ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_ID			 0x0
#define ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_AFFINITY	 0x4
#define ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_NOTIFICATION 0x8
#define ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_CONTROL		 0xC
#define ADDR_OFFSET_CMGR_CMD_EVENT_TASK_INFO_ID			 0x20
#define ADDR_OFFSET_CMGR_CMD_EVENT_TASK_INFO_WORKLOAD	 0x24

union cmgr_cmd_event_cmd_info_id {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union cmgr_cmd_event_cmd_info_affinity {
	struct __attribute__((packed)) {
		uint32_t local_dnc_affinity : 16;
		uint32_t local_rbdma_affinity : 1;
		uint32_t cmgr_affinity : 4;
		uint32_t reserved : 11;
	};
	uint32_t bits;
};

union cmgr_cmd_event_cmd_info_notification {
	struct __attribute__((packed)) {
		uint32_t target : 22;
		uint32_t event_code_dnc : 4;
		uint32_t event_group_idx_dnc : 6;
	};
	uint32_t bits;
};

union cmgr_cmd_event_cmd_info_control {
	struct __attribute__((packed)) {
		uint32_t event_group_idx_rbdma : 8;
		uint32_t cmd_id_cmgr : 16;
		uint32_t noti_format_dnc : 1;
		uint32_t noti_format_rbdma : 1;
		uint32_t reserved : 2;
		uint32_t cmd_type : 3;
		uint32_t eocs : 1;
	};
	uint32_t bits;
};

union cmgr_cmd_event_task_info_id {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union cmgr_cmd_event_task_info_workload {
	struct __attribute__((packed)) {
		uint32_t tinfo_id : 8;
		uint32_t credit : 8;
		uint32_t local_timestamp : 8;
		uint32_t rsvd_24 : 1;
		uint32_t event_type : 3;
		uint32_t cmd_type : 3;
		uint32_t sender : 1;
	};
	uint32_t bits;
};

#endif /* _G_CMGR_CMD_EVENT_COMMON_H_*/
