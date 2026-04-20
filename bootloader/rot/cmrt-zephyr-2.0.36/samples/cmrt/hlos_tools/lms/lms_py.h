#ifndef LMS_PY_H
#define LMS_PY_H

#include <stdint.h>

uint32_t py_lms_sig_size(uint32_t lms_type, uint32_t ots_type);
uint32_t py_lms_hss_sig_size(int levels, const uint32_t *types, const uint32_t *otstypes);
void py_lms_keygen(void *sk, void *pk, const void *seed, uint32_t lms_type, uint32_t ots_type);
void py_lms_sign(void *sig, void *sk, const void *msg, uint32_t mlen, uint32_t lms_type, uint32_t ots_type);
int py_lms_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen);
void py_lms_hss_keygen(void *sk, void *pk, const void *seed, const uint32_t *lms_types, const uint32_t *ots_types, uint32_t levels);
void py_lms_hss_sign(void *sk, void *sig, int levels, const uint32_t *types, const uint32_t *otstypes, const void *msg, uint32_t mlen);
int py_lms_hss_verify(const void *sig, const void *pk, const void *msg, uint32_t mlen);

#endif
