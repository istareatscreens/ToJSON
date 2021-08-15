cmake_minimum_required(VERSION 3.13.4)

set(This ToJSON)

project(${this} -C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    ToJSON.h
)

set(Sources
    ToJSON.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
