//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H
#define FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include <string>
using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver<string, string> solver;
public:
    //todo get input stream and output stream in handleClient
    virtual void handleClient();
};


#endif //FLIGTSIMPROJ2_MYTESTCLIENTHANDLER_H
