//
// Created by t on 1/13/19.
//

#include "MyClientHandler.h"
#include <cstring>
#include <unistd.h>
#include <vector>
#include "Utils.h"
#include <algorithm>
#include <iostream>

#define BUFFER_LENGTH 512
using namespace std;

//talk with a client. client write lines format: num,num,num,num\n, then row,col\n row,col\n, end\n.
//then client handler return the solution: values {Up, Down, Left, Right} with ',' between them.
void MyClientHandler::handleClient(int socket) {
    cout << "start jandle client" << endl;
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
    //we don't know when the end is, so in each iteration move the data from client
    //between the strings so in the end everything will be in it's place.
    vector<string> matrixLines;
    string coordinate2(inputBuffer);
    string coordinate1;
    string partOfMatrix;
    //end of talking if client sent "end"
    while (strcmp(inputBuffer, "end") != 0) {
        //push the decided-to-be part of matrix to the vector
        if(!partOfMatrix.empty()) {
            matrixLines.push_back(partOfMatrix);
        }
        //jungle the strings
        coordinate1 = coordinate2;
        partOfMatrix = coordinate1;
        memset(outputBuffer, 0, BUFFER_LENGTH);
        //read
        memset(inputBuffer, 0, BUFFER_LENGTH);
        n = read(socket, inputBuffer, BUFFER_LENGTH);
        if (n < 0) {
            throw "read failed";
        }
        //} else { //end
        //this->setStopTalking(true);
    }
    //figure out number of ints in the matrix
    long columnsNum = count(matrixLines[0].begin(), matrixLines[0].end(), ',') + 1;
    unsigned long rowNum = matrixLines.size();
    //build the matrix
    int matrix[matrixLines.size()][columnsNum];
    Utils utils;
    vector<string> strInts;
    //for each line formet int,int,int,...
    for (int i = 0; i < matrixLines.size(); i++) {
        //get all the int as string, seperated
        strInts.clear();
        utils.parseByDelimiter(matrixLines[i], ",", &strInts);
        //for every str int put inside the matrix as a real int (not str)
        for (int j = 0; j < strInts.size(); j++) {
            matrix[i][j] = atoi(strInts[j].c_str());
        }
    }


    //ask the cache manager for a saved solution
    if (this->cacheManager->hasSolutionForProblem(inputBuffer)) {//todo
        //set the solution to the buffer
        solutionStr = this->cacheManager->getSolutionForProblem(inputBuffer);
        strcpy(outputBuffer, solutionStr.c_str());
    } else { //if there is none, send for the solver
        //todo make a searchable matrix

        //send for the solver (which is a searcher)
        solutionStr = this->solver->solve(inputBuffer);
        strcpy(outputBuffer, solutionStr.c_str());
    }
    //Send solution to the server
    n = write(socket, outputBuffer, strlen(outputBuffer));
    if (n < 0) {
        throw "write to socket failed";
    }
}//handle client

/*/true when should stop talking, false otherwise
bool MyTestClientHandler::getStopTalking() {
    return this->stopTalking;
}

void MyTestClientHandler::setStopTalking(bool flag) {
    this->stopTalking = flag;
}
*/

MyClientHandler::MyClientHandler(Solver<string, string> *solver, CacheManager<string, string> *cacheManager) {
    this->solver = solver;
    this->cacheManager = cacheManager;
}