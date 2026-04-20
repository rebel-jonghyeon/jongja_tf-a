zephyr_library_named(caliptra)
zephyr_library_sources(
  src/x509.c
  src/crypto.c
  src/zeroize.c
  src/assets.c
  src/uds.c
  src/field_entropy.c
  src/flow.c
  src/handover.c
)
target_include_directories(caliptra PUBLIC include)
