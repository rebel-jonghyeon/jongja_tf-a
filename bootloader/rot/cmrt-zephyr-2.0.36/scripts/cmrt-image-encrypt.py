#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Encrypt CMRT images with AES GCM.
#

import sys
import os

from struct import pack
from binascii import hexlify

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

# https://cryptography.io/en/3.2/hazmat/primitives/symmetric-encryption/
def encrypt(key, plaintext, associated_data):
    # Generate a random 96-bit IV.
    iv = os.urandom(12)

    # Construct an AES-GCM Cipher object with the given key and a
    # randomly generated IV.
    encryptor = Cipher(
        algorithms.AES(key),
        modes.GCM(iv),
        default_backend()
    ).encryptor()

    # associated_data will be authenticated but not encrypted,
    # it must also be passed in on decryption.
    encryptor.authenticate_additional_data(associated_data)

    # Encrypt the plaintext and get the associated ciphertext.
    # GCM does not require padding.
    ciphertext = encryptor.update(plaintext) + encryptor.finalize()

    return (iv, ciphertext, encryptor.tag)

def encrypt_img(key, plaintext):
    return encrypt(key, plaintext, b'')

def get_values(key, keyid, divpath):
    if key.startswith('0x'):
        key = key[2:]
    key_bytes = bytes.fromhex(key)
    if len(key_bytes) != 32:
        print(f'Invalid key length {8*len(key_bytes)}b, only 256b supported')
        sys.exit(1)

    if main.verbose: print('Using key:', hexlify(key_bytes))

    if divpath.startswith('0x'):
        divpath = divpath[2:]
    diversify_path = bytes.fromhex(divpath)
    if len(diversify_path) != 4:
        print(f'Invalid diversify path {8*len(key_bytes)}b, only 32b supported')
        sys.exit(1)

    if main.verbose: print('Using diversify path:', hexlify(diversify_path))

    key_src = 0x00
    keysplit_id = 0x00
    keyid = keyid.lower()
    if keyid == 'ds':
        if main.verbose: print('Using static DS key')
        key_src = 0x00
        keysplit_id = 0x00
    elif keyid == 'dgok':
        if main.verbose: print('Using DGOK based key')
        key_src = 0x01
        keysplit_id = 0x00
    elif keyid == 'bnak':
        if main.verbose: print('Using BNAK based key')
        key_src = 0x01
        keysplit_id = 0x01
    elif keyid == 'snak':
        if main.verbose: print('Using SNAK based key')
        key_src = 0x01
        keysplit_id = 0x02
    elif keyid == 'pnak':
        if main.verbose: print('Using PNAK based key')
        key_src = 0x01
        keysplit_id = 0x03
    else:
        keysplit_id = int(keyid)
        if keysplit_id < 1 or keysplit_id > 7:
            print(f'Invalid keysplit id {keysplit_id}, only 1-7 supported')
        key_src = 0x01
        keysplit_id += 0x10
        if main.verbose: print(f'Using KEYSPLIT {keysplit_id} based key')

    return key_bytes, key_src, keysplit_id, diversify_path

def generate_ed(key_src, iv, tag, keysplit_id, diversify_path):
    encryption_data = pack('<L', 1) # version
    encryption_data += pack('<L', key_src)
    encryption_data += iv
    encryption_data += tag
    encryption_data += pack('<L', keysplit_id)
    encryption_data += diversify_path
    if main.verbose: print('Using iv:', hexlify(iv))
    if main.verbose: print('Using tag:', hexlify(tag))

    return encryption_data

def main():
    if len(sys.argv) > 1 and sys.argv[1] == '--verbose':
        main.verbose = True
        sys.argv.pop(1)
    else:
        main.verbose = False
        pass
    if len(sys.argv) != 7 or not os.path.isfile(sys.argv[4]):
        print(f'Usage: {sys.argv[0]} [--verbose] key keyid divpath plain.raw cipher.raw encdata')
        print('  key is the key data string in hex')
        print('  keyid defines the key source and keysplit')
        print('    ds = use key stored in the security monitor data store')
        print('    dgok = derive the key using DGOK')
        print('    bnak = derive the key using BNAK')
        print('    snak = derive the key using SNAK')
        print('    pnak = derive the key using PNAK')
        print('    1-7 = derive the key using given keysplit number')
        print('  divpath diversify path, four bytes in hex')
        print('  plain.raw is the raw plaintext CMRT image to encrypt')
        print('  cipher.raw is the resulting ciphertext CMRT image')
        print('  encdata is the structure for the footer tool')
        sys.exit(1)

    # Generate key and other values.
    key, key_src, keysplit_id, diversify_path = get_values(sys.argv[1], sys.argv[2], sys.argv[3])

    # Encrypt and write image file.
    plaintext = open(sys.argv[4], 'rb').read()
    iv, ciphertext, tag = encrypt_img(key, plaintext)
    with open(sys.argv[5], 'wb') as wf:
        wf.write(ciphertext)

    # Generate and write encryption data.
    encryption_data = generate_ed(key_src, iv, tag, keysplit_id, diversify_path)
    with open(sys.argv[6], 'wb') as wf:
        wf.write(encryption_data)

if __name__ == '__main__':
    main()
