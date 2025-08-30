#ifndef JACOBI_SEQUENCIAL_H
#define JACOBI_SEQUENCIAL_H

#include "header.h"

#define N 3
#define CRITERIO_PARADA 1e-5

void jacobi(double **A, double b[], double p);

#endif
