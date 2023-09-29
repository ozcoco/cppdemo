cmake_minimum_required(VERSION 3.26)

file(RELATIVE_PATH PROJECT_PATH_NAME ${CMAKE_SOURCE_DIR}/../ ${CMAKE_SOURCE_DIR})

message(STATUS "PROJECT_PATH_NAME=${PROJECT_PATH_NAME}")

project(${PROJECT_PATH_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB SUB_PATH_LIST ${CMAKE_SOURCE_DIR}/*)

foreach (SUB_PATH ${SUB_PATH_LIST})
    if (IS_DIRECTORY ${SUB_PATH})
        file(RELATIVE_PATH SUB_PATH_NAME ${CMAKE_SOURCE_DIR} ${SUB_PATH})

        if (NOT SUB_PATH_NAME MATCHES "cmake-build-debug"
                AND NOT SUB_PATH_NAME MATCHES ".idea"
                AND NOT SUB_PATH_NAME MATCHES ".git")
            add_subdirectory(${SUB_PATH_NAME})
            message(STATUS "SUB_PATH_NAME=${SUB_PATH_NAME}")
        endif ()
    endif ()
endforeach ()
