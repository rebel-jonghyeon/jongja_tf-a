#ifndef XMSS_H
#define XMSS_H

#include <stdint.h>

#include "xmss_ots.h"

typedef xmss_ots_addr xmss_ltree_addr;
typedef xmss_ots_addr xmss_htree_addr;

typedef struct {
    xmss_ots_addr   ots;
    xmss_ltree_addr ltree;
    xmss_ltree_addr hash;
} xmss_addr;

void tree_hash(void *root_node, void *auth_path, void *key, int leaf, int height, int curr, xmss_ots_addr *addr, const void *seed, const void *pub_seed, const xmss_ots_param *parm);
void xmss_keygen(void *sk, void *pk, const void *seed, int height, int layer, const xmss_ots_param *parm);
void xmss_sign(void *sm, void *sk, const void *msg, uint32_t mlen, int height, int layer, const xmss_ots_param *parm);
int xmss_verify(const void *sig, const void *msg, uint32_t mlen, const void *pk, int height, int layer, const xmss_ots_param *parm);

#endif
