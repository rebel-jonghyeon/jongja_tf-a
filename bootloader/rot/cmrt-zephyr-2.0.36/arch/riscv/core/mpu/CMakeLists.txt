#
# Copyright (c) 2020 BayLibre, SAS
#
# SPDX-License-Identifier: Apache-2.0
#

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_CMRT_MPU cmrt_mpu.c)

zephyr_include_directories(.)
