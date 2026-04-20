add_library(generic_timer
	STATIC
	generic_timer.c
)

target_link_libraries(generic_timer
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(generic_timer
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
