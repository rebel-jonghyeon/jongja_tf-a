/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <smcalls.h>
#include <teedev_dmac.h>
#include <sac.h>

#include <cri/cmrt/sic.h>

#include <tee_client_api.h> /* TEEC_MEMREF values */
#include <tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "fips_asset.h"
#include "cmvp_sw.h"

int32_t fips_service_command(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	fips_command service_command = (fips_command) ((teec_abi_header_t *) h)->cmdres;

	if (service_command == FIPS_SERVICE_LOGIN_FINAL) {
		dprintk("FIPS_SERVICE_LOGIN_FINAL\n");

		if (state->user_session) {
			dprintk("There is an open session");
			status = -EINVAL;
			goto direct_exit;
		}

		if (!state->authenticated_login_started) {
			dprintk("Authenticated login not started");
			status = -EINVAL;
			goto direct_exit;
		}

		if (!fips_get_permissions(state->user, FIPS_SERVICE_LOGIN_FINAL)) {
			dprintk("Permission denied");
			status = -EACCES;
			goto direct_exit;
		}

		get_approved_mode(FIPS_SERVICE_LOGIN_FINAL, &state->approved_mode);

		status = fips_service_login_final(state, h);

		goto direct_exit;
	}

	if (!state->user_session) {
		dprintk("No open session");
		status = -EINVAL;
		goto direct_exit;
	}

	if (!fips_get_permissions(state->user, service_command)) {
		dprintk("Permission denied");
		status = -EACCES;
		goto direct_exit;
	}

	get_approved_mode(service_command, &state->approved_mode);

	switch (service_command) {
	case FIPS_SERVICE_CREATE_USER:
		dprintk("FIPS_SERVICE_CREATE_USER\n");
		status = fips_create_user(state, h);
		break;

	case FIPS_SERVICE_DELETE_USER:
		dprintk("FIPS_SERVICE_DELETE_USER\n");
		status = fips_delete_user(state, h);
		break;

	case FIPS_SERVICE_GEN_SYMM_KEY:
		dprintk("FIPS_SERVICE_GEN_SYMM_KEY\n");
		status = fips_generate_symmetric_key(state, h);
		break;

	case FIPS_SERVICE_DERIVE_SYMM_KEY:
		dprintk("FIPS_SERVICE_DERIVE_SYMM_KEY\n");
		status = fips_derive_symmetric_key(state, h, DERIVE_KEY_ONE_STEP);
		break;

	case FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP:
		dprintk("FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP\n");
		status = fips_derive_symmetric_key(state, h, DERIVE_KEY_TWO_STEP);
		break;

	case FIPS_SERVICE_GEN_EC_KEYPAIR:
		dprintk("FIPS_SERVICE_GEN_EC_KEYPAIR\n");
		status = fips_ec_generate_key(state, h);
		break;

	case FIPS_SERVICE_GEN_RSA_KEYPAIR:
		dprintk("FIPS_SERVICE_GEN_RSA_KEYPAIR\n");
		status = fips_rsa_generate_keypair(state, h);
		break;

	case FIPS_SERVICE_IMPORT_KEY:
		dprintk("FIPS_SERVICE_IMPORT_KEY\n");
		status = fips_key_import_export(state, h, FIPS_IMPORT);
		break;

	case FIPS_SERVICE_EXPORT_KEY:
		dprintk("FIPS_SERVICE_EXPORT_KEY\n");
		status = fips_key_import_export(state, h, FIPS_EXPORT);
		break;

	case FIPS_SERVICE_EXPORT_KEY_KTC:
		dprintk("FIPS_SERVICE_EXPORT_KEY_KTC\n");
		status = fips_service_export_ktc(state, h);
		break;

	case FIPS_SERVICE_AES_ECB:
		dprintk("FIPS_SERVICE_AES_ECB\n");
		status = fips_aes_ecb(state, h);
		break;

	case FIPS_SERVICE_AES_GCM_INIT:
		dprintk("FIPS_SERVICE_AES_GCM_INIT\n");
		status = fips_aes_gcm_init(state, h);
		break;

	case FIPS_SERVICE_AES_GCM_AAD_UPDATE:
		dprintk("FIPS_SERVICE_AES_GCM_AAD_UPDATE\n");
		status = fips_aes_gcm_aad_update(state, h);
		break;

	case FIPS_SERVICE_AES_GCM_UPDATE:
		dprintk("FIPS_SERVICE_AES_GCM_UPDATE\n");
		status = fips_aes_gcm_update(state, h);
		break;

	case FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL:
		dprintk("FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL\n");
		status = fips_aes_gcm_encrypt_final(state, h);
		break;

	case FIPS_SERVICE_AES_GCM_DECRYPT_FINAL:
		dprintk("FIPS_SERVICE_AES_GCM_DECRYPT_FINAL\n");
		status = fips_aes_gcm_decrypt_final(state, h);
		break;

	case FIPS_SERVICE_AES_CBC_INIT:
		dprintk("FIPS_SERVICE_AES_CBC_INIT\n");
		status = fips_aes_cbc_init(state, h);
		break;

	case FIPS_SERVICE_AES_CBC_UPDATE:
		dprintk("FIPS_SERVICE_AES_CBC_UPDATE\n");
		status = fips_aes_cbc_update(state, h);
		break;

	case FIPS_SERVICE_AES_CBC_FINAL:
		dprintk("FIPS_SERVICE_AES_CBC_FINAL\n");
		status = fips_aes_cbc_final(state, h);
		break;

	case FIPS_SERVICE_AES_CTR_INIT:
		dprintk("FIPS_SERVICE_AES_CTR_INIT\n");
		status = fips_aes_ctr_init(state, h);
		break;

	case FIPS_SERVICE_AES_CTR_UPDATE:
		dprintk("FIPS_SERVICE_AES_CTR_UPDATE\n");
		status = fips_aes_ctr_update(state, h);
		break;

	case FIPS_SERVICE_AES_CTR_FINAL:
		dprintk("FIPS_SERVICE_AES_CTR_FINAL\n");
		status = fips_aes_ctr_final(state, h);
		break;

	case FIPS_SERVICE_AES_CFB128_INIT:
		dprintk("FIPS_SERVICE_AES_CFB128_INIT\n");
		status = fips_aes_cfb128_init(state, h);
		break;

	case FIPS_SERVICE_AES_CFB128_UPDATE:
		dprintk("FIPS_SERVICE_AES_CFB128_UPDATE\n");
		status = fips_aes_cfb128_update(state, h);
		break;

	case FIPS_SERVICE_AES_CFB128_FINAL:
		dprintk("FIPS_SERVICE_AES_CFB128_FINAL\n");
		status = fips_aes_cfb128_final(state, h);
		break;

	case FIPS_SERVICE_ECDSA_SIGN:
		dprintk("FIPS_SERVICE_ECDSA_SIGN\n");
		status = fips_ecdsa_sign(state, h);
		break;

	case FIPS_SERVICE_ECDSA_VERIFY:
		dprintk("FIPS_SERVICE_ECDSA_VERIFY\n");
		status = fips_ecdsa_verify(state, h);
		break;

	case FIPS_SERVICE_ECDSA_PK_TEST:
		dprintk("FIPS_SERVICE_ECDSA_PK_TEST\n");
		status = fips_ecdsa_pk_test(state, h);
		break;

	case FIPS_SERVICE_ECDH:
		dprintk("FIPS_SERVICE_ECDH\n");
		status = fips_ecdh(state, h);
		break;

	case FIPS_SERVICE_RSA_SIGN:
		dprintk("FIPS_SERVICE_RSA_SIGN\n");
		status = fips_rsa_sign(state, h);
		break;

	case FIPS_SERVICE_RSA_VERIFY:
		dprintk("FIPS_SERVICE_RSA_VERIFY\n");
		status = fips_rsa_verify(state, h);
		break;

	case FIPS_SERVICE_MAC_GEN_INIT:
		dprintk("FIPS_SERVICE_MAC_GEN_INIT\n");
		status = fips_mac_gen_init(state, h);
		break;

	case FIPS_SERVICE_MAC_GEN_FINAL:
		dprintk("FIPS_SERVICE_MAC_GEN_FINAL\n");
		status = fips_mac_gen_final(state, h);
		break;

	case FIPS_SERVICE_MAC_VERIFY_INIT:
		dprintk("FIPS_SERVICE_MAC_VERIFY_INIT\n");
		status = fips_mac_ver_init(state, h);
		break;

	case FIPS_SERVICE_MAC_VERIFY_FINAL:
		dprintk("FIPS_SERVICE_MAC_VERIFY_FINAL\n");
		status = fips_mac_ver_final(state, h);
		break;

	case FIPS_SERVICE_MAC_UPDATE:
		dprintk("FIPS_SERVICE_MAC_UPDATE\n");
		status = fips_mac_update(state, h);
		break;

	case FIPS_SERVICE_HASH_INIT:
		dprintk("FIPS_SERVICE_HASH_INIT\n");
		status = fips_hash_init(state, h);
		break;

	case FIPS_SERVICE_HASH_UPDATE:
		dprintk("FIPS_SERVICE_HASH_UPDATE\n");
		status = fips_hash_update(state, h);
		break;

	case FIPS_SERVICE_HASH_FINAL:
		dprintk("FIPS_SERVICE_HASH_FINAL\n");
		status = fips_hash_final(state, h);
		break;

	case FIPS_SERVICE_GET_TRNG:
		dprintk("FIPS_SERVICE_GET_TRNG\n");
		status = fips_get_randomness(state, h);
		break;

	case FIPS_SERVICE_LIST_ASSETS:
		dprintk("FIPS_SERVICE_LIST_ASSETS\n");
		status = fips_list_asset_service(state, h);
		break;

	case FIPS_SERVICE_MOVE_ASSET:
		dprintk("FIPS_SERVICE_MOVE_ASSET\n");
		status = fips_move_asset(state, h);
		break;

	case FIPS_DELETE_DYNAMIC_ASSET:
		dprintk("FIPS_DELETE_DYNAMIC_ASSET\n");
		status = fips_delete_asset(state, h, FIPS_ASSET_DYNAMIC);
		break;

	case FIPS_DELETE_STATIC_ASSET:
		dprintk("FIPS_DELETE_STATIC_ASSET\n");
		status = fips_delete_asset(state, h, FIPS_ASSET_STATIC);
		break;

	case FIPS_SERVICE_ZEROIZE:
		dprintk("FIPS_SERVICE_ZEROIZE\n");
		status = fips_zeroize_assets(state, h);
		break;

	case FIPS_SERVICE_SELF_TEST:
		dprintk("FIPS_SERVICE_SELF_TEST\n");
		status = fips_selftest(state, h);
		break;

	case FIPS_SERVICE_RESET:
		dprintk("FIPS_SERVICE_RESET\n");
		status = destroy_workcontext_and_reset(state);
		break;

	case FIPS_SERVICE_SHOW_STATUS:
		dprintk("FIPS_SERVICE_SHOW_STATUS\n");
		status = fips_show_status(state, h);
		break;

	case FIPS_SERVICE_DRBG:
		dprintk("FIPS_SERVICE_DRBG\n");
		status = fips_drbg(state, h);
		break;
#ifdef CONFIG_CMRT_SHSIG_LMS
	case FIPS_SERVICE_LMS_VERIFY:
		dprintk("FIPS_SERVICE_LMS_VERIFY\n");
		status = fips_lms_verify(state, h);
		break;
#endif
#ifdef CONFIG_CMRT_SHSIG_LMS_HSS
	case FIPS_SERVICE_HSS_VERIFY:
		dprintk("FIPS_SERVICE_HSS_VERIFY\n");
		status = fips_hss_verify(state, h);
		break;
#endif
#ifdef CONFIG_CMRT_SHSIG_XMSS
	case FIPS_SERVICE_XMSS_VERIFY:
		dprintk("FIPS_SERVICE_XMSS_VERIFY\n");
		status = fips_xmss_verify(state, h);
		break;
#endif
#ifdef CONFIG_CMRT_SHSIG_XMSS_MT
	case FIPS_SERVICE_XMSSMT_VERIFY:
		dprintk("FIPS_SERVICE_XMSSMT_VERIFY\n");
		status = fips_xmss_mt_verify(state, h);
		break;
#endif
	default:
		dprintk("FIPS_SERVICE_INVALID_COMMAND\n");
		status = -EINVAL;
	}

direct_exit:
	dprintk("Returning the status %d\n", status);
	return status;
}
