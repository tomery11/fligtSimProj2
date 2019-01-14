//
// Created by t on 1/14/19.
//

#ifndef FLIGTSIMPROJ2_MYPARALLELSERVER_H
#define FLIGTSIMPROJ2_MYPARALLELSERVER_H

#include "Server.h"
#include <pthread.h>
#include <vector>
//#include <thread_db.h>
using namespace std;
using namespace server_side;

//the struct the server thread will get
struct ServerData {
    int port;
    int socketDescriptor;
    ClientHandler *clientHandler;
    bool *setStop;
    int newSocket;
};

class MyParallelServer : public Server {
        pthread_t threadID;
        vector<pthread_t> threads;
        bool setStop = false;
        int socketDescriptor;
        struct ServerData *serverData;
    public:
        virtual void open(int port, ClientHandler *clientHandler);
        virtual void stop();
};


#endif //FLIGTSIMPROJ2_MYPARALLELSERVER_H
