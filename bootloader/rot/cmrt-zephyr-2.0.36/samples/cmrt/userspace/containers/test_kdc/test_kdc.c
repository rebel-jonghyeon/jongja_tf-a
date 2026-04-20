/*
 * Copyright (c) 2022-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/pke.h>

#define BUFSZ 4096
#define TMPBUFSZ 512
#define ECDH_MAX_KEY_SIZE 66

/* Global variables. */
static size_t _keylen;
static size_t _ivlen;
static size_t _taglen;
static size_t _aadlen;
static size_t _datalen;
static uint32_t _curve_id_ecdh = 0;

static cmrt_aes_mode_t _mode_aes = -1;
static cmrt_aes_operation_t _op_aes = -1;
static cmrt_hash_algo_t _algo_hc = -1;

/* Global buffer for receive and response messages from SIC. */
static alignas(4) uint8_t buffer[BUFSZ + AES_BLOCK_BYTES /* some slack */];

/* Global buffer for intermediate computations such as storing encoded AAD (bn)
 * for ccm mode. */
static alignas(4) uint8_t tmp_buf[TMPBUFSZ];

/* Global buffer for the AES IV */
static alignas(4) uint8_t iv_aes[AES_BLOCK_BYTES];

/* Global buffer for ECDH */
static alignas(4) uint8_t pub_x_ecdh[ECDH_MAX_KEY_SIZE] = {0};
static alignas(4) uint8_t priv_key_ecdh[ECDH_MAX_KEY_SIZE] = {0};

/* Global aes, hc, and ecdh contexts */
static cmrt_aes_t aes = CMRT_INVALID_HANDLE;
static cmrt_hc_t hc = CMRT_INVALID_HANDLE;
static cmrt_pke_t pke = CMRT_INVALID_HANDLE;

static void print_usage(void)
{
	LOG_INF("First message:      AES|HC|ECDH [MODE|OP] [ALGO|CORE] [DATALEN] [KEYSIZE] [CURVE] KEY [DIV_PATH]");
	LOG_INF("Next message(s):    AES|HC|ECDH update|final|aad|private|public DATA");
	LOG_INF("MODE (AES):         ecb|cbc|cfb|ctr|gcm|ccm|cmac|xts");
	LOG_INF("OP (AES):           encrypt|decrypt");
	LOG_INF("ALGO (HC):          sha-224|sha-256|sha-384|sha-512|sha-512_224|sha-512_256|");
	LOG_INF("                    sha3-224|sha3-256|sha3-384|sha3-512|shake128|shake256|whirlpool");
	LOG_INF("CORE (HC):          s2hc|s3hc|cshc|whc");
	LOG_INF("DATALEN (AES GCM):  total data that will be used in AES GCM");
	LOG_INF("KEYSIZE (AES|HC):   16|32");
	LOG_INF("KEY (AES|HC|ECDH):  DGOK|BNAK|SNAK|PNAK");
	LOG_INF("CURVE (ECDH):       NIST_P192|NIST_P224|NIST_P256|NIST_P384|NIST_P521|Bp_P192R1|");
	LOG_INF("                    Bp_P224R1|Bp_P256R1|Bp_P320R1|Bp_P384R1|Bp_P512R1|Bp_P192T1|");
	LOG_INF("                    Bp_P224T1|Bp_P256T1|Bp_P320T1|Bp_P384T1|Bp_P512T1|X25519|");
	LOG_INF("                    X448|FRP_256V1");
	LOG_INF("DIV_PATH (ECDH):    diversity path to differentiate between user key and peer key (any value)");
	LOG_INF("DATA (AES|HC|ECDH): ascii or binary (no hex encoding)\n");
}

/*
 * yet to find a home...
 */
static inline uint32_t argl_init(uint8_t **argpp)
{
	const uint32_t argl = **(uint32_t**)argpp;
	*argpp += sizeof(uint32_t);
	return argl;
}

static inline uint32_t argl_next(uint8_t **argpp, uint32_t argl)
{
	*argpp += ((argl + 3) & ~3);
	argl = **(uint32_t**)argpp;
	*argpp += sizeof(uint32_t);
	return argl;
}

static const struct {
	const char *str;
	cmrt_aes_mode_t mode;
} cmd_aes_mode[] = {
	{ "ecb", CMRT_AES_ECB },
	{ "cbc", CMRT_AES_CBC },
	{ "cfb", CMRT_AES_CFB },
	{ "ctr", CMRT_AES_CTR },
	{ "gcm", CMRT_AES_GCM },
	{ "cmac", CMRT_AES_CMAC },
	{ "ccm", CMRT_AES_CCM },
	{ "xts", CMRT_AES_XTS }
};

static const struct {
	const char *str;
	cmrt_aes_operation_t op;
} cmd_aes_op[] = {
	{ "encrypt", CMRT_AES_ENCRYPT },
	{ "decrypt", CMRT_AES_DECRYPT }
};

static const struct {
	const char *str;
	cmrt_hash_algo_t algo;
} cmd_hc_algo[] = {
	{ "sha-224", CMRT_HASH_SHA224 },
	{ "sha-256", CMRT_HASH_SHA256 },
	{ "sha-384", CMRT_HASH_SHA384 },
	{ "sha-512_224", CMRT_HASH_SHA512_224 },
	{ "sha-512_256", CMRT_HASH_SHA512_256 },
	{ "sha-512", CMRT_HASH_SHA512 },
	{ "sha3-224", CMRT_HASH_SHA3_224 },
	{ "sha3-256", CMRT_HASH_SHA3_256 },
	{ "sha3-384", CMRT_HASH_SHA3_384 },
	{ "sha3-512", CMRT_HASH_SHA3_512 },
	{ "shake128", CMRT_HASH_SHAKE128 },
	{ "shake256", CMRT_HASH_SHAKE256 },
	{ "whirlpool", CMRT_HASH_WHIRLPOOL },
};

static const char *cmd_hc_core[] = { "s2hc", "s3hc", "cshc", "whc" };

static const struct {
	const char *str;
	uint32_t curve_id;
} cmd_ecdh_curve[] = {
	{ "NIST_P192", CMRT_ECC_CURVE_NIST_P192 },
	{ "NIST_P224", CMRT_ECC_CURVE_NIST_P224 },
	{ "NIST_P256", CMRT_ECC_CURVE_NIST_P256 },
	{ "NIST_P384", CMRT_ECC_CURVE_NIST_P384 },
	{ "NIST_P521", CMRT_ECC_CURVE_NIST_P521 },
	{ "Bp_P192R1", CMRT_ECC_CURVE_BRAINPOOL_P192R1 },
	{ "Bp_P224R1", CMRT_ECC_CURVE_BRAINPOOL_P224R1 },
	{ "Bp_P256R1", CMRT_ECC_CURVE_BRAINPOOL_P256R1 },
	{ "Bp_P320R1", CMRT_ECC_CURVE_BRAINPOOL_P320R1 },
	{ "Bp_P384R1", CMRT_ECC_CURVE_BRAINPOOL_P384R1 },
	{ "Bp_P512R1", CMRT_ECC_CURVE_BRAINPOOL_P512R1 },
	{ "Bp_P192T1", CMRT_ECC_CURVE_BRAINPOOL_P192T1 },
	{ "Bp_P224T1", CMRT_ECC_CURVE_BRAINPOOL_P224T1 },
	{ "Bp_P256T1", CMRT_ECC_CURVE_BRAINPOOL_P256T1 },
	{ "Bp_P320T1", CMRT_ECC_CURVE_BRAINPOOL_P320T1 },
	{ "Bp_P384T1", CMRT_ECC_CURVE_BRAINPOOL_P384T1 },
	{ "Bp_P512T1", CMRT_ECC_CURVE_BRAINPOOL_P512T1 },
	{ "X25519", CMRT_ECC_CURVE_25519 },
	{ "X448", CMRT_ECC_CURVE_448 },
	{ "FRP_256V1", CMRT_ECC_CURVE_ANSSI_FRP256V1 },
};

static const struct {
	const char *str;
	uint32_t base_key_id;
} cmd_kdc_type[] = {
	{ "DGOK", KEY_ID_DGOK },
	{ "BNAK", KEY_ID_BNAK },
	{ "SNAK", KEY_ID_SNAK },
	{ "PNAK", KEY_ID_PNAK },
};

static size_t get_keylen_by_curve_id(uint32_t curve_id)
{
	switch (curve_id) {
	case CMRT_ECC_CURVE_NIST_P192:
	case CMRT_ECC_CURVE_BRAINPOOL_P192R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P192T1:
		return 24;
	case CMRT_ECC_CURVE_NIST_P224:
	case CMRT_ECC_CURVE_BRAINPOOL_P224R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P224T1:
		return 28;
	case CMRT_ECC_CURVE_NIST_P256:
	case CMRT_ECC_CURVE_BRAINPOOL_P256R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P256T1:
	case CMRT_ECC_CURVE_ANSSI_FRP256V1:
	case CMRT_ECC_CURVE_25519:
		return 32;
	case CMRT_ECC_CURVE_BRAINPOOL_P320R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P320T1:
		return 40;
	case CMRT_ECC_CURVE_NIST_P384:
	case CMRT_ECC_CURVE_BRAINPOOL_P384R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P384T1:
		return 48;
	case CMRT_ECC_CURVE_448:
		return 56;
	case CMRT_ECC_CURVE_BRAINPOOL_P512R1:
	case CMRT_ECC_CURVE_BRAINPOOL_P512T1:
		return 64;
	case CMRT_ECC_CURVE_NIST_P521:
		return 66;
	}

	return 0;
}

static void reset_static_vars(void)
{
	_keylen = _ivlen = _taglen = _aadlen = _datalen = 0;
	_mode_aes = -1;
	_op_aes = -1,
	_algo_hc = -1;
	aes = CMRT_INVALID_HANDLE;
	hc = CMRT_INVALID_HANDLE;
	pke = CMRT_INVALID_HANDLE;
	memset(buffer, sizeof(buffer), 0);
	memset(tmp_buf, sizeof(tmp_buf), 0);
	memset(iv_aes, sizeof(iv_aes), 0);
	memset(pub_x_ecdh, sizeof(pub_x_ecdh), 0);
	memset(priv_key_ecdh, sizeof(priv_key_ecdh), 0);
}

static int aes_open(void)
{
	aes = cmrt_aes_open(CMRT_O_HWC_KEYED);
	if (!cmrt_is_valid(aes)) {
		LOG_ERR("Cannot open AES context!");
		return -1;
	}
	LOG_INF("aes core opened");
	return 0;
}

static void aes_close(void)
{
	if (cmrt_is_valid(aes)) {
		LOG_INF("Closing AES context (resets state)");
		cmrt_aes_close(aes);
		reset_static_vars();
	}
}

static int hc_open(const char *core)
{
	hc = cmrt_hc_open(core, CMRT_O_HWC_KEYED);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Cannot open HC context!");
		return -1;
	}
	LOG_INF("hc core opened");
	return 0;
}

static void hc_close(void)
{
	if (cmrt_is_valid(hc)) {
		LOG_INF("Closing HC context (resets state)");
		cmrt_hc_close(hc);
		reset_static_vars();
	}
}

static int derive(cmrt_kdc_cmd_t *kdc_cmd)
{
	int res = -1;
	cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_SYNC);
	if (cmrt_is_valid(kdc)) {
		res = cmrt_kdc_derive_key(kdc, kdc_cmd);
		LOG_INF("Closing KDC context (resets state)");
		cmrt_kdc_close(kdc);
	} else {
		LOG_ERR("Cannot open KDC context!");
	}
	return res;
}

static int pke_open(void)
{
	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PEK context!");
		return -1;
	}
	LOG_INF("pke core opened");
	return 0;
}

static void pke_close(void)
{
	if (cmrt_is_valid(pke)) {
		LOG_INF("Closing PKE context (resets state)");
		cmrt_pke_close(pke);
		reset_static_vars();
	}
}

static int process_init_aes(uint8_t *argp, uint32_t argl)
{
	int res = 0;
	size_t keylen = 0;
	size_t taglen = 0;
	size_t ivlen = 0;
	uint8_t *iv = iv_aes;
	uint32_t datalen = 0;
	static const char diversify_path[] = "it's magic";

	cmrt_kdc_cmd_t kdc_cmd = {
		.diversify_len = strlen(diversify_path) + 1,
		.base_key_id = 0xffffffff
	};

	memcpy(kdc_cmd.diversify_path, diversify_path, strlen(diversify_path));

	/* Get MODE parameter */
	for (size_t i = 0; i < sizeof(cmd_aes_mode) / sizeof(*cmd_aes_mode); i++) {
		if (memcmp(argp, cmd_aes_mode[i].str, argl) == 0
			&& cmd_aes_mode[i].str[argl] == '\0') {
			LOG_INF("MODE: %s", cmd_aes_mode[i].str);
			_mode_aes = cmd_aes_mode[i].mode;
			break;
		}
	}
	if (_mode_aes == (cmrt_aes_mode_t)-1) {
		argp[argl] = '\0';
		LOG_ERR("Invalid MODE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get OP parameter */
	for (size_t i = 0; i < sizeof(cmd_aes_op) / sizeof(*cmd_aes_op); i++) {
		if (memcmp(argp, cmd_aes_op[i].str, argl) == 0
			&& cmd_aes_op[i].str[argl] == '\0') {
			LOG_INF("OP: %s", cmd_aes_op[i].str);
			_op_aes = cmd_aes_op[i].op;
			break;
		}
	}
	if (_op_aes == (cmrt_aes_operation_t)-1) {
		argp[argl] = '\0';
		LOG_ERR("Invalid OP %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	if (_mode_aes == CMRT_AES_CCM) {
		/* Get DATALEN parameter */
		if (argl != 4) {
			argp[argl] = '\0';
			LOG_ERR("Invalid DATALEN %s", (char *)argp);
			return -EINVAL;
		}
		datalen = *((uint32_t*) argp);
		LOG_INF("init datalen: %lu", datalen);
		argl = argl_next(&argp, argl);
	}


	/* Get KEYSIZE parameter */
	if (memcmp(argp, "16", argl) == 0) {
		LOG_INF("KEYSIZE: %d", 16);
		keylen = 16;
	} else if (memcmp(argp, "32", argl) == 0) {
		LOG_INF("KEYSIZE: %d", 32);
		keylen = 32;
	} else {
		argp[argl] = '\0';
		LOG_ERR("Invalid KEYSIZE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get KEY parameter */
	for (size_t i = 0; i < sizeof(cmd_kdc_type) / sizeof(*cmd_kdc_type); i++) {
		if (memcmp(argp, cmd_kdc_type[i].str, argl) == 0
			&& cmd_kdc_type[i].str[argl] == '\0') {
			LOG_INF("KEY: %s", cmd_kdc_type[i].str);
			kdc_cmd.base_key_id = cmd_kdc_type[i].base_key_id;
			break;
		}
	}
	if (kdc_cmd.base_key_id == 0xffffffff) {
		argp[argl] = '\0';
		LOG_ERR("Invalid KEY %s", (char *)argp);
		return -EINVAL;
	}

	/* Manage different AES modes */
	if (_mode_aes == CMRT_AES_ECB) {
		iv = NULL;
		ivlen = 0;
		taglen = 0;
	} else if ((_mode_aes == CMRT_AES_CBC) ||
		   (_mode_aes == CMRT_AES_CTR) ||
		   (_mode_aes == CMRT_AES_CFB)) {
		ivlen = AES_BLOCK_BYTES;
		taglen = 0;
	} else if (_mode_aes == CMRT_AES_GCM) {
		ivlen = 12;
		taglen = 12;
	} else if (_mode_aes == CMRT_AES_CMAC) {
		iv = NULL;
		ivlen = 0;
		taglen = AES_BLOCK_BYTES;
	} else if (_mode_aes == CMRT_AES_CCM) {
		ivlen = 12;
		taglen = 12;
		res = cmrt_aes_ccm_encode_nonce(tmp_buf, sizeof(tmp_buf),
						iv, ivlen, datalen, taglen, 1);
		if (res < 0) {
			LOG_ERR("Cannot encode aes ccm nonce: %d", res);
			return res;
		}
		ivlen = res;
		iv = tmp_buf;
	} else if (_mode_aes == CMRT_AES_XTS) {
		LOG_ERR("AES XTS mode currently not supported");
		return -EINVAL;
	}

	res = aes_open();
	if (res) {
		return res;
	}
	res = cmrt_aes_kdc_cmd(aes, _op_aes, _mode_aes,
				keylen, taglen, &kdc_cmd);
	if (res) {
		LOG_ERR("Cannot init kdc cmd: %d", res);
		return res;
	}
	LOG_INF("Starting KDC derivation...");
	res = derive(&kdc_cmd);
	if (res) {
		LOG_ERR("Cannot derive kdc key: %d", res);
		return res;
	}
	memset(&iv_aes, 0, sizeof(iv_aes));
	res = cmrt_aes_init(aes, _op_aes, _mode_aes, NULL, 0,
				iv, ivlen, taglen);
	if (res) {
		LOG_ERR("Cannot init aes: %d", res);
		return res;
	}

	return res;
}

static int process_update_aes_cmac(uint8_t *data, uint32_t datalen, size_t *outlen)
{
	int res = 0;

	res = cmrt_aes_update_aad(aes, data, datalen);
	if (res) {
		LOG_ERR("Cannot do aes cmac update aad: %d", res);
	}

	*outlen = 0;
	return res;

}

static int process_update_aes(uint8_t *data, uint32_t datalen, uint8_t *out, size_t *outlen)
{
	int res = 0;

	switch (_mode_aes) {
	case CMRT_AES_CMAC:
		res = process_update_aes_cmac(data, datalen, outlen);
		break;
	case CMRT_AES_XTS:
		LOG_ERR("XTS mode not implemented.");
		res = -EINVAL;
		*outlen = 0;
		break;
	default:
		res = cmrt_aes_update(aes, data, datalen, out);
		*outlen = datalen;
		if (res) {
			LOG_ERR("Cannot do aes update: %d", res);
			*outlen = 0;
		}
		break;
	}

	return res;
}

static int process_final_aes(uint8_t *data, uint32_t datalen, uint8_t *out, size_t *outlen)
{
	int res = 0;

	if (_mode_aes == CMRT_AES_GCM || _mode_aes == CMRT_AES_CCM) {
		LOG_INF("datalen: %lu", datalen);
		if (_op_aes == CMRT_AES_ENCRYPT) {
			/* Retrieve the tag */
			res = cmrt_aes_ae_final(aes, data, datalen, out,
						out + datalen, outlen);
			*outlen += datalen;
		} else if (_op_aes == CMRT_AES_DECRYPT) {
			/* Pass in the tag */
			if (datalen < 12) {
				LOG_ERR("Provided %lu bytes of data, +12 are needed", datalen);
			}
			LOG_HEXDUMP_DBG(data, datalen - 12, "data:");
			LOG_HEXDUMP_DBG(data + datalen - 12, 12, "tag:");
			*outlen = 12;
			res = cmrt_aes_ae_final(aes, data, datalen - 12, out,
						data + datalen - 12, outlen);
			*outlen = datalen - 12;
		} else {
			LOG_ERR("Wrong aes operation: %d", (int) _op_aes);
			*outlen = 0;
			res = -1;
		}
	} else if (_mode_aes == CMRT_AES_CMAC) {
		res = cmrt_aes_final_aad(aes, data, datalen);
		if (res) {
			LOG_ERR("Cannot do aes cmac final aad: %d", res);
			*outlen = 0;
			return res;
		}
		res = cmrt_aes_ae_final(aes, NULL, 0, NULL, out, outlen);
		*outlen = 16;
	} else {
		res = cmrt_aes_final(aes, data, datalen, out);
		*outlen = datalen;
	}

	if (res) {
		LOG_ERR("Cannot do aes final: %d", res);
		*outlen = 0;
	}

	return res;
}

static int process_aad_aes(uint8_t *data, uint32_t datalen)
{
	int res = 0;

	if (_mode_aes == CMRT_AES_CCM) {
		res = cmrt_aes_ccm_encode_aad(tmp_buf, sizeof(tmp_buf), data, datalen);
		if (res < 0) {
			LOG_ERR("Cannot encode aad: %d", res);
			return res;
		}
		data = tmp_buf;
		datalen = res;
	}

	res = cmrt_aes_final_aad(aes, data, datalen);
	if (res) {
		LOG_ERR("Cannot do aes final aad: %d", res);
	}

	return res;

}

static int process_message_aes(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	if (!cmrt_is_valid(aes)) {
		/* Core is not open, this must be init. */
		LOG_INF("Stage: init");
		res = process_init_aes(argp, argl);
		*outlen = 0;
	} else {
		if (memcmp(argp, "update", argl) == 0) {
			LOG_INF("Stage: update");
			argl = argl_next(&argp, argl);
			res = process_update_aes(argp, argl, out, outlen);
		} else if (memcmp(argp, "final", argl) == 0) {
			LOG_INF("Stage: final");
			argl = argl_next(&argp, argl);
			res = process_final_aes(argp, argl, out, outlen);
			aes_close();
		} else if (memcmp(argp, "aad", argl) == 0) {
			LOG_INF("Stage: aad");
			argl = argl_next(&argp, argl);
			res = process_aad_aes(argp, argl);
			*outlen = 0;
		} else {
			LOG_ERR("Stage: not valid");
			*outlen = 0;
			res = -1;
		}
	}

	if (res) {
		aes_close();
	}

	return res;
}

static int process_init_hc(uint8_t *argp, uint32_t argl)
{
	int res = 0;
	int _core_idx_hc = -1;
	size_t keylen = 0;
	static const char diversify_path[] = "it's magic";

	cmrt_kdc_cmd_t kdc_cmd = {
		.diversify_len = strlen(diversify_path) + 1,
		.base_key_id = 0xffffffff
	};

	memcpy(kdc_cmd.diversify_path, diversify_path, strlen(diversify_path));

	/* Get ALGO parameter */
	for (size_t i = 0; i < sizeof(cmd_hc_algo) / sizeof(*cmd_hc_algo); i++) {
		if (memcmp(argp, cmd_hc_algo[i].str, argl) == 0
			&& cmd_hc_algo[i].str[argl] == '\0') {
			LOG_INF("ALGO: %s", cmd_hc_algo[i].str);
			_algo_hc = cmd_hc_algo[i].algo;
			break;
		}
	}
	if (_algo_hc == (cmrt_hash_algo_t)-1) {
		argp[argl] = '\0';
		LOG_ERR("Invalid ALGO %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get CORE parameter */
	for (size_t i = 0; i < sizeof(cmd_hc_core) / sizeof(*cmd_hc_core); i++) {
		if (memcmp(argp, cmd_hc_core[i], argl) == 0
			&& cmd_hc_core[i][argl] == '\0') {
			LOG_INF("CORE: %s", cmd_hc_core[i]);
			_core_idx_hc = i;
			break;
		}
	}
	if (_core_idx_hc == -1) {
		argp[argl] = '\0';
		LOG_ERR("Invalid CORE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get KEYSIZE parameter */
	if (memcmp(argp, "16", argl) == 0) {
		LOG_INF("KEYSIZE: %d", 16);
		keylen = 16;
	} else if (memcmp(argp, "32", argl) == 0) {
		LOG_INF("KEYSIZE: %d", 32);
		keylen = 32;
	} else {
		argp[argl] = '\0';
		LOG_ERR("Invalid KEYSIZE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get KEY parameter */
	for (size_t i = 0; i < sizeof(cmd_kdc_type) / sizeof(*cmd_kdc_type); i++) {
		if (memcmp(argp, cmd_kdc_type[i].str, argl) == 0
			&& cmd_kdc_type[i].str[argl] == '\0') {
			LOG_INF("KEY: %s", cmd_kdc_type[i].str);
			kdc_cmd.base_key_id = cmd_kdc_type[i].base_key_id;
			break;
		}
	}
	if (kdc_cmd.base_key_id == 0xffffffff) {
		argp[argl] = '\0';
		LOG_ERR("Invalid KEY %s", (char *)argp);
		return -EINVAL;
	}
	res = hc_open(cmd_hc_core[_core_idx_hc]);
	if (res) {
		return res;
	}
	res = cmrt_hc_kdc_cmd(hc, _algo_hc, keylen, &kdc_cmd);
	if (res) {
		LOG_ERR("Cannot init kdc cmd: %d", res);
		return res;
	}
	LOG_INF("Starting KDC derivation...");
	res = derive(&kdc_cmd);
	if (res) {
		LOG_ERR("Cannot derive kdc key: %d", res);
		return res;
	}
	res = cmrt_hc_init(hc, _algo_hc, NULL, 0);
	if (res) {
		LOG_ERR("Cannot init hc: %d", res);
		return res;
	}

	return res;
}

static int process_update_hc(uint8_t *data, uint32_t datalen)
{
	int res = 0;

	res = cmrt_hc_update(hc, data, datalen);
	if (res) {
		LOG_ERR("Cannot do hc update: %d", res);
	}

	return res;
}

static int process_final_hc(uint8_t *data, uint32_t datalen, uint8_t *out, size_t *outlen)
{
	int res = 0;

	res = cmrt_hc_final(hc, data, datalen, out, outlen);
	if (res) {
		LOG_ERR("Cannot do hc final: %d", res);
	}

	return res;
}

static int process_message_hc(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	if (!cmrt_is_valid(hc)) {
		/* Core is not open, this must be init. */
		LOG_INF("Stage: init");
		hc_close();
		res = process_init_hc(argp, argl);
		*outlen = 0;
	} else {
		if (memcmp(argp, "update", argl) == 0) {
			LOG_INF("Stage: update");
			argl = argl_next(&argp, argl);
			res = process_update_hc(argp, argl);
			*outlen = 0;
		} else if (memcmp(argp, "final", argl) == 0) {
			LOG_INF("Stage: final");
			argl = argl_next(&argp, argl);
			res = process_final_hc(argp, argl, out, outlen);
			hc_close();
		} else {
			LOG_ERR("Stage: not valid");
			res = -1;
		}
	}

	if (res) {
		hc_close();
	}

	return res;
}

static int process_keygen_ecdh(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	size_t keylen = 0;

	cmrt_kdc_cmd_t kdc_cmd = {
		.diversify_len = 0xf,
		.base_key_id = 0xffffffff,
		.dest = KDC_DEST_SW
	};

	*outlen = 0;

	/* Get CURVE parameter */
	_curve_id_ecdh = 0;
	for (size_t i = 0; i < sizeof(cmd_ecdh_curve) / sizeof(*cmd_ecdh_curve); i++) {
		if (memcmp(argp, cmd_ecdh_curve[i].str, argl) == 0
			&& cmd_ecdh_curve[i].str[argl] == '\0') {
			LOG_INF("CURVE: %s", cmd_ecdh_curve[i].str);
			_curve_id_ecdh = cmd_ecdh_curve[i].curve_id;
			break;
		}
	}
	if (_curve_id_ecdh == 0) {
		argp[argl] = '\0';
		LOG_ERR("Invalid CURVE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get KEY parameter */
	for (size_t i = 0; i < sizeof(cmd_kdc_type) / sizeof(*cmd_kdc_type); i++) {
		if (memcmp(argp, cmd_kdc_type[i].str, argl) == 0
			&& cmd_kdc_type[i].str[argl] == '\0') {
			LOG_INF("KEY: %s", cmd_kdc_type[i].str);
			kdc_cmd.base_key_id = cmd_kdc_type[i].base_key_id;
			break;
		}
	}
	if (kdc_cmd.base_key_id == 0xffffffff) {
		argp[argl] = '\0';
		LOG_ERR("Invalid KEY %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	/* Get DIV_PATH parameter */
	memcpy(kdc_cmd.diversify_path, argp, argl);
	kdc_cmd.diversify_len = argl + 1;

	LOG_INF("Starting KDC derivation...");
	res = derive(&kdc_cmd);

	keylen = get_keylen_by_curve_id(_curve_id_ecdh);
	LOG_INF("key length: %u", keylen);
	memcpy(priv_key_ecdh, kdc_cmd.key, MIN(32, keylen));
	if (keylen > 32) {
		memcpy(priv_key_ecdh + 32, kdc_cmd.key, keylen - 32);
	}

	res = pke_open();
	if (res) {
		return res;
	}

	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(_curve_id_ecdh);
	if (!curve) {
		LOG_INF("Failed to obtain curve\n");
		pke_close();
		return -1;
	}

	if (_curve_id_ecdh == CMRT_ECC_CURVE_25519 || _curve_id_ecdh == CMRT_ECC_CURVE_448) {
		res = cmrt_pke_rfc7748_keygen(pke, curve, priv_key_ecdh, pub_x_ecdh);
	} else {
		res = cmrt_pke_ecdh_keygen(pke, curve, priv_key_ecdh, pub_x_ecdh);
	}
	if (res) {
		LOG_ERR("Cannot generate public key: %d", res);
		pke_close();
		return res;
	}

	pke_close();

	keylen = get_keylen_by_curve_id(_curve_id_ecdh);
	memcpy(out, priv_key_ecdh, keylen);
	memcpy(out + keylen, pub_x_ecdh, keylen);
	*outlen = 2 * keylen;

	return res;
}

static int process_public_ecdh(uint8_t *argp, uint8_t *out, size_t *outlen)
{
	int res = 0;
	size_t keylen = 0;

	*outlen = 0;

	res = pke_open();
	if (res) {
		return res;
	}

	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(_curve_id_ecdh);
	if (!curve) {
		LOG_INF("Failed to obtain curve\n");
		pke_close();
		return -1;
	}

	keylen = get_keylen_by_curve_id(_curve_id_ecdh);

	if (_curve_id_ecdh == CMRT_ECC_CURVE_25519 || _curve_id_ecdh == CMRT_ECC_CURVE_448) {
		res = cmrt_pke_rfc7748(pke, curve, priv_key_ecdh, argp, out);
	} else {
		res = cmrt_pke_ecdh(pke, curve, priv_key_ecdh, argp, out);
	}
	if (res) {
		LOG_ERR("Cannot generate ECDH shared secret: %d", res);
		pke_close();
		return res;
	}

	pke_close();

	*outlen = keylen;

	return res;
}

static int process_private_ecdh(uint8_t *argp, uint8_t *out, size_t *outlen)
{
	int res = 0;
	size_t keylen = 0;

	*outlen = 0;

	res = pke_open();
	if (res) {
		return res;
	}

	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(_curve_id_ecdh);
	if (!curve) {
		LOG_INF("Failed to obtain curve\n");
		pke_close();
		return -1;
	}

	keylen = get_keylen_by_curve_id(_curve_id_ecdh);

	if (_curve_id_ecdh == CMRT_ECC_CURVE_25519 || _curve_id_ecdh == CMRT_ECC_CURVE_448) {
		res = cmrt_pke_rfc7748(pke, curve, argp, pub_x_ecdh, out);
	} else {
		res = cmrt_pke_ecdh(pke, curve, argp, pub_x_ecdh, out);
	}
	if (res) {
		LOG_ERR("Cannot generate ECDH shared secret: %d", res);
		pke_close();
		return res;
	}

	pke_close();

	*outlen = keylen;

	return res;
}

static int process_message_ecdh(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;

	if (memcmp(argp, "public", argl) == 0) {
		LOG_INF("Stage: public");
		argl = argl_next(&argp, argl);
		LOG_HEXDUMP_DBG(argp, argl, "Public key: ");
		res = process_public_ecdh(argp, out, outlen);
	} else if (memcmp(argp, "private", argl) == 0) {
		LOG_INF("Stage: private");
		argl = argl_next(&argp, argl);
		LOG_HEXDUMP_DBG(argp, argl, "Private key: ");
		res = process_private_ecdh(argp, out, outlen);
	} else {
		LOG_INF("Stage: key generation");
		res = process_keygen_ecdh(argp, argl, out, outlen);
	}

	if (res) {
		pke_close();
	}

	return res;
}

static int process_message(uint8_t *buffer, size_t *buflen)
{
	if (*buflen < 8) {
		LOG_ERR("Short message");
		return -EINVAL;
	}
	int res = -EINVAL;
	uint8_t *argp = buffer;
	uint32_t argc = argl_init(&argp);
	/*
	 * Check argument array length matches message length, then
	 * rest of the code can trust the lengths of inputs given...
	 */
	const uint8_t *ap2 = argp;
	for (size_t i = 0; i < argc; i++) {
		const int alen = *(uint32_t*)ap2;
		const uint8_t *const nap = ap2 + ((alen + 7) & ~3);
		if (nap < ap2 || (size_t)(nap - buffer) > *buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	uint32_t argl = argl_init(&argp);

	if (memcmp(argp, "AES", argl) == 0) {
		LOG_INF("Selection: AES");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_aes(argp, argl, buffer, buflen);
	} else if (memcmp(argp, "HC", argl) == 0) {
		LOG_INF("Selection: HC");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_hc(argp, argl, buffer, buflen);
	} else if (memcmp(argp, "ECDH", argl) == 0) {
		LOG_INF("Selection: ECDH");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_ecdh(argp, argl, buffer, buflen);
	} else {
		LOG_ERR("Invalid selection (AES|HC): %s", (char *)argp);
	}

	return res;
}

static int main_loop(uint32_t flowid)
{
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return -ENODEV;
	}
	LOG_INF("Waiting for SIC input on flow 0x%x...", (unsigned int)flowid);

	int res = 0;
	while (true) {
		uint32_t peerid;
		size_t buflen = sizeof(buffer) - 4;
		res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}

		LOG_INF("Got request from HLOS of %zu bytes", buflen);
		if (buflen) {
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Request from HLOS:");
		}

		/* Processing failure is a fatal error. */
		res = process_message(buffer, &buflen);
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			break;
		}

		/* The same buffer holds the response to HLOS. */
		LOG_INF("Sending response to HLOS of %zu bytes", buflen);
		if (buflen) {
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Response to HLOS:");
		}

		if (!buflen) { continue; }
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	aes_close();
	hc_close();
	pke_close();
	return res;
}

void container(void *p1, void *p2, void *p3)
{
	(void)p2;
	(void)p3;
	print_usage();
	int res = main_loop((uint32_t)p1);
	LOG_ERR("Container main_loop exited with %d!", res);
}
