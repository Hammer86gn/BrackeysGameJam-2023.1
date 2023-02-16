cmake_minimum_required(VERSION 3.22)
project(stbi C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_library(stbi STATIC inc/stb_image.h stb_image.c)
target_include_directories(stbi PUBLIC inc)

