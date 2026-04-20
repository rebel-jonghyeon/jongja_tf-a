ENTRY(_start)
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

MEMORY
{
    bl31     (!RWX) : ORIGIN = 0x0,              LENGTH = 0x200000
    dram0_pa (RWX)  : ORIGIN = 0x00014200000,    LENGTH = (0x3E000000 - 0x14200000)
    dram0    (RWX)  : ORIGIN = 0x10014200000,    LENGTH = (0x3E000000 - 0x14200000)
    cs_q (RW) : ORIGIN = 0x1000fe00000 - 0x200000, LENGTH = 0x200000 /* 2MB at the end of FW region */
}

isr_stack_size  = 0x4000;   /* 16KB per each core */
_stack_size     = 0x4000;   /* 16KB per each core */
mmu_page_size   = 0x1000;   /* 4KB aligned */
mmu_page_2mb    = 0x2000;   /* 2MB aligned */

dma_mcode_region_size   = 0x2000;
dma_reserved_size       = 0x1000;
smmu_cte_size           = 0x1000;
smmu_cd_size            = 0x1000;
smmu_cmdq_size          = 0x8000;
smmu_evtq_size          = 0x8000;
dma_smmu_reserved_size  = 0x1000;

dyn_heap_size   = 0x200000;

SECTIONS
{
    .text : AT (ORIGIN(dram0_pa))
    {
        text_region_start = .;
        KEEP(*(.text.startup))
        KEEP(*(.text.vectors))
        *(.text)
        *(privileged_functions)
        *(freertos_system_calls)
    } > dram0

    .init_func ALIGN(8):
    {
        start_init_func = .;
        KEEP(*(SORT(.init_func_[_A-Z0-9]*)))
        end_init_func = .;
    } > dram0

    . = ALIGN(mmu_page_size);
    text_region_end = .;

    rodata_region_start =.;
    .rodata ALIGN(4):
    {
        rodata_start = .;
        *(.rodata .rodata.*)
        *(.got .igot .got.plt .igot.plt)
        rodata_end = .;
    } > dram0

    . = ALIGN(mmu_page_2mb);
    rodata_region_end = .;

    data_region_start = .;
    .data data_region_start :
    {
        data_start = .;
        *(.data .data.*)
        *(privileged_data)
        PROVIDE( __cli_register_funcs_start = . );
        *(.cli_register_funcs)
        PROVIDE( __cli_register_funcs_end = . );
        . = ALIGN(1024);
        . += isr_stack_size;
        PROVIDE(isr_stack_top = .);
        . = ALIGN(1024);
        . += _stack_size;
        PROVIDE(_stack_top = .);
        data_end = .;
    } > dram0

    . = ALIGN(mmu_page_size);
    .bss ALIGN(4):
    {
        bss_start = .;
        *(.sbss*)
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(16);
        bss_end = .;
    } > dram0

    . = ALIGN(mmu_page_2mb);
    data_region_end = .;

    dma_mcode_start = .;
    .nocache_data ALIGN(4) (NOLOAD):
    {
        PROVIDE(dma_mcode_base = .);
        *(.nocache .nocache.*)
        . += dma_mcode_region_size;
    } > dram0

    . = ALIGN(mmu_page_size);
    dma_mcode_end = .;

    dma_reserved_start = .;
    .dma_reserved ALIGN(4) (NOLOAD):
    {
        *(.dma_reserved .dma_reserved.*)
        . += dma_reserved_size;
    } > dram0

    . = ALIGN(mmu_page_size);
    dma_reserved_end = .;

    dma_smmu_region_start = .;
    .dma_smmu_region ALIGN(4) (NOLOAD):
    {
        smmu_cte_start = .;
        . += smmu_cte_size;
        smmu_cte_end = .;

        smmu_cd_start = .;
        . += smmu_cd_size;
        smmu_cd_end = .;

        smmu_cmdq_start = .;
        . += smmu_cmdq_size;
        smmu_cmdq_end = .;

        smmu_evtq_start = .;
        . += smmu_evtq_size;
        smmu_evtq_end = .;
    } > dram0

    . = ALIGN(mmu_page_size);
    dma_smmu_region_end = .;

    dma_smmu_reserved_start = .;
    .dma_smmu_reserved ALIGN(4) (NOLOAD):
    {
        *(.dma_smmu_reserved .dma_smmu_reserved.*)
        . += dma_smmu_reserved_size;
    } > dram0

    . = ALIGN(mmu_page_2mb);
    dma_smmu_reserved_end = .;

    heap_region_start = .;
    .heap ALIGN(8) (NOLOAD):
    {
        KEEP(*(.heap*))
    } > dram0
    . = ALIGN(mmu_page_2mb);
    heap_region_end = .;

    dyn_heap_region_start = .;
    .dyn_heap ALIGN(8) (NOLOAD):
    {
        PROVIDE( metal_segment_heap_target_start = . );
        . += dyn_heap_size;
        . = ALIGN(8);
        PROVIDE( metal_segment_heap_target_end = . );
    } > dram0

    . = ALIGN(mmu_page_2mb);
    dyn_heap_region_end = .;

    /DISCARD/ : { *(.eh_frame) }
}
