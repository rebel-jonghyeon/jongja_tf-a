/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <fs/teefs.h>
#include <fs/teedev.h>

#include "teeint.h"

#ifdef CONFIG_TEEFS_MULTITHREADING
#ifdef __ZEPHYR__
#include <zephyr.h>
static K_MUTEX_DEFINE(mutex);
inline void lock_teefs(void) { k_mutex_lock(&mutex, K_FOREVER); }
inline void unlock_teefs(void) { k_mutex_unlock(&mutex); }
#endif
#endif

struct teefs_mount_point {
	bool used;
	uint8_t mp[CONFIG_TEEFS_MAX_NAMELEN];
	size_t mplen;
	tee_fs_t fs;
};

struct teefs_mount_point tmps[CONFIG_TEEFS_MAX_INSTANCES];

int teedev_mount(const void *mp, size_t mplen, tee_device_t *dev)
{
	if (!mp || mplen > CONFIG_TEEFS_MAX_NAMELEN || !dev) return -EINVAL;

	for (int i = 0; i < CONFIG_TEEFS_MAX_INSTANCES; i++) {
		struct teefs_mount_point *tmp = &tmps[i];
		if (tmp->used && tmp->mplen == mplen &&
		    (!memcmp(tmp->mp, mp, mplen) || tmp->fs.dev == dev)) {
			/* Already registered. */
			return -EEXIST;
		}
	}
	for (int i = 0; i < CONFIG_TEEFS_MAX_INSTANCES; i++) {
		struct teefs_mount_point *tmp = &tmps[i];
		if (!tmp->used) {
			/* Unused, take it. */
			tmp->used = true;
			memcpy(tmp->mp, mp, mplen);
			tmp->mplen = mplen;
			tmp->fs.dev = dev;
			return i;
		}
	}
	return -ENOSPC;
}

int teedev_umount(const void *mp, size_t mplen, tee_stats_t *stats)
{
	if (!mp || mplen > CONFIG_TEEFS_MAX_NAMELEN) return -EINVAL;

	for (int i = 0; i < CONFIG_TEEFS_MAX_INSTANCES; i++) {
		struct teefs_mount_point *tmp = &tmps[i];
		if (tmp->used && tmp->mplen == mplen &&
		    !memcmp(tmp->mp, mp, mplen)) {
			tee_fs_t *fs = &tmp->fs;
			if (fs->refs != 1) return -EBUSY;
			if (stats) {
				/* Counters are cumulative. */
				stats->cache_reads += fs->stats.cache_reads;
				stats->cache_progs += fs->stats.cache_progs;
				stats->dev_reads += fs->stats.dev_reads;
				stats->dev_progs += fs->stats.dev_progs;
				stats->dev_errors += fs->stats.dev_errors;
			}
			memset(tmp, 0, sizeof(*tmp));
			return 0;
		}
	}
	return -ENODEV;
}

tee_fs_t *open_mp(const void *mp, size_t mplen, bool ismp)
{
	if (!mp || mplen > CONFIG_TEEFS_MAX_NAMELEN) return NULL;

	tee_fs_t *fs = NULL;
	for (int i = 0, l = -1; i < CONFIG_TEEFS_MAX_INSTANCES; i++) {
		struct teefs_mount_point *tmp = &tmps[i];
		if (tmp->used && !memcmp(tmp->mp, mp, tmp->mplen)) {
			if (ismp) {
				/* Looking for mp instead of path. */
				if (tmp->mplen == mplen) {
					/* It is full match. */
					fs = &tmp->fs;
				}
			} else if ((int)tmp->mplen > l) {
				/* Longest prefix so far. */
				fs = &tmp->fs;
				l = tmp->mplen;
			}
		}
	}
	if (fs) fs->refs++;
	return fs;
}

tee_fs_t *open_mp_at(int index, void *mp, size_t *mplen, tee_stats_t *stats)
{
	if (index < 0 || index >= CONFIG_TEEFS_MAX_INSTANCES ||
	    !mp || !mplen || *mplen != CONFIG_TEEFS_MAX_NAMELEN) return NULL;

	tee_fs_t *fs = NULL;
	struct teefs_mount_point *tmp = &tmps[index];
	if (tmp->used) {
		memset(mp, 0, CONFIG_TEEFS_MAX_NAMELEN);
		memcpy(mp, tmp->mp, tmp->mplen);
		*mplen = tmp->mplen;
		fs = &tmp->fs;
		if (stats) {
			stats->cache_reads = fs->stats.cache_reads;
			stats->cache_progs = fs->stats.cache_progs;
			stats->dev_reads = fs->stats.dev_reads;
			stats->dev_progs = fs->stats.dev_progs;
			stats->dev_errors = fs->stats.dev_errors;
		}
		fs->refs++;
	}
	return fs;
}

void close_mp(tee_fs_t *fs)
{
	if (fs->refs > 0) fs->refs--;
}

tee_file_t tfds[CONFIG_TEEFS_MAX_FILES];

int open_fd(tee_fs_t *fs, const void *name, size_t namelen, bool reserve)
{
	/* Search for already opened fd. */
	for (int i = 0; i < CONFIG_TEEFS_MAX_FILES; i++) {
		tee_file_t *file = &tfds[i];
		if (file->fs == fs &&
		    file->pathlen == namelen &&
		    !memcmp(file->path, name, namelen)) {
			file->refs++;
			fs->refs++;
			return i;
		}
	}
	if (reserve) {
		/* Not found, take a free fd. */
		for (int i = 0; i < CONFIG_TEEFS_MAX_FILES; i++) {
			tee_file_t *file = &tfds[i];
			if (!file->fs) {
				file->fs = fs;
				file->pathlen = namelen;
				memcpy(file->path, name, namelen);
				file->refs++;
				fs->refs++;
				return i;
			}
		}
	}
	return -EMFILE;
}

void rename_fd(int fd, const void *name, size_t namelen)
{
	if (fd >= 0 && fd < CONFIG_TEEFS_MAX_FILES) {
		tee_file_t *file = &tfds[fd];
		tee_fs_t *fs = file->fs;
		if (fs) {
			file->pathlen = namelen;
			memcpy(file->path, name, namelen);
		}
	}
}

int find_fd(tee_fs_t *fs, tee_id_t id)
{
	for (int i = 0; i < CONFIG_TEEFS_MAX_FILES; i++) {
		tee_file_t *file = &tfds[i];
		if (file->fs == fs && file->start_id == id) {
			return i;
		}
	}
	return -ENOENT;
}

int close_fd(int fd)
{
	if (fd < 0 || fd >= CONFIG_TEEFS_MAX_FILES)
		return -EINVAL;

	tee_file_t *file = &tfds[fd];
	tee_fs_t *fs = file->fs;
	if (fs) {
		fs->refs--;
		file->refs--;
		if (file->refs == 0) {
			memset(file, 0, sizeof(*file));
		}
		return 0;
	}
	return -ENOENT;
}

tee_file_t *fd2file(int fd)
{
	if (fd >= 0 && fd < CONFIG_TEEFS_MAX_FILES) {
		tee_file_t *file = &tfds[fd];
		if (file->fs) return file;
	}
	return NULL;
}

tee_dir_t tdds[CONFIG_TEEFS_MAX_DIRS];

int open_dd(tee_fs_t *fs)
{
	for (int i = 0; i < CONFIG_TEEFS_MAX_DIRS; i++) {
		tee_dir_t *dir = &tdds[i];
		if (!dir->fs) {
			dir->fs = fs;
			fs->refs++;
			return i;
		}
	}
	return -EMFILE;
}

int close_dd(int dd)
{
	if (dd < 0 || dd >= CONFIG_TEEFS_MAX_DIRS)
		return -EINVAL;

	tee_dir_t *dir = &tdds[dd];
	tee_fs_t *fs = dir->fs;
	if (fs) {
		fs->refs--;
		memset(dir, 0, sizeof(*dir));
		return 0;
	}
	return -ENOENT;
}

tee_dir_t *dd2file(int dd)
{
	if (dd >= 0 && dd < CONFIG_TEEFS_MAX_DIRS) {
		tee_dir_t *dir = &tdds[dd];
		if (dir->fs) return dir;
	}
	return NULL;
}
