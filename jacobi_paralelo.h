#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define N 2000
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

typedef enum {
    STATIC,
    DYNAMIC,
    GUIDED
} ScheduleType;

int jacobi_paralelo(double **A, double *b, double *x, ScheduleType type, int chunk_size);