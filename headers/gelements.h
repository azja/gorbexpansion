#ifndef GELEMENTS_H_
#define GELEMENTS_H_

#include <gsl/gsl_matrix.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>


static const double  gexp1 = pow(2,2.5);
static const double  gexp2 = pow(2,3.5);
static const double  gpi = 3.14159265359;
static const double  gsq_pi = pow(gpi, 0.5);


class GElements {

    double psi_ij(double g_i, double g_j);
    double psih_ij(double g_i, double g_j);

    void calculate_g(double q, double g_0, gsl_vector& g_vector);
    void calculate_g(double q, double g_0, double* g_vector) ;

    template <typename Functor>
    void fill_matrix(double q, double g_0, gsl_matrix& matrix,Functor& f);

    const int _size;
    gsl_vector* _gVector;

public:

    GElements(const GElements&) = delete;
    GElements& operator=(const GElements&) = delete;

    void psi_matrix(double q, double g_0, gsl_matrix& matrix);
    void psih_matrix(double q, double g_0, gsl_matrix& matrix);

    GElements(int size) : _size(size) {
        _gVector = gsl_vector_alloc (_size);
    }

    ~GElements() {
        gsl_vector_free( _gVector );
    }

};
#endif /*GELEMENTS_H_*/
