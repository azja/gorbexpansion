#include "../headers/gminimizer.h"

double GMinimizer :: trialEigen( const gsl_vector* vector, void* params) {

GMinimizer* minimizer = (GMinimizer*)params;

minimizer-> gelem.psi_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(minimizer->psi));
minimizer-> gelem.psih_matrix(gsl_vector_get(vector,0), gsl_vector_get(vector,1), *(minimizer->psi_h));
minimizer->general_solver.solve(*(minimizer->psi_h), *(minimizer->psi));

return gsl_vector_get(&minimizer->general_solver.getEigenValues(), 0);
}




double GMinimizer::solve(int n, double q, double gamma_0) {

  double dq = 0.001;
  double dg = 0.001;

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

  do
    {

     gsl_multimin_fminimizer_iterate (s);
     d=gsl_multimin_fminimizer_size(s);

    }
  while ( d > 1.0e-6);

  std::cout<<"q = "<<gsl_vector_get(gsl_multimin_fminimizer_x (s),0)<< " g_0 = "<<gsl_vector_get(gsl_multimin_fminimizer_x (s),1)<<" E_0 ="<<gsl_multimin_fminimizer_minimum (s)<<std::endl;

  gsl_multimin_fminimizer_free (s);
  gsl_vector_free (initial_guess);
  gsl_vector_free (initial_step);




return 0;
}
