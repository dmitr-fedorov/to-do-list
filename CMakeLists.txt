cmake_minimum_required(VERSION 3.15)

project(to-do-list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)