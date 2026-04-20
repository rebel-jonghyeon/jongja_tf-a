/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Thread entry
 *
 * This file provides the common thread entry function
 */

#include <stdlib.h>
#include <stdint.h>
#include <container.h>

#include <stdnoreturn.h> /* deprecated in C23 [[noreturn]] */
#define NORETURN noreturn
#define WEAK __attribute__((weak))
#define NAKED __attribute__((naked))
#define SECTION(X) __attribute__((section(X)))

void _start(void *, void *, void *);

static cmrt_container_t s_container_id;

cmrt_container_t cmrt_container_id(void)
{
	return s_container_id;
}

/* Arguments passed in are (0, 0, 0) to allow for all main() signatures
 * present in ported source.
 */
int main(int, char **argv, char **envp);
NORETURN void exit();
void container(void *, void *, void *);

typedef void (*constructor)(void);

extern constructor __constructors_begin;
extern constructor __constructors_end;

/*
 * Container entry point.  The parameter passed in are the _start
 * routine itself, the container's id, and an unused parameter
 * pass through.
 *
 * This routine does not return, and is marked as such so the compiler
 * won't generate preamble code that is only used by functions that
 * actually return.  The function is placed into a startup section to
 * allow locating it.
 */
NORETURN NAKED SECTION(".text.startup")
void _start(void *dummy, void *p1, void *p2)
{
	(void)dummy; /* this is _start address itself currently */
	s_container_id = (unsigned)(uintptr_t)p1; /* cache the ID */
	for (constructor *p = &__constructors_begin; p != &__constructors_end; ++p) {
		(*p)();
	}
	container(p1, p2, NULL);
	exit(0); /* fallback return should never happen */
}

/* Call container main function. */
WEAK NAKED void container(void *p1, void *p2, void *p3)
{
	(void)p1;
	(void)p2;
	(void)p3;
	exit(main(0, NULL, NULL));
}
