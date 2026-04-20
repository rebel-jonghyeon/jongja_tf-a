echo [GDB] REBEL_Q FW Preload Start...\n
target extended-remote :3333
set architecture aarch64
set pagination off
set confirm off
delete

#
# Functions
#
define resume_all_targets
	monitor targets REBEL_Q.apb
	monitor resume
	monitor targets REBEL_Q.axi
	monitor resume
	monitor targets REBEL_Q.CL3.CP0.Core0
	monitor resume
	monitor targets REBEL_Q.CL2.CP0.Core0
	monitor resume
	monitor targets REBEL_Q.CL1.CP0.Core0
	monitor resume

	monitor targets REBEL_Q.CL0.CP0.Core0
	monitor resume
end

# $arg0: Target Name
define halt_and_reset
	monitor targets $arg0
	monitor halt
	monitor mww 0x1FF0230400 1
end

define halt_and_reset_all
	echo \n\n### Do PMU SW RESET!!! ###\n\n
	halt_and_reset REBEL_Q.CL3.CP0.Core0
	halt_and_reset REBEL_Q.CL2.CP0.Core0
	halt_and_reset REBEL_Q.CL1.CP0.Core0
	halt_and_reset REBEL_Q.CL0.CP0.Core0

	monitor reset halt
	resume_all_targets
end

# $arg0: Chiplet offset (0x2000000000)
define load_chiplet_fw
	restore ./binaries/BootLoader_CP/bl31.bin binary ($arg0+0x0)
	restore ./binaries/FreeRTOS_CP/freertos_kernel.bin binary ($arg0+0x200000)
	restore ./binaries/FreeRTOS_CP1/bl31.bin binary ($arg0+0x14100000)
	restore ./binaries/FreeRTOS_CP1/freertos_kernel.bin binary ($arg0+0x14200000)
end

#
# Main execution sequence
#
echo \n\n[GDB] ### Resetting targets... ###\n
monitor reset halt
resume_all_targets

# if pc is not sram, run pmu sw reset
set $curr_pc=$pc
if $curr_pc!=0x1e00000040
	halt_and_reset_all
end

# halt CL0 core0 to load fw
monitor targets REBEL_Q.CL0.CP0.Core0
monitor halt

echo \n\n[GDB] ### Loading Bootloaders... ###\n
restore ./binaries/BootLoader_CP/bl1.bin binary 0x1e00010000
restore ./binaries/BootLoader_CP/bl2.bin binary 0x1e00030000
restore ./binaries/FreeRTOS_PCIE/freertos_kernel.bin binary 0x1e08000000

set $pc = 0x1e00010000
symbol-file ./binaries/BootLoader_CP/bl1.elf
hbreak _bl1_init_blk_rbc
continue

echo \n\n[GDB] ### Loading UCIe FW EVT0: master_rt_9264e.bin ###\n
restore ./binaries/3rd_party/ucie/evt0/master_rt_9264e.bin binary 0x1e05c20000

# delete _bl1_init_blk_rbc break point
delete

symbol-file ./binaries/BootLoader_CP/bl2.elf
hbreak tzpc_init_sysreg_bl2
continue

# Load BL31 and Kernel for each chiplet
echo \n\n[GDB] ### Loading BL31 and FW at each CL ###\n
echo [GDB] CL0\n
load_chiplet_fw 0x0
echo \n\n[GDB] CL1\n
load_chiplet_fw 0x2000000000
echo \n\n[GDB] CL2\n
load_chiplet_fw 0x4000000000
echo \n\n[GDB] CL3\n
load_chiplet_fw 0x6000000000

echo \n\n[GDB] All binaries loaded. Proceeding...\n
continue
