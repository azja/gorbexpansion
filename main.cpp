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
#include "headers/gelements.h"

#include "headers/gminimizer.h"
#include <iostream>


#define N  51
int main() {

for(int i = 1, j = 0; i < N; i = 2*j + 1, j++) {
std::cout<<"#Gaussian: "<<i<<" Result:       ";
GMinimizer minimizer(i);
minimizer.solve(i, 2.0, 2.0);
}


	return EXIT_SUCCESS;
}



