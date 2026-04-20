#ifndef XMSS_OTS_H
#define XMSS_OTS_H

#include <stdint.h>

typedef enum {
    WOTSP_RESERVED = 0,
    WOTSP_SHA2_256,
    WOTSP_SHA2_512,
    WOTSP_SHAKE_256,
    WOTSP_SHAKE_512
} xmss_ots_type;

typedef struct __attribute__((__packed__)) {
    uint32_t layer;
    uint64_t tree;
    uint32_t type;          // 0, 1, 2
    uint32_t ots;           // ltree   // padding
    uint32_t chain;         // height  // height
    uint32_t hash;          // index   // index
    uint32_t keymask;
} xmss_ots_addr;

static inline void copy_addr(xmss_ots_addr *dst, const xmss_ots_addr *src)
{
    dst->layer = src->layer;
    dst->tree = src->tree;
}

static inline uint32_t index_length(int height, int layer)
{
    uint32_t len = (layer == 1) ? 4 : ((height * layer) + 7) / 8;
    return len;
}

static inline uint64_t decode_index(const void *data, uint32_t len)
{
    const uint8_t *p = data;
    uint64_t ret = 0;

    for (uint32_t i = 0; i < len; ++i) {
        ret |= ((uint64_t)p[i]) << (8 * (len - 1 - i));
    }

    return ret;
}

static inline void encode_index(void *data, uint32_t len, uint64_t idx)
{
    uint8_t *p = data;

    for (int i = len - 1; i >= 0; i--) {
        p[i] = idx & 0xff;
        idx >>= 8;
    }
}

typedef void (*hash_f)(void *dig, const void *key, const void *msg);
typedef void (*hash_keygen_f)(void *dig, const void *key, const void *pub, const void *addr);
typedef void (*hash_msg_f)(void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen);

typedef struct {
    xmss_ots_type type;
    int n;
    int w;
    int len;
    int len_1;
    int len_2;

    hash_f f;
    hash_f prf;

    hash_f h;
    hash_msg_f h_msg;

    hash_keygen_f prf_keygen;
} xmss_ots_param;

// WOTSP-SHA2_256
// SHA2-256
// n=32, w=16, len=67, len_1=64, len_2=3
// F: SHA2-256(toByte(0, 32) || KEY || M)
// H: SHA2-256(toByte(1, 32) || KEY || M)
// H_msg: SHA2-256(toByte(2, 32) || KEY || M)
// PRF: SHA2-256(toByte(3, 32) || KEY || M)
// PRF_KEYGEN: SHA2-256(toByte(4, 32) || KEY || M), where M = PUB_SEED || ADDR
//
// WOTSP-SHA2_512
// SHA2-512
// n=64, w=16, len=131, len_1=128, len_2=3
// F: SHA2-512(toByte(0, 64) || KEY || M)
// H: SHA2-512(toByte(1, 64) || KEY || M)
// H_msg: SHA2-512(toByte(2, 64) || KEY || M)
// PRF: SHA2-512(toByte(3, 64) || KEY || M)
// PRF_KEYGEN: SHA2-512(toByte(4, 64) || KEY || M), where M = PUB_SEED || ADDR
//
// WOTSP-SHAKE_256
// SHAKE128
// n=32, w=16, len=67, len_1=64, len_2=3
// F: SHAKE128(toByte(0, 32) || KEY || M, 256)
// H: SHAKE128(toByte(1, 32) || KEY || M, 256)
// H_msg: SHAKE128(toByte(2, 32) || KEY || M, 256)
// PRF: SHAKE128(toByte(3, 32) || KEY || M, 256)
// PRF_KEYGEN: SHAKE128(toByte(4, 32) || KEY || M), where M = PUB_SEED || ADDR
//
// WOTSP-SHAKE_512
// SHAKE256
// n=64, w=16, len=131, len_1=128, len_2=3
// F: SHAKE256(toByte(0, 64) || KEY || M, 512)
// H: SHAKE256(toByte(1, 64) || KEY || M, 512)
// H_msg: SHAKE256(toByte(2, 64) || KEY || M, 512)
// PRF: SHAKE256(toByte(3, 64) || KEY || M, 512)
// PRF_KEYGEN: SHAKE256(toByte(4, 64) || KEY || M), where M = PUB_SEED || ADDR

const xmss_ots_param *load_ots_parm(xmss_ots_type type);

void wots_gensk(void *sk, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type);
void wots_genpk2(void *pk, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type);
void wots_genpk(void *pk, const void *sk, xmss_ots_addr *addr, const void *pub_seed, xmss_ots_type type);
void wots_sign(void *sig, const void *m, const void *sk, xmss_ots_addr *addr, const void *pub_seed, xmss_ots_type type);
void wots_sign2(void *sig, const void *m, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type);
void wots_verify(void *pk, const void *m, const void *sig, xmss_ots_addr *addr, const void *seed, xmss_ots_type type);

#endif
