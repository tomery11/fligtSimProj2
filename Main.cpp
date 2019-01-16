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
#include <vector>
#include "MatrixSearchClient.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"
#include "SolverToSearcherAdapter.h"
#include "Matrix.h"
using namespace std;

//template class CacheManager<string,string>;
//template class FileCacheManager<string,string>;

//int boot::Main::main(int argc, char *argv[]) {
int Main::main(int argc, char *argv[]) {//todo no new
    try {
        int port = atoi(argv[1]);
        cout << "port: " << port << endl;
        //create a server: MySerialServer
        MyParallelServer server;
        Server *myServer = &server;

        cout << "Main after server" << endl;
        //create a cache manager
        FileCacheManager fcm;
        CacheManager<string,string> *cacheManager = &fcm;
        cout << "Main after cache" << endl;
        //create solver
        //StringReverser stringRev;
        //Solver<string, string> *solver = &stringRev;

        SolverToSearcherAdapter<Matrix, string> solver1 = SolverToSearcherAdapter<Matrix, string>();
        Solver<Matrix, string> *solver = &solver1;

        //SolverToSearcherAdapter(ISearcher *searcher)

        //create client handler
        MyClientHandler client(solver, cacheManager);
        ClientHandler *clientHandler = &client;


        //get message
        string arr[] = {
                "4, 2, 9, 5, 7, 0, 7, 6, 3, 7, 8\n",
                "4, 0,10, 8, 1, 0, 5, 5, 7, 8, 4\n",
                "4, 5, 2, 8, 1, 1, 9, 3, 3, 0, 7\n",
                "3, 3, 6, 2, 8, 9, 6, 8, 3, 5, 7\n",
                "0, 3, 7, 3, 7,10, 4, 8, 9, 1, 1\n",
                "7, 3, 2, 3, 5, 0, 2, 1, 6, 0, 9\n",
                "6, 9, 8, 1,10, 3, 9, 8, 3, 4, 8\n",
                "10, 8, 0, 2, 3, 8, 0,10,10, 2, 7\n",
                "5, 7, 0, 8, 8, 8, 0, 3, 4, 5, 1\n",
                "7, 7, 5,10, 8,10, 1, 6, 9, 9, 1\n"
                "5,10, 1,10, 7, 7, 3,10, 8, 0, 6\n",
                "0,0\n",
                "10,10\n"};
        vector<string> message(arr, arr + (sizeof(arr)/sizeof(arr[0])));
        myServer->open(port, clientHandler);
        //start client
        MatrixSearchClient searcherMatrix;
        searcherMatrix.open("127.0.0.1" ,port, &message);
        sleep(1);
        myServer->stop();
        return 0;
    } catch (const char *exception) {
        printf("%s",exception);
    }
}
