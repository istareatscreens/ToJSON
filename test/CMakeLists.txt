cmake_minimum_required(VERSION 3.13.4)

set(This ToJSONTests)

set(Sources
    ToJSONTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC 
    gtest_main
    ToJSON
)

add_test(
    NAME ${This}
    COMMAND ${This}
)