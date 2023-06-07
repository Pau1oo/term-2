cmake_minimum_required(VERSION 3.23)
project(lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 lab5/main.c lab5/functions.c lab5/functions.h)
add_executable(akinator akinator/main.c akinator/functions.c akinator/functions.h)
add_executable(lab3 lab3/main.c lab3/functions.c lab3/functions.h)
add_executable(lab2 lab2/main.c lab2/functions.c lab2/functions.h)
add_executable(lab2decompr lab2decompr/main.c lab2decompr/functions.c lab2decompr/functions.h)
add_executable(lab1 lab1/main.c lab1/functions.c lab1/functions.h)