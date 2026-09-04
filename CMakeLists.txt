cmake_minimum_required(VERSION 4.1)
project(Software_Engineering_Project_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Software_Engineering_Project_2
        functions.c
        functions.h
        main.c)
