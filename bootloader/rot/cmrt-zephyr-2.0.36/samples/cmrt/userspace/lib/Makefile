USERLIBS := libc os teefs cmrt_v1 libucu
USERLIBS += libshsig
USERLIBS += caliptra

.PHONY: all $(USERLIBS) clean pristine
all clean pristine:	$(USERLIBS)

# translate goal into submakes
submake_goal := $(filter-out $(USERLIBS),$(subst pristine,clean,$(MAKECMDGOALS)))

# never care about success of (translated) "clean"
prefix := $(if $(filter clean,$(submake_goal)),-,)

$(USERLIBS):
	$(prefix)$(MAKE) -C $@ $(submake_goal)

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
unexport MAKEFLAGS
