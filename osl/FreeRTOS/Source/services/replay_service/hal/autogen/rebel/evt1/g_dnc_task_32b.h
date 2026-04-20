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

#ifndef _G_DNC_TASK_32B_EVT1_H_
#define _G_DNC_TASK_32B_EVT1_H_

#define ADDR_OFFSET_DNC_TASK_DESC_TSYNC			0x014
#define ADDR_OFFSET_DNC_TASK_DO					0x030
#define ADDR_OFFSET_DNC_TASK_TRIG				0x034
#define ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH1	0x08C
#define ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH1 0x0AC
#define ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH1 0x0CC
#define ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH1 0x0EC
#define ADDR_OFFSET_DNC_TASK_DELAY				0x0FC
#define ADDR_OFFSET_DNC_TASK_WAIT_HANDLE		0x100
#define ADDR_OFFSET_DNC_TASK_DEQ_TASK0			0x140
#define ADDR_OFFSET_DNC_TASK_DEQ_TASK1			0x144
#define ADDR_OFFSET_DNC_TASK_DEQ_TASK2			0x148
#define ADDR_OFFSET_DNC_TASK_DEQ_TASK3			0x14C
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_ID		0x170
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_MODE		0x174
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_PROG0	0x178
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_PROG1	0x17C
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_PROG2	0x180
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_TSYNC	0x184
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_CFG0		0x188
#define ADDR_OFFSET_DNC_TASK_ALI0_DESC_CFG1		0x18C
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_ID		0x1A0
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_MODE		0x1A4
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_PROG0	0x1A8
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_PROG1	0x1AC
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_PROG2	0x1B0
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_TSYNC	0x1B4
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_CFG0		0x1B8
#define ADDR_OFFSET_DNC_TASK_ALI1_DESC_CFG1		0x1BC
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_ID		0x1D0
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_MODE		0x1D4
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_PROG0	0x1D8
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_PROG1	0x1DC
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_PROG2	0x1E0
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_TSYNC	0x1E4
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_CFG0		0x1E8
#define ADDR_OFFSET_DNC_TASK_ALI2_DESC_CFG1		0x1EC

union dnc_task_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 12;
		uint32_t set_dest : 8;
		uint32_t set_code : 12;
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
		uint32_t en_wait_handle : 1;
		uint32_t en_af_done_rpt : 1;
		uint32_t en_tsync_serial : 1;
		uint32_t rsvd13 : 17;
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
		uint32_t start_fetch_comp : 1;
		uint32_t start_fetch_ldudma : 1;
		uint32_t start_fetch_lpudma : 1;
		uint32_t start_fetch_studma : 1;
		uint32_t rsvd20 : 4;
		uint32_t kill_running_task_comp : 1;
		uint32_t kill_running_task_ldudma : 1;
		uint32_t kill_running_task_lpudma : 1;
		uint32_t kill_running_task_studma : 1;
		uint32_t clear_wait_handle : 1;
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
		uint32_t rsvd18 : 2;
		uint32_t size : 12;
	};
	uint32_t bits;
};

union dnc_task_ldudma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 2;
		uint32_t size : 12;
	};
	uint32_t bits;
};

union dnc_task_lpudma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 2;
		uint32_t size : 12;
	};
	uint32_t bits;
};

union dnc_task_studma_task_fetch1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 2;
		uint32_t size : 12;
	};
	uint32_t bits;
};

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

union dnc_task_wait_handle {
	struct __attribute__((packed)) {
		uint32_t op_mode : 4;
		uint32_t rpt_base_set : 1;
		uint32_t rpt_addr_reset : 1;
		uint32_t rpt_addr_inc : 1;
		uint32_t rsvd7 : 1;
		uint32_t cnt : 8;
		uint32_t rsvd16 : 8;
		uint32_t ignore_tsync : 1;
		uint32_t force_wait : 1;
		uint32_t rsvd27 : 2;
		uint32_t comp : 1;
		uint32_t ldudma : 1;
		uint32_t lpudma : 1;
		uint32_t studma : 1;
	};
	uint32_t bits;
};

union dnc_task_deq_task0 {
	struct __attribute__((packed)) {
		uint32_t comp : 32;
	};
	uint32_t bits;
};

union dnc_task_deq_task1 {
	struct __attribute__((packed)) {
		uint32_t ldudma : 32;
	};
	uint32_t bits;
};

union dnc_task_deq_task2 {
	struct __attribute__((packed)) {
		uint32_t lpudma : 32;
	};
	uint32_t bits;
};

union dnc_task_deq_task3 {
	struct __attribute__((packed)) {
		uint32_t studma : 32;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_id {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_mode {
	struct __attribute__((packed)) {
		uint32_t id_extend : 1;
		uint32_t auto_fetch_bfix : 1;
		uint32_t enq_rpt : 1;
		uint32_t chkin_rpt : 1;
		uint32_t done_rpt : 1;
		uint32_t cdump : 1;
		uint32_t wait : 1;
		uint32_t tochk : 1;
		uint32_t tsync_chk : 3;
		uint32_t tsync_chk_clr : 1;
		uint32_t tsync_set : 3;
		uint32_t wait_preq : 1;
		uint32_t task_pofs : 8;
		uint32_t rpt_pofs : 8;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_prog0 {
	struct __attribute__((packed)) {
		uint32_t size : 32;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_prog1 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 32;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_prog2 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 8;
		uint32_t addr_sp : 16;
		uint32_t skip_barrier : 1;
		uint32_t option : 2;
		uint32_t qos : 1;
		uint32_t insist : 1;
		uint32_t rsvd29 : 1;
		uint32_t tlb_miss_rpt : 1;
		uint32_t prog_off : 1;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 10;
		uint32_t set_dest : 6;
		uint32_t set_code : 16;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_cfg0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_task_ali0_desc_cfg1 {
	struct __attribute__((packed)) {
		uint32_t data : 12;
		uint32_t addr : 13;
		uint32_t auto_fetch_pfix : 1;
		uint32_t mode : 2;
		uint32_t queue : 2;
		uint32_t sole : 1;
		uint32_t itdone : 1;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_id {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_mode {
	struct __attribute__((packed)) {
		uint32_t id_extend : 1;
		uint32_t auto_fetch_bfix : 1;
		uint32_t enq_rpt : 1;
		uint32_t chkin_rpt : 1;
		uint32_t done_rpt : 1;
		uint32_t cdump : 1;
		uint32_t wait : 1;
		uint32_t tochk : 1;
		uint32_t tsync_chk : 3;
		uint32_t tsync_chk_clr : 1;
		uint32_t tsync_set : 3;
		uint32_t wait_preq : 1;
		uint32_t task_pofs : 8;
		uint32_t rpt_pofs : 8;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_prog0 {
	struct __attribute__((packed)) {
		uint32_t size : 32;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_prog1 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 32;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_prog2 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 8;
		uint32_t addr_sp : 16;
		uint32_t skip_barrier : 1;
		uint32_t option : 2;
		uint32_t qos : 1;
		uint32_t insist : 1;
		uint32_t rsvd29 : 1;
		uint32_t tlb_miss_rpt : 1;
		uint32_t prog_off : 1;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 10;
		uint32_t set_dest : 6;
		uint32_t set_code : 16;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_cfg0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_task_ali1_desc_cfg1 {
	struct __attribute__((packed)) {
		uint32_t data : 12;
		uint32_t addr : 13;
		uint32_t auto_fetch_pfix : 1;
		uint32_t mode : 2;
		uint32_t queue : 2;
		uint32_t sole : 1;
		uint32_t itdone : 1;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_id {
	struct __attribute__((packed)) {
		uint32_t id : 32;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_mode {
	struct __attribute__((packed)) {
		uint32_t id_extend : 1;
		uint32_t auto_fetch_bfix : 1;
		uint32_t enq_rpt : 1;
		uint32_t chkin_rpt : 1;
		uint32_t done_rpt : 1;
		uint32_t cdump : 1;
		uint32_t wait : 1;
		uint32_t tochk : 1;
		uint32_t tsync_chk : 3;
		uint32_t tsync_chk_clr : 1;
		uint32_t tsync_set : 3;
		uint32_t wait_preq : 1;
		uint32_t task_pofs : 8;
		uint32_t rpt_pofs : 8;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_prog0 {
	struct __attribute__((packed)) {
		uint32_t size : 32;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_prog1 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 32;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_prog2 {
	struct __attribute__((packed)) {
		uint32_t addr_ext : 8;
		uint32_t addr_sp : 16;
		uint32_t skip_barrier : 1;
		uint32_t option : 2;
		uint32_t qos : 1;
		uint32_t insist : 1;
		uint32_t rsvd29 : 1;
		uint32_t tlb_miss_rpt : 1;
		uint32_t prog_off : 1;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 10;
		uint32_t set_dest : 6;
		uint32_t set_code : 16;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_cfg0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_task_ali2_desc_cfg1 {
	struct __attribute__((packed)) {
		uint32_t data : 12;
		uint32_t addr : 13;
		uint32_t auto_fetch_pfix : 1;
		uint32_t mode : 2;
		uint32_t queue : 2;
		uint32_t sole : 1;
		uint32_t itdone : 1;
	};
	uint32_t bits;
};

enum dnc_task_desc_tsync_set_dest {
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA0,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA1,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA2,
	DNC_TASK_DESC_TSYNC_SET_DEST_RBDMA3,
};

enum dnc_task_comp_task_fetch1_mode {
	DNC_TASK_COMP_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_COMP_TASK_FETCH1_MODE_EATF,
	DNC_TASK_COMP_TASK_FETCH1_MODE_ESTF,
};

enum dnc_task_ldudma_task_fetch1_mode {
	DNC_TASK_LDUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_LDUDMA_TASK_FETCH1_MODE_EATF,
	DNC_TASK_LDUDMA_TASK_FETCH1_MODE_ESTF,
};

enum dnc_task_lpudma_task_fetch1_mode {
	DNC_TASK_LPUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_LPUDMA_TASK_FETCH1_MODE_EATF,
	DNC_TASK_LPUDMA_TASK_FETCH1_MODE_ESTF,
};

enum dnc_task_studma_task_fetch1_mode {
	DNC_TASK_STUDMA_TASK_FETCH1_MODE_FOFF,
	DNC_TASK_STUDMA_TASK_FETCH1_MODE_EATF,
	DNC_TASK_STUDMA_TASK_FETCH1_MODE_ESTF,
};

enum dnc_task_wait_handle_op_mode {
	DNC_TASK_WAIT_HANDLE_OP_MODE_G0,
	DNC_TASK_WAIT_HANDLE_OP_MODE_G1,
	DNC_TASK_WAIT_HANDLE_OP_MODE_D0 = 8,
	DNC_TASK_WAIT_HANDLE_OP_MODE_D1,
};

#endif /* _G_DNC_TASK_32B_EVT1_H_*/
