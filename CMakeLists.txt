cmake_minimum_required(VERSION 3.22)
project(Elevator)

set(CMAKE_CXX_STANDARD 14)
include_directories(src/include)
aux_source_directory(src/main dir_srcs)
set(WORK ${dir_srcs})
add_executable(Elevator ${WORK})
