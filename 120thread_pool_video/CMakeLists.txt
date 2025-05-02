cmake_minimum_required(VERSION 3.31.6)

project(thread_tool)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILE *.cpp)

message(STATUS ${SRC_FILE})

add_executable(${PROJECT_NAME} ${SRC_FILE})
