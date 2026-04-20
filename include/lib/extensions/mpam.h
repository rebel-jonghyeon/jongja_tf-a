/*
<<<<<<< HEAD
 * Copyright (c) 2018-2023, Arm Limited and Contributors. All rights reserved.
=======
 * Copyright (c) 2018-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MPAM_H
#define MPAM_H

#include <stdbool.h>

#include <context.h>

#if ENABLE_FEAT_MPAM
<<<<<<< HEAD
void mpam_enable(cpu_context_t *context);
void mpam_init_el2_unused(void);
#else
static inline void mpam_enable(cpu_context_t *context)
=======
void mpam_enable_per_world(per_world_context_t *per_world_ctx);
void mpam_init_el2_unused(void);
void mpam_init_el3(void);
#else
static inline void mpam_enable_per_world(per_world_context_t *per_world_ctx)
>>>>>>> upstream_import/upstream_v2_14_1
{
}
static inline void mpam_init_el2_unused(void)
{
}
<<<<<<< HEAD
=======
static inline void mpam_init_el3(void)
{
}
>>>>>>> upstream_import/upstream_v2_14_1
#endif /* ENABLE_FEAT_MPAM */

#endif /* MPAM_H */
