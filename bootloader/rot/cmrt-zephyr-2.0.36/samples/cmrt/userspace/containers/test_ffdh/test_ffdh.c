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
#include <inttypes.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/pke.h>

#define BUFSZ 8192
#define PARMSZ 8192
#define KEYSZ 1024
#define MAX_SIG_LEN 500

/* Global buffer for receive and response messages from SIC. */
alignas(4) uint8_t buffer[BUFSZ];

/* Global params struct, used to save params between function uses */
struct cmrt_ffdh_param params;

/* Global buffers to save incoming params */
alignas(4) uint8_t p[PARMSZ];
alignas(4) uint8_t q[PARMSZ];
alignas(4) uint8_t g[PARMSZ];

/* Global buffers to save keys */
static uint8_t priv_key_a[KEYSZ];
static uint8_t priv_key_b[KEYSZ];
static uint8_t pub_key_a[KEYSZ];
static uint8_t pub_key_b[KEYSZ];
static uint8_t shared_key_a[KEYSZ];
static uint8_t shared_key_b[KEYSZ];

/* Global buffer to save pbits */
alignas(4) uint8_t pbits[PARMSZ];
alignas(4) uint8_t qbits[PARMSZ];

static void print_usage(void)
{
	LOG_INF("Set parameters and verify: parmset %%{p} %%{q} %%{g}");
	LOG_INF("Generate parameters (1024|2048): parmgen 1024 | parmgen 2048");
	LOG_INF("Exchange (first set parameters): exchange");
	LOG_INF("Generate private key (first set parameters): privkey");
}

static cmrt_pke_t pke_open(void)
{
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE context");
	}
	return pke;
}

static void pke_close(cmrt_pke_t pke)
{
	if (cmrt_is_valid(pke)) {
		LOG_INF("Closing PKE context");
		cmrt_pke_close(pke);
	}
}

/* Function used for printing the buffer, change MAX_SIG_LEN*/
static void debug_print_blob(uint8_t *blob, size_t sz, char *info_text)
{
#ifdef CONFIG_DEBUG
	if (!blob || !sz) {
		return;
	}

	size_t sz_hex = sz * 2;
	uint8_t blob_hex[MAX_SIG_LEN * 2];
	size_t written = bin2hex(blob, MIN(sz, MAX_SIG_LEN), (char *)blob_hex, MAX_SIG_LEN*2);

	LOG_DBG("%s%.*s%s", info_text, (int)sz_hex, blob_hex,
		(written < sz_hex) ? "..." /*cropped*/ : "");
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

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))


static int process_parmset(uint8_t *argp, uint32_t argc)
{
	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -1;
	}

	uint32_t argl;
	size_t size_p = argl = argl_init(&argp);

	if (size_p > sizeof(p)) {
		LOG_ERR("Error size_p too large");
		return -1;
	}
	memcpy(p, argp, size_p);

	size_t size_q = argl = argl_next(&argp, argl);
	if (size_q > sizeof(q)) {
		LOG_ERR("Error size_q too large");
		return -1;
	}
	memcpy(q, argp, size_q);

	size_t size_g = argl = argl_next(&argp, argl);
	if (size_g > sizeof(g)) {
		LOG_ERR("Error size_g too large");
		return -1;
	}
	memcpy(g, argp, size_g);

	debug_print_blob(p, 768, "p value: 0x");
	//debug_print_blob(q, 32, "q value: 0x");
	//debug_print_blob(g, 256, "g value: 0x");

	LOG_DBG("size_p: %zu", size_p);
	LOG_DBG("size_q: %zu", size_q);
	LOG_DBG("size_g: %zu", size_g);

	/*Fill parmset struct*/
	params.mod_size = size_p;
	params.mod_bits = size_p * 8;
	params.p = p;
	params.grp_size = size_q;
	params.grp_bits = size_q * 8;
	params.q = q;
	params.gen_size = size_g;
	params.g = g;

	cmrt_pke_t pke = pke_open();
	int res = cmrt_pke_ffdh_verify(pke, &params);
	if (res != 0) {
		LOG_ERR("Error verifying params, error: %d", res);
	} else {
		LOG_DBG("Params verification succeeded");
	}
	pke_close(pke);
	return res;
}

static int process_parmgen(uint8_t *argp, uint32_t argc)
{
	if (argc != 1) {
		LOG_ERR("Error pbits arg missing");
		return -1;
	}
	params.p = p;
	params.q = q;
	params.g = g;

	uint32_t argl = argl_init(&argp);
	LOG_DBG("pbits: %s", argp);

	int res = -1;
	cmrt_pke_t pke = pke_open();
	if (MATCH(argp, argl, "1024")) {
		LOG_DBG("generating for 1024");
		res = cmrt_pke_ffdh_parmgen(pke, 1024, 1024/4, &params);
		if (res != 0) {
			LOG_ERR("Error generating params, error: %d", res);
		} else {
			LOG_DBG("Params generation succeeded");
		}
	} else if (MATCH(argp, argl, "2048")) {
		LOG_DBG("generating for 2048");
		res = cmrt_pke_ffdh_parmgen(pke, 2048, 2048/4, &params);
		if (res != 0) {
			LOG_ERR("Error generating params, error: %d", res);
		} else {
			LOG_DBG("Params generation succeeded");
		}
	} else {
		LOG_ERR("Error unknown pbits");
		res = -1;
	}
	pke_close(pke);
	return res;
}

static int process_exchange(uint8_t *argp, uint32_t argc)
{
	(void)argp; (void)argc;

	/* Rules:
	   pub_key or shared_key are generated
	   If pub_key is generated, shared key must be null
	   If shared_key is generated, pub_key must be null
	   If shared_key is generated, peer_key must not be null
	*/

	/* Check preconditions for exchange */
	if (!params.p || !params.q || !params.g) {
		LOG_ERR("Params not found, set params first");
		return -1;
	}

	cmrt_pke_t pke = pke_open();
	/* Generate private key A */
	int res = cmrt_pke_ffdh_private_keygen(pke, params.grp_size, params.q, priv_key_a);
	if (res != 0) {
		LOG_ERR("Privkey_a generation failed");
		goto _close;
	} else {
		LOG_DBG("Privkey_a generation succeeded");
	}

	/* Generate private key B */
	res = cmrt_pke_ffdh_private_keygen(pke, params.grp_size, params.q, priv_key_b);
	if (res != 0) {
		LOG_ERR("Privkey_b generation failed");
		goto _close;
	} else {
		LOG_DBG("Privkey_b generation succeeded");
	}

	LOG_DBG("pubkey_a: %p", pub_key_a);

	/* Generate public key A */
	res = cmrt_pke_ffdh(pke, &params, priv_key_a, NULL, pub_key_a, NULL);
	if (res != 0) {
		LOG_ERR("Pubkey_a generation failed");
		goto _close;
	} else {
		LOG_DBG("Pubkey_a generation succeeded");
	}

	/* Generate public key B */
	res = cmrt_pke_ffdh(pke, &params, priv_key_b, NULL, pub_key_b, NULL);
	if (res != 0) {
		LOG_ERR("Pubkey_b generation failed");
		goto _close;
	} else {
		LOG_DBG("Pubkey_b generation succeeded");
	}

	/* Generate shared key A */
	res = cmrt_pke_ffdh(pke, &params, priv_key_a, pub_key_b, NULL, shared_key_a);
	if (res != 0) {
		LOG_ERR("Sharedkey_a generation failed");
		goto _close;
	} else {
		LOG_DBG("Sharedkey_a generation succeeded");
	}

	/* Generate shared key B */
	res = cmrt_pke_ffdh(pke, &params, priv_key_b, pub_key_a, NULL, shared_key_b);
	if (res != 0) {
		LOG_ERR("Sharedkey_b generation failed");
		goto _close;
	} else {
		LOG_DBG("Sharedkey_b generation succeeded");
	}
_close:
	pke_close(pke);
	return res;
}

static int process_shared(uint8_t *argp, uint32_t argc, size_t *buflen)
{
	/* Check preconditions for exchange */
	if (!params.p || !params.q || !params.g) {
		LOG_ERR("Params not found, set params first");
		return -1;
	}

	if (argc != 2) {
		LOG_ERR("Error wrong number of inputs (%lu)", argc);
		return -1;
	}

	uint32_t argl;
	size_t size_privkey_a = argl = argl_init(&argp);

	if (size_privkey_a > sizeof(priv_key_a)) {
		LOG_ERR("Error priv_key_a too large");
		return -1;
	}
	memcpy(priv_key_a, argp, size_privkey_a);

	size_t size_pub_key_b = argl = argl_next(&argp, argl);
	if (size_pub_key_b > sizeof(pub_key_b)) {
		LOG_ERR("Error pub_key_b too large");
		return -1;
	}
	memcpy(pub_key_b, argp, size_pub_key_b);

	debug_print_blob(priv_key_a, 256, "pub_key_b value: 0x");
	debug_print_blob(pub_key_b, 256, "pub_key_b value: 0x");

	LOG_DBG("size_privkey_a: %zu", size_privkey_a);
	LOG_DBG("size_pub_key_b: %zu", size_pub_key_b);

	cmrt_pke_t pke = pke_open();
	/* Generate shared key A */
	int res = cmrt_pke_ffdh(pke, &params, priv_key_a, pub_key_b, NULL, shared_key_a);
	if (res != 0) {
		LOG_ERR("Sharedkey_a generation failed");
	} else {
		LOG_DBG("Sharedkey_a generation succeeded");
		memcpy(buffer, shared_key_a, params.mod_size);
		*buflen = params.mod_size;
	}
	pke_close(pke);
	return res;
}

static int process_privkey(uint8_t *argp, uint32_t argc)
{
	(void)argp; (void)argc;

	/* Check preconditions for exchange */
	if (!params.p || !params.q || !params.g) {
		LOG_ERR("Params not found, set params first");
		return -1;
	}

	cmrt_pke_t pke = pke_open();
	int res = cmrt_pke_ffdh_private_keygen(pke, params.mod_size, params.q, priv_key_a);
	if (res != 0) {
		LOG_ERR("Privkey generation failed");
	} else {
		LOG_DBG("Privkey generation succeeded");
	}
	pke_close(pke);
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

	if (MATCH(argp, argl, "parmset")) {
		int res = process_parmset(argp_next, argc);
		if (res != 0) {
			LOG_ERR("Parameter verification failed.");
		}
		return res;
	}
	if (MATCH(argp, argl, "parmgen")) {
		int res = process_parmgen(argp_next, argc);
		if (res != 0) {
			LOG_ERR("Parameter generation failed.");
		}
		return res;
	}
	if (MATCH(argp, argl, "exchange")) {
		int res = process_exchange(argp_next, argc);
		if (res != 0) {
			LOG_ERR("Exchange failed.");
		}
		return res;
	}
	if (MATCH(argp, argl, "shared")) {
		int res = process_shared(argp_next, argc, buflen);
		if (res != 0) {
			LOG_ERR("Shared failed.");
		}
		return res;
	}
	if (MATCH(argp, argl, "privkey")) {
		int res = process_privkey(argp_next, argc);
		if (res != 0) {
			LOG_ERR("Privkey generation failed.");
		}
		return res;
	}
	/* else */
	argp[argl] = '\0';
	LOG_ERR("%s: Invalid COMMAND", argp);
	return -1;
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
		if (buflen > 0) {
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen),
					"Response to HLOS:");
			res = cmrt_sic_write(sic, buffer, buflen, peerid);
			if (res < 0) {
				LOG_INF("Failed to write to HLOS: %d!", res);
				break;
			}
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
