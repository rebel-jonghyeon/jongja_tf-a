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

#ifndef _G_DNC_TASK_32B_EVT0_H_
#define _G_DNC_TASK_32B_EVT0_H_

#define ADDR_OFFSET_DNC_TASK_DESC_TSYNC			0x014
#define ADDR_OFFSET_DNC_TASK_LEGACY_Q_CREDIT	0x028
#define ADDR_OFFSET_DNC_TASK_LEGACY_T_CREDIT	0x02C
#define ADDR_OFFSET_DNC_TASK_DO					0x030
#define ADDR_OFFSET_DNC_TASK_TRIG				0x034
#define ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH1	0x08C
#define ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH1 0x0AC
#define ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH1 0x0CC
#define ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH1 0x0EC
//#define ADDR_OFFSET_DNC_TASK_DELAY				0x0FC

/*
union dnc_task_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 10;
		uint32_t set_dest : 6;
		uint32_t set_code : 16;
	};
	uint32_t bits;
};
*/

union dnc_task_legacy_q_credit {
	struct __attribute__((packed)) {
		uint32_t comp : 8;
		uint32_t ldudma : 8;
		uint32_t lpudma : 8;
		uint32_t studma : 8;
	};
	uint32_t bits;
};

union dnc_task_legacy_t_credit {
	struct __attribute__((packed)) {
		uint32_t comp : 8;
		uint32_t ldudma : 8;
		uint32_t lpudma : 8;
		uint32_t studma : 8;
	};
	uint32_t bits;
};

union dnc_task_do {
	struct __attribute__((packed)) {
		uint32_t en_comp : 1;
		uint32_t en_ldudma : 1;
		uint32_t en_lpudma : 1;
		uint32_t en_studma : 1;
		uint32_t pause_comp : 1;
		uint32_t pause_ldudma : 1;
		uint32_t pause_lpudma : 1;
		uint32_t pause_studma : 1;
		uint32_t tstamp_en : 1;
		uint32_t en_credit_vio : 1;
		uint32_t rsvd10 : 20;
		uint32_t en_desc_fid_max : 1;
		uint32_t en_legacy_credit : 1;
	};
	uint32_t bits;
};

union dnc_task_trig {
	struct __attribute__((packed)) {
		uint32_t clear_comp : 1;
		uint32_t clear_ldudma : 1;
		uint32_t clear_lpudma : 1;
		uint32_t clear_studma : 1;
		uint32_t erun_comp : 1;
		uint32_t erun_ldudma : 1;
		uint32_t erun_lpudma : 1;
		uint32_t erun_studma : 1;
		uint32_t reset_fetch_addr_comp : 1;
		uint32_t reset_fetch_addr_ldudma : 1;
		uint32_t reset_fetch_addr_lpudma : 1;
		uint32_t reset_fetch_addr_studma : 1;
		uint32_t erun_preq_comp : 1;
		uint32_t erun_preq_ldudma : 1;
		uint32_t erun_preq_lpudma : 1;
		uint32_t erun_preq_studma : 1;
		uint32_t rsvd16 : 12;
		uint32_t apply_cfg : 1;
		uint32_t clear_wait : 1;
		uint32_t clear_pause : 1;
		uint32_t etdone : 1;
	};
	uint32_t bits;
};

union dnc_task_comp_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_ldudma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_lpudma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_studma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

/*
union dnc_task_delay {
	struct __attribute__((packed)) {
		uint32_t comp_cfg : 4;
		uint32_t udma_cfg : 4;
		uint32_t tstamp_unit : 8;
		uint32_t dummy : 8;
		uint32_t rsvd24 : 8;
	};
	uint32_t bits;
};
*/

enum dnc_task_desc_tsync_set_dest {
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA0,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA1,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA2,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA3,
};

enum dnc_task_comp_task_fetch1_mode {
	DNC_TASK_COMP_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_COMP_TASK_FETCH1_MODE_EATF,
};

enum dnc_task_ldudma_task_fetch1_mode {
	DNC_TASK_LDUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_LDUDMA_TASK_FETCH1_MODE_EATF,
};

enum dnc_task_lpudma_task_fetch1_mode {
	DNC_TASK_LPUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_LPUDMA_TASK_FETCH1_MODE_EATF,
};

enum dnc_task_studma_task_fetch1_mode {
	DNC_TASK_STUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_STUDMA_TASK_FETCH1_MODE_EATF,
};

#endif /* _G_DNC_TASK_32B_EVT0_H_*/
