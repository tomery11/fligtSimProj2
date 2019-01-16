//
// Created by tomer on 1/15/19.
//

#ifndef FLIGTSIMPROJ2_DEPTHFIRSTSEARCH_H
#define FLIGTSIMPROJ2_DEPTHFIRSTSEARCH_H

#include <stack>
#include "Searcher.h"

template <class T>
class DepthFirstSearch : public Searcher<State<T>>{
private:
    stack<State<T>*> openList1;
    stack<State<T>*> openList2;
    void reverseBackStack();
public:
    void addToOpenList(State<T>* curr_state);
    bool isOpenListEmpty();
    void clearAllStates();
    State<T*> popOpenList();
};

template<class T>
void DepthFirstSearch<T>::addToOpenList(State<T> *curr_state) {
    //meaning openList2 is the empty stack
    State<T>* temp_state;
    bool is_inStack1=false;
    if(!openList1.empty()){
        while(!openList1.empty()){
            is_inStack1=true;
            temp_state=openList1.top();
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
            temp_state=openList2.top();
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

    reverseBackStack();

}

template<class T>
bool DepthFirstSearch<T>::isOpenListEmpty() {
    return (openList1.empty() || openList2.empty());
}

template<class T>
State<T *> DepthFirstSearch<T>::popOpenList() {
    Searcher<T> :: evaluatedNodes++;
    State<T>* toReturn;
    if(!openList1.empty()){
        toReturn=openList1.top();
        openList1.pop();
    }else{
        toReturn=openList2.top();
        openList2.pop();
    }
    return toReturn;

}

template<class T>
void DepthFirstSearch<T>::clearAllStates() {
    Searcher<T> ::clearAllStates();
    State<T>* temp_state;
    bool is_inStack1=false;
    if(!openList1.empty()){
        while(!openList1.empty()){
            is_inStack1=true;
            temp_state=openList1.top();
            if(temp_state->appearInSolution()){
                delete temp_state;
            }
            openList1.pop();
            openList2.push(temp_state);
        }
    }
    if(!is_inStack1){
        while(!openList2.empty()){
            temp_state=openList2.top();
            if(temp_state->appearInSolution()){
                delete temp_state;
            }
            openList2.pop();
            openList1.push(temp_state);
        }
    }
    reverseBackStack();
}

template<class T>
void DepthFirstSearch<T>::reverseBackStack() {
    State<T>* x;
    if(!openList1.empty()){
        x= openList1.top();
        openList1.pop();
        openList2.push(x);
    }else if(!openList2.empty()){
        x = openList2.top();
        openList2.pop();
        openList1.push(x);
    }
}


#endif //FLIGTSIMPROJ2_DEPTHFIRSTSEARCH_H
