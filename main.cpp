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


#define N  51

int main() {

    double q = 2.0;
    double g0 = 2.0;

    for(int i = 1, j = 0; i <= N; i = 2*(++j) + 1) { /* i in {2k+1} */

        std::cout<<"#Gaussian: "<<i<<" Result:       ";
        GMinimizer minimizer(i);                  /*minimizer*/
        gsl_vector *eigen = gsl_vector_alloc(i);
        const gsl_vector  *result =  &minimizer.solve(q, g0,0.000001,0.01, 0.01,  eigen);

        q = gsl_vector_get(result,0);
        g0 =gsl_vector_get(result, 1);

        std::cout<<"q = "<<q<< " g_0 = "<<g0<<" E_0 = "<<gsl_vector_get(result, 2)<<std::endl;
        gsl_vector_free(eigen);
    }

    return EXIT_SUCCESS;
}



