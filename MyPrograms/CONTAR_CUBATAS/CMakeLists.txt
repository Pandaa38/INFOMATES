cmake_minimum_required(VERSION 3.30)
project(CONTAR_CUBATAS)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(CONTAR_CUBATAS main.cpp
        src/Cubata.cpp
        include/Cubata.h)
