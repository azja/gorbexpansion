//============================================================================
// Name        : GaussOrbitalExpansion.cpp
// Author      : Andrzej Biborski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include "headers/gslwrapper.h"
#include "headers/geignslv.h"
#include "headers/gelements.h"


#define N  3

int main(void) {
	//puts("");



gsl_matrix *psi = gsl_matrix_alloc(N,N);
gsl_matrix *psi_h = gsl_matrix_alloc(N,N);

GElements gelem(N);

gelem.psi_matrix(2.2092, 0.892, *psi);
gelem.psih_matrix(2.2092, 0.892, *psi_h);

//GslMatrixManip::show(*psi_h);


Geignslv<GslEigenRealSymmetricSolver> general_solver(N);

general_solver.solve(*psi_h, *psi);
GslMatrixManip::show(general_solver.getEigenValues());



//GslEigenRealSymmetricSolver solver(*psi,N);
//solver.solve();
//GslMatrixManip::show(solver.getEigenValues());

/*

double 	M[ N * N];

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j <= i; ++j){
		M[j + i*N]  = static_cast<double>(i + j + 1);
        if( i != j)
		 M[j*N + i] = M[j + i*N];
		}
	}

GslEigenRealSymmetricSolver solver(M,N);
solver.solve();
GslMatrixManip::show(solver.getEigenValues());


Geignslv< GslEigenRealSymmetricSolver > gs(N);

gsl_matrix *matrix = gsl_matrix_alloc(N, N);
matrix->data = M;
GslMatrixManip::show(*matrix);
gs.solve(*matrix, *matrix);
*/
	return EXIT_SUCCESS;
}
