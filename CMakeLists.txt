cmake_minimum_required(VERSION 2.8.3)

set(This nop_cpp)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(
    include/googletest
)

include_directories(
    include
    lib/include
)

set(LibSources
    lib/baseFunctions.cpp
    lib/nop.cpp
    lib/model.cpp
    lib/controller.cpp
    lib/runner.cpp
)

add_library(${This} STATIC ${LibSources})

# Create tests
add_subdirectory(
    test
)

# # Create more complex test (TNetOperTest)
# add_executable(test_app app/test_app.cpp)

# target_link_libraries(test_app PUBLIC
#     nop_cpp
# )
