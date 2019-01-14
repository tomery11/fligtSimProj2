//
// Created by tomer on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_ISEARCHER_H
#define FLIGTSIMPROJ2_ISEARCHER_H


#include "ISearchable.h"
#include "State.h"

template <class T>
class ISearcher {
public://not sure whether this needs to be generic.
virtual State<T>* search(ISearchable<T>& searchable)=0;
virtual int getNumberOfNodesEvaluated()=0;
virtual ~ISearcher();
};


#endif //FLIGTSIMPROJ2_ISEARCHER_H
