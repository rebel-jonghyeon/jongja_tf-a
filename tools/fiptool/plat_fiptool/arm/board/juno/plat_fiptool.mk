#
<<<<<<< HEAD
# Copyright (c) 2023, Arm Limited. All rights reserved.
=======
# Copyright (c) 2023-2025, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
#
# SPDX-License-Identifier: BSD-3-Clause
#

PLAT_DEF_UUID := yes

ifeq (${PLAT_DEF_UUID}, yes)
<<<<<<< HEAD
HOSTCCFLAGS += -DPLAT_DEF_FIP_UUID
ifeq (${ETHOSN_NPU_TZMP1},1)
HOSTCCFLAGS += -DETHOSN_NPU_TZMP1
endif
INCLUDE_PATHS += -I./ -I${PLAT_DIR}fip -I../../include/
OBJECTS += ${PLAT_DIR}fip/plat_def_uuid_config.o
=======
FIPTOOL_DEFINES += PLAT_DEF_FIP_UUID
ifeq (${ETHOSN_NPU_TZMP1},1)
FIPTOOL_DEFINES += ETHOSN_NPU_TZMP1
endif
FIPTOOL_INCLUDE_DIRS += ./ ../../plat/arm/board/juno/fip ../../include
FIPTOOL_SOURCES += plat_fiptool/arm/board/juno/plat_def_uuid_config.c
>>>>>>> upstream_import/upstream_v2_14_1
endif
