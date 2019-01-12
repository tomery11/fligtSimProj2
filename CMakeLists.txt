cmake_minimum_required(VERSION 3.13)
project(fligtSimProj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(fligtSimProj2 main.cpp ISearcher.h ISearchable.h State.cpp State.h StatePriority.h CompareState.h Searcher.h PQueueSearcher.h)