#!/usr/bin/env python3
#
# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# xmss.py ...
#

import argparse
import os
import sys

from ctypes import CDLL, byref, c_char

# XMSS Signatures
# See Page 52 of RFC8391
XMSS_RESERVED     = 0
XMSS_SHA2_10_256  = 0x1
XMSS_SHA2_16_256  = 0x2
XMSS_SHA2_20_256  = 0x3
XMSS_SHA2_10_512  = 0x4
XMSS_SHA2_16_512  = 0x5
XMSS_SHA2_20_512  = 0x6
XMSS_SHAKE_10_256 = 0x7
XMSS_SHAKE_16_256 = 0x8
XMSS_SHAKE_20_256 = 0x9
XMSS_SHAKE_10_512 = 0xA
XMSS_SHAKE_16_512 = 0xB
XMSS_SHAKE_20_512 = 0xC

# XMSS^MT Signatures
# See Page 53 of RFC8391
XMSSMT_RESERVED         = 0
XMSSMT_SHA2_20_2_256    = 0x01
XMSSMT_SHA2_20_4_256    = 0x02
XMSSMT_SHA2_40_2_256    = 0x03
XMSSMT_SHA2_40_4_256    = 0x04
XMSSMT_SHA2_40_8_256    = 0x05
XMSSMT_SHA2_60_3_256    = 0x06
XMSSMT_SHA2_60_6_256    = 0x07
XMSSMT_SHA2_60_12_256   = 0x08
XMSSMT_SHA2_20_2_512    = 0x09
XMSSMT_SHA2_20_4_512    = 0x0A
XMSSMT_SHA2_40_2_512    = 0x0B
XMSSMT_SHA2_40_4_512    = 0x0C
XMSSMT_SHA2_40_8_512    = 0x0D
XMSSMT_SHA2_60_3_512    = 0x0E
XMSSMT_SHA2_60_6_512    = 0x0F
XMSSMT_SHA2_60_12_512   = 0x10
XMSSMT_SHAKE_20_2_256   = 0x11
XMSSMT_SHAKE_20_4_256   = 0x12
XMSSMT_SHAKE_40_2_256   = 0x13
XMSSMT_SHAKE_40_4_256   = 0x14
XMSSMT_SHAKE_40_8_256   = 0x15
XMSSMT_SHAKE_60_3_256   = 0x16
XMSSMT_SHAKE_60_6_256   = 0x17
XMSSMT_SHAKE_60_12_256  = 0x18
XMSSMT_SHAKE_20_2_512   = 0x19
XMSSMT_SHAKE_20_4_512   = 0x1A
XMSSMT_SHAKE_40_2_512   = 0x1B
XMSSMT_SHAKE_40_4_512   = 0x1C
XMSSMT_SHAKE_40_8_512   = 0x1D
XMSSMT_SHAKE_60_3_512   = 0x1E
XMSSMT_SHAKE_60_6_512   = 0x1F
XMSSMT_SHAKE_60_12_512  = 0x20

xmss_dic = { XMSS_SHA2_10_256  : "XMSS_SHA2_10_256",
             XMSS_SHA2_16_256  : "XMSS_SHA2_16_256",
             XMSS_SHA2_20_256  : "XMSS_SHA2_20_256",
             XMSS_SHA2_10_512  : "XMSS_SHA2_10_512",
             XMSS_SHA2_16_512  : "XMSS_SHA2_16_512",
             XMSS_SHA2_20_512  : "XMSS_SHA2_20_512",
             XMSS_SHAKE_10_256 : "XMSS_SHAKE_10_256",
             XMSS_SHAKE_16_256 : "XMSS_SHAKE_16_256",
             XMSS_SHAKE_20_256 : "XMSS_SHAKE_20_256",
             XMSS_SHAKE_10_512 : "XMSS_SHAKE_10_512",
             XMSS_SHAKE_16_512 : "XMSS_SHAKE_16_512",
             XMSS_SHAKE_20_512 : "XMSS_SHAKE_20_512"
           }

xmss_mt_dic = { XMSSMT_SHA2_20_2_256    : "XMSSMT_SHA2_20_2_256",
                XMSSMT_SHA2_20_4_256    : "XMSSMT_SHA2_20_4_256",
                XMSSMT_SHA2_40_2_256    : "XMSSMT_SHA2_40_2_256",
                XMSSMT_SHA2_40_4_256    : "XMSSMT_SHA2_40_4_256",
                XMSSMT_SHA2_40_8_256    : "XMSSMT_SHA2_40_8_256",
                XMSSMT_SHA2_60_3_256    : "XMSSMT_SHA2_60_3_256",
                XMSSMT_SHA2_60_6_256    : "XMSSMT_SHA2_60_6_256",
                XMSSMT_SHA2_60_12_256   : "XMSSMT_SHA2_60_12_256",
                XMSSMT_SHA2_20_2_512    : "XMSSMT_SHA2_20_2_512",
                XMSSMT_SHA2_20_4_512    : "XMSSMT_SHA2_20_4_512",
                XMSSMT_SHA2_40_2_512    : "XMSSMT_SHA2_40_2_512",
                XMSSMT_SHA2_40_4_512    : "XMSSMT_SHA2_40_4_512",
                XMSSMT_SHA2_40_8_512    : "XMSSMT_SHA2_40_8_512",
                XMSSMT_SHA2_60_3_512    : "XMSSMT_SHA2_60_3_512",
                XMSSMT_SHA2_60_6_512    : "XMSSMT_SHA2_60_6_512",
                XMSSMT_SHA2_60_12_512   : "XMSSMT_SHA2_60_12_512",
                XMSSMT_SHAKE_20_2_256   : "XMSSMT_SHAKE_20_2_256",
                XMSSMT_SHAKE_20_4_256   : "XMSSMT_SHAKE_20_4_256",
                XMSSMT_SHAKE_40_2_256   : "XMSSMT_SHAKE_40_2_256",
                XMSSMT_SHAKE_40_4_256   : "XMSSMT_SHAKE_40_4_256",
                XMSSMT_SHAKE_40_8_256   : "XMSSMT_SHAKE_40_8_256",
                XMSSMT_SHAKE_60_3_256   : "XMSSMT_SHAKE_60_3_256",
                XMSSMT_SHAKE_60_6_256   : "XMSSMT_SHAKE_60_6_256",
                XMSSMT_SHAKE_60_12_256  : "XMSSMT_SHAKE_60_12_256",
                XMSSMT_SHAKE_20_2_512   : "XMSSMT_SHAKE_20_2_512",
                XMSSMT_SHAKE_20_4_512   : "XMSSMT_SHAKE_20_4_512",
                XMSSMT_SHAKE_40_2_512   : "XMSSMT_SHAKE_40_2_512",
                XMSSMT_SHAKE_40_4_512   : "XMSSMT_SHAKE_40_4_512",
                XMSSMT_SHAKE_40_8_512   : "XMSSMT_SHAKE_40_8_512",
                XMSSMT_SHAKE_60_3_512   : "XMSSMT_SHAKE_60_3_512",
                XMSSMT_SHAKE_60_6_512   : "XMSSMT_SHAKE_60_6_512",
                XMSSMT_SHAKE_60_12_512  : "XMSSMT_SHAKE_60_12_512"
              }

class XMSS:
    """ wrapper of libxmss.so"""

    def __init__(self):
        self.xmss = CDLL('libxmss.so')

    def __del__(self):
        if hasattr(self, 'xmss'):
            del self.xmss

    def seed_len(self, ty):
        return self.xmss.py_xmss_seed_size(ty)

    def keygen(self, seed, ty):
        """ seed is immutable """
        pk = (c_char * self.xmss.py_xmss_pk_size(ty))()
        sk = (c_char * self.xmss.py_xmss_sk_size(ty))()
        ret = self.xmss.py_xmss_keygen(byref(sk), byref(pk), seed, ty)
        if ret: raise ValueError("py_xmss_keygen failed")
        return (sk, pk)

    def sig_size(self, ty):
        return self.xmss.py_xmss_sig_size(ty)

    def sign(self, sk, msg, mlen, ty):
        """ sk must be mutable """
        sig = (c_char * self.xmss.py_xmss_sig_size(ty))()
        sk_ct = (c_char * len(sk)).from_buffer(bytearray(sk))
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        ret = self.xmss.py_xmss_sign(byref(sig), byref(sk_ct), byref(msg_ct),mlen, ty)
        if ret: raise ValueError("py_xmss_sign failed")
        return sig

    def verify(self, sig, msg, mlen, pk):
        """ all params are immutable """
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        return self.xmss.py_xmss_verify(byref(sig), byref(msg_ct), mlen, byref(pk))

    def mt_seed_len(self, ty):
        return self.xmss.py_xmssmt_seed_size(ty)

    def mt_keygen(self, seed, ty):
        """ seed is immutable """
        pk = (c_char * self.xmss.py_xmssmt_pk_size(ty))()
        sk = (c_char * self.xmss.py_xmssmt_sk_size(ty))()
        ret = self.xmss.py_xmssmt_keygen(byref(sk), byref(pk), seed, ty)
        if ret: raise ValueError("py_xmssmt_keygen failed")
        return (sk, pk)

    def mt_sig_size(self, ty):
        return self.xmss.py_xmssmt_sig_size(ty)

    def mt_sign(self, sk, msg, mlen, ty):
        """ sk must be mutable """
        sig = (c_char * self.xmss.py_xmssmt_sig_size(ty))()
        sk_ct = (c_char * len(sk)).from_buffer(bytearray(sk))
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        ret = self.xmss.py_xmssmt_sign(byref(sig), byref(sk_ct), byref(msg_ct), mlen, ty)
        if ret: raise ValueError("py_xmssmt_sign failed")
        return sig

    def mt_verify(self, sig, msg, mlen, pk):
        """ all params are immutable """
        msg_ct = (c_char * mlen).from_buffer(bytearray(msg))
        return self.xmss.py_xmssmt_verify(byref(sig), byref(msg_ct), mlen, byref(pk))

    @staticmethod
    def xmss_type_to_str(xmss_type: int) -> str:
        return xmss_dic[xmss_type]

    @staticmethod
    def xmss_mt_type_to_str(xmss_mt_type: int) -> str:
        return xmss_mt_dic[xmss_mt_type]


def test_xmss(xmss):
    """ tests for xmss """
    n = 256
    ty = XMSS_SHA2_10_256

    # seed's length = n * 3, where n in {256, 512}
    seed = os.urandom(n * 3)
    sk, pk = xmss.keygen(seed, ty)
    msg = os.urandom(n)
    sig = xmss.sign(bytes(sk), msg, n, ty)
    ret = xmss.verify(sig, msg, n, pk)
    return ret


def test_xmss_mt(xmss):
    """ tests for xmss^mt """
    n = 256
    ty = XMSSMT_SHA2_20_2_256

    # seed's length = n * 3, where n in {256, 512}
    seed = os.urandom(n * 3)
    sk, pk = xmss.mt_keygen(seed, ty)
    msg = os.urandom(n)
    sig = xmss.mt_sign(bytes(sk), msg, n, ty)
    ret = xmss.mt_verify(sig, msg, n, pk)
    return ret


def xmss_type_from_str(name: str) -> int:
    """Convert XMSS type from name to id """
    for key, val in xmss_dic.items():
        if val == name:
            return key
    return XMSS_RESERVED


def xmss_mt_type_from_str(name: str) -> int:
    """Convert XMSS^MT type from name to id """
    for key, val in xmss_mt_dic.items():
        if val == name:
            return key
    return XMSSMT_RESERVED


def save_xmss_key(file: str, ty: int, sk: bytes, pk: bytes, mt: bool):
    """Save XMSS/XMSS^MT key key """
    type_str = xmss_mt_dic[ty] if mt else xmss_dic[ty]
    print(type_str)
    print('sk:', sk.raw.hex())
    print('pk:', pk.raw.hex())
    if file:
        with open(file, 'w') as f:
            f.write(type_str + "\n")
            f.write(sk.raw.hex() + "\n")
            f.write(pk.raw.hex() + "\n")


def load_xmss_key(file: str):
    """Load XMSS/XMSS^MT key
    XMSS_TYPE or XMSS_MT_TYPE
    <line of hex-encoded bytes of SK>
    <line of hex-encoded bytes of PK>

    @return (mt, xmsstype, sk, pk)
    """
    mt = False
    with open(file, 'r') as f:
        ty = f.readline().strip()
        xmsstype = xmss_type_from_str(ty)
        if xmsstype == XMSS_RESERVED:
            xmsstype = xmss_mt_type_from_str(ty)
            assert xmsstype != XMSSMT_RESERVED
            mt = True
        sk = bytes.fromhex(f.readline().strip())
        pk = bytes.fromhex(f.readline().strip())
    return (mt, xmsstype, sk, pk)


def save_xmss_signature(sigfile: str, sig: bytes):
    """Save XMSS/XMSS^MT signature to file """
    print('sig:', sig.raw.hex())
    if sigfile:
        with open(sigfile, 'w') as f:
            f.write(sig.raw.hex())


def load_xmss_signature(sigfile: str):
    """Load XMSS/XMSS^MT signature from file """
    with open(sigfile, 'r') as f:
        sig = bytes.fromhex(f.readline().strip())
    return sig


def main(args):
    xmss = XMSS()
    if args.command == 'test':
        assert test_xmss(xmss) == 0
        assert test_xmss_mt(xmss) == 0
        print('Tests OK')
    elif args.command == 'keygen':
        xmsstype = xmss_type_from_str(args.xmsstype)
        mt = False
        if xmsstype == XMSS_RESERVED:
            xmsstype = xmss_mt_type_from_str(args.xmsstype)
            assert xmsstype != XMSSMT_RESERVED
            mt = True
        if mt:
            print('XMSS^MT keygen type:%s' % (args.xmsstype))
            seed_len = xmss.mt_seed_len(xmsstype)
            seed = os.urandom(seed_len)
            sk, pk = xmss.mt_keygen(seed, xmsstype)
        else:
            print('XMSS keygen type:%s' % (args.xmsstype))
            seed_len = xmss.seed_len(xmsstype)
            seed = os.urandom(seed_len)
            sk, pk = xmss.keygen(seed, xmsstype)
        save_xmss_key(args.keyfile, xmsstype, sk, pk, mt)
    elif args.command == 'sign':
        print('XMSS sign key:%s msg:%s' % (args.keyfile, args.message))
        mt, xmsstype, sk, pk = load_xmss_key(args.keyfile)
        msg = args.message.encode()
        if mt:
            sig = xmss.mt_sign(sk, msg, len(msg), xmsstype)
        else:
            sig = xmss.sign(sk, msg, len(msg), xmsstype)
        save_xmss_signature(args.sigfile, sig)
    elif args.command == 'verify':
        print('verify key:%s sig:%s msg:%s' % (args.keyfile, args.sigfile, args.message))
        mt, xmsstype, sk, pk = load_xmss_key(args.keyfile)
        if mt:
            print('XMSS^MT type:%s' % (xmss_mt_dic[xmsstype]))
        else:
            print('XMSS type:%s' % (xmss_dic[xmsstype]))
        pk_ct = (c_char * len(pk)).from_buffer(bytearray(pk))
        sig = load_xmss_signature(args.sigfile)
        sig_ct = (c_char * len(sig)).from_buffer(bytearray(sig))
        msg = args.message.encode()
        if mt:
            ret = xmss.mt_verify(sig_ct, msg, len(msg), pk_ct)
        else:
            ret = xmss.verify(sig_ct, msg, len(msg), pk_ct)
        if ret == 0: print("Verify OK")
        else: print("Verify failed")
    else: raise ValueError("Unknown commad %s" % args.command)


def _xmsstypehelp():
    return """XMSS Signatures: XMSS_SHA2_10_256, XMSS_SHA2_16_256, XMSS_SHA2_20_256,
XMSS_SHA2_10_512, XMSS_SHA2_16_512, XMSS_SHA2_20_512, XMSS_SHAKE_10_256,
XMSS_SHAKE_16_256, XMSS_SHAKE_20_256, XMSS_SHAKE_10_512, XMSS_SHAKE_16_512,
XMSS_SHAKE_20_512

XMSS^MT Signatures: XMSSMT_SHA2_20_2_256, XMSSMT_SHA2_20_4_256, XMSSMT_SHA2_40_2_256,
XMSSMT_SHA2_40_4_256, XMSSMT_SHA2_40_8_256, XMSSMT_SHA2_60_3_256, XMSSMT_SHA2_60_6_256,
XMSSMT_SHA2_60_12_256, XMSSMT_SHA2_20_2_512, XMSSMT_SHA2_20_4_512,
XMSSMT_SHA2_40_2_512, XMSSMT_SHA2_40_4_512, XMSSMT_SHA2_40_8_512,
XMSSMT_SHA2_60_3_512, XMSSMT_SHA2_60_6_512, XMSSMT_SHA2_60_12_512,
XMSSMT_SHAKE_20_2_256, XMSSMT_SHAKE_20_4_256, XMSSMT_SHAKE_40_2_256,
XMSSMT_SHAKE_40_4_256, XMSSMT_SHAKE_40_8_256, XMSSMT_SHAKE_60_3_256,
XMSSMT_SHAKE_60_6_256, XMSSMT_SHAKE_60_12_256, XMSSMT_SHAKE_20_2_512,
XMSSMT_SHAKE_20_4_512, XMSSMT_SHAKE_40_2_512, XMSSMT_SHAKE_40_4_512,
XMSSMT_SHAKE_40_8_512, XMSSMT_SHAKE_60_3_512, XMSSMT_SHAKE_60_6_512,
XMSSMT_SHAKE_60_12_512"""


DESCRIPTION = """
XMSS commands    : keygen|sign|verify
Test commands: test
"""

def _parse_args():
    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', type=str, help='command to run')
    parser.add_argument('--xmsstype', type=str, help=_xmsstypehelp())
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
