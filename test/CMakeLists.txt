cmake_minimum_required(VERSION 2.8.3)

set(This nop_tests)

set(Sources
    nop_test.cpp
    controller_test.cpp
    model_test.cpp
    runner_test.cpp
)

enable_testing()

add_subdirectory(
    include/googletest
)

add_executable(${This} ${Sources})

target_link_libraries( ${This} PUBLIC
    gtest_main
    nop_cpp
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
