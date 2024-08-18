cmake_minimum_required(VERSION 3.20)

project("libVescCan" C)

set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(${PROJECT_NAME} STATIC)

add_subdirectory(src/libVescCan)
