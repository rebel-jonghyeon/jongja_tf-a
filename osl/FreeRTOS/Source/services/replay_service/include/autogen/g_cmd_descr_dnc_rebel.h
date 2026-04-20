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

#ifndef _G_CMD_DESCR_DNC_REBEL_H_
#define _G_CMD_DESCR_DNC_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_DNC_ARCH_MAJOR 0
#define CMD_DESCR_DNC_ARCH_MINOR 9
#define CMD_DESCR_DNC_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_DNC_CHUNK_SIZE						   15
#define BIT_WIDTH_CMD_DESCR_DNC_PADDING_SIZE					   12
#define BIT_WIDTH_CMD_DESCR_DNC_NUM_OF_CHUNK					   5
#define BIT_WIDTH_CMD_DESCR_DNC_JCR_CNT							   5
#define BIT_WIDTH_CMD_DESCR_DNC_BUF_IDX							   8
#define BIT_WIDTH_CMD_DESCR_DNC_DATA_GROUP_IDX					   8
#define BIT_WIDTH_CMD_DESCR_DNC_DATA_SEL_MODE					   1
#define BIT_WIDTH_CMD_DESCR_DNC_JCR_BUF_ACCESS_TYPE				   1
#define BIT_WIDTH_CMD_DESCR_DNC_RESERVED1						   1
#define BIT_WIDTH_CMD_DESCR_DNC_JCR_BUF_ACCESS_MODE				   1
#define BIT_WIDTH_CMD_DESCR_DNC_JCR_BUF_ADDR					   24
#define BIT_WIDTH_CMD_DESCR_DNC_VA								   16
#define BIT_WIDTH_CMD_DESCR_DNC_VA_SIZE							   16
#define BIT_WIDTH_CMD_DESCR_DNC_UDMA_SG_EXT_STRIDE_SIZE			   15
#define BIT_WIDTH_CMD_DESCR_DNC_UDMA_SG_CHUNK_NUM				   5
#define BIT_WIDTH_CMD_DESCR_DNC_VF_ID_MAX						   1
#define BIT_WIDTH_CMD_DESCR_DNC_AUTO_FETCH_BFIX					   1
#define BIT_WIDTH_CMD_DESCR_DNC_ENQ_RPT							   1
#define BIT_WIDTH_CMD_DESCR_DNC_CHKIN_RPT						   1
#define BIT_WIDTH_CMD_DESCR_DNC_DONE_RPT						   1
#define BIT_WIDTH_CMD_DESCR_DNC_CDUMP							   1
#define BIT_WIDTH_CMD_DESCR_DNC_WAIT							   1
#define BIT_WIDTH_CMD_DESCR_DNC_TOCHK							   1
#define BIT_WIDTH_CMD_DESCR_DNC_TSYNC_CHK						   3
#define BIT_WIDTH_CMD_DESCR_DNC_TSYNC_CHK_CLR					   1
#define BIT_WIDTH_CMD_DESCR_DNC_TSYNC_SET						   3
#define BIT_WIDTH_CMD_DESCR_DNC_WAIT_PREQ						   1
#define BIT_WIDTH_CMD_DESCR_DNC_TASK_POFS						   8
#define BIT_WIDTH_CMD_DESCR_DNC_RPT_POFS						   8
#define BIT_WIDTH_CMD_DESCR_DNC_PROG0_COMPUTE					   32
#define BIT_WIDTH_CMD_DESCR_DNC_ADDR_EXT1						   8
#define BIT_WIDTH_CMD_DESCR_DNC_ADDR_SP							   16
#define BIT_WIDTH_CMD_DESCR_DNC_SKIP_BARRIER					   1
#define BIT_WIDTH_CMD_DESCR_DNC_OPTION							   2
#define BIT_WIDTH_CMD_DESCR_DNC_QOS								   1
#define BIT_WIDTH_CMD_DESCR_DNC_INSIST							   1
#define BIT_WIDTH_CMD_DESCR_DNC_TLB_MISS_RPT					   1
#define BIT_WIDTH_CMD_DESCR_DNC_PROG_OFF						   1
#define BIT_WIDTH_CMD_DESCR_DNC_CHK_CODE						   10
#define BIT_WIDTH_CMD_DESCR_DNC_SET_DEST						   6
#define BIT_WIDTH_CMD_DESCR_DNC_SET_CODE						   16
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_PROG1					   32
#define BIT_WIDTH_CMD_DESCR_DNC_CORE_AFFINITY					   64
#define BIT_WIDTH_CMD_DESCR_DNC_HW_LOCK_STEP					   1
#define BIT_WIDTH_CMD_DESCR_DNC_LOCK_STEP_TARGET				   4
#define BIT_WIDTH_CMD_DESCR_DNC_LOCK_STEP_GROUP_IDX				   6
#define BIT_WIDTH_CMD_DESCR_DNC_CMGR_PUT_SYNC_CMD_ID_VALID		   1
#define BIT_WIDTH_CMD_DESCR_DNC_CMGR_PUT_SYNC_CMD_ID			   16
#define BIT_WIDTH_CMD_DESCR_DNC_PROG1							   32
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_EXT_DESCR_TYPE		   4
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_PARA_UPDATE_MASK_CHIPLET 4
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_ENABLE_PARA_DIFF		   1
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_PARA_DIFF_BOUNDARY	   1
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_PARA_UPDATE_MASK_DNC	   48
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_SIZE_DIFF				   32
#define BIT_WIDTH_CMD_DESCR_DNC_EXT1_PARA_ADDR_DIFF				   32

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_prog0_udma {
	uint32_t chunk_size : 15;
	uint32_t padding_size : 12;
	uint32_t num_of_chunk : 5;
};

struct __attribute__((packed, aligned(4))) cmd_descr_const_buf {
	uint32_t jcr_cnt : 5;
	uint32_t buf_idx : 8;
	uint32_t data_group_idx : 8;
	uint32_t data_sel_mode : 1;
	uint32_t reserved : 7;
	uint32_t jcr_buf_access_type : 1;
	uint32_t reserved1 : 1;
	uint32_t jcr_buf_access_mode : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_jcr_buf {
	uint32_t jcr_cnt : 5;
	uint32_t jcr_buf_addr : 24;
	uint32_t jcr_buf_access_type : 1;
	uint32_t reserved : 1;
	uint32_t jcr_buf_access_mode : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_tlb_info {
	uint32_t va : 16;
	uint32_t va_size : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_udma_sg_ext {
	uint32_t udma_sg_ext_stride_size : 15;
	uint32_t udma_sg_chunk_num : 5;
	uint32_t reserved : 12;
};

struct __attribute__((packed, aligned(4))) cmd_descr_mode {
	uint32_t vf_id_max : 1;
	uint32_t auto_fetch_bfix : 1;
	uint32_t enq_rpt : 1;
	uint32_t chkin_rpt : 1;
	uint32_t done_rpt : 1;
	uint32_t cdump : 1;
	uint32_t wait : 1;
	uint32_t tochk : 1;
	uint32_t tsync_chk : 3;
	uint32_t tsync_chk_clr : 1;
	uint32_t tsync_set : 3;
	uint32_t wait_preq : 1;
	uint32_t task_pofs : 8;
	uint32_t rpt_pofs : 8;
};

union __attribute__((packed, aligned(4))) cmd_descr_prog0_union {
	uint32_t prog0_compute : 32;
	struct cmd_descr_prog0_udma prog0_udma;
};

struct __attribute__((packed, aligned(4))) cmd_descr_prog2 {
	uint32_t addr_ext1 : 8;
	uint32_t addr_sp : 16;
	uint32_t skip_barrier : 1;
	uint32_t option : 2;
	uint32_t qos : 1;
	uint32_t insist : 1;
	uint32_t reserved : 1;
	uint32_t tlb_miss_rpt : 1;
	uint32_t prog_off : 1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_tsync_conf {
	uint32_t chk_code : 10;
	uint32_t set_dest : 6;
	uint32_t set_code : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_tlb {
	struct cmd_descr_tlb_info tlb_info;
	struct cmd_descr_tlb_info tlb_info1;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext {
	struct cmd_descr_udma_sg_ext udma_sg_ext;
	uint32_t reserved : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_para {
	union cmd_descr_prog0_union prog0_union;
	uint32_t prog1 : 32;
	struct cmd_descr_prog2 prog2;
	struct cmd_descr_tsync_conf tsync_conf;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_task_conf {
	uint64_t core_affinity : 64;
	uint64_t hw_lock_step : 1;
	uint64_t lock_step_target : 4;
	uint64_t lock_step_group_idx : 6;
	uint64_t cmgr_put_sync_cmd_id_valid : 1;
	uint64_t cmgr_put_sync_cmd_id : 16;
	uint64_t reserved : 4;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_task {
	struct cmd_descr_mode mode;
	union cmd_descr_prog0_union prog0_union;
	uint32_t prog1 : 32;
	struct cmd_descr_prog2 prog2;
	struct cmd_descr_tsync_conf tsync_conf;
};

union __attribute__((packed, aligned(4))) cmd_descr_jcr_union {
	struct cmd_descr_const_buf const_buf;
	struct cmd_descr_jcr_buf jcr_buf;
};

union __attribute__((packed, aligned(4))) cmd_descr_dnc_ext_union {
	struct cmd_descr_dnc_tlb dnc_tlb;
	struct cmd_descr_dnc_ext dnc_ext;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext_header {
	uint64_t ext_descr_type : 4;
	uint64_t para_update_mask_chiplet : 4;
	uint64_t enable_para_diff : 1;
	uint64_t para_diff_boundary : 1;
	uint64_t reserved : 6;
	uint64_t para_update_mask_dnc : 48;
};

struct __attribute__((packed, aligned(4))) cmd_descr_para_diff {
	uint64_t size_diff : 32;
	uint64_t addr_diff : 32;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc {
	struct cmd_descr_dnc_task_conf dnc_task_conf;
	struct cmd_descr_dnc_task dnc_task;
	union cmd_descr_jcr_union jcr_union;
	union cmd_descr_dnc_ext_union dnc_ext_union;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext1_para {
	struct cmd_descr_dnc_ext_header dnc_ext_header;
	struct cmd_descr_para para[3];
	struct cmd_descr_para_diff para_diff;
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext2_para {
	struct cmd_descr_dnc_ext_header dnc_ext_header;
	struct cmd_descr_para para[3];
	struct cmd_descr_para_diff para_diff;
	struct cmd_descr_para para1[4];
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext3_para {
	struct cmd_descr_dnc_ext_header dnc_ext_header;
	struct cmd_descr_para para[3];
	struct cmd_descr_para_diff para_diff;
	struct cmd_descr_para para1[12];
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext4_para {
	struct cmd_descr_dnc_ext_header dnc_ext_header;
	struct cmd_descr_para para[3];
	struct cmd_descr_para_diff para_diff;
	struct cmd_descr_para para1[28];
};

struct __attribute__((packed, aligned(4))) cmd_descr_dnc_ext5_para {
	struct cmd_descr_dnc_ext_header dnc_ext_header;
	struct cmd_descr_para para[3];
	struct cmd_descr_para_diff para_diff;
	struct cmd_descr_para para1[60];
};

/* Constants: Possible enum value of field */
enum dnc_data_sel_mode {
	DNC_DATA_SEL_MODE_COMMON = 0,
	DNC_DATA_SEL_MODE_PER_TASK,
};

enum dnc_jcr_buf_access_type {
	DNC_JCR_BUF_ACCESS_TYPE_COMMON = 0,
	DNC_JCR_BUF_ACCESS_TYPE_PER_DNC,
};

enum dnc_jcr_buf_access_mode {
	DNC_JCR_BUF_ACCESS_MODE_ADDR_BASED = 0,
	DNC_JCR_BUF_ACCESS_MODE_IDX_BASED,
};

enum dnc_tsync_chk {
	DNC_TSYNC_CHK_BYPS = 0,
	DNC_TSYNC_CHK_QV,
	DNC_TSYNC_CHK_QB,
	DNC_TSYNC_CHK_TC0,
	DNC_TSYNC_CHK_TC1,
	DNC_TSYNC_CHK_RSVD5,
	DNC_TSYNC_CHK_RSVD6,
	DNC_TSYNC_CHK_RSVD7,
};

enum dnc_tsync_set {
	DNC_TSYNC_SET_BYPS = 0,
	DNC_TSYNC_SET_QMD,
	DNC_TSYNC_SET_QAD,
	DNC_TSYNC_SET_RSVD3,
	DNC_TSYNC_SET_TCMD,
	DNC_TSYNC_SET_TCAD,
	DNC_TSYNC_SET_PDCC,
	DNC_TSYNC_SET_SCND,
};

enum dnc_option_comp {
	DNC_OPTION_SHM_RCE_COMP = 1,
	DNC_OPTION_SHM_PRL_COMP,
};

enum dnc_option_ldudma {
	DNC_OPTION_BL1_LDUDMA,
	DNC_OPTION_BL2_LDUDMA,
	DNC_OPTION_BL4_LDUDMA,
	DNC_OPTION_BL8_LDUDMA,
};

enum dnc_option_lpudma {
	DNC_OPTION_BL1_LPUDMA,
	DNC_OPTION_BL2_LPUDMA,
	DNC_OPTION_BL4_LPUDMA,
	DNC_OPTION_BL8_LPUDMA,
};

enum dnc_option_studma {
	DNC_OPTION_BL1_STUDMA,
	DNC_OPTION_BL2_STUDMA,
	DNC_OPTION_BL4_STUDMA,
	DNC_OPTION_BL8_STUDMA,
};

enum dnc_qos {
	DNC_QOS_QL = 0,
	DNC_QOS_QH,
};

enum dnc_insist {
	DNC_INSIST_NORM = 0,
	DNC_INSIST_URGT,
};

enum dnc_set_dest_tsync_set7 {
	DNC_SET_DEST_RBDMA0_TSYNC_SET7,
	DNC_SET_DEST_RBDMA1_TSYNC_SET7,
	DNC_SET_DEST_RBDMA2_TSYNC_SET7,
	DNC_SET_DEST_RBDMA3_TSYNC_SET7,
};

enum dnc_hw_lock_step {
	DNC_HW_LOCK_STEP_TASK_INDEPENDENT_MODE = 0,
	DNC_HW_LOCK_STEP_TASK_SYNCHRONIZED_MODE,
};

enum dnc_ext1_para_para_diff_boundary {
	DNC_EXT1_PARA_PARA_DIFF_BOUNDARY_CHIP = 0,
	DNC_EXT1_PARA_PARA_DIFF_BOUNDARY_CHIPLET,
};

#endif /* _G_CMD_DESCR_DNC_REBEL_H_ */
