//
// Created by t on 1/8/19.
//

#ifndef FLIGTSIMPROJ2_STRINGREVERSER_H
#define FLIGTSIMPROJ2_STRINGREVERSER_H
#include "Solver.h"
#include <string>
using namespace std;

class StringReverser : public Solver<string, string> {
public:
    virtual string solve(string problem);
};


#endif //FLIGTSIMPROJ2_STRINGREVERSER_H
