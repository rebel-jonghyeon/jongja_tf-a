/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#pragma once

#include <stdint.h>

#include "hbm3.h"
#include "icon.h"
#include "tmrs.h"
#include "ddr_csr.h"
#include "hbm3ephy.h"
#include "sysreg_dram.h"

#define HBM3_INIT_OFFSET_DQ 0x34
#define HBM3_INIT_VREF 0x4040
#define HBM3_INIT_DS 0x2d

#define PHY_VWM_LEN (DQ_WIDTH + ECC_WIDTH + SEV_WIDTH + DBI_WIDTH)
#define PHY_OFFSET_LEN (2 * (DQ_WIDTH + ECC_WIDTH + SEV_WIDTH + DBI_WIDTH + DWORD_NUM))

union __attribute__((packed)) phy_vwm {
	uint16_t val[PHY_VWM_LEN];
	struct {
		uint16_t dq[DQ_WIDTH];
		uint16_t ecc[ECC_WIDTH];
		uint16_t sev[SEV_WIDTH];
		uint16_t dbi[DBI_WIDTH];
	};
};

union __attribute__((packed)) phy_offset {
	uint16_t val[PHY_OFFSET_LEN];
	struct {
		uint16_t p_dq[DQ_WIDTH];
		uint16_t n_dq[DQ_WIDTH];
		uint16_t p_ecc[ECC_WIDTH];
		uint16_t n_ecc[ECC_WIDTH];
		uint16_t p_sev[SEV_WIDTH];
		uint16_t n_sev[SEV_WIDTH];
		uint16_t p_dbi[DBI_WIDTH];
		uint16_t n_dbi[DBI_WIDTH];
		uint16_t p_rdqs[DWORD_NUM];
		uint16_t n_rdqs[DWORD_NUM];
	};
};

enum HBM3_ID {
	HBM3_VER_NEW = 0,
	HBM3_VER_OLD = 1,
};

/* Common */
int32_t hbm3_init(uint32_t chiplet_id);
void hbm_ecc_scrub_init(uint32_t chiplet_id);
void add_delay(void);
uint8_t get_read_latency(uint8_t datarate);
uint8_t get_write_latency(uint8_t datarate);
uint32_t icon_mrs(struct hbm3_config *cfg, enum ch_select ch);
uint8_t get_lotid_for_hbm(void);

#if defined(HBM_EOM)
void mt_alg_pre(uint32_t chiplet_id, uint32_t ch);
void mt_alg_post(uint32_t chiplet_id, uint32_t ch);
int mt_alg_dq_eom(uint32_t chiplet_id, uint32_t ch, uint8_t dq);
int mt_alg_channel_eom(uint32_t chiplet_id, uint32_t ch);
void run_eom_dq(uint32_t chiplet_id, uint32_t ch);
void run_eom(uint32_t chiplet_id);
#elif defined(HBM_AMT)
int mt_alg_test(uint32_t chiplet_id, uint32_t ch);
int mt_arb_test(uint32_t chiplet_id, uint32_t ch);
int mt_amt_test(uint32_t chiplet_id, uint32_t ch);
int mt_mta_test(uint32_t chiplet_id, uint32_t ch);
void run_memtest(uint32_t chiplet_id);
#endif
