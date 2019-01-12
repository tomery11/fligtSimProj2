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
#include <iostream>
#include <unistd.h>

using namespace std;

//template class CacheManager<string,string>;
//template class FileCacheManager<string,string>;

//int boot::Main::main(int argc, char *argv[]) {
int Main::main(int argc, char *argv[]) {//todo no new
    try {
        cout << "Main" << endl;
        //create a server: MySerialServer
        MySerialServer server;
        Server *myServer = &server;

        cout << "Main after server" << endl;
        //create a cache manager
        FileCacheManager fcm;
        CacheManager<string,string> *cacheManager = &fcm;
        cout << "Main after cache" << endl;
        //create solver
        StringReverser stringRev;
        Solver<string, string> *solver = &stringRev;

        //create client handler
        MyTestClientHandler testClient(solver, cacheManager);
        ClientHandler *clientHandler = &testClient;
        int port = atoi(argv[1]);
        cout << "port: " << port << endl;
        myServer->open(port, clientHandler);
        sleep(1);
        myServer->stop();
        return 0;
    } catch (const char *exception) {
        printf("%s",exception);
    }
}
