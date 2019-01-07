//
// Created by t on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_SOLVER_H
#define FLIGTSIMPROJ2_SOLVER_H

template<class Problem, class Solution> class Solver {
public:
    virtual Solution solve() = 0;
};
#endif //FLIGTSIMPROJ2_SOLVER_H
