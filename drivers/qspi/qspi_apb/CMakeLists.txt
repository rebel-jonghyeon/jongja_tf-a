add_library(qspi_apb
	OBJECT
	qspi_apb.c
)

target_link_libraries(qspi_apb
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(qspi_apb
	PUBLIC
	${${DD_COMMON_INCLUDES}}
	${CMAKE_CURRENT_LIST_DIR}
)
