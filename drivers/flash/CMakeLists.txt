add_library(flash
	OBJECT
	mt25q_flash.c
)

target_link_libraries(flash
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(flash
	PUBLIC
	${${DD_COMMON_INCLUDES}}
	${CMAKE_CURRENT_LIST_DIR}
)
