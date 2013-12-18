#ifndef GMINIMIZER_H_INCLUDED
#define GMINIMIZER_H_INCLUDED

#include "geignslv.h"
#include "gelements.h"
#include  "gslwrapper.h"
#include <gsl/gsl_multimin.h>
#include <iostream>


class GMinimizer {


 gsl_matrix *psi;
 gsl_matrix *psi_h;
 gsl_multimin_function *my_func;

 int _size;
 GElements gelem;
 Geignslv<GslEigenRealSymmetricSolver> general_solver;

static double trialEigen( const gsl_vector* vector, void* params);

public:

 GMinimizer(int size) :_size(size), gelem(size), general_solver(size) {

 psi = gsl_matrix_alloc(size,size);
 psi_h = gsl_matrix_alloc(size,size);

 }

double  solve(int n, double q, double gamma_0);

virtual ~GMinimizer() {
 gsl_matrix_free(psi);
 gsl_matrix_free(psi_h);
}

};



#endif // GMINIMIZER_H_INCLUDED
/***********************************************************************************/
