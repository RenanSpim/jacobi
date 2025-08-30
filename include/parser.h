#ifndef PARSER_H
#define PARSER_H

#include "header.h"

#define N 2000
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

void read_file(const char *filename, double A[N][N], double B[N]);

#endif /* PARSER_H */