cmake_minimum_required(VERSION 3.15)
project(TowerOfHanoi CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    ex02.cpp
)

add_library(Hanoi_lib STATIC ${SOURCE_FILES})

add_executable(UnitTest Unittest.cpp)
target_link_libraries(UnitTest PRIVATE Hanoi_lib)
