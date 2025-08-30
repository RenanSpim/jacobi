#ifndef JACOBI_SEQUENCIAL_H
#define JACOBI_SEQUENCIAL_H

#include "header.h"
#include "../include/parser.h"

#define N 2000
#define CRITERIO_PARADA 1e-5

void jacobi(double A[N][N], double b[], double p);

#endif
