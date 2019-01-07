//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_MYSERIALSERVER_H
#define FLIGTSIMPROJ2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;

class MySerialServer : Server {
    virtual void open(int port);
    virtual void stop();
};


#endif //FLIGTSIMPROJ2_MYSERIALSERVER_H
