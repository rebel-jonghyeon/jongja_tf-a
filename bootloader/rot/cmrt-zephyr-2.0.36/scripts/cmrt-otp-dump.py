#!/usr/bin/env python3
#
# Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

import sys
import os
from shutil import which
import json

assert sys.version_info >= (3,6)

# The layout is dumped from a spec in August 2019.
# It may vary in a different platform.
otplayout_v1 = (
    ("OTP_LIFE_CYCLE"  , 0, 4),
    ("OTP_TDV"         , 4, 16),
    ("OTP_STATUS_WORD" , 20, 4),
    ("OTP_DEV_ID"      , 24, 12),
    ("OTP_OEM_ID"      , 36, 8),
    ("OTP_DGOK"        , 44, 32))

otplayout_v2 = (
    ("OTP_LIFE_CYCLE"  , 0, 4),
    ("OTP_TDV"         , 4, 16),
    ("OTP_STATUS_WORD" , 20, 4),
    ("OTP_KEY_OB_WORD" , 24, 4),
    ("OTP_DEV_ID"      , 28, 12),
    ("OTP_OEM_ID"      , 40, 8),
    ("OTP_DGOK"        , 48, 32))

otplayout_v3 = (
    ("OTP_LIFE_CYCLE"   , 0, 4),
    ("OTP_TDV"          , 4, 16),
    ("OTP_STATUS_WORD"  , 20, 4),
    ("OTP_KEY_OB_WORD"  , 24, 4),
    ("OTP_ROOT_ST_WORD" , 28, 4),
    ("OTP_ROOT_OB_WORD" , 32, 4),
    ("OTP_DEV_ID"       , 36, 12),
    ("OTP_OEM_ID"       , 48, 8),
    ("OTP_DGOK"         , 56, 32))


# The following block shows how otp is laid out when there
# are 7 keysplits (8 - DGOK) and 8 roots. As the amounts
# vary, those offsets are calculated...
#    ("OTP_KEYSPLIT(0)"  , 80, 32),
#    ("OTP_KEYSPLIT(1)"  , 112, 32),
#    ("OTP_KEYSPLIT(2)"  , 144, 32),
#    ("OTP_KEYSPLIT(3)"  , 176, 32),
#    ("OTP_KEYSPLIT(4)"  , 208, 32),
#    ("OTP_KEYSPLIT(5)"  , 240, 32),
#    ("OTP_KEYSPLIT(6)"  , 272, 32),
#    ("OTP_ROOT_ID(0)"   , 304, 32),
#    ("OTP_ROOT_PERM(0)" , 336, 24),
#    ("OTP_ROOT_ID(1)"   , 360, 32),
#    ("OTP_ROOT_PERM(1)" , 392, 24),
#    ("OTP_ROOT_ID(2)"   , 416, 32),
#    ("OTP_ROOT_PERM(2)" , 448, 24),
#    ("OTP_ROOT_ID(3)"   , 472, 32),
#    ("OTP_ROOT_PERM(3)" , 504, 24),
#    ("OTP_ROOT_ID(4)"   , 528, 32),
#    ("OTP_ROOT_PERM(4)" , 560, 24),
#    ("OTP_ROOT_ID(5)"   , 584, 32),
#    ("OTP_ROOT_PERM(5)" , 616, 24),
#    ("OTP_ROOT_ID(6)"   , 640, 32),
#    ("OTP_ROOT_PERM(6)" , 672, 24),
#    ("OTP_ROOT_ID(7)"   , 696, 32),
#    ("OTP_ROOT_PERM(7)" , 728, 24))


try:
    path = which('cmrt-footer-dump.py')
    if path is not None:
        path = os.path.dirname(path)
    else:
        path = os.path.dirname(os.path.abspath( __file__ ))
    sys.path.append(path)
    fp = __import__('cmrt-footer-dump')
except ImportError as dep_no_exist:
    raise ImportError('Dependent program "cmrt-footer-dump.py" is not found'
                      ' from $PATH nor in \'%s\'.' % path) from dep_no_exist


def decode_otp_head(head, layout, keysplits, roots):
    next_offset = 0

    assert layout > 1
    otplayout = otplayout_v3 if layout == 3 else otplayout_v2

    for name, offset, length in otplayout:
        if offset != next_offset:
            raise SystemExit(f"Internal error: {offset} != {next_offset}")
        next_offset = offset + length
        slot = head[offset: next_offset].hex()
        name = f'{name.lower()}:'
        print(f'{offset:3} {name:17}  {slot}')
        pass

    offset = next_offset

    # the 2 loops below used to be part of the above loop, kinda works now...
    for n in range(keysplits):
        slot = head[offset: offset + 32].hex()
        print(f'{offset:3} OTP_KEYSPLIT({n}):   {slot}')
        # separated from loop above
        offset += 32
        pass
    if roots == 0:
        roots = 1
        zeroots = True
    else:
        zeroots = False
        pass

    for n in range(roots):
        slot = head[offset: offset + 32].hex()
        print(f'{offset:3} OTP_ROOT_ID({n}):    {slot}')
        offset += 32
        if slot == '00' * 32:
            print(
                f'{offset} permissions: suppressed for unprovisioned root {n}')
            offset += 24
            continue
        slot = bytearray(b ^ 0xff for b in head[offset: offset + 24])
        perms = fp.container_perms.from_buffer(slot)
        perms.sw_otp_perm[0] = perms.sw_otp_perm[0] ^ 0x7fff # restore range lo
        perms.sw_otp_perm[1] = perms.sw_otp_perm[1] ^ 0x7fff # ditto
        print(f'{offset:3}', end=' ')
        fp.decode_perms(perms)
        offset += 24
        pass

    if zeroots:
        print('\nOnly first root was printed. If you want to see more roots')
        print('or first bytes of esw_region (sboot) enter [roots] parameter.\n')
    else:
        if offset == len(head):
            print(f'{offset:3} EOF\n')
        else:
            slot = head[offset: offset + 16].hex(' ')
            print(f'{offset:3} first 16 esw bytes:  {slot}')
            offset += 16
            slot = head[offset: offset + 16].hex(' ')
            print(f'{offset:3}  next 16 esw bytes:  {slot}')
            pass
        pass
    pass


def otp_dump(layout, keysplits, roots, filename):
    desired_size = 44 + 32 + keysplits * 32 + roots * 56
    if layout >= 2:
        desired_size += 4
    if roots == 0: desired_size += 56
    desired_size += 32

    if filename in ('/dev/cmrt', '/dev/cmrt2'):
        fd = os.open(filename, os.O_RDONLY)
        data = os.pread(fd, desired_size, 0x30_0000)
        os.close(fd)
    else:
        data = open(filename, 'rb').read(desired_size)
        pass
    size = len(data)
    if size < desired_size:
        data = data + bytes(desired_size - size)
        pass
    decode_otp_head(data, layout, keysplits, roots)
    if size < desired_size:
        print(f'Note: since offset {size} with padded zero bytes.')
        pass
    print()
    pass


def main():
    if len(sys.argv) != 3:
        print(f'Usage:\n  {sys.argv[0]}'
              ' ({board.json} | {layout}:{keysplits}:{roots}) {otpmemfile}')
        print("  otpmemfile can be e.g. otpmem.bin, otp-lead or /dev/cmrt2\n")
        raise SystemExit(1)

    if os.path.exists(sys.argv[1]):
        cnf = json.load(open(sys.argv[1]))
        # add check...
        cores = cnf.get('cores')
        if cores is None:
            raise SystemExit(f'{sys.argv[1]} does not contain "cores"')
        for omc in cores:
            if omc.get('type', '') == 'omc': break
            pass
        else:
            raise SystemExit(f'{sys.argv[1]} does not contain "cores[omc]"')
        omc_features = omc.get('features')  #pylint: disable=W0631
        if omc_features is None:
            raise SystemExit(
                f'{sys.argv[1]} does not contain "cores[omc][features]"')
        try:
            # expect integers...
            layout = omc_features['layout_version']
            roots = omc_features['roots']
            keysplits = omc_features['keysplits']
        except KeyError as e:
            raise SystemExit(f'{sys.argv[1]} does not contain'
                             ' cores[omc][features][{e}]"') from e
        print(f"layout: {layout} roots: {roots} keysplits: {keysplits}")
        pass
    else:
        lkr = sys.argv[1].split(':')
        if len(lkr) != 3:
            raise SystemExit(f"'{sys.argv[1]}' does not exist, or it is not"
                             ' in format {layout}:{keysplits}:{roots}')
        layout = int(lkr[0])
        keysplits = int(lkr[1])
        roots = int(lkr[2])
        pass

    otp_dump(layout, keysplits, roots, sys.argv[2])
    pass


if __name__ == '__main__':
    main()
