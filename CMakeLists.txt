cmake_minimum_required(VERSION 3.14)
project(cxx_creed)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(src)

add_subdirectory(src)
