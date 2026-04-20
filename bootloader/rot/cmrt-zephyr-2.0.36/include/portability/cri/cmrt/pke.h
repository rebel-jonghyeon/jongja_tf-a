/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke.h
 *
 * @brief Public APIs for the PKE driver.
 */

#ifndef CRI_PKE_H
#define CRI_PKE_H

#include <stdint.h>
#include <stddef.h>
#include <cri/cmrt/crypto/pke_common.h>

/**
 * @brief PKE Interface
 * @defgroup pke_interface PKE Interface
 * @ingroup pke_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_TINYCRYPT
#define NUM_ECC_BYTES 32u
#define NUM_ECC_WORDS 8u
#endif
#define PKERAM_SLOT_WORDS 32u


struct dpa_ecc_curve_struct;
/*!
 * Opaque ECC curve handle.  The handle refers to a constant curve description.
 */
typedef const struct dpa_ecc_curve_struct *cri_ecc_curve_t;

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_pke_t;
#else
typedef struct cmrt_pke_context *cri_pke_t;
#endif

/**
 * @brief Get elliptic curve constants for PKE operations
 *
 * @param curve Curve identifier.
 * @return Pointer to dpa_ecc_curve_struct on success or NULL on error.
 */
cri_ecc_curve_t cri_pke_get_curve(uint32_t curve);

/**
 * @brief Get elliptic curve length
 *
 * @param curve Pointer to dpa_ecc_curve_struct.
 * @return The length of the curve in bytes.
 */
uint32_t cri_pke_get_curve_length(cri_ecc_curve_t curve);

/**
 * @brief Open PKE context for subsequent operations.
 *
 * Open and reserve a PKE context. May block for a context to be available.
 *
 * @param flags Currently reserved and must be zero.
 * @return Context handle on success or NULL on error.
 */
cri_pke_t cri_pke_open(uint32_t flags);

/**
 * @brief Close PKE context, reverse of open.
 *
 * Close and free previously opened PKE context.
 *
 * @param context Pointer to the device.
 */
void cri_pke_close(cri_pke_t context);

/**
 * @brief Get PKE result.
 *
 * Get PKE result after interrupt, or wait until it finishes.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_sync(cri_pke_t context);

/**
 * @brief Flush the PKE core.
 *
 * Issues a FLUSH command to the core without releasing the context.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_flush(cri_pke_t context);

#ifdef CONFIG_CRI_FIPS_140_MODE
/**
 * @brief Start FIPS EC pairwise consistency test.
 *
 * Start FIPS ECDSA/ECDH pairwise consistency test.
 *
 * @param curve Pointer to curve.
 * @param asset_type Type of asset.
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecc_pairwise_consistency_check(cri_ecc_curve_t curve,
					   const uint32_t asset_type,
					   const uint8_t *private_key,
					   const uint8_t *pub_x,
					   const uint8_t *pub_y);
#endif

 /**
 * @brief Start ECDSA verify operation.
 *
 * Start ECDSA verify operation.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @param digest Pointer to digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cri_pke_ecdsa_verify_hash().
 */
int cri_pke_ecdsa_verify(cri_pke_t context,
			 cri_ecc_curve_t curve,
			 const void *pub_x, const void *pub_y,
			 const void *digest,
			 const void *sign_r, const void *sign_s,
			 void *rprime);

 /**
 * @brief Start ECDSA verify operation.
 *
 * Start ECDSA verify operation.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecdsa_verify_hash(cri_pke_t context,
			      cri_ecc_curve_t curve,
			      const void *pub_x, const void *pub_y,
			      const void *digest, unsigned int digest_len,
			      const void *sign_r, const void *sign_s,
			      void *rprime);

#if defined(CONFIG_CRI_FBOOT_HAS_ECDSA_FULL) || !defined(CONFIG_CRI_FBOOT)
/**
 * @brief Start ECDSA signature operation.
 *
 * Start ECDSA signature operation.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param digest Pointer to digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 * @deprecated This function is deprecated. See @cri_pke_ecdsa_sign_hash().
 */
int cri_pke_ecdsa_sign(cri_pke_t context,
		       cri_ecc_curve_t curve,
		       const void *priv_key,
		       const void *digest,
		       void *sign_r, void *sign_s);

#ifdef CONFIG_CRI_FIPS_140_MODE
/**
 * @brief Start ECDSA signature operation with
 * chosen nonce.
 *
 * Start ECDSA signature operation.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
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
int cri_pke_ecdsa_sign_extended(cri_pke_t context,
				cri_ecc_curve_t curve,
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
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param digest Pointer to digest.
 * @param digest_len Size of digest.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecdsa_sign_hash(cri_pke_t context,
			    cri_ecc_curve_t curve,
			    const void *priv_key,
			    const void *digest, unsigned int digest_len,
			    void *sign_r, void *sign_s);

/**
 * @brief Start ECDSA key generation.
 *
 * Start ECDSA key generation.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecdsa_keygen(cri_pke_t context,
			 cri_ecc_curve_t curve,
			 const void *priv_key,
			 void *pub_x, void *pub_y);
#endif

#if defined(CONFIG_CRI_FBOOT_HAS_RSA_VERIFY) || !defined(CONFIG_CRI_FBOOT)
/**
 * @brief Start RSA pub operation
 *
 * Computes an RSA public key primitive.
 * All input and output are of little endian.
 *
 * @param context Pointer to the device.
 * @param bits the bit length of the RSA modulus.
 * @param mod pointer to the modulus parameter from the public_key.
 * @param public_key pointer to the exponent parameter from the public_key.
 * @param signature the input signature or message.
 * @param message the output message or ciphertext.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_rsa_public_key_primitive(cri_pke_t context,
				     uint32_t bits,
				     const uint32_t *mod,
				     const uint32_t *public_key,
				     const uint32_t *signature,
				     uint32_t *message);
#endif

#ifndef CONFIG_CRI_FBOOT
/**
 * @brief Blind the secret key.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param key Pointer to secret key.
 * @param share1 Pointer to first share of secret key.
 * @param share2 Pointer to second share of secret key.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_blind_secret_key(cri_pke_t context,
			     cri_ecc_curve_t curve,
			     const void *key,
			     void *share1, void *share2);

/**
 * @brief Generate ECDH public key.
 *
 * Generate ECDH public key from blindened private key.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecdh_keygen(cri_pke_t context,
			cri_ecc_curve_t curve,
			const void *priv_key, void *pub_x);

/**
 * @brief Start ECDH operation.
 *
 * Start EC Diffie-Hellman key exchange operation
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param peer_key_x Pointer peer public key X.
 * @param shared_secret Pointer to shared secret.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ecdh(cri_pke_t dev,
		 cri_ecc_curve_t curve,
		 const void *priv_key,
		 const void *peer_key,
		 void *shared_secret);

/**
 * @brief Create keypair for ECDH operation on curve x25519 or x448
 *
 * Create a keypair for RFC7748 Edwards-curve Diffie-Hellman key
 * exchange.  The \a priv_key data should be randomly generated and is
 * either 32 (X25519) or 56 (X448) bytes, and interpreted as a
 * little-endian number.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key
 * @param[out] pub_x Pointer to public key X
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_rfc7748_keygen(cri_pke_t context,
			   cri_ecc_curve_t curve,
			   const void *priv_key,
			   void *pub_x);

/**
 * @brief Start ECDH operation on curve x25519.
 *
 * Start EC Diffie-Hellman.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param pub_x Pointer to public key X.
 * @param shared_secret Pointer to shared secret.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_rfc7748(cri_pke_t context,
		    cri_ecc_curve_t curve,
		    const void *priv_key, const void *pub_x,
		    void *shared_secret);

/**
 * @brief Generate EdDSA signature.
 *
 * Generate EdDSA signature.  The signature is typically the direct
 * concatenation of R || S.  The buffers must be appropriately sized
 * (32 bytes each.)
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve ed25519.
 * @param priv_key Pointer to private key.
 * @param message Pointer to message
 * @param msglen of message in bytes.
 * @param sign_r buffer to receive signature R-part.
 * @param sign_s buffer to receive signature S-part.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_eddsa_sign(cri_pke_t context,
		       cri_ecc_curve_t curve,
		       const void *priv_key,
		       const void *message, unsigned int msglen,
		       void *sign_r, void *sign_s);

/**
 * @brief EdDSA verify operation.
 *
 * Verify an EdDSA signature on an Edwards curve (Ed25519 or Ed448.)
 * A return value of -EINVAL is returned for a non-matching signature
 * (or, if any of the parameters is wrong.)
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param pub_x Pointer to public key.
 * @param message Pointer to message.
 * @param msglen Length of message in bytes.
 * @param sign_r Pointer to signature R-part.
 * @param sign_s Pointer to signature S-part.
 * @param rprime Pointer to rprime.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_eddsa_verify(cri_pke_t context,
			 cri_ecc_curve_t curve,
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
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param priv_key Pointer to private key.
 * @param[out] pub_x Pointer to buffer to receive public key data
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_eddsa_keygen(cri_pke_t context,
			 cri_ecc_curve_t curve,
			 const void *priv_key, void *pub_x);

/**
 * @brief Start ECC key validation operation.
 *
 * Check thay the public key is on the curve.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve.
 * @param pub_x Pointer to public key X.
 * @param pub_y Pointer to public key Y.
 * @return Zero on success (on curve), -ERRNO on error.
 */
int cri_pke_validate_ecc_xy_key(cri_pke_t context,
				cri_ecc_curve_t curve,
				const void *pub_x, const void *pub_y);

/**
 * @brief Start RSA priv operation
 *
 * Computes an RSA private key primitive from a split private key and the
 * public key. All input and output are of litle endian.
 *
 * @param context Pointer to the device.
 * @param bits the bit length of the RSA modulus.
 * @param mod pointer to public key modulus
 * @param public_key pointer the public key exponent, using the same amount of
 *        memory as the modulus.
 * @param priv_exp pointer to private exponent (d) in little endian
 * @param message message to be signed or ciphertext (little-endian
 * message equivalent.)
 * @param signature the output signature or message (little-endian equivalent)
 * @return Zero on success, -ERRNO on error.
 * @note this routine is asynchronous, signature buffer must be held
 * in scope, and the final result is obtained by cri_pke_sync().
 */
int cri_pke_rsa_private_key_primitive(cri_pke_t context,
				      uint32_t bits,
				      const uint32_t *mod,
				      const uint32_t *public_exp,
				      const uint32_t *priv_exp,
				      const uint32_t *message,
				      uint32_t *signature);


/*!
 * RSA (CRT) key.  Accepted key sizes depend on exact system
 * specifications, but typically accepted are 2048, 3072, and 4096.
 * The members can be optional according to routine;
 * - public keys have n and e
 * - private keys have n, and either (d, e), or (e, p, q, dp, dq, iq);
 * or, all of the elements
 */
struct cri_rsa_key {
	uint16_t bits; /**< bits in key data */
	uint16_t flags; /**< flags, keep at 0 */
	uint32_t *n; /**< public modulus, bits/8 bytes */
	uint32_t *e; /**< public exponent, bits/8 bytes */
	uint32_t *d; /**< private exponent, bits/8 bytes */
	uint32_t *p; /**< crt prime 1, bits/16 bytes */
	uint32_t *q; /**< crt prime 2, bits/16 bytes */
	uint32_t *dp; /**< crt exponent 1, bits/16 bytes */
	uint32_t *dq; /**< crt exponent 2, bits/16 bytes */
	uint32_t *iq; /**< crt coefficient, bits/16 bytes */
};


/*!
 * RSA CRT (private/signing) primitive.
 * @param context open pke device
 * @param key key to use
 * @param message (or pt) message to sign or encrypt
 * @param signature (or ct) signature buffer (or encrypted data)
 * @param scratch scratch buffer to use
 * @param scratch_size size of scratch buffer
 * @return negative on errors
 * @note this routine is asynchronous, signature buffer and scratch
 * are reserved until cri_pke_sync() returns
 */
int cri_pke_rsa_crt_primitive(cri_pke_t dev,
			      const struct cri_rsa_key *key,
			      const uint32_t *message,
			      uint32_t *signature,
			      uint32_t *scratch, size_t scratch_size);

/*!
 * RSA key generation parameters.  These arguments are used as input
 * to generate similar key pairs (the actual key data will be
 * different.)
 */
struct cri_rsa_keygen_params {
	size_t bits;	       /**< modulus size in bits */
	const uint32_t *pube; /* public exponent for key */
	size_t esize;	      /* size of pube in words */
	uint32_t *scratch;    /* required scratch space used */
	uint32_t scratch_size; /* size of scratch in bytes */
	const uint32_t *seed; /* optional seed, NULL for random */
};

/*!
 * Generate RSA keypair.  The routine generates a key pair; \a key
 * must be filled in to have pointer to the output buffers to receive
 * the key components, with sufficient size; @see cri_rsa_key for the
 * sizes.  This routine is synchronous: the buffers will have been
 * updated on return (no sync is required.)
 * @param context open pke context
 * @param params arguments to key generation
 * @param key output key, must have been correctly allocated
 * @return < 0 for failures
 */
int cri_pke_rsa_keygen(cri_pke_t dev,
		       const struct cri_rsa_keygen_params *params,
		       struct cri_rsa_key *key);

/**
 * @brief Finite Field Diffie-Hellman key exchange.
 *
 * Derive public key or shared key or both. @p pub_key and @p shared_key are
 * optional, however at least one should be non-zero. If @p shared_key is zero
 * then @p peer_key is not required. All other parameters are required.
 *
 * @param context Pointer to the device.
 * @param mod_size Size of the modulus (and other parameters) in bytes.
 * @param p Pointer to group modulus.
 * @param q Pointer to group prime order.
 * @param g Pointer to group generator.
 * @param priv_key Pointer to private key.
 * @param peer_key Pointer to peer's public key. It must be specified if
 *                 @p shared_key is to be derived.
 * @param [out] pub_key Pointer to own public key.
 * @param [out] shared_key Pointer to shared public key.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ffdh(cri_pke_t context,
		 size_t mod_size, const void *p, const void *q, const void *g,
		 const void *priv_key, const void *peer_key,
		 void *pub_key, void *shared_key);

/**
 * @brief Finite Field Diffie-Hellman private key generation.
 *
 * Generate a key in interval [1, @p q - 1].
 *
 * Size of @p priv_key should be at least equal to the size of @p q. However for
 * compatibility with @ref cri_pke_ffdh(), it must not be smaller than the size
 * of the modulus. All pointer arguments must be 32-bit aligned.
 *
 * @param mod_size Size of the modulus (and other parameters) in bytes.
 * @param q Pointer to group prime order.
 * @param [out] priv_key Pointer to private key.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pke_ffdh_keygen(cri_pke_t context,
			size_t mod_size, const void *q, void *priv_key);

/**
 * @brief Verify FFDH parameters
 *
 * Verifies that @p p and @p q are prime and g^q = 1 mod p.
 *
 * @param context Pointer to the device.
 * @param psize Size of p in bytes.
 * @param p Pointer to group modulus.
 * @param qsize Size of q in bytes.
 * @param q Pointer to group prime order.
 * @param gsize Size of g in bytes.
 * @param g Pointer to group generator.
 * @return Zero on success, -ERRNO on error.
 */
int
cri_pke_ffdh_verify(cri_pke_t context,
		    size_t psize,
		    const uint32_t *p,
		    size_t qsize,
		    const uint32_t *q,
		    size_t gsize,
		    const uint32_t *g);

/**
 * @brief Generate FFDH parameters
 *
 * Generates DH group parameters of the given size.  May take a long
 * time for large sizes.
 *
 * @param context Pointer to the device.
 * @param pbits Size of p in bits.
 * @param qbits Size of q in bits.
 * @param [out] presult Pointer to group modulus.
 * @param [out] qresult Pointer to group prime order.
 * @param [out] gresult Pointer to group generator.
 * @return Zero on success, -ERRNO on error.
 */
int
cri_pke_ffdh_parmgen(cri_pke_t context,
		     size_t pbits,
		     size_t qbits,
		     uint32_t *presult,
		     uint32_t *qresult,
		     uint32_t *gresult);

#endif /* CONFIG_CRI_FBOOT */

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
