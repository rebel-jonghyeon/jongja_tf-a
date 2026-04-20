/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
/**
 * @file scratchpad.h
 *
 * @brief Public APIs for the scratchpad.
 */
#ifndef CMRT_SCRATCHPAD_H
#define CMRT_SCRATCHPAD_H

/**
 * Scratchpad Interface
 *
 * @defgroup scratchpad_interface Scratchpad Interface
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Open the scratchpad.
 *
 * All the other functions will return an error until the scratchpad
 * is opened. Open and close are multithread protected, for all the other
 * operations caller needs to call cmrt_scratchpad_lock to reserve the
 * scratchpad for further operations.
 *
 * @param buffer The scratchpad buffer to use.
 * @param len Scratchpad buffer max len.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_scratchpad_open(void *buffer, size_t len);
#define cri_scratchpad_open cmrt_scratchpad_open

/**
 * @brief Close the scratchpad.
 *
 * Reverse of open.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_scratchpad_close(void);
#define cri_scratchpad_close cmrt_scratchpad_close

/**
 * @brief Lock the scratchpad for data processing.
 *
 * @param timeout See k_mutex_lock.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_scratchpad_lock(s32_t timeout);
#define cri_scratchpad_lock cmrt_scratchpad_lock

#define SCRATCHPAD_SEEK_SET 0 /* Seek from beginning of scratchpad. */
#define SCRATCHPAD_SEEK_CUR 1 /* Seek from current position. */
#define SCRATCHPAD_SEEK_END 2 /* Seek from end of scratchpad. */

/**
 * @brief Reset the scratchpad.
 *
 * Set the scratchpad buffer current offset.
 *
 * @return New offset on success, -ERRNO on error.
 */
int cmrt_scratchpad_seek(int offset, int whence);
#define cri_scratchpad_seek cmrt_scratchpad_seek

/**
 * @brief Fill the scratchpad.
 *
 * Fill the scratchpad with given value starting from current offset.
 *
 * @param data Byte to write.
 * @param size Size of data.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_scratchpad_fill(u8_t data, size_t size);
#define cri_scratchpad_fill cmrt_scratchpad_fill

/**
 * @brief Truncate the scratchpad.
 *
 * Truncate the scratchpad to given size.
 *
 * @param data Byte to write.
 * @param size Size of data.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_scratchpad_truncate(size_t size);
#define cri_scratchpad_truncate cmrt_scratchpad_truncate

/**
 * @brief Get pointer to the scratchpad offset for data processing.
 *
 * @param offset Current offset in return.
 * @param left Free space after the offset.
 * @return Pointer to the data or NULL on error.
 */
void *cmrt_scratchpad_data(size_t *offset, size_t *left);
#define cri_scratchpad_data cmrt_scratchpad_data

/**
 * @brief Unlock the scratchpad.
 *
 * @return Zero on success, -ERRNO on error.
 */
void cmrt_scratchpad_unlock(void);
#define cri_scratchpad_unlock cmrt_scratchpad_unlock

#endif /* CMRT_SCRATCHPAD_H */
