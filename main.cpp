//============================================================================
// Name        : gorbexpansion
// Author      : Andrzej Biborski
// Version     : 1.0
// Copyright   : General Public Licence
// Description : s-like GTO expansion for s-Slater wave function of hydrogenium
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include "headers/gslwrapper.h"
#include "headers/geignslv.h"
#include "headers/gelements.h"
#include "headers/gelements.h"
#include "headers/gminimizer.h"
#include <iostream>


#define N  21

int main()

double q = 2.0;
double g0 = 2.0;

 for(int i = 1, j = 0; i <= N; i = 2*(++j) + 1) { /* i in {2k+1} */

    std::cout<<"#Gaussian: "<<i<<" Result:       ";
    GMinimizer minimizer(i);                  /*minimizer*/
    const gsl_vector  *result =  &minimizer.solve(q, g0, 1.0e-6);

    q = gsl_vector_get(result,0);
    g0 =gsl_vector_get(result, 1);

    std::cout<<"q = "<<q<< " g_0 = "<<g0<<" E_0 = "<<gsl_vector_get(result, 2)<<std::endl;
 }

return EXIT_SUCCESS;
}



