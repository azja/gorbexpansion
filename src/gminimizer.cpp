#include "../headers/gminimizer.h"

double GMinimizer :: trialEigen( const gsl_vector* vector, void* params) {

    GMinimizer* minimizer = (GMinimizer*)params;

    minimizer-> gelem.psi_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(minimizer->psi));
    minimizer-> gelem.psih_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(minimizer->psi_h));
    minimizer->general_solver.solve(*(minimizer->psi_h), *(minimizer->psi));

    return gsl_vector_get(&minimizer->general_solver.getEigenValues(), 0);
}


/*************************************************************************************/

const gsl_vector& GMinimizer::solve( double q, double gamma_0, double eps , double dq, double dg, gsl_vector* output) {

    gsl_multimin_fminimizer *s;
    const gsl_multimin_fminimizer_type *T;
    T = gsl_multimin_fminimizer_nmsimplex;
    s = gsl_multimin_fminimizer_alloc (T, 2);

    gsl_multimin_function my_func;
    my_func.n = 2;
    my_func.params = this;
    my_func.f = trialEigen;



    gsl_vector *initial_guess = gsl_vector_alloc(2);
    gsl_vector_set(initial_guess,0, q);
    gsl_vector_set(initial_guess,1, gamma_0);

    gsl_vector *initial_step = gsl_vector_alloc(2);
    gsl_vector_set(initial_step,0, dq);
    gsl_vector_set(initial_step,1, dg);

    gsl_multimin_fminimizer_set (s, &my_func, initial_guess, initial_step);
    double d;

    do    {
        gsl_multimin_fminimizer_iterate (s);
        d = gsl_multimin_fminimizer_size(s);
    }
    while ( d > eps);

    gsl_vector_set(scalar_results, 0, gsl_vector_get(gsl_multimin_fminimizer_x (s),0)); //q is set
    gsl_vector_set(scalar_results, 1, gsl_vector_get(gsl_multimin_fminimizer_x (s),1)); //g0 is set
    gsl_vector_set(scalar_results, 2, gsl_multimin_fminimizer_minimum (s)); //q is set
    gsl_multimin_fminimizer_free (s);
    gsl_vector_free (initial_guess);
    gsl_vector_free (initial_step);
    
     if(output != NULL && output->size == (size_t)_size)
     {
         getEigenVector(scalar_results,output);
     }
    return *scalar_results;
}


void GMinimizer::getEigenVector(const gsl_vector* vector, gsl_vector* eigen_vector) {
  gelem.psi_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(psi));
  gelem.psih_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(psi_h));
  general_solver.solve(*(psi_h), *(psi));
  general_solver.getMinEigenVector(*eigen_vector);
}

