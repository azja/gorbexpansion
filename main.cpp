//============================================================================
// Name        : GaussOrbitalExpansion.cpp
// Author      : Andrzej Biborski
// Version     :
// Copyright   : Your copyright notice
// Description : Expands orbital, Slater - typed wave function into SGO
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include "headers/gslwrapper.h"
#include "headers/geignslv.h"
#include "headers/gelements.h"


#define N  15

int main(void) {


gsl_matrix *psi = gsl_matrix_alloc(N,N);
gsl_matrix *psi_h = gsl_matrix_alloc(N,N);

GElements gelem(N);
Geignslv<GslEigenRealSymmetricSolver> general_solver(N);
for(int i = 0; i < 1000; ++i) {
gelem.psi_matrix(1.4928,3.9443, *psi);
gelem.psih_matrix(1.4928, 3.9443, *psi_h);


general_solver.solve(*psi_h, *psi);

}

GslMatrixManip::show(general_solver.getEigenValues());


	return EXIT_SUCCESS;
}
