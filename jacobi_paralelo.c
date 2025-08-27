#include "jacobi_paralelo.h"

int jacobi_paralelo(double **A, double *b, double *x, ScheduleType type, int chunk_size) {
    double *x_new = malloc(N * sizeof(double));
    int iterations = 0;
    double error = CRITERIO_PARADA + 1.0;
    struct timespec inicio, fim;

    omp_sched_t kind;
    switch (type)
    {
    case STATIC: kind = omp_sched_static; break;
    case GUIDED: kind = omp_sched_guided; break;
    case DYNAMIC: kind = omp_sched_dynamic; break;
    default: 
        printf("Digite um tipo correto\n"); 
        return NULL;
        break;
    }
    omp_set_schedule(kind, chunk_size);

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    while (iterations++ < MAX_ITER && error <= CRITERIO_PARADA) {
        error = 0.0;
        #pragma omp parallel for schedule(runtime) reduction(max:error)
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
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo de execução: %f segundos\n", tempo);
    return 1;
}
