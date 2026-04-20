add_library(test_pmic
	OBJECT
	test_pmic_main.c
)

target_link_libraries(test_pmic
	PUBLIC
	cli_service
	${DD_LISTS}
)
target_include_directories(test_pmic
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
