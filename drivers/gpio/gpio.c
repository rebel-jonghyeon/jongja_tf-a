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

#include "gpio.h"
#include <assert.h>
#include <string.h>

/* GPIO Data APIs */
void gpio_set_con(size_t gpio_addr, uint32_t gpio_pin, uint32_t mode)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	 *val = ((*val) & ~(GPIO_HALF_BYTE << offset)) | (mode << offset);
}

uint32_t gpio_get_con(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	return ((*val) >> offset) & GPIO_HALF_BYTE;
}

void gpio_set_dat(size_t gpio_addr, uint32_t gpio_pin, uint32_t data)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	 *val = ((*val) & ~(GPIO_ONE_BIT << offset)) | (data << offset);
}

uint32_t gpio_get_dat(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	return ((*val) >> offset) & GPIO_ONE_BIT;
}

void gpio_set_pud(size_t gpio_addr, uint32_t gpio_pin, uint32_t pad_state)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	 *val = ((*val) & ~(GPIO_HALF_BYTE << offset)) | (pad_state << offset);
}

uint32_t gpio_get_pud(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	return ((*val) >> offset) & GPIO_HALF_BYTE;
}

void gpio_set_drv(size_t gpio_addr, uint32_t gpio_pin, uint32_t drive_strength)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	 *val = ((*val) & ~(GPIO_HALF_BYTE << offset)) | (drive_strength << offset);
}

uint32_t gpio_get_drv(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	return ((*val) >> offset) & GPIO_HALF_BYTE;
}

void gpio_set_toggle(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	 *val = ~(*val);
}

/* GPIO EINT APIs */
void gpio_set_eint_grppri(size_t gpio_addr, uint32_t group_priority)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	*val = (group_priority & GPIO_ONE_BIT);
}

uint32_t gpio_get_eint_grppri(size_t gpio_addr)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	return (*val) & GPIO_ONE_BIT;
}

void gpio_set_eint_pri(size_t gpio_addr, uint32_t gpio_group)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = gpio_group;

	*val = ((*val) & ~(GPIO_ONE_BIT << offset)) | (GPIO_ONE_BIT << offset);
}

uint32_t gpio_get_eint_pri(size_t gpio_addr, uint32_t gpio_group)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = gpio_group;

	return ((*val) >> offset) & GPIO_ONE_BIT;
}

void gpio_set_eint_svc(size_t gpio_addr, uint32_t svc_group, uint32_t irq_num)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	*val = ((svc_group & GPIO_FIVE_BIT) << 3U) | (irq_num & GPIO_THREE_BIT);
}

uint32_t gpio_get_eint_svc(size_t gpio_addr)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	return (*val) & GPIO_ONE_BYTE;
}

void gpio_set_eint_svcpend(size_t gpio_addr, uint32_t irq_group_num)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	*val = (irq_group_num & GPIO_ONE_BYTE);
}

uint32_t gpio_get_eint_svcpend(size_t gpio_addr)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	return (*val) & GPIO_ONE_BYTE;
}

void gpio_set_eint_grpfixpri(size_t gpio_addr, uint32_t highest_irq_group_num)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	*val = (highest_irq_group_num & GPIO_FIVE_BIT);
}

uint32_t gpio_get_eint_grpfixpri(size_t gpio_addr)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	return (*val) & GPIO_FIVE_BIT;
}

/* GPIO NWEINT APIs */
void gpio_set_nweint_con(size_t gpio_addr, uint32_t gpio_pin, uint32_t irq_trigger)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	*val = (*val & ~(GPIO_THREE_BIT << offset)) | (irq_trigger << offset);
}

uint32_t gpio_get_nweint_con(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = ((gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_PIN_OFFSET);

	return (*val >> offset) & GPIO_THREE_BIT;
}

void gpio_set_nweint_mask(size_t gpio_addr, uint32_t gpio_pin, uint32_t mask)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	*val = (((*val) & ~(GPIO_ONE_BIT << offset)) | (mask << offset));
}

uint32_t gpio_get_nweint_mask(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	return ((*val) >> offset) & GPIO_ONE_BIT;
}

void gpio_set_nweint_pend(size_t gpio_addr, uint32_t gpio_pin, uint32_t release_pend)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	*val = (((*val) & ~(GPIO_ONE_BIT << offset)) | (release_pend << offset));
}

uint32_t gpio_get_nweint_pend(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM);

	return ((*val) >> offset) & GPIO_ONE_BIT;
}

void gpio_set_nweint_fixpri(size_t gpio_addr, uint32_t priority)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	*val = (priority % GPIO_NWEINT_FIXPRI_MAX);
}

uint32_t gpio_get_nweint_fixpri(size_t gpio_addr)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);

	return *val;
}

/*	No NWEINT_FLTCON for GPA  */
uint32_t GPB_NWEINT_FLTCON[]	= {
	0x0800U, 0x0804U,	/* GPB0 */
	0x0808U, 0x080CU,	/* GPB1 */
	0x0810U, -1,		/* GPB2 */
	0x0814U, -1,		/* GPB3 */
	0x0818U, -1,		/* GPB4 */
	0x081CU, -1,		/* GPB5 */
};

uint32_t GPC_NWEINT_FLTCON[] = {
	0x0800U, 0x0804U,	/* GPC0 */
	0x0808U, -1,		/* GPC1 */
};

uint32_t GPD_NWEINT_FLTCON[] = {
	0x0800U, 0x0804U,	/* GPD0 */
	0x0808U, 0x080CU,	/* GPD1 */
	0x0810U, 0x0814U,	/* GPD2 */
	0x0818U, 0x081CU,	/* GPD3 */
	0x0820U, 0x0824U,	/* GPD4 */
	0x0828U, 0x082CU,	/* GPD5 */
	0x0830U, -1,		/* GPD6 */
};

uint32_t GPE_NWEINT_FLTCON[]	= {
	0x0800U, 0x0804U,	/* GPE0 */
	0x0808U, 0x080CU,	/* GPE1 */
	0x0810U, -1,		/* GPE2 */
	0x0814U, -1,		/* GPE3 */
	0x0818U, -1,		/* GPE4 */
	0x081CU, -1,		/* GPE5 */
};

void gpio_set_nweint_fltcon(size_t gpio_addr, uint32_t *fltcon_ptr, uint32_t fltcon_num,
							uint32_t enable, uint32_t width)
{
	uint32_t fltcon_offset = fltcon_ptr[fltcon_num];
	/* Invalid FLTCON address */
	if (fltcon_offset == -1)
		return;

	volatile uint32_t *val = (uint32_t *)(gpio_addr + fltcon_offset);
	uint32_t offset = ((fltcon_num % GPIO_NWEINT_FLTCON_MAX) * GPIO_NWEINT_FLTCON_SIZE);

	*val = ((*val) & ~(GPIO_ONE_BYTE << offset)) | ((((enable & GPIO_ONE_BIT) << 7) | (width & GPIO_SEVEN_BIT)) << offset);
}

uint32_t gpio_get_nweint_fltcon(size_t gpio_addr, uint32_t *fltcon_ptr, uint32_t fltcon_num)
{
	uint32_t fltcon_offset = fltcon_ptr[fltcon_num];
	/* Invalid FLTCON address */
	if (fltcon_offset == -1)
		return -1;

	volatile uint32_t *val = (uint32_t *)(gpio_addr + fltcon_offset);
	uint32_t offset = ((fltcon_num % GPIO_NWEINT_FLTCON_MAX) * GPIO_NWEINT_FLTCON_SIZE);

	return ((*val) >> offset) & GPIO_ONE_BYTE;
}

/* GPIO TZPC APIs */
void gpio_set_tzpc(size_t gpio_addr, uint32_t gpio_pin, uint32_t secure_mode)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_TWO_BIT;

	*val = ((*val) & ~(GPIO_TWO_BIT << offset)) | (secure_mode << offset);
}

uint32_t gpio_get_tzpc(size_t gpio_addr, uint32_t gpio_pin)
{
	volatile uint32_t *val = (uint32_t *)(gpio_addr);
	uint32_t offset = (gpio_pin % GPIO_PIN_MAX_NUM) * GPIO_TWO_BIT;

	return ((*val) >> offset) & GPIO_TWO_BIT;
}

#if defined(__RUN_RTOS)
void (*GPIO_GPB_USER_CALLBACK[GPIO_GPB_EINT_NUM * GPIO_PIN_MAX_NUM])(void) = { 0 };
void (*GPIO_GPC_USER_CALLBACK[GPIO_GPC_EINT_NUM * GPIO_PIN_MAX_NUM])(void) = { 0 };
void (*GPIO_GPD_USER_CALLBACK[GPIO_GPD_EINT_NUM * GPIO_PIN_MAX_NUM])(void) = { 0 };
void (*GPIO_GPE_USER_CALLBACK[GPIO_GPE_EINT_NUM * GPIO_PIN_MAX_NUM])(void) = { 0 };

static void gpio_gpb_isr(void *cb_ref)
{
	volatile uint32_t val;
	uint32_t index;

	for (uint32_t group = 0; group < GPIO_GPB_EINT_NUM; ++group) {
		for (uint32_t pin = 0; pin < GPIO_PIN_MAX_NUM; ++pin) {
			val = GPIO_GPB_GET_NWEINT(group, pin, PEND);

			/* Execute user callback function */
			if (val) {
				index = (group * GPIO_PIN_MAX_NUM) + pin;
				if (GPIO_GPB_USER_CALLBACK[index]) {
					GPIO_GPB_USER_CALLBACK[index]();
				}

				/* Clear pending register */
				GPIO_GPB_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);
				return;
			}
		}
	}
	/* Failed to find source of GPIO interrupt */
	assert(0);
}

static void gpio_gpc_isr(void *cb_ref)
{
	volatile uint32_t val;
	uint32_t index;

	for (uint32_t group = 0; group < GPIO_GPC_EINT_NUM; ++group) {
		for (uint32_t pin = 0; pin < GPIO_PIN_MAX_NUM; ++pin) {
			val = GPIO_GPC_GET_NWEINT(group, pin, PEND);

			/* Execute user callback function */
			if (val) {
				index = (group * GPIO_PIN_MAX_NUM) + pin;
				if (GPIO_GPC_USER_CALLBACK[index]) {
					GPIO_GPC_USER_CALLBACK[index]();
				}

				/* Clear pending register */
				GPIO_GPC_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);
				return;
			}
		}
	}
	/* Failed to find source of GPIO interrupt */
	assert(0);
}

static void gpio_gpd_isr(void *cb_ref)
{
	volatile uint32_t val;
	uint32_t index;

	for (uint32_t group = 0; group < GPIO_GPD_EINT_NUM; ++group) {
		for (uint32_t pin = 0; pin < GPIO_PIN_MAX_NUM; ++pin) {
			val = GPIO_GPD_GET_NWEINT(group, pin, PEND);

			/* Execute user callback function */
			if (val) {
				index = (group * GPIO_PIN_MAX_NUM) + pin;
				if (GPIO_GPD_USER_CALLBACK[index]) {
					GPIO_GPD_USER_CALLBACK[index]();
				}

				/* Clear pending register */
				GPIO_GPD_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);
				return;
			}
		}
	}
	/* Failed to find source of GPIO interrupt */
	assert(0);
}

static void gpio_gpe_isr(void *cb_ref)
{
	volatile uint32_t val;
	uint32_t index;

	for (uint32_t group = 0; group < GPIO_GPE_EINT_NUM; ++group) {
		for (uint32_t pin = 0; pin < GPIO_PIN_MAX_NUM; ++pin) {
			val = GPIO_GPE_GET_NWEINT(group, pin, PEND);

			/* Execute user callback function */
			if (val) {
				index = (group * GPIO_PIN_MAX_NUM) + pin;
				if (GPIO_GPE_USER_CALLBACK[index])
					GPIO_GPE_USER_CALLBACK[index]();

				/* Clear pending register */
				GPIO_GPE_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);
				return;
			}
		}
	}
	/* Failed to find source of GPIO interrupt */
	assert(0);
}

int gpio_init(void)
{
	/* Register GPIO user callbacks */
	/* Example */
	/* GPIO_GPB_REGISTER_USER_CALLBACK(5, 1, callback); */

	/* Enable all gpio isr */
	gpio_register_isr(246, 1, IRQ_TYPE_LEVEL, gpio_gpb_isr, GPIO_ISR_PERI0);	/* GPIO_PERI0	: GPB */
	gpio_register_isr(138, 1, IRQ_TYPE_LEVEL, gpio_gpc_isr, GPIO_ISR_ROT);		/* GPIO_ROT		: GPC */
	gpio_register_isr(982, 1, IRQ_TYPE_LEVEL, gpio_gpd_isr, GPIO_ISR_NBUS_L);	/* GPIO_NBUS_L	: GPD */
	gpio_register_isr(296, 1, IRQ_TYPE_LEVEL, gpio_gpe_isr, GPIO_ISR_PERI1);	/* GPIO_PERI1	: GPE */

	/* GPIO_SET_CON */
	/* GPIO_GPB_SET(5, 1, CON, GPIO_CON_INTERUPT); */

	/* GPIO_SET_NWEINT_CON */
	/* GPIO_GPB_SET_NWEINT(5, 1, CON, GPIO_EINT_CON_BOTH_EDGE); */

	/* GPIO_SET_NWEINT_PEND */
	/* GPIO_GPB_SET_NWEINT(5, 1, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR); */

	/* GPIO_SET_NWEINT_MASK */
	/* GPIO_GPB_SET_NWEINT(5, 1, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT); */

	return 0;
}

DRIVER_INIT_ENTRY_DEFINE(5, gpio_init);
#endif
