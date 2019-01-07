cmake_minimum_required(VERSION 3.13)
project(fligtSimProj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(fligtSimProj2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.cpp CacheManager.h FileCacheManager.cpp FileCacheManager.h)