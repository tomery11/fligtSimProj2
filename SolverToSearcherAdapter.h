//
// Created by t on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H
#define FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H

#include "Solver.h"
#include "ISearcher.h"
#include "ISearchable.h"

template<class Problem>
class SolverToSearcherAdapter : public Solver<Problem, string> {
    ISearcher<Problem> *searcher;
    ISearchable<Problem> *searchable;
public:
    explicit SolverToSearcherAdapter(ISearcher<Problem> *searcher);
    SolverToSearcherAdapter();
    //void setSearchable(ISearchable<Problem> *searchable);
    virtual string solve(Problem problem);
    virtual string ProblemToString(Problem problem);
};

template<class Problem>
SolverToSearcherAdapter<Problem>::SolverToSearcherAdapter(ISearcher<Problem> *searcher) {
    this->searcher = searcher;
    this->searchable = searchable;
}

template<class Problem>
string SolverToSearcherAdapter<Problem>::solve(Problem problem) {
    //todo
    return this->searcher->search(*this->searchable);
    //virtual State<T>* search(ISearchable<T>* searchable)=0;

}

template<class Problem>
string SolverToSearcherAdapter<Problem>::ProblemToString(Problem problem) {
    return this->searchable->getStrRepresentation();
}

/*
template<class Problem, class Solution>
void SolverToSearcherAdapter<Problem, Solution>::setSearchable(ISearchable<Problem> *searchable) {
    this->searchable = searchable;
}

template<class Problem, class Solution>
void SolverToSearcherAdapter<Problem, Solution>::setSearcher(ISearcher *searcher) {
    this->searcher = searcher;
}*/

template<class Problem>
SolverToSearcherAdapter<Problem>::SolverToSearcherAdapter() {}

#endif //FLIGTSIMPROJ2_SOLVERTOSEARCHERADAPTER_H
