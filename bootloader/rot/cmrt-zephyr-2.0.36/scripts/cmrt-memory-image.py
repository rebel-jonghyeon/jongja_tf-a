#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2020 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

# Options a bit more detail:

# output file mandatory, the file where changes are applied

# input file, if given will be inserted to given seek offset
# in output file -- without --seek will be inserted at the
# beginning of the file. output file size may enlarge if input
# file is large enough.

# with --size, output file of this size will be created, or if output
# file exists, its size will be adjusted to match (using truncate(2))

# with --clear, the given amount of bytes in output file will be zeroed
# from seek position onward -- bytes from input file are not affected.
# this clear max to the size of output file -- and it is possible to
# enter --clear=max to clear up to the end of the file.

# with --unlink, if output file existed it will be unlinked first
# -- new file created will have new inode (and old references
# (if any) to the previous file will not be affected)

# the options listed above are "core features"; the following are
# "user convenience options" which just adjust "core features" options


import argparse
import os


def _na(ns):
    s = ns[-1]
    if s in ('k', 'K'): m = 1024; ns = ns[:-1]
    elif s in ('m', 'M'): m = 1024 * 1024; ns = ns[:-1]
    else: m = 1
    return int(ns, 0) * m


def _nam(ns):
    if ns == 'max': return 2 ** 64
    return _na(ns)


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--of', '-o', help='output file (required)', required=True)
    # '-of' added for protecting user error -- not much use as above required
    p.add_argument('-of', dest='of', help=argparse.SUPPRESS)
    p.add_argument('--if', '-i', help='input file')
    # like '-of', but this can actually be given -- safe and convenient
    p.add_argument('-if', dest='if', help=argparse.SUPPRESS)

    p.add_argument('--size', help='output file size',
                   type=_na, default=0)

    p.add_argument('--seek', help='position write file offset',
                   type=_na, default=0)

    p.add_argument('--clear', help='clear bytes to zero',
                   type=_nam, default=0)

    p.add_argument('--unlink', help='unlink file before re-creation',
                   action='store_true', default=False)

    args = p.parse_args()

    ifile = getattr(args, 'if') # args.if gives syntax error
    if ifile:
        if not os.path.exists(ifile):
            raise SystemExit(f"'{ifile}': no such file")

        isize = os.path.getsize(ifile)
        if isize > 10 * 1024 * 1024:
            raise SystemExit(f"'{isize}': suspiciously large '{ifile}'")
        idata = open(ifile, 'rb').read()
        if len(idata) != isize:
            rlen = len(idata)
            raise SystemExit(
                f"'{ifile}': read size difference: {rlen} != {isize}, ")
        pass

    if os.path.isfile(args.of):
        if args.unlink:
            args.clear = 0
            os.unlink(args.of)
            print(f"Removed previous '{args.of}'")
            pass
        pass
    else:
        args.clear = 0
        pass

    ofd = os.open(args.of, os.O_RDWR | os.O_CREAT, 0o644)
    if args.size:
        os.ftruncate(ofd, args.size)
    else:
        args.size = os.fstat(ofd).st_size
        pass
    if args.seek:
        os.lseek(ofd, args.seek, os.SEEK_SET)
        pass

    if ifile:
        # note: this may enlarge size...
        os.write(ofd, idata)
        if args.seek:
            print(f"Inserted '{ifile}', {isize} bytes at offset {args.seek}.")
        else:
            print(f"Inserted '{ifile}', {isize} bytes.")
            pass
        args.seek += isize
        if args.clear:
            args.clear -= isize
            pass
        pass

    if args.clear > 0:
        # ... but for clear, no size increase
        if args.clear + args.seek > args.size:
            args.clear = args.size - args.seek
            pass

        if args.clear > 0:
            os.write(ofd, bytes(args.clear))
            if args.seek:
                print(f"Cleared {args.clear} bytes at offset {args.seek}.")
            else:
                print(f"Cleared {args.clear} bytes.")
                pass
            pass
        pass
    args.size = os.fstat(ofd).st_size
    print(f"Wrote '{args.of}'. Size {args.size}.")
    os.close(ofd)
    pass


if __name__ == '__main__':
    main()
    pass
