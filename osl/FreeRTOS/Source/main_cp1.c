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

#include <rebel_h_platform.h>
#include "mailbox.h"

#include <rebel_h_ca73_freertos_driver.h>

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

	BOOT_LOG(CP1, CP1_FREERTOS, BOOT_DONE(CP1));

	vTaskStartScheduler();

	for (;;)
		;

	return 0;
}
