/*
 * Copyright (c) 2020 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief RISCV specific syscall header
 *
 * This header contains the RISCV specific syscall interface.  It is
 * included by the syscall interface architecture-abstraction header
 * (include/arch/syscall.h)
 */

#ifndef CMRT_SYSCALL_H
#define CMRT_SYSCALL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Syscall invocation macros. riscv-specific machine constraints used to ensure
 * args land in the proper registers.
 */
static inline uintptr_t arch_syscall_invoke6(uintptr_t arg1, uintptr_t arg2,
					     uintptr_t arg3, uintptr_t arg4,
					     uintptr_t arg5, uintptr_t arg6,
					     uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
	register uint32_t a1 __asm__ ("a1") = arg2;
	register uint32_t a2 __asm__ ("a2") = arg3;
	register uint32_t a3 __asm__ ("a3") = arg4;
	register uint32_t a4 __asm__ ("a4") = arg5;
	register uint32_t a5 __asm__ ("a5") = arg6;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif
	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a1), "r" (a2), "r" (a3), "r" (a4), "r" (a5),
			  "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke5(uintptr_t arg1, uintptr_t arg2,
					     uintptr_t arg3, uintptr_t arg4,
					     uintptr_t arg5,
					     uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
	register uint32_t a1 __asm__ ("a1") = arg2;
	register uint32_t a2 __asm__ ("a2") = arg3;
	register uint32_t a3 __asm__ ("a3") = arg4;
	register uint32_t a4 __asm__ ("a4") = arg5;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a1), "r" (a2), "r" (a3), "r" (a4), "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke4(uintptr_t arg1, uintptr_t arg2,
					     uintptr_t arg3, uintptr_t arg4,
					     uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
	register uint32_t a1 __asm__ ("a1") = arg2;
	register uint32_t a2 __asm__ ("a2") = arg3;
	register uint32_t a3 __asm__ ("a3") = arg4;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a1), "r" (a2), "r" (a3), "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke3(uintptr_t arg1, uintptr_t arg2,
					     uintptr_t arg3,
					     uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
	register uint32_t a1 __asm__ ("a1") = arg2;
	register uint32_t a2 __asm__ ("a2") = arg3;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a1), "r" (a2), "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke2(uintptr_t arg1, uintptr_t arg2,
					     uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
	register uint32_t a1 __asm__ ("a1") = arg2;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a1), "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke1(uintptr_t arg1, uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0") = arg1;
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a7)
			  : "memory");
	return a0;
}

static inline uintptr_t arch_syscall_invoke0(uintptr_t call_id)
{
	register uint32_t a0 __asm__ ("a0");
#ifdef CONFIG_EMBEDDED_ISA
	register uint32_t a7 __asm__ ("t0") = call_id;
#else
	register uint32_t a7 __asm__ ("a7") = call_id;
#endif

	__asm__ volatile ("ecall"
			  : "+r" (a0)
			  : "r" (a7)
			  : "memory");
	return a0;
}

#ifdef __cplusplus
}
#endif

#endif
