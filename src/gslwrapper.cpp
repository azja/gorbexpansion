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
	 _input
	    = gsl_matrix_view_array (matrix, _size, _size);
	 _eval = gsl_vector_alloc (_size);
	 _evec = gsl_matrix_alloc(_size, _size);

}

/************************************************************************/

GslEigenSolver::GslEigenSolver(gsl_matrix& matrix) {

	 _input
	    = gsl_matrix_view_array ( matrix.data, matrix.size1, matrix.size2 );
	 _size = matrix.size1;
	 _eval = gsl_vector_alloc (_size);
	 _evec = gsl_matrix_alloc(_size, _size);

}

/************************************************************************/

const gsl_matrix& GslEigenSolver::getEigenVectors() {
	return *_evec;
}

/************************************************************************/

const gsl_vector& GslEigenSolver::getEigenValues() {
	return *_eval;
}

/************************************************************************/

GslEigenSolver :: ~GslEigenSolver() {
	gsl_vector_free (_eval);
	gsl_matrix_free (_evec);
}

//////////////////////////////////////////////////////////////////////////
///////////////// ////Real Symmetric Solver ///////////////////////////////
//////////////////////////////////////////////////////////////////////////

void GslEigenRealSymmetricSolver::solve() {
	gsl_eigen_symmv (&_input.matrix, _eval, _evec, _w);
	gsl_eigen_symmv_sort (_eval, _evec,
	                        GSL_EIGEN_SORT_ABS_ASC);
}

/************************************************************************/

GslEigenRealSymmetricSolver::~GslEigenRealSymmetricSolver() {
	gsl_eigen_symmv_free(_w);
}
