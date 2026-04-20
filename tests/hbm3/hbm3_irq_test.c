/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include <common.h>
#include <stdlib.h>
#include <string.h>
#include <cache.h>
#include "hbm3_irq.h"
#include "test_common.h"
#include "task.h"

#define MAX_CH_NUM 16

uint8_t hbm3_irq_main(int argc, char *argv[])
{
	uint32_t ch;

	for (ch = 0 ; ch < MAX_CH_NUM ; ch++) {
		hbm3_interrupt_enable(ch);

		printf("hbm3 interrupt gen test\n");

		for (int i = 0 ; i < MAX_HBM3IRQ_NUM ; i++) {
			hbm3_interrupt_gen(ch, BIT(i));
		}

		vTaskDelay(pdMS_TO_TICKS(1));

		printf("hbm3 interrupt mask test\n");

		for (int i = 0 ; i < MAX_HBM3IRQ_NUM ; i++) {
			hbm3_interrupt_mask(ch, BIT(i));

			hbm3_interrupt_gen(ch, BIT(i));

			hbm3_interrupt_mask(ch, 0);
		}

		hbm3_interrupt_gen(ch, 0);

		hbm3_interrupt_disable(ch);
	}

	return 1;
}

static const char help_hbm3_irq[] =
	"[hbm3_irq]\r\n"
	" - Run hbm3 interrupt test\r\n"
	"\r\n";

CLI_REGISTER(hbm3_irq, NULL, hbm3_irq_main, help_hbm3_irq);
