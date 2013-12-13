#ifndef GEIGNSLV_H_
#define GEIGNSLV_H_

/* So called general eigen problem solution
*     H * c = lambda * S * c
*     H is  double  n x n matrix ( gsl_matrix)
*     c is n dimensional eigen vector
*     lambda is eigen value
*     S is n x n matrix
*/

#include "gslwrapper.h"
#include <gsl/gsl_cblas.h>

template <typename EigenSolver>
class Geignslv {

gsl_matrix* mA;
gsl_matrix* mD;
gsl_vector* mS;
gsl_matrix* mV;
gsl_vector* mL;

EigenSolver _solver;

const size_t _size;

void s_eigen(gsl_matrix& S) {

 _solver.solve(S);
 mD = &_solver.getEigenVectors();
 mS = &_solver.getEigenValues();


 for(size_t i = 0; i < _size; i++) {
   for( size_t j = 0; j < i; j++) {
    double v  = gsl_matrix_get(mD, i, j)/sqrt(gsl_vector_get(mS,j));
    gsl_matrix_set(mD, i, j, v);
   }
 }


}

void aha_eigen(gsl_matrix& H) {

}

public:

Geignslv( size_t size): _solver( EigenSolver(size) ), _size(size) {

	 mS = gsl_vector_alloc(_size);
	 mV = gsl_matrix_alloc(_size, _size);
	 mL = gsl_vector_alloc (_size);

}

void solve( gsl_matrix& H, gsl_matrix& S) {
 s_eigen(S);
}


//void solve(const double * H, const double * S);

~Geignslv() {


 gsl_matrix_free(mV);
 gsl_vector_free(mL);
}

};

#endif /*GEIGNSLV_H_*/
