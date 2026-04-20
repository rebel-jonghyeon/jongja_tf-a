/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <string.h>
#include "datastore.h"

__noinit static sys_dlist_t datastore;

void data_store_init(void)
{
	sys_dlist_init(&datastore);
}

static struct data_store_object *data_store_find(const uint8_t *name, size_t namelen)
{
	struct data_store_object *object;
	SYS_DLIST_FOR_EACH_CONTAINER(&datastore, object, node) {
		if (object->namelen == namelen &&
		    memcmp(object->name, name, namelen) == 0) {
		    return object;
		}
	}
	return NULL;
}

static struct data_store_object *data_store_create(size_t namelen, size_t datalen)
{
	struct data_store_object *object = k_malloc(sizeof(struct data_store_object));
	if (object == NULL) { return NULL; }

	object->name = k_malloc(namelen);
	if (object->name == NULL) {
		k_free(object);
		return NULL;
	}
	object->data = k_malloc(datalen); /* NULL for zero datalen */
	if (datalen) {
		if (object->data == NULL) {
			k_free(object->name);
			k_free(object);
			return NULL;
		}
	}
	object->namelen = namelen;
	object->datalen = datalen;
	(void)memset(object->attributes, 0, sizeof(object->attributes));
	sys_dlist_append(&datastore, &object->node);

	return object;
}

static void data_store_remove(struct data_store_object *object)
{
	sys_dlist_remove(&object->node);
	(void)memset(object->name, 0, object->namelen);
	(void)memset(object->data, 0, object->datalen);
	k_free(object->name);
	k_free(object->data);
	k_free(object);
}

int data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, uint32_t required, int root)
{
	struct data_store_object *object = data_store_find(name, namelen);
	if (object == NULL) {
		return -ENOENT;
	}
	if (required != 0 &&
	    (object->attributes[root] & required) != required) {
		/* No permissions to read. */
		return -EPERM;
	}
	if (object->datalen > *datalen) {
		/* Not enough space in caller buffer. */
		return -ENOSPC;
	}
	/* Copy data to user buffer. */
	if (object->data != NULL && object->datalen != 0) {
		(void)memcpy(data, object->data, object->datalen);
	}
	*datalen = object->datalen;
	return 0;
}

int data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, uint32_t required, int root)
{
	struct data_store_object *object = data_store_find(name, namelen);
	if (object != NULL) {
		/* Already there, this is an update. */
		if (required != 0 &&
		    (object->attributes[root] & required) != required) {
			/* No permissions to update. */
			return -EPERM;
		}
		if (object->datalen == datalen) {
			/* Do update in place. */
			(void)memcpy(object->data, data, datalen);
			return 0;
		}
		/* Different size, remove data and make new. */
		k_free(object->data);
		object->datalen = 0;
		object->data = k_malloc(datalen); /* NULL for zero datalen */
		if (datalen > 0) {
			if (object->data == NULL) {
				/* No memory for new data. The object
				 * now has NULL data and zero datalen. */
				return -ENOMEM;
			}
			(void)memcpy(object->data, data, datalen);
			object->datalen = datalen;
		}
		return 0;
	}
	/* Create new empty object. */
	object = data_store_create(namelen, datalen);
	if (object == NULL) { return -ENOMEM; }

	/* Copy name, data and attributes. */
	(void)memcpy(object->name, name, namelen);
	(void)memcpy(object->data, data, datalen);
	/* Required attributes for writing existing object are zero for machine,
	 * DS_S_WRITE/DS_U_WRITE for supervisor/user. For new object we want
	 * zero for machine, DS_S_GRANT/DS_U_GRANT for supervisor/user. */
	object->attributes[root] = required << 2;
	return 0;
}

int data_store_grant(const void *name, size_t namelen, uint32_t attributes, uint32_t required, int index, int root)
{
	struct data_store_object *object = data_store_find(name, namelen);
	if (object == NULL) {
		return -ENOENT;
	}
	if (required != 0 &&
	    (object->attributes[root] & required) != required) {
		/* No permissions to grant. */
		return -EPERM;
	}
	/* Update attributes and check for remove. */
	bool all = (attributes & DS_ALL_ROOTS) == DS_ALL_ROOTS;
	bool other = (attributes & DS_OTHER_ROOTS) == DS_OTHER_ROOTS;
	uint8_t all_attributes = 0;
	for (int i = 0; i < sizeof(object->attributes); i++) {
		if (all || (other && i != index) || (!other && i == index)) {
			object->attributes[i] = attributes;
		}
		all_attributes |= object->attributes[i];
	}
	if (all_attributes == 0) {
		/* No access for any root, remove. */
		data_store_remove(object);
	}
	return 0;
}
