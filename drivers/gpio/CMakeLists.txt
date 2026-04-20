add_library(gpio
	OBJECT
	gpio.c
)

target_link_libraries(gpio
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(gpio
	PUBLIC
	${${DD_COMMON_INCLUDES}}
	${CMAKE_CURRENT_LIST_DIR}
)
