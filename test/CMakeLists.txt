if (NOT DEFINED BPARSER_TESTS)
	option(BPARSER_TESTS "Default Tests" ${PROJECT_IS_TOP_LEVEL})
endif()

if (BPARSER_TESTS)
	add_executable( bparser-tests tests.cxx )
	target_link_libraries( bparser-tests bparser )
	add_custom_command(
		TARGET bparser-tests
		COMMAND bparser-tests
		DEPENDS bparser-tests
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running bparser-tests..."
	)
endif()
