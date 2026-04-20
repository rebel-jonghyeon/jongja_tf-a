#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Output ROM footer which is SHA256 of the image data.
#
import sys
import hashlib

def main(argv):
    if len(sys.argv) != 2:
        raise SystemExit(f"\nUsage: {sys.argv[0]} input.raw\n")

    data = open(argv[1], "rb").read()
    digest = hashlib.sha256(data).digest()
    sys.stdout.buffer.write(digest)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
