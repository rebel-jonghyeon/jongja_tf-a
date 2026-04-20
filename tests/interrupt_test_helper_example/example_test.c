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
#include "example_driver.h"
#include "interrupt_test_helper.h"
#include "interrupt.h"
#include "unity_fixture.h"
#include "task.h"

#if defined(__TARGET_PCIE)
#define IRQ_NUM_FOR_TEST (29)
#define IRQ_PRIO_FOR_TEST (0)
#elif defined(__TARGET_CP)
#define IRQ_NUM_FOR_TEST (92)
#define IRQ_PRIO_FOR_TEST (0)
#endif

static void some_delay(void)
{
	#if defined(__TARGET_CP)
	/*
	 * Since IRQ is processed as a multi-core in CA73,
	 * some delay is required to distinguish individual IRQ service processing.
	 */
	volatile int count = 10000;

	while (count--) {
	}
	#endif//__TARGET_CP
}

TEST_GROUP(interrupt_test_helper_example);

TEST_SETUP(interrupt_test_helper_example)
{
	TEST_ASSERT_TRUE(interrupt_test_init(IRQ_NUM_FOR_TEST));
	driver_init();
	connect_interrupt_with_handler(IRQ_NUM_FOR_TEST, IRQ_PRIO_FOR_TEST, IRQ_TYPE_LEVEL,
								   driver_isr, NULL);
}

TEST_TEAR_DOWN(interrupt_test_helper_example)
{
	TEST_ASSERT_TRUE(interrupt_test_end(IRQ_NUM_FOR_TEST));
}

TEST(interrupt_test_helper_example, check_device_init)
{
	TEST_ASSERT_EQUAL(0, get_device_state());
	TEST_ASSERT_EQUAL(0, get_isr_call_count());
}

TEST(interrupt_test_helper_example, check_set_device_state)
{
	set_device_state(-1);
	TEST_ASSERT_EQUAL(-1, get_device_state());
}

TEST(interrupt_test_helper_example, is_isr_called)
{
	interrupt_set_pending(IRQ_NUM_FOR_TEST);
	some_delay();
	TEST_ASSERT_EQUAL(1, get_isr_call_count());
}

TEST(interrupt_test_helper_example, check_updating_dev_state_by_isr)
{
	set_device_state(7);
	interrupt_set_pending(IRQ_NUM_FOR_TEST);
	some_delay();
	TEST_ASSERT_EQUAL(1234, get_device_state());
}

TEST(interrupt_test_helper_example, check_multi_calling_isr)
{
	set_device_state(777);
	interrupt_set_pending(IRQ_NUM_FOR_TEST);
	some_delay();
	interrupt_set_pending(IRQ_NUM_FOR_TEST);
	some_delay();
	interrupt_set_pending(IRQ_NUM_FOR_TEST);
	some_delay();
	TEST_ASSERT_EQUAL(3, get_isr_call_count());
	TEST_ASSERT_EQUAL(1234, get_device_state());
}

/**
 * To explain the difference between the Test Group Runner and the Test Group,
 * it is composed of two runners.
 **/
TEST_GROUP_RUNNER(interrupt_test_helper_example_1)
{
	RUN_TEST_CASE(interrupt_test_helper_example, check_device_init);
	RUN_TEST_CASE(interrupt_test_helper_example, check_set_device_state);
}

TEST_GROUP_RUNNER(interrupt_test_helper_example_2)
{
	RUN_TEST_CASE(interrupt_test_helper_example, is_isr_called);
	RUN_TEST_CASE(interrupt_test_helper_example, check_updating_dev_state_by_isr);
	RUN_TEST_CASE(interrupt_test_helper_example, check_multi_calling_isr);
}

static void all_tests(void)
{
	RUN_TEST_GROUP(interrupt_test_helper_example_1);
	RUN_TEST_GROUP(interrupt_test_helper_example_2);
}

uint8_t example_driver_isr_test(int argc, char *argv[])
{
	UnityMain(argc + 1, (const char **)(&argv[0] - 1), all_tests);

	return true;
}

CLI_REGISTER(interrupt_helper_example, NULL, example_driver_isr_test, NULL);
