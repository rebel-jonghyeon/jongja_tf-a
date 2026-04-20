#
# Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

REBEL_PLAT				:=	plat/rebel
REBEL_PLAT_SOC			:=	${REBEL_PLAT}/${PLAT}
REBEL_PLAT_COMMON		:=	${REBEL_PLAT}/common

include ${REBEL_PLAT_COMMON}/common.mk

include lib/xlat_tables_v2/xlat_tables.mk

GICV3_SUPPORT_GIC600	:=	1
include drivers/arm/gic/v3/gicv3.mk

# To speed-up UART logging at ZEBU, this will set a different baud-rate as per target
ifeq ($(ZEBU),1)
ZEBU					:= 1
$(eval $(call add_define,ZEBU))
PLAT_BAUDRATE			:= 7812500
DCL_CNT					:= ${DCL_CNT}
else
PLAT_BAUDRATE			:= 115200
DCL_CNT					:= 2
endif
$(eval $(call add_define,PLAT_BAUDRATE))
$(eval $(call add_define,DCL_CNT))
$(eval $(call add_define,CHIPLET_COUNT))

$(info BUS_FREQ = ${BUS_FREQ}Mhz)
$(eval $(call add_define,BUS_FREQ))
$(info DCL_FREQ = ${DCL_FREQ}Mhz)
$(eval $(call add_define,DCL_FREQ))

$(info HBM_DATA_RATE = ${HBM_DATA_RATE} Mbps)
$(eval $(call add_define,HBM_DATA_RATE))

$(info UCIE_DATA_RATE = ${UCIE_DATA_RATE} MT/s)
$(eval $(call add_define,UCIE_DATA_RATE))

$(info EVT_VER = EVT${EVT_VER})
$(eval $(call add_define,EVT_VER))

ifeq ($(NCHANNEL),ch1)
HBM3_NUM_CH				:= 1
else
HBM3_NUM_CH				:= 16
endif
$(eval $(call add_define,HBM3_NUM_CH))

ifeq ($(HBM_TEST),1)
HBM_EOM					:= 1
$(eval $(call add_define,HBM_EOM))
else ifeq ($(HBM_TEST),2)
HBM_AMT					:= 1
$(eval $(call add_define,HBM_AMT))
endif

USE_GPT					:= $(USE_GPT)
$(eval $(call add_define,USE_GPT))

PCIE_PHY_SRAM_LOAD		:= $(PCIE_PHY_SRAM_LOAD)
$(eval $(call add_define,PCIE_PHY_SRAM_LOAD))

ifeq ($(CP), 0)
__TARGET_CP				:= 0
else ifeq ($(CP), 1)
__TARGET_CP				:= 1
endif
$(eval $(call add_define,__TARGET_CP))

PLAT_INCLUDES			:=	-I${REBEL_PLAT_SOC}/include \
							-I${REBEL_PLAT_COMMON}/include \
							-Idrivers/clk/clk_samsung \
							-I$(abspath ../../../drivers/hbm3)	\
							-I$(abspath ../../../common/bakery_lock) \
							-I$(abspath ../../../drivers/gpio)

PLAT_BL_COMMON_SOURCES	:=	drivers/ti/uart/aarch64/16550_console.S	\
							drivers/delay_timer/delay_timer.c	\
							${REBEL_PLAT_SOC}/rebel_h_pmu.c \
							drivers/delay_timer/generic_delay_timer.c	\
							plat/common/aarch64/platform_mp_stack.S	\
							${REBEL_PLAT_SOC}/plat_helper.S	\
							${REBEL_PLAT_SOC}/rebel_h_topology.c \
							lib/cpus/aarch64/wa_cve_2017_5715_bpiall.S \
							${XLAT_TABLES_LIB_SRCS}

IO_SOURCES				+=	common/desc_image_load.c \
							drivers/io/io_memmap.c \
							drivers/io/io_storage.c

BL1_SOURCES				+=	${IO_SOURCES} \
							lib/cpus/aarch64/cortex_a73.S \
							${REBEL_PLAT_SOC}/rebel_h_pcie.c \
							${REBEL_PLAT_SOC}/rebel_h_plat.c \
							${REBEL_PLAT_SOC}/rebel_h_rbc.c \
							${REBEL_PLAT_SOC}/rebel_h_bl1_setup.c \
							drivers/synopsys/qspi_bridge/qspi_bridge.c \
							drivers/synopsys/watchdog/dw_wdt.c \
							drivers/partition/partition_simple.c \
							drivers/partition/gpt.c \
							drivers/aw/ucie.c \
							drivers/clk/clk_samsung/cmu.c \
							drivers/arm/pl330/pl330.c \
							drivers/synopsys/qspi_boot/qspi_boot.c \
							drivers/synopsys/qspi_apb/qspi_apb.c \
							$(abspath ../../../drivers/gpio/gpio.c)

BL1_CPPFLAGS += -march=armv8-a+crc

BL2_SOURCES				+=	${IO_SOURCES} \
							${REBEL_PLAT_SOC}/rebel_h_image_load.c \
							${REBEL_PLAT_SOC}/rebel_h_bl2_setup.c \
							${REBEL_PLAT_SOC}/rebel_h_plat.c \
							${REBEL_PLAT_SOC}/rebel_h_pcie.c \
							${REBEL_PLAT_SOC}/rebel_h_rbc.c \
							drivers/smmu/smmu.c \
							drivers/synopsys/qspi_bridge/qspi_bridge.c \
							drivers/partition/partition_simple.c \
							drivers/partition/gpt.c \
							drivers/hbm3/hbm3_init.c \
							drivers/hbm3/hbm3_chipid.c \
							drivers/clk/clk_samsung/cmu.c \
							drivers/arm/pl330/pl330.c	\
							drivers/mailbox/mailbox.c	\
							drivers/aw/ucie.c	\
							$(addprefix ../../../drivers/hbm3/,	\
							hbm3.c	\
							tmrs.c	\
							icon.c	\
							)	\
							$(abspath ../../../common/bakery_lock/bakery_lock.c)

ifeq ($(HBM_EOM),1)
BL2_SOURCES				+=	drivers/hbm3/mt_eom.c \
							drivers/hbm3/mt_common.c \
							drivers/hbm3/mt_alg.c

else ifeq ($(HBM_AMT),1)
BL2_SOURCES				+=	drivers/hbm3/mt_test.c \
							drivers/hbm3/mt_common.c \
							drivers/hbm3/mt_alg.c \
							drivers/hbm3/mt_arb.c \
							drivers/hbm3/mt_amt.c
endif

BL2_CPPFLAGS += -march=armv8-a+crc

BL31_SOURCES			+=	${GICV3_SOURCES} \
							lib/cpus/aarch64/cortex_a73.S \
							plat/common/plat_psci_common.c \
							${REBEL_PLAT_SOC}/rebel_h_plat.c \
							plat/common/plat_gicv3.c \
							plat/arm/common/arm_gicv3.c \
							drivers/synopsys/watchdog/dw_wdt.c \
							${REBEL_PLAT_SOC}/rebel_h_pm.c \
							${REBEL_PLAT_SOC}/rebel_h_bl31_setup.c \
							${REBEL_PLAT_SOC}/rebel_h_sip_svc.c \
							drivers/synopsys/qspi_boot/qspi_boot.c \
							drivers/flash/mt25q_flash.c \
							$(abspath ../../../common/bakery_lock/bakery_lock.c)

# Common
LOG_LEVEL						:= 30

# PSCI: to avoid losing psci_locks
WARMBOOT_ENABLE_DCACHE_EARLY	:= 1

# CA73 Errata for CPU revision
ERRATA_A73_855423				:= 1
ERRATA_A73_852427				:= 1
WORKAROUND_CVE_2017_5715		:= 0
WORKAROUND_CVE_2022_23960		:= 1

# bl31 common level
RESET_TO_BL31					:= 1
ifeq ($(ZEBU_POC),1)
COLD_BOOT_SINGLE_CPU			:= 0
PROGRAMMABLE_RESET_ADDRESS      := 0

ZEBU_POC						:= 1
$(eval $(call add_define,ZEBU_POC))
else
COLD_BOOT_SINGLE_CPU			:= 1
PROGRAMMABLE_RESET_ADDRESS      := 1
endif
