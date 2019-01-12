//
// Created by tomer on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_COMPARESTATE_H
#define FLIGTSIMPROJ2_COMPARESTATE_H

#include "State.h"
#include "StatePriority.h"


template <class T>
class CompareState {
public:
    bool operator()(State<T>* left, State<T>* right){
        return (left->getWeight()>right->getWeight());
    }
};

template <class T>
class PriorityStateCompare{
public:
    bool operator()(StatePriority<T>* left, StatePriority<T>* right){
        return (left->getPriority() > right->getPriority());
    }
};

template <class T>
struct PointerStateCompare{
    State<T>* search;
    explicit PointerStateCompare(State<T>* search){
        this->search=search;
    }
    bool operator()(State<T>* pointer){
        return (*pointer == *search);
    }
};

#endif //FLIGTSIMPROJ2_COMPARESTATE_H
