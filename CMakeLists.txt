cmake_minimum_required(VERSION 2.8.9)
PROJECT(ASTAR)
add_compile_options(-std=c++11)
add_compile_options(-std=c++14)
ADD_EXECUTABLE(ASTAR 
main.cpp
A_star.cpp
)
