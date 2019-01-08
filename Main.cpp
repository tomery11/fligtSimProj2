//
// Created by t on 1/8/19.
//

#include "Main.h"
#include "Server.h"
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "Solver.h"
#include "StringReverser.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>

using namespace std;

//template class CacheManager<string,string>;
//template class FileCacheManager<string,string>;

//int boot::Main::main(int argc, char *argv[]) {
int Main::main(int argc, char *argv[]) {
    //create a server: MySerialServer
    Server *myServer = new MySerialServer();

    //create a cache manager
    //CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
    FileCacheManager<string, string> fcm;
    CacheManager<string,string> *cacheManager = &fcm;

    //create solver
    Solver<string, string> *solver = new StringReverser();

    //create client handler
    ClientHandler *clientHandler = new MyTestClientHandler(solver, cacheManager);
    myServer->open(atoi(argv[1]), clientHandler);

    //delete
    delete myServer;
    myServer = nullptr;
    delete cacheManager;
    cacheManager = nullptr;
    delete solver;
    solver = nullptr;
    delete clientHandler;
    clientHandler = nullptr;
    return 0;
}
