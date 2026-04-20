/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_API_H
#define FBOOT_API_H

/*
 * Fboot API for machine mode development (sboot, tboot, perso).
 */

#include <zephyr.h>
#include <device.h>
#include <sys/util.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sac.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/ktc.h>
#ifdef CONFIG_CMRT_PKE
#include <drivers/cmrt/pke.h>
#endif
#ifdef CONFIG_CMRT_ENCRYPTED_IMAGE_SUPPORT
#include <drivers/cmrt/aes.h>
#endif
#ifdef CONFIG_CMRT_PMU
#include <drivers/cmrt/pmu.h>
#endif
#include <drivers/cmrt/fmc.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/cc.h>
#include <drivers/cmrt/util.h>

#include <stdalign.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmrt/fboot/fboot_config.h>
#include <cmrt/fboot/img_format.h>

/**
 * @brief Halt the CPU.
 *
 * Set error register and print debug message to the console.
 *
 * @param major Major error code.
 * @param minor Minor error code.
 * @param fmt Format string.
 *
 * @ingroup FBOOT_API
 */
#define halt(major, minor, fmt, ...) do { LOG_ERR(fmt, ##__VA_ARGS__); cmrt_eac_halt(CORE_ID_CPU, major, minor); } while (0)

/**
 * @brief Word aligned, timing constant, secure memory compare.
 *
 * Can use the Canary Core for glitch protection.
 * Will return a mismatch if pointers or size are not word aligned.
 *
 * @param cc Canary Core context or null if not used.
 * @param s1 Word array to compare.
 * @param s2 Word array to compare.
 * @param n Number of bytes to compare.
 * @return True for matching arrays, false otherwise.
 *
 * @ingroup FBOOT_API
 */
bool fboot_memmatch(cmrt_cc_t cc, const void *s1, const void *s2, size_t n);

/**
 * @brief Generic function to calculate any supported digest.
 *
 * Will close the Hash Core context given as parameter or created internally.
 * Everything needs to be word aligned.
 *
 * @param hc Hash Core context or null to create one internally.
 * @param algo Hash algorithm, see hc.h for values.
 * @param data Data to hash.
 * @param size Size of data.
 * @param digest Buffer for returned digest, length depends on algorithm.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_hash(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *data, size_t size, void *digest);

/**
 * @brief Generic function to calculate digest on two data areas.
 *
 * Will close the Hash Core context given as parameter or created internally.
 * Everything needs to be word aligned.
 *
 * @param hc Hash Core context or null to create one internally.
 * @param algo Hash algorithm, see hc.h for values.
 * @param data1 First data to hash.
 * @param size1 Size of the first data.
 * @param data2 Second data to hash.
 * @param size2 Size of the second data.
 * @param digest Buffer for returned digest, length depends on algorithm.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_hash2(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *data1, size_t size1, const void *data2, size_t size2, void *digest);

/**
 * @brief Calculate digest for image and footer.
 *
 * Calculate requested algo hash for image and footer.
 * Everything needs to be word aligned.
 *
 * @param hc Hash Core context or null to create one internally.
 * @param algo Hash algorithm, see hc.h for values.
 * @param blob Start of image blob.
 * @param size Size of the image blob.
 * @param footer Start of image footer.
 * @param digest Buffer for returned digest, length depends on algorithm.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int img_digest(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *blob, size_t size, const cmrt_img_footer_t *footer, void *digest);

/**
 * @brief Verify ECDSA signed image.
 *
 * Verify an ECDSA-P256 signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param blob Pointer to image blob.
 * @param size Size of image blob.
 * @param pkhash Hash digest for verifying image.
 * @param footer Pointer to image footer.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_sig(cmrt_cc_t cc, const void *blob, size_t size, const void *pkhash, const cmrt_img_footer_t *footer);

/**
 * @brief Verify HMAC signed image.
 *
 * Verify an HMAC-SHA256 signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param blob Pointer to image blob.
 * @param size Size of image blob.
 * @param pkhash Hash digest for verifying image.
 * @param footer Pointer to image footer.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_hmac(cmrt_cc_t cc, const void *blob, size_t size, const void *pkhash, const cmrt_img_footer_t *footer);

/**
 * @brief Verify RSA signed image.
 *
 * Verify an RSA signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param pklen Modulus + exponent in bytes.
 * @param pub Public RSA key (modulus + exponent).
 * @param digest SHA3-512 digest of loaded image.
 * @param signature Image signature from footer.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_rsa(cmrt_cc_t cc, uint32_t pklen, uint32_t *pub, const uint32_t *digest, uint32_t *signature);

/**
 * @brief Verify LMS signed image.
 *
 * Verify an LMS signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param pk Public key, contains type, otstype, I, root_hash.
 * @param digest Digest of loaded image.
 * @param dlen Digest length of loaded image.
 * @param signature Image signature from footer.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_lms(cmrt_cc_t cc, const uint8_t *pk, const uint8_t *digest, size_t dlen, const uint8_t *signature);

/**
 * @brief Verify LMS-HSS signed image.
 *
 * Verify an LMS-HSS signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param pk Public key, contains type, otstype, I, root_hash.
 * @param digest Digest of loaded image.
 * @param dlen Digest length of loaded image.
 * @param signature Image signature from footer.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_lms_hss(cmrt_cc_t cc, const uint8_t *pk, const uint8_t *digest, size_t dlen, const uint8_t *signature);

/**
 * @brief Verify XMSS or XMSS^MT signed image.
 *
 * Verify an XMSS or XMSS^MT signed boot stage image.
 *
 * @param cc Device context to Canary core.
 * @param blob Pointer to image blob.
 * @param bsize Size of image blob.
 * @param footer Pointer to image footer.
 * @param digest Buffer for digest of loaded image and footer.
 *               Digest is calculated using algorithm given
 *               by XMSS or XMSS^MT mode from footer, max size 64B.
 * @param dsize Digest buffer size.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_xmss(cmrt_cc_t cc, const void *blob, size_t bsize, const cmrt_img_footer_t *footer, uint32_t *digest, size_t dsize);

/**
 * @brief Verify CID.
 *
 * Verify a container id (CID) from image footer.
 *
 * @param cc Device context to Canary core.
 * @param footer Pointer to image footer.
 * @param pkhash Hash digest for verifying image.
 * @return Zero on success or -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_verify_cid(cmrt_cc_t cc, const cmrt_img_footer_t *footer, const void *pkhash);

/**
 * @brief Set test and debug vector.
 *
 * Test and debug vector is customer specific.
 *
 * @param tdv Array of TDV words.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_set_tdv(const uint32_t tdv[CMRT_FMC_TDV_SIZE]);

/**
 * @brief Set KDC hardware state.
 *
 * KDC hardware state is a machine mode write only register.
 * Bits set cannot be unset. Its value affects key derivations.
 *
 * @param value Value to set.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_kdc_set_hw_state(uint8_t value);

/**
 * @brief Initialize supervisor loading.
 *
 * @return Load address of supervisor image.
 *
 * @ingroup FBOOT_API
 */
uint32_t fboot_supervisor_clear(void);

/**
 * @brief Start optional tboot.
 *
 * Starts tboot is it was first in the supervisor image bundle.
 * Will return back to caller (sboot) for loading the supervisor next.
 *
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_tboot_start(void);

/**
 * @brief Make final setup and start supervisor.
 *
 * Configure supervisor environment and start running it. If supervisor is
 * non-silo then the HW security context is cleared, and the first loaded
 * user container sets the root and permissions.
 *
 * If supervisor is a monolithic application then its HW security
 * context will be set according to the footer and respective root.
 *
 * @return No return on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_supervisor_start(void);

/**
 * @brief Return boot bypass vector.
 *
 * @param state CMRT lifecycle state.
 * @return Return boot bypass vector or NULL if it is not set.
 *
 * @ingroup FBOOT_API
 */
void *fboot_bootbypass_vector(uint32_t state);

/**
 * @brief Set fboot permissions (= all permissions).
 *
 * Any error will lead to CMRT halt. Permissions must be cleared
 * by calling cmrt_clear_container_context() before calling this function.
 *
 * @param id Root id for setting the derive path, or NULL to leave it unset.
 * @param init True to initialize security monitor.
 * @return Return OMC driver handle.
 *
 * @ingroup FBOOT_API
 */
cmrt_omc_t fboot_permissions(const cmrt_omc_root_id_t *id, bool init);

#endif
