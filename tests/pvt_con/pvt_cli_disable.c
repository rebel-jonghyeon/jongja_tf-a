/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <rebel_h_platform.h>
#include <printf.h>
#include <pvt_con.h>
#include <pvt_con_reg.h>
#include "pvt_cli_disable.h"

extern uint64_t pvt_base_address[];
extern uint32_t pvt_n_sensors[];

#if defined(__TARGET_PCIE)
#define CHIPLET_BAT_OFFSET		(0x10000000)
#endif

void pvt_cli_disable_dfs(uint32_t chiplet_id, uint32_t instance_id)
{
	struct pvt_regs *pvt_regs;

#if defined(__TARGET_CP)
	pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

	PVT_DISABLE_DFS_MODE(pvt_regs);
}

void pvt_cli_disable_trip(uint32_t chiplet_id, uint32_t instance_id)
{
	struct pvt_regs *pvt_regs;

#if defined(__TARGET_CP)
	pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

	PVT_DISABLE_TRIP_MODE(pvt_regs);
}

void pvt_cli_disable_process(uint32_t chiplet_id, uint32_t instance_id)
{
	struct pvt_regs *pvt_regs;

#if defined(__TARGET_CP)
	pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_PROC_N_SENSOR(instance_id); ++sensor_id) {
		PVT_DISABLE_PROC_SENSOR(pvt_regs, sensor_id);
	}
	PVT_DISABLE_PROC_CONTROLLER(pvt_regs);
}

void pvt_cli_disable_voltage(uint32_t chiplet_id, uint32_t instance_id)
{
	struct pvt_regs *pvt_regs;

#if defined(__TARGET_CP)
	pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_VOLT_N_SENSOR(instance_id); ++sensor_id) {
		PVT_DISABLE_VOLT_SENSOR(pvt_regs, sensor_id);
	}
	PVT_DISABLE_VOLT_CONTROLLER(pvt_regs);
}

void pvt_cli_disable_temperature(uint32_t chiplet_id, uint32_t instance_id)
{
	struct pvt_regs *pvt_regs;

#if defined(__TARGET_CP)
	pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] + (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(instance_id); ++sensor_id) {
		PVT_DISABLE_TEMP_SENSOR(pvt_regs, sensor_id);
	}
	PVT_DISABLE_TEMP_CONTROLLER(pvt_regs);
}
