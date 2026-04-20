/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <zephyr/arch/arm64/arm_mmu.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/util.h>

static const struct arm_mmu_region mmu_regions[] = {
	MMU_REGION_FLAT_ENTRY("GIC_DIST",
						  DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic_v3), 0),
						  DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic_v3), 0),
						  MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE),
	MMU_REGION_FLAT_ENTRY("GIC_RDIST",
						  DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic_v3), 1),
						  DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic_v3), 1),
						  MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE),
	MMU_REGION_FLAT_ENTRY("UART",
						  DT_REG_ADDR_BY_IDX(DT_INST(0, ns16550), 0),
						  DT_REG_SIZE_BY_IDX(DT_INST(0, ns16550), 0),
						  MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_DEFAULT_SECURE_STATE),
};

const struct arm_mmu_config mmu_config = {
	.num_regions = ARRAY_SIZE(mmu_regions),
	.mmu_regions = mmu_regions,
};
