# Copyright (c) 2017-2024 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(supervisor)

zephyr_cc_option(-Wno-pointer-arith)

if(NOT BUILDDIR)
  if(DEFINED ENV{BUILDDIR})
    set(BUILDDIR $ENV{BUILDDIR})
  else()
    set(BUILDDIR build)
  endif()
endif()

add_definitions(-DSUPERVISOR_VERSION_INFO="${SUPERVISOR_VERSION_INFO}")

target_include_directories(app
  PRIVATE
  src
  ${ZEPHYR_BASE}/include/portability
  ${ZEPHYR_BASE}
)

target_sources(                             app PRIVATE src/main.c)
target_sources(                             app PRIVATE src/cmd_echo.c)
target_sources(                             app PRIVATE src/cmd_enable_debug.c)
target_sources(                             app PRIVATE src/cmd_list.c)
target_sources(                             app PRIVATE src/cmd_sha.c)
target_sources(                             app PRIVATE src/cmd_fmc.c)
target_sources(                             app PRIVATE src/cmd_ecdsa.c)
target_sources(                             app PRIVATE src/cmd_rsa.c)
target_sources(                             app PRIVATE src/cmd_rsa_key_exch.c)
target_sources(                             app PRIVATE src/cmd_aes.c)
target_sources(                             app PRIVATE src/cmd_kdc.c)
target_sources(                             app PRIVATE src/cmd_random.c)
target_sources(                             app PRIVATE src/common.c)
target_sources(                             app PRIVATE src/rsa_padding.c)
target_sources(                             app PRIVATE src/swap_endian.c)
if(CONFIG_SHELL)
  target_sources(                           app PRIVATE src/cmrt_shell.c)
  target_sources_ifdef(CONFIG_FLASH         app PRIVATE src/flash_shell.c)
  target_sources_ifdef(CONFIG_CRI_OMC_EMULATED_OTP app PRIVATE src/shell_otp.c)
endif()
target_sources_ifdef(CONFIG_CMRT_SID        app PRIVATE src/cmd_sid.c)
target_sources_ifdef(CONFIG_CMRT_FFDH       app PRIVATE src/cmd_ffdh.c)
target_sources_ifdef(CONFIG_UART_NS16550    app PRIVATE src/cmd_uart_config.c)
target_sources_ifdef(CONFIG_CMRT_ECIES      app PRIVATE src/cmd_ecies.c)
target_sources_ifdef(CONFIG_CRI_OMC_EMULATED_OTP app PRIVATE src/cmd_otp.c)
target_sources_ifdef(CONFIG_CRI_OMC_EMULATED_OTP app PRIVATE src/oec_common.c)
target_sources(                             app PRIVATE src/cmd_ecdh.c)
target_sources_ifdef(CONFIG_CMRT_CCP        app PRIVATE src/cmd_ccp.c)
target_sources_ifdef(CONFIG_SV_PERF_MEAS    app PRIVATE src/cmd_perf.c)

target_link_libraries(app PUBLIC "-Wl,-e__reset")
