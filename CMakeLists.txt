cmake_minimum_required(VERSION 3.8)
project(Deque)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES test.cpp deque.h)
add_executable(Deque ${SOURCE_FILES})
target_link_libraries(Deque gtest gtest_main)