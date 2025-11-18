cmake_minimum_required(VERSION 4.0)
project(todo)

set(CMAKE_CXX_STANDARD 20)

add_executable(TodoList
        main.cpp
        Task.cpp
        TodoList.cpp
)
