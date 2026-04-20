#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2019 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# Calculate the sum of all NOBITS (bss, noinit) segments in ELF.
# This is needed to reserve space for such segments for binaries that are
# linked against fboot. This means sboot and tboot add-on in particular.
#
# Outputs zero bytes to be appended to the raw objcopy image.

import sys
import subprocess


def main():
    if len(sys.argv) != 2:
        raise SystemExit("Usage: %s {file}.elf" % sys.argv[0])

    relf = subprocess.Popen(('riscv32-unknown-elf-readelf', '-S', sys.argv[1]),
                            stdout=subprocess.PIPE)
    size = 0
    for line in relf.stdout:
        if b'NOBITS' not in line: continue
        #print(line)
        columns = line.split()
        size += int(columns[-6], 16)
        #print(columns[-6])
        pass
    relf.wait()
    if size != 0: sys.stdout.buffer.write(bytes(size))
    pass


if __name__ == '__main__':
    main()
    pass  # pylint: disable=W0107
