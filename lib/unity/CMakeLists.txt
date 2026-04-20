add_library(unity
	STATIC
	unity.c
	unity_fixture.c
)

target_compile_definitions(unity
	PRIVATE
	UNITY_EXCLUDE_SETJMP_H
	UNITY_EXCLUDE_MATH_H
	UNITY_EXCLUDE_STDDEF_H
	UNITY_FIXTURE_NO_EXTRAS
)

target_link_libraries(unity
	PUBLIC
	uart
	common
)

target_include_directories(unity
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/../../osl/FreeRTOS/Source/include # temp code for Unity example
)