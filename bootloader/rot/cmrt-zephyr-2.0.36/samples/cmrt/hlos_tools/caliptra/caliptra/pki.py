# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

# pylint: disable=unsubscriptable-object

import hmac
from dataclasses import dataclass
from datetime import datetime, timezone
from hashlib import sha384
from typing import List

# pylint: disable=import-error
import asn1crypto.algos
import asn1crypto.csr
import asn1crypto.keys
import cryptography.hazmat.primitives.asymmetric.ec as pyca_ec
from asn1crypto import x509
from asn1crypto.core import (
    BitString,
    Integer,
    OctetString,
    Sequence,
    SequenceOf,
    UTF8String,
)
from certbuilder import CertificateBuilder
from certvalidator import CertificateValidator, ValidationContext
from oscrypto import asymmetric

# pylint: enable=import-error

# DICE OIDs
oid_tcg = "2.23.133"
oid_tcg_dice = f"{oid_tcg}.5.4"

# Policy OIDs
oid_tcg_dice_kp = f"{oid_tcg_dice}.100"
oid_tcg_dice_kp_identityInit = f"{oid_tcg_dice_kp}.6"
oid_tcg_dice_kp_identityLoc = f"{oid_tcg_dice_kp}.7"
oid_tcg_dice_kp_attestInit = f"{oid_tcg_dice_kp}.8"
oid_tcg_dice_kp_attestLoc = f"{oid_tcg_dice_kp}.9"
oid_tcg_dice_kp_assertInit = f"{oid_tcg_dice_kp}.10"
oid_tcg_dice_kp_assertLoc = f"{oid_tcg_dice_kp}.11"
oid_tcg_dice_kp_eca = f"{oid_tcg_dice_kp}.12"

# TCB info
oid_tcg_dice_tcbinfo = f"{oid_tcg_dice}.1"
oid_tcg_dice_multi_tcbinfo = f"{oid_tcg_dice}.5"

# pylint: disable=protected-access

CERT_BEGIN_DATE = datetime(2022, 9, 1, 23, 59, 59, tzinfo=timezone.utc)
CERT_END_DATE = datetime(9999, 12, 31, 23, 59, 59, tzinfo=timezone.utc)


class OperationalFlags(BitString):
    _map = {
        0: "notConfigured",
        1: "notSecure",
        2: "recovery",
        3: "debug",
    }


class FWID(Sequence):
    _fields = [
        ("hashAlg", asn1crypto.algos.DigestAlgorithmId),
        ("digest", OctetString),
    ]


class FWIDLIST(SequenceOf):
    _child_spec = FWID


class DiceTcbInfo(Sequence):
    _fields = [
        ("vendor", UTF8String, dict(implicit=0, optional=True)),
        ("model", UTF8String, dict(implicit=1, optional=True)),
        ("version", UTF8String, dict(implicit=2, optional=True)),
        ("svn", Integer, dict(implicit=3, optional=True)),
        ("layer", Integer, dict(implicit=4, optional=True)),
        ("index", Integer, dict(implicit=5, optional=True)),
        ("fwids", FWIDLIST, dict(implicit=6, optional=True)),
        ("flags", OperationalFlags, dict(implicit=7, optional=True)),
        ("vendorInfo", OctetString, dict(implicit=8, optional=True)),
        ("type", OctetString, dict(implicit=9, optional=True)),
    ]


class DiceTcbInfoSeq(SequenceOf):
    _child_spec = DiceTcbInfo


# TODO verify asn1crypto version

# Monkey-patch asn1crypto to let it know about the new extensions.
x509.PolicyIdentifier._map[oid_tcg_dice_kp_attestInit] = "tcg-dice-kp-attestInit"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_identityInit] = "tcg-dice-kp-identityInit"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_attestLoc] = "tcg-dice-kp-attestLoc"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_identityLoc] = "tcg-dice-kp-identityLoc"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_assertInit] = "tcg-dice-kp-assertInit"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_assertLoc] = "tcg-dice-kp-assertLoc"
x509.PolicyIdentifier._map[oid_tcg_dice_kp_eca] = "tcg-dice-kp-eca"


x509.ExtensionId._map[oid_tcg_dice_multi_tcbinfo] = "tcg-dice-MultiTcbInfo"
x509.Extension._oid_specs["tcg-dice-MultiTcbInfo"] = DiceTcbInfoSeq
x509.ExtensionId._map[oid_tcg_dice_tcbinfo] = "tcg-dice-TcbInfo"
x509.Extension._oid_specs["tcg-dice-TcbInfo"] = DiceTcbInfo


class GeneralizedTimeAlways(x509.Time):
    _alternatives = [
        ("utc_time", x509.GeneralizedTime),
        ("general_time", x509.GeneralizedTime),
    ]


def ecckpdf(inputkey, keyname):
    xb = hmac.new(inputkey, keyname, sha384).digest()
    priv = int.from_bytes(xb, "big")
    # This is a bit convoluted: since asn1crypto does not have a way
    # to use a fixed private key, we have to deserialize one. For that
    # we need a public key too because they use d2i_AutoPrivateKey()
    # and the heuristics there relies on the public key being in the
    # PrivateKeyInfo object, even though it would be optional. We
    # calculate the public key with the cryptography.io libraries.
    pyca_priv = pyca_ec.derive_private_key(priv, pyca_ec.SECP384R1())
    pn = pyca_priv.public_key().public_numbers()
    pubx, puby = pn.x, pn.y
    # Wrap into asn1 and load into an asn1crypto private key...
    dom = asn1crypto.keys.ECDomainParameters(
        dict(named=asn1crypto.keys.NamedCurve("secp384r1"))
    )
    pka = asn1crypto.keys.PrivateKeyAlgorithm(dict(algorithm="ec", parameters=dom))
    # ECPrivateKey from RFC 5915
    prv = asn1crypto.keys.ECPrivateKey(
        dict(
            version=1,
            private_key=priv,
            parameters=dom,
            public_key=asn1crypto.keys.ECPointBitString.from_coords(pubx, puby),
        )
    )
    # PKCS#8 PrivateKeyInfo from RFC 5208
    pki = asn1crypto.keys.PrivateKeyInfo(
        dict(
            version=0,
            private_key_algorithm=pka,
            private_key=prv,
        )
    )
    return asymmetric.load_private_key(pki.dump())


def validate_csr_sig(csr: asn1crypto.csr.CertificationRequest):
    """Validate the self-signature on the CSR"""
    spk = csr["certification_request_info"]["subject_pk_info"]
    pub = asymmetric.load_public_key(spk)
    tbs = csr["certification_request_info"].dump()
    sig = csr["signature"].native
    alg = csr["signature_algorithm"]
    assert alg.signature_algo == "ecdsa"
    asymmetric.ecdsa_verify(pub, sig, tbs, alg.hash_algo)


def der_to_csr(der: bytes) -> asn1crypto.csr.CertificationRequest:
    return asn1crypto.csr.CertificationRequest.load(bytes(der))


def load_csr(path: str) -> asn1crypto.csr.CertificationRequest:
    return der_to_csr(open(path, "rb").read())


def issue_cert(
    csr: asn1crypto.csr.CertificationRequest,
    issuer: x509.Certificate,
    issuer_priv: asymmetric.PrivateKey,
    begin_date: datetime = CERT_BEGIN_DATE,
    end_date: datetime = CERT_END_DATE,
) -> x509.Certificate:
    validate_csr_sig(csr)
    csri = csr["certification_request_info"]
    # Could do more validation on the CSR...
    b = CertificateBuilder(csri["subject"], csri["subject_pk_info"])
    b.issuer = issuer
    for ext in csri["attributes"][0]["values"][0]:
        # Just add any extension requested...
        b.set_extension(ext["extn_id"], ext["extn_value"].parsed)

    b.begin_date = begin_date
    b.end_date = end_date

    # Fix up the subject key identifier: certbuilder uses sha1
    # unconditionally, and we want sha384 since CMRT uses that
    # internally.
    spkbytes = bytes(csri["subject_pk_info"]["public_key"])
    spkhash = sha384(spkbytes).digest()[:20]
    b.set_extension("key_identifier", OctetString(spkhash))

    # XXX: the version of CertBuilder we use hardcodes UTCTime for
    # certificate validity, but that cannot represent dates after
    # 2049. As a workaround we replace x509.Time during the call to
    # build() with this class that always uses GeneralizedTime.
    Time, x509.Time = x509.Time, GeneralizedTimeAlways
    cert = b.build(issuer_priv)
    x509.Time = Time
    return cert


@dataclass
class Authority:
    priv: asymmetric.PrivateKey
    cert: x509.Certificate

    @staticmethod
    def load(path: str, prefix: str):
        cert = asymmetric.load_certificate(f"{path}/{prefix}_cert.der")
        priv = asymmetric.load_private_key(f"{path}/{prefix}_key.der")
        return Authority(priv, cert)


def load_ca_chain(path: str):
    return Authority.load(path, "root_ca"), Authority.load(path, "sub_ca")


def create_ca_certs(cn_prefix: str, path: str):
    root_pub, root_priv = asymmetric.generate_pair("ec", curve="secp384r1")
    b = CertificateBuilder(
        dict(
            common_name=f"{cn_prefix} Root CA",
            organization_name="Rambus",
            organizational_unit_name="CMRT",
        ),
        root_pub,
    )
    b.self_signed = True
    b.ca = True
    b.end_date = datetime.fromisoformat("2049-01-01T23:59:59+00:00")
    root_cert = b.build(root_priv)

    sub_pub, sub_priv = asymmetric.generate_pair("ec", curve="secp384r1")
    b = CertificateBuilder(
        dict(
            common_name=f"{cn_prefix} Sub CA",
            organization_name="Rambus",
            organizational_unit_name="CMRT",
        ),
        sub_pub,
    )
    b.ca = True
    b.issuer = root_cert
    b.end_date = datetime.fromisoformat("2049-01-01T23:59:59Z+00:00")
    sub_cert = b.build(root_priv)

    open(f"{path}/root_ca_cert.der", "wb").write(
        asymmetric.dump_certificate(root_cert, encoding="der")
    )
    open(f"{path}/root_ca_key.der", "wb").write(
        asymmetric.dump_private_key(root_priv, passphrase=None, encoding="der")
    )
    open(f"{path}/sub_ca_cert.der", "wb").write(
        asymmetric.dump_certificate(sub_cert, encoding="der")
    )
    open(f"{path}/sub_ca_key.der", "wb").write(
        asymmetric.dump_private_key(sub_priv, passphrase=None, encoding="der")
    )


def validate_cert_chain(
    cert: x509.Certificate,
    intermediates: List[x509.Certificate],
    roots: List[Authority],
):
    ctx = ValidationContext(trust_roots=[r.cert.asn1 for r in roots])
    validator = CertificateValidator(cert, intermediates, validation_context=ctx)
    validator.validate_usage(set())
