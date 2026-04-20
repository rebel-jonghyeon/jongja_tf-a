user_footer = footer.json
user_name = caliptra_rt
user_libs = -lcaliptra
user_objs = caliptra_rt.o
user_cflags =
user_ldflags =
user_stack = 10240
user_defines += -DSBOOT_IMG_LEN=$(SBOOT_IMG_LEN)

ifdef RELEASE_BUILD
BUILDDIR ?= build
else
BUILDDIR ?= build-dbg
endif
export BUILDDIR

include ../../common/container.mk

ifeq (,$(filter clean pristine, $(lastword $(MAKECMDGOALS))))
include $(ZEPHYR_BASE)/samples/cmrt/fboot/$(BUILDDIR)/zephyr/.config
include $(ZEPHYR_BASE)/samples/cmrt/fboot/$(BUILDDIR)/board.mk
endif

# make-footer.sh uses the following environment variables:

export CONFIG_CMRT_OMC_ESW_RSVD_FIRST
export CONFIG_CMRT_OMC_ESW_RSVD_WORDS
export OTP_SIZE
export OTP_ESW
export SBOOT_IMG = $(ZEPHYR_BASE)/samples/cmrt/sboot/$(BUILDDIR)/sboot.img
ifeq ($(CONFIG_CMRT_SBOOT_IN_ROM),y)
    export SBOOT_IMG_LEN = 0
else
    export SBOOT_IMG_LEN = $(shell stat -c %s $(SBOOT_IMG))
endif

# Dependencies of footer.json are not that easy to express currently,
# so let's just rebuild it always for simplicity.
.PHONY: FORCE
$(user_footer): FORCE
	./make-footer.sh >$@

$(user_name): $(user_footer)

.PHONY: clean-footer
clean-footer:
	-rm -f footer.json
clean: clean-footer
