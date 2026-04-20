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

import math
import json

from UserDict import DictMixin


##
## Instruction formatting
##
## Keys are opcode name
##
## Values are ordered list of argument specifiers:
##   (argname, argtype, argsigned, msb, lsb)
##
## or with optional min/max fields to limit the range of an argument:
##   (argname, argtype, argsigned, msb, lsb, max, min)
##
## Arg specifiers are in the same order as the args appear in asm source
##
## Argtype is one of:
##   R: register
##   I: immediate value 
##   L: instruction address
##
## ArgSigned is one of:
##   True:  Value is treated as signed for instruction operation
##   False: Value is treated as unsigned for instruction operation
##   None:  Value is treated as unsigned for instruction operation, but for immediate values a signed immediate is legal
##
## Msb/Lsb are the argument's location in 32 bit machine code
##
## Max/Min can be optionally specified for immediate argtypes; a value of 'None' means the full bit range is legal
##

class InstructionFormatBase(object):
    def __init__(self,**kwargs):
        self.data = {}
        self.current = None
        self.sysdef = kwargs.get('sysdef')
        self.gen()


    def new(self,name):
        self.data[name] = list()
        self.sel(name)

    def sel(self,name):
        self.current = name

    def arg(self,argname,argtype,argsigned,msb,lsb,maxval=None,minval=None):
        self.data[self.current].append((argname,argtype,argsigned,msb,lsb,maxval,minval))

    def gen(self):
        
        # Special cases first
        
        self.new( 'invalid' )
        self.arg( 'data',              'i', False, 47, 10)
        
        self.new( 'undefined' )
        self.arg( 'data',              'i', False, 47, 10)


class IF_original (InstructionFormatBase):

    def gen(self):

        super(IF_original,self).gen()

        # Normal instruction set
        
        self.new( 'add' )
        self.arg( 'dstreg',            'r', True,  46, 42)
        self.arg( 'srcreg',            'r', True,   9,  5)
        self.arg( 'value',             'i', True,  41, 10)

        self.new( 'and' )
        self.arg( 'dstreg',            'r', False, 46, 42)
        self.arg( 'srcreg',            'r', False,  9,  5)
        self.arg( 'value',             'i', False, 41, 10)

        self.new( 'xor' )
        self.arg( 'dstreg',            'r', False, 46, 42)
        self.arg( 'srcreg',            'r', False,  9,  5)
        self.arg( 'value',             'i', False, 41, 10)

        self.new( 'set' )
        self.arg( 'dstreg',            'r', None,  46, 42)
        self.arg( 'value',             'i', None,  41, 10)

        self.new( 'shiftreg' )
        self.arg( 'dstreg',            'r', False, 46, 42)
        self.arg( 'srcreg1',           'r', False,  9,  5)
        self.arg( 'srcreg2',           'r', True,  14, 10)

        self.new( 'xorreg' )
        self.arg( 'dstreg',            'r', False, 46, 42)
        self.arg( 'srcreg1',           'r', False,  9,  5)
        self.arg( 'srcreg2',           'r', False, 14, 10)

        self.new( 'jsr' )
        self.arg( 'line_number',       'l', False, 19, 10)

        self.new( 'jump_not0' )
        self.arg( 'regno',             'r', False,  9,  5)
        self.arg( 'line_number',       'l', False, 19, 10)

        self.new( 'ret' )

        self.new( 'mem_read' )
        self.arg( 'start_reg',         'r', False,  9,  5)
        self.arg( 'length_reg',        'r', False, 14, 10)
        self.arg( 'step',              'i', True,  17, 15,    2,  -2)
        self.arg( 'iv',                'i', False, 47, 47)
        self.arg( 'ap',                'i', False, 41, 41)
        self.arg( 'up',                'i', False, 40, 40)

        self.new( 'mem_write' )
        self.arg( 'start_reg',         'r', False,  9,  5)
        self.arg( 'length_reg',        'r', False, 14, 10)
        self.arg( 'step',              'i', True,  17, 15,    2,  -2)
        self.arg( 'iv',                'i', False, 47, 47)
        self.arg( 'ap',                'i', False, 41, 41)
        self.arg( 'up',                'i', False, 40, 40)

        self.new( 'refsb' )
        self.arg( 'regno',             'r', False, 9,   5)

        self.new( 'halt' )


class IF_memory (IF_original):

    def gen(self):

        super(IF_memory,self).gen()
        
        self.current = 'mem_read'
        self.arg( 'or',                'i', False, 39, 39)

        self.current = 'mem_write'
        self.arg( 'or',                'i', False, 39, 39)

        self.current = 'refsb'
        self.arg( 'ad',                'i', False, 40, 40)
        self.arg( 'or',                'i', False, 39, 39)



def get_instruction_set(sysdef):
    name = sysdef.get('instruction_set','IF_memory')
    instr_class = { 
        'IF_original'     : IF_original,
        'IF_memory' : IF_memory,
    }[name]
    return instr_class(sysdef=sysdef)



opcodes = {
    'add'       : 0b00001,
    'and'       : 0b00010,
    'xor'       : 0b00011,
    'set'       : 0b00100,
    'shiftreg'  : 0b00110,
    'xorreg'    : 0b00111,
    'jsr'       : 0b01000,
    'jump_not0' : 0b01001,
    'ret'       : 0b01010,
    'mem_read'  : 0b01100,
    'mem_write' : 0b01101,
    'refsb'     : 0b01110,
    'halt'      : 0b11111,
}


registers = {
    'baseaddr' : 0b11101,
    'errcnt'   : 0b11110,
    'cmdstat'  : 0b11111,
}


# Inverse lookups
mnemonics = None
regnames  = None

# Operative system definition
sysdef    = None

# Global instruction format
instr_format = None

# Bit encoded exceptions; order is defined by simulation trace bitmap
exceptions = (
    'add_overflow'       ,
    'add_underflow'      ,
    'stack_overflow'     ,
    'stack_underflow'    ,
    'm_b_len_overflow'   ,
    'pc_overflow'        ,
    'undefined_register' ,
    'invalid_opcode'     ,
    'undefined_opcode'   ,
    'inst_count_overflow',
    'invalid_m_b_size'   ,
)


def load_sysdef(sysdef_json,**kwargs):
    result = {}

    if sysdef_json is not None:
        with file(sysdef_json) as inf:
            result = no_unicode( json.loads(inf.read()) )
        
    # Apply any overrides:
    result.update(kwargs)

    apply_sysdef(**result)


def scrub_sysdef(sysdef):
    for k,v in sysdef.iteritems():
        convert_type = {
            'instruction_set': str,
        }.get(k,number)
        sysdef[k] = convert_type(v)
    

    # List of parameters affecting system configuration
    sysdef.setdefault('burst_size_width',16)
    sysdef.setdefault('instruction_addr_width',6)
    sysdef.setdefault('instruction_count_addr_width',50)
    sysdef.setdefault('num_regs',16)
    sysdef.setdefault('mem_addr_increment',4)
    
    sysdef['ir_depth']       = 2**sysdef['instruction_addr_width']
    sysdef['max_ic']         = 2**sysdef['instruction_count_addr_width'] - 1
    sysdef['max_burst_size'] = 2**sysdef['burst_size_width']

    assert sysdef['num_regs'] >= 4
    assert sysdef['num_regs'] <= 29


def apply_sysdef(**kwargs):
    
    global sysdef
    global instr_format
    global opcodes
    global mnemonics
    global regnames

    sysdef = kwargs

    scrub_sysdef(sysdef)

    for n in range(sysdef['num_regs']):
        regname = "r{0}".format(n)
        if not registers.has_key(regname):
            registers[regname] = n


    instruction_set = get_instruction_set( sysdef )
    instr_format    = instruction_set.data

    # Keep opcodes and instr_format data synchronized:
    assert set(instr_format) == (set(opcodes) | set(['invalid','undefined']))

    # Generate inverse lookup tables
    mnemonics = { v:k for (k,v) in opcodes.iteritems() }
    regnames  = { v:k for (k,v) in registers.iteritems() }



def arg_format_dict(arg_spec_i):
    arg_labels = ('name', 'type', 'signed', 'msb', 'lsb', 'max', 'min')
    arg_spec   = arg_spec_i + (None,)*(len(arg_labels)-len(arg_spec_i))
    return dict( zip( arg_labels, arg_spec ) )



def make_logmask(width):
    val=0
    while (width > 0):
        val = (val << 1) | 0x1
        width = width - 1
    return val


## Convert fixed with number to python signed integer
def signed(n,bits=None):
    if bits is None or n < 0:
        return n
        
    # Handle negative numbers
    msb = 0x1 << (bits-1)
    if (n & msb) == 0:
        return int(n)

    mask = make_logmask(bits)

    return int(-((n ^ mask) + 1))


def number(s):
    if type(s) in (int,long):
        return s

    base = 10
    if s.startswith('0x'):
        base = 16
    elif s.startswith('0b'):
        base = 2
    return int(s,base)


## Both of these functions presume a signed value

def most_positive_int(bits=None):
    return make_logmask(bits - 1)

def most_negative_int(bits=None):
    return -most_positive_int(bits) - 1



def auto_radix(val,width=None,is_signed=False):

    if is_signed:
        return str(signed(val,bits=width))

    if val > 9:
        return "0x{0:x}".format(val)
    if width is not None and val < -9:
        return "0x{0:x}".format(make_logmask(width) & val)

    return str(val)
    

##
## InstructionArgs class:
##  * emulates an ordered dictionary
##  * provides correct argument format
##
class InstructionArgs(DictMixin,object):
    def __init__(self,mnemonic,**kwargs):
        self.mnemonic = mnemonic
        self.spec     = instr_format[mnemonic]
        self.data     = { k[0]:None  for k in self.spec }
        self.rfile    = kwargs.get('rfile')

    def get_spec(self,arg):

        result = None
        for i in self.spec:
            if i[0] == arg:
                result = i
                break
        if result is None:
            raise Exception, "Unknown arg name {arg} to instruction {mnemonic}".format(mnemonic=self.mnemonic,arg=arg)
        
        return arg_format_dict(result)
        

    def keys(self):
        # Order is specified in spec data structure:
        return [ x[0] for x in self.spec ]

    def __iter__(self):
        return iter(self.keys())

    def iteritems(self):
        return [ (k,self[k]) for k in self ]

    def __getitem__(self,k):
        return self.data[k]

    def __setitem__(self,k,v):
        self.data[k] = v

    def __repr__(self):
        return repr({ n:self[n] for n in self})

    def __str__(self):
        result = []
        for arg in self:
            val    = self[arg]
            strval = str(val)

            # Annotate reg values if available
            spec   = self.get_spec(arg)
            width  = spec['msb'] - spec['lsb'] + 1

            if self.rfile is not None and spec['type'] == 'r':
                rval   = self.rfile.get(val)
                if rval is None:
                    strval += ":None"
                else:
                    strval += ":" + auto_radix(rval,width=32,is_signed=spec['signed'])

            elif spec['type'] == 'i':
                strval = auto_radix(val,width=width,is_signed=spec['signed'])

            result.append(strval)
        return ", ".join(result)

##
## Instruction class
##  * abstract representation of an instruction
##  * used for internal manipulation as well as assembly/disassembly
##
class Instruction(object):
    def __init__(self,**kwargs):
        self.ln         = kwargs.get('ln')
        self.offset     = kwargs.get('offset')
        self.mnemonic   = kwargs.get('mnemonic')
        self.mcode      = kwargs.get('mcode')
        self.immediate  = kwargs.get('immediate')

        if self.mnemonic is not None:
            self.args = InstructionArgs(self.mnemonic,rfile=kwargs.get('rfile'))

        # Automatically disassemble if we are passed machine code
        if self.mcode is not None:
            self.disassemble(rfile=kwargs.get('rfile'))


    def __repr__(self):
        return repr({ k:v for (k,v) in self.__dict__.iteritems() if k not in ('format')})

    def __str__(self):
        ln = "" if (self.ln is None) else self.ln
        return "{0:5} {1:05x} {2:012x} {3} {4}".format(ln,self.offset,self.mcode,self.mnemonic,str(self.args))

    def assemble(self):

        if self.mcode is not None and self.immediate:
            return self.mcode

        result=0

        #print self

        result |= opcodes[self.mnemonic]

        for argname,argvalue in self.args.iteritems(): #arglist:
            spec = self.args.get_spec(argname)

            msb = spec['msb']
            lsb = spec['lsb']

            m = make_logmask(msb-lsb+1)

            result |= (argvalue & m) << lsb

        self.mcode = result

        return result


    def disassemble(self,**kwargs):

        mcode = self.mcode

        #print "disassemble {0:012x}".format(mcode)

        opcode        = mcode & make_logmask(5)
        self.mnemonic = mnemonics.get(opcode)

        if self.mnemonic is None:
            if opcode in (0,): 
                self.mnemonic = 'invalid'
            else:
                self.mnemonic = 'undefined'

        #print "mnemonic {0}".format(self.mnemonic)

        args = []

        for arg_spec_i in instr_format[self.mnemonic]:

            arg_spec  = arg_format_dict(arg_spec_i)
            arg_width = arg_spec['msb'] - arg_spec['lsb'] + 1
            arg_mask  = make_logmask(arg_width)  << arg_spec['lsb']
            arg_value = (mcode & arg_mask) >> arg_spec['lsb']

            #print "arg_value {0} arg_mask {1:x} arg_spec {2}".format(arg_value,arg_mask,arg_spec,)

            arg_repr = arg_value
            if arg_spec['type'] == 'r':
                if regnames.has_key(arg_value):
                    arg_repr = regnames[arg_value]
                else:
                    arg_repr = "0x{0:x}".format(arg_value)
                
            args.append((arg_spec['name'], arg_repr))
            #args.append((arg_spec['name'], regnames[arg_value] if arg_spec['type'] == 'r' else arg_value))

        
        self.args = InstructionArgs(self.mnemonic, rfile=kwargs.get('rfile'))
        self.args.update(dict(args))






##
## Assembler directives
##

class JSONEncoder(json.JSONEncoder):
    def default(self,o):
        try:
            return json.JSONEncoder.default(self,o)
        except:
            return o.to_json()


class Directive(object):
    def __init__(self,**kwargs):
        self.__dict__.update(**kwargs)

        if not self.__dict__.has_key('args'):
            self.parse_args()

    def parse_args(self):
        self.args = self.argstr.split()
        
    def __repr__(self):
        return repr(self.__dict__)

    def __str__(self):
        return "{0:5} {1:05x}              .{2} {3}".format(self.ln,self.offset,self.name,repr(self.args))

    def to_json(self):
        return dict(self.__dict__)


class UnknownDirective(Directive):
    pass


class InitRegDirective(Directive):
    def parse_args(self):
        Directive.parse_args(self)

        if len(self.args) != 2:
            raise ValueError, "InitRegDirective requires 2 arguments, got: {0!r}".format(self.args)

        self.regname = self.args[0]

        global registers
        if not registers.has_key(self.regname):
            raise ValueError, "InitRegDirective: unknown register {0!r}".format(self.regname)

        value = self.args[1]

        self.val = None
        m = re.search("^sysdef\((.+)\)$", value)
        if m:
            global sysdef
            self.val = sysdef[m.group(1)]
        else:
            self.val = number(value)


def get_initreg(dlist):
    regs = {}
    for d in dlist:
        if d.name != 'initreg':
            continue
        regs[registers[d.regname]] = d.val

    return regs

def initreg_memh(regs):
    result = []
    last = -1
    for r in sorted(regs):
        if last+1 < r:
            result.append("@{0:x}".format(r))
        result.append("{0:08x}".format(regs[r]))
        last = r

    return "\n".join(result)


class InstructionDirective(Directive):
    def parse_args(self):
        Directive.parse_args(self)

        if len(self.args) != 1:
            raise ValueError, "Incorrect number of arguments for InstructionDirective: {0!r}".format(self.args)

        self.machine_code = int(re.sub("^0x","",self.args[0]),16)

        if self.machine_code > make_logmask(48):
            raise ValueError, "Invalid instruction machine code passed to InstructionDirective: {0:x}".format(self.machine_code)



class ExceptionDirective(Directive):
    def parse_args(self):
        Directive.parse_args(self)
        
        if len(self.args) < 2:
            raise ValueError, "Insufficient arguments for ExceptionDirective: {0!r}".format(self.args)

        self.operator = self.args[0]
        self.operands = self.args[1:]

        if self.operator not in ("allow","disallow"):
            raise ValueError, "Unrecognized exception operation: {0} ".format(self.operator)


def resolve_symbol(s,**kwargs):
    s_r = kwargs.get('aliases',{}).get(s,s)

    if kwargs.has_key('regs') and kwargs['regs'].has_key(s_r):
        return kwargs['regs'][s_r]

    if kwargs.has_key('sysdef') and s_r.startswith('sysdef'):
        m = re.search("^sysdef\((.+)\)$", s_r)
        return kwargs['sysdef'][m.group(1)]

    return s_r

class AssertionDirective(Directive):
    def parse_args(self):
        Directive.parse_args(self)

        if len(self.args) != 3:
            raise ValueError, "Got invalid assertion arguments: {0!r}".format(self.args)
    
    def eval_expression(self,regs):
        global sysdef
        a = number(resolve_symbol(self.args[0], regs=regs, sysdef=sysdef, aliases=self.aliases)) & 0xffffffff
        b = number(resolve_symbol(self.args[2], regs=regs, sysdef=sysdef, aliases=self.aliases)) & 0xffffffff

        op = self.args[1]
    
        if op == '==': return a == b
        if op == '!=': return a != b
        if op == '<' : return a <  b
        if op == '>' : return a >  b
        if op == '<=': return a <= b
        if op == '>=': return a >= b

        raise ValueError, "Unknown operator {0}".format(op)


def mk_directive(**kwargs):
    directive = {
        'initreg'       : InitRegDirective,
        'instruction'   : InstructionDirective,
        'exception'     : ExceptionDirective,
        'assert'        : AssertionDirective,
    }.get(kwargs['name'], UnknownDirective)

    return directive(**kwargs)


## Convert unicode returned from json to ascii
def no_unicode(data):
    if isinstance(data, dict):
        return {no_unicode(k): no_unicode(v) for (k,v) in data.iteritems()}
    elif isinstance(data, list):
        return [no_unicode(element) for element in data]
    elif isinstance(data, unicode):
        return data.encode('utf-8')
    else:
        return data


def load_directives(directive_file):
    with file(directive_file) as fd:
        return [ mk_directive(**d) for d in no_unicode(json.loads(fd.read())) ]
