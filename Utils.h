//
// Created by t on 1/13/19.
//

#ifndef FLIGTSIMPROJ2_UTILS_H
#define FLIGTSIMPROJ2_UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils {
public:
    void parseByDelimiter(string inputStr, string token, vector<string> *outputVec);
};


#endif //FLIGTSIMPROJ2_UTILS_H
