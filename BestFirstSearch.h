//
// Created by tomer on 1/16/19.
//

#ifndef FLIGTSIMPROJ2_BESTFIRSTSEARCH_H
#define FLIGTSIMPROJ2_BESTFIRSTSEARCH_H

#include "PQueueSearcher.h"
#include "State.h"
#include "CompareState.h"

template <class T>
class BestFirstSearch : public PQueueSearcher<T> {
public:
    double getStatePriority(State<T>* curr_state);
};

template<class T>
double BestFirstSearch<T>::getStatePriority(State<T> *curr_state) {
    return curr_state->getWeight();
}


#endif //FLIGTSIMPROJ2_BESTFIRSTSEARCH_H
