add_library(cmu OBJECT cmu.c)

target_link_libraries(cmu
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(cmu
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
