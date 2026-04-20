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

#ifndef _G_DNC_UAN_BASE_COMMON_H_
#define _G_DNC_UAN_BASE_COMMON_H_

#define ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO 0x000
#define ADDR_OFFSET_DNC_UAN_BASE_RSVD2	   0x004
#define ADDR_OFFSET_DNC_UAN_BASE_RSVD3	   0x008
#define ADDR_OFFSET_DNC_UAN_BASE_RSVD4	   0x00C

union dnc_uan_base_unit_info {
	struct __attribute__((packed)) {
		uint32_t core_id : 4;
		uint32_t unit_id : 4;
		uint32_t sub_unit_id : 4;
		uint32_t op : 4;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_uan_base_rsvd2 {
	struct __attribute__((packed)) {
		uint32_t rsvd : 32;
	};
	uint32_t bits;
};

union dnc_uan_base_rsvd3 {
	struct __attribute__((packed)) {
		uint32_t rsvd : 32;
	};
	uint32_t bits;
};

union dnc_uan_base_rsvd4 {
	struct __attribute__((packed)) {
		uint32_t rsvd : 32;
	};
	uint32_t bits;
};

#endif /* _G_DNC_UAN_BASE_COMMON_H_*/
