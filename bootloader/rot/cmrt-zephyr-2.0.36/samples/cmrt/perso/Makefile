include ../$(BOARD).mk
PERSOS ?= blank tested provisioned

.PHONY: all
all: $(PERSOS)

CLEAN_PRISTINE := $(filter clean pristine, $(MAKECMDGOALS))

# for recipes not to complain when undefined
MAKEOVERRIDES ?=

BUILDDIR ?= build

.PHONY: $(PERSOS)
# parallel build possible
$(PERSOS): $(CLEAN_PRISTINE)
	$(MAKE) -C $@ all $(MAKEOVERRIDES)

.PHONY: clean pristine
clean pristine:
	rm -rf $(PERSOS:%=%/$(BUILDDIR))

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
