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

#include <stdint.h>

#if (__RUN_RTOS == 1)
	#include <rebel_h_platform.h>
	#include <cpu.h>
#else
	#include <platform_def.h>
	#define dmb()	__asm__ volatile ("dmb sy" ::: "memory")
#endif

/* Bakery Lock */
#define BAKERY_ENTERING_ADDR		(CPMU_PRIVATE + 0x810)
#define BAKERY_TICKET_ADDR			(CPMU_PRIVATE + 0x850)
#define BAKERY_ENTERING				((volatile uint32_t *)BAKERY_ENTERING_ADDR)
#define BAKERY_TICKET				((volatile uint32_t *)BAKERY_TICKET_ADDR)

/* A smaller number means higher priority */
#define BAKERY_ID_ROT				(0)
#define BAKERY_ID_CP0				(1)
#define BAKERY_ID_CP1				(2)
#define BAKERY_ID_CM7				(3)
#define BAKERY_ID_MAX				(4)

void rebel_bakery_lock_acquire(uint32_t cpu_id);
void rebel_bakery_lock_release(uint32_t cpu_id);
void rebel_bakery_lock_init(void);
