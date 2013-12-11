#include "../headers/gelements.h"




/*************************************************************************************/

double GElements::psi_ij(double g_i, double g_j) {
  return pow((2* g_i * g_j)/(g_i*g_i + g_j*g_j),1.5);
}

/*************************************************************************************/
double GElements::psih_ij(double g_i, double g_j) {

double mult = g_i * g_j;
double sum =  g_i * g_i + g_j * g_j;

return 03 * gexp1 * pow(mult,2.5)/(pow(sum, 2.5)) - gexp2 * pow(mult,1.5)/(gsq_pi * sum);
}

/*************************************************************************************/
void GElements::calculate_g(double q, double g_0, gsl_vector& vector) {

 for(int i = -_size/2; i < _size/2; ++i) {
  gsl_vector_set(&vector,i, pow(q,i) * g_0 );
 }
}

/*************************************************************************************/
void GElements::calculate_g(double q, double g_0, double* vector) {

 for(int i = -_size/2; i < _size/2; ++i) {
  vector[i] =  pow(q,i) * g_0;
 }
}

/*************************************************************************************/
template <typename Functor>
void GElements::fill_matrix( double q, double g_0, gsl_matrix& matrix, Functor& f) {

  double non_diag = 0.0;

  calculate_g(q, g_0, *_gVector);
   for(int i = 0; i < _size; ++i) {
    for(int j = 0; j < i; ++j) {
     non_diag = f(gsl_vector_get(_gVector,i), gsl_vector_get(_gVector, j));
     gsl_matrix_set (&matrix, i, j, non_diag);
     gsl_matrix_set (&matrix, j, i, non_diag);
    }
    gsl_matrix_set(&matrix, i, i, f(gsl_vector_get(_gVector,i), gsl_vector_get(_gVector, i)));
   }

}

/************************************************************************************/
void GElements::psi_matrix(double q, double g_0, gsl_matrix& matrix) {
    fill_matrix(q,g_0,matrix,GElements::psi_ij);
}

/*************************************************************************************/
void GElements::psih_matrix(double q, double g_0, gsl_matrix& matrix) {
    fill_matrix(q,g_0,matrix,GElements::psih_ij);
}
