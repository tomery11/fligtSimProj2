//
// Created by t on 1/15/19.
//

#ifndef FLIGTSIMPROJ2_CLIENT_H
#define FLIGTSIMPROJ2_CLIENT_H

#include <string>

using namespace std;

class Client {
public:
    virtual void open(string ipAddress, int port, vector<string> *message) = 0;
};

#endif //FLIGTSIMPROJ2_CLIENT_H
