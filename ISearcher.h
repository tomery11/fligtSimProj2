//
// Created by tomer on 1/7/19.
//

#ifndef FLIGTSIMPROJ2_ISEARCHER_H
#define FLIGTSIMPROJ2_ISEARCHER_H


#include "ISearchable.h"

class ISearcher {
public:
    //not sure whether this needs to be generic.
virtual int search(ISearchable searchable)=0;
virtual int getNumberOfNodesEvaluated()=0;
};


#endif //FLIGTSIMPROJ2_ISEARCHER_H
