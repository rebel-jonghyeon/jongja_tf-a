#
<<<<<<< HEAD
# Copyright (c) 2019-2021, Arm Limited. All rights reserved.
=======
# Copyright (c) 2019-2024, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
#
# SPDX-License-Identifier: BSD-3-Clause
#

include common/fdt_wrappers.mk

FCONF_SOURCES		:=	lib/fconf/fconf.c
FCONF_SOURCES		+=	${FDT_WRAPPERS_SOURCES}

FCONF_DYN_SOURCES	:=	lib/fconf/fconf_dyn_cfg_getter.c
FCONF_DYN_SOURCES	+=	${FDT_WRAPPERS_SOURCES}
