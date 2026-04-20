add_library(i2c OBJECT i2c.c)

target_link_libraries(i2c
        PUBLIC
        ${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(i2c
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

