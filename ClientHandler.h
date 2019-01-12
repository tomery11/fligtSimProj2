//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_CLIENTHANDLER_H
#define FLIGTSIMPROJ2_CLIENTHANDLER_H

//handle a single client
class ClientHandler {
protected:
    //bool stopTalking;
public:
    virtual void handleClient(int socket) = 0;
    //virtual void setStopTalking(bool flag) = 0;
    //virtual bool getStopTalking() = 0;
};

#endif //FLIGTSIMPROJ2_CLIENTHANDLER_H
