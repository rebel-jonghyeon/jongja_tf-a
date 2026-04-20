/*
 * Copyright (C) Arm Limited, 2019 All rights reserved.
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * The example code is provided to you as an aid to learning when working
 * with Arm-based technology, including but not limited to programming tutorials.
 * Arm hereby grants to you, subject to the terms and conditions of this Licence,
 * a non-exclusive, non-transferable, non-sub-licensable, free-of-charge licence,
 * to use and copy the Software solely for the purpose of demonstration and
 * evaluation.
 *
 * You accept that the Software has not been tested by Arm therefore the Software
 * is provided "as is", without warranty of any kind, express or implied. In no
 * event shall the authors or copyright holders be liable for any claim, damages
 * or other liability, whether in action or contract, tort or otherwise, arising
 * from, out of or in connection with the Software or the use of Software
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <arm_neon.h>

void print_matrix(float32_t *M, uint32_t rows, uint32_t cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%f ", M[j * rows + i]);
		}
		printf("\n");
	}
	printf("\n");
}

void u_print_matrix(uint32_t *M, uint32_t rows, uint32_t cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%X ", M[j * rows + i]);
		}
		printf("\n");
	}
	printf("\n");
}

void matrix_init_rand(float32_t *M, uint32_t numvals)
{
	for (int i = 0; i < numvals; i++) {
		M[i] = (float)rand() / (float)(RAND_MAX);
	}
}

void matrix_init(float32_t *M, uint32_t rows, uint32_t cols, float32_t val)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			M[j * rows + i] = val;
		}
	}
}

bool f32comp_noteq(float32_t a, float32_t b)
{
	if (fabs(a - b) < 0.000001) {
		return false;
	}
	return true;
}

int32_t matrix_comp(float32_t *A, float32_t *B, uint32_t rows, uint32_t cols)
{
	float32_t a;
	float32_t b;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			a = A[rows * j + i];
			b = B[rows * j + i];
			if (f32comp_noteq(a, b)) {
				printf("i=%d, j=%d, A=%f, B=%f\n", i, j, a, b);
				return false;
			}
		}
	}
	return true;
}

void matrix_multiply_c(float32_t *A, float32_t *B, float32_t *C, uint32_t n, uint32_t m, uint32_t k)
{
	for (int i_idx = 0; i_idx < n; i_idx++) {
		for (int j_idx = 0; j_idx < m; j_idx++) {
			for (int k_idx = 0; k_idx < k; k_idx++) {
				C[n * j_idx + i_idx] += A[n * k_idx + i_idx] * B[k * j_idx + k_idx];
			}
		}
	}
}

void matrix_init_neon(float32_t  *A, uint32_t n, float32_t val)
{
	int A_idx;

	float32x4_t A0;
	float32x4_t A1;
	float32x4_t A2;
	float32x4_t A3;

	for (int i_idx = 0; i_idx < n; i_idx += 4) {
		for (int j_idx = 0; j_idx < n; j_idx += 4) {
			A_idx = i_idx + n * j_idx;

			A0 = vmovq_n_f32(val);
			A1 = vmovq_n_f32(val);
			A2 = vmovq_n_f32(val);
			A3 = vmovq_n_f32(val);

			vst1q_f32(A + A_idx, A0);
			vst1q_f32(A + A_idx + n, A1);
			vst1q_f32(A + A_idx + 2 * n, A2);
			vst1q_f32(A + A_idx + 3 * n, A3);
		}
	}
	//print_matrix(A, n, n);

}

void matrix_copy_neon(float32_t  *A, float32_t  *B, uint32_t n)
{
	int A_idx;
	int B_idx;

	float32x4_t B0;
	float32x4_t B1;
	float32x4_t B2;
	float32x4_t B3;

	for (int i_idx = 0; i_idx < n; i_idx += 4) {
		for (int j_idx = 0; j_idx < n; j_idx += 4) {
			A_idx = i_idx + n * j_idx;
			B_idx = i_idx + n * j_idx;

			B0 = vld1q_f32(A + A_idx);
			B1 = vld1q_f32(A + A_idx + n);
			B2 = vld1q_f32(A + A_idx + 2 * n);
			B3 = vld1q_f32(A + A_idx + 3 * n);

			vst1q_f32(B + B_idx, B0);
			vst1q_f32(B + B_idx + n, B1);
			vst1q_f32(B + B_idx + 2 * n, B2);
			vst1q_f32(B + B_idx + 3 * n, B3);
		}
	}
	//print_matrix(B, n, n);
}

void matrix_multiply_neon(float32_t  *A, float32_t  *B, float32_t *C, uint32_t n, uint32_t m, uint32_t k)
{
	/*m
	 * Multiply matrices A and B, store the result in C.
	 * It is the user's responsibility to make sure the matrices are compatible.
	 */
	int A_idx;
	int B_idx;
	int C_idx;

	// these are the columns of a 4x4 sub matrix of A
	float32x4_t A0;
	float32x4_t A1;
	float32x4_t A2;
	float32x4_t A3;

	// these are the columns of a 4x4 sub matrix of B
	float32x4_t B0;
	float32x4_t B1;
	float32x4_t B2;
	float32x4_t B3;

	// these are the columns of a 4x4 sub matrix of C
	float32x4_t C0;
	float32x4_t C1;
	float32x4_t C2;
	float32x4_t C3;

	for (int i_idx = 0; i_idx < n; i_idx += 4) {
		for (int j_idx = 0; j_idx < m; j_idx += 4) {
			// Zero accumulators before matrix op
			C_idx = n * j_idx + i_idx;
			C0 = vld1q_f32(C + C_idx);
			C1 = vld1q_f32(C + C_idx + n);
			C2 = vld1q_f32(C + C_idx + 2 * n);
			C3 = vld1q_f32(C + C_idx + 3 * n);
			// C0 = vmovq_n_f32(0);
			// C1 = vmovq_n_f32(0);
			// C2 = vmovq_n_f32(0);
			// C3 = vmovq_n_f32(0);
			for (int k_idx = 0; k_idx < k; k_idx += 4) {
				// Compute base index to 4x4 block
				A_idx = i_idx + n * k_idx;
				B_idx = k * j_idx + k_idx;

				// Load most current A values in row
				A0 = vld1q_f32(A + A_idx);
				A1 = vld1q_f32(A + A_idx + n);
				A2 = vld1q_f32(A + A_idx + 2 * n);
				A3 = vld1q_f32(A + A_idx + 3 * n);

				// Multiply accumulate in 4x1 blocks, i.e. each column in C
				B0 = vld1q_f32(B + B_idx);
				C0 = vfmaq_laneq_f32(C0, A0, B0, 0);
				C0 = vfmaq_laneq_f32(C0, A1, B0, 1);
				C0 = vfmaq_laneq_f32(C0, A2, B0, 2);
				C0 = vfmaq_laneq_f32(C0, A3, B0, 3);

				B1 = vld1q_f32(B + B_idx + k);
				C1 = vfmaq_laneq_f32(C1, A0, B1, 0);
				C1 = vfmaq_laneq_f32(C1, A1, B1, 1);
				C1 = vfmaq_laneq_f32(C1, A2, B1, 2);
				C1 = vfmaq_laneq_f32(C1, A3, B1, 3);

				B2 = vld1q_f32(B + B_idx + 2 * k);
				C2 = vfmaq_laneq_f32(C2, A0, B2, 0);
				C2 = vfmaq_laneq_f32(C2, A1, B2, 1);
				C2 = vfmaq_laneq_f32(C2, A2, B2, 2);
				C2 = vfmaq_laneq_f32(C2, A3, B2, 3);

				B3 = vld1q_f32(B + B_idx + 3 * k);
				C3 = vfmaq_laneq_f32(C3, A0, B3, 0);
				C3 = vfmaq_laneq_f32(C3, A1, B3, 1);
				C3 = vfmaq_laneq_f32(C3, A2, B3, 2);
				C3 = vfmaq_laneq_f32(C3, A3, B3, 3);
			}
			// Compute base index for stores
			vst1q_f32(C + C_idx, C0);
			vst1q_f32(C + C_idx + n, C1);
			vst1q_f32(C + C_idx + 2 * n, C2);
			vst1q_f32(C + C_idx + 3 * n, C3);
		}
	}
	//print_matrix(C, n, m);
}

/*
 *return the absolute value of the difference between even Core and odd Core.
 */
void absolute_diff(float32_t  *even_C, float32_t *odd_C, float32_t *E, uint32_t n, uint32_t m)
{
	int C_idx;
	int E_idx;

	float32x4_t E0;
	float32x4_t E1;
	float32x4_t E2;
	float32x4_t E3;

	float32x4_t EC0;
	float32x4_t EC1;
	float32x4_t EC2;
	float32x4_t EC3;

	float32x4_t OC0;
	float32x4_t OC1;
	float32x4_t OC2;
	float32x4_t OC3;

	for (int i_idx = 0; i_idx < n; i_idx += 4) {
		for (int j_idx = 0; j_idx < m; j_idx += 4) {
			C_idx = n * j_idx + i_idx;
			EC0 = vld1q_f32(even_C + C_idx);
			EC1 = vld1q_f32(even_C + C_idx + n);
			EC2 = vld1q_f32(even_C + C_idx + 2 * n);
			EC3 = vld1q_f32(even_C + C_idx + 3 * n);

			OC0 = vld1q_f32(odd_C + C_idx);
			OC1 = vld1q_f32(odd_C + C_idx + n);
			OC2 = vld1q_f32(odd_C + C_idx + 2 * n);
			OC3 = vld1q_f32(odd_C + C_idx + 3 * n);

			E0 = vabdq_f32(EC0, OC0);
			E1 = vabdq_f32(EC1, OC1);
			E2 = vabdq_f32(EC2, OC2);
			E3 = vabdq_f32(EC3, OC3);

			E_idx = n * j_idx + i_idx;
			vst1q_f32(E + E_idx, E0);
			vst1q_f32(E + E_idx + n, E1);
			vst1q_f32(E + E_idx + 2 * n, E2);
			vst1q_f32(E + E_idx + 3 * n, E3);
		}
	}
	//print_matrix(E, n, m);

}

/*
 *If the size of E is smaller than Elimit, return the true to D.
 */
void comp_less_than(float32_t *E, uint32_t *D, float32x4_t Elimit, uint32_t n, uint32_t m)
{
	int E_idx;
	int D_idx;

	float32x4_t E0;
	float32x4_t E1;
	float32x4_t E2;
	float32x4_t E3;

	uint32x4_t D0;
	uint32x4_t D1;
	uint32x4_t D2;
	uint32x4_t D3;

	for (int i_idx = 0; i_idx < n; i_idx += 4) {
		for (int j_idx = 0; j_idx < m; j_idx += 4) {
			E_idx = n * j_idx + i_idx;
			E0 = vld1q_f32(E + E_idx);
			E1 = vld1q_f32(E + E_idx + n);
			E2 = vld1q_f32(E + E_idx + 2 * n);
			E3 = vld1q_f32(E + E_idx + 3 * n);
			D0 = vcltq_f32(E0, Elimit);
			D1 = vcltq_f32(E1, Elimit);
			D2 = vcltq_f32(E2, Elimit);
			D3 = vcltq_f32(E3, Elimit);
			D_idx = n * j_idx + i_idx;
			vst1q_u32(D + D_idx, D0);
			vst1q_u32(D + D_idx + n, D1);
			vst1q_u32(D + D_idx + 2 * n, D2);
			vst1q_u32(D + D_idx + 3 * n, D3);
		}
	}
	//u_print_matrix(D, n, m);
}
