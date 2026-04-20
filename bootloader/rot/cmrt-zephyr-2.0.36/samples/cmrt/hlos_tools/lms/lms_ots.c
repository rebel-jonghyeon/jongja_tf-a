#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#include "lms_ots.h"
#include "utils.h"

const lmots_param *lms_ots_parm(uint32_t type)
{
    static const lmots_param parm1 = {
        lmots_sha256_n32_w1, 32, 1, 265, 7, 8516
    };
    static const lmots_param parm2 = {
        lmots_sha256_n32_w2, 32, 2, 133, 6, 4292
    };
    static const lmots_param parm4 = {
        lmots_sha256_n32_w4, 32, 4, 67, 4, 2180
    };
    static const lmots_param parm8 = {
        lmots_sha256_n32_w8, 32, 8, 34, 0, 1124
    };
    switch (type) {
    case lmots_sha256_n32_w1: return &parm1;
    case lmots_sha256_n32_w2: return &parm2;
    case lmots_sha256_n32_w4: return &parm4;
    case lmots_sha256_n32_w8: return &parm8;
    default: printf("unknown OTS type: %d\n", type); return NULL;
    }
}

// TODO: it can be made faster.
static uint32_t coef(const void *s, uint32_t i, uint32_t w)
{
    assert(w == 1 || w == 2 || w == 4 || w == 8);
    assert(s != NULL);

    const uint8_t *p = s;
    size_t offs = (i * w) / 8;
    uint32_t ret = (1U << w) - 1;
    uint8_t c;

    p += offs;
    c = p[0] >> (w * (~i & (8 / w - 1)));
    ret &= c;

    return ret;
}

/*
void coef_test(void)
{
    uint16_t s = 0x3412;
    assert(coef(&s, 7, 1) == 0);
    assert(coef(&s, 0, 4) == 1);
}
*/

// Appendix-A
// q is in big endian, i in little endian
static void pseudo_keygen(void *dst, const uint8_t I[16], uint32_t q, int i, const uint8_t seed[32])
{
    SHA256_CTX ctx;
    uint16_t ni = i;
    uint8_t ff = 0xff;

    ni = htons(ni);
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &q, 4);
    SHA256_Update(&ctx, &ni, 2);
    SHA256_Update(&ctx, &ff, 1);
    SHA256_Update(&ctx, seed, 32);
    SHA256_Final((unsigned char *)dst, &ctx);
}

// 4.2
void lms_ots_sk_gen(void *sk, uint32_t type, uint32_t q, const uint8_t I[16], const uint8_t seed[32])
{
    uint8_t *p = sk;
    const lmots_param *parm = lms_ots_parm(type);
    if (parm == NULL) {
        return;
    }

    // type || I || q
    type = htonl(type);
    memcpy(p, &type, 4);
    p += 4;
    memcpy(p, I, 16);
    p += 16;
    q = htonl(q);
    memcpy(p, &q, 4);
    p += 4;

    for (int i = 0; i < parm->p; ++i) {
        pseudo_keygen(p, I, q, i, seed);
        p += 32;
    }
}

// 4.3
void lms_ots_pk_gen(void *pk, const void *sk)
{
    uint8_t *k = pk;
    const uint8_t *p = sk;
    const lmots_param *parm;
    uint32_t type;
    uint32_t q;
    uint16_t d_pblc = 0x8080;
    const uint8_t *I;
    SHA256_CTX kctx;

    memcpy(&type, p, 4);
    p += 4;
    type = ntohl(type);
    parm = lms_ots_parm(type);
    if (parm == NULL) {
        return;
    }

    I = p;
    p += 16;
    memcpy(&q, p, 4);
    p += 4;

    type = htonl(type);

    // I || q || D_PBLC || y
    SHA256_Init(&kctx);
    SHA256_Update(&kctx, I, 16);
    SHA256_Update(&kctx, &q, 4);
    SHA256_Update(&kctx, &d_pblc, 2);

    for (int i = 0; i < parm->p; ++i) {
        uint8_t tmp[32];
        uint8_t w = (1 << parm->w) - 1;
        uint16_t ni = i;

        ni = htons(ni);
        memcpy(tmp, p, 32);
        for (uint8_t j = 0; j < w; ++j) {
            SHA256_CTX ctx;

            SHA256_Init(&ctx);
            SHA256_Update(&ctx, I, 16);
            SHA256_Update(&ctx, &q, 4);
            SHA256_Update(&ctx, &ni, 2);
            SHA256_Update(&ctx, &j, 1);
            SHA256_Update(&ctx, tmp, 32);
            SHA256_Final((unsigned char *)tmp, &ctx);
        }
        SHA256_Update(&kctx, tmp, 32);
        p += 32;
    }

    // type || I || q || K
    memcpy(k, &type, 4);
    k += 4;
    memcpy(k, I, 16);
    k += 16;
    memcpy(k, &q, 4);
    k += 4;
    SHA256_Final((unsigned char *)k, &kctx);
}

// 4.4
static uint16_t lms_ots_checksum(const void *s, const lmots_param *parm)
{
    uint16_t sum = 0;
    uint32_t w = parm->w;
    int e = (1 << w) - 1;
    uint32_t b = (parm->n * 8) / w;

    for (uint32_t i = 0; i < b; ++i) {
        sum = sum + e - coef(s, i, w);
    }

    return sum << parm->ls;
}

// 4.5
void lms_ots_sign(void *sig, const void *sk, const uint8_t seed[32], const void *msg, uint32_t mlen)
{
    uint8_t C[32];
    uint8_t Q[32 + 2];
    const lmots_param *parm;
    uint32_t type;
    uint32_t w;
    const uint8_t *p = sk;
    const uint8_t *I;
    uint32_t q;
    uint8_t *s = sig;
    SHA256_CTX ctx;
    uint16_t d_mesg = 0x8181;

    memcpy(&type, p, 4);
    p += 4;

    type = ntohl(type);
    parm = lms_ots_parm(type);
    if (parm == NULL) {
        return;
    }
    type = htonl(type);
    w = parm->w;

    I = p;
    p += 16;
    memcpy(&q, p, 4);
    p += 4; // x

    // deterministic C. not specified by RFC,
    // but adopated by ref impl.
    pseudo_keygen(C, I, q, ~2, seed);

    // type || C || ...
    memcpy(s, &type, 4);
    s += 4;
    memcpy(s, C, 32);
    s += 32;

    // Q = H(I || u32str(q) || u16str(D_MESG) || C || message)
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &q, 4);
    SHA256_Update(&ctx, &d_mesg, 2);
    SHA256_Update(&ctx, C, 32);
    SHA256_Update(&ctx, msg, mlen);
    SHA256_Final((unsigned char *)Q, &ctx);

    // attach lms_ots_checksum to Q
    uint16_t cksum = lms_ots_checksum(Q, parm);
    cksum = htons(cksum);
    memcpy(Q + 32, &cksum, 2);

    for (int i = 0; i < parm->p; ++i) {
        uint8_t tmp[32];
        uint8_t a = coef(Q, i, w);
        uint16_t ni = i;

        ni = htons(ni);
        memcpy(tmp, p, 32);

        for (uint8_t j = 0; j < a; ++j) {
            SHA256_Init(&ctx);
            SHA256_Update(&ctx, I, 16);
            SHA256_Update(&ctx, &q, 4);
            SHA256_Update(&ctx, &ni, 2);
            SHA256_Update(&ctx, &j, 1);
            SHA256_Update(&ctx, tmp, 32);
            SHA256_Final((unsigned char *)tmp, &ctx);
        }
        memcpy(s, tmp, 32);
        s += 32;
        p += 32;
    }
}

// q in little-endian
void lms_ots_verify_hash(void *hash, const void *I, uint32_t q, const void *sig, const void *msg, uint32_t mlen)
{
    const uint8_t *C, *y;
    uint32_t type;
    const lmots_param *parm;
    uint8_t Q[32 + 2];
    uint16_t d_mesg = 0x8181;
    uint16_t d_pblc = 0x8080;
    int w;

    SHA256_CTX ctx;
    SHA256_CTX kctx;

    q = htonl(q);

    // get type, C from sig
    memcpy(&type, sig, 4);
    type = ntohl(type);
    parm = lms_ots_parm(type);
    if (parm == NULL) {
        return;
    }
    w = parm->w;
    C = sig;
    C += 4;
    y = C + 32;

    // I || q || D_PBLC || y
    SHA256_Init(&kctx);
    SHA256_Update(&kctx, I, 16);
    SHA256_Update(&kctx, &q, 4);
    SHA256_Update(&kctx, &d_pblc, 2);

    // Q = H(I || u32str(q) || u16str(D_MESG) || C || message)
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &q, 4);
    SHA256_Update(&ctx, &d_mesg, 2);
    SHA256_Update(&ctx, C, 32);
    SHA256_Update(&ctx, msg, mlen);
    SHA256_Final((unsigned char *)Q, &ctx);

    // attach lms_ots_checksum to Q
    uint16_t cksum = lms_ots_checksum(Q, parm);
    cksum = htons(cksum);
    memcpy(Q + 32, &cksum, 2);

    for (int i = 0; i < parm->p; ++i) {
        uint8_t tmp[32];
        uint8_t a = coef(Q, i, w);
        uint16_t ni = i;

        ni = htons(ni);
        memcpy(tmp, y, 32);

        for (uint8_t j = a; j < (1 << w) - 1; ++j) {
            SHA256_Init(&ctx);
            SHA256_Update(&ctx, I, 16);
            SHA256_Update(&ctx, &q, 4);
            SHA256_Update(&ctx, &ni, 2);
            SHA256_Update(&ctx, &j, 1);
            SHA256_Update(&ctx, tmp, 32);
            SHA256_Final((unsigned char *)tmp, &ctx);
        }
        // z[i] = tmp
        SHA256_Update(&kctx, tmp, 32);
        y += 32;
    }
    SHA256_Final((unsigned char *)hash, &kctx);
}

// 4.6
int lms_ots_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen)
{
    // get parm, I, q, K from pk
    const uint8_t *p = pk;
    const uint8_t *K, *I;
    uint32_t type, q;
    uint8_t Kc[32];

    memcpy(&type, p, 4);
    p += 4;
    I = p;
    p += 16;
    memcpy(&q, p, 4); // keep it in big endian
    q = ntohl(q);
    p += 4;
    K = p;

    // get type, C from sig
    if (memcmp(&type, sig, 4) != 0) {
        printf("wrong type\n");
        return -1;
    }

    lms_ots_verify_hash(Kc, I, q, sig, msg, mlen);

    if (memcmp(K, Kc, 32) != 0) {
        printf("wrong K\n");
        return -1;
    }
    return 0;
}
