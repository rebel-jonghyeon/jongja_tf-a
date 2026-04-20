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

#include "stdint.h"
#include "mmu.h"
#include "rebel_h_platform.h"

extern const char bss_start[];
extern const char bss_end[];

extern int main(void);

static inline void bss_clear(void)
{
	volatile uint64_t *p = (uint64_t *)bss_start;
	volatile uint64_t *end = (uint64_t *)bss_end;

	while (p < end) {
		*p++ = 0U;
	}
}

void primary_prep_c(void)
{
#if !defined(ZEBU)
	bss_clear();
#endif
	mmu_init();

#ifndef ZEBU_POC
	uint64_t main_func = (uint64_t)main;
	if (main_func < FREERTOS_VA_OFFSET) {
		main_func += (FREERTOS_VA_OFFSET - CHIPLET_BASE_ADDRESS);
	}
	((int (*)(void))main_func)();
#else
	main();
#endif	/* ZEBU_POC */

	/* Never return here */
	__asm("b .");
}
