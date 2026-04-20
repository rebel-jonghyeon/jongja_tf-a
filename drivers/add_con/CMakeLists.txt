add_library(add_con
	OBJECT
	add_con.c
)

target_link_libraries(add_con
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(add_con
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	../cmu
)
