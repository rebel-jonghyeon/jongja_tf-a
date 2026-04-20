
USDIR = $(ZEPHYR_BASE)/samples/cmrt/userspace
ifneq (clean, $(MAKECMDGOALS))
-include $(dir $(lastword $(MAKEFILE_LIST)))encrypt.mk
include $(ZEPHYR_BASE)/samples/cmrt/$(BOARD).mk
endif

DEBUGFLAGS = -g

CROSS_COMPILE = $(RISCV32_TOOLCHAIN_PATH)/bin/riscv32-unknown-elf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump


SKVAR := $(CURDIR:$(ZEPHYR_BASE)/samples/cmrt/%=%)
ifdef SIGN_KEY_$(SKVAR)
SIGN_KEY := $(SIGN_KEY_$(SKVAR))
else
SIGN_KEY ?= $(ZEPHYR_BASE)/samples/cmrt/common/prikey_ecdsa_p256.pem
endif
signkey := $(SIGN_KEY)
user_footer ?=
user_stack ?= 0
user_heap ?= 0

OS_BUILDDIR ?= build

INCLUDES = \
	-I$(USDIR)/include \
	-I$(USDIR)/include/portability \
	-I$(USDIR)/include/drivers/cmrt \
	-I$(USDIR)/include/drivers/cmrt/teefs \
	-I$(USDIR)/lib/libucu/include \
	-I$(USDIR)/lib/libshsig/include \
	-I$(USDIR)/lib/caliptra/include \
	-include $(USDIR)/include/autoconf.h \
	$(user_includes)

LDFLAGS = \
	$(ARCHFLAGS) \
	-static \
	-pie \
	-nostdlib -Wl,-zstack-size=0 -Wl,-q -Wl,--gc-sections $(user_ldflags) \
	-Wl,--defsym=HEAP_SIZE=$(user_heap) \
	-Wl,--orphan-handling=warn \
	-L $(USDIR)/lib/os -L $(USDIR)/lib/libc -L $(USDIR)/lib/teefs \
	-L $(USDIR)/lib/cmrt_v1 \
	-L $(USDIR)/lib/libucu \
	-L $(USDIR)/lib/libshsig \
	-L $(USDIR)/lib/caliptra \

ifneq ($(user_heap),0)
LDFLAGS += -Wl,-u,user_heap_init
endif

linker_script := $(USDIR)/common/container.ld

WARNINGS = -Wall -Wextra -Wmissing-prototypes -Wvla -Wno-error=main -Werror

DEFINES = -DCONFIG_RISCV32 -DCONFIG_COOP_ENABLED -DCONFIG_CMRT_V1
DEFINES += -DUSER_CONTAINER $(user_defines)

gcc_inc := $(dir $(shell $(CC) -print-file-name=include/stddef.h))

CFLAGS = \
	-fpie -Og -std=c11 $(ARCHFLAGS) \
	$(DEBUGFLAGS) $(WARNINGS) -fdata-sections -ffunction-sections \
	-ffreestanding \
	$(DEFINES) $(user_cflags) \
	-nostdinc \
	-isystem $(gcc_inc) \
	-isystem $(USDIR)/lib/libc/include \
	-DCONFIG_RISCV -DCONFIG_ASSERT -DCONFIG_ASSERT_LEVEL=2 \
	-DCONFIG_ASSERT_VERBOSE -DCONFIG_ASSERT_NO_FILE_INFO \
	-D__syscall='static inline'

ARCHFLAGS = -mabi=ilp32 -march=rv32imc
ASFLAGS = $(ARCHFLAGS)

all:

C_OBJS = $(user_objs)
ifdef root_json
ROOT_C = $(subst .json,.c,$(root_json))
C_OBJS += $(subst .json,.o,$(root_json))
ifndef pubkey
$(error pubkey must be defined if root_json is specified)
endif
$(ROOT_C): $(root_json) $(pubkey)
	cmrt-image-footer.py --create-root $(pubkey) $(root_json)
else
ROOT_C =
endif

ifdef VERBOSE
#print the full command line (ign. 2nd arg of quiet if any)
quiet = $($(word 1, $(1)))
verbose_opt = --verbose
else
#print partial command line (print 2nd arg or $@ if no 2nd)
quiet = $(info $(1) $(or $(2),$@)) @$($(word 1, $(1)))
verbose_opt =
endif

%.o: %.c
	$(call quiet,CC) $(CFLAGS) $(INCLUDES) -MP -MD -c -o $@ $<

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

$(C_OBJS): $(MAKEFILE_LIST)

DEPS = $(C_OBJS:%.o=%.d)
-include $(DEPS)

all: $(user_name)

ifeq (.a,$(suffix $(user_name))) # building a static lib

$(user_name): $(C_OBJS)
	$(AR) crD $(user_name) $(C_OBJS)

else # building container image(s)

$(user_name): $(user_name).wip
	ln -f $< $@

all: $(user_name).img
all: $(user_name).img2

endif

all: $(user_name)

-include $(user_name).elf.d

$(user_name).elf: $(C_OBJS) $(MAKEFILE_LIST) $(linker_script)
	$(call quiet,LD) $(LDFLAGS) -T $(linker_script) \
		-Wl,--dependency-file=$@.d \
		$(C_OBJS) \
		-o $@ $(user_libs) -Wl,--start-group -los -lc -lgcc -Wl,--end-group

.PRECIOUS: %.wip %.raw %.tmp %.img %.tmp2 %.enc

%.wip: %.elf
	$(OBJCOPY) -O binary $< $@

%.raw: %.wip $(MAKEFILE_LIST)
	cmrt-raw-footer.py $(verbose_opt) $*.elf $< $@ true $(user_stack)

%.tmp: %.raw $(signkey) $(user_footer)
	cmrt-image-footer.py $(signkey) $< $(or $(user_footer),-) $@

%.img: %.tmp
	cmrt-image-header.py $< $@


# Encrypted image

%.enc %.raw2: %.raw
	cmrt-image-encrypt.py $(verbose_opt) \
		$(ENCRYPT_KEY) $(ENCRYPT_KEYID) $(ENCRYPT_DIVERSIFY) \
		$< $*.raw2 $*.enc

%.tmp2: %.enc %.raw2 $(signkey) $(user_footer)
	cmrt-image-footer.py $(signkey) $*.raw2 $(or $(user_footer),-) $*.tmp2 $*.enc

%.img2: %.tmp2
	cmrt-image-header.py $< $@

.PHONY: clean
clean:
	rm -f $(C_OBJS) $(DEPS) $(user_name).elf.d \
		$(user_name) $(user_name).str $(user_name).elf \
		$(user_name).img $(user_name).raw $(user_name).wip \
		$(user_name).lst $(user_name).tmp $(user_name).raw2 \
		$(user_name).tmp2 $(user_name).enc $(user_name).img2 $(ROOT_C)

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules # --warn-undefined-variables
