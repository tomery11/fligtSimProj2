//
// Created by t on 1/16/19.
//

#include "MatrixCacheAdapter.h"

MatrixCacheAdapter::MatrixCacheAdapter(FileCacheManager *fileCacheManager1) {
    this->fileCacheManager = fileCacheManager1;
}

bool MatrixCacheAdapter::hasSolutionForProblem(Matrix *problem) {
    string strR = problem->getStrRepresentation();
    this->fileCacheManager->hasSolutionForProblem(&strR);
}

string MatrixCacheAdapter::getSolutionForProblem(Matrix *problem) {
    string strR = problem->getStrRepresentation();
    this->fileCacheManager->getSolutionForProblem(&strR);
}

void MatrixCacheAdapter::save(Matrix problem, string solution) {

}