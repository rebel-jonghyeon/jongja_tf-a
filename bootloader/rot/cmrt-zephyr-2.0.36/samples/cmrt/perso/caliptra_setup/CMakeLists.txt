# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(caliptra_setup)

add_definitions(-DPERSO_VERSION_INFO="${PERSO_VERSION_INFO}")

target_sources(app PRIVATE
	src/common.c
	src/main.c)
target_include_directories(app PRIVATE ${BUILDDIR})
target_link_libraries(app PUBLIC "-Wl,-e__reset")
target_link_libraries(app PRIVATE caliptra)
