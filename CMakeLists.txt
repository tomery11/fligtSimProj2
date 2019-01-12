cmake_minimum_required(VERSION 3.13)
project(fligtSimProj2)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(fligtSimProj2 main.cpp Main.cpp Main.h Server.h MySerialServer.cpp MySerialServer.h
            ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h
            Solver.h CacheManager.cpp CacheManager.h
            FileCacheManager.cpp FileCacheManager.h StringReverser.cpp
            StringReverser.h ISearcher.h ISearchable.h)
