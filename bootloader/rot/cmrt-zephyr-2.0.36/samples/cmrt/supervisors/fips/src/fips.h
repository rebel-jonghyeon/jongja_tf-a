/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_FIPS_H
#define CMRT_FIPS_H

#include <stdint.h>
#include <stddef.h>

#include <cri/cmrt/fips/fips_types.h>

#include "cmvp_sw.h"
#include <tee_client_api.h> /* TEEC_MEMREF values */
#include <tee_client_abi.h>

#include <cri/cmrt.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/aes.h>

#define SHA_BUF_MAX_SIZE 64
#define PTR_SIZE 4

typedef struct {
	uint8_t user;
	uint8_t teec_session;
	uint8_t user_session;
	uint8_t authenticated_login_started;
	uint8_t approved_mode;
	uint32_t key_length;
	uint8_t *key_value;
	uint8_t *scratch;
	uint8_t do_reset;
} fips_state_t;

typedef struct {
	fips_asset *asset;
	fips_aes_key *key;
	uint8_t *keyvalue;
} aeskey_work_struct;

typedef struct {
	aeskey_work_struct aeskey;
	uint8_t *IV;
	uint32_t IVlen;
	cri_aes_t aesengine;
	uint32_t direction;
	uint32_t taglen;
} aes_work_struct;

typedef struct {
	uint32_t hashtype;
	uint32_t hashlen;
	uint8_t hash_buffer[SHA_BUF_MAX_SIZE];
	uint32_t buffer_offset;
	cri_hc_t hashengine;
} hash_work_struct;

typedef struct {
	fips_asset *asset;
	fips_hmac_key *key; /* also used for AES CMAC with cast */
	uint8_t *keyvalue;
} mackey_work_struct;

typedef struct {
	mackey_work_struct mackey;
	hash_work_struct sha;
	aes_work_struct aes;
} mac_work_struct;

typedef struct {
	aes_work_struct aeskey;
	uint8_t *scratch;
} import_work_struct;

typedef struct {
	aes_work_struct aeskey;
	fips_asset *outkey;
	uint8_t *scratch;
} export_work_struct;

void fips_intialize_state(fips_state_t *state);

int32_t fips_login(fips_state_t *state, teec_abi_header_t *h);
int32_t fips_logout(fips_state_t *state, teec_abi_header_t *h);
int32_t fips_service_login_final(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_service_command(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t get_approved_mode(fips_command operation, uint8_t *approved_mode);
uint32_t fips_get_permissions(fips_owner_user user, fips_command operation);

#define FIPS_DENIED 0
#define FIPS_READ 1
#define FIPS_WRITE 2
uint32_t fips_get_asset_permissions(fips_owner_user session_user,
		fips_owner_user asset_owner);

#define FIPS_IMPORT 0
#define FIPS_EXPORT 1
int32_t fips_key_import_export(fips_state_t *state, teec_abi_invokecommand_t *h, uint8_t direction);
/*int32_t fips_key_import(fips_state_t *state, teec_abi_invokecommand_t *h);*/
int32_t fips_key_export(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_service_export_ktc(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t get_randomness_int(uint8_t *buffer, size_t size);
int32_t fips_get_randomness(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_generate_symmetric_key(fips_state_t *state, teec_abi_invokecommand_t *h);

#define DERIVE_KEY_ONE_STEP 1
#define DERIVE_KEY_TWO_STEP 2
int32_t fips_derive_symmetric_key(fips_state_t *state, teec_abi_invokecommand_t *h, uint8_t step);

int32_t fips_aes_ecb(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cbc_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cbc_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cbc_final(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_gcm_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_gcm_aad_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_gcm_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_gcm_encrypt_final(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_gcm_decrypt_final(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_ctr_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_ctr_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_ctr_final(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cfb128_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cfb128_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_aes_cfb128_final(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t hash_int(hash_work_struct *sha, uint8_t *in_dataarray, size_t inlen, uint8_t *out_hash, size_t outlen);
int32_t fips_hash_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_hash_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_hash_final(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_mac_gen_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_mac_update(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_mac_gen_final(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_mac_ver_init(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_mac_ver_final(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_create_user(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_delete_user(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_ec_generate_key(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_ecdsa_sign(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_ecdsa_verify(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_ecdsa_pk_test(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_ecdh(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_selftest(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_rsa_generate_keypair(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_rsa_sign(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_rsa_verify(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_move_asset(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_zeroize_assets(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_list_asset_service(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_show_status(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_drbg(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_is_fips_asset_location(int asset);
int32_t fips_is_fips_direction(int direction);
int32_t fips_is_valid_tag_length(uint32_t length);
int32_t fips_asset_to_buffer(fips_asset *asset, uint8_t *inout_buffer,
		uint32_t *inout_buffer_len);
int32_t buffer_to_fips_asset(uint8_t *inout_buffer,
		uint32_t *inout_buffer_len, uint8_t *destination,
		uint8_t *workcontext_buffer);
int32_t fips_check_valid_asset_size_ext(fips_asset_type type, size_t checksize);
int32_t fips_check_valid_key_length(fips_asset_type type, size_t checksize);

void destroy_workcontext(int32_t length);
void destroy_workcontext_and_halt(int32_t status);
int32_t destroy_workcontext_and_reset(fips_state_t *state);

int32_t test_otp(void);

int32_t fips_dilithium_generate_keypair(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_dilithium_sign(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_dilithium_verify(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_kyber_kem_generate_keypair(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_kyber_kem_encapsultate(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_kyber_kem_decapsultate(fips_state_t *state, teec_abi_invokecommand_t *h);

int32_t fips_lms_verify(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_hss_verify(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_xmss_verify(fips_state_t *state, teec_abi_invokecommand_t *h);
int32_t fips_xmss_mt_verify(fips_state_t *state, teec_abi_invokecommand_t *h);

#endif
