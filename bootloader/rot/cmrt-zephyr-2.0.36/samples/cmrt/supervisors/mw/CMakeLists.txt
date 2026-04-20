# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(supervisor)

if(CONFIG_DEBUG)
  zephyr_cc_option(-Os)
endif()
add_definitions(-DSUPERVISOR_VERSION_INFO="${SUPERVISOR_VERSION_INFO}")

zephyr_include_directories_ifdef(
  CONFIG_TEST_REBEL_H
  src/test
  )

target_include_directories(app PRIVATE
  ${ZEPHYR_BASE}/samples/cmrt/fboot/include
  ${ZEPHYR_BASE}/drivers/dma
  ${ZEPHYR_BASE}/drivers/ipm
  ${ZEPHYR_BASE}/drivers/spi
  ${ZEPHYR_BASE}/drivers/misc/pvt_con
  ${ZEPHYR_BASE}/include
  ${ZEPHYR_BASE}/lib/gpt/include
  ${ZEPHYR_BASE}/lib/integrity/include
  ${ZEPHYR_BASE}/drivers/otp
  src/pcie
  )

target_sources_ifdef(CONFIG_TEST_REBEL_H
  app
  PRIVATE
  src/test/test_main.c
  src/test/test_mailbox.c
  src/test/test_crypto.c
  src/test/test_qspi.c
  )

target_sources(app PRIVATE
  src/cmrt_container.c
  src/main.c
  ${ZEPHYR_BASE}/drivers/dma/dma_pl330.c
  ${ZEPHYR_BASE}/drivers/ipm/ipm_samsung.c
  ${ZEPHYR_BASE}/drivers/misc/pvt_con/pvt_con.c
  ${ZEPHYR_BASE}/drivers/syscon/sysreg_rot.c
  ${ZEPHYR_BASE}/drivers/spi/qspi.c

  src/pcie/pcie_ide.c
  src/test/test_pvt_con.c
  src/test/test_otp.c
  ${ZEPHYR_BASE}/drivers/otp/otp.c
  )
target_link_libraries(app PUBLIC "-Wl,-e__reset")

if(CONFIG_CMRT_CALIPTRA_SUPPORT)
  target_sources(app PRIVATE src/caliptra.c)
  target_link_libraries(app PRIVATE caliptra)
endif()
