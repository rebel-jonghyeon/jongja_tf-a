/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file img_format.h
 *
 * @brief Define CMRT image headers and footers.
 */

#ifndef CMRT_IMG_FORMAT_H
#define CMRT_IMG_FORMAT_H

#include <stdint.h>
#include <stdbool.h>
#include <drivers/cmrt/omc_reg.h>
#include <drivers/cmrt/kdc_reg.h>

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
} cmrt_flash_header_t;

#define CMRT_FHDR_MAGIC 0x43464832UL /* CFH2 in ascii, 2 is the version */

static inline bool cmrt_is_valid_fhdr(const cmrt_flash_header_t *fhdr)
{
	return (((uintptr_t)fhdr & 0x3u) == 0u) &&
		(fhdr != NULL) && (fhdr->magic == CMRT_FHDR_MAGIC);
}

/*
 * Image header is metadata in front of an image. Mirror field is one's
 * complement of the length to prevent image modifications in ROM/OTP.
 */
typedef struct {
	uint32_t length;
	uint32_t mirror;
} cmrt_img_header_t;

static inline bool cmrt_is_valid_hdr(const cmrt_img_header_t *hdr, size_t maxsize)
{
	return (((uintptr_t)hdr & 0x3u) == 0u) && (hdr->length != 0u) &&
		(hdr->length <= maxsize) && ((hdr->length & 0x3u) == 0u) &&
		(hdr->length == ~hdr->mirror);
}

/*
 * All the rest from here on is for image footer.
 */
#define CAVEAT_NONE 0u
#define CAVEAT_SILO 1u
#define CAVEAT_BOOT 2u

typedef struct {
	cmrt_omc_root_id_t root;
	uint32_t handling_caveats;
} cmrt_container_id_t;

typedef struct {
	cmrt_container_id_t cid;
	uint32_t scid;
} cmrt_container_scid_t;

typedef struct {
	cmrt_container_id_t cid;
	uint32_t scid_min;
	uint32_t scid_max;
} cmrt_container_range_t;

enum cmrt_image_key_src {
	CMRT_IMAGE_KEY_SRC_DS = 0,
	CMRT_IMAGE_KEY_SRC_KDC = 1
};

enum cmrt_image_keysplit_id {
	CMRT_IMAGE_KEYSPLIT_DGOK = KEY_ID_DGOK,
	CMRT_IMAGE_KEYSPLIT_BNAK = KEY_ID_BNAK,
	CMRT_IMAGE_KEYSPLIT_SNAK = KEY_ID_SNAK,
	CMRT_IMAGE_KEYSPLIT_PNAK = KEY_ID_PNAK,
	CMRT_IMAGE_KEYSPLIT_1 = KEY_ID_OTP_KEYSPLIT+1,
	CMRT_IMAGE_KEYSPLIT_2 = KEY_ID_OTP_KEYSPLIT+2,
	CMRT_IMAGE_KEYSPLIT_3 = KEY_ID_OTP_KEYSPLIT+3,
	CMRT_IMAGE_KEYSPLIT_4 = KEY_ID_OTP_KEYSPLIT+4,
	CMRT_IMAGE_KEYSPLIT_5 = KEY_ID_OTP_KEYSPLIT+5,
	CMRT_IMAGE_KEYSPLIT_6 = KEY_ID_OTP_KEYSPLIT+6,
	CMRT_IMAGE_KEYSPLIT_7 = KEY_ID_OTP_KEYSPLIT+7,
};

typedef struct cmrt_encryption_data {
	uint32_t version;
	enum cmrt_image_key_src key_src;
	uint8_t iv[12];
	uint8_t tag[16];
	enum cmrt_image_keysplit_id keysplit_id;
	uint32_t diversify_path;
} cmrt_encryption_data_t;

/* PK: private key type
 * PL: public key size (bytes)
 * SL: signature size (bytes) */
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

#define PK_LMS             7UL
#define PL_LMS            56UL /* 4(type) + 4(otstype) + 16(I) + 32(root_hash) */
#define SL_LMS_MIN      1292UL /* 4(q) + 1124(ots_sig) + 4(type) + 32(path) * 5(h) */
#define SL_LMS_MAX      9324UL /* 4(q) + 8516(ots_sig) + 4(type) + 32(path) * 25(h) */

#define PK_LMS_HSS         8UL
#define PL_LMS_HSS        60UL /* 4(level) + 4(type) + 4(otstype) + 16(I) + 32(root_hash) */
#define SL_LMS_HSS_MIN  2644UL /* lms_sha256_n32_h5 lms_sha256_n32_h5, lmots_sha256_n32_w8 lmots_sha256_n32_w8 */
#define SL_LMS_HSS_MAX 18708UL /* lms_sha256_n32_h25 lms_sha256_n32_h25, lmots_sha256_n32_w1 lmots_sha256_n32_w1 */

#define PK_XMSS            9UL
#define PL_XMSS_256       68UL
#define PL_XMSS_512      132UL
#define SL_XMSS_MIN     2500UL /* XMSS_SHA2_10_256, XMSS_SHAKE_16_256 */
#define SL_XMSS_MAX     9732UL /* XMSS_SHA2_20_512, XMSS_SHAKE_20_512 */

#define PK_XMSS_MT         10UL
#define PL_XMSS_MT_256     68UL
#define PL_XMSS_MT_512    132UL
#define SL_XMSS_MT_MIN   4963UL /* XMSSMT_SHA2_20_2_256, XMSSMT_SHAKE_20_2_256 */
#define SL_XMSS_MT_MAX 104520UL /* XMSSMT_SHA2_60_12_512, XMSSMT_SHAKE_60_12_512 */


#define PK_ECDSA_P384 11UL
#define PL_ECDSA_P384 96UL /* X, Y */
#define SL_ECDSA_P384 96UL

#define METADATA_VERSION 1UL
#define METADATA_LENGTH (sizeof(uint32_t) + sizeof(cmrt_container_scid_t) + sizeof(uint32_t) + sizeof(cmrt_omc_root_perm_t))

#define MAXSIZEOF_PUBLIC_KEY PL_RSAPSS_4K

#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
#define MAXSIZEOF_SIGNATURE SL_XMSS_MT_MAX
#elif defined(CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY)
#define MAXSIZEOF_SIGNATURE SL_LMS_HSS_MAX
#elif CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
#define MAXSIZEOF_SIGNATURE SL_XMSS_MAX
#elif defined(CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY)
#define MAXSIZEOF_SIGNATURE SL_LMS_MAX
#else
#define MAXSIZEOF_SIGNATURE SL_RSAPSS_4K
#endif

#define MINSIZEOF_FOOTER (METADATA_LENGTH + sizeof(uint32_t) * 5u)

typedef struct {
	uint32_t metadata_length;
	uint32_t metadata_version;
	cmrt_container_scid_t scid;
	uint32_t container_version;
	cmrt_omc_root_perm_t permissions;
	uint32_t encryption_length;
	cmrt_encryption_data_t *encryption_data;
	uint32_t public_key_type;
	uint32_t public_key_length;
	uint8_t *public_key;
	uint32_t signature_length;
	uint8_t *signature;
	uint32_t footer_length;
} cmrt_img_footer_t;

typedef struct {
	uint32_t text_start;
	uint32_t text_end;
	uint32_t rodata_start;
	uint32_t rodata_end;
	uint32_t bss_start;
	uint32_t bss_end;
	uint32_t noinit_start;
	uint32_t noinit_end;
	uint32_t data_start;
	uint32_t data_end;
	uint32_t entry_point;
	uint32_t load_address;
	uint32_t relocation_offset;
	uint32_t verlen; /* just length of footer in first version */
} cmrt_raw_footer_t;

#define RAW_ADDR_FIELDS 13u /* from text_start to relocate_offset */
#define RAW_SECT_FIELDS 10u /* from text_start to noinit_end */

typedef struct {
	uint32_t stack_size;
	uint32_t global_pointer;
	uint32_t relo_start;
	uint32_t relo_end;
	uint32_t got_start;
	uint32_t got_end;
	uint32_t verlen; /* just length of footer in first version */
} cmrt_usr_footer_t;

typedef struct {
	uint32_t meta_start;
	uint32_t meta_end;
	uint32_t verlen; /* just length of footer in first version */
} cmrt_cfi_footer_t;

#if __SIZEOF_SIZE_T__ != 8
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
