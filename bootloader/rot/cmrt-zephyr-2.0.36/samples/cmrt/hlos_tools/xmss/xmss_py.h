#ifndef XMSS_PY_H
#define XMSS_PY_H

#include <stdint.h>

#include "xmss_ots.h"
#include "xmss.h"

// API exposed to python

// XMSS Signatures
// See Page 52 of RFC8391
#define XMSS_RESERVED      0x0
#define XMSS_SHA2_10_256   0x1
#define XMSS_SHA2_16_256   0x2
#define XMSS_SHA2_20_256   0x3
#define XMSS_SHA2_10_512   0x4
#define XMSS_SHA2_16_512   0x5
#define XMSS_SHA2_20_512   0x6
#define XMSS_SHAKE_10_256  0x7
#define XMSS_SHAKE_16_256  0x8
#define XMSS_SHAKE_20_256  0x9
#define XMSS_SHAKE_10_512  0xA
#define XMSS_SHAKE_16_512  0xB
#define XMSS_SHAKE_20_512  0xC

// XMSS^MT Signatures
// See Page 53 of RFC8391
#define XMSSMT_RESERVED          0x00
#define XMSSMT_SHA2_20_2_256     0x01
#define XMSSMT_SHA2_20_4_256     0x02
#define XMSSMT_SHA2_40_2_256     0x03
#define XMSSMT_SHA2_40_4_256     0x04
#define XMSSMT_SHA2_40_8_256     0x05
#define XMSSMT_SHA2_60_3_256     0x06
#define XMSSMT_SHA2_60_6_256     0x07
#define XMSSMT_SHA2_60_12_256    0x08
#define XMSSMT_SHA2_20_2_512     0x09
#define XMSSMT_SHA2_20_4_512     0x0A
#define XMSSMT_SHA2_40_2_512     0x0B
#define XMSSMT_SHA2_40_4_512     0x0C
#define XMSSMT_SHA2_40_8_512     0x0D
#define XMSSMT_SHA2_60_3_512     0x0E
#define XMSSMT_SHA2_60_6_512     0x0F
#define XMSSMT_SHA2_60_12_512    0x10
#define XMSSMT_SHAKE_20_2_256    0x11
#define XMSSMT_SHAKE_20_4_256    0x12
#define XMSSMT_SHAKE_40_2_256    0x13
#define XMSSMT_SHAKE_40_4_256    0x14
#define XMSSMT_SHAKE_40_8_256    0x15
#define XMSSMT_SHAKE_60_3_256    0x16
#define XMSSMT_SHAKE_60_6_256    0x17
#define XMSSMT_SHAKE_60_12_256   0x18
#define XMSSMT_SHAKE_20_2_512    0x19
#define XMSSMT_SHAKE_20_4_512    0x1A
#define XMSSMT_SHAKE_40_2_512    0x1B
#define XMSSMT_SHAKE_40_4_512    0x1C
#define XMSSMT_SHAKE_40_8_512    0x1D
#define XMSSMT_SHAKE_60_3_512    0x1E
#define XMSSMT_SHAKE_60_6_512    0x1F
#define XMSSMT_SHAKE_60_12_512   0x20

uint32_t get_xmss_type(uint32_t ots_type, uint32_t height);
uint32_t get_xmss_mt_type(uint32_t ots_type, uint32_t height, uint32_t layer);

uint32_t py_xmss_pk_size(int type);
uint32_t py_xmss_sk_size(int type);
uint32_t py_xmss_sig_size(int type);

int py_xmss_keygen(void *sk, void *pk, const void *seed, int type);
int py_xmss_sign(void *sm, void *sk, const void *msg, uint32_t mlen, int type);
int py_xmss_verify(const void *sig, const void *msg, uint32_t mlen, const void *pk);

uint32_t py_xmssmt_pk_size(int type);
uint32_t py_xmssmt_sk_size(int type);
uint32_t py_xmssmt_sig_size(int type);

int py_xmssmt_keygen(void *sk, void *pk, const void *seed, int type);
int py_xmssmt_sign(void *sm, void *sk, const void *msg, uint32_t mlen, int type);
int py_xmssmt_verify(const void *sig, const void *msg, uint32_t mlen, const void *pk);

#endif
