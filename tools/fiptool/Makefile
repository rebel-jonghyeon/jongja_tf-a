#
# Copyright (c) 2014-2025, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

MAKE_HELPERS_DIRECTORY := ../../make_helpers/
include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}build-rules.mk
include ${MAKE_HELPERS_DIRECTORY}common.mk
include ${MAKE_HELPERS_DIRECTORY}defaults.mk
include ${MAKE_HELPERS_DIRECTORY}toolchain.mk

<<<<<<< HEAD
FIPTOOL ?= fiptool${BIN_EXT}
PROJECT := $(notdir ${FIPTOOL})
OBJECTS := fiptool.o tbbr_config.o
V ?= 0
STATIC ?= 0

override CPPFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=700
HOSTCCFLAGS := -Wall -Werror -pedantic -std=c99
=======
FIPTOOL_SOURCES := fiptool.c tbbr_config.c
STATIC ?= 0

FIPTOOL_DEFINES += _GNU_SOURCE _XOPEN_SOURCE=700
FIPTOOL_CFLAGS := -Wall -Werror -pedantic -std=c99
>>>>>>> upstream_import/upstream_v2_14_1
ifeq (${DEBUG},1)
  FIPTOOL_CFLAGS += -g -O0 -DDEBUG
else
  FIPTOOL_CFLAGS += -O2
endif

<<<<<<< HEAD
INCLUDE_PATHS := -I../../include/tools_share

DEFINES += -DSTATIC=$(STATIC)

ifeq (${STATIC},1)
LDOPTS := -static
=======
FIPTOOL_INCLUDE_DIRS := ../../include/tools_share

FIPTOOL_DEFINES += STATIC=$(STATIC)

ifeq (${STATIC},1)
FIPTOOL_LDFLAGS := -static
>>>>>>> upstream_import/upstream_v2_14_1
else
OPENSSL_DIR := /usr

# Select OpenSSL version flag according to the OpenSSL build selected
# from setting the OPENSSL_DIR path.
$(eval $(call SELECT_OPENSSL_API_VERSION))

# USING_OPENSSL3 flag will be added to the HOSTCCFLAGS variable with the proper
# computed value.
<<<<<<< HEAD
DEFINES += -DUSING_OPENSSL3=$(USING_OPENSSL3)
=======
FIPTOOL_DEFINES += USING_OPENSSL3=$(USING_OPENSSL3)
>>>>>>> upstream_import/upstream_v2_14_1

# Include library directories where OpenSSL library files are located.
# For a normal installation (i.e.: when ${OPENSSL_DIR} = /usr or
# /usr/local), binaries are located under the ${OPENSSL_DIR}/lib/
# directory. However, for a local build of OpenSSL, the built binaries are
# located under the main project directory (i.e.: ${OPENSSL_DIR}, not
# ${OPENSSL_DIR}/lib/).
<<<<<<< HEAD
LDOPTS := -L${OPENSSL_DIR}/lib -L${OPENSSL_DIR} -lcrypto
INCLUDE_PATHS += -I${OPENSSL_DIR}/include
endif # STATIC

HOSTCCFLAGS += ${DEFINES}

ifeq (${V},0)
  Q := @
else
  Q :=
endif

HOSTCC ?= gcc
=======
FIPTOOL_LDFLAGS := -L${OPENSSL_DIR}/lib -L${OPENSSL_DIR} -lcrypto
FIPTOOL_INCLUDE_DIRS += ${OPENSSL_DIR}/include
endif # STATIC
>>>>>>> upstream_import/upstream_v2_14_1

ifneq (${PLAT},)
TF_PLATFORM_ROOT	:=	../../plat/
include ${MAKE_HELPERS_DIRECTORY}plat_helpers.mk
COMBINED_PATH_FRAG := plat_fiptool/
PLAT_FIPTOOL_HELPER_MK := $(foreach path_frag,$(subst /, ,$(patsubst ../../plat/%/,%,${PLAT_DIR})),\
			  $(eval COMBINED_PATH_FRAG := ${COMBINED_PATH_FRAG}/${path_frag})\
			  $(wildcard ${COMBINED_PATH_FRAG}/plat_fiptool.mk))
endif

ifneq (,$(wildcard $(lastword ${PLAT_FIPTOOL_HELPER_MK})))
include ${PLAT_FIPTOOL_HELPER_MK}
endif

$(eval $(call MAKE_TOOL,$(BUILD_PLAT)/tools,fiptool,FIPTOOL))

.PHONY: all clean distclean --openssl

<<<<<<< HEAD
all: --openssl ${PROJECT}

${PROJECT}: ${OBJECTS} Makefile
	@echo "  HOSTLD  $@"
	${Q}${HOSTCC} ${OBJECTS} -o $@ $(LDOPTS)
	@${ECHO_BLANK_LINE}
	@echo "Built $@ successfully"
	@${ECHO_BLANK_LINE}

%.o: %.c Makefile
	@echo "  HOSTCC  $<"
	${Q}${HOSTCC} -c ${CPPFLAGS} ${HOSTCCFLAGS} ${INCLUDE_PATHS} -MD -MP $< -o $@

-include $(DEPS)
=======
all: --openssl
>>>>>>> upstream_import/upstream_v2_14_1

--openssl:
ifeq ($(STATIC),0)
ifeq ($(DEBUG),1)
	$(s)echo "Selected OpenSSL version: ${OPENSSL_CURRENT_VER}"
endif
endif # STATIC

clean:
	$(q)rm -rf $(BUILD_PLAT)/tools/fiptool
