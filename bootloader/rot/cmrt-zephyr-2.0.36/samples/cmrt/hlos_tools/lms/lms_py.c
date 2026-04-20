#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

#include "lms_ots.h"
#include "lms.h"
#include "lms_py.h"

uint32_t py_lms_sig_size(uint32_t lms_type, uint32_t ots_type)
{
    const lmots_param *parm = lms_ots_parm(ots_type);
    int h = lms_height(lms_type);
    return LMS_SIG_LEN(parm->p, h);
}

uint32_t py_lms_hss_sig_size(int levels, const uint32_t *types, const uint32_t *otstypes)
{
    return lms_hss_sig_len(levels, types, otstypes);
}

void py_lms_keygen(void *sk, void *pk, const void *seed, uint32_t lms_type, uint32_t ots_type)
{
    const uint8_t *I = seed;
    uint8_t *p = sk;

    I += 32;
    lms_pk_gen(pk, lms_type, ots_type, I, seed);
    memset(p, 0, 4 + 32 + 16);
    p += 4; // skip idx
    memcpy(p, seed, 32);
    memcpy(p + 32, I, 16);
}

void py_lms_sign(void *sig, void *sk, const void *msg, uint32_t mlen, uint32_t lms_type, uint32_t ots_type)
{
    uint8_t *p = sk;
    uint32_t idx = 0;

    memcpy(&idx, p, 4);
    idx = ntohl(idx);
    p += 4; // sk = idx || seed || I

    lms_sign(sig, idx, lms_type, ots_type, p + 32, p, msg, mlen);

    ++idx;
    idx = htonl(idx);
    memcpy(sk, &idx, 4);
}

int py_lms_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen)
{
    return lms_verify(sig, pk, msg, mlen);
}

void py_lms_hss_keygen(void *sk, void *pk, const void *seed, const uint32_t *lms_types, const uint32_t *ots_types, uint32_t levels)
{
    const uint8_t *I = seed;
    uint8_t *p = sk;

    I += 32;
    lms_hss_pk_gen(pk, levels, lms_types, ots_types, I, seed);
    memset(p, 0, 4 + 32 + 16);
    p += 4; // skip idx
    memcpy(p, seed, 32);
    memcpy(p + 32, I, 16);
}

void py_lms_hss_sign(void *sk, void *sig, int levels, const uint32_t *types, const uint32_t *otstypes, const void *msg, uint32_t mlen)
{
    uint8_t *p = sk;
    uint32_t idx = 0;

    memcpy(&idx, p, 4);
    idx = ntohl(idx);
    p += 4; // sk = idx || seed || I

    lms_hss_sign(sig, idx, levels, types, otstypes, p + 32, p, msg, mlen);

    ++idx;
    idx = htonl(idx);
    memcpy(sk, &idx, 4);
}

int py_lms_hss_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen)
{
    return lms_hss_verify(sig, pk, msg, mlen);
}
