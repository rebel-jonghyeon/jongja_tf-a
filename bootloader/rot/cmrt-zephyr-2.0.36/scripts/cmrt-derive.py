#!/usr/bin/env python3
#
# Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Derive keys.  Match key derivation for KDC and OEC.
#
# Derive path of the OTP is the Hamming weight (bit count) of efuse,
# and works otherwise with the same logic.
# - syntax cmrt-derive.py {derive} [target] [diversify]
# - target is one of: sw, aes, hc, otp, or a number in the range
#   0..255
# Prints out the derived key as a hex-encoded string (64 hex
# characters, i.e. 32 bytes.)
#
# The device-key-spec file contains initial key data.  If this is file
# is not specified, a builtin default all zero value is used.  The
# same data can be supplied with the -k and -S arguments.

import hmac
import hashlib
import argparse
import sys
from os import access, R_OK


# Precalculated expansions for lookup of bit pairs
EXP2BA = (
    b'\x00' * 64, b'\x55' * 64, b'\xaa' * 64, b'\xff' * 64
)


def expand(inbytes: bytes) -> bytes:
    """Expand input bytes, two bits at a time.
    @return 64-byte expansion for each input byte
    """
    result = b''
    for byte in inbytes:
        result += EXP2BA[byte & 0x3]
        result += EXP2BA[(byte >> 2) & 0x3]
        result += EXP2BA[(byte >> 4) & 0x3]
        result += EXP2BA[(byte >> 6) & 0x3]
    return result


def _calc_derive_info(silo: bool, de_path: str, de_hwstate) -> bytes:
    """
    @param silo integer silo value (0 or 1, typically)
    @param de_path hex string derivation path
    @param de_hwstate a number, typically 0 (or 1), or None to leave
    unexpanded.
    """
    rval = b''
    # Applies the mask to the HW state byte if it's not None
    if de_hwstate is not None:
        rval = bytes([de_hwstate])
    rval += bytes.fromhex(de_path)
    if silo is not None:
        rval += bytes([silo, 0])
    return rval


def _calc_otp_info(version: bytes) -> bytes:
    """Calculate the word for encrypted OTP instead.
    @param version input fuses (version) as hex
    @return derivation data string to use
    """
    bitcount = sum(bin(x).count('1') for x in version)
    bitcount = bitcount % 256
    return expand(bitcount.to_bytes(1, 'little'))


def cmrt_hkdf(salt: bytes, key: bytes, info: bytes) -> bytes:
    prk = hmac.new(salt, key, hashlib.sha256).digest()
    key = hmac.new(prk, info, hashlib.sha256).digest()
    return key


def otpkey(ikm: bytes, dna: bytes, version: bytes) -> bytes:
    """Derive the key like OTP does.
    @param ikm original input key data (256 bits, 32 bytes) in big-endian
    @param dna fuse dna, (96 bits, 12 bytes), big-endian
    @version version fuses (160 bits)
    @return otp encryption key
    """
    return cmrt_hkdf(bytes(32), dna[::-1] + ikm[::-1],
                     _calc_otp_info(version))


class CmrtKdf:
    def __init__(self, silo: bool, ikm, salt, verbosity=0):
        self.silo = silo
        self.ikm = ikm
        self.salt = salt
        self.derived_key = None
        self.verbosity = verbosity

    def _hkdf(self, salt, ikm, path: str) -> bytes:
        """Use default salt and ikm here now to work, and add output
        according to selections.  The expanded path.. is really long.
        """
        r = cmrt_hkdf(salt, ikm or b'', expand(path))
        if self.verbosity > 0:
            # note the path is now "unexpanded here..."
            print("HKDF(salt=%r, ikm=%r, path=%r) = " %
                  (salt.hex(), (ikm or b'').hex(), path.hex()),
                  r.hex())
        if not self.derived_key:
            self.derived_key = r
        return r

    def hkdf(self, path: str) -> bytes:
        """Derive a raw key from the data.  Expands the input path
        (reversed)
        @param non-expanded input path
        @return the derived key (set if not set before)
        """
        r = self._hkdf(self.salt, self.ikm, path)
        if not self.derived_key:
            self.derived_key = r
        return r

    def derive(self, path: str, hwstate) -> bytes:
        """Derive the key.  The derivation will set the base key and
        affect further diversify() calls
        @param path derivation path, hex string
        @param silo boolean silo value
        @param hwstate hardware state to use
        @return bytes of derived key
        """
        self.derived_key = self._hkdf(
            self.salt,
            self.derived_key or self.ikm,
            _calc_derive_info(self.silo, path, hwstate))
        return self.derived_key

    def diversify(self, path: str) -> bytes:
        """Diversify the key.
        The input key will be either the key stored during the
        previous derive() call, or the initial input key given during
        the start.  The salt value is always the salt value given in
        the constructor.
        @param path hex string path
        @param destination key destination
        """
        return self._hkdf(self.salt, self.derived_key or self.ikm,
                          bytes.fromhex(path))


def load_kdf_params(devfile: str):
    """Load KDC device-specific parameters from a file.  The file is
    expected to be line-based ASCII format (the length will affect the
    result.)  The key data can be empty, which will cause an empty
    (all-zero) key to be returned.

    RKPF-1.0
    <line of hex-encoded bytes of input key data>
    <line of hex-encoded bytes of salt>

    @return (ikm, salt) byte arrays
    """
    salt = None
    key = None

    with open(devfile, 'r') as f:
        head = f.readline()
        if not head.startswith('RKPF-1.'):
            raise ValueError("%s: invalid file format" % devfile)
        key = bytes.fromhex(f.readline().strip())
        salt = bytes.fromhex(f.readline().strip())
    return (key, salt)


TARGETS = {
    'kreg': 0,                  # internal register not seen by sw
    'aes': 1,
    'hc': 2,
    'ktc': 16,                  # 16..31
    'sw': 255,                  # software buffer

    'otp': -1
}


def targetid(target: str) -> int:
    if target in TARGETS:
        return TARGETS[target]
    return int(target, 0)


def main(args):
    salt = bytes(32)
    ikm = bytes(32)
    if args.device:
        ikm, salt = load_kdf_params(args.device)
    if args.salt:
        salt = bytes.fromhex(args.salt)
    if args.key:
        ikm = bytes.fromhex(args.key)
    if args.target == TARGETS['otp']:
        # NOTE: the name/order of arguments is different now!
        # the version fuses are given as the derivation path
        key = cmrt_hkdf(salt, ikm,
                        _calc_otp_info(bytes.fromhex(args.derive)))
        # easier to read but does multiple ordering changes
        # key = otpkey(b'', salt[::-1], bytes.fromhex(args.derive))
    else:
        kdc = CmrtKdf(args.silo, ikm=ikm, salt=salt, verbosity=args.verbose)
        if args.derive:
            if args.derive != '-':
                if args.raw:
                    key = kdc.hkdf(bytes.fromhex(args.derive))
                else:
                    key = kdc.derive(args.derive, args.hwstate)
            else:
                key = ikm
        if args.diversify:
            divpath = args.diversify
            if not args.raw:
                divpath += "%02x" % args.target
            if len(divpath) > 34:
                raise ValueError("diversify path too long (%u)"
                                 % len(divpath), divpath)
            key = kdc.diversify(divpath)
    if args.reverse:
        key = key[::-1]
    if args.binary:
        sys.stdout.buffer.write(key)
    else:
        print(key.hex())
    return 0


def _targethelp():
    return "key target from: " + str(tuple(TARGETS.keys())) \
        + ", or a number in the range [0..255]"


def bytewbase(s: str) -> int:
    """Return an integer from a hex or decimal input string. single byte."""
    n = int(s, 0)
    if n < 0 or n > 255:
        raise ValueError(n)
    return n


def hexstr(s: str) -> str:
    """Return a validated hex string.  An empty one is allowed as well."""
    if len(s) > 0 and s != '-':
        _ = bytes.fromhex(s)    # let raise exception!
    return s


def ikmfile(s: str) -> str:
    """Check a file for access."""
    if not access(s, R_OK):
        raise ValueError(s)
    return s


DESCRIPTION = """Derive keys.

Derive keys with the same algorithm as used by the CMRT KDC.
The input parameters can be given as separate arguments, or
with a key parameter file.

The program can either;
- derive only (no diversify path is given)
- diversify only (- as input derivation path, ikm is directly
  assumed the input)
- derive, then diversify

To any target (given as either a symbolic name or a number 0..255).
"""

# should we have diversify and target the same?
def _parse_args():
    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('derive', help='derive path (hex) or -', type=hexstr)
    parser.add_argument('target', nargs='?', help=_targethelp(),
                        type=targetid)
    parser.add_argument('diversify', nargs='?', help='diversify path (hex)',
                        type=hexstr)
    parser.add_argument('--silo', '-s', action='store_true', default=False,
                        help='silo mode')
    # what's the hw state really?
    parser.add_argument('--raw', '-n', action='store_true', default=False,
                        help='use salt and hwstate directly as part of'
                        ' derive string no hwstate or silo is extracted')
    parser.add_argument('--salt', '-S', type=str,
                        help='salt material to derivation as hex string')
    parser.add_argument('-k', '--key', type=str,
                        help='input key material (IKM) as hex string')
    parser.add_argument('-H', '--hwstate', type=bytewbase,
                        help='hardware state to use')
    parser.add_argument('-D', '--device', type=ikmfile,
                        help='device key data info file')
    parser.add_argument('-R', '--reverse', action='store_true',
                        default=False,
                        help='reverse the key order of the result')
    parser.add_argument('-B', '--binary', action='store_true',
                        help='output key as binary')
    parser.add_argument('--verbose', '-v', action='count', default=0,
                        help='add extra debug output')
    return parser.parse_args()


if __name__ == '__main__':
    exitval = 0
    try:
        exitval = main(_parse_args())
    except Exception as e:      # pylint: disable=broad-except
        print(e, file=sys.stderr)
        exitval = 2
    sys.exit(exitval)
