/*
 * gslwrapper.cpp
 *
 *  Created on: 9 gru 2013
 *      Author: Andrzej Biborski
 */

#include "../headers/gslwrapper.h"


/************************************************************************/

GslEigenSolver::GslEigenSolver(double* matrix, size_t size) {
    _size = size;
    std::cout<<"Size is = "<<size<<std::endl;
    _input = gsl_matrix_alloc(_size, _size);
    _input->data = matrix;
    _eval = gsl_vector_alloc (_size);
    _evec = gsl_matrix_alloc(_size, _size);

}

/************************************************************************/

GslEigenSolver::GslEigenSolver(gsl_matrix& matrix) {

    _size = matrix.size1;
    _input = gsl_matrix_alloc(_size, _size);
    _input->data = matrix.data;
    _eval = gsl_vector_alloc (_size);
    _evec = gsl_matrix_alloc(_size, _size);

}

/************************************************************************/

GslEigenSolver::GslEigenSolver(size_t size) {

    _size = size;
    _input = gsl_matrix_alloc(_size, _size);
    _input->data = NULL;
    _eval = gsl_vector_alloc (_size);
    _evec = gsl_matrix_alloc(_size, _size);

}

/************************************************************************/

gsl_matrix& GslEigenSolver::getEigenVectors() {
    return *_evec;
}

/************************************************************************/
gsl_vector& GslEigenSolver::getEigenValues() {
    return *_eval;
}

/************************************************************************/

GslEigenSolver :: ~GslEigenSolver() {
    gsl_vector_free (_eval);
    gsl_matrix_free (_evec);
    gsl_matrix_free (_input);
}

//////////////////////////////////////////////////////////////////////////
///////////////// ////Real Symmetric Solver ///////////////////////////////
//////////////////////////////////////////////////////////////////////////

void GslEigenRealSymmetricSolver::solve() {

    if(_input->data == NULL) {
        std::cerr<<"Data is null in void GslEigenRealSymmetricSolver::solve()"<<std::endl;
        return;
    }
    gsl_eigen_symmv (_input, _eval, _evec, _w);
    gsl_eigen_symmv_sort (_eval, _evec,
                          GSL_EIGEN_SORT_VAL_ASC);
}

/************************************************************************/

void GslEigenRealSymmetricSolver::solve(double* matrix) {
    _input->data = matrix;
    gsl_eigen_symmv (_input, _eval, _evec, _w);
    gsl_eigen_symmv_sort (_eval, _evec,
                          GSL_EIGEN_SORT_VAL_ASC);
}

/************************************************************************/


void GslEigenRealSymmetricSolver::solve(gsl_matrix& matrix) {

    gsl_eigen_symmv (&matrix, _eval, _evec, _w);
    gsl_eigen_symmv_sort (_eval, _evec,
                          GSL_EIGEN_SORT_VAL_ASC);
}

/************************************************************************/


GslEigenRealSymmetricSolver::~GslEigenRealSymmetricSolver() {
    gsl_eigen_symmv_free(_w);
}

