cmake_minimum_required(VERSION 2.8.3)

set(This nop_cpp)

project(${This} C CXX)

option (BUILD_TESTS "Build GTests" ON)
option (TO_CATKIN_WS "" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(
    lib/include
)

set(LibSources
    lib/baseFunctions.cpp
    lib/controller.cpp
    lib/model.cpp
    lib/nop.cpp
    # lib/runner.cpp  # do we need runner ??? IMO -no
)

add_library(${This} STATIC ${LibSources})

if (BUILD_TESTS)

add_subdirectory(
    test
)

endif()


if (TO_CATKIN_WS)

install(
    TARGETS nop_cpp
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

endif()

