cmake_minimum_required( VERSION 3.20..3.29 )

project( bparser LANGUAGES CXX )

include_directories( include )

add_subdirectory( src )

set(BPARSER_TESTS BOOL TRUE)
add_subdirectory( test )
