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

#ifndef _G_EDMA_GLOBAL_REGISTERS_COMMON_H_
#define _G_EDMA_GLOBAL_REGISTERS_COMMON_H_

#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_CTRL		  0x00
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_CTRL_STATUS  0x04
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_STATUS_MNG	  0x08
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_STATUS_CLEAR 0x0C
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_SET0		  0x10
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_SET1		  0x14
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_SET2		  0x018
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_SET3		  0x01C
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_EDMA_DBUS		  0x020
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_RESERVED10	  0x024
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_RESERVED11	  0x028
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_EDMA_RESERVED12	  0x02C
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WDATA_0		  0x030
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WDATA_1		  0x034
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WDATA_2		  0x038
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WDATA_3		  0x03C
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WDATA_4		  0x040
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RDATA_0		  0x044
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RDATA_1		  0x048
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RDATA_2		  0x04C
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RDATA_3		  0x050
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RDATA_4		  0x054
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_WADDR_WE		  0x058
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_SRAM_RADDR_RE		  0x05C
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_TASK_KILL_ID		  0x60
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_TASK_KILL_CMD		  0x64
#define ADDR_OFFSET_RBDMA_GLOBAL_EDMA_TASK_KILL_STATUS	  0x68

enum rbdma_global_config_edma_status_mng_tpd_clear_policy {
	RBDMA_GLOBAL_CONFIG_EDMA_STATUS_MNG_TPD_CLEAR_POLICY_IMP_CLR,
	RBDMA_GLOBAL_CONFIG_EDMA_STATUS_MNG_TPD_CLEAR_POLICY_EXP_CLR,
};

enum rbdma_global_config_edma_status_mng_kd_clear_policy {
	RBDMA_GLOBAL_CONFIG_EDMA_STATUS_MNG_KD_CLEAR_POLICY_IMP_CLR,
	RBDMA_GLOBAL_CONFIG_EDMA_STATUS_MNG_KD_CLEAR_POLICY_EXP_CLR,
};

enum rbdma_global_config_edma_set2_ras_op {
	RBDMA_GLOBAL_CONFIG_EDMA_SET2_RAS_OP_STP,
	RBDMA_GLOBAL_CONFIG_EDMA_SET2_RAS_OP_KPG,
};

enum rbdma_global_config_edma_set2_pt_miss_rpt {
	RBDMA_GLOBAL_CONFIG_EDMA_SET2_PT_MISS_RPT_PT_TBU,
	RBDMA_GLOBAL_CONFIG_EDMA_SET2_PT_MISS_RPT_PT_ERR,
};

union rbdma_global_config_edma_ctrl {
	struct __attribute__((packed)) {
		uint32_t te_clear : 1;
		uint32_t te_pause : 1;
		uint32_t te_resume : 1;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_ctrl_status {
	struct __attribute__((packed)) {
		uint32_t te_pause_done : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_status_mng {
	struct __attribute__((packed)) {
		uint32_t tpd_clear_policy : 1;
		uint32_t kd_clear_policy : 1;
		uint32_t reserved : 30;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_status_clear {
	struct __attribute__((packed)) {
		uint32_t tpd_clear : 1;
		uint32_t kd_clear : 1;
		uint32_t reserved : 30;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_set0 {
	struct __attribute__((packed)) {
		uint32_t read_mo : 8;
		uint32_t write_mo : 8;
		uint32_t split_boundary : 2;
		uint32_t reserved : 14;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_set1 {
	struct __attribute__((packed)) {
		uint32_t arcache : 4;
		uint32_t awcache : 4;
		uint32_t reserved : 24;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_set2 {
	struct __attribute__((packed)) {
		uint32_t en_debug_edma : 1;
		uint32_t ras_op : 1;
		uint32_t pt_miss_rpt : 1;
		uint32_t en_sram_access : 1;
		uint32_t sram_wl : 1;
		uint32_t reserved : 27;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_set3 {
	struct __attribute__((packed)) {
		uint32_t user_chiplet : 3;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};

union rbdma_global_status_edma_dbus {
	struct __attribute__((packed)) {
		uint32_t master_w : 8;
		uint32_t master_r : 8;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_reserved10 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_reserved11 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_edma_reserved12 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_wdata_0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_wdata_1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_wdata_2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_wdata_3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_wdata_4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_rdata_0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_rdata_1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_rdata_2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_rdata_3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_rdata_4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_waddr_we {
	struct __attribute__((packed)) {
		uint32_t slice : 3;
		uint32_t entry : 9;
		uint32_t reserved : 19;
		uint32_t en : 1;
	};
	uint32_t bits;
};

union rbdma_global_edma_sram_raddr_re {
	struct __attribute__((packed)) {
		uint32_t slice : 3;
		uint32_t entry : 9;
		uint32_t reserved : 19;
		uint32_t en : 1;
	};
	uint32_t bits;
};

union rbdma_global_edma_task_kill_id {
	struct __attribute__((packed)) {
		uint32_t pt_id : 32;
	};
	uint32_t bits;
};

union rbdma_global_edma_task_kill_cmd {
	struct __attribute__((packed)) {
		uint32_t run : 1;
		uint32_t reserved : 27;
		uint32_t level : 4;
	};
	uint32_t bits;
};

union rbdma_global_edma_task_kill_status {
	struct __attribute__((packed)) {
		uint32_t kill_done : 1;
		uint32_t reserved1 : 3;
		uint32_t killed_ste : 2;
		uint32_t reserved6 : 2;
		uint32_t killed_stb : 4;
		uint32_t reserved12 : 20;
	};
	uint32_t bits;
};

#endif /* _G_EDMA_GLOBAL_REGISTERS_COMMON_H_*/
