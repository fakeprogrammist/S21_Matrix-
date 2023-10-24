cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        s21_matrix_oop.cc
        s21_matrix_oop.h
        main.cc
        s21_utils.cc)
