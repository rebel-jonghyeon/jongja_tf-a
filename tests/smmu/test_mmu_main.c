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

#include "test_mmu.h"
#include <mmu.h>
#include <stdlib.h>

#define CONTINUOUS		(1)
#define NOT_CONTINUOUS	(0)

uint8_t test_mmu_main(int argc, char *argv[])
{
	printf("\nStart mmu test\n");

	if (argc < 1) {
		return 0;
	} else if (argc == 1) {
		uint64_t va, pa;

		printf("VA to PA test\n");

		va = (uint64_t)strtol(argv[0], NULL, 0);
		pa = va_to_pa(NULL, va);
		printf("VA = 0x%lx, PA = 0x%lx\n", va, pa);
		return 1;
	} else {
		uint64_t va_start, va_end;

		printf("Continuous Test\n");

		va_start = (uint64_t)strtol(argv[0], NULL, 0);
		va_end = (uint64_t)strtol(argv[1], NULL, 0);
		printf("va_start = 0x0%lx, va_end = 0x%lx\n", va_start, va_end);
		if (is_pa_continuous(NULL, va_start, va_end) == CONTINUOUS) {
			printf("Continuous\n");
			return 1;
		} else {
			printf("Not continuous\n");
			return 0;
		}
	}
}

static const char help_mmu[] =
	"[test_mmu]\r\n"
	" - [test_mmu <va_to_pa>]\r\n"
	" - [test_mmu <va_start> <va_end>]\r\n"
	"\r\n";

CLI_REGISTER(test_mmu, NULL, test_mmu_main, help_mmu);
