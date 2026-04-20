#
# Copyright (C) 2025 Samsung Electronics
#
# SPDX-License-Identifier: BSD-3-Clause
#

REBEL_PLAT		:=	plat/rebel
REBEL_PLAT_SOC		:=	${REBEL_PLAT}/${PLAT}
REBEL_PLAT_COMMON	:=	${REBEL_PLAT}/common

# Translation tables library
include lib/xlat_tables_v2/xlat_tables.mk

PLAT_BL_COMMON_SOURCES	+=	${XLAT_TABLES_LIB_SRCS} \
				plat/common/plat_psci_common.c

BL31_SOURCES		+=	${REBEL_PLAT_COMMON}/rebel_sip_svc.c

INCLUDES		+=	-Iinclude/bl31 \
				-Iinclude/lib \
				-Iinclude/lib/psci \
				-Iinclude/lib/xlat_tables \
				-Iinclude/plat/common \
				-Iinclude/drivers \
				-Iinclude/drivers/arm \
				-Iinclude/tools_share
