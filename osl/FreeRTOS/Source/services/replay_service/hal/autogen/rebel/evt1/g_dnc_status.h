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

#ifndef _G_DNC_STATUS_EVT1_H_
#define _G_DNC_STATUS_EVT1_H_

#define ADDR_OFFSET_DNC_STATUS_COMP_ACC6   0x0D8
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC6 0x0F8
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC6 0x118
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC6 0x138

union dnc_status_comp_acc6 {
	struct __attribute__((packed)) {
		uint32_t handle_discard : 16;
		uint32_t handle_prog_off : 16;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc6 {
	struct __attribute__((packed)) {
		uint32_t handle_discard : 16;
		uint32_t handle_prog_off : 16;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc6 {
	struct __attribute__((packed)) {
		uint32_t handle_discard : 16;
		uint32_t handle_prog_off : 16;
	};
	uint32_t bits;
};

union dnc_status_studma_acc6 {
	struct __attribute__((packed)) {
		uint32_t handle_discard : 16;
		uint32_t handle_prog_off : 16;
	};
	uint32_t bits;
};

#endif /* _G_DNC_STATUS_EVT1_H_*/
