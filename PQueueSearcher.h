//
// Created by tomer on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_PQUEUESEARCHER_H
#define FLIGTSIMPROJ2_PQUEUESEARCHER_H

#include "ISearcher.h"
#include "State.h"
#include "Searcher.h"
#include "StatePriority.h"
#include "CompareState.h"
#include "ISearchable.h"
#include <queue>

template <class T>

//for Best First Search
class PQueueSearcher {
private:
    priority_queue<StatePriority<T>*,
            vector<StatePriority<T>*>,
                    PriorityStateCompare<T>> p_queue;

public:
    State<T>* popOpenList();
    void clearAllStates();
    void addToOpenList(State<T>* state);
    bool isOpenEmpty();

    virtual double getStatePriority(State<T>* state)=0;


};

template<class T>
bool PQueueSearcher<T>::isOpenEmpty() {
    if(p_queue.empty())
        return true;
    return false;
}

template<class T>
void PQueueSearcher<T>::clearAllStates() {
    Searcher<T> ::clearAllStates();

    while (!p_queue.empty()){
        StatePriority<T>* state_p = p_queue.top();
        p_queue.pop();

        if(!state_p->getState()->appearInSolution()){
            delete state_p;
        }
    }
}

template<class T>
State<T> *PQueueSearcher<T>::popOpenList() {
    Searcher<T> :: nodesEvaluated++;
    StatePriority<T>* state_p= p_queue.top();
    p_queue.top();
    State<T>* save_state = state_p->getState();
    delete(state_p);
    return save_state;
}

template<class T>
void PQueueSearcher<T>::addToOpenList(State<T>* state) {
    vector<StatePriority<T>*> vector1;
    bool shouldBePushed = true;
    StatePriority<T>* state_p = new StatePriority<T>(state, getStatePriority(state));


    while(!p_queue.empty()){
        StatePriority<T>* curr = p_queue.top();
        p_queue.pop();

        if(*curr->getState()==*state){
            if(curr->getPriority()<state_p->getPriority()){
                shouldBePushed= false;
            }
            else{
                delete curr->getState();
                delete curr;
            }
            break;
        }
        vector1.push_back(curr);
    }
    if(shouldBePushed){
        p_queue.push(state_p);
    }
    else{
        delete state;
        delete state_p;
    }

    for(auto y : vector1){
        p_queue.push(y);
    }
}


#endif //FLIGTSIMPROJ2_PQUEUESEARCHER_H
