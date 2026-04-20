/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Markku-Juhani O. Saarinen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRI_SHAKE256_H
#define CRI_SHAKE256_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief context for shake256 operation.
 *
 * User shall allocate the context by its own.
 */
struct shake_ctx {
	union {
		uint8_t b[200];
		uint64_t q[25];
	} st;
	int pt;
};

typedef struct shake_ctx shake_ctx_t;

/**
 * @brief Initiate shake256 context.
 *
 * @param ctx Pointer to given shake256 context.
 * @retval Returns Pointer to shake256 context.
 */
shake_ctx_t *cmrt_shake256_init(shake_ctx_t *ctx);

/**
 * @brief Update shake256 context with bytes.
 *
 * @param ctx Pointer to given shake256 context.
 * @param msg Pointer to bytes to be updated.
 * @param len Length of msg in bytes.
 */
void cmrt_shake256_update(shake_ctx_t *ctx, const void *msg, size_t len);

/**
 * @brief Finalize shake256.
 *
 * @param ctx Pointer to given shake256 context.
 * @param hash Pointer to output.
 * @param len Length of hash in bytes.
 */
void cmrt_shake256_finish(shake_ctx_t *ctx, void *hash, size_t len);

#ifdef __cplusplus
}
#endif

#endif
