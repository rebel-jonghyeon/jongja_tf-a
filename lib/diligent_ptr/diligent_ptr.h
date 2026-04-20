#ifndef _DILIGENT_PTR_H
#define _DILIGENT_PTR_H
#include <stdio.h>

/* #define PTR_DEBUG_PRINT_ENALBE */
#ifdef PTR_DEBUG_PRINT_ENALBE
	#define PTR_DEBUG_PRINT(...)	(INSPECT_PRINT(__VA_ARGS__))
#else
	#define PTR_DEBUG_PRINT(...)
#endif /* PTR_DEBUG_PRINT_ENABLE */

#ifdef UNIT_TEST
	#include "unity.h"
#else
	#define TEST_FAIL() INSPECT_PRINT("Test Failed!!\n"); do {} while (1)
#endif /* UNIT_TEST */

#define INSPECT_PRINT(...)  (printf(__VA_ARGS__))
#define INSPECT_ARR_SIZE	(300)
#define NEED_TO_COMPARE	 (1)
#define NEED_NOT_TO_COMPARE (0)

#define PUSH_EXPECT_READ_AND_RETURN(target_ptr, val_ptr)			(target_ptr.push_expect_read_and_return(val_ptr))
#define PUSH_COMPARE_SNAPSHOT(target_ptr, val_ptr)						(target_ptr.push_compare_snapshot(val_ptr))
#define PUSH_EXPECT_WRITE(target_ptr, current_val_ptr, write_val_ptr)					\
						do {															\
							PUSH_EXPECT_READ_AND_RETURN(target_ptr, current_val_ptr);	\
							PUSH_COMPARE_SNAPSHOT(target_ptr, write_val_ptr);			\
							*current_val_ptr = *write_val_ptr;							\
						} while (0)
#define CLEAR_SNAPSHOT_ARR(target_ptr)									(target_ptr.clear_snapshot_arr())
#define VERIFY(target_ptr)												(target_ptr.verify())
#define PAUSE(target_ptr)												(target_ptr.pause())
#define RESUME(target_ptr)												(target_ptr.resume())

template < typename T_mmio_map >
struct diligent_ptr {
	/* The size of T_mmio_map must be aligned to 4 bytes */
	T_mmio_map *map;
	T_mmio_map expected_read_return_arr[INSPECT_ARR_SIZE];
	const int max_arr_idx;
	int cur_read_empty_idx;
	int cur_read_target_idx;

	int need_to_compare_flag[INSPECT_ARR_SIZE];
	T_mmio_map compare_snapshot_arr[INSPECT_ARR_SIZE];
	int cur_compare_empty_idx;
	int cur_compare_target_idx;

	bool is_paused;

	diligent_ptr()
		: map(nullptr), cur_read_empty_idx(0), cur_read_target_idx(0), max_arr_idx(INSPECT_ARR_SIZE),
			cur_compare_empty_idx(0), cur_compare_target_idx(0), is_paused(0) {
			clear_snapshot_arr();
		}

	T_mmio_map *operator = (T_mmio_map *target_map) {
		map = target_map;
		return map;
	};

	T_mmio_map *operator = (const struct diligent_ptr < T_mmio_map > &ptr) {
		map = ptr.map;
		return map;
	};

	bool operator == (const void *ptr) {
		return map == ptr;
	};

	T_mmio_map *operator->() {
		if (is_paused) {
			return map;
		}

		if (cur_read_empty_idx >= max_arr_idx) {
			INSPECT_PRINT("\nsnapshot array already full!!\n");
			TEST_FAIL();
		} else if (cur_read_target_idx >= cur_read_empty_idx) {
			INSPECT_PRINT("\nIt was accessed more than expected.\n");
			INSPECT_PRINT("expected:%d actual:%d\n", cur_read_empty_idx, cur_read_target_idx + 1);
			TEST_FAIL();
		} else if (need_to_compare_flag[cur_read_target_idx] == NEED_TO_COMPARE) {
			/* Reading is bound to be ahead of compare. */
			compare_with_expected(cur_compare_target_idx);
			cur_compare_target_idx++;
		}

		PTR_DEBUG_PRINT("[return idx %d] returned\n", cur_read_target_idx);

		*map = expected_read_return_arr[cur_read_target_idx++];
		return map;
	};

void pause(void)
{
	is_paused = 1;
};

void resume(void)
{
	is_paused = 0;
};

void clear_snapshot_arr(void)
{
	for (int idx = 0; idx < INSPECT_ARR_SIZE; ++idx) {
		expected_read_return_arr[idx] = {};
		compare_snapshot_arr[idx] = {};
		need_to_compare_flag[idx] = NEED_NOT_TO_COMPARE;
	}
	cur_read_empty_idx = 0;
	cur_read_target_idx = 0;
	cur_compare_empty_idx = 0;
	cur_compare_target_idx = 0;
};

void push_expect_read_and_return(T_mmio_map *return_map)
{
	expected_read_return_arr[cur_read_empty_idx] = *return_map;
	cur_read_empty_idx++;
};

void push_compare_snapshot(T_mmio_map *compare_map)
{
	compare_snapshot_arr[cur_compare_empty_idx] = *compare_map;
	if (need_to_compare_flag[cur_read_empty_idx] == NEED_TO_COMPARE) {
		INSPECT_PRINT("[%d] It's already filled up!\n", cur_read_empty_idx);
		TEST_FAIL();
	}
	need_to_compare_flag[cur_read_empty_idx] = NEED_TO_COMPARE;
	cur_compare_empty_idx++;
};

int compare_with_expected(int target_idx)
{
	unsigned char *real_buf = (unsigned char *)map;
	unsigned char *exp_buf = (unsigned char *)&compare_snapshot_arr[target_idx];

	for (size_t buf_i = 0; buf_i < sizeof(T_mmio_map); ++buf_i) {
		if (exp_buf[buf_i] != real_buf[buf_i]) {
			INSPECT_PRINT("\n[compare idx %d] not equal!!\n", target_idx);
			INSPECT_PRINT("[expected]");
			print_4bytes_map(&compare_snapshot_arr[target_idx], buf_i);
			INSPECT_PRINT("[actual]");
			print_4bytes_map(map, buf_i);
			TEST_FAIL();
		}
	}

	return 0;
};

void verify(void)
{
	if (cur_read_empty_idx > cur_read_target_idx) {
		INSPECT_PRINT("\nIt was accessed less than expected.\n");
		INSPECT_PRINT("expected:%d actual:%d\n", cur_read_empty_idx, cur_read_target_idx);
		TEST_FAIL();
	} else if (cur_read_empty_idx < cur_read_target_idx) {
		/* both values must be equal */
		TEST_FAIL();
	} else if (need_to_compare_flag[cur_read_target_idx] == NEED_TO_COMPARE) {
		/* Reading is bound to be ahead of compare. */
		compare_with_expected(cur_compare_target_idx);
		cur_compare_target_idx++;
	}
	if (cur_compare_target_idx != cur_compare_empty_idx) {
		INSPECT_PRINT("\nIt was compareded less than expected.\n");
		INSPECT_PRINT("expected:%d actual:%d\n", cur_compare_empty_idx, cur_compare_target_idx);
		TEST_FAIL();
	}

	PTR_DEBUG_PRINT("\nrd_empty_idx %d\nrd_target_idx %d\ncmp_empty_idx %d\ncmp_target_idx %d\n",
					cur_read_empty_idx, cur_read_target_idx, cur_compare_empty_idx, cur_compare_target_idx);
	PTR_DEBUG_PRINT("\nIt was accessed as expected.\n");
};

void print_4bytes_map(T_mmio_map *target_map, int offset)
{
	unsigned char *buf = (unsigned char *)target_map;

	if (offset % 4 != 0) {
		offset -= offset % 4;
	}
	INSPECT_PRINT("\n0x%08x:", offset);
	INSPECT_PRINT(" 0x%02x%02x_%02x%02x\n",
				  buf[offset + 3], buf[offset + 2], buf[offset + 1], buf[offset]);
};

void print_part_map(T_mmio_map *target_map, int offset, int end)
{
	unsigned char *buf = (unsigned char *)target_map;

	if (offset % 32 != 0) {
		INSPECT_PRINT("\n0x%08x:", offset);
		for (int idx = offset; idx % 32 != 0; ++idx) {
			INSPECT_PRINT(" 0x%02x%02x_%02x%02x",
						  buf[idx + 3], buf[idx + 2], buf[idx + 1], buf[idx]);
		}
	}
	for (int idx = offset; idx < end; idx += 4) {
		if (idx % 32 == 0) {
			INSPECT_PRINT("\n0x%08x:", idx);
		}
		INSPECT_PRINT(" 0x%02x%02x_%02x%02x",
					  buf[idx + 3], buf[idx + 2], buf[idx + 1], buf[idx]);
	}
	INSPECT_PRINT("\n");
};

void print_whole_map(T_mmio_map *target_map)
{
	print_part_map(target_map, 0, sizeof(T_mmio_map));
};

};
#endif /* _DILIGENT_PTR_H */
