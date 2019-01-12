cmake_minimum_required(VERSION 3.13)
project(fligtSimProj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(fligtSimProj2 main.cpp ISearcher.h ISearchable.h CacheManager.cpp CacheManager.h ClientHandler.h CompareState.h
        FileCacheManager.cpp FileCacheManager.h Main.cpp MySerialServer.h MySerialServer.cpp MyTestClientHandler.h MySerialServer.cpp
        PQueueSearcher.h Searcher.h Server.h Solver.h State.h State.cpp StringReverser.h StringReverser.cpp)