cmake_minimum_required(VERSION 3.0)
add_executable(interpreter file_io.c interpreter.c)
add_definitions(-Wall -Wextra -O3)
#  add_definitions(-g -Wall -Wextra -O3)
