#include "../headers/geignslv.h"


void Geignslv::s_eigen(gsl_matrix& S) {

_solver.solve(S);
mA = &_solver.getEigenVectors();

}

void Geignslv::aha_eigen(gsl_matrix& H) {


}
