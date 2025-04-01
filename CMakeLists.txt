cmake_minimum_required( VERSION 3.21..3.29 )

project( bparser LANGUAGES CXX )

add_subdirectory( src )
target_include_directories( bparser PUBLIC include )

add_subdirectory( test )
