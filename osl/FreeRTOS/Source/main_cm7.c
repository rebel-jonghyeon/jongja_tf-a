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

#include <stdbool.h>
#include <freedom_metal.h>
#include "printf.h"

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <rebel_h_cm7_freertos_driver.h>
#include <uart.h>
#include <semphr.h>

#include "console_uart.h"
#include "cli_task.h"
#include "terminal_task.h"
#include "rebel_h_platform.h"
#include "mailbox.h"

enum cm7_boot_sequence {
	NOT_STARTED,
	HW_INIT,
	NOTIFY_PCIE_COMPLETION,
	RUNTIME_SERVICE,
};

SemaphoreHandle_t print_semaphore;
#define PRINT(...)								\
	if (xSemaphoreTake(print_semaphore, portMAX_DELAY)) {	\
		printf(__VA_ARGS__);					\
		xSemaphoreGive(print_semaphore);		\
	}

uint32_t handle_cnt;
TaskHandle_t handles[100];

void prvSetupHardware(void)
{
	init_drivers_by_calling_init_entry();
}

int main(void)
{
	BOOT_LOG(CM7, TBOOT_P0, HW_INIT);
	init_drivers_by_calling_init_entry();

	/*
	 * NOTE: PCIe completion notification defined in the boot sequence can be added here.
	 * You can only record data using ipm_samsung_write(), or you can use ipm_samsung_send()
	 * together to generate an interrupt.
	 * If ipm_samsung_send() is used, the interrupt is processed immediately after the completion
	 * of the start scheduler of CP0 FreeRTOS.
	 */
	/*
	 * BOOT_LOG(CM7, TBOOT_P0, NOTIFY_PCIE_COMPLETION);
	 * if (CHIPLET_ID == CHIPLET_ID0) {
	 * ipm_samsung_write(IDX_MAILBOX_CP0_M4, CHIPLET_ID, "done", sizeof("done") - 1, CPU0);
	 * ipm_samsung_send(IDX_MAILBOX_CP0_M4, CHIPLET_ID, 0, CPU0);
	 * } else if (CHIPLET_ID == CHIPLET_ID3) {
	 * ipm_samsung_write(IDX_MAILBOX_CP0_M4_C3, CHIPLET_ID, "done", sizeof("done") - 1, CPU0);
	 * ipm_samsung_send(IDX_MAILBOX_CP0_M4_C3, CHIPLET_ID, 0, CPU0);
	 * }
	 */

	console_uart_init();

	print_semaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(print_semaphore);

	printf("Hello! from FreeRTOS\r\n");

	xTaskCreate(terminal_task,		"terminal_task",		configMINIMAL_STACK_SIZE, NULL, 1, &handles[handle_cnt++]);
	xTaskCreate(cli_task,			"cli_task",				configMINIMAL_STACK_SIZE, NULL, 1, &handles[handle_cnt++]);

	terminal_init(handles[0]);
	cli_task_init(handles[1]);

	printf("Start Scheduler!!\r\n");

	BOOT_LOG(CM7, TBOOT_P0, RUNTIME_SERVICE);
	vTaskStartScheduler();

	/* infinite loop */
	__asm__("b .");

	return 0;
}
