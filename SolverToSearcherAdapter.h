//
// Created by t on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H
#define FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H

#include "Solver.h"
#include "ISearcher.h"
#include "ISearchable.h"

template<class Problem, class Solution>
class SolverToSearcherAdapter : public Solver<Problem, Solution> {
    ISearcher<Problem> *searcher;//todo understand if should use problem or solution here
    ISearchable<Problem> *searchable;
public:
    explicit SolverToSearcherAdapter(ISearcher<Problem> *searcher, ISearchable<Problem> *searchable);
    virtual Solution solve(Problem problem);
    virtual string ProblemToString(Problem problem);
};

template<class Problem, class Solution>
SolverToSearcherAdapter<Problem, Solution>::SolverToSearcherAdapter(ISearcher<Problem> *searcher, ISearchable<Problem> *searchable) {
    this->searcher = searcher;
    this->searchable = searchable;
}

template<class Problem, class Solution>
Solution SolverToSearcherAdapter<Problem, Solution>::solve(Problem problem) {
    this->searcher->search(&this->searchable);
}

//todo function
template<class Problem, class Solution>
string SolverToSearcherAdapter<Problem, Solution>::ProblemToString(Problem problem) {
    return std::__cxx11::string();
}

#endif //FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H
