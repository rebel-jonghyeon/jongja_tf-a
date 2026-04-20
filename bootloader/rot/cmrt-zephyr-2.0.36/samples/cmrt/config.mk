
ifndef BOARD
$(error BOARD is not set)
endif

BOARD_NAME := $(word 2, $(subst _, ,$(BOARD)))

# execute `VERBOSE=1 make ...` to get (very) VERBOSE build messages
VERBOSE ?=

# attempt to include from the same dir where this "config.mk" is located
-include $(dir $(lastword $(MAKEFILE_LIST)))$(BOARD).mk

ifndef SOURCE_DATE_EPOCH
$(info SOURCE_DATE_EPOCH unset (or ''). Resolving current dates...)
SOURCE_COMMIT := $(shell git rev-parse --short=7 HEAD)
SOURCE_DATE := $(shell date -u +'%Y-%m-%d')
endif

# SOURCE_COMMIT may still be empty...
ifndef SOURCE_COMMIT
SOURCE_COMMIT := 0000000
endif

# ...ditto, for SOURCE_DATE
ifndef SOURCE_DATE
SOURCE_DATE := $(shell date -u +'%Y-%m-%d' --date @$(SOURCE_DATE_EPOCH))
endif

ifdef RELEASE_BUILD
  VERSION_INFO := $(SOURCE_DATE)-g$(SOURCE_COMMIT)
  ifeq ($(RELEASE_BUILD),BEFORE_BOOT)
    # Do not disable BEFORE_BOOT configs
    BUILD_CONFIG := -DCONFIG_DEBUG=n -DCONFIG_LOG=n -DCONFIG_CONSOLE=n -DCONFIG_RAM_CONSOLE=n -DCONFIG_PRINTK=n -DCONFIG_RELEASE=y -DCONFIG_THREAD_MONITOR=n
  else
    # Normally disable also BEFORE_BOOT configs
    BUILD_CONFIG := -DCONFIG_WAIT_BEFORE_BOOT=n -DCONFIG_JTAG_BEFORE_BOOT=n -DCONFIG_DEBUG=n -DCONFIG_LOG=n -DCONFIG_CONSOLE=n -DCONFIG_RAM_CONSOLE=n -DCONFIG_PRINTK=n -DCONFIG_RELEASE=y -DCONFIG_THREAD_MONITOR=n
  endif
  BUILDDIR ?= build
else
  VERSION_INFO := $(SOURCE_DATE)-g$(SOURCE_COMMIT)-$(BOARD_NAME)-debug
  BUILD_CONFIG :=
  BUILDDIR ?= build-dbg
endif

export BUILDDIR
ZEPHYR_BASE_BUILDDIR ?= $(ZEPHYR_BASE)/$(BUILDDIR)


#$(foreach v, $(.VARIABLES), $(info $(origin $v) $(flavor $v) $v = $($v)))

.SUFFIXES:
