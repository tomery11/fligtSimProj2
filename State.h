//
// Created by tomer on 1/10/19.
//
#include <string>
#include <iostream>

#ifndef FLIGTSIMPROJ2_STATE_H
#define FLIGTSIMPROJ2_STATE_H
using namespace std;
template <class T>
class State {
private:
        T* state;
        State<T>* pre= nullptr;
        double weight;
        bool appear_inSolution=false;

public:
    State(T* state, double weight, State<T>* pre);
    ~State();

    //get & set
    T* getState();
    State<T>* getPre();
    void setPre(State<T>* pre);
    double getWeight();
    void setWeight(double weight);

    //overload operator==
    bool operator==(State<T>& rightSide);

    //auxilary functions
    void switchSolution();
    bool appearInSolution();

};




template<class T>
State<T>::State(T *state, double weight, State<T> *pre) {
    this->state=state;
    this->weight=weight;
    this->pre=pre;
}

template<class T>
State<T>::~State() {
    delete state;
}

template<class T>
T *State<T>::getState() {
    return this->state;
}

template<class T>
State<T> *State<T>::getPre() {
    return this->pre;
}

template<class T>
void State<T>::setPre(State<T> *pre) {
    this->pre=pre;
}

template<class T>
double State<T>::getWeight() {
    return this->weight;
}

template<class T>
void State<T>::setWeight(double weight) {
    this->weight=weight;
}

template<class T>
bool State<T>::operator==(State<T> &rightSide) {
    return (*this->getState() == *rightSide.getState());
}

template<class T>
void State<T>::switchSolution() {
    this->appear_inSolution = !this->appear_inSolution;
}

template<class T>
bool State<T>::appearInSolution() {
    return this->appear_inSolution;
}





#endif //FLIGTSIMPROJ2_STATE_H
