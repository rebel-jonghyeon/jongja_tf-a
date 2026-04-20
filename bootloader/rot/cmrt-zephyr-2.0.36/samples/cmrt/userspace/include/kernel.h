/*
 * Copyright (c) 2016, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef ZEPHYR_INCLUDE_KERNEL_H_
#define ZEPHYR_INCLUDE_KERNEL_H_

#include <sys/util.h>
#include <sys/__assert.h>

/* toolchain/common.h */

#define __syscall static inline


/* sys_clock.h */

/* number of nsec per usec */
#define NSEC_PER_USEC 1000U

/* number of microseconds per millisecond */
#define USEC_PER_MSEC 1000U

/* number of milliseconds per second */
#define MSEC_PER_SEC 1000U

/* number of microseconds per second */
#define USEC_PER_SEC ((USEC_PER_MSEC) * (MSEC_PER_SEC))

/* number of nanoseconds per second */
#define NSEC_PER_SEC ((NSEC_PER_USEC) * (USEC_PER_MSEC) * (MSEC_PER_SEC))


/* kernel/thread.h */

typedef void *k_tid_t;


/* sys/arch_interface.h */

typedef void (*k_thread_entry_t)(void *p1, void *p2, void *p3);


/* kernel/include/kernel_internal.h */

extern FUNC_NORETURN void z_thread_entry(k_thread_entry_t entry,
					 void *p1, void *p2, void *p3);

#endif
