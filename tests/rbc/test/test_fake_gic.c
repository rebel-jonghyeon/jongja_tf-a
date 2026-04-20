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
#include "fake_gic.h"

TEST_GROUP(fake_gic);

TEST_SETUP(fake_gic)
{
}

TEST_TEAR_DOWN(fake_gic)
{
}

static void test_isr(void *data)
{
	uint32_t *count = (uint32_t *)data;
	*count += 1;
}

TEST(fake_gic, call_isr)
{
	const uint32_t irq_id = 123;
	uint32_t count = 0;

	gic_irq_connect(irq_id, test_isr, &count);
	call_interrupt_handler(irq_id);
	call_interrupt_handler(irq_id);
	call_interrupt_handler(irq_id);

	TEST_ASSERT_EQUAL(3, count);
}
