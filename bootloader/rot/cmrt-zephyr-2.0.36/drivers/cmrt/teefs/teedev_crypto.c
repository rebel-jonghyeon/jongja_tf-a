/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <errno.h>
#include <zephyr.h>

#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/teefs/teedev_crypto.h>

int z_impl_teedev_page_crypto(uint8_t *key, int operation, uint32_t base, uint32_t page, const void *src, void *dst, size_t len)
{
	cmrt_aes_t aes = cmrt_aes_open(0);
	if (!aes) return -ENODEV;

	uint32_t iv[2];
	iv[0] = base;
	iv[1] = page;
	int res = cmrt_aes_init(aes, operation, AES_CBC, key, KDC_KEY_SIZE, iv, sizeof(iv), 0);
	if (!res) res = cmrt_aes_final(aes, src, len, dst);

	cmrt_aes_close(aes);
	return res;
}

int z_impl_teedev_derive_key(uint8_t *key, const uint8_t *path, size_t pathlen)
{
	cmrt_kdc_cmd_t cmd;
	memset(&cmd, 0, sizeof(cmd));
	if (pathlen > sizeof(cmd.diversify_path))
		return -EINVAL;

	cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_SYNC);
	if (!kdc) return -ENODEV;

	cmd.diversify_len = pathlen;
	memcpy(cmd.diversify_path, path, cmd.diversify_len);
	cmd.base_key_id = KEY_ID_DGOK;
	cmd.dest = KDC_DEST_SW;
	int res = cmrt_kdc_derive_key(kdc, &cmd);
	if (!res) memcpy(key, cmd.key, sizeof(cmd.key));

	cmrt_kdc_close(kdc);
	return res;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_teedev_page_crypto(uint8_t *key, int operation, uint32_t base, uint32_t page, const void *src, void *dst, size_t len)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(key, KDC_KEY_SIZE));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(src, len));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(dst, len));
	return z_impl_teedev_page_crypto(key, operation, base, page, src, dst, len);
}
#include <syscalls/teedev_page_crypto_mrsh.c>

static inline int z_vrfy_teedev_derive_key(uint8_t *key, const uint8_t *path, size_t pathlen)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(key, KDC_KEY_SIZE));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(path, pathlen));
	return z_impl_teedev_derive_key(key, path, pathlen);
}
#include <syscalls/teedev_derive_key_mrsh.c>

#endif /* CONFIG_USERSPACE */
