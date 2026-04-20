/*
 * Copyright (c) 2017-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke.h
 *
 * @brief Public APIs for the PKE driver.
 */

#ifndef CMRT_PKE_H
#define CMRT_PKE_H

#include <stdint.h>
#include <stddef.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/crypto/pke_common.h>
#else
#include "pke_common.h"
#endif

#include "pke_memcpy.h"

/**
 * @brief PKE Interface
 * @defgroup pke_interface PKE Interface
 * @ingroup pke_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_pke_context *cmrt_pke_t;

#ifndef CRI_PKE_STANDALONE
#ifndef CONFIG_TINYCRYPT
#define NUM_ECC_BYTES 32u
#define NUM_ECC_WORDS 8u
#endif
#define PKERAM_SLOT_WORDS 32u
#endif

struct dpa_ecc_curve_struct;
/*!
 * Opaque ECC curve handle.  The handle refers to a constant curve
 * description.  The curve can be retrieved by a call to
 * cmrt_get_curve() by numeric id.
 */
typedef const struct dpa_ecc_curve_struct *cmrt_ecc_curve_t;

/* Max EC curve length in words */
enum { MAX_EC_CURVE_LENGTH_W = 17UL };

/**
 * @brief Get elliptic curve constants for PKE operations
 *
 * @note synchronous function, do not call cmrt_pke_sync()
 * @param curve Curve identifier.
 * @return Curve handle on success or NULL on error.
 */
__syscall cmrt_ecc_curve_t cmrt_pke_get_curve(uint32_t curve);

/**
 * @brief Get elliptic curve length
 *
 * @note synchronous function, do not call cmrt_pke_sync()
 * @param curve Curve handle.
 * @return The length of the curve in bytes.
 */
__syscall uint32_t cmrt_pke_get_curve_length(cmrt_ecc_curve_t curve);

#ifndef CRI_PKE_STANDALONE
/**
 * @brief Open PKE context for subsequent operations.
 *
 * Open and reserve a PKE context. May block for a context to be
 * available forever and will not prevent deadlock (having allocated
 * the context itself).  The flag #CMRT_O_SYNC will affect most
 * PKE API calls made with the context returned by this call
 * - APIs return synchronously, if \a flags specifies #CMRT_O_SYNC
 * (the bit is set)
 * - cmrt_pke_sync() must be called to retrieve the result of the API
 * call if the bit is clear, if and only if the preceding API call was
 * successful (did not return an error).
 *
 * The synchronous API mechanism is a lot easier to use, and will
 * never be less efficient than calling the asynchronous API and
 * immediately synchronizing on return.  The overhead of the separate
 * sync call (a system call for user space) in code space, and
 * possibly small latency (it is a system call) are saved.
 *
 * The asynchronous API can leverage parallel operations either on the
 * CPU, SIC, or other cores, when PKE operations are being processed
 * in the background.  Note however:
 * - operations not taking a PKE handle are always synchronous, and
 * generally short (cmrt_pke_get_curve() and
 * cmrt_pke_get_curve_length())
 * - some (very long) operations are mostly (99%) synchronous
 *
 * These APIs are marked in their descriptions.  The latter APIs can
 * only be called taking extra precautions with the watchdog, as they
 * will generally exceed any watchdog timeouts as well
 * (cmrt_pke_rsa_key_gen(), cmrt_pke_ffdh_parmgen()).
 *
 * @param flags flags to open
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_pke_t cmrt_pke_open(uint32_t flags);
#else
/**
 * @brief Open PKE context for subsequent operations.
 *
 * Open and reserve a PKE context. May block for a context to be available.
 *
 * @param context Address of a PKE context.
 * @return Context handle on success or NULL on error.
 */
cmrt_pke_t cmrt_pke_open(cmrt_pke_t context);
#endif

/**
 * @brief Close PKE context, reverse of open.
 *
 * Close and free previously opened PKE context.
 *
 * @param context handle returned by cmrt_pke_open()
 */
__syscall void cmrt_pke_close(cmrt_pke_t context);

/**
 * @brief Get PKE result of asynchronous operation.
 *
 * Wait for PKE operation to finish, and retrieve the result.
 *
 * @note the behavior if no call preceding it is undefined.  Typically
 * the call will block forever.
 * @param context handle returned by cmrt_pke_open()
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_sync(cmrt_pke_t context);

/**
 * @brief Get PKE result.
 *
 * Get PKE result after polling, or wait until it finishes.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_wait(void);

/**
 * @brief Flush the PKE core.
 *
 * Issues a FLUSH command to the core without releasing the context.
 *
 * @param context handle returned by cmrt_pke_open()
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_flush(cmrt_pke_t context);

#ifdef CONFIG_CMRT_FIPS_140_MODE
/**
 * @brief Start FIPS EC pairwise consistency test.
 *
 * Start FIPS ECDSA/ECDH pairwise consistency test.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_pairwise_consistency_check(cmrt_pke_t context,
					    cmrt_ecc_curve_t curve,
					    const uint8_t *priv_key,
					    const uint8_t *pub_x,
					    const uint8_t *pub_y);

/**
 * @brief Start FIPS EC SP800-56Ar3 public key validation test.
 *
 * Start FIPS EC SP800-56Ar3 public key validation test.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param curve Pointer to curve.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_sp800_public_key_validation(cmrt_pke_t context,
				     cmrt_ecc_curve_t curve,
				     uint8_t *pub_x,
				     uint8_t *pub_y);
#endif

#ifndef CRI_PKE_STANDALONE
/**
 * @brief Start ECDSA verify operation.
 *
 * Start ECDSA verify operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @param digest Pointer to digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cmrt_pke_ecdsa_verify_hash().
 */
__syscall int cmrt_pke_ecdsa_verify(cmrt_pke_t context,
				    cmrt_ecc_curve_t curve,
				    const void *pub_x, const void *pub_y,
				    const void *digest,
				    const void *sign_r, const void *sign_s,
				    void *rprime);
#endif

/**
 * @brief Start ECDSA verify operation.
 *
 * Start ECDSA verify operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ecdsa_verify_hash(cmrt_pke_t context,
					 cmrt_ecc_curve_t curve,
					 const void *pub_x, const void *pub_y,
					 const void *digest, unsigned int digest_len,
					 const void *sign_r, const void *sign_s,
					 void *rprime);

#if defined(CONFIG_CMRT_FBOOT_HAS_ECDSA_FULL) || !defined(CONFIG_CMRT_FBOOT)
#ifndef CRI_PKE_STANDALONE
/**
 * @brief Start ECDSA signature operation.
 *
 * Start ECDSA signature operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param digest Pointer to digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cmrt_pke_ecdsa_sign_hash().
 */
__syscall int cmrt_pke_ecdsa_sign(cmrt_pke_t context,
				  cmrt_ecc_curve_t curve,
				  const void *priv_key,
				  const void *digest,
				  void *sign_r, void *sign_s);
#endif

#ifdef CONFIG_CMRT_FIPS_140_MODE
/**
 * @brief Start ECDSA signature operation with
 * chosen nonce.
 *
 * Start ECDSA signature operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key_share0 Pointer to private key0.
 * @param priv_key_share1 Pointer to private key1,
 * can be NULL.
 * @param nonce  Pointer to nonce (double length)
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecdsa_sign_extended(cmrt_pke_t context,
				 cmrt_ecc_curve_t curve,
				 const void *priv_key_share0,
				 const void *priv_key_share1,
				 const void *nonce,
				 const void *digest,
				 const uint32_t digest_len,
				 void *sign_r,
				 void *sign_s);
#endif

/**
 * @brief Start ECDSA signature operation.
 *
 * Start ECDSA signature operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ecdsa_sign_hash(cmrt_pke_t context,
				       cmrt_ecc_curve_t curve,
				       const void *priv_key,
				       const void *digest, unsigned int digest_len,
				       void *sign_r, void *sign_s);

/**
 * @brief Start ECDSA signature operation.
 *
 * Start ECDSA signature operation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param nonce Pointer to nonce (can be NULL). Note: this is expected to point
 *             to an initialized location twice the length of the other parameters.
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecdsa_sign_extended(cmrt_pke_t context,
				 cmrt_ecc_curve_t curve,
				 const void *priv_key_share1,
				 const void *priv_key_share2,
				 const void *nonce,
				 const void *digest,
				 const uint32_t digest_len,
				 void *sign_r,
				 void *sign_s);

/**
 * @brief Start ECDSA key generation.
 *
 * Start ECDSA key generation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve handle returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ecdsa_keygen(cmrt_pke_t context,
				    cmrt_ecc_curve_t curve,
				    const void *priv_key,
				    void *pub_x, void *pub_y);

/**
 * @brief Start ECDSA key generation.
 *
 * Start ECDSA key generation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecdsa_keygen_extended(cmrt_pke_t context,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x,
				   void *pub_y);

/**
 * @brief Start EC private key generation.
 *
 * Start EC private key generation.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_private_keygen(cmrt_pke_t context,
				cmrt_ecc_curve_t curve,
				void *priv_key);

/**
 * @brief Generate EC public key.
 *
 * Generate EC public key from private key, returns
 * the x-coordinate only.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_x_keygen(cmrt_pke_t context,
			  cmrt_ecc_curve_t curve,
			  const void *priv_key,
			  void *pub_x);

/**
 * @brief Generate EC public key.
 *
 * Generate EC public key from a blinded private key,
 * returns the x-coordinate only.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param pub_x Pointer to public key X.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_x_keygen_extended(cmrt_pke_t context,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x);

/**
 * @brief Generate EC public key.
 *
 * Generate EC public key from a private key,
 * returns the x,y coordinates.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_xy_keygen(cmrt_pke_t context,
			   cmrt_ecc_curve_t curve,
			   const void *priv_key,
			   void *pub_x, void *pub_y);

/**
 * @brief Generate EC public key.
 *
 * Generate EC public key from a blinded private key,
 * returns the x,y coordinates.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecc_xy_keygen_extended(cmrt_pke_t context,
				    cmrt_ecc_curve_t curve,
				    const void *priv_key_share1,
				    const void *priv_key_share2,
				    void *pub_x, void *pub_y);
#endif

#if defined(CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY) || !defined(CONFIG_CMRT_FBOOT)
/**
 * @brief Start RSA pub operation
 *
 * Computes an RSA public key primitive.
 * All input and output are of little endian.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param bits the bit length of the RSA modulus.
 * @param mod pointer to the modulus parameter from the public_key.
 * @param public_key pointer to the exponent parameter from the public_key.
 * @param signature the input signature or message.
 * @param message the output message or ciphertext.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_rsa_public_key_primitive(cmrt_pke_t context,
						uint32_t bits,
						const uint8_t *mod,
						const uint8_t *public_key,
						const uint8_t *signature,
						uint8_t *message);
#endif

/**
 * @brief Blind the private key.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param key Pointer to secret key.
 * @param share1 Pointer to first share of private key.
 * @param share2 Pointer to second share of private key.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_blind_private_key(cmrt_pke_t context,
			       cmrt_ecc_curve_t curve,
			       const void *key,
			       void *share1,
			       void *share2);

#if defined(CONFIG_CMRT_FIPS_140_MODE) || !defined(CONFIG_CMRT_FBOOT)
/**
 * @brief Start ECDH operation.
 *
 * Start EC Diffie-Hellman key exchange operation
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param peer_key Pointer peer public key x-coordinate.
 * @param shared_secret Pointer to shared secret.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ecdh(cmrt_pke_t context,
			    cmrt_ecc_curve_t curve,
			    const void *priv_key,
			    const void *peer_key,
			    void *shared_secret);
#endif

/**
 * @brief Generate ECDH public key.
 *
 * Generate ECDH public key from a private key.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ecdh_keygen(cmrt_pke_t context,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key, void *pub_x);

/**
 * @brief Generate ECDH public key.
 *
 * Generate ECDH public key from blinded private key.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param pub_x Pointer to public key X.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecdh_keygen_extended(cmrt_pke_t context,
				  cmrt_ecc_curve_t curve,
				  const void *priv_key_share1,
				  const void *priv_key_share2,
				  void *pub_x);

/**
 * @brief Start ECDH operation.
 *
 * Start EC Diffie-Hellman key exchange operation
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param peer_key_x Pointer peer public key X.
 * @param shared_secret Pointer to shared secret.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_ecdh_extended(cmrt_pke_t context,
			   cmrt_ecc_curve_t curve,
			   const void *priv_key_share1,
			   const void *priv_key_share2,
			   const void *peer_key_x,
			   void *shared_secret);

#ifndef CRI_PKE_STANDALONE
/**
 * @brief Create keypair for ECDH operation on curve x25519 or x448
 *
 * Create a keypair for RFC7748 Edwards-curve Diffie-Hellman key
 * exchange.  The \a priv_key data should be randomly generated and is
 * either 32 (X25519) or 56 (X448) bytes, and interpreted as a
 * little-endian number.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key
 * @param[out] pub_x Pointer to public key X
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cmrt_pke_ecdh_keygen().
 */
__syscall int cmrt_pke_rfc7748_keygen(cmrt_pke_t context,
				      cmrt_ecc_curve_t curve,
				      const void *priv_key,
				      void *pub_x);

/**
 * @brief Start ECDH operation on curve x25519.
 *
 * Start EC Diffie-Hellman.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param shared_secret Pointer to shared secret.
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cmrt_pke_ecdh().
 */
__syscall int cmrt_pke_rfc7748(cmrt_pke_t context,
			       cmrt_ecc_curve_t curve,
			       const void *priv_key, const void *pub_x,
			       void *shared_secret);

/**
 * @brief Generate EdDSA signature.
 *
 * Generate EdDSA signature.  The signature is typically the direct
 * concatenation of R || S.  The buffers must be appropriately sized
 * (32 bytes each.)
 *
 * \a curve must be of the appropriate type for the operation (Ed25519
 * or Ed448).
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param message Pointer to message
 * @param msglen of message in bytes.
 * @param sign_r buffer to receive signature R-part.
 * @param sign_s buffer to receive signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_eddsa_sign(cmrt_pke_t context,
				  cmrt_ecc_curve_t curve,
				  const void *priv_key,
				  const void *message, unsigned int msglen,
				  void *sign_r, void *sign_s);
#endif


/**
 * @brief EdDSA verify operation.
 *
 * Verify an EdDSA signature on an Edwards curve (Ed25519 or Ed448).
 * A return value of -EINVAL is returned for a non-matching signature
 * (or, if any of the parameters is wrong.)
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to public key.
 * @param message Pointer to message.
 * @param msglen Length of message in bytes.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_eddsa_verify(cmrt_pke_t context,
				    cmrt_ecc_curve_t curve,
				    const void *pub_x,
				    const void *message, unsigned int msglen,
				    const void *sign_r, const void *sign_s,
				    void *rprime);

/**
 * @brief Generate EdDSA key pair.
 *
 * Generate an Edwards-curve key pair (Ed25519 or Ed448.)  The private
 * key part is passed in, and the public key returned.  Buffers must
 * be 32 bytes (Ed25519) or 57 bytes in length (Ed448.)
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param[out] pub_y Pointer to buffer to receive public key data
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_eddsa_keygen(cmrt_pke_t context,
				    cmrt_ecc_curve_t curve,
				    const void *priv_key, void *pub_y);

/**
 * @brief Generate EdDSA key pair.
 *
 * Generate an Edwards-curve key pair (Ed25519 or Ed448.)  The private
 * key part is passed in, and the public key returned.  Buffers must
 * be 32 bytes (Ed25519) or 57 bytes in length (Ed448.)
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key_share1 Pointer to private key share.
 * @param priv_key_share2 Pointer to private key share (can be NULL).
 * @param[out] pub_y Pointer to buffer to receive public key data
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_eddsa_keygen_extended(cmrt_pke_t context,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_y);

/**
 * @brief Start ECC key validation operation.
 *
 * Check thay the public key is on the curve.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success (on curve), -ERRNO on error.
 */
__syscall int cmrt_pke_validate_ecc_xy_key(cmrt_pke_t context,
					   cmrt_ecc_curve_t curve,
					   const void *pub_x, const void *pub_y);

/**
 * @brief Start ECC key validation operation.
 *
 * Check thay the public key is on the curve.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to public key X.
 * @return Zero on success (on curve), -ERRNO on error.
 */
int cmrt_pke_validate_ecc_x_key(cmrt_pke_t context,
				cmrt_ecc_curve_t curve,
				const void *pub_x);

/**
 * @brief Start ECC decompress.
 *
 * Generate the y-coordinate of an elliptic curve
 * point from the x-coordinate. Note that the result is from
 * a square-root operation and will, therefore, be y or (p-y).
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param pub_x Pointer to X coordinate.
 * @param pub_y Pointer to Y coordinate.
 * @param sy    Sign of point Y. 0 for positive, 1 for negative.
 * @return Zero on success (on curve), -ERRNO on error.
 */
int cmrt_pke_ecc_decompress(cmrt_pke_t context,
			    cmrt_ecc_curve_t curve,
			    const void *pub_x,
			    void *pub_y,
			    int sy);

/**
 * RSA key. Apply to CRT as well.
 */
struct cmrt_rsa_key {
	uint32_t bits;          /**< bit length of the modulus */
	uint16_t flags;         /**< flags, keep at 0 */
	uint8_t *n;             /**< public key modulus */
	uint8_t *e;             /**< public key exponent */
	uint32_t elength;       /**< byte length of e */
	uint8_t *d;             /**< private exponent, if required */

	uint8_t *p;             /**< private key (CRT) prime */
	uint8_t *q;             /**< private key (CRT) prime */
	uint8_t *dp;            /**< private key dp = d mod p-1 */
	uint8_t *dq;            /**< private key dq = d mod q-1 */
	uint8_t *iq;            /**< private key iq = q^-1 mod p */

	uint8_t *mask;          /**< mask used to blind key */
};
typedef struct cmrt_rsa_key *cmrt_rsa_key_t;

/**
 * @brief RSA context pointers, including key, signature,
 * message, and supportive fields.
 */
struct cmrt_rsa_ctx {
	struct cmrt_rsa_key key;
	uint8_t *signature;     /**< signature */
	uint8_t *message;       /**< message */
};
typedef struct cmrt_rsa_ctx *cmrt_rsa_ctx_t;

/**
 * @brief RSA sign primitive
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 * n - public key modulus
 * e - public key exponent
 * d1 - private key
 * message - the message to be signed
 *
 * These fields of ctx must be valid pointer:
 * d2 - optional second share, may be NULL
 * signature - keep it empty: where the result is
 *
 * @param context The PKE device
 * @param ctx The RSA context
 * @return Zero on success (on curve), -ERRNO on error.
 */
__syscall int cmrt_pke_rsa_sign(cmrt_pke_t context, struct cmrt_rsa_ctx *ctx);

/**
 * @brief RSA pub primitive
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 * n - public key modulus
 * e - public key exponent
 * signature - the signature
 *
 * These fields of ctx must be valid pointer:
 * message - where the result is
 *
 * @param context The PKE device
 * @param ctx The RSA context
 * @return Zero on success (on curve), -ERRNO on error.
 */
int cmrt_pke_rsa_pub(cmrt_pke_t context, struct cmrt_rsa_ctx *ctx);

/**
 * @brief RSA keygen primitive
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 *
 * These fields of ctx must be valid pointer:
 * d1, e, n - where the result is
 * Note that NULL pointers will not raise an exception because
 * you may request a partial key (see documentation).
 *
 * @param context The PKE device
 * @param key The RSA key
 * @return Zero on success (on curve), -ERRNO on error.
 * @note this operation may take a very long time during the initial
 * call with only a very short time in the end allowing asynchronous
 * processing
 */
__syscall int cmrt_pke_rsa_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key);


#ifdef CONFIG_CMRT_RSA_CRT
/**
 * @brief RSA keygen primitive with CRT
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 *
 * These fields of ctx may be valid pointers:
 * e, n, d, p, q, dp, dq, iq.
 * Note that NULL pointers will not raise an exception because
 * you may request a partial key (see documentation).
 *
 * @param context The PKE device
 * @param[out] key RSA key buffer filled by call
 * @return Zero on success (on curve), -ERRNO on error.
 */
__syscall int cmrt_pke_rsa_crt_key_gen(cmrt_pke_t context, struct cmrt_rsa_key *key);

/**
 * @brief Blind an RSA CRT private key.
 *
 * Blinds an RSA CRT private key. If the key is unblinded the mask
 * should be set to one.
 *
 * @param context The PKE device
 * @param key The RSA CRT key
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pke_blind_rsa_crt_key(cmrt_pke_t context, struct cmrt_rsa_key *key);

/**
 * @brief RSA sign primitive with CRT
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 * n - public key modulus
 * e - public key exponent
 * message - the message to be signed
 * p, q, dp, dq, iq, mask
 *
 * These fields of ctx must be valid pointer:
 * signature - keep it empty: where the result is
 *
 * Note that iq is not required for the DPA resistant version
 * of this function.
 *
 * @param context The PKE device
 * @param ctx The RSA context
 * @return Zero on success (on curve), -ERRNO on error.
 */
__syscall int cmrt_pke_rsa_crt_sign(cmrt_pke_t context, struct cmrt_rsa_ctx *ctx);

/**
 * @brief RSA pub primitive with CRT
 *
 * These fields of ctx must be initialized with proper value:
 * bits - size of key in bit
 * n - public key modulus
 * e - public key exponent
 * signature - the signature
 *
 * These fields of ctx must be valid pointer:
 * message - where the result is
 *
 * @param context The PKE device
 * @param ctx The RSA context
 * @retval Zero on success (on curve), -ERRNO on error.
 */
int cmrt_pke_rsa_crt_pub(cmrt_pke_t context, struct cmrt_rsa_ctx *ctx);

#endif /* RSA-CRT */

/**
 * @brief FFDH parameter.
 * These parameters can be shared by multiple key agreement keys and
 * are descibed in RFC 2549.
 * - \a p identifies the prime defining the Galois field
 * - \a g specifies the generator of the multiplicative subgroup
 * - \a q specifies the prime factor of $p-1$
 *
 * All pointers must be 32-bit aligned.
 */
struct cmrt_ffdh_param {
	uint32_t mod_size;      /**< modulus size in bytes */
	uint32_t mod_bits;      /**< modulus size in bits */
	uint8_t *p;             /**< prime (modulus) */
	uint32_t grp_bits;      /**< group size in bits */
	uint32_t grp_size;      /**< group size in bytes */
	uint8_t *q;             /**< factor of p-1 sub-prime (group) */
	uint32_t gen_size;      /**< generator size in bytes */
	uint8_t *g;             /**< pointer to base (generator) */
};

typedef struct cmrt_ffdh_param *cmrt_ffdh_param_t;

/**
 * @brief Finite Field Diffie-Hellman key exchange.
 *
 * Derive public key or shared key. @p pub_key and @p shared_key are
 * optional, however at least one must be present. If @p shared_key is null
 * then @p peer_key is not required. All other parameters are required.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param curve curve returned by cmrt_pke_get_curve()
 * @param priv_key Pointer to private key.
 * @param peer_key Pointer to peer's public key. It must be specified if
 *                 @p shared_key is to be derived.
 * @param [out] pub_key Pointer to own public key.
 * @param [out] shared_key Pointer to shared public key.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ffdh(cmrt_pke_t pke, const struct cmrt_ffdh_param *param,
			    const uint8_t *priv_key, const uint8_t *peer_key,
			    uint8_t *pub_key, uint8_t *shared_key);

/**
 * @brief Finite Field Diffie-Hellman private key generation.
 *
 * Generate a key in interval [1, @p q - 1].
 *
 * Size of @p priv_key should be at least equal to the size of @p
 * q. However for compatibility with @ref cmrt_pke_ffdh(), it must not
 * be smaller than the size of the modulus.  All pointer arguments
 * must be 32-bit aligned.
 *
 * @note this operation may take a very long time during the initial
 * call with only a very short time in the end allowing asynchronous
 * processing
 *
 * @param context handle returned by cmrt_pke_open()
 * @param mod_size Size of the modulus (and other parameters) in bytes.
 * @param q Pointer to group prime order.
 * @param [out] priv_key Pointer to private key.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ffdh_private_keygen(cmrt_pke_t pke,
					   size_t mod_size,
					   const uint8_t *q,
					   uint8_t *priv_key);

/**
 * @brief Verify FFDH parameters
 *
 * Verifies that @p p and @p q are prime and g^q = 1 mod p.
 *
 * @param context handle returned by cmrt_pke_open()
 * @param param group parameters to verify
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ffdh_verify(cmrt_pke_t pke, const struct cmrt_ffdh_param *param);

/**
 * @brief Generate FFDH parameters
 *
 * Generates DH group parameters of the given size.  May take a long
 * time for large sizes.
 *
 * @note this operation may take a very long time during the initial
 * call with only a very short time in the end allowing asynchronous
 * processing
 *
 * @param context handle returned by cmrt_pke_open()
 * @param pbits Size of p in bits.
 * @param qbits Size of q in bits.
 * @param [out] param Pointer to the FFDH parameter.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_pke_ffdh_parmgen(cmrt_pke_t pke,
				    size_t pbits,
				    size_t qbits,
				    struct cmrt_ffdh_param *param);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#include <syscalls/pke.h>

#endif
