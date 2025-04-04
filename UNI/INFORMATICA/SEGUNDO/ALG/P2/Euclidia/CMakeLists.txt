cmake_minimum_required(VERSION 3.30)
project(P2)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(euclidia_fuerza scr/euclidia_fuerza.cpp scr/Punto2D.cpp include/Punto2D.h)
add_executable(euclidia_divide scr/euclidia_divide.cpp scr/Punto2D.cpp include/Punto2D.h)
