cmake_minimum_required(VERSION 3.14)
project(Project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project4 main.cpp sampler.cpp sampler.h output.cpp pathfinder.h DisjointSetForest.cpp DisjointSetForest.h)