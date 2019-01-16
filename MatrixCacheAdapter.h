//
// Created by t on 1/16/19.
//

#ifndef FLIGTSIMPROJ2_MATRIXCACHEADAPTER_H
#define FLIGTSIMPROJ2_MATRIXCACHEADAPTER_H

#include "FileCacheManager.h"
#include "CacheManager.h"
#include "Matrix.h"
using namespace std;

class MatrixCacheAdapter : public CacheManager<Matrix, string> {
    FileCacheManager *fileCacheManager;
public:
    MatrixCacheAdapter(FileCacheManager *fileCacheManager1);
    virtual bool hasSolutionForProblem(Matrix problem);
    virtual string getSolutionForProblem(Matrix problem);
    virtual void save(Matrix problem, string solution);
};


#endif //FLIGTSIMPROJ2_MATRIXCACHEADAPTER_H
