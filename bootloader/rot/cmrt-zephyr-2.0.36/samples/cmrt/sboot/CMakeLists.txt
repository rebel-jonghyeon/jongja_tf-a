# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sboot)

add_definitions(-DSBOOT_VERSION_INFO="${SBOOT_VERSION_INFO}")

target_include_directories(
	app
	PRIVATE
	${ZEPHYR_BASE}/kernel/include
	${ZEPHYR_BASE}/samples/cmrt/fboot/include
	${ZEPHYR_BASE}/samples/cmrt/fboot/src
	${ZEPHYR_BASE}/include
	${ZEPHYR_BASE}/drivers/cmrt
	${ZEPHYR_BASE}/lib/gpt/include
	${ZEPHYR_BASE}/lib/integrity/include
	src
	src/drivers/cmu
	src/drivers/dma
	src/drivers/spi
	src/drivers/timer
	src/drivers/uart
	src/drivers/sac
)

target_sources(
	app
	PRIVATE
	src/main.c
	src/emergency.c
	src/drivers/dma/dma.c
	src/drivers/cmu/cmu.c
	src/drivers/spi/dwc_ssi.c
	src/drivers/timer/timer.c
	src/drivers/uart/uart.c
	src/drivers/sac/sac_custom.c
	../../fboot/src/lifecycle.c
	../../fboot/src/fboot.c
	../../fboot/src/img.c
	../../fboot/src/syscalls.c
	../../fboot/src/supervisor.c
	../../fboot/src/supervisor.S
	../../fboot/src/isr.S
)

target_sources_ifdef(
	CONFIG_CMRT_DATASTORE
	app
	PRIVATE
	../../fboot/src/datastore.c
)

target_sources_ifdef(
	CONFIG_CMRT_CFI
	app
	PRIVATE
	../../fboot/src/cfi.c
)

target_sources_ifdef(
	CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY
	app
	PRIVATE
	../../fboot/src/fboot_rsa_verify.c
)

target_sources_ifdef(
	CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY
	app
	PRIVATE
	../../fboot/src/fboot_lms_verify.c
)

target_sources_ifdef(
	CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY
	app
	PRIVATE
	../../fboot/src/fboot_lms_hss_verify.c
)

target_sources_ifdef(
	CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
	app
	PRIVATE
	../../fboot/src/fboot_xmss_verify.c
)

if(CONFIG_CMRT_CALIPTRA_SUPPORT)
	target_sources(app PRIVATE src/caliptra.c)
	target_link_libraries(app PRIVATE caliptra)
endif()
