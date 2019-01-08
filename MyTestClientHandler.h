//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H
#define FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include <string>
#include "CacheManager.h"
using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;
public:
    MyTestClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager);
    //todo get input stream and output stream in handleClient
    virtual void handleClient(int socket);
    virtual void setStopTalking(bool flag);
    virtual bool getStopTalking();
};


#endif //FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H
