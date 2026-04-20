#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#include "tiny_sha3/sha3.h"
#include "utils.h"
#include "xmss_ots.h"

static void sha2_256(int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
    uint8_t bs[32] = {0};
    SHA256_CTX ctx;

    bs[31] = b;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, bs, 32);
    SHA256_Update(&ctx, key, klen);
    SHA256_Update(&ctx, msg, mlen);
    SHA256_Final((unsigned char *)dig, &ctx);
}

static void sha2_256_f(void *dig, const void *key, const void *msg)
{
    sha2_256(0, dig, key, 32, msg, 32);
}

static void sha2_256_h(void *dig, const void *key, const void *msg)
{
    sha2_256(1, dig, key, 32, msg, 32 * 2);
}

static void sha2_256_h_msg(void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
    uint32_t key[3 * 8];

    memset(key, 0, sizeof(key));
    memcpy(key, r, 32);
    memcpy(key + 8, root, 32);
    encode_index(key + 16, 32, idx);
    sha2_256(2, dig, key, sizeof(key), msg, mlen);
}

static void sha2_256_prf(void *dig, const void *key, const void *addr)
{
    uint32_t msg[8];
    const uint32_t *a = addr;

    for (int i = 0; i < 8; ++i) {
        msg[i] = htonl(a[i]);
    }
    sha2_256(3, dig, key, 32, msg, sizeof(msg));
}

static void sha2_256_prf_keygen(void *dig, const void *key, const void *pub, const void *addr)
{
    uint32_t msg[16];
    uint32_t *an = msg + 8;
    const uint32_t *a = addr;

    memcpy(msg, pub, 32);
    for (int i = 0; i < 8; ++i) {
        an[i] = htonl(a[i]);
    }
    sha2_256(4, dig, key, 32, msg, 64);
}

static void sha2_512(int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
    uint8_t bs[64] = {0};
    SHA512_CTX ctx;

    bs[63] = b;
    SHA512_Init(&ctx);
    SHA512_Update(&ctx, bs, 64);
    SHA512_Update(&ctx, key, klen);
    SHA512_Update(&ctx, msg, mlen);
    SHA512_Final((unsigned char *)dig, &ctx);
}

static void sha2_512_f(void *dig, const void *key, const void *msg)
{
    sha2_512(0, dig, key, 64, msg, 64);
}

static void sha2_512_h(void *dig, const void *key, const void *msg)
{
    sha2_512(1, dig, key, 64, msg, 64 * 2);
}

static void sha2_512_h_msg(void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
    uint64_t key[3 * 8];

    memset(key, 0, sizeof(key));
    memcpy(key, r, 64);
    memcpy(key + 8, root, 64);
    encode_index(key + 16, 64, idx);
    sha2_512(2, dig, key, sizeof(key), msg, mlen);
}

static void sha2_512_prf(void *dig, const void *key, const void *addr)
{
    uint32_t msg[8];
    const uint32_t *a = addr;

    for (int i = 0; i < 8; ++i) {
        msg[i] = htonl(a[i]);
    }
    sha2_512(3, dig, key, 64, msg, sizeof(msg));
}

static void sha2_512_prf_keygen(void *dig, const void *key, const void *pub, const void *addr)
{
    uint32_t msg[24];
    uint32_t *an = msg + 16;
    const uint32_t *a = addr;

    memcpy(msg, pub, 64);
    for (int i = 0; i < 8; ++i) {
        an[i] = htonl(a[i]);
    }
    sha2_512(4, dig, key, 64, msg, sizeof(msg));
}

static void shake_128(int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
    uint8_t bs[32] = {0};
    sha3_ctx_t ctx;

    bs[31] = b;
    shake128_init(&ctx);
    shake_update(&ctx, bs, 32);
    shake_update(&ctx, key, klen);
    shake_update(&ctx, msg, mlen);
    shake_xof(&ctx);
    shake_out(&ctx, (unsigned char *)dig, 32);
}

static void shake_256_f(void *dig, const void *key, const void *msg)
{
    shake_128(0, dig, key, 32, msg, 32);
}

static void shake_256_h(void *dig, const void *key, const void *msg)
{
    shake_128(1, dig, key, 32, msg, 32 * 2);
}

static void shake_256_h_msg(void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
    uint32_t key[3 * 8];

    memset(key, 0, sizeof(key));
    memcpy(key, r, 32);
    memcpy(key + 8, root, 32);
    encode_index(key + 16, 32, idx);
    shake_128(2, dig, key, sizeof(key), msg, mlen);
}

static void shake_256_prf(void *dig, const void *key, const void *addr)
{
    uint32_t msg[8];
    const uint32_t *a = addr;

    for (int i = 0; i < 8; ++i) {
        msg[i] = htonl(a[i]);
    }
    shake_128(3, dig, key, 32, msg, sizeof(msg));
}

static void shake_256_prf_keygen(void *dig, const void *key, const void *pub, const void *addr)
{
    uint32_t msg[16];
    uint32_t *an = msg + 8;
    const uint32_t *a = addr;

    memcpy(msg, pub, 32);
    for (int i = 0; i < 8; ++i) {
        an[i] = htonl(a[i]);
    }
    shake_128(3, dig, key, 32, msg, sizeof(msg));
}

static void shake_256(int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
    uint8_t bs[64] = {0};
    sha3_ctx_t ctx;

    bs[63] = b;
    shake256_init(&ctx);
    shake_update(&ctx, bs, 64);
    shake_update(&ctx, key, klen);
    shake_update(&ctx, msg, mlen);
    shake_out(&ctx, (unsigned char *)dig, 64);
}

static void shake_512_f(void *dig, const void *key, const void *msg)
{
    shake_256(0, dig, key, 64, msg, 64);
}

static void shake_512_h(void *dig, const void *key, const void *msg)
{
    shake_256(1, dig, key, 64, msg, 64 * 2);
}

static void shake_512_h_msg(void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
    uint64_t key[3 * 8];

    memset(key, 0, sizeof(key));
    memcpy(key, r, 64);
    memcpy(key + 8, root, 64);
    encode_index(key + 16, 64, idx);
    shake_256(2, dig, key, sizeof(key), msg, mlen);
}

static void shake_512_prf(void *dig, const void *key, const void *addr)
{
    uint32_t msg[8];
    const uint32_t *a = addr;

    for (int i = 0; i < 8; ++i) {
        msg[i] = htonl(a[i]);
    }
    shake_256(3, dig, key, 64, msg, sizeof(msg));
}

static void shake_512_prf_keygen(void *dig, const void *key, const void *pub, const void *addr)
{
    uint32_t msg[24];
    uint32_t *an = msg + 16;
    const uint32_t *a = addr;

    memcpy(msg, pub, 64);
    for (int i = 0; i < 8; ++i) {
        an[i] = htonl(a[i]);
    }
    shake_256(4, dig, key, 64, msg, sizeof(msg));
}

const xmss_ots_param *load_ots_parm(xmss_ots_type type)
{
    static const xmss_ots_param parm_sha2_256 = {
        WOTSP_SHA2_256,
        32, 16, 67, 64, 3,
        sha2_256_f, sha2_256_prf,
        sha2_256_h, sha2_256_h_msg,
        sha2_256_prf_keygen
    };
    static const xmss_ots_param parm_sha2_512 = {
        WOTSP_SHA2_512,
        64, 16, 131, 128, 3,
        sha2_512_f, sha2_512_prf,
        sha2_512_h, sha2_512_h_msg,
        sha2_512_prf_keygen
    };
    static const xmss_ots_param parm_shake_256 = {
        WOTSP_SHAKE_256,
        32, 16, 67, 64, 3,
        shake_256_f, shake_256_prf,
        shake_256_h, shake_256_h_msg,
        shake_256_prf_keygen
    };
    static const xmss_ots_param parm_shake_512 = {
        WOTSP_SHAKE_512,
        64, 16, 131, 128, 3,
        shake_512_f, shake_512_prf,
        shake_512_h, shake_512_h_msg,
        shake_512_prf_keygen
    };
    switch (type) {
    case WOTSP_SHA2_256  : return &parm_sha2_256;
    case WOTSP_SHA2_512  : return &parm_sha2_512;
    case WOTSP_SHAKE_256 : return &parm_shake_256;
    case WOTSP_SHAKE_512 : return &parm_shake_512;
    default: return NULL;
    }
}
