# Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).

zephyr_sources(src/teefs.c src/teedev.c)
zephyr_include_directories(${ZEPHYR_BASE}/include/fs)
