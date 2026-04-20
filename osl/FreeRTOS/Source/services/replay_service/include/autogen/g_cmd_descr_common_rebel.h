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

#ifndef _G_CMD_DESCR_COMMON_REBEL_H_
#define _G_CMD_DESCR_COMMON_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_COMMON_ARCH_MAJOR 0
#define CMD_DESCR_COMMON_ARCH_MINOR 9
#define CMD_DESCR_COMMON_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_COMMON_EOCS							2
#define BIT_WIDTH_CMD_DESCR_COMMON_CMD_ID						16
#define BIT_WIDTH_CMD_DESCR_COMMON_CMD_TYPE						3
#define BIT_WIDTH_CMD_DESCR_COMMON_CMD_TYPE_EXT					3
#define BIT_WIDTH_CMD_DESCR_COMMON_DESCR_TYPE					3
#define BIT_WIDTH_CMD_DESCR_COMMON_EXECUTION_MODE				1
#define BIT_WIDTH_CMD_DESCR_COMMON_TLB_GEN_MODE					1
#define BIT_WIDTH_CMD_DESCR_COMMON_TLB_INVALIDATE				2
#define BIT_WIDTH_CMD_DESCR_COMMON_USE_TBU						1
#define BIT_WIDTH_CMD_DESCR_COMMON_TLB_CNT_GEN_BY_CP			7
#define BIT_WIDTH_CMD_DESCR_COMMON_SET_CP_DEP_SLOT_ID			6
#define BIT_WIDTH_CMD_DESCR_COMMON_SET_CP_DEP_SLOT_ID_REF_COUNT 6
#define BIT_WIDTH_CMD_DESCR_COMMON_EXT_SYNC_TYPE				2
#define BIT_WIDTH_CMD_DESCR_COMMON_EXT_SYNC_ID					7
#define BIT_WIDTH_CMD_DESCR_COMMON_REQUEST_CMD_SUBDIVISION		1
#define BIT_WIDTH_CMD_DESCR_COMMON_ENABLE_CMGR					1
#define BIT_WIDTH_CMD_DESCR_COMMON_CMGR_DNC_SYNC_TYPE			1
#define BIT_WIDTH_CMD_DESCR_COMMON_NOTIFY_TARGET				22
#define BIT_WIDTH_CMD_DESCR_COMMON_NOTIFY_CODE					4
#define BIT_WIDTH_CMD_DESCR_COMMON_NOTIFY_GROUP_INDEX			6
#define BIT_WIDTH_CMD_DESCR_COMMON_CP_DEP_SLOT_MASK				64

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_common {
	uint64_t eocs : 2;
	uint64_t cmd_id : 16;
	uint64_t cmd_type : 3;
	uint64_t cmd_type_ext : 3;
	uint64_t descr_type : 3;
	uint64_t execution_mode : 1;
	uint64_t tlb_gen_mode : 1;
	uint64_t tlb_invalidate : 2;
	uint64_t use_tbu : 1;
	uint64_t tlb_cnt_gen_by_cp : 7;
	uint64_t set_cp_dep_slot_id : 6;
	uint64_t set_cp_dep_slot_id_ref_count : 6;
	uint64_t ext_sync_type : 2;
	uint64_t ext_sync_id : 7;
	uint64_t request_cmd_subdivision : 1;
	uint64_t reserved : 1;
	uint64_t enable_cmgr : 1;
	uint64_t cmgr_dnc_sync_type : 1;
	uint64_t notify_target : 22;
	uint64_t notify_code : 4;
	uint64_t notify_group_index : 6;
	uint64_t cp_dep_slot_mask : 64;
};

/* Constants: Possible enum value of field */
enum common_eocs {
	COMMON_EOCS_FALSE = 0,
	COMMON_EOCS_TRUE,
	COMMON_EOCS_CONTINUE_TO_NEXT_CS,
};

enum common_cmd_type {
	COMMON_CMD_TYPE_COMPUTE = 0,
	COMMON_CMD_TYPE_UDMA,
	COMMON_CMD_TYPE_UDMA_LP,
	COMMON_CMD_TYPE_UDMA_ST,
	COMMON_CMD_TYPE_DDMA,
	COMMON_CMD_TYPE_DDMA_HIGHP,
	COMMON_CMD_TYPE_RESERVED,
	COMMON_CMD_TYPE_EXTENSION,
};

enum common_cmd_type_ext {
	COMMON_CMD_TYPE_EXT_NOP = 0,
	COMMON_CMD_TYPE_EXT_SYNC,
	COMMON_CMD_TYPE_EXT_CTRL_FLOW,
	COMMON_CMD_TYPE_EXT_HDMA,
	COMMON_CMD_TYPE_EXT_CS_HDR,
	COMMON_CMD_TYPE_EXT_CP_OP,
	COMMON_CMD_TYPE_EXT_EVENT,
	COMMON_CMD_TYPE_EXT_HANG,
};

enum common_descr_type {
	COMMON_DESCR_TYPE_DEFAULT = 0,
	COMMON_DESCR_TYPE_EXT1_PARA,
	COMMON_DESCR_TYPE_EXT2_PARA,
	COMMON_DESCR_TYPE_EXT3_PARA,
	COMMON_DESCR_TYPE_EXT4_PARA,
	COMMON_DESCR_TYPE_EXT5_PARA,
};

enum common_execution_mode {
	COMMON_EXECUTION_MODE_NORMAL = 0,
	COMMON_EXECUTION_MODE_TLB_PRELOAD,
};

enum common_tlb_gen_mode {
	COMMON_TLB_GEN_MODE_PER_COMMAND = 0,
	COMMON_TLB_GEN_MODE_PER_TASK,
};

enum common_tlb_invalidate {
	COMMON_TLB_INVALIDATE_NOP = 0,
	COMMON_TLB_INVALIDATE_ALL,
	COMMON_TLB_INVALIDATE_ALL_REFILL,
};

enum common_use_tbu {
	COMMON_USE_TBU_FALSE = 0,
	COMMON_USE_TBU_TRUE,
};

enum common_ext_sync_type {
	COMMON_EXT_SYNC_TYPE_NO_SYNC = 0,
	COMMON_EXT_SYNC_TYPE_GET_SYNC,
	COMMON_EXT_SYNC_TYPE_PUT_SYNC,
	COMMON_EXT_SYNC_TYPE_BIDIRECTIONAL_SYNC,
};

enum common_cmgr_dnc_sync_type {
	COMMON_CMGR_DNC_SYNC_TYPE_TSYNC = 0,
	COMMON_CMGR_DNC_SYNC_TYPE_PSYNC,
};

#endif /* _G_CMD_DESCR_COMMON_REBEL_H_ */
