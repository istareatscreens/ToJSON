cmake_minimum_required(VERSION 3.13.4)

set(This ToJSON)

project(${This} VERSION 0.0.1
                DESCRIPTION "Provides an easy way to place data into JSON format"
                HOMEPAGE_URL "https://github.com/istareatscreens/ToJSON" )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set_source_files_properties(${This} PROPERTIES COMPILE_FLAGS -Wall -Wcast-align -Wconversion -Wctor-dtor-privacy -Werror -Wextra -Wpedantic -Wshadow -Wsign-conversion)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

set(_INTERFACE_OR_PUBLIC INTERFACE)
add_library(${This} INTERFACE)
add_library(${This}::${This} ALIAS ${This})

add_subdirectory(test)