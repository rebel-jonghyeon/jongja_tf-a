ENTRY(_vector_table)
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY
{
	SRAM (LWX) : ORIGIN = 0x00000000, LENGTH = 256K /* Code area */
}

_heap_size	= 0x200;
pl330_reserved_size = 0x200;

SECTIONS
{
	.text :
	{
		*(.vector)
		*(.interrupt)
		*(.text.VectorHandlers)
		*(.text.Start)
	} > SRAM

	.init_func ALIGN(4):
	{
		start_init_func = .;
        KEEP(*(SORT(.init_func_[_A-Z0-9]*)))
		end_init_func = .;
	} > SRAM

	.rodata ALIGN(4):
	{
		*(.rodata .rodata.*)
	} > SRAM

	.data ALIGN(4):
	{
		*(.data)
	} > SRAM

	.cli ALIGN(4):
	{
		PROVIDE( __cli_register_funcs_start = . );
		*(.cli_register_funcs)
		PROVIDE( __cli_register_funcs_end = . );
	} > SRAM

	.bss ALIGN(4):
	{
		start_bss = .;
		*(.bss)
		end_bss = .;
	} > SRAM

	.heap ALIGN(4):
	{
		PROVIDE( metal_segment_heap_target_start = . );
		. += _heap_size;
		. = ALIGN(8);
		PROVIDE( metal_segment_heap_target_end = . );
	} > SRAM

	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - pl330_reserved_size;

	. = 0x3fe00;
	.pl330_reserved ALIGN(4):
	{
		PROVIDE( __pl330_reserved_start = . );
		PROVIDE( __pl330_reserved_end = . + pl330_reserved_size );
		*(.pl330_reserved)
		. = __pl330_reserved_end;
	} > SRAM

	/DISCARD/ :
	{
	}
}
