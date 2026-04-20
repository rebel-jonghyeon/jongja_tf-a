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

#ifndef _G_DNC_UAN_COMP_EVT1_H_
#define _G_DNC_UAN_COMP_EVT1_H_

#define ADDR_OFFSET_DNC_UAN_COMP_UNIT_INFO 0x000
#define ADDR_OFFSET_DNC_UAN_COMP_SPR_0123  0x004
#define ADDR_OFFSET_DNC_UAN_COMP_SPR_45	   0x008
#define ADDR_OFFSET_DNC_UAN_COMP_SPR_67	   0x00C
#define ADDR_OFFSET_DNC_UAN_COMP_UNIT_CFG  0x100
#define ADDR_OFFSET_DNC_UAN_COMP_PS_CFG_0  0x104
#define ADDR_OFFSET_DNC_UAN_COMP_PS_CFG_1  0x108
#define ADDR_OFFSET_DNC_UAN_COMP_PCFG_00   0x200
#define ADDR_OFFSET_DNC_UAN_COMP_PCFG_01   0x204
#define ADDR_OFFSET_DNC_UAN_COMP_PCFG_02   0x208
#define ADDR_OFFSET_DNC_UAN_COMP_PCFG_03   0x20C
#define ADDR_OFFSET_DNC_UAN_COMP_PSTAT_00  0x210
#define ADDR_OFFSET_DNC_UAN_COMP_PSTAT_01  0x214
#define ADDR_OFFSET_DNC_UAN_COMP_PSTAT_02  0x218
#define ADDR_OFFSET_DNC_UAN_COMP_PSTAT_03  0x21C
#define ADDR_OFFSET_DNC_UAN_COMP_USTAT_00  0x220
#define ADDR_OFFSET_DNC_UAN_COMP_USTAT_01  0x224
#define ADDR_OFFSET_DNC_UAN_COMP_USTAT_02  0x228
#define ADDR_OFFSET_DNC_UAN_COMP_USTAT_03  0x230
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_0	   0x300
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_1	   0x304
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_2	   0x308
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_3	   0x30C
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_4	   0x310
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_5	   0x314
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_6	   0x318
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_7	   0x31C
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_8	   0x320
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_9	   0x324
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_10	   0x328
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_11	   0x32C
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_12	   0x330
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_13	   0x334
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_14	   0x338
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_15	   0x33C
#define ADDR_OFFSET_DNC_UAN_COMP_JCR_FIFO  0x3FC

union dnc_uan_comp_unit_info {
	struct __attribute__((packed)) {
		uint32_t core_id : 4;
		uint32_t unit_id : 4;
		uint32_t sub_unit_id : 4;
		uint32_t op : 4;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_spr_0123 {
	struct __attribute__((packed)) {
		uint32_t prog_exe : 1;
		uint32_t exe_mode : 1;
		uint32_t reserved0 : 1;
		uint32_t throttle_ctrl : 1;
		uint32_t overflow_mode : 1;
		uint32_t zero_gating : 1;
		uint32_t reserved1 : 1;
		uint32_t exe_done : 1;
		uint32_t compute_precision : 4;
		uint32_t compute_precision_mode : 4;
		uint32_t exception_en_mask : 6;
		uint32_t timeout_cfg : 2;
		uint32_t invalid_op : 1;
		uint32_t fp_exc : 1;
		uint32_t machine_exc : 1;
		uint32_t unaligned_mem_acc_exc : 1;
		uint32_t prog_err : 1;
		uint32_t hw_fault : 1;
		uint32_t timeout : 1;
		uint32_t external_abort : 1;
	};
	uint32_t bits;
};

union dnc_uan_comp_spr_45 {
	struct __attribute__((packed)) {
		uint32_t machine_exc_en_mask : 16;
		uint32_t machine_exc_type : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_spr_67 {
	struct __attribute__((packed)) {
		uint32_t fp_exc_report_en : 1;
		uint32_t fp_exc_slice : 3;
		uint32_t fp_exc_mask : 8;
		uint32_t reserved : 12;
		uint32_t exc_pc : 8;
	};
	uint32_t bits;
};

union dnc_uan_comp_unit_cfg {
	struct __attribute__((packed)) {
		uint32_t if_cfg : 3;
	};
	uint32_t bits;
};

union dnc_uan_comp_ps_cfg_0 {
	struct __attribute__((packed)) {
		uint32_t ps_en : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

union dnc_uan_comp_ps_cfg_1 {
	struct __attribute__((packed)) {
		uint32_t len : 8;
		uint32_t init : 8;
		uint32_t thres : 8;
		uint32_t skew : 8;
	};
	uint32_t bits;
};

union dnc_uan_comp_pcfg_00 {
	struct __attribute__((packed)) {
		uint32_t profile_mode : 2;
		uint32_t profile_cycle_src : 1;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};

union dnc_uan_comp_pcfg_01 {
	struct __attribute__((packed)) {
		uint32_t profile_start : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_pcfg_02 {
	struct __attribute__((packed)) {
		uint32_t profile_window : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_pcfg_03 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_pstat_00 {
	struct __attribute__((packed)) {
		uint32_t count_cycle : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_pstat_01 {
	struct __attribute__((packed)) {
		uint32_t count_fetch : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_pstat_02 {
	struct __attribute__((packed)) {
		uint32_t prog_status : 2;
		uint32_t prog_pc : 8;
		uint32_t prog_lnlc : 5;
		uint32_t prog_lccr : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_pstat_03 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union dnc_uan_comp_ustat_00 {
	struct __attribute__((packed)) {
		uint32_t unit_stat0 : 16;
		uint32_t unit_stat1 : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_ustat_01 {
	struct __attribute__((packed)) {
		uint32_t unit_stat2 : 16;
		uint32_t unit_stat3 : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_ustat_02 {
	struct __attribute__((packed)) {
		uint32_t unit_stat4 : 16;
		uint32_t unit_stat5 : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_ustat_03 {
	struct __attribute__((packed)) {
		uint32_t unit_stat8 : 16;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_0 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_1 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_2 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_3 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_4 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_5 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_6 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_7 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_8 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_9 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_10 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_11 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_12 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_13 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_14 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_15 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_comp_jcr_fifo {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

enum dnc_uan_comp_spr_0123_prog_exe {
	DNC_UAN_COMP_SPR_0123_PROG_EXE_DISABLE,
	DNC_UAN_COMP_SPR_0123_PROG_EXE_ENABLE,
};

enum dnc_uan_comp_spr_0123_exe_mode {
	DNC_UAN_COMP_SPR_0123_EXE_MODE_NORMAL,
	DNC_UAN_COMP_SPR_0123_EXE_MODE_PROMPT,
};

enum dnc_uan_comp_spr_0123_throttle_ctrl {
	DNC_UAN_COMP_SPR_0123_THROTTLE_CTRL_DISABLE,
	DNC_UAN_COMP_SPR_0123_THROTTLE_CTRL_ENABLE,
};

enum dnc_uan_comp_spr_0123_zero_gating {
	DNC_UAN_COMP_SPR_0123_ZERO_GATING_DISABLE,
	DNC_UAN_COMP_SPR_0123_ZERO_GATING_ENABLE,
};

enum dnc_uan_comp_pcfg_00_profile_cycle_src {
	DNC_UAN_COMP_PCFG_00_PROFILE_CYCLE_SRC_CLK_CYCLE,
	DNC_UAN_COMP_PCFG_00_PROFILE_CYCLE_SRC_FETCH_CNT,
};

#endif /* _G_DNC_UAN_COMP_EVT1_H_*/
