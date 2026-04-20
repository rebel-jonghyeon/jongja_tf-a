/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef ENDIANNESS_H
#define ENDIANNESS_H


#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Buffer endianness swap
 * @param s buffer to swap byte order of
 * @param words number of words to swap
 * @return pointer to start of buffer
 */
uint32_t *cmrt_endian_swap(uint32_t *s, uint32_t words);


/*!
 * Copy data reversing input.  The data in pin, pin+1, ..., pin+n-1
 * will be written out to pout+n-1, pout+n-2, ... pout.  We streamline
 * the case of being word-aligned: this case is expected with most
 * data arguments.
 *
 * Overlapping ranges are allowed (which will cause the input to be
 * garbled), including inplace-reversal (which is generally faster.)
 *
 * @param pvout output buffer start (low byte)
 * @param pvin input buffer lowest byte
 * @param n number of bytes to copy
 * @return 0
 */
int cmrt_reverse(void *pvout, const void *pvin, size_t n);


#ifdef __cplusplus
}
#endif


#endif
