ENTRY(_start)
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

MEMORY
{
	iROM (LRX)	: ORIGIN = 0x1E00000000, LENGTH = 64K
	iRAM (W)	: ORIGIN = 0x1E00040000, LENGTH = 4K
}

SECTIONS
{
	.text :
	{
		*(.text.startup)
		. = ALIGN(0x100);
		*(.vectors)
		*(.text)
		*(.rodata .rodata.*)
		*(.got .igot .got.plt .igot.plt)
	} > iROM

	. = ALIGN(16);
	etext = .;

	.data : AT(etext)
	{
		data_start = .;
		*(.data .data.*)
		. = ALIGN(16);
		data_end = .;
	} > iRAM

	.bss (NOLOAD) : ALIGN(16)
	{
		bss_start = .;
		*(.bss .bss.*)
		*(COMMON)
		. = ALIGN(16);
		bss_end = .;
	} > iRAM

	data_reloc_start =  etext;
	stack_top = ORIGIN(iRAM) + LENGTH(iRAM);
}
