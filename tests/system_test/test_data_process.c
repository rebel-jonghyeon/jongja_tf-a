/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include "data_process.h"
#include "unity_fixture.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <arm_neon.h>
#define BLOCK_SIZE 16
TEST_GROUP(data_process_test);

TEST_SETUP(data_process_test)
{
}

TEST_TEAR_DOWN(data_process_test)
{
}

static int32_t _u32_matrix_comp(uint32_t *A, uint32_t *B, uint32_t rows, uint32_t cols)
{
	uint32_t a;
	uint32_t b;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			a = A[rows * j + i];
			b = B[rows * j + i];
			if (a != b) {
				printf("i=%d, j=%d, A=%d, B=%d\n", i, j, a, b);
				return false;
			}
		}
	}
	return true;
}

static void _u32_matrix_init(uint32_t *M, uint32_t rows, uint32_t cols, uint32_t val)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			M[j * rows + i] = val;
		}
	}
}

TEST(data_process_test, check_true_result_matrix_comp)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	float32_t A[n * m];
	float32_t B[n * m];

	matrix_init(A, n, m, 1);
	matrix_init(B, n, m, 1);

	TEST_ASSERT_EQUAL(true, matrix_comp(A, B, n, m));
}

TEST(data_process_test, check_false_result_matrix_comp)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	float32_t A[n * m];
	float32_t B[n * m];

	matrix_init(A, n, m, 1);
	matrix_init(B, n, m, 0);
	TEST_ASSERT_EQUAL(false, matrix_comp(A, B, n, m));
}

TEST(data_process_test, check_matrix_init_neon)
{
	float32_t pi = 3.1415927410125732F;
	uint32_t n = BLOCK_SIZE;

	float32_t A[n * n];
	float32_t B[n * n];
	float32_t C[n * n];
	float32_t comp_A[n * n];
	float32_t comp_B[n * n];
	float32_t comp_C[n * n];

	matrix_init_neon(A, n, pi);
	matrix_copy_neon(A, B, n);
	matrix_copy_neon(A, C, n);

	matrix_init(comp_A, n, n, pi);
	matrix_init(comp_B, n, n, pi);
	matrix_init(comp_C, n, n, pi);

	TEST_ASSERT_EQUAL(true,  matrix_comp(A, comp_A, n, n));
	TEST_ASSERT_EQUAL(true,  matrix_comp(B, comp_B, n, n));
	TEST_ASSERT_EQUAL(true,  matrix_comp(C, comp_C, n, n));
}

TEST(data_process_test, comp_zero_matrix_multiply_neon)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	uint32_t k = BLOCK_SIZE;
	float32_t A[n * k];
	float32_t B[k * m];
	float32_t C[n * m];
	float32_t CC[n * m];

	matrix_init(A, n, k, 0);
	matrix_init(B, k, m, 0);
	matrix_init(C, n, m, 0);
	matrix_init(CC, n, m, 0);

	matrix_multiply_neon(A, B, C, n, m, k);
	matrix_multiply_c(A, B, CC, n, m, k);

	TEST_ASSERT_EQUAL(true,  matrix_comp(C, CC, n, m));
}

TEST(data_process_test, comp_rand_matrix_multiply_neon)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	uint32_t k = BLOCK_SIZE;
	float32_t A[n * k];
	float32_t B[k * m];
	float32_t C[n * m];
	float32_t CC[n * m];

	matrix_init_rand(A, n * k);
	matrix_init_rand(B, k * m);
	matrix_init(C, n, m, 0);
	matrix_init(CC, n, m, 0);
	matrix_multiply_neon(A, B, C, n, m, k);
	matrix_multiply_c(A, B, CC, n, m, k);

	TEST_ASSERT_EQUAL(true,  matrix_comp(C, CC, n, m));
}

TEST(data_process_test, comp_pi_matrix_multiply_neon)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	uint32_t k = BLOCK_SIZE;
	float32_t A[n * k];
	float32_t B[k * m];
	float32_t C[n * m];
	float32_t CC[n * m];
	float32_t pi = 3.1415927410125732F;

	matrix_init(A, n, k, pi);
	matrix_init(B, k, m, pi);
	matrix_init(C, n, m, pi);
	matrix_init(CC, n, m, pi);
	matrix_multiply_neon(A, B, C, n, m, k);
	matrix_multiply_c(A, B, CC, n, m, k);

	TEST_ASSERT_EQUAL(true,  matrix_comp(C, CC, n, m));
}

TEST(data_process_test, check_absolute_diff_result)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	float32_t even_C[n * m];
	float32_t odd_C[n * m];
	float32_t E[n * m];
	float32_t comp_E[n * m];
	float32_t pi = 3.1415927410125732F;

	matrix_init(even_C, n, m, pi);
	matrix_init(odd_C, n, m, pi);
	absolute_diff(even_C, odd_C, E, n, m);

	matrix_init(comp_E, n, m, 0);
	TEST_ASSERT_EQUAL(true,  matrix_comp(comp_E, E, n, m));
}

TEST(data_process_test, check_true_comp_less_than_result)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	float32_t E[n * m];
	uint32_t D[n * m];
	float32x4_t Elimit = {2, 2, 2, 2};
	uint32_t comp_D[n * m];

	matrix_init(E, n, m, 0);
	comp_less_than(E, D, Elimit, n, m);
	_u32_matrix_init(comp_D, n, m, 0);
	TEST_ASSERT_NOT_EQUAL(true,  _u32_matrix_comp(D, comp_D, n, m));
}

TEST(data_process_test, check_false_comp_less_than_result)
{
	uint32_t n = BLOCK_SIZE;
	uint32_t m = BLOCK_SIZE;
	float32_t E[n * m];
	uint32_t D[n * m];
	float32x4_t Elimit = {0, 0, 0, 0};
	uint32_t comp_D[n * m];

	matrix_init(E, n, m, 2);
	comp_less_than(E, D, Elimit, n, m);
	_u32_matrix_init(comp_D, n, m, 0);
	TEST_ASSERT_EQUAL(true,  _u32_matrix_comp(D, comp_D, n, m));
}

static void all_data_process_tests(void)
{
	RUN_TEST_CASE(data_process_test, check_true_result_matrix_comp);
	RUN_TEST_CASE(data_process_test, check_false_result_matrix_comp);
	RUN_TEST_CASE(data_process_test, check_matrix_init_neon);
	RUN_TEST_CASE(data_process_test, comp_zero_matrix_multiply_neon);
	RUN_TEST_CASE(data_process_test, comp_rand_matrix_multiply_neon);
	RUN_TEST_CASE(data_process_test, comp_pi_matrix_multiply_neon);
	RUN_TEST_CASE(data_process_test, check_absolute_diff_result);
	RUN_TEST_CASE(data_process_test, check_true_comp_less_than_result);
	RUN_TEST_CASE(data_process_test, check_false_comp_less_than_result);
}

uint8_t data_process_tests_main(int argc, char *argv[])
{
	UnityMain(argc + 1, (const char **)(&argv[0] - 1), all_data_process_tests);
	return true;
}

CLI_REGISTER(data_process_test, NULL, data_process_tests_main, NULL);
