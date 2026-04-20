/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <platform_def.h>
#include <lib/mmio.h>
#include <rebel_h_pcie.h>
#include <common/debug.h>

#define SFR_PHY_CFG_0_REG       (0x20ec)
#define SFR_PHY_CFG_102_REG     (0x1138)
#define SFR_PHY_CFG_103_REG     (0x113c)
#define SFR_PHY_CFG_104_REG     (0x1140)
#define PHY_SRAM_EXT_LD_DONE    (0x20)

#define WAIT_SRAM_INIT_DONE(addr)                               \
	do {                                                        \
		;                                                       \
	} while (!(mmio_read_32(addr) & 0x1))

#define PHY0_SRAM_INIT_DONE (0x215c)
#define PHY1_SRAM_INIT_DONE (0x112c)
#define PHY2_SRAM_INIT_DONE (0x1130)
#define PHY3_SRAM_INIT_DONE (0x1134)

/* TODO: support the same functions for a chiplet-3 used case at EVT1 */
void cm7_wait_phy_sram_init_done(uint32_t chiplet_id)
{
	if (chiplet_id == CHIPLET_ID0) {
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + PHY0_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + PHY1_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + PHY2_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + PHY3_SRAM_INIT_DONE);
	} else if (chiplet_id == CHIPLET_ID3) {
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + PHY0_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + PHY1_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + PHY2_SRAM_INIT_DONE);
		WAIT_SRAM_INIT_DONE(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + PHY3_SRAM_INIT_DONE);
	}
}

void cm7_notify_load_done(uint32_t chiplet_id)
{
	if (chiplet_id == CHIPLET_ID0 || chiplet_id == CHIPLET_ID3) {
		uint32_t val;

		val = mmio_read_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_0_REG);
		mmio_write_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_0_REG,
					  val | PHY_SRAM_EXT_LD_DONE);

		val = mmio_read_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_102_REG);
		mmio_write_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_102_REG,
					  val | PHY_SRAM_EXT_LD_DONE);

		val = mmio_read_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_103_REG);
		mmio_write_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_103_REG,
					  val | PHY_SRAM_EXT_LD_DONE);

		val = mmio_read_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_104_REG);
		mmio_write_32(PCIE_SUB_CTRL_INST + CHIPLET_OFFSET * chiplet_id + SFR_PHY_CFG_104_REG,
					  val | PHY_SRAM_EXT_LD_DONE);
	}
}
