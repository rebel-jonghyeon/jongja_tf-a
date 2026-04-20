# Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)

set(EMU_PLATFORM qemu)

set(QEMU_binary_suffix riscv32)
set(QEMU_CPU_TYPE_${ARCH} riscv32)

if(NOT BUILDDIR)
  if(DEFINED ENV{BUILDDIR})
    set(BUILDDIR $ENV{BUILDDIR})
  else()
    set(BUILDDIR build)
  endif()
endif()

set(QEMU_FLAGS_${ARCH}
  -nographic
  -machine cmrt
  -cmrt config=$ENV{ZEPHYR_BASE}/${BUILDDIR}/board.json
)

board_set_debugger_ifnset(qemu)
