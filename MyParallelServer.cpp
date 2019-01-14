//
// Created by t on 1/14/19.
//

#include "MyParallelServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>
using namespace std;

//run in a thread, talk to clients.
void *clientTalkThreadFunc(void *serverData) {
    try {
        //serverData is of type ServerData
        struct ServerData *serverData1;
        serverData1 = (struct ServerData *) serverData;

        //talk to the client
        serverData1->clientHandler->handleClient(serverData1->newSocket);//todo give client the input

    } catch (const char *exception) {
        printf("%s",exception);
    }
}

//wait for clients. for each client create a thread to talk with.
void* parallelServerThreadFunc(void *serverData) {
    int newSocket = 0;
    vector<pthread_t> *threads;
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
            serverData1->newSocket = newSocket;
            //create a thread for talking with the client

            threads->push_back(nullptr);
            int rc = pthread_create(&this->threadID, nullptr, parallelServerThreadFunc, (void *)serverData);
            if (rc) {
                throw "unable to create thread";
            }
            //cout << "server accepted" <<endl;
            //handle the client

        }
        //end all the other threads
        stopThreads(threads);
        close(newSocket);
        //sleep(1);
        cout << "end of thread" << endl;
        //serverData = NULL;
        //return nullptr;
    } catch (const char *exception) {
        printf("%s",exception);
    }
}
//run in the thread. talk with clients until get a stop sign.
//talk serially: continue talking to one client to the end before talk with next client.
void* 1parallelServerThreadFunc(void *serverData) {
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

//listen for clients. wait infinitely for the first client' one second for second and up.
//in timeout stop gracefully.
void MyParallelServer::open(int port, ClientHandler *clientHandler) {

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
    //loop for parallel  talking with clients

    //create a thread to talk with each client, one after the other
    //pthread_t threadID;
    this->serverData = new struct ServerData;
    serverData->port = port;
    serverData->socketDescriptor = socketDescriptor;
    serverData->clientHandler = clientHandler;
    serverData->setStop = &this->setStop;

    //start the thread
    //int rc = pthread_create(&threadID, NULL, serverThreadFunc, (void *)serverData);
    int rc = pthread_create(&this->threadID, nullptr, parallelServerThreadFunc, (void *)serverData);
    if (rc) {
        throw "unable to create thread";
    }

    //gracefull stop
    this->stop();
}

/*
DataReaderServer::~DataReaderServer() {
    //cout << "server socket closed" << endl;
    close(this->socketDescriptor);
    close(this->newSocket);
}*/

//stop the server and all the threads
void MyParallelServer::stop() {
    cout << "stop" << endl;
    //stop server
    this->setStop = true;
    void *res;
    //loop to close all the threads
    int s;
    for (auto it : this->threads) {
        s = pthread_join(it, &res);
        cout << "back from join" << endl;
        if (s != 0) {
            throw "error in join thread";
        }
        //free memory allocated by thread
        //free(res);
    }
    cout << "after free memory thread" << endl;
    close(this->socketDescriptor);
    delete this->serverData;
    this->serverData = nullptr;
    cout << "end of server" << endl;
}


//stop the threads
void stopThreads(vector<pthread_t> *threads) {
    cout << "stop threads" << endl;
    void *res;
    //loop to close all the threads
    int s;
    for (auto it : *threads) {
        s = pthread_join(it, &res);
        cout << "back from join" << endl;
        if (s != 0) {
            throw "error in join thread";
        }
        //free memory allocated by thread
        //free(res);
    }
    cout << "after free all but one thread" << endl;
}