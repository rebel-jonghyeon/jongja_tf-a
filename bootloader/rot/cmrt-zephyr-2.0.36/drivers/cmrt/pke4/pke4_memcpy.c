/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include <drivers/cmrt/pke_memcpy.h>

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
#include "pke4_random.h"
#endif

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
static int setup_random_ordering(uint8_t *order, const uint32_t wlength, const int8_t slot)
{
	int ret = 0;
	int j;

	uint32_t i;
	uint32_t rorder_length;

	uint8_t ordering[PKE_CP_ORDER_SIZE];
	uint8_t tmp;

	if (wlength < PKE_CP_ORDER_SIZE) {
		rorder_length = wlength;
	} else {
		rorder_length = PKE_CP_ORDER_SIZE;
	}

	for (i = 0; i < rorder_length; i++) {
		order[i] = i % rorder_length;
	}

	if (slot != PKE_CP_NO_RANDOM_ORDER) {
#ifdef CONFIG_CMRT_PKE_32_BIT
		ret = cmrt_pke_get_pseudo_random(ordering, rorder_length, slot, wlength);
#else /* 64 bit*/
		ret = cmrt_pke_get_pseudo_random(ordering, rorder_length, slot, ((wlength - 1) / 2) + 1);
#endif
		if (ret) {
			goto err;
		}

		for (i = 0; i < rorder_length; i++) {
			j = ordering[i] % rorder_length;
			tmp = order[i];
			order[i] = order[j];
			order[j] = tmp;
		}
	}

err:
	return ret;
}
#endif

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
static int __copy_to_pke(const uint8_t *input, const size_t input_length, uint32_t *out, const int8_t slot)
#else
static int __copy_to_pke(const uint8_t *input, const size_t input_length, uint32_t *out)
#endif
{
	uint32_t i = 0;

	int j = 0;
#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
	int k = 0;
#endif
	int ret = 0;

	uint32_t temp;
	uint32_t length = input_length;
	uint32_t wlength = ((length - 1) / sizeof(uint32_t) + 1);
#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
	uint32_t sum = 0;
	uint32_t sum2 = 0;
#endif
	uint32_t iw;
	uint32_t ow;

	uint8_t *in;

	if (!input || !out) {
		ret = -EINVAL;
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
	uint8_t order[PKE_CP_ORDER_SIZE];

	ret = setup_random_ordering(order, wlength, slot);
	if (ret) {
		goto err;
	}
#endif

#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
	if ((length & (sizeof(uint32_t) - 1)) != 0) {
		in = (uint8_t *)input - sizeof(uint32_t) + (length & (sizeof(uint32_t) - 1));
	} else {
		in = (uint8_t *)input;
	}
#else
	in = (uint8_t *)input;
#endif

#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
	if ((length & (sizeof(uint32_t) - 1)) != 0) {
		length = wlength * sizeof(uint32_t);
	}
#endif

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
	k = wlength;
#endif

	for (i = 0; i < wlength; i++) {
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		/* compute in random order? */
		iw = (i & 0xFFFFFFE0) + order[i & (PKE_CP_ORDER_SIZE - 1)];
#else
		iw = i;
#endif

#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		/* reverse 32-bit words */
		ow = (wlength - iw - 1);
#else
		ow = iw;
#endif

		temp = 0;
#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		/* reverse endianness of 32-bit words? */
		for (j = 3; (j >= 0) && (&(in[(4 * iw) + j]) >= input); j--) {
			temp ^= in[(4 * iw) + j] << (8 * (3 - j));
		}
#else
		for (j = 3; (j >= 0) && (&(in[(4 * iw) + j]) >= input); j--) {
			temp ^= in[(4 * iw) + j] << (8 * j);
		}
#endif

#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
		/* compute sum of bytes of read key */
		sum += (temp >> 24) + ((temp >> 16) & 0xff) + ((temp >> 8) & 0xff) + (temp & 0xff);
#endif

		out[ow] = temp;

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
		/* are loop counters consistent */
		if ((i + k) != wlength) {
			ret = -EFAULT;
			goto err;
		}
		k--;
#endif
	}

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
	/* are loop counters consistent */
	if ((i + k) != wlength) {
		ret = -EFAULT;
		goto err;
	}
#endif

#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
	/* compute sum of bytes of written key */
	for (i = 0; i < wlength; i++) {
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		iw = (i & 0xFFFE0) + order[i & (PKE_CP_ORDER_SIZE - 1)];
#else
		iw = i;
#endif

		sum2 += (out[iw] >> 24) + ((out[iw] >> 16) & 0xff) + ((out[iw] >> 8) & 0xff) + (out[iw] & 0xff);
	}

	/* written key and read key sums need to be equal */
	if (sum != sum2) {
		ret = -EFAULT;
	}
#endif

err:
	return ret;
}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
int copy_to_pke(const uint8_t *input, const size_t input_length, uint32_t *out, const int8_t slot)
#else
int copy_to_pke(const uint8_t *input, const size_t input_length, uint32_t *out)
#endif
{
	int ret = 0;

	if (!input || !out) {
		ret = -EINVAL;
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
	size_t r = input_length & ((4 * PKE_CP_ORDER_SIZE) - 1);
	size_t q = input_length - r;

	if ((input_length < (4 * PKE_CP_ORDER_SIZE)) || (r == 0)) {
		ret = __copy_to_pke(input, input_length, out, slot);
	} else {
#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		ret = __copy_to_pke(input, r, out + (q / sizeof(uint32_t)), slot);
		if (ret) {
			goto err;
		}

		ret = __copy_to_pke(input + r, q, out, slot);
#else
		ret = __copy_to_pke(input, q, out, slot);
		if (ret) {
			goto err;
		}

		ret = __copy_to_pke(input + q, r, out + (q / sizeof(uint32_t)), slot);
#endif
	}
#else
	ret = __copy_to_pke(input, input_length, out);
#endif

err:
	return ret;
}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
static int __copy_from_pke(uint32_t *in, const size_t input_length, uint8_t *output, const int8_t slot)
#else
static int __copy_from_pke(uint32_t *in, const size_t input_length, uint8_t *output)
#endif
{
	int ret = 0;
	int j = 0;

	uint32_t i = 0;

	uint32_t iw;
	uint32_t ow;
	uint32_t temp;
#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
	uint32_t sum = 0;
	uint32_t sum2 = 0;
#endif
	uint32_t length = input_length;
	uint32_t wlength = ((length - 1) / sizeof(uint32_t) + 1);

	uint8_t *out;

	if (!in || !output) {
		ret = -EINVAL;
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
	uint8_t order[PKE_CP_ORDER_SIZE];

	ret = setup_random_ordering(order, wlength, slot);
	if (ret) {
		goto err;
	}
#endif

#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
	if ((length & (sizeof(uint32_t) - 1)) != 0) {
		out = (uint8_t *)output - sizeof(uint32_t) + (length & (sizeof(uint32_t) - 1));
		length = wlength * sizeof(uint32_t);
	} else {
		out = (uint8_t *)output;
	}
#else
	out = (uint8_t *)output;
#endif

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
	int	k = wlength;
#endif

	for (i = 0; i < wlength; i++) {
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		/* compute in random order? */
		iw = (i & 0xFFFFFFE0) + order[i & (PKE_CP_ORDER_SIZE  - 1)];
#else
		iw = i;
#endif

#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		/* reverse 32-bit words */
		ow = (wlength - iw - 1);
#else
		ow = iw;
#endif

		temp = in[iw];
#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		/* reverse endianness of 32-bit words? */
		for (j = 3; (j >= 0) && (&(out[(4 * ow) + j]) >= output); j--) {
			out[(4 * ow) + j] = (temp >> (8 * (3 - j))) & 0xff;
		}
#else
		for (j = 3; (j >= 0) && (&(out[(4 * ow) + j]) >= output); j--) {
			out[(4 * ow) + j] = (temp >> (8 * j)) & 0xff;
		}
#endif

#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
		/* compute sum of bytes of read key */
		sum += (temp >> 24) + ((temp >> 16) & 0xff) + ((temp >> 8) & 0xff) + (temp & 0xff);
#endif

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
		/* are loop counters consistent */
		if ((i + k) != wlength) {
			ret = -EFAULT;
			goto err;
		}
		k--;
#endif
	}

#ifdef CONFIG_CMRT_PKE_CP_PROTECT_LOOP
	/* are loop counters consistent */
	if ((i + k) != wlength) {
		ret = -EFAULT;
		goto err;
	}
#endif

	/* compute sum of bytes of written key */
#ifdef CONFIG_CMRT_PKE_CP_SUM_WORDS
	for (i = 0; i < wlength; i++) {
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		iw = (i & 0xFFFE0) + order[i & (PKE_CP_ORDER_SIZE - 1)];
#else
		iw = i;
#endif
		for (j = 3; (j >= 0) && (&(out[(4 * iw) + j]) >= output); j--) {
			sum2 += out[(4 * iw) + j];
		}
	}

	/* written key and read key sums need to be equal */
	if (sum != sum2) {
		ret = -EFAULT;
	}
#endif

err:
	return ret;
}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
int copy_from_pke(uint32_t *in, const size_t input_length, uint8_t *output, const int8_t slot)
#else
int copy_from_pke(uint32_t *in, const size_t input_length, uint8_t *output)
#endif
{
	int ret = 0;

	if (input_length == 1) {
		output[0] = (uint8_t) in[0];
		goto exit;
	}

	if (!in || !output) {
		ret = -EINVAL;
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
	size_t r = input_length & ((4 * PKE_CP_ORDER_SIZE) - 1);
	size_t q = input_length - r;

	if ((input_length < (4 * PKE_CP_ORDER_SIZE)) || (r == 0)) {
		ret = __copy_from_pke(in, input_length, output, slot);
	} else {
#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		ret = __copy_from_pke(in, r, output + q, slot);
		if (ret) {
			goto err;
		}

		ret = __copy_from_pke(in + (r / sizeof(uint32_t)), q, output, slot);
#else
		ret = __copy_from_pke(in, q, output, slot);
		if (ret) {
			goto err;
		}

		ret = __copy_from_pke(in + (q / sizeof(uint32_t)), r, output + q, slot);
#endif
	}
#else
	ret = __copy_from_pke(in, input_length, output);
#endif

err:
exit:
	return ret;
}
