cmake_minimum_required(VERSION 3.15)

project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList
src/DateTime.cpp
src/DateTimeUtility.cpp
src/Task.cpp
src/InputHandler.cpp
src/TasksManager.cpp
src/main.cpp
)

target_include_directories(ToDoList PUBLIC
  src
  include
)
