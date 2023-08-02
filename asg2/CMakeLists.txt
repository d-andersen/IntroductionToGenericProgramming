cmake_minimum_required(VERSION 3.10)
project(asg2)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES)

include_directories(src)
add_subdirectory(src)

add_subdirectory(test)
