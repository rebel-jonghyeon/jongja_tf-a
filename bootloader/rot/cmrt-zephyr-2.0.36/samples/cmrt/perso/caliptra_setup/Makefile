# Build perso binary using Zephyr makefiles for config generation and
# building the object files. Persos are independent binaries.

.ONESHELL: # gnu make >= 3.82 feature
SHELL = /bin/sh
.SHELLFLAGS = -xeuc

include ../../config.mk

ifeq (,$(filter clean pristine, $(lastword $(MAKECMDGOALS))))
include ../../fboot/$(BUILDDIR)/config.mk
include ../../fboot/$(BUILDDIR)/board.mk
endif

ZEPHYR_ELF = $(CURDIR)/$(BUILDDIR)/zephyr/zephyr.elf

TARGET = caliptra_setup

SRCS = src/main.c

SBOOT_IMG = $(ZEPHYR_BASE)/samples/cmrt/sboot/$(BUILDDIR)/sboot.img

SIGN_KEY ?= $(ZEPHYR_BASE)/samples/cmrt/common/prikey_perso_p256.pem

.PHONY: all
all: rest

$(ZEPHYR_ELF): $(SRCS)
	@mkdir -p $(BUILDDIR)
	cd $(BUILDDIR)
	pwd
ifneq ($(CONFIG_CMRT_SBOOT_IN_ROM),y)
	cat $(SBOOT_IMG) > sboot_img
	xxd -i sboot_img | sed '1s/char/alignas(4) char/' > sboot_img.h
endif
	cmake $(FBOOT_XKFLAGS) -DBUILDDIR=$(BUILDDIR) -DPERSO_VERSION_INFO='$(VERSION_INFO)' ..
	cp $(ZEPHYR_BASE)/samples/cmrt/common/pkhash*.inc zephyr/include/generated/
	$(MAKE) '$(VERBOSE)MAKELEVEL=0'
	ls -lrtac $$PWD

$(BUILDDIR)/$(TARGET).elf: $(ZEPHYR_ELF)
	@cd $(BUILDDIR)
	pwd
	riscv32-unknown-elf-objdump -D $(ZEPHYR_ELF) > $(TARGET).lst
	ln -f $(ZEPHYR_ELF) $(@F)

.PHONY: rest
rest: $(BUILDDIR)/$(TARGET).elf
	@cd $(BUILDDIR)
	pwd
	riscv32-unknown-elf-objcopy -O binary -S -R pkeram -R .comment -R vector -R rom_start -R otp $(<F) $(TARGET).raw.tmp
ifeq ($(CFI_ENABLED),y)
	cmrt-cfi-metadata.py $(TARGET).elf $(TARGET).cfi
endif
	cmrt-raw-footer.py $(TARGET).elf $(TARGET).raw.tmp $(TARGET).raw
	cmrt-image-footer.py $(SIGN_KEY) $(TARGET).raw ../footer.json $(TARGET).img
	ls -lrtac $$PWD

.PHONY: clean
clean:
	@-rm -f $(BUILDDIR)/$(TARGET)* $(BUILDDIR)/sboot_img* $(OBJS) *~
	$(MAKE) -C $(BUILDDIR) clean

.PHONY: pristine
pristine:
	@-rm -rf $(BUILDDIR) *~

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
