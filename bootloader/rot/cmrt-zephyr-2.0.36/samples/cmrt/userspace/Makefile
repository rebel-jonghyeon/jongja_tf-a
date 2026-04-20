
.PHONY: containers
containers:
	ln -sf container.mk common/lib.mk
	$(MAKE) -C lib all
	$(MAKE) -C containers all

.PHONY: all
all: containers

.PHONY: clean pristine
clean pristine:
	test -f common/lib.mk || ln -s container.mk common/lib.mk
	-$(MAKE) -C lib clean
	-$(MAKE) -C containers clean
	-test -L common/lib.mk && rm common/lib.mk || :

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
