# Build sboot binary using Zephyr makefiles for config generation and
# building the object files. Linking is done against fboot zephyr.elf

.ONESHELL: # gnu make >= 3.82 feature
SHELL = /bin/sh
.SHELLFLAGS = -xeuc

.NOTPARALLEL:

include ../config.mk

ifeq (,$(filter clean pristine, $(lastword $(MAKECMDGOALS))))
include ../fboot/$(BUILDDIR)/config.mk
include ../fboot/$(BUILDDIR)/board.mk
include $(BUILDDIR)/zephyr/.config
endif

-include src/$(BOARD)/board.mk

LDFLAGS = -nostdlib --no-relax --gc-sections
LDFLAGS += -n -e main -Ttext $(SBOOT_START) -T$(ZEPHYR_BASE)/samples/cmrt/common/linker.ld

TARGET = sboot

# Sboot is currently built first as a Zephyr application, and then
# certain object files and libraries are re-linked from the resulting
# build tree into the real sboot ELF. The paths below therefore are
# dependent on the Zephyr buildsystem.
OBJS ?= CMakeFiles/app.dir/src/main.c.obj
ifdef CONFIG_CMRT_CALIPTRA_SUPPORT
OBJS += CMakeFiles/app.dir/src/caliptra.c.obj
OBJS += zephyr/lib/caliptra/libcaliptra.a
OBJS += zephyr/lib/libucu/liblib__libucu.a
endif
OBJS += CMakeFiles/app.dir/src/emergency.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/dma/dma.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/cmu/cmu.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/spi/dwc_ssi.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/timer/timer.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/uart/uart.c.obj
OBJS += CMakeFiles/app.dir/src/drivers/sac/sac_custom.c.obj
OBJS += zephyr/lib/integrity/librebel_h_integrity.a
OBJS += $(FBOOT_DIR)/libfboot-machine-api.a
OBJS += zephyr/lib/gpt/librebel_h_gpt.a

.PHONY: all
all: rest

$(BUILDDIR)/zephyr/.config: $(BUILDDIR)/Makefile
	@: done as side effect

$(BUILDDIR)/Makefile:
	@mkdir -p $(BUILDDIR)
	cd $(BUILDDIR)
	pwd
	cmake $(BUILD_CONFIG) -DSBOOT_VERSION_INFO='$(VERSION_INFO)' ..

.PHONY: $(BUILDDIR)/zephyr/zephyr.elf
$(BUILDDIR)/zephyr/zephyr.elf: $(BUILDDIR)/Makefile
	cd $(BUILDDIR)
	pwd
	$(MAKE) '$(VERBOSE)MAKELEVEL=0'
	ls -lrtac $$PWD

$(BUILDDIR)/$(TARGET).elf: $(BUILDDIR)/zephyr/zephyr.elf
	@cd $(BUILDDIR)
	pwd
	riscv32-unknown-elf-ld $(LDFLAGS) -o $(@F).wip $(OBJS)
	riscv32-unknown-elf-objdump -D $(@F).wip > $(TARGET).lst
	mv $(@F).wip $(@F)

$(BUILDDIR)/$(TARGET).img: $(BUILDDIR)/$(TARGET).elf
	@cd $(BUILDDIR)
	pwd
	riscv32-unknown-elf-objcopy -O binary -S -R pkeram -R .comment -R otp $(<F) $(TARGET).raw.tmp
	cmrt-raw-nobits.py $(<F) >> $(TARGET).raw.tmp
ifeq ($(CFI_ENABLED),y)
	: : Generate image metadata for sboot : :
	cmrt-cfi-metadata.py $(TARGET).elf $(TARGET).cfi
endif
	cmrt-raw-footer.py --verbose $(TARGET).elf $(TARGET).raw.tmp $(TARGET).raw
	cmrt-sboot-footer.py $(TARGET).raw >> $(TARGET).raw
	cmrt-image-header.py $(TARGET).raw $(TARGET).img
	gen_otp_img.py $(TARGET).img
	ls -lrtac $$PWD


.PHONY: rest
rest: $(BUILDDIR)/$(TARGET).img
	@cd $(BUILDDIR)
	pwd
	test -d $(ZEPHYR_BASE_BUILDDIR) || mkdir -p $(ZEPHYR_BASE_BUILDDIR)
	../otp-lead.py $(OTP_LAYOUT_VERSION) $(KEYSPLITS_NUM) $(ZEPHYR_BASE_BUILDDIR)/otp-lead
ifeq ($(SBOOT_IN_ROM),y)
	cmrt-memory-image.py --of $(ZEPHYR_BASE_BUILDDIR)/rommem.bin \
		--size $(EXT_ROM_SIZE) --if $(TARGET).img
endif
ifdef OTPE_KEY
	truncate -s $$(($(OTP_SIZE) - 32)) $(ZEPHYR_BASE_BUILDDIR)/otpmem.bin
	cmrt-oec-encrypt.py -o $(ZEPHYR_BASE_BUILDDIR)/oecmem.bin '$(OTPE_KEY)' \
		$(ZEPHYR_BASE_BUILDDIR)/otpmem.bin
endif
	ls -lrtac $$PWD $(ZEPHYR_BASE_BUILDDIR)

BIN_FILES = $(ZEPHYR_BASE_BUILDDIR)/otp-lead
ifdef OTPE_KEY
BIN_FILES += $(ZEPHYR_BASE_BUILDDIR)/otpmem.bin
BIN_FILES += $(ZEPHYR_BASE_BUILDDIR)/oecmem.bin
endif

ifeq ($(SBOOT_IN_ROM),y)
BIN_FILES += $(ZEPHYR_BASE_BUILDDIR)/rommem.bin
endif


.PHONY: clean
clean:
	@-rm -f $(BUILDDIR)/$(TARGET)* $(OBJS) *~
	$(MAKE) -C $(BUILDDIR) clean


.PHONY: pristine
pristine:
	@-rm -rf $(BUILDDIR) $(BIN_FILES)

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
