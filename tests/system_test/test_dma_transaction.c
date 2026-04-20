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
#include "system_test.h"
#include "dma_transaction.h"
#include "unity_fixture.h"

TEST_GROUP(dma_transaction_test);

TEST_SETUP(dma_transaction_test)
{
}

TEST_TEAR_DOWN(dma_transaction_test)
{
}

static int32_t _compare_data(void *src, void *dst, uint32_t size)
{
	printf("compare start\n");
	int32_t result = memcmp(src, dst, size);

	printf("compare end\n");
	if (result) {
		for (int offset = 0; offset < (size / sizeof(uint32_t)); offset++) {
			uint32_t src_data = ((uint32_t *)src)[offset];
			uint32_t dst_data = ((uint32_t *)dst)[offset];

			if (src_data != dst_data) {
				printf("First Diff betw src(0x%p) and  dst(0x%p) is...\n", src, dst);
				printf("[offset 0x%x] src : 0x%x, dst : 0x%x\n", offset, src_data, dst_data);
				break;
			}
		}
	}

	return result;
}

TEST(dma_transaction_test, transfer_unalign_data)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 2048 + 123;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)(CHIPLET0_SYSTEST_BUF + (size << 2));

	memset(src, DATA, size);
	memset(dst, 0, size);

	transfer_data(0, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

TEST(dma_transaction_test, transfer_less_size_than_minimum)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 1024;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)(CHIPLET0_SYSTEST_BUF + (size << 2));

	memset(src, DATA, size);
	memset(dst, 0, size);

	transfer_data(0, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

TEST(dma_transaction_test, chiplet_0_to_0_512KiB)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 512 << 10;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)(CHIPLET0_SYSTEST_BUF + (size << 2));

	memset(src, DATA, size);
	memset(dst, 0, size);

	transfer_data(0, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

TEST(dma_transaction_test, chiplet_0_to_1_512KiB)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 512 << 10;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)CHIPLET1_SYSTEST_BUF;

	memset(src, DATA, size);
	memset(dst, 0, size);

	transfer_data(1, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

TEST(dma_transaction_test, chiplet_0_to_2_512KiB)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 512 << 10;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)CHIPLET2_SYSTEST_BUF;

	memset(src, DATA, size);
	memset(dst, 0, size);

	transfer_data(2, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

TEST(dma_transaction_test, chiplet_0_to_3_512KiB)
{
	const uint8_t DATA = 0xA5;

	uint32_t size = 512 << 10;
	uint32_t *src = (uint32_t *)CHIPLET0_SYSTEST_BUF;
	uint32_t *dst = (uint32_t *)CHIPLET3_SYSTEST_BUF;

	memset(dst, 0, size);
	memset(src, DATA, size);

	transfer_data(3, src, dst, size);

	TEST_ASSERT_EQUAL(0, _compare_data(src, dst, size));
}

static void all_dma_transaction_tests(void)
{
	RUN_TEST_CASE(dma_transaction_test, transfer_unalign_data);
	RUN_TEST_CASE(dma_transaction_test, transfer_less_size_than_minimum);

	RUN_TEST_CASE(dma_transaction_test, chiplet_0_to_0_512KiB);
	RUN_TEST_CASE(dma_transaction_test, chiplet_0_to_1_512KiB);
	RUN_TEST_CASE(dma_transaction_test, chiplet_0_to_2_512KiB);
	RUN_TEST_CASE(dma_transaction_test, chiplet_0_to_3_512KiB);
}

uint8_t dma_transaction_tests_main(int argc, char *argv[])
{
	UnityMain(argc + 1, (const char **)(&argv[0] - 1), all_dma_transaction_tests);

	return true;
}

CLI_REGISTER(dma_transaction_test, NULL, dma_transaction_tests_main, NULL);
