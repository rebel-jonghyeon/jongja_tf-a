/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef INTERNALS_H
#define INTERNALS_H

/*!
 * Reverse the byte string.  The buffers may overlap.
 * @param pout start of output range
 * @param pin input buffer
 * @param nbuf size of buffer in bytes
 */
int cri_reverse(void *pout, const void *pin, size_t nbuf);

#endif
