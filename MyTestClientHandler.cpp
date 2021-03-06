//
// Created by t on 1/7/19.
//

#include <cstring>
#include <unistd.h>
#include "MyTestClientHandler.h"
#define BUFFER_LENGTH 512

//talk with a client. client write first, client handler send a replay
//client send string problem and this return string solution until client send "end"
void MyTestClientHandler::handleClient(int socket) {
    //get a problem from client
    char inputBuffer[BUFFER_LENGTH + 1];
    char outputBuffer[BUFFER_LENGTH + 1];
    ssize_t n;
    string solutionStr;
    //read
    memset(inputBuffer, 0, BUFFER_LENGTH);
    n = read(socket, inputBuffer, BUFFER_LENGTH);
    if (n < 0) {
        throw "read failed";
    }
    //end of talking if client sent "end"
    while (strcmp(inputBuffer, "end") != 0) {
        memset(outputBuffer, 0, BUFFER_LENGTH);
        //ask the cache manager for a saved solution
        string strbuf(inputBuffer);
        if (this->cacheManager->hasSolutionForProblem(&strbuf)) {
            //set the solution to the buffer
            solutionStr = this->cacheManager->getSolutionForProblem(&strbuf);
            strcpy(outputBuffer, solutionStr.c_str());
        } else { //if there is none, send for the solver
            solutionStr = this->solver->solve(inputBuffer);
            strcpy(outputBuffer, solutionStr.c_str());
        }
        //Send solution to the server
        n = write(socket, outputBuffer, strlen(outputBuffer));
        if (n < 0) {
            throw "write to socket failed";
        }
        //read
        memset(inputBuffer, 0, BUFFER_LENGTH);
        n = read(socket, inputBuffer, BUFFER_LENGTH);
        if (n < 0) {
            throw "read failed";
        }
    //} else { //end
        //this->setStopTalking(true);
    }
}

/*/true when should stop talking, false otherwise
bool MyTestClientHandler::getStopTalking() {
    return this->stopTalking;
}

void MyTestClientHandler::setStopTalking(bool flag) {
    this->stopTalking = flag;
}
*/

MyTestClientHandler::MyTestClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager) {
    this->solver = solver;
    this->cacheManager = cacheManager;
}
