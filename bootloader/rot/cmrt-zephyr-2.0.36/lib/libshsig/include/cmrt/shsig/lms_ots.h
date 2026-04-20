/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file lms_ots.h
 *
 * @brief LMS One-Time Signature (OTS).
 */

#ifndef CMRT_LMS_OTS_H
#define CMRT_LMS_OTS_H

#include <stdint.h>
#include <sys/byteorder.h>

/* one-time signatures */

typedef enum {
    LMOTS_RESERVED       = 0,
    LMOTS_SHA256_N32_W1  = 1,
    LMOTS_SHA256_N32_W2  = 2,
    LMOTS_SHA256_N32_W4  = 3,
    LMOTS_SHA256_N32_W8  = 4
} lmots_algorithm_type;

typedef struct {
    lmots_algorithm_type ots_alg_type;
    int n; // always 32
    int w; // 1, 2, 4, 8
    int p; // 265, 133, 67, 34
    int ls; // 7, 6, 4, 0
    int sig_len; // 8516, 4292, 2180, 1124
} lmots_param;

const lmots_param *lms_ots_parm(lmots_algorithm_type type);

int lms_ots_verify(cmrt_hc_t hc, const void *sig, const void *pk,
                   const void *msg, uint32_t mlen);
void lms_ots_verify_hash(cmrt_hc_t hc, void *hash, const void *I,
                         uint32_t q, const void *sig, const void *msg,
                         uint32_t mlen);

// type || I || q || K
#define LMS_OTS_PK_LEN (4u + 16u + 4u + 32u)

// type || C || 32 * p
#define LMS_OTS_SIG_LEN(p) (4u + 32u + 32u * (p))

#define ntohl(x) sys_be32_to_cpu(x)
#define htonl(x) sys_cpu_to_be32(x)
#define htons(x) ((uint16_t) ((((x) >> 8u) & 0xffu) | (((x) & 0xffu) << 8u)))

#endif
