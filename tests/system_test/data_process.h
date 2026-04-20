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
#include <stdint.h>
#include "test_common.h"
#include <arm_neon.h>

void print_matrix(float32_t *M, uint32_t cols, uint32_t rows);
void matrix_init_rand(float32_t *M, uint32_t numvals);
void matrix_init(float32_t *M, uint32_t cols, uint32_t rows, float32_t val);
void matrix_init_neon(float32_t  *A, uint32_t n, float32_t val);
void matrix_copy_neon(float32_t  *A, float32_t  *B, uint32_t n);

int32_t matrix_comp(float32_t *A, float32_t *B, uint32_t rows, uint32_t cols);

void matrix_multiply_c(float32_t *A, float32_t *B, float32_t *C, uint32_t n, uint32_t m, uint32_t k);
void matrix_multiply_neon(float32_t  *A, float32_t  *B, float32_t *C, uint32_t n, uint32_t m, uint32_t k);

//two core diff&comp
void absolute_diff(float32_t  *even_C, float32_t *odd_C, float32_t *E, uint32_t n, uint32_t m);
void comp_less_than(float32_t *E, uint32_t *D, float32x4_t Elimit, uint32_t n, uint32_t m);

//one core neon process
void neon_process(float32_t *A, float32_t *B, float32_t *C, float32_t *D);

