//
// Created by t on 1/7/19.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include "FileCacheManager.h"
#define NO_FILE_ERR 2

using namespace std;

template<class Problem, class Solution>
bool FileCacheManager<Problem, Solution>::hasSolutionForProblem(Problem problem) {
    if (this->problemsSolutions.find(problem) == this->problemsSolutions.end()) {
        return false;
    }
    return true;
}

//get the saved solution for a given problem. if there is none, return null.
template<class Problem, class Solution>
Solution FileCacheManager<Problem, Solution>::getSolutionForProblem(Problem problem) {
    if (!hasSolutionForProblem(problem)) {
        return nullptr;
    }
    //if has solution, return it
    auto it = this->problemsSolutions.find(problem);
    return it->second;
}

//put a problem solution pair to the map
template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::save(Problem problem, Solution solution) {
    this->problemsSolutions.insert(pair<Problem, Solution>(problem, solution));
}

//save to file. format: problem$solution$problem$solution$...
template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::saveAllToDisk() {
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
            file << it.first << "$" << it.second << "$";
            //cout<<' '<<*it<<endl;
        }
    }
}

//parse by delimiter. input is string to delimit, token and vector for output
void parseByDelimiter(string inputStr, string token, vector<string> *outputVec) {
    //go over the inputStr and parses according to to the token
    std::size_t prev = 0, pos;
    while ((pos = inputStr.find_first_of(token, prev)) != string::npos) {
        if (pos > prev) {
            outputVec->push_back(inputStr.substr(prev, pos - prev));
        }
        prev = pos + 1;
    }
    //add last word
    if (prev < inputStr.length()) {
        outputVec->push_back(inputStr.substr(prev, string::npos));
    }
}

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::getAllFromDisk() {
    //open the file
    fstream file(this->file, fstream::in);
    stringstream buffer;
    vector<string> inputVec;
        //if failed
    if (file.fail()) {
        throw "bad file";
    }
    //if open, get all the problems and solutions to the map
    //format: problem$solution$problem$solution$...
    if (file.is_open()) {
        //get the file contents as a single string
        buffer << file.rdbuf();
        parseByDelimiter(buffer.str(), "$", &inputVec);
        file.close();
    }
    //put the problems and solutions from file to the map
    for(auto it=inputVec.begin(); it!=inputVec.end(); ++it){
        //put in map. assume parity of inputVec length
        this->problemsSolutions.insert(pair<string,string>(*it, *(++it)));
        //cout<<' '<<*it<<endl;
    }
}

template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::~FileCacheManager() {
    //save the map to disk
    this->saveAllToDisk();
}

template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::FileCacheManager() {
    //get all problems and solutions from file
    this->getAllFromDisk();
}

template class CacheManager<string,string>;
template class FileCacheManager<string,string>;