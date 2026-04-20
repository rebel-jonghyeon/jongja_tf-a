add_library(dvfs
	OBJECT
	dvfs.c
)

target_link_libraries(dvfs
        PUBLIC
        ${DEVICE_DRIVER_COMMON_LIBS}
		pmic
		cmu
)

target_include_directories(dvfs
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

