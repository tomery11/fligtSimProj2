//
// Created by t on 1/7/19.
//

#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <netinet/in.h>
#include <pthread.h>
#include "MySerialServer.h"


//run in the thread. talk with clients until get a stop sign.
//talk serially: continue talking to one client to the end before talk with next client.
void* serverThreadFunc(void *serverData) {
    //todo timeout in writing to the client
    //serverData is of type ServerData
    struct ServerData *serverData1;
    serverData1 = (struct ServerData *) serverData;

    //talk with a client until get a stop sign
    while (!serverData1->clientHandler->getStopTalking()) {
        int l = 0;
        l = listen(serverData1->socketDescriptor, 5);
        if (l < 0) {
            throw "server listen failed";
        }

        //accept
        //cout << "server try to accept" << endl;
        int newSocket = accept(serverData1->socketDescriptor, (struct sockaddr *) &serverData1->address,
                (socklen_t *) &serverData1->addrlen);
        //int newSocket = accept(serverData1->socketDescriptor,
        //                       (struct sockaddr *) serverData1->address, &serverData1->addrlen);
        if (newSocket < 0) {
            throw "server accept failed";
        }
        //cout << "server accepted" <<endl;

        //handle the client
        serverData1->clientHandler->handleClient(newSocket);//todi give client the input
    }
    //serverData = NULL;
    //return nullptr;
}

//in a loop in a thread listen for clients and handle them using the clientHandler.
void MySerialServer::open(int port, ClientHandler *clientHandler) {

    //open a socket
    char buffer[256 + 1];
    int b;
    int frequency;
    int socketDescriptor;
    int opt = 1;

    //create socket
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == 0) {
        throw "server socket creation failed";
    }
    //allow reuse of address and port
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) {
        throw "set socket option failed";
    }
    //create address structure for bind
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET; //tcp
    address.sin_addr.s_addr = INADDR_ANY; //accept all addresses\clients
    address.sin_port = htons((uint16_t) port);

    //bind socket to port and ip address
    b = bind(socketDescriptor, (struct sockaddr *) &address, sizeof(address));
    if (b < 0) {
        throw "server could not bind";
    }

    //create a thread to talk with each client, one after the other
    pthread_t threadID;
    struct ServerData *serverData = new struct ServerData;
    serverData->port = port;
    serverData->socketDescriptor = socketDescriptor;
    serverData->addrlen = addrlen;
    serverData->address = &address;
    serverData->clientHandler = clientHandler;

    //start the thread
    //int rc = pthread_create(&threadID, NULL, serverThreadFunc, (void *)serverData);
    pthread_create(&threadID, nullptr, serverThreadFunc, (void *)serverData);

}

/*
DataReaderServer::~DataReaderServer() {
    //cout << "server socket closed" << endl;
    close(this->socketDescriptor);
    close(this->newSocket);
}*/


void MySerialServer::stop() {

}
