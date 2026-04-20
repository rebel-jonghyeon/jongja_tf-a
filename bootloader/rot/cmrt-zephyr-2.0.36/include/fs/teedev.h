/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef TEEDEV_H
#define TEEDEV_H

/** \addtogroup teefs_interface TEEFS Interface */
/*@{*/
#include <stdint.h>
#include <stdbool.h>

struct tee_device;

/**
 * The following structure needs to be implemented for TEEFS.
 * TEEDEV drivers can use tee_device_t below as the base class and add
 * their own proprietary members. Everything in struct tee_device can
 * be set on compile time making this structure read-only.
 */
typedef struct {
	const struct tee_device *impl;
} tee_device_t;

struct tee_device {
	uint8_t block_size; /* log2 block size */
	uint8_t page_size; /* log2 page size */
	bool write_once; /* true for OTP, false for FLASH/RAM/etc. */
	bool write_over; /* true for OTP/RAM/etc., false for FLASH. */
	bool auto_obliterate; /* can be true if write_over is allowed */
	int cache_pages; /* number of cache pages, >= 1 */
	uint8_t (*blocks)(tee_device_t *dev);
	void *(*cache)(tee_device_t *dev, int index);
	bool (*block_isbad)(tee_device_t *dev, uint32_t block);
	void (*block_markbad)(tee_device_t *dev, uint32_t block);
	int (*block_erase)(tee_device_t *dev, uint32_t block);
	int (*page_read)(tee_device_t *dev, uint32_t page, int index);
	int (*page_prog)(tee_device_t *dev, uint32_t page, int index);
};

/**
 * Define the following values to make a statically allocated device.
 * There can be many file systems and many devices, but each device in one
 * application must be declared in its own file (which includes this header).
 */

#if defined(TEEDEV_PAGE_SIZE) && defined(TEEDEV_BLOCK_SIZE) && defined(TEEDEV_CACHE_PAGES) && defined(TEEDEV_WRITE_ONCE) && defined(TEEDEV_WRITE_OVER) && defined(TEEDEV_AUTO_OBLITERATE)

#include <string.h>
#include <errno.h>
#include <sys/types.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/kdc.h>
#ifdef TEEDEV_CRYPTO
#include <drivers/cmrt/teefs/teedev_crypto.h>
#endif
#ifdef TEEDEV_DMAC
#include <drivers/cmrt/teefs/teedev_dmac.h>
#endif
#ifdef TEEDEV_FLASH
#include <drivers/cmrt/teefs/teedev_flash.h>
#endif
#ifdef TEEDEV_OTP
#include <drivers/cmrt/teefs/teedev_otp.h>
#endif

#include <logging/log.h>
#if defined(__ZEPHYR__) && !defined(ZEPHYR_INCLUDE_LOGGING_LOG_H_)
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);
#endif

typedef struct tee_gen_device {
	tee_device_t dev;
	bool opened;
	uint32_t base;
	uint8_t blocks;
	size_t keylen;
#ifdef TEEDEV_CRYPTO
	uint8_t key[KDC_KEY_SIZE];
#endif
	uint8_t data[1u << TEEDEV_PAGE_SIZE];
	uint8_t cache[TEEDEV_CACHE_PAGES][1u << TEEDEV_PAGE_SIZE];
} tee_gen_device_t;

static tee_gen_device_t gen_device;

static inline int block_erase(off_t offset, size_t size)
{
#ifdef TEEDEV_RAM
	if (((offset & 0x3) != 0u) ||
	    ((size & ((1u << TEEDEV_BLOCK_SIZE) - 1u)) != 0u)) {
		return -EINVAL;
	}
	memset((void *)(uintptr_t)offset, 0, size);
	return 0;
#endif
#ifdef TEEDEV_DMAC
	return teedev_dmac_block_erase(offset, size);
#endif
#ifdef TEEDEV_FLASH
	return teedev_flash_block_erase(offset, size);
#endif
#ifdef TEEDEV_OTP
	return teedev_otp_block_erase(offset, size);
#endif
}

static inline int page_read(off_t offset, void *buffer, size_t size)
{
#ifdef TEEDEV_RAM
	if (((offset & 0x3) != 0u) || (buffer == NULL) ||
	    ((size & ((1u << TEEDEV_PAGE_SIZE) - 1u)) != 0u)) {
		return -EINVAL;
	}
	memcpy(buffer, (void *)(uintptr_t)offset, size);
	return 0;
#endif
#ifdef TEEDEV_DMAC
	return teedev_dmac_page_read(offset, buffer, size);
#endif
#ifdef TEEDEV_FLASH
	return teedev_flash_page_read(offset, buffer, size);
#endif
#ifdef TEEDEV_OTP
	return teedev_otp_page_read(offset, buffer, size);
#endif
}

static inline int page_prog(off_t offset, const void *buffer, size_t size)
{
#ifdef TEEDEV_RAM
	if (((offset & 0x3) != 0u) || (buffer == NULL) ||
	    ((size & ((1u << TEEDEV_PAGE_SIZE) - 1u)) != 0u)) {
		return -EINVAL;
	}
	memcpy((void *)(uintptr_t)offset, buffer, size);
	return 0;
#endif
#ifdef TEEDEV_DMAC
	return teedev_dmac_page_prog(offset, buffer, size);
#endif
#ifdef TEEDEV_FLASH
	return teedev_flash_page_prog(offset, buffer, size);
#endif
#ifdef TEEDEV_OTP
	return teedev_otp_page_prog(offset, buffer, size);
#endif
}

static uint8_t teedev_blocks(tee_device_t *dev)
{
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	return d ? d->blocks : 0;
}

static void *teedev_cache(tee_device_t *dev, int index)
{
	if (!dev || index < 0 || index >= TEEDEV_CACHE_PAGES) {
		return NULL;
	}
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	return d->cache[index];
}

static bool teedev_block_isbad(tee_device_t *dev, uint32_t block)
{
	(void)dev;
	(void)block;
	return false;
}

static void teedev_block_markbad(tee_device_t *dev, uint32_t block)
{
	(void)dev;
	(void)block;
}

static int teedev_block_erase(tee_device_t *dev, uint32_t block)
{
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	if (block >> d->blocks) return -EINVAL;

	off_t offset = d->base + (block << TEEDEV_BLOCK_SIZE);
	size_t size = 1 << TEEDEV_BLOCK_SIZE;

	return block_erase(offset, size);
}

#define PAGE2BLOCK(p) ((p) >> (TEEDEV_BLOCK_SIZE - TEEDEV_PAGE_SIZE))

static int teedev_page_read(tee_device_t *dev, uint32_t page, int index)
{
	if (!dev || index < 0 || index >= TEEDEV_CACHE_PAGES) {
		return -EINVAL;
	}
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	if (PAGE2BLOCK(page) >> d->blocks) return -EINVAL;
	void *data = d->cache[index];
	off_t offset = d->base + (page << TEEDEV_PAGE_SIZE);
	void *buffer = d->keylen ? d->data : data;
	size_t size = 1 << TEEDEV_PAGE_SIZE;

	LOG_DBG("Page %08x read at offset %08x", (unsigned int)page, (unsigned int)offset);
	int res = page_read(offset, buffer, size);
	if (res != 0) return res;
#ifdef TEEDEV_CRYPTO
	if (d->keylen) {
		LOG_HEXDUMP_DBG(d->data, size, "ciphertext:");
		res = teedev_page_crypto(d->key, AES_DECRYPT, d->base, page, d->data, data, size);
		if (res != 0) return res;
		LOG_HEXDUMP_DBG(data, size, "plaintext:");
	}
#endif
	return res;
}

static int teedev_page_prog(tee_device_t *dev, uint32_t page, int index)
{
	if (!dev || index < 0 || index >= TEEDEV_CACHE_PAGES) {
		return -EINVAL;
	}
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	if (PAGE2BLOCK(page) >> d->blocks) return -EINVAL;
	void *data = d->cache[index];
	off_t offset = d->base + (page << TEEDEV_PAGE_SIZE);
	void *buffer = d->keylen ? d->data : data;
	size_t size = 1 << TEEDEV_PAGE_SIZE;

	LOG_DBG("Page %08x read at offset %08x", (unsigned int)page, (unsigned int)offset);
#ifdef TEEDEV_CRYPTO
	if (d->keylen) {
		LOG_HEXDUMP_DBG(data, size, "plaintext:");
		int res = teedev_page_crypto(d->key, AES_ENCRYPT, d->base, page, data, d->data, size);
		if (res != 0) return res;
		LOG_HEXDUMP_DBG(d->data, size, "ciphertext:");
	}
#endif
	return page_prog(offset, buffer, size);
}

static const struct tee_device teedev_ram = {
	.block_size = TEEDEV_BLOCK_SIZE,
	.page_size = TEEDEV_PAGE_SIZE,
	.write_once = TEEDEV_WRITE_ONCE,
	.write_over = TEEDEV_WRITE_OVER,
	.auto_obliterate = TEEDEV_AUTO_OBLITERATE,
	.cache_pages = TEEDEV_CACHE_PAGES,
	.blocks = teedev_blocks,
	.cache = teedev_cache,
	.block_isbad = teedev_block_isbad,
	.block_markbad = teedev_block_markbad,
	.block_erase = teedev_block_erase,
	.page_read = teedev_page_read,
	.page_prog = teedev_page_prog,
};

static tee_device_t *teedev_open(uint32_t base, uint8_t blocks, const uint8_t *path, size_t pathlen)
{
	tee_gen_device_t *d = &gen_device;
	if (d->opened) return NULL;

	d->dev.impl = &teedev_ram;
	d->base = base;
	d->blocks = blocks;
	d->keylen = 0;

#ifdef TEEDEV_CRYPTO
	if (path && pathlen) {
		/* Derive key for encryption. */
		int res = teedev_derive_key(d->key, path, pathlen);
		if (res) return NULL;
		d->keylen = sizeof(d->key);
	}
#else
	(void)path;
	(void)pathlen;
#endif
	d->opened = true;

	return &d->dev;
}

static void teedev_close(tee_device_t *dev)
{
	tee_gen_device_t *d = (tee_gen_device_t *)dev;
	if (d && d->opened) {
		memset(d, 0, sizeof(*d));
	}
}

#endif

#endif
