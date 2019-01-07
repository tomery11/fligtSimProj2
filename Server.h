//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_SERVER_H
#define FLIGTSIMPROJ2_SERVER_H

namespace server_side {
    //interface for the server
    class Server {
    public:
        virtual void open(int port) = 0;
        virtual void stop() = 0;
    };
}

#endif //FLIGTSIMPROJ2_SERVER_H
