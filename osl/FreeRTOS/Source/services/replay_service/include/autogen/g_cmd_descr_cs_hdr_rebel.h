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

#ifndef _G_CMD_DESCR_CS_HDR_REBEL_H_
#define _G_CMD_DESCR_CS_HDR_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_CS_HDR_ARCH_MAJOR 0
#define CMD_DESCR_CS_HDR_ARCH_MINOR 9
#define CMD_DESCR_CS_HDR_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CONST_BUF		  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_MULTI_DEV_SYNC	  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CS_DRIVEN_HDMA	  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CP_DEP_GET_CMD_CNT 18
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CP_DEP_PUT_CMD_CNT 18
#define BIT_WIDTH_CMD_DESCR_CS_HDR_ENABLE_CMGR		  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_JCR_UPDATE		  2
#define BIT_WIDTH_CMD_DESCR_CS_HDR_SW_SG_UDMA		  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_RESERVED0		  5
#define BIT_WIDTH_CMD_DESCR_CS_HDR_SW_SG_RBDMA		  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_DYN_DDMA			  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_MULTI_TSTC		  1
#define BIT_WIDTH_CMD_DESCR_CS_HDR_RESERVED1		  21
#define BIT_WIDTH_CMD_DESCR_CS_HDR_DEVICE_ID		  4
#define BIT_WIDTH_CMD_DESCR_CS_HDR_REV_ID			  2
#define BIT_WIDTH_CMD_DESCR_CS_HDR_ARCH_MAJOR		  4
#define BIT_WIDTH_CMD_DESCR_CS_HDR_ARCH_MINOR		  4
#define BIT_WIDTH_CMD_DESCR_CS_HDR_ARCH_PATCH		  4
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CHIP_ID			  8
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CHIPLET_ID		  2
#define BIT_WIDTH_CMD_DESCR_CS_HDR_CS_ID			  16
#define BIT_WIDTH_CMD_DESCR_CS_HDR_COMPUTE_CNT		  16
#define BIT_WIDTH_CMD_DESCR_CS_HDR_UDMA_CNT			  16
#define BIT_WIDTH_CMD_DESCR_CS_HDR_LPUDMA_CNT		  16
#define BIT_WIDTH_CMD_DESCR_CS_HDR_STUDMA_CNT		  16
#define BIT_WIDTH_CMD_DESCR_CS_HDR_RBDMA_CNT		  16

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_cs {
	uint64_t const_buf : 1;
	uint64_t multi_dev_sync : 1;
	uint64_t cs_driven_hdma : 1;
	uint64_t cp_dep_get_cmd_cnt : 18;
	uint64_t cp_dep_put_cmd_cnt : 18;
	uint64_t enable_cmgr : 1;
	uint64_t reserved : 24;
};

struct __attribute__((packed, aligned(4))) cmd_descr_hw {
	uint32_t jcr_update : 2;
	uint32_t sw_sg_udma : 1;
	uint32_t reserved0 : 5;
	uint32_t sw_sg_rbdma : 1;
	uint32_t dyn_ddma : 1;
	uint32_t multi_tstc : 1;
	uint32_t reserved1 : 21;
};

struct __attribute__((packed, aligned(4))) cmd_descr_id {
	uint64_t device_id : 4;
	uint64_t rev_id : 2;
	uint64_t arch_major : 4;
	uint64_t arch_minor : 4;
	uint64_t arch_patch : 4;
	uint64_t chip_id : 8;
	uint64_t chiplet_id : 2;
	uint64_t reserved0 : 8;
	uint64_t cs_id : 16;
	uint64_t reserved1 : 12;
};

struct __attribute__((packed, aligned(4))) cmd_descr_feature_req {
	struct cmd_descr_cs cs;
	struct cmd_descr_hw hw;
};

struct __attribute__((packed, aligned(4))) cmd_descr_workload_desc {
	uint64_t compute_cnt : 16;
	uint64_t udma_cnt : 16;
	uint64_t lpudma_cnt : 16;
	uint64_t studma_cnt : 16;
	uint64_t rbdma_cnt : 16;
	uint64_t reserved : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_cs_hdr {
	struct cmd_descr_id id;
	struct cmd_descr_feature_req feature_req;
	struct cmd_descr_workload_desc workload_desc;
};

/* Constants: Possible enum value of field */
enum cs_hdr_const_buf {
	CS_HDR_CONST_BUF_NOT_USE = 0,
	CS_HDR_CONST_BUF_USE,
};

enum cs_hdr_multi_dev_sync {
	CS_HDR_MULTI_DEV_SYNC_NOT_USE = 0,
	CS_HDR_MULTI_DEV_SYNC_USE,
};

enum cs_hdr_cs_driven_hdma {
	CS_HDR_CS_DRIVEN_HDMA_NOT_USE = 0,
	CS_HDR_CS_DRIVEN_HDMA_USE,
};

enum cs_hdr_jcr_update {
	CS_HDR_JCR_UPDATE_NOT_USE = 0,
	CS_HDR_JCR_UPDATE_CP_UPDATED,
	CS_HDR_JCR_UPDATE_DNC_UPDATED,
	CS_HDR_JCR_UPDATE_RESERVED,
};

enum cs_hdr_sw_sg_udma {
	CS_HDR_SW_SG_UDMA_NOT_USE = 0,
	CS_HDR_SW_SG_UDMA_USE,
};

enum cs_hdr_sw_sg_rbdma {
	CS_HDR_SW_SG_RBDMA_NOT_USE = 0,
	CS_HDR_SW_SG_RBDMA_USE,
};

enum cs_hdr_dyn_ddma {
	CS_HDR_DYN_DDMA_NOT_USE = 0,
	CS_HDR_DYN_DDMA_USE,
};

enum cs_hdr_multi_tstc {
	CS_HDR_MULTI_TSTC_NOT_USE = 0,
	CS_HDR_MULTI_TSTC_USE,
};

enum cs_hdr_device_id {
	CS_HDR_DEVICE_ID_ION = 0,
	CS_HDR_DEVICE_ID_ATOM,
	CS_HDR_DEVICE_ID_REBEL_H,
};

enum cs_hdr_rev_id {
	CS_HDR_REV_ID_DEV = 0,
	CS_HDR_REV_ID_EVT0,
	CS_HDR_REV_ID_EVT1,
	CS_HDR_REV_ID_MASS,
};

#endif /* _G_CMD_DESCR_CS_HDR_REBEL_H_ */
