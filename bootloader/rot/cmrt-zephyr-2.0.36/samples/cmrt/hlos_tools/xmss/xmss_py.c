#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "xmss_py.h"

typedef struct {
    uint32_t oid;
    uint32_t ots_type;
    uint32_t layer;
    uint32_t height;
} xmss_parm_set;

static const xmss_parm_set xmss_parm_sets[] = {
    { XMSS_SHA2_10_256,  WOTSP_SHA2_256,  1, 10 },
    { XMSS_SHA2_16_256,  WOTSP_SHA2_256,  1, 16 },
    { XMSS_SHA2_20_256,  WOTSP_SHA2_256,  1, 20 },
    { XMSS_SHA2_10_512,  WOTSP_SHA2_512,  1, 10 },
    { XMSS_SHA2_16_512,  WOTSP_SHA2_512,  1, 16 },
    { XMSS_SHA2_20_512,  WOTSP_SHA2_512,  1, 20 },
    { XMSS_SHAKE_10_256, WOTSP_SHAKE_256, 1, 10 },
    { XMSS_SHAKE_16_256, WOTSP_SHAKE_256, 1, 16 },
    { XMSS_SHAKE_20_256, WOTSP_SHAKE_256, 1, 20 },
    { XMSS_SHAKE_10_512, WOTSP_SHAKE_512, 1, 10 },
    { XMSS_SHAKE_16_512, WOTSP_SHAKE_512, 1, 16 },
    { XMSS_SHAKE_20_512, WOTSP_SHAKE_512, 1, 20 }
};

static const xmss_parm_set xmss_mt_parm_sets[] = {
    { XMSSMT_SHA2_20_2_256,   WOTSP_SHA2_256,   2, 20 },
    { XMSSMT_SHA2_20_4_256,   WOTSP_SHA2_256,   4, 20 },
    { XMSSMT_SHA2_40_2_256,   WOTSP_SHA2_256,   2, 40 },
    { XMSSMT_SHA2_40_4_256,   WOTSP_SHA2_256,   4, 40 },
    { XMSSMT_SHA2_40_8_256,   WOTSP_SHA2_256,   8, 40 },
    { XMSSMT_SHA2_60_3_256,   WOTSP_SHA2_256,   3, 60 },
    { XMSSMT_SHA2_60_6_256,   WOTSP_SHA2_256,   6, 60 },
    { XMSSMT_SHA2_60_12_256,  WOTSP_SHA2_256,  12, 60 },
    { XMSSMT_SHA2_20_2_512,   WOTSP_SHA2_512,   2, 20 },
    { XMSSMT_SHA2_20_4_512,   WOTSP_SHA2_512,   4, 20 },
    { XMSSMT_SHA2_40_2_512,   WOTSP_SHA2_512,   2, 40 },
    { XMSSMT_SHA2_40_4_512,   WOTSP_SHA2_512,   4, 40 },
    { XMSSMT_SHA2_40_8_512,   WOTSP_SHA2_512,   8, 40 },
    { XMSSMT_SHA2_60_3_512,   WOTSP_SHA2_512,   3, 60 },
    { XMSSMT_SHA2_60_6_512,   WOTSP_SHA2_512,   6, 60 },
    { XMSSMT_SHA2_60_12_512,  WOTSP_SHA2_512,  12, 60 },
    { XMSSMT_SHAKE_20_2_256,  WOTSP_SHAKE_256,  2, 20 },
    { XMSSMT_SHAKE_20_4_256,  WOTSP_SHAKE_256,  4, 20 },
    { XMSSMT_SHAKE_40_2_256,  WOTSP_SHAKE_256,  2, 40 },
    { XMSSMT_SHAKE_40_4_256,  WOTSP_SHAKE_256,  4, 40 },
    { XMSSMT_SHAKE_40_8_256,  WOTSP_SHAKE_256,  8, 40 },
    { XMSSMT_SHAKE_60_3_256,  WOTSP_SHAKE_256,  3, 60 },
    { XMSSMT_SHAKE_60_6_256,  WOTSP_SHAKE_256,  6, 60 },
    { XMSSMT_SHAKE_60_12_256, WOTSP_SHAKE_256, 12, 60 },
    { XMSSMT_SHAKE_20_2_512,  WOTSP_SHAKE_512,  2, 20 },
    { XMSSMT_SHAKE_20_4_512,  WOTSP_SHAKE_512,  4, 20 },
    { XMSSMT_SHAKE_40_2_512,  WOTSP_SHAKE_512,  2, 40 },
    { XMSSMT_SHAKE_40_4_512,  WOTSP_SHAKE_512,  4, 40 },
    { XMSSMT_SHAKE_40_8_512,  WOTSP_SHAKE_512,  8, 40 },
    { XMSSMT_SHAKE_60_3_512,  WOTSP_SHAKE_512,  3, 60 },
    { XMSSMT_SHAKE_60_6_512,  WOTSP_SHAKE_512,  6, 60 },
    { XMSSMT_SHAKE_60_12_512, WOTSP_SHAKE_512, 12, 60 }
};

const xmss_ots_param *py_load_parm(int type, int *height)
{
    for (int i = 0; i < sizeof(xmss_parm_sets)/sizeof(xmss_parm_set); ++i) {
        const xmss_parm_set *p = &xmss_parm_sets[i];
        if ((int)p->oid == type) {
             *height = (int)p->height;
             return load_ots_parm(p->ots_type);
         }
    }
    return NULL;
}

uint32_t get_xmss_type(uint32_t ots_type, uint32_t height)
{
    for (int i = 0; i < sizeof(xmss_parm_sets)/sizeof(xmss_parm_set); ++i) {
        const xmss_parm_set *p = &xmss_parm_sets[i];
        if ((p->ots_type == ots_type)
            && (p->height == height)) {
            return p->oid;
        }
    }
    return XMSS_RESERVED;
}

static const xmss_ots_param *py_load_mt_parm(int type, int *height, int *layer)
{
    for (int i = 0; i < sizeof(xmss_mt_parm_sets)/sizeof(xmss_parm_set); ++i) {
        const xmss_parm_set *p = &xmss_mt_parm_sets[i];
        if ((int)p->oid == type) {
             *height = (int)p->height / (int)p->layer;
             *layer = (int)p->layer;
             return load_ots_parm(p->ots_type);
         }
    }
    return NULL;
}

uint32_t get_xmss_mt_type(uint32_t ots_type, uint32_t height, uint32_t layer)
{
    for (int i = 0; i < sizeof(xmss_mt_parm_sets)/sizeof(xmss_parm_set); ++i) {
        const xmss_parm_set *p = &xmss_mt_parm_sets[i];
        if ((p->ots_type == ots_type)
            && (p->height == height)) {
             return p->oid;
        }
    }
    return XMSSMT_RESERVED;
}

int py_xmss_keygen(void *sk, void *pk, const void *seed, int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return -1;
    }
    uint32_t *ppk = pk;
    xmss_keygen(sk, ppk + 1, seed, height, 1, parm);
    type = htonl(type);
    ppk[0] = type;
    return 0;
}

int py_xmss_sign(void *sm, void *sk, const void *msg, uint32_t mlen, int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return -1;
    }
    xmss_sign(sm, sk, msg, mlen, height, 1, parm);
    return 0;
}

int py_xmss_verify(const void *sig, const void *msg, uint32_t mlen, const void *pk)
{
    int height = -1;
    const uint32_t *ppk = pk;
    int type = ppk[0];
    type = ntohl(type);
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return -1;
    }
    return xmss_verify(sig, msg, mlen, ppk + 1, height, 1, parm);
}

int py_xmssmt_keygen(void *sk, void *pk, const void *seed, int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return -1;
    }
    uint32_t *ppk = pk;
    xmss_keygen(sk, ppk + 1, seed, height, layer, parm);
    type = htonl(type);
    ppk[0] = type;
    return 0;
}

int py_xmssmt_sign(void *sm, void *sk, const void *msg, uint32_t mlen, int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return -1;
    }
    xmss_sign(sm, sk, msg, mlen, height, layer, parm);
    return 0;
}

int py_xmssmt_verify(const void *sig, const void *msg, uint32_t mlen, const void *pk)
{
    int height = -1, layer = -1;
    const uint32_t *ppk = pk;
    int type = ppk[0];
    type = ntohl(type);
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return -1;
    }
    return xmss_verify(sig, msg, mlen, ppk + 1, height, layer, parm);
}

uint32_t py_xmss_seed_size(int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return 0;
    }

    return parm->n * 3;
}

uint32_t py_xmss_pk_size(int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return 0;
    }

    /* OID || root || SEED */
    return parm->n * 2 + 4;
}

uint32_t py_xmss_sk_size(int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return 0;
    }

    /* idx || wots_sk || SK_PRF || root || SEED */
    return parm->n * 4 + 4;
}

uint32_t py_xmss_sig_size(int type)
{
    int height = -1;
    const xmss_ots_param *parm = py_load_parm(type, &height);

    if (!parm || height < 1) {
        return 0;
    }

    // sig = idx || r || ots-sig || auth || ...
    return 4 + parm->n + parm->n * parm->len + parm->n * height;
}

uint32_t py_xmssmt_seed_size(int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return 0;
    }

    return parm->n * 3;
}

uint32_t py_xmssmt_pk_size(int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return 0;
    }

    /* OID || root || SEED */
    return parm->n * 2 + 4;
}

uint32_t py_xmssmt_sk_size(int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return 0;
    }

    uint32_t idx_len = index_length(height, layer);
    return parm->n * 4 + idx_len;
}

uint32_t py_xmssmt_sig_size(int type)
{
    int height = -1, layer = -1;
    const xmss_ots_param *parm = py_load_mt_parm(type, &height, &layer);

    if (!parm || height < 1 || layer < 1) {
        return 0;
    }

    uint32_t idx_len = index_length(height, layer);
    // sig = idx || r || ots-sig || auth || ...
    return idx_len + parm->n + layer * (parm->n * parm->len + parm->n * height);
}
