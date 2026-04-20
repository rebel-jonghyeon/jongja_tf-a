/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_SRC_INTERNAL_H
#define CMRT_CALIPTRA_SRC_INTERNAL_H

#include <stddef.h>
#include <stdbool.h>
#include <cmrt/ucu/span.h>
#include <cmrt/caliptra/types.h>

/* Construct a span from a string literal. */
#define STRSPAN(str) ((span){(uint8_t const *)str, sizeof(str) - 1})

/* Construct a span from an object. */
#define SPAN(obj) ((span){(uint8_t const *)&(obj), sizeof(obj)})

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#undef IS_ALIGNED
#define IS_ALIGNED(p, align) ((((uintptr_t)(p)) & ((align) - 1u)) == 0u)
#undef ROUND_UP
#define ROUND_UP(n, align) (((n) + (uintptr_t)(align) - 1) & ~((uintptr_t)(align) - 1))
#undef ROUND_DOWN
#define ROUND_DOWN(n, align) ((n) & ~((uintptr_t)(align) - 1))

int sha384(const span data, span out);
int hmac384(const span key, const span data, span out);
int p384_genpub(const span priv, span pubx, span puby);
int p384_sign(const span priv, const span digest, span sigr, span sigs);

int ecckpdf(const span input, const span keyname,
	    cmrt_caliptra_privkey_t *priv, cmrt_caliptra_pubkey_t *pub);

int deobfuscate(const span data, const span iv, const span diversify_path, span out);

void zeroize(span buf);
bool allzero(const span buf);

#endif
