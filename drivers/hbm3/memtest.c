#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <cache.h>
#include "memtest.h"

#define DBG_EN		0
#if DBG_EN
#define dprintf(...) printf(__VA_ARGS__)
#else
#define dprintf(...) do {} while (0)
#endif

struct test_list {
	char *name;
	int (*fp)(ullv *bufa, ullv *bufb, size_t count);
};

typedef union {
	unsigned char bytes[UL_LEN / 8];
	ull val;
} mword8_t;

typedef union {
	unsigned short u16s[UL_LEN / 16];
	ull val;
} mword16_t;

int compare_regions(ullv *bufa, ullv *bufb, size_t count)
{
	int ret = 0;
	size_t i, j;
	ullv *p1 = bufa;
	ullv *p2 = bufb;

	// arch_dcache_flush_range((void *)p1, sizeof(ullv *) * count);
	// arch_dcache_flush_range((void *)p2, sizeof(ullv *) * count);

	for (i = 0; i < count; i++, p1++, p2++) {
		if (*p1 != *p2) {
			dprintf(" A:0x%08lx -- 0x%016llx != A:0x%08lx -- 0x%016llx  ::  ",
					(ul)p1, (ull)(*p1), (ul)p2, (ull)(*p2));
					//printf("comapre Fail\n");

			ull diff = *p1 ^ *p2;

			for (j = 0 ; j < 64 ; j++) {
				if (((diff >> j) & 0x1) == 0x1)
					dprintf(" %lu,", j);
			}
			dprintf("\r\n");

			ret = -1;
		}
	}
	return ret;
}

int test_stuck_address(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	int ret = 0;
	size_t i, j;

	for (j = 0; j < 16; j++) {

		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;

		for (i = 0; i < count; i++) {
			*p1 = ((j + i) % 2) == 0 ? (ull)p1 : ~((ull)p1);
			*p2 = ((j + i) % 2) == 0 ? (ull)p1 : ~((ull)p1);

			p1++;
			p2++;
		}

		ret = compare_regions(bufa, bufb, count);
		if (ret) {
			return ret;
		}
	}

	return 0;
}

int test_random_value(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;

	for (i = 0; i < count; i++) {
		*p1++ = *p2++ = rand_ul();
	}

	return compare_regions(bufa, bufb, count);
}

int test_xor_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ ^= q;
		*p2++ ^= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_sub_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ -= q;
		*p2++ -= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_mul_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ *= q;
		*p2++ *= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_div_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		if (!q)
			q++;

		*p1++ /= q;
		*p2++ /= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_or_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ |= q;
		*p2++ |= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_and_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ &= q;
		*p2++ &= q;
	}

	return compare_regions(bufa, bufb, count);
}

int test_seqinc_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i;
	ull q;

	q = rand_ul();

	for (i = 0; i < count; i++)
		*p1++ = *p2++ = (i + q);

	return compare_regions(bufa, bufb, count);
}

int test_solidbits_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;
	ull q;

	for (j = 0; j < 64; j++) {
		q = (j % 2) == 0 ? UL_ONEBITS : 0;

		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;
		for (i = 0; i < count; i++)
			*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;

		if (compare_regions(bufa, bufb, count))
			return -1;
	}
	return 0;
}

int test_checkerboard_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;
	ull q;

	for (j = 0; j < 64; j++) {
		q = (j % 2) == 0 ? CHECKERBOARD1 : CHECKERBOARD2;

		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;

		for (i = 0; i < count; i++)
			*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;

		if (compare_regions(bufa, bufb, count))
			return -1;
	}

	return 0;
}

int test_blockseq_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;

	for (j = 0; j < 256; j++) {
		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;

		for (i = 0; i < count; i++)
			*p1++ = *p2++ = (ull)UL_BYTE(j);

		if (compare_regions(bufa, bufb, count))
			return -1;
	}
	return 0;
}

int test_walkbits0_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;

	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;
		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = ONE << j;
			} else { /* Walk it back down. */
				*p1++ = *p2++ = ONE << (UL_LEN * 2 - j - 1);
			}
		}

		if (compare_regions(bufa, bufb, count))
			return -1;
	}
	return 0;
}

int test_walkbits1_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;

	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;

		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = UL_ONEBITS ^ (ONE << j);
			} else { /* Walk it back down. */
				*p1++ = *p2++ = UL_ONEBITS ^ (ONE << (UL_LEN * 2 - j - 1));
			}
		}

		if (compare_regions(bufa, bufb, count))
			return -1;
	}
	return 0;
}

int test_bitspread_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j;

	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ullv *)bufa;
		p2 = (ullv *)bufb;

		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = (i % 2 == 0)
								? (ONE << j) | (ONE << (j + 2))
								: UL_ONEBITS ^ ((ONE << j)
												| (ONE << (j + 2)));
			} else { /* Walk it back down. */
				*p1++ = *p2++ = (i % 2 == 0)
								? (ONE << (UL_LEN * 2 - 1 - j)) | (ONE << (UL_LEN * 2 + 1 - j))
								: UL_ONEBITS ^ (ONE << (UL_LEN * 2 - 1 - j)
												| (ONE << (UL_LEN * 2 + 1 - j)));
			}
		}

		if (compare_regions(bufa, bufb, count))
			return -1;
	}
	return 0;
}

int test_bitflip_comparison(ullv *bufa, ullv *bufb, size_t count)
{
	ullv *p1 = bufa;
	ullv *p2 = bufb;
	unsigned int i, j, k;
	ull q;

	for (k = 0; k < UL_LEN; k++) {
		q = ONE << k;

		for (j = 0; j < 8; j++) {
			q = ~q;

			p1 = (ullv *)bufa;
			p2 = (ullv *)bufb;
			for (i = 0; i < count; i++)
				*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;

			if (compare_regions(bufa, bufb, count))
				return -1;
		}
	}
	return 0;
}

int test_8bit_wide_random(ullv *bufa, ullv *bufb, size_t count)
{
	u8v *p1, *t;
	ullv *p2;
	unsigned int i, b, attempt;
	mword8_t mword8;

	for (attempt = 0; attempt < 2;  attempt++) {
		if (attempt & 1) {
			p1 = (u8v *)bufa;
			p2 = bufb;
		} else {
			p1 = (u8v *)bufb;
			p2 = bufa;
		}
		for (i = 0; i < count; i++) {
			t = mword8.bytes;
			*p2++ = mword8.val = rand_ul();
			for (b = 0; b < UL_LEN / 8; b++)
				*p1++ = *t++;
		}

		if (compare_regions(bufa, bufb, count))
			return -1;

	}
	return 0;
}

int test_16bit_wide_random(ullv *bufa, ullv *bufb, size_t count)
{
	u16v *p1, *t;
	ullv *p2;
	unsigned int i, b, attempt;
	mword16_t mword16;

	for (attempt = 0; attempt < 2; attempt++) {
		if (attempt & 1) {
			p1 = (u16v *)bufa;
			p2 = bufb;
		} else {
			p1 = (u16v *)bufb;
			p2 = bufa;
		}
		for (i = 0; i < count; i++) {
			t = mword16.u16s;
			*p2++ = mword16.val = rand_ul();

			for (b = 0; b < UL_LEN / 16; b++)
				*p1++ = *t++;
		}

		if (compare_regions(bufa, bufb, count))
			return -1;
	}

	return 0;
}

// #define STUCK_TEST_BEFORE_MEMTEST

struct test_list memtest_list[] = {
	// { "All", NULL},
	{ "Stuck Address", test_stuck_address },
	{ "Random Value", test_random_value },
	{ "Compare XOR", test_xor_comparison },
	{ "Compare SUB", test_sub_comparison },
	{ "Compare MUL", test_mul_comparison },
	{ "Compare DIV", test_div_comparison },
	{ "Compare OR", test_or_comparison },
	{ "Compare AND", test_and_comparison },
	{ "Sequential Increment", test_seqinc_comparison },
	{ "Solid Bits", test_solidbits_comparison },
	{ "Block Sequential", test_blockseq_comparison },
	{ "Checkerboard", test_checkerboard_comparison },
	{ "Bit Spread", test_bitspread_comparison },
	{ "Bit Flip", test_bitflip_comparison },
	{ "Walking Ones", test_walkbits1_comparison },
	{ "Walking Zeroes", test_walkbits0_comparison },
	{ "8-bit Writes", test_8bit_wide_random },
	{ "16-bit Writes", test_16bit_wide_random },
};

int do_memtest(ullv addr, size_t size)
{
	ul loops, loop, i, mtlen;
	size_t count;
	ullv *bufa, *bufb;
	int ret = 0;

	count = size / sizeof(ull);
	bufa = (ullv *)addr;
	bufb = (ullv *)((size_t)addr + size);

	loops = 1;
	mtlen = (sizeof(memtest_list) / sizeof(struct test_list));

	for (loop = 1; ((!loops) || loop <= loops); loop++) {

		dprintf("0x%llx - Loop %lu \r\n", addr, loop);

		// if (loops)
			// dprintf("%lu \r\n", loops);

		#ifdef STUCK_TEST_BEFORE_MEMTEST
		if (test_stuck_address(bufa, bufb, count)) {
			ret |= EXIT_FAIL_ADDRESSLINES;
		}
		#endif // STUCK_TEST_BEFORE_MEMTEST
		printf("shkim test\n");

		for (i = 1; i < mtlen; i++) {
			//printf("shkim test222\n");

			dprintf("%s\n", memtest_list[i].name);
			if (memtest_list[i].fp(bufa, bufb, count)) {
				ret |= 0x1 << (i - 1);
			}
		}
	}

	return ret;
}
