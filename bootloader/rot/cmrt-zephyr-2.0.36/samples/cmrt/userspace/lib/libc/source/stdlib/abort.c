/*
 * Copyright (c) 2020 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <zephyr.h>

FUNC_NORETURN void abort(void)
{
	(void)k_oops();
	CODE_UNREACHABLE;
}
