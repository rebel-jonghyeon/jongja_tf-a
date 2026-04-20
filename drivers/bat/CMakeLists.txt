add_library(bat
	STATIC
	bat.c
)

target_link_libraries(bat
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(bat
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
