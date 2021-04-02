cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BallAlg-Serial)
set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES main.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(serial ${SOURCE_FILES})