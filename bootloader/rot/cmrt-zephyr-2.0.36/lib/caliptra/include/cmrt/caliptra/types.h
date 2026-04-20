/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_TYPES_H
#define CMRT_CALIPTRA_TYPES_H
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SECP384R1 key length */
#define CMRT_CALIPTRA_KEY_LEN (384UL / 8UL)

/* SHA384, used all over */
#define CMRT_CALIPTRA_HASH_LEN (384UL / 8UL)

#define CMRT_CALIPTRA_DEVICE_ID_LEN 12UL
#define CMRT_CALIPTRA_OEM_ID_LEN 8UL

/* Length of the UDS (and its seed) */
#define CMRT_CALIPTRA_UDS_LEN (384UL / 8UL)

#define CMRT_CALIPTRA_FIELD_ENTROPY_LEN 32UL
#define CMRT_CALIPTRA_FIELD_ENTROPY_SLOTS 4UL

/* Maximum length of the IDevID cert chain in OTP. */
#define CMRT_CALIPTRA_IDEVID_CHAIN_MAX_LEN 4096

/* Length of a root id */
#define CMRT_CALIPTRA_ROOT_ID_LEN (256UL / 8UL)

/* Length of the sboot hash */
#define CMRT_CALIPTRA_SBOOT_HASH_LEN (256UL / 8UL)

/* UDS (unique device secret). */
typedef struct cmrt_caliptra_uds {
	alignas(4) uint8_t value[CMRT_CALIPTRA_UDS_LEN];
} cmrt_caliptra_uds_t;

/* A field entropy slot. */
typedef struct cmrt_caliptra_field_entropy {
	alignas(4) uint8_t value[CMRT_CALIPTRA_FIELD_ENTROPY_LEN];
} cmrt_caliptra_field_entropy_t;

/* P-384 private key. */
typedef struct cmrt_caliptra_privkey {
	alignas(4) uint8_t priv[CMRT_CALIPTRA_KEY_LEN];
} cmrt_caliptra_privkey_t;

/* P-384 public key. */
typedef struct cmrt_caliptra_pubkey {
	alignas(4) uint8_t x[CMRT_CALIPTRA_KEY_LEN];
	alignas(4) uint8_t y[CMRT_CALIPTRA_KEY_LEN];
} cmrt_caliptra_pubkey_t;

/* SHA2-384 digest. */
typedef struct cmrt_caliptra_digest {
	alignas(4) uint8_t digest[CMRT_CALIPTRA_HASH_LEN];
} cmrt_caliptra_digest_t;

/* Device information that appears in the Caliptra certificates. */
typedef struct cmrt_caliptra_deviceinfo {
	uint8_t device_id[CMRT_CALIPTRA_DEVICE_ID_LEN];
	uint8_t oem_id[CMRT_CALIPTRA_OEM_ID_LEN];
} cmrt_caliptra_deviceinfo_t;

/* Caliptra layer identities. */
typedef enum cmrt_caliptra_id {
	CMRT_CALIPTRA_ID_IDevID = 1,
	CMRT_CALIPTRA_ID_LDevID = 2,
	CMRT_CALIPTRA_ID_AliasFMC = 3,
	CMRT_CALIPTRA_ID_AliasRT = 4,
} cmrt_caliptra_id_t;

#ifdef __cplusplus
}
#endif
#endif
