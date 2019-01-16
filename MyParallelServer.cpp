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



//little server threads: run in a thread, talk to clients.
void *clientTalkThreadFunc(void *talkingData) {
    try {
        cout << "little thread" << endl;
        //TalkingData is of type TalkingData
        TalkingData *talkingData1;
        talkingData1 = (TalkingData *) talkingData;
        //talk to the client
        talkingData1->clientHandler->handleClient(talkingData1->newSocket);
        close(talkingData1->newSocket);
    } catch (const char *exception) {
        printf("%s",exception);
    }
}

//listen and accept, give timeout of time
int MyParallelServer::listenAccept(int time, struct ServerData *serverData1) {
    int l = 0;
    l = listen(serverData1->socketDescriptor, 5);
    if (l < 0) {
        throw "server listen failed";
    }

    sockaddr_in client;
    socklen_t clilen = sizeof(client);

    timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    cout << "set time wait: " << time << endl;

    setsockopt(serverData1->socketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    //accept
    //cout << "server try to accept" << endl;
    int newSocket = accept(serverData1->socketDescriptor, (struct sockaddr*)&client, &clilen);
    if (newSocket < 0)	{
        //in timeout end all the threads
        if (errno == EWOULDBLOCK)	{
            cout << "timeout!" << endl;
            serverData1->parallelServer->setDoneListening(true);
        } else { //in other error throw an exception
            throw "accept failed";
        }
    }
    return newSocket;
}

//main server thread: wait for clients. for each client create a thread to talk with.
void* parallelServerThreadFunc(void *serverData) {
    int newSocket = 0;
    vector<pthread_t> threads;
    pthread_t threadID;
    vector<TalkingData*> talkingStructs;
    try {
        //todo timeout in writing to the client
        //serverData is of type ServerData1
        struct ServerData *serverData1;
        serverData1 = (struct ServerData *) serverData;

        //first client: listen for 10 seconds. set the new socket number for the thread
        newSocket = serverData1->parallelServer->listenAccept(10, serverData1);
        auto *talking1 = new TalkingData;
        talkingStructs.push_back(talking1);
        talking1->newSocket = newSocket;
        talking1->clientHandler = serverData1->clientHandler;
        //create a thread to talk with
        int rc = pthread_create(&threadID, nullptr, clientTalkThreadFunc, (void *)&talking1);
        if (rc) {
            throw "unable to create thread";
        }
        threads.push_back(threadID);
        serverData1->parallelServer->setDoneListening(true);//todo delete this
        //talk with the other clients: client after client serially. 1 second max to wait, end if timeout.
        //cout << *serverData1->setStop << endl;
        while (!(serverData1->parallelServer->getDoneListening())) {
            //listen for 1 second. set the new socket number for the thread
            newSocket = serverData1->parallelServer->listenAccept(1, serverData1);
            auto *talking = new TalkingData;
            talkingStructs.push_back(talking);
            talking->newSocket = newSocket;
            talking->clientHandler = serverData1->clientHandler;
            //create a thread for talking with the client
            rc = pthread_create(&threadID, nullptr, parallelServerThreadFunc, (void *)&talking);
            if (rc) {
                throw "unable to create thread";
            }
            threads.push_back(threadID);
        }
        //end all the other threads
        serverData1->parallelServer->stopThreads(&threads, &talkingStructs);
        //end this one, and the whole parallel server
        serverData1->parallelServer->stop();
        //close(newSocket);-no need?
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

    cout << "my parallel server open" << endl;
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
    serverData->parallelServer = this;

    //start the thread
    //int rc = pthread_create(&threadID, NULL, serverThreadFunc, (void *)serverData);
    int rc = pthread_create(&this->threadID, nullptr, parallelServerThreadFunc, (void *)serverData);
    if (rc) {
        throw "unable to create thread";
    }

    //gracefull stop
    //this->stop();
}



//stop the server and all the threads
void MyParallelServer::stop() {
    cout << "stop" << endl;
    //stop server
    this->setStop = true;
    void *res;
    //close the main thread
    int s = pthread_join(threadID, &res);
    cout << "back from join" << endl;
    if (s != 0) {
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


//stop the little threads, clean memory of the big thread
void MyParallelServer::stopThreads(vector<pthread_t> *threads, vector<TalkingData*> *talkingStructs) {
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
    //free memory of the big thread
    for (auto it1 : *talkingStructs) {
        delete(it1);
    }
    cout << "after free all but one thread" << endl;
}

void MyParallelServer::setDoneListening(bool done) {
    this->doneListening = done;
}

bool MyParallelServer::getDoneListening() {
    return this->doneListening;
}
