/*
<<<<<<< HEAD
 * Copyright (c) 2013-2019, Arm Limited and Contributors. All rights reserved.
=======
 * Copyright (c) 2013-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stddef.h>
#include <string_private.h>

void *memchr(const void *src, int c, size_t len)
{
	const unsigned char *s = src;

	while (len--) {
		if (*s == (unsigned char)c)
			return (void *) s;
		s++;
	}

	return NULL;
}
