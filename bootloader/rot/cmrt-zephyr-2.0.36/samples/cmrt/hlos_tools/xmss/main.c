#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "xmss_ots.h"
#include "xmss.h"

static int xmss_ots_test(void)
{
    xmss_ots_type type = WOTSP_SHA2_256;
    uint8_t seed[32];
    uint8_t pub_seed[32];
    uint8_t msg[32];
    xmss_ots_addr addr;

    // below array is for *256.
    static uint8_t sk[32 * 67];
    static uint8_t pk[32 * 67];
    static uint8_t pk2[32 * 67];
    static uint8_t sig[32 * 67];
    static uint8_t sig2[32 * 67];
    static uint8_t pkc[32 * 67];

    randombytes(seed, 32);
    randombytes(pub_seed, 32);
    randombytes(msg, 32);
    randombytes(&addr, sizeof(addr));

    wots_gensk(sk, &addr, seed, pub_seed, type);

    wots_genpk(pk, sk, &addr, pub_seed, type);
    wots_genpk2(pk2, &addr, seed, pub_seed, type);

    if (memcmp(pk, pk2, sizeof(pk2)) != 0) {
        return -1;
    }

    wots_sign(sig, msg, sk, &addr, pub_seed, type);
    wots_sign2(sig2, msg, &addr, seed, pub_seed, type);

    if (memcmp(sig, sig2, sizeof(sig2)) != 0) {
        return -1;
    }

    wots_verify(pkc, msg, sig, &addr, pub_seed, type);

    if (memcmp(pk, pkc, sizeof(pk)) != 0) {
        return -1;
    }

    return 0;
}

static int treehash_test(void)
{
    xmss_ots_type type = WOTSP_SHA2_256;
    const xmss_ots_param *parm = load_ots_parm(type);
    int height = 10;

    xmss_ots_addr addr;

    uint8_t seed[parm->n];
    uint8_t pub_seed[parm->n];
    uint8_t root_hash[parm->n];
    uint8_t sk[parm->n * parm->len];
    uint8_t auth_path[parm->n * height];

    prng_reseed(0xdeadbeef);
    randombytes(seed, parm->n);
    randombytes(pub_seed, parm->n);
    randombytes(&addr, sizeof(addr));

    tree_hash(root_hash, auth_path, sk, 0, height, 1, &addr, seed, pub_seed, parm);
    // printf("root: %u bytes\n", parm->n);
    // checksum(root_hash, parm->n);
    // checksum(auth_path, sizeof(auth_path));

    return 0;
}

static int xmss_keygen_test(void)
{
    xmss_ots_type type = WOTSP_SHA2_256;
    const xmss_ots_param *parm = load_ots_parm(type);
    int height = 10;
    size_t n = parm->n;

    uint8_t pk[n * 2];
    uint8_t sk[n * 4 + 4];
    uint8_t seed[parm->n * 3];

    prng_reseed(0xdeadbeef);
    randombytes(seed, sizeof(seed));

    xmss_keygen(sk, pk, seed, height, 1, parm);
    // checksum(pk, sizeof(pk));
    // checksum(sk, sizeof(sk));

    return 0;
}

static int xmss_sign_verify_test(void)
{
    int ret;
    xmss_ots_type type = WOTSP_SHA2_256;
    const xmss_ots_param *parm = load_ots_parm(type);
    int height = 10;
    size_t n = parm->n;

    uint8_t pk[n * 2];
    uint8_t sk[n * 4 + 4];
    uint8_t seed[parm->n * 3];
    unsigned char msg[n];
    // sm = idx || r || ots-sig || auth
    //    = 4 + n + n * len + n * height
    unsigned char sm[4 + n + n * parm->len + n * height];

    prng_reseed(0xdeadbeef);
    randombytes(seed, sizeof(seed));
    randombytes(msg, sizeof(msg));

    xmss_keygen(sk, pk, seed, height, 1, parm);
    xmss_sign(sm, sk, msg, sizeof(msg), height, 1, parm);
    ret = xmss_verify(sm, msg, sizeof(msg), pk, height, 1, parm);

    return ret;
}

static int xmss_mt_sign_verify_test(void)
{
    int ret;
    xmss_ots_type type = WOTSP_SHA2_256;
    const xmss_ots_param *parm = load_ots_parm(type);
    int height = 10;
    int layer = 2;
    uint32_t idx_len = index_length(height, layer);
    size_t n = parm->n;

    uint8_t pk[n * 2];
    uint8_t sk[n * 4 + idx_len];
    uint8_t seed[parm->n * 3];
    unsigned char msg[n];
    unsigned char sm[idx_len + n + layer * (n * parm->len + n * height)];

    prng_reseed(0xdeadbeef);
    randombytes(seed, sizeof(seed));
    xmss_keygen(sk, pk, seed, height, layer, parm);
    randombytes(msg, sizeof(msg));
    xmss_sign(sm, sk, msg, sizeof(msg), height, layer, parm);
    ret = xmss_verify(sm, msg, sizeof(msg), pk, height, layer, parm);

    return ret;
}

int main(void)
{
    printf("xmss_ots_test:            %d\n", xmss_ots_test());
    printf("treehash_test:            %d\n", treehash_test());
    printf("xmss_keygen_test:         %d\n", xmss_keygen_test());
    printf("xmss_sign_verify_test:    %d\n", xmss_sign_verify_test());
    printf("xmss_mt_sign_verify_test: %d\n", xmss_mt_sign_verify_test());
    return 0;
}
