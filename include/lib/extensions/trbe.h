/*
 * Copyright (c) 2021-2025, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TRBE_H
#define TRBE_H

#include <context.h>

#if ENABLE_TRBE_FOR_NS
<<<<<<< HEAD
void trbe_init_el3(void);
void trbe_init_el2_unused(void);
#else
static inline void trbe_init_el3(void)
=======
void trbe_enable_ns(cpu_context_t *ctx);
void trbe_disable_ns(cpu_context_t *ctx);
void trbe_disable_secure(cpu_context_t *ctx);
void trbe_disable_realm(cpu_context_t *ctx);
void trbe_init_el2_unused(void);
#else
static inline void trbe_enable_ns(cpu_context_t *ctx)
{
}
static inline void trbe_disable_ns(cpu_context_t *ctx)
{
}
static inline void trbe_disable_secure(cpu_context_t *ctx)
{
}
static inline void trbe_disable_realm(cpu_context_t *ctx)
>>>>>>> upstream_import/upstream_v2_14_1
{
}
static inline void trbe_init_el2_unused(void)
{
}
#endif /* ENABLE_TRBE_FOR_NS */

#endif /* TRBE_H */
