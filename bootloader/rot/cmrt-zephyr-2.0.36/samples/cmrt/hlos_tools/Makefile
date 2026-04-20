
# Executes the given make command line in all $(HLOS_TOOLS) subdirectories

# defines e.g. HLOS_TOOLS
include ../$(BOARD).mk

HLOS_TOOLS = lms xmss

# this .PHONY seemingly unnecessary, but leaves out stat(2)ing 'all'...
.PHONY: all
all: $(HLOS_TOOLS)

CLEAN_PRISTINE := $(filter clean pristine, $(MAKECMDGOALS))

# for recipes not to complain when undefined
MAKECMDGOALS ?=

# "the" build rule
.PHONY: $(HLOS_TOOLS)
$(HLOS_TOOLS): $(CLEAN_PRISTINE)
# runs in parallel if requested
$(HLOS_TOOLS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# do clean/pristine in all HLOS_TOOLS first, in case 'all' also given
ifneq ($(CLEAN_PRISTINE),)
CLEAN := $(HLOS_TOOLS:=--) # add trailing '--' to all words in HLOS_TOOLS ...
.PHONY: clean pristine
clean pristine: $(CLEAN)

.PHONY: $(CLEAN)
$(CLEAN): # ... drop trailing '--' below
	$(MAKE) -C $(@:--=) $(CLEAN_PRISTINE)
endif


.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
