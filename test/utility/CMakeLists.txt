cmake_minimum_required(VERSION 2.8)

set(This Utility)

set(Sources
    test_clock.cpp
    test_any.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
)

# gtest_add_tests(TARGET ${This})

add_test(
    NAME ${This} 
    COMMAND ${This}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)