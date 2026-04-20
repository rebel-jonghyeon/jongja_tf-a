/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _G_CMD_DESCR_SYNC_REBEL_H_
#define _G_CMD_DESCR_SYNC_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_SYNC_ARCH_MAJOR 0
#define CMD_DESCR_SYNC_ARCH_MINOR 9
#define CMD_DESCR_SYNC_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_PUT_SYNC_DEVICE_MASK 16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_MASK	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_PUT_SYNC_ID		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_0		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_1		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_2		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_3		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_4		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_5		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_6		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_7		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_8		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_9		   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_10	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_11	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_12	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_13	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_14	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_MULTI_DEVICE_GET_SYNC_ID_15	   16
#define BIT_WIDTH_CMD_DESCR_SYNC_EXT_GET_SYNC_MASK_LO			   64
#define BIT_WIDTH_CMD_DESCR_SYNC_EXT_GET_SYNC_MASK_HI			   64
#define BIT_WIDTH_CMD_DESCR_SYNC_EXT_PUT_SYNC_MASK_LO			   64
#define BIT_WIDTH_CMD_DESCR_SYNC_EXT_PUT_SYNC_MASK_HI			   64
#define BIT_WIDTH_CMD_DESCR_SYNC_SYNC_TYPE						   1

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_md_sync_mask {
	uint32_t multi_device_put_sync_device_mask : 16;
	uint32_t multi_device_get_sync_id_mask : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_put_sync_id {
	uint32_t multi_device_put_sync_id : 16;
	uint32_t reserved : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_get_sync_id {
	uint64_t multi_device_get_sync_id_0 : 16;
	uint64_t multi_device_get_sync_id_1 : 16;
	uint64_t multi_device_get_sync_id_2 : 16;
	uint64_t multi_device_get_sync_id_3 : 16;
	uint64_t multi_device_get_sync_id_4 : 16;
	uint64_t multi_device_get_sync_id_5 : 16;
	uint64_t multi_device_get_sync_id_6 : 16;
	uint64_t multi_device_get_sync_id_7 : 16;
	uint64_t multi_device_get_sync_id_8 : 16;
	uint64_t multi_device_get_sync_id_9 : 16;
	uint64_t multi_device_get_sync_id_10 : 16;
	uint64_t multi_device_get_sync_id_11 : 16;
	uint64_t multi_device_get_sync_id_12 : 16;
	uint64_t multi_device_get_sync_id_13 : 16;
	uint64_t multi_device_get_sync_id_14 : 16;
	uint64_t multi_device_get_sync_id_15 : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_md_sync_id {
	struct cmd_descr_md_sync_mask md_sync_mask;
	struct cmd_descr_put_sync_id put_sync_id;
	struct cmd_descr_get_sync_id get_sync_id;
};

struct __attribute__((packed, aligned(4))) cmd_descr_ext_sync_mask {
	uint64_t ext_get_sync_mask_lo : 64;
	uint64_t ext_get_sync_mask_hi : 64;
	uint64_t ext_put_sync_mask_lo : 64;
	uint64_t ext_put_sync_mask_hi : 64;
	uint64_t reserved : 64;
};

struct __attribute__((packed, aligned(4))) cmd_descr_md_sync_hdr {
	uint32_t sync_type : 1;
	uint32_t reserved : 31;
};

union __attribute__((packed, aligned(4))) cmd_descr_sync_union {
	struct cmd_descr_md_sync_id md_sync_id;
	struct cmd_descr_ext_sync_mask ext_sync_mask;
};

struct __attribute__((packed, aligned(4))) cmd_descr_sync {
	struct cmd_descr_md_sync_hdr md_sync_hdr;
	union cmd_descr_sync_union sync_union;
};

/* Constants: Possible enum value of field */
enum sync_sync_type {
	SYNC_SYNC_TYPE_MULTI_DEVICE_SYNC = 0,
	SYNC_SYNC_TYPE_EXTERNAL_MULTI_SYNC,
};

#endif /* _G_CMD_DESCR_SYNC_REBEL_H_ */
