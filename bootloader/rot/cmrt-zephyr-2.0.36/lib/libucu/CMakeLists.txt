zephyr_include_directories(include)

zephyr_library()
zephyr_library_sources(
  src/asn1.c
  src/ecies.c
  src/endianness.c
  src/reverse.c
  src/rsa_pad.c
  src/span.c
  src/bitstat.c
  src/edges.c
  src/kdf.c
)
