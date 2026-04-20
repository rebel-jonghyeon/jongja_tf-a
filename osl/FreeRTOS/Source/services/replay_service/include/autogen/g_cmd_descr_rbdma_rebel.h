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

#ifndef _G_CMD_DESCR_RBDMA_REBEL_H_
#define _G_CMD_DESCR_RBDMA_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_RBDMA_ARCH_MAJOR 0
#define CMD_DESCR_RBDMA_ARCH_MINOR 9
#define CMD_DESCR_RBDMA_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_RBDMA_TSTC_IDX						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_TSTC_IDX_VALID				 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_RESERVED0						 5
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_LSYNC_MP					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_LSYNC_MP_CNT				 3
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_LSYNC_MP_IDX				 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_LSYNC_MP					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_LSYNC_RSV					 3
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_LSYNC_MP_IDX				 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_RLSYNC_MASK				 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_RLSYNC_MASK				 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_CMGR_PUT_SYNC_CMD_ID_VALID	 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_CMGR_PUT_SYNC_CMD_ID			 16
#define BIT_WIDTH_CMD_DESCR_RBDMA_SW_SG_TYPE					 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_SRC_ADDR						 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_DST_ADDR						 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_BLOCK_SIZE					 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_DNC_MASK					 16
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_DNC_MASK					 16
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_TSYNC_GIDX				 7
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_TSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_TSYNC_GIDX				 7
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_TSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_LSYNC_GIDX				 6
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_LSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_RLSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_LSYNC_GIDX				 6
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_LSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_RLSYNC_EN					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_TASK_TYPE						 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_SPLIT_GRANULE_L2				 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT_NUM_OF_CHUNK				 12
#define BIT_WIDTH_CMD_DESCR_RBDMA_SRC_ADDR_MSB					 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_DST_ADDR_MSB					 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_TSYNC_DNC_CODE				 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT_DNC_MASK					 3
#define BIT_WIDTH_CMD_DESCR_RBDMA_FID_MAX						 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_INTR_DISABLE					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_EN_DONERPT_MST				 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_EN_INVALID_PT					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_NO_TLB						 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_MAP_LVL						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_IV_LVL						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_PTNUM_OR_V2PNUM				 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_READ_BL						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_WRITE_BL						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_TE_MASK						 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_READ_QOS						 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_WRITE_QOS						 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_TD_MST						 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_QUEUE_TYPE					 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK1_STRIDE_MSB				 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK2_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK3_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK4_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK5_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK6_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_CHK7_MSB						 2
#define BIT_WIDTH_CMD_DESCR_RBDMA_GET_REMOTE_DCL_MASK			 6
#define BIT_WIDTH_CMD_DESCR_RBDMA_PUT_REMOTE_DCL_MASK			 6
#define BIT_WIDTH_CMD_DESCR_RBDMA_TDE_CHK1_BASE_ADDR_STRIDE		 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK_BASE_ADDR		 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK_SIZE				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_EXT_DESCR_TYPE			 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_PARA_UPDATE_MASK_CHIPLET	 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_ENABLE_PARA_DIFF			 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_PARA_UPDATE_MASK_RBDMA	 16
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_DESCR_TYPE				 4
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_PARA_UPDATE_MASK			 5
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_BUF_IDX					 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_DATA_GROUP_IDX			 8
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_PARA_UPDATE_EQUATION_TYPE 1
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_SRC_PARA1				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_SRC_PARA2				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_SRC_BASE					 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_DST_PARA1				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_DST_PARA2				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_DST_BASE					 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_BLK_SIZE_PARA1			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_BLK_SIZE_PARA2			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_BLK_SIZE_BASE			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_STRIDE_PARA1				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_STRIDE_PARA2				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_STRIDE_BASE				 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_CHUNK_CNT_PARA1			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_CHUNK_CNT_PARA2			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT1_CHUNK_CNT_BASE			 32
#define BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK1_SIZE			 32

/* Constants: Byte Unit size */
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_SRC_ADDR						  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_SRC_ADDR				  7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_DST_ADDR						  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_DST_ADDR				  7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_BLOCK_SIZE					  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_BLOCK_SIZE				  7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_TDE_CHK1_BASE_ADDR_STRIDE	  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_TDE_CHK1_BASE_ADDR_STRIDE 7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_EXT0_TDE_CHK_BASE_ADDR		  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK_BASE_ADDR	  7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_EXT0_TDE_CHK_SIZE			  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK_SIZE		  7
#define BYTE_UNIT_SIZE_CMD_DESCR_RBDMA_EXT0_TDE_CHK1_SIZE			  128
#define UNIT_SIZE_BIT_WIDTH_CMD_DESCR_RBDMA_EXT0_TDE_CHK1_SIZE		  7

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_task_conf {
	uint64_t tstc_idx : 2;
	uint64_t tstc_idx_valid : 1;
	uint64_t reserved0 : 5;
	uint64_t get_lsync_mp : 1;
	uint64_t get_lsync_mp_cnt : 3;
	uint64_t get_lsync_mp_idx : 8;
	uint64_t put_lsync_mp : 1;
	uint64_t put_lsync_rsv : 3;
	uint64_t put_lsync_mp_idx : 8;
	uint64_t get_rlsync_mask : 4;
	uint64_t put_rlsync_mask : 4;
	uint64_t reserved : 5;
	uint64_t cmgr_put_sync_cmd_id_valid : 1;
	uint64_t cmgr_put_sync_cmd_id : 16;
	uint64_t sw_sg_type : 2;
};

struct __attribute__((packed, aligned(4))) cmd_descr_task_desc_conf {
	uint64_t src_addr : 32;
	uint64_t dst_addr : 32;
	uint64_t block_size : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_tsync_conf_mask {
	uint32_t get_dnc_mask : 16;
	uint32_t put_dnc_mask : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_tsync_conf_gidx {
	uint32_t get_tsync_gidx : 7;
	uint32_t get_tsync_en : 1;
	uint32_t put_tsync_gidx : 7;
	uint32_t put_tsync_en : 1;
	uint32_t get_lsync_gidx : 6;
	uint32_t get_lsync_en : 1;
	uint32_t get_rlsync_en : 1;
	uint32_t put_lsync_gidx : 6;
	uint32_t put_lsync_en : 1;
	uint32_t put_rlsync_en : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_run_conf0 {
	uint32_t task_type : 4;
	uint32_t split_granule_l2 : 4;
	uint32_t ext_num_of_chunk : 12;
	uint32_t src_addr_msb : 2;
	uint32_t dst_addr_msb : 2;
	uint32_t tsync_dnc_code : 4;
	uint32_t ext_dnc_mask : 3;
	uint32_t fid_max : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_run_conf1 {
	uint32_t intr_disable : 1;
	uint32_t en_donerpt_mst : 1;
	uint32_t en_invalid_pt : 1;
	uint32_t no_tlb : 1;
	uint32_t map_lvl : 2;
	uint32_t iv_lvl : 2;
	uint32_t ptnum_or_v2pnum : 8;
	uint32_t read_bl : 2;
	uint32_t write_bl : 2;
	uint32_t te_mask : 8;
	uint32_t read_qos : 1;
	uint32_t write_qos : 1;
	uint32_t td_mst : 1;
	uint32_t queue_type : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_task_ext_conf {
	uint64_t chk1_stride_msb : 2;
	uint64_t chk2_msb : 2;
	uint64_t chk3_msb : 2;
	uint64_t chk4_msb : 2;
	uint64_t chk5_msb : 2;
	uint64_t chk6_msb : 2;
	uint64_t chk7_msb : 2;
	uint64_t get_remote_dcl_mask : 6;
	uint64_t put_remote_dcl_mask : 6;
	uint64_t reserved : 6;
	uint64_t tde_chk1_base_addr_stride : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_tde_chk {
	uint64_t tde_chk_base_addr : 32;
	uint64_t tde_chk_size : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_rbdma_ext_header0 {
	uint32_t ext_descr_type : 4;
	uint32_t para_update_mask_chiplet : 4;
	uint32_t enable_para_diff : 1;
	uint32_t reserved : 7;
	uint32_t para_update_mask_rbdma : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_rbdma_ext_header1 {
	uint32_t descr_type : 4;
	uint32_t para_update_mask : 5;
	uint32_t buf_idx : 8;
	uint32_t data_group_idx : 8;
	uint32_t para_update_equation_type : 1;
	uint32_t reserved : 6;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dyn_update_para {
	uint64_t src_para1 : 32;
	uint64_t src_para2 : 32;
	uint64_t src_base : 32;
	uint64_t dst_para1 : 32;
	uint64_t dst_para2 : 32;
	uint64_t dst_base : 32;
	uint64_t blk_size_para1 : 32;
	uint64_t blk_size_para2 : 32;
	uint64_t blk_size_base : 32;
	uint64_t stride_para1 : 32;
	uint64_t stride_para2 : 32;
	uint64_t stride_base : 32;
	uint64_t chunk_cnt_para1 : 32;
	uint64_t chunk_cnt_para2 : 32;
	uint64_t chunk_cnt_base : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_rbdma {
	struct cmd_descr_task_conf task_conf;
	struct cmd_descr_task_desc_conf task_desc_conf;
	struct cmd_descr_tsync_conf_mask tsync_conf_mask;
	struct cmd_descr_tsync_conf_gidx tsync_conf_gidx;
	struct cmd_descr_run_conf0 run_conf0;
	struct cmd_descr_run_conf1 run_conf1;
	struct cmd_descr_task_ext_conf task_ext_conf;
};

struct __attribute__((packed, aligned(4))) cmd_descr_rbdma_ext0 {
	struct cmd_descr_rbdma_ext_header0 rbdma_ext_header0;
	uint64_t tde_chk1_size : 32;
	struct cmd_descr_tde_chk tde_chk[6];
	uint64_t reserved : 64;
};

struct __attribute__((packed, aligned(4))) cmd_descr_rbdma_ext1 {
	struct cmd_descr_rbdma_ext_header1 rbdma_ext_header1;
	struct cmd_descr_dyn_update_para dyn_update_para;
};

/* Constants: Possible enum value of field */
enum rbdma_get_lsync_mp {
	RBDMA_GET_LSYNC_MP_DISABLE = 0,
	RBDMA_GET_LSYNC_MP_ENABLE,
};

enum rbdma_put_lsync_mp {
	RBDMA_PUT_LSYNC_MP_DISABLE = 0,
	RBDMA_PUT_LSYNC_MP_ENABLE,
};

enum rbdma_sw_sg_type {
	RBDMA_SW_SG_TYPE_DEFAULT = 0,
	RBDMA_SW_SG_TYPE_GTH,
	RBDMA_SW_SG_TYPE_SCT,
	RBDMA_SW_SG_TYPE_N2N,
};

enum rbdma_task_type {
	RBDMA_TASK_TYPE_OTO = 0,
	RBDMA_TASK_TYPE_CST,
	RBDMA_TASK_TYPE_GTH,
	RBDMA_TASK_TYPE_SCT,
	RBDMA_TASK_TYPE_OTM,
	RBDMA_TASK_TYPE_RSV1,
	RBDMA_TASK_TYPE_GTHR,
	RBDMA_TASK_TYPE_SCTR,
	RBDMA_TASK_TYPE_PTL,
	RBDMA_TASK_TYPE_IVL,
	RBDMA_TASK_TYPE_VCM,
	RBDMA_TASK_TYPE_DUM,
	RBDMA_TASK_TYPE_DAS,
	RBDMA_TASK_TYPE_RSV2,
	RBDMA_TASK_TYPE_RSV3,
	RBDMA_TASK_TYPE_RSV4,
};

enum rbdma_ext0_ext_descr_type {
	RBDMA_EXT0_EXT_DESCR_TYPE_SG_IRREGULAR = 0,
	RBDMA_EXT0_EXT_DESCR_TYPE_SG_DYNAMIC_PARA,
};

enum rbdma_ext1_descr_type {
	RBDMA_EXT1_DESCR_TYPE_SG_IRREGULAR = 0,
	RBDMA_EXT1_DESCR_TYPE_SG_DYNAMIC_PARA,
};

enum rbdma_ext1_para_update_mask {
	RBDMA_EXT1_PARA_UPDATE_MASK_SRC_ADDR = 0,
	RBDMA_EXT1_PARA_UPDATE_MASK_DST_ADDR,
	RBDMA_EXT1_PARA_UPDATE_MASK_BLK_SIZE,
	RBDMA_EXT1_PARA_UPDATE_MASK_STRIDE,
	RBDMA_EXT1_PARA_UPDATE_MASK_CHUNK_CNT,
};

enum rbdma_ext1_para_update_equation_type {
	RBDMA_EXT1_PARA_UPDATE_EQUATION_TYPE_BINOMIAL = 0,
	RBDMA_EXT1_PARA_UPDATE_EQUATION_TYPE_TRINOMIAL,
};

#endif /* _G_CMD_DESCR_RBDMA_REBEL_H_ */
