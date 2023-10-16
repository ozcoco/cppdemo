cmake_minimum_required(VERSION 3.26)

file(RELATIVE_PATH SUB_PROJECT_PATH_NAME ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR})
project(${SUB_PROJECT_PATH_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC "./*.c*" "./*.h*")

include_directories(./)

add_executable("test-${SUB_PROJECT_PATH_NAME}" ${SRC})