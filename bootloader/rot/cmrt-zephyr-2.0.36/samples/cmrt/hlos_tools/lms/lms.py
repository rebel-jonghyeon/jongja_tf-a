#!/usr/bin/env python3
#
# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# lms.py ...
#

import argparse
import os
import sys
from ctypes import CDLL, byref, c_uint32, c_char


# LM-OTS Signatures
# See Page 37 of RFC8554
LMOTS_RESERVED      = 0
LMOTS_SHA256_N32_W1 = 1
LMOTS_SHA256_N32_W2 = 2
LMOTS_SHA256_N32_W4 = 3
LMOTS_SHA256_N32_W8 = 4

# Leighton Micali Signatures (LMS) Signatures
# See Page 38 of RFC8554
LMS_RESERVED       = 0
LMS_SHA256_M32_H5  = 5
LMS_SHA256_M32_H10 = 6
LMS_SHA256_M32_H15 = 7
LMS_SHA256_M32_H20 = 8
LMS_SHA256_M32_H25 = 9

lmots_dic = { LMOTS_SHA256_N32_W1 : "LMOTS_SHA256_N32_W1",
              LMOTS_SHA256_N32_W2 : "LMOTS_SHA256_N32_W2",
              LMOTS_SHA256_N32_W4 : "LMOTS_SHA256_N32_W4",
              LMOTS_SHA256_N32_W8 : "LMOTS_SHA256_N32_W8"
            }

lms_dic = { LMS_SHA256_M32_H5  : "LMS_SHA256_M32_H5",
            LMS_SHA256_M32_H10 : "LMS_SHA256_M32_H10",
            LMS_SHA256_M32_H15 : "LMS_SHA256_M32_H15",
            LMS_SHA256_M32_H20 : "LMS_SHA256_M32_H20",
            LMS_SHA256_M32_H25 : "LMS_SHA256_M32_H25"
          }

class LMS:
    """ wrapper of liblms.so"""

    def __init__(self):
        self.lms = CDLL('liblms.so')

    def __del__(self):
        if hasattr(self, 'lms'):
            del self.lms

    # pylint: disable=R0201
    def sk_len(self):
        """ secrek key length is fixed """
        return 4 + 16 + 32

    # pylint: disable=R0201
    def pk_len(self):
        """ public key length is fixed """
        return 4 + 4 + 16 + 32

    def hss_pk_len(self):
        """ HSS public key length is fixed """
        return self.pk_len() + 4

    def keygen(self, seed, ty, otsty):
        """ seed is immutable, 48 bytes long """
        # sk = idx || seed || I, idx 8 bytes long
        sk = (c_char * self.sk_len())()
        pk = (c_char * self.pk_len())()
        self.lms.py_lms_keygen(byref(sk), byref(pk), seed, ty, otsty)
        return (sk, pk)

    def sig_size(self, ty, otsty):
        return self.lms.py_lms_sig_size(ty, otsty)

    def sign(self, sk, msg, mlen, ty, otsty):
        sig = (c_char * self.lms.py_lms_sig_size(ty, otsty))()
        sk_ct = (c_char * len(sk)).from_buffer(bytearray(sk))
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        self.lms.py_lms_sign(byref(sig), byref(sk_ct), byref(msg_ct), mlen, ty, otsty)
        return sig

    def verify(self, sig, msg, mlen, pk):
        """ all params are immutable """
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        return self.lms.py_lms_verify(byref(sig), byref(pk), byref(msg_ct), mlen)

    def hss_keygen(self, seed, tys, otstys):
        """ seed is immutable, 48 bytes long """
        assert len(tys) == len(otstys)
        sk = (c_char * self.sk_len())()
        pk = (c_char * self.hss_pk_len())()
        tys_arr = (c_uint32 * len(tys))(*tys)
        otstys_arr = (c_uint32 * len(otstys))(*otstys)
        self.lms.py_lms_hss_keygen(byref(sk), byref(pk), seed, byref(tys_arr),
                                   byref(otstys_arr), len(tys))
        return (sk, pk)

    def hss_sig_size(self, tys, otstys):
        levels = len(tys)
        tys_arr = (c_uint32 * levels)(*tys)
        otstys_arr = (c_uint32 * levels)(*otstys)
        return self.lms.py_lms_hss_sig_size(levels, byref(tys_arr),
                                            byref(otstys_arr))

    def hss_sign(self, sk, msg, mlen, tys, otstys):
        assert len(tys) == len(otstys)
        levels = len(tys)
        tys_arr = (c_uint32 * levels)(*tys)
        otstys_arr = (c_uint32 * levels)(*otstys)
        sig = (c_char * self.lms.py_lms_hss_sig_size(levels, byref(tys_arr),
                                                     byref(otstys_arr)))()
        sk_ct = (c_char * len(sk)).from_buffer(bytearray(sk))
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        self.lms.py_lms_hss_sign(byref(sk_ct), byref(sig), levels, byref(tys_arr),
                                 byref(otstys_arr), byref(msg_ct), mlen)
        return sig

    def hss_verify(self, sig, msg, mlen, pk):
        """ all params are immutable """
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        return self.lms.py_lms_hss_verify(byref(sig), byref(pk), byref(msg_ct), mlen)

    @staticmethod
    def lmstypes_to_str(lmstypes: [int]) -> str:
        return lmstypes_to_str(lmstypes)

    @staticmethod
    def lmotstypes_to_str(lmotstypes: [int]) -> str:
        return lmotstypes_to_str(lmotstypes)


def test_lms(lms):
    """ tests for lms """
    ty = LMS_SHA256_M32_H5
    otsty = LMOTS_SHA256_N32_W1

    seed = os.urandom(48)
    sk, pk = lms.keygen(seed, ty, otsty)
    msg = os.urandom(32)
    sig = lms.sign(bytes(sk), msg, 32, ty, otsty)
    ret = lms.verify(sig, msg, 32, pk)
    assert ret == 0
    msg = os.urandom(32)
    ret = lms.verify(sig, msg, 32, pk)
    assert ret != 0
    return 0


def test_lms_hss(lms):
    """test for lms-hss """
    ty = [LMS_SHA256_M32_H5, LMS_SHA256_M32_H10]
    otsty = [LMOTS_SHA256_N32_W1, LMOTS_SHA256_N32_W2]

    seed = os.urandom(48)
    sk, pk = lms.hss_keygen(seed, ty, otsty)
    msg = os.urandom(32)
    sig = lms.hss_sign(bytes(sk), msg, 32, ty, otsty)
    ret = lms.hss_verify(sig, msg, 32, pk)
    assert ret == 0
    msg = os.urandom(32)
    ret = lms.hss_verify(sig, msg, 32, pk)
    assert ret != 0
    return 0


def lmotstype_from_str(name: str) -> int:
    """Convert LMOTS type from name to id """
    for key, val in lmots_dic.items():
        if val == name:
            return key
    raise ValueError("%s: invalid LMOTS type" % name)


def lmstype_from_str(name: str) -> int:
    """Convert LMS type from name to id """
    for key, val in lms_dic.items():
        if val == name:
            return key
    raise ValueError("%s: invalid LMS type" % name)


def lmstypes_to_str(lmstypes: [int]) -> str:
    """Convert LMS types array to string """
    lmstype_str = ''
    for ty in lmstypes:
        if lmstype_str != '': lmstype_str += ' '
        lmstype_str += lms_dic[ty]
    return lmstype_str

def lmotstypes_to_str(lmotstypes: [int]) -> str:
    """Convert LMOTS types array to string """
    lmotstype_str = ''
    for otsty in lmotstypes:
        if lmotstype_str != '': lmotstype_str += ' '
        lmotstype_str += lmots_dic[otsty]
    return lmotstype_str


def save_lms_key(file: str, lmstypes: [int], lmotstypes: [int], sk: bytes, pk: bytes):
    """Save LMS key """
    print(lmstypes_to_str(lmstypes))
    print(lmotstypes_to_str(lmotstypes))
    print('sk:', sk.raw.hex())
    print('pk:', pk.raw.hex())
    if file:
        with open(file, 'w') as f:
            f.write(lmstypes_to_str(lmstypes) + "\n")
            f.write(lmotstypes_to_str(lmotstypes) + "\n")
            f.write(sk.raw.hex() + "\n")
            f.write(pk.raw.hex() + "\n")


def load_lms_key(file: str):
    """Load LMS key
    LMS_TYPE [LMS_TYPE2]
    LMS_OTS_TYPE [LMS_OTS_TYPE2]
    <line of hex-encoded bytes of SK>
    <line of hex-encoded bytes of PK>

    @return (lmstypes[int], otstypes[int], sk, pk)
    """
    lmstypes, lmotstypes = [], []
    with open(file, 'r') as f:
        l1 = f.readline().strip().split()
        for ty in l1:
            lmstype = lmstype_from_str(ty)
            lmstypes.append(lmstype)
        l2 = f.readline().strip().split()
        for otsty in l2:
            lmotstype = lmotstype_from_str(otsty)
            lmotstypes.append(lmotstype)
        assert len(lmstypes) == len(lmotstypes)
        sk = bytes.fromhex(f.readline().strip())
        pk = bytes.fromhex(f.readline().strip())
    return (lmstypes, lmotstypes, sk, pk)


def save_lms_signature(sigfile: str, sig: bytes):
    """Save LMS/LMS-HSS signature to file """
    print('sig:', sig.raw.hex())
    if sigfile:
        with open(sigfile, 'w') as f:
            f.write(sig.raw.hex())


def load_lms_signature(sigfile: str):
    """Load LMS/LMS-HSS signature from file """
    with open(sigfile, 'r') as f:
        sig = bytes.fromhex(f.readline().strip())
    return sig


def main(args):
    lms = LMS()
    if args.command == 'test':
        assert test_lms(lms) == 0
        assert test_lms_hss(lms) == 0
        print('Tests OK')
    elif args.command == 'lms-keygen':
        print('LMS keygen lms:%s ots:%s' % (args.lmstype, args.lmotstype))
        assert len(args.lmstype) == 1, "Only one LMS type is allowed"
        assert len(args.lmotstype) == 1, "Only one LMOTS type is allowed"
        lmstype = lmstype_from_str(args.lmstype[0])
        lmotstype = lmotstype_from_str(args.lmotstype[0])
        seed = os.urandom(48)
        sk, pk = lms.keygen(seed, lmstype, lmotstype)
        save_lms_key(args.keyfile, [lmstype], [lmotstype], sk, pk)
    elif args.command == 'lms-sign':
        print('LMS sign key:%s msg:%s' % (args.keyfile, args.message))
        lmstypes, lmotstypes, sk, _pk = load_lms_key(args.keyfile)
        assert len(lmstypes) == len(lmotstypes) == 1
        msg = args.message.encode()
        sig = lms.sign(sk, msg, len(msg), lmstypes[0], lmotstypes[0])
        save_lms_signature(args.sigfile, sig)
    elif args.command == 'lms-verify':
        print('LMS verify key:%s sig:%s msg:%s' % (args.keyfile, args.sigfile, args.message))
        lmstypes, lmotstypes, _sk, pk = load_lms_key(args.keyfile)
        assert len(lmstypes) == len(lmotstypes) == 1
        print('lmstype:%s lmotstype:%s' % (lms_dic[lmstypes[0]], lmots_dic[lmotstypes[0]]))
        pk_ct = (c_char * len(pk)).from_buffer(bytearray(pk))
        sig = load_lms_signature(args.sigfile)
        sig_ct = (c_char * len(sig)).from_buffer(bytearray(sig))
        msg = args.message.encode()
        ret = lms.verify(sig_ct, msg, len(msg), pk_ct)
        if ret == 0: print("LMS verify OK")
        else: print("LMS verify failed")
    elif args.command == 'hss-keygen':
        print('HSS keygen lms:%s ots:%s' % (args.lmstype, args.lmotstype))
        assert len(args.lmstype) >= 2, "2 or more OTS types needed"
        assert len(args.lmotstype) >= 2, "2 or more LMOTS types needed"
        seed = os.urandom(48)
        lmstypes, lmotstypes = [], []
        for ty in args.lmstype:
            lmstype = lmstype_from_str(ty)
            lmstypes.append(lmstype)
        for otsty in args.lmotstype:
            lmotstype = lmotstype_from_str(otsty)
            lmotstypes.append(lmotstype)
        assert len(lmstypes) == len(lmotstypes) > 1
        sk, pk = lms.hss_keygen(seed, lmstypes, lmotstypes)
        save_lms_key(args.keyfile, lmstypes, lmotstypes, sk, pk)
    elif args.command == 'hss-sign':
        print('HSS sign key:%s msg:%s' % (args.keyfile, args.message))
        lmstypes, lmotstypes, sk, _pk = load_lms_key(args.keyfile)
        msg = args.message.encode()
        sig = lms.hss_sign(sk, msg, len(msg), lmstypes, lmotstypes)
        save_lms_signature(args.sigfile, sig)
    elif args.command == 'hss-verify':
        print('LMS verify key:%s sig:%s msg:%s' % (args.keyfile, args.sigfile, args.message))
        lmstypes, lmotstypes, _sk, pk = load_lms_key(args.keyfile)
        pk_ct = (c_char * len(pk)).from_buffer(bytearray(pk))
        sig = load_lms_signature(args.sigfile)
        sig_ct = (c_char * len(sig)).from_buffer(bytearray(sig))
        msg = args.message.encode()
        ret = lms.hss_verify(sig_ct, msg, len(msg), pk_ct)
        if ret == 0: print("HSS verify OK")
        else: print("HSS verify failed")
    else: raise ValueError("Unknown commad %s" % args.command)


def _lmotstypehelp():
    return """LM-OTS Signatures: LMOTS_SHA256_N32_W1, LMOTS_SHA256_N32_W2,
LMOTS_SHA256_N32_W4, LMOTS_SHA256_N32_W8"""

def _lmstypehelp():
    return """
Leighton Micali Signatures (LMS) Signatures:
LMS_SHA256_M32_H5, LMS_SHA256_M32_H10, LMS_SHA256_M32_H15, LMS_SHA256_M32_H20,
LMS_SHA256_M32_H25"""


DESCRIPTION = """
LMS commands : lms-keygen|lms-sign|lms-verify
HSS commands : hss-keygen|hss-sign|hss-verify
Test commands: test
"""

def _parse_args():
    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', type=str, help='command to run')
    parser.add_argument('--lmstype', nargs='*', type=str, help=_lmstypehelp())
    parser.add_argument('--lmotstype', nargs='*', type=str, help=_lmotstypehelp())
    parser.add_argument('--keyfile', type=str, help='key data file')
    parser.add_argument('--sigfile', type=str, help='signature data file')
    parser.add_argument('--message', type=str, help='message to sign')
    return parser.parse_args()

if __name__ == '__main__':
    exitval = 0
    try:
        main(_parse_args())
    except Exception as e:      # pylint: disable=broad-except
        print(e, file=sys.stderr)
        exitval = 2
    sys.exit(exitval)
