/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include "unity_fixture.h"
#include "fake_timer.h"

TEST_GROUP(fake_timer);

TEST_SETUP(fake_timer)
{
}

TEST_TEAR_DOWN(fake_timer)
{
}

TEST(fake_timer, set_fake_tick)
{
	uint32_t tick;

	fake_set_tick(100);
	tick = get_tick();
	TEST_ASSERT_EQUAL(100, tick);
}

TEST(fake_timer, set_fake_tick_increment)
{
	uint32_t increment = 10;
	uint32_t tick;

	fake_set_tick_increment(increment);
	tick = get_tick();
	TEST_ASSERT_EQUAL(increment, get_tick()-tick);
}
