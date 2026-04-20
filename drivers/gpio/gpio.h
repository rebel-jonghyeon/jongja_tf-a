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
#include <rebel_h_platform.h>
#include <driver.h>
#include <interrupt.h>
#else
#include <platform_def.h>
#endif /* __RUN_RTOS */

/* GPIO macros */
/* Block specific */
#define GPIO_GPA_NUM		(3)		/* GPA0-2			*/
#define GPIO_GPA_EINT_NUM	(0)		/* None				*/
#define GPIO_GPA_TZPC_NUM	(2)		/* TZPC_PCIE_0-1	*/
#define GPIO_GPB_NUM		(14)	/* GPB0-13			*/
#define GPIO_GPB_EINT_NUM	(14)	/* GPB0-5			*/
#define GPIO_GPB_TZPC_NUM	(7)		/* TZPC_PERI0_0-6	*/
#define GPIO_GPC_NUM		(2)		/* GPC0-1			*/
#define GPIO_GPC_EINT_NUM	(2)		/* GPC0-1			*/
#define GPIO_GPC_TZPC_NUM	(1)		/* TZPC_ROT_0		*/
#define GPIO_GPD_NUM		(7)		/* GPD0-6			*/
#define GPIO_GPD_EINT_NUM	(7)		/* GPD0-6			*/
#define GPIO_GPD_TZPC_NUM	(4)		/* TZPC_NBUS_L_0-3	*/
#define GPIO_GPE_NUM		(14)	/* GPE0-13			*/
#define GPIO_GPE_EINT_NUM	(14)	/* GPE0-5			*/
#define GPIO_GPE_TZPC_NUM	(7)		/* TZPC_PERI1_0-6	*/

/* Common to GPIOs */
#define GPIO_GROUP_OFFSET			(0x0020U)
#define GPIO_PIN_OFFSET				(0x0004U)
#define GPIO_CON					(0x0000U)
#define GPIO_DAT					(0x0004U)
#define GPIO_PUD					(0x0008U)
#define GPIO_DRV					(0x000CU)

#define GPIO_NWEINT_CON				(0x0700U)
#define GPIO_NWEINT_MASK			(0x0900U)
#define GPIO_NWEINT_PEND			(0x0A00U)
#define GPIO_EINT_GRPPRI			(0x0B00U)
#define GPIO_EINT_PRI				(0x0B04U)
#define GPIO_EINT_SVC				(0x0B08U)
#define GPIO_EINT_SVCPEND			(0x0B0CU)
#define GPIO_EINT_GRPFIXPRI			(0x0B10U)
#define GPIO_NWEINT_FIXPRI			(0x0B14U)
#define GPIO_TZPC					(0x2000U)
#define GPIO_NWEINT_GROUP_OFFSET	(0x0004U)
#define GPIO_TZPC_GROUP_OFFSET		(0x0004U)

#define GPIO_ONE_BIT				(1U)
#define GPIO_TWO_BIT				(0x10U)
#define GPIO_THREE_BIT				(0x7U)
#define GPIO_HALF_BYTE				(0xFU)
#define GPIO_FIVE_BIT				(0x1FU)
#define GPIO_SEVEN_BIT				(0x7FU)
#define GPIO_ONE_BYTE				(0xFFU)
#define GPIO_PIN_MAX_NUM			(8U)
#define GPIO_NWEINT_FIXPRI_MAX		(8U)
#define GPIO_NWEINT_FLTCON_SIZE		(8U)
#define GPIO_NWEINT_FLTCON_MAX		(2U)

/* GPIO Data APIs */
enum {							/* 4-bit each									*/
	GPIO_CON_INPUT,				/* 0x0 = GPIO input mode						*/
	GPIO_CON_OUTPUT,			/* 0x1 = GPIO output mode						*/
	GPIO_CON_FUNCTION,			/* 0x2 = Predefined function mode				*/
	GPIO_CON_RESERVED,			/* 0x3 ~ 0xE = Reserved							*/
	GPIO_CON_INTERUPT = 0xFU,	/* 0xF = External interrupt mode				*/
};

enum {					/* 4-bit each														*/
	GPIO_PUD_DISABLE,	/* 0x0 = Disable	(pad value = high Z, input value to chip = X)	*/
	GPIO_PUD_PULLDOWN,	/* 0x1 = Pull-down	(pad value = weak-0, input value to chip = 0)	*/
	GPIO_PUD_DISABLE1,	/* 0x2 = Disable													*/
	GPIO_PUD_PULLUP,	/* 0x3 = Pull-up	(pad value = weak-1, input value to chip = 1)	*/
	GPIO_PUD_RESERVED,	/* 0x4 ~ 0xF = Reserved												*/
};

enum {					/* 4-bit each					*/
	GPIO_DRV_1X,		/* 0x0 = 1x						*/
	GPIO_DRV_1_5X,		/* 0x1 = 1.5x					*/
	GPIO_DRV_2X,		/* 0x2 = 2x = Reset Value		*/
	GPIO_DRV_2_5X,		/* 0x3 = 2.5x					*/
	GPIO_DRV_3X,		/* 0x4 = 3x						*/
	GPIO_DRV_4X,		/* 0x5 = 4x						*/
	GPIO_DRV_RESERVED,	/* 0x6 ~ 0xF = Reserved			*/
};

#define GPIO_GPA_SET(group, pin, type, val)	\
	GPIO_SET_##type(GPIO_PCIE + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPA_GET(group, pin, type)		\
	GPIO_GET_##type(GPIO_PCIE + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin)
#define GPIO_GPB_SET(group, pin, type, val) \
	GPIO_SET_##type(GPIO_PERI0 + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPB_GET(group, pin, type)		\
	GPIO_GET_##type(GPIO_PERI0 + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin)
#define GPIO_GPC_SET(group, pin, type, val)	\
	GPIO_SET_##type(GPIO_ROT + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPC_GET(group, pin, type)		\
	GPIO_GET_##type(GPIO_ROT + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin)
#define GPIO_GPD_SET(group, pin, type, val)	\
	GPIO_SET_##type(GPIO_NBUS_L + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPD_GET(group, pin, type)		\
	GPIO_GET_##type(GPIO_NBUS_L + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin)
#define GPIO_GPE_SET(group, pin, type, val)	\
	GPIO_SET_##type(GPIO_PERI1  + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPE_GET(group, pin, type)		\
	GPIO_GET_##type(GPIO_PERI1  + GPIO_##type + (GPIO_GROUP_OFFSET * (group)), pin)

#define GPIO_SET_CON(addr, pin, mode)			gpio_set_con(addr, pin, mode)
#define GPIO_GET_CON(addr, pin)					gpio_get_con(addr, pin)
#define GPIO_SET_DAT(addr, pin, data)			gpio_set_dat(addr, pin, data)
#define GPIO_GET_DAT(addr, pin)					gpio_get_dat(addr, pin)
#define GPIO_SET_PUD(addr, pin, state)			gpio_set_pud(addr, pin, state)
#define GPIO_GET_PUD(addr, pin)					gpio_get_pud(addr, pin)
#define GPIO_SET_DRV(addr, pin, strength)		gpio_set_drv(addr, pin, strength)
#define GPIO_GET_DRV(addr, pin)					gpio_get_drv(addr, pin)

/**
 * @brief Sets the pin configuration for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO configuration register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] mode The desired configuration mode for the GPIO pin
 *
 * @return None
 */
void gpio_set_con(size_t gpio_addr, uint32_t gpio_pin, uint32_t mode);

/**
 * @brief Gets the current pin configuration for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO configuration register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pin configuration mode for the specified GPIO pin
 */
uint32_t gpio_get_con(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the pin data value for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO data register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] data The desired data value for the GPIO pin
 *
 * @return None
 */
void gpio_set_dat(size_t gpio_addr, uint32_t gpio_pin, uint32_t data);

/* TODO */
/**
 * @brief Gets the current pin data value for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO data register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pin data value for the specified GPIO pin
 */
uint32_t gpio_get_dat(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the pin pull-up/down state for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO pull-up/down register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] pad_state The desired pull-up/down state for the GPIO pin
 *
 * @return None
 */
void gpio_set_pud(size_t gpio_addr, uint32_t gpio_pin, uint32_t pad_state);

/**
 * @brief Gets the current pin pull-up/down state for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO pull-up/down register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pin pull-up/down state for a specified GPIO pin
 */
uint32_t gpio_get_pud(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the pin drive strength for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO drive strength register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] drive_strength The desired drive strength for the GPIO pin
 *
 * @return None
 */
void gpio_set_drv(size_t gpio_addr, uint32_t gpio_pin, uint32_t drive_strength);

/**
 * @brief Gets the current pin drive strength for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO drive strength register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pin drive strength for the specified GPIO pin
 */
uint32_t gpio_get_drv(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Toggles the pin value for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO register to toggle
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return None
 */
void gpio_set_toggle(size_t gpio_addr, uint32_t gpio_pin);

/* GPIO EINT APIs */
enum {							/* Only 1-bit				*/
	GPIO_GRPPRI_NOT_ROTATE,		/* 0x0 = Not rotate (Fixed)	*/
	GPIO_GRPPRI_ROTATE,			/* 0x1 = Rotate enable		*/
};

enum {							/* 1-bit each				*/
	GPIO_PRI_NOT_ROTATE,		/* 0x0 = Not rotate (Fixed)	*/
	GPIO_PRI_ROTATE,			/* 0x1 = Rotate enable		*/
};

enum {									/* 1-bit */
	GPIO_SVCPEND_INTERRUPT_NOT_OCCUR,	/* 0x0 = Interurpt does not occur	*/
	GPIO_SVCPEND_INTERRUPT_OCCUR,		/* 0x1 = Interrupt occurs			*/
};

/* type = {GRPPRI, PRI, SVC, SVCPEND, GRPFIXPRI} */
#define GPIO_GPB_SET_EINT(group, type, val0, val1)	\
	GPIO_SET_EINT_##type(GPIO_PERI0	 + GPIO_EINT_##type, group, val0, val1)
#define GPIO_GPB_GET_EINT(group, type)				\
	GPIO_GET_EINT_##type(GPIO_PERI0	 + GPIO_EINT_##type, group)
#define GPIO_GPC_SET_EINT(group, type, val0, val1)	\
	GPIO_SET_EINT_##type(GPIO_ROT	 + GPIO_EINT_##type, group, val0, val1)
#define GPIO_GPC_GET_EINT(group, type)				\
	GPIO_GET_EINT_##type(GPIO_ROT	 + GPIO_EINT_##type, group)
#define GPIO_GPD_SET_EINT(group, type, val0, val1)	\
	GPIO_SET_EINT_##type(GPIO_NBUS_L + GPIO_EINT_##type, group, val0, val1)
#define GPIO_GPD_GET_EINT(group, type)				\
	GPIO_GET_EINT_##type(GPIO_NBUS_L + GPIO_EINT_##type, group)
#define GPIO_GPE_SET_EINT(group, type, val0, val1)	\
	GPIO_SET_EINT_##type(GPIO_PERI1	 + GPIO_EINT_##type, group, val0, val1)
#define GPIO_GPE_GET_EINT(group, type)				\
	GPIO_GET_EINT_##type(GPIO_PERI1	 + GPIO_EINT_##type, group)

#define GPIO_SET_EINT_GRPPRI(addr, group, prio, val1)					\
	gpio_set_eint_grppri(addr, prio)
#define GPIO_GET_EINT_GRPPRI(addr, group)								\
	gpio_get_eint_grppri(addr)
#define GPIO_SET_EINT_PRI(addr, group, val0, val1)						\
	gpio_set_eint_pri(addr, group)
#define GPIO_GET_EINT_PRI(addr, group)									\
	gpio_get_eint_pri(addr, group)
#define GPIO_SET_EINT_SVC(addr, group, svc_group, irq)					\
	gpio_set_eint_svc(addr, svc_group, irq)
#define GPIO_GET_EINT_SVC(addr, group)									\
	gpio_get_eint_svc(addr)
#define GPIO_SET_EINT_SVCPEND(addr, group, irq_group, val1)				\
	gpio_set_eint_svcpend(addr, irq_group)
#define GPIO_GET_EINT_SVCPEND(addr, group)								\
	gpio_get_eint_svcpend(addr)
#define GPIO_SET_EINT_GRPFIXPRI(addr, group, highest_irq_group, val1)	\
	gpio_set_eint_grpfixpri(addr, highest_irq_group)
#define GPIO_GET_EINT_GRPFIXPRI(addr, group)							\
	gpio_get_eint_grpfixpri(addr)

/**
 * @brief Sets the EINT group priority for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the gpio EINT group priority register to set
 * @param[in] group_priority The desired group priority enablement for the GPIO block
 *
 * @return None
 */
void gpio_set_eint_grppri(size_t gpio_addr, uint32_t group_priority);

/**
 * @brief Gets the EINT group priority for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the gpio EINT group priority register to set
 *
 * @return The current group priority enablement for the specific GPIO block
 */
uint32_t gpio_get_eint_grppri(size_t gpio_addr);

/**
 * @brief Sets the EINT priority for a specific GPIO group
 *
 * @param[in] gpio_addr The address of the GPIO EINT priority register to set
 * @param[in] gpio_group The desired GPIO group number to enable EINT priority
 *
 * @return None
 */
void gpio_set_eint_pri(size_t gpio_addr, uint32_t gpio_group);

/**
 * @brief Gets the EINT priority for a specific GPIO group
 *
 * @param[in] gpio_addr The address of the GPIO EINT priority register to get
 * @param[in] gpio_group The desired GPIO group number to get EINT priority
 *
 * @return The current priority enablement for the specific GPIO block
 */
uint32_t gpio_get_eint_pri(size_t gpio_addr, uint32_t gpio_group);

/**
 * @brief Sets the EINT service group and IRQ number for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT SVC/IRQ register to set
 * @param[in] svc_group The desired service group to the GPIO block
 * @param[in] irq_num The desired IRQ number to the GPIO block
 *
 * @return None
 */
void gpio_set_eint_svc(size_t gpio_addr, uint32_t svc_group, uint32_t irq_num);

/**
 * @brief Gets the EINT service group and IRQ number for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT SVC/IRQ register to get
 *
 * @returns The current EINT service group and IRQ number for the specified GPIO pin
 */
uint32_t gpio_get_eint_svc(size_t gpio_addr);

/**
 * @brief Set the EINT SVC pend status for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT SVC pend reigster to set
 * @param[in] irq_group_num The desired IRQ group number to the GPIO block
 *
 * @returns None
 */
void gpio_set_eint_svcpend(size_t gpio_addr, uint32_t irq_group_num);

/**
 * @brief Gets the EINT SVC pend status for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT SVC pend reigster to get
 *
 * @returns The current EINT SVC pend status for the specified GPIO block
 */
uint32_t gpio_get_eint_svcpend(size_t gpio_addr);

/**
 * @brief Sets the EINT fixed group priority for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT fixed group priority to set
 * @param[in] highest_irq_group_num The desired highest IRQ group number to the GPIO block
 *
 * @returns None
 */
void gpio_set_eint_grpfixpri(size_t gpio_addr, uint32_t highest_irq_group_num);

/**
 * @brief Gets the EINT fixed group priority for a specific GPIO block
 *
 * @param[in] gpio_addr The address of the GPIO EINT fixed group priority to get
 *
 * @return The current EINT fixed group priority for the specified GPIO block
 */
uint32_t gpio_get_eint_grpfixpri(size_t gpio_addr);

/* GPIO NWEINT APIs */
enum {							/* 3-bit each, Reset Value = 0x */
	GPIO_EINT_CON_LOW_LEVEL,	/* 0x0 = Low level triggered	*/
	GPIO_EINT_CON_HIGH_LEVEL,	/* 0x1 = High level triggered	*/
	GPIO_EINT_CON_FALLING_EDGE,	/* 0x2 = Falling edge triggered	*/
	GPIO_EINT_CON_RISING_EDGE,	/* 0x3 = Rising edge triggered	*/
	GPIO_EINT_CON_BOTH_EDGE,	/* 0x4 = Both edge triggered	*/
	GPIO_EINT_CON_RESERVED,		/* 0x5 ~ 0x7 = Reserved			*/
};

enum {							/* 2-bit each, Reset Value = 0x */
	GPIO_EINT_FLTCON_DISABLE,	/* 0x0 = Filter disable	*/
	GPIO_EINT_FLTCON_ENABLE,	/* 0x1 = Filter enable	*/
};

enum {									/* 1-bit */
	GPIO_EINT_MASK_ENABLE_INTERRUPT,	/* 0x0 = Enable interrupt	*/
	GPIO_EINT_MASK_MASK_INTERRUPT,		/* 0x1 = Mask interrupt		*/
};

enum {									/* 1-bit */
	GPIO_EINT_PEND_INTERRUPT_NOT_OCCUR,	/* 0x0 = Interrupt does not occur	*/
	GPIO_EINT_PEND_INTERRUPT_OCCUR,		/* 0x1 = Interrupt occurs			*/
};

/* Reserved = 31:8		*/
/* Group number = 7:3	*/
/* Bit number = 2:0		*/

/* Reserved = 31:8					*/
/* Highest interrupt priority = 7:0	*/

/* EINT_GRPFIXPRI	*/
/* External Interrupt Group Fix Priority	*/

/* External Interrupt Fix Priority	*/
/* type = {CON, MASK, PEND, FIXPRI} */
#define GPIO_GPB_SET_NWEINT(group, pin, type, val)							\
	GPIO_SET_NWEINT_##type(GPIO_PERI0 + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPB_GET_NWEINT(group, pin, type)								\
	GPIO_GET_NWEINT_##type(GPIO_PERI0 + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin)
#define GPIO_GPC_SET_NWEINT(group, pin, type, val)							\
	GPIO_SET_NWEINT_##type(GPIO_ROT + GPIO_NWEINT_##type +					\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPC_GET_NWEINT(group, pin, type)								\
	GPIO_GET_NWEINT_##type(GPIO_ROT + GPIO_NWEINT_##type +					\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin)
#define GPIO_GPD_SET_NWEINT(group, pin, type, val)							\
	GPIO_SET_NWEINT_##type(GPIO_NBUS_L + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPD_GET_NWEINT(group, pin, type)								\
	GPIO_GET_NWEINT_##type(GPIO_NBUS_L + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin)
#define GPIO_GPE_SET_NWEINT(group, pin, type, val)							\
	GPIO_SET_NWEINT_##type(GPIO_PERI1 + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin, val)
#define GPIO_GPE_GET_NWEINT(group, pin, type)								\
	GPIO_GET_NWEINT_##type(GPIO_PERI1 + GPIO_NWEINT_##type +				\
						   (GPIO_NWEINT_GROUP_OFFSET * (group)), pin)

#define GPIO_SET_NWEINT_CON(addr, pin, trigger)			gpio_set_nweint_con(addr, pin, trigger)
#define GPIO_GET_NWEINT_CON(addr, pin)					gpio_get_nweint_con(addr, pin)
#define GPIO_SET_NWEINT_MASK(addr, pin, mask)			gpio_set_nweint_mask(addr, pin, mask)
#define GPIO_GET_NWEINT_MASK(addr, pin)					gpio_get_nweint_mask(addr, pin)
#define GPIO_SET_NWEINT_PEND(addr, pin, pend)			gpio_set_nweint_pend(addr, pin, pend)
#define GPIO_GET_NWEINT_PEND(addr, pin)					gpio_get_nweint_pend(addr, pin)
#define GPIO_SET_NWEINT_FIXPRI(addr, pin, prio)			gpio_set_nweint_fixpri(addr, prio)
#define GPIO_GET_NWEINT_FIXPRI(addr, pin)				gpio_get_nweint_fixpri(addr)

#define GPIO_GPB_SET_NWEINT_FLTCON(group, pin, fltcon_num, enable, width)	\
	gpio_set_nweint_fltcon(GPIO_ROT, GPB_NWEINT_FLTCON, fltcon_num, enable, width)
#define GPIO_GPB_GET_NWEINT_FLTCON(group, pin, fltcon_num)					\
	gpio_get_nweint_fltcon(GPIO_ROT, GPB_NWEINT_FLTCON, fltcon_num)
#define GPIO_GPC_SET_NWEINT_FLTCON(group, pin, fltcon_num, enable, width)	\
	gpio_set_nweint_fltcon(GPIO_ROT, GPC_NWEINT_FLTCON, fltcon_num, enable, width)
#define GPIO_GPC_GET_NWEINT_FLTCON(group, pin, fltcon_num)					\
	gpio_get_nweint_fltcon(GPIO_ROT, GPC_NWEINT_FLTCON, fltcon_num)
#define GPIO_GPD_SET_NWEINT_FLTCON(group, pin, fltcon_num, enable, width)	\
	gpio_set_nweint_fltcon(GPIO_ROT, GPD_NWEINT_FLTCON, fltcon_num, enable, width)
#define GPIO_GPD_GET_NWEINT_FLTCON(group, pin, fltcon_num)					\
	gpio_get_nweint_fltcon(GPIO_ROT, GPD_NWEINT_FLTCON, fltcon_num)
#define GPIO_GPE_SET_NWEINT_FLTCON(group, pin, fltcon_num, enable, width)	\
	gpio_set_nweint_fltcon(GPIO_ROT, GPE_NWEINT_FLTCON, fltcon_num, enable, width)
#define GPIO_GPE_GET_NWEINT_FLTCON(group, pin, fltcon_num)					\
	gpio_get_nweint_fltcon(GPIO_ROT, GPE_NWEINT_FLTCON, fltcon_num)

/**
 * @brief Sets the EINT pin configuration for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT configuration register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] irq_trigger The desired IRQ trigger type for the GPIO pin
 *
 * @return None
 */
void gpio_set_nweint_con(size_t gpio_addr, uint32_t gpio_pin, uint32_t irq_trigger);

/**
 * @brief Gets the EINT pin configuration for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT configuration register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pin configuration mode for the specified GPIO EINT pin
 */
uint32_t gpio_get_nweint_con(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the mask value for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT mask register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] mask The desired mask value for the GPIO pin
 *
 * @return None
 */
void gpio_set_nweint_mask(size_t gpio_addr, uint32_t gpio_pin, uint32_t mask);

/**
 * @brief Gets the mask value for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT mask register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current mask value for the specified GPIO EINT pin
 */
uint32_t gpio_get_nweint_mask(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the pending status for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT pending register to set
 * @param[in] gpio_pin The pin number within the GPIO group
 * @param[in] release_pend The true/false to release pending value for the GPIO pin
 *
 * @return None
 */
void gpio_set_nweint_pend(size_t gpio_addr, uint32_t gpio_pin, uint32_t release_pend);

/**
 * @brief Gets the pending status for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO EINT pending register to get
 * @param[in] gpio_pin The pin number within the GPIO group
 *
 * @return The current pending status for the specified GPIO EINT pin
 */
uint32_t gpio_get_nweint_pend(size_t gpio_addr, uint32_t gpio_pin);

/**
 * @brief Sets the fixed priority for a specific GPIO EINT group
 *
 * @param[in] gpio_addr The address of the GPIO EINT fixed priority register to set
 * @param[in] priority The desired fixed priority value for the GPIO EINT group
 *
 * @return None
 */
void gpio_set_nweint_fixpri(size_t gpio_addr, uint32_t priority);

/**
 * @brief Gets the fixed priority for a specific GPIO EINT group
 *
 * @param[in] gpio_addr The address of the GPIO EINT fixed priority register to get
 *
 * @return The current fixed priority value for the specified GPIO EINT group
 */
uint32_t gpio_get_nweint_fixpri(size_t gpio_addr);

/**
 * @brief Sets the filter configuration for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO filter configuration register to set
 * @param[in] fltcon_ptr The pointer of the filter configuration table
 * @param[in] fltcon_num The filter configuration number
 * @param[in] enable The desired enablement for the GPIO pin
 * @param[in] width The desired filter width value for the GPIO pin
 *
 * @return None
 */
void gpio_set_nweint_fltcon(size_t gpio_addr, uint32_t *fltcon_ptr, uint32_t fltcon_num,
							uint32_t enable, uint32_t width);

/**
 * @brief Gets the filter configuration for a specific GPIO EINT pin
 *
 * @param[in] gpio_addr The address of the GPIO filter configuration register to get
 * @param[in] fltcon_ptr The pointer of the filter configuration table
 * @param[in] fltcon_num The filter configuration number
 *
 * @return The current filter configuration for the specified GPIO EINT pin
 */
uint32_t gpio_get_nweint_fltcon(size_t gpio_addr, uint32_t *fltcon_ptr, uint32_t fltcon_num);

/* GPIO TZPC APIs */
/* TZPC_[BLK]_#	*/
/* 0x0 = Only secure master can access				*/
/* 0x1 = Secure & non-secure masters can access		*/
/* 0x2 ~ 0x3 = Only non-secure masters can access	*/
/* TODO : Find rule of TZPC addresses & make array and function */
#define GPIO_GPA_SET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PCIE + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPA_GET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PCIE + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPB_SET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PERI0 + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPB_GET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PERI0 + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPC_SET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_ROT + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPC_GET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_ROT + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPD_SET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_NBUS_L + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPD_GET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_NBUS_L + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPE_SET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PERI1 + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)
#define GPIO_GPE_GET_TZPC(enable)	\
	gpio_set_tzpc(GPIO_PERI1 + GPIO_TZPC + (GPIO_TZPC_GROUP_OFFSET * (group / 2)), enable)

/**
 * @brief Sets the secure mode for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO TZPC register to set
 * @param[in] gpio_pin The pin number within GPIO group
 * @param[in] secure_mode The desired secure mode value for the GPIO pin
 *
 * @return None
 */
void gpio_set_tzpc(size_t gpio_addr, uint32_t gpio_pin, uint32_t secure_mode);

/**
 * @brief Gets the secure mode for a specific GPIO pin
 *
 * @param[in] gpio_addr The address of the GPIO TZPC register to get
 * @param[in] gpio_pin The pin number within GPIO group
 *
 * @return The current secure mode for the specified GPIO pin
 */
uint32_t gpio_get_tzpc(size_t gpio_addr, uint32_t gpio_pin);

/* ISR related APIs */
#define GPIO_GPB_REGISTER_USER_CALLBACK(group, pin, callback)				\
	GPIO_GPB_USER_CALLBACK[(group * GPIO_PIN_MAX_NUM) + pin] = callback;	\
	GPIO_GPB_SET(group, pin, CON, GPIO_CON_INTERUPT);						\
	GPIO_GPB_SET_NWEINT(group, pin, CON, GPIO_EINT_CON_BOTH_EDGE);			\
	GPIO_GPB_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);	\
	GPIO_GPB_SET_NWEINT(group, pin, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT)
#define GPIO_GPC_REGISTER_USER_CALLBACK(group, pin, callback)				\
	GPIO_GPC_USER_CALLBACK[(group * GPIO_PIN_MAX_NUM) + pin] = callback;	\
	GPIO_GPC_SET(group, pin, CON, GPIO_CON_INTERUPT);						\
	GPIO_GPC_SET_NWEINT(group, pin, CON, GPIO_EINT_CON_BOTH_EDGE);			\
	GPIO_GPC_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);	\
	GPIO_GPC_SET_NWEINT(group, pin, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT)
#define GPIO_GPD_REGISTER_USER_CALLBACK(group, pin, callback)				\
	GPIO_GPD_USER_CALLBACK[(group * GPIO_PIN_MAX_NUM) + pin] = callback;	\
	GPIO_GPD_SET(group, pin, CON, GPIO_CON_INTERUPT);						\
	GPIO_GPD_SET_NWEINT(group, pin, CON, GPIO_EINT_CON_BOTH_EDGE);			\
	GPIO_GPD_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);	\
	GPIO_GPD_SET_NWEINT(group, pin, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT)
#define GPIO_GPE_REGISTER_USER_CALLBACK(group, pin, callback)				\
	GPIO_GPE_USER_CALLBACK[(group * GPIO_PIN_MAX_NUM) + pin] = callback;	\
	GPIO_GPE_SET(group, pin, CON, GPIO_CON_INTERUPT);						\
	GPIO_GPE_SET_NWEINT(group, pin, CON, GPIO_EINT_CON_BOTH_EDGE);			\
	GPIO_GPE_SET_NWEINT(group, pin, PEND, GPIO_EINT_PEND_INTERRUPT_OCCUR);	\
	GPIO_GPE_SET_NWEINT(group, pin, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT)

#define gpio_register_isr(irq_num, irq_prio, irq_type, handler, cb_ref)	\
	connect_interrupt_with_handler(irq_num, irq_prio, irq_type, handler, (void *)cb_ref)

enum {
	/* No interrupt for GPIO_PCIE */
	GPIO_ISR_PERI0,
	GPIO_ISR_ROT,
	GPIO_ISR_PERI1,
	GPIO_ISR_NBUS_L,
};

/**
 * @brief This function initializes GPIO and enables interrupts for the specified pins
 *
 * @returns 0
 */
int gpio_init(void);
