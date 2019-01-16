//
// Created by tomer on 1/15/19.
//

#ifndef FLIGTSIMPROJ2_BREADTHFIRSTSEARCH_H
#define FLIGTSIMPROJ2_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>;

template <class T>
class BreadthFirstSearch {
private:
    queue<State<T>*> openList1;

    queue<State<T>*> openList2;
public:
    void addToOpenList(State<T>* curr_state);
    bool isOpenListEmpty();
    void clearAllStates();
    State<T*> popOpenList();
};

template<class T>
bool BreadthFirstSearch<T>::isOpenListEmpty() {
    return (openList1.empty()||openList2.empty());
}

template<class T>
void BreadthFirstSearch<T>::addToOpenList(State<T> *curr_state) {
    // before we put the state in our list we will check that it doesn't
    //exist already
    State<T>* temp_state;
    bool is_inStack1=false;
    if(!openList1.empty()){
        while(!openList1.empty()){
            is_inStack1=true;
            temp_state=openList1.front();
            if(temp_state==curr_state){
                delete curr_state;
                return;
            }
            openList1.pop();
            openList2.push(temp_state);
        }
    }
    if(!is_inStack1){
        while(!openList2.empty()){
            temp_state=openList2.front();
            if(temp_state==curr_state){
                delete curr_state;
                return;
            }
            openList2.pop();
            openList1.push(temp_state);
        }
    }
    if(is_inStack1)
        openList2.push(curr_state);
    else{
        openList1.push(curr_state);
    }


}

template<class T>
void BreadthFirstSearch<T>::clearAllStates() {
    Searcher<T> ::clearAllStates();
    State<T>* temp_state;
    bool is_inStack1=false;
    if(!openList1.empty()){
        while(!openList1.empty()){
            is_inStack1=true;
            temp_state=openList1.front();
            if(temp_state->appearInSolution()){
                delete temp_state;
            }
            openList1.pop();
            openList2.push(temp_state);
        }
    }
    if(!is_inStack1){
        while(!openList2.empty()){
            temp_state=openList2.front();
            if(temp_state->appearInSolution()){
                delete temp_state;
            }
            openList2.pop();
            openList1.push(temp_state);
        }
    }
}

template<class T>
State<T *> BreadthFirstSearch<T>::popOpenList() {
    Searcher<T> :: evaluatedNodes++;
    State<T>* toReturn;
    if(!openList1.empty()){
        toReturn=openList1.front();
        openList1.pop();
    }else{
        toReturn=openList2.front();
        openList2.pop();
    }
    return toReturn;
}


#endif //FLIGTSIMPROJ2_BREADTHFIRSTSEARCH_H
