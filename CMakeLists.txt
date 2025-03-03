cmake_minimum_required(VERSION 3.13)
project(System_Design)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/utility)
include_directories(include/algorithms)

add_library(System_Design INTERFACE)

target_include_directories(System_Design INTERFACE include)

add_subdirectory(tests)

