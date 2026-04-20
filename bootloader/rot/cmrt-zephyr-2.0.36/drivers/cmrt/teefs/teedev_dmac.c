/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <errno.h>
#include <zephyr.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/teefs/teedev_dmac.h>

int z_impl_teedev_dmac_block_erase(off_t offset, size_t size)
{
	int res = -ENODEV;
	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
	if (cmrt_is_valid(dmac)) {
		res = cmrt_dmac_fill(dmac, 0, (uint32_t)offset, size, 0);
		cmrt_dmac_close(dmac);
	}
	return res;
}

int z_impl_teedev_dmac_page_read(off_t offset, void *buffer, size_t size)
{
	if (buffer == NULL) return -EINVAL;

	int res = -ENODEV;
	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
	if (cmrt_is_valid(dmac)) {
		res = cmrt_dmac_data(dmac, (uint32_t)offset, (uint32_t)(uintptr_t)buffer, size, 0);
		cmrt_dmac_close(dmac);
	}
	return res;
}

int z_impl_teedev_dmac_page_prog(off_t offset, const void *buffer, size_t size)
{
	if (buffer == NULL) return -EINVAL;

	int res = -ENODEV;
	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
	if (cmrt_is_valid(dmac)) {
		res = cmrt_dmac_data(dmac, (uint32_t)(uintptr_t)buffer, (uint32_t)offset, size, 0);
		cmrt_dmac_close(dmac);
	}
	return res;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_teedev_dmac_block_erase(off_t offset, size_t size)
{
	return z_impl_teedev_dmac_block_erase(offset, size);
}
#include <syscalls/teedev_dmac_block_erase_mrsh.c>

static inline int z_vrfy_teedev_dmac_page_read(off_t offset, void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, size));
	return z_impl_teedev_dmac_page_read(offset, buffer, size);
}
#include <syscalls/teedev_dmac_page_read_mrsh.c>

static inline int z_vrfy_teedev_dmac_page_prog(off_t offset, const void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, size));
	return z_impl_teedev_dmac_page_prog(offset, buffer, size);
}
#include <syscalls/teedev_dmac_page_prog_mrsh.c>

#endif /* CONFIG_USERSPACE */
