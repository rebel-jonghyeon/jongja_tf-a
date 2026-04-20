/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REBEL_H_PLAT_H
#define REBEL_H_PLAT_H

#include <stdint.h>

uint32_t plat_get_secondary_chiplet_cnt(void);
void plat_set_secondary_chiplet_cnt(uint32_t chiplet, uint32_t cnt);

void plat_set_cpu_rvbar(uint32_t chiplet, uint32_t cluster, uint32_t cpu, uint64_t ep);

void plat_pmu_cpu_on(uint32_t chiplet, uint32_t cluster, uint32_t cpu);
void plat_pmu_cpu_off(uint32_t chiplet, uint32_t cluster, uint32_t cpu);

void plat_pmu_cl_on(uint32_t chiplet, uint32_t cluster);

void plat_pmu_reset_rot(uint32_t chiplet);

#endif /* REBEL_H_PLAT_H */
