
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

struct rbcm_cli_cmd {
	const char *name;
	const char *help;
	int32_t (*handler)(int argc, char **argv);
};

struct test_counts {
	int total;
	int pass;
	int fail;
};

const char rbcm_check_crc_help[] =
	"check_crc [-a|-m RbcModule]\r\n"
	"  Dump UCIe CRC error registers for one module or all modules with -a.\r\n";

const char rbcm_sw_reset_help[] =
	"sw_reset [-m RbcModule] [-a (all)]\r\n"
	"  Reset the specified RBC module or all modules.\r\n";

const char rbcm_scan_ttreg_help[] =
	"scan_ttreg [-m RbcModule] [-p Port] [-b {inbound|outbound}]\r\n"
	"  Scan the Transaction Table Register (TTREG) for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -p Port: Specify the port (0-3) to scan.\r\n"
	"    -b {inbound|outbound}: Specify the direction of traffic to scan.\r\n";

const char rbcm_dump_incomplete_ttreg_help[] =
	"dump_incomplete_ttreg [-m RbcModule] [-a (all)]\r\n"
	"  Dump incomplete Transaction Table Register (TTREG) entries for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -a: Dump for all modules.\r\n";

const char rbcm_clear_ttreg_help[] =
	"clear_ttreg [-m RbcModule]\r\n"
	"  Clear the Transaction Table Register (TTREG) for the specified RBC module.\r\n"
	"  If no module is specified, it clears all modules.\r\n";

const char rbcm_utg_write_help[] =
	"utg_write [-m RbcModule] [-p Port] [-r Repeat] <TargetAddr>\r\n"
	"  Generate a User Traffic Generation (UTG) write request for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -p Port: Specify the port (0-3) to write to.\r\n"
	"    -r Repeat: Number of times to repeat the write operation.\r\n"
	"    <TargetAddr>: The target address to write to.\r\n";

const char rbcm_utg_read_help[] =
	"utg_read [-m RbcModule] [-p Port] [-r Repeat]\r\n"
	"  Generate a User Traffic Generation (UTG) Read request for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -p Port: Specify the port (0-3) to read from.\r\n"
	"    -r Repeat: Number of times to repeat the read operation.\r\n"
	"    <TargetAddr>: The target address to write to.\r\n";

const char rbcm_addr_remap_help[] =
	"addr_remap [-m RbcModule] <MsbFrom> <MsbTo>\r\n"
	"  Remap the most significant bits (MSB) of the address for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    <MsbFrom>: The MSB to remap from (4 bits).\r\n"
	"    <MsbTo>: The MSB to remap to (4 bits).\r\n"
	"  This remaps the MSB 4-bits of address from MsbFrom[39:36] to MsbTo[39:36].\r\n";

const char rbcm_set_loopback_help[] =
	"set_loopback [-m RbcModule] [-l {Port,Inner,Outer}] [-d (disable)]\r\n"
	"  Set the loopback mode for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -l {Port,Inner,Outer}: Specify the loopback type.\r\n"
	"    -d (disable): Disable loopback if specified.\r\n";

const char rbcm_set_timeout_help[] =
	"set_timeout [-m RbcModule] [TimeOutInterval]\r\n"
	"  Set the timeout interval for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"    -t TimeoutVal: Set timeout value.\r\n";

const char rbcm_get_timeout_help[] =
	"get_timeout [-m RbcModule]\r\n"
	"  Get the timeout interval (tick/window) for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n";

const char rbcm_enable_irq_help[] =
	"enable_irq [-a all|-m RbcModule] [all|port|timeout|cbus|utg_done|utg_err|ttreg]\r\n"
	"  Enable interrupts for RBC modules. Options:\r\n"
	"    -a all: Apply to all modules (mutually exclusive with -m).\r\n"
	"    -m RbcModule: Apply to a specific module (e.g., C0E0, C1E1).\r\n"
	"    [all|port|timeout|cbus|utg_done|utg_err|ttreg]: Select interrupts.\r\n"
	"    If 'all' is specified, all interrupts are enabled. If none specified,\r\n"
	"    all interrupts are enabled by default.\r\n";

const char rbcm_disable_irq_help[] =
	"disable_irq [-a all|-m RbcModule] [all|port|timeout|cbus|utg|ttreg]\r\n"
	"  Disable interrupts for RBC modules. Options:\r\n"
	"    -a all: Apply to all modules (mutually exclusive with -m).\r\n"
	"    -m RbcModule: Apply to a specific module (e.g., C0E0, C1E1).\r\n"
	"    [all|port|timeout|cbus|utg_done|utg_err|ttreg]: Select interrupts.\r\n"
	"    If 'all' is specified, all interrupts are disabled. If none\r\n"
	"    specified, all interrupts are disabled by default.\r\n";

const char rbcm_check_ucie_help[] =
	"check_ucie [-a|-m RbcModule]\r\n"
	"  Dump UCIe link health registers for one module or all modules with -a.\r\n";

const char rbcm_reg_acc_test_help[] =
	"reg_acc_test [-m RbcModule]\r\n"
	"  Perform a register access test for the specified RBC module.\r\n"
	"  Options:\r\n"
	"    -m RbcModule: Specify the RBC module (e.g., C0E0, C1E1, etc.).\r\n"
	"  This command tests the register access functionality of the RBC module.\r\n";

const char rbcm_test_all_help[] =
	"test_all [-t all|loopback|ttreg|reg_acc|soft_reset[,...]]\r\n"
	"  Run selected tests and print a summary table.\r\n"
	"  Options:\r\n"
	"    -t <list> : Comma-separated list or repeated -t to select\r\n"
	"                tests. Supported: all, loopback, ttreg, reg_acc,\r\n"
	"                soft_reset. If omitted, all tests run by default.\r\n"
	"  Output:\r\n"
	"    Prints an ASCII table with Total/Passed/Failed per test type.\r\n";
