CTOOLDIR=../common

user_name = libc.a
user_objs = ./source/time/gmtime.o \
	./source/time/time.o \
	./source/string/string.o \
	./source/string/strncasecmp.o \
	./source/string/strspn.o \
	./source/string/strstr.o \
	./source/stdout/sprintf.o \
	./source/stdout/fprintf.o \
	./source/stdout/stdout_console.o \
	./source/stdlib/atoi.o \
	./source/stdlib/abort.o \
	./source/stdlib/bsearch.o \
	./source/stdlib/qsort.o \
	./source/stdlib/malloc.o \
	./source/stdlib/rand.o \
	./source/stdlib/strtol.o \
	./source/stdlib/strtoul.o \
	./source/stdlib/exit.o

user_cflags = -DCONFIG_FPUTC_BUFFER_SIZE=80 -DCONFIG_MINIMAL_LIBC_RAND -DCONFIG_MINIMAL_LIBC_MALLOC -DCONFIG_MINIMAL_LIBC_MALLOC_ARENA_SIZE=1024 -DCONFIG_MINIMAL_LIBC_CALLOC -DCONFIG_MINIMAL_LIBC_REALLOCARRAY

include ../../common/lib.mk
