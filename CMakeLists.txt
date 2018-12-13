cmake_minimum_required(VERSION 2.8)
project(MastermindSolver CXX)


set(CMAKE_CXX_COMPILER "mpiCC")
set(GCC_MPI_FLAGS "-lmpi")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${G++_MPI_FLAGS}")

find_package(MPI REQUIRED)

add_subdirectory(utils)

add_executable(MastermindSolver main.cpp players/Challenger.h players/GameMaster.h)

target_link_libraries(MastermindSolver utils)
