/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include "test_common.h"
#include "interrupt_test_helper.h"
#include "interrupt.h"
#include "../../drivers/pcie/pcie_rebelh.h"

static const char help_test_irq[] =
	"[test_irq <irq_num>]\r\n";

void call_all_pcie_isr(void)
{
	int32_t i;

	for (i = PCIE_PAD_PERST_N_FALL_IRQ_NUM; i <= PCIE_VDI_STATUS; i++) {
		interrupt_set_pending(i);
	}
}

void call_specific_isr(const int32_t irq_num)
{
	interrupt_set_pending(irq_num);
}

uint8_t test_m7_pcie_isr(int argc, char *argv[])
{
	if (argc) {
		int32_t i, irq_num;

		for (i = 0; i < argc; i++) {
			irq_num = strtol(argv[i], NULL, 0);
			call_specific_isr(irq_num);
		}
	} else {
		call_all_pcie_isr();
	}

	return true;
}

CLI_REGISTER(test_irq, NULL, test_m7_pcie_isr, help_test_irq);
