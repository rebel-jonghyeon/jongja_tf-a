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

#pragma once

#include <stdint.h>

#if defined(__RUN_RTOS)
#include <FreeRTOS.h>
#endif

#if defined(__TARGET_PCIE)
#include <ARMCM7_SP.h>
/* NOTE
 * The NVIC does not determine the IRQ type through software.
 * Following defines are left for users to refer and
 * use connect_interrupt_with_handler() function consistently with the CA73.
 */
#define IRQ_TYPE_LEVEL	(0x0U)
#define IRQ_TYPE_EDGE	(0x0U)
#endif

#ifndef ENABLE_DEVICE_INTERRUPT_DRIVEN
#if defined(__RUN_RTOS)
#define ENABLE_DEVICE_INTERRUPT_DRIVEN	(1)
#else
#define ENABLE_DEVICE_INTERRUPT_DRIVEN	(0)
#endif /* __RUN_RTOS */
#endif /* ENABLE_DEVICE_INTERRUPT_DRIVEN */

void set_dev_interrupt_priority(uint32_t irq_num, uint32_t irq_prio);
void enable_dev_interrupt(uint32_t irq_num);

void enable_all_interrupts(void);
void disable_all_interrupts(void);

void connect_interrupt_with_handler(uint32_t irq_num, uint32_t irq_prio,
		uint32_t irq_type, void *handler, void *cb_ref);

#if defined(__TARGET_CP)
void connect_interrupt_with_core_handler(uint32_t irq_num, uint32_t irq_prio,
										 uint32_t irq_type, uint32_t core_id, void *handler, void *cb_ref);

#endif
