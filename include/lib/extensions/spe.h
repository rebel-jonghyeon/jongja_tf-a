/*
<<<<<<< HEAD
 * Copyright (c) 2017-2023, Arm Limited and Contributors. All rights reserved.
=======
 * Copyright (c) 2017-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPE_H
#define SPE_H

#include <stdbool.h>
#include <context.h>

#if ENABLE_SPE_FOR_NS
<<<<<<< HEAD
void spe_init_el3(void);
void spe_init_el2_unused(void);
void spe_disable(void);
#else
static inline void spe_init_el3(void)
{
}
static inline void spe_init_el2_unused(void)
=======
void spe_enable_ns(cpu_context_t *ctx);
void spe_disable_secure(cpu_context_t *ctx);
void spe_disable_realm(cpu_context_t *ctx);
void spe_init_el2_unused(void);
#else
static inline void spe_enable_ns(cpu_context_t *ctx)
>>>>>>> upstream_import/upstream_v2_14_1
{
}
static inline void spe_disable_secure(cpu_context_t *ctx)
{
}
<<<<<<< HEAD
=======
static inline void spe_disable_realm(cpu_context_t *ctx)
{
}
static inline void spe_init_el2_unused(void)
{
}
>>>>>>> upstream_import/upstream_v2_14_1
#endif /* ENABLE_SPE_FOR_NS */

#endif /* SPE_H */
