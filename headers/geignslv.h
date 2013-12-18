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
#include <gsl/gsl_blas.h>



template <typename EigenSolver>
class Geignslv {

gsl_matrix* mA;
gsl_matrix* mT;
gsl_matrix* mAha;
gsl_matrix* mD;
gsl_vector* mS;
gsl_matrix* mC;
gsl_vector* mL;

EigenSolver _solver;

const size_t _size;

void s_eigen(gsl_matrix& S) {

 _solver.solve(S);
 mD = &_solver.getEigenVectors();
 mS = &_solver.getEigenValues();


 for(size_t i = 0; i < _size; i++) {
   for( size_t j = 0; j < _size; j++) {
    double v  = gsl_matrix_get(mD, i, j)/sqrt(gsl_vector_get(mS,j));
    gsl_matrix_set(mA, i, j, v);
   }
 }


}

void aha_eigen(gsl_matrix& H) {

 gsl_blas_dgemm ( CblasNoTrans, CblasNoTrans, 1.0 , &H, mA, 0.0, mT);
 gsl_blas_dgemm ( CblasTrans, CblasNoTrans, 1.0 , mA, mT, 0.0, mAha);
 _solver.solve(*mAha);

}

void calc_c() {
 //gsl_blas_dgemv ('N', 1.0, mA, _solver.getEigenValues(), 0.0, mL)
}

public:

const gsl_matrix& getEigenVectors() {
 return _solver.getEigenVector();
}

const gsl_vector& getEigenValues()  {
 return _solver.getEigenValues();
}

Geignslv( size_t size): _solver( EigenSolver(size) ), _size(size) {

	 mA = gsl_matrix_alloc(_size, _size);
         mT = gsl_matrix_alloc(_size, _size);
         mAha = gsl_matrix_alloc(_size, _size);
	 mC = gsl_matrix_alloc(_size, _size);
	 mL = gsl_vector_alloc (_size);

}

void solve( gsl_matrix& H, gsl_matrix& S) {
 s_eigen(S);
 aha_eigen(H);
}




//void solve(const double * H, const double * S);

~Geignslv() {

 gsl_matrix_free(mT);
 gsl_matrix_free(mA);
 gsl_matrix_free(mC);
 gsl_matrix_free(mAha);
 gsl_vector_free(mL);

}

};





#endif /*GEIGNSLV_H_*/
