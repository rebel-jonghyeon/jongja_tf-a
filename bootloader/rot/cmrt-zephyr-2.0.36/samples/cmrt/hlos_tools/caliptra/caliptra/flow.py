# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

# pylint: disable=unsubscriptable-object

import logging
from ctypes import Structure, c_uint8, c_uint32, c_uint64
from typing import Iterable, List, Optional, Union
from errno import EBUSY

from cmrt import CMRT

logger = logging.getLogger(__name__)


class Structurex(Structure):
    # A ctypes.Structure with ability to set defaults for fields. In
    # addition, it forces use of keyword arguments (no positional).
    def __init__(self, *, _=None, **kwargs):
        if hasattr(self, "_defaults_"):
            vals = dict(self._defaults_).copy()
            vals.update(kwargs)
        else:
            vals = kwargs
        super().__init__(**vals)


FieldEntropySlot = c_uint8 * 32


class cmrt_caliptra_msg_write_field_entropy(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("use_tmc", c_uint32),
        ("value", FieldEntropySlot),
    )
    _defaults_ = (("cmd", 1),)


class cmrt_caliptra_msg_export_idevid_csr(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("max_len", c_uint32),
        ("sac_address", c_uint64),
    )
    _defaults_ = (("cmd", 2),)


class cmrt_caliptra_msg_import_idevid_cert_chain(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("chain_len", c_uint32),
        ("sac_address", c_uint64),
    )
    _defaults_ = (("cmd", 3),)


class cmrt_caliptra_msg_export_owner_csrs(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("max_len", c_uint32),
        ("sac_address", c_uint64),
    )
    _defaults_ = (("cmd", 4),)


class cmrt_caliptra_msg_export_idevid_cert_chain(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("max_len", c_uint32),
        ("sac_address", c_uint64),
    )
    _defaults_ = (("cmd", 5),)


class cmrt_caliptra_msg_update_field_entropy(Structurex):
    _pack_ = 1
    _fields_ = (
        ("cmd", c_uint32),
        ("value", FieldEntropySlot),
    )
    _defaults_ = (("cmd", 6),)


class cmrt_caliptra_msg_exit(Structurex):
    _pack_ = 1
    _fields_ = (("cmd", c_uint32),)
    _defaults_ = (("cmd", 100),)


# Some data used by Caliptra SW is serialized in SAC in LV
# (length-value) form.


def items_to_lv(items: Iterable[bytes]) -> bytes:
    """Construct a (length, data, [pad])* blob from the sequence of blobs."""
    data = b""
    for item in items:
        data += len(item).to_bytes(4, "little")
        data += item
        rem = len(data) % 4
        if rem > 0:
            data += b"\0" * (4 - rem)
    return data


def lv_to_items(data: bytes) -> List[bytes]:
    """Deconstruct a (length, data, [pad])* blob into its elements."""
    items = []
    while data:
        lengthb, data = data[:4], data[4:]
        length = int.from_bytes(lengthb, "little")
        item, data = data[:length], data[length:]
        items.append(item)
        rem = length % 4
        if rem > 0:
            # Skip over the padding.
            data = data[4 - rem :]
    return items


class SicError(Exception):
    """Error in SIC transfer"""

    pass


class SacError(Exception):
    """Error in SAC access"""

    pass


class EswError(Exception):
    """Error returned from CMRT Caliptra software"""

    pass


class CaliptraClient:
    """Base class of a HLOS client for talking to Caliptra SW"""

    SAC_BASE = 0x4000_0000

    def __init__(
        self,
        cmrt: CMRT,
        *,
        hlos_flowid: int = 0,
        esw_flowid: int = 0,
        sic_channel: int = 0,
        timeout_ms: int = 5000,
    ):
        self.cmrt = cmrt
        self.sic_channel = sic_channel
        self.hlos_flowid = hlos_flowid
        self.esw_flowid = esw_flowid
        self.timeout_ms = timeout_ms

    def rpc(
        self,
        data: Union[Structure, bytes],
        timeout_ms: int = 0,
        retries: int = 10
    ) -> int:
        """Attempt a Caliptra RPC command with retries.

        Sends the given data via SIC registers (never SAC), and
        expects a non-negative 32-bit integer as successful reply.

        It retries the call the given amount of times in case CMRT SIC
        replies with EBUSY. If all attempts failed, it re-raises the
        last error received.

        Raises SicError on communication errors, EswError on negative
        return value, and AssertionError on protocol violations.

        """

        last_exc = None
        for _ in range(retries):
            try:
                return self.rpc1(data, timeout_ms)
            except SicError as e:
                last_exc = e
                # Retry on EBUSY
                if e.args[1] != EBUSY:
                    raise
        # If all retries failed, we re-raise the last error.
        raise last_exc

    def rpc1(self, data: Union[Structure, bytes], timeout_ms: int = 0) -> int:
        """Attempt a Caliptra RPC command once.

        Sends the given data via SIC registers (never SAC), and
        expects a non-negative 32-bit integer as successful reply.

        Raises SicError on communication errors, EswError on negative
        return value, and AssertionError on protocol violations.

        """
        if not isinstance(data, bytes):
            data = bytes(data)
        logger.debug("caliptra-rpc: sending %r", data)
        # NOTE: timeout is not cumulative, it applies for each
        # individual operation.
        timeout = timeout_ms or self.timeout_ms
        datalen = len(data)
        rv = self.cmrt.sic_send_data(
            id_=self.sic_channel,
            src=self.hlos_flowid,
            dest=self.esw_flowid,
            address=0,
            count=datalen,
            timeout=timeout,
        )
        if rv != 0:
            raise SicError("sic_send_data: failed", rv)
        rv = self.cmrt.sic_send_reg(
            id_=self.sic_channel,
            src=self.hlos_flowid,
            dest=self.esw_flowid,
            buf=data,
            count=datalen,
            timeout=timeout,
        )
        if rv != datalen:
            # sic_send_reg() may return short if CMRT wrote an early
            # error. Ignore it here and let sic_recv_data() retrieve
            # the error.
            pass
        if rv < 0:
            raise SicError("sic_send_reg: error", rv)

        rv, addr = self.cmrt.sic_recv_data(
            id_=self.sic_channel,
            src=self.hlos_flowid,
            dest=self.esw_flowid,
            timeout=timeout,
        )
        if rv < 0:
            # The true error code is in errno.
            assert rv == -1, "sic_recv_data always returns -1 on error"
            raise SicError("sic_recv_data: failed", self.cmrt.errno())
        if rv != 4:
            raise AssertionError("sic_recv_data: expected 4 bytes response", rv)
        if addr != 0:
            raise AssertionError("sic_recv_data: expected sac address == 0", addr)
        ans = self.cmrt.sic_recv_reg(
            id_=0, src=self.hlos_flowid, dest=self.esw_flowid, count=rv, timeout=timeout
        )
        if ans is None:
            # The true return value is eaten by cmrt.CMRT()...
            raise SicError("sic_recv_reg: error", -1)
        logger.debug("caliptra-rpc: received %r", ans)
        if len(ans) != 4:
            raise AssertionError("sic_recv_reg: expected 4 bytes response", rv)
        esw_rv = int.from_bytes(ans, "little", signed=True)
        if esw_rv < 0:
            raise EswError("CMRT call returned", esw_rv)
        return esw_rv

    def items_from_sac(self, sac_address: int, n: int) -> List[bytes]:
        # Read a LV formatted blob of N items from SAC.
        items = []
        off = sac_address
        while n > 0:
            ans = self.cmrt.read_mem(self.SAC_BASE, off, 4)
            if ans is None or len(ans) != 4:
                raise SacError("failed to read from sac", ans, self.SAC_BASE + off, 4)
            length = int.from_bytes(ans, "little", signed=False)
            if length == 0:
                raise AssertionError("zero length item in SAC")
            off += 4
            data = self.cmrt.read_mem(self.SAC_BASE, off, length)
            logger.debug("reading item from sac %x+%d", self.SAC_BASE + off, length)
            if data is None or len(data) != length:
                raise SacError("read from sac failed", ans, self.SAC_BASE + off, length)
            items.append(data)
            off += length
            off = (off + 3) & 0xFFFFFFFC
            n -= 1
        return items


class CaliptraSetupClient(CaliptraClient):
    """HLOS client for the Caliptra setup perso container."""

    def __init__(self, *args, **kwargs):
        kwargs.setdefault("esw_flowid", 123)
        super().__init__(*args, **kwargs)

    def write_field_entropy(
        self, entropy: Optional[bytes] = None, use_tmc: bool = True
    ) -> int:
        if entropy:
            if use_tmc:
                raise ValueError("entropy and use_tmc are mutually exclusive")
            if len(entropy) != 32:
                raise ValueError("entropy must be 32 bytes long")
            m = cmrt_caliptra_msg_write_field_entropy(
                value=FieldEntropySlot.from_buffer_copy(entropy)
            )
        elif use_tmc:
            m = cmrt_caliptra_msg_write_field_entropy(use_tmc=use_tmc)
        else:
            raise ValueError("either entropy or use_tmc must be specified")
        return self.rpc(m)

    def export_idevid_csr(self) -> bytes:
        sacoff = 0
        maxlen = 1024
        self.rpc(
            cmrt_caliptra_msg_export_idevid_csr(max_len=maxlen, sac_address=sacoff)
        )
        return self.items_from_sac(sacoff, 1)[0]

    def import_idevid_cert_chain(self, chain: Iterable[bytes]) -> int:
        data = items_to_lv(chain)
        sacoff = 0
        length = len(data)
        rv = self.cmrt.write_mem(self.SAC_BASE, sacoff, data)
        if rv != length:
            raise SacError("failed to write chain", self.SAC_BASE + sacoff, length)
        return self.rpc(
            cmrt_caliptra_msg_import_idevid_cert_chain(
                chain_len=length, sac_address=sacoff
            )
        )


class CaliptraRTClient(CaliptraClient):
    """HLOS client for the Caliptra runtime container."""

    def __init__(self, *args, **kwargs):
        kwargs.setdefault("esw_flowid", 124)
        super().__init__(*args, **kwargs)

    def exit_rt(self) -> int:
        return self.rpc(cmrt_caliptra_msg_exit())

    def export_owner_csrs(self) -> List[bytes]:
        sacoff = 0
        maxlen = 16 * 1024
        m = cmrt_caliptra_msg_export_owner_csrs(max_len=maxlen, sac_address=sacoff)
        rv = self.rpc(m)
        if rv != 0:
            raise EswError("export_owner_csrs: failed", rv)
        return self.items_from_sac(sacoff, 2)

    def export_idevid_cert_chain(self) -> List[bytes]:
        sacoff = 0
        maxlen = 16 * 1024
        rv = self.rpc(
            cmrt_caliptra_msg_export_idevid_cert_chain(
                max_len=maxlen, sac_address=sacoff
            )
        )
        if rv != 0:
            raise EswError("export_idevid_cert_chain: failed", rv)
        return self.items_from_sac(sacoff, 4)

    def update_field_entropy(self, entropy: bytes):
        if len(entropy) != 32:
            raise ValueError("entropy must be 32 bytes long")
        return self.rpc(
            cmrt_caliptra_msg_update_field_entropy(
                value=FieldEntropySlot.from_buffer_copy(entropy)
            )
        )
