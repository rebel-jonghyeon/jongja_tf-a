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

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include <cri/cmrt/omc.h>
#include <cri/cmrt/omc_reg.h>
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

static int32_t check_root_id(uint8_t *hash, int root_id)
{
	int32_t res;

	cmrt_omc_root_t root;

	cri_otp_t omc = cri_otp_open(0);
	if (!cri_is_valid(omc)) {
			dprintk("Failed to open omc\n");
			return -EACCES;
	}

	res = cri_otp_read_root(omc, root_id, &root);
	if (res != 0) {
		dprintk("Cannot read root: %d\n", res);
		res = -EACCES;
		goto direct_exit;
	}

	res = memcmp(hash, root.id.hash, 32);
	if (res) {
		res = -EPERM;
		goto direct_exit;
	}

direct_exit:
	cri_otp_close(omc);
	return res;
}

int32_t fips_login(fips_state_t *state,
		teec_abi_header_t *h)
{
	int32_t status = 0;
	uint32_t total_length = sizeof(uint32_t);

	teec_abi_opensession_t *session_command = (teec_abi_opensession_t *) h;

	CHECK_COMMAND(FIPS_SERVICE_LOGIN_FINAL);

	switch (session_command->params[0].value.b) {
#if 0
	/* disabling anonymous login for future use */
	case FIPS_ROLE_INVALID_PK:
		dprintk("Anonymous login\n");

		if ((session_command->params[0].value.a != FIPS_OWNER_ANONYMOUS) ||
			(TEEC_PARAM_TYPE_GET(h->param_types, 1) != TEEC_NONE) ||
			(TEEC_PARAM_TYPE_GET(h->param_types, 2) != TEEC_NONE) ||
			(TEEC_PARAM_TYPE_GET(h->param_types, 3) != TEEC_NONE)) {
			status = -EINVAL;
			goto direct_exit;
		}
		state->user = FIPS_OWNER_ANONYMOUS;
		state->user_session = 1;
		status = 0;
		((uint32_t *)workcontext)[0] = 0;
		break;
#endif
	case FIPS_ROLE_ECDSA_P256_PK:
		dprintk("Authenticated login\n");
		uint8_t *mytestkey = (uint8_t *) (SAC_MEMORY_BASE + session_command->params[1].memref.offset) ;

		if ((session_command->params[0].value.a == FIPS_OWNER_ANONYMOUS) ||
			(session_command->params[2].memref.size != 16) ||
			(session_command->params[3].memref.size != 16) ||
			(session_command->params[1].memref.size != 68) ||
			(session_command->params[0].value.a < FIPS_OWNER_CRYPTO_OFFICER) ||
			(session_command->params[0].value.a > FIPS_OWNER_USER_5)) {
			status = -EINVAL;
			goto direct_exit;
		}

		dprintk("Setting up the HASH\n");
		/*requested_root_id = SHA256(params[0].value.b | params[1].memref.offset.x | params[1].memref.offset.y)*/
		uint32_t *tmp;
		uint8_t *dataarray;
		tmp = (uint32_t *) workcontext;
		tmp[0] = (uint32_t) FIPS_SERVICE_LOGIN_INIT;
		hash_work_struct *sha = (hash_work_struct *)(workcontext + 4);
		dataarray = (uint8_t *)(workcontext + 4 + sizeof(hash_work_struct));
		uint8_t *hash = (uint8_t *)(workcontext + 4 + sizeof(hash_work_struct) + 68);
		sha->hashtype = FIPS_HASH_SHA256;
		sha->hashlen = 32;
		memcpy(dataarray, &(session_command->params[0].value.b), 4);
		memcpy(dataarray+4, mytestkey+4, 32);
		memcpy(dataarray+4+32, mytestkey+36, 32);
		total_length = 4 + sizeof(hash_work_struct) + 68 + 32;

		status = cri_hash(sha, dataarray, 68, hash, 32, FIPS_HC_1);
		if (status) {
			goto direct_exit;
		}
		dprintk("Checking root ID\n");
		status = check_root_id(hash, session_command->params[0].value.a);
		if (status) {
			dprintk("Public key is not valid.");
			status = -EINVAL;
			goto direct_exit;
		}

		/* generate randomness */
		dprintk("Creating randomness\n");
		status = cri_get_randomness((uint8_t *) (SAC_MEMORY_BASE + session_command->params[3].memref.offset), session_command->params[3].memref.size);
		if (status) {
			dprintk("Randomness generation failed\n");
			goto direct_exit;
		}

		dprintk("Caching parameters\n");
		/* cache the necessary parameters */
		tmp = (uint32_t *) (workcontext + 4);
		tmp[0] = session_command->params[0].value.a;
		tmp[1] = session_command->params[0].value.b;
		fips_ecdsa_public_key *pubkey = (fips_ecdsa_public_key *) (workcontext + 12);
		pubkey->curve_type = CRI_ECC_CURVE_NIST_P256;
		fips_ecdsa_public_key_components *pubkey_comp = &(pubkey->public_key);
		pubkey_comp->x = (uint8_t *) (workcontext + 12 + sizeof(fips_ecdsa_public_key));
		pubkey_comp->y = (uint8_t *) (workcontext + 12 + sizeof(fips_ecdsa_public_key) + 32);
		memcpy(pubkey_comp->x, mytestkey+4, 32);
		memcpy(pubkey_comp->y, mytestkey+36, 32);
		/* prep input for the hash */
		uint8_t *strt = (uint8_t *) (workcontext + 12 + sizeof(fips_ecdsa_public_key) + 64);
		uint32_t datalen = 0;
		strt += 4;
		reverse_endian_words(&(session_command->params[0].value.a), 1, strt);
		datalen += 4;
		strt += 4;
		memcpy(strt, (uint8_t *) (SAC_MEMORY_BASE + session_command->params[2].memref.offset), session_command->params[2].memref.size);
		datalen += session_command->params[2].memref.size;
		strt += session_command->params[2].memref.size;
		memcpy(strt, (uint8_t *) (SAC_MEMORY_BASE + session_command->params[3].memref.offset), session_command->params[3].memref.size);
		datalen += session_command->params[3].memref.size;
		strt += session_command->params[3].memref.size;
		/* role_pk_type = keyid in LE */
		memcpy(strt, &(session_command->params[0].value.b), 4);
		datalen += 4;
		strt += 4;
		memcpy(strt, pubkey_comp->x, 32);
		datalen += 32;
		strt += 32;
		memcpy(strt, pubkey_comp->y, 32);
		datalen += 32;
		strt += 32;
		memcpy((uint32_t *) (workcontext + 12 + sizeof(fips_ecdsa_public_key) + 64), &datalen, 4);

		state->user = session_command->params[0].value.a;
		state->authenticated_login_started = 1;
		break;
	default:
		dprintk("Wrong service request %d\n", session_command->params[0].value.b);
		status = -EPERM;
		goto direct_exit;
	}

	goto out;

direct_exit:
	destroy_workcontext(total_length);
	dprintk("Returning the status %d\n", status);
out:
	return status;
}

int32_t fips_service_login_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{
/*	digest = SHA256(role | nonceclient | noncecmrt | role_pk_type | role_pk)
	signature = ecdsa_sign(role_private, digest) */

	int32_t status;
	uint32_t total_length = 0;

	uint32_t *tmp;
	tmp = (uint32_t *) workcontext;
	if ((tmp[0] != (uint32_t) FIPS_SERVICE_LOGIN_INIT) || (state->authenticated_login_started != 1)) {
		status = -EPERM;
		goto direct_exit;
	}

	if (h->params[0].memref.size != 64) {
		status = -EINVAL;
		goto direct_exit;
	}

	hash_work_struct sha;
	sha.hashtype = FIPS_HASH_SHA256;
	sha.hashlen = 32;
	uint8_t hash[32];
	uint8_t *dataarray = (uint8_t *) (workcontext + 12 + sizeof(fips_ecdsa_public_key) + 64);
	size_t len = ((uint32_t *) dataarray)[0];
	total_length = 12 + sizeof(fips_ecdsa_public_key) + 64 + len;
	status = cri_hash(&sha, dataarray+4, len, hash, sha.hashlen, FIPS_HC_1);
	if (status) {
		goto direct_exit;
	}
	fips_ecdsa_public_key *pubkey = (fips_ecdsa_public_key *) (workcontext + 12);
	fips_ecdsa_public_key_components *pubkey_comp = &(pubkey->public_key);
	uint8_t *rp = dataarray + sha.hashlen;

	cri_ecc_curve_t curve = cri_pke_get_curve(pubkey->curve_type);
	if (!curve) {
		dprintk("Failed to obtain a curve\n");
		status = -EIO;
		goto direct_exit;
	}
	total_length += cri_pke_get_curve_length(curve);

	status = cri_ecdsa_verify(curve, (uint8_t *) (SAC_MEMORY_BASE + h->params[0].memref.offset), (uint8_t *) (SAC_MEMORY_BASE + h->params[0].memref.offset + 32),
			pubkey_comp->x, pubkey_comp->y, hash, sha.hashlen, rp);
	if (status) {
		dprintk("Status of ecdsa_verify: %d\n", status);
		goto direct_exit;
	}

	if (memcmp((uint8_t *) (SAC_MEMORY_BASE + h->params[0].memref.offset), rp, cri_pke_get_curve_length(curve)) != 0) {
		dprintk("Verify failed\n");
		status = -EPERM;
		goto direct_exit;
	}

	state->user_session = 1;
	state->authenticated_login_started = 0;

direct_exit:
	destroy_workcontext(total_length);
	return status;
}

int32_t fips_logout(fips_state_t *state,
		teec_abi_header_t *h)
{
	int32_t status = 0;

	fips_intialize_state(state);

	return status;
}
