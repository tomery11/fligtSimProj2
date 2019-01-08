//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_FILECACHEMANAGER_H
#define FLIGTSIMPROJ2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
using namespace std;

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
    unordered_map<Problem, Solution> problemsSolutions;
    string file = "problemsSolutions.txt";
    void saveAllToDisk();
    void getAllFromDisk();
public:
    //virtual bool hasSolutionForProblem(Problem problem) = 0;
    //virtual Solution getSolutionForProblem(Problem problem) = 0;
    //virtual void save(Problem problem, Solution solution) = 0;

    FileCacheManager();
    virtual bool hasSolutionForProblem(Problem problem);
    virtual Solution getSolutionForProblem(Problem problem);
    virtual void save(Problem problem, Solution solution);
    ~FileCacheManager();
};

#endif //FLIGTSIMPROJ2_FILECACHEMANAGER_H
