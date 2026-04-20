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
#include <freedom_metal.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cpu.h"
#include "psci.h"
#include "smp.h"
#include "printf.h"

#include "console_uart.h"
#include "cli_task.h"
#include "terminal_task.h"
#include "task_adder.h"
#include <rebel_h_platform.h>
#include "mailbox.h"
#include "rbc_cmd.h"

#include "replay.h"

#include <rebel_h_ca73_freertos_driver.h>
#include "pvt_cli_show.h"

/* This enum value is used in succession to the enum defined in mmu.c. */
enum main_boot_sequence {
	HW_INIT = 3,
	RUNTIME_SERVICE,
};

void vAssertCalled(const char *pcFile, uint32_t ulLine)
{
	printf("%s : %d, core : %lu\n", pcFile, ulLine, portGET_CORE_ID());
	taskDISABLE_INTERRUPTS();
	for ( ;; )
		;
}

void prvSetupHardware(void)
{
    /* write h/w init code */
	init_drivers_by_calling_init_entry();
#if (configNUMBER_OF_CORES > 1)
	init_smp();
#endif
}

int main(void)
{
	prvSetupHardware();

	BOOT_LOG(CP0, CP0_FREERTOS, HW_INIT);

	TaskHandle_t handle[10];

	console_uart_init();

	printf("\nHello world FreeRTOS_CP\n");

#if 0
	xTaskCreate(terminal_task, "terminal_task", configMINIMAL_STACK_SIZE, NULL, 1, &handle[0]);
	xTaskCreate(cli_task, "cli_task", configMINIMAL_STACK_SIZE, NULL, 1, &handle[1]);
	xTaskCreate(task_adder_task, "task_adder", configMINIMAL_STACK_SIZE, NULL, 1, &handle[2]);
#else
	xTaskCreateAffinitySet(terminal_task, "terminal_task", configMINIMAL_STACK_SIZE, NULL,
						   1, 1, &handle[0]);
	xTaskCreateAffinitySet(cli_task, "cli_task", configMINIMAL_STACK_SIZE, NULL,
						   1, 1, &handle[1]);
	xTaskCreateAffinitySet(task_adder_task, "task_adder", configMINIMAL_STACK_SIZE, NULL,
						   1, 1, &handle[2]);
	xTaskCreateAffinitySet(replay_task, "replay", configMINIMAL_STACK_SIZE, NULL,
						   1, 1, &handle[3]);
#endif

	terminal_init(handle[0]);
	cli_task_init(handle[1]);
	task_adder_init(handle[2]);
	replay_task_init(handle[3]);
	BOOT_LOG(CP0, CP0_FREERTOS, RUNTIME_SERVICE);

	BOOT_LOG(CP0, CP0_FREERTOS, BOOT_DONE(CP0));

	if (!IS_PRIMARY_CHIPLET && (IS_OTP_SECURE_BOOT || IS_XIP_SECURE_BOOT)) {
		/*
		 * In the case of a secure boot and secondary chiplet, since there is no SBOOT_N,
		 * The RoT BOOT_DONE should be checked in FreeRTOS
		 */
		WAIT_BOOT_DONE(ROT);
	}
//	WAIT_BOOT_DONE(CP1);
#if CHIPLET_COUNT > 1
	_check_ucie_link_speed();
#endif /* CHIPLET_COUNT */

	uint32_t boot_state = *(uint32_t *)BOOT_LOG_ADDR;

	printf("\n----------------------------------------------------\n");
	printf("BOOT%s - 0x%x", CHECK_BOOT_DONE(boot_state), boot_state);
	printf("\n----------------------------------------------------\n");

#if CHIPLET_COUNT > 1
//	show_crc_err_count();
#endif /* CHIPLET_COUNT */
	printf("Start FreeRTOS scheduler\n");
	pvt_cli_show_dram();
	vTaskStartScheduler();

	for (;;)
		;

	return 0;
}
