#
<<<<<<< HEAD
# Copyright (c) 2023, Arm Limited and Contributors. All rights reserved.
=======
# Copyright (c) 2023-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
#
# SPDX-License-Identifier: BSD-3-Clause
#

ifeq (${TRANSFER_LIST},1)

<<<<<<< HEAD
ifeq (${ARCH},aarch32)
$(eval $(call add_define,TRANSFER_LIST_AARCH32))
endif

TRANSFER_LIST_SOURCES	+=	$(addprefix lib/transfer_list/,	\
				transfer_list.c)

BL31_SOURCES	+=	$(TRANSFER_LIST_SOURCES)
BL2_SOURCES	+=	$(TRANSFER_LIST_SOURCES)

endif	# TRANSFER_LIST

=======
# Default path if not set externally
LIBTL_PATH	?=	contrib/libtl

# Common include paths (always needed)
INCLUDES	+=	-I$(LIBTL_PATH)/include \
			-I$(LIBTL_PATH)/include/arm

LIBTL_SRC_PATH	:=	$(LIBTL_PATH)/src

LIBTL_SRCS	:=	$(addprefix $(LIBTL_SRC_PATH)/, \
				arm/ep_info.c \
				generic/logging.c \
				generic/transfer_list.c)

ifeq ($(MEASURED_BOOT), 1)
LIBTL_SRCS	+=	$(LIBTL_SRC_PATH)/generic/tpm_event_log.c
endif

$(eval $(call MAKE_LIB,tl))

endif	# TRANSFER_LIST
>>>>>>> upstream_import/upstream_v2_14_1
