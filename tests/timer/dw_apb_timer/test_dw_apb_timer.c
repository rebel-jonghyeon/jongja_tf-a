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

#include "test_common.h"
#include "test_dw_apb_timer.h"

#include "printf.h"
#include "dw_apb_timer.h"

extern struct dw_apb_timer_config dw_apb_timer_peri0[NUM_TIMERS];
extern struct dw_apb_timer_config dw_apb_timer_peri1[NUM_TIMERS];

void dw_apb_timer_test_alarm_callback(const struct dw_apb_timer_config *timer_config)
{
	printf("Alarm callback!\n");
}

void test_dw_apb_timer(void)
{
	struct dw_apb_timer_config *configs[] = {dw_apb_timer_peri0, dw_apb_timer_peri1};
	struct dw_apb_timer_config *temp_config;

	for (uint32_t peri_num = 0; peri_num < 2; ++peri_num) {
		for (uint32_t i = 0; i < NUM_TIMERS; ++i) {
			printf("BLK_PERI%u timer_intr[%u]\n", peri_num, i);
			temp_config = &configs[peri_num][i];

			dw_apb_timer_set_load_count(temp_config);
		#if defined(__TARGET_CP)
			printf("Default 'load_count' = 0x%08x\n", dw_apb_timer_get_load_count(temp_config));
		#elif defined(__TARGET_PCIE)
			printf("Default 'load_count' = 0x%08lx\n", dw_apb_timer_get_load_count(temp_config));
		#endif

			dw_apb_timer_start(temp_config);
			for (uint32_t i = 0; i < 10; ++i)
			#if defined(__TARGET_CP)
				printf("current_value = 0x%08x\n", dw_apb_timer_get_value(temp_config));
			#elif defined(__TARGET_PCIE)
				printf("current_value = 0x%08lx\n", dw_apb_timer_get_value(temp_config));
			#endif
			dw_apb_timer_disable(temp_config);

			dw_apb_timer_set_alarm_callback(temp_config, 0xFFFFU, dw_apb_timer_test_alarm_callback, NULL);
		#if defined(__TARGET_CP)
			printf("Alarm 'load_count' = 0x%x\n", dw_apb_timer_get_load_count(temp_config));
		#elif defined(__TARGET_PCIE)
			printf("Alarm 'load_count' = 0x%lx\n", dw_apb_timer_get_load_count(temp_config));
		#endif
			for (uint32_t i = 0; i < 10; ++i)
			#if defined(__TARGET_CP)
				printf("current_value = 0x%08x\n", dw_apb_timer_get_value(temp_config));
			#elif defined(__TARGET_PCIE)
				printf("current_value = 0x%08lx\n", dw_apb_timer_get_value(temp_config));
			#endif
			dw_apb_timer_cancel_alarm_callback(temp_config);
		}
	}
}

uint8_t test_dw_apb_timer_cli(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart dw_apb_timer test\n");
	test_dw_apb_timer();

	return ret;
}

static const char help_dw_apb_timer[] =
	"[dw_apb_timer]\n"
	" * Test for dw_apb_timer driver\n"
	"\n";

CLI_REGISTER(dw_apb_timer, NULL, test_dw_apb_timer_cli, help_dw_apb_timer);
