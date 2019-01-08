//
// Created by t on 1/8/19.
//

#include "StringReverser.h"

//get a string and return it's reverse string
string StringReverser::solve(string problem) {
    string reverse;
    for (int i = 0; i < problem.length(); i++) {
        reverse += problem[i];
    }
    return reverse;
}
