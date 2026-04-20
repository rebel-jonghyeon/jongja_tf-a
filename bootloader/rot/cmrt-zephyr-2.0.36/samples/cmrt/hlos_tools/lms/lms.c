#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#include "lms_ots.h"
#include "utils.h"
#include "lms.h"

int lms_height(lms_algorithm_type type)
{
    int h = -1;

    switch (type) {
    case lms_sha256_n32_h5:  h = 5; break;
    case lms_sha256_n32_h10: h = 10; break;
    case lms_sha256_n32_h15: h = 15; break;
    case lms_sha256_n32_h20: h = 20; break;
    case lms_sha256_n32_h25: h = 25; break;
    default: assert(0); break;
    }

    return h;
}

static void lms_pk_hash_rec(void *hash, int h, int r, lmots_algorithm_type type, const uint8_t I[16], const uint8_t seed[32])
{
    static uint8_t sk[4 + 16 + 4 + 32 * 265];
    static uint8_t pk[4 + 16 + 4 + 32];

    const uint32_t rn = htonl(r);

    if (r >= h) {
        // leaf
        // H(I||u32str(r)||u16str(D_LEAF)||OTS_PUB_HASH[r-2^h])
        const uint16_t d_leaf = 0x8282;
        const lmots_param *parm = lms_ots_parm(type);
        if (parm == NULL) {
            return;
        }
        SHA256_CTX ctx;

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, I, 16);
        SHA256_Update(&ctx, &rn, 4);
        SHA256_Update(&ctx, &d_leaf, 2);
        lms_ots_sk_gen(sk, type, r - h, I, seed);
        lms_ots_pk_gen(pk, sk);
        SHA256_Update(&ctx, pk + 4 + 16 + 4, 32);
        SHA256_Final((unsigned char *)hash, &ctx);

        return;
    }


    // H(I||u32str(r)||u16str(D_INTR)||T[2*r]||T[2*r+1])

    const uint16_t d_intr = 0x8383;
    uint8_t child[32];
    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &rn, 4);
    SHA256_Update(&ctx, &d_intr, 2);
    lms_pk_hash_rec(child, h, 2 * r, type, I, seed);
    SHA256_Update(&ctx, child, 32);
    lms_pk_hash_rec(child, h, 2 * r + 1, type, I, seed);
    SHA256_Update(&ctx, child, 32);
    SHA256_Final((unsigned char *)hash, &ctx);
}

static void lms_pk_root(void *hash, int h, lmots_algorithm_type type, const uint8_t I[16], const uint8_t seed[32])
{
    lms_pk_hash_rec(hash, 1 << h, 1, type, I, seed);
}

void lms_pk_gen(void *pk, lms_algorithm_type type, lmots_algorithm_type otstype, const uint8_t I[16], const uint8_t seed[32])
{
    int h = lms_height(type);
    uint8_t *hash = pk;

    lms_pk_root(hash + 4 + 4 + 16, h, otstype, I, seed);

    type = htonl(type);
    otstype = htonl(otstype);

    // pk = type || otstype || I || root_hash
    memcpy(hash, &type, 4);
    hash += 4;
    memcpy(hash, &otstype, 4);
    hash += 4;
    memcpy(hash, I, 16);
}

static void lms_pk_path_rec(uint8_t *path, void *key, void *hash, int h, int r, int q, lmots_algorithm_type type, const uint8_t I[16], const uint8_t seed[32])
{
    static uint8_t sk[4 + 16 + 4 + 32 * 265];
    static uint8_t pk[4 + 16 + 4 + 32];

    const uint32_t rn = htonl(r);
    const int powh = 1 << h;

    if (r >= powh) {
        // leaf
        // H(I||u32str(r)||u16str(D_LEAF)||OTS_PUB_HASH[r-2^h])
        const uint16_t d_leaf = 0x8282;
        const lmots_param *parm = lms_ots_parm(type);
        if (parm == NULL) {
            return;
        }
        const size_t sklen = 4 + 16 + 4 + 32 * parm->p;
        SHA256_CTX ctx;

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, I, 16);
        SHA256_Update(&ctx, &rn, 4);
        SHA256_Update(&ctx, &d_leaf, 2);
        lms_ots_sk_gen(sk, type, r - powh, I, seed);
        lms_ots_pk_gen(pk, sk);
        SHA256_Update(&ctx, pk + 4 + 16 + 4, 32);
        SHA256_Final((unsigned char *)hash, &ctx);

        if (q + powh == r) {
            memcpy(key, sk, sklen);
            return;
        }
    } else {
        // H(I||u32str(r)||u16str(D_INTR)||T[2*r]||T[2*r+1])

        const uint16_t d_intr = 0x8383;
        uint8_t child[32];
        SHA256_CTX ctx;

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, I, 16);
        SHA256_Update(&ctx, &rn, 4);
        SHA256_Update(&ctx, &d_intr, 2);

        lms_pk_path_rec(path, key, child, h, 2 * r, q, type, I, seed);
        SHA256_Update(&ctx, child, 32);

        lms_pk_path_rec(path, key, child, h, 2 * r + 1, q, type, I, seed);
        SHA256_Update(&ctx, child, 32);

        SHA256_Final((unsigned char *)hash, &ctx);
    }

    int depth, target;

    // found our depth
    depth = h - (31 - __builtin_clz(r));
    assert(depth >= 0);
    // path on current depth
    target = powh + q;
    target = (target >> depth) ^ 1;

    if (r == target) {
        memcpy(path + depth * 32, hash, 32);
    }
}

// signing requires a path from root to leaf.
// since the size of the tree is huge, we never store the leaf or internal
// nodes of the tree. it means that we have to calculate everything
// again on every signing.
void lms_sign(void *sig, uint32_t q, lms_algorithm_type type, lmots_algorithm_type otstype, const uint8_t I[16], const uint8_t seed[32], const void *msg, uint32_t mlen)
{
    static uint8_t sk[4 + 16 + 4 + 32 * 265];

    uint8_t root[32];
    uint8_t *path = sig;
    const lmots_param *parm = lms_ots_parm(otstype);
    if (parm == NULL) {
        return;
    }
    size_t siglen = LMS_OTS_SIG_LEN(parm->p);
    int h = lms_height(type);

    path += 4 + 4 + siglen;
    lms_pk_path_rec(path, sk, root, h, 1, q, otstype, I, seed);

    // sig = q || ots_signature || type || path x h
    path = sig;
    q = htonl(q);
    memcpy(path, &q, 4);
    path += 4;
    lms_ots_sign(path, sk, seed, msg, mlen);
    path += siglen;
    type = htonl(type);
    memcpy(path, &type, 4);
}

int lms_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen)
{
    // pk = type || otstype || I || root_hash
    uint32_t type, otstype, q;
    const uint8_t *I, *root_hash, *ots_sig, *path;
    const lmots_param *parm;
    size_t siglen;
    int h, node_num, nn;
    uint8_t Kc[32];
    uint8_t tmp[32];
    const uint16_t d_leaf = 0x8282;
    const uint16_t d_intr = 0x8383;
    SHA256_CTX ctx;

    I = pk;
    memcpy(&type, I, 4);
    I += 4;
    memcpy(&otstype, I, 4);
    I += 4;
    root_hash = I + 16;
    parm = lms_ots_parm(ntohl(otstype));
    if (parm == NULL) {
        return -1;
    }
    siglen = LMS_OTS_SIG_LEN(parm->p);

    // sig = q || ots_signature || type || path x h
    ots_sig = sig;
    memcpy(&q, ots_sig, 4);
    q = ntohl(q);
    ots_sig += 4;

    if (memcmp(&otstype, ots_sig, 4) != 0) {
        return -1;
    }
    if (memcmp(&type, ots_sig + siglen, 4) != 0) {
        return -1;
    }
    path = ots_sig + siglen + 4;
    otstype = ntohl(otstype);
    type = ntohl(type);
    h = lms_height(type);
    if ((h < 0) || (q >= (1UL << h))) {
        return -1;
    }
    lms_ots_verify_hash(Kc, I, q, ots_sig, msg, mlen);

    node_num = (1 << h) + q;
    nn = htonl(node_num);

    // tmp = H(I || u32str(node_num) || u16str(D_LEAF) || Kc)
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &nn, 4);
    SHA256_Update(&ctx, &d_leaf, 2);
    SHA256_Update(&ctx, Kc, 32);
    SHA256_Final((unsigned char *)tmp, &ctx);

    for (int i = 0; node_num > 1; ++i) {
        nn = htonl(node_num / 2);

        SHA256_Init(&ctx);
        SHA256_Update(&ctx, I, 16);
        SHA256_Update(&ctx, &nn, 4);
        SHA256_Update(&ctx, &d_intr, 2);

        if ((node_num % 2) == 1) {
            // H(I||u32str(node_num/2)||u16str(D_INTR)||path[i]||tmp)
            SHA256_Update(&ctx, path, 32);
            SHA256_Update(&ctx, tmp, 32);
        } else {
            // H(I||u32str(node_num/2)||u16str(D_INTR)||tmp||path[i])
            SHA256_Update(&ctx, tmp, 32);
            SHA256_Update(&ctx, path, 32);
        }

        SHA256_Final((unsigned char *)tmp, &ctx);
        node_num = node_num / 2;
        path += 32;
    }
    if (memcmp(tmp, root_hash, 32) != 0) {
        return -1;
    }
    return 0;
}

void lms_hss_pk_gen(void *pk, int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes, const uint8_t I[16], const uint8_t seed[32])
{
    // we don't bother generating all keypairs.
    // instead, just the top level is generated.
    // the sub-trees are generated at signing phase.
    levels = htonl(levels);
    memcpy(pk, &levels, 4);
    lms_pk_gen((uint8_t *)pk + 4, types[0], otstypes[0], I, seed);
}

void lms_hss_child_seed(void *child_seed, void *child_I, const void *seed, const void *I, uint32_t idx, lms_algorithm_type type, lmots_algorithm_type otstype)
{
    SHA256_CTX ctx;
    uint16_t ni = 0xfeff;
    uint8_t ff = 0xff;

    idx = htonl(idx);

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &idx, 4);
    SHA256_Update(&ctx, &ni, 2);
    SHA256_Update(&ctx, &ff, 1);
    SHA256_Update(&ctx, seed, 32);
    SHA256_Final((unsigned char *)child_seed, &ctx);

    ni = 0xffff;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, I, 16);
    SHA256_Update(&ctx, &idx, 4);
    SHA256_Update(&ctx, &ni, 2);
    SHA256_Update(&ctx, &ff, 1);
    SHA256_Update(&ctx, seed, 32);
    SHA256_Final((unsigned char *)child_I, &ctx);
}

void lms_hss_sign(void *sig, uint32_t q, int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes, const uint8_t I[16], const uint8_t seed[32], const void *msg, uint32_t mlen)
{
    uint8_t child_I[16];
    uint8_t child_seed[32];

    // the total number of leaves used for signing message = 2^(\sum h)
    uint32_t leaves[levels];
    uint8_t *psig = sig;
    uint32_t li = levels - 1;

    li = htonl(li);
    memcpy(psig, &li, 4);
    psig += 4;

    for (int i = levels - 1; i >= 0; --i) {
        uint32_t height = lms_height(types[i]);
        uint32_t leaf = (q & ((1 << height) - 1));
        q >>= height;
        leaves[i] = leaf;
    }

    for (int i = 0; i < levels - 1; ++i) {
        // generate seed for subtree
        uint32_t height = lms_height(types[i]);
        const lmots_param *parm = lms_ots_parm(otstypes[i]);
        if (parm == NULL) {
            return;
        }
        uint8_t *pk = psig + LMS_SIG_LEN(parm->p, height);

        lms_hss_child_seed(child_seed, child_I, seed, I, leaves[i], types[i], otstypes[i]);
        // generate pub key of subtree
        lms_pk_gen(pk, types[i + 1], otstypes[i + 1], child_I, child_seed);
        // sign subtree's pub by our private key
        lms_sign(psig, leaves[i], types[i], otstypes[i], I, seed, pk, LMS_PK_LEN);

        psig = pk + LMS_PK_LEN;
    }

    // finally, sign msg with last subtree
    lms_sign(psig, leaves[levels - 1], types[levels - 1], otstypes[levels - 1], child_I, child_seed, msg, mlen);
}

size_t lms_hss_sig_len(int levels, const lms_algorithm_type *types, const lmots_algorithm_type *otstypes)
{
    size_t len = 0;

    len += 4;
    // u32str(Nspk) || sig || pub || ... || sig
    for (int i = 0; i < levels; ++i) {
        uint32_t height = lms_height(types[i]);
        const lmots_param *parm = lms_ots_parm(otstypes[i]);
        if (parm == NULL) {
            return 0;
        }

        len += LMS_SIG_LEN(parm->p, height);
        if (i != levels - 1) {
            len += LMS_PK_LEN;
        }
    }

    return len;
}

static size_t lms_sig_len(const void *sig)
{
    // q || ots_sig || type || path x h
    uint32_t type, otstype;
    const uint8_t *s = sig;
    const lmots_param *parm;

    s += 4; // skip q
    // type || C || 32 * p
    memcpy(&otstype, s, 4);
    otstype = ntohl(otstype);
    parm = lms_ots_parm(otstype);
    s += LMS_OTS_SIG_LEN(parm->p);
    memcpy(&type, s, 4);
    type = ntohl(type);

    return LMS_SIG_LEN(parm->p, lms_height(type));
}

int lms_hss_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen)
{
    // pk = level || type || otstype || I || root_hash
    // sig = n || n * (lms_sig || lms_pk) || lms_sig, where n = levels - 1
    int level, nspk;
    int ret = -1;
    size_t siglen;
    const uint8_t *p1;
    const uint8_t *s1;
    const uint8_t *key;

    memcpy(&level, pk, 4);
    level = ntohl(level);
    memcpy(&nspk, sig, 4);
    nspk = ntohl(nspk);

    if (nspk != level - 1) {
        return -1;
    }

    key = pk;
    key += 4; // skip level

    s1 = sig;
    s1 += 4; // skip n

    for (int i = 0; i < nspk; ++i) {
        siglen = lms_sig_len(s1);
        p1 = s1 + siglen;
        ret = lms_verify(s1, key, p1, LMS_PK_LEN);
        if (ret != 0) {
            return ret;
        }
        s1 = p1 + LMS_PK_LEN;
        key = p1;
    }
    ret = lms_verify(s1, key, msg, mlen);

    return ret;
}
