/*
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <drivers/cmrt/util.h>


FUNC_NORETURN void _exit(int status)
{
	cmrt_exit_container(status);

	/*
	 * Compiler can't tell that cmrt_exit_container() won't return
	 * and issues a warning unless we tell it that control never
	 * gets this far.
	 */

	CODE_UNREACHABLE; /* LCOV_EXCL_LINE */
}
