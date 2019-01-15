cmake_minimum_required(VERSION 3.13)
project(fligtSimProj2)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(fligtSimProj2 main.cpp ISearcher.h ISearchable.h CacheManager.cpp
        CacheManager.h ClientHandler.h CompareState.h
        FileCacheManager.cpp FileCacheManager.h Main.cpp MySerialServer.h
        MySerialServer.cpp MyTestClientHandler.cpp Utils.cpp Utils.h
        MyTestClientHandler.h MySerialServer.cpp MyParallelServer.cpp MyParallelServer.h
        PQueueSearcher.h Searcher.h Server.h Solver.h State.h
        State.cpp StatePriority.h StringReverser.h StringReverser.cpp Matrix.h Matrix.cpp DepthFirstSearch.h)