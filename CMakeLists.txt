cmake_minimum_required(VERSION 3.0)

project(amin LANGUAGES C)

add_executable(amin main.c)

install(TARGETS amin RUNTIME DESTINATION bin)
