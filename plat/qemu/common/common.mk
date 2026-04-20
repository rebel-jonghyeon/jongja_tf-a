#
<<<<<<< HEAD
# Copyright (c) 2023, Linaro Limited and Contributors. All rights reserved.
=======
# Copyright (c) 2023-2024, Linaro Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
#
# SPDX-License-Identifier: BSD-3-Clause
#

include lib/libfdt/libfdt.mk
include common/fdt_wrappers.mk

PLAT_INCLUDES		:=	-Iinclude/plat/arm/common/		\
<<<<<<< HEAD
=======
				-I${PLAT_QEMU_COMMON_PATH}/		\
>>>>>>> upstream_import/upstream_v2_14_1
				-I${PLAT_QEMU_COMMON_PATH}/include	\
				-I${PLAT_QEMU_PATH}/include		\
				-Iinclude/common/tbbr

ifeq (${ARCH},aarch32)
QEMU_CPU_LIBS		:=	lib/cpus/${ARCH}/cortex_a15.S
else
QEMU_CPU_LIBS		:=	lib/cpus/aarch64/aem_generic.S		\
				lib/cpus/aarch64/cortex_a53.S		\
				lib/cpus/aarch64/cortex_a55.S		\
				lib/cpus/aarch64/cortex_a57.S		\
				lib/cpus/aarch64/cortex_a72.S		\
				lib/cpus/aarch64/cortex_a76.S		\
				lib/cpus/aarch64/cortex_a710.S		\
<<<<<<< HEAD
				lib/cpus/aarch64/neoverse_n_common.S	\
=======
>>>>>>> upstream_import/upstream_v2_14_1
				lib/cpus/aarch64/neoverse_n1.S		\
				lib/cpus/aarch64/neoverse_v1.S		\
				lib/cpus/aarch64/neoverse_n2.S		\
				lib/cpus/aarch64/qemu_max.S

PLAT_INCLUDES		+=	-Iinclude/plat/arm/common/${ARCH}
<<<<<<< HEAD

# Cpu core architecture level:
# v8.0: a53, a57, a72
# v8.2: a76, n1
# v8.4: v1
# v9.0: a710, n2
#
# let treat v9.0 as v8.5 as they share cpu features
# https://developer.arm.com/documentation/102378/0201/Armv8-x-and-Armv9-x-extensions-and-features

ARM_ARCH_MAJOR		:=	8
ARM_ARCH_MINOR		:=	5
=======
>>>>>>> upstream_import/upstream_v2_14_1
endif

PLAT_BL_COMMON_SOURCES	:=	${PLAT_QEMU_COMMON_PATH}/qemu_common.c		\
				${PLAT_QEMU_COMMON_PATH}/qemu_console.c		\
				drivers/arm/pl011/${ARCH}/pl011_console.S

include lib/xlat_tables_v2/xlat_tables.mk
PLAT_BL_COMMON_SOURCES	+=	${XLAT_TABLES_LIB_SRCS}

ifneq ($(ENABLE_STACK_PROTECTOR), 0)
	PLAT_BL_COMMON_SOURCES += ${PLAT_QEMU_COMMON_PATH}/qemu_stack_protector.c
endif

BL1_SOURCES		+=	drivers/io/io_semihosting.c		\
				drivers/io/io_storage.c			\
				drivers/io/io_fip.c			\
				drivers/io/io_memmap.c			\
				lib/semihosting/semihosting.c		\
				lib/semihosting/${ARCH}/semihosting_call.S	\
				${PLAT_QEMU_COMMON_PATH}/qemu_io_storage.c	\
				${PLAT_QEMU_COMMON_PATH}/${ARCH}/plat_helpers.S	\
				${PLAT_QEMU_COMMON_PATH}/qemu_bl1_setup.c	\
				${QEMU_CPU_LIBS}

BL2_SOURCES		+=	drivers/io/io_semihosting.c		\
				drivers/io/io_storage.c			\
				drivers/io/io_fip.c			\
				drivers/io/io_memmap.c			\
				lib/semihosting/semihosting.c		\
				lib/semihosting/${ARCH}/semihosting_call.S		\
				${PLAT_QEMU_COMMON_PATH}/qemu_io_storage.c		\
				${PLAT_QEMU_COMMON_PATH}/${ARCH}/plat_helpers.S		\
				${PLAT_QEMU_COMMON_PATH}/qemu_bl2_setup.c		\
				${PLAT_QEMU_COMMON_PATH}/qemu_bl2_mem_params_desc.c	\
				${PLAT_QEMU_COMMON_PATH}/qemu_image_load.c		\
				common/desc_image_load.c		\
<<<<<<< HEAD
				common/fdt_fixup.c
=======
				common/fdt_fixup.c			\
				${FDT_WRAPPERS_SOURCES}
>>>>>>> upstream_import/upstream_v2_14_1

BL31_SOURCES		+=	${QEMU_CPU_LIBS}				\
				lib/semihosting/semihosting.c			\
				lib/semihosting/${ARCH}/semihosting_call.S	\
				plat/common/plat_psci_common.c			\
				${PLAT_QEMU_COMMON_PATH}/aarch64/plat_helpers.S	\
				${PLAT_QEMU_COMMON_PATH}/qemu_bl31_setup.c	\
				common/fdt_fixup.c				\
				${QEMU_GIC_SOURCES}

# CPU flag enablement
ifeq (${ARCH},aarch64)

<<<<<<< HEAD
# Later QEMU versions support SME and SVE.
=======
# Cpu core architecture level:
# v8.0: a53, a57, a72
# v8.2: a55, a76, n1
# v8.4: v1
# v9.0: a710, n2
#
#
# We go v8.0 by default and will enable all features we want

ARM_ARCH_MAJOR		?=	8
ARM_ARCH_MINOR		?=	0

# 8.0
ENABLE_FEAT_CSV2_2	:=	2

# 8.1
ENABLE_FEAT_PAN		:=	2
ENABLE_FEAT_VHE		:=	2

# 8.2
# TF-A currently does not permit dynamic detection of FEAT_RAS
# so this is the only safe setting
ENABLE_FEAT_RAS		:=	0

# 8.4
ENABLE_FEAT_SEL2	:=	2
ENABLE_FEAT_DIT		:=	2
ENABLE_TRF_FOR_NS	:=	2

# 8.5
ENABLE_FEAT_RNG		:=	2
# TF-A currently does not do dynamic detection of FEAT_SB.
# Compiler puts SB instruction when it is enabled.
ENABLE_FEAT_SB		:=	0

# 8.6
ENABLE_FEAT_ECV		:=	2
ENABLE_FEAT_FGT		:=	2

# 8.7
ENABLE_FEAT_HCX		:=	2

# 8.8
ENABLE_FEAT_TCR2	:=	2
ENABLE_FEAT_SCTLR2	:=	2
ENABLE_FEAT_S2PIE	:=	2
ENABLE_FEAT_S1PIE	:=	2
ENABLE_FEAT_S2POE	:=	2
ENABLE_FEAT_S1POE	:=	2

# 9.3
ENABLE_FEAT_GCS		:=	2

>>>>>>> upstream_import/upstream_v2_14_1
# SPM_MM is not compatible with ENABLE_SVE_FOR_NS (build breaks)
ifeq (${SPM_MM},1)
	ENABLE_SVE_FOR_NS	:= 0
	ENABLE_SME_FOR_NS	:= 0
else
	ENABLE_SVE_FOR_NS	:= 2
	ENABLE_SME_FOR_NS	:= 2
endif

<<<<<<< HEAD
# QEMU will use the RNDR instruction for the stack protector canary.
ENABLE_FEAT_RNG			:= 2

# QEMU 7.2+ has support for FGT and Linux needs it enabled to boot on max
ENABLE_FEAT_FGT			:= 2
=======
ifeq (${ENABLE_RME},1)
BL31_SOURCES			+= plat/qemu/common/qemu_plat_attest_token.c \
				   plat/qemu/common/qemu_realm_attest_key.c
endif
>>>>>>> upstream_import/upstream_v2_14_1

# Treating this as a memory-constrained port for now
USE_COHERENT_MEM	:=	0

# This can be overridden depending on CPU(s) used in the QEMU image
HW_ASSISTED_COHERENCY	:=	1

CTX_INCLUDE_AARCH32_REGS := 0
ifeq (${CTX_INCLUDE_AARCH32_REGS}, 1)
$(error "This is an AArch64-only port; CTX_INCLUDE_AARCH32_REGS must be disabled")
endif

# Pointer Authentication sources
<<<<<<< HEAD
ifeq (${ENABLE_PAUTH}, 1)
PLAT_BL_COMMON_SOURCES	+=	plat/arm/common/aarch64/arm_pauth.c
CTX_INCLUDE_PAUTH_REGS	:=	1
=======
ifeq ($(BRANCH_PROTECTION),$(filter $(BRANCH_PROTECTION),1 2 3 5))
PLAT_BL_COMMON_SOURCES	+=	plat/arm/common/aarch64/arm_pauth.c
endif

ifeq (${TRANSFER_LIST}, 1)
include lib/transfer_list/transfer_list.mk
endif

ifeq (${HOB_LIST}, 1)
include lib/hob/hob.mk
>>>>>>> upstream_import/upstream_v2_14_1
endif

endif
