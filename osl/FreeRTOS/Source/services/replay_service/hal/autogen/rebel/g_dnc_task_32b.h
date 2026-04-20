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

#ifndef _G_DNC_TASK_32B_COMMON_H_
#define _G_DNC_TASK_32B_COMMON_H_

#ifndef EVT_VER
#error "EVT_VER must be defined (replay_service: CMake -DEVT_VER=0 or 1)"
#endif

#define ADDR_OFFSET_DNC_TASK_DESC_ID			0x000
#define ADDR_OFFSET_DNC_TASK_DESC_MODE			0x004
#define ADDR_OFFSET_DNC_TASK_DESC_PROG0			0x008
#define ADDR_OFFSET_DNC_TASK_DESC_PROG1			0x00C
#define ADDR_OFFSET_DNC_TASK_DESC_PROG2			0x010
#define ADDR_OFFSET_DNC_TASK_DESC_CFG0			0x018
#define ADDR_OFFSET_DNC_TASK_DESC_CFG1			0x01C
#define ADDR_OFFSET_DNC_TASK_Q_CREDIT			0x038
#define ADDR_OFFSET_DNC_TASK_ENQ_TASK0			0x040
#define ADDR_OFFSET_DNC_TASK_ENQ_TASK1			0x044
#define ADDR_OFFSET_DNC_TASK_ENQ_TASK2			0x048
#define ADDR_OFFSET_DNC_TASK_ENQ_TASK3			0x04C
#define ADDR_OFFSET_DNC_TASK_RUN_TASK0			0x050
#define ADDR_OFFSET_DNC_TASK_RUN_TASK1			0x054
#define ADDR_OFFSET_DNC_TASK_RUN_TASK2			0x058
#define ADDR_OFFSET_DNC_TASK_RUN_TASK3			0x05C
#define ADDR_OFFSET_DNC_TASK_DONE_TASK0			0x060
#define ADDR_OFFSET_DNC_TASK_DONE_TASK1			0x064
#define ADDR_OFFSET_DNC_TASK_DONE_TASK2			0x068
#define ADDR_OFFSET_DNC_TASK_DONE_TASK3			0x06C
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_ENQ0		0x070
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_ENQ1		0x074
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_DEQ0		0x078
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_DEQ1		0x07C
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE0		0x080
#define ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1		0x084
#define ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH0	0x088
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_ENQ0	0x090
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_ENQ1	0x094
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DEQ0	0x098
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DEQ1	0x09C
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE0	0x0A0
#define ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1	0x0A4
#define ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH0 0x0A8
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_ENQ0	0x0B0
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_ENQ1	0x0B4
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DEQ0	0x0B8
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DEQ1	0x0BC
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE0	0x0C0
#define ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE1	0x0C4
#define ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH0 0x0C8
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_ENQ0	0x0D0
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_ENQ1	0x0D4
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DEQ0	0x0D8
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DEQ1	0x0DC
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE0	0x0E0
#define ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE1	0x0E4
#define ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH0 0x0E8
#define ADDR_OFFSET_DNC_TASK_TIMEOUT0			0x0F0
#define ADDR_OFFSET_DNC_TASK_TIMEOUT1			0x0F4
#define ADDR_OFFSET_DNC_TASK_WAIT_CNT			0x0F8
#define ADDR_OFFSET_DNC_DELAY					0x0FC

#if EVT_VER == 1
#include "evt1/g_dnc_task_32b.h"
#else
#include "evt0/g_dnc_task_32b.h"
#endif

union dnc_task_desc_id {
	struct __attribute__((packed)) {
		uint32_t fid : 4;
		uint32_t ctx_id : 8;
		uint32_t thid : 4;
		uint32_t cmd_id : 16;
	} id;
	uint32_t bits;
};

union dnc_task_desc_mode {
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

union dnc_task_desc_prog0 {
	struct __attribute__((packed)) {
		uint32_t isize : 10;
		uint32_t rsvd10 : 22;
	} comp;
	struct __attribute__((packed)) {
		uint32_t csize : 15;
		uint32_t psize : 12;
		uint32_t noch : 5;
	} ldudma;
	struct __attribute__((packed)) {
		uint32_t csize : 15;
		uint32_t psize : 12;
		uint32_t noch : 5;
	} lpudma;
	struct __attribute__((packed)) {
		uint32_t csize : 15;
		uint32_t psize : 12;
		uint32_t noch : 5;
	} studma;
	uint32_t bits;
};

union dnc_task_desc_prog1 {
	struct __attribute__((packed)) {
		uint32_t noh_rd : 8;
		uint32_t noh_wr : 8;
		uint32_t rsvd16 : 16;
	} comp;
	struct __attribute__((packed)) {
		uint32_t src : 32;
	} ldudma;
	struct __attribute__((packed)) {
		uint32_t src : 32;
	} lpudma;
	struct __attribute__((packed)) {
		uint32_t dst : 32;
	} studma;
	uint32_t bits;
};

union dnc_task_desc_prog2 {
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

#if EVT_VER == 0
/* EVT0 version of dnc_task_desc_tsync */
union dnc_task_desc_tsync {
	struct __attribute__((packed)) {
		uint32_t chk_code : 10;
		uint32_t set_dest : 6;
		uint32_t set_code : 16;
	};
	uint32_t bits;
};
#endif
/* EVT1 version is defined in evt1/g_dnc_task_32b.h */

union dnc_task_desc_cfg0 {
	struct __attribute__((packed)) {
		uint32_t config_data : 32;
	} general_cofig_mode_1;
	struct __attribute__((packed)) {
		uint32_t paddr : 19;
		uint32_t vaddr_l : 13;
	} tlb_setting_mode_2;
	uint32_t bits;
};

union dnc_task_desc_cfg1 {
	struct __attribute__((packed)) {
		uint32_t data : 12;
		uint32_t addr : 13;
		uint32_t auto_fetch_pfix : 1;
		uint32_t mode : 2;
		uint32_t queue : 2;
		uint32_t sole : 1;
		uint32_t itdone : 1;
	} general_config_mode_1;
	struct __attribute__((packed)) {
		uint32_t vaddr_h : 6;
//		uint32_t tlb_attr : 6;
		uint32_t page_size : 4;
		uint32_t burst_length : 2;
		uint32_t tlb_idx : 8;
		uint32_t tlb_valid : 1;
		uint32_t tlb_clr_mode : 2;
		uint32_t tlb_clr_type : 1;
		uint32_t rsvd24	: 1;
		uint32_t auto_fetch_pfix : 1;
		uint32_t mode : 2;
		uint32_t queue : 2;
		uint32_t sole : 1;
		uint32_t itdone : 1;
	} tlb_setting_mode_2;
	uint32_t bits;
};

union dnc_task_q_credit {
	struct __attribute__((packed)) {
		uint32_t comp : 8;
		uint32_t ldudma : 8;
		uint32_t lpudma : 8;
		uint32_t studma : 8;
	};
	uint32_t bits;
};

union dnc_task_enq_task0 {
	struct __attribute__((packed)) {
		uint32_t comp : 32;
	};
	uint32_t bits;
};

union dnc_task_enq_task1 {
	struct __attribute__((packed)) {
		uint32_t ldudma : 32;
	};
	uint32_t bits;
};

union dnc_task_enq_task2 {
	struct __attribute__((packed)) {
		uint32_t lpudma : 32;
	};
	uint32_t bits;
};

union dnc_task_enq_task3 {
	struct __attribute__((packed)) {
		uint32_t studma : 32;
	};
	uint32_t bits;
};

union dnc_task_run_task0 {
	struct __attribute__((packed)) {
		uint32_t comp : 32;
	};
	uint32_t bits;
};

union dnc_task_run_task1 {
	struct __attribute__((packed)) {
		uint32_t ldudma : 32;
	};
	uint32_t bits;
};

union dnc_task_run_task2 {
	struct __attribute__((packed)) {
		uint32_t lpudma : 32;
	};
	uint32_t bits;
};

union dnc_task_run_task3 {
	struct __attribute__((packed)) {
		uint32_t studma : 32;
	};
	uint32_t bits;
};

union dnc_task_done_task0 {
	struct __attribute__((packed)) {
		uint32_t comp : 32;
	};
	uint32_t bits;
};

union dnc_task_done_task1 {
	struct __attribute__((packed)) {
		uint32_t ldudma : 32;
	};
	uint32_t bits;
};

union dnc_task_done_task2 {
	struct __attribute__((packed)) {
		uint32_t lpudma : 32;
	};
	uint32_t bits;
};

union dnc_task_done_task3 {
	struct __attribute__((packed)) {
		uint32_t studma : 32;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_enq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_enq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_deq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_deq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_done0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_comp_rpt_done1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_comp_task_fetch0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_enq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_enq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_deq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_deq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_done0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_ldudma_rpt_done1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_ldudma_task_fetch0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_enq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_enq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_deq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_deq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_done0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_lpudma_rpt_done1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_lpudma_task_fetch0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_enq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_enq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_deq0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_deq1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_done0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_studma_rpt_done1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t mode : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_task_studma_task_fetch0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_task_timeout0 {
	struct __attribute__((packed)) {
		uint32_t threshold : 32;
	};
	uint32_t bits;
};

union dnc_task_timeout1 {
	struct __attribute__((packed)) {
		uint32_t threshold : 16;
		uint32_t mode : 4;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_task_wait_cnt {
	struct __attribute__((packed)) {
		uint32_t comp : 8;
		uint32_t ldudma : 8;
		uint32_t lpudma : 8;
		uint32_t studma : 8;
	};
	uint32_t bits;
};


#if EVT_VER == 0
/* EVT0 version of dnc_task_delay */
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
#endif
/* EVT1 version is defined in evt1/g_dnc_task_32b.h */

enum dnc_task_desc_mode_tsync_chk {
	DNC_TASK_DESC_MODE_TSYNC_CHK_BYPS,
	DNC_TASK_DESC_MODE_TSYNC_CHK_QV,
	DNC_TASK_DESC_MODE_TSYNC_CHK_QB,
	DNC_TASK_DESC_MODE_TSYNC_CHK_TC0,
	DNC_TASK_DESC_MODE_TSYNC_CHK_TC1,
	DNC_TASK_DESC_MODE_TSYNC_CHK_RSVD5,
	DNC_TASK_DESC_MODE_TSYNC_CHK_RSVD6,
	DNC_TASK_DESC_MODE_TSYNC_CHK_RSVD7,
};

enum dnc_task_desc_mode_tsync_set {
	DNC_TASK_DESC_MODE_TSYNC_SET_BYPS,
	DNC_TASK_DESC_MODE_TSYNC_SET_QMD,
	DNC_TASK_DESC_MODE_TSYNC_SET_QAD,
	DNC_TASK_DESC_MODE_TSYNC_SET_RSVD3,
	DNC_TASK_DESC_MODE_TSYNC_SET_TCMD,
	DNC_TASK_DESC_MODE_TSYNC_SET_TCAD,
	DNC_TASK_DESC_MODE_TSYNC_SET_PDCC,
	DNC_TASK_DESC_MODE_TSYNC_SET_SCND,
};

enum dnc_task_desc_prog2_qos {
	DNC_TASK_DESC_PROG2_QOS_QL,
	DNC_TASK_DESC_PROG2_QOS_QH,
};

enum dnc_task_desc_prog2_insist {
	DNC_TASK_DESC_PROG2_INSIST_NORM,
	DNC_TASK_DESC_PROG2_INSIST_URGT,
};

enum dnc_task_desc_cfg1_mode {
	DNC_TASK_DESC_CFG1_MODE_NOP,
	DNC_TASK_DESC_CFG1_MODE_GCFG,
	DNC_TASK_DESC_CFG1_MODE_TLB,
	DNC_TASK_DESC_CFG1_MODE_PCFG,
};

enum dnc_task_desc_cfg1_queue {
	DNC_TASK_DESC_CFG1_QUEUE_COMP,
	DNC_TASK_DESC_CFG1_QUEUE_LDUDMA,
	DNC_TASK_DESC_CFG1_QUEUE_LPUDMA,
	DNC_TASK_DESC_CFG1_QUEUE_STUDMA,
};

enum dnc_task_comp_rpt_enq1_mode {
	DNC_TASK_COMP_RPT_ENQ1_MODE_ROFF,
	DNC_TASK_COMP_RPT_ENQ1_MODE_SRCA,
};

enum dnc_task_comp_rpt_deq1_mode {
	DNC_TASK_COMP_RPT_DEQ1_MODE_ROFF,
	DNC_TASK_COMP_RPT_DEQ1_MODE_SRCA,
};

enum dnc_task_comp_rpt_done1_mode {
	DNC_TASK_COMP_RPT_DONE1_MODE_ROFF,
	DNC_TASK_COMP_RPT_DONE1_MODE_SRCA,
	DNC_TASK_COMP_RPT_DONE1_MODE_SRRF,
};

enum dnc_task_ldudma_rpt_enq1_mode {
	DNC_TASK_LDUDMA_RPT_ENQ1_MODE_ROFF,
	DNC_TASK_LDUDMA_RPT_ENQ1_MODE_SRCA,
};

enum dnc_task_ldudma_rpt_deq1_mode {
	DNC_TASK_LDUDMA_RPT_DEQ1_MODE_ROFF,
	DNC_TASK_LDUDMA_RPT_DEQ1_MODE_SRCA,
};

enum dnc_task_ldudma_rpt_done1_mode {
	DNC_TASK_LDUDMA_RPT_DONE1_MODE_ROFF,
	DNC_TASK_LDUDMA_RPT_DONE1_MODE_SRCA,
	DNC_TASK_LDUDMA_RPT_DONE1_MODE_SRRF,
};

enum dnc_task_lpudma_rpt_enq1_mode {
	DNC_TASK_LPUDMA_RPT_ENQ1_MODE_ROFF,
	DNC_TASK_LPUDMA_RPT_ENQ1_MODE_SRCA,
};

enum dnc_task_lpudma_rpt_deq1_mode {
	DNC_TASK_LPUDMA_RPT_DEQ1_MODE_ROFF,
	DNC_TASK_LPUDMA_RPT_DEQ1_MODE_SRCA,
};

enum dnc_task_lpudma_rpt_done1_mode {
	DNC_TASK_LPUDMA_RPT_DONE1_MODE_ROFF,
	DNC_TASK_LPUDMA_RPT_DONE1_MODE_SRCA,
	DNC_TASK_LPUDMA_RPT_DONE1_MODE_SRRF,
};

enum dnc_task_studma_rpt_enq1_mode {
	DNC_TASK_STUDMA_RPT_ENQ1_MODE_ROFF,
	DNC_TASK_STUDMA_RPT_ENQ1_MODE_SRCA,
};

enum dnc_task_studma_rpt_deq1_mode {
	DNC_TASK_STUDMA_RPT_DEQ1_MODE_ROFF,
	DNC_TASK_STUDMA_RPT_DEQ1_MODE_SRCA,
};

enum dnc_task_studma_rpt_done1_mode {
	DNC_TASK_STUDMA_RPT_DONE1_MODE_ROFF,
	DNC_TASK_STUDMA_RPT_DONE1_MODE_SRCA,
	DNC_TASK_STUDMA_RPT_DONE1_MODE_SRRF,
};

#endif /* _G_DNC_TASK_32B_COMMON_H_*/
