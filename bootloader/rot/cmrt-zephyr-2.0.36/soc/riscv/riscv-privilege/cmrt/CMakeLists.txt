# Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)

zephyr_sources_ifdef(CONFIG_CMRT_EAC soc.c)

zephyr_sources_ifdef(CONFIG_SUPERVISOR_MODE supervisor.S)
