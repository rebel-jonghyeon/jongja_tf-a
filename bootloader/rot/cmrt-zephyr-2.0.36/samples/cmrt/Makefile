
DIRS := sboot hlos_tools supervisors userspace perso

ifdef CMRT_MAKE_FILTER_OUT
DIRS := $(filter-out $(CMRT_MAKE_FILTER_OUT), $(DIRS))
endif

.PHONY: all
all: $(DIRS)
	$(info $@ done)

# toplevel inter-dir dependencies (DIRS may be provided in make command line)
# (dependencies must be pre-satisfied if missing in DIRS)
# note that eg `make perso` would have sboot and supervisors as dependencies
userspace perso: $(filter supervisors, $(DIRS))
perso: $(filter sboot, $(DIRS))

CLEAN_PRISTINE := $(filter clean pristine, $(MAKECMDGOALS))

# for recipes not to complain when undefined
MAKEOVERRIDES ?=

# "the" build rule
.PHONY: $(DIRS)
$(DIRS): $(CLEAN_PRISTINE)
	$(MAKE) -C $@ all $(MAKEOVERRIDES)

.PHONY: config
config: $(CLEAN_PRISTINE)
	$(MAKE) -C supervisors config


# do clean/pristine in all DIRS first, in case 'all' also given
ifneq ($(CLEAN_PRISTINE),)
CLEAN := $(DIRS:=--) # add trailing '--' to all words in DIRS ...
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
