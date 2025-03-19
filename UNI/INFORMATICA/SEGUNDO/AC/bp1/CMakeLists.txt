cmake_minimum_required(VERSION 3.30)
project(bp1 C)

set(CMAKE_C_STANDARD 23)

find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}") #para c++
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}") #para c
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}") #nose gabriel lo tiene
endif()

add_executable(atomic atomic.c)
add_executable(barrier barrier.c)
add_executable(bucle-for bucle-for.c)
add_executable(critical critical.c)
add_executable(critical_sin critical_sin.c)
add_executable(master master.c)
add_executable(parallel parallel.c)
add_executable(single single.c)
