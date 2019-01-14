//
// Created by t on 1/7/19.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <iostream>
#include "FileCacheManager.h"
#include "Utils.h"
#define NO_FILE_ERR 2

using namespace std;

bool FileCacheManager::hasSolutionForProblem(string problem) {
    if (this->problemsSolutions.find(problem) == this->problemsSolutions.end()) {
        return false;
    }
    return true;
}

//get the saved solution for a given problem. if there is none, return null.
string FileCacheManager::getSolutionForProblem(string problem) {
    if (!hasSolutionForProblem(problem)) {
        return nullptr;
    }
    //if has solution, return it
    auto it = this->problemsSolutions.find(problem);
    return it->second;
}

//put a problem solution pair to the map
void FileCacheManager::save(string problem, string solution) {
    this->problemsSolutions.insert(pair<string, string>(problem, solution));
}

//save to file. format: problem$solution$problem$solution$...

void FileCacheManager::saveAllToDisk() {
    //open the file
    fstream file(this->file);
    string pair;
    //if failed
    if (file.fail()) {
        //if no such file or directory, create the file
        if (errno == NO_FILE_ERR) {
            file = fstream(this->file, fstream::out);
            file.close();
            file.open(this->file);
        }
    }
    //if open
    if (file.is_open()) {
        //go over the map and put in file, with "$" as delimiter.
        for(auto it : this->problemsSolutions){
            file << it.first << "$" << it.second << "$";//todo not only string
            //cout<<' '<<*it<<endl;
        }
    }
}

void FileCacheManager::getAllFromDisk() {
    //open the file
    fstream file(this->file, fstream::in);
    stringstream buffer;
    vector<string> inputVec;
    //if failed
    if (file.fail()) {
        //if no such file or directory, no need to upload; return
        if (errno == NO_FILE_ERR) {
            return;
        } //else, other error so throw an exception
        throw "bad file";
    }
    //if open, get all the problems and solutions to the map
    //format: problem$solution$problem$solution$...
    if (file.is_open()) {
        //get the file contents as a single string
        buffer << file.rdbuf();
        Utils utils;
        utils.parseByDelimiter(buffer.str(), "$", &inputVec);
        file.close();
    }
    //put the problems and solutions from file to the map
    for(auto it=inputVec.begin(); it!=inputVec.end(); ++it){
        //put in map. assume parity of inputVec length
        this->problemsSolutions.insert(pair<string,string>(*it, *(++it)));//todo not only string
        //cout<<' '<<*it<<endl;
    }
}

FileCacheManager::~FileCacheManager() {
    //save the map to disk
    this->saveAllToDisk();
}

FileCacheManager::FileCacheManager() {
    cout << "file cache manager constructor" << endl;
    //get all problems and solutions from file
    this->getAllFromDisk();
}
