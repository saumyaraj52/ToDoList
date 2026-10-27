cmake_minimum_required(VERSION 3.16)
project(TodoList VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define executable
add_executable(TodoList
    src/main.cpp
)
