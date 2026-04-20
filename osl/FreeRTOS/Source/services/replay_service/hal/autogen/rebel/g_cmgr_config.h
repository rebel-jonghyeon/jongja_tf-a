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

#ifndef _G_CMGR_CONFIG_COMMON_H_
#define _G_CMGR_CONFIG_COMMON_H_

#define ADDR_OFFSET_CMGR_CONFIG_IP_INFO0			  0x000
#define ADDR_OFFSET_CMGR_CONFIG_IP_INFO1			  0x004
#define ADDR_OFFSET_CMGR_CONFIG_IP_INFO2			  0x008
#define ADDR_OFFSET_CMGR_CONFIG_IP_INFO3			  0x00C
#define ADDR_OFFSET_CMGR_CONFIG_DESIGN_INFO0		  0x010
#define ADDR_OFFSET_CMGR_CONFIG_DESIGN_INFO1		  0x014
#define ADDR_OFFSET_CMGR_CONFIG_COMMON_RPT			  0x018
#define ADDR_OFFSET_CMGR_CONFIG_COMMON_REG			  0x01C
#define ADDR_OFFSET_CMGR_CONFIG_CHIPLET0_BASE_ADDR	  0x30
#define ADDR_OFFSET_CMGR_CONFIG_CHIPLET1_BASE_ADDR	  0x34
#define ADDR_OFFSET_CMGR_CONFIG_CHIPLET2_BASE_ADDR	  0x38
#define ADDR_OFFSET_CMGR_CONFIG_CHIPLET3_BASE_ADDR	  0x3C
#define ADDR_OFFSET_CMGR_CONFIG_DCL0_BASE_ADDR		  0x40
#define ADDR_OFFSET_CMGR_CONFIG_DCL0_DNC_OFFSET		  0x44
#define ADDR_OFFSET_CMGR_CONFIG_DCL1_BASE_ADDR		  0x48
#define ADDR_OFFSET_CMGR_CONFIG_DCL1_DNC_OFFSET		  0x4C
#define ADDR_OFFSET_CMGR_CONFIG_DNC_TSYNC_OFFSET	  0x50
#define ADDR_OFFSET_CMGR_CONFIG_DNC_ERUN_OFFSET		  0x54
#define ADDR_OFFSET_CMGR_CONFIG_RBDMA_BASE_ADDR		  0x58
#define ADDR_OFFSET_CMGR_CONFIG_RBDMA_TSYNC_OFFSET	  0x5C
#define ADDR_OFFSET_CMGR_CONFIG_RBDMA_RLSYNC_OFFSET	  0x60
#define ADDR_OFFSET_CMGR_CONFIG_RESERVED_26			  0x64
#define ADDR_OFFSET_CMGR_CONFIG_CMGR_BASE_ADDR		  0x68
#define ADDR_OFFSET_CMGR_CONFIG_CMGR_TASK_INFO_OFFSET 0x6C
#define ADDR_OFFSET_CMGR_CONFIG_IDLE				  0x70
#define ADDR_OFFSET_CMGR_CONFIG_CONFIG				  0x80
#define ADDR_OFFSET_CMGR_CONFIG_CTL					  0x84
#define ADDR_OFFSET_CMGR_CONFIG_INTR_MASK			  0x90
#define ADDR_OFFSET_CMGR_CONFIG_RESERVED_38			  0x94
#define ADDR_OFFSET_CMGR_CONFIG_INTR_STATUS_0		  0xA0
#define ADDR_OFFSET_CMGR_CONFIG_INTR_STATUS_1		  0xA4
#define ADDR_OFFSET_CMGR_CONFIG_LOG_CONFIG_0		  0xC0
#define ADDR_OFFSET_CMGR_CONFIG_LOG_STR_ADDR_0		  0xC4
#define ADDR_OFFSET_CMGR_CONFIG_PORT_CONFIG_SLV		  0xD8

enum cmgr_config_config_rpt_mode {
	CMGR_CONFIG_CONFIG_RPT_MODE_INTR,
	CMGR_CONFIG_CONFIG_RPT_MODE_POLL,
};

enum cmgr_config_intr_mask_noti {
	CMGR_CONFIG_INTR_MASK_NOTI_UNMSK,
	CMGR_CONFIG_INTR_MASK_NOTI_MSK,
};

enum cmgr_config_intr_mask_error {
	CMGR_CONFIG_INTR_MASK_ERROR_UNMSK,
	CMGR_CONFIG_INTR_MASK_ERROR_MSK,
};

union cmgr_config_ip_info0 {
	struct __attribute__((packed)) {
		uint32_t release_date : 32;
	};
	uint32_t bits;
};

union cmgr_config_ip_info1 {
	struct __attribute__((packed)) {
		uint32_t min_ver : 8;
		uint32_t maj_ver : 8;
		uint32_t ip_ver : 8;
		uint32_t ip_id : 8;
	};
	uint32_t bits;
};

union cmgr_config_ip_info2 {
	struct __attribute__((packed)) {
		uint32_t global_nid0 : 8;
		uint32_t global_nid1 : 8;
		uint32_t global_nid2 : 8;
		uint32_t global_nid3 : 8;
	};
	uint32_t bits;
};

union cmgr_config_ip_info3 {
	struct __attribute__((packed)) {
		uint32_t local_nid0 : 8;
		uint32_t local_nid1 : 8;
		uint32_t reserved : 8;
		uint32_t local_ready : 8;
	};
	uint32_t bits;
};

union cmgr_config_design_info0 {
	struct __attribute__((packed)) {
		uint32_t local_ready : 32;
	};
	uint32_t bits;
};

union cmgr_config_design_info1 {
	struct __attribute__((packed)) {
		uint32_t local_ready : 32;
	};
	uint32_t bits;
};

union cmgr_config_common_rpt {
	struct __attribute__((packed)) {
		uint32_t local_ready : 32;
	};
	uint32_t bits;
};

union cmgr_config_common_reg {
	struct __attribute__((packed)) {
		uint32_t local_ready : 32;
	};
	uint32_t bits;
};

union cmgr_config_chiplet0_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_chiplet1_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_chiplet2_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_chiplet3_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dcl0_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dcl0_dnc_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dcl1_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dcl1_dnc_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dnc_tsync_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_dnc_erun_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_rbdma_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_rbdma_tsync_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_rbdma_rlsync_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_reserved_26 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union cmgr_config_cmgr_base_addr {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_cmgr_task_info_offset {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_idle {
	struct __attribute__((packed)) {
		uint32_t stat : 32;
	};
	uint32_t bits;
};

union cmgr_config_config {
	struct __attribute__((packed)) {
		uint32_t rpt_mode : 1;
		uint32_t intr_clr_mode : 1;
		uint32_t noti_chiplet_base_addr_mode : 1;
		uint32_t rsvd_21_3 : 19;
		uint32_t log_format : 1;
		uint32_t rsvd_24_23 : 2;
		uint32_t log_cnt_en : 1;
		uint32_t secded_en : 1;
		uint32_t rsvd_27 : 1;
		uint32_t glb_cnt_en : 1;
		uint32_t acc_cnt_en : 1;
		uint32_t log_en : 1;
		uint32_t af_en : 1;
	};
	uint32_t bits;
};

union cmgr_config_ctl {
	struct __attribute__((packed)) {
		uint32_t rsvd_24_0 : 25;
		uint32_t log_cnt_clr : 1;
		uint32_t secded_cnt_clr : 1;
		uint32_t rsvd_27 : 1;
		uint32_t glb_cnt_clr : 1;
		uint32_t acc_cnt_clr : 1;
		uint32_t rsvd_31_30 : 2;
	};
	uint32_t bits;
};

union cmgr_config_intr_mask {
	struct __attribute__((packed)) {
		uint32_t noti : 1;
		uint32_t error : 1;
		uint32_t rsvd_31_2 : 30;
	};
	uint32_t bits;
};

union cmgr_config_reserved_38 {
	struct __attribute__((packed)) {
		uint32_t rsvd_1_0 : 2;
		uint32_t rsvd_31_2 : 30;
	};
	uint32_t bits;
};

union cmgr_config_intr_status_0 {
	struct __attribute__((packed)) {
		uint32_t intr_type : 4;
		uint32_t rsvd_7_4 : 4;
		uint32_t intr_cnt : 8;
		uint32_t intr_flag : 8;
		uint32_t intr_subinfo : 4;
		uint32_t intr_src : 4;
	};
	uint32_t bits;
};

union cmgr_config_intr_status_1 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union cmgr_config_log_config_0 {
	struct __attribute__((packed)) {
		uint32_t mask : 2;
		uint32_t rsvd_31_2 : 30;
	};
	uint32_t bits;
};

union cmgr_config_log_str_addr_0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_config_port_config_slv {
	struct __attribute__((packed)) {
		uint32_t buser_mode : 1;
		uint32_t rsvd_3_1 : 3;
		uint32_t config_buser : 4;
		uint32_t rsvd_15_8 : 8;
		uint32_t ruser_mode : 1;
		uint32_t rsvd_19_17 : 3;
		uint32_t config_ruser : 4;
		uint32_t rsvd_31_24 : 8;
	};
	uint32_t bits;
};

#endif /* _G_CMGR_CONFIG_COMMON_H_*/
