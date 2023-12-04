cmake_minimum_required(VERSION 3.23.2)

project(LAB7 VERSION 1.0.0)

add_compile_options(-g)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin/")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(LAB7 ${SOURCES})

target_include_directories(LAB7 PUBLIC headers)
target_link_libraries(LAB7 -g -std=c++17)