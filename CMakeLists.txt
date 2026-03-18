cmake_minimum_required(VERSION 3.16)
project(Parkhausimulation C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(parkhaus
    Code/src/Main.c
    Code/src/Konfig.c
    Code/src/Queue.c
    Code/src/Simulation.c
)

add_executable(test_queue
    Code/tests/test_queue.c
    Code/src/Queue.c
)

add_executable(test_simulation
    Code/tests/test_simulation.c
    Code/src/Simulation.c
    Code/src/Queue.c
)

add_executable(test_konfig
    Code/tests/test_konfig.c
    Code/src/Konfig.c
)
