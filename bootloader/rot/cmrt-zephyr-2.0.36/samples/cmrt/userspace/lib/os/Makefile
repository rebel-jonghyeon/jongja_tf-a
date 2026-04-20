CTOOLDIR=../common

user_name = libos.a
user_objs = ./assert.o \
	./base64.o \
	./clz32.o \
	./ctz32.o \
	./crc16_sw.o \
	./crc32c_sw.o \
	./crc32_sw.o \
	./crc7_sw.o \
	./crc8_sw.o \
	./cbprintf_nano.o \
	./heap.o \
	./hex.o \
	./hexdump.o \
	./json.o \
	./rb.o \
	./start.o \
	crtheap.o

user_cflags = -DCONFIG_SYS_HEAP_ALLOC_LOOPS=3 -DCONFIG_MISRA_SANE -DCONFIG_CBPRINTF_LIBC_SUBSTS

include ../../common/lib.mk
