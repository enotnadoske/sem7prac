cmake_minimum_required(VERSION 3.16)
project(untitled4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(untitled4 library.cpp library.h main.cpp Test/test.cpp)
target_link_libraries(untitled4 gtest gtest_main)
