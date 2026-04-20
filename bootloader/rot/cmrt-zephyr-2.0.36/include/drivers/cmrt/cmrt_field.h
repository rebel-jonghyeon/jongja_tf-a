/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_FIELD_H

#define FIELD_PTR(p, member)                       (&(p)->member)
#define FIELD_MASK(size)                           ((1 << (size)) - 1)
#define FIELD_CLEAR(val, size, shift)              ((val) & ~(FIELD_MASK(size) << (shift)))

#define FIELD_SET(val, member, size, shift)        (((val) & FIELD_MASK(size)) << (shift))
#define FIELD_GET(type_ptr, member, size, shift)   ((*FIELD_PTR(type_ptr, member) >> (shift)) & FIELD_MASK(size))
#define FIELD_UPDATE(type_ptr, val, member, size, shfit) \
	(FIELD_SET(val, member, size, shfit) | FIELD_CLEAR(*FIELD_PTR(type_ptr, member), size, shfit))

#define CMRT_FIELD(op, ...) FIELD_##op(__VA_ARGS__)
#endif
