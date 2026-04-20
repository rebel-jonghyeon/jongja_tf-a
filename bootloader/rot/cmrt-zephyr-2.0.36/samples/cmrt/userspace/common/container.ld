/* Script for -n: mix text and data on same page */
/* Copyright (C) 2014-2017 Free Software Foundation, Inc.

   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */

/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
  . = SEGMENT_START("text", 0x10000);
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  .text           : ALIGN(4)
  {
    __cmrt_text_start = .;
    *(.text.startup .text.startup.* .text.exit .text.exit.*)
    *(.text .text.* .gnu.linkonce.t.*)
  }
  .exception           :
  {
    KEEP(*(".exception.entry.*"))
    *(".exception.other.*")
  }
  . = ALIGN(. + 2, 4);
  __cmrt_text_end = .;

  __cmrt_rodata_start = .;

  .rodata : ALIGN(4) {
     PROVIDE(__constructors_begin = .);
     KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
     KEEP (*(.init_array .ctors))
     PROVIDE(__constructors_end = .);
     *(.rodata .rodata.* .rodata1 .gnu.linkonce.r.*)
     *(.data.rel.ro*)
     *(.srodata .srodata.*)
  }
  . = ALIGN(4);
  .eh_frame_hdr : { *(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*) }
  .eh_frame : { KEEP (*(.eh_frame)) *(.eh_frame.*) }
  .gcc_except_table : { *(.gcc_except_table .gcc_except_table.*) }
  .gnu_extab   : { *(.gnu_extab*) }

  .got : ALIGN(4) {
    __cmrt_got_start = ALIGN(4);
    *(.got.plt) *(.igot.plt) *(.got) *(.igot)
    *(.rela.got)
    __cmrt_got_end = ALIGN(4);
  }
  . = ALIGN(4);
  __cmrt_rodata_end = .;

  /* Thread Local Storage sections  */
  .tdata	  : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss	  : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
  .dynamic        : { *(.dynamic) }

  .data           : ALIGN(4)
  {
    __cmrt_data_start = .;
    *(.data.rel*)
    *(.data .data1 .data.* .gnu.linkonce.d.*)
    *(.sdata .sdata.* .gnu.linkonce.s.* .sdata2 .sdata2.* .gnu.linkonce.s2.*)
  }

  .bss : ALIGN(4) {
      *(.bss .bss.* .gnu.linkonce.b.* COMMON)
      *(.sbss .sbss.* .gnu.linkonce.sb.* .scommon)
      *(.sbss2 .sbss2.* .gnu.linkonce.sb2.*)
  }

  /* Assign the global pointer so that the full range can be used to
   * access variables (heap variables will not as they are dynamic, the
   * heap begin itself could be).  The toolchain will never generate code to
   * load a function address via gp.  Small data should be preferred as
   * more variables could be made to hit it.
   */
  __global_pointer$ = MIN(MAX(., __heap_begin) - 0x800, __cmrt_rodata_start + 0x800);

  .heap : ALIGN(16)
  {
    PROVIDE_HIDDEN(__heap_begin = .);
    *(.heap);
    ASSERT((. - __heap_begin == 0) || (HEAP_SIZE >= 32),
	   "NO HEAP_SIZE DEFINED, MUST SPECIFY user_heap_size");
    ASSERT((HEAP_SIZE % 8) == 0, "Unaligned heap size");
    . = ALIGN(MAX(., __heap_begin + HEAP_SIZE), 16);
    PROVIDE_HIDDEN(__heap_end = .);
  }

  __cmrt_data_end = .;

  /* Sentinel data section to force a write-out of the preceding sections,
   * including .bss
   */
  .sentinel : ALIGN(4) {
    LONG(0x54524c43);
  }

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end ) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    0 : { *(.debug_macro) }
  .debug_addr     0 : { *(.debug_addr) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }

  .info : {
	    *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*)
	    *(.comment .comment.*)
	    *(.riscv.attributes)
	    *(.gnu.warning)
  }

  /DISCARD/ : {
  }
}
