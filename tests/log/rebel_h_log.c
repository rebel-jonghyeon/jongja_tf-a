#include <stdint.h>
#include <rebel_h_platform.h>
#include "test_common.h"

union _log_data {
	struct {
		uint32_t cp0_step:5;
		uint32_t rot_step:5;
		uint32_t cm7_step:4;
		uint32_t cp1_step:2;
		uint32_t cp0_binary:3;
		uint32_t rot_binary:2;
		uint32_t cm7_binary:2;
		uint32_t cp1_binary:2;
		uint32_t reset_type:5;
		uint32_t chiplet_id:2;
	};
	uint32_t val;
};

/* NOTE: These strings delived from RST_STAT in the cpmu sfr description. */
static const char * const RESET_NAME[] = {
	"CLUSTER0_DBGRSTREQ0",
	"CLUSTER0_DBGRSTREQ1",
	"CLUSTER0_DBGRSTREQ2",
	"CLUSTER0_DBGRSTREQ3",
	"CLUSTER1_DBGRSTREQ0",
	"CLUSTER1_DBGRSTREQ1",
	"CLUSTER1_DBGRSTREQ2",
	"CLUSTER1_DBGRSTREQ3",
	"CLUSTER0_WARMRSTREQ0",
	"CLUSTER0_WARMRSTREQ1",
	"CLUSTER0_WARMRSTREQ2",
	"CLUSTER0_WARMRSTREQ3",
	"CLUSTER1_WARMRSTREQ0",
	"CLUSTER1_WARMRSTREQ1",
	"CLUSTER1_WARMRSTREQ2",
	"CLUSTER1_WARMRSTREQ3",
	"PINRESET",
	"RSVD3",
	"RSVD3",
	"RSVD3",
	"PCIE_PERST",
	"HOTRESET_GLOBAL",
	"RSVD2",
	"CLUSTER0_WDTRESET_L1",
	"CLUSTER1_WDTRESET_L1",
	"CLUSTER0_WDTRESET_L2",
	"CLUSTER1_WDTRESET_L2",
	"RSVD1",
	"WRESET",
	"SWRESET",
	"RSVD0",
	"RSVD0",
};

/* NOTE: These strings depends on the boot binary index in common/rebel_h_platform.h */
static const char * const CP0_BIN_NAME[] = {
	"NULL",
	"FBOOT_N",
	"SBOOT_N",
	"TBOOT_N",
	"BL31",
	"FREERTOS",
};

static const char * const CP1_BIN_NAME[] = {
	"NULL",
	"BL31",
	"FREERTOS",
};

static const char * const CM7_BIN_NAME[] = {
	"NULL",
	"TBOOT_P0",
};

static const char * const ROT_BIN_NAME[] = {
	"NULL",
	"SBOOT_S",
	"MIDDLEWARE",
};

/* NOTE: These strings depends on the boot sequence in fboot/main.c and fboot/aarch64/init.S */
static const char * const FBOOT_N_STEPS[] = {
	"NOT_STARTED",
	"NOT_PRIMARY_CHIPLET",
	"CHECK_BOOT_MODE",
	"NOT_NORMAL_BOOT",
	"INIT_CPU_REGS",
	"JUMP_TO_MAIN",
	"SIZE_CHECK_SBOOT_N",
	"SIZE_ERROR_SBOOT_N",
	"INIT_QSPI",
	"LOAD_SBOOT_N",
	"JUMP_TO_SBOOT_N",
};

/* NOTE: These strings depends on the boot sequence in rebel_h_bl1_setup.c */
static const char * const SBOOT_N_STEPS[] = {
	"NOT_STARTED",
	"HW_INIT",
	"LOAD_TBOOT_P0",
	"RESET_RELEASE_CM7",
	"WAIT_PHY_SRAM_INIT_DONE",
	"LOAD_TBOOT_P1",
	"CM7_NOTIFY_LOAD_DONE",
	"QSPI_BRIDGE_STATUS_CHECK",
	"PMU_ENABLE_BLK_RBC",
	"REQUEST_TBOOT_U_INTEGRITY",
	"RESPONSE_TBOOT_U_INTEGRITY",
	"INIT_BLK_RBC",
	"REQUEST_TBOOT_N_INTEGRITY",
	"RESPONSE_TBOOT_N_INTEGRITY",
};

/* NOTE: These strings depends on the boot sequence in rebel_h_bl2_setup.c */
static const char * const TBOOT_N_STEPS[] = {
	"NOT_STARTED",
	"HW_INIT",
	"WAITING_UCIE_INIT",
	"HBM3_INIT",
	"LOAD_CP0_BL31",
	"LOAD_CP0_FREERTOS",
	"LOAD_CP1_BL31",
	"LOAD_CP1_FREERTOS",
	"SEND_SBOOT_S_SECONDARY_CHIPLETS",
	"SEND_TBOOT_S_SECONDARY_CHIPLETS",
	"RESET_RELEASE_SECONDARY_ROTS",
	"REQUEST_CP0_BL31_INTEGRITY",
	"RESPONSE_CP0_BL31_INTEGRITY",
	"REQUEST_CP0_FREERTOS_INTEGRITY",
	"RESPONSE_CP0_FREERTOS_INTEGRITY",
	"REQUEST_CP1_BL31_INTEGRITY",
	"RESPONSE_CP1_BL31_INTEGRITY",
	"REQUEST_CP1_FREERTOS_INTEGRITY",
	"RESPONSE_CP1_FREERTOS_INTEGRITY",
	"LOAD_SECONDARY_CP0_BL31",
	"LOAD_SECONDARY_CP0_FREERTOS",
	"LOAD_SECONDARY_CP1_BL31",
	"LOAD_SECONDARY_CP1_FREERTOS",
	"SET_RVBAR_AND_RESET_SECONDARY_CP0",
	"SET_RVBAR_AND_RESET_SECONDARY_CP1",
};

/* NOTE: These strings depends on the boot sequence in bl31_main.c */
static const char * const BL31_STEPS[] = {
	"NOT_STARTED",
	"JUMP_TO_RTOS",
};

/* NOTE: These strings depends on the boot sequence in ARM_CA73/mmu.c and FreeRTOS/Source/main.c */
static const char * const FREERTOS_STEPS[] = {
	"NOT_STARTED",
	"START_MMU_INIT",
	"SET_STACK_POINTER",
	"HW_INIT",
	"RUNTIME_SERVICE",
};

/* NOTE: These strings depends on the boot sequence in FreeRTOS/Source/main_cm7.c */
static const char * const CM7_STEPS[] = {
	"NOT_STARTED",
	"HW_INIT",
	"NOTIFY_PCIE_COMPLETION",
	"RUNTIME_SERVICE",
};

/* NOTE: These strings depends on the boot sequence in sboot/src/main.c */
static const char * const SBOOT_S_STEPS[] = {
	"NOT_STARTED",
	"INIT_LOG",
	"HW_INIT",
	"CHECK_EMERGENCY_DOWNLOAD",
	"RUN_EMERGENCY_DOWNLOAD",
	"LOAD_AND_CHECK_TBOOT_P0",
	"RESET_RELEASE_CM7",
	"WAIT_CM7_RESET_DONE",
	"LOAD_AND_CHECK_TBOOT_P1",
	"NOTIFY_CM7_PHY_RESET_DONE",
	"LOAD_AND_CHECK_TBOOT_S",
	"RETURN_TO_FBOOT_S",
};

/* NOTE: These strings depends on the boot sequence in supervisors/mw/src/main.c */
static const char * const MW_STEPS[] = {
	"NOT_STARTED",
	"START_MAIN",
	"LOAD_SBOOT_N",
	"ASSIGN_RVBAR_OF_CP0",
	"RESET_RELEASE_NONCPU",
	"RESET_RELEASE_CPU0",
	"TEST_READY_EXTERNAL_IP",
	"RUNTIME_SERVICE",
};

static const char *get_cm7_step_name(uint32_t bin, uint32_t step)
{
	const char *step_name;

	if (step == BOOT_DONE(CM7)) {
		step_name = "BOOT_DONE";
	} else {
		step_name = CM7_STEPS[step];
	}

	return step_name;
}

static const char *get_rot_step_name(uint32_t bin, uint32_t step)
{
	const char *step_name;

	switch (bin) {
	case BOOT_SBOOT_S:
		step_name = SBOOT_S_STEPS[step];
		break;
	case BOOT_ROT_MW:
		if (step == BOOT_DONE(ROT)) {
			step_name = "BOOT_DONE";
		} else {
			step_name = MW_STEPS[step];
		}
		break;
	default:
		step_name = "INVALID BIN NAME";
		break;
	}

	return step_name;
}

static const char *get_cp0_step_name(uint32_t bin, uint32_t step)
{
	const char *step_name;

	switch (bin) {
	case BOOT_FBOOT_N:
		step_name = FBOOT_N_STEPS[step];
		break;
	case BOOT_SBOOT_N:
		step_name = SBOOT_N_STEPS[step];
		break;
	case BOOT_TBOOT_N:
		step_name = TBOOT_N_STEPS[step];
		break;
	case BOOT_CP0_BL31:
		step_name = BL31_STEPS[step];
		break;
	case BOOT_CP0_FREERTOS:
		if (step == BOOT_DONE(CP0)) {
			step_name = "BOOT_DONE";
		} else {
			step_name = FREERTOS_STEPS[step];
		}
		break;
	default:
		step_name = "INVALID BIN NAME";
		break;
	}

	return step_name;
}

static const char *get_cp1_step_name(uint32_t bin, uint32_t step)
{
	const char *step_name;

	switch (bin) {
	case BOOT_CP1_BL31:
		step_name = BL31_STEPS[step];
		break;
	case BOOT_CP1_FREERTOS:
		if (step == BOOT_DONE(CP1)) {
			step_name = "BOOT_DONE";
		} else {
			step_name = FREERTOS_STEPS[step];
		}
		break;
	default:
		step_name = "INVALID BIN NAME";
		break;
	}

	return step_name;
}

void print_log(union _log_data data)
{
	printf("\n------------------------------------------------------------\n");
	printf("Log val: 0x%x\n", (unsigned int)data.val);
	printf("------------------------------------------------------------\n");
	printf(" Chiplet_id: %02d\n", data.chiplet_id);
	printf(" Reset_type: %s(%d)\n", RESET_NAME[data.reset_type], data.reset_type);
	printf("  cm7) binary: %-10s step: %s(%d)\n", CM7_BIN_NAME[data.cm7_binary],
		   get_cm7_step_name(data.cm7_binary, data.cm7_step), data.cm7_step);
	printf("  rot) binary: %-10s step: %s(%d)\n", ROT_BIN_NAME[data.rot_binary],
		   get_rot_step_name(data.rot_binary, data.rot_step), data.rot_step);
	printf("  cp0) binary: %-10s step: %s(%d)\n", CP0_BIN_NAME[data.cp0_binary],
		   get_cp0_step_name(data.cp0_binary, data.cp0_step), data.cp0_step);
	printf("  cp1) binary: %-10s step: %s(%d)\n", CP1_BIN_NAME[data.cp1_binary],
		   get_cp1_step_name(data.cp1_binary, data.cp1_step), data.cp1_step);
}

uint8_t test_main_log(int arc, char *argv[])
{
	print_log(*(union _log_data *)BOOT_LOG_ADDR);

	return true;
}

static const char help_log[] =
	"[show_log]\r\n"
	"\r\n";

CLI_REGISTER(show_log, NULL, test_main_log, help_log);

