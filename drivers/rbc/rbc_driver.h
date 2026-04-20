/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */
#pragma once
#include <stdint.h>

#define EOM_LINE_LENGTH  41
#define INIT_VREF_OFFSET  20

enum {
	BLK_RBC_H00_ID = 0,
	BLK_RBC_H01_ID,
	BLK_RBC_V00_ID,
	BLK_RBC_V01_ID,
	BLK_RBC_V10_ID,
	BLK_RBC_V11_ID,
	NUM_OF_BLK_RBC_ID
};

enum {
	CHIPLET_0_ID = 0,
	CHIPLET_1_ID,
	CHIPLET_2_ID,
	CHIPLET_3_ID,
};

enum {
	ROUTING_DIR_LOCAL = 0,
	ROUTING_DIR_SOUTH,
	ROUTING_DIR_EAST,
	ROUTING_DIR_NORTH,
};

int32_t rbc_driver_init(const int32_t blk_id,
						void * const cmu_base, void * const sysreg_rbc_base, void * const ucie_ss_base);
int32_t rbc_set_target_blk_id(const int32_t blk_id);
int32_t rbc_get_target_blk_id(void);
int32_t rbc_set_lp_mode(const uint32_t lp_mode);
int32_t rbc_lp_entry(void);
int32_t rbc_lp_exit(void);
int32_t rbc_pch_mux_on(void);
int32_t rbc_pch_mux_off(void);
int32_t rbc_aw_ucie_print_eye_diagram(const uint32_t module_sel, const uint32_t lane_id, const uint32_t iter_max);
