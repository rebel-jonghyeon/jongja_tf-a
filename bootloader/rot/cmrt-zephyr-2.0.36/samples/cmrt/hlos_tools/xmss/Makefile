BUILDDIR ?= build
TOOLCHAIN_INSTALL_DIR ?= /opt/cmrt/bsp-zc706-zynq7
MINGW_INSTALL_DIR ?= /usr/bin
ZEPHYR_BASE_BUILDDIR ?= $(ZEPHYR_BASE)/$(BUILDDIR)

CROSS_GCC = $(wildcard $(TOOLCHAIN_INSTALL_DIR)/sysroots/x86_64-*-linux/usr/bin/arm-*-linux-gnueabi/arm-*-linux-gnueabi-gcc)

# sudo apt-get install gcc-mingw-w64-x86-64
MINGW_GCC = $(wildcard $(MINGW_INSTALL_DIR)/x86_64-w64-mingw32-gcc)

all: libxmss.so test_xmss install \
     vcu108/libxmss.so

# if CROSS_GCC exists, add zynq706/* components to all:
ifneq ("$(wildcard $(CROSS_GCC))", "")
all: zynq706/libxmss.so zynq706/install
endif

INCLUDE = -I.
CFLAGS = -ggdb -std=c99 -O2 -fPIC $(INCLUDE) -Wall -Werror -Wno-deprecated-declarations -fstack-protector
VERSION_INFO := $(shell set -- `git log -1 --abbrev=7 --format="%ci %h"`;\
			test "$${4-}" && echo $$1-g$$4 || :)

ifdef VERSION_INFO
CFLAGS += -DVERSION_INFO='"$(VERSION_INFO)"'
endif

CC = gcc

FPGAGOALS = zynq706/libxmss.so zynq706/test_xmss

$(FPGAGOALS): TITARGETOPTS = -march=armv7-a -marm -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9
$(FPGAGOALS): SYSROOT = --sysroot $(wildcard $(TOOLCHAIN_INSTALL_DIR)/sysroots/cortexa9hf-neon-*-linux-gnueabi)
$(FPGAGOALS): CC = $(CROSS_GCC) $(TITARGETOPTS) $(SYSROOT)


vcu108 zynq706 mingw:
	mkdir -p $@ $@/tiny_sha3

%.o: %.c Makefile
	$(CC) -c -o $@ $< $(CFLAGS)

vcu108/%.o: %.c Makefile | vcu108
	$(CC) -c -o $@ $< $(CFLAGS)

zynq706/%.o: %.c Makefile | zynq706
	$(CC) -c -o $@ $< $(CFLAGS)

mingw/%.o: %.c Makefile | mingw
	$(MINGW_GCC) -c -o $@ $< $(CFLAGS)

libxmss.so: xmss_ots.o xmss.o xmss_py.o utils.o xmss_param.o tiny_sha3/sha3.o
	$(CC) -shared -Wl,-soname,$(@F) -o $@ $^ -lcrypto

vcu108/libxmss.so: vcu108/xmss_ots.o vcu108/xmss.o vcu108/xmss_py.o vcu108/xmss_param.o vcu108/tiny_sha3/sha3.o
	$(CC) -shared -Wl,-soname,$(@F) -o $@ $^ -lcrypto

zynq706/libxmss.so: zynq706/xmss_ots.o zynq706/xmss.o zynq706/xmss_py.o zynq706/xmss_param.o zynq706/tiny_sha3/sha3.o
	$(CC) -shared -Wl,-soname,$(@F) -o $@ $^ -lcrypto

LDFLAGS_BIN_AMD64 ?=

test_xmss: main.o utils.o libxmss.so
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS_BIN_AMD64) -L. -lxmss -lcrypto

install: libxmss.so test_xmss
	install -d $(ZEPHYR_BASE_BUILDDIR)/bin
	install -d $(ZEPHYR_BASE_BUILDDIR)/lib/python
	install -m 644 libxmss.so $(ZEPHYR_BASE_BUILDDIR)/lib
	install -m 755 xmss.py $(ZEPHYR_BASE_BUILDDIR)/lib/python
	install -m 755 test_xmss $(ZEPHYR_BASE_BUILDDIR)/bin

zynq706/install: zynq706/libxmss.so
	install -d $(ZEPHYR_BASE_BUILDDIR)/zynq706
	install -m 644 zynq706/libxmss.so $(ZEPHYR_BASE_BUILDDIR)/zynq706
	install -m 755 xmss.py $(ZEPHYR_BASE_BUILDDIR)/zynq706

.PHONY: clean pristine install zynq706/install
clean pristine:
	rm -rf *.o *.so *.a *~ test_xmss tiny_sha3/*.o vcu108/ zynq706/
	rm -fr $(ZEPHYR_BASE_BUILDDIR)/bin $(ZEPHYR_BASE_BUILDDIR)/lib $(ZEPHYR_BASE_BUILDDIR)/zynq706

.SUFFIXES: # remove default suffix rules
MAKEFLAGS += --no-builtin-rules --warn-undefined-variables
