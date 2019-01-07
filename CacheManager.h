//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_CACHEMANAGER_H
#define FLIGTSIMPROJ2_CACHEMANAGER_H


template<class Problem, class Solution> class CacheManager {
public:
    virtual bool hasSolutionForProblem(Problem problem) = 0;
    virtual Solution getSolutionForProblem(Problem problem) = 0;
    virtual void save(Problem problem, Solution solution) = 0;
};


#endif //FLIGTSIMPROJ2_CACHEMANAGER_H
