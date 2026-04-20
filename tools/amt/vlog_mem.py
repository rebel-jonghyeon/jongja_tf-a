#!/bin/env python2.7

## ------------------------- CONFIDENTIAL ----------------------------------
##
## Copyright (c) 2016 by Northwest Logic, Inc.
## All rights reserved.
##
## Trade Secret of Northwest Logic, Inc. Do not disclose.
##
## Use of this source code in any form or means is permitted only
## with a valid, written license agreement with Northwest Logic, Inc.
##
## Licensee shall keep all information contained herein confidential
## and shall protect same in whole or in part from disclosure and
## dissemination to all third parties.
##
##
## Northwest Logic, Inc.
## 1100 NW Compton Drive, Suite 100
## Beaverton, OR 97006, USA
##
## Ph: +1 503 533 5800
## Fax: +1 503 533 5900
## E-Mail: info@nwlogic.com
## www.nwlogic.com
##

import os
import re
import sys


comment_rx = re.compile("//.*")
addr_rx    = re.compile("@\s*([0-9a-fA-F_]+)")
data_rx    = re.compile("([0-9a-fA-F_]+)")


class VlogMem(object):
    def __init__(self,**kwargs):
        self.fname = kwargs.get('fname')
        self.radix = kwargs.get('radix',16)
        self.addr = 0
        self.data = {}
        self.digits = None
        self.parse()

    def __iter__(self):
        return iter(sorted(self.data))

    def __getitem__(self,k):
        return self.data[k]

    def __setitem__(self,k,v):
        self.data[k] = v

    def parse(self):
        with file(self.fname) as infile:
            self.digits = 0
            for line in infile:
                stripped = comment_rx.sub("",line).strip().replace("_","")

                if stripped == "":
                    continue

                m = addr_rx.search(stripped)
                if m:
                    self.addr = int(m.group(1),16)
                    continue
                
                m = data_rx.search(stripped)
                if m:
                    self.data[self.addr] = int(m.group(1),self.radix)
                    self.addr += 1
                    self.digits = max(self.digits,len(stripped))
                    continue

                raise ValueError, "Unrecognized data: {0}".format(stripped)
                
        
    def __repr__(self):
        return repr(self.data)


    def __str__(self):
        fmt = "{{0:{0}{1}}}".format(
            ""  if self.digits is None else "0" + str(self.digits),
            "b" if self.radix == 2 else "x",
        )

        result = []
        last = -1
        for addr in self:
            if addr != (last+1):
                result.append("\n@{0:x}".format(addr))
            result.append(fmt.format(self.data[addr]))
            last = addr

        return "\n".join(result)




def readmemh(fname):
    return VlogMem(fname=fname,radix=16)

def readmemb(fname):
    return VlogMem(fname=fname,radix=2)


if __name__ == '__main__':
    print "== sys.argv[1] =="
    print readmemh(sys.argv[1])
    print
    print "== sys.argv[2] =="
    print readmemb(sys.argv[2])

