cmake_minimum_required(VERSION 3.15)
project(TowerOfHanoi CXX)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(TowerOfHanoiLib STATIC
    TowerOfHanoi.hpp
    TowerOfHanoi.cpp
)

add_executable(TowerOfHanoi
    ex02.cpp
)
target_link_libraries(TowerOfHanoi PRIVATE TowerOfHanoiLib)

configure_file(
    ex02_inp.txt
    ex02_inp.txt
    COPYONLY
)

add_executable(TowerOfHanoiTest
    ex02_test.cpp
)
target_link_libraries(TowerOfHanoiTest PRIVATE TowerOfHanoiLib gtest gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(TowerOfHanoiTest)
