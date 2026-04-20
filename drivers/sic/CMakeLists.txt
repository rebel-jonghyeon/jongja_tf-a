add_library(sic OBJECT sic.c)

target_link_libraries(sic
        PUBLIC
        ${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(sic
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

