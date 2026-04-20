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

#ifndef _G_DNC_TASK_DONE_COMMON_H_
#define _G_DNC_TASK_DONE_COMMON_H_

#define ADDR_OFFSET_DNC_TASK_DONE_DONE_RPT0		 0x000
#define ADDR_OFFSET_DNC_TASK_DONE_LOG0_0		 0x010
#define ADDR_OFFSET_DNC_TASK_DONE_LOG0_1		 0x014
#define ADDR_OFFSET_DNC_TASK_DONE_LOG1_0		 0x018
#define ADDR_OFFSET_DNC_TASK_DONE_LOG1_1		 0x01C
#define ADDR_OFFSET_DNC_TASK_DONE_LOG2_0		 0x020
#define ADDR_OFFSET_DNC_TASK_DONE_LOG2_1		 0x024
#define ADDR_OFFSET_DNC_TASK_DONE_LOG3_0		 0x028
#define ADDR_OFFSET_DNC_TASK_DONE_LOG3_1		 0x02C
#define ADDR_OFFSET_DNC_TASK_DONE_LOG4_0		 0x030
#define ADDR_OFFSET_DNC_TASK_DONE_LOG4_1		 0x034
#define ADDR_OFFSET_DNC_TASK_DONE_LOG5_0		 0x038
#define ADDR_OFFSET_DNC_TASK_DONE_LOG5_1		 0x03C
#define ADDR_OFFSET_DNC_TASK_DONE_LOG6_0		 0x040
#define ADDR_OFFSET_DNC_TASK_DONE_LOG6_1		 0x044
#define ADDR_OFFSET_DNC_TASK_DONE_LOG7_0		 0x048
#define ADDR_OFFSET_DNC_TASK_DONE_LOG7_1		 0x04C
#define ADDR_OFFSET_DNC_TASK_DONE_MEASURE0		 0x080
#define ADDR_OFFSET_DNC_TASK_DONE_MEASURE1		 0x084
#define ADDR_OFFSET_DNC_TASK_DONE_MEASURE2		 0x088
#define ADDR_OFFSET_DNC_TASK_DONE_MEASURE3		 0x08C
#define ADDR_OFFSET_DNC_TASK_DONE_DO			 0x090
#define ADDR_OFFSET_DNC_TASK_DONE_TRIG			 0x094
#define ADDR_OFFSET_DNC_TASK_DONE_STATUS0		 0x0A0
#define ADDR_OFFSET_DNC_TASK_DONE_STATUS1		 0x0A4
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_MODE	 0x0B0
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_SIZE	 0x0B4
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_DEST0	 0x0B8
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_DEST1	 0x0BC
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_PERIOD	 0x0C0
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_SRC		 0x0C4
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_UAN		 0x0C8
#define ADDR_OFFSET_DNC_TASK_DONE_CDUMP_STATUS	 0x0CC
#define ADDR_OFFSET_DNC_TASK_DONE_PROFILE_MODE	 0x0D0
#define ADDR_OFFSET_DNC_TASK_DONE_PROFILE_DEST0	 0x0D4
#define ADDR_OFFSET_DNC_TASK_DONE_PROFILE_DEST1	 0x0D8
#define ADDR_OFFSET_DNC_TASK_DONE_PROFILE_STATUS 0x0DC

union dnc_task_done_done_rpt0 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log0_0 {
	uint32_t bits;
};

union dnc_task_done_log0_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log1_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log1_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log2_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log2_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log3_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log3_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log4_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log4_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log5_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log5_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log6_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log6_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log7_0 {
	struct __attribute__((packed)) {
		uint32_t info : 32;
	};
	uint32_t bits;
};

union dnc_task_done_log7_1 {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_done_measure0 {
	struct __attribute__((packed)) {
		uint32_t back_pressure : 32;
	};
	uint32_t bits;
};

union dnc_task_done_measure1 {
	struct __attribute__((packed)) {
		uint32_t intr_time : 32;
	};
	uint32_t bits;
};

union dnc_task_done_measure2 {
	struct __attribute__((packed)) {
		uint32_t intr_cnt_comp : 16;
		uint32_t intr_cnt_ldudma : 16;
	};
	uint32_t bits;
};

union dnc_task_done_measure3 {
	struct __attribute__((packed)) {
		uint32_t intr_cnt_lpudma : 16;
		uint32_t intr_cnt_studma : 16;
	};
	uint32_t bits;
};

union dnc_task_done_do {
	struct __attribute__((packed)) {
		uint32_t en_intr : 1;
		uint32_t en_log : 1;
		uint32_t en_measure : 1;
		uint32_t en_cdump : 1;
		uint32_t en_profile : 1;
		uint32_t rsvd5 : 27;
	};
	uint32_t bits;
};

union dnc_task_done_trig {
	struct __attribute__((packed)) {
		uint32_t done_chk : 1;
		uint32_t clr_done_queue : 1;
		uint32_t clr_log : 1;
		uint32_t clr_measure : 1;
		uint32_t clr_cdump : 1;
		uint32_t clr_profile : 1;
		uint32_t rsvd6 : 26;
	};
	uint32_t bits;
};

union dnc_task_done_status0 {
	struct __attribute__((packed)) {
		uint32_t blocking : 8;
		uint32_t q_depth : 8;
		uint32_t intr_comp : 1;
		uint32_t intr_ldudma : 1;
		uint32_t intr_lpudma : 1;
		uint32_t intr_studma : 1;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_task_done_status1 {
	struct __attribute__((packed)) {
		uint32_t quiesce_c0_tu : 1;
		uint32_t quiesce_c0_vu : 1;
		uint32_t quiesce_c0_xvu : 1;
		uint32_t quiesce_c0_ablu : 1;
		uint32_t quiesce_c0_absu : 1;
		uint32_t quiesce_c0_splu : 1;
		uint32_t quiesce_c0_spsu : 1;
		uint32_t quiesce_c0_rsvd : 1;
		uint32_t quiesce_c1_tu : 1;
		uint32_t quiesce_c1_vu : 1;
		uint32_t quiesce_c1_xvu : 1;
		uint32_t quiesce_c1_ablu : 1;
		uint32_t quiesce_c1_absu : 1;
		uint32_t quiesce_c1_splu : 1;
		uint32_t quiesce_c1_spsu : 1;
		uint32_t quiesce_c1_rsvd : 1;
		uint32_t quiesce_nclu : 1;
		uint32_t quiesce_ncsu : 1;
		uint32_t rsvd18 : 6;
		uint32_t idle_ldudma : 1;
		uint32_t idle_lpudma : 1;
		uint32_t idle_studma : 1;
		uint32_t idle_comp_queue : 1;
		uint32_t idle_ldudma_queue : 1;
		uint32_t idle_lpudma_queue : 1;
		uint32_t idle_studma_queue : 1;
		uint32_t idle_sp : 1;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_mode {
	struct __attribute__((packed)) {
		uint32_t trigger : 2;
		uint32_t allow_bl2 : 1;
		uint32_t allow_bl4 : 1;
		uint32_t allow_bl8 : 1;
		uint32_t ersp_method : 2;
		uint32_t done_policy : 1;
		uint32_t dcrn_en : 1;
		uint32_t uan_en : 1;
		uint32_t rsvd10 : 22;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_size {
	struct __attribute__((packed)) {
		uint32_t dcrn : 16;
		uint32_t uan : 16;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_dest0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_dest1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t stride : 24;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_period {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_src {
	struct __attribute__((packed)) {
		uint32_t dcrn : 16;
		uint32_t uan : 16;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_uan {
	struct __attribute__((packed)) {
		uint32_t ncore0_tu : 1;
		uint32_t ncore0_ablu : 1;
		uint32_t ncore0_absu : 1;
		uint32_t ncore0_vu : 1;
		uint32_t ncore0_xvu : 1;
		uint32_t ncore0_splu : 1;
		uint32_t ncore0_spsu : 1;
		uint32_t ncore1_tu : 1;
		uint32_t ncore1_ablu : 1;
		uint32_t ncore1_absu : 1;
		uint32_t ncore1_vu : 1;
		uint32_t ncore1_xvu : 1;
		uint32_t ncore1_splu : 1;
		uint32_t ncore1_spsu : 1;
		uint32_t nclu : 1;
		uint32_t ncsu : 1;
		uint32_t ldudma : 1;
		uint32_t lpudma : 1;
		uint32_t studma : 1;
		uint32_t rsvd24 : 13;
	};
	uint32_t bits;
};

union dnc_task_done_cdump_status {
	struct __attribute__((packed)) {
		uint32_t count : 16;
		uint32_t exception : 16;
	};
	uint32_t bits;
};

union dnc_task_done_profile_mode {
	struct __attribute__((packed)) {
		uint32_t comp : 1;
		uint32_t ldudma : 1;
		uint32_t lpudma : 1;
		uint32_t studma : 1;
		uint32_t rsvd4 : 28;
	};
	uint32_t bits;
};

union dnc_task_done_profile_dest0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_done_profile_dest1 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_done_profile_status {
	struct __attribute__((packed)) {
		uint32_t count : 16;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

enum dnc_task_done_cdump_mode_trigger {
	DNC_TASK_DONE_CDUMP_MODE_TRIGGER_DRPT,
	DNC_TASK_DONE_CDUMP_MODE_TRIGGER_CPT1,
	DNC_TASK_DONE_CDUMP_MODE_TRIGGER_CPT2,
	DNC_TASK_DONE_CDUMP_MODE_TRIGGER_CPT3,
};

enum dnc_task_done_cdump_mode_ersp_method {
	DNC_TASK_DONE_CDUMP_MODE_ERSP_METHOD_ERSP_M0,
	DNC_TASK_DONE_CDUMP_MODE_ERSP_METHOD_ERSP_M1,
	DNC_TASK_DONE_CDUMP_MODE_ERSP_METHOD_ERSP_M2,
	DNC_TASK_DONE_CDUMP_MODE_ERSP_METHOD_ERSP_M3,
};

enum dnc_task_done_cdump_mode_done_policy {
	DNC_TASK_DONE_CDUMP_MODE_DONE_POLICY_DONE_G,
	DNC_TASK_DONE_CDUMP_MODE_DONE_POLICY_DONE_R,
};

#endif /* _G_DNC_TASK_DONE_COMMON_H_*/
