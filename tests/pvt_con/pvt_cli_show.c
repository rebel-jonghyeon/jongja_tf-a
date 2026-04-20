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
#include "pvt_cli_show.h"
#include <system_api.h>

extern uint64_t pvt_base_address[];
extern uint32_t pvt_n_sensors[];

#if defined(__TARGET_PCIE)
#define CHIPLET_BAT_OFFSET		(0x08000000)
#endif

char *inst_name[5] = {
	"PVT_ROT",
	"PVT0CTRL_DCL0",
	"PVT1CTRL_DCL0",
	"PVT0CTRL_DCL1",
	"PVT1CTRL_DCL1"
};

char *pvt_process_sensor_info[32] = {
	"INV_D0P7_LVT",
	"INV_D1_LVT",
	"INV_D2_LVT",
	"INV_D4_LVT",
	"INV_D8_LVT",
	"INV_D16_LVT",
	"INV_D0P7_RVT",
	"INV_D1_RVT",
	"INV_D2_RVT",
	"INV_D4_RVT",
	"INV_D0P7_SLVT",
	"INV_D1_SLVT",
	"INV_D2_SLVT",
	"INV_D4_SLVT",
	"INV_D1_LVT_L06",
	"INV_D4_LVT_L06",
	"INV_D1_RVT_L06",
	"INV_D4_RVT_L06",
	"INV_D1_SLVT_L06",
	"INV_D4_SLVT_L06",
	"DLY_D1_RVT_L06",
	"DLY_D4_RVT_L06",
	"NAND_D2_LVT",
	"NOR2_D2_LVT",
	"INV_D0P7_ULVT",
	"INV_D1_ULVT",
	"INV_D2_ULVT",
	"INV_D4_ULVT",
	"INV_D1_ULVT_L06",
	"INV_D2_ULVT_L06",
	"NPG_LVT",
	"PPG_LVT",
};

void pvt_cli_show_process(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t current_value;

#if defined(ZEBU)
	for (uint32_t instance_id = 0; instance_id < 1; ++instance_id) {
#else
	for (uint32_t instance_id = 0; instance_id < PVT_N_INSTANCE; ++instance_id) {
#endif
		printf("\n| %-15s | Chiplet-0  | Chiplet-1  | Chiplet-2  | Chiplet-3  |\n", inst_name[instance_id]);
		printf("-----------------------------------------------------------------------\n");
		for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
			PVT_ENABLE_PROC_CONTROLLER(pvt_regs);
		}

		for (uint32_t sensor_id = 0; sensor_id < PVT_GET_PROC_N_SENSOR(instance_id); ++sensor_id) {
			printf("| %15s", pvt_process_sensor_info[sensor_id]);
			for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(__TARGET_CP)
				pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
						   (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
				pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
						   (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

				current_value = PVT_GET_CURRENT_PROC_VALUE(pvt_regs, sensor_id);
				printf(" | %10u", current_value);
			}
			printf(" |\n");
		}
	}
}

/* [instance_id][sensor_id][name + existence] */
char *pvt_voltage_sensor_info[5][7][6] = {
	{
		// Available in EVT1
		{"BLK_ROT",		"VDD_TOP_BUS",	"1", "1", "1", "1",},
		{"BLK_PCIE",	"VDD_PCIE",		"1", "0", "0", "1",},
		{"BLK_CP0",		"VDD_CP",		"1", "1", "1", "1",},
		{"BLK_CP1",		"VDD_CP",		"1", "1", "1", "1",},
		{"BLK_RBC_V00",	"VDD_RBC_V",	"0", "1", "1", "0",},
		{},
		{"BLK_DRAM",	"VDD_DRAM",		"1", "1", "1", "1",},
	},
	{
		{"BLK_DCL0",	"VDD_DCL",		"1", "1", "1", "1",},
		{"BLK_RBC_H00",	"VDD_RBC_H",	"1", "1", "1", "1",},
		{},
	},
	{
		{},
	},
	{
		{"BLK_DCL1",	"VDD_DCL",		"1", "1", "1", "1",},
	},
	{
		{},
		{"BLK_RBC_V10",	"VDD_RBC_V",	"1", "0", "0", "1",},
	},
};

void pvt_cli_show_voltage(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t current_value;
	char **info;

#if defined(ZEBU)
	for (uint32_t instance_id = 0; instance_id < 1; ++instance_id) {
#else
	for (uint32_t instance_id = 0; instance_id < PVT_N_INSTANCE; ++instance_id) {
#endif
		printf("\n|          %18s |   Chiplet-0  |   Chiplet-1  |   Chiplet-2  |   Chiplet-3  |\n", inst_name[instance_id]);
		printf("------------------------------------------------------------------------------------------\n");

		for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
					(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
					(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
			PVT_ENABLE_VOLT_CONTROLLER(pvt_regs);
		}

		for (uint32_t sensor_id = 0; sensor_id < PVT_GET_VOLT_N_SENSOR(instance_id); ++sensor_id) {
			info = pvt_voltage_sensor_info[instance_id][sensor_id];
			if (info[0] != NULL) {
				printf("| [%11s] | %11s", info[0], info[1]);
				for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
					if (info[chiplet_id + 2][0] == '0') {
						printf(" |           ");
					} else {
#if defined(__TARGET_CP)
						pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
								(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
						pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
								(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
						current_value = PVT_GET_CURRENT_VOLT_VALUE(pvt_regs, sensor_id);
						printf(" | %4u -> %4u",
							   pvt_regs->voltage_regs[sensor_id].current_vol.currvoltage,
							   current_value);
					}
				}
				printf(" |\n");
			}
		}
	}
}

char *pvt_temperature_sensor_info[5][16] = {
	{
		"BLK_ROT",		"BLK_CP0",		"BLK_CP1",		"BLK_RBC_V00",
		"BLK_DRAM",		"BLK_PCIE",		"BLK_RBC_V01",
	},
	{
		"PVT0_DCL0",
		"SHM4_1",		"SHM4_0",		"SHM4_3",		"SHM4_2",
		"DNC1s_NCORE1",	"DNC1s_NCORE0",	"DNC0s_NCORE1",	"DNC0s_NCORE0",
		"DNC3s_NCORE1",	"DNC3s_NCORE0",	"DNC2s_NCORE1",	"DNC2s_NCORE0",
		"BLK_PERI0",	"BLK_RBC_H00",	"BLK_RBC_H01",
	},
	{
		"PVT1_DCL0",
		"DNC1n_NCORE1",	"DNC1n_NCORE0",	"DNC0n_NCORE1",	"DNC0n_NCORE0",
		"DNC3n_NCORE1",	"DNC3n_NCORE0",	"DNC2n_NCORE1",	"DNC2n_NCORE0",
	},
	{
		"PVT0_DCL1",
		"SHM4_1",		"SHM4_0",		"SHM4_3",		"SHM4_2",
		"DNC1s_NCORE1",	"DNC1s_NCORE0",	"DNC0s_NCORE1",	"DNC0s_NCORE0",
		"DNC3s_NCORE1",	"DNC3s_NCORE0",	"DNC2s_NCORE1",	"DNC2s_NCORE0",
		"BLK_PERI1",
	},
	{
		"PVT1_DCL1",
		"DNC1n_NCORE1",	"DNC1n_NCORE0",	"DNC0n_NCORE1",	"DNC0n_NCORE0",
		"DNC3n_NCORE1",	"DNC3n_NCORE0",	"DNC2n_NCORE1",	"DNC2n_NCORE0",
		"BLK_RBC_V10",	"BLK_RBC_V11",
	},
};

uint32_t pvt_cli_init;
int32_t pvt_cli_t25[4 * PVT_N_INSTANCE * PVT_TEMPERATURE_N_SENSOR];
int32_t pvt_cli_t85[4 * PVT_N_INSTANCE * PVT_TEMPERATURE_N_SENSOR];

void pvt_cli_save_otp(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t index;

	for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(ZEBU)
		for (uint32_t instance_id = 0; instance_id < 1; ++instance_id) {
#else
		for (uint32_t instance_id = 0; instance_id < PVT_N_INSTANCE; ++instance_id) {
#endif
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
			index = (chiplet_id * PVT_N_INSTANCE) + instance_id;
			for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(instance_id); ++sensor_id) {
				pvt_cli_t25[(index * PVT_TEMPERATURE_N_SENSOR) + sensor_id] = PVT_GET_TEMP_TRIMINFO_25(pvt_regs,
																									   sensor_id);
				pvt_cli_t85[(index * PVT_TEMPERATURE_N_SENSOR) + sensor_id] = PVT_GET_TEMP_TRIMINFO_85(pvt_regs,
																									   sensor_id);
			}
		}
	}
	pvt_cli_init = 1;
}

uint32_t pvt_cli_get_current_temperature(uint32_t chiplet_id, uint32_t instance_id, uint32_t sensor_id)
{
#if defined(__TARGET_CP)
	struct pvt_regs *pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
								(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
	struct pvt_regs *pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
								(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
	uint32_t calib_data = pvt_regs->temperature_regs[sensor_id].current_temp.currenttemp;
	uint32_t index = (((chiplet_id * PVT_N_INSTANCE) + instance_id) * PVT_TEMPERATURE_N_SENSOR) + sensor_id;

	return (((calib_data - pvt_cli_t25[index]) * (85 - 25)) / (pvt_cli_t85[index] - pvt_cli_t25[index])) + 25;
}

void pvt_cli_show_temperature(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t current_value;
	char **info;

	if (pvt_cli_init == 0) {
		pvt_cli_save_otp();
	}

#if defined(ZEBU)
	for (uint32_t instance_id = 0; instance_id < 1; ++instance_id) {
#else
	for (uint32_t instance_id = 0; instance_id < PVT_N_INSTANCE; ++instance_id) {
#endif
		printf("\n| %-13s | Chiplet-0 | Chiplet-1 | Chiplet-2 | Chiplet-3 |\n", inst_name[instance_id]);
		printf("-----------------------------------------------------------------\n");

		for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
						(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
			PVT_ENABLE_TEMP_CONTROLLER(pvt_regs);
		}

		for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(instance_id); ++sensor_id) {
			info = pvt_temperature_sensor_info[instance_id];
			printf("| %13s", info[sensor_id]);

			for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
#if defined(__TARGET_CP)
				pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
						   (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
				pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
						   (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

				current_value = pvt_cli_get_current_temperature(chiplet_id, instance_id, sensor_id);
				printf(" |   %4u   ", current_value);
			}
			printf(" |\n");
		}
	}
}

void pvt_cli_show_interrupt(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t int_en;

	printf(" - 'Enabled' means not occurred\n\n");
	for (uint32_t chiplet_id = 0; chiplet_id <= ID_MASK; ++chiplet_id) {
		printf("Chiplet-%u\n", chiplet_id);

#if defined(ZEBU)
		for (uint32_t instance_id = 0; instance_id < 1; ++instance_id) {
#else
		for (uint32_t instance_id = 0; instance_id < PVT_N_INSTANCE; ++instance_id) {
#endif
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
					   (chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
					   (chiplet_id * CHIPLET_BAT_OFFSET));
#endif

			printf("[ ID  ]| DFS | TRIP | FALL isEnabled | RISE isEnabled |\n");
			for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(instance_id); ++sensor_id) {
				int_en = pvt_regs->temperature_regs[sensor_id].inten.val;
				printf("[%2u-%2u]|  %c  |   %c  |    %c%c%c%c%c%c%c%c    |     %c%c%c%c%c%c%c    |\n",
					   instance_id, sensor_id,
					   (int_en &    0x100) ? '1' : '0',	/* DFS */
					   (int_en &     0x80) ? '1' : '0',	/* TRIP */
					   (int_en & 0x800000) ? '1' : '0',	/* FALL thresholds */
					   (int_en & 0x400000) ? '1' : '0',
					   (int_en & 0x200000) ? '1' : '0',
					   (int_en & 0x100000) ? '1' : '0',
					   (int_en &  0x80000) ? '1' : '0',
					   (int_en &  0x40000) ? '1' : '0',
					   (int_en &  0x20000) ? '1' : '0',
					   (int_en &  0x10000) ? '1' : '0',
					   (int_en &     0x40) ? '1' : '0',	/* RISE thresholds */
					   (int_en &     0x20) ? '1' : '0',
					   (int_en &     0x10) ? '1' : '0',
					   (int_en &      0x8) ? '1' : '0',
					   (int_en &      0x4) ? '1' : '0',
					   (int_en &      0x2) ? '1' : '0',
					   (int_en &      0x1) ? '1' : '0'
				);
			}
		}
	}
}

void pvt_cli_show_dram(void)
{
	struct pvt_regs *pvt_regs;
	uint32_t current_value;
	char **info;
	uint32_t instance_id = 0;
	uint32_t sensor_id = 6;

	if (CHIPLET_ID != 0) {
		return;
	}

	info = pvt_voltage_sensor_info[instance_id][sensor_id];
	if (info[0]) {
		printf("%s |", info[1]);
		for (uint32_t chiplet_id = 0; chiplet_id < CHIPLET_COUNT; ++chiplet_id) {
#if defined(__TARGET_CP)
			pvt_regs = (struct pvt_regs *)(pvt_base_address[instance_id] +
					(chiplet_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#else
			pvt_regs = (struct pvt_regs *)(uintptr_t)(pvt_base_address[instance_id] +
					(chiplet_id * CHIPLET_BAT_OFFSET));
#endif
			PVT_ENABLE_VOLT_CONTROLLER(pvt_regs);
			mdelay(10);
			current_value = PVT_GET_CURRENT_VOLT_VALUE(pvt_regs, sensor_id);
			printf("\nChiplet ID: %d, %4umV", chiplet_id, current_value);
		}
		printf("\n");
	}
}
