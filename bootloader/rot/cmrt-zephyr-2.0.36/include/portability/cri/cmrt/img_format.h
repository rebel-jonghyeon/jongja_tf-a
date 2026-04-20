/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file img_format.h
 *
 * @brief Define CMRT image headers and footers.
 */

#ifndef CRI_IMG_FORMAT_H
#define CRI_IMG_FORMAT_H

#include <stdint.h>
#include <stdbool.h>
#include <cri/cmrt/omc_reg.h>
#include <cri/cmrt/kdc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

#if __SIZEOF_SIZE_T__ != 8
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wpadded"
#endif

/*
 * Flash header can precede image headers in the beginning of the Flash.
 * These definitions are used to support primary and secondary images.
 */
typedef struct {
	uint32_t magic;     /* id and version */
	uint32_t flags;     /* must be zero */
	uint32_t primary;   /* offset to primary image, zero for adjacent */
	uint32_t secondary; /* offset to secondary image, zero for none */
} cri_flash_header_t;

#define CMRT_FHDR_MAGIC 0x43464832UL /* CFH2 in ascii, 2 is the version */

static inline bool cri_is_valid_fhdr(const cri_flash_header_t *fhdr)
{
	return (fhdr != NULL) && (fhdr->magic == CMRT_FHDR_MAGIC);
}

/*
 * Image header is filesystem metadata but will be in front of an image
 * in Flash, for example, if the Flash has no real filesystem.
 */
typedef struct {
	uint32_t length;
} cri_img_header_t;

/*
 * Sboot header is similar but we have the inverse of the length
 * in the upper half because sboot is only protected by a digest.
 */
typedef struct {
	uint16_t length;
	uint16_t mirror;
} cri_sboot_header_t;

/*
 * All the rest from here on is for image footer.
 */
#define CAVEAT_NONE 0u
#define CAVEAT_SILO 1u
#define CAVEAT_BOOT 2u

typedef struct {
	cmrt_omc_root_id_t root;
	uint32_t handling_caveats;
} cri_container_id_t;

typedef struct {
	cri_container_id_t cid;
	uint32_t scid;
} cri_container_scid_t;

typedef struct {
	cri_container_id_t cid;
	uint32_t scid_min;
	uint32_t scid_max;
} cri_container_range_t;

enum cri_image_key_src {
	CRI_IMAGE_KEY_SRC_IPC = 0,
	CRI_IMAGE_KEY_SRC_KDC = 1
};

enum cri_image_keysplit_id {
	CRI_IMAGE_KEYSPLIT_DGOK = KEY_ID_DGOK,
	CRI_IMAGE_KEYSPLIT_BNAK = KEY_ID_BNAK,
	CRI_IMAGE_KEYSPLIT_SNAK = KEY_ID_SNAK,
	CRI_IMAGE_KEYSPLIT_PNAK = KEY_ID_PNAK,
	CRI_IMAGE_KEYSPLIT_1 = KEY_ID_OTP_KEYSPLIT+1,
	CRI_IMAGE_KEYSPLIT_2 = KEY_ID_OTP_KEYSPLIT+2,
	CRI_IMAGE_KEYSPLIT_3 = KEY_ID_OTP_KEYSPLIT+3,
	CRI_IMAGE_KEYSPLIT_4 = KEY_ID_OTP_KEYSPLIT+4,
	CRI_IMAGE_KEYSPLIT_5 = KEY_ID_OTP_KEYSPLIT+5,
	CRI_IMAGE_KEYSPLIT_6 = KEY_ID_OTP_KEYSPLIT+6,
	CRI_IMAGE_KEYSPLIT_7 = KEY_ID_OTP_KEYSPLIT+7,
};

typedef struct cri_encryption_data {
	uint32_t version;
	enum cri_image_key_src key_src;
	uint8_t iv[12];
	uint8_t tag[16];
	enum cri_image_keysplit_id keysplit_id;
	uint32_t diversify_path;
} cri_encryption_data_t;

#define PK_UNSIGNED 0UL
#define PL_UNSIGNED 0UL /* no key */
#define SL_UNSIGNED 0UL

#define PK_ECDSA_P256 1UL
#define PL_ECDSA_P256 64UL /* X, Y */
#define SL_ECDSA_P256 64UL

#define PK_HMAC_SHA256 2UL
#define PL_HMAC_SHA256 4UL /* 1 word of key id */
#define SL_HMAC_SHA256 32UL

#define PK_ECDSA_P521 3UL
#define PL_ECDSA_P521 132UL /* X, Y */
#define SL_ECDSA_P521 132UL

#define PK_RSAPSS_3K 4UL
#define PL_RSAPSS_3K 768UL /* modulus, exponent */
#define SL_RSAPSS_3K 384UL

#define PK_RSAPSS_4K 5UL
#define PL_RSAPSS_4K 1024UL /* modulus, exponent */
#define SL_RSAPSS_4K 512UL

#define PK_SHA256 6UL
#define PL_SHA256 0UL /* no key */
#define SL_SHA256 32UL

#ifndef CONFIG_CMRT_V1
#define METADATA_VERSION 1UL
#define METADATA_LENGTH (sizeof(uint32_t) + sizeof(cri_container_scid_t) + sizeof(uint32_t) + sizeof(cmrt_omc_root_perm_t))
#define MAXSIZEOF_PUBLIC_KEY PL_RSAPSS_4K
#define MAXSIZEOF_SIGNATURE SL_RSAPSS_4K
#define MINSIZEOF_FOOTER (METADATA_LENGTH + sizeof(uint32_t) * 5u)
#endif

typedef struct {
	uint32_t metadata_length;
	uint32_t metadata_version;
	cri_container_scid_t *scid;
	uint32_t container_version;
	cmrt_omc_root_perm_t permissions;
	uint32_t encryption_length;
	cri_encryption_data_t *encryption_data;
	uint32_t public_key_type;
	uint32_t public_key_length;
	uint8_t *public_key;
	uint32_t signature_length;
	uint8_t *signature;
	uint32_t footer_length;
} cri_img_footer_t;

typedef struct {
	uint32_t text_start;
	uint32_t text_end;
	uint32_t rodata_start;
	uint32_t rodata_end;
	uint32_t data_start;
	uint32_t data_end;
	uint32_t bss_start;
	uint32_t bss_end;
	uint32_t noinit_start;
	uint32_t noinit_end;
	uint32_t entry_point;
	uint32_t load_address;
	uint32_t verlen; /* just length of footer in first version */
} raw_image_footer_t;

#ifndef CONFIG_CMRT_V1
#define RAW_ADDR_FIELDS 12u /* from text_start to load_address */
#define RAW_SECT_FIELDS 10u /* from text_start to noinit_end */
#endif

typedef struct {
	uint32_t text_metadata;
	uint32_t verlen; /* just length of footer in first version */
} cri_cfi_footer_t;

#if __SIZEOF_SIZE_T__ != 8
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
