add_library(pmic
	OBJECT
	ltc1427cs8.c
	tca9548a.c
	mp5998.c
	mpq8785.c
	mp29816a.c
	g1505.c
	pmic_mgr.c
)

target_link_libraries(pmic
        PUBLIC
        ${DEVICE_DRIVER_COMMON_LIBS}
		i2c
)

target_include_directories(pmic
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

