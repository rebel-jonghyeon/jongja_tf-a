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

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "shake256.h"

static inline uint64_t rotl64(uint64_t x, unsigned int y)
{
	return (x << y) | ((x) >> (64 - y));
}

#define SHAKE256_RATE (200 - 2 * 32)

static void sha3_keccakf(void *state)
{
	static const uint64_t keccakf_rc[24] = {
		1ULL, 0x8082ULL, 0x800000000000808aULL, 0x8000000080008000ULL,
		0x808bULL, 0x80000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL,
		0x8aULL, 0x88ULL, 0x80008009ULL, 0x8000000aULL,
		0x8000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL,
		0x8000000000008002ULL, 0x8000000000000080ULL, 0x800aULL, 0x800000008000000aULL,
		0x8000000080008081ULL, 0x8000000000008080ULL, 0x80000001ULL, 0x8000000080008008ULL
	};
	static const uint8_t keccakf_rho[24] = {
		1,  3,  6,  10, 15, 21, 28, 36, 45, 55, 2,  14,
		27, 41, 56, 8,  25, 43, 62, 18, 39, 61, 20, 44
	};
	static const uint8_t keccakf_pi[24] = {
		10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4,
		15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1
	};

	uint64_t t, bc[5];
	uint64_t *st = (uint64_t *) state;

	for (size_t r = 0; r < 24; r++) {

		for (int i = 0; i < 5; i++)
			bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];

		for (int i = 0; i < 5; i++) {
			t = bc[(i + 4) % 5] ^ rotl64(bc[(i + 1) % 5], 1);
			for (int j = 0; j < 25; j += 5)
				st[j + i] ^= t;
		}

		t = st[1];
		for (int i = 0; i < 24; i++) {
			int j = keccakf_pi[i];

			bc[0] = st[j];
			st[j] = rotl64(t, keccakf_rho[i]);
			t = bc[0];
		}

		for (int j = 0; j < 25; j += 5) {
			for (int i = 0; i < 5; i++)
				bc[i] = st[j + i];
			for (int i = 0; i < 5; i++)
				st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
		}

		st[0] ^= keccakf_rc[r];
	}

}

shake_ctx_t *cmrt_shake256_init(shake_ctx_t *ctx)
{
	memset(ctx, 0, sizeof(shake_ctx_t));
	return ctx;
}

void cmrt_shake256_update(shake_ctx_t *c, const void *msg, size_t len)
{
	int j;
	const uint8_t *pin = (const uint8_t *) msg;

	j = c->pt;
	for (size_t i = 0; i < len; i++) {
		c->st.b[j++] ^= pin[i];
		if (j >= SHAKE256_RATE) {
			sha3_keccakf(c->st.q);
			j = 0;
		}
	}
	c->pt = j;
}

void cmrt_shake256_finish(shake_ctx_t *c, void *hash, size_t len)
{
	int j;
	uint8_t *pout = (uint8_t *) hash;

	c->st.b[c->pt] ^= 0x1FU;
	c->st.b[SHAKE256_RATE - 1] ^= 0x80U;
	sha3_keccakf(c->st.q);
	c->pt = 0;

	j = c->pt;
	for (size_t i = 0; i < len; i++) {
		if (j >= SHAKE256_RATE) {
			sha3_keccakf(c->st.q);
			j = 0;
		}
		pout[i] = c->st.b[j++];
	}
	c->pt = j;
}
