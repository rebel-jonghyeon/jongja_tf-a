/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2026 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <string.h>

#include "cpu.h"
#include "core_timer.h"
#include "rbln/core.h"
#include "rbln/rand.h"

/* generate seed on input state (Splitmix64) */
static inline uint64_t gen_states(uint64_t *state)
{
	uint64_t z;

	*state += 0x9e3779b97f4a7c15ULL;
	z = *state;
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;

	return z ^ (z >> 31);
}

static inline uint64_t rol64(uint64_t v, int r)
{
	return (v << r) | (v >> (64 - r));
}

/* generate 64 bit prandom value from states */
static inline uint64_t gen_64b_rand(uint64_t s[4])
{
	uint64_t const r = rol64(s[0] + s[3], 23) + s[0];
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return r;
}

void rand_fill(void *addr, size_t size)
{
	int i;
	uint64_t chunk;
	uint64_t state[4];
	uint8_t *ptr = addr;
	uint64_t seed = get_current_count();

	for (i = 0; i < 4; i++)
		state[i] = gen_states(&seed);

	/* Assume size is 64bit_aligned */
	for (i = 0; i < (size / 8); i++, ptr += 8) {
		chunk = gen_64b_rand(state);
		memcpy(ptr, &chunk, 8);
	}

	cpu_clean_dcache_range((uintptr_t)addr, size);
	dsb();
}
