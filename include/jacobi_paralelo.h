#ifndef JACOBI_PARALELO_H
#define JACOBI_PARALELO_H

#include "../include/parser.h"
#include "header.h"
#include <omp.h>

#define N 2000
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

typedef enum {
    STATIC,
    DYNAMIC,
    GUIDED
} ScheduleType;

int jacobi_paralelo(double A[N][N], double *b, double *x, ScheduleType type, int chunk_size, int num_threads);

#endif /* JACOBI_PARALELO_H */
