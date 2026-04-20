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

#ifndef _G_EDMA_DLOG_COMMON_H_
#define _G_EDMA_DLOG_COMMON_H_

#define ADDR_OFFSET_RBDMA_ELOG_CTRL_CLEAR				0x00
#define ADDR_OFFSET_RBDMA_ELOG_SUBTASK_DONE_CNT			0x04
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT0_VA2PA			0x08
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT1_VA2PA			0x0C
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT2_VA2PA			0x10
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT3_VA2PA			0x14
#define ADDR_OFFSET_RBDMA_ELOG_STE0_SUB_TASK_ID			0x18
#define ADDR_OFFSET_RBDMA_ELOG_STE0_SRCADDRESS_OR_CONST 0x1C
#define ADDR_OFFSET_RBDMA_ELOG_STE0_DST0_ADDR			0x20
#define ADDR_OFFSET_RBDMA_ELOG_STE0_SIZEOF128BLOCK		0x24
#define ADDR_OFFSET_RBDMA_ELOG_STE0_TASK_RUN_ACTION		0x28
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT_3_0_MSB			0x2C
#define ADDR_OFFSET_RBDMA_ELOG_STE0_DST1_ADDR			0x30
#define ADDR_OFFSET_RBDMA_ELOG_STE0_DST2_ADDR			0x34
#define ADDR_OFFSET_RBDMA_ELOG_STE0_DST3_ADDR			0x38
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT4_VA2PA			0x3C
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT5_VA2PA			0x40
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT6_VA2PA			0x44
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT7_VA2PA			0x48
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT8_VA2PA			0x4C
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT9_VA2PA			0x50
#define ADDR_OFFSET_RBDMA_ELOG_STE0_DST_PT_5_4_MSB		0x54
#define ADDR_OFFSET_RBDMA_ELOG_STE0_PT_9_6_MSB			0x58
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT0_VA2PA			0x5C
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT1_VA2PA			0x60
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT2_VA2PA			0x64
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT3_VA2PA			0x68
#define ADDR_OFFSET_RBDMA_ELOG_STE1_SUB_TASK_ID			0x6C
#define ADDR_OFFSET_RBDMA_ELOG_STE1_SRCADDRESS_OR_CONST 0x70
#define ADDR_OFFSET_RBDMA_ELOG_STE1_DST0_ADDR			0x74
#define ADDR_OFFSET_RBDMA_ELOG_STE1_SIZEOF128BLOCK		0x78
#define ADDR_OFFSET_RBDMA_ELOG_STE1_TASK_RUN_ACTION		0x7C
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT_3_0_MSB			0x80
#define ADDR_OFFSET_RBDMA_ELOG_STE1_DST1_ADDR			0x84
#define ADDR_OFFSET_RBDMA_ELOG_STE1_DST2_ADDR			0x88
#define ADDR_OFFSET_RBDMA_ELOG_STE1_DST3_ADDR			0x8C
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT4_VA2PA			0x90
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT5_VA2PA			0x94
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT6_VA2PA			0x98
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT7_VA2PA			0x9C
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT8_VA2PA			0xA0
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT9_VA2PA			0xA4
#define ADDR_OFFSET_RBDMA_ELOG_STE1_DST_PT_5_4_MSB		0xA8
#define ADDR_OFFSET_RBDMA_ELOG_STE1_PT_9_6_MSB			0xAC
#define ADDR_OFFSET_RBDMA_ELOG_TE_STATUS				0xB0
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_INFO			0xB4
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_CONFIG			0xB8
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_POP				0xBC
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_READ_REQ_ADDR	0xC0
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_READ_REQ_INFO	0xC4
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_READ_DATA_DATA	0xC8
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_READ_DATA_INFO	0xCC
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_WRITE_REQ_ADDR	0xD0
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_WRITE_REQ_INFO	0xD4
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_WRITE_DATA		0xD8
#define ADDR_OFFSET_RBDMA_ELOG_LOG_FIFO_WRITE_RSP		0xDC
#define ADDR_OFFSET_RBDMA_ELOG_NUM_CE_TE				0xE0
#define ADDR_OFFSET_RBDMA_ELOG_NUM_UE_TE				0xE4
#define ADDR_OFFSET_RBDMA_ELOG_NUM_CE_RRSP				0xE8
#define ADDR_OFFSET_RBDMA_ELOG_NUM_UE_RRSP				0xEC
#define ADDR_OFFSET_RBDMA_ELOG_NUM_CE_BRSP				0xF0
#define ADDR_OFFSET_RBDMA_ELOG_NUM_UE_BRSP				0xF4
#define ADDR_OFFSET_RBDMA_ELOG_NUM_OF_READ_REQ			0xF8
#define ADDR_OFFSET_RBDMA_ELOG_NUM_OF_READ_DATA			0xFC
#define ADDR_OFFSET_RBDMA_ELOG_NUM_OF_WRITE_REQ			0x100
#define ADDR_OFFSET_RBDMA_ELOG_NUM_OF_WRITE_DATA		0x104
#define ADDR_OFFSET_RBDMA_ELOG_NUM_OF_WRITE_RESP		0x108
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_ARVALID			0x10C
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_ARVALID_ARREADY	0x110
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_RVALID			0x114
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_RVALID_RREADY		0x118
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_AWVALID			0x11C
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_AWVALID_AWREADY	0x120
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_WVALID			0x124
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_WVALID_WREADY		0x128
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_BVALID			0x12C
#define ADDR_OFFSET_RBDMA_ELOG_CYC_OF_BVALID_BREADY		0x130

enum rbdma_elog_log_fifo_config_rreq_explicit_clear {
	RBDMA_ELOG_LOG_FIFO_CONFIG_RREQ_EXPLICIT_CLEAR_IMP_CLR,
	RBDMA_ELOG_LOG_FIFO_CONFIG_RREQ_EXPLICIT_CLEAR_EXP_CLR,
};

enum rbdma_elog_log_fifo_config_rdata_explicit_clear {
	RBDMA_ELOG_LOG_FIFO_CONFIG_RDATA_EXPLICIT_CLEAR_IMP_CLR,
	RBDMA_ELOG_LOG_FIFO_CONFIG_RDATA_EXPLICIT_CLEAR_EXP_CLR,
};

enum rbdma_elog_log_fifo_config_wreq_explicit_clear {
	RBDMA_ELOG_LOG_FIFO_CONFIG_WREQ_EXPLICIT_CLEAR_IMP_CLR,
	RBDMA_ELOG_LOG_FIFO_CONFIG_WREQ_EXPLICIT_CLEAR_EXP_CLR,
};

enum rbdma_elog_log_fifo_config_wdata_explicit_clear {
	RBDMA_ELOG_LOG_FIFO_CONFIG_WDATA_EXPLICIT_CLEAR_IMP_CLR,
	RBDMA_ELOG_LOG_FIFO_CONFIG_WDATA_EXPLICIT_CLEAR_EXP_CLR,
};

enum rbdma_elog_log_fifo_config_wrsp_explicit_clear {
	RBDMA_ELOG_LOG_FIFO_CONFIG_WRSP_EXPLICIT_CLEAR_IMP_CLR,
	RBDMA_ELOG_LOG_FIFO_CONFIG_WRSP_EXPLICIT_CLEAR_EXP_CLR,
};

union rbdma_elog_ctrl_clear {
	struct __attribute__((packed)) {
		uint32_t pause_read_req : 1;
		uint32_t pause_read_data : 1;
		uint32_t pause_write_req : 1;
		uint32_t pause_write_data : 1;
		uint32_t pause_write_rsp : 1;
		uint32_t clear_log : 1;
		uint32_t clear_ras : 1;
		uint32_t clear_event : 1;
		uint32_t clear_st_done_cnt : 1;
		uint32_t reserved : 23;
	};
	uint32_t bits;
};

union rbdma_elog_subtask_done_cnt {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt0_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt1_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt2_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt3_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_sub_task_id {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_srcaddress_or_const {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_dst0_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_sizeof128block {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_task_run_action {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt_3_0_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_dst1_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_dst2_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_dst3_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt4_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt5_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt6_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt7_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt8_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt9_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_dst_pt_5_4_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste0_pt_9_6_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt0_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt1_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt2_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt3_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_sub_task_id {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_srcaddress_or_const {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_dst0_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_sizeof128block {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_task_run_action {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt_3_0_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_dst1_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_dst2_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_dst3_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt4_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt5_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt6_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt7_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt8_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt9_va2pa {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_dst_pt_5_4_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_ste1_pt_9_6_msb {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_te_status {
	struct __attribute__((packed)) {
		uint32_t ste0_fsm_state : 8;
		uint32_t ste0_rreq_gen_finished : 1;
		uint32_t ste0_wreq_gen_finished : 1;
		uint32_t ste0_wreq_auth_grant : 1;
		uint32_t ste0_wreq_auth_ask : 1;
		uint32_t ste0_rreq_auth_grant : 1;
		uint32_t ste0_rreq_auth_ask : 1;
		uint32_t ste0_brsv_auth_grant : 1;
		uint32_t ste0_brsv_auth_ask : 1;
		uint32_t ste1_fsm_state : 8;
		uint32_t ste1_rreq_gen_finished : 1;
		uint32_t ste1_wreq_gen_finished : 1;
		uint32_t ste1_wreq_auth_grant : 1;
		uint32_t ste1_wreq_auth_ask : 1;
		uint32_t ste1_rreq_auth_grant : 1;
		uint32_t ste1_rreq_auth_ask : 1;
		uint32_t ste1_brsv_auth_grant : 1;
		uint32_t ste1_brsv_auth_ask : 1;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_info {
	struct __attribute__((packed)) {
		uint32_t num_of_rreq : 5;
		uint32_t num_of_rdata : 5;
		uint32_t num_of_wreq : 5;
		uint32_t num_of_wdata : 5;
		uint32_t num_of_wrsp : 5;
		uint32_t ovfl_of_rreq : 1;
		uint32_t ovfl_of_rdata : 1;
		uint32_t ovfl_of_wreq : 1;
		uint32_t ovfl_of_wdata : 1;
		uint32_t ovfl_of_wrsp : 1;
		uint32_t reserved : 2;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_config {
	struct __attribute__((packed)) {
		uint32_t rreq_explicit_clear : 1;
		uint32_t rdata_explicit_clear : 1;
		uint32_t wreq_explicit_clear : 1;
		uint32_t wdata_explicit_clear : 1;
		uint32_t wrsp_explicit_clear : 1;
		uint32_t reserved : 27;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_pop {
	struct __attribute__((packed)) {
		uint32_t rreq_log_pop : 1;
		uint32_t rdata_log_pop : 1;
		uint32_t wreq_log_pop : 1;
		uint32_t wdata_log_pop : 1;
		uint32_t wrsp_log_pop : 1;
		uint32_t reserved : 27;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_read_req_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_read_req_info {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_read_data_data {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_read_data_info {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_write_req_addr {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_write_req_info {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_write_data {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_log_fifo_write_rsp {
	struct __attribute__((packed)) {
		uint32_t debug : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ce_te {
	struct __attribute__((packed)) {
		uint32_t correct : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ue_te {
	struct __attribute__((packed)) {
		uint32_t uncorrect : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ce_rrsp {
	struct __attribute__((packed)) {
		uint32_t correct : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ue_rrsp {
	struct __attribute__((packed)) {
		uint32_t uncorrect : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ce_brsp {
	struct __attribute__((packed)) {
		uint32_t correct : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_ue_brsp {
	struct __attribute__((packed)) {
		uint32_t uncorrect : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_of_read_req {
	struct __attribute__((packed)) {
		uint32_t number : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_of_read_data {
	struct __attribute__((packed)) {
		uint32_t number : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_of_write_req {
	struct __attribute__((packed)) {
		uint32_t number : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_of_write_data {
	struct __attribute__((packed)) {
		uint32_t number : 32;
	};
	uint32_t bits;
};

union rbdma_elog_num_of_write_resp {
	struct __attribute__((packed)) {
		uint32_t number : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_arvalid {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_arvalid_arready {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_rvalid {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_rvalid_rready {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_awvalid {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_awvalid_awready {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_wvalid {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_wvalid_wready {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_bvalid {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

union rbdma_elog_cyc_of_bvalid_bready {
	struct __attribute__((packed)) {
		uint32_t cycle : 32;
	};
	uint32_t bits;
};

#endif /* _G_EDMA_DLOG_COMMON_H_*/
