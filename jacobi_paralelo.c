#include "main.h"
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int jacobi_paralelo(double **A, double *b, double *x) {
    double *x_new = malloc(n * sizeof(double));
    int iterations = 0;
    double error = CRITERIO_PARADA + 1.0;

    while (iterations++ < MAX_ITER && error > CRITERIO_PARADA) {
        error = 0.0;

        #pragma omp parallel for reduction(max:error)
        for (int i = 0; i < N; i++) {
            double sigma = 0.0;

            for (int j = 0; j < N; j++) {
                if (i == j) continue;

                sigma += A[i][j] * x[j];
            }

            x_new[i] = (b[i] - sigma) / A[i][i];

            double local_error = fabs(x_new[i] - x[i]);

            error = local_error > error ? local_error : error;
        }

        for (int i = 0; i < N; i++) {
            x[i] = x_new[i];
        }
    }

    return 1;
}

int main() {

}
