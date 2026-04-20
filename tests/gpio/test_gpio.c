/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include "test_common.h"
#include "test_gpio.h"

#include "printf.h"
#include "gpio.h"

extern void (*GPIO_GPB_USER_CALLBACK[GPIO_GPB_EINT_NUM * GPIO_PIN_MAX_NUM])(void);
extern void (*GPIO_GPC_USER_CALLBACK[GPIO_GPC_EINT_NUM * GPIO_PIN_MAX_NUM])(void);
extern void (*GPIO_GPD_USER_CALLBACK[GPIO_GPD_EINT_NUM * GPIO_PIN_MAX_NUM])(void);
extern void (*GPIO_GPE_USER_CALLBACK[GPIO_GPE_EINT_NUM * GPIO_PIN_MAX_NUM])(void);

static void test_gpio_rw(void)
{
	volatile uint32_t rec;
	volatile uint32_t val;

	/* GPIO CON */
	{
		rec = GPIO_GPB_GET(5, 0, CON);

		GPIO_GPB_SET(5, 0, CON, GPIO_CON_INPUT);
		val = GPIO_GPB_GET(5, 0, CON);
		printf("[Test] GPIO CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_CON_INPUT)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, CON, GPIO_CON_OUTPUT);
		val = GPIO_GPB_GET(5, 0, CON);
		printf("[Test] GPIO CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_CON_OUTPUT)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, CON, GPIO_CON_FUNCTION);
		val = GPIO_GPB_GET(5, 0, CON);
		printf("[Test] GPIO CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_CON_FUNCTION)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, CON, GPIO_CON_INTERUPT);
		val = GPIO_GPB_GET(5, 0, CON);
		printf("[Test] GPIO CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_CON_INTERUPT)
			printf("ERROR!\n");

		GPIO_GPB_SET(5, 0, CON, rec);
	}
	/* GPIO PUD */
	{
		rec = GPIO_GPB_GET(5, 0, PUD);

		GPIO_GPB_SET(5, 0, PUD, GPIO_PUD_DISABLE);
		val = GPIO_GPB_GET(5, 0, PUD);
		printf("[Test] GPIO PUD GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_PUD_DISABLE)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, PUD, GPIO_PUD_PULLDOWN);
		val = GPIO_GPB_GET(5, 0, PUD);
		printf("[Test] GPIO PUD GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_PUD_PULLDOWN)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, PUD, GPIO_PUD_DISABLE1);
		val = GPIO_GPB_GET(5, 0, PUD);
		printf("[Test] GPIO PUD GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_PUD_DISABLE1)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, PUD, GPIO_PUD_PULLUP);
		val = GPIO_GPB_GET(5, 0, PUD);
		printf("[Test] GPIO PUD GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_PUD_PULLUP)
			printf("ERROR!\n");

		GPIO_GPB_SET(5, 0, PUD, rec);
	}
	/* GPIO DRV */
	{
		rec = GPIO_GPB_GET(5, 0, DRV);

		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_1X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_1X)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_1_5X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_1_5X)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_2X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_2X)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_2_5X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_2_5X)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_3X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_3X)
			printf("ERROR!\n");
		GPIO_GPB_SET(5, 0, DRV, GPIO_DRV_4X);
		val = GPIO_GPB_GET(5, 0, DRV);
		printf("[Test] GPIO DRV GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_DRV_4X)
			printf("ERROR!\n");

		GPIO_GPB_SET(5, 0, DRV, rec);
	}
	/* GPIO EINT GRPPRI */
	{
		rec = GPIO_GPB_GET_EINT(5, GRPPRI);

		GPIO_GPB_SET_EINT(5, GRPPRI, GPIO_GRPPRI_NOT_ROTATE, NULL);
		val = GPIO_GPB_GET_EINT(5, GRPPRI);
		printf("[Test] GPIO EINT GRPPRI GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_GRPPRI_NOT_ROTATE)
			printf("ERROR!\n");
		GPIO_GPB_SET_EINT(5, GRPPRI, GPIO_GRPPRI_ROTATE, NULL);
		val = GPIO_GPB_GET_EINT(5, GRPPRI);
		printf("[Test] GPIO EINT GRPPRI GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_GRPPRI_ROTATE)
			printf("ERROR!\n");

		GPIO_GPB_SET_EINT(5, GRPPRI, rec, NULL);
	}
	/* GPIO EINT GRPFIXPRI */
	{
		rec = GPIO_GPB_GET_EINT(5, GRPFIXPRI);

		for (uint32_t prio = 1; prio < 26; ++prio) {
			GPIO_GPB_SET_EINT(5, GRPFIXPRI, prio, NULL);
			val = GPIO_GPB_GET_EINT(5, GRPFIXPRI);
			printf("[Test] GPIO EINT GRPFIXPRI GPB5[1] = 0x%lx\n", val);
			if (val != prio)
				printf("ERROR!\n");
		}

		GPIO_GPB_SET_EINT(5, GRPFIXPRI, rec, NULL);
	}
	/* GPIO NWEINT CON */
	{
		rec = GPIO_GPB_GET_NWEINT(5, 0, CON);

		GPIO_GPB_SET_NWEINT(5, 0, CON, GPIO_EINT_CON_LOW_LEVEL);
		val = GPIO_GPB_GET_NWEINT(5, 0, CON);
		printf("[Test] GPIO NWEINT CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_CON_LOW_LEVEL)
			printf("ERROR!\n");
		GPIO_GPB_SET_NWEINT(5, 0, CON, GPIO_EINT_CON_HIGH_LEVEL);
		val = GPIO_GPB_GET_NWEINT(5, 0, CON);
		printf("[Test] GPIO NWEINT CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_CON_HIGH_LEVEL)
			printf("ERROR!\n");
		GPIO_GPB_SET_NWEINT(5, 0, CON, GPIO_EINT_CON_FALLING_EDGE);
		val = GPIO_GPB_GET_NWEINT(5, 0, CON);
		printf("[Test] GPIO NWEINT CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_CON_FALLING_EDGE)
			printf("ERROR!\n");
		GPIO_GPB_SET_NWEINT(5, 0, CON, GPIO_EINT_CON_BOTH_EDGE);
		val = GPIO_GPB_GET_NWEINT(5, 0, CON);
		printf("[Test] GPIO NWEINT CON GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_CON_BOTH_EDGE)
			printf("ERROR!\n");

		GPIO_GPB_SET_NWEINT(5, 0, CON, rec);
	}
	/* GPIO NWEINT MASK */
	{
		rec = GPIO_GPB_GET_NWEINT(5, 0, MASK);

		GPIO_GPB_SET_NWEINT(5, 0, MASK, GPIO_EINT_MASK_ENABLE_INTERRUPT);
		val = GPIO_GPB_GET_NWEINT(5, 0, MASK);
		printf("[Test] GPIO NWEINT MASK GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_MASK_ENABLE_INTERRUPT)
			printf("ERROR!\n");
		GPIO_GPB_SET_NWEINT(5, 0, MASK, GPIO_EINT_MASK_MASK_INTERRUPT);
		val = GPIO_GPB_GET_NWEINT(5, 0, MASK);
		printf("[Test] GPIO NWEINT MASK GPB5[1] = 0x%lx\n", val);
		if (val != GPIO_EINT_MASK_MASK_INTERRUPT)
			printf("ERROR!\n");

		GPIO_GPB_SET_NWEINT(5, 0, MASK, rec);
	}
	/* GPIO NWEINT FIXPRI*/
	{
		rec = GPIO_GPB_GET_NWEINT(5, 0, FIXPRI);

		for (uint32_t prio = 0; prio < 8; ++prio) {
			GPIO_GPB_SET_NWEINT(5, 0, FIXPRI, prio);
			val = GPIO_GPB_GET_NWEINT(5, 0, FIXPRI);
			printf("[Test] GPIO NWEINT FIXPRI GPB5[1] = 0x%lx\n", val);
			if (val != prio)
				printf("ERROR!\n");
		}

		GPIO_GPB_SET_NWEINT(5, 0, FIXPRI, rec);
	}
}
/* Only possible on GPIO manipulated ZEBU image */
static char gpio_irq_test_log[1000];

/* No irq for GPA */

static void gpio_gpb_0_0(void) { strcat(gpio_irq_test_log, "GPB0[0] irq called\n"); }
static void gpio_gpb_1_0(void) { strcat(gpio_irq_test_log, "GPB1[0] irq called\n"); }
static void gpio_gpb_2_0(void) { strcat(gpio_irq_test_log, "GPB2[0] irq called\n"); }
// static void gpio_gpb_3_0(void) { strcat(gpio_irq_test_log, "GPB3[0] irq called\n"); } /* Except for UART */
static void gpio_gpb_4_0(void) { strcat(gpio_irq_test_log, "GPB4[0] irq called\n"); }
static void gpio_gpb_5_0(void) { strcat(gpio_irq_test_log, "GPB5[0] irq called\n"); }
static void gpio_gpb_6_0(void) { strcat(gpio_irq_test_log, "GPB6[0] irq called\n"); }
static void gpio_gpb_7_0(void) { strcat(gpio_irq_test_log, "GPB7[0] irq called\n"); }
static void gpio_gpb_8_0(void) { strcat(gpio_irq_test_log, "GPB8[0] irq called\n"); }
static void gpio_gpb_9_0(void) { strcat(gpio_irq_test_log, "GPB9[0] irq called\n"); }
static void gpio_gpb_10_0(void) { strcat(gpio_irq_test_log, "GPB10[0] irq called\n"); }
static void gpio_gpb_11_0(void) { strcat(gpio_irq_test_log, "GPB11[0] irq called\n"); }
static void gpio_gpb_12_0(void) { strcat(gpio_irq_test_log, "GPB12[0] irq called\n"); }
static void gpio_gpb_13_0(void) { strcat(gpio_irq_test_log, "GPB13[0] irq called\n"); }

static void gpio_gpc_0_0(void) { strcat(gpio_irq_test_log, "GPC0[0] irq called\n"); }
static void gpio_gpc_1_0(void) { strcat(gpio_irq_test_log, "GPC1[0] irq called\n"); }

/* No available output pad in GPD */
static void gpio_gpd_0_0(void) { strcat(gpio_irq_test_log, "GPD0[0] irq called\n"); }
static void gpio_gpd_0_1(void) { strcat(gpio_irq_test_log, "GPD0[1] irq called\n"); }
static void gpio_gpd_0_2(void) { strcat(gpio_irq_test_log, "GPD0[2] irq called\n"); }
static void gpio_gpd_3_0(void) { strcat(gpio_irq_test_log, "GPD3[0] irq called\n"); }
static void gpio_gpd_3_1(void) { strcat(gpio_irq_test_log, "GPD3[1] irq called\n"); }
static void gpio_gpd_3_2(void) { strcat(gpio_irq_test_log, "GPD3[2] irq called\n"); }
static void gpio_gpd_3_3(void) { strcat(gpio_irq_test_log, "GPD3[3] irq called\n"); }

static void gpio_gpe_0_0(void) { strcat(gpio_irq_test_log, "GPE0[0] irq called\n"); }
static void gpio_gpe_1_0(void) { strcat(gpio_irq_test_log, "GPE1[0] irq called\n"); }
static void gpio_gpe_2_0(void) { strcat(gpio_irq_test_log, "GPE2[0] irq called\n"); }
// static void gpio_gpe_3_0(void) { strcat(gpio_irq_test_log, "GPE3[0] irq called\n"); } /* Except for UART */
static void gpio_gpe_4_0(void) { strcat(gpio_irq_test_log, "GPE4[0] irq called\n"); }
static void gpio_gpe_5_0(void) { strcat(gpio_irq_test_log, "GPE5[0] irq called\n"); }
static void gpio_gpe_6_0(void) { strcat(gpio_irq_test_log, "GPE6[0] irq called\n"); }
static void gpio_gpe_7_0(void) { strcat(gpio_irq_test_log, "GPE7[0] irq called\n"); }
static void gpio_gpe_8_0(void) { strcat(gpio_irq_test_log, "GPE8[0] irq called\n"); }
static void gpio_gpe_9_0(void) { strcat(gpio_irq_test_log, "GPE9[0] irq called\n"); }
static void gpio_gpe_10_0(void) { strcat(gpio_irq_test_log, "GPE10[0] irq called\n"); }
static void gpio_gpe_11_0(void) { strcat(gpio_irq_test_log, "GPE11[0] irq called\n"); }
static void gpio_gpe_12_0(void) { strcat(gpio_irq_test_log, "GPE12[0] irq called\n"); }
static void gpio_gpe_13_0(void) { strcat(gpio_irq_test_log, "GPE13[0] irq called\n"); }

static void test_gpio_irq(void)
{
	GPIO_GPB_REGISTER_USER_CALLBACK(5, 1, test_gpio);

	memset(gpio_irq_test_log, 0, sizeof(gpio_irq_test_log));

	/* No irq for GPA */
	/* GPB */
	GPIO_GPB_REGISTER_USER_CALLBACK(0, 0, gpio_gpb_0_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(1, 0, gpio_gpb_1_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(2, 0, gpio_gpb_2_0);
	// GPIO_GPB_REGISTER_USER_CALLBACK(3, 0, gpio_gpb_3_0); /* Except for UART */
	GPIO_GPB_REGISTER_USER_CALLBACK(4, 0, gpio_gpb_4_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(5, 0, gpio_gpb_5_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(6, 0, gpio_gpb_6_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(7, 0, gpio_gpb_7_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(8, 0, gpio_gpb_8_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(9, 0, gpio_gpb_9_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(10, 0, gpio_gpb_10_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(11, 0, gpio_gpb_11_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(12, 0, gpio_gpb_12_0);
	GPIO_GPB_REGISTER_USER_CALLBACK(13, 0, gpio_gpb_13_0);
	/* GPC */
	GPIO_GPC_REGISTER_USER_CALLBACK(0, 0, gpio_gpc_0_0);
	GPIO_GPC_REGISTER_USER_CALLBACK(1, 0, gpio_gpc_1_0);
	/* GPD */
	GPIO_GPD_REGISTER_USER_CALLBACK(0, 0, gpio_gpd_0_0);
	GPIO_GPD_REGISTER_USER_CALLBACK(0, 1, gpio_gpd_0_1);
	GPIO_GPD_REGISTER_USER_CALLBACK(0, 2, gpio_gpd_0_2);
	GPIO_GPD_REGISTER_USER_CALLBACK(3, 0, gpio_gpd_3_0);
	GPIO_GPD_REGISTER_USER_CALLBACK(3, 1, gpio_gpd_3_1);
	GPIO_GPD_REGISTER_USER_CALLBACK(3, 2, gpio_gpd_3_2);
	GPIO_GPD_REGISTER_USER_CALLBACK(3, 3, gpio_gpd_3_3);
	/* GPE */
	GPIO_GPE_REGISTER_USER_CALLBACK(0, 0, gpio_gpe_0_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(1, 0, gpio_gpe_1_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(2, 0, gpio_gpe_2_0);
	// GPIO_GPE_REGISTER_USER_CALLBACK(3, 0, gpio_gpb_3_0); /* Except for UART */
	GPIO_GPE_REGISTER_USER_CALLBACK(4, 0, gpio_gpe_4_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(5, 0, gpio_gpe_5_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(6, 0, gpio_gpe_6_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(7, 0, gpio_gpe_7_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(8, 0, gpio_gpe_8_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(9, 0, gpio_gpe_9_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(10, 0, gpio_gpe_10_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(11, 0, gpio_gpe_11_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(12, 0, gpio_gpe_12_0);
	GPIO_GPE_REGISTER_USER_CALLBACK(13, 0, gpio_gpe_13_0);

	/* Sleep */
	for (uint32_t i = 0; i < 1000000; ++i)
		__asm__ volatile ("nop");
	/* Print logs */
	printf(gpio_irq_test_log);
}
void test_gpio(void)
{
	test_gpio_rw();
	test_gpio_irq();

	/* Restore GPIO configuration */
	gpio_init();
}

uint8_t test_gpio_cli(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart gpio test\n");
	test_gpio();

	return ret;
}

static const char help_gpio[] = "[gpio]\nTest for GPIO driver\n\r\n";

CLI_REGISTER(gpio, NULL, test_gpio_cli, help_gpio);
