//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_MYSERIALSERVER_H
#define FLIGTSIMPROJ2_MYSERIALSERVER_H

#include "Server.h"
#include <pthread.h>


using namespace server_side;

//the struct the server thread will get
struct ServerSData {
    int port;
    int socketDescriptor;
    ClientHandler *clientHandler;
    bool *setStop;
};

class MySerialServer : public Server {
    //int threadIDNum;
    pthread_t threadID;
    bool setStop = false;
    int socketDescriptor;
    struct ServerSData *serverData;
public:
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
};


#endif //FLIGTSIMPROJ2_MYSERIALSERVER_H
