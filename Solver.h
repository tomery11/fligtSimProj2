//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_SOLVER_H
#define FLIGTSIMPROJ2_SOLVER_H

#include <string>

using namespace std;

template<class Problem, class Solution> class Solver {
public:
    virtual Solution solve(Problem problem) = 0;
    virtual string ProblemToString(Problem problem) = 0;
};
#endif //FLIGTSIMPROJ2_SOLVER_H
