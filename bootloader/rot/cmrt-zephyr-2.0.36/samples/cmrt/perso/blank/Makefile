# Build perso binary using Zephyr makefiles for config generation and
# building the object files. Linking is done against fboot zephyr.elf

.ONESHELL: # gnu make >= 3.82 feature
SHELL = /bin/sh
.SHELLFLAGS = -xeuc

include ../../config.mk

ifeq (,$(filter clean pristine, $(lastword $(MAKECMDGOALS))))
include ../../fboot/$(BUILDDIR)/config.mk
include ../../fboot/$(BUILDDIR)/board.mk
endif

START = $(FBOOT_IMAGE_END)

LDFLAGS = -nostdlib --no-relax
LDFLAGS += -n -e main -Ttext $(START) -T$(ZEPHYR_BASE)/samples/cmrt/common/linker.ld

TARGET = blank

OBJS = CMakeFiles/app.dir/src/main.c.obj
OBJS += zephyr/drivers/cmrt/CMakeFiles/drivers__cmrt.dir/util.c.obj
OBJS += $(FBOOT_DIR)/libfboot-machine-api.a

SRCS = src/main.c

PNAK_KEY ?= $(ZEPHYR_BASE)/samples/cmrt/common/pnak.hmac

.PHONY: all
all: rest

$(BUILDDIR)/$(TARGET).elf: $(SRCS)
	@mkdir -p $(BUILDDIR)
	cd $(BUILDDIR)
	pwd
	cmake $(BUILD_CONFIG) -DPERSO_VERSION_INFO='$(VERSION_INFO)' ..
	cp $(ZEPHYR_BASE)/samples/cmrt/common/pkhash*.inc zephyr/include/generated/
	$(MAKE) '$(VERBOSE)MAKELEVEL=0'
	pwd
	riscv32-unknown-elf-ld $(LDFLAGS) -o $(@F).wip $(OBJS)
	riscv32-unknown-elf-objdump -D $(@F).wip > $(TARGET).lst
	mv $(@F).wip $(@F)

.PHONY: rest
rest: $(BUILDDIR)/$(TARGET).elf
	@cd $(BUILDDIR)
	pwd
	riscv32-unknown-elf-objcopy -O binary -S -R pkeram -R .comment -R otp $(<F) $(TARGET).raw.tmp
ifeq ($(CFI_ENABLED),y)
	: : Generate image metadata : :
	cmrt-cfi-metadata.py $(TARGET).elf $(TARGET).cfi
endif
	: : Attach elf section info to tail of raw image : :
	cmrt-raw-footer.py $(TARGET).elf $(TARGET).raw.tmp $(TARGET).raw
	: : Sign perso with pnak based hmac key : :
	cmrt-image-footer.py $(PNAK_KEY) $(TARGET).raw - $(TARGET).img
	ls -lrtac $$PWD

.PHONY: clean
clean:
	@-rm -f $(BUILDDIR)/$(TARGET)* $(OBJS) *~
	rm -f $(BUILDDIR)/zephyr/include/generated/*.inc $(BUILDDIR)/fboot.elf
	$(MAKE) -C $(BUILDDIR) clean

.PHONY: pristine
pristine:
	@-rm -rf $(BUILDDIR) *~

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
