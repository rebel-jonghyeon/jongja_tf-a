# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(supervisor)

add_definitions(-DSUPERVISOR_VERSION_INFO="${SUPERVISOR_VERSION_INFO}")

target_sources(app PRIVATE src/main.c)
target_link_libraries(app PUBLIC "-Wl,-e__reset")
