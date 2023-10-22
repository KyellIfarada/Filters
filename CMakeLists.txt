cmake_minimum_required(VERSION 3.25)
project(IfaradaFilters_c C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_library(IfaradaFilters_c SHARED IfaradaFilters.c)


target_link_libraries(<target_link_libraries(IfaradaFilters.c)> m)

