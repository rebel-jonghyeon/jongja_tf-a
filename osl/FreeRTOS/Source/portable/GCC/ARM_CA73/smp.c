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

#include "FreeRTOS.h"
#include <stdint.h>
#include <stdbool.h>
#include "psci.h"
#include "gic.h"
#include "cpu.h"
#include "printf.h"
#include "task.h"
#include "smp.h"
#include "mmu.h"

extern void _start(void);

void ipi_handler(void *data)
{
	extern uint64_t ullPortYieldRequired[];
	uint32_t core_id;

	core_id = portGET_CORE_ID();

	ullPortYieldRequired[core_id] = true;
}

uint32_t volatile ulSecondaryHoldingPen[configNUMBER_OF_CORES] = {0, };

void secondary_prep_c(void)
{
	mmu_init();
	gic_init();

	printf("core %d is online\n", get_current_cpuid());
	ulSecondaryHoldingPen[get_current_cpuid()] = 1;

	xPortStartScheduler();
}

#if (configNUMBER_OF_CORES > 1)
void init_smp(void)
{
	for (int id = 1; id < configNUMBER_OF_CORES; id++) {
		psci_cpu_on(id, (uint64_t)_start + ((CHIPLET_ID * CHIPLET_OFFSET) - 0x10000000000ULL));

		printf("core %d is up\n", id);

		while (ulSecondaryHoldingPen[id] == 0)
			dsb();
	}
}
#endif
