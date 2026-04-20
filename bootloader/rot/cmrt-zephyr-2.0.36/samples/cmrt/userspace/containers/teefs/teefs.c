/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/sac.h>

#define TEEDEV_BLOCK_SIZE 10
#define TEEDEV_PAGE_SIZE 8
#define TEEDEV_CACHE_PAGES 4
#define TEEDEV_WRITE_ONCE false
#define TEEDEV_WRITE_OVER false
#define TEEDEV_AUTO_OBLITERATE false
#undef TEEDEV_CRYPTO
#define TEEDEV_RAM
#include <fs/teedev.h>
#include <fs/teefs.h>

/* Creates two SIC flows, the first one takes in file name and returns
 * file contents if the file exists. The second flow is for writing file
 * data for the named file into the RAM filesystem. */

static int create_fs(uint32_t base, uint8_t blocks)
{
#ifdef TEEDEV_CRYPTO
	/* Using encryption, supervisor must have CONFIG_CMRT_TEEDEV_CRYPTO=y */
	const uint8_t *path = (const uint8_t *)"secret pin";
	size_t pathlen = strlen((const char *)path);
#else
	const uint8_t *path = NULL;
	size_t pathlen = 0;
#endif
	tee_device_t *dev = teedev_open(base, blocks, path, pathlen);
	if (!dev) {
		LOG_ERR("Failed in teedev_open");
		return -EFAULT;
	}
	int res = teefs_mkfs(dev, 0);
	if (res < 0) {
		teedev_close(dev);
		LOG_ERR("Failed in teefs_mkfs: %d", res);
		return -EFAULT;
	}
	LOG_INF("Mounting %d blocks to 0x%x", (int)(1 << blocks), (unsigned int)base);
	res = teefs_mount("", 0, dev, TEEFS_FLAG_AUTOGC);
	if (res < 0) {
		teedev_close(dev);
		LOG_ERR("Failed in teefs_mount: %d", res);
		return -EFAULT;
	}
	return res;
}

static int load_file(uint8_t *name, size_t namelen, uint8_t *data, size_t *datalen)
{
	int fd = teefs_open(name, namelen, 0);
	int res = fd;
	if (fd >= 0) {
		res = teefs_read(fd, data, datalen);
		(void)teefs_close(fd);
	}
	return res;
}

static int save_file(uint8_t *name, size_t namelen, uint8_t *data, size_t datalen)
{
	int fd = teefs_open(name, namelen, TEEFS_FLAG_CREATE);
	int res = fd;
	if (fd >= 0) {
		res = teefs_truncate(fd, 0);
		if (res >= 0) {
			res = teefs_write(fd, data, datalen);
		}
		(void)teefs_close(fd);
	}
	return res;
}

static alignas(4) uint8_t namebuffer[64];
static alignas(4) uint8_t databuffer[1024];
#ifdef TEEDEV_RAM
static alignas(4) uint8_t filesystem[8192];
#define FS_SIZE sizeof(filesystem)
#else /* use beginning of the SAC memory for the filesystem */
static uint8_t *filesystem = (uint8_t *)(SAC_MEMORY_BASE + 0x1000);
#define FS_SIZE 8192
#endif

void container(void *p1, void *p2, void *p3)
{
	uint32_t nameid = (uint32_t)(uintptr_t)p1;
	uint32_t dataid = nameid + 1;
	(void)p2;
	(void)p3;

	uint8_t blocks = 31 - __builtin_clz(FS_SIZE >> TEEDEV_BLOCK_SIZE);
	int res = create_fs((uint32_t)(uintptr_t)filesystem, blocks);
	if (res < 0) return;

	cmrt_sic_t namesic = cmrt_sic_open(0, nameid);
	cmrt_sic_t datasic = cmrt_sic_open(0, dataid);
	if (!cmrt_is_valid(namesic) || !cmrt_is_valid(datasic)) {
		LOG_ERR("Cannot open SIC");
		return;
	}
	LOG_INF("Waiting for file name on 0x%x...", (unsigned int)nameid);
	LOG_INF("Waiting for file data on 0x%x...", (unsigned int)dataid);
	size_t namelen = 0;
	for (;;) {
		size_t namebuflen = sizeof(namebuffer);
		size_t databuflen = sizeof(databuffer);
		uint32_t namepeerid, datapeerid;
		int res1 = cmrt_sic_read(namesic, namebuffer, &namebuflen, &namepeerid, 0);
		int res2 = cmrt_sic_read(datasic, databuffer, &databuflen, &datapeerid, 0);
		if (res1 < 0 || res2 < 0) {
			LOG_ERR("Failed to read from HLOS: %d %d", res1, res2);
			return;
		}

		cmrt_handle_t sics[2];
		sics[0] = namesic;
		sics[1] = datasic;
		int fds = cmrt_wait(2, sics, CMRT_FOREVER);
		if (fds <= 0) {
			LOG_ERR("Failed to read from HLOS");
			return;
		}
		if (fds & (1 << 1)) {
			int res = cmrt_sic_sync(datasic);
			if (res < 0) {
				LOG_ERR("Failed to sync from HLOS: %d", res);
				return;
			}
			if (namelen != 0) {
				LOG_INF("File data set for %s:%d", namebuffer, databuflen);
				res = save_file(namebuffer, namelen, databuffer, databuflen);
				if (res < 0) {
					LOG_ERR("Failed to save file %s:%d", namebuffer, databuflen);
				}
				namelen = 0;
			}
		}
		if (fds & (1 << 0)) {
			int res = cmrt_sic_sync(namesic);
			if (res < 0) {
				LOG_ERR("Failed to sync from HLOS: %d", res);
				return;
			}
			if (namebuflen == sizeof(namebuffer)) {
				namebuflen--;
			}
			if (namebuffer[namebuflen - 1] == '\n') {
				namebuflen--;
			}
			namebuffer[namebuflen] = '\0';
			LOG_INF("File name set to %s", namebuffer);
			res = load_file(namebuffer, namebuflen, databuffer, &databuflen);
			if (res >= 0) {
				LOG_INF("Returning file of %d bytes", res);
				res = cmrt_sic_write(namesic, databuffer, databuflen, namepeerid);
				if (res < 0) {
					LOG_ERR("Failed to write to HLOS: %d", res);
					return;
				}
			}
			namelen = namebuflen;
		}
	}
}
