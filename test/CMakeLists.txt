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
