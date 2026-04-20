/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <string.h>

#include <cmrt/scratchpad.h>

#ifdef CONFIG_MULTITHREADING
static K_MUTEX_DEFINE(mutex);
#endif
static void *sp_buffer;
static size_t sp_maxlen;
static size_t sp_offset;
static bool opened;

int cmrt_scratchpad_open(void *buffer, size_t len)
{
	if (!buffer || !len) {
		return -EINVAL;
	}
	int res = -EEXIST;
#ifdef CONFIG_MULTITHREADING
	k_mutex_lock(&mutex, K_FOREVER);
#endif
	if (!opened) {
		sp_buffer = buffer;
		sp_maxlen = len;
		sp_offset = 0;
		opened = true;
		res = 0;
	}
#ifdef CONFIG_MULTITHREADING
	k_mutex_unlock(&mutex);
#endif
	return res;
}

int cmrt_scratchpad_close(void)
{
	int res = -EFAULT;
#ifdef CONFIG_MULTITHREADING
	k_mutex_lock(&mutex, K_FOREVER);
#endif
	if (opened) {
		sp_buffer = NULL;
		sp_maxlen = 0;
		sp_offset = 0;
		opened = false;
		res = 0;
	}
#ifdef CONFIG_MULTITHREADING
	k_mutex_unlock(&mutex);
#endif
	return res;
}

int cmrt_scratchpad_lock(s32_t timeout)
{
	if (opened) {
#ifdef CONFIG_MULTITHREADING
		return k_mutex_lock(&mutex, K_MSEC(timeout));
#endif
	}
	return -EFAULT;
}

int cmrt_scratchpad_seek(int offset, int whence)
{
	if (opened) {
		switch (whence) {
		case SCRATCHPAD_SEEK_SET:
			if (offset >= 0 && offset < sp_maxlen) {
				sp_offset = offset;
				return sp_offset;
			}
			break;
		case SCRATCHPAD_SEEK_CUR:
			if ((offset >= 0 && (offset + sp_offset < sp_maxlen)) ||
			    (offset < 0 && (size_t)offset <= sp_offset)) {
				sp_offset += offset;
				return sp_offset;
			}
			break;
		case SCRATCHPAD_SEEK_END:
			if ((offset >= 0 && (offset + sp_offset < sp_maxlen)) ||
			    (offset < 0 && (size_t)offset <= sp_offset)) {
				sp_offset += offset;
				return sp_offset;
			}
			break;
		}
	}
	return -EINVAL;
}

int cmrt_scratchpad_fill(uint8_t data, size_t size)
{
	if (opened && (sp_offset + size < sp_maxlen)) {
		memset(sp_buffer + sp_offset, data, size);
		sp_offset += size;
		return 0;
	}
	return -EINVAL;
}

int cmrt_scratchpad_truncate(size_t size)
{
	if (opened && (size < sp_maxlen)) {
		if (size > sp_offset) {
			memset(sp_buffer + sp_offset, 0, size - sp_offset);
		}
		sp_offset = size;
		return 0;
	}
	return -EINVAL;
}

void *cmrt_scratchpad_data(size_t *offset, size_t *left)
{
	if (opened) {
		if (offset) *offset = sp_offset;
		if (left) *left = sp_maxlen - sp_offset;
		return sp_buffer;
	}
	return NULL;
}

void cmrt_scratchpad_unlock(void)
{
	if (opened) {
#ifdef CONFIG_MULTITHREADING
		k_mutex_unlock(&mutex);
#endif
	}
}
