cmake_minimum_required(VERSION 3.30)
project(prueba)

set(CMAKE_CXX_STANDARD 23)

add_executable(quick quick.cpp)
add_executable(quick_ordenado quick_ordenado.cpp)
add_executable(quick_pequenios quick_pequenios.cpp)

add_executable(merge merge.cpp)
add_executable(merge_ordenado merge_ordenado.cpp)
add_executable(merge_pequenios merge_pequenios.cpp)

add_executable(bubble bubble.cpp)
add_executable(bubble_ordenado bubble_ordenado.cpp)
add_executable(bubble_pequenios bubble_pequenios.cpp)
