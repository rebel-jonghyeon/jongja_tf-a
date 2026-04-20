/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <errno.h>
#include <zephyr.h>

#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/teefs/teedev_otp.h>

int z_impl_teedev_otp_block_erase(off_t offset, size_t size)
{
	if (!is_aligned(offset, 4u) || (offset < CMRT_OTP_BASE) ||
	    ((offset + size) >= (CMRT_OTP_BASE + CMRT_OTP_SIZE)) ||
	    !is_aligned(size, 4u)) {
		return -EINVAL;
	}
	/* Cannot erase OTP but check that it is empty. */
	int res = -ENODEV;
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (cmrt_is_valid(omc)) {
		res = 0;
		int words = size >> 2;
		uint32_t *addr = (uint32_t *)(uintptr_t)offset;
		for (int i = 0; i < words; i++) {
			if (addr[i] != 0) {
				/* Not empty, return error. */
				res = -EIO;
				break;
			}
		}
		cmrt_omc_close(omc);
	}
	return res;
}

int z_impl_teedev_otp_page_read(off_t offset, void *buffer, size_t size)
{
	if (!is_aligned(offset, 4u) || (offset < CMRT_OTP_BASE) ||
	    ((offset + size) >= (CMRT_OTP_BASE + CMRT_OTP_SIZE)) ||
	    !is_aligned(size, 4u) || (buffer == NULL) ||
	    !is_aligned(buffer, 4u)) {
		return -EINVAL;
	}

	int res = -ENODEV;
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (cmrt_is_valid(omc)) {
		offset -= CMRT_OTP_BASE;
		uint32_t *dst_addr = (uint32_t *)buffer;
		res = cmrt_omc_read(omc, offset, dst_addr, size);
		cmrt_omc_close(omc);
	}
	return res;
}

int z_impl_teedev_otp_page_prog(off_t offset, const void *buffer, size_t size)
{
	if (!is_aligned(offset, 4u) || (offset < CMRT_OTP_BASE) ||
	    ((offset + size) >= (CMRT_OTP_BASE + CMRT_OTP_SIZE)) ||
	    !is_aligned(size, 4u) || (buffer == NULL) ||
	    !is_aligned(buffer, 4u)) {
		return -EINVAL;
	}

	int res = -ENODEV;
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (cmrt_is_valid(omc)) {
		uint32_t *src_addr = (uint32_t *)buffer;
		uint32_t *dst_addr = (uint32_t *)(uintptr_t)offset;
		memcpy(dst_addr, src_addr, size);
		cmrt_omc_close(omc);
		res = 0;
	}
	return res;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_teedev_otp_block_erase(off_t offset, size_t size)
{
	return z_impl_teedev_otp_block_erase(offset, size);
}
#include <syscalls/teedev_otp_block_erase_mrsh.c>

static inline int z_vrfy_teedev_otp_page_read(off_t offset, void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, size));
	return z_impl_teedev_otp_page_read(offset, buffer, size);
}
#include <syscalls/teedev_otp_page_read_mrsh.c>

static inline int z_vrfy_teedev_otp_page_prog(off_t offset, const void *buffer, size_t size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, size));
	return z_impl_teedev_otp_page_prog(offset, buffer, size);
}
#include <syscalls/teedev_otp_page_prog_mrsh.c>

#endif /* CONFIG_USERSPACE */
