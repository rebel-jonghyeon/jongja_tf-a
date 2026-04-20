
#include <shell/shell.h>
#include <cri/cmrt.h>
#include <cri/cmrt/aes.h>
#include <ctype.h>
#include <stdlib.h>
#include <teefs.h>
#include "oec_common.h"
#include "common.h"


static int idem(void *image, size_t imlen, uint8_t keynr)
{
	(void)image;
	(void)keynr;
	return imlen;
}

static int readfile(const char *name, void *buffer, size_t buflen)
{
	int res = -1;
	int file = teefs_open(name, strlen(name), 0);

	if (file >= 0) {
		res = teefs_read(file, buffer, &buflen);
		teefs_close(file);
	}

	return res;
}

static int getnr(const char *s)
{
	int res = -1;
	if (s && isdigit(s[0])) {
		char *e = NULL;
		int nr = strtol(s, &e, 0);
		if ((nr >= 0) && (e > s) && (e[0] == '\0')) {
			res = nr;
		}
	}
	return res;
}

static int
otp_shell_strobe(const struct shell *shell, size_t argc, char **argv)
{
	(void)shell;
	(void)argc;
	(void)argv;
	cri_otp_t oec = cri_otp_open(CRI_O_OTP_COMMIT);
	if (cri_is_valid(oec)) {
		cri_otp_close(oec);
	}
	return 0;
}

static int
otp_shell_file(const struct shell *shell, size_t argc, char **argv,
	       int (*f)(void *buffer, size_t buflen, uint8_t keynr))
{
	int res = -1;
	int keynr = 0;
	if (argc == 3) {
		keynr = getnr(argv[2]);
	}
	if ((argc >= 2) && (keynr >= 0) && (keynr < 2)) {
		/* then do it like we want it to be done with the key */
		uint32_t buffer[4192]; /* should be ok on stack!? */
		int res = -1;
		int buflen = readfile(argv[1], buffer, sizeof(buffer));
		/* we should most probably match length exactly if writing it
		 */
		if ((buflen > 0) && (buflen <= sizeof(buffer) - 16)) {
			/* we do a hex here, as there's no piping etc. */
			buflen = f(buffer, buflen, keynr);
			if (buflen > 0) {
				shell_hexdump(shell, (uint8_t *)buffer, buflen);
				res = 0;
			}
		}

	}

	return res;
}

static int
otp_shell_encrypt(const struct shell *shell, size_t argc, char **argv)
{
	return otp_shell_file(shell, argc, argv, oec_image_encrypt);
}

static int
otp_shell_decrypt(const struct shell *shell, size_t argc, char **argv)
{
	return otp_shell_file(shell, argc, argv, oec_image_decrypt);
}


static int otp_shell_show(const struct shell *shell, size_t argc, char **argv)
{
	return otp_shell_file(shell, argc, argv, idem);
}

static int hexc2u(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c + 10 - 'A';
	if (c >= 'a' && c <= 'f')
		return c + 10 - 'a';
	return -1;
}

static int unhexdump(const char *s, void *pbuf, size_t nbuf)
{
	char *p = pbuf;
	size_t n = 0;

	while (isxdigit(s[0]) && (n < nbuf)) {
		int d = (hexc2u(s[0]) << 4) | hexc2u(s[1]);
		if (d < 0)
			return -1;
		p[n++] = d;
		s += 2;
	}

	return (*s == '\0') ? n : -1;
}

/* Calculate the next IV bytes */
static uint64_t lfsr_next(uint64_t x)
{
	uint64_t mask = 0;
	if (x & 1)
		mask = (1ull << 62) | (1ull << 60) | (1ull << 59);
	x = (((x & 1) << 63) | (x >> 1)) ^ mask;
	return x;
}

static uint64_t lfsr_prev(uint64_t x)
{
	uint64_t mask = 0;
	x = (x << 1) | (x >> 63); /* ror(x, 1) */
	if (x & 1)
		mask = (1ull << 63) | (1ull << 61) | (1ull << 60);
	x ^= mask;
	return x;
}

static int adjust_iv(uint32_t *iv, long n)
{
	enum { k_max_iter = 10 };
	int res = -1;
	if ((n != 0) && (n >= -k_max_iter) && (n <= k_max_iter)) {
		uint64_t x = iv[0] | ((uint64_t)iv[1] << 32ull);
		for (; n < 0; ++n) {
			x = lfsr_prev(x);
		}
		for (; n > 0; --n) {
			x = lfsr_next(x);
		}
		iv[0] = (uint32_t)x;
		iv[1] = (uint32_t)(x >> 32ull);
		res = 0;
	}
	return res;
}

static int otp_shell_iv(const struct shell *shell, size_t argc, char **argv)
{
	uint32_t iv[4] = { 0 };
	int ivlen = 0;
	if (argc > 1) {
		ivlen = unhexdump(argv[1], iv, sizeof(iv));
		if (ivlen <= 0) {
			return -1;
		}
		if (argc > 2) {
			char *e = NULL;
			long n = strtol(argv[2], &e, 10);
			if ((e <= argv[2]) || (*e != '\0')) {
				return -1;
			}
			if (adjust_iv(iv, n) < 0) {
				return -1;
			}
		}
	}
	cri_otp_t oec = cri_otp_open(CRI_O_SYNC | CRI_O_OTP_COMMIT);
	if (cri_is_valid(oec)) {
		uint32_t *const hwiv = (uint32_t *)0x304080u;

		if (ivlen > 0) {
			cri_otp_oec_write(oec, OEC_ADDRESS_AES_IV, iv, ivlen);
		}
		for (unsigned i = 0; i < 4; ++i)
			iv[i] = hwiv[i];
		cri_otp_close(oec);
		shell_hexdump(shell, (const uint8_t *)iv, sizeof(iv));
	}
	return -1;
}


SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_cmd,
	SHELL_CMD(asis, NULL, "asis <file name>\tshow file contents",
		  otp_shell_show),
	SHELL_CMD(decrypt, NULL,
		  "decrypt <file name> [keynr]\tdump decrypted file",
		  otp_shell_decrypt),
	SHELL_CMD(encrypt, NULL,
		  "encrypt <file name> [keynr]\tdump encrypted file",
		  otp_shell_encrypt),
	SHELL_CMD(iv, NULL, "iv [hexiv]\tset iv on otp", otp_shell_iv),
	SHELL_CMD(strobe, NULL, "strobe\tselect and unselect otp driver",
		  otp_shell_strobe),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(otp, &sub_cmd, "otp and oec commands", NULL);
