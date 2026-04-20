/*
 * Copyright (c) 2024 Samsung Electronics Co, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "../../../../../../common/rebel_h_sic.h"

#define ACTIVE_PART_ONE				(0x006F6E65)
#define ACTIVE_PART_TWO				(0x0074776F)

#define IS_PHY_SRAM_LOAD			(0x29272523)

#define RECOVERY_FLAG_NORMAL		(0)
#define RECOVERY_FLAG_BOOT_FAIL		(1)
#define RECOVERY_FLAG_FW_UPDATE		(2)

#define RECOVERY_REASON_BOOT_FAIL	(1)
#define RECOVERY_REASON_FW_UPDATE	(2)

typedef int (*func_ptr)(uint32_t offset, uint32_t *data, uint32_t data_size);
#define GPT1_START_ADDRESS			(0x1F80080000ULL)
#define GPT2_START_ADDRESS			(0x1F80880000ULL)
#define GPT_SIZE					(0x780000)

#define GPT_IMAGE_HEADER_ADDR		(0x1F8007C000ULL)

uint64_t get_image_offset(uint32_t type, uint64_t gpt_base);
uint64_t get_image_address(uint32_t type, uint64_t gpt_base);
uint32_t get_active_partition(void);
uint64_t get_active_partition_base(void);
uint32_t get_is_pcie_phy_sram_load(void);
void handling_img_error(func_ptr write_flash);
uint32_t get_recovery_flag(void);
void set_active_partition(uint32_t active, func_ptr write_flash);
void set_recovery_flag(uint32_t flag, func_ptr write_flash);
void set_recovery_reason(uint32_t recovery_reason, func_ptr write_flash);
void gpt_init(void);
