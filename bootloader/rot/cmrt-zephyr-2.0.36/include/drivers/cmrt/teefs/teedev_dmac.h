/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
/** \addtogroup teefs_interface TEEFS Interface */
/*@{*/

#ifndef TEEDEV_DMAC_H
#define TEEDEV_DMAC_H

#include <sys/types.h>

__syscall int teedev_dmac_block_erase(off_t offset, size_t size);
__syscall int teedev_dmac_page_read(off_t offset, void *buffer, size_t size);
__syscall int teedev_dmac_page_prog(off_t offset, const void *buffer, size_t size);

#include <syscalls/teedev_dmac.h>

#endif
