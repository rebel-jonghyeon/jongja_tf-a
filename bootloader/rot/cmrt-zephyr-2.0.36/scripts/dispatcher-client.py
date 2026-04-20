#!/usr/bin/env python3

# Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

import argparse
import sys

from ctypes import Structure, c_uint32, c_int32, c_uint8, c_char, Array, sizeof
from hashlib import sha1, sha224, sha256, sha384, sha512
from errno import errorcode, EBUSY
from os import strerror
from time import sleep

from random import choices
from cryptography.hazmat.primitives.asymmetric.rsa import \
    rsa_crt_iqmp, rsa_crt_dmp1, rsa_crt_dmq1, rsa_recover_prime_factors
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.exceptions import InvalidSignature
from cryptography.hazmat.primitives.asymmetric import utils

from cmrt_pm import CMRT_QUERY_CMD_PHYS_SYSCTL, R_SYSCTL_FMC_FEATURE_BITS


_timeout = 5000 # 5 seconds
verbose = False


# keep in sync with common.h
CMDID_BASE         = 0xa5415400
CMDID_LIST         = 0xa5415401
CMDID_ECHO         = 0xa5415402
CMDID_SHA2         = 0xa5415403
CMDID_ECDSA        = 0xa5415404
CMDID_AES          = 0xa5415405
CMDID_FLASH        = 0xa5415406
CMDID_SID          = 0xa5415407
CMDID_FFDH         = 0xa5415408
CMDID_RSA          = 0xa5415409
CMDID_UART         = 0xa541540a
CMDID_ECIES        = 0xa541540b
CMDID_OTP          = 0xa541540c
CMDID_ECDH         = 0xa541540d
CMDID_SHA3         = 0xa541540e
CMDID_RANDOM       = 0xa541540f
CMDID_RSA_KEY_EXCH = 0xa5415410
CMDID_HMAC         = 0xa5415411
CMDID_CCP          = 0xa5415412
CMDID_HSDH         = 0xa5415413
CMDID_KDC          = 0xa5415414
CMDID_FMC          = 0xa5415415
CMDID_SET_DEBUG    = 0xa5415416
CMDID_PERF         = 0xa5415417

ecdh_curve = {
    'NIST_P224': (0x00000002, 28),
    'NIST_P256': (0x00000003, 32),
    'NIST_P384': (0x00000004, 48),
    'NIST_P521': (0x00000005, 66),
    'X448': (0x80000011, 56),
    'X25519': (0x00000300, 32),
    'Bp_P192R1': (0x00000102, 24),
    'Bp_P224R1': (0x00000103, 28),
    'Bp_P256R1': (0x00000104, 32),
    'Bp_P320R1': (0x00000105, 40),
    'Bp_P384R1': (0x00000106, 48),
    'Bp_P512R1': (0x00000107, 64),
    'Bp_P192T1': (0x00000202, 24),
    'Bp_P224T1': (0x00000203, 28),
    'Bp_P256T1': (0x00000204, 32),
    'Bp_P320T1': (0x00000205, 40),
    'Bp_P384T1': (0x00000206, 48),
    'Bp_P512T1': (0x00000207, 64),
}

ecdsa_curve = {
    'NIST_P192': (0x00000001, 24),
    'NIST_P224': (0x00000002, 28),
    'NIST_P256': (0x00000003, 32),
    'NIST_P384': (0x00000004, 48),
    'NIST_P521': (0x00000005, 66),
    'Ed25519': (0x80000010, 32),
    'Ed448': (0x80000013, 57),
    'Bp_P192R1': (0x00000102, 24),
    'Bp_P224R1': (0x00000103, 28),
    'Bp_P256R1': (0x00000104, 32),
    'Bp_P320R1': (0x00000105, 40),
    'Bp_P384R1': (0x00000106, 48),
    'Bp_P512R1': (0x00000107, 64),
    'Bp_P192T1': (0x00000202, 24),
    'Bp_P224T1': (0x00000203, 28),
    'Bp_P256T1': (0x00000204, 32),
    'Bp_P320T1': (0x00000205, 40),
    'Bp_P384T1': (0x00000206, 48),
    'Bp_P512T1': (0x00000207, 64),
}

ecdsa_hash = {
    'SHA1': sha1,
    'SHA224': sha224,
    'SHA256': sha256,
    'SHA384': sha384,
    'SHA512': sha512
}

rsa_hash = {
    'SHA224': (sha224, 0x00000000),
    'SHA256': (sha256, 0x00000100),
    'SHA384': (sha384, 0x00000200),
    'SHA512': (sha512, 0x00000300)
}

aes_cipher = {
    'ECB': 0,
    'CBC': 1,
    'CFB': 2,
    'CTR': 3,
    'GCM': 4,
    'CCM': 5,
    'XTS': 6,
    'CMAC': 7}

cipher_op = {'ENCRYPT': 0, 'DECRYPT': 1}
ecdsa_mode = {'SIGN': 0, 'VERIFY': 1, 'KEYGEN': 2}
ecdh_mode = {'SECRET': 0, 'KEYGEN': 1}
ffdh_mod_size = ['1024', '2048', '3072', '4096']

class SicError(Exception):
    def __init__(self, rv, errno, message):
        super().__init__(message)
        self.return_value = rv
        self.errno = errno
        self.message = message

    def __str__(self):
        err_str = errorcode[self.errno] if self.errno > 0 else " "
        return "SicError: %s rv:%d errno:%s (%d)" % \
               (self.message, self.return_value, err_str, self.errno)


class memory_range_t(Structure):
    _fields_ = ( ("offset", c_uint32),
                 ("size", c_uint32),
                 ("used", c_uint32) )
    pass


class buffer_ctrl_t(Structure):
    _fields_ = ( ("to_esw", memory_range_t),
                 ("to_hlos", memory_range_t) )
    pass


class sic_cmd(Structure):
    _fields_ = ( ("cmd_id", c_uint32), )
    pass


def str_ctypes_obj(obj, *, pfx=None):
    txt = ""
    if pfx is None:
        pfx = "    "
        txt += "%s:\n" % obj.__class__.__name__
        pass

    if hasattr(obj, "_fields_"):
        for fname, _unused_ftype in obj._fields_: # pylint: disable=protected-access
            val = getattr(obj, fname)
            txt += str_ctypes_obj(val, pfx=pfx + "." + fname)
    elif isinstance(obj, Array):
        pad = pfx + " = "
        x = bytes(obj)
        while x:
            txt += "{}{} +\n".format(pad, x[:40].hex())
            x = x[40:]
            pad = " " * len(pad)
        txt = txt[:-3] + "\n"
    else:
        if isinstance(obj, int):
            if obj >= 10:
                obj = "%d = 0x%02x" % (obj, obj)
        elif obj is not None:
            h = ""
            for x in obj:
                h += "%s " % hex(x)
            obj = h
        txt += "{} = {}\n".format(pfx, obj)
    return txt

hdtt = b'................................' + \
       b' !"#$%&\'()*+,-./0123456789:;<=>?' + \
       b'@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_' + \
       b'`abcdefghijklmnopqrstuvwxyz{|}~.' + \
       b'.' * 128

def hexdump(data, address):
    while len(data) >= 16:
        d = data[0:16]
        print('%08x: ' % address, d[:8].hex(' '),'',d[8:].hex(' '), '',
              d.translate(hdtt).decode())
        data = data[16:]
        address += 16
        pass
    if len(data) > 8:
        l = 16 - len(data)
        d = data
        print('%08x: ' % address, d[:8].hex(' '),'',d[8:].hex(' '),'   ' * l,
              d.translate(hdtt).decode())
        return
    if len(data) > 0:
        l = 16 - len(data)
        print('%08x: ' % address, data.hex(' '), '', '   ' * l,
              data.translate(hdtt).decode())
        pass
    pass


def round_up(n, align):
    return ((n + align - 1) // align) * align


def sic_send_command(pm, cmd_id, timeout=None):
    if timeout is None: timeout = _timeout
    cmd = sic_cmd(cmd_id)
    cntr = 0
    while True:
        cntr += 1
        rv, errno, _ = pm.write_data(0, cmd)
        if rv <= 0:
            raise SicError(rv, errno, "Failed to send SIC command")

        rv, errno, _, data = pm.read_data(0, timeout=timeout)
        if rv < 0 and errno == EBUSY and cntr < 10:
            sleep(0.1)
            continue
        break

    if rv <= 0:
        raise SicError(rv, errno, "Failed to read SIC response")

    ret = c_int32.from_buffer(data).value
    if verbose:
        print("Command returned %d" % ret)
    if ret:
        print("Command %d failed %s (%s)" % (cmd_id & 0xff, ret, strerror(-ret)))
        raise RuntimeError(ret)

def read_sac(pm, offset, size):
    rv, errno, _ = pm.open_memory()
    if rv <= 0:
        raise SicError(rv, errno, "Failed to open memory")

    rv, errno, _, data = pm.read_memory(offset, size)
    if rv <= 0:
        pm.close_memory()
        raise SicError(rv, errno, "Failed to read memory")

    rv, errno, _ = pm.close_memory()
    if rv <= 0:
        raise SicError(rv, errno, "Failed to close memory")

    return data


def write_sac(pm, offset, data):
    rv, errno, _ = pm.open_memory()
    if rv <= 0:
        raise SicError(rv, errno, "Failed to open memory")

    rv, errno, data = pm.write_memory(offset, data)
    if rv <= 0:
        pm.close_memory()
        raise SicError(rv, errno, "Failed to write to memory")

    rv, errno, _ = pm.close_memory()
    if rv <= 0:
        raise SicError(rv, errno, "Failed to close memory")


def get_buffer_ctrl(pm):
    data = read_sac(pm, 0, sizeof(buffer_ctrl_t))
    ctrl = buffer_ctrl_t.from_buffer(data)
    if verbose:
        print(str_ctypes_obj(ctrl))
    return ctrl


def sac_send(pm, data):
    ctrl = get_buffer_ctrl(pm)
    write_sac(pm, ctrl.to_esw.offset, data)
    #hexdump(bytes(data), ctrl.to_esw.offset)
    ctrl.to_esw.used = sizeof(data)
    write_sac(pm, 0, ctrl)


def sac_receive(pm):
    ctrl = get_buffer_ctrl(pm)
    size = (ctrl.to_hlos.used + 3) & ~3
    data = read_sac(pm, ctrl.to_hlos.offset, size)
    ctrl.to_esw.used = 0
    if size != ctrl.to_hlos.used:
        data = (c_char * ctrl.to_hlos.used).from_buffer(data)
    return data


class sha_args(Structure):
    _fields_ = ( ("hc_id", c_uint32),
                 ("hash_size", c_uint32),
                 ("truncated", c_uint8),
                 ("sha3_shake", c_uint8),
                 ("size", c_uint32) )
    pass


class random_args(Structure):
    _fields_ = ( ("rsize", c_uint32), )
    pass

class ecdsa_args(Structure):
    _fields_ = ( ('mode', c_uint32),
                 ('curve', c_uint32),
                 ('algorithm', c_uint32),
                 ('key_len', c_uint32),
                 ('sig_len', c_uint32),
                 ('msg_len', c_uint32) )
    # continues as data[0]
    pass


class rsa_args(Structure):
    _fields_ = ( ('mode', c_uint32),
                 ('alg', c_uint32),
                 ('n_len', c_uint32),
                 ('e_len', c_uint32),
                 ('d_len', c_uint32),
                 ('salt_val_len', c_uint32),
                 ('s_len', c_uint32),
                 ('p_len', c_uint32),
                 ('q_len', c_uint32),
                 ('dp_len', c_uint32),
                 ('dq_len', c_uint32),
                 ('iq_len', c_uint32),
                 ('msg_len', c_uint32) )
    # continues as data[0]
    pass


class rsa_key_args(Structure):
    _fields_ = ( ('cmd', c_uint32), # always 0 for key loading
                 ('n_len', c_uint32),
                 ('e_len', c_uint32),
                 ('d_len', c_uint32),
                 ('p_len', c_uint32),
                 ('q_len', c_uint32),
                 ('dp_len', c_uint32),
                 ('dq_len', c_uint32),
                 ('iq_len', c_uint32) )
    # continues as data[0]


class rsa_key_exch_args(Structure):
    _fields_ = ( ('cmd', c_uint32), # always 1 for rsa key exchange
                 ('msg_len', c_uint32) )
    # continues as data[0]


class aes_args(Structure):
    _fields_ = ( ("algorithm", c_uint32),
                 ("encrypt", c_uint32),
                 ("key_len", c_uint32),
                 ("iv_len", c_uint32),
                 ("aad_len", c_uint32),
                 ("tag_len", c_uint32),
                 ("msg_len", c_uint32) )
    # continues as data[0]
    pass


class flash_args(Structure):
    _fields_ = ( ("cmd", c_uint32),
                 ("offs", c_uint32),
                 ("len", c_uint32) )
    pass


class fmc_args(Structure):
    _fields_ = ( ("cmd", c_uint32),
                 ("offs", c_uint32),
                 ("data", c_uint32),
                 ("mask", c_uint32), )
    pass


fmc_cmds = {
    "feature_set": 0,
    "feature_get" : 1,
    "feature_sys_out": 4,
}


class debug_args(Structure):
    _fields_ = ( ("mode", c_uint32), )
    pass

class uart_args(Structure):
    _fields_ = ( ("cmd", c_uint32),
                 ("baudrate", c_uint32),
                 ("parity", c_uint8),
                 ("stop_bits", c_uint8),
                 ("data_bits", c_uint8),
                 ("flow_ctrl", c_uint8) )
    pass

uart_cmds = {
    "set-config": 1,
    "set-default": 2,
    "enable": 3,
    "disable": 4,
    "get-config": 5,
}

uart_cfg_baudrate = {
    "9600"   : 9600,
    "38400"  : 38400,
    "115200" : 115200,
}

uart_cfg_parity = {
    "PARITY_NONE" : 0,
    "PARITY_ODD"  : 1,
    "PARITY_EVEN" : 2,
    "PARITY_MARK" : 3,
    "PARITY_SPACE": 4
}

uart_cfg_stop_bits = {
    "STOP_BITS_0_5" : 0,
    "STOP_BITS_1"   : 1,
    "STOP_BITS_1_5" : 2,
    "STOP_BITS_2"   : 3,
}

uart_cfg_data_bits = {
    "DATA_BITS_5" : 0,
    "DATA_BITS_6" : 1,
    "DATA_BITS_7" : 2,
    "DATA_BITS_8" : 3,
}

uart_cfg_flow_ctrl = {
    "FLOW_CTRL_NONE"   : 0,
    "FLOW_CTRL_RTS_CTS": 1,
    "FLOW_CTRL_DTR_DSR": 2,
}

class sid_args(Structure):
    _fields_ = ( ("subcmd", c_uint32),
                 ("irqs", c_uint32) )
    pass

class ecdh_args(Structure):
    _fields_ = ( ("mode", c_uint32),
                 ("curve", c_uint32),
                 ("curve_len", c_uint32) )
    # continues as data[0]
    pass

FFDH_MAX_LENGTH = 4096

def BITS2WORDS(n):
    return n // 32

ffdh_key_t = c_uint32 * BITS2WORDS(FFDH_MAX_LENGTH)

class ffdh_params_t(Structure):
    _fields_ = (
        ("size", c_uint32),
        ("P", ffdh_key_t),
        ("Q", ffdh_key_t),
        ("G", ffdh_key_t),
    )

class ffdh_args(Structure):
    _fields_ = (
        ("cmd", c_uint32),
        ("modsize", c_uint32),
        ("params", ffdh_params_t),
        ("key", ffdh_key_t),
    )

ffdh_cmds = {
    "reset": 0,
    "set_params": 1,
    "gen_params": 2,
    "set_peer_pub": 3,
    "gen_our_key": 4,
    "calc_shared": 5,
}


class ecies_args(Structure):
    _fields_ = (
        ("cmd", c_uint32),
        ("hc_id", c_uint32),
        ("mode", c_uint32),
        ("textlen", c_uint32),
        ("sharedinfolen", c_uint32),
        ("taglen", c_uint32),
        # continues as data[0]
    )

ecies_cmds = {
    "close": 0,
    "encrypt_init": 1,
    "encrypt_update": 2,
    "encrypt_final": 3,
    "decrypt_init": 4,
    "decrypt_update": 5,
    "decrypt_final": 6,
    "encrypt_final_si": 7,
    "decrypt_final_si": 8,
}

ecies_mode = {
    'P256_SHA256_AES128': (0, 32),
    'P384_SHA384_AES128': (1, 48),
    'P521_SHA512_AES256': (2, 66),
}

class otp_args(Structure):
    _fields_ = (
        ("cmd", c_uint32),
        ("arg0", c_uint32),
        ("arg1", c_uint32),
        ("len", c_uint32),
        # continues as data[0]
    )

otp_cmds = {
    "encrypt": 1,
    "write": 4,
}

class perf_args(Structure):
    _fields_ = (
        ("cmd", c_uint32),
        ("arg0", c_uint32),
        ("arg1", c_uint32),
        ("len", c_uint32),
        # continues as data[0]
    )

perf_cmds = {
    "status": 1,
    "reset": 2,
    "getdata": 4,
}

class hmac_args(Structure):
    _fields_ = (
        ("hash_func", c_uint32),
        ("hc_id", c_uint32),
        ("hash_size", c_uint32),
        ("truncated", c_uint8),
        ("key_len", c_uint32),
        ("data_len", c_uint32),
        # continues as data[0]
    )

class ccp_args(Structure):
    _fields_ = (
        ("op", c_uint32),
        ("mode", c_uint32),
        ("key_len", c_uint32),
        ("iv_len", c_uint32),
        ("aad_len", c_uint32),
        ("tag_len", c_uint32),
        ("msg_len", c_uint32),
        # continues as data[0]
    )

class hsdh_args(Structure):
    _fields_ = (
        ("cmd", c_uint32), # to ESW
        ("flowid", c_uint32), # to ESW
        ("state", c_uint32), # to HLOS
    )

hsdh_cmds = {
    "enable": 1,
    "disable": 2,
    "state": 3,
}


class kdc_args(Structure):
    _fields_ = (
        ("key", c_uint8),
        ("len", c_uint8),
        ("dest", c_uint8),
        ("_res0", c_uint8),
        # continues as data[0]
    )


def make_packet(struct, *args, blob=""):
    if isinstance(blob, str): blob = blob.encode()
    datalen = (len(blob) + 3) & ~3
    if not struct: # just blob of data
        packet = (c_char * datalen)()
        packet.value = blob
        return packet

    blob_field = [("data", c_uint8 * datalen)]
    class Packet(Structure):
        _fields_ = list(struct._fields_) + blob_field # pylint: disable=protected-access

    return Packet(*args, tuple(blob))


# -----------------------------------------------------------------------------

public_key = None
msg_digest = None

def init_rsa_key_exch(pm, args):
    if len(args) < 3:
        print("Usage: RSA_KEY_EXCH \\\n"
              "\tcrt calculation: ('CRT_ON', 'CRT_OFF') \\\n"
              "\t{path}/id_rsa.pem\n")
        print("NOTE: RSA private key can be generated with:\n"
              "      openssl genrsa -out ./id_rsa.pem 2048\n")
        print("NOTE: Set timeout 'dispatcher-client.py -t 40 ...'\n"
              "      when executing larger key size\n")
        raise SystemExit(1)

    crt = args[1]
    crt_modes = ('CRT_ON', 'CRT_OFF')
    if crt not in crt_modes:
        return False, "CRT calculation %s not in %r" % (crt, crt_modes)
    key_in = args[2]

    # import rsa private key from pem file and convert to binary format
    private_key = None
    with open(key_in, "rb") as key_file:
        private_key = serialization.load_pem_private_key(
            key_file.read(),
            password=None, backend=default_backend())

    global public_key, msg_digest
    public_key = private_key.public_key()
    n = public_key.public_numbers().n
    e = public_key.public_numbers().e
    d = private_key.private_numbers().d

    n = n.to_bytes(public_key.key_size // 8, byteorder='little')
    e = e.to_bytes(public_key.key_size // 8, byteorder='little')
    d = d.to_bytes(public_key.key_size // 8, byteorder='little')

    if crt == 'CRT_ON':
        p = private_key.private_numbers().p
        q = private_key.private_numbers().q
        dmp1 = private_key.private_numbers().dmp1
        dmq1 = private_key.private_numbers().dmq1
        iqmp = private_key.private_numbers().iqmp
        p = p.to_bytes(public_key.key_size // 8, byteorder='little')
        q = q.to_bytes(public_key.key_size // 8, byteorder='little')
        dmp1 = dmp1.to_bytes(public_key.key_size // 8, byteorder='little')
        dmq1 = dmq1.to_bytes(public_key.key_size // 8, byteorder='little')
        iqmp = iqmp.to_bytes(public_key.key_size // 8, byteorder='little')
    else:
        p = q = dmp1 = dmq1 = iqmp = 0

    # send key to cmrt and request public key back
    rsa_load_key_command(pm, n, e, d, p, q, dmp1, dmq1, iqmp)
    sic_send_command(pm, CMDID_RSA_KEY_EXCH)
    prefix, resp, _index = receive_hex_or_text_response(pm)
    print(prefix, resp)

    # NOTE: Instead of using private key directly, it is recommended
    # to run it trough key derivation function before using it. One example
    # can be found in here:
    # https://en.wikipedia.org/wiki/HKDF#Example:_Python_implementation

    expected_result = (n + e).hex()
    assert expected_result == resp, "public key did not match the private key"

    # create random
    # ascii digits + ascii uppercase chars + ascii lowercase chars
    random_msg = b'0123456789' + bytes(range(65, 91)) + bytes(range(97, 123))
    random_msg = bytes(choices(random_msg, k=10))
    print("Random message is: %r" % random_msg)
    # encrypt random with public key of cmrt
    resp = bytes.fromhex(resp)
    index = public_key.key_size // 8
    cmrt_pub_n = resp[:index]
    cmrt_pub_e = resp[index:]
    ciphertext = public_key.encrypt(random_msg,
                                    padding.OAEP(
                                        mgf=padding.MGF1(algorithm=hashes.SHA256()),
                                        algorithm=hashes.SHA256(),
                                        label=None))
    print("Encrypted random data:", ciphertext.hex())
    # hash random data and public key
    digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
    print("Hash in:", (random_msg + cmrt_pub_n + cmrt_pub_e).hex())
    digest.update(random_msg + cmrt_pub_n + cmrt_pub_e)
    msg_digest = digest.finalize()
    print("Hash out:", msg_digest.hex())
    # send encrypted random data to cmrt
    rsa_key_exch_command(pm, ciphertext)
    # typical execution times for different key sizes:
    # 2k rsa key 0,99 - 1,54 seconds
    # 4k rsa key 5,24 - 5,27 seconds
    # 8k rsa key 35,3 - 35,4 seconds
    sic_send_command(pm, CMDID_RSA_KEY_EXCH, 80000)
    return True, "Success"


def verify_rsa_signature(pm):
    prefix, resp, _index = receive_hex_or_text_response(pm)
    print(prefix, resp)
    # expect signed hash (=signature) in return
    try:
        #global public_key, msg_digest
        public_key.verify(bytes.fromhex(resp),
                          msg_digest,
                          padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                                      salt_length=64),
                          utils.Prehashed(hashes.SHA256()))
        print("Signature verified successfully")
        return 'Result:', 'PASS', -1
    except InvalidSignature:
        print("Signature of the shared hash does not match")
        return 'Result:', 'FAIL', -1


resplen = None

def echo_send_command(pm, args):
    if len(args) < 2:
        return False, "Usage: Echo 'message'\n"
    data = ' '.join(args[1:])
    global resplen
    resplen = len(data)
    data = make_packet(None, blob=data)
    sac_send(pm, data)
    return True, "Success"


def sha_send_command(pm, args, sha_family):
    sha_families = (2, 3)
    hc_ids = (1, 2)
    sha2_funcs = ('SHA224', 'SHA256', 'SHA384', 'SHA512', 'SHA512/224', 'SHA512/256')
    sha3_funcs = ('SHA3_224', 'SHA3_256', 'SHA3_384', 'SHA3_512', 'SHA3_SHAKE_128',
                  'SHA3_SHAKE_256')
    if sha_family not in sha_families:
        return False, ("Secure Hash Algorithm SHA-%d not in %r" %
                       (sha_family, sha_families))
    if sha_family == 2:
        hash_funcs = sha2_funcs
    else:
        hash_funcs = sha3_funcs
    if len(args) != 4:
        sp = 'SHA2 SHA256' if sha_family == 2 else 'SHA3 SHA3_256'
        return False, ("Usage: SHA%d \\\n" % (sha_family) +
                       "\thash_func: " + str(hash_funcs) + " \\\n"
                       "\thc_id: " + str(hc_ids) + " \\\n"
                       "\tdata: data to hash (plaintext or hex string)\n\n"
                       "Example:\n"
                       "  dispatcher-client.py " + sp + " 1 'Hash me please'"
                       "\n")
    hash_func = args[1]
    if hash_func not in hash_funcs:
        return False, "Hash function %s not in %r" % (hash_func, hash_funcs)
    hc_id = int(args[2])
    if hc_id not in hc_ids:
        return False, "Hash core id %d not in %r" % (hc_id, hc_ids)
    hash_size = int(hash_func[-3:])
    truncated = int('512/' in hash_func)
    sha3_shake = int('SHAKE' in hash_func)
    try:
        # User might be entering hex string or plaintext. Try hex string first:
        data = bytes.fromhex(args[3])
    except ValueError:
        data = ' '.join(args[3:])
    data = make_packet(sha_args, hc_id, hash_size, truncated, sha3_shake,
                       len(data), blob=data)
    sac_send(pm, data)
    return True, "Success"


def sha_receive_response(pm):
    data = sac_receive(pm)
    return "Hash:", bytes(data).hex(), -1


def sha2_send_command(pm, args):
    return sha_send_command(pm, args, 2)


def sha3_send_command(pm, args):
    return sha_send_command(pm, args, 3)


def ecdh_send_command(pm, args):
    if len(args) < 2:
        return False, "Usage: ECDH (SECRET|KEYGEN) ...\n"

    mode = ecdh_mode.get(args[1])
    if mode is None:
        print("Unknown ECDH operation. '%s' not 'SECRET' nor 'KEYGEN'\n" % args[1])
        raise SystemExit(1)

    if args[1] == 'SECRET':
        if len(args) != 5: usage_ecdh_shared_secret()
        pass
    else:
        if len(args) != 4: usage_ecdh_keygen()
        pass
    if args[2] not in ecdh_curve.keys():
        return False, ("curve: %s not in %r:"
                       % (args[2], tuple(k for k in ecdh_curve)))
    try:
        curve = ecdh_curve[args[2]][0]
    except KeyError as e:
        print("Supported curves:", tuple(k for k in ecdh_curve), "\n")
        raise SystemExit(1) from e

    curve_len = ecdh_curve[args[2]][1]

    data = ""
    for i in args[3:]:
        if len(i) > (curve_len * 2):
            print("Max key length is 2 * curve length")
            raise SystemExit(1)
        i = i.zfill(curve_len * 2)
        # add padding if size not divisible by eight (8) (serialized data align)
        data += i.ljust(round_up(len(i), 8), '0')
    try:
        data = bytes.fromhex(data)
    except ValueError:
        return False, "\nInput_error: Input must be in hex format"
    data = make_packet(ecdh_args, mode, curve, curve_len, blob=data)
    sac_send(pm, data)
    return True, "Success"


def usage_chacha_shared_secret():
    print("Usage: CCP {operation} CHACHA \\\n"
          "\toperation: " + str(tuple(cipher_op.keys())), "\\\n"
          "\tkey: big-endian hex-encoded string \\\n"
          "\tiv: big-endian hex-encoded string \\\n"
          "\taad: must be empty \\\n"
          "\ttag: must be empty \\\n"
          "\tdata: plaintext or hex string\n\n"
          "NOTE: aad and tag must be '' for CHACHA\n\n"
          "Example:\n"
          "  dispatcher-client.py CCP ENCRYPT CHACHA "
          "00112233445566778899aabbccddeeff "
          "beef '' '' ae\n"
          "  dispatcher-client.py CCP DECRYPT CHACHA "
          "00112233445566778899aabbccddeeff "
          "beef '' '' 80"
          "\n")
    raise SystemExit(1)


def usage_poly_shared_secret():
    print("Usage: CCP {operation} CHACHA \\\n"
          "\toperation: " + str(tuple(cipher_op.keys())), "\\\n"
          "\tkey: big-endian hex-encoded string \\\n"
          "\tiv: must be empty \\\n"
          "\taad: must be empty \\\n"
          "\ttag: must be empty \\\n"
          "\tdata: plaintext or hex string\n\n"
          "NOTE: iv, aad and tag must be '' for POLY\n"
          "NOTE: ONLY ENCRYPT supports for POLY\n\n"
          "Example:\n"
          "  dispatcher-client.py CCP ENCRYPT POLY "
          "00112233445566778899aabbccddeeff"
          "00112233445566778899aabbccddeeff "
          "'' '' '' poly-encrypt"
          "\n")
    raise SystemExit(1)


def usage_chacha_poly_shared_secret():
    print("Usage: CCP {operation} CHACHA \\\n" +
          "\toperation: " + str(tuple(cipher_op.keys())), "\\\n"
          "\tkey: big-endian hex-encoded string \\\n"
          "\tiv: big-endian hex-encoded string \\\n"
          "\taad: plaintext or hex string \\\n"
          "\ttag: big-endian hex-encoded string \\\n"
          "\tdata: plaintext or hex string\n\n"
          "NOTE: tag must be '' for CHACHAPOLY ENCRYPT\n"
          "NOTE: For DECRYPT, iv, aad must be same as that of ENCRYPT\n"
          "NOTE: When Encrypting, tag gets appended to the output, so "
          "for DECRYPT, extract the tag. Tag must be the last 32 hex of "
          "ENCRYPT output and rest of the value must be the input data\n\n"
          "Example:\n"
          "  dispatcher-client.py CCP ENCRYPT CHACHAPOLY "
          "00112233445566778899aabbccddeeff "
          "070000004041424344454647 "
          "31323334353637383961626364656630 '' ae\n"
          "  dispatcher-client.py CCP DECRYPT CHACHAPOLY "
          "00112233445566778899aabbccddeeff "
          "070000004041424344454647 "
          "31323334353637383961626364656630 "
          "3121043d277c25e95b7892aafbc4041d a0"
          "\n")
    raise SystemExit(1)


def usage_ecdh_shared_secret():
    print("Usage: ECDH SECRET \\\n" +
          "\tcurve:", tuple(k for k in ecdh_curve), "\\\n"
          "\tprivate key: big-endian hex-encoded string \\\n"
          "\tpeer public key: big-endian hex-encoded string\n\n"
          "NOTE: Max key length is 2 * curve length\n\n"
          "Example:\n"
          "  dispatcher-client.py ECDH SECRET NIST_P224 "
          "5f43068183586643e100472162e642ca8abfd995c1d62bf0c9af4475 "
          "a21642d03277d5cecc3bd6995e45a86cec2dc53067b1c5cb64ff3589\n")
    raise SystemExit(1)


def usage_ecdh_keygen():
    print("Usage: ECDH KEYGEN \\\n"
          "\tcurve:", tuple(k for k in ecdh_curve), "\\\n"
          "\tprivate key: big-endian hex-encoded string \\\n"
          "NOTE: Max key length is 2 * curve length\n\n"
          "Example:\n"
          "  dispatcher-client.py ECDH KEYGEN NIST_P224 "
          "5f43068183586643e100472162e642ca8abfd995c1d62bf0c9af4475\n")
    raise SystemExit(1)


def ecdsa_send_command(pm, args):
    if len(args) < 2:
        return False, "Usage: ECDSA (SIGN|VERIFY|KEYGEN) ...\n"

    priv_key_arg = 4
    keys = args[4:-1]
    mode = ecdsa_mode.get(args[1])
    if mode == ecdsa_mode['SIGN']:
        if len(args) != 6: usage_ecdsa_sign()
    elif mode == ecdsa_mode['VERIFY']:
        if len(args) != 9: usage_ecdsa_verify()
    elif mode == ecdsa_mode['KEYGEN']:
        if len(args) != 4: usage_ecdsa_keygen()
        priv_key_arg = 3
        keys = [args[priv_key_arg]]
    else:
        print("Unknown ECDSA mode: '%s' not in %r\n" %
              (args[1], tuple(k for k in ecdsa_mode)))
        raise SystemExit(1)

    curves = tuple(k for k in ecdsa_curve)
    if args[2] not in curves:
        return False, "Curve %s not in %r" % (args[2], curves)
    curve = ecdsa_curve[args[2]][0]
    curve_key_len = ecdsa_curve[args[2]][1]

    key_len = (len(args[priv_key_arg]) + 1) // 2
    sig_len = key_len
    msg_len = 0
    if mode == ecdsa_mode['VERIFY']:
        sig_len = (len(args[6]) + 1) // 2

    # truncate not necessary, rest of the msg is just not used by dispatcher
    #if msg_len > key_len:
    #    msg_hash = msg_hash[:key_len] # truncate msg to key len
    #    msg_len = key_len

    data = ""
    for i in keys:
        if i is None or i == '' and args[2] in ("Ed25519", "Ed448"):
            # Eddsa does not provide nor use pub_y, but one is required with proper length
            # Create a zero key that will be filled to proper length
            i = '0'
        elif i == '':
            return False, "Input can not be empty %s" % (args[2])
        # ensure even hexdigits (may add leading '0')
        i = i.zfill((len(i) + 1) & ~1)
        # if key/signature component lengt less than curve_key_len...
        i = i.zfill(curve_key_len * 2)
        # add padding if size not divisible by four (4) (serialized data align)
        data += i.ljust(round_up(len(i), 8), '0')

    if not mode == ecdsa_mode['KEYGEN']:
        msg = args[-1]
        eddsa_curve = curve in (ecdsa_curve['Ed25519'][0], ecdsa_curve['Ed448'][0])
        if not eddsa_curve:
            hash_algos = tuple(k for k in ecdsa_hash)
            if args[3] not in hash_algos:
                return False, "Hash algorithm %s not in %r" % (args[3], hash_algos)
            hash_func = ecdsa_hash[args[3]]
            try:
                # User might be entering hex string or plaintext. Try hex string first:
                msg = bytes.fromhex(msg)
            except ValueError:
                msg = msg.encode()

            msg_hash = hash_func(msg).hexdigest()
            msg_len = len(msg_hash) // 2
            data += msg_hash
        else:
            try:
                # confirm msg is hex, else ValueError
                int(msg, 16)
            except ValueError:
                msg = msg.encode().hex()
            # Even bytes required, odd number of hex will add leading '0'
            msg = msg.zfill((len(msg) + 1) & ~1)
            msg_len = len(msg) // 2
            data += msg
    try:
        # Try hex string first
        data = bytes.fromhex(data)
    except ValueError:
        return False, "\nInput_error: Input must be in hex format"
    data = make_packet(ecdsa_args, mode, curve, 0, key_len,
                       sig_len, msg_len, blob=data)
    sac_send(pm, data)
    return True, "Success"


def usage_ecdsa_sign():
    print("Usage: ECDSA SIGN \\\n"
          "\tcurve:", tuple(k for k in ecdsa_curve), "\\\n"
          "\thash algorithm:", tuple(k for k in ecdsa_hash), "\\\n"
          "\tprivate key: bignum in hex format \\\n"
          "\tmsg: plaintext or hex string\n\n"
          "Examples:\n"
          "  dispatcher-client.py ECDSA SIGN NIST_P256 SHA256 "
          "16260783e40b16731673622ac8a5b045fc3ea4af70f727f3f9e92bdd3a1ddc42 "
          "'Sign me please'\n"
          "For EdDSA the hash algorithm must be left empty:\n"
          "  dispatcher-client.py ECDSA SIGN Ed25519 '' "
          "16260783e40b16731673622ac8a5b045fc3ea4af70f727f3f9e92bdd3a1ddc42 "
          "'Sign me please'\n")
    raise SystemExit(1)


def usage_aes_ecb():
    print("Examples:\n"
          "  dispatcher-client.py AES ECB ENCRYPT "
          "2b7e151628aed2a6abf7158809cf4f3c '' '' 0 "
          "3243f6a8885a308d313198a2e0370734\n"
          "  dispatcher-client.py AES ECB DECRYPT "
          "2b7e151628aed2a6abf7158809cf4f3c '' '' '' "
          "3925841d02dc09fbdc118597196a0b32\n")
    raise SystemExit(1)


def usage_aes_cbc():
    print("Examples:\n"
          "  dispatcher-client.py AES CBC ENCRYPT "
          "3b7e151628aed2a6abf7158809cf4f3c '' '' 0 "
          "3243f6a8885a308d313198a2e0370734\n"
          "  dispatcher-client.py AES CBC DECRYPT "
          "3b7e151628aed2a6abf7158809cf4f3c '' '' '' "
          "2fdbe27b054a02ccfac28f8239491cc5\n")
    raise SystemExit(1)


def usage_aes_cfb():
    print("Examples:\n"
          "  dispatcher-client.py AES CFB ENCRYPT "
          "4b7e151628aed2a6abf7158809cf4f3c "
          "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff '' 0 "
          "3243f6a8885a308d313198a2e0370734\n"
          "  dispatcher-client.py AES CFB DECRYPT "
          "4b7e151628aed2a6abf7158809cf4f3c "
          "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff '' '' "
          "ea1f2eae63afa3476e4dff7ec6f11a01\n")
    raise SystemExit(1)


def usage_aes_ctr():
    print("Examples:\n"
          "  dispatcher-client.py AES CTR ENCRYPT "
          "5b7e151628aed2a6abf7158809cf4f3c "
          "a0f1f2f3f4f5f6f7f8f9fafbfcfdfeff '' 0 "
          "3243f6a8885a308d313198a2e0370734\n"
          "  dispatcher-client.py AES CTR DECRYPT "
          "5b7e151628aed2a6abf7158809cf4f3c "
          "a0f1f2f3f4f5f6f7f8f9fafbfcfdfeff '' '' "
          "ee0109364ecab4cdd39f993e0bc2ea06\n")
    raise SystemExit(1)


def usage_aes_gcm():
    print("Examples:\n"
          "  dispatcher-client.py AES GCM ENCRYPT "
          "e2f483989b349efb59ae0a7cadc74b7a "
          "3338343f9b97ebb784e75027 '' 128 "
          "14d80ad66e8f5f2e6c43c3109e023a93\n"
          "  dispatcher-client.py AES GCM DECRYPT "
          "e2f483989b349efb59ae0a7cadc74b7a "
          "3338343f9b97ebb784e75027 '' "
          "93a904915c6c5735e30839e025fb9c4d "
          "43c2d68384d486e9788950bbb8cd8fd1\n")
    raise SystemExit(1)


def usage_aes_ccm():
    print("Examples:\n"
          "  dispatcher-client.py AES CCM ENCRYPT "
          "9a57a22c7f26feff8ca6cceff214e4c2 "
          "88f30fd2b04fb8ddbce8fc26e6 "
          "a95bdff6 128 "
          "035c516776c706a7dd5f181fa6aa891b04dd423042ea0667\n"
          "  dispatcher-client.py AES CCM DECRYPT "
          "9a57a22c7f26feff8ca6cceff214e4c2 "
          "88f30fd2b04fb8ddbce8fc26e6 a95bdff6 "
          "9b6443a35f329b2068916fb6ab8227eb "
          "b92f7ec2ebecebdbd2977b3874e61bf496a382153b2529fc\n")
    raise SystemExit(1)

def usage_aes_xts():
    print("Examples:\n"
          "  dispatcher-client.py AES XTS ENCRYPT "
          "a1b90cba3f06ac353b2c343876081762090923026e91771815f29dab01932f2f "
          "4faef7117cda59c66e4b92013e768ad5 '' 0 "
          "ebabce95b14d3c8d6fb350390790311c\n"
          "  dispatcher-client.py AES XTS DECRYPT "
          "a1b90cba3f06ac353b2c343876081762090923026e91771815f29dab01932f2f "
          "4faef7117cda59c66e4b92013e768ad5 '' '' "
          "778ae8b43cb98d5a825081d5be471c63\n")
    raise SystemExit(1)


def usage_aes_cmac():
    print("Example:\n"
          "  dispatcher-client.py AES CMAC ENCRYPT "
          "2b7e151628aed2a6abf7158809cf4f3c "
          "'' 6bc1bee22e409f96e93d7e117393172a 128 ''\n")
    raise SystemExit(1)


def usage_ecdsa_verify():
    print("Usage: ECDSA VERIFY \\\n"
          "\tcurve:", tuple(k for k in ecdsa_curve), "\\\n"
          "\thash algorithm:", tuple(k for k in ecdsa_hash), "\\\n"
          "\tpublic key x: bignum in hex format \\\n"
          "\tpublic key y: bignum in hex format \\\n"
          "\tsignature r: bignum in hex format \\\n"
          "\tsignature s: bignum in hex format \\\n"
          "\tmsg: plaintext or hex string\n\n"
          "Examples:\n"
          "  dispatcher-client.py ECDSA VERIFY NIST_P256 SHA256 "
          "e424dc61d4bb3cb7ef4344a7f8957a0c5134e16f7a67c074f82e6e12f49abf3c "
          "970eed7aa2bc48651545949de1dddaf0127e5965ac85d1243d6f60e7dfaee927 "
          "bf96b99aa49c705c910be33142017c642ff540c76349b9dab72f981fd9347f4f "
          "17c55095819089c2e03b9cd415abdf12444e323075d98f31920b9e0f57ec871c "
          "e1130af6a38ccb412a9c8d13e15dbfc9e69a16385af3c3f1e5da954fd5e7c45f"
          "d75e2b8c36699228e92840c0562fbf3772f07e17f1add56588dd45f7450e1217"
          "ad239922dd9c32695dc71ff2424ca0dec1321aa47064a044b7fe3c2b97d03ce4"
          "70a592304c5ef21eed9f93da56bb232d1eeb0035f9bf0dfafdcc4606272b20a3\n\n"
          "For EdDSA the hash algorithm and pub_y must be left empty:\n"
          "  dispatcher-client.py ECDSA VERIFY Ed25519 '' "
          "10699e499be99e2b11b98f6f86b67cdc4ccf69f3c53ce094875647d2d0d0ecc5"
          " '' "
          "4c2d31d5bbc42e026dc1e079ecc4dd072c5d2cce65e3db8d8a1dd9057faa0371 "
          "727f727231a0f060fa27097533b6db3b8f6252f2793d75662caadf5f0fcc710e "
          "9fc4d28cfd25e6c0c5e724e19ca39d71e53bf4aa2796c54c3351f108fc70f261"
          "1a62e0ab90af6ade5216788e9eb2a873059b1e79d7d59debd68f2d4d80ffe31b"
          "f74b928c\n")
    raise SystemExit(1)


def usage_ecdsa_keygen():
    print("Usage: ECDSA KEYGEN \\\n"
          "\tcurve:", tuple(k for k in ecdsa_curve), "\\\n"
          "\tprivate key: bignum in hex format\n\n"
          "Examples:\n"
          "  dispatcher-client.py ECDSA KEYGEN NIST_P256 "
          "16260783e40b16731673622ac8a5b045fc3ea4af70f727f3f9e92bdd3a1ddc42\n"
          "  dispatcher-client.py ECDSA KEYGEN Ed25519 "
          "16260783e40b16731673622ac8a5b045fc3ea4af70f727f3f9e92bdd3a1ddc42\n")
    raise SystemExit(1)


def rsa_send_command(pm, args):
    if len(args) < 2:
        print("Usage: RSA (SIGN|VERIFY) ...\n")
        raise SystemExit(1)

    mode = ecdsa_mode.get(args[1])
    if mode is None:
        print("Unknown RSA operation. '%s' not 'SIGN' nor 'VERIFY'\n" % args[1])
        raise SystemExit(1)

    if args[1] == 'SIGN':
        if len(args) != 9: usage_rsa_sign()
        pass
    else:
        if len(args) != 9: usage_rsa_verify()
        pass

    hash_algos = tuple(k for k in rsa_hash)
    if args[2] not in hash_algos:
        return False, "Hash algorithm %s not in %r" % (args[2], hash_algos)
    hash_func = rsa_hash[args[2]][0]
    alg = rsa_hash[args[2]][1]

    try:
        # User might be entering hex string or plaintext. Try hex string first:
        data = bytes.fromhex(args[-1])
    except ValueError:
        data = args[-1].encode()

    msg_hash = hash_func(data).hexdigest()
    msg_len = (len(msg_hash) + 1) // 2

    if args[1] == 'SIGN':
        crt = args[3]
        crt_modes = ('CRT_ON', 'CRT_OFF')
        if crt not in crt_modes:
            return False, "CRT calculation %s not in %r" % (crt, crt_modes)
        offset = 3
    else:
        crt = 'CRT_OFF'
        offset = 2

    n = args[offset + 1]
    e = args[offset + 2]
    d = args[offset + 3]
    salt_val = args[offset + 4]
    s = args[offset + 5]

    n_len = (len(n) + 1) // 2
    e_len = (len(e) + 1) // 2
    d_len = (len(d) + 1) // 2
    salt_val_len = (len(salt_val) + 1) // 2
    s_len = (len(s) + 1) // 2 if args[1] == 'VERIFY' else 0

    if crt == 'CRT_ON':
        try:
            p, q = rsa_recover_prime_factors(int(n, 16), int(e, 16), int(d, 16))
        except ValueError:
            return False, "\nInput_error: Input must be in hex format"
        p = format(p, 'x')
        q = format(q, 'x')
        dmp1 = format(rsa_crt_dmp1(int(d, 16), int(p, 16)), 'x')
        dmq1 = format(rsa_crt_dmq1(int(d, 16), int(q, 16)), 'x')
        iqmp = format(rsa_crt_iqmp(int(p, 16), int(q, 16)), 'x')
        crt_data = [p, q, dmp1, dmq1, iqmp]
        p_len = (len(crt_data[0]) + 1) // 2
        q_len = (len(crt_data[1]) + 1) // 2
        dp_len = (len(crt_data[2]) + 1) // 2
        dq_len = (len(crt_data[3]) + 1) // 2
        iq_len = (len(crt_data[4]) + 1) // 2
    else:
        crt_data = []
        dp_len = dq_len = iq_len = p_len = q_len = 0

    data = ""
    for i in list(args[offset + 1:-1]) + crt_data:
        # add padding if size not divisible by four (4) (serialized data align)
        data += i.ljust(round_up(len(i), 8), '0')

    data += msg_hash
    try:
        data = bytes.fromhex(data)
    except ValueError:
        return False, "\nInput_error: Input must be in hex format"
    data = make_packet(rsa_args, mode, alg, n_len, e_len, d_len, salt_val_len,
                       s_len, p_len, q_len, dp_len, dq_len, iq_len, msg_len,
                       blob=data)
    sac_send(pm, data)
    return True, "Success"


def rsa_key_exch_command(pm, msg):
    # add padding if msg size not divisible by four (4) (serialized data align)
    data = msg.ljust(round_up(len(msg), 4), b'\0')
    data = make_packet(rsa_key_exch_args, 1, len(msg), blob=data)
    sac_send(pm, data)
    return True, "Success"


def rsa_load_key_command(pm, n, e, d, p, q, dmp1, dmq1, iqmp):
    n_len = len(n)
    e_len = len(e)
    d_len = len(d)
    if isinstance(p, int):
        p_len = q_len = dp_len = dq_len = iq_len = 0
        data = n + e + d
    else:
        p_len = len(p)
        q_len = len(q)
        dp_len = len(dmp1)
        dq_len = len(dmq1)
        iq_len = len(iqmp)
        data = n + e + d + p + q + dmp1 + dmq1 + iqmp
    data = make_packet(rsa_key_args, 0, n_len, e_len, d_len,
                       p_len, q_len, dp_len, dq_len, iq_len, blob=data)
    sac_send(pm, data)
    return True, "Success"

def usage_ffdh_set_params():
    print("Usage: FFDH set_params {modsize} from modsize:%r \\\n" %
          ffdh_mod_size +
          "\tModulus P: hex string \\\n"
          "\tGroup Size Q: hex string \\\n"
          "\tGenerator G: hex string\n\n"
          "Examples:\n"
          "  dispatcher-client.py FFDH reset\n"
          "  dispatcher-client.py -t 40 FFDH gen_params 1024\n"
          "  dispatcher-client.py FFDH reset\n"
          "  dispatcher-client.py -t 40 FFDH set_params 1024 "
          "ab65686682e5c3c6f8fd80f17ba03041cd42fa6c"
          "60c90023f035cf25bc6ad4cf9f534620a78bbfa4"
          "2a59a1521b6030433449fc40f32244dcc9bfea64"
          "ea0ebd1e1a4a56efecc97719b781d069b3b441a"
          "03889608250552b531c5d259adb85c285b1c9f5d"
          "560418db2f4efc3caf9eabd09fad3ae5c40dc5fa"
          "7079c17c37046ffc7 "
          "e997c56908301807b1be1b1a7a75192177e4e09"
          "53850ec1430f3bacc69d54e07 "
          "92f4d2c22528bf78c7d73f659ce7c30e47ac7f5fc1"
          "2a5ea4c2c97dcd1eabd3263ae4e9d0c5553dc041cf"
          "89f2018093341528babb39f2e123513105082762a5"
          "bce8927f102812bc3fe191d0f8a56bbcba0b828683"
          "c7fe3c9dd09cb8cd247866bb7a38159dc115bd8fd3"
          "a9f91fe487fc0f70a4e165603d8c141957a12a71ebe7d2\n"
          "NOTE: Set timeout 'dispatcher-client.py -t 40 ...' "
          "when executing larger key size\n"
          "NOTE: Execute 'dispatcher-client.py FFDH reset' before "
          "executing 'dispatcher-client.py -t 40 FFDH gen_params' or "
          "'dispatcher-client.py -t 40 FFDH set_params' command"
          "\n")
    raise SystemExit(1)

def usage_ffdh_gen_params():

    print("Usage: FFDH gen_params {modsize} from modsize:%r\n\n" %
          ffdh_mod_size +
          "Examples:\n"
          "  dispatcher-client.py FFDH reset\n"
          "  dispatcher-client.py -t 40 FFDH gen_params 1024\n"
          "NOTE: Set timeout 'dispatcher-client.py -t 40 ...' "
          "when executing larger key size\n"
          "NOTE: Execute 'dispatcher-client.py FFDH reset' before "
          "executing 'dispatcher-client.py -t 40 FFDH gen_params' or "
          "'dispatcher-client.py -t 40 FFDH set_params' command"
          "\n")
    raise SystemExit(1)


def usage_ffdh_set_peer_pub():
    print("Usage: FFDH set_peer_pub {pub_value (hex)}\n\n"
          "Examples:\n"
          "  dispatcher-client.py -t 40 FFDH set_peer_pub {pub_value}"
          "\n")
    raise SystemExit(1)


def usage_encrypt_init():
    print("Usage: ECIES encrypt_init \\\n"
          "\thc_id: (1, 2) \\\n"
          "\tmode:", str(tuple(m for m in ecies_mode)), "\\\n"
          "\tpubkey: pubkey in hex\n\n"
          "Examples:\n"
          "  dispatcher-client.py ECIES encrypt_init 1 P256_SHA256_AES128 "
          "52c61281593ad5ecf8d041f778dd97777f9cd89e9e4830015de52052e2cd0778\n"
          "  dispatcher-client.py ECIES encrypt_init 1 P384_SHA384_AES128 "
          "08c17712e18663d54f67f0b943d8c68af807d21a92f676e0"
          "d4fed736b76dc7619eb769ef94b09b263e87e102ff8bc00a\n"
          "  dispatcher-client.py ECIES encrypt_init 1 P521_SHA512_AES256 "
          "00f384fda776118ca0ee197954d909bf7e2a37d3ec41565a1"
          "f8a2f3d020262177de75774ef02e82f677c37ff6ec54e1183"
          "9f6ff089a85930aa9cf69f22850256257a"
          "\n")
    raise SystemExit(1)


def usage_encrypt_update():
    print("Usage: ECIES encrypt_update {plaintext 16B aligned}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES encrypt_update 'Plain test string'"
          "\n")
    raise SystemExit(1)


def usage_encrypt_final():
    print("Usage: ECIES encrypt_final {plaintext}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES encrypt_final 'g'\n\n"
          "NOTE: After 'encrypt_final' has been called, 'encrypt_update' can\n"
          "      no longer be used again before re-execution of 'encrypt_init'"
          "\n")
    raise SystemExit(1)


def usage_encrypt_final_si():
    print("Usage: ECIES encrypt_final_si {sharedinfo} {plaintext}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES encrypt_final_si 'shared_info' 'shared_msg'\n\n"
          "NOTE: After 'encrypt_final_si' has been called, this can no longer\n"
          "      be used again before re-execution of 'encrypt_init'"
          "\n")
    raise SystemExit(1)


def decrypt_init():
    print("Usage: ECIES decrypt_init \\\n"
          "\thc_id: (1, 2) \\\n"
          "\tmode:", str(tuple(m for m in ecies_mode)), "\\\n"
          "\tprivkey: privkey in hex \\\n"
          "\tepubkey: epubkey in hex\n\n"
          "Examples:\n"
          "  dispatcher-client.py ECIES decrypt_init 1 P256_SHA256_AES128 "
          "b1e79339d02a6c0331b057b2e84fb93a2648341d7c891f3e46591cdb6200a805 "
          "{epubkey of 'encrypt_init'}\n"
          "  dispatcher-client.py ECIES decrypt_init 1 P384_SHA384_AES128 "
          "b0876cddcc1c2890472c71210e2af9af00c784125892cdd4"
          "eee70017c1fd6adbdf1a794f9febe605055d3c0fb7406c74 "
          "{epubkey of 'encrypt_init'}\n"
          "  dispatcher-client.py ECIES decrypt_init 1 P521_SHA512_AES256 "
          "009a90288bb61dfd1d027518b4cdc6acb8a632a321c9e7a95"
          "cba2f954c4b1c9c31136b97b6490672e92b6a963f8003d837"
          "2162f93025c23dd8e755bab36be99b65e4 "
          "{epubkey of 'encrypt_init'}"
          "\n")
    raise SystemExit(1)


def usage_decrypt_update():
    print("Usage: ECIES decrypt_update {plaintext 16B aligned}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES decrypt_update {ct of 'encrypt_update'}"
          "\n")
    raise SystemExit(1)


def usage_decrypt_final():
    print("Usage: ECIES decrypt_final {plaintext}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES decrypt_final {ct of 'encrypt_final'}\n\n"
          "NOTE: After 'decrypt_final' has been called, "
          "this along with the 'decrypt_update' can no longer be used again "
          "without executing the 'decrypt_init'"
          "\n")
    raise SystemExit(1)


def usage_decrypt_final_si():
    print("Usage: ECIES decrypt_final_si {sharedinfo} {cipher}\n\n"
          "Example:\n"
          "  dispatcher-client.py ECIES decrypt_final_si {sharedinfo of 'encrypt_final_si'} "
          "{cipher is ct of 'encrypt_final_si'}\n"
          "NOTE: After 'decrypt_final' has been called, "
          "this along with the 'decrypt_update' can no longer be used again "
          "without executing the 'decrypt_init'"
          "\n")
    raise SystemExit(1)


def usage_rsa_sign():
    print("Usage: RSA SIGN \\\n"
          "\thash algorithm:", tuple(k for k in rsa_hash), "\\\n"
          "\tcrt calculation: ('CRT_ON', 'CRT_OFF') \\\n"
          "\tn public modulus: hex string \\\n"
          "\te public exponent: hex string \\\n"
          "\td private exponent: hex string \\\n"
          "\tsalt val: hex string \\\n"
          "\tmsg: plaintext or hex string\n\n"
          "Example:\n"
          "  dispatcher-client.py RSA SIGN SHA256 CRT_ON "
          "bf15c7a344db52c3da4c73bbe1aa9e43a24cc3ccdfa6dcb994e29846401f3d5e"
          "c9138756487def58d4bc5082baa8e93c840405d36ef37f59594d01f0665edb27"
          "cee3b6b647437405652cf809200597b0de806ea9ae20799400fe24bb3496d92e"
          "65ab5718c61ea24e302b2414f4a6ac1c99a4177de0f83882d638c46c95e2412b "
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000183a77 "
          "27d46433e4a96f1089c9da5e63254c1bed4075943dc00dfe44ac3eeb3115a71f"
          "b9c975b0db87860bceb813c0c4060eba926627add6b70b959e71274defa0a79e"
          "4a9a9262dd68ec6539e72078e0888c3f4e6ff74374e968f97033d1c328b17eab"
          "87e9637062726ac82b4f042fd376c892b61325a2004d372534b7e106817e8e07 "
          "507372afffebc2d67cd714e38e367776e34b377a "
          "0b95962764ca7454c8212a4407782e6174248c5898db391d28d2a42f35228f1d"
          "a3701d49dccd2cecc5dbe45af23190881601adcbbdf841e23d666f37e99f4762"
          "89a1e3ef07f7af616bdd087609a409adf958a106c8a1e9096de7b5097fb96aaa"
          "a5700fa14d0fa6bba16ebc21b6983fda07719091239cd999a29ba12e5d389dfe\n"
          "NOTE: Set timeout 'dispatcher-client.py -t 40 ...' "
          "when executing larger key size"
          "\n")
    raise SystemExit(1)


def usage_rsa_verify():
    print("Usage: RSA VERIFY \\\n"
          "\thash algorithm:", tuple(k for k in rsa_hash), "\\\n"
          "\tn public modulus: hex string \\\n"
          "\te public exponent: hex string \\\n"
          "\td private exponent: hex string \\\n"
          "\tsalt val: hex string \\\n"
          "\tsignature: hex string \\\n"
          "\tmsg: plaintext or hex string\n\n"
          "Examples:\n"
          "  dispatcher-client.py RSA VERIFY SHA256 "
          "bf15c7a344db52c3da4c73bbe1aa9e43a24cc3ccdfa6dcb994e29846401f3d5e"
          "c9138756487def58d4bc5082baa8e93c840405d36ef37f59594d01f0665edb27"
          "cee3b6b647437405652cf809200597b0de806ea9ae20799400fe24bb3496d92e"
          "65ab5718c61ea24e302b2414f4a6ac1c99a4177de0f83882d638c46c95e2412b "
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000000000"
          "0000000000000000000000000000000000000000000000000000000000183a77 "
          "27d46433e4a96f1089c9da5e63254c1bed4075943dc00dfe44ac3eeb3115a71f"
          "b9c975b0db87860bceb813c0c4060eba926627add6b70b959e71274defa0a79e"
          "4a9a9262dd68ec6539e72078e0888c3f4e6ff74374e968f97033d1c328b17eab"
          "87e9637062726ac82b4f042fd376c892b61325a2004d372534b7e106817e8e07 "
          "507372afffebc2d67cd714e38e367776e34b377a "
          "7287a0b4db04c8c795018cf818a170b152309ee195cb239d22c70eb248e1db54"
          "dcf0c0f6c8a311bd07c7051218e53c41e94d0c67707d0a69f5bd9cd1abc5e01c"
          "dbe70d4abc75a8536bad424d94ce160d71104b89d920fbdddf8da741178bbbf3"
          "15c3e9fa9cfdaacd41a55a86eb143c1fce55f0bac0b5e08c9dffdad05485031d "
          "0b95962764ca7454c8212a4407782e6174248c5898db391d28d2a42f35228f1d"
          "a3701d49dccd2cecc5dbe45af23190881601adcbbdf841e23d666f37e99f4762"
          "89a1e3ef07f7af616bdd087609a409adf958a106c8a1e9096de7b5097fb96aaa"
          "a5700fa14d0fa6bba16ebc21b6983fda07719091239cd999a29ba12e5d389dfe\n")
    raise SystemExit(1)


def aes_send_command(pm, args):
    key_sizes = (128, 192, 256, 512)
    iv_sizes = (0, 96, 128, 256)
    iv_ccm_sizes = (56, 64, 72, 80, 88, 96, 104)
    tag_lengths = (0, 96, 104, 112, 120, 128)
    tag_ccm_lengths = (32, 48, 64, 96, 112, 128)
    ciphers = tuple(k for k in aes_cipher)
    operations = tuple(k for k in cipher_op)
    if len(args) < 2:
        print("Usage: AES \\\n"
              "\tcipher:", ciphers, " \\\n"
              "\toperation:", operations, " \\\n"
              "\tkey: in hex format, accepted key sizes:", key_sizes, " \\\n"
              "\tiv: in hex format, accepted iv sizes:", iv_sizes, " \\\n"
              "\taad: in hex format, can be empty \\\n"
              "\ttag: in hex format (decrypt) or integer (encrypt), "
              "accepted tag lengths:", tag_lengths, "\\\n"
              "\tmsg: (ciphertext, plaintext)\n\n"
             )
        raise SystemExit(1)
    if args[1] not in ciphers:
        return False, "Cipher %s not in %r" % (args[1], ciphers)
    if len(args) != 8:
        if args[1] == "ECB": usage_aes_ecb()
        if args[1] == "CBC": usage_aes_cbc()
        if args[1] == "CFB": usage_aes_cfb()
        if args[1] == "CTR": usage_aes_ctr()
        if args[1] == "GCM": usage_aes_gcm()
        if args[1] == "XTS": usage_aes_xts()
        if args[1] == "CMAC": usage_aes_cmac()
        if args[1] == "CCM": usage_aes_ccm()
        return (False, "No usage for AES cipher %s!" % args[1])
    algorithm = aes_cipher[args[1]]
    if args[2] not in operations:
        return False, "Operation %s not in %r" % (args[2], operations)
    encrypt = cipher_op[args[2]]
    if args[1] == "ECB" and len(args[4]) != 0:
        return False, "IV length is %u, but must be empty for AES-ECB" % len(args[4])
    if args[1] == "CMAC" and len(args[7]) != 0:
        return False, "msg length is %u, but must be empty for AES-CMAC" % len(args[7])
    if args[1] == "CMAC" and args[2] == "DECRYPT":
        return False, "DECRYPT operation not supported for AES-CMAC"
    keylen = (len(args[3]) + 1) // 2
    if keylen * 8 not in key_sizes:
        return False, "Key size %s not in %r" % (keylen*8, key_sizes)
    if keylen * 8 == 512 and args[1] != "XTS":
        return (False, "Key size 512 only for AES-XTS not %s" % args[1])
    ivlen = (len(args[4]) + 1) // 2
    if args[1] == "CCM":
        if ivlen * 8 not in iv_ccm_sizes:
            return False, "IV length %s not in %r for CCM" % (ivlen*8, iv_ccm_sizes)
    else:
        if ivlen * 8 not in iv_sizes:
            return False, "IV length %s not in %r" % (ivlen*8, iv_sizes)
    if args[1] == "GCM" and ivlen * 8 != 96:
        return False, "IV length %u must be 96 bits for AES-GCM" % (ivlen*8)
    aadlen = (len(args[5]) + 1) // 2
    msg = args.pop()

    if encrypt == cipher_op['DECRYPT']:
        taglen = (len(args[6]) + 1) // 2
        if args[1] == "CCM":
            if taglen * 8 not in tag_ccm_lengths:
                return False, "Tag length %s not in %r for CCM " % (taglen*8, tag_ccm_lengths)
        else:
            if taglen * 8 not in tag_lengths:
                return False, "Tag length %s not in %r" % (taglen*8, tag_lengths)
    else:
        try:
            taglen = int(args.pop()) // 8
            if args[1] in ["ECB", "CBC"] and taglen != 0:
                return False, "tag length must be zero"
        except ValueError:
            return False, "tag length can not be empty"

    data = b""
    # add trailing zeroes for final 4-aligns (msg does not need to be padded)
    for arg in args[3:]:
        try:
            # need to first round-up then fromhex as hex string may have odd length
            data += bytes.fromhex(arg.ljust(round_up(len(arg), 8), '0'))
        except ValueError:
            return False, "\nInput_error: Input must be in hex format"
        pass

    try:
        # opportunistically try if msg is hex string (pad '0' if odd length)
        if len(msg) & 1:
            msg = bytes.fromhex(msg + '0')
        else:
            msg = bytes.fromhex(msg)
    except ValueError:
        msg = msg.encode()
        pass

    msglen = len(msg)
    data += msg
    data = make_packet(aes_args, algorithm, encrypt, keylen,
                       ivlen, aadlen, taglen, msglen, blob=data)
    sac_send(pm, data)
    return True, "Success"


def receive_hex_response(pm):
    data = sac_receive(pm)
    return "Core out:", bytes(data).hex(), -1

def receive_text_response(pm):
    data = bytes(sac_receive(pm)).decode()
    global resplen
    if resplen is not None: data, resplen = data[:resplen], None
    return "Core out:", data, -1

def receive_hex_or_text_response(pm):
    data = sac_receive(pm)
    if len(data) == 1:
        data = int.from_bytes(data, "big")
        return "Core out:", ("PASS" if data == 0 else "FAIL"), -1
    return "Core out:", bytes(data).hex(), -1


def flash_send_command(pm, args):
    if len(args) < 3:
        return False, ("Usage: %s (read|write) (length|data)" % args[0] + "\n\n"
                       "Examples:\n"
                       "  dispatcher-client.py Flash write 'Hello world!'\n"
                       "  dispatcher-client.py Flash read 12"
                       "\n")
    if args[1] not in ('read', 'write'):
        return False, "Flash command %s is not read or write" % (args[1])
    if args[1] == 'read':
        cmd = 1
        try:
            dlen = int(args[2], 0)
        except ValueError:
            return False, "Requested value %s is not a valid integer" % args[2]
        data = 'A' * dlen
    elif args[1] == 'write':
        cmd = 2
        data = ' '.join(args[2:])
        dlen = len(data)
    else:
        return False, "'%s': not 'read' nor 'write')" % args[1]

    if dlen == 0:
        return False, "Data len must be larger than zero"

    data = make_packet(flash_args, cmd, 1024 * 1024, dlen, blob=data)
    sac_send(pm, data)
    return True, "Success"


def flash_receive_response(pm):
    data = sac_receive(pm)
    hdr = flash_args.from_buffer(data, 0)
    cmd = hdr.cmd
    offs = hdr.offs
    dlen = hdr.len
    print("offset: ", offs)
    print("length: ", dlen)
    if cmd == 1:
        return "Read data:", data.raw[12:], offs
    return "Write len:", dlen, -1


def fmc_send_command(pm, args):
    if len(args) < 4:
        return False, ("Usage: %s (feature_set|feature_get|feature_sys_out)"
                       " address data mask" % args[0] + "\n\n"
                       "Examples:\n"
                       "  dispatcher-client.py FMC feature_set 4 1 0xf\n"
                       "  dispatcher-client.py FMC feature_get 4 1 0xf\n"
                       "  dispatcher-client.py FMC feature_sys_out 4 0xabc 0xffffffff"
                       "\n")
    cmd = args[1]
    if cmd not in fmc_cmds:
        return False, ("unknown FMC command: %s not in %r" %
                       (cmd, tuple(k for k in fmc_cmds)))
    # pylint: disable=attribute-defined-outside-init
    f = fmc_args()
    f.cmd = fmc_cmds[cmd]
    addr = try_int(args[2])
    try:
        in_data = int(args[3], 16)
    except ValueError:
        return False, "'%s': Only supports hex data" % args[3]
    try:
        in_mask = int(args[4], 16)
    except ValueError:
        return False, "'%s': Only supports hex mask" % args[4]
    f.offs = addr
    f.data = in_data
    f.mask = in_mask
    sac_send(pm, f)
    if verbose:
        print("fmc_send_command args\n", str_ctypes_obj(f))
    return True, "Success"


def fmc_receive_response(pm):
    data = sac_receive(pm)
    hdr = fmc_args.from_buffer(data, 0)
    if verbose:
        print("uart_receive_response args\n", str_ctypes_obj(hdr))
    cmd = hdr.cmd
    if cmd == 4:
        rv, err, prm = pm.read_fpga(CMRT_QUERY_CMD_PHYS_SYSCTL, R_SYSCTL_FMC_FEATURE_BITS)
        assert rv > 0, (rv, err)
        fpga_out = prm.r.value
        return "Success: FEATURE_SYS_OUT :", format(fpga_out, 'x'), -1
    data = data.raw[:20]
    data = data.decode().split("\n")[0]
    return "States:", data, -1


def elem(arr, i):
    if i < len(arr):
        return arr[i]
    return None


def try_int(x, base=0):
    try:
        return int(x, base=base)
    except ValueError:
        return None


def sid_send_command(pm, args):
    cmd = elem(args, 1)
    if cmd == "watch":
        irqs = try_int(elem(args, 2), base=0)
        if irqs is None:
            return False, "Usage: %s watch {irqs}\n" % args[0]
        data = make_packet(sid_args, 1, irqs)
        sac_send(pm, data)
        return True, "Success"
    if cmd == "get-irqs":
        data = make_packet(sid_args, 2, 0)
        sac_send(pm, data)
        return True, "Success"
    return False, "Usage: %s (watch {irqs} | get-irqs)\n" % args[0]


def sid_receive_response(pm):
    data = sac_receive(pm)
    args = sid_args.from_buffer(data, 0)
    if args.subcmd == 1:
        return "watch", args.irqs, -1
    if args.subcmd == 2:
        return "SID: seen IRQs", args.irqs, -1
    return "SID: unknown command", None, -1


def random_send_command(pm, args):
    if len(args) != 2:
        print("Usage: %s {size}\n" % args[0])
        raise SystemExit(1)
    try:
        random_size = int(args[1], 0)
        if args[1] < str(0):
            return False, "Requested value %s must be a non-negative integer" % args[1]
    except ValueError:
        return False, "Requested value %s is not a valid integer" % args[1]
    r = random_args(rsize=random_size)
    sac_send(pm, r)
    return True, "Success"


def debug_send_command(pm, args):
    if len(args) != 2:
        print("Usage: %s {enable|disable}\n" % args[0])
        raise SystemExit(1)
    enable = None
    if args[1] == "enable":
        enable = 1
    elif args[1] == "disable":
        enable = 0
    else:
        return False, "Unknown option: %s not 'enable' nor 'disable'\n" % args[1]

    d = debug_args(mode=enable)
    sac_send(pm, d)
    return True, "Success"


def perf_send_command(pm, args):
    if len(args) == 1 or args[1] not in perf_cmds:
        return False, ("Usage: Perf (getdata | status | reset)\n\n"
                       "Example:\n"
                       "  dispatcher-client.py Perf getdata\n")
    packet = make_packet(perf_args, perf_cmds[args[1]], 0, 0, 0)
    sac_send(pm, packet)
    return True, "Success"


def uart_send_command(pm, args):
    if len(args) < 2:
        opts = "{baudrate} {parity} {stop_bits} {data_bits} {flow_control}"
        return False, ("Usage: %s set-config %s | "
                       "set-default | enable | disable | get-config" % (args[0], opts) + "\n\n"
                       "Examples:\n"
                       "  dispatcher-client.py UART set-default\n"
                       "  dispatcher-client.py UART enable\n"
                       "  dispatcher-client.py UART disable\n"
                       "  dispatcher-client.py UART get-config\n")
    cmd = args[1]
    if cmd not in uart_cmds:
        return False, ("unknown UART command: %s not in %r" %
                       (cmd, tuple(k for k in uart_cmds)))

    # pylint: disable=attribute-defined-outside-init
    u = uart_args()
    u.cmd = uart_cmds[cmd]
    if cmd == "set-config":
        if len(args) != 7:
            print("Usage: UART set-config",
                  '|'.join(uart_cfg_baudrate.keys()),
                  '|'.join(uart_cfg_parity.keys()),
                  '|'.join(uart_cfg_stop_bits.keys()),
                  '|'.join(uart_cfg_data_bits.keys()),
                  '|'.join(uart_cfg_flow_ctrl.keys()) + "\n\n"
                  "Examples:\n"
                  "  dispatcher-client.py UART set-config "
                  "38400 PARITY_NONE STOP_BITS_1 DATA_BITS_8 "
                  "FLOW_CTRL_NONE\n"
                  "  dispatcher-client.py UART set-config "
                  "115200 PARITY_NONE STOP_BITS_1 "
                  "DATA_BITS_8 FLOW_CTRL_NONE\n")
            raise SystemExit(1)

        baudrate = uart_cfg_baudrate.get(args[2])
        if baudrate is None:
            return False, "Baud rate not in %s" % (tuple(uart_cfg_baudrate.keys()),)

        parity = uart_cfg_parity.get(args[3])
        if parity is None:
            return False, "Parity not in %s" % (tuple(uart_cfg_parity.keys()),)

        stop_bits = uart_cfg_stop_bits.get(args[4])
        if stop_bits is None:
            return False, "Stop bits not in %s" % (tuple(uart_cfg_stop_bits.keys()),)

        data_bits = uart_cfg_data_bits.get(args[5])
        if data_bits is None:
            return False, "Data bits not in %s" % (tuple(uart_cfg_data_bits.keys()),)

        flow_ctrl = uart_cfg_flow_ctrl.get(args[6])
        if flow_ctrl is None:
            return False, "Flow control not in %s" % (tuple(uart_cfg_flow_ctrl.keys()),)

        u.baudrate = baudrate
        u.parity = parity
        u.stop_bits = stop_bits
        u.data_bits = data_bits
        u.flow_ctrl = flow_ctrl
    if verbose:
        print("uart_send_command args\n", str_ctypes_obj(u))
    sac_send(pm, u)
    return True, "Success"


def getkey(dct, v):
    """
    Get corresponding key of the value from dictionary object
    """
    return tuple(dct.keys())[tuple(dct.values()).index(v)]


def uart_receive_response(pm, raw=False):
    data = sac_receive(pm)
    a = uart_args.from_buffer(data, 0)
    if verbose:
        print("uart_receive_response args\n", str_ctypes_obj(a))
    for k, v in uart_cmds.items():
        if v == a.cmd:
            cmd = k
            break
    else:
        return "UART", "Unknown return cmd", -1
    if raw:
        return a
    if cmd == "set-config":
        return "UART", "configuration updated", -1
    if cmd == "set-default":
        return "UART", "default configuration updated", -1
    if cmd == "enable":
        return "UART", "Enabled", -1
    if cmd == "disable":
        return "UART", "Disabled", -1
    if cmd == "get-config":
        pr = getkey(uart_cfg_parity, a.parity)
        sb = getkey(uart_cfg_stop_bits, a.stop_bits)
        db = getkey(uart_cfg_data_bits, a.data_bits)
        fc = getkey(uart_cfg_flow_ctrl, a.flow_ctrl)
        return ("UART Serial Port Config",
                f"\nbaudrate = {a.baudrate:d}" +
                f"\nparity = {pr:s}" +
                f"\nstopbits = {sb:s}" +
                f"\ndatabits = {db:s}" +
                f"\nflowctrl = {fc:s}", -1)
    assert 0, "unreachable"


def hex2le(s, size):
    # Convert an integer from hex string format into its little-endian
    # representation.  Be lenient about whitespace in the string.
    s = s.replace("\n", "").replace(" ", "")
    return int(s, base=16).to_bytes(size, "little")


def ffdh_key_t_fromhex(h):
    return ffdh_key_t.from_buffer_copy(hex2le(h, sizeof(ffdh_key_t)))


def ffdh_send_command(pm, args):
    if len(args) < 2:
        return False, ("Usage: FFDH \\\n"
                       "\tffdh_command: (" +
                       ", ".join(ffdh_cmds.keys()) + ") \\\n\tparams\n\n"
                       "Execute 'dispatcher-client.py -t 40 FFDH gen_params',\n"
                       "'dispatcher-client.py -t 40 FFDH set_params' or\n"
                       "'dispatcher-client.py -t 40 FFDH set_peer_pub' "
                       "to see individual examples\n\n"
                       "Execution Order:\n"
                       "  'dispatcher-client.py FFDH reset'\n"
                       "  'dispatcher-client.py -t 40 FFDH gen_params 1024'\n"
                       "   or\n"
                       "  'dispatcher-client.py -t 40 FFDH set_params ...'\n"
                       "  'dispatcher-client.py -t 40 FFDH set_peer_pub {pub_value}'\n"
                       "  'dispatcher-client.py -t 40 FFDH gen_our_key'\n"
                       "  'dispatcher-client.py -t 40 FFDH calc_shared'\n\n"
                       "NOTE: Set timeout 'dispatcher-client.py -t 40 ...' "
                       "when executing larger key size\n"
                       "NOTE: Execute 'dispatcher-client.py FFDH reset' before executing\n"
                       "     'dispatcher-client.py -t 40 FFDH gen_params' or\n"
                       "     'dispatcher-client.py -t 40 FFDH set_params'"
                       "\n")
    cmd = args[1]
    if cmd not in ffdh_cmds:
        return False, ("unknown FFDH command: %s not in %r" %
                       (cmd, tuple(k for k in ffdh_cmds)))
    # pylint: disable=attribute-defined-outside-init
    a = ffdh_args()
    a.cmd = ffdh_cmds[cmd]
    if cmd == "reset":
        pass
    elif cmd == "set_params":
        if len(args) != 6: usage_ffdh_set_params()
        if args[2] not in ffdh_mod_size:
            return False, ("modsize: %s not in %r" % (args[2], ffdh_mod_size))
        a.modsize = int(args[2])
        try:
            a.params.P = ffdh_key_t_fromhex(args[3])
            a.params.Q = ffdh_key_t_fromhex(args[4])
            a.params.G = ffdh_key_t_fromhex(args[5])
            pass
        except ValueError:
            return False, "\nInput_error: Input must be in hex format"

    elif cmd == "gen_params":
        if len(args) != 3: usage_ffdh_gen_params()
        if args[2] not in ffdh_mod_size:
            return False, ("modsize: %s not in modsize:%r"
                           % (args[2], ffdh_mod_size))
        a.modsize = int(args[2])
    elif cmd == "set_peer_pub":
        if len(args) != 3: usage_ffdh_set_peer_pub()
        try:
            a.key = ffdh_key_t_fromhex(args[2])
        except ValueError:
            return False, "\nInput_error: Input must be in hex format"
    elif cmd == "gen_our_key":
        pass
    elif cmd == "calc_shared":
        pass
    if verbose:
        print("ffdh_send_command args\n", str_ctypes_obj(a))
    sac_send(pm, a)
    return True, "Success"


def ffdh_receive_response(pm, raw=False):
    data = sac_receive(pm)
    a = ffdh_args.from_buffer(data, 0)
    if verbose:
        print("ffdh_receive_response args\n", str_ctypes_obj(a))
    for k, v in ffdh_cmds.items():
        if v == a.cmd:
            cmd = k
            break
    else:
        return "FFDH", "Unknown return cmd", -1
    if raw:
        return a
    if cmd == "reset":
        return "FFDH", "reset ok", -1
    if cmd == "set_params":
        p = int.from_bytes(a.params.P, "little")
        q = int.from_bytes(a.params.Q, "little")
        g = int.from_bytes(a.params.G, "little")
        return "FFDH", f"P: {p:x}\nQ: {q:x}\nG: {g:x}\n", -1
    if cmd == "gen_params":
        p = int.from_bytes(a.params.P, "little")
        q = int.from_bytes(a.params.Q, "little")
        g = int.from_bytes(a.params.G, "little")
        return "FFDH", f"\nP=0x{p:x}\nQ=0x{q:x}\nG=0x{g:x}\n", -1
    if cmd == "set_peer_pub":
        return "FFDH", "peer public value is set", -1
    if cmd == "gen_our_key":
        pub = int.from_bytes(a.key, "little")
        return "FFDH", f"\ncmrt_pub=0x{pub:x}", -1
    if cmd == "calc_shared":
        shared = int.from_bytes(a.key, "little")
        return "FFDH", f"\nshared_secret=0x{shared:x}", -1
    assert 0, "unreachable"


def ecies_send_command(pm, args, raw_send=False):
    if len(args) < 2:
        return False, ("Usage: ECIES {cmd} {args}...\n"
                       "Where {cmd} is one of:\n    " +
                       ", ".join(ecies_cmds.keys()) + "\n\n"
                       "NOTE: After 'encrypt_final', 'encrypt_final_si' and 'decrypt_final'\n"
                       "      has been called, they along with the 'encrypt_update and'\n"
                       "      'decrypt_update' can no longer be used without executing\n"
                       "      'encrypt_init' or 'decrypt_init'\n"
                       "NOTE: Set timeout 'dispatcher-client.py -t 40 ...'\n"
                       "      when executing larger key size"
                       "\n")
    cmd = args[1]
    if cmd not in ecies_cmds:
        return False, "Unknown command: %s" % cmd

    # pylint: disable=attribute-defined-outside-init
    a = ecies_args()
    a.cmd = ecies_cmds[cmd]
    if cmd == "close":
        pass
    elif cmd == "encrypt_init":
        if len(args) != 5: usage_encrypt_init()
        hc_id = int(args[2])
        mode = int(ecies_mode[args[3]][0])
        keysize = int(ecies_mode[args[3]][1])
        try:
            data = bytes.fromhex(args[4])
        except ValueError:
            return False, "{pubkey} must be in hex format\n"
        data_size = len(data)
        if data_size != keysize:
            return False, "ECIES encrypt_init wrong pubkey"
        a = make_packet(ecies_args, a.cmd, hc_id, mode, keysize, 0, 0,
                        blob=data)
        pass
    elif cmd == "encrypt_update":
        if len(args) < 3: usage_encrypt_update()
        pt = ' '.join(args[2:])
        if raw_send is False:
            if len(pt) <= 16:
                pt = pt.zfill(16)
            else:
                pt_z = (len(pt) // 16) + 1
                pt = pt.zfill(pt_z*16)
        a = make_packet(ecies_args, a.cmd, 0, 0, len(pt), 0, 0, blob=pt)
    elif cmd == "encrypt_final":
        argc = len(args)
        pt = ""
        if argc <= 2: usage_encrypt_final()
        if argc >= 3:
            pt = ' '.join(args[2:])
        if raw_send is False:
            if len(pt) <= 16:
                pt = pt.zfill(16)
            else:
                pt_z = (len(pt) // 16) + 1
                pt = pt.zfill(pt_z*16)
        textlen = len(pt)
        a = make_packet(ecies_args, a.cmd, 0, 0, textlen, 0, 0, blob=pt)
    elif cmd == "encrypt_final_si":
        argc = len(args)
        pt = ""
        if argc < 3: usage_encrypt_final_si()
        sharedinfo = args[2]
        if argc >= 4:
            pt = ' '.join(args[3:])
        if raw_send is False:
            if len(pt) <= 16:
                pt = pt.zfill(16)
            else:
                pt_z = (len(pt) // 16) + 1
                pt = pt.zfill(pt_z*16)
        data = pt + sharedinfo
        print("earlier_data", data)
        print("earlier_data", len(data))
        a.cmd = ecies_cmds["encrypt_final"]
        a = make_packet(ecies_args, a.cmd, 0, 0, len(pt), len(sharedinfo), 0, blob=data)
    elif cmd == "decrypt_init":
        if len(args) != 6: decrypt_init()
        hc_id = int(args[2])
        mode = int(ecies_mode[args[3]][0])
        keysize = int(ecies_mode[args[3]][1])
        try:
            privkey = bytes.fromhex(args[4])
        except ValueError:
            return False, "{privkey} must be in hex format\n"
        privlen = len(privkey)
        if privlen != keysize:
            return False, "ECIES decrypt_init wrong peer private key size"
        try:
            epubkey = bytes.fromhex(args[5])
        except ValueError:
            return False, "{epubkey} must be in hex format\n"
        epublen = len(epubkey)
        if epublen != keysize:
            return False, "ECIES decrypt_init wrong empheral public key size"
        data = privkey + epubkey
        a = make_packet(ecies_args, a.cmd, hc_id, mode, privlen, epublen, 0, blob=data)
        pass
    elif cmd == "decrypt_update":
        if len(args) < 3: usage_decrypt_update()
        cipher = bytes.fromhex(args[2])
        a = make_packet(ecies_args, a.cmd, 0, 0, len(cipher), 0, 0, blob=cipher)
        pass
    elif cmd == "decrypt_final":
        argc = len(args)
        if argc <= 2: usage_decrypt_final()
        cipherlen = 0
        data = ''
        if argc == 3:
            cipher = bytes.fromhex(args[2])
            cipherlen = len(cipher)
            data = cipher
        a = make_packet(ecies_args, a.cmd, 0, 0, cipherlen, 0, 0, blob=data)
        pass
    elif cmd == "decrypt_final_si":
        argc = len(args)
        if argc <= 3 or argc > 4: usage_decrypt_final_si()
        sharedinfo = args[2].encode()
        data = sharedinfo
        cipherlen = 0
        if argc == 4:
            try:
                cipher = bytes.fromhex(args[3])
            except ValueError:
                return False, "{cipher} must be in hex format\n"
            cipherlen = len(cipher)
            data = cipher + data
        a.cmd = ecies_cmds["decrypt_final"]
        a = make_packet(ecies_args, a.cmd, 0, 0, cipherlen, len(sharedinfo), 0,
                        blob=data)
    if verbose:
        print("ecies_send_command args\n", str_ctypes_obj(a))
    sac_send(pm, a)
    return True, "Success"


def ecies_receive_response(pm, raw=False):
    data = sac_receive(pm)
    a = ecies_args.from_buffer(data, 0)
    if verbose:
        print("ecies_receive_response args\n", str_ctypes_obj(a))
    for k, v in ecies_cmds.items():
        if v == a.cmd:
            cmd = k
            break
    else:
        return "ECIES", "Unknown return cmd", -1
    if raw:
        return data
    if cmd == "close":
        return "ECIES", "Close ok", -1
    if cmd == "encrypt_init":
        epub_key = int.from_bytes(data.raw[24:(24+a.textlen)], "big")
        epub_key_str = f"{epub_key:0{2*a.textlen}x}"
        return "ECIES", f"epubkey({a.textlen:d}): {epub_key_str:s}", -1
    if cmd == "encrypt_update":
        ct = int.from_bytes(data.raw[24:(24+a.textlen)], "big")
        ct_str = f"{ct:0{2*a.textlen}x}"
        return "ECIES", f"ct({a.textlen:d}): {ct_str:s}", -1
    if cmd == "encrypt_final":
        tag = int.from_bytes(data.raw[24:(24+a.taglen)], "big")
        ct = int.from_bytes(data.raw[(24+a.taglen):(24+a.taglen+a.textlen)],
                            "big")
        ct_str = f"{ct:0{2*a.textlen}x}"
        tag_str = f"{tag:0{2*a.taglen}x}"
        return ("ECIES", f"ct({a.textlen:d}): {ct_str:s}" +
                f"\ntag({a.taglen:d}): {tag_str:s}", -1)
    if cmd == "decrypt_init":
        epub_key = int.from_bytes(data[24:(24+a.textlen)], "big")
        epub_key_str = f"{epub_key:0{2*a.textlen}x}"
        return "ECIES", f"epubkey({a.textlen:d}): {epub_key_str:s}", -1
    if cmd == "decrypt_update":
        pt = data.raw[24:(24+a.textlen)].decode().lstrip('0')
        return "ECIES", f"pt({a.textlen:d}): {pt:s}", -1
    if cmd == "decrypt_final":
        tag = int.from_bytes(data.raw[24:(24+a.taglen)], "big")
        pt = data.raw[(24+a.taglen):(24+a.taglen+a.textlen)].decode().lstrip('0')
        tag_str = f"{tag:0{2*a.taglen}x}"
        return ("ECIES", f"pt({a.textlen:d}): {pt:s}" +
                f"\ntag({a.taglen:d}): {tag_str:s}", -1)
    assert 0, "Unreachable"


# should be encrypt 0 data ?
# or alternatively data should have the stuff in it
def otp_send_command(pm, args):
    # ok, let's take the data in here, or from a file instead?
    if len(args) != 3 or args[1] not in otp_cmds:
        return False, ("Usage: OTP (ENCRYPT|WRITE) file\n\n"
                       "Examples:\n"
                       "  dd if=/dev/zero of=blank.pt bs=4064 count=1\n"
                       "  dispatcher-client.py OTP encrypt blank.pt\n"
                       "  dispatcher-client.py OTP write encrypted.ct\n"
                       "  NOTE: write operation is very dangerous and may\n"
                       "        result in an unbootable system\n")
    data = b''
    try:
        data = open(args[-1], 'rb').read()
    except OSError as e:
        return False, "Could not read %s: %s" % (args[-1], e.strerror)
    packet = make_packet(otp_args, otp_cmds[args[1]], 0, 0,
                         len(data), blob=data)
    sac_send(pm, packet)
    return True, "Success"


def otp_receive_response(pm, raw=False):
    data = sac_receive(pm)
    if raw:
        return data
    return "Encrypted:", data.raw[16:].hex(), -1

def hsdh_send_command(pm, args):
    if len(args) < 2 or args[1] == "help" or args[1] not in hsdh_cmds.keys():
        return False, ("Usage: HSDH (enable {flowid} | disable | state)\n\n"
                       "Examples:\n"
                       "  dispatcher-client.py HSDH enable 22\n"
                       "  dispatcher-client.py HSDH state\n"
                       "  dispatcher-client.py HSDH disable\n")

    cmd = hsdh_cmds[args[1]]
    flowid = 0
    if args[1] == "enable":
        if len(args) != 3:
            return False, "Provide the Flowid"
        pass
        try:
            flowid = int(args[2])
        except ValueError:
            return False, "Flowid must be a integer"
        if flowid == 0:
            return False, "Flowid 0 is reserved for dispatcher main thread"

    packet = hsdh_args(cmd, flowid, 0)
    sac_send(pm, packet)
    return True, "Success"

def hsdh_receive_response(pm):
    hsdh_state = {
        0: "", # Status unknown
        1: "stopped",
        2: "starting",
        3: "running",
    }

    data = sac_receive(pm)
    resp = hsdh_args.from_buffer(data)
    state = hsdh_state[resp.state]
    if state:
        return "HSDH", f"service is {state:s}", -1
    return "OK", "", -1

def hmac_send_command(pm, args):
    hc_ids = (1, 2)
    sha2_funcs = ('SHA224', 'SHA256', 'SHA384', 'SHA512', 'SHA512/224', 'SHA512/256')
    sha3_funcs = ('SHA3_224', 'SHA3_256', 'SHA3_384', 'SHA3_512')
    if len(args) != 5:
        return (False, ("Usage: HMAC \\\n"
                        "\thash_func: \\\n"
                        "\t    SHA2 functions: " + str(sha2_funcs) + " \\\n"
                        "\t    SHA3 functions (if available): " + str(sha3_funcs) + " \\\n"
                        "\thc_id: " + str(tuple(hc for hc in hc_ids)) + " \\\n"
                        "\tkey: plaintext or hex string \\\n"
                        "\tdata: plaintext or hex string\n\n"
                        "Example:\n"
                        "  dispatcher-client.py HMAC SHA224 1 "
                        "0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b "
                        "4869205468657265"
                        "\n"))

    hash_func = args[1]
    if hash_func[:5] == 'SHA3_':
        sha_family = 3
        hash_funcs = sha3_funcs
    else:
        sha_family = 2
        hash_funcs = sha2_funcs
    if hash_func not in hash_funcs:
        return False, "Hash function %s not in %r" % (hash_func, hash_funcs)
    hash_size = int(hash_func[-3:])
    truncated = int('512/' in hash_func)
    hc_id = int(args[2])
    if hc_id not in hc_ids:
        return False, "Hash core id %d not in %r" % (hc_id, hc_ids)
    key = args[3]
    try:
        # confirm key is hex, else ValueError
        int(key, 16)
    except ValueError:
        key = key.encode().hex()
    if len(key) % 2 != 0:
        return False, "Even number of hmac key bytes required"
    keylen = len(key)
    # key is 4-byte aligned to reduce the need to copy later on
    key = key.ljust(round_up(keylen, 8), '0')
    keylen //= 2
    msg = args[4]
    try:
        # confirm msg is hex, else ValueError
        int(msg, 16)
    except ValueError:
        msg = msg.encode().hex()
    if len(msg) % 2 != 0:
        return False, "Even number of hmac msg bytes required"
    data = bytes.fromhex(key + msg)
    data = make_packet(hmac_args, sha_family, hc_id, hash_size,
                       truncated, keylen, len(data), blob=data)
    sac_send(pm, data)
    return True, "Success"

def hmac_receive_response(pm):
    data = sac_receive(pm)
    return "HMAC:", bytes(data).hex(), -1

def ccp_send_command(pm, args):
    modes = {'CHACHA': 1, 'POLY': 2, 'CHACHAPOLY': 3}
    if len(args) < 3:
        return (False, ("Usage: CCP {operation} {mode} ..."
                        "\n\toperation: " + str(tuple(cipher_op.keys())) +
                        "\n\tmode: " + str(tuple(modes.keys())) +
                        "\n"))
    op = args[1]
    if op not in cipher_op:
        return False, ("CCP operation %s not in %r" % (op, cipher_op.keys()))
    op = cipher_op[op]
    mode = args[2]
    if mode not in modes:
        return False, ("CCP mode %s not in %r" % (mode, modes.keys()))
    if args[2] == 'CHACHA':
        if len(args) != 8: usage_chacha_shared_secret()
        pass
    if args[2] == 'POLY':
        if len(args) != 8: usage_poly_shared_secret()
        pass
    if args[2] == 'CHACHAPOLY':
        if len(args) != 8: usage_chacha_poly_shared_secret()
        pass

    mode = modes[mode]
    if mode == modes['POLY'] and op == cipher_op['DECRYPT']:
        return False, "\nInput_error: POLY only supports ENCRYPT tag verification"
    try:
        key = bytes.fromhex(args[3])
        if mode in (modes['CHACHA'], modes['CHACHAPOLY']) and len(key) not in (16, 32):
            pass
        if mode == modes['POLY'] and len(key) != 32:
            return False, "\nInput_error: key length %u not 32 hex for POLY" % (len(key))
    except ValueError:
        return False, "\nInput_error: Key length must be 32 or 64 hex"

    iv = args[4]
    if mode == modes['CHACHA'] and len(iv) == 0:
        return False, "\nInput_error: iv length must be nonzero for CHACHA"
    if mode in [modes['CHACHA'], modes['CHACHAPOLY']]:
        iv = iv.zfill(16 * 2) # must be 16B, if not 0
    try:
        iv = bytes.fromhex(iv)
    except ValueError:
        return False, "\nInput_error: input must be in hex format and non-empty"

    aad = args[5]
    tag = args[6]
    if (len(aad) or len(tag)) > 0 and mode in [modes['CHACHA']]:
        return False, "\nInput_error: aad and tag must be empty for CHACHA"
    if mode == modes['CHACHAPOLY'] and op == cipher_op['DECRYPT'] and len(tag) != 32:
        return False, "\nInput_error: tag length must be 32 hex for CHACHAPOLY"
    if mode == modes['POLY'] and op in [cipher_op['ENCRYPT'], cipher_op['DECRYPT']]:
        if len(iv) != 0 or len(aad) != 0:
            return False, "\nInput_error: iv and aad must be empty for POLY"
    aadlen = len(aad) // 2
    if aadlen > 0:
        # 4-byte align aad
        aad = aad.ljust(round_up(len(aad), 8), '0')
    try:
        aad = bytes.fromhex(aad)
    except ValueError:
        aad = aad.encode()
    if mode == modes['CHACHA'] or op == cipher_op['ENCRYPT']:
        if len(tag) != 0:
            return False,"\nInput_error: tag must be empty for ENCRYPT "
    else:
        tag = tag.zfill(16 * 2) # must be 16B
    try:
        tag = bytes.fromhex(tag)
    except ValueError:
        return False, "\nInput_error: input must be in hex format"
    msg = args[7]
    if mode == modes['POLY'] and len(msg) == 0:
        return False, "\nInput_error: message can not be Empty for POLY"
    try:
        msg = bytes.fromhex(msg)
    except ValueError:
        msg = msg.encode()
    data = key + iv + aad + tag + msg
    data = make_packet(
        ccp_args, op, mode, len(key), len(iv), aadlen, len(tag), len(msg), blob=data)
    sac_send(pm, data)
    return True, "Success"


def ccp_receive_response(pm):
    data = sac_receive(pm)
    return "CCP:", bytes(data).hex(), -1

KEYS = {
    'dgok': 0,
    'bnak': 1,
    'snak': 2,
    'pnak': 3,
    'selftest': 0x40
}

def key2num(key: str):
    """Transform the key into the numeric argument"""
    if key in KEYS:
        return KEYS[key]
    return int(key, 0)


def kdc_send_command(pm, args):
    # base key and diversify path
    if len(args) != 3 and len(args) != 4:
        return False, ("Usage: KDC key-id path [dest]\n\n"
                       "Examples:\n"
                       "  dispatcher-client.py KDC dgok 0011223344\n"
                       "  dispatcher-client.py KDC dgok 0011223344 [0x10, 0x1F]\n")
    if args[1].lower() not in KEYS:
        return False, ("KDC command %s not in %r" % (args[1], KEYS.keys()))
    try:
        # should have some keys built in...
        key = key2num(args[1].lower())
        data = bytes.fromhex(args[2])
        dest = 0xff
        if len(args) == 4:
            valid_dest = tuple(range(0x10, 0x20))
            dest = int(args[3], 16)
            if dest not in valid_dest:
                return False, ("KTC valid destination not in [0x10, 0x1F]")
    except ValueError:
        return False, "Could not read : %r", args[1:2]
    packet = make_packet(kdc_args, key, len(data), dest, 0, blob=data)
    sac_send(pm, packet)
    return True, "Success"


def kdc_receive_response(pm, raw=False):
    data = sac_receive(pm)
    if raw:
        return data
    return "Derived:", data.raw.hex(), -1

command_rtx = {
    "Echo": {"send": echo_send_command, "receive": receive_text_response},
    "SHA2": {"send": sha2_send_command, "receive": sha_receive_response},
    "ECDSA": {"send": ecdsa_send_command, "receive": receive_hex_or_text_response},
    "RSA": {"send": rsa_send_command, "receive": receive_hex_or_text_response},
    "AES": {"send": aes_send_command, "receive": receive_hex_response},
    "KDC": { "send": kdc_send_command, "receive": kdc_receive_response },
    "Flash": {"send": flash_send_command, "receive": flash_receive_response},
    "SID": {"send": sid_send_command, "receive": sid_receive_response},
    "FFDH": {"send": ffdh_send_command, "receive": ffdh_receive_response},
    "UART": {"send": uart_send_command, "receive": uart_receive_response},
    "ECIES": {"send": ecies_send_command, "receive": ecies_receive_response},
    "OTP": {"send": otp_send_command, "receive": otp_receive_response},
    "ECDH": {"send": ecdh_send_command, "receive": receive_hex_response},
    "SHA3": {"send": sha3_send_command, "receive": sha_receive_response},
    "Random": {"send": random_send_command, "receive": receive_hex_response},
    "RSA_KEY_EXCH": {"send": init_rsa_key_exch, "receive": verify_rsa_signature},
    "HMAC": {"send": hmac_send_command, "receive": hmac_receive_response},
    "CCP": {"send": ccp_send_command, "receive": ccp_receive_response},
    "HSDH": {"send": hsdh_send_command, "receive": hsdh_receive_response},
    "FMC": {"send": fmc_send_command, "receive": fmc_receive_response},
    "Debug": {"send": debug_send_command, "receive": receive_hex_response},
    "Perf": {"send": perf_send_command, "receive": receive_text_response},
}

# -----------------------------------------------------------------------------

def query_commands(pm):
    sic_send_command(pm, CMDID_LIST)
    data = sac_receive(pm)

    class record(Structure):
        _fields_ = ( ("id", c_uint32),
                     ("name", c_char * 16),
                     ("length", c_uint32) )
    offset = 0
    command_info = {}
    while offset < len(data):
        r = record.from_buffer(data, offset)
        offset += sizeof(r)

        info = (c_char * r.length).from_buffer(data, offset)
        offset += round_up(r.length, 4)

        name = r.name.decode()
        if name not in command_rtx:
            # unsupported commands not shown
            continue
        command_info[name] = {"id": r.id, "info": info.raw.decode()}
        command_info[name].update(command_rtx[name])

    return command_info


def show_command_list(pm):
    commands = query_commands(pm)
    print("The following commands are available:")
    print(" ID | Name         | Info")
    print("-" * 40)
    for name, cmd in commands.items():
        print("%3d | %-12s | %s" % (cmd["id"] & 0xff, name, cmd["info"]))


def run_command(pm, args):
    commands = query_commands(pm)

    cmd = args.cmd[0]
    if cmd not in commands:
        print("Unknown command", cmd)
        show_command_list(pm)
        return

    cmd = commands[cmd]
    _id = cmd["id"]
    retval, info = cmd["send"](pm, args.cmd)
    if not retval:
        print(info)
        raise SystemExit(1)
    sic_send_command(pm, _id)
    prefix, data, index = cmd["receive"](pm)
    if index >= 0:
        print(prefix)
        hexdump(data, index)
    else:
        print(prefix, data)


def parse_args(help_msg=''):
    parser = argparse.ArgumentParser()
    parser.add_argument("--list", "-ls", "-l", action="store_true",
                        help="List available commands")
    parser.add_argument("-t", "--timeout",
                        help="Seconds to wait for eSW to finish processing "
                        "and reply. Default: %ds" % (_timeout // 1000))
    parser.add_argument("-c", action="store_true", help=argparse.SUPPRESS) #ign
    parser.add_argument("-d", action="store_true", help=argparse.SUPPRESS) #hid
    parser.add_argument("cmd", action="store", nargs=argparse.REMAINDER,
                        help="Command [and args] to execute")
    if help_msg:
        parser.print_usage()
        print("\n", help_msg, "\n")
    return parser.parse_args()


def main():
    args = parse_args()

    from cmrt import CMRT     # pylint: disable=import-outside-toplevel
    from cmrt_pm2 import PM2  # pylint: disable=import-outside-toplevel
    pm = PM2(CMRT("libcmrt.so"))

    #import pdb; pdb.set_trace()

    # currently (undocumended) developer option
    if args.d:
        pm.cmrt.cdll.set_debug.argtypes = (c_int32,)
        pm.cmrt.cdll.set_debug(2)

    if args.timeout:
        global _timeout
        _timeout = int(float(args.timeout) * 1000) # in msec
        print("Timeout set to %d msec\n" % _timeout)

    try:
        if args.list:
            show_command_list(pm)
            return

        if not args.cmd:
            parse_args("Either command [args] or '--list' required")
            return

        run_command(pm, args)
    except RuntimeError as e:
        sys.exit(e.args[0])
    except SicError as e:
        print(str(e))
        sys.exit(e.return_value)


if __name__ == '__main__':
    main()
