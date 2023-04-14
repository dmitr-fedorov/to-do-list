cmake_minimum_required(VERSION 3.15)

project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList
src/DateTimeUtility.cpp
src/DateTime.cpp
src/Task.cpp
src/TaskList.cpp
src/TaskStorageFile.cpp
src/InputAnalysisTools.cpp
src/CommandAdd.cpp
src/CommandUpdate.cpp
src/CommandDelete.cpp
src/CommandDone.cpp
src/CommandSelect.cpp
src/CommandSave.cpp
src/CommandsInvoker.cpp
src/main.cpp
)

target_include_directories(ToDoList PUBLIC
  src
  include
)
