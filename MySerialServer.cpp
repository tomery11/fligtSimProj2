//
// Created by t on 1/7/19.
//

#include <sys/socket.h>
//#include <bits/socket_type.h>
#include <netinet/in.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "MySerialServer.h"
using namespace std;

//run in the thread. talk with clients until get a stop sign.
//talk serially: continue talking to one client to the end before talk with next client.
void* serverThreadFunc(void *serverData) {
    int newSocket = 0;
    try {
        //todo timeout in writing to the client
        //serverData is of type ServerData
        struct ServerData *serverData1;
        serverData1 = (struct ServerData *) serverData;

        //talk with client after client serially
        //cout << *serverData1->setStop << endl;
        while (!(*serverData1->setStop)) {
            //talk with a single client until get a stop sign
            int l = 0;
            l = listen(serverData1->socketDescriptor, 5);
            if (l < 0) {
                throw "server listen failed";
            }

            struct sockaddr_in client;
            socklen_t clilen = sizeof(client);

            timeval timeout;
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;

            setsockopt(serverData1->socketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

            //accept
            //cout << "server try to accept" << endl;
            newSocket = accept(serverData1->socketDescriptor, (struct sockaddr*)&client, &clilen);
            if (newSocket < 0)	{
                //in timeout end the thread
                if (errno == EWOULDBLOCK)	{
                    cout << "timeout!" << endl;
                    break;
                } else { //in other error throw an exception
                    throw "accept failed";
                }
            }
            //cout << "server accepted" <<endl;
            //handle the client
            serverData1->clientHandler->handleClient(newSocket);//todo give client the input
        }
        close(newSocket);
        //sleep(1);
        cout << "end of thread" << endl;
    //serverData = NULL;
    //return nullptr;
    } catch (const char *exception) {
        printf("%s",exception);
    }
}

//in a loop in a thread listen for clients and handle them using the clientHandler.
void MySerialServer::open(int port, ClientHandler *clientHandler) {

    cout << "my serial server open" << endl;
    //open a socket
    char buffer[256 + 1];
    int b;
    int frequency;
    //int socketDescriptor;
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
    //pthread_t threadID;
    this->serverData = new struct ServerData;
    serverData->port = port;
    serverData->socketDescriptor = socketDescriptor;
    serverData->clientHandler = clientHandler;
    serverData->setStop = &this->setStop;

    //start the thread
    //int rc = pthread_create(&threadID, NULL, serverThreadFunc, (void *)serverData);
    int rc = pthread_create(&this->threadID, nullptr, serverThreadFunc, (void *)serverData);
    if (rc) {
        throw "unable to create thread";
    }
}

/*
DataReaderServer::~DataReaderServer() {
    //cout << "server socket closed" << endl;
    close(this->socketDescriptor);
    close(this->newSocket);
}*/

//stop the server
void MySerialServer::stop() {
    cout << "stop" << endl;
    //stop server
    this->setStop = true;
    void *res;
    int s = pthread_join(this->threadID, &res);
    cout << "back from join" << endl;
    if(s != 0) {
        throw "error in join thread";
    }
    //free memory allocated by thread
    //free(res);
    cout << "after free memory thread" << endl;
    close(this->socketDescriptor);
    delete this->serverData;
    this->serverData = nullptr;
    cout << "end of server" << endl;
}
