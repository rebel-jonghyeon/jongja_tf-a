/*
 * Copyright (c) 2024 Samsung Electronics Co, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fboot.h>
#include <sac.h>
#include <sac_reg.h>
#include <rebel_h.h>
#include <rebel_h_gpt.h>
#include <drivers/watchdog.h>

#define EFI_NAMELEN						(36)

#define GPT_FLASH_BASE_ADDR				(0x1F80000000ULL)
#define GPT_IMAGE_HEADER_ADDR			(0x1F8007C000ULL)
#define GPT_IMAGE_HEADER_OFFSET			((uint32_t)GPT_IMAGE_HEADER_ADDR & 0x7FFFFFFF)

#define GPT_HEADER_OFFSET				(0x200)
#define GPT_TABLE_OFFSET				(GPT_HEADER_OFFSET + 0x200)

#define SIZEOF_PARTITION_ENTRY			(0x80)
#define SIZEOF_LBA						(0x200)

#define TBOOT_S_SECONDARY_SRC_ADDR		(0x1E00014000ULL)

#define RESET_TIME						(0x424)

#include <logging/log.h>
LOG_MODULE_DECLARE(gpt_s, CONFIG_CMRT_LOG_LEVEL);

struct efi_guid {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clock_seq_and_node[8];
};

struct gpt_entry {
	struct efi_guid		type_uuid;
	struct efi_guid		unique_uuid;
	unsigned long long	first_lba;
	unsigned long long	last_lba;
	unsigned long long	attr;
	unsigned short		name[EFI_NAMELEN];
};

struct __attribute__((packed)) gpt_header {
	unsigned char		signature[8];
	unsigned int		revision;
	unsigned int		size;
	unsigned int		header_crc;
	unsigned int		reserved;
	unsigned long long	current_lba;
	unsigned long long	backup_lba;
	unsigned long long	first_lba;
	unsigned long long	last_lba;
	struct efi_guid		disk_uuid;
	/* starting LBA of array of partition entries */
	unsigned long long	part_lba;
	/* number of partition entries in array */
	unsigned int		list_num;
	/* size of a single partition entry (usually 128) */
	unsigned int		part_size;
	unsigned int		part_crc;
};

struct flash_image_header {
	uint32_t magic;
	uint32_t active_partition;
	uint32_t partition1_offset;
	uint32_t partition2_offset;
	uint32_t recovery_flag;
	uint32_t is_pcie_phy_sram_load;
	uint32_t recovery_reason;
};

static struct flash_image_header img_header;

void gpt_init(void)
{
	cmrt_sac_set_base(NULL, GPT_IMAGE_HEADER_ADDR);

	img_header = *(struct flash_image_header *)(CMRT_SAC_BASE + R_CPU_DATA);
}

uint32_t get_active_partition(void)
{
	return img_header.active_partition;
}

void set_active_partition(uint32_t active, func_ptr write_flash)
{
	img_header.active_partition = active;

	if (write_flash) {
		write_flash(GPT_IMAGE_HEADER_OFFSET, (uint32_t *)&img_header,
					sizeof(struct flash_image_header));
	}
}

void set_recovery_flag(uint32_t recovery_flag, func_ptr write_flash)
{
	img_header.recovery_flag = recovery_flag;

	if (write_flash) {
		write_flash(GPT_IMAGE_HEADER_OFFSET, (uint32_t *)&img_header,
					sizeof(struct flash_image_header));
	}
}

uint32_t get_is_pcie_phy_sram_load(void)
{
	return img_header.is_pcie_phy_sram_load;
}

static void sw_reset(void)
{
	uint32_t chiplet_cnt = get_chiplet_cnt();

	for (int i = chiplet_cnt; i >= 0; i--) {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(CPMU + (i * CHIPLET_BASE_OFFSET)));

		uint32_t temp_time = sys_read32(GET_SAC_R_CPU_DATA(RESET_TIME));

		sys_write32(temp_time & 0xffff, GET_SAC_R_CPU_DATA(RESET_TIME));
		sys_write32(RESET, GET_SAC_R_CPU_DATA(SWRESET));
	}
}

void handling_img_error(func_ptr write_flash)
{
	if (get_active_partition() == ACTIVE_PART_ONE) {
		set_active_partition(ACTIVE_PART_TWO, NULL);
		set_recovery_flag(RECOVERY_FLAG_BOOT_FAIL, write_flash);
		LOG_INF("Image error in GPT partition1");
		LOG_INF("Rebooting with images in GPT partition2");
		LOG_INF("soft reset...");
		sw_reset();
	} else {
		const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));

		if (wdt) {
			(void)wdt_disable(wdt);
		}

		LOG_INF("Image error in GPT partition2");
		__asm__("j .");
	}
}

void set_recovery_reason(uint32_t recovery_reason, func_ptr write_flash)
{
	img_header.recovery_reason = recovery_reason;

	if (write_flash) {
		write_flash(GPT_IMAGE_HEADER_OFFSET, (uint32_t *)(&img_header),
					sizeof(struct flash_image_header));
	}
}

uint32_t get_recovery_flag(void)
{
	return img_header.recovery_flag;
}

uint64_t get_active_partition_base(void)
{
	uint64_t gpt_base = GPT_FLASH_BASE_ADDR;

	if (get_active_partition() == ACTIVE_PART_ONE) {
		gpt_base += img_header.partition1_offset;
	} else {
		gpt_base += img_header.partition2_offset;
	}

	return gpt_base;
}

uint64_t get_image_offset(uint32_t type, uint64_t gpt_base)
{
	if (type == IMG_TBOOT_P0_C3) {
		type = IMG_TBOOT_P0;
	} else if (type == IMG_TBOOT_P1_C3) {
		type = IMG_TBOOT_P1;
	}

	uint64_t entry_addr = gpt_base + GPT_TABLE_OFFSET + (type * SIZEOF_PARTITION_ENTRY);
	uint32_t offset = entry_addr & ~CPU_ADDR_MASK;

	entry_addr &= CPU_ADDR_MASK;
	cmrt_sac_set_base(NULL, entry_addr);

	uint64_t lba = ((volatile struct gpt_entry *)(CMRT_SAC_BASE + R_CPU_DATA + offset))->first_lba;

	return (lba * SIZEOF_LBA);
}

uint64_t get_image_address(uint32_t type, uint64_t gpt_base)
{
	if (type == IMG_TBOOT_S && (get_chiplet_id() != CHIPLET_PRIMARY)) {
		return TBOOT_S_SECONDARY_SRC_ADDR;
	}

	return get_image_offset(type, gpt_base) + gpt_base;
}
