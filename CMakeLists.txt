cmake_minimum_required(VERSION 3.12)
project(leetcode_io VERSION 0.3.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/example.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)