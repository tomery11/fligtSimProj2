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


#endif //FLIGTSIMPROJ2_STATE_H
