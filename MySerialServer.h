//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_MYSERIALSERVER_H
#define FLIGTSIMPROJ2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;

//the struct the server thread will get
struct ServerData {
    int port;
    int socketDescriptor;
    int addrlen;
    struct sockaddr_in *address;
    ClientHandler *clientHandler;
};

class MySerialServer : public Server {
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
};


#endif //FLIGTSIMPROJ2_MYSERIALSERVER_H
