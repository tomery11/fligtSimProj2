//
// Created by t on 1/13/19.
//

#ifndef FLIGTSIMPROJ2_MYCLIENTHANDLER_H
#define FLIGTSIMPROJ2_MYCLIENTHANDLER_H
#include "ClientHandler.h"
#include "Solver.h"
#include <string>
#include "CacheManager.h"
using namespace std;

class MyClientHandler : public ClientHandler {
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;//todo change classes
public:
    MyClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager);
    //todo get input stream and output stream in handleClient
    virtual void handleClient(int socket);
    //virtual void setStopTalking(bool flag);
    //virtual bool getStopTalking();
};



#endif //FLIGTSIMPROJ2_MYCLIENTHANDLER_H
