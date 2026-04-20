#ifndef LMS_H
#define LMS_H

#include "lms_ots.h"

typedef enum {
    lms_reserved       = 0,
    lms_sha256_n32_h5  = 5,
    lms_sha256_n32_h10 = 6,
    lms_sha256_n32_h15 = 7,
    lms_sha256_n32_h20 = 8,
    lms_sha256_n32_h25 = 9
} lms_algorithm_type;

// q || ots_sig || type || path x h
#define LMS_SIG_LEN(p, h) (4 + LMS_OTS_SIG_LEN(p) + 4 + 32 * (h))

// type || otstype || I || root_hash
#define LMS_PK_LEN (4 + 4 + 16 + 32)

// level || LMS_PK
#define LMS_HSS_PK_LEN (LMS_PK_LEN + 4)

int lms_height(lms_algorithm_type type);
void lms_pk_gen(void *pk, lms_algorithm_type type, lmots_algorithm_type otstype, const uint8_t I[16], const uint8_t seed[32]);
void lms_sign(void *sig, uint32_t q, lms_algorithm_type type, lmots_algorithm_type otstype, const uint8_t I[16], const uint8_t seed[32], const void *msg, uint32_t mlen);
int lms_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen);
void lms_hss_pk_gen(void *pk, int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes, const uint8_t I[16], const uint8_t seed[32]);
void lms_hss_child_seed(void *child_seed, void *child_I, const void *seed, const void *I, uint32_t idx, lms_algorithm_type type, lmots_algorithm_type otstype);
void lms_hss_sign(void *sig, uint32_t q, int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes, const uint8_t I[16], const uint8_t seed[32], const void *msg, uint32_t mlen);
size_t lms_hss_sig_len(int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes);
int lms_hss_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen);

#endif
