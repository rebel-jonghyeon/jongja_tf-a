/*
 * Copyright (c) 2019-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_math.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"
#include "pke_internal.h"

/**
 * Products of small primes packed into 32-bit words
 */
static const uint32_t primes[] = {
	/* 512-bit primes */
	0xc0cfd797, 0x05aa381f, 0x361592b7, 0xf64d985d, 0x073b5a0d, 0x0f5a0395,
	0x1d43ffdd, 0x323e7003, 0x4e5884b7, 0x7eb0f0b1, 0xb72efc93, 0x0102dedd,
	0x01341eff, 0x0163888f, 0x01c7ff8d, 0x021b8e8f, 0x028c4daf, 0x02ede03d,
	0x0000017b,
	/* 1024-bit primes */
	0x0386863f, 0x0418949b, 0x04aedb5b, 0x0534666d, 0x05d0651b, 0x067e44fb,
	0x07587c67, 0x08444cd7, 0x09d3206b, 0x0ae71bf9, 0x0bf8b47b, 0x0d065761,
	0x0df45e8f, 0x0f806d65, 0x10986041, 0x11f36ba9, 0x13b8340d, 0x1616f5fd,
	0x000843f7,
	/* 1536-bit primes */
	0x192d52bd, 0x1af690dd, 0x1e3edd3f, 0x20a97ea1, 0x2248eb29, 0x256db61f,
	0x27be57c3, 0x2a578f87, 0x2e5bc8f9, 0x31c4e00f, 0x3555f625, 0x38ba8399,
	0x3cbd7a99, 0x3fef5c69, 0x431b892f, 0x46a73431, 0x4b9041f9, 0x00000445,
	/* 2048-bit primes */
	0x4ffb76d3, 0x54699c4f, 0x5bfebb75, 0x61d842d5, 0x67977035, 0x6d07df9b,
	0x715cdbdb, 0x7a90b2c1, 0x7f421c29, 0x830d2b13, 0x87bd13a5, 0x9327e8c9,
	0x9e1c6947, 0xaa899b9d, 0xafa36a13, 0xb5d63549, 0x0020bf8d,
#if RSA_MAX_KEY_SIZE == 8192
	/* 4096-bit primes */
	0xc2aa2c0d, 0xc6a045e7, 0xd2000ba7, 0xdd3e200b, 0xe4c1637b, 0xededeb91,
	0xf6bdfdff, 0xfc50d403, 0x0028a3e7, 0x002a0c07, 0x002a740f, 0x002bd6bd,
	0x002c4e27, 0x002d3f23, 0x002e09c1, 0x002ebadb, 0x002fb1ef, 0x00309e2d,
	0x003129e5, 0x0032604d, 0x00339a61, 0x00350437, 0x003578ff, 0x0035d0e3,
	0x0036cb4d, 0x0037aa5b, 0x0038f48f, 0x003a0583, 0x003b9437, 0x003c6d1b,
	0x003ce9c3, 0x003d7681, 0x003e628b, 0x003f20ab, 0x0040a04b, 0x0041b2b5,
	0x00425555, 0x0042e82b, 0x00440fff, 0x00453a43, 0x0045d055, 0x004666f7,
	0x0047d9d3, 0x004a3045, 0x004aff81, 0x004c6d03, 0x004d0aa1, 0x004e7d0f,
	0x004f1cc9, 0x005004bb, 0x0050eddd, 0x005244cb, 0x00538d0f, 0x005431e5,
	0x005545df, 0x00565bf5, 0x0056de3b, 0x00579907, 0x0058eb3b, 0x005a19d3,
	0x005b2487, 0x005c90b1, 0x005d7835, 0x006048af, 0x00620e61, 0x0062e8bb,
	0x0063881b, 0x0065f64d, 0x00673a51, 0x0068a995, 0x006a58cf, 0x006bcd83,
	0x006c88a9, 0x006d9837, 0x006e3fff, 0x006ee837, 0x006ffab5, 0x00708f07,
	0x0071b8e3, 0x0072f9a1, 0x00743c0f, 0x00762e1d, 0x00771ddb, 0x0077ccc3,
	0x0079dc33, 0x007b1237, 0x007c499b, 0x007daf13, 0x00000b47,
#endif
};

/**
 * The base u is generated using the following algorithm
 **
 * n = 2048; k = 2; pp = 1; tpp = 1; bitoffset = 0;
 * While[BitLength[tpp] < n,
 *   pp = tpp; tpp *= Prime[k]; k++;
 * ];
 * ftab = FactorInteger[pp];
 * u = 0;
 * For[i = 1, i <= k - 3, i++,
 *   p = ftab[[i]][[1]];
 *   up = p;
 *   While[(JacobiSymbol[-up, p] != -1) &&
 *         (JacobiSymbol[-Mod[u + up*(pp/p)^2, pp], pp] != -1),
 *    bitoffset = bitoffset + BitLength[p] + 1;
 *    up = BitAnd[Ceiling[Pi*2^bitoffset], 2^(BitLength[p] + 1) - 1];
 *    up = Mod[up, p];
 *  ];
 *   u = Mod[u + up*(pp/p)^2, pp];
 * ];
 * Return[u]
 */
static const uint32_t base_u[] = {
#if RSA_MAX_KEY_SIZE == 8192
	0x02006135, 0x7f8491d9, 0xfd5b87db, 0x2a856fd4, 0xda638bef, 0x91c2dbfe,
	0xe82ab05c, 0x716e825d, 0xa628ed00, 0xd315050d, 0xf7b284d2, 0x0627e8f6,
	0x9b5fcb4c, 0x2fc380db, 0x78248ded, 0xcb29fc42, 0x6510640b, 0x4c544588,
	0x301c7db8, 0x826b9000, 0x84b55fef, 0x1f6c36ed, 0x8670b21e, 0x87ad20bd,
	0x426a988e, 0xb8f090a2, 0x6d2e4bfb, 0xfc544007, 0x260c9633, 0x2ebe707b,
	0x39f47ec3, 0x191331aa, 0x25cfab81, 0x74e0f6a7, 0x5b289eae, 0x4848a9cc,
	0x75c1b1cb, 0xb6c32f87, 0xe4afad23, 0xa9ef56a6, 0x61268643, 0xf1418e5c,
	0x06c44612, 0x16d09416, 0xb7752ecc, 0x2038aac5, 0x526ec03d, 0xd1ab3a06,
	0x653db101, 0x8c7a4992, 0x1f612c2d, 0x13f8b04a, 0x1b5e0707, 0x7e8e43f8,
	0x5dffac2f, 0xc04b8bc4, 0x452dc36c, 0x826d8a6b, 0xa7aaa0f2, 0x344f3f76,
	0x67e4003b, 0x4ac8fe78, 0x9b5a8ece, 0xf6d46df6, 0x791a14e2, 0x14f729c0,
	0x44f1191b, 0xed570941, 0xcb5d0561, 0x40f6ff62, 0xd6af2eed, 0xb9630378,
	0x61048cc5, 0xc8dc16f8, 0xebd40282, 0x63b90dbd, 0x754ec698, 0xebae923d,
	0x16852458, 0xbd9459db, 0x601f2190, 0xfafb3f52, 0x48eb9a7f, 0x4664c8e7,
	0xf0f16b91, 0xb66ad8fc, 0x2c26064e, 0xd147b5d4, 0xada313cb, 0x2f062ddd,
	0xbb20ee8c, 0x59e8b4eb, 0xfc12bd5c, 0x536f6ead, 0x89b8c975, 0x0ffec950,
	0xfd2b371a, 0x1018c06f, 0x65401e59, 0x9c2980b8, 0x48f0675e, 0x5039b349,
	0x15e31b47, 0xa0fa2ccd, 0x4febb68f, 0xa7cc5eb1, 0x6413879d, 0xe690aae1,
	0x1d1b2d9c, 0x2cd1f9bf, 0x7b77acc1, 0xdd0e4496, 0xd10c64b0, 0xb6d4b684,
	0xc350b7e4, 0xd0bd6b21, 0x8a51e3c4, 0xfad060b8, 0xb4496a12, 0xc8d35566,
	0x8813637a, 0x3b222d4f, 0x63994c4d, 0x08fb2bd0, 0x1ad264ce, 0xca6b0d10,
	0x8b8bbdb8, 0x07c0cb16
#else
	0xa895426b, 0xc7c5ed1f, 0x9999591b, 0xa9b0e391, 0xf723b0be, 0x2eea5437,
	0xeafc5bc3, 0x194aae81, 0xa12940d9, 0x09053070, 0xb427e939, 0x740852c3,
	0x02fdae15, 0xfa2c4396, 0x5c9f0e41, 0x6c987e36, 0xc262ea1e, 0xf7f986d3,
	0x6c24acf2, 0x525312a7, 0xac33b3df, 0xbb764870, 0xa39ebe23, 0xe24e850d,
	0xdd41b5bb, 0xa501636c, 0xc3f6541b, 0x668e9dab, 0xa275114e, 0xada5794a,
	0xe2a9d471, 0x8f36adff, 0xec358338, 0xd66240be, 0xa632707d, 0xe32cb81c,
	0x5c16cef1, 0xf335fc6e, 0xf9ee889d, 0xd2dc8886, 0xe94878c6, 0x3405a78b,
	0xca07bece, 0xdb8861dd, 0x2256f811, 0xdff752de, 0x61ba19c9, 0x5434620f,
	0xdbc35265, 0x2c6ca953, 0x42d91ef7, 0x4130ab6a, 0x0aadeaf3, 0xe0856f32,
	0x4e86087a, 0x94c6cfdf, 0x2968dba2, 0x2f134d5d, 0x3f9d1771, 0x30a936a6,
	0x8091f106, 0x60ee16aa, 0x101f2ba3, 0x17ffa47f
#endif
};

static const uint32_t cmds_zero[] = {
	SLOT_CMD(LOAD,          R_MAU_ZERO),
	SLOT_CMD(STORE,         SLOT(0)),
	SLOT_CMD(STORE,         SLOT(1)),
	SLOT_CMD(STORE,         SLOT(2)),
	SLOT_CMD(STORE,         SLOT(3)),
	SLOT_CMD(STORE,         SLOT(4)),
	SLOT_CMD(STORE,         SLOT(5)),
	SLOT_CMD(STORE,         SLOT(6)),
};

static const uint32_t cmds_generate_u[] = {
	SLOT_CMD(SET_MAND,       SLOT(primegen_qr_r)),
	SLOT_CMD(MONT_MUL,       R_MAU_ONE),
	SLOT_CMD(CANON,          0),
	SLOT_CMD(STORE,          SLOT(primegen_qr_r)),
	SLOT_CMD(MONT_MUL,       SLOT(primegen_qr_r)),
	SLOT_CMD(CANON,          0),
	SLOT_CMD(STORE,          SLOT(primegen_qr_r)),
	SLOT_CMD(MOD_ADD,        SLOT(primegen_qr_u)),
	SLOT_CMD(CANON,          0),
	SLOT_CMD(STORE,          SLOT(primegen_qr_r)),
	SLOT_CMD(MONT_MUL,       SLOT(primegen_qr_x)),
	SLOT_CMD(CANON,          0),
	SLOT_CMD(STORE,          SLOT(primegen_qr_x)),
};

static const uint32_t cmds_generate_candidate[] = {
	SLOT_CMD(SET_MAND,       SLOT(primegen_qr_c)),
	SLOT_CMD(INT_MUL,        SLOT(primegen_qr_m)),
	SLOT_CMD(LOAD,           SLOT(primegen_qr_c)),
	SLOT_CMD(INT_ADD,        SLOT(primegen_qr_x)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_c)),
};

static const uint32_t cmds_set_x[] = {
	SLOT_CMD(LOAD,           SLOT(primegen_qr_u)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_ub)),  /* backup u */
	SLOT_CMD(LOAD,           SLOT(primegen_qr_x)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_xb)),  /* backup x */
	SLOT_CMD(INT_ADD,        SLOT(primegen_qr_x)),
	SLOT_CMD(INT_ADD,        SLOT(primegen_qr_m)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_x)),
	SLOT_CMD(LOAD,           SLOT(primegen_qr_m)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_mb)),  /* backup m */
	SLOT_CMD(INT_ADD,        SLOT(primegen_qr_m)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_m)),
};


static const uint32_t cmds_restore_params[] = {
	SLOT_CMD(LOAD,           R_MAU_ZERO),
	SLOT_CMD(STORE,          SLOT(primegen_qr_mr)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_xr)),
	SLOT_CMD(LOAD,           SLOT(primegen_qr_xb)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_x)),
	SLOT_CMD(LOAD,           SLOT(primegen_qr_ub)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_u)),
	SLOT_CMD(LOAD,           SLOT(primegen_qr_mb)),
	SLOT_CMD(STORE,          SLOT(primegen_qr_m)),
};

#ifdef CONFIG_CMRT_FFDH
static int ___pke_generate_prime(cmrt_pke_t pke,
				 uint32_t bits,
				 uint8_t slot_number,
				 uint32_t qbits,
				 uint8_t *q,
				 uint8_t flags)
#else
int cmrt_pke_generate_prime(cmrt_pke_t pke,
			    uint32_t bits,
			    uint8_t slot_number,
			    uint8_t flags)
#endif
{
	int ret = -EPERM;

	uint32_t i;
	uint32_t length;
	uint32_t word_length;
	uint32_t prime_word_length;
	uint32_t max_length;
	uint32_t max_bit_length;
	uint32_t random_length;
	uint32_t m_bit_length;
	uint32_t bit_length_diff;
	uint32_t bit_mask;
	uint32_t counter = 0;
	uint32_t min_test;
	uint32_t candidate;
	uint32_t prime = 0;

	uint32_t *aptr = NULL;
	uint32_t *bptr = NULL;
	uint32_t *uptr = NULL;
	uint32_t *mptr = NULL;
	uint32_t *rptr = NULL;
	uint32_t *srptr = NULL;

	const uint32_t minimum[] = { 0x754abe9f, 0x597d89b3, 0xf9de6484, 0xb504f333 };
#ifdef CONFIG_CMRT_FFDH
	const uint32_t dh_minimum = 0x80000000;
#endif

	max_length = (MAU_READ_REG(R_MAU_MAX_LEN) / 2);
	word_length = (bits / 8) / sizeof(uint32_t);
#ifdef CONFIG_CMRT_FFDH
	if ((flags == DH_SETUP_REQUIRED) || (flags == DH_GENERATE_P)) {
		prime_word_length = ((bits - qbits) / 8) / sizeof(uint32_t);
	} else {
		prime_word_length = word_length;
	}
#else
	prime_word_length = word_length;
#endif

#ifdef CONFIG_CMRT_PKE_32_BIT
	length = (bits / 8) / sizeof(uint32_t);
	max_bit_length = max_length * 32;
	random_length = length + 2;
#else /* 64-bit */
	length = (bits / 8) / sizeof(uint64_t);
	max_bit_length = max_length * 64;
	random_length = length + 1;
#endif

	aptr = pke_addr(primegen_setup_qr_acc, NULL, max_bit_length);
#ifdef CONFIG_CMRT_FFDH
	if ((flags == SETUP_REQUIRED) || (flags == DH_SETUP_REQUIRED) || (flags == DH_GENERATE_P)) {
#else
	if (flags == SETUP_REQUIRED) {
#endif
		/* Generate product of primes and starting product QNR
		 * allowing space for maximum possible prime size
		 */
		ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, max_length);

		ret = cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), max_length);
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_MAND, SLOT(primegen_setup_qr_acc), max_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		bptr = pke_addr(primegen_setup_qr_b, NULL, max_bit_length);
		uptr = pke_addr(primegen_setup_qr_u, NULL, max_bit_length);
		aptr[0] = 1;

		memcpy(uptr, base_u, sizeof(base_u));

		i = 0;
		do {
			bptr[0] = primes[i];
			ISSUE_MAU_COMMAND(INT_MUL, SLOT(primegen_setup_qr_b), max_length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}

			if ((aptr[prime_word_length] == 0) || (bits == RSA_MAX_KEY_SIZE / 2)) {
				ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_setup_qr_acc), max_length);
				ISSUE_MAU_COMMAND(STORE, SLOT(primegen_setup_qr_m), max_length);

				ret = cmrt_pke_wait();
				if (ret) {
					goto err;
				}
			}

			i++;
		} while (((aptr[prime_word_length] == 0) && (bits < RSA_MAX_KEY_SIZE / 2)) ||
			 ((i < sizeof(primes)/sizeof(uint32_t)) && (bits == RSA_MAX_KEY_SIZE / 2)));

		static const uint32_t cmds_create_m_u[] = {
			SLOT_CMD(COPY,          SLOT(primegen_setup_qr_m)),
			SLOT_CMD(SET_PARAMS,    SLOT(primegen_setup_qr_acc)),
			SLOT_CMD(SET_MAND,      SLOT(primegen_setup_qr_u)),
			SLOT_CMD(MONT_MUL,      R_MAU_ONE),
			SLOT_CMD(CANON,         0),
			SLOT_CMD(STORE,         SLOT(primegen_setup_qr_b)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_create_m_u, sizeof(cmds_create_m_u)/sizeof(uint32_t), max_length);
		if (ret) {
			goto err;
		}

		/* Change slot size to length of requested prime number
		 * Moving the contents of slot 1 could be done in the MAU but we
		 * use memcpy for clarity
		 */
		uptr = pke_addr(primegen_qr_u, NULL, bits);
		memcpy(uptr, bptr, word_length * sizeof(uint32_t));
		mptr = pke_addr(primegen_qr_m, NULL, bits);
		memcpy(mptr, aptr, word_length * sizeof(uint32_t));

		/* Setup prime generation with correct slot size
		 * m is in slot primegen_qr_m
		 * u is in slot primegen_qr_u
		 */
		static const uint32_t cmds_zero_setup[] = {
			SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
			SLOT_CMD(LOAD,          R_MAU_ZERO),
			SLOT_CMD(STORE,         SLOT(primegen_qr_mr)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_sr)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_c)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_cu)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_x)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_xr)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_mb)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_ub)),
			SLOT_CMD(STORE,         SLOT(primegen_qr_xb)),
			SLOT_CMD(STORE,         SLOT(primegen_phi_high)),
			SLOT_CMD(STORE,         SLOT(primegen_p)),
			SLOT_CMD(STORE,         SLOT(primegen_q)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_zero_setup, sizeof(cmds_zero_setup)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_PARAMS, SLOT(primegen_qr_m), random_length);
		ISSUE_MAU_COMMAND(LOAD, R_MAU_ONE, random_length);
		ISSUE_MAU_COMMAND(STORE, SLOT(primegen_qr_x), random_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		/* Randomize u and put result in x */
		rptr = pke_addr(primegen_qr_r, NULL, bits);
		for (i = 0; i < 6; i++) {
			ret = cmrt_pke_get_true_random(rptr, (word_length + 2) * sizeof(uint32_t));
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_mau_command_sequence(cmds_generate_u, sizeof(cmds_generate_u)/sizeof(uint32_t), random_length);
			if (ret) {
				goto err;
			}
		}

		/* Generate 2x + m and 2 m
		 * Backing up u, x, m for next candidate
		 */
		ret = cmrt_pke_mau_command_sequence(cmds_set_x, sizeof(cmds_set_x)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

#ifdef CONFIG_CMRT_FFDH
		if (flags == DH_GENERATE_P) {
			memcpy(pke_addr(ffdh_parmgen_q, NULL, word_length * 32), q, qbits / 8);

			ret = cmrt_pke_binary_xgcd(primegen_qr_mb, ffdh_parmgen_q, primegen_qr_mb, word_length * sizeof(uint32_t), 0, ffdh_parmgen_inv_q);
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_mau_command_sequence(cmds_restore_params, sizeof(cmds_restore_params)/sizeof(uint32_t), length);
			if (ret) {
				goto err;
			}

			ISSUE_MAU_COMMAND(SET_PARAMS, SLOT(primegen_qr_m), random_length);

			ret = cmrt_pke_mau_command_sequence(cmds_set_x, sizeof(cmds_set_x)/sizeof(uint32_t), length);
			if (ret) {
				goto err;
			}
		}
#endif

	} else if (flags == SETUP_DONE) {
		rptr = pke_addr(primegen_qr_r, NULL, bits);
		ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);

		ret = cmrt_pke_mau_command_sequence(cmds_restore_params, sizeof(cmds_restore_params)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_PARAMS, SLOT(primegen_qr_m), random_length);
		ISSUE_MAU_COMMAND(LOAD, R_MAU_ONE, random_length);
		ISSUE_MAU_COMMAND(STORE, SLOT(primegen_qr_x), random_length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		for (i = 0; i < 6; i++) {
			ret = cmrt_pke_get_true_random(rptr, (word_length + 2) * sizeof(uint32_t));
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_mau_command_sequence(cmds_generate_u, sizeof(cmds_generate_u)/sizeof(uint32_t), random_length);
			if (ret) {
				goto err;
			}
		}

		ret = cmrt_pke_mau_command_sequence(cmds_set_x, sizeof(cmds_set_x)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}
	} else {
		ret = -EINVAL;
		goto err;
	}

	cmrt_pke_get_bit_length(aptr, word_length, &m_bit_length);
	bit_length_diff = (prime_word_length * 32) - m_bit_length;
	bit_mask = (1 << (bit_length_diff + 1)) - 1;

	srptr = pke_addr(primegen_qr_c, NULL, bits);
	do {
		do {
			ISSUE_MAU_COMMAND(SET_MAND, SLOT(primegen_qr_r), length);
			ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}

			candidate = 0;
			for (i = 0; (i < word_length) && (candidate == 0); i++) {
				ISSUE_MAU_COMMAND(LOAD, R_MAU_ZERO, length);
				ISSUE_MAU_COMMAND(STORE, SLOT(primegen_qr_c), length);
				ISSUE_MAU_COMMAND(STORE, SLOT(primegen_qr_cu), length);
				ISSUE_MAU_COMMAND(STORE, SLOT(primegen_qr_xr), length);

				ret = cmrt_pke_wait();
				if (ret) {
					goto err;
				}

				srptr[0] = rptr[i] & bit_mask;

				if (((bit_length_diff > 2) && ((srptr[0] >> (bit_length_diff - 2)) == 0)) || (srptr[0] == 0)) {
					continue;
				}

				ret = cmrt_pke_mau_command_sequence(cmds_generate_candidate, sizeof(cmds_generate_candidate)/sizeof(uint32_t), length + 1);
				if (ret) {
					goto err;
				}

#ifdef CONFIG_CMRT_FFDH
				if (flags == DH_GENERATE_P) {
					uint32_t *qinvptr = pke_addr(ffdh_parmgen_inv_q, NULL, bits);

					if (((srptr[0] & 1) ^ (qinvptr[0] & 1)) == 1) {
						if ((srptr[0] & 1) == 1) {
							ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_qr_c), length);
							ISSUE_MAU_COMMAND(INT_ADD, SLOT(primegen_qr_c), length);
						} else {
							continue;
						}
					} else {
						ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_qr_c), length);
					}

					static const uint32_t cmds_dh_prep_candidate[] = {
						SLOT_CMD(INT_SUB,       SLOT(ffdh_parmgen_inv_q)),
						SLOT_CMD(STORE,         SLOT(primegen_qr_c)),
						SLOT_CMD(STORE,         SLOT(ffdh_parmgen_dh)),
						SLOT_CMD(SET_MAND,      SLOT(primegen_qr_c)),
						SLOT_CMD(INT_MUL,       SLOT(ffdh_parmgen_q)),
						SLOT_CMD(STORE,         SLOT(primegen_qr_c + 1)),
						SLOT_CMD(LOAD,          SLOT(primegen_qr_c)),
						SLOT_CMD(INT_ADD,       R_MAU_ONE),
						SLOT_CMD(STORE,         SLOT(primegen_qr_c)),
					};

					ret = cmrt_pke_mau_command_sequence(cmds_dh_prep_candidate, sizeof(cmds_dh_prep_candidate) / sizeof(uint32_t), length);
					if (ret) {
						goto err;
					}
				}
#endif

				/* Check minimum threshold */
				min_test = 0;
#ifdef CONFIG_CMRT_FFDH
				if ((srptr[word_length - 1] > minimum[3]) ||
				    ((srptr[word_length - 1] > dh_minimum) &&
				     ((flags == DH_SETUP_REQUIRED) || (flags == DH_GENERATE_P)))) {
#else
				if (srptr[word_length - 1] > minimum[3]) {
#endif
					min_test = 1;
#ifdef CONFIG_CMRT_FFDH
				} else if ((flags == DH_SETUP_REQUIRED) || (flags == DH_GENERATE_P)) {
					min_test = 0;
#endif
				} else if ((srptr[word_length - 1] == minimum[3]) &&
					   (srptr[word_length - 2] > minimum[2])) {
					min_test = 1;
				} else if ((srptr[word_length - 1] == minimum[3]) &&
					   (srptr[word_length - 2] == minimum[2]) &&
					   (srptr[word_length - 3] > minimum[1])) {
					min_test = 1;
				} else if ((srptr[word_length - 1] == minimum[3]) &&
					   (srptr[word_length - 2] == minimum[2]) &&
					   (srptr[word_length - 3] == minimum[1]) &&
					   (srptr[word_length - 4] > minimum[0])) {
					min_test = 1;
				} else {
					min_test = 0;
				}

				/* Check minimum threshold */
				if ((min_test == 1) && (srptr[word_length] == 0)) {
					candidate = 1;
				}
			}
		} while (candidate == 0);

		ISSUE_MAU_COMMAND(LOAD, SLOT(primegen_qr_c), length);
		ISSUE_MAU_COMMAND(STORE, SLOT(slot_number), length);

		ret = cmrt_pke_is_probable_prime(pke, bits, slot_number, &prime);
		if (ret) {
			goto err;
		}

		if (prime == 0) {
			ret = cmrt_pke_get_true_random(rptr, (word_length + 2) * sizeof(uint32_t));
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_mau_command_sequence(cmds_restore_params, sizeof(cmds_restore_params)/sizeof(uint32_t), length);
			if (ret) {
				goto err;
			}

			ISSUE_MAU_COMMAND(SET_PARAMS, SLOT(primegen_qr_m), random_length);

			ret = cmrt_pke_mau_command_sequence(cmds_generate_u, sizeof(cmds_generate_u)/sizeof(uint32_t), random_length);
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_mau_command_sequence(cmds_set_x, sizeof(cmds_set_x)/sizeof(uint32_t), length);
			if (ret) {
				goto err;
			}
		}

		counter++;
	} while ((prime == 0) && (counter < 5 * bits));

	if (prime == 1) {
		ret = 0;
	} else {
		ret = -EIO;
	}
err:
	(void)cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), 2 * length);
	return ret;
}

#ifdef CONFIG_CMRT_FFDH
#ifndef CONFIG_CMRT_FIPS_140_MODE
int cmrt_pke_generate_prime(cmrt_pke_t pke,
			    uint32_t bits,
			    uint8_t slot_number,
			    uint8_t setup_needed)
{
	return ___pke_generate_prime(pke, bits, slot_number, 0, NULL, setup_needed);
}
#endif

int cmrt_pke_generate_dh_prime(cmrt_pke_t pke,
			       uint32_t pbits,
			       uint8_t pslot_number,
			       uint32_t qbits,
			       uint8_t *q,
			       uint8_t setup_needed)
{
	return ___pke_generate_prime(pke, pbits, pslot_number, qbits, q, setup_needed);
}
#endif
