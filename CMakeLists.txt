cmake_minimum_required(VERSION 3.27)
project(files C)

set(CMAKE_C_STANDARD 11)

add_executable(files
        main.c
        max-clique.c)
