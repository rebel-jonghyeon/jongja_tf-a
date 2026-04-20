#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#include "utils.h"
#include "lms_ots.h"
#include "lms.h"

static int lms_ots_test(void)
{
    uint8_t I[16];
    uint32_t q;
    uint8_t seed[32];

    static uint8_t msg[59];
    // sk: 4 + 16 + 4 + 32 * p
    static uint8_t sk[4 + 16 + 4 + 32 * 265];
    // pk: 4 + 16 + 4 + 32
    static uint8_t pk[4 + 16 + 4 + 32];
    // sig: 4 + 32 + 32 * p
    static uint8_t sig[4 + 32 + 32 * 265];

    prng_reseed(0xdeadbeef);
    randombytes(msg, sizeof(msg));
    randombytes(I, 16);
    randombytes(seed, 32);
    q = prng();

    lms_ots_sk_gen(sk, lmots_sha256_n32_w1, q, I, seed);
    lms_ots_pk_gen(pk, sk);
    lms_ots_sign(sig, sk, seed, msg, sizeof(msg));

    return lms_ots_verify(sig, pk, msg, sizeof(msg));
}

static int lms_test(void)
{
    uint8_t I[16];
    uint8_t seed[32];
    uint8_t pk[4 + 4 + 16 + 32];
    uint8_t msg[32];

    // q || ots_sig || type || path x h
    static uint8_t sig[4 + 4 + 32 + 32 * 265 + 4 + 32 * 25];

    prng_reseed(0xdeadbeef);
    randombytes(seed, 32);
    randombytes(I, 16);
    lms_pk_gen(pk, lms_sha256_n32_h5, lmots_sha256_n32_w1, I, seed);
    randombytes(msg, sizeof(msg));
    // use first private key, counting starts from zero
    lms_sign(sig, 0, lms_sha256_n32_h5, lmots_sha256_n32_w1, I, seed, msg, sizeof(msg));
    return lms_verify(sig, pk, msg, sizeof(msg));
}

static int lms_hss_test(void)
{
    uint8_t I[16];
    uint8_t seed[32];
    // pk = level || type || otstype || I || root_hash
    uint8_t pk[4 + 4 + 4 + 16 + 32];
    uint8_t msg[32];
    // sig = n || n * (lms_sig || lms_pk) || lms_sig, where n = levels - 1
    uint8_t *sig = NULL;
    size_t siglen = 0;
    int ret;

    const int levels = 2;
    const lms_algorithm_type types[] = { lms_sha256_n32_h5, lms_sha256_n32_h10 };
    const lmots_algorithm_type ots_types[] = { lmots_sha256_n32_w1, lmots_sha256_n32_w2 };

    prng_reseed(0xdeadbeef);

    randombytes(seed, 32);
    randombytes(I, 16);

    lms_hss_pk_gen(pk, levels, types, ots_types, I, seed);

    randombytes(msg, sizeof(msg));
    siglen = lms_hss_sig_len(levels, types, ots_types);
    sig = malloc(siglen);
    lms_hss_sign(sig, 0, levels, types, ots_types, I, seed, msg, sizeof(msg));
    // checksum(sig, siglen);
    ret = lms_hss_verify(sig, pk, msg, sizeof(msg));
    free(sig);

    return ret;
}

static int child_seed_test(void)
{
    uint8_t I[16];
    uint8_t seed[32];
    uint8_t child_I[16];
    uint8_t child_seed[32];
    uint32_t index = 1;

    prng_reseed(0xdeadbeef);

    randombytes(seed, 32);
    randombytes(I, 16);
    lms_hss_child_seed(child_seed, child_I, seed, I, index, lms_sha256_n32_h5, lmots_sha256_n32_w1);
    checksum(child_I, sizeof(child_I));
    checksum(child_seed, sizeof(child_seed));

    return 0;
}

int main(void)
{
    printf("lms_ots_test:    %d\n", lms_ots_test());
    printf("lms_test:        %d\n", lms_test());
    printf("lms_hss_test:    %d\n", lms_hss_test());
    printf("child_seed_test: %d\n", child_seed_test());
    return 0;
}
