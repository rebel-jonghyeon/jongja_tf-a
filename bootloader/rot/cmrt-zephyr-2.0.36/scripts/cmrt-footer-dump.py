#!/usr/bin/env python3
#
# Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

import sys
import ctypes

CMRT_FHDR_MAGIC = 0x43464832

class raw_image_footer(ctypes.Structure):
    _fields_ = ( ('text_start', ctypes.c_uint32),
                 ('text_end', ctypes.c_uint32),
                 ('rodata_start', ctypes.c_uint32),
                 ('rodata_end', ctypes.c_uint32),
                 ('bss_start', ctypes.c_uint32),
                 ('bss_end', ctypes.c_uint32),
                 ('noinit_start', ctypes.c_uint32),
                 ('noinit_end', ctypes.c_uint32),
                 ('data_start', ctypes.c_uint32),
                 ('data_end', ctypes.c_uint32),
                 ('entry_point', ctypes.c_uint32),
                 ('load_address', ctypes.c_uint32),
                 ('relocation_offset', ctypes.c_uint32),
                 ('verlen', ctypes.c_uint32) )

class raw_image_footer_user_ext(ctypes.Structure):
    _fields_ = ( ('stack_size', ctypes.c_uint32),
                 ('global_pointer', ctypes.c_uint32),
                 ('relocation_len', ctypes.c_uint32),
                 ('got_start', ctypes.c_uint32),
                 ('got_end', ctypes.c_uint32),
                 ('verlen', ctypes.c_uint32) )

class raw_image_footer_metadata_ext(ctypes.Structure):
    _fields_ = ( ('text_metadata', ctypes.c_uint32),
                 ('verlen', ctypes.c_uint32) )

class container_id(ctypes.Structure):
    _fields_ = ( ('pk_hash', ctypes.c_uint8 * 32),
                 ('handling_caveats', ctypes.c_uint32),
                 ('scid', ctypes.c_uint32) )

class container_perms(ctypes.Structure):
    _fields_ = ( ('slot_perm', ctypes.c_uint32),
                 ('key_perm', ctypes.c_uint32),
                 ('feature_perm', ctypes.c_uint32),
                 ('sw_otp_perm', ctypes.c_uint32 * 2),
                 ('software_perm', ctypes.c_uint32) )

class encryption_data(ctypes.Structure):
    _fields_ = ( ('version', ctypes.c_uint32),
                 ('key_src', ctypes.c_uint32),
                 ('iv', ctypes.c_uint8 * 12),
                 ('tag', ctypes.c_uint8 * 16),
                 ('keysplit_id', ctypes.c_uint32),
                 ('diversify_path', ctypes.c_uint8 * 4) )

def xu(v): return '%u (0x%x)' % (v, v)
def xub(b): v = int.from_bytes(b, 'little') ; return '%u (0x%x)' % (v, v)
def ub(b): return int.from_bytes(b, 'little')

def decode_raw_image(footer):
    def xd(v): return '0x%0x (+ %d)' % (v, v - footer.text_start)

    s = ctypes.sizeof(raw_image_footer)
    if footer.verlen != s:
        print("Raw footer length %u does not match expected raw footer size %u"
              % (footer.verlen, s))
        return

    print('RAW IMAGE FOOTER:')
    print('text_start:        ', xd(footer.text_start))
    print('text_end:          ', xd(footer.text_end))
    print('rodata_start:      ', xd(footer.rodata_start))
    print('rodata_end:        ', xd(footer.rodata_end))
    print('bss_start:         ', xd(footer.bss_start))
    print('bss_end:           ', xd(footer.bss_end))
    print('noinit_start:      ', xd(footer.noinit_start))
    print('noinit_end:        ', xd(footer.noinit_end))
    print('data_start:        ', xd(footer.data_start))
    print('data_end:          ', xd(footer.data_end))
    print('entry_point:       ', xd(footer.entry_point))
    print('load_address:      ', xd(footer.load_address))
    print('relocation_offset: ', xd(footer.relocation_offset))
    print('verlen:            ', xu(footer.verlen))
    print('')

def decode_raw_image_user_ext(data):
    footer = raw_image_footer_user_ext.from_buffer(bytearray(data[:24]))
    if footer.verlen != 24:
        return 0
    print('RAW IMAGE USER FOOTER:')
    print('stack size:         0x%x' % footer.stack_size)
    print('global_pointer:     0x%x' % footer.global_pointer)
    print('relocation_len:     0x%x' % footer.relocation_len)
    print('got_start:          0x%x' % footer.got_start)
    print('got_end:            0x%x' % footer.got_end)
    print('verlen:            ', xu(footer.verlen))
    print('')
    return footer.verlen

def decode_raw_image_metadata_ext(data):
    footer = raw_image_footer_metadata_ext.from_buffer(bytearray(data[:8]))
    if footer.verlen != 8:
        return 0
    print('RAW IMAGE METADATA FOOTER:')
    print('text_metadata:      0x%x' % footer.text_metadata)
    print('verlen:             %u' % xu(footer.verlen))
    print('')
    return footer.verlen


def decode_handling_caveats(handling_caveats):
    caveats = { 0: 'None',
                1: 'Silo',
                2: 'BOOT' }
    if handling_caveats in caveats:
        return caveats[handling_caveats]
    return 'Unknown'


def list_set_bits(bitvec, low, high, offset):
    bits = []
    for i in range(low, high):
        if bitvec & (1 << (offset + i)):
            bits.append(str(i))
    return bits


def decode_slot_perm(slot_perm):
    perm = []
    if slot_perm & 0xff000000:
        ro = list_set_bits(slot_perm, 0, 8, 24)
        perm.append('Root_Obliterate(' + ', '.join(ro) + ')')
    if slot_perm & 0x00ff0000:
        rc = list_set_bits(slot_perm, 0, 8, 16)
        perm.append('Root_Create(' + ', '.join(rc) + ')')
    if slot_perm & 0x0000ff00:
        ks = list_set_bits(slot_perm, 1, 8, 8)
        if slot_perm & 0x00000100:
            ks.append('DGOK')
        perm.append('Keysplits(' + ', '.join(ks) + ')')
    if slot_perm & 0x10:
        perm.append('Perso_Obliterate')
    if slot_perm & 0x8:
        perm.append('OEM_ID')
    if slot_perm & 0x4:
        perm.append('Device_ID')
    if slot_perm & 0x2:
        perm.append('TDV')
    if slot_perm & 0x1:
        perm.append('LC')
    return ', '.join(perm)


def decode_key_perm(key_perm):
    perm = []
    if key_perm & 0xffff0000:
        kd = list_set_bits(key_perm, 0, 16, 16)
        perm.append('Key_Destinations(' + ', '.join(kd) + ')')
    if key_perm & 0x0000fe00:
        ks = list_set_bits(key_perm, 1, 8, 8)
        perm.append('Keysplits(' + ', '.join(ks) + ')')
    if key_perm & 0x4:
        perm.append('PNAK')
    if key_perm & 0x2:
        perm.append('SNAK')
    if key_perm & 0x1:
        perm.append('BNAK')
    return ', '.join(perm)


def decode_sw_otp_perm(sw_otp_perm):

    r = 'R' if sw_otp_perm & 0x00008000 else ''
    w = 'W' if sw_otp_perm & 0x80000000 else ''
    if r or w:
        low = sw_otp_perm & 0x7fff
        high = (sw_otp_perm >> 16) & 0x7fff
        return '%s%s 0x%04x(0d%04d) - 0x%04x(0d%04d)' % (r, w, low, low, high, high)
    return ''


def decode_public_key_type(public_key_type):
    key_types = { 0: 'Unsigned',
                  1: 'ECDSA-NIST-P256',
                  2: 'HMAC-SHA256',
                  3: 'ECDSA-NIST-P521',
                  4: 'RSA-PSS-3K',
                  5: 'RSA-PSS-4K',
                  6: 'SHA256',
                  7: 'LMS',
                  8: 'LMS-HSS',
                  9: 'XMSS',
                  10: 'XMSS-MT',
                  11: 'ECDSA-NIST-P384'}
    if public_key_type in key_types:
        return key_types[public_key_type]
    return 'Unknown'

def sw_perms(sw_perm):
    debug_mode = "ON" if sw_perm & 0x80000000 else "OFF"
    return '{:08x} (DEBUG MODE: {}, SAC Page Access: {})' \
        .format(sw_perm, debug_mode, list_set_bits(sw_perm & 0xffff, 0, 16, 0))

def decode_perms(perms):
    print('permissions:')
    print('  slot_perm:        %08x (%s)' %
          (perms.slot_perm,
           decode_slot_perm(perms.slot_perm)))
    print('  key_perm:         %08x (%s)' %
          (perms.key_perm,
           decode_key_perm(perms.key_perm)))
    print('  feature_perm:     %08x (GPIO/Feature Slot Access: %s)' %
          (perms.feature_perm,
           list_set_bits(perms.feature_perm, 0, 32, 0)))
    print('  sw_otp_perm:      %08x (%s) %08x (%s)' %
          (perms.sw_otp_perm[0],
           decode_sw_otp_perm(perms.sw_otp_perm[0]),
           perms.sw_otp_perm[1],
           decode_sw_otp_perm(perms.sw_otp_perm[1])))
    print('  software_perm:    %s' % sw_perms(perms.software_perm))

def decode_encryption_data(ed):
    print('  version:          %02x' % ed.version)
    print('  key_src:          %02x' % ed.key_src)
    print('  iv:               %s' % bytes(ed.iv).hex())
    print('  tag:              %s' % bytes(ed.tag).hex())
    print('  keysplit_id:      %d' % ed.keysplit_id)
    print('  diversify_path:   %s' % bytes(ed.diversify_path).hex())


def decode_footer(footer):
    i = 0
    print('PERMISSION FOOTER:')
    print('metadata_length:   ', xub(footer[i:i + 4])) ; i += 4
    print('metadata_version:  ', ub(footer[i:i + 4])) ; i += 4

    print('container_id')
    cid = container_id.from_buffer(bytearray(footer[i:i + 40])) ; i += 40
    print('  pk_hash:          %s' % bytes(cid.pk_hash).hex())
    print('  handling_caveats: %u (%s)' %
          (cid.handling_caveats,
           decode_handling_caveats(cid.handling_caveats)))
    print('  scid:             %08x' % cid.scid)

    print('container_version:  %u' % ub(footer[i:i + 4])) ; i += 4
    s = ctypes.sizeof(container_perms)
    permissions = container_perms.from_buffer(bytearray(footer[i:i + s])) ; i += s
    decode_perms(permissions)

    encryption_length = ub(footer[i:i + 4]) ; i += 4

    print('encryption_length:  %u' % encryption_length)
    if encryption_length:
        enc_data = footer[i:i + encryption_length] ; i += encryption_length
        print('encryption_data:    %s' % bytes(footer[i:i + encryption_length]).hex())
        decode_encryption_data(encryption_data.from_buffer(bytearray(enc_data)))

    public_key_type = ub(footer[i:i + 4]) ; i += 4
    print('public_key_type:    %u (%s)' %
          (public_key_type, decode_public_key_type(public_key_type)))
    public_key_length = ub(footer[i:i + 4]) ; i += 4
    print('public_key_length:  %u' % public_key_length)
    print('public_key:         %s' % bytes(footer[i:i + public_key_length]).hex())
    i += public_key_length
    signature_length = ub(footer[i:i + 4]) ; i += 4
    print('signature_length:   %u' % signature_length)
    print('signature:          %s' % bytes(footer[i:i + signature_length]).hex())
    i += signature_length
    if signature_length & 3:
        i += 4 - signature_length & 3
    print('footer_length:      %u' % ub(footer[i:i + 4])) ; i += 4


def main():
    if len(sys.argv) != 2:
        print(f'usage: {sys.argv[0]} image')
        raise SystemExit(1)

    with open(sys.argv[1], 'rb') as f:
        img = f.read()

    # header validation
    img_len = len(img)
    flen = int.from_bytes(img[:4], 'little')
    flen2 = int.from_bytes(img[4:8], 'little')
    hlen = 0
    # A/B image header
    if flen == CMRT_FHDR_MAGIC:
        print("A/B image header detected")
        pri_o = int.from_bytes(img[8:11], 'little')
        hlen = 16
        if pri_o: flen += pri_o
        else: flen += hlen
    # legacy os.img: 4 bytes size, 4 bytes ~size and size bytes of image
    elif flen == 0xffffffff - flen2:
        print("header ~size check ok")
        hlen = 8
        if img_len != flen + hlen:
            print("invalid image length %u != header length %u", img_len, flen + 8)
            #raise SystemExit(1)
    else:
        print('Unknown header: %s' % bytes(img[:4]).hex())
        flen = img_len

    footer_len = int.from_bytes(img[-4:], 'little')
    if footer_len > img_len:
        print("probably sboot image")
        print('digest: %s' % bytes(img[img_len-32:]).hex())
        return
    footer_start = img_len - footer_len

    decode_raw_image_metadata_ext(img[footer_start-64:])

    decode_raw_image_user_ext(img[footer_start-60:])

    image_raw_len = ub(img[img_len-footer_len-4:img_len-footer_len])
    if image_raw_len == ctypes.sizeof(raw_image_footer):
        image_raw = bytearray(img[img_len-footer_len-image_raw_len:img_len-footer_len])
        decode_raw_image(raw_image_footer.from_buffer(image_raw))

    decode_footer(img[footer_start:])

    print('\nFile size:', flen, 'header length:', hlen, 'footers length:',
          footer_len, 'binary size:', flen - footer_len - 8)


if __name__ == '__main__':
    main()
