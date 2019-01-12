//
// Created by tomer on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_STATEPRIORITY_H
#define FLIGTSIMPROJ2_STATEPRIORITY_H

#include "State.h"

template <class T>
class StatePriority {
    double priority = 0;
    State<T>* state;
public:
    void setPriority(double weight);
    void setState(State<T>* state);
    State<T>* getState();
    double getPriority();

};

template<class T>
void StatePriority<T>::setPriority(double weight) {
    this->priority=weight;
}

template<class T>
void StatePriority<T>::setState(State<T> *state) {
    this->state=state;
}

template<class T>
State<T> *StatePriority<T>::getState() {
    return this->state;
}

template<class T>
double StatePriority<T>::getPriority() {
    return this->priority;
}


#endif //FLIGTSIMPROJ2_STATEPRIORITY_H
