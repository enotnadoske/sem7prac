cmake_minimum_required(VERSION 3.16)
project(game_of_life)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O5")
add_executable(game_of_life main.cpp)