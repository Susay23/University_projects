cmake_minimum_required(VERSION 3.28)
project(session_2)
set(CMAKE_CXX_STANDARD 17)
add_executable(session_2 main.cpp)

configure_file(dt.txt dt.txt COPYONLY)
