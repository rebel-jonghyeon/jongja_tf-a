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

#include "system_api.h"
#include <FreeRTOS.h>

#define TICKS_TO_COUNT(ticks)	((ticks) * (config ## CPU_CLOCK_HZ) / (config ## TICK_RATE_HZ))
#define GHz						(1000000000)
#define MHz						(1000000)
#define KHz						(1000)
#define NS_TO_COUNT(ns)			((ns) * (config ## CPU_CLOCK_HZ) / GHz)
#define US_TO_COUNT(us)			((us) * (config ## CPU_CLOCK_HZ) / MHz)
#define MS_TO_COUNT(ms)			((ms) * (config ## CPU_CLOCK_HZ) / KHz)
#define SEC_TO_COUNT(sec)		((sec) * (config ## CPU_CLOCK_HZ))
/* 1-tick = 1-ms * ms-to-count / tick-to-count */
/* #define pdMS_TO_TICKS(ms)	((ms) * (config ## TICK_RATE_HZ) / 1000) */

/* TODO: Compare delay time from clock waveform */

void ndelay(uint64_t ns)
{
	uint64_t total_count = NS_TO_COUNT(ns);

	delay_count(total_count);
}

void udelay(uint64_t us)
{
	uint64_t total_count = US_TO_COUNT(us);

	delay_count(total_count);
}

void mdelay(uint64_t ms)
{
	uint64_t total_count = MS_TO_COUNT(ms);

	delay_count(total_count);
}

void delay(uint64_t sec)
{
	uint64_t total_count = SEC_TO_COUNT(sec);

	delay_count(total_count);
}
