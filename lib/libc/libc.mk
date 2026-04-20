#
<<<<<<< HEAD
# Copyright (c) 2016-2021, Arm Limited and Contributors. All rights reserved.
=======
# Copyright (c) 2016-2024, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
#
# SPDX-License-Identifier: BSD-3-Clause
#
#

<<<<<<< HEAD
LIBC_SRCS	:=	$(addprefix lib/libc/,		\
			abort.c				\
			assert.c			\
			exit.c				\
			memchr.c			\
			memcmp.c			\
			memcpy.c			\
			memcpy_s.c			\
			memmove.c			\
			memrchr.c			\
			memset.c			\
			printf.c			\
			putchar.c			\
			puts.c				\
			snprintf.c			\
			strchr.c			\
			strcmp.c			\
			strlcat.c			\
			strlcpy.c			\
			strlen.c			\
			strncmp.c			\
			strnlen.c			\
			strrchr.c			\
			strtok.c			\
			strtoul.c			\
			strtoll.c			\
			strtoull.c			\
			strtol.c)
=======
include lib/libc/libc_common.mk
>>>>>>> upstream_import/upstream_v2_14_1

LIBC_SRCS	+=	$(addprefix lib/libc/,		\
			memset.c)
