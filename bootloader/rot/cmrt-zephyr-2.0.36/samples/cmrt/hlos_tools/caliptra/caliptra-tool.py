#!/usr/bin/env python3
#
# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

r"""CMRT Caliptra tool

"""

import argparse
import logging
import os
import sys
import traceback
from pathlib import Path
from typing import Any

from caliptra import flow, pki

from cmrt import CMRT


def logging_env_config(envvar: str = "LOGLEVEL"):
    """Configure logging based on an environment variable.

    The variable ("LOGLEVEL" by default) should contain comma
    delimited logger config statements in "[logger:]level" form, where
    logger is a hierarchical name of a logging.Logger, and level is a
    valid log level string. If the logger name is omitted the level is
    applied to the root logger. Examples: LOGLEVEL="debug", or
    LOGLEVEL="info,some.module:debug"

    """
    logging.basicConfig(format="%(levelname)s: %(name)s: %(message)s")
    for part in os.environ.get(envvar, "").split(","):
        logconf = part.split(":")
        if len(logconf) == 1:
            logger = ""
            level = logconf[0]
        else:
            logger = logconf[0]
            level = logconf[1]
        if level:
            logging.getLogger(logger).setLevel(level.upper())


def get_cmrt():
    c = CMRT("libcmrt.so")
    if logging.getLogger("libcmrt").isEnabledFor(logging.DEBUG):
        c.cdll.set_debug(1)
    return c


def cmd_create_ca(opts):
    os.makedirs(opts.ca_dir, exist_ok=True)
    pki.create_ca_certs(opts.ca_cn_prefix, opts.ca_dir)


def cmd_issue_cert(opts):
    if not opts.out:
        return "--out must be specified"
    cas = pki.load_ca_chain(opts.ca_dir)
    csr = pki.load_csr(opts.csr)
    cert = pki.issue_cert(csr, cas[-1].cert, cas[-1].priv)
    opts.out.write(cert.dump())
    return None


def cmd_validate_cert(opts):
    root_ca, sub_ca = pki.load_ca_chain(opts.ca_dir)
    certs = [pki.asymmetric.load_certificate(f).asn1 for f in opts.chain]
    end_entity = certs[0]
    intermediates = certs[1:] + [sub_ca.cert.asn1]  # pylint: disable=no-member
    pki.validate_cert_chain(end_entity, intermediates, [root_ca])


def exactly_one_of(*conditions: Any) -> bool:
    return sum(bool(c) for c in conditions) == 1


def cmd_write_field_entropy(opts):
    client = flow.CaliptraSetupClient(get_cmrt(), timeout_ms=opts.timeout)
    if not exactly_one_of(opts.input, opts.use_tmc):
        return "either --input or --use-tmc must be specified"
    if opts.input:
        entropy = opts.input.read(32)
    else:
        entropy = None
    client.write_field_entropy(entropy=entropy, use_tmc=opts.use_tmc)
    return None


def cmd_export_idevid_csr(opts):
    client = flow.CaliptraSetupClient(get_cmrt(), timeout_ms=opts.timeout)
    if not opts.out:
        return "--out must be specified"
    csr = client.export_idevid_csr()
    opts.out.write(csr)
    return None


def cmd_import_idevid_cert_chain(opts):
    if not opts.input:
        return "--input must be specified"
    cert = opts.input.read()
    # This loads root first, then intermediates.
    cas = pki.load_ca_chain(opts.ca_dir)

    chain_bytes = (
        *(ca.cert.asn1.dump() for ca in cas),  # pylint: disable=no-member
        cert,
    )
    # Flip it, so IDevID is first, followed by intermediates and finally root.
    chain_bytes = chain_bytes[::-1]

    client = flow.CaliptraSetupClient(get_cmrt(), timeout_ms=opts.timeout)
    client.import_idevid_cert_chain(chain_bytes)
    return None


def cmd_provision(opts):
    if not opts.out:
        return "--out must be specified for saving the IDevID certificate"
    cas = pki.load_ca_chain(opts.ca_dir)
    client = flow.CaliptraSetupClient(get_cmrt(), timeout_ms=opts.timeout)

    # 1. Write field entropy using TMC
    client.write_field_entropy(use_tmc=True)

    # 2. Get the IDevID CSR and issue a certificate for it.
    csr_der = client.export_idevid_csr()
    csr = pki.der_to_csr(csr_der)
    cert = pki.issue_cert(csr, cas[-1].cert, cas[-1].priv)

    # 2.1. Save the IDevID cert to disk.
    opts.out.write(cert.dump())

    # 3. Get raw DER blobs out of the chain and import to CMRT.
    chain = *(ca.cert.asn1 for ca in cas), cert  # pylint: disable=no-member
    chain = chain[::-1]
    chain_bytes = [cert.dump() for cert in chain]
    client.import_idevid_cert_chain(chain_bytes)
    return None


def cmd_export_owner_csrs(opts):
    client = flow.CaliptraRTClient(get_cmrt(), timeout_ms=opts.timeout)
    csrs = client.export_owner_csrs()
    names = ["Owner LDevID", "Owner AliasFMC"]
    if len(csrs) != len(names):
        return f"unexpected number of CSRs: {len(csrs)}"
    os.makedirs(opts.outdir, exist_ok=True)
    for name, csr_der in zip(names, csrs):
        fn: Path = (opts.outdir / name.replace(" ", "_")).with_suffix(".der")
        fn.write_bytes(csr_der)
        logging.info("written %s", fn)
        try:
            pki.validate_csr_sig(pki.der_to_csr(csr_der))
        except Exception as e:  # pylint: disable=broad-except
            logging.warning("CSR validation failed: %r", e)
    return None


def cmd_export_idevid_cert_chain(opts):
    client = flow.CaliptraRTClient(get_cmrt(), timeout_ms=opts.timeout)
    certs = client.export_idevid_cert_chain()
    # Break up the IDevID cert chain.
    idevid_chain = flow.lv_to_items(certs[-1])
    certs = certs[:-1] + idevid_chain
    names = ["AliasRT", "AliasFMC", "LDevID", "IDevID", "SubCA", "RootCA"]
    if len(certs) != len(names):
        return f"unexpected number of certificates: {len(certs)}"
    os.makedirs(opts.outdir, exist_ok=True)
    for name, cert_der in zip(names, certs):
        fn: Path = (opts.outdir / name.replace(" ", "_")).with_suffix(".der")
        fn.write_bytes(cert_der)
        logging.info("written %s", fn)
    return None


def cmd_update_field_entropy(opts):
    client = flow.CaliptraRTClient(get_cmrt(), timeout_ms=opts.timeout)
    if not opts.input:
        return "--input must be specified"
    entropy = opts.input.read(32)
    client.update_field_entropy(entropy)
    return None


def cmd_exit(opts):
    client = flow.CaliptraRTClient(get_cmrt(), timeout_ms=opts.timeout)
    client.exit_rt()


def parse_args():
    argp_common = argparse.ArgumentParser(add_help=False)
    argp_common.add_argument(
        "--out",
        help="output file, or - for stdout",
        type=argparse.FileType("wb"),
    )

    argp_common.add_argument(
        "--input",
        help="input file, or - for stdin",
        type=argparse.FileType("rb"),
    )

    argp_ca = argparse.ArgumentParser(add_help=False)
    argp_ca.add_argument(
        "--ca-dir",
        help="directory with CA keys and certs",
        required=True,
    )

    argp = argparse.ArgumentParser(description=__doc__)
    argp.add_argument(
        "--verbose", "-v", action="count", help="increase verbosity", default=0
    )
    argp.add_argument(
        "--timeout",
        help="timeout (ms) for CMRT operations",
        type=int,
        default=5000,
    )

    argp.set_defaults(action=None)
    subp = argp.add_subparsers()
    argp_create_ca = subp.add_parser(
        "create-ca",
        parents=[argp_common, argp_ca],
        help="generate keys and certificates for 2-level CA",
    )
    argp_create_ca.add_argument(
        "--ca-cn-prefix",
        help="commonName prefix for the CA to be created",
        default="Demo Manufacturer",
    )
    argp_create_ca.set_defaults(action=cmd_create_ca)

    argp_issue_cert = subp.add_parser(
        "issue-cert", parents=[argp_common, argp_ca], help="issue a certificate"
    )
    argp_issue_cert.add_argument(
        "--csr",
        help="path to CSR file",
        required=True,
    )
    argp_issue_cert.set_defaults(action=cmd_issue_cert)

    argp_validate = subp.add_parser(
        "validate", parents=[argp_ca], help="validate a certificate chain"
    )
    argp_validate.add_argument(
        "chain",
        nargs="+",
        help="path to the certificate of the end entity followed by intermediates",
    )
    argp_validate.set_defaults(action=cmd_validate_cert)

    cmd = subp.add_parser(
        "write-field-entropy",
        parents=[argp_common],
        help="setup: provision field entropy",
    )
    cmd.add_argument(
        "--use-tmc",
        action="store_true",
        help="use the on-device TMC to generate field entropy",
    )
    cmd.set_defaults(action=cmd_write_field_entropy)

    cmd = subp.add_parser(
        "export-idevid-csr", parents=[argp_common], help="setup: export the IDevID CSR"
    )
    cmd.set_defaults(action=cmd_export_idevid_csr)

    cmd = subp.add_parser(
        "import-idevid-cert-chain",
        parents=[argp_common, argp_ca],
        help="setup: import the IDevID certificate chain",
    )
    cmd.set_defaults(action=cmd_import_idevid_cert_chain)

    cmd = subp.add_parser(
        "provision",
        parents=[argp_common, argp_ca],
        help="setup: one-stop shop provisioning",
    )
    cmd.set_defaults(action=cmd_provision)

    cmd = subp.add_parser(
        "export-owner-csrs", parents=[argp_common], help="rt: export owner CSRs"
    )
    cmd.add_argument(
        "--outdir",
        help="directory to store exported CSRs",
        required=True,
        type=Path,
    )
    cmd.set_defaults(action=cmd_export_owner_csrs)

    cmd = subp.add_parser(
        "export-idevid-cert-chain",
        parents=[argp_common],
        help="rt: export the IDevID certificate chain",
    )
    cmd.add_argument(
        "--outdir",
        help="directory to store the exported certificates",
        required=True,
        type=Path,
    )
    cmd.set_defaults(action=cmd_export_idevid_cert_chain)

    cmd = subp.add_parser(
        "update-field-entropy",
        parents=[argp_common],
        help="rt: provision new field entropy",
    )
    cmd.set_defaults(action=cmd_update_field_entropy)

    cmd = subp.add_parser(
        "rt-exit", parents=[argp_common], help="rt: stop the runtime container"
    )
    cmd.set_defaults(action=cmd_exit)
    return argp.parse_args()


def main():
    opts = parse_args()
    if not opts.action:
        return "a subcommand is required"

    # If stdio is requested, replace input and output with their
    # underlying binary-io buffers.
    if "input" in opts and opts.input is sys.stdin:
        opts.input = sys.stdin.buffer
    if "out" in opts and opts.out is sys.stdout:
        opts.out = sys.stdout.buffer

    logging_env_config()
    if opts.verbose:
        level = logging.DEBUG if opts.verbose == 2 else logging.INFO
        logging.getLogger().setLevel(level)

    try:
        return opts.action(opts)
    except Exception as e:  # pylint: disable=broad-except
        if logging.getLogger().isEnabledFor(logging.DEBUG):
            traceback.print_exc()
        return f"{opts.action.__name__}: error: {e!r}"


if __name__ == "__main__":
    sys.exit(main())
