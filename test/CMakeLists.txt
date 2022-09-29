cmake_minimum_required(VERSION 2.8.3)

set(This nop_tests)

set(Sources
    nop_test.cpp
    controller_test.cpp
    model_test.cpp
    runner_test.cpp
    reader_test.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")

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

add_custom_command(TARGET ${This}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/test_data
                ${CMAKE_CURRENT_BINARY_DIR}/test_data)
