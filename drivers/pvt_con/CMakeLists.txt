add_library(pvt_con
	OBJECT
	pvt_con.c
)

target_link_libraries(pvt_con
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(pvt_con
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${DD_COMMON_INCLUDES}
)
