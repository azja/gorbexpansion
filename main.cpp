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


#define N  10

int main(void) {
	//puts("");

double 	M[ N * N];

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j <= i; ++j){
		M[j + i*N]  = i + 1;//static_cast<double>(i + j);
        if( i != j)
		 M[j*N + i] = i;
		}
	}

GslEigenRealSymmetricSolver solver(M,N);
solver.solve();
GslMatrixManip::show(solver.getEigenValues());

	return EXIT_SUCCESS;
}
