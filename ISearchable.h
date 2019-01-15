//
// Created by tomer on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_ISEARCHABLE_H
#define FLIGTSIMPROJ2_ISEARCHABLE_H

#include "State.h"
//#include "ISearcher.h"
#include <set>

template <class T>
class ISearchable {
public:
    virtual State<T>* getInitialState()=0;
    virtual bool isGoal(State<T>*)=0;
    virtual set<State<T>*> getAllPossibleStates(State<T>*)=0;
    virtual ~ISearchable()= default;
};


#endif //FLIGTSIMPROJ2_ISEARCHABLE_H
