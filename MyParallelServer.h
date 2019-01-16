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

//struct for the little client talking threads
struct TalkingData {
    int newSocket;
    ClientHandler *clientHandler;
};

void *clientTalkThreadFunc(void *talkingData);
void* parallelServerThreadFunc(void *serverData);

class MyParallelServer : public Server {
    pthread_t threadID;
    //vector<pthread_t> threads;
    bool setStop = false;
    bool doneListening = false;
    int socketDescriptor;
    struct ServerData *serverData;
    int counter = 0;
public:
    void stopThreads(vector<pthread_t> *threads, vector<TalkingData*> *talkingStructs);
    int listenAccept(int time, struct ServerData *serverData1);
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    void setDoneListening(bool done);
    bool getDoneListening();

};

//the struct the server thread will get
struct ServerData {
    MyParallelServer *parallelServer;
    int port;
    int socketDescriptor;
    ClientHandler *clientHandler;
    bool *setStop;
    int newSocket;
};



#endif //FLIGTSIMPROJ2_MYPARALLELSERVER_H
