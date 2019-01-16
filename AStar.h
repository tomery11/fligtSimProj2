//
// Created by tomer on 1/16/19.
//

#ifndef FLIGTSIMPROJ2_ASTAR_H
#define FLIGTSIMPROJ2_ASTAR_H

#include "PQueueSearcher.h"
#include "State.h"
#include "CompareState.h"
#include "ISearcher.h"
#include "Searcher.h"
#include <limits>
template <class T>
class AStar: public PQueueSearcher<T> {
public:
    double getStatePriority(State<T>* curr_state);


};

template<class T>
double AStar<T>::getStatePriority(State<T> *curr_state) {
    set<State<T>*> extension = Searcher<T>::curr_Searchable->getAllPossibleStates();

    double upper_bound = numeric_limits<double>::max();

    for(auto x : extension){
        double tmp_weight=x->getWeight();
        if(tmp_weight<upper_bound){
            upper_bound=tmp_weight;
        }
        delete x;
    }
    if(numeric_limits<double>::max()==upper_bound){
        upper_bound=curr_state->getWeight();
    }

    return upper_bound;

}


#endif //FLIGTSIMPROJ2_ASTAR_H
