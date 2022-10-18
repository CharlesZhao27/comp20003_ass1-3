cmake_minimum_required(VERSION 3.23)
project(ass3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ass3 src/flow_solver.c src/engine.c src/extensions.c src/node.c src/options.c src/queues.c src/search.c
        src/utils.c)
