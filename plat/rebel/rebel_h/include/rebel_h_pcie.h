/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REBEL_H_PCIE_H
#define REBEL_H_PCIE_H

#include <stdint.h>

#if USE_GPT
#define TBOOT_P0_SRC_ADDR		(0x1f80100000ULL)
#define TBOOT_P1_SRC_ADDR		(0x1f80140000ULL)

#define MUX_SWITCH				(0x404)
#define MUX_VALUE				(0x2)

#define MUX_CR_PARA_SEL			(0x644)
#define MUX_CR_PARA_SEL_SEPARATE	(0x1)
#define MUX_CR_PARA_SEL_BROADCAST	(0x0)

#define IMAGE_SIZE_FIELD	(0x10)
#endif /* USE_GPT */

void cm7_wait_phy_sram_init_done(uint32_t chiplet_id);
void cm7_notify_load_done(uint32_t chiplet_id);

#endif /* REBEL_H_PCIE_H */
