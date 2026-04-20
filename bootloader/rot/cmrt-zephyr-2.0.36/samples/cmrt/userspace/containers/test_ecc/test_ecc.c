/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
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
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/hc.h>

#define BUFSZ 4096
#define MAX_SIG_LEN 68
#define MAX_HASH_LEN 64

#define LOG_ERR_RET(res, ...) do {	\
	LOG_ERR(__VA_ARGS__);	\
	return res;	\
} while(0)

#define LOG_ERR_GOTO(label, ...) do {	\
	LOG_ERR(__VA_ARGS__);	\
	goto label;	\
} while(0)

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

/* Global buffer for receive and response messages from SIC. */
alignas(4) uint8_t buffer[BUFSZ];


cmrt_pke_t pke = CMRT_INVALID_HANDLE;
bool opened_from_hlos = false;


typedef enum scheme {
	INVALID_SCHEME = 0,
	ECDSA,
	EDDSA,
} scheme_t;

static struct {
	const char *name;
	uint32_t id;
	scheme_t scheme;
} curve_table[] = {
	{ "ed25519", CMRT_ECC_CURVE_ED25519, EDDSA },
	{ "ed448", CMRT_ECC_CURVE_ED448, EDDSA },

	{ "secp256k1", CMRT_ECC_CURVE_SECP256K1, ECDSA },
	{ "25519", CMRT_ECC_CURVE_25519, ECDSA },
	{ "448", CMRT_ECC_CURVE_448, ECDSA },
	{ "anssi_frp256v1", CMRT_ECC_CURVE_ANSSI_FRP256V1, ECDSA },

	{ "nist_p192", CMRT_ECC_CURVE_NIST_P192, ECDSA },
	{ "nist_p224", CMRT_ECC_CURVE_NIST_P224, ECDSA },
	{ "nist_p256", CMRT_ECC_CURVE_NIST_P256, ECDSA },
	{ "nist_p384", CMRT_ECC_CURVE_NIST_P384, ECDSA },
	{ "nist_p521", CMRT_ECC_CURVE_NIST_P521, ECDSA },

	{ "brainpool_p192r1", CMRT_ECC_CURVE_BRAINPOOL_P192R1, ECDSA },
	{ "brainpool_p224r1", CMRT_ECC_CURVE_BRAINPOOL_P224R1, ECDSA },
	{ "brainpool_p256r1", CMRT_ECC_CURVE_BRAINPOOL_P256R1, ECDSA },
	{ "brainpool_p320r1", CMRT_ECC_CURVE_BRAINPOOL_P320R1, ECDSA },
	{ "brainpool_p384r1", CMRT_ECC_CURVE_BRAINPOOL_P384R1, ECDSA },
	{ "brainpool_p512r1", CMRT_ECC_CURVE_BRAINPOOL_P512R1, ECDSA },
	{ "brainpool_p192t1", CMRT_ECC_CURVE_BRAINPOOL_P192T1, ECDSA },
	{ "brainpool_p224t1", CMRT_ECC_CURVE_BRAINPOOL_P224T1, ECDSA },
	{ "brainpool_p256t1", CMRT_ECC_CURVE_BRAINPOOL_P256T1, ECDSA },
	{ "brainpool_p320t1", CMRT_ECC_CURVE_BRAINPOOL_P320T1, ECDSA },
	{ "brainpool_p384t1", CMRT_ECC_CURVE_BRAINPOOL_P384T1, ECDSA },
	{ "brainpool_p512t1", CMRT_ECC_CURVE_BRAINPOOL_P512T1, ECDSA },
};

static struct {
	const char *name;
	cmrt_hash_algo_t hash_algo;
	size_t hashlen;
} hash_algo_table[] = {
	{ "sha224", CMRT_HASH_SHA224, 28 },
	{ "sha256", CMRT_HASH_SHA256, 32 },
	{ "sha384", CMRT_HASH_SHA384, 48 },
	{ "sha512", CMRT_HASH_SHA512, 64 },
	{ "sha512_224", CMRT_HASH_SHA512_224, 28 },
	{ "sha512_256", CMRT_HASH_SHA512_256, 32 },
	{ "sha3_224", CMRT_HASH_SHA3_224, 28 },
	{ "sha3_256", CMRT_HASH_SHA3_256, 32 },
	{ "sha3_384", CMRT_HASH_SHA3_384, 48 },
	{ "sha3_512", CMRT_HASH_SHA3_512, 64 },
	{ "shake128", CMRT_HASH_SHAKE128, 16 },
	{ "shake256", CMRT_HASH_SHAKE256, 32 },
	{ "whirlpool", CMRT_HASH_WHIRLPOOL, 28 }
};

static void print_usage(void)
{
	LOG_INF("Usage: COMMAND CURVE [options]");
	LOG_INF("COMMAND:  open|close|keygen|sign|verify|ecdh_keygen|ecdh|pke_sync");
	LOG_INF("CURVE:    ed25519|nist_p224|... See supported curves below.\n");

	LOG_INF("keygen CURVE PRIVKEY\n");

	LOG_INF("sign CURVE PRIVKEY DIGEST\n");

	LOG_INF("verify CURVE PUBKEY SIGN DIGEST");
	LOG_INF("PUBKEY (ecdsa): x and y pubkey components");
	LOG_INF("PUBKEY (eddsa): y pubkey component");
	LOG_INF("SIGN:           r and s signature components");
	LOG_INF("DIGEST:         digest\n");

	LOG_INF("ecdh_keygen CURVE PRIVKEY\n");

	LOG_INF("ecdh CURVE PRIVKEY PEERKEY");
	LOG_INF("PRIVKEY:  private key");
	LOG_INF("PEERKEY:  x-component of peer's public key,");
	LOG_INF("          (the output of ecdh_keygen)");

	LOG_INF("Notes: PRIVKEY, PEERKEY as well as PUBKEY and SIGN components");
	LOG_INF("      (x, y) must be `curvelen' bytes in length,");
	LOG_INF("      where `curvelen' is a parameter of the curve.\n");
	LOG_INF("      If a session is not opened with open, other commands");
	LOG_INF("      will call open/close internally for themselves.\n");

	LOG_INF("Supported curves:");
	for (size_t i = 0; i < ARRAY_SIZE(curve_table); i++) {
		LOG_INF("%s", curve_table[i].name);
	}
}

static int pke_open_from_hlos()
{
	if (cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context (already opened)");
		return -1;
	}

	pke = cmrt_pke_open(0);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
		pke = CMRT_INVALID_HANDLE;
		return -1;
	}

	opened_from_hlos = true;
	return 0;
}

static int pke_open(void)
{
	if (opened_from_hlos) {
		return 0;
	}

	if (cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context (already opened)");
		return -1;
	}

	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
		pke = CMRT_INVALID_HANDLE;
		return -1;
	}

	return 0;
}

static int pke_close_from_hlos()
{
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
		pke = CMRT_INVALID_HANDLE;
		opened_from_hlos = false;
		return 0;
	} else {
		LOG_ERR("Cannot close PKE context (already closed)");
		return -1;
	}
}

static void pke_close(void) {
	if (opened_from_hlos) {
		return;
	}

	if (cmrt_is_valid(pke)) {
		LOG_INF("Closing PKE context");
		cmrt_pke_close(pke);
		pke = CMRT_INVALID_HANDLE;
	}
}

static void debug_print_blob(uint8_t *blob, size_t sz, const char *info_text)
{
#ifdef CONFIG_DEBUG
	if (!blob || !sz) return;

	size_t sz_hex = sz*2;
	uint8_t blob_hex[MAX_SIG_LEN*2];
	size_t written = bin2hex(blob, MIN(sz, MAX_SIG_LEN), (char*)blob_hex, MAX_SIG_LEN*2);

	LOG_DBG("%s%.*s%s", info_text, (int)sz_hex, blob_hex,
		(written < sz_hex) ? "..." /*cropped*/ : "" );
#else
	(void)blob; (void)sz; (void)info_text;
#endif
}

static int get_curve_info(uint32_t curve_id, cmrt_ecc_curve_t *out_curve,
			  uint32_t *out_curvelen)
{
	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(curve_id);
	if (!curve) LOG_ERR_RET(-1, "Invalid CURVE (cmrt_pke_get_curve failed)");

	if (out_curve) *out_curve = curve;

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
	if (out_curvelen) *out_curvelen = curvelen;

	return 0;
}

static cmrt_hash_algo_t get_hash_algo(const uint8_t *name, size_t namelen,
	cmrt_hash_algo_t *out_hash_algo, size_t *out_hashlen)
{
	for (size_t i = 0; i < ARRAY_SIZE(hash_algo_table); i++) {
		if (memcmp(name, hash_algo_table[i].name, namelen) == 0
		    && hash_algo_table[i].name[namelen] == '\0') { // XXX
			*out_hash_algo = hash_algo_table[i].hash_algo;
			*out_hashlen = hash_algo_table[i].hashlen;
			return 0;
		}
	}
	return -1;
}

static uint32_t get_curve(const uint8_t * name, size_t namelen,
			  scheme_t *out_scheme)
{
	for (size_t i = 0; i < ARRAY_SIZE(curve_table); i++) {
		if (memcmp(name, curve_table[i].name, namelen) == 0
		    && curve_table[i].name[namelen] == '\0') {
			if (out_scheme) *out_scheme = curve_table[i].scheme;
			return curve_table[i].id;
		}
	}
	return 0;
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

static int process_verify(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	int res = -1;

	if (argc < 6) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	scheme_t scheme;
	uint32_t curve_id = get_curve(argp, argl, &scheme);
	if (curve_id == 0) return -1;
	LOG_DBG("verify: curve %.*s", (int)argl, argp);

	uint32_t pubx_len = 0;
	uint8_t *pubx = NULL;

	if (scheme == ECDSA) {
		if (argc != 7) {
			LOG_ERR("Error wrong number of parameters (%lu)", argc);
			return -1;
		}
		pubx_len = argl = argl_next(&argp, argl);
		pubx = argp;
		debug_print_blob(pubx, (size_t)pubx_len, "verify: pubx: 0x");
	} else { /* EDDSA so far */
		if (argc != 6) {
			LOG_ERR("Error wrong number of parameters (%lu)", argc);
			return -1;
		}
	}
	uint32_t puby_len = argl = argl_next(&argp, argl);
	uint8_t *puby = argp;
	debug_print_blob(puby, (size_t)puby_len, "verify: puby: 0x");

	if (pubx != NULL && pubx_len != puby_len) {
		LOG_ERR("verify (ecdsa): Invalid PUBKEY, mismatched lengths");
		return -1;
	}
	uint32_t sig_r_len = argl = argl_next(&argp, argl);
	uint8_t *sig_r = argp;
	debug_print_blob(sig_r, (size_t)sig_r_len, "verify: sig_r: 0x");

	uint32_t sig_s_len = argl = argl_next(&argp, argl);
	uint8_t *sig_s = argp;
	debug_print_blob(sig_s, (size_t)sig_s_len, "verify: sig_s: 0x");

	if (sig_s_len != sig_r_len) {
		LOG_ERR("verify: Invalid SIG (mismatched lengths)");
		return -1;
	}

	uint32_t data_len = argl = argl_next(&argp, argl);
	uint8_t *data = argp;

	uint32_t hash_algo_name_len = argl = argl_next(&argp, argl);
	uint8_t *hash_algo_name = argp;
	cmrt_hash_algo_t hash_algo;

	uint32_t digest_len = data_len; /* prehashed, initially */
	uint8_t *digest = data;
	if (!MATCH(hash_algo_name, hash_algo_name_len, "prehashed")) {

		alignas(4) uint8_t hash[MAX_HASH_LEN];
		size_t hashlen = 0;

		res = get_hash_algo(hash_algo_name, hash_algo_name_len, &hash_algo,
			&hashlen);
		if (res != 0) {
			LOG_ERR("Invalid hash algo");
			return -1;
		}

		LOG_DBG("verify: hash algo: %.*s", (int)hashlen, hash_algo_name);

		cmrt_hc_t hc = cmrt_hc_open("s2hc", 0 /* no kdc keyed */);
		if (!cmrt_is_valid(hc)) {
			LOG_ERR("Cannot open hc");
			return -1;
		}

		res = cmrt_hc_init(hc, hash_algo, NULL, 0);
		if (res != 0) {
			LOG_ERR("Cannot init hc");
			cmrt_hc_close(hc);
			return res;
		}

		res = cmrt_hc_final(hc, data, data_len, hash, &hashlen);
		if (res != 0) {
			LOG_ERR("cmrt_hc_final failed with %d", res);
			cmrt_hc_close(hc);
			return res;
		}

		cmrt_hc_close(hc);
		digest = hash;
		digest_len = (uint32_t)hashlen;
	}

	debug_print_blob(digest, (size_t)digest_len, "digest: 0x");

	res = pke_open();
	if (res != 0) return res;

	uint32_t curvelen;
	cmrt_ecc_curve_t curve;
	if (get_curve_info(curve_id, &curve, &curvelen) != 0) {
		res = -1;
		goto out;
	}

	LOG_DBG("verify: curve_id=%lu curve=%p curvelen=%lu scheme=%d",
		curve_id, curve, curvelen, scheme);

	if (sig_s_len != curvelen) {
		LOG_ERR("Invalid SIG len (curve's len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	if (scheme == ECDSA) {
		res = cmrt_pke_ecdsa_verify_hash(pke, curve, pubx, puby, digest,
			digest_len, sig_r, sig_s, NULL /*rprime*/);
	} else if (scheme == EDDSA) {
		res = cmrt_pke_eddsa_verify(pke, curve, puby, digest,
			digest_len, sig_r, sig_s, NULL /*rprime*/);
	} else {
		abort(); /* corrupted scheme */
	}

	/* The result of the operation is 0 if sig is VALID,
	 * -EINVAL if INVALID. Any value != 0 is considered as INVALID.
	 * The SIC output is the result of the operation as a machine-endian
	 * int */
	*((int*)buffer) = res;
	*_buflen = sizeof(int);

	LOG_INF("verify: signature is %d %s", res, (res == 0) ? "VALID" : "INVALID");

	if (res != 0 && res != -EINVAL)
		LOG_WRN("verify: odd error %d", res);

	res = 0;
	/* fallthrough */
out:
	pke_close();
	return res;
}

static int process_sign(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	scheme_t scheme;
	uint32_t curve_id = get_curve(argp, argl, &scheme);
	if (curve_id == 0) return -1;

	uint32_t privkey_len = argl = argl_next(&argp, argl);
	uint8_t *privkey = argp;

	uint32_t digest_len = argl = argl_next(&argp, argl);
	uint8_t *digest = argp;

	int res = pke_open();
	if (res != 0) return res;

	uint32_t curvelen;
	cmrt_ecc_curve_t curve;
	if (get_curve_info(curve_id, &curve, &curvelen) != 0) {
		res = -1;
		goto out;
	}

	LOG_DBG("sign: curve_id=%lu curve=%p curvelen=%lu scheme=%d",
		curve_id, curve, curvelen, scheme);

	if (privkey_len != curvelen) {
		LOG_ERR("Invalid PRIVKEY len (curve len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	if (scheme == ECDSA) {
		res = cmrt_pke_ecdsa_sign_hash(pke, curve, privkey, digest, digest_len,
					       buffer, buffer+curvelen);
		if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_ecdsa_sign_hash failed %d", res);
	} else if (scheme == EDDSA) {
		res = cmrt_pke_eddsa_sign(pke, curve, privkey, digest, digest_len,
					  buffer, buffer+curvelen);
		if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_eddsa_sign failed %d", res);
	} else abort(); /* corrupted scheme */

	*_buflen = curvelen * 2;

	debug_print_blob(buffer, curvelen, "sign: sign_r: 0x");
	debug_print_blob(buffer+curvelen, curvelen, "sign: sign_s: 0x");

	res = 0;
	/* fallthrough */
out:
	pke_close();
	return res;
}

static int process_keygen(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	if (argc != 2) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	scheme_t scheme;
	uint32_t curve_id = get_curve(argp, argl, &scheme);
	if (curve_id == 0) return -1;

	uint32_t privkey_len = argl = argl_next(&argp, argl);
	uint8_t *privkey = argp;

	int res = pke_open();
	if (res != 0) return res;

	uint32_t curvelen;
	cmrt_ecc_curve_t curve;
	if (get_curve_info(curve_id, &curve, &curvelen) != 0) {
		res = -1;
		goto out;
	}

	LOG_DBG("keygen: curve_id=%lu curve=%p curvelen=%lu scheme=%d",
		curve_id, curve, curvelen, scheme);

	if (privkey_len != curvelen) {
		LOG_ERR("Invalid PRIVKEY len (curve len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	if (scheme == ECDSA) {
		/* cmrt_pke_ecdsa_keygen outputs `curvelen` bytes for each
		 * pubkey point. We tell it to write the x and y points
		 * consecutively at `buffer`. */
		res = cmrt_pke_ecdsa_keygen(pke, curve, privkey, buffer, buffer+curvelen);
		if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_ecdsa_keygen failed %d", res);

		*_buflen = curvelen*2;

		debug_print_blob(buffer, curvelen, "keygen (ecdsa): pub_x: 0x");
		debug_print_blob(buffer+curvelen, curvelen, "keygen (ecdsa): pub_y: 0x");
	} else if (scheme == EDDSA) {
		/* cmrt_pke_eddsa_keygen outputs `keylen` bytes for the
		 * y point of the pubkey. We tell it to write it at `buffer`.
		 * x point is not returned */
		res = cmrt_pke_eddsa_keygen(pke, curve, privkey, buffer);
		if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_eddsa_keygen failed %d", res);
		*_buflen = curvelen;

		debug_print_blob(buffer, curvelen, "keygen (eddsa): pub_y: 0x");
	} else
		abort(); /* corrupted scheme */

	res = 0;
	/* fallthrough */
out:
	if (res != 0) *_buflen = 0;
	pke_close();
	return res;
}

static int process_ecdh_keygen(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	if (argc != 2) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	uint32_t curve_id = get_curve(argp, argl, NULL);
	if (curve_id == 0) return -1;

	uint32_t privkey_len = argl = argl_next(&argp, argl);
	uint8_t *privkey = argp;

	int res = pke_open();
	if (res != 0) return res;

	uint32_t curvelen;
	cmrt_ecc_curve_t curve;
	if (get_curve_info(curve_id, &curve, &curvelen) != 0) {
		res = -1;
		goto out;
	}
	LOG_DBG("ecdh_keygen: curve_id=%lu curve=%p curvelen=%lu", curve_id, curve, curvelen);

	if (privkey_len != curvelen) {
		LOG_ERR("Invalid PRIVKEY len (curve len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	res = cmrt_pke_ecdh_keygen(pke, curve, privkey, buffer);
	if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_ecdh_keygen failed %d", res);

	debug_print_blob(buffer, curvelen, "ecdh_keygen: pub_x: 0x");
	*_buflen = curvelen;

	res = 0;
	/* fallthrough */
out:
	pke_close();
	return res;
}

static int process_ecdh(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	uint32_t curve_id = get_curve(argp, argl, NULL);
	if (curve_id == 0) return -1;

	uint32_t privkey_len = argl = argl_next(&argp, argl);
	uint8_t *privkey = argp;

	uint32_t peerkey_len = argl = argl_next(&argp, argl);
	uint8_t *peerkey = argp;

	int res = pke_open();
	if (res != 0) return res;

	uint32_t curvelen;
	cmrt_ecc_curve_t curve;
	if (get_curve_info(curve_id, &curve, &curvelen) != 0) {
		res = -1;
		goto out;
	}

	LOG_DBG("ecdh: curve_id=%lu curve=%p curvelen=%lu", curve_id, curve, curvelen);

	if (privkey_len != curvelen) {
		LOG_ERR("Invalid PRIVKEY len (curve len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	if (peerkey_len != curvelen) {
		LOG_ERR("Invalid PEERKEY len (curve len is %lu)", curvelen);
		res = -1;
		goto out;
	}

	res = cmrt_pke_ecdh(pke, curve, privkey, peerkey, buffer);
	if (res != 0) LOG_ERR_GOTO(out, "cmrt_pke_ecdh failed %d", res);

	debug_print_blob(buffer, curvelen, "ecdh: shared_secret: 0x");
	*_buflen = curvelen;

	res = 0;
	/* fallthrough */
out:
	pke_close();
	return res;
}

static int process_pke_sync(size_t *_buflen)
{
	int res = cmrt_pke_sync(pke);
	LOG_DBG("pke_sync:%d", res);
	*((int*)buffer) = res;
	*_buflen = sizeof(int);
	return 0;
}

static int process_message(uint8_t *buffer, size_t *_buflen)
{
	if (*_buflen < 8) {
		LOG_ERR("Short message!");
		return -EINVAL;
	}
	uint8_t *argp = buffer;
	uint32_t argc = argl_init(&argp);
	/*
	 * Check argument array length matches message length, then
	 * commands can trust the lengths of inputs given to them.
	 */
	const uint8_t *ap2 = argp;
	for (size_t i = 0; i < argc; i++) {
		const int alen = *(uint32_t*)ap2;
		const uint8_t *const nap = ap2 + ((alen + 7) & ~3);
		if (nap < ap2 || (size_t)(nap - buffer) > *_buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	*_buflen = 0;
	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3); /* revisit how to do .*/
	argc--;

	/* dispatch OPERATION */
	if (MATCH(argp, argl, "open")) {
		int res_open = pke_open_from_hlos();
		*((int*)buffer) = res_open;
		*_buflen = sizeof(int);
		return 0;
	}
	if (MATCH(argp, argl, "close")) {
		int res_close = pke_close_from_hlos();
		*((int*)buffer) = res_close;
		*_buflen = sizeof(int);
		return 0;
	}
	if (MATCH(argp, argl, "keygen")) {
		return process_keygen(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "sign")) {
		return process_sign(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "verify")) {
		return process_verify(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "ecdh_keygen")) {
		return process_ecdh_keygen(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "ecdh")) {
		return process_ecdh(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "pke_sync")) {
		return process_pke_sync(_buflen);
	}
	/* else */
	argp[argl] = '\0';
	LOG_ERR("%s: Invalid COMMAND", argp);
	return 0;
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
		if (buflen)
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Request from HLOS:");

		/* Processing failure is a fatal error. */
		res = process_message(buffer, &buflen);
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			break;
		}

		/* The same buffer holds the response to HLOS. */
		LOG_INF("Sending response to HLOS of %zu bytes", buflen);
		if (buflen)
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Response to HLOS:");

		if (!buflen) continue;
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	opened_from_hlos = false;
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
