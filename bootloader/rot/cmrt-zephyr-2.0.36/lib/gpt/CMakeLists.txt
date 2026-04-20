zephyr_library_named(rebel_h_gpt)
zephyr_library_sources(
  src/rebel_h_gpt.c
)
target_include_directories(rebel_h_gpt PUBLIC include)

include_directories(
  ../../../../../common/include
  )
