add_library(intc
	STATIC
	gicv3.c
)

target_link_libraries(intc
	PUBLIC
	bakery_lock
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(intc
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
