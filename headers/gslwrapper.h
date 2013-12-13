/*
 * gslwrapper.h
 *
 *  Created on: 9 gru 2013
 *      Author: abiborski
 */

#ifndef GSLWRAPPER_H_
#define GSLWRAPPER_H_

#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <iostream>


/*
 * Theses classes hide implementations of annoying gsl initialization
 * they are not responsible for handling with matrices (allocation, handling etc.)
 */

struct GslMatrixManip {

static void show(const gsl_matrix& matrix) {

for (size_t i = 0; i < matrix.size1; ++i)
      {
        for(size_t j = 0; j < matrix.size2; ++j)
         std::cout<<matrix.data[i * matrix.size1 + j]<<" ";
        std::cout<<std::endl;
      }

}

static void show(const gsl_vector& vector) {

for (size_t i = 0; i < vector.size; ++i)
      {
         std::cout<<vector.data[i * vector.stride]<<" ";
      }
 std::cout<<std::endl;
}

};




class GslEigenSolver {

protected:
	GslEigenSolver(double* matrix, size_t size);
	GslEigenSolver(gsl_matrix& matrix);
	GslEigenSolver(size_t size);
	size_t _size;
	gsl_matrix* _input;

	gsl_vector* _eval;
	gsl_matrix* _evec;

public:

	void setMatrix();

	virtual void solve() = 0;
    virtual void solve(double* matrix) = 0;
    virtual void solve(gsl_matrix& matrix) = 0;

	gsl_matrix& getEigenVectors();
	gsl_vector& getEigenValues();


	virtual ~GslEigenSolver();

};

class GslEigenRealSymmetricSolver: public GslEigenSolver {

	gsl_eigen_symmv_workspace* _w;

public:
	GslEigenRealSymmetricSolver(double* matrix, size_t size) :
			GslEigenSolver(matrix, size) {
		_w = gsl_eigen_symmv_alloc(_size);
	}

	GslEigenRealSymmetricSolver(gsl_matrix& matrix, size_t size) :
			GslEigenSolver(matrix) {
		_w = gsl_eigen_symmv_alloc(_size);
	}

	GslEigenRealSymmetricSolver(size_t size) :
			GslEigenSolver(size) {
		_w = gsl_eigen_symmv_alloc(_size);
	}


	void solve();
	void solve(double* matrix);
	void solve(gsl_matrix& matrix);

	~GslEigenRealSymmetricSolver();

};

#endif /* GSLWRAPPER_H_ */
