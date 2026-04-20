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

import useq_arch

from argparse import ArgumentParser

import UserList

## Use list emulation class so we can add attributes to the native format later if necessary

class NativeFormat(UserList.UserList):
    def __init__(self,**kwargs):
        self.data = kwargs.get('data',[])

    def __str__(self):
        return "\n".join([ "{0:012X}".format(d) for d in self.data ])


        

def partition(seq,size):
    return [ seq[i:i+size] for i in range(0,len(seq),size) ]

## Conversion Routines

## We rely on a generic verilog memory library for vlogmem conversion

def verilog_to_native(data,**kwargs):
    comment_rx = re.compile("//.+")
    result = NativeFormat()
    for d in data.splitlines():
        stripped = comment_rx.sub("",d).strip()
        if stripped == "":
            continue
        result.append(int(stripped,16))
    return result

def native_to_verilog(data,**kwargs):
    return str(data)


## Since intel hex format is more complex than we want to support at this time, 
## just implement the subset of functionality we care about:

def intel_hex_to_native(data,**kwargs):

    # Construct memory map from hex file lines

    memory = {}

    ln = -1
    for line in data.splitlines():
        stripped = line.strip()
        ln += 1
        if stripped == '':
            continue
        
        if stripped[0] != ':':
            raise ValueError, "Got unexpected data in file {0}:{1}".format(self.fname,ln)
    
        record     = stripped[1:]
        chk_data   = [ int(x,16) for x in partition(record[0:-2], 2) ]
    
        byte_count = chk_data[0]
        address    = int(record[2:6],16)
        rtype      = chk_data[3]
        data       = chk_data[4:]
        chksum     = int(record[-2:],16)
    
        #print "{0:>25} {1}".format(data_type[rtype],record)
        
        # Verify data byte count
        if byte_count != len(data):
            raise ValueError, "Expected {0} bytes in record, got {1} for data:{2}".format(byte_count,len(data),data)
    
        # Verify that byte count for data is 6; we only read hex files that were created by useq_asm
        if rtype == 0 and byte_count != 6:
            raise ValueError, "Expected byte count to be {0}, got {1}.".format(6,byte_count)

        # Verify checksum
        data_chksum = (~sum(chk_data)+1) & 0xff
        if data_chksum != chksum:
            raise ValueError, "Failed checksum {0}:{1} data:{2} expected:{3} got:{4}".format(self.fname,ln, data, chksum, data_chksum)
    
        if rtype == 0:
            memory[address]  = 0
            for i in range(6):
                memory[address] |= data[i] << ((5-i)*8)
        

    # Convert memory map to list of words (data should start at zero and be contiguous to be a valid hex file for useq):

    result = []
    last = -4
    for offset in sorted(memory):
        if offset != last+4:
            raise ValueError, "Memory gaps not supported by the microsequencer: last:{0:x} current:{1:x}".format(last,offset)
        result.append(memory[offset])
        last = offset


    return result


def native_to_intel_hex(data,**kwargs):
    result = []

    for offset in range(len(data)):
        data_string = "{bcount:02x}{address:04x}{rtype:02x}{data:012x}".format(
            bcount  = 6,
            address = offset<<2,
            rtype   = 0,
            data    = data[offset],
        )
        data_bytes = [ int(x,16) for x in partition(data_string,size=2)]
        result.append(
            ":{data}{cksum:02x}".format(
                data  = data_string,
                cksum = 0xff & (~sum(data_bytes)+1) & 0xff,
            )
        )

    result.append(":00000001FF")


    return "\n".join(result)

## Convenience function

conversion_map = {
    ('native',   'verilog')   : native_to_verilog,
    ('verilog',  'native')    : verilog_to_native,
    ('native',   'intel_hex') : native_to_intel_hex,
    ('intel_hex','native')    : intel_hex_to_native,
}

def convert(from_format,to_format,data,**kwargs):
    if 'native' not in (from_format,to_format):
        tmp1 = convert(data, from_format, 'native',  **kwargs)
        tmp2 = convert(tmp1, 'native',    to_format, **kwargs)
        return tmp2

    return conversion_map[from_format,to_format](data,**kwargs)
    

def mk_random_mcode():
    # Don't generate valid opcodes, it causes the disassembler to bomb,
    # and we want to test emulation behavior with random data

    import random
    import useq_arch
    valid_opcodes = useq_arch.mnemonics.keys()

    rand_op = 1
    while rand_op in valid_opcodes:
        rand_op = random.getrandbits(5)
    
    return (random.getrandbits(48-5) << 5) | rand_op


def adjust_size(data,**kwargs):
    depth = kwargs.get('depth')
    fill  = kwargs.get('fill',lambda addr: 0)

    if depth is None:
        return data

    if len(data) > depth:
        raise ValueError, "Requested depth of {0} instructions is smaller than ROM image of size {1}".format(depth,len(data))

    result = list(data)
    result.extend([ fill(addr) for addr in range(len(data),depth) ])

    return NativeFormat(data=result)


def get_extension(fmt):
    if fmt == 'verilog':   return ".memh"
    if fmt == 'intel_hex': return ".hex"
    raise ValueError, "Unknown rom format {0}".format(fmt)


## Standalone mode code

def mk_parser():
    parser=ArgumentParser()
    parser.add_argument( "-i", "--infile",                help="input instruction filename" )
    parser.add_argument( "-o", "--outfile",               help="output machine code filename" )
    parser.add_argument( "--iformat",        
                         choices=('intel_hex','verilog'), help="file format for output file" )
    parser.add_argument( "--oformat",        
                         choices=('intel_hex','verilog'), help="file format for output file" )
    return parser



def main():
    parser = mk_parser()
    options = parser.parse_args()

    print options

    #with fd as file(options.infile):
    #    machine_code = verilog_to_int(fd)

    print convert(iformat,oformat,data)


if __name__ == '__main__':
    main()
