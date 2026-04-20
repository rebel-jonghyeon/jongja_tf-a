/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <string.h>
#include <cmrt/caliptra/x509.h>
#include <cmrt/ucu/span.h>
#include <cmrt/ucu/asn1.h>
#include "internal.h"

/* Cutoff points for DER-encoded lengths: 1..127 is encoded as 1 byte,
 * 128..255 as 2 bytes, 256..65535 is 3 bytes. Used in
 * asn1_writer_open() calls as the length hint instead of estimating
 * precise lengths.
 */
enum {
	asn1_len_small = 1, /* less than 128 bytes */
	asn1_len_medium = 128, /* between 128..255 bytes */
	asn1_len_large = 256,  /* larger than 255 bytes */
};

/* NOTE: for readability, in this file always open a block after
 * asn1_writer_open() and close before its corresponding
 * asn1_writer_close().
 */

/* Write a small integer with the given tag (normally ASN1_INTEGER,
 * but can be different for implicit tags.
 */
static asn1e asn1_write_smallint(asn1_writer *w, int8_t n, asn1id tag)
{
	return asn1_write(w, tag, SPAN(n), 0);
}

/* Write a long nonnegative integer. Input is in big-endian form. */
static asn1e asn1_write_longint(asn1_writer *w, span longint)
{
	/* Remove leading zero bytes from the value as it would not
	 * result in the shortest possible encoding and is therefore
	 * invalid DER.
	 */
	size_t i;
	for (i = 0; i < longint.n; ++i) {
		if (longint.p[i] != 0) {
			break;
		}
	}
	longint = span_slice(longint, i, longint.n);

	/* If the MSB is set we must add a 0x00 prefix to have it
	 * interpreted as a positive value.
	 *
	 * If we don't find any nonzero bytes (longint.n == 0), it
	 * means the value is zero, which is encoded as a single 0x00
	 * octet. This is also handled via the prefix mechanism.
	 */
	uint32_t prefix = 0x100;
	if ((longint.n > 0) && (longint.p[0] < 128)) {
		prefix = 0x00;
	}
	return asn1_write(w, ASN1_INTEGER, longint, prefix);
}

static asn1e asn1_write_bool(asn1_writer *w, bool cond)
{
	uint8_t v = cond ? 0xffu : 0x00u;
	return asn1_write(w, ASN1_BOOLEAN, SPAN(v), 0);
}

static span cmrt_caliptra_id_name(cmrt_caliptra_id_t id)
{
	switch (id) {
	case CMRT_CALIPTRA_ID_IDevID: return STRSPAN("IDevID");
	case CMRT_CALIPTRA_ID_LDevID: return STRSPAN("LDevID");
	case CMRT_CALIPTRA_ID_AliasFMC: return STRSPAN("AliasFMC");
	case CMRT_CALIPTRA_ID_AliasRT: return STRSPAN("AliasRT");
	default: return EMPTY_SPAN;
	}
}

/* Write an RelativeDistinguishedName. Value is a PrintableString */
static asn1e write_rdn(asn1_writer *w, span oid, span value)
{
	/* RDN ::= SET of AttributeTypeAndValue */
	asn1_writer_open(w, ASN1_SET, asn1_len_small);
	{
		/* AttributeTypeAndValue ::= SEQUENCE { type oid, value } */
		asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
		{
			asn1_write(w, ASN1_OBJECT_IDENTIFIER, oid, 0);
			asn1_write(w, ASN1_PrintableString, value, 0);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_name(asn1_writer *w,
			cmrt_caliptra_id_t identity,
			const cmrt_caliptra_deviceinfo_t *deviceinfo)
{
	/* SEQUENCE of RDN */
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_organizationName[] = { 0x55, 0x4, 0xa };
		write_rdn(w, SPAN(id_organizationName), STRSPAN("Rambus"));
		static const uint8_t id_organizationalUnitName[] = { 0x55, 0x4, 0xb };
		write_rdn(w, SPAN(id_organizationalUnitName), STRSPAN("CMRT"));
		static const uint8_t id_commonName[] = { 0x55, 0x4, 0x3 };
		/* The commonName is formatted as:
		 * "IDevID D: 0102030405060708090A0B0C O: 0D0E0F1011121314"
		 */
		uint8_t cn_buf[64];
		span_writer cn = SPAN_WRITER(cn_buf);
		span_writer_append(cn, cmrt_caliptra_id_name(identity));
		span_writer_append(cn, STRSPAN(" D: "));
		span_writer_append_hex(cn, SPAN(deviceinfo->device_id));
		span_writer_append(cn, STRSPAN(" O: "));
		span_writer_append_hex(cn, SPAN(deviceinfo->oem_id));
		write_rdn(w, SPAN(id_commonName), span_writer_span(cn));
	}
	return asn1_writer_close(w);
}

static asn1e write_subjectpublickeyinfo(asn1_writer *w, const cmrt_caliptra_pubkey_t *pubkey)
{
	/* SEQUENCE { algorithmId, publicKey } */
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		/* AlgorithmIdentifier ::= SEQUENCE { algorithm, parameters } */
		static const uint8_t id_ecpublickey[] = {
			0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02, 0x01
		};
		static const uint8_t id_namedcurve_secp384r1[] = {
			0x2b, 0x81, 0x04, 0x0, 0x22
		};
		asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
		{
			asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_ecpublickey), 0);
			asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_namedcurve_secp384r1), 0);
		}
		asn1_writer_close(w);

		/* the public key is wrapped in a BIT STRING */
		asn1_writer_open(w, ASN1_BIT_STRING, asn1_len_small);
		{
			/* A DER-encoded bitstring starts with the number of
			 * unused bits, which is zero in our case. The EC
			 * public key itself starts with 0x04 (indicating
			 * uncompressed format), which is followed by the X
			 * and Y coordinates.
			 */
			asn1_write_raw(w, STRSPAN("\x00\x04"));
			asn1_write_raw(w, SPAN(pubkey->x));
			asn1_write_raw(w, SPAN(pubkey->y));
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_ext_basicconstraints(asn1_writer *w, bool ca)
{
	static const uint8_t id_basicConstraints[] = { 0x55, 0x1d, 0x13 };
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_basicConstraints), 0);
		/* critical: true */
		asn1_write_bool(w, true);
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
			{
				/* CA: is_ca */
				asn1_write_bool(w, ca);
			}
			asn1_writer_close(w);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_ext_keyusage(asn1_writer *w)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_keyUsage[] = { 0x55, 0x1d, 0xf };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_keyUsage), 0);
		/* critical: true */
		asn1_write_bool(w, true);
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			/* keyCertSign(5) */
			uint8_t ku = 1u << (7-5); /* has to be stored in reverse */
			asn1_write(w, ASN1_BIT_STRING, SPAN(ku), 0x102); /* 2 unused bits */
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_ext_subj_keyid(asn1_writer *w, span kid)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_ce_subjectKeyIdentifier[] = { 0x55, 0x1d, 0xe };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_ce_subjectKeyIdentifier), 0);
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			asn1_write(w, ASN1_OCTET_STRING, kid, 0);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_ext_auth_keyid(asn1_writer *w, span kid)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_ce_authorityKeyIdentifier[] = { 0x55, 0x1d, 0x23 };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_ce_authorityKeyIdentifier), 0);
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
			{
				asn1_write(w, ASN1_IMPLICIT(0, ASN1_OCTET_STRING), kid, 0);
			}
			asn1_writer_close(w);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

/* Write a DiceTcbInfo structure. */
static asn1e write_tcbinfo(asn1_writer *w, const cmrt_caliptra_tcbinfo_t *info)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		/* vendor */
		asn1_write(w, ASN1_IMPLICIT(0, ASN1_UTF8String), STRSPAN("Rambus"), 0);
		/* model */
		asn1_write(w, ASN1_IMPLICIT(1, ASN1_UTF8String), STRSPAN("CMRT"), 0);
		/* version */
		asn1_write(w, ASN1_IMPLICIT(2, ASN1_UTF8String),
			   span_from(info->version, info->version_len), 0);
		/* layer */
		asn1_write_smallint(w, info->layer, ASN1_IMPLICIT(4, ASN1_INTEGER));
		/* fwids */
		if (info->fwids != NULL) {
			/* fwidlist ::= SEQUENCE of fwid */
			asn1_writer_open(w, ASN1_IMPLICIT(6, ASN1_SEQUENCE), asn1_len_small);
			{
				/* fwid ::= SEQUENCE { hashAlg, digest } */
				for (size_t i = 0; i < info->fwids_len; ++i) {
					asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
					{
						/* We only support sha384 digests. */
						static const uint8_t id_sha384[] = {
							0x60, 0x86, 0x48, 0x1, 0x65, 0x3, 0x4, 0x2, 0x2
						};
						asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_sha384), 0);
						asn1_write(w, ASN1_OCTET_STRING,
							   span_from(info->fwids[i], sizeof(*info->fwids[i])), 0);
					}
					asn1_writer_close(w);
				}
			}
			asn1_writer_close(w);
		}
		/* flags */
		if (info->debug_mode) {
			/* Bit 3, stored reversed; 4 unused bits */
			uint8_t debugflag = 1u << (7-3);
			asn1_write(w, ASN1_IMPLICIT(7, ASN1_BIT_STRING), SPAN(debugflag), 0x104);
		}
	}
	return asn1_writer_close(w);
}

/* Write a MultiTcbInfo structure. */
static asn1e write_ext_tcbinfos(asn1_writer *w, const cmrt_caliptra_tcbinfo_t *infos, size_t infos_len)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_tcg_dice_MultiTcbInfo[] = { 0x67, 0x81, 0x5, 0x5, 0x4, 0x5 };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_tcg_dice_MultiTcbInfo), 0);

		/* NOTE: we don't make it critical for now, as HLOS
		 * side validation libraries may not know about it.
		 */
		const bool dice_is_critical = false;
		if (dice_is_critical) {
			/* critical: true */
			asn1_write_bool(w, true);
		}
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			/* SEQUENCE of DiceTcbInfo */
			asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
			{
				for (size_t i = 0; i < infos_len; ++i) {
					write_tcbinfo(w, &infos[i]);
				}
			}
			asn1_writer_close(w);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_policyinformation(asn1_writer *w, span policy_oid)
{
	/* SEQUENCE { oid, [omitted] qualifier } */
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, policy_oid, 0);
	}
	return asn1_writer_close(w);
}

static asn1e write_ext_certificatepolicies(asn1_writer *w, const cmrt_caliptra_tcb_t *tcb)
{
	/* TCG DICE OIDs */
	static const uint8_t id_tcg_dice_kp_identityInit[] = {
		0x67, 0x81, 0x05, 0x05, 0x04, 0x64, 0x06,
	};
	static const uint8_t id_tcg_dice_kp_attestInit[] = {
		0x67, 0x81, 0x05, 0x05, 0x04, 0x64, 0x08,
	};
	static const uint8_t id_tcg_dice_kp_eca[] = {
		0x67, 0x81, 0x05, 0x05, 0x04, 0x64, 0x0c,
	};
	static const uint8_t id_tcg_dice_kp_identityLoc[] = {
		0x67, 0x81, 0x05, 0x05, 0x04, 0x64, 0x07,
	};
	static const uint8_t id_tcg_dice_kp_attestLoc[] = {
		0x67, 0x81, 0x05, 0x05, 0x04, 0x64, 0x09,
	};
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static const uint8_t id_certificatePolicies[] = { 0x55, 0x1d, 0x20 };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_certificatePolicies), 0);
		/* critical: true */
		asn1_write_bool(w, true);
		asn1_writer_open(w, ASN1_OCTET_STRING, asn1_len_small);
		{
			/* SEQUENCE of PolicyInformation */
			asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
			{
				if (tcb->identity == CMRT_CALIPTRA_ID_IDevID) {
					write_policyinformation(w, SPAN(id_tcg_dice_kp_identityInit));
					write_policyinformation(w, SPAN(id_tcg_dice_kp_attestInit));
					write_policyinformation(w, SPAN(id_tcg_dice_kp_eca));
				} else if (tcb->identity == CMRT_CALIPTRA_ID_LDevID) {
					write_policyinformation(w, SPAN(id_tcg_dice_kp_identityLoc));
					write_policyinformation(w, SPAN(id_tcg_dice_kp_attestLoc));
					write_policyinformation(w, SPAN(id_tcg_dice_kp_eca));
				} else {
					/* AliasFMC, AliasRT */
					write_policyinformation(w, SPAN(id_tcg_dice_kp_eca));
				}
			}
			asn1_writer_close(w);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_attributes(asn1_writer *w, const cmrt_caliptra_csr_params_t *params)
{
	/* SET of Attribute */
	asn1_writer_open(w, ASN1_IMPLICIT(0, ASN1_SET), asn1_len_medium);
	{
		static const uint8_t id_extensionRequest[] = {
			0x2a, 0x86, 0x48, 0x86, 0xf7, 0xd, 0x1, 0x9, 0xe
		};
		asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_medium);
		{
			asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_extensionRequest), 0);
			asn1_writer_open(w, ASN1_SET, asn1_len_medium);
			{
				/* SEQUENCE of Extension */
				asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_medium);
				write_ext_basicconstraints(w, true);
				write_ext_keyusage(w);
				write_ext_tcbinfos(w, params->tcbinfos, params->tcbinfos_len);
				write_ext_certificatepolicies(w, params->subject);
				asn1_writer_close(w);
			}
			asn1_writer_close(w);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_csrinfo(asn1_writer *w, const cmrt_caliptra_csr_params_t *params)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_large);
	{
		/* version v1(0) */
		asn1_write_smallint(w, 0, ASN1_INTEGER);
		/* subject */
		write_name(w, params->subject->identity, params->deviceinfo);
		/* subjectPKInfo */
		write_subjectpublickeyinfo(w, params->subject->pubkey);
		/* attributes */
		write_attributes(w, params);
	}
	return asn1_writer_close(w);
}

static asn1e write_sigalg(asn1_writer *w)
{
	/* We only support ecdsa-with-sha384 */
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		static uint8_t id_ecdsa_sha384[] = { 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x4, 0x3, 0x3 };
		asn1_write(w, ASN1_OBJECT_IDENTIFIER, SPAN(id_ecdsa_sha384), 0);
	}
	return asn1_writer_close(w);
}

/* Write an ECDSA signature. */
static asn1e write_sig(asn1_writer *w, span sigr, span sigs)
{
	/* BIT STRING encapsulating a sequence of two INTEGERs (r, s) */
	asn1_writer_open(w, ASN1_BIT_STRING, asn1_len_small);
	{
		/* zero unused bits */
		asn1_write_raw(w, STRSPAN("\x00"));
		asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
		{
			asn1_write_longint(w, sigr);
			asn1_write_longint(w, sigs);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static asn1e write_validity(asn1_writer *w)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_small);
	{
		asn1_write(w, ASN1_GENERALIZED_TIME, STRSPAN("20220901235959Z"), 0);
		asn1_write(w, ASN1_GENERALIZED_TIME, STRSPAN("99991231235959Z"), 0);
	}
	return asn1_writer_close(w);
}

/* Calculate a key id from public key, based on RFC5280 4.2.1.2:
 *
 *      (1) The keyIdentifier is composed of the 160-bit SHA-1 hash of
 *      the value of the BIT STRING subjectPublicKey (excluding the
 *      tag, length, and number of unused bits).
 *
 * except SHA-1 is replaced with SHA384.
 */
static void keyid_hash(const cmrt_caliptra_pubkey_t *pubkey, cmrt_caliptra_digest_t *pkhash)
{
	alignas(4) struct {
		uint8_t type;
		cmrt_caliptra_pubkey_t pubkey;
	} __attribute__((packed)) pk_bitstring = {
		.type = 0x04, /* uncompressed point, \x04 */
		.pubkey = *pubkey,
	};
	sha384(SPAN(pk_bitstring), SPAN(*pkhash));
}

static asn1e write_cert_extensions(asn1_writer *w, const cmrt_caliptra_cert_params_t *params)
{
	/* [3] EXPLICIT Extensions */
	asn1_writer_open(w, ASN1_EXPLICIT(3), asn1_len_medium);
	{
		/* SEQUENCE of Extension */
		asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_medium);
		{
			write_ext_basicconstraints(w, true);

			cmrt_caliptra_digest_t pkhash;
			keyid_hash(params->subject->pubkey, &pkhash);
			write_ext_subj_keyid(w, span_slice(SPAN(pkhash), 0, 20));

			if (params->issuer->pubkey != NULL) {
				cmrt_caliptra_digest_t pkhash;
				keyid_hash(params->issuer->pubkey, &pkhash);
				write_ext_auth_keyid(w, span_slice(SPAN(pkhash), 0, 20));
			}

			write_ext_keyusage(w);
			write_ext_certificatepolicies(w, params->subject);
			write_ext_tcbinfos(w, params->tcbinfos, params->tcbinfos_len);
		}
		asn1_writer_close(w);
	}
	return asn1_writer_close(w);
}

static void calc_serial(span sn, const cmrt_caliptra_tcb_t *tcb)
{
	/* sn = TRUNCATE(20, SHA384(pubkey || keyname))
	 * sn[0] &= 0x7f
	 */
	alignas(4) uint8_t sn_buf[CMRT_CALIPTRA_KEY_LEN * 2 + 16];
	span_writer snh = SPAN_WRITER(sn_buf);
	span_writer_append(snh, SPAN(tcb->pubkey->x));
	span_writer_append(snh, SPAN(tcb->pubkey->y));
	span_writer_append(snh, cmrt_caliptra_id_name(tcb->identity));
	uint8_t snhash[CMRT_CALIPTRA_HASH_LEN];
	sha384(span_writer_span(snh), SPAN(snhash));
	snhash[0] &= 0x7f;
	(void)span_copy(sn, span_slice(SPAN(snhash), 0, 20));
}

static asn1e write_tbscert(asn1_writer *w, const cmrt_caliptra_cert_params_t *params)
{
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_large);
	/* version [0] EXPLICIT INTEGER */
	{
		enum { Version_v3 = 2 };
		asn1_writer_open(w, ASN1_EXPLICIT(0), asn1_len_small);
		{
			asn1_write_smallint(w, Version_v3, ASN1_INTEGER);
		}
		asn1_writer_close(w);
		/* serialNumber */
		uint8_t sn[20];
		calc_serial(SPAN(sn), params->subject);
		asn1_write_longint(w, SPAN(sn));

		/* signature AlgorithmIdentifier */
		write_sigalg(w);
		/* issuer */
		write_name(w, params->issuer->identity, params->deviceinfo);
		/* validity */
		write_validity(w);
		/* subject */
		write_name(w, params->subject->identity, params->deviceinfo);
		/* subjectPublicKeyInfo */
		write_subjectpublickeyinfo(w, params->subject->pubkey);
		/* extensions */
		write_cert_extensions(w, params);
	}
	return asn1_writer_close(w);
}

/* Sign tbs with ecdsa-with-sha384 using the given private key and append the signature */
static asn1e x509_sign(asn1_writer *w, span tbs, const cmrt_caliptra_privkey_t *privkey)
{
	uint8_t digest[CMRT_CALIPTRA_HASH_LEN];
	sha384(tbs, SPAN(digest));

	struct {
		uint8_t r[CMRT_CALIPTRA_KEY_LEN];
		uint8_t s[CMRT_CALIPTRA_KEY_LEN];
	} sig;
	p384_sign(SPAN(*privkey), SPAN(digest), SPAN(sig.r), SPAN(sig.s));
	return write_sig(w, SPAN(sig.r), SPAN(sig.s));
}

int cmrt_caliptra_write_csr(void *buf, size_t *len, const cmrt_caliptra_csr_params_t *params)
{
	asn1_writer wr, *w;
	w = &wr;

	if ((buf == NULL) || (len == NULL)) {
		return -1;
	}
	asn1_writer_init(w, (span){buf, *len});
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_large);
	{
		/* certificationRequestInfo */
		asn1e tbs = write_csrinfo(w, params);

		/* signatureAlgorithm */
		write_sigalg(w);

		/* signature */
		x509_sign(w, asn1_e2span(tbs), params->subject->privkey);
	}
	asn1e csr = asn1_writer_close(w);
	if (w->error == 0) {
		*len = csr.n;
		return 0;
	} else {
		return -1;
	}
}

int cmrt_caliptra_write_cert(void *buf, size_t *len, const cmrt_caliptra_cert_params_t *params)
{
	asn1_writer wr, *w;
	w = &wr;

	asn1_writer_init(w, (span){buf, *len});
	asn1_writer_open(w, ASN1_SEQUENCE, asn1_len_large);
	{
		/* tbsCertificate */
		asn1e tbs = write_tbscert(w, params);

		/* signatureAlgorithm */
		write_sigalg(w);

		/* signature */
		x509_sign(w, asn1_e2span(tbs), params->issuer->privkey);
	}
	asn1e cert = asn1_writer_close(w);
	if (w->error == 0) {
		*len = cert.n;
		return 0;
	} else {
		return -1;
	}
}
