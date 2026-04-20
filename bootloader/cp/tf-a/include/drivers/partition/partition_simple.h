/*
 * Copyright (c) 2016-2023, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PARTITION_H
#define PARTITION_H

#include <stdint.h>

#include <lib/cassert.h>
#include <drivers/partition/efi.h>
#include <tools_share/uuid.h>

#define PLAT_PARTITION_MAX_ENTRIES	10

#if !PLAT_PARTITION_MAX_ENTRIES
# define PLAT_PARTITION_MAX_ENTRIES	128
#endif	/* PLAT_PARTITION_MAX_ENTRIES */

CASSERT(PLAT_PARTITION_MAX_ENTRIES <= 128, assert_plat_partition_max_entries);

#if !PLAT_PARTITION_BLOCK_SIZE
# define PLAT_PARTITION_BLOCK_SIZE	512
#endif /* PLAT_PARTITION_BLOCK_SIZE */

CASSERT(PLAT_PARTITION_BLOCK_SIZE == 512 ||
		PLAT_PARTITION_BLOCK_SIZE == 4096,
		assert_plat_partition_block_size);

#define LEGACY_PARTITION_BLOCK_SIZE	512

#define LBA(n) ((unsigned long long)(n) * PLAT_PARTITION_BLOCK_SIZE)

#define GPT_ENTITY_INDEX_SBOOT_N		0
#define GPT_ENTITY_INDEX_TBOOT_S		1
#define GPT_ENTITY_INDEX_TBOOT_N		2
#define GPT_ENTITY_INDEX_TBOOT_P0		3
#define GPT_ENTITY_INDEX_TBOOT_P1		4
#define GPT_ENTITY_INDEX_UCIE			5
#define GPT_ENTITY_INDEX_BL31			6
#define GPT_ENTITY_INDEX_FREERTOS		7
#define GPT_ENTITY_INDEX_BL31_CP1		8
#define GPT_ENTITY_INDEX_FREERTOS_CP1		9

#define GPT_NOK							-1
#define GPT_OK							0

#define GPT_HEADER_FIELD_SIZE			16ULL

#define USE_GPT1			1
#define USE_GPT2			2

#define ACTIVE_PART_ONE		(0x006f6e65)
#define ACTIVE_PART_TWO		(0x0074776f)

#define RECOVERY_FLAG_NORMAL		(0)
#define RECOVERY_FLAG_BOOT_FAIL		(1)
#define RECOVERY_FLAG_FW_UPDATE		(2)

#define EFI_PART_HEX_UPPER			0x54524150
#define EFI_PART_HEX_LOWER			0x20494645

#define MBR_FIRST_LBA				(1)

typedef struct partition_entry {
	uint64_t		start;
	uint64_t		length;
	char			name[EFI_NAMELEN];
	struct efi_guid		part_guid;
	struct efi_guid		type_guid;
} partition_entry_t;

typedef struct partition_entry_list {
	partition_entry_t	list[PLAT_PARTITION_MAX_ENTRIES];
	int			entry_count;
} partition_entry_list_t;

typedef struct flash_image_header {
	uint32_t magic;
	uint32_t active_partition;
	uint32_t partition1_offset;
	uint32_t partition2_offset;
	uint32_t recovery_flag;
	uint32_t is_pcie_phy_sram_load;
	uint32_t recovery_reason;
} flash_image_header_t;

uint32_t gpt_partition_init(void);
uint64_t gpt_get_address_by_entry(uint32_t entry_num);
uint64_t gpt_get_length_by_entry(uint32_t entry_num);

#endif /* PARTITION_H */
