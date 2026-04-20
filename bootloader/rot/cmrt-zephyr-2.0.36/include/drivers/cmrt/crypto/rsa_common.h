/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef RSA_COMMON_H
#define RSA_COMMON_H

#include <limits.h>
#include <stdint.h>

/*
 * howmany, with the include guard, and the format written below, have
 * been available for decades in sys/param.h (used e.g. with select(2)).
 * sys/param.h is not available in all environments this file is used.
 */
#ifndef howmany
#define howmany(x, y)  (((x) + ((y) - 1)) / (y))
#endif

enum rsa_pss_flag {
	RSA_PSS_PREHASHED = 1 << 0
};

#define BYTES_PER_WORD (sizeof(uint32_t))

#define BYTES_TO_WORDS(n) howmany((n), BYTES_PER_WORD)
#define BITS_TO_WORDS(n) howmany((n), BYTES_PER_WORD * CHAR_BIT)

#endif
