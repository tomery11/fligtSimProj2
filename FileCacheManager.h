//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_FILECACHEMANAGER_H
#define FLIGTSIMPROJ2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
using namespace std;

class FileCacheManager : public CacheManager<string, string> {
    unordered_map<string, string> problemsSolutions;
    string file = "problemsSolutions.txt";
    void saveAllToDisk();
    void getAllFromDisk();
public:
    FileCacheManager();
    virtual bool hasSolutionForProblem(string *problem);
    virtual string getSolutionForProblem(string *problem);
    virtual void save(string problem, string solution);
    ~FileCacheManager();
};

#endif //FLIGTSIMPROJ2_FILECACHEMANAGER_H
