#ifndef LMS_OTS_H
#define LMS_OTS_H

#include <stdint.h>

/* one-time signatures */

typedef enum {
    lmots_reserved       = 0,
    lmots_sha256_n32_w1  = 1,
    lmots_sha256_n32_w2  = 2,
    lmots_sha256_n32_w4  = 3,
    lmots_sha256_n32_w8  = 4
} lmots_algorithm_type;

typedef struct {
    lmots_algorithm_type ots_alg_type;
    int n; // always 32
    int w; // 1, 2, 4, 8
    int p; // 265, 133, 67, 34
    int ls; // 7, 6, 4, 0
    int sig_len; // 8516, 4292, 2180, 1124
} lmots_param;

const lmots_param *lms_ots_parm(uint32_t type);

void lms_ots_sk_gen(void *sk, uint32_t type, uint32_t q, const uint8_t I[16], const uint8_t seed[32]);
void lms_ots_pk_gen(void *pk, const void *sk);
void lms_ots_sign(void *sig, const void *sk, const uint8_t seed[32], const void *msg, uint32_t mlen);
int lms_ots_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen);
void lms_ots_verify_hash(void *hash, const void *I, uint32_t q, const void *sig, const void *msg, uint32_t mlen);

// type || I || q || K
#define LMS_OTS_PK_LEN (4 + 16 + 4 + 32)

// type || C || 32 * p
#define LMS_OTS_SIG_LEN(p) (4 + 32 + 32 * (p))

#endif
