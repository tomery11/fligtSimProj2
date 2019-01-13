//
// Created by t on 1/13/19.
//

#include "Utils.h"


//parse by delimiter. input is string to delimit, token and vector for output
void Utils::parseByDelimiter(string inputStr, string token, vector<string> *outputVec) {
    //go over the inputStr and parses according to to the token
    std::size_t prev = 0, pos;
    while ((pos = inputStr.find_first_of(token, prev)) != string::npos) {
        if (pos > prev) {
            outputVec->push_back(inputStr.substr(prev, pos - prev));
        }
        prev = pos + 1;
    }
    //add last word
    if (prev < inputStr.length()) {
        outputVec->push_back(inputStr.substr(prev, string::npos));
    }
}