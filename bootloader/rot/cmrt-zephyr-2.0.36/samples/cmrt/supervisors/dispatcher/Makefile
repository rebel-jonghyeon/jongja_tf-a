# Build supervisor binary using Zephyr makefiles for config generation and
# building the object files.

.ONESHELL: # gnu make >= 3.82 feature
SHELL = /bin/sh
.SHELLFLAGS = -xeuc

include ../../config.mk

ifeq (,$(filter clean pristine, $(lastword $(MAKECMDGOALS))))
include ../../fboot/$(BUILDDIR)/config.mk
include ../../fboot/$(BUILDDIR)/board.mk
include ../../common/tboot.mk
endif
ifeq ($(ENCRYPTED_IMAGE),y)
include ../../common/encrypt.mk
endif

ZEPHYR_ELF = $(CURDIR)/$(BUILDDIR)/zephyr/zephyr.elf

TARGET = dispatcher

SRCS = src/*.[ch] # used for dependency resolvation (to be a bit more accurate)

SIGN_KEY ?= $(ZEPHYR_BASE)/samples/cmrt/common/prikey_ecdsa_p256.pem

.PHONY: all
all: rest

.PHONY: config
config: $(BUILDDIR)/Makefile

$(BUILDDIR)/Makefile: CMakeLists.txt Makefile $(SRCS)
	@mkdir -p $(BUILDDIR)
	cd $(BUILDDIR)
	pwd
	cmake $(BUILD_CONFIG) -DSUPERVISOR_VERSION_INFO='$(VERSION_INFO)' -DCONFIG_PIX_OFFSET=$(TBOOT_OFFSET) ..
	cmrt-config-tool.py with_tboot=$(INSTALL_TBOOT) sv_name=$(TARGET) \
		$(ZEPHYR_BASE_BUILDDIR)/$(BOARD)-$(TARGET).json \
		config.asciidoctor \
		autoconf.h
ifeq ($(notdir $(CURDIR)), $(notdir $(OS_DIR)))
	ln -sf $(BOARD)-$(TARGET).json $(ZEPHYR_BASE_BUILDDIR)/board.json
	cp config.asciidoctor $(ZEPHYR_BASE_BUILDDIR)/config.asciidoctor
endif

$(ZEPHYR_ELF): $(BUILDDIR)/Makefile
	@cd $(BUILDDIR)
	pwd
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
	: : Generate image metadata : :
	cmrt-cfi-metadata.py $(TARGET).elf $(TARGET).cfi
endif
	cmrt-raw-footer.py $(TARGET).elf $(TARGET).raw.tmp $(TARGET).raw
ifeq ($(ENCRYPTED_IMAGE),y)
	cmrt-image-encrypt.py $(ENCRYPT_KEY) $(ENCRYPT_KEYID) $(ENCRYPT_DIVERSIFY) $(TARGET).raw $(TARGET).raw2 $(TARGET).enc
	cmrt-image-footer.py $(SIGN_KEY) $(TARGET).raw2 ../footer.json $(TARGET).tmp2 $(TARGET).enc
endif
ifeq ($(SUPERVISOR_IN_ROM),y)
	: : ROM image is just hashed, not signed : :
	cmrt-image-footer.py $(TARGET).raw ../footer.json $(TARGET).rom.img
	mv $(TARGET).rom.img $(TARGET).tmp
else
	: : Normal image is signed : :
	cmrt-image-footer.py $(SIGN_KEY) $(TARGET).raw ../footer.json $(TARGET).tmp
endif
	cmrt-image-header.py $(TARGET).tmp $(TARGET).img
	: : write os image bundle, possible tboot first : :
	cat $(FHDR_IMG) $(TBOOT_IMG) $(TARGET).img >os.img
ifeq ($(ENCRYPTED_IMAGE),y)
	: : additional encrypted image bundle : :
	cmrt-image-header.py $(TARGET).tmp2 $(TARGET).img2
	: : write os image bundle, possible tboot first : :
	cat $(FHDR_IMG) $(TBOOT_IMG) $(TARGET).img2 >os.img2
endif
ifeq ($(SUPERVISOR_IN_ROM),y)
ifeq ($(SBOOT_IN_ROM),y)
	cmrt-memory-image.py --of $(ZEPHYR_BASE_BUILDDIR)/rommem.bin \
		--size $(EXT_ROM_SIZE) --if os.img --seek $(MACHINE_ROM_SIZE)
else
	cmrt-memory-image.py --of $(ZEPHYR_BASE_BUILDDIR)/rommem.bin \
		--size $(EXT_ROM_SIZE) --if os.img
endif
endif
	ls -lrtac $$PWD

.PHONY: clean
clean:
	@-rm -f $(BUILDDIR)/$(TARGET)* $(OBJS) *~ $(BUILDDIR)/os.img
	rm -f $(ZEPHYR_BASE_BUILDDIR)/$(BOARD)-$(TARGET).json
	$(MAKE) -C $(BUILDDIR) clean

.PHONY: pristine
pristine:
	@-rm -f $(ZEPHYR_BASE_BUILDDIR)/$(BOARD)-$(TARGET).json
	rm -rf $(BUILDDIR) *~

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
