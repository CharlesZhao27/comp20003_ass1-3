cmake_minimum_required(VERSION 3.23)
project(comp20003_ass2 C)

set(CMAKE_C_STANDARD 99)

add_executable(comp20003_ass2 stage3.c struct.c struct.h quadtree.c quadtree.h read.c read.h)
