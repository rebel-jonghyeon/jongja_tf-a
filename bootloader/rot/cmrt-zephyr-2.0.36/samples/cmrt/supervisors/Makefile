
include ../$(BOARD).mk

CLEAN_PRISTINE := $(filter clean pristine, $(MAKECMDGOALS))

BUILDDIR ?= build

.PHONY: all
all: $(SUPERVISORS)

.PHONY: config
config: $(notdir $(OS_DIR))

# for recipes not to complain when undefined
MAKECMDGOALS ?=

.PHONY: $(SUPERVISORS)
# parallel build possible
$(SUPERVISORS): $(CLEAN_PRISTINE)
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: clean pristine
clean pristine:
	rm -rf $(SUPERVISORS:%=%/$(BUILDDIR))

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
