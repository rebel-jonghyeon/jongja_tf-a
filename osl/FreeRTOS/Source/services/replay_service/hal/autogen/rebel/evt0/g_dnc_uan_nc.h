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

#ifndef _G_DNC_UAN_NC_EVT0_H_
#define _G_DNC_UAN_NC_EVT0_H_

#define ADDR_OFFSET_DNC_UAN_NC_SPR_0123 0x004
#define ADDR_OFFSET_DNC_UAN_NC_TLB_CTRL 0x10C

union dnc_uan_nc_spr_0123 {
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

union dnc_uan_nc_tlb_ctrl {
	struct __attribute__((packed)) {
		uint32_t tlb_clear : 1;
		uint32_t reserved0 : 3;
		uint32_t tlb_default_mode : 4;
		uint32_t reserved1 : 24;
	};
	uint32_t bits;
};

enum dnc_uan_nc_spr_0123_prog_exe {
	DNC_UAN_NC_SPR_0123_PROG_EXE_DISABLE,
	DNC_UAN_NC_SPR_0123_PROG_EXE_ENABLE,
};

enum dnc_uan_nc_spr_0123_exe_mode {
	DNC_UAN_NC_SPR_0123_EXE_MODE_NORMAL,
	DNC_UAN_NC_SPR_0123_EXE_MODE_PROMPT,
};

enum dnc_uan_nc_spr_0123_throttle_ctrl {
	DNC_UAN_NC_SPR_0123_THROTTLE_CTRL_DISABLE,
	DNC_UAN_NC_SPR_0123_THROTTLE_CTRL_ENABLE,
};

enum dnc_uan_nc_spr_0123_zero_gating {
	DNC_UAN_NC_SPR_0123_ZERO_GATING_DISABLE,
	DNC_UAN_NC_SPR_0123_ZERO_GATING_ENABLE,
};

#endif /* _G_DNC_UAN_NC_EVT0_H_*/
