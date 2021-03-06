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
    cout << "start jangle client" << endl;
    //get a problem from client
    char inputBuffer[BUFFER_LENGTH + 1];
    char outputBuffer[BUFFER_LENGTH + 1];
    ssize_t n;
    string solutionStr;
    //read
    //memset(inputBuffer, 0, BUFFER_LENGTH);
    //n = read(socket, inputBuffer, BUFFER_LENGTH);
    //printf("recieved:  %s\n",inputBuffer);
    //if (n < 0) {
    //    throw "read failed";
    //}
    //we don't know when the end is, so in each iteration move the data from client
    //between the strings so in the end everything will be in it's place.
    vector<string> matrixLines;
    string end;
    string coordinate2;
    string coordinate1;
    string partOfMatrix;
    //end of talking if client sent "end"
    while (strcmp(end.c_str(), "end") != 0) {

        memset(outputBuffer, 0, BUFFER_LENGTH);
        //read
        memset(inputBuffer, 0, BUFFER_LENGTH);
        n = read(socket, inputBuffer, BUFFER_LENGTH);
        if (n < 0) {
            throw "read failed";
        }
        printf("recieved:  %s\n",inputBuffer);

        //jungle the strings
        partOfMatrix = coordinate1;
        coordinate1 = coordinate2;
        coordinate2 = end;
        end = inputBuffer;
        cout << "end: " << end << " cord1: " << coordinate1 << " cor2: " << coordinate2 << endl;
        cout << "part of matrix: " << partOfMatrix << endl;
        //push the decided-to-be part of matrix to the vector
        if(!partOfMatrix.empty()) {
            matrixLines.push_back(partOfMatrix);
        }

        //} else { //end
        //this->setStopTalking(true);
    }
    for (auto it : matrixLines) {
        cout << it << endl;
    }
    //figure out number of ints in the matrix
    long columnsNum = count(matrixLines[0].begin(), matrixLines[0].end(), ',') + 1;
    unsigned long rowNum = matrixLines.size();
    //build the matrix
    int matrix[matrixLines.size()][columnsNum];
    Utils utils;
    vector<string> strInts;
    //for each line formet int,int,int,...
    int i, j;
    for (i = 0; i < matrixLines.size(); i++) {
        //get all the int as string, seperated
        strInts.clear();
        utils.parseByDelimiter(matrixLines[i], ",", &strInts);
        //for every str int put inside the matrix as a real int (not str)
        for (j = 0; j < strInts.size(); j++) {
            matrix[i][j] = atoi(strInts[j].c_str());
        }
    }
    //get the start point
    strInts.clear();
    utils.parseByDelimiter(coordinate1, ",", &strInts);

    //get the end point
    utils.parseByDelimiter(coordinate2, ",", &strInts);

    Matrix matrix1((int**)matrix, i, j, atoi(strInts[0].c_str()), atoi(strInts[2].c_str()),
            atoi(strInts[1].c_str()), atoi(strInts[3].c_str()));
    //Matrix(int **matrix, int row, int col, int i_start, int j_start, int i_goal, int j_goal);

    cout << "matrix1: " << &matrix1 << endl;
    //ask the cache manager for a saved solution
    if (this->cacheManager->hasSolutionForProblem(&matrix1)) {//todo
        //set the solution to the buffer
        solutionStr = this->cacheManager->getSolutionForProblem(&matrix1);
    } else { //if there is none, send for the solver
        //todo make a searchable matrix
        //send for the solver (which is a searcher)
        solutionStr = this->solver->solve(matrix1);
        //put in cache manager
        this->cacheManager->save(matrix1, solutionStr);
    }
    strcpy(outputBuffer, solutionStr.c_str());
    //Send solution to the server
    cout << "solution: " << solutionStr << endl;
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

MyClientHandler::MyClientHandler(Solver<Matrix, string> *solver, CacheManager<Matrix, string> *cacheManager) {
    this->solver = solver;
    this->cacheManager = cacheManager;
}