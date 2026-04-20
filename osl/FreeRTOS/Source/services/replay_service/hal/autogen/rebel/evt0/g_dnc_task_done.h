/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _G_DNC_TASK_DONE_EVT0_H_
#define _G_DNC_TASK_DONE_EVT0_H_

#define ADDR_OFFSET_DNC_TASK_DONE_DONE_RPT1 0x004

union dnc_task_done_done_rpt1 {
	struct __attribute__((packed)) {
		uint32_t dnc_id : 4;
		uint32_t chiplet_id : 2;
		uint32_t rsvd6 : 2;
		uint32_t sole_cnt : 8;
		uint32_t local_tstamp : 8;
		uint32_t rsvd24 : 1;
		uint32_t event_type : 3;
		uint32_t cmd_type : 3;
		uint32_t sender : 1;
	};
	uint32_t bits;
};

enum dnc_task_done_done_rpt1_event_type {
	DNC_TASK_DONE_DONE_RPT1_EVENT_TYPE_ENQ,
	DNC_TASK_DONE_DONE_RPT1_EVENT_TYPE_CHKIN,
	DNC_TASK_DONE_DONE_RPT1_EVENT_TYPE_DONE,
};

enum dnc_task_done_done_rpt1_cmd_type {
	DNC_TASK_DONE_DONE_RPT1_CMD_TYPE_COMP,
	DNC_TASK_DONE_DONE_RPT1_CMD_TYPE_LDUDMA,
	DNC_TASK_DONE_DONE_RPT1_CMD_TYPE_LPUDMA,
	DNC_TASK_DONE_DONE_RPT1_CMD_TYPE_STUDMA,
};

#endif /* _G_DNC_TASK_DONE_EVT0_H_*/
