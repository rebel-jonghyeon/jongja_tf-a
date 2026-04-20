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

from UserDict import DictMixin

import argparse

import useq_mem_fmt
import useq_arch

try:
    import useq_trace_diff
except:
    pass

if os.getenv("NWL_IP_DIR") is not None:
    sys.path.append(os.path.join(os.getenv("NWL_IP_DIR"),"scripts/pythonlib"))

import vlog_mem

signed = useq_arch.signed
number = useq_arch.number


def fmt_regval(rname,n):
    fmt = ""
    if n is not None:
        fmt = "0x{1:08x} {0: 11}".format(0xffffffff & n, n)
        if signed(n,32) < 0:
            fmt += " ({0})".format(signed(n,32))

    return "{0:>14}: {1}".format(rname,fmt)



class RegisterFileBase(DictMixin,object):
    def __init__(self,**kwargs):
        self.emulator  = kwargs['emulator']
        self.registers = useq_arch.registers        
        self.simtrace  = kwargs.get('simtrace')
        self.schedule  = {}

        self.data = { k:None for k in self.registers }

        self.initregs()

        if kwargs.get('initdata') is not None:
            for k in kwargs['initdata']:
                # translate from numeric register address to symbolic name
                k_name = useq_arch.regnames.get(k,k)
                if not self.data.has_key(k_name):
                    raise ValueError, "Unrecognized register {0} from init file.".format(k)
                self.data[k_name] = kwargs['initdata'][k]


    def initregs(self):
        pass

    def do_reg_write(self,r,v):
        return

    def add_event(self,when,thunk):
        #print "add_event {0} {1}".format(when,thunk.__name__)
        if when <= self.emulator.ic:
            raise ValueError, "tried to add an event to the past"
        self.schedule.setdefault(when,list())
        self.schedule[when].append(thunk)

    def do_events(self,ic):
        for event in self.schedule.get(ic,()):
            #print "do_events {0} {1}".format(ic,event.__name__)
            event()

    def keys(self):
        r     = self.registers
        cmp_r = lambda a,b: cmp(r[a],r[b])
        return sorted(r,cmp=cmp_r)

    def __iter__(self):
        return iter(self.keys())

    def __getitem__(self,k):
        return self.data[k]

    def __setitem__(self,r,v_in):

        v = self.do_reg_write(r,v_in)

        # NOTE: We are tracing register value transitions, not transactions
        if self.simtrace is not None:
            self.simtrace.add(
                count = self.emulator.ic,
                addr  = self.emulator.ip,
                reg   = r,
                val   = 0xffffffff & v,
            )


    def __str__(self):
        return "\n".join([ fmt_regval(k,v) for (k,v) in self.iteritems() ])


class DefaultRegisterFile(RegisterFileBase):

    def initregs(self):
        self.data['baseaddr'] = 0x0
        self.data['errcnt']   = 0x0
        self.data['cmdstat']  = 0x0


    def do_reg_write(self,r,v_in):

        # special reg behavior
        v = v_in
        if r == 'cmdstat':  v = 0
        if r == 'baseaddr': v = v_in & 0x000000ff
        if r == 'errcnt':   v = v_in & 0x0000ffff
        self.data[r] = v

        return v



def get_register_file(**kwargs):

    if kwargs.get('custom_rfile') is None:
        return DefaultRegisterFile

    custom_rfile = os.path.abspath(kwargs['custom_rfile']).replace('\\','/')

    print "INFO: Loading custom rfile from {0}".format(custom_rfile)

    execfile(custom_rfile,globals())
    
    return CustomRegisterFile


def index_directives(dlist):
    result = {}
    for d in dlist:
        result.setdefault(d.offset,list())
        result[d.offset].append(d)
    return result

class Emulator(object):
    def __init__(self,**kwargs):
        self.trace      = kwargs.get('trace')
        self.simtrace   = kwargs.get('simtrace')
        self.directives = index_directives(kwargs.get('directives',list()))
        self.reg        = kwargs.get('rfile',DefaultRegisterFile)(initdata=kwargs.get('reginit'),simtrace=kwargs['simtrace'],emulator=self)
        self.ip         = 0  # instruction pointer
        self.ic         = 0  # instruction count
        self.stack      = [] # call stack
        emulator_only_exceptions = ('general','invalid_step_size')
        self.exceptions = { e:None for e in emulator_only_exceptions + useq_arch.exceptions }
        self.halted     = False

        self.allowed_exceptions = set()

    def tracing(self,name):
        return (name in self.trace) or ('all' in self.trace)

    def numeric_exceptions(self):
        return { k:(0 if v is None else 1) for (k,v) in self.exceptions.iteritems() }

    def get_hw_exceptions(self):
        return [ (k,v) for k,v in self.exceptions.iteritems() if k in useq_arch.exceptions ]

    def get_emu_exceptions(self):
        return [ (k,v) for k,v in self.exceptions.iteritems() if k not in useq_arch.exceptions ]

    def exception_bitmap(self):
        result = 0
        for i in range(len(useq_arch.exceptions)):
            e = useq_arch.exceptions[i]
            if self.exceptions[e] is not None:
                result |= 0x1 << i
        return result

    def report_exception(self,name,instr):
        self.exceptions[name] = instr

        if self.simtrace is not None:
            self.simtrace.add(
                count = self.ic,
                addr  = self.ip,
                reg   = 'exception',
                val   = self.exception_bitmap(),
            )

        if name in self.allowed_exceptions:
            print "\n-> Allowed exception: {0}\n".format(name)
        else:
            raise ValueError, "{0}: {1}".format(name,instr)

    def failed(self):
        return any([ v is not None for (k,v) in self.exceptions.iteritems() if k not in self.allowed_exceptions ])

    def is_stopped(self,stop_at_ic=None):
        for e in self.exceptions:
            if self.exceptions[e] is not None:
                print "\n-> Execution stopped after {0} instructions due to exception: {1}\n".format(self.ic,e)
                return 1

        if (stop_at_ic is not None) and (self.ic >= stop_at_ic):
            print "\n-> Execution stopped after {0} instructions\n".format(self.ic)
            return 1

        return self.halted

    def execute(self,mcode,stop=None):

        if self.tracing('instructions'):
            print
            print "count  line  addr  instruction"
            print "======================================"

        try:
            self.apply_directives()
            while not self.is_stopped(stop_at_ic=stop):
                self.reg.do_events(self.ic)
                self.exec_instr( useq_arch.Instruction( offset=self.ip, mcode=mcode[self.ip], rfile=self.reg ) )
                if self.ip >= len(mcode) and not self.halted:
                    self.report_exception('pc_overflow',self.prev_instr)
                if self.ic > useq_arch.sysdef['max_ic']:
                    self.report_exception('inst_count_overflow',self.prev_instr)
                self.apply_directives()
                self.ic += 1
        except Exception as e:
            self.exceptions['general'] = e
            import traceback
            print traceback.format_exc()
            

    def exec_instr(self,instr):

        if self.simtrace is not None:
            self.simtrace.add(
                count = self.ic,
                addr  = self.ip,
                reg   = 'iar',
                val   = self.ip,
            )

        if self.tracing('instructions') or self.tracing(instr.mnemonic): 
            #print instr
            print "{0:5}  {1}".format(self.ic,instr)

        # Lookup self.do_xxx() where xxx is the instruction mnemonic
        method = getattr(self,"do_{0}".format(instr.mnemonic),None)
        if method is None:
            print "\nERROR: Unsupported instruction: {0:012x}\n\n{1}\n".format(instr.mcode,instr)
            sys.exit(1)

        # Advance the ip now, because some instructions will set it and we don't want to clobber that
        self.ip += 1

        # If the method exists, call it
        method(instr)

        self.prev_instr = instr


    def apply_directives(self):
        for d in self.directives.get(self.ip,()):
            if self.tracing('directives'): print "       {0}".format(d)
            
            if d.name == 'exception':
                if d.args[0] == 'allow':
                    self.allowed_exceptions.add(d.args[1])
                if d.args[0] == 'disallow':
                    self.allowed_exceptions.discard(d.args[1])
                continue

            if d.name == 'assert':
                regs = {}
                regs.update(self.reg)
                regs.update(self.numeric_exceptions())
                if not d.eval_expression(regs):
                    raise AssertionError, "{0}".format(d)

        
    def valid_registers(self,instr,*regs):
        for reg in regs:
            if not self.reg.has_key(reg):
                self.report_exception('undefined_register',instr)
                return False
        return True



    ## Instruction set implementation

    def do_invalid(self,instr):
        self.report_exception('invalid_opcode',instr)

    def do_undefined(self,instr):
        self.report_exception('undefined_opcode',instr)


    def do_add(self,instr):
        dstreg = instr.args['dstreg']
        srcreg = instr.args['srcreg']
        value  = instr.args['value']

        if not self.valid_registers(instr,dstreg,srcreg):
            return

        # NOTE: python uses bignums (infinite precision integers)
        result = signed(value,32) + signed(self.reg[srcreg],32)

        # Check for overflow
        if result > useq_arch.most_positive_int(bits=32):
            self.report_exception('add_overflow',instr)

        # Check for underflow
        if result < useq_arch.most_negative_int(bits=32):
            self.report_exception('add_underflow',instr)

        self.reg[dstreg] = result & 0xffffffff

    def do_and(self,instr):
        dstreg = instr.args['dstreg']
        srcreg = instr.args['srcreg']
        value  = instr.args['value']

        if not self.valid_registers(instr,dstreg,srcreg):
            return

        self.reg[dstreg] = value & self.reg[srcreg]

    def do_jsr(self,instr):
        line_number = instr.args['line_number']
        self.stack.append(self.ip)
        self.ip = line_number

        if len(self.stack) > 4:
            self.report_exception('stack_overflow',instr)



    def do_jump_not0(self,instr):
        regno       = instr.args['regno']
        line_number = instr.args['line_number']

        if not self.valid_registers(instr,regno):
            return

        if self.reg[regno] != 0:
            self.ip = line_number

    def do_mem_read(self,instr):
        start_reg  = instr.args['start_reg']
        length_reg = instr.args['length_reg']
        step       = instr.args['step']
        up         = instr.args['up']

        if not self.valid_registers(instr,start_reg,length_reg):
            return

        if self.reg[length_reg] == 0:
            self.report_exception('invalid_m_b_size',instr)
            return

        max_length = useq_arch.make_logmask(useq_arch.sysdef['burst_size_width'])

        if up:
            s_step = signed(step,3)

            if (s_step < -2) or (2 < s_step):
                self.report_exception('invalid_step_size',instr)

            self.reg[start_reg] += (max_length & self.reg[length_reg]) * s_step * useq_arch.sysdef['mem_addr_increment']

            if self.reg[start_reg] > useq_arch.make_logmask(32):
                self.report_exception('add_overflow',instr)

            if self.reg[start_reg] < 0:
                self.report_exception('add_underflow',instr)

        if self.reg[length_reg] > max_length:
            self.report_exception('m_b_len_overflow',instr)
            return


    def do_mem_write(self,instr):
        start_reg  = instr.args['start_reg']
        length_reg = instr.args['length_reg']
        step       = instr.args['step']
        up         = instr.args['up']

        if not self.valid_registers(instr,start_reg,length_reg):
            return

        if self.reg[length_reg] == 0:
            self.report_exception('invalid_m_b_size',instr)
            return

        max_length = useq_arch.make_logmask(useq_arch.sysdef['burst_size_width'])

        if up:
            s_step = signed(step,3)

            if (s_step < -2) or (2 < s_step):
                self.report_exception('invalid_step_size',instr)

            self.reg[start_reg] += (max_length & self.reg[length_reg]) * s_step * useq_arch.sysdef['mem_addr_increment']

            if self.reg[start_reg] > useq_arch.make_logmask(32):
                self.report_exception('add_overflow',instr)

            if self.reg[start_reg] < 0:
                self.report_exception('add_underflow',instr)

        if self.reg[length_reg] > max_length:
            self.report_exception('m_b_len_overflow',instr)
            return


    def do_refsb(self,instr):
        regno  = instr.args['regno']
        ad     = instr.args.get('ad')

        # verify that the register exists:
        if not self.valid_registers(instr,regno):
            return
        
        if ad == 1:
            self.reg[regno] = (self.reg[regno] - 1) & 0xffffffff

    def do_ret(self,instr):
        if len(self.stack) == 0:
            self.report_exception('stack_underflow',instr)
            return

        self.ip = self.stack.pop()

    def do_set(self,instr):
        dstreg = instr.args['dstreg']
        value  = instr.args['value']

        if not self.valid_registers(instr,dstreg):
            return

        self.reg[dstreg] = value

    def do_shiftreg(self,instr):
        srcreg1 = instr.args['srcreg1']
        srcreg2 = instr.args['srcreg2']
        dstreg  = instr.args['dstreg']

        if not self.valid_registers(instr,srcreg1,srcreg2,dstreg):
            return

        shiftamt = signed(self.reg[srcreg2],32)
        shift = abs(shiftamt) % 32
        if shiftamt < 0:
            shift = -shift

        if shift > 0:
            result = (self.reg[srcreg1] <<  shift)
            self.reg[dstreg] =  ((result & 0xffffffff00000000) >> 32) | (result & 0xffffffff)

        elif shift < 0:
            result = (self.reg[srcreg1] << 32) >> -shift
            self.reg[dstreg] =  ((result & 0xffffffff00000000) >> 32) | (result & 0xffffffff)
            
        else:
            self.reg[dstreg] = self.reg[srcreg1]


    def do_xor(self,instr):
        srcreg = instr.args['srcreg']
        value  = instr.args['value']
        dstreg = instr.args['dstreg']

        if not self.valid_registers(instr,srcreg,dstreg):
            return

        self.reg[dstreg] = value ^ self.reg[srcreg]

    def do_xorreg(self,instr):
        srcreg1 = instr.args['srcreg1']
        srcreg2 = instr.args['srcreg2']
        dstreg = instr.args['dstreg']

        if not self.valid_registers(instr,srcreg1,srcreg2,dstreg):
            return

        self.reg[dstreg] = self.reg[srcreg1] ^ self.reg[srcreg2]


    def do_halt(self,instr):
        self.halted = True


def get_input_data(options):

    if options.odir is not None and not os.path.exists(options.odir):
        os.makedirs(options.odir)

    infile = options.infile

    iformat = options.iformat
    if iformat is 'detect':
        if infile.endswith(".asm"):  
            iformat = 'asm'
        elif infile.endswith(".memh"):
            iformat = 'verilog'
        elif infile.endswith(".hex"):
            iformat = 'intel_hex'
        else: 
            print "ERROR: Could not detect input format from file {0}.  Use --format option.".format(infile)
            sys.exit(1)

    ## If input is source file, automatically assemble it
    if iformat == 'asm':
        print "INFO: Assembling {0}...".format(infile)
        import useq_asm
        asm = useq_asm.Assembler(
            infile  = infile,
            odir    = options.odir,
            format  = options.oformat,
        )
    
        asm.parse_program()
        asm.translate_program()
        asm.write_output()

        # Workaround for linux synchronization issue:
        #infile = asm.outfile
        return (asm.machine_code, asm.directives, useq_arch.get_initreg(asm.directives))

    ## Now read the machine code
    with file(infile) as fd:
        machine_code = useq_mem_fmt.convert(iformat,'native',fd.read())

    ## Get any directives, if a file exists for them
    directive_file = re.sub("\..+$","",infile) + "_directives.json"
    if os.path.isfile(directive_file):
        directives = useq_arch.load_directives(directive_file)
    else:
        directives = []

    ## Detect reginit file and load if it exists
    reginit_file = re.sub("\..+$","", infile) + "_initreg.memh"
    if os.path.exists(reginit_file):
        reginit = vlog_mem.readmemh(reginit_file)
    else:
        reginit = None



    return (machine_code, directives, reginit)


def mk_parser():
    parser=argparse.ArgumentParser(description="Rambus Microsequencer Emulator v1.01")
    parser.add_argument( "-i", "--infile",    required=True,                   help="input instruction filename" )
    parser.add_argument( "-t", "--trace",     default=list(), action='append', help="items to print during execution (instructions,directives,all)" )
    parser.add_argument( "--simtrace",                                         help="dump instruction trace suitable for comparing to verilog simulation" )
    parser.add_argument( "--sysdef",                                           help="json system definition file" )
    parser.add_argument( "--custom_rfile",                                     help="path to python file with custom rfile behavior" )
    parser.add_argument( "--odir",                                             help="output directory for generated files" )
    parser.add_argument( "-d", "--define",    default=list(), action='append', help=argparse.SUPPRESS ) # Override individual settings from json system definition file: -d var=val; for NWL testing only
    parser.add_argument( "-p", "--print",     
                         default=list(), 
                         action='append', 
                         dest='dump',
                                                                               help="items to print upon completion: registers,exceptions,all" )
    parser.add_argument( "--stop", type=int,                                   help="stop after n instructions" )
    parser.add_argument( "--iformat",        
                         default='detect', 
                         choices=('detect','asm','verilog','intel_hex',),
                                                                               help="Input file format.  When loading a rom or asm file, file format use (default is to 'detect' based on file extension)." )
    parser.add_argument( "--oformat",        
                         default='verilog', 
                         choices=('verilog','intel_hex'),
                                                                               help="Output file format.  When processing source (.asm), a rom file is generated in the specified format (defaults to 'verilog')." )
    return parser



def check_options(parser,options):

    valid_trace = ['all', 'instructions', 'directives'] + useq_arch.opcodes.keys()
    for o in options.trace:
        if o not in valid_trace:
            parser.print_usage()
            msg = "{prog}: error: cannot trace {o!r}, valid arguments to --trace:\n\n{valid}\n"
            print msg.format(prog  = parser.prog,
                             o     = o,
                             valid = "\n".join(valid_trace))
            sys.exit(1)

    valid_print = ('all', 'registers', 'exceptions')
    for o in options.dump:
        if o not in valid_print:
            parser.print_usage()
            msg = "{prog}: error: cannot print {o!r}, valid arguments to --print:\n\n{valid}\n"
            print msg.format(prog  = parser.prog,
                             o     = o,
                             valid = "\n".join(valid_print))
            sys.exit(1)


def main():

    parser = mk_parser()
    options = parser.parse_args()

    useq_arch.load_sysdef(options.sysdef, **{ x.split('=')[0]:x.split('=')[1] for x in options.define} )

    check_options(parser,options)

    (machine_code, directives, reginit) = get_input_data(options)

    # Pad machine code to instruction ram size
    machine_code = useq_mem_fmt.adjust_size(machine_code, depth=useq_arch.sysdef['ir_depth'], fill=lambda addr:0 )

    simtrace = None
    if options.simtrace:
        simtrace = useq_trace_diff.SimTrace()
        simtrace.fname = options.simtrace
        simtrace.new_test(re.sub("\..+$","",os.path.basename(options.infile)))


    emu = Emulator( 
        trace      = options.trace,
        directives = directives,
        rfile      = get_register_file(custom_rfile=options.custom_rfile),
        reginit    = reginit,
        simtrace   = simtrace
    )
    emu.execute(machine_code,stop=options.stop)

    if options.simtrace:
        import json
        with file(options.simtrace,'w') as of:
            of.write(json.dumps(emu.simtrace,cls=useq_arch.JSONEncoder))
            of.write("\n")


    if emu.failed() or ('registers' in options.dump) or ('all' in options.dump):
        print
        print "Registers"
        print "======================================================="
        print emu.reg
        print "======================================================="
        print fmt_regval("inst_count",emu.ic)

    if emu.failed() or ('exceptions' in options.dump) or ('all' in options.dump):
        print
        print "Hardware Exceptions"
        print "======================================================="
        print "\n".join([ "{0:>20}: {1}".format(k,v) for (k,v) in sorted( emu.get_hw_exceptions() ) ])
        print "======================================================="
        print
        print "Emulation Exceptions"
        print "======================================================="
        print "\n".join([ "{0:>20}: {1}".format(k,v) for (k,v) in sorted( emu.get_emu_exceptions() ) ])
        print "======================================================="

    sys.exit(1 if emu.failed() else 0)


if __name__ == '__main__':
    main()
