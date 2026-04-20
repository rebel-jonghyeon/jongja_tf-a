/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <string.h>
#include <errno.h>
#include <zephyr.h>

#include <drivers/flash.h>
#include <drivers/cmrt/teefs/teedev_flash.h>

#ifdef CONFIG_SOC_FLASH_M25P80
#define M25P80_BLOCK_MASK ((1u << 12u) - 1u)
#define M25P80_PAGE_MASK ((1u << 8u) - 1u)
#include <drivers/cmrt/axi_flash.h>
#endif

int z_impl_teedev_flash_block_erase(off_t offset, size_t size)
{
#ifdef CONFIG_SOC_FLASH_M25P80
	if (((offset & M25P80_BLOCK_MASK) != 0) ||
	    ((size & M25P80_BLOCK_MASK) != 0)) {
		return -EINVAL;
	}
#endif
	int res;
	struct device *flash = device_get_binding(DT_FLASH_DEV_NAME);
#ifdef CONFIG_SOC_FLASH_M25P80
	res = flash_open(flash);
	if (res) return res;
#endif
	res = flash_write_protection_set(flash, false);
	if (res) return res;
	res = flash_erase(flash, offset, size);
	flash_write_protection_set(flash, true);
#ifdef CONFIG_SOC_FLASH_M25P80
	flash_close(flash);
#endif
	return res;
}

int z_impl_teedev_flash_page_read(off_t offset, void *buffer, size_t size)
{
	if (buffer == NULL) return -EINVAL;
#ifdef CONFIG_SOC_FLASH_M25P80
	if (((offset & M25P80_PAGE_MASK) != 0) ||
	    ((size & M25P80_PAGE_MASK) != 0)) {
		return -EINVAL;
	}
#endif
	int res;
	struct device *flash = device_get_binding(DT_FLASH_DEV_NAME);
#ifdef CONFIG_SOC_FLASH_M25P80
	res = flash_open(flash);
	if (res) return res;
#endif
	res = flash_read(flash, offset, buffer, size);
#ifdef CONFIG_SOC_FLASH_M25P80
	flash_close(flash);
#endif
	return res;
}

int z_impl_teedev_flash_page_prog(off_t offset, const void *buffer, size_t size)
{
	if (buffer == NULL) return -EINVAL;
#ifdef CONFIG_SOC_FLASH_M25P80
	if (((offset & M25P80_PAGE_MASK) != 0) ||
	    ((size & M25P80_PAGE_MASK) != 0)) {
		return -EINVAL;
	}
#endif
	int res;
	struct device *flash = device_get_binding(DT_FLASH_DEV_NAME);
#ifdef CONFIG_SOC_FLASH_M25P80
	res = flash_open(flash);
	if (res) return res;
#endif
	res = flash_write_protection_set(flash, false);
	if (res) return res;
	res = flash_write(flash, offset, buffer, size);
	flash_write_protection_set(flash, true);
#ifdef CONFIG_SOC_FLASH_M25P80
	flash_close(flash);
#endif
	return res;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_teedev_flash_block_erase(off_t offset, size_t size)
{
	return z_impl_teedev_flash_block_erase(offset, size);
}
#include <syscalls/teedev_flash_block_erase_mrsh.c>

static inline int z_vrfy_teedev_flash_page_read(off_t offset, void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, size));
	return z_impl_teedev_flash_page_read(offset, buffer, size);
}
#include <syscalls/teedev_flash_page_read_mrsh.c>

static inline int z_vrfy_teedev_flash_page_prog(off_t offset, const void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, size));
	return z_impl_teedev_flash_page_prog(offset, buffer, size);
}
#include <syscalls/teedev_flash_page_prog_mrsh.c>

#endif /* CONFIG_USERSPACE */
