add_library(rbcm
	OBJECT
	rbcm_core.c
	rbcm_driver.c
)

target_link_libraries(rbcm
	PUBLIC
		${DEVICE_DRIVER_COMMON_LIBS}
	PRIVATE
)

target_include_directories(rbcm
	PUBLIC
		${${DD_COMMON_INCLUDES}}
		${CMAKE_CURRENT_LIST_DIR}
	PRIVATE
)