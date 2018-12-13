cmake_minimum_required(VERSION 2.8)
project(MastermindSolver)

set(CMAKE_CXX_STANDARD 17)
set(GCC_MPI_FLAGS "-lmpi")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${G++_MPI_FLAGS}")

find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})
add_subdirectory(utils)
add_subdirectory(players)

add_executable(MastermindSolver main.cpp)

target_link_libraries(MastermindSolver ${MPI_CPP_LIBRARIES})
target_link_libraries(MastermindSolver utils)
target_link_libraries(MastermindSolver players)