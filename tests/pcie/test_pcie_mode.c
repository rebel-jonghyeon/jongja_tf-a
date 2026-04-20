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

#include "FreeRTOS.h"
#include "task.h"

#include "unity_fixture.h"
#include "test_common.h"
#include "rl_errors.h"

#include "pcie_dw.h"

#if defined(ZEBU)
#define T_DELAY (1)
#else
#define T_DELAY (10)
#endif

static const char help_pcie_set_speed[] =
	"[pcie set_speed <speed>]\r\n"
	"\r\n";

static const char help_pcie_set_width[] =
	"[pcie set_width <width>]\r\n"
	"\r\n";

int32_t test_pcie_set_speed(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_set_speed);
		return RL_BADARG;
	}

	uint8_t speed = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	return pcie_set_speed(epc, speed);
}

int32_t test_pcie_set_width(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_set_width);
		return RL_BADARG;
	}

	uint8_t width = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	return pcie_set_width(epc, width);
}

int32_t test_pcie_get_speed(void)
{
	struct pcie_epc *epc = pcie_get_epc();
	int32_t speed;

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	speed = pcie_get_speed(epc);
	if (speed == GEN1) {
		printf("PCIe current rate is 2.5GT/s\n");
	} else if (speed == GEN2) {
		printf("PCIe current rate is 5.0GT/s\n");
	} else if (speed == GEN3) {
		printf("PCIe current rate is 8.0GT/s\n");
	} else if (speed == GEN4) {
		printf("PCIe current rate is 16.0GT/s\n");
	} else if (speed == GEN5) {
		printf("PCIe current rate is 32.0GT/s\n");
	} else {
		printf("Unexpected PCIe rate %d\n", speed);
	}

	return RL_OK;
}

int32_t test_pcie_get_width(void)
{
	struct pcie_epc *epc = pcie_get_epc();
	int32_t width;

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	width = pcie_get_width(epc);
	printf("PCIe current width is %d\n", width);

	return RL_OK;
}

static uint8_t origin_speed, origin_width;
static struct pcie_epc *pcie_epc;

TEST_GROUP(pcie_change_speed);

TEST_SETUP(pcie_change_speed)
{
	pcie_epc = pcie_get_epc();
	origin_speed = pcie_get_speed(pcie_epc);
}

TEST_TEAR_DOWN(pcie_change_speed)
{
	pcie_set_speed(pcie_epc, origin_speed);
	vTaskDelay(T_DELAY);
	pcie_epc = NULL;
}

TEST(pcie_change_speed, change_speed_gen1)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, GEN1));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(GEN1, pcie_get_speed(pcie_epc));
}

TEST(pcie_change_speed, change_speed_gen2)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, GEN2));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(GEN2, pcie_get_speed(pcie_epc));
}

TEST(pcie_change_speed, change_speed_gen3)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, GEN3));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(GEN3, pcie_get_speed(pcie_epc));
}

TEST(pcie_change_speed, change_speed_gen4)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, GEN4));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(GEN4, pcie_get_speed(pcie_epc));
}

TEST(pcie_change_speed, change_speed_gen5)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, GEN5));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(GEN5, pcie_get_speed(pcie_epc));
}

TEST(pcie_change_speed, fail_to_change_speed_gen6)
{
	TEST_ASSERT_NOT_EQUAL(RL_OK, pcie_set_speed(pcie_epc, 6));
	vTaskDelay(T_DELAY);
}

TEST_GROUP_RUNNER(pcie_change_speed_group)
{
	RUN_TEST_CASE(pcie_change_speed, change_speed_gen1);
	RUN_TEST_CASE(pcie_change_speed, change_speed_gen2);
	RUN_TEST_CASE(pcie_change_speed, change_speed_gen3);
	RUN_TEST_CASE(pcie_change_speed, change_speed_gen4);
	RUN_TEST_CASE(pcie_change_speed, change_speed_gen5);
	RUN_TEST_CASE(pcie_change_speed, fail_to_change_speed_gen6);
}

TEST_GROUP(pcie_change_width);

TEST_SETUP(pcie_change_width)
{
	pcie_epc = pcie_get_epc();
	origin_width = pcie_get_width(pcie_epc);
}

TEST_TEAR_DOWN(pcie_change_width)
{
	pcie_set_width(pcie_epc, origin_width);
	vTaskDelay(T_DELAY);
	pcie_epc = NULL;
}

TEST(pcie_change_width, change_speed_width_1)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 1));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(1, pcie_get_width(pcie_epc));
}

TEST(pcie_change_width, change_speed_width_2)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 2));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(2, pcie_get_width(pcie_epc));
}

TEST(pcie_change_width, change_speed_width_4)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 4));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(4, pcie_get_width(pcie_epc));
}

TEST(pcie_change_width, change_speed_width_8)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 8));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(8, pcie_get_width(pcie_epc));
}

TEST(pcie_change_width, change_speed_width_16)
{
	TEST_ASSERT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 16));
	vTaskDelay(T_DELAY);
	TEST_ASSERT_EQUAL(16, pcie_get_width(pcie_epc));
}

TEST(pcie_change_width, fail_to_change_speed_width_32)
{
	TEST_ASSERT_NOT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 32));
	vTaskDelay(T_DELAY);
}

TEST(pcie_change_width, fail_to_change_speed_width_6)
{
	TEST_ASSERT_NOT_EQUAL(RL_OK, pcie_set_width(pcie_epc, 6));
	vTaskDelay(T_DELAY);
}

TEST_GROUP_RUNNER(pcie_change_width_group)
{
	RUN_TEST_CASE(pcie_change_width, change_speed_width_1);
	RUN_TEST_CASE(pcie_change_width, change_speed_width_2);
	RUN_TEST_CASE(pcie_change_width, change_speed_width_4);
	RUN_TEST_CASE(pcie_change_width, change_speed_width_8);
	RUN_TEST_CASE(pcie_change_width, change_speed_width_16);
	RUN_TEST_CASE(pcie_change_width, fail_to_change_speed_width_32);
	RUN_TEST_CASE(pcie_change_width, fail_to_change_speed_width_6);
}

static void pcie_mode_tests(void)
{
	RUN_TEST_GROUP(pcie_change_speed_group);
	RUN_TEST_GROUP(pcie_change_width_group);
}

int32_t test_pcie_mode(int argc, char *argv[])
{
	return UnityMain(argc, (const char **)argv, pcie_mode_tests);
}
