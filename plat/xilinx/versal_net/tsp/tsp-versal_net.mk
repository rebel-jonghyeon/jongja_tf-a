#
# Copyright (c) 2023, Advanced Micro Devices, Inc. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

# TSP source files specific to Versal NET platform

PLAT_XILINX_COMMON := plat/xilinx/common/
<<<<<<< HEAD

include ${PLAT_XILINX_COMMON}/tsp/tsp.mk

BL32_SOURCES		+=	plat/xilinx/versal_net/plat_topology.c		\
				${XLAT_TABLES_LIB_SRCS}
=======
BL32_SOURCES	   += ${GIC_SOURCES}

include ${PLAT_XILINX_COMMON}/tsp/tsp.mk
>>>>>>> upstream_import/upstream_v2_14_1
