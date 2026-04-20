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

from argparse import ArgumentParser

import useq_arch
import useq_mem_fmt





def mk_parser():
    parser=ArgumentParser(description="Rambus Microsequencer Disassembler v1.0")
    parser.add_argument( "-i", "--infile", required=True, help="input instruction filename" )
    parser.add_argument( "--format",        
                         default='detect', 
                         choices=('detect', 'intel_hex','verilog'), 
                                                          help="file format for input file" )
    parser.add_argument( "--sysdef",                      help="json system definition file" )
    return parser



def main():
    parser = mk_parser()
    options = parser.parse_args()

    useq_arch.load_sysdef(options.sysdef)

    format = options.format
    if format == 'detect':
        if   options.infile.endswith('.memh'):
            format = 'verilog'
        elif options.infile.endswith('.hex'):
            format = 'intel_hex'
        else:
            raise ValueError, "Could not detect input format from file {0}.  Use --format option.".format(options.infile)


    with file(options.infile) as fd:
        machine_code = useq_mem_fmt.convert(format,'native',fd.read())

    result = []

    for i in range(len(machine_code)):
        result.append(useq_arch.Instruction(offset=i,mcode=machine_code[i]))
    
    print "\n".join([ str(x) for x in result ])



if __name__ == '__main__':
    main()
