/*
 * Copyright (c) 2019 Cryptography Research, Inc. (CRI).
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

#define RSA_CONTEXT_SIZE(bytes) (BYTES_TO_WORDS(bytes) * BYTES_PER_WORD + 2 * sizeof(uint32_t) + sizeof(uint64_t))

#define RSA_CONTEXT_LENGTH(bits, n) \
	RSA_CONTEXT_SIZE(((BITS_TO_WORDS(bits) * (n)) + 2) * BYTES_PER_WORD)

#define _RSA_SCRATCH_SIZE(bits) RSA_CONTEXT_LENGTH(bits, 1)
#define _RSA_CRT_SCRATCH_SIZE(bits) RSA_CONTEXT_LENGTH(bits, 14)
#define _RSA_KEYGEN_SCRATCH_SIZE(bits) RSA_CONTEXT_LENGTH(bits, 27)

/** Length of scratchpad for RSA sign/pub */
#define RSA_SCRATCH_SIZE(bits) \
	(_RSA_SCRATCH_SIZE(bits) + BITS_TO_WORDS(bits) * BYTES_PER_WORD)

/** Length of scratchpad for RSA CRT sign/pub */
#define RSA_CRT_SCRATCH_SIZE(bits) \
	(_RSA_CRT_SCRATCH_SIZE(bits) + sizeof(uint32_t))

/** Length of scratchpad for RSA keygen */
#define RSA_KEYGEN_SCRATCH_SIZE(bits) \
	(_RSA_KEYGEN_SCRATCH_SIZE(bits) + BITS_TO_WORDS(bits) * sizeof(uint32_t))

/** Max length of scratchpad */
#define RSA_MAX_SCRATCH_SIZE(bits) RSA_KEYGEN_SCRATCH_SIZE(bits)

#endif
