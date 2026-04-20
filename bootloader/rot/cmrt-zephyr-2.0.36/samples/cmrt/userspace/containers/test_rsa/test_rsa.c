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
#include <inttypes.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/pke.h>

#include <cmrt/ucu/rsa_pad.h>
#include <cmrt/ucu/endianness.h>

LOG_MODULE_DECLARE(perf, CONFIG_CMRT_LOG_LEVEL);

#define MAX_MODSIZE_BITS 8192
#define BUFSZ 8192

/* Length in bytes of pubkey exponent (E). Some syscalls ask us to specify it,
 * but cmrt_pke_rsa_public_key_primitive hardcodes it to 4, so we only allow a
 * elength of 4 for all operation. */
#define ELEN 4

/* Global buffer for receive and response messages from SIC. */
alignas(4) uint8_t buffer[BUFSZ];

alignas(4) uint8_t SCRATCHPAD0[MAX_MODSIZE_BITS/8];
alignas(4) uint8_t SCRATCHPAD1[MAX_MODSIZE_BITS/8];
alignas(4) uint8_t SCRATCHPAD2[MAX_MODSIZE_BITS/8];

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

static struct {
	const char *name;
	cmrt_hash_algo_t hash_algo;
	uint32_t hashlen;
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
};

static int get_hash_algo(const uint8_t *name, size_t namelen,
	cmrt_hash_algo_t *out_hash_algo, uint32_t *out_hashlen)
{
	for (size_t i = 0; i < ARRAY_SIZE(hash_algo_table); i++) {
		/* XXX: Improve this, name is not necessarily null-terminated. */
		if (namelen == strlen(hash_algo_table[i].name) &&
			memcmp(name, hash_algo_table[i].name, namelen) == 0) {
			*out_hash_algo = hash_algo_table[i].hash_algo;
			*out_hashlen = hash_algo_table[i].hashlen;
			return 0;
		}
	}
	return -1;
}
static void print_usage(void)
{
	/* XXX: Consider merging these for smaller code size. */
	LOG_INF("Usage: cmtest cmd COMMAND [arguments]");
	LOG_INF("COMMAND: keygen|pss_sign|pss_verify\n");

	LOG_INF("keygen MODSIZE PUBE");
	LOG_INF("Generate an RSA keypair");
	LOG_INF("Outputs PUBN||PRIVD");
	LOG_INF("PUBN and PRIVD are MODBITS/8 bytes long");
	LOG_INF("MODSIZE:  length in bits of the RSA modulus. Must be multiple");
	LOG_INF("          multiple of 8. Maximum is %u\n", MAX_MODSIZE_BITS);
	LOG_INF("PUBE:     RSA public key exponent. Must be %u bytes long\n", ELEN);

	LOG_INF("pss_sign MODSIZE HASHALGO SALTLEN PUBN PUBE PRIVD MSG");
	LOG_INF("Sign a message or a digest with RSA-PSS");
	LOG_INF("Outputs the pss signature, which is MODSIZE/8 bytes long");
	LOG_INF("MODSIZE:  length in bits of RSA modules. See keygen command");
	LOG_INF("HASHALGO: hash algorithm to use or \"prehashed\" if msg is a digest");
	LOG_INF("SALTLEN:  length in bytes of the PSS salt. Can be 0 for deterministic sigs");
	LOG_INF("PUBN:     n component of pubkey. Must be MODSIZE/8 bytes long");
	LOG_INF("PUBE:     e component of pubkey (exponent). Must be %u bytes long", ELEN);
	LOG_INF("PRIVD:    d component of private key. Must be MODSIZE/8 bytes long");
	LOG_INF("MSG:      message (or digest if prehashed) to sign");
	LOG_INF("          Max len is MODSIZE/8. If prehashed, the len of digest is the hash len\n");

	LOG_INF("pss_verify MODSIZE HASHALGO SALTLEN PUBN PUBE SIG MSG");
	LOG_INF("outputs a u32 little-endian value. 0 on valid signature");
	LOG_INF("Sign a message or a digest with RSA-PSS");
	LOG_INF("MODSIZE:  length in bits of RSA modules. See keygen command");
	LOG_INF("HASHALGO: hash algorithm to use or \"prehashed\" if msg is a digest");
	LOG_INF("SALTLEN:  length in bytes of the PSS salt. Can be 0 for deterministic sigs");
	LOG_INF("PUBN:     n component of pubkey. Must be MODSIZE/8 bytes long");
	LOG_INF("PUBE:     e component of pubkey (exponent). Must be %u bytes long", ELEN);
	LOG_INF("SIG:      pss signature blob, the output of pss_sign");
	LOG_INF("MSG:      message (or digest if prehashed) to verify with SIG");
	LOG_INF("          Max len is MODSIZE/8. If prehashed, the len of digest is the hash len\n");

	LOG_INF("oaep_encrypt MODSIZE HASHALGO PUBN PUBE MSG");
	LOG_INF("Encrypts a message with OAEP RSA");
	LOG_INF("Returns an encrypted message with length MODSIZE/8");
	LOG_INF("MODSIZE:  length in bits of RSA modulus. See keygen command");
	LOG_INF("HASHALGO: hash algorithm to use");
	LOG_INF("PUBN:     n component of pubkey. Must be MODSIZE/8 bytes long");
	LOG_INF("PUBE:     e component of pubkey (exponent). Must be %u bytes long", ELEN);
	LOG_INF("LABEL:    optional parameter used to add an additional input to the encryption process");
	LOG_INF("MSG:      message to encrypt with OAEP RSA\n");

	LOG_INF("oaep_decrypt MODSIZE HASHALGO PUBN PUBE PRIVD ENCMSG");
	LOG_INF("Decrypts a message previously encrypted with OAEP RSA");
	LOG_INF("Returns a plaintext message");
	LOG_INF("MODSIZE:  length in bits of RSA modulus. See keygen command");
	LOG_INF("HASHALGO: hash algorithm to use");
	LOG_INF("PUBN:     n component of pubkey. Must be MODSIZE/8 bytes long");
	LOG_INF("PUBE:     e component of pubkey (exponent). Must be %u bytes long", ELEN);
	LOG_INF("PRIVD:    d component of private key. Must be MODSIZE/8 bytes long");
	LOG_INF("LABEL:    optional parameter used to add an additional input to the encryption process");
	LOG_INF("ENCMSG:   encrypted message to decrypt\n");

	LOG_INF("NOTE:     If \"-\" is provided as SALTLEN, hash len is used as salt len\n");

	LOG_INF("Avaliable HASHALGO:\n");
	for (size_t i = 0; i < sizeof(hash_algo_table)/sizeof(hash_algo_table[0]); i++) {
		LOG_INF("%s (len %lu bytes)", hash_algo_table[i].name,
			hash_algo_table[i].hashlen);
	}
}

/* Converts a (decimal) string into a uint32_t. Returns the parsed number.
 * Processes exactly `sl` bytes from the string `s`.
 * On conversion error sets errno to -EINVAL and returns 0.
 *
 * Encountering a nullbyte is a a conversion error.
 * An empty string (`sl`== 0) is a conversion error.
 * No wrapparound checks on the parsed number or on `sl`.
 * */
static uint32_t conv_strl2u32(const char *s, size_t sl)
{
	uint32_t acc = 0;
	const char *s_end = s + sl; /* no ovf check */
	for (; s < s_end; ++s) {
		char v = *s;
		if (v < '0' || v > '9') {
			errno = EINVAL;
			return 0;
		}
		v -= '0';
		acc *= 10; /* no ovf check */
		acc += v;
	}
	return acc;
}

static void debug_print_blob(uint8_t *blob, size_t sz, const char *info_text)
{
#ifdef CONFIG_DEBUG
#define _MAX_DBG_LEN 64
	if (!blob || !sz) return;

	size_t sz_hex = sz*2;
	uint8_t blob_hex[_MAX_DBG_LEN*2];
	size_t written = bin2hex(blob, MIN(sz, _MAX_DBG_LEN), (char*)blob_hex, _MAX_DBG_LEN*2);

	LOG_DBG("%s%.*s%s", info_text, (int)sz_hex, blob_hex,
		(written < sz_hex) ? "..." /*cropped*/ : "" );
#undef _MAX_DBG_LEN
#else
	(void)blob; (void)sz; (void)info_text;
#endif
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

static int oaep_encode(uint32_t modsize, uint8_t *n, uint8_t *e,
		       const struct cmrt_oaep_params *oaep,
		       const void *data, size_t ndata,
		       uint8_t *out)
{
	uint32_t encbuf[MAX_MODSIZE_BITS/32];
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		return -EBUSY;
	}
	int ret = cmrt_oaep_enc(hc, oaep, data, ndata, encbuf);
	cmrt_hc_close(hc);

	if (ret >= 0) {
		if (!cmrt_endian_swap((uint32_t *)encbuf, modsize / 32)) {
			printk("Endian swap NOK\n");
			return -EIO;
		}
		cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
		ret = cmrt_pke_rsa_public_key_primitive(pke, modsize,
							n, e, (const uint8_t *)encbuf,
							(uint8_t *)out);
		cmrt_pke_close(pke);
		if (ret != 0) {
			printk("RSA PUB NOK\n");
		} else {
			cmrt_endian_swap((uint32_t *)out, modsize / 32);
		}
	}

	return ret;
}

static int oaep_decode(uint32_t modsize, uint8_t *n, uint8_t *e,
		       uint8_t *d,
		       const struct cmrt_oaep_params *oaep,
		       const void *data, size_t ndata,
		       uint8_t *out)
{
	uint32_t inbuf[MAX_MODSIZE_BITS/32];
	uint32_t encbuf[MAX_MODSIZE_BITS/32];

	cmrt_reverse(inbuf, data, ndata);

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	struct cmrt_rsa_ctx ctx;

	memset(&ctx, 0, sizeof(ctx));
	ctx.key.bits = modsize;
	ctx.key.flags = 0;
	ctx.key.n = n;
	ctx.key.e = e;
	ctx.key.elength = ELEN;
	ctx.key.d = d;
	ctx.signature = (uint8_t *)encbuf;
	ctx.message = (uint8_t *)inbuf;

	int res = cmrt_pke_rsa_sign(pke, &ctx);
	cmrt_pke_close(pke);
	if (res != 0) {
		printk("RSA SIGN NOK %d\n", res);
		return -1;
	}
	size_t keylen = modsize / 8;

	cmrt_reverse(encbuf, encbuf, keylen);
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		return -EBUSY;
	}
	res = cmrt_oaep_dec(hc, oaep, encbuf, out);
	cmrt_hc_close(hc);

	if (res < 0) {
		printk("OAEP decrypt NOK %d\n", res);
	} else {
		printk("OAEP decrypt OK\n");
	}
	return res;
}

static int process_verify(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	if (argc != 7) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}

	uint32_t argl = argl_init(&argp);
	uint32_t modsize = conv_strl2u32((char *)argp, argl);
	if (modsize == 0 || (modsize % 8) != 0 || modsize > MAX_MODSIZE_BITS) {
		LOG_ERR("Invalid modsize");
		return -1;
	}
	uint32_t modbytes = modsize / 8;
	LOG_INF("modsize: %lu, modbytes: %lu", modsize, modbytes);

	argl = argl_next(&argp, argl);
	bool prehashed = true;
	cmrt_hash_algo_t halgo = -1;
	uint32_t hlen = argl;

	if (!MATCH(argp, argl, "prehashed")) {
		if (get_hash_algo(argp, argl, &halgo, &hlen) != 0) {
			LOG_ERR("Invalid hash algo");
			return -1;
		}
		prehashed = false;
	}

	LOG_INF("halgo: %hu", halgo);

	uint32_t slen = 0;
	argl = argl_next(&argp, argl);
	if (argl == 1 && argp[0] == '-') {
		/* "-" in slen arg indicates default value slen = hlen */
		slen = hlen;
	} else {
		errno = 0;
		slen = conv_strl2u32((char *)argp, argl);
		if (errno) {
			LOG_ERR("Invalid slen");
			return -1;
		}
	}

	LOG_INF("hlen: %lu slen: %lu", hlen, slen);

	argl = argl_next(&argp, argl);
	if (argl != modbytes) {
		LOG_INF("Invalid pubn");
		return -1;
	}

	uint8_t *pubn = argp;
	debug_print_blob(pubn, (size_t)modbytes, "pubn: 0x");

	argl = argl_next(&argp, argl);
	if (argl != ELEN) {
		LOG_ERR("E (pubkey exponent) must be %u bytes", ELEN);
		return -1;
	}
	uint8_t *pube = argp;
	debug_print_blob(pube, ELEN, "pube: 0x");

	argl = argl_next(&argp, argl);
	uint8_t *sig = argp;
	if (argl != modbytes) {
		LOG_ERR("Invalid sig len");
		return -1;
	}
	debug_print_blob(sig, (size_t)modbytes, "sig: 0x");

	uint32_t msglen = argl = argl_next(&argp, argl);
	uint8_t *msg = argp;

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
		return -1;
	}

	memset(SCRATCHPAD0, 0, sizeof(SCRATCHPAD0));
	int res = cmrt_pke_rsa_public_key_primitive(pke, modsize, pubn, pube, sig, SCRATCHPAD0);
	cmrt_pke_close(pke);
	if (res != 0) {
		LOG_ERR("cmrt_pke_rsa_public_key_primitive failed with %d", res);
		return res;
	}

	debug_print_blob(SCRATCHPAD0, (size_t)modbytes, "decrypted sig (swapped): 0x");

	if (cmrt_endian_swap((uint32_t *)SCRATCHPAD0, modbytes/4) == NULL) {
		LOG_ERR("cmrt_endian_swap failed");
		return -1;
	}

	debug_print_blob(SCRATCHPAD0, (size_t)modbytes, "decrypted sig 0x");

	cmrt_hc_t hc = cmrt_hc_open(NULL, 0);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Failed to open HC");
		return -1;
	}

	struct cmrt_pss_params pss = {
		.bits = modsize,
		.hlen = hlen,
		.flags = prehashed ? CMRT_PSS_PREHASHED : 0,
		.halgo = halgo,
		.slen = slen
	};

	//msg[1]=0xad;
	res = cmrt_pss_verify(hc, &pss, msg, (size_t)msglen, SCRATCHPAD0);

	LOG_INF("cmrt_pss_verify returned %d", res);
	if (res == 0) {
		LOG_INF("SIG OK");
	} else {
		LOG_INF("SIG NOK");
	}

	cmrt_hc_close(hc);

	memcpy(buffer, &res, sizeof(res));
	*buflen = sizeof(res);

	return 0;
}

static int process_sign(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	cmrt_pke_t pke = NULL;

	if (argc != 7) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}

	uint32_t argl = argl_init(&argp);
	uint32_t modsize = conv_strl2u32((char *)argp, argl);
	if (modsize == 0 || (modsize & 7) != 0 || modsize > MAX_MODSIZE_BITS) {
		LOG_ERR("Invalid modsize");
		return -1;
	}
	uint32_t modbytes = modsize >> 3;
	LOG_INF("modsize: %lu, modbytes: %lu", modsize, modbytes);

	argl = argl_next(&argp, argl);
	bool prehashed = true;
	cmrt_hash_algo_t halgo = -1;
	uint32_t hlen = argl;

	if (!MATCH(argp, argl, "prehashed")) {
		if (get_hash_algo(argp, argl, &halgo, &hlen) != 0) {
			LOG_ERR("Invalid hash algo");
			return -1;
		}
		prehashed = false;
	}

	LOG_INF("halgo: %hu", halgo);

	uint32_t slen = 0;
	argl = argl_next(&argp, argl);
	if (argl == 1 && argp[0] == '-') {
		/* "-" in slen arg indicates default value slen = hlen */
		slen = hlen;
	} else {
		errno = 0;
		slen = conv_strl2u32((char *)argp, argl);
		if (errno) {
			LOG_ERR("Invalid slen");
			return -1;
		}
	}

	LOG_INF("hlen: %lu slen: %lu", hlen, slen);

	argl = argl_next(&argp, argl);
	if (argl != modbytes) {
		LOG_INF("Invalid pubn");
		return -1;
	}
	uint8_t *pubn = argp;
	debug_print_blob(pubn, (size_t)modbytes, "pubn: 0x");

	argl = argl_next(&argp, argl);
	if (argl != ELEN) {
		LOG_ERR("E (pubkey exponent) must be %u bytes", ELEN);
		return -1;
	}
	uint8_t *pube = argp;
	debug_print_blob(pube, ELEN, "pube: 0x");

	argl = argl_next(&argp, argl);
	if (argl != modbytes) {
		LOG_INF("Invalid privd");
		return -1;
	}
	uint8_t *privd = argp;
	debug_print_blob(privd, (size_t)modbytes, "privd: 0x");

	uint32_t msglen = argl_next(&argp, argl);
	uint8_t *msg = argp;

	struct cmrt_pss_params pss = {
		.bits = modsize,
		.hlen = hlen,
		.flags = prehashed ? CMRT_PSS_PREHASHED : 0,
		.halgo = halgo,
		.slen = slen
	};

	/* TODO: Maybe allow HLOS to specify HC to use. */
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Failed to open HC");
		return -1;
	}

	/* NOTE: doxygen of this api has typo in @return */
	memset(SCRATCHPAD0, 0, sizeof(SCRATCHPAD0));
	int res = cmrt_pss_enc(hc, &pss, msg, msglen, SCRATCHPAD0);
	if (res != 0) {
		LOG_ERR("cmrt_pss_enc failed with %d", res);
		cmrt_hc_close(hc);
		return -1;
	}
	cmrt_hc_close(hc);
	debug_print_blob(SCRATCHPAD0, modbytes, "pss encoded msg: 0x");

	/* NOTE: this can give bad output if modbytes is not multiple of 4 */
	if (cmrt_endian_swap((uint32_t *)SCRATCHPAD0, modbytes/4) == NULL) {
		LOG_ERR("cmrt_endian_swap after pss_enc failed");
		return -1;
	}
	debug_print_blob(SCRATCHPAD0, modbytes, "pss encoded msg (swapped): 0x");

	memset(SCRATCHPAD1, 0, sizeof(SCRATCHPAD1));
	struct cmrt_rsa_ctx rsa_ctx = { 0 };
	rsa_ctx.key.bits = modsize;
	rsa_ctx.key.flags = 0;
	rsa_ctx.key.n = pubn;
	rsa_ctx.key.e = pube;
	rsa_ctx.key.elength = ELEN;
	rsa_ctx.key.d = privd;
	rsa_ctx.message = SCRATCHPAD0;
	rsa_ctx.signature = SCRATCHPAD1;

	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
		return -1;
	}
	res = cmrt_pke_rsa_sign(pke, &rsa_ctx);
	cmrt_pke_close(pke);

	debug_print_blob(rsa_ctx.signature, modbytes, "signature: 0x");
	memcpy(buffer, rsa_ctx.signature, modbytes);
	*buflen = modbytes;

	return 0;
}

static int process_keygen(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	if (argc != 2) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}
	uint32_t argl = argl_init(&argp);

	uint32_t modsize = conv_strl2u32((char *)argp, argl);
	if (modsize == 0 || (modsize & 7) != 0 || modsize > MAX_MODSIZE_BITS) {
		LOG_ERR("Invalid modsize");
		return -1;
	}
	uint32_t modbytes = modsize >> 3;
	LOG_INF("modsize: %lu, modbytes: %lu", modsize, modbytes);

	argl = argl_next(&argp, argl);
	uint8_t *pube = argp;
	if (argl != ELEN) {
		LOG_ERR("E (pubkey exponent) must be %u bytes", ELEN);
		return -1;
	}

	memset(SCRATCHPAD1, 0, sizeof(SCRATCHPAD1));
	memset(SCRATCHPAD1, 0, sizeof(SCRATCHPAD1));
	struct cmrt_rsa_key rsa_key = { 0 };

	rsa_key.bits = modsize;
	rsa_key.flags = 0;
	rsa_key.n = SCRATCHPAD0;
	rsa_key.e = pube;
	rsa_key.elength = ELEN;
	rsa_key.d = SCRATCHPAD1;

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
		return -1;
	}

	LOG_DBG("Generating key with modize=%lu...", modsize);
	int res = cmrt_pke_rsa_key_gen(pke, &rsa_key);
	cmrt_pke_close(pke);
	if (res != 0) {
		LOG_ERR("cmrt_pke_rsa_key_gen failed with %d", res);
		return res;
	}
	assert(rsa_key.elength == 4);

	debug_print_blob(rsa_key.n, modbytes, "N: 0x");
	debug_print_blob(pube, ELEN, "E: 0x");
	debug_print_blob(rsa_key.d, modbytes, "D: 0x");

	memcpy(buffer, rsa_key.n, modbytes);
	memcpy(buffer+modbytes, rsa_key.d, modbytes);
	*buflen = modbytes << 1;

	return 0;
}

static int process_encrypt(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	int res = 0;

	//Check that the number of arguments is the correct one
	if (argc != 6) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}

	//Initialize argument iterator
	uint32_t argl = argl_init(&argp);

	//Obtain modsize and making some assertions
	uint32_t modsize = conv_strl2u32((char *)argp, argl);
	if (modsize == 0 || (modsize & 7) != 0 || modsize > MAX_MODSIZE_BITS) {
		LOG_ERR("Invalid modsize");
		return -1;
	}

	//Size of mod in bytes -> modbytes
	uint32_t modbytes = modsize >> 3;

	LOG_INF("modsize: %lu, modbytes: %lu", modsize, modbytes);

	//Iterate to next argument
	argl = argl_next(&argp, argl);

	//Obtain hash algorithm
	cmrt_hash_algo_t halgo = -1;
	uint32_t hlen = argl;

	if (get_hash_algo(argp, argl, &halgo, &hlen) != 0) {
		LOG_ERR("Invalid hash algo");
		return -1;
	}

	LOG_INF("halgo: %hu", halgo);

	argl = argl_next(&argp, argl);

	//Obtain public number "n"
	if (argl != modbytes) {
		LOG_INF("Invalid pubn");
		return -1;
	}
	uint8_t *pubn = argp;
	debug_print_blob(pubn, (size_t)modbytes, "pubn: 0x");

	//Obtain exponene "e"
	argl = argl_next(&argp, argl);
	if (argl != ELEN) {
		LOG_ERR("E (pubkey exponent) must be %u bytes", ELEN);
		return -1;
	}
	uint8_t *pube = argp;
	debug_print_blob(pube, ELEN, "pube: 0x");

	//Obtain label
	uint32_t lablen = argl = argl_next(&argp, argl);
	uint8_t *label = argp;

	debug_print_blob(label, lablen, "label: 0x");

	//Obtain message
	uint32_t msglen = argl = argl_next(&argp, argl);
	uint8_t *msg = argp;

	debug_print_blob(msg, msglen, "msg: 0x");
	memset(buffer, 0, *buflen);

	//SCRACHPAD2 used to store output of encryption
	memset(SCRATCHPAD2, 0, sizeof(SCRATCHPAD2));

	struct cmrt_oaep_params params = {
		.bits = modsize,
		.hlen = hlen,
		.halgo = halgo,
		.label = (const char *)label,
		.llen = lablen
	};

	LOG_INF("Encrypting");
	res = oaep_encode(modsize, pubn, pube, &params, msg, msglen, SCRATCHPAD2);
	LOG_INF("Finished encrypting with: %d", res);

	debug_print_blob((uint8_t *)SCRATCHPAD2, (size_t)modbytes, "encrypted msg: ");
	memcpy(buffer, SCRATCHPAD2, modbytes);
	*buflen = modbytes;

	return res;
}

static int process_decrypt(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	int res = 0;

	//Check that the number of arguments is the correct one
	if (argc != 7) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}

	//Initialize argument iterator
	uint32_t argl = argl_init(&argp);

	//Obtain modsize and making some assertions
	uint32_t modsize = conv_strl2u32((char *)argp, argl);
	if (modsize == 0 || (modsize & 7) != 0 || modsize > MAX_MODSIZE_BITS) {
		LOG_ERR("Invalid modsize");
		return -1;
	}

	//Size of mod in bytes -> modbytes
	uint32_t modbytes = modsize >> 3;

	LOG_INF("modsize: %lu, modbytes: %lu", modsize, modbytes);

	//Iterate to next argument
	argl = argl_next(&argp, argl);

	//Obtain hash algorithm
	cmrt_hash_algo_t halgo = -1;
	uint32_t hlen = argl;

	if (get_hash_algo(argp, argl, &halgo, &hlen) != 0) {
		LOG_ERR("Invalid hash algo");
		return -1;
	}

	LOG_INF("halgo: %hu", halgo);

	argl = argl_next(&argp, argl);

	//Obtain public number "n"
	if (argl != modbytes) {
		LOG_INF("Invalid pubn");
		return -1;
	}
	uint8_t *pubn = argp;
	debug_print_blob(pubn, (size_t)modbytes, "pubn: 0x");

	//Obtain exponent "e"
	argl = argl_next(&argp, argl);
	if (argl != ELEN) {
		LOG_ERR("E (pubkey exponent) must be %u bytes", ELEN);
		return -1;
	}
	uint8_t *pube = argp;
	debug_print_blob(pube, ELEN, "pube: 0x");

	//Obtain private key "d"
	argl = argl_next(&argp, argl);
	if (argl != modbytes) {
		LOG_INF("Invalid privd");
		return -1;
	}
	uint8_t *privd = argp;
	debug_print_blob(privd, (size_t)modbytes, "privd: 0x");

	//Obtain label
	uint32_t lablen = argl = argl_next(&argp, argl);
	uint8_t *label = argp;

	debug_print_blob(label, lablen, "label: 0x");

	//Obtain encrypted message
	uint32_t msglen = argl = argl_next(&argp, argl);
	uint8_t *encmsg = argp;

	debug_print_blob(encmsg, msglen, "encmsg: 0x");
	memset(buffer, 0, *buflen);

	//SCRACHPAD2 used to store output of encryption
	memset(SCRATCHPAD2, 0, sizeof(SCRATCHPAD2));

	struct cmrt_oaep_params params = {
		.bits = modsize,
		.hlen = hlen,
		.halgo = halgo,
		.label = (const char *)label,
		.llen = lablen
	};

	LOG_INF("Decoding");
	res = oaep_decode(modsize, pubn, pube, privd, &params, encmsg, msglen, SCRATCHPAD2);
	LOG_INF("Finished decrypting with: %d", res);

	debug_print_blob((uint8_t *)SCRATCHPAD2, (size_t)res, "encrypted msg: ");
	memcpy(buffer, SCRATCHPAD2, res);
	*buflen = res;

	return res;
}

static int process_message(uint8_t *buffer, size_t *buflen)
{
	if (*buflen < 8) {
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
		if (nap < ap2 || (size_t)(nap - buffer) > *buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	*buflen = 0;
	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3); /* revisit how to do .*/
	argc--;

	/* XXX: should we make buflen a global? */

	int res = -1;

	if (MATCH(argp, argl, "keygen")) {
		res = process_keygen(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("RSA keygen failed");
		}
		return res;
	}

	if (MATCH(argp, argl, "pss_sign")) {
		res = process_sign(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("RSA pss_sign failed");
		}
		return res;
	}

	if (MATCH(argp, argl, "pss_verify")) {
		res = process_verify(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("RSA pss_verify failed");
		}
		return res;
	}

	if (MATCH(argp, argl, "oaep_encrypt")) {
		res = process_encrypt(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("RSA oaep_encrypt failed");
		}
		return res;
	}

	if (MATCH(argp, argl, "oaep_decrypt")) {
		res = process_decrypt(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("RSA oaep_decrypt failed");
		}
		return res;
	}

	/* else */
	LOG_ERR("%.*s: Invalid COMMAND", (int)argl, argp);
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

		if (!buflen) {
			continue;
		}

		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
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
