add_library(test_mmu
	OBJECT
	test_mmu_main.c
)

target_link_libraries(test_mmu
	PRIVATE	cli_service
)

target_include_directories(test_mmu
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
