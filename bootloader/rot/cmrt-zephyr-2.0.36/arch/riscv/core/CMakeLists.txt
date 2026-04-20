# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_RISCV_PMP pmp)
add_subdirectory_ifdef(CONFIG_CMRT_MPU mpu)

zephyr_library()

zephyr_library_sources(
  cpu_idle.c
  fatal.c
  irq_manage.c
  prep_c.c
  reboot.c
  reset.S
  swap.S
  thread.c
)

if(CONFIG_SOC_SERIES_RISCV_CMRT)
zephyr_library_sources_ifndef(CONFIG_ARCH_HAS_CUSTOM_ISR cmrt_isr.S)
else()
zephyr_library_sources_ifndef(CONFIG_ARCH_HAS_CUSTOM_ISR isr.S)
endif()
zephyr_library_sources_ifdef(CONFIG_IRQ_OFFLOAD irq_offload.c)
zephyr_library_sources_ifdef(CONFIG_THREAD_LOCAL_STORAGE tls.c)
zephyr_library_sources_ifdef(CONFIG_USERSPACE userspace.S)
zephyr_library_sources_ifdef(CONFIG_RISCV_MISALIGNED_FIXUP fixup.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_SAC_ACCESS_FIXUP fixup.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_OMC otp_fixup.c)
