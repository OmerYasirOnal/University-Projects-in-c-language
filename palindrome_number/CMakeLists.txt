cmake_minimum_required(VERSION 3.26)
project(First C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(First
        main.c
        library.c
)
