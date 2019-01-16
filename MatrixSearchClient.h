//
// Created by t on 1/15/19.
//

#ifndef FLIGTSIMPROJ2_MATRIXSEARCHCLIENT_H
#define FLIGTSIMPROJ2_MATRIXSEARCHCLIENT_H

#include <pthread.h>
#include "Client.h"
//#include "Matrix.h"

//struct for the thread
struct Data {
    string ipAddress;
    int port;
    string messsage;
};

void *threadFunc(void *data);

class MatrixSearchClient : public Client {
    Data *data;
    pthread_t threadID;
public:
    virtual void open(string ipAddress, int port, string messsage);
    ~MatrixSearchClient();
};




/*
    pthread_t threadID;
    //vector<pthread_t> threads;
    bool setStop = false;
    int socketDescriptor;
    struct ServerData *serverData;
    void stopThreads(vector<pthread_t> *threads, vector<TalkingData*> *talkingStructs);
    int listenAccept(int time, struct ServerData *serverData1);
    virtual void stop();
*/



#endif //FLIGTSIMPROJ2_MATRIXSEARCHCLIENT_H
