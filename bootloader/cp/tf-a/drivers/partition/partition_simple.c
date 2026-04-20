/*
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <common/tf_crc32.h>
#include <drivers/partition/efi.h>
#include <drivers/partition/partition_simple.h>
#include <drivers/partition/gpt.h>
#include <drivers/partition/mbr.h>
#include <common/debug.h>
#include <platform_def.h>

#define GPT1_MBR_ADDR		(XIP_FLASH_GPT_BASE_ADDR)
#define GPT2_MBR_ADDR		(XIP_FLASH_GPT2_BASE_ADDR)
#define GPT_FLASH_IMAGE_HEADER_ADDR	(XIP_FLASH_IMAGE_HEADER_ADDR)

uint8_t mbr_sector[PLAT_PARTITION_BLOCK_SIZE];
partition_entry_list_t list;
uint64_t binary_size[PLAT_PARTITION_MAX_ENTRIES];
uint64_t gpt_image_addr;
static flash_image_header_t image_header;

void *gpt_32bit_memcpy(void *dst, const void *src, size_t len_t)
{
	const uint32_t *s = src;
	uint32_t *d = dst;
	uint32_t len;

	len = len_t >> 2;

	while (len--)
		*d++ = *s++;

	return dst;
}

void gpt_get_image_header(void)
{
	gpt_32bit_memcpy((void *)&image_header, (void *)GPT_FLASH_IMAGE_HEADER_ADDR,
					 sizeof(flash_image_header_t));
}

uint32_t gpt_get_recovery_flag(void)
{
	return image_header.recovery_flag;
}

uint32_t gpt_get_active_partition(void)
{
	return image_header.active_partition;
}

void gpt_set_gpt_image_addr(uint32_t gpt_number)
{
	if (gpt_number == ACTIVE_PART_ONE)
		gpt_image_addr = GPT1_MBR_ADDR;
	else
		gpt_image_addr = GPT2_MBR_ADDR;
}

int load_gpt_entry(gpt_entry_t *entry, unsigned long long gpt_entry_offset)
{
	gpt_32bit_memcpy(entry, (void *)(gpt_image_addr + gpt_entry_offset), sizeof(gpt_entry_t));

	return GPT_OK;
}

int load_partition_gpt(unsigned long long part_lba)
{
	unsigned long long gpt_entry_offset = LBA(part_lba);
	gpt_entry_t entry;
	int result, i;

	for (i = 0; i < PLAT_PARTITION_MAX_ENTRIES; i++) {
		result = load_gpt_entry(&entry, gpt_entry_offset + (i * sizeof(gpt_entry_t)));

		if (result != GPT_OK) {
			NOTICE("GPT - Failed - load_gpt_entry\n");
			return result;
		}

		result = parse_gpt_entry(&entry, &list.list[i]);

		if (result != GPT_OK) {
			NOTICE("GPT - Failed - parse_gpt_entry\n");
			break;
		}
	}
	if (i == 0) {
		NOTICE("GPT - No Valid GPT Entries found\n");
		return GPT_NOK;
	}

	/*
	 * Only records the valid partition number that is loaded from
	 * partition table.
	 */
	list.entry_count = i;

	return GPT_OK;
}

int load_gpt_header(size_t header_offset, unsigned long long *part_lba)
{
	gpt_header_t header;
	uint32_t header_crc, calc_crc;
	uint32_t *sig = (uint32_t *)header.signature;

	gpt_32bit_memcpy(&header, (void *)(gpt_image_addr + (uint64_t)header_offset),
					 sizeof(gpt_header_t));

	if (*sig != EFI_PART_HEX_LOWER || *(sig + 0x1) != EFI_PART_HEX_UPPER)
		return GPT_NOK;

	/*
	 * UEFI Spec 2.8 March 2019 Page 119: HeaderCRC32 value is
	 * computed by setting this field to 0, and computing the
	 * 32-bit CRC for HeaderSize bytes.
	 */
	header_crc = header.header_crc;
	header.header_crc = 0U;

	calc_crc = tf_crc32(0U, (uint8_t *)&header, sizeof(gpt_header_t));
	if (header_crc != calc_crc) {
		return GPT_NOK;
	}

	header.header_crc = header_crc;

	/* partition numbers can't exceed PLAT_PARTITION_MAX_ENTRIES */
	list.entry_count = header.list_num;
	if (list.entry_count > PLAT_PARTITION_MAX_ENTRIES) {
		list.entry_count = PLAT_PARTITION_MAX_ENTRIES;
	}

	*part_lba = header.part_lba;
	return GPT_OK;
}

int load_primary_gpt(unsigned int first_lba)
{
	int result;
	unsigned long long part_lba;
	size_t gpt_header_offset;

	/* Try to load Primary GPT header from LBA1 */
	gpt_header_offset = LBA(first_lba);
	result = load_gpt_header(gpt_header_offset, &part_lba);
	if (result != GPT_OK || part_lba == 0) {
		NOTICE("GPT - Failed to retrieve Primary GPT header\n");
		return GPT_NOK;
	}

	result = load_partition_gpt(part_lba);

	return result;

}

int load_mbr_header(mbr_entry_t *mbr_entry)
{
	mbr_entry_t *tmp;

	/* MBR partition table is in LBA0. */
	gpt_32bit_memcpy(mbr_sector, (void *)gpt_image_addr, PLAT_PARTITION_BLOCK_SIZE);

	/* Check MBR boot signature. */
	if (mbr_sector[LEGACY_PARTITION_BLOCK_SIZE - 2] != MBR_SIGNATURE_FIRST ||
	    mbr_sector[LEGACY_PARTITION_BLOCK_SIZE - 1] != MBR_SIGNATURE_SECOND) {
		NOTICE("GPT - MBR boot signature failure\n");
		return GPT_NOK;
	}

	tmp = (mbr_entry_t *)(&mbr_sector[MBR_PRIMARY_ENTRY_OFFSET]);

	if (tmp->first_lba != 1) {
		NOTICE("GPT - MBR header may have an invalid first LBA\n");
		return GPT_NOK;
	}

	if (tmp->sector_nums == 0 || tmp->sector_nums == UINT32_MAX) {
		NOTICE("GPT - MBR header entry has an invalid number of sectors\n");
		return GPT_NOK;
	}

	mbr_entry->type = tmp->type;
	mbr_entry->first_lba = tmp->first_lba;

	return GPT_OK;
}

int load_partition_table(void)
{
	mbr_entry_t mbr_entry;
	int result;

	result = load_mbr_header(&mbr_entry);

	if (result != GPT_OK) {
		NOTICE("GPT - MBR - Failed to access image id=%d\n", result);
		return result;
	}

	if (mbr_entry.type == PARTITION_TYPE_GPT) {
		result = load_primary_gpt(mbr_entry.first_lba);

		if (result != GPT_OK) {
			NOTICE("GPT - Failed load_primary_gpt - result=%d\n", result);
			/* todo */
			/* return load_backup_gpt(BKUP_GPT_IMAGE_ID, mbr_entry.sector_nums); */
			return result;
		}
	} else {
		/* todo */
		/* result = load_mbr_entries(image_handle); */
		return GPT_NOK;
	}

	return result;
}

void gpt_load_binary_length(void)
{
	for (int i = 0; i < PLAT_PARTITION_MAX_ENTRIES; i++) {
		binary_size[i] = *(uint32_t *)(gpt_image_addr + list.list[i].start);
		/* NOTICE("GPT - binary_size[%d] = %ld\n", i, binary_size[i]); */
	}
}

uint64_t gpt_get_address_by_entry(uint32_t entry_num)
{
	return (gpt_image_addr + list.list[entry_num].start + GPT_HEADER_FIELD_SIZE);
}

uint64_t gpt_get_length_by_entry(uint32_t entry_num)
{
	return binary_size[entry_num];
}

/* gpt_load_binary() is an unused function but for other's information, didn't delete it */
uint32_t gpt_load_binary(uint32_t gpt_image_id)
{
#ifdef GPT_USE_DMA
	/* to do */
#else
	uint64_t dest_addr[6];
	uint32_t num_of_dest, i;

	num_of_dest = 1;

	/* use memcpy */
	if (gpt_image_id == GPT_ENTITY_INDEX_SBOOT_N) {
		dest_addr[0] = GPT_DEST_ADDR_SBOOT_N;
	} else if (gpt_image_id == GPT_ENTITY_INDEX_TBOOT_S) {
		dest_addr[0] = GPT_DEST_ADDR_TBOOT_S;
	} else if (gpt_image_id == GPT_ENTITY_INDEX_TBOOT_N) {
		dest_addr[0] = GPT_DEST_ADDR_TBOOT_N;
	} else if (gpt_image_id == GPT_ENTITY_INDEX_TBOOT_P0) {
		dest_addr[0] = GPT_DEST_ADDR_TBOOT_P0;
	} else if (gpt_image_id == GPT_ENTITY_INDEX_TBOOT_P1) {
		num_of_dest = 4;
		dest_addr[0] = GPT_DEST_ADDR_TBOOT_P1_PHY0;
		dest_addr[1] = GPT_DEST_ADDR_TBOOT_P1_PHY1;
		dest_addr[2] = GPT_DEST_ADDR_TBOOT_P1_PHY2;
		dest_addr[3] = GPT_DEST_ADDR_TBOOT_P1_PHY3;

	} else if (gpt_image_id == GPT_ENTITY_INDEX_UCIE) {
		num_of_dest = 6;
		dest_addr[0] = GPT_DEST_ADDR_UCIE_SS0_V0;
		dest_addr[1] = GPT_DEST_ADDR_UCIE_SS1_V0;
		dest_addr[2] = GPT_DEST_ADDR_UCIE_SS0_V1;
		dest_addr[3] = GPT_DEST_ADDR_UCIE_SS1_V1;
		dest_addr[4] = GPT_DEST_ADDR_UCIE_SS0_H;
		dest_addr[5] = GPT_DEST_ADDR_UCIE_SS1_H;

	} else if (gpt_image_id == GPT_ENTITY_INDEX_BL31) {
		dest_addr[0] = GPT_DEST_ADDR_BL31;
	} else if (gpt_image_id == GPT_ENTITY_INDEX_FREERTOS) {
		dest_addr[0] = GPT_DEST_ADDR_FREERTOS;
	} else {
		return GPT_NOK;
	}

	for (i = 0; i < num_of_dest; i++) {
		gpt_32bit_memcpy((void *)dest_addr[i], (void *)gpt_get_address_by_entry(gpt_image_id),
						 gpt_get_length_by_entry(gpt_image_id));

	}

#endif

	return GPT_OK;
}

uint32_t gpt_partition_init(void)
{
	uint32_t result;

	NOTICE("    GPT init\n");

	gpt_get_image_header();
	gpt_set_gpt_image_addr(gpt_get_active_partition());

	result = load_partition_table();

	if (result != GPT_OK) {
		NOTICE("    GPT init failure\n");
		return result;
	}

	gpt_load_binary_length();

	return GPT_OK;
}
