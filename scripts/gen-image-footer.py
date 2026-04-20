#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Add image footer to the raw file created by cmrt-raw-footer.py.
#
# Running this tool without giving any arguments will show usage message.
#

import sys
import os
import json
import hashlib
import hmac

from struct import pack

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import ec, rsa
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives.asymmetric import utils

class Die(Exception):
    def __init__(self, *_list): # pylint: disable=super-init-not-called
        print(sys.argv[0].rsplit('/', 2)[-1], end=': ', file=sys.stderr)
        print(_list[0].format(*_list[1:]), file=sys.stderr)
        raise SystemExit(1)
    pass

def info(*args, **kwargs):
    if _verbose:
        print(*args, **kwargs)

# Silence pylint's nagging about raising exceptions with unformatted format
# strings. `Die` will format the format string using the rest args.
# pylint: disable=raising-format-tuple

_verbose = False
# do not check incompatible permissions for test purposes only
_skip_validity_check = False

PK_UNSIGNED    = 0
PK_ECDSA_P256  = 1
PK_HMAC_SHA256 = 2
PK_ECDSA_P521  = 3
PK_RSAPSS_3K   = 4
PK_RSAPSS_4K   = 5
PK_SHA256      = 6
PK_LMS         = 7
PK_LMS_HSS     = 8
PK_XMSS        = 9
PK_XMSS_MT     = 10
PK_ECDSA_P384  = 11

class Imgkey:
    #pylint: disable=no-member
    @property
    def pub_type(self):
        """Key type serialized as little-endian integer."""
        return self.keytype.to_bytes(4, "little")

    @property
    def keyid(self):
        """Concatenation of the key type and public key bytes used to
        calculate key hash.

        """
        return self.pub_type + self.pub_bytes

    def keyhash(self):
        """Return the public key hash used in the image footer."""
        info('pubkey:  ', self.keyid.hex())
        kh = hashlib.sha256(self.keyid).digest()
        info('keyhash:', kh.hex())
        return kh

    def sign(self, data):
        """Calculate signature over @data and return it in the format expected
        by CMRT.

        """
        raise NotImplementedError()

class Unsigned_imgkey(Imgkey):
    def __init__(self):
        self.keytype = PK_UNSIGNED
        self.pub_bytes = b""
        self.signature_len = 0

    def sign(self, data):
        return b""

# The Rsa_imgkey and Ec_imgkey classes can represent both a private OR
# a public key, decided at construction.  The sign() method fails if
# it is not a private key.

class Rsa_imgkey(Imgkey):
    def __init__(self, priv=None, pub=None):
        assert bool(priv) ^ bool(pub)
        self.key = None
        if pub:
            assert isinstance(pub, rsa.RSAPublicKey)
            self.pub = pub
        if priv:
            assert isinstance(priv, rsa.RSAPrivateKey)
            self.key = priv
            self.pub = self.key.public_key()

        if self.pub.key_size == 3072:
            self.keytype = PK_RSAPSS_3K
            self.signature_len = 384
        elif self.pub.key_size == 4096:
            self.keytype = PK_RSAPSS_4K
            self.signature_len = 512
        else:
            raise Die("Unsupported RSA key: {}", self.pub)

        l = self.pub.key_size // 8
        n = self.pub.public_numbers().n
        e = self.pub.public_numbers().e
        self.pub_bytes = n.to_bytes(l, "big") + e.to_bytes(l, "big")

    def sign(self, data):
        if self.key is None:
            raise Die("Not an RSA private key")
        ref_sha = hashlib.sha3_512(data)
        info(ref_sha.name + ':', ref_sha.hexdigest())
        return self.key.sign(ref_sha.digest(),
                             padding.PSS(mgf=padding.MGF1(hashes.SHA3_512()),
                                         salt_length=hashes.SHA3_512().digest_size),
                             utils.Prehashed(hashes.SHA3_512()))

class Ec_imgkey(Imgkey):
    def __init__(self, priv=None, pub=None):
        assert bool(priv) ^ bool(pub)
        self.key = None
        if pub:
            assert isinstance(pub, ec.EllipticCurvePublicKey)
            self.pub = pub
        if priv:
            assert isinstance(priv, ec.EllipticCurvePrivateKey)
            self.key = priv
            self.pub = self.key.public_key()

        if isinstance(self.pub.curve, ec.SECP256R1):
            self.keytype = PK_ECDSA_P256
            self.signhasher = hashes.SHA256
            self.signhasher_py = hashlib.sha256
            self.signature_len = 64
        elif isinstance(self.pub.curve, ec.SECP521R1):
            self.keytype = PK_ECDSA_P521
            self.signhasher = hashes.SHA512
            self.signhasher_py = hashlib.sha512
            self.signature_len = 132
        elif isinstance(self.pub.curve, ec.SECP384R1):
            self.keytype = PK_ECDSA_P384
            self.signhasher = hashes.SHA384
            self.signhasher_py = hashlib.sha384
            self.signature_len = 96
        else:
            raise Die("Unsupported EC key: {}", self.pub)
        l = (self.pub.key_size + 7) // 8
        x = self.pub.public_numbers().x
        y = self.pub.public_numbers().y
        self.pub_bytes = x.to_bytes(l, "big") + y.to_bytes(l, "big")

    def sign(self, data):
        if self.key is None:
            raise Die("Not an EC private key")
        ref_sha = self.signhasher_py(data)
        info(ref_sha.name + ':', ref_sha.hexdigest())
        sig = self.key.sign(ref_sha.digest(),
                            ec.ECDSA(utils.Prehashed(self.signhasher())))
        r, s = utils.decode_dss_signature(sig)
        l = (self.pub.key_size + 7) // 8
        sigr = r.to_bytes(l, "big")
        sigs = s.to_bytes(l, "big")
        info('sigr:  ', sigr.hex())
        info('sigs:  ', sigs.hex())
        signature = sigr + sigs
        return signature

class Hmac_imgkey(Imgkey):
    def __init__(self, keydata):
        keyhex = keydata.strip()
        if len(keyhex) != 64:
            raise ValueError("Wrong HMAC key length (expected 64 hex digits)")
        self.key = bytes.fromhex(keyhex)
        self.keytype = PK_HMAC_SHA256
        self.signature_len = 32
        self.pub_bytes = b"\x02\x00\x00\x00" # PNAK

    def sign(self, data):
        return hmac.new(self.key, data, hashlib.sha256).digest()

class Sha_imgkey(Imgkey):
    def __init__(self):
        self.keytype = PK_SHA256
        self.pub_bytes = b""
        self.signature_len = 32

    def sign(self, data):
        return hashlib.sha256(data).digest()

# The Lms_imgkey is used for storing LMS and LMS-HSS keys

class Lms_imgkey(Imgkey):
    def __init__(self, lmstypes, lmotstypes, sk, pk):
        from lms import LMS # pylint: disable=import-outside-toplevel, import-error, unused-import
        self.lms = LMS() # pylint: disable=undefined-variable
        assert len(lmstypes) == len(lmotstypes)
        if len(lmstypes) == 1:
            self.keytype = PK_LMS
            self.signature_len = self.lms.sig_size(lmstypes[0], lmotstypes[0])
        else:
            self.keytype = PK_LMS_HSS
            self.signature_len = self.lms.hss_sig_size(lmstypes, lmotstypes)

        self.lmstypes = lmstypes
        self.lmotstypes = lmotstypes
        self.sk = sk
        self.pub_bytes = pk

    def sign(self, data):
        ref_sha = hashlib.sha256(data)
        info(ref_sha.name + ':', ref_sha.hexdigest())
        if self.keytype == PK_LMS:
            info("LMS signature lmstype:%s lmsotstype:%s" %
                 (self.lms.lmstypes_to_str(self.lmstypes),
                  self.lms.lmotstypes_to_str(self.lmotstypes)))
            sig = self.lms.sign(self.sk, ref_sha.digest(), ref_sha.digest_size,
                                self.lmstypes[0], self.lmotstypes[0])
        elif self.keytype == PK_LMS_HSS:
            info("LMS-HSS signature lmstypes:%s lmsotstypes:%s" %
                 (self.lms.lmstypes_to_str(self.lmstypes),
                  self.lms.lmotstypes_to_str(self.lmotstypes)))
            sig = self.lms.hss_sign(self.sk, ref_sha.digest(),
                                    ref_sha.digest_size,
                                    self.lmstypes, self.lmotstypes)
        return sig.raw


# The Xmss_imgkey is used for storing XMSS and XMSS^MT keys

class Xmss_imgkey(Imgkey):
    def __init__(self, mt, xmsstype, sk, pk):
        from xmss import XMSS # pylint: disable=import-outside-toplevel, import-error, unused-import
        self.xmss = XMSS() # pylint: disable=undefined-variable
        if mt:
            self.keytype = PK_XMSS_MT
            self.signature_len = self.xmss.mt_sig_size(xmsstype)
        else:
            self.keytype = PK_XMSS
            self.signature_len = self.xmss.sig_size(xmsstype)

        self.xmsstype = xmsstype
        self.sk = sk
        self.pub_bytes = pk

    def sign(self, data):
        ref_sha = hashlib.sha256(data)
        info(ref_sha.name + ':', ref_sha.hexdigest())
        if self.keytype == PK_XMSS:
            info("XMSS signature xmstype:%s" %
                 self.xmss.xmss_type_to_str(self.xmsstype))
            sig = self.xmss.sign(self.sk, ref_sha.digest(),
                                 ref_sha.digest_size,
                                 self.xmsstype)
        elif self.keytype == PK_XMSS_MT:
            info("XMSS^MT signature xmss_mt_type:%s" %
                 self.xmss.xmss_mt_type_to_str(self.xmsstype))
            sig = self.xmss.mt_sign(self.sk, ref_sha.digest(),
                                    ref_sha.digest_size, self.xmsstype)
        return sig.raw

def load_pubkey(keyfile):
    data = open(keyfile, "rb").read()
    if data.startswith(b"-----BEGIN "):
        loader = serialization.load_pem_public_key
    else:
        loader = serialization.load_der_public_key
    return loader(data, default_backend())

def load_privkey(keyfile):
    data = open(keyfile, "rb").read()
    if data.startswith(b"-----BEGIN "):
        loader = serialization.load_pem_private_key
    else:
        loader = serialization.load_der_private_key
    return loader(data, None, default_backend())

def load_key(filename):
    """Try to load any kind of key from @filename.  First asymmetric
    private keys are tried, accepting both PEM and DER formats, then
    public keys, and finally construction of a HMAC key is attempted.

    """
    #pylint: disable=import-outside-toplevel, import-error, unused-import
    if filename.endswith('.lmskey'):
        from lms import load_lms_key
        lmstypes, lmotstypes, sk, pk = load_lms_key(filename)
        return Lms_imgkey(lmstypes, lmotstypes, sk, pk)
    if filename.endswith('.xmsskey'):
        from xmss import load_xmss_key
        mt, xmsstype, sk, pk = load_xmss_key(filename)
        return Xmss_imgkey(mt, xmsstype, sk, pk)
    #pylint: enable=import-outside-toplevel, import-error, unused-import

    # First try to load as a EC/RSA private key.
    try:
        key = load_privkey(filename)
        if isinstance(key, rsa.RSAPrivateKey):
            return Rsa_imgkey(priv=key)
        if isinstance(key, ec.EllipticCurvePrivateKey):
            return Ec_imgkey(priv=key)
    except ValueError:
        pass
    # Next, try as public keys.
    try:
        key = load_pubkey(filename)
        if isinstance(key, rsa.RSAPublicKey):
            return Rsa_imgkey(pub=key)
        if isinstance(key, ec.EllipticCurvePublicKey):
            return Ec_imgkey(pub=key)
    except ValueError:
        pass
    # Finally try it as a HMAC key.
    try:
        return Hmac_imgkey(open(filename, "rt").read())
    except ValueError:
        pass
    raise Die("Unable to parse '{}' as any known key type", filename)

def wraphex(data, n=8, indent="\t\t"):
    """Format @data as C hex literals and wrap it at every @nth byte.
    Prefix each line with @indent.

    """
    lines = []
    for i in range(0, len(data), n):
        hx = "".join("0x{:02x}, ".format(b) for b in data[i:i + n]).rstrip()
        lines.append(indent + hx)
    return "\n".join(lines)

def template():
    return '''{
    "container_format_version": 1,
    "entity": {
        "caveats": [ 1 ],
        "SCID": "c0ffbeef"
    },
    "container_version": 1,
    "permissions": {
        "write_otp_slots": [ 1, 2, 3 ],
        "write_otp_keys": [ 1, 2, 3 ],
        "establish_roots": [ 0, 1, 3 ],
        "obliterate_roots": [ 0, 1, 3 ],
        "use_special_keys": [ "BNAK", "SNAK", "PNAK" ],
        "use_otp_keys": [ 1, 2, 3, 4, 5, 6, 7 ],
        "use_keydests": [ 1 ],
        "write_feature_block": [ 0, 1, 2, 3, 5, 8 ],
        "access_otp": [
            { "lo": 2048, "hi": 3068, "perms": "r" },
            { "lo": 3072, "hi": 4092, "perms": "rw" }
        ],
        "software_permissions": [ 0, 1, 2, 3, 31 ]
    }
}'''

def inc_lead():
    return r'''/*
 * Copyrght (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#include "omc_reg.h"

__attribute__ ((weak)) cmrt_omc_root_t cri_root = {'''


def set_bits(permissions, name):
    val = 0
    for i in permissions[name]: val |= (1 << i)
    return val

zero_perms = dict(lo=0, hi=0, perms='')
def otp_perms(od, i):
    lo = od['lo'] + 0
    hi = od['hi'] + 0
    r = 1 if 'r' in od['perms'] else 0
    w = 1 if 'w' in od['perms'] else 0
    if r: lo |= (1 << 15)
    if w: hi |= (1 << 15)
    s = '[{0}].s.lower_and_read = 0x{1:04X}, ' \
        '[{0}].s.upper_and_write = 0x{2:04X}'.format(i, lo, hi)
    return lo, hi, s


def read_permissions(d, file=None, write_inc_with_key=None, caveats=None):
    if not d:
        return bytes(24) # no permissions, potentially fboot container

    if write_inc_with_key is not None:
        inc = [ inc_lead() ]
        def append_inc(*args):
            inc.append(args[0] % args[1:])
            pass
    else:
        inc = False
        def append_inc(*_args): pass
        pass

    if inc:
        hashval = write_inc_with_key.keyhash()
        append_inc('\t.id.hash = {\n%s\n\t},', wraphex(hashval))
    append_inc('\t.perm = {')

    append_inc('\t\t.slot_perm = {')
    permissions = d['permissions']
    write_otp_slots = set_bits(permissions, 'write_otp_slots')
    append_inc('\t\t\t.s.general_slots = 0x%02x,', write_otp_slots)

    write_otp_keys = set_bits(permissions, 'write_otp_keys')
    append_inc('\t\t\t.s.keysplits = 0x%02x,', write_otp_keys)

    establish_roots = set_bits(permissions, 'establish_roots')
    append_inc('\t\t\t.s.root_creation = 0x%02x,', establish_roots)

    obliterate_roots = set_bits(permissions, 'obliterate_roots')
    append_inc('\t\t\t.s.root_obliteration = 0x%02x,', obliterate_roots)
    append_inc('\t\t},')

    append_inc('\t\t.key_perm = {')
    dict_use_key = dict(BNAK=1, SNAK=2, PNAK=4)
    use_key = 0
    for i in permissions['use_special_keys']: use_key |= dict_use_key[i]
    append_inc('\t\t\t.s.general_slots = 0x%02x,', use_key)

    use_otp_keys = set_bits(permissions, 'use_otp_keys')
    append_inc('\t\t\t.s.keysplits = 0x%02x,', use_otp_keys)

    key_destinations = set_bits(permissions, 'use_keydests')
    append_inc('\t\t\t.s.key_destinations = 0x%04x,', key_destinations)
    append_inc('\t\t},')

    append_inc('\t\t.feature_perm = {')
    write_feature_block = set_bits(permissions, 'write_feature_block')
    append_inc('\t\t\t.val = 0x%08x,', write_feature_block)
    append_inc('\t\t},')

    access_otp = permissions['access_otp']
    append_inc('\t\t.sw_otp_perm = {')
    if len(access_otp) >= 1:
        low_and_read_0, high_and_write_0, s = otp_perms(access_otp[0], 0)
    else:
        low_and_read_0, high_and_write_0, s = otp_perms(zero_perms, 0)
        pass
    append_inc('\t\t\t%s,', s)
    if len(access_otp) >= 2:
        low_and_read_1, high_and_write_1, s = otp_perms(access_otp[1], 1)
    else:
        low_and_read_1, high_and_write_1, s = otp_perms(zero_perms, 1)
        pass
    append_inc('\t\t\t%s,', s)
    append_inc('\t\t},')

    software = set_bits(permissions, 'software_permissions')
    append_inc('\t\t.software_perm.val = 0x%08x,', software)
    append_inc('\t},')
    append_inc('};')

    if inc:
        ofile = (file[:-5] if file.endswith('.json') else file) + '.c'
        with open(ofile, 'w') as f:
            print('\n'.join(inc), file=f)
            pass
        print("Wrote '{}'".format(ofile))
        return None
    if caveats < 1 and (write_otp_slots or write_otp_keys or
                        establish_roots or obliterate_roots or
                        low_and_read_0 or high_and_write_0 or
                        low_and_read_1 or high_and_write_1):
        msg = 'Silo-only permissions requested without silo mode caveat'
        if _skip_validity_check: print(msg)
        else: raise Die(msg)
    return pack('<BBBBBBHIHHHHI',
                write_otp_slots, write_otp_keys,
                establish_roots, obliterate_roots,
                use_key, use_otp_keys,
                key_destinations, write_feature_block,
                low_and_read_0, high_and_write_0,
                low_and_read_1, high_and_write_1,
                software)

def get_caveat_and_scid(d):
    """Parse caveats and SCID fields and return container id"""
    try:
        entity = d['entity']
        try:
            caveats = 0
            for c in entity['caveats']:
                caveats |= c
        except KeyError: # caveats field is missing
            caveats = 0
        except (TypeError, ValueError): # some caveats failed int conversion
            raise Die("Caveats field in JSON should be an array of numbers") \
                from None

        try:
            scid = int(entity['SCID'], base=16)
            if scid < 0 or scid >= 2**32:
                raise ValueError()
        except KeyError: # SCID field is missing
            raise Die("SCID field must be defined in JSON") from None
        except (TypeError, ValueError): # SCID failed int conversion
            raise Die("SCID field in JSON should be a 32-bit integer "
                      "represented as hex string, e.g. \"c0ffbeef\"") from None
    except KeyError: # entity field is missing
        caveats = 0
        scid = 0

    return caveats, scid

def load_json(path):
    if path == '-':
        # JSON parsing not required
        return {}

    with open(path) as f:
        d = json.load(f)

    if d['container_format_version'] != 1:
        raise Die('container_format_version not 1')
    return d

def show_pubkey(privkey, hash_only):
    if privkey and not os.path.isfile(privkey):
        raise Die("'{}': no such file", privkey)
    public_key = load_key(privkey)
    hashval = public_key.keyhash()
    if hash_only:
        print(hashval.hex())
    else:
        print("pubkey hash:", hashval.hex(), file=sys.stderr)
        print(wraphex(hashval, indent=" "))

def do_generate_img(caveats, scid, permissions, raw_img, keyfile, outfile,
                    re_sign=False, container_version=1, encryption_data=b''):
    if not os.path.isfile(raw_img):
        raise Die("'{}': no such file", raw_img)

    if keyfile and not os.path.isfile(keyfile):
        raise Die("'{}': no such file", keyfile)

    wipout = outfile + '.wip'
    if os.path.exists(wipout):
        raise Die("Intermediate output file '{}' exists", wipout)

    filecontents = open(raw_img, 'rb').read()
    flen = len(filecontents)
    if flen % 4:
        raise Die("File size {} in {} must be multiple of 4",
                  flen, raw_img)

#    # signing multiple images is not allowed
#    hlen1 = int.from_bytes(filecontents[:4], 'little')
#    hlen2 = int.from_bytes(filecontents[4:8], 'little')
#    if hlen1 == hlen2 ^ 0xffffffff and hlen1 + 8 != flen:
#        raise Die("Image size from header {} does not match file size {}", hlen1, flen)

    if re_sign:
        img_footer_len = int.from_bytes(filecontents[-4:], 'little')
        if not 96 <= img_footer_len <= 104520:
            raise Die('Image footer size {} in {} not between 96 and 104520',
                      img_footer_len, raw_img)
        if img_footer_len % 4:
            raise Die("Image footer size {} in {} must be multiple of 4",
                      img_footer_len, raw_img)
        # skip image header
        filecontents = filecontents[8:-img_footer_len]
        pass

    info("filesz:", len(filecontents))
    if keyfile:
        key = load_key(keyfile)
    elif outfile.endswith('rom.img'):
        key = Sha_imgkey()
    else:
        key = Unsigned_imgkey()

    container_id = key.keyhash()
    container_id += pack('<I', caveats)
    container_id += pack('<I', scid)
    info("contid:", container_id.hex())

    info("container_version:", container_version)

    # packed footer data
    metadata_length = pack('<L', 72)
    metadata_version = pack('<L', 1)
    container_version = pack('<L', container_version)

    public_key = key.pub_bytes
    public_key_type = key.pub_type

    length = len(encryption_data)
    encryption_pad = bytes(4 - length & 3) if length & ~3 else b''
    encryption_length = pack('<L', length)
    length = len(public_key)
    public_key_pad = bytes(4 - length & 3) if length & ~3 else b''
    public_key_length = pack('<L', length)
    del length
    signature_pad = bytes(4 - key.signature_len & 3) if key.signature_len & ~3 else b''
    signature_length_padded = key.signature_len + len(signature_pad)
    signature_length = pack('<L', signature_length_padded)

    footer_lead = (
        metadata_length + metadata_version +
        container_id + container_version +
        permissions +
        encryption_length + encryption_data + encryption_pad +
        public_key_type + public_key_length + public_key + public_key_pad +
        signature_length)

    # footer length (footer_length included)
    footsz = len(footer_lead) + signature_length_padded + 4
    info("footsz:", footsz)
    if footsz % 4:
        raise Die("Footer must be word aligned")
    footer_length = pack('<L', footsz)

    data = filecontents + footer_lead + footer_length
    signature = key.sign(data)

    if len(signature) != key.signature_len:
        raise Die("Internal error: signature length mismatch ({} != {})",
                  len(signature), key.signature_len)

    with open(wipout, 'wb') as wf:
        if re_sign:
            # add image header
            size = len(data) + signature_length_padded
            wf.write(pack("<ll", size, ~size))
        wf.write(filecontents)
        wf.write(footer_lead)
        wf.write(signature)
        wf.write(signature_pad)
        wf.write(footer_length)
        pass

    info('footer:', (footer_lead + signature + signature_length +
                     footer_length).hex())

    os.rename(wipout, outfile)
    if _verbose:
        os.spawnl(os.P_WAIT, '/bin/ls', 'ls', '-l', outfile)
    pass

def generate_img(raw_img, keyfile, footer, outfile, re_sign, encfile):
    d = load_json(footer)
    caveats, scid = get_caveat_and_scid(d)
    permissions = read_permissions(d, footer, caveats=caveats)
    if "container_version" in d:
        container_version = d["container_version"]
    else:
        container_version = 1

    if encfile:
        if not os.path.isfile(encfile):
            raise Die("'{}': no such file", encfile)
        encryption_data = open(encfile, 'rb').read()
    else:
        encryption_data = b''
        pass

    do_generate_img(caveats, scid, permissions, raw_img, keyfile, outfile,
                    re_sign, container_version, encryption_data)
    pass


def main():
    op = None
    re_sign = False
    while len(sys.argv) > 1:
        opt = sys.argv[1]
        if opt[0] != '-': break
        sys.argv.pop(1)
        if opt == '--': break
        if opt == '-v':
            global _verbose
            _verbose = True
            continue
        if opt == '--re-sign':
            re_sign = True
            continue
        if opt in ('--print-template', '--show-pubkey', '--show-pubkey-hash', '--create-root'):
            if op is not None:
                raise Die("Two operations: '{}' and '{}'", op, opt)
            op = opt
            continue
        if opt == '--skip-validity-check':
            global _skip_validity_check
            _skip_validity_check = True
            continue
        raise Die("'{}': unknown option", opt)

    if op == '--print-template':
        # note: no args count check. would just be extra code
        print(template())
        raise SystemExit(0)

    if op == '--create-root':
        if len(sys.argv) != 3: raise Die("--create-root pubkey.pem file.json")
        keyfile = sys.argv[1]
        if keyfile and not os.path.isfile(keyfile):
            raise Die("'{}': no such file", keyfile)
        # keyfile can be either public or private key
        public_key = load_key(keyfile)

        d = load_json(sys.argv[2])
        read_permissions(d, sys.argv[2], write_inc_with_key=public_key)
        raise SystemExit(0)

    if op == '--show-pubkey-hash':
        if len(sys.argv) != 2: raise Die("--show-pubkey-hash prikey.pem")
        show_pubkey(sys.argv[1], hash_only=True)
        raise SystemExit(0)

    if op == '--show-pubkey':
        if len(sys.argv) != 2: raise Die("--show-pubkey prikey.pem")
        show_pubkey(sys.argv[1], hash_only=False)
        raise SystemExit(0)

    # note: op = None
    if len(sys.argv) > 1 and (
            sys.argv[1].endswith('.pem') or sys.argv[1].endswith('.hmac')
            or sys.argv[1].endswith('.lmskey') or sys.argv[1].endswith('.xmsskey')):
        keyfile = sys.argv.pop(1)
    else:
        keyfile = None
        pass

    if len(sys.argv) < 4 or len(sys.argv) > 5:
        raise SystemExit("\nUsage: {0} [-v] [--re-sign] [prikey.(pem|hmac|lmskey|xmsskey)]"
                         " input.raw (footer.json|'-')"
                         " output.img [encryption.data]\n"
                         "   or  {0} --print-template\n"
                         "   or  {0} --create-root pubkey.pem file.json\n"
                         "   or  {0} --show-pubkey prikey.pem\n"
                         .format(sys.argv[0]))

    encfile = sys.argv[4] if len(sys.argv) == 5 else ''
    generate_img(sys.argv[1], keyfile, sys.argv[2], sys.argv[3],
                 re_sign, encfile)

if __name__ == '__main__':
    main()
    pass
