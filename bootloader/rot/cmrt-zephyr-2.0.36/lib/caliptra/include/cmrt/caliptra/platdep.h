/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_PLATDEP_H
#define CMRT_CALIPTRA_PLATDEP_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies required by this Caliptra library. The application
 * must provide these.
 */

int cmrt_caliptra_plat_datastore_write(const char *name, size_t namelen,
				       const void *data, size_t datalen);

int cmrt_caliptra_plat_datastore_read(const char *name, size_t namelen,
				      void *data, size_t *datalen);

int cmrt_caliptra_plat_datastore_grant(const char *name, size_t namelen,
				       int root, uint32_t attr);

#ifdef __cplusplus
}
#endif
#endif
