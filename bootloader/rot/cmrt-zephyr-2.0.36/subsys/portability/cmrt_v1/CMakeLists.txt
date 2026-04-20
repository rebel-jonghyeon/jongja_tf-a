# Copyright (c) 2023 by Cryptography Research, Inc. (CRI)

add_library(CMRT_V1 INTERFACE)

zephyr_include_directories(CMRT_V1 INTERFACE
  ${PROJECT_SOURCE_DIR}/include/portability
  ${PROJECT_SOURCE_DIR}/include/portability/cri/cmrt
  ${ZEPHYR_BASE}/include/cmrt
  ${ZEPHYR_BASE}/include/drivers
  ${ZEPHYR_BASE}/include/drivers/cmrt/teefs
)

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_CMRT_V1 wrapper.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_TEEDEV_RAM wrapper_teedev_ram.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_TEEDEV_DMAC wrapper_teedev_dmac.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_TEEDEV_FLASH wrapper_teedev_flash.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_TEEDEV_OTP wrapper_teedev_otp.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_ECIES wrapper_ecies.c)

zephyr_library_include_directories(
  ${ZEPHYR_BASE}/kernel/include
  ${ZEPHYR_BASE}/arch/${ARCH}/include
)

zephyr_library_link_libraries(CMRT_V1)
