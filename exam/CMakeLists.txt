cmake_minimum_required(VERSION 3.21)
project(exam)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

include_directories(src)
add_subdirectory(src)

add_subdirectory(test)
