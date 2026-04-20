#!/usr/bin/env python3

# one day, merge all otp-manipulation functionality of this dir to
# a python3 tool

# the output of this particular code is used in CSDK

from sys import argv

lead1 = ('03 0d 01 20'                           # life cycle (mission)
         'ffffffff ffffffff ffffffff ffffffff'   # tdv
         '00 05 00 00'                           # status word
         '61 62 63 64 65 66 67 68 69 6a 6b 6c'   # device id
         '31 32 33 34 35 36 37 38'               # oem id
         '2d1e98bbf7187b01' '4a45a40e7b36548e'   # dgok
         'b155109330f1978c' 'bd984005720a112b')  # dgok (cont)

lead2 = ('03 0d 01 20'                           # life cycle (mission)
         'ffffffff ffffffff ffffffff ffffffff'   # tdv
         '00 05 00 00'                           # status word
         '00 00 00 00'                           # obliterate word
         '61 62 63 64 65 66 67 68 69 6a 6b 6c'   # device id
         '31 32 33 34 35 36 37 38'               # oem id
         '2d1e98bbf7187b01' '4a45a40e7b36548e'   # dgok (random in production)
         'b155109330f1978c' 'bd984005720a112b')  # dgok (cont)

lead3 = ('03 0d 01 20'                           # life cycle (mission)
         'ffffffff ffffffff ffffffff ffffffff'   # tdv
         '00 05 00 00'                           # status word
         '00 00 00 00'                           # obliterate word
         '00 05 00 00'                           # root valid word
         '00 00 00 00'                           # root obliterate word
         '61 62 63 64 65 66 67 68 69 6a 6b 6c'   # device id
         '31 32 33 34 35 36 37 38'               # oem id
         '2d1e98bbf7187b01' '4a45a40e7b36548e'   # dgok (random in production)
         'b155109330f1978c' 'bd984005720a112b')  # dgok (cont)

# keysplits (after dgok)
# same as default test PNAK
omc_keysplit0 = ('7F 20 03 48 7B 71 C0 4A  52 81 B1 41 D0 70 82 02'
                 'C8 45 10 89 95 33 9D 39  0D 44 E9 99 DC 7F F6 C2')

# roots (32 bytes root hash, 24 bytes permissions)
# pubkey of `prikey.pem` hashed, prefixed with type. see docs
pk_hash = ('84 F7 82 3C A4 D4 1C D6  69 28 66 DF 15 94 F2 88'
           'C2 4F 27 40 61 7F D9 EC  1A CF 4D EC 0B 53 F5 79')
pk_perm = ('00' * 24) # all permissions on, widest otp range


def main():
    if len(argv) != 4:
        raise SystemExit(
            f"Usage: {argv[0]} layout nr_of_keysplits otpfilename")
    layout = int(argv[1])
    if layout < 1 or layout > 3:
        raise SystemExit("Suspicious layout: %d" % layout)
    # nr_of_keysplits excluding DGOK
    keysplits = int(argv[2])
    if keysplits < 1 or keysplits > 7:
        raise SystemExit("Suspicious nr of keysplits: %d" % keysplits)
    #
    b = b''.fromhex(lead1 if layout == 1 else lead2 if layout == 2 else lead3)

    # insert keysplit0, used when hw keysplit not accessible
    b = b + b''.fromhex(omc_keysplit0)
    keysplits -= 1

    # insert zeroes for next keysplits
    b = b + bytes(keysplits * 0x20)

    # then add root0 pk_hash, and pk_perm...
    b = b + b''.fromhex(pk_hash + pk_perm)

    # and write it
    open(argv[3], 'wb').write(b)
    pass  # pylint: disable=W0107


if __name__ == '__main__':
    main()
    pass  # pylint: disable=W0107
