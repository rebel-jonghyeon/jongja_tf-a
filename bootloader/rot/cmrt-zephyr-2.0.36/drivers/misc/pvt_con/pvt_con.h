/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include <kernel.h>
#include <device.h>
#include <soc.h>
#include <drivers/cmrt/sac.h>
#include <rebel_h.h>

#include <stdint.h>
#include "pvt_con_reg.h"
#include "pvt_con_config.h"

#define PVT_INSTANCE_OFFSET					(3)
#define PVT_INSTANCE_VOLTAGE(_instance)		(((_instance) * PVT_INSTANCE_OFFSET) + 0)
#define PVT_INSTANCE_TEMPERATURE(_instance)	(((_instance) * PVT_INSTANCE_OFFSET) + 1)
#define PVT_INSTANCE_PROCESS(_instance)		(((_instance) * PVT_INSTANCE_OFFSET) + 2)

#define PVT_INDEX_FALL7		(0b1 << 23U)
#define PVT_INDEX_FALL6		(0b1 << 22U)
#define PVT_INDEX_FALL5		(0b1 << 21U)
#define PVT_INDEX_FALL4		(0b1 << 20U)
#define PVT_INDEX_FALL3		(0b1 << 19U)
#define PVT_INDEX_FALL2		(0b1 << 18U)
#define PVT_INDEX_FALL1		(0b1 << 17U)
#define PVT_INDEX_FALL0		(0b1 << 16U)

#define PVT_INDEX_RISE8		(0b1 << 8U)
#define PVT_INDEX_RISE7		(0b1 << 7U)
#define PVT_INDEX_RISE6		(0b1 << 6U)
#define PVT_INDEX_RISE5		(0b1 << 5U)
#define PVT_INDEX_RISE4		(0b1 << 4U)
#define PVT_INDEX_RISE3		(0b1 << 3U)
#define PVT_INDEX_RISE2		(0b1 << 2U)
#define PVT_INDEX_RISE1		(0b1 << 1U)
#define PVT_INDEX_RISE0		(0b1 << 0U)

#define PVT_CALLBACK_FALL7	(15)
#define PVT_CALLBACK_FALL6	(14)
#define PVT_CALLBACK_FALL5	(13)
#define PVT_CALLBACK_FALL4	(12)
#define PVT_CALLBACK_FALL3	(11)
#define PVT_CALLBACK_FALL2	(10)
#define PVT_CALLBACK_FALL1	(9)
#define PVT_CALLBACK_FALL0	(8)
#define PVT_CALLBACK_RISE7	(7)
#define PVT_CALLBACK_RISE6	(6)
#define PVT_CALLBACK_RISE5	(5)
#define PVT_CALLBACK_RISE4	(4)
#define PVT_CALLBACK_RISE3	(3)
#define PVT_CALLBACK_RISE2	(2)
#define PVT_CALLBACK_RISE1	(1)
#define PVT_CALLBACK_RISE0	(0)

/**
 * PVT APIs
 */
struct pvt_regs;

struct pvt_samsung_api {
	/* Configurations */
	uint32_t init;
	uint32_t vol_enable_sensor;
	uint32_t temp_enable_sensor;
	uint32_t proc_enable_sensor;
	uint32_t vol_get_current_value;
	uint32_t temp_get_current_value;
	uint32_t proc_get_current_value;
	uint32_t vol_get_past_value;
	uint32_t temp_get_past_value;
	uint32_t proc_get_past_value;
	/* Emulation */
	uint32_t emul_set_next_time;
	uint32_t emul_set_next_data;
	uint32_t emul_enable_emulation;
	uint32_t emul_disable_emulation;
	/* Calibration */
	uint32_t temp_apply_calibration;
	uint32_t temp_apply_reverse_calibration;
};

/* Enable sensor */
void pvt_vol_enable_sensor(uint64_t pvt_addr,
						   uint32_t voltage_range,
						   uint32_t sampling_interval,
						   uint32_t average_selection_ts_vs);
void pvt_temp_enable_sensor(uint64_t pvt_addr,
							uint32_t fast_conversion,
							uint32_t dfs_mode,
							uint32_t dfs_enable,
							uint32_t trip_mode,
							uint32_t trip_enable,
							uint32_t sampling_interval,
							uint32_t average_selection_ts_vs);
void pvt_proc_enable_sensor(uint64_t pvt_addr,
							uint32_t process_range,
							uint32_t sampling_interval,
							uint32_t average_selection_ps);

/* Get current value */
uint32_t pvt_vol_get_current_value(uint64_t pvt_addr,
								   uint32_t sensor_id);
uint32_t pvt_temp_get_current_value(uint64_t pvt_addr,
									uint32_t sensor_id);
uint32_t pvt_proc_get_current_value(uint64_t pvt_addr,
									uint32_t sensor_id);

/* Get past value */
uint32_t pvt_vol_get_past_value(uint64_t pvt_addr,
								uint32_t sensor_id,
								uint32_t past_index);
uint32_t pvt_temp_get_past_value(uint64_t pvt_addr,
								 uint32_t sensor_id,
								 uint32_t past_index);
uint32_t pvt_proc_get_past_value(uint64_t pvt_addr,
								 uint32_t sensor_id,
								 uint32_t past_index);

/* Emulation mode */
void pvt_emul_set_next_time(uint64_t pvt_addr,
							uint32_t next_time);
void pvt_emul_set_next_data(uint64_t pvt_addr,
							uint32_t next_data);
void pvt_emul_enable_emulation(uint64_t pvt_addr);
void pvt_emul_disable_emulation(uint64_t pvt_addr);

/* Temperature Calibration */
uint32_t pvt_temp_apply_calibration(uint64_t pvt_addr,
									uint32_t sensor_id,
									uint32_t temperature);
uint32_t pvt_temp_apply_reverse_calibration(uint64_t pvt_addr,
											uint32_t sensor_id,
											uint32_t calibrated_temperature);

#define SAC_ADDRESS		(struct pvt_regs *)(0x40000000U)
