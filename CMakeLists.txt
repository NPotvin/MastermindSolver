cmake_minimum_required(VERSION 3.0)
project(MastermindSolver)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(utils)
add_subdirectory(players)

add_executable(MastermindSolver main.cpp)

target_link_libraries(MastermindSolver utils)
target_link_libraries(MastermindSolver players)