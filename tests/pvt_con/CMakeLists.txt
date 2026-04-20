add_library(test_pvt_con
	OBJECT
	test_pvt_con.c
)

target_link_libraries(test_pvt_con
	PRIVATE	cli_service
	PUBLIC	pvt_con
)

target_include_directories(test_pvt_con
	PUBLIC
	${TEST_COMMON_INCLUDES}
)

add_library(pvt_cli
	OBJECT
	pvt_cli.c
	pvt_cli_show.c
	pvt_cli_enable.c
	pvt_cli_disable.c
	pvt_cli_set.c
)

target_link_libraries(pvt_cli
	PRIVATE	cli_service
	PUBLIC	pvt_con
)

target_include_directories(pvt_cli
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
