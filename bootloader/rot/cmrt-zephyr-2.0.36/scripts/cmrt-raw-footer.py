#!/usr/bin/env python3
#
# Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# cmrt-raw-footer.py ELF RAW-BINARY OUTPUT [USER-CONTAINER-FOOTER]
#
# Attach a footer to RAW-BINARY according to info
# from ELF, which shall include following symbols:
#
# __cmrt_text_start
# __cmrt_text_end
#
# __cmrt_rodata_start
# __cmrt_rodata_end
#
# __cmrt_bss_start
# __cmrt_bss_end
#
# __cmrt_noinit_start
# __cmrt_noinit_end
#
# __cmrt_data_start
# __cmrt_data_end
#
# These symbols define 5 segments, and these
# segments must be in the sequence stated above.
#
# The format of the footer is as below, address space
# grows downward.
#
# +--------------------+
# |   text start       |
# +--------------------+
# |   text end         |
# +--------------------+
# |   rodata start     |
# +--------------------+
# |   rodata end       |
# +--------------------+
# |   bss start        |
# +--------------------+
# |   bss end          |
# +--------------------+
# |   noinit start     |
# +--------------------+
# |   noinit end       |
# +--------------------+
# |   data start       |
# +--------------------+
# |   data end         |
# +--------------------+
# |   entry point      | : entry point address
# +--------------------+
# |   load address     | : address of loading the raw image
# +--------------------+
# |   relocate offset  | : usually zero, updated at parsing
# +--------------------+
# |   verlen           | : version number and length including this field
# +--------------------+
#
# User container image has an identical footer as fboot image, with an extension
# at the top. That is, following 7 fields are added at the top of above map.
# +--------------------+
# |   stack size       | : stack allocation size
# +--------------------+
# |   global pointer   | : address of global pointer relative to image
# +--------------------+
# |   relo start       | : start of relocation data before the footer
# +--------------------+
# |   relo end         | : end of relocation data before the footer
# +--------------------+
# |   got start        | : start of got data in the raw image
# +--------------------+
# |   got end          | : end of got data in the raw image
# +--------------------+
# |   verlen           | : version number and length including this field
# +--------------------+
#
# CFI systems add yet another footer at the top of above map.
# +--------------------+
# |   meta start       | : start of CFI metadata before the footer
# +--------------------+
# |   meta end         | : end of CFI metadata before the footer
# +--------------------+
# |   verlen           | : version number and length including this field
# +--------------------+


import subprocess
import sys
import os
from struct import pack

ELF_TEXT_START = 0
ELF_TEXT_END = 1
ELF_RODATA_START = 2
ELF_RODATA_END = 3
ELF_BSS_START = 4
ELF_BSS_END = 5
ELF_NOINIT_START = 6
ELF_NOINIT_END = 7
ELF_DATA_START = 8
ELF_DATA_END = 9
ELF_GOT_START = 10
ELF_GOT_END = 11


# List of handled relocation records.  Relocation types present in
# different files are here.  The R_RISCV_ADD/SUB32 will work without
# adjustment while R_RISCV_RVC_LUI and R_RISCV_LO12_I will not.  Dynamic
# relocations (RELATIVE, COPY, JUMP_SLOT, TLS_{DTMOD[32|64], DTPREL[32|64],
# TPREL[32|64], IRELATIVE), and PLT32 are not handled.  TLS_GOT_HI20,
# TLS_GD_HI20, TPREL_HI20, TPREL_LO12_I, TPREL_LO12_S, TPREL_ADD are
# unexpected.  HI20, LO12_I, LO12_S are not handled. 64 is not
# expected.  ALIGN, SUB6, SET8, SET16, SET32 are not handled.
# Any future relocation records are not listed so they will produce an error.
HANDLED_RECORDS = ('32',            # full 32-bit relocation
                   'NONE', 'RELAX', # no action

                   'BRANCH',    # 12-bit pc-relative branch work
                   'JAL',       # 20-bit pc-relative jump offset
                   'CALL', 'CALL_PLT', # 32-bit pc-relative

                   'GOT_HI20',  # pc-relative got access

                   'PCREL_HI20', 'PCREL_LO12_I', 'PCREL_LO12_S',
                   'GPREL_I', 'GPREL_S',

                   'ADD8', 'ADD16', 'ADD32', 'ADD64',
                   'SUB8', 'SUB16', 'SUB32', 'SUB64',

                   'RVC_BRANCH', # 8-bit pc-relative
                   'RVC_JUMP',   # 11-bit pc-relative
                   '32_PCREL',   # 32-bit pc-relative
                   )


def verbose(fmt, *args):
    if verbose.verbose:
        print(fmt.format(*args))
verbose.verbose = False

def load_relocations(elffile, segaddrs):
    """Build a full list of relocations which are just offsets from
    image start. These locations in the image will be relocated when loaded.
    """
    out = subprocess.check_output(["riscv32-unknown-elf-objdump", "-x", elffile]).decode('utf-8')
    relocations = b''
    section_base = None
    for line in out.splitlines():
        if line.startswith("RELOCATION RECORDS FOR"):
            if '.text' in line:
                section_base = segaddrs[ELF_TEXT_START]
            elif '.rodata' in line or '.eh_frame' in line:
                section_base = segaddrs[ELF_RODATA_START]
            elif '.debug' in line:
                section_base = None
            else:
                section_base = segaddrs[ELF_DATA_START]
        if section_base:
            try:
                addr, reltype, symbol = line.split()
                addr = int(addr, 16)
            except ValueError:
                continue
            if reltype[8:] not in HANDLED_RECORDS:
                raise ValueError("unhandled relocation type %s for %s @%x"
                                 % (reltype, symbol, addr))
            if reltype == 'R_RISCV_32':
                assert (addr % 4) == 0, "unaligned address"
                offset = section_base + addr - segaddrs[ELF_TEXT_START]
                verbose("%x\t%x\t%s" % (addr, offset, symbol))
                relocations += pack('<I', offset)

    return relocations


def find_gp(elffile):
    """Find the value of the global pointer.  This should be set relative to
    image start.  We could grep directly to __global_pointer$ and or similar.
    """
    gps = [ "__global_pointer$", "__global_pointer", "__gp" ]
    out = subprocess.check_output(["riscv32-unknown-elf-nm", elffile]).decode('utf-8')
    for line in out.splitlines():
        for e in gps:
            if line.endswith(e):
                return int(line.split()[0], 16)
    return None


def main():
    if len(sys.argv) > 1 and sys.argv[1] == '--verbose':
        verbose.verbose = True
        sys.argv.pop(1)

    if len(sys.argv) < 4:
        raise SystemExit(-1)

    elf_file = sys.argv[1]
    raw_file = sys.argv[2]
    output_file = sys.argv[3]
    meta_file = output_file.replace('raw', 'cfi')
    is_user_image = False
    stack_size = 0

    # Including __cmrt_data_rel_start and __cmrt_data_rel_end
    if len(sys.argv) >= 5 and bool(sys.argv[4]):
        is_user_image = True
    if len(sys.argv) >= 6:
        stack_size = int(sys.argv[5], 0)

    # Verify ELF with readelf and nm
    # TODO: Use pyelftools to parse ELF formally
    segaddrs = [0] * 14
    segmap = { "__cmrt_text_start"     : ELF_TEXT_START,
               "__cmrt_text_end"       : ELF_TEXT_END,
               "__cmrt_rodata_start"   : ELF_RODATA_START,
               "__cmrt_rodata_end"     : ELF_RODATA_END,
               "__cmrt_bss_start"      : ELF_BSS_START,
               "__cmrt_bss_end"        : ELF_BSS_END,
               "__cmrt_noinit_start"   : ELF_NOINIT_START,
               "__cmrt_noinit_end"     : ELF_NOINIT_END,
               "__cmrt_data_start"     : ELF_DATA_START,
               "__cmrt_data_end"       : ELF_DATA_END,
               "__cmrt_got_start"      : ELF_GOT_START,
               "__cmrt_got_end"        : ELF_GOT_END,
    }

    ps = subprocess.Popen(('riscv32-unknown-elf-nm', '-fp', elf_file), stdout=subprocess.PIPE)
    output = subprocess.check_output(('grep', '__cmrt_'), stdin=ps.stdout)
    ps.wait()

    section_count = 0
    for line in output.splitlines():
        terms = line.decode('ascii').split(' ')
        seg = terms[0]
        addr = int(terms[2], 16)
        if seg in segmap:       # can have unused sections/symbols
            if addr & 0x3:
                print("section {}:{:08x} not aligned!".format(seg, addr))
                raise SystemExit(-1)
            segaddrs[segmap[seg]] = addr
            section_count = section_count + 1
    assert (section_count >= 6), "missing sections!"

    # bss, noinit, and rel field can be empty.
    # Fill it with rodata_end.
    # pylint: disable=consider-using-enumerate
    for x in range(len(segaddrs)):
        if segaddrs[x] == 0:
            segaddrs[x] = segaddrs[ELF_RODATA_END]
    # pylint: enable=consider-using-enumerate

    # Read entry point
    ps = subprocess.Popen(('riscv32-unknown-elf-readelf', '-h', elf_file),
                          stdout=subprocess.PIPE)
    output = subprocess.check_output(('grep', 'Entry point address'), stdin=ps.stdout)
    ps.wait()
    entry_point = int(output.splitlines()[0].decode('ascii').split(':')[1].strip(), 16)
    assert (segaddrs[ELF_TEXT_START] <= entry_point < segaddrs[ELF_TEXT_END]), "wrong entry point!"

    global_pointer = find_gp(elf_file)

    # Load address is always beginning of .text
    # This is ensured by linker script
    # Now apply the footer
    rawcontents = open(raw_file, 'rb').read()
    # Image must include at least the text section, but .data may be
    # effectively .bss (non load section)
    rawlen = len(rawcontents)
    padded_rawlen = (rawlen + 3) & ~0x3
    # Though the .text section is 4-byte aligned, the image size may still
    # be 2-byte aligned due to compressed ISA. In this case the raw image
    # file size may be 2 byte smaller than the section size. But this is
    # valid and should be accepted.
    textlen = segaddrs[ELF_TEXT_END] - segaddrs[ELF_TEXT_START]
    assert textlen <= padded_rawlen, "short raw image file!"
    padding = padded_rawlen - rawlen
    # calculate relocations
    relocontents = load_relocations(elf_file, segaddrs)
    # check if there is metadata following the raw image
    metacontents = open(meta_file, 'rb').read() if os.path.exists(meta_file) else b''
    metalen = len(metacontents)
    if metalen:
        # Yes there is, size must be <= text segment size.
        assert metalen <= textlen, "invalid metadata size!"

    with open(output_file, 'wb') as wf:
        # write image and padding
        wf.write(rawcontents)
        if padding:
            wf.write(bytes(padding))

        segaddr = padded_rawlen + segaddrs[ELF_TEXT_START]

        if metalen:
            # append metadata
            wf.write(metacontents)
            # additional footer for CFI metadata
            wf.write(pack('<I', segaddr))
            verbose("CFI_META_START {:08x}", segaddr)
            segaddr += metalen
            wf.write(pack('<I', segaddr))
            verbose("CFI_META_END {:08x}", segaddr)
            wf.write(pack('<I', 3*4))
            segaddr += 3*4

        # if it is user image, write user footer first
        # The sequence must be the same as usr_image_footer_t
        if is_user_image:
            # write relocations
            wf.write(relocontents)
            # write user footer
            wf.write(pack('<I', stack_size or 0))
            verbose("STACK_SIZE {:08x}", stack_size)
            wf.write(pack('<I', global_pointer or 0))
            verbose("GLOBAL_POINTER {:08x}", global_pointer)
            wf.write(pack('<I', segaddr))
            verbose("RELO_START {:08x}", segaddr)
            segaddr += len(relocontents)
            wf.write(pack('<I', segaddr))
            verbose("RELO_END {:08x}", segaddr)
            wf.write(pack('<I', segaddrs[ELF_GOT_START]))
            verbose("ELF_GOT_START {:08x}", segaddrs[ELF_GOT_START])
            wf.write(pack('<I', segaddrs[ELF_GOT_END]))
            verbose("ELF_GOT_END {:08x}", segaddrs[ELF_GOT_END])
            wf.write(pack('<I', 7*4))
            segaddr += 7*4

        # write footer
        # The sequence must be the same as raw_image_footer_t
        wf.write(pack('<I', segaddrs[ELF_TEXT_START]))
        verbose("ELF_TEXT_START {:08x}", segaddrs[ELF_TEXT_START])
        wf.write(pack('<I', segaddrs[ELF_TEXT_END]))
        verbose("ELF_TEXT_END {:08x}", segaddrs[ELF_TEXT_END])
        wf.write(pack('<I', segaddrs[ELF_RODATA_START]))
        verbose("ELF_RODATA_START {:08x}", segaddrs[ELF_RODATA_START])
        wf.write(pack('<I', segaddrs[ELF_RODATA_END]))
        verbose("ELF_RODATA_END {:08x}", segaddrs[ELF_RODATA_END])
        wf.write(pack('<I', segaddrs[ELF_BSS_START]))
        verbose("ELF_BSS_START {:08x}", segaddrs[ELF_BSS_START])
        wf.write(pack('<I', segaddrs[ELF_BSS_END]))
        verbose("ELF_BSS_END {:08x}", segaddrs[ELF_BSS_END])
        wf.write(pack('<I', segaddrs[ELF_NOINIT_START]))
        verbose("ELF_NOINIT_START {:08x}", segaddrs[ELF_NOINIT_START])
        wf.write(pack('<I', segaddrs[ELF_NOINIT_END]))
        verbose("ELF_NOINIT_END {:08x}", segaddrs[ELF_NOINIT_END])
        wf.write(pack('<I', segaddrs[ELF_DATA_START]))
        verbose("ELF_DATA_START {:08x}", segaddrs[ELF_DATA_START])
        wf.write(pack('<I', segaddrs[ELF_DATA_END]))
        verbose("ELF_DATA_END {:08x}", segaddrs[ELF_DATA_END])

        wf.write(pack('<I', entry_point))
        verbose("ENTRY_POINT {:08x}", entry_point)
        wf.write(pack('<I', segaddrs[0]))
        verbose("LOAD_ADDRESS {:08x}", segaddrs[0])
        wf.write(pack('<I', 0))
        verbose("RELOCATION_OFFSET {:08x}", 0)
        wf.write(pack('<I', 14*4))


if __name__ == '__main__':
    main()
    pass
