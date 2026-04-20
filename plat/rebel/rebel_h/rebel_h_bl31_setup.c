/*
 * Copyright (c) 2023-2025, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <arch_helpers.h>
#include <platform_def.h>
#include <common/bl_common.h>
#include <common/debug.h>

#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <drivers/ti/uart/uart_16550.h>
#include <drivers/arm/gicv3.h>
#include <plat/arm/common/plat_arm.h>
#include <rebel_h_pmu.h>
#include <rebel_h_plat.h>
#include <bakery_lock.h>

extern int plat_my_core_pos(void);
extern unsigned int plat_core_pos_by_mpidr(u_register_t mpidr);

static entry_point_info_t bl33_image_ep_info;
#if (__TARGET_CP != 1)
static console_t rebel_console;
#endif

typedef struct {
	unsigned long physical_address;
	unsigned long virtual_address;
	unsigned long size;
} mapping_t;

const mapping_t bl31_coherent_area[] = {
	{0x3d000000, 0x3d000000, 0x1000000},	/* 2M aligned region for extra coherent mem, {PA, VA, SIZE} */
};

void bl31_early_platform_setup2(u_register_t arg0, u_register_t arg1,
								u_register_t arg2, u_register_t arg3)
{
#ifndef ZEBU_POC
	/* Enable secondary chiplet's timer */
	if (CHIPLET_ID)
		mmio_write_32(CSS600_CNTGEN + CNTCR, CNTEN);

	/* Set all CA73 core(cpu0-3) to AArch64 mode */
#if (__TARGET_CP == 1)
	mmio_clrbits_32(CPMU_PRIVATE + CPU_RESET_DISABLE_FROM_LEVEL2RESET, (1 << PEND_CLUSTER1));
	mmio_write_32(SYSREG_CP1 + AA64NAA32, 0xF);
#else
	mmio_clrbits_32(CPMU_PRIVATE + CPU_RESET_DISABLE_FROM_LEVEL2RESET, (1 << PEND_CLUSTER0));
	mmio_write_32(SYSREG_CP0 + AA64NAA32, 0xF);
#endif

	/* FIXME: For iRAM-boot W/A, set all iRAM area to non-secure to jump to O/S */
	mmio_write_32(SYSREG_ROT + TZPC_R0SIZE, ALL_NS);
#endif /* ZEBU_POC */

#if (__TARGET_CP != 1)
	console_16550_register(PLAT_UART0_PERI0,
						   PLAT_UART_CLOCK,
						   PLAT_BAUDRATE,
						   &rebel_console);

	console_set_scope(&rebel_console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH |
									CONSOLE_FLAG_RUNTIME);
#endif

	INFO("rebel_h: Preparing to jump to the next O/S\n");

	uint32_t bootreason = pmu_get_bootreason();

	NOTICE("BL31: Chiplet-%d / Boot reason: %s\n", CHIPLET_ID, pmu_get_bootreason_str(bootreason));

	/* Next image is FreeRTOS or Zephyr O/S with EL1 non-secure */
	/* Specify FreeRTOS start address for each chiplet */
	bl33_image_ep_info.pc = (CHIPLET_ID * CHIPLET_OFFSET) + REBEL_H_FREERTOS_LOAD_BASE;
	bl33_image_ep_info.spsr = SPSR_64(MODE_EL1, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	SET_SECURITY_STATE(bl33_image_ep_info.h.attr, NON_SECURE);

	/* Passing a set of proper argmuents to the next O/S */
	bl33_image_ep_info.args.arg0 = 0x0ULL;
	bl33_image_ep_info.args.arg1 = 0x0ULL;
	bl33_image_ep_info.args.arg2 = 0x0ULL;
	bl33_image_ep_info.args.arg3 = 0x0ULL;
}

void bl31_plat_arch_setup(void)
{
	touch_dummy_mmu_cfg_el3();
}

/* ML4_DEV15 ver. */
void tzpc_init_sysreg(void)
{
#ifndef ZEBU_POC
	/* TODO: Update TZPC bits according to the latest document */

	/* SYSREG_ROT */
	/* TZPC_PROT0STAT SFR description
	 * [31:17] : Reserved							/ [16] : Used for SYSREG_SYSREMAP.TrustZoneInfo
	 * [15:14] : Not Used							/ [13] : CSSYS_DP	/ [12] : DMA330
	 * [11] : Not Used		/ [10] : MAILBOX_M2		/ [9] : MAILBOX_M1	/ [8] : MAILBOX_M0
	 * [7] : OTP_CON_CPU	/ [6] : PVT_CON			/ [5] : OTP_CON_SOC	/ [4] : GPIO
	 * [3] : Central_PMU	/ [2] : SYSREG_SYSREMAP	/ [1] : Not Used	/ [0] : CMU_ROT
	 * [Valid bits] : U(0x000137FD)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_ROT.TrustZoneInfo		/ [30:0] : Not Used
	 * [Valid bits] : U(0x80000000)
	 */
	mmio_write_32(SYSREG_ROT + SYSREG_ROT_TZPC_PROT0SET, U(0x000137FD));
	mmio_write_32(SYSREG_ROT + SYSREG_ROT_TZPC_PROT1SET, U(0x00000000));

	/* SYSREG_CP0/1 */
	/* TZPC_PROT0STAT SFR desciption
	 * [31:7] : Reserved	/ [6] : TrustZoneInfo_SYSREG_BUSCSR_CP__CONTROL_SYSREG_TZPC
	 * [5] : MAILBOX_M4		/ [4] : MAILBOX_M3
	 * [3] : ADD_CON_CP		/ [2] : SYSREG_BUSCSR_CP	/ [1] : Reserved	/ [0] : CMU_CP
	 * [Valid bits] : U(0x0000007D)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_CP.TrustZonInfo			/ [30:0] : Reserved
	 * [Valid bits] : U(0x80000000)
	 */
	mmio_write_32(SYSREG_CP0 + SYSREG_CP_TZPC_PROT0SET, U(0x00000039));
	mmio_write_32(SYSREG_CP1 + SYSREG_CP_TZPC_PROT0SET, U(0x00000039));
	mmio_write_32(SYSREG_CP0 + SYSREG_CP_TZPC_PROT1SET, U(0x00000000));
	mmio_write_32(SYSREG_CP1 + SYSREG_CP_TZPC_PROT1SET, U(0x00000000));

	/* SYSREG_DRAM */
	/* TZPC_PROT0STAT SFR description
	 * [31:4] : Reserved
	 * [3] : TrustZoneInfo for PHY+ICON			/ [2] : TrustZoneInfo for HBM Controller
	 * [1] : Reserved							/ [0] : TrustZoneInfo for CMU_DRAM
	 * [Valid bits] : U(0x0000000D)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_DRAM.TrustZoneInfo	/ [30:0] : Reserved
	 * [Valid bits] : U(0x80000000)
	 */
	mmio_write_32(SYSREG_DRAM + SYSREG_DRAM_TZPC_PROT0SET, U(0x0000000D));
	mmio_write_32(SYSREG_DRAM + SYSREG_DRAM_TZPC_PROT1SET, U(0x00000000));

	/* SYSREG_PCIE */
	/* TZPC_PROT0STAT SFR description
	 * [31:19] : Not Used	/ [18] : NOC_PCIE to TZPC_DBI				/ [17:16] : Not Used
	 * [15] : VDM			/ [14] : IAT			/ [13] : IDE		/ [12] : Not Used
	 * [11:9] : Not Used												/ [8] : pcie_sub_ctrl_inst
	 * [7] : Not Used		/ [6] : MAILBOX_PCIE	/ [5] : GPIO_PCIE	/ [4] : WDT_PCIE
	 * [3] : UART_PCIE		/ [2] : SYSREG_BUSCSR	/ [1] : SYSREG_PCIE	/ [0] : CMU_PCIE
	 * [Valid bits] : U(0x0004E17F)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_PCIE.TrustZoneInfo	/ [30:16] : Not Used
	 * [15:13] : Not Used							/ [12] : PHY3_APB2CR_PARA
	 * [11:9] : Not Used							/ [8] : PHY2_APB2CR_PARA
	 * [7:5] : Not Used								/ [4] : PHY1_APB2CR_PARA
	 * [3:1] : Not Used								/ [0] : PHY0_APB2CR_PARA
	 * [Valid bits] : U(0x80001111)
	 */
#endif

	if (((GET_REVISION == REVISION_EVT0 && CHIPLET_ID == CHIPLET_ID0) ||
		 (GET_REVISION == REVISION_EVT1 && (CHIPLET_ID == CHIPLET_ID0 || CHIPLET_ID == CHIPLET_ID3)))) {
		mmio_write_32(SYSREG_PCIE + SYSREG_PCIE_TZPC_PROT0SET, U(0x0004E17F));
		mmio_write_32(SYSREG_PCIE + SYSREG_PCIE_TZPC_PROT1SET, U(0x00001111));
	}

#ifndef ZEBU_POC
	/* SYSREG_PERI0/1 */
	/* TZPC_PROT0STAT SFR description
	 * [31:12] : Not Used
	 * [11] : GPIO_PERI	/ [10] : PWM_PERI	/ [9] : WDT1_PERI	/ [8] : WDT0_PERI
	 * [7] : I2C1_PERI	/ [6] : I2C0_PERI	/ [5] : UART1_PERI	/ [4] : UART0_PERI
	 * [3:1] : Not Used											/ [0] : CMU_PERI
	 * [Valid bits] : U(0x00000FF1)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_PERI.TrustZoneInfo										/ [30:10] : Not Used
	 * [9] : MAILBOX_PERI_M14	/ [8] : MAILBOX_PERI_M13
	 * [7] : MAILBOX_PERI_M12	/ [6] : MAILBOX_PERI_M11	/ [5] : MAILBOX_PERI_M10	/ [4] : MAILBOX_PERI_M9
	 * [3] : MAILBOX_PERI_M8	/ [2] : MAILBOX_PERI_M7		/ [1] : MAILBOX_PERI_M6		/ [0] : MAILBOX_PERI_M5
	 * [Valid bits] : U(0x800003FF)
	 */
	mmio_write_32(SYSREG_PERI0 + SYSREG_PERI_TZPC_PROT0SET, U(0x00000FF1));
	mmio_write_32(SYSREG_PERI1 + SYSREG_PERI_TZPC_PROT0SET, U(0x00000FF1));
	mmio_write_32(SYSREG_PERI0 + SYSREG_PERI_TZPC_PROT1SET, U(0x000003FF));
	mmio_write_32(SYSREG_PERI1 + SYSREG_PERI_TZPC_PROT1SET, U(0x000003FF));

	/* SYSREG_EBUS_D */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : TrustZoneInfo_SYSREG_BUSCSR_EBUS__CONTROL_SYSREG_TZPC	/ [14:13] : Not Used	/ [12] : NOC_SHBUS_ED_W
	 * [11] : NOC_SHBUS_ED_R	/ [10] : NOC_C_EBUS_D				/ [9] : NOC_D_EBUS_D_W	/ [8] : NOC_D_EBUS_D_R
	 * [7:3] : Not Used			/ [2] : SYSREG_BUSCSR_EBUS_D		/ [1] : Not Used		/ [0] : CMU_EBUS_D
	 * [Valid bits] : U(0x00009F05)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_EBUS_D.TrustZoneInfo								/ [30:16] : Not Used
	 * [15] : TZPC_TCU			/ [14:13] : Not Used							/ [12] : NOC_SHBUS_ED_W
	 * [11] : NOC_SHBUS_ED_R	/ [10] : NOC_C_EBUS_D	/ [9] : NOC_D_EBUS_D_W	/ [8] : NOC_D_EBUS_D_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80009F00)
	 */
	mmio_write_32(SYSREG_EBUS_D + SYSREG_EBUS_TZPC_PROT0SET, U(0x00001F01));
	mmio_write_32(SYSREG_EBUS_D + SYSREG_EBUS_TZPC_PROT1SET, U(0x80009F00));

	/* SYSREG_EBUS_R */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : TrustZoneInfo_SYSREG_BUSCSR_EBUS__CONTROL_SYSREG_TZPC			/ [14:12] : Not Used
	 * [11] : Not Used		/ [10] : NOC_C_EBUS_R	/ [9] : NOC_D_EBUS_R_W	/ [8] : NOC_D_EBUS_R_R
	 * [7:3] : Not Used		/ [2] : SYSREG_BUSCSR	/ [1] : Not Used		/ [0] : CMU_EBUS_R
	 * [Valid bits] : U(0x00008705)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_EBUS_R.TrustZoneInfo						/ [30:16] : Not Used
	 * [15] : TZPC_TCU	/ [14:12] : Not Used
	 * [11] : Not Used	/ [10] : NOC_C_EBUS_R	/ [9] : NOC_D_EBUS_R_W	/ [8] : NOC_D_EBUS_R_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80008700)
	 */
	mmio_write_32(SYSREG_EBUS_R + SYSREG_EBUS_TZPC_PROT0SET, U(0x00008705));
	mmio_write_32(SYSREG_EBUS_R + SYSREG_EBUS_TZPC_PROT1SET, U(0x80008700));

	/* SYSREG_EBUS_U */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : TrustZoneInfo_SYSREG_BUSCSR_EBUS__CONTROL_SYSREG_TZPC	/ [14:13] : Not Used	/ [12] : NOC_SHBUS_EU_W
	 * [11] : NOC_SHBUS_EU_R	/ [10] : NOC_C_EBUS_U			/ [9] : NOC_D_EBUS_U_W		/ [8] : NOC_D_EBUS_U_R
	 * [7:3] : Not Used			/ [2] : SYSREG_BUSCSR_EBUS_U	/ [1] : Not Used			/ [0] : CMU_EBUS_U
	 * [Valid bits] : U(0x00009F05)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_EBUS_U.TrustZoneInfo		/ [30:16] : Not Used
	 * [15] : TZPC_TCU			/ [14:13] : Not Used	/ [12] : NOC_SHBUS_EU_W
	 * [11] : NOC_SHBUS_EU_R	/ [10] : NOC_C_EBUS_U	/ [9:0] : Not Used
	 * [Valid bits] : U(0x80009C00)
	 */
	mmio_write_32(SYSREG_EBUS_U + SYSREG_EBUS_TZPC_PROT0SET, U(0x00001F01));
	mmio_write_32(SYSREG_EBUS_U + SYSREG_EBUS_TZPC_PROT1SET, U(0x80009C00));

	/* SYSREG_NBUS_D */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : TrustZoneInfo_SYSREG_BUSCSR_NBUS__CONTROL_SYSREG_TZPC					/ [14:12] : Not Used
	 * [11] : Not Used		/ [10] : NOC_C_NBUS_D			/ [9] : NOC_D_NBUS_D_W	/ [8] : NOC_D_NBUS_D_R
	 * [7:3] : Not Used		/ [2] : SYSREG_BUSCSR_NBUS_D	/ [1] : Not Used		/ [0] : CMU_NBUS_D
	 * [Valid bits] : U(0x00008705)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_NBUS_D.TrustZoneInfo						/ [30:16] : Not Used
	 * [15] : CBUS DBG TZPC												/ [14:12] : Not Used
	 * [11:10] : Not Used	/ [9] : NOC_D_NBUS_D_W (AXI2APB_DBG_NBUS_D)	/ [8] : NOC_D_NBUS_D_R (AXI2APB_DBG_NBUS_D)
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80008300)
	 */
	mmio_write_32(SYSREG_NBUS_D + SYSREG_NBUS_TZPC_PROT0SET, U(0x00000701));
	mmio_write_32(SYSREG_NBUS_D + SYSREG_NBUS_TZPC_PROT1SET, U(0x80008300));

	/* SYSREG_NBUS_L */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : TrustZoneInfo_SYSREG_BUSCSR_NBUS__CONTROL_SYSREG_TZPC
	 * [14:11] : Not Used	/ [10] : NOC_C_NBUS_L			/ [9] : NOC_D_NBUS_L_W	/ [8] : NOC_D_NBUS_L_R
	 * [7:4] : Not Used
	 * [3] : GPIO_NBUS_L	/ [2] : SYSREG_BUSCSR_NBUS_L	/ [1] : Not Used		/ [0] : CMU_NBUS_L
	 * [Valid bits] : U(0x0000870D)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_NBUS_L.TrustZoneInfo			/ [30:16] : Not Used
	 * [15] : CBUS DBG TZPC									/ [14:0] : Not Used
	 * [Valid bits] : U(0x80008000)
	 */
	mmio_write_32(SYSREG_NBUS_L + SYSREG_NBUS_TZPC_PROT0SET, U(0x00000709));
	mmio_write_32(SYSREG_NBUS_L + SYSREG_NBUS_TZPC_PROT1SET, U(0x80008000));

	/* SYSREG_NBUS_U */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used
	 * [15] : SYSREG_BUSCSR_NBUS_U_TZPC_CTRL			/ [14:12] : Not Used
	 * [11] : Not Used	/ [10] : NOC_C_NBUS_U			/ [9] : NOC_D_NBUS_U_W	/ [8] : NOC_D_NBUS_U_R
	 * [7:3] : Not Used	/ [2] : SYSREG_BUSCSR_NBUS_U	/ [1] : Not Used		/ [0] : CMU_NBUS_U
	 * [Valid bits] : U(0x00008705)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_NBUS_U.TrustZoneInfo		/ [30:16] : Not Used
	 * [15] : TZPC_TCU	/ [14:12] : Not Used
	 * [11] : Not Used	/ [10] : NOC_C_NBUS_U	/ [9] : NOC_D_NBUS_U_W	/ [8] : NOC_D_NBUS_U_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80008700)
	 */
	mmio_write_32(SYSREG_NBUS_U + SYSREG_NBUS_TZPC_PROT0SET, U(0x00008705));
	mmio_write_32(SYSREG_NBUS_U + SYSREG_NBUS_TZPC_PROT1SET, U(0x80008700));

	/* SYSREG_SBUS_D */
	/* TZPC_PROT0STAT SFR description
	 * [31:12] : Not Used
	 * [11] : Not Used	/ [10] : NOC_C_SBUS_D	/ [9] : NOC_D_SBUS_D_W	/ [8] : NOC_D_SBUS_D_R
	 * [7:1] : Not Used													/ [0] : CMU_SBUS_D
	 * [Valid bits] : U(0x00000701)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_SBUS_D.TrustZoneInfo	/ [30:16] : Not Used
	 * [15] : TZPC_TCU								/ [14:0] : Not Used
	 * [Valid bits] : U(0x80008000)
	 */
	mmio_write_32(SYSREG_SBUS_D + SYSREG_SBUS_TZPC_PROT0SET, U(0x00000701));
	mmio_write_32(SYSREG_SBUS_D + SYSREG_SBUS_TZPC_PROT1SET, U(0x80008000));

	/* SYSREG_SBUS_L */
	/* TZPC_PROT0STAT SFR description
	 * [31:12] : Not Used
	 * [11] : NOC_MBUS_W	/ [10] : NOC_MBUS_R		/ [9] : NOC_MBUS_W	/ [8] : NOC_MBUS_R
	 * [7:1] : Not Used													/ [0] : CMU_SBUS_L
	 * [Valid bits] : U(0x00000F01)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_SBUS_L.TrustZoneInfo	/ [30:12] : Not Used
	 * [11:10] : Not Used							/ [9] : NOC_MBUS_W	/ [8] : NOC_MBUS_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80000300)
	 */
	mmio_write_32(SYSREG_SBUS_L + SYSREG_SBUS_TZPC_PROT0SET, U(0x00000F01));
	mmio_write_32(SYSREG_SBUS_L + SYSREG_SBUS_TZPC_PROT1SET, U(0x00000300));

	/* SYSREG_SBUS_U */
	/* TZPC_PROT0STAT SFR description
	 * [31:10] : Not Used	/ [9] : NOC_D_SBUS_U_W	/ [8] : NOC_D_SBUS_U_R
	 * [7:1] : Not Used								/ [0] : CMU_SBUS_U
	 * [Valid bits] : U(0x00000301)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_SBUS_U.TrustZoneInfo	/ [30:12] : Not Used
	 * [11:10] : Not Used	/ [9] : NOC_D_SBUS_U_W	/ [8] : NOC_D_SBUS_U_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80000300)
	 */
	mmio_write_32(SYSREG_SBUS_U + SYSREG_SBUS_TZPC_PROT0SET, U(0x00000301));
	mmio_write_32(SYSREG_SBUS_U + SYSREG_SBUS_TZPC_PROT1SET, U(0x00000300));

	/* SYSREG_WBUS_D */
	/* TZPC_PROT0STAT SFR description
	 * [31:10] : Not Used							/ [9] : NOC_DBUS_W	/ [8] : NOC_DBUS_R
	 * [7:3] : Not Used		/ [2] : SYSREG_BUSCSR	/ [1] : Not Used	/ [0] : CMU_WBUS_D
	 * [Valid bits] : U(0x00000305)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_WBUS_D.TrustZoneInfo	/ [30:0] : Not Used
	 * [Valid bits] : U(0x80000000)
	 */
	mmio_write_32(SYSREG_WBUS_D + SYSREG_WBUS_TZPC_PROT0SET, U(0x00000301));
	mmio_write_32(SYSREG_WBUS_D + SYSREG_WBUS_TZPC_PROT1SET, U(0x80000000));

	/* SYSREG_WBUS_U */
	/* TZPC_PROT0STAT SFR description
	 * [31:10] : Not Used							/ [9] : NOC_DBUS_W	/ [8] : NOC_DBUS_R
	 * [7:3] : Not Used		/ [2] : SYSREG_BUSCSR	/ [1] : Not Used	/ [0] : CMU_WBUS_U
	 * [Valid bits] : U(0x00000305)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : Used for SYSREG_WBUS_U.TrustZoneInfo						/ [30:12] : Not Used
	 * [11:10] : Not Used							/ [9] : NOC_DBUS_W	/ [8] : NOC_DBUS_R
	 * [7:0] : Not Used
	 * [Valid bits] : U(0x80000300)
	 */
	mmio_write_32(SYSREG_WBUS_U + SYSREG_SBUS_TZPC_PROT0SET, U(0x00000301));
	mmio_write_32(SYSREG_WBUS_U + SYSREG_SBUS_TZPC_PROT1SET, U(0x80000300));

	/* SYSREG_DCL0/1 */
	/* TZPC_PROT0STAT SFR description
	 * [31:8] : Not Used
	 * [7] : ADD_CON3	/ [6] : ADD_CON2	/ [5] : ADD_CON1	/ [4] : ADD_CON0
	 * [3] : PVT_CON1	/ [2] : PVT_CON0	/ [1] : Not Used	/ [0] : CMU_DCL
	 * [Valid bits] : U(0x000000FD)
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31] : SYSREG_DCL.TrustZoneInfo		/ [30:0] : Not Used
	 * [Valid bits] : U(0x80000000)
	 */
	mmio_write_32(SYSREG_DCL0 + SYSREG_SBUS_TZPC_PROT0SET, U(0x000000FD));
	mmio_write_32(SYSREG_DCL1 + SYSREG_SBUS_TZPC_PROT0SET, U(0x000000FD));
	mmio_write_32(SYSREG_DCL0 + SYSREG_SBUS_TZPC_PROT1SET, U(0x80000000));
	mmio_write_32(SYSREG_DCL1 + SYSREG_SBUS_TZPC_PROT1SET, U(0x80000000));

	uint32_t second_chiplet_count = mmio_read_32(CPMU_PRIVATE + INFORM4);

	if (second_chiplet_count > 0) {
		if (CHIPLET_ID == 0 || CHIPLET_ID == 3) {
			mmio_write_32(SYSREG_RBC_V10_PRIVATE + SYSREG_RBC_V_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_V10_PRIVATE + SYSREG_RBC_V_TZPC_PROT1SET, U(0x80000000));
			mmio_write_32(SYSREG_RBC_V11_PRIVATE + SYSREG_RBC_V_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_V11_PRIVATE + SYSREG_RBC_V_TZPC_PROT1SET, U(0x80000000));
		} else {
			mmio_write_32(SYSREG_RBC_V00_PRIVATE + SYSREG_RBC_V_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_V00_PRIVATE + SYSREG_RBC_V_TZPC_PROT1SET, U(0x80000000));
			mmio_write_32(SYSREG_RBC_V01_PRIVATE + SYSREG_RBC_V_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_V01_PRIVATE + SYSREG_RBC_V_TZPC_PROT1SET, U(0x80000000));
		}

		if (second_chiplet_count > 2) {
			mmio_write_32(SYSREG_RBC_H00_PRIVATE + SYSREG_RBC_H_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_H00_PRIVATE + SYSREG_RBC_H_TZPC_PROT1SET, U(0x80000000));
			mmio_write_32(SYSREG_RBC_H01_PRIVATE + SYSREG_RBC_H_TZPC_PROT0SET, U(0x85));
			mmio_write_32(SYSREG_RBC_H01_PRIVATE + SYSREG_RBC_H_TZPC_PROT1SET, U(0x80000000));
		}
	}
#endif /* ZEBU_POC */
}

void tzpc_init_gpio(void)
{
#ifndef ZEBU_POC
	/* Sets the secure mode
	 * 0x0 = Secure access only
	 * 0x1 = All transaction can access
	 * 0x2 ~ 0x3 = Non-secure access only
	 */

	/* GPIO_ROT */
	/* TZPC_ROT_0 SFR description
	 * [31:22] : RSVD0		/ [21:20] : _GPC1_2_	/ [19:18] : _GPC1_1_	/ [17:16] : _GPC1_0_
	 * [15:14] : _GPC0_7_	/ [13:12] : _GPC0_6_	/ [11:10] : _GPC0_5_	/ [9:8]   : _GPC0_4_
	 * [7:6]   : _GPC0_3_	/ [5:4]   : _GPC0_2_	/ [3:2]   : _GPC0_1_	/ [1:0]   : _GPC0_0_
	 */
	mmio_write_32(GPIO_ROT + GPIO_ROT_TZPC_0, U(0x00155555));

	/* GPIO_NBUS_L */
	/* TZPC_NBUS_L_0 SFR description
	 * [31:30] : _GPD1_7_	/ [29:28] : _GPD1_6_	/ [27:26] : _GPD1_5_	/ [25:24] : _GPD1_4_
	 * [23:22] : _GPD1_3_	/ [21:20] : _GPD1_2_	/ [19:18] : _GPD1_1_	/ [17:16] : _GPD1_0_
	 * [15:14] : _GPD0_7_	/ [13:12] : _GPD0_6_	/ [11:10] : _GPD0_5_	/ [9:8]   : _GPD0_4_
	 * [7:6]   : _GPD0_3_	/ [5:4]   : _GPD0_2_	/ [3:2]   : _GPD0_1_	/ [1:0]   : _GPD0_0_
	 */
	/* TZPC_NBUS_L_1 SFR description
	 * [31:30] : _GPD3_7_	/ [29:28] : _GPD3_6_	/ [27:26] : _GPD3_5_	/ [25:24] : _GPD3_4_
	 * [23:22] : _GPD3_3_	/ [21:20] : _GPD3_2_	/ [19:18] : _GPD3_1_	/ [17:16] : _GPD3_0_
	 * [15:14] : _GPD2_7_	/ [13:12] : _GPD2_6_	/ [11:10] : _GPD2_5_	/ [9:8]   : _GPD2_4_
	 * [7:6]   : _GPD2_3_	/ [5:4]   : _GPD2_2_	/ [3:2]   : _GPD2_1_	/ [1:0]   : _GPD2_0_
	 */
	/* TZPC_NBUS_L_2 SFR description
	 * [31:30] : _GPD5_7_	/ [29:28] : _GPD5_6_	/ [27:26] : _GPD5_5_	/ [25:24] : _GPD5_4_
	 * [23:22] : _GPD5_3_	/ [21:20] : _GPD5_2_	/ [19:18] : _GPD5_1_	/ [17:16] : _GPD5_0_
	 * [15:14] : _GPD4_7_	/ [13:12] : _GPD4_6_	/ [11:10] : _GPD4_5_	/ [9:8]   : _GPD4_4_
	 * [7:6]   : _GPD4_3_	/ [5:4]   : _GPD4_2_	/ [3:2]   : _GPD4_1_	/ [1:0]   : _GPD4_0_
	 */
	/* TZPC_NBUS_L_3 SFR description
	 * [31:16] : RSVD0	/ [15:8] : RSVD1
	 * [7:6] : _GPD6_3_	/ [5:4] : _GPD6_2_	/ [3:2] : _GPD6_1_	/ [1:0] : _GPD6_0_
	 */
	mmio_write_32(GPIO_NBUS_L + GPIO_NBUS_L_TZPC_0, U(0x55555555));
	mmio_write_32(GPIO_NBUS_L + GPIO_NBUS_L_TZPC_1, U(0x55555555));
	mmio_write_32(GPIO_NBUS_L + GPIO_NBUS_L_TZPC_2, U(0x55555555));
	mmio_write_32(GPIO_NBUS_L + GPIO_NBUS_L_TZPC_3, U(0x00000055));

	/* GPIO_PCIE */
	/* TZPC_PCIE_0 SFR description
	 * [31:30] : _GPA1_7_	/ [29:28] : _GPA1_6_	/ [27:26] : _GPA1_5_	/ [25:24] : _GPA1_4_
	 * [23:22] : _GPA1_3_	/ [21:20] : _GPA1_2_	/ [19:18] : _GPA1_1_	/ [17:16] : _GPA1_0_
	 * [15:6]  : RSVD0		/ [5:4]   : _GPA0_2_	/ [3:2]   : _GPA0_1_	/ [1:0]   : _GPA0_0_
	 */
	/* TZPC_PCIE_1 SFR description
	 * [31:16] : RSVD0		/ [15:4]  : RSVD1		/ [3:2]   : _GPA2_1_	/ [1:0]   : _GPA2_0_
	 */

	if (((GET_REVISION == REVISION_EVT0 && CHIPLET_ID == CHIPLET_ID0) ||
		 (GET_REVISION == REVISION_EVT1 && (CHIPLET_ID == CHIPLET_ID0 || CHIPLET_ID == CHIPLET_ID3)))) {
		mmio_write_32(GPIO_PCIE + GPIO_PCIE_TZPC_0, U(0x55550015));
		mmio_write_32(GPIO_PCIE + GPIO_PCIE_TZPC_1, U(0x00000005));
	}

	/* GPIO_PERI0/1 */
	/* TZPC_PERI_0 SFR description
	 * [31:30] : _GPB1_7_	/ [29:28] : _GPB1_6_	/ [27:26] : _GPB1_5_	/ [25:24] : _GPB1_4_
	 * [23:22] : _GPB1_3_	/ [21:20] : _GPB1_2_	/ [19:18] : _GPB1_1_	/ [17:16] : _GPB1_0_
	 * [15:14] : _GPB0_7_	/ [13:12] : _GPB0_6_	/ [11:10] : _GPB0_5_	/ [9:8]   : _GPB0_4_
	 * [7:6]   : _GPB0_3_	/ [5:4]   : _GPB0_2_	/ [3:2]   : _GPB0_1_	/ [1:0]   : _GPB0_0_
	 */
	/* TZPC_PERI_1 SFR description
	 * [31:24] : RSVD0
	 * [23:22] : _GPB3_3_	/ [21:20] : _GPB3_2_	/ [19:18] : _GPB3_1_	/ [17:16] : _GPB3_0_
	 * [15:8]  : RSVD1
	 * [7:6]   : _GPB2_3_	/ [5:4]   : _GPB2_2_	/ [3:2]   : _GPB2_1_	/ [1:0]   : _GPB2_0_
	 */
	/* TZPC_PERI_2 SFR description
	 * [31:20] : RSVD0								/ [19:18] : _GPB5_1_	/ [17:16] : _GPB5_0_
	 * [15:8]  : RSVD1
	 * [7:6]   : _GPB4_3_	/ [5:4]   : _GPB4_2_	/ [3:2]   : _GPB4_1_	/ [1:0]   : _GPB4_0_
	 */
	/* TZPC_PERI_3 SFR description
	 * [31:30] : _GPB7_7_	/ [29:28] : _GPB7_6_	/ [27:26] : _GPB7_5_	/ [25:24] : _GPB7_4_
	 * [23:22] : _GPB7_3_	/ [21:20] : _GPB7_2_	/ [19:18] : _GPB7_1_	/ [17:16] : _GPB7_0_
	 * [15:14] : _GPB6_7_	/ [13:12] : _GPB6_6_	/ [11:10] : _GPB6_5_	/ [9:8]   : _GPB6_4_
	 * [7:6]   : _GPB6_3_	/ [5:4]   : _GPB6_2_	/ [3:2]   : _GPB6_1_	/ [1:0]   : _GPB6_0_
	 */
	/* TZPC_PERI_4 SFR description
	 * [31:30] : _GPB9_7_	/ [29:28] : _GPB9_6_	/ [27:26] : _GPB9_5_	/ [25:24] : _GPB9_4_
	 * [23:22] : _GPB9_3_	/ [21:20] : _GPB9_2_	/ [19:18] : _GPB9_1_	/ [17:16] : _GPB9_0_
	 * [15:12] : RSVD0								/ [11:10] : _GPB8_5_	/ [9:8]   : _GPB8_4_
	 * [7:6]   : _GPB8_3_	/ [5:4]   : _GPB8_2_	/ [3:2]   : _GPB8_1_	/ [1:0]   : _GPB8_0_
	 */
	/* TZPC_PERI_5 SFR description
	 * [31:30] : _GPB11_7_	/ [29:28] : _GPB11_6_	/ [27:26] : _GPB11_5_	/ [25:24] : _GPB11_4_
	 * [23:22] : _GPB11_3_	/ [21:20] : _GPB11_2_	/ [19:18] : _GPB11_1_	/ [17:16] : _GPB11_0_
	 * [15:14] : _GPB10_7_	/ [13:12] : _GPB10_6_	/ [11:10] : _GPB10_5_	/ [9:8]   : _GPB10_4_
	 * [7:6]   : _GPB10_3_	/ [5:4]   : _GPB10_2_	/ [3:2]   : _GPB10_1_	/ [1:0]   : _GPB10_0_
	 */
	/* TZPC_PERI_6 SFR description
	 * [31:24] : RSVD0
	 * [23:22] : _GPB13_3_	/ [21:20] : _GPB13_2_	/ [19:18] : _GPB13_1_	/ [17:16] : _GPB13_0_
	 * [15:14] : _GPB12_7_	/ [13:12] : _GPB12_6_	/ [11:10] : _GPB12_5_	/ [9:8]   : _GPB12_4_
	 * [7:6]   : _GPB12_3_	/ [5:4]   : _GPB12_2_	/ [3:2]   : _GPB12_1_	/ [1:0]   : _GPB12_0_
	 */
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_0, U(0x55555555));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_1, U(0x00550055));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_2, U(0x00050055));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_3, U(0x55555555));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_4, U(0x55550555));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_5, U(0x55555555));
	mmio_write_32(GPIO_PERI0 + GPIO_PERI_TZPC_6, U(0x00555555));

	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_0, U(0x55555555));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_1, U(0x00550055));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_2, U(0x00050055));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_3, U(0x55555555));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_4, U(0x55550555));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_5, U(0x55555555));
	mmio_write_32(GPIO_PERI1 + GPIO_PERI_TZPC_6, U(0x00555555));
#endif /* ZEBU_POC */
}

void bl31_platform_setup(void)
{
	uint64_t reg;
	/* Set ACTLR to access ECTLR for exclusive signaling */
	reg = read_actlr_el3();
	/* TODO : replace MAGIC NUMBER*/
	reg |= 0x2;
	write_actlr_el3(reg);

	reg = read_actlr_el2();
	reg |= 0x2;
	write_actlr_el2(reg);

#ifndef ZEBU_POC
#if (__TARGET_CP == 0)
	rebel_bakery_lock_acquire(BAKERY_ID_CP0);
#elif (__TARGET_CP == 1)
	rebel_bakery_lock_acquire(BAKERY_ID_CP1);
#endif
#endif /* ZEBU_POC */

	/* Init common gic driver and enable GICR connected to primary core(cpu0) */
	plat_arm_gic_driver_init();
	plat_arm_gic_init();

#ifndef ZEBU_POC
#if (__TARGET_CP == 0)
	rebel_bakery_lock_release(BAKERY_ID_CP0);
#elif (__TARGET_CP == 1)
	rebel_bakery_lock_release(BAKERY_ID_CP1);
#endif
#endif /* ZEBU_POC */

	tzpc_init_sysreg();
	tzpc_init_gpio();
}

entry_point_info_t *bl31_plat_get_next_image_ep_info(uint32_t type)
{
	if (type == NON_SECURE)
		return &bl33_image_ep_info;

	return NULL;
}

uint32_t plat_get_syscnt_freq2(void)
{
	return CORE_TIMER_FREQ;
}
