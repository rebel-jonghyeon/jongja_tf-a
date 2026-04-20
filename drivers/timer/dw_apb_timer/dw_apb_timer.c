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

#include "dw_apb_timer.h"
#include <interrupt.h>
#include <driver.h>
#include <rebel_h_platform.h>

void dw_apb_timer_default_callback(const struct dw_apb_timer_config *timer_config);

struct dw_apb_timer_config dw_apb_timer_peri0[NUM_TIMERS] = {
	{
		.timer_id			= 0,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI0,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 1,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI0,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 2,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI0,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 3,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI0,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	}
};
struct dw_apb_timer_config dw_apb_timer_peri1[NUM_TIMERS] = {
	{
		.timer_id			= 0,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI1,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 1,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI1,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 2,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI1,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	},
	{
		.timer_id			= 3,
		.load_count			= TIMER_MAX_LOAD_COUNT,
		.reg_base			= PWM_PERI1,

		.lock				= NULL,
		.freq				= TIMER_FREQUENCY,

		.default_callback	= dw_apb_timer_default_callback,
		.alarm_callback		= NULL,
		.alarm_data			= NULL,
	}
};

void dw_apb_timer_default_callback(const struct dw_apb_timer_config *timer_config)
{
}

void __attribute__((__used__)) dw_apb_timer_irq_handler(void *cb_ref)
{
	struct dw_apb_timer_config *timer_config = (struct dw_apb_timer_config *)(cb_ref);

	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	SemaphoreHandle_t lock = timer_config->lock;

	void (*alarm_callback)(const struct dw_apb_timer_config *) = timer_config->alarm_callback;
	void (*default_callback)(const struct dw_apb_timer_config *) = timer_config->default_callback;

	/* read EOI register to clear interrupt flag */
	timers_reg->timer_n_reg[timer_id].timer_n_eoi;

	/* TODO: Add failure of take oepration or do not add */
	xSemaphoreTakeFromISR(lock, pdFALSE);

	if (alarm_callback) {
		timers_reg->timer_n_reg[timer_id].timer_n_control_reg = TIMER_INTERRUPT_MASKED;

		timer_config->alarm_callback = NULL;
		alarm_callback(timer_config);
	} else if (default_callback) {
		default_callback(timer_config);
	}

	xSemaphoreGiveFromISR(lock, pdFALSE);
}

int __attribute__((__used__)) dw_apb_timer_start(const struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;

	/* disable timer before starting in free-running mode */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_ENABLED;

	/* starting timer in free running mode */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_USER_DEFINED;
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_INTERRUPT_MASKED;
	timers_reg->timer_n_prot_level[timer_id] = TIMER_BASE_PROT_LEVEL;
	timers_reg->timer_n_reg[timer_id].timer_n_load_count = TIMER_SET_LOAD_COUNT(TIMER_FREE_RUNNING_MODE_LOAD_VALUE);

	/* enable timer */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_ENABLED;
	return 0;
}

int dw_apb_timer_disable(const struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;

	/* disable timer */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_ENABLED;
	return 0;
}

uint32_t __attribute__((__used__)) dw_apb_timer_get_load_count(const struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	uint32_t load_val = 0;

	/* get the current value from load count register */
	load_val = timers_reg->timer_n_reg[timer_id].timer_n_load_count;

	return load_val;
}

uint32_t __attribute__((__used__)) dw_apb_timer_get_value(const struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	uint32_t current_value = 0;

	/* current value of the current value register */
	current_value = timers_reg->timer_n_reg[timer_id].timer_n_current_value;

	return current_value;
}

int __attribute__((__used__)) dw_apb_timer_set_load_count(struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	uint32_t load_count = timer_config->load_count;
	SemaphoreHandle_t lock = timer_config->lock;

	xSemaphoreTake(lock, portMAX_DELAY);

	/* load value cannot be updated if the alarm is active */
	if (timer_config->alarm_callback) {
		xSemaphoreGive(lock);
		/* If user callback (alarm callback) is active, load value cannot be updated! */
		return -1;
	}

	/* unmask interrupt */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_INTERRUPT_MASKED;

	/* load value can be loaded only when timer is stopped and re-enabled */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_ENABLED;

	/* configure timer in user-defined mode */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_USER_DEFINED;

	/* set new load value */
	timers_reg->timer_n_prot_level[timer_id] = TIMER_BASE_PROT_LEVEL;
	timers_reg->timer_n_reg[timer_id].timer_n_load_count = TIMER_SET_LOAD_COUNT(load_count);

	/* enable timer */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_ENABLED;

	xSemaphoreGive(lock);

	return 0;
}

int __attribute__((__used__)) dw_apb_timer_set_alarm_callback(struct dw_apb_timer_config *timer_config, const uint32_t load_count,
										const void (*alarm_callback)(const struct dw_apb_timer_config *), void *alarm_data)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	SemaphoreHandle_t lock = timer_config->lock;

	if (!alarm_callback) {
		/* 'alarm_callback' function cannot be NULL */
		return -1;
	}

	xSemaphoreTake(lock, portMAX_DELAY);

	/* check if user callback is already active */
	if (timer_config->alarm_callback != NULL) {
		/* 'alarm_callback' is already active */
		xSemaphoreGive(lock);
		return -1;
	}

	timer_config->alarm_callback = alarm_callback;
	timer_config->alarm_data = alarm_data;

	/* disable timer to change control register */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_ENABLED;

	/* start timer in user-defined mode */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_USER_DEFINED;

	/* unmask interrupt */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_INTERRUPT_MASKED;

	/* update load value */
	timers_reg->timer_n_prot_level[timer_id] = TIMER_BASE_PROT_LEVEL;
	timers_reg->timer_n_reg[timer_id].timer_n_load_count = TIMER_SET_LOAD_COUNT(load_count);

	/* enable timer */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg |= TIMER_ENABLED;

	xSemaphoreGive(lock);

	return 0;
}

int __attribute__((__used__)) dw_apb_timer_cancel_alarm_callback(struct dw_apb_timer_config *timer_config)
{
	volatile struct dw_apb_timers_reg *timers_reg = (struct dw_apb_timers_reg *)(timer_config->reg_base);
	uint32_t timer_id = timer_config->timer_id;
	SemaphoreHandle_t lock = timer_config->lock;

	xSemaphoreTake(lock, portMAX_DELAY);

	/* disable timer */
	timers_reg->timer_n_reg[timer_id].timer_n_control_reg &= ~TIMER_ENABLED;

	/* remove alarm callback & user data */
	timer_config->alarm_callback = NULL;
	timer_config->alarm_data = NULL;

	xSemaphoreGive(lock);

	return 0;
}

uint32_t dw_apb_timer_get_freq(const struct dw_apb_timer_config *timer_config)
{
	return timer_config->freq;
}

static int dw_apb_timer_n_init(struct dw_apb_timer_config *timer_config)
{
	/* crearte semaphore to protect user data */
	timer_config->lock = xSemaphoreCreateBinary();
	if (!timer_config->lock) {
		/* Lock is not created */
		return -1;
	}
	xSemaphoreGive(timer_config->lock);

	return 0;
}

int dw_apb_timer_init(void)
{
	for (uint32_t timer_id = 0; timer_id < NUM_TIMERS; ++timer_id) {
		dw_apb_timer_n_init(&dw_apb_timer_peri0[timer_id]);
		dw_apb_timer_n_init(&dw_apb_timer_peri1[timer_id]);
	}

#if defined(__TARGET_CP)
	connect_interrupt_with_handler(204, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri0[0]));
	connect_interrupt_with_handler(205, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri0[1]));
	connect_interrupt_with_handler(206, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri0[2]));
	connect_interrupt_with_handler(207, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri0[3]));
	connect_interrupt_with_handler(254, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri1[0]));
	connect_interrupt_with_handler(255, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri1[1]));
	connect_interrupt_with_handler(256, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri1[2]));
	connect_interrupt_with_handler(257, 2, IRQ_TYPE_LEVEL, dw_apb_timer_irq_handler, (void *)(&dw_apb_timer_peri1[3]));
#endif

	return 0;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(5, dw_apb_timer_init);
#endif
