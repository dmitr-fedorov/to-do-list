cmake_minimum_required(VERSION 3.15)

project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList
src/DateTimeUtility.cpp
src/DateTime.cpp
src/Task.cpp
src/TasksManager.cpp
src/InputAnalysisTools.cpp
src/InputHandler.cpp
src/main.cpp
)

target_include_directories(ToDoList PUBLIC
  src
  include
)
