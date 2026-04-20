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

#ifndef _G_CMD_DESCR_HDMA_REBEL_H_
#define _G_CMD_DESCR_HDMA_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_HDMA_ARCH_MAJOR 0
#define CMD_DESCR_HDMA_ARCH_MINOR 9
#define CMD_DESCR_HDMA_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_HDMA_SRC_ADDR						 44
#define BIT_WIDTH_CMD_DESCR_HDMA_DST_ADDR						 44
#define BIT_WIDTH_CMD_DESCR_HDMA_MULTI_DEVICE_PUT_SYNC_EN		 1
#define BIT_WIDTH_CMD_DESCR_HDMA_MULTI_DEVICE_PUT_SYNC_DEVICE_ID 4
#define BIT_WIDTH_CMD_DESCR_HDMA_MULTI_DEVICE_GET_SYNC_EN		 1
#define BIT_WIDTH_CMD_DESCR_HDMA_RESERVED1						 31
#define BIT_WIDTH_CMD_DESCR_HDMA_MULTI_DEVICE_PUT_SYNC_ID		 16
#define BIT_WIDTH_CMD_DESCR_HDMA_MULTI_DEVICE_GET_SYNC_ID		 16
#define BIT_WIDTH_CMD_DESCR_HDMA_TRAFFIC_DIRECTION				 2
#define BIT_WIDTH_CMD_DESCR_HDMA_EXT_TASK_CNT					 5
#define BIT_WIDTH_CMD_DESCR_HDMA_GET_SYNC_MODE					 1
#define BIT_WIDTH_CMD_DESCR_HDMA_BLK_SIZE						 32

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_src_addr {
	uint64_t src_addr : 44;
	uint64_t reserved : 20;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dst_addr {
	uint64_t dst_addr : 44;
	uint64_t reserved : 20;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_md_sync_mask {
	uint64_t multi_device_put_sync_en : 1;
	uint64_t multi_device_put_sync_device_id : 4;
	uint64_t reserved : 27;
	uint64_t multi_device_get_sync_en : 1;
	uint64_t reserved1 : 31;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_md_sync_id {
	uint32_t multi_device_put_sync_id : 16;
	uint32_t multi_device_get_sync_id : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_ctrl {
	uint32_t traffic_direction : 2;
	uint32_t ext_task_cnt : 5;
	uint32_t get_sync_mode : 1;
	uint32_t reserved : 24;
};

struct __attribute__((packed, aligned(4))) cmd_descr_task {
	struct cmd_descr_src_addr src_addr;
	struct cmd_descr_dst_addr dst_addr;
	uint32_t blk_size : 32;
	struct cmd_descr_hdma_md_sync_mask hdma_md_sync_mask;
	struct cmd_descr_hdma_md_sync_id hdma_md_sync_id;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma {
	struct cmd_descr_hdma_ctrl hdma_ctrl;
	uint64_t reserved : 64;
	struct cmd_descr_task task;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_ext1 {
	struct cmd_descr_task task[2];
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_ext2 {
	struct cmd_descr_task task[4];
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_ext3 {
	struct cmd_descr_task task[8];
};

struct __attribute__((packed, aligned(4))) cmd_descr_hdma_ext4 {
	struct cmd_descr_task task[16];
};

/* Constants: Possible enum value of field */
enum hdma_traffic_direction {
	HDMA_TRAFFIC_DIRECTION_OUTBOUND = 0,
	HDMA_TRAFFIC_DIRECTION_INBOUND,
	HDMA_TRAFFIC_DIRECTION_CHIP_INTERNAL,
};

enum hdma_get_sync_mode {
	HDMA_GET_SYNC_MODE_WAIT_ALL_SYNC = 0,
	HDMA_GET_SYNC_MODE_WAIT_ANY_SYNC,
};

#endif /* _G_CMD_DESCR_HDMA_REBEL_H_ */
