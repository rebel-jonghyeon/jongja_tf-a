#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#include "utils.h"
#include "xmss_ots.h"

static void base_w(const uint8_t *x, int w, int *basew, int out_len)
{
    assert(w == 4 || w == 16);

    int lgw = w == 4 ? 2 : 4;
    int in = 0;
    int out = 0;
    unsigned int total = 0;
    int bits = 0;

    for (int consumed = 0; consumed < out_len; consumed++) {
        if (bits == 0) {
            total = x[in];
            in++;
            bits += 8;
        }
        bits -= lgw;
        basew[out] = (total >> bits) & (w - 1);
        out++;
    }
}

#if 0
void basew_test(void)
{
    uint8_t x[2] = {0x12, 0x34};
    int basew[4];

    memset(basew, 0xff, sizeof(basew));
    base_w(x, 16, basew, 4);
    assert(basew[0] == 1);
    assert(basew[1] == 2);
    assert(basew[2] == 3);
    assert(basew[3] == 4);

    memset(basew, 0xff, sizeof(basew));
    base_w(x, 16, basew, 3);
    assert(basew[0] == 1);
    assert(basew[1] == 2);
    assert(basew[2] == 3);

    memset(basew, 0xff, sizeof(basew));
    base_w(x, 16, basew, 2);
    assert(basew[0] == 1);
    assert(basew[1] == 2);
}
#endif

static void *chain(uint8_t *input, int index, int steps, const void *seed, xmss_ots_addr *addr, const xmss_ots_param *parm)
{
    uint8_t *tmp;
    uint8_t key[parm->n];
    uint8_t bm[parm->n];

    if (steps == 0) {
        return input;
    }
    if (index + steps > (parm->w - 1)) {
        return NULL;
    }
    tmp = chain(input, index, steps - 1, seed, addr, parm);

    addr->hash = index + steps - 1;
    addr->keymask = 0;
    parm->prf(key, seed, addr);
    addr->keymask = 1;
    parm->prf(bm, seed, addr);
    // tmp xor bm
    for (int i = 0; i < parm->n; ++i) {
        tmp[i] ^= bm[i];
    }
    parm->f(tmp, key, tmp);

    return tmp;
}

void wots_gensk(void *sk, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type)
{
    /* The ref impl does not follow RFC8391.
     * Instead, the secret key is derived by:
     * sk[i] = hash(toBytes(4, 32|64) || seed || pub_seed || addr[i])
     * where addr[i].hash = 0, addr[i].keymask = 0, and addr[i].chain = i,
     * besides, all 4-byte integers in addr must be in big-endian.
     */
    const xmss_ots_param *parm = load_ots_parm(type);
    uint8_t *p = sk;

    addr->hash = 0;
    addr->keymask = 0;

    for (int i = 0; i < parm->len; ++i) {
        addr->chain = i;
        parm->prf_keygen(p, seed, pub_seed, addr);
        p += parm->n;
    }
}

void wots_genpk2(void *pk, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type)
{
    const xmss_ots_param *parm = load_ots_parm(type);
    uint8_t *p = pk;
    xmss_ots_addr addr2;

    memcpy(&addr2, addr, sizeof(addr2));
    addr->hash = 0;
    addr2.hash = 0;
    addr2.keymask = 0;

    for (int i = 0; i < parm->len; ++i) {
        addr2.chain = i;
        addr->chain = i;
        parm->prf_keygen(p, seed, pub_seed, &addr2);
        chain(p, 0, parm->w - 1, pub_seed, addr, parm);
        p += parm->n;
    }
}

void wots_genpk(void *pk, const void *sk, xmss_ots_addr *addr, const void *pub_seed, xmss_ots_type type)
{
    const xmss_ots_param *parm = load_ots_parm(type);
    uint8_t *p = pk;
    const uint8_t *s = sk;

    addr->hash = 0;

    for (int i = 0; i < parm->len; ++i) {
        addr->chain = i;
        memcpy(p, s, parm->n);
        chain(p, 0, parm->w - 1, pub_seed, addr, parm);
        p += parm->n;
        s += parm->n;
    }
}

void wots_sign(void *sig, const void *m, const void *sk, xmss_ots_addr *addr, const void *pub_seed, xmss_ots_type type)
{
    const xmss_ots_param *parm = load_ots_parm(type);
    int msg[parm->len];
    uint16_t csum = 0;
    int lgw = parm->w == 4 ? 2 : 4;
    uint8_t *s = sig;
    const uint8_t *k = sk;

    base_w(m, parm->w, msg, parm->len_1);
    for (int i = 0; i < parm->len_1; ++i) {
        csum += parm->w - 1 - msg[i];
    }

    csum <<= 8 - ((parm->len_2 * lgw) % 8);
    csum = htons(csum);
    base_w((const uint8_t *)&csum, parm->w, msg + parm->len_1, parm->len_2);

    for (int i = 0; i < parm->len; ++i) {
        addr->chain = i;
        memcpy(s, k, parm->n);
        chain(s, 0, msg[i], pub_seed, addr, parm);
        s += parm->n;
        k += parm->n;
    }
}

void wots_sign2(void *sig, const void *m, xmss_ots_addr *addr, const void *seed, const void *pub_seed, xmss_ots_type type)
{
    const xmss_ots_param *parm = load_ots_parm(type);
    int msg[parm->len];
    uint16_t csum = 0;
    int lgw = parm->w == 4 ? 2 : 4;
    uint8_t *s = sig;
    xmss_ots_addr addr2;

    memcpy(&addr2, addr, sizeof(addr2));
    addr2.hash = 0;
    addr2.keymask = 0;

    base_w(m, parm->w, msg, parm->len_1);
    for (int i = 0; i < parm->len_1; ++i) {
        csum += parm->w - 1 - msg[i];
    }

    csum <<= 8 - ((parm->len_2 * lgw) % 8);
    csum = htons(csum);
    base_w((const uint8_t *)&csum, parm->w, msg + parm->len_1, parm->len_2);

    for (int i = 0; i < parm->len; ++i) {
        addr->chain = i;
        addr2.chain = i;
        parm->prf_keygen(s, seed, pub_seed, &addr2);
        chain(s, 0, msg[i], pub_seed, addr, parm);
        s += parm->n;
    }
}

void wots_verify(void *pk, const void *m, const void *sig, xmss_ots_addr *addr, const void *seed, xmss_ots_type type)
{
    const xmss_ots_param *parm = load_ots_parm(type);
    int msg[parm->len];
    uint16_t csum = 0;
    int lgw = parm->w == 4 ? 2 : 4;
    const uint8_t *s = sig;
    uint8_t *k = pk;

    base_w(m, parm->w, msg, parm->len_1);
    for (int i = 0; i < parm->len_1; ++i) {
        csum += parm->w - 1 - msg[i];
    }

    csum <<= 8 - ((parm->len_2 * lgw) % 8);
    csum = htons(csum);
    base_w((const uint8_t *)&csum, parm->w, msg + parm->len_1, parm->len_2);

    for (int i = 0; i < parm->len; ++i) {
        addr->chain = i;
        memcpy(k, s, parm->n);
        chain(k, msg[i], parm->w - 1 - msg[i], seed, addr, parm);
        s += parm->n;
        k += parm->n;
    }
}
