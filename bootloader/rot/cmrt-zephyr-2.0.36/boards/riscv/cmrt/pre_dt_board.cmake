# Suppress "unique_unit_address_if_enabled" to handle the overlap
# of PKE RAM and start of SRAM.
list(APPEND EXTRA_DTC_FLAGS "-Wno-unique_unit_address_if_enabled")
