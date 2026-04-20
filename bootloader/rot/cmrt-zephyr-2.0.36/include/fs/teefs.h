/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
/**
 * @file teefs.h
 *
 * @brief Public APIs for the TEEFS.
 */

#ifndef TEEFS_H
#define TEEFS_H

/**
 * TEEFS Interface
 *
 * @defgroup teefs_interface TEEFS Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stddef.h>
#include <stdint.h>

#include <fs/teedev.h>

/**
 * @brief Build a TEE filesystem.
 *
 * Filesystem will be built starting from block 0 up.
 *
 * @param[in] dev Device to use.
 * @param[in] flags Reserved and must be zero.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -EFAULT means if there are no good blocks to create the filesystem.
 */
int teefs_mkfs(tee_device_t *dev, int flags);

#define TEEFS_FLAG_CREATE   (1 << 0) /* create if it does not exist */
#define TEEFS_FLAG_AUTOSYNC (1 << 1) /* autosync at file descriptor close */
#define TEEFS_FLAG_AUTOGC   (1 << 2) /* auto garbage collect when needed */

/**
 * @brief Mount a TEE filesystem.
 *
 * @param[in] mp Mount point for the fs.
 * @param[in] mplen Mount point length.
 * @param[in] dev Device to use in this mount point.
 * @param[in] flags TEEFS_FLAG_CREATE to create filesystem if mount fails.
 *                  TEEFS_FLAG_AUTOSYNC to call teefs_sync when needed.
 *                  TEEFS_FLAG_AUTOGC to call teefs_gc when needed.
 * @retval Mount point index >= 0 on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOENT is returned if filesystem was not found.
 * @retval -EEXIST is returned if the mount point is already registered.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -EFAULT means there is a filesystem but it has different layout.
 */
int teefs_mount(const void *mp, size_t mplen, tee_device_t *dev, int flags);

typedef struct tee_stats {
	unsigned long dev_reads;   /* nr of page reads going to the device */
	unsigned long dev_progs;   /* nr of page progs going to the device */
	unsigned long dev_errors;  /* nr of device errors in any operation */
	unsigned long cache_reads; /* nr of page reads in cache */
	unsigned long cache_progs; /* nr of page progs in cache */
	unsigned long used_pages;  /* nr of used pages in the filesystem */
	unsigned long free_pages;  /* nr of free pages in the filesystem */
	unsigned long rsvd_pages;  /* nr of rsvd pages (for bad blocks etc.) */
} tee_stats_t;

/**
 * @brief Read mount point data.
 *
 * Check mount point at index from 0 to CONFIG_TEEFS_MAX_INSTANCES - 1.
 * If given index is negative just get stats for the given mount point.
 *
 * @param[in] index Mount point index or negative for given mp.
 * @param[in,out] mp Mount point name or buffer for CONFIG_TEEFS_MAX_NAMELEN.
 * @param[in,out] mplen Mount point name length.
 * @param[out] stats Mount point statistics in return if non null.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENODEV is returned if the mount point does not exist.
 */
int teefs_mp(int index, void *mp, size_t *mplen, tee_stats_t *stats);

/**
 * @brief Unmount a TEE filesystem.
 *
 * Umount will succeed even if there are open file handles. Caller must
 * consider all file handles invalid after teefs_umount.
 *
 * @param[in] mp Mount point for the fs.
 * @param[in] mplen Mount point length.
 * @param[in] flags Reserved for future use, must be zero.
 * @param[in,out] stats Add counters to the stats if non null.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -EBUSY is returned if there are open files.
 * @retval -ENODEV is returned if the mount point does not exist.
 */
int teefs_umount(const void *mp, size_t mplen, int flags, tee_stats_t *stats);

typedef struct tee_dirent {
	uint8_t name[CONFIG_TEEFS_MAX_NAMELEN+1];
	size_t namelen;
	size_t datalen;
} tee_dirent_t;

/**
 * @brief Directory open.
 *
 * Opens an existing directory specified by the path.
 * Reserves and opens a directory descriptor that will be used in successive
 * calls to teefs_readdir and teefs_closedir.
 *
 * @param[in] path Path to the directory to open.
 * @param[in] pathlen Path length.
 * @retval Directory descriptor >= 0 on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -EMFILE means there are no free file descriptors.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_opendir(const void *path, size_t pathlen);

/**
 * @brief Directory read entry.
 *
 * Reads directory entries of an open directory. Note that TEEFS does not
 * have real directories. All searches are based on the file name prefix.
 *
 * @param[in] dd File descriptor from teefs_opendir.
 * @param[in,out] entry Pointer to tee_dirent_t structure for the entry.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOENT is returned if there are no files any more.
 * @retval -ENOSPC means a file was returned but teefs_gc should be
 *                 called in order to restart directory listing.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_readdir(int dd, tee_dirent_t *entry);

/**
 * @brief Directory close.
 *
 * Closes an open directory.
 *
 * @param[in] dd File descriptor from teefs_opendir.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOENT is returned if the descriptor was not in use.
 */
int teefs_closedir(int dd);

/**
 * @brief Perform one round of garbage collecting.
 *
 * If there are no deleted files in the filesystem, return value will be zero.
 * Positive return value means teefs_gc can be called again to free more space.
 *
 * @param[in] mp Mount point for the fs.
 * @param[in] mplen Mount point length.
 * @retval Zero or positive on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -EBUSY is returned if there are open files.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -ENOTSUP is returned if device is write once like OTP.
 */
int teefs_gc(const void *mp, size_t mplen);

/**
 * @brief Sync the filesystem.
 *
 * Sync the filesystem. This is currently only used with manual journaling
 * where calling this function writes the current root entry to disk.
 *
 * @param[in] mp Mount point for the fs.
 * @param[in] mplen Mount point length.
 * @retval Zero or positive on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_sync(const void *mp, size_t mplen);

/**
 * @brief Create new file.
 *
 * Create new file.
 *
 * @param[in] name Buffer for file name.
 * @param[in] namelen Name buffer length.
 * @param[in] data Buffer for file data.
 * @param[in] datalen Data buffer length.
 * @retval File descriptor >= 0 on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EMFILE means there are no free file descriptors.
 * @retval -EEXIST means the file already exists and was opened.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_create(const void *name, size_t namelen, const void *data, size_t datalen);

/**
 * @brief Open file.
 *
 * Open and possibly create file.
 *
 * @param[in] name Buffer for file name.
 * @param[in] namelen Name buffer length.
 * @param[in] flags TEEFS_FLAG_CREATE to create empty file if it does not exist.
 * @retval File descriptor >= 0 on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EMFILE means there are no free file descriptors.
 * @retval -ENOENT is returned if file was not found.
 * @retval -ENODEV is returned if the mount point does not exist.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_open(const void *name, size_t namelen, int flags);

/**
 * @brief Close file.
 *
 * Close previously opened or created file.
 *
 * @param[in] fd File descriptor.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOENT is returned if the descriptor was not in use.
 */
int teefs_close(int fd);

/**
 * @brief Unlink file.
 *
 * Unlink previously opened or created file. The file can be referenced until
 * the last descriptor is closed.
 *
 * @param[in] fd File descriptor.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_unlink(int fd);

/**
 * @brief Rename existing file.
 *
 * Rename existing file.
 *
 * @param[in] fd File descriptor.
 * @param[in] name Buffer for file name.
 * @param[in] namelen Name buffer length.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EMFILE means there are no free file descriptors.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -EXDEV is returned if new and old files are not in the same fs.
 * @retval -EBUSY is returned if the new name is currently opened.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_rename(int fd, const void *name, size_t namelen);

/**
 * @brief Read file.
 *
 * Read previously opened or created file from current offset.
 *
 * @param[in] fd File descriptor.
 * @param[out] data Buffer for file data.
 * @param[in,out] datalen Data buffer length.
 * @retval Number of bytes read on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_read(int fd, void *data, size_t *datalen);

/**
 * @brief Write file.
 *
 * Write previously opened or created file from current offset.
 * Write with zero datalen will create a new identical version of the file.
 *
 * @param[in] fd File descriptor.
 * @param[in] data Buffer for file data.
 * @param[in] datalen Data buffer length.
 * @retval Number of bytes written on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_write(int fd, const void *data, size_t datalen);

/**
 * @brief Obliterate file.
 *
 * Obliterate previously opened or created file contents starting from the
 * current file offset. This can be used in OTP/RAM filesystems to write over
 * the file data with value 0xFF. The obliterated file is not deleted.
 *
 * @param[in] fd File descriptor.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOTSUP means the device does not support over writing.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_obliterate(int fd);

/**
 * @brief Truncate file.
 *
 * Truncate previously opened or created file to given length.
 *
 * @param[in] fd File descriptor.
 * @param[in] datalen Truncate length.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 * @retval -ENOSPC means there is no free space until teefs_gc is called.
 * @retval -EROFS is returned if filesystem state is not OK.
 * @retval -EFAULT is a fatal error, filesystem should be remounted.
 */
int teefs_truncate(int fd, size_t datalen);

/**
 * @brief Seek file.
 *
 * Seek file to change current offset.
 *
 * @param[in] fd File descriptor.
 * @param[in] offset Bytes to add to current offset.
 * @param[in] whence Position to apply offset from, see below.
 * @retval Zero on success.
 * @retval -EINVAL is returned for invalid parameters.
 */
int teefs_seek(int fd, int offset, int whence);

#define TEEFS_SEEK_SET 0 /* Seek from beginning of file. */
#define TEEFS_SEEK_CUR 1 /* Seek from current position. */
#define TEEFS_SEEK_END 2 /* Seek from end of file. */

/**
 * @brief Return file offset.
 *
 * Return file offset.
 *
 * @param[in] fd File descriptor.
 * @retval File offset.
 */
size_t teefs_tell(int fd);

/**
 * @brief Get file status.
 *
 * Get file status (really only the size).
 *
 * @param[in] fd File descriptor.
 * @retval File length.
 */
size_t teefs_stat(int fd);

/**
 * @brief Get last error info.
 *
 * Get last error info for the file descriptor.
 * Primary use in debugging the TEEFS itself if something fails.
 *
 * @param[in] fd File descriptor.
 * @param[out] func Pointer to function name.
 * @param[out] line Line number for the error.
 * @param[out] hash Internal hash of the file.
 * @param[out] page Internal page id of the file.
 * @retval The last error code.
 */
int teefs_error(int fd, const char **func, unsigned *line, unsigned *hash, unsigned *page);

#endif
