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
#include <drivers/cmrt/aes.h>

#define BUFSZ 4096

/* Buffers where parsed+decoded input data is stored from the encrypt|decrypt
 * cmds. AAD data will overwrite buffer during parsing of encrypt|decrypt cmds.
 * */
static alignas(4) uint8_t _key[64];
static alignas(4) uint8_t _iv[64];
static alignas(4) uint8_t _tag[64];

static size_t _keylen;
static size_t _ivlen;
static size_t _taglen;
static size_t _aadlen;
static size_t _datalen;

static cmrt_aes_mode_t _mode = -1;
static cmrt_aes_operation_t _op = -1;

/* Global buffer for receive and response messages from SIC. */
static alignas(4) uint8_t buffer[BUFSZ + AES_BLOCK_BYTES /* some slack */];

/* Global buffer for intermediate computations such as storing encoded AAD (bn)
 * for ccm mode. */
static alignas(4) uint8_t tmp_buffer[BUFSZ];

/* Global aes context */
static cmrt_aes_t aes = CMRT_INVALID_HANDLE;

static void print_usage(void)
{
	LOG_INF("First message:  encrypt|decrypt MODE [TAGLEN | TAG] [AAD] KEY [IV]");
	LOG_INF("Next message(s): DATA or unaligned/empty for final");
	LOG_INF("MODE:   ecb|cbc|cfb|ctr|gcm|xts");
	LOG_INF("TAGLEN: Length of tag in bytes");
	LOG_INF("KEY:    ascii or 0x.. for hex data");
	LOG_INF("IV:     ascii or 0x.. for hex data");
	LOG_INF("AAD:    ascii or 0x... for hex AAD data.");
	LOG_INF("TAG:    0x... for hex AEAD TAG or '-' for empty");
	LOG_INF("DATA:   ascii or binary (no hex encoding)\n");

	LOG_INF("Note: DATA is unaligned iff length %% %lu != 0", AES_BLOCK_BYTES);
	LOG_INF("Note: TAGLEN, TAG and AAD are used for AEAD modes only");
	LOG_INF("Note: When using an AEAD mode you should provide either TAGLEN");
	LOG_INF("      (when 'encrypt') or TAG (when 'decrypt')");
}

/* Use carefully, no static checks done. */
#define STATIC_STRLEN(s) (sizeof((s))-1)

#define LOG_ERR_RET(retcode, ...) do { \
	LOG_ERR(__VA_ARGS__);	\
	return retcode;	\
} while(0)

static int aes_open(void)
{
	aes = cmrt_aes_open(0);
	if (!cmrt_is_valid(aes)) {
		LOG_ERR("Cannot open AES context!");
		return -1;
	}

	return 0;
}

static void aes_close(void)
{
	if (cmrt_is_valid(aes)) {
		LOG_INF("Closing AES context (resets state)");
		cmrt_aes_close(aes);
		aes = CMRT_INVALID_HANDLE;
		_keylen = _ivlen = _taglen = _aadlen = 0;
		_mode = -1;
		_op = -1;
	}
}

/* Advance p until whitespace is reached. Returns new value of p.
 * If end is reached returns end. */
static inline uint8_t *find_whitespace(uint8_t *p, uint8_t *end)
{
	for (; (uintptr_t)p < (uintptr_t)end && !isspace(*p); p++);
	return p;
}

/* Check if p >= end. Used when doing lookahead. */
#define ptr_oob(p, end) (((uintptr_t)(p)) >= ((uintptr_t)(end)))

static struct {
	const char *str;
	cmrt_aes_mode_t mode;
} cmd_mode[] = {
	{ "ecb", CMRT_AES_ECB	},
	{ "cbc", CMRT_AES_CBC	},
	{ "cfb", CMRT_AES_CFB	},
	{ "ctr", CMRT_AES_CTR	},
	{ "gcm", CMRT_AES_GCM	},
	{ "cmac", CMRT_AES_CMAC },
	{ "ccm", CMRT_AES_CCM },
	{ "xts", CMRT_AES_XTS }
};

/* Lenght of longest mode name, keep it updated. Now it's strlen("cmac") */
#define MODE_STR_MAX_LEN 4

#define MAX_DBG_LEN 64

static void debug_print_blob(uint8_t *blob, size_t sz, const char *info_text)
{
#ifdef CONFIG_DEBUG
	if (!blob || !sz) { return; }

	size_t sz_hex = sz*2;
	uint8_t blob_hex[MAX_DBG_LEN*2];
	size_t written = bin2hex(blob, MIN(sz, MAX_DBG_LEN), (char*)blob_hex, MAX_DBG_LEN*2);

	LOG_DBG("%s%.*s%s", info_text, (int)sz_hex, blob_hex,
		(written < sz_hex) ? "..." /*cropped*/ : "" );
#else
	(void)blob; (void)sz; (void)info_text;
#endif
}

static bool mode_is_aead(cmrt_aes_mode_t mode)
{
	if (mode == CMRT_AES_GCM || mode == CMRT_AES_CCM) {
		return true;
	}
	return false;
}

static ssize_t parse_num(uint8_t *p, uint8_t *end, size_t *out_val)
{
	if (ptr_oob(p, end) || isspace(*p)) { return -EINVAL; }

	char *_p;
	size_t val = (size_t)strtoul((const char *)p, &_p, 0);
	if (errno == EINVAL || errno == ERANGE) { return -errno; }
	*out_val = val;
	ssize_t skip = (ssize_t)( ((size_t)_p)-((size_t)p) );
	assert(skip >= 0);
	return skip;
}

static int parse_encrypt_decrypt(uint8_t *p, size_t buflen)
{
	uint8_t *end = buffer + buflen;

	/* parsing MODE */
	p++;
	if (p == end) {
		LOG_ERR_RET(-EINVAL, "Invalid MODE");
	}

	size_t i;
	_mode = -1;
	for (i = 0; i < ARRAY_SIZE(cmd_mode); i++) {
		size_t len = strlen(cmd_mode[i].str);
		if (memcmp(p, cmd_mode[i].str, len) == 0) {
			_mode = cmd_mode[i].mode;
			p += len;
			break;
		}
	}

	if (i == ARRAY_SIZE(cmd_mode)) {
		LOG_ERR_RET(-EINVAL, "Invalid MODE");
	}

	if (mode_is_aead(_mode)) {
		/* Parsing TAG (decrypt) or TAGLEN (encrypt). For decrypt TAGLEN is calculated from TAG.  */
		if (_op == CMRT_AES_ENCRYPT) {
			p++;
			if (p == end) { LOG_ERR_RET(-EINVAL, "Invalid TAGLEN"); }

			ssize_t _skip = parse_num(p, end, &_taglen);
			if (_skip <= 0) {
				LOG_ERR_RET(-EINVAL, "Invalid TAGLEN");
			}
			p += _skip;
		} else if (_op == CMRT_AES_DECRYPT) {
			p++;
			uint8_t *buf_tag = p;
			uint8_t *q = find_whitespace(buf_tag, end);
			_taglen = (size_t)q - (size_t)buf_tag;
			p = q;

			if (_taglen >= 2 && memcmp(buf_tag, "0x", 2) == 0) {
				size_t new_taglen = (_taglen-2) >> 1;
				if (new_taglen > sizeof(_tag)) {
					LOG_ERR_RET(-EINVAL, "Invalid TAG (too long)");
				}

				if (hex2bin((char *)buf_tag+2, _taglen-2, _tag,
					    new_taglen) != new_taglen) {
					LOG_ERR_RET(-EINVAL, "Invalid TAG");
				}
				_taglen = new_taglen;
			} else {
				if (_taglen > sizeof(_tag)) {
					LOG_ERR_RET(-EINVAL, "Invalid TAG (too long)");
				}
				memcpy(_tag, buf_tag, _taglen);
			}
		} else {
			abort();
		}
	}
	if (_mode == CMRT_AES_CCM) {
		/* Parse DATALEN (length in bytes of message to encrypt). */
		p++;
		ssize_t _skip = parse_num(p, end, &_datalen);
		if (_skip < 0) {
			LOG_ERR_RET(-EINVAL, "Invalid DATALEN");
		}
		p += _skip;
	}

	/* Parsing KEY */
	p++;
	if (p == end) {
		LOG_ERR_RET(-EINVAL, "Invalid KEY");
	}

	uint8_t *buf_key = p;
	uint8_t *q = find_whitespace(buf_key, end);
	_keylen = (size_t)q - (size_t)buf_key;
	p = q;

	if (_keylen >= 2 && memcmp(buf_key, "0x", 2) == 0) {
		/* Decode key if hex-encoded. */
		size_t new_keylen = (_keylen-2) >> 1;
		if (new_keylen > sizeof(_key)) {
			LOG_ERR_RET(-EINVAL, "Invalid KEY (too long)");
		}

		if (hex2bin((char *)buf_key+2, _keylen-2, _key, new_keylen) != new_keylen) {
			LOG_ERR_RET(-EINVAL, "Invalid KEY");
		}
		_keylen = new_keylen;
	} else {
		if (_keylen > sizeof(_key)) {
			LOG_ERR_RET(-EINVAL, "Invalid KEY (too long)");
		}

		memcpy(_key, buf_key, _keylen);
	}

	/* Parsing IV if provided. */
	if (p != end) {
		uint8_t *buf_iv = p+1;
		uint8_t *q = find_whitespace(buf_iv, end);
		_ivlen = (size_t)q - (size_t)buf_iv;

		if (_ivlen >= 2 && memcmp(buf_iv, "0x", 2) == 0) {
			/* Decode iv if hex-encoded. */
			size_t new_ivlen = (_ivlen-2) >> 1;
			if (new_ivlen > sizeof(_iv)) {
				LOG_ERR_RET(-EINVAL, "Invalid IV (too long)");
			}

			if (hex2bin((char *)buf_iv+2, _ivlen-2, _iv, new_ivlen) != new_ivlen) {
				LOG_ERR_RET(-EINVAL, "Invalid IV");
			}
			_ivlen = new_ivlen;
		} else {
			if (_ivlen > sizeof(_iv)) {
				LOG_ERR_RET(-EINVAL, "Invalid IV (too long)");
			}

			memcpy(_iv, buf_iv, _ivlen);
		}
	}

	/* For XTS, key must be 32 or 64 bytes in length and iv (xts tweak)
	 * must be AES_BLOCK_BYTES in length, and is not optional. */
	if (_mode == CMRT_AES_XTS) {
		if (_keylen != 32 && _keylen != 64) {
			LOG_ERR_RET(-EINVAL, "Invalid xts key length (must be 32 or 64)");
		}

		if (_ivlen != AES_BLOCK_BYTES) {
			LOG_ERR_RET(-EINVAL, "Invalid xts iv (tweak) len");
		}
	}

	return 0;
}

static int process_encrypt_decrypt(uint8_t *p, size_t *_buflen)
{
	size_t buflen = *_buflen;
	*_buflen = 0; /* No response message for now. */

	int res = parse_encrypt_decrypt(p, buflen);

	if (res < 0) {
		LOG_INF("Error parsing encrypt|decrypt message");
		return 0; /* Invalid message is not a fatal error. */
	}

	uint8_t *iv = _iv;
	if (!_ivlen) {
		iv = NULL;
	}

	/* Clean AES state in case previous operation did not complete. */
	aes_close();

	if (aes_open() < 0) { return -1; }

	if (_mode != CMRT_AES_CCM) {
		/* For CCM we can only do the init later, when we have the
		 * whole message to encrypt/decrypt and can encode the nonce
		 * and aad properly. */

		LOG_DBG("Performing cmrt_aes_init() with operation=%d "
			"mode%d taglen=%zu key=%p keylen=%zu iv=%p ivlen=%zu",
			_op, _mode, _taglen, _key, _keylen, iv, _ivlen);

		debug_print_blob(_key, _keylen, "key: 0x");
		debug_print_blob(iv, _ivlen, "iv: 0x");

		res = cmrt_aes_init(aes, _op, _mode, _key, _keylen, iv, _ivlen, _taglen);
		if (res < 0) {
			LOG_ERR("cmrt_aes_init() failed with %d", res);
			aes_close();
			return res; /* syscall error will exit the container */
		}
	}

	return 0;
}

static int process_cmac(uint8_t *p, size_t *_buflen)
{
	int res = -1;
	size_t buflen = *_buflen;
	*_buflen = 0; /* No response message for now. */

	/* Parsing the CMAC key */
	uint8_t *end = buffer + buflen;
	p++;
	uint8_t *buf_key = p;
	uint8_t *q = find_whitespace(buf_key, end);
	size_t keylen = (size_t)q - (size_t)buf_key;

	if (keylen >= 2 && memcmp(buf_key, "0x", 2) == 0) {
		size_t new_keylen = (keylen-2) >> 1;
		if (new_keylen > sizeof(_key)) {
			LOG_ERR_RET(-1, "Invalid KEY (too long)");
		}

		if (hex2bin((char*)buf_key+2, keylen-2, _key, new_keylen) != new_keylen) {
			LOG_ERR_RET(-1, "Invalid KEY");
		}
		keylen = new_keylen;
	} else {
		if (keylen > sizeof(_key)) {
			LOG_ERR_RET(-1, "Invalid KEY (too long)");
		}
		memcpy(_key, buf_key, keylen);
	}

	if ((res = aes_open()) < 0) { return -1; }

	LOG_DBG("Performing cmrt_aes_init() for CMAC");
	debug_print_blob(_key, keylen, "key: 0x");

	res = cmrt_aes_init(aes, CMRT_AES_ENCRYPT, CMRT_AES_CMAC, _key, keylen,
		NULL/*iv*/, 0/*ivlen*/, 16 /*taglen, hardcoded for CMAC*/);
	if (res < 0) {
		LOG_ERR("cmrt_aes_init() failed with %d", res);
		aes_close();
		return res;
	}

	_mode = CMRT_AES_CMAC;

	return 0;
}

static int process_data_cmac(uint8_t *buffer, size_t *_buflen)
{
	size_t buflen = *_buflen;
	*_buflen = 0;
	int res = -1;

	if (buflen > 0 && (buflen & (AES_BLOCK_BYTES-1)) == 0) {
		LOG_DBG("cmac: performing cmrt_aes_update_aad() with aadlen=%zu", buflen);
		res = cmrt_aes_update_aad(aes, buffer, buflen);

		if (res < 0) {
			LOG_ERR("cmac: cmrt_aes_update_aad failed with %d", res);
			goto err;
		}
	} else {
		/* Unaligned or empty message, this is the last one. */
		if (buflen) {
			LOG_DBG("cmac: performing cmrt_aes_final_aad() with aadlen=%zu", buflen);
			res = cmrt_aes_final_aad(aes, buffer, buflen);

			if (res < 0) {
				LOG_ERR("cmac: cmrt_aes_final_aad failed with %d", res);
				goto err;
			}
		}

		LOG_DBG("cmac: performing cmrt_aes_ae_final");
		size_t taglen = 16; /* hardcoded for CMAC */
		res = cmrt_aes_ae_final(aes, NULL, 0, NULL, _tag, &taglen);
		if (res < 0) {
			LOG_ERR("cmac: cmrt_aes_ae_final failed with %d", res);
			goto err;
		}

		memcpy(buffer, _tag, taglen);
		*_buflen = taglen;

		aes_close();
	}

	return 0;

err:
	aes_close();
	return res;
}

static int process_data_aead(uint8_t *buffer, size_t *_buflen)
{
	static enum {
		EXPECTING_GCM_AAD,
		EXPECTING_GCM_DATA
	} gcm_state = EXPECTING_GCM_AAD;

	size_t buflen = *_buflen;
	*_buflen = 0; /* No response message by default until we set it. */
	int res = -1;

	assert(cmrt_is_valid(aes));

	switch (gcm_state) {
	case EXPECTING_GCM_AAD:
		if (buflen > 0 && (buflen & (AES_BLOCK_BYTES-1)) == 0) {
			LOG_DBG("aead: performing cmrt_aes_update_aad() with aadlen=%zu", buflen);
			res = cmrt_aes_update_aad(aes, buffer, buflen);

			if (res < 0) {
				LOG_ERR("aead: cmrt_aes_update_aad failed with %d", res);
				goto err;
			}
		} else {
			LOG_DBG("aead: performing cmrt_aes_final_aad() with aadlen=%zu", buflen);
			res = cmrt_aes_final_aad(aes, buffer, buflen);
			if (res < 0) {
				LOG_ERR("aead: cmrt_aes_final_aad failed with %d", res);
				goto err;
			}
			gcm_state = EXPECTING_GCM_DATA;
		}
		*_buflen = 0;
		break;
	case EXPECTING_GCM_DATA:
		if (buflen > 0 && (buflen & (AES_BLOCK_BYTES-1)) == 0) {
			LOG_DBG("aead: Doing cmrt_aes_update (inlen=%zu)...", buflen);
			res = cmrt_aes_update(aes, buffer, buflen, buffer);
			if (res < 0) {
				LOG_ERR("aead: cmrt_aes_update failed with %d", res);
				goto err;
			}
			*_buflen = buflen;

			/* Message was multiple of 16. Not closing aes,
			   waiting for more input */
		} else {
			uint8_t *buf = buffer;
			LOG_DBG("Doing cmrt_aes_ae_final (inlen=%zu, taglen=%zu)...", buflen, _taglen);
			res = cmrt_aes_ae_final(aes, buf, buflen, buf, _tag, &_taglen);
			if (res < 0) {
				LOG_ERR("aead: cmrt_aes_final failed with %d", res);
				goto err;
			}


			if (_op == CMRT_AES_ENCRYPT || _op == CMRT_AES_DECRYPT) {
				memcpy(buffer+buflen, _tag, _taglen);
				*_buflen = buflen+_taglen;
			} else {
				abort();
			}

			aes_close();
			gcm_state = EXPECTING_GCM_AAD;
		}

		break;
	default:
		LOG_ERR("Corrupted gcm_state");
		abort();
	}

	return 0;

err:
	*_buflen = 0; /* No response message in case of error */
	gcm_state = EXPECTING_GCM_AAD;
	aes_close();
	return res;
}

static int process_data(uint8_t *buffer, size_t *_buflen)
{
	size_t buflen = *_buflen;
	*_buflen = 0; /* No response message by default until we set it. */
	int res = -1;

	assert(cmrt_is_valid(aes));

	if (!buflen) {
		aes_close();
		return 0;
	}

	if ((buflen & (AES_BLOCK_BYTES-1)) == 0) {
		LOG_DBG("Doing cmrt_aes_update (inlen=%zu)...", buflen);
		res = cmrt_aes_update(aes, buffer, buflen, buffer);
		if (res < 0) {
			LOG_ERR("cmrt_aes_update failed with %d", res);
			goto err;
		}
		*_buflen = buflen;
	} else {
		/* For block modes (ECB, CBC), pad the last block with zeros
		 * or output block will be truncated (at least for encrypt)
		 * and then will output garbage when decrypting.
		 */
		if (_mode == CMRT_AES_ECB || _mode == CMRT_AES_CBC) {
			buflen = ROUND_UP(buflen, 16);
			/* NOTE: There's zeroes in the buffer already! */
		}

		LOG_DBG("Doing cmrt_aes_final (inlen=%zu)...", buflen);
		res = cmrt_aes_final(aes, buffer, buflen, buffer);
		if (res < 0) {
			LOG_ERR("cmrt_aes_final failed with %d", res);
			goto err;
		}
		aes_close();
		*_buflen = buflen;
	}

	return 0;

err:
	*_buflen = 0; /* No response message in case of error */
	aes_close();
	return res;
}

static int process_data_ccm(uint8_t *buffer, size_t *_buflen)
{
	/* First CCM data message must be the entire AAD or empty if none.
	 * Second one must be entire data to encrypt/decrypt or empty if none.*/
	static enum {
		EXPECTING_CCM_AAD,
		EXPECTING_CCM_DATA
	} ccm_state = EXPECTING_CCM_AAD;
	static size_t ccm_datalen;

	alignas(4) uint8_t nonce[16] = {0};
	size_t buflen = *_buflen;
	*_buflen = 0;
	int res = -1;


	assert(cmrt_is_valid(aes));

	switch (ccm_state) {
	case EXPECTING_CCM_AAD:
		LOG_DBG("ccm: expecting AAD (in a single message)");
		int has_aad = buflen != 0;
		LOG_DBG("ccm_encode_nonce: _ivlen=%zu _datalen=%zu _taglen=%zu hasaad=%d",
			_ivlen, _datalen, _taglen, has_aad);
		res = cmrt_aes_ccm_encode_nonce(nonce, sizeof(nonce), _iv, _ivlen,
			_datalen, _taglen, has_aad);
		if (res < 0) {
			LOG_ERR("cmrt_aes_ccm_encode_nonce failed with %d", res);
			goto err;
		}

		res = cmrt_aes_ccm_encode_aad(tmp_buffer, sizeof(tmp_buffer), buffer, buflen);
		if (res < 0) {
			LOG_ERR("cmrt_aes_ccm_encode_aad failed with %d", res);
			goto err;
		}
		_aadlen = (size_t)res;

		res = cmrt_aes_init(aes, _op, CMRT_AES_CCM, _key, _keylen, nonce,
			sizeof(nonce), _taglen);

		if (res < 0) {
			LOG_ERR("ccm: cmrt_aes_init failed with %d", res);
			goto err;
		}

		res = cmrt_aes_final_aad(aes, tmp_buffer, _aadlen);
		if (res < 0) {
			LOG_ERR("ccm: cmrt_aes_final_aad failed with %d", res);
			goto err;
		}

		ccm_datalen = _datalen;
		ccm_state = EXPECTING_CCM_DATA;
		break;
	case EXPECTING_CCM_DATA:
		LOG_DBG("ccm: expecting DATA");

		if (buflen > 0 && (buflen & (AES_BLOCK_BYTES-1)) == 0
		    && buflen < ccm_datalen) {
			res = cmrt_aes_update(aes, buffer, buflen, buffer);
			if (res < 0) {
				LOG_ERR("ccm: cmrt_aes_update failed with %d", res);
				goto err;
			}
			ccm_datalen -= buflen;
			*_buflen = buflen;
		} else if (buflen == ccm_datalen) {

			LOG_DBG("ccm: Doing cmrt_aes_ae_final (inlen=%zu, taglen=%zu)...",
				buflen, _taglen);
			res = cmrt_aes_ae_final(aes, buffer, buflen, buffer, _tag, &_taglen);
			if (res < 0) {
				LOG_ERR("cmrt_aes_final failed with %d", res);
				goto err;
			}

			if (_op == CMRT_AES_ENCRYPT || _op == CMRT_AES_DECRYPT) {
				memcpy(buffer+buflen, _tag, _taglen);
				*_buflen = buflen + _taglen;
			} else {
				abort();
			}

			ccm_state = EXPECTING_CCM_AAD; /* reset for next call */
			ccm_datalen = 0;
			aes_close();
		} else {
			LOG_DBG("ccm: buffer length mismatch (inlen=%zu, expected=%zu)",
				buflen, ccm_datalen);
			ccm_state = EXPECTING_CCM_AAD;
			ccm_datalen = 0;
		}

		break;
	default:
		LOG_ERR("Corrupted ccm_state");
		abort();
	}

	return 0;

err:
	*_buflen = 0;
	ccm_state = EXPECTING_CCM_AAD; /* reset for next call */
	aes_close();
	return res;
}

static int process_data_xts(uint8_t *buffer, size_t *_buflen)
{
	static enum {
		XTS_STATE_UPDATE,
		XTS_STATE_FINAL,
		XTS_STATE_ERROR
	} xts_state = XTS_STATE_ERROR;

	size_t buflen = *_buflen;
	*_buflen = 0;
	int res = -1;

	if (buflen > 0 && (buflen & (AES_BLOCK_BYTES-1)) == 0) {
		xts_state = XTS_STATE_UPDATE;
	} else {
		xts_state = XTS_STATE_FINAL;
	}

	switch (xts_state) {
	case XTS_STATE_UPDATE:
		res = cmrt_aes_update(aes, buffer, buflen, buffer);
		if (res < 0) {
			LOG_ERR("process_data_xts: cmrt_aes_update failed with %d", res);
			goto err;
		}
		*_buflen = buflen;
		break;
	case XTS_STATE_FINAL:
		if (buflen > 0 && buflen < AES_BLOCK_BYTES) {
			LOG_ERR("process_data_xts: Calling final with less than one block."
					"This will make the call fail for xts mode.");
		}

		res = cmrt_aes_final(aes, buffer, buflen, buffer);
		if (res < 0) {
			LOG_ERR("process_data_xts: cmrt_aes_final failed with %d", res);
			goto err;
		}
		*_buflen = buflen;
		aes_close();
		break;
	default:
		LOG_ERR("process_message_xts: Corrupted xts state!");
		goto err;
	}

	return 0;
err:
	*_buflen = 0; /* No response message in case of error */
	aes_close();
	return res;
}

/* NOTE: *_buflen is the length of the message in the buffer.
 * Before returning, the response message must be written in buffer and
 * _buflen must be set to the length of the response message or 0 if none.
 */
static int process_message(uint8_t *buffer, size_t *_buflen)
{
	uint8_t *p = buffer;

	if (cmrt_is_valid(aes)) {
		/* hex decode input (if needed) before processing */
		if (*_buflen > 2 && memcmp(buffer, "0x", 2) == 0) {
			size_t new_buflen = ((*_buflen)-2) >> 1;
			if (hex2bin((char*)buffer+2, (*_buflen)-2, buffer, new_buflen) != new_buflen) {
				*_buflen = 0;
				LOG_ERR_RET(-EINVAL, "Invalid data");
			}
			*_buflen = new_buflen;
		}

		if (_mode == CMRT_AES_GCM) {
			return process_data_aead(buffer, _buflen);
		} else if (_mode == CMRT_AES_CMAC) {
			return process_data_cmac(buffer, _buflen);
		} else if (_mode == CMRT_AES_CCM) {
			return process_data_ccm(buffer, _buflen);
		} else if (_mode == CMRT_AES_XTS) {
			return process_data_xts(buffer, _buflen);
		}

		return process_data(buffer, _buflen);
	}

	if (*_buflen == 0) {
		return 0;
	}

	if (memcmp(p, "encrypt", STATIC_STRLEN("encrypt")) == 0) {
		p += STATIC_STRLEN("encrypt");
		_op = CMRT_AES_ENCRYPT;
		return process_encrypt_decrypt(p, _buflen);
	} else if (memcmp(p, "decrypt", STATIC_STRLEN("decrypt")) == 0) {
		p += STATIC_STRLEN("decrypt");
		_op = CMRT_AES_DECRYPT;
		return process_encrypt_decrypt(p, _buflen);
	} else if (memcmp(p, "cmac", STATIC_STRLEN("cmac")) == 0) {
		p += STATIC_STRLEN("cmac");
		_op = -1;
		return process_cmac(p, _buflen);
	}

	LOG_ERR("Invalid COMMAND");
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
		/* memset(buffer, 0, sizeof(buffer)); */
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
