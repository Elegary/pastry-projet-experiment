cmake_minimum_required(VERSION 3.20)
project(pastry_project C)

set(CMAKE_C_STANDARD 99)

add_executable(pastry_project main.c pastry.h pastry.c)
