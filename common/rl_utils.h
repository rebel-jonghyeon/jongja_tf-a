/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2023 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _RL_UTILS_H
#define _RL_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cpu.h"

#define RL_BITS_PER_BYTE		8
#define RL_BITS_PER_LONG		32
#define RL_BITS_PER_LONG_LONG	64

#define SZ_KB	0x400

#ifndef __iomem
#define __iomem
#endif /* __iomem */

#define IS_ALIGNED(x, a)        (((x) & ((typeof(x))(a) - 1)) == 0)

/* To suppress warnings about intentionally unused function arguments or local variables */
#define RL_REFERENCE(arg)	((void)(arg))

/* Bit operations for 32-bit */
#define RL_BIT(n)				(1u << (n))
#define RL_SET_BIT(v, i)		((v) |= 1u << (i))
#define RL_CLR_BIT(v, i)		((v) &= ~(1u << (i)))
#define RL_IS_SET(v, i)			((v) & (1u << (i)))
#define RL_IS_CLR(v, i)			(!RL_IS_SET(v, i))

/* Bit operations for 64-bit */
#define RL_BIT64(n)				(1ull << (n))
#define RL_SET_BIT64(v, i)		((v) |= 1ull << (i))
#define RL_CLR_BIT64(v, i)		((v) &= ~(1ull << (i)))
#define RL_IS_SET64(v, i)		((v) & (1ull << (i)))
#define RL_IS_CLR64(v, i)		(!RL_IS_SET64(v, i))
#define RL_CHECK_OVERFLOW64(v, bit_width) ((uint64_t)(v) >> (bit_width))

#define RL_CLR_FIRST_BIT(x)		(((x) - 1) & (x))
#define RL_FIRST_BIT(x)			(RL_CLR_FIRST_BIT(x) ^ (x))
#define RL_FOREACH_BIT(c, mask) \
	for (c = RL_FIRST_BIT(mask); mask != 0; \
			mask = RL_CLR_FIRST_BIT(mask), c = RL_FIRST_BIT(mask))

/* Bit operation for array */
#define RL_SET_BIT_ARRAY(a, i)	\
	(((uint8_t *)a)[(i) / RL_BITS_PER_BYTE] |= 1u << ((i) % RL_BITS_PER_BYTE))
#define RL_CLR_BIT_ARRAY(a, i)	\
	(((uint8_t *)a)[(i) / RL_BITS_PER_BYTE] &= ~(1u << ((i) % RL_BITS_PER_BYTE)))
#define RL_IS_BIT_ARRAY(a, i)	\
	(((const uint8_t *)a)[(i) / RL_BITS_PER_BYTE] & (1u << ((i) % RL_BITS_PER_BYTE)))
#define RL_IS_CLR_ARRAY(a, i)	(!(IS_BIT_ARRAY(a, i)))

#define RL_GENMASK(h, l)	\
	((0xFFFFFFFF << (l)) & (0xFFFFFFFF >> (RL_BITS_PER_LONG - 1 - (h))))
#define RL_GENMASK64(h, l)	\
	((0xFFFFFFFFFFFFFFFFull << (l)) & (0xFFFFFFFFFFFFFFFFull >> (RL_BITS_PER_LONG_LONG - 1 - (h))))

#define RL_SET_BITS(hi, lo, x)	(((x) & ((1 << ((hi) - (lo) + 1)) - 1)) << (lo))

#define RL_EXTRACT_LOW32(n)		((uint32_t)((n) & (~0)))
#define RL_EXTRACT_HIGH32(n)	((uint32_t)(((uint64_t)n >> 32) & (~0)))

#define RL_ALIGN_SIZE(size, boundary) \
	(((size) + (boundary) - 1) & ~((boundary) - 1))
#define RL_ALIGN_ADDR(addr, boundary) \
	((void *)(((uint64_t)(addr) + (boundary) - 1) & ~((uint64_t)(boundary) - 1)))

#ifndef ABS
#define ABS(v)					(((v) < 0) ? -(a) : (a))
#endif /* ABS */

#ifndef MIN
#define MIN(a, b)				(((a) < (b)) ? (a) : (b))
#endif /* MIN */

#ifndef MAX
#define MAX(a, b)				(((a) > (b)) ? (a) : (b))
#endif /* MAX */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A)			(sizeof(A) / sizeof((A)[0]))
#endif /* ARRAY_SIZE */

#ifndef OFFSET_OF
	#define OFFSET_OF(type, member)	__builtin_offsetof(type, member)
#else
	#define OFFSET_OF(type, member)	((size_t)&((type *)0)->member)
#endif /* OFFSET_OF */

#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)	((type *)((char *)(ptr) - OFFSET_OF(type, member)))
#endif /* CONTAINER_OF */

#define __bf_shf(x) (__builtin_ffsll(x) - 1)

/* Produce the maximum value representable by a filed */
#define RL_BITFIELD_MAX(_mask)			((typeof(_mask))((_mask) >> __bf_shf(_mask)))
/* Check if value fits in the field */
#define RL_BITFIELD_FIT(_mask, _val)	(!((((typeof(_mask))_val) << __bf_shf(_mask)) & ~(_mask)))
/* Prepare a bitfield element */
#define RL_BITFIELD_PREP(_mask, _val)	(((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask))
/* Extract a bitfield element */
#define RL_BITFIELD_GET(_mask, _val)	((typeof(_mask))(((_val) & (_mask)) >> __bf_shf(_mask)))
/* Set a bitfield element */
#define RL_BITFIELD_SET(_mask, _val, _old)	\
	(((_old) & ~(_mask)) | RL_BITFIELD_PREP((_mask), (_val)))
#define RL_BITFIELD_MASK(width)			((1ul << (width)) - 1)
#define RL_BITFIELD_MASK64(width)			((1ull << (width)) - 1)

#ifndef BIT
#define BIT(n) (1UL << (n))
#endif
#ifndef BIT64
#define BIT64(n) (1ULL << (n))
#endif
#ifndef BIT_MASK
#define BIT_MASK(n) (BIT(n) - 1UL)
#endif
#ifndef BIT64_MASK
#define BIT64_MASK(n) (BIT64(n) - 1ULL)
#endif

#define likely(x)	__builtin_expect((x), 1)
#define unlikely(x)	__builtin_expect((x), 0)

#define ISDIGIT(c)  (((c) >= '0') && ((c) <= '9'))
#define ISHEXDIGITU(c)  (((c) >= 'A') && ((c) <= 'F'))
#define ISHEXDIGITL(c)  (((c) >= 'a') && ((c) <= 'f'))

#define upper_32_bits(n) ((uint32_t)(((n) >> 16) >> 16))
#define lower_32_bits(n) ((uint32_t)(n))

static inline void rl_writeb(uint8_t val, volatile void __iomem *addr)
{
	dmb();
	*((volatile uint8_t *)addr) = val;
}

static inline void rl_writel(uint32_t val, volatile void __iomem *addr)
{
	dmb();
	*((volatile uint32_t *)addr) = val;
}

static inline uint32_t rl_readl(const volatile void __iomem *addr)
{
	uint32_t val = *((volatile uint32_t *)(addr));

	dmb();
	return val;
}

static inline void rl_writeq(uint64_t val, volatile void __iomem *addr)
{
	dmb();
	*((volatile uint64_t *)addr) = val;
}

static inline uint64_t rl_readq(const volatile void __iomem *addr)
{
	uint64_t val = *((volatile uint64_t *)(addr));

	dmb();
	return val;
}

static inline void rl_writel_relaxed(uint32_t val, volatile void __iomem *addr)
{
	*((volatile uint32_t *)addr) = val;
}

static inline uint32_t rl_readl_relaxed(const volatile void __iomem *addr)
{
	uint32_t val = *((volatile uint32_t *)(addr));

	return val;
}

static inline void rl_writeq_relaxed(uint64_t val, volatile void __iomem *addr)
{
	*((volatile uint64_t *)addr) = val;
}

static inline uint64_t rl_readq_relaxed(const volatile void __iomem *addr)
{
	uint64_t val = *((volatile uint64_t *)(addr));

	return val;
}

static inline void rl_memcpy32_fromio(void *dst_,
		const void __iomem *src_, size_t len)
{
	uint32_t *dst = (uint32_t *)dst_;
	const uint32_t __iomem *src = (uint32_t __iomem *)src_;

	assert(len % 4 == 0);
	while (len) {
		*dst++ = rl_readl(src++);
		len -= 4;
	}
}

static inline void rl_memcpy32_toio(void __iomem *dst_,
		const void *src_, size_t len)
{
	uint32_t __iomem *dst = (uint32_t __iomem *)dst_;
	const uint32_t *src = (uint32_t *)src_;

	assert(len % 4 == 0);
	while (len) {
		rl_writel(*src++, dst++);
		len -= 4;
	}
}

static inline int rl_find_index(const uint32_t *array,
								size_t size, uint32_t value)
{
	for (size_t i = 0; i < size; i++) {
		if (array[i] == value) {
			return (int)i;
		}
	}
	return -1;
}

static inline int rl_find_first_zero_bit(uint32_t bitmap)
{
	for (int bit = 0; bit < 32; bit++) {
		if (!(bitmap & (1U << bit))) {
			return bit;
		}
	}
	return -1;
}

static inline void rl_set_bit(uint32_t *bitmap, size_t bit)
{
	if (bit < 32) {
		*bitmap |= (1U << bit);
	}
}

static inline void rl_clear_bit(uint32_t *bitmap, size_t bit)
{
	if (bit < 32) {
		*bitmap &= ~(1U << bit);
	}
}

int crc16(unsigned char *ptr, int count);
uint32_t hex2u32(const char *num_array);

#endif /* _RL_UTILS_H */

