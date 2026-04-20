/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/*** GENERIC FUNCTIONS ***/

#include <errno.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define TEEDEV_BLOCK_SIZE CONFIG_TEEDEV_DMAC_BLOCK_SIZE
#define TEEDEV_PAGE_SIZE CONFIG_TEEDEV_DMAC_PAGE_SIZE
#define TEEDEV_CACHE_PAGES CONFIG_TEEDEV_DMAC_CACHE_PAGES
#define TEEDEV_WRITE_ONCE false
#define TEEDEV_WRITE_OVER true
#define TEEDEV_AUTO_OBLITERATE false
#define TEEDEV_CRYPTO
#define TEEDEV_DMAC
#include <fs/teedev.h>

tee_device_t *teedev_dmac_open(uint8_t *base, uint8_t blocks, const char *path, size_t pathlen)
{
	return teedev_open((uint32_t)(uintptr_t)base, blocks, path, pathlen);
}

void teedev_dmac_close(tee_device_t *dev)
{
	teedev_close(dev);
}
