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

#ifndef _G_SHM_REG_COMMON_H_
#define _G_SHM_REG_COMMON_H_

#define ADDR_OFFSET_SHM_REG_IP_INFO0		0x000
#define ADDR_OFFSET_SHM_REG_IP_INFO1		0x004
#define ADDR_OFFSET_SHM_REG_IP_INFO2		0x008
#define ADDR_OFFSET_SHM_REG_IP_INFO3		0x00C
#define ADDR_OFFSET_SHM_REG_MALF			0x020
#define ADDR_OFFSET_SHM_REG_INTR_VEC		0x030
#define ADDR_OFFSET_SHM_REG_INTR_ERROR_MASK 0x034
#define ADDR_OFFSET_SHM_REG_INTR_INFO_MASK	0x038
#define ADDR_OFFSET_SHM_REG_AXI_PORT		0x03C
#define ADDR_OFFSET_SHM_REG_TRIG			0x040
#define ADDR_OFFSET_SHM_REG_CLEAR			0x044
#define ADDR_OFFSET_SHM_REG_ENAB_0			0x048
#define ADDR_OFFSET_SHM_REG_ENAB_1			0x04C

#define ADDR_OFFSET_SHM_REG_FCONF			0x050

#define ADDR_OFFSET_SHM_REG_GREG0			0x05C
#define ADDR_OFFSET_SHM_REG_GREG1			0x060
#define ADDR_OFFSET_SHM_REG_GREG2			0x064
#define ADDR_OFFSET_SHM_REG_GREG3			0x068
#define ADDR_OFFSET_SHM_REG_CEA_RSP			0x070
#define ADDR_OFFSET_SHM_REG_GRPT_MODE		0x0BC
#define ADDR_OFFSET_SHM_REG_GRPT0			0x0C0
#define ADDR_OFFSET_SHM_REG_GRPT1			0x0C4
#define ADDR_OFFSET_SHM_REG_GRPT2			0x0C8
#define ADDR_OFFSET_SHM_REG_GRPT3			0x0CC
#define ADDR_OFFSET_SHM_REG_GRPT4			0x0D0
#define ADDR_OFFSET_SHM_REG_GRPT5			0x0D4
#define ADDR_OFFSET_SHM_REG_GRPT6			0x0D8
#define ADDR_OFFSET_SHM_REG_GRPT7			0x0DC
#define ADDR_OFFSET_SHM_REG_GRPT8			0x0E0
#define ADDR_OFFSET_SHM_REG_GRPT9			0x0E4
#define ADDR_OFFSET_SHM_REG_GRPT10			0x0E8
#define ADDR_OFFSET_SHM_REG_GRPT11			0x0EC
#define ADDR_OFFSET_SHM_REG_GRPT12			0x0F0
#define ADDR_OFFSET_SHM_REG_GRPT13			0x0F4
#define ADDR_OFFSET_SHM_REG_GRPT14			0x0F8
#define ADDR_OFFSET_SHM_REG_GRPT15			0x0FC

union shm_reg_ip_info0 {
	struct __attribute__((packed)) {
		uint32_t release_date : 32;
	};
	uint32_t bits;
};

union shm_reg_ip_info1 {
	struct __attribute__((packed)) {
		uint32_t min_ver : 8;
		uint32_t max_ver : 8;
		uint32_t ip_ver : 8;
		uint32_t ip_id : 8;
	};
	uint32_t bits;
};

union shm_reg_ip_info2 {
	struct __attribute__((packed)) {
		uint32_t shm_unit_id : 8;
		uint32_t rdsn_rtid : 8;
		uint32_t rd_lat : 8;
		uint32_t wr_lat : 8;
	};
	uint32_t bits;
};

union shm_reg_ip_info3 {
	struct __attribute__((packed)) {
		uint32_t n_bank : 8;
		uint32_t etc : 8;
		uint32_t capa_man : 8;
		uint32_t capa_exp : 8;
	};
	uint32_t bits;
};

union shm_reg_malf {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_intr_vec {
	struct __attribute__((packed)) {
		uint32_t tpg_done : 1;
		uint32_t wrm_done : 1;
		uint32_t intr_wstt : 1;
		uint32_t intr_rstt : 1;
		uint32_t res : 12;
		uint32_t intr_malf : 1;
		uint32_t intr_derr : 1;
		uint32_t intr_serr : 1;
		uint32_t res1 : 13;
	};
	uint32_t bits;
};

union shm_reg_intr_error_mask {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_intr_info_mask {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_axi_port {
	struct __attribute__((packed)) {
		uint32_t reserve_0 : 8;
		uint32_t lock_en : 1;
		uint32_t reserve_1 : 7;
		uint32_t lock_mode : 2;
		uint32_t reserve_2 : 6;
		uint32_t user_en : 5;
		uint32_t reserve_3 : 3;
	};
	uint32_t bits;
};

union shm_reg_trig {
	struct __attribute__((packed)) {
		uint32_t wrm : 1;
		uint32_t tpg : 1;
		uint32_t tpg_all : 1;
		uint32_t etc : 29;
	};
	uint32_t bits;
};

union shm_reg_clear {
	struct __attribute__((packed)) {
		uint32_t all_hard : 1;
		uint32_t all_soft : 1;
		uint32_t intr_clear : 1;
		uint32_t axc : 1;
		uint32_t axd : 1;
		uint32_t tot : 1;
		uint32_t lat : 1;
		uint32_t tpg : 1;
		uint32_t wrm : 1;
		uint32_t eca : 1;
		uint32_t ecr : 1;
		uint32_t eij : 1;
		uint32_t rdb : 1;
		uint32_t dummy : 1;
		uint32_t cfc : 1;
		uint32_t cdp : 1;
		uint32_t cea : 1;
		uint32_t stt : 1;
		uint32_t etc : 14;
	};
	uint32_t bits;
};

union shm_reg_enab_0 {
	struct __attribute__((packed)) {
		uint32_t atl : 1;
		uint32_t lat : 1;
		uint32_t tpg : 1;
		uint32_t tgs : 1;
		uint32_t eij : 1;
		uint32_t wrm : 1;
		uint32_t ecr : 1;
		uint32_t stt : 1;
		uint32_t etc : 24;
	};
	uint32_t bits;
};

union shm_reg_enab_1 {
	struct __attribute__((packed)) {
		uint32_t rdb : 1;
		uint32_t tot : 1;
		uint32_t ecc : 1;
		uint32_t eca : 1;
		uint32_t dontuse : 1;
		uint32_t pld : 1;
		uint32_t bst : 1;
		uint32_t etc : 25;
	};
	uint32_t bits;
};

union shm_reg_greg0 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_greg1 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_greg2 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_greg3 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_cea_rsp {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt_mode {
	struct __attribute__((packed)) {
		uint32_t ai : 8;
	};
	uint32_t bits;
};

union shm_reg_grpt0 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt1 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt2 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt3 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt4 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt5 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt6 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt7 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt8 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt9 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt10 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt11 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt12 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt13 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt14 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

union shm_reg_grpt15 {
	struct __attribute__((packed)) {
		uint32_t ai : 32;
	};
	uint32_t bits;
};

#endif /* _G_SHM_REG_COMMON_H_*/
