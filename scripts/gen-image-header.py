#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Create CMRT image header, first 32bit word has the length of the
# image, next 32bit word has the length inverted.
#
import sys
import struct

def main(argv):
    if len(sys.argv) != 3:
        raise SystemExit(f"\nUsage: {sys.argv[0]} input.img output.img\n")

    # 32'size || 32'~size || dummay8 || data
    data = open(argv[1], "rb").read()
    size = len(data)
    open(argv[2], "wb").write(struct.pack("<ll", size, ~size) + b'\x00' * 8 + data)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
