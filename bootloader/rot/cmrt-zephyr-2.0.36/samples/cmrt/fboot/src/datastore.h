/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_DATASTORE_H
#define CMRT_DATASTORE_H

#include <sys/dlist.h>
#include <cmrt/fboot/datastore_attr.h>
#include <drivers/cmrt/omc.h>

struct data_store_object {
	sys_dnode_t node;
	uint8_t *name; /* allocated name */
	size_t namelen;
	uint8_t *data; /* allocated data */
	size_t datalen;
	uint8_t attributes[CMRT_OTP_NUM_ROOTS + 1];
};

void data_store_init(void);
int data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, uint32_t required, int root);
int data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, uint32_t required, int root);
int data_store_grant(const void *name, size_t namelen, uint32_t attributes, uint32_t required, int index, int root);

#endif
