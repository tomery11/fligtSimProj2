//
// Created by t on 1/16/19.
//

#include "MatrixCacheAdapter.h"

MatrixCacheAdapter::MatrixCacheAdapter(FileCacheManager *fileCacheManager1) {
    this->fileCacheManager = fileCacheManager1;
}

bool MatrixCacheAdapter::hasSolutionForProblem(Matrix problem) {
    this->fileCacheManager->hasSolutionForProblem(problem.)
}
string MatrixCacheAdapter::getSolutionForProblem(Matrix problem);
void MatrixCacheAdapter::save(Matrix problem, string solution);