//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_FILECACHEMANAGER_H
#define FLIGTSIMPROJ2_FILECACHEMANAGER_H

#include "CacheManager.h"

template<class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
public:
    virtual bool hasSolutionForProblem(Problem problem);
    virtual Solution getSolutionForProblem(Problem problem);
    virtual void save(Problem problem, Solution solution);
};


#endif //FLIGTSIMPROJ2_FILECACHEMANAGER_H
