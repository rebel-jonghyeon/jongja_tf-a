/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_X509_H
#define CMRT_CALIPTRA_X509_H
#include <stdint.h>
#include <stdalign.h>
#include <stddef.h>
#include <cmrt/caliptra/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	/* An estimated upper bound on the size of certificates
	 * produced.
	 */
	CMRT_CALIPTRA_MAX_DER_LEN = 1024,
};

/* TCB (trusted computing base) information appearing in DICE
 * certificates.
 */
typedef struct cmrt_caliptra_tcbinfo {
	/* Version identifier of the TCB layer. */
	const char *version;
	size_t version_len;
	/* Identifiers (hash digest) of firmware components in the TCB layer. */
	const cmrt_caliptra_digest_t **fwids;
	size_t fwids_len;
	/* Layer number (0 = ROM, 1 = FMC, 2 = RT, ...) */
	int8_t layer;
	/* Whether the layer is running with debugging enabled. */
	bool debug_mode;
} cmrt_caliptra_tcbinfo_t;

/* Caliptra DICE TCB layer identity and keypair. */
typedef struct cmrt_caliptra_tcb {
	cmrt_caliptra_id_t identity;
	const cmrt_caliptra_privkey_t *privkey;
	const cmrt_caliptra_pubkey_t *pubkey;
} cmrt_caliptra_tcb_t;

/* Parameters for CSR generation. */
typedef struct cmrt_caliptra_csr_params {
	/* DICE TCB layer for which the CSR is generated */
	const cmrt_caliptra_tcb_t *subject;
	/* Device information */
	const cmrt_caliptra_deviceinfo_t *deviceinfo;
	/* List of TCB component information */
	const cmrt_caliptra_tcbinfo_t *tcbinfos;
	size_t tcbinfos_len;
} cmrt_caliptra_csr_params_t;

/* Parameters for certificate generation. */
typedef struct cmrt_caliptra_cert_params {
	/* DICE TCB layer of the issuer */
	const cmrt_caliptra_tcb_t *issuer;
	/* DICE TCB layer of the subject */
	const cmrt_caliptra_tcb_t *subject;
	/* Device information */
	const cmrt_caliptra_deviceinfo_t *deviceinfo;
	/* List of TCB component information */
	const cmrt_caliptra_tcbinfo_t *tcbinfos;
	size_t tcbinfos_len;
} cmrt_caliptra_cert_params_t;

/**
 * Write a CSR based on @a params to @a buf.
 *
 * @param buf buffer to hold the DER-encoded CSR
 * @param[inout] len length of @a buf at entry, length of the CSR on return
 * @param params parameters required for the CSR
 * @return 0 on success, -1 on error
 */
int cmrt_caliptra_write_csr(void *buf, size_t *len,
			    const cmrt_caliptra_csr_params_t *params);

/**
 * Write an X.509 certificate based on @a params to @a buf.
 *
 * @param buf buffer to hold the DER-encoded certificate
 * @param[inout] len length of @a buf at entry, length of the certificate on return
 * @param params parameters required for the certificate
 * @return 0 on success, -1 on error
 */
int cmrt_caliptra_write_cert(void *buf, size_t *len,
			     const cmrt_caliptra_cert_params_t *params);

#ifdef __cplusplus
}
#endif
#endif
