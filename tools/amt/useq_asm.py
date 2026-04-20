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
import json

from argparse import ArgumentParser

import useq_arch
import useq_mem_fmt

number   = useq_arch.number
signed   = useq_arch.signed


def bounds_check(**kwargs):
    # Signed can be None,True,False; see useq_arch for meaning
    signed = kwargs.get('signed')
    value  = kwargs.get('value')

    if signed or (signed is None and value < 0):
        if value > useq_arch.most_positive_int(kwargs['width']):
            raise ValueError, "signed value '{value}' larger than specified {width} bits".format(**kwargs)
        if value < useq_arch.most_negative_int(kwargs['width']):
            raise ValueError, "signed negative value '{value}' magnitude exceeds {width} bits".format(**kwargs)

    if signed in (None,False):
        if value > useq_arch.make_logmask(kwargs['width']):
            raise ValueError, "unsigned value '{value}' larger than specified {width} bits".format(**kwargs)
        if value < 0 and (signed is False): 
            raise ValueError, "unsigned value '{value}' cannot be a negative number".format(**kwargs)
    
    # Additional constraints
    if kwargs.get('max_val') and value > kwargs['max_val']:
        raise ValueError, "value '{value}' larger than specified maximum of {max_val}".format(**kwargs)

    if kwargs.get('min_val') and value < kwargs['min_val']:
        raise ValueError, "value '{value}' smaller than specified minimum of {min_val}".format(**kwargs)




class Assembler(object):
    def __init__(self,**kwargs):
        self.infile = None
        self.outfile = None
        self.odir = None
        self.__dict__.update(**kwargs)
        self.instructions = []
        self.directives = []
        self.labels  = {}
        self.aliases = {}

        self.asm_in = file(self.infile)
        self.fname  = self.infile
        

    def parse_program(self):

        comment_rx     = re.compile("//.*$")
        instruction_rx = re.compile("^([^\s]+)\s*(.+)?\s*$")
        label_rx       = re.compile("^([A-Za-z0-9_]+):$")
        alias_rx       = re.compile("^([A-Za-z0-9_]+)\s*=\s*([-A-Za-z0-9_]+)")
        directive_rx   = re.compile("^\.([A-Za-z0-9_]+)\s+(.+)$")

        ln = 0
        for line in self.asm_in:
            ln+=1

            stripped = comment_rx.sub("",line).strip()

            #print stripped

            # Skip blank lines
            if stripped == "":
                continue
        
            m = alias_rx.search(stripped)
            if m:
                #print "Got alias {0!r}".format(m.groups())
                if self.aliases.has_key(m.group(1)):
                    msg = "{fname}:{ln}: Alias {alias} already exists"
                    raise ValueError, msg.format(fname=self.fname, ln=ln, alias=m.group(1))

                self.add_alias(m.group(1), m.group(2), fname=self.fname, ln=ln)
                continue

            m = label_rx.search(stripped)
            if m:
                #print "Got label {0!r}".format(m.groups())
                if self.labels.has_key(m.group(1)):
                    msg = "{fname}:{ln}: Label {label} already exists"
                    raise ValueError, msg.format(fname=self.fname, ln=ln, label=m.group(1))

                self.add_label(m.group(1), len(self.instructions), ln=ln, fname=self.fname)
                continue

            m = directive_rx.search(stripped)
            if m:
                #print "Got directive {0!r}".format(m.groups())
                self.directives.append( self.parse_directive(m.group(1),m.group(2),ln,len(self.instructions) ) )
                continue

            m = instruction_rx.search(stripped)
            if m:
                #print "Got instruction {0!r}".format(m.groups())
                if m.group(1) not in useq_arch.instr_format.keys():
                    raise SyntaxError, "{fname}:{ln}: Unrecognized instruction: {stripped}".format(fname=self.fname, ln=ln, stripped=stripped)
                self.instructions.append( self.parse_instruction(m.group(1),m.group(2),ln,len(self.instructions) ) )
                continue

            raise SyntaxError, "{fname}:{ln}: Unrecognized data: {stripped}".format(fname=self.fname, ln=ln, stripped=stripped)

        
    def add_alias( self, name, target, **kwargs ):
        if name in useq_arch.opcodes:
            raise ValueError, "{fname}:{ln}: Alias '{0}' is a keyword".format(name, **kwargs)
        self.aliases[name] = target

    def add_label( self, name, target, **kwargs ):
        if name in useq_arch.opcodes:
            raise ValueError, "{fname}:{ln}: Label '{0}' is a keyword".format(name, **kwargs)
        self.labels[name] = target


    def parse_directive( self, name, argstr, ln, offset ):

        d = useq_arch.mk_directive(
            name     = name,
            argstr   = argstr,
            ln       = ln,
            offset   = offset,
            aliases  = self.aliases,
        )

        if type(d) is useq_arch.UnknownDirective:
            raise SyntaxError, "{fname}:{ln}: Unknown directive: {d}".format(fname=self.fname, ln=ln, d=d)


        if d.name == 'instruction':
            self.instructions.append(useq_arch.Instruction(mcode=d.machine_code,immediate=True))

        return d
            

    def parse_instruction( self, mnemonic, argstr, ln, offset ):
        
        result = useq_arch.Instruction(
            mnemonic = mnemonic,
            ln       = ln,
            offset   = offset,
        )

        if not useq_arch.instr_format.has_key(mnemonic):
            msg = "{fname}:{ln}: Unknown instruction {mnemonic}"
            raise SyntaxError, msg.format(fname=self.fname,**result.__dict__)

        argnames = list(result.args)
        arglist  = () if argstr is None else [ x.strip() for x in argstr.split(',') ]

        if len(argnames) != len(arglist):
            msg = "{fname}:{ln}: Got {n} args for instruction {mnemonic} with arity {arity}"
            raise SyntaxError, msg.format(fname=self.fname,
                                          arity=len(argnames),
                                          n=len(arglist),
                                          **result.__dict__)

        # interpolate aliases, convert immediate values to integers
        registers = useq_arch.registers
        arglist_interp = []
        for (arg_orig, arg_name) in zip(arglist,argnames):
            fmt = result.args.get_spec(arg_name)

            if fmt['type'] == 'r':
                arg = self.aliases.get(arg_orig,arg_orig)
                if not registers.has_key(arg):
                    msg = "{fname}:{ln}: instruction {mnemonic} argument {argname} refers to non-existent register '{regname}'"
                    raise SyntaxError, msg.format(fname=self.fname,argname=arg_name,regname=arg,**result.__dict__)
                arg = registers[arg]

            elif fmt['type'] == 'i':
                arg = self.aliases.get(arg_orig,arg_orig)
                try:
                    arg = number(arg)
                    bounds_check(
                        value   = arg, 
                        width   = fmt['msb']-fmt['lsb']+1, 
                        signed  = fmt['signed'], 
                        max_val = fmt['max'],
                        min_val = fmt['min'],
                    )
                except Exception as e:
                    msg = "{fname}:{ln}: instruction '{mnemonic}' argument '{argname}' of type '{argtype}': {0}"
                    raise TypeError, msg.format(repr(e),fname=self.fname,argname=arg_name,argtype=fmt['type'],**result.__dict__)

            else:
                arg = arg_orig

            arglist_interp.append(arg)


        result.args.update(dict(zip(argnames,arglist_interp)))

        return result


    def translate_program( self ):
        
        # Resolve Labels
        # Convert numeric arguments to integers

        self.machine_code = useq_mem_fmt.NativeFormat()

        for instr in self.instructions:
            new_arglist=[]

            for argname,argvalue in instr.args.iteritems(): #get_arglist():
                fmt = instr.args.get_spec(argname)
    
                if fmt['type'] == 'l':
                    if not self.labels.has_key(argvalue):
                        msg = "{fname}:{ln}: instruction {mnemonic} arg {argname} refers to non-existent label {argvalue}"
                        raise SyntaxError, msg.format(fname=self.fname,
                                                      argname=argname,
                                                      argvalue=argvalue,
                                                      **instr.__dict__)
                    argvalue = self.labels[argvalue]

                new_arglist.append((argname,argvalue))

            instr.args.update(dict(new_arglist))

            self.machine_code.append(instr.assemble())


    def check_program(self):
        program_size = len(self.machine_code)
        ir_depth     = useq_arch.sysdef['ir_depth']
        if program_size > ir_depth:
            raise ValueError, "Program size {0} exceeds instruction ram depth of {1}".format(program_size, ir_depth)

        invalid_labels = [l for l in self.labels if self.labels[l] > (program_size-1)]
        if len(invalid_labels) > 0:
            raise ValueError, "Labels defined after end of program text: {0}".format(invalid_labels)
        


    def write_output(self):

        result     = useq_mem_fmt.convert('native', self.format, self.machine_code)
        directives = json.dumps(self.directives , cls=useq_arch.JSONEncoder, ensure_ascii=True)

        if self.outfile is not None:
            output_base = re.sub("\.[^\.]+$", "", self.outfile)
        else:
            output_base = re.sub("\.[^\.]+$", "", self.infile)
            if self.odir is not None:
                output_base = os.path.basename(output_base)
                output_base = "/".join((self.odir,output_base))
            self.outfile = output_base + useq_mem_fmt.get_extension(self.format)

        with file(self.outfile,'w') as of:
            of.write(result)
            of.write('\n')

        directive_file = output_base + "_directives.json"
        with file(directive_file,'w') as of:
            of.write(directives)
            of.write('\n')
    
        initreg_file = output_base + "_initreg.memh"
        with file(initreg_file,'w') as of:
            of.write(useq_arch.initreg_memh(useq_arch.get_initreg(self.directives)))
            of.write('\n')


def mk_parser():
    parser=ArgumentParser(description="Rambus Microsequencer Assembler v1.01")
    parser.add_argument( "-i", "--infile",  required=True, help="input instruction filename" )
    parser.add_argument( "-o", "--outfile",                help="output machine code filename" )
    parser.add_argument( "--format",        
                         default='verilog', 
                         choices=('intel_hex','verilog'),  help="file format for output file" )
    parser.add_argument( "--sysdef",                       help="json system definition file" )
    return parser



def main():
    parser = mk_parser()
    options = parser.parse_args()

    useq_arch.load_sysdef(options.sysdef)

    asm = Assembler(
        infile  = options.infile,
        outfile = options.outfile,
        format  = options.format,
    )

    asm.parse_program()
    asm.translate_program()
    asm.check_program()
    asm.write_output()




if __name__ == '__main__':
    main()
