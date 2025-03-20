if (BPARSER_TESTS)
	add_executable( bparser-tests tests.cxx )
	target_link_libraries( bparser-tests bparser )
endif()
