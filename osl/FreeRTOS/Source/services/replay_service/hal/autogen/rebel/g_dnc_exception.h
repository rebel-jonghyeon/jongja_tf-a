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

#ifndef _G_DNC_EXCEPTION_COMMON_H_
#define _G_DNC_EXCEPTION_COMMON_H_

#define ADDR_OFFSET_DNC_EXCEPTION_EXCEPTION0		   0x000
#define ADDR_OFFSET_DNC_EXCEPTION_EXCEPTION2		   0x008
#define ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK0		   0x020
#define ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK1		   0x024
#define ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK2		   0x028
#define ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK3		   0x02C
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK0		   0x030
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK1		   0x034
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK2		   0x038
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK3		   0x03C
#define ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK0			   0x040
#define ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK1			   0x044
#define ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK2			   0x048
#define ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK3			   0x04C
#define ADDR_OFFSET_DNC_EXCEPTION_DO				   0x060
#define ADDR_OFFSET_DNC_EXCEPTION_TRIG				   0x064
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_CONFIG		   0x068
#define ADDR_OFFSET_DNC_EXCEPTION_ABORT_STATUS		   0x06C
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_MODE		   0x080
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_SIZE		   0x084
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_DEST0		   0x088
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_DEST1		   0x08C
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_SRC			   0x094
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_UAN			   0x098
#define ADDR_OFFSET_DNC_EXCEPTION_CDUMP_STATUS		   0x09C
#define ADDR_OFFSET_DNC_EXCEPTION_CHK_EXCEPTION0	   0x0C0
#define ADDR_OFFSET_DNC_EXCEPTION_CHK_EXCEPTION1	   0x0C4
#define ADDR_OFFSET_DNC_EXCEPTION_CHK_EXCEPTION2	   0x0C8
#define ADDR_OFFSET_DNC_EXCEPTION_CHK_EXCEPTION3	   0x0CC
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_00 0x0D0
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_01 0x0D4
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_02 0x0D8
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_03 0x0DC
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_04 0x0E0
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_05 0x0E4
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_06 0x0E8
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_07 0x0EC
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_08 0x0F0
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_09 0x0F4
#define ADDR_OFFSET_DNC_EXCEPTION_TLB_MISS_RPT_MORE_10 0x0F8

union dnc_exception_exception0 {
	struct __attribute__((packed)) {
		uint32_t comp_tout_run : 1;
		uint32_t comp_tout_pre : 1;
		uint32_t comp_tout_fetch : 1;
		uint32_t comp_ovf : 1;
		uint32_t comp_malf_fetch0 : 1;
		uint32_t comp_malf_fetch1 : 1;
		uint32_t comp_perr : 1;
		uint32_t comp_config_err : 1;
		uint32_t ldudma_tout_run : 1;
		uint32_t ldudma_tout_pre : 1;
		uint32_t ldudma_tout_fetch : 1;
		uint32_t ldudma_ovf : 1;
		uint32_t ldudma_malf_fetch0 : 1;
		uint32_t ldudma_malf_fetch1 : 1;
		uint32_t ldudma_perr : 1;
		uint32_t ldudma_config_err : 1;
		uint32_t lpudma_tout_run : 1;
		uint32_t lpudma_tout_pre : 1;
		uint32_t lpudma_tout_fetch : 1;
		uint32_t lpudma_ovf : 1;
		uint32_t lpudma_malf_fetch0 : 1;
		uint32_t lpudma_malf_fetch1 : 1;
		uint32_t lpudma_perr : 1;
		uint32_t lpudma_config_err : 1;
		uint32_t studma_tout_run : 1;
		uint32_t studma_tout_pre : 1;
		uint32_t studma_tout_fetch : 1;
		uint32_t studma_ovf : 1;
		uint32_t studma_malf_fetch0 : 1;
		uint32_t studma_malf_fetch1 : 1;
		uint32_t studma_perr : 1;
		uint32_t studma_config_err : 1;
	};
	uint32_t bits;
};

union dnc_exception_exception2 {
	struct __attribute__((packed)) {
		uint32_t ext_dbus_rd_resp0 : 1;
		uint32_t ext_dbus_rd_resp1 : 1;
		uint32_t ext_dbus_wr_resp0 : 1;
		uint32_t ext_dbus_wr_resp1 : 1;
		uint32_t ext_cbus_rd_resp0 : 1;
		uint32_t ext_cbus_rd_resp1 : 1;
		uint32_t ext_cbus_wr_resp0 : 1;
		uint32_t ext_cbus_wr_resp1 : 1;
		uint32_t tlb_miss_comp : 1;
		uint32_t tlb_miss_ldudma : 1;
		uint32_t tlb_miss_lpudma : 1;
		uint32_t tlb_miss_studma : 1;
		uint32_t rsvd12 : 1;
		uint32_t rsvd13 : 1;
		uint32_t rsvd14 : 1;
		uint32_t rsvd15 : 1;
		uint32_t sp_stuck_at_nclu0 : 1;
		uint32_t sp_stuck_at_ncsu0 : 1;
		uint32_t sp_stuck_at_nclu1 : 1;
		uint32_t sp_stuck_at_ncsu1 : 1;
		uint32_t sp_stuck_at_wrslv : 1;
		uint32_t sp_stuck_at_rdslv : 1;
		uint32_t rsvd22 : 1;
		uint32_t rsvd23 : 1;
		uint32_t rsvd24 : 1;
		uint32_t rsvd25 : 1;
		uint32_t rsvd26 : 1;
		uint32_t rsvd27 : 1;
		uint32_t rsvd28 : 1;
		uint32_t rsvd29 : 1;
		uint32_t rsvd30 : 1;
		uint32_t rsvd31 : 1;
	};
	uint32_t bits;
};

union dnc_exception_intr_mask0 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_intr_mask1 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_intr_mask2 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_intr_mask3 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_abort_mask0 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_abort_mask1 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_abort_mask2 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_abort_mask3 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_aeh_mask0 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_aeh_mask1 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_aeh_mask2 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_aeh_mask3 {
	struct __attribute__((packed)) {
		uint32_t inv : 32;
	};
	uint32_t bits;
};

union dnc_exception_do {
	struct __attribute__((packed)) {
		uint32_t en_intr : 1;
		uint32_t en_auto_pause_comp : 1;
		uint32_t en_auto_pause_ldudma : 1;
		uint32_t en_auto_pause_lpudma : 1;
		uint32_t en_auto_pause_studma : 1;
		uint32_t en_auto_cdump : 1;
		uint32_t en_implicit_chk : 1;
		uint32_t en_abort : 1;
		uint32_t rsvd8 : 24;
	};
	uint32_t bits;
};

union dnc_exception_trig {
	struct __attribute__((packed)) {
		uint32_t clr_intr : 1;
		uint32_t clr_exception : 1;
		uint32_t clr_status : 1;
		uint32_t cdump : 1;
		uint32_t abort : 1;
		uint32_t abort_injec : 1;
		uint32_t rsvd6 : 26;
	};
	uint32_t bits;
};

union dnc_exception_abort_config {
	struct __attribute__((packed)) {
		uint32_t propagate_en : 1;
		uint32_t wait_cdump : 1;
		uint32_t core_reset_en : 1;
		uint32_t qclr_en : 1;
		uint32_t rsvd4 : 4;
		uint32_t propagate_target : 8;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_exception_abort_status {
	struct __attribute__((packed)) {
		uint32_t aborted : 1;
		uint32_t rsvd1 : 7;
		uint32_t abort_seq : 4;
		uint32_t rsvd12 : 20;
	};
	uint32_t bits;
};

union dnc_exception_cdump_mode {
	struct __attribute__((packed)) {
		uint32_t rsvd0 : 2;
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

union dnc_exception_cdump_size {
	struct __attribute__((packed)) {
		uint32_t dcrn : 16;
		uint32_t uan : 16;
	};
	uint32_t bits;
};

union dnc_exception_cdump_dest0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_exception_cdump_dest1 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_exception_cdump_src {
	struct __attribute__((packed)) {
		uint32_t dcrn : 16;
		uint32_t uan : 16;
	};
	uint32_t bits;
};

union dnc_exception_cdump_uan {
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
		uint32_t rsvd19 : 13;
	};
	uint32_t bits;
};

union dnc_exception_cdump_status {
	struct __attribute__((packed)) {
		uint32_t ongoing : 1;
		uint32_t rsvd1 : 3;
		uint32_t done_cnt : 4;
		uint32_t rsvd8 : 8;
		uint32_t exception : 16;
	};
	uint32_t bits;
};

union dnc_exception_chk_exception0 {
	struct __attribute__((packed)) {
		uint32_t log : 32;
	};
	uint32_t bits;
};

union dnc_exception_chk_exception1 {
	struct __attribute__((packed)) {
		uint32_t log : 32;
	};
	uint32_t bits;
};

union dnc_exception_chk_exception2 {
	struct __attribute__((packed)) {
		uint32_t log : 32;
	};
	uint32_t bits;
};

union dnc_exception_chk_exception3 {
	struct __attribute__((packed)) {
		uint32_t log : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_00 {
	struct __attribute__((packed)) {
		uint32_t invoker_00 : 1;
		uint32_t invoker_01 : 1;
		uint32_t invoker_02 : 1;
		uint32_t invoker_03 : 1;
		uint32_t invoker_04 : 1;
		uint32_t invoker_05 : 1;
		uint32_t invoker_06 : 1;
		uint32_t invoker_07 : 1;
		uint32_t invoker_08 : 1;
		uint32_t invoker_09 : 1;
		uint32_t rsvd10 : 22;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_01 {
	struct __attribute__((packed)) {
		uint32_t addr0 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_02 {
	struct __attribute__((packed)) {
		uint32_t addr1 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_03 {
	struct __attribute__((packed)) {
		uint32_t addr2 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_04 {
	struct __attribute__((packed)) {
		uint32_t addr3 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_05 {
	struct __attribute__((packed)) {
		uint32_t addr4 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_06 {
	struct __attribute__((packed)) {
		uint32_t addr5 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_07 {
	struct __attribute__((packed)) {
		uint32_t addr6 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_08 {
	struct __attribute__((packed)) {
		uint32_t addr7 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_09 {
	struct __attribute__((packed)) {
		uint32_t addr8 : 32;
	};
	uint32_t bits;
};

union dnc_exception_tlb_miss_rpt_more_10 {
	struct __attribute__((packed)) {
		uint32_t addr9 : 32;
	};
	uint32_t bits;
};

enum dnc_exception_cdump_mode_ersp_method {
	DNC_EXCEPTION_CDUMP_MODE_ERSP_METHOD_ERSP_M0,
	DNC_EXCEPTION_CDUMP_MODE_ERSP_METHOD_ERSP_M1,
	DNC_EXCEPTION_CDUMP_MODE_ERSP_METHOD_ERSP_M2,
	DNC_EXCEPTION_CDUMP_MODE_ERSP_METHOD_ERSP_M3,
};

enum dnc_exception_cdump_mode_done_policy {
	DNC_EXCEPTION_CDUMP_MODE_DONE_POLICY_DONE_G,
	DNC_EXCEPTION_CDUMP_MODE_DONE_POLICY_DONE_R,
};

#endif /* _G_DNC_EXCEPTION_COMMON_H_*/
