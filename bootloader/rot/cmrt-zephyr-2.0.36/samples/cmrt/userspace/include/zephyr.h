/*
 * Copyright (c) 2016, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_KERNEL_H_
#define ZEPHYR_INCLUDE_KERNEL_H_

/* fatal.h */

enum k_fatal_error_reason {
        /** Generic CPU exception, not covered by other codes */
        K_ERR_CPU_EXCEPTION,

        /** Unhandled hardware interrupt */
        K_ERR_SPURIOUS_IRQ,

        /** Faulting context overflowed its stack buffer */
        K_ERR_STACK_CHK_FAIL,

        /** Moderate severity software error */
        K_ERR_KERNEL_OOPS,

        /** High severity software error */
        K_ERR_KERNEL_PANIC

        /* TODO: add more codes for exception types that are common across
         * architectures
         */
};

/* zephyr.h */

#include <syscall.h>
#include <syscall_list.h>
#include <toolchain.h>

#define k_oops() arch_syscall_invoke1(K_ERR_KERNEL_OOPS, C_SYSCALL_BASE + C_SYSCALL_USER_FAULT)

#endif
