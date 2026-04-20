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
import itertools

import useq_arch

from argparse import ArgumentParser


start_rx = re.compile("^## Start of test (.+)$")
end_rx   = re.compile("^## End of test (.+)$")
pc_rx    = re.compile("^([0-9]+)\s+0x([0-9a-fA-F]+)$")
reg_rx   = re.compile("^([0-9]+)\s+0x([0-9a-fA-F]+)\s+([a-zA-Z_0-9]+):0x([0-9a-fA-F]+)$")


class SimStep(object):
    def __init__(self,data):
        self.data = data

        # To consolidate all step activity into one transaction,
        # we merge all reg accesses to a conslidated 'regs' dict
        if self.data.has_key('reg'):
            self.data['regs'] = dict()
            self.data['regs'][self.data['reg']] = self.data['val']
            del self.data['reg']


    def update(self,**kwargs):
        if kwargs['count'] != self.data['count']:
            raise ValueError, "Tried to update SimStep {0} with data from a different SimStep {1}".format(self.data['count'],kwargs['count'])
        self.data['regs'][kwargs['reg']] = kwargs['val']

    def differs_from(self,b):
        for k in self.data:
            if k not in b.data:
                return True
        for k in b.data:
            if k not in self.data:
                return True
            if self.data[k] != b.data[k]:
                return True
        return False


    def to_json(self):
        return self.__dict__

    def __repr__(self):
        return "SimStep({0!r})".format(self.data)

    def __str__(self):
        return "{count} 0x{addr:x} {regs!r}".format(**self.data)


class SimTest(object):
    def __init__(self,**kwargs):
        self.name  = kwargs.get('name')
        self.fname = kwargs.get('fname')
        self.ln    = kwargs.get('ln')
        self.idx   = kwargs.get('idx')
        #self.data = kwargs.get('data',list())
        self.data  = kwargs.get('data',dict())

    def __iter__(self):
        return iter([ self.data[k] for k in self.data ])
        #return iter(self.data)

    def add(self,**kwargs):
        count = kwargs['count']
        if not self.data.has_key(count):
            self.data[count] = SimStep(kwargs)
        else:
            self.data[count].update(**kwargs)

        #self.data.append(SimStep(kwargs))

    def diff(self,other):

        for a,b in itertools.izip_longest(self, other):
            #print "a:{0} b:{1}".format(a,b)
            if None in (a,b) or a.differs_from(b):
                return (a,b)

        return None

    def to_json(self):
        return self.__dict__

    def __str__(self):
        ln = ""
        if self.ln is not None:
            ln = ":{0}".format(self.ln)
        return "<SimTrace {0}{1} Test {2} '{3}'>".format(self.fname,ln, self.idx, self.name,)

    def __repr__(self):
        result = [str(self)]
        result.extend([ str(d) for d in self ])
        return "\n".join(result)


class SimTrace(object):
    def __init__(self,**kwargs):
        self.fname = kwargs.get('fname')
        self.tests = []
        self.last_count = None
        self.test_idx = -1

        if self.fname is not None:
            if self.fname.endswith(".json"):
                self.from_json()
            else:
                self.parse_simlog()

    def __iter__(self):
        return iter(self.tests)

    def __len__(self):
        return len(self.tests)

    def new_test(self,name,ln=None):
        #print "SimTrace.new_test {0!r}".format(name)
        self.last_count = -1
        self.test_idx += 1
        self.tests.append( SimTest(
            name  = name,
            fname = self.fname,
            idx   = self.test_idx,
            ln    = ln,
        ))
        
    def get_tests(self,name):
        return [ t for t in self.tests if t.name == name ]

    def get_test(self,name,idx=None):
        tl = self.get_tests(name)
        if len(tl) == 0:
            raise KeyError, "No test {0} in {1}".format(name,self.fname)
        if idx is not None:
            return tl[idx]
        if len(tl) > 1:
            raise KeyError, "{0} tests named {1} in {2}".format(len(tl),name,self.fname)
        return tl[0]

    def verify_instr_count(self,ln,**kwargs):
        test = self.tests[-1]
        count = kwargs.get('count')
        if count not in (self.last_count,self.last_count+1):
            msg = "{fname}:{ln} test '{name}' Got invalid instruction count {count}, last count was {last_count}"
            raise ValueError, msg.format(
                name       = test.name,
                fname      = self.fname,
                ln         = ln,
                count      = count,
                last_count = self.last_count,
            )
        self.last_count = count

    def add(self,**kwargs):
        self.tests[-1].add(**kwargs)


    def to_json(self):
        return self.__dict__


    def from_json(self):
        import json
        with file(self.fname) as infile:
            data = json.loads(infile.read())
            data = useq_arch.no_unicode(data)
            for test in data['tests']:
                self.new_test(test['name'])
                for step in test['data']:
                    self.add(**test['data'][step]['data'])


    def parse_simlog(self):
        in_test = False

        with file(self.fname) as infile:
            ln = 0
            for line in infile:
                stripped = line.strip()
                ln += 1

                #print stripped

                m = start_rx.search(stripped)
                if m:
                    in_test = True
                    self.new_test(m.group(1),ln=ln)
                    continue

                if not in_test:
                    continue

                m = end_rx.search(stripped)
                if m:
                    in_test = False
                    continue
                
                m = reg_rx.search(stripped)
                if m:
                    args = dict(
                        count = int(m.group(1)   ),
                        addr  = int(m.group(2),16),
                        reg   =     m.group(3),
                        val   = int(m.group(4),16),
                    )
                    self.verify_instr_count( ln, **args )
                    self.add( **args )
                    continue
                    
                m = pc_rx.search(stripped)
                if m:
                    args = dict(
                        count = int(m.group(1)   ),
                        addr  = int(m.group(2),16),
                        reg   = "iar",
                        val   = int(m.group(2),16),
                    )
                    self.verify_instr_count( ln, **args )
                    self.add( **args )
                    continue

                raise ValueError, "Unrecognized data:\n{0}".format(stripped)

    def __repr__(self):
        return "\n".join([repr(x) for x in self.tests])

    def __str__(self):
        return "<SimTrace {0}>".format(self.fname)


def mk_parser():
    parser=ArgumentParser(description="Either trace may be .log (from simulation) or .json (from emulator)")
    parser.add_argument( "base",          help="name of base trace" )
    parser.add_argument( "compare",       help="name of compare trace" )
    parser.add_argument( "--testname",    help="name of test to compare.  If omitted, both traces will be compared 1-1." )
    parser.add_argument( "--base_num",    type=int, help="Optional index of base test.  Required if --testname is given and there are multiple instances of testname in the base trace." )
    parser.add_argument( "--compare_num", type=int, help="Optional index of compare test.  Required if --testname is given and there are multiple instances of testname in the compare trace." )
    return parser


def diff_full(b,c):

    b_tl = [ t.name for t in b ]
    c_tl = [ t.name for t in c ]
    
    print "\ndiff_full base {0} -> compare {1}".format(b,c)

    failures = 0

    for i in range(max(len(b),len(c))):

        b_test = None if len(b) <= i else b.tests[i]
        c_test = None if len(c) <= i else c.tests[i]

        if None in (c_test,b_test) or b_test.name != c_test.name:
            msg = "ERROR: Trace mismatch: {b_test:60} {c_test}"
            print msg.format(
                b_test=b_test,
                c_test=c_test,
            )
            failures += 1
            continue

        result = b_test.diff(c_test)

        print_result(b_test,c_test,result,print_match=False)

        if result is not None: failures += 1

    return failures


def diff_one_n(b,c,testname,**kwargs):

    base_num    = kwargs.get('base_num')
    compare_num = kwargs.get('compare_num')

    # 1 to N comparison

    base_tests    = b.get_tests(testname)

    b_num_tests = len(base_tests)

    if base_num is None and b_num_tests != 1:
        msg = "There are {0} tests named '{1}' in the base trace, you must select one with --base_num"
        raise ValueError, msg.format(b_num_tests, testname)

    base_num  = base_num if base_num is not None else 0
    base_test = base_tests[base_num]

    if compare_num is not None:
        compare_list = [c.get_tests(testname)[compare_num]]
    else:
        compare_list = c.get_tests(testname)

    
    failures = 0

    for compare_test in compare_list:

        print "\ndiff_one_n base {0} -> compare {1}".format(base_test,compare_test)

        result = base_test.diff( compare_test )

        print_result(base_test,compare_test,result,print_match=False,b_label='base',c_label='compare')

        if result is not None: failures += 1
    
    return failures


def diff_traces(options):

    b = SimTrace( fname=options.base )
    c = SimTrace( fname=options.compare )

    # 1-1 multiple tests per trace
    if options.testname is None:
        if options.base_num is not None:
            raise ValueError, "You must specify a --testname with option --base_num"
        if options.compare_num is not None:
            raise ValueError, "You must specify a --testname with option --compare_num"
        return diff_full(b,c)
    else:
        return diff_one_n(b, c,
                          options.testname,
                          base_num    = options.base_num,
                          compare_num = options.compare_num)


def print_result(b,c,result,**kwargs):
    if result is not None: 
        print "ERROR: ({0}) difference encountered".format(os.path.basename(sys.argv[0]))
        print "       {0:60} {1}".format(kwargs.get('b_label', b), result[0])
        print "       {0:60} {1}".format(kwargs.get('c_label', c), result[1])
    elif kwargs.get('print_match',True):
        print "{0} matches {1}".format(b, c)


if __name__ == '__main__':
    
    parser   = mk_parser()
    options  = parser.parse_args()
    failures = diff_traces(options)
    sys.exit(0 if failures == 0 else 1)

