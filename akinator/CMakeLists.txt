cmake_minimum_required(VERSION 3.23)
project(akinator C)

set(CMAKE_C_STANDARD 99)

add_executable(akinator main.c functions.c functions.h)

target_link_libraries(akinator winmm)