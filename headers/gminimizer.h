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
    gsl_vector *scalar_results;
    int _size;
    GElements gelem;
    Geignslv<GslEigenRealSymmetricSolver> general_solver;

    static double trialEigen( const gsl_vector* vector, void* params);
    void getEigenVector(const gsl_vector* parameters, gsl_vector* eigen_vector);



public:



    GMinimizer(int size) :_size(size), gelem(size), general_solver(size) {

        psi = gsl_matrix_alloc(size,size);
        psi_h = gsl_matrix_alloc(size,size);
        scalar_results = gsl_vector_alloc( 3 ); //q, g_0, E_0

    }



    GMinimizer(const GMinimizer&) = delete;
    GMinimizer& operator=(const GMinimizer&) = delete;



    const gsl_vector& solve( double q, double gamma_0, double eps = 1.0e-6, double dq = 0.001, double dg = 0.001,gsl_vector* output = NULL);

    virtual ~GMinimizer() {
        gsl_matrix_free(psi);
        gsl_matrix_free(psi_h);
        gsl_vector_free(scalar_results);
    }


};



#endif // GMINIMIZER_H_INCLUDED

